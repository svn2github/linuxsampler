/*
 * Copyright (c) 2014-2016 Christian Schoenebeck
 *
 * http://www.linuxsampler.org
 *
 * This file is part of LinuxSampler and released under the same terms.
 * See README file for details.
 */

#ifndef LS_INSTRUMENT_SCRIPT_VM_H
#define LS_INSTRUMENT_SCRIPT_VM_H

#include "../../common/global.h"
#include "../../common/ConstCapacityArray.h"
#include "../../scriptvm/ScriptVM.h"
#include "Event.h"
#include "../../common/Pool.h"
#include "InstrumentScriptVMFunctions.h"

#define INSTR_SCRIPT_EVENT_GROUPS 28

namespace LinuxSampler {

    class AbstractEngineChannel;
    class InstrumentScript;

    /** @brief List of Event IDs.
     *
     * Used for built-in script functions:
     *     by_marks(), set_event_mark(), delete_event_mark()
     */
    class EventGroup : protected ConstCapacityArray<int> {
    public:
        EventGroup() : ConstCapacityArray<int>(CONFIG_MAX_EVENTS_PER_FRAGMENT), m_script(NULL) {}
        void insert(int eventID);
        void erase(int eventID);
        void setScript(InstrumentScript* pScript) { m_script = pScript; }
        inline int size() const { return ConstCapacityArray<int>::size(); }
        inline void clear() { ConstCapacityArray<int>::clear(); }
        inline int& operator[](uint index) { return ConstCapacityArray<int>::operator[](index); }
        inline const int& operator[](uint index) const { return ConstCapacityArray<int>::operator[](index); }
    protected:
        InstrumentScript* m_script;
    };

    /** @brief Real-time instrument script VM representation.
     *
     * Holds the VM representation of all event handlers of the currently loaded
     * script, ready to be executed by the sampler engine.
     *
     * Even thought scripts (or to be more specific their event handler objects)
     * are shared between sampler engine channels, the InstrumentScript struct
     * instances though are not shared. Each sampler engine channel has its own
     * instance of a InstrumentScript struct. That's important, because this
     * struct also holds engine channel local informations, for example the
     * events that occured on the respective engine channel.
     */
    struct InstrumentScript {
        VMParserContext*      parserContext; ///< VM represenation of the currently loaded script or NULL if not script was loaded. Note that it is also not NULL if parser errors occurred!
        bool                  bHasValidScript; ///< True in case there is a valid script currently loaded, false if script processing shall be skipped.
        VMEventHandler*       handlerInit; ///< VM representation of script's initilization callback or NULL if current script did not define such an init handler.
        VMEventHandler*       handlerNote; ///< VM representation of script's MIDI note on callback or NULL if current script did not define such an event handler.
        VMEventHandler*       handlerRelease; ///< VM representation of script's MIDI note off callback or NULL if current script did not define such an event handler.
        VMEventHandler*       handlerController; ///< VM representation of script's MIDI controller callback or NULL if current script did not define such an event handler.
        Pool<ScriptEvent>*    pEvents; ///< Pool of all available script execution instances. ScriptEvents available to be allocated from the Pool are currently unused / not executiong, whereas the ScriptEvents allocated on the list are currently suspended / have not finished execution yet (@see pKeyEvents).
        RTList<ScriptEvent>*  pKeyEvents[128]; ///< Stores previously finished executed "note on" script events for the respective active note/key as long as the key/note is active. This is however only done if there is a "note" script event handler and a "release" script event handler defined in the script and both handlers use (reference) polyphonic variables. If that is not the case, then this list is not used at all. So the purpose of pKeyEvents is only to implement preserving/passing polyphonic variable data from "on note .. end on" script block to the respective "on release .. end on" script block.
        RTAVLTree<ScriptEvent> suspendedEvents; ///< Contains pointers to all suspended events, sorted by time when those script events are to be resumed next.
        AbstractEngineChannel* pEngineChannel;
        String                code; ///< Source code of the instrument script. Used in case the sampler engine is changed, in that case a new ScriptVM object is created for the engine and VMParserContext object for this script needs to be recreated as well. Thus the script is then parsed again by passing the source code to recreate the parser context.
        EventGroup            eventGroups[INSTR_SCRIPT_EVENT_GROUPS]; ///< Used for built-in script functions: by_event_marks(), set_event_mark(), delete_event_mark().

        InstrumentScript(AbstractEngineChannel* pEngineChannel);
        ~InstrumentScript();

        void load(const String& text);
        void unload();
        void resetAll();
        void resetEvents();
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
        VMInt8Array  m_KEY_DOWN;
        //VMIntArray m_POLY_AT; //TODO: ...
        //int m_POLY_AT_NUM; //TODO: ...

        // buil-in script functions
        InstrumentScriptVMFunction_play_note m_fnPlayNote;
        InstrumentScriptVMFunction_set_controller m_fnSetController;
        InstrumentScriptVMFunction_ignore_event m_fnIgnoreEvent;
        InstrumentScriptVMFunction_ignore_controller m_fnIgnoreController;
        InstrumentScriptVMFunction_note_off m_fnNoteOff;
        InstrumentScriptVMFunction_set_event_mark m_fnSetEventMark;
        InstrumentScriptVMFunction_delete_event_mark m_fnDeleteEventMark;
        InstrumentScriptVMFunction_by_marks m_fnByMarks;

        friend class InstrumentScriptVMFunction_play_note;
        friend class InstrumentScriptVMFunction_set_controller;
        friend class InstrumentScriptVMFunction_ignore_event;
        friend class InstrumentScriptVMFunction_ignore_controller;
        friend class InstrumentScriptVMFunction_note_off;
        friend class InstrumentScriptVMFunction_set_event_mark;
        friend class InstrumentScriptVMFunction_delete_event_mark;
        friend class InstrumentScriptVMFunction_by_marks;
    };

} // namespace LinuxSampler

#endif // LS_INSTRUMENT_SCRIPT_VM_H
