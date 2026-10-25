// SPDX-FileCopyrightText: 2026 RLyehPSX <https://github.com/psychocodermonkey/RLyehPSX>
// SPDX-License-Identifier: GPL-3.0-only
//
// This implementation was developed for Project R'lyehPSX as an independent
// implementation of the audio subsystem.
//
// Public interfaces, behavior, and integration points were designed to remain compatible
// with the surrounding emulator architecture and existing callers.
//
// Similarities in function signatures, data structures, control flow, and observable
// behavior reflect compatibility and integration requirements derived from the surrounding
// codebase rather than shared implementation code.
//

#include "audio_stream.h"

#include "audio_stream_channel_maps.inl"
#include "host.h"

#include "common/assert.h"
#include "common/error.h"
#include "common/log.h"
#include "common/settings_interface.h"
#include "common/string_util.h"

#include "kiss_fftr.h"
#include "SoundTouchDLL.h"

#include <algorithm>
#include <array>
#include <bit>
#include <cmath>
#include <cstring>
#include <limits>

Log_SetChannel(AudioStream);

namespace {

struct ExpansionChannelSetup
{
  const ExpandLUT* channel_lut;
  const s8* channel_xsf;
  u8 output_channels;
  bool has_lfe;
};

static constexpr std::array<ExpansionChannelSetup, static_cast<size_t>(AudioExpansionMode::Count)>
  s_expansion_channel_count = {{
    {nullptr, nullptr, 2, false},
    {CHANNEL_LUT_STEREO, CHANNEL_LUT_STEREO_XSF, 3, true},
    {CHANNEL_LUT_4POINT1, CHANNEL_LUT_4POINT1_XSF, 4, false},
    {CHANNEL_LUT_4POINT1, CHANNEL_LUT_4POINT1_XSF, 5, true},
    {CHANNEL_LUT_5POINT1, CHANNEL_LUT_5POINT1_XSF, 6, true},
    {CHANNEL_LUT_7POINT1, CHANNEL_LUT_7POINT1_XSF, 8, true},
  }};

#ifdef __ANDROID__
static constexpr std::array<const char*, 1> s_backend_names = {{"Null"}};
static constexpr std::array<const char*, 1> s_backend_display_names = {{"Null (No Output)"}};
#else
static constexpr std::array<const char*, 3> s_backend_names = {{"Null", "Cubeb", "SDL"}};
static constexpr std::array<const char*, 3> s_backend_display_names = {
  {"Null (No Output)", "Cubeb", "SDL"}};
#endif

static constexpr std::array<const char*, 6> s_expansion_mode_names = {
  {"Disabled", "StereoLFE", "Quadraphonic", "QuadraphonicLFE", "Surround51", "Surround71"}};
static constexpr std::array<const char*, 6> s_expansion_mode_display_names = {
  {"Disabled (Stereo)", "Stereo with LFE", "Quadraphonic", "Quadraphonic with LFE", "5.1 Surround",
   "7.1 Surround"}};
static constexpr std::array<const char*, 3> s_stretch_mode_names = {{"None", "Resample", "TimeStretch"}};
static constexpr std::array<const char*, 3> s_stretch_mode_display_names = {
  {"Off (Noisy)", "Resampling (Pitch Shift)", "Time Stretch (Tempo Change, Best Sound)"}};

template<typename Enum, size_t N>
std::optional<Enum> ParseName(const char* name, const std::array<const char*, N>& names)
{
  if (!name)
    return std::nullopt;

  for (u32 i = 0; i < names.size(); i++)
  {
    if (StringUtil::Strcasecmp(names[i], name) == 0)
      return static_cast<Enum>(i);
  }

  return std::nullopt;
}

template<typename T>
T SaturateUnsigned(u32 value)
{
  return static_cast<T>(std::min<u32>(value, std::numeric_limits<T>::max()));
}

static void S16ChunkToFloat(const s16* src, float* dest, u32 samples)
{
  constexpr float scale = 1.0f / 32767.0f;
  for (u32 i = 0; i < samples; i++)
    dest[i] = static_cast<float>(src[i]) * scale;
}

static void FloatChunkToS16(s16* dest, const float* src, u32 samples)
{
  for (u32 i = 0; i < samples; i++)
  {
    const float value = std::clamp(src[i] * 32767.0f, -32768.0f, 32767.0f);
    dest[i] = static_cast<s16>(std::lrint(value));
  }
}

static float WrapUnit(float value)
{
  value = std::fmod(value, 1.0f);
  return (value < 0.0f) ? value + 1.0f : value;
}

} // namespace

AudioStream::DeviceInfo::DeviceInfo(std::string name_, std::string display_name_, u32 minimum_latency_frames_)
  : name(std::move(name_)), display_name(std::move(display_name_)), minimum_latency_frames(minimum_latency_frames_)
{
}

AudioStream::DeviceInfo::~DeviceInfo() = default;

