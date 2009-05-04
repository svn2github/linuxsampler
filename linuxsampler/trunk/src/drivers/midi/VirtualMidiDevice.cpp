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

    struct VirtualMidiDevice::private_data_t {
        atomic_t notesChanged; // whether some key changed at all
        atomic_t pNoteChanged[MIDI_KEYS]; // which key(s) changed
        atomic_t pNoteIsActive[MIDI_KEYS]; // status of each key (either active or inactive)
        atomic_t pNoteOnVelocity[MIDI_KEYS];
        atomic_t pNoteOffVelocity[MIDI_KEYS];
        RingBuffer<VirtualMidiDevice::event_t,false> events;

        private_data_t() : events(MAX_EVENTS, 0) {}
    };

    VirtualMidiDevice::VirtualMidiDevice() : p(new private_data_t) {
        atomic_t zero = ATOMIC_INIT(0);
        atomic_t defaultVelocity = ATOMIC_INIT(127);
        p->notesChanged = zero;
        for (int i = 0; i < MIDI_KEYS; i++) {
            p->pNoteChanged[i]  = zero;
            p->pNoteIsActive[i] = zero;
            p->pNoteOnVelocity[i] = defaultVelocity;
            p->pNoteOffVelocity[i] = defaultVelocity;
        }
    }

    VirtualMidiDevice::~VirtualMidiDevice() {
        delete p;
    }

    bool VirtualMidiDevice::SendNoteOnToSampler(uint8_t Key, uint8_t Velocity) {
        if (Key >= MIDI_KEYS || Velocity > 127) return false;
        event_t ev = { EVENT_TYPE_NOTEON, Key, Velocity };
        if (p->events.write_space() <= 0) return false;
        p->events.push(&ev);
        return true;
    }

    bool VirtualMidiDevice::SendNoteOffToSampler(uint8_t Key, uint8_t Velocity) {
        if (Key >= MIDI_KEYS || Velocity > 127) return false;
        event_t ev = { EVENT_TYPE_NOTEOFF, Key, Velocity };
        if (p->events.write_space() <= 0) return false;
        p->events.push(&ev);
        return true;
    }

    bool VirtualMidiDevice::GetMidiEventFromDevice(event_t& Event) {
        return (p->events.pop(&Event) > 0);
    }

    bool VirtualMidiDevice::NotesChanged() {
        int c = atomic_read( &p->notesChanged );
        atomic_sub(c, &p->notesChanged );
        return c;
    }

    bool VirtualMidiDevice::NoteChanged(uint8_t Key) {
        int c = atomic_read( &(p->pNoteChanged)[Key] );
        atomic_sub(c, &(p->pNoteChanged)[Key] );
        return c;
    }

    bool VirtualMidiDevice::NoteIsActive(uint8_t Key) {
        return atomic_read( &(p->pNoteIsActive)[Key] );
    }

    uint8_t VirtualMidiDevice::NoteOnVelocity(uint8_t Key) {
        return atomic_read( &(p->pNoteOnVelocity)[Key] );
    }

    uint8_t VirtualMidiDevice::NoteOffVelocity(uint8_t Key) {
        return atomic_read( &(p->pNoteOffVelocity)[Key] );
    }

    void VirtualMidiDevice::SendNoteOnToDevice(uint8_t Key, uint8_t Velocity) {
        if (Key >= MIDI_KEYS) return;
        atomic_set( &(p->pNoteOnVelocity)[Key], Velocity );
        atomic_inc( &(p->pNoteIsActive)[Key] );
        atomic_inc( &(p->pNoteChanged)[Key] );
        atomic_inc( &p->notesChanged );
    }

    void VirtualMidiDevice::SendNoteOffToDevice(uint8_t Key, uint8_t Velocity) {
        if (Key >= MIDI_KEYS) return;
        atomic_set( &(p->pNoteOffVelocity)[Key], Velocity );
        atomic_dec( &(p->pNoteIsActive)[Key] );
        atomic_inc( &(p->pNoteChanged)[Key] );
        atomic_inc( &p->notesChanged );
    }

} // namespace LinuxSampler
