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

#ifndef __MIDIIN_H__
#define __MIDIIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <alsa/asoundlib.h>

#include "global.h"
#include "thread.h"
#include "audiothread.h"
#include "ringbuffer.h"

// Reflects the current values (0-127) of all MIDI controllers
extern uint8_t MIDIControllerTable[128];

class MidiIn : public Thread {
    public:
        int AlsaID;    ///< Alsa Sequencer client ID
        int AlsaPort;  ///< Alsa Sequencer client port number

        MidiIn(AudioThread* pAudioThread);
       ~MidiIn();
        void SubscribeToClient(const char* Client);
    protected:
        int  Main(); ///< Implementation of virtual method from class Thread
        int  open_alsa_midi_seq(void);
        void close_alsa_midi_seq(void);
    private:
        AudioThread* pAudioThread; ///< We will send Note On and Note Off messages to the audio thread
        snd_seq_t*   seq_handle;
};

#endif // __MIDIIN_H__
