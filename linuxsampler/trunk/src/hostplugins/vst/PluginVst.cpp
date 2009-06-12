/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2008 - 2009 Andreas Persson                             *
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
 *   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,                *
 *   MA  02110-1301  USA                                                   *
 ***************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <cstring>

#ifdef WIN32
#include <tchar.h>
#endif

#include "PluginVst.h"

#ifndef CHANNELS
#define CHANNELS 32
#endif

namespace {

#if defined(WIN32) && CONFIG_DEBUG_LEVEL >= 2
// on windows, send debug logging to a file instead of a non-existent
// console
#include <cstdarg>
#include "../../common/Mutex.h"
    LinuxSampler::Mutex logmutex;

    void log(const char* fmt, ...) {
        logmutex.Lock();
        FILE* f = fopen("C:\\linuxsamplervst.log", "a");
        va_list ap;
        va_start(ap, fmt);
        vfprintf(f, fmt, ap);
        va_end(ap);
        fclose(f);
        logmutex.Unlock();
    }
#undef dmsg
#define dmsg(debuglevel,x) log x;
#endif


// *************** LinuxSamplerVstProgram ***************
// *

    LinuxSamplerVstProgram::LinuxSamplerVstProgram() {
        vst_strncpy(name, "Basic", kVstMaxProgNameLen);
    }


// *************** LinuxSamplerEditor ***************
// *

    LinuxSamplerEditor::LinuxSamplerEditor(AudioEffect* effect) :
        AEffEditor(effect) {
        dmsg(2, ("-->LinuxSamplerEditor constructor\n"));
#ifdef WIN32
        ProcessHandle = INVALID_HANDLE_VALUE;
#endif
    }

    LinuxSamplerEditor::~LinuxSamplerEditor() {
        close();
    }

