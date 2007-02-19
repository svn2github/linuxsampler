/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
 *   Copyright (C) 2005 - 2007 Christian Schoenebeck                       *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this library; if not, write to the Free Software           *
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
#include "../common/Condition.h"

#include "../drivers/midi/MidiInstrumentMapper.h"

/// TCP Port on which the server should listen for connection requests.
#define LSCP_ADDR INADDR_ANY
#define LSCP_PORT 8888

/// try up to 3 minutes to bind server socket
#define LSCP_SERVER_BIND_TIMEOUT 180

using namespace LinuxSampler;

// External references to the main scanner and parser functions
extern int yyparse(void* YYPARSE_PARAM);
extern void restart(yyparse_param_t* pparam, int& yychar);

/**
 * Network server for the LinuxSampler Control Protocol (LSCP).
 */
class LSCPServer : public Thread {
    public:
        LSCPServer(Sampler* pSampler, long int addr, short int port);
        virtual ~LSCPServer();
        int WaitUntilInitialized(long TimeoutSeconds = 0L, long TimeoutNanoSeconds = 0L);

        // Methods called by the parser
        String DestroyAudioOutputDevice(uint DeviceIndex);
        String DestroyMidiInputDevice(uint DeviceIndex);
        String LoadInstrument(String Filename, uint uiInstrument, uint uiSamplerChannel, bool bBackground = false);
        String SetEngineType(String EngineName, uint uiSamplerChannel);
        String GetChannels();
        String ListChannels();
        String AddChannel();
        String RemoveChannel(uint uiSamplerChannel);
        String GetAvailableEngines();
        String ListAvailableEngines();
        String GetEngineInfo(String EngineName);
        String GetChannelInfo(uint uiSamplerChannel);
        String GetVoiceCount(uint uiSamplerChannel);
        String GetStreamCount(uint uiSamplerChannel);
        String GetBufferFill(fill_response_t ResponseType, uint uiSamplerChannel);
        String GetAvailableAudioOutputDrivers();
        String ListAvailableAudioOutputDrivers();
        String GetAvailableMidiInputDrivers();
        String ListAvailableMidiInputDrivers();
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
        String SetVolume(double dVolume, uint uiSamplerChannel);
        String SetChannelMute(bool bMute, uint uiSamplerChannel);
        String SetChannelSolo(bool bSolo, uint uiSamplerChannel);
        String AddOrReplaceMIDIInstrumentMapping(uint MidiMapID, uint MidiBank, uint MidiProg, String EngineType, String InstrumentFile, uint InstrumentIndex, float Volume, MidiInstrumentMapper::mode_t LoadMode, String Name, bool bModal);
        String RemoveMIDIInstrumentMapping(uint MidiMapID, uint MidiBank, uint MidiProg);
        String GetMidiInstrumentMappings(uint MidiMapID);
        String GetAllMidiInstrumentMappings();
        String GetMidiInstrumentMapping(uint MidiMapID, uint MidiBank, uint MidiProg);
        String ListMidiInstrumentMappings(uint MidiMapID);
        String ListAllMidiInstrumentMappings();
        String ClearMidiInstrumentMappings(uint MidiMapID);
        String ClearAllMidiInstrumentMappings();
        String AddMidiInstrumentMap(String MapName = "");
        String RemoveMidiInstrumentMap(uint MidiMapID);
        String RemoveAllMidiInstrumentMaps();
        String GetMidiInstrumentMaps();
        String ListMidiInstrumentMaps();
        String GetMidiInstrumentMap(uint MidiMapID);
        String SetMidiInstrumentMapName(uint MidiMapID, String NewName);
        String SetChannelMap(uint uiSamplerChannel, int MidiMapID);
        String CreateFxSend(uint uiSamplerChannel, uint MidiCtrl, String Name = "");
        String DestroyFxSend(uint uiSamplerChannel, uint FxSendID);
        String GetFxSends(uint uiSamplerChannel);
        String ListFxSends(uint uiSamplerChannel);
        String GetFxSendInfo(uint uiSamplerChannel, uint FxSendID);
        String SetFxSendAudioOutputChannel(uint uiSamplerChannel, uint FxSendID, uint FxSendChannel, uint DeviceChannel);
        String SetFxSendMidiController(uint uiSamplerChannel, uint FxSendID, uint MidiController);
        String SetFxSendLevel(uint uiSamplerChannel, uint FxSendID, double dLevel);
        String ResetChannel(uint uiSamplerChannel);
        String ResetSampler();
        String GetServerInfo();
        String GetTotalVoiceCount();
        String GetTotalVoiceCountMax();
        String GetGlobalVolume();
        String SetGlobalVolume(double dVolume);
        String SubscribeNotification(LSCPEvent::event_t);
        String UnsubscribeNotification(LSCPEvent::event_t);
	String QueryDatabase(String query);
        String SetEcho(yyparse_param_t* pSession, double boolean_value);
        void   AnswerClient(String ReturnMessage);

	static int currentSocket;
	static std::map<int,String> bufferedCommands;

	static void SendLSCPNotify( LSCPEvent Event );
	static int EventSubscribers( std::list<LSCPEvent::event_t> events );
	static void LockRTNotify( void ) { RTNotifyMutex.Lock(); }
	static void UnlockRTNotify( void ) { RTNotifyMutex.Unlock(); }

    protected:
        int            hSocket;
        sockaddr_in    SocketAddress;
        Sampler*       pSampler;
        Condition      Initialized;

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

        bool HasSoloChannel();
        void MuteNonSoloChannels();
        void UnmuteChannels();

	static std::map<int,String> bufferedNotifies;
	static Mutex NotifyMutex;
	static Mutex NotifyBufferMutex;
	static bool GetLSCPCommand( std::vector<yyparse_param_t>::iterator iter );
	static void CloseConnection( std::vector<yyparse_param_t>::iterator iter );
	static std::vector<yyparse_param_t> Sessions;
	static Mutex SubscriptionMutex;
	static std::map< LSCPEvent::event_t, std::list<int> > eventSubscriptions;
	static fd_set fdSet;

	//Protect main thread that generates real time notify messages
	//like voice count, stream count and buffer fill
	//from LSCP server removing engines and channels from underneath
	static Mutex RTNotifyMutex;
};

#endif // __LSCPSERVER_H_
