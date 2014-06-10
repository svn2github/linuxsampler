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
#include "../../common/global_private.h"
#include "AbstractInstrumentManager.h"
#include "MidiKeyboardManager.h"

namespace LinuxSampler {

    ///////////////////////////////////////////////////////////////////////
    // class 'InstrumentScript'

    /** @brief Load real-time instrument script.
     *
     * Loads the real-time instrument script given by @a text on the engine
     * channel this InstrumentScript object belongs to (defined by
     * pEngineChannel member variable). The sampler engine's resource manager is
     * used to allocate and share equivalent scripts on multiple engine
     * channels.
     *
     * @param text - source code of script
     */
    void InstrumentScript::load(const String& text) {
        dmsg(1,("Loading real-time instrument script ... "));

        // hand back old script reference and VM execution contexts
        // (if not done already)
        unload();

        code = text;

        AbstractInstrumentManager* pManager =
            dynamic_cast<AbstractInstrumentManager*>(pEngineChannel->pEngine->GetInstrumentManager());

        // get new script reference
        parserContext = pManager->scripts.Borrow(text, pEngineChannel);
        if (!parserContext->errors().empty()) {
            std::vector<ParserIssue> errors = parserContext->errors();
            std::cerr << "[ScriptVM] Could not load instrument script, there were "
                    << errors.size() << " parser errors:\n";
            for (int i = 0; i < errors.size(); ++i)
                errors[i].dump();
            return; // stop here if there were any parser errors
        }

        handlerInit = parserContext->eventHandlerByName("init");
        handlerNote = parserContext->eventHandlerByName("note");
        handlerRelease = parserContext->eventHandlerByName("release");
        handlerController = parserContext->eventHandlerByName("controller");
        bHasValidScript =
            handlerInit || handlerNote || handlerRelease || handlerController;

        // amount of script handlers each script event has to execute
        int handlerExecCount = 0;
        if (handlerNote || handlerRelease || handlerController) // only one of these are executed after "init" handler
            handlerExecCount++;

        // create script event pool (if it doesn't exist already)
        if (!pEvents)
            pEvents = new Pool<ScriptEvent>(CONFIG_MAX_EVENTS_PER_FRAGMENT);

        // create new VM execution contexts for new script
        while (!pEvents->poolIsEmpty()) {
            RTList<ScriptEvent>::Iterator it = pEvents->allocAppend();
            it->execCtx = pEngineChannel->pEngine->pScriptVM->createExecContext(
                parserContext
            );
            it->handlers = new VMEventHandler*[handlerExecCount+1];
        }
        pEvents->clear();

        dmsg(1,("Done\n"));
    }

    /** @brief Unload real-time instrument script.
     *
     * Unloads the currently used real-time instrument script and frees all
     * resources allocated for that script. The sampler engine's resource manager
     * is used to share equivalent scripts among multiple sampler channels, and
     * to deallocate the parsed script once not used on any engine channel
     * anymore.
     *
     * Calling thid method will however not clear the @c code member variable.
     * Thus, the script can be parsed again afterwards.
     */
    void InstrumentScript::unload() {
        if (parserContext)
            dmsg(1,("Unloading current instrument script.\n"));

        // free allocated VM execution contexts
        if (pEvents) {
            pEvents->clear();
            while (!pEvents->poolIsEmpty()) {
                RTList<ScriptEvent>::Iterator it = pEvents->allocAppend();
                if (it->execCtx) {
                    // free VM execution context object
                    delete it->execCtx;
                    it->execCtx = NULL;
                    // free C array of handler pointers
                    delete [] it->handlers;
                }
            }
            pEvents->clear();
        }
        // hand back VM representation of script
        if (parserContext) {
            AbstractInstrumentManager* pManager =
                dynamic_cast<AbstractInstrumentManager*>(pEngineChannel->pEngine->GetInstrumentManager());

            pManager->scripts.HandBack(parserContext, pEngineChannel);
            parserContext = NULL;
            handlerInit = NULL;
            handlerNote = NULL;
            handlerRelease = NULL;
            handlerController = NULL;
        }
        bHasValidScript = false;
    }

    /**
     * Same as unload(), but this one also empties the @c code member variable
     * to an empty string.
     */
    void InstrumentScript::resetAll() {
        unload();
        code.clear();
    }

    ///////////////////////////////////////////////////////////////////////
    // class 'InstrumentScriptVM'

    InstrumentScriptVM::InstrumentScriptVM() :
        m_event(NULL), m_fnPlayNote(this), m_fnSetController(this),
        m_fnIgnoreEvent(this), m_fnIgnoreController(this)
    {
        m_CC.size = _MEMBER_SIZEOF(AbstractEngineChannel, ControllerTable);
        m_CC_NUM = DECLARE_VMINT(m_event, class ScriptEvent, cause.Param.CC.Controller);
        m_EVENT_ID = DECLARE_VMINT(m_event, class ScriptEvent, id);
        m_EVENT_NOTE = DECLARE_VMINT(m_event, class ScriptEvent, cause.Param.Note.Key);
        m_EVENT_VELOCITY = DECLARE_VMINT(m_event, class ScriptEvent, cause.Param.Note.Velocity);
        m_KEY_DOWN.size = 128;
    }

    VMExecStatus_t InstrumentScriptVM::exec(VMParserContext* parserCtx, ScriptEvent* event) {
        AbstractEngineChannel* pEngineChannel =
            static_cast<AbstractEngineChannel*>(event->cause.pEngineChannel);

        // prepare built-in script variables for script execution
        m_event = event;
        m_CC.data = (int8_t*) &pEngineChannel->ControllerTable[0];
        m_KEY_DOWN.data = &pEngineChannel->GetMidiKeyboardManager()->KeyDown[0];

        // if script is in start condition, then do mandatory MIDI event
        // preprocessing tasks, which essentially means updating i.e. controller
        // table with new CC value in case of a controller event, because the
        // script might access the new CC value
        if (!event->executionSlices) {
            switch (event->cause.Type) {
                case Event::type_control_change:
                    pEngineChannel->ControllerTable[event->cause.Param.CC.Controller] =
                        event->cause.Param.CC.Value;
                    break;
                case Event::type_channel_pressure:
                    pEngineChannel->ControllerTable[CTRL_TABLE_IDX_AFTERTOUCH] =
                        event->cause.Param.ChannelPressure.Value;
                    break;
                case Event::type_pitchbend:
                    pEngineChannel->ControllerTable[CTRL_TABLE_IDX_PITCHBEND] =
                        event->cause.Param.Pitch.Pitch;
                    break;
            }
        }

        // run the script handler(s)
        VMExecStatus_t res = VM_EXEC_NOT_RUNNING;
        for ( ; event->handlers[event->currentHandler]; event->currentHandler++) {
            res = ScriptVM::exec(
                parserCtx, event->execCtx, event->handlers[event->currentHandler]
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
        m["$EVENT_ID"] = &m_EVENT_ID;
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
        m["%KEY_DOWN"] = &m_KEY_DOWN;
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

    VMFunction* InstrumentScriptVM::functionByName(const String& name) {
        // built-in script functions of this class
        if      (name == "play_note") return &m_fnPlayNote;
        else if (name == "set_controller") return &m_fnSetController;
        else if (name == "ignore_event") return &m_fnIgnoreEvent;
        else if (name == "ignore_controller") return &m_fnIgnoreController;

        // built-in script functions of derived VM class
        return ScriptVM::functionByName(name);
    }

} // namespace LinuxSampler
