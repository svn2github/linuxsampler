/*
 * Copyright (c) 2014 Christian Schoenebeck
 *
 * http://www.linuxsampler.org
 *
 * This file is part of LinuxSampler and released under the same terms.
 * See README file for details.
 */

#ifndef LS_INSTRSCRIPTVMFUNCTIONS_H
#define LS_INSTRSCRIPTVMFUNCTIONS_H

#include "../../common/global.h"
#include "../../scriptvm/CoreVMFunctions.h"

namespace LinuxSampler {

    class InstrumentScriptVM;

    class InstrumentScriptVMFunction_play_note : public VMIntResultFunction {
    public:
        InstrumentScriptVMFunction_play_note(InstrumentScriptVM* parent);
        int minRequiredArgs() const { return 1; }
        int maxAllowedArgs() const { return 4; }
        bool acceptsArgType(int iArg, ExprType_t type) const { return type == INT_EXPR;}
        ExprType_t argType(int iArg) const { return INT_EXPR; }
        VMFnResult* exec(VMFnArgs* args);
    protected:
        InstrumentScriptVM* m_vm;
    };

    class InstrumentScriptVMFunction_ignore_event : public VMEmptyResultFunction {
    public:
        InstrumentScriptVMFunction_ignore_event(InstrumentScriptVM* parent);
        int minRequiredArgs() const { return 1; }
        int maxAllowedArgs() const { return 1; }
        bool acceptsArgType(int iArg, ExprType_t type) const { return type == INT_EXPR;}
        ExprType_t argType(int iArg) const { return INT_EXPR; }
        VMFnResult* exec(VMFnArgs* args);
    protected:
        InstrumentScriptVM* m_vm;
    };

    class InstrumentScriptVMFunction_ignore_controller : public VMEmptyResultFunction {
    public:
        InstrumentScriptVMFunction_ignore_controller(InstrumentScriptVM* parent);
        int minRequiredArgs() const { return 0; }
        int maxAllowedArgs() const { return 1; }
        bool acceptsArgType(int iArg, ExprType_t type) const { return type == INT_EXPR;}
        ExprType_t argType(int iArg) const { return INT_EXPR; }
        VMFnResult* exec(VMFnArgs* args);
    protected:
        InstrumentScriptVM* m_vm;
    };

} // namespace LinuxSampler

#endif // LS_INSTRSCRIPTVMFUNCTIONS_H
