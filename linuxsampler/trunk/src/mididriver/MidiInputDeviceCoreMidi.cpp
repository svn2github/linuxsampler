/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
 *   Copyright (C) 2004 Grame											   *
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

namespace LinuxSampler {

    MidiInputDeviceCoreMidi::MidiInputDeviceCoreMidi(char* AutoConnectPortID) : MidiInputDevice(MidiInputDevice::type_core_midi) 
	{
		OSStatus err;
	
		err = MIDIClientCreate(CFSTR("LinuxSampler"), NotifyProc, NULL, &hCoreMidiClient);
		if (!hCoreMidiClient) {
			fprintf(stderr, "Can not open CoreMidi client\n");
			goto error;
		}
		
		err = MIDIInputPortCreate(hCoreMidiClient, CFSTR("Input port"), ReadProc, this, &hCoreMidiInPort);
		if (!hCoreMidiInPort) {
			fprintf(stderr, "Can not open Midi in por\n");
			goto error;
		}
		
		if (AutoConnectPortID) ConnectToCoreMidiSource(AutoConnectPortID);
		
		// for test : to be improved
		ConnectToCoreMidiSource(NULL);
		return;
		
	error :
		if (hCoreMidiInPort){
			 MIDIPortDispose(hCoreMidiInPort);
		}
		
		if (hCoreMidiClient) {
			MIDIClientDispose(hCoreMidiClient);
		}
		
		throw MidiInputException("Error opening CoreMidi device");
    }

    void MidiInputDeviceCoreMidi::SetInputPort(const char * MidiSource) 
	{
	    ConnectToCoreMidiSource(MidiSource);
    }

    MidiInputDeviceCoreMidi::~MidiInputDeviceCoreMidi() 
	{
        if (hCoreMidiInPort){
			 MIDIPortDispose(hCoreMidiInPort);
		}
		
		if (hCoreMidiClient) {
			MIDIClientDispose(hCoreMidiClient);
		}
    }

	void MidiInputDeviceCoreMidi::ConnectToCoreMidiSource(const char* MidiSource)
	{
		// Open connections from all sources : to be improved
		int n = MIDIGetNumberOfSources();
		for (int i = 0; i < n; ++i) {
			MIDIEndpointRef src = MIDIGetSource(i);
			MIDIPortConnectSource(hCoreMidiInPort, src, NULL);
		}
	}
	
	void MidiInputDeviceCoreMidi::NotifyProc(const MIDINotification *message, void *refCon)
	{
		if (message->messageID == kMIDIMsgSetupChanged) {
			printf("kMIDIMsgSetupChanged\n");
		}
	}
	
	void MidiInputDeviceCoreMidi::ReadProc(const MIDIPacketList *pktlist, void *refCon, void *connRefCon)
	{
		MidiInputDeviceCoreMidi* driver = (MidiInputDeviceCoreMidi*)refCon;
		MIDIPacket *packet = (MIDIPacket *)pktlist->packet;	
	
		for (int i = 0; i < pktlist->numPackets; ++i) {
		
			int cin = packet->data[0] & 0xF0;
			
			// To be checked : several events per packet
		
			switch(cin) { // status byte
			
				case 0xB0:
					driver->DispatchControlChange(packet->data[1],packet->data[2],packet->data[0]&0x0F);
					break;
					
				case 0xE0:
					driver->DispatchPitchbend(packet->data[1],packet->data[0]&0x0F);
					break;

				case 0x90:
					if (packet->data[1] < 128)
						driver->DispatchNoteOn(packet->data[1],packet->data[2], packet->data[0]&0x0F);
					break;
				
				case 0x80:
					if (packet->data[1] < 128)
						driver->DispatchNoteOff(packet->data[1],packet->data[2],packet->data[0]&0x0F);
					break;
			}
			
			packet = MIDIPacketNext(packet);
		}
	}


} // namespace LinuxSampler
