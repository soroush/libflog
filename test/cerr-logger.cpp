/*
 * Copyright 2017 - FDE Co., <rabiei@fdeshragh.com>
 * This file is part of libfde_network.
 *
 * libfde_network is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libfde_network is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libfde_network.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <string>
#include <random>
#include <algorithm>
#include <iostream>
#include "../src/flog.hpp"

using namespace flog;

std::string random_string(size_t length)
{
    auto randchar = []() -> char {
        const char charset[] =
        "0123456789      "
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::string str(length, 0);
    std::generate_n(str.begin(), length, randchar);
    return str;
}

int main(int argc, char *argv[])
{
    auto l = logger::instance();
    l->set_backend(backend_t::STDERR);
    for(int i = 0; i < 1000; ++i) {
        l->log(level_t::TRACE, "TRACE LOG");
        l->log(level_t::DEBUG, "D RANDOM: \"%s\"", random_string(rand() % 10).c_str());
        l->log(level_t::ERROR_, "E RANDOM: \"%s\"", random_string(rand() % 10).c_str());
        l->log(level_t::FATAL, "F RANDOM: \"%s\"", random_string(rand() % 10).c_str());
    }
    l->flush(std::chrono::milliseconds{});
    exit(EXIT_SUCCESS);
}
