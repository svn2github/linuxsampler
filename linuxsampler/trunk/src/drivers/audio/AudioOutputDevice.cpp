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

#include "AudioOutputDeviceFactory.h"
#include "AudioOutputDevice.h"

namespace LinuxSampler {

// *************** ParameterActive ***************
// *

    AudioOutputDevice::ParameterActive::ParameterActive() : DeviceCreationParameterBool() {
        InitWithDefault();
    }

    AudioOutputDevice::ParameterActive::ParameterActive(String s) : DeviceCreationParameterBool(s) {
    }

    String AudioOutputDevice::ParameterActive::Description() {
        return "Enable / disable device";
    }

    bool AudioOutputDevice::ParameterActive::Fix() {
        return false;
    }

    bool AudioOutputDevice::ParameterActive::Mandatory() {
        return false;
    }

    std::map<String,DeviceCreationParameter*> AudioOutputDevice::ParameterActive::DependsAsParameters() {
        return std::map<String,DeviceCreationParameter*>();
    }

    optional<bool> AudioOutputDevice::ParameterActive::DefaultAsBool(std::map<String,String> Parameters) {
        return true;
    }

    void AudioOutputDevice::ParameterActive::OnSetValue(bool b) throw (LinuxSamplerException) {
        if (b) ((AudioOutputDevice*)pDevice)->Play();
        else ((AudioOutputDevice*)pDevice)->Stop();
    }

    String AudioOutputDevice::ParameterActive::Name() {
        return "ACTIVE";
    }



// *************** ParameterSampleRate ***************
// *

    AudioOutputDevice::ParameterSampleRate::ParameterSampleRate() : DeviceCreationParameterInt() {
        InitWithDefault();
    }

    AudioOutputDevice::ParameterSampleRate::ParameterSampleRate(String s) : DeviceCreationParameterInt(s) {
    }

    String AudioOutputDevice::ParameterSampleRate::Description() {
        return "Output sample rate";
    }

    bool AudioOutputDevice::ParameterSampleRate::Fix() {
        return true;
    }

    bool AudioOutputDevice::ParameterSampleRate::Mandatory() {
        return false;
    }

    std::map<String,DeviceCreationParameter*> AudioOutputDevice::ParameterSampleRate::DependsAsParameters() {
        return std::map<String,DeviceCreationParameter*>();
    }

    optional<int> AudioOutputDevice::ParameterSampleRate::DefaultAsInt(std::map<String,String> Parameters) {
        return 44100;
    }

    optional<int> AudioOutputDevice::ParameterSampleRate::RangeMinAsInt(std::map<String,String> Parameters) {
        return optional<int>::nothing;
    }

    optional<int> AudioOutputDevice::ParameterSampleRate::RangeMaxAsInt(std::map<String,String> Parameters) {
        return optional<int>::nothing;
    }

    std::vector<int> AudioOutputDevice::ParameterSampleRate::PossibilitiesAsInt(std::map<String,String> Parameters) {
        return std::vector<int>();
    }

    void AudioOutputDevice::ParameterSampleRate::OnSetValue(int i) throw (LinuxSamplerException) {
        /* cannot happen, as parameter is fix */
    }

    String AudioOutputDevice::ParameterSampleRate::Name() {
        return "SAMPLERATE";
    }



// *************** ParameterChannels ***************
// *

    AudioOutputDevice::ParameterChannels::ParameterChannels() : DeviceCreationParameterInt() {
       InitWithDefault();
    }

    AudioOutputDevice::ParameterChannels::ParameterChannels(String s) : DeviceCreationParameterInt(s) {
    }

    String AudioOutputDevice::ParameterChannels::Description() {
        return "Number of output channels";
    }

    bool AudioOutputDevice::ParameterChannels::Fix() {
        return false;
    }

    bool AudioOutputDevice::ParameterChannels::Mandatory() {
        return false;
    }

    std::map<String,DeviceCreationParameter*> AudioOutputDevice::ParameterChannels::DependsAsParameters() {
        return std::map<String,DeviceCreationParameter*>();
    }

    optional<int> AudioOutputDevice::ParameterChannels::DefaultAsInt(std::map<String,String> Parameters) {
        return 2;
    }

