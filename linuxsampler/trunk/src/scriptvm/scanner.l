/*
 * Copyright (c) 2014 Christian Schoenebeck and Andreas Persson
 *
 * http://www.linuxsampler.org
 *
 * This file is part of LinuxSampler and released under the same terms.
 * See README file for details.
 */

/* Token scanner for instrument script language. */

/* FIXME: line numbers (i.e. on error/warning messages) are incorrect, because
   the current grammar does not process new line characters. \n is currently
   filtered out in this lexer. Due to this, the parser will sometimes read
   several lines before it matches the next complete grammar rule, causing the
   incorrect lines in the error/warning messages. */

%{

#include "parser_shared.h"
#include <math.h>
// reentrant scanner data context
#define YY_EXTRA_TYPE ParserContext*
// set line number each time a token is recognized
#define YY_USER_ACTION                  \
{                                       \
    yylloc->first_line = yylineno;      \
    yylloc->last_line  = yylineno;      \
    /* first_column = TODO */           \
    /* last_column  = TODO */           \
    /*printf("lex: line '%s'\n", yytext);*/  \
}
// custom (f)lex input for reading from std::istream object
#define YY_INPUT(buf,result,max_size)   \
{                                       \
    char c = yyextra->is->get();        \
    if (yyextra->is->eof())             \
        result = YY_NULL;               \
    else {                              \
        buf[0] = c;                     \
        result = 1;                     \
    }                                   \
}

static void scanner_error(YYLTYPE* locp, LinuxSampler::ParserContext* context, const char* err) {
    context->addErr(locp->first_line, err);
}

static void scanner_warning(YYLTYPE* locp, LinuxSampler::ParserContext* context, const char* txt) {
    context->addWrn(locp->first_line, txt);
}

#define SCANNER_ERR(txt)  scanner_error(yylloc, yyextra, txt)
#define SCANNER_WRN(txt)  scanner_warning(yylloc, yyextra, txt)

using namespace LinuxSampler;

%}

/* use Flex's built-in support for line numbers */
%option yylineno
/* generate a reentrant safe scanner */
%option reentrant
/* avoid symbol collision with other (i.e. future) scanner symbols */
%option prefix="InstrScript_"
/* bison-bridge adds an argument yylval to yylex, and bison-locations adds an
   argument code yylloc for location tracking. */
%option bison-bridge
%option bison-locations
/* yywrap() would be called at EOF, we don't need it */
%option noyywrap
/* enable functions yy_push_state(), yy_pop_state(), yy_top_state() */
%option stack

/* inclusive scanner conditions */
%s PREPROC_BODY_USE
/* exclusive scanner conditions */
%x PREPROC_SET_COND PREPROC_RESET_COND PREPROC_IF PREPROC_IF_NOT PREPROC_BODY_EAT PREPROC_PRE_BODY_USE PREPROC_PRE_BODY_EAT

DIGIT    [0-9]
ID       [a-zA-Z0-9_]*

%%

\"[^"]*\" {
    yylval->sValue = strdup(yytext + 1);
    yylval->sValue[strlen(yylval->sValue) - 1] = '\0';
    return STRING;
}

{DIGIT}+ {
    yylval->iValue = atoi(yytext);
    return INTEGER;
}

{DIGIT}+"."{DIGIT}* {
    printf("A float: %s (%g)\n", yytext, atof(yytext));
}


 /* Preprocessor statement:  SET_CONDITION(name) */

<*>"SET_CONDITION"[ \t]*"(" {
    printf("SET_CONDITION\n");
    yy_push_state(PREPROC_SET_COND, yyscanner);
}
<PREPROC_SET_COND>{ID} {
    printf("preproc set condition '%s'\n", yytext);
    bool success = yyextra->setPreprocessorCondition(yytext);
    if (!success) {
        SCANNER_WRN((String("Preprocessor: Condition '") +
                    yytext + "' is already set.").c_str());
    }
}
<PREPROC_SET_COND>[ \t]*")" {
    printf("End of PREPROC_SET_COND\n");
    yy_pop_state(yyscanner);
}


 /* Preprocessor statement:  RESET_CONDITION(name) */

