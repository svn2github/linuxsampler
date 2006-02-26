/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
 *   Copyright (C) 2005 Christian Schoenebeck                              *
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
#include "../../common/LinuxSamplerException.h"
#include "../DeviceParameter.h"
#include "midi.h"
#include "MidiInputDevice.h"
#include "../../engines/common/EngineChannel.h"
#include "../../common/SynchronizedConfig.h"

namespace LinuxSampler {

    // just symbol prototyping
    class MidiInputDevice;
    class EngineChannel;

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
                    virtual void OnSetValue(String s) throw (LinuxSamplerException);
                protected:
                    MidiInputPort* pPort;
            };



            /////////////////////////////////////////////////////////////////
            // normal methods
            //     (usually not to be overriden by descendant)

            /**
             * Connect given sampler engine with this MIDI input device.
             * The engine can either be connected to one specific MIDI
             * channel or all MIDI channels. If an engine gets connected
             * twice to this MIDI input device, then the engine's old
             * connection will be detached (no matter on which MIDI channel).
             *
             * @param pEngine     - sampler engine
             * @param MidiChannel - MIDI channel to connect to
             * @throws MidiInputException  if MidiChannel argument invalid
             */
            void Connect(EngineChannel* pEngineChannel, midi_chan_t MidiChannel);

            /**
             * Disconnect given sampler engine from this MIDI input device.
             * If the given engine was not connected with this device,
             * nothing happens.
             *
             * @param pEngine - sampler engine
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





            /////////////////////////////////////////////////////////////////
            // dispatch methods
            //     (should be called by the MidiInputDevice descendant on events)

            /**
             * Should be called by the implementing MIDI input device
             * whenever a note on event arrived, this will cause the note on
             * event to be forwarded to all connected engines on the
             * corresponding MIDI channel.
             *
             * @param Key         - MIDI key number of the triggered key
             * @param Velocity    - MIDI velocity of the triggered key
             * @param MidiChannel - MIDI channel on which event occured on
             *                      (low level indexing, means 0..15)
             */
            void DispatchNoteOn(uint8_t Key, uint8_t Velocity, uint MidiChannel);

            /**
             * Should be called by the implementing MIDI input device
             * whenever a note off event arrived, this will cause the note
             * off event to be forwarded to all connected engines on the
             * corresponding MIDI channel.
             *
             * @param Key         - MIDI key number of the released key
             * @param Velocity    - MIDI velocity of the released key
             * @param MidiChannel - MIDI channel on which event occured on
             *                      (low level indexing, means 0..15)
             */
            void DispatchNoteOff(uint8_t Key, uint8_t Velocity, uint MidiChannel);

            /**
             * Should be called by the implementing MIDI input device
             * whenever a pitchbend event arrived, this will cause the
             * pitchbend event to be forwarded to all connected engines.
             *
             * @param Pitch       - MIDI pitch value
             * @param MidiChannel - MIDI channel on which event occured on
             *                      (low level indexing, means 0..15)
             */
            void DispatchPitchbend(int Pitch, uint MidiChannel);

            /**
             * Should be called by the implementing MIDI input device
             * whenever a control change event arrived, this will cause the
             * control change event to be forwarded to all engines on the
             * corresponding MIDI channel.
             *
             * @param Controller  - MIDI controller number
             * @param Value       - MIDI control change value
             * @param MidiChannel - MIDI channel on which event occured on
             *                      (low level indexing, means 0..15)
             */
            void DispatchControlChange(uint8_t Controller, uint8_t Value, uint MidiChannel);

            /**
             * Should be called by the implementing MIDI input device
             * whenever a program change event arrived, this will cause the
             * appropriate sampler channel to be connected with this MIDI
             * device.
             *
             * For example consider a program change event on MIDI channel
             * 3 for program number 18. This would cause this MIDI input
             * device to be connected to sampler channel 18 and would cause
             * sampler channel 18 to listen to MIDI channel 3.
             *
             * This is the current, general implementation of program
             * change events. It might change in future, e.g to allow
             * sampler engines to allow by themselfes how to act on a
             * program change event.
             *
             * @param Program     - sampler channel to connect to this MIDI
             *                      input device
             * @param MidiChannel - MIDI channel on which sampler channel
             *                      \a Program should listen to
             */
            void DispatchProgramChange(uint8_t Program, uint MidiChannel);

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
            Mutex MidiChannelMapMutex; ///< Used to protect the MidiChannelMap from being used at the same time by different threads.

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
            EngineChannel* pPreviousProgramChangeEngineChannel; ///< Points to the engine channel which was connected by the previous DispatchProgramChange() call.
    };

} // namsepace LinuxSampler

#endif // __LS_MIDIINPUTPORT_H__
