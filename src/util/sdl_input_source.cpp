// 2026/08/14 - Modified by R'Lyeh PSX contributors.
// SPDX-FileCopyrightText: 2026 RLyehPSX <https://github.com/RlyehPSX>
// SPDX-FileCopyrightText: 2019-2024 Connor McLaughlin <stenzek@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "sdl_input_source.h"
#include "input_manager.h"

#include "core/host.h"
#include "core/settings.h"

#include "common/assert.h"
#include "common/bitutils.h"
#include "common/file_system.h"
#include "common/log.h"
#include "common/path.h"
#include "common/string_util.h"

#include "IconsPromptFont.h"

#include <cmath>

#ifdef __APPLE__
#include <dispatch/dispatch.h>
#endif

Log_SetChannel(SDLInputSource);

static constexpr const char* CONTROLLER_DB_FILENAME = "gamecontrollerdb.txt";

static constexpr const char* s_sdl_axis_names[] = {
  "LeftX",        // SDL_GAMEPAD_AXIS_LEFTX
  "LeftY",        // SDL_GAMEPAD_AXIS_LEFTY
  "RightX",       // SDL_GAMEPAD_AXIS_RIGHTX
  "RightY",       // SDL_GAMEPAD_AXIS_RIGHTY
  "LeftTrigger",  // SDL_GAMEPAD_AXIS_LEFT_TRIGGER
  "RightTrigger", // SDL_GAMEPAD_AXIS_RIGHT_TRIGGER
};
static constexpr const char* s_sdl_axis_icons[][2] = {
  {ICON_PF_LEFT_ANALOG_LEFT, ICON_PF_LEFT_ANALOG_RIGHT},   // SDL_GAMEPAD_AXIS_LEFTX
  {ICON_PF_LEFT_ANALOG_UP, ICON_PF_LEFT_ANALOG_DOWN},      // SDL_GAMEPAD_AXIS_LEFTY
  {ICON_PF_RIGHT_ANALOG_LEFT, ICON_PF_RIGHT_ANALOG_RIGHT}, // SDL_GAMEPAD_AXIS_RIGHTX
  {ICON_PF_RIGHT_ANALOG_UP, ICON_PF_RIGHT_ANALOG_DOWN},    // SDL_GAMEPAD_AXIS_RIGHTY
  {nullptr, ICON_PF_LEFT_TRIGGER_PULL},                    // SDL_GAMEPAD_AXIS_LEFT_TRIGGER
  {nullptr, ICON_PF_RIGHT_TRIGGER_PULL},                   // SDL_GAMEPAD_AXIS_RIGHT_TRIGGER
};
static constexpr const GenericInputBinding s_sdl_generic_binding_axis_mapping[][2] = {
  {GenericInputBinding::LeftStickLeft, GenericInputBinding::LeftStickRight},   // SDL_GAMEPAD_AXIS_LEFTX
  {GenericInputBinding::LeftStickUp, GenericInputBinding::LeftStickDown},      // SDL_GAMEPAD_AXIS_LEFTY
  {GenericInputBinding::RightStickLeft, GenericInputBinding::RightStickRight}, // SDL_GAMEPAD_AXIS_RIGHTX
  {GenericInputBinding::RightStickUp, GenericInputBinding::RightStickDown},    // SDL_GAMEPAD_AXIS_RIGHTY
  {GenericInputBinding::Unknown, GenericInputBinding::L2},                     // SDL_GAMEPAD_AXIS_LEFT_TRIGGER
  {GenericInputBinding::Unknown, GenericInputBinding::R2},                     // SDL_GAMEPAD_AXIS_RIGHT_TRIGGER
};

