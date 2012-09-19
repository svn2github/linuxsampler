/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2004, 2005 Grame                                        *
 *   Copyright (C) 2005 - 2012 Christian Schoenebeck                       *
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
	
// *************** privat static functions ***************
// *
	
	static void _bridgeInputEvent(const MIDIPacketList* packetList, void* /*device*/, void* port) {
		//MidiInputDeviceCoreMidi* pDevice = (MidiInputDeviceCoreMidi*) device;
		MidiInputDeviceCoreMidi::MidiInputPortCoreMidi* pPort = (MidiInputDeviceCoreMidi::MidiInputPortCoreMidi*) port;
		pPort->ProcessMidiEvents(packetList);
	}
	
	static String _getDisplayName(MIDIObjectRef object) {
		CFStringRef name = nil;
		if (MIDIObjectGetStringProperty(object, kMIDIPropertyDisplayName, &name) != noErr) {
			dmsg(1,("CoreMIDI: could not resolve display name of object\n"));
			return "";
		}
		// convert NSString to C string
		char* buf = new char[256];
		if (!CFStringGetCString(name, buf, 256, kCFStringEncodingUTF8)) {
			dmsg(1,("CoreMIDI: could not convert display name string\n"));
			delete buf;
			return "";
		}
		String result = buf;
		delete buf;
		return result;
	}
	
	
// *************** ParameterName ***************
// *

	MidiInputDeviceCoreMidi::MidiInputPortCoreMidi::ParameterName::ParameterName(MidiInputPort* pPort) throw (Exception) : MidiInputPort::ParameterName(pPort, "Port " + ToString(pPort->GetPortNumber())) {
        OnSetValue(ValueAsString()); // initialize port name
    }

    void MidiInputDeviceCoreMidi::MidiInputPortCoreMidi::ParameterName::OnSetValue(String s) throw (Exception) {
		//TODO: renaming of port to be implemented
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
		
		const ItemCount sourceCount = MIDIGetNumberOfSources();
		for (ItemCount i = 0; i < sourceCount; ++i) {
			MIDIEndpointRef source = MIDIGetSource(i);
			res.push_back(
				_getDisplayName(source)
			);
		}
		
		return res;
    }

    void MidiInputDeviceCoreMidi::MidiInputPortCoreMidi::ParameterCoreMidiBindings::OnSetValue(std::vector<String> vS) throw (Exception) {
        for (int k = 0; k < vS.size(); ++k) {
			const ItemCount sourceCount = MIDIGetNumberOfSources();
			for (ItemCount i = 0; i < sourceCount; ++i) {
				MIDIEndpointRef source = MIDIGetSource(i);
				String name = _getDisplayName(source);
				if (name == vS[k]) {
					pPort->connectToSource(source);
					goto matchFound;
				}
			}
			throw MidiInputException("No CoreMIDI source '" + vS[k] + "' found to connect to");
			matchFound:
			; // noop
		}
    }
	
// *************** ParameterAutoBind ***************
// *
	
	MidiInputDeviceCoreMidi::MidiInputPortCoreMidi::ParameterAutoBind::ParameterAutoBind(MidiInputPortCoreMidi* pPort)
		: DeviceRuntimeParameterBool(false)
	{
		this->pPort = pPort;
	}
	
	String MidiInputDeviceCoreMidi::MidiInputPortCoreMidi::ParameterAutoBind::Description() {
		return "Whether port shall automatically be connected to all CoreMIDI source endpoints.";
	}
	
	bool MidiInputDeviceCoreMidi::MidiInputPortCoreMidi::ParameterAutoBind::Fix() {
		return false;
	}
	
	void MidiInputDeviceCoreMidi::MidiInputPortCoreMidi::ParameterAutoBind::OnSetValue(bool b) throw (Exception) {
		if (b) pPort->connectToAllSources();
	}


