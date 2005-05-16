/***************************************************************************
 *                                                                         *
 *   libgig - C++ cross-platform Gigasampler format file loader library    *
 *                                                                         *
 *   Copyright (C) 2003-2005 by Christian Schoenebeck                      *
 *                              <cuse@users.sourceforge.net>               *
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

// just for testing the disk streaming capability of libgig;
// you will also need to set this to 1 at the moment if you want to
// extract compressed samples, as I haven't implemented the
// decompression algorithm in gig::Sample::LoadSampleData() yet
#define USE_DISK_STREAMING	1

// only when USE_DISK_STREAMING is set to 1:
// just for testing the disk stream capability; with this option set
// gigextract will read the samples in smaller pieces, just to stress
// gig::Sample::Read() method a bit
#define HASHED_READS_TEST	1

#include <iostream>
#include <cstdlib>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <dlfcn.h>

// only libsndfile is available for Windows, so we use that for writing the sound files
#ifdef WIN32
# define HAVE_SNDFILE 1
#endif // WIN32

// we prefer libsndfile before libaudiofile
#if HAVE_SNDFILE
# include <sndfile.h>
#else
# include <audiofile.h>
#endif // HAVE_SNDFILE

#include "gig.h"

using namespace std;

typedef map<unsigned int, bool> OrderMap;
OrderMap* pOrderedSamples = NULL;

string Revision();
void PrintVersion();
void PrintUsage();
void ExtractSamples(gig::File* gig, char* destdir, OrderMap* ordered);
int writeWav(const char* filename, void* samples, long samplecount, int channels, int bitdepth, long rate);
string ToString(int i);

#ifndef HAVE_SNDFILE
void* hAFlib; // handle to libaudiofile
void openAFlib(void);
void closeAFlib(void);
// pointers to libaudiofile functions
AFfilesetup(*_afNewFileSetup)(void);
void(*_afFreeFileSetup)(AFfilesetup);
void(*_afInitChannels)(AFfilesetup,int,int);
void(*_afInitSampleFormat)(AFfilesetup,int,int,int);
void(*_afInitFileFormat)(AFfilesetup,int);
void(*_afInitRate)(AFfilesetup,int,double);
int(*_afWriteFrames)(AFfilehandle,int,const void*,int);
AFfilehandle(*_afOpenFile)(const char*,const char*,AFfilesetup);
int(*_afCloseFile)(AFfilehandle file);
#endif // !HAVE_SNDFILE

int main(int argc, char *argv[]) {
     if (argc >= 2) {
        if (argv[1][0] == '-') {
            switch (argv[1][1]) {
                case 'v':
                    PrintVersion();
                    return EXIT_SUCCESS;
            }
        }
    }
    if (argc < 3) {
        PrintUsage();
        return EXIT_FAILURE;
    }
    if (argc > 3) { // extracting specific samples
        pOrderedSamples = new OrderMap;
        for (int i = 3; i < argc; i++) {
            unsigned int index = atoi(argv[i]);
            (*pOrderedSamples)[index] = true;
        }
    }
    FILE* hFile = fopen(argv[1], "r");
    if (!hFile) {
        cout << "Invalid input file argument!" << endl;
        return EXIT_FAILURE;
    }
    fclose(hFile);
    DIR* dir = opendir(argv[2]);
    if (!dir) {
        cout << "Unable to open DESTDIR: ";
        switch (errno) {
            case EACCES:  cout << "Permission denied." << endl;
                          break;
            case EMFILE:  cout << "Too many file descriptors in use by process." << endl;
                          break;
            case ENFILE:  cout << "Too many files are currently open in the system." << endl;
                          break;
            case ENOENT:  cout << "Directory does not exist, or name is an empty string." << endl;
                          break;
            case ENOMEM:  cout << "Insufficient memory to complete the operation." << endl;
                          break;
            case ENOTDIR: cout << "Is not a directory." << endl;
                          break;
            default:      cout << "Unknown error" << endl;
        }
        return EXIT_FAILURE;
    }
    if (dir) closedir(dir);
    try {
        RIFF::File* riff = new RIFF::File(argv[1]);
        gig::File*  gig  = new gig::File(riff);
        cout << "Extracting samples from \"" << argv[1] << "\" to directory \"" << argv[2] << "\"." << endl << flush;
        ExtractSamples(gig, argv[2], pOrderedSamples);
        cout << "Extraction finished." << endl << flush;
        delete gig;
        delete riff;
        if (pOrderedSamples) delete pOrderedSamples;
    }
    catch (RIFF::Exception e) {
        e.PrintMessage();
        return EXIT_FAILURE;
    }
    catch (...) {
        cout << "Unknown exception while trying to parse file." << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void ExtractSamples(gig::File* gig, char* destdir, OrderMap* ordered) {
#ifndef HAVE_SNDFILE
    hAFlib = NULL;
    openAFlib();
#endif // !HAVE_SNDFILE
    uint8_t* pWave  = NULL;
    long BufferSize = 0;
    int samples     = 0;
    cout << "Seeking for available samples..." << flush;
    gig::Sample* pSample = gig->GetFirstSample();
    cout << "OK" << endl << flush;
    while (pSample) {
        samples++;
        if (ordered) {
            if ((*ordered)[samples] == false) {
                pSample = gig->GetNextSample();
                continue;
            }
        }
        string name = pSample->pInfo->Name;
        string filename = destdir;
        if (filename[filename.size() - 1] != '/') filename += "/";
        filename += ToString(samples);
        filename += "_";
        if (name == "") {
            name = "(NO NAME)";
            filename += "NONAME";
        }
        else {
            filename += name;
            name.insert(0, "\"");
            name += "\"";
        }
        filename += ".wav";
        if (pSample->Compressed) cout << "Decompressing ";
        else                     cout << "Extracting ";
        cout << "Sample " << samples << ") " << name << " (" << pSample->BitDepth <<"Bits, " << pSample->SamplesPerSecond << "Hz, " << pSample->Channels << " Channels, " << pSample->SamplesTotal << " Samples)..." << flush;


#if USE_DISK_STREAMING
        long neededsize = (pSample->Compressed) ? 10485760 /* 10 MB buffer */
                                                : pSample->SamplesTotal * pSample->FrameSize;
        if (BufferSize < neededsize) {
            if (pWave) delete[] pWave;
            pWave = new uint8_t[neededsize];
            BufferSize = neededsize;
        }
