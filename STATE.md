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

## Platform Validation Matrix

| Platform      | Status       |
|---------------|--------------|
| macOS         | PASS         |
| Android       | NOT TESTED   |
| Windows       | NOT TESTED   |
| Linux         | NOT TESTED   |

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

Validate:

- Dependency build
- Configure process
- Full build process

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
