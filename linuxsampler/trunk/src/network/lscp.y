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

%{

#include "lscpparser.h"
#include "lscpserver.h"

// as we need an reentrant scanner, we have to pass the pointer to the scanner with each yylex() call
#define YYLEX_PARAM ((yyparse_param_t*) yyparse_param)->pScanner

// to save us typing work in the rules action definitions
#define LSCPSERVER ((yyparse_param_t*) yyparse_param)->pServer

// clears input buffer and restarts scanner.
void restart(yyparse_param_t* pparam, int& yychar);
#define RESTART restart((yyparse_param_t*) YYPARSE_PARAM, yychar)

// external reference to the main scanner function yylex()
extern YY_DECL;

// external reference to restart the lex scanner
extern void yyrestart(FILE* input_file, yyscan_t yyscanner);

// we provide our own version of yyerror() so we don't have to link against the yacc library
void yyerror(const char* s);

%}

// reentrant parser
%pure_parser

%token <Char>   CHAR
%token <Dotnum> DOTNUM
%token <Number> NUMBER
%token SP LF CR
%token ADD GET LOAD REMOVE SET SUBSCRIBE UNSUBSCRIBE RESET QUIT
%token CHANNEL NOTIFICATION
%token AVAILABLE_ENGINES CHANNELS INFO BUFFER_FILL STREAM_COUNT VOICE_COUNT
%token INSTRUMENT ENGINE
%token AUDIO_OUTPUT_CHANNEL AUDIO_OUTPUT_TYPE MIDI_INPUT_PORT MIDI_INPUT_CHANNEL MIDI_INPUT_TYPE VOLUME
%token BYTES PERCENTAGE
%token ALSA JACK

%type <Dotnum> volume
%type <Number> sampler_channel instrument_index udp_port audio_output_channel midi_input_channel
%type <String> string alpha_num_string filename engine_name session_id midi_input_port command get_instruction load_instruction set_chan_instruction load_instr_args load_engine_args
%type <FillResponse> buffer_size_type
%type <AudioOutput> audio_output_type
%type <MidiInput> midi_input_type

%start input

%%

//TODO: return more meaningful error messages

input                 :  line
                      |  input LF line
                      |  input CR LF line
                      ;

line                  :  /* epsilon (empty line ignored) */
                      |  command  { LSCPSERVER->AnswerClient($1); }
                      |  error    { LSCPSERVER->AnswerClient("Err:0:Unknown command.\r\n"); RESTART; return LSCP_SYNTAX_ERROR; }
                      ;

command               :  ADD SP CHANNEL                             { $$ = LSCPSERVER->AddChannel();                  }
                      |  GET SP get_instruction                     { $$ = $3;                                        }
                      |  LOAD SP load_instruction                   { $$ = $3;                                        }
                      |  REMOVE SP CHANNEL SP sampler_channel       { $$ = LSCPSERVER->RemoveChannel($5);             }
                      |  SET SP CHANNEL SP set_chan_instruction     { $$ = $5;                                        }
                      |  SUBSCRIBE SP NOTIFICATION SP udp_port      { $$ = LSCPSERVER->SubscribeNotification($5);     }
                      |  UNSUBSCRIBE SP NOTIFICATION SP session_id  { $$ = LSCPSERVER->UnsubscribeNotification($5);   }
                      |  RESET SP CHANNEL SP sampler_channel        { $$ = LSCPSERVER->ResetChannel($5);              }
                      |  QUIT                                       { LSCPSERVER->AnswerClient("Bye!\r\n"); return 0; }
                      ;

get_instruction       :  AVAILABLE_ENGINES                                              { $$ = LSCPSERVER->GetAvailableEngines(); }
                      |  CHANNELS                                                       { $$ = LSCPSERVER->GetChannels();         }
                      |  CHANNEL SP INFO SP sampler_channel                             { $$ = LSCPSERVER->GetChannelInfo($5);    }
                      |  CHANNEL SP BUFFER_FILL SP buffer_size_type SP sampler_channel  { $$ = LSCPSERVER->GetBufferFill($5, $7); }
                      |  CHANNEL SP STREAM_COUNT SP sampler_channel                     { $$ = LSCPSERVER->GetStreamCount($5);    }
                      |  CHANNEL SP VOICE_COUNT SP sampler_channel                      { $$ = LSCPSERVER->GetVoiceCount($5);     }
                      |  ENGINE SP INFO SP engine_name                                  { $$ = LSCPSERVER->GetEngineInfo($5);     }
                      ;

