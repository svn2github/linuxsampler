/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003 by Benno Senoner and Christian Schoenebeck         *
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

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#define LS_DEBUG_LEVEL	1  ///< the higher this value the higher verbosity, 0 means no debug messages at all

#if LS_DEBUG_LEVEL > 0
#  define dmsg(debuglevel,x)	if (LS_DEBUG_LEVEL >= debuglevel) {printf x; fflush(stdout);}
#else
#  define dmsg(debuglevel,x)
#endif // LS_DEBUG

/// Defines the max. pitch value used in the application (in octaves)
#define MAX_PITCH			4

/// Defines how many event objects the modulation system allocates
#define MAX_EVENTS_PER_FRAGMENT		1024

/// defines globally the bit depth of used samples
typedef int16_t sample_t;

typedef std::string String;

/**
 * Wether a function / method call was successful, or if warnings or even an
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

#endif // __GLOBAL_H__
