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

#include "rtelmemorypool.h"

#define DEBUG			0
#define PITCHBEND_SEMITONES	12
#define MAX_AUDIO_VOICES	64

// preload 64k samples = 128kB of data in RAM for 16 bit mono samples
#define NUM_RAM_PRELOAD_SAMPLES 32768

class AudioThread : public Thread {
    public:
        AudioThread(AudioIO* pAudioIO, DiskThread* pDiskThread, gig::Instrument* pInstrument);
       ~AudioThread();
        void ProcessNoteOn(uint8_t Pitch, uint8_t Velocity);
        void ProcessNoteOff(uint8_t Pitch, uint8_t Velocity);
        void ProcessContinuousController(uint8_t Channel, uint8_t Number, uint8_t Value);

        // the number of currently active streams
        // printed on the console the main thread (along with the active streams count)
        int ActiveVoiceCount;

    protected:
        int Main(); ///< Implementation of virtual method from class Thread
    private:
        enum command_type_t {
            command_type_note_on,
            command_type_note_off,
            command_type_continuous_controller
        };
        struct command_t {
            command_type_t type;
            uint8_t        channel;
            uint8_t        pitch;
            uint8_t        velocity;
            uint8_t        number;
            uint8_t        value;
        } command;
        RingBuffer<command_t>* pCommandQueue;
        float*                 pAudioSumBuffer;    ///< Audio sum of all voices (32 bit)
        Voice**                pVoices;            ///< The voice pool, containing all Voices (active and inactice voices) in unsorted order

        RTEList<Voice *> *pActiveVoices[128];  ///< Contains all active voices sorted by MIDI key number
        /* ActiveVoicePool is a memory pool of limited size (size=MAX VOICES) of active voices.
           it can be allocated dynamically in real time and the allocated elements can be added to
           the linked lists represented by ActiveVoices[MIDIKey]. This means we can have unlimited
           active voices per key. This if for example useful to manage the sustain pedal messages
         */
        RTELMemoryPool<Voice *> *ActiveVoicePool; 
        /* SustainedVoicePool is a dynamically allocated pool (size=MAX VOICES) and list of notes
           notes that were sustained and where the corresponding MIDI note-off arrived
           but cannot processed yet. Basically when the sustain pedal is pressed and the
           note-off on a certain midi key arrives. notes are not deleted from the
           ActiveVoices[MIDIKey] list but an element is added in the SustainedVoicePool,
           which is a dynamically allocated pool with a builtin list.
           Then the pedal is finally released, this list is traversed and all elements
           in the lists ActiveVoices[MIDIKey] ( where MIDIKey is contained in the list of
           sustained voices) are processed (voices are released)
        */
 
        typedef struct {
                         int midikey;
                         int velocity;
                       } sustained_key_t;
 
        RTELMemoryPool<sustained_key_t> *SustainedKeyPool;

        uint8_t PrevHoldCCValue;
        // SustainPedal = 1 if the sustain pedal is down, otherwise it is 0
        uint8_t SustainPedal;



        AudioIO*               pAudioIO;
        DiskThread*            pDiskThread;
        gig::Instrument*       pInstrument;

        void ActivateVoice(uint8_t MIDIKey, uint8_t Velocity);
        void ReleaseVoice(uint8_t MIDIKey, uint8_t Velocity);
        void ContinuousController(uint8_t Channel, uint8_t Number, uint8_t Value);
       
        void CacheInitialSamples(gig::Sample* pSample);
};

#endif // __AUDIOTHREAD_H__
