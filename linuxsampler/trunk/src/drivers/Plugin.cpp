/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2008 - 2009 Andreas Persson                             *
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
 *   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,                *
 *   MA  02110-1301  USA                                                   *
 ***************************************************************************/

#include <sstream>

#include "Plugin.h"
#include "audio/AudioOutputDeviceFactory.h"
#include "midi/MidiInputDeviceFactory.h"

namespace LinuxSampler {

// *************** PluginGlobal ***************
// *

    PluginGlobal::PluginGlobal() :
        RefCount(0) {
        // we need to remove the ASIO driver, otherwise the lscp info
        // methods will lock up the audio device
        AudioOutputDeviceFactory::Unregister("ASIO");

        REGISTER_AUDIO_OUTPUT_DRIVER(AudioOutputDevicePlugin);
        REGISTER_AUDIO_OUTPUT_DRIVER_PARAMETER(AudioOutputDevicePlugin, ParameterActive);
        REGISTER_AUDIO_OUTPUT_DRIVER_PARAMETER(AudioOutputDevicePlugin, ParameterSampleRate);
        REGISTER_AUDIO_OUTPUT_DRIVER_PARAMETER(AudioOutputDevicePlugin, ParameterChannels);
        REGISTER_AUDIO_OUTPUT_DRIVER_PARAMETER(AudioOutputDevicePlugin, ParameterFragmentSize);

        REGISTER_MIDI_INPUT_DRIVER(MidiInputDevicePlugin);
        REGISTER_MIDI_INPUT_DRIVER_PARAMETER(MidiInputDevicePlugin, ParameterActive);
        REGISTER_MIDI_INPUT_DRIVER_PARAMETER(MidiInputDevicePlugin, ParameterPorts);

        pSampler = new Sampler;

        // using LOOPBACK instead of ANY to prevent windows firewall
        // warnings
        pLSCPServer = new LSCPServer(pSampler, htonl(INADDR_LOOPBACK),
                                     htons(LSCP_PORT));
        pLSCPServer->StartThread();
        pLSCPServer->WaitUntilInitialized();

        pEventThread = new EventThread(pSampler);
        pEventThread->StartThread();
    }


    PluginGlobal::~PluginGlobal() {
        pEventThread->StopThread();
        pLSCPServer->StopThread();
        pLSCPServer->RemoveListeners();

        delete pEventThread;
        delete pSampler;
        delete pLSCPServer;
    }


// *************** EventThread ***************
// *


    EventThread::EventThread(Sampler* pSampler) :
        Thread(false, false, 0, 0),
        pSampler(pSampler) {
    }

    int EventThread::Main() {
        for (;;) {
            sleep(1);
            pSampler->fireStatistics();
        }
        return 0;
    }


// *************** Plugin ***************
// *

    PluginGlobal* Plugin::global = 0;

    Plugin::Plugin(bool bDoPreInit) :
        pAudioDevice(0),
        pMidiDevice(0) {
        bPreInitDone = false;
        if (bDoPreInit) PreInit();
    }

    void Plugin::PreInit() {
        if (bPreInitDone) return;

        bPreInitDone = true;
        if (!global) {
            global = new PluginGlobal;
        }
        global->RefCount++;
    }

    void Plugin::Init(int SampleRate, int FragmentSize, int Channels) {
        if (pAudioDevice && SampleRate == pAudioDevice->SampleRate() &&
            FragmentSize == pAudioDevice->MaxSamplesPerCycle()) {
            return; // nothing has changed
        }

        String oldState;
        if (pAudioDevice) {
            oldState = GetState();
            RemoveChannels();
            global->pSampler->DestroyAudioOutputDevice(pAudioDevice);
        }
        std::map<String, String> params;
        params["SAMPLERATE"] = ToString(SampleRate);
        params["FRAGMENTSIZE"] = ToString(FragmentSize);
        if (Channels > 0) params["CHANNELS"] = ToString(Channels);
        pAudioDevice = dynamic_cast<AudioOutputDevicePlugin*>(
            global->pSampler->CreateAudioOutputDevice(AudioOutputDevicePlugin::Name(), params));

        if (!pMidiDevice) {
            pMidiDevice = dynamic_cast<MidiInputDevicePlugin*>(
                global->pSampler->CreateMidiInputDevice(MidiInputDevicePlugin::Name(),
                                                        std::map<String,String>()));
        }

        if (!oldState.empty()) {
            SetState(oldState);
        }
    }