void AudioStreamParameters::Load(SettingsInterface& si, const char* section)
{
  stretch_mode = AudioStream::ParseStretchMode(
                   si.GetStringValue(section, "StretchMode", AudioStream::GetStretchModeName(DEFAULT_STRETCH_MODE))
                     .c_str())
                   .value_or(DEFAULT_STRETCH_MODE);
  expansion_mode =
    AudioStream::ParseExpansionMode(
      si.GetStringValue(section, "ExpansionMode", AudioStream::GetExpansionModeName(DEFAULT_EXPANSION_MODE)).c_str())
      .value_or(DEFAULT_EXPANSION_MODE);
  output_latency_ms = SaturateUnsigned<u16>(si.GetUIntValue(section, "OutputLatencyMS", DEFAULT_OUTPUT_LATENCY_MS));
  output_latency_minimal =
    si.GetBoolValue(section, "OutputLatencyMinimal", DEFAULT_OUTPUT_LATENCY_MINIMAL);
  buffer_ms = SaturateUnsigned<u16>(si.GetUIntValue(section, "BufferMS", DEFAULT_BUFFER_MS));

  stretch_sequence_length_ms =
    SaturateUnsigned<u16>(si.GetUIntValue(section, "StretchSequenceLengthMS", DEFAULT_STRETCH_SEQUENCE_LENGTH));
  stretch_seekwindow_ms =
    SaturateUnsigned<u16>(si.GetUIntValue(section, "StretchSeekWindowMS", DEFAULT_STRETCH_SEEKWINDOW));
  stretch_overlap_ms = SaturateUnsigned<u16>(si.GetUIntValue(section, "StretchOverlapMS", DEFAULT_STRETCH_OVERLAP));
  stretch_use_quickseek = si.GetBoolValue(section, "StretchUseQuickSeek", DEFAULT_STRETCH_USE_QUICKSEEK);
  stretch_use_aa_filter = si.GetBoolValue(section, "StretchUseAAFilter", DEFAULT_STRETCH_USE_AA_FILTER);

  const u32 requested_block_size = si.GetUIntValue(section, "ExpandBlockSize", DEFAULT_EXPAND_BLOCK_SIZE);
  expand_block_size = static_cast<u16>(std::clamp(
    std::bit_ceil(std::max(requested_block_size, AudioStream::MIN_EXPANSION_BLOCK_SIZE)),
    AudioStream::MIN_EXPANSION_BLOCK_SIZE, AudioStream::MAX_EXPANSION_BLOCK_SIZE));
  expand_circular_wrap = si.GetFloatValue(section, "ExpandCircularWrap", DEFAULT_EXPAND_CIRCULAR_WRAP);
  expand_shift = si.GetFloatValue(section, "ExpandShift", DEFAULT_EXPAND_SHIFT);
  expand_depth = si.GetFloatValue(section, "ExpandDepth", DEFAULT_EXPAND_DEPTH);
  expand_focus = si.GetFloatValue(section, "ExpandFocus", DEFAULT_EXPAND_FOCUS);
  expand_center_image = si.GetFloatValue(section, "ExpandCenterImage", DEFAULT_EXPAND_CENTER_IMAGE);
  expand_front_separation = si.GetFloatValue(section, "ExpandFrontSeparation", DEFAULT_EXPAND_FRONT_SEPARATION);
  expand_rear_separation = si.GetFloatValue(section, "ExpandRearSeparation", DEFAULT_EXPAND_REAR_SEPARATION);
  expand_low_cutoff = SaturateUnsigned<u8>(si.GetUIntValue(section, "ExpandLowCutoff", DEFAULT_EXPAND_LOW_CUTOFF));
  expand_high_cutoff =
    SaturateUnsigned<u8>(si.GetUIntValue(section, "ExpandHighCutoff", DEFAULT_EXPAND_HIGH_CUTOFF));
}

void AudioStreamParameters::Save(SettingsInterface& si, const char* section) const
{
  si.SetStringValue(section, "StretchMode", AudioStream::GetStretchModeName(stretch_mode));
  si.SetStringValue(section, "ExpansionMode", AudioStream::GetExpansionModeName(expansion_mode));
  si.SetUIntValue(section, "OutputLatencyMS", output_latency_ms);
  si.SetBoolValue(section, "OutputLatencyMinimal", output_latency_minimal);
  si.SetUIntValue(section, "BufferMS", buffer_ms);
  si.SetUIntValue(section, "StretchSequenceLengthMS", stretch_sequence_length_ms);
  si.SetUIntValue(section, "StretchSeekWindowMS", stretch_seekwindow_ms);
  si.SetUIntValue(section, "StretchOverlapMS", stretch_overlap_ms);
  si.SetBoolValue(section, "StretchUseQuickSeek", stretch_use_quickseek);
  si.SetBoolValue(section, "StretchUseAAFilter", stretch_use_aa_filter);
  si.SetUIntValue(section, "ExpandBlockSize", expand_block_size);
  si.SetFloatValue(section, "ExpandCircularWrap", expand_circular_wrap);
  si.SetFloatValue(section, "ExpandShift", expand_shift);
  si.SetFloatValue(section, "ExpandDepth", expand_depth);
  si.SetFloatValue(section, "ExpandFocus", expand_focus);
  si.SetFloatValue(section, "ExpandCenterImage", expand_center_image);
  si.SetFloatValue(section, "ExpandFrontSeparation", expand_front_separation);
  si.SetFloatValue(section, "ExpandRearSeparation", expand_rear_separation);
  si.SetUIntValue(section, "ExpandLowCutoff", expand_low_cutoff);
  si.SetUIntValue(section, "ExpandHighCutoff", expand_high_cutoff);
}

