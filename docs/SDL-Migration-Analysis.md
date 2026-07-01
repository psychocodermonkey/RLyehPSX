# SDL2 to SDL3 Migration Analysis

This document summarizes where SDL2 is used in this project and highlights the areas that are likely to matter when migrating to SDL3.

The current SDL2 version is pinned to 2.30.6. The main runtime usage is concentrated in `src/util/sdl_audio_stream.cpp` and `src/util/sdl_input_source.cpp`; SDL is not the primary desktop windowing or UI layer.

Primary SDL3 reference:

- SDL3 migration guide: https://wiki.libsdl.org/SDL3/README-migration

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
- `scripts/flatpak/modules/20-sdl2.yaml`

Windows project files also reference SDL2 directly:

- `src/util/util.props`
- `src/util/util.vcxproj`
- `src/util/util.vcxproj.filters`
- `src/duckstation-qt/CMakeLists.txt`

Migration implication:

The dependency/build side is not just a source edit. The migration needs coordinated updates to CMake package discovery, dependency download/build scripts, Flatpak metadata, Windows props/project files, and copied runtime DLL names.

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

SDL3 audio is one of the larger API changes. The SDL3 migration guide describes audio as substantially redesigned around audio streams. This backend should be treated as a real port, not a mechanical rename.

Risk areas:

- The current backend pulls frames from the emulator through an SDL callback. SDL3 prefers `SDL_AudioStream`-based flow.
- Device opening and playback control APIs changed.
- Pause/resume behavior and callback ownership need to be revalidated.
- Latency behavior must be tested, because emulator audio glitches are user-visible quickly.

Recommended migration approach:

- Port this file separately from input.
- Preserve the existing `AudioStream` interface if possible.
- Validate latency and underrun behavior with the same buffer settings currently used by SDL2.
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
  - `SDL_GameControllerNumMappings()`
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

Risk:

The saved binding names in this project are user-facing strings like `SDL-0/+LeftX`, `SDL-0/A`, `SDL-0/LargeMotor`. Those should probably remain stable even if the underlying SDL3 names change, otherwise existing controller mappings may break.

Recommendation:

Preserve the project's existing binding string format unless there is a deliberate settings migration.

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

SDL3 changes joystick identification semantics. The migration guide notes that joystick instance IDs are now used more consistently, including in device add events.

Risk:

This can silently break hotplug if the code continues treating add-event IDs as SDL2-style device indices.

Recommendation:

Treat hotplug as a first-class test case. Test startup with controllers already connected, plug-in after launch, unplug, replug, and reconnect with multiple devices.

### Event names and event fields

Current code filters and handles SDL2 event constants directly:

- `SDLInputSource::IsHandledInputEvent()`
- `SDLInputSource::ProcessSDLEvent()`

SDL3 impact:

Many event constants were renamed. Controller events become gamepad events. Some event structures and field names also changed.

Risk:

A compile fix may still leave behavioral bugs if the wrong field is used for device lookup.

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

SDL3 impact:

Several hints were renamed, removed, or changed. The controller database terminology also moved from controller to gamepad.

Risk:

If hints are wrong or ignored, controllers may still appear to work while enhanced rumble, PS5 LEDs, IOKit/MFi behavior, or custom mappings regress.

Recommendation:

Make a table of each current hint and its SDL3 equivalent before implementation. Treat unknown user-provided `SDLHints` as pass-through, but audit built-in hints.

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

SDL3 still has haptic support, but gamepad rumble should be reviewed through the SDL3 gamepad APIs. Haptic support may not map identically across platforms.

Risk:

Rumble can compile and still feel wrong: swapped motors, weak intensity, stuck rumble, no stop on disconnect, or no enhanced controller behavior.

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

Port after input or as a separate branch. Keep testing focused on:

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

SDL3 installs different CMake package and target names. Include layout may also differ depending on package configuration.

Risk:

The source may compile locally against one package layout but fail in Flatpak, Windows dependency builds, or CI.

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
- `scripts/flatpak/modules/20-sdl2.yaml`
- `src/util/util.props`
- `src/duckstation-qt/CMakeLists.txt`

Possible secondary updates:

- UI labels containing `SDL2`, such as `controllerledsettingsdialog.ui`.
- Documentation and README dependency notes.
- User-facing settings names only if the project deliberately wants to rename them.

## Migration Strategy

Recommended order:

1. Update dependency scripts and CMake discovery for SDL3 in a branch.
2. Port `sdl_input_source` compile errors first, preserving existing project binding strings.
3. Validate device add/remove semantics with real controllers.
4. Validate controller mappings, raw joystick fallback, rumble, haptics, LEDs, and platform-specific hints.
5. Port `sdl_audio_stream` separately and compare behavior against the existing SDL2 backend and cubeb.
6. Clean up labels/docs after runtime behavior is validated.

The most important engineering choice is to avoid mixing semantic changes with rename churn. Keep the project-level input binding format stable unless a settings migration is intentionally planned.

## Test Matrix

Minimum practical validation:

- macOS:
  - app launch
  - controller connected before launch
  - hotplug after launch
  - unplug/replug
  - rumble
  - DualShock/DualSense LED behavior if available
  - SDL audio backend playback
- Linux:
  - X11 and/or Wayland as applicable
  - gamepad hotplug
  - raw joystick fallback
  - rumble/haptic fallback
  - Flatpak build
- Windows:
  - dependency build script
  - runtime DLL packaging
  - XInput plus SDL source interaction
  - rumble

## Roadmap Recommendation

SDL3 is a meaningful migration for this project, but the impact is concentrated. It is more important than a C++23 bump because it affects real runtime behavior and supportability.

Suggested roadmap wording:

> Migrate SDL2 2.30.6 to SDL3, preserving existing input binding strings and validating gamepad, joystick, rumble, haptic, LED, hotplug, and SDL audio behavior across macOS, Linux, and Windows.