static constexpr const char* s_sdl_button_names[] = {
  "South",         // SDL_GAMEPAD_BUTTON_SOUTH
  "East",          // SDL_GAMEPAD_BUTTON_EAST
  "West",          // SDL_GAMEPAD_BUTTON_WEST
  "North",         // SDL_GAMEPAD_BUTTON_NORTH
  "Back",          // SDL_GAMEPAD_BUTTON_BACK
  "Guide",         // SDL_GAMEPAD_BUTTON_GUIDE
  "Start",         // SDL_GAMEPAD_BUTTON_START
  "LeftStick",     // SDL_GAMEPAD_BUTTON_LEFT_STICK
  "RightStick",    // SDL_GAMEPAD_BUTTON_RIGHT_STICK
  "LeftShoulder",  // SDL_GAMEPAD_BUTTON_LEFT_SHOULDER
  "RightShoulder", // SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER
  "DPadUp",        // SDL_GAMEPAD_BUTTON_DPAD_UP
  "DPadDown",      // SDL_GAMEPAD_BUTTON_DPAD_DOWN
  "DPadLeft",      // SDL_GAMEPAD_BUTTON_DPAD_LEFT
  "DPadRight",     // SDL_GAMEPAD_BUTTON_DPAD_RIGHT
  "Misc1",         // SDL_GAMEPAD_BUTTON_MISC1
  "RightPaddle1",  // SDL_GAMEPAD_BUTTON_RIGHT_PADDLE1
  "LeftPaddle1",   // SDL_GAMEPAD_BUTTON_LEFT_PADDLE1
  "RightPaddle2",  // SDL_GAMEPAD_BUTTON_RIGHT_PADDLE2
  "LeftPaddle2",   // SDL_GAMEPAD_BUTTON_LEFT_PADDLE2
  "Touchpad",      // SDL_GAMEPAD_BUTTON_TOUCHPAD
  "Misc2",         // SDL_GAMEPAD_BUTTON_MISC2
  "Misc3",         // SDL_GAMEPAD_BUTTON_MISC3
  "Misc4",         // SDL_GAMEPAD_BUTTON_MISC4
  "Misc5",         // SDL_GAMEPAD_BUTTON_MISC5
  "Misc6",         // SDL_GAMEPAD_BUTTON_MISC6
};
static constexpr const char* s_sdl_button_icons[] = {
  ICON_PF_BUTTON_A,           // SDL_GAMEPAD_BUTTON_SOUTH
  ICON_PF_BUTTON_B,           // SDL_GAMEPAD_BUTTON_EAST
  ICON_PF_BUTTON_X,           // SDL_GAMEPAD_BUTTON_WEST
  ICON_PF_BUTTON_Y,           // SDL_GAMEPAD_BUTTON_NORTH
  ICON_PF_SHARE_CAPTURE,      // SDL_GAMEPAD_BUTTON_BACK
  ICON_PF_XBOX,               // SDL_GAMEPAD_BUTTON_GUIDE
  ICON_PF_BURGER_MENU,        // SDL_GAMEPAD_BUTTON_START
  ICON_PF_LEFT_ANALOG_CLICK,  // SDL_GAMEPAD_BUTTON_LEFT_STICK
  ICON_PF_RIGHT_ANALOG_CLICK, // SDL_GAMEPAD_BUTTON_RIGHT_STICK
  ICON_PF_LEFT_SHOULDER_LB,   // SDL_GAMEPAD_BUTTON_LEFT_SHOULDER
  ICON_PF_RIGHT_SHOULDER_RB,  // SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER
  ICON_PF_XBOX_DPAD_UP,       // SDL_GAMEPAD_BUTTON_DPAD_UP
  ICON_PF_XBOX_DPAD_DOWN,     // SDL_GAMEPAD_BUTTON_DPAD_DOWN
  ICON_PF_XBOX_DPAD_LEFT,     // SDL_GAMEPAD_BUTTON_DPAD_LEFT
  ICON_PF_XBOX_DPAD_RIGHT,    // SDL_GAMEPAD_BUTTON_DPAD_RIGHT
};
static constexpr const GenericInputBinding s_sdl_generic_binding_button_mapping[] = {
  GenericInputBinding::Cross,     // SDL_GAMEPAD_BUTTON_SOUTH
  GenericInputBinding::Circle,    // SDL_GAMEPAD_BUTTON_EAST
  GenericInputBinding::Square,    // SDL_GAMEPAD_BUTTON_WEST
  GenericInputBinding::Triangle,  // SDL_GAMEPAD_BUTTON_NORTH
  GenericInputBinding::Select,    // SDL_GAMEPAD_BUTTON_BACK
  GenericInputBinding::System,    // SDL_GAMEPAD_BUTTON_GUIDE
  GenericInputBinding::Start,     // SDL_GAMEPAD_BUTTON_START
  GenericInputBinding::L3,        // SDL_GAMEPAD_BUTTON_LEFT_STICK
  GenericInputBinding::R3,        // SDL_GAMEPAD_BUTTON_RIGHT_STICK
  GenericInputBinding::L1,        // SDL_GAMEPAD_BUTTON_LEFT_SHOULDER
  GenericInputBinding::R1,        // SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER
  GenericInputBinding::DPadUp,    // SDL_GAMEPAD_BUTTON_DPAD_UP
  GenericInputBinding::DPadDown,  // SDL_GAMEPAD_BUTTON_DPAD_DOWN
  GenericInputBinding::DPadLeft,  // SDL_GAMEPAD_BUTTON_DPAD_LEFT
  GenericInputBinding::DPadRight, // SDL_GAMEPAD_BUTTON_DPAD_RIGHT
  GenericInputBinding::Unknown,   // SDL_GAMEPAD_BUTTON_MISC1
  GenericInputBinding::Unknown,   // SDL_GAMEPAD_BUTTON_RIGHT_PADDLE1
  GenericInputBinding::Unknown,   // SDL_GAMEPAD_BUTTON_LEFT_PADDLE1
  GenericInputBinding::Unknown,   // SDL_GAMEPAD_BUTTON_RIGHT_PADDLE2
  GenericInputBinding::Unknown,   // SDL_GAMEPAD_BUTTON_LEFT_PADDLE2
  GenericInputBinding::Unknown,   // SDL_GAMEPAD_BUTTON_TOUCHPAD
};

static constexpr const char* s_sdl_hat_direction_names[] = {
  // clang-format off
	"North",
	"East",
	"South",
	"West",
  // clang-format on
};

static constexpr const char* s_sdl_default_led_colors[] = {
  "0000ff", // SDL-0
  "ff0000", // SDL-1
  "00ff00", // SDL-2
  "ffff00", // SDL-3
};

static void SetGamepadRGBLED(SDL_Gamepad* gamepad, u32 color)
{
  SDL_SetGamepadLED(gamepad, (color >> 16) & 0xff, (color >> 8) & 0xff, color & 0xff);
}

static bool GamepadHasCapability(SDL_Gamepad* gamepad, const char* property)
{
  return SDL_GetBooleanProperty(SDL_GetGamepadProperties(gamepad), property, false);
}

static void SDLLogCallback(void* userdata, int category, SDL_LogPriority priority, const char* message)
{
  static constexpr LOGLEVEL priority_map[SDL_LOG_PRIORITY_COUNT] = {
    LOGLEVEL_DEBUG,
    LOGLEVEL_DEBUG,   // SDL_LOG_PRIORITY_VERBOSE
    LOGLEVEL_DEBUG,   // SDL_LOG_PRIORITY_DEBUG
    LOGLEVEL_INFO,    // SDL_LOG_PRIORITY_INFO
    LOGLEVEL_WARNING, // SDL_LOG_PRIORITY_WARN
    LOGLEVEL_ERROR,   // SDL_LOG_PRIORITY_ERROR
    LOGLEVEL_ERROR,   // SDL_LOG_PRIORITY_CRITICAL
  };

  Log::Write("SDL", "SDL", priority_map[priority], message);
}

bool SDLInputSource::ALLOW_EVENT_POLLING = true;

SDLInputSource::SDLInputSource() = default;

SDLInputSource::~SDLInputSource()
{
  Assert(m_controllers.empty());
}

