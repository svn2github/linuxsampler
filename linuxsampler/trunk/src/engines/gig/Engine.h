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

#ifndef __LS_GIG_ENGINE_H__
#define __LS_GIG_ENGINE_H__

#include "../../common/global.h"

#if DEBUG_HEADERS
# warning Engine.h included
#endif // DEBUG_HEADERS

#include <map>

#include "../../common/RingBuffer.h"
#include "../../common/Pool.h"
#include "../../common/ConditionServer.h"
#include "../common/Engine.h"
#include "../common/Event.h"
#include "../common/BiquadFilter.h"
#include "../../lib/fileloader/libgig/gig.h"
#include "InstrumentResourceManager.h"
#include "../../network/lscp.h"

#define PITCHBEND_SEMITONES		12
#define MAX_AUDIO_VOICES		128
#define SYSEX_BUFFER_SIZE		2048  // 2kB
#define VOICE_STEAL_ALGORITHM		voice_steal_algo_oldestkey  ///< @see voice_steal_algo_t for available voice stealing algorithms

namespace LinuxSampler { namespace gig {

    using std::map;

    // just symbol prototyping
    class Voice;
    class DiskThread;
    class InstrumentResourceManager;

    /**
     * Sampler engine for the Gigasampler format.
     */
    class Engine : public LinuxSampler::Engine, public InstrumentConsumer {
        public:
            // types
            enum voice_steal_algo_t {
                voice_steal_algo_none,
                voice_steal_algo_keymask,
                voice_steal_algo_oldestkey
            };

            // methods
            Engine();
           ~Engine();

            // abstract methods derived from class 'LinuxSampler::Engine'
            virtual void   PrepareLoadInstrument(const char* FileName, uint Instrument);
            virtual void   LoadInstrument();
            virtual void   Reset();
            virtual void   Enable();
            virtual void   Disable();
            virtual void   SendNoteOn(uint8_t Key, uint8_t Velocity);
            virtual void   SendNoteOff(uint8_t Key, uint8_t Velocity);
            virtual void   SendPitchbend(int Pitch);
            virtual void   SendControlChange(uint8_t Controller, uint8_t Value);
            virtual void   SendSysex(void* pData, uint Size);
            virtual float  Volume();
            virtual void   Volume(float f);
            virtual uint   Channels();
            virtual void   Connect(AudioOutputDevice* pAudioOut);
            virtual void   DisconnectAudioOutputDevice();
            virtual void   SetOutputChannel(uint EngineAudioChannel, uint AudioDeviceChannel);
            virtual int    OutputChannel(uint EngineAudioChannel);
            virtual int    RenderAudio(uint Samples);
            virtual uint   VoiceCount();
            virtual uint   VoiceCountMax();
            virtual bool   DiskStreamSupported();
            virtual uint   DiskStreamCount();
            virtual uint   DiskStreamCountMax();
            virtual String DiskStreamBufferFillBytes();
            virtual String DiskStreamBufferFillPercentage();
            virtual String Description();
            virtual String Version();
            virtual String EngineName();
            virtual String InstrumentFileName();
            virtual String InstrumentName();
            virtual int    InstrumentIndex();
            virtual int    InstrumentStatus();

            // abstract methods derived from interface class 'InstrumentConsumer'
            virtual void ResourceToBeUpdated(::gig::Instrument* pResource, void*& pUpdateArg);
            virtual void ResourceUpdated(::gig::Instrument* pOldResource, ::gig::Instrument* pNewResource, void* pUpdateArg);
        //protected:
            struct midi_key_info_t {
                RTList<Voice>*  pActiveVoices;  ///< Contains the active voices associated with the MIDI key.
                bool            KeyPressed;     ///< Is true if the respective MIDI key is currently pressed.
                bool            Active;         ///< If the key contains active voices.
                bool            ReleaseTrigger; ///< If we have to launch release triggered voice(s) when the key is released
                Pool<uint>::Iterator itSelf;         ///< hack to allow fast deallocation of the key from the list of active keys
                RTList<Event>*  pEvents;        ///< Key specific events (only Note-on, Note-off and sustain pedal currently)
            };

            static InstrumentResourceManager Instruments;