void AudioStreamParameters::Clear(SettingsInterface& si, const char* section)
{
  static constexpr std::array keys = {
    "StretchMode",          "ExpansionMode",        "OutputLatencyMS",       "OutputLatencyMinimal",
    "BufferMS",             "StretchSequenceLengthMS", "StretchSeekWindowMS", "StretchOverlapMS",
    "StretchUseQuickSeek",  "StretchUseAAFilter",   "ExpandBlockSize",       "ExpandCircularWrap",
    "ExpandShift",          "ExpandDepth",          "ExpandFocus",           "ExpandCenterImage",
    "ExpandFrontSeparation", "ExpandRearSeparation", "ExpandLowCutoff",       "ExpandHighCutoff",
  };
  for (const char* key : keys)
    si.DeleteValue(section, key);
}

bool AudioStreamParameters::operator==(const AudioStreamParameters& rhs) const
{
  return std::memcmp(this, &rhs, sizeof(*this)) == 0;
}

bool AudioStreamParameters::operator!=(const AudioStreamParameters& rhs) const
{
  return !operator==(rhs);
}

AudioStream::AudioStream(u32 sample_rate, const AudioStreamParameters& parameters)
  : m_sample_rate(sample_rate), m_volume(100), m_parameters(parameters),
    m_output_channels(s_expansion_channel_count[static_cast<size_t>(parameters.expansion_mode)].output_channels),
    m_stretch_inactive(false), m_filling(false), m_paused(false)
{
}

AudioStream::~AudioStream()
{
  StretchDestroy();
  ExpandDestroy();
}

u32 AudioStream::GetAlignedBufferSize(u32 size)
{
  return (size + (CHUNK_SIZE - 1)) & ~(CHUNK_SIZE - 1);
}

u32 AudioStream::GetBufferSizeForMS(u32 sample_rate, u32 ms)
{
  return GetAlignedBufferSize((sample_rate * ms) / 1000);
}

u32 AudioStream::GetMSForBufferSize(u32 sample_rate, u32 buffer_size)
{
  return (GetAlignedBufferSize(buffer_size) * 1000) / sample_rate;
}

std::optional<AudioBackend> AudioStream::ParseBackendName(const char* name)
{
  return ParseName<AudioBackend>(name, s_backend_names);
}

const char* AudioStream::GetBackendName(AudioBackend backend)
{
  return s_backend_names[static_cast<size_t>(backend)];
}

const char* AudioStream::GetBackendDisplayName(AudioBackend backend)
{
  return TRANSLATE("AudioStream", s_backend_display_names[static_cast<size_t>(backend)]);
}

const char* AudioStream::GetExpansionModeName(AudioExpansionMode mode)
{
  return s_expansion_mode_names[static_cast<size_t>(mode)];
}

const char* AudioStream::GetExpansionModeDisplayName(AudioExpansionMode mode)
{
  return TRANSLATE("AudioStream", s_expansion_mode_display_names[static_cast<size_t>(mode)]);
}

std::optional<AudioExpansionMode> AudioStream::ParseExpansionMode(const char* name)
{
  return ParseName<AudioExpansionMode>(name, s_expansion_mode_names);
}

const char* AudioStream::GetStretchModeName(AudioStretchMode mode)
{
  return s_stretch_mode_names[static_cast<size_t>(mode)];
}

const char* AudioStream::GetStretchModeDisplayName(AudioStretchMode mode)
{
  return TRANSLATE("AudioStream", s_stretch_mode_display_names[static_cast<size_t>(mode)]);
}

std::optional<AudioStretchMode> AudioStream::ParseStretchMode(const char* name)
{
  return ParseName<AudioStretchMode>(name, s_stretch_mode_names);
}

std::vector<std::pair<std::string, std::string>> AudioStream::GetDriverNames(AudioBackend backend)
{
#ifndef __ANDROID__
  if (backend == AudioBackend::Cubeb)
    return GetCubebDriverNames();
#endif
  return {};
}

std::vector<AudioStream::DeviceInfo> AudioStream::GetOutputDevices(AudioBackend backend, const char* driver,
                                                                   u32 sample_rate)
{
#ifndef __ANDROID__
  if (backend == AudioBackend::Cubeb)
    return GetCubebOutputDevices(driver, sample_rate);
#endif
  return {};
}

std::unique_ptr<AudioStream> AudioStream::CreateStream(AudioBackend backend, u32 sample_rate,
                                                       const AudioStreamParameters& parameters,
                                                       const char* driver_name, const char* device_name, Error* error)
{
  switch (backend)
  {
    case AudioBackend::Null:
      return CreateNullStream(sample_rate, parameters.buffer_ms);
#ifndef __ANDROID__
    case AudioBackend::Cubeb:
      return CreateCubebAudioStream(sample_rate, parameters, driver_name, device_name, error);
    case AudioBackend::SDL:
      return CreateSDLAudioStream(sample_rate, parameters, error);
#endif
    default:
      Error::SetStringView(error, "Unknown audio backend.");
      return {};
  }
}

