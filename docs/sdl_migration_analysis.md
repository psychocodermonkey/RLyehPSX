# SDL2 to SDL3 Migration Analysis

This document is the implementation guide for migrating the project from SDL2 to SDL3. Its source-tree claims were reviewed on the `migration/sdl3` baseline; SDL3 API claims were checked against the official migration guide. Select and record the exact SDL3 release and archive checksum before changing dependency scripts.

The current SDL2 version is pinned to 2.30.6. The main runtime usage is concentrated in `src/util/sdl_audio_stream.cpp` and `src/util/sdl_input_source.cpp`; SDL is not the primary desktop windowing or UI layer.

Primary SDL3 references:

- SDL3 migration guide: https://wiki.libsdl.org/SDL3/README-migration
- SDL3 CMake integration: https://wiki.libsdl.org/SDL3/README-cmake

## Scope and compatibility boundaries

SDL is used for the optional SDL audio backend and the non-Android SDL input source. It is not this project's primary desktop windowing or UI layer.

The migration must preserve:

- Input source names and user-visible settings keys.
- The user controller database override (`gamecontrollerdb.txt`).

The saved SDL2-named `SDL-<player>/...` bindings are intentionally incompatible with the SDL3-native binding format. Do not translate, import, rewrite, or automatically delete them. Users can explicitly clear controller settings and remap; newly generated bindings use SDL3-native PascalCase names while retaining their direct PlayStation action meanings.

`SDL-0` through `SDL-3` in UI labels denote player slots, not the SDL library version. Do not rename those labels or their translations as part of this migration.

Flatpak and AppImage packaging are intentionally out of scope and will be addressed by a separate packaging update. The Flatpak manifest currently pins an SDL2 module; the AppImage script has no SDL2-specific reference. Their current packaging status is not assumed by this migration.

## Current SDL2 Integration

### Build and dependency plumbing

SDL2 is required globally through CMake:

- `CMakeModules/DuckStationDependencies.cmake`
  - `find_package(SDL2 2.30.6 REQUIRED)`

The `util` target links SDL2 and includes the SDL-specific runtime files:

- `src/util/CMakeLists.txt`
  - `sdl_audio_stream.cpp`
  - `sdl_input_source.cpp`
  - `sdl_input_source.h`
  - `SDL2::SDL2`

SDL2 is also pinned in platform dependency scripts:

- `scripts/deps/build-dependencies-mac.sh`
- `scripts/deps/build-dependencies-linux.sh`
- `scripts/deps/build-dependencies-windows-x64.bat`
- `scripts/deps/build-dependencies-windows-arm64.bat`
- `scripts/deps/sdl2-pipewire-compat.patch`

Windows build/deployment files also reference SDL2 directly:

- `src/util/util.props`
- `src/duckstation-qt/CMakeLists.txt`

Migration implication:

The dependency/build side is not just a source edit. The migration needs coordinated updates to CMake package discovery, dependency download/build scripts, Windows props, and copied runtime DLL names. The SDL2 PipeWire compatibility patch must be removed or replaced only after confirming that the selected SDL3 release does not need an equivalent workaround.

## Runtime Usage Summary

### SDL audio backend

File:

- `src/util/sdl_audio_stream.cpp`

Purpose:

- Provides the optional `AudioBackend::SDL` implementation.
- Registered through `AudioStream::CreateStream()` in `src/util/audio_stream.cpp`.

Current SDL2 APIs used:

- `SDL_InitSubSystem(SDL_INIT_AUDIO)`
- `SDL_QuitSubSystem(SDL_INIT_AUDIO)`
- `SDL_AudioSpec`
- callback-based audio via `SDL_AudioSpec::callback`
- `SDL_OpenAudioDevice()`
- `SDL_PauseAudioDevice()`
- `SDL_CloseAudioDevice()`
- `SDL_GetError()`

SDL3 migration concern:

SDL3 audio is substantially redesigned around audio streams. A callback path still exists, but it is attached to an `SDL_AudioStream`, not directly to an `SDL_AudioDeviceID`. This backend is a focused port, not a mechanical rename.

Risk areas:

- The current backend pulls frames from the emulator through an SDL callback. In SDL3, preserve that producer model with an `SDL_AudioStream` callback, or deliberately adopt a push model; do not mix the two accidentally.
- `SDL_AudioSpec` no longer has `samples`, and `SDL_AUDIO_ALLOW_SAMPLES_CHANGE` is gone. The current requested-buffer and obtained-buffer logging therefore needs a deliberate SDL3 replacement; SDL3 normally manages this itself, while `SDL_HINT_AUDIO_DEVICE_SAMPLE_FRAMES` is available only when an explicit request is justified.
- Pause and resume are separate operations in SDL3.
- Latency behavior must be tested, because emulator audio glitches are user-visible quickly.

Decision:

- Preserve the current SDL backend latency-setting control. Derive the requested device frame count from the existing latency-setting logic and set `SDL_HINT_AUDIO_DEVICE_SAMPLE_FRAMES` before opening the SDL3 audio device. This deliberately retains the setting's intent rather than silently allowing SDL3 defaults to make it ineffective. Validate the resulting real latency and underrun behavior on supported platforms.

Recommended migration approach:

- Port this file as an independently reviewable unit from input, while keeping it in the same migration branch if that is more practical.
- Preserve the existing `AudioStream` interface if possible.
- Preserve the current latency-setting control through `SDL_HINT_AUDIO_DEVICE_SAMPLE_FRAMES`, rather than assuming SDL3 defaults are an adequate replacement for SDL2's device-buffer request.
- Compare against the cubeb backend so regressions are easier to isolate.

### SDL input backend

Files:

- `src/util/sdl_input_source.h`
- `src/util/sdl_input_source.cpp`

Purpose:

- Provides the SDL input source on non-Android platforms.
- Registered from `InputManager::ReloadSources()` in `src/util/input_manager.cpp`.
- Handles game controllers, raw joysticks, haptics, rumble, controller LEDs, SDL hints, and SDL input events.

Current SDL2 API groups used:

- Initialization:
  - `SDL_InitSubSystem(SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER | SDL_INIT_HAPTIC)`
  - `SDL_QuitSubSystem(...)`
  - `SDL_PollEvent()`
- Logging:
  - `SDL_LogSetOutputFunction()`
  - `SDL_LogSetAllPriority()`
  - `SDL_NUM_LOG_PRIORITIES`
- Hints:
  - `SDL_SetHint()`
  - `SDL_HINT_GAMECONTROLLERCONFIG_FILE`
  - `SDL_HINT_JOYSTICK_HIDAPI_PS4_RUMBLE`
  - `SDL_HINT_JOYSTICK_HIDAPI_PS5_RUMBLE`
  - `SDL_HINT_JOYSTICK_HIDAPI_PS5_PLAYER_LED`
  - `SDL_HINT_JOYSTICK_HIDAPI_WII`
  - `SDL_HINT_JOYSTICK_HIDAPI_PS3`
  - `SDL_HINT_JOYSTICK_IOKIT`
  - `SDL_HINT_JOYSTICK_MFI`
- Game controller:
  - `SDL_GameController`
  - `SDL_IsGameController()`
  - `SDL_GameControllerOpen()`
  - `SDL_GameControllerClose()`
  - `SDL_GameControllerGetJoystick()`
  - `SDL_GameControllerName()`
  - `SDL_GameControllerGetPlayerIndex()`
  - `SDL_GameControllerGetBindForAxis()`
  - `SDL_GameControllerGetBindForButton()`
  - `SDL_GameControllerRumble()`
  - `SDL_GameControllerHasLED()`
  - `SDL_GameControllerSetLED()`
  - `SDL_GameControllerAxis`
  - `SDL_GameControllerButton`
  - `SDL_GameControllerButtonBind`
