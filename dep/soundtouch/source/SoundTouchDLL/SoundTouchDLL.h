//////////////////////////////////////////////////////////////////////////////
///
/// SoundTouch DLL wrapper - wraps SoundTouch routines into a Dynamic Load
/// Library interface.
///
/// Author        : Copyright (c) Olli Parviainen
/// Author e-mail : oparviai 'at' iki.fi
/// SoundTouch WWW: http://www.surina.net/soundtouch
///
////////////////////////////////////////////////////////////////////////////////
//
// License :
//
//  SoundTouch audio processing library
//  Copyright (c) Olli Parviainen
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _SoundTouchDLL_h_
#define _SoundTouchDLL_h_

#if defined(_WIN32) || defined(WIN32)
    // Windows
    #ifndef __cplusplus
        #error "Expected g++"
    #endif

    #ifdef DLL_EXPORTS
        #define SOUNDTOUCHDLL_API extern "C" __declspec(dllexport)
    #else
        #define SOUNDTOUCHDLL_API extern "C" __declspec(dllimport)
    #endif

#else
    // GNU version

    #if defined(DLL_EXPORTS) || defined(SoundTouchDLL_EXPORTS)
        // GCC declaration for exporting functions
        #define SOUNDTOUCHDLL_API extern "C" __attribute__((__visibility__("default")))
    #else
        // import function
        #define SOUNDTOUCHDLL_API extern "C"
    #endif

    // Linux-replacements for Windows declarations:
    #define __cdecl
    typedef unsigned int DWORD;
    #define FALSE    0
    #define TRUE    1

#endif

typedef void * HANDLE;

/// Create a new instance of SoundTouch processor.
SOUNDTOUCHDLL_API HANDLE __cdecl soundtouch_createInstance();

/// Destroys a SoundTouch processor instance.
SOUNDTOUCHDLL_API void __cdecl soundtouch_destroyInstance(HANDLE h);

/// Get SoundTouch library version string
SOUNDTOUCHDLL_API const char *__cdecl soundtouch_getVersionString();

/// Get SoundTouch library version string - alternative function for
/// environments that can't properly handle character string as return value
SOUNDTOUCHDLL_API void __cdecl soundtouch_getVersionString2(char* versionString, int bufferSize);

/// Get SoundTouch library version Id
SOUNDTOUCHDLL_API unsigned int __cdecl soundtouch_getVersionId();

/// Sets new rate control value. Normal rate = 1.0, smaller values
/// represent slower rate, larger faster rates.
SOUNDTOUCHDLL_API void __cdecl soundtouch_setRate(HANDLE h, float newRate);

/// Sets new tempo control value. Normal tempo = 1.0, smaller values
/// represent slower tempo, larger faster tempo.
SOUNDTOUCHDLL_API void __cdecl soundtouch_setTempo(HANDLE h, float newTempo);

/// Sets new rate control value as a difference in percents compared
/// to the original rate (-50 .. +100 %);
SOUNDTOUCHDLL_API void __cdecl soundtouch_setRateChange(HANDLE h, float newRate);

/// Sets new tempo control value as a difference in percents compared
/// to the original tempo (-50 .. +100 %);
SOUNDTOUCHDLL_API void __cdecl soundtouch_setTempoChange(HANDLE h, float newTempo);

/// Sets new pitch control value. Original pitch = 1.0, smaller values
/// represent lower pitches, larger values higher pitch.
SOUNDTOUCHDLL_API void __cdecl soundtouch_setPitch(HANDLE h, float newPitch);

/// Sets pitch change in octaves compared to the original pitch
/// (-1.00 .. +1.00);
SOUNDTOUCHDLL_API void __cdecl soundtouch_setPitchOctaves(HANDLE h, float newPitch);

/// Sets pitch change in semi-tones compared to the original pitch
/// (-12 .. +12);
SOUNDTOUCHDLL_API void __cdecl soundtouch_setPitchSemiTones(HANDLE h, float newPitch);


/// Sets the number of channels, 1 = mono, 2 = stereo, n = multichannel
SOUNDTOUCHDLL_API int __cdecl soundtouch_setChannels(HANDLE h, unsigned int numChannels);

/// Sets sample rate.
SOUNDTOUCHDLL_API int __cdecl soundtouch_setSampleRate(HANDLE h, unsigned int srate);

/// Flushes the last samples from the processing pipeline to the output.
/// Clears also the internal processing buffers.
//
/// Note: This function is meant for extracting the last samples of a sound
/// stream. This function may introduce additional blank samples in the end
/// of the sound stream, and thus it's not recommended to call this function
/// in the middle of a sound stream.
SOUNDTOUCHDLL_API int __cdecl soundtouch_flush(HANDLE h);

