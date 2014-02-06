/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
 *   Copyright (C) 2005 - 2014 Christian Schoenebeck                       *
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

/*
    The parser's C++ source files should be automatically (re)generated if
    this file was modified. If not, or in case you want explicitly
    regenerate the parser C++ files, run 'make parser'. In both cases you
    need to have bison or another yacc compatible parser generator
    installed though.
*/

%{

#include "lscpparser.h"
#include "lscpserver.h"
#include "lscpevent.h"
#include "lscpsymbols.h"
#include <algorithm>
#include "lscp.h"

namespace LinuxSampler {

// to save us typing work in the rules action definitions
#define LSCPSERVER ((yyparse_param_t*) yyparse_param)->pServer
#define SESSION_PARAM ((yyparse_param_t*) yyparse_param)
#define INCREMENT_LINE { SESSION_PARAM->iLine++; SESSION_PARAM->iColumn = 0; sParsed.clear(); }

// clears input buffer
void restart(yyparse_param_t* pparam, int& yychar);
#define RESTART restart((yyparse_param_t*) YYPARSE_PARAM, yychar)

static char buf[1024]; // input buffer to feed the parser with new characters
static int bytes = 0;  // current number of characters in the input buffer
static int ptr   = 0;  // current position in the input buffer
static String sLastError; // error message of the last error occured
static String sParsed; ///< Characters of current line which have already been shifted (consumed/parsed) by the parser.

// external reference to the function which actually reads from the socket
extern int GetLSCPCommand( void *buf, int max_size);

// external reference to the function in lscpserver.cpp which returns the
// current session (only works because the server runs as singleton)
extern yyparse_param_t* GetCurrentYaccSession();

// returns true if supplied characters has an ASCII code of 128 or higher
inline bool isExtendedAsciiChar(const char c) {
    return (c < 0);
}

// returns true if the given character is between between a to z.
inline bool isLowerCaseAlphaChar(const char c) {
    return c >= 'a' && c <= 'z';
}

// converts the given (expected) lower case character to upper case
inline char alphaCharToUpperCase(const char c) {
    return (c - 'a') + 'A';
}

// custom scanner function which reads from the socket
// (bison expects it to return the numerical ID of the next
// "recognized token" from the input stream)
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
    // this is the next character in the input stream
    const char c = buf[ptr++];
    // increment current reading position (just for verbosity / messages)
    GetCurrentYaccSession()->iColumn++;
    sParsed += c;
    // we have to handle "normal" and "extended" ASCII characters separately
    if (isExtendedAsciiChar(c)) {
        // workaround for characters with ASCII code higher than 127
        yylval->Char = c;
        return EXT_ASCII_CHAR;
    } else {
        // simply return the ASCII code as terminal symbol ID
        return (int) c;
    }
}

// parser helper functions

int octalsToNumber(char oct_digit0, char oct_digit1 = '0', char oct_digit2 = '0') {
    const char d0[] = { oct_digit0, '\0' };
    const char d1[] = { oct_digit1, '\0' };
    const char d2[] = { oct_digit2, '\0' };
    return atoi(d2)*8*8 + atoi(d1)*8 + atoi(d0);
}

}

using namespace LinuxSampler;

static std::set<String> yyExpectedSymbols();

/**
 * Will be called when an error occured (usually syntax error).
 *
 * We provide our own version of yyerror() so we a) don't have to link against
 * the yacc library and b) can render more helpful syntax error messages.
 */
void yyerror(void* x, const char* s) {
    yyparse_param_t* param = GetCurrentYaccSession();

    // get the text part already parsed (of current line)
    const bool bContainsLineFeed =
        sParsed.find('\r') != std::string::npos ||
        sParsed.find('\n') != std::string::npos;
    // remove potential line feed characters
    if (bContainsLineFeed) {
        for (size_t p = sParsed.find('\r'); p != std::string::npos;
             p = sParsed.find('\r')) sParsed.erase(p);
        for (size_t p = sParsed.find('\n'); p != std::string::npos;
             p = sParsed.find('\n')) sParsed.erase(p);
    }

    // start assembling the error message with Bison's own message
    String txt = s;

    // append exact position info of syntax error
    txt += (" (line:"  + ToString(param->iLine+1)) +
           (",column:" + ToString(param->iColumn)) + ")";

    // append the part of the lined that has already been parsed
    txt += ". Context: \"" + sParsed;
    if (txt.empty() || bContainsLineFeed)
        txt += "^";
    else
        txt.insert(txt.size() - 1, "^");
    txt += "...\"";

    // append the non-terminal symbols expected now/next
    std::set<String> expectedSymbols = yyExpectedSymbols();
    for (std::set<String>::const_iterator it = expectedSymbols.begin();
         it != expectedSymbols.end(); ++it)
    {
        if (it == expectedSymbols.begin())
            txt += " -> Should be: " + *it;
        else
            txt += " | " + *it;
    }

    dmsg(2,("LSCPParser: %s\n", txt.c_str()));
    sLastError = txt;
}

%}

// reentrant parser
%pure-parser

%parse-param {void* yyparse_param}

// After entering the yyparse() function, store references to the parser's
// state stack, so that we can create more helpful syntax error messages than
// Bison (2.x) could do.
%initial-action {
    yyparse_param_t* p = (yyparse_param_t*) yyparse_param;
    p->ppStackBottom = &yyss;
    p->ppStackTop    = &yyssp;
}

// tell bison to spit out verbose syntax error messages
%error-verbose

%token <Char> EXT_ASCII_CHAR

%type <Char> char char_base alpha_char digit digit_oct digit_hex escape_seq escape_seq_octal escape_seq_hex
%type <Dotnum> real dotnum volume_value boolean control_value
%type <Number> number sampler_channel instrument_index fx_send_id audio_channel_index device_index effect_index effect_instance effect_chain chain_pos input_control midi_input_channel_index midi_input_port_index midi_map midi_bank midi_prog midi_ctrl
%type <String> string string_escaped text text_escaped text_escaped_base stringval stringval_escaped digits param_val_list param_val query_val filename module effect_system db_path map_name entry_name fx_send_name effect_name engine_name command add_instruction create_instruction destroy_instruction get_instruction list_instruction load_instruction send_instruction set_chan_instruction load_instr_args load_engine_args audio_output_type_name midi_input_type_name remove_instruction unmap_instruction set_instruction subscribe_event unsubscribe_event map_instruction reset_instruction clear_instruction find_instruction move_instruction copy_instruction scan_mode edit_instruction format_instruction append_instruction insert_instruction
%type <FillResponse> buffer_size_type
%type <KeyValList> key_val_list query_val_list
%type <LoadMode> instr_load_mode
%type <Bool> modal_arg
%type <UniversalPath> path path_base path_prefix path_body

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

line                  :  /* epsilon (empty line ignored) */ { INCREMENT_LINE; return LSCP_DONE; }
                      |  comment  { INCREMENT_LINE; return LSCP_DONE; }
                      |  command  { INCREMENT_LINE; LSCPSERVER->AnswerClient($1); return LSCP_DONE; }
                      |  error    { INCREMENT_LINE; LSCPSERVER->AnswerClient("ERR:0:" + sLastError + "\r\n"); RESTART; return LSCP_SYNTAX_ERROR; }
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
                      |  RESET SP reset_instruction            { $$ = $3;                                                }
                      |  CLEAR SP clear_instruction            { $$ = $3;                                                }
                      |  FIND SP find_instruction              { $$ = $3;                                                }
                      |  MOVE SP move_instruction              { $$ = $3;                                                }
                      |  COPY SP copy_instruction              { $$ = $3;                                                }
                      |  EDIT SP edit_instruction              { $$ = $3;                                                }
                      |  FORMAT SP format_instruction          { $$ = $3;                                                }
                      |  SEND SP send_instruction              { $$ = $3;                                                }
                      |  APPEND SP append_instruction          { $$ = $3;                                                }
                      |  INSERT SP insert_instruction          { $$ = $3;                                                }
                      |  RESET                                 { $$ = LSCPSERVER->ResetSampler();                        }
                      |  QUIT                                  { LSCPSERVER->AnswerClient("Bye!\r\n"); return LSCP_QUIT; }
                      ;

add_instruction       :  CHANNEL                               { $$ = LSCPSERVER->AddChannel();                  }
                      |  CHANNEL SP MIDI_INPUT SP sampler_channel SP device_index                           { $$ = LSCPSERVER->AddChannelMidiInput($5,$7);    }
                      |  CHANNEL SP MIDI_INPUT SP sampler_channel SP device_index SP midi_input_port_index  { $$ = LSCPSERVER->AddChannelMidiInput($5,$7,$9); }
                      |  DB_INSTRUMENT_DIRECTORY SP db_path    { $$ = LSCPSERVER->AddDbInstrumentDirectory($3);  }
                      |  DB_INSTRUMENTS SP NON_MODAL SP scan_mode SP db_path SP filename                        { $$ = LSCPSERVER->AddDbInstruments($5,$7,$9, true);        }
                      |  DB_INSTRUMENTS SP NON_MODAL SP scan_mode SP FILE_AS_DIR SP db_path SP filename         { $$ = LSCPSERVER->AddDbInstruments($5,$9,$11, true, true); }
                      |  DB_INSTRUMENTS SP scan_mode SP db_path SP filename                                     { $$ = LSCPSERVER->AddDbInstruments($3,$5,$7);              }
                      |  DB_INSTRUMENTS SP scan_mode SP FILE_AS_DIR SP db_path SP filename                      { $$ = LSCPSERVER->AddDbInstruments($3,$7,$9, false, true); }
                      |  DB_INSTRUMENTS SP NON_MODAL SP db_path SP filename                                     { $$ = LSCPSERVER->AddDbInstruments($5,$7, -1, true);       }
                      |  DB_INSTRUMENTS SP NON_MODAL SP db_path SP filename SP instrument_index                 { $$ = LSCPSERVER->AddDbInstruments($5,$7,$9, true);        }
                      |  DB_INSTRUMENTS SP db_path SP filename                                                  { $$ = LSCPSERVER->AddDbInstruments($3,$5);                 }
                      |  DB_INSTRUMENTS SP db_path SP filename SP instrument_index                              { $$ = LSCPSERVER->AddDbInstruments($3,$5,$7);              }
                      |  MIDI_INSTRUMENT_MAP                   { $$ = LSCPSERVER->AddMidiInstrumentMap();                }
                      |  MIDI_INSTRUMENT_MAP SP map_name       { $$ = LSCPSERVER->AddMidiInstrumentMap($3);              }
                      |  SEND_EFFECT_CHAIN SP device_index     { $$ = LSCPSERVER->AddSendEffectChain($3);                }
                      ;

