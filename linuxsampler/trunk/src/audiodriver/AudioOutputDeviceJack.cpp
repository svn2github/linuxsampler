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

#include "AudioOutputDeviceJack.h"
#include "AudioOutputDeviceFactory.h"

#if HAVE_JACK

namespace LinuxSampler {

    REGISTER_AUDIO_OUTPUT_DRIVER("Jack",AudioOutputDeviceJack);

    /**
     * Open and initialize connection to the JACK system.
     *
     * @param Parameters - optional parameters
     * @throws AudioOutputException  on error
     * @see AcquireChannels()
     */
    AudioOutputDeviceJack::AudioOutputDeviceJack(std::map<String,String> Parameters) : AudioOutputDevice(std::map<String,DeviceCreationParameter*>()) {
        if ((hJackClient = jack_client_new("LinuxSampler")) == 0)
            throw AudioOutputException("Seems Jack server not running.");

        jack_set_process_callback(hJackClient, __libjack_process_callback, this);
        jack_on_shutdown(hJackClient, __libjack_shutdown_callback, this);
        if (jack_activate(hJackClient))
            throw AudioOutputException("Jack: Cannot activate Jack client.");

        uiMaxSamplesPerCycle = jack_get_buffer_size(hJackClient);

#if 0
        // create amount of audio channels and jack output ports we need for autoconnect
        for (uint p = 0; p < AutoConnectPorts; p++) {
            // create jack output port
            std::stringstream portid; portid << "LinuxSampler:" << p;
            jack_port_t* newport;
            if (newport = jack_port_register(hJackClient, portid.str().c_str(), JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0)) {
                hJackPorts.push_back(newport);
            }
            else throw AudioOutputException("Jack: Cannot register Jack output port.");

            // create LS audio channel
            std::stringstream chanid; chanid << "Jack:" << p;
            Channels.push_back(new AudioChannel((float*) jack_port_get_buffer(newport, uiMaxSamplesPerCycle), uiMaxSamplesPerCycle, chanid.str()));

            // autoconnect port
            if (jack_connect(hJackClient, portid.str().c_str(), AutoConnectPortIDs[p].c_str())) {
                std::stringstream err; err << "Jack: Cannot auto connect port " << p;
                throw AudioOutputException(err.str());
            }
        }
#endif
    }

    AudioOutputDeviceJack::~AudioOutputDeviceJack() {
        // destroy all audio channels
        for (int c = 0; c < Channels.size(); c++) delete Channels[c];
        // destroy jack client
        jack_client_close(hJackClient);
    }

    /**
     * This method should not be called directly! It will be called by
     * libjack to demand transmission of further sample points.
     */
    int AudioOutputDeviceJack::Process(uint Samples) {
        if (csIsPlaying.Pop()) {
            // let all connected engines render 'Samples' sample points
            return RenderAudio(Samples);
        }
        else {
            // playback stop by zeroing output buffer(s) and not calling connected sampler engines to render audio
            return RenderSilence(Samples);
        }
    }

    void AudioOutputDeviceJack::Play() {
        csIsPlaying.PushAndUnlock(true);
    }

    bool AudioOutputDeviceJack::IsPlaying() {
        csIsPlaying.GetUnsafe();
    }

    void AudioOutputDeviceJack::Stop() {
        csIsPlaying.PushAndUnlock(false);
    }

    void AudioOutputDeviceJack::AcquireChannels(uint uiChannels) {
        if (uiChannels > this->Channels.size()) {
            for (int c = this->Channels.size(); c < uiChannels; c++) {
                // create new jack output port
                std::stringstream portid; portid << "LinuxSampler:" << c;
                jack_port_t* newport;
                if (newport = jack_port_register(hJackClient, portid.str().c_str(), JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0)) {
                    hJackPorts.push_back(newport);
                }
                else throw AudioOutputException("Jack: Cannot register Jack output port.");

                // create LS audio channel
                std::stringstream chanid; chanid << "Jack:" << c;
                Channels.push_back(new AudioChannel((float*) jack_port_get_buffer(newport, uiMaxSamplesPerCycle), uiMaxSamplesPerCycle, chanid.str()));
            }
        }
    }

    uint AudioOutputDeviceJack::MaxSamplesPerCycle() {
        return jack_get_buffer_size(hJackClient);
    }

    uint AudioOutputDeviceJack::SampleRate() {
        return jack_get_sample_rate(hJackClient);
    }

    String AudioOutputDeviceJack::Description() {
        return "JACK Audio Connection Kit";
    }

    String AudioOutputDeviceJack::Version() {
       String s = "$Revision: 1.6 $";
       return s.substr(11, s.size() - 13); // cut dollar signs, spaces and CVS macro keyword
    }

    std::map<String,DeviceCreationParameter*> AudioOutputDeviceJack::AvailableParameters() {
        // FIXME: not a good solution to get the commot parameters (ACTIVE,SAMPERATE,CHANNELS which have to be offered by all audio output drivers)
        std::map<String,DeviceCreationParameter*> available_parameters = AudioOutputDevice::AvailableParameters();
        return available_parameters; // this driver currently does not have additional, individual device parameters
    }


    // libjack callback functions

    int __libjack_process_callback(jack_nframes_t nframes, void* arg) {
        AudioOutputDeviceJack* pAudioOutputDeviceJack = (AudioOutputDeviceJack*) arg;
        return pAudioOutputDeviceJack->Process(nframes);
    }

    void __libjack_shutdown_callback(void* arg) {
        AudioOutputDeviceJack* pAudioOutputDeviceJack = (AudioOutputDeviceJack*) arg;
        pAudioOutputDeviceJack->Stop();
        fprintf(stderr, "Jack: Jack server shutdown, exiting.\n");
    }

} // namespace LinuxSampler

#endif // HAVE_JACK
