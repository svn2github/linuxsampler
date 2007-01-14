/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
 *   Copyright (C) 2005, 2006 Christian Schoenebeck                        *
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

/* CAUTION: !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/*                                                                         */
/*     don't forget to run 'make parser' after you changed this file,      */
/*     otherwise the parser will not be regenerated !                      */
/*                                                                         */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

%{

#include "lscpparser.h"
#include "lscpserver.h"
#include "lscpevent.h"

// to save us typing work in the rules action definitions
#define LSCPSERVER ((yyparse_param_t*) yyparse_param)->pServer

// clears input buffer
void restart(yyparse_param_t* pparam, int& yychar);
#define RESTART restart((yyparse_param_t*) YYPARSE_PARAM, yychar)

// we provide our own version of yyerror() so we don't have to link against the yacc library
void yyerror(const char* s);

static char buf[1024]; // input buffer to feed the parser with new characters
static int bytes = 0;  // current number of characters in the input buffer
static int ptr   = 0;  // current position in the input buffer

// external reference to the function which actually reads from the socket
extern int GetLSCPCommand( void *buf, int max_size);

// custom scanner function which reads from the socket
int yylex(YYSTYPE* yylval) {
    // check if we have to read new characters
    if (ptr >= bytes) {
        bytes = GetLSCPCommand(buf, 1023);
        ptr   = 0;
        if (bytes < 0) {
            bytes = 0;
            return 0;
        }
    }
    return (int) buf[ptr++];
}

%}

// reentrant parser
%pure_parser

%type <Char> char digit
%type <Dotnum> dotnum volume_value boolean
%type <Number> number sampler_channel instrument_index fx_send_id audio_channel_index device_index midi_input_channel_index midi_input_port_index midi_map midi_bank midi_prog midi_ctrl
%type <String> string text stringval digits param_val_list param_val filename map_name entry_name fx_send_name engine_name command add_instruction create_instruction destroy_instruction get_instruction list_instruction load_instruction set_chan_instruction load_instr_args load_engine_args audio_output_type_name midi_input_type_name remove_instruction unmap_instruction set_instruction subscribe_event unsubscribe_event map_instruction reset_instruction clear_instruction
%type <FillResponse> buffer_size_type
%type <KeyValList> key_val_list
%type <LoadMode> instr_load_mode

%start input

%%

//TODO: return more meaningful error messages

/*
  The LSCP specification document input file (Documentation/lscp.xml) is
  automatically updated with this file using the scripts/update_grammar.pl
  script. Do not modify or delete the GRAMMAR_BNF_BEGIN and GRAMMAR_BNF_END
  lines !
*/

// GRAMMAR_BNF_BEGIN - do NOT delete or modify this line !!!

input                 : line LF
                      | line CR LF
                      ;

line                  :  /* epsilon (empty line ignored) */ { return LSCP_DONE; }
                      |  comment  { return LSCP_DONE; }
                      |  command  { LSCPSERVER->AnswerClient($1); return LSCP_DONE; }
                      |  error    { LSCPSERVER->AnswerClient("ERR:0:Unknown command.\r\n"); RESTART; return LSCP_SYNTAX_ERROR; }
                      ;

comment               :  '#'
                      |  comment '#'
                      |  comment SP
                      |  comment number
                      |  comment string
                      ;

command               :  ADD SP add_instruction                { $$ = $3;                                                }
                      |  MAP SP map_instruction                { $$ = $3;                                                }
                      |  UNMAP SP unmap_instruction            { $$ = $3;                                                }
                      |  GET SP get_instruction                { $$ = $3;                                                }
                      |  CREATE SP create_instruction          { $$ = $3;                                                }
                      |  DESTROY SP destroy_instruction        { $$ = $3;                                                }
                      |  LIST SP list_instruction              { $$ = $3;                                                }
                      |  LOAD SP load_instruction              { $$ = $3;                                                }
                      |  REMOVE SP remove_instruction          { $$ = $3;                                                }
                      |  SET SP set_instruction                { $$ = $3;                                                }
                      |  SUBSCRIBE SP subscribe_event          { $$ = $3;                                                }
                      |  UNSUBSCRIBE SP unsubscribe_event      { $$ = $3;                                                }
                      |  SELECT SP text                        { $$ = LSCPSERVER->QueryDatabase($3);                     }
                      |  RESET SP reset_instruction            { $$ = $3;                                                }
                      |  CLEAR SP clear_instruction            { $$ = $3;                                                }
                      |  RESET                                 { $$ = LSCPSERVER->ResetSampler();                        }
                      |  QUIT                                  { LSCPSERVER->AnswerClient("Bye!\r\n"); return LSCP_QUIT; }
                      ;

add_instruction       :  CHANNEL                               { $$ = LSCPSERVER->AddChannel();                          }
                      |  MIDI_INSTRUMENT_MAP                   { $$ = LSCPSERVER->AddMidiInstrumentMap();                }
                      |  MIDI_INSTRUMENT_MAP SP map_name       { $$ = LSCPSERVER->AddMidiInstrumentMap($3);              }
                      ;

subscribe_event       :  AUDIO_OUTPUT_DEVICE_COUNT             { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_audio_device_count);   }
                      |  AUDIO_OUTPUT_DEVICE_INFO              { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_audio_device_info);    }
                      |  MIDI_INPUT_DEVICE_COUNT               { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_device_count);    }
                      |  MIDI_INPUT_DEVICE_INFO                { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_device_info);     }
                      |  CHANNEL_COUNT                         { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_channel_count);        }
                      |  VOICE_COUNT                           { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_voice_count);          }
                      |  STREAM_COUNT                          { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_stream_count);         }
                      |  BUFFER_FILL                           { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_buffer_fill);          }
                      |  CHANNEL_INFO                          { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_channel_info);         }
                      |  MIDI_INSTRUMENT_MAP_COUNT             { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_instr_map_count); }
                      |  MIDI_INSTRUMENT_MAP_INFO              { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_instr_map_info);  }
                      |  MIDI_INSTRUMENT_COUNT                 { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_instr_count);     }
                      |  MIDI_INSTRUMENT_INFO                  { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_instr_info);      }
                      |  MISCELLANEOUS                         { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_misc);                 }
                      |  TOTAL_VOICE_COUNT                     { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_total_voice_count);    }
                      ;

