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

#include "ConditionServer.h"

ConditionServer::ConditionServer() {
    bConditionQuick = false;
    bChangeRequest  = false;
    bOldCondition   = false;
}

bool* ConditionServer::Push(bool bCondition, long TimeoutSeconds, long TimeoutNanoSeconds) {
    dmsg(3,("conditionserver:Push() requesting change to %d\n", bCondition));
    PushMutex.Lock();
    bOldCondition = bConditionQuick;
    if (bConditionQuick != bCondition) {
        bChangeRequest = bCondition;
        int timeoutexceeded = SyncCondition.WaitAndUnlockIf(bOldCondition, TimeoutSeconds, TimeoutNanoSeconds); // wait until actually condition was changed on Pop() side
        if (timeoutexceeded) return NULL;
    }
    return &bOldCondition;
}

bool* ConditionServer::PushAndUnlock(bool bCondition, long TimeoutSeconds, long TimeoutNanoSeconds) {
    bool* pBefore = Push(bCondition, TimeoutSeconds, TimeoutNanoSeconds);
    Unlock();
    return pBefore;
}

void ConditionServer::Unlock() {
    PushMutex.Unlock();
}

bool ConditionServer::GetUnsafe() {
    return bConditionQuick;
}

bool ConditionServer::Pop() {
    if (bConditionQuick == bChangeRequest) return bConditionQuick;
    dmsg(3,("conditionserver:Pop() change requested\n"));
    bConditionQuick = bChangeRequest;
    SyncCondition.Set(bChangeRequest);
    dmsg(3,("conditionserver:Pop() condition now: %d\n", bConditionQuick));
    return bConditionQuick;
}
