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
#include "drivers/midi/MidiInputDeviceFactory.h"
#include "drivers/audio/AudioOutputDeviceFactory.h"
#include "engines/gig/Profiler.h"
#include "network/lscpserver.h"
#include "common/stacktrace.h"
#include "common/Features.h"

using namespace LinuxSampler;

Sampler*    pSampler    = NULL;
LSCPServer* pLSCPServer = NULL;
pthread_t   main_thread;
bool profile = false;
bool tune = true;

void parse_options(int argc, char **argv);
void signal_handler(int signal);
void kill_app();

int main(int argc, char **argv) {

    // initialize the stack trace mechanism with our binary file
    StackTraceInit(argv[0], -1);

    main_thread = pthread_self();

    // setting signal handler for catching SIGINT (thus e.g. <CTRL><C>)
    signal(SIGINT, signal_handler);

    // register signal handler for all unusual signals
    // (we will print the stack trace and exit)
    struct sigaction sact;
    sigemptyset(&sact.sa_mask);
    sact.sa_flags   = 0;
    sact.sa_handler = signal_handler;
    sigaction(SIGSEGV, &sact, NULL);
    sigaction(SIGBUS,  &sact, NULL);
    sigaction(SIGILL,  &sact, NULL);
    sigaction(SIGFPE,  &sact, NULL);
    sigaction(SIGUSR1, &sact, NULL);
    sigaction(SIGUSR2, &sact, NULL);

    // parse and assign command line options
    parse_options(argc, argv);

    dmsg(1,("LinuxSampler %s\n", VERSION));
    dmsg(1,("Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck\n"));

    if (tune)
    {
	    // detect and print system / CPU specific features
	    String sFeatures;
	    Features::detect();
#if ARCH_X86
	    if (Features::supportsMMX()) sFeatures += " MMX";
	    if (Features::supportsSSE()) sFeatures += " SSE";
#endif // ARCH_X86
	    if (!sFeatures.size()) sFeatures = " None";
	    dmsg(1,("Detected features:%s\n",sFeatures.c_str()));
    }

    // create LinuxSampler instance
    dmsg(1,("Creating Sampler..."));
    pSampler = new Sampler;
    dmsg(1,("OK\n"));

    dmsg(1,("Registered MIDI input drivers: %s\n", MidiInputDeviceFactory::AvailableDriversAsString().c_str()));
    dmsg(1,("Registered audio output drivers: %s\n", AudioOutputDeviceFactory::AvailableDriversAsString().c_str()));

    // start LSCP network server
    dmsg(1,("Starting LSCP network server (on TCP port %d)...", LSCP_PORT));
    pLSCPServer = new LSCPServer(pSampler);
    pLSCPServer->StartThread();
    pLSCPServer->WaitUntilInitialized();
    dmsg(1,("OK\n"));

    if (profile)
    {
	    dmsg(1,("Calibrating profiler..."));
	    gig::Profiler::Calibrate();
	    gig::Profiler::Reset();
	    dmsg(1,("OK\n"));
    }

    printf("LinuxSampler initialization completed.\n");

    std::list<LSCPEvent::event_t> rtEvents;
    rtEvents.push_back(LSCPEvent::event_voice_count);
    rtEvents.push_back(LSCPEvent::event_stream_count);
    rtEvents.push_back(LSCPEvent::event_buffer_fill);

    while(true)
    {
      /*printf("Voices: %3.3d (Max: %3.3d) Streams: %3.3d (Max: %3.3d, Unused: %3.3d)\r",
            pEngine->ActiveVoiceCount, pEngine->ActiveVoiceCountMax,
            pEngine->pDiskThread->ActiveStreamCount, pEngine->pDiskThread->ActiveStreamCountMax, Stream::GetUnusedStreams());
      fflush(stdout);*/
      sleep(1);
      if (profile)
      {
	      unsigned int samplingFreq = 48000; //FIXME: hardcoded for now
	      unsigned int bv = gig::Profiler::GetBogoVoices(samplingFreq);
	      if (bv != 0)
	      {
		      printf("       BogoVoices: %i         \r", bv);
		      fflush(stdout);
	      }
      }
      
      if (LSCPServer::EventSubscribers(rtEvents))
      {
	      LSCPServer::LockRTNotify();
	      std::map<uint,SamplerChannel*> channels = pSampler->GetSamplerChannels();
	      std::map<uint,SamplerChannel*>::iterator iter = channels.begin();
	      for (; iter != channels.end(); iter++) {
		      SamplerChannel* pSamplerChannel = iter->second;
		      Engine* pEngine = pSamplerChannel->GetEngine();
		      if (!pEngine) continue;
		      LSCPServer::SendLSCPNotify(LSCPEvent(LSCPEvent::event_voice_count, iter->first, pEngine->VoiceCount()));
		      LSCPServer::SendLSCPNotify(LSCPEvent(LSCPEvent::event_stream_count, iter->first, pEngine->DiskStreamCount()));
		      LSCPServer::SendLSCPNotify(LSCPEvent(LSCPEvent::event_buffer_fill, iter->first, pEngine->DiskStreamBufferFillPercentage()));
	      }
	      LSCPServer::UnlockRTNotify();
      }

    }

    return EXIT_SUCCESS;
}

