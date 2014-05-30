/*
 * Copyright (c) 2014 Christian Schoenebeck
 *
 * http://www.linuxsampler.org
 *
 * This file is part of LinuxSampler and released under the same terms.
 * See README file for details.
 */

#include "ScriptVM.h"

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

    ScriptVM::ScriptVM() : fnWait(this) {
        m_context = new ParserContext(this);
    }

    ScriptVM::~ScriptVM() {
        if (m_context) {
            if (m_context->globalIntMemory) {
                delete m_context->globalIntMemory;
                m_context->globalIntMemory = NULL;
            }
            delete m_context;
        }
    }

    void ScriptVM::loadScript(const String& s) {
        std::istringstream iss(s);
        loadScript(&iss);
    }
    
    void ScriptVM::loadScript(std::istream* is) {
        m_context->createScanner(is);
        InstrScript_parse(m_context);
        std::cout << "Allocating " << m_context->globalIntVarCount * sizeof(int) << " bytes of global int VM memory.\n";
        std::cout << "Allocating " << m_context->globalStrVarCount << " of global VM string variables.\n";
        if (!m_context->globalIntMemory)
            m_context->globalIntMemory = new ArrayList<int>();
        if (!m_context->globalStrMemory)
            m_context->globalStrMemory = new ArrayList<String>();
        m_context->globalIntMemory->resize(m_context->globalIntVarCount);
        m_context->globalStrMemory->resize(m_context->globalStrVarCount);
    }

    std::vector<ParserIssue> ScriptVM::issues() const {
        return m_context->issues;
    }

    std::vector<ParserIssue> ScriptVM::errors() const {
        return m_context->errors;
    }

    std::vector<ParserIssue> ScriptVM::warnings() const {
        return m_context->warnings;
    }

    void ScriptVM::dumpParsedScript() {
        if (!m_context) {
            std::cerr << "No VM context. So nothing to dump.\n";
            return;
        }
        if (!m_context->handlers) {
            std::cerr << "No event handlers defined in script. So nothing to dump.\n";
            return;
        }
        if (!m_context->globalIntMemory) {
            std::cerr << "Internal error: no global memory assigend to script VM.\n";
            return;
        }
        m_context->handlers->dump();
    }

    VMExecContext* ScriptVM::createExecContext() {
        ExecContext* ctx = new ExecContext();
        const int stackSize = _requiredMaxStackSizeFor(&*m_context->handlers);
        ctx->stack.resize(stackSize);
        std::cout << "Created VM exec context with "
                  << stackSize * sizeof(ExecContext::StackFrame)
                  << " bytes VM stack size.\n";
        const int polySize = m_context->polyphonicIntVarCount;
        ctx->polyphonicIntMemory.resize(polySize);
        std::cout << "Allocated " << polySize * sizeof(int)
                  << " bytes polyphonic memory.\n";
        return ctx;
    }

    VMEventHandler* ScriptVM::eventHandler(uint index) {
        if (!m_context) return NULL;
        if (!m_context->handlers) return NULL;
        return m_context->handlers->eventHandler(index);
    }

    VMEventHandler* ScriptVM::eventHandlerByName(const String& name) {
        if (!m_context) return NULL;
        if (!m_context->handlers) return NULL;
        return m_context->handlers->eventHandlerByName(name);
    }

    VMFunction* ScriptVM::functionByName(const String& name) {
        if (name == "message") return &fnMessage;
        else if (name == "exit") return &fnExit;
        else if (name == "wait") return &fnWait;
        return NULL;
    }
    
    VMExecContext* ScriptVM::currentVMExecContext() {
        if (!m_context) return NULL;
        return m_context->execContext;
    }

    VMExecStatus_t ScriptVM::exec(VMEventHandler* handler, VMExecContext* execContex) {
        if (!m_context) {
            std::cerr << "No VM parser context. Did you load a script?.\n";
            return VMExecStatus_t(VM_EXEC_NOT_RUNNING | VM_EXEC_ERROR);
        }

        ExecContext* ctx = dynamic_cast<ExecContext*>(execContex);
        if (!ctx) {
            std::cerr << "Invalid VM exec context.\n";
            return VMExecStatus_t(VM_EXEC_NOT_RUNNING | VM_EXEC_ERROR);
        }
        EventHandler* h = dynamic_cast<EventHandler*>(handler);
        if (!h) return VM_EXEC_NOT_RUNNING;

        m_context->execContext = ctx;

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

        m_context->execContext = NULL;
        return ctx->status;
    }

} // namespace LinuxSampler
