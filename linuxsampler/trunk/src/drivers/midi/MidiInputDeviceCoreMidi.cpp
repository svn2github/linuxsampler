/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2004, 2005 Grame                                        *
 *   Copyright (C) 2005 - 2009 Christian Schoenebeck                       *
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

#include "MidiInputDeviceCoreMidi.h"
#include "MidiInputDeviceFactory.h"

namespace LinuxSampler {

	int MidiInputDeviceCoreMidi::MidiInputPortCoreMidi::pPortID = 0;

	MidiInputDeviceCoreMidi::MidiInputPortCoreMidi::ParameterName::ParameterName(MidiInputPort* pPort) throw (Exception) : MidiInputPort::ParameterName(pPort, "Port " + ToString(pPort->GetPortNumber())) {
        OnSetValue(ValueAsString()); // initialize port name
    }

    void MidiInputDeviceCoreMidi::MidiInputPortCoreMidi::ParameterName::OnSetValue(String s) throw (Exception) {

    }

	// *************** ParameterCoreMidiBindings ***************
	// *

    MidiInputDeviceCoreMidi::MidiInputPortCoreMidi::ParameterCoreMidiBindings::ParameterCoreMidiBindings(MidiInputPortCoreMidi* pPort) : DeviceRuntimeParameterStrings( std::vector<String>() ) {
        this->pPort = pPort;
    }

    String MidiInputDeviceCoreMidi::MidiInputPortCoreMidi::ParameterCoreMidiBindings::Description() {
        return "Bindings to other CoreMidi clients";
    }
    bool MidiInputDeviceCoreMidi::MidiInputPortCoreMidi::ParameterCoreMidiBindings::Fix() {
        return false;
    }

    std::vector<String> MidiInputDeviceCoreMidi::MidiInputPortCoreMidi::ParameterCoreMidiBindings::PossibilitiesAsString() {
        std::vector<String> res;
		// Connections
		return res;
    }

    void MidiInputDeviceCoreMidi::MidiInputPortCoreMidi::ParameterCoreMidiBindings::OnSetValue(std::vector<String> vS) throw (Exception) {
        // to finish
    }


// *************** MidiInputPortCoreMidi ***************
// *

    MidiInputDeviceCoreMidi::MidiInputPortCoreMidi::MidiInputPortCoreMidi(MidiInputDeviceCoreMidi* pDevice) throw (MidiInputException) : MidiInputPort(pDevice, -1) {
    	// create CoreMidi virtual destination

	   /*  20080105 Toshi Nagata  */
		char buf[32];
		CFStringRef str;
		snprintf(buf, sizeof buf, "LinuxSampler_in_%d", pPortID);
		str = CFStringCreateWithCString(NULL, buf, kCFStringEncodingUTF8);
		MIDIDestinationCreate(pDevice->hCoreMidiClient, str, ReadProc, this, &pDestination);
		/*  */

		if (!pDestination) throw MidiInputException("Error creating CoreMidi virtual destination");
		this->portNumber = pPortID++;

        Parameters["NAME"]	= new ParameterName(this);
        Parameters["CORE_MIDI_BINDINGS"] = new ParameterCoreMidiBindings(this);
    }

    MidiInputDeviceCoreMidi::MidiInputPortCoreMidi::~MidiInputPortCoreMidi() {
		MIDIEndpointDispose(pDestination);
    }

	void MidiInputDeviceCoreMidi::MidiInputPortCoreMidi::ReadProc(const MIDIPacketList* pktlist, void* refCon, void* connRefCon)
	{
		MidiInputPortCoreMidi* port = (MidiInputPortCoreMidi*)refCon;
		MIDIPacket *packet = (MIDIPacket *)pktlist->packet;

		for (unsigned int i = 0; i < pktlist->numPackets; ++i) {

			// To be checked : several events per packet

			port->DispatchRaw(packet->data);

			packet = MIDIPacketNext(packet);
		}
	}


// *************** MidiInputDeviceCoreMidi ***************
// *

    MidiInputDeviceCoreMidi::MidiInputDeviceCoreMidi(std::map<String,DeviceCreationParameter*> Parameters, void* pSampler) : MidiInputDevice(Parameters, pSampler)
	{
		MIDIClientCreate(CFSTR("LinuxSampler"), NotifyProc, NULL, &hCoreMidiClient);
		if (!hCoreMidiClient) throw MidiInputException("Error opening CoreMidi client");
		AcquirePorts(((DeviceCreationParameterInt*)Parameters["PORTS"])->ValueAsInt());
	}

    MidiInputDeviceCoreMidi::~MidiInputDeviceCoreMidi()
	{
   		if (hCoreMidiClient) {
			MIDIClientDispose(hCoreMidiClient);
		}
    }

	MidiInputDeviceCoreMidi::MidiInputPortCoreMidi* MidiInputDeviceCoreMidi::CreateMidiPort() {
		return new MidiInputPortCoreMidi(this);
    }

	String MidiInputDeviceCoreMidi::Name() {
	    return "COREMIDI";
    }

	String MidiInputDeviceCoreMidi::Driver() {
	    return Name();
    }

	 String MidiInputDeviceCoreMidi::Description() {
	    return "Apple CoreMidi";
    }

    String MidiInputDeviceCoreMidi::Version() {
	    String s = "$Revision: 1.12 $";
	    return s.substr(11, s.size() - 13); // cut dollar signs, spaces and CVS macro keyword
    }

	void MidiInputDeviceCoreMidi::NotifyProc(const MIDINotification* message, void* refCon)
	{
		// to be finished
		if (message->messageID == kMIDIMsgSetupChanged) {
			printf("kMIDIMsgSetupChanged\n");
		}
	}


} // namespace LinuxSampler
