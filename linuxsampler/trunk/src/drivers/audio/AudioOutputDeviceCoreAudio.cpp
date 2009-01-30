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

#include "AudioOutputDeviceCoreAudio.h"

#include "../../common/global_private.h"

namespace LinuxSampler {

    void AudioOutputDeviceCoreAudio::HandleOutputBuffer (
        void                 *aqData,
        AudioQueueRef        inAQ,
        AudioQueueBufferRef  inBuffer
    ) {
        AQPlayerState* pAqData = (AQPlayerState*) aqData;
        if (atomic_read(&(pAqData->mIsRunning)) == 0) {
            AudioQueueFlush(pAqData->mQueue);
            AudioQueueStop (pAqData->mQueue, true);
            return;
        }
        uint bufferSize = pAqData->pDevice->uiBufferSize;

        // let all connected engines render 'fragmentSize' sample points
        pAqData->pDevice->RenderAudio(bufferSize);

        int16_t* pDataBuf = (int16_t*)(inBuffer->mAudioData);

        uint uiCoreAudioChannels = pAqData->pDevice->uiCoreAudioChannels;
        // convert from DSP value range (-1.0..+1.0) to 16 bit integer value
        // range (-32768..+32767), check clipping  and copy to Alsa output buffer
        for (int c = 0; c < uiCoreAudioChannels; c++) {
            float* in  = pAqData->pDevice->Channels[c]->Buffer();
            for (int i = 0, o = c; i < bufferSize; i++ , o += uiCoreAudioChannels) {
                float sample_point = in[i] * 32768.0f;
                if (sample_point < -32768.0) sample_point = -32768.0;
                if (sample_point >  32767.0) sample_point =  32767.0;
                pDataBuf[o] = (int16_t) sample_point;
            }
        }

        inBuffer->mAudioDataByteSize = (uiCoreAudioChannels * 2) * bufferSize;

        OSStatus res = AudioQueueEnqueueBuffer(pAqData->mQueue, inBuffer, 0, NULL);
        if(res) std::cerr << "AudioQueueEnqueueBuffer: Error " << res << std::endl;
    }

    AudioOutputDeviceCoreAudio::DeviceInfo* AudioOutputDeviceCoreAudio::pDeviceInfo = NULL;

    AudioOutputDeviceCoreAudio::DeviceInfo* AudioOutputDeviceCoreAudio::GetDeviceInfo() {
        if(pDeviceInfo == NULL) {
            pDeviceInfo = new DeviceInfo;

            pDeviceInfo->uiSamplerate = 44100;
            pDeviceInfo->uiChannelNumber = 2;

            AudioStreamBasicDescription dataFormat;
            SetAudioDataFormat(&dataFormat);
            AudioQueueRef pQueue = NULL;

            OSStatus res = AudioQueueNewOutput (
                &dataFormat, NULL, NULL, NULL, NULL, 0, &pQueue
            );

            if(res) {
                std::cerr << "Failed to retrieve device info: " << res << std::endl;
                return pDeviceInfo;
            }

            UInt32 chns = pDeviceInfo->uiChannelNumber;
            UInt32 size = sizeof(chns);
            res = AudioQueueGetProperty (
                pQueue,
                kAudioQueueDeviceProperty_NumberChannels,
                &chns, &size
            );

            if(res) std::cerr << "Failed to retrieve channel number: " << res << std::endl;
            else pDeviceInfo->uiChannelNumber = chns;

            Float64 sRate = pDeviceInfo->uiSamplerate;
            size = sizeof(sRate);
            res = AudioQueueGetProperty (
                pQueue,
                kAudioQueueDeviceProperty_SampleRate,
                &sRate, &size
            );

            if(res) std::cerr << "Failed to retrieve samplerate: " << res << std::endl;
            else pDeviceInfo->uiSamplerate = (uint)sRate;

            AudioQueueDispose(pQueue, true);
        }

        return pDeviceInfo;
    }

