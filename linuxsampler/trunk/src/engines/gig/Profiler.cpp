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

#include "Profiler.h"
#include <time.h>

namespace LinuxSampler { namespace gig {

	unsigned long long Profiler::profilingSamples = 0;
	unsigned long long Profiler::profilingTime = 0;
	unsigned long long Profiler::ticksPerSecond = 0;

	void Profiler::Calibrate( void )
	{
		clock_t start_time = clock();
		unsigned long long start_clocks = Stamp();
		volatile int a = 1;
		volatile int b = 1;
		for (volatile int i = 0; i < 100000000; i++)
		{
			a += b;
		}
		clock_t stop_time = clock();
		unsigned long long stop_clocks = Stamp();
		unsigned int diff_ticks = (unsigned int) (stop_clocks - start_clocks);
		double diff_time = ((stop_time - start_time) / (double(CLOCKS_PER_SEC)));
		ticksPerSecond = (unsigned long long)(double(diff_ticks) / diff_time);
	}

	unsigned int Profiler::GetBogoVoices(unsigned int SamplingFreq)
	{
		if (profilingSamples == 0) return 0;
		unsigned int avgTicks = profilingTime / profilingSamples;
		unsigned int samplesPerSecond = ticksPerSecond / avgTicks;
		unsigned int bogoVoices = samplesPerSecond / SamplingFreq;
		return bogoVoices;
	}

}} // namespace LinuxSampler::gig
