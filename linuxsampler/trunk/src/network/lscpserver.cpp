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

#include "lscpserver.h"
#include "lscpresultset.h"

#include "../engines/gig/Engine.h"
#include "../audiodriver/AudioOutputDeviceFactory.h"

LSCPServer::LSCPServer(Sampler* pSampler) : Thread(false, 0, -4) {
    this->pSampler = pSampler;
}

int LSCPServer::Main() {
    hSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (hSocket < 0) {
        std::cerr << "LSCPServer: Could not create server socket." << std::endl;
        //return -1;
        exit(EXIT_FAILURE);
    }

    SocketAddress.sin_family      = AF_INET;
    SocketAddress.sin_port        = htons(LSCP_PORT);
    SocketAddress.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(hSocket, (sockaddr*) &SocketAddress, sizeof(sockaddr_in)) < 0) {
        std::cerr << "LSCPServer: Could not bind server socket." << std::endl;
        close(hSocket);
        //return -1;
        exit(EXIT_FAILURE);
    }

    listen(hSocket, 1);
    dmsg(1,("LSCPServer: Server running.\n")); // server running

    // now wait for client connections and handle their requests
    sockaddr_in client;
    int length = sizeof(client);
    while (true) {
        hSession = accept(hSocket, (sockaddr*) &client, (socklen_t*) &length);
        if (hSession < 0) {
            std::cerr << "LSCPServer: Client connection failed." << std::endl;
            close(hSocket);
            //return -1;
            exit(EXIT_FAILURE);
        }

        dmsg(1,("LSCPServer: Client connection established.\n"));
        //send(hSession, "Welcome!\r\n", 10, 0);

        // Parser invocation
        yyparse_param_t yyparse_param;
        yyparse_param.pServer = this;
        yylex_init(&yyparse_param.pScanner);
        while (yyparse(&yyparse_param) == LSCP_SYNTAX_ERROR); // recall parser in case of syntax error
        yylex_destroy(yyparse_param.pScanner);

        close(hSession);
        dmsg(1,("LSCPServer: Client connection terminated.\n"));
    }
}

/**
 * Will be called by the parser whenever it wants to send an answer to the
 * client / frontend.
 *
 * @param ReturnMessage - message that will be send to the client
 */
void LSCPServer::AnswerClient(String ReturnMessage) {
    dmsg(2,("LSCPServer::AnswerClient(ReturnMessage=%s)", ReturnMessage.c_str()));
    send(hSession, ReturnMessage.c_str(), ReturnMessage.size(), 0);
}

String LSCPServer::CreateAudioOutputDevice(String Driver, std::map<String,String> Parameters) {
    dmsg(2,("LSCPServer: CreateAudioOutputDevice(Driver=%s)\n", Driver.c_str()));
    LSCPResultSet result;
    try {
        AudioOutputDevice* pDevice = pSampler->CreateAudioOutputDevice(Driver, Parameters);
        std::map<uint, AudioOutputDevice*> devices = pSampler->GetAudioOutputDevices();
        // search for the created device to get its index
        int index = -1;
        std::map<uint, AudioOutputDevice*>::iterator iter = devices.begin();
        for (; iter != devices.end(); iter++) {
            if (iter->second == pDevice) {
                index = iter->first;
                break;
            }
        }
        if (index == -1) throw LinuxSamplerException("Internal error: could not find created audio output device.");
        result = index; // success
    }
    catch (LinuxSamplerException e) {
        result.Error(e);
    }
    return result.Produce();
}

String LSCPServer::DestroyAudioOutputDevice(uint DeviceIndex) {
    dmsg(2,("LSCPServer: DestroyAudioOutputDevice(DeviceIndex=%d)\n", DeviceIndex));
    LSCPResultSet result;
    try {
        std::map<uint, AudioOutputDevice*> devices = pSampler->GetAudioOutputDevices();
        if (!devices[DeviceIndex]) throw LinuxSamplerException("There is no audio output device with index " + ToString(DeviceIndex) + ".");
        AudioOutputDevice* pDevice = devices[DeviceIndex];
        pSampler->DestroyAudioOutputDevice(pDevice);
    }
    catch (LinuxSamplerException e) {
        result.Error(e);
    }
    return result.Produce();
}

