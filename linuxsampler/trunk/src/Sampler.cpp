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

#include <sstream>

#include "Sampler.h"

#include "engines/EngineChannelFactory.h"
#include "drivers/audio/AudioOutputDeviceFactory.h"
#include "drivers/midi/MidiInputDeviceFactory.h"
#include "network/lscpserver.h"

namespace LinuxSampler {

    // ******************************************************************
    // * SamplerChannel

    SamplerChannel::SamplerChannel(Sampler* pS) {
        pSampler           = pS;
        pEngineChannel     = NULL;
        pMidiInputDevice   = NULL;
        pAudioOutputDevice = NULL;
        midiPort           = 0;
        midiChannel        = MidiInputPort::midi_chan_all;
        iIndex             = -1;
    }

    SamplerChannel::~SamplerChannel() {
        if (pEngineChannel) {
            MidiInputPort* pMidiInputPort = GetMidiInputDevicePort(this->midiPort);
            if (pMidiInputPort) pMidiInputPort->Disconnect(pEngineChannel);
            if (pEngineChannel) {
                if (pAudioOutputDevice) pEngineChannel->DisconnectAudioOutputDevice();
                delete pEngineChannel;
            }
        }
    }

    void SamplerChannel::SetEngineType(String EngineType) throw (LinuxSamplerException) {
        dmsg(2,("SamplerChannel: Assigning engine type..."));

        // create new engine channel
        EngineChannel* pNewEngineChannel = EngineChannelFactory::Create(EngineType);
        if (!pNewEngineChannel) throw LinuxSamplerException("Unknown engine type");

        // dereference midi input port.
        MidiInputPort* pMidiInputPort = GetMidiInputDevicePort(this->midiPort);
        // disconnect old engine
        if (pEngineChannel) {
            if (pMidiInputPort) pMidiInputPort->Disconnect(pEngineChannel);
            if (pAudioOutputDevice) pEngineChannel->DisconnectAudioOutputDevice();
            delete pEngineChannel;
        }

        // connect new engine channel
        pEngineChannel = pNewEngineChannel;
        if (pMidiInputPort) pMidiInputPort->Connect(pNewEngineChannel, this->midiChannel);
        if (pAudioOutputDevice) {
            pNewEngineChannel->Connect(pAudioOutputDevice);
            pAudioOutputDevice->Connect(pNewEngineChannel->GetEngine());
        }
        dmsg(2,("OK\n"));
    }

    void SamplerChannel::SetAudioOutputDevice(AudioOutputDevice* pDevice) {
        // disconnect old device
        if (pAudioOutputDevice && pEngineChannel) pEngineChannel->DisconnectAudioOutputDevice();
        // connect new device
        pAudioOutputDevice = pDevice;
        if (pEngineChannel) {
            pEngineChannel->Connect(pAudioOutputDevice);
            pAudioOutputDevice->Connect(pEngineChannel->GetEngine());
        }
    }

    void SamplerChannel::SetMidiInputDevice(MidiInputDevice* pDevice) {
       SetMidiInput(pDevice, this->midiPort, this->midiChannel);
    }

    void SamplerChannel::SetMidiInputPort(int MidiPort) {
       SetMidiInput(pMidiInputDevice, MidiPort, this->midiChannel);
    }

    void SamplerChannel::SetMidiInputChannel(MidiInputPort::midi_chan_t MidiChannel) {
       SetMidiInput(pMidiInputDevice, this->midiPort, MidiChannel);
    }