bool SDLInputSource::Initialize(SettingsInterface& si, std::unique_lock<std::mutex>& settings_lock)
{
  LoadSettings(si);
  settings_lock.unlock();
  SetHints();
  bool result = InitializeSubsystem();
  settings_lock.lock();
  return result;
}

void SDLInputSource::UpdateSettings(SettingsInterface& si, std::unique_lock<std::mutex>& settings_lock)
{
  const bool old_controller_enhanced_mode = m_controller_enhanced_mode;
  const bool old_controller_ps5_player_led = m_controller_ps5_player_led;

#ifdef __APPLE__
  const bool old_enable_iokit_driver = m_enable_iokit_driver;
  const bool old_enable_mfi_driver = m_enable_mfi_driver;
#endif

  LoadSettings(si);

#ifdef __APPLE__
  const bool drivers_changed =
    (m_enable_iokit_driver != old_enable_iokit_driver || m_enable_mfi_driver != old_enable_mfi_driver);
#else
  constexpr bool drivers_changed = false;
#endif

  if (m_controller_enhanced_mode != old_controller_enhanced_mode ||
      m_controller_ps5_player_led != old_controller_ps5_player_led ||
      drivers_changed)
  {
    settings_lock.unlock();
    ShutdownSubsystem();
    SetHints();
    InitializeSubsystem();
    settings_lock.lock();
  }
}

bool SDLInputSource::ReloadDevices()
{
  // We'll get a gamepad added/removed event here.
  PollEvents();
  return false;
}

void SDLInputSource::Shutdown()
{
  ShutdownSubsystem();
}

void SDLInputSource::LoadSettings(SettingsInterface& si)
{
  for (u32 i = 0; i < MAX_LED_COLORS; i++)
  {
    const u32 color = GetRGBForPlayerId(si, i);
    if (m_led_colors[i] == color)
      continue;

    m_led_colors[i] = color;

    const auto it = GetControllerDataForPlayerId(i);
    if (it == m_controllers.end() || !it->gamepad ||
        !GamepadHasCapability(it->gamepad, SDL_PROP_GAMEPAD_CAP_RGB_LED_BOOLEAN))
      continue;

    SetGamepadRGBLED(it->gamepad, color);
  }

  m_controller_enhanced_mode = si.GetBoolValue("InputSources", "SDLControllerEnhancedMode", false);
  m_controller_ps5_player_led = si.GetBoolValue("InputSources", "SDLPS5PlayerLED", false);
  m_sdl_hints = si.GetKeyValueList("SDLHints");

#ifdef __APPLE__
  m_enable_iokit_driver = si.GetBoolValue("InputSources", "SDLIOKitDriver", true);
  m_enable_mfi_driver = si.GetBoolValue("InputSources", "SDLMFIDriver", true);
#endif
}

u32 SDLInputSource::GetRGBForPlayerId(SettingsInterface& si, u32 player_id)
{
  return ParseRGBForPlayerId(
    si.GetStringValue("SDLExtra", fmt::format("Player{}LED", player_id).c_str(), s_sdl_default_led_colors[player_id]),
    player_id);
}

u32 SDLInputSource::ParseRGBForPlayerId(std::string_view str, u32 player_id)
{
  if (player_id >= MAX_LED_COLORS)
    return 0;

  const u32 default_color = StringUtil::FromChars<u32>(s_sdl_default_led_colors[player_id], 16).value_or(0);
  const u32 color = StringUtil::FromChars<u32>(str, 16).value_or(default_color);

  return color;
}

void SDLInputSource::SetHints()
{
  if (const std::string upath = Path::Combine(EmuFolders::DataRoot, CONTROLLER_DB_FILENAME);
      FileSystem::FileExists(upath.c_str()))
  {
    INFO_LOG("Using Controller DB from user directory: '{}'", upath);
    SDL_SetHint(SDL_HINT_GAMECONTROLLERCONFIG_FILE, upath.c_str());
  }
  else if (const std::string rpath = EmuFolders::GetOverridableResourcePath(CONTROLLER_DB_FILENAME);
           FileSystem::FileExists(rpath.c_str()))
  {
    INFO_LOG("Using Controller DB from resources.");
    SDL_SetHint(SDL_HINT_GAMECONTROLLERCONFIG_FILE, rpath.c_str());
  }
  else
  {
    ERROR_LOG("Controller DB not found, it should be named '{}'", CONTROLLER_DB_FILENAME);
  }

  SDL_SetHint(SDL_HINT_JOYSTICK_ENHANCED_REPORTS, m_controller_enhanced_mode ? "1" : "0");
  SDL_SetHint(SDL_HINT_JOYSTICK_HIDAPI_PS5_PLAYER_LED, m_controller_ps5_player_led ? "1" : "0");
  SDL_SetHint(SDL_HINT_JOYSTICK_HIDAPI_WII, "1");
  SDL_SetHint(SDL_HINT_JOYSTICK_HIDAPI_PS3, "1");

#ifdef __APPLE__
  INFO_LOG("IOKit is {}, MFI is {}.", m_enable_iokit_driver ? "enabled" : "disabled",
           m_enable_mfi_driver ? "enabled" : "disabled");
  SDL_SetHint(SDL_HINT_JOYSTICK_IOKIT, m_enable_iokit_driver ? "1" : "0");
  SDL_SetHint(SDL_HINT_JOYSTICK_MFI, m_enable_mfi_driver ? "1" : "0");
#endif

  for (const std::pair<std::string, std::string>& hint : m_sdl_hints)
    SDL_SetHint(hint.first.c_str(), hint.second.c_str());
}