subscribe_event       :  AUDIO_OUTPUT_DEVICE_COUNT             { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_audio_device_count);   }
                      |  AUDIO_OUTPUT_DEVICE_INFO              { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_audio_device_info);    }
                      |  MIDI_INPUT_DEVICE_COUNT               { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_device_count);    }
                      |  MIDI_INPUT_DEVICE_INFO                { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_device_info);     }
                      |  CHANNEL_COUNT                         { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_channel_count);        }
                      |  CHANNEL_MIDI                          { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_channel_midi);         }
                      |  DEVICE_MIDI                           { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_device_midi);          }
                      |  VOICE_COUNT                           { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_voice_count);          }
                      |  STREAM_COUNT                          { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_stream_count);         }
                      |  BUFFER_FILL                           { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_buffer_fill);          }
                      |  CHANNEL_INFO                          { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_channel_info);         }
                      |  FX_SEND_COUNT                         { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_fx_send_count);        }
                      |  FX_SEND_INFO                          { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_fx_send_info);         }
                      |  MIDI_INSTRUMENT_MAP_COUNT             { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_instr_map_count); }
                      |  MIDI_INSTRUMENT_MAP_INFO              { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_instr_map_info);  }
                      |  MIDI_INSTRUMENT_COUNT                 { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_instr_count);     }
                      |  MIDI_INSTRUMENT_INFO                  { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_instr_info);      }
                      |  DB_INSTRUMENT_DIRECTORY_COUNT         { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_db_instr_dir_count);   }
                      |  DB_INSTRUMENT_DIRECTORY_INFO          { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_db_instr_dir_info);    }
                      |  DB_INSTRUMENT_COUNT                   { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_db_instr_count);       }
                      |  DB_INSTRUMENT_INFO                    { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_db_instr_info);        }
                      |  DB_INSTRUMENTS_JOB_INFO               { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_db_instrs_job_info);   }
                      |  MISCELLANEOUS                         { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_misc);                 }
                      |  TOTAL_STREAM_COUNT                    { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_total_stream_count);   }
                      |  TOTAL_VOICE_COUNT                     { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_total_voice_count);    }
                      |  GLOBAL_INFO                           { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_global_info);          }
                      |  EFFECT_INSTANCE_COUNT                 { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_fx_instance_count);    }
                      |  EFFECT_INSTANCE_INFO                  { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_fx_instance_info);     }
                      |  SEND_EFFECT_CHAIN_COUNT               { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_send_fx_chain_count);  }
                      |  SEND_EFFECT_CHAIN_INFO                { $$ = LSCPSERVER->SubscribeNotification(LSCPEvent::event_send_fx_chain_info);   }
                      ;

unsubscribe_event     :  AUDIO_OUTPUT_DEVICE_COUNT             { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_audio_device_count);   }
                      |  AUDIO_OUTPUT_DEVICE_INFO              { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_audio_device_info);    }
                      |  MIDI_INPUT_DEVICE_COUNT               { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_device_count);    }
                      |  MIDI_INPUT_DEVICE_INFO                { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_device_info);     }
                      |  CHANNEL_COUNT                         { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_channel_count);        }
                      |  CHANNEL_MIDI                          { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_channel_midi);         }
                      |  DEVICE_MIDI                           { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_device_midi);          }
                      |  VOICE_COUNT                           { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_voice_count);          }
                      |  STREAM_COUNT                          { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_stream_count);         }
                      |  BUFFER_FILL                           { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_buffer_fill);          }
                      |  CHANNEL_INFO                          { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_channel_info);         }
                      |  FX_SEND_COUNT                         { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_fx_send_count);        }
                      |  FX_SEND_INFO                          { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_fx_send_info);         }
                      |  MIDI_INSTRUMENT_MAP_COUNT             { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_instr_map_count); }
                      |  MIDI_INSTRUMENT_MAP_INFO              { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_instr_map_info);  }
                      |  MIDI_INSTRUMENT_COUNT                 { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_instr_count);     }
                      |  MIDI_INSTRUMENT_INFO                  { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_instr_info);      }
                      |  DB_INSTRUMENT_DIRECTORY_COUNT         { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_db_instr_dir_count);   }
                      |  DB_INSTRUMENT_DIRECTORY_INFO          { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_db_instr_dir_info);    }
                      |  DB_INSTRUMENT_COUNT                   { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_db_instr_count);       }
                      |  DB_INSTRUMENT_INFO                    { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_db_instr_info);        }
                      |  DB_INSTRUMENTS_JOB_INFO               { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_db_instrs_job_info);   }
                      |  MISCELLANEOUS                         { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_misc);                 }
                      |  TOTAL_STREAM_COUNT                    { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_total_stream_count);   }
                      |  TOTAL_VOICE_COUNT                     { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_total_voice_count);    }
                      |  GLOBAL_INFO                           { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_global_info);          }
                      |  EFFECT_INSTANCE_COUNT                 { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_fx_instance_count);    }
                      |  EFFECT_INSTANCE_INFO                  { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_fx_instance_info);     }
                      |  SEND_EFFECT_CHAIN_COUNT               { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_send_fx_chain_count);  }
                      |  SEND_EFFECT_CHAIN_INFO                { $$ = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_send_fx_chain_info);   }
                      ;

map_instruction       :  MIDI_INSTRUMENT SP modal_arg midi_map SP midi_bank SP midi_prog SP engine_name SP filename SP instrument_index SP volume_value { $$ = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping($4,$6,$8,$10,$12,$14,$16,MidiInstrumentMapper::DONTCARE,"",$3); }
                      |  MIDI_INSTRUMENT SP modal_arg midi_map SP midi_bank SP midi_prog SP engine_name SP filename SP instrument_index SP volume_value SP instr_load_mode { $$ = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping($4,$6,$8,$10,$12,$14,$16,$18,"",$3); }
                      |  MIDI_INSTRUMENT SP modal_arg midi_map SP midi_bank SP midi_prog SP engine_name SP filename SP instrument_index SP volume_value SP entry_name { $$ = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping($4,$6,$8,$10,$12,$14,$16,MidiInstrumentMapper::DONTCARE,$18,$3); }
                      |  MIDI_INSTRUMENT SP modal_arg midi_map SP midi_bank SP midi_prog SP engine_name SP filename SP instrument_index SP volume_value SP instr_load_mode SP entry_name { $$ = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping($4,$6,$8,$10,$12,$14,$16,$18,$20,$3); }
                      ;

unmap_instruction     :  MIDI_INSTRUMENT SP midi_map SP midi_bank SP midi_prog  { $$ = LSCPSERVER->RemoveMIDIInstrumentMapping($3,$5,$7); }
                      ;

remove_instruction    :  CHANNEL SP sampler_channel                   { $$ = LSCPSERVER->RemoveChannel($3);                      }
                      |  CHANNEL SP MIDI_INPUT SP sampler_channel                                           { $$ = LSCPSERVER->RemoveChannelMidiInput($5);       }
                      |  CHANNEL SP MIDI_INPUT SP sampler_channel SP device_index                           { $$ = LSCPSERVER->RemoveChannelMidiInput($5,$7);    }
                      |  CHANNEL SP MIDI_INPUT SP sampler_channel SP device_index SP midi_input_port_index  { $$ = LSCPSERVER->RemoveChannelMidiInput($5,$7,$9); }
                      |  MIDI_INSTRUMENT_MAP SP midi_map              { $$ = LSCPSERVER->RemoveMidiInstrumentMap($3);            }
                      |  MIDI_INSTRUMENT_MAP SP ALL                   { $$ = LSCPSERVER->RemoveAllMidiInstrumentMaps();          }
                      |  SEND_EFFECT_CHAIN SP device_index SP effect_chain  { $$ = LSCPSERVER->RemoveSendEffectChain($3,$5);     }
                      |  SEND_EFFECT_CHAIN SP EFFECT SP device_index SP effect_chain SP chain_pos  { $$ = LSCPSERVER->RemoveSendEffectChainEffect($5,$7,$9); }
                      |  FX_SEND SP EFFECT SP sampler_channel SP fx_send_id  { $$ = LSCPSERVER->SetFxSendEffect($5,$7,-1,-1);    }
                      |  DB_INSTRUMENT_DIRECTORY SP FORCE SP db_path  { $$ = LSCPSERVER->RemoveDbInstrumentDirectory($5, true);  }
                      |  DB_INSTRUMENT_DIRECTORY SP db_path           { $$ = LSCPSERVER->RemoveDbInstrumentDirectory($3);        }
                      |  DB_INSTRUMENT SP db_path                     { $$ = LSCPSERVER->RemoveDbInstrument($3);                 }
                      ;

