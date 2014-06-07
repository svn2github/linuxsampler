/*
 * Copyright (c) 2014 Christian Schoenebeck
 *
 * http://www.linuxsampler.org
 *
 * This file is part of LinuxSampler and released under the same terms.
 * See README file for details.
 */

#include "InstrumentScriptVMFunctions.h"
#include "InstrumentScriptVM.h"
#include "EngineChannel.h"

namespace LinuxSampler { namespace gig {

  /////////////////////////////////////////////////////////////////////////
  // Function:
  //     gig_set_dim_zone(event_id, dimension, zone)

    InstrumentScriptVMFunction_gig_set_dim_zone::InstrumentScriptVMFunction_gig_set_dim_zone(InstrumentScriptVM* parent)
        : m_vm(parent)
    {
    }

    VMFnResult* InstrumentScriptVMFunction_gig_set_dim_zone::exec(VMFnArgs* args) {
        int id   = args->arg(0)->asInt()->evalInt();
        int dim  = args->arg(1)->asInt()->evalInt();
        int zone = args->arg(2)->asInt()->evalInt();

        if (id < 0) {
            wrnMsg("gig_set_dim_zone(): argument 1 may not be a negative event ID");
            return successResult();
        }

        int note = m_vm->m_event->cause.Param.Note.Key;

        EngineChannel* pEngineChannel =
            static_cast<EngineChannel*>(m_vm->m_event->cause.pEngineChannel);

        ::gig::Region* pRegion = pEngineChannel->pInstrument->GetRegion(note);
        if (!pRegion) return successResult();

        int idx = -1, baseBits = 0;
        for (int i = 0; i < pRegion->Dimensions; ++i) {
            if (pRegion->pDimensionDefinitions[i].dimension == dim) {
                idx = i;
                break;
            }
            baseBits += pRegion->pDimensionDefinitions[i].bits;
        }
        if (idx < 0) return successResult(); // no such dimension found

        RTList<Event>::Iterator itEvent = pEngineChannel->pEngine->EventByID(id);
        if (!itEvent) return successResult();

        int bits = pRegion->pDimensionDefinitions[idx].bits;
        int mask = 0;
        for (int i = 0; i < bits; ++i) mask |= (1 << (baseBits + i));

        itEvent->Format.Gig.DimMask |= mask;
        itEvent->Format.Gig.DimBits |= (zone << baseBits) & mask;

        return successResult();
    }

}} // namespace LinuxSampler::gig
