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
#include <map>
#include <stddef.h> // offsetof()

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

    class VMIntExpr;
    class VMStringExpr;

    class VMExpr {
    public:
        virtual ExprType_t exprType() const = 0;
        VMIntExpr* asInt() const;
        VMStringExpr* asString() const;
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

    /**
     * POD base of VMIntRelPtr and VMInt8RelPtr structures. Not intended to be
     * used directly. Use VMIntRelPtr or VMInt8RelPtr instead.
     */
    struct VMRelPtr {
        void** base; ///< Base pointer.
        int offset;  ///< Offset (in bytes) to base pointer.
    };

    /** @brief Pointer to built-in VM integer variable (of C/C++ type int).
     *
     * Used for defining built-in integer script variables.
     *
     * @b CAUTION: You may only use this class for pointing to C/C++ variables
     * of type "int" (which on most systems is 32 bit in size). If the C/C++ int
     * variable you want to reference is only 8 bit in size, then you @b must
     * use VMInt8RelPtr instead!
     *
     * For efficiency reasons the actual native C/C++ int variable is referenced
     * by two components here. The actual native int C/C++ variable in memory
     * is dereferenced at VM run-time by taking the @c base pointer dereference
     * and adding @c offset bytes. This has the advantage that for a large
     * number of built-in int variables, only one (or few) base pointer need
     * to be re-assigned before running a script, instead of updating each
     * built-in variable each time before a script is executed.
     *
     * Refer to DECLARE_VMINT() for example code.
     *
     * @see VMInt8RelPtr, DECLARE_VMINT()
     */
    struct VMIntRelPtr : VMRelPtr {
        VMIntRelPtr() {
            base   = NULL;
            offset = 0;
        }
        VMIntRelPtr(const VMRelPtr& data) {
            base   = data.base;
            offset = data.offset;
        }
        virtual int evalInt() { return *(int*)&(*(uint8_t**)base)[offset]; }
        virtual void assign(int i) { *(int*)&(*(uint8_t**)base)[offset] = i; }
    };

    /** @brief Pointer to built-in VM integer variable (of C/C++ type int8_t).
     *
     * Used for defining built-in integer script variables.
     *
     * @b CAUTION: You may only use this class for pointing to C/C++ variables
     * of type "int8_t" (8 bit integer). If the C/C++ int variable you want to
     * reference is an "int" type (which is 32 bit on most systems), then you
     * @b must use VMIntRelPtr instead!
     *
     * For efficiency reasons the actual native C/C++ int variable is referenced
     * by two components here. The actual native int C/C++ variable in memory
     * is dereferenced at VM run-time by taking the @c base pointer dereference
     * and adding @c offset bytes. This has the advantage that for a large
     * number of built-in int variables, only one (or few) base pointer need
     * to be re-assigned before running a script, instead of updating each
     * built-in variable each time before a script is executed.
     *
     * Refer to DECLARE_VMINT() for example code.
     *
     * @see VMIntRelPtr, DECLARE_VMINT()
     */
    struct VMInt8RelPtr : VMIntRelPtr {
        VMInt8RelPtr() : VMIntRelPtr() {}
        VMInt8RelPtr(const VMRelPtr& data) : VMIntRelPtr(data) {}
        virtual int evalInt() OVERRIDE {
            return *(uint8_t*)&(*(uint8_t**)base)[offset];
        }
        virtual void assign(int i) OVERRIDE {
            *(uint8_t*)&(*(uint8_t**)base)[offset] = i;
        }
    };

    /**
     * Convenience macro for initializing VMIntRelPtr and VMInt8RelPtr
     * structures. Example:
     * @code
     * struct Foo {
     *   uint8_t a;
     *   int b;
     * };
     *
     * Foo foo1 = (Foo) { 1, 3000 };
     * Foo foo2 = (Foo) { 2, 4000 };
     *
     * Foo* pFoo;
     *
     * VMInt8RelPtr var1 = DECLARE_VMINT(pFoo, class Foo, a);
     * VMIntRelPtr  var2 = DECLARE_VMINT(pFoo, class Foo, b);
     *
     * pFoo = &foo1;
     * printf("%d\n", var1->evalInt()); // will print 1
     * printf("%d\n", var2->evalInt()); // will print 3000
     *
     * pFoo = &foo2;
     * printf("%d\n", var1->evalInt()); // will print 2
     * printf("%d\n", var2->evalInt()); // will print 4000
     * @endcode
     */
    #define DECLARE_VMINT(basePtr, T_struct, T_member) ( \
        (VMRelPtr) {                                     \
            (void**) &basePtr,                           \
            offsetof(T_struct, T_member)                 \
        }                                                \
    )                                                    \

    /** @brief Built-in VM 8 bit integer array variable.
     *
     * Used for defining built-in integer array script variables.
     */
    struct VMInt8Array {
        int8_t* data;
        int size;

        VMInt8Array() : data(NULL), size(0) {}
    };

    class VMFunctionProvider {
    public:
        virtual VMFunction* functionByName(const String& name) = 0;
        virtual std::map<String,VMIntRelPtr*> builtInIntVariables() = 0;
        virtual std::map<String,VMInt8Array*> builtInIntArrayVariables() = 0;
        virtual std::map<String,int> builtInConstIntVariables() = 0;
    };

    /** @brief Execution state of a virtual machine.
     *
     * An instance of this abstract base class represents exactly one execution
     * state of a virtual machine. This encompasses most notably the VM
     * execution stack, and VM polyphonic variables. You might see it as one
     * virtual thread of the virtual machine.
     *
     * @see VMParserContext
     */
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

    /** @brief Virtual machine representation of a script.
     *
     * An instance of this abstract base class represents a parsed script,
     * translated into a virtual machine. You should first check if there were
     * any parser errors. If there were any parser errors, you should refrain
     * from executing the virtual machine. Otherwise if there were no parser
     * errors (i.e. only warnings), then you might access one of the script's
     * event handlers by i.e. calling eventHandlerByName() and pass the
     * respective event handler to the ScriptVM class (or to one of its
     * descendants) for execution.
     *
     * @see VMExecContext
     */
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
