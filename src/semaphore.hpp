/*
 * libtidm_common - Common tools and utilities of the TIDM/OI
 * Copyright (C) 2017 TIDM Co.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
 */

#ifndef LIBFLOG_SEMAPHORE_HPP
#define LIBFLOG_SEMAPHORE_HPP

#include <mutex>
#include <condition_variable>
#include <chrono>

namespace flog {
class semaphore {
    public:
        semaphore(int count = 0);
        void notify();
        void wait();
        bool wait_for(const std::chrono::nanoseconds &);
        bool try_wait();

    private:
        std::mutex m_mtx;
        std::condition_variable m_cv;
        int m_count;
};
}

#endif // LIBFLOG_SEMAPHORE_HPP
