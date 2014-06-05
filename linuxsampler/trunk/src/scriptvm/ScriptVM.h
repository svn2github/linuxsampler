/*
 * Copyright (c) 2014 Christian Schoenebeck
 *
 * http://www.linuxsampler.org
 *
 * This file is part of LinuxSampler and released under the same terms.
 * See README file for details.
 */

#ifndef LS_SCRIPTVM_H
#define LS_SCRIPTVM_H

#include <iostream>
#include <vector>

#include "../common/global.h"
#include "common.h"
#include "CoreVMFunctions.h"

namespace LinuxSampler {

    class ParserContext;
    class ExecContext;

    /** @brief Core virtual machine for real-time instrument scripts.
     *
     * This is the core of the virtual machine, used for running real-time
     * instrument scripts. The core encompasses the instrument script parser,
     * generalized virtual machine and very generic built-in script functions.
     * Thus this class only provides functionalities which are yet independent
     * of the actual purpose the virtual machine is going to be used for.
     *
     * The actual use case specific functionalites (i.e. MIDI processing) is
     * then implemented by VM classes which are derived from this generalized
     * ScriptVM class.
     *
     * This class is re-entrant safe, but not thread safe. So you can share one
     * instance of this class between multiple (native) threads, but you @b must
     * @b not execute methods of the same class instance simultaniously from
     * different (native) threads. If you want to execute scripts simultaniously
     * multi threaded, then create a separate ScriptVM instance for each
     * (native) thread. Also note that one VMParserContext instance is tied to
     * exactly one ScriptVM instance. So you @b must @b not create a
     * VMParserContext with one ScriptVM instance and run it with a different
     * ScriptVM instance!
     */
    class ScriptVM : public VMFunctionProvider {
    public:
        ScriptVM();
        virtual ~ScriptVM();
        VMParserContext* loadScript(const String& s);
        VMParserContext* loadScript(std::istream* is);
        void dumpParsedScript(VMParserContext* context);
        VMExecContext* createExecContext(VMParserContext* parserContext);
        VMExecStatus_t exec(VMParserContext* parserContext, VMExecContext* execContex, VMEventHandler* handler);
        VMFunction* functionByName(const String& name) OVERRIDE;
        std::map<String,VMIntRelPtr*> builtInIntVariables() OVERRIDE;
        std::map<String,VMInt8Array*> builtInIntArrayVariables() OVERRIDE;
        std::map<String,int> builtInConstIntVariables() OVERRIDE;

        VMParserContext* currentVMParserContext(); //TODO: should be protected (only usable during exec() calls, intended only for VMFunctions)
        VMExecContext* currentVMExecContext(); //TODO: should be protected (only usable during exec() calls, intended only for VMFunctions)
    protected:
        ParserContext* m_parserContext;
        CoreVMFunction_message fnMessage;
        CoreVMFunction_exit fnExit;
        CoreVMFunction_wait fnWait;
    };

} // namespace LinuxSampler

#endif // LS_INSTRUMENTSCRIPTVM_H
