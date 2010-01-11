/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003-2004 by Benno Senoner and Christian Schoenebeck    *
 *   Copyright (C) 2005-2009 Christian Schoenebeck                         *
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
#include <sys/stat.h>

#if defined(WIN32)
// require at least Windows 2000 for the GlobalMemoryStatusEx() call
#if _WIN32_WINNT < 0x0500
#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif
#define _WIN32_WINNT 0x0500
#endif
#endif

#include "Sampler.h"
#include "common/global_private.h"
#include "engines/EngineFactory.h"
#include "plugins/InstrumentEditorFactory.h"
#include "drivers/midi/MidiInputDeviceFactory.h"
#include "drivers/audio/AudioOutputDeviceFactory.h"
#include "engines/gig/Profiler.h"
#include "network/lscpserver.h"
#include "common/stacktrace.h"
#include "common/Features.h"
#include "common/atomic.h"

using namespace LinuxSampler;

Sampler*    pSampler    = NULL;
LSCPServer* pLSCPServer = NULL;
#if defined(WIN32)
// inet_aton seems missing under WIN32
#ifndef INADDR_NONE
#define INADDR_NONE 0xffffffff
#endif

int inet_aton(const char *cp, struct in_addr *addr)
{
    addr->s_addr = inet_addr(cp);
    return (addr->s_addr == INADDR_NONE) ? 0 : 1;
}

#else
pid_t       main_pid;
#endif
bool bPrintStatistics = false;
bool profile = false;
bool tune = true;
static bool bShowStackTrace = false;
unsigned long int lscp_addr;
unsigned short int lscp_port;

void parse_options(int argc, char **argv);
void signal_handler(int signal);
void kill_app();
static atomic_t running = ATOMIC_INIT(1);

