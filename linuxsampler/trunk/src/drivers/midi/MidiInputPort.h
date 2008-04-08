/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
 *   Copyright (C) 2005 - 2008 Christian Schoenebeck                       *
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

#ifndef __LS_MIDIINPUTPORT_H__
#define __LS_MIDIINPUTPORT_H__

#include "../../common/global.h"
#include "../../common/Mutex.h"
#include "../../common/Exception.h"
#include "../DeviceParameter.h"
#include "midi.h"
#include "MidiInputDevice.h"
#include "../../engines/EngineChannel.h"
#include "../../common/SynchronizedConfig.h"

namespace LinuxSampler {

    // just symbol prototyping
    class MidiInputDevice;
    class EngineChannel;
    class VirtualMidiDevice;

    class MidiInputPort {
        public:

            /////////////////////////////////////////////////////////////////
            // type definitions

            /** MIDI Port Parameter 'NAME'
             *
             * Used to assign an arbitrary name to the MIDI port.
             */
            class ParameterName : public DeviceRuntimeParameterString {
                public:
                    ParameterName(MidiInputPort* pPort);
                    ParameterName(MidiInputPort* pPort, String val);
                    virtual String Description();
                    virtual bool   Fix();
                    virtual std::vector<String> PossibilitiesAsString();
                    virtual void OnSetValue(String s) throw (Exception);
                protected:
                    MidiInputPort* pPort;
            };



            /////////////////////////////////////////////////////////////////
            // normal methods
            //     (usually not to be overriden by descendant)

            /**
             * Connect given sampler engine channel with this MIDI input
             * device. The engine channel can either be connected to one
             * specific MIDI channel or all MIDI channels. If an engine
             * channel gets connected twice to this MIDI input device, then
             * the engine's old connection will be detached (no matter on
             * which MIDI channel).
             *
             * @param pEngineChannel - sampler engine
             * @param MidiChannel - MIDI channel to connect to
             * @throws MidiInputException  if MidiChannel argument invalid
             */
            void Connect(EngineChannel* pEngineChannel, midi_chan_t MidiChannel);

            /**
             * Disconnect given sampler engine channel from this MIDI input
             * device. If the given engine channel was not connected with
             * this device, nothing happens.
             *
             * @param pEngineChannel - sampler engine
             */
            void Disconnect(EngineChannel* pEngineChannel);

            /**
             * Return MIDI device where this MIDI port belongs to.
             */
            MidiInputDevice* GetDevice();

            /**
             * Return port number with which this MIDI port is registered to
             * the MIDI device.
             */
            uint GetPortNumber();

            /**
             * Return all parameter settings of this MIDI port.
             */
            std::map<String,DeviceRuntimeParameter*> PortParameters();

            /**
             * Registers that an engine wants to have sysex messages.
             */
            static void AddSysexListener(Engine* engine);

            /**
             * Removes engine from list of engines getting sysex
             * messages.
             *
             * @returns true if engine was removed, false if it wasn't
             *          present in the list.
             */
            static bool RemoveSysexListener(Engine* engine);

            /**
             * Connects the given virtual MIDI device to this MIDI input
             * device. This can be used to listen to MIDI data arriving on
             * the MIDI input device's MIDI ports, e.g. to show an MIDI
             * activity indicator somewhere.
             */
            void Connect(VirtualMidiDevice* pDevice);

            /**
             * Disconnect the previously connected virtual MIDI device.
             */
            void Disconnect(VirtualMidiDevice* pDevice);


            /////////////////////////////////////////////////////////////////
            // dispatch methods
            //     (should be called by the MidiInputDevice descendant on events)