bool SDLInputSource::InitializeSubsystem()
{
  if (!SDL_InitSubSystem(SDL_INIT_JOYSTICK | SDL_INIT_GAMEPAD | SDL_INIT_HAPTIC))
  {
    ERROR_LOG("SDL_InitSubSystem(SDL_INIT_JOYSTICK | SDL_INIT_GAMEPAD | SDL_INIT_HAPTIC) failed");
    return false;
  }

  SDL_SetLogOutputFunction(SDLLogCallback, nullptr);
#ifdef _DEBUG
  SDL_SetLogPriorities(SDL_LOG_PRIORITY_VERBOSE);
#else
  SDL_SetLogPriorities(SDL_LOG_PRIORITY_INFO);
#endif

  m_sdl_subsystem_initialized = true;

  int joystick_count = 0;
  SDL_JoystickID* joystick_ids = SDL_GetJoysticks(&joystick_count);
  for (int i = 0; i < joystick_count; i++)
    OpenDevice(joystick_ids[i], SDL_IsGamepad(joystick_ids[i]));
  SDL_free(joystick_ids);

  int gamepad_mapping_count = 0;
  char** gamepad_mappings = SDL_GetGamepadMappings(&gamepad_mapping_count);
  SDL_free(gamepad_mappings);
  INFO_LOG("{} gamepad mappings are loaded.", gamepad_mapping_count);
  return true;
}

void SDLInputSource::ShutdownSubsystem()
{
  while (!m_controllers.empty())
    CloseDevice(m_controllers.begin()->joystick_id);

  if (m_sdl_subsystem_initialized)
  {
    SDL_QuitSubSystem(SDL_INIT_JOYSTICK | SDL_INIT_GAMEPAD | SDL_INIT_HAPTIC);
    m_sdl_subsystem_initialized = false;
  }
}

void SDLInputSource::PollEvents()
{
  if (!ALLOW_EVENT_POLLING)
    return;

  for (;;)
  {
    SDL_Event ev;
    if (SDL_PollEvent(&ev))
      ProcessSDLEvent(&ev);
    else
      break;
  }
}

std::vector<std::pair<std::string, std::string>> SDLInputSource::EnumerateDevices()
{
  std::vector<std::pair<std::string, std::string>> ret;

  for (const ControllerData& cd : m_controllers)
  {
    std::string id = fmt::format("SDL-{}", cd.player_id);

    const char* name = cd.gamepad ? SDL_GetGamepadName(cd.gamepad) : SDL_GetJoystickName(cd.joystick);
    if (name)
      ret.emplace_back(std::move(id), name);
    else
      ret.emplace_back(std::move(id), "Unknown Device");
  }

  return ret;
}

std::optional<InputBindingKey> SDLInputSource::ParseKeyString(std::string_view device, std::string_view binding)
{
  if (!device.starts_with("SDL-") || binding.empty())
    return std::nullopt;

  const std::optional<s32> player_id = StringUtil::FromChars<s32>(device.substr(4));
  if (!player_id.has_value() || player_id.value() < 0)
    return std::nullopt;

  InputBindingKey key = {};
  key.source_type = InputSourceType::SDL;
  key.source_index = static_cast<u32>(player_id.value());

  if (binding.ends_with("Motor"))
  {
    key.source_subtype = InputSubclass::ControllerMotor;
    if (binding == "LargeMotor")
    {
      key.data = 0;
      return key;
    }
    else if (binding == "SmallMotor")
    {
      key.data = 1;
      return key;
    }
    else
    {
      return std::nullopt;
    }
  }
  else if (binding.ends_with("Haptic"))
  {
    key.source_subtype = InputSubclass::ControllerHaptic;
    key.data = 0;
    return key;
  }
  else if (binding[0] == '+' || binding[0] == '-')
  {
    // likely an axis
    const std::string_view axis_name(binding.substr(1));

    if (axis_name.starts_with("Axis"))
    {
      std::string_view end;
      if (auto value = StringUtil::FromChars<u32>(axis_name.substr(4), 10, &end))
      {
        key.source_subtype = InputSubclass::ControllerAxis;
        key.data = *value + static_cast<u32>(std::size(s_sdl_axis_names));
        key.modifier = (binding[0] == '-') ? InputModifier::Negate : InputModifier::None;
        key.invert = (end == "~");
        return key;
      }
    }
    for (u32 i = 0; i < std::size(s_sdl_axis_names); i++)
    {
      if (axis_name == s_sdl_axis_names[i])
      {
        // found an axis!
        key.source_subtype = InputSubclass::ControllerAxis;
        key.data = i;
        key.modifier = (binding[0] == '-') ? InputModifier::Negate : InputModifier::None;
        return key;
      }
    }
  }
  else if (binding.starts_with("FullAxis"))
  {
    std::string_view end;
    if (auto value = StringUtil::FromChars<u32>(binding.substr(8), 10, &end))
    {
      key.source_subtype = InputSubclass::ControllerAxis;
      key.data = *value + static_cast<u32>(std::size(s_sdl_axis_names));
      key.modifier = InputModifier::FullAxis;
      key.invert = (end == "~");
      return key;
    }
  }
  else if (binding.starts_with("Hat"))
  {
    std::string_view hat_dir;
    if (auto value = StringUtil::FromChars<u32>(binding.substr(3), 10, &hat_dir); value.has_value() && !hat_dir.empty())
    {
      for (u8 dir = 0; dir < static_cast<u8>(std::size(s_sdl_hat_direction_names)); dir++)
      {
        if (hat_dir == s_sdl_hat_direction_names[dir])
        {
          key.source_subtype = InputSubclass::ControllerHat;
          key.data = value.value() * static_cast<u32>(std::size(s_sdl_hat_direction_names)) + dir;
          return key;
        }
      }
    }
  }
  else
  {
    // must be a button
    if (binding.starts_with("Button"))
    {
      if (auto value = StringUtil::FromChars<u32>(binding.substr(6)))
      {
        key.source_subtype = InputSubclass::ControllerButton;
        key.data = *value + static_cast<u32>(std::size(s_sdl_button_names));
        return key;
      }
    }
    for (u32 i = 0; i < std::size(s_sdl_button_names); i++)
    {
      if (binding == s_sdl_button_names[i])
      {
        key.source_subtype = InputSubclass::ControllerButton;
        key.data = i;
        return key;
      }
    }
  }

  // unknown axis/button
  return std::nullopt;
}

