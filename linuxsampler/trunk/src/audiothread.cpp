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
    // allocate the ActiveVoicePool (for each midi key there is a variable size linked list
    // of pointers to Voice objects)
    ActiveVoicePool = new RTELMemoryPool<Voice*>(MAX_AUDIO_VOICES);
    for (uint i = 0; i < MAX_AUDIO_VOICES; i++) {
        pVoices[i] = new Voice(pDiskThread);
    }
    for (uint i = 0; i < 128; i++) {
        pMIDIKeyInfo[i].pActiveVoices = new RTEList<Voice*>;
        pMIDIKeyInfo[i].hSustainPtr   = NULL;
        pMIDIKeyInfo[i].Sustained     = false;
    }
    SustainedKeyPool = new RTELMemoryPool<uint>(128);

    pAudioSumBuffer = new float[pAudioIO->FragmentSize * pAudioIO->Channels];

    // set all voice outputs to the AudioSumBuffer
    for (int i = 0; i < MAX_AUDIO_VOICES; i++) {
        pVoices[i]->SetOutput(pAudioSumBuffer, pAudioIO->FragmentSize * 2);  //FIXME: assuming stereo
    }

    // cache initial samples points (for actually needed samples)
    dmsg(1,("Caching initial samples..."));
    gig::Region* pRgn = this->pInstrument->GetFirstRegion();
    while (pRgn) {
        if (!pRgn->GetSample()->GetCache().Size) {
            dmsg(2,("C"));
            CacheInitialSamples(pRgn->GetSample());
        }
        for (uint i = 0; i < pRgn->DimensionRegions; i++) {
            CacheInitialSamples(pRgn->pDimensionRegions[i]->pSample);
        }

        pRgn = this->pInstrument->GetNextRegion();
    }

    // sustain pedal value
    PrevHoldCCValue = 0;
    SustainPedal    = 0;

    dmsg(1,("OK\n"));
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
    dmsg(2,("Audio thread running\n"));

    while (true) {

        // read and process commands from the queue
        while (true) {
            command_t command;
            if (pCommandQueue->read(&command, 1) == 0) break;

            switch (command.type) {
                case command_type_note_on:
                    dmsg(5,("Audio Thread: Note on received\n"));
                    ActivateVoice(command.pitch, command.velocity);
                    break;
                case command_type_note_off:
                    dmsg(5,("Audio Thread: Note off received\n"));
                    ReleaseVoice(command.pitch, command.velocity);
                    break;
                case command_type_continuous_controller:
                    dmsg(5,("Audio Thread: MIDI CC received\n"));
                    ContinuousController(command.channel, command.number, command.value);
                    break;
            }
        }


        // zero out the sum buffer
        for (uint u = 0; u < pAudioIO->FragmentSize * pAudioIO->Channels; u++) {
            pAudioSumBuffer[u] = 0.0;
        }


        // render audio from all active voices
        int active_voices = 0;
        for (uint i = 0; i < MAX_AUDIO_VOICES; i++) {
            if (pVoices[i]->IsActive()) {
                pVoices[i]->RenderAudio();
                if (pVoices[i]->IsActive()) active_voices++; // still active
                else { // voice reached end, is now inactive
                    ReleaseVoice(pVoices[i]); // remove voice from the list of active voices
                }
            }
        }
        // write that to the disk thread class so that it can print it
        // on the console for debugging purposes
        ActiveVoiceCount = active_voices;
        if (ActiveVoiceCount > ActiveVoiceCountMax) ActiveVoiceCountMax = ActiveVoiceCount;


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

// Will be called by the MIDIIn Thead to send MIDI continuos controller events
void AudioThread::ProcessContinuousController(uint8_t Channel, uint8_t Number, uint8_t Value) {
    command_t cmd;
    cmd.type     = command_type_continuous_controller;
    cmd.channel  = Channel;
    cmd.number   = Number;
    cmd.value    = Value;
    this->pCommandQueue->write(&cmd, 1);
}

void AudioThread::ActivateVoice(uint8_t MIDIKey, uint8_t Velocity) {
    for (int i = 0; i < MAX_AUDIO_VOICES; i++) {
        if (pVoices[i]->IsActive()) continue;

        // add (append) a new voice to the corresponding MIDIKey active voices list
        Voice** new_voice_ptr = ActiveVoicePool->alloc_append(pMIDIKeyInfo[MIDIKey].pActiveVoices);
        *new_voice_ptr = pVoices[i];
        pVoices[i]->pSelfPtr = new_voice_ptr; // FIXME: hack to allow fast deallocation
        pVoices[i]->Trigger(MIDIKey, Velocity, this->pInstrument);

        if (!pMIDIKeyInfo[MIDIKey].hSustainPtr) {
            dmsg(4,("ActivateVoice(uint,uint): hSustainPtr == null, setting release pointer to the last voice on the key...\n"));
            pMIDIKeyInfo[MIDIKey].pActiveVoices->last();
            pMIDIKeyInfo[MIDIKey].hSustainPtr = pMIDIKeyInfo[MIDIKey].pActiveVoices->current();
        }
        return;
    }
    std::cerr << "No free voice!" << std::endl << std::flush;
}

/**
 *  Releases the voices on the given key if sustain pedal is not pressed.
 *  If sustain is pressed, the release of the note will be postponed until
 *  sustain pedal will be released or voice turned inactive by itself (e.g.
 *  due to completion of sample playback).
 */
void AudioThread::ReleaseVoice(uint8_t MIDIKey, uint8_t Velocity) {
    midi_key_info_t* pmidikey = &pMIDIKeyInfo[MIDIKey];
    if (SustainPedal) { // if sustain pedal is pressed postpone the Note-Off
        if (pmidikey->hSustainPtr) {
            // stick the note-off information to the respective voice
            Voice** pVoiceToRelease = pmidikey->pActiveVoices->set_current(pmidikey->hSustainPtr);
            if (pVoiceToRelease) {
                (*pVoiceToRelease)->ReleaseVelocity = Velocity;
                // now increment the sustain pointer
                pmidikey->pActiveVoices->next();
                pmidikey->hSustainPtr = pmidikey->pActiveVoices->current();
                // if the key was not sustained yet, add it's MIDI key number to the sustained key pool
                if (!pmidikey->Sustained) {
                    uint* sustainedmidikey = SustainedKeyPool->alloc();
                    *sustainedmidikey      = MIDIKey;
                    pmidikey->Sustained    = true;
                }
            }
            else dmsg(3,("Ignoring NOTE OFF --> pVoiceToRelease == null!\n"));
        }
        else dmsg(3,("Ignoring NOTE OFF, seems like more Note-Offs than Note-Ons or no free voices available?\n"));
    }
    else {
        // get the first voice in the list of active voices on the MIDI Key
        Voice** pVoicePtr = pmidikey->pActiveVoices->first();
        if (pVoicePtr) ReleaseVoice(*pVoicePtr);
        else dmsg(2,("Couldn't find active voice for note off command, maybe already released.\n"));
    }
}

/**
 *  Releases the voice given with pVoice (no matter if sustain is pressed or
 *  not). This method will e.g. be directly called if a voice went inactive
 *  by itself. If susatain pedal is pressed the method takes care to free
 *  those sustain informations of the voice.
 */
void AudioThread::ReleaseVoice(Voice* pVoice) {
    if (pVoice) {
        if (pVoice->IsActive()) pVoice->Kill(); //TODO: for now we're rude and just kill the poor, poor voice immediately :), later we add a Release() method to the Voice class and call it here to let the voice go through it's release phase

        if (pMIDIKeyInfo[pVoice->MIDIKey].Sustained) {

            // check if the sustain pointer has to be moved, now that we release the voice
            RTEList<Voice*>::NodeHandle hSustainPtr = pMIDIKeyInfo[pVoice->MIDIKey].hSustainPtr;
            if (hSustainPtr) {
                Voice** pVoicePtr = pMIDIKeyInfo[pVoice->MIDIKey].pActiveVoices->set_current(hSustainPtr);
                if (pVoicePtr) {
                    if (*pVoicePtr == pVoice) { // move sustain pointer to the next sustained voice
                        dmsg(3,("Correcting sustain pointer\n"));
                        pMIDIKeyInfo[pVoice->MIDIKey].pActiveVoices->next();
                        pMIDIKeyInfo[pVoice->MIDIKey].hSustainPtr = pMIDIKeyInfo[pVoice->MIDIKey].pActiveVoices->current();
                    }
                    else dmsg(4,("ReleaseVoice(Voice*): *hSustain != pVoice\n"));
                }
                else dmsg(3,("ReleaseVoice(Voice*): pVoicePtr == null\n"));
            }
            else dmsg(3,("ReleaseVoice(Voice*): hSustainPtr == null\n"));

            // remove the voice from the list associated with this MIDI key
            ActiveVoicePool->free(pVoice->pSelfPtr);

            // check if there are no sustained voices left on the MIDI key and update the key info if so
            if (pMIDIKeyInfo[pVoice->MIDIKey].pActiveVoices->is_empty()) {
                pMIDIKeyInfo[pVoice->MIDIKey].hSustainPtr = NULL;
                pMIDIKeyInfo[pVoice->MIDIKey].Sustained   = false;
                dmsg(3,("Key now not sustained\n"));
            }
        }
        else {
            // remove the voice from the list associated with this MIDI key
            ActiveVoicePool->free(pVoice->pSelfPtr);
            dmsg(4,("Key was not sustained\n"));
        }
    }
    else std::cerr << "Couldn't release voice! (pVoice == NULL)\n" << std::flush;
}

void AudioThread::ContinuousController(uint8_t Channel, uint8_t Number, uint8_t Value) {
    dmsg(4,("AudioThread::ContinuousController c=%d n=%d v=%d\n", Channel, Number, Value));
    if (Number == 64) {
        if (Value >= 64 && PrevHoldCCValue < 64) {
            dmsg(4,("PEDAL DOWN\n"));
            SustainPedal = true;
        }
        if (Value < 64 && PrevHoldCCValue >= 64) {
            dmsg(4,("PEDAL UP\n"));
            SustainPedal = false;
            // iterate through all keys that are currently sustained
            for (uint* key = SustainedKeyPool->first(); key; key = SustainedKeyPool->next()) {
                // release all active voices on the midi key
                Voice** pVoicePtr = pMIDIKeyInfo[*key].pActiveVoices->first();
                while (pVoicePtr) {
                    Voice** pVoicePtrNext = pMIDIKeyInfo[*key].pActiveVoices->next();
                    dmsg(3,("Sustain CC: releasing voice on midi key %d\n", *key));
                    ReleaseVoice(*pVoicePtr);
                    pVoicePtr = pVoicePtrNext;
                }
            }
            // empty the SustainedKeyPool (free all the elements)
            SustainedKeyPool->empty();
        }
        PrevHoldCCValue = Value;
    }
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
        dmsg(4,("Cached %d Bytes, %d silence bytes.\n", buf.Size, buf.NullExtensionSize));
    }
    else { // we only cache NUM_RAM_PRELOAD_SAMPLES and stream the other sample points from disk
        pSample->LoadSampleData(NUM_RAM_PRELOAD_SAMPLES);
    }

    if (!pSample->GetCache().Size) std::cerr << "Unable to cache sample - maybe memory full!" << std::endl << std::flush;
}
