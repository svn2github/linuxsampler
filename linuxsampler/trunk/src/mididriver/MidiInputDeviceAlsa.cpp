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

#include "MidiInputDeviceAlsa.h"
#include "MidiInputDeviceFactory.h"

namespace LinuxSampler {

	REGISTER_MIDI_INPUT_DRIVER("Alsa",MidiInputDeviceAlsa);

    MidiInputDeviceAlsa::MidiInputDeviceAlsa(std::map<String,String> Parameters) : MidiInputDevice(CreateParameters(Parameters)), Thread(true, 1, -1) {
        if (snd_seq_open(&hAlsaSeq, "default", SND_SEQ_OPEN_INPUT, 0) < 0) {
            throw MidiInputException("Error opening ALSA sequencer");
        }
        this->hAlsaSeqClient = snd_seq_client_id(hAlsaSeq);
        snd_seq_set_client_name(hAlsaSeq, "LinuxSampler");
    }

    MidiInputDeviceAlsa::~MidiInputDeviceAlsa() {
	    snd_seq_close(hAlsaSeq);
    }

    MidiInputDeviceAlsa::MidiInputPortAlsa::MidiInputPortAlsa(MidiInputDeviceAlsa* pDevice, int alsaPort) : MidiInputPort(pDevice, alsaPort) {
	    this->pDevice = pDevice;
	    Parameters = MidiInputDevice::MidiInputPort::AvailableParameters();
	    Parameters["alsa_seq_bindings"] = new ParameterAlsaSeqBindings(this);
    }

    MidiInputDeviceAlsa::MidiInputPortAlsa::~MidiInputPortAlsa() {
	    snd_seq_delete_simple_port(pDevice->hAlsaSeq, portNumber);
    }

    MidiInputDeviceAlsa::MidiInputPortAlsa* MidiInputDeviceAlsa::CreateMidiPort() {
	    int alsaPort;
	    if ((alsaPort = snd_seq_create_simple_port(hAlsaSeq, "LinuxSampler",
					    SND_SEQ_PORT_CAP_WRITE|SND_SEQ_PORT_CAP_SUBS_WRITE,
					    SND_SEQ_PORT_TYPE_APPLICATION)) < 0) {
		    throw MidiInputException("Error creating sequencer port");
	    }
	    return ( new MidiInputPortAlsa(this, alsaPort) );
    }

    void MidiInputDeviceAlsa::Listen() {
        StartThread();
    }

    void MidiInputDeviceAlsa::StopListen() {
        StopThread();
    }

    /**
    * Connects this Alsa midi input device with an Alsa MIDI source.
    *
    * @param Client - Alsa sequencer client and port ID of a MIDI source
    *                (e.g. "64:0")
    * @throws MidiInputException  if connection cannot be established
    */
    void MidiInputDeviceAlsa::MidiInputPortAlsa::ConnectToAlsaMidiSource(const char* MidiSource) {
        snd_seq_addr_t sender, dest;
        snd_seq_port_subscribe_t* subs;
        int hExtClient, hExtPort;

        sscanf(MidiSource, "%d:%d", &hExtClient, &hExtPort);
        sender.client = (char) hExtClient;
        sender.port   = (char) hExtPort;
        dest.client   = (char) pDevice->hAlsaSeqClient;
        dest.port     = (char) portNumber;
        snd_seq_port_subscribe_alloca(&subs);
        snd_seq_port_subscribe_set_sender(subs, &sender);
        snd_seq_port_subscribe_set_dest(subs, &dest);
        snd_seq_port_subscribe_set_queue(subs, 1);
        snd_seq_port_subscribe_set_time_update(subs, 1);
        snd_seq_port_subscribe_set_time_real(subs, 1);
        if (snd_seq_subscribe_port(pDevice->hAlsaSeq, subs) < 0)
            throw MidiInputException(String("Unable to connect to Alsa seq client \'") + MidiSource + "\' (" + snd_strerror(errno) + ")");
    }

    String MidiInputDeviceAlsa::Description() {
	    return "Advanced Linux Sound Architecture";
    }

    String MidiInputDeviceAlsa::Version() {
	    String s = "$Revision: 1.5 $";
	    return s.substr(11, s.size() - 13); // cut dollar signs, spaces and CVS macro keyword
    }

    std::map<String,DeviceCreationParameter*> MidiInputDeviceAlsa::CreateParameters(std::map<String,String> Parameters) {
	     std::map<String,DeviceCreationParameter*> result;
	     result["active"] = OptionalParameter<ParameterActive>::New(this, Parameters["active"]);
	     result["ports"] = OptionalParameter<ParameterPorts>::New(this, Parameters["ports"]);
	     return result;
    }

    int MidiInputDeviceAlsa::Main() {
        int npfd;
        struct pollfd* pfd;
        snd_seq_event_t* ev;

        npfd = snd_seq_poll_descriptors_count(hAlsaSeq, POLLIN);
        pfd = (struct pollfd*) alloca(npfd * sizeof(struct pollfd));
        snd_seq_poll_descriptors(hAlsaSeq, pfd, npfd, POLLIN);
        while (true) {
            if (poll(pfd, npfd, 100000) > 0) {
                do {
                    snd_seq_event_input(hAlsaSeq, &ev);
		    int port = (int) ev->dest.port;
		    MidiInputPort* pMidiInputPort = Ports[port];

                    switch (ev->type) {
                        case SND_SEQ_EVENT_CONTROLLER:
                            pMidiInputPort->DispatchControlChange(ev->data.control.param, ev->data.control.value, ev->data.control.channel);
                            break;

                        case SND_SEQ_EVENT_PITCHBEND:
                          //  fprintf(stderr, "Pitchbender event on Channel %2d: %5d   \n",
                          //          ev->data.control.channel, ev->data.control.value);
                            pMidiInputPort->DispatchPitchbend(ev->data.control.value, ev->data.control.channel);
                            break;

                        case SND_SEQ_EVENT_NOTEON:
                            if (ev->data.note.velocity != 0) {
                                pMidiInputPort->DispatchNoteOn(ev->data.note.note, ev->data.note.velocity, ev->data.control.channel);
                            }
                            else {
                                pMidiInputPort->DispatchNoteOff(ev->data.note.note, 0, ev->data.control.channel);
                            }
                            break;

                        case SND_SEQ_EVENT_NOTEOFF:
                            pMidiInputPort->DispatchNoteOff(ev->data.note.note, ev->data.note.velocity, ev->data.control.channel);
                            break;
                    }
                    snd_seq_free_event(ev);
                } while (snd_seq_event_input_pending(hAlsaSeq, 0) > 0);
            }
        }
    }

} // namespace LinuxSampler
