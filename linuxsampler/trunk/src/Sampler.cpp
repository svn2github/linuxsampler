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

#include <sstream>

#include "Sampler.h"

#include "audiodriver/AudioOutputDeviceFactory.h"
#include "mididriver/MidiInputDeviceAlsa.h"
#include "engines/gig/Engine.h"

namespace LinuxSampler {

    // ******************************************************************
    // * SamplerChannel

    SamplerChannel::SamplerChannel(Sampler* pS) {
        pSampler           = pS;
        pEngine            = NULL;
        pMidiInputDevice   = NULL;
        pAudioOutputDevice = NULL;
        iIndex             = -1;
    }

    SamplerChannel::~SamplerChannel() {
        if (pEngine) {
            if (pMidiInputDevice) pMidiInputDevice->Disconnect(pEngine);
            if (pAudioOutputDevice) pAudioOutputDevice->Disconnect(pEngine);
            delete pEngine;
        }
    }

    void SamplerChannel::LoadEngine(Engine::type_t EngineType) {
        dmsg(2,("SamplerChannel: Loading engine..."));

        // create new engine
        Engine* pNewEngine = NULL;
        switch (EngineType) {
            case Engine::type_gig:
                pNewEngine = new gig::Engine;
                break;
            default:
                throw LinuxSamplerException("Unknown engine type");
        }

        // disconnect old engine
        if (pEngine) {
            if (pMidiInputDevice) pMidiInputDevice->Disconnect(pEngine);
            if (pAudioOutputDevice) pAudioOutputDevice->Disconnect(pEngine);
            delete pEngine;
        }

        // connect new engine
        pEngine = pNewEngine;
        if (pMidiInputDevice) pMidiInputDevice->Connect(pNewEngine, (MidiInputDevice::midi_chan_t) Index());
        if (pAudioOutputDevice) pAudioOutputDevice->Connect(pNewEngine);
        dmsg(2,("OK\n"));
    }

    void SamplerChannel::SetAudioOutputDevice(AudioOutputDevice* pDevice) {
        // disconnect old device
        if (pAudioOutputDevice && pEngine) pAudioOutputDevice->Disconnect(pEngine);

        // connect new device
        pAudioOutputDevice = pDevice;
        if (pEngine) pAudioOutputDevice->Connect(pEngine);
    }

    void SamplerChannel::SetMidiInputDevice(MidiInputDevice::type_t MidiType, MidiInputDevice::midi_chan_t MidiChannel) {
        // get / create desired midi device
        MidiInputDevice* pDevice = pSampler->GetMidiInputDevice(MidiType);
        if (!pDevice) pDevice = pSampler->CreateMidiInputDevice(MidiType);

        // disconnect old device
        if (pMidiInputDevice && pEngine) pMidiInputDevice->Disconnect(pEngine);

        // connect new device
        pMidiInputDevice = pDevice;
        if (pEngine) pMidiInputDevice->Connect(pEngine, MidiChannel);
    }

    Engine* SamplerChannel::GetEngine() {
        return pEngine;
    }

    MidiInputDevice* SamplerChannel::GetMidiInputDevice() {
        return pMidiInputDevice;
    }

    AudioOutputDevice* SamplerChannel::GetAudioOutputDevice() {
        return pAudioOutputDevice;
    }

    uint SamplerChannel::Index() {
        if (iIndex >= 0) return iIndex;

        std::vector<SamplerChannel*>::iterator iter = pSampler->vSamplerChannels.begin();
        for (int i = 0; iter != pSampler->vSamplerChannels.end(); i++, iter++) {
            if (*iter == this) {
                iIndex = i;
                return i;
            }
        }

        throw LinuxSamplerException("SamplerChannel index not found");
    }


    // ******************************************************************
    // * Sampler

    Sampler::Sampler() {
    }

    Sampler::~Sampler() {
        // delete sampler channels
        {
            std::vector<SamplerChannel*>::iterator iter = vSamplerChannels.begin();
            for (; iter != vSamplerChannels.end(); iter++) delete *iter;
        }

        // delete midi input devices
        {
            MidiInputDeviceMap::iterator iter = MidiInputDevices.begin();
            for (; iter != MidiInputDevices.end(); iter++) {
                MidiInputDevice* pDevice = iter->second;
                pDevice->StopListen();
                delete pDevice;
            }
        }

        // delete audio output devices
        {
            AudioOutputDeviceMap::iterator iter = mAudioOutputDevices.begin();
            for (; iter != mAudioOutputDevices.end(); iter++) {
                AudioOutputDevice* pDevice = iter->second;
                pDevice->Stop();
                delete pDevice;
            }
        }
    }

