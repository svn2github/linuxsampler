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
#include "lscpsymbols.h"

/// handle for a client connection (FIXME: doesn't work for more than one network connections of course)
int hSession;

%}

%option reentrant

DIGIT           [0-9]

%%

" "                                     { return SP; }
\n                                      { return LF; }
\r                                      { return CR; }
("+"|"-")?{DIGIT}+"."{DIGIT}+           { yylval->Dotnum = atof(yytext); return DOTNUM; }
ADD                                     { return ADD; }
GET                                     { return GET; }
LOAD                                    { return LOAD; }
REMOVE                                  { return REMOVE; }
SET                                     { return SET; }
SUBSCRIBE                               { return SUBSCRIBE; }
UNSUBSCRIBE                             { return UNSUBSCRIBE; }
CHANNEL                                 { return CHANNEL; }
NOTIFICATION                            { return NOTIFICATION; }
AVAILABLE_ENGINES                       { return AVAILABLE_ENGINES; }
CHANNELS                                { return CHANNELS; }
INFO                                    { return INFO; }
BUFFER_FILL                             { return BUFFER_FILL; }
STREAM_COUNT                            { return STREAM_COUNT; }
VOICE_COUNT                             { return VOICE_COUNT; }
INSTRUMENT                              { return INSTRUMENT; }
ENGINE                                  { return ENGINE; }
AUDIO_OUTPUT_CHANNEL                    { return AUDIO_OUTPUT_CHANNEL; }
AUDIO_OUTPUT_TYPE                       { return AUDIO_OUTPUT_TYPE; }
MIDI_INPUT_PORT                         { return MIDI_INPUT_PORT; }
MIDI_INPUT_CHANNEL                      { return MIDI_INPUT_CHANNEL; }
MIDI_INPUT_TYPE                         { return MIDI_INPUT_TYPE; }
VOLUME                                  { return VOLUME; }
BYTES                                   { return BYTES; }
PERCENTAGE                              { return PERCENTAGE; }
ALSA                                    { return ALSA; }
JACK                                    { return JACK; }
RESET                                   { return RESET; }
QUIT                                    { return QUIT; }
0|([1-9]{DIGIT}*)                       { yylval->Number = atoi(yytext); return NUMBER; }
.                                       { yylval->Char = yytext[0]; return CHAR; }

%%

/**
 * We provide our own version of yywrap() so we don't have to link against
 * the lex library.
 */
int yywrap(yyscan_t yyscanner) {
    return 1; // continue scanning
}