/// Adds 'numSamples' pcs of samples from the 'samples' memory position into
/// the input of the object. Notice that sample rate _has_to_ be set before
/// calling this function, otherwise throws a runtime_error exception.
SOUNDTOUCHDLL_API int __cdecl soundtouch_putSamples(HANDLE h,
        const float *samples,       ///< Pointer to sample buffer.
        unsigned int numSamples     ///< Number of sample frames in buffer. Notice
                                    ///< that in case of multi-channel sound a single
                                    ///< sample frame contains data for all channels.
);

/// int16 version of soundtouch_putSamples(): This accept int16 (short) sample data
/// and internally converts it to float format before processing
SOUNDTOUCHDLL_API void __cdecl soundtouch_putSamples_i16(HANDLE h,
        const short *samples,       ///< Pointer to sample buffer.
        unsigned int numSamples     ///< Number of sample frames in buffer. Notice
                                    ///< that in case of multi-channel sound a single
                                    ///< sample frame contains data for all channels.
);


/// Clears all the samples in the object's output and internal processing
/// buffers.
SOUNDTOUCHDLL_API void __cdecl soundtouch_clear(HANDLE h);

// 2026-08-01 R'Lyeh PSX ========================== - START - ========================
// - Copied from soundtouch/include/SoundTouch.h
// - Expose SETTING_* from within SoundTouchDLL for downstream consumers
// - Including ALL settings for future compatability

// Available setting IDs for the 'setSetting' & 'get_setting' functions:

/// Enable/disable anti-alias filter in pitch transposer (0 = disable)
#define SETTING_USE_AA_FILTER 0

/// Pitch transposer anti-alias filter length (8 .. 128 taps, default = 32)
#define SETTING_AA_FILTER_LENGTH 1

/// Enable/disable quick seeking algorithm in tempo changer routine
/// (enabling quick seeking lowers CPU utilization but causes a minor sound
///  quality compromising)
#define SETTING_USE_QUICKSEEK 2

/// Time-stretch algorithm single processing sequence length in milliseconds. This determines
/// to how long sequences the original sound is chopped in the time-stretch algorithm.
/// See "STTypes.h" or README for more information.
#define SETTING_SEQUENCE_MS 3

/// Time-stretch algorithm seeking window length in milliseconds for algorithm that finds the
/// best possible overlapping location. This determines from how wide window the algorithm
/// may look for an optimal joining location when mixing the sound sequences back together.
/// See "STTypes.h" or README for more information.
#define SETTING_SEEKWINDOW_MS 4

/// Time-stretch algorithm overlap length in milliseconds. When the chopped sound sequences
/// are mixed back together, to form a continuous sound stream, this parameter defines over
/// how long period the two consecutive sequences are let to overlap each other.
/// See "STTypes.h" or README for more information.
#define SETTING_OVERLAP_MS 5

/// Call "getSetting" with this ID to query processing sequence size in samples.
/// This value gives approximate value of how many input samples you'll need to
/// feed into SoundTouch after initial buffering to get out a new batch of
/// output samples.
///
/// This value does not include initial buffering at beginning of a new processing
/// stream, use SETTING_INITIAL_LATENCY to get the initial buffering size.
///
/// Notices:
/// - This is read-only parameter, i.e. setSetting ignores this parameter
/// - This parameter value is not constant but change depending on
///   tempo/pitch/rate/samplerate settings.
#define SETTING_NOMINAL_INPUT_SEQUENCE 6

/// Call "getSetting" with this ID to query nominal average processing output
/// size in samples. This value tells approcimate value how many output samples
/// SoundTouch outputs once it does DSP processing run for a batch of input samples.
///
/// Notices:
/// - This is read-only parameter, i.e. setSetting ignores this parameter
/// - This parameter value is not constant but change depending on
///   tempo/pitch/rate/samplerate settings.
#define SETTING_NOMINAL_OUTPUT_SEQUENCE 7

/// Call "getSetting" with this ID to query initial processing latency, i.e.
/// approx. how many samples you'll need to enter to SoundTouch pipeline before
/// you can expect to get first batch of ready output samples out.
///
/// After the first output batch, you can then expect to get approx.
/// SETTING_NOMINAL_OUTPUT_SEQUENCE ready samples out for every
/// SETTING_NOMINAL_INPUT_SEQUENCE samples that you enter into SoundTouch.
///
/// Example:
///     processing with parameter -tempo=5
///     => initial latency = 5509 samples
///        input sequence  = 4167 samples
///        output sequence = 3969 samples
///
/// Accordingly, you can expect to feed in approx. 5509 samples at beginning of
/// the stream, and then you'll get out the first 3969 samples. After that, for
/// every approx. 4167 samples that you'll put in, you'll receive again approx.
/// 3969 samples out.
///
/// This also means that average latency during stream processing is
/// INITIAL_LATENCY-OUTPUT_SEQUENCE/2, in the above example case 5509-3969/2
/// = 3524 samples
///
/// Notices:
/// - This is read-only parameter, i.e. setSetting ignores this parameter
/// - This parameter value is not constant but change depending on
///   tempo/pitch/rate/samplerate settings.
#define SETTING_INITIAL_LATENCY 8

