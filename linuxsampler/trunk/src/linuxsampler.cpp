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
#include <pthread.h>

#include <string>

#include "global.h"
#include "diskthread.h"
#include "audiothread.h"
#include "alsaio.h"
#include "jackio.h"
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
uint             instrument_index;
double           volume;
int              num_fragments;
int              fragmentsize;
std::string      input_client;
pthread_t        signalhandlerthread;

void parse_options(int argc, char **argv);
void signal_handler(int signal);

int main(int argc, char **argv) {
    pAudioIO = NULL;
    pRIFF    = NULL;
    pGig     = NULL;

    // setting signal handler for catching SIGINT (thus e.g. <CTRL><C>)
    signalhandlerthread = pthread_self();
    signal(SIGINT, signal_handler);

    patch_format      = patch_format_unknown;
    instrument_index  = 0;
    num_fragments     = AUDIO_FRAGMENTS;
    fragmentsize      = AUDIO_FRAGMENTSIZE;
    volume            = 0.25; // default volume

    // parse and assign command line options
    parse_options(argc, argv);

    if (patch_format != patch_format_gig) {
        printf("Sorry only Gigasampler loading migrated in LinuxSampler so far, use --gig to load a .gig file!\n");
        printf("Use 'linuxsampler --help' to see all available options.\n");
        return EXIT_FAILURE;
    }

#if HAVE_JACK
    dmsg(1,("Initializing audio output (Jack)..."));
    pAudioIO = new JackIO();
    int error = ((JackIO*)pAudioIO)->Initialize(AUDIO_CHANNELS);
    if (error) {
        dmsg(1,("Trying Alsa output instead.\n"));
        dmsg(1,("Initializing audio output (Alsa)..."));
        pAudioIO = new AlsaIO();
        int error = ((AlsaIO*)pAudioIO)->Initialize(AUDIO_CHANNELS, AUDIO_SAMPLERATE, num_fragments, fragmentsize);
        if (error) return EXIT_FAILURE;
    }
    dmsg(1,("OK\n"));
#else // Alsa only
    dmsg(1,("Initializing audio output (Alsa)..."));
    pAudioIO = new AlsaIO();
    int error = ((AlsaIO*)pAudioIO)->Initialize(AUDIO_CHANNELS, AUDIO_SAMPLERATE, num_fragments, fragmentsize);
    if (error) return EXIT_FAILURE;
    dmsg(1,("OK\n"));
#endif // HAVE_JACK

    // Loading gig file
    try {
        printf("Loading gig file...");
        fflush(stdout);
        pRIFF       = new RIFF::File(argv[argc - 1]);
        pGig        = new gig::File(pRIFF);
        pInstrument = pGig->GetInstrument(instrument_index);
        if (!pInstrument) {
            printf("there's no instrument with index %d.\n", instrument_index);
            exit(EXIT_FAILURE);
        }
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

    DiskThread*  pDiskThread   = new DiskThread(((pAudioIO->MaxSamplesPerCycle() << MAX_PITCH) << 1) + 6); //FIXME: assuming stereo
    AudioThread* pAudioThread  = new AudioThread(pAudioIO, pDiskThread, pInstrument);
    MidiIn*      pMidiInThread = new MidiIn(pAudioThread);

    dmsg(1,("Starting disk thread..."));
    pDiskThread->StartThread();
    dmsg(1,("OK\n"));
    dmsg(1,("Starting MIDI in thread..."));
    if (input_client.size() > 0) pMidiInThread->SubscribeToClient(input_client.c_str());
    pMidiInThread->StartThread();
    dmsg(1,("OK\n"));

    sleep(1);
    dmsg(1,("Starting audio thread..."));
    pAudioThread->Volume = volume;
    pAudioIO->AssignEngine(pAudioThread);
    pAudioIO->Activate();
    dmsg(1,("OK\n"));

    printf("LinuxSampler initialization completed.\n");

    while(true)  {
      printf("Voices: %3.3d (Max: %3.3d) Streams: %3.3d (Max: %3.3d, Unused: %3.3d)\r",
            pAudioThread->ActiveVoiceCount, pAudioThread->ActiveVoiceCountMax,
            pDiskThread->ActiveStreamCount, pDiskThread->ActiveStreamCountMax, Stream::GetUnusedStreams());
      fflush(stdout);
      usleep(500000);
    }

    return EXIT_SUCCESS;
}

void signal_handler(int signal) {
    if (pthread_equal(pthread_self(), signalhandlerthread) && signal == SIGINT) {
        // stop all threads
        if (pAudioIO)      pAudioIO->Close();
        if (pMidiInThread) pMidiInThread->StopThread();
        if (pDiskThread)   pDiskThread->StopThread();

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
            {"volume",1,0,0},
            {"dls",0,0,0},
            {"gig",0,0,0},
            {"instrument",1,0,0},
            {"inputclient",1,0,0},
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
                    volume = atof(optarg);
                    break;
                case 3:
                    patch_format = patch_format_dls;
                    break;
                case 4:
                    patch_format = patch_format_gig;
                    break;
                case 5:
                    instrument_index = atoi(optarg);
                    break;
                case 6:
                    input_client = optarg;
                    break;
                case 7:
                    printf("usage: linuxsampler [OPTIONS] <INSTRUMENTFILE>\n\n");
                    printf("--gig              loads a Gigasampler instrument\n");
                    printf("--dls              loads a DLS instrument\n");
                    printf("--instrument       index of the instrument in the instrument file if it\n");
                    printf("                   contains more than one (default: 0)\n");
                    printf("--numfragments     sets the number of audio fragments\n");
                    printf("--fragmentsize     sets the fragment size\n");
                    printf("--volume           sets global volume gain factor (a value > 1.0 means\n");
                    printf("                   amplification, a value < 1.0 means attenuation,\n");
                    printf("                   default: 0.25)\n");
                    printf("--inputclient      connects to an Alsa sequencer input client on startup\n");
                    printf("                   (e.g. 64:0 to connect to a client with ID 64 and port 0)\n");
                    exit(0);
                    break;
            }
        }
    }
}
