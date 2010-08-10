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

#ifndef __LS_MIDIKEYBOARDMANAGER_H__
#define __LS_MIDIKEYBOARDMANAGER_H__

#include "Event.h"
#include "Stream.h"
#include "../../EventListeners.h"
#include "../../common/Pool.h"
#include "../../common/global_private.h"

namespace LinuxSampler {

    /**
     * This class is used as a listener, which is notified
     * when MIDI keyboard events occur like note on, note off, etc.
     * Note that all events are triggered even when the channel is muted
     */
    class MidiKeyboardListener {
        public:
            /** Called before the engine start processing the note on event */
            virtual void PreProcessNoteOn(uint8_t key, uint8_t velocity) = 0;

            /** Called after the engine has processed the note on event */
            virtual void PostProcessNoteOn(uint8_t key, uint8_t velocity) = 0;

            /** Called before the engine start processing the note off event */
            virtual void PreProcessNoteOff(uint8_t key, uint8_t velocity) = 0;

            /** Called after the engine has processed the note off event */
            virtual void PostProcessNoteOff(uint8_t key, uint8_t velocity) = 0;

            /** Called before the engine start processing the sustain pedal up event */
            virtual void PreProcessSustainPedalUp() = 0;

            /** Called after the engine has processed the sustain pedal up event */
            virtual void PostProcessSustainPedalUp() = 0;

            /** Called before the engine start processing the sustain pedal down event */
            virtual void PreProcessSustainPedalDown() = 0;

            /** Called after the engine has processed the sustain pedal down event */
            virtual void PostProcessSustainPedalDown() = 0;

            /** Called before the engine start processing the sostenuto pedal up event */
            virtual void PreProcessSostenutoPedalUp() = 0;

            /** Called after the engine has processed the sostenuto pedal up event */
            virtual void PostProcessSostenutoPedalUp() = 0;

            /** Called before the engine start processing the sostenuto pedal down event */
            virtual void PreProcessSostenutoPedalDown() = 0;

            /** Called after the engine has processed the sostenuto pedal down event */
            virtual void PostProcessSostenutoPedalDown() = 0;
    };

    /**
     * This class exists as convenience for creating listener objects.
     * The methods in this class are empty.
     */
    class MidiKeyboardAdapter : public MidiKeyboardListener {
        public:
            virtual void PreProcessNoteOn(uint8_t key, uint8_t velocity) { }
            virtual void PostProcessNoteOn(uint8_t key, uint8_t velocity) { }
            virtual void PreProcessNoteOff(uint8_t key, uint8_t velocity) { }
            virtual void PostProcessNoteOff(uint8_t key, uint8_t velocity) { }
            virtual void PreProcessSustainPedalUp() { }
            virtual void PostProcessSustainPedalUp() { }
            virtual void PreProcessSustainPedalDown() { }
            virtual void PostProcessSustainPedalDown() { }
            virtual void PreProcessSostenutoPedalUp() { }
            virtual void PostProcessSostenutoPedalUp() { }
            virtual void PreProcessSostenutoPedalDown() { }
            virtual void PostProcessSostenutoPedalDown() { }
    };

    template <class V>
    class MidiKeyboardManager {
        public:
            /** @brief Voice Stealing Algorithms
             *
             * Enumeration of all possible voice stealing algorithms.
             */
            enum voice_steal_algo_t {
                voice_steal_algo_none,              ///< Voice stealing disabled.
                voice_steal_algo_oldestvoiceonkey,  ///< Try to kill the oldest voice from same key where the new voice should be spawned.
                voice_steal_algo_oldestkey          ///< Try to kill the oldest voice from the oldest active key.
            };


            /** @brief MIDI key runtime informations
             *
             * Reflects runtime informations for one MIDI key.
             */
            class MidiKey {
            public:
                RTList<V>*      pActiveVoices;  ///< Contains the active voices associated with the MIDI key.
                bool            KeyPressed;     ///< Is true if the respective MIDI key is currently pressed.
                bool            Active;         ///< If the key contains active voices.
                bool            ReleaseTrigger; ///< If we have to launch release triggered voice(s) when the key is released
                Pool<uint>::Iterator itSelf;    ///< hack to allow fast deallocation of the key from the list of active keys
                RTList<Event>*  pEvents;        ///< Key specific events (only Note-on, Note-off and sustain pedal currently)
                int             VoiceTheftsQueued; ///< Amount of voices postponed due to shortage of voices.
                uint32_t*       pRoundRobinIndex; ///< For the round robin dimension: current articulation for this key, will be incremented for each note on
                uint8_t         Velocity;       ///< Latest Note-on velocity for this key
                unsigned long   NoteOnTime;     ///< Time for latest Note-on event for this key

