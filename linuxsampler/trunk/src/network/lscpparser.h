/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
 *   Copyright (C) 2005 - 2007 Christian Schoenebeck                       *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the Free Software           *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston,                 *
 *   MA  02111-1307  USA                                                   *
 ***************************************************************************/

#ifndef __LSCPPARSER_H__
#define __LSCPPARSER_H__

#include <sys/types.h>
#include <sys/socket.h>

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>

#include "../common/global.h"
#include "../common/Path.h"
#include "lscpevent.h"
#include "../Sampler.h"
#include "../drivers/midi/MidiInstrumentMapper.h"

/// Will be returned by the parser in case of syntax errors.
#define LSCP_SYNTAX_ERROR	-69
#define LSCP_QUIT		-1
#define LSCP_DONE		0

using namespace LinuxSampler;

// just symbol prototyping
class LSCPServer;

/**
 * How the fill states of disk stream buffers should be reflected.
 */
enum fill_response_t {
    fill_response_bytes,      ///< The returned values are meant in bytes.
    fill_response_percentage  ///< The returned values are meant in percentage.
};

/**
 * Semantic value of the lookahead symbol.
 *
 * Structure that is used by the parser to process and return values from the
 * input text. The lexical analyzer for example returns a number for
 * recognized number strings in the input text and the parser might return a
 * value for each of it's rules.
 */
struct _YYSTYPE {
    union {
        char                         Char;
        unsigned int                 Number;
        bool                         Bool;
        double                       Dotnum;
        fill_response_t              FillResponse;
        LSCPEvent::event_t           Event;
        MidiInstrumentMapper::mode_t LoadMode;
    };
    std::string                       String;
    std::map<std::string,std::string> KeyValList;
    Path                              UniversalPath;
};
#define YYSTYPE _YYSTYPE
#define yystype YYSTYPE		///< For backward compatibility.
#define YYSTYPE_IS_DECLARED	///< We tell the lexer / parser that we use our own data structure as defined above.

/**
 * Parameters given to the parser on every yyparse() call.
 */
struct yyparse_param_t {
    LSCPServer* pServer;
    int         hSession;
    bool        bVerbose; ///< if true then all commands will immediately sent back (echo)
    int         iLine;    ///< Current line (just for verbosity / messages)
    int         iColumn;  ///< Current column (just for verbosity / messages)

    yyparse_param_t() {
        pServer  = NULL;
        hSession = -1;
        bVerbose = false;
        iLine = iColumn = 0;
    }
};
#define YYPARSE_PARAM yyparse_param

/**
 * Prototype of the main scanner function (lexical analyzer).
 */
#define YY_DECL int yylex(YYSTYPE* yylval)

#endif // __LSCPPARSER_H__