            /**
             * Should be called by the implementing MIDI input device
             * whenever a note on event arrived, this will cause the note on
             * event to be forwarded to all connected engines on the
             * corresponding MIDI channel.
             *
             * This method is meant for realtime rendering, this way an event
             * is immediately created with the current system time as time
             * stamp.
             *
             * @param Key         - MIDI key number of the triggered key
             * @param Velocity    - MIDI velocity of the triggered key
             * @param MidiChannel - MIDI channel on which event occured on
             *                      (low level indexing, means 0..15)
             */
            void DispatchNoteOn(uint8_t Key, uint8_t Velocity, uint MidiChannel);

            /**
             * Should be called by the implementing MIDI input device
             * whenever a note on event arrived, this will cause the note on
             * event to be forwarded to all connected engines on the
             * corresponding MIDI channel.
             *
             * This method is meant for offline rendering and / or in case the
             * exact fragment position of the event is already known.
             *
             * @param Key         - MIDI key number of the triggered key
             * @param Velocity    - MIDI velocity of the triggered key
             * @param MidiChannel - MIDI channel on which event occured on
             *                      (low level indexing, means 0..15)
             * @param FragmentPos - event's sample point position in the
             *                      current audio fragment
             */
            void DispatchNoteOn(uint8_t Key, uint8_t Velocity, uint MidiChannel, int32_t FragmentPos);

            /**
             * Should be called by the implementing MIDI input device
             * whenever a note off event arrived, this will cause the note
             * off event to be forwarded to all connected engines on the
             * corresponding MIDI channel.
             *
             * This method is meant for realtime rendering, this way an event
             * is immediately created with the current system time as time
             * stamp.
             *
             * @param Key         - MIDI key number of the released key
             * @param Velocity    - MIDI velocity of the released key
             * @param MidiChannel - MIDI channel on which event occured on
             *                      (low level indexing, means 0..15)
             */
            void DispatchNoteOff(uint8_t Key, uint8_t Velocity, uint MidiChannel);

            /**
             * Should be called by the implementing MIDI input device
             * whenever a note off event arrived, this will cause the note
             * off event to be forwarded to all connected engines on the
             * corresponding MIDI channel.
             *
             * This method is meant for offline rendering and / or in case the
             * exact fragment position of the event is already known.
             *
             * @param Key         - MIDI key number of the released key
             * @param Velocity    - MIDI velocity of the released key
             * @param MidiChannel - MIDI channel on which event occured on
             *                      (low level indexing, means 0..15)
             * @param FragmentPos - event's sample point position in the
             *                      current audio fragment
             */
            void DispatchNoteOff(uint8_t Key, uint8_t Velocity, uint MidiChannel, int32_t FragmentPos);

            /**
             * Should be called by the implementing MIDI input device
             * whenever a pitchbend event arrived, this will cause the
             * pitchbend event to be forwarded to all connected engines.
             *
             * This method is meant for realtime rendering, this way an event
             * is immediately created with the current system time as time
             * stamp.
             *
             * @param Pitch       - MIDI pitch value
             * @param MidiChannel - MIDI channel on which event occured on
             *                      (low level indexing, means 0..15)
             */
            void DispatchPitchbend(int Pitch, uint MidiChannel);

            /**
             * Should be called by the implementing MIDI input device
             * whenever a pitchbend event arrived, this will cause the
             * pitchbend event to be forwarded to all connected engines.
             *
             * This method is meant for offline rendering and / or in case the
             * exact fragment position of the event is already known.
             *
             * @param Pitch       - MIDI pitch value
             * @param MidiChannel - MIDI channel on which event occured on
             *                      (low level indexing, means 0..15)
             * @param FragmentPos - event's sample point position in the
             *                      current audio fragment
             */
            void DispatchPitchbend(int Pitch, uint MidiChannel, int32_t FragmentPos);

            /**
             * Should be called by the implementing MIDI input device
             * whenever a control change event arrived, this will cause the
             * control change event to be forwarded to all engines on the
             * corresponding MIDI channel.
             *
             * This method is meant for realtime rendering, this way an event
             * is immediately created with the current system time as time
             * stamp.
             *
             * @param Controller  - MIDI controller number
             * @param Value       - MIDI control change value
             * @param MidiChannel - MIDI channel on which event occured on
             *                      (low level indexing, means 0..15)
             */
            void DispatchControlChange(uint8_t Controller, uint8_t Value, uint MidiChannel);