// *************** MidiInputPortCoreMidi ***************
// *
	
	int MidiInputDeviceCoreMidi::MidiInputPortCoreMidi::pPortID = 0;

    MidiInputDeviceCoreMidi::MidiInputPortCoreMidi::MidiInputPortCoreMidi(MidiInputDeviceCoreMidi* pDevice) throw (MidiInputException) : MidiInputPort(pDevice, -1) {
		this->pDevice = pDevice;
		
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
		Parameters["AUTO_BIND"] = new ParameterAutoBind(this);
    }

    MidiInputDeviceCoreMidi::MidiInputPortCoreMidi::~MidiInputPortCoreMidi() {
		MIDIEndpointDispose(pDestination);
    }

	void MidiInputDeviceCoreMidi::MidiInputPortCoreMidi::ReadProc(const MIDIPacketList* pktlist, void* refCon, void* connRefCon)
	{
		MidiInputPortCoreMidi* port = (MidiInputPortCoreMidi*)refCon;
		port->ProcessMidiEvents(pktlist);
	}
	
	void MidiInputDeviceCoreMidi::MidiInputPortCoreMidi::ProcessMidiEvents(const MIDIPacketList *pktlist) {
		MIDIPacket *packet = (MIDIPacket *)pktlist->packet;
		for (unsigned int i = 0; i < pktlist->numPackets; ++i) {
			//TODO: To be checked : several events per packet ?
			DispatchRaw(packet->data);
			packet = MIDIPacketNext(packet);
		}
	}
	
	void MidiInputDeviceCoreMidi::MidiInputPortCoreMidi::connectToSource(MIDIEndpointRef source) {
		// check if we already have such a connection, if yes, disconnect it first
		for (uint i = 0; i < bindings.size(); ++i) {
			if (bindings[i] == source) {
				MIDIPortDisconnectSource(pDevice->pBridge, source);
				break;
			}
		}
		// now establish the CoreMIDI connection
		MIDIPortConnectSource(pDevice->pBridge, source, this);
		// and remember it
		bindings.push_back(source);
	}
	
	void MidiInputDeviceCoreMidi::MidiInputPortCoreMidi::connectToAllSources() {
		const ItemCount sourceCount = MIDIGetNumberOfSources();
		for (ItemCount i = 0; i < sourceCount; ++i) {
			MIDIEndpointRef source = MIDIGetSource(i);
			connectToSource(source);
			dmsg(1,("Auto binded to CoreMIDI source '%s'\n", _getDisplayName(source).c_str()));
		}
	}
	
	void MidiInputDeviceCoreMidi::MidiInputPortCoreMidi::onNewSourceAppeared(MIDIEndpointRef source) {
		if (((ParameterAutoBind*)Parameters["AUTO_BIND"])->ValueAsBool()) {
			connectToSource(source);
			dmsg(1,("Auto binded to new CoreMIDI source '%s'\n", _getDisplayName(source).c_str()));
		}
	}
	
	void MidiInputDeviceCoreMidi::MidiInputPortCoreMidi::onNewSourceDisappeared(MIDIEndpointRef source) {
		//TODO: remove source from 'bindings' list eventually
	}


// *************** MidiInputDeviceCoreMidi ***************
// *

    MidiInputDeviceCoreMidi::MidiInputDeviceCoreMidi(std::map<String,DeviceCreationParameter*> Parameters, void* pSampler) : MidiInputDevice(Parameters, pSampler)
	{
		MIDIClientCreate(CFSTR("LinuxSampler"), NotifyProc, this, &hCoreMidiClient);
		if (!hCoreMidiClient) throw MidiInputException("Error opening CoreMidi client");
		
		OSStatus status = MIDIInputPortCreate(hCoreMidiClient, CFSTR("bridge"), _bridgeInputEvent, this, &pBridge);
		if (status != noErr) throw MidiInputException("Could not create bridge port for CoreMIDI client");
							
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
		MidiInputDeviceCoreMidi* pDevice = (MidiInputDeviceCoreMidi*) refCon;
		
		switch (message->messageID) {
			case kMIDIMsgObjectAdded: {
				MIDIObjectAddRemoveNotification* notification = (MIDIObjectAddRemoveNotification*) message;
				if (notification->childType == kMIDIObjectType_Source) {
					for (std::map<int,MidiInputPort*>::iterator iter = pDevice->Ports.begin();
						 iter != pDevice->Ports.end(); ++iter)
					{
						MidiInputPortCoreMidi* pPort = (MidiInputPortCoreMidi*) iter->second;
						MIDIEndpointRef source = (MIDIEndpointRef) notification->child;
						pPort->onNewSourceAppeared(source);
					}
				}
				break;
			}
				
			case kMIDIMsgObjectRemoved: {
				MIDIObjectAddRemoveNotification* notification = (MIDIObjectAddRemoveNotification*) message;
				if (notification->childType == kMIDIObjectType_Source) {
					for (std::map<int,MidiInputPort*>::iterator iter = pDevice->Ports.begin();
						 iter != pDevice->Ports.end(); ++iter)
					{
						MidiInputPortCoreMidi* pPort = (MidiInputPortCoreMidi*) iter->second;
						MIDIEndpointRef source = (MIDIEndpointRef) notification->child;
						pPort->onNewSourceDisappeared(source);
					}
				}
				break;
			}
				
			case kMIDIMsgSetupChanged:
			case kMIDIMsgPropertyChanged:
			case kMIDIMsgThruConnectionsChanged:
			case kMIDIMsgSerialPortOwnerChanged:
			case kMIDIMsgIOError:
				break;
		}
	}

} // namespace LinuxSampler
