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

#ifndef FASTLOG_LOGGER_HPP
#define FASTLOG_LOGGER_HPP

#include <stdarg.h>
#include <chrono>
#include <string>
#include <thread>
#include <mutex>
#include <atomic>
#include <queue>
#include <functional>
#include "semaphore.hpp"

namespace flog {

enum class backend_t {
    DISABLED = 0,
    // DATABASE = 1,
    STDERR   = 2,
};
enum class level_t {
    OFF   = 0,  // The highest possible rank and is intended to turn off logging.
    FATAL = 1,  // Designates very severe error events that will presumably lead the application to abort.
    ERROR_ = 2, // Designates error events that might still allow the application to continue running.
    WARN  = 3,  // Designates potentially harmful situations.
    INFO  = 4,  // Designates informational messages that highlight the progress of the application at coarse-grained level.
    DEBUG = 5,  // Designates fine-grained informational events that are most useful to debug an application.
    TRACE = 6,  // Designates finer-grained informational events than the DEBUG.
    ALL   = 7,  // All levels
};

struct log_data {
    std::chrono::system_clock::time_point date;
    level_t level;
    std::string description;
    bool is_initial;
    std::string level_str() const;
};

class logger {
public:
    // Logging callbacks for initial logs
    void log(std::chrono::system_clock::time_point date,
             level_t l, const char* format, ...);

    void log(level_t l, const char* format, ...);

    void log(const char* format, ...);

    // Logging callbacks for following logs
    void logc(level_t l, const char* format, ...);

    void logc(const char* format, ...);

    void flush(std::chrono::milliseconds timout) ;

    // Setters
    void set_backend(backend_t t) ;

    // Static instance
    static logger* instance() ;

    // Set external callback
    void set_callback(std::function<void(log_data)> callee);
private:
    // constructor, to be private to avoid instantiation
    logger();
    ~logger();

    // thread callback
    void worker();

    // static data members
    static logger* m_instance;
    // instance data members
    level_t m_logging_level;
    backend_t m_backend;
    std::thread m_worker_thread;
    std::atomic_bool m_is_running;
    std::deque<log_data> m_log_queue;
    std::mutex m_queue_lock;
    flog::semaphore m_queue_sem;
    // Backend functions for initial logs
    void log(std::chrono::system_clock::time_point date, level_t l,
             const char* format, va_list argptr) ;
    // Backend functions for following logs
    void logc(level_t l, const char* format, va_list argptr) ;
    // worker functions
    void log_cerr(const log_data& data);
    const char* level2str(level_t l);
    // External log callback
    std::function<void(log_data)> m_callback;
};

}

#endif // FASTLOG_LOGGER_HPP
