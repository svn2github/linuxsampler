/*
    Copyright (C) 2008 Christian Schoenebeck
 */

#include "VirtualMidiDevice.h"

#include "../../common/global_private.h"
#include "../../common/atomic.h"
#include "../../common/RingBuffer.h"

#define MIDI_KEYS	128

// assuming VirtualMidiDevice implementation is only controlled
// by mouse (and the user not being Billy the Kid)
#define MAX_EVENTS  12

namespace LinuxSampler {

    struct _private_data_t {
        atomic_t notesChanged; // whether some key changed at all
        atomic_t pNoteChanged[MIDI_KEYS]; // which key(s) changed
        atomic_t pNoteIsActive[MIDI_KEYS]; // status of each key (either active or inactive)
        RingBuffer<VirtualMidiDevice::event_t,false> events;

        _private_data_t() : events(MAX_EVENTS, 0) {}
    };

    VirtualMidiDevice::VirtualMidiDevice() {
        _private_data_t* p = new _private_data_t;
        pPrivateData = p;
        atomic_t zero = ATOMIC_INIT(0);
        p->notesChanged = zero;
        for (int i = 0; i < MIDI_KEYS; i++) {
            p->pNoteChanged[i]  = zero;
            p->pNoteIsActive[i] = zero;
        }
    }

    VirtualMidiDevice::~VirtualMidiDevice() {
        if (pPrivateData) delete (_private_data_t*)pPrivateData;
    }

    bool VirtualMidiDevice::SendNoteOnToSampler(uint8_t Key, uint8_t Velocity) {
        if (Key >= MIDI_KEYS || Velocity > 127) return false;
        _private_data_t* p = (_private_data_t*)pPrivateData;
        event_t ev = { EVENT_TYPE_NOTEON, Key, Velocity };
        if (p->events.write_space() <= 0) return false;
        p->events.push(&ev);
        return true;
    }

    bool VirtualMidiDevice::SendNoteOffToSampler(uint8_t Key, uint8_t Velocity) {
        if (Key >= MIDI_KEYS || Velocity > 127) return false;
        _private_data_t* p = (_private_data_t*)pPrivateData;
        event_t ev = { EVENT_TYPE_NOTEOFF, Key, Velocity };
        if (p->events.write_space() <= 0) return false;
        p->events.push(&ev);
        return true;
    }

    bool VirtualMidiDevice::GetMidiEventFromDevice(event_t& Event) {
        _private_data_t* p = (_private_data_t*)pPrivateData;
        return (p->events.pop(&Event) > 0);
    }

    bool VirtualMidiDevice::NotesChanged() {
        _private_data_t* p = (_private_data_t*)pPrivateData;
        int c = atomic_read( &p->notesChanged );
        atomic_sub(c, &p->notesChanged );
        return c;
    }

    bool VirtualMidiDevice::NoteChanged(uint8_t Key) {
        _private_data_t* p = (_private_data_t*)pPrivateData;
        int c = atomic_read( &(p->pNoteChanged)[Key] );
        atomic_sub(c, &(p->pNoteChanged)[Key] );
        return c;
    }

    bool VirtualMidiDevice::NoteIsActive(uint8_t Key) {
        _private_data_t* p = (_private_data_t*)pPrivateData;
        return atomic_read( &(p->pNoteIsActive)[Key] );
    }

    void VirtualMidiDevice::SendNoteOnToDevice(uint8_t Key, uint8_t /*Velocity*/) {
        if (Key >= MIDI_KEYS) return;
        _private_data_t* p = (_private_data_t*)pPrivateData;
        atomic_inc( &(p->pNoteIsActive)[Key] );
        atomic_inc( &(p->pNoteChanged)[Key] );
        atomic_inc( &p->notesChanged );
    }

    void VirtualMidiDevice::SendNoteOffToDevice(uint8_t Key, uint8_t /*Velocity*/) {
        if (Key >= MIDI_KEYS) return;
        _private_data_t* p = (_private_data_t*)pPrivateData;
        atomic_dec( &(p->pNoteIsActive)[Key] );
        atomic_inc( &(p->pNoteChanged)[Key] );
        atomic_inc( &p->notesChanged );
    }

} // namespace LinuxSampler