                MidiKey() {
                    pActiveVoices  = NULL;
                    KeyPressed     = false;
                    Active         = false;
                    ReleaseTrigger = false;
                    pEvents        = NULL;
                    VoiceTheftsQueued = 0;
                }

                void Reset() {
                    if (pActiveVoices) pActiveVoices->clear();
                    if (pEvents) pEvents->clear();
                    KeyPressed        = false;
                    Active            = false;
                    ReleaseTrigger    = false;
                    itSelf            = Pool<uint>::Iterator();
                    VoiceTheftsQueued = 0;
                }
            };

            typedef typename RTList<V>::Iterator RTListVoiceIterator;
            typedef typename Pool<V>::Iterator PoolVoiceIterator;

            /**
             * Override this class to iterate through all active keys/voices
             * using ProcessActiveVoices() method.
             */
            class VoiceHandler {
                public:
                    /**
                     * @returns true if the voices on the specified key should be processed
                     * adn false to cancel the processing of the active voices for the
                     * specified key
                     */
                    virtual bool Process(MidiKey* pMidiKey) = 0;

                    virtual void Process(RTListVoiceIterator& itVoice) = 0;
            };

            class VoiceHandlerBase : public VoiceHandler {
                public:
                    virtual bool Process(MidiKey* pMidiKey) { return true; }
                    virtual void Process(RTListVoiceIterator& itVoice) { }
            };

            MidiKey*              pMIDIKeyInfo; ///< Contains all active voices sorted by MIDI key number and other informations to the respective MIDI key
            Pool<uint>*           pActiveKeys;  ///< Holds all keys in it's allocation list with active voices.
            bool                  SoloMode;                 ///< in Solo Mode we only play one voice (group) at a time
            int                   SoloKey;                  ///< Currently 'active' solo key, that is the key to which the currently sounding voice belongs to (only if SoloMode is enabled)
            bool                  SustainPedal;             ///< true if sustain pedal is down
            bool                  SostenutoPedal;           ///< true if sostenuto pedal is down
            int                   SostenutoKeys[128];
            int                   SostenutoKeyCount;
            uint32_t              RoundRobinIndexes[128];

            MidiKeyboardManager() {
                pMIDIKeyInfo = new MidiKey[128];
                pActiveKeys  = new Pool<uint>(128);
                SoloMode     = false;
                SustainPedal   = false;
                SostenutoPedal = false;
                for (int i = 0 ; i < 128 ; i++) {
                    RoundRobinIndexes[i] = 0;

                    // by default use one counter for each key (the
                    // gig engine will change this to one counter per
                    // region)
                    pMIDIKeyInfo[i].pRoundRobinIndex = &RoundRobinIndexes[i];
                }
            }

            virtual ~MidiKeyboardManager() {
                listeners.RemoveAllListeners();
                if (pActiveKeys) delete pActiveKeys;
                if (pMIDIKeyInfo) delete[] pMIDIKeyInfo;
            }

            void Reset() {
                SoloKey = -1;    // no solo key active yet

                // reset key info
                for (uint i = 0; i < 128; i++) pMIDIKeyInfo[i].Reset();

                // free all active keys
                pActiveKeys->clear();
            }

            void AllocateActiveVoices(Pool<V>* pVoicePool) {
                DeleteActiveVoices();

                for (uint i = 0; i < 128; i++) {
                    pMIDIKeyInfo[i].pActiveVoices = new RTList<V>(pVoicePool);
                }
            }

            void DeleteActiveVoices() {
                for (uint i = 0; i < 128; i++) {
                    if (pMIDIKeyInfo[i].pActiveVoices) {
                        delete pMIDIKeyInfo[i].pActiveVoices;
                        pMIDIKeyInfo[i].pActiveVoices = NULL;
                    }
                }
            }