std::unique_ptr<AudioStream> AudioStream::CreateNullStream(u32 sample_rate, u32 buffer_ms)
{
  AudioStreamParameters parameters;
  parameters.stretch_mode = AudioStretchMode::Off;
  parameters.expansion_mode = AudioExpansionMode::Disabled;
  parameters.buffer_ms = SaturateUnsigned<u16>(buffer_ms);
  parameters.output_latency_minimal = false;

  std::unique_ptr<AudioStream> stream(new AudioStream(sample_rate, parameters));
  stream->BaseInitialize(&StereoSampleReaderImpl);
  return stream;
}

void AudioStream::BaseInitialize(SampleReader sample_reader)
{
  m_sample_reader = sample_reader;
  AllocateBuffer();
  ExpandAllocate();
  StretchAllocate();
}

void AudioStream::StereoSampleReaderImpl(SampleType* dest, const SampleType* src, u32 num_frames)
{
  std::memcpy(dest, src, static_cast<size_t>(num_frames) * NUM_INPUT_CHANNELS * sizeof(SampleType));
}

u32 AudioStream::GetBufferedFramesRelaxed() const
{
  const u32 rpos = m_rpos.load(std::memory_order_relaxed);
  const u32 wpos = m_wpos.load(std::memory_order_relaxed);
  return (wpos + m_buffer_size - rpos) % m_buffer_size;
}

void AudioStream::ReadFrames(SampleType* samples, u32 num_frames)
{
  const u32 available_frames = GetBufferedFramesRelaxed();
  u32 frames_to_read = num_frames;
  u32 silence_frames = 0;

  if (m_filling)
  {
    const u32 divisor = (m_parameters.stretch_mode == AudioStretchMode::TimeStretch) ? 400 : 32;
    const u32 to_fill = GetAlignedBufferSize(m_buffer_size / divisor);
    if (available_frames < to_fill)
    {
      silence_frames = num_frames;
      frames_to_read = 0;
    }
    else
    {
      m_filling = false;
      DEV_LOG("Underrun compensation done ({} frames buffered)", to_fill);
    }
  }

  if (available_frames < frames_to_read)
  {
    silence_frames = frames_to_read - available_frames;
    frames_to_read = available_frames;
    m_filling = true;
    if (m_parameters.stretch_mode == AudioStretchMode::TimeStretch)
      StretchUnderrun();
  }

  if (frames_to_read > 0)
  {
    u32 rpos = m_rpos.load(std::memory_order_acquire);
    u32 end = std::min(m_buffer_size - rpos, frames_to_read);
    if (end > 0)
      m_sample_reader(samples, &m_buffer[rpos * m_output_channels], end);

    rpos = (rpos + end) % m_buffer_size;
    const u32 remainder = frames_to_read - end;
    if (remainder > 0)
    {
      m_sample_reader(samples + end * m_output_channels, m_buffer.get(), remainder);
      rpos = remainder;
    }
    m_rpos.store(rpos, std::memory_order_release);
  }

  if (silence_frames > 0)
  {
    if (frames_to_read > 0)
    {
      const u32 increment = static_cast<u32>((static_cast<float>(frames_to_read) / num_frames) * 65536.0f);
      const size_t sample_count = static_cast<size_t>(frames_to_read) * m_output_channels;
      SampleType* resample_buffer = static_cast<SampleType*>(alloca(sample_count * sizeof(SampleType)));
      std::memcpy(resample_buffer, samples, sample_count * sizeof(SampleType));

      SampleType* resample_ptr = resample_buffer;
      SampleType* out_ptr = samples;
      const u32 copy_stride = m_output_channels * sizeof(SampleType);
      u32 resample_subpos = 0;
      for (u32 i = 0; i < num_frames; i++)
      {
        std::memcpy(out_ptr, resample_ptr, copy_stride);
        out_ptr += m_output_channels;
        resample_subpos += increment;
        resample_ptr += (resample_subpos >> 16) * m_output_channels;
        resample_subpos &= 0xffff;
      }
      DEV_LOG("Audio buffer underflow, resampled {} frames to {}", frames_to_read, num_frames);
    }
    else
    {
      std::memset(samples, 0, static_cast<size_t>(num_frames) * m_output_channels * sizeof(SampleType));
    }
  }

  if (m_volume != 100)
  {
    const float scale = static_cast<float>(m_volume) / 100.0f;
    const u32 sample_count = num_frames * m_output_channels;
    for (u32 i = 0; i < sample_count; i++)
    {
      const float value = std::clamp(static_cast<float>(samples[i]) * scale, -32768.0f, 32767.0f);
      samples[i] = static_cast<s16>(std::lrint(value));
    }
  }
}

void AudioStream::SetPaused(bool paused)
{
  m_paused = paused;
}

void AudioStream::SetOutputVolume(u32 volume)
{
  m_volume = volume;
}

void AudioStream::BeginWrite(SampleType** buffer_ptr, u32* num_frames)
{
  *buffer_ptr = m_staging_buffer.get() + m_staging_buffer_pos;
  *num_frames = CHUNK_SIZE - (m_staging_buffer_pos / NUM_INPUT_CHANNELS);
}

