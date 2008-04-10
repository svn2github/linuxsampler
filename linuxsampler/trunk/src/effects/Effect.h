/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2008 Christian Schoenebeck                              *
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

#ifndef LS_EFFECT_H
#define LS_EFFECT_H

#include <vector>
#include "../drivers/audio/AudioChannel.h"

namespace LinuxSampler {

// just symbol prototyping
class AudioOutputDevice;

/**
 * Abstract base class for sampler internal effects.
 */
class Effect {
public:
    /////////////////////////////////////////////////////////////////
    // abstract methods
    //     (these have to be implemented by the descendant)

    /**
     * Use the input audio signal given with @a ppInputChannels, render the
     * effect and mix the result into the effect's output channels.
     *
     * @param Samples         - amount of sample points to process
     */
    virtual void RenderAudio(uint Samples) = 0;

    /**
     * Will be called by the sampler before using the effect the first time.
     * This method can be implemented by the effect to adjust itself to the
     * requirements given by the audio output device.
     *
     * This is the perfect place to create the required audio input and
     * output channels! ;-)
     *
     * @param pDevice - audio output device which is going to play the signal
     */
    virtual void InitEffect(AudioOutputDevice* pDevice);

    /**
     * Destructor, deletes all audio input and output channels.
     */
    virtual ~Effect();



    /////////////////////////////////////////////////////////////////
    // normal methods
    //     (usually not to be overriden by descendant)

    /**
     * Returns audio input channel with index \a ChannelIndex or NULL if
     * index out of bounds.
     */
    AudioChannel* InputChannel(uint ChannelIndex) const;

    /**
     * Returns the amount of audio input channels the effect is currently
     * providing.
     */
    uint InputChannelCount() const;

    /**
     * Returns audio output channel with index \a ChannelIndex or NULL if
     * index out of bounds.
     */
    AudioChannel* OutputChannel(uint ChannelIndex) const;

    /**
     * Returns the amount of audio output channels the effect is currently
     * providing.
     */
    uint OutputChannelCount() const;

protected:
    std::vector<AudioChannel*> vInputChannels;
    std::vector<AudioChannel*> vOutputChannels;
};

} // namespace LinuxSampler

#endif // LS_EFFECT_H
