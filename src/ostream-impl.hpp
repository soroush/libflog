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

#ifndef FASTLOG_OSTREAM_IMPL_LOGGER_HPP
#define FASTLOG_OSTREAM_IMPL_LOGGER_HPP

#include "logger.hpp"
#include <ostream>

namespace flog {
class ostream_impl : public logger {
public:
    static logger* create();
protected:
    ostream_impl(std::ostream& stream);
    ostream_impl(const ostream_impl&) = delete;
    ~ostream_impl() = default;
    virtual void log(const log_data& data);
    std::ostream& m_stream;
};
}

#endif // FASTLOG_OSTREAM_IMPL_LOGGER_HPP
