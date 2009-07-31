/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2008 Andreas Persson                                    *
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
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,            *
 *   MA 02110-1301 USA.                                                    *
 ***************************************************************************/

#ifndef LS_MIDIINPUTDEVICEJACK_H
#define LS_MIDIINPUTDEVICEJACK_H

#include <jack/midiport.h>

#include "MidiInputDevice.h"

namespace LinuxSampler {

    class JackClient;

    /** JACK MIDI input driver
     *
     * Implements MIDI input for the JACK Audio Connection Kit (JACK).
     */
    class MidiInputDeviceJack : public MidiInputDevice {
        public:

            /**
             * MIDI Port implementation for the JACK MIDI input driver.
             */
            class MidiInputPortJack : public MidiInputPort {
                public:
                    /** MIDI Port Parameter 'NAME'
                     *
                     * Used to assign an arbitrary name to the MIDI port.
                     */
                    class ParameterName : public MidiInputPort::ParameterName {
                        public:
                            ParameterName(MidiInputPortJack* pPort) throw (Exception);
                            virtual void OnSetValue(String s) throw (Exception);
                        protected:
                            MidiInputPortJack* pPort;
                    };

                    /** MIDI Port Parameter 'JACK_BINDINGS'
                     *
                     * Used to connect to other JACK clients.
                     */
                    class ParameterJackBindings : public DeviceRuntimeParameterStrings {
                        public:
                            ParameterJackBindings(MidiInputPortJack* pPort);
                            virtual String              Description();
                            virtual bool                Fix();
                            virtual std::vector<String> PossibilitiesAsString();
                            virtual void                OnSetValue(std::vector<String> vS);
                            static String Name();
                        protected:
                            MidiInputPortJack*  pPort;
                            std::vector<String> Bindings;
                    };

                protected:
                    MidiInputPortJack(MidiInputDeviceJack* pDevice) throw (MidiInputException);
                    ~MidiInputPortJack();
                    friend class MidiInputDeviceJack;
                private:
                    MidiInputDeviceJack* pDevice;
                    jack_port_t*         hJackPort;
            };

            /** MIDI Device Parameter 'NAME'
             *
             * Used to assign an arbitrary name to the JACK client of this
             * MIDI device.
             */
            class ParameterName : public DeviceCreationParameterString {
                public:
                    ParameterName();
                    ParameterName(String s);
                    virtual String              Description();
                    virtual bool                Fix();
                    virtual bool                Mandatory();
                    virtual std::map<String,DeviceCreationParameter*> DependsAsParameters();
                    virtual std::vector<String> PossibilitiesAsString(std::map<String,String> Parameters);
                    virtual optional<String>    DefaultAsString(std::map<String,String> Parameters);
                    virtual void                OnSetValue(String s) throw (Exception);
                    static String Name();
            };

            MidiInputDeviceJack(std::map<String,DeviceCreationParameter*> Parameters, void* pSampler);
            ~MidiInputDeviceJack();

            // derived abstract methods from class 'MidiInputDevice'
            void Listen();
            void StopListen();
            String Driver();
            static String Name();
            static String Description();
            static String Version();

            MidiInputPortJack* CreateMidiPort();

            void Process(int nsamples);
        private:
            jack_client_t* hJackClient;
            JackClient*    pJackClient;
    };
}
#endif
