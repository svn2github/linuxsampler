/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2007, 2008 Christian Schoenebeck                        *
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

#include "InstrumentEditor.h"

#include "../common/global_private.h"
#include "../common/atomic.h"

#include <algorithm>
#include <functional>

#define MIDI_KEYS	128

namespace LinuxSampler {

    InstrumentEditor::InstrumentEditor() : Thread(false, false, -1, 0) {
        pInstrument = NULL;
        pNotesChanged = new atomic_t;
        pNoteChanged  = new atomic_t[MIDI_KEYS];
        pNoteIsActive = new atomic_t[MIDI_KEYS];
        atomic_t zero = ATOMIC_INIT(0);
        for (int i = 0; i < MIDI_KEYS; i++) {
            ((atomic_t*)pNoteChanged)[i]  = zero;
            ((atomic_t*)pNoteIsActive)[i] = zero;
        }
        *((atomic_t*)pNotesChanged) = zero;
    }

    InstrumentEditor::~InstrumentEditor() {
        if (pNoteIsActive) delete[] (atomic_t*)pNoteIsActive;
        if (pNoteChanged)  delete[] (atomic_t*)pNoteChanged;
        if (pNotesChanged) delete (atomic_t*)pNotesChanged;
    }

    void InstrumentEditor::Launch(void* pInstrument, String sTypeName, String sTypeVersion) {
        dmsg(1,("InstrumentEditor::Launch(instr=%x,type=%s,version=%s)\n", pInstrument, sTypeName.c_str(), sTypeVersion.c_str()));
        // prepare the editor's mandatory parameters
        this->pInstrument  = pInstrument;
        this->sTypeName    = sTypeName;
        this->sTypeVersion = sTypeVersion;
        // start the editor in its own thread
        StartThread();
    }

    int InstrumentEditor::Main() {
        dmsg(1,("InstrumentEditor::Main()\n"));
        // run the editor's main loop
        int iResult = Main(pInstrument, sTypeName, sTypeVersion);
        // reset editor parameters
        this->pInstrument  = NULL;
        this->sTypeName    = "";
        this->sTypeVersion = "";
        dmsg(1,("Instrument editor '%s' returned with exit status %d\n", Name().c_str(), iResult));
        // notify all registered listeners
        std::for_each(
            listeners.begin(), listeners.end(),
            std::bind2nd(std::mem_fun(&InstrumentEditorListener::OnInstrumentEditorQuit), this)
        );
        // done
        return iResult;
    }

    void InstrumentEditor::SendNoteOnToEditor(uint8_t Key, uint8_t /*Velocity*/) {
        if (Key >= MIDI_KEYS) return;
        atomic_inc( &((atomic_t*)pNoteIsActive)[Key] );
        atomic_inc( &((atomic_t*)pNoteChanged)[Key] );
        atomic_inc( (atomic_t*)pNotesChanged );
    }

    void InstrumentEditor::SendNoteOffToEditor(uint8_t Key, uint8_t /*Velocity*/) {
        if (Key >= MIDI_KEYS) return;
        atomic_dec( &((atomic_t*)pNoteIsActive)[Key] );
        atomic_inc( &((atomic_t*)pNoteChanged)[Key] );
        atomic_inc( (atomic_t*)pNotesChanged );
    }

    bool InstrumentEditor::NotesChanged() {
        int c = atomic_read( (atomic_t*)pNotesChanged );
        atomic_sub(c, (atomic_t*)pNotesChanged );
        return c;
    }

    bool InstrumentEditor::NoteChanged(uint8_t Key) {
        int c = atomic_read( &((atomic_t*)pNoteChanged)[Key] );
        atomic_sub(c, &((atomic_t*)pNoteChanged)[Key] );
        return c;
    }

    bool InstrumentEditor::NoteIsActive(uint8_t Key) {
        return atomic_read( &((atomic_t*)pNoteIsActive)[Key] );
    }

    void InstrumentEditor::AddListener(InstrumentEditorListener* pListener) {
        listeners.insert(pListener);
    }

    void InstrumentEditor::RemoveListener(InstrumentEditorListener* pListener) {
        listeners.erase(pListener);
    }

    void InstrumentEditor::NotifySamplesToBeRemoved(std::set<void*> Samples) {
        for ( // notify all registered listeners
            std::set<InstrumentEditorListener*>::iterator iter = listeners.begin();
            iter != listeners.end(); iter++
        ) (*iter)->OnSamplesToBeRemoved(Samples, this);
    }

    void InstrumentEditor::NotifySamplesRemoved() {
        for ( // notify all registered listeners
            std::set<InstrumentEditorListener*>::iterator iter = listeners.begin();
            iter != listeners.end(); iter++
        ) (*iter)->OnSamplesRemoved(this);
    }

    void InstrumentEditor::NotifyDataStructureToBeChanged(void* pStruct, String sStructType) {
        for ( // notify all registered listeners
            std::set<InstrumentEditorListener*>::iterator iter = listeners.begin();
            iter != listeners.end(); iter++
        ) (*iter)->OnDataStructureToBeChanged(pStruct, sStructType, this);
    }

    void InstrumentEditor::NotifyDataStructureChanged(void* pStruct, String sStructType) {
        for ( // notify all registered listeners
            std::set<InstrumentEditorListener*>::iterator iter = listeners.begin();
            iter != listeners.end(); iter++
        ) (*iter)->OnDataStructureChanged(pStruct, sStructType, this);
    }

    void InstrumentEditor::NotifySampleReferenceChanged(void* pOldSample, void* pNewSample) {
        for ( // notify all registered listeners
            std::set<InstrumentEditorListener*>::iterator iter = listeners.begin();
            iter != listeners.end(); iter++
        ) (*iter)->OnSampleReferenceChanged(pOldSample, pNewSample, this);
    }

} // namespace LinuxSampler
