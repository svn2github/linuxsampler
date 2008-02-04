/*
    Copyright (C) 2008 Christian Schoenebeck
 */

#ifndef LS_VIRTUALMIDIDEVICE_H
#define LS_VIRTUALMIDIDEVICE_H

#include "../../common/global.h"

namespace LinuxSampler {

/**
 * Light-weight MIDI interface (for MIDI in & out) intended to be used by
 * pure software MIDI "devices", that is e.g. a graphical virtual MIDI
 * keyboard in an instrument editor or in a sampler frontend. This class
 * should not be used for regular MIDI input device drivers for the sampler.
 * This primitive interface by design doesn't care about jitter, fast event
 * delivery or masses and masses of events in a short time!
 */
class VirtualMidiDevice {
public:
    enum event_type_t {
        EVENT_TYPE_NOTEON  = 1,
        EVENT_TYPE_NOTEOFF = 2
    };

    struct event_t {
        event_type_t Type;
        uint8_t      Key;
        uint8_t      Velocity;
    };

    /////////////////////////////////////////////////////////////////
    // Device methods
    //     (called by the VirtualMidiDevice implementation)

    /**
     * Sends a MIDI @e note @e on event to the sampler.
     *
     * @returns true on success, false if internal FIFO full
     *          (or provided values invalid)
     */
    bool SendNoteOnToSampler(uint8_t Key, uint8_t Velocity);

    /**
     * Sends a MIDI @e note @e off event to the sampler.
     *
     * @returns true on success, false if internal FIFO full
     *          (or provided values invalid)
     */
    bool SendNoteOffToSampler(uint8_t Key, uint8_t Velocity);

    /**
     * Can be called by the virtual MIDI device to check whether a new note
     * on or note off MIDI event arrived to the sampler during the last
     * call to this method. So this is a asynchronously, "polling" based
     * communication mechanism, which works in conjunction with the
     * NoteIsActive() method call.
     */
    bool NotesChanged();

    /**
     * Can be called by the virtual MIDI device to check whether a new note
     * on or note off MIDI event arrived to the sampler for @a Key during
     * the last call to this method. So this is a asynchronously,
     * "polling" based communication mechanism, which works in
     * conjunction with the NoteIsActive() method call.
     */
    bool NoteChanged(uint8_t Key);

    /**
     * Can be called by the virtual MIDI device to check which key / note
     * is currently active by the sampler, e.g. to highlight the
     * respective keys on a graphical virtual keyboard.
     *
     * @see NotesChanged(), NoteChanged()
     */
    bool NoteIsActive(uint8_t Key);

    /**
     * Returns the velocity of the @e last note on event. No FIFO is used!
     */
    uint8_t NoteOnVelocity(uint8_t Key);

    /**
     * Returns the velocity of the @e last note off event. No FIFO is used!
     */
    uint8_t NoteOffVelocity(uint8_t Key);

    /////////////////////////////////////////////////////////////////
    // Sampler methods
    //     (usually only called by the Sampler)

    /**
     * Informs the virtual MIDI device that a @e note @e on event occured
     * (e.g. caused by a MIDI keyboard connected to the sampler).
     * Communication acts asynchronously, that is this method call doesn't
     * lock in any way and returns immediately. It is thus realtime safe.
     *
     * @e Note: this method is usually only called by the sampler.
     *
     * @see ActiveNotesChanged(), NoteIsActive()
     */
    void SendNoteOnToDevice(uint8_t Key, uint8_t Velocity);

    /**
     * Informs the virtual MIDI device that a @e note @e off event occured
     * (e.g. caused by a MIDI keyboard connected to the sampler).
     * Communication acts asynchronously, that is this method call doesn't
     * lock in any way and returns immediately. It is thus realtime safe.
     *
     * @e Note: this method is usually only called by the sampler.
     *
     * @see ActiveNotesChanged(), NoteIsActive()
     */
    void SendNoteOffToDevice(uint8_t Key, uint8_t Velocity);

    /**
     * Gets the next pending MIDI event from the virtual MIDI device by
     * using a lockfree FIFO.
     *
     * @e Note: this method is usually only called by the sampler.
     *
     * @param Event - destination for writing the next event to
     * @returns true on success, false if no event pending
     */
    bool GetMidiEventFromDevice(event_t& Event);

    /**
     * Constructor
     */
    VirtualMidiDevice();

    /**
     * Destructor
     */
    virtual ~VirtualMidiDevice();

private:
    void* pPrivateData;
};

} // namespace LinuxSampler

#endif // LS_VIRTUALMIDIDEVICE_H
