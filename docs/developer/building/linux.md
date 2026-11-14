# Build on Linux

These steps build R'Lyeh PSX from source.

## Build environment

Install Git, curl, CMake 3.21 or newer, Ninja, and the system `clang` and `clang++` compilers. The dependency script requires additional build tools and system development packages for Qt and other libraries. Package names vary by distribution; a verified distribution-specific package list remains to be documented here.

The Linux dependency script selects the host's system Clang for its builds. The `debug-linux` and `release-linux` CMake presets use the project's Linux Clang toolchain file.

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
./scripts/deps/build-dependencies-linux.sh deps
```

The script downloads and verifies third-party sources, then builds and installs them into the local `deps/` directory. It selects the system `clang` and `clang++` compilers for its builds.

## Configure the app

```sh
cmake --preset debug-linux
```

This reads the `debug-linux` **configure preset** and generates a Debug build in `build/debug-linux/`.

## Build the app

```sh
cmake --build --preset debug-linux
```

This reads the `debug-linux` **build preset** and compiles the configured project. The executable is written to `build/debug-linux/bin/RLyehPSX`.

## How the presets work

See [CMake presets](cmake_presets.md) for the shared preset definitions, inheritance, and maintenance guidance.

## Release build

After building the dependencies, configure the Release preset:

```sh
cmake --preset release-linux
```

Build the configured Release app:

```sh
cmake --build --preset release-linux
```

The executable is written to `build/release-linux/bin/RLyehPSX`.

The [Linux packaging notes](../packaging/linux_package_notes.md) record current AppImage and Flatpak work; they are not a release or installation guide.

[Back to building](index.md)