unsubscribe_event     :  AUDIO_OUTPUT_DEVICE_COUNT             { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_audio_device_count);   }
                      |  AUDIO_OUTPUT_DEVICE_INFO              { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_audio_device_info);    }
                      |  MIDI_INPUT_DEVICE_COUNT               { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_device_count);    }
                      |  MIDI_INPUT_DEVICE_INFO                { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_device_info);     }
                      |  CHANNEL_COUNT                         { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_channel_count);        }
                      |  VOICE_COUNT                           { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_voice_count);          }
                      |  STREAM_COUNT                          { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_stream_count);         }
                      |  BUFFER_FILL                           { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_buffer_fill);          }
                      |  CHANNEL_INFO                          { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_channel_info);         }
                      |  MIDI_INSTRUMENT_MAP_COUNT             { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_instr_map_count); }
                      |  MIDI_INSTRUMENT_MAP_INFO              { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_instr_map_info);  }
                      |  MIDI_INSTRUMENT_COUNT                 { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_instr_count);     }
                      |  MIDI_INSTRUMENT_INFO                  { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_instr_info);      }
                      |  MISCELLANEOUS                         { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_misc);                 }
                      |  TOTAL_VOICE_COUNT                     { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_total_voice_count);    }
                      ;

map_instruction       :  MIDI_INSTRUMENT SP midi_map SP midi_bank SP midi_prog SP engine_name SP filename SP instrument_index SP volume_value { $$ = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping($3,$5,$7,$9,$11,$13,$15,MidiInstrumentMapper::VOID,""); }
                      |  MIDI_INSTRUMENT SP midi_map SP midi_bank SP midi_prog SP engine_name SP filename SP instrument_index SP volume_value SP instr_load_mode { $$ = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping($3,$5,$7,$9,$11,$13,$15,$17,""); }
                      |  MIDI_INSTRUMENT SP midi_map SP midi_bank SP midi_prog SP engine_name SP filename SP instrument_index SP volume_value SP entry_name { $$ = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping($3,$5,$7,$9,$11,$13,$15,MidiInstrumentMapper::VOID,$17); }
                      |  MIDI_INSTRUMENT SP midi_map SP midi_bank SP midi_prog SP engine_name SP filename SP instrument_index SP volume_value SP instr_load_mode SP entry_name { $$ = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping($3,$5,$7,$9,$11,$13,$15,$17,$19); }
                      ;

unmap_instruction     :  MIDI_INSTRUMENT SP midi_map SP midi_bank SP midi_prog  { $$ = LSCPSERVER->RemoveMIDIInstrumentMapping($3,$5,$7); }
                      ;

remove_instruction    :  CHANNEL SP sampler_channel       { $$ = LSCPSERVER->RemoveChannel($3);             }
                      |  MIDI_INSTRUMENT_MAP SP midi_map  { $$ = LSCPSERVER->RemoveMidiInstrumentMap($3);   }
                      |  MIDI_INSTRUMENT_MAP SP ALL       { $$ = LSCPSERVER->RemoveAllMidiInstrumentMaps(); }
                      ;

