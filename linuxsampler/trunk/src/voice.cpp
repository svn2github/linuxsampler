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

void Voice::Trigger(int MIDIKey, uint8_t Velocity, gig::Instrument* Instrument) {
    Active          = true;
    this->MIDIKey   = MIDIKey;
    pRegion         = Instrument->GetRegion(MIDIKey);
    PlaybackState   = playback_state_ram; // we always start playback from RAM cache and switch then to disk if needed
    Pos             = 0;
    ReleaseVelocity = 127; // default release velocity value

    if (!pRegion) {
        std::cerr << "Audio Thread: No Region defined for MIDI key " << MIDIKey << std::endl << std::flush;
        Active = false;
        return;
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

    if (DiskVoice) {
        MaxRAMPos = cachedsamples - (OutputBufferSize << MAX_PITCH) / pSample->Channels;
        pDiskThread->OrderNewStream(&DiskStreamRef, pSample, MaxRAMPos);
        dmsg(5,("Disk voice launched (cached samples: %d, total Samples: %d, MaxRAMPos: %d\n", cachedsamples, pSample->SamplesTotal, MaxRAMPos));
    }
    else {
        MaxRAMPos = cachedsamples;
        dmsg(5,("RAM only voice launched\n"));
    }

    CurrentPitch = pow(2, (double) (MIDIKey - (int) pSample->MIDIUnityNote) / (double) 12);

    // ************************************************
    // TODO: ARTICULATION DATA HANDLING IS MISSING HERE
    // ************************************************
}

void Voice::RenderAudio() {

    switch (this->PlaybackState) {

        case playback_state_ram: {
                Interpolate((sample_t*) pSample->GetCache().pStart);
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
                        pDiskThread->OrderDeletionOfStream(&DiskStreamRef);
                        this->Active = false;
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
}

void Voice::Interpolate(sample_t* pSrc) {
    float effective_volume = 1;  // TODO: use the art. data instead
    int   i = 0;

    // ************************************************
    // TODO: ARTICULATION DATA HANDLING IS MISSING HERE
    // ************************************************

    // FIXME: assuming either mono or stereo
    if (this->pSample->Channels == 2) { // Stereo Sample
        while (i < this->OutputBufferSize) {
            #ifdef USE_LINEAR_INTERPOLATION
                int   pos_int   = double_to_int(this->Pos);  // integer position
                float pos_fract = this->Pos - pos_int;       // fractional part of position
                pos_int <<= 1;
                // left channel
                this->pOutput[i++] += effective_volume * (pSrc[pos_int]   + pos_fract * (pSrc[pos_int+2] - pSrc[pos_int]));
                // right channel
                this->pOutput[i++] += effective_volume * (pSrc[pos_int+1] + pos_fract * (pSrc[pos_int+3] - pSrc[pos_int+1]));
            #else // polynomial interpolation
                //FIXME: !!!THIS WON'T WORK!!! needs to be adjusted for stereo, use linear interpolation meanwhile
                xm1 = pSrc[pos_int];
                x0  = pSrc[pos_int+1];
                x1  = pSrc[pos_int+2];
                x2  = pSrc[pos_int+3];
                a   = (3 * (x0-x1) - xm1 + x2) / 2;
                b   = 2 * x1 + xm1 - (5 * x0 + x2) / 2;
                c   = (x1 - xm1) / 2;
                this->pOutput[u] += effective_volume*((((a * pos_fract) + b) * pos_fract + c) * pos_fract + x0);
            #endif // USE_LINEAR_INTERPOLATION

            this->Pos += this->CurrentPitch;
        }
    }
    else { // Mono Sample
        while (i < this->OutputBufferSize) {
            #ifdef USE_LINEAR_INTERPOLATION
                int   pos_int       = double_to_int(this->Pos);  // integer position
                float pos_fract     = this->Pos - pos_int;       // fractional part of position
                float sample_point  = effective_volume * (pSrc[pos_int] + pos_fract * (pSrc[pos_int+1] - pSrc[pos_int]));
                this->pOutput[i]   += sample_point;
                this->pOutput[i+1] += sample_point;
                i += 2;
            #else // polynomial interpolation
                //FIXME: !!!THIS WON'T WORK!!! needs to be adjusted for stereo, use linear interpolation meanwhile
                xm1 = pSrc[pos_int];
                x0  = pSrc[pos_int+1];
                x1  = pSrc[pos_int+2];
                x2  = pSrc[pos_int+3];
                a   = (3 * (x0-x1) - xm1 + x2) / 2;
                b   = 2 * x1 + xm1 - (5 * x0 + x2) / 2;
                c   = (x1 - xm1) / 2;
               this->pOutput[u] += effective_volume*((((a * pos_fract) + b) * pos_fract + c) * pos_fract + x0);
            #endif

            this->Pos += this->CurrentPitch;
        }
    }
}

void Voice::Kill() {
    if (DiskVoice && DiskStreamRef.State != Stream::state_unused) {
        pDiskThread->OrderDeletionOfStream(&DiskStreamRef);
    }
    Active = false;
}
