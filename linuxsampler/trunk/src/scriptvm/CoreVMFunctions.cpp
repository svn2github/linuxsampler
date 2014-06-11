/*
 * Copyright (c) 2014 Christian Schoenebeck
 *
 * http://www.linuxsampler.org
 *
 * This file is part of LinuxSampler and released under the same terms.
 * See README file for details.
 */

#include "CoreVMFunctions.h"

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "tree.h"
#include "ScriptVM.h"

namespace LinuxSampler {

VMFnResult* VMEmptyResultFunction::errorResult() {
    result.flags = StmtFlags_t(STMT_ABORT_SIGNALLED | STMT_ERROR_OCCURRED);
    return &result;
}

VMFnResult* VMEmptyResultFunction::successResult() {
    result.flags = STMT_SUCCESS;
    return &result;
}

VMFnResult* VMIntResultFunction::errorResult(int i) {
    result.flags = StmtFlags_t(STMT_ABORT_SIGNALLED | STMT_ERROR_OCCURRED);
    result.value = i;
    return &result;
}

VMFnResult* VMIntResultFunction::successResult(int i) {
    result.flags = STMT_SUCCESS;
    result.value = i;
    return &result;
}

VMFnResult* VMStringResultFunction::errorResult(const String& s) {
    result.flags = StmtFlags_t(STMT_ABORT_SIGNALLED | STMT_ERROR_OCCURRED);
    result.value = s;
    return &result;
}

VMFnResult* VMStringResultFunction::successResult(const String& s) {
    result.flags = STMT_SUCCESS;
    result.value = s;
    return &result;
}

bool CoreVMFunction_message::acceptsArgType(int iArg, ExprType_t type) const {
    return type == INT_EXPR || type == STRING_EXPR;
}

VMFnResult* CoreVMFunction_message::exec(VMFnArgs* args) {
    if (!args->argsCount()) return errorResult();

    VMStringExpr* strExpr = dynamic_cast<VMStringExpr*>(args->arg(0));
    if (strExpr) {
        std::cout << "[ScriptVM] " << strExpr->evalStr() << "\n";
        return successResult();
    }

    VMIntExpr* intExpr = dynamic_cast<VMIntExpr*>(args->arg(0));
    if (intExpr) {
        std::cout << "[ScriptVM] " << intExpr->evalInt() << "\n";
        return successResult();
    }

    return errorResult();
}

VMFnResult* CoreVMFunction_exit::exec(VMFnArgs* args) {
    this->result.flags = STMT_ABORT_SIGNALLED;
    return &result;
}

VMFnResult* CoreVMFunction_wait::exec(VMFnArgs* args) {
    ExecContext* ctx = dynamic_cast<ExecContext*>(vm->currentVMExecContext());
    VMIntExpr* expr = dynamic_cast<VMIntExpr*>(args->arg(0));
    ctx->suspendMicroseconds = expr->evalInt();
    this->result.flags = STMT_SUSPEND_SIGNALLED;
    return &result;
}

bool CoreVMFunction_abs::acceptsArgType(int iArg, ExprType_t type) const {
    return type == INT_EXPR;
}

VMFnResult* CoreVMFunction_abs::exec(VMFnArgs* args) {
    return successResult( ::abs(args->arg(0)->asInt()->evalInt()) );
}

bool CoreVMFunction_random::acceptsArgType(int iArg, ExprType_t type) const {
    return type == INT_EXPR;
}

VMFnResult* CoreVMFunction_random::exec(VMFnArgs* args) {
    int iMin = args->arg(0)->asInt()->evalInt();
    int iMax = args->arg(1)->asInt()->evalInt();
    float f = float(::random()) / float(RAND_MAX);
    return successResult(
        iMin + roundf( f * float(iMax - iMin) )
    );
}

bool CoreVMFunction_num_elements::acceptsArgType(int iArg, ExprType_t type) const {
    return type == INT_ARR_EXPR;
}

VMFnResult* CoreVMFunction_num_elements::exec(VMFnArgs* args) {
    return successResult( args->arg(0)->asIntArray()->arraySize() );
}

} // namespace LinuxSampler
