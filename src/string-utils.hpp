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

#ifndef FASTLOG_STRING_UTILS_HPP
#define FASTLOG_STRING_UTILS_HPP

#include <string>
#include <chrono>
#include "logger.hpp"

namespace flog {
const std::string to_string(const std::chrono::system_clock::time_point& tp);
const char* level2str(flog::level_t l);
}

#endif // FASTLOG_STRING_UTILS_HPP
