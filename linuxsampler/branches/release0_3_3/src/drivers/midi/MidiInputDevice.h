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

#ifndef __LS_MIDIINPUTDEVICE_H__
#define __LS_MIDIINPUTDEVICE_H__

#include <stdexcept>
#include <set>
#include <map>
#include <vector>

#include "../../common/global.h"
#include "../../common/LinuxSamplerException.h"
#include "../DeviceParameter.h"
#include "MidiInputPort.h"
#include "../../engines/common/Engine.h"

namespace LinuxSampler {

    // just symbol prototyping
    class MidiInputPort;
    class Engine;

    /**
     * Midi input exception that should be thrown by the MidiInputDevice
     * descendants in case initialization of the MIDI input system failed
     * (which should be done in the constructor of the MidiInputDevice
     * descendant).
     */
    class MidiInputException : public LinuxSamplerException {
        public:
            MidiInputException(const std::string& msg) : LinuxSamplerException(msg) {}
    };

    /** Abstract base class for MIDI input drivers in LinuxSampler
     *
     * This class will be derived by specialized classes which implement the
     * connection to a specific MIDI input system (e.g. Alsa Sequencer,
     * CoreMIDI). The MidiInputDevice desendant should just call the
     * appropriate (protected) Dispatch* method here when an MIDI event
     * occured. The dispatch* methods here will automatically forward the
     * MIDI event to the appropriate, connected sampler engines.
     */
    class MidiInputDevice : public Device {
        public:

            /////////////////////////////////////////////////////////////////
            // type definitions

            /** Device Parameter 'ACTIVE'
             *
             * Used to activate / deactivate the MIDI input device.
             */
            class ParameterActive : public DeviceCreationParameterBool {
                public:
                    ParameterActive();
                    ParameterActive(String active);
                    virtual String Description();
                    virtual bool   Fix();
                    virtual bool   Mandatory();
                    virtual std::map<String,DeviceCreationParameter*> DependsAsParameters();
                    virtual optional<bool> DefaultAsBool(std::map<String,String> Parameters);
                    virtual void OnSetValue(bool b) throw (LinuxSamplerException);
                    static String Name();
            };

            /** Device Parameter 'PORTS'
             *
             * Used to increase / decrease the number of MIDI ports of the
             * MIDI input device.
             */
            class ParameterPorts : public DeviceCreationParameterInt {
                public:
                    ParameterPorts();
                    ParameterPorts(String val);
                    virtual String Description();
                    virtual bool   Fix();
                    virtual bool   Mandatory();
                    virtual std::map<String,DeviceCreationParameter*> DependsAsParameters();
                    virtual optional<int>    DefaultAsInt(std::map<String,String> Parameters);
                    virtual optional<int>    RangeMinAsInt(std::map<String,String> Parameters);
                    virtual optional<int>    RangeMaxAsInt(std::map<String,String> Parameters);
                    virtual std::vector<int> PossibilitiesAsInt(std::map<String,String> Parameters);
                    virtual void             OnSetValue(int i) throw (LinuxSamplerException);
                    static String Name();
            };



            /////////////////////////////////////////////////////////////////
            // abstract methods
            //     (these have to be implemented by the descendant)

            /**
             * Start listen to MIDI input events on the MIDI input port.
             * The MIDIInputPort descendant should forward all MIDI input
             * events by calling the appropriate (protected) Dispatch*
             * method of class MidiInputPort.
             */
            virtual void Listen() = 0;

            /**
             * Stop to listen to MIDI input events on the MIDI input port.
             * After this method was called, the MidiInputPort descendant
             * should ignore all MIDI input events.
             */
            virtual void StopListen() = 0;

            /**
             * Return device driver name
             */
            virtual String Driver() = 0;

            /**
             * Create new Midi port
             * This will be called by AcquirePorts
             * Each individual device must implement this.
             */
            virtual MidiInputPort* CreateMidiPort() = 0;



            /////////////////////////////////////////////////////////////////
            // normal methods
            //     (usually not to be overriden by descendant)

            /**
             * Return midi port \a iPort.
             *
             * @throws MidiInputException  if index out of bounds
             */
            MidiInputPort* GetPort(uint iPort) throw (MidiInputException);

            /**
             * Return all device parameter settings.
             */
            std::map<String,DeviceCreationParameter*> DeviceParameters();

        protected:
            std::map<String,DeviceCreationParameter*> Parameters;  ///< All device parameters.
            std::map<int,MidiInputPort*> Ports;                    ///< All MIDI ports.
            void* pSampler;                                        ///< Sampler instance. FIXME: should actually be of type Sampler*

            /**
             * Constructor
             *
             * FIXME: the pointer argument \a pSapmler should actually be of type Sampler*.
             * Unfortunately the bidirectional relationship between this
             * header and Sampler.h would clash on header file inclusion,
             * so that's why I had to make it of type void* here. This is
             * an annoying constraint of C++.
             */
            MidiInputDevice(std::map<String,DeviceCreationParameter*> DriverParameters, void* pSampler);

            /**
             * Destructor
             */
            virtual ~MidiInputDevice();

            /**
             * Set number of MIDI ports required by the engine
             * This can either do nothing, create more ports
             * or destroy ports depenging on the parameter
             * and how many ports already exist on this driver.
             *
             * @param Ports - number of ports to be left on this driver after this call.
             */
            void AcquirePorts(uint Ports);

            friend class ParameterActive;
            friend class ParameterPorts;
            friend class Sampler; // allow Sampler class to destroy midi devices
            friend class MidiInputPort; // allow MidiInputPort to access pSampler
    };
}

#endif // __LS_MIDIINPUTDEVICE_H__
