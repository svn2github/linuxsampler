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

#ifndef __LS_AUDIOOUTPUTDEVICE_H__
#define __LS_AUDIOOUTPUTDEVICE_H__

#include <set>
#include <vector>
#include <stdexcept>

#include "../common/global.h"
#include "../common/LinuxSamplerException.h"
#include "../engines/common/Engine.h"
#include "AudioChannel.h"

namespace LinuxSampler {

    // just symbol prototyping
    class Engine;

    /** Abstract base class for audio output drivers in LinuxSampler
     *
     * This class will be derived by specialized classes which implement the
     * connection to a specific audio output system (e.g. Alsa, Jack,
     * CoreAudio).
     */
    class AudioOutputDevice {
        public:

            /////////////////////////////////////////////////////////////////
            // abstract methods
            //     (these have to be implemented by the descendant)

            /**
             * Start playback of audio signal on the audio device. It's the
             * responsibility of the implementing audio device to call the
             * RenderAudio(uint Samples) method of all connected engines.
             * This will cause the engines to continue to render 'Samples'
             * number of audio sample points and the engines will
             * automatically add their audio signals to the audio buffers of
             * the audio channels of this audio device. So the implementing
             * audio device just has to access the buffers of it's audio
             * channels.
             *
             * @throws AudioOutputException  if playback can not be started
             * @see AudioChannel
             */
            virtual void Play() = 0;

            /**
             * Returns true if the audio device is currently playing back.
             */
            virtual bool IsPlaying() = 0;

            /**
             * Stop playback of audio signal on the audio device. The
             * implementing audio device will stop calling the RenderAudio()
             * method of all connected engines and close it's connection to
             * audio output system.
             */
            virtual void Stop() = 0;

            /**
             * This method will usually be called by the sampler engines that
             * are connected to this audio device to inform the audio device
             * how much audio channels the engine(s) need. It's the
             * responsibility of the audio device to offer that amount of
             * audio channels - again: this is not an option this is a must!
             * The engines will assume to be able to access those audio
             * channels right after. If the audio driver is not able to offer
             * that much channels, it can simply create mix channels which
             * are then just mixed to the 'real' audio channels. See
             * AudioChannel.h for details about channels and mix channels.
             *
             * @param Channels - amount of output channels required by
             *                   a sampler engine
             * @throws AudioOutputException  if desired amount of channels
             *                               cannot be offered
             * @see AudioChannel
             */
            virtual void AcquireChannels(uint Channels) = 0;

            /**
             * Maximum amount of sample points the implementing audio
             * device will ever demand the sampler engines to write in one
             * fragment cycle / period. Simple audio device drivers usually
             * have a fixed fragment size, so those devices just would return
             * the fragment size in this method.
             *
             * @returns  max. amount of sample points ever
             */
            virtual uint MaxSamplesPerCycle() = 0;

            /**
             * Playback samplerate the audio device uses. The sampler engines
             * currently assume this to be a constant value for the whole
             * life time of an instance of the implementing audio device.
             *
             * @returns  sample rate in Hz
             */
            virtual uint SampleRate() = 0;



            /////////////////////////////////////////////////////////////////
            // normal methods
            //     (usually not to be overriden by descendant)

            /**
             * Connect given sampler engine to this audio output device. The
             * engine will be added to the Engines container of this audio
             * device and the engine will also automatically be informed
             * about the connection.
             *
             * @param pEngine - sampler engine
             */
            void Connect(Engine* pEngine);

            /**
             * Disconnect given sampler engine from this audio output device.
             * Removes given sampler engine reference from the Engines
             * container of this audio device.
             *
             * @param pEngine - sampler engine
             */
            void Disconnect(Engine* pEngine);

            /**
             * Returns audio channel with index \a ChannelIndex or NULL if
             * index out of bounds.
             */
            AudioChannel* Channel(uint ChannelIndex);

        protected:
            std::set<Engine*>          Engines;  ///< All sampler engines that are connected to the audio output device.
            std::vector<AudioChannel*> Channels; ///< All audio channels of the audio output device. This is just a container; the descendant has to create channels by himself.

            /**
             * This method should be called by the AudioOutputDevice
             * descendant to let all connected engines proceed to render the
             * given amount of sample points. The engines will place their
             * calculated audio data by themselfes into the buffers of the
             * respective AudioChannel objects, so the implementing audio
             * output device just has to copy the AudioChannel buffers to
             * the output buffer(s) of its audio system.
             *
             * @returns  0 on success or the last error return code of one
             *           engine
             */
            int RenderAudio(uint Samples);

            /**
             * This can be called as an alternative to RenderAudio() for
             * just writing silence to the audio output buffers and not
             * calling the connected sampler engines for rendering audio, so
             * to provide a method to stop playback if the used audio output
             * system doesn't provide a better way.
             *
             * @returns  0 on success
             */
            int RenderSilence(uint Samples);
    };

    /**
     * Audio output exception that should be thrown by the AudioOutputDevice
     * descendants in case initialization of the audio output system failed
     * (which should be done in the constructor of the AudioOutputDevice
     * descendant).
     */
    class AudioOutputException : public LinuxSamplerException {
        public:
            AudioOutputException(const std::string& msg) : LinuxSamplerException(msg) {}
    };
}

#endif // __LS_AUDIOOUTPUTDEVICE_H__