get_instruction       :  AVAILABLE_ENGINES                                                          { $$ = LSCPSERVER->GetAvailableEngines();                          }
                      |  AVAILABLE_MIDI_INPUT_DRIVERS                                               { $$ = LSCPSERVER->GetAvailableMidiInputDrivers();                 }
                      |  MIDI_INPUT_DRIVER SP INFO SP string                                        { $$ = LSCPSERVER->GetMidiInputDriverInfo($5);                     }
                      |  MIDI_INPUT_DRIVER_PARAMETER SP INFO SP string SP string                    { $$ = LSCPSERVER->GetMidiInputDriverParameterInfo($5, $7);        }
                      |  MIDI_INPUT_DRIVER_PARAMETER SP INFO SP string SP string SP key_val_list    { $$ = LSCPSERVER->GetMidiInputDriverParameterInfo($5, $7, $9);    }
                      |  AVAILABLE_AUDIO_OUTPUT_DRIVERS                                             { $$ = LSCPSERVER->GetAvailableAudioOutputDrivers();               }
                      |  AUDIO_OUTPUT_DRIVER SP INFO SP string                                      { $$ = LSCPSERVER->GetAudioOutputDriverInfo($5);                   }
                      |  AUDIO_OUTPUT_DRIVER_PARAMETER SP INFO SP string SP string                  { $$ = LSCPSERVER->GetAudioOutputDriverParameterInfo($5, $7);      }
                      |  AUDIO_OUTPUT_DRIVER_PARAMETER SP INFO SP string SP string SP key_val_list  { $$ = LSCPSERVER->GetAudioOutputDriverParameterInfo($5, $7, $9);  }
                      |  AUDIO_OUTPUT_DEVICES                                                       { $$ = LSCPSERVER->GetAudioOutputDeviceCount();                    }
                      |  MIDI_INPUT_DEVICES                                                         { $$ = LSCPSERVER->GetMidiInputDeviceCount();                      }
                      |  AUDIO_OUTPUT_DEVICE SP INFO SP number                                      { $$ = LSCPSERVER->GetAudioOutputDeviceInfo($5);                   }
                      |  MIDI_INPUT_DEVICE SP INFO SP number                                        { $$ = LSCPSERVER->GetMidiInputDeviceInfo($5);                     }
                      |  MIDI_INPUT_PORT SP INFO SP number SP number                                { $$ = LSCPSERVER->GetMidiInputPortInfo($5, $7);                   }
                      |  MIDI_INPUT_PORT_PARAMETER SP INFO SP number SP number SP string            { $$ = LSCPSERVER->GetMidiInputPortParameterInfo($5, $7, $9);      }
                      |  AUDIO_OUTPUT_CHANNEL SP INFO SP number SP number                           { $$ = LSCPSERVER->GetAudioOutputChannelInfo($5, $7);              }
                      |  AUDIO_OUTPUT_CHANNEL_PARAMETER SP INFO SP number SP number SP string       { $$ = LSCPSERVER->GetAudioOutputChannelParameterInfo($5, $7, $9); }
                      |  CHANNELS                                                                   { $$ = LSCPSERVER->GetChannels();                                  }
                      |  CHANNEL SP INFO SP sampler_channel                                         { $$ = LSCPSERVER->GetChannelInfo($5);                             }
                      |  CHANNEL SP BUFFER_FILL SP buffer_size_type SP sampler_channel              { $$ = LSCPSERVER->GetBufferFill($5, $7);                          }
                      |  CHANNEL SP STREAM_COUNT SP sampler_channel                                 { $$ = LSCPSERVER->GetStreamCount($5);                             }
                      |  CHANNEL SP VOICE_COUNT SP sampler_channel                                  { $$ = LSCPSERVER->GetVoiceCount($5);                              }
                      |  ENGINE SP INFO SP engine_name                                              { $$ = LSCPSERVER->GetEngineInfo($5);                              }
                      |  SERVER SP INFO                                                             { $$ = LSCPSERVER->GetServerInfo();                                }
                      |  TOTAL_VOICE_COUNT                                                          { $$ = LSCPSERVER->GetTotalVoiceCount();                                }
                      |  TOTAL_VOICE_COUNT_MAX                                                      { $$ = LSCPSERVER->GetTotalVoiceCountMax();                        }
                      |  MIDI_INSTRUMENTS SP midi_map                                               { $$ = LSCPSERVER->GetMidiInstrumentMappings($3);                  }
                      |  MIDI_INSTRUMENTS SP ALL                                                    { $$ = LSCPSERVER->GetAllMidiInstrumentMappings();                 }
                      |  MIDI_INSTRUMENT SP INFO SP midi_map SP midi_bank SP midi_prog              { $$ = LSCPSERVER->GetMidiInstrumentMapping($5,$7,$9);             }
                      |  MIDI_INSTRUMENT_MAPS                                                       { $$ = LSCPSERVER->GetMidiInstrumentMaps();                        }
                      |  MIDI_INSTRUMENT_MAP SP INFO SP midi_map                                    { $$ = LSCPSERVER->GetMidiInstrumentMap($5);                       }
                      |  FX_SENDS SP sampler_channel                                                { $$ = LSCPSERVER->GetFxSends($3);                                 }
                      |  FX_SEND SP INFO SP sampler_channel SP fx_send_id                           { $$ = LSCPSERVER->GetFxSendInfo($5,$7);                           }
                      |  VOLUME                                                                     { $$ = LSCPSERVER->GetGlobalVolume();                              }
                      ;

set_instruction       :  AUDIO_OUTPUT_DEVICE_PARAMETER SP number SP string '=' param_val_list             { $$ = LSCPSERVER->SetAudioOutputDeviceParameter($3, $5, $7);      }
                      |  AUDIO_OUTPUT_CHANNEL_PARAMETER SP number SP number SP string '=' param_val_list  { $$ = LSCPSERVER->SetAudioOutputChannelParameter($3, $5, $7, $9); }
                      |  MIDI_INPUT_DEVICE_PARAMETER SP number SP string '=' param_val_list               { $$ = LSCPSERVER->SetMidiInputDeviceParameter($3, $5, $7);        }
                      |  MIDI_INPUT_PORT_PARAMETER SP number SP number SP string '=' param_val_list       { $$ = LSCPSERVER->SetMidiInputPortParameter($3, $5, $7, $9);      }
                      |  CHANNEL SP set_chan_instruction                                                  { $$ = $3;                                                         }
                      |  MIDI_INSTRUMENT_MAP SP NAME SP midi_map SP map_name                              { $$ = LSCPSERVER->SetMidiInstrumentMapName($5, $7);               }
                      |  FX_SEND SP AUDIO_OUTPUT_CHANNEL SP sampler_channel SP fx_send_id SP audio_channel_index SP audio_channel_index  { $$ = LSCPSERVER->SetFxSendAudioOutputChannel($5,$7,$9,$11); }
                      |  FX_SEND SP MIDI_CONTROLLER SP sampler_channel SP fx_send_id SP midi_ctrl         { $$ = LSCPSERVER->SetFxSendMidiController($5,$7,$9);              }
                      |  FX_SEND SP LEVEL SP sampler_channel SP fx_send_id SP volume_value                { $$ = LSCPSERVER->SetFxSendLevel($5,$7,$9);                       }
                      |  ECHO SP boolean                                                                  { $$ = LSCPSERVER->SetEcho((yyparse_param_t*) yyparse_param, $3);  }
                      |  VOLUME SP volume_value                                                           { $$ = LSCPSERVER->SetGlobalVolume($3);                            }
                      ;

create_instruction    :  AUDIO_OUTPUT_DEVICE SP string SP key_val_list  { $$ = LSCPSERVER->CreateAudioOutputDevice($3,$5); }
                      |  AUDIO_OUTPUT_DEVICE SP string                  { $$ = LSCPSERVER->CreateAudioOutputDevice($3);    }
                      |  MIDI_INPUT_DEVICE SP string SP key_val_list    { $$ = LSCPSERVER->CreateMidiInputDevice($3,$5);   }
                      |  MIDI_INPUT_DEVICE SP string                    { $$ = LSCPSERVER->CreateMidiInputDevice($3);      }
                      |  FX_SEND SP sampler_channel SP midi_ctrl        { $$ = LSCPSERVER->CreateFxSend($3,$5);            }
                      |  FX_SEND SP sampler_channel SP midi_ctrl SP fx_send_name  { $$ = LSCPSERVER->CreateFxSend($3,$5,$7); }
                      ;

