/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003 by Benno Senoner and Christian Schoenebeck         *
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

LSCPServer::LSCPServer(AudioThread* pEngine) : Thread(false, 0, -4) {
    this->pEngine = pEngine;
}

int LSCPServer::Main() {
    hSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (hSocket < 0) {
        std::cerr << "LSCPServer: Could not create server socket." << std::endl;
        return -1;
    }

    SocketAddress.sin_family      = AF_INET;
    SocketAddress.sin_port        = htons(LSCP_PORT);
    SocketAddress.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(hSocket, (sockaddr*) &SocketAddress, sizeof(sockaddr_in)) < 0) {
        std::cerr << "LSCPServer: Could not bind server socket." << std::endl;
        close(hSocket);
        return -1;
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
            return -1;
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

/**
 * Will be called by the parser to load an instrument.
 */
String LSCPServer::LoadInstrument(String Filename, uint Instrument, uint SamplerChannel) {
    dmsg(2,("LSCPServer: LoadInstrument(Filename=%s,Instrument=%d,SamplerChannel=%d)\n", Filename.c_str(), Instrument, SamplerChannel));
    result_t res = pEngine->LoadInstrument(Filename.c_str(), Instrument);
    return ConvertResult(res);
}

/**
 * Will be called by the parser to load and deploy an engine.
 */
String LSCPServer::LoadEngine(String EngineName, uint SamplerChannel) {
    dmsg(2,("LSCPServer: LoadEngine(EngineName=%s,SamplerChannel=%d)\n", EngineName.c_str(), SamplerChannel));
    return "ERR:0:Not implemented yet.\r\n";
}

/**
 * Will be called by the parser to get the amount of sampler channels.
 */
String LSCPServer::GetChannels() {
    dmsg(2,("LSCPServer: GetChannels()\n"));
    return "1\r\n";
}

/**
 * Will be called by the parser to add a sampler channel.
 */
String LSCPServer::AddChannel() {
    dmsg(2,("LSCPServer: AddChannel()\n"));
    return "ERR:0:Not implemented yet.\r\n";
}

/**
 * Will be called by the parser to remove a sampler channel.
 */
String LSCPServer::RemoveChannel(uint SamplerChannel) {
    dmsg(2,("LSCPServer: RemoveChannel(SamplerChannel=%d)\n", SamplerChannel));
    return "ERR:0:Not implemented yet.\r\n";
}

/**
 * Will be called by the parser to get all available engines.
 */
String LSCPServer::GetAvailableEngines() {
    dmsg(2,("LSCPServer: GetAvailableEngines()\n"));
    return "ERR:0:Not implemented yet.\r\n";
}

/**
 * Will be called by the parser to get descriptions for a particular engine.
 */
String LSCPServer::GetEngineInfo(String EngineName) {
    dmsg(2,("LSCPServer: GetEngineInfo(EngineName=%s)\n", EngineName.c_str()));
    return "ERR:0:Not implemented yet.\r\n";
}

/**
 * Will be called by the parser to get informations about a particular
 * sampler channel.
 */
String LSCPServer::GetChannelInfo(uint SamplerChannel) {
    dmsg(2,("LSCPServer: GetChannelInfo(SamplerChannel=%d)\n", SamplerChannel));
    return "ERR:0:Not implemented yet.\r\n";
}

/**
 * Will be called by the parser to get the amount of active voices on a
 * particular sampler channel.
 */
String LSCPServer::GetVoiceCount(uint SamplerChannel) {
    dmsg(2,("LSCPServer: GetVoiceCount(SamplerChannel=%d)\n", SamplerChannel));
    return ToString(pEngine->ActiveVoiceCount) + "\r\n";
}

/**
 * Will be called by the parser to get the amount of active disk streams on a
 * particular sampler channel.
 */
String LSCPServer::GetStreamCount(uint SamplerChannel) {
    dmsg(2,("LSCPServer: GetStreamCount(SamplerChannel=%d)\n", SamplerChannel));
    return ToString(pEngine->pDiskThread->ActiveStreamCount) + "\r\n";
}

/**
 * Will be called by the parser to get the buffer fill states of all disk
 * streams on a particular sampler channel.
 */
String LSCPServer::GetBufferFill(fill_response_t ResponseType, uint SamplerChannel) {
    dmsg(2,("LSCPServer: GetBufferFill(ResponseType=%d, SamplerChannel=%d)\n", ResponseType, SamplerChannel));
    return (ResponseType == fill_response_bytes) ? pEngine->pDiskThread->GetBufferFillBytes() + "\r\n"
                                                 : pEngine->pDiskThread->GetBufferFillPercentage() + "\r\n";
}

/**
 * Will be called by the parser to change the audio output type on a
 * particular sampler channel.
 */
String LSCPServer::SetAudioOutputType(audio_output_type_t AudioOutputType, uint SamplerChannel) {
    dmsg(2,("LSCPServer: SetAudioOutputType(AudioOutputType=%d, SamplerChannel=%d)\n", AudioOutputType, SamplerChannel));
    return "ERR:0:Not implemented yet.\r\n";
}

/**
 * Will be called by the parser to change the audio output channel for
 * playback on a particular sampler channel.
 */
String LSCPServer::SetAudioOutputChannel(uint AudioOutputChannel, uint SamplerChannel) {
    dmsg(2,("LSCPServer: SetAudioOutputChannel(AudioOutputChannel=%d, SamplerChannel=%d)\n", AudioOutputChannel, SamplerChannel));
    return "ERR:0:Not implemented yet.\r\n";
}

/**
 * Will be called by the parser to change the MIDI input port on which the
 * engine of a particular sampler channel should listen to.
 */
String LSCPServer::SetMIDIInputPort(String MIDIInputPort, uint Samplerchannel) {
    dmsg(2,("LSCPServer: SetMIDIInputPort(MIDIInputPort=%s, Samplerchannel=%d)\n", MIDIInputPort.c_str(), Samplerchannel));
    return "ERR:0:Not implemented yet.\r\n";
}

/**
 * Will be called by the parser to change the MIDI input channel on which the
 * engine of a particular sampler channel should listen to.
 */
String LSCPServer::SetMIDIInputChannel(uint MIDIChannel, uint SamplerChannel) {
    dmsg(2,("LSCPServer: SetMIDIInputChannel(MIDIChannel=%d, SamplerChannel=%d)\n", MIDIChannel, SamplerChannel));
    return "ERR:0:Not implemented yet.\r\n";
}

/**
 * Will be called by the parser to change the global volume factor on a
 * particular sampler channel.
 */
String LSCPServer::SetVolume(double Volume, uint SamplerChannel) {
    dmsg(2,("LSCPServer: SetVolume(Volume=%f, SamplerChannel=%d)\n", Volume, SamplerChannel));
    pEngine->Volume = Volume;
    return "OK\r\n";
}

/**
 * Will be called by the parser to reset a particular sampler channel.
 */
String LSCPServer::ResetChannel(uint SamplerChannel) {
    dmsg(2,("LSCPServer: ResetChannel(SamplerChannel=%d)\n", SamplerChannel));
    pEngine->Reset();
    return "OK\r\n";
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
