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

#ifndef __LSCPSERVER_H_
#define __LSCPSERVER_H_

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <list>

#include "lscp.h"
#include "lscpparser.h"
#include "lscp.h"
#include "lscpevent.h"
#include "../Sampler.h"
#include "../common/Thread.h"
#include "../common/Mutex.h"

/// TCP Port on which the server should listen for connection requests.
#define LSCP_PORT 8888

using namespace LinuxSampler;

// External references to the main scanner and parser functions
extern int yyparse(void* YYPARSE_PARAM);
extern int yylex_init(yyscan_t* scanner);
extern int yylex_destroy(yyscan_t yyscanner);

/**
 * Network server for the LinuxSampler Control Protocol (LSCP).
 */
class LSCPServer : public Thread {
    public:
        LSCPServer(Sampler* pSampler);

        // Methods called by the parser
        String DestroyAudioOutputDevice(uint DeviceIndex);
        String DestroyMidiInputDevice(uint DeviceIndex);
        String LoadInstrument(String Filename, uint uiInstrument, uint uiSamplerChannel, bool bBackground = false);
        String LoadEngine(String EngineName, uint uiSamplerChannel);
        String GetChannels();
        String ListChannels();
        String AddChannel();
        String RemoveChannel(uint uiSamplerChannel);
        String GetAvailableEngines();
        String GetEngineInfo(String EngineName);
        String GetChannelInfo(uint uiSamplerChannel);
        String GetVoiceCount(uint uiSamplerChannel);
        String GetStreamCount(uint uiSamplerChannel);
        String GetBufferFill(fill_response_t ResponseType, uint uiSamplerChannel);
        String GetAvailableAudioOutputDrivers();
        String GetAvailableMidiInputDrivers();
        String GetAudioOutputDriverInfo(String Driver);
        String GetMidiInputDriverInfo(String Driver);
#ifdef __GNUC__
        typedef std::map<String,String> StringMap; // nasty workaround for a GCC bug (see GCC bug #15980, #57)
        String GetAudioOutputDriverParameterInfo(String Driver, String Parameter, std::map<String,String> DependencyList = StringMap());
        String GetMidiInputDriverParameterInfo(String Driver, String Parameter, std::map<String,String> DependencyList = StringMap());
        String CreateAudioOutputDevice(String Driver, std::map<String,String> Parameters = StringMap());
        String CreateMidiInputDevice(String Driver, std::map<String,String> Parameters = StringMap());
#else
        String GetAudioOutputDriverParameterInfo(String Driver, String Parameter, std::map<String,String> DependencyList = std::map<String,String>());
        String GetMidiInputDriverParameterInfo(String Driver, String Parameter, std::map<String,String> DependencyList = std::map<String,String>());
        String CreateAudioOutputDevice(String Driver, std::map<String,String> Parameters = std::map<String,String>());
        String CreateMidiInputDevice(String Driver, std::map<String,String> Parameters = std::map<String,String>());
#endif // __GNUC__
        String GetAudioOutputDeviceCount();
        String GetMidiInputDeviceCount();
        String GetAudioOutputDevices();
        String GetMidiInputDevices();
        String GetAudioOutputDeviceInfo(uint DeviceIndex);
        String GetMidiInputDeviceInfo(uint DeviceIndex);
        String GetMidiInputPortInfo(uint DeviceIndex, uint PortIndex);
        String GetMidiInputPortParameterInfo(uint DeviceId, uint PortId, String ParameterName);
        String GetAudioOutputChannelInfo(uint DeviceId, uint ChannelId);
        String GetAudioOutputChannelParameterInfo(uint DeviceId, uint ChannelId, String ParameterName);
        String SetAudioOutputChannelParameter(uint DeviceId, uint ChannelId, String ParamKey, String ParamVal);
        String SetAudioOutputDeviceParameter(uint DeviceIndex, String ParamKey, String ParamVal);
        String SetMidiInputDeviceParameter(uint DeviceIndex, String ParamKey, String ParamVal);
        String SetMidiInputPortParameter(uint DeviceIndex, uint PortIndex, String ParamKey, String ParamVal);
        String SetAudioOutputChannel(uint ChannelAudioOutputChannel, uint AudioOutputDeviceInputChannel, uint uiSamplerChannel);
        String SetAudioOutputDevice(uint AudioDeviceId, uint SamplerChannel);
        String SetAudioOutputType(String AudioOutputDriver, uint uiSamplerChannel);
        String SetMIDIInputPort(uint MIDIPort, uint uiSamplerChannel);
        String SetMIDIInputChannel(uint MIDIChannel, uint uiSamplerChannel);
        String SetMIDIInputDevice(uint MIDIDeviceId, uint uiSamplerChannel);
        String SetMIDIInputType(String MidiInputDriver, uint uiSamplerChannel);
        String SetMIDIInput(uint MIDIDeviceId, uint MIDIPort, uint MIDIChannel, uint uiSamplerChannel);
        String SetVolume(double Volume, uint uiSamplerChannel);
        String ResetChannel(uint uiSamplerChannel);
        String SubscribeNotification(LSCPEvent::event_t);
        String UnsubscribeNotification(LSCPEvent::event_t);
        void   AnswerClient(String ReturnMessage);

	static int currentSocket;
	static std::map<int,String> bufferedCommands;

	static void SendLSCPNotify( LSCPEvent Event );

    protected:
        int            hSocket;
        sockaddr_in    SocketAddress;
        Sampler*       pSampler;

        int Main(); ///< Implementation of virtual method from class Thread

    private:

        /**
         * Find a created audio output device index.
         */
        int GetAudioOutputDeviceIndex (AudioOutputDevice *pDevice);

        /**
         * Find a created midi input device index.
         */
        int GetMidiInputDeviceIndex (MidiInputDevice *pDevice);

	static std::map<int,String> bufferedNotifies;
	static Mutex NotifyMutex;
	static Mutex NotifyBufferMutex;
	static bool GetLSCPCommand( std::vector<int>::iterator iter );
	static void CloseConnection( std::vector<int>::iterator iter );
	static std::vector<int> hSessions;
	static Mutex SubscriptionMutex;
	static std::map< LSCPEvent::event_t, std::list<int> > eventSubscriptions;
	static fd_set fdSet;
};

/**
 * Instrument loader thread for the LinuxSampler Control Protocol (LSCP).
 */
class LSCPLoadInstrument : public Thread {

    public:
        LSCPLoadInstrument(Engine* pEngine, String Filename, uint uiInstrument);

    protected:
        // Instance variables.
        Engine* pEngine;
        String  Filename;
        uint    uiInstrument;

        // Implementation of virtual method from class Thread.
        int Main();
};

#endif // __LSCPSERVER_H_
