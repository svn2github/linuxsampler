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

#include "Event.h"

namespace LinuxSampler {

    /**
     * Create an EventGenerator.
     *
     * @param SampleRate - sample rate of the sampler engine's audio output
     *                     signal (in Hz)
     */
    EventGenerator::EventGenerator(uint SampleRate) {
        uiSampleRate       = SampleRate;
        uiSamplesProcessed = 0;
        FragmentTime.end   = CreateTimeStamp();
    }

    /**
     * Updates the time stamps for the beginning and end of the current audio
     * fragment. This is needed to be able to calculate the respective sample
     * point later to which an event belongs to.
     *
     * @param SamplesToProcess - number of sample points to process in this
     *                           audio fragment cycle
     */
    void EventGenerator::UpdateFragmentTime(uint SamplesToProcess) {
        // update time stamp for this audio fragment cycle
        FragmentTime.begin = FragmentTime.end;
        FragmentTime.end   = CreateTimeStamp();
        // recalculate sample ratio for this audio fragment
        time_stamp_t fragmentDuration = FragmentTime.end - FragmentTime.begin;
        FragmentTime.sample_ratio = (float) uiSamplesProcessed / (float) fragmentDuration;
        // store amount of samples to process for the next cycle
        uiSamplesProcessed = SamplesToProcess;
    }

    /**
     * Create a new event with the current time as time stamp.
     */
    Event EventGenerator::CreateEvent() {
        return Event(this, CreateTimeStamp());
    }

    /**
     * Creates a real time stamp for the current moment. Out of efficiency this
     * is implemented in inline assembly for each CPU independently; we currently
     * don't use a generic solution for CPUs that are not yet covered by the
     * assembly code, instead an error message is prompted on compile time, forcing
     * the user to contact us.
     */
    EventGenerator::time_stamp_t EventGenerator::CreateTimeStamp() {
        #if defined(__i386__) || defined(__x86_64__)
            uint64_t t;
            __asm__ __volatile__ ("rdtsc" : "=A" (t));
            return t >> 8;
        #elif defined(__ia64__)
            time_stamp_t t;
            __asm__ __volatile__ ("mov %0=ar.itc" : "=r"(t));
            return t;
        #elif defined(__powerpc__)
            time_stamp_t t;
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
            time_stamp_t t;
            __asm__ __volatile__ ("rpcc %0" : "=r"(t));
            return t;
        #else // we don't want to use a slow generic solution
        #  error Sorry, LinuxSampler lacks time stamp code for your system.
        #  error Please report this error and the CPU you are using to the LinuxSampler developers mailing list!
        #endif
    }

    /**
     * Will be called by an EventGenerator to create a new Event.
     */
    Event::Event(EventGenerator* pGenerator, time_stamp_t Time) {
        pEventGenerator = pGenerator;
        TimeStamp       = Time;
        iFragmentPos    = -1;
    }

} // namespace LinuxSampler
