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
        FragmentTime.end   = RTMath::CreateTimeStamp();
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
        FragmentTime.end   = RTMath::CreateTimeStamp();
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
        return Event(this, RTMath::CreateTimeStamp());
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