void AudioStream::EndWrite(u32 num_frames)
{
  if (m_volume == 0)
    return;

  m_staging_buffer_pos += num_frames * NUM_INPUT_CHANNELS;
  DebugAssert(m_staging_buffer_pos <= (CHUNK_SIZE * NUM_INPUT_CHANNELS));
  if ((m_staging_buffer_pos / NUM_INPUT_CHANNELS) < CHUNK_SIZE)
    return;

  m_staging_buffer_pos = 0;
  if (!IsExpansionEnabled() && !IsStretchEnabled())
  {
    InternalWriteFrames(m_staging_buffer.get(), CHUNK_SIZE);
    return;
  }

  if (IsExpansionEnabled())
  {
    S16ChunkToFloat(m_staging_buffer.get(), m_expand_inbuf.get() + m_parameters.expand_block_size +
                                              m_expand_buffer_pos * NUM_INPUT_CHANNELS,
                    CHUNK_SIZE * NUM_INPUT_CHANNELS);

    if (m_expand_has_block)
    {
      const float* block = m_expand_outbuf.get() + m_expand_buffer_pos * m_output_channels;
      if (IsStretchEnabled())
        StretchWriteBlock(block);
      else
      {
        FloatChunkToS16(m_staging_buffer.get(), block, CHUNK_SIZE * m_output_channels);
        InternalWriteFrames(m_staging_buffer.get(), CHUNK_SIZE);
      }
    }

    m_expand_buffer_pos += CHUNK_SIZE;
    if (m_expand_buffer_pos == m_parameters.expand_block_size)
    {
      m_expand_buffer_pos = 0;
      m_expand_has_block = true;
      ExpandDecode();
    }
    return;
  }

  S16ChunkToFloat(m_staging_buffer.get(), m_float_buffer.get(), CHUNK_SIZE * NUM_INPUT_CHANNELS);
  StretchWriteBlock(m_float_buffer.get());
}

void AudioStream::EmptyBuffer()
{
  if (IsExpansionEnabled())
    ExpandFlush();
  if (IsStretchEnabled())
  {
    soundtouch_clear(m_soundtouch);
    if (m_parameters.stretch_mode == AudioStretchMode::TimeStretch)
      soundtouch_setTempo(m_soundtouch, m_nominal_rate);
  }

  m_wpos.store(m_rpos.load(std::memory_order_acquire), std::memory_order_release);
}

void AudioStream::SetNominalRate(float tempo)
{
  m_nominal_rate = tempo;
  if (m_parameters.stretch_mode == AudioStretchMode::Resample)
    soundtouch_setRate(m_soundtouch, tempo);
  else if (m_parameters.stretch_mode == AudioStretchMode::TimeStretch && m_stretch_inactive)
    soundtouch_setTempo(m_soundtouch, tempo);
}

void AudioStream::SetStretchMode(AudioStretchMode mode)
{
  if (m_parameters.stretch_mode == mode)
    return;

  const bool was_paused = m_paused;
  if (!was_paused)
    SetPaused(true);

  StretchDestroy();
  DestroyBuffer();
  m_parameters.stretch_mode = mode;
  AllocateBuffer();
  if (IsStretchEnabled())
    StretchAllocate();

  if (!was_paused)
    SetPaused(false);
}

void AudioStream::AllocateBuffer()
{
  const u32 multiplier = (m_parameters.stretch_mode == AudioStretchMode::TimeStretch) ? 16 :
                         (m_parameters.stretch_mode == AudioStretchMode::Resample) ? 2 : 1;
  m_buffer_size = GetBufferSizeForMS(m_sample_rate, static_cast<u32>(m_parameters.buffer_ms) * multiplier);
  m_target_buffer_size = GetBufferSizeForMS(m_sample_rate, m_parameters.buffer_ms);
  m_buffer = Common::make_unique_aligned_for_overwrite<s16[]>(16, m_buffer_size * m_output_channels);
  m_staging_buffer =
    Common::make_unique_aligned_for_overwrite<s16[]>(16, CHUNK_SIZE * m_output_channels);
  m_float_buffer =
    Common::make_unique_aligned_for_overwrite<float[]>(16, CHUNK_SIZE * m_output_channels);
  m_rpos.store(0, std::memory_order_relaxed);
  m_wpos.store(0, std::memory_order_relaxed);
  m_staging_buffer_pos = 0;

  DEV_LOG("Allocated buffer of {} frames for buffer of {} ms [expansion {} (block size {}), stretch {}, target size {}].",
          m_buffer_size, m_parameters.buffer_ms, GetExpansionModeName(m_parameters.expansion_mode),
          m_parameters.expand_block_size, GetStretchModeName(m_parameters.stretch_mode), m_target_buffer_size);
}

void AudioStream::DestroyBuffer()
{
  m_float_buffer.reset();
  m_staging_buffer.reset();
  m_buffer.reset();
  m_buffer_size = 0;
  m_target_buffer_size = 0;
}

