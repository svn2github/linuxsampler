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

#include "audiothread.h"

AudioThread::AudioThread(AudioIO* pAudioIO, DiskThread* pDiskThread, gig::Instrument* pInstrument) : Thread(true, 1, 0) {
    this->pAudioIO    = pAudioIO;
    this->pDiskThread = pDiskThread;
    this->pInstrument = pInstrument;
    pCommandQueue     = new RingBuffer<command_t>(1024);
    pVoices           = new Voice*[MAX_AUDIO_VOICES];
    for (uint i = 0; i < MAX_AUDIO_VOICES; i++) {
        pVoices[i] = new Voice(pDiskThread);
    }
    for (uint i = 0; i < 128; i++) {
        ActiveVoices[i] = NULL;
    }

    pAudioSumBuffer = new float[pAudioIO->FragmentSize * pAudioIO->Channels];

    // set all voice outputs to the AudioSumBuffer
    for (int i = 0; i < MAX_AUDIO_VOICES; i++) {
        pVoices[i]->SetOutput(pAudioSumBuffer, pAudioIO->FragmentSize * 2);  //FIXME: assuming stereo
    }

    // cache initial samples points (for actually needed samples)
    dmsg(("Caching initial samples..."));
    gig::Region* pRgn = this->pInstrument->GetFirstRegion();
    while (pRgn) {
        if (!pRgn->GetSample()->GetCache().Size) {
            CacheInitialSamples(pRgn->GetSample());
        }
        for (uint i = 0; i < pRgn->DimensionRegions; i++) {
            CacheInitialSamples(pRgn->pDimensionRegions[i]->pSample);
        }

        pRgn = this->pInstrument->GetNextRegion();
    }
    dmsg(("OK\n"));
}

AudioThread::~AudioThread() {
    if (pCommandQueue) delete pCommandQueue;
    if (pVoices) {
        for (uint i = 0; i < MAX_AUDIO_VOICES; i++) {
            if (pVoices[i]) delete pVoices[i];
        }
    }
    delete[] pVoices;
}

int AudioThread::Main() {
    dmsg(("Audio thread running\n"));

    while (true) {

        // read and process commands from the queue
        while (true) {
            command_t command;
            if (pCommandQueue->read(&command, 1) == 0) break;

            switch (command.type) {
                case command_type_note_on:
                    dmsg(("Audio Thread: Note on received\n"));
                    ActivateVoice(command.pitch, command.velocity);
                    break;
                case command_type_note_off:
                    dmsg(("Audio Thread: Note off received\n"));
                    ReleaseVoice(command.pitch, command.velocity);
                    break;
            }
        }


        // zero out the sum buffer
        for (uint u = 0; u < pAudioIO->FragmentSize * pAudioIO->Channels; u++) {
            pAudioSumBuffer[u] = 0.0;
        }


        // render audio from all active voices
        for (uint i = 0; i < MAX_AUDIO_VOICES; i++) {
            if (pVoices[i]->IsActive()) {
                pVoices[i]->RenderAudio();
            }
        }


        // check clipping in the audio sum, convert to sample_type
        // (from 32bit to 16bit sample) and copy to output buffer
        float sample_point;
        for (uint u = 0; u < pAudioIO->FragmentSize * pAudioIO->Channels; u++) {
            sample_point = this->pAudioSumBuffer[u] / 4; // FIXME division by 4 just for testing purposes (to give a bit of head room when mixing multiple voices together)
            if (sample_point < -32768.0) sample_point = -32768.0;
            if (sample_point > 32767.0)  sample_point = 32767.0;
            this->pAudioIO->pOutputBuffer[u] = (sample_t) sample_point;
        }


        // call audio driver to output sound
        int res = this->pAudioIO->Output();
        if (res < 0) exit(EXIT_FAILURE);
    }
}

/// Will be called by the MIDIIn Thread to let the audio thread trigger a new voice.
void AudioThread::ProcessNoteOn(uint8_t Pitch, uint8_t Velocity) {
    command_t cmd;
    cmd.type     = command_type_note_on;
    cmd.pitch    = Pitch;
    cmd.velocity = Velocity;
    this->pCommandQueue->write(&cmd, 1);
}

/// Will be called by the MIDIIn Thread to signal the audio thread to release a voice.
void AudioThread::ProcessNoteOff(uint8_t Pitch, uint8_t Velocity) {
    command_t cmd;
    cmd.type     = command_type_note_off;
    cmd.pitch    = Pitch;
    cmd.velocity = Velocity;
    this->pCommandQueue->write(&cmd, 1);
}

void AudioThread::ActivateVoice(uint8_t MIDIKey, uint8_t Velocity) {
    for (int i = 0; i < MAX_AUDIO_VOICES; i++) {
        if (pVoices[i]->IsActive()) continue;
        pVoices[i]->Trigger(MIDIKey, Velocity, this->pInstrument);
        ActiveVoices[MIDIKey] = pVoices[i];
        return;
    }
    std::cerr << "No free voice!" << std::endl << std::flush;
}

void AudioThread::ReleaseVoice(uint8_t MIDIKey, uint8_t Velocity) {
    Voice* pVoice = ActiveVoices[MIDIKey];
    if (pVoice) {
        pVoice->Kill(); //TODO: for now we're rude and just kill the poor, poor voice immediately :), later we add a Release() method to the Voice class and call it here to let the voice go through it's release phase
        ActiveVoices[MIDIKey] = NULL;
    }
    else std::cerr << "Couldn't find active voice for note off command!" << std::endl << std::flush;
}

void AudioThread::CacheInitialSamples(gig::Sample* pSample) {
    if (!pSample || pSample->GetCache().Size) return;
    if (pSample->SamplesTotal <= NUM_RAM_PRELOAD_SAMPLES) {
        // Sample is too short for disk streaming, so we load the whole
        // sample into RAM and place 'pAudioIO->FragmentSize << MAX_PITCH'
        // number of '0' samples (silence samples) behind the official buffer
        // border, to allow the interpolator do it's work even at the end of
        // the sample.
        gig::buffer_t buf = pSample->LoadSampleDataWithNullSamplesExtension(pAudioIO->FragmentSize << MAX_PITCH);
        dmsg(("Cached %d Bytes, %d silence bytes.\n", buf.Size, buf.NullExtensionSize));
    }
    else { // we only cache NUM_RAM_PRELOAD_SAMPLES and stream the other sample points from disk
        pSample->LoadSampleData(NUM_RAM_PRELOAD_SAMPLES);
    }

    if (!pSample->GetCache().Size) std::cerr << "Unable to cache sample - maybe memory full!" << std::endl << std::flush;
}
