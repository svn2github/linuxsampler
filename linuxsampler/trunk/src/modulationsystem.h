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

#ifndef __MODULATION_SYSTEM_H__
#define __MODULATION_SYSTEM_H__

#include "global.h"

/**
 * Handles modulation parameters and events for the current audio fragment.
 *
 * TODO: class should better be renamed to 'EventSystem' or even better: most of the attributes here could be moved into the engine and everything left would just be class Event (thus -> event.h and event.cpp), but that can wait until we restructe the source tree for multi engine support
 */
class ModulationSystem {
    public:
        enum destination_t {
            destination_vca,   ///< Volume level
            destination_vco,   ///< Pitch depth
            destination_count  ///< Total number of modulation sources (this has to stay the last element in the enum)
        };
        typedef uint32_t real_time_t; ///< We read the processor's cycle count register as an reference for the real time. These are of course only abstract values with arbitrary time entity, but that's not a problem as we calculate relatively.
        enum event_type_t {
            event_type_note_on,
            event_type_note_off,
            event_type_pitchbend,
            event_type_control_change,
            event_type_cancel_release,  ///< transformed either from a note-on or sustain-pedal-down event
            event_type_release          ///< transformed either from a note-off or sustain-pedal-up event
        };
        class Event {
            public:
                event_type_t Type;
                union {
                    uint8_t Key;          ///< MIDI key number for note-on and note-off events.
                    uint8_t Controller;   ///< MIDI controller number for control change events.
                };
                union {
                    uint8_t Velocity;     ///< Trigger or release velocity for note-on or note-off events.
                    uint8_t Value;        ///< Value for control change events.
                };
                int16_t Pitch;            ///< Pitch value for pitchbend events.

                Event() {
                    TimeStamp = ModulationSystem::CreateTimeStamp();
                    iFragmentPos = -1;
                }
                inline uint FragmentPos() {
                    if (iFragmentPos >= 0) return (uint) iFragmentPos;
                    return (uint) (iFragmentPos = ModulationSystem::ToFragmentPos(TimeStamp));
                }
            private:
                real_time_t TimeStamp;    ///< Time stamp of the event's occurence.
                int         iFragmentPos; ///< Position in the current fragment this event refers to.
        };

        static float** pDestinationParameter;

        static        void  Initialize(uint SampleRate, uint MaxSamplesPerCycle);
        static        void  Close();
        static        void  ResetDestinationParameter(ModulationSystem::destination_t dst, float val);
        static        void  UpdateFragmentTime();
        static real_time_t  CreateTimeStamp();
        static inline uint  MaxSamplesPerCycle()                  { return uiMaxSamplesPerCycle; }
        static inline uint  SampleRate()                          { return uiSampleRate;         }
        static inline uint  ToFragmentPos(real_time_t time_stamp) {
            return uint ((time_stamp - FragmentTime.begin) * FragmentTime.sample_ratio);
        }
    protected:
        static uint uiMaxSamplesPerCycle;
        static uint uiSampleRate;
        static struct __FragmentTime__ {
            real_time_t begin;         ///< Real time stamp of the beginning of this audio fragment cycle.
            real_time_t end;           ///< Real time stamp of the end of this audio fragment cycle.
            float       sample_ratio;  ///< (Samples per cycle) / (Real time duration of cycle)
        } FragmentTime;
};

#endif // __MODULATION_SYSTEM_H__
