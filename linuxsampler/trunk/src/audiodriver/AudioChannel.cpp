/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003 by Benno Senoner and Christian Schoenebeck         *
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
    AudioChannel::AudioChannel(uint BufferSize, String Name) {
        this->pBuffer            = new float[BufferSize];
        this->uiBufferSize       = BufferSize;
        this->pMixChannel        = NULL;
        this->Name               = Name;
        this->UsesExternalBuffer = false;
        Clear();
    }

    /**
     * Create channel with external (already existing) audio buffer.
     *
     * @param pBuffer    - external audio buffer
     * @param BufferSIze - size of the external buffer
     * @param Name       - arbitrary name for this channel (optional)
     */
    AudioChannel::AudioChannel(float* pBuffer, uint BufferSize, String Name) {
        this->pBuffer            = pBuffer;
        this->uiBufferSize       = BufferSize;
        this->pMixChannel        = NULL;
        this->Name               = Name;
        this->UsesExternalBuffer = true;
        Clear();
    }

    /**
     * Create mix channel.
     *
     * @param pMixChannel - the real channel this new mix channel refers to
     * @param Name        - arbitrary name for this channel (optional)
     */
    AudioChannel::AudioChannel(AudioChannel* pMixChannel, String Name) {
        this->pBuffer            = pMixChannel->Buffer();
        this->uiBufferSize       = pMixChannel->uiBufferSize;
        this->pMixChannel        = pMixChannel;
        this->Name               = Name;
        this->UsesExternalBuffer = true;
        Clear();
    }

    /**
     * Destructor
     */
    AudioChannel::~AudioChannel() {
        if (!UsesExternalBuffer) delete[] pBuffer;
    }
}
