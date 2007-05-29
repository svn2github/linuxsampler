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

// All application global declarations are defined here.

#ifndef __LS_GLOBAL_H__
#define __LS_GLOBAL_H__

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include <string>
#include <sstream>

#if HAVE_CONFIG_H
# include <config.h>
#endif

#if CONFIG_DEBUG_LEVEL > 0
#  define dmsg(debuglevel,x)	if (CONFIG_DEBUG_LEVEL >= debuglevel) {printf x; fflush(stdout);}
#else
#  define dmsg(debuglevel,x)
#endif // CONFIG_DEBUG_LEVEL > 0

#define EMMS __asm__ __volatile__ ("emms" ::: "st", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)", "mm0", "mm1", "mm2", "mm3", "mm4", "mm5", "mm6", "mm7")

/// defines globally the bit depth of used samples
typedef int16_t sample_t;

typedef std::string String;

/**
 * Whether a function / method call was successful, or if warnings or even an
 * error occured.
 */
enum result_type_t {
    result_type_success,
    result_type_warning,
    result_type_error
};

/**
 * Used whenever a detailed description of the result of a function / method
 * call is needed.
 */
struct result_t {
    result_type_t type;     ///< success, warning or error
    int           code;     ///< warning or error code
    String        message;  ///< detailed warning or error message
};

template<class T> inline String ToString(T o) {
	std::stringstream ss;
	ss << o;
	return ss.str();
}

class Runnable {
    public:
        virtual ~Runnable() { }
        virtual void Run() = 0;
};

extern double GLOBAL_VOLUME;

#endif // __LS_GLOBAL_H__
