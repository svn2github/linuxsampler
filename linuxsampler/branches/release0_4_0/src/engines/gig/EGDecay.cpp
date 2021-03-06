/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
 *   Copyright (C) 2005 Christian Schoenebeck                              *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this library; if not, write to the Free Software           *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston,                 *
 *   MA  02111-1307  USA                                                   *
 ***************************************************************************/

#include "EGDecay.h"

namespace LinuxSampler { namespace gig {

    EGDecay::EGDecay() {
    }

    void EGDecay::trigger(float Depth, float DecayTime, unsigned int SampleRate) {
        this->Level = Depth;

        // calculate decay parameters (lin. curve)
        StepsLeft = (int) (DecayTime * SampleRate);
        Coeff     = (1.0f - Depth) / (float) StepsLeft;

        dmsg(4,("Depth=%d, DecayTime=%f\n", Depth, DecayTime));
    }

}} // namespace LinuxSampler::gig
