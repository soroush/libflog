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
#include <cassert>
#include <thread>
#include <forward_list>
#include <random>
#include <chrono>
#include "../src/stderr-logger.hpp"

std::string random_string(size_t length) {
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

void runner() {
    static std::default_random_engine gen1;
    static std::default_random_engine gen2;
    static std::uniform_int_distribution<int> distribution(1,100);
    static std::uniform_int_distribution<int> sleep_time_dist(0,5);
    int length = distribution(gen1);
    auto l = flog::stderr_logger::create();
    for(int i = 0; i < 1000; ++i) {
        l->log(flog::level_t::TRACE,  "%s", random_string(length).c_str());
        std::this_thread::sleep_for(std::chrono::milliseconds{sleep_time_dist(gen2)});
        l->log(flog::level_t::DEBUG,  "%s", random_string(length).c_str());
        std::this_thread::sleep_for(std::chrono::milliseconds{sleep_time_dist(gen2)});
        l->log(flog::level_t::ERROR_, "%s", random_string(length).c_str());
        std::this_thread::sleep_for(std::chrono::milliseconds{sleep_time_dist(gen2)});
        l->log(flog::level_t::FATAL,  "%s", random_string(length).c_str());
        std::this_thread::sleep_for(std::chrono::milliseconds{sleep_time_dist(gen2)});
    }
    l->flush(std::chrono::seconds{10});
    auto l2 = flog::stderr_logger::create();
    auto l3 = flog::stderr_logger::create();
    assert(l == l2);
    assert(l == l3);
}

int main(int argc, char* argv[]) {
    std::forward_list<std::thread> threads;
    for(int i=0; i<10; ++i) {
        threads.emplace_front(&runner);
    }
    for(std::thread& thread : threads) {
        thread.join();
    }
    exit(EXIT_SUCCESS);
}
