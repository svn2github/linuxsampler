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

#include <stdint.h>
#include <stdio.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#define LS_DEBUG_LEVEL	1  ///< the higher this value the higher verbosity, 0 means no debug messages at all

#if LS_DEBUG_LEVEL > 0
#  define dmsg(debuglevel,x)	if (LS_DEBUG_LEVEL >= debuglevel) {printf x; fflush(stdout);}
#else
#  define dmsg(debuglevel,x)
#endif // LS_DEBUG

// defines globally the bit depth of used samples
typedef int16_t sample_t;

#endif // __GLOBAL_H__
