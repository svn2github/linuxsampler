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
 *   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,                *
 *   MA  02110-1301  USA                                                   *
 ***************************************************************************/

#include "MidiInputDevicePlugin.h"

namespace LinuxSampler {

// *************** MidiInputPortPlugin ***************
// *

    MidiInputDevicePlugin::MidiInputPortPlugin::MidiInputPortPlugin(MidiInputDevicePlugin* pDevice) :
        MidiInputPort(pDevice, 0) {
    }



// *************** MidiInputDevicePlugin ***************
// *

    MidiInputDevicePlugin::MidiInputDevicePlugin(std::map<String, DeviceCreationParameter*> Parameters,
                                                 void* pSampler) :
        MidiInputDevice(Parameters, pSampler) {
        AcquirePorts(1);
    }

    MidiInputDevicePlugin::~MidiInputDevicePlugin() {
        for (std::map<int, MidiInputPort*>::iterator iter =
                 Ports.begin() ; iter != Ports.end() ; iter++) {
            delete dynamic_cast<MidiInputPortPlugin*>(iter->second);
        }
        Ports.clear();
    }

    void MidiInputDevicePlugin::Listen() {
    }

    void MidiInputDevicePlugin::StopListen() {
    }

    String MidiInputDevicePlugin::Driver() {
        return Name();
    }

    String MidiInputDevicePlugin::Name() {
        return "Plugin";
    }

    String MidiInputDevicePlugin::Version() {
        String s = "$Revision: 1.1 $";
        return s.substr(11, s.size() - 13); // cut dollar signs, spaces and CVS macro keyword
    }

    String MidiInputDevicePlugin::Description() {
        return Name();
    }

    MidiInputPort* MidiInputDevicePlugin::CreateMidiPort() {
        return new MidiInputPortPlugin(this);
    }
}
