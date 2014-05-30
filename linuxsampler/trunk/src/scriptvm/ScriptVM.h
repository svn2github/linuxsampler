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

    class ScriptVM : public VMFunctionProvider {
    public:
        ScriptVM();
        virtual ~ScriptVM();
        void loadScript(const String& s);
        void loadScript(std::istream* is);
        std::vector<ParserIssue> issues() const;
        std::vector<ParserIssue> errors() const;
        std::vector<ParserIssue> warnings() const;
        void dumpParsedScript();
        VMExecContext* createExecContext();
        VMEventHandler* eventHandler(uint index);
        VMEventHandler* eventHandlerByName(const String& name);
        VMExecStatus_t exec(VMEventHandler* handler, VMExecContext* execContex);
        VMExecContext* currentVMExecContext();
        VMFunction* functionByName(const String& name);
    protected:
        ParserContext* m_context;
        CoreVMFunction_message fnMessage;
        CoreVMFunction_exit fnExit;
        CoreVMFunction_wait fnWait;
    };

} // namespace LinuxSampler

#endif // LS_INSTRUMENTSCRIPTVM_H
