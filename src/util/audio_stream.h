// SPDX-FileCopyrightText: 2026 RlyehPSX <https://github.com/RlyehPSX>
// SPDX-License-Identifier: GPL-3.0-or-later
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

#pragma once

#include "common/align.h"
#include "common/types.h"

#include <array>
#include <atomic>
#include <complex>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

class Error;
class SettingsInterface;
struct kiss_fftr_state;

enum class AudioBackend : u8
{
  Null,
#ifndef __ANDROID__
  Cubeb,
  SDL,
#endif
  Count
};

enum class AudioStretchMode : u8
{
  Off,
  Resample,
  TimeStretch,
  Count
};

enum class AudioExpansionMode : u8
{
  Disabled,
  StereoLFE,
  Quadraphonic,
  QuadraphonicLFE,
  Surround51,
  Surround71,
  Count
};

struct AudioStreamParameters
{
  static constexpr AudioStretchMode DEFAULT_STRETCH_MODE = AudioStretchMode::TimeStretch;
  static constexpr AudioExpansionMode DEFAULT_EXPANSION_MODE = AudioExpansionMode::Disabled;

  static constexpr u16 DEFAULT_BUFFER_MS = 50;
  static constexpr u16 DEFAULT_OUTPUT_LATENCY_MS = 20;
  static constexpr bool DEFAULT_OUTPUT_LATENCY_MINIMAL = false;
  static constexpr u16 DEFAULT_EXPAND_BLOCK_SIZE = 2048;
  static constexpr float DEFAULT_EXPAND_CIRCULAR_WRAP = 90.0f;
  static constexpr float DEFAULT_EXPAND_SHIFT = 0.0f;
  static constexpr float DEFAULT_EXPAND_DEPTH = 1.0f;
  static constexpr float DEFAULT_EXPAND_FOCUS = 0.0f;
  static constexpr float DEFAULT_EXPAND_CENTER_IMAGE = 1.0f;
  static constexpr float DEFAULT_EXPAND_FRONT_SEPARATION = 1.0f;
  static constexpr float DEFAULT_EXPAND_REAR_SEPARATION = 1.0f;
  static constexpr u8 DEFAULT_EXPAND_LOW_CUTOFF = 40;
  static constexpr u8 DEFAULT_EXPAND_HIGH_CUTOFF = 90;

  static constexpr u16 DEFAULT_STRETCH_SEQUENCE_LENGTH = 30;
  static constexpr u16 DEFAULT_STRETCH_SEEKWINDOW = 20;
  static constexpr u16 DEFAULT_STRETCH_OVERLAP = 10;
  static constexpr bool DEFAULT_STRETCH_USE_QUICKSEEK = false;
  static constexpr bool DEFAULT_STRETCH_USE_AA_FILTER = false;

  AudioStretchMode stretch_mode = DEFAULT_STRETCH_MODE;
  AudioExpansionMode expansion_mode = DEFAULT_EXPANSION_MODE;
  u16 buffer_ms = DEFAULT_BUFFER_MS;
  u16 output_latency_ms = DEFAULT_OUTPUT_LATENCY_MS;
  bool output_latency_minimal = DEFAULT_OUTPUT_LATENCY_MINIMAL;
  bool pad1 = false;

  u16 stretch_sequence_length_ms = DEFAULT_STRETCH_SEQUENCE_LENGTH;
  u16 stretch_seekwindow_ms = DEFAULT_STRETCH_SEEKWINDOW;
  u16 stretch_overlap_ms = DEFAULT_STRETCH_OVERLAP;
  bool stretch_use_quickseek = DEFAULT_STRETCH_USE_QUICKSEEK;
  bool stretch_use_aa_filter = DEFAULT_STRETCH_USE_AA_FILTER;

  float expand_circular_wrap = DEFAULT_EXPAND_CIRCULAR_WRAP;
  float expand_shift = DEFAULT_EXPAND_SHIFT;
  float expand_depth = DEFAULT_EXPAND_DEPTH;
  float expand_focus = DEFAULT_EXPAND_FOCUS;
  float expand_center_image = DEFAULT_EXPAND_CENTER_IMAGE;
  float expand_front_separation = DEFAULT_EXPAND_FRONT_SEPARATION;
  float expand_rear_separation = DEFAULT_EXPAND_REAR_SEPARATION;
  u16 expand_block_size = DEFAULT_EXPAND_BLOCK_SIZE;
  u8 expand_low_cutoff = DEFAULT_EXPAND_LOW_CUTOFF;
  u8 expand_high_cutoff = DEFAULT_EXPAND_HIGH_CUTOFF;

  void Load(SettingsInterface& si, const char* section);
  void Save(SettingsInterface& si, const char* section) const;
  void Clear(SettingsInterface& si, const char* section);

  bool operator==(const AudioStreamParameters& rhs) const;
  bool operator!=(const AudioStreamParameters& rhs) const;
};

class AudioStream
{
public:
  using SampleType = s16;