- Joystick:
  - `SDL_Joystick`
  - `SDL_JoystickOpen()`
  - `SDL_JoystickClose()`
  - `SDL_JoystickName()`
  - `SDL_JoystickInstanceID()`
  - `SDL_JoystickGetPlayerIndex()`
  - `SDL_JoystickNumAxes()`
  - `SDL_JoystickNumButtons()`
  - `SDL_JoystickNumHats()`
- Haptic:
  - `SDL_Haptic`
  - `SDL_HapticOpenFromJoystick()`
  - `SDL_HapticClose()`
  - `SDL_HapticEffect`
  - `SDL_HAPTIC_LEFTRIGHT`
  - `SDL_HapticNewEffect()`
  - `SDL_HapticUpdateEffect()`
  - `SDL_HapticRunEffect()`
  - `SDL_HapticStopEffect()`
  - `SDL_HapticRumbleSupported()`
  - `SDL_HapticRumbleInit()`
  - `SDL_HapticRumblePlay()`
  - `SDL_HapticRumbleStop()`
- Events:
  - `SDL_Event`
  - `SDL_CONTROLLERDEVICEADDED`
  - `SDL_CONTROLLERDEVICEREMOVED`
  - `SDL_CONTROLLERAXISMOTION`
  - `SDL_CONTROLLERBUTTONDOWN`
  - `SDL_CONTROLLERBUTTONUP`
  - `SDL_JOYDEVICEADDED`
  - `SDL_JOYDEVICEREMOVED`
  - `SDL_JOYAXISMOTION`
  - `SDL_JOYBUTTONDOWN`
  - `SDL_JOYBUTTONUP`
  - `SDL_JOYHATMOTION`
  - `SDL_ControllerAxisEvent`
  - `SDL_ControllerButtonEvent`
  - `SDL_JoyAxisEvent`
  - `SDL_JoyButtonEvent`
  - `SDL_JoyHatEvent`

SDL3 migration concern:

This is the largest migration surface. SDL2's `GameController` API was renamed/reworked as SDL3's `Gamepad` API. Event names, types, hints, and device identifiers also changed.

## SDL3-Specific Breakpoints

### Return-value semantics must be audited

SDL3 changes many camel-case APIs that returned `0` on success or a negative value on failure to return `bool`: `true` on success and `false` on failure. This is not a mechanical type change.

The current source contains SDL2-style checks for subsystem initialization, gamepad rumble probing, and haptic-rumble initialization. Each must be reviewed when its API is ported. In particular, a condition such as `result != 0` can invert success under SDL3 and leave the source compiling while disabling a subsystem or capability.

Do not bulk-rewrite comparisons. For every changed API, verify its SDL3 return contract and make the success path explicit.

### GameController becomes Gamepad

Current code uses SDL2 `SDL_GameController*` throughout `SDLInputSource::ControllerData` and the open/event paths.

Relevant code:

- `src/util/sdl_input_source.h`
  - `SDL_GameController* game_controller`
- `src/util/sdl_input_source.cpp`
  - controller axis/button name tables are keyed to `SDL_CONTROLLER_AXIS_*` and `SDL_CONTROLLER_BUTTON_*`
  - `OpenDevice()`
  - `HandleControllerAxisEvent()`
  - `HandleControllerButtonEvent()`
  - `GetGenericBindingMapping()`
  - `SendRumbleUpdate()`

SDL3 impact:

- Types and functions move from `GameController` naming to `Gamepad` naming.
- Constants and event names move from `SDL_CONTROLLER*` naming to `SDL_GAMEPAD*` naming.
- Binding structures and mapping APIs need review, not just search-and-replace.
- `SDL_GameControllerGetBindForAxis()` and `SDL_GameControllerGetBindForButton()` are removed in favor of `SDL_GetGamepadBindings()`. The duplicate-event suppression logic therefore needs an intentional adaptation.