TinyString SDLInputSource::ConvertKeyToString(InputBindingKey key)
{
  TinyString ret;

  if (key.source_type == InputSourceType::SDL)
  {
    if (key.source_subtype == InputSubclass::ControllerAxis)
    {
      const char* modifier =
        (key.modifier == InputModifier::FullAxis ? "Full" : (key.modifier == InputModifier::Negate ? "-" : "+"));
      if (key.data < std::size(s_sdl_axis_names))
      {
        ret.format("SDL-{}/{}{}", static_cast<u32>(key.source_index), modifier, s_sdl_axis_names[key.data]);
      }
      else
      {
        ret.format("SDL-{}/{}Axis{}{}", static_cast<u32>(key.source_index), modifier,
                   key.data - static_cast<u32>(std::size(s_sdl_axis_names)), key.invert ? "~" : "");
      }
    }
    else if (key.source_subtype == InputSubclass::ControllerButton)
    {
      if (key.data < std::size(s_sdl_button_names))
      {
        ret.format("SDL-{}/{}", static_cast<u32>(key.source_index), s_sdl_button_names[key.data]);
      }
      else
      {
        ret.format("SDL-{}/Button{}", static_cast<u32>(key.source_index),
                   key.data - static_cast<u32>(std::size(s_sdl_button_names)));
      }
    }
    else if (key.source_subtype == InputSubclass::ControllerHat)
    {
      const u32 hat_index = key.data / static_cast<u32>(std::size(s_sdl_hat_direction_names));
      const u32 hat_direction = key.data % static_cast<u32>(std::size(s_sdl_hat_direction_names));
      ret.format("SDL-{}/Hat{}{}", static_cast<u32>(key.source_index), hat_index,
                 s_sdl_hat_direction_names[hat_direction]);
    }
    else if (key.source_subtype == InputSubclass::ControllerMotor)
    {
      ret.format("SDL-{}/{}Motor", static_cast<u32>(key.source_index), key.data ? "Large" : "Small");
    }
    else if (key.source_subtype == InputSubclass::ControllerHaptic)
    {
      ret.format("SDL-{}/Haptic", static_cast<u32>(key.source_index));
    }
  }

  return ret;
}

TinyString SDLInputSource::ConvertKeyToIcon(InputBindingKey key)
{
  TinyString ret;

  if (key.source_type == InputSourceType::SDL)
  {
    if (key.source_subtype == InputSubclass::ControllerAxis)
    {
      if (key.data < std::size(s_sdl_axis_icons) && key.modifier != InputModifier::FullAxis)
      {
        ret.format("SDL-{}  {}", static_cast<u32>(key.source_index),
                   s_sdl_axis_icons[key.data][key.modifier == InputModifier::None]);
      }
    }
    else if (key.source_subtype == InputSubclass::ControllerButton)
    {
      if (key.data < std::size(s_sdl_button_icons))
        ret.format("SDL-{}  {}", static_cast<u32>(key.source_index), s_sdl_button_icons[key.data]);
    }
  }

  return ret;
}

bool SDLInputSource::IsHandledInputEvent(const SDL_Event* ev)
{
  switch (ev->type)
  {
    case SDL_EVENT_GAMEPAD_ADDED:
    case SDL_EVENT_GAMEPAD_REMOVED:
    case SDL_EVENT_JOYSTICK_ADDED:
    case SDL_EVENT_JOYSTICK_REMOVED:
    case SDL_EVENT_GAMEPAD_AXIS_MOTION:
    case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
    case SDL_EVENT_GAMEPAD_BUTTON_UP:
    case SDL_EVENT_JOYSTICK_AXIS_MOTION:
    case SDL_EVENT_JOYSTICK_BUTTON_DOWN:
    case SDL_EVENT_JOYSTICK_BUTTON_UP:
    case SDL_EVENT_JOYSTICK_HAT_MOTION:
      return true;

    default:
      return false;
  }
}

bool SDLInputSource::ProcessSDLEvent(const SDL_Event* event)
{
  switch (event->type)
  {
    case SDL_EVENT_GAMEPAD_ADDED:
    {
      INFO_LOG("Controller {} inserted", event->gdevice.which);
      OpenDevice(event->gdevice.which, true);
      return true;
    }

    case SDL_EVENT_GAMEPAD_REMOVED:
    {
      INFO_LOG("Controller {} removed", event->gdevice.which);
      CloseDevice(event->gdevice.which);
      return true;
    }

    case SDL_EVENT_JOYSTICK_ADDED:
    {
      // Let game controller handle.. well.. game controllers.
      if (SDL_IsGamepad(event->jdevice.which))
        return false;

      INFO_LOG("Joystick {} inserted", event->jdevice.which);
      OpenDevice(event->jdevice.which, false);
      return true;
    }
    break;

    case SDL_EVENT_JOYSTICK_REMOVED:
    {
      if (auto it = GetControllerDataForJoystickId(event->jdevice.which);
          it != m_controllers.end() && it->gamepad)
        return false;

      INFO_LOG("Joystick {} removed", event->jdevice.which);
      CloseDevice(event->jdevice.which);
      return true;
    }

    case SDL_EVENT_GAMEPAD_AXIS_MOTION:
      return HandleGamepadAxisEvent(&event->gaxis);

    case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
    case SDL_EVENT_GAMEPAD_BUTTON_UP:
      return HandleGamepadButtonEvent(&event->gbutton);

    case SDL_EVENT_JOYSTICK_AXIS_MOTION:
      return HandleJoystickAxisEvent(&event->jaxis);

    case SDL_EVENT_JOYSTICK_BUTTON_DOWN:
    case SDL_EVENT_JOYSTICK_BUTTON_UP:
      return HandleJoystickButtonEvent(&event->jbutton);

    case SDL_EVENT_JOYSTICK_HAT_MOTION:
      return HandleJoystickHatEvent(&event->jhat);

    default:
      return false;
  }
}

