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

/* Note: don't forget to run 'make parser' after you changed this file, */
/*       otherwise the parser will not be regenerated!                  */

%{

#include "lscpparser.h"
#include "lscpserver.h"
#include "lscpevent.h"

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
%token <String> STRINGVAL
%token SP LF CR HASH EQ
%token ADD GET CREATE DESTROY LIST LOAD NON_MODAL REMOVE SET SUBSCRIBE UNSUBSCRIBE RESET ECHO QUIT
%token CHANNEL NOTIFICATION
%token AVAILABLE_ENGINES AVAILABLE_AUDIO_OUTPUT_DRIVERS CHANNELS INFO BUFFER_FILL STREAM_COUNT VOICE_COUNT
%token INSTRUMENT ENGINE
%token AUDIO_OUTPUT_CHANNEL AUDIO_OUTPUT_CHANNEL_PARAMETER AUDIO_OUTPUT_DEVICE AUDIO_OUTPUT_DEVICES AUDIO_OUTPUT_DEVICE_PARAMETER AUDIO_OUTPUT_DRIVER AUDIO_OUTPUT_DRIVER_PARAMETER AUDIO_OUTPUT_TYPE MIDI_INPUT MIDI_INPUT_TYPE MIDI_INPUT_PORT MIDI_INPUT_CHANNEL VOLUME
%token MIDI_INPUT_DRIVER MIDI_INPUT_DRIVER_PARAMETER AVAILABLE_MIDI_INPUT_DRIVERS MIDI_INPUT_DEVICE MIDI_INPUT_DEVICES MIDI_INPUT_DEVICE_PARAMETER MIDI_INPUT_PORT_PARAMETER
%token BYTES PERCENTAGE
%token MISCELLANEOUS

%type <Dotnum> volume boolean
%type <Number> sampler_channel instrument_index audio_output_channel audio_output_device midi_input_channel midi_input_port midi_input_device
%type <String> string param_val filename engine_name command create_instruction destroy_instruction get_instruction list_instruction load_instruction set_chan_instruction load_instr_args load_engine_args audio_output_type midi_input_type set_instruction subscribe_event unsubscribe_event
%type <FillResponse> buffer_size_type
%type <KeyValList> key_val_list

%start input

%%

//TODO: return more meaningful error messages

input                 : line LF

line                  :  /* epsilon (empty line ignored) */ { return LSCP_DONE; }
                      |  comment  { return LSCP_DONE; }
                      |  command  { LSCPSERVER->AnswerClient($1); return LSCP_DONE; }
                      |  error    { LSCPSERVER->AnswerClient("Err:0:Unknown command.\r\n"); RESTART; return LSCP_SYNTAX_ERROR; }
                      ;

comment               :  HASH
                      |  comment HASH
                      |  comment SP
                      |  comment NUMBER
                      |  comment string
                      ;

command               :  ADD SP CHANNEL                             { $$ = LSCPSERVER->AddChannel();                  }
                      |  GET SP get_instruction                     { $$ = $3;                                        }
                      |  CREATE SP create_instruction               { $$ = $3;                                        }
                      |  DESTROY SP destroy_instruction             { $$ = $3;                                        }
                      |  LIST SP list_instruction                   { $$ = $3;                                        }
                      |  LOAD SP load_instruction                   { $$ = $3;                                        }
                      |  REMOVE SP CHANNEL SP sampler_channel       { $$ = LSCPSERVER->RemoveChannel($5);             }
                      |  SET SP set_instruction                     { $$ = $3;                                        }
                      |  SUBSCRIBE SP subscribe_event               { $$ = $3;                                        }
                      |  UNSUBSCRIBE SP unsubscribe_event           { $$ = $3;                                        }
                      |  RESET SP CHANNEL SP sampler_channel        { $$ = LSCPSERVER->ResetChannel($5);              }
                      |  RESET                                      { $$ = LSCPSERVER->ResetSampler();                }
                      |  QUIT                                       { LSCPSERVER->AnswerClient("Bye!\r\n"); return LSCP_QUIT; }
                      ;

subscribe_event       :  CHANNELS                                   { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_channels); }
                      |  VOICE_COUNT                                { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_voice_count); }
                      |  STREAM_COUNT                               { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_stream_count); }
                      |  BUFFER_FILL                                { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_buffer_fill); }
                      |  INFO                                       { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_info); }
                      |  MISCELLANEOUS                              { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_misc); }
                      ;

unsubscribe_event     :  CHANNELS                                   { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_channels); }
                      |  VOICE_COUNT                                { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_voice_count); }
                      |  STREAM_COUNT                               { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_stream_count); }
                      |  BUFFER_FILL                                { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_buffer_fill); }
                      |  INFO                                       { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_info); }
                      |  MISCELLANEOUS                              { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_misc); }
                      ;