reset_instruction     :  CHANNEL SP sampler_channel  { $$ = LSCPSERVER->ResetChannel($3); }
                      ;

clear_instruction     :  MIDI_INSTRUMENTS SP midi_map   { $$ = LSCPSERVER->ClearMidiInstrumentMappings($3);  }
                      |  MIDI_INSTRUMENTS SP ALL        { $$ = LSCPSERVER->ClearAllMidiInstrumentMappings(); }
                      ;

destroy_instruction   :  AUDIO_OUTPUT_DEVICE SP number  { $$ = LSCPSERVER->DestroyAudioOutputDevice($3); }
                      |  MIDI_INPUT_DEVICE SP number    { $$ = LSCPSERVER->DestroyMidiInputDevice($3);   }
                      |  FX_SEND SP sampler_channel SP fx_send_id  { $$ = LSCPSERVER->DestroyFxSend($3,$5); }
                      ;

load_instruction      :  INSTRUMENT SP load_instr_args  { $$ = $3; }
                      |  ENGINE SP load_engine_args     { $$ = $3; }
                      ;

set_chan_instruction  :  AUDIO_OUTPUT_DEVICE SP sampler_channel SP device_index                                              { $$ = LSCPSERVER->SetAudioOutputDevice($5, $3);      }
                      |  AUDIO_OUTPUT_CHANNEL SP sampler_channel SP audio_channel_index SP audio_channel_index               { $$ = LSCPSERVER->SetAudioOutputChannel($5, $7, $3); }
                      |  AUDIO_OUTPUT_TYPE SP sampler_channel SP audio_output_type_name                                      { $$ = LSCPSERVER->SetAudioOutputType($5, $3);        }
                      |  MIDI_INPUT SP sampler_channel SP device_index SP midi_input_port_index SP midi_input_channel_index  { $$ = LSCPSERVER->SetMIDIInput($5, $7, $9, $3);      }
                      |  MIDI_INPUT_DEVICE SP sampler_channel SP device_index                                                { $$ = LSCPSERVER->SetMIDIInputDevice($5, $3);        }
                      |  MIDI_INPUT_PORT SP sampler_channel SP midi_input_port_index                                         { $$ = LSCPSERVER->SetMIDIInputPort($5, $3);          }
                      |  MIDI_INPUT_CHANNEL SP sampler_channel SP midi_input_channel_index                                   { $$ = LSCPSERVER->SetMIDIInputChannel($5, $3);       }
                      |  MIDI_INPUT_TYPE SP sampler_channel SP midi_input_type_name                                          { $$ = LSCPSERVER->SetMIDIInputType($5, $3);          }
                      |  VOLUME SP sampler_channel SP volume_value                                                           { $$ = LSCPSERVER->SetVolume($5, $3);                 }
                      |  MUTE SP sampler_channel SP boolean                                                                  { $$ = LSCPSERVER->SetChannelMute($5, $3);            }
                      |  SOLO SP sampler_channel SP boolean                                                                  { $$ = LSCPSERVER->SetChannelSolo($5, $3);            }
                      |  MIDI_INSTRUMENT_MAP SP sampler_channel SP midi_map                                                  { $$ = LSCPSERVER->SetChannelMap($3, $5);             }
                      |  MIDI_INSTRUMENT_MAP SP sampler_channel SP NONE                                                      { $$ = LSCPSERVER->SetChannelMap($3, -1);             }
                      |  MIDI_INSTRUMENT_MAP SP sampler_channel SP DEFAULT                                                   { $$ = LSCPSERVER->SetChannelMap($3, -2);             }
                      ;

key_val_list          :  string '=' param_val_list                  { $$[$1] = $3;          }
                      |  key_val_list SP string '=' param_val_list  { $$ = $1; $$[$3] = $5; }
                      ;

buffer_size_type      :  BYTES       { $$ = fill_response_bytes;      }
                      |  PERCENTAGE  { $$ = fill_response_percentage; }
                      ;

list_instruction      :  AUDIO_OUTPUT_DEVICES            { $$ = LSCPSERVER->GetAudioOutputDevices();           }
                      |  MIDI_INPUT_DEVICES              { $$ = LSCPSERVER->GetMidiInputDevices();             }
                      |  CHANNELS                        { $$ = LSCPSERVER->ListChannels();                    }
                      |  AVAILABLE_ENGINES               { $$ = LSCPSERVER->ListAvailableEngines();            }
                      |  AVAILABLE_MIDI_INPUT_DRIVERS    { $$ = LSCPSERVER->ListAvailableMidiInputDrivers();   }
                      |  AVAILABLE_AUDIO_OUTPUT_DRIVERS  { $$ = LSCPSERVER->ListAvailableAudioOutputDrivers(); }
                      |  MIDI_INSTRUMENTS SP midi_map    { $$ = LSCPSERVER->ListMidiInstrumentMappings($3);    }
                      |  MIDI_INSTRUMENTS SP ALL         { $$ = LSCPSERVER->ListAllMidiInstrumentMappings();   }
                      |  MIDI_INSTRUMENT_MAPS            { $$ = LSCPSERVER->ListMidiInstrumentMaps();          }
                      |  FX_SENDS SP sampler_channel     { $$ = LSCPSERVER->ListFxSends($3);                   }
                      ;

load_instr_args       :  filename SP instrument_index SP sampler_channel               { $$ = LSCPSERVER->LoadInstrument($1, $3, $5);       }
                      |  NON_MODAL SP filename SP instrument_index SP sampler_channel  { $$ = LSCPSERVER->LoadInstrument($3, $5, $7, true); }
                      ;