SDL_Joystick* SDLInputSource::GetJoystickForDevice(std::string_view device)
{
  if (!device.starts_with("SDL-"))
    return nullptr;

  const std::optional<s32> player_id = StringUtil::FromChars<s32>(device.substr(4));
  if (!player_id.has_value() || player_id.value() < 0)
    return nullptr;

  auto it = GetControllerDataForPlayerId(player_id.value());
  if (it == m_controllers.end())
    return nullptr;

  return it->joystick;
}

SDLInputSource::ControllerDataVector::iterator SDLInputSource::GetControllerDataForJoystickId(SDL_JoystickID id)
{
  return std::find_if(m_controllers.begin(), m_controllers.end(),
                      [id](const ControllerData& cd) { return cd.joystick_id == id; });
}

SDLInputSource::ControllerDataVector::iterator SDLInputSource::GetControllerDataForPlayerId(int id)
{
  return std::find_if(m_controllers.begin(), m_controllers.end(),
                      [id](const ControllerData& cd) { return cd.player_id == id; });
}

int SDLInputSource::GetFreePlayerId() const
{
  for (int player_id = 0;; player_id++)
  {
    size_t i;
    for (i = 0; i < m_controllers.size(); i++)
    {
      if (m_controllers[i].player_id == player_id)
        break;
    }
    if (i == m_controllers.size())
      return player_id;
  }

  return 0;
}

bool SDLInputSource::OpenDevice(SDL_JoystickID instance_id, bool is_gamepad)
{
  if (GetControllerDataForJoystickId(instance_id) != m_controllers.end())
    return true;

  SDL_Gamepad* gcontroller;
  SDL_Joystick* joystick;

  if (is_gamepad)
  {
    gcontroller = SDL_OpenGamepad(instance_id);
    joystick = gcontroller ? SDL_GetGamepadJoystick(gcontroller) : nullptr;
  }
  else
  {
    gcontroller = nullptr;
    joystick = SDL_OpenJoystick(instance_id);
  }

  if (!gcontroller && !joystick)
  {
    ERROR_LOG("Failed to open controller {}", instance_id);
    if (gcontroller)
      SDL_CloseGamepad(gcontroller);

    return false;
  }

  const SDL_JoystickID joystick_id = SDL_GetJoystickID(joystick);
  int player_id = gcontroller ? SDL_GetGamepadPlayerIndex(gcontroller) : SDL_GetJoystickPlayerIndex(joystick);
  if (player_id < 0 || GetControllerDataForPlayerId(player_id) != m_controllers.end())
  {
    const int free_player_id = GetFreePlayerId();
    WARNING_LOG("Controller {} (joystick {}) returned player ID {}, which is invalid or in use. Using ID {} instead.",
                instance_id, joystick_id, player_id, free_player_id);
    player_id = free_player_id;
  }

  const char* name = gcontroller ? SDL_GetGamepadName(gcontroller) : SDL_GetJoystickName(joystick);
  if (!name)
    name = "Unknown Device";

  VERBOSE_LOG("Opened {} {} (instance id {}, player id {}): {}", is_gamepad ? "gamepad" : "joystick",
              instance_id, joystick_id, player_id, name);

  ControllerData cd = {};
  cd.player_id = player_id;
  cd.joystick_id = joystick_id;
  cd.haptic_left_right_effect = -1;
  cd.gamepad = gcontroller;
  cd.joystick = joystick;

  if (gcontroller)
  {
    const int num_axes = SDL_GetNumJoystickAxes(joystick);
    const int num_buttons = SDL_GetNumJoystickButtons(joystick);
    cd.joy_axis_used_in_gamepad.resize(num_axes, false);
    cd.joy_button_used_in_gamepad.resize(num_buttons, false);

    int binding_count = 0;
    SDL_GamepadBinding** bindings = SDL_GetGamepadBindings(gcontroller, &binding_count);
    for (int i = 0; bindings && i < binding_count; i++)
    {
      const SDL_GamepadBinding& binding = *bindings[i];
      if (binding.input_type == SDL_GAMEPAD_BINDTYPE_AXIS && binding.input.axis.axis < num_axes)
        cd.joy_axis_used_in_gamepad[binding.input.axis.axis] = true;
      else if (binding.input_type == SDL_GAMEPAD_BINDTYPE_BUTTON && binding.input.button < num_buttons)
        cd.joy_button_used_in_gamepad[binding.input.button] = true;
    }
    SDL_free(bindings);

    VERBOSE_LOG("Gamepad {} has {} axes and {} buttons", player_id, num_axes, num_buttons);
  }
  else
  {
    // Gamepads don't have the concept of hats, so we only need to do this for joysticks.
    const int num_hats = SDL_GetNumJoystickHats(joystick);
    if (num_hats > 0)
      cd.last_hat_state.resize(static_cast<size_t>(num_hats), u8(0));

    VERBOSE_LOG("Joystick {} has {} axes, {} buttons and {} hats", player_id, SDL_GetNumJoystickAxes(joystick),
                SDL_GetNumJoystickButtons(joystick), num_hats);
  }

  cd.use_gamepad_rumble =
    (gcontroller && GamepadHasCapability(gcontroller, SDL_PROP_GAMEPAD_CAP_RUMBLE_BOOLEAN));
  if (cd.use_gamepad_rumble)
  {
    VERBOSE_LOG("Rumble is supported on '{}' via gamepad", name);
  }
  else if (!gcontroller)
  {
    SDL_Haptic* haptic = SDL_OpenHapticFromJoystick(joystick);
    if (haptic)
    {
      SDL_HapticEffect ef = {};
      ef.leftright.type = SDL_HAPTIC_LEFTRIGHT;
      ef.leftright.length = 1000;

      const SDL_HapticEffectID ef_id = SDL_CreateHapticEffect(haptic, &ef);
      if (ef_id >= 0)
      {
        cd.haptic = haptic;
        cd.haptic_left_right_effect = ef_id;
      }
      else
      {
        ERROR_LOG("Failed to create haptic left/right effect: {}", SDL_GetError());
        if (SDL_HapticRumbleSupported(haptic) && SDL_InitHapticRumble(haptic))
        {
          cd.haptic = haptic;
        }
        else
        {
          ERROR_LOG("No haptic rumble supported: {}", SDL_GetError());
          SDL_CloseHaptic(haptic);
        }
      }
    }

    if (cd.haptic)
      VERBOSE_LOG("Rumble is supported on '{}' via haptic", name);
  }

  if (!cd.haptic && !cd.use_gamepad_rumble)
    VERBOSE_LOG("Rumble is not supported on '{}'", name);

  if (player_id >= 0 && static_cast<u32>(player_id) < MAX_LED_COLORS && gcontroller &&
      GamepadHasCapability(gcontroller, SDL_PROP_GAMEPAD_CAP_RGB_LED_BOOLEAN))
  {
    SetGamepadRGBLED(gcontroller, m_led_colors[player_id]);
  }

  m_controllers.push_back(std::move(cd));

  InputManager::OnInputDeviceConnected(fmt::format("SDL-{}", player_id), name);
  return true;
}

