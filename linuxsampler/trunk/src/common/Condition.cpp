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

#include "Condition.h"

#include "global.h"

Condition::Condition(bool bInitialCondition) {
    pthread_cond_init(&__posix_true_condition, NULL);
    pthread_cond_init(&__posix_false_condition, NULL);
    bCondition = bInitialCondition;
}

Condition::~Condition() {
    pthread_cond_destroy(&__posix_true_condition);
    pthread_cond_destroy(&__posix_false_condition);
}

int Condition::WaitIf(bool bCondition, long TimeoutSeconds, long TimeoutNanoSeconds) {
    dmsg(7,("Condition::Waitif() -> LOCK()\n"));
    Lock();
    dmsg(7,("Condition::Waitif() -> LOCK() passed\n"));
    int res = 0;
    if (this->bCondition == bCondition) {
        if (bCondition) { // wait until condition turned 'false'
            if (TimeoutSeconds || TimeoutNanoSeconds) { // wait with timeout
                timespec timeout;
                timeout.tv_sec  = TimeoutSeconds;
                timeout.tv_nsec = TimeoutNanoSeconds;
                dmsg(7,("Condition::Waitif() -> waiting for 'false' condition with timeout\n"));
                res = pthread_cond_timedwait(&__posix_false_condition, &__posix_mutex, &timeout);
                dmsg(7,("Condition::Waitif() -> awakened from 'false' condition waiting\n"));
            }
            else { // wait without timeout
                dmsg(7,("Condition::Waitif() -> waiting for 'false' condition\n"));
                pthread_cond_wait(&__posix_false_condition, &__posix_mutex);
                dmsg(7,("Condition::Waitif() -> awakened from 'false' condition waiting\n"));
            }
        }
        else { // wait until condition turned 'true'
            if (TimeoutSeconds || TimeoutNanoSeconds) { // wait with timeout
                timespec timeout;
                timeout.tv_sec  = TimeoutSeconds;
                timeout.tv_nsec = TimeoutNanoSeconds;
                dmsg(7,("Condition::Waitif() -> waiting for 'true' condition with timeout\n"));
                res = pthread_cond_timedwait(&__posix_true_condition, &__posix_mutex, &timeout);
                dmsg(7,("Condition::Waitif() -> awakened from 'true' condition waiting\n"));
            }
            else { // wait without timeout
                dmsg(7,("Condition::Waitif() -> waiting for 'true' condition\n"));
                pthread_cond_wait(&__posix_true_condition, &__posix_mutex);
                dmsg(7,("Condition::Waitif() -> awakened from 'true' condition waiting\n"));
            }
        }
    }
    return res;
}

int Condition::WaitAndUnlockIf(bool bCondition, long TimeoutSeconds, long TimeoutNanoSeconds) {
    int res = WaitIf(bCondition, TimeoutSeconds, TimeoutNanoSeconds);
    dmsg(7,("Condition::WaitAndUnlockIf() -> UNLOCK()\n"));
    Unlock();
    dmsg(7,("Condition::WaitAndUnlockIf() -> UNLOCK() passed\n"));
    return res;
}

void Condition::Set(bool bCondition) {
    dmsg(7,("Condition::Set() -> LOCK()\n"));
    Lock();
    dmsg(7,("Condition::Set() -> LOCK() passed\n"));
    if (this->bCondition != bCondition) {
        this->bCondition = bCondition;
        if (bCondition) {
            dmsg(7,("Condition::Set() -> broadcasting 'true' condition\n"));
            pthread_cond_broadcast(&__posix_true_condition);
        }
        else {
            dmsg(7,("Condition::Set() -> broadcasting 'false' condition\n"));
            pthread_cond_broadcast(&__posix_false_condition);
        }
    }
    Unlock();
}