load_engine_args      :  engine_name SP sampler_channel  { $$ = LSCPSERVER->SetEngineType($1, $3); }
                      ;

instr_load_mode       :  ON_DEMAND       { $$ = MidiInstrumentMapper::ON_DEMAND;      }
                      |  ON_DEMAND_HOLD  { $$ = MidiInstrumentMapper::ON_DEMAND_HOLD; }
                      |  PERSISTENT      { $$ = MidiInstrumentMapper::PERSISTENT;     }
                      ;

device_index              :  number
                          ;

audio_channel_index       :  number
                          ;

audio_output_type_name    :  string
                          ;

midi_input_port_index     :  number
                          ;

midi_input_channel_index  :  number
                          |  ALL  { $$ = 16; }
                          ;

midi_input_type_name      :  string
                          ;

midi_map                  :  number
                          ;

midi_bank                 :  number
                          ;

midi_prog                 :  number
                          ;

midi_ctrl                 :  number
                          ;

volume_value              :  dotnum
                          |  number  { $$ = $1; }
                          ;

sampler_channel           :  number
                          ;

instrument_index          :  number
                          ;

fx_send_id                :  number
                          ;

engine_name               :  string
                          ;

filename                  :  stringval
                          ;

map_name                  :  stringval
                          ;

entry_name                :  stringval
                          ;

fx_send_name              :  stringval
                          ;

param_val_list            :  param_val
                          |  param_val_list','param_val  { $$ = $1 + "," + $3; }
                          ;

param_val                 :  string
                          |  stringval
                          |  number            { std::stringstream ss; ss << "\'" << $1 << "\'"; $$ = ss.str(); }
                          |  dotnum            { std::stringstream ss; ss << "\'" << $1 << "\'"; $$ = ss.str(); }
                          ;

// GRAMMAR_BNF_END - do NOT delete or modify this line !!!


// atomic variable symbol rules

boolean               :  number  { $$ = $1; }
                      |  string  { $$ = -1; }
                      ;

string                :  char          { std::string s; s = $1; $$ = s; }
                      |  string char   { $$ = $1 + $2;                  }
                      ;

dotnum                :      digits '.' digits  { $$ = atof(String($1 + "." + $3).c_str());                         }
                      |  '+' digits '.' digits  { String s = "+"; s += $2; s += "."; s += $4; $$ = atof(s.c_str()); }
                      |  '-' digits '.' digits  { $$ = atof(String("-" + $2 + "." + $4).c_str());                   }
                      ;


digits                :  digit         { $$ = $1;      }
                      |  digits digit  { $$ = $1 + $2; }
                      ;

digit                 :  '0'  { $$ = '0'; }
                      |  '1'  { $$ = '1'; }
                      |  '2'  { $$ = '2'; }
                      |  '3'  { $$ = '3'; }
                      |  '4'  { $$ = '4'; }
                      |  '5'  { $$ = '5'; }
                      |  '6'  { $$ = '6'; }
                      |  '7'  { $$ = '7'; }
                      |  '8'  { $$ = '8'; }
                      |  '9'  { $$ = '9'; }
                      ;

number                :  digit       { $$ = atoi(String(1, $1).c_str());      }
                      |  '1' digits  { $$ = atoi(String(String("1") + $2).c_str()); }
                      |  '2' digits  { $$ = atoi(String(String("2") + $2).c_str()); }
                      |  '3' digits  { $$ = atoi(String(String("3") + $2).c_str()); }
                      |  '4' digits  { $$ = atoi(String(String("4") + $2).c_str()); }
                      |  '5' digits  { $$ = atoi(String(String("5") + $2).c_str()); }
                      |  '6' digits  { $$ = atoi(String(String("6") + $2).c_str()); }
                      |  '7' digits  { $$ = atoi(String(String("7") + $2).c_str()); }
                      |  '8' digits  { $$ = atoi(String(String("8") + $2).c_str()); }
                      |  '9' digits  { $$ = atoi(String(String("9") + $2).c_str()); }