load_instruction      :  INSTRUMENT SP load_instr_args  { $$ = $3; }
                      |  ENGINE SP load_engine_args     { $$ = $3; }
                      ;

set_chan_instruction  :  AUDIO_OUTPUT_CHANNEL SP sampler_channel SP audio_output_channel  { $$ = LSCPSERVER->SetAudioOutputChannel($5, $3); }
                      |  AUDIO_OUTPUT_TYPE SP sampler_channel SP audio_output_type        { $$ = LSCPSERVER->SetAudioOutputType($5, $3);    }
                      |  MIDI_INPUT_PORT SP sampler_channel SP midi_input_port            { $$ = LSCPSERVER->SetMIDIInputPort($5, $3);      }
                      |  MIDI_INPUT_CHANNEL SP sampler_channel SP midi_input_channel      { $$ = LSCPSERVER->SetMIDIInputChannel($5, $3);   }
                      |  MIDI_INPUT_TYPE SP sampler_channel SP midi_input_type            { $$ = LSCPSERVER->SetMIDIInputType($5, $3);      }
                      |  VOLUME SP sampler_channel SP volume                              { $$ = LSCPSERVER->SetVolume($5, $3);             }
                      ;

buffer_size_type      :  BYTES       { $$ = fill_response_bytes;      }
                      |  PERCENTAGE  { $$ = fill_response_percentage; }
                      ;

load_instr_args       :  filename SP instrument_index SP sampler_channel  { $$ = LSCPSERVER->LoadInstrument($1, $3, $5); }
                      ;

load_engine_args      :  engine_name SP sampler_channel  { $$ = LSCPSERVER->LoadEngine($1, $3); }
                      ;

audio_output_type     :  ALSA  { $$ = audio_output_type_alsa; }
                      |  JACK  { $$ = audio_output_type_jack; }
                      ;

midi_input_type       :  ALSA  { $$ = midi_input_type_alsa; }
                      ;

volume                :  DOTNUM
                      |  NUMBER  { $$ = $1; }
                      ;

sampler_channel       :  NUMBER
                      ;

instrument_index      :  NUMBER
                      ;

udp_port              :  NUMBER
                      ;

audio_output_channel  :  NUMBER
                      ;

midi_input_channel    :  NUMBER
                      ;

session_id            :  alpha_num_string
                      ;

engine_name           :  string
                      ;

midi_input_port       :  alpha_num_string
                      ;

filename              :  alpha_num_string
                      |  filename SP alpha_num_string  { $$ = $1 + ' ' + $3; }
                      ;

alpha_num_string      :  string                   { $$ = $1;                                             }
                      |  NUMBER                   { std::stringstream ss; ss << $1; $$ = ss.str();       }
                      |  alpha_num_string string  { $$ = $1 + $2;                                        }
                      |  alpha_num_string NUMBER  { std::stringstream ss; ss << $1 << $2; $$ = ss.str(); }
                      ;

string                :  CHAR          { std::string s; s = $1; $$ = s; }
                      |  string CHAR   { $$ = $1 + $2;                  }
                      ;

%%

/**
 * Will be called when an error occured (usually syntax error).
 */
void yyerror(const char* s) {
    dmsg(2,("LSCPParser: %s\n", s));
}

/**
 * Clears input buffer and restarts scanner.
 */
void restart(yyparse_param_t* pparam, int& yychar) {
    // restart scanner
    yyrestart(stdin, pparam->pScanner);
    // flush input buffer
    static char buf[1024];
    while(recv(hSession, buf, 1024, MSG_DONTWAIT) > 0);
    // reset lookahead symbol
    yyclearin;
}