get_instruction       :  AVAILABLE_ENGINES                                                          { $$ = LSCPSERVER->GetAvailableEngines();                          }
                      |  AVAILABLE_EFFECTS                                                          { $$ = LSCPSERVER->GetAvailableEffects();                          }
                      |  EFFECT_INSTANCES                                                           { $$ = LSCPSERVER->GetEffectInstances();                           }
                      |  EFFECT SP INFO SP effect_index                                             { $$ = LSCPSERVER->GetEffectInfo($5);                              }
                      |  EFFECT_INSTANCE SP INFO SP effect_instance                                 { $$ = LSCPSERVER->GetEffectInstanceInfo($5);                      }
                      |  EFFECT_INSTANCE_INPUT_CONTROL SP INFO SP effect_instance SP input_control  { $$ = LSCPSERVER->GetEffectInstanceInputControlInfo($5,$7);       }
                      |  SEND_EFFECT_CHAINS SP device_index                                         { $$ = LSCPSERVER->GetSendEffectChains($3);                        }
                      |  SEND_EFFECT_CHAIN SP INFO SP device_index SP effect_chain                  { $$ = LSCPSERVER->GetSendEffectChainInfo($5,$7);                  }
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
                      |  TOTAL_STREAM_COUNT                                                         { $$ = LSCPSERVER->GetTotalStreamCount();                           }
                      |  TOTAL_VOICE_COUNT                                                          { $$ = LSCPSERVER->GetTotalVoiceCount();                           }
                      |  TOTAL_VOICE_COUNT_MAX                                                      { $$ = LSCPSERVER->GetTotalVoiceCountMax();                        }
                      |  MIDI_INSTRUMENTS SP midi_map                                               { $$ = LSCPSERVER->GetMidiInstrumentMappings($3);                  }
                      |  MIDI_INSTRUMENTS SP ALL                                                    { $$ = LSCPSERVER->GetAllMidiInstrumentMappings();                 }
                      |  MIDI_INSTRUMENT SP INFO SP midi_map SP midi_bank SP midi_prog              { $$ = LSCPSERVER->GetMidiInstrumentMapping($5,$7,$9);             }
                      |  MIDI_INSTRUMENT_MAPS                                                       { $$ = LSCPSERVER->GetMidiInstrumentMaps();                        }
                      |  MIDI_INSTRUMENT_MAP SP INFO SP midi_map                                    { $$ = LSCPSERVER->GetMidiInstrumentMap($5);                       }
                      |  FX_SENDS SP sampler_channel                                                { $$ = LSCPSERVER->GetFxSends($3);                                 }
                      |  FX_SEND SP INFO SP sampler_channel SP fx_send_id                           { $$ = LSCPSERVER->GetFxSendInfo($5,$7);                           }
                      |  DB_INSTRUMENT_DIRECTORIES SP RECURSIVE SP db_path                          { $$ = LSCPSERVER->GetDbInstrumentDirectoryCount($5, true);        }
                      |  DB_INSTRUMENT_DIRECTORIES SP db_path                                       { $$ = LSCPSERVER->GetDbInstrumentDirectoryCount($3, false);       }
                      |  DB_INSTRUMENT_DIRECTORY SP INFO SP db_path                                 { $$ = LSCPSERVER->GetDbInstrumentDirectoryInfo($5);               }
                      |  DB_INSTRUMENTS SP RECURSIVE SP db_path                                     { $$ = LSCPSERVER->GetDbInstrumentCount($5, true);                 }
                      |  DB_INSTRUMENTS SP db_path                                                  { $$ = LSCPSERVER->GetDbInstrumentCount($3, false);                }
                      |  DB_INSTRUMENT SP INFO SP db_path                                           { $$ = LSCPSERVER->GetDbInstrumentInfo($5);                        }
                      |  DB_INSTRUMENTS_JOB SP INFO SP number                                       { $$ = LSCPSERVER->GetDbInstrumentsJobInfo($5);                    }
                      |  VOLUME                                                                     { $$ = LSCPSERVER->GetGlobalVolume();                              }
                      |  VOICES                                                                     { $$ = LSCPSERVER->GetGlobalMaxVoices();                           }
                      |  STREAMS                                                                    { $$ = LSCPSERVER->GetGlobalMaxStreams();                          }
                      |  FILE SP INSTRUMENTS SP filename                                            { $$ = LSCPSERVER->GetFileInstruments($5);                         }
                      |  FILE SP INSTRUMENT SP INFO SP filename SP instrument_index                 { $$ = LSCPSERVER->GetFileInstrumentInfo($7,$9);                   }
                      ;

set_instruction       :  AUDIO_OUTPUT_DEVICE_PARAMETER SP number SP string '=' param_val_list             { $$ = LSCPSERVER->SetAudioOutputDeviceParameter($3, $5, $7);      }
                      |  AUDIO_OUTPUT_CHANNEL_PARAMETER SP number SP number SP string '=' param_val_list  { $$ = LSCPSERVER->SetAudioOutputChannelParameter($3, $5, $7, $9); }
                      |  MIDI_INPUT_DEVICE_PARAMETER SP number SP string '=' param_val_list               { $$ = LSCPSERVER->SetMidiInputDeviceParameter($3, $5, $7);        }
                      |  MIDI_INPUT_PORT_PARAMETER SP number SP number SP string '=' NONE                 { $$ = LSCPSERVER->SetMidiInputPortParameter($3, $5, $7, "");      }
                      |  MIDI_INPUT_PORT_PARAMETER SP number SP number SP string '=' param_val_list       { $$ = LSCPSERVER->SetMidiInputPortParameter($3, $5, $7, $9);      }
                      |  EFFECT_INSTANCE_INPUT_CONTROL SP VALUE SP effect_instance SP input_control SP control_value  { $$ = LSCPSERVER->SetEffectInstanceInputControlValue($5, $7, $9); }
                      |  CHANNEL SP set_chan_instruction                                                  { $$ = $3;                                                         }
                      |  MIDI_INSTRUMENT_MAP SP NAME SP midi_map SP map_name                              { $$ = LSCPSERVER->SetMidiInstrumentMapName($5, $7);               }
                      |  FX_SEND SP NAME SP sampler_channel SP fx_send_id SP fx_send_name                 { $$ = LSCPSERVER->SetFxSendName($5,$7,$9);                        }
                      |  FX_SEND SP AUDIO_OUTPUT_CHANNEL SP sampler_channel SP fx_send_id SP audio_channel_index SP audio_channel_index  { $$ = LSCPSERVER->SetFxSendAudioOutputChannel($5,$7,$9,$11); }
                      |  FX_SEND SP MIDI_CONTROLLER SP sampler_channel SP fx_send_id SP midi_ctrl         { $$ = LSCPSERVER->SetFxSendMidiController($5,$7,$9);              }
                      |  FX_SEND SP LEVEL SP sampler_channel SP fx_send_id SP volume_value                { $$ = LSCPSERVER->SetFxSendLevel($5,$7,$9);                       }
                      |  FX_SEND SP EFFECT SP sampler_channel SP fx_send_id SP effect_chain SP chain_pos  { $$ = LSCPSERVER->SetFxSendEffect($5,$7,$9,$11);                  }
                      |  DB_INSTRUMENT_DIRECTORY SP NAME SP db_path SP stringval_escaped                  { $$ = LSCPSERVER->SetDbInstrumentDirectoryName($5,$7);            }
                      |  DB_INSTRUMENT_DIRECTORY SP DESCRIPTION SP db_path SP stringval_escaped           { $$ = LSCPSERVER->SetDbInstrumentDirectoryDescription($5,$7);     }
                      |  DB_INSTRUMENT SP NAME SP db_path SP stringval_escaped                            { $$ = LSCPSERVER->SetDbInstrumentName($5,$7);                     }
                      |  DB_INSTRUMENT SP DESCRIPTION SP db_path SP stringval_escaped                     { $$ = LSCPSERVER->SetDbInstrumentDescription($5,$7);              }
                      |  DB_INSTRUMENT SP FILE_PATH SP filename SP filename                               { $$ = LSCPSERVER->SetDbInstrumentFilePath($5,$7);                 }
                      |  ECHO SP boolean                                                                  { $$ = LSCPSERVER->SetEcho((yyparse_param_t*) yyparse_param, $3);  }
                      |  SHELL SP INTERACT SP boolean                                                     { $$ = LSCPSERVER->SetShellInteract((yyparse_param_t*) yyparse_param, $5); }
                      |  SHELL SP AUTO_CORRECT SP boolean                                                 { $$ = LSCPSERVER->SetShellAutoCorrect((yyparse_param_t*) yyparse_param, $5); }
                      |  VOLUME SP volume_value                                                           { $$ = LSCPSERVER->SetGlobalVolume($3);                            }
                      |  VOICES SP number                                                                 { $$ = LSCPSERVER->SetGlobalMaxVoices($3);                         }
                      |  STREAMS SP number                                                                { $$ = LSCPSERVER->SetGlobalMaxStreams($3);                        }
                      ;

