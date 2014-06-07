/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
 *   Copyright (C) 2005 - 2014 Christian Schoenebeck                       *
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
            Event CreateEvent(int32_t FragmentPos);
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
     * controller like LFO or EG. An event should only be created by an
     * EventGenerator!
     *
     * @see EventGenerator, ScriptEvent
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
                type_release,         ///< transformed either from a note-off or sustain-pedal-up event
                type_channel_pressure, ///< a.k.a. aftertouch
                type_note_pressure, ///< polyphonic key pressure (aftertouch)
            } Type;
            union {
                /// Note-on and note-off event specifics
                struct _Note {
                    uint8_t Channel;     ///< MIDI channel (0..15)
                    uint8_t Key;         ///< MIDI key number of note-on / note-off event.
                    uint8_t Velocity;    ///< Trigger or release velocity of note-on / note-off event.
                    int8_t  Layer;       ///< Layer index (usually only used if a note-on event has to be postponed, e.g. due to shortage of free voices).
                    int8_t  ReleaseTrigger; ///< If new voice should be a release triggered voice (actually boolean field and usually only used if a note-on event has to be postponed, e.g. due to shortage of free voices).
                    void*   pRegion;     ///< Engine specific pointer to instrument region
                } Note;
                /// Control change event specifics
                struct _CC {
                    uint8_t Channel;     ///< MIDI channel (0..15)
                    uint8_t Controller;  ///< MIDI controller number of control change event.
                    uint8_t Value;       ///< Controller Value of control change event.
                } CC;
                /// Pitchbend event specifics
                struct _Pitch {
                    uint8_t Channel;     ///< MIDI channel (0..15)
                    int16_t Pitch;       ///< Pitch value of pitchbend event.
                } Pitch;
                /// MIDI system exclusive event specifics
                struct _Sysex {
                    uint Size;           ///< Data length (in bytes) of MIDI system exclusive message.
                } Sysex;
                /// Channel Pressure (aftertouch) event specifics
                struct _ChannelPressure {
                    uint8_t Channel; ///< MIDI channel (0..15)
                    uint8_t Value;   ///< New aftertouch / pressure value for keys on that channel.
                } ChannelPressure;
                /// Polyphonic Note Pressure (aftertouch) event specifics
                struct _NotePressure {
                    uint8_t Channel; ///< MIDI channel (0..15)
                    uint8_t Key;     ///< MIDI note number where key pressure (polyphonic aftertouch) changed.
                    uint8_t Value;   ///< New pressure value for note.
                } NotePressure;
            } Param;
            /// Sampler format specific informations and variables.
            union {
                /// Gigasampler/GigaStudio format specifics.
                struct _Gig {
                    uint8_t DimMask; ///< May be used to override the Dimension zone to be selected for a new voice: each 1 bit means that respective bit shall be overridden by taking the respective bit from DimBits instead.
                    uint8_t DimBits; ///< Used only in conjunction with DimMask: Dimension bits that shall be selected.
                } Gig;
            } Format;
            EngineChannel* pEngineChannel; ///< Pointer to the EngineChannel where this event occured on, NULL means Engine global event (e.g. SysEx message).
            MidiInputPort* pMidiInputPort; ///< Pointer to the MIDI input port on which this event occured (NOTE: currently only for global events, that is SysEx messages)

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
            Event(EventGenerator* pGenerator, int32_t FragmentPos);
            friend class EventGenerator;
        private:
            EventGenerator* pEventGenerator; ///< Creator of the event.
            time_stamp_t    TimeStamp;       ///< Time stamp of the event's occurence.
            int32_t         iFragmentPos;    ///< Position in the current fragment this event refers to.
    };

    class VMEventHandler;
    class VMExecContext;

    /** @brief Real-time instrument script event.
     *
     * Encapsulates one execution instance of a real-time instrument script for
     * exactly one script event handler (script event callback).
     */
    class ScriptEvent {
    public:
        Event cause; ///< Original external event that triggered this script event (i.e. MIDI note on event, MIDI CC event, etc.).
        int id; ///< Unique ID of the external event that triggered this cript event.
        VMEventHandler** handlers; ///< The script's event handlers (callbacks) to be processed (NULL terminated list).
        VMExecContext* execCtx; ///< Script's current execution state (polyphonic variables and execution stack).
        int currentHandler; ///< Current index in 'handlers' list above.
        int executionSlices; ///< Amount of times this script event has been executed by the ScriptVM runner class.
    };

} // namespace LinuxSampler

#endif // __LS_EVENT_H__