get_instruction       :  AVAILABLE_ENGINES                          { $$ = LSCPSERVER->GetAvailableEngines();       }
                      |  AVAILABLE_MIDI_INPUT_DRIVERS               { $$ = LSCPSERVER->GetAvailableMidiInputDrivers();       }
                      |  MIDI_INPUT_DRIVER SP INFO SP string        { $$ = LSCPSERVER->GetMidiInputDriverInfo($5);       }
                      |  MIDI_INPUT_DRIVER_PARAMETER SP INFO SP string SP string     { $$ = LSCPSERVER->GetMidiInputDriverParameterInfo($5, $7);       }
                      |  MIDI_INPUT_DRIVER_PARAMETER SP INFO SP string SP string SP key_val_list    { $$ = LSCPSERVER->GetMidiInputDriverParameterInfo($5, $7, $9);       }
                      |  AVAILABLE_AUDIO_OUTPUT_DRIVERS                                             { $$ = LSCPSERVER->GetAvailableAudioOutputDrivers();       }
                      |  AUDIO_OUTPUT_DRIVER SP INFO SP string                                      { $$ = LSCPSERVER->GetAudioOutputDriverInfo($5);       }
                      |  AUDIO_OUTPUT_DRIVER_PARAMETER SP INFO SP string SP string                  { $$ = LSCPSERVER->GetAudioOutputDriverParameterInfo($5, $7);       }
                      |  AUDIO_OUTPUT_DRIVER_PARAMETER SP INFO SP string SP string SP key_val_list  { $$ = LSCPSERVER->GetAudioOutputDriverParameterInfo($5, $7, $9);       }
                      |  AUDIO_OUTPUT_DEVICES                                                       { $$ = LSCPSERVER->GetAudioOutputDeviceCount();       }
                      |  MIDI_INPUT_DEVICES                                                         { $$ = LSCPSERVER->GetMidiInputDeviceCount();       }
                      |  AUDIO_OUTPUT_DEVICE SP INFO SP NUMBER                                      { $$ = LSCPSERVER->GetAudioOutputDeviceInfo($5);       }
                      |  MIDI_INPUT_DEVICE SP INFO SP NUMBER                                        { $$ = LSCPSERVER->GetMidiInputDeviceInfo($5);       }
                      |  MIDI_INPUT_PORT SP INFO SP NUMBER SP NUMBER                                { $$ = LSCPSERVER->GetMidiInputPortInfo($5, $7);       }
                      |  MIDI_INPUT_PORT_PARAMETER SP INFO SP NUMBER SP NUMBER SP string            { $$ = LSCPSERVER->GetMidiInputPortParameterInfo($5, $7, $9);       }
                      |  AUDIO_OUTPUT_CHANNEL SP INFO SP NUMBER SP NUMBER                           { $$ = LSCPSERVER->GetAudioOutputChannelInfo($5, $7);       }
                      |  AUDIO_OUTPUT_CHANNEL_PARAMETER SP INFO SP NUMBER SP NUMBER SP string       { $$ = LSCPSERVER->GetAudioOutputChannelParameterInfo($5, $7, $9);       }
                      |  CHANNELS                                                                   { $$ = LSCPSERVER->GetChannels();       }
                      |  CHANNEL SP INFO SP sampler_channel                                         { $$ = LSCPSERVER->GetChannelInfo($5);       }
                      |  CHANNEL SP BUFFER_FILL SP buffer_size_type SP sampler_channel              { $$ = LSCPSERVER->GetBufferFill($5, $7);       }
                      |  CHANNEL SP STREAM_COUNT SP sampler_channel                                 { $$ = LSCPSERVER->GetStreamCount($5);       }
                      |  CHANNEL SP VOICE_COUNT SP sampler_channel                                  { $$ = LSCPSERVER->GetVoiceCount($5);       }
                      |  ENGINE SP INFO SP engine_name                                              { $$ = LSCPSERVER->GetEngineInfo($5);       }
                      ;

set_instruction       :  AUDIO_OUTPUT_DEVICE_PARAMETER SP NUMBER SP string EQ param_val             { $$ = LSCPSERVER->SetAudioOutputDeviceParameter($3, $5, $7);       }
                      |  AUDIO_OUTPUT_CHANNEL_PARAMETER SP NUMBER SP NUMBER SP string EQ param_val  { $$ = LSCPSERVER->SetAudioOutputChannelParameter($3, $5, $7, $9);       }
                      |  MIDI_INPUT_DEVICE_PARAMETER SP NUMBER SP string EQ param_val               { $$ = LSCPSERVER->SetMidiInputDeviceParameter($3, $5, $7);       }
                      |  MIDI_INPUT_PORT_PARAMETER SP NUMBER SP NUMBER SP string EQ param_val       { $$ = LSCPSERVER->SetMidiInputPortParameter($3, $5, $7, $9);       }
                      |  CHANNEL SP set_chan_instruction                                            { $$ = $3;                                                         }
                      |  ECHO SP boolean                                                            { $$ = LSCPSERVER->SetEcho((yyparse_param_t*) yyparse_param, $3);  }
                      ;

