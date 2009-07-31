/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003,2004 by Benno Senoner and Christian Schoenebeck    *
 *   Copyright (C) 2005-2009 Christian Schoenebeck                         *
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

#include <map>
#include <gig.h>

#include "EngineGlobals.h"
#include "../../common/RingBuffer.h"
#include "../../common/Pool.h"
#include "../../common/ArrayList.h"
#include "../../common/Condition.h"
#include "../../common/ConditionServer.h"
#include "../../common/atomic.h"
#include "../Engine.h"
#include "../common/Event.h"
#include "../../network/lscp.h"
#include "EngineChannel.h"

// identifier of this sampler engine
#define LS_GIG_ENGINE_NAME "GIG"

namespace LinuxSampler { namespace gig {

    // just symbol prototyping
    class Voice;
    class DiskThread;
    class InstrumentResourceManager;
    class midi_key_info_t;
    class EngineChannel;

    /**
     * Sampler engine for the Gigasampler format.
     */
    class Engine : public LinuxSampler::Engine {
        public:
            // methods
            Engine();
            virtual ~Engine();
            void Connect(AudioOutputDevice* pAudioOut);
            void SuspendAll();
            void ResumeAll();
            void Suspend(::gig::Region* pRegion);
            void Resume(::gig::Region* pRegion);

            // implementation of abstract methods derived from class 'LinuxSampler::Engine'
            virtual int    RenderAudio(uint Samples);
            virtual void   SendSysex(void* pData, uint Size, MidiInputPort* pSender);
            virtual void   Reset();
            virtual void   Enable();
            virtual void   Disable();
            virtual uint   VoiceCount();
            virtual uint   VoiceCountMax();
            virtual int    MaxVoices();
            virtual void   SetMaxVoices(int iVoices) throw (Exception);
            virtual bool   DiskStreamSupported();
            virtual uint   DiskStreamCount();
            virtual uint   DiskStreamCountMax();
            virtual int    MaxDiskStreams();
            virtual void   SetMaxDiskStreams(int iStreams) throw (Exception);
            virtual String DiskStreamBufferFillBytes();
            virtual String DiskStreamBufferFillPercentage();
            virtual String Description();
            virtual String Version();
            virtual String EngineName();
            virtual InstrumentManager* GetInstrumentManager();

            void SetVoiceCount(uint Count);

            // Simple array wrapper just to make sure memory is freed
            // when liblinuxsampler is unloaded
            class FloatTable {
            private:
                const float* array;
            public:
                FloatTable(const float* array) : array(array) { }
                ~FloatTable() { delete[] array; }
                const float& operator[](int i) const { return array[i]; }
            };

            static const FloatTable VolumeCurve;    ///< Table that maps volume control change values 0..127 to amplitude. Unity gain is at 90.
            static const FloatTable PanCurve;       ///< Table that maps pan control change values 0..128 to right channel amplitude. Unity gain is at 64 (center).
            static const FloatTable CrossfadeCurve; ///< Table that maps crossfade control change values 0..127 to amplitude. Unity gain is at 127.

        //protected:
            static InstrumentResourceManager instruments;

            AudioOutputDevice*      pAudioOutputDevice;
            uint                    SampleRate;            ///< Sample rate of the engines output audio signal (in Hz)
            uint                    MaxSamplesPerCycle;    ///< Size of each audio output buffer
            DiskThread*             pDiskThread;
            RingBuffer<Event,false>* pEventQueue;          ///< Input event queue for engine global events (e.g. SysEx messages).
            Pool<Voice>*            pVoicePool;            ///< Contains all voices that can be activated.
            EventGenerator*         pEventGenerator;
            RTList<Event>*          pVoiceStealingQueue;   ///< All voice-launching events which had to be postponed due to free voice shortage.
            RTList<Event>*          pGlobalEvents;         ///< All engine global events for the current audio fragment (usually only SysEx messages).
            Pool<Event>*            pEventPool;            ///< Contains all Event objects that can be used.
            RingBuffer<uint8_t,false>* pSysexBuffer;       ///< Input buffer for MIDI system exclusive messages.
            int                     ActiveVoiceCountTemp;  ///< number of currently active voices (for internal usage, will be used for incrementation)
            int                     ActiveVoiceCountMax;   ///< the maximum voice usage since application start
            int                     VoiceSpawnsLeft;       ///< We only allow CONFIG_MAX_VOICES voices to be spawned per audio fragment, we use this variable to ensure this limit.
            RTList<Voice>::Iterator itLastStolenVoice;     ///< Only for voice stealing: points to the last voice which was theft in current audio fragment, NULL otherwise.
            RTList<uint>::Iterator  iuiLastStolenKey;      ///< Only for voice stealing: key number of last key on which the last voice was theft in current audio fragment, NULL otherwise.
            EngineChannel*          pLastStolenChannel;    ///< Only for voice stealing: points to the engine channel on which the previous voice was stolen in this audio fragment.
            RTList<Voice>::Iterator itLastStolenVoiceGlobally; ///< Same as itLastStolenVoice, but engine globally
            RTList<uint>::Iterator  iuiLastStolenKeyGlobally;  ///< Same as iuiLastStolenKey, but engine globally
            bool                    SuspensionRequested;
            ConditionServer         EngineDisabled;
            int8_t                  ScaleTuning[12];       ///< contains optional detune factors (-64..+63 cents) for all 12 semitones of an octave
            int                     MinFadeOutSamples;     ///< The number of samples needed to make an instant fade out (e.g. for voice stealing) without leading to clicks.
            uint32_t                RandomSeed;            ///< State of the random number generator used by the random dimension.
            Mutex                   ResetInternalMutex;    ///< Mutex to protect the ResetInternal function for concurrent usage (e.g. by the lscp and instrument loader threads).
            Pool< ::gig::DimensionRegion*>* pDimRegionPool[2]; ///< Double buffered pool, used by the engine channels to keep track of dimension regions in use.

