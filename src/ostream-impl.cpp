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

#include "ostream-impl.hpp"
#include "string-utils.hpp"

// constructor
flog::ostream_impl::ostream_impl(std::ostream& stream) :
    m_stream{stream} {
}

// worker functions
void flog::ostream_impl::log(const log_data& data) {
    char buffer[2048];
    if(data.is_initial) {
        sprintf(buffer, "[%s][%s]: %s",
                flog::to_string(data.date).c_str(),
                level2str(data.level),
                data.description.c_str());
    } else {
        sprintf(buffer, "                                : %s",
                data.description.c_str());
    }
    m_stream << buffer << std::endl;
}
