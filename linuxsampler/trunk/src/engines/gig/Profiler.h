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

#ifndef __LS_GIG_PROFILER_H__
#define __LS_GIG_PROFILER_H__
#include <stdio.h>

namespace LinuxSampler { namespace gig {

    class Profiler {
        public:
	    static void Reset( void )
	    {
		    profilingSamples = 0;
		    profilingTime = 0;
	    }

	    static unsigned int GetBogoVoices( unsigned int SamplingFreq );

	    static unsigned long long Stamp( void )
	    {
		    unsigned long long temp;
		    __asm__ __volatile__ ("rdtsc" : "=A" (temp));
		    return temp;
	    }

	    static void Record( unsigned long long start,
			unsigned int samples, unsigned int skip )
	    {
		    unsigned long long stop = Stamp();
		    profilingTime += (stop - start);
		    profilingSamples += (samples - skip);
	    }

	    static void Calibrate( void );

	private:
	    static unsigned long long profilingSamples;
	    static unsigned long long profilingTime;
	    static unsigned long long ticksPerSecond;
    };

}} // namespace LinuxSampler::gig

#endif // __LS_GIG_PROFILER_H__