Risk:

The saved SDL2 binding names in this project include strings like `SDL-0/+LeftX`, `SDL-0/A`, and `SDL-0/LargeMotor`. SDL3 uses positional face-button names (South/East/West/North), and its paddle enum naming/order differs from SDL2. The existing name and generic-binding tables must therefore be audited by semantic meaning, not enum ordinal.

Recommendation:

Adopt SDL3-native binding strings and validate newly mapped controls. Do not retain an SDL2 translation layer or validate stale saved SDL2 bindings as a compatibility requirement.

### Joystick device IDs and open semantics

Current SDL2 logic:

- Add events pass a device index.
- Remove and input events use joystick instance IDs.
- `OpenDevice(int index, bool is_gamecontroller)` opens either a game controller or joystick using the event-provided index.
- `CloseDevice(int joystick_index)` closes by stored joystick instance ID.

Relevant code:

- `SDLInputSource::ProcessSDLEvent()`
- `SDLInputSource::OpenDevice()`
- `SDLInputSource::CloseDevice()`
- `SDLInputSource::GetControllerDataForJoystickId()`

SDL3 impact:

SDL3 add events provide joystick instance IDs, not device indexes, for both gamepads and raw joysticks. `SDL_JoystickID` is now an unsigned type whose invalid value is zero.

Risk:

This can silently break startup enumeration and hotplug if `OpenDevice()` continues treating add-event IDs as SDL2-style device indices. The stored ID and lookup parameter types should become `SDL_JoystickID` rather than `int`.

Recommendation:

Treat hotplug as a first-class test case. Test startup with controllers already connected, plug-in after launch, unplug, replug, and reconnect with multiple devices.

### Event names and event fields

Current code filters and handles SDL2 event constants directly:

- `SDLInputSource::IsHandledInputEvent()`
- `SDLInputSource::ProcessSDLEvent()`

SDL3 impact:

Many event constants were renamed. Controller events become gamepad events, and their union members become `gaxis`, `gbutton`, and `gdevice`. Button events use a boolean `down` field; `SDL_PRESSED` and `SDL_RELEASED` are removed.

Risk:

A compile fix may still leave behavioral bugs if the wrong event field is used for device lookup or if the old `state` interpretation is retained.

Recommendation:

Port event handling around the meaning of each event:

- device added
- device removed
- gamepad axis motion
- gamepad button down/up
- joystick axis motion
- joystick button down/up
- joystick hat motion

Avoid treating this as only a textual rename.

### Logging API rename

The custom SDL log callback is part of the input-source initialization path. Port `SDL_LogSetOutputFunction()` to `SDL_SetLogOutputFunction()`, `SDL_LogSetAllPriority()` to `SDL_SetLogPriorities()`, and `SDL_NUM_LOG_PRIORITIES` to `SDL_LOG_PRIORITY_COUNT`. Keep the existing project log-level mapping, then verify its array bounds against the SDL3 enum.

### Hints and controller database

Current code uses SDL2 hint names, including controller mapping and HIDAPI behavior:

- `SDL_HINT_GAMECONTROLLERCONFIG_FILE`
- `SDL_HINT_JOYSTICK_HIDAPI_PS4_RUMBLE`
- `SDL_HINT_JOYSTICK_HIDAPI_PS5_RUMBLE`
- `SDL_HINT_JOYSTICK_HIDAPI_PS5_PLAYER_LED`
- `SDL_HINT_JOYSTICK_HIDAPI_WII`
- `SDL_HINT_JOYSTICK_HIDAPI_PS3`
- `SDL_HINT_JOYSTICK_IOKIT`
- `SDL_HINT_JOYSTICK_MFI`

Verified built-in-hint disposition:

