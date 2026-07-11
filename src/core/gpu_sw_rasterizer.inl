// SPDX-FileCopyrightText: 2026 RlyehPSX <https://github.com/RlyehPSX>
// SPDX-License-Identifier: GPL-3.0-or-later
//
// This implementation was developed for Project R'lyehPSX as an independent
// implementation of the software rasterizer.
//
// Public interfaces, behavior, and integration points were designed to remain compatible
// with the surrounding emulator architecture and existing callers.
//
// Similarities in function signatures, data structures, control flow, and observable
// behavior reflect compatibility and integration requirements derived from the surrounding
// codebase rather than shared implementation code.
//
// This file is deliberately reusable from an architecture namespace.

#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdlib>
#include <utility>

namespace {

/*
 * VRAM stores pixels as RGB5551: R in bits 0..4, G in 5..9, B in 10..14,
 * and the texture semi-transparency/mask flag in bit 15. PS1 dithering is
 * phased by final raster-space coordinates. Selecting matrix position (2,3),
 * whose value is zero, reproduces undithered floor(V/8) quantization while
 * retaining identical clamping behavior.
 */
ALWAYS_INLINE u8 QuantizeChannel(u32 value, s32 x, s32 y, bool dither)
{
  return GPU_SW_Rasterizer::g_dither_lut[dither ? (static_cast<u32>(y) & 3u) : 2u]
                                               [dither ? (static_cast<u32>(x) & 3u) : 3u]
                                               [value];
}

/*
 * PS1 textures live in the same 1024x512 array of 16-bit VRAM words used as
 * the render target. A texture page begins at (page_x * 64, page_y * 256).
 * Coordinates first pass through the texture window independently:
 *
 *   windowed = (coordinate & AND_mask) | OR_value
 *
 * Four-bit indexed texels pack four low-to-high nibbles per word; eight-bit
 * texels pack low/even and high/odd bytes. Those indices address the expanded
 * 256-entry CLUT maintained by the surrounding GPU backend. Direct modes read
 * RGB5551 words. Both axes wrap to physical VRAM dimensions.
 *
 * Because source and destination share g_vram, fetch timing and primitive
 * traversal order are hardware-visible when a draw overlaps its texture.
 */
ALWAYS_INLINE u16 FetchTexel(const GPUBackendDrawCommand* cmd, u8 u, u8 v)
{
  u = static_cast<u8>((u & cmd->window.and_x) | cmd->window.or_x);
  v = static_cast<u8>((v & cmd->window.and_y) | cmd->window.or_y);
  const u32 base_x = cmd->draw_mode.GetTexturePageBaseX();
  const u32 base_y = cmd->draw_mode.GetTexturePageBaseY();

  switch (cmd->draw_mode.texture_mode.GetValue())
  {
    case GPUTextureMode::Palette4Bit:
    {
      const u16 packed = g_vram[((base_y + v) & VRAM_HEIGHT_MASK) * VRAM_WIDTH + ((base_x + (u >> 2)) & VRAM_WIDTH_MASK)];
      return g_gpu_clut[(packed >> ((u & 3u) * 4u)) & 0x0fu];
    }
    case GPUTextureMode::Palette8Bit:
    {
      const u16 packed = g_vram[((base_y + v) & VRAM_HEIGHT_MASK) * VRAM_WIDTH + ((base_x + (u >> 1)) & VRAM_WIDTH_MASK)];
      return g_gpu_clut[(packed >> ((u & 1u) * 8u)) & 0xffu];
    }
    case GPUTextureMode::Direct16Bit:
    case GPUTextureMode::Reserved_Direct16Bit:
    default:
      return g_vram[((base_y + v) & VRAM_HEIGHT_MASK) * VRAM_WIDTH + ((base_x + u) & VRAM_WIDTH_MASK)];
  }
}

/*
 * PS1 semi-transparency operates independently on each five-bit RGB channel:
 * floor((B+F)/2), saturated B+F, saturated B-F, or saturated B+floor(F/4).
 * Per-channel arithmetic avoids carries crossing RGB555 field boundaries.
 * Bit 15 is metadata rather than a color channel and follows the foreground.
 */
ALWAYS_INLINE u16 BlendPixel(u16 background, u16 foreground, GPUTransparencyMode mode)
{
  u32 result = foreground & 0x8000u;
  for (u32 shift = 0; shift <= 10; shift += 5)
  {
    const u32 b = (background >> shift) & 31u;
    const u32 f = (foreground >> shift) & 31u;
    u32 channel;
    switch (mode)
    {
      case GPUTransparencyMode::HalfBackgroundPlusHalfForeground: channel = (b + f) >> 1; break;
      case GPUTransparencyMode::BackgroundPlusForeground: channel = std::min(31u, b + f); break;
      case GPUTransparencyMode::BackgroundMinusForeground: channel = (b > f) ? (b - f) : 0u; break;
      case GPUTransparencyMode::BackgroundPlusQuarterForeground:
      default: channel = std::min(31u, b + (f >> 2)); break;
    }
    result |= channel << shift;
  }
  return static_cast<u16>(result);
}

template<bool Texture, bool RawTexture, bool Transparency, bool Dither>
/*
 * This is the common PS1 pixel pipeline, specialized by dispatch-table mode.
 * Its ordering is observable and must remain:
 *
 *   fetch/window/CLUT -> zero-texel discard -> raw copy or modulation ->
 *   optional blend -> destination-mask rejection -> forced-mask store.
 *
 * Modulated channels use P=floor((texel5 * vertex8)/16) before dithered
 * quantization. Raw textures preserve all 16 texel bits and ignore vertex
 * color/dithering. Textured transparency is conditional on texel bit 15;
 * untextured transparent primitives blend every covered pixel and clear bit
 * 15 before the optional forced mask. A resolved texel of exactly zero is
 * transparent and performs no destination access or mask write.
 *
 * The caller guarantees accepted X coordinates are valid VRAM columns. Y is
 * wrapped to 512 rows as required by the GPU addressing behavior.
 */
ALWAYS_INLINE void ShadePixel(const GPUBackendDrawCommand* cmd, s32 x, s32 y, u8 r, u8 g, u8 b, u8 u, u8 v)
{
  u16 foreground;
  if constexpr (Texture)
  {
    const u16 texel = FetchTexel(cmd, u, v);
    if (texel == 0)
      return;
    if constexpr (RawTexture)
      foreground = texel;
    else
    {
      const u32 tr = texel & 31u;
      const u32 tg = (texel >> 5) & 31u;
      const u32 tb = (texel >> 10) & 31u;
      foreground = static_cast<u16>(QuantizeChannel((tr * r) >> 4, x, y, Dither) |
                                    (QuantizeChannel((tg * g) >> 4, x, y, Dither) << 5) |
                                    (QuantizeChannel((tb * b) >> 4, x, y, Dither) << 10) | (texel & 0x8000u));
    }
  }
  else
  {
    foreground = static_cast<u16>(QuantizeChannel(r, x, y, Dither) | (QuantizeChannel(g, x, y, Dither) << 5) |
                                  (QuantizeChannel(b, x, y, Dither) << 10));
  }

  u16& destination = g_vram[(static_cast<u32>(y) & VRAM_HEIGHT_MASK) * VRAM_WIDTH + static_cast<u32>(x)];
  if constexpr (Transparency)
  {
    if constexpr (!Texture)
      foreground = static_cast<u16>(BlendPixel(destination, foreground, cmd->draw_mode.transparency_mode) & 0x7fffu);
    else if (foreground & 0x8000u)
      foreground = BlendPixel(destination, foreground, cmd->draw_mode.transparency_mode);
  }
  if (cmd->params.check_mask_before_draw && (destination & 0x8000u))
    return;
  destination = static_cast<u16>(foreground | (cmd->params.set_mask_while_drawing ? 0x8000u : 0u));
}

template<bool Texture, bool RawTexture, bool Transparency>
/*
 * Rectangles are half-open in local sprite space: [0,width) x [0,height),
 * then clipped against the inclusive drawing area. Texture U/V advance with
 * those unclipped local offsets and wrap at eight bits, so scissoring cannot
 * rebase the texture. Rectangles always use undithered quantization.
 *
 * The scalar implementation visits top-to-bottom and left-to-right. Earlier
 * writes are therefore visible to later texture and destination reads during
 * overlapping VRAM operations. Interlaced rendering suppresses candidate
 * rows matching the active display-field parity; interpolation/stepping still
 * follows original rectangle offsets.
 */
void DrawRectangle(const GPUBackendDrawRectangleCommand* cmd)
{
  const u8 initial_u = static_cast<u8>(cmd->texcoord);
  const u8 initial_v = static_cast<u8>(cmd->texcoord >> 8);
  const u8 r = static_cast<u8>(cmd->color), g = static_cast<u8>(cmd->color >> 8), b = static_cast<u8>(cmd->color >> 16);
  for (u32 dy = 0; dy < cmd->height; dy++)
  {
    const s64 y64 = static_cast<s64>(cmd->y) + dy;
    if (y64 < GPU_SW_Rasterizer::g_drawing_area.top || y64 > GPU_SW_Rasterizer::g_drawing_area.bottom ||
        (cmd->params.interlaced_rendering && ((static_cast<u32>(y64) & 1u) == cmd->params.active_line_lsb)))
      continue;
    for (u32 dx = 0; dx < cmd->width; dx++)
    {
      const s64 x64 = static_cast<s64>(cmd->x) + dx;
      if (x64 < GPU_SW_Rasterizer::g_drawing_area.left || x64 > GPU_SW_Rasterizer::g_drawing_area.right)
        continue;
      ShadePixel<Texture, RawTexture, Transparency, false>(cmd, static_cast<s32>(x64), static_cast<s32>(y64), r, g, b,
                                                           static_cast<u8>(initial_u + dx), static_cast<u8>(initial_v + dy));
    }
  }
}

template<bool Shading, bool Transparency, bool Dither>
/*
 * Lines reproduce the PS1's one-pixel DDA rather than an ideal geometric
 * segment. Primitives spanning 1024 X or 512 Y units are rejected. Endpoints
 * are normalized by X (with the second input first for a nonzero vertical
 * line), and K=max(|dx|,|dy|) produces exactly K+1 samples including both
 * endpoints. This normalization affects interpolation and coordinate bias.
 *
 * Coordinates are signed 32.32 fixed point, initialized at half a pixel. X
 * carries a -2^-22 bias; Y carries it only on a negative slope. The increment
 * is (delta*2^32 + sign(delta)*(K-1))/K with division toward zero. Unsigned
 * accumulators deliberately preserve two's-complement modulo-2^64 addition;
 * each emitted integer is then wrapped to the GPU's 11-bit coordinate domain.
 *
 * Gouraud colors use signed 20.12 fixed point with a half-fraction initial
 * bias and increments (C1-C0)*2^12/K truncated toward zero. Coordinate and
 * color state advance even when clipping or interlace parity suppresses a
 * sample. A zero-length line emits the first endpoint once.
 */
void DrawLine(const GPUBackendDrawLineCommand* cmd, const GPUBackendDrawLineCommand::Vertex* first,
              const GPUBackendDrawLineCommand::Vertex* second)
{
  const s64 raw_dx = static_cast<s64>(second->x) - first->x;
  const s64 raw_dy = static_cast<s64>(second->y) - first->y;
  const u32 dx = static_cast<u32>(std::abs(raw_dx)), dy = static_cast<u32>(std::abs(raw_dy));
  if (dx >= 1024 || dy >= 512)
    return;
  const u32 count = std::max(dx, dy);
  const auto* a = first;
  const auto* b = second;
  if (first->x > second->x || (first->x == second->x && count > 0))
    std::swap(a, b);

  const s64 delta_x = static_cast<s64>(b->x) - a->x;
  const s64 delta_y = static_cast<s64>(b->y) - a->y;
  auto increment = [count](s64 delta, u32 fraction_bits) -> s64 {
    if (count == 0)
      return 0;
    const s64 numerator = delta * (s64{1} << fraction_bits) + ((delta > 0) ? (count - 1) : (delta < 0 ? -static_cast<s64>(count - 1) : 0));
    return numerator / count;
  };
  u64 x = static_cast<u64>(static_cast<u32>(a->x)) << 32;
  u64 y = static_cast<u64>(static_cast<u32>(a->y)) << 32;
  x += (u64{1} << 31) - (u64{1} << 10);
  y += (u64{1} << 31) - ((delta_y < 0) ? (u64{1} << 10) : 0);
  const s64 x_step = increment(delta_x, 32), y_step = increment(delta_y, 32);
  s64 colors[3] = {(static_cast<s64>(a->r) << 12) + 2048, (static_cast<s64>(a->g) << 12) + 2048,
                   (static_cast<s64>(a->b) << 12) + 2048};
  const s64 color_steps[3] = {increment(static_cast<s64>(b->r) - a->r, 12),
                              increment(static_cast<s64>(b->g) - a->g, 12),
                              increment(static_cast<s64>(b->b) - a->b, 12)};
  for (u32 i = 0; i <= count; i++)
  {
    const u32 px = static_cast<u32>(x >> 32) & 2047u;
    const u32 py = static_cast<u32>(y >> 32) & 2047u;
    if (px >= GPU_SW_Rasterizer::g_drawing_area.left && px <= GPU_SW_Rasterizer::g_drawing_area.right &&
        py >= GPU_SW_Rasterizer::g_drawing_area.top && py <= GPU_SW_Rasterizer::g_drawing_area.bottom &&
        !(cmd->params.interlaced_rendering && ((py & 1u) == cmd->params.active_line_lsb)))
      ShadePixel<false, false, Transparency, Dither>(cmd, static_cast<s32>(px), static_cast<s32>(py),
                                                     static_cast<u8>(colors[0] >> 12), static_cast<u8>(colors[1] >> 12),
                                                     static_cast<u8>(colors[2] >> 12), 0, 0);
    x += static_cast<u64>(x_step);
    y += static_cast<u64>(y_step);
    if constexpr (Shading)
      for (u32 c = 0; c < 3; c++)
        colors[c] += color_steps[c];
  }
}

template<bool Shading, bool Texture, bool RawTexture, bool Transparency, bool Dither>
/*
 * Triangles use a scanline edge walker matching PS1 coverage rules. Vertices
 * are stably ordered by Y as top/middle/bottom, while the last input vertex at
 * the minimum X becomes the independent interpolation/traversal reference C.
 * Oversized, flat, or zero-determinant primitives are rejected, but winding
 * is not culled.
 *
 * Edge X values are signed 32.32 fixed point with a bias of 1-2^-21. Slopes
 * use (dx*2^32 + sign(dx)*(dy-1))/dy, truncated toward zero. Spans include the
 * integer left edge and exclude the right edge. This half-open ownership rule
 * is hardware-visible: two adjacent triangles sharing a quantized edge must
 * not both shade it. Span width is computed before the left endpoint is
 * reduced to the signed 11-bit GPU coordinate domain.
 *
 * Color and UV attributes are affine in screen space; the PS1 performs no
 * perspective correction. Determinant gradients retain two 12-bit stages to
 * form effective 8.24 fixed-point state. Signed gradient division truncates
 * toward zero, after which reference values, products, and sums intentionally
 * wrap modulo 2^32. Scissoring changes neither the source-space X used for
 * interpolation nor the attribute assigned to surviving pixels.
 *
 * Row order depends on C and is preserved even though a conventional ascending
 * scan would produce the same non-aliasing coverage: texture and destination
 * share VRAM, so writes from an earlier row may affect later fetches. Within a
 * row the scalar path always proceeds from the included left edge rightward.
 */
void DrawTriangle(const GPUBackendDrawPolygonCommand* cmd, const GPUBackendDrawPolygonCommand::Vertex* v0,
                  const GPUBackendDrawPolygonCommand::Vertex* v1, const GPUBackendDrawPolygonCommand::Vertex* v2)
{
  using Vertex = GPUBackendDrawPolygonCommand::Vertex;
  const Vertex* input[3] = {v0, v1, v2};
  for (u32 i = 0; i < 3; i++)
    for (u32 j = i + 1; j < 3; j++)
      if (std::abs(static_cast<s64>(input[i]->x) - input[j]->x) >= 1024)
        return;
  std::stable_sort(std::begin(input), std::end(input), [](const Vertex* a, const Vertex* b) { return a->y < b->y; });
  const Vertex *t = input[0], *m = input[1], *bottom = input[2];
  if (static_cast<s64>(bottom->y) - t->y >= 512 || t->y == bottom->y)
    return;
  const s64 area = (static_cast<s64>(m->x) - t->x) * (static_cast<s64>(bottom->y) - m->y) -
                   (static_cast<s64>(bottom->x) - m->x) * (static_cast<s64>(m->y) - t->y);
  if (area == 0)
    return;

  const Vertex* c = v0;
  for (const Vertex* candidate : {v1, v2})
    if (candidate->x <= c->x)
      c = candidate;

  auto edge_step = [](const Vertex* a, const Vertex* b) -> s64 {
    const s64 dx = static_cast<s64>(b->x) - a->x;
    const s64 dy = static_cast<s64>(b->y) - a->y;
    const s64 adjustment = (dx > 0) ? (dy - 1) : (dx < 0 ? -(dy - 1) : 0);
    return (dx * (s64{1} << 32) + adjustment) / dy;
  };
  const s64 long_step = edge_step(t, bottom);
  const bool flat_top = (t->y == m->y);
  const s64 upper_step = flat_top ? 0 : edge_step(t, m);
  const bool short_right = (flat_top && m->x > t->x) || (!flat_top && upper_step > long_step);
  auto edge_x = [](const Vertex* a, s64 step, s32 row) -> u64 {
    const u64 base = static_cast<u64>(static_cast<u32>(a->x)) << 32;
    return base + ((u64{1} << 32) - (u64{1} << 11)) +
           static_cast<u64>(static_cast<s64>(row - a->y) * step);
  };

  /*
   * The determinant formulation evaluates the same affine plane for R, G, B,
   * U, and V. Using C as the reference anchors constant-color selection and
   * preserves the GPU's wrapped arithmetic independently of vertex Y sorting.
   */
  struct Gradient { u32 x, y, reference; };
  auto gradient = [&](u8 Vertex::* member) -> Gradient {
    const s64 numerator_x = (static_cast<s64>(m->*member) - t->*member) * (static_cast<s64>(bottom->y) - m->y) -
                            (static_cast<s64>(bottom->*member) - m->*member) * (static_cast<s64>(m->y) - t->y);
    const s64 numerator_y = (static_cast<s64>(m->x) - t->x) * (static_cast<s64>(bottom->*member) - m->*member) -
                            (static_cast<s64>(bottom->x) - m->x) * (static_cast<s64>(m->*member) - t->*member);
    return {static_cast<u32>((numerator_x * 4096) / area) << 12,
            static_cast<u32>((numerator_y * 4096) / area) << 12,
            (static_cast<u32>(c->*member) * 4096u + 2048u) << 12};
  };
  const Gradient gradients[5] = {gradient(&Vertex::r), gradient(&Vertex::g), gradient(&Vertex::b),
                                 gradient(&Vertex::u), gradient(&Vertex::v)};

  /*
   * Drawing-area right is inclusive externally but becomes an exclusive span
   * limit after clipping. Interlaced mode discards an entire row whose low bit
   * equals the active field; accepted rows wrap to the 512-line VRAM address.
   */
  auto draw_row = [&](s32 row) {
    if (row < static_cast<s32>(GPU_SW_Rasterizer::g_drawing_area.top) ||
        row > static_cast<s32>(GPU_SW_Rasterizer::g_drawing_area.bottom) ||
        (cmd->params.interlaced_rendering && ((static_cast<u32>(row) & 1u) == cmd->params.active_line_lsb)))
      return;
    const bool upper = row < m->y;
    const Vertex* short_start = upper ? t : m;
    const s64 short_step = upper ? upper_step : edge_step(m, bottom);
    const u64 lx_fixed = short_right ? edge_x(t, long_step, row) : edge_x(short_start, short_step, row);
    const u64 rx_fixed = short_right ? edge_x(short_start, short_step, row) : edge_x(t, long_step, row);
    const s32 left = static_cast<s32>(lx_fixed >> 32);
    const s32 right = static_cast<s32>(rx_fixed >> 32);
    const s64 width = static_cast<s64>(right) - left;
    if (width <= 0)
      return;
    const s32 destination_start = SignExtendN<11, s32>(left);
    for (s64 offset = 0; offset < width; offset++)
    {
      const s32 destination_x = destination_start + static_cast<s32>(offset);
      if (destination_x < static_cast<s32>(GPU_SW_Rasterizer::g_drawing_area.left) ||
          destination_x > static_cast<s32>(GPU_SW_Rasterizer::g_drawing_area.right))
        continue;
      const s32 sx = left + static_cast<s32>(offset);
      const u32 sy = static_cast<u32>(row) & VRAM_HEIGHT_MASK;
      u8 attributes[5];
      for (u32 a = 0; a < 5; a++)
      {
        const u32 value = gradients[a].reference + gradients[a].x * static_cast<u32>(sx - c->x) +
                          gradients[a].y * static_cast<u32>(sy - c->y);
        attributes[a] = static_cast<u8>(value >> 24);
      }
      ShadePixel<Texture, RawTexture, Transparency, Dither>(cmd, destination_x, static_cast<s32>(sy),
                                                            Shading ? attributes[0] : c->r,
                                                            Shading ? attributes[1] : c->g,
                                                            Shading ? attributes[2] : c->b, attributes[3], attributes[4]);
    }
  };

  auto visit_up = [&](s32 begin, s32 end) { for (s32 y = begin; y < end; y++) draw_row(y); };
  auto visit_down = [&](s32 begin, s32 end) { for (s32 y = begin; y >= end; y--) draw_row(y); };
  if (c == t)
  {
    visit_up(t->y, m->y);
    visit_up(m->y, bottom->y);
  }
  else if (c == m)
  {
    visit_up(m->y, bottom->y);
    visit_down(m->y - 1, t->y);
  }
  else
  {
    visit_down(bottom->y - 1, m->y);
    visit_down(m->y - 1, t->y);
  }
}

} // namespace

/*
 * Table construction encodes semantically inactive modes as pointer aliases:
 * rectangles ignore raw mode when untextured; raw triangles ignore dithering;
 * and an untextured/raw request resolves to the corresponding undithered
 * non-raw path. These aliases are part of the public dispatch contract.
 */
#define RECT(tex, raw) {DrawRectangle<tex, raw, false>, DrawRectangle<tex, raw, true>}
DrawRectangleFunctionTable DrawRectangleFunctions = {{RECT(false, false), RECT(false, false)},
                                                      {RECT(true, false), RECT(true, true)}};
#undef RECT

#define TRI(shade, tex, raw, trans, dither) DrawTriangle<shade, tex, raw, trans, dither>
#define TRI_TRANS(shade, tex, raw, d0, d1) {{TRI(shade, tex, raw, false, d0), TRI(shade, tex, raw, false, d1)}, \
                                            {TRI(shade, tex, raw, true, d0), TRI(shade, tex, raw, true, d1)}}
DrawTriangleFunctionTable DrawTriangleFunctions = {
  {{TRI_TRANS(false, false, false, false, true), TRI_TRANS(false, false, false, false, false)},
   {TRI_TRANS(false, true, false, false, true), TRI_TRANS(false, true, true, false, false)}},
  {{TRI_TRANS(true, false, false, false, true), TRI_TRANS(true, false, false, false, false)},
   {TRI_TRANS(true, true, false, false, true), TRI_TRANS(true, true, true, false, false)}}};
#undef TRI_TRANS
#undef TRI

#define LINE(shade, trans) {DrawLine<shade, trans, false>, DrawLine<shade, trans, true>}
DrawLineFunctionTable DrawLineFunctions = {{LINE(false, false), LINE(false, true)},
                                            {LINE(true, false), LINE(true, true)}};
#undef LINE