bool SDLInputSource::CloseDevice(SDL_JoystickID instance_id)
{
  auto it = GetControllerDataForJoystickId(instance_id);
  if (it == m_controllers.end())
    return false;

  InputManager::OnInputDeviceDisconnected(
    InputBindingKey{{.source_type = InputSourceType::SDL, .source_index = static_cast<u32>(it->player_id)}},
    fmt::format("SDL-{}", it->player_id));

  if (it->haptic)
    SDL_CloseHaptic(it->haptic);

  if (it->gamepad)
    SDL_CloseGamepad(it->gamepad);
  else
    SDL_CloseJoystick(it->joystick);

  m_controllers.erase(it);
  return true;
}

static float NormalizeS16(s16 value)
{
  return static_cast<float>(value) / (value < 0 ? 32768.0f : 32767.0f);
}

bool SDLInputSource::HandleGamepadAxisEvent(const SDL_GamepadAxisEvent* ev)
{
  auto it = GetControllerDataForJoystickId(ev->which);
  if (it == m_controllers.end())
    return false;

  const InputBindingKey key(MakeGenericControllerAxisKey(InputSourceType::SDL, it->player_id, ev->axis));
  InputManager::InvokeEvents(key, NormalizeS16(ev->value));
  return true;
}

bool SDLInputSource::HandleGamepadButtonEvent(const SDL_GamepadButtonEvent* ev)
{
  auto it = GetControllerDataForJoystickId(ev->which);
  if (it == m_controllers.end())
    return false;

  const InputBindingKey key(MakeGenericControllerButtonKey(InputSourceType::SDL, it->player_id, ev->button));
  const GenericInputBinding generic_key = (ev->button < std::size(s_sdl_generic_binding_button_mapping)) ?
                                            s_sdl_generic_binding_button_mapping[ev->button] :
                                            GenericInputBinding::Unknown;
  InputManager::InvokeEvents(key, ev->down ? 1.0f : 0.0f, generic_key);
  return true;
}

bool SDLInputSource::HandleJoystickAxisEvent(const SDL_JoyAxisEvent* ev)
{
  auto it = GetControllerDataForJoystickId(ev->which);
  if (it == m_controllers.end())
    return false;
  if (ev->axis < it->joy_axis_used_in_gamepad.size() && it->joy_axis_used_in_gamepad[ev->axis])
    return false;                                                            // Will get handled by gamepad event
  const u32 axis = ev->axis + static_cast<u32>(std::size(s_sdl_axis_names)); // Ensure we don't conflict with GC axes
  const InputBindingKey key(MakeGenericControllerAxisKey(InputSourceType::SDL, it->player_id, axis));
  InputManager::InvokeEvents(key, NormalizeS16(ev->value));
  return true;
}

bool SDLInputSource::HandleJoystickButtonEvent(const SDL_JoyButtonEvent* ev)
{
  auto it = GetControllerDataForJoystickId(ev->which);
  if (it == m_controllers.end())
    return false;
  if (ev->button < it->joy_button_used_in_gamepad.size() && it->joy_button_used_in_gamepad[ev->button])
    return false; // Will get handled by gamepad event
  const u32 button =
    ev->button + static_cast<u32>(std::size(s_sdl_button_names)); // Ensure we don't conflict with GC buttons
  const InputBindingKey key(MakeGenericControllerButtonKey(InputSourceType::SDL, it->player_id, button));
  InputManager::InvokeEvents(key, ev->down ? 1.0f : 0.0f);
  return true;
}

bool SDLInputSource::HandleJoystickHatEvent(const SDL_JoyHatEvent* ev)
{
  auto it = GetControllerDataForJoystickId(ev->which);
  if (it == m_controllers.end() || ev->hat >= it->last_hat_state.size())
    return false;

  const unsigned long last_direction = it->last_hat_state[ev->hat];
  it->last_hat_state[ev->hat] = ev->value;

  unsigned long changed_direction = last_direction ^ ev->value;
  while (changed_direction != 0)
  {
    const u32 pos = CountTrailingZeros(changed_direction);

    const unsigned long mask = (1u << pos);
    changed_direction &= ~mask;

    const InputBindingKey key(MakeGenericControllerHatKey(InputSourceType::SDL, it->player_id, ev->hat,
                                                          static_cast<u8>(pos),
                                                          static_cast<u32>(std::size(s_sdl_hat_direction_names))));
    InputManager::InvokeEvents(key, (last_direction & mask) ? 0.0f : 1.0f);
  }

  return true;
}

std::vector<InputBindingKey> SDLInputSource::EnumerateMotors()
{
  std::vector<InputBindingKey> ret;

  InputBindingKey key = {};
  key.source_type = InputSourceType::SDL;

  for (ControllerData& cd : m_controllers)
  {
    key.source_index = cd.player_id;

    if (cd.use_gamepad_rumble || cd.haptic_left_right_effect)
    {
      // two motors
      key.source_subtype = InputSubclass::ControllerMotor;
      key.data = 0;
      ret.push_back(key);
      key.data = 1;
      ret.push_back(key);
    }
    else if (cd.haptic)
    {
      // haptic effect
      key.source_subtype = InputSubclass::ControllerHaptic;
      key.data = 0;
      ret.push_back(key);
    }
  }

  return ret;
}

