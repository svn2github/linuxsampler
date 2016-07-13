/*
 * Copyright (c) 2016 Christian Schoenebeck
 *
 * http://www.linuxsampler.org
 *
 * This file is part of LinuxSampler and released under the same terms.
 * See README file for details.
 */

#include "InstrumentScriptVMFunctions.h"
#include "InstrumentScriptVMDynVars.h"
#include "InstrumentScriptVM.h"
#include "../AbstractEngineChannel.h"

namespace LinuxSampler {

    int InstrumentScriptVMDynVar_ENGINE_UPTIME::evalInt() {

        AbstractEngineChannel* pEngineChannel =
            static_cast<AbstractEngineChannel*>(m_vm->m_event->cause.pEngineChannel);

        AbstractEngine* pEngine =
            static_cast<AbstractEngine*>(pEngineChannel->GetEngine());

        // engine's official playback time in milliseconds (offline bounce safe)
        return int( double(pEngine->FrameTime + m_vm->m_event->cause.FragmentPos()) /
                    double(pEngine->SampleRate) * 1000.0 );
    }

} // namespace LinuxSampler
