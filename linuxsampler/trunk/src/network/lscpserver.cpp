/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
 *   Copyright (C) 2005, 2006 Christian Schoenebeck                        *
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

#include "lscpserver.h"
#include "lscpresultset.h"
#include "lscpevent.h"
//#include "../common/global.h"

#include <fcntl.h>

#if HAVE_SQLITE3
# include "sqlite3.h"
#endif

#include "../engines/EngineFactory.h"
#include "../engines/EngineChannelFactory.h"
#include "../drivers/audio/AudioOutputDeviceFactory.h"
#include "../drivers/midi/MidiInputDeviceFactory.h"

/**
 * Below are a few static members of the LSCPServer class.
 * The big assumption here is that LSCPServer is going to remain a singleton.
 * These members are used to support client connections.
 * Class handles multiple connections at the same time using select() and non-blocking recv()
 * Commands are processed by a single LSCPServer thread.
 * Notifications are delivered either by the thread that originated them
 * or (if the resultset is currently in progress) by the LSCPServer thread
 * after the resultset was sent out.
 * This makes sure that resultsets can not be interrupted by notifications.
 * This also makes sure that the thread sending notification is not blocked
 * by the LSCPServer thread.
 */
fd_set LSCPServer::fdSet;
int LSCPServer::currentSocket = -1;
std::vector<yyparse_param_t> LSCPServer::Sessions = std::vector<yyparse_param_t>();
std::map<int,String> LSCPServer::bufferedNotifies = std::map<int,String>();
std::map<int,String> LSCPServer::bufferedCommands = std::map<int,String>();
std::map< LSCPEvent::event_t, std::list<int> > LSCPServer::eventSubscriptions = std::map< LSCPEvent::event_t, std::list<int> >();
Mutex LSCPServer::NotifyMutex = Mutex();
Mutex LSCPServer::NotifyBufferMutex = Mutex();
Mutex LSCPServer::SubscriptionMutex = Mutex();
Mutex LSCPServer::RTNotifyMutex = Mutex();

LSCPServer::LSCPServer(Sampler* pSampler, long int addr, short int port) : Thread(true, false, 0, -4) {
    SocketAddress.sin_family      = AF_INET;
    SocketAddress.sin_addr.s_addr = addr;
    SocketAddress.sin_port        = port;
    this->pSampler = pSampler;
    LSCPEvent::RegisterEvent(LSCPEvent::event_channel_count, "CHANNEL_COUNT");
    LSCPEvent::RegisterEvent(LSCPEvent::event_voice_count, "VOICE_COUNT");
    LSCPEvent::RegisterEvent(LSCPEvent::event_stream_count, "STREAM_COUNT");
    LSCPEvent::RegisterEvent(LSCPEvent::event_buffer_fill, "BUFFER_FILL");
    LSCPEvent::RegisterEvent(LSCPEvent::event_channel_info, "CHANNEL_INFO");
    LSCPEvent::RegisterEvent(LSCPEvent::event_misc, "MISCELLANEOUS");
    LSCPEvent::RegisterEvent(LSCPEvent::event_total_voice_count, "TOTAL_VOICE_COUNT");
    hSocket = -1;
}

LSCPServer::~LSCPServer() {
    if (hSocket >= 0) close(hSocket);
}

/**
 * Blocks the calling thread until the LSCP Server is initialized and
 * accepting socket connections, if the server is already initialized then
 * this method will return immediately.
 * @param TimeoutSeconds     - optional: max. wait time in seconds
 *                             (default: 0s)
 * @param TimeoutNanoSeconds - optional: max wait time in nano seconds
 *                             (default: 0ns)
 * @returns  0 on success, a value less than 0 if timeout exceeded
 */
int LSCPServer::WaitUntilInitialized(long TimeoutSeconds, long TimeoutNanoSeconds) {
    return Initialized.WaitAndUnlockIf(false, TimeoutSeconds, TimeoutNanoSeconds);
}

int LSCPServer::Main() {
    hSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (hSocket < 0) {
        std::cerr << "LSCPServer: Could not create server socket." << std::endl;
        //return -1;
        exit(EXIT_FAILURE);
    }

    if (bind(hSocket, (sockaddr*) &SocketAddress, sizeof(sockaddr_in)) < 0) {
        std::cerr << "LSCPServer: Could not bind server socket, retrying for " << ToString(LSCP_SERVER_BIND_TIMEOUT) << " seconds...";
        for (int trial = 0; true; trial++) { // retry for LSCP_SERVER_BIND_TIMEOUT seconds
            if (bind(hSocket, (sockaddr*) &SocketAddress, sizeof(sockaddr_in)) < 0) {
                if (trial > LSCP_SERVER_BIND_TIMEOUT) {
                    std::cerr << "gave up!" << std::endl;
                    close(hSocket);
                    //return -1;
                    exit(EXIT_FAILURE);
                }
                else sleep(1); // sleep 1s
            }
            else break; // success
        }
    }

    listen(hSocket, 1);
    Initialized.Set(true);

    // now wait for client connections and handle their requests
    sockaddr_in client;
    int length = sizeof(client);
    FD_ZERO(&fdSet);
    FD_SET(hSocket, &fdSet);
    int maxSessions = hSocket;

    timeval timeout;

    while (true) {
        // check if some engine channel's parameter / status changed, if so notify the respective LSCP event subscribers
        {
            std::set<EngineChannel*> engineChannels = EngineChannelFactory::EngineChannelInstances();
            std::set<EngineChannel*>::iterator itEngineChannel = engineChannels.begin();
            std::set<EngineChannel*>::iterator itEnd           = engineChannels.end();
            for (; itEngineChannel != itEnd; ++itEngineChannel) {
                if ((*itEngineChannel)->StatusChanged()) {
                    SendLSCPNotify(LSCPEvent(LSCPEvent::event_channel_info, (*itEngineChannel)->iSamplerChannelIndex));
                }
            }
        }

	//Now let's deliver late notifies (if any)
	NotifyBufferMutex.Lock();
	for (std::map<int,String>::iterator iterNotify = bufferedNotifies.begin(); iterNotify != bufferedNotifies.end(); iterNotify++) {
#ifdef MSG_NOSIGNAL
		send(iterNotify->first, iterNotify->second.c_str(), iterNotify->second.size(), MSG_NOSIGNAL);
#else
		send(iterNotify->first, iterNotify->second.c_str(), iterNotify->second.size(), 0);
#endif
	}
        bufferedNotifies.clear();
	NotifyBufferMutex.Unlock();

        fd_set selectSet = fdSet;
        timeout.tv_sec  = 0;
        timeout.tv_usec = 100000;

        int retval = select(maxSessions+1, &selectSet, NULL, NULL, &timeout);

	if (retval == 0)
		continue; //Nothing try again
	if (retval == -1) {
		std::cerr << "LSCPServer: Socket select error." << std::endl;
		close(hSocket);
		exit(EXIT_FAILURE);
	}

	//Accept new connections now (if any)
	if (FD_ISSET(hSocket, &selectSet)) {
		int socket = accept(hSocket, (sockaddr*) &client, (socklen_t*) &length);
		if (socket < 0) {
			std::cerr << "LSCPServer: Client connection failed." << std::endl;
			exit(EXIT_FAILURE);
		}

		if (fcntl(socket, F_SETFL, O_NONBLOCK)) {
			std::cerr << "LSCPServer: F_SETFL O_NONBLOCK failed." << std::endl;
			exit(EXIT_FAILURE);
		}

                // Parser initialization
                yyparse_param_t yyparse_param;
                yyparse_param.pServer  = this;
                yyparse_param.hSession = socket;

		Sessions.push_back(yyparse_param);
		FD_SET(socket, &fdSet);
		if (socket > maxSessions)
			maxSessions = socket;
		dmsg(1,("LSCPServer: Client connection established on socket:%d.\n", socket));
		LSCPServer::SendLSCPNotify(LSCPEvent(LSCPEvent::event_misc, "Client connection established on socket", socket));
		continue; //Maybe this was the only selected socket, better select again
	}

	//Something was selected and it was not the hSocket, so it must be some command(s) coming.
	for (std::vector<yyparse_param_t>::iterator iter = Sessions.begin(); iter != Sessions.end(); iter++) {
		if (FD_ISSET((*iter).hSession, &selectSet)) {	//Was it this socket?
			if (GetLSCPCommand(iter)) {	//Have we read the entire command?
				dmsg(3,("LSCPServer: Got command on socket %d, calling parser.\n", currentSocket));
                                int dummy; // just a temporary hack to fulfill the restart() function prototype
                                restart(NULL, dummy); // restart the 'scanner'
				currentSocket = (*iter).hSession;  //a hack
				dmsg(2,("LSCPServer: [%s]\n",bufferedCommands[currentSocket].c_str()));
                                if ((*iter).bVerbose) { // if echo mode enabled
                                    AnswerClient(bufferedCommands[currentSocket]);
                                }
				int result = yyparse(&(*iter));
				currentSocket = -1;	//continuation of a hack
				dmsg(3,("LSCPServer: Done parsing on socket %d.\n", currentSocket));
				if (result == LSCP_QUIT) { //Was it a quit command by any chance?
					CloseConnection(iter);
				}
			}
			//socket may have been closed, iter may be invalid, get out of the loop for now.
			//we'll be back if there is data.
			break;
		}
	}
    }
}

void LSCPServer::CloseConnection( std::vector<yyparse_param_t>::iterator iter ) {
	int socket = (*iter).hSession;
	dmsg(1,("LSCPServer: Client connection terminated on socket:%d.\n",socket));
	LSCPServer::SendLSCPNotify(LSCPEvent(LSCPEvent::event_misc, "Client connection terminated on socket", socket));
	Sessions.erase(iter);
	FD_CLR(socket,  &fdSet);
	SubscriptionMutex.Lock(); //Must unsubscribe this socket from all events (if any)
	for (std::map< LSCPEvent::event_t, std::list<int> >::iterator iter = eventSubscriptions.begin(); iter != eventSubscriptions.end(); iter++) {
		iter->second.remove(socket);
	}
	SubscriptionMutex.Unlock();
	NotifyMutex.Lock();
	bufferedCommands.erase(socket);
	bufferedNotifies.erase(socket);
	close(socket);
	NotifyMutex.Unlock();
}

