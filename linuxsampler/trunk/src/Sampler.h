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

#ifndef __LS_SAMPLER_H__
#define __LS_SAMPLER_H__

#include <vector>
#include <map>
#include "common/global.h"
#include "common/LinuxSamplerException.h"
#include "engines/common/Engine.h"
#include "mididriver/MidiInputDevice.h"
#include "audiodriver/AudioOutputDevice.h"

namespace LinuxSampler {

    // just symbol prototyping
    class Sampler;

    /** LinuxSampler sampler channel
     *
     * Encapsulates one sampler engine, one connection to a MIDI input
     * device and one connection to an audio output device. You cannot
     * create an instance of this class on your own, you have to use the
     * AddSamplerChannel() method of the Sampler object to create a new
     * sampler channel.
     */
    class SamplerChannel {
        public:
            /**
             * Deploy a sampler engine of the given type for this sampler
             * channnel. If there was already a sampler engine deployed on
             * this sampler channel, then the old engine will automatically
             * be destroyed.
             *
             * @param EngineType - type of the engine to deploy
             */
            void LoadEngine(Engine::type_t EngineType); // TODO: to be changed to 'void LoadEngine(String EngineType) throws (LinuxSamplerException);'

            /**
             * Connect this sampler channel to an audio output device, that
             * is an instance of an audio output driver. If this sampler
             * channel was already connected to an audio output device, then
             * the old connection will automatically be removed before.
             *
             * @param pDevice - audio output device to connect to
             */
            void SetAudioOutputDevice(AudioOutputDevice* pDevice);

            /**
             * Connect this sampler channel to and MIDI input device (that
             * is MIDI input driver) of the given type. If the MIDI input
             * driver for the desired MIDI input system is not yet created,
             * then it will be created automatically, but with default
             * settings though. If this sampler channel was already
             * connected to a MIDI input device, then the old connection
             * will automatically be removed before.
             *
             * @param MidiType    - MIDI input system to connect to
             * @param MidiChannel - optional: MIDI channel on which the
             *                      sampler channel should listen to
             *                      (default: listen on all MIDI channels)
             */
            void SetMidiInputDevice(MidiInputDevice::type_t MidiType, MidiInputDevice::midi_chan_t MidiChannel = MidiInputDevice::midi_chan_all); // TODO: 'MidiType' type to be changed to 'MidiInputDevice*'

            /**
             * Returns the engine that was deployed on this sampler channel.
             *
             * @returns  pointer to engine or NULL if no engine deployed
             */
            Engine* GetEngine();

            /**
             * Returns the MIDI input device to which this sampler channel
             * is currently connected to.
             *
             * @returns  pointer to MIDI input device or NULL if not
             *           connected
             */
            MidiInputDevice* GetMidiInputDevice();

            /**
             * Returns the audio output device to which this sampler channel
             * is currently connected to.
             *
             * @returns  pointer to audio output device or NULL if not
             *           connected
             */
            AudioOutputDevice* GetAudioOutputDevice();

            /**
             * Returns the index number of this sampler channel within the
             * Sampler instance.
             */
            uint Index();

        protected:
            SamplerChannel(Sampler* pS);
           ~SamplerChannel();

            Sampler*           pSampler;
            Engine*            pEngine;
            MidiInputDevice*   pMidiInputDevice;
            AudioOutputDevice* pAudioOutputDevice;
            int                iIndex;

            friend class Sampler;
    };

