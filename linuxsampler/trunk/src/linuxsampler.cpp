/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
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

#include <getopt.h>
#include <signal.h>

#include "Sampler.h"
#include "audiodriver/AudioOutputDeviceFactory.h"
#include "network/lscpserver.h"

#if 0
#define AUDIO_CHANNELS		2     // stereo
#define AUDIO_FRAGMENTS		3     // 3 fragments, if it does not work set it to 2
#define AUDIO_FRAGMENTSIZE	512   // each fragment has 512 frames
#define AUDIO_SAMPLERATE	44100 // Hz
#endif

using namespace LinuxSampler;

/*enum patch_format_t {
    patch_format_unknown,
    patch_format_gig,
    patch_format_dls
} patch_format = patch_format_unknown;*/

Sampler*     pSampler         = NULL;
LSCPServer*  pLSCPServer      = NULL;
pthread_t    signalhandlerthread;
/*AudioThread* pEngine          = NULL;
uint         instrument_index = 0;
double       volume           = 0.25;
int          num_fragments    = AUDIO_FRAGMENTS;
int          fragmentsize     = AUDIO_FRAGMENTSIZE;
uint         samplerate       = AUDIO_SAMPLERATE;
String       input_client;
String       alsaout          = "0,0"; // default card
String       jack_playback[2] = { "", "" };
bool         use_jack         = true;
bool         run_server       = false;*/


void parse_options(int argc, char **argv);
void signal_handler(int signal);

int main(int argc, char **argv) {

    // setting signal handler for catching SIGINT (thus e.g. <CTRL><C>)
    signalhandlerthread = pthread_self();
    signal(SIGINT, signal_handler);

    // parse and assign command line options
    //parse_options(argc, argv);

    /*if (patch_format != patch_format_gig) {
        printf("Sorry only Gigasampler loading migrated in LinuxSampler so far, use --gig to load a .gig file!\n");
        printf("Use 'linuxsampler --help' to see all available options.\n");
        return EXIT_FAILURE;
    }*/


    // create LinuxSampler instance
    dmsg(1,("Creating Sampler..."));
    pSampler = new Sampler;
    dmsg(1,("OK\n"));

    dmsg(1,("Registered audio output drivers: %s\n", AudioOutputDeviceFactory::AvailableDriversAsString().c_str()));

    // create an audio output device
   /* bool no_jack = true;
#if HAVE_JACK
    if (use_jack) {
        dmsg(1,("Creating audio output device (Jack)..."));
        try {
            pSampler->CreateAudioOutputDevice(audio_output_type_jack);
            no_jack = false;
        }
        catch (AudioOutputException aoe) {
            aoe.PrintMessage();
            dmsg(1,("Trying to create Alsa output device instead.\n"));
        }
    }
#endif // HAVE_JACK
    if (no_jack) {
        dmsg(1,("Creating audio output device (Alsa)..."));
        try {
            pSampler->CreateAudioOutputDevice(audio_output_type_alsa);
        }
        catch (AudioOutputException aoe) {
            aoe.PrintMessage();
            dmsg(1,("Trying to create Alsa output device instead.\n"));
            return EXIT_FAILURE;
        }
    }
    dmsg(1,("OK\n"));*/

    // start LSCP network server
    dmsg(1,("Starting network server..."));
    pLSCPServer = new LSCPServer(pSampler);
    pLSCPServer->StartThread();
    dmsg(1,("OK\n"));

    printf("LinuxSampler initialization completed.\n");

    while(true)  {
      /*printf("Voices: %3.3d (Max: %3.3d) Streams: %3.3d (Max: %3.3d, Unused: %3.3d)\r",
            pEngine->ActiveVoiceCount, pEngine->ActiveVoiceCountMax,
            pEngine->pDiskThread->ActiveStreamCount, pEngine->pDiskThread->ActiveStreamCountMax, Stream::GetUnusedStreams());
      fflush(stdout);*/
      usleep(500000);
    }

    return EXIT_SUCCESS;
}

void signal_handler(int signal) {
    if (pthread_equal(pthread_self(), signalhandlerthread) && signal == SIGINT) {
        if (pLSCPServer) {
            pLSCPServer->StopThread();
            delete pLSCPServer;
        }
        if (pSampler) delete pSampler;
        printf("LinuxSampler stopped due to SIGINT\n");
        exit(EXIT_SUCCESS);
    }
}

/*void parse_options(int argc, char **argv) {
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
            {"alsaout",1,0,0},
            {"jackout",1,0,0},
            {"samplerate",1,0,0},
            {"server",0,0,0},
            {"help",0,0,0},
            {0,0,0,0}
        };

    while (true) {
        res = getopt_long_only(argc, argv, "", long_options, &option_index);
        if(res == -1) break;
        if (res == 0) {
            switch(option_index) {
                case 0: // --numfragments
                    num_fragments = atoi(optarg);
                    break;
                case 1: // --fragmentsize
                    fragmentsize = atoi(optarg);
                    break;
                case 2: // --volume
                    volume = atof(optarg);
                    break;
                case 3: // --dls
                    patch_format = patch_format_dls;
                    break;
                case 4: // --gig
                    patch_format = patch_format_gig;
                    break;
                case 5: // --instrument
                    instrument_index = atoi(optarg);
                    break;
                case 6: // --inputclient
                    input_client = optarg;
                    break;
                case 7: // --alsaout
                    alsaout = optarg;
                    use_jack = false; // If this option is specified do not connect to jack
                    break;
                case 8: { // --jackout
                    try {
                        String arg(optarg);
                        // remove outer apostrophes
                        arg = arg.substr(arg.find('\'') + 1, arg.rfind('\'') - (arg.find('\'') + 1));
                        // split in two arguments
                        jack_playback[0] = arg.substr(0, arg.find("\' "));
                        jack_playback[1] = arg.substr(arg.find("\' ") + 2, arg.size() - (arg.find("\' ") + 2));
                        // remove inner apostrophes
                        jack_playback[0] = jack_playback[0].substr(0, jack_playback[0].find('\''));
                        jack_playback[1] = jack_playback[1].substr(jack_playback[1].find('\'') + 1, jack_playback[1].size() - jack_playback[1].find('\''));
                        // this is the default but set it up anyway in case alsa_card was also used.
                        use_jack = true;
                    }
                    catch (...) {
                        fprintf(stderr, "Invalid argument '%s' for parameter --jackout\n", optarg);
                        exit(EXIT_FAILURE);
                    }
                    break;
                }
                case 9: // --samplerate
                    samplerate = atoi(optarg);
                    break;
                case 10: // --server
                    run_server = true;
                    break;
                case 11: // --help
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
                    printf("--alsaout          connects to the given Alsa sound device on startup\n");
                    printf("                   (e.g. 0,0 to connect to hw:0,0 or plughw:0,0)\n");
                    printf("--jackout          connects to the given Jack playback ports on startup\n");
                    printf("                   (e.g. \"\'alsa_pcm:playback_1\' \'alsa_pcm:playback_2\'\"\n");
                    printf("                   in case of stereo output)\n");
                    printf("--samplerate       sets sample rate if supported by audio output system\n");
                    printf("                   (e.g. 44100)\n");
                    printf("--server           launch network server for remote control\n");
                    exit(EXIT_SUCCESS);
                    break;
            }
        }
    }
}*/
