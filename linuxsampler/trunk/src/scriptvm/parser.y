/*
 * Copyright (c) 2014-2016 Christian Schoenebeck and Andreas Persson
 *
 * http://www.linuxsampler.org
 *
 * This file is part of LinuxSampler and released under the same terms.
 * See README file for details.
 */
 
/* Parser for NKSP real-time instrument script language. */

%{
    #define YYERROR_VERBOSE 1
    #include "parser_shared.h"
    #include <string>
    #include <map>
    using namespace LinuxSampler;

    void InstrScript_error(YYLTYPE* locp, LinuxSampler::ParserContext* context, const char* err);
    void InstrScript_warning(YYLTYPE* locp, LinuxSampler::ParserContext* context, const char* txt);
    int InstrScript_lex(YYSTYPE* lvalp, YYLTYPE* llocp, void* scanner);
    #define scanner context->scanner
    #define PARSE_ERR(loc,txt)  yyerror(&loc, context, txt)
    #define PARSE_WRN(loc,txt)  InstrScript_warning(&loc, context, txt)
%}

// generate reentrant safe parser
%pure-parser
%parse-param { LinuxSampler::ParserContext* context }
%lex-param { void* scanner }
// avoid symbol collision with other (i.e. future) auto generated (f)lex scanners
%name-prefix "InstrScript_"
%locations
%defines
%error-verbose

%token <iValue> INTEGER
%token <sValue> STRING
%token <sValue> IDENTIFIER
%token <sValue> VARIABLE
%token ON END INIT NOTE DECLARE ASSIGNMENT WHILE IF OR RELEASE AND ELSE
%token BITWISE_OR BITWISE_AND BITWISE_NOT
%token CONTROLLER SELECT CASE TO NOT CONST_ POLYPHONIC MOD
%token LE GE

%type <nEventHandlers> script eventhandlers
%type <nEventHandler> eventhandler
%type <nStatements> statements body
%type <nStatement> statement assignment
%type <nFunctionCall> functioncall
%type <nArgs> args
%type <nExpression> arg expr logical_or_expr logical_and_expr bitwise_or_expr bitwise_and_expr rel_expr add_expr mul_expr unary_expr concat_expr
%type <nCaseBranch> caseclause
%type <nCaseBranches> caseclauses

%start script

%%

script:
    eventhandlers  {
        $$ = context->handlers = $1;
    }

eventhandlers:
    eventhandler  {
        $$ = new EventHandlers();
        $$->add($1);
    }
    | eventhandlers eventhandler  {
        $$ = $1;
        $$->add($2);
    }

eventhandler:
    ON NOTE body END ON  {
        if (context->onNote)
            PARSE_ERR(@2, "Redeclaration of 'note' event handler.");
        context->onNote = new OnNote($3);
        $$ = context->onNote;
    }
    | ON INIT body END ON  {
        if (context->onInit)
            PARSE_ERR(@2, "Redeclaration of 'init' event handler.");
        context->onInit = new OnInit($3);
        $$ = context->onInit;
    }
    | ON RELEASE body END ON  {
        if (context->onRelease)
            PARSE_ERR(@2, "Redeclaration of 'release' event handler.");
        context->onRelease = new OnRelease($3);
        $$ = context->onRelease;
    }
    | ON CONTROLLER body END ON  {
        if (context->onController)
            PARSE_ERR(@2, "Redeclaration of 'controller' event handler.");
        context->onController = new OnController($3);
        $$ = context->onController;
    }

body:
    /* epsilon (empty argument) */  {
        $$ = new Statements();
    }
    | statements  {
        $$ = $1;
    }

statements:
    statement  {
        $$ = new Statements();
        if ($1) {
            if (!isNoOperation($1)) $$->add($1); // filter out NoOperation statements
        } else 
            PARSE_WRN(@1, "Not a statement.");
    }
    | statements statement  {
        $$ = $1;
        if ($2) {
            if (!isNoOperation($2)) $$->add($2); // filter out NoOperation statements
        } else
            PARSE_WRN(@2, "Not a statement.");
    }

