/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2009 Grigor Iliev                                       *
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

#ifndef _AUDIOOUTPUTDEVICECOREAUDIO_H
#define	_AUDIOOUTPUTDEVICECOREAUDIO_H

#include "../../common/atomic.h"
#include "../../common/Mutex.h"
#include "../../common/Thread.h"

#include "AudioOutputDevice.h"

#include <AudioToolbox/AudioToolbox.h>
#include <CoreAudio/CoreAudio.h>

namespace LinuxSampler {

    /** Core Audio audio output driver
     *
     * Implements audio output to the Core Audio architecture.
     */
    class AudioOutputDeviceCoreAudio : public AudioOutputDevice, protected Thread {
        private:
            struct AQPlayerState {
                AudioStreamBasicDescription   mDataFormat;
                AudioQueueRef                 mQueue;
                AudioQueueBufferRef*          mBuffers;
                UInt32                        bufferByteSize;
                UInt32                        mNumPacketsToRead;
                atomic_t                      mIsRunning;
                AudioOutputDeviceCoreAudio*   pDevice; // needed for the callback
            };

            struct DeviceInfo {
                uint uiSamplerate;
                uint uiChannelNumber;
            };

        public:
            AudioOutputDeviceCoreAudio(std::map<String,DeviceCreationParameter*> Parameters);
            virtual ~AudioOutputDeviceCoreAudio();

            // derived abstract methods from class 'AudioOutputDevice'
            virtual void Play();
            virtual bool IsPlaying();
            virtual void Stop();
            virtual uint MaxSamplesPerCycle();
            virtual uint SampleRate();
            virtual String Driver();
            virtual AudioChannel* CreateChannel(uint ChannelNr);

            static String Name();
            static String Description();
            static String Version();


// *************** PARAMETERS ***************

            /** Device Parameter 'SAMPLERATE'
             *
             * Used to set the sample rate of the audio output device.
             */
            class ParameterSampleRate : public AudioOutputDevice::ParameterSampleRate {
                public:
                    ParameterSampleRate();
                    ParameterSampleRate(String s);
                    virtual optional<int> DefaultAsInt(std::map<String,String> Parameters);
            };

            /** Device Parameters 'CHANNELS'
             *
             * Used to increase / decrease the number of audio channels of
             * audio output device.
             */
            class ParameterChannels : public AudioOutputDevice::ParameterChannels {
                public:
                    ParameterChannels();
                    ParameterChannels(String s);
                    virtual optional<int> DefaultAsInt(std::map<String,String> Parameters);
            };

            /** Device Parameter 'BUFFERS'
             *
             * Used to select the number of audio buffers.
             */
            class ParameterBuffers : public DeviceCreationParameterInt {
                public:
                    ParameterBuffers();
                    ParameterBuffers(String s) throw (Exception);
                    virtual String Description();
                    virtual bool   Fix();
                    virtual bool   Mandatory();
                    virtual std::map<String,DeviceCreationParameter*> DependsAsParameters();
                    virtual optional<int>    DefaultAsInt(std::map<String,String> Parameters);
                    virtual optional<int>    RangeMinAsInt(std::map<String,String> Parameters);
                    virtual optional<int>    RangeMaxAsInt(std::map<String,String> Parameters);
                    virtual std::vector<int> PossibilitiesAsInt(std::map<String,String> Parameters);
                    virtual void             OnSetValue(int i) throw (Exception);
                    static String Name();
            };

            /** Device Parameter 'BUFFERSIZE'
             *
             * Used to set the audio buffer size in sample frames.
             */
            class ParameterBufferSize : public DeviceCreationParameterInt {
                public:
                    ParameterBufferSize();
                    ParameterBufferSize(String s) throw (Exception);
                    virtual String Description();
                    virtual bool   Fix();
                    virtual bool   Mandatory();
                    virtual std::map<String,DeviceCreationParameter*> DependsAsParameters();
                    virtual optional<int>    DefaultAsInt(std::map<String,String> Parameters);
                    virtual optional<int>    RangeMinAsInt(std::map<String,String> Parameters);
                    virtual optional<int>    RangeMaxAsInt(std::map<String,String> Parameters);
                    virtual std::vector<int> PossibilitiesAsInt(std::map<String,String> Parameters);
                    virtual void             OnSetValue(int i) throw (Exception);
                    static String Name();
            };

        protected:
            int Main();  ///< Implementation of virtual method from class Thread

        private:
            uint           uiCoreAudioChannels;
            uint           uiBufferNumber; // once initialized this value shouldn't be changed
            uint           uiBufferSize; // once initialized this value shouldn't be changed
            AQPlayerState  aqPlayerState;
            atomic_t       pausedNew;
            uint           pausedOld;
            Mutex          destroyMutex;

            static DeviceInfo* pDeviceInfo;

            static void HandleOutputBuffer(void *aqData, AudioQueueRef inAQ, AudioQueueBufferRef inBuffer);
            static void SetAudioDataFormat(AudioStreamBasicDescription* pDataFormat);
            static DeviceInfo* GetDeviceInfo();
    };
} // namespace LinuxSampler

#endif	/* _AUDIOOUTPUTDEVICECOREAUDIO_H */
