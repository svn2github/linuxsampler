/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
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

#ifndef __THREAD_H__
#define __THREAD_H__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/mman.h>
#include <memory.h>
#include <pthread.h>
#include <errno.h>

/// Abstract base class for classes that need to run in an own thread.
class Thread {
    public:
        Thread(bool RealTime, int PriorityMax, int PriorityDelta);
        virtual ~Thread();
        virtual int  StartThread();
        virtual int  StopThread();
        virtual int  SignalStopThread();
        virtual bool IsRunning() { return Running; }
        virtual int  SetSchedulingPriority(); //FIXME: should be private
        virtual void EnableDestructor();      //FIXME: should be private
        virtual int  Destructor();            //FIXME: should be private
        virtual int  Main() = 0; ///< This method needs to be implemented by the descendant and is the entry point for the new thread. FIXME: should be protected
    private:
        pthread_t       __thread_id;
        pthread_key_t   __thread_destructor_key;
        pthread_mutex_t __thread_state_mutex;
        pthread_cond_t  __thread_exit_condition;
        int             PriorityMax;
        int             PriorityDelta;
        bool            Running;
        bool            isRealTime;
};

// Callback functions for the POSIX thread API
void* __pthread_launcher(void* thread);
void  __pthread_destructor(void* thread);

#endif // __THREAD_H__