int LSCPServer::EventSubscribers( std::list<LSCPEvent::event_t> events ) {
	int subs = 0;
	SubscriptionMutex.Lock();
	for( std::list<LSCPEvent::event_t>::iterator iter = events.begin();
			iter != events.end(); iter++)
	{
		subs += eventSubscriptions.count(*iter);
	}
	SubscriptionMutex.Unlock();
	return subs;
}

void LSCPServer::SendLSCPNotify( LSCPEvent event ) {
	SubscriptionMutex.Lock();
	if (eventSubscriptions.count(event.GetType()) == 0) {
		SubscriptionMutex.Unlock();	//Nobody is subscribed to this event
		return;
	}
	std::list<int>::iterator iter = eventSubscriptions[event.GetType()].begin();
	std::list<int>::iterator end = eventSubscriptions[event.GetType()].end();
	String notify = event.Produce();

	while (true) {
		if (NotifyMutex.Trylock()) {
			for(;iter != end; iter++)
#ifdef MSG_NOSIGNAL
				send(*iter, notify.c_str(), notify.size(), MSG_NOSIGNAL);
#else
				send(*iter, notify.c_str(), notify.size(), 0);
#endif
			NotifyMutex.Unlock();
			break;
		} else {
			if (NotifyBufferMutex.Trylock()) {
				for(;iter != end; iter++)
					bufferedNotifies[*iter] += notify;
				NotifyBufferMutex.Unlock();
				break;
			}
		}
	}
	SubscriptionMutex.Unlock();
}

extern int GetLSCPCommand( void *buf, int max_size ) {
	String command = LSCPServer::bufferedCommands[LSCPServer::currentSocket];
	if (command.size() == 0) { 		//Parser wants input but we have nothing.
		strcpy((char*) buf, "\n"); 	//So give it an empty command
		return 1;			//to keep it happy.
	}

	if (max_size < command.size()) {
		std::cerr << "getLSCPCommand: Flex buffer too small, ignoring the command." << std::endl;
		return 0;	//This will never happen
	}

	strcpy((char*) buf, command.c_str());
	LSCPServer::bufferedCommands.erase(LSCPServer::currentSocket);
	return command.size();
}

/**
 * Will be called to try to read the command from the socket
 * If command is read, it will return true. Otherwise false is returned.
 * In any case the received portion (complete or incomplete) is saved into bufferedCommand map.
 */
bool LSCPServer::GetLSCPCommand( std::vector<yyparse_param_t>::iterator iter ) {
	int socket = (*iter).hSession;
	char c;
	int i = 0;
	while (true) {
		int result = recv(socket, (void *)&c, 1, 0); //Read one character at a time for now
		if (result == 0) { //socket was selected, so 0 here means client has closed the connection
			CloseConnection(iter);
			break;
		}
		if (result == 1) {
			if (c == '\r')
				continue; //Ignore CR
			if (c == '\n') {
				LSCPServer::SendLSCPNotify(LSCPEvent(LSCPEvent::event_misc, "Received \'" + bufferedCommands[socket] + "\' on socket", socket));
				bufferedCommands[socket] += "\r\n";
				return true; //Complete command was read
			}
			bufferedCommands[socket] += c;
		}
		if (result == -1) {
			if (errno == EAGAIN) //Would block, try again later.
				return false;
			switch(errno) {
				case EBADF:
					dmsg(2,("LSCPScanner: The argument s is an invalid descriptor.\n"));
					break;
				case ECONNREFUSED:
					dmsg(2,("LSCPScanner: A remote host refused to allow the network connection (typically because it is not running the requested service).\n"));
					break;
				case ENOTCONN:
					dmsg(2,("LSCPScanner: The socket is associated with a connection-oriented protocol and has not been connected (see connect(2) and accept(2)).\n"));
					break;
				case ENOTSOCK:
					dmsg(2,("LSCPScanner: The argument s does not refer to a socket.\n"));
					break;
				case EAGAIN:
					dmsg(2,("LSCPScanner: The socket is marked non-blocking and the receive operation would block, or a receive timeout had been set and the timeout expired before data was received.\n"));
					break;
				case EINTR:
					dmsg(2,("LSCPScanner: The receive was interrupted by delivery of a signal before any data were available.\n"));
					break;
				case EFAULT:
					dmsg(2,("LSCPScanner: The receive buffer pointer(s) point outside the process's address space.\n"));
					break;
				case EINVAL:
					dmsg(2,("LSCPScanner: Invalid argument passed.\n"));
					break;
				case ENOMEM:
					dmsg(2,("LSCPScanner: Could not allocate memory for recvmsg.\n"));
					break;
				default:
					dmsg(2,("LSCPScanner: Unknown recv() error.\n"));
					break;
			}
			CloseConnection(iter);
			break;
		}
	}
	return false;
}

/**
 * Will be called by the parser whenever it wants to send an answer to the
 * client / frontend.
 *
 * @param ReturnMessage - message that will be send to the client
 */
void LSCPServer::AnswerClient(String ReturnMessage) {
    dmsg(2,("LSCPServer::AnswerClient(ReturnMessage=%s)", ReturnMessage.c_str()));
    if (currentSocket != -1) {
	    NotifyMutex.Lock();
#ifdef MSG_NOSIGNAL
	    send(currentSocket, ReturnMessage.c_str(), ReturnMessage.size(), MSG_NOSIGNAL);
#else
	    send(currentSocket, ReturnMessage.c_str(), ReturnMessage.size(), 0);
#endif
	    NotifyMutex.Unlock();
    }
}

/**
 * Find a created audio output device index.
 */
int LSCPServer::GetAudioOutputDeviceIndex ( AudioOutputDevice *pDevice )
{
    // Search for the created device to get its index
    std::map<uint, AudioOutputDevice*> devices = pSampler->GetAudioOutputDevices();
    std::map<uint, AudioOutputDevice*>::iterator iter = devices.begin();
    for (; iter != devices.end(); iter++) {
        if (iter->second == pDevice)
            return iter->first;
    }
    // Not found.
    return -1;
}

/**
 * Find a created midi input device index.
 */
int LSCPServer::GetMidiInputDeviceIndex ( MidiInputDevice *pDevice )
{
    // Search for the created device to get its index
    std::map<uint, MidiInputDevice*> devices = pSampler->GetMidiInputDevices();
    std::map<uint, MidiInputDevice*>::iterator iter = devices.begin();
    for (; iter != devices.end(); iter++) {
        if (iter->second == pDevice)
            return iter->first;
    }
    // Not found.
    return -1;
}

String LSCPServer::CreateAudioOutputDevice(String Driver, std::map<String,String> Parameters) {
    dmsg(2,("LSCPServer: CreateAudioOutputDevice(Driver=%s)\n", Driver.c_str()));
    LSCPResultSet result;
    try {
        AudioOutputDevice* pDevice = pSampler->CreateAudioOutputDevice(Driver, Parameters);
        // search for the created device to get its index
        int index = GetAudioOutputDeviceIndex(pDevice);
        if (index == -1) throw Exception("Internal error: could not find created audio output device.");
        result = index; // success
    }
    catch (Exception e) {
        result.Error(e);
    }
    return result.Produce();
}

String LSCPServer::CreateMidiInputDevice(String Driver, std::map<String,String> Parameters) {
    dmsg(2,("LSCPServer: CreateMidiInputDevice(Driver=%s)\n", Driver.c_str()));
    LSCPResultSet result;
    try {
        MidiInputDevice* pDevice = pSampler->CreateMidiInputDevice(Driver, Parameters);
        // search for the created device to get its index
        int index = GetMidiInputDeviceIndex(pDevice);
        if (index == -1) throw Exception("Internal error: could not find created midi input device.");
        result = index; // success
    }
    catch (Exception e) {
        result.Error(e);
    }
    return result.Produce();
}

String LSCPServer::DestroyAudioOutputDevice(uint DeviceIndex) {
    dmsg(2,("LSCPServer: DestroyAudioOutputDevice(DeviceIndex=%d)\n", DeviceIndex));
    LSCPResultSet result;
    try {
        std::map<uint, AudioOutputDevice*> devices = pSampler->GetAudioOutputDevices();
        if (!devices.count(DeviceIndex)) throw Exception("There is no audio output device with index " + ToString(DeviceIndex) + ".");
        AudioOutputDevice* pDevice = devices[DeviceIndex];
        pSampler->DestroyAudioOutputDevice(pDevice);
    }
    catch (Exception e) {
        result.Error(e);
    }
    return result.Produce();
}

String LSCPServer::DestroyMidiInputDevice(uint DeviceIndex) {
    dmsg(2,("LSCPServer: DestroyMidiInputDevice(DeviceIndex=%d)\n", DeviceIndex));
    LSCPResultSet result;
    try {
        std::map<uint, MidiInputDevice*> devices = pSampler->GetMidiInputDevices();
        if (!devices.count(DeviceIndex)) throw Exception("There is no audio output device with index " + ToString(DeviceIndex) + ".");
        MidiInputDevice* pDevice = devices[DeviceIndex];
        pSampler->DestroyMidiInputDevice(pDevice);
    }
    catch (Exception e) {
        result.Error(e);
    }
    return result.Produce();
}

/**
 * Will be called by the parser to load an instrument.
 */