    optional<int> AudioOutputDevice::ParameterChannels::RangeMinAsInt(std::map<String,String> Parameters) {
        return optional<int>::nothing;
    }

    optional<int> AudioOutputDevice::ParameterChannels::RangeMaxAsInt(std::map<String,String> Parameters) {
        return optional<int>::nothing;
    }

    std::vector<int> AudioOutputDevice::ParameterChannels::PossibilitiesAsInt(std::map<String,String> Parameters) {
        return std::vector<int>();
    }

    void AudioOutputDevice::ParameterChannels::OnSetValue(int i) throw (LinuxSamplerException) {
        ((AudioOutputDevice*)pDevice)->AcquireChannels(i);
    }

    String AudioOutputDevice::ParameterChannels::Name() {
        return "CHANNELS";
    }



// *************** AudioOutputDevice ***************
// *

    AudioOutputDevice::AudioOutputDevice(std::map<String,DeviceCreationParameter*> DriverParameters) {
        this->Parameters = DriverParameters;
    }

    AudioOutputDevice::~AudioOutputDevice() {
        // delete all audio channels
        {
            std::vector<AudioChannel*>::iterator iter = Channels.begin();
            while (iter != Channels.end()) {
                Channels.erase(iter);
                delete *iter;
                iter++;
            }

        }

        // delete all device parameters
        {
            std::map<String,DeviceCreationParameter*>::iterator iter = Parameters.begin();
            while (iter != Parameters.end()) {
                Parameters.erase(iter);
                delete iter->second;
                iter++;
            }
        }
    }

    void AudioOutputDevice::Connect(Engine* pEngine) {
        if (Engines.find(pEngine) == Engines.end()) {
            pEngine->Connect(this);
            Engines.insert(pEngine);
        }
    }

    void AudioOutputDevice::Disconnect(Engine* pEngine) {
        if (Engines.find(pEngine) != Engines.end()) { // if clause to prevent disconnect loop
            Engines.erase(pEngine);
            pEngine->DisconnectAudioOutputDevice();
        }
    }

    AudioChannel* AudioOutputDevice::Channel(uint ChannelIndex) {
        return (ChannelIndex < Channels.size()) ? Channels[ChannelIndex] : NULL;
    }

    void AudioOutputDevice::AcquireChannels(uint Channels) {
        if (Channels > this->Channels.size()) {
            for (int c = this->Channels.size(); c < Channels; c++) {
                this->Channels.push_back(CreateChannel(c));
            }
        }
    }

    std::map<String,DeviceCreationParameter*> AudioOutputDevice::DeviceParameters() {
        return Parameters;
    }

    int AudioOutputDevice::RenderAudio(uint Samples) {
        if (Channels.empty()) return 0;

        // reset all channels with silence
        {
            std::vector<AudioChannel*>::iterator iterChannels = Channels.begin();
            std::vector<AudioChannel*>::iterator end          = Channels.end();
            for (; iterChannels != end; iterChannels++)
                (*iterChannels)->Clear(); // zero out audio buffer
        }

        int result = 0;

        // let all connected engines render audio for the current audio fragment cycle
        #if USE_EXCEPTIONS
        try
        #endif // USE_EXCEPTIONS
        {
            std::set<Engine*>::iterator iterEngine = Engines.begin();
            std::set<Engine*>::iterator end        = Engines.end();
            for (; iterEngine != end; iterEngine++) {
                int res = (*iterEngine)->RenderAudio(Samples);
                if (res != 0) result = res;
            }
        }
        #if USE_EXCEPTIONS
        catch (std::runtime_error se) {
            std::cerr << "std::runtime_error: " << se.what() << std::endl << std::flush;
            exit(EXIT_FAILURE);
        }
        #endif // USE_EXCEPTIONS

        return result;
    }

    int AudioOutputDevice::RenderSilence(uint Samples) {
        if (Channels.empty()) return 0;

        // reset all channels with silence
        {
            std::vector<AudioChannel*>::iterator iterChannels = Channels.begin();
            std::vector<AudioChannel*>::iterator end          = Channels.end();
            for (; iterChannels != end; iterChannels++)
                (*iterChannels)->Clear(); // zero out audio buffer
        }

        return 0;
    }

} // namespace LinuxSampler