  static constexpr u32 NUM_INPUT_CHANNELS = 2;
  static constexpr u32 MAX_OUTPUT_CHANNELS = 8;
  static constexpr u32 CHUNK_SIZE = 64;
  static constexpr u32 MIN_EXPANSION_BLOCK_SIZE = 256;
  static constexpr u32 MAX_EXPANSION_BLOCK_SIZE = 4096;

#ifdef __ANDROID__
  static constexpr AudioBackend DEFAULT_BACKEND = AudioBackend::Null;
#else
  static constexpr AudioBackend DEFAULT_BACKEND = AudioBackend::Cubeb;
#endif

  struct DeviceInfo
  {
    std::string name;
    std::string display_name;
    u32 minimum_latency_frames;

    DeviceInfo(std::string name_, std::string display_name_, u32 minimum_latency_frames_);
    ~DeviceInfo();
  };

  virtual ~AudioStream();

  static u32 GetAlignedBufferSize(u32 size);
  static u32 GetBufferSizeForMS(u32 sample_rate, u32 ms);
  static u32 GetMSForBufferSize(u32 sample_rate, u32 buffer_size);

  static std::optional<AudioBackend> ParseBackendName(const char* name);
  static const char* GetBackendName(AudioBackend backend);
  static const char* GetBackendDisplayName(AudioBackend backend);

  static const char* GetExpansionModeName(AudioExpansionMode mode);
  static const char* GetExpansionModeDisplayName(AudioExpansionMode mode);
  static std::optional<AudioExpansionMode> ParseExpansionMode(const char* name);

  static const char* GetStretchModeName(AudioStretchMode mode);
  static const char* GetStretchModeDisplayName(AudioStretchMode mode);
  static std::optional<AudioStretchMode> ParseStretchMode(const char* name);

  ALWAYS_INLINE u32 GetSampleRate() const { return m_sample_rate; }
  ALWAYS_INLINE u32 GetInternalChannels() const { return m_output_channels; }
  ALWAYS_INLINE u32 GetOutputChannels() const { return m_output_channels; }
  ALWAYS_INLINE u32 GetBufferSize() const { return m_buffer_size; }
  ALWAYS_INLINE u32 GetTargetBufferSize() const { return m_target_buffer_size; }
  ALWAYS_INLINE u32 GetOutputVolume() const { return m_volume; }
  ALWAYS_INLINE float GetNominalTempo() const { return m_nominal_rate; }
  ALWAYS_INLINE bool IsPaused() const { return m_paused; }

  u32 GetBufferedFramesRelaxed() const;

  virtual void SetPaused(bool paused);
  void SetOutputVolume(u32 volume);
  void BeginWrite(SampleType** buffer_ptr, u32* num_frames);
  void EndWrite(u32 num_frames);
  void EmptyBuffer();
  void SetNominalRate(float tempo);
  void SetStretchMode(AudioStretchMode mode);

  static std::vector<std::pair<std::string, std::string>> GetDriverNames(AudioBackend backend);
  static std::vector<DeviceInfo> GetOutputDevices(AudioBackend backend, const char* driver, u32 sample_rate);
  static std::unique_ptr<AudioStream> CreateStream(AudioBackend backend, u32 sample_rate,
                                                   const AudioStreamParameters& parameters, const char* driver_name,
                                                   const char* device_name, Error* error);
  static std::unique_ptr<AudioStream> CreateNullStream(u32 sample_rate, u32 buffer_ms);

protected:
  enum ReadChannel : u8
  {
    READ_CHANNEL_FRONT_LEFT,
    READ_CHANNEL_FRONT_CENTER,
    READ_CHANNEL_FRONT_RIGHT,
    READ_CHANNEL_SIDE_LEFT,
    READ_CHANNEL_SIDE_RIGHT,
    READ_CHANNEL_REAR_LEFT,
    READ_CHANNEL_REAR_RIGHT,
    READ_CHANNEL_LFE,
    READ_CHANNEL_NONE
  };

  using SampleReader = void (*)(SampleType* dest, const SampleType* src, u32 num_frames);

  AudioStream(u32 sample_rate, const AudioStreamParameters& parameters);
  void BaseInitialize(SampleReader sample_reader);
  void ReadFrames(SampleType* samples, u32 num_frames);

  template<AudioExpansionMode mode, ReadChannel c0, ReadChannel c1, ReadChannel c2 = READ_CHANNEL_NONE,
           ReadChannel c3 = READ_CHANNEL_NONE, ReadChannel c4 = READ_CHANNEL_NONE,
           ReadChannel c5 = READ_CHANNEL_NONE, ReadChannel c6 = READ_CHANNEL_NONE,
           ReadChannel c7 = READ_CHANNEL_NONE>
  static void SampleReaderImpl(SampleType* dest, const SampleType* src, u32 num_frames);
  static void StereoSampleReaderImpl(SampleType* dest, const SampleType* src, u32 num_frames);