            /**
             * Should be called by the implementing MIDI input device
             * whenever a control change event arrived, this will cause the
             * control change event to be forwarded to all engines on the
             * corresponding MIDI channel.
             *
             * This method is meant for offline rendering and / or in case the
             * exact fragment position of the event is already known.
             *
             * @param Controller  - MIDI controller number
             * @param Value       - MIDI control change value
             * @param MidiChannel - MIDI channel on which event occured on
             *                      (low level indexing, means 0..15)
             * @param FragmentPos - event's sample point position in the
             *                      current audio fragment
             */
            void DispatchControlChange(uint8_t Controller, uint8_t Value, uint MidiChannel, int32_t FragmentPos);

            /**
             * Should be called by the implementing MIDI input device
             * whenever a program change event arrived. In case the
             * respective sampler channel(s) are enabled for MIDI
             * instrument mapping, the respective sampler engine and
             * instrument will be loaded on the connected sampler
             * channel(s) as defined by the respective entry in the
             * MIDI instrument map.
             *
             * @e Note: the MIDI instrument map is empty by default on
             * sampler startup. It has to be explicitly filled with
             * entries and the sampler channel(s) have to be enabled for
             * a certain MIDI instrument table, otherwise program change
             * messages are ignored!
             *
             * @param Program     - MIDI program change number
             * @param MidiChannel - MIDI channel on which this program
             *                      change occured
             * @see MidiInstrumentMapper
             */
            void DispatchProgramChange(uint8_t Program, uint MidiChannel);

            void DispatchBankSelectMsb(uint8_t BankMsb, uint MidiChannel);

            void DispatchBankSelectLsb(uint8_t BankLsb, uint MidiChannel);

            /**
             * Should be called by the implementing MIDI input device
             * whenever a system exclusive message arrived, this will cause
             * the message to be forwarded to all connected engines.
             *
             * @param pData - pointer to the sysex data
             * @param Size  - length of the sysex data (in bytes)
             */
            void DispatchSysex(void* pData, uint Size);

        protected:
            MidiInputDevice* pDevice;
            int portNumber;
            std::map<String,DeviceRuntimeParameter*> Parameters;  ///< All port parameters.
            typedef std::set<EngineChannel*> MidiChannelMap_t[17];
            SynchronizedConfig<MidiChannelMap_t> MidiChannelMap; ///< Contains the list of connected engines for each MIDI channel, where index 0 points to the list of engines which are connected to all MIDI channels. Usually it's not necessary for the descendant to use this map, instead it should just use the Dispatch* methods.
            SynchronizedConfig<MidiChannelMap_t>::Reader MidiChannelMapReader; ///< MIDI thread access to MidiChannelMap
            Mutex MidiChannelMapMutex; ///< Used to protect the MidiChannelMap from being used at the same time by different threads.
            SynchronizedConfig<std::set<Engine*> >::Reader SysexListenersReader; ///< MIDI thread access to SysexListeners
            SynchronizedConfig<std::vector<VirtualMidiDevice*> > virtualMidiDevices;
            SynchronizedConfig<std::vector<VirtualMidiDevice*> >::Reader virtualMidiDevicesReader;
            Mutex virtualMidiDevicesMutex;

            /**
             * Constructor
             */
            MidiInputPort(MidiInputDevice* pDevice, int portNumber);

            /**
             * Destructor
             */
            virtual ~MidiInputPort();

            friend class MidiInputDevice;

        private:
            static SynchronizedConfig<std::set<Engine*> > SysexListeners; ///< All engines that are listening to sysex messages.
    };

} // namsepace LinuxSampler

#endif // __LS_MIDIINPUTPORT_H__