int main(int argc, char **argv) {

    lscp_addr = htonl(LSCP_ADDR);
    lscp_port = htons(LSCP_PORT);

    #if !defined(WIN32)
    main_pid = getpid();
    #endif

    // parse and assign command line options
    parse_options(argc, argv);

    // setting signal handler for catching SIGINT (thus e.g. <CTRL><C>)
    signal(SIGINT, signal_handler);

    // initialize the stack trace mechanism with our binary file
    // (if requested by command line option)
    if (bShowStackTrace) {
        #if defined(WIN32)
        // FIXME: sigaction() not supported on WIN32, we ignore it for now
        #else
        StackTraceInit(argv[0], -1);
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
        #endif
    }

    dmsg(1,("LinuxSampler %s\n", VERSION));
    dmsg(1,("Copyright (C) 2003,2004 by Benno Senoner and Christian Schoenebeck\n"));
    dmsg(1,("Copyright (C) 2005-2009 Christian Schoenebeck\n"));

    #if defined(WIN32)
    #if 0
    // some WIN32 memory info code which tries to determine the maximum lockable amount of memory (for debug purposes)
    SYSTEM_INFO siSysInfo;
    long physical_memory;
    GetSystemInfo(&siSysInfo);
    dmsg(2,("page size=%d\n", siSysInfo.dwPageSize));

    MEMORYSTATUSEX statex;
	statex.dwLength = sizeof (statex);
    GlobalMemoryStatusEx (&statex);
    dmsg(2, ("There are %*I64d total Kbytes of physical memory.\n",
          8, statex.ullTotalPhys));
    dmsg(2, ("There are %*I64d free Kbytes of physical memory.\n",
          8, statex.ullAvailPhys));
    physical_memory = statex.ullTotalPhys;

    HANDLE hProcess = GetCurrentProcess();

    unsigned long MinimumWorkingSetSize, MaximumWorkingSetSize;
    unsigned long DefaultMinimumWorkingSetSize, DefaultMaximumWorkingSetSize;
    unsigned long RequestedMinimumWorkingSetSize, RequestedMaximumWorkingSetSize;
    int res;

    res = GetProcessWorkingSetSize(hProcess, &DefaultMinimumWorkingSetSize, &DefaultMaximumWorkingSetSize);

    RequestedMaximumWorkingSetSize = physical_memory - 2*1024*1024;
    RequestedMinimumWorkingSetSize = RequestedMaximumWorkingSetSize;

    for(;;) {
        dmsg(2,("TRYING VALUES  RequestedMinimumWorkingSetSize=%d, RequestedMaximumWorkingSetSize=%d\n", RequestedMinimumWorkingSetSize, RequestedMaximumWorkingSetSize));
        res = SetProcessWorkingSetSize(hProcess, RequestedMinimumWorkingSetSize, RequestedMaximumWorkingSetSize);
        dmsg(2,("AFTER SET: res = %d  RequestedMinimumWorkingSetSize=%d, RequestedMaximumWorkingSetSize=%d\n", res,RequestedMinimumWorkingSetSize, RequestedMaximumWorkingSetSize));

        res = GetProcessWorkingSetSize(hProcess, &MinimumWorkingSetSize, &MaximumWorkingSetSize);
        dmsg(2,("AFTER GET: res = %d  MinimumWorkingSetSize=%d, MaximumWorkingSetSize=%d\n", res,MinimumWorkingSetSize, MaximumWorkingSetSize));

        if( RequestedMinimumWorkingSetSize == MinimumWorkingSetSize ) {
            dmsg(2,("RequestedMinimumWorkingSetSize == MinimumWorkingSetSize. OK !\n"));
            break;
        }

        RequestedMinimumWorkingSetSize -=  10*1024*1024;
        if(RequestedMinimumWorkingSetSize < DefaultMinimumWorkingSetSize) break;
    }

    dmsg(2,("AFTER GetProcessWorkingSetSize: res = %d  MinimumWorkingSetSize=%d, MaximumWorkingSetSize=%d\n", res,MinimumWorkingSetSize, MaximumWorkingSetSize));
    #endif
    #endif // WIN32

    if (tune) {
        // detect and print system / CPU specific features
        Features::detect();
        dmsg(1,("Detected features: %s\n", Features::featuresAsString().c_str()));
        // prevent slow denormal FPU modes
        Features::enableDenormalsAreZeroMode();
    }

    dmsg(1,("Automatic Stacktrace: %s\n", (bShowStackTrace) ? "On" : "Off"));

    // create LinuxSampler instance
    dmsg(1,("Creating Sampler..."));
    pSampler = new Sampler;
    dmsg(1,("OK\n"));

    dmsg(1,("Registered sampler engines: %s\n", EngineFactory::AvailableEngineTypesAsString().c_str()));
    dmsg(1,("Registered MIDI input drivers: %s\n", MidiInputDeviceFactory::AvailableDriversAsString().c_str()));
    dmsg(1,("Registered audio output drivers: %s\n", AudioOutputDeviceFactory::AvailableDriversAsString().c_str()));
    dmsg(1,("Registered instrument editors: %s\n", InstrumentEditorFactory::AvailableEditorsAsString().c_str()));

    // start LSCP network server
    struct in_addr addr;
    addr.s_addr = lscp_addr;
    dmsg(1,("Starting LSCP network server (%s:%d)...", inet_ntoa(addr), ntohs(lscp_port)));
    pLSCPServer = new LSCPServer(pSampler, lscp_addr, lscp_port);
    pLSCPServer->StartThread();
    pLSCPServer->WaitUntilInitialized();
    dmsg(1,("OK\n"));

    if (profile)
    {
        dmsg(1,("Calibrating profiler..."));
        LinuxSampler::gig::Profiler::Calibrate();
        LinuxSampler::gig::Profiler::Reset();
        LinuxSampler::gig::Profiler::enable();
        dmsg(1,("OK\n"));
    }

    printf("LinuxSampler initialization completed. :-)\n\n");

    while (atomic_read(&running)) {
        if (bPrintStatistics) {
            const std::set<Engine*>& engines = EngineFactory::EngineInstances();
            std::set<Engine*>::iterator itEngine = engines.begin();
            for (int i = 0; itEngine != engines.end(); itEngine++, i++) {
                Engine* pEngine = *itEngine;
                printf("Engine %d) Voices: %3.3d (Max: %3.3d) Streams: %3.3d (Max: %3.3d)\n", i,
                    pEngine->VoiceCount(), pEngine->VoiceCountMax(),
                    pEngine->DiskStreamCount(), pEngine->DiskStreamCountMax()
                );
                fflush(stdout);
            }
        }

        sleep(1);
        if (profile)
        {
            unsigned int samplingFreq = 48000; //FIXME: hardcoded for now
            unsigned int bv = LinuxSampler::gig::Profiler::GetBogoVoices(samplingFreq);
            if (bv != 0)
            {
                printf("       BogoVoices: %i         \r", bv);
                fflush(stdout);
            }
        }

        pSampler->fireStatistics();
    }
    if (pLSCPServer) pLSCPServer->StopThread();
    // the delete order here is important: the Sampler
    // destructor sends notifications to the lscpserver
    if (pSampler) delete pSampler;
    if (pLSCPServer) delete pLSCPServer;
    printf("LinuxSampler stopped due to SIGINT.\n");
    return EXIT_SUCCESS;
}

