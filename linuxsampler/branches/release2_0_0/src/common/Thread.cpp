/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
 *   Copyright (C) 2005 - 2011 Christian Schoenebeck                       *
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

#if HAVE_CONFIG_H
# include <config.h>
#endif

// this is the minimum stack size a thread will be spawned with
// if this value is too small, the OS will allocate memory on demand and
// thus might lead to dropouts in realtime threads
// TODO: should be up for testing to get a reasonable good value
#define MIN_STACK_SIZE		524288

namespace LinuxSampler {

#if defined(WIN32)
// Callback functions for the WIN32 thread API
DWORD WINAPI __win32thread_launcher(LPVOID lpParameter);
#else
// Callback functions for the POSIX thread API
static void* __pthread_launcher(void* thread);
static void  __pthread_destructor(void* thread);
#endif

Thread::Thread(bool LockMemory, bool RealTime, int PriorityMax, int PriorityDelta) {
    this->bLockedMemory     = LockMemory;
    this->isRealTime        = RealTime;
    this->PriorityDelta     = PriorityDelta;
    this->PriorityMax       = PriorityMax;
#if defined(WIN32)
#if defined(WIN32_SIGNALSTARTTHREAD_WORKAROUND)
    win32isRunning = false;
#endif
#else
    __thread_destructor_key = 0;
    pthread_attr_init(&__thread_attr);
#endif
}

Thread::~Thread() {
    StopThread();
#if defined(WIN32)
#else
    pthread_attr_destroy(&__thread_attr);
#endif
}

/**
 *  Starts the thread. This method will wait until the thread actually
 *  started it's execution before it will return. The abstract method
 *  Main() is the entry point for the new thread. You have to implement the
 *  Main() method in your subclass.
 */
int Thread::StartThread() {
#if defined (WIN32_SIGNALSTARTTHREAD_WORKAROUND)
    // poll the win32isRunning variable and sleep 1msec inbetween
    if(!win32isRunning) {
        SignalStartThread();
        while(1) {
            Sleep(1);
            if(win32isRunning) break;
        }
    }
    return 0;
#else
    RunningCondition.Lock();
    if (!RunningCondition.GetUnsafe()) {
        SignalStartThread();
        // wait until thread started execution
        RunningCondition.WaitIf(false);
    }
    RunningCondition.Unlock();
    return 0;
#endif
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
#if defined(WIN32)
    LPVOID lpParameter;
    hThread = CreateThread(
               NULL, // no security attributes
               MIN_STACK_SIZE,
               __win32thread_launcher,
               this,
               0,
               &lpThreadId);
    if(hThread == NULL) {
        std::cerr << "Thread creation failed: Error" << GetLastError() << std::endl << std::flush;
        #if defined(WIN32_SIGNALSTARTTHREAD_WORKAROUND)
        win32isRunning = false;
        #else
        RunningCondition.Set(false);
        #endif
        return -1;
    }
    return 0;
#else
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
#endif
}

/**
 *  Stops the thread. This method will wait until the thread actually stopped
 *  it's execution before it will return.
 */
int Thread::StopThread() {
#if defined(WIN32_SIGNALSTARTTHREAD_WORKAROUND)
    SignalStopThread();
    win32isRunning = false;
    return 0;
#endif
    RunningCondition.Lock();
    if (RunningCondition.GetUnsafe()) {
        SignalStopThread();
        // wait until thread stopped execution
        RunningCondition.WaitIf(true);
        #if defined(WIN32)
        #else		
        pthread_detach(__thread_id);
        #endif		
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
#if defined(WIN32)
    BOOL res;
    res = TerminateThread(hThread, 0); // we set ExitCode to 0
    //res = WaitForSingleObject( hThread, INFINITE);
    //myprint(("Thread::SignalStopThread:  WaitForSingleObject( hThread, INFINITE) res=%d\n",res));
    #if defined(WIN32_SIGNALSTARTTHREAD_WORKAROUND)
    win32isRunning = false;
    #else
    RunningCondition.Set(false);
    #endif
#else
    pthread_cancel(__thread_id);
#endif	
    return 0;
}

/**
 * Returns @c true in case the thread is currently running.
 */
bool Thread::IsRunning() {
    #if defined(WIN32_SIGNALSTARTTHREAD_WORKAROUND)
    return win32isRunning;
    #else
    return RunningCondition.GetUnsafe();
    #endif
}

/**
 *  Sets the process SCHED_FIFO policy,  if max=1 then set at max priority,
 *  else use min priority. delta is added to the priority so that we can
 *  for example set 3 SCHED_FIFO tasks to different priorities by specifying
 *  delta  0 , -1 , -2  ( 0 = highest priority because -1 is subtracted to the
 *  current priority).
 */
int Thread::SetSchedulingPriority() {
#if defined(WIN32)
    DWORD dwPriorityClass;
    int nPriority;

    if(isRealTime) {
        dwPriorityClass = REALTIME_PRIORITY_CLASS;
        if (this->PriorityMax == 1) {
            if(this->PriorityDelta == 0) nPriority = THREAD_PRIORITY_TIME_CRITICAL;
            else nPriority = 7 + this->PriorityDelta;
        }
        else nPriority = THREAD_PRIORITY_NORMAL + this->PriorityDelta;
    }
    else {
        dwPriorityClass = NORMAL_PRIORITY_CLASS;
        nPriority = THREAD_PRIORITY_NORMAL + this->PriorityDelta;
    }

    BOOL res;
    // FIXME: priority class (realtime) does not work yet, gives error. check why.
    #if 0
    res = SetPriorityClass( hThread, dwPriorityClass );
    if(res == false) {
        std::cerr << "Thread: WARNING, setPriorityClass " << dwPriorityClass << "failed. Error " << GetLastError() << "\n";
        return -1;
    }

    res = SetThreadPriority( hThread, nPriority );
    if(res == false) {
        std::cerr << "Thread: WARNING, setThreadPriority " << nPriority << "failed. Error " << GetLastError() << "\n";
        return -1;
    }
    #endif
    return 0;
#else
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
#endif	
}

/**
 * Locks the memory so it will not be swapped out by the operating system.
 */
int Thread::LockMemory() {
#if defined(WIN32)
    return 0;
#else
#if !defined(__APPLE__)
    if (!bLockedMemory) return 0;
    if (mlockall(MCL_CURRENT | MCL_FUTURE) < 0) {
        std::cerr << "Thread: WARNING, can't mlockall() memory!\n"
                  << std::flush;
        return -1;
    }
#endif
    return 0;
#endif	
}

/**
 *  Registers thread destructor callback function which will be executed when
 *  the thread stops it's execution and sets the 'Running' flag to true. This
 *  method will be called by the __pthread_launcher callback function, DO NOT
 *  CALL THIS METHOD YOURSELF!
 */
void Thread::EnableDestructor() {
#if defined(WIN32_SIGNALSTARTTHREAD_WORKAROUND)
    win32isRunning = true;
    return;	
#endif
    RunningCondition.Lock();
#if defined(WIN32)
#else	
    pthread_key_create(&__thread_destructor_key, __pthread_destructor);
    pthread_setspecific(__thread_destructor_key, this);
#endif	
    RunningCondition.Set(true);
    RunningCondition.Unlock();
}

/**
 *  Will be called by the kernel when the thread stops it's execution.
 */
int Thread::Destructor() {
#if defined(WIN32)
#else
    pthread_key_delete(__thread_destructor_key);
    RunningCondition.Set(false);
#endif	
    return 0;
}

void Thread::TestCancel() {
#if CONFIG_PTHREAD_TESTCANCEL
    pthread_testcancel();
#endif
}

#if defined(WIN32)
DWORD WINAPI __win32thread_launcher(LPVOID lpParameter) {
    Thread* t;
    t = (Thread*) lpParameter;
    t->SetSchedulingPriority();
    t->LockMemory();
    t->EnableDestructor();
    t->Main();
    return 0;
}
#else
/// Callback function for the POSIX thread API
static void* __pthread_launcher(void* thread) {
#if !CONFIG_PTHREAD_TESTCANCEL
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL); // let the thread be killable under any circumstances
#endif

    Thread* t;
    t = (Thread*) thread;
    t->SetSchedulingPriority();
    t->LockMemory();
    t->EnableDestructor();
    t->Main();
    return NULL;
}
#endif

#if defined(WIN32)
#else
/// Callback function for the POSIX thread API
static void __pthread_destructor(void* thread) {
    Thread* t;
    t = (Thread*) thread;
    t->Destructor();
}
#endif

} // namespace LinuxSampler