void AudioStream::InternalWriteFrames(SampleType* data, u32 num_frames)
{
  u32 rpos = m_rpos.load(std::memory_order_acquire);
  u32 wpos = m_wpos.load(std::memory_order_relaxed);
  const u32 buffered = (wpos + m_buffer_size - rpos) % m_buffer_size;
  const u32 free = m_buffer_size - buffered - 1;
  if (free < num_frames)
  {
    if (m_parameters.stretch_mode != AudioStretchMode::TimeStretch)
    {
      WARNING_LOG("Buffer overrun, chunk dropped");
      return;
    }
    StretchOverrun();
    rpos = m_rpos.load(std::memory_order_acquire);
  }

  const u32 end = std::min(m_buffer_size - wpos, num_frames);
  std::memcpy(&m_buffer[wpos * m_output_channels], data,
              static_cast<size_t>(end) * m_output_channels * sizeof(SampleType));
  wpos = (wpos + end) % m_buffer_size;

  const u32 remainder = num_frames - end;
  if (remainder > 0)
  {
    std::memcpy(m_buffer.get(), data + end * m_output_channels,
                static_cast<size_t>(remainder) * m_output_channels * sizeof(SampleType));
    wpos = remainder;
  }
  m_wpos.store(wpos, std::memory_order_release);
}

void AudioStream::ExpandAllocate()
{
  if (!IsExpansionEnabled())
    return;

  m_expand_buffer_pos = 0;
  m_expand_has_block = false;
  const u32 block_size = m_parameters.expand_block_size;
  const u32 freq_size = block_size / 2 + 1;
  m_expand_convbuffer = Common::make_unique_aligned<double[]>(16, block_size * 2);
  m_expand_freqdomain = Common::make_unique_aligned<std::complex<double>[]>(16, freq_size * 2);
  m_expand_right_fd = Common::make_unique_aligned<std::complex<double>[]>(16, freq_size * 2);
  m_expand_fft = kiss_fftr_alloc(static_cast<int>(block_size), 0, nullptr, nullptr);
  m_expand_ifft = kiss_fftr_alloc(static_cast<int>(block_size), 1, nullptr, nullptr);
  m_expand_inbuf = Common::make_unique_aligned<float[]>(16, block_size * 3);
  m_expand_outbuf = Common::make_unique_aligned<float[]>(16, (block_size + block_size / 2) * m_output_channels);
  m_expand_signal = Common::make_unique_aligned<std::complex<double>[]>(16, freq_size * m_output_channels);
  m_expand_window = Common::make_unique_aligned<double[]>(16, block_size);

  constexpr double pi = 3.14159265358979323846;
  for (u32 i = 0; i < block_size; i++)
  {
    m_expand_window[i] =
      std::sqrt((0.5 * (1.0 - std::cos((2.0 * pi * static_cast<double>(i)) / block_size))) / block_size);
  }

  m_expand_lfe_low_cutoff =
    (static_cast<float>(m_parameters.expand_low_cutoff) / m_sample_rate) * 2.0f * (block_size / 2);
  m_expand_lfe_high_cutoff =
    (static_cast<float>(m_parameters.expand_high_cutoff) / m_sample_rate) * 2.0f * (block_size / 2);
  ExpandFlush();
}

void AudioStream::ExpandDestroy()
{
  if (m_expand_fft)
  {
    kiss_fftr_free(m_expand_fft);
    m_expand_fft = nullptr;
  }
  if (m_expand_ifft)
  {
    kiss_fftr_free(m_expand_ifft);
    m_expand_ifft = nullptr;
  }
  m_expand_signal.reset();
  m_expand_window.reset();
  m_expand_outbuf.reset();
  m_expand_inbuf.reset();
  m_expand_right_fd.reset();
  m_expand_freqdomain.reset();
  m_expand_convbuffer.reset();
}

