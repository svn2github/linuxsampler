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
     ECHO = 279,
     QUIT = 280,
     CHANNEL = 281,
     NOTIFICATION = 282,
     AVAILABLE_ENGINES = 283,
     AVAILABLE_AUDIO_OUTPUT_DRIVERS = 284,
     CHANNELS = 285,
     INFO = 286,
     BUFFER_FILL = 287,
     STREAM_COUNT = 288,
     VOICE_COUNT = 289,
     INSTRUMENT = 290,
     ENGINE = 291,
     AUDIO_OUTPUT_CHANNEL = 292,
     AUDIO_OUTPUT_CHANNEL_PARAMETER = 293,
     AUDIO_OUTPUT_DEVICE = 294,
     AUDIO_OUTPUT_DEVICES = 295,
     AUDIO_OUTPUT_DEVICE_PARAMETER = 296,
     AUDIO_OUTPUT_DRIVER = 297,
     AUDIO_OUTPUT_DRIVER_PARAMETER = 298,
     AUDIO_OUTPUT_TYPE = 299,
     MIDI_INPUT = 300,
     MIDI_INPUT_TYPE = 301,
     MIDI_INPUT_PORT = 302,
     MIDI_INPUT_CHANNEL = 303,
     VOLUME = 304,
     MIDI_INPUT_DRIVER = 305,
     MIDI_INPUT_DRIVER_PARAMETER = 306,
     AVAILABLE_MIDI_INPUT_DRIVERS = 307,
     MIDI_INPUT_DEVICE = 308,
     MIDI_INPUT_DEVICES = 309,
     MIDI_INPUT_DEVICE_PARAMETER = 310,
     MIDI_INPUT_PORT_PARAMETER = 311,
     BYTES = 312,
     PERCENTAGE = 313,
     MISCELLANEOUS = 314
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
#define ECHO 279
#define QUIT 280
#define CHANNEL 281
#define NOTIFICATION 282
#define AVAILABLE_ENGINES 283
#define AVAILABLE_AUDIO_OUTPUT_DRIVERS 284
#define CHANNELS 285
#define INFO 286
#define BUFFER_FILL 287
#define STREAM_COUNT 288
#define VOICE_COUNT 289
#define INSTRUMENT 290
#define ENGINE 291
#define AUDIO_OUTPUT_CHANNEL 292
#define AUDIO_OUTPUT_CHANNEL_PARAMETER 293
#define AUDIO_OUTPUT_DEVICE 294
#define AUDIO_OUTPUT_DEVICES 295
#define AUDIO_OUTPUT_DEVICE_PARAMETER 296
#define AUDIO_OUTPUT_DRIVER 297
#define AUDIO_OUTPUT_DRIVER_PARAMETER 298
#define AUDIO_OUTPUT_TYPE 299
#define MIDI_INPUT 300
#define MIDI_INPUT_TYPE 301
#define MIDI_INPUT_PORT 302
#define MIDI_INPUT_CHANNEL 303
#define VOLUME 304
#define MIDI_INPUT_DRIVER 305
#define MIDI_INPUT_DRIVER_PARAMETER 306
#define AVAILABLE_MIDI_INPUT_DRIVERS 307
#define MIDI_INPUT_DEVICE 308
#define MIDI_INPUT_DEVICES 309
#define MIDI_INPUT_DEVICE_PARAMETER 310
#define MIDI_INPUT_PORT_PARAMETER 311
#define BYTES 312
#define PERCENTAGE 313
#define MISCELLANEOUS 314




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif





