/*
 * Copyright 2018-2020 - Soroush Rabiei <soroush@ametisco.ir>
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

#ifndef LIBFLOG_EXPORT_HPP
#define LIBFLOG_EXPORT_HPP

#if defined(LIBFLOG_EXPORT)
    #if defined(_MSC_VER)
        #define LIBFLOG_API __declspec(dllexport)
    #else
        #define LIBFLOG_API __attribute__((visibility("default")))
    #endif
#elif defined(LIBFLOG_STATIC)
    #define LIBFLOG_API
#else
    #if defined(_MSC_VER)
            #define LIBFLOG_API __declspec(dllimport)
    #else
            #define LIBFLOG_API
    #endif
#endif

#endif // LIBFLOG_EXPORT_HPP