statement:
    functioncall  {
        $$ = $1;
    }
    | DECLARE VARIABLE  {
        const char* name = $2;
        //printf("declared var '%s'\n", name);
        if (context->variableByName(name))
            PARSE_ERR(@2, (String("Redeclaration of variable '") + name + "'.").c_str());
        if (name[0] == '@') {
            context->vartable[name] = new StringVariable(context);
            $$ = new NoOperation;
        } else {
            context->vartable[name] = new IntVariable(context);
            $$ = new NoOperation;
        }
    }
    | DECLARE POLYPHONIC VARIABLE  {
        const char* name = $3;
        //printf("declared polyphonic var '%s'\n", name);
        if (context->variableByName(name))
            PARSE_ERR(@3, (String("Redeclaration of variable '") + name + "'.").c_str());
        if (name[0] != '$') {
            PARSE_ERR(@3, "Polyphonic variables may only be declared as integers.");
            $$ = new FunctionCall("nothing", new Args, NULL); // whatever
        } else {
            context->vartable[name] = new PolyphonicIntVariable(context);
            $$ = new NoOperation;
        }
    }
    | DECLARE VARIABLE ASSIGNMENT expr  {
        const char* name = $2;
        //printf("declared assign var '%s'\n", name);
        if (context->variableByName(name))
            PARSE_ERR(@2, (String("Redeclaration of variable '") + name + "'.").c_str());
        if ($4->exprType() == STRING_EXPR) {
            if (name[0] == '$')
                PARSE_WRN(@2, (String("Variable '") + name + "' declared as integer, string expression assigned though.").c_str());
            StringExprRef expr = $4;
            if (expr->isConstExpr()) {
                const String s = expr->evalStr();
                StringVariableRef var = new StringVariable(context);
                context->vartable[name] = var;
                $$ = new Assignment(var, new StringLiteral(s));
            } else {
                StringVariableRef var = new StringVariable(context);
                context->vartable[name] = var;
                $$ = new Assignment(var, expr);
            }
        } else {
            if (name[0] == '@')
                PARSE_WRN(@2, (String("Variable '") + name + "' declared as string, integer expression assigned though.").c_str());
            IntExprRef expr = $4;
            if (expr->isConstExpr()) {
                const int i = expr->evalInt();
                IntVariableRef var = new IntVariable(context);
                context->vartable[name] = var;
                $$ = new Assignment(var, new IntLiteral(i));
            } else {
                IntVariableRef var = new IntVariable(context);
                context->vartable[name] = var;
                $$ = new Assignment(var, expr);
            }
        }
    }
    | DECLARE VARIABLE '[' expr ']'  {
        //printf("declare array without args\n");
        const char* name = $2;
        if (!$4->isConstExpr()) {
            PARSE_ERR(@4, (String("Array variable '") + name + "' must be declared with constant array size.").c_str());
            $$ = new FunctionCall("nothing", new Args, NULL); // whatever
        } else if ($4->exprType() != INT_EXPR) {
            PARSE_ERR(@4, (String("Size of array variable '") + name + "' declared with non integer expression.").c_str());
            $$ = new FunctionCall("nothing", new Args, NULL); // whatever
        } else if (context->variableByName(name)) {
            PARSE_ERR(@2, (String("Redeclaration of variable '") + name + "'.").c_str());
            $$ = new FunctionCall("nothing", new Args, NULL); // whatever
        } else {
            IntExprRef expr = $4;
            int size = expr->evalInt();
            if (size <= 0) {
                PARSE_ERR(@4, (String("Array variable '") + name + "' declared with array size " + ToString(size) + ".").c_str());
                $$ = new FunctionCall("nothing", new Args, NULL); // whatever
            } else {
                context->vartable[name] = new IntArrayVariable(context, size);
                $$ = new NoOperation;
            }
        }
    }
    | DECLARE VARIABLE '[' expr ']' ASSIGNMENT '(' args ')'  {
        const char* name = $2;
        if (!$4->isConstExpr()) {
            PARSE_ERR(@4, (String("Array variable '") + name + "' must be declared with constant array size.").c_str());
            $$ = new FunctionCall("nothing", new Args, NULL); // whatever
        } else if ($4->exprType() != INT_EXPR) {
            PARSE_ERR(@4, (String("Size of array variable '") + name + "' declared with non integer expression.").c_str());
            $$ = new FunctionCall("nothing", new Args, NULL); // whatever
        } else if (context->variableByName(name)) {
            PARSE_ERR(@2, (String("Redeclaration of variable '") + name + "'.").c_str());
            $$ = new FunctionCall("nothing", new Args, NULL); // whatever
        } else {
            IntExprRef sizeExpr = $4;
            ArgsRef args = $8;
            int size = sizeExpr->evalInt();
            if (size <= 0) {
                PARSE_ERR(@4, (String("Array variable '") + name + "' must be declared with positive array size.").c_str());
                $$ = new FunctionCall("nothing", new Args, NULL); // whatever
            } else if (args->argsCount() > size) {
                PARSE_ERR(@8, (String("Variable '") + name +
                          "' was declared with size " + ToString(size) +
                          " but " + ToString(args->argsCount()) +
                          " values were assigned." ).c_str());
                $$ = new FunctionCall("nothing", new Args, NULL); // whatever           
            } else {
                bool argsOK = true;
                for (int i = 0; i < args->argsCount(); ++i) {
                    if (args->arg(i)->exprType() != INT_EXPR) {
                        PARSE_ERR(
                            @8, 
                            (String("Array variable '") + name +
                            "' declared with invalid assignment values. Assigned element " +
                            ToString(i+1) + " is not an integer expression.").c_str()
                        );
                        argsOK = false;
                        break;
                    }
                }
                if (argsOK)
                    $$ = context->vartable[name] = new IntArrayVariable(context, size, args);
                else
                    $$ = new FunctionCall("nothing", new Args, NULL); // whatever
            }
        }
    }
    | DECLARE CONST_ VARIABLE ASSIGNMENT expr  {
        const char* name = $3;
        if ($5->exprType() == STRING_EXPR) {
            if (name[0] == '$')
                PARSE_WRN(@5, "Variable declared as integer, string expression assigned though.");
            String s;
            StringExprRef expr = $5;
            if (expr->isConstExpr())
                s = expr->evalStr();
            else
                PARSE_ERR(@5, (String("Assignment to const string variable '") + name + "' requires const expression.").c_str());
            ConstStringVariableRef var = new ConstStringVariable(context, s);
            context->vartable[name] = var;
            //$$ = new Assignment(var, new StringLiteral(s));
            $$ = new NoOperation();
        } else {
            if (name[0] == '@')
                PARSE_WRN(@5, "Variable declared as string, integer expression assigned though.");
            int i = 0;
            IntExprRef expr = $5;
            if (expr->isConstExpr())
                i = expr->evalInt();
            else
                PARSE_ERR(@5, (String("Assignment to const integer variable '") + name + "' requires const expression.").c_str());
            ConstIntVariableRef var = new ConstIntVariable(i);
            context->vartable[name] = var;
            //$$ = new Assignment(var, new IntLiteral(i));
            $$ = new NoOperation();
        }
    }
    | assignment  {
        $$ = $1;
    }
    | WHILE '(' expr ')' statements END WHILE  {
        if ($3->exprType() == INT_EXPR) {
            $$ = new While($3, $5);
        } else {
            PARSE_ERR(@3, "Condition for 'while' loops must be integer expression.");
            $$ = new While(new IntLiteral(0), $5);
        }
    }
    | IF '(' expr ')' statements ELSE statements END IF  {
        $$ = new If($3, $5, $7);
    }
    | IF '(' expr ')' statements END IF  {
        $$ = new If($3, $5);
    }
    | SELECT expr caseclauses END SELECT  {
        if ($2->exprType() == INT_EXPR) {
            $$ = new SelectCase($2, $3);
        } else {
            PARSE_ERR(@2, "Statement 'select' can only by applied to integer expressions.");
            $$ = new SelectCase(new IntLiteral(0), $3);
        }
    }

