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

// Allow to avoid inclusion of config.h
// (we used it for the _old_ xcode project file to avoid inclusion of
// config.h here and rather used our manually maintained version.h)
#ifndef OVERRIDE_CONFIG_H
# include <config.h>
#endif

// Make sure all mandatory configuration macros are defined.
// We don't care about optional configuration macros though.
#ifndef CONFIG_GLOBAL_ATTENUATION_DEFAULT
# error "Configuration macro CONFIG_GLOBAL_ATTENUATION_DEFAULT not defined!"
#endif // CONFIG_GLOBAL_ATTENUATION_DEFAULT
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
#ifndef CONFIG_DEFAULT_SUBFRAGMENT_SIZE
# error "Configuration macro CONFIG_DEFAULT_SUBFRAGMENT_SIZE not defined!"
#endif // CONFIG_DEFAULT_SUBFRAGMENT_SIZE
#ifndef CONFIG_VOICE_STEAL_ALGO
# error "Configuration macro CONFIG_VOICE_STEAL_ALGO not defined!"
#endif // CONFIG_VOICE_STEAL_ALGO
#ifndef CONFIG_SYSEX_BUFFER_SIZE
# error "Configuration macro CONFIG_SYSEX_BUFFER_SIZE not defined!"
#endif // CONFIG_SYSEX_BUFFER_SIZE
#ifndef CONFIG_FILTER_CUTOFF_MIN
# error "Configuration macro CONFIG_FILTER_CUTOFF_MIN not defined!"
#endif // CONFIG_FILTER_CUTOFF_MIN
#ifndef CONFIG_FILTER_CUTOFF_MAX
# error "Configuration macro CONFIG_FILTER_CUTOFF_MAX not defined!"
#endif // CONFIG_FILTER_CUTOFF_MAX
#ifndef CONFIG_PORTAMENTO_TIME_MIN
# error "Configuration macro CONFIG_PORTAMENTO_TIME_MIN not defined!"
#endif // CONFIG_PORTAMENTO_TIME_MIN
#ifndef CONFIG_PORTAMENTO_TIME_MAX
# error "Configuration macro CONFIG_PORTAMENTO_TIME_MAX not defined!"
#endif // CONFIG_PORTAMENTO_TIME_MAX
#ifndef CONFIG_PORTAMENTO_TIME_DEFAULT
# error "Configuration macro CONFIG_PORTAMENTO_TIME_DEFAULT not defined!"
#endif // CONFIG_PORTAMENTO_TIME_DEFAULT

// this is the sampler global volume coefficient that should be obeyed by all
// sampler engine implementations
double GLOBAL_VOLUME = CONFIG_GLOBAL_ATTENUATION_DEFAULT;
