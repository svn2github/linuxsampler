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

#ifndef __LSCPSERVER_H_
#define __LSCPSERVER_H_

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "lscp.h"
#include "lscpparser.h"
#include "../Sampler.h"
#include "../common/Thread.h"

/// TCP Port on which the server should listen for connection requests.
#define LSCP_PORT 8888

using namespace LinuxSampler;

/// Handle for a client connection (FIXME: doesn't work for more than one network connections of course, thus has to be included to the yyparse() parameters instead).
extern int hSession;

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
        String LoadInstrument(String Filename, uint uiInstrument, uint uiSamplerChannel);
        String LoadEngine(String EngineName, uint uiSamplerChannel);
        String GetChannels();
        String AddChannel();
        String RemoveChannel(uint uiSamplerChannel);
        String GetAvailableEngines();
        String GetEngineInfo(String EngineName);
        String GetChannelInfo(uint uiSamplerChannel);
        String GetVoiceCount(uint uiSamplerChannel);
        String GetStreamCount(uint uiSamplerChannel);
        String GetBufferFill(fill_response_t ResponseType, uint uiSamplerChannel);
        String SetAudioOutputType(audio_output_type_t AudioOutputType, uint uiSamplerChannel);
        String SetAudioOutputChannel(uint AudioOutputChannel, uint uiSamplerChannel);
        String SetMIDIInputType(midi_input_type_t MidiInputType, uint uiSamplerChannel);
        String SetMIDIInputPort(String MIDIInputPort, uint uiSamplerchannel);
        String SetMIDIInputChannel(uint MIDIChannel, uint uiSamplerChannel);
        String SetVolume(double Volume, uint uiSamplerChannel);
        String ResetChannel(uint uiSamplerChannel);
        String SubscribeNotification(uint UDPPort);
        String UnsubscribeNotification(String SessionID);
        void   AnswerClient(String ReturnMessage);
    protected:
        int            hSocket;
        sockaddr_in    SocketAddress;
        Sampler*       pSampler;

        int Main(); ///< Implementation of virtual method from class Thread
    private:
        /**
         * Converts a result_t structure into a valid LSCP answer message.
         */
        inline String ConvertResult(result_t result) {
            switch (result.type) {
                case result_type_success: {
                    return "OK\r\n";
                }
                case result_type_warning: {
                    std::stringstream ss;
                    ss << "WRN:" << result.code << ":" << result.message << "\r\n";
                    return ss.str();
                }
                case result_type_error: {
                    std::stringstream ss;
                    ss << "ERR:" << result.code << ":" << result.message << "\r\n";
                    return ss.str();
                }
            }
        }

        template<class T> inline String ToString(T o) {
            std::stringstream ss;
            ss << o;
            return ss.str();
        }
};

#endif // __LSCPSERVER_H_