caseclauses:
    caseclause  {
        $$ = CaseBranches();
        $$.push_back($1);
    }
    | caseclauses caseclause  {
        $$ = $1;
        $$.push_back($2);
    }

caseclause:
    CASE INTEGER statements  {
        $$ = CaseBranch();
        $$.from = new IntLiteral($2);
        $$.statements = $3;
    }
    | CASE INTEGER TO INTEGER statements  {
        $$ = CaseBranch();
        $$.from = new IntLiteral($2);
        $$.to   = new IntLiteral($4);
        $$.statements = $5;
    }

functioncall:
    IDENTIFIER '(' args ')'  {
        const char* name = $1;
        //printf("function call of '%s' with args\n", name);
        ArgsRef args = $3;
        VMFunction* fn = context->functionProvider->functionByName(name);
        if (!fn) {
            PARSE_ERR(@1, (String("No built-in function with name '") + name + "'.").c_str());
            $$ = new FunctionCall(name, args, NULL);
        } else if (args->argsCount() < fn->minRequiredArgs()) {
            PARSE_ERR(@3, (String("Built-in function '") + name + "' requires at least " + ToString(fn->minRequiredArgs()) + " arguments.").c_str());
            $$ = new FunctionCall(name, args, NULL);
        } else if (args->argsCount() > fn->maxAllowedArgs()) {
            PARSE_ERR(@3, (String("Built-in function '") + name + "' accepts max. " + ToString(fn->maxAllowedArgs()) + " arguments.").c_str());
            $$ = new FunctionCall(name, args, NULL);
        } else {
            bool argsOK = true;
            for (int i = 0; i < args->argsCount(); ++i) {
                if (args->arg(i)->exprType() != fn->argType(i) && !fn->acceptsArgType(i, args->arg(i)->exprType())) {
                    PARSE_ERR(@3, (String("Argument ") + ToString(i+1) + " of built-in function '" + name + "' expects " + typeStr(fn->argType(i)) + " type, but type " + typeStr(args->arg(i)->exprType()) + " was given instead.").c_str());
                    argsOK = false;
                    break;
                } else if (fn->modifiesArg(i) && !args->arg(i)->isModifyable()) {
                    PARSE_ERR(@3, (String("Argument ") + ToString(i+1) + " of built-in function '" + name + "' expects an assignable variable.").c_str());
                    argsOK = false;
                    break;
                }
            }
            $$ = new FunctionCall(name, args, argsOK ? fn : NULL);
        }
    }
    | IDENTIFIER '(' ')' {
        const char* name = $1;
        //printf("function call of '%s' (with empty args)\n", name);
        ArgsRef args = new Args;
        VMFunction* fn = context->functionProvider->functionByName(name);
        if (!fn) {
            PARSE_ERR(@1, (String("No built-in function with name '") + name + "'.").c_str());
            $$ = new FunctionCall(name, args, NULL);
        } else if (fn->minRequiredArgs() > 0) {
            PARSE_ERR(@3, (String("Built-in function '") + name + "' requires at least " + ToString(fn->minRequiredArgs()) + " arguments.").c_str());
            $$ = new FunctionCall(name, args, NULL);
        } else {
            $$ = new FunctionCall(name, args, fn);
        }
    }
    | IDENTIFIER  {
        const char* name = $1;
        //printf("function call of '%s' (without args)\n", name);
        ArgsRef args = new Args;
        VMFunction* fn = context->functionProvider->functionByName(name);
        if (!fn) {
            PARSE_ERR(@1, (String("No built-in function with name '") + name + "'.").c_str());
            $$ = new FunctionCall(name, args, NULL);
        } else if (fn->minRequiredArgs() > 0) {
            PARSE_ERR(@1, (String("Built-in function '") + name + "' requires at least " + ToString(fn->minRequiredArgs()) + " arguments.").c_str());
            $$ = new FunctionCall(name, args, NULL);
        } else {
            $$ = new FunctionCall(name, args, fn);
        }
    }

