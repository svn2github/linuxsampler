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

#include "voice.h"

// FIXME: no support for layers (nor crossfades) yet

DiskThread* Voice::pDiskThread = NULL;

Voice::Voice(DiskThread* pDiskThread) {
    Active             = false;
    Voice::pDiskThread = pDiskThread;
}

Voice::~Voice() {
}

/**
 *  Initializes and triggers the voice, a disk stream will be launched if
 *  needed.
 *
 *  @returns  0 on success, a value < 0 if something failed
 */
int Voice::Trigger(int MIDIKey, uint8_t Velocity, gig::Instrument* Instrument) {
    Active          = true;
    this->MIDIKey   = MIDIKey;
    pRegion         = Instrument->GetRegion(MIDIKey);
    PlaybackState   = playback_state_ram; // we always start playback from RAM cache and switch then to disk if needed
    Pos             = 0;
    ReleaseVelocity = 127; // default release velocity value

    if (!pRegion) {
        std::cerr << "Audio Thread: No Region defined for MIDI key " << MIDIKey << std::endl << std::flush;
        Kill();
        return -1;
    }

    //TODO: current MIDI controller values are not taken into account yet
    gig::DimensionRegion* pDimRgn = NULL;
    for (int i = pRegion->Dimensions - 1; i >= 0; i--) { // Check if instrument has a velocity split
        if (pRegion->pDimensionDefinitions[i].dimension == gig::dimension_velocity) {
            uint DimValues[5] = {0,0,0,0,0};
                 DimValues[i] = Velocity;
            pDimRgn = pRegion->GetDimensionRegionByValue(DimValues[4],DimValues[3],DimValues[2],DimValues[1],DimValues[0]);
            break;
        }
    }
    if (!pDimRgn) { // if there was no velocity split
        pDimRgn = pRegion->GetDimensionRegionByValue(0,0,0,0,0);
    }

    pSample = pDimRgn->pSample; // sample won't change until the voice is finished

    // Check if the sample needs disk streaming or is too short for that
    long cachedsamples = pSample->GetCache().Size / pSample->FrameSize;
    DiskVoice          = cachedsamples < pSample->SamplesTotal;

    if (DiskVoice) { // voice to be streamed from disk
        MaxRAMPos = cachedsamples - (OutputBufferSize << MAX_PITCH) / pSample->Channels;

        // check if there's a loop defined which completely fits into the cached (RAM) part of the sample
        if (pSample->Loops && pSample->LoopEnd <= MaxRAMPos) {
            RAMLoop        = true;
            LoopCyclesLeft = pSample->LoopPlayCount;
        }
        else RAMLoop = false;

        if (pDiskThread->OrderNewStream(&DiskStreamRef, pSample, MaxRAMPos, !RAMLoop) < 0) {
            dmsg(1,("Disk stream order failed!\n"));
            Kill();
            return -1;
        }
        dmsg(4,("Disk voice launched (cached samples: %d, total Samples: %d, MaxRAMPos: %d, RAMLooping: %s\n", cachedsamples, pSample->SamplesTotal, MaxRAMPos, (RAMLoop) ? "yes" : "no"));
    }
    else { // RAM only voice
        MaxRAMPos = cachedsamples;
        if (pSample->Loops) {
            RAMLoop        = true;
            LoopCyclesLeft = pSample->LoopPlayCount;
        }
        else RAMLoop = false;
        dmsg(4,("RAM only voice launched (Looping: %s)\n", (RAMLoop) ? "yes" : "no"));
    }


    // Pitch according to keyboard position (if 'PitchTrack' is set)
    CurrentPitch = (pDimRgn->PitchTrack) ? pow(2, ((double) (MIDIKey - (int) pDimRgn->UnityNote) + (double) pDimRgn->FineTune / 100.0) / 12.0)
                                         : pow(2, ((double) pDimRgn->FineTune / 100.0) / 12.0);

    Volume = pDimRgn->GetVelocityAttenuation(Velocity);

    EG1.Trigger(pDimRgn->EG1PreAttack, pDimRgn->EG1Attack, pDimRgn->EG1Release);

    // ************************************************
    // TODO: ARTICULATION DATA HANDLING IS MISSING HERE
    // ************************************************

    return 0; // success
}

/**
 *  Renders the audio data for this voice for the current audio fragment.
 *  The sample input data can either come from RAM (cached sample or sample
 *  part) or directly from disk. The output signal will be rendered by
 *  resampling / interpolation. If this voice is a disk streaming voice and
 *  the voice completely played back the cached RAM part of the sample, it
 *  will automatically switch to disk playback for the next RenderAudio()
 *  call.
 */
