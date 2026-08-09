# R'Lyeh PSX

<p align="center">
  <img
    src="data/resources/images/vaulketh.png"
    alt="Vaul'keth"
    width="300"
  />
</p>

An experimental PlayStation (PS1) emulator project derived from the GPL-licensed [DuckStation-GPL](https://github.com/Trixarian/duckstation-gpl) codebase.

## Project Status

**Early Development - macOS build succeeds - Other platforms are not yet validated.**

R'Lyeh PSX is an independent fork intended for long-term experimentation, maintenance, and feature development. The project is still undergoing dependency modernization, library migration, and validation work, but the macOS build path has been brought to a successful build state.

### Recent development highlights

#### Completed build-system and dependency work

- Established modern macOS/Xcode build support, local dependency retrieval, and deployment-target guidance.
- Upgraded ImGui from 1.91.0 to 1.92.7 and updated the texture and UI integration for the newer API.
- Replaced LunaSVG with PlutoSVG 0.0.8 and added PlutoVG 1.3.3 as its dependency.
- Upgraded {fmt} from 10.1.1 to 12.2.0 and applied required compiler compatibility fixes.
- Updated Cubeb from current upstream while preserving project-specific behavior.
- Added macOS and Linux CMake presets.
- Updated the Qt 6.7.2 dependency build for Apple Clang 21.
- Established working Linux dependency builds and recorded dependency provenance with pinned source revisions where releases are unavailable.
- Vendored upstream SoundTouch and removed the separate macOS and Linux SoundTouch dependency builds.
- Migrated CPUInfo from the Stenzek fork to upstream PyTorch CPUInfo on macOS and Linux.
- Migrated Shaderc from the Stenzek fork to upstream 2026.3, including its CMake integration and runtime API updates.
- Updated macOS and Linux FFmpeg dependencies and vendored FFmpeg headers to 7.1.5.
- Removed the deprecated Discord RPC integration, dependency builds, and deployment references.

#### Replacing restricted components

- Audio-stream subsystem rewrite.
- Software rasterizer rewrite.
- Replaced components with licensing constraints to simplify long-term maintenance and project ownership.

Expect incomplete functionality, regressions, unfinished features, and build failures on unvalidated platforms.

## About

R'Lyeh PSX began as a fork of the GPL-licensed DuckStation-GPL project.

The original DuckStation and DuckStation-GPL contributors deserve full credit for the architecture, design, and implementation of the emulator that serves as the foundation for this repository. The overwhelming majority of the current codebase originated from their work.

This repository exists to support independent experimentation, maintenance, and future development under the R'Lyeh PSX project.

## Relationship to Upstream Projects

R'Lyeh PSX is:

- Derived from the DuckStation-GPL codebase.
- Licensed in accordance with the GPL requirements of the upstream project.
- An independent project.

R'Lyeh PSX is not:

- The official DuckStation project.
- Endorsed by the DuckStation developers.
- Supported by the DuckStation developers.
- Maintained by the DuckStation developers.
- Affiliated with the DuckStation project beyond its GPL heritage.

Questions, bugs, regressions, broken builds, and questionable engineering decisions introduced by this repository belong to R'Lyeh PSX, not upstream.

## Current Goals

Current areas of investigation include:

- Continued modernization of third-party dependencies.
- Dear ImGui compatibility updates.
- Build system improvements.
- Enhanced game library management.
- Multi-disc and M3U workflow improvements.
- Future Android support research.
- Long-term maintainability improvements.

## Building

At the time of writing, the macOS build path is the only validated build path.

Other platform build instructions and support documentation will be updated as the project stabilizes.

### macOS build notes

These steps go from a fresh clone to a runnable macOS app bundle. The app is currently unsigned, so ad hoc signing is needed before macOS will launch it locally.

Prerequisites: `git`, `curl`, CMake 3.21 or newer, `ninja`, Xcode command line tools, and a macOS shell with `codesign`, `lipo`, and `shasum` available.

#### Clone the repo

``` sh
git clone git@github.com:psychocodermonkey/RlyehPSX.git
```

#### Build and install dependencies

This script downloads, verifies, builds, and installs the dependency set into `deps/`. It also sets `MACOSX_DEPLOYMENT_TARGET=11.0` internally.

``` sh
cd RlyehPSX
```

Run the dependencies build script.

``` sh
./scripts/deps/build-dependencies-mac.sh deps
```

#### Configure and build the app

Configure the Debug build. The preset sets the generator, dependency path, build type, and deployment target.

``` sh
cmake --preset debug-mac
```

Build and ad-hoc sign the package. These steps are necessary to rebuild and launch the package on macOS. The `--deep` flag ensures that all embedded resources are also signed.

``` sh
cmake --build --preset debug-mac
```

Sign the package to allow running on MacOS.

``` sh
codesign --force --deep --sign - build/debug-mac/bin/DuckStation.app
```

The resulting app bundle is written to `build/debug-mac/bin/DuckStation.app`. Use `release-mac` in place of `debug-mac` for a Release build.

## Licensing

R'Lyeh PSX incorporates code derived from GPL-licensed projects and remains subject to the terms of those licenses.

See the repository license files and third-party notices for complete licensing information. Their contributor lists, licenses, copyright notices, and attribution files belong to those projects and should be preserved in place.

## Disclaimer

This repository is currently a development and learning project.

If you are looking for a stable, production-ready PlayStation emulator, this is not it.

At least not yet.

"PlayStation" and "PSX" are registered trademarks of Sony Interactive Entertainment. This project is not affiliated in any way with Sony Interactive Entertainment.

## AI Usage

AI tools are used in this project as development support for understanding the codebase, tracking build nuances, reviewing changes, investigating issues, and improving documentation.

AI-generated output is not treated as authoritative. Contributions are expected to be reviewed, tested, and understood by the person submitting them. AI may be used by contributors, but it must be used as tooling, not as a substitute for engineering judgment.

This project allows AI-assisted work. It does not accept unchecked AI-generated code, broad automated rewrites, or changes that the contributor cannot explain and maintain.