    uint Sampler::SamplerChannels() {
        return vSamplerChannels.size();
    }

    SamplerChannel* Sampler::AddSamplerChannel() {
        SamplerChannel* pChannel = new SamplerChannel(this);
        vSamplerChannels.push_back(pChannel);
        return pChannel;
    }

    SamplerChannel* Sampler::GetSamplerChannel(uint uiSamplerChannel) {
        if (uiSamplerChannel >= SamplerChannels()) return NULL;
        return vSamplerChannels[uiSamplerChannel];
    }

    void Sampler::RemoveSamplerChannel(SamplerChannel* pSamplerChannel) {
        std::vector<SamplerChannel*>::iterator iterChan = vSamplerChannels.begin();
        for (; iterChan != vSamplerChannels.end(); iterChan++) {
            if (*iterChan == pSamplerChannel) {
                vSamplerChannels.erase(iterChan);
                delete pSamplerChannel;
                return;
            }
        }
    }

    void Sampler::RemoveSamplerChannel(uint uiSamplerChannel) {
        SamplerChannel* pChannel = GetSamplerChannel(uiSamplerChannel);
        if (!pChannel) return;
        RemoveSamplerChannel(pChannel);
    }

    std::vector<String> Sampler::AvailableAudioOutputDrivers() {
        return AudioOutputDeviceFactory::AvailableDrivers();
    }

    AudioOutputDevice* Sampler::CreateAudioOutputDevice(String AudioDriver, std::map<String,String> Parameters) throw (LinuxSamplerException) {
        // create new device
        AudioOutputDevice* pDevice = AudioOutputDeviceFactory::Create(AudioDriver, Parameters);

        // activate device
        pDevice->Play();

        // add new audio device to the audio device list
        for (uint i = 0; ; i++) { // seek for a free place starting from the beginning
            if (!mAudioOutputDevices[i]) {
                mAudioOutputDevices[i] = pDevice;
                break;
            }
        }

        return pDevice;
    }

    uint Sampler::AudioOutputDevices() {
        return mAudioOutputDevices.size();
    }

    std::map<uint, AudioOutputDevice*> Sampler::GetAudioOutputDevices() {
        return mAudioOutputDevices;
    }

    void Sampler::DestroyAudioOutputDevice(AudioOutputDevice* pDevice) throw (LinuxSamplerException) {
        AudioOutputDeviceMap::iterator iter = mAudioOutputDevices.begin();
        for (; iter != mAudioOutputDevices.end(); iter++) {
            if (iter->second == pDevice) {
                // check if there are still sampler engines connected to this device
                for (uint i = 0; i < SamplerChannels(); i++)
                    if (GetSamplerChannel(i)->GetAudioOutputDevice() == pDevice) throw LinuxSamplerException("Sampler channel " + ToString(i) + " is still connected to the audio output device.");

                // disable device
                pDevice->Stop();

                // remove device from the device list
                mAudioOutputDevices.erase(iter);

                // destroy and free device from memory
                delete pDevice;
            }
        }
    }

    MidiInputDevice* Sampler::CreateMidiInputDevice(MidiInputDevice::type_t MidiType) {
        // check if device already created
        MidiInputDevice* pDevice = GetMidiInputDevice(MidiType);
        if (pDevice) return pDevice;

        // create new device
        switch (MidiType) {
            case MidiInputDevice::type_alsa:
                pDevice = new MidiInputDeviceAlsa;
                break;
            default:
                throw LinuxSamplerException("Unknown audio output device type");
        }

        // activate device
        pDevice->Listen();

        // add new MIDI device to the MIDI device list
        MidiInputDevices[MidiType] = pDevice;

        return pDevice;
    }

    MidiInputDevice* Sampler::GetMidiInputDevice(MidiInputDevice::type_t MidiType) {
        MidiInputDeviceMap::iterator iter = MidiInputDevices.find(MidiType);
        return (iter != MidiInputDevices.end()) ? iter->second : NULL;
    }

} // namespace LinuxSampler
