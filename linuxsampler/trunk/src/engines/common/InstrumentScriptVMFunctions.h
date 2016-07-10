/*
 * Copyright (c) 2014 - 2016 Christian Schoenebeck
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

    class EventGroup;
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

    class InstrumentScriptVMFunction_set_controller : public VMIntResultFunction {
    public:
        InstrumentScriptVMFunction_set_controller(InstrumentScriptVM* parent);
        int minRequiredArgs() const { return 2; }
        int maxAllowedArgs() const { return 2; }
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
        bool acceptsArgType(int iArg, ExprType_t type) const;
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

    class InstrumentScriptVMFunction_note_off : public VMEmptyResultFunction {
    public:
        InstrumentScriptVMFunction_note_off(InstrumentScriptVM* parent);
        int minRequiredArgs() const { return 1; }
        int maxAllowedArgs() const { return 2; }
        bool acceptsArgType(int iArg, ExprType_t type) const;
        ExprType_t argType(int iArg) const { return INT_EXPR; }
        VMFnResult* exec(VMFnArgs* args);
    protected:
        InstrumentScriptVM* m_vm;
    };

    class InstrumentScriptVMFunction_set_event_mark : public VMEmptyResultFunction {
    public:
        InstrumentScriptVMFunction_set_event_mark(InstrumentScriptVM* parent);
        int minRequiredArgs() const { return 2; }
        int maxAllowedArgs() const { return 2; }
        bool acceptsArgType(int iArg, ExprType_t type) const { return type == INT_EXPR;}
        ExprType_t argType(int iArg) const { return INT_EXPR; }
        VMFnResult* exec(VMFnArgs* args);
    protected:
        InstrumentScriptVM* m_vm;
    };

    class InstrumentScriptVMFunction_delete_event_mark : public VMEmptyResultFunction {
    public:
        InstrumentScriptVMFunction_delete_event_mark(InstrumentScriptVM* parent);
        int minRequiredArgs() const { return 2; }
        int maxAllowedArgs() const { return 2; }
        bool acceptsArgType(int iArg, ExprType_t type) const { return type == INT_EXPR;}
        ExprType_t argType(int iArg) const { return INT_EXPR; }
        VMFnResult* exec(VMFnArgs* args);
    protected:
        InstrumentScriptVM* m_vm;
    };

    class InstrumentScriptVMFunction_by_marks : public VMFunction {
    public:
        InstrumentScriptVMFunction_by_marks(InstrumentScriptVM* parent);
        int minRequiredArgs() const { return 1; }
        int maxAllowedArgs() const { return 1; }
        bool acceptsArgType(int iArg, ExprType_t type) const { return type == INT_EXPR;}
        ExprType_t argType(int iArg) const { return INT_EXPR; }
        ExprType_t returnType() { return INT_ARR_EXPR; }
        VMFnResult* exec(VMFnArgs* args);
    protected:
        InstrumentScriptVM* m_vm;
        class Result : public VMFnResult, public VMIntArrayExpr {
        public:
            StmtFlags_t flags;
            EventGroup* eventGroup;

            int arraySize() const OVERRIDE;
            int evalIntElement(uint i) OVERRIDE;
            void assignIntElement(uint i, int value) OVERRIDE {} // ignore assignment
            VMExpr* resultValue() OVERRIDE { return this; }
            StmtFlags_t resultFlags() { return flags; }
        } m_result;

        VMFnResult* errorResult();
        VMFnResult* successResult(EventGroup* eventGroup);
    };

    class InstrumentScriptVMFunction_change_vol : public VMEmptyResultFunction {
    public:
        InstrumentScriptVMFunction_change_vol(InstrumentScriptVM* parent);
        int minRequiredArgs() const { return 2; }
        int maxAllowedArgs() const { return 3; }
        bool acceptsArgType(int iArg, ExprType_t type) const;
        ExprType_t argType(int iArg) const { return INT_EXPR; }
        VMFnResult* exec(VMFnArgs* args);
    protected:
        InstrumentScriptVM* m_vm;
    };

    class InstrumentScriptVMFunction_change_tune : public VMEmptyResultFunction {
    public:
        InstrumentScriptVMFunction_change_tune(InstrumentScriptVM* parent);
        int minRequiredArgs() const { return 2; }
        int maxAllowedArgs() const { return 3; }
        bool acceptsArgType(int iArg, ExprType_t type) const;
        ExprType_t argType(int iArg) const { return INT_EXPR; }
        VMFnResult* exec(VMFnArgs* args);
    protected:
        InstrumentScriptVM* m_vm;
    };

    class InstrumentScriptVMFunction_change_pan : public VMEmptyResultFunction {
    public:
        InstrumentScriptVMFunction_change_pan(InstrumentScriptVM* parent);
        int minRequiredArgs() const { return 2; }
        int maxAllowedArgs() const { return 3; }
        bool acceptsArgType(int iArg, ExprType_t type) const;
        ExprType_t argType(int iArg) const { return INT_EXPR; }
        VMFnResult* exec(VMFnArgs* args);
    protected:
        InstrumentScriptVM* m_vm;
    };

    class InstrumentScriptVMFunction_change_cutoff : public VMEmptyResultFunction {
    public:
        InstrumentScriptVMFunction_change_cutoff(InstrumentScriptVM* parent);
        int minRequiredArgs() const { return 2; }
        int maxAllowedArgs() const { return 2; }
        bool acceptsArgType(int iArg, ExprType_t type) const;
        ExprType_t argType(int iArg) const { return INT_EXPR; }
        VMFnResult* exec(VMFnArgs* args);
    protected:
        InstrumentScriptVM* m_vm;
    };

    class InstrumentScriptVMFunction_change_reso : public VMEmptyResultFunction {
    public:
        InstrumentScriptVMFunction_change_reso(InstrumentScriptVM* parent);
        int minRequiredArgs() const { return 2; }
        int maxAllowedArgs() const { return 2; }
        bool acceptsArgType(int iArg, ExprType_t type) const;
        ExprType_t argType(int iArg) const { return INT_EXPR; }
        VMFnResult* exec(VMFnArgs* args);
    protected:
        InstrumentScriptVM* m_vm;
    };

    class InstrumentScriptVMFunction_event_status : public VMIntResultFunction {
    public:
        InstrumentScriptVMFunction_event_status(InstrumentScriptVM* parent);
        int minRequiredArgs() const { return 1; }
        int maxAllowedArgs() const { return 1; }
        bool acceptsArgType(int iArg, ExprType_t type) const { return type == INT_EXPR;}
        ExprType_t argType(int iArg) const { return INT_EXPR; }
        VMFnResult* exec(VMFnArgs* args);
    protected:
        InstrumentScriptVM* m_vm;
    };

} // namespace LinuxSampler

#endif // LS_INSTRSCRIPTVMFUNCTIONS_H
