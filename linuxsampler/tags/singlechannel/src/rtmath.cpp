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

#include "rtmath.h"

float  RTMath::CentsToFreqTable[MAX_PITCH * 1200 * 2 + 1]; // +-1200 cents per octave
float* RTMath::pCentsToFreqTable(InitCentsToFreqTable());

/**
 * Will automatically be called once to initialize the 'Cents to frequency
 * ratio' table.
 */
float* RTMath::InitCentsToFreqTable() {
    float* pMiddleOfTable = &CentsToFreqTable[MAX_PITCH * 1200];
    for (int i = -1200; i <= 1200; i++) {
        pMiddleOfTable[i] = pow(TWELVEHUNDREDTH_ROOT_OF_TWO, i);
    }
    return pMiddleOfTable;
}
