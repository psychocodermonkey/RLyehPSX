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

#include "gpu_sw_rasterizer.h"

#include "common/intrin.h"
#include "common/log.h"
#include "common/string_util.h"

#include <algorithm>
#include <cstdlib>

#if defined(CPU_ARCH_SSE) && defined(_MSC_VER)
#include <cpuinfo.h>
#endif

Log_SetChannel(GPU_SW_Rasterizer);

namespace GPU_SW_Rasterizer {
namespace {
/*
 * PS1 dithering adds the signed matrix entry before reducing an intermediate
 * channel to RGB555. For V in [0,511], the hardware-compatible result is
 * clamp(floor((V + D[y&3][x&3]) / 8), 0, 31). C++ signed division truncates
 * toward zero, so the negative branch explicitly implements arithmetic-shift
 * (floor) semantics instead of relying on implementation-defined shifts.
 */
constexpr u8 MakeDitherValue(u32 y, u32 x, u32 value)
{
  const s32 adjusted = static_cast<s32>(value) + DITHER_MATRIX[y][x];
  const s32 divided = (adjusted >= 0) ? (adjusted / 8) : -static_cast<s32>((-adjusted + 7) / 8);
  return static_cast<u8>(std::clamp(divided, 0, 31));
}

} // namespace

/*
 * Constant initialization is required because dispatch and drawing state may
 * be observed during other translation units' dynamic initialization. The
 * table also serves as the public, inspectable definition of the PS1 dither
 * rule rather than merely an optimization of QuantizeChannel().
 */
const DitherLUT g_dither_lut = []() constexpr {
  DitherLUT lut{};
  for (u32 y = 0; y < 4; y++)
    for (u32 x = 0; x < 4; x++)
      for (u32 value = 0; value < DITHER_LUT_SIZE; value++)
        lut[y][x][value] = MakeDitherValue(y, x, value);
  return lut;
}();

GPUDrawingArea g_drawing_area{};

/*
 * The implementation body is included inside this namespace so the same
 * scalar templates can instantiate the default tables and, where required by
 * the build, architecture-specific table namespaces. gpu.h is therefore
 * included by the public header at global scope; including it from the .inl
 * would incorrectly redeclare the emulator-owned VRAM and CLUT in this
 * namespace.
 */
#include "gpu_sw_rasterizer.inl"

/*
 * Selection begins at the universally compatible tables. The pointers are
 * mutable for process-lifetime ISA selection, while table objects and entry
 * addresses remain stable for callers that cache a selected function.
 */
DrawRectangleFunctionTable* SelectedDrawRectangleFunctions = &DrawRectangleFunctions;
DrawTriangleFunctionTable* SelectedDrawTriangleFunctions = &DrawTriangleFunctions;
DrawLineFunctionTable* SelectedDrawLineFunctions = &DrawLineFunctions;

void SelectImplementation()
{
  /*
   * Backend initialization is single-threaded by contract. This lightweight
   * guard intentionally provides call-once behavior without introducing a
   * synchronization primitive into rasterizer startup. The environment is
   * consequently sampled once and subsequent calls neither select nor log.
   */
  static bool called = false;
  if (called)
    return;
  called = true;

  const char* request = std::getenv("SW_USE_ISA");
  request = request ? request : "Scalar";
  const char* selected_name = "scalar";

#if defined(CPU_ARCH_SSE) && defined(_MSC_VER)
  if (StringUtil::Strcasecmp(request, "AVX2") == 0 && cpuinfo_initialize() && cpuinfo_has_x86_avx2())
  {
    SelectedDrawRectangleFunctions = &AVX2::DrawRectangleFunctions;
    SelectedDrawTriangleFunctions = &AVX2::DrawTriangleFunctions;
    SelectedDrawLineFunctions = &AVX2::DrawLineFunctions;
    selected_name = "AVX2";
  }
  else
#endif
  INFO_LOG("Using {} software rasterizer implementation.", selected_name);
}

} // namespace GPU_SW_Rasterizer