            void AllocateEvents(Pool<Event>* pEventPool) {
                DeleteEvents();

                for (uint i = 0; i < 128; i++) {
                    pMIDIKeyInfo[i].pEvents = new RTList<Event>(pEventPool);
                }
            }

            void DeleteEvents() {
                for (uint i = 0; i < 128; i++) {
                    if (pMIDIKeyInfo[i].pEvents) {
                        delete pMIDIKeyInfo[i].pEvents;
                        pMIDIKeyInfo[i].pEvents = NULL;
                    }
                }
            }

            void ClearAllActiveKeyEvents() {
                RTList<uint>::Iterator iuiKey = pActiveKeys->first();
                RTList<uint>::Iterator end    = pActiveKeys->end();
                for(; iuiKey != end; ++iuiKey) {
                    pMIDIKeyInfo[*iuiKey].pEvents->clear(); // free all events on the key
                }
            }

            /**
             *  Removes the given voice from the MIDI key's list of active voices.
             *  This method will be called when a voice went inactive, e.g. because
             *  it finished to playback its sample, finished its release stage or
             *  just was killed.
             *
             *  @param itVoice - points to the voice to be freed
             */
            void FreeVoice(PoolVoiceIterator& itVoice) {
                if (itVoice) {
                    MidiKey* pKey = &pMIDIKeyInfo[itVoice->MIDIKey];

                    // if the sample and dimension region belong to an
                    // instrument that is unloaded, tell the disk thread to
                    // release them
                    if (itVoice->Orphan) {
                        if(itVoice->pDiskThread != NULL) {
                            itVoice->pDiskThread->OrderDeletionOfRegion(itVoice->GetRegion());
                        }
                    }

                    // free the voice object
                    pKey->pActiveVoices->free(itVoice);
                }
                else std::cerr << "Couldn't release voice! (!itVoice)\n" << std::flush;
            }

            /**
             *  Called when there's no more voice left on a key, this call will
             *  update the key info respectively.
             *
             *  @param pEngineChannel - engine channel on which this event occured on
             *  @param pKey - key which is now inactive
             */
            void FreeKey(MidiKey* pKey) {
                if (pKey->pActiveVoices->isEmpty()) {
                    pKey->Active = false;
                    pActiveKeys->free(pKey->itSelf); // remove key from list of active keys
                    pKey->itSelf = RTList<uint>::Iterator();
                    pKey->ReleaseTrigger = false;
                    pKey->pEvents->clear();
                    dmsg(3,("Key has no more voices now\n"));
                }
                else dmsg(1,("MidiKeyboardManager: Oops, tried to free a key which contains voices.\n"));
            }

            /**
             * Free all keys which have no active voices left
             */
            void FreeAllInactiveKyes() {
                RTList<uint>::Iterator iuiKey = pActiveKeys->first();
                RTList<uint>::Iterator end    = pActiveKeys->end();
                while (iuiKey != end) { // iterate through all active keys
                   MidiKey* pKey = &pMIDIKeyInfo[*iuiKey];
                    ++iuiKey;
                    if (pKey->pActiveVoices->isEmpty()) FreeKey(pKey);
                    #if CONFIG_DEVMODE
                    else { // just a sanity check for debugging
                        RTListVoiceIterator itVoice = pKey->pActiveVoices->first();
                        RTListVoiceIterator = pKey->pActiveVoices->end();
                        for (; itVoice != itVoicesEnd; ++itVoice) { // iterate through all voices on this key
                            if (itVoice->itKillEvent) {
                                dmsg(1,("gig::Engine: ERROR, killed voice survived !!!\n"));
                            }
                        }
                    }
                    #endif // CONFIG_DEVMODE
                }
            }

