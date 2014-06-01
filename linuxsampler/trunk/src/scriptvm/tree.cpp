/*
 * Copyright (c) 2014 Christian Schoenebeck and Andreas Persson
 *
 * http://www.linuxsampler.org
 *
 * This file is part of LinuxSampler and released under the same terms.
 * See README file for details.
 */

#include <cstdio>
#include <string.h>
#include "tree.h"
#include "../common/global_private.h"
#include <assert.h>

namespace LinuxSampler {
    
bool isNoOperation(StatementRef statement) {
    NoOperation* noOp = dynamic_cast<NoOperation*>(&*statement);
    return noOp;
}
    
Node::Node() {
}

Node::~Node() {
}

void Node::printIndents(int n) {
    for (int i = 0; i < n; ++i) printf("  ");
    fflush(stdout);
}

String IntExpr::evalCastToStr() {
    return ToString(evalInt());
}

int IntLiteral::evalInt() {
    return value;
}

void IntLiteral::dump(int level) {
    printIndents(level);
    printf("IntLiteral %d\n", value);
}

void StringLiteral::dump(int level) {
    printIndents(level);
    printf("StringLiteral: '%s'\n", value.c_str());
}

int Add::evalInt() {
    IntExpr* pLHS = dynamic_cast<IntExpr*>(&*lhs);
    IntExpr* pRHS = dynamic_cast<IntExpr*>(&*rhs);;
    return (pLHS && pRHS) ? pLHS->evalInt() + pRHS->evalInt() : 0;
}

void Add::dump(int level) {
    printIndents(level);
    printf("Add(\n");
    lhs->dump(level+1);
    printIndents(level);
    printf(",\n");
    rhs->dump(level+1);
    printIndents(level);
    printf(")\n");
}

int Sub::evalInt() {
    IntExpr* pLHS = dynamic_cast<IntExpr*>(&*lhs);
    IntExpr* pRHS = dynamic_cast<IntExpr*>(&*rhs);;
    return (pLHS && pRHS) ? pLHS->evalInt() - pRHS->evalInt() : 0;
}

void Sub::dump(int level) {
    printIndents(level);
    printf("Sub(\n");
    lhs->dump(level+1);
    printIndents(level);
    printf(",\n");
    rhs->dump(level+1);
    printIndents(level);
    printf(")\n");
}

int Mul::evalInt() {
    IntExpr* pLHS = dynamic_cast<IntExpr*>(&*lhs);
    IntExpr* pRHS = dynamic_cast<IntExpr*>(&*rhs);;
    return (pLHS && pRHS) ? pLHS->evalInt() * pRHS->evalInt() : 0;
}

void Mul::dump(int level) {
    printIndents(level);
    printf("Mul(\n");
    lhs->dump(level+1);
    printIndents(level);
    printf(",\n");
    rhs->dump(level+1);
    printIndents(level);
    printf(")\n");
}

int Div::evalInt() {
    IntExpr* pLHS = dynamic_cast<IntExpr*>(&*lhs);
    IntExpr* pRHS = dynamic_cast<IntExpr*>(&*rhs);;
    return (pLHS && pRHS) ? pRHS->evalInt() == 0 ? 0 : pLHS->evalInt() / pRHS->evalInt() : 0;
}

void Div::dump(int level) {
    printIndents(level);
    printf("Div(\n");
    lhs->dump(level+1);
    printIndents(level);
    printf(",\n");
    rhs->dump(level+1);
    printIndents(level);
    printf(")\n");
}

int Mod::evalInt() {
    IntExpr* pLHS = dynamic_cast<IntExpr*>(&*lhs);
    IntExpr* pRHS = dynamic_cast<IntExpr*>(&*rhs);;
    return (pLHS && pRHS) ? pLHS->evalInt() % pRHS->evalInt() : 0;
}

void Mod::dump(int level) {
    printIndents(level);
    printf("Mod(\n");
    lhs->dump(level+1);
    printIndents(level);
    printf(",\n");
    rhs->dump(level+1);
    printIndents(level);
    printf(")\n");
}

void Args::dump(int level) {
    printIndents(level);
    printf("Args(\n");
    for (std::vector<ExpressionRef>::iterator it = args.begin() ; it != args.end() ; ++it) {
        (*it)->dump(level+1);
    }
    printIndents(level);
    printf(")\n");
}

EventHandlers::EventHandlers() {
    //printf("EventHandlers::Constructor 0x%lx\n", (long long)this);
}

EventHandlers::~EventHandlers() {
}

void EventHandlers::add(EventHandlerRef arg) {
    args.push_back(arg);
}

void EventHandlers::dump(int level) {
    printIndents(level);
    printf("EventHandlers {\n");
    for (std::vector<EventHandlerRef>::iterator it = args.begin() ; it != args.end() ; ++it) {
        (*it)->dump(level+1);
    }
    printIndents(level);
    printf("}\n");
}

EventHandler* EventHandlers::eventHandlerByName(const String& name) const {
    for (int i = 0; i < args.size(); ++i)
        if (args.at(i)->eventHandlerName() == name)
            return const_cast<EventHandler*>(&*args.at(i));
    return NULL;
}

EventHandler* EventHandlers::eventHandler(uint index) const {
    if (index >= args.size()) return NULL;
    return const_cast<EventHandler*>(&*args.at(index));
}

Assignment::Assignment(VariableRef variable, ExpressionRef value)
   : variable(variable), value(value)
{
}

void Assignment::dump(int level) {
    printIndents(level);
    printf("Assignment\n");
}

StmtFlags_t Assignment::exec() {
    if (!variable)
        return StmtFlags_t(STMT_ABORT_SIGNALLED | STMT_ERROR_OCCURRED);
    variable->assign(&*value);
    return STMT_SUCCESS;
}

void EventHandler::dump(int level) {
    printIndents(level);
    printf("EventHandler {\n");
    statements->dump(level+1);
    printIndents(level);
    printf("}\n");
}

void Statements::dump(int level) {
    printIndents(level);
    printf("Statements {\n");
    for (std::vector<StatementRef>::iterator it = args.begin() ; it != args.end() ; ++it) {
        (*it)->dump(level+1);
    }
    printIndents(level);
    printf("}\n");
}

Statement* Statements::statement(uint i) {
    if (i >= args.size()) return NULL;
    return &*args.at(i);
}

void FunctionCall::dump(int level) {
    printIndents(level);
    printf("FunctionCall '%s' args={\n", functionName.c_str());
    args->dump(level+1);
    printIndents(level);
    printf("}\n");
}

ExprType_t FunctionCall::exprType() const {
    if (!fn) return EMPTY_EXPR;
    return fn->returnType();
}

VMFnResult* FunctionCall::execVMFn() {
    if (!fn) return NULL;
    // assuming here that all argument checks (amount and types) have been made
    // at parse time, to avoid time intensive checks on each function call
    return fn->exec(dynamic_cast<VMFnArgs*>(&*args));
}

StmtFlags_t FunctionCall::exec() {
    VMFnResult* result = execVMFn();
    if (!result)
        return StmtFlags_t(STMT_ABORT_SIGNALLED | STMT_ERROR_OCCURRED);
    return result->resultFlags();
}

int FunctionCall::evalInt() {
    VMFnResult* result = execVMFn();
    if (!result) return 0;
    VMIntExpr* intExpr = dynamic_cast<VMIntExpr*>(result->resultValue());
    if (!intExpr) return 0;
    return intExpr->evalInt();
}

String FunctionCall::evalStr() {
    VMFnResult* result = execVMFn();
    if (!result) return "";
    VMStringExpr* strExpr = dynamic_cast<VMStringExpr*>(result->resultValue());
    if (!strExpr) return "";
    return strExpr->evalStr();
}

String FunctionCall::evalCastToStr() {
    VMFnResult* result = execVMFn();
    if (!result) return "";
    if (result->resultValue()->exprType() == STRING_EXPR) {
        VMStringExpr* strExpr = dynamic_cast<VMStringExpr*>(result->resultValue());
        return strExpr ? strExpr->evalStr() : "";
    } else {
        VMIntExpr* intExpr = dynamic_cast<VMIntExpr*>(result->resultValue());
        return intExpr ? ToString(intExpr->evalInt()) : "";
    }
}

IntVariable::IntVariable(ParserContext* ctx)
    : Variable(ctx, ctx ? ctx->globalIntVarCount++ : 0, false), polyphonic(false)
{
    //printf("globalIntVar parserctx=0x%lx memPOS=%d\n", ctx, memPos);
    assert(ctx);
}

inline static int postfixInc(int& object, int incBy) {
    const int i = object;
    object += incBy;
    return i;
}

IntVariable::IntVariable(ParserContext* ctx, bool polyphonic, bool bConst, int size)
    : Variable(ctx, !ctx ? 0 : polyphonic ? postfixInc(ctx->polyphonicIntVarCount, size) : postfixInc(ctx->globalIntVarCount, size), bConst),
      polyphonic(polyphonic)
{
    //printf("InvVar size=%d parserCtx=0x%lx\n", size, (uint64_t)ctx);
    if (polyphonic) {
        //printf("polyIntVar memPOS=%d\n", memPos);
        assert(ctx);
    }
}

void IntVariable::assign(Expression* expr) {
    IntExpr* intExpr = dynamic_cast<IntExpr*>(expr);
    if (intExpr)
        if (polyphonic)
            context->execContext->polyphonicIntMemory[memPos] = intExpr->evalInt();
        else
            (*context->globalIntMemory)[memPos] = intExpr->evalInt();
}

int IntVariable::evalInt() {
    //printf("IntVariable::eval pos=%d\n", memPos);
    if (polyphonic) {
        //printf("evalInt() poly memPos=%d execCtx=0x%lx\n", memPos, (uint64_t)context->execContext);
        return context->execContext->polyphonicIntMemory[memPos];
    }
    return (*context->globalIntMemory)[memPos];
}

void IntVariable::dump(int level) {
    printIndents(level);
    //printf("IntVariable memPos=%d\n", memPos);
}

//ConstIntVariable::ConstIntVariable(ParserContext* ctx, int value)
ConstIntVariable::ConstIntVariable(int value)
    : IntVariable(NULL,false,true), value(value)
{
}

void ConstIntVariable::assign(Expression* expr) {
    // ignore assignment
/*
    printf("ConstIntVariable::assign()\n");
    IntExpr* intExpr = dynamic_cast<IntExpr*>(expr);
    if (intExpr) {
        value = intExpr->evalInt();
    }
*/
}

int ConstIntVariable::evalInt() {
    return value;
}

void ConstIntVariable::dump(int level) {
    printIndents(level);
    printf("ConstIntVariable val=%d\n", value);
}

PolyphonicIntVariable::PolyphonicIntVariable(ParserContext* ctx)
    : IntVariable(ctx,true,false)
{
}

void PolyphonicIntVariable::dump(int level) {
    printIndents(level);
    printf("PolyphonicIntVariable\n");
}

IntArrayVariable::IntArrayVariable(ParserContext* ctx, int size)
    : Variable(ctx, 0, false)
{
    values.resize(size);
    memset(&values[0], 0, size * sizeof(int));
}

IntArrayVariable::IntArrayVariable(ParserContext* ctx, int size, ArgsRef values)
    : Variable(ctx, 0, false)
{
    this->values.resize(size);
    for (int i = 0; i < values->argsCount(); ++i) {
        VMIntExpr* expr = dynamic_cast<VMIntExpr*>(values->arg(i));
        if (expr) this->values[i] = expr->evalInt();
    }
}

int IntArrayVariable::evalIntElement(uint i) {
    if (i >= values.size()) return 0;
    return values[i];
}

void IntArrayVariable::assignIntElement(uint i, int value) {
    if (i >= values.size()) return;
    values[i] = value;
}

void IntArrayVariable::dump(int level) {
    printIndents(level);
    printf("IntArray(");
    for (int i = 0; i < values.size(); ++i) {
        if (i % 12 == 0) {
            printf("\n");
            printIndents(level+1);
        }
        printf("%d, ", values[i]);
    }
    printIndents(level);
    printf(")\n");
}

IntArrayElement::IntArrayElement(IntArrayVariableRef array, IntExprRef arrayIndex)
    : IntVariable(NULL, false, false, 0), array(array), index(arrayIndex)
{    
}

void IntArrayElement::assign(Expression* expr) {
    IntExpr* valueExpr = dynamic_cast<IntExpr*>(expr);
    if (!valueExpr) return;
    int value = valueExpr->evalInt();

    if (!index) return;
    int idx = index->evalInt();
    if (idx < 0 || idx >= array->arraySize()) return;

    array->assignIntElement(idx, value);
}

int IntArrayElement::evalInt() {
    if (!index) return 0;
    int idx = index->evalInt();
    if (idx < 0 || idx >= array->arraySize()) return 0;

    return array->evalIntElement(idx);
}

void IntArrayElement::dump(int level) {
    printIndents(level);
    printf("IntArrayElement\n");
}

StringVariable::StringVariable(ParserContext* ctx)
    : Variable(ctx,ctx->globalStrVarCount++,false)
{
}

StringVariable::StringVariable(ParserContext* ctx, bool bConst)
    : Variable(ctx,0,bConst)
{
}

void StringVariable::assign(Expression* expr) {
    StringExpr* strExpr = dynamic_cast<StringExpr*>(expr);
    (*context->globalStrMemory)[memPos] = strExpr->evalStr();
}

String StringVariable::evalStr() {
    //printf("StringVariable::eval pos=%d\n", memPos);
    return (*context->globalStrMemory)[memPos];
}

void StringVariable::dump(int level) {
    printIndents(level);
    printf("StringVariable memPos=%d\n", memPos);
}

ConstStringVariable::ConstStringVariable(ParserContext* ctx, String _value)
    : StringVariable(ctx,true), value(_value)
{
}

void ConstStringVariable::assign(Expression* expr) {
    // ignore assignment
//     StringExpr* strExpr = dynamic_cast<StringExpr*>(expr);
//     if (strExpr) value = strExpr->evalStr();
}

String ConstStringVariable::evalStr() {
    return value;
}

void ConstStringVariable::dump(int level) {
    printIndents(level);
    printf("ConstStringVariable val='%s'\n", value.c_str());
}

void If::dump(int level) {
    printIndents(level);
    if (ifStatements && elseStatements)
        printf("if cond stmts1 else stmts2 end if\n");
    else if (ifStatements)
        printf("if cond statements end if\n");
    else
        printf("if [INVALID]\n");
}

int If::evalBranch() {
    if (condition->evalInt()) return 0;
    if (elseStatements) return 1;
    return -1;
}

Statements* If::branch(uint i) const {
    if (i == 0) return (Statements*) &*ifStatements;
    if (i == 1) return (elseStatements) ? (Statements*) &*elseStatements : NULL;
    return NULL;
}

void SelectCase::dump(int level) {
    printIndents(level);
    if (select)
        if (select->isConstExpr())
            printf("Case select %d\n", select->evalInt());
        else
            printf("Case select [runtime expr]\n");
    else
        printf("Case select NULL\n");
    for (int i = 0; i < branches.size(); ++i) {
        printIndents(level+1);
        CaseBranch& branch = branches[i];
        if (branch.from && branch.to)
            if (branch.from->isConstExpr() && branch.to->isConstExpr())
                printf("case %d to %d\n", branch.from->evalInt(), branch.to->evalInt());
            else if (branch.from->isConstExpr() && !branch.to->isConstExpr())
                printf("case %d to [runtime expr]\n", branch.from->evalInt());
            else if (!branch.from->isConstExpr() && branch.to->isConstExpr())
                printf("case [runtime expr] to %d\n", branch.to->evalInt());
            else
                printf("case [runtime expr] to [runtime expr]\n");
        else if (branch.from)
            if (branch.from->isConstExpr())
                printf("case %d\n", branch.from->evalInt());
            else
                printf("case [runtime expr]\n");
        else
            printf("case NULL\n");
    }
}

int SelectCase::evalBranch() {
    int value = select->evalInt();
    for (int i = 0; i < branches.size(); ++i) {
        if (branches.at(i).from && branches.at(i).to) { // i.e. "case 4 to 7" ...
            if (branches.at(i).from->evalInt() <= value &&
                branches.at(i).to->evalInt() >= value) return i;
        } else { // i.e. "case 5" ...
            if (branches.at(i).from->evalInt() == value) return i;
        }
    }
    return -1;
}

Statements* SelectCase::branch(uint i) const {
    if (i < branches.size())
        return const_cast<Statements*>( &*branches[i].statements );
    return NULL;
}

// void Case::addBranch(IntExprRef condition, StatementsRef statements) {
//     CaseBranchRef b = new CaseBranchRef;
//     b->from = condition;
//     b->statements = statements;
//     branches.push_back(b);
// }
// 
// void Case::addBranch(IntExprRef from, IntExprRef to, StatementsRef statements) {
//     CaseBranchRef b = new CaseBranchRef;
//     b->from = from;
//     b->to   = to;
//     b->statements = statements;
//     branches.push_back(b);
// }
// 
// void Case::addBranch(CaseBranchRef branch) {
//     branches.push_back(branch);
// }

void While::dump(int level) {
    printIndents(level);
    if (m_condition)
        if (m_condition->isConstExpr())
            printf("while (%d) {\n", m_condition->evalInt());
        else
            printf("while ([runtime expr]) {\n");
    else
        printf("while ([INVALID]) {\n");
    m_statements->dump(level+1);
    printIndents(level);
    printf("}\n");
}

Statements* While::statements() const {
    return (m_statements) ? const_cast<Statements*>( &*m_statements ) : NULL;
}

bool While::evalLoopStartCondition() {
    if (!m_condition) return false;
    return m_condition->evalInt();
}

void Neg::dump(int level) {
    printIndents(level);
    printf("Negative Expr\n");
}

String ConcatString::evalStr() {
    return lhs->evalCastToStr() + rhs->evalCastToStr();
}

void ConcatString::dump(int level) {
    printIndents(level);
    printf("ConcatString(\n");
    lhs->dump(level+1);
    printIndents(level);
    printf(",\n");
    rhs->dump(level+1);
    printIndents(level);
    printf(")");
}

bool ConcatString::isConstExpr() const {
    return lhs->isConstExpr() && rhs->isConstExpr();
}

int Relation::evalInt() {
    switch (type) {
        case LESS_THAN:
            return lhs->evalInt() < rhs->evalInt();
        case GREATER_THAN:
            return lhs->evalInt() > rhs->evalInt();
        case LESS_OR_EQUAL:
            return lhs->evalInt() <= rhs->evalInt();
        case GREATER_OR_EQUAL:
            return lhs->evalInt() >= rhs->evalInt();
        case EQUAL:
            if (lhs->exprType() == STRING_EXPR || rhs->exprType() == STRING_EXPR)
                return lhs->evalCastToStr() == rhs->evalCastToStr();
            else
                return lhs->evalInt() == rhs->evalInt();
        case NOT_EQUAL:
            if (lhs->exprType() == STRING_EXPR || rhs->exprType() == STRING_EXPR)
                return lhs->evalCastToStr() != rhs->evalCastToStr();
            else
                return lhs->evalInt() != rhs->evalInt();
    }
    return 0;
}

void Relation::dump(int level) {
    printIndents(level);
    printf("Relation(\n");
    lhs->dump(level+1);
    printIndents(level);
    switch (type) {
        case LESS_THAN:
            printf("LESS_THAN\n");
            break;
        case GREATER_THAN:
            printf("GREATER_THAN\n");
            break;
        case LESS_OR_EQUAL:
            printf("LESS_OR_EQUAL\n");
            break;
        case GREATER_OR_EQUAL:
            printf("GREATER_OR_EQUAL\n");
            break;
        case EQUAL:
            printf("EQUAL\n");
            break;
        case NOT_EQUAL:
            printf("NOT_EQUAL\n");
            break;
    }
    rhs->dump(level+1);
    printIndents(level);
    printf(")\n");
}

bool Relation::isConstExpr() const {
    return lhs->isConstExpr() && rhs->isConstExpr();
}

int Or::evalInt() {
    IntExpr* pLHS = dynamic_cast<IntExpr*>(&*lhs);
    IntExpr* pRHS = dynamic_cast<IntExpr*>(&*rhs);;
    return pLHS->evalInt() || pRHS->evalInt();
}

void Or::dump(int level) {
    printIndents(level);
    printf("Or(\n");
    lhs->dump(level+1);
    printIndents(level);
    printf(",\n");
    rhs->dump(level+1);
    printIndents(level);
    printf(")\n");
}

int And::evalInt() {
    IntExpr* pLHS = dynamic_cast<IntExpr*>(&*lhs);
    IntExpr* pRHS = dynamic_cast<IntExpr*>(&*rhs);;
    return pLHS->evalInt() && pRHS->evalInt();
}

void And::dump(int level) {
    printIndents(level);
    printf("And(\n");
    lhs->dump(level+1);
    printIndents(level);
    printf(",\n");
    rhs->dump(level+1);
    printIndents(level);
    printf(")\n");
}

void Not::dump(int level) {
    printIndents(level);
    printf("Not(\n");
    expr->dump(level+1);
    printIndents(level);
    printf(")\n");
}

VariableRef ParserContext::variableByName(const String& name) {
    if (!vartable.count(name)) {
        return VariableRef();
    }
    return vartable.find(name)->second;
}

VariableRef ParserContext::globalVar(const String& name) {
    if (!vartable.count(name)) {
        //printf("No global var '%s'\n", name.c_str());
        //for (std::map<String,VariableRef>::const_iterator it = vartable.begin(); it != vartable.end(); ++it)
        //    printf("-> var '%s'\n", it->first.c_str());
        return VariableRef();
    }
    return vartable.find(name)->second;
}

IntVariableRef ParserContext::globalIntVar(const String& name) {
    return globalVar(name);
}

StringVariableRef ParserContext::globalStrVar(const String& name) {
    return globalVar(name);
}

ParserContext::~ParserContext() {
    destroyScanner();
    if (globalIntMemory) {
        delete globalIntMemory;
        globalIntMemory = NULL;
    }
}

void ParserContext::addErr(int line, const char* txt) {
    ParserIssue e;
    e.type = PARSER_ERROR;
    e.txt = txt;
    e.line = line;
    vErrors.push_back(e);
    vIssues.push_back(e);
}

void ParserContext::addWrn(int line, const char* txt) {
    ParserIssue w;
    w.type = PARSER_WARNING;
    w.txt = txt;
    w.line = line;
    vWarnings.push_back(w);
    vIssues.push_back(w);
}

bool ParserContext::setPreprocessorCondition(const char* name) {
    if (builtinPreprocessorConditions.count(name)) return false;
    if (userPreprocessorConditions.count(name)) return false;
    userPreprocessorConditions.insert(name);
    return true;
}

bool ParserContext::resetPreprocessorCondition(const char* name) {
    if (builtinPreprocessorConditions.count(name)) return false;
    if (!userPreprocessorConditions.count(name)) return false;
    userPreprocessorConditions.erase(name);
    return true;
}

bool ParserContext::isPreprocessorConditionSet(const char* name) {
    if (builtinPreprocessorConditions.count(name)) return true;
    return userPreprocessorConditions.count(name);
}

std::vector<ParserIssue> ParserContext::issues() const {
    return vIssues;
}

std::vector<ParserIssue> ParserContext::errors() const {
    return vErrors;
}

std::vector<ParserIssue> ParserContext::warnings() const {
    return vWarnings;
}

VMEventHandler* ParserContext::eventHandler(uint index) {
    if (!handlers) return NULL;
    return handlers->eventHandler(index);
}

VMEventHandler* ParserContext::eventHandlerByName(const String& name) {
    if (!handlers) return NULL;
    return handlers->eventHandlerByName(name);
}

} // namespace LinuxSampler
