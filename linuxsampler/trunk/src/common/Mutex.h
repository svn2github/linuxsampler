/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
 *   Copyright (C) 2005, 2006 Christian Schoenebeck                        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the Free Software           *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston,                 *
 *   MA  02111-1307  USA                                                   *
 ***************************************************************************/

#ifndef __MUTEX_H__
#define __MUTEX_H__

#include <pthread.h>

namespace LinuxSampler {

/** @brief Mutual exclusive objects
 *
 * This class provides the classical thread / process synchronisation
 * technique called Mutex. It is used to protect critical sections, that is
 * resources (typically data structures) from being used at the same time by
 * different threads or processes which otherwise might turn into undefined
 * and of course undesired behavior.
 *
 * Note: as this technique might block the calling thread and also implies
 * a system call, this should not be used directly in realtime sensitive
 * threads!
 */
class Mutex {
    public:
        /**
         * Constructor
         */    
        Mutex();

        /**
         * Destructor
         */
        virtual ~Mutex();

        /** @brief Lock this Mutex.
         *
         * If this Mutex object is currently be locked by another thread,
         * then the calling thread will be blocked until the other thread
         * unlocks this Mutex object. The calling thread though can safely
         * call this method several times without danger to be blocked
         * himself.
         *
         * The calling thread should call Unlock() as soon as the critical
         * section was left.
         */      
        void Lock();

        /** @brief Try to lock this Mutex.
         *
         * Same as Lock() except that this method won't block the calling
         * thread in case this Mutex object is currently locked by another
         * thread. So this call will always immediately return and the
         * return value has to be checked if the locking request was
         * successful or not.
         *
         * @returns  true if the Mutex object could be locked, false if the
         *           Mutex is currently locked by another thread
         */
        bool Trylock();

        /** @brief Unlock this Mutex.
         *
         * If other threads are currently blocked and waiting due to a
         * Lock() call, one of them will be awaken.
         */
        void Unlock();
        
    protected:
        pthread_mutex_t     __posix_mutex;
        pthread_mutexattr_t __posix_mutexattr;
};

} // namespace LinuxSampler

#endif // __MUTEX_H__
