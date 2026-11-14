# CMake presets

The repository's [CMakePresets.json](../../../CMakePresets.json) defines the supported CMake configure and build presets. It uses preset file format version 3. The top-level [CMakeLists.txt](../../../CMakeLists.txt) requires CMake 3.21 or newer.

This page explains the presets themselves. Follow the [macOS](macos.md) or [Linux](linux.md) build guide for dependency setup and platform build steps.

## Existing presets

`configurePresets` holds the settings CMake uses to generate a build tree. `buildPresets` tells `cmake --build` which configured tree to compile. Each public build preset points to a configure preset with the same name; the two entries are separate and both are needed for the paired commands below.

| Configure preset | Build preset | Host | Build tree | Build type |
| --- | --- | --- | --- | --- |
| `debug-mac` | `debug-mac` | macOS | `build/debug-mac/` | Debug |
| `release-mac` | `release-mac` | macOS | `build/release-mac/` | Release |
| `debug-linux` | `debug-linux` | Linux | `build/debug-linux/` | Debug |
| `release-linux` | `release-linux` | Linux | `build/release-linux/` | Release |

The configure presets inherit settings in layers:

- Hidden `base` selects the Ninja generator, sets the build directory to `${sourceDir}/build/${presetName}`, and sets `CMAKE_PREFIX_PATH` to `${sourceDir}/deps`. `${sourceDir}` is the repository root; `${presetName}` is the selected preset's name.
- Hidden `base-mac` inherits `base`, limits its children to a Darwin host, and sets `MACOSX_DEPLOYMENT_TARGET=11.0` in the configure environment.
- Hidden `base-linux` inherits `base`, limits its children to a Linux host, and sets `CMAKE_TOOLCHAIN_FILE` to [scripts/clang-toolchain.cmake](../../../scripts/clang-toolchain.cmake). That file selects the system `clang` and `clang++` compilers.
- Each public `debug-*` or `release-*` configure preset inherits its platform base and sets `CMAKE_BUILD_TYPE`.

Each public build preset names its matching `configurePreset` and has a host condition. The hidden bases provide shared settings; they are not build configurations to invoke directly. There is no Windows preset at present.

## Use a preset

From the repository root, after building the platform dependencies into `deps/`, configure a build tree:

```sh
cmake --preset debug-mac
```

Then build that configured tree:

```sh
cmake --build --preset debug-mac
```

On Linux, use `debug-linux`; replace `debug` with `release` for a Release build. Run the configure command before the corresponding build command. Preset names are host-limited, so macOS presets appear on macOS and Linux presets appear on Linux.

To inspect the presets available on the current host without configuring or building, run `cmake --list-presets` for configure presets and `cmake --list-presets=build` for build presets.

## Add a preset

Use an existing preset for the same host as a model. For example, a new `relwithdebinfo-linux` configuration would need:

1. A `configurePresets` entry named `relwithdebinfo-linux` that inherits `base-linux` and sets `CMAKE_BUILD_TYPE` to `RelWithDebInfo`. It will get `build/relwithdebinfo-linux/` from `base`.
2. A `buildPresets` entry named `relwithdebinfo-linux` whose `configurePreset` is `relwithdebinfo-linux`, with the same Linux host condition used by the existing Linux build presets.
3. A check that the new name appears in the configure and build preset lists on Linux, followed by configure and build validation for that configuration.

Keep settings at the narrowest level that applies to all affected presets: shared generator and dependency prefix in `base`, host requirements in the platform base, and configuration choices in the public leaf. A new platform also needs a working toolchain and dependency build path before its presets can be treated as supported; the [Windows migration inventory](windows_build_documentation.md) is reference material, not a Windows build preset.

## Maintain presets as requirements change

- Update [CMakePresets.json](../../../CMakePresets.json) when the generator, build tree layout, dependency prefix, host condition, toolchain path, deployment target, or build configuration changes. Review every preset that inherits the changed entry.
- Keep the macOS deployment target aligned with [build-dependencies-mac.sh](../../../scripts/deps/build-dependencies-mac.sh), which sets the target separately for dependency builds.
- Keep the Linux toolchain selection aligned with [build-dependencies-linux.sh](../../../scripts/deps/build-dependencies-linux.sh), which uses the system Clang for dependencies. Compiler or dependency ABI changes may require a fresh dependency tree as well as a fresh application build tree.
- Re-run the affected configure preset after changing preset settings, then validate its matching build preset. When changing the generator or compiler, use a fresh build directory rather than reusing a CMake cache configured for the old choice.
- Keep the platform guides and this page in sync when preset names, output paths, or supported hosts change.

[Back to building](index.md)
