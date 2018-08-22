/*
 * Copyright 2018 - Soroush Rabiei <soroush@ametisco.ir>
 * This file is part of libflog.
 *
 * libflog is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libflog is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libflog.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "string-utils.hpp"

namespace flog {
template <typename clock>
const std::string to_string_impl(const typename clock::time_point& tp) {
    auto ttime_t = clock::to_time_t(tp);
    auto tp_sec = clock::from_time_t(ttime_t);
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(tp - tp_sec);
    std::tm* ttm = ::localtime(&ttime_t);
    static const char date_time_format[] = "%Y-%m-%d %H:%M:%S";
    char time_str[] = "yyyy-mm-dd HH:MM:SS.fff";
    ::strftime(time_str, 23, date_time_format, ttm);
    char final[2048];
    #ifdef _WIN32
    sprintf(final, "%s.%03lld", time_str, ms.count());
    #else
    sprintf(final, "%s.%03ld", time_str, ms.count());
    #endif
    return std::string(final);
}
}

const std::string flog::to_string(const std::chrono::system_clock::time_point& tp) {
    return flog::to_string_impl<typename std::chrono::system_clock>(tp);
}

const char* flog::level2str(flog::level_t l) {
    static const char* level_str_map[] = {
        "FATAL",
        "ERROR",
        " WARN",
        " INFO",
        "DEBUG",
        "TRACE",
    };
    return level_str_map[static_cast<int>(l) - 1];
}
