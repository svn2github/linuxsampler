/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003 by Benno Senoner and Christian Schoenebeck         *
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

namespace LinuxSampler {

    /**
     * Create Alsa MIDI input device for LinuxSampler. Opens and initializes
     * Alsa sequencer client and creates one Alsa MIDI input port for
     * LinuxSampler. The optional argument allows to auto connect to a Alsa
     * MIDI source (e.g. a software sequencer or a hardware MIDI input
     * port).
     *
     * @param AutoConnectPortID - (optional) Alsa client and port ID of a
     *                            MIDI source we should auto connect to
     *                            (e.g. "64:0")
     * @throws MidiInputException  if initialization failed
     */
    MidiInputDeviceAlsa::MidiInputDeviceAlsa(char* AutoConnectPortID) : Thread(true, 1, -1) {
        if (snd_seq_open(&hAlsaSeq, "default", SND_SEQ_OPEN_INPUT, 0) < 0) {
            throw MidiInputException("Error opening ALSA sequencer");
        }
        this->hAlsaSeqClient = snd_seq_client_id(hAlsaSeq);
        snd_seq_set_client_name(hAlsaSeq, "LinuxSampler");
        if ((this->hAlsaSeqPort = snd_seq_create_simple_port(hAlsaSeq, "LinuxSampler",
                                                             SND_SEQ_PORT_CAP_WRITE|SND_SEQ_PORT_CAP_SUBS_WRITE,
                                                             SND_SEQ_PORT_TYPE_APPLICATION)) < 0) {
            throw MidiInputException("Error creating sequencer port");
        }

        if (AutoConnectPortID) ConnectToAlsaMidiSource(AutoConnectPortID);
    }

    MidiInputDeviceAlsa::~MidiInputDeviceAlsa() {
        //TODO: close Alsa seq
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
    void MidiInputDeviceAlsa::ConnectToAlsaMidiSource(const char* MidiSource) {
        snd_seq_addr_t sender, dest;
        snd_seq_port_subscribe_t* subs;
        int hExtClient, hExtPort;

        sscanf(MidiSource, "%d:%d", &hExtClient, &hExtPort);
        sender.client = (char) hExtClient;
        sender.port   = (char) hExtPort;
        dest.client   = (char) this->hAlsaSeqClient;
        dest.port     = (char) this->hAlsaSeqPort;
        snd_seq_port_subscribe_alloca(&subs);
        snd_seq_port_subscribe_set_sender(subs, &sender);
        snd_seq_port_subscribe_set_dest(subs, &dest);
        snd_seq_port_subscribe_set_queue(subs, 1);
        snd_seq_port_subscribe_set_time_update(subs, 1);
        snd_seq_port_subscribe_set_time_real(subs, 1);
        if (snd_seq_subscribe_port(this->hAlsaSeq, subs) < 0)
            throw MidiInputException(String("Unable to connect to Alsa seq client \'") + MidiSource + "\' (" + snd_strerror(errno) + ")");
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
                    switch (ev->type) {
                        case SND_SEQ_EVENT_CONTROLLER:
                            DispatchControlChange(ev->data.control.param, ev->data.control.value, ev->data.control.channel);
                            break;

                        case SND_SEQ_EVENT_PITCHBEND:
                          //  fprintf(stderr, "Pitchbender event on Channel %2d: %5d   \n",
                          //          ev->data.control.channel, ev->data.control.value);
                            DispatchPitchbend(ev->data.control.value, ev->data.control.channel);
                            break;

                        case SND_SEQ_EVENT_NOTEON:
                            if (ev->data.note.velocity != 0) {
                                DispatchNoteOn(ev->data.note.note, ev->data.note.velocity, ev->data.control.channel);
                            }
                            else {
                                DispatchNoteOff(ev->data.note.note, 0, ev->data.control.channel);
                            }
                            break;

                        case SND_SEQ_EVENT_NOTEOFF:
                            DispatchNoteOff(ev->data.note.note, ev->data.note.velocity, ev->data.control.channel);
                            break;
                    }
                    snd_seq_free_event(ev);
                } while (snd_seq_event_input_pending(hAlsaSeq, 0) > 0);
            }
        }
    }

} // namespace LinuxSampler
