/*
 * Copyright (c) 2014 Christian Schoenebeck
 *
 * http://www.linuxsampler.org
 *
 * This file is part of LinuxSampler and released under the same terms.
 * See README file for details.
 */

#ifndef LS_INSTRUMENT_SCRIPT_VM_H
#define LS_INSTRUMENT_SCRIPT_VM_H

#include "../../common/global.h"
#include "../../scriptvm/ScriptVM.h"
#include "Event.h"
#include "../../common/Pool.h"
#include "InstrumentScriptVMFunctions.h"

namespace LinuxSampler {

    class AbstractEngineChannel;

    /** @brief Real-time instrument script VM representation.
     *
     * Holds the VM representation of all event handlers of the currently loaded
     * script, ready to be executed by the sampler engine.
     */
    struct InstrumentScript {
        VMParserContext*      parserContext; ///< VM represenation of the currently loaded script or NULL if not script was loaded. Note that it is also not NULL if parser errors occurred!
        bool                  bHasValidScript; ///< True in case there is a valid script currently loaded, false if script processing shall be skipped.
        VMEventHandler*       handlerInit; ///< VM representation of script's initilization callback or NULL if current script did not define such an init handler.
        VMEventHandler*       handlerNote; ///< VM representation of script's MIDI note on callback or NULL if current script did not define such an event handler.
        VMEventHandler*       handlerRelease; ///< VM representation of script's MIDI note off callback or NULL if current script did not define such an event handler.
        VMEventHandler*       handlerController; ///< VM representation of script's MIDI controller callback or NULL if current script did not define such an event handler.
        Pool<ScriptEvent>*    pEvents; ///< Pool of all available script execution instances. ScriptEvents available to be allocated from the Pool are currently unused / not executiong, whereas the ScriptEvents allocated on the list are currently suspended / have not finished execution yet.
        AbstractEngineChannel* pEngineChannel;
        String                code; ///< Source code of the instrument script. Used in case the sampler engine is changed, in that case a new ScriptVM object is created for the engine and VMParserContext object for this script needs to be recreated as well. Thus the script is then parsed again by passing the source code to recreate the parser context.

        InstrumentScript(AbstractEngineChannel* pEngineChannel) {
            parserContext = NULL;
            bHasValidScript = false;
            handlerInit = NULL;
            handlerNote = NULL;
            handlerRelease = NULL;
            handlerController = NULL;
            pEvents = NULL;
            this->pEngineChannel = pEngineChannel;
        }

        ~InstrumentScript() {
            resetAll();
        }

        void load(const String& text);
        void unload();
        void resetAll();
    };

    /** @brief Real-time instrument script virtual machine.
     *
     * Extends the core ScriptVM implementation with MIDI specific built-in
     * script functions and MIDI specific built-in script variables required
     * for MIDI processing by instrument script for all sampler engine
     * implementations (sampler formats) of this sampler.
     *
     * Note that this class is currently re-entrant safe, but @b not thread
     * safe! See also comments of base class ScriptVM regarding this issue.
     */
    class InstrumentScriptVM : public ScriptVM {
    public:
        InstrumentScriptVM();
        VMExecStatus_t exec(VMParserContext* parserCtx, ScriptEvent* event);
        VMFunction* functionByName(const String& name) OVERRIDE;
        std::map<String,VMIntRelPtr*> builtInIntVariables() OVERRIDE;
        std::map<String,VMInt8Array*> builtInIntArrayVariables() OVERRIDE;
        std::map<String,int> builtInConstIntVariables() OVERRIDE;
    protected:
        ScriptEvent* m_event; ///< The event currently executed by exec().

        // buil-in script variables
        VMInt8Array m_CC;
        VMInt8RelPtr m_CC_NUM;
        VMIntRelPtr  m_EVENT_ID;
        VMInt8RelPtr m_EVENT_NOTE;
        VMInt8RelPtr m_EVENT_VELOCITY;
        //VMIntArray m_KEY_DOWN; //TODO: ...
        //VMIntArray m_POLY_AT; //TODO: ...
        //int m_POLY_AT_NUM; //TODO: ...

        // buil-in script functions
        InstrumentScriptVMFunction_play_note m_fnPlayNote;
        InstrumentScriptVMFunction_set_controller m_fnSetController;
        InstrumentScriptVMFunction_ignore_event m_fnIgnoreEvent;
        InstrumentScriptVMFunction_ignore_controller m_fnIgnoreController;

        friend class InstrumentScriptVMFunction_play_note;
        friend class InstrumentScriptVMFunction_set_controller;
        friend class InstrumentScriptVMFunction_ignore_event;
        friend class InstrumentScriptVMFunction_ignore_controller;
    };

} // namespace LinuxSampler

#endif // LS_INSTRUMENT_SCRIPT_VM_H
