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

#include "AudioChannel.h"

namespace LinuxSampler {

    /**
     * Create real channel.
     *
     * @param BufferSize - desired audio data buffer size
     * @param Name       - arbitrary name for this channel (optional)
     */
    AudioChannel::AudioChannel(uint BufferSize, String Name, std::map<String,DeviceRuntimeParameter*> ChannelParameters) {
        this->pBuffer            = new float[BufferSize];
        this->uiBufferSize       = BufferSize;
        this->pMixChannel        = NULL;
        this->UsesExternalBuffer = false;

        if (!ChannelParameters["NAME"])           ChannelParameters["Name"]           = new ParameterName(Name);
        if (!ChannelParameters["IS_MIX_CHANNEL"]) ChannelParameters["IS_MIX_CHANNEL"] = new ParameterIsMixChannel(false);
        this->mParameters = ChannelParameters;

        Clear();
    }

    /**
     * Create channel with external (already existing) audio buffer.
     *
     * @param pBuffer    - external audio buffer
     * @param BufferSIze - size of the external buffer
     * @param Name       - arbitrary name for this channel (optional)
     */
    AudioChannel::AudioChannel(float* pBuffer, uint BufferSize, String Name, std::map<String,DeviceRuntimeParameter*> ChannelParameters) {
        this->pBuffer            = pBuffer;
        this->uiBufferSize       = BufferSize;
        this->pMixChannel        = NULL;
        this->UsesExternalBuffer = true;

        if (!ChannelParameters["NAME"])           ChannelParameters["Name"]           = new ParameterName(Name);
        if (!ChannelParameters["IS_MIX_CHANNEL"]) ChannelParameters["IS_MIX_CHANNEL"] = new ParameterIsMixChannel(false);

        Clear();
    }

    /**
     * Create mix channel.
     *
     * @param pMixChannel - the real channel this new mix channel refers to
     * @param Name        - arbitrary name for this channel (optional)
     */
    AudioChannel::AudioChannel(AudioChannel* pMixChannel, String Name, std::map<String,DeviceRuntimeParameter*> ChannelParameters) {
        this->pBuffer            = pMixChannel->Buffer();
        this->uiBufferSize       = pMixChannel->uiBufferSize;
        this->pMixChannel        = pMixChannel;
        this->UsesExternalBuffer = true;

        if (!ChannelParameters["NAME"])                    ChannelParameters["Name"]                    = new ParameterName(Name);
        if (!ChannelParameters["IS_MIX_CHANNEL"])          ChannelParameters["IS_MIX_CHANNEL"]          = new ParameterIsMixChannel(true);
        //TODO: if (!ChannelParameters["MIX_CHANNEL_DESTINATION"]) ChannelParameters["MIX_CHANNEL_DESTINATION"] = new ParameterMixChannelDestination(dest_chan);

        Clear();
    }

    /**
     * Destructor
     */
    AudioChannel::~AudioChannel() {
        std::map<String,DeviceRuntimeParameter*>::iterator iter = mParameters.begin();
        while (iter != mParameters.end()) { delete iter->second; iter++; }
        if (!UsesExternalBuffer)          delete[] pBuffer;
    }

    std::map<String,DeviceRuntimeParameter*> AudioChannel::ChannelParameters() {
        return mParameters;
    }
}
