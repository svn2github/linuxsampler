/*
 * Copyright (c) 2014 Christian Schoenebeck
 *
 * http://www.linuxsampler.org
 *
 * This file is part of LinuxSampler and released under the same terms.
 * See README file for details.
 */

// This header defines data types shared between the VM core implementation
// (inside the current source directory) and other parts of the sampler
// (located at other source directories).

#ifndef LS_INSTR_SCRIPT_PARSER_COMMON_H
#define LS_INSTR_SCRIPT_PARSER_COMMON_H

#include "../common/global.h"
#include <vector>

namespace LinuxSampler {
    
    enum ParserIssueType_t {
        PARSER_ERROR,
        PARSER_WARNING
    };

    enum ExprType_t {
        EMPTY_EXPR, ///< i.e. on invalid expressions or i.e. a function call that does not return a result value
        INT_EXPR,
        INT_ARR_EXPR,
        STRING_EXPR,
        STRING_ARR_EXPR,
    };

    enum StmtFlags_t {
       STMT_SUCCESS = 0, ///< Function / statement was executed successfully, no error occurred.
       STMT_ABORT_SIGNALLED = 1, ///< VM should stop the current callback execution (usually because of an error, but might also be without an error reason).
       STMT_SUSPEND_SIGNALLED = (1<<1),
       STMT_ERROR_OCCURRED = (1<<2),
    };

    enum VMExecStatus_t {
        VM_EXEC_NOT_RUNNING = 0,
        VM_EXEC_RUNNING = 1,
        VM_EXEC_SUSPENDED = (1<<1),
        VM_EXEC_ERROR = (1<<2),
    };

    class VMExpr {
    public:
        virtual ExprType_t exprType() const = 0;
    };

    class VMIntExpr : virtual public VMExpr {
    public:
        virtual int evalInt() = 0;
        ExprType_t exprType() const { return INT_EXPR; }
    };

    class VMStringExpr : virtual public VMExpr {
    public:
        virtual String evalStr() = 0;
        ExprType_t exprType() const { return STRING_EXPR; }
    };

    class VMFnArgs {
    public:
        virtual int argsCount() const = 0;
        virtual VMExpr* arg(int i) = 0;
    };

    class VMFnResult {
    public:
        virtual VMExpr* resultValue() = 0;
        virtual StmtFlags_t resultFlags() { return STMT_SUCCESS; }
    };

    class VMFunction {
    public:
        virtual ExprType_t returnType() = 0;
        virtual int minRequiredArgs() const = 0;
        virtual int maxAllowedArgs() const = 0;
        virtual ExprType_t argType(int iArg) const = 0;
        virtual bool acceptsArgType(int iArg, ExprType_t type) const = 0;
        virtual VMFnResult* exec(VMFnArgs* args) = 0;
    };

    class VMFunctionProvider {
    public:
        virtual VMFunction* functionByName(const String& name) = 0;
    };

    class VMExecContext {
    public:
        virtual ~VMExecContext() {}
        virtual int suspensionTimeMicroseconds() const = 0;
    };

    class VMEventHandler {
    public:
        virtual String eventHandlerName() const = 0;
    };

    struct ParserIssue {
        String txt;
        int line;
        ParserIssueType_t type;

        inline void dump() {
            switch (type) {
                case PARSER_ERROR:
                    printf("[ERROR] line %d: %s\n", line, txt.c_str());
                    break;
                case PARSER_WARNING:
                    printf("[Warning] line %d: %s\n", line, txt.c_str());
                    break;
            }
        }
        
        inline bool isErr() const { return type == PARSER_ERROR;   }
        inline bool isWrn() const { return type == PARSER_WARNING; }
    };

    inline String typeStr(const ExprType_t& type) {
        switch (type) {
            case EMPTY_EXPR: return "empty";
            case INT_EXPR: return "integer";
            case INT_ARR_EXPR: return "integer array";
            case STRING_EXPR: return "string";
            case STRING_ARR_EXPR: return "string array";
        }
        return "invalid";
    }

    class VMParserContext {
    public:
        virtual ~VMParserContext() {}
        virtual std::vector<ParserIssue> issues() const = 0;
        virtual std::vector<ParserIssue> errors() const = 0;
        virtual std::vector<ParserIssue> warnings() const = 0;
        virtual VMEventHandler* eventHandler(uint index) = 0;
        virtual VMEventHandler* eventHandlerByName(const String& name) = 0;
    };

} // namespace LinuxSampler

#endif // LS_INSTR_SCRIPT_PARSER_COMMON_H