    AudioOutputDeviceCoreAudio::AudioOutputDeviceCoreAudio (
                    std::map<String,DeviceCreationParameter*> Parameters
    ) : AudioOutputDevice(Parameters), Thread(true, true, 1, 0) {

        dmsg(2,("AudioOutputDeviceCoreAudio::AudioOutputDeviceCoreAudio()\n"));
        atomic_set(&pausedNew, 0);
        pausedOld = 0;

        uiCoreAudioChannels = ((DeviceCreationParameterInt*)Parameters["CHANNELS"])->ValueAsInt();
        uint samplerate     = ((DeviceCreationParameterInt*)Parameters["SAMPLERATE"])->ValueAsInt();
        uiBufferNumber     = ((DeviceCreationParameterInt*)Parameters["BUFFERS"])->ValueAsInt();
        uiBufferSize        = ((DeviceCreationParameterInt*)Parameters["BUFFERSIZE"])->ValueAsInt();

        aqPlayerState.mDataFormat.mSampleRate = samplerate;
        aqPlayerState.mDataFormat.mFormatID = kAudioFormatLinearPCM;

        aqPlayerState.mDataFormat.mFormatFlags =
            kAudioFormatFlagIsSignedInteger | kAudioFormatFlagIsPacked;

        aqPlayerState.mDataFormat.mBytesPerPacket = uiCoreAudioChannels * 2;
        aqPlayerState.mDataFormat.mFramesPerPacket = 1;
        aqPlayerState.mDataFormat.mBytesPerFrame = uiCoreAudioChannels * 2;
        aqPlayerState.mDataFormat.mChannelsPerFrame = uiCoreAudioChannels;
        aqPlayerState.mDataFormat.mBitsPerChannel = 16;

        aqPlayerState.mBuffers = new AudioQueueBufferRef[uiBufferNumber];

        aqPlayerState.bufferByteSize =
                MaxSamplesPerCycle() * aqPlayerState.mDataFormat.mBytesPerFrame;

        aqPlayerState.mNumPacketsToRead = MaxSamplesPerCycle();

        aqPlayerState.pDevice = this;
        aqPlayerState.mQueue = NULL;

        uint fragmentSize = MaxSamplesPerCycle();
        // create audio channels for this audio device to which the sampler engines can write to
        for (int i = 0; i < uiCoreAudioChannels; i++) {
            this->Channels.push_back(new AudioChannel(i, fragmentSize));
        }

        StartThread();

        if (!((DeviceCreationParameterBool*)Parameters["ACTIVE"])->ValueAsBool()) {
		Stop();
	}
    }

    AudioOutputDeviceCoreAudio::~AudioOutputDevice() {
        atomic_set(&(aqPlayerState.mIsRunning), 0);
        destroyMutex.Lock();
        AudioQueueDispose(aqPlayerState.mQueue, true);
        destroyMutex.Unlock();
        delete [] aqPlayerState.mBuffers;
    }

    void AudioOutputDeviceCoreAudio::SetAudioDataFormat(AudioStreamBasicDescription* pDataFormat) {
        pDataFormat->mSampleRate = 44100;
        pDataFormat->mFormatID = kAudioFormatLinearPCM;

        pDataFormat->mFormatFlags =
            kAudioFormatFlagIsSignedInteger | kAudioFormatFlagIsPacked;

        pDataFormat->mBytesPerPacket = 4;
        pDataFormat->mFramesPerPacket = 1;
        pDataFormat->mBytesPerFrame = 4;
        pDataFormat->mChannelsPerFrame = 2;
        pDataFormat->mBitsPerChannel = 16;
    }

    String AudioOutputDeviceCoreAudio::Name() {
        return "COREAUDIO";
    }

    String AudioOutputDeviceCoreAudio::Description() {
        return "Apple CoreAudio";
    }

    String AudioOutputDeviceCoreAudio::Version() {
       String s = "$Revision: 1.1 $";
       return s.substr(11, s.size() - 13); // cut dollar signs, spaces and CVS macro keyword
    }

    void AudioOutputDeviceCoreAudio::Play() {
        atomic_set(&pausedNew, 0);
    }

    bool AudioOutputDeviceCoreAudio::IsPlaying() {
        return !atomic_read(&pausedNew);
    }

    void AudioOutputDeviceCoreAudio::Stop() {
        atomic_set(&pausedNew, 1);
    }

    uint AudioOutputDeviceCoreAudio::MaxSamplesPerCycle() {
        return uiBufferSize;
    }

    uint AudioOutputDeviceCoreAudio::SampleRate() {
        return aqPlayerState.mDataFormat.mSampleRate;
    }

    String AudioOutputDeviceCoreAudio::Driver() {
        return Name();
    }

    AudioChannel* AudioOutputDeviceCoreAudio::CreateChannel(uint ChannelNr) {
        // just create a mix channel
        return new AudioChannel(ChannelNr, Channel(ChannelNr % uiCoreAudioChannels));
    }