args:
    arg  {
        $$ = new Args();
        $$->add($1);
    }
    | args ',' arg  {
        $$ = $1;
        $$->add($3);
    }

arg:
    expr

assignment:
    VARIABLE ASSIGNMENT expr  {
        //printf("variable lookup with name '%s' as assignment expr\n", $1);
        const char* name = $1;
        VariableRef var = context->variableByName(name);
        if (!var)
            PARSE_ERR(@1, (String("Variable assignment: No variable declared with name '") + name + "'.").c_str());
        else if (var->isConstExpr())
            PARSE_ERR(@2, (String("Variable assignment: Cannot modify const variable '") + name + "'.").c_str());
        else if (!var->isAssignable())
            PARSE_ERR(@2, (String("Variable assignment: Variable '") + name + "' is not assignable.").c_str());
        else if (var->exprType() != $3->exprType())
            PARSE_ERR(@3, (String("Variable assignment: Variable '") + name + "' is of type " + typeStr(var->exprType()) + ", assignment is of type " + typeStr($3->exprType()) + " though.").c_str());
        $$ = new Assignment(var, $3);
    }
    | VARIABLE '[' expr ']' ASSIGNMENT expr  {
        const char* name = $1;
        VariableRef var = context->variableByName(name);
        if (!var)
            PARSE_ERR(@1, (String("No variable declared with name '") + name + "'.").c_str());
        else if (var->exprType() != INT_ARR_EXPR)
            PARSE_ERR(@2, (String("Variable '") + name + "' is not an array variable.").c_str());
        else if ($3->exprType() != INT_EXPR)
            PARSE_ERR(@3, (String("Array variable '") + name + "' accessed with non integer expression.").c_str());
        else if ($6->exprType() != INT_EXPR)
            PARSE_ERR(@5, (String("Value assigned to array variable '") + name + "' must be an integer expression.").c_str());
        IntArrayElementRef element = new IntArrayElement(var, $3);
        $$ = new Assignment(element, $6);
    }

