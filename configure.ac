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


AC_PREREQ([2.69])
AC_INIT([libflog], [0.2.0])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
LT_INIT([static shared pic-only])

# Configure automake
AM_INIT_AUTOMAKE
AM_SILENT_RULES([yes])

# Check for C++11 compiler
AX_CXX_COMPILE_STDCXX_11([noext],[mandatory])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.

AX_PTHREAD()

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 test/Makefile
                 libflog.pc])

AC_SUBST([FLOG_SO_VERSION], [1:0:1])
AC_SUBST([FLOG_API_VERSION], [0.2.0])

AC_OUTPUT