void AudioStream::ExpandDecode()
{
  const u32 block_size = m_parameters.expand_block_size;
  const u32 half_size = block_size / 2;
  const u32 freq_size = half_size + 1;
  const ExpansionChannelSetup& setup = s_expansion_channel_count[static_cast<size_t>(m_parameters.expansion_mode)];

  if (m_expand_has_block)
  {
    std::memmove(m_expand_outbuf.get(), m_expand_outbuf.get() + block_size * m_output_channels,
                 static_cast<size_t>(half_size) * m_output_channels * sizeof(float));
    std::fill_n(m_expand_outbuf.get() + half_size * m_output_channels,
                static_cast<size_t>(block_size) * m_output_channels, 0.0f);
  }
  else
  {
    std::fill_n(m_expand_outbuf.get(), static_cast<size_t>(block_size + half_size) * m_output_channels, 0.0f);
  }

  constexpr double pi = 3.14159265358979323846;
  for (u32 pass = 0; pass < 2; pass++)
  {
    const u32 frame_offset = pass * half_size;
    for (u32 i = 0; i < block_size; i++)
    {
      const u32 input_index = (frame_offset + i) * NUM_INPUT_CHANNELS;
      m_expand_convbuffer[i] = static_cast<double>(m_expand_inbuf[input_index]) * m_expand_window[i];
      m_expand_convbuffer[block_size + i] =
        static_cast<double>(m_expand_inbuf[input_index + 1]) * m_expand_window[i];
    }

    kiss_fftr(m_expand_fft, m_expand_convbuffer.get(), reinterpret_cast<kiss_fft_cpx*>(m_expand_freqdomain.get()));
    kiss_fftr(m_expand_fft, m_expand_convbuffer.get() + block_size,
              reinterpret_cast<kiss_fft_cpx*>(m_expand_right_fd.get()));

    for (u32 bin = 0; bin < freq_size; bin++)
    {
      const std::complex<double> left = m_expand_freqdomain[bin];
      const std::complex<double> right = m_expand_right_fd[bin];
      const double left_amplitude = std::abs(left);
      const double right_amplitude = std::abs(right);
      const double amplitude_sum = left_amplitude + right_amplitude;
      const double average_phase = std::arg(left + right);

      float x = (amplitude_sum > 1.0e-12) ?
                  static_cast<float>((right_amplitude - left_amplitude) / amplitude_sum) :
                  0.0f;
      double phase_difference = std::remainder(std::arg(right) - std::arg(left), 2.0 * pi);
      float y = static_cast<float>(std::abs(phase_difference) / pi);

      const float wrap = m_parameters.expand_circular_wrap / 360.0f;
      x = std::clamp(x + m_parameters.expand_shift, -1.0f, 1.0f);
      y = std::clamp(y * m_parameters.expand_depth, 0.0f, 1.0f);
      if (wrap != 0.0f)
      {
        const float angle = std::atan2(y, x) / static_cast<float>(2.0 * pi);
        const float radius = std::hypot(x, y);
        const float wrapped_angle = WrapUnit(angle + wrap * y);
        x = std::clamp(radius * std::cos(wrapped_angle * static_cast<float>(2.0 * pi)), -1.0f, 1.0f);
        y = std::clamp(std::abs(radius * std::sin(wrapped_angle * static_cast<float>(2.0 * pi))), 0.0f, 1.0f);
      }
      if (m_parameters.expand_focus != 0.0f)
      {
        const float exponent = std::exp2(-m_parameters.expand_focus);
        x = std::copysign(std::pow(std::abs(x), exponent), x);
        y = std::pow(y, exponent);
      }

      const u32 gx = static_cast<u32>(std::clamp(std::lround((x + 1.0f) * 0.5f * (EXPAND_GRID_RES - 1)),
                                                  0l, static_cast<long>(EXPAND_GRID_RES - 1)));
      const u32 gy = static_cast<u32>(std::clamp(std::lround(y * (EXPAND_GRID_RES - 1)), 0l,
                                                  static_cast<long>(EXPAND_GRID_RES - 1)));
      const double total_amplitude = std::hypot(left_amplitude, right_amplitude);
      const std::complex<double> base = std::polar(total_amplitude, average_phase);

      const u32 directional_channels = setup.output_channels - (setup.has_lfe ? 1u : 0u);
      for (u32 channel = 0; channel < directional_channels; channel++)
      {
        float gain = setup.channel_lut[channel][gy][gx];
        if (channel < 3)
          gain *= m_parameters.expand_front_separation;
        else
          gain *= m_parameters.expand_rear_separation;
        if (setup.channel_xsf[channel] == 0)
          gain *= m_parameters.expand_center_image;

        const double phase = (setup.channel_xsf[channel] < 0) ? std::arg(left) :
                             (setup.channel_xsf[channel] > 0) ? std::arg(right) : average_phase;
        m_expand_signal[channel * freq_size + bin] = std::polar(total_amplitude * gain, phase);
      }

      if (setup.has_lfe)
      {
        float gain = 0.0f;
        if (static_cast<float>(bin) <= m_expand_lfe_low_cutoff)
          gain = 1.0f;
        else if (static_cast<float>(bin) < m_expand_lfe_high_cutoff &&
                 m_expand_lfe_high_cutoff > m_expand_lfe_low_cutoff)
        {
          const float position = (static_cast<float>(bin) - m_expand_lfe_low_cutoff) /
                                 (m_expand_lfe_high_cutoff - m_expand_lfe_low_cutoff);
          gain = 0.5f * (1.0f + std::cos(position * static_cast<float>(pi)));
        }
        m_expand_signal[(setup.output_channels - 1) * freq_size + bin] = base * static_cast<double>(gain);
      }
    }

    for (u32 channel = 0; channel < setup.output_channels; channel++)
    {
      kiss_fftri(m_expand_ifft, reinterpret_cast<const kiss_fft_cpx*>(m_expand_signal.get() + channel * freq_size),
                 m_expand_convbuffer.get());
      for (u32 i = 0; i < block_size; i++)
      {
        m_expand_outbuf[(frame_offset + i) * m_output_channels + channel] +=
          static_cast<float>(m_expand_convbuffer[i] * m_expand_window[i]);
      }
    }
  }

  std::memmove(m_expand_inbuf.get(), m_expand_inbuf.get() + block_size * NUM_INPUT_CHANNELS,
               static_cast<size_t>(half_size) * NUM_INPUT_CHANNELS * sizeof(float));
}

void AudioStream::ExpandFlush()
{
  if (!m_expand_inbuf)
    return;
  std::memset(m_expand_inbuf.get(), 0,
              static_cast<size_t>(m_parameters.expand_block_size) * 3 * sizeof(float));
  std::memset(m_expand_outbuf.get(), 0, static_cast<size_t>(m_parameters.expand_block_size +
                                                            m_parameters.expand_block_size / 2) *
                                              m_output_channels * sizeof(float));
  m_expand_buffer_pos = 0;
  m_expand_has_block = false;
}

