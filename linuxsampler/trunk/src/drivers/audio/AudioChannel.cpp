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
#include <malloc.h>

namespace LinuxSampler {

    /**
     * Create real channel.
     *
     * @param ChannelNr  - channel number of this new channel
     * @param BufferSize - desired audio data buffer size
     */
    AudioChannel::AudioChannel(uint ChannelNr, uint BufferSize) {
        this->ChannelNr          = ChannelNr;
        this->pBuffer            = (float *) memalign(16,BufferSize*sizeof(float));
        this->uiBufferSize       = BufferSize;
        this->pMixChannel        = NULL;
        this->UsesExternalBuffer = false;

        Parameters["NAME"]           = new ParameterName("Channel " + ToString(ChannelNr));
        Parameters["IS_MIX_CHANNEL"] = new ParameterIsMixChannel(false);

        Clear();
    }

    /**
     * Create channel with external (already existing) audio buffer.
     *
     * @param ChannelNr  - channel number of this new channel
     * @param pBuffer    - external audio buffer
     * @param BufferSIze - size of the external buffer
     */
    AudioChannel::AudioChannel(uint ChannelNr, float* pBuffer, uint BufferSize) {
        this->ChannelNr          = ChannelNr;
        this->pBuffer            = pBuffer;
        this->uiBufferSize       = BufferSize;
        this->pMixChannel        = NULL;
        this->UsesExternalBuffer = true;

        Parameters["NAME"]           = new ParameterName("Channel " + ToString(ChannelNr));
        Parameters["IS_MIX_CHANNEL"] = new ParameterIsMixChannel(false);

        Clear();
    }

    /**
     * Create mix channel.
     *
     * @param ChannelNr              - channel number of this new channel
     * @param pMixChannelDestination - a real audio channel this new mix
     *                                 channel refers to
     */
    AudioChannel::AudioChannel(uint ChannelNr, AudioChannel* pMixChannelDestination) {
        this->ChannelNr          = ChannelNr;
        this->pBuffer            = pMixChannelDestination->Buffer();
        this->uiBufferSize       = pMixChannelDestination->uiBufferSize;
        this->pMixChannel        = pMixChannelDestination;
        this->UsesExternalBuffer = true;

        Parameters["NAME"]           = new ParameterName("Channel " + ToString(ChannelNr));
        Parameters["IS_MIX_CHANNEL"] = new ParameterIsMixChannel(true);
        //TODO: Parameters["MIX_CHANNEL_DESTINATION"] = new ParameterMixChannelDestination(dest_chan);

        Clear();
    }

    /**
     * Destructor
     */
    AudioChannel::~AudioChannel() {
        std::map<String,DeviceRuntimeParameter*>::iterator iter = Parameters.begin();
        while (iter != Parameters.end()) { delete iter->second; iter++; }
        if (!UsesExternalBuffer) free(pBuffer);
    }

    std::map<String,DeviceRuntimeParameter*> AudioChannel::ChannelParameters() {
        return Parameters;
    }
}
