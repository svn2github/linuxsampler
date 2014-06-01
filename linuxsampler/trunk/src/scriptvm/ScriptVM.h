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

    class ScriptVM : public VMFunctionProvider {
    public:
        ScriptVM();
        virtual ~ScriptVM();
        VMParserContext* loadScript(const String& s);
        VMParserContext* loadScript(std::istream* is);
        void dumpParsedScript(VMParserContext* context);
        VMExecContext* createExecContext(VMParserContext* parserContext);
        VMExecStatus_t exec(VMParserContext* parserContext, VMExecContext* execContex, VMEventHandler* handler);
        VMFunction* functionByName(const String& name);

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