create_instruction    :  AUDIO_OUTPUT_DEVICE SP string SP key_val_list { $$ = LSCPSERVER->CreateAudioOutputDevice($3,$5); }
                      |  AUDIO_OUTPUT_DEVICE SP string                 { $$ = LSCPSERVER->CreateAudioOutputDevice($3);    }
                      |  MIDI_INPUT_DEVICE SP string SP key_val_list   { $$ = LSCPSERVER->CreateMidiInputDevice($3,$5);   }
                      |  MIDI_INPUT_DEVICE SP string                   { $$ = LSCPSERVER->CreateMidiInputDevice($3);      }
                      ;

destroy_instruction   :  AUDIO_OUTPUT_DEVICE SP NUMBER  { $$ = LSCPSERVER->DestroyAudioOutputDevice($3);       }
                      |  MIDI_INPUT_DEVICE SP NUMBER    { $$ = LSCPSERVER->DestroyMidiInputDevice($3);         }
                      ;

load_instruction      :  INSTRUMENT SP load_instr_args  { $$ = $3; }
                      |  ENGINE SP load_engine_args     { $$ = $3; }
                      ;

set_chan_instruction  :  AUDIO_OUTPUT_DEVICE SP sampler_channel SP audio_output_device                            { $$ = LSCPSERVER->SetAudioOutputDevice($5, $3);      }
                      |  AUDIO_OUTPUT_CHANNEL SP sampler_channel SP audio_output_channel SP audio_output_channel  { $$ = LSCPSERVER->SetAudioOutputChannel($5, $7, $3); }
                      |  AUDIO_OUTPUT_TYPE SP sampler_channel SP audio_output_type                                { $$ = LSCPSERVER->SetAudioOutputType($5, $3);        }
                      |  MIDI_INPUT SP sampler_channel SP midi_input_device SP midi_input_port SP midi_input_channel  { $$ = LSCPSERVER->SetMIDIInput($5, $7, $9, $3);  }
                      |  MIDI_INPUT_DEVICE SP sampler_channel SP midi_input_device                                { $$ = LSCPSERVER->SetMIDIInputDevice($5, $3);        }
                      |  MIDI_INPUT_PORT SP sampler_channel SP midi_input_port                                    { $$ = LSCPSERVER->SetMIDIInputPort($5, $3);          }
                      |  MIDI_INPUT_CHANNEL SP sampler_channel SP midi_input_channel                              { $$ = LSCPSERVER->SetMIDIInputChannel($5, $3);       }
                      |  MIDI_INPUT_TYPE SP sampler_channel SP midi_input_type                                    { $$ = LSCPSERVER->SetMIDIInputType($5, $3);          }
                      |  VOLUME SP sampler_channel SP volume                                                      { $$ = LSCPSERVER->SetVolume($5, $3);                 }
                      ;

key_val_list          :  string EQ param_val                  { $$[$1] = $3;          }
                      |  key_val_list SP string EQ param_val  { $$ = $1; $$[$3] = $5; }
                      ;

buffer_size_type      :  BYTES       { $$ = fill_response_bytes;      }
                      |  PERCENTAGE  { $$ = fill_response_percentage; }
                      ;

list_instruction      :  AUDIO_OUTPUT_DEVICES  { $$ = LSCPSERVER->GetAudioOutputDevices(); }
                      |  MIDI_INPUT_DEVICES    { $$ = LSCPSERVER->GetMidiInputDevices();   }
                      |  CHANNELS              { $$ = LSCPSERVER->ListChannels();          }
                      ;

load_instr_args       :  filename SP instrument_index SP sampler_channel  { $$ = LSCPSERVER->LoadInstrument($1, $3, $5);       }
                      |  NON_MODAL SP filename SP instrument_index SP sampler_channel  { $$ = LSCPSERVER->LoadInstrument($3, $5, $7, true);       }
                      ;

load_engine_args      :  engine_name SP sampler_channel  { $$ = LSCPSERVER->LoadEngine($1, $3);       }
                      ;

audio_output_device   :  NUMBER
                      ;

audio_output_channel  :  NUMBER
                      ;

audio_output_type     :  string
                      ;

midi_input_device     :  NUMBER
                      ;

midi_input_port       :  NUMBER
                      ;

midi_input_channel    :  NUMBER
                      ;

midi_input_type       :  string
                      ;

volume                :  DOTNUM
                      |  NUMBER  { $$ = $1; }
                      ;

sampler_channel       :  NUMBER
                      ;

instrument_index      :  NUMBER
                      ;

engine_name           :  string
                      ;

filename              :  STRINGVAL
                      ;

param_val             :  STRINGVAL                { $$ = $1;                                             }
                      |  NUMBER                   { std::stringstream ss; ss << $1; $$ = ss.str();       }
                      |  DOTNUM                   { std::stringstream ss; ss << $1; $$ = ss.str();       }
                      ;

boolean               :  NUMBER  { $$ = $1; }
                      |  string  { $$ = -1; }
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
    // reset lookahead symbol
    yyclearin;
}