create_instruction    :  AUDIO_OUTPUT_DEVICE SP string SP key_val_list  { $$ = LSCPSERVER->CreateAudioOutputDevice($3,$5); }
                      |  AUDIO_OUTPUT_DEVICE SP string                  { $$ = LSCPSERVER->CreateAudioOutputDevice($3);    }
                      |  MIDI_INPUT_DEVICE SP string SP key_val_list    { $$ = LSCPSERVER->CreateMidiInputDevice($3,$5);   }
                      |  MIDI_INPUT_DEVICE SP string                    { $$ = LSCPSERVER->CreateMidiInputDevice($3);      }
                      |  FX_SEND SP sampler_channel SP midi_ctrl        { $$ = LSCPSERVER->CreateFxSend($3,$5);            }
                      |  FX_SEND SP sampler_channel SP midi_ctrl SP fx_send_name  { $$ = LSCPSERVER->CreateFxSend($3,$5,$7); }
                      |  EFFECT_INSTANCE SP effect_index                { $$ = LSCPSERVER->CreateEffectInstance($3);       }
                      |  EFFECT_INSTANCE SP effect_system SP module SP effect_name  { $$ = LSCPSERVER->CreateEffectInstance($3,$5,$7); }
                      ;

reset_instruction     :  CHANNEL SP sampler_channel  { $$ = LSCPSERVER->ResetChannel($3); }
                      ;

clear_instruction     :  MIDI_INSTRUMENTS SP midi_map   { $$ = LSCPSERVER->ClearMidiInstrumentMappings($3);  }
                      |  MIDI_INSTRUMENTS SP ALL        { $$ = LSCPSERVER->ClearAllMidiInstrumentMappings(); }
                      ;

find_instruction      :  DB_INSTRUMENTS SP NON_RECURSIVE SP db_path SP query_val_list              { $$ = LSCPSERVER->FindDbInstruments($5,$7, false);           }
                      |  DB_INSTRUMENTS SP db_path SP query_val_list                               { $$ = LSCPSERVER->FindDbInstruments($3,$5, true);            }
                      |  DB_INSTRUMENT_DIRECTORIES SP NON_RECURSIVE SP db_path SP query_val_list   { $$ = LSCPSERVER->FindDbInstrumentDirectories($5,$7, false); }
                      |  DB_INSTRUMENT_DIRECTORIES SP db_path SP query_val_list                    { $$ = LSCPSERVER->FindDbInstrumentDirectories($3,$5, true);  }
                      |  LOST SP DB_INSTRUMENT_FILES                                               { $$ = LSCPSERVER->FindLostDbInstrumentFiles();                 }
                      ;

move_instruction      :  DB_INSTRUMENT_DIRECTORY SP db_path SP db_path    { $$ = LSCPSERVER->MoveDbInstrumentDirectory($3,$5); }
                      |  DB_INSTRUMENT SP db_path SP db_path              { $$ = LSCPSERVER->MoveDbInstrument($3,$5);          }
                      ;

copy_instruction      :  DB_INSTRUMENT_DIRECTORY SP db_path SP db_path    { $$ = LSCPSERVER->CopyDbInstrumentDirectory($3,$5); }
                      |  DB_INSTRUMENT SP db_path SP db_path              { $$ = LSCPSERVER->CopyDbInstrument($3,$5);          }
                      ;

destroy_instruction   :  AUDIO_OUTPUT_DEVICE SP number  { $$ = LSCPSERVER->DestroyAudioOutputDevice($3); }
                      |  MIDI_INPUT_DEVICE SP number    { $$ = LSCPSERVER->DestroyMidiInputDevice($3);   }
                      |  FX_SEND SP sampler_channel SP fx_send_id  { $$ = LSCPSERVER->DestroyFxSend($3,$5); }
                      |  EFFECT_INSTANCE SP number      { $$ = LSCPSERVER->DestroyEffectInstance($3);    }
                      ;

load_instruction      :  INSTRUMENT SP load_instr_args  { $$ = $3; }
                      |  ENGINE SP load_engine_args     { $$ = $3; }
                      ;

append_instruction    :  SEND_EFFECT_CHAIN SP EFFECT SP device_index SP effect_chain SP effect_instance  { $$ = LSCPSERVER->AppendSendEffectChainEffect($5,$7,$9); }
                      ;

insert_instruction    :  SEND_EFFECT_CHAIN SP EFFECT SP device_index SP effect_chain SP chain_pos SP effect_instance  { $$ = LSCPSERVER->InsertSendEffectChainEffect($5,$7,$9,$11); }
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

edit_instruction      :  CHANNEL SP INSTRUMENT SP sampler_channel  { $$ = LSCPSERVER->EditSamplerChannelInstrument($5); }
                      ;

format_instruction    :  INSTRUMENTS_DB  { $$ = LSCPSERVER->FormatInstrumentsDb(); }
                      ;

modal_arg             :  /* epsilon (empty argument) */  { $$ = true;  }
                      |  NON_MODAL SP                    { $$ = false; }
                      ;

key_val_list          :  string '=' param_val_list                  { $$[$1] = $3;          }
                      |  key_val_list SP string '=' param_val_list  { $$ = $1; $$[$3] = $5; }
                      ;

buffer_size_type      :  BYTES       { $$ = fill_response_bytes;      }
                      |  PERCENTAGE  { $$ = fill_response_percentage; }
                      ;

list_instruction      :  AUDIO_OUTPUT_DEVICES                               { $$ = LSCPSERVER->GetAudioOutputDevices();              }
                      |  MIDI_INPUT_DEVICES                                 { $$ = LSCPSERVER->GetMidiInputDevices();                }
                      |  CHANNELS                                           { $$ = LSCPSERVER->ListChannels();                       }
                      |  CHANNEL SP MIDI_INPUTS SP sampler_channel          { $$ = LSCPSERVER->ListChannelMidiInputs($5);            }
                      |  AVAILABLE_ENGINES                                  { $$ = LSCPSERVER->ListAvailableEngines();               }
                      |  AVAILABLE_EFFECTS                                  { $$ = LSCPSERVER->ListAvailableEffects();               }
                      |  EFFECT_INSTANCES                                   { $$ = LSCPSERVER->ListEffectInstances();                }
                      |  SEND_EFFECT_CHAINS SP number                       { $$ = LSCPSERVER->ListSendEffectChains($3);             }
                      |  AVAILABLE_MIDI_INPUT_DRIVERS                       { $$ = LSCPSERVER->ListAvailableMidiInputDrivers();      }
                      |  AVAILABLE_AUDIO_OUTPUT_DRIVERS                     { $$ = LSCPSERVER->ListAvailableAudioOutputDrivers();    }
                      |  MIDI_INSTRUMENTS SP midi_map                       { $$ = LSCPSERVER->ListMidiInstrumentMappings($3);       }
                      |  MIDI_INSTRUMENTS SP ALL                            { $$ = LSCPSERVER->ListAllMidiInstrumentMappings();      }
                      |  MIDI_INSTRUMENT_MAPS                               { $$ = LSCPSERVER->ListMidiInstrumentMaps();             }
                      |  FX_SENDS SP sampler_channel                        { $$ = LSCPSERVER->ListFxSends($3);                      }
                      |  DB_INSTRUMENT_DIRECTORIES SP RECURSIVE SP db_path  { $$ = LSCPSERVER->GetDbInstrumentDirectories($5, true); }
                      |  DB_INSTRUMENT_DIRECTORIES SP db_path               { $$ = LSCPSERVER->GetDbInstrumentDirectories($3);       }
                      |  DB_INSTRUMENTS SP RECURSIVE SP db_path             { $$ = LSCPSERVER->GetDbInstruments($5, true);           }
                      |  DB_INSTRUMENTS SP db_path                          { $$ = LSCPSERVER->GetDbInstruments($3);                 }
                      |  FILE SP INSTRUMENTS SP filename                    { $$ = LSCPSERVER->ListFileInstruments($5);              }
                      ;

send_instruction      :  CHANNEL SP MIDI_DATA SP string SP sampler_channel SP number SP number  { $$ = LSCPSERVER->SendChannelMidiData($5, $7, $9, $11); }
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

effect_instance           : number
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

control_value             :  real
                          ;

sampler_channel           :  number
                          ;

instrument_index          :  number
                          ;

fx_send_id                :  number
                          ;

engine_name               :  string
                          ;

filename                  :  path  {
                                 #if WIN32
                                 $$ = $1.toWindows();
                                 #else
                                 // assuming POSIX
                                 $$ = $1.toPosix();
                                 #endif
                             }
                          ;

db_path                   :  path  { $$ = $1.toDbPath(); }
                          ;

map_name                  :  stringval_escaped
                          ;

entry_name                :  stringval_escaped
                          ;

fx_send_name              :  stringval_escaped
                          ;

effect_name               :  stringval_escaped
                          ;

effect_index              :  number
                          ;

effect_chain              :  number
                          ;

chain_pos                 :  number
                          ;

input_control             :  number
                          ;

param_val_list            :  param_val
                          |  param_val_list','param_val  { $$ = $1 + "," + $3; }
                          ;

//TODO: the re-encapsulation into apostrophes for string and strinval here is a hack, since we need a way for __parse_strings() (DeviceParameters.cpp) to distinguish a comma separated list of strings and a string which contains commas. A clean solution would be to move those parser jobs over here to lscp.y
param_val                 :  string            { $$ = "\'" + $1 + "\'"; }
                          |  stringval         { $$ = "\'" + $1 + "\'"; }
                          |  number            { std::stringstream ss; ss << "\'" << $1 << "\'"; $$ = ss.str(); }
                          |  dotnum            { std::stringstream ss; ss << "\'" << $1 << "\'"; $$ = ss.str(); } //TODO: maybe better using 'real' instead of 'number' and 'dotnum' rules
                          ;