bool SDLInputSource::GetGenericBindingMapping(std::string_view device, GenericInputBindingMapping* mapping)
{
  if (!device.starts_with("SDL-"))
    return false;

  const std::optional<s32> player_id = StringUtil::FromChars<s32>(device.substr(4));
  if (!player_id.has_value() || player_id.value() < 0)
    return false;

  ControllerDataVector::iterator it = GetControllerDataForPlayerId(player_id.value());
  if (it == m_controllers.end())
    return false;

  if (it->gamepad)
  {
    // assume all buttons are present.
    const s32 pid = player_id.value();
    for (u32 i = 0; i < std::size(s_sdl_generic_binding_axis_mapping); i++)
    {
      const GenericInputBinding negative = s_sdl_generic_binding_axis_mapping[i][0];
      const GenericInputBinding positive = s_sdl_generic_binding_axis_mapping[i][1];
      if (negative != GenericInputBinding::Unknown)
        mapping->emplace_back(negative, fmt::format("SDL-{}/-{}", pid, s_sdl_axis_names[i]));

      if (positive != GenericInputBinding::Unknown)
        mapping->emplace_back(positive, fmt::format("SDL-{}/+{}", pid, s_sdl_axis_names[i]));
    }
    for (u32 i = 0; i < std::size(s_sdl_generic_binding_button_mapping); i++)
    {
      const GenericInputBinding binding = s_sdl_generic_binding_button_mapping[i];
      if (binding != GenericInputBinding::Unknown)
        mapping->emplace_back(binding, fmt::format("SDL-{}/{}", pid, s_sdl_button_names[i]));
    }

    if (it->use_gamepad_rumble || it->haptic_left_right_effect >= 0)
    {
      mapping->emplace_back(GenericInputBinding::SmallMotor, fmt::format("SDL-{}/SmallMotor", pid));
      mapping->emplace_back(GenericInputBinding::LargeMotor, fmt::format("SDL-{}/LargeMotor", pid));
    }
    // R'Lyeh Contributors: SDL3 gamepad rumble and raw joystick haptics are separate capabilities.
    // Do not offer haptic bindings to a gamepad unless it has an opened haptic device.
    else if (it->haptic)
    {
      mapping->emplace_back(GenericInputBinding::SmallMotor, fmt::format("SDL-{}/Haptic", pid));
      mapping->emplace_back(GenericInputBinding::LargeMotor, fmt::format("SDL-{}/Haptic", pid));
    }

    return true;
  }
  else
  {
    // joysticks have arbitrary axis numbers, so automapping isn't going to work here.
    return false;
  }
}

void SDLInputSource::UpdateMotorState(InputBindingKey key, float intensity)
{
  if (key.source_subtype != InputSubclass::ControllerMotor && key.source_subtype != InputSubclass::ControllerHaptic)
    return;

  auto it = GetControllerDataForPlayerId(key.source_index);
  if (it == m_controllers.end())
    return;

  it->rumble_intensity[key.data] = static_cast<u16>(intensity * 65535.0f);
  SendRumbleUpdate(&(*it));
}

void SDLInputSource::UpdateMotorState(InputBindingKey large_key, InputBindingKey small_key, float large_intensity,
                                      float small_intensity)
{
  if (large_key.source_index != small_key.source_index || large_key.source_subtype != InputSubclass::ControllerMotor ||
      small_key.source_subtype != InputSubclass::ControllerMotor)
  {
    // bonkers config where they're mapped to different controllers... who would do such a thing?
    UpdateMotorState(large_key, large_intensity);
    UpdateMotorState(small_key, small_intensity);
    return;
  }

  auto it = GetControllerDataForPlayerId(large_key.source_index);
  if (it == m_controllers.end())
    return;

  it->rumble_intensity[large_key.data] = static_cast<u16>(large_intensity * 65535.0f);
  it->rumble_intensity[small_key.data] = static_cast<u16>(small_intensity * 65535.0f);
  SendRumbleUpdate(&(*it));
}

void SDLInputSource::SendRumbleUpdate(ControllerData* cd)
{
  // we'll update before this duration is elapsed
  static constexpr u32 DURATION = 65535; // SDL_MAX_RUMBLE_DURATION_MS

  if (cd->use_gamepad_rumble)
  {
    SDL_RumbleGamepad(cd->gamepad, cd->rumble_intensity[0], cd->rumble_intensity[1], DURATION);
    return;
  }

  if (cd->haptic_left_right_effect >= 0)
  {
    if ((static_cast<u32>(cd->rumble_intensity[0]) + static_cast<u32>(cd->rumble_intensity[1])) > 0)
    {
      SDL_HapticEffect ef;
      ef.type = SDL_HAPTIC_LEFTRIGHT;
      ef.leftright.large_magnitude = cd->rumble_intensity[0];
      ef.leftright.small_magnitude = cd->rumble_intensity[1];
      ef.leftright.length = DURATION;
      SDL_UpdateHapticEffect(cd->haptic, cd->haptic_left_right_effect, &ef);
      SDL_RunHapticEffect(cd->haptic, cd->haptic_left_right_effect, SDL_HAPTIC_INFINITY);
    }
    else
    {
      SDL_StopHapticEffect(cd->haptic, cd->haptic_left_right_effect);
    }
  }
  else
  {
    const float strength =
      static_cast<float>(std::max(cd->rumble_intensity[0], cd->rumble_intensity[1])) * (1.0f / 65535.0f);
    if (strength > 0.0f)
      SDL_PlayHapticRumble(cd->haptic, strength, DURATION);
    else
      SDL_StopHapticRumble(cd->haptic);
  }
}

std::unique_ptr<InputSource> InputSource::CreateSDLSource()
{
  return std::make_unique<SDLInputSource>();
}
