/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003,2004 by Benno Senoner and Christian Schoenebeck    *
 *   Copyright (C) 2005-2008 Christian Schoenebeck                         *
 *   Copyright (C) 2009-2010 Christian Schoenebeck and Grigor Iliev        *
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

#ifndef __LS_ENGINECHANNELBASE_H__
#define	__LS_ENGINECHANNELBASE_H__

#include "AbstractEngineChannel.h"
#include "common/MidiKeyboardManager.h"
#include "common/Voice.h"
#include "../common/ResourceManager.h"

namespace LinuxSampler {
    /// Command used by the instrument loader thread to
    /// request an instrument change on a channel.
    template <class R /* Region */, class I /* Instrument */>
    class InstrumentChangeCmd {
        public:
            bool bChangeInstrument;       ///< Set to true by the loader when the channel should change instrument.
            I* pInstrument;               ///< The new instrument. Also used by the loader to read the previously loaded instrument.
            RTList<R*>* pRegionsInUse; ///< List of dimension regions in use by the currently loaded instrument. Continuously updated by the audio thread.
    };

    template<class R>
    class RegionPools {
        public:
            virtual Pool<R*>* GetRegionPool(int index) = 0;
    };

    template<class V>
    class VoicePool {
        public:
            virtual Pool<V>* GetVoicePool() = 0;
    };

    template <class V /* Voice */, class R /* Region */, class I /* Instrument */>
    class EngineChannelBase: public AbstractEngineChannel, public MidiKeyboardManager<V>, public ResourceConsumer<I> {
        public:
            typedef typename RTList<R*>::Iterator RTListRegionIterator;
            typedef typename MidiKeyboardManager<V>::MidiKey MidiKey;

            virtual void HandBack(I* Instrument) {
                ResourceManager<InstrumentManager::instrument_id_t, I>* mgr =
                    dynamic_cast<ResourceManager<InstrumentManager::instrument_id_t, I>*>(pEngine->GetInstrumentManager());
                mgr->HandBack(Instrument, this);
            }

            virtual void ClearRegionsInUse() {
                {
                    InstrumentChangeCmd<R, I>& cmd = InstrumentChangeCommand.GetConfigForUpdate();
                    if(cmd.pRegionsInUse != NULL) cmd.pRegionsInUse->clear();
                }
                {
                    InstrumentChangeCmd<R, I>& cmd = InstrumentChangeCommand.SwitchConfig();
                    if(cmd.pRegionsInUse != NULL) cmd.pRegionsInUse->clear();
                }
            }

            virtual void ResetRegionsInUse(Pool<R*>* pRegionPool[]) {
                DeleteRegionsInUse();
                AllocateRegionsInUse(pRegionPool);
            }

            virtual void DeleteRegionsInUse() {
                {
                    InstrumentChangeCmd<R, I>& cmd = InstrumentChangeCommand.GetConfigForUpdate();
                    if(cmd.pRegionsInUse != NULL) {
                        delete cmd.pRegionsInUse;
                        cmd.pRegionsInUse = NULL;
                    }
                }
                {
                    InstrumentChangeCmd<R, I>& cmd = InstrumentChangeCommand.SwitchConfig();
                    if(cmd.pRegionsInUse != NULL) {
                        delete cmd.pRegionsInUse;
                        cmd.pRegionsInUse = NULL;
                    }
                }
            }

            virtual void AllocateRegionsInUse(Pool<R*>* pRegionPool[]) {
                {
                    InstrumentChangeCmd<R, I>& cmd = InstrumentChangeCommand.GetConfigForUpdate();
                    cmd.pRegionsInUse = new RTList<R*>(pRegionPool[0]);
                }
                {
                    InstrumentChangeCmd<R, I>& cmd = InstrumentChangeCommand.SwitchConfig();
                    cmd.pRegionsInUse = new RTList<R*>(pRegionPool[1]);
                }
            }