query_val_list            :  string '=' query_val                    { $$[$1] = $3;          }
                          |  query_val_list SP string '=' query_val  { $$ = $1; $$[$3] = $5; }
                          ;

query_val                 :  text_escaped
                          |  stringval_escaped
                          ;

scan_mode                 :  RECURSIVE      { $$ = "RECURSIVE"; }
                          |  NON_RECURSIVE  { $$ = "NON_RECURSIVE"; }
                          |  FLAT           { $$ = "FLAT"; }
                          ;

effect_system             :  string
                          ;

module                    :  filename
                          ;

// GRAMMAR_BNF_END - do NOT delete or modify this line !!!


// atomic variable symbol rules

boolean               :  number  { $$ = $1; }
                      |  string  { $$ = -1; }
                      ;

dotnum                :      digits '.' digits  { std::stringstream ss($1 + "." + $3); ss.imbue(std::locale::classic()); ss >> $$; }
                      |  '+' digits '.' digits  { std::stringstream ss($2 + "." + $4); ss.imbue(std::locale::classic()); ss >> $$; }
                      |  '-' digits '.' digits  { std::stringstream ss("-" + $2 + "." + $4); ss.imbue(std::locale::classic()); ss >> $$; }
                      ;

real                  :      digits '.' digits  { std::stringstream ss($1 + "." + $3); ss.imbue(std::locale::classic()); ss >> $$; }
                      |  '+' digits '.' digits  { std::stringstream ss($2 + "." + $4); ss.imbue(std::locale::classic()); ss >> $$; }
                      |  '-' digits '.' digits  { std::stringstream ss("-" + $2 + "." + $4); ss.imbue(std::locale::classic()); ss >> $$; }
                      |      digits             { std::stringstream ss($1); ss.imbue(std::locale::classic()); ss >> $$;                  }
                      |  '+' digits             { std::stringstream ss($2); ss.imbue(std::locale::classic()); ss >> $$;                  }
                      |  '-' digits             { std::stringstream ss("-" + $2); ss.imbue(std::locale::classic()); ss >> $$;            }
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

digit_oct             :  '0'  { $$ = '0'; }
                      |  '1'  { $$ = '1'; }
                      |  '2'  { $$ = '2'; }
                      |  '3'  { $$ = '3'; }
                      |  '4'  { $$ = '4'; }
                      |  '5'  { $$ = '5'; }
                      |  '6'  { $$ = '6'; }
                      |  '7'  { $$ = '7'; }
                      ;

digit_hex             :  '0'  { $$ = '0'; }
                      |  '1'  { $$ = '1'; }
                      |  '2'  { $$ = '2'; }
                      |  '3'  { $$ = '3'; }
                      |  '4'  { $$ = '4'; }
                      |  '5'  { $$ = '5'; }
                      |  '6'  { $$ = '6'; }
                      |  '7'  { $$ = '7'; }
                      |  '8'  { $$ = '8'; }
                      |  '9'  { $$ = '9'; }
                      |  'a'  { $$ = 'a'; }
                      |  'b'  { $$ = 'b'; }
                      |  'c'  { $$ = 'c'; }
                      |  'd'  { $$ = 'd'; }
                      |  'e'  { $$ = 'e'; }
                      |  'f'  { $$ = 'f'; }
                      |  'A'  { $$ = 'a'; }
                      |  'B'  { $$ = 'b'; }
                      |  'C'  { $$ = 'c'; }
                      |  'D'  { $$ = 'd'; }
                      |  'E'  { $$ = 'e'; }
                      |  'F'  { $$ = 'f'; }
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
                      ;

path                  :  '\'' path_base '\''  { $$ = $2; }
                      |  '\"' path_base '\"'  { $$ = $2; }
                      ;

path_base             :  path_prefix path_body  { $$ = $1 + $2; }
                      ;

path_prefix           :  '/'                 { $$ = Path();                    }
                      |  alpha_char ':' '/'  { Path p; p.setDrive($1); $$ = p; }
                      ;

path_body             :  /* epsilon (empty argument) */ { $$ = Path();                           }
                      |  path_body '/'                  { $$ = $1;                               }
                      |  path_body text_escaped_base    { Path p; p.appendNode($2); $$ = $1 + p; }
                      ;

stringval             :  '\'' text '\''  { $$ = $2; }
                      |  '\"' text '\"'  { $$ = $2; }
                      ;

stringval_escaped     :  '\'' text_escaped '\''  { $$ = $2; }
                      |  '\"' text_escaped '\"'  { $$ = $2; }
                      ;

text                  :  SP           { $$ = " ";      }
                      |  string
                      |  text SP      { $$ = $1 + " "; }
                      |  text string  { $$ = $1 + $2;  }
                      ;

// like text_escaped, but missing the slash ('/') character
text_escaped_base     :  SP                                { $$ = " ";      }
                      |  string_escaped
                      |  text_escaped_base SP              { $$ = $1 + " "; }
                      |  text_escaped_base string_escaped  { $$ = $1 + $2;  }
                      ;

text_escaped          :  '/'                              { $$ = "/";      }
                      |  text_escaped_base
                      |  text_escaped '/'                 { $$ = $1 + "/"; }
                      |  text_escaped text_escaped_base   { $$ = $1 + $2;  }
                      ;

string                :  char          { std::string s; s = $1; $$ = s; }
                      |  string char   { $$ = $1 + $2;                  }
                      ;

string_escaped        :  char_base                   { std::string s; s = $1; $$ = s; }
                      |  escape_seq                  { std::string s; s = $1; $$ = s; }
                      |  string_escaped char_base    { $$ = $1 + $2;                  }
                      |  string_escaped escape_seq   { $$ = $1 + $2;                  }
                      ;

// full ASCII character set except space, quotation mark and apostrophe
char                  :  char_base
                      |  '\\'  { $$ = '\\'; }
                      |  '/'   { $$ = '/';  }
                      ;

// characters A..Z and a..z
alpha_char            :  'A' { $$ = 'A'; } | 'B' { $$ = 'B'; } | 'C' { $$ = 'C'; } | 'D' { $$ = 'D'; } | 'E' { $$ = 'E'; } | 'F' { $$ = 'F'; } | 'G' { $$ = 'G'; } | 'H' { $$ = 'H'; } | 'I' { $$ = 'I'; } | 'J' { $$ = 'J'; } | 'K' { $$ = 'K'; } | 'L' { $$ = 'L'; } | 'M' { $$ = 'M'; } | 'N' { $$ = 'N'; } | 'O' { $$ = 'O'; } | 'P' { $$ = 'P'; } | 'Q' { $$ = 'Q'; } | 'R' { $$ = 'R'; } | 'S' { $$ = 'S'; } | 'T' { $$ = 'T'; } | 'U' { $$ = 'U'; } | 'V' { $$ = 'V'; } | 'W' { $$ = 'W'; } | 'X' { $$ = 'X'; } | 'Y' { $$ = 'Y'; } | 'Z' { $$ = 'Z'; }
                      |  'a' { $$ = 'a'; } | 'b' { $$ = 'b'; } | 'c' { $$ = 'c'; } | 'd' { $$ = 'd'; } | 'e' { $$ = 'e'; } | 'f' { $$ = 'f'; } | 'g' { $$ = 'g'; } | 'h' { $$ = 'h'; } | 'i' { $$ = 'i'; } | 'j' { $$ = 'j'; } | 'k' { $$ = 'k'; } | 'l' { $$ = 'l'; } | 'm' { $$ = 'm'; } | 'n' { $$ = 'n'; } | 'o' { $$ = 'o'; } | 'p' { $$ = 'p'; } | 'q' { $$ = 'q'; } | 'r' { $$ = 'r'; } | 's' { $$ = 's'; } | 't' { $$ = 't'; } | 'u' { $$ = 'u'; } | 'v' { $$ = 'v'; } | 'w' { $$ = 'w'; } | 'x' { $$ = 'x'; } | 'y' { $$ = 'y'; } | 'z' { $$ = 'z'; }
                      ;

// ASCII characters except space, quotation mark, apostrophe, backslash and slash
char_base             :  alpha_char
                      |  '0' { $$ = '0'; } | '1' { $$ = '1'; } | '2' { $$ = '2'; } | '3' { $$ = '3'; } | '4' { $$ = '4'; } | '5' { $$ = '5'; } | '6' { $$ = '6'; } | '7' { $$ = '7'; } | '8' { $$ = '8'; } | '9' { $$ = '9'; }
                      |  '!' { $$ = '!'; } | '#' { $$ = '#'; } | '$' { $$ = '$'; } | '%' { $$ = '%'; } | '&' { $$ = '&'; } | '(' { $$ = '('; } | ')' { $$ = ')'; } | '*' { $$ = '*'; } | '+' { $$ = '+'; } | '-' { $$ = '-'; } | '.' { $$ = '.'; } | ',' { $$ = ','; }
                      |  ':' { $$ = ':'; } | ';' { $$ = ';'; } | '<' { $$ = '<'; } | '=' { $$ = '='; } | '>' { $$ = '>'; } | '?' { $$ = '?'; } | '@' { $$ = '@'; }
                      |  '[' { $$ = '['; } | ']' { $$ = ']'; } | '^' { $$ = '^'; } | '_' { $$ = '_'; }
                      |  '{' { $$ = '{'; } | '|' { $$ = '|'; } | '}' { $$ = '}'; } | '~' { $$ = '~'; }
                      |  EXT_ASCII_CHAR
                      ;