char                  :  'A' { $$ = 'A'; } | 'B' { $$ = 'B'; } | 'C' { $$ = 'C'; } | 'D' { $$ = 'D'; } | 'E' { $$ = 'E'; } | 'F' { $$ = 'F'; } | 'G' { $$ = 'G'; } | 'H' { $$ = 'H'; } | 'I' { $$ = 'I'; } | 'J' { $$ = 'J'; } | 'K' { $$ = 'K'; } | 'L' { $$ = 'L'; } | 'M' { $$ = 'M'; } | 'N' { $$ = 'N'; } | 'O' { $$ = 'O'; } | 'P' { $$ = 'P'; } | 'Q' { $$ = 'Q'; } | 'R' { $$ = 'R'; } | 'S' { $$ = 'S'; } | 'T' { $$ = 'T'; } | 'U' { $$ = 'U'; } | 'V' { $$ = 'V'; } | 'W' { $$ = 'W'; } | 'X' { $$ = 'X'; } | 'Y' { $$ = 'Y'; } | 'Z' { $$ = 'Z'; }
                      |  'a' { $$ = 'a'; } | 'b' { $$ = 'b'; } | 'c' { $$ = 'c'; } | 'd' { $$ = 'd'; } | 'e' { $$ = 'e'; } | 'f' { $$ = 'f'; } | 'g' { $$ = 'g'; } | 'h' { $$ = 'h'; } | 'i' { $$ = 'i'; } | 'j' { $$ = 'j'; } | 'k' { $$ = 'k'; } | 'l' { $$ = 'l'; } | 'm' { $$ = 'm'; } | 'n' { $$ = 'n'; } | 'o' { $$ = 'o'; } | 'p' { $$ = 'p'; } | 'q' { $$ = 'q'; } | 'r' { $$ = 'r'; } | 's' { $$ = 's'; } | 't' { $$ = 't'; } | 'u' { $$ = 'u'; } | 'v' { $$ = 'v'; } | 'w' { $$ = 'w'; } | 'x' { $$ = 'x'; } | 'y' { $$ = 'y'; } | 'z' { $$ = 'z'; }
                      |  '0' { $$ = '0'; } | '1' { $$ = '1'; } | '2' { $$ = '2'; } | '3' { $$ = '3'; } | '4' { $$ = '4'; } | '5' { $$ = '5'; } | '6' { $$ = '6'; } | '7' { $$ = '7'; } | '8' { $$ = '8'; } | '9' { $$ = '9'; }
                      |  '!' { $$ = '!'; } | '#' { $$ = '#'; } | '$' { $$ = '$'; } | '%' { $$ = '%'; } | '&' { $$ = '&'; } | '(' { $$ = '('; } | ')' { $$ = ')'; } | '*' { $$ = '*'; } | '+' { $$ = '+'; } | '-' { $$ = '-'; } | '.' { $$ = '.'; } | ',' { $$ = ','; } | '/' { $$ = '/'; }
                      |  ':' { $$ = ':'; } | ';' { $$ = ';'; } | '<' { $$ = '<'; } | '=' { $$ = '='; } | '>' { $$ = '>'; } | '?' { $$ = '?'; } | '@' { $$ = '@'; }
                      |  '[' { $$ = '['; } | '\\' { $$ = '\\'; } | ']' { $$ = ']'; } | '^' { $$ = '^'; } | '_' { $$ = '_'; }
                      |  '{' { $$ = '{'; } | '|' { $$ = '|'; } | '}' { $$ = '}'; } | '~' { $$ = '~'; }
                      |  '\200' { $$ = '\200'; } | '\201' { $$ = '\201'; } | '\202' { $$ = '\202'; }
                      |  '\203' { $$ = '\203'; } | '\204' { $$ = '\204'; } | '\205' { $$ = '\205'; }
                      |  '\206' { $$ = '\206'; } | '\207' { $$ = '\207'; } | '\210' { $$ = '\210'; }
                      |  '\211' { $$ = '\211'; } | '\212' { $$ = '\212'; } | '\213' { $$ = '\213'; }
                      |  '\214' { $$ = '\214'; } | '\215' { $$ = '\215'; } | '\216' { $$ = '\216'; }
                      |  '\217' { $$ = '\217'; } | '\220' { $$ = '\220'; } | '\221' { $$ = '\221'; }
                      |  '\222' { $$ = '\222'; } | '\223' { $$ = '\223'; } | '\224' { $$ = '\224'; }
                      |  '\225' { $$ = '\225'; } | '\226' { $$ = '\226'; } | '\227' { $$ = '\227'; }
                      |  '\230' { $$ = '\230'; } | '\231' { $$ = '\231'; } | '\232' { $$ = '\232'; }
                      |  '\233' { $$ = '\233'; } | '\234' { $$ = '\234'; } | '\235' { $$ = '\235'; }
                      |  '\236' { $$ = '\236'; } | '\237' { $$ = '\237'; } | '\240' { $$ = '\240'; }
                      |  '\241' { $$ = '\241'; } | '\242' { $$ = '\242'; } | '\243' { $$ = '\243'; }
                      |  '\244' { $$ = '\244'; } | '\245' { $$ = '\245'; } | '\246' { $$ = '\246'; }
                      |  '\247' { $$ = '\247'; } | '\250' { $$ = '\250'; } | '\251' { $$ = '\251'; }
                      |  '\252' { $$ = '\252'; } | '\253' { $$ = '\253'; } | '\254' { $$ = '\254'; }
                      |  '\255' { $$ = '\255'; } | '\256' { $$ = '\256'; } | '\257' { $$ = '\257'; }
                      |  '\260' { $$ = '\260'; } | '\261' { $$ = '\261'; } | '\262' { $$ = '\262'; }
                      |  '\263' { $$ = '\263'; } | '\264' { $$ = '\264'; } | '\265' { $$ = '\265'; }
                      |  '\266' { $$ = '\266'; } | '\267' { $$ = '\267'; } | '\270' { $$ = '\270'; }
                      |  '\271' { $$ = '\271'; } | '\272' { $$ = '\272'; } | '\273' { $$ = '\273'; }
                      |  '\274' { $$ = '\274'; } | '\275' { $$ = '\275'; } | '\276' { $$ = '\276'; }
                      |  '\277' { $$ = '\277'; } | '\300' { $$ = '\300'; } | '\301' { $$ = '\301'; }
                      |  '\302' { $$ = '\302'; } | '\303' { $$ = '\303'; } | '\304' { $$ = '\304'; }
                      |  '\305' { $$ = '\305'; } | '\306' { $$ = '\306'; } | '\307' { $$ = '\307'; }
                      |  '\310' { $$ = '\310'; } | '\311' { $$ = '\311'; } | '\312' { $$ = '\312'; }
                      |  '\313' { $$ = '\313'; } | '\314' { $$ = '\314'; } | '\315' { $$ = '\315'; }
                      |  '\316' { $$ = '\316'; } | '\317' { $$ = '\317'; } | '\320' { $$ = '\320'; }
                      |  '\321' { $$ = '\321'; } | '\322' { $$ = '\322'; } | '\323' { $$ = '\323'; }
                      |  '\324' { $$ = '\324'; } | '\325' { $$ = '\325'; } | '\326' { $$ = '\326'; }
                      |  '\327' { $$ = '\327'; } | '\330' { $$ = '\330'; } | '\331' { $$ = '\331'; }
                      |  '\332' { $$ = '\332'; } | '\333' { $$ = '\333'; } | '\334' { $$ = '\334'; }
                      |  '\335' { $$ = '\335'; } | '\336' { $$ = '\336'; } | '\337' { $$ = '\337'; }
                      |  '\340' { $$ = '\340'; } | '\341' { $$ = '\341'; } | '\342' { $$ = '\342'; }
                      |  '\343' { $$ = '\343'; } | '\344' { $$ = '\344'; } | '\345' { $$ = '\345'; }
                      |  '\346' { $$ = '\346'; } | '\347' { $$ = '\347'; } | '\350' { $$ = '\350'; }
                      |  '\351' { $$ = '\351'; } | '\352' { $$ = '\352'; } | '\353' { $$ = '\353'; }
                      |  '\354' { $$ = '\354'; } | '\355' { $$ = '\355'; } | '\356' { $$ = '\356'; }
                      |  '\357' { $$ = '\357'; } | '\360' { $$ = '\360'; } | '\361' { $$ = '\361'; }
                      |  '\362' { $$ = '\362'; } | '\363' { $$ = '\363'; } | '\364' { $$ = '\364'; }
                      |  '\365' { $$ = '\365'; } | '\366' { $$ = '\366'; } | '\367' { $$ = '\367'; }
                      |  '\370' { $$ = '\370'; } | '\371' { $$ = '\371'; } | '\372' { $$ = '\372'; }
                      |  '\373' { $$ = '\373'; } | '\374' { $$ = '\374'; } | '\375' { $$ = '\375'; }
                      |  '\376' { $$ = '\376'; } | '\377' { $$ = '\377'; }
                      ;