  u32 m_sample_rate;
  u32 m_volume;
  AudioStreamParameters m_parameters;
  u8 m_output_channels;
  bool m_stretch_inactive;
  bool m_filling;
  bool m_paused;

private:
  static constexpr u32 AVERAGING_BUFFER_SIZE = 256;
  static constexpr u32 AVERAGING_WINDOW = 50;
  static constexpr u32 STRETCH_RESET_THRESHOLD = 5;
  static constexpr u32 TARGET_IPS = 691;

#ifndef __ANDROID__
  static std::vector<std::pair<std::string, std::string>> GetCubebDriverNames();
  static std::vector<DeviceInfo> GetCubebOutputDevices(const char* driver, u32 sample_rate);
  static std::unique_ptr<AudioStream> CreateCubebAudioStream(u32 sample_rate,
                                                             const AudioStreamParameters& parameters,
                                                             const char* driver_name, const char* device_name,
                                                             Error* error);
  static std::unique_ptr<AudioStream> CreateSDLAudioStream(u32 sample_rate, const AudioStreamParameters& parameters,
                                                           Error* error);
#endif

  ALWAYS_INLINE bool IsExpansionEnabled() const { return m_parameters.expansion_mode != AudioExpansionMode::Disabled; }
  ALWAYS_INLINE bool IsStretchEnabled() const { return m_parameters.stretch_mode != AudioStretchMode::Off; }

  void AllocateBuffer();
  void DestroyBuffer();
  void InternalWriteFrames(SampleType* data, u32 num_frames);

  void ExpandAllocate();
  void ExpandDestroy();
  void ExpandDecode();
  void ExpandFlush();

  void StretchAllocate();
  void StretchDestroy();
  void StretchWriteBlock(const float* data);
  void StretchUnderrun();
  void StretchOverrun();
  float AddAndGetAverageTempo(float tempo);
  void UpdateStretchTempo();

  u32 m_buffer_size = 0;
  Common::unique_aligned_ptr<s16[]> m_buffer;
  SampleReader m_sample_reader = nullptr;

  std::atomic<u32> m_rpos{0};
  std::atomic<u32> m_wpos{0};

  void* m_soundtouch = nullptr;

  u32 m_target_buffer_size = 0;
  u32 m_stretch_reset = STRETCH_RESET_THRESHOLD;
  u32 m_stretch_ok_count = 0;
  float m_nominal_rate = 1.0f;
  float m_dynamic_target_usage = 0.0f;
  u32 m_average_position = 0;
  u32 m_average_available = 0;
  u32 m_staging_buffer_pos = 0;

  std::array<float, AVERAGING_BUFFER_SIZE> m_average_fullness{};

  Common::unique_aligned_ptr<s16[]> m_staging_buffer;
  Common::unique_aligned_ptr<float[]> m_float_buffer;

  u32 m_expand_buffer_pos = 0;
  bool m_expand_has_block = false;
  float m_expand_lfe_low_cutoff = 1.0f;
  float m_expand_lfe_high_cutoff = 1.0f;
  Common::unique_aligned_ptr<double[]> m_expand_convbuffer;
  Common::unique_aligned_ptr<std::complex<double>[]> m_expand_freqdomain;
  Common::unique_aligned_ptr<std::complex<double>[]> m_expand_right_fd;
  kiss_fftr_state* m_expand_fft = nullptr;
  kiss_fftr_state* m_expand_ifft = nullptr;
  Common::unique_aligned_ptr<float[]> m_expand_inbuf;
  Common::unique_aligned_ptr<float[]> m_expand_outbuf;
  Common::unique_aligned_ptr<double[]> m_expand_window;
  Common::unique_aligned_ptr<std::complex<double>[]> m_expand_signal;
};

template<AudioExpansionMode mode, AudioStream::ReadChannel c0, AudioStream::ReadChannel c1,
         AudioStream::ReadChannel c2, AudioStream::ReadChannel c3, AudioStream::ReadChannel c4,
         AudioStream::ReadChannel c5, AudioStream::ReadChannel c6, AudioStream::ReadChannel c7>
void AudioStream::SampleReaderImpl(SampleType* dest, const SampleType* src, u32 num_frames)
{
  static constexpr u8 luts[static_cast<u8>(AudioExpansionMode::Count)][READ_CHANNEL_NONE + 1] = {
    {0, 0xff, 1, 0xff, 0xff, 0xff, 0xff, 0xff, 2},
    {0, 0xff, 1, 0xff, 0xff, 0xff, 0xff, 2, 3},
    {0, 0xff, 1, 0xff, 0xff, 2, 3, 0xff, 4},
    {0, 0xff, 1, 0xff, 0xff, 2, 3, 4, 5},
    {0, 1, 2, 0xff, 0xff, 3, 4, 5, 6},
    {0, 1, 2, 3, 4, 5, 6, 7, 8},
  };
  static constexpr ReadChannel channels[] = {c0, c1, c2, c3, c4, c5, c6, c7};
  constexpr u32 input_channels = luts[static_cast<u8>(mode)][READ_CHANNEL_NONE];

  for (u32 frame = 0; frame < num_frames; frame++)
  {
    for (u32 channel = 0; channel < input_channels; channel++)
      *(dest++) = src[luts[static_cast<u8>(mode)][channels[channel]]];
    src += input_channels;
  }
}