unary_expr:
    INTEGER  {
        $$ = new IntLiteral($1);
    }
    | STRING    {
        $$ = new StringLiteral($1);
    }
    | VARIABLE  {
        //printf("variable lookup with name '%s' as unary expr\n", $1);
        VariableRef var = context->variableByName($1);
        if (var)
            $$ = var;
        else {
            PARSE_ERR(@1, (String("No variable declared with name '") + $1 + "'.").c_str());
            $$ = new IntLiteral(0);
        }
    }
    | VARIABLE '[' expr ']'  {
        const char* name = $1;
        VariableRef var = context->variableByName(name);
        if (!var) {
            PARSE_ERR(@1, (String("No variable declared with name '") + name + "'.").c_str());
            $$ = new IntLiteral(0);
        } else if (var->exprType() != INT_ARR_EXPR) {
            PARSE_ERR(@2, (String("Variable '") + name + "' is not an array variable.").c_str());
            $$ = new IntLiteral(0);
        } else if ($3->exprType() != INT_EXPR) {
            PARSE_ERR(@3, (String("Array variable '") + name + "' accessed with non integer expression.").c_str());
            $$ = new IntLiteral(0);
        } else {
            $$ = new IntArrayElement(var, $3);
        }
    }
    | '(' expr ')'  {
        $$ = $2;
    }
    | functioncall  {
        $$ = $1;
    }
    | '-' unary_expr  {
        $$ = new Neg($2);
    }
    | BITWISE_NOT unary_expr  {
        if ($2->exprType() != INT_EXPR) {
            PARSE_ERR(@2, (String("Right operand of bitwise operator '.not.' must be an integer expression, is ") + typeStr($2->exprType()) + " though.").c_str());
            $$ = new IntLiteral(0);
        } else {
            $$ = new BitwiseNot($2);
        }
    }
    | NOT unary_expr  {
        if ($2->exprType() != INT_EXPR) {
            PARSE_ERR(@2, (String("Right operand of operator 'not' must be an integer expression, is ") + typeStr($2->exprType()) + " though.").c_str());
            $$ = new IntLiteral(0);
        } else {
            $$ = new Not($2);
        }
    }