void signal_handler(int iSignal) {
    switch (iSignal) {
        case SIGINT:
            atomic_set(&running, 0);
            return;
        #if defined(WIN32)
        // FIXME: under WIN32 we ignore the signals below due to the missing sigaction call
        #else
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
        #endif
        default: { // this should never happen, as we register for the signals we want
            std::cerr << ">>> FATAL ERROR: Unknown signal received! <<<\n" << std::flush;
            break;
        }
    }
    signal(iSignal, SIG_DFL); // Reinstall default handler to prevent race conditions
    if (bShowStackTrace) {
        std::cerr << "Showing stack trace...\n" << std::flush;
        StackTrace();
        sleep(2);
    }
    std::cerr << "Killing LinuxSampler...\n" << std::flush;
    kill_app(); // Use abort() if we want to generate a core dump.
}

void kill_app() {
    #if defined(WIN32)
    // FIXME: do we need to do anything at this point under WIN32 ?  is exit(0) ok ?
    exit(0);
    #else
    kill(main_pid, SIGKILL);
    #endif
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
            {"statistics",0,0,0},
            {"instruments-db-location",1,0,0},
            {"create-instruments-db",1,0,0},
            {"lscp-addr",1,0,0},
            {"lscp-port",1,0,0},
            {"stacktrace",0,0,0},
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
                    printf("--help                      prints this message\n");
                    printf("--version                   prints version information\n");
                    printf("--profile                   profile synthesis algorithms\n");
                    printf("--no-tune                   disable assembly optimization\n");
                    printf("--statistics                periodically prints statistics\n");
                    printf("--lscp-addr                 set LSCP address (default: any)\n");
                    printf("--lscp-port                 set LSCP port (default: 8888)\n");
                    printf("--create-instruments-db     creates an instruments DB\n");
                    printf("--instruments-db-location   specifies the instruments DB file\n");
                    printf("--stacktrace                automatically shows stacktrace if crashes\n");
                    printf("                            (broken on most systems at the moment)\n");
                    exit(EXIT_SUCCESS);
                    break;
                case 1: // --version
                    printf("LinuxSampler %s\n", VERSION);
                    exit(EXIT_SUCCESS);
                    break;
                case 2: // --profile
                    profile = true;
                    //FIXME: profiling code is currently broken!
                    std::cerr << "Option '--profile' is currently not supported, since the profiling code is currently broken!"  << std::endl;
                    exit(EXIT_FAILURE);
                    break;
                case 3: // --no-tune
                    tune = false;
                    break;
                case 4: // --statistics
                    bPrintStatistics = true;
                    break;
                case 5: // --instruments-db-location
#if HAVE_SQLITE3
                    try {
                        if (optarg) {
                            struct stat statBuf;
                            int res = stat(optarg, &statBuf);

                            if (res) {
                                std::stringstream ss;
                                ss << "Failed to stat `" << optarg << "`: " << strerror(errno);
                                throw Exception(ss.str());
                            }

                            if (!S_ISREG(statBuf.st_mode)) {
                                std::stringstream ss;
                                ss << "`" << optarg << "` is not a regular file";
                                throw Exception(ss.str());
                            }

                            InstrumentsDb::GetInstrumentsDb()->SetDbFile(String(optarg));
                        }
                    } catch(Exception e) {
                        std::cerr << "Could not open instruments DB file: "
                                  << e.Message() << std::endl;
                        exit(EXIT_FAILURE);
                    }
                    break;
#else
                    std::cerr << "LinuxSampler was not build with ";
                    std::cerr << "instruments database support!\n";
                    exit(EXIT_FAILURE);
                    break;
#endif
                case 6: // --create-instruments-db
#if HAVE_SQLITE3
                    try {
                        if (optarg) {
                            std::cout << "Creating instruments database..." << std::endl;
                            InstrumentsDb::CreateInstrumentsDb(String(optarg));
                            std::cout << "Done" << std::endl;
                        }
                    } catch(Exception e) {
                        std::cerr << e.Message() << std::endl;
                        exit(EXIT_FAILURE);
                        return;
                    }

                    exit(EXIT_SUCCESS);
                    return;
#else
                    std::cerr << "Failed to create the database. LinuxSampler was ";
                    std::cerr << "not build with instruments database support!\n";
                    exit(EXIT_FAILURE);
                    return;
#endif
                case 7: { // --lscp-addr
                    struct in_addr addr;
                    if (inet_aton(optarg, &addr) == 0)
                        printf("WARNING: Failed to parse lscp-addr argument, ignoring!\n");
                    else
                        lscp_addr = addr.s_addr;
                    break;
                }
                case 8: {// --lscp-port
                    long unsigned int port = 0;
                    if ((sscanf(optarg, "%u", &port) != 1) || (port == 0) || (port > 65535))
                        printf("WARNING: Failed to parse lscp-port argument, ignoring!\n");
                    else
                        lscp_port = htons(port);
                    break;
                }
                case 9: // --stacktrace
                    bShowStackTrace = true;
                    break;
            }
        }
    }
}