    void SamplerChannel::SetMidiInput(MidiInputDevice* pDevice, int iMidiPort, MidiInputPort::midi_chan_t MidiChannel) {
        // dereference old midi input port.
        MidiInputPort* pMidiInputPort = GetMidiInputDevicePort(this->midiPort);
        // disconnect old device port
        if (pMidiInputPort && pEngineChannel) pMidiInputPort->Disconnect(pEngineChannel);
        // new device, port and channel
        pMidiInputDevice = pDevice;
        this->midiPort = iMidiPort;
        this->midiChannel = MidiChannel;
        // connect new device port
        pMidiInputPort = GetMidiInputDevicePort(this->midiPort);
        if (pMidiInputPort && pEngineChannel) pMidiInputPort->Connect(pEngineChannel, MidiChannel);
        // Ooops.
        if (pMidiInputPort == NULL)
            throw LinuxSamplerException("There is no MIDI input port with index " + ToString(iMidiPort) + ".");
    }

    EngineChannel* SamplerChannel::GetEngineChannel() {
        return pEngineChannel;
    }

    MidiInputPort::midi_chan_t SamplerChannel::GetMidiInputChannel() {
        return this->midiChannel;
    }

    int SamplerChannel::GetMidiInputPort() {
        MidiInputPort* pMidiInputPort = GetMidiInputDevicePort(this->midiPort);
        return (pMidiInputPort ? (int) pMidiInputPort->GetPortNumber() : -1);
    }

    AudioOutputDevice* SamplerChannel::GetAudioOutputDevice() {
        return pAudioOutputDevice;
    }

    MidiInputDevice* SamplerChannel::GetMidiInputDevice() {
        return pMidiInputDevice;
    }

    uint SamplerChannel::Index() {
        if (iIndex >= 0) return iIndex;

        Sampler::SamplerChannelMap::iterator iter = pSampler->mSamplerChannels.begin();
        for (; iter != pSampler->mSamplerChannels.end(); iter++) {
            if (iter->second == this) {
                iIndex = iter->first;
                return iIndex;
            }
        }

        throw LinuxSamplerException("Internal error: SamplerChannel index not found");
    }

    MidiInputPort* SamplerChannel::GetMidiInputDevicePort(int iMidiPort) {
        MidiInputPort* pMidiInputPort = NULL;
        if (pMidiInputDevice)
            pMidiInputPort = pMidiInputDevice->GetPort(iMidiPort);
        return pMidiInputPort;
    }



    // ******************************************************************
    // * Sampler

    Sampler::Sampler() {
    }

    Sampler::~Sampler() {
        Reset();
    }

    uint Sampler::SamplerChannels() {
        return mSamplerChannels.size();
    }

    SamplerChannel* Sampler::AddSamplerChannel() {
        // if there's no sampler channel yet
        if (!mSamplerChannels.size()) {
            SamplerChannel* pChannel = new SamplerChannel(this);
            mSamplerChannels[0] = pChannel;
	    LSCPServer::SendLSCPNotify(LSCPEvent(LSCPEvent::event_channels, 1));
            return pChannel;
        }

        // get the highest used sampler channel index
        uint lastIndex = (--(mSamplerChannels.end()))->first;

        // check if we reached the index limit
        if (lastIndex + 1 < lastIndex) {
            // search for an unoccupied sampler channel index starting from 0
            for (uint i = 0; i < lastIndex; i++) {
                if (mSamplerChannels.find(i) != mSamplerChannels.end()) continue;
                // we found an unused index, so insert the new channel there
                SamplerChannel* pChannel = new SamplerChannel(this);
                mSamplerChannels[i] = pChannel;
		LSCPServer::SendLSCPNotify(LSCPEvent(LSCPEvent::event_channels, i));
                return pChannel;
            }
            throw LinuxSamplerException("Internal error: could not find unoccupied sampler channel index.");
        }

        // we have not reached the index limit so we just add the channel past the highest index
        SamplerChannel* pChannel = new SamplerChannel(this);
        mSamplerChannels[lastIndex + 1] = pChannel;
	LSCPServer::SendLSCPNotify(LSCPEvent(LSCPEvent::event_channels, lastIndex + 1));
        return pChannel;
    }

    SamplerChannel* Sampler::GetSamplerChannel(uint uiSamplerChannel) {
        return (mSamplerChannels.find(uiSamplerChannel) != mSamplerChannels.end()) ? mSamplerChannels[uiSamplerChannel] : NULL;
    }