void signal_handler(int iSignal) {
    switch (iSignal) {
        case SIGINT: {
            if (pthread_equal(pthread_self(), main_thread)) {
                if (pLSCPServer) {
                    pLSCPServer->StopThread();
                    delete pLSCPServer;
                }
                if (pSampler) delete pSampler;
                printf("LinuxSampler stopped due to SIGINT.\n");
                exit(EXIT_SUCCESS);
            }
            return;
        }
        case SIGSEGV:
            std::cerr << ">>> FATAL ERROR: Segmentation fault (SIGSEGV) occured! <<<\n" << std::flush;
            break;
        case SIGBUS:
            std::cerr << ">>> FATAL ERROR: Access to undefined portion of a memory object (SIGBUS) occured! <<<\n" << std::flush;
            break;
        case SIGILL:
            std::cerr << ">>> FATAL ERROR: Illegal instruction (SIGILL) occured! <<<\n" << std::flush;
            break;
        case SIGFPE:
            std::cerr << ">>> FATAL ERROR: Erroneous arithmetic operation (SIGFPE) occured! <<<\n" << std::flush;
            break;
        case SIGUSR1:
            std::cerr << ">>> User defined signal 1 (SIGUSR1) received <<<\n" << std::flush;
            break;
        case SIGUSR2:
            std::cerr << ">>> User defined signal 2 (SIGUSR2) received <<<\n" << std::flush;
            break;
        default: { // this should never happen, as we register for the signals we want
            std::cerr << ">>> FATAL ERROR: Unknown signal received! <<<\n" << std::flush;
            break;
        }
    }
    signal(iSignal, SIG_DFL); // Reinstall default handler to prevent race conditions
    std::cerr << "Showing stack trace...\n" << std::flush;
    StackTrace();
    sleep(2);
    std::cerr << "Killing LinuxSampler...\n" << std::flush;
    kill_app(); // Use abort() if we want to generate a core dump.
}

void kill_app() {
    kill(main_thread, SIGKILL);
}

void parse_options(int argc, char **argv) {
    int res;
    int option_index = 0;
    static struct option long_options[] =
        {
            {"help",0,0,0},
            {"version",0,0,0},
            {"profile",0,0,0},
            {"no-tune",0,0,0},
            {0,0,0,0}
        };

    while (true) {
        /*
          Stephane Letz : letz@grame.fr
          getopt_long_only does not exist on OSX : replaced by getopt_long for now.
        */
        res = getopt_long(argc, argv, "", long_options, &option_index);
        if(res == -1) break;
        if (res == 0) {
            switch(option_index) {
                case 0: // --help
                    printf("usage: linuxsampler [OPTIONS]\n\n");
                    printf("--help             prints this message\n");
                    printf("--version          prints version information\n");
                    printf("--profile          profile synthesis algorithms\n");
                    printf("--no-tune          disable assembly optimization\n");
                    exit(EXIT_SUCCESS);
                    break;
                case 1: // --version
                    printf("LinuxSampler %s\n", VERSION);
                    exit(EXIT_SUCCESS);
                    break;
                case 2: // --profile
		    profile = true;
                    break;
                case 3: // --no-tune
		    tune = false;
                    break;
            }
        }
    }
}