            int StealVoice (
                Pool<Event>::Iterator&   itNoteOnEvent,
                RTListVoiceIterator*     LastStolenVoice,
                RTList<uint>::Iterator*  LastStolenKey
            ) {
                RTListVoiceIterator itSelectedVoice;

                // Select one voice for voice stealing
                switch (CONFIG_VOICE_STEAL_ALGO) {

                    // try to pick the oldest voice on the key where the new
                    // voice should be spawned, if there is no voice on that
                    // key, or no voice left to kill, then procceed with
                    // 'oldestkey' algorithm
                    case voice_steal_algo_oldestvoiceonkey: {
                        MidiKey* pSelectedKey = &pMIDIKeyInfo[itNoteOnEvent->Param.Note.Key];
                        itSelectedVoice = pSelectedKey->pActiveVoices->first();
                        // proceed iterating if voice was created in this fragment cycle
                        while (itSelectedVoice && !itSelectedVoice->IsStealable()) ++itSelectedVoice;
                        // if we haven't found a voice then proceed with algorithm 'oldestkey'
                        if (itSelectedVoice && itSelectedVoice->IsStealable()) break;
                    } // no break - intentional !

                    // try to pick the oldest voice on the oldest active key
                    // from the same engine channel
                    // (caution: must stay after 'oldestvoiceonkey' algorithm !)
                    case voice_steal_algo_oldestkey: {
                        // if we already stole in this fragment, try to proceed on same key
                        if (*LastStolenVoice) {
                            itSelectedVoice = *LastStolenVoice;
                            do {
                                ++itSelectedVoice;
                            } while (itSelectedVoice && !itSelectedVoice->IsStealable()); // proceed iterating if voice was created in this fragment cycle
                            // found a "stealable" voice ?
                            if (itSelectedVoice && itSelectedVoice->IsStealable()) {
                                // remember which voice we stole, so we can simply proceed on next voice stealing
                                *LastStolenVoice = itSelectedVoice;
                                break; // selection succeeded
                            }
                        }
                        // get (next) oldest key
                        RTList<uint>::Iterator iuiSelectedKey = (*LastStolenKey) ? ++(*LastStolenKey) : pActiveKeys->first();
                        while (iuiSelectedKey) {
                            MidiKey* pSelectedKey = &pMIDIKeyInfo[*iuiSelectedKey];
                            itSelectedVoice = pSelectedKey->pActiveVoices->first();
                            // proceed iterating if voice was created in this fragment cycle
                            while (itSelectedVoice && !itSelectedVoice->IsStealable()) ++itSelectedVoice;
                            // found a "stealable" voice ?
                            if (itSelectedVoice && itSelectedVoice->IsStealable()) {
                                // remember which voice on which key we stole, so we can simply proceed on next voice stealing
                                *LastStolenKey  = iuiSelectedKey;
                                *LastStolenVoice = itSelectedVoice;
                                break; // selection succeeded
                            }
                            ++iuiSelectedKey; // get next oldest key
                        }
                        break;
                    }

                    // don't steal anything
                    case voice_steal_algo_none:
                    default: {
                        dmsg(1,("No free voice (voice stealing disabled)!\n"));
                        return -1;
                    }
                }

                if (!itSelectedVoice || !itSelectedVoice->IsStealable()) return -1;

                #if CONFIG_DEVMODE
                if (!itSelectedVoice->IsActive()) {
                    dmsg(1,("gig::Engine: ERROR, tried to steal a voice which was not active !!!\n"));
                    return -1;
                }
                #endif // CONFIG_DEVMODE

                // now kill the selected voice
                itSelectedVoice->Kill(itNoteOnEvent);

                return 0;
            }

            /**
             * Releases all voices. All voices will go into
             * the release stage and thus it might take some time (e.g. dependant to
             * their envelope release time) until they actually die.
             *
             * @param itReleaseEvent - event which caused this releasing of all voices
             */
            void ReleaseAllVoices(Pool<Event>::Iterator& itReleaseEvent) {
                RTList<uint>::Iterator iuiKey = pActiveKeys->first();
                while (iuiKey) {
                    MidiKey* pKey = &pMIDIKeyInfo[*iuiKey];
                    ++iuiKey;
                    // append a 'release' event to the key's own event list
                    RTList<Event>::Iterator itNewEvent = pKey->pEvents->allocAppend();
                    if (itNewEvent) {
                        *itNewEvent = *itReleaseEvent; // copy original event (to the key's event list)
                        itNewEvent->Type = Event::type_release; // transform event type
                    }
                    else dmsg(1,("Event pool emtpy!\n"));
                }
            }
            /**
             * Kill all active voices.
             * @returns The number of voices.
             */
            int KillAllVoices(Pool<Event>::Iterator& itKillEvent) {
                int count = 0;

                RTList<uint>::Iterator iuiKey  = pActiveKeys->first();
                RTList<uint>::Iterator end = pActiveKeys->end();
                for (; iuiKey != end; ++iuiKey) { // iterate through all active keys
                    MidiKey* pKey = &pMIDIKeyInfo[*iuiKey];
                    RTListVoiceIterator itVoice = pKey->pActiveVoices->first();
                    RTListVoiceIterator itVoicesEnd = pKey->pActiveVoices->end();
                    for (; itVoice != itVoicesEnd; ++itVoice) { // iterate through all voices on this key
                        itVoice->Kill(itKillEvent);
                        count++;
                    }
                }

                return count;
            }

