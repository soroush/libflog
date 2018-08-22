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

#include "stdout-logger.hpp"
#include "string-utils.hpp"
#include <iostream>

// constructor
flog::stdout_logger::stdout_logger() :
    flog::ostream_impl(std::cout) {
}

flog::logger* flog::stdout_logger::create() {
    static flog::stdout_logger logger_instance;
    return &logger_instance;
}
