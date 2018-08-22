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

#include "logger.hpp"
#include <iostream>


// Logging callbacks for initial logs
void flog::logger::log(std::chrono::system_clock::time_point date,
                       level_t l, const char* format, ...) {
    va_list argptr;
    va_start(argptr, format);
    log(date, l, format, argptr);
    va_end(argptr);
}

void flog::logger::log(level_t l, const char* format, ...) {
    va_list argptr;
    va_start(argptr, format);
    logger::log(std::chrono::system_clock::now(), l, format, argptr);
    va_end(argptr);
}

void flog::logger::log(const char* format, ...) {
    level_t l = level_t::INFO;
    va_list argptr;
    va_start(argptr, format);
    logger::log(std::chrono::system_clock::now(), l, format, argptr);
    va_end(argptr);
}

// Logging callbacks for following logs
void flog::logger::logc(level_t l, const char* format, ...) {
    va_list argptr;
    va_start(argptr, format);
    logger::logc(l, format, argptr);
    va_end(argptr);
}

void flog::logger::logc(const char* format, ...) {
    level_t l = level_t::INFO;
    va_list argptr;
    va_start(argptr, format);
    logger::logc(l, format, argptr);
    va_end(argptr);
}

void flog::logger::flush(std::chrono::milliseconds timout) {
    if(timout.count() == 0) {
        while(!m_log_queue.empty()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    } else {
        std::chrono::system_clock::time_point then = std::chrono::system_clock::now();
        std::chrono::milliseconds elapsed_time{0};
        while(!m_log_queue.empty() && elapsed_time < timout) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            auto now = std::chrono::system_clock::now();
            elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(now - then);
        }
    }
}

// Setters
void flog::logger::set_level(flog::level_t level) {
    m_logging_level = level;
}

// Set external callback
void flog::logger::set_callback(std::function<void(log_data)> callee) {
    m_callback = callee;
}

// constructor, to be private to avoid instantiation
flog::logger::logger()
    : m_logging_level(level_t::ALL),
      m_is_running(true) {
    m_worker_thread = std::thread(&logger::worker, this);
}

flog::logger::~logger() {
    m_is_running.store(false);
    m_worker_thread.join();
}

// thread callback
void flog::logger::worker() {
    while(m_is_running.load()) {
        log_data d;
        if(!m_queue_sem.wait_for(std::chrono::milliseconds{10})) {
            continue;
        }
        std::unique_lock<std::mutex> guard(m_queue_lock);
        if(!m_log_queue.empty()) {
            d = m_log_queue.front();
            m_log_queue.pop_front();
        } else {
            continue;
        }
        guard.unlock();
        this->log(d);
    }
}

// Backend functions for initial logs
void flog::logger::log(std::chrono::system_clock::time_point date, level_t l,
                       const char* format, va_list argptr) {
    if(l > m_logging_level) {
        return;
    }
    char buffer[2048];
    vsnprintf(buffer, 2048, format, argptr);
    log_data d;
    d.date = date;
    d.level = l;
    d.description = buffer;
    d.is_initial = true;
    std::lock_guard<std::mutex> guard(m_queue_lock);
    m_log_queue.push_back(d);
    if(m_callback) {
        m_callback(d);
    }
    m_queue_sem.notify();
}

// Backend functions for following logs
void flog::logger::logc(level_t l, const char* format, va_list argptr) {
    if(l > m_logging_level) {
        return;
    }
    char buffer[2048];
    vsnprintf(buffer, 2048, format, argptr);
    log_data d;
    d.level = l;
    d.description = buffer;
    d.is_initial = false;
    std::lock_guard<std::mutex> guard(m_queue_lock);
    m_log_queue.push_back(d);
    if(m_callback) {
        m_callback(d);
    }
    m_queue_sem.notify();
}