#  if HASHED_READS_TEST
        unsigned long readsamples     = 0,
                      readinthisrun   = 0,
                      samplepiecesize = 2000;
        uint8_t* pSamplePiece = pWave;
        do { // we read the sample in small pieces and increment the size with each run just to test streaming capability
            readinthisrun = pSample->Read(pSamplePiece, ++samplepiecesize);
            // 24 bit is truncated to 16 by Sample::Read at the moment
            pSamplePiece += readinthisrun * (2 * pSample->Channels); // readinthisrun * pSample->FrameSize;
            readsamples  += readinthisrun;
        } while (readinthisrun == samplepiecesize);

        if (pSample->Compressed) { // hack
            pSample->SamplesTotal = readsamples;
            pSample->BitDepth = 16;
        }
#  else // read in one piece
        if (pSample->Compressed) {
            pSample->SamplesTotal = pSample->Read(pWave, 10485760 >> 2); // assumes 16 bit stereo
        }
        else {
            pSample->Read(pWave, pSample->SamplesTotal);
        }
#  endif // HASHED_READS_TEST
#else // no disk streaming
        if (pSample->Compressed) {
            cout << "Sorry, sample is compressed and Sample::LoadSampleData() has no decompression routine yet! - Solution: set USE_DISK_STREAMING in gigextract.cpp (line 29) to 1 and recompile!" << endl;
        }
        else pWave = (uint8_t*) pSample->LoadSampleData(); // load wave into RAM
#endif // USE_DISK_STREAMING
        if (pWave) {
            int res = writeWav(filename.c_str(),
                               pWave,
                               pSample->SamplesTotal,
                               pSample->Channels,
                               pSample->BitDepth,
                               pSample->SamplesPerSecond);
            if (res < 0) cout << "Couldn't write sample data." << endl;
            else cout << "ok" << endl;
            pSample->ReleaseSampleData(); // free wave from RAM
        }
        else cout << "Failed to load sample data." << endl;

        pSample = gig->GetNextSample();
    }
    if (pWave) delete[] (uint8_t*) pWave;
#ifndef HAVE_SNDFILE
    closeAFlib();
#endif // !HAVE_SNDFILE
}

int writeWav(const char* filename, void* samples, long samplecount, int channels, int bitdepth, long rate) {
#if HAVE_SNDFILE
    SNDFILE* hfile;
    SF_INFO  sfinfo;
    int format = SF_FORMAT_WAV;
    switch (bitdepth) {
        case 8:
            format |= SF_FORMAT_PCM_S8;
            cout << "8 bit" << endl << flush;
            break;
        case 16:
            format |= SF_FORMAT_PCM_16;
            cout << "16 bit" << endl << flush;
            break;
        case 24:
            format |= SF_FORMAT_PCM_24;
            cout << "24 bit" << endl << flush;
            break;
        case 32:
            format |= SF_FORMAT_PCM_32;
            cout << "32 bit" << endl << flush;
            break;
        default:
            cerr << "Error: Bithdepth " << ToString(bitdepth) << " not supported by libsndfile, ignoring sample!\n" << flush;
            return -1;
    }
    memset(&sfinfo, 0, sizeof (sfinfo));
    sfinfo.samplerate = rate;
    sfinfo.frames     = samplecount;
    sfinfo.channels   = channels;
    sfinfo.format     = format;
    if (!(hfile = sf_open(filename, SFM_WRITE, &sfinfo))) {
        cerr << "Error: Unable to open output file \'" << filename << "\'.\n" << flush;
        return -1;
    }
    if (sf_write_short(hfile, (short*)samples, channels * samplecount) != channels * samplecount) {
        cerr << sf_strerror(hfile) << endl << flush;
        sf_close(hfile);
        return -1;
    }
    sf_close(hfile);
#else
    AFfilesetup setup = _afNewFileSetup();
    _afInitFileFormat(setup, AF_FILE_WAVE);
    _afInitChannels(setup, AF_DEFAULT_TRACK, channels);
    _afInitSampleFormat(setup, AF_DEFAULT_TRACK, AF_SAMPFMT_TWOSCOMP, bitdepth);
    _afInitRate(setup, AF_DEFAULT_TRACK, rate);
    if (setup == AF_NULL_FILESETUP) return -1;
    AFfilehandle hFile = _afOpenFile(filename, "w", setup);
    if (hFile == AF_NULL_FILEHANDLE) return -1;
    if (_afWriteFrames(hFile, AF_DEFAULT_TRACK, samples, samplecount) < 0) return -1;
    _afCloseFile(hFile);
    _afFreeFileSetup(setup);
#endif // HAVE_SNDFILE

    return 0; // success
}

