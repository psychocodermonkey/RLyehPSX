# Build on macOS

These steps build R'Lyeh PSX from source and create a locally runnable app bundle.

## Build environment

Install Git, curl, CMake 3.21 or newer, Ninja, and the Xcode command line tools. The dependency script also uses macOS tools including `lipo` and `shasum`; `codesign` is needed after the application build.

This section can be extended with tested Xcode and macOS versions and any host package requirements as they are verified.

## Clone the repository

```sh
git clone https://github.com/psychocodermonkey/RlyehPSX.git
```

This creates a local `RlyehPSX` directory. Enter it before running the remaining commands:

```sh
cd RlyehPSX
```

## Build dependencies

```sh
./scripts/deps/build-dependencies-mac.sh deps
```

The script downloads and verifies third-party sources, then builds and installs them into the local `deps/` directory. It sets `MACOSX_DEPLOYMENT_TARGET=11.0` for those dependency builds.

## Configure the app

```sh
cmake --preset debug-mac
```

This reads the `debug-mac` **configure preset** and generates a Debug build in `build/debug-mac/`.

## Build the app

```sh
cmake --build --preset debug-mac
```

This reads the `debug-mac` **build preset** and compiles the configured project. The app bundle is written to `build/debug-mac/bin/RLyehPSX.app`.

## Sign and launch

```sh
codesign --force --deep --sign - build/debug-mac/bin/RLyehPSX.app
```

This applies an ad hoc signature to the bundle and its nested content so the locally built app can launch. Open `build/debug-mac/bin/RLyehPSX.app` after signing.

## How the presets work

See [CMake presets](cmake_presets.md) for the shared preset definitions, inheritance, and maintenance guidance.

## Release build

After building the dependencies, configure the Release preset:

```sh
cmake --preset release-mac
```

Build the configured Release app:

```sh
cmake --build --preset release-mac
```

Ad hoc sign the resulting `build/release-mac/bin/RLyehPSX.app` bundle before launching it:

```sh
codesign --force --deep --sign - build/release-mac/bin/RLyehPSX.app
```

[Back to building](index.md)
