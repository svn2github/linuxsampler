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

#include <math.h>
#include <unistd.h>
#include <fcntl.h>

#include "global.h"
#include "thread.h"
#include "ringbuffer.h"
#include "audioio.h"
#include "voice.h"
#include "gig.h"
#include "rtelmemorypool.h"
#include "modulationsystem.h"

#define PITCHBEND_SEMITONES		12
#define MAX_AUDIO_VOICES		64
#define MAX_EVENTS_PER_FRAGMENT		1024

// preload 64k samples = 128kB of data in RAM for 16 bit mono samples
#define NUM_RAM_PRELOAD_SAMPLES 32768

// just symbol prototyping
class Voice;

//FIXME: Class name "AudioThread" is now misleading, because there is no thread anymore, but the name will change soon to "Engine" when we restructure the source tree
class AudioThread {
    public:
        double Volume;               ///< overall volume (a value < 1.0 means attenuation, a value > 1.0 means amplification)
        int    ActiveVoiceCount;     ///< number of currently active voices
        int    ActiveVoiceCountMax;  ///< the maximum voice usage since application start

        AudioThread(AudioIO* pAudioIO, DiskThread* pDiskThread, gig::Instrument* pInstrument);
       ~AudioThread();
        void          SendNoteOn(uint8_t Key, uint8_t Velocity);
        void          SendNoteOff(uint8_t Key, uint8_t Velocity);
        void          SendPitchbend(int Pitch);
        void          SendControlChange(uint8_t Controller, uint8_t Value);
        int           RenderAudio(uint Samples);
        inline float* GetAudioSumBuffer(uint Channel) {
            return pAudioSumBuffer[Channel];
        };
    protected:
        struct midi_key_info_t {
            RTEList<Voice>*                      pActiveVoices;         ///< Contains the active voices associated with the MIDI key.
            Voice*                               pSustainPtr;           ///< Points to the voice element in the active voice list which has not received a note-off yet (this pointer is needed for sustain pedal handling)
            bool                                 Sustained;             ///< Is true if the MIDI key is currently sustained, thus if Note-off arrived while sustain pedal pressed.
            bool                                 KeyPressed;            ///< Is true if the respective MIDI key is currently pressed.
            uint*                                pSustainPoolNode;      ///< FIXME: hack to allow fast deallocation of the key from the sustained key pool
        };

        RingBuffer<ModulationSystem::Event>*     pEventQueue;           ///< Input event queue.
        float*                                   pAudioSumBuffer[2];    ///< Audio sum of all voices (32 bit, index 0 = left channel, index 1 = right channel)
        midi_key_info_t                          pMIDIKeyInfo[128];     ///< Contains all active voices sorted by MIDI key number and other informations to the respective MIDI key
        /* ActiveVoicePool is a memory pool of limited size (size=MAX VOICES) of active voices.
           it can be allocated dynamically in real time and the allocated elements can be added to
           the linked lists represented by ActiveVoices[MIDIKey]. This means we can have unlimited
           active voices per key. This if for example useful to manage the sustain pedal messages
         */
        RTELMemoryPool<Voice>*                   pVoicePool;            ///< Contains all voices that can be activated.
        RTELMemoryPool<uint>*                    pSustainedKeyPool;     ///< Contains the MIDI key numbers of all currently sustained keys.
        RTELMemoryPool<ModulationSystem::Event>* pEventPool;            ///< Contains all Event objects that can be used.
        RTEList<ModulationSystem::Event>*        pEvents;               ///< All events for the current audio fragment.
        RTEList<ModulationSystem::Event>*        pCCEvents[ModulationSystem::destination_count];  ///< Control change events for the current audio fragment.
        AudioIO*                                 pAudioIO;
        DiskThread*                              pDiskThread;
        gig::Instrument*                         pInstrument;
        bool                                     SustainPedal;          ///< true if sustain pedal is down
        uint8_t                                  PrevHoldCCValue;
        int                                      Pitch;                 ///< Current (absolute) MIDI pitch value.

        void ProcessNoteOn(ModulationSystem::Event* pNoteOnEvent);
        void ProcessNoteOff(ModulationSystem::Event* pNoteOffEvent);
        void ProcessPitchbend(ModulationSystem::Event* pPitchbendEvent);
        void ProcessControlChange(ModulationSystem::Event* pControlChangeEvent);
        void KillVoice(Voice* pVoice);
        void CacheInitialSamples(gig::Sample* pSample);

        friend class Voice;
};

#endif // __AUDIOTHREAD_H__
