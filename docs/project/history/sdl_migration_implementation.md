# SDL3 Migration Implementation Notes

This document records implementation decisions for the SDL2-to-SDL3 migration. It is intended to be read at the start of a new work session together with [SDL2 to SDL3 Migration Analysis](sdl_migration_analysis.md).

The analysis document describes the source-tree impact, SDL3 API changes, risks, and validation matrix. This document records decisions already made so later sessions do not reopen them accidentally.

## Current baseline

- Candidate dependency: **SDL 3.4.14**.
- Review source checkout: `tmp/SDL-3.4.x`, detached at the immutable `release-3.4.14` tag.
- Review commit: `147a8ee32dbf9ac02f3794964490687b6bbda1bc`.
- Source archive: `https://github.com/libsdl-org/SDL/releases/download/release-3.4.14/SDL3-3.4.14.tar.gz`.
- Source archive SHA-256: `30d4aa2b3037718142b32dffd4e72f917ebb6cc5227150e7bb9c45efb2153aeb`.
- Local review copy: `tmp/SDL3-3.4.14.tar.gz` (archive integrity verified with `tar -tzf`).

SDL 3.4.14 is the selected starting point because it is a stable release and includes a macOS fix for the 8BitDo Pro 3 being reported twice. The controller is part of the available real-hardware test set.

## Completed milestones

- Linux dependency build: `build-dependencies-linux.sh` downloads, verifies, builds, and installs shared SDL 3.4.14 without SDL test targets. The SDL2-only PipeWire compatibility patch was removed after this build succeeded.
- macOS dependency build: `build-dependencies-mac.sh` downloads, verifies, builds, and installs shared SDL 3.4.14 without SDL test targets. The installed `libSDL3.dylib` was verified as universal with `x86_64` and `arm64` slices.
- CMake build configuration: SDL is discovered through the installed SDL3 config package and `util` links `SDL3::SDL3`. The Windows runtime deployment list uses `SDL3.dll`.
- CMake configuration succeeded against the installed SDL3 package on macOS and Linux. Linux resolved `SDL3_DIR` from the project dependency prefix.

Windows dependency scripts, Visual Studio project properties, and Windows build validation are deferred pending the planned Windows toolchain replacement. Do not treat the existing Windows SDL2 path as a supported or verified baseline.

## Migration principle

Adopt SDL3-native APIs, terminology, and persisted binding names while preserving emulator runtime behavior after controllers are remapped. Configuration compatibility is intentionally dropped; functional compatibility is not.

After remapping, face buttons must retain their PlayStation action/glyph meanings, and sticks, triggers, D-pad, motors, LEDs, raw joystick inputs, player assignment, hotplug, disconnect cleanup, and SDL audio behavior must retain their intended behavior. Use this principle to resolve implementation choices: remove SDL2-specific compatibility code, but do not introduce unrelated behavior changes.

## Decisions

### Pin SDL 3.4.14

Use the immutable `release-3.4.14` source release for integration and dependency scripts. Do not use the moving `release-3.4.x` branch as a build input.

The current checkout may be used to compare earlier tags when needed, but any build, checksum, or final dependency update must be tied to the 3.4.14 release archive.

### Adopt SDL3-native controller semantics

The SDL input source will use SDL3 gamepad terminology and semantics internally and in newly generated SDL binding strings. This is an intentional configuration compatibility break: existing SDL2-named `SDL-*` bindings do not need to continue resolving, and controllers may be reset and remapped after migration.

In particular:

- Use SDL3 positional face-button names: `South`, `East`, `West`, and `North`, rather than retaining SDL2's `A`, `B`, `X`, and `Y` binding names.
- Use SDL3's explicit paddle positions: `RightPaddle1`, `LeftPaddle1`, `RightPaddle2`, and `LeftPaddle2`.
- Serialize generated SDL3 gamepad bindings with readable PascalCase SDL3-native names. Examples include `South`, `LeftTrigger`, `RightShoulder`, and `RightPaddle1`; do not use SDL2 names or SDL's lower-case conversion tokens as the persisted format.
- Do not retain an SDL2-to-SDL3 translation layer solely to preserve saved binding strings.
- Do not import, rewrite, or automatically delete stale SDL2-named bindings. They are intentionally unsupported; controller settings can be cleared and remapped explicitly.
- Keep the direct semantic mapping from SDL3 controls to the emulator's PlayStation glyphs and generic actions. For example, the SDL3 South face button maps directly to the Cross action/glyph. This is current input behavior, not legacy binding compatibility.