String LSCPServer::LoadInstrument(String Filename, uint uiInstrument, uint uiSamplerChannel, bool bBackground) {
    dmsg(2,("LSCPServer: LoadInstrument(Filename=%s,Instrument=%d,SamplerChannel=%d)\n", Filename.c_str(), uiInstrument, uiSamplerChannel));
    LSCPResultSet result;
    try {
        SamplerChannel* pSamplerChannel = pSampler->GetSamplerChannel(uiSamplerChannel);
        if (!pSamplerChannel) throw Exception("Invalid sampler channel number " + ToString(uiSamplerChannel));
        EngineChannel* pEngineChannel = pSamplerChannel->GetEngineChannel();
        if (!pEngineChannel) throw Exception("No engine type assigned to sampler channel yet");
        if (!pSamplerChannel->GetAudioOutputDevice())
            throw Exception("No audio output device connected to sampler channel");
        if (bBackground) {
            InstrumentManager::instrument_id_t id;
            id.FileName = Filename;
            id.Index    = uiInstrument;
            InstrumentManager::LoadInstrumentInBackground(id, pEngineChannel);
        }
        else {
            // tell the engine channel which instrument to load
            pEngineChannel->PrepareLoadInstrument(Filename.c_str(), uiInstrument);
            // actually start to load the instrument (blocks until completed)
            pEngineChannel->LoadInstrument();
        }
    }
    catch (Exception e) {
         result.Error(e);
    }
    return result.Produce();
}

/**
 * Will be called by the parser to assign a sampler engine type to a
 * sampler channel.
 */
String LSCPServer::SetEngineType(String EngineName, uint uiSamplerChannel) {
    dmsg(2,("LSCPServer: SetEngineType(EngineName=%s,uiSamplerChannel=%d)\n", EngineName.c_str(), uiSamplerChannel));
    LSCPResultSet result;
    try {
        SamplerChannel* pSamplerChannel = pSampler->GetSamplerChannel(uiSamplerChannel);
        if (!pSamplerChannel) throw Exception("Invalid sampler channel number " + ToString(uiSamplerChannel));
	LockRTNotify();
        pSamplerChannel->SetEngineType(EngineName);
        if(HasSoloChannel()) pSamplerChannel->GetEngineChannel()->SetMute(-1);
	UnlockRTNotify();
    }
    catch (Exception e) {
         result.Error(e);
    }
    return result.Produce();
}

/**
 * Will be called by the parser to get the amount of sampler channels.
 */
String LSCPServer::GetChannels() {
    dmsg(2,("LSCPServer: GetChannels()\n"));
    LSCPResultSet result;
    result.Add(pSampler->SamplerChannels());
    return result.Produce();
}

/**
 * Will be called by the parser to get the list of sampler channels.
 */
String LSCPServer::ListChannels() {
    dmsg(2,("LSCPServer: ListChannels()\n"));
    String list;
    std::map<uint,SamplerChannel*> channels = pSampler->GetSamplerChannels();
    std::map<uint,SamplerChannel*>::iterator iter = channels.begin();
    for (; iter != channels.end(); iter++) {
        if (list != "") list += ",";
        list += ToString(iter->first);
    }
    LSCPResultSet result;
    result.Add(list);
    return result.Produce();
}

/**
 * Will be called by the parser to add a sampler channel.
 */
String LSCPServer::AddChannel() {
    dmsg(2,("LSCPServer: AddChannel()\n"));
    LockRTNotify();
    SamplerChannel* pSamplerChannel = pSampler->AddSamplerChannel();
    UnlockRTNotify();
    LSCPResultSet result(pSamplerChannel->Index());
    return result.Produce();
}

/**
 * Will be called by the parser to remove a sampler channel.
 */
String LSCPServer::RemoveChannel(uint uiSamplerChannel) {
    dmsg(2,("LSCPServer: RemoveChannel(SamplerChannel=%d)\n", uiSamplerChannel));
    LSCPResultSet result;
    LockRTNotify();
    pSampler->RemoveSamplerChannel(uiSamplerChannel);
    UnlockRTNotify();
    return result.Produce();
}

/**
 * Will be called by the parser to get the amount of all available engines.
 */
String LSCPServer::GetAvailableEngines() {
    dmsg(2,("LSCPServer: GetAvailableEngines()\n"));
    LSCPResultSet result;
    try {
        int n = EngineFactory::AvailableEngineTypes().size();
        result.Add(n);
    }
    catch (Exception e) {
        result.Error(e);
    }
    return result.Produce();
}

/**
 * Will be called by the parser to get a list of all available engines.
 */
String LSCPServer::ListAvailableEngines() {
    dmsg(2,("LSCPServer: ListAvailableEngines()\n"));
    LSCPResultSet result;
    try {
        String s = EngineFactory::AvailableEngineTypesAsString();
        result.Add(s);
    }
    catch (Exception e) {
        result.Error(e);
    }
    return result.Produce();
}

/**
 * Will be called by the parser to get descriptions for a particular
 * sampler engine.
 */
String LSCPServer::GetEngineInfo(String EngineName) {
    dmsg(2,("LSCPServer: GetEngineInfo(EngineName=%s)\n", EngineName.c_str()));
    LSCPResultSet result;
    LockRTNotify();
    try {
        Engine* pEngine = EngineFactory::Create(EngineName);
        result.Add("DESCRIPTION", pEngine->Description());
        result.Add("VERSION",     pEngine->Version());
        EngineFactory::Destroy(pEngine);
    }
    catch (Exception e) {
         result.Error(e);
    }
    UnlockRTNotify();
    return result.Produce();
}

/**
 * Will be called by the parser to get informations about a particular
 * sampler channel.
 */
String LSCPServer::GetChannelInfo(uint uiSamplerChannel) {
    dmsg(2,("LSCPServer: GetChannelInfo(SamplerChannel=%d)\n", uiSamplerChannel));
    LSCPResultSet result;
    try {
        SamplerChannel* pSamplerChannel = pSampler->GetSamplerChannel(uiSamplerChannel);
        if (!pSamplerChannel) throw Exception("Invalid sampler channel number " + ToString(uiSamplerChannel));
        EngineChannel* pEngineChannel = pSamplerChannel->GetEngineChannel();

	//Defaults values
	String EngineName = "NONE";
        float Volume = 0.0f;
	String InstrumentFileName = "NONE";
	String InstrumentName = "NONE";
	int InstrumentIndex = -1;
	int InstrumentStatus = -1;
        int AudioOutputChannels = 0;
        String AudioRouting;
        int Mute = 0;
        bool Solo = false;

        if (pEngineChannel) {
            EngineName          = pEngineChannel->EngineName();
            AudioOutputChannels = pEngineChannel->Channels();
            Volume              = pEngineChannel->Volume();
            InstrumentStatus    = pEngineChannel->InstrumentStatus();
            InstrumentIndex     = pEngineChannel->InstrumentIndex();
            if (InstrumentIndex != -1) {
                InstrumentFileName = pEngineChannel->InstrumentFileName();
                InstrumentName     = pEngineChannel->InstrumentName();
            }
            for (int chan = 0; chan < pEngineChannel->Channels(); chan++) {
                if (AudioRouting != "") AudioRouting += ",";
                AudioRouting += ToString(pEngineChannel->OutputChannel(chan));
            }
            Mute = pEngineChannel->GetMute();
            Solo = pEngineChannel->GetSolo();
	}

        result.Add("ENGINE_NAME", EngineName);
        result.Add("VOLUME", Volume);

	//Some not-so-hardcoded stuff to make GUI look good
        result.Add("AUDIO_OUTPUT_DEVICE", GetAudioOutputDeviceIndex(pSamplerChannel->GetAudioOutputDevice()));
        result.Add("AUDIO_OUTPUT_CHANNELS", AudioOutputChannels);
        result.Add("AUDIO_OUTPUT_ROUTING", AudioRouting);

        result.Add("MIDI_INPUT_DEVICE", GetMidiInputDeviceIndex(pSamplerChannel->GetMidiInputDevice()));
        result.Add("MIDI_INPUT_PORT", pSamplerChannel->GetMidiInputPort());
        if (pSamplerChannel->GetMidiInputChannel() == midi_chan_all) result.Add("MIDI_INPUT_CHANNEL", "ALL");
        else result.Add("MIDI_INPUT_CHANNEL", pSamplerChannel->GetMidiInputChannel());

        result.Add("INSTRUMENT_FILE", InstrumentFileName);
        result.Add("INSTRUMENT_NR", InstrumentIndex);
        result.Add("INSTRUMENT_NAME", InstrumentName);
        result.Add("INSTRUMENT_STATUS", InstrumentStatus);
        result.Add("MUTE", Mute == -1 ? "MUTED_BY_SOLO" : (Mute ? "true" : "false"));
        result.Add("SOLO", Solo);
    }
    catch (Exception e) {
         result.Error(e);
    }
    return result.Produce();
}

/**
 * Will be called by the parser to get the amount of active voices on a
 * particular sampler channel.
 */
String LSCPServer::GetVoiceCount(uint uiSamplerChannel) {
    dmsg(2,("LSCPServer: GetVoiceCount(SamplerChannel=%d)\n", uiSamplerChannel));
    LSCPResultSet result;
    try {
        SamplerChannel* pSamplerChannel = pSampler->GetSamplerChannel(uiSamplerChannel);
        if (!pSamplerChannel) throw Exception("Invalid sampler channel number " + ToString(uiSamplerChannel));
        EngineChannel* pEngineChannel = pSamplerChannel->GetEngineChannel();
        if (!pEngineChannel) throw Exception("No engine loaded on sampler channel");
        if (!pEngineChannel->GetEngine()) throw Exception("No audio output device connected to sampler channel");
	result.Add(pEngineChannel->GetEngine()->VoiceCount());
    }
    catch (Exception e) {
         result.Error(e);
    }
    return result.Produce();
}

/**
 * Will be called by the parser to get the amount of active disk streams on a
 * particular sampler channel.
 */
