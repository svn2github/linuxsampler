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

#include "midiin.h"

MidiIn::MidiIn(AudioThread* pAudioThread) : Thread(true, 1, -1) {
    this->seq_handle   = NULL;
    this->pAudioThread = pAudioThread;
    memset(MIDIControllerTable, 0x00, 128); // set all controller values to zero
}

MidiIn::~MidiIn() {
    close_alsa_midi_seq();
}

int MidiIn::open_alsa_midi_seq(void) {
    if (snd_seq_open(&seq_handle, "default", SND_SEQ_OPEN_INPUT, 0) < 0) {
        fprintf(stderr, "Error opening ALSA sequencer.\n");
        exit(1);
    }
    this->AlsaID = snd_seq_client_id(seq_handle);
    snd_seq_set_client_name(seq_handle, "LinuxSampler");
    if ((this->AlsaPort = snd_seq_create_simple_port(seq_handle, "LinuxSampler",
                                                     SND_SEQ_PORT_CAP_WRITE|SND_SEQ_PORT_CAP_SUBS_WRITE,
                                                     SND_SEQ_PORT_TYPE_APPLICATION)) < 0) {
        fprintf(stderr, "Error creating sequencer port.\n");
        exit(1);
    }
    return 0;
}

void MidiIn::close_alsa_midi_seq(void) {
}

/**
 * Makes a connection to another Alsa sequencer client, so that all MIDI
 * events from e.g. a keyboard are always delivered to us.
 *
 * @param Client - Alsa sequencer client ID and port string to connect to
 *                (e.g. "64:0")
 */
void MidiIn::SubscribeToClient(const char* Client) {
    if (!this->seq_handle) {  // if we haven't registered our seq client yet
        int res = open_alsa_midi_seq();
        if (res < 0) {
            fprintf(stderr,"Opening of MIDI in device failed, exiting.\n");
            exit(EXIT_FAILURE);
        }
    }

    snd_seq_addr_t sender, dest;
    snd_seq_port_subscribe_t* subs;
    int extClientID, extPortID;

    sscanf(Client, "%d:%d", &extClientID, &extPortID);
    sender.client = (char) extClientID;
    sender.port   = (char) extPortID;
    dest.client   = (char) this->AlsaID;
    dest.port     = (char) this->AlsaPort;
    snd_seq_port_subscribe_alloca(&subs);
    snd_seq_port_subscribe_set_sender(subs, &sender);
    snd_seq_port_subscribe_set_dest(subs, &dest);
    snd_seq_port_subscribe_set_queue(subs, 1);
    snd_seq_port_subscribe_set_time_update(subs, 1);
    snd_seq_port_subscribe_set_time_real(subs, 1);
    if (snd_seq_subscribe_port(this->seq_handle, subs) < 0) {
        fprintf(stderr, "Unable to subscribe to client \'%s\' (%s)\n", Client, snd_strerror(errno));
    }
}

int MidiIn::Main() {
    if (!this->seq_handle) {  // if we haven't registered our seq client yet
        int res = open_alsa_midi_seq();
        if (res < 0) {
            fprintf(stderr,"Opening of MIDI in device failed, exiting.\n");
            exit(EXIT_FAILURE);
        }
    }

    int npfd;
    struct pollfd *pfd;
    snd_seq_event_t *ev;

    npfd = snd_seq_poll_descriptors_count(seq_handle, POLLIN);
    pfd = (struct pollfd *)alloca(npfd * sizeof(struct pollfd));
    snd_seq_poll_descriptors(seq_handle, pfd, npfd, POLLIN);
    while (true) {
        if (poll(pfd, npfd, 100000) > 0) {
            do {
                snd_seq_event_input(seq_handle, &ev);
                switch (ev->type) {
                    case SND_SEQ_EVENT_CONTROLLER:
                        pAudioThread->SendControlChange(ev->data.control.param, ev->data.control.value);
                        break;

                    case SND_SEQ_EVENT_PITCHBEND:
                      //  fprintf(stderr, "Pitchbender event on Channel %2d: %5d   \n",
                      //          ev->data.control.channel, ev->data.control.value);
                        pAudioThread->SendPitchbend(ev->data.control.value);
                        break;

                    case SND_SEQ_EVENT_NOTEON:
                        if (ev->data.note.velocity != 0) {
                            pAudioThread->SendNoteOn(ev->data.note.note, ev->data.note.velocity);
                        }
                        else {
                            pAudioThread->SendNoteOff(ev->data.note.note, 0);
                        }
                        break;

                    case SND_SEQ_EVENT_NOTEOFF:
                        pAudioThread->SendNoteOff(ev->data.note.note, ev->data.note.velocity);
                        break;
                }
                snd_seq_free_event(ev);
            } while (snd_seq_event_input_pending(seq_handle, 0) > 0);
        }
    }
}

