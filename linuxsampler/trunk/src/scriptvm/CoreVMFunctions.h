/*
 * Copyright (c) 2014 Christian Schoenebeck
 *
 * http://www.linuxsampler.org
 *
 * This file is part of LinuxSampler and released under the same terms.
 * See README file for details.
 */

#ifndef LS_COREVMFUNCTIONS_H
#define LS_COREVMFUNCTIONS_H

#include "../common/global.h"
#include "common.h"

namespace LinuxSampler {
    
class ScriptVM;
    
class VMEmptyResult : public VMFnResult, public VMExpr {
public:
    StmtFlags_t flags;

    VMEmptyResult() : flags(STMT_SUCCESS) {}
    ExprType_t exprType() const { return EMPTY_EXPR; }
    VMExpr* resultValue() { return this; }
    StmtFlags_t resultFlags() { return flags; }
};

class VMStringResult : public VMFnResult, public VMStringExpr {
public:
    StmtFlags_t flags;
    String value;

    VMStringResult() : flags(STMT_SUCCESS) {}
    String evalStr() { return value; }
    VMExpr* resultValue() { return this; }
    StmtFlags_t resultFlags() { return flags; }
};

class VMEmptyResultFunction : public VMFunction {
protected:
    ExprType_t returnType() { return EMPTY_EXPR; }
    VMFnResult* errorResult();
    VMFnResult* successResult();
protected:
    VMEmptyResult result;
};

class VMStringResultFunction : public VMFunction {
protected:
    ExprType_t returnType() { return STRING_EXPR; }
    VMFnResult* errorResult(const String& s = "");
    VMFnResult* successResult(const String& s = "");
protected:
    VMStringResult result;
};

class CoreVMFunction_message : public VMEmptyResultFunction {
public:
    int minRequiredArgs() const { return 1; }
    int maxAllowedArgs() const { return 1; }
    bool acceptsArgType(int iArg, ExprType_t type) const;
    ExprType_t argType(int iArg) const { return STRING_EXPR; }
    VMFnResult* exec(VMFnArgs* args);
};

class CoreVMFunction_exit : public VMEmptyResultFunction {
public:
    int minRequiredArgs() const { return 0; }
    int maxAllowedArgs() const { return 0; }
    bool acceptsArgType(int iArg, ExprType_t type) const { return false; }
    ExprType_t argType(int iArg) const { return INT_EXPR; /*whatever*/ }
    VMFnResult* exec(VMFnArgs* args);
};

class CoreVMFunction_wait : public VMEmptyResultFunction {
public:
    CoreVMFunction_wait(ScriptVM* vm) : vm(vm) {}
    int minRequiredArgs() const { return 1; }
    int maxAllowedArgs() const { return 1; }
    bool acceptsArgType(int iArg, ExprType_t type) const { return type == INT_EXPR; }
    ExprType_t argType(int iArg) const { return INT_EXPR; }
    VMFnResult* exec(VMFnArgs* args);
protected:
    ScriptVM* vm;
};

} // namespace LinuxSampler

#endif // LS_COREVMFUNCTIONS_H
