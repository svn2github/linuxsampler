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
     HASH = 264,
     ADD = 265,
     GET = 266,
     LOAD = 267,
     REMOVE = 268,
     SET = 269,
     SUBSCRIBE = 270,
     UNSUBSCRIBE = 271,
     RESET = 272,
     QUIT = 273,
     CHANNEL = 274,
     NOTIFICATION = 275,
     AVAILABLE_ENGINES = 276,
     CHANNELS = 277,
     INFO = 278,
     BUFFER_FILL = 279,
     STREAM_COUNT = 280,
     VOICE_COUNT = 281,
     INSTRUMENT = 282,
     ENGINE = 283,
     AUDIO_OUTPUT_CHANNEL = 284,
     AUDIO_OUTPUT_TYPE = 285,
     MIDI_INPUT_PORT = 286,
     MIDI_INPUT_CHANNEL = 287,
     MIDI_INPUT_TYPE = 288,
     VOLUME = 289,
     BYTES = 290,
     PERCENTAGE = 291,
     ALSA = 292,
     JACK = 293
   };
#endif
#define CHAR 258
#define DOTNUM 259
#define NUMBER 260
#define SP 261
#define LF 262
#define CR 263
#define HASH 264
#define ADD 265
#define GET 266
#define LOAD 267
#define REMOVE 268
#define SET 269
#define SUBSCRIBE 270
#define UNSUBSCRIBE 271
#define RESET 272
#define QUIT 273
#define CHANNEL 274
#define NOTIFICATION 275
#define AVAILABLE_ENGINES 276
#define CHANNELS 277
#define INFO 278
#define BUFFER_FILL 279
#define STREAM_COUNT 280
#define VOICE_COUNT 281
#define INSTRUMENT 282
#define ENGINE 283
#define AUDIO_OUTPUT_CHANNEL 284
#define AUDIO_OUTPUT_TYPE 285
#define MIDI_INPUT_PORT 286
#define MIDI_INPUT_CHANNEL 287
#define MIDI_INPUT_TYPE 288
#define VOLUME 289
#define BYTES 290
#define PERCENTAGE 291
#define ALSA 292
#define JACK 293




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif





