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
    this->pAudioThread = pAudioThread;
    memset(MIDIControllerTable, 0x00, 128); // set all controller values to zero
}

MidiIn::~MidiIn() {
    close_alsa_midi_seq();
}

int MidiIn::open_alsa_midi_seq(void) {

    int portid;

    if (snd_seq_open(&seq_handle, "default", SND_SEQ_OPEN_INPUT, 0) < 0) {
        fprintf(stderr, "Error opening ALSA sequencer.\n");
        exit(1);
    }
    snd_seq_set_client_name(seq_handle, "LinuxSampler");
    if ((portid = snd_seq_create_simple_port(seq_handle, "LinuxSampler",
                                             SND_SEQ_PORT_CAP_WRITE|SND_SEQ_PORT_CAP_SUBS_WRITE,
                                             SND_SEQ_PORT_TYPE_APPLICATION)) < 0) {
        fprintf(stderr, "Error creating sequencer port.\n");
        exit(1);
    }
    return 0;
}

void MidiIn::close_alsa_midi_seq(void) {
}

int MidiIn::Main() {

    int res = open_alsa_midi_seq();
    if (res < 0) {
        fprintf(stderr,"opening of MIDI in device failed, exiting.\n");
        exit(1);
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
                        fprintf(stderr, "Control event on Channel %2d: %5d       \n",
                                ev->data.control.channel, ev->data.control.value);
                        break;

                    case SND_SEQ_EVENT_PITCHBEND:
                        fprintf(stderr, "Pitchbender event on Channel %2d: %5d   \n",
                                ev->data.control.channel, ev->data.control.value);
                        break;

                    case SND_SEQ_EVENT_NOTEON:
                        fprintf(stderr, "Note On event on Channel %2d: note=%5d velocity=%d      \n",
                                ev->data.control.channel, ev->data.note.note, ev->data.note.velocity);
                        if (ev->data.note.velocity != 0) {
                            pAudioThread->ProcessNoteOn(ev->data.note.note, ev->data.note.velocity);
                        }
                        else {
                            pAudioThread->ProcessNoteOff(ev->data.note.note, 0);
                        }
                        break;

                    case SND_SEQ_EVENT_NOTEOFF:
                        fprintf(stderr, "Note Off event on Channel %2d: note=%5d velocity=%d      \n",
                                ev->data.control.channel, ev->data.note.note, ev->data.note.velocity);
                        pAudioThread->ProcessNoteOff(ev->data.note.note, ev->data.note.velocity);
                        break;
                }
                snd_seq_free_event(ev);
            } while (snd_seq_event_input_pending(seq_handle, 0) > 0);
        } // end of if(poll...)
    }  // end of while
}
