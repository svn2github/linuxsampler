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

#ifndef __MODULATION_SYSTEM_H__
#define __MODULATION_SYSTEM_H__

#include "global.h"

class ModulationSystem {
    public:
        enum destination_t {
            destination_vca,   ///< Volume level
            destination_count  ///< Total number of modulation sources (this has to stay the last element in the enum)
        };
        enum source_t {
            source_eg1,   ///< Envelope Generator 1
            source_count  ///< Total number of modulation sources (this has to stay the last element in the enum)
        };

        static float** pDestinationParameter;
        //static bool    DestinationParameterModified;

        static        void Initialize(uint SampleRate, uint MaxSamplesPerCycle);
        static        void Close();
        static        void ResetDestinationParameter(ModulationSystem::destination_t dst, float val);
        static inline uint GetMaxSamplesPerCycle() { return uiMaxSamplesPerCycle; };
        static inline uint GetSampleRate()         { return uiSampleRate;         };
    protected:
        static uint uiMaxSamplesPerCycle;
        static uint uiSampleRate;
};

#endif // __MODULATION_SYSTEM_H__