            virtual void Connect(AudioOutputDevice* pAudioOut) {
                if (pEngine) {
                    if (pEngine->pAudioOutputDevice == pAudioOut) return;
                    DisconnectAudioOutputDevice();
                }
                pEngine = AbstractEngine::AcquireEngine(this, pAudioOut);
                ResetInternal();
                pEvents = new RTList<Event>(pEngine->pEventPool);

                RegionPools<R>* pRegionPool = dynamic_cast<RegionPools<R>*>(pEngine);
                // reset the instrument change command struct (need to be done
                // twice, as it is double buffered)
                {
                    InstrumentChangeCmd<R, I>& cmd = InstrumentChangeCommand.GetConfigForUpdate();
                    cmd.pRegionsInUse = new RTList<R*>(pRegionPool->GetRegionPool(0));
                    cmd.pInstrument = 0;
                    cmd.bChangeInstrument = false;
                }
                {
                    InstrumentChangeCmd<R, I>& cmd = InstrumentChangeCommand.SwitchConfig();
                    cmd.pRegionsInUse = new RTList<R*>(pRegionPool->GetRegionPool(1));
                    cmd.pInstrument = 0;
                    cmd.bChangeInstrument = false;
                }

                if (pInstrument != NULL) {
                    pInstrument = NULL;
                    InstrumentStat = -1;
                    InstrumentIdx  = -1;
                    InstrumentIdxName = "";
                    InstrumentFile = "";
                    bStatusChanged = true;
                }

                VoicePool<V>* pVoicePool = dynamic_cast<VoicePool<V>*>(pEngine);
                MidiKeyboardManager<V>::AllocateActiveVoices(pVoicePool->GetVoicePool());
                MidiKeyboardManager<V>::AllocateEvents(pEngine->pEventPool);

                AudioDeviceChannelLeft  = 0;
                AudioDeviceChannelRight = 1;
                if (fxSends.empty()) { // render directly into the AudioDevice's output buffers
                    pChannelLeft  = pAudioOut->Channel(AudioDeviceChannelLeft);
                    pChannelRight = pAudioOut->Channel(AudioDeviceChannelRight);
                } else { // use local buffers for rendering and copy later
                    // ensure the local buffers have the correct size
                    if (pChannelLeft)  delete pChannelLeft;
                    if (pChannelRight) delete pChannelRight;
                    pChannelLeft  = new AudioChannel(0, pAudioOut->MaxSamplesPerCycle());
                    pChannelRight = new AudioChannel(1, pAudioOut->MaxSamplesPerCycle());
                }
                if (pEngine->EngineDisabled.GetUnsafe()) pEngine->Enable();
                MidiInputPort::AddSysexListener(pEngine);
            }

            virtual void DisconnectAudioOutputDevice() {
                if (pEngine) { // if clause to prevent disconnect loops

                    ResetInternal();

                    DeleteRegionsInUse();

                    InstrumentChangeCmd<R, I>& cmd = InstrumentChangeCommand.GetConfigForUpdate();
                    if (cmd.pInstrument) {
                        // release the currently loaded instrument
                        HandBack(cmd.pInstrument);
                    }

                    if (pEvents) {
                        delete pEvents;
                        pEvents = NULL;
                    }

                    MidiKeyboardManager<V>::DeleteActiveVoices();
                    MidiKeyboardManager<V>::DeleteEvents();
                    DeleteGroupEventLists();

                    AudioOutputDevice* oldAudioDevice = pEngine->pAudioOutputDevice;
                    pEngine = NULL;
                    AbstractEngine::FreeEngine(this, oldAudioDevice);
                    AudioDeviceChannelLeft  = -1;
                    AudioDeviceChannelRight = -1;
                    if (!fxSends.empty()) { // free the local rendering buffers
                        if (pChannelLeft)  delete pChannelLeft;
                        if (pChannelRight) delete pChannelRight;
                    }
                    pChannelLeft  = NULL;
                    pChannelRight = NULL;
                }
            }

            class ClearEventListsHandler : public MidiKeyboardManager<V>::VoiceHandlerBase {
                public:
                    virtual bool Process(MidiKey* pMidiKey) { pMidiKey->pEvents->clear(); return false; }
            };

            void ClearEventLists() {
                pEvents->clear();
                // empty MIDI key specific event lists
                ClearEventListsHandler handler;
                ProcessActiveVoices(&handler);

                // empty exclusive group specific event lists
                ClearGroupEventLists();
            }

            // implementation of abstract methods derived from interface class 'InstrumentConsumer'

            /**
             * Will be called by the InstrumentResourceManager when the instrument
             * we are currently using on this EngineChannel is going to be updated,
             * so we can stop playback before that happens.
             */
            virtual void ResourceToBeUpdated(I* pResource, void*& pUpdateArg) {
                dmsg(3,("EngineChannelBase: Received instrument update message.\n"));
                if (pEngine) pEngine->DisableAndLock();
                ResetInternal();
                this->pInstrument = NULL;
            }

            /**
             * Will be called by the InstrumentResourceManager when the instrument
             * update process was completed, so we can continue with playback.
             */
            virtual void ResourceUpdated(I* pOldResource, I* pNewResource, void* pUpdateArg) {
                this->pInstrument = pNewResource; //TODO: there are couple of engine parameters we should update here as well if the instrument was updated (see LoadInstrument())
                if (pEngine) pEngine->Enable();
                bStatusChanged = true; // status of engine has changed, so set notify flag
            }