// 2026-08-01 R'Lyeh PSX ========================== - END - ==========================

/// Changes a setting controlling the processing system behaviour. See the
/// 'SETTING_...' defines for available setting ID's.
///
/// \return 'nonzero' if the setting was successfully changed, otherwise zero
SOUNDTOUCHDLL_API int __cdecl soundtouch_setSetting(HANDLE h,
        int settingId,   ///< Setting ID number. see SETTING_... defines.
        int value        ///< New setting value.
);

/// Reads a setting controlling the processing system behaviour. See the
/// 'SETTING_...' defines for available setting ID's.
///
/// \return the setting value.
SOUNDTOUCHDLL_API int __cdecl soundtouch_getSetting(HANDLE h,
        int settingId    ///< Setting ID number, see SETTING_... defines.
);


/// Returns number of samples currently unprocessed.
SOUNDTOUCHDLL_API unsigned int __cdecl soundtouch_numUnprocessedSamples(HANDLE h);

/// Adjusts book-keeping so that given number of samples are removed from beginning of the
/// sample buffer without copying them anywhere.
///
/// Used to reduce the number of samples in the buffer when accessing the sample buffer directly
/// with 'ptrBegin' function.
SOUNDTOUCHDLL_API unsigned int __cdecl soundtouch_receiveSamples(HANDLE h,
        float *outBuffer,           ///< Buffer where to copy output samples.
        unsigned int maxSamples     ///< How many samples to receive at max.
);


/// int16 version of soundtouch_receiveSamples(): This converts internal float samples
/// into int16 (short) return data type
SOUNDTOUCHDLL_API unsigned int __cdecl soundtouch_receiveSamples_i16(HANDLE h,
        short *outBuffer,           ///< Buffer where to copy output samples.
        unsigned int maxSamples     ///< How many samples to receive at max.
);

/// Returns number of samples currently available.
SOUNDTOUCHDLL_API unsigned int __cdecl soundtouch_numSamples(HANDLE h);

/// Returns nonzero if there aren't any samples available for outputting.
SOUNDTOUCHDLL_API int __cdecl soundtouch_isEmpty(HANDLE h);

/// Create a new instance of BPM detector
SOUNDTOUCHDLL_API HANDLE __cdecl bpm_createInstance(int numChannels, int sampleRate);

/// Destroys a BPM detector instance.
SOUNDTOUCHDLL_API void __cdecl bpm_destroyInstance(HANDLE h);

/// Feed 'numSamples' sample frames from 'samples' into the BPM detector.
SOUNDTOUCHDLL_API void __cdecl bpm_putSamples(HANDLE h,
        const float *samples,           ///< Pointer to sample buffer.
        unsigned int numSamples         ///< Number of samples in buffer. Notice
                                        ///< that in case of stereo-sound a single sample
                                        ///< contains data for both channels.
        );

/// Feed 'numSamples' sample frames from 'samples' into the BPM detector.
/// 16bit int sample format version.
SOUNDTOUCHDLL_API void __cdecl bpm_putSamples_i16(HANDLE h,
        const short *samples,           ///< Pointer to sample buffer.
        unsigned int numSamples         ///< Number of samples in buffer. Notice
                                        ///< that in case of stereo-sound a single sample
                                        ///< contains data for both channels.
        );

/// Analyzes the results and returns the BPM rate. Use this function to read result
/// after whole song data has been input to the class by consecutive calls of
/// 'inputSamples' function.
///
/// \return Beats-per-minute rate, or zero if detection failed.
SOUNDTOUCHDLL_API float __cdecl bpm_getBpm(HANDLE h);

/// Get beat position arrays. Note: The array includes also really low beat detection values
/// in absence of clear strong beats. Consumer may wish to filter low values away.
/// - "pos" receive array of beat positions
/// - "values" receive array of beat detection strengths
/// - max_num indicates max.size of "pos" and "values" array.
///
/// You can query a suitable array sized by calling this with nullptr in "pos" & "values".
///
/// \return number of beats in the arrays.
SOUNDTOUCHDLL_API int __cdecl bpm_getBeats(HANDLE h, float *pos, float *strength, int count);

#endif  // _SoundTouchDLL_h_