            /**
             * Kill all voices the *die hard* way.
             * @returns The number of pending stream deletions
             */
            int KillAllVoicesImmediately() {
                int iPendingStreamDeletions = 0;

                RTList<uint>::Iterator iuiKey  = pActiveKeys->first();
                RTList<uint>::Iterator end = pActiveKeys->end();
                for (; iuiKey != end; ++iuiKey) { // iterate through all active keys
                    MidiKey* pKey = &pMIDIKeyInfo[*iuiKey];
                    RTListVoiceIterator itVoice = pKey->pActiveVoices->first();
                    RTListVoiceIterator itVoicesEnd = pKey->pActiveVoices->end();
                    for (; itVoice != itVoicesEnd; ++itVoice) { // iterate through all voices on this key
                        // request a notification from disk thread side for stream deletion
                        const Stream::Handle hStream = itVoice->KillImmediately(true);
                        if (hStream != Stream::INVALID_HANDLE) { // voice actually used a stream
                            iPendingStreamDeletions++;
                        }
                        // free the voice to the voice pool and update key info
                        FreeVoice(itVoice);
                    }
                }

                return iPendingStreamDeletions;
            }

            /**
             * Mark all currently active voices as "orphans", which means that the regions and
             * samples they use should be released to the instrument manager when the voices die.
             */
            void MarkAllActiveVoicesAsOrphans() {
                RTList<uint>::Iterator iuiKey  = pActiveKeys->first();
                RTList<uint>::Iterator end = pActiveKeys->end();
                for (; iuiKey != end; ++iuiKey) { // iterate through all active keys
                    MidiKey* pKey = &pMIDIKeyInfo[*iuiKey];
                    RTListVoiceIterator itVoice = pKey->pActiveVoices->first();
                    RTListVoiceIterator itVoicesEnd = pKey->pActiveVoices->end();
                    for (; itVoice != itVoicesEnd; ++itVoice) { // iterate through all voices on this key
                        itVoice->Orphan = true;
                    }
                }
            }

            void ProcessActiveVoices(VoiceHandler* pVoiceHandler) {
                if (pVoiceHandler == NULL) return;

                RTList<uint>::Iterator iuiKey  = pActiveKeys->first();
                RTList<uint>::Iterator end = pActiveKeys->end();
                for (; iuiKey != end; ++iuiKey) { // iterate through all active keys
                    MidiKey* pKey = &pMIDIKeyInfo[*iuiKey];
                    if (!pVoiceHandler->Process(pKey)) continue;

                    RTListVoiceIterator itVoice = pKey->pActiveVoices->first();
                    RTListVoiceIterator itVoicesEnd = pKey->pActiveVoices->end();
                    for (; itVoice != itVoicesEnd; ++itVoice) { // iterate through all voices on this key
                        pVoiceHandler->Process(itVoice);
                    }
                }
            }

            void ProcessSustainPedalDown(Pool<Event>::Iterator& itEvent) {
                // Cancel release process of all voices
                RTList<uint>::Iterator iuiKey = pActiveKeys->first();
                for (; iuiKey; ++iuiKey) {
                    MidiKey* pKey = &pMIDIKeyInfo[*iuiKey];
                    if (!pKey->KeyPressed) {
                        RTList<Event>::Iterator itNewEvent = pKey->pEvents->allocAppend();
                        if (itNewEvent) {
                            *itNewEvent = *itEvent; // copy event to the key's own event list
                            itNewEvent->Type = Event::type_cancel_release; // transform event type
                        }
                        else dmsg(1,("Event pool emtpy!\n"));
                    }
                }
            }