    /**
     * Entry point for the thread.
     */
    int AudioOutputDeviceCoreAudio::Main() {
        dmsg(2,("CoreAudio thread started\n"));

        bool initialized = aqPlayerState.mQueue != NULL;
        if(!initialized) {
            /*
             * Initializing the audio queue
             * Need to be run from this thread because of CFRunLoopGetCurrent()
             * which returns the CFRunLoop object for the current thread.
             */
            OSStatus res = AudioQueueNewOutput (
                &aqPlayerState.mDataFormat,
                HandleOutputBuffer,
                &aqPlayerState,
                CFRunLoopGetCurrent(),
                kCFRunLoopCommonModes,
                0,
                &aqPlayerState.mQueue
            );

            if(res) {
                String s = String("AudioQueueNewOutput: Error ") + ToString(res);
                throw Exception(s);
            }

            for (int i = 0; i < uiBufferNumber; ++i) {
                OSStatus res = AudioQueueAllocateBuffer (
                    aqPlayerState.mQueue,
                    aqPlayerState.bufferByteSize,
                    &aqPlayerState.mBuffers[i]
                );

                if(res) {
                    String s = String("AudioQueueAllocateBuffer: Error ");
                    throw Exception(s + ToString(res));
                }
            }
        }

        for (int i = 0; i < uiBufferNumber; ++i) {
            HandleOutputBuffer (
                &aqPlayerState,
                aqPlayerState.mQueue,
                aqPlayerState.mBuffers[i]
            );
        }

        Float32 gain = 1.0;

        OSStatus res = AudioQueueSetParameter (
            aqPlayerState.mQueue,
            kAudioQueueParam_Volume,
            gain
        );

        if(res) std::cerr << "AudioQueueSetParameter: Error " << res << std::endl;

        atomic_set(&(aqPlayerState.mIsRunning), 1);

        if(!initialized) {
            res = AudioQueuePrime(aqPlayerState.mQueue, 0, NULL);
            if(res) {
                String s = String("AudioQueuePrime: Error ") + ToString(res);
                throw Exception(s);
            }
        }

        res = AudioQueueStart(aqPlayerState.mQueue, NULL);
        if(res) {
            String s = String("AudioQueueStart: Error ") + ToString(res);
            throw Exception(s);
        }

        destroyMutex.Lock();
        do {
            if(atomic_read(&pausedNew) != pausedOld) {
                pausedOld = atomic_read(&pausedNew);

                if(pausedOld) {
                    res = AudioQueuePause(aqPlayerState.mQueue);
                    if(res) std::cerr << "AudioQueuePause: Error " << res << std::endl;
                } else {
                    res = AudioQueuePrime(aqPlayerState.mQueue, 0, NULL);
                    if(res) std::cerr << "AudioQueuePrime: Error " << res << std::endl;
                    res = AudioQueueStart(aqPlayerState.mQueue, NULL);
                    if(res) std::cerr << "AudioQueueStart: Error " << res << std::endl;
                }
            }
            
            CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0.2, false);
        } while (atomic_read(&(aqPlayerState.mIsRunning)));
        destroyMutex.Unlock();

        dmsg(2,("CoreAudio thread stopped\n"));

        return 0;
    }


// *************** ParameterSampleRate ***************
// *

    AudioOutputDeviceCoreAudio::ParameterSampleRate::ParameterSampleRate() :
                AudioOutputDevice::ParameterSampleRate::ParameterSampleRate() {

    }

    AudioOutputDeviceCoreAudio::ParameterSampleRate::ParameterSampleRate(String s) :
                AudioOutputDevice::ParameterSampleRate::ParameterSampleRate(s) {
        
    }

    optional<int>
    AudioOutputDeviceCoreAudio::ParameterSampleRate::DefaultAsInt(std::map<String,String> Parameters) {
        dmsg(2,("AudioOutputDeviceCoreAudio::ParameterSampleRate::DefaultAsInt()\n"));
        return GetDeviceInfo()->uiSamplerate;
    }


