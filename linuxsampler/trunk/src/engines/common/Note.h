/*
 * Copyright (c) 2016 Christian Schoenebeck
 *
 * http://www.linuxsampler.org
 *
 * This file is part of LinuxSampler and released under the same terms.
 * See README file for details.
 */ 

#ifndef LS_NOTE_H
#define LS_NOTE_H

#include "../../common/Pool.h"
#include "Event.h"

namespace LinuxSampler {

    /**
     * Abstract base class of its deriving @c Note class, this class (NoteBase)
     * is not intended to be instantiated directly. It just provides access to
     * the parts of a Note object which do not depend on any C++ template
     * parameter.
     */
    class NoteBase {
    public:
        int hostKey; ///< Key on which this is @c Note is allocated on. This is usually the note-on event's note number, however in case of a child note this will rather be the parent note's key instead!
        note_id_t parentNoteID; ///< If not null: unique ID of the parent note of this note (see comments of field @c pChildNotes).
        RTList<note_id_t>* pChildNotes; ///< Note ID list of "child" notes of this note. These are special notes that must be released once this note gets released.
        Event cause; ///< Copy of the original event (usually a note-on event) which caused this note.
        event_id_t eventID; ///< Unique ID of the actual original @c Event which caused this note.
        /// Sampler format specific informations and variables.
        union _Format {
            /// Gigasampler/GigaStudio format specifics.
            struct _Gig {
                uint8_t DimMask; ///< May be used to override the Dimension zone to be selected for a new voice: each 1 bit means that respective bit shall be overridden by taking the respective bit from DimBits instead.
                uint8_t DimBits; ///< Used only in conjunction with DimMask: Dimension bits that shall be selected.
            } Gig;
        } Format;
    protected:
        NoteBase() : hostKey(0), parentNoteID(0), pChildNotes(NULL) {
            Format = _Format();
        }
    };

    /**
     * Contains the voices caused by one specific note, as well as basic
     * informations about the note itself.
     */
    template<class V>
    class Note : public NoteBase {
    public:
        RTList<V>* pActiveVoices; ///< Contains the active voices associated with this note.

        Note() : NoteBase(), pActiveVoices(NULL) {}

        virtual ~Note() {
            if (pChildNotes) delete pChildNotes;
            if (pActiveVoices) delete pActiveVoices;
        }

        void init(Pool<V>* pVoicePool, Pool<note_id_t>* pNoteIDPool) {
            if (pActiveVoices) delete pActiveVoices;
            pActiveVoices = new RTList<V>(pVoicePool);
            if (pChildNotes) delete pChildNotes;
            pChildNotes = new RTList<note_id_t>(pNoteIDPool);
        }

        void reset() {
            hostKey = 0;
            parentNoteID = 0;
            if (pChildNotes)
                pChildNotes->clear();
            cause = Event();
            eventID = 0;
            Format = _Format();
            if (pActiveVoices) {
                typename RTList<V>::Iterator itVoice = pActiveVoices->first();
                typename RTList<V>::Iterator itVoicesEnd = pActiveVoices->end();
                for (; itVoice != itVoicesEnd; ++itVoice) { // iterate through all voices on this key
                    itVoice->VoiceFreed();
                }
                pActiveVoices->clear();
            }
        }
    };

} // namespace LinuxSampler

#endif // LS_NOTE_H