            void ProcessSustainPedalUp(Pool<Event>::Iterator& itEvent) {
                // release voices if their respective key is not pressed
                RTList<uint>::Iterator iuiKey = pActiveKeys->first();
                for (; iuiKey; ++iuiKey) {
                    MidiKey* pKey = &pMIDIKeyInfo[*iuiKey];
                    if (!pKey->KeyPressed && ShouldReleaseVoice(*iuiKey)) {
                        RTList<Event>::Iterator itNewEvent = pKey->pEvents->allocAppend();
                        if (itNewEvent) {
                            *itNewEvent = *itEvent; // copy event to the key's own event list
                            itNewEvent->Type = Event::type_release; // transform event type
                        }
                        else dmsg(1,("Event pool emtpy!\n"));
                    }
                }
            }

            /**
             * Determines whether the specified voice should be released.
             *
             * @param pEngineChannel - The engine channel on which the voice should be checked
             * @param Key - The key number
             * @returns true if the specified voice should be released, false otherwise.
             */
            bool ShouldReleaseVoice(int Key) {
                if (SustainPedal) return false;

                if (SostenutoPedal) {
                    for (int i = 0; i < SostenutoKeyCount; i++)
                        if (Key == SostenutoKeys[i]) return false;
                }

                return true;
            }

            void ProcessSostenutoPedalDown() {
                SostenutoKeyCount = 0;
                // Remeber the pressed keys
                RTList<uint>::Iterator iuiKey = pActiveKeys->first();
                for (; iuiKey; ++iuiKey) {
                    MidiKey* pKey = &pMIDIKeyInfo[*iuiKey];
                    if (pKey->KeyPressed && SostenutoKeyCount < 128) SostenutoKeys[SostenutoKeyCount++] = *iuiKey;
                }
            }

            void ProcessSostenutoPedalUp(Pool<Event>::Iterator& itEvent) {
                // release voices if the damper pedal is up and their respective key is not pressed
                for (int i = 0; i < SostenutoKeyCount; i++) {
                    MidiKey* pKey = &pMIDIKeyInfo[SostenutoKeys[i]];
                    if (!pKey->KeyPressed && !SustainPedal) {
                        RTList<Event>::Iterator itNewEvent = pKey->pEvents->allocAppend();
                        if (itNewEvent) {
                            *itNewEvent = *itEvent; // copy event to the key's own event list
                            itNewEvent->Type = Event::type_release; // transform event type
                        }
                        else dmsg(1,("Event pool emtpy!\n"));
                    }
                }
            }

            void AddMidiKeyboardListener(MidiKeyboardListener* l) { listeners.AddListener(l); }

            void RemoveMidiKeyboardListener(MidiKeyboardListener* l) { listeners.RemoveListener(l); }

        protected:
            class Listeners : public MidiKeyboardListener, public ListenerList<MidiKeyboardListener*> {
            public:
                REGISTER_FIRE_EVENT_METHOD_ARG2(PreProcessNoteOn, uint8_t, uint8_t)
                REGISTER_FIRE_EVENT_METHOD_ARG2(PostProcessNoteOn, uint8_t, uint8_t)
                REGISTER_FIRE_EVENT_METHOD_ARG2(PreProcessNoteOff, uint8_t, uint8_t)
                REGISTER_FIRE_EVENT_METHOD_ARG2(PostProcessNoteOff, uint8_t, uint8_t)
                REGISTER_FIRE_EVENT_METHOD(PreProcessSustainPedalUp)
                REGISTER_FIRE_EVENT_METHOD(PostProcessSustainPedalUp)
                REGISTER_FIRE_EVENT_METHOD(PreProcessSustainPedalDown)
                REGISTER_FIRE_EVENT_METHOD(PostProcessSustainPedalDown)
                REGISTER_FIRE_EVENT_METHOD(PreProcessSostenutoPedalUp)
                REGISTER_FIRE_EVENT_METHOD(PostProcessSostenutoPedalUp)
                REGISTER_FIRE_EVENT_METHOD(PreProcessSostenutoPedalDown)
                REGISTER_FIRE_EVENT_METHOD(PostProcessSostenutoPedalDown)
            } listeners;
    };
} // namespace LinuxSampler

#endif  /* __LS_MIDIKEYBOARDMANAGER_H__ */
