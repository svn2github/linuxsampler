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

#include "AudioOutputDevice.h"

namespace LinuxSampler {

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
        {
            std::set<Engine*>::iterator iterEngine = Engines.begin();
            std::set<Engine*>::iterator end        = Engines.end();
            for (; iterEngine != end; iterEngine++) {
                int res = (*iterEngine)->RenderAudio(Samples);
                if (res != 0) result = res;
            }
        }

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