expr:
    concat_expr

concat_expr:
    logical_or_expr
    | concat_expr '&' logical_or_expr  {
        ExpressionRef lhs = $1;
        ExpressionRef rhs = $3;
        if (lhs->isConstExpr() && rhs->isConstExpr()) {
            $$ = new StringLiteral(
                lhs->evalCastToStr() + rhs->evalCastToStr()
            );
        } else {
            $$ = new ConcatString(lhs, rhs);
        }
    }

logical_or_expr:
    logical_and_expr
    | logical_or_expr OR logical_and_expr  {
        ExpressionRef lhs = $1;
        ExpressionRef rhs = $3;
        if (lhs->exprType() != INT_EXPR) {
            PARSE_ERR(@1, (String("Left operand of operator 'or' must be an integer expression, is ") + typeStr(lhs->exprType()) + " though.").c_str());
            $$ = new IntLiteral(0);
        } else if (rhs->exprType() != INT_EXPR) {
            PARSE_ERR(@3, (String("Right operand of operator 'or' must be an integer expression, is ") + typeStr(rhs->exprType()) + " though.").c_str());
            $$ = new IntLiteral(0);
        } else {
            $$ = new Or(lhs, rhs);
        }
    }

logical_and_expr:
    bitwise_or_expr  {
        $$ = $1;
    }
    | logical_and_expr AND bitwise_or_expr  {
        ExpressionRef lhs = $1;
        ExpressionRef rhs = $3;
        if (lhs->exprType() != INT_EXPR) {
            PARSE_ERR(@1, (String("Left operand of operator 'and' must be an integer expression, is ") + typeStr(lhs->exprType()) + " though.").c_str());
            $$ = new IntLiteral(0);
        } else if (rhs->exprType() != INT_EXPR) {
            PARSE_ERR(@3, (String("Right operand of operator 'and' must be an integer expression, is ") + typeStr(rhs->exprType()) + " though.").c_str());
            $$ = new IntLiteral(0);
        } else {
            $$ = new And(lhs, rhs);
        }
    }

bitwise_or_expr:
    bitwise_and_expr
    | bitwise_or_expr BITWISE_OR bitwise_and_expr  {
        ExpressionRef lhs = $1;
        ExpressionRef rhs = $3;
        if (lhs->exprType() != INT_EXPR) {
            PARSE_ERR(@1, (String("Left operand of bitwise operator '.or.' must be an integer expression, is ") + typeStr(lhs->exprType()) + " though.").c_str());
            $$ = new IntLiteral(0);
        } else if (rhs->exprType() != INT_EXPR) {
            PARSE_ERR(@3, (String("Right operand of bitwise operator '.or.' must be an integer expression, is ") + typeStr(rhs->exprType()) + " though.").c_str());
            $$ = new IntLiteral(0);
        } else {
            $$ = new BitwiseOr(lhs, rhs);
        }
    }

bitwise_and_expr:
    rel_expr  {
        $$ = $1;
    }
    | bitwise_and_expr BITWISE_AND rel_expr  {
        ExpressionRef lhs = $1;
        ExpressionRef rhs = $3;
        if (lhs->exprType() != INT_EXPR) {
            PARSE_ERR(@1, (String("Left operand of bitwise operator '.and.' must be an integer expression, is ") + typeStr(lhs->exprType()) + " though.").c_str());
            $$ = new IntLiteral(0);
        } else if (rhs->exprType() != INT_EXPR) {
            PARSE_ERR(@3, (String("Right operand of bitwise operator '.and.' must be an integer expression, is ") + typeStr(rhs->exprType()) + " though.").c_str());
            $$ = new IntLiteral(0);
        } else {
            $$ = new BitwiseAnd(lhs, rhs);
        }
    }