escape_seq            :  '\\' '\''  { $$ = '\''; }
                      |  '\\' '\"'  { $$ = '\"'; }
                      |  '\\' '\\'  { $$ = '\\'; }
                      |  '\\' '/'   { $$ = '/';  }
                      |  '\\' 'n'   { $$ = '\n'; }
                      |  '\\' 'r'   { $$ = '\r'; }
                      |  '\\' 'f'   { $$ = '\f'; }
                      |  '\\' 't'   { $$ = '\t'; }
                      |  '\\' 'v'   { $$ = '\v'; }
                      |  escape_seq_octal
                      |  escape_seq_hex
                      ;

escape_seq_octal      :  '\\' digit_oct                      { $$ = (char) octalsToNumber($2);       }
                      |  '\\' digit_oct digit_oct            { $$ = (char) octalsToNumber($3,$2);    }
                      |  '\\' digit_oct digit_oct digit_oct  { $$ = (char) octalsToNumber($4,$3,$2); }
                      ;

escape_seq_hex        :  '\\' 'x' digit_hex            { $$ = (char) hexsToNumber($3);    }
                      |  '\\' 'x' digit_hex digit_hex  { $$ = (char) hexsToNumber($4,$3); }
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

FIND                  :  'F''I''N''D'
                      ;

FILE_AS_DIR           :  'F''I''L''E''_''A''S''_''D''I''R'
                      ;

MOVE                  :  'M''O''V''E'
                      ;

COPY                  :  'C''O''P''Y'
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

SHELL                 :  'S''H''E''L''L'
                      ;

INTERACT              :  'I''N''T''E''R''A''C''T'
                      ;

AUTO_CORRECT          :  'A''U''T''O''_''C''O''R''R''E''C''T'
                      ;

APPEND                :  'A''P''P''E''N''D'
                      ;

INSERT                :  'I''N''S''E''R''T'
                      ;

SUBSCRIBE             :  'S''U''B''S''C''R''I''B''E'
                      ;

UNSUBSCRIBE           :  'U''N''S''U''B''S''C''R''I''B''E'
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

DB_INSTRUMENT_DIRECTORY_COUNT :  'D''B''_''I''N''S''T''R''U''M''E''N''T''_''D''I''R''E''C''T''O''R''Y''_''C''O''U''N''T'
                              ;

DB_INSTRUMENT_DIRECTORY_INFO  :  'D''B''_''I''N''S''T''R''U''M''E''N''T''_''D''I''R''E''C''T''O''R''Y''_''I''N''F''O'
                              ;

DB_INSTRUMENT_COUNT           :  'D''B''_''I''N''S''T''R''U''M''E''N''T''_''C''O''U''N''T'
                              ;

DB_INSTRUMENT_INFO            :  'D''B''_''I''N''S''T''R''U''M''E''N''T''_''I''N''F''O'
                              ;

DB_INSTRUMENT_FILES           :  'D''B''_''I''N''S''T''R''U''M''E''N''T''_''F''I''L''E''S'
                              ;

DB_INSTRUMENTS_JOB_INFO       :  'D''B''_''I''N''S''T''R''U''M''E''N''T''S''_''J''O''B''_''I''N''F''O'
                              ;

CHANNEL_COUNT        :  'C''H''A''N''N''E''L''_''C''O''U''N''T'
                     ;

CHANNEL_MIDI         :  'C''H''A''N''N''E''L''_''M''I''D''I'
                     ;

DEVICE_MIDI          :  'D''E''V''I''C''E''_''M''I''D''I'
                     ;

CHANNEL_INFO         :  'C''H''A''N''N''E''L''_''I''N''F''O'
                     ;

FX_SEND_COUNT        :  'F''X''_''S''E''N''D''_''C''O''U''N''T'
                     ;

FX_SEND_INFO         :  'F''X''_''S''E''N''D''_''I''N''F''O'
                     ;

BUFFER_FILL          :  'B''U''F''F''E''R''_''F''I''L''L'
                     ;

STREAM_COUNT         :  'S''T''R''E''A''M''_''C''O''U''N''T'
                     ;

VOICE_COUNT          :  'V''O''I''C''E''_''C''O''U''N''T'
                     ;

TOTAL_STREAM_COUNT   :  'T''O''T''A''L''_''S''T''R''E''A''M''_''C''O''U''N''T'
                     ;

TOTAL_VOICE_COUNT    :  'T''O''T''A''L''_''V''O''I''C''E''_''C''O''U''N''T'
                     ;

TOTAL_VOICE_COUNT_MAX:  'T''O''T''A''L''_''V''O''I''C''E''_''C''O''U''N''T''_''M''A''X'
                     ;

GLOBAL_INFO          :  'G''L''O''B''A''L''_''I''N''F''O'
                     ;

EFFECT_INSTANCE_COUNT   :  'E''F''F''E''C''T''_''I''N''S''T''A''N''C''E''_''C''O''U''N''T'
                        ;

EFFECT_INSTANCE_INFO    :  'E''F''F''E''C''T''_''I''N''S''T''A''N''C''E''_''I''N''F''O'
                        ;

SEND_EFFECT_CHAIN_COUNT :  'S''E''N''D''_''E''F''F''E''C''T''_''C''H''A''I''N''_''C''O''U''N''T'
                        ;

SEND_EFFECT_CHAIN_INFO  :  'S''E''N''D''_''E''F''F''E''C''T''_''C''H''A''I''N''_''I''N''F''O'
                        ;

INSTRUMENT           :  'I''N''S''T''R''U''M''E''N''T'
                     ;

INSTRUMENTS          :  'I''N''S''T''R''U''M''E''N''T''S'
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

AVAILABLE_EFFECTS :  'A''V''A''I''L''A''B''L''E''_''E''F''F''E''C''T''S'
                  ;

EFFECT :  'E''F''F''E''C''T'
       ;

EFFECT_INSTANCE :  'E''F''F''E''C''T''_''I''N''S''T''A''N''C''E'
                ;

EFFECT_INSTANCES :  'E''F''F''E''C''T''_''I''N''S''T''A''N''C''E''S'
                 ;

EFFECT_INSTANCE_INPUT_CONTROL :  'E''F''F''E''C''T''_''I''N''S''T''A''N''C''E''_''I''N''P''U''T''_''C''O''N''T''R''O''L'
                              ;

SEND_EFFECT_CHAIN :  'S''E''N''D''_''E''F''F''E''C''T''_''C''H''A''I''N'
                  ;

SEND_EFFECT_CHAINS :  'S''E''N''D''_''E''F''F''E''C''T''_''C''H''A''I''N''S'
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

MIDI_INPUTS           :  'M''I''D''I''_''I''N''P''U''T''S'
                      ;

MIDI_CONTROLLER       :  'M''I''D''I''_''C''O''N''T''R''O''L''L''E''R'
                      ;

SEND                  :  'S''E''N''D'
                      ;

FX_SEND               :  'F''X''_''S''E''N''D'
                      ;

FX_SENDS              :  'F''X''_''S''E''N''D''S'
                      ;

DB_INSTRUMENT_DIRECTORY    :  'D''B''_''I''N''S''T''R''U''M''E''N''T''_''D''I''R''E''C''T''O''R''Y'
                           ;

DB_INSTRUMENT_DIRECTORIES  :  'D''B''_''I''N''S''T''R''U''M''E''N''T''_''D''I''R''E''C''T''O''R''I''E''S'
                           ;

DB_INSTRUMENTS             :  'D''B''_''I''N''S''T''R''U''M''E''N''T''S'
                           ;

DB_INSTRUMENT              :  'D''B''_''I''N''S''T''R''U''M''E''N''T'
                           ;

DB_INSTRUMENTS_JOB         :  'D''B''_''I''N''S''T''R''U''M''E''N''T''S''_''J''O''B'
                           ;

INSTRUMENTS_DB             :  'I''N''S''T''R''U''M''E''N''T''S''_''D''B'
                           ;

DESCRIPTION                :  'D''E''S''C''R''I''P''T''I''O''N'
                           ;

FORCE                      :  'F''O''R''C''E'
                           ;

FLAT                       :  'F''L''A''T'
                           ;

RECURSIVE                  :  'R''E''C''U''R''S''I''V''E'
                           ;

NON_RECURSIVE              :  'N''O''N''_''R''E''C''U''R''S''I''V''E'
                           ;

LOST                       :  'L''O''S''T'
                           ;

FILE_PATH                  :  'F''I''L''E''_''P''A''T''H'
                           ;

SERVER                :  'S''E''R''V''E''R'
                      ;

VOLUME                :  'V''O''L''U''M''E'
                      ;

LEVEL                 :  'L''E''V''E''L'
                      ;

VALUE                 :  'V''A''L''U''E'
                      ;

MUTE                  :  'M''U''T''E'
                      ;

SOLO                  :  'S''O''L''O'
                      ;

VOICES                :  'V''O''I''C''E''S'
                      ;

STREAMS               :  'S''T''R''E''A''M''S'
                      ;

BYTES                 :  'B''Y''T''E''S'
                      ;

PERCENTAGE            :  'P''E''R''C''E''N''T''A''G''E'
                      ;

FILE                  :  'F''I''L''E'
                      ;

EDIT                  :  'E''D''I''T'
                      ;

FORMAT                :  'F''O''R''M''A''T'
                      ;

MIDI_DATA             :  'M''I''D''I''_''D''A''T''A'
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

// TODO: actually would be fine to have the following bunch of source code in a separate file, however those functions are a) accessing private Bison tables like yytable and b) including the functions from another file here would make the line numbers incorrect on compile errors in auto generated lscpparser.cpp