// *************** ParameterChannels ***************
// *

    AudioOutputDeviceCoreAudio::ParameterChannels::ParameterChannels() :
                    AudioOutputDevice::ParameterChannels::ParameterChannels() {
        
    }

    AudioOutputDeviceCoreAudio::ParameterChannels::ParameterChannels(String s) :
                    AudioOutputDevice::ParameterChannels::ParameterChannels(s) {
        
    }

    optional<int>
    AudioOutputDeviceCoreAudio::ParameterChannels::DefaultAsInt(std::map<String,String> Parameters) {
        dmsg(2,("AudioOutputDeviceCoreAudio::ParameterChannels::DefaultAsInt()\n"));
        return GetDeviceInfo()->uiChannelNumber;
    }

// *************** ParameterBuffers ***************
// *

    AudioOutputDeviceCoreAudio::ParameterBuffers::ParameterBuffers() : DeviceCreationParameterInt() {
        InitWithDefault();
    }

    AudioOutputDeviceCoreAudio::ParameterBuffers::ParameterBuffers(String s)
            throw (Exception) : DeviceCreationParameterInt(s) {
    }

    String AudioOutputDeviceCoreAudio::ParameterBuffers::Description() {
        return "Number of audio buffer";
    }

    bool AudioOutputDeviceCoreAudio::ParameterBuffers::Fix() {
        return true;
    }

    bool AudioOutputDeviceCoreAudio::ParameterBuffers::Mandatory() {
        return false;
    }

    std::map<String,DeviceCreationParameter*>
    AudioOutputDeviceCoreAudio::ParameterBuffers::DependsAsParameters() {
        return std::map<String,DeviceCreationParameter*>();
    }

    optional<int>
    AudioOutputDeviceCoreAudio::ParameterBuffers::DefaultAsInt(std::map<String,String> Parameters) {
        return 3;
    }

    optional<int>
    AudioOutputDeviceCoreAudio::ParameterBuffers::RangeMinAsInt(std::map<String,String> Parameters) {
        return 2;
    }

    optional<int>
    AudioOutputDeviceCoreAudio::ParameterBuffers::RangeMaxAsInt(std::map<String,String> Parameters) {
        return 16;
    }

    std::vector<int>
    AudioOutputDeviceCoreAudio::ParameterBuffers::PossibilitiesAsInt(std::map<String,String> Parameters) {
        return std::vector<int>();
    }

    void AudioOutputDeviceCoreAudio::ParameterBuffers::OnSetValue(int i) throw (Exception) {
        // not posssible, as parameter is fix
    }

    String AudioOutputDeviceCoreAudio::ParameterBuffers::Name() {
        return "BUFFERS";
    }

// *************** ParameterBufferSize ***************
// *

    AudioOutputDeviceCoreAudio::ParameterBufferSize::ParameterBufferSize() : DeviceCreationParameterInt() {
        InitWithDefault();
    }

    AudioOutputDeviceCoreAudio::ParameterBufferSize::ParameterBufferSize(String s)
            throw (Exception) : DeviceCreationParameterInt(s) {
    }

    String AudioOutputDeviceCoreAudio::ParameterBufferSize::Description() {
        return "Size of the audio buffer in sample frames";
    }

    bool AudioOutputDeviceCoreAudio::ParameterBufferSize::Fix() {
        return true;
    }

    bool AudioOutputDeviceCoreAudio::ParameterBufferSize::Mandatory() {
        return false;
    }

    std::map<String,DeviceCreationParameter*>
    AudioOutputDeviceCoreAudio::ParameterBufferSize::DependsAsParameters() {
        return std::map<String,DeviceCreationParameter*>();
    }

    optional<int>
    AudioOutputDeviceCoreAudio::ParameterBufferSize::DefaultAsInt(std::map<String,String> Parameters) {
        return 128;
    }

    optional<int>
    AudioOutputDeviceCoreAudio::ParameterBufferSize::RangeMinAsInt(std::map<String,String> Parameters) {
        return 32;
    }

    optional<int>
    AudioOutputDeviceCoreAudio::ParameterBufferSize::RangeMaxAsInt(std::map<String,String> Parameters) {
        return 4096;
    }

    std::vector<int>
    AudioOutputDeviceCoreAudio::ParameterBufferSize::PossibilitiesAsInt(std::map<String,String> Parameters) {
        return std::vector<int>();
    }

    void AudioOutputDeviceCoreAudio::ParameterBufferSize::OnSetValue(int i) throw (Exception) {
        // not posssible, as parameter is fix
    }

    String AudioOutputDeviceCoreAudio::ParameterBufferSize::Name() {
        return "BUFFERSIZE";
    }
} // namespace LinuxSampler