rel_expr:
      add_expr
    | rel_expr '<' add_expr  {
        ExpressionRef lhs = $1;
        ExpressionRef rhs = $3;
        if (lhs->exprType() != INT_EXPR) {
            PARSE_ERR(@1, (String("Left operand of operator '<' must be an integer expression, is ") + typeStr(lhs->exprType()) + " though.").c_str());
            $$ = new IntLiteral(0);
        } else if (rhs->exprType() != INT_EXPR) {
            PARSE_ERR(@3, (String("Right operand of operator '<' must be an integer expression, is ") + typeStr(rhs->exprType()) + " though.").c_str());
            $$ = new IntLiteral(0);
        } else {
            $$ = new Relation(lhs, Relation::LESS_THAN, rhs);
        }
    }
    | rel_expr '>' add_expr  {
        ExpressionRef lhs = $1;
        ExpressionRef rhs = $3;
        if (lhs->exprType() != INT_EXPR) {
            PARSE_ERR(@1, (String("Left operand of operator '>' must be an integer expression, is ") + typeStr(lhs->exprType()) + " though.").c_str());
            $$ = new IntLiteral(0);
        } else if (rhs->exprType() != INT_EXPR) {
            PARSE_ERR(@3, (String("Right operand of operator '>' must be an integer expression, is ") + typeStr(rhs->exprType()) + " though.").c_str());
            $$ = new IntLiteral(0);
        } else {
            $$ = new Relation(lhs, Relation::GREATER_THAN, rhs);
        }
    }
    | rel_expr LE add_expr  {
        ExpressionRef lhs = $1;
        ExpressionRef rhs = $3;
        if (lhs->exprType() != INT_EXPR) {
            PARSE_ERR(@1, (String("Left operand of operator '<=' must be an integer expression, is ") + typeStr(lhs->exprType()) + " though.").c_str());
            $$ = new IntLiteral(0);
        } else if (rhs->exprType() != INT_EXPR) {
            PARSE_ERR(@3, (String("Right operand of operator '<=' must be an integer expression, is ") + typeStr(rhs->exprType()) + " though.").c_str());
            $$ = new IntLiteral(0);
        } else {
            $$ = new Relation(lhs, Relation::LESS_OR_EQUAL, rhs);
        }
    }
    | rel_expr GE add_expr  {
        ExpressionRef lhs = $1;
        ExpressionRef rhs = $3;
        if (lhs->exprType() != INT_EXPR) {
            PARSE_ERR(@1, (String("Left operand of operator '>=' must be an integer expression, is ") + typeStr(lhs->exprType()) + " though.").c_str());
            $$ = new IntLiteral(0);
        } else if (rhs->exprType() != INT_EXPR) {
            PARSE_ERR(@3, (String("Right operand of operator '>=' must be an integer expression, is ") + typeStr(rhs->exprType()) + " though.").c_str());
            $$ = new IntLiteral(0);
        } else {
            $$ = new Relation(lhs, Relation::GREATER_OR_EQUAL, rhs);
        }
    }
    | rel_expr '=' add_expr  {
        $$ = new Relation($1, Relation::EQUAL, $3);
    }
    | rel_expr '#' add_expr  {
        $$ = new Relation($1, Relation::NOT_EQUAL, $3);
    }

