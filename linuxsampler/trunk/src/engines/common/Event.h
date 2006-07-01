/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
 *   Copyright (C) 2005, 2006 Christian Schoenebeck                        *
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

#ifndef __LS_EVENT_H__
#define __LS_EVENT_H__

#include "../../common/global.h"
#include "../../common/RTMath.h"
#include "../EngineChannel.h"

namespace LinuxSampler {

    // just symbol prototyping
    class Event;

    /**
     * Generates Event objects and is responsible for resolving the position
     * in the current audio fragment each Event actually belongs to.
     */
    class EventGenerator {
        public:
            EventGenerator(uint SampleRate);
            void UpdateFragmentTime(uint SamplesToProcess);
            Event CreateEvent();
        protected:
            typedef RTMath::time_stamp_t time_stamp_t;
            inline int32_t ToFragmentPos(time_stamp_t TimeStamp) {
                return int32_t (int32_t(TimeStamp - FragmentTime.begin) * FragmentTime.sample_ratio);
            }
            friend class Event;
        private:
            uint uiSampleRate;
            uint uiSamplesProcessed;
            struct __FragmentTime__ {
                time_stamp_t begin;        ///< Real time stamp of the beginning of this audio fragment cycle.
                time_stamp_t end;          ///< Real time stamp of the end of this audio fragment cycle.
                float        sample_ratio; ///< (Samples per cycle) / (Real time duration of cycle)
            } FragmentTime;
    };

    /**
     * Events are usually caused by a MIDI source or an internal modulation
     * controller like LFO or EG. An event can only be created by an
     * EventGenerator.
     *
     * @see EventGenerator
     */
    class Event {
        public:
            Event(){}
            enum type_t {
                type_note_on,
                type_note_off,
                type_pitchbend,
                type_control_change,
                type_sysex,           ///< MIDI system exclusive message
                type_cancel_release,  ///< transformed either from a note-on or sustain-pedal-down event
                type_release          ///< transformed either from a note-off or sustain-pedal-up event
            } Type;
            union {
                /// Note-on and note-off event specifics
                struct _Note {
                    uint8_t Key;         ///< MIDI key number of note-on / note-off event.
                    uint8_t Velocity;    ///< Trigger or release velocity of note-on / note-off event.
                    int8_t  Layer;       ///< Layer index (usually only used if a note-on event has to be postponed, e.g. due to shortage of free voices).
                    int8_t  ReleaseTrigger; ///< If new voice should be a release triggered voice (actually boolean field and usually only used if a note-on event has to be postponed, e.g. due to shortage of free voices).
                } Note;
                /// Control change event specifics
                struct _CC {
                    uint8_t Controller;  ///< MIDI controller number of control change event.
                    uint8_t Value;       ///< Controller Value of control change event.
                } CC;
                /// Pitchbend event specifics
                struct _Pitch {
                    int16_t Pitch;       ///< Pitch value of pitchbend event.
                } Pitch;
                /// MIDI system exclusive event specifics
                struct _Sysex {
                    uint Size;           ///< Data length (in bytes) of MIDI system exclusive message.
                } Sysex;
            } Param;
            EngineChannel* pEngineChannel; ///< Pointer to the EngineChannel where this event occured on, NULL means Engine global event (e.g. SysEx message).

            inline int32_t FragmentPos() {
                if (iFragmentPos >= 0) return iFragmentPos;
                iFragmentPos = pEventGenerator->ToFragmentPos(TimeStamp);
                if (iFragmentPos < 0) iFragmentPos = 0; // if event arrived shortly before the beginning of current fragment
                return iFragmentPos;
            }
            inline void ResetFragmentPos() {
                iFragmentPos = -1;
            }
        protected:
            typedef EventGenerator::time_stamp_t time_stamp_t;
            Event(EventGenerator* pGenerator, EventGenerator::time_stamp_t Time);
            friend class EventGenerator;
        private:
            EventGenerator* pEventGenerator; ///< Creator of the event.
            time_stamp_t    TimeStamp;       ///< Time stamp of the event's occurence.
            int32_t         iFragmentPos;    ///< Position in the current fragment this event refers to.
    };

} // namespace LinuxSampler

#endif // __LS_EVENT_H__
