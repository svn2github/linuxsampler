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

#define PITCHBEND_SEMITONES	12
#define MAX_AUDIO_VOICES	64

// preload 64k samples = 128kB of data in RAM for 16 bit mono samples
#define NUM_RAM_PRELOAD_SAMPLES 32768

class AudioThread : public Thread {
    public:
        int ActiveVoiceCount;     ///< number of currently active voices
        int ActiveVoiceCountMax;  ///< the maximum voice usage since application start

        AudioThread(AudioIO* pAudioIO, DiskThread* pDiskThread, gig::Instrument* pInstrument);
       ~AudioThread();
        void SendNoteOn(uint8_t Pitch, uint8_t Velocity);
        void SendNoteOff(uint8_t Pitch, uint8_t Velocity);
        void SendControlChange(uint8_t Channel, uint8_t Number, uint8_t Value);
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
        struct midi_key_info_t {
            RTEList<Voice*>*             pActiveVoices;      ///< Contains the active voices associated with the MIDI key.
            RTEList<Voice*>::NodeHandle  hSustainPtr;        ///< Points to the voice element in the active voice list which has not received a note-off yet (this pointer is needed for sustain pedal handling)
            bool                         Sustained;          ///< Is true if the MIDI key is currently sustained, thus if Note-off arrived while sustain pedal pressed.
            bool                         KeyPressed;         ///< Is true if the respective MIDI key is currently pressed.
            uint*                        pSustainPoolNode;   ///< FIXME: hack to allow fast deallocation of the key from the sustained key pool
        };

        RingBuffer<command_t>*           pCommandQueue;
        float*                           pAudioSumBuffer;    ///< Audio sum of all voices (32 bit)
        Voice**                          pVoices;            ///< The voice pool, containing all Voices (active and inactice voices) in unsorted order
        midi_key_info_t                  pMIDIKeyInfo[128];  ///< Contains all active voices sorted by MIDI key number and other informations to the respective MIDI key
        /* ActiveVoicePool is a memory pool of limited size (size=MAX VOICES) of active voices.
           it can be allocated dynamically in real time and the allocated elements can be added to
           the linked lists represented by ActiveVoices[MIDIKey]. This means we can have unlimited
           active voices per key. This if for example useful to manage the sustain pedal messages
         */
        RTELMemoryPool<Voice*>*          ActiveVoicePool;
        RTELMemoryPool<uint>*            SustainedKeyPool;   ///< Contains the MIDI key numbers of all currently sustained keys.
        AudioIO*                         pAudioIO;
        DiskThread*                      pDiskThread;
        gig::Instrument*                 pInstrument;
        bool                             SustainPedal;       ///< true if sustain pedal is down
        uint8_t                          PrevHoldCCValue;

        void ProcessNoteOn(uint8_t MIDIKey, uint8_t Velocity);
        void ProcessNoteOff(uint8_t MIDIKey, uint8_t Velocity);
        void ProcessControlChange(uint8_t Channel, uint8_t Number, uint8_t Value);
        void ReleaseVoice(Voice* pVoice);
        void CacheInitialSamples(gig::Sample* pSample);
};

#endif // __AUDIOTHREAD_H__
