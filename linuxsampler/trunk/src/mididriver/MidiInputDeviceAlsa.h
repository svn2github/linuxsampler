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

#ifndef __LS_MIDIINPUTDEVICEALSA_H__
#define __LS_MIDIINPUTDEVICEALSA_H__

#include <alsa/asoundlib.h>

#include "../common/global.h"
#include "../common/Thread.h"
#include "../common/RingBuffer.h"
#include "MidiInputDevice.h"

namespace LinuxSampler {

    /** ALSA MIDI input driver
     *
     * Implements MIDI input for the Advanced Linux Sound Architecture
     * (ALSA).
     */
    class MidiInputDeviceAlsa : public MidiInputDevice, public Thread {
        public:
            MidiInputDeviceAlsa(char* AutoConnectPortID = NULL);
            ~MidiInputDeviceAlsa();

            // derived abstract methods from class 'NidiInputDevice'
            void Listen();
            void StopListen();

            // own methods
            void ConnectToAlsaMidiSource(const char* MidiSource);
        protected:
            int Main(); ///< Implementation of virtual method from class Thread
        private:
            snd_seq_t* hAlsaSeq;
            int        hAlsaSeqClient;       ///< Alsa Sequencer client ID
            int        hAlsaSeqPort;     ///< Alsa Sequencer client port number
    };
}

#endif // __LS_MIDIINPUTDEVICEALSA_H__