void Voice::RenderAudio() {

    // Let all modulators throw their parameter changes for the current audio fragment
    ModulationSystem::ResetDestinationParameter(ModulationSystem::destination_vca, this->Volume);
    EG1.ProcessFragment();


    switch (this->PlaybackState) {

        case playback_state_ram: {
                if (RAMLoop) InterpolateAndLoop((sample_t*) pSample->GetCache().pStart);
                else         Interpolate((sample_t*) pSample->GetCache().pStart);
                if (DiskVoice) {
                    // check if we reached the allowed limit of the sample RAM cache
                    if (Pos > MaxRAMPos) {
                        dmsg(5,("Voice: switching to disk playback (Pos=%f)\n", Pos));
                        this->PlaybackState = playback_state_disk;
                    }
                }
                else if (Pos >= pSample->GetCache().Size / pSample->FrameSize) {
                    this->PlaybackState = playback_state_end;
                }
            }
            break;

        case playback_state_disk: {
                if (!DiskStreamRef.pStream) {
                    // check if the disk thread created our ordered disk stream in the meantime
                    DiskStreamRef.pStream = pDiskThread->AskForCreatedStream(DiskStreamRef.OrderID);
                    if (!DiskStreamRef.pStream) {
                        std::cout << stderr << "Disk stream not available in time!" << std::endl << std::flush;
                        Kill();
                        return;
                    }
                    DiskStreamRef.pStream->IncrementReadPos(pSample->Channels * (double_to_int(Pos) - MaxRAMPos));
                    Pos -= double_to_int(Pos);
                }

                // add silence sample at the end if we reached the end of the stream (for the interpolator)
                if (DiskStreamRef.State == Stream::state_end && DiskStreamRef.pStream->GetReadSpace() < (OutputBufferSize << MAX_PITCH) / pSample->Channels) {
                    DiskStreamRef.pStream->WriteSilence((OutputBufferSize << MAX_PITCH) / pSample->Channels);
                    this->PlaybackState = playback_state_end;
                }

                sample_t* ptr = DiskStreamRef.pStream->GetReadPtr(); // get the current read_ptr within the ringbuffer where we read the samples from
                Interpolate(ptr);
                DiskStreamRef.pStream->IncrementReadPos(double_to_int(Pos) * pSample->Channels);
                Pos -= double_to_int(Pos);
            }
            break;

        case playback_state_end:
            Kill(); // free voice
            break;
    }

    // If release stage finished, let the voice be killed
    if (EG1.GetStage() == EG_VCA::stage_end) this->PlaybackState = playback_state_end;
}

/**
 *  Interpolates the input audio data (no loop).
 *
 *  @param pSrc - pointer to input sample data
 */
void Voice::Interpolate(sample_t* pSrc) {
    int i = 0;
    float e = 1.0;

    // FIXME: assuming either mono or stereo
    if (this->pSample->Channels == 2) { // Stereo Sample
        while (i < this->OutputBufferSize) {
            InterpolateOneStep_Stereo(pSrc, i, ModulationSystem::pDestinationParameter[ModulationSystem::destination_vca][i>>1]);
        }
    }
    else { // Mono Sample
        while (i < this->OutputBufferSize) {
            InterpolateOneStep_Mono(pSrc, i, ModulationSystem::pDestinationParameter[ModulationSystem::destination_vca][i>>1]);
        }
    }
}

/**
 *  Interpolates the input audio data, this method honors looping.
 *
 *  @param pSrc - pointer to input sample data
 */
void Voice::InterpolateAndLoop(sample_t* pSrc) {
    int i = 0;

    // FIXME: assuming either mono or stereo
    if (pSample->Channels == 2) { // Stereo Sample
        if (pSample->LoopPlayCount) {
            // render loop (loop count limited)
            while (i < OutputBufferSize && LoopCyclesLeft) {
                InterpolateOneStep_Stereo(pSrc, i, ModulationSystem::pDestinationParameter[ModulationSystem::destination_vca][i>>1]);
                if (Pos > pSample->LoopEnd) {
                    Pos = pSample->LoopStart + fmod(Pos - pSample->LoopEnd, pSample->LoopSize);;
                    LoopCyclesLeft--;
                }
            }
            // render on without loop
            while (i < OutputBufferSize) {
                InterpolateOneStep_Stereo(pSrc, i, ModulationSystem::pDestinationParameter[ModulationSystem::destination_vca][i>>1]);
            }
        }
        else { // render loop (endless loop)
            while (i < OutputBufferSize) {
                InterpolateOneStep_Stereo(pSrc, i, ModulationSystem::pDestinationParameter[ModulationSystem::destination_vca][i>>1]);
                if (Pos > pSample->LoopEnd) {
                    Pos = pSample->LoopStart + fmod(Pos - pSample->LoopEnd, pSample->LoopSize);
                }
            }
        }
    }
    else { // Mono Sample
        if (pSample->LoopPlayCount) {
            // render loop (loop count limited)
            while (i < OutputBufferSize && LoopCyclesLeft) {
                InterpolateOneStep_Mono(pSrc, i, ModulationSystem::pDestinationParameter[ModulationSystem::destination_vca][i>>1]);
                if (Pos > pSample->LoopEnd) {
                    Pos = pSample->LoopStart + fmod(Pos - pSample->LoopEnd, pSample->LoopSize);;
                    LoopCyclesLeft--;
                }
            }
            // render on without loop
            while (i < OutputBufferSize) {
                InterpolateOneStep_Mono(pSrc, i, ModulationSystem::pDestinationParameter[ModulationSystem::destination_vca][i>>1]);
            }
        }
        else { // render loop (endless loop)
            while (i < OutputBufferSize) {
                InterpolateOneStep_Mono(pSrc, i, ModulationSystem::pDestinationParameter[ModulationSystem::destination_vca][i>>1]);
                if (Pos > pSample->LoopEnd) {
                    Pos = pSample->LoopStart + fmod(Pos - pSample->LoopEnd, pSample->LoopSize);;
                }
            }
        }
    }
}

/**
 *  Immediately kill the voice.
 */
void Voice::Kill() {
    if (DiskVoice && DiskStreamRef.State != Stream::state_unused) {
        pDiskThread->OrderDeletionOfStream(&DiskStreamRef);
    }
    DiskStreamRef.pStream = NULL;
    DiskStreamRef.hStream = 0;
    DiskStreamRef.State   = Stream::state_unused;
    DiskStreamRef.OrderID = 0;
    Active = false;
}

/**
 *  Release the voice in an appropriate time range, the voice will go through
 *  it's release stage before it will be killed.
 */
void Voice::Release() {
   EG1.Release();
}
