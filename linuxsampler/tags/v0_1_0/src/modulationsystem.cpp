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
uint    ModulationSystem::uiSampleRate;
uint    ModulationSystem::uiMaxSamplesPerCycle;
ModulationSystem::__FragmentTime__ ModulationSystem::FragmentTime;

void ModulationSystem::Initialize(uint SampleRate, uint MaxSamplesPerCycle) {
    ModulationSystem::uiMaxSamplesPerCycle = MaxSamplesPerCycle;
    ModulationSystem::uiSampleRate         = SampleRate;
    if (!pDestinationParameter) {
        pDestinationParameter    = new float*[destination_count];
        pDestinationParameter[0] = new float[destination_count * MaxSamplesPerCycle];
        for (int i = 1; i < destination_count; i++) {
            pDestinationParameter[i] = pDestinationParameter[i - 1] + MaxSamplesPerCycle;
        }
    }
    ModulationSystem::FragmentTime.end = ModulationSystem::CreateTimeStamp();
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
    for (int i = 0; i < uiMaxSamplesPerCycle; i++) pDestinationParameter[dst][i] = val;
}

/**
 * Updates the time stamps for the beginning and end of the current audio
 * fragment. This is needed to be able to calculate the respective sample
 * point later for which an event belongs to.
 */
void ModulationSystem::UpdateFragmentTime() {
    // update time stamp for this audio fragment cycle
    ModulationSystem::FragmentTime.begin = ModulationSystem::FragmentTime.end;
    ModulationSystem::FragmentTime.end   = ModulationSystem::CreateTimeStamp();

    // recalculate sample ratio for this audio fragment
    real_time_t fragmentDuration = ModulationSystem::FragmentTime.end - ModulationSystem::FragmentTime.begin;
    ModulationSystem::FragmentTime.sample_ratio = (float) ModulationSystem::uiMaxSamplesPerCycle / (float) fragmentDuration;
}

/**
 * Creates a real time stamp for the current moment. Out of efficiency this
 * is implemented in inline assembly for each CPU independently; we currently
 * don't use a generic solution for CPUs that are not yet covered by the
 * assembly code, instead an error message is prompted on compile time, forcing
 * the user to contact us.
 */
ModulationSystem::real_time_t ModulationSystem::CreateTimeStamp() {
    #if defined(__i386__) || defined(__x86_64__)
        uint64_t t;
        __asm__ __volatile__ ("rdtsc" : "=A" (t));
        return t >> 8;
    #elif defined(__ia64__)
        real_time_t t;
        __asm__ __volatile__ ("mov %0=ar.itc" : "=r"(t));
        return t;
    #elif defined(__powerpc__)
        real_time_t t;
        __asm__ __volatile__ (
            "98:	mftb %0\n"
            "99:\n"
            ".section __ftr_fixup,\"a\"\n"
            "	.long %1\n"
            "	.long 0\n"
            "	.long 98b\n"
            "	.long 99b\n"
            ".previous"
            : "=r" (t) : "i" (0x00000100)
        );
        return t;
    #elif defined(__alpha__)
        real_time_t t;
        __asm__ __volatile__ ("rpcc %0" : "=r"(t));
        return t;
    #else // we don't want to use a slow generic solution
    #  error Sorry, LinuxSampler lacks time stamp code for your system.
    #  error Please report this error and the CPU you are using to the LinuxSampler developers mailing list!
    #endif
}
