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

#ifndef __LS_SAMPLER_H__
#define __LS_SAMPLER_H__

#include <vector>
#include <map>
#include "common/global.h"
#include "common/LinuxSamplerException.h"
#include "engines/common/Engine.h"
#include "mididriver/MidiInputDevice.h"
#include "audiodriver/AudioOutputDevice.h"

namespace LinuxSampler {

    /**
     * Which sampler engine to be used.
     */
    enum engine_type_t {
        engine_type_gig
    };

    /**
     * Which audio output system to be used.
     */
    enum audio_output_type_t {
        audio_output_type_alsa,
        audio_output_type_jack
    };

    /**
     * Which MIDI input system to be used.
     */
    enum midi_input_type_t {
        midi_input_type_alsa
    };

    // just symbol prototyping
    class Sampler;

    class SamplerChannel {
        public:
            SamplerChannel(Sampler* pS);
           ~SamplerChannel();
            void               LoadEngine(engine_type_t EngineType);
            void               SetAudioOutputDevice(audio_output_type_t AudioType);
            void               SetMidiInputDevice(midi_input_type_t MidiType, MidiInputDevice::midi_chan_t MidiChannel = MidiInputDevice::midi_chan_all);
            Engine*            GetEngine();
            MidiInputDevice*   GetMidiInputDevice();
            AudioOutputDevice* GetAudioOutputDevice();
            uint               Index();
        protected:
            Sampler*           pSampler;
            Engine*            pEngine;
            MidiInputDevice*   pMidiInputDevice;
            AudioOutputDevice* pAudioOutputDevice;
            int                iIndex;
    };

    class Sampler {
        public:
            Sampler();
           ~Sampler();
            uint               SamplerChannels();
            SamplerChannel*    AddSamplerChannel();
            SamplerChannel*    GetSamplerChannel(uint uiSamplerChannel);
            void               RemoveSamplerChannel(SamplerChannel* pSamplerChannel);
            void               RemoveSamplerChannel(uint uiSamplerChannel);
            AudioOutputDevice* CreateAudioOutputDevice(audio_output_type_t AudioType);
            AudioOutputDevice* GetAudioOutputDevice(audio_output_type_t AudioType);
            MidiInputDevice*   CreateMidiInputDevice(midi_input_type_t MidiType);
            MidiInputDevice*   GetMidiInputDevice(midi_input_type_t MidiType);
        protected:
            typedef std::map<audio_output_type_t, AudioOutputDevice*> AudioOutputDeviceMap;
            typedef std::map<midi_input_type_t, MidiInputDevice*> MidiInputDeviceMap;

            std::vector<SamplerChannel*> vSamplerChannels;   ///< contains all created sampler channels
            AudioOutputDeviceMap         AudioOutputDevices; ///< contains all created audio output devices
            MidiInputDeviceMap           MidiInputDevices;

            friend class SamplerChannel;
    };
}

#endif // __LS_SAMPLER_H__
