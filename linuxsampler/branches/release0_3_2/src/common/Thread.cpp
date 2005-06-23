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

#include "Thread.h"

Thread::Thread(bool LockMemory, bool RealTime, int PriorityMax, int PriorityDelta) {
    this->bLockedMemory     = LockMemory;
    this->isRealTime        = RealTime;
    this->Running           = false;
    this->PriorityDelta     = PriorityDelta;
    this->PriorityMax       = PriorityMax;
    __thread_destructor_key = 0;
    pthread_mutex_init(&__thread_state_mutex, NULL);
    pthread_cond_init(&__thread_start_condition, NULL);
    pthread_cond_init(&__thread_exit_condition, NULL);
}

Thread::~Thread() {
    StopThread();
    pthread_cond_destroy(&__thread_start_condition);
    pthread_cond_destroy(&__thread_exit_condition);
    pthread_mutex_destroy(&__thread_state_mutex);
}

/**
 *  Starts the thread. This method will wait until the thread actually
 *  started it's execution before it will return. The abstract method
 *  Main() is the entry point for the new thread. You have to implement the
 *  Main() method in your subclass.
 */
int Thread::StartThread() {
    pthread_mutex_lock(&__thread_state_mutex);
    if (!Running) {
        SignalStartThread();
        pthread_cond_wait(&__thread_start_condition, &__thread_state_mutex);
    }
    pthread_mutex_unlock(&__thread_state_mutex);
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
    // Create and run the thread
    int res = pthread_create(&this->__thread_id, NULL, __pthread_launcher, this);
    switch (res) {
        case 0: // Success
            break;
        case EAGAIN:
            std::cerr << "Thread creation failed: System doesn't allow to create another thread."
                      << std::endl << std::flush;
            this->Running = false;
            break;
        case EPERM:
            std::cerr << "Thread creation failed: You're lacking permisssions to set required scheduling policy and parameters."
                      << std::endl << std::flush;
            this->Running = false;
            break;
        default:
            std::cerr << "Thread creation failed: Unknown cause."
                      << std::endl << std::flush;
            this->Running = false;
            break;
    }
    return res;
}

/**
 *  Stops the thread. This method will wait until the thread actually stopped
 *  it's execution before it will return.
 */
int Thread::StopThread() {
    pthread_mutex_lock(&__thread_state_mutex);
    if (Running) {
        SignalStopThread();
        pthread_cond_wait(&__thread_exit_condition, &__thread_state_mutex);
        pthread_detach(__thread_id);
    }
    pthread_mutex_unlock(&__thread_state_mutex);
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
    pthread_cancel(__thread_id);
    return 0;
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
    struct sched_param schp;

    if (!isRealTime) return 0;

    /*
     * set the process to realtime privs
     */
    memset(&schp, 0, sizeof(schp));
    if (this->PriorityMax == 1) {
        schp.sched_priority = sched_get_priority_max(SCHED_FIFO) + this->PriorityDelta;
    }
    if (this->PriorityMax == -1) {
        schp.sched_priority = sched_get_priority_min(SCHED_FIFO) + this->PriorityDelta;
    }

    if (sched_setscheduler(0, SCHED_FIFO, &schp) != 0) {
        perror("Thread: WARNING, can't assign realtime scheduling to thread!");
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
        perror("Thread: WARNING, can't mlockall() memory!");
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
    pthread_mutex_lock(&__thread_state_mutex);
    pthread_key_create(&__thread_destructor_key, __pthread_destructor);
    pthread_setspecific(__thread_destructor_key, this);
    Running = true;
    pthread_mutex_unlock(&__thread_state_mutex);
    pthread_cond_broadcast(&__thread_start_condition);
}

/**
 *  Will be called by the kernel when the thread stops it's execution.
 */
int Thread::Destructor() {
    pthread_key_delete(__thread_destructor_key);
    pthread_mutex_lock(&__thread_state_mutex);
    Running = false;
    pthread_mutex_unlock(&__thread_state_mutex);
    pthread_cond_broadcast(&__thread_exit_condition);
    return 0;
}

/// Callback function for the POSIX thread API
void* __pthread_launcher(void* thread) {
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
void __pthread_destructor(void* thread) {
    Thread* t;
    t = (Thread*) thread;
    t->Destructor();
}