String LSCPServer::GetStreamCount(uint uiSamplerChannel) {
    dmsg(2,("LSCPServer: GetStreamCount(SamplerChannel=%d)\n", uiSamplerChannel));
    LSCPResultSet result;
    try {
        SamplerChannel* pSamplerChannel = pSampler->GetSamplerChannel(uiSamplerChannel);
        if (!pSamplerChannel) throw Exception("Invalid sampler channel number " + ToString(uiSamplerChannel));
        EngineChannel* pEngineChannel = pSamplerChannel->GetEngineChannel();
        if (!pEngineChannel) throw Exception("No engine type assigned to sampler channel");
        if (!pEngineChannel->GetEngine()) throw Exception("No audio output device connected to sampler channel");
        result.Add(pEngineChannel->GetEngine()->DiskStreamCount());
    }
    catch (Exception e) {
         result.Error(e);
    }
    return result.Produce();
}

/**
 * Will be called by the parser to get the buffer fill states of all disk
 * streams on a particular sampler channel.
 */
String LSCPServer::GetBufferFill(fill_response_t ResponseType, uint uiSamplerChannel) {
    dmsg(2,("LSCPServer: GetBufferFill(ResponseType=%d, SamplerChannel=%d)\n", ResponseType, uiSamplerChannel));
    LSCPResultSet result;
    try {
        SamplerChannel* pSamplerChannel = pSampler->GetSamplerChannel(uiSamplerChannel);
        if (!pSamplerChannel) throw Exception("Invalid sampler channel number " + ToString(uiSamplerChannel));
        EngineChannel* pEngineChannel = pSamplerChannel->GetEngineChannel();
        if (!pEngineChannel) throw Exception("No engine type assigned to sampler channel");
        if (!pEngineChannel->GetEngine()) throw Exception("No audio output device connected to sampler channel");
        if (!pEngineChannel->GetEngine()->DiskStreamSupported()) result.Add("NA");
        else {
            switch (ResponseType) {
                case fill_response_bytes:
                    result.Add(pEngineChannel->GetEngine()->DiskStreamBufferFillBytes());
                    break;
                case fill_response_percentage:
                    result.Add(pEngineChannel->GetEngine()->DiskStreamBufferFillPercentage());
                    break;
                default:
                    throw Exception("Unknown fill response type");
            }
	}
    }
    catch (Exception e) {
         result.Error(e);
    }
    return result.Produce();
}

String LSCPServer::GetAvailableAudioOutputDrivers() {
    dmsg(2,("LSCPServer: GetAvailableAudioOutputDrivers()\n"));
    LSCPResultSet result;
    try {
        int n = AudioOutputDeviceFactory::AvailableDrivers().size();
        result.Add(n);
    }
    catch (Exception e) {
        result.Error(e);
    }
    return result.Produce();
}

String LSCPServer::ListAvailableAudioOutputDrivers() {
    dmsg(2,("LSCPServer: ListAvailableAudioOutputDrivers()\n"));
    LSCPResultSet result;
    try {
        String s = AudioOutputDeviceFactory::AvailableDriversAsString();
        result.Add(s);
    }
    catch (Exception e) {
        result.Error(e);
    }
    return result.Produce();
}

String LSCPServer::GetAvailableMidiInputDrivers() {
    dmsg(2,("LSCPServer: GetAvailableMidiInputDrivers()\n"));
    LSCPResultSet result;
    try {
        int n = MidiInputDeviceFactory::AvailableDrivers().size();
        result.Add(n);
    }
    catch (Exception e) {
        result.Error(e);
    }
    return result.Produce();
}

String LSCPServer::ListAvailableMidiInputDrivers() {
    dmsg(2,("LSCPServer: ListAvailableMidiInputDrivers()\n"));
    LSCPResultSet result;
    try {
        String s = MidiInputDeviceFactory::AvailableDriversAsString();
        result.Add(s);
    }
    catch (Exception e) {
        result.Error(e);
    }
    return result.Produce();
}

String LSCPServer::GetMidiInputDriverInfo(String Driver) {
    dmsg(2,("LSCPServer: GetMidiInputDriverInfo(Driver=%s)\n",Driver.c_str()));
    LSCPResultSet result;
    try {
        result.Add("DESCRIPTION", MidiInputDeviceFactory::GetDriverDescription(Driver));
        result.Add("VERSION",     MidiInputDeviceFactory::GetDriverVersion(Driver));

        std::map<String,DeviceCreationParameter*> parameters = MidiInputDeviceFactory::GetAvailableDriverParameters(Driver);
        if (parameters.size()) { // if there are parameters defined for this driver
            String s;
            std::map<String,DeviceCreationParameter*>::iterator iter = parameters.begin();
            for (;iter != parameters.end(); iter++) {
                if (s != "") s += ",";
                s += iter->first;
            }
            result.Add("PARAMETERS", s);
        }
    }
    catch (Exception e) {
        result.Error(e);
    }
    return result.Produce();
}

String LSCPServer::GetAudioOutputDriverInfo(String Driver) {
    dmsg(2,("LSCPServer: GetAudioOutputDriverInfo(Driver=%s)\n",Driver.c_str()));
    LSCPResultSet result;
    try {
        result.Add("DESCRIPTION", AudioOutputDeviceFactory::GetDriverDescription(Driver));
        result.Add("VERSION",     AudioOutputDeviceFactory::GetDriverVersion(Driver));

        std::map<String,DeviceCreationParameter*> parameters = AudioOutputDeviceFactory::GetAvailableDriverParameters(Driver);
        if (parameters.size()) { // if there are parameters defined for this driver
            String s;
            std::map<String,DeviceCreationParameter*>::iterator iter = parameters.begin();
            for (;iter != parameters.end(); iter++) {
                if (s != "") s += ",";
                s += iter->first;
            }
            result.Add("PARAMETERS", s);
        }
    }
    catch (Exception e) {
        result.Error(e);
    }
    return result.Produce();
}

String LSCPServer::GetMidiInputDriverParameterInfo(String Driver, String Parameter, std::map<String,String> DependencyList) {
    dmsg(2,("LSCPServer: GetMidiInputDriverParameterInfo(Driver=%s,Parameter=%s,DependencyListSize=%d)\n",Driver.c_str(),Parameter.c_str(),DependencyList.size()));
    LSCPResultSet result;
    try {
        DeviceCreationParameter* pParameter = MidiInputDeviceFactory::GetDriverParameter(Driver, Parameter);
        result.Add("TYPE",         pParameter->Type());
        result.Add("DESCRIPTION",  pParameter->Description());
        result.Add("MANDATORY",    pParameter->Mandatory());
        result.Add("FIX",          pParameter->Fix());
        result.Add("MULTIPLICITY", pParameter->Multiplicity());
        optional<String> oDepends       = pParameter->Depends();
        optional<String> oDefault       = pParameter->Default(DependencyList);
        optional<String> oRangeMin      = pParameter->RangeMin(DependencyList);
        optional<String> oRangeMax      = pParameter->RangeMax(DependencyList);
        optional<String> oPossibilities = pParameter->Possibilities(DependencyList);
        if (oDepends)       result.Add("DEPENDS",       *oDepends);
        if (oDefault)       result.Add("DEFAULT",       *oDefault);
        if (oRangeMin)      result.Add("RANGE_MIN",     *oRangeMin);
        if (oRangeMax)      result.Add("RANGE_MAX",     *oRangeMax);
        if (oPossibilities) result.Add("POSSIBILITIES", *oPossibilities);
    }
    catch (Exception e) {
        result.Error(e);
    }
    return result.Produce();
}

String LSCPServer::GetAudioOutputDriverParameterInfo(String Driver, String Parameter, std::map<String,String> DependencyList) {
    dmsg(2,("LSCPServer: GetAudioOutputDriverParameterInfo(Driver=%s,Parameter=%s,DependencyListSize=%d)\n",Driver.c_str(),Parameter.c_str(),DependencyList.size()));
    LSCPResultSet result;
    try {
        DeviceCreationParameter* pParameter = AudioOutputDeviceFactory::GetDriverParameter(Driver, Parameter);
        result.Add("TYPE",         pParameter->Type());
        result.Add("DESCRIPTION",  pParameter->Description());
        result.Add("MANDATORY",    pParameter->Mandatory());
        result.Add("FIX",          pParameter->Fix());
        result.Add("MULTIPLICITY", pParameter->Multiplicity());
        optional<String> oDepends       = pParameter->Depends();
        optional<String> oDefault       = pParameter->Default(DependencyList);
        optional<String> oRangeMin      = pParameter->RangeMin(DependencyList);
        optional<String> oRangeMax      = pParameter->RangeMax(DependencyList);
        optional<String> oPossibilities = pParameter->Possibilities(DependencyList);
        if (oDepends)       result.Add("DEPENDS",       *oDepends);
        if (oDefault)       result.Add("DEFAULT",       *oDefault);
        if (oRangeMin)      result.Add("RANGE_MIN",     *oRangeMin);
        if (oRangeMax)      result.Add("RANGE_MAX",     *oRangeMax);
        if (oPossibilities) result.Add("POSSIBILITIES", *oPossibilities);
    }
    catch (Exception e) {
        result.Error(e);
    }
    return result.Produce();
}

String LSCPServer::GetAudioOutputDeviceCount() {
    dmsg(2,("LSCPServer: GetAudioOutputDeviceCount()\n"));
    LSCPResultSet result;
    try {
        uint count = pSampler->AudioOutputDevices();
        result.Add(count); // success
    }
    catch (Exception e) {
        result.Error(e);
    }
    return result.Produce();
}

String LSCPServer::GetMidiInputDeviceCount() {
    dmsg(2,("LSCPServer: GetMidiInputDeviceCount()\n"));
    LSCPResultSet result;
    try {
        uint count = pSampler->MidiInputDevices();
        result.Add(count); // success
    }
    catch (Exception e) {
        result.Error(e);
    }
    return result.Produce();
}

String LSCPServer::GetAudioOutputDevices() {
    dmsg(2,("LSCPServer: GetAudioOutputDevices()\n"));
    LSCPResultSet result;
    try {
        String s;
        std::map<uint, AudioOutputDevice*> devices = pSampler->GetAudioOutputDevices();
        std::map<uint, AudioOutputDevice*>::iterator iter = devices.begin();
        for (; iter != devices.end(); iter++) {
            if (s != "") s += ",";
            s += ToString(iter->first);
        }
        result.Add(s);
    }
    catch (Exception e) {
        result.Error(e);
    }
    return result.Produce();
}