add_expr:
      mul_expr
    | add_expr '+' mul_expr  {
        ExpressionRef lhs = $1;
        ExpressionRef rhs = $3;
        if (lhs->exprType() != INT_EXPR) {
            PARSE_ERR(@1, (String("Left operand of operator '+' must be an integer expression, is ") + typeStr(lhs->exprType()) + " though.").c_str());
            $$ = new IntLiteral(0);
        } else if (rhs->exprType() != INT_EXPR) {
            PARSE_ERR(@3, (String("Right operand of operator '+' must be an integer expression, is ") + typeStr(rhs->exprType()) + " though.").c_str());
            $$ = new IntLiteral(0);
        } else {
            $$ = new Add(lhs,rhs);
        }
    }
    | add_expr '-' mul_expr  {
        ExpressionRef lhs = $1;
        ExpressionRef rhs = $3;
        if (lhs->exprType() != INT_EXPR) {
            PARSE_ERR(@1, (String("Left operand of operator '-' must be an integer expression, is ") + typeStr(lhs->exprType()) + " though.").c_str());
            $$ = new IntLiteral(0);
        } else if (rhs->exprType() != INT_EXPR) {
            PARSE_ERR(@3, (String("Right operand of operator '-' must be an integer expression, is ") + typeStr(rhs->exprType()) + " though.").c_str());
            $$ = new IntLiteral(0);
        } else {
            $$ = new Sub(lhs,rhs);
        }
    }

mul_expr:
    unary_expr
    | mul_expr '*' unary_expr  {
        ExpressionRef lhs = $1;
        ExpressionRef rhs = $3;
        if (lhs->exprType() != INT_EXPR) {
            PARSE_ERR(@1, (String("Left operand of operator '*' must be an integer expression, is ") + typeStr(lhs->exprType()) + " though.").c_str());
            $$ = new IntLiteral(0);
        } else if (rhs->exprType() != INT_EXPR) {
            PARSE_ERR(@3, (String("Right operand of operator '*' must be an integer expression, is ") + typeStr(rhs->exprType()) + " though.").c_str());
            $$ = new IntLiteral(0);
        } else {
            $$ = new Mul(lhs,rhs);
        }
    }
    | mul_expr '/' unary_expr  {
        ExpressionRef lhs = $1;
        ExpressionRef rhs = $3;
        if (lhs->exprType() != INT_EXPR) {
            PARSE_ERR(@1, (String("Left operand of operator '/' must be an integer expression, is ") + typeStr(lhs->exprType()) + " though.").c_str());
            $$ = new IntLiteral(0);
        } else if (rhs->exprType() != INT_EXPR) {
            PARSE_ERR(@3, (String("Right operand of operator '/' must be an integer expression, is ") + typeStr(rhs->exprType()) + " though.").c_str());
            $$ = new IntLiteral(0);
        } else {
            $$ = new Div(lhs,rhs);
        }
    }
    | mul_expr MOD unary_expr  {
        ExpressionRef lhs = $1;
        ExpressionRef rhs = $3;
        if (lhs->exprType() != INT_EXPR) {
            PARSE_ERR(@1, (String("Left operand of modulo operator must be an integer expression, is ") + typeStr(lhs->exprType()) + " though.").c_str());
            $$ = new IntLiteral(0);
        } else if (rhs->exprType() != INT_EXPR) {
            PARSE_ERR(@3, (String("Right operand of modulo operator must be an integer expression, is ") + typeStr(rhs->exprType()) + " though.").c_str());
            $$ = new IntLiteral(0);
        } else {
            $$ = new Mod(lhs,rhs);
        }
    }

%%

void InstrScript_error(YYLTYPE* locp, LinuxSampler::ParserContext* context, const char* err) {
    //fprintf(stderr, "%d: %s\n", locp->first_line, err);
    context->addErr(locp->first_line, locp->last_line, locp->first_column+1, locp->last_column+1, err);
}

void InstrScript_warning(YYLTYPE* locp, LinuxSampler::ParserContext* context, const char* txt) {
    //fprintf(stderr, "WRN %d: %s\n", locp->first_line, txt);
    context->addWrn(locp->first_line, locp->last_line, locp->first_column+1, locp->last_column+1, txt);
}