<*>"RESET_CONDITION"[ \t]*"(" {
    printf("RESET_CONDITION\n");
    yy_push_state(PREPROC_RESET_COND, yyscanner);
}
<PREPROC_RESET_COND>{ID} {
    printf("preproc reset condition '%s'\n", yytext);
    bool success = yyextra->resetPreprocessorCondition(yytext);
    if (!success) {
        SCANNER_ERR((String("Preprocessor: could not reset condition '") +
                    yytext + "' (either not set or a built-in condition).").c_str());
    }
}
<PREPROC_RESET_COND>[ \t]*")" {
    printf("End of RESET_CONDITION\n");
    yy_pop_state(yyscanner);
}


 /* Preprocessor conditional statements:

    USE_CODE_IF(name)
      ...
    END_USE_CODE

    and:

    USE_CODE_IF_NOT(name)
      ...
    END_USE_CODE    
 */

<*>"USE_CODE_IF"[ \t]*"(" {
    printf("USE_CODE_IF\n");
    yy_push_state(PREPROC_IF, yyscanner);
}
<*>"USE_CODE_IF_NOT"[ \t]*"(" {
    printf("USE_CODE_IF_NOT\n");
    yy_push_state(PREPROC_IF_NOT, yyscanner);
}
<PREPROC_IF>{ID} {
    printf("preproc use code if '%s'\n", yytext);
    yy_pop_state(yyscanner);
    if (yyextra->isPreprocessorConditionSet(yytext))
        yy_push_state(PREPROC_PRE_BODY_USE, yyscanner);
    else
        yy_push_state(PREPROC_PRE_BODY_EAT, yyscanner);
}
<PREPROC_IF_NOT>{ID} {
    printf("preproc use code if not '%s'\n", yytext);
    yy_pop_state(yyscanner);
    if (!yyextra->isPreprocessorConditionSet(yytext))
        yy_push_state(PREPROC_PRE_BODY_USE, yyscanner);
    else
        yy_push_state(PREPROC_PRE_BODY_EAT, yyscanner);
}
<PREPROC_PRE_BODY_USE>[ \t]*")" {
    yy_pop_state(yyscanner);
    yy_push_state(PREPROC_BODY_USE, yyscanner);
}
<PREPROC_PRE_BODY_EAT>[ \t]*")" {
    yy_pop_state(yyscanner);
    yy_push_state(PREPROC_BODY_EAT, yyscanner);
}
<*>.*"END_USE_CODE" {
    printf("END_USE_CODE\n");
    yy_pop_state(yyscanner);
}


 /* Language keywords */

"on" return ON;
"end" return END;
"note" return NOTE;
"init" return INIT;
"declare" return DECLARE;
"while" return WHILE;
"if" return IF;
"or" return OR;
"release" return RELEASE;
"and" return AND;
"not" return NOT;
"else" return ELSE;
"controller" return CONTROLLER;
"case" return CASE;
"select" return SELECT;
"to" return TO;
"<=" return LE;
">=" return GE;
"const" return CONST_; // note: "CONST" is already defined for C/C++ compilers on Windows by default
"polyphonic" return POLYPHONIC;
"mod" return MOD;

on|end|note|init|declare|if|then|begin|end|procedure|function {
    printf("A keyword: %s\n", yytext);
}

[&,()[\]<>=*+#/-] { return *yytext; }

("$"|"@"){ID} {
    yylval->sValue = strdup(yytext);
    return VARIABLE;
}

"%"{ID} {
    yylval->sValue = strdup(yytext);
    return VARIABLE;
}

{ID} {
    yylval->sValue = strdup(yytext);
    return IDENTIFIER;
}

":=" return ASSIGNMENT;

\n+ {
    //printf("lex: new line %d\n", yylineno, yytext);
    //return LF;
}

"{"[^}]*"}" /* eat up comments */

[ \t\r]+ /* eat up whitespace */

"..." /* eat up */

. printf( "Unrecognized character: %s\n", yytext );

%%

namespace LinuxSampler {

void ParserContext::createScanner(std::istream* is) {
   if (scanner) destroyScanner();
   this->is = is;
   yylex_init(&scanner);
   yyset_extra(this, scanner);
}

void ParserContext::destroyScanner() {
   if (!scanner) return;
   yylex_destroy(scanner);
   scanner = NULL;
}

} // namespace LinuxSampler
