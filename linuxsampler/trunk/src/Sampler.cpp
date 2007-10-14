/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
 *   Copyright (C) 2005 - 2007 Christian Schoenebeck                       *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this library; if not, write to the Free Software           *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston,                 *
 *   MA  02111-1307  USA                                                   *
 ***************************************************************************/

#include <sstream>

#include "Sampler.h"

#include "common/global_private.h"
#include "engines/EngineFactory.h"
#include "engines/EngineChannelFactory.h"
#include "plugins/InstrumentEditorFactory.h"
#include "drivers/audio/AudioOutputDeviceFactory.h"
#include "drivers/midi/MidiInputDeviceFactory.h"
#include "drivers/midi/MidiInstrumentMapper.h"

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
            Engine* engine = pEngineChannel->GetEngine();
            if (pAudioOutputDevice) pAudioOutputDevice->Disconnect(engine);

            MidiInputPort* pMidiInputPort = (pEngineChannel) ? pEngineChannel->GetMidiInputPort() : __GetMidiInputDevicePort(GetMidiInputChannel());
            if (pMidiInputPort) pMidiInputPort->Disconnect(pEngineChannel);
            if (pEngineChannel) {
                if (pAudioOutputDevice) pEngineChannel->DisconnectAudioOutputDevice();
                EngineChannelFactory::Destroy(pEngineChannel);

                // reconnect engine if it still exists
                const std::set<Engine*>& engines = EngineFactory::EngineInstances();
                if (engines.find(engine) != engines.end()) pAudioOutputDevice->Connect(engine);
            }
        }
    }

    void SamplerChannel::SetEngineType(String EngineType) throw (Exception) {
        dmsg(2,("SamplerChannel: Assigning engine type..."));
        
        if (pEngineChannel) {
            if (!strcasecmp(pEngineChannel->EngineName().c_str(), EngineType.c_str())) {
                dmsg(2,("OK\n"));
                return;
            }
        }

        // create new engine channel
        EngineChannel* pNewEngineChannel = EngineChannelFactory::Create(EngineType);
        if (!pNewEngineChannel) throw Exception("Unknown engine type");

        //FIXME: hack to allow fast retrieval of engine channel's sampler channel index
        pNewEngineChannel->iSamplerChannelIndex = Index();

        // dereference midi input port.
        MidiInputPort* pMidiInputPort = __GetMidiInputDevicePort(GetMidiInputPort());
        // disconnect old engine channel
        if (pEngineChannel) {
            Engine* engine = pEngineChannel->GetEngine();
            if (pAudioOutputDevice) pAudioOutputDevice->Disconnect(engine);

            if (pMidiInputPort) pMidiInputPort->Disconnect(pEngineChannel);
            if (pAudioOutputDevice) pEngineChannel->DisconnectAudioOutputDevice();
            EngineChannelFactory::Destroy(pEngineChannel);

            // reconnect engine if it still exists
            const std::set<Engine*>& engines = EngineFactory::EngineInstances();
            if (engines.find(engine) != engines.end()) pAudioOutputDevice->Connect(engine);
        }

        // connect new engine channel
        if (pAudioOutputDevice) {
            pNewEngineChannel->Connect(pAudioOutputDevice);
            pAudioOutputDevice->Connect(pNewEngineChannel->GetEngine());
        }
        if (pMidiInputPort) pMidiInputPort->Connect(pNewEngineChannel, GetMidiInputChannel());
        pEngineChannel = pNewEngineChannel;

        // from now on get MIDI device and port from EngineChannel object
        this->pMidiInputDevice = NULL;
        this->iMidiPort        = 0;

        pEngineChannel->StatusChanged(true);
        fireEngineChanged();
        dmsg(2,("OK\n"));
    }

    void SamplerChannel::SetAudioOutputDevice(AudioOutputDevice* pDevice) {
        if(pAudioOutputDevice == pDevice) return;

        // disconnect old device
        if (pAudioOutputDevice && pEngineChannel) {
            Engine* engine = pEngineChannel->GetEngine();
            pAudioOutputDevice->Disconnect(engine);

            pEngineChannel->DisconnectAudioOutputDevice();

            // reconnect engine if it still exists
            const std::set<Engine*>& engines = EngineFactory::EngineInstances();
            if (engines.find(engine) != engines.end()) pAudioOutputDevice->Connect(engine);
        }

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
        if (!pDevice) throw Exception("No MIDI input device assigned.");

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
            throw Exception("There is no MIDI input port with index " + ToString(iMidiPort) + ".");
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

        throw Exception("Internal error: SamplerChannel index not found");
    }

    void SamplerChannel::AddEngineChangeListener(EngineChangeListener* l) {
        llEngineChangeListeners.AddListener(l);
    }

    void SamplerChannel::RemoveEngineChangeListener(EngineChangeListener* l) {
       llEngineChangeListeners.RemoveListener(l);
    }

    void SamplerChannel::RemoveAllEngineChangeListeners() {
       llEngineChangeListeners.RemoveAllListeners();
    }

    void SamplerChannel::fireEngineChanged() {
        for (int i = 0; i < llEngineChangeListeners.GetListenerCount(); i++) {
            llEngineChangeListeners.GetListener(i)->EngineChanged(Index());
        }
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
        eventHandler.SetSampler(this);
    }

    Sampler::~Sampler() {
        Reset();
    }

    uint Sampler::SamplerChannels() {
        return mSamplerChannels.size();
    }

    void Sampler::AddChannelCountListener(ChannelCountListener* l) {
        llChannelCountListeners.AddListener(l);
    }

    void Sampler::RemoveChannelCountListener(ChannelCountListener* l) {
       llChannelCountListeners.RemoveListener(l);
    }

    void Sampler::fireChannelCountChanged(int NewCount) {
        for (int i = 0; i < llChannelCountListeners.GetListenerCount(); i++) {
            llChannelCountListeners.GetListener(i)->ChannelCountChanged(NewCount);
        }
    }

    void Sampler::AddAudioDeviceCountListener(AudioDeviceCountListener* l) {
        llAudioDeviceCountListeners.AddListener(l);
    }

    void Sampler::RemoveAudioDeviceCountListener(AudioDeviceCountListener* l) {
        llAudioDeviceCountListeners.RemoveListener(l);
    }

    void Sampler::fireAudioDeviceCountChanged(int NewCount) {
        for (int i = 0; i < llAudioDeviceCountListeners.GetListenerCount(); i++) {
            llAudioDeviceCountListeners.GetListener(i)->AudioDeviceCountChanged(NewCount);
        }
    }

    void Sampler::AddMidiDeviceCountListener(MidiDeviceCountListener* l) {
        llMidiDeviceCountListeners.AddListener(l);
    }

    void Sampler::RemoveMidiDeviceCountListener(MidiDeviceCountListener* l) {
        llMidiDeviceCountListeners.RemoveListener(l);
    }

    void Sampler::fireMidiDeviceCountChanged(int NewCount) {
        for (int i = 0; i < llMidiDeviceCountListeners.GetListenerCount(); i++) {
            llMidiDeviceCountListeners.GetListener(i)->MidiDeviceCountChanged(NewCount);
        }
    }

    void Sampler::AddVoiceCountListener(VoiceCountListener* l) {
        llVoiceCountListeners.AddListener(l);
    }

    void Sampler::RemoveVoiceCountListener(VoiceCountListener* l) {
        llVoiceCountListeners.RemoveListener(l);
    }

    void Sampler::fireVoiceCountChanged(int ChannelId, int NewCount) {
        for (int i = 0; i < llVoiceCountListeners.GetListenerCount(); i++) {
            llVoiceCountListeners.GetListener(i)->VoiceCountChanged(ChannelId, NewCount);
        }
    }

    void Sampler::AddStreamCountListener(StreamCountListener* l) {
        llStreamCountListeners.AddListener(l);
    }

    void Sampler::RemoveStreamCountListener(StreamCountListener* l) {
        llStreamCountListeners.RemoveListener(l);
    }

    void Sampler::fireStreamCountChanged(int ChannelId, int NewCount) {
        for (int i = 0; i < llStreamCountListeners.GetListenerCount(); i++) {
            llStreamCountListeners.GetListener(i)->StreamCountChanged(ChannelId, NewCount);
        }
    }

    void Sampler::AddBufferFillListener(BufferFillListener* l) {
        llBufferFillListeners.AddListener(l);
    }

    void Sampler::RemoveBufferFillListener(BufferFillListener* l) {
        llBufferFillListeners.RemoveListener(l);
    }

    void Sampler::fireBufferFillChanged(int ChannelId, String FillData) {
        for (int i = 0; i < llBufferFillListeners.GetListenerCount(); i++) {
            llBufferFillListeners.GetListener(i)->BufferFillChanged(ChannelId, FillData);
        }
    }

    void Sampler::AddTotalVoiceCountListener(TotalVoiceCountListener* l) {
        llTotalVoiceCountListeners.AddListener(l);
    }

    void Sampler::RemoveTotalVoiceCountListener(TotalVoiceCountListener* l) {
        llTotalVoiceCountListeners.RemoveListener(l);
    }

    void Sampler::fireTotalVoiceCountChanged(int NewCount) {
        for (int i = 0; i < llTotalVoiceCountListeners.GetListenerCount(); i++) {
            llTotalVoiceCountListeners.GetListener(i)->TotalVoiceCountChanged(NewCount);
        }
    }

    void Sampler::AddFxSendCountListener(FxSendCountListener* l) {
        llFxSendCountListeners.AddListener(l);
    }

    void Sampler::RemoveFxSendCountListener(FxSendCountListener* l) {
        llFxSendCountListeners.RemoveListener(l);
    }

    void Sampler::fireFxSendCountChanged(int ChannelId, int NewCount) {
        for (int i = 0; i < llFxSendCountListeners.GetListenerCount(); i++) {
            llFxSendCountListeners.GetListener(i)->FxSendCountChanged(ChannelId, NewCount);
        }
    }

    void Sampler::EventHandler::EngineChanged(int ChannelId) {
        EngineChannel* engineChannel = pSampler->GetSamplerChannel(ChannelId)->GetEngineChannel();
        if(engineChannel == NULL) return;
        engineChannel->AddFxSendCountListener(this);
    }

    void Sampler::EventHandler::FxSendCountChanged(int ChannelId, int NewCount) {
        pSampler->fireFxSendCountChanged(ChannelId, NewCount);
    }


    SamplerChannel* Sampler::AddSamplerChannel() {
        // if there's no sampler channel yet
        if (!mSamplerChannels.size()) {
            SamplerChannel* pChannel = new SamplerChannel(this);
            mSamplerChannels[0] = pChannel;
            fireChannelCountChanged(1);
            pChannel->AddEngineChangeListener(&eventHandler);
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
                fireChannelCountChanged(SamplerChannels());
                pChannel->AddEngineChangeListener(&eventHandler);
                return pChannel;
            }
            throw Exception("Internal error: could not find unoccupied sampler channel index.");
        }

        // we have not reached the index limit so we just add the channel past the highest index
        SamplerChannel* pChannel = new SamplerChannel(this);
        mSamplerChannels[lastIndex + 1] = pChannel;
        fireChannelCountChanged(SamplerChannels());
        pChannel->AddEngineChangeListener(&eventHandler);
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
                pSamplerChannel->RemoveAllEngineChangeListeners();
                mSamplerChannels.erase(iterChan);
                delete pSamplerChannel;
                fireChannelCountChanged(SamplerChannels());
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

    std::vector<String> Sampler::AvailableMidiInputDrivers() {
        return MidiInputDeviceFactory::AvailableDrivers();
    }

    std::vector<String> Sampler::AvailableEngineTypes() {
        return EngineFactory::AvailableEngineTypes();
    }

    AudioOutputDevice* Sampler::CreateAudioOutputDevice(String AudioDriver, std::map<String,String> Parameters) throw (Exception) {
        // create new device
        AudioOutputDevice* pDevice = AudioOutputDeviceFactory::Create(AudioDriver, Parameters);

        // add new audio device to the audio device list
        for (uint i = 0; ; i++) { // seek for a free place starting from the beginning
            if (!mAudioOutputDevices[i]) {
                mAudioOutputDevices[i] = pDevice;
                break;
            }
        }

        fireAudioDeviceCountChanged(AudioOutputDevices());
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

    void Sampler::DestroyAudioOutputDevice(AudioOutputDevice* pDevice) throw (Exception) {
        AudioOutputDeviceMap::iterator iter = mAudioOutputDevices.begin();
        for (; iter != mAudioOutputDevices.end(); iter++) {
            if (iter->second == pDevice) {
                // check if there are still sampler engines connected to this device
                for (uint i = 0; i < SamplerChannels(); i++)
                    if (GetSamplerChannel(i)->GetAudioOutputDevice() == pDevice) throw Exception("Sampler channel " + ToString(i) + " is still connected to the audio output device.");

                // disable device
                pDevice->Stop();

                // remove device from the device list
                mAudioOutputDevices.erase(iter);

                // destroy and free device from memory
                delete pDevice;

                fireAudioDeviceCountChanged(AudioOutputDevices());
                break;
            }
        }
    }

    void Sampler::DestroyMidiInputDevice(MidiInputDevice* pDevice) throw (Exception) {
        MidiInputDeviceMap::iterator iter = mMidiInputDevices.begin();
        for (; iter != mMidiInputDevices.end(); iter++) {
            if (iter->second == pDevice) {
                // check if there are still sampler engines connected to this device
                for (uint i = 0; i < SamplerChannels(); i++)
                    if (GetSamplerChannel(i)->GetMidiInputDevice() == pDevice) throw Exception("Sampler channel " + ToString(i) + " is still connected to the midi input device.");

                // disable device
                pDevice->StopListen();

                // remove device from the device list
                mMidiInputDevices.erase(iter);

                // destroy and free device from memory
                delete pDevice;

                fireMidiDeviceCountChanged(MidiInputDevices());
                break;
            }
        }
    }

    MidiInputDevice* Sampler::CreateMidiInputDevice(String MidiDriver, std::map<String,String> Parameters) throw (Exception) {
        // create new device
        MidiInputDevice* pDevice = MidiInputDeviceFactory::Create(MidiDriver, Parameters, this);

	// add new device to the midi device list
	for (uint i = 0; ; i++) { // seek for a free place starting from the beginning
		if (!mMidiInputDevices[i]) {
			mMidiInputDevices[i] = pDevice;
			break;
		}
	}

        fireMidiDeviceCountChanged(MidiInputDevices());
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

        // delete MIDI instrument maps
        try {
            MidiInstrumentMapper::RemoveAllMaps();
        }
        catch(...) {
            std::cerr << "Sampler::Reset(): Exception occured while trying to delete all MIDI instrument maps, exiting.\n" << std::flush;
            exit(EXIT_FAILURE);
        }

        // unload all instrument editor DLLs
        InstrumentEditorFactory::ClosePlugins();
    }

} // namespace LinuxSampler
