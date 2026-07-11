// SPDX-FileCopyrightText: 2026 RlyehPSX <https://github.com/RlyehPSX>
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Required behavior:
//
// 1. Reject a null output pointer. There is nowhere to store either the
//    converted value or the deterministic failure value in that case.
//
// 2. Zero-initialize *result before calling a platform API. If conversion
//    fails, callers that accidentally inspect the value still receive a
//    deterministic empty std::tm rather than uninitialized memory.
//
// 3. Select the platform API at compile time:
//
//      Windows (_WIN32):
//        - Call localtime_s with result and the address of timestamp.
//        - localtime_s returns zero on success.
//
//      POSIX (macOS, Linux, and Android):
//        - Call localtime_r with the address of timestamp and result.
//        - localtime_r returns result on success and nullptr on failure.
//
// 4. Translate the platform-specific return value into this function's simple
//    Boolean contract.
//
// Keep formatting out of this helper. Its only responsibility is safely
// converting std::time_t to a caller-owned local std::tm. Callers can then use
// fmt, strftime, or another presentation layer as appropriate.

#include "time_util.h"
#include <ctime>

bool TimeUtil::ToLocalTime(std::time_t timestamp, std::tm* result) {
    if (result == nullptr) return false;

    *result = {};

    #ifdef _WIN32
        return localtime_s(result, &timestamp) == 0;

    #else
        return localtime_r(&timestamp, result) != nullptr;

    #endif
}