            void ProcessEvents(EngineChannel* pEngineChannel, uint Samples);
            void RenderActiveVoices(EngineChannel* pEngineChannel, uint Samples);
            void RenderStolenVoices(uint Samples);
            void RouteAudio(EngineChannel* pEngineChannel, uint Samples);
            void PostProcess(EngineChannel* pEngineChannel);
            void ClearEventLists();
            void ImportEvents(uint Samples);
            void ProcessNoteOn(EngineChannel* pEngineChannel, Pool<Event>::Iterator& itNoteOnEvent);
            void ProcessNoteOff(EngineChannel* pEngineChannel, Pool<Event>::Iterator& itNoteOffEvent);
            void ProcessPitchbend(EngineChannel* pEngineChannel, Pool<Event>::Iterator& itPitchbendEvent);
            void ProcessControlChange(EngineChannel* pEngineChannel, Pool<Event>::Iterator& itControlChangeEvent);
            void ProcessSysex(Pool<Event>::Iterator& itSysexEvent);
            void ProcessSuspensionsChanges();
            void ProcessPendingStreamDeletions();
            Pool<Voice>::Iterator LaunchVoice(EngineChannel* pEngineChannel, Pool<Event>::Iterator& itNoteOnEvent, int iLayer, bool ReleaseTriggerVoice, bool VoiceStealing, bool HandleKeyGroupConflicts);
            int  StealVoice(EngineChannel* pEngineChannel, Pool<Event>::Iterator& itNoteOnEvent);
            void FreeVoice(EngineChannel* pEngineChannel, Pool<Voice>::Iterator& itVoice);
            void FreeKey(EngineChannel* pEngineChannel, midi_key_info_t* pKey);
            void ResetInternal();
            void ResetScaleTuning();
            void ResetSuspendedRegions();

            static Engine* AcquireEngine(LinuxSampler::gig::EngineChannel* pChannel, AudioOutputDevice* pDevice);
            static void    FreeEngine(LinuxSampler::gig::EngineChannel* pChannel, AudioOutputDevice* pDevice);

            void DisableAndLock(); // FIXME: should at least be protected

            friend class Voice;
        private:
            Pool< ::gig::Region*> SuspendedRegions;
            Mutex                 SuspendedRegionsMutex;
            Condition             SuspensionChangeOngoing;
            ::gig::Region*        pPendingRegionSuspension;
            ::gig::Region*        pPendingRegionResumption;
            int                   iPendingStreamDeletions;

            ArrayList<EngineChannel*> engineChannels; ///< All engine channels of a gig::Engine instance.

            static std::map<AudioOutputDevice*,Engine*> engines; ///< All instances of gig::Engine.

            int SostenutoKeys[128];
            int SostenutoKeyCount;

            uint8_t GSCheckSum(const RingBuffer<uint8_t,false>::NonVolatileReader AddrReader, uint DataSize);
            void    AdjustScale(int8_t ScaleTunes[12]);
            void    ReleaseAllVoices(EngineChannel* pEngineChannel, Pool<Event>::Iterator& itReleaseEvent);
            void    KillAllVoices(EngineChannel* pEngineChannel, Pool<Event>::Iterator& itKillEvent);
            bool    ShouldReleaseVoice(EngineChannel* pEngineChannel, int Key);
            bool    RegionSuspended(::gig::Region* pRegion);
            static float* InitVolumeCurve();
            static float* InitPanCurve();
            static float* InitCrossfadeCurve();
            static float* InitCurve(const float* segments, int size = 128);

            unsigned long FrameTime; ///< Time in frames of the start of the current audio fragment

            atomic_t ActiveVoiceCount; ///< number of currently active voices
            int iMaxDiskStreams;
    };

}} // namespace LinuxSampler::gig

#endif // __LS_GIG_ENGINE_H__
