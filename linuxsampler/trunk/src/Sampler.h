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
#include "drivers/midi/MidiInputDevice.h"
#include "drivers/audio/AudioOutputDevice.h"

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
             * Connect this sampler channel to and MIDI input device.
             *
             * @param pDevice - MIDI input device to connect to
             */
            void SetMidiInputDevice(MidiInputDevice *pDevice);

            /**
             * Connect this sampler channel to and MIDI input port.
             *
             * @param MidiPort - MIDI port to connect to
             */
            void SetMidiInputPort(int MidiPort);

            /**
             * Connect this sampler channel to and MIDI input channel.
             *
             * @param MidiChannel - MIDI channel to connect to
             */
            void SetMidiInputChannel(MidiInputDevice::MidiInputPort::midi_chan_t MidiChannel);

            /**
             * Connect this sampler channel to a MIDI input triplet.
             *
             * @param pDevice - MIDI input device to connect to
             * @param MidiPort - MIDI port to connect to
             * @param MidiChannel - optional: MIDI channel on which the
             *                      sampler channel should listen to
             *                      (default: listen on all MIDI channels)
             */
            void SetMidiInput(MidiInputDevice* pDevice, int MidiPort, MidiInputDevice::MidiInputPort::midi_chan_t MidiChannel = MidiInputDevice::MidiInputPort::midi_chan_all);

            /**
             * Returns the engine that was deployed on this sampler channel.
             *
             * @returns  pointer to engine or NULL if no engine deployed
             */
            Engine* GetEngine();

            /**
             * Returns the MIDI input channel to which this sampler
             * channel is currently connected to.
             *
             * @returns  The MIDI input channel on which the sampler
             *           channel is listening to.
             */
            MidiInputDevice::MidiInputPort::midi_chan_t GetMidiInputChannel();

            /**
             * Returns the MIDI input port number to which this sampler
             * channel is currently connected to.
             *
             * @returns  MIDI input port number or -1 if not connected
             */
            int GetMidiInputPort();

            /**
             * Returns the audio output device to which this sampler channel
             * is currently connected to.
             *
             * @returns  pointer to audio output device or NULL if not
             *           connected
             */
            AudioOutputDevice* GetAudioOutputDevice();

            /**
             * Returns the MIDI input device to which this sampler channel
             * is currently connected to.
             *
             * @returns  pointer to MIDI input device or NULL if not
             *           connected
             */
            MidiInputDevice* GetMidiInputDevice();

            /**
             * Returns the index number of this sampler channel within the
             * Sampler instance.
             */
            uint Index();

        protected:
            SamplerChannel(Sampler* pS);
           ~SamplerChannel();

            /** Getting MIDI input device port given its index number. */
            MidiInputDevice::MidiInputPort* GetMidiInputDevicePort(int MidiPort);

            Sampler*           pSampler;
            Engine*            pEngine;
            AudioOutputDevice* pAudioOutputDevice;
            MidiInputDevice*   pMidiInputDevice;
            int                midiPort;
            MidiInputDevice::MidiInputPort::midi_chan_t midiChannel;
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
             * Create and add a new sampler channel to this Sampler
             * instance. For race condition reasons the new channel will use
             * an index past the last already existing sampler channel
             * index (in case the index limit was not reached yet, otherwise
             * a free index starting from 0 is searched).
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
             * Returns all created sampler channels.
             */
            std::map<uint, SamplerChannel*> GetSamplerChannels();

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

            /**
             * Returns the names of all available audio output drivers.
             */
            std::vector<String> AvailableAudioOutputDrivers();

            /**
             * Create an audio output device.
             *
             * @param AudioDriver - name of the audio driver
             * @param Parameters - eventually needed driver parameters to
             *                     create the device
             * @returns  pointer to created audio output device
             * @throws LinuxSamplerException  if device could not be created
             */
            AudioOutputDevice* CreateAudioOutputDevice(String AudioDriver, std::map<String,String> Parameters) throw (LinuxSamplerException);

            /**
             * Create a midi input device.
             *
             * @param MidiDriver - name of the midi driver
             * @param Parameters - eventually needed driver parameters to
             *                     create the device
             * @returns  pointer to created midi input device
             * @throws LinuxSamplerException  if device could not be created
             */
            MidiInputDevice* CreateMidiInputDevice(String MidiDriver, std::map<String,String> Parameters) throw (LinuxSamplerException);

            /**
             * Returns the number of all created audio output devices.
             */
            uint AudioOutputDevices();

            /**
             * Returns the number of all created MIDI input devices.
             */
            uint MidiInputDevices();

            /**
             * Returns all created audio output devices.
             */
            std::map<uint, AudioOutputDevice*> GetAudioOutputDevices();

            /**
             * Returns all created MIDI input devices.
             */
            std::map<uint, MidiInputDevice*> GetMidiInputDevices();

            /**
             * Destroy the given audio output device and takes care if there
             * are still sampler angines connected to this device, etc.
             *
             * @throws LinuxSamplerException  if sampler channels are still
             *                                connected to the device
             */
            void DestroyAudioOutputDevice(AudioOutputDevice* pDevice) throw (LinuxSamplerException);

            /**
             * Destroy the given MIDI input device and takes care if there
             * are still sampler angines connected to this device, etc.
             *
             * @throws LinuxSamplerException  if sampler channels are still
             *                                connected to the device
             */
            void DestroyMidiInputDevice(MidiInputDevice* pDevice) throw (LinuxSamplerException);

        protected:
            typedef std::map<uint, AudioOutputDevice*> AudioOutputDeviceMap;
            typedef std::map<uint, MidiInputDevice*> MidiInputDeviceMap;
            typedef std::map<uint, SamplerChannel*> SamplerChannelMap;

            SamplerChannelMap     mSamplerChannels;    ///< contains all created sampler channels
            AudioOutputDeviceMap  mAudioOutputDevices; ///< contains all created audio output devices
            MidiInputDeviceMap    mMidiInputDevices;   ///< contains all created MIDI input devices

            friend class SamplerChannel;
    };
}

#endif // __LS_SAMPLER_H__