            AudioOutputDevice*      pAudioOutputDevice;
            float*                  pOutputLeft;           ///< Audio output channel buffer (left)
            float*                  pOutputRight;          ///< Audio output channel buffer (right)
            int                     AudioDeviceChannelLeft;  ///< audio device channel number to which the left channel is connected to
            int                     AudioDeviceChannelRight; ///< audio device channel number to which the right channel is connected to
            uint                    SampleRate;            ///< Sample rate of the engines output audio signal (in Hz)
            uint                    MaxSamplesPerCycle;    ///< Size of each audio output buffer
            DiskThread*             pDiskThread;
            uint8_t                 ControllerTable[128];  ///< Reflects the current values (0-127) of all MIDI controllers for this engine / sampler channel.
            RingBuffer<Event>*      pEventQueue;           ///< Input event queue.
            RingBuffer<uint8_t>*    pSysexBuffer;          ///< Input buffer for MIDI system exclusive messages.
            midi_key_info_t         pMIDIKeyInfo[128];     ///< Contains all active voices sorted by MIDI key number and other informations to the respective MIDI key
            Pool<Voice>*            pVoicePool;            ///< Contains all voices that can be activated.
            Pool<uint>*             pActiveKeys;           ///< Holds all keys in it's allocation list with active voices.
            Pool<Event>*            pEventPool;            ///< Contains all Event objects that can be used.
            EventGenerator*         pEventGenerator;
            RTList<Event>*          pVoiceStealingQueue;   ///< All voice-launching events which had to be postponed due to free voice shortage.
            RTList<Event>*          pEvents;               ///< All events for the current audio fragment.
            RTList<Event>*          pCCEvents;             ///< All control change events for the current audio fragment.
            RTList<Event>*          pSynthesisEvents[Event::destination_count];     ///< Events directly affecting synthesis parameter (like pitch, volume and filter).
            float*                  pSynthesisParameters[Event::destination_count]; ///< Matrix with final synthesis parameters for the current audio fragment which will be used in the main synthesis loop.
            biquad_param_t*         pBasicFilterParameters; ///< Biquad parameters of the basic bandpass filter.
            biquad_param_t*         pMainFilterParameters;  ///< Main biquad parameters of the individual filter (lowpass / bandpass / highpass).
            map<uint,uint*>         ActiveKeyGroups;        ///< Contains active keys (in case they belong to a key group) ordered by key group ID.
            RIFF::File*             pRIFF;
            ::gig::File*            pGig;
            ::gig::Instrument*      pInstrument;
            bool                    SustainPedal;          ///< true if sustain pedal is down
            double                  GlobalVolume;          ///< overall volume (a value < 1.0 means attenuation, a value > 1.0 means amplification)
            int                     Pitch;                 ///< Current (absolute) MIDI pitch value.
            int                     CurrentKeyDimension;   ///< Current value (0-127) for the keyboard dimension, altered by pressing a keyswitching key.
            int                     ActiveVoiceCount;      ///< number of currently active voices
            int                     ActiveVoiceCountMax;   ///< the maximum voice usage since application start
            bool                    SuspensionRequested;
            ConditionServer         EngineDisabled;
	    String                  InstrumentFile;
	    int                     InstrumentIdx;
	    String                  InstrumentIdxName;
	    int                     InstrumentStat;
            int8_t                  ScaleTuning[12];       ///< contains optional detune factors (-64..+63 cents) for all 12 semitones of an octave
            RTList<Voice>::Iterator itLastStolenVoice;      ///< Only for voice stealing: points to the last voice which was theft in current audio fragment, NULL otherwise.
            RTList<uint>::Iterator  iuiLastStolenKey;      ///< Only for voice stealing: key number of last key on which the last voice was theft in current audio fragment, NULL otherwise.
            int                     MaxFadeOutPos;         ///< The last position in an audio fragment to allow a instant fade out (e.g. for voice stealing) without leading to clicks.

            void ProcessNoteOn(Pool<Event>::Iterator& itNoteOnEvent);
            void ProcessNoteOff(Pool<Event>::Iterator& itNoteOffEvent);
            void ProcessPitchbend(Pool<Event>::Iterator& itPitchbendEvent);
            void ProcessControlChange(Pool<Event>::Iterator& itControlChangeEvent);
            void ProcessSysex(Pool<Event>::Iterator& itSysexEvent);
            Pool<Voice>::Iterator LaunchVoice(Pool<Event>::Iterator& itNoteOnEvent, int iLayer, bool ReleaseTriggerVoice, bool VoiceStealing);
            void StealVoice(Pool<Event>::Iterator& itNoteOnEvent);
            void FreeVoice(Pool<Voice>::Iterator& itVoice);
            void FreeKey(midi_key_info_t* pKey);
            void ResetSynthesisParameters(Event::destination_t dst, float val);
            void ResetInternal();

            friend class Voice;
            friend class EGADSR;
            friend class EGDecay;
            friend class VCAManipulator;
            friend class VCFCManipulator;
            friend class VCOManipulator;
            friend class InstrumentResourceManager;
        private:
            void    DisableAndLock();
            uint8_t GSCheckSum(const RingBuffer<uint8_t>::NonVolatileReader AddrReader, uint DataSize);
            void    AdjustScale(int8_t ScaleTunes[12]);
    };

}} // namespace LinuxSampler::gig

#endif // __LS_GIG_ENGINE_H__
