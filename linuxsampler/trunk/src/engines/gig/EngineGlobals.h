/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
 *   Copyright (C) 2005 Christian Schoenebeck                              *
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

#ifndef __LS_GIG_ENGINEGLOBALS_H__
#define __LS_GIG_ENGINEGLOBALS_H__

#if DEBUG_HEADERS
# warning EngineGlobals.h included
#endif // DEBUG_HEADERS

#define PITCHBEND_SEMITONES             12
#define MAX_AUDIO_VOICES                128
#define SYSEX_BUFFER_SIZE               2048  // 2kB
#define VOICE_STEAL_ALGORITHM           voice_steal_algo_oldestkey  ///< @see voice_steal_algo_t for available voice stealing algorithms

#define FILTER_UPDATE_PERIOD            64 ///< amount of sample points after which filter parameters (cutoff, resonance) are going to be updated (higher value means less CPU load, but also worse parameter resolution, this value will be aligned to a power of two)
#define FORCE_FILTER_USAGE              0  ///< if set to 1 then filter is always used, if set to 0 filter is used only in case the instrument file defined one
#define FILTER_CUTOFF_MAX               10000.0f ///< maximum cutoff frequency (10kHz)
#define FILTER_CUTOFF_MIN               100.0f   ///< minimum cutoff frequency (100Hz)

// Uncomment following line to override external cutoff controller
//#define OVERRIDE_FILTER_CUTOFF_CTRL   1  ///< set to an arbitrary MIDI control change controller (e.g. 1 for 'modulation wheel')

// Uncomment following line to override external resonance controller
//#define OVERRIDE_FILTER_RES_CTRL      91  ///< set to an arbitrary MIDI control change controller (e.g. 91 for 'effect 1 depth')

// Uncomment following line to override filter type
//#define OVERRIDE_FILTER_TYPE          ::gig::vcf_type_lowpass  ///< either ::gig::vcf_type_lowpass, ::gig::vcf_type_bandpass or ::gig::vcf_type_highpass

#include "Voice.h"
#include "../common/Event.h"

namespace LinuxSampler { namespace gig {

    class Voice;

    enum voice_steal_algo_t {
        voice_steal_algo_none,
        voice_steal_algo_keymask,
        voice_steal_algo_oldestkey
    };

    struct midi_key_info_t {
        RTList<Voice>*  pActiveVoices;  ///< Contains the active voices associated with the MIDI key.
        bool            KeyPressed;     ///< Is true if the respective MIDI key is currently pressed.
        bool            Active;         ///< If the key contains active voices.
        bool            ReleaseTrigger; ///< If we have to launch release triggered voice(s) when the key is released
        Pool<uint>::Iterator itSelf;    ///< hack to allow fast deallocation of the key from the list of active keys
        RTList<Event>*  pEvents;        ///< Key specific events (only Note-on, Note-off and sustain pedal currently)
    };

}} // namespace LinuxSampler::gig

#endif // __LS_GIG_ENGINEGLOBALS_H__