This choice favors one coherent SDL3 model over support for configuration files that have not been released publicly.

## Implementation boundaries

- SDL remains limited to the optional SDL audio backend and the non-Android SDL input source; it is not the primary desktop windowing or UI layer.
- Do not rename `SDL-0` through `SDL-3` player-slot labels. They identify player slots, not an SDL library version.
- Treat input and audio as separate reviewable ports. The input port has the largest API and behavior surface; the audio port must preserve its pull/callback producer model while adapting to SDL3 audio streams.
- Do not use SDL3 old-name compatibility aliases as the migration strategy. Port changed APIs according to their SDL3 contracts.
- Flatpak and AppImage packaging remain separate work unless explicitly brought into scope.

## Compartmentalized implementation sequence

Implement and review the migration as the following narrow change sets. Do not combine later change sets into an earlier one merely because they touch the same source files. The sets are logical review boundaries, not necessarily independently buildable milestones: Steps 1 and 2 remain separate commits, with functional input validation after Step 3 completes the SDL3 input port.

1. **Input identity and lifecycle** — Restrict changes to `src/util/sdl_input_source.h` and `src/util/sdl_input_source.cpp`. Port device identity, startup enumeration, add/remove events, open/close paths, and lookup types to use `SDL_JoystickID` consistently. Do not rename bindings or alter haptics, rumble, LEDs, or audio in this set. Its later validation responsibility is controllers connected before launch and basic plug/unplug/replug behavior.
2. **Input API and binding semantics** — Restrict changes to the SDL input source. Port GameController types and events to SDL3 Gamepad APIs; produce the decided SDL3-native binding names; and rebuild duplicate raw-joystick-event suppression with `SDL_GetGamepadBindings()`. Its later validation responsibility is newly mapped buttons, axes, D-pad, and raw-joystick fallback controls retaining their intended PlayStation actions.
3. **Input capabilities and SDL3 contracts** — Restrict changes to the SDL input source. Port hints, rumble, haptics, LEDs, and every affected success/failure check to their SDL3 contracts. Verify supported rumble and LED behavior, raw-joystick haptic fallback, and disconnect cleanup while rumble is active.
4. **Audio backend** — Restrict changes to `src/util/sdl_audio_stream.cpp` and directly required build declarations. Replace the SDL2 device callback arrangement with SDL3's audio-stream callback model while preserving the emulator's pull producer model. Verify startup, pause/resume, close/reopen, latency, underrun behavior, and sustained playback.
5. **Deferred Windows integration** — Do not begin until the Windows toolchain replacement is in scope. Then update the Windows dependency scripts and Visual Studio properties from SDL2 to SDL3 and validate dependency build, runtime DLL deployment, and XInput/SDL interaction.

## High-risk items to address during implementation

1. SDL3 gamepad/joystick add events provide instance IDs, not SDL2 device indexes. Open, lookup, removal, and event handling must use `SDL_JoystickID` consistently.
2. SDL3 converts many success/failure return values to `bool`. Audit each ported call; do not mechanically retain SDL2 comparisons such as `!= 0`.
3. SDL3 replaces per-control game-controller binding queries with `SDL_GetGamepadBindings()`. Rebuild duplicate raw-joystick-event suppression around that complete binding list.
4. SDL3 audio is stream-oriented. Its buffer sizing is not a direct replacement for SDL2's `SDL_AudioSpec::samples`; validate latency rather than forcing the old requested frame count.
5. SDL3 uses gamepad capability properties for RGB LED and rumble capability checks. Simple-rumble gamepads no longer appear in the haptics interface.
6. SDL 3.4.14's PipeWire implementation has been built and installed successfully through the Linux dependency script. The SDL2-only PipeWire compatibility patch is obsolete and should be removed from the dependency flow.

## Remaining implementation-session checklist

- Port the SDL input source using SDL3-native binding names and test the 8BitDo Pro 3 first on macOS.
- Port the SDL audio backend separately, then validate its latency and long-running playback behavior.

## Hardware validation priority

For the 8BitDo Pro 3 on macOS, verify:

- it appears once;
- it receives one stable player slot;
- all controls can be newly mapped using SDL3-native names;
- unplug/replug does not create duplicates;
- rumble and LED behavior work when the controller/driver supports them.

Use other available controllers to cover raw joystick fallback, Xbox-style gamepad behavior, DualShock/DualSense behavior, and multi-controller hotplug.
