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

#ifndef __AUDIOTHREAD_H__
#define __AUDIOTHREAD_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>

#include "global.h"
#include "thread.h"
#include "ringbuffer.h"
#include "voice.h"
#include "audioio.h"
#include "gig.h"

#define DEBUG			0
#define PITCHBEND_SEMITONES	12
#define MAX_AUDIO_VOICES	64

// preload 64k samples = 128kB of data in RAM for 16 bit mono samples
#define NUM_RAM_PRELOAD_SAMPLES 65536

class AudioThread : public Thread {
    public:
        AudioThread(AudioIO* pAudioIO, DiskThread* pDiskThread, gig::Instrument* pInstrument);
       ~AudioThread();
        void ProcessNoteOn(uint8_t Pitch, uint8_t Velocity);
        void ProcessNoteOff(uint8_t Pitch, uint8_t Velocity);
    protected:
        int Main(); ///< Implementation of virtual method from class Thread
    private:
        enum command_type_t {
            command_type_note_on,
            command_type_note_off
        };
        struct command_t {
            command_type_t type;
            uint8_t        pitch;
            uint8_t        velocity;
        } command;
        RingBuffer<command_t>* pCommandQueue;
        float*                 pAudioSumBuffer;    ///< Audio sum of all voices (32 bit)
        Voice**                pVoices;            ///< The voice pool, containing all Voices (active and inactice voices) in unsorted order
        Voice*                 ActiveVoices[128];  ///< Contains all active voices sorted by MIDI key number
        AudioIO*               pAudioIO;
        DiskThread*            pDiskThread;
        gig::Instrument*       pInstrument;

        void ActivateVoice(uint8_t MIDIKey, uint8_t Velocity);
        void ReleaseVoice(uint8_t MIDIKey, uint8_t Velocity);
        void CacheInitialSamples(gig::Sample* pSample);
};

#endif // __AUDIOTHREAD_H__