    Plugin::~Plugin() {
        RemoveChannels();
        if (pAudioDevice) global->pSampler->DestroyAudioOutputDevice(pAudioDevice);
        if (pMidiDevice) global->pSampler->DestroyMidiInputDevice(pMidiDevice);
        if (bPreInitDone) {
            if (--global->RefCount == 0) {
                delete global;
                global = 0;
            }
        }
    }

    void Plugin::InitState() {
        SamplerChannel* channel = global->pSampler->AddSamplerChannel();
        channel->SetEngineType("gig");
        channel->SetAudioOutputDevice(pAudioDevice);
        channel->SetMidiInputDevice(pMidiDevice);
        channel->SetMidiInputChannel(midi_chan_1);
    }


    String Plugin::GetState() {
        std::stringstream s;

        s << GLOBAL_VOLUME << '\n';
        std::map<uint, SamplerChannel*> channels = global->pSampler->GetSamplerChannels();
        for (std::map<uint, SamplerChannel*>::iterator iter = channels.begin() ;
             iter != channels.end() ; iter++) {
            SamplerChannel* channel = iter->second;
            if (channel->GetAudioOutputDevice() == pAudioDevice) {
                EngineChannel* engine_channel = channel->GetEngineChannel();
                String filename = engine_channel->InstrumentFileName();
                s << channel->GetMidiInputChannel() << ' ' <<
                    engine_channel->Volume() << ' ' <<
                    filename << '\n' <<
                    engine_channel->InstrumentIndex() << ' ' <<
                    engine_channel->GetSolo() << ' ' <<
                    (engine_channel->GetMute() == 1) << '\n';
            }
        }
        return s.str();
    }

    void Plugin::RemoveChannels() {
        if(global == NULL) return;

        std::map<uint, SamplerChannel*> channels = global->pSampler->GetSamplerChannels();

        for (std::map<uint, SamplerChannel*>::iterator iter = channels.begin() ;
             iter != channels.end() ; iter++) {
            if (iter->second->GetAudioOutputDevice() == pAudioDevice) {
                global->pSampler->RemoveSamplerChannel(iter->second);
            }
        }
    }

    bool Plugin::SetState(String State) {
        RemoveChannels();

        std::stringstream s(State);
        s >> GLOBAL_VOLUME;

        int midiChannel;
        float volume;
        while (s >> midiChannel >> volume) {
            s.ignore();
            String filename;
            std::getline(s, filename);
            int index;
            bool solo;
            bool mute;
            s >> index >> solo >> mute;

            SamplerChannel* channel = global->pSampler->AddSamplerChannel();
            channel->SetEngineType("gig");
            channel->SetAudioOutputDevice(pAudioDevice);
            channel->SetMidiInputDevice(pMidiDevice);
            channel->SetMidiInputChannel(midi_chan_t(midiChannel));

            EngineChannel* engine_channel = channel->GetEngineChannel();
            engine_channel->Volume(volume);
            if (!filename.empty() && index != -1) {
                InstrumentManager::instrument_id_t id;
                id.FileName = filename;
                id.Index    = index;
                InstrumentManager::LoadInstrumentInBackground(id, engine_channel);
            }
            if (solo) engine_channel->SetSolo(solo);
            if (mute) engine_channel->SetMute(1);
        }

        return true;
    }
}