    std::map<uint, SamplerChannel*> Sampler::GetSamplerChannels() {
        return mSamplerChannels;
    }

    void Sampler::RemoveSamplerChannel(SamplerChannel* pSamplerChannel) {
        SamplerChannelMap::iterator iterChan = mSamplerChannels.begin();
        for (; iterChan != mSamplerChannels.end(); iterChan++) {
            if (iterChan->second == pSamplerChannel) {
                mSamplerChannels.erase(iterChan);
                delete pSamplerChannel;
		LSCPServer::SendLSCPNotify(LSCPEvent(LSCPEvent::event_channels, mSamplerChannels.size()));
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

    uint Sampler::MidiInputDevices() {
        return mMidiInputDevices.size();
    }

    std::map<uint, AudioOutputDevice*> Sampler::GetAudioOutputDevices() {
        return mAudioOutputDevices;
    }

    std::map<uint, MidiInputDevice*> Sampler::GetMidiInputDevices() {
        return mMidiInputDevices;
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

    void Sampler::DestroyMidiInputDevice(MidiInputDevice* pDevice) throw (LinuxSamplerException) {
        MidiInputDeviceMap::iterator iter = mMidiInputDevices.begin();
        for (; iter != mMidiInputDevices.end(); iter++) {
            if (iter->second == pDevice) {
                // check if there are still sampler engines connected to this device
                for (uint i = 0; i < SamplerChannels(); i++)
                    if (GetSamplerChannel(i)->GetMidiInputDevice() == pDevice) throw LinuxSamplerException("Sampler channel " + ToString(i) + " is still connected to the midi input device.");

                // disable device
                pDevice->StopListen();

                // remove device from the device list
                mMidiInputDevices.erase(iter);

                // destroy and free device from memory
                delete pDevice;
            }
        }
    }

    MidiInputDevice* Sampler::CreateMidiInputDevice(String MidiDriver, std::map<String,String> Parameters) throw (LinuxSamplerException) {
        // create new device
        MidiInputDevice* pDevice = MidiInputDeviceFactory::Create(MidiDriver, Parameters, this);

	// add new device to the midi device list
	for (uint i = 0; ; i++) { // seek for a free place starting from the beginning
		if (!mMidiInputDevices[i]) {
			mMidiInputDevices[i] = pDevice;
			break;
		}
	}

        return pDevice;
    }

    void Sampler::Reset() {
        // delete sampler channels
        try {
	    while (true) {
		    SamplerChannelMap::iterator iter = mSamplerChannels.begin();
		    if (iter == mSamplerChannels.end()) break;
		    RemoveSamplerChannel(iter->second);
            }
        }
        catch(...) {
            std::cerr << "Sampler::Reset(): Exception occured while trying to delete all sampler channels, exiting.\n" << std::flush;
            exit(EXIT_FAILURE);
        }

        // delete midi input devices
        try {
	    while (true) {
		    MidiInputDeviceMap::iterator iter = mMidiInputDevices.begin();
		    if (iter == mMidiInputDevices.end()) break;
		    DestroyMidiInputDevice(iter->second);
            }
        }
        catch(...) {
            std::cerr << "Sampler::Reset(): Exception occured while trying to delete all MIDI input devices, exiting.\n" << std::flush;
            exit(EXIT_FAILURE);
        }

        // delete audio output devices
        try {
	    while (true) {
		    AudioOutputDeviceMap::iterator iter = mAudioOutputDevices.begin();
		    if (iter == mAudioOutputDevices.end()) break;
		    DestroyAudioOutputDevice(iter->second);
            }
        }
        catch(...) {
            std::cerr << "Sampler::Reset(): Exception occured while trying to delete all audio output devices, exiting.\n" << std::flush;
            exit(EXIT_FAILURE);
        }
    }

} // namespace LinuxSampler
