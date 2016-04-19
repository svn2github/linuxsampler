/*
 * Copyright (c) 2014-2016 Christian Schoenebeck
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
            const ScriptID id = args->arg(0)->asInt()->evalInt();
            if (!id) {
                wrnMsg("gig_set_dim_zone(): note ID for argument 1 may not be zero");
                return successResult();
            }
            if (!id.isNoteID()) {
                wrnMsg("gig_set_dim_zone(): argument 1 is not a note ID");
                return successResult();
            }

            NoteBase* pNote = pEngineChannel->pEngine->NoteByID( id.noteID() );
            if (!pNote) {
                dmsg(2,("gig_set_dim_zone(): no active note with ID %d\n", int(id)));
                return successResult();
            }

            int note = pNote->cause.Param.Note.Key;

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

            pNote->Format.Gig.DimMask |= mask;
            pNote->Format.Gig.DimBits |= (zone << baseBits) & mask;

            dmsg(3,("gig_set_dim_zone(): success, mask=%d bits=%d\n", pNote->Format.Gig.DimMask, pNote->Format.Gig.DimBits));
        } else if (args->arg(0)->exprType() == INT_ARR_EXPR) {
            VMIntArrayExpr* ids = args->arg(0)->asIntArray();
            for (int i = 0; i < ids->arraySize(); ++i) {
                const ScriptID id = ids->evalIntElement(i);
                if (!id || !id.isNoteID()) continue;

                NoteBase* pNote = pEngineChannel->pEngine->NoteByID( id.noteID() );
                if (!pNote) continue;

                int note = pNote->cause.Param.Note.Key;

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

                pNote->Format.Gig.DimMask |= mask;
                pNote->Format.Gig.DimBits |= (zone << baseBits) & mask;

                dmsg(3,("gig_set_dim_zone(): success, mask=%d bits=%d\n", pNote->Format.Gig.DimMask, pNote->Format.Gig.DimBits));
            }
        }

        return successResult();
    }

}} // namespace LinuxSampler::gig
