/* A Bison parser, made by GNU Bison 1.875.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software Foundation, Inc.

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
     STRINGVAL = 261,
     SP = 262,
     LF = 263,
     CR = 264,
     HASH = 265,
     EQ = 266,
     ADD = 267,
     GET = 268,
     CREATE = 269,
     DESTROY = 270,
     LIST = 271,
     LOAD = 272,
     NON_MODAL = 273,
     REMOVE = 274,
     SET = 275,
     SUBSCRIBE = 276,
     UNSUBSCRIBE = 277,
     RESET = 278,
     QUIT = 279,
     CHANNEL = 280,
     NOTIFICATION = 281,
     AVAILABLE_ENGINES = 282,
     AVAILABLE_AUDIO_OUTPUT_DRIVERS = 283,
     CHANNELS = 284,
     INFO = 285,
     BUFFER_FILL = 286,
     STREAM_COUNT = 287,
     VOICE_COUNT = 288,
     INSTRUMENT = 289,
     ENGINE = 290,
     AUDIO_OUTPUT_CHANNEL = 291,
     AUDIO_OUTPUT_CHANNEL_PARAMETER = 292,
     AUDIO_OUTPUT_DEVICE = 293,
     AUDIO_OUTPUT_DEVICES = 294,
     AUDIO_OUTPUT_DEVICE_PARAMETER = 295,
     AUDIO_OUTPUT_DRIVER = 296,
     AUDIO_OUTPUT_DRIVER_PARAMETER = 297,
     AUDIO_OUTPUT_TYPE = 298,
     MIDI_INPUT_PORT = 299,
     MIDI_INPUT_CHANNEL = 300,
     MIDI_INPUT_TYPE = 301,
     VOLUME = 302,
     BYTES = 303,
     PERCENTAGE = 304,
     MISCELLANEOUS = 305
   };
#endif
#define CHAR 258
#define DOTNUM 259
#define NUMBER 260
#define STRINGVAL 261
#define SP 262
#define LF 263
#define CR 264
#define HASH 265
#define EQ 266
#define ADD 267
#define GET 268
#define CREATE 269
#define DESTROY 270
#define LIST 271
#define LOAD 272
#define NON_MODAL 273
#define REMOVE 274
#define SET 275
#define SUBSCRIBE 276
#define UNSUBSCRIBE 277
#define RESET 278
#define QUIT 279
#define CHANNEL 280
#define NOTIFICATION 281
#define AVAILABLE_ENGINES 282
#define AVAILABLE_AUDIO_OUTPUT_DRIVERS 283
#define CHANNELS 284
#define INFO 285
#define BUFFER_FILL 286
#define STREAM_COUNT 287
#define VOICE_COUNT 288
#define INSTRUMENT 289
#define ENGINE 290
#define AUDIO_OUTPUT_CHANNEL 291
#define AUDIO_OUTPUT_CHANNEL_PARAMETER 292
#define AUDIO_OUTPUT_DEVICE 293
#define AUDIO_OUTPUT_DEVICES 294
#define AUDIO_OUTPUT_DEVICE_PARAMETER 295
#define AUDIO_OUTPUT_DRIVER 296
#define AUDIO_OUTPUT_DRIVER_PARAMETER 297
#define AUDIO_OUTPUT_TYPE 298
#define MIDI_INPUT_PORT 299
#define MIDI_INPUT_CHANNEL 300
#define MIDI_INPUT_TYPE 301
#define VOLUME 302
#define BYTES 303
#define PERCENTAGE 304
#define MISCELLANEOUS 305




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif





