// SPDX-FileCopyrightText: 2026 Andrew Dixon <andrew.dixon@rlyeh.dev>
// SPDX-License-Identifier: GPL-3.0-only
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

#pragma once

#include "gpu.h"

#include <array>

namespace GPU_SW_Rasterizer {

/*
 * The PS1 reduces 8-bit vertex colors, and modulated texture products up to
 * 494, to five-bit VRAM channels through a screen-position-dependent 4x4
 * dither matrix. Keeping every possible 0..511 input materialized makes the
 * signed rounding and saturation rule shared, immutable rasterizer state.
 */
inline constexpr u32 DITHER_LUT_SIZE = 512;
using DitherLUT = std::array<std::array<std::array<u8, DITHER_LUT_SIZE>, 4>, 4>;

extern const DitherLUT g_dither_lut;

/*
 * PS1 drawing-area bounds are inclusive on all four sides. The command
 * processor is responsible for copying GP0 drawing-area state here before a
 * draw; rasterizer entry points consume it without validation or clamping.
 */
extern GPUDrawingArea g_drawing_area;

/*
 * These tables expose one specialized entry point for each effective command
 * mode. Their index order is part of the backend contract:
 *
 *   rectangle: texture, raw texture, semi-transparency
 *   triangle:  Gouraud, texture, raw texture, semi-transparency, dithering
 *   line:      Gouraud, semi-transparency, dithering
 *
 * Compile-time specialization keeps mode checks out of the per-pixel path.
 * Raw-texture indices are intentionally aliased where their meaning is
 * suppressed by the PS1 command mode.
 */
using DrawRectangleFunction = void (*)(const GPUBackendDrawRectangleCommand*);
using DrawRectangleFunctionTable = const DrawRectangleFunction[2][2][2];

using DrawTriangleFunction = void (*)(const GPUBackendDrawPolygonCommand*, const GPUBackendDrawPolygonCommand::Vertex*,
                                      const GPUBackendDrawPolygonCommand::Vertex*,
                                      const GPUBackendDrawPolygonCommand::Vertex*);
using DrawTriangleFunctionTable = const DrawTriangleFunction[2][2][2][2][2];

using DrawLineFunction = void (*)(const GPUBackendDrawLineCommand*, const GPUBackendDrawLineCommand::Vertex*,
                                  const GPUBackendDrawLineCommand::Vertex*);
using DrawLineFunctionTable = const DrawLineFunction[2][2][2];

extern DrawRectangleFunctionTable DrawRectangleFunctions;
extern DrawTriangleFunctionTable DrawTriangleFunctions;
extern DrawLineFunctionTable DrawLineFunctions;

extern DrawRectangleFunctionTable* SelectedDrawRectangleFunctions;
extern DrawTriangleFunctionTable* SelectedDrawTriangleFunctions;
extern DrawLineFunctionTable* SelectedDrawLineFunctions;

/*
 * The backend has already decoded GPU command flags when it calls these
 * accessors. Boolean-to-index conversion is deliberately direct: changing
 * index meaning here would silently select a different hardware pixel path.
 */
ALWAYS_INLINE static DrawLineFunction GetDrawLineFunction(bool shading_enable, bool transparency_enable,
                                                           bool dithering_enable)
{
  return (*SelectedDrawLineFunctions)[shading_enable][transparency_enable][dithering_enable];
}

ALWAYS_INLINE static DrawRectangleFunction GetDrawRectangleFunction(bool texture_enable, bool raw_texture_enable,
                                                                     bool transparency_enable)
{
  return (*SelectedDrawRectangleFunctions)[texture_enable][raw_texture_enable][transparency_enable];
}

ALWAYS_INLINE static DrawTriangleFunction GetDrawTriangleFunction(bool shading_enable, bool texture_enable,
                                                                   bool raw_texture_enable, bool transparency_enable,
                                                                   bool dithering_enable)
{
  return (*SelectedDrawTriangleFunctions)[shading_enable][texture_enable][raw_texture_enable][transparency_enable]
                                         [dithering_enable];
}

void SelectImplementation();

} // namespace GPU_SW_Rasterizer

#if defined(CPU_ARCH_SSE) && defined(_MSC_VER)
/*
 * Microsoft x86 builds may link a separately compiled AVX2 instantiation of
 * the same table interface. The declaration facility remains available after
 * this header so build-specific translation units can share the ABI without
 * exposing private rasterization helpers.
 */
#define ALTERNATIVE_RASTERIZER_LIST()                                                                                  \
  namespace GPU_SW_Rasterizer::AVX2 {                                                                                  \
  extern DrawRectangleFunctionTable DrawRectangleFunctions;                                                           \
  extern DrawTriangleFunctionTable DrawTriangleFunctions;                                                             \
  extern DrawLineFunctionTable DrawLineFunctions;                                                                     \
  }
#else
#define ALTERNATIVE_RASTERIZER_LIST()
#endif

ALTERNATIVE_RASTERIZER_LIST()
