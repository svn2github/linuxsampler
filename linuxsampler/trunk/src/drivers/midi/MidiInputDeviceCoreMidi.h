/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2004, 2005 Grame                                        *
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

#ifndef __LS_MIDIINPUTDEVICECOREMIDI_H__
#define __LS_MIDIINPUTDEVICECOREMIDI_H__

#include <CoreMIDI/MIDIServices.h>

#include "../../common/global.h"
#include "MidiInputDevice.h"

namespace LinuxSampler {

    /** CoreMidi input driver
     *
     * Implements MIDI input for MacOSX CoreMidi architecture
     */
    class MidiInputDeviceCoreMidi : public MidiInputDevice {

		 public:
			/**
             * MIDI Port implementation for the CoreMidi input driver.
             */
            class MidiInputPortCoreMidi : public MidiInputPort {
                public:
                    /** MIDI Port Parameter 'NAME'
                     *
                     * Used to assign an arbitrary name to the MIDI port.
                     */
                    class ParameterName : public MidiInputPort::ParameterName {
                        public:
                            ParameterName(MidiInputPort* pPort) throw (LinuxSamplerException);
                            virtual void OnSetValue(String s) throw (LinuxSamplerException);
                    };

                    /** MIDI Port Parameter 'CORE_MIDI_BINDINGS'
                     *
                     * Used to connect to other Alsa sequencer clients.
                     */

                    class ParameterCoreMidiBindings : public DeviceRuntimeParameterStrings {
                        public:
                            ParameterCoreMidiBindings(MidiInputPortCoreMidi* pPort);
                            virtual String Description();
                            virtual bool Fix();
                            virtual std::vector<String> PossibilitiesAsString();
                            virtual void OnSetValue(std::vector<String> vS) throw (LinuxSamplerException);
                        protected:
                            MidiInputPortCoreMidi* pPort;
                    };

					static void ReadProc(const MIDIPacketList *pktlist, void *refCon, void *connRefCon);
					static int pPortID;

                protected:
                    MidiInputPortCoreMidi(MidiInputDeviceCoreMidi* pDevice) throw (MidiInputException);
                    ~MidiInputPortCoreMidi();
                    friend class MidiInputDeviceCoreMidi;
                private:
                    MidiInputPortCoreMidi* pDevice;
					MIDIEndpointRef pDestination;

                    friend class ParameterName;
                    friend class ParameterCoreMidiBindings;
            };

            MidiInputDeviceCoreMidi(std::map<String,DeviceCreationParameter*> Parameters, void* pSampler);
            virtual ~MidiInputDeviceCoreMidi();

            // derived abstract methods from class 'MidiInputDevice'
            void Listen(){}
            void StopListen(){}
			virtual String Driver();
			static String Name();
			static String Description();
            static String Version();

			MidiInputPortCoreMidi* CreateMidiPort();

			// CoreMidi callback
			static void NotifyProc(const MIDINotification* message, void* refCon);

        private:
			MIDIClientRef   hCoreMidiClient;
    };
}

#endif // __LS_MIDIINPUTDEVICECOREMIDI_H__
