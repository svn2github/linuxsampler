/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2008 Andreas Persson                                    *
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

#ifndef LS_AUDIOOUTPUTDEVICEPLUGIN_H
#define LS_AUDIOOUTPUTDEVICEPLUGIN_H

#include "AudioOutputDevice.h"

namespace LinuxSampler {

    /** Plugin audio output driver
     *
     * Implements audio output when LinuxSampler is running as a
     * plugin.
     *
     * The plugin implementation is given access to the Render
     * function, which should be called to render audio.
     */
    class AudioOutputDevicePlugin : public AudioOutputDevice {
    public:
        AudioOutputDevicePlugin(std::map<String,DeviceCreationParameter*> Parameters);

        /**
         * Audio channel implementation for the plugin audio driver.
         */
        class AudioChannelPlugin : public AudioChannel {
        protected:
            AudioChannelPlugin(uint ChannelNr);

            friend class AudioOutputDevicePlugin;
        };

        /**
         * Device Parameter 'FRAGMENTSIZE'
         *
         * Used to set the audio fragment size / period size.
         */
        class ParameterFragmentSize : public DeviceCreationParameterInt {
        public:
            ParameterFragmentSize();
            ParameterFragmentSize(String s) throw (Exception);
            String Description();
            bool Fix();
            bool Mandatory();
            std::map<String,DeviceCreationParameter*> DependsAsParameters();
            optional<int> DefaultAsInt(std::map<String,String> Parameters);
            optional<int> RangeMinAsInt(std::map<String,String> Parameters);
            optional<int> RangeMaxAsInt(std::map<String,String> Parameters);
            std::vector<int> PossibilitiesAsInt(std::map<String,String> Parameters);
            void OnSetValue(int i) throw (Exception);
            static String Name();
        };

        // derived abstract methods from class 'AudioOutputDevice'
        void Play();
        bool IsPlaying();
        void Stop();
        uint MaxSamplesPerCycle();
        uint SampleRate();
        String Driver();
        AudioChannel* CreateChannel(uint ChannelNr);
        static String Name();
        static String Version();
        static String Description();

        /**
         * This should be called by the plugin implementation to let
         * the engines render audio. The buffers where the data is
         * rendered can be set with Channel(index)->getBuffer().
         *
         * @param Samples - number of sample points to be rendered
         * @returns 0 on success or the last error return code of one
         *          engine
         */
        int Render(uint Samples) { return RenderAudio(Samples); }

    private:
        uint uiSampleRate;
        uint uiMaxSamplesPerCycle;
    };
}

#endif
