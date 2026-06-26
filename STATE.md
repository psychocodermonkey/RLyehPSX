# R’Lyeh PSX - Current Development State

## Project Overview

R’Lyeh PSX is an independent GPL-derived PlayStation emulator project based on the DuckStation-GPL codebase.

## Repository

- GitHub: [RlyehPSX](https://github.com/psychocodermonkey/RlyehPSX)
- Default branch: master

## Project goals

- Learn emulator architecture and maintenance.
- Maintain and modernize the codebase.
- Preserve clean history through small, deliberate commits.
- Maintain practical cross-platform support.

---

## Current Status

### Overall Status

Current development focus:

- Platform validation
- Rebranding cleanup

Repository health:

- Stable
- Building
- Runtime validated on macOS

### macOS

**Status:** PASS

#### Verified from a completely fresh clone

- Dependency build succeeds
- Configure succeeds
- Full build succeeds
- Application bundle is generated
- Application launches successfully

#### Reference build process

``` sh
./scripts/deps/build-dependencies-mac.sh deps

export MACOSX_DEPLOYMENT_TARGET=11.0

cmake -S . -B build \
  -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_PREFIX_PATH="$PWD/deps"

ninja -C build
```

#### Observed cold build time

##### M4 Pro Macbook (14C/20GPU)

- Approximately 12-15 minutes
- Conservatively less than 20 minutes

---

#### Runtime Validation

##### Application

- Launches successfully
- No immediate startup issues observed

##### Game Testing

###### Castlevania: Symphony of the Night

- Existing save loaded successfully
- Gameplay tested for approximately 10-15 minutes
- No observed regressions

###### Xenogears

- Existing save detected successfully
- Reached title screen successfully

##### Save / Memory Card Compatibility

Successfully validated existing memory cards and save data that have previously been used across:

- PCSX ReARMed
- DuckStation
- SwanStation
- R’Lyeh PSX

##### Controller Validation

Verified working:

- CRKD Neo S (XInput)
- 8BitDo Pro 2 (XInput)

---

### Linux

**Status:** IN PROGRESS

#### Current Focus

- Bring the Linux dependency build back into a known-good state.
- Keep the Linux dependency script aligned with the MacOS dependency script where the upstream sources overlap.
- Validate the Qt dependency stack on Linux without destabilizing the working MacOS build.

#### Current Findings

- The Linux dependency script has been updated to use upstream Qt source archives.
- The Linux dependency script now verifies tarballs with `sha256sum`.
- Qt was tested with Clang 17 on Linux, but Qt host tools hit compatibility issues with the Linux standard library/toolchain.
- Qt was then moved back to GCC for Linux dependency builds, but Qt 6.7.2 still failed during host-tool linking on this machine.
- The current Linux blocker appears to be a Qt / GCC 16 / libstdc++ compatibility issue, not a project source issue.
- The cleanest next validation point is back on the working MacOS environment.

#### Linux Build

##### Reference Build Process

``` sh
./scripts/deps/build-dependencies-linux.sh deps

cmake -S . -B build \
  -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_PREFIX_PATH="$PWD/deps" \
  -DCMAKE_TOOLCHAIN_FILE="$PWD/scripts/clang-toolchain.cmake"

ninja -C build
```

##### Linux Host Tooling Assumptions

- Linux build tooling is currently pinned to `clang-17` in `scripts/clang-toolchain.cmake`.
- The dependency build script uses upstream source archives for its third-party components.
- Qt's configure step expects system packages for X11, XCB, XKB, fontconfig, OpenGL, GTK, and related headers.

##### Required Host Tools

These should be present before running the Linux dependency script:

- `clang-17`
- `clang++-17`
- `lld-17`
- `cmake`
- `ninja`
- `make`
- `git`
- `curl`
- `pkg-config`
- `autoconf`
- `automake`
- `libtool`
- `m4`
- `sha256sum`
- `tar`
- `unzip`

##### Required Linux Development Packages

These are the main system packages identified from Qt's configure and link failures on Fedora:

- `fontconfig-devel`
- `mesa-libGL-devel`
- `mesa-libEGL-devel`
- `libxcb-devel`
- `xcb-util-devel`
- `xcb-util-keysyms-devel`
- `xcb-util-image-devel`
- `xcb-util-renderutil-devel`
- `xcb-util-wm-devel`
- `xcb-util-cursor-devel`
- `libxkbcommon-devel`
- `libxkbcommon-x11-devel`
- `gtk3-devel`
- `glib2-devel`
- `libX11-devel`
- `libXext-devel`
- `libXi-devel`
- `libXrender-devel`
- `libSM-devel`
- `libICE-devel`

Depending on distro release and how Qt probes the system, additional XCB-related development packages may still be needed.

##### Notes On Clang

- The current Linux path expects Clang 17 for compatibility with the repo's Linux toolchain file.
- Keeping a newer system default compiler, such as Clang 22, is fine as long as `clang-17` remains available and is the compiler selected for this project.

##### Fedora Install Command

``` sh
sudo dnf install \
  clang17 llvm17 lld17 \
  cmake ninja make git curl pkgconf-pkg-config \
  autoconf automake libtool m4 \
  fontconfig-devel mesa-libGL-devel mesa-libEGL-devel \
  libxcb-devel xcb-util-devel xcb-util-keysyms-devel xcb-util-image-devel xcb-util-renderutil-devel \
  xcb-util-wm-devel xcb-util-cursor-devel \
  libxkbcommon-devel libxkbcommon-x11-devel \
  gtk3-devel glib2-devel \
  libX11-devel libXext-devel libXi-devel libXrender-devel \
  libSM-devel libICE-devel
```

##### Debian / Ubuntu Install Command

``` sh
sudo apt update && sudo apt install -y \
  clang-17 lld-17 llvm-17 \
  cmake ninja-build make git curl pkg-config \
  autoconf automake libtool m4 \
  libfontconfig1-dev libgl1-mesa-dev libegl1-mesa-dev \
  libxcb1-dev xcb-util-dev xcb-util-keysyms-dev xcb-util-image-dev xcb-util-renderutil-dev \
  xcb-util-wm-dev xcb-util-cursor-dev \
  libxkbcommon-dev libxkbcommon-x11-dev \
  libgtk-3-dev libglib2.0-dev \
  libx11-dev libxext-dev libxi-dev libxrender-dev \
  libsm-dev libice-dev
```

Package names can vary slightly across Debian-based releases. If one of the Qt-related packages is unavailable, install the closest `-dev` equivalent for that library family.

## Platform Validation Matrix

| Platform      | Status       |
|---------------|--------------|
| macOS         | PASS         |
| Android       | NOT TESTED   |
| Windows       | NOT TESTED   |
| Linux         | IN PROGRESS  |

---

## Recent Achievements

- Repository successfully rebranded as R'Lyeh PSX.
- Fresh-clone reproducible build process verified.
- Dependency and build system modernization completed.
- macOS build and runtime validation completed.

⸻

## Immediate Next Steps

### Rebranding

- Remove DuckStation logos.
- Remove DuckStation naming from descriptions links.
- Remove DuckStation repo references and links.

### Code Base Modernization

Areas for future investigation:

- Qt version updates.
- Toolchain modernization (C++ / Clang).

### Android Validation

Determine:

- Required SDK version
- Required NDK version
- Current Android build status

Goal:

- Produce a successful Android build from macOS.

### Windows Validation

Validate:

- Dependency build
- Configure process
- Full build process

Target platform:

- Blade laptop

### Linux Validation

Current goal:

- Validate the dependency build.
- Verify configure succeeds.
- Verify the full build succeeds.

Current blocker:

- Qt host-tool linking on Linux with the current GCC/libstdc++ toolchain.

Next step:

- Return to the MacOS environment and validate the Qt update there first.

### Maintenance Work / Feature ToDo

These are features I'd like to explore implementing.

- Disable RetroAchievements during development ahead of approval.
  - IMPORTANT NOTE: 2026/06/19: Initial working build connected to RA server using existing. DuckStation configuration. No achievements unlocked or progress made. This needs to be disclosed when applying for RetroAchievements approval.
  - Set as a build flag so once approval is granted it's easy to re-enable.
  - Current `rcheevos` version is v11.5.0. As of 2026/06/22, latest version is v12.3.0. Investigate drop in change and re-work integration to use latest version of achievement code.
- Remove Discord Rich Presence support.
- M3U support when being called from another frontend.
  - M3U support seems to work on desktop when opening from the browser.
  - Verify functionality from Android build.
- Update C++ versions on all platforms. (Major re-work)
- Update SDL2 to SDL3. (Major re-work)
- More Shaders/filters.

---

*Insaniam non modo amplectere; Contrecta eam invītam; Osculis voracibus obruito; Atque ei vinum eme.*

---

## Resume

``` sh
codex resume 019ee319-0f1f-7cf2-8c18-4b7e19ebd55d
```
