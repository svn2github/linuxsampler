/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
 *   Copyright (C) 2005 - 2007 Christian Schoenebeck                       *
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

#include "Thread.h"

// this is the minimum stack size a thread will be spawned with
// if this value is too small, the OS will allocate memory on demand and
// thus might lead to dropouts in realtime threads
// TODO: should be up for testing to get a reasonable good value
#define MIN_STACK_SIZE		524288

namespace LinuxSampler {

// Callback functions for the POSIX thread API
static void* __pthread_launcher(void* thread);
static void  __pthread_destructor(void* thread);

Thread::Thread(bool LockMemory, bool RealTime, int PriorityMax, int PriorityDelta) {
    this->bLockedMemory     = LockMemory;
    this->isRealTime        = RealTime;
    this->PriorityDelta     = PriorityDelta;
    this->PriorityMax       = PriorityMax;
    __thread_destructor_key = 0;
    pthread_attr_init(&__thread_attr);
}

Thread::~Thread() {
    StopThread();
    pthread_attr_destroy(&__thread_attr);
}

/**
 *  Starts the thread. This method will wait until the thread actually
 *  started it's execution before it will return. The abstract method
 *  Main() is the entry point for the new thread. You have to implement the
 *  Main() method in your subclass.
 */
int Thread::StartThread() {
    RunningCondition.Lock();
    if (!RunningCondition.GetUnsafe()) {
        SignalStartThread();
        // wait until thread started execution
        RunningCondition.WaitIf(false);
    }
    RunningCondition.Unlock();
    return 0;
}

/**
 *  Starts the thread. This method will signal to start the thread and
 *  return immediately. Note that the thread might not yet run when this
 *  method returns! The abstract method Main() is the entry point for the
 *  new thread. You have to implement the Main() method in your subclass.
 *
 *  @see StartThread()
 */
int Thread::SignalStartThread() {
    // prepare the thread properties
    int res = pthread_attr_setinheritsched(&__thread_attr, PTHREAD_EXPLICIT_SCHED);
    if (res) {
        std::cerr << "Thread creation failed: Could not inherit thread properties."
                  << std::endl << std::flush;
        RunningCondition.Set(false);
        return res;
    }
    res = pthread_attr_setdetachstate(&__thread_attr, PTHREAD_CREATE_JOINABLE);
    if (res) {
        std::cerr << "Thread creation failed: Could not request a joinable thread."
                  << std::endl << std::flush;
        RunningCondition.Set(false);
        return res;
    }
    res = pthread_attr_setscope(&__thread_attr, PTHREAD_SCOPE_SYSTEM);
    if (res) {
        std::cerr << "Thread creation failed: Could not request system scope for thread scheduling."
                  << std::endl << std::flush;
        RunningCondition.Set(false);
        return res;
    }
    res = pthread_attr_setstacksize(&__thread_attr, MIN_STACK_SIZE);
    if (res) {
        std::cerr << "Thread creation failed: Could not set minimum stack size."
                  << std::endl << std::flush;
        RunningCondition.Set(false);
        return res;
    }
    // Create and run the thread
    res = pthread_create(&this->__thread_id, &__thread_attr, __pthread_launcher, this);
    switch (res) {
        case 0: // Success
            break;
        case EAGAIN:
            std::cerr << "Thread creation failed: System doesn't allow to create another thread."
                      << std::endl << std::flush;
            RunningCondition.Set(false);
            break;
        case EPERM:
            std::cerr << "Thread creation failed: You're lacking permisssions to set required scheduling policy and parameters."
                      << std::endl << std::flush;
            RunningCondition.Set(false);
            break;
        default:
            std::cerr << "Thread creation failed: Unknown cause."
                      << std::endl << std::flush;
            RunningCondition.Set(false);
            break;
    }
    return res;
}

/**
 *  Stops the thread. This method will wait until the thread actually stopped
 *  it's execution before it will return.
 */
int Thread::StopThread() {
    RunningCondition.Lock();
    if (RunningCondition.GetUnsafe()) {
        SignalStopThread();
        // wait until thread stopped execution
        RunningCondition.WaitIf(true);
        pthread_detach(__thread_id);
    }
    RunningCondition.Unlock();
    return 0;
}

/**
 *  Stops the thread. This method will signal to stop the thread and return
 *  immediately. Note that the thread might still run when this method
 *  returns!
 *
 *  @see StopThread()
 */
int Thread::SignalStopThread() {
    //FIXME: segfaults when thread is not yet running
    pthread_cancel(__thread_id);
    return 0;
}

/**
 * Returns @c true in case the thread is currently running.
 */
bool Thread::IsRunning() {
    return RunningCondition.GetUnsafe();
}

/**
 *  Sets the process SCHED_FIFO policy,  if max=1 then set at max priority,
 *  else use min priority. delta is added to the priority so that we can
 *  for example set 3 SCHED_FIFO tasks to different priorities by specifying
 *  delta  0 , -1 , -2  ( 0 = highest priority because -1 is subtracted to the
 *  current priority).
 */
int Thread::SetSchedulingPriority() {
#if !defined(__APPLE__)
    int policy;
    const char* policyDescription = NULL;
    if (isRealTime) { // becomes a RT thread
        policy = SCHED_FIFO;
        policyDescription = "realtime";
    } else { // 'normal', non-RT thread
        policy = SCHED_OTHER;
        policyDescription = "normal (non-RT)";
    }
    // set selected scheduling policy and priority
    struct sched_param schp;
    memset(&schp, 0, sizeof(schp));
    if (isRealTime) { // it is not possible to change priority for the SCHED_OTHER policy
        if (this->PriorityMax == 1) {
            schp.sched_priority = sched_get_priority_max(policy) + this->PriorityDelta;
        }
        if (this->PriorityMax == -1) {
            schp.sched_priority = sched_get_priority_min(policy) + this->PriorityDelta;
        }
    }
    if (pthread_setschedparam(__thread_id, policy, &schp) != 0) {
        std::cerr << "Thread: WARNING, can't assign "
                  << policyDescription
                  << " scheduling to thread!"
                  << std::endl << std::flush;
        return -1;
    }
#endif
    return 0;
}

/**
 * Locks the memory so it will not be swapped out by the operating system.
 */
int Thread::LockMemory() {
#if !defined(__APPLE__)
    if (!bLockedMemory) return 0;
    if (mlockall(MCL_CURRENT | MCL_FUTURE) < 0) {
        std::cerr << "Thread: WARNING, can't mlockall() memory!\n"
                  << std::flush;
        return -1;
    }
#endif
    return 0;
}

/**
 *  Registers thread destructor callback function which will be executed when
 *  the thread stops it's execution and sets the 'Running' flag to true. This
 *  method will be called by the __pthread_launcher callback function, DO NOT
 *  CALL THIS METHOD YOURSELF!
 */
void Thread::EnableDestructor() {
    RunningCondition.Lock();
    pthread_key_create(&__thread_destructor_key, __pthread_destructor);
    pthread_setspecific(__thread_destructor_key, this);
    RunningCondition.Set(true);
    RunningCondition.Unlock();
}

/**
 *  Will be called by the kernel when the thread stops it's execution.
 */
int Thread::Destructor() {
    pthread_key_delete(__thread_destructor_key);
    RunningCondition.Set(false);
    return 0;
}

/// Callback function for the POSIX thread API
static void* __pthread_launcher(void* thread) {
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL); // let the thread be killable under any circumstances
    Thread* t;
    t = (Thread*) thread;
    t->SetSchedulingPriority();
    t->LockMemory();
    t->EnableDestructor();
    t->Main();
    return NULL;
}

/// Callback function for the POSIX thread API
static void __pthread_destructor(void* thread) {
    Thread* t;
    t = (Thread*) thread;
    t->Destructor();
}

} // namespace LinuxSampler
