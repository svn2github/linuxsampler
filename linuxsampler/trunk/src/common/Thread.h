/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
 *   Copyright (C) 2005 - 2008 Christian Schoenebeck                       *
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

#ifndef __LS_THREAD_H__
#define __LS_THREAD_H__

//FIXME: this is a temorary solution because of problems with condition variables we use a polling lock in SignalStartThread()
#if defined(WIN32)
#define WIN32_SIGNALSTARTTHREAD_WORKAROUND 1
#endif

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#if defined(WIN32)
#include <windows.h>
#else
#include <sched.h>
#include <sys/mman.h>
#include <memory.h>
#include <pthread.h>
#endif
#include <errno.h>

#include "Condition.h"

namespace LinuxSampler {

/// Abstract base class for classes that need to run in an own thread.
class Thread {
    public:
        Thread(bool LockMemory, bool RealTime, int PriorityMax, int PriorityDelta);
        virtual ~Thread();
        virtual int  StartThread();
        virtual int  StopThread();
        virtual int  SignalStartThread();
        virtual int  SignalStopThread();

        inline void TestCancel() {
#if CONFIG_PTHREAD_TESTCANCEL
            pthread_testcancel();
#endif
        }

        virtual bool IsRunning();
        virtual int  SetSchedulingPriority(); //FIXME: should be private
        virtual int  LockMemory();            //FIXME: should be private
        virtual void EnableDestructor();      //FIXME: should be private
        virtual int  Destructor();            //FIXME: should be private
        virtual int  Main() = 0; ///< This method needs to be implemented by the descendant and is the entry point for the new thread. FIXME: should be protected

        /**
         * Allocates an aligned block of memory. Allocated memory blocks
         * need to be freed using freeAlignedMem().
         *
         * @param boundary - the alignement boundary, usually a power of 2
         *                   e.g. 4 but it can be an arbitrary number
         *                   between 1 and 128
         * @param size     - size in bytes to be allocated
         * @returns  pointer to the allocated memory block
         */
        static void* allocAlignedMem(size_t boundary, size_t size) {
            unsigned char *ptr = (unsigned char *)malloc(size+boundary);
            size_t offset = boundary - ((size_t)ptr % boundary);
            ptr[offset-1] = (unsigned char)offset;
            return (ptr + offset);
        }

        /**
         * Frees an aligned block of memory allocated with allocAlignedMem()
         *
         * @param ptr - pointer to the memory block
         */
        static void freeAlignedMem(void *ptr) {
            unsigned char *p = (unsigned char *)ptr;
            p -= p[-1];
            free(p);
        }

        /**
         * Locks a region of memory in physical RAM.
         *
         * @param addr - address of the memory block
         * @param size - size of the memory block
         * @return true if the locking succeded, otherwise false
         */
        static bool lockMemory(void *addr, size_t size) {
            #if defined(WIN32)
            return VirtualLock(addr, size);
            #else
            return !mlock(addr, size);
            #endif
        }

        /**
         * Unlocks a region of memory in physical RAM.
         *
         * @param addr - address of the memory block
         * @param size - size of the memory block
         * @return true if the unlocking succeded, otherwise false
         */
        static bool unlockMemory(void *addr, size_t size) {
            #if defined(WIN32)
            return VirtualUnlock(addr, size);
            #else
            return !munlock(addr, size);
            #endif
        }

    private:
    #if defined(WIN32)
        HANDLE hThread;
        DWORD lpThreadId;
        #if defined(WIN32_SIGNALSTARTTHREAD_WORKAROUND)
        bool win32isRunning;
        #endif
    #else
        pthread_attr_t  __thread_attr;
        pthread_t       __thread_id;
        pthread_key_t   __thread_destructor_key;
    #endif
        Condition       RunningCondition;
        int             PriorityMax;
        int             PriorityDelta;
        bool            isRealTime;
        bool            bLockedMemory;
};

} // namespace LinuxSampler

#endif // __LS_THREAD_H__