/**
 * Additional informations of a grammar symbol.
 */
struct BisonSymbolInfo {
    bool isTerminalSymbol; ///< Whether the symbol is a terminal or non-termianl symbol. NOTE: Read comment regarding this in _isRuleTerminalSymbol() !!
    String nextExpectedChars; ///< According to current parser position: sequence of characters expected next for satisfying this grammar symbol.
};

/**
 * Returns true if the given grammar @a rule is a terminal symbol (in *our*
 * terms).
 *
 * Please note that the term "terminal symbol" is a bit confusingly used in
 * this source code here around. In Bison's terms, "terminal symbols" are (more
 * or less) just the numbers returned by the YYLEX function. Since we decided
 * though to use a convenient solution without a separate lexer, and all its
 * caveats, all numbers by the yylex() function here are just the ASCII
 * numbers of the individual characters received. Based on that however, one
 * single character is not what one would intuitively expect of being a 
 * "terminal symbol", because it is simply too primitive.
 *
 * So in this LSCP parser source code a "terminal symbol" rather means a
 * keyword like "CREATE" or "GET". In the grammal definition above, those are
 * however defined as grammar rules (non-terminals in Bison's terms). So this
 * function decides like this: if the given grammar rule just contains
 * individual characters on the right side of its grammar rule, then it is a
 * "terminal symbol" in *our* terms.
 *
 * @param rule - Bison grammar rule number
 */
inline static bool _isRuleTerminalSymbol(int rule) {
    for (int i = yyprhs[rule]; yyrhs[i] != -1; ++i)
        if (yyrhs[i] >= YYNTOKENS) return false;
    return true;
}

/**
 * Returns additional informations to the given grammar @a rule.
 */
inline static BisonSymbolInfo _symbolInfoForRule(int rule, const String& nextExpectedChars) {
    BisonSymbolInfo info;
    info.isTerminalSymbol = _isRuleTerminalSymbol(rule);
    if (info.isTerminalSymbol) info.nextExpectedChars  = nextExpectedChars;
    return info;
}

/**
 * Returns the human readable name of the given @a token.
 */
inline static String _tokenName(int token) {
    String s = yytname[token];
    // remove leading and trailing apostrophes that Bison usually adds to
    // ASCII characters used directly in grammar rules
    if (s.empty()) return s;
    if (s[0] == '\'') s.erase(0, 1);
    if (s.empty()) return s;
    if (s[s.size() - 1] == '\'') s.erase(s.size() - 1);
    return s;
}

#define DEBUG_BISON_SYNTAX_ERROR_WALKER 0

/**
 * Tries to find the next expected grammar symbols according to the given
 * precise parse position & state represented by @a stack, according to Bison's
 * LALR(1) parser algorithm.
 *
 * This function is given a Bison parser state stack, reflecting the parser's
 * entire state at a certain point, i.e. when a syntax error occured. This
 * function will then walk ahead the potential parse tree starting from the
 * current head of the given state stack. This function will call itself
 * recursively to scan the individual parse tree branches. As soon as it hits
 * on the next non-terminal grammar symbol in one parse tree branch, it adds the
 * found non-terminal symbol to @a expectedSymbols and aborts scanning the
 * respective tree branch further. If any local parser state is reached a second
 * time, the respective parse tree is aborted to avoid any endless recursion.
 *
 * @param stack - current Bison (yacc) state stack to be examined
 * @param expectedSymbols - will be filled with next expected grammar symbols
 * @param nextExpectedChars - just for internal purpose, due to the recursive
 *                            implementation of this function, do supply an
 *                            empty character for this argument
 * @param depth - just for internal debugging purposes
 */
static void walkAndFillExpectedSymbols(
    std::vector<YYTYPE_INT16>& stack,
    std::map<String,BisonSymbolInfo>& expectedSymbols,
    String& nextExpectedChars, int depth = 0)
{
#if DEBUG_BISON_SYNTAX_ERROR_WALKER
    printf("\n");
    for (int i = 0; i < depth; ++i) printf("\t");
    printf("State stack:");
    for (int i = 0; i < stack.size(); ++i) {
        printf(" %d", stack[i]);
    }
    printf("\n");
#endif

    if (stack.empty()) return;

    int state = stack[stack.size() - 1];
    int n = yypact[state];
    if (n == YYPACT_NINF) { // default reduction required ...
        // get default reduction rule for this state
        n = yydefact[state];
        if (n <= 0 || n >= YYNRULES) return; // no rule, something is wrong
        // return the new resolved expected symbol (left-hand symbol of grammar
        // rule), then we're done in this state
        expectedSymbols[yytname[yyr1[n]]] = _symbolInfoForRule(n, nextExpectedChars);
        return;
    }
    if (!(YYPACT_NINF < n && n <= YYLAST)) return;

#if DEBUG_BISON_SYNTAX_ERROR_WALKER
    for (int i = 0; i < depth; ++i) printf("\t");
    printf("Expected tokens:");
#endif
    int begin = n < 0 ? -n : 0;
    int checklim = YYLAST - n + 1;
    int end = checklim < YYNTOKENS ? checklim : YYNTOKENS;
    int rule, action, stackSize, nextExpectedCharsLen;
    for (int token = begin; token < end; ++token) {
        if (token == YYTERROR || yycheck[n + token] != token) continue;
#if DEBUG_BISON_SYNTAX_ERROR_WALKER
        printf(" %s", yytname[token]);
#endif

        //if (yycheck[n + token] != token) goto default_reduction;

        action = yytable[n + token];
        if (action == 0 || action == YYTABLE_NINF) {
#if DEBUG_BISON_SYNTAX_ERROR_WALKER
            printf(" (invalid action) "); fflush(stdout);
#endif
            continue; // error, ignore
        }
        if (action < 0) { // reduction with rule -action required ...
#if DEBUG_BISON_SYNTAX_ERROR_WALKER
            printf(" (reduction) "); fflush(stdout);
#endif
            rule = -action;
            goto reduce;
        }
        if (action == YYFINAL) continue; // "accept" state, we don't care about it here

        // "shift" required ...

        if (std::find(stack.begin(), stack.end(), action) != stack.end())
            continue; // duplicate state, ignore it to avoid endless recursions

        // "shift" / push the new state on the state stack and call this
        // function recursively, and restore the stack after the recurse return
        stackSize = stack.size();
        nextExpectedCharsLen = nextExpectedChars.size();
        stack.push_back(action);
        nextExpectedChars += _tokenName(token);
        walkAndFillExpectedSymbols( //FIXME: could cause stack overflow (should be a loop instead), is probably fine with our current grammar though
            stack, expectedSymbols, nextExpectedChars, depth + 1
        );
        stack.resize(stackSize); // restore stack
        nextExpectedChars.resize(nextExpectedCharsLen); // restore 'nextExpectedChars'
        continue;

    //default_reduction: // resolve default reduction for this state
    //    printf(" (default red.) "); fflush(stdout);
    //    rule = yydefact[state];

    reduce: // "reduce" required
#if DEBUG_BISON_SYNTAX_ERROR_WALKER
        printf(" (reduce by %d) ", rule); fflush(stdout);
#endif
        if (rule == 0 || rule >= YYNRULES) continue; // invalid rule, something is wrong
        // store the left-hand symbol of the grammar rule
        expectedSymbols[yytname[yyr1[rule]]] = _symbolInfoForRule(rule, nextExpectedChars);
#if DEBUG_BISON_SYNTAX_ERROR_WALKER
        printf(" (SYM %s) ", yytname[yyr1[rule]]); fflush(stdout);
#endif
    }
#if DEBUG_BISON_SYNTAX_ERROR_WALKER
    printf("\n");
#endif
}

/**
 * Implements Bison's so called "reduce" action, according to Bison's LALR(1)
 * parser algorithm.
 */
inline static int _yyReduce(std::vector<YYTYPE_INT16>& stack, const int& rule) {
    if (stack.empty()) throw 1; // severe error
    const int len = yyr2[rule];
    stack.resize(stack.size() - len);
    YYTYPE_INT16 newState = yypgoto[yyr1[rule] - YYNTOKENS] + stack.back();
    if (0 <= newState && newState <= YYLAST && yycheck[newState] == stack.back())
        newState = yytable[newState];
    else
        newState = yydefgoto[yyr1[rule] - YYNTOKENS];
    stack.push_back(newState);
    return newState;
}

/**
 * Implements Bison's so called "default reduce" action, according to Bison's
 * LALR(1) parser algorithm.
 */
inline static int _yyDefaultReduce(std::vector<YYTYPE_INT16>& stack) {
    if (stack.empty()) throw 2; // severe error
    int rule = yydefact[stack.back()];
    if (rule <= 0 || rule >= YYNRULES) throw 3; // no rule, something is wrong
    return _yyReduce(stack, rule);
}

#define DEBUG_PUSH_PARSE 0

/**
 * Implements parsing exactly one character (given by @a c), continueing at the
 * parser position reflected by @a stack. The @a stack will hold the new parser
 * state after this call.
 *
 * This function is implemented according to Bison's LALR(1) parser algorithm.
 */
