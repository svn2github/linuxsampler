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

#include "EGDecay.h"

namespace LinuxSampler { namespace gig {

    EGDecay::EGDecay(gig::Engine* pEngine, Event::destination_t ModulationDestination) {
        this->ModulationDestination = ModulationDestination;
        this->pEngine = pEngine;
    }

    /**
     * Will be called by the voice for every audio fragment to let the EG
     * queue it's modulation changes for the current audio fragment.
     *
     * @param Samples - total number of sample points to be rendered in this
     *                  audio fragment cycle by the audio engine
     */
    void EGDecay::Process(uint Samples) {
        if (!DecayStepsLeft) return;

        int iSample     = TriggerDelay;
        int to_process  = RTMath::Min(Samples - iSample, DecayStepsLeft);
        int process_end = iSample + to_process;
        DecayStepsLeft -= to_process;
        while (iSample < to_process) {
            pEngine->pSynthesisParameters[ModulationDestination][iSample++] *= Level;
            Level += DecayCoeff;
        }
        TriggerDelay = 0;
    }

    /**
     * Will be called by the voice when the key / voice was triggered.
     *
     * @param Depth     - Initial level of the envelope
     * @param DecayTime - Decay time of the envelope (0.000 - 10.000s)
     * @param Delay     - Number of sample points triggering should be delayed.
     */
    void EGDecay::Trigger(float Depth, double DecayTime, uint Delay) {
        this->TriggerDelay = Delay;
        this->Level        = Depth;

        // calculate decay parameters (lin. curve)
        DecayStepsLeft = (long) (DecayTime * pEngine->pAudioOutputDevice->SampleRate());
        DecayCoeff     = (1.0 - Depth) / DecayStepsLeft;

        dmsg(4,("Depth=%d, DecayTime=%f\n", Depth, DecayTime));
    }

}} // namespace LinuxSampler::gig
