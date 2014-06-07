/*
 * Copyright (c) 2014 Christian Schoenebeck
 *
 * http://www.linuxsampler.org
 *
 * This file is part of LinuxSampler and released under the same terms.
 * See README file for details.
 */

#include "InstrumentScriptVMFunctions.h"
#include "InstrumentScriptVM.h"
#include "../AbstractEngineChannel.h"

namespace LinuxSampler {

    InstrumentScriptVMFunction_play_note::InstrumentScriptVMFunction_play_note(InstrumentScriptVM* parent)
        : m_vm(parent)
    {
    }

    VMFnResult* InstrumentScriptVMFunction_play_note::exec(VMFnArgs* args) {
        int note = args->arg(0)->asInt()->evalInt();
        int velocity = (args->argsCount() >= 2) ? args->arg(1)->asInt()->evalInt() : 127;
        int sampleoffset = (args->argsCount() >= 3) ? args->arg(2)->asInt()->evalInt() : 0;
        int duration = (args->argsCount() >= 4) ? args->arg(3)->asInt()->evalInt() : 0; //TODO: once -1 is implemented, it might be a better default value instead of 0

        if (note < 0 || note > 127) {
            errMsg("play_note(): argument 1 is an invalid note number");
            return errorResult(-1);
        }

        if (velocity < 0 || velocity > 127) {
            errMsg("play_note(): argument 2 is an invalid velocity value");
            return errorResult(-1);
        }

        if (sampleoffset < 0) {
            errMsg("play_note(): argument 3 may not be a negative sample offset");
            return errorResult(-1);
        } else if (sampleoffset != 0) {
            wrnMsg("play_note(): argument 3 does not support a sample offset other than 0 yet");
        }

        if (duration < -1) {
            errMsg("play_note(): argument 4 must be a duration value of at least -1 or higher");
            return errorResult(-1);
        } else if (duration == -1) {
            wrnMsg("play_note(): argument 4 does not support special value -1 as duration yet");
        } else if (duration != 0) {
            wrnMsg("play_note(): argument 4 does not support any other value as 0 as duration yet");
        }

        AbstractEngineChannel* pEngineChannel =
            static_cast<AbstractEngineChannel*>(m_vm->m_event->cause.pEngineChannel);

        Event e = m_vm->m_event->cause;
        e.Type = Event::type_note_on;
        e.Param.Note.Key = note;
        e.Param.Note.Velocity = velocity;
        e.Format = {}; // init format speific stuff with zero

        int id = pEngineChannel->ScheduleEvent(&e, duration);

        return successResult(id);
    }

    InstrumentScriptVMFunction_set_controller::InstrumentScriptVMFunction_set_controller(InstrumentScriptVM* parent)
        : m_vm(parent)
    {
    }

    VMFnResult* InstrumentScriptVMFunction_set_controller::exec(VMFnArgs* args) {
        int controller = args->arg(0)->asInt()->evalInt();
        int value      = args->arg(1)->asInt()->evalInt();

        AbstractEngineChannel* pEngineChannel =
            static_cast<AbstractEngineChannel*>(m_vm->m_event->cause.pEngineChannel);

        Event e = m_vm->m_event->cause;
        e.Format = {}; // init format speific stuff with zero
        if (controller == CTRL_TABLE_IDX_AFTERTOUCH) {
            e.Type = Event::type_channel_pressure;
            e.Param.ChannelPressure.Value = value & 127;
        } else if (controller == CTRL_TABLE_IDX_PITCHBEND) {
            e.Type = Event::type_pitchbend;
            e.Param.Pitch.Pitch = value;
        } else if (controller >= 0 && controller <= 127) {
            e.Type = Event::type_control_change;
            e.Param.CC.Controller = controller;
            e.Param.CC.Value = value;
        } else {
            errMsg("set_controller(): argument 1 is an invalid controller");
            return errorResult();
        }

        int id = pEngineChannel->ScheduleEvent(&e, 0);

        return successResult(id);
    }    

    InstrumentScriptVMFunction_ignore_event::InstrumentScriptVMFunction_ignore_event(InstrumentScriptVM* parent)
        : m_vm(parent)
    {
    }

    VMFnResult* InstrumentScriptVMFunction_ignore_event::exec(VMFnArgs* args) {
        int id = args->arg(0)->asInt()->evalInt();
        if (id < 0) {
            wrnMsg("ignore_event(): argument may not be a negative event ID");
            return successResult();
        }

        AbstractEngineChannel* pEngineChannel =
            static_cast<AbstractEngineChannel*>(m_vm->m_event->cause.pEngineChannel);

        pEngineChannel->IgnoreEvent(id);

        return successResult();
    }

    InstrumentScriptVMFunction_ignore_controller::InstrumentScriptVMFunction_ignore_controller(InstrumentScriptVM* parent)
        : m_vm(parent)
    {
    }

    VMFnResult* InstrumentScriptVMFunction_ignore_controller::exec(VMFnArgs* args) {
        int id = (args->argsCount() >= 1) ? args->arg(0)->asInt()->evalInt() : m_vm->m_event->id;
        if (id < 0) {
            wrnMsg("ignore_controller(): argument may not be a negative event ID");
            return successResult();
        }

        AbstractEngineChannel* pEngineChannel =
            static_cast<AbstractEngineChannel*>(m_vm->m_event->cause.pEngineChannel);

        pEngineChannel->IgnoreEvent(id);

        return successResult();
    }

} // namespace LinuxSampler
