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

#include "semaphore.hpp"

flog::semaphore::semaphore(int count): m_count(count)
{
}

void flog::semaphore::notify()
{
    std::unique_lock<std::mutex> lock(m_mtx);
    ++m_count;
    m_cv.notify_one();
}

void flog::semaphore::wait()
{
    std::unique_lock<std::mutex> lock(m_mtx);
    while(m_count == 0) {
        m_cv.wait(lock);
    }
    --m_count;
}

bool flog::semaphore::wait_for(const std::chrono::nanoseconds &duration)
{
    std::unique_lock<std::mutex> lock(m_mtx);
    while(m_count == 0) {
        if(m_cv.wait_for(lock, duration) == std::cv_status::timeout) {
            return false;
        }
    }
    --m_count;
    return true;
}

bool flog::semaphore::try_wait()
{
    std::lock_guard<std::mutex> lock(m_mtx);
    if(!m_count) {
        return false;
    }
    --m_count;
    return true;
}