            /**
             * Will be called by the InstrumentResourceManager on progress changes
             * while loading or realoading an instrument for this EngineChannel.
             *
             * @param fProgress - current progress as value between 0.0 and 1.0
             */
            virtual void OnResourceProgress(float fProgress) {
                this->InstrumentStat = int(fProgress * 100.0f);
                dmsg(7,("EngineChannelBase: progress %d%", InstrumentStat));
                bStatusChanged = true; // status of engine has changed, so set notify flag
            }

            void RenderActiveVoices(uint Samples) {
                RenderVoicesHandler handler(this, Samples);
                ProcessActiveVoices(&handler);

                SetVoiceCount(handler.VoiceCount);
                SetDiskStreamCount(handler.StreamCount);
            }

            RTList<R*>* pRegionsInUse;     ///< temporary pointer into the instrument change command, used by the audio thread
            I* pInstrument;

            template<class TV, class TRR, class TR, class TD, class TIM, class TI> friend class EngineBase;

        protected:
            EngineChannelBase() : InstrumentChangeCommandReader(InstrumentChangeCommand) {
                pInstrument = NULL;

                // reset the instrument change command struct (need to be done
                // twice, as it is double buffered)
                {
                    InstrumentChangeCmd<R, I>& cmd = InstrumentChangeCommand.GetConfigForUpdate();
                    cmd.pRegionsInUse = NULL;
                    cmd.pInstrument = NULL;
                    cmd.bChangeInstrument = false;
                }
                {
                    InstrumentChangeCmd<R, I>& cmd = InstrumentChangeCommand.SwitchConfig();
                    cmd.pRegionsInUse = NULL;
                    cmd.pInstrument = NULL;
                    cmd.bChangeInstrument = false;
                }
            }

            virtual ~EngineChannelBase() { }

            typedef typename RTList<V>::Iterator RTListVoiceIterator;

            class RenderVoicesHandler : public MidiKeyboardManager<V>::VoiceHandlerBase {
                public:
                    uint Samples;
                    uint VoiceCount;
                    uint StreamCount;
                    EngineChannelBase<V, R, I>* pChannel;

                    RenderVoicesHandler(EngineChannelBase<V, R, I>* channel, uint samples) :
                        pChannel(channel), Samples(samples), VoiceCount(0), StreamCount(0) { }

                    virtual void Process(RTListVoiceIterator& itVoice) {
                        // now render current voice
                        itVoice->Render(Samples);
                        if (itVoice->IsActive()) { // still active
                            if (!itVoice->Orphan) {
                                *(pChannel->pRegionsInUse->allocAppend()) = itVoice->GetRegion();
                            }
                            VoiceCount++;

                            if (itVoice->PlaybackState == Voice::playback_state_disk) {
                                if ((itVoice->DiskStreamRef).State != Stream::state_unused) StreamCount++;
                            }
                        }  else { // voice reached end, is now inactive
                            pChannel->FreeVoice(itVoice); // remove voice from the list of active voices
                        }
                    }
            };

            typedef typename SynchronizedConfig<InstrumentChangeCmd<R, I> >::Reader SyncConfInstrChangeCmdReader;

            SynchronizedConfig<InstrumentChangeCmd<R, I> > InstrumentChangeCommand;
            SyncConfInstrChangeCmdReader InstrumentChangeCommandReader;

            /** This method is not thread safe! */
            virtual void ResetInternal() {
                AbstractEngineChannel::ResetInternal();

                MidiKeyboardManager<V>::Reset();
            }

            virtual void ResetControllers() {
                AbstractEngineChannel::ResetControllers();

                MidiKeyboardManager<V>::SustainPedal   = false;
                MidiKeyboardManager<V>::SostenutoPedal = false;
            }

            /**
             * Changes the instrument for an engine channel.
             *
             * @param pInstrument - new instrument
             * @returns the resulting instrument change command after the
             *          command switch, containing the old instrument and
             *          the dimregions it is using
             */
            InstrumentChangeCmd<R, I>& ChangeInstrument(I* pInstrument) {
                InstrumentChangeCmd<R, I>& cmd = InstrumentChangeCommand.GetConfigForUpdate();
                cmd.pInstrument = pInstrument;
                cmd.bChangeInstrument = true;

                return InstrumentChangeCommand.SwitchConfig();
            }

            virtual void ProcessKeySwitchChange(int key) = 0;
    };

} // namespace LinuxSampler

#endif	/* __LS_ENGINECHANNELBASE_H__ */