| SDL2 hint | SDL3 disposition |
| --- | --- |
| `SDL_HINT_GAMECONTROLLERCONFIG_FILE` | Retained; set it before SDL initializes. |
| `SDL_HINT_JOYSTICK_HIDAPI_PS4_RUMBLE` | Replace with `SDL_HINT_JOYSTICK_ENHANCED_REPORTS`. |
| `SDL_HINT_JOYSTICK_HIDAPI_PS5_RUMBLE` | Replace with `SDL_HINT_JOYSTICK_ENHANCED_REPORTS`. |
| `SDL_HINT_JOYSTICK_HIDAPI_PS5_PLAYER_LED` | Retained. |
| `SDL_HINT_JOYSTICK_HIDAPI_WII` | Retained. |
| `SDL_HINT_JOYSTICK_HIDAPI_PS3` | Retained. |
| `SDL_HINT_JOYSTICK_IOKIT` | Retained. |
| `SDL_HINT_JOYSTICK_MFI` | Retained. |

The two old PlayStation rumble hints collapse into the single enhanced-reports hint. Keep the existing setting's intended enabled/disabled behavior; do not silently change it to SDL3's `auto` mode. SDL3 notes that enabling enhanced reports affects Bluetooth PlayStation behavior and cannot be undone without power-cycling the controller.

User-provided `SDLHints` are an externally configurable compatibility surface. Continue passing them through, but do not automatically rewrite their names without a documented settings migration. Record any changed or removed user-facing hints in release notes.

### Rumble and haptics

Current behavior:

- Prefer `SDL_GameControllerRumble()` when available.
- Fall back to `SDL_HapticOpenFromJoystick()`.
- Try a left/right haptic effect via `SDL_HAPTIC_LEFTRIGHT`.
- Fall back to generic haptic rumble.

Relevant code:

- `SDLInputSource::OpenDevice()`
- `SDLInputSource::EnumerateMotors()`
- `SDLInputSource::UpdateMotorState()`
- `SDLInputSource::SendRumbleUpdate()`

SDL3 impact:

SDL3 retains haptic effects with mostly renamed APIs, but simple-rumble gamepads no longer appear in the haptics interface. Gamepad rumble must use `SDL_RumbleGamepad()`; retain a haptic fallback only for raw joysticks where it is actually available.

Risk:

Rumble can compile and still feel wrong: swapped motors, weak intensity, stuck rumble, no stop on disconnect, a missing raw-joystick fallback, or no enhanced controller behavior.

Recommendation:

Test rumble separately for:

- Xbox-style controller
- DualShock 4
- DualSense
- generic DirectInput-style joystick
- controller without rumble

### Audio callback backend

Current behavior:

- SDL opens a playback device with `SDL_OpenAudioDevice()`.
- SDL invokes `AudioCallback()`.
- The callback pulls emulator frames through `ReadFrames()`.
- Playback pause is controlled by `SDL_PauseAudioDevice()`.

Relevant code:

- `src/util/sdl_audio_stream.cpp`

SDL3 impact:

SDL3 audio is stream-oriented and substantially different from SDL2's classic callback setup.

Risk:

This is likely the most behavior-sensitive non-input area. A naive port can compile but introduce crackling, latency changes, or underruns.

Recommendation:

Port as an independently reviewable unit. Keep testing focused on:

- clean startup
- pause/resume
- device close/reopen
- latency setting behavior
- long-running playback
- underrun behavior under load

### Include and CMake target names

Current source includes:

- `<SDL.h>`

Current target:

- `SDL2::SDL2`

SDL3 impact:

SDL3 uses `#include <SDL3/SDL.h>`. Its documented CMake package/target is `SDL3` / `SDL3::SDL3`; use config-mode package discovery so every local dependency build produces the same package layout.

Risk:

The source may compile locally against one package layout but fail in Windows dependency builds or CI.

Recommendation:

Decide one canonical CMake usage for SDL3, then update all dependency scripts and platform build paths to produce that same layout.

