/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
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
#include "../Sampler.h"

/// Will be returned by the parser in case of syntax errors.
#define LSCP_SYNTAX_ERROR	-69

using namespace LinuxSampler;

/**
 * How the fill states of disk stream buffers should be reflected.
 */
enum fill_response_t {
    fill_response_bytes,      ///< The returned values are meant in bytes.
    fill_response_percentage  ///< The returned values are meant in percentage.
};

/**
 * Event types
 */
enum event_t {
    event_channels,
    event_voice_count,
    event_stream_count,
    event_channel_buffer_fill,
    event_channel_info,
    event_misc
};

/**
 * Semantic value of the lookahead symbol.
 *
 * Structure that is used by the parser to process and return values from the
 * input text. The lexical analyzer for example returns a number for
 * recognized number strings in the input text and the parser might return a
 * value for each of it's rules.
 */
struct YYSTYPE {
    union {
        char            Char;
        unsigned int    Number;
        double          Dotnum;
        fill_response_t FillResponse;
	event_t	        Event;
    };
    std::string                       String;
    std::map<std::string,std::string> KeyValList;
};
#define yystype YYSTYPE		///< For backward compatibility.
#define YYSTYPE_IS_DECLARED	///< We tell the lexer / parser that we use our own data structure as defined above.

// just symbol prototyping
class LSCPServer;

// pointer to an (reentrant) scanner / lexical analyzer
typedef void* yyscan_t;

/**
 * Parameters given to the parser on every yyparse() call.
 */
struct yyparse_param_t {
    LSCPServer* pServer;
    yyscan_t    pScanner;
};
#define YYPARSE_PARAM yyparse_param

/**
 * Prototype of the main scanner function (lexical analyzer).
 */
#define YY_DECL int yylex(YYSTYPE* yylval, yyscan_t yyscanner)

/**
 * Override lex's input function which just reads from stdin by default.
 * We read from a socket instead.
 */
#define YY_INPUT(buf,result,max_size) \
	errno=0; \
	while ( (result = recv(hSession, buf, max_size, 0)) < 0 ) \
	{ \
		if(errno != EINTR) \
		{ \
			switch(errno) { \
				case EBADF: \
					dmsg(2,("LSCPScanner: The argument s is an invalid descriptor.\n")); \
					break; \
				case ECONNREFUSED: \
					dmsg(2,("LSCPScanner: A remote host refused to allow the network connection (typically because it is not running the requested service).\n")); \
					break; \
				case ENOTCONN: \
					dmsg(2,("LSCPScanner: The socket is associated with a connection-oriented protocol and has not been connected (see connect(2) and accept(2)).\n")); \
					break; \
				case ENOTSOCK: \
					dmsg(2,("LSCPScanner: The argument s does not refer to a socket.\n")); \
					break; \
				case EAGAIN: \
					dmsg(2,("LSCPScanner: The socket is marked non-blocking and the receive operation would block, or a receive timeout had been set and the timeout expired before data was received.\n")); \
					break; \
				case EINTR: \
					dmsg(2,("LSCPScanner: The receive was interrupted by delivery of a signal before any data were available.\n")); \
					break; \
				case EFAULT: \
					dmsg(2,("LSCPScanner: The receive buffer pointer(s) point outside the process's address space.\n")); \
					break; \
				case EINVAL: \
					dmsg(2,("LSCPScanner: Invalid argument passed.\n")); \
					break; \
				case ENOMEM: \
					dmsg(2,("LSCPScanner: Could not allocate memory for recvmsg.\n")); \
					break; \
				default: \
					dmsg(2,("LSCPScanner: Unknown recv() error.\n")); \
					break; \
			} \
			YY_FATAL_ERROR( "input in flex scanner failed" ); \
			break; \
		} \
		errno=0; \
		clearerr(yyin); \
	}\


#endif // __LSCPPARSER_H__
