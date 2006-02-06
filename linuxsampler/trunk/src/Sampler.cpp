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

#include "engines/EngineFactory.h"
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
        pAudioOutputDevice = NULL;
        pMidiInputDevice   = NULL;
        iMidiPort          = 0;
        midiChannel        = midi_chan_all;
        iIndex             = -1;
    }

    SamplerChannel::~SamplerChannel() {
        if (pEngineChannel) {
            MidiInputPort* pMidiInputPort = (pEngineChannel) ? pEngineChannel->GetMidiInputPort() : __GetMidiInputDevicePort(GetMidiInputChannel());
            if (pMidiInputPort) pMidiInputPort->Disconnect(pEngineChannel);
            if (pEngineChannel) {
                if (pAudioOutputDevice) pEngineChannel->DisconnectAudioOutputDevice();
                EngineChannelFactory::Destroy(pEngineChannel);
            }
        }
    }

    void SamplerChannel::SetEngineType(String EngineType) throw (LinuxSamplerException) {
        dmsg(2,("SamplerChannel: Assigning engine type..."));

        // create new engine channel
        EngineChannel* pNewEngineChannel = EngineChannelFactory::Create(EngineType);
        if (!pNewEngineChannel) throw LinuxSamplerException("Unknown engine type");

        //FIXME: hack to allow fast retrieval of engine channel's sampler channel index
        pNewEngineChannel->iSamplerChannelIndex = Index();

        // dereference midi input port.
        MidiInputPort* pMidiInputPort = __GetMidiInputDevicePort(GetMidiInputPort());
        // disconnect old engine channel
        if (pEngineChannel) {
            if (pMidiInputPort) pMidiInputPort->Disconnect(pEngineChannel);
            if (pAudioOutputDevice) pEngineChannel->DisconnectAudioOutputDevice();
            EngineChannelFactory::Destroy(pEngineChannel);
        }

        // connect new engine channel
        if (pMidiInputPort) pMidiInputPort->Connect(pNewEngineChannel, GetMidiInputChannel());
        if (pAudioOutputDevice) {
            pNewEngineChannel->Connect(pAudioOutputDevice);
            pAudioOutputDevice->Connect(pNewEngineChannel->GetEngine());
        }
        pEngineChannel = pNewEngineChannel;

        // from now on get MIDI device and port from EngineChannel object
        this->pMidiInputDevice = NULL;
        this->iMidiPort        = 0;

        pEngineChannel->StatusChanged(true);

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
       SetMidiInput(pDevice, 0, GetMidiInputChannel());
    }

    void SamplerChannel::SetMidiInputPort(int MidiPort) {
       SetMidiInput(GetMidiInputDevice(), MidiPort, GetMidiInputChannel());
    }

    void SamplerChannel::SetMidiInputChannel(midi_chan_t MidiChannel) {
       SetMidiInput(GetMidiInputDevice(), GetMidiInputPort(), MidiChannel);
    }

    void SamplerChannel::SetMidiInput(MidiInputDevice* pDevice, int iMidiPort, midi_chan_t MidiChannel) {
        if (!pDevice) throw LinuxSamplerException("No MIDI input device assigned.");

        // get old and new midi input port
        MidiInputPort* pOldMidiInputPort = __GetMidiInputDevicePort(GetMidiInputPort());
        MidiInputPort* pNewMidiInputPort = pDevice->GetPort(iMidiPort);

        // disconnect old device port
        if (pOldMidiInputPort && pEngineChannel) pOldMidiInputPort->Disconnect(pEngineChannel);
        // remember new device, port and channel if not engine channel yet created
        if (!pEngineChannel) {
            this->pMidiInputDevice = pDevice;
            this->iMidiPort        = iMidiPort;
            this->midiChannel      = MidiChannel;
        }

        // connect new device port
        if (pNewMidiInputPort && pEngineChannel) pNewMidiInputPort->Connect(pEngineChannel, MidiChannel);
        // Ooops.
        if (pNewMidiInputPort == NULL)
            throw LinuxSamplerException("There is no MIDI input port with index " + ToString(iMidiPort) + ".");
    }

    EngineChannel* SamplerChannel::GetEngineChannel() {
        return pEngineChannel;
    }

    midi_chan_t SamplerChannel::GetMidiInputChannel() {
        if (pEngineChannel) this->midiChannel = pEngineChannel->MidiChannel();
        return this->midiChannel;
    }

    int SamplerChannel::GetMidiInputPort() {
        MidiInputPort* pMidiInputPort = (pEngineChannel) ? pEngineChannel->GetMidiInputPort() : NULL;
        if (pMidiInputPort) this->iMidiPort = (int) pMidiInputPort->GetPortNumber();
        return iMidiPort;
    }

    AudioOutputDevice* SamplerChannel::GetAudioOutputDevice() {
        return pAudioOutputDevice;
    }

    MidiInputDevice* SamplerChannel::GetMidiInputDevice() {
        if (pEngineChannel)
            pMidiInputDevice = (pEngineChannel->GetMidiInputPort()) ? pEngineChannel->GetMidiInputPort()->GetDevice() : NULL;
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

    MidiInputPort* SamplerChannel::__GetMidiInputDevicePort(int iMidiPort) {
        MidiInputPort* pMidiInputPort = NULL;
        MidiInputDevice* pMidiInputDevice = GetMidiInputDevice();
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
	    LSCPServer::SendLSCPNotify(LSCPEvent(LSCPEvent::event_channel_count, 1));
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
		LSCPServer::SendLSCPNotify(LSCPEvent(LSCPEvent::event_channel_count, i));
                return pChannel;
            }
            throw LinuxSamplerException("Internal error: could not find unoccupied sampler channel index.");
        }

        // we have not reached the index limit so we just add the channel past the highest index
        SamplerChannel* pChannel = new SamplerChannel(this);
        mSamplerChannels[lastIndex + 1] = pChannel;
	LSCPServer::SendLSCPNotify(LSCPEvent(LSCPEvent::event_channel_count, lastIndex + 1));
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
		LSCPServer::SendLSCPNotify(LSCPEvent(LSCPEvent::event_channel_count, mSamplerChannels.size()));
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

                // destroy and free device from memory
                delete pDevice;
            }
        }
        // remove devices from the device list
        mAudioOutputDevices.clear();
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

                // destroy and free device from memory
                delete pDevice;
            }
        }
        // remove devices from the device list
        mMidiInputDevices.clear();
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

    int Sampler::GetVoiceCount() {
        int count = 0;
        std::set<Engine*>::iterator it = EngineFactory::EngineInstances().begin();

        for(; it != EngineFactory::EngineInstances().end(); it++) {
            count += (*it)->VoiceCount();
        }

        return count;
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