/**
 * Will be called by the parser to load an instrument.
 */
String LSCPServer::LoadInstrument(String Filename, uint uiInstrument, uint uiSamplerChannel) {
    dmsg(2,("LSCPServer: LoadInstrument(Filename=%s,Instrument=%d,SamplerChannel=%d)\n", Filename.c_str(), uiInstrument, uiSamplerChannel));
    LSCPResultSet result;
    try {
        SamplerChannel* pSamplerChannel = pSampler->GetSamplerChannel(uiSamplerChannel);
        if (!pSamplerChannel) throw LinuxSamplerException("Index out of bounds");
        Engine* pEngine = pSamplerChannel->GetEngine();
        if (!pEngine) throw LinuxSamplerException("No engine loaded on channel");
        pEngine->LoadInstrument(Filename.c_str(), uiInstrument);
    }
    catch (LinuxSamplerException e) {
         result.Error(e);
    }
    return result.Produce();
}

/**
 * Will be called by the parser to load and deploy an engine.
 */
String LSCPServer::LoadEngine(String EngineName, uint uiSamplerChannel) {
    dmsg(2,("LSCPServer: LoadEngine(EngineName=%s,SamplerChannel=%d)\n", EngineName.c_str(), uiSamplerChannel));
    LSCPResultSet result;
    try {
        Engine::type_t type;
        if ((EngineName == "GigEngine") || (EngineName == "gig")) type = Engine::type_gig;
        else throw LinuxSamplerException("Unknown engine type");
        SamplerChannel* pSamplerChannel = pSampler->GetSamplerChannel(uiSamplerChannel);
        if (!pSamplerChannel) throw LinuxSamplerException("Index out of bounds");
        pSamplerChannel->LoadEngine(type);
    }
    catch (LinuxSamplerException e) {
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
 * Will be called by the parser to add a sampler channel.
 */
String LSCPServer::AddChannel() {
    dmsg(2,("LSCPServer: AddChannel()\n"));
    SamplerChannel* pSamplerChannel = pSampler->AddSamplerChannel();
    LSCPResultSet result(pSamplerChannel->Index());
    return result.Produce();
}

/**
 * Will be called by the parser to remove a sampler channel.
 */
String LSCPServer::RemoveChannel(uint uiSamplerChannel) {
    dmsg(2,("LSCPServer: RemoveChannel(SamplerChannel=%d)\n", uiSamplerChannel));
    LSCPResultSet result;
    pSampler->RemoveSamplerChannel(uiSamplerChannel);
    return result.Produce();
}

/**
 * Will be called by the parser to get all available engines.
 */
String LSCPServer::GetAvailableEngines() {
    dmsg(2,("LSCPServer: GetAvailableEngines()\n"));
    LSCPResultSet result("GigEngine");
    return result.Produce();
}

/**
 * Will be called by the parser to get descriptions for a particular engine.
 */
String LSCPServer::GetEngineInfo(String EngineName) {
    dmsg(2,("LSCPServer: GetEngineInfo(EngineName=%s)\n", EngineName.c_str()));
    LSCPResultSet result;
    try {
        if ((EngineName == "GigEngine") || (EngineName == "gig")) {
            Engine* pEngine = new LinuxSampler::gig::Engine;
	    result.Add(pEngine->Description());
            result.Add(pEngine->Version());
            delete pEngine;
        }
        else throw LinuxSamplerException("Unknown engine type");
    }
    catch (LinuxSamplerException e) {
         result.Error(e);
    }
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
        if (!pSamplerChannel) throw LinuxSamplerException("Index out of bounds");
        Engine* pEngine = pSamplerChannel->GetEngine();

	//Defaults values
	String EngineName = "NONE";
	float Volume = 0;
	String InstrumentFileName = "NONE";
	int InstrumentIndex = 0;

        if (pEngine) {
	    EngineName =  pEngine->EngineName();
	    Volume = pEngine->Volume();
            int iIdx = pEngine->InstrumentIndex();
            if (iIdx != -1) {
	        InstrumentFileName = pEngine->InstrumentFileName();
		InstrumentIndex = iIdx;
            }
	}

        result.Add("ENGINE_NAME", EngineName);
        result.Add("VOLUME", Volume);

	//Some hardcoded stuff for now to make GUI look good
        result.Add("AUDIO_OUTPUT_DEVICE", "0");
        result.Add("AUDIO_OUTPUT_CHANNELS", "2");
        result.Add("AUDIO_OUTPUT_ROUTING", "0,1");

        result.Add("INSTRUMENT_FILE", InstrumentFileName);
        result.Add("INSTRUMENT_NR", InstrumentIndex);

	//Some more hardcoded stuff for now to make GUI look good
        result.Add("MIDI_INPUT_DEVICE", "0");
        result.Add("MIDI_INPUT_PORT", "0");
        result.Add("MIDI_INPUT_CHANNEL", "1");
    }
    catch (LinuxSamplerException e) {
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
        if (!pSamplerChannel) throw LinuxSamplerException("Index out of bounds");
        Engine* pEngine = pSamplerChannel->GetEngine();
        if (!pEngine) throw LinuxSamplerException("No engine loaded on channel");
	result.Add(pEngine->VoiceCount());
    }
    catch (LinuxSamplerException e) {
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
        if (!pSamplerChannel) throw LinuxSamplerException("Index out of bounds");
        Engine* pEngine = pSamplerChannel->GetEngine();
        if (!pEngine) throw LinuxSamplerException("No engine loaded on channel");
	result.Add(pEngine->DiskStreamCount());
    }
    catch (LinuxSamplerException e) {
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
        if (!pSamplerChannel) throw LinuxSamplerException("Index out of bounds");
        Engine* pEngine = pSamplerChannel->GetEngine();
        if (!pEngine) throw LinuxSamplerException("No engine loaded on channel");
        if (!pEngine->DiskStreamSupported())
	    result.Add("NA");
        else {
            switch (ResponseType) {
                case fill_response_bytes:
	    	    result.Add(pEngine->DiskStreamBufferFillBytes());
	    	    break;
                case fill_response_percentage:
		    result.Add(pEngine->DiskStreamBufferFillPercentage());
		    break;
                default:
                    throw LinuxSamplerException("Unknown fill response type");
            }
	}
    }
    catch (LinuxSamplerException e) {
         result.Error(e);
    }
    return result.Produce();
}

String LSCPServer::GetAvailableAudioOutputDrivers() {
    dmsg(2,("LSCPServer: GetAvailableAudioOutputDrivers()\n"));
    LSCPResultSet result;
    try {
        String s = AudioOutputDeviceFactory::AvailableDriversAsString();
        result.Add(s);
    }
    catch (LinuxSamplerException e) {
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
    catch (LinuxSamplerException e) {
        result.Error(e);
    }
    return result.Produce();
}

String LSCPServer::GetAudioOutputDriverParameterInfo(String Driver, String Parameter, std::map<String,String> DependencyList) {
    dmsg(2,("LSCPServer: GetAudioOutputDriverParameterInfo(Driver=%s,Parameter=%s)\n",Driver.c_str(),Parameter.c_str()));
    LSCPResultSet result;
    try {
        DeviceCreationParameter* pParameter = AudioOutputDeviceFactory::GetDriverParameter(Driver, Parameter);
        result.Add("TYPE",         pParameter->Type());
        result.Add("DESCRIPTION",  pParameter->Description());
        result.Add("MANDATORY",    pParameter->Mandatory());
        result.Add("FIX",          pParameter->Fix());
        result.Add("MULTIPLICITY", pParameter->Multiplicity());
        if (pParameter->Depends())       result.Add("DEPENDS",       pParameter->Depends());
        if (pParameter->Default())       result.Add("DEFAULT",       pParameter->Default());
        if (pParameter->RangeMin())      result.Add("RANGE_MIN",     pParameter->RangeMin());
        if (pParameter->RangeMax())      result.Add("RANGE_MAX",     pParameter->RangeMax());
        if (pParameter->Possibilities()) result.Add("POSSIBILITIES", pParameter->Possibilities());
    }
    catch (LinuxSamplerException e) {
        result.Error(e);
    }
    return result.Produce();
}

String LSCPServer::GetAudioOutputDeviceCount() {
    dmsg(2,("LSCPServer: GetAudioOutputDeviceCount()\n"));
    LSCPResultSet result;
    try {
        uint count = pSampler->AudioOutputDevices();
        result = count; // success
    }
    catch (LinuxSamplerException e) {
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
    catch (LinuxSamplerException e) {
        result.Error(e);
    }
    return result.Produce();
}

String LSCPServer::GetAudioOutputDeviceInfo(uint DeviceIndex) {
    dmsg(2,("LSCPServer: GetAudioOutputDeviceInfo(DeviceIndex=%d)\n",DeviceIndex));
    LSCPResultSet result;
    try {
        std::map<uint,AudioOutputDevice*> devices = pSampler->GetAudioOutputDevices();
        if (!devices[DeviceIndex]) throw LinuxSamplerException("There is no audio output device with index " + ToString(DeviceIndex) + ".");
        AudioOutputDevice* pDevice = devices[DeviceIndex];
        std::map<String,DeviceCreationParameter*> parameters = pDevice->DeviceParameters();
        std::map<String,DeviceCreationParameter*>::iterator iter = parameters.begin();
        for (; iter != parameters.end(); iter++) {
            result.Add(iter->first, iter->second->Value());
        }
    }
    catch (LinuxSamplerException e) {
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
        if (!devices[DeviceId]) throw LinuxSamplerException("There is no audio output device with index " + ToString(DeviceId) + ".");
        AudioOutputDevice* pDevice = devices[DeviceId];

        // get audio channel
        AudioChannel* pChannel = pDevice->Channel(ChannelId);
        if (!pChannel) throw LinuxSamplerException("Audio ouotput device does not have channel " + ToString(ChannelId) + ".");

        // return the values of all audio channel parameters
        std::map<String,DeviceRuntimeParameter*> parameters = pChannel->ChannelParameters();
        std::map<String,DeviceRuntimeParameter*>::iterator iter = parameters.begin();
        for (; iter != parameters.end(); iter++) {
            result.Add(iter->first, iter->second->Value());
        }
    }
    catch (LinuxSamplerException e) {
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
        if (!devices[DeviceId]) throw LinuxSamplerException("There is no audio output device with index " + ToString(DeviceId) + ".");
        AudioOutputDevice* pDevice = devices[DeviceId];

        // get audio channel
        AudioChannel* pChannel = pDevice->Channel(ChannelId);
        if (!pChannel) throw LinuxSamplerException("Audio output device does not have channel " + ToString(ChannelId) + ".");

        // get desired audio channel parameter
        std::map<String,DeviceRuntimeParameter*> parameters = pChannel->ChannelParameters();
        if (!parameters[ParameterName]) throw LinuxSamplerException("Audio channel does not provide a parameter '" + ParameterName + "'.");
        DeviceRuntimeParameter* pParameter = parameters[ParameterName];

        // return all fields of this audio channel parameter
        result.Add("TYPE",         pParameter->Type());
        result.Add("DESCRIPTION",  pParameter->Description());
        result.Add("FIX",          pParameter->Fix());
        result.Add("MULTIPLICITY", pParameter->Multiplicity());
        if (pParameter->RangeMin())      result.Add("RANGE_MIN",     pParameter->RangeMin());
        if (pParameter->RangeMax())      result.Add("RANGE_MAX",     pParameter->RangeMax());
        if (pParameter->Possibilities()) result.Add("POSSIBILITIES", pParameter->Possibilities());
    }
    catch (LinuxSamplerException e) {
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
        if (!devices[DeviceId]) throw LinuxSamplerException("There is no audio output device with index " + ToString(DeviceId) + ".");
        AudioOutputDevice* pDevice = devices[DeviceId];

        // get audio channel
        AudioChannel* pChannel = pDevice->Channel(ChannelId);
        if (!pChannel) throw LinuxSamplerException("Audio output device does not have channel " + ToString(ChannelId) + ".");

        // get desired audio channel parameter
        std::map<String,DeviceRuntimeParameter*> parameters = pChannel->ChannelParameters();
        if (!parameters[ParamKey]) throw LinuxSamplerException("Audio channel does not provide a parameter '" + ParamKey + "'.");
        DeviceRuntimeParameter* pParameter = parameters[ParamKey];

        // set new channel parameter value
        pParameter->SetValue(ParamVal);
    }
    catch (LinuxSamplerException e) {
        result.Error(e);
    }
    return result.Produce();
}

String LSCPServer::SetAudioOutputDeviceParameter(uint DeviceIndex, String ParamKey, String ParamVal) {
    dmsg(2,("LSCPServer: SetAudioOutputDeviceParameter(DeviceIndex=%d,ParamKey=%s,ParamVal=%s)\n",DeviceIndex,ParamKey.c_str(),ParamVal.c_str()));
    LSCPResultSet result;
    try {
        std::map<uint,AudioOutputDevice*> devices = pSampler->GetAudioOutputDevices();
        if (!devices[DeviceIndex]) throw LinuxSamplerException("There is no audio output device with index " + ToString(DeviceIndex) + ".");
        AudioOutputDevice* pDevice = devices[DeviceIndex];
        std::map<String,DeviceCreationParameter*> parameters = pDevice->DeviceParameters();
        if (!parameters[ParamKey]) throw LinuxSamplerException("Audio output device " + ToString(DeviceIndex) + " does not have a device parameter '" + ParamKey + "'");
        parameters[ParamKey]->SetValue(ParamVal);
    }
    catch (LinuxSamplerException e) {
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
    return "ERR:0:Not implemented yet.\r\n"; //FIXME: Add support for this in resultset class?
}

String LSCPServer::SetMIDIInputType(String MidiInputDriver, uint uiSamplerChannel) {
    dmsg(2,("LSCPServer: SetMIDIInputType(String MidiInputDriver=%s, SamplerChannel=%d)\n",MidiInputDriver.c_str(),uiSamplerChannel));
    LSCPResultSet result;
    try {
        SamplerChannel* pSamplerChannel = pSampler->GetSamplerChannel(uiSamplerChannel);
        if (!pSamplerChannel) throw LinuxSamplerException("Index out of bounds");
        // FIXME: workaround until MIDI driver configuration is implemented (using a Factory class for the MIDI input drivers then, like its already done for audio output drivers)
        if (MidiInputDriver != "ALSA") throw LinuxSamplerException("Unknown MIDI input driver '" + MidiInputDriver + "'.");
        MidiInputDevice::type_t MidiInputType = MidiInputDevice::type_alsa;
        pSamplerChannel->SetMidiInputDevice(MidiInputType);
    }
    catch (LinuxSamplerException e) {
         result.Error(e);
    }
    return result.Produce();
}

/**
 * Will be called by the parser to change the MIDI input port on which the
 * engine of a particular sampler channel should listen to.
 */
String LSCPServer::SetMIDIInputPort(String MIDIInputPort, uint uiSamplerChannel) {
    dmsg(2,("LSCPServer: SetMIDIInputPort(MIDIInputPort=%s, Samplerchannel=%d)\n", MIDIInputPort.c_str(), uiSamplerChannel));
    LSCPResultSet result;
    try {
        SamplerChannel* pSamplerChannel = pSampler->GetSamplerChannel(uiSamplerChannel);
        if (!pSamplerChannel) throw LinuxSamplerException("Index out of bounds");
        if (!pSamplerChannel->GetMidiInputDevice()) throw LinuxSamplerException("No MIDI input device connected yet");
        pSamplerChannel->GetMidiInputDevice()->SetInputPort(MIDIInputPort.c_str());
    }
    catch (LinuxSamplerException e) {
         result.Error(e);
    }
    return result.Produce();
}

/**
 * Will be called by the parser to change the MIDI input channel on which the
 * engine of a particular sampler channel should listen to.
 */
String LSCPServer::SetMIDIInputChannel(uint MIDIChannel, uint uiSamplerChannel) {
    dmsg(2,("LSCPServer: SetMIDIInputChannel(MIDIChannel=%d, SamplerChannel=%d)\n", MIDIChannel, uiSamplerChannel));
    LSCPResultSet result;
    try {
        SamplerChannel* pSamplerChannel = pSampler->GetSamplerChannel(uiSamplerChannel);
        if (!pSamplerChannel) throw LinuxSamplerException("Index out of bounds");
        if (!pSamplerChannel->GetMidiInputDevice()) throw LinuxSamplerException("No MIDI input device connected yet");
        MidiInputDevice::type_t oldtype = pSamplerChannel->GetMidiInputDevice()->Type();
        pSamplerChannel->SetMidiInputDevice(oldtype, (MidiInputDevice::midi_chan_t) MIDIChannel);
    }
    catch (LinuxSamplerException e) {
         result.Error(e);
    }
    return result.Produce();
}

String LSCPServer::SetAudioOutputDevice(uint AudioDeviceId, uint SamplerChannel) {
    LSCPResultSet result;
    try {
        throw LinuxSamplerException("Command not yet implemented");
    }
    catch (LinuxSamplerException e) {
         result.Error(e);
    }
    return result.Produce();
}

/**
 * Will be called by the parser to change the global volume factor on a
 * particular sampler channel.
 */
String LSCPServer::SetVolume(double Volume, uint uiSamplerChannel) {
    dmsg(2,("LSCPServer: SetVolume(Volume=%f, SamplerChannel=%d)\n", Volume, uiSamplerChannel));
    LSCPResultSet result;
    try {
        SamplerChannel* pSamplerChannel = pSampler->GetSamplerChannel(uiSamplerChannel);
        if (!pSamplerChannel) throw LinuxSamplerException("Index out of bounds");
        Engine* pEngine = pSamplerChannel->GetEngine();
        if (!pEngine) throw LinuxSamplerException("No engine loaded on channel");
        pEngine->Volume(Volume);
    }
    catch (LinuxSamplerException e) {
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
        if (!pSamplerChannel) throw LinuxSamplerException("Index out of bounds");
        Engine* pEngine = pSamplerChannel->GetEngine();
        if (!pEngine) throw LinuxSamplerException("No engine loaded on channel");
        pEngine->Reset();
    }
    catch (LinuxSamplerException e) {
         result.Error(e);
    }
    return result.Produce();
}

/**
 * Will be called by the parser to subscribe a client (frontend) on the
 * server for receiving event messages.
 */
String LSCPServer::SubscribeNotification(uint UDPPort) {
    dmsg(2,("LSCPServer: SubscribeNotification(UDPPort=%d)\n", UDPPort));
    return "ERR:0:Not implemented yet.\r\n";
}

/**
 * Will be called by the parser to unsubscribe a client on the server
 * for not receiving further event messages.
 */
String LSCPServer::UnsubscribeNotification(String SessionID) {
    dmsg(2,("LSCPServer: UnsubscribeNotification(SessionID=%s)\n", SessionID.c_str()));
    return "ERR:0:Not implemented yet.\r\n";
}
