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
     EQ = 265,
     ADD = 266,
     GET = 267,
     CREATE = 268,
     DESTROY = 269,
     LIST = 270,
     LOAD = 271,
     REMOVE = 272,
     SET = 273,
     SUBSCRIBE = 274,
     UNSUBSCRIBE = 275,
     RESET = 276,
     QUIT = 277,
     CHANNEL = 278,
     NOTIFICATION = 279,
     AVAILABLE_ENGINES = 280,
     AVAILABLE_AUDIO_OUTPUT_DRIVERS = 281,
     CHANNELS = 282,
     INFO = 283,
     BUFFER_FILL = 284,
     STREAM_COUNT = 285,
     VOICE_COUNT = 286,
     INSTRUMENT = 287,
     ENGINE = 288,
     AUDIO_OUTPUT_CHANNEL = 289,
     AUDIO_OUTPUT_CHANNEL_PARAMETER = 290,
     AUDIO_OUTPUT_DEVICE = 291,
     AUDIO_OUTPUT_DEVICES = 292,
     AUDIO_OUTPUT_DEVICE_PARAMETER = 293,
     AUDIO_OUTPUT_DRIVER = 294,
     AUDIO_OUTPUT_DRIVER_PARAMETER = 295,
     MIDI_INPUT_PORT = 296,
     MIDI_INPUT_CHANNEL = 297,
     MIDI_INPUT_TYPE = 298,
     VOLUME = 299,
     BYTES = 300,
     PERCENTAGE = 301
   };
#endif
#define CHAR 258
#define DOTNUM 259
#define NUMBER 260
#define SP 261
#define LF 262
#define CR 263
#define HASH 264
#define EQ 265
#define ADD 266
#define GET 267
#define CREATE 268
#define DESTROY 269
#define LIST 270
#define LOAD 271
#define REMOVE 272
#define SET 273
#define SUBSCRIBE 274
#define UNSUBSCRIBE 275
#define RESET 276
#define QUIT 277
#define CHANNEL 278
#define NOTIFICATION 279
#define AVAILABLE_ENGINES 280
#define AVAILABLE_AUDIO_OUTPUT_DRIVERS 281
#define CHANNELS 282
#define INFO 283
#define BUFFER_FILL 284
#define STREAM_COUNT 285
#define VOICE_COUNT 286
#define INSTRUMENT 287
#define ENGINE 288
#define AUDIO_OUTPUT_CHANNEL 289
#define AUDIO_OUTPUT_CHANNEL_PARAMETER 290
#define AUDIO_OUTPUT_DEVICE 291
#define AUDIO_OUTPUT_DEVICES 292
#define AUDIO_OUTPUT_DEVICE_PARAMETER 293
#define AUDIO_OUTPUT_DRIVER 294
#define AUDIO_OUTPUT_DRIVER_PARAMETER 295
#define MIDI_INPUT_PORT 296
#define MIDI_INPUT_CHANNEL 297
#define MIDI_INPUT_TYPE 298
#define VOLUME 299
#define BYTES 300
#define PERCENTAGE 301




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif





