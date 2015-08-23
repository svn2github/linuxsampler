/*
 * Copyright (c) 2014 - 2015 Christian Schoenebeck
 *
 * http://www.linuxsampler.org
 *
 * This file is part of LinuxSampler and released under the same terms.
 * See README file for details.
 */

#include "ScriptVM.h"

#include <string.h>
#include <assert.h>
#include "../common/global_private.h"
#include "tree.h"

#define DEBUG_SCRIPTVM_CORE 0

int InstrScript_parse(LinuxSampler::ParserContext*);

namespace LinuxSampler {

    static void _printIndents(int n) {
        for (int i = 0; i < n; ++i) printf("  ");
        fflush(stdout);
    }

    static int _requiredMaxStackSizeFor(Statement* statement, int depth = 0) {
        if (!statement) return 1;

        switch (statement->statementType()) {
            case STMT_LEAF:
                #if DEBUG_SCRIPTVM_CORE
                _printIndents(depth);
                printf("-> STMT_LEAF\n");
                #endif
                return 1;

            case STMT_LIST: {
                #if DEBUG_SCRIPTVM_CORE
                _printIndents(depth);
                printf("-> STMT_LIST\n");
                #endif
                Statements* stmts = (Statements*) statement;
                int max = 0;
                for (int i = 0; stmts->statement(i); ++i) {
                    int size = _requiredMaxStackSizeFor( stmts->statement(i), depth+1 );
                    if (max < size) max = size;
                }
                return max + 1;
            }

            case STMT_BRANCH: {
                #if DEBUG_SCRIPTVM_CORE
                _printIndents(depth);
                printf("-> STMT_BRANCH\n");
                #endif
                BranchStatement* branchStmt = (BranchStatement*) statement;
                int max = 0;
                for (int i = 0; branchStmt->branch(i); ++i) {
                    int size = _requiredMaxStackSizeFor( branchStmt->branch(i), depth+1 );
                    if (max < size) max = size;
                }
                return max + 1;
            }

            case STMT_LOOP: {
                #if DEBUG_SCRIPTVM_CORE
                _printIndents(depth);
                printf("-> STMT_LOOP\n");
                #endif
                While* whileStmt = (While*) statement;
                if (whileStmt->statements())
                    return _requiredMaxStackSizeFor( whileStmt->statements() ) + 1;
                else
                    return 1;
            }
        }

        return 1; // actually just to avoid compiler warning
    }

    static int _requiredMaxStackSizeFor(EventHandlers* handlers) {
        int max = 1;
        for (int i = 0; i < handlers->size(); ++i) {
            int size = _requiredMaxStackSizeFor(handlers->eventHandler(i));
            if (max < size) max = size;
        }
        return max;
    }

    ScriptVM::ScriptVM() : m_parserContext(NULL), fnWait(this) {
    }

    ScriptVM::~ScriptVM() {
    }

    VMParserContext* ScriptVM::loadScript(const String& s) {
        std::istringstream iss(s);
        return loadScript(&iss);
    }
    
    VMParserContext* ScriptVM::loadScript(std::istream* is) {
        ParserContext* context = new ParserContext(this);
        //printf("parserCtx=0x%lx\n", (uint64_t)context);

        context->registerBuiltInConstIntVariables( builtInConstIntVariables() );
        context->registerBuiltInIntVariables( builtInIntVariables() );
        context->registerBuiltInIntArrayVariables( builtInIntArrayVariables() );

        context->createScanner(is);

        InstrScript_parse(context);
        dmsg(2,("Allocating %ld bytes of global int VM memory.\n", long(context->globalIntVarCount * sizeof(int))));
        dmsg(2,("Allocating %d of global VM string variables.\n", context->globalStrVarCount));
        if (!context->globalIntMemory)
            context->globalIntMemory = new ArrayList<int>();
        if (!context->globalStrMemory)
            context->globalStrMemory = new ArrayList<String>();
        context->globalIntMemory->resize(context->globalIntVarCount);
        memset(&((*context->globalIntMemory)[0]), 0, context->globalIntVarCount * sizeof(int));
        
        context->globalStrMemory->resize(context->globalStrVarCount);

        context->destroyScanner();

        return context;
    }

    void ScriptVM::dumpParsedScript(VMParserContext* context) {
        ParserContext* ctx = dynamic_cast<ParserContext*>(context);
        if (!ctx) {
            std::cerr << "No VM context. So nothing to dump.\n";
            return;
        }
        if (!ctx->handlers) {
            std::cerr << "No event handlers defined in script. So nothing to dump.\n";
            return;
        }
        if (!ctx->globalIntMemory) {
            std::cerr << "Internal error: no global memory assigend to script VM.\n";
            return;
        }
        ctx->handlers->dump();
    }

    VMExecContext* ScriptVM::createExecContext(VMParserContext* parserContext) {
        ParserContext* parserCtx = dynamic_cast<ParserContext*>(parserContext);
        ExecContext* execCtx = new ExecContext();
        
        if (parserCtx->requiredMaxStackSize < 0) {
             parserCtx->requiredMaxStackSize =
                _requiredMaxStackSizeFor(&*parserCtx->handlers);
        }
        execCtx->stack.resize(parserCtx->requiredMaxStackSize);
        dmsg(2,("Created VM exec context with %ld bytes VM stack size.\n",
                long(parserCtx->requiredMaxStackSize * sizeof(ExecContext::StackFrame))));
        //printf("execCtx=0x%lx\n", (uint64_t)execCtx);
        const int polySize = parserCtx->polyphonicIntVarCount;
        execCtx->polyphonicIntMemory.resize(polySize);
        memset(&execCtx->polyphonicIntMemory[0], 0, polySize * sizeof(int));

        dmsg(2,("Allocated %ld bytes polyphonic memory.\n", long(polySize * sizeof(int))));
        return execCtx;
    }

    VMFunction* ScriptVM::functionByName(const String& name) {
        if (name == "message") return &fnMessage;
        else if (name == "exit") return &fnExit;
        else if (name == "wait") return &fnWait;
        else if (name == "abs") return &fnAbs;
        else if (name == "random") return &fnRandom;
        else if (name == "num_elements") return &fnNumElements;
        return NULL;
    }

    std::map<String,VMIntRelPtr*> ScriptVM::builtInIntVariables() {
        return std::map<String,VMIntRelPtr*>();
    }

    std::map<String,VMInt8Array*> ScriptVM::builtInIntArrayVariables() {
        return std::map<String,VMInt8Array*>();
    }

    std::map<String,int> ScriptVM::builtInConstIntVariables() {
        return std::map<String,int>();
    }

    VMParserContext* ScriptVM::currentVMParserContext() {
        return m_parserContext;
    }

    VMExecContext* ScriptVM::currentVMExecContext() {
        if (!m_parserContext) return NULL;
        return m_parserContext->execContext;
    }

    VMExecStatus_t ScriptVM::exec(VMParserContext* parserContext, VMExecContext* execContex, VMEventHandler* handler) {
        m_parserContext = dynamic_cast<ParserContext*>(parserContext);
        if (!m_parserContext) {
            std::cerr << "No VM parser context provided. Did you load a script?.\n";
            return VMExecStatus_t(VM_EXEC_NOT_RUNNING | VM_EXEC_ERROR);
        }

        // a ParserContext object is always tied to exactly one ScriptVM object
        assert(m_parserContext->functionProvider == this);

        ExecContext* ctx = dynamic_cast<ExecContext*>(execContex);
        if (!ctx) {
            std::cerr << "Invalid VM exec context.\n";
            return VMExecStatus_t(VM_EXEC_NOT_RUNNING | VM_EXEC_ERROR);
        }
        EventHandler* h = dynamic_cast<EventHandler*>(handler);
        if (!h) return VM_EXEC_NOT_RUNNING;

        m_parserContext->execContext = ctx;

        ctx->status = VM_EXEC_RUNNING;
        StmtFlags_t flags = STMT_SUCCESS;

        int& frameIdx = ctx->stackFrame;
        if (frameIdx < 0) { // start condition ...
            frameIdx = -1;
            ctx->pushStack(h);
        }

        while (flags == STMT_SUCCESS && frameIdx >= 0) {
            if (frameIdx >= ctx->stack.size()) { // should never happen, otherwise it's a bug ...
                std::cerr << "CRITICAL: VM stack overflow! (" << frameIdx << ")\n";
                flags = StmtFlags_t(STMT_ABORT_SIGNALLED | STMT_ERROR_OCCURRED);
                break;
            }

            ExecContext::StackFrame& frame = ctx->stack[frameIdx];
            switch (frame.statement->statementType()) {
                case STMT_LEAF: {
                    #if DEBUG_SCRIPTVM_CORE
                    _printIndents(frameIdx);
                    printf("-> STMT_LEAF\n");
                    #endif
                    LeafStatement* leaf = (LeafStatement*) frame.statement;
                    flags = leaf->exec();
                    ctx->popStack();
                    break;
                }

                case STMT_LIST: {
                    #if DEBUG_SCRIPTVM_CORE
                    _printIndents(frameIdx);
                    printf("-> STMT_LIST subidx=%d\n", frame.subindex);
                    #endif
                    Statements* stmts = (Statements*) frame.statement;
                    if (stmts->statement(frame.subindex)) {
                        ctx->pushStack(
                            stmts->statement(frame.subindex++)
                        );
                    } else {
                        #if DEBUG_SCRIPTVM_CORE
                        _printIndents(frameIdx);
                        printf("[END OF LIST] subidx=%d\n", frame.subindex);
                        #endif
                        ctx->popStack();
                    }
                    break;
                }

                case STMT_BRANCH: {
                    #if DEBUG_SCRIPTVM_CORE
                    _printIndents(frameIdx);
                    printf("-> STMT_BRANCH\n");
                    #endif
                    if (frame.subindex < 0) ctx->popStack();
                    else {
                        BranchStatement* branchStmt = (BranchStatement*) frame.statement;
                        frame.subindex = branchStmt->evalBranch();
                        if (frame.subindex >= 0) {
                            ctx->pushStack(
                                branchStmt->branch(frame.subindex)
                            );
                            frame.subindex = -1;
                        } else ctx->popStack();
                    }
                    break;
                }

                case STMT_LOOP: {
                    #if DEBUG_SCRIPTVM_CORE
                    _printIndents(frameIdx);
                    printf("-> STMT_LOOP\n");
                    #endif
                    While* whileStmt = (While*) frame.statement;
                    if (whileStmt->evalLoopStartCondition() && whileStmt->statements()) {
                        ctx->pushStack(
                            whileStmt->statements()
                        );
                    } else ctx->popStack();
                }
            }
        }

        if (flags & STMT_SUSPEND_SIGNALLED) {
            ctx->status = VM_EXEC_SUSPENDED;
        } else {
            ctx->status = VM_EXEC_NOT_RUNNING;
            if (flags & STMT_ERROR_OCCURRED)
                ctx->status = VM_EXEC_ERROR;
            ctx->reset();
        }

        m_parserContext->execContext = NULL;
        m_parserContext = NULL;
        return ctx->status;
    }

} // namespace LinuxSampler
