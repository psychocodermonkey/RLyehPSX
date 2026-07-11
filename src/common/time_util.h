// SPDX-FileCopyrightText: 2026 RlyehPSX <https://github.com/RlyehPSX>
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ctime>

namespace TimeUtil {

/// Converts a Unix timestamp to local calendar time using the host platform's
/// current timezone rules.
///
/// The converted value is written to caller-owned storage so callers never
/// depend on the shared static storage returned by std::localtime(). This also
/// gives the function the same ownership and thread-safety model on Windows,
/// macOS, Linux, and Android.
///
/// Returns true when the conversion succeeds. Returns false when result is
/// null or the timestamp cannot be represented as local calendar time. On
/// failure, a non-null result should contain a zero-initialized std::tm.
bool ToLocalTime(std::time_t timestamp, std::tm* result);

} // namespace TimeUtil
