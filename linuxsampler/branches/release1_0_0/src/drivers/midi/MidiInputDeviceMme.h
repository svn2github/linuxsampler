/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
 *   Copyright (C) 2005 - 2007 Christian Schoenebeck                       *
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

#ifndef __LS_MIDIINPUTDEVICEMME_H__
#define __LS_MIDIINPUTDEVICEMME_H__

#define MME_MAX_SYSEX_BUF_SIZE 32768

#include "../../common/global_private.h"
#include "MidiInputDevice.h"

#include <windows.h>
#include <mmsystem.h>

namespace LinuxSampler {

    /** MME MIDI input driver
     *
     * Implements MIDI input for the Windows Multimedia Extensions
     * (MME).
     */
    class MidiInputDeviceMme : public MidiInputDevice {
        public:
        
            class ParameterPorts : public DeviceCreationParameterInt {
                public:
                    ParameterPorts();
                    ParameterPorts(String val);
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

         /**
             * MIDI Port implementation for the MME MIDI input driver.
             */
            class MidiInputPortMme : public MidiInputPort {
                public:
                    

                   

                /** MIDI Port Parameter 'Port'
                     *
                     * MME MIDI ports
                     * 
                     */
                    class ParameterPort : public DeviceRuntimeParameterString {
                        public:
                            ParameterPort(MidiInputPortMme* pPort);
                            virtual bool                Fix();
                            virtual String              Description();
                            virtual std::vector<String> PossibilitiesAsString();
                            virtual void                OnSetValue(String s);
                        private:
                            MidiInputPortMme* pPort;

                    };

                    
                protected:
                    

                    MidiInputPortMme(MidiInputDeviceMme* pDevice) throw (MidiInputException);
                    ~MidiInputPortMme();
                    void ConnectToMmeMidiSource(const char* MidiSource);
                    void CloseMmeMidiPort(void);
                    void MmeCallbackDispatcher(HMIDIIN handle, UINT uMsg, DWORD dwParam1, DWORD dwParam2);
                    friend class MidiInputDeviceMme;
                private:
                    MidiInputDeviceMme* pDevice;
                    static void CALLBACK win32_midiin_callback(HMIDIIN handle, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);
                    HMIDIIN MidiInHandle;
                    MIDIHDR midiHdr;
                    bool MidiInOpened;
                    int SysExOffset;
                    char *SysExBuf;
                    char *TmpSysExBuf;
                    bool ExitFlag;
                    bool FirstSysExBlock;
                    bool SysExMsgComplete;
            };

            MidiInputDeviceMme(std::map<String,DeviceCreationParameter*> Parameters, void* pSampler);
            ~MidiInputDeviceMme();

            // derived abstract methods from class 'MidiInputDevice'
            void Listen();
            void StopListen();
            virtual String Driver();
            static String Name();
            static String Description();
            static String Version();

            MidiInputPortMme* CreateMidiPort();
        private:
            friend class MidiInputPortMme;
            friend class MidiInputPortMme::ParameterPort;
    };
}

#endif // __LS_MIDIINPUTDEVICEMME_H__