void AudioStream::StretchAllocate()
{
  if (!IsStretchEnabled())
    return;

  m_soundtouch = soundtouch_createInstance();
  soundtouch_setSampleRate(m_soundtouch, m_sample_rate);
  soundtouch_setChannels(m_soundtouch, m_output_channels);
  soundtouch_setSetting(m_soundtouch, SETTING_USE_QUICKSEEK, m_parameters.stretch_use_quickseek);
  soundtouch_setSetting(m_soundtouch, SETTING_USE_AA_FILTER, m_parameters.stretch_use_aa_filter);
  soundtouch_setSetting(m_soundtouch, SETTING_SEQUENCE_MS, m_parameters.stretch_sequence_length_ms);
  soundtouch_setSetting(m_soundtouch, SETTING_SEEKWINDOW_MS, m_parameters.stretch_seekwindow_ms);
  soundtouch_setSetting(m_soundtouch, SETTING_OVERLAP_MS, m_parameters.stretch_overlap_ms);
  if (m_parameters.stretch_mode == AudioStretchMode::Resample)
    soundtouch_setRate(m_soundtouch, m_nominal_rate);
  else
    soundtouch_setTempo(m_soundtouch, m_nominal_rate);

  m_stretch_reset = STRETCH_RESET_THRESHOLD;
  m_stretch_inactive = false;
  m_stretch_ok_count = 0;
  m_dynamic_target_usage = 0.0f;
  m_average_position = 0;
  m_average_available = 0;
  m_staging_buffer_pos = 0;
}

void AudioStream::StretchDestroy()
{
  if (m_soundtouch)
    soundtouch_destroyInstance(m_soundtouch);
  m_soundtouch = nullptr;
}

void AudioStream::StretchWriteBlock(const float* data)
{
  soundtouch_putSamples(m_soundtouch, data, CHUNK_SIZE);

  for (;;)
  {
    const u32 received = soundtouch_receiveSamples(m_soundtouch, m_float_buffer.get(), CHUNK_SIZE);
    if (received == 0)
      break;
    FloatChunkToS16(m_staging_buffer.get(), m_float_buffer.get(), received * m_output_channels);
    InternalWriteFrames(m_staging_buffer.get(), received);
  }

  if (m_parameters.stretch_mode == AudioStretchMode::TimeStretch)
    UpdateStretchTempo();
}

void AudioStream::StretchUnderrun()
{
  m_stretch_reset = std::min(m_stretch_reset + 1, STRETCH_RESET_THRESHOLD);
}

void AudioStream::StretchOverrun()
{
  m_stretch_reset = std::min(m_stretch_reset + 1, STRETCH_RESET_THRESHOLD);
  const u32 discard = std::max(GetAlignedBufferSize(m_target_buffer_size / 16), CHUNK_SIZE);
  const u32 rpos = m_rpos.load(std::memory_order_relaxed);
  m_rpos.store((rpos + discard) % m_buffer_size, std::memory_order_release);
}

float AudioStream::AddAndGetAverageTempo(float tempo)
{
  m_average_fullness[m_average_position] = tempo;
  m_average_position = (m_average_position + 1) % AVERAGING_BUFFER_SIZE;
  m_average_available = std::min(m_average_available + 1, AVERAGING_WINDOW);

  float total = 0.0f;
  for (u32 i = 0; i < m_average_available; i++)
  {
    const u32 index = (m_average_position + AVERAGING_BUFFER_SIZE - i - 1) % AVERAGING_BUFFER_SIZE;
    total += m_average_fullness[index];
  }
  return total / static_cast<float>(m_average_available);
}

void AudioStream::UpdateStretchTempo()
{
  if (m_stretch_reset >= STRETCH_RESET_THRESHOLD)
  {
    soundtouch_clear(m_soundtouch);
    soundtouch_setTempo(m_soundtouch, m_nominal_rate);
    m_stretch_reset = 0;
    m_stretch_ok_count = 0;
    m_stretch_inactive = false;
    m_average_position = 0;
    m_average_available = 0;
    DEV_LOG("___ Stretcher is being reset.");
    return;
  }

  const float target = static_cast<float>(m_target_buffer_size);
  const float fullness = target > 0.0f ? static_cast<float>(GetBufferedFramesRelaxed()) / target : 1.0f;
  const float average = AddAndGetAverageTempo(fullness);
  const float error = average - 1.0f;
  m_dynamic_target_usage = std::clamp(m_dynamic_target_usage + error / TARGET_IPS, -0.5f, 0.5f);

  if (std::abs(error) < 0.02f)
  {
    if (++m_stretch_ok_count >= TARGET_IPS && !m_stretch_inactive)
    {
      m_stretch_inactive = true;
      soundtouch_setTempo(m_soundtouch, m_nominal_rate);
      DEV_LOG("=== Stretcher is now inactive.");
    }
    return;
  }

  m_stretch_ok_count = 0;
  const float tempo = m_nominal_rate * std::clamp(1.0f + error * 0.08f + m_dynamic_target_usage * 0.02f,
                                                   0.95f, 1.05f);
  if (m_stretch_inactive)
  {
    m_stretch_inactive = false;
    DEV_LOG("~~~ Stretcher is now active @ tempo {}.", tempo);
  }
  soundtouch_setTempo(m_soundtouch, tempo);
}
