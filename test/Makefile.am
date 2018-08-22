#
# Copyright 2018 - Soroush Rabiei <soroush@ametisco.ir>
# This file is part of libflog.
#
# libflog is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# libflog is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with libflog.  If not, see <http://www.gnu.org/licenses/>.

ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I m4
AUTOMAKE_OPTIONS = subdir-objects

AM_CPPFLAGS = \
    --pedantic -Wall -Werror \
    $(PTHREAD_CFLAGS) \
    -I$(srcdir)/..

check_PROGRAMS = \
    stderr_logger \
    stderr_logger_mt \
    file_logger_mt

stderr_logger_SOURCES = \
    stderr-logger.cpp

stderr_logger_LDADD = \
    ../src/libflog.la \
    $(PTHREAD_LIBS) \
    $(PTHREAD_CFLAGS)

stderr_logger_mt_SOURCES = \
    stderr-logger-mt.cpp

stderr_logger_mt_LDADD = \
    ../src/libflog.la \
    $(PTHREAD_LIBS) \
    $(PTHREAD_CFLAGS)

file_logger_mt_SOURCES = \
    file-logger-mt.cpp

file_logger_mt_LDADD = \
    ../src/libflog.la \
    $(PTHREAD_LIBS) \
    $(PTHREAD_CFLAGS)

TESTS = $(check_PROGRAMS)
