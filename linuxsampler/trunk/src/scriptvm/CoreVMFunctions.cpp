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
#include "tree.h"
#include "ScriptVM.h"

namespace LinuxSampler {

VMFnResult* VMEmptyResultFunction::errorResult() {
    result.flags = StmtFlags_t(STMT_ABORT_SIGNALLED | STMT_ERROR_OCCURRED);
    return &result;
}

void VMEmptyResultFunction::wrnMsg(const String& txt) {
    std::cout << "[ScriptVM] " << txt << std::endl;
}

void VMEmptyResultFunction::errMsg(const String& txt) {
    std::cerr << "[ScriptVM] " << txt << std::endl;
}

VMFnResult* VMEmptyResultFunction::successResult() {
    result.flags = STMT_SUCCESS;
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

} // namespace LinuxSampler