text                  :  SP           { $$ = " ";      }
                      |  string
                      |  text SP      { $$ = $1 + " "; }
                      |  text string  { $$ = $1 + $2;  }
                      ;

stringval             :  '\'' text '\''  { $$ = $2; }
                      |  '\"' text '\"'  { $$ = $2; }
                      ;


// rules which are more or less just terminal symbols

SP                    :  ' '
                      ;

LF                    :  '\n'
                      ;

CR                    :  '\r'
                      ;

ADD                   :  'A''D''D'
                      ;

GET                   :  'G''E''T'
                      ;

MAP                   :  'M''A''P'
                      ;

UNMAP                 :  'U''N''M''A''P'
                      ;

CLEAR                 :  'C''L''E''A''R'
                      ;

CREATE                :  'C''R''E''A''T''E'
                      ;

DESTROY               :  'D''E''S''T''R''O''Y'
                      ;

LIST                  :  'L''I''S''T'
                      ;

LOAD                  :  'L''O''A''D'
                      ;

ALL                   :  'A''L''L'
                      ;

NONE                  :  'N''O''N''E'
                      ;

DEFAULT               :  'D''E''F''A''U''L''T'
                      ;

NON_MODAL             :  'N''O''N''_''M''O''D''A''L'
                      ;

REMOVE                :  'R''E''M''O''V''E'
                      ;

SET                   :  'S''E''T'
                      ;

SUBSCRIBE             :  'S''U''B''S''C''R''I''B''E'
                      ;

UNSUBSCRIBE           :  'U''N''S''U''B''S''C''R''I''B''E'
                      ;

SELECT                :  'S''E''L''E''C''T'
                      ;

CHANNEL               :  'C''H''A''N''N''E''L'
                      ;

AVAILABLE_ENGINES     :  'A''V''A''I''L''A''B''L''E''_''E''N''G''I''N''E''S'
                      ;

AVAILABLE_AUDIO_OUTPUT_DRIVERS  :  'A''V''A''I''L''A''B''L''E''_''A''U''D''I''O''_''O''U''T''P''U''T''_''D''R''I''V''E''R''S'
                                ;

CHANNELS             :  'C''H''A''N''N''E''L''S'
                     ;

INFO                 :  'I''N''F''O'
                     ;

AUDIO_OUTPUT_DEVICE_COUNT :  'A''U''D''I''O''_''O''U''T''P''U''T''_''D''E''V''I''C''E''_''C''O''U''N''T'
                     ;

AUDIO_OUTPUT_DEVICE_INFO  :  'A''U''D''I''O''_''O''U''T''P''U''T''_''D''E''V''I''C''E''_''I''N''F''O'
                     ;

MIDI_INPUT_DEVICE_COUNT   :  'M''I''D''I''_''I''N''P''U''T''_''D''E''V''I''C''E''_''C''O''U''N''T'
                     ;

MIDI_INPUT_DEVICE_INFO    :  'M''I''D''I''_''I''N''P''U''T''_''D''E''V''I''C''E''_''I''N''F''O'
                     ;

MIDI_INSTRUMENT_MAP_COUNT :  'M''I''D''I''_''I''N''S''T''R''U''M''E''N''T''_''M''A''P''_''C''O''U''N''T'
                     ;

MIDI_INSTRUMENT_MAP_INFO  :  'M''I''D''I''_''I''N''S''T''R''U''M''E''N''T''_''M''A''P''_''I''N''F''O'
                     ;

MIDI_INSTRUMENT_COUNT     :  'M''I''D''I''_''I''N''S''T''R''U''M''E''N''T''_''C''O''U''N''T'
                     ;

MIDI_INSTRUMENT_INFO      :  'M''I''D''I''_''I''N''S''T''R''U''M''E''N''T''_''I''N''F''O'
                     ;

CHANNEL_COUNT        :  'C''H''A''N''N''E''L''_''C''O''U''N''T'
                     ;

CHANNEL_INFO         :  'C''H''A''N''N''E''L''_''I''N''F''O'
                     ;

BUFFER_FILL          :  'B''U''F''F''E''R''_''F''I''L''L'
                     ;

STREAM_COUNT         :  'S''T''R''E''A''M''_''C''O''U''N''T'
                     ;

VOICE_COUNT          :  'V''O''I''C''E''_''C''O''U''N''T'
                     ;

TOTAL_VOICE_COUNT    :  'T''O''T''A''L''_''V''O''I''C''E''_''C''O''U''N''T'
                     ;

TOTAL_VOICE_COUNT_MAX:  'T''O''T''A''L''_''V''O''I''C''E''_''C''O''U''N''T''_''M''A''X'
                     ;