    bool LinuxSamplerEditor::open(void* ptr) {
        dmsg(2, ("-->LinuxSamplerEditor::open\n"));
        AEffEditor::open(ptr);

#ifdef WIN32
        // try to start the JSample Fantasia GUI as a separate process

        // first check if it's already running
        if (ProcessHandle != INVALID_HANDLE_VALUE) {
            DWORD exitCode;
            if (GetExitCodeProcess(ProcessHandle, &exitCode)) {
                if (exitCode == STILL_ACTIVE) return true;
            }
            free(Command);
            CloseHandle(ProcessHandle);
            ProcessHandle = INVALID_HANDLE_VALUE;
        }

        // assume Fantasia is in the same directory as the
        // liblinuxsampler dll
        String lspath = LinuxSampler::Sampler::GetInstallDir();
        if (!lspath.empty()) {
            lspath += "\\";
            WIN32_FIND_DATA fd;
            HANDLE hFind = FindFirstFile((lspath + "Fantasia*.jar").c_str(), &fd);
            if (hFind != INVALID_HANDLE_VALUE) {
                String fantasia(fd.cFileName);
                FindClose(hFind);

                // start a java process
                STARTUPINFO si;
                PROCESS_INFORMATION pi;
                ZeroMemory(&si, sizeof(si));
                si.cb = sizeof(si);
                ZeroMemory(&pi, sizeof(pi));

                Command = _tcsdup(TEXT((String("javaw -jar \"") + lspath + fantasia + "\" &").c_str()));
                CreateProcess(NULL, Command, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
                ProcessHandle = pi.hProcess;
                CloseHandle(pi.hThread);
            }
        }
#endif
        dmsg(2, ("<--LinuxSamplerEditor::open\n"));
        return true;
    }

    void LinuxSamplerEditor::close() {
        systemWindow = 0;
#ifdef WIN32
        if (ProcessHandle != INVALID_HANDLE_VALUE) {
            TerminateProcess(ProcessHandle, 0);
            free(Command);
            CloseHandle(ProcessHandle);
            ProcessHandle = INVALID_HANDLE_VALUE;
        }
#endif
    }

    bool LinuxSamplerEditor::getRect(ERect** rect) {
        ERect* r = new ERect();
        r->top = 0;
        r->left = 0;
        r->bottom = 0;
        r->right = 400;
        *rect = r;
        return true;
    }


// *************** LinuxSamplerVst ***************
// *

    LinuxSamplerVst::LinuxSamplerVst(audioMasterCallback audioMaster) :
        AudioEffectX(audioMaster, NbPrograms, 0),
        StateBuf(0)
    {
        dmsg(2, ("-->constructor\n"));

        Programs = new LinuxSamplerVstProgram[NbPrograms];
        setProgram(0);
        setNumInputs(0);
        setNumOutputs(CHANNELS);
        canProcessReplacing();
        isSynth();
        programsAreChunks();
        setUniqueID(CCONST('L', 'S', 'm', 'p')); // (registred at Steinberg)
        setEditor(new LinuxSamplerEditor(this));

        suspend();
        dmsg(2, ("<--constructor\n"));
    }


    void LinuxSamplerVst::resume() {
        dmsg(2, ("-->resume\n"));
        if (!pAudioDevice) {
            Init(int(sampleRate), blockSize, CHANNELS);

            if (!SavedChunk.empty()) {
                SetState(SavedChunk);
                SavedChunk.clear();
            } else {
                InitState();
            }
        } else {
            Init(int(sampleRate), blockSize);
        }
        dmsg(2, ("<--resume\n"));
    }

    LinuxSamplerVst::~LinuxSamplerVst() {
        dmsg(2, ("-->destructor\n"));
        delete[] Programs;
        if (StateBuf) free(StateBuf);
        dmsg(2, ("<--destructor\n"));
    }


    void LinuxSamplerVst::setProgram(VstInt32 program) {
        if (program < 0 || program >= NbPrograms) return;

        curProgram = program;
    }


    void LinuxSamplerVst::setProgramName(char* name) {
        vst_strncpy(Programs[curProgram].name, name, kVstMaxProgNameLen);
    }


    void LinuxSamplerVst::getProgramName(char* name) {
        vst_strncpy(name, Programs[curProgram].name, kVstMaxProgNameLen);
    }


    bool LinuxSamplerVst::getOutputProperties(VstInt32 index,
                                              VstPinProperties* properties) {
        if (index < CHANNELS) {
            sprintf(properties->label, "LS %d", index + 1);
            properties->flags = kVstPinIsActive | kVstPinIsStereo;
            return true;
        }
        return false;
    }


    bool LinuxSamplerVst::getProgramNameIndexed(VstInt32 category, VstInt32 index,
                                                char* text) {
        if (index < NbPrograms) {
            vst_strncpy(text, Programs[index].name, kVstMaxProgNameLen);
            return true;
        }
        return false;
    }


    bool LinuxSamplerVst::getEffectName(char* name) {
        vst_strncpy(name, "LinuxSampler", kVstMaxEffectNameLen);
        return true;
    }


    bool LinuxSamplerVst::getVendorString(char* text) {
        vst_strncpy(text, "linuxsampler.org", kVstMaxVendorStrLen);
        return true;
    }


    bool LinuxSamplerVst::getProductString(char* text) {
        vst_strncpy(text, "LinuxSampler VST", kVstMaxProductStrLen);
        return true;
    }


    VstInt32 LinuxSamplerVst::getVendorVersion() {
        return 1000;
    }


    VstInt32 LinuxSamplerVst::canDo(char* text) {
        dmsg(2, ("canDo %s\n", text));
        if (strcmp(text, "receiveVstEvents") == 0 ||
            strcmp(text, "receiveVstMidiEvent") == 0) return 1;
        return -1;
    }

    void LinuxSamplerVst::setSampleRate(float sampleRate) {
        dmsg(2, ("linuxsampler: setSampleRate %f\n", sampleRate));
        AudioEffectX::setSampleRate(sampleRate);
    }

    void LinuxSamplerVst::setBlockSize(VstInt32 blockSize) {
        dmsg(2, ("linuxsampler: setBlockSize %d\n", blockSize));
        AudioEffectX::setBlockSize(blockSize);
    }


    void LinuxSamplerVst::processReplacing(float** inputs, float** outputs,
                                           VstInt32 sampleFrames) {
        if (pAudioDevice) {
            for (int i = 0 ; i < CHANNELS ; i++) {
                pAudioDevice->Channel(i)->SetBuffer(outputs[i]);
            }
            pAudioDevice->Render(sampleFrames);
        } else {
            for (int i = 0 ; i < CHANNELS ; i++) {
                memset(outputs[i], 0, sampleFrames * sizeof(float));
            }
        }
    }


    VstInt32 LinuxSamplerVst::processEvents(VstEvents* ev) {
        if (pMidiDevice) {
            for (int i = 0; i < ev->numEvents; i++)
            {
                if (ev->events[i]->type == kVstMidiType) {
                    VstMidiEvent* event = reinterpret_cast<VstMidiEvent*>(ev->events[i]);
                    pMidiDevice->Port()->DispatchRaw(reinterpret_cast<uint8_t*>(event->midiData),
                                                     event->deltaFrames);
                }
            }
        }
        return 1;
    }


    VstInt32 LinuxSamplerVst::getChunk(void** data, bool isPreset) {
        dmsg(2, ("-->getChunk\n"));

        String state = GetState();
        dmsg(2, ("state=\"%s\"\n", state.c_str()));;
        if (StateBuf) free(StateBuf);
        StateBuf = strdup(state.c_str());
        *data = StateBuf;
        dmsg(2, ("<--getChunk\n"));
        return state.length() + 1;
    }


    VstInt32 LinuxSamplerVst::setChunk(void* data, VstInt32 byteSize,
                                       bool isPreset) {
        dmsg(2, ("-->setChunk byteSize=%d isPreset=%d\n", byteSize, isPreset));

        const char* state = static_cast<const char*>(data);
        VstInt32 res = 0;
        if (byteSize > 0 && state[byteSize - 1] == '\0') {
            dmsg(2, ("state=\"%s\"\n", state));
            if (pAudioDevice) {
                res = SetState(state);
            } else {
                SavedChunk = state;
            }
        }
        dmsg(2, ("<--setChunk\n"));
        return res;
    }
}


// *************** VST main function ***************
// *

AudioEffect* createEffectInstance(audioMasterCallback audioMaster)
{
    return new LinuxSamplerVst(audioMaster);
}
