/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003 by Benno Senoner and Christian Schoenebeck         *
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
    Lock();
    int res = 0;
    if (this->bCondition == bCondition) {
        if (bCondition) {
            if (TimeoutSeconds || TimeoutNanoSeconds) {
                timespec timeout;
                timeout.tv_sec  = TimeoutSeconds;
                timeout.tv_nsec = TimeoutNanoSeconds;
                res = pthread_cond_timedwait(&__posix_false_condition, &__posix_mutex, &timeout);
            }
            else pthread_cond_wait(&__posix_false_condition, &__posix_mutex);
        }
        else {
            if (TimeoutSeconds || TimeoutNanoSeconds) {
                timespec timeout;
                timeout.tv_sec  = TimeoutSeconds;
                timeout.tv_nsec = TimeoutNanoSeconds;
                res = pthread_cond_timedwait(&__posix_true_condition, &__posix_mutex, &timeout);
            }
            else pthread_cond_wait(&__posix_true_condition, &__posix_mutex);
        }
    }
    return res;
}

int Condition::WaitAndUnlockIf(bool bCondition, long TimeoutSeconds, long TimeoutNanoSeconds) {
    int res = WaitIf(bCondition, TimeoutSeconds, TimeoutNanoSeconds);
    Unlock();
    return res;
}

void Condition::Set(bool bCondition) {
    Lock();
    if (this->bCondition != bCondition) {
        this->bCondition = bCondition;
        if (bCondition) pthread_cond_broadcast(&__posix_true_condition);
        else            pthread_cond_broadcast(&__posix_false_condition);
    }
    else Unlock();
}
