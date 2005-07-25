/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
 *   Copyright (C) 2005 Christian Schoenebeck                              *
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

#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include <string>
#include <sstream>

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

// Make sure all mandatory configuration macros are defined.
// We don't care about optional configuration macros though.
#ifndef CONFIG_MAX_PITCH
# error "Configuration macro CONFIG_MAX_PITCH not defined!"
#endif // CONFIG_MAX_PITCH
#ifndef CONFIG_MAX_EVENTS_PER_FRAGMENT
# error "Configuration macro CONFIG_MAX_EVENTS_PER_FRAGMENT not defined!"
#endif // CONFIG_MAX_EVENTS_PER_FRAGMENT
#ifndef CONFIG_EG_BOTTOM
# error "Configuration macro CONFIG_EG_BOTTOM not defined!"
#endif // CONFIG_EG_BOTTOM
#ifndef CONFIG_EG_MIN_RELEASE_TIME
# error "Configuration macro CONFIG_EG_MIN_RELEASE_TIME not defined!"
#endif // CONFIG_EG_MIN_RELEASE_TIME
#ifndef CONFIG_REFILL_STREAMS_PER_RUN
# error "Configuration macro CONFIG_REFILL_STREAMS_PER_RUN not defined!"
#endif // CONFIG_REFILL_STREAMS_PER_RUN
#ifndef CONFIG_STREAM_MIN_REFILL_SIZE
# error "Configuration macro CONFIG_STREAM_MIN_REFILL_SIZE not defined!"
#endif // CONFIG_STREAM_MIN_REFILL_SIZE
#ifndef CONFIG_STREAM_MAX_REFILL_SIZE
# error "Configuration macro CONFIG_STREAM_MAX_REFILL_SIZE not defined!"
#endif // CONFIG_STREAM_MAX_REFILL_SIZE
#ifndef CONFIG_STREAM_BUFFER_SIZE
# error "Configuration macro CONFIG_STREAM_BUFFER_SIZE not defined!"
#endif // CONFIG_STREAM_BUFFER_SIZE
#ifndef CONFIG_MAX_STREAMS
# error "Configuration macro CONFIG_MAX_STREAMS not defined!"
#endif // CONFIG_MAX_STREAMS
#ifndef CONFIG_MAX_VOICES
# error "Configuration macro CONFIG_MAX_VOICES not defined!"
#endif // CONFIG_MAX_VOICES
#ifndef CONFIG_VOICE_STEAL_ALGO
# error "Configuration macro CONFIG_VOICE_STEAL_ALGO not defined!"
#endif // CONFIG_VOICE_STEAL_ALGO
#ifndef CONFIG_SYSEX_BUFFER_SIZE
# error "Configuration macro CONFIG_SYSEX_BUFFER_SIZE not defined!"
#endif // CONFIG_SYSEX_BUFFER_SIZE
#ifndef CONFIG_FILTER_UPDATE_STEPS
# error "Configuration macro CONFIG_FILTER_UPDATE_STEPS not defined!"
#endif // CONFIG_FILTER_UPDATE_STEPS
#ifndef CONFIG_FILTER_CUTOFF_MIN
# error "Configuration macro CONFIG_FILTER_CUTOFF_MIN not defined!"
#endif // CONFIG_FILTER_CUTOFF_MIN
#ifndef CONFIG_FILTER_CUTOFF_MAX
# error "Configuration macro CONFIG_FILTER_CUTOFF_MAX not defined!"
#endif // CONFIG_FILTER_CUTOFF_MAX

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

#endif // __GLOBAL_H__