String LSCPServer::GetMidiInputDevices() {
    dmsg(2,("LSCPServer: GetMidiInputDevices()\n"));
    LSCPResultSet result;
    try {
        String s;
        std::map<uint, MidiInputDevice*> devices = pSampler->GetMidiInputDevices();
        std::map<uint, MidiInputDevice*>::iterator iter = devices.begin();
        for (; iter != devices.end(); iter++) {
            if (s != "") s += ",";
            s += ToString(iter->first);
        }
        result.Add(s);
    }
    catch (Exception e) {
        result.Error(e);
    }
    return result.Produce();
}

String LSCPServer::GetAudioOutputDeviceInfo(uint DeviceIndex) {
    dmsg(2,("LSCPServer: GetAudioOutputDeviceInfo(DeviceIndex=%d)\n",DeviceIndex));
    LSCPResultSet result;
    try {
        std::map<uint,AudioOutputDevice*> devices = pSampler->GetAudioOutputDevices();
        if (!devices.count(DeviceIndex)) throw Exception("There is no audio output device with index " + ToString(DeviceIndex) + ".");
        AudioOutputDevice* pDevice = devices[DeviceIndex];
        result.Add("DRIVER", pDevice->Driver());
        std::map<String,DeviceCreationParameter*> parameters = pDevice->DeviceParameters();
        std::map<String,DeviceCreationParameter*>::iterator iter = parameters.begin();
        for (; iter != parameters.end(); iter++) {
            result.Add(iter->first, iter->second->Value());
        }
    }
    catch (Exception e) {
        result.Error(e);
    }
    return result.Produce();
}

String LSCPServer::GetMidiInputDeviceInfo(uint DeviceIndex) {
    dmsg(2,("LSCPServer: GetMidiInputDeviceInfo(DeviceIndex=%d)\n",DeviceIndex));
    LSCPResultSet result;
    try {
        std::map<uint,MidiInputDevice*> devices = pSampler->GetMidiInputDevices();
        if (!devices.count(DeviceIndex)) throw Exception("There is no MIDI input device with index " + ToString(DeviceIndex) + ".");
        MidiInputDevice* pDevice = devices[DeviceIndex];
        result.Add("DRIVER", pDevice->Driver());
        std::map<String,DeviceCreationParameter*> parameters = pDevice->DeviceParameters();
        std::map<String,DeviceCreationParameter*>::iterator iter = parameters.begin();
        for (; iter != parameters.end(); iter++) {
            result.Add(iter->first, iter->second->Value());
        }
    }
    catch (Exception e) {
        result.Error(e);
    }
    return result.Produce();
}
String LSCPServer::GetMidiInputPortInfo(uint DeviceIndex, uint PortIndex) {
    dmsg(2,("LSCPServer: GetMidiInputPortInfo(DeviceIndex=%d, PortIndex=%d)\n",DeviceIndex, PortIndex));
    LSCPResultSet result;
    try {
        // get MIDI input device
        std::map<uint,MidiInputDevice*> devices = pSampler->GetMidiInputDevices();
        if (!devices.count(DeviceIndex)) throw Exception("There is no MIDI input device with index " + ToString(DeviceIndex) + ".");
        MidiInputDevice* pDevice = devices[DeviceIndex];

        // get MIDI port
        MidiInputPort* pMidiInputPort = pDevice->GetPort(PortIndex);
        if (!pMidiInputPort) throw Exception("There is no MIDI input port with index " + ToString(PortIndex) + ".");

        // return the values of all MIDI port parameters
        std::map<String,DeviceRuntimeParameter*> parameters = pMidiInputPort->PortParameters();
        std::map<String,DeviceRuntimeParameter*>::iterator iter = parameters.begin();
        for (; iter != parameters.end(); iter++) {
            result.Add(iter->first, iter->second->Value());
        }
    }
    catch (Exception e) {
        result.Error(e);
    }
    return result.Produce();
}

String LSCPServer::GetAudioOutputChannelInfo(uint DeviceId, uint ChannelId) {
    dmsg(2,("LSCPServer: GetAudioOutputChannelInfo(DeviceId=%d,ChannelId)\n",DeviceId,ChannelId));
    LSCPResultSet result;
    try {
        // get audio output device
        std::map<uint,AudioOutputDevice*> devices = pSampler->GetAudioOutputDevices();
        if (!devices.count(DeviceId)) throw Exception("There is no audio output device with index " + ToString(DeviceId) + ".");
        AudioOutputDevice* pDevice = devices[DeviceId];

        // get audio channel
        AudioChannel* pChannel = pDevice->Channel(ChannelId);
        if (!pChannel) throw Exception("Audio output device does not have audio channel " + ToString(ChannelId) + ".");

        // return the values of all audio channel parameters
        std::map<String,DeviceRuntimeParameter*> parameters = pChannel->ChannelParameters();
        std::map<String,DeviceRuntimeParameter*>::iterator iter = parameters.begin();
        for (; iter != parameters.end(); iter++) {
            result.Add(iter->first, iter->second->Value());
        }
    }
    catch (Exception e) {
        result.Error(e);
    }
    return result.Produce();
}

String LSCPServer::GetMidiInputPortParameterInfo(uint DeviceId, uint PortId, String ParameterName) {
    dmsg(2,("LSCPServer: GetMidiInputPortParameterInfo(DeviceId=%d,PortId=%d,ParameterName=%s)\n",DeviceId,PortId,ParameterName.c_str()));
    LSCPResultSet result;
    try {
        // get MIDI input device
        std::map<uint,MidiInputDevice*> devices = pSampler->GetMidiInputDevices();
        if (!devices.count(DeviceId)) throw Exception("There is no midi input device with index " + ToString(DeviceId) + ".");
        MidiInputDevice* pDevice = devices[DeviceId];

        // get midi port
        MidiInputPort* pPort = pDevice->GetPort(PortId);
        if (!pPort) throw Exception("Midi input device does not have port " + ToString(PortId) + ".");

        // get desired port parameter
        std::map<String,DeviceRuntimeParameter*> parameters = pPort->PortParameters();
        if (!parameters.count(ParameterName)) throw Exception("Midi port does not provide a parameter '" + ParameterName + "'.");
        DeviceRuntimeParameter* pParameter = parameters[ParameterName];

        // return all fields of this audio channel parameter
        result.Add("TYPE",         pParameter->Type());
        result.Add("DESCRIPTION",  pParameter->Description());
        result.Add("FIX",          pParameter->Fix());
        result.Add("MULTIPLICITY", pParameter->Multiplicity());
        if (pParameter->RangeMin())      result.Add("RANGE_MIN",     *pParameter->RangeMin());
        if (pParameter->RangeMax())      result.Add("RANGE_MAX",     *pParameter->RangeMax());
        if (pParameter->Possibilities()) result.Add("POSSIBILITIES", *pParameter->Possibilities());
    }
    catch (Exception e) {
        result.Error(e);
    }
    return result.Produce();
}

String LSCPServer::GetAudioOutputChannelParameterInfo(uint DeviceId, uint ChannelId, String ParameterName) {
    dmsg(2,("LSCPServer: GetAudioOutputChannelParameterInfo(DeviceId=%d,ChannelId=%d,ParameterName=%s)\n",DeviceId,ChannelId,ParameterName.c_str()));
    LSCPResultSet result;
    try {
        // get audio output device
        std::map<uint,AudioOutputDevice*> devices = pSampler->GetAudioOutputDevices();
        if (!devices.count(DeviceId)) throw Exception("There is no audio output device with index " + ToString(DeviceId) + ".");
        AudioOutputDevice* pDevice = devices[DeviceId];

        // get audio channel
        AudioChannel* pChannel = pDevice->Channel(ChannelId);
        if (!pChannel) throw Exception("Audio output device does not have audio channel " + ToString(ChannelId) + ".");

        // get desired audio channel parameter
        std::map<String,DeviceRuntimeParameter*> parameters = pChannel->ChannelParameters();
        if (!parameters.count(ParameterName)) throw Exception("Audio channel does not provide a parameter '" + ParameterName + "'.");
        DeviceRuntimeParameter* pParameter = parameters[ParameterName];

        // return all fields of this audio channel parameter
        result.Add("TYPE",         pParameter->Type());
        result.Add("DESCRIPTION",  pParameter->Description());
        result.Add("FIX",          pParameter->Fix());
        result.Add("MULTIPLICITY", pParameter->Multiplicity());
        if (pParameter->RangeMin())      result.Add("RANGE_MIN",     *pParameter->RangeMin());
        if (pParameter->RangeMax())      result.Add("RANGE_MAX",     *pParameter->RangeMax());
        if (pParameter->Possibilities()) result.Add("POSSIBILITIES", *pParameter->Possibilities());
    }
    catch (Exception e) {
        result.Error(e);
    }
    return result.Produce();
}

String LSCPServer::SetAudioOutputChannelParameter(uint DeviceId, uint ChannelId, String ParamKey, String ParamVal) {
    dmsg(2,("LSCPServer: SetAudioOutputChannelParameter(DeviceId=%d,ChannelId=%d,ParamKey=%s,ParamVal=%s)\n",DeviceId,ChannelId,ParamKey.c_str(),ParamVal.c_str()));
    LSCPResultSet result;
    try {
        // get audio output device
        std::map<uint,AudioOutputDevice*> devices = pSampler->GetAudioOutputDevices();
        if (!devices.count(DeviceId)) throw Exception("There is no audio output device with index " + ToString(DeviceId) + ".");
        AudioOutputDevice* pDevice = devices[DeviceId];

        // get audio channel
        AudioChannel* pChannel = pDevice->Channel(ChannelId);
        if (!pChannel) throw Exception("Audio output device does not have audio channel " + ToString(ChannelId) + ".");

        // get desired audio channel parameter
        std::map<String,DeviceRuntimeParameter*> parameters = pChannel->ChannelParameters();
        if (!parameters.count(ParamKey)) throw Exception("Audio channel does not provide a parameter '" + ParamKey + "'.");
        DeviceRuntimeParameter* pParameter = parameters[ParamKey];

        // set new channel parameter value
        pParameter->SetValue(ParamVal);
    }
    catch (Exception e) {
        result.Error(e);
    }
    return result.Produce();
}