    /** LinuxSampler main class
     *
     * This is the toplevel class for a LinuxSampler instance.
     *
     * LinuxSampler can have arbitrary numbers of sampler channels. Each
     * sampler channel can individually be deployed with it's own sampler
     * engine, connected to an arbitrary MIDI input device and connected to
     * an arbitrary audio output device. Here an example setup:
     *
     *	S.Channel.	MIDI in		S.Engine		Audio out
     *	-------------------------------------------------------------------
     *	0		Alsa	->	gig::Engine	->	Jack
     *	1		VSTi	->	Akai::Engine	->	VSTi
     *	2		Jack	->	DLS::Engine	->	Jack
     *	3		Jack	->	SF::Engine	->	Alsa
     *
     *	... (and so on) ...
     *
     * Note that not all audio and MIDI backends and sampler engines listed
     * in the example above are already implemented!
     *
     * As you can see in the example setup, LinuxSampler is capable to use
     * several, different audio output and MIDI input systems
     * simultaniously at the same time. Here the example setup shown in the
     * ascpect of MIDI input and audio output devices / drivers:
     *
     *				  ######################### #########################
     *				  # AudioOutputDeviceJack # # AudioOutputDeviceVSTi #
     *				  ######################### #########################
     *						^   ^		^
     *	  /------------>|Sampler Channel 0|-----/   |		|
     *	  |  /--------->|Sampler Channel 1|---------------------/
     *	  |  |	  /---->|Sampler Channel 2|---------/
     *	  |  |	  |  /->|Sampler Channel 3|------------>#########################
     *	  |  |	  |  |	... (and so on) ...		# AudioOutputDeviceAlsa #
     *	  |  |	  |  |					#########################
     *	  |  |	  |  \----------------------------------------------------\
     *	  |  |	  \-------------------------------------------\		  |
     *	  |  \--------------------\			      |		  |
     *	  |			  |			      |		  |
     *	####################### ####################### #######################
     *	# MidiInputDeviceAlsa # # MidiInputDeviceVSTi # # MidiInputDeviceJack #
     *	####################### ####################### #######################
     *
     * As you can see in this example setup, one device (that is midi input
     * driver / audio output driver) can be connected multiple times to
     * different sampler channels.
     */
    class Sampler {
        public:
            /**
             * Constructor. Create a LinuxSampler instance.
             */
            Sampler();

            /**
             * Destructor.
             */
           ~Sampler();

            /**
             * Returns the number of sampler channels currently allocated.
             */
            uint SamplerChannels();

            /**
             * Create and add a new sampler channel to this Sampler instance.
             *
             * @returns  pointer to new sampler channel
             */
            SamplerChannel* AddSamplerChannel();

            /**
             * Returns the sampler channel of the given sampler channel
             * index.
             *
             * @returns  pointer to sought sampler channel
             */
            SamplerChannel* GetSamplerChannel(uint uiSamplerChannel);

            /**
             * Destroy and remove the given sampler channel from this
             * Sampler instance.
             *
             * @param pSamplerChannel - pointer to sampler channel to remove
             */
            void RemoveSamplerChannel(SamplerChannel* pSamplerChannel);

            /**
             * Destroy and remove the given sampler channel from this
             * Sampler instance.
             *
             * @param uiSamplerChannel - index of the sampler channel to
             *                           remove
             */
            void RemoveSamplerChannel(uint uiSamplerChannel);

            std::vector<String> AvailableAudioOutputDrivers();

            /**
             * Create an audio output device of the given type.
             *
             * @param AudioDriver - name of the audio driver
             * @param Parameters - eventually needed driver parameters to
             *                     create the device
             * @returns  pointer to created audio output device
             * @throws LinuxSamplerException  if device could not be created
             */
            AudioOutputDevice* CreateAudioOutputDevice(String AudioDriver, std::map<String,String> Parameters) throw (LinuxSamplerException);

            uint AudioOutputDevices();

            std::map<uint, AudioOutputDevice*> GetAudioOutputDevices();

            void DestroyAudioOutputDevice(AudioOutputDevice* pDevice) throw (LinuxSamplerException);

            /**
             * Create a MIDI input device of the given type.
             *
             * @param MidiType - desired MIDI input system to use
             * @returns  pointer to created MIDI input device
             */
            MidiInputDevice* CreateMidiInputDevice(MidiInputDevice::type_t MidiType); //TODO: to be changed to 'MidiInputDevice* CreateMidiInputDevice(String MidiDriver, std::map<String,String> Parameters) throw (LinuxSamplerException);'

            /**
             * Returns the MIDI input device of the given type.
             *
             * @param MidiType - desired MIDI input system to use
             * @returns  pointer to MIDI input device or NULL if device of
             *           desired type is not yet created
             */
            MidiInputDevice* GetMidiInputDevice(MidiInputDevice::type_t MidiType);

        protected:
            typedef std::map<uint, AudioOutputDevice*> AudioOutputDeviceMap;
            typedef std::map<MidiInputDevice::type_t, MidiInputDevice*> MidiInputDeviceMap;

            std::vector<SamplerChannel*> vSamplerChannels;   ///< contains all created sampler channels
            AudioOutputDeviceMap         mAudioOutputDevices; ///< contains all created audio output devices
            MidiInputDeviceMap           MidiInputDevices;

            template<class T> inline String ToString(T o) {
                std::stringstream ss;
                ss << o;
                return ss.str();
            }

            friend class SamplerChannel;
    };
}

#endif // __LS_SAMPLER_H__