static bool yyPushParse(std::vector<YYTYPE_INT16>& stack, char ch) {
    startLabel:

#if DEBUG_PUSH_PARSE
    //printf("\n");
    //for (int i = 0; i < depth; ++i) printf("\t");
    printf("State stack:");
    for (int i = 0; i < stack.size(); ++i) {
        printf(" %d", stack[i]);
    }
    printf(" char='%c'(%d)\n", ch, (int)ch);
#endif

    if (stack.empty()) return false;

    int state = stack.back();
    int n = yypact[state];
    if (n == YYPACT_NINF) { // default reduction required ...
#if DEBUG_PUSH_PARSE
        printf("(def reduce 1)\n");
#endif
        state = _yyDefaultReduce(stack);
        goto startLabel;
    }
    if (!(YYPACT_NINF < n && n <= YYLAST)) return false;

    YYTYPE_INT16 token = (ch == YYEOF) ? YYEOF : yytranslate[ch];
    n += token;
    if (n < 0 || YYLAST < n || yycheck[n] != token) {
#if DEBUG_PUSH_PARSE
        printf("(def reduce 2) n=%d token=%d\n", n, token);
#endif
        state = _yyDefaultReduce(stack);
        goto startLabel;
    }
    int action = yytable[n]; // yytable[yypact[state] + token]
    if (action == 0 || action == YYTABLE_NINF) throw 4;
    if (action < 0) {
#if DEBUG_PUSH_PARSE
        printf("(reduce)\n");
#endif
        int rule = -action;
        state = _yyReduce(stack, rule);
        goto startLabel;
    }
    if (action == YYFINAL) return true; // final state reached

#if DEBUG_PUSH_PARSE
    printf("(push)\n");
#endif
    // push new state
    state = action;
    stack.push_back(state);
    return true;
}

/**
 * Returns true if parsing ahead with given character @a ch is syntactially
 * valid according to the LSCP grammar, it returns false if it would create a
 * parse error.
 *
 * This is just a wrapper ontop of yyPushParse() which converts parser
 * exceptions thrown by yyPushParse() into negative return value.
 */
static bool yyValid(std::vector<YYTYPE_INT16>& stack, char ch) {
    try {
        return yyPushParse(stack, ch);
    } catch (int i) {
#if DEBUG_PUSH_PARSE
        printf("exception %d\n", i);
#endif
        return false;
    } catch (...) {
        return false;
    }
}

/**
 * Returns the amount of correct characters of given @a line from the left,
 * according to the LSCP grammar.
 *
 * @param stack - a Bison symbol state stack to work with
 * @param line  - the input line to check
 * @param bAutoCorrect - if true: try to correct obvious, trivial syntax errors
 */
static int yyValidCharacters(std::vector<YYTYPE_INT16>& stack, String& line, bool bAutoCorrect) {
    int i;
    for (i = 0; i < line.size(); ++i) {
        // since we might check the same parser state twice against the current
        // char here below, and since the state stack might be altered
        // (i.e. shifted or reduced) on syntax errors, we have to backup the
        // current state stack and restore it on syntax errors below
        std::vector<YYTYPE_INT16> stackBackup = stack;
        if (yyValid(stackBackup, line[i])) {
            stack = stackBackup;
            continue;
        }
        if (bAutoCorrect) {
            // try trivial corrections, i.e. upper case character instead of
            // lower case, subline instead of space and vice versa
            char c;
            if      (line[i] == ' ') c = '_';
            else if (line[i] == '_') c = ' ';
            else if (isLowerCaseAlphaChar(line[i]))
                c = alphaCharToUpperCase(line[i]);
            else return i;
            if (yyValid(stack, c)) {
                line[i] = c;
                continue;
            }
        }
        return i;
    }
    return i;
}

/**
 * Should only be called on syntax errors: returns a set of non-terminal
 * symbols expected to appear now/next, just at the point where the syntax
 * error appeared.
 */
static std::set<String> yyExpectedSymbols() {
    std::map<String,BisonSymbolInfo> expectedSymbols;
    yyparse_param_t* param = GetCurrentYaccSession();
    YYTYPE_INT16* ss = (*param->ppStackBottom);
    YYTYPE_INT16* sp = (*param->ppStackTop);
    int iStackSize   = sp - ss + 1;
    // copy and wrap parser's state stack into a convenient STL container
    std::vector<YYTYPE_INT16> stack;
    for (int i = 0; i < iStackSize; ++i) {
        stack.push_back(ss[i]);
    }
    String notUsedHere;
    // do the actual parser work
    walkAndFillExpectedSymbols(stack, expectedSymbols, notUsedHere);

    // convert expectedSymbols to the result set
    std::set<String> result;
    for (std::map<String,BisonSymbolInfo>::const_iterator it = expectedSymbols.begin();
         it != expectedSymbols.end(); ++it) result.insert(it->first);
    return result;
}

namespace LinuxSampler {

#define DEBUG_SHELL_INTERACTION 0

/**
 * If LSP shell mode is enabled, then this function is called on every new
 * received from client. It will check the current total input line and reply
 * to the LSCP shell for providing colored syntax highlighting and potential
 * auto completion in the shell.
 *
 * It also performs auto correction of obvious & trivial syntax mistakes if
 * requested.
 */
String lscpParserProcessShellInteraction(String& line, yyparse_param_t* param) {
    // first, determine how many characters (starting from the left) of the
    // given input line are already syntactially correct
    std::vector<YYTYPE_INT16> stack;
    stack.push_back(0); // every Bison symbol stack starts with state zero
    String l = line + '\n'; // '\n' to pretend ENTER as if the line was now complete
    int n = yyValidCharacters(stack, l, param->bShellAutoCorrect);

    // if auto correction is enabled, apply the auto corrected string to
    // intput/output string 'line'
    if (param->bShellAutoCorrect) {
        int nMin = (n < line.length()) ? n : line.length();
        line.replace(0, nMin, l.substr(0, nMin));
    }

    // generate an info string that will be sent to the LSCP shell for letting
    // it know which part is correct, which one is wrong, where is the cursor, etc.
    String result = line;
    result.insert(n <= result.length() ? n : result.length(), LSCP_SHK_GOOD_FRONT);
    int code = (n > line.length()) ? LSCP_SHU_COMPLETE : (n < line.length()) ?
               LSCP_SHU_SYNTAX_ERR : LSCP_SHU_INCOMPLETE;
    result = "SHU:" + ToString(code) + ":" + result + LSCP_SHK_CURSOR;
    //if (n > line.length()) result += " [OK]";

    // get a clean parser stack to the last valid parse position
    // (due to the appended '\n' character above, and on syntax errors, the
    // state stack might be in undesired, i.e. reduced state)
    stack.clear();
    stack.push_back(0); // every Bison symbol stack starts with state zero
    l = line.substr(0, n);
    if (!l.empty()) yyValidCharacters(stack, l, param->bShellAutoCorrect);

    // generate auto completion suggestion (based on the current parser stack)
    std::map<String,BisonSymbolInfo> expectedSymbols;
    String notUsedHere;
    walkAndFillExpectedSymbols(stack, expectedSymbols, notUsedHere);
    if (expectedSymbols.size() == 1) {
        String name          = expectedSymbols.begin()->first;
        BisonSymbolInfo info = expectedSymbols.begin()->second;
#if DEBUG_SHELL_INTERACTION
        printf("Suggested Completion (%d): %s '%s'\n", expectedSymbols.size(), (info.isTerminalSymbol) ? "T:" : "NT:", (name + " (" + info.nextExpectedChars + ")").c_str());
#endif
        result += LSCP_SHK_SUGGEST_BACK + info.nextExpectedChars;
    } else if (expectedSymbols.size() == 0) {
#if DEBUG_SHELL_INTERACTION
        printf("No suggestion.\n");
#endif
    } else if (expectedSymbols.size() > 1) {
#if DEBUG_SHELL_INTERACTION
        printf("Multiple possibilities:");
        for (std::map<String,BisonSymbolInfo>::const_iterator it = expectedSymbols.begin();
             it != expectedSymbols.end(); ++it)
        {
            printf(" %s (..%s)", it->first.c_str(), it->second.nextExpectedChars.c_str());
        }
        printf("\n");
#endif
        // check if any of the possibilites is a non-terminal symbol, if so, we
        // have no way for auto completion at this point
        bool bNonTerminalExists = false;
        for (std::map<String,BisonSymbolInfo>::const_iterator it = expectedSymbols.begin();
             it != expectedSymbols.end(); ++it) if (!it->second.isTerminalSymbol) { bNonTerminalExists = true; break; };
        if (!bNonTerminalExists) {
            // all possibilites are terminal symbaols, so try to find the least
            // common string all possibilites start with from the left
            String sCommon;
            for (int i = 0; true; ++i) {
                char c;
                for (std::map<String,BisonSymbolInfo>::const_iterator it = expectedSymbols.begin();
                     it != expectedSymbols.end(); ++it)
                {
                    if (i >= it->second.nextExpectedChars.size())
                        goto commonSearchEndLabel;
                    if (it == expectedSymbols.begin())
                        c = it->second.nextExpectedChars[i];
                    if (c != it->second.nextExpectedChars[i])
                        goto commonSearchEndLabel;
                    if (it == --expectedSymbols.end())
                        sCommon += c;
                }
            }
            commonSearchEndLabel:
            if (!sCommon.empty()) result += LSCP_SHK_SUGGEST_BACK + sCommon;
#if DEBUG_SHELL_INTERACTION
            printf("Common possibility: '%s'\n", sCommon.c_str());
#endif
        }
    }

#if DEBUG_SHELL_INTERACTION
    printf("%s\n", result.c_str());
#endif

    return result;
}

/**
 * Clears input buffer.
 */
void restart(yyparse_param_t* pparam, int& yychar) {
    bytes = 0;
    ptr   = 0;
    sLastError = "";
    sParsed = "";
}

}
