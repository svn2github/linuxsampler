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

#include "modulationsystem.h"

float** ModulationSystem::pDestinationParameter = NULL;
uint    ModulationSystem::SampleRate;
uint    ModulationSystem::FragmentSize;

void ModulationSystem::Initialize(uint SampleRate, uint FragmentSize) {
    ModulationSystem::FragmentSize = FragmentSize;
    ModulationSystem::SampleRate   = SampleRate;
    if (!pDestinationParameter) {
        pDestinationParameter    = new float*[destination_count];
        pDestinationParameter[0] = new float[destination_count * FragmentSize];
        for (int i = 1; i < destination_count; i++) {
            pDestinationParameter[i] = pDestinationParameter[i - 1] + FragmentSize;
        }
    }
}

void ModulationSystem::Close() {
    if (pDestinationParameter) {
        delete[] ModulationSystem::pDestinationParameter[0];
        delete[] ModulationSystem::pDestinationParameter;
    }
}

/**
 * Initialize the parameter sequence for the modulation destination given by
 * by 'dst' with the constant value given by val.
 */
void ModulationSystem::ResetDestinationParameter(ModulationSystem::destination_t dst, float val) {
    for (int i = 0; i < FragmentSize; i++) pDestinationParameter[dst][i] = val;
}
