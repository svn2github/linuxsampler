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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <signal.h>

#include "global.h"
#include "audioio.h"
#include "diskthread.h"
#include "audiothread.h"
#include "midiin.h"
#include "stream.h"
#include "RIFF.h"
#include "gig.h"

#define AUDIO_CHANNELS		2     // stereo
#define AUDIO_FRAGMENTS		3     // 3 fragments, if it does not work set it to 2
#define AUDIO_FRAGMENTSIZE	512   // each fragment has 512 frames
#define AUDIO_SAMPLERATE	44100 // Hz

enum patch_format_t {
    patch_format_unknown,
    patch_format_gig,
    patch_format_dls
} patch_format;

AudioIO*         pAudioIO;
DiskThread*      pDiskThread;
AudioThread*     pAudioThread;
MidiIn*          pMidiInThread;

RIFF::File*      pRIFF;
gig::File*       pGig;
gig::Instrument* pInstrument;

void parse_options(int argc, char **argv);
void signal_handler(int signal);

int midi_non_blocking;
int num_fragments;
int fragmentsize;
bool instrument_is_DLS;
bool instruemtn_is_gig;
char midi_device[40];

int main(int argc, char **argv) {
    pAudioIO = NULL;
    pRIFF    = NULL;
    pGig     = NULL;

    // setting signal handler for catching SIGINT (thus e.g. <CTRL><C>)
    signal(SIGINT, signal_handler);

    patch_format      = patch_format_unknown;
    midi_non_blocking = 1;
    num_fragments     = AUDIO_FRAGMENTS;
    fragmentsize      = AUDIO_FRAGMENTSIZE;
    strcpy(midi_device, "/dev/midi00");

    // parse and assign command line options
    parse_options(argc, argv);

    if (patch_format != patch_format_gig) {
        printf("Sorry only Gigasampler loading migrated in LinuxSampler so far, use --gig\n");
        printf("to load a .gig file!\n");
        return EXIT_FAILURE;
    }

    dmsg(("Initializing audio output..."));
    pAudioIO = new AudioIO();
    int error = pAudioIO->Initialize(AUDIO_CHANNELS, AUDIO_SAMPLERATE, num_fragments, fragmentsize);
    if (error) return EXIT_FAILURE;
    dmsg(("OK\n"));

    // Loading gig file
    try {
        printf("Loading gig file...");
        fflush(stdout);
        pRIFF       = new RIFF::File(argv[argc - 1]);
        pGig        = new gig::File(pRIFF);
        pInstrument = pGig->GetFirstInstrument();
        pGig->GetFirstSample(); // just to complete instrument loading before we enter the realtime part
        printf("OK\n");
        fflush(stdout);
    }
    catch (RIFF::Exception e) {
        e.PrintMessage();
        return EXIT_FAILURE;
    }
    catch (...) {
        printf("Unknown exception while trying to parse gig file.\n");
        return EXIT_FAILURE;
    }

    DiskThread*  pDiskThread   = new DiskThread(((pAudioIO->FragmentSize << MAX_PITCH) << 1) + 3); //FIXME: assuming stereo
    AudioThread* pAudioThread  = new AudioThread(pAudioIO, pDiskThread, pInstrument);
    MidiIn*      pMidiInThread = new MidiIn(pAudioThread);

    dmsg(("Starting disk thread..."));
    pDiskThread->StartThread();
    dmsg(("OK\n"));
    dmsg(("Starting MIDI in thread..."));
    pMidiInThread->StartThread();
    dmsg(("OK\n"));

    sleep(1);
    dmsg(("Starting audio thread..."));
    pAudioThread->StartThread();
    dmsg(("OK\n"));

    printf("LinuxSampler initialization completed.\n");

    while(true)  {
      printf("Voices: %3.3d  Streams: %3.3d  \r",pAudioThread->ActiveVoiceCount, pDiskThread->ActiveStreamCount); fflush(stdout);
      usleep(500000);
    }

    return EXIT_SUCCESS;
}

void signal_handler(int signal) {
    if (signal == SIGINT) {
        // stop all threads
        if (pMidiInThread) pMidiInThread->StopThread();
        if (pAudioThread)  pAudioThread->StopThread();
        if (pDiskThread)   pDiskThread->StopThread();

        sleep(1);

        // free all resources
        if (pMidiInThread) delete pMidiInThread;
        if (pAudioThread)  delete pAudioThread;
        if (pDiskThread)   delete pDiskThread;
        if (pGig)          delete pGig;
        if (pRIFF)         delete pRIFF;
        if (pAudioIO)      delete pAudioIO;

        printf("LinuxSampler stopped due to SIGINT\n");
        exit(EXIT_SUCCESS);
    }
}

void parse_options(int argc, char **argv) {
    int res;
    int option_index = 0;
    static struct option long_options[] =
        {
            {"numfragments",1,0,0},
            {"fragmentsize",1,0,0},
            {"dls",0,0,0},
            {"gig",0,0,0},
            {"help",0,0,0},
            {0,0,0,0}
        };

    while (true) {
        res = getopt_long_only(argc, argv, "", long_options, &option_index);
        if(res == -1) break;
        if (res == 0) {
            switch(option_index) {
                case 0:
                    num_fragments = atoi(optarg);
                    break;
                case 1:
                    fragmentsize = atoi(optarg);
                    break;
                case 2:
                    patch_format = patch_format_dls;
                    break;
                case 3:
                    patch_format = patch_format_gig;
                    break;
                case 4:
                    printf("usage: linuxsampler [OPTIONS] <INSTRUMENTFILE>\n\n");
                    printf("--numfragments     sets the number of audio fragments\n");
                    printf("--fragmentsize     sets the fragment size\n");
                    printf("--dls              loads a DLS instrument\n");
                    printf("--gig              loads a Gigasampler instrument\n");
                    exit(0);
                    break;
            }
        }
    }
}