INSTRUMENT           :  'I''N''S''T''R''U''M''E''N''T'
                     ;

ENGINE               :  'E' 'N' 'G' 'I' 'N' 'E'
                     ;

ON_DEMAND            :  'O''N''_''D''E''M''A''N''D'
                     ;

ON_DEMAND_HOLD       :  'O''N''_''D''E''M''A''N''D''_''H''O''L''D'
                     ;

PERSISTENT           :  'P''E''R''S''I''S''T''E''N''T'
                     ;

AUDIO_OUTPUT_DEVICE_PARAMETER  :  'A''U''D''I''O''_''O''U''T''P''U''T''_''D''E''V''I''C''E''_''P''A''R''A''M''E''T''E''R'
                               ;

AUDIO_OUTPUT_DEVICES  :  'A''U''D''I''O''_''O''U''T''P''U''T''_''D''E''V''I''C''E''S'
                      ;

AUDIO_OUTPUT_DEVICE   :  'A''U''D''I''O''_''O''U''T''P''U''T''_''D''E''V''I''C''E'
                      ;

AUDIO_OUTPUT_DRIVER_PARAMETER  :  'A''U''D''I''O''_''O''U''T''P''U''T''_''D''R''I''V''E''R''_''P''A''R''A''M''E''T''E''R'
                               ;

AUDIO_OUTPUT_DRIVER   :  'A''U''D''I''O''_''O''U''T''P''U''T''_''D''R''I''V''E''R'
                      ;

AUDIO_OUTPUT_CHANNEL_PARAMETER  :  'A''U''D''I''O''_''O''U''T''P''U''T''_''C''H''A''N''N''E''L''_''P''A''R''A''M''E''T''E''R'
                                ;

AUDIO_OUTPUT_CHANNEL  :  'A''U''D''I''O''_''O''U''T''P''U''T''_''C''H''A''N''N''E''L'
                      ;

AUDIO_OUTPUT_TYPE     :  'A''U''D''I''O''_''O''U''T''P''U''T''_''T''Y''P''E'
                      ;

AVAILABLE_MIDI_INPUT_DRIVERS  :  'A''V''A''I''L''A''B''L''E''_''M''I''D''I''_''I''N''P''U''T''_''D''R''I''V''E''R''S'
                              ;

MIDI_INPUT_DEVICE_PARAMETER  :  'M''I''D''I''_''I''N''P''U''T''_''D''E''V''I''C''E''_''P''A''R''A''M''E''T''E''R'
                             ;

MIDI_INPUT_PORT_PARAMETER    :  'M''I''D''I''_''I''N''P''U''T''_''P''O''R''T''_''P''A''R''A''M''E''T''E''R'
                             ;

MIDI_INPUT_DEVICES   :  'M''I''D''I''_''I''N''P''U''T''_''D''E''V''I''C''E''S'
                     ;

MIDI_INPUT_DEVICE     :  'M''I''D''I''_''I''N''P''U''T''_''D''E''V''I''C''E'
                      ;

MIDI_INPUT_DRIVER_PARAMETER  :  'M''I''D''I''_''I''N''P''U''T''_''D''R''I''V''E''R''_''P''A''R''A''M''E''T''E''R'
                             ;

MIDI_INSTRUMENT  :  'M''I''D''I''_''I''N''S''T''R''U''M''E''N''T'
                 ;

MIDI_INSTRUMENTS  :  'M''I''D''I''_''I''N''S''T''R''U''M''E''N''T''S'
                  ;

MIDI_INSTRUMENT_MAP  :  'M''I''D''I''_''I''N''S''T''R''U''M''E''N''T''_''M''A''P'
                     ;

MIDI_INSTRUMENT_MAPS  :  'M''I''D''I''_''I''N''S''T''R''U''M''E''N''T''_''M''A''P''S'
                      ;

MIDI_INPUT_DRIVER     :  'M''I''D''I''_''I''N''P''U''T''_''D''R''I''V''E''R'
                      ;

MIDI_INPUT_PORT       :  'M''I''D''I''_''I''N''P''U''T''_''P''O''R''T'
                      ;

MIDI_INPUT_CHANNEL    :  'M''I''D''I''_''I''N''P''U''T''_''C''H''A''N''N''E''L'
                      ;

MIDI_INPUT_TYPE       :  'M''I''D''I''_''I''N''P''U''T''_''T''Y''P''E'
                      ;

MIDI_INPUT            :  'M''I''D''I''_''I''N''P''U''T'
                      ;

MIDI_CONTROLLER       :  'M''I''D''I''_''C''O''N''T''R''O''L''L''E''R'
                      ;

FX_SEND               :  'F''X''_''S''E''N''D'
                      ;

FX_SENDS              :  'F''X''_''S''E''N''D''S'
                      ;

SERVER                :  'S''E''R''V''E''R'
                      ;

VOLUME                :  'V''O''L''U''M''E'
                      ;

LEVEL                 :  'L''E''V''E''L'
                      ;

MUTE                  :  'M''U''T''E'
                      ;

SOLO                  :  'S''O''L''O'
                      ;

BYTES                 :  'B''Y''T''E''S'
                      ;

PERCENTAGE            :  'P''E''R''C''E''N''T''A''G''E'
                      ;

RESET                 :  'R''E''S''E''T'
                      ;

MISCELLANEOUS         :  'M''I''S''C''E''L''L''A''N''E''O''U''S'
                      ;

NAME                  :  'N''A''M''E'
                      ;

ECHO                  :  'E''C''H''O'
                      ;

QUIT                  :  'Q''U''I''T'
                      ;

%%

/**
 * Will be called when an error occured (usually syntax error).
 */
void yyerror(const char* s) {
    dmsg(2,("LSCPParser: %s\n", s));
}

/**
 * Clears input buffer.
 */
void restart(yyparse_param_t* pparam, int& yychar) {
    bytes = 0;
    ptr   = 0;
}
