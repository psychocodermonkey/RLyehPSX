# Vendored Dependencies

This document records the third-party source currently vendored under `dep/`.
It is intended to make future compatibility audits and dependency updates
traceable.

Versions marked **unrecorded snapshot** have no authoritative release or
version marker in the vendored source. Before updating one of these, identify
and record the upstream commit used as the baseline.

| Dependency             | Vendored version                 | Upstream                                                                                  |
|------------------------|---------------------------------:|-------------------------------------------------------------------------------------------|
| biscuit                | 0.9.1                            | [lioncash/biscuit](https://github.com/lioncash/biscuit)                                   |
| cubeb                  | Upstream `19fcbef` plus patches  | [mozilla/cubeb](https://github.com/mozilla/cubeb)                                         |
| D3D12 Memory Allocator | 2.1.0-development (2023-07-05)   | [GPUOpen D3D12MA](https://github.com/GPUOpen-LibrariesAndSDKs/D3D12MemoryAllocator)       |
| fast_float             | Unrecorded snapshot              | [fastfloat/fast_float](https://github.com/fastfloat/fast_float)                           |
| FFmpeg                 | 7.0.2                            | [FFmpeg/FFmpeg](https://github.com/FFmpeg/FFmpeg)                                         |
| fmt                    | 12.2.0                           | [fmtlib/fmt](https://github.com/fmtlib/fmt)                                               |
| glad                   | Generator 2.0.5                  | [Dav1dde/glad](https://github.com/Dav1dde/glad)                                           |
| GoogleTest             | Unrecorded snapshot              | [google/googletest](https://github.com/google/googletest)                                 |
| Dear ImGui             | 1.92.7                           | [ocornut/imgui](https://github.com/ocornut/imgui)                                         |
| KissFFT                | Unrecorded snapshot              | [mborgerding/kissfft](https://github.com/mborgerding/kissfft)                             |
| libchdr                | Unrecorded snapshot              | [rtissera/libchdr](https://github.com/rtissera/libchdr)                                   |
| LZMA SDK               | 9.35                             | [Igor Pavlov's 7-Zip](https://github.com/ip7z/7zip)                                       |
| MiniZip                | 1.1 (2010)                       | Maintained fork of: [nmoinvaz/minizip](https://github.com/nmoinvaz/minizip)               |
| RAInterface            | Unrecorded snapshot              | [RetroAchievements/RAIntegration](https://github.com/RetroAchievements/RAIntegration)     |
| rapidyaml              | Unrecorded snapshot              | [biojppm/rapidyaml](https://github.com/biojppm/rapidyaml)                                 |
| rcheevos               | 11.5                             | [RetroAchievements/rcheevos](https://github.com/RetroAchievements/rcheevos)               |
| ReShade FX             | Unrecorded snapshot              | [crosire/reshade](https://github.com/crosire/reshade)                                     |
| RISC-V disassembler    | Unrecorded snapshot              | [michaeljclark/riscv-disassembler](https://github.com/michaeljclark/riscv-disassembler)   |
| SimpleIni              | 4.22                             | [brofield/simpleini](https://github.com/brofield/simpleini)                               |
| VIXL                   | Unrecorded snapshot              | [Linaro/vixl](https://github.com/Linaro/vixl)                                             |
| Vulkan-Headers         | 1.3.279                          | [KhronosGroup/Vulkan-Headers](https://github.com/KhronosGroup/Vulkan-Headers)             |
| WinPixEventRuntime     | Unrecorded binary/header package | [Microsoft/PixEvents](https://github.com/microsoft/PixEvents)                             |
| Xbyak                  | 6.73.0                           | [herumi/xbyak](https://github.com/herumi/xbyak)                                           |
| xxHash                 | 0.8.0                            | [Cyan4973/xxHash](https://github.com/Cyan4973/xxHash)                                     |
| Zydis                  | 4.0.0                            | [zyantific/zydis](https://github.com/zyantific/zydis)                                     |

## Notes

- `dep/msvc` contains project Visual Studio build-property files and is not a
  third-party dependency.
- Zydis vendors Zycore-C as a nested dependency.
- libchdr vendors codec code, including dr_flac 0.12.42, as nested
  dependencies.

## DuckStation `dep/` Comparison

Comparison performed on 2026-07-12 against the local DuckStation checkout at
`ad7519d72c935b57b6a6e1c17f5fcba3c15783ff` (2026-07-11). The checkout must be
fetched before treating it as a comparison with the current online DuckStation
repository.

DuckStation is a useful maintenance reference for dependency versions and
integration impact. Dependency source should be obtained directly from the
dependency's upstream project; DuckStation-specific build and wrapper changes
must be independently assessed and reimplemented where appropriate.

### Directory Inventory

The following top-level directories exist only in R'Lyeh PSX:

- `kissfft`
- `msvc` (project build-property files, not a third-party dependency)
- `rainterface`
- `simpleini`

The following top-level directories exist only in the compared DuckStation
checkout:

- `lagoon`
- `prebuilt`
- `vsprops`

The shared dependency directories with identical contents are `biscuit`,
`fast_float`, `riscv-disas`, `winpixeventruntime`, and `xbyak`.

For `d3d12ma`, `glad`, `minizip`, `vixl`, and `zydis`, the source is identical;
only Visual Studio project files differ. `xxhash` also has identical source,
with differences limited to its license copy and Visual Studio project file.

### Known Version Differences

| Dependency       | R'Lyeh PSX | DuckStation   | Interpretation                                                    |
|------------------|-----------:|---------------|-------------------------------------------------------------------|
| FFmpeg           | 7.0.2      | 8.1           | DuckStation provides a potential upgrade reference.               |
| fmt              | 12.2.0     | 12.1.0        | R'Lyeh PSX is intentionally newer.                                |
| rcheevos         | 11.5.0     | 12.3.0        | DuckStation provides a potential upgrade reference.               |
| Vulkan-Headers   | 1.3.279    | 1.4.337       | DuckStation provides a potential upgrade reference.               |
| Dear ImGui       | 1.92.7     | 1.92.7 WIP    | Do not infer update direction from this label alone.              |
|                  |            |               |   R'Lyeh PSX intentionally retains its newer completed            |
|                  |            |               |   integration; the DuckStation tree is an in-progress snapshot.   |
| LZMA SDK         | 9.35       | 9.35          | Same recorded version, despite source-tree differences.           |

`googletest`, `libchdr`, `rapidyaml`, and `reshadefx` have meaningful
source-tree differences but lack an authoritative embedded version marker.
They require upstream commit/tag identification before this comparison can
establish which side is newer.

### Cubeb Provenance

R'Lyeh PSX's `dep/cubeb` is byte-for-byte identical to the final Cubeb tree in
the full GPL-era DuckStation history used for this audit. It is not an unknown
R'Lyeh-local modification.

The previous vendored tree was established by these DuckStation commits:

| DuckStation commit | Date | Purpose |
|---|---|---|
| `872cee908c99e72f7738c16641a1021445616ecf` | 2024-05-12 | Synced Cubeb to upstream commit `19fcbef`; also applied upstream PR #740 to re-enable and polish `IAudioClient3` for lower WASAPI latency, including a stream-frame latency reporting correction. |
| `eab4271bf72280db0606da648fcd485a032e6bef` | 2024-05-12 | DuckStation follow-up: enumerate only connected WASAPI devices (`dep/cubeb/src/cubeb_wasapi.cpp`). |

### Cubeb Update and Validation

Cubeb was updated from upstream commit
`6d5e5e6470aa0836139a1feb79793a33db227d3e` (2026-07-06). The vendored copy
retains the DuckStation active-WASAPI-device enumeration behavior from
`eab4271bf72280db0606da648fcd485a032e6bef`.

The production vendor copy omits Cubeb's repository metadata, tests, tools,
documentation, formatting scripts, and sanitizer support. Its CMake build was
adjusted accordingly, while retaining runtime backends and platform detection.

The `cubeb_get_backend_names()` API changed from a null-terminated string array
to a `cubeb_backend_names` struct. R'Lyeh PSX's audio wrapper was updated to
iterate the returned `names` array by its `count` field.

Validation completed on macOS with Apple Clang 21:

- Full R'Lyeh PSX Debug build completed successfully.
- Cubeb initialized, produced audio, remained selectable alongside the SDL
  fallback, and populated the driver and output-device settings controls.
- *Castlevania: Symphony of the Night* was used to verify normal emulated music
  and sound-effect mixing under a render-heavy game workload.
- *Descent* was used to verify CD-DA music playback alongside emulated sound
  effects under a distinct render-heavy workload.

These games were selected because their expected visual and audio behavior is
well known to the project maintainer.

### Intentional R'Lyeh PSX Divergences

- The `{fmt}` 12.2.0 update is retained for Apple Clang 21 compatibility.
- Dear ImGui is intentionally ahead of the compared DuckStation integration.
- The PlutoSVG migration replacing LunaSVG is a project integration change and
  is not represented by a top-level `dep/` directory difference.

### Upgrade and Validation Boundaries

Cubeb, FFmpeg, and libchdr can be upgraded and validated through local build
and emulator regression testing without waiting for external branding work.
Rcheevos can be compiled and tested locally, but its end-to-end RetroAchievements
API validation should wait until R'Lyeh PSX reports its final product identity.

## Maintenance Priority

The unrecorded snapshots—especially fast_float, GoogleTest, rapidyaml, and
VIXL—should be considered the first candidates for provenance work. Pinning
each to an upstream release or commit will make future compiler-compatibility
updates repeatable. Cubeb provenance has been recovered and is documented
above; it should be updated only when a concrete compatibility, security, or
audio-behavior reason justifies the integration risk.