## Files Most Likely To Need Changes

High confidence:

- `CMakeModules/DuckStationDependencies.cmake`
- `src/util/CMakeLists.txt`
- `src/util/sdl_input_source.h`
- `src/util/sdl_input_source.cpp`
- `src/util/sdl_audio_stream.cpp`
- `scripts/deps/build-dependencies-mac.sh`
- `scripts/deps/build-dependencies-linux.sh`
- `scripts/deps/build-dependencies-windows-x64.bat`
- `scripts/deps/build-dependencies-windows-arm64.bat`
- `scripts/deps/sdl2-pipewire-compat.patch` (remove or replace after verification)
- `src/util/util.props`
- `src/duckstation-qt/CMakeLists.txt`

Possible secondary updates:

- Documentation and README dependency notes.
- User-facing settings names only if the project deliberately approves a settings migration.

## Migration Strategy

Recommended order:

1. Select and record the SDL3 release, source URL, checksum, and platform build options. Confirm whether the SDL2 PipeWire patch is obsolete before deleting it.
2. Update build plumbing, headers, CMake package discovery, and Windows library/DLL names together.
3. Port `sdl_input_source`, explicitly addressing return values, instance IDs, gamepad binding queries, event fields, the built-in hint table, and SDL3-native binding names.
4. Validate device add/remove semantics and newly mapped SDL3 bindings with real controllers before treating the input port as complete.
5. Port `sdl_audio_stream` as a separate reviewable unit, using an SDL3 audio stream and preserving the existing latency-setting intent. Compare it with cubeb.
6. Validate the supported core build paths and update dependency documentation. Do not rename player-slot labels such as `SDL-2 LED`.

The most important engineering choice is to adopt one coherent SDL3 input model: use SDL3 names and semantics for newly generated bindings while preserving their PlayStation action meanings, without retaining an SDL2 compatibility layer.

## Completion checklist

- [ ] All in-scope dependency sources, package names, import libraries, and runtime DLL names use SDL3.
- [ ] The selected SDL3 package is discovered through one canonical CMake configuration on every supported platform.
- [ ] Input initialization and all changed SDL return-value checks use SDL3's boolean contracts.
- [ ] Gamepad and joystick add events open devices by instance ID; removal and input events use the same ID type.
- [ ] Newly generated bindings use SDL3-native PascalCase names and retain their intended PlayStation action meanings; stale SDL2-named bindings are intentionally unsupported.
- [ ] The controller database override and every built-in hint have their documented SDL3 behavior.
- [ ] Gamepad rumble, raw-joystick haptics, LEDs, and disconnect cleanup are independently tested.
- [ ] The SDL audio backend supports startup, pause/resume, device close/reopen, and sustained playback without a latency regression.

## Test Matrix

Minimum practical validation:

- macOS:
  - app launch
  - controller connected before launch
  - hotplug after launch
  - unplug/replug
  - newly mapped SDL3 bindings and `gamecontrollerdb.txt` override
  - rumble
  - DualShock/DualSense LED behavior if available
  - SDL audio backend playback
- Linux:
  - X11 and/or Wayland as applicable
  - gamepad hotplug
  - raw joystick fallback
  - rumble/haptic fallback
- Windows:
  - dependency build script
  - runtime DLL packaging
  - XInput plus SDL source interaction
  - rumble

For every platform with hardware available, also test two simultaneous controllers and clean disconnect while rumble is active. This specifically exercises player-slot assignment, instance-ID handling, and cleanup.

## Roadmap Recommendation

SDL3 is a meaningful migration for this project, but the impact is concentrated. It is more important than a C++23 bump because it affects real runtime behavior and supportability.

Suggested roadmap wording:

> Migrate SDL2 2.30.6 to SDL3 with SDL3-native input bindings, validating gamepad, joystick, rumble, haptic, LED, hotplug, and SDL audio behavior across macOS, Linux, and Windows.