#ifndef HAVE_SNDFILE
void openAFlib() {
    hAFlib = dlopen("libaudiofile.so", RTLD_NOW);
    if (!hAFlib) {
        cout << "Unable to load library libaudiofile.so: " << dlerror() << endl;
        return;
    }
    _afNewFileSetup     = (AFfilesetup(*)(void)) dlsym(hAFlib, "afNewFileSetup");
    _afFreeFileSetup    = (void(*)(AFfilesetup)) dlsym(hAFlib, "afFreeFileSetup");
    _afInitChannels     = (void(*)(AFfilesetup,int,int)) dlsym(hAFlib, "afInitChannels");
    _afInitSampleFormat = (void(*)(AFfilesetup,int,int,int)) dlsym(hAFlib, "afInitSampleFormat");
    _afInitFileFormat   = (void(*)(AFfilesetup,int)) dlsym(hAFlib, "afInitFileFormat");
    _afInitRate         = (void(*)(AFfilesetup,int,double)) dlsym(hAFlib, "afInitRate");
    _afWriteFrames      = (int(*)(AFfilehandle,int,const void*,int)) dlsym(hAFlib, "afWriteFrames");
    _afOpenFile         = (AFfilehandle(*)(const char*,const char*,AFfilesetup)) dlsym(hAFlib, "afOpenFile");
    _afCloseFile        = (int(*)(AFfilehandle file)) dlsym(hAFlib, "afCloseFile");
    if (dlerror()) cout << "Failed to load function from libaudiofile.so: " << dlerror() << endl;
}

void closeAFlib() {
    if (hAFlib) dlclose(hAFlib);
}
#endif // !HAVE_SNDFILE

string Revision() {
    string s = "$Revision: 1.6 $";
    return s.substr(11, s.size() - 13); // cut dollar signs, spaces and CVS macro keyword
}

void PrintVersion() {
    cout << "gigextract revision " << Revision() << endl;
    cout << "using " << gig::libraryName() << " " << gig::libraryVersion();
    #if HAVE_SNDFILE
    char versionBuffer[128];
    sf_command(NULL, SFC_GET_LIB_VERSION, versionBuffer, 128);
    cout << ", " << versionBuffer;
    #endif // HAVE_SNDFILE
    cout << endl;
    #if !HAVE_SNDFILE
    cout << "built against libaudiofile "
         << LIBAUDIOFILE_MAJOR_VERSION << "." << LIBAUDIOFILE_MINOR_VERSION
    # ifdef LIBAUDIOFILE_MICRO_VERSION
         << "." << LIBAUDIOFILE_MICRO_VERSION
    # endif // LIBAUDIOFILE_MICRO_VERSION
         << endl;
    #endif // !HAVE_SNDFILE
}

void PrintUsage() {
    cout << "gigextract - extracts samples from a Gigasampler file." << endl;
    cout << endl;
    cout << "Usage: gigextract [-v] GIGFILE DESTDIR [SAMPLENR] [ [SAMPLENR] ...]" << endl;
    cout << endl;
    cout << "	GIGFILE  Input Gigasampler (.gig) file." << endl;
    cout << endl;
    cout << "	DESTDIR  Destination directory where all .wav files will be written to." << endl;
    cout << endl;
    cout << "	SAMPLENR Index (/indices) of Sample(s) which should be extracted." << endl;
    cout << "	         If no sample indices are given, all samples will be extracted" << endl;
    cout << "	         (use gigdump to look for available samples)." << endl;
    cout << endl;
    cout << "	-v       Print version and exit." << endl;
    cout << endl;
}

string ToString(int i) {
    static char strbuf[1024];
    sprintf(strbuf,"%d",i);
    string s = strbuf;
    return s;
}