String LSCPServer::SetAudioOutputDeviceParameter(uint DeviceIndex, String ParamKey, String ParamVal) {
    dmsg(2,("LSCPServer: SetAudioOutputDeviceParameter(DeviceIndex=%d,ParamKey=%s,ParamVal=%s)\n",DeviceIndex,ParamKey.c_str(),ParamVal.c_str()));
    LSCPResultSet result;
    try {
        std::map<uint,AudioOutputDevice*> devices = pSampler->GetAudioOutputDevices();
        if (!devices.count(DeviceIndex)) throw Exception("There is no audio output device with index " + ToString(DeviceIndex) + ".");
        AudioOutputDevice* pDevice = devices[DeviceIndex];
        std::map<String,DeviceCreationParameter*> parameters = pDevice->DeviceParameters();
        if (!parameters.count(ParamKey)) throw Exception("Audio output device " + ToString(DeviceIndex) + " does not have a device parameter '" + ParamKey + "'");
        parameters[ParamKey]->SetValue(ParamVal);
    }
    catch (Exception e) {
        result.Error(e);
    }
    return result.Produce();
}

String LSCPServer::SetMidiInputDeviceParameter(uint DeviceIndex, String ParamKey, String ParamVal) {
    dmsg(2,("LSCPServer: SetMidiOutputDeviceParameter(DeviceIndex=%d,ParamKey=%s,ParamVal=%s)\n",DeviceIndex,ParamKey.c_str(),ParamVal.c_str()));
    LSCPResultSet result;
    try {
        std::map<uint,MidiInputDevice*> devices = pSampler->GetMidiInputDevices();
        if (!devices.count(DeviceIndex)) throw Exception("There is no MIDI input device with index " + ToString(DeviceIndex) + ".");
        MidiInputDevice* pDevice = devices[DeviceIndex];
        std::map<String,DeviceCreationParameter*> parameters = pDevice->DeviceParameters();
        if (!parameters.count(ParamKey)) throw Exception("MIDI input device " + ToString(DeviceIndex) + " does not have a device parameter '" + ParamKey + "'");
        parameters[ParamKey]->SetValue(ParamVal);
    }
    catch (Exception e) {
        result.Error(e);
    }
    return result.Produce();
}

String LSCPServer::SetMidiInputPortParameter(uint DeviceIndex, uint PortIndex, String ParamKey, String ParamVal) {
    dmsg(2,("LSCPServer: SetMidiOutputDeviceParameter(DeviceIndex=%d,ParamKey=%s,ParamVal=%s)\n",DeviceIndex,ParamKey.c_str(),ParamVal.c_str()));
    LSCPResultSet result;
    try {
        // get MIDI input device
        std::map<uint,MidiInputDevice*> devices = pSampler->GetMidiInputDevices();
        if (!devices.count(DeviceIndex)) throw Exception("There is no MIDI input device with index " + ToString(DeviceIndex) + ".");
        MidiInputDevice* pDevice = devices[DeviceIndex];

        // get MIDI port
        MidiInputPort* pMidiInputPort = pDevice->GetPort(PortIndex);
        if (!pMidiInputPort) throw Exception("There is no MIDI input port with index " + ToString(PortIndex) + ".");

        // set port parameter value
        std::map<String,DeviceRuntimeParameter*> parameters = pMidiInputPort->PortParameters();
        if (!parameters.count(ParamKey)) throw Exception("MIDI input device " + ToString(PortIndex) + " does not have a parameter '" + ParamKey + "'");
        parameters[ParamKey]->SetValue(ParamVal);
    }
    catch (Exception e) {
        result.Error(e);
    }
    return result.Produce();
}

/**
 * Will be called by the parser to change the audio output channel for
 * playback on a particular sampler channel.
 */
String LSCPServer::SetAudioOutputChannel(uint ChannelAudioOutputChannel, uint AudioOutputDeviceInputChannel, uint uiSamplerChannel) {
    dmsg(2,("LSCPServer: SetAudioOutputChannel(ChannelAudioOutputChannel=%d, AudioOutputDeviceInputChannel=%d, SamplerChannel=%d)\n",ChannelAudioOutputChannel,AudioOutputDeviceInputChannel,uiSamplerChannel));
    LSCPResultSet result;
    try {
        SamplerChannel* pSamplerChannel = pSampler->GetSamplerChannel(uiSamplerChannel);
        if (!pSamplerChannel) throw Exception("Invalid sampler channel number " + ToString(uiSamplerChannel));
        EngineChannel* pEngineChannel = pSamplerChannel->GetEngineChannel();
        if (!pEngineChannel) throw Exception("No engine type yet assigned to sampler channel " + ToString(uiSamplerChannel));
        if (!pSamplerChannel->GetAudioOutputDevice()) throw Exception("No audio output device connected to sampler channel " + ToString(uiSamplerChannel));
        pEngineChannel->SetOutputChannel(ChannelAudioOutputChannel, AudioOutputDeviceInputChannel);
    }
    catch (Exception e) {
         result.Error(e);
    }
    return result.Produce();
}

String LSCPServer::SetAudioOutputDevice(uint AudioDeviceId, uint uiSamplerChannel) {
    dmsg(2,("LSCPServer: SetAudiotOutputDevice(AudioDeviceId=%d, SamplerChannel=%d)\n",AudioDeviceId,uiSamplerChannel));
    LSCPResultSet result;
    LockRTNotify();
    try {
        SamplerChannel* pSamplerChannel = pSampler->GetSamplerChannel(uiSamplerChannel);
        if (!pSamplerChannel) throw Exception("Invalid sampler channel number " + ToString(uiSamplerChannel));
        std::map<uint, AudioOutputDevice*> devices = pSampler->GetAudioOutputDevices();
        if (!devices.count(AudioDeviceId)) throw Exception("There is no audio output device with index " + ToString(AudioDeviceId));
        AudioOutputDevice* pDevice = devices[AudioDeviceId];
        pSamplerChannel->SetAudioOutputDevice(pDevice);
    }
    catch (Exception e) {
         result.Error(e);
    }
    UnlockRTNotify();
    return result.Produce();
}

String LSCPServer::SetAudioOutputType(String AudioOutputDriver, uint uiSamplerChannel) {
    dmsg(2,("LSCPServer: SetAudioOutputType(String AudioOutputDriver=%s, SamplerChannel=%d)\n",AudioOutputDriver.c_str(),uiSamplerChannel));
    LSCPResultSet result;
    LockRTNotify();
    try {
        SamplerChannel* pSamplerChannel = pSampler->GetSamplerChannel(uiSamplerChannel);
        if (!pSamplerChannel) throw Exception("Invalid sampler channel number " + ToString(uiSamplerChannel));
        // Driver type name aliasing...
        if (AudioOutputDriver == "Alsa") AudioOutputDriver = "ALSA";
        if (AudioOutputDriver == "Jack") AudioOutputDriver = "JACK";
        // Check if there's one audio output device already created
        // for the intended audio driver type (AudioOutputDriver)...
        AudioOutputDevice *pDevice = NULL;
        std::map<uint, AudioOutputDevice*> devices = pSampler->GetAudioOutputDevices();
        std::map<uint, AudioOutputDevice*>::iterator iter = devices.begin();
        for (; iter != devices.end(); iter++) {
            if ((iter->second)->Driver() == AudioOutputDriver) {
                pDevice = iter->second;
                break;
            }
        }
        // If it doesn't exist, create a new one with default parameters...
        if (pDevice == NULL) {
            std::map<String,String> params;
            pDevice = pSampler->CreateAudioOutputDevice(AudioOutputDriver, params);
        }
        // Must have a device...
        if (pDevice == NULL)
            throw Exception("Internal error: could not create audio output device.");
        // Set it as the current channel device...
        pSamplerChannel->SetAudioOutputDevice(pDevice);
    }
    catch (Exception e) {
         result.Error(e);
    }
    UnlockRTNotify();
    return result.Produce();
}

String LSCPServer::SetMIDIInputPort(uint MIDIPort, uint uiSamplerChannel) {
    dmsg(2,("LSCPServer: SetMIDIInputPort(MIDIPort=%d, SamplerChannel=%d)\n",MIDIPort,uiSamplerChannel));
    LSCPResultSet result;
    try {
        SamplerChannel* pSamplerChannel = pSampler->GetSamplerChannel(uiSamplerChannel);
        if (!pSamplerChannel) throw Exception("Invalid sampler channel number " + ToString(uiSamplerChannel));
        pSamplerChannel->SetMidiInputPort(MIDIPort);
    }
    catch (Exception e) {
         result.Error(e);
    }
    return result.Produce();
}

String LSCPServer::SetMIDIInputChannel(uint MIDIChannel, uint uiSamplerChannel) {
    dmsg(2,("LSCPServer: SetMIDIInputChannel(MIDIChannel=%d, SamplerChannel=%d)\n",MIDIChannel,uiSamplerChannel));
    LSCPResultSet result;
    try {
        SamplerChannel* pSamplerChannel = pSampler->GetSamplerChannel(uiSamplerChannel);
        if (!pSamplerChannel) throw Exception("Invalid sampler channel number " + ToString(uiSamplerChannel));
        pSamplerChannel->SetMidiInputChannel((midi_chan_t) MIDIChannel);
    }
    catch (Exception e) {
         result.Error(e);
    }
    return result.Produce();
}

String LSCPServer::SetMIDIInputDevice(uint MIDIDeviceId, uint uiSamplerChannel) {
    dmsg(2,("LSCPServer: SetMIDIInputDevice(MIDIDeviceId=%d, SamplerChannel=%d)\n",MIDIDeviceId,uiSamplerChannel));
    LSCPResultSet result;
    try {
        SamplerChannel* pSamplerChannel = pSampler->GetSamplerChannel(uiSamplerChannel);
        if (!pSamplerChannel) throw Exception("Invalid sampler channel number " + ToString(uiSamplerChannel));
        std::map<uint, MidiInputDevice*> devices = pSampler->GetMidiInputDevices();
        if (!devices.count(MIDIDeviceId)) throw Exception("There is no MIDI input device with index " + ToString(MIDIDeviceId));
        MidiInputDevice* pDevice = devices[MIDIDeviceId];
        pSamplerChannel->SetMidiInputDevice(pDevice);
    }
    catch (Exception e) {
         result.Error(e);
    }
    return result.Produce();
}

String LSCPServer::SetMIDIInputType(String MidiInputDriver, uint uiSamplerChannel) {
    dmsg(2,("LSCPServer: SetMIDIInputType(String MidiInputDriver=%s, SamplerChannel=%d)\n",MidiInputDriver.c_str(),uiSamplerChannel));
    LSCPResultSet result;
    try {
        SamplerChannel* pSamplerChannel = pSampler->GetSamplerChannel(uiSamplerChannel);
        if (!pSamplerChannel) throw Exception("Invalid sampler channel number " + ToString(uiSamplerChannel));
        // Driver type name aliasing...
        if (MidiInputDriver == "Alsa") MidiInputDriver = "ALSA";
        // Check if there's one MIDI input device already created
        // for the intended MIDI driver type (MidiInputDriver)...
        MidiInputDevice *pDevice = NULL;
        std::map<uint, MidiInputDevice*> devices = pSampler->GetMidiInputDevices();
        std::map<uint, MidiInputDevice*>::iterator iter = devices.begin();
        for (; iter != devices.end(); iter++) {
            if ((iter->second)->Driver() == MidiInputDriver) {
                pDevice = iter->second;
                break;
            }
        }
        // If it doesn't exist, create a new one with default parameters...
        if (pDevice == NULL) {
            std::map<String,String> params;
            pDevice = pSampler->CreateMidiInputDevice(MidiInputDriver, params);
            // Make it with at least one initial port.
            std::map<String,DeviceCreationParameter*> parameters = pDevice->DeviceParameters();
            parameters["PORTS"]->SetValue("1");
        }
        // Must have a device...
        if (pDevice == NULL)
            throw Exception("Internal error: could not create MIDI input device.");
        // Set it as the current channel device...
        pSamplerChannel->SetMidiInputDevice(pDevice);
    }
    catch (Exception e) {
         result.Error(e);
    }
    return result.Produce();
}

/**
 * Will be called by the parser to change the MIDI input device, port and channel on which
 * engine of a particular sampler channel should listen to.
 */
String LSCPServer::SetMIDIInput(uint MIDIDeviceId, uint MIDIPort, uint MIDIChannel, uint uiSamplerChannel) {
    dmsg(2,("LSCPServer: SetMIDIInput(MIDIDeviceId=%d, MIDIPort=%d, MIDIChannel=%d, SamplerChannel=%d)\n", MIDIDeviceId, MIDIPort, MIDIChannel, uiSamplerChannel));
    LSCPResultSet result;
    try {
        SamplerChannel* pSamplerChannel = pSampler->GetSamplerChannel(uiSamplerChannel);
        if (!pSamplerChannel) throw Exception("Invalid sampler channel number " + ToString(uiSamplerChannel));
        std::map<uint, MidiInputDevice*> devices =  pSampler->GetMidiInputDevices();
        if (!devices.count(MIDIDeviceId)) throw Exception("There is no MIDI input device with index " + ToString(MIDIDeviceId));
        MidiInputDevice* pDevice = devices[MIDIDeviceId];
        pSamplerChannel->SetMidiInput(pDevice, MIDIPort, (midi_chan_t) MIDIChannel);
    }
    catch (Exception e) {
         result.Error(e);
    }
    return result.Produce();
}

/**
 * Will be called by the parser to change the global volume factor on a
 * particular sampler channel.
 */
String LSCPServer::SetVolume(double dVolume, uint uiSamplerChannel) {
    dmsg(2,("LSCPServer: SetVolume(Volume=%f, SamplerChannel=%d)\n", dVolume, uiSamplerChannel));
    LSCPResultSet result;
    try {
        SamplerChannel* pSamplerChannel = pSampler->GetSamplerChannel(uiSamplerChannel);
        if (!pSamplerChannel) throw Exception("Invalid sampler channel number " + ToString(uiSamplerChannel));
        EngineChannel* pEngineChannel = pSamplerChannel->GetEngineChannel();
        if (!pEngineChannel) throw Exception("No engine type assigned to sampler channel");
        pEngineChannel->Volume(dVolume);
    }
    catch (Exception e) {
         result.Error(e);
    }
    return result.Produce();
}

/**
 * Will be called by the parser to mute/unmute particular sampler channel.
 */
String LSCPServer::SetChannelMute(bool bMute, uint uiSamplerChannel) {
    dmsg(2,("LSCPServer: SetChannelMute(bMute=%d,uiSamplerChannel=%d)\n",bMute,uiSamplerChannel));
    LSCPResultSet result;
    try {
        SamplerChannel* pSamplerChannel = pSampler->GetSamplerChannel(uiSamplerChannel);
        if (!pSamplerChannel) throw Exception("Invalid sampler channel number " + ToString(uiSamplerChannel));

        EngineChannel* pEngineChannel = pSamplerChannel->GetEngineChannel();
        if (!pEngineChannel) throw Exception("No engine type assigned to sampler channel");

        if(!bMute) pEngineChannel->SetMute((HasSoloChannel() && !pEngineChannel->GetSolo()) ? -1 : 0);
        else pEngineChannel->SetMute(1);
    } catch (Exception e) {
        result.Error(e);
    }
    return result.Produce();
}

/**
 * Will be called by the parser to solo particular sampler channel.
 */
String LSCPServer::SetChannelSolo(bool bSolo, uint uiSamplerChannel) {
    dmsg(2,("LSCPServer: SetChannelSolo(bSolo=%d,uiSamplerChannel=%d)\n",bSolo,uiSamplerChannel));
    LSCPResultSet result;
    try {
        SamplerChannel* pSamplerChannel = pSampler->GetSamplerChannel(uiSamplerChannel);
        if (!pSamplerChannel) throw Exception("Invalid sampler channel number " + ToString(uiSamplerChannel));

        EngineChannel* pEngineChannel = pSamplerChannel->GetEngineChannel();
        if (!pEngineChannel) throw Exception("No engine type assigned to sampler channel");

        bool oldSolo = pEngineChannel->GetSolo();
        bool hadSoloChannel = HasSoloChannel();
        
        pEngineChannel->SetSolo(bSolo);
        
        if(!oldSolo && bSolo) {
            if(pEngineChannel->GetMute() == -1) pEngineChannel->SetMute(0);
            if(!hadSoloChannel) MuteNonSoloChannels();
        }
        
        if(oldSolo && !bSolo) {
            if(!HasSoloChannel()) UnmuteChannels();
            else if(!pEngineChannel->GetMute()) pEngineChannel->SetMute(-1);
        }
    } catch (Exception e) {
        result.Error(e);
    }
    return result.Produce();
}

/**
 * Determines whether there is at least one solo channel in the channel list.
 *
 * @returns true if there is at least one solo channel in the channel list,
 * false otherwise.
 */
bool LSCPServer::HasSoloChannel() {
    std::map<uint,SamplerChannel*> channels = pSampler->GetSamplerChannels();
    std::map<uint,SamplerChannel*>::iterator iter = channels.begin();
    for (; iter != channels.end(); iter++) {
        EngineChannel* c = iter->second->GetEngineChannel();
        if(c && c->GetSolo()) return true;
    }

    return false;
}

/**
 * Mutes all unmuted non-solo channels. Notice that the channels are muted
 * with -1 which indicates that they are muted because of the presence
 * of a solo channel(s). Channels muted with -1 will be automatically unmuted
 * when there are no solo channels left.
 */
void LSCPServer::MuteNonSoloChannels() {
    dmsg(2,("LSCPServer: MuteNonSoloChannels()\n"));
    std::map<uint,SamplerChannel*> channels = pSampler->GetSamplerChannels();
    std::map<uint,SamplerChannel*>::iterator iter = channels.begin();
    for (; iter != channels.end(); iter++) {
        EngineChannel* c = iter->second->GetEngineChannel();
        if(c && !c->GetSolo() && !c->GetMute()) c->SetMute(-1);
    }
}

/**
 * Unmutes all channels that are muted because of the presence
 * of a solo channel(s).
 */
void  LSCPServer::UnmuteChannels() {
    dmsg(2,("LSCPServer: UnmuteChannels()\n"));
    std::map<uint,SamplerChannel*> channels = pSampler->GetSamplerChannels();
    std::map<uint,SamplerChannel*>::iterator iter = channels.begin();
    for (; iter != channels.end(); iter++) {
        EngineChannel* c = iter->second->GetEngineChannel();
        if(c && c->GetMute() == -1) c->SetMute(0);
    }
}

String LSCPServer::AddOrReplaceMIDIInstrumentMapping(uint MidiBankMSB, uint MidiBankLSB, uint MidiProg, String EngineType, String InstrumentFile, uint InstrumentIndex, float Volume, MidiInstrumentMapper::mode_t LoadMode, String Name) {
    dmsg(2,("LSCPServer: AddOrReplaceMIDIInstrumentMapping()\n"));

    midi_prog_index_t idx;
    idx.midi_bank_msb = MidiBankMSB;
    idx.midi_bank_lsb = MidiBankLSB;
    idx.midi_prog     = MidiProg;

    MidiInstrumentMapper::entry_t entry;
    entry.EngineName      = EngineType;
    entry.InstrumentFile  = InstrumentFile;
    entry.InstrumentIndex = InstrumentIndex;
    entry.LoadMode        = LoadMode;
    entry.Volume          = Volume;
    entry.Name            = Name;

    LSCPResultSet result;
    try {
        // PERSISTENT mapping commands might bloock for a long time, so in
        // that case we add/replace the mapping in another thread
        bool bInBackground = (entry.LoadMode == MidiInstrumentMapper::PERSISTENT);
        MidiInstrumentMapper::AddOrReplaceMapping(idx, entry, bInBackground);
    } catch (Exception e) {
        result.Error(e);
    }
    return result.Produce();
}

