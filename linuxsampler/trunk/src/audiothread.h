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
#include <pthread.h>
#include <sstream>

#include "global.h"
#include "thread.h"
#include "ringbuffer.h"
#include "audioio.h"
#include "voice.h"
#include "gig.h"
#include "rtelmemorypool.h"
#include "modulationsystem.h"
#include "network/lscp.h"

#define PITCHBEND_SEMITONES		12
#define MAX_AUDIO_VOICES		64

// preload 64k samples = 128kB of data in RAM for 16 bit mono samples
#define NUM_RAM_PRELOAD_SAMPLES 32768

// just symbol prototyping
class Voice;

//FIXME: Class name "AudioThread" is now misleading, because there is no thread anymore, but the name will change soon to "Engine" when we restructure the source tree
class AudioThread {
    public:
        double       Volume;               ///< overall volume (a value < 1.0 means attenuation, a value > 1.0 means amplification)
        int          ActiveVoiceCount;     ///< number of currently active voices
        int          ActiveVoiceCountMax;  ///< the maximum voice usage since application start
        DiskThread*  pDiskThread;

        AudioThread(AudioIO* pAudioIO);
       ~AudioThread();
        result_t      LoadInstrument(const char* FileName, uint Instrument);
        void          Reset();
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
            bool                                 KeyPressed;            ///< Is true if the respective MIDI key is currently pressed.
            bool                                 Active;                ///< If the key contains active voices.
            uint*                                pSelf;                 ///< hack to allow fast deallocation of the key from the list of active keys
            RTEList<ModulationSystem::Event>*    pEvents;               ///< Key specific events (only Note-on, Note-off and sustain pedal currently)
        };

        RingBuffer<ModulationSystem::Event>*     pEventQueue;           ///< Input event queue.
        float*                                   pAudioSumBuffer[2];    ///< Audio sum of all voices (32 bit, index 0 = left channel, index 1 = right channel)
        midi_key_info_t                          pMIDIKeyInfo[128];     ///< Contains all active voices sorted by MIDI key number and other informations to the respective MIDI key
        RTELMemoryPool<Voice>*                   pVoicePool;            ///< Contains all voices that can be activated.
        RTELMemoryPool<uint>*                    pActiveKeys;           ///< Holds all keys in it's allocation list with active voices.
        RTELMemoryPool<ModulationSystem::Event>* pEventPool;            ///< Contains all Event objects that can be used.
        RTEList<ModulationSystem::Event>*        pEvents;               ///< All events for the current audio fragment.
        RTEList<ModulationSystem::Event>*        pCCEvents[ModulationSystem::destination_count];  ///< Control change events for the current audio fragment.
        AudioIO*                                 pAudioIO;
        RIFF::File*                              pRIFF;
        gig::File*                               pGig;
        gig::Instrument*                         pInstrument;
        bool                                     SustainPedal;          ///< true if sustain pedal is down
        uint8_t                                  PrevHoldCCValue;
        int                                      Pitch;                 ///< Current (absolute) MIDI pitch value.
        bool                                     SuspensionRequested;
        pthread_mutex_t                          __render_state_mutex;
        pthread_cond_t                           __render_exit_condition;

        void ProcessNoteOn(ModulationSystem::Event* pNoteOnEvent);
        void ProcessNoteOff(ModulationSystem::Event* pNoteOffEvent);
        void ProcessPitchbend(ModulationSystem::Event* pPitchbendEvent);
        void ProcessControlChange(ModulationSystem::Event* pControlChangeEvent);
        void KillVoice(Voice* pVoice);
        void CacheInitialSamples(gig::Sample* pSample);
        void ResetInternal();

        friend class Voice;
};

#endif // __AUDIOTHREAD_H__
