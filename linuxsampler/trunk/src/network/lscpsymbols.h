/* A Bison parser, made by GNU Bison 1.875a.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     CHAR = 258,
     DOTNUM = 259,
     NUMBER = 260,
     SP = 261,
     LF = 262,
     CR = 263,
     ADD = 264,
     GET = 265,
     LOAD = 266,
     REMOVE = 267,
     SET = 268,
     SUBSCRIBE = 269,
     UNSUBSCRIBE = 270,
     RESET = 271,
     QUIT = 272,
     CHANNEL = 273,
     NOTIFICATION = 274,
     AVAILABLE_ENGINES = 275,
     CHANNELS = 276,
     INFO = 277,
     BUFFER_FILL = 278,
     STREAM_COUNT = 279,
     VOICE_COUNT = 280,
     INSTRUMENT = 281,
     ENGINE = 282,
     AUDIO_OUTPUT_CHANNEL = 283,
     AUDIO_OUTPUT_TYPE = 284,
     MIDI_INPUT_PORT = 285,
     MIDI_INPUT_CHANNEL = 286,
     MIDI_INPUT_TYPE = 287,
     VOLUME = 288,
     BYTES = 289,
     PERCENTAGE = 290,
     ALSA = 291,
     JACK = 292
   };
#endif
#define CHAR 258
#define DOTNUM 259
#define NUMBER 260
#define SP 261
#define LF 262
#define CR 263
#define ADD 264
#define GET 265
#define LOAD 266
#define REMOVE 267
#define SET 268
#define SUBSCRIBE 269
#define UNSUBSCRIBE 270
#define RESET 271
#define QUIT 272
#define CHANNEL 273
#define NOTIFICATION 274
#define AVAILABLE_ENGINES 275
#define CHANNELS 276
#define INFO 277
#define BUFFER_FILL 278
#define STREAM_COUNT 279
#define VOICE_COUNT 280
#define INSTRUMENT 281
#define ENGINE 282
#define AUDIO_OUTPUT_CHANNEL 283
#define AUDIO_OUTPUT_TYPE 284
#define MIDI_INPUT_PORT 285
#define MIDI_INPUT_CHANNEL 286
#define MIDI_INPUT_TYPE 287
#define VOLUME 288
#define BYTES 289
#define PERCENTAGE 290
#define ALSA 291
#define JACK 292




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif





