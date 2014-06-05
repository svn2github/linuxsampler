/*
 * Copyright (c) 2014 Christian Schoenebeck
 *
 * http://www.linuxsampler.org
 *
 * This file is part of LinuxSampler and released under the same terms.
 * See README file for details.
 */

#include "InstrumentScriptVM.h"
#include "../AbstractEngineChannel.h"

namespace LinuxSampler {

    // circumvents a bug in GCC 4.x which causes a sizeof() expression applied
    // on a class member to throw a compiler error, i.e. with GCC 4.4:
    // "object missing in reference to 'LinuxSampler::AbstractEngineChannel::ControllerTable'")
    // or with GCC 4.0:
    // "invalid use of non-static data member 'LinuxSampler::AbstractEngineChannel::ControllerTable'"
    #define _MEMBER_SIZEOF(T_Class, Member) sizeof(((T_Class*)NULL)->Member)

    InstrumentScriptVM::InstrumentScriptVM() : m_event(NULL) {
        m_CC.size = _MEMBER_SIZEOF(AbstractEngineChannel, ControllerTable);
        m_CC_NUM = DECLARE_VMINT(m_cause, class Event, Param.CC.Controller);
        m_EVENT_NOTE = DECLARE_VMINT(m_cause, class Event, Param.Note.Key);
        m_EVENT_VELOCITY = DECLARE_VMINT(m_cause, class Event, Param.Note.Velocity);
    }

    VMExecStatus_t InstrumentScriptVM::exec(VMParserContext* parserCtx, ScriptEvent* event) {
        AbstractEngineChannel* pEngineChannel =
            static_cast<AbstractEngineChannel*>(event->cause.pEngineChannel);

        // prepare built-in script variables for script execution
        m_cause = &event->cause;
        m_CC.data = (int8_t*) &pEngineChannel->ControllerTable[0];

        // if script is in start condition, then do mandatory MIDI event
        // preprocessing tasks, which essentially means updating i.e. controller
        // table with new CC value in case of a controller event, because the
        // script might access the new CC value
        if (!event->executionSlices) {
            switch (m_cause->Type) {
                case Event::type_control_change:
                    pEngineChannel->ControllerTable[m_cause->Param.CC.Controller] =
                        m_cause->Param.CC.Value;
                    break;
                case Event::type_channel_pressure:
                    pEngineChannel->ControllerTable[CTRL_TABLE_IDX_AFTERTOUCH] =
                        m_cause->Param.ChannelPressure.Value;
                    break;
                case Event::type_pitchbend:
                    pEngineChannel->ControllerTable[CTRL_TABLE_IDX_PITCHBEND] =
                        m_cause->Param.Pitch.Pitch;
                    break;
            }
        }

        // run the script handler(s)
        VMExecStatus_t res = VM_EXEC_NOT_RUNNING;
        while (event->handlers[event->currentHandler]) {
            res = ScriptVM::exec(
                parserCtx, event->execCtx, event->handlers[event->currentHandler++]
            );
            event->executionSlices++;
            if (res & VM_EXEC_SUSPENDED || res & VM_EXEC_ERROR) return res;
        }

        return res;
    }

    std::map<String,VMIntRelPtr*> InstrumentScriptVM::builtInIntVariables() {
        // first get buil-in integer variables of derived VM class
        std::map<String,VMIntRelPtr*> m = ScriptVM::builtInIntVariables();

        // now add own built-in variables
        m["$CC_NUM"] = &m_CC_NUM;
        m["$EVENT_NOTE"] = &m_EVENT_NOTE;
        m["$EVENT_VELOCITY"] = &m_EVENT_VELOCITY;
//         m["$POLY_AT_NUM"] = &m_POLY_AT_NUM;

        return m;
    }

    std::map<String,VMInt8Array*> InstrumentScriptVM::builtInIntArrayVariables() {
        // first get buil-in integer array variables of derived VM class
        std::map<String,VMInt8Array*> m = ScriptVM::builtInIntArrayVariables();

        // now add own built-in variables
        m["%CC"] = &m_CC;
        //m["%KEY_DOWN"] = &m_KEY_DOWN;
        //m["%POLY_AT"] = &m_POLY_AT;

        return m;
    }

    std::map<String,int> InstrumentScriptVM::builtInConstIntVariables() {
        // first get buil-in integer variables of derived VM class
        std::map<String,int> m = ScriptVM::builtInConstIntVariables();

        m["$VCC_MONO_AT"] = CTRL_TABLE_IDX_AFTERTOUCH;
        m["$VCC_PITCH_BEND"] = CTRL_TABLE_IDX_PITCHBEND;

        return m;
    }

} // namespace LinuxSampler