String LSCPServer::RemoveMIDIInstrumentMapping(uint MidiBankMSB, uint MidiBankLSB, uint MidiProg) {
    dmsg(2,("LSCPServer: RemoveMIDIInstrumentMapping()\n"));

    midi_prog_index_t idx;
    idx.midi_bank_msb = MidiBankMSB;
    idx.midi_bank_lsb = MidiBankLSB;
    idx.midi_prog     = MidiProg;

    LSCPResultSet result;
    try {
        MidiInstrumentMapper::RemoveMapping(idx);
    } catch (Exception e) {
        result.Error(e);
    }
    return result.Produce();
}

String LSCPServer::GetMidiIstrumentMappings() {
    dmsg(2,("LSCPServer: GetMidiIstrumentMappings()\n"));
    LSCPResultSet result;
    result.Add(MidiInstrumentMapper::Mappings().size());
    return result.Produce();
}

String LSCPServer::GetMidiInstrumentMapping(uint MidiBankMSB, uint MidiBankLSB, uint MidiProg) {
    dmsg(2,("LSCPServer: GetMidiIstrumentMapping()\n"));
    LSCPResultSet result;
    try {
        midi_prog_index_t idx;
        idx.midi_bank_msb = MidiBankMSB;
        idx.midi_bank_lsb = MidiBankLSB;
        idx.midi_prog     = MidiProg;

        std::map<midi_prog_index_t,MidiInstrumentMapper::entry_t> mappings = MidiInstrumentMapper::Mappings();
        std::map<midi_prog_index_t,MidiInstrumentMapper::entry_t>::iterator iter = mappings.find(idx);
        if (iter == mappings.end()) result.Error("there is no map entry with that index");
        else { // found
            result.Add("NAME", iter->second.Name);
            result.Add("ENGINE_NAME", iter->second.EngineName);
            result.Add("INSTRUMENT_FILE", iter->second.InstrumentFile);
            result.Add("INSTRUMENT_NR", (int) iter->second.InstrumentIndex);
            String instrumentName;
            Engine* pEngine = EngineFactory::Create(iter->second.EngineName);
            if (pEngine) {
                if (pEngine->GetInstrumentManager()) {
                    InstrumentManager::instrument_id_t instrID;
                    instrID.FileName = iter->second.InstrumentFile;
                    instrID.Index    = iter->second.InstrumentIndex;
                    instrumentName = pEngine->GetInstrumentManager()->GetInstrumentName(instrID);
                }
                EngineFactory::Destroy(pEngine);
            }
            result.Add("INSTRUMENT_NAME", instrumentName);
            switch (iter->second.LoadMode) {
                case MidiInstrumentMapper::ON_DEMAND:
                    result.Add("LOAD_MODE", "ON_DEMAND");
                    break;
                case MidiInstrumentMapper::ON_DEMAND_HOLD:
                    result.Add("LOAD_MODE", "ON_DEMAND_HOLD");
                    break;
                case MidiInstrumentMapper::PERSISTENT:
                    result.Add("LOAD_MODE", "PERSISTENT");
                    break;
                default:
                    throw Exception("entry reflects invalid LOAD_MODE, consider this as a bug!");
            }
            result.Add("VOLUME", iter->second.Volume);
        }
    } catch (Exception e) {
        result.Error(e);
    }
    return result.Produce();
}

String LSCPServer::ListMidiInstrumentMappings() {
    dmsg(2,("LSCPServer: ListMidiIstrumentMappings()\n"));
    LSCPResultSet result;
    try {
        String s;
        std::map<midi_prog_index_t,MidiInstrumentMapper::entry_t> mappings = MidiInstrumentMapper::Mappings();
        std::map<midi_prog_index_t,MidiInstrumentMapper::entry_t>::iterator iter = mappings.begin();
        for (; iter != mappings.end(); iter++) {
            if (s.size()) s += ",";
            s += "{" + ToString(int(iter->first.midi_bank_msb)) + ","
                     + ToString(int(iter->first.midi_bank_lsb)) + ","
                     + ToString(int(iter->first.midi_prog))     + "}";
        }
        result.Add(s);
    } catch (Exception e) {
        result.Error(e);
    }
    return result.Produce();
}

String LSCPServer::ClearMidiInstrumentMappings() {
    dmsg(2,("LSCPServer: ClearMidiInstrumentMappings()\n"));
    LSCPResultSet result;
    try {
        MidiInstrumentMapper::RemoveAllMappings();
    } catch (Exception e) {
        result.Error(e);
    }
    return result.Produce();
}

/**
 * Will be called by the parser to reset a particular sampler channel.
 */
String LSCPServer::ResetChannel(uint uiSamplerChannel) {
    dmsg(2,("LSCPServer: ResetChannel(SamplerChannel=%d)\n", uiSamplerChannel));
    LSCPResultSet result;
    try {
        SamplerChannel* pSamplerChannel = pSampler->GetSamplerChannel(uiSamplerChannel);
        if (!pSamplerChannel) throw Exception("Invalid sampler channel number " + ToString(uiSamplerChannel));
        EngineChannel* pEngineChannel = pSamplerChannel->GetEngineChannel();
        if (!pEngineChannel) throw Exception("No engine type assigned to sampler channel");
        pEngineChannel->Reset();
    }
    catch (Exception e) {
         result.Error(e);
    }
    return result.Produce();
}

/**
 * Will be called by the parser to reset the whole sampler.
 */
String LSCPServer::ResetSampler() {
    dmsg(2,("LSCPServer: ResetSampler()\n"));
    pSampler->Reset();
    LSCPResultSet result;
    return result.Produce();
}

/**
 * Will be called by the parser to return general informations about this
 * sampler.
 */
String LSCPServer::GetServerInfo() {
    dmsg(2,("LSCPServer: GetServerInfo()\n"));
    LSCPResultSet result;
    result.Add("DESCRIPTION", "LinuxSampler - modular, streaming capable sampler");
    result.Add("VERSION", VERSION);
    result.Add("PROTOCOL_VERSION", ToString(LSCP_RELEASE_MAJOR) + "." + ToString(LSCP_RELEASE_MINOR));
    return result.Produce();
}

/**
 * Will be called by the parser to return the current number of all active voices.
 */
String LSCPServer::GetTotalVoiceCount() {
    dmsg(2,("LSCPServer: GetTotalVoiceCount()\n"));
    LSCPResultSet result;
    result.Add(pSampler->GetVoiceCount());
    return result.Produce();
}

/**
 * Will be called by the parser to return the maximum number of voices.
 */
String LSCPServer::GetTotalVoiceCountMax() {
    dmsg(2,("LSCPServer: GetTotalVoiceCountMax()\n"));
    LSCPResultSet result;
    result.Add(EngineFactory::EngineInstances().size() * CONFIG_MAX_VOICES);
    return result.Produce();
}

/**
 * Will be called by the parser to subscribe a client (frontend) on the
 * server for receiving event messages.
 */
String LSCPServer::SubscribeNotification(LSCPEvent::event_t type) {
    dmsg(2,("LSCPServer: SubscribeNotification(Event=%s)\n", LSCPEvent::Name(type).c_str()));
    LSCPResultSet result;
    SubscriptionMutex.Lock();
    eventSubscriptions[type].push_back(currentSocket);
    SubscriptionMutex.Unlock();
    return result.Produce();
}

/**
 * Will be called by the parser to unsubscribe a client on the server
 * for not receiving further event messages.
 */
String LSCPServer::UnsubscribeNotification(LSCPEvent::event_t type) {
    dmsg(2,("LSCPServer: UnsubscribeNotification(Event=%s)\n", LSCPEvent::Name(type).c_str()));
    LSCPResultSet result;
    SubscriptionMutex.Lock();
    eventSubscriptions[type].remove(currentSocket);
    SubscriptionMutex.Unlock();
    return result.Produce();
}

static int select_callback(void * lscpResultSet, int argc,
			char **argv, char **azColName)
{
    LSCPResultSet* resultSet = (LSCPResultSet*) lscpResultSet;
    resultSet->Add(argc, argv);
    return 0;
}

String LSCPServer::QueryDatabase(String query) {
    LSCPResultSet result;
#if HAVE_SQLITE3
    char* zErrMsg = NULL;
    sqlite3 *db;
    String selectStr = "SELECT " + query;

    int rc = sqlite3_open("linuxsampler.db", &db);
    if (rc == SQLITE_OK)
    {
	    rc = sqlite3_exec(db, selectStr.c_str(), select_callback, &result, &zErrMsg);
    }
    if ( rc != SQLITE_OK )
    {
	    result.Error(String(zErrMsg), rc);
    }
    sqlite3_close(db);
#else
    result.Error(String("SQLITE3 was not installed when linuxsampler was built. SELECT statement is not available."), 0);
#endif
    return result.Produce();
}

/**
 * Will be called by the parser to enable or disable echo mode; if echo
 * mode is enabled, all commands from the client will (immediately) be
 * echoed back to the client.
 */
String LSCPServer::SetEcho(yyparse_param_t* pSession, double boolean_value) {
    dmsg(2,("LSCPServer: SetEcho(val=%f)\n", boolean_value));
    LSCPResultSet result;
    try {
        if      (boolean_value == 0) pSession->bVerbose = false;
        else if (boolean_value == 1) pSession->bVerbose = true;
        else throw Exception("Not a boolean value, must either be 0 or 1");
    }
    catch (Exception e) {
         result.Error(e);
    }
    return result.Produce();
}
