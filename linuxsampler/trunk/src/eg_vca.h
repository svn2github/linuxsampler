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

#ifndef __EG_VCA_H__
#define __EG_VCA_H__

#include <math.h>

#include "global.h"
#include "modulationsystem.h"

#define EG_ENVELOPE_LIMIT	0.001
#define EG_MIN_RELEASE_TIME	0.005

/**
 * VCA Envelope Generator
 *
 * This EG controls volume attenuation.
 */
class EG_VCA {
    public:
        enum stage_t {
            stage_attack,
            stage_sustain,
            stage_release,
            stage_end
        };

        static const double Limit;

        EG_VCA();
        void ProcessFragment();
        void Trigger(uint PreAttack, double Attack, double Release);
        void Release();
        inline EG_VCA::stage_t GetStage() { return Stage; };
    protected:
        float   Level;
        bool    ReleaseSignalReceived;
        stage_t Stage;
        float   AttackCoeff;
        long    AttackStepsLeft;   ///< number of sample points til end of attack stage
        float   ReleaseCoeff;
        long    ReleaseStepsLeft;  ///< number of sample points til end of release stage

        inline long Min(long A, long B) {
            return (A > B) ? B : A;
        }
};

#endif // __EG_VCA_H__
