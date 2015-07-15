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

    bool InstrumentScriptVMFunction_gig_set_dim_zone::acceptsArgType(int iArg, ExprType_t type) const {
        return type == INT_EXPR || type == INT_ARR_EXPR;
    }

    VMFnResult* InstrumentScriptVMFunction_gig_set_dim_zone::exec(VMFnArgs* args) {
        EngineChannel* pEngineChannel =
            static_cast<EngineChannel*>(m_vm->m_event->cause.pEngineChannel);

        int dim  = args->arg(1)->asInt()->evalInt();
        int zone = args->arg(2)->asInt()->evalInt();

        if (args->arg(0)->exprType() == INT_EXPR) {
            int id  = args->arg(0)->asInt()->evalInt();
            if (id < 0) {
                wrnMsg("gig_set_dim_zone(): argument 1 may not be a negative event ID");
                return successResult();
            }

            RTList<Event>::Iterator itEvent = pEngineChannel->pEngine->EventByID(id);
            if (!itEvent) {
                dmsg(2,("gig_set_dim_zone(): no active event with ID %d\n", id));
                return successResult();
            }

            int note = itEvent->Param.Note.Key;

            ::gig::Region* pRegion = pEngineChannel->pInstrument->GetRegion(note);
            if (!pRegion) {
                dmsg(2,("gig_set_dim_zone(): no region for key %d\n", note));
                return successResult();
            }

            int idx = -1, baseBits = 0;
            for (int i = 0; i < pRegion->Dimensions; ++i) {
                if (pRegion->pDimensionDefinitions[i].dimension == dim) {
                    idx = i;
                    break;
                }
                baseBits += pRegion->pDimensionDefinitions[i].bits;
            }
            if (idx < 0) {
                dmsg(2,("gig_set_dim_zone(): no such gig dimension %d\n", dim));
                return successResult(); // no such dimension found
            }

            int bits = pRegion->pDimensionDefinitions[idx].bits;
            int mask = 0;
            for (int i = 0; i < bits; ++i) mask |= (1 << (baseBits + i));

            itEvent->Format.Gig.DimMask |= mask;
            itEvent->Format.Gig.DimBits |= (zone << baseBits) & mask;

            dmsg(3,("gig_set_dim_zone(): success, mask=%d bits=%d\n", itEvent->Format.Gig.DimMask, itEvent->Format.Gig.DimBits));
        } else if (args->arg(0)->exprType() == INT_ARR_EXPR) {
            VMIntArrayExpr* ids = args->arg(0)->asIntArray();
            for (int i = 0; i < ids->arraySize(); ++i) {
                int id = ids->evalIntElement(i);
                if (id < 0) continue;

                RTList<Event>::Iterator itEvent = pEngineChannel->pEngine->EventByID(id);
                if (!itEvent) continue;

                int note = itEvent->Param.Note.Key;

                ::gig::Region* pRegion = pEngineChannel->pInstrument->GetRegion(note);
                if (!pRegion) continue;

                int idx = -1, baseBits = 0;
                for (int i = 0; i < pRegion->Dimensions; ++i) {
                    if (pRegion->pDimensionDefinitions[i].dimension == dim) {
                        idx = i;
                        break;
                    }
                    baseBits += pRegion->pDimensionDefinitions[i].bits;
                }
                if (idx < 0) continue;

                int bits = pRegion->pDimensionDefinitions[idx].bits;
                int mask = 0;
                for (int i = 0; i < bits; ++i) mask |= (1 << (baseBits + i));

                itEvent->Format.Gig.DimMask |= mask;
                itEvent->Format.Gig.DimBits |= (zone << baseBits) & mask;

                dmsg(3,("gig_set_dim_zone(): success, mask=%d bits=%d\n", itEvent->Format.Gig.DimMask, itEvent->Format.Gig.DimBits));
            }
        }

        return successResult();
    }

}} // namespace LinuxSampler::gig
