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

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 26 "lscp.y"


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



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 232 "y.tab.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  30
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   306

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  60
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  33
/* YYNRULES -- Number of rules. */
#define YYNRULES  111
/* YYNRULES -- Number of states. */
#define YYNSTATES  318

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   314

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     6,     7,     9,    11,    13,    15,    18,
      21,    24,    27,    31,    35,    39,    43,    47,    51,    57,
      61,    65,    69,    75,    77,    79,    81,    83,    85,    87,
      89,    91,    93,    95,    97,    99,   101,   103,   105,   111,
     119,   129,   131,   137,   145,   155,   157,   159,   165,   171,
     179,   189,   197,   207,   209,   215,   223,   229,   235,   241,
     249,   259,   267,   277,   281,   285,   291,   295,   301,   305,
     309,   313,   317,   321,   327,   335,   341,   351,   357,   363,
     369,   375,   381,   385,   391,   393,   395,   397,   399,   401,
     407,   415,   419,   421,   423,   425,   427,   429,   431,   433,
     435,   437,   439,   441,   443,   445,   447,   449,   451,   453,
     455,   457
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      61,     0,    -1,    62,     8,    -1,    -1,    63,    -1,    64,
      -1,     1,    -1,    10,    -1,    63,    10,    -1,    63,     7,
      -1,    63,     5,    -1,    63,    92,    -1,    12,     7,    26,
      -1,    13,     7,    67,    -1,    14,     7,    69,    -1,    15,
       7,    70,    -1,    16,     7,    75,    -1,    17,     7,    71,
      -1,    19,     7,    26,     7,    86,    -1,    20,     7,    68,
      -1,    21,     7,    65,    -1,    22,     7,    66,    -1,    23,
       7,    26,     7,    86,    -1,    25,    -1,    30,    -1,    34,
      -1,    33,    -1,    32,    -1,    31,    -1,    59,    -1,    30,
      -1,    34,    -1,    33,    -1,    32,    -1,    31,    -1,    59,
      -1,    28,    -1,    52,    -1,    50,     7,    31,     7,    92,
      -1,    51,     7,    31,     7,    92,     7,    92,    -1,    51,
       7,    31,     7,    92,     7,    92,     7,    73,    -1,    29,
      -1,    42,     7,    31,     7,    92,    -1,    43,     7,    31,
       7,    92,     7,    92,    -1,    43,     7,    31,     7,    92,
       7,    92,     7,    73,    -1,    40,    -1,    54,    -1,    39,
       7,    31,     7,     5,    -1,    53,     7,    31,     7,     5,
      -1,    47,     7,    31,     7,     5,     7,     5,    -1,    56,
       7,    31,     7,     5,     7,     5,     7,    92,    -1,    37,
       7,    31,     7,     5,     7,     5,    -1,    38,     7,    31,
       7,     5,     7,     5,     7,    92,    -1,    30,    -1,    26,
       7,    31,     7,    86,    -1,    26,     7,    32,     7,    74,
       7,    86,    -1,    26,     7,    33,     7,    86,    -1,    26,
       7,    34,     7,    86,    -1,    36,     7,    31,     7,    88,
      -1,    41,     7,     5,     7,    92,    11,    90,    -1,    38,
       7,     5,     7,     5,     7,    92,    11,    90,    -1,    55,
       7,     5,     7,    92,    11,    90,    -1,    56,     7,     5,
       7,     5,     7,    92,    11,    90,    -1,    26,     7,    72,
      -1,    24,     7,    91,    -1,    39,     7,    92,     7,    73,
      -1,    39,     7,    92,    -1,    53,     7,    92,     7,    73,
      -1,    53,     7,    92,    -1,    39,     7,     5,    -1,    53,
       7,     5,    -1,    35,     7,    76,    -1,    36,     7,    77,
      -1,    39,     7,    86,     7,    78,    -1,    37,     7,    86,
       7,    79,     7,    79,    -1,    44,     7,    86,     7,    80,
      -1,    45,     7,    86,     7,    81,     7,    82,     7,    83,
      -1,    53,     7,    86,     7,    81,    -1,    47,     7,    86,
       7,    82,    -1,    48,     7,    86,     7,    83,    -1,    46,
       7,    86,     7,    84,    -1,    49,     7,    86,     7,    85,
      -1,    92,    11,    90,    -1,    73,     7,    92,    11,    90,
      -1,    57,    -1,    58,    -1,    40,    -1,    54,    -1,    30,
      -1,    89,     7,    87,     7,    86,    -1,    18,     7,    89,
       7,    87,     7,    86,    -1,    88,     7,    86,    -1,     5,
      -1,     5,    -1,    92,    -1,     5,    -1,     5,    -1,     5,
      -1,    92,    -1,     4,    -1,     5,    -1,     5,    -1,     5,
      -1,    92,    -1,     6,    -1,     6,    -1,     5,    -1,     4,
      -1,     5,    -1,    92,    -1,     3,    -1,    92,     3,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned char yyrline[] =
{
       0,    82,    82,    84,    85,    86,    87,    90,    91,    92,
      93,    94,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   111,   112,   113,   114,   115,   116,
     119,   120,   121,   122,   123,   124,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   152,
     153,   154,   155,   156,   157,   160,   161,   162,   163,   166,
     167,   170,   171,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   185,   186,   189,   190,   193,   194,   195,   198,
     199,   202,   205,   208,   211,   214,   217,   220,   223,   226,
     227,   230,   233,   236,   239,   242,   243,   244,   247,   248,
     251,   252
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CHAR", "DOTNUM", "NUMBER", "STRINGVAL", 
  "SP", "LF", "CR", "HASH", "EQ", "ADD", "GET", "CREATE", "DESTROY", 
  "LIST", "LOAD", "NON_MODAL", "REMOVE", "SET", "SUBSCRIBE", 
  "UNSUBSCRIBE", "RESET", "ECHO", "QUIT", "CHANNEL", "NOTIFICATION", 
  "AVAILABLE_ENGINES", "AVAILABLE_AUDIO_OUTPUT_DRIVERS", "CHANNELS", 
  "INFO", "BUFFER_FILL", "STREAM_COUNT", "VOICE_COUNT", "INSTRUMENT", 
  "ENGINE", "AUDIO_OUTPUT_CHANNEL", "AUDIO_OUTPUT_CHANNEL_PARAMETER", 
  "AUDIO_OUTPUT_DEVICE", "AUDIO_OUTPUT_DEVICES", 
  "AUDIO_OUTPUT_DEVICE_PARAMETER", "AUDIO_OUTPUT_DRIVER", 
  "AUDIO_OUTPUT_DRIVER_PARAMETER", "AUDIO_OUTPUT_TYPE", "MIDI_INPUT", 
  "MIDI_INPUT_TYPE", "MIDI_INPUT_PORT", "MIDI_INPUT_CHANNEL", "VOLUME", 
  "MIDI_INPUT_DRIVER", "MIDI_INPUT_DRIVER_PARAMETER", 
  "AVAILABLE_MIDI_INPUT_DRIVERS", "MIDI_INPUT_DEVICE", 
  "MIDI_INPUT_DEVICES", "MIDI_INPUT_DEVICE_PARAMETER", 
  "MIDI_INPUT_PORT_PARAMETER", "BYTES", "PERCENTAGE", "MISCELLANEOUS", 
  "$accept", "input", "line", "comment", "command", "subscribe_event", 
  "unsubscribe_event", "get_instruction", "set_instruction", 
  "create_instruction", "destroy_instruction", "load_instruction", 
  "set_chan_instruction", "key_val_list", "buffer_size_type", 
  "list_instruction", "load_instr_args", "load_engine_args", 
  "audio_output_device", "audio_output_channel", "audio_output_type", 
  "midi_input_device", "midi_input_port", "midi_input_channel", 
  "midi_input_type", "volume", "sampler_channel", "instrument_index", 
  "engine_name", "filename", "param_val", "boolean", "string", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    60,    61,    62,    62,    62,    62,    63,    63,    63,
      63,    63,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    65,    65,    65,    65,    65,    65,
      66,    66,    66,    66,    66,    66,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    68,
      68,    68,    68,    68,    68,    69,    69,    69,    69,    70,
      70,    71,    71,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    73,    73,    74,    74,    75,    75,    75,    76,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      85,    86,    87,    88,    89,    90,    90,    90,    91,    91,
      92,    92
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     2,     0,     1,     1,     1,     1,     2,     2,
       2,     2,     3,     3,     3,     3,     3,     3,     5,     3,
       3,     3,     5,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     5,     7,
       9,     1,     5,     7,     9,     1,     1,     5,     5,     7,
       9,     7,     9,     1,     5,     7,     5,     5,     5,     7,
       9,     7,     9,     3,     3,     5,     3,     5,     3,     3,
       3,     3,     3,     5,     7,     5,     9,     5,     5,     5,
       5,     5,     3,     5,     1,     1,     1,     1,     1,     5,
       7,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     6,     7,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    23,     0,     0,     4,     5,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,     2,   110,    10,     9,     8,    11,    12,     0,    36,
      41,    53,     0,     0,     0,     0,    45,     0,     0,     0,
       0,     0,    37,     0,    46,     0,    13,     0,     0,    14,
       0,     0,    15,    88,    86,    87,    16,     0,     0,    17,
       0,     0,     0,     0,     0,     0,     0,    19,    24,    28,
      27,    26,    25,    29,    20,    30,    34,    33,    32,    31,
      35,    21,     0,   111,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    66,    68,    69,    70,   104,
       0,    71,     0,    72,     0,   103,   101,    18,   108,    64,
     109,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      63,     0,     0,     0,     0,    22,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    54,
      84,    85,     0,    56,    57,    58,     0,     0,    47,    42,
       0,     0,    38,     0,    48,     0,    65,     0,    67,     0,
     102,     0,    91,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      55,    51,     0,    43,    49,    39,     0,     0,   107,   106,
     105,    82,     0,    89,    93,     0,    92,    73,    75,    94,
      95,     0,    80,    98,    96,    78,    97,    79,    99,   100,
      81,    77,     0,    59,    61,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    52,    44,    40,    50,
      83,    90,    74,     0,    60,    62,     0,    76
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,    15,    16,    17,    18,    84,    91,    56,    77,    59,
      62,    69,   160,   216,   202,    66,   141,   143,   277,   275,
     278,   281,   285,   287,   282,   290,   147,   221,   144,   142,
     271,   149,   217
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -252
static const short yypact[] =
{
      85,  -252,  -252,    24,    39,    54,    73,    81,   105,   108,
     128,   144,   147,   148,  -252,    92,   109,   124,  -252,   126,
     -14,   -26,    -9,   -22,   110,   133,   -21,    25,    32,   136,
    -252,  -252,  -252,  -252,  -252,  -252,   153,  -252,   156,  -252,
    -252,  -252,   157,   158,   159,   160,  -252,   161,   162,   163,
     164,   165,  -252,   166,  -252,   167,  -252,   168,   169,  -252,
     170,   171,  -252,  -252,  -252,  -252,  -252,   174,   175,  -252,
     177,   178,   179,   180,   181,   182,   183,  -252,  -252,  -252,
    -252,  -252,  -252,  -252,  -252,  -252,  -252,  -252,  -252,  -252,
    -252,  -252,   184,  -252,   107,   172,   173,   176,   185,   186,
     187,   188,   189,   190,   192,   194,   191,   191,   193,   195,
       3,   191,   196,    78,    77,   197,   200,   201,   203,   196,
     202,   204,   205,   206,   207,   208,   220,   221,   222,   223,
     224,   226,   228,   229,   230,    38,    40,  -252,  -252,  -252,
     231,  -252,   233,  -252,   234,   153,  -252,  -252,  -252,  -252,
     153,   236,   237,   238,   239,   240,   241,   242,   243,   244,
    -252,   245,   246,   247,   248,  -252,   196,    90,   196,   196,
     191,   251,   252,   253,   191,   191,   254,   191,   191,   255,
     256,   191,   191,   257,   259,   196,   196,   196,   196,   196,
     196,   196,   196,   196,   196,   260,   191,   191,   261,  -252,
    -252,  -252,   262,  -252,  -252,  -252,   263,   264,  -252,   153,
      75,   265,   153,   106,  -252,   266,   267,    -1,   267,   268,
    -252,   269,  -252,   270,   271,   273,   274,   276,   277,   278,
     279,   280,   281,     8,    49,   282,   196,   285,   286,   191,
     287,   191,   288,   191,   138,   259,   196,   289,   290,   191,
     291,   191,   292,   293,   145,   291,   191,   138,   138,   191,
    -252,  -252,   294,   129,  -252,   130,   295,    74,  -252,  -252,
    -252,  -252,   296,  -252,  -252,   297,  -252,  -252,  -252,   153,
    -252,   298,  -252,   153,  -252,  -252,  -252,  -252,  -252,  -252,
    -252,  -252,    76,  -252,  -252,   100,   191,   191,   191,   191,
     138,   196,   289,   292,   138,   138,   153,   267,   267,   153,
    -252,  -252,  -252,   299,  -252,  -252,   293,  -252
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
    -252,  -252,  -252,  -252,  -252,  -252,  -252,  -252,  -252,  -252,
    -252,  -252,  -252,  -178,  -252,  -252,  -252,  -252,  -252,  -110,
    -252,   -62,  -108,  -120,  -252,  -252,  -118,   -48,    29,    27,
    -251,  -252,   -17
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -4
static const short yytable[] =
{
      36,   165,    93,    71,   218,    72,   293,   294,    63,   139,
     244,    93,    38,    57,    39,    40,    41,    73,    64,   257,
      74,   140,    42,    43,    44,    45,    46,    58,    47,    48,
      60,    19,    65,    49,    75,    76,    50,    51,    52,    53,
      54,    93,    55,    93,    61,   181,    20,   182,   199,   310,
     203,   204,    93,   314,   315,    78,    79,    80,    81,    82,
     258,    21,    85,    86,    87,    88,    89,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,    93,    93,    93,
      22,    32,   239,   148,    83,   300,     1,   304,    23,   135,
     136,    90,    30,    -3,   145,     2,   150,     3,     4,     5,
       6,     7,     8,    93,     9,    10,    11,    12,    13,    93,
      14,   305,    24,   241,   151,    25,   152,    31,   260,   307,
     308,   153,   154,   155,   156,   157,   158,    32,   273,    33,
     159,    34,    93,    93,    35,    26,   297,   298,   120,   121,
     122,   123,   268,   269,   270,    67,    68,   200,   201,   288,
     289,    27,    37,   145,    28,    29,    93,   209,   210,    70,
     212,   213,    92,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   233,
     234,   110,   111,   311,   112,   113,   114,   115,   116,   117,
     118,   119,   312,   291,    32,   313,   317,   272,   137,   205,
     138,   146,   161,   124,   125,   162,   163,   126,   164,   166,
     219,   167,   168,   169,   170,   171,   127,   128,   129,   130,
     131,   132,   263,   133,   265,   134,   267,   172,   173,   174,
     175,   176,   279,   177,   283,   178,   179,   180,   183,   292,
     184,   185,   295,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   206,   207,   208,   211,
     214,   215,     0,   139,   220,   232,   235,     0,     0,   236,
     237,   238,   240,   242,   243,   245,   246,   247,   248,   306,
     249,   250,   309,   251,   252,   253,   254,   255,   256,   259,
     261,   262,   264,   266,   274,   276,   280,   284,   286,     0,
       0,   296,   299,   301,   302,   303,   316
};

static const short yycheck[] =
{
      17,   119,     3,    24,   182,    26,   257,   258,    30,     6,
      11,     3,    26,    39,    28,    29,    30,    38,    40,    11,
      41,    18,    36,    37,    38,    39,    40,    53,    42,    43,
      39,     7,    54,    47,    55,    56,    50,    51,    52,    53,
      54,     3,    56,     3,    53,     7,     7,     7,   166,   300,
     168,   169,     3,   304,   305,    30,    31,    32,    33,    34,
      11,     7,    30,    31,    32,    33,    34,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,     3,     3,     3,
       7,     3,     7,     5,    59,    11,     1,    11,     7,   106,
     107,    59,     0,     8,   111,    10,   113,    12,    13,    14,
      15,    16,    17,     3,    19,    20,    21,    22,    23,     3,
      25,    11,     7,     7,    37,     7,    39,     8,   236,   297,
     298,    44,    45,    46,    47,    48,    49,     3,   246,     5,
      53,     7,     3,     3,    10,     7,     7,     7,    31,    32,
      33,    34,     4,     5,     6,    35,    36,    57,    58,     4,
       5,     7,    26,   170,     7,     7,     3,   174,   175,    26,
     177,   178,    26,     7,     7,     7,     7,     7,     7,     7,
       7,     7,     7,     7,     7,     7,     7,     7,     7,   196,
     197,     7,     7,   301,     7,     7,     7,     7,     7,     7,
       7,     7,   302,   255,     3,   303,   316,   245,     5,   170,
       5,     5,     5,    31,    31,     5,     5,    31,     5,     7,
     183,     7,     7,     7,     7,     7,    31,    31,    31,    31,
      31,    31,   239,    31,   241,    31,   243,     7,     7,     7,
       7,     7,   249,     7,   251,     7,     7,     7,     7,   256,
       7,     7,   259,     7,     7,     7,     7,     7,     7,     7,
       7,     7,     7,     7,     7,     7,     5,     5,     5,     5,
       5,     5,    -1,     6,     5,     5,     5,    -1,    -1,     7,
       7,     7,     7,     7,     7,     7,     7,     7,     7,   296,
       7,     7,   299,     7,     7,     7,     7,     7,     7,     7,
       5,     5,     5,     5,     5,     5,     5,     5,     5,    -1,
      -1,     7,     7,     7,     7,     7,     7
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     1,    10,    12,    13,    14,    15,    16,    17,    19,
      20,    21,    22,    23,    25,    61,    62,    63,    64,     7,
       7,     7,     7,     7,     7,     7,     7,     7,     7,     7,
       0,     8,     3,     5,     7,    10,    92,    26,    26,    28,
      29,    30,    36,    37,    38,    39,    40,    42,    43,    47,
      50,    51,    52,    53,    54,    56,    67,    39,    53,    69,
      39,    53,    70,    30,    40,    54,    75,    35,    36,    71,
      26,    24,    26,    38,    41,    55,    56,    68,    30,    31,
      32,    33,    34,    59,    65,    30,    31,    32,    33,    34,
      59,    66,    26,     3,     7,     7,     7,     7,     7,     7,
       7,     7,     7,     7,     7,     7,     7,     7,     7,     7,
       7,     7,     7,     7,     7,     7,     7,     7,     7,     7,
      31,    32,    33,    34,    31,    31,    31,    31,    31,    31,
      31,    31,    31,    31,    31,    92,    92,     5,     5,     6,
      18,    76,    89,    77,    88,    92,     5,    86,     5,    91,
      92,    37,    39,    44,    45,    46,    47,    48,    49,    53,
      72,     5,     5,     5,     5,    86,     7,     7,     7,     7,
       7,     7,     7,     7,     7,     7,     7,     7,     7,     7,
       7,     7,     7,     7,     7,     7,     7,     7,     7,     7,
       7,     7,     7,     7,     7,     7,     7,     7,     7,    86,
      57,    58,    74,    86,    86,    88,     5,     5,     5,    92,
      92,     5,    92,    92,     5,     5,    73,    92,    73,    89,
       5,    87,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,     5,    92,    92,     5,     7,     7,     7,     7,
       7,     7,     7,     7,    11,     7,     7,     7,     7,     7,
       7,     7,     7,     7,     7,     7,     7,    11,    11,     7,
      86,     5,     5,    92,     5,    92,     5,    92,     4,     5,
       6,    90,    87,    86,     5,    79,     5,    78,    80,    92,
       5,    81,    84,    92,     5,    82,     5,    83,     4,     5,
      85,    81,    92,    90,    90,    92,     7,     7,     7,     7,
      11,     7,     7,     7,    11,    11,    92,    73,    73,    92,
      90,    86,    79,    82,    90,    90,     7,    83
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrlab1


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)         \
  Current.first_line   = Rhs[1].first_line;      \
  Current.first_column = Rhs[1].first_column;    \
  Current.last_line    = Rhs[N].last_line;       \
  Current.last_column  = Rhs[N].last_column;
#endif

/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (cinluded).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylineno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylineno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */






/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  /* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
#line 84 "lscp.y"
    { return LSCP_DONE; }
    break;

  case 4:
#line 85 "lscp.y"
    { return LSCP_DONE; }
    break;

  case 5:
#line 86 "lscp.y"
    { LSCPSERVER->AnswerClient(yyvsp[0].String); return LSCP_DONE; }
    break;

  case 6:
#line 87 "lscp.y"
    { LSCPSERVER->AnswerClient("Err:0:Unknown command.\r\n"); RESTART; return LSCP_SYNTAX_ERROR; }
    break;

  case 12:
#line 97 "lscp.y"
    { yyval.String = LSCPSERVER->AddChannel();                  }
    break;

  case 13:
#line 98 "lscp.y"
    { yyval.String = yyvsp[0].String;                                        }
    break;

  case 14:
#line 99 "lscp.y"
    { yyval.String = yyvsp[0].String;                                        }
    break;

  case 15:
#line 100 "lscp.y"
    { yyval.String = yyvsp[0].String;                                        }
    break;

  case 16:
#line 101 "lscp.y"
    { yyval.String = yyvsp[0].String;                                        }
    break;

  case 17:
#line 102 "lscp.y"
    { yyval.String = yyvsp[0].String;                                        }
    break;

  case 18:
#line 103 "lscp.y"
    { yyval.String = LSCPSERVER->RemoveChannel(yyvsp[0].Number);             }
    break;

  case 19:
#line 104 "lscp.y"
    { yyval.String = yyvsp[0].String;                                        }
    break;

  case 20:
#line 105 "lscp.y"
    { yyval.String = yyvsp[0].String;                                        }
    break;

  case 21:
#line 106 "lscp.y"
    { yyval.String = yyvsp[0].String;                                        }
    break;

  case 22:
#line 107 "lscp.y"
    { yyval.String = LSCPSERVER->ResetChannel(yyvsp[0].Number);              }
    break;

  case 23:
#line 108 "lscp.y"
    { LSCPSERVER->AnswerClient("Bye!\r\n"); return LSCP_QUIT; }
    break;

  case 24:
#line 111 "lscp.y"
    { yyval.String = LSCPSERVER->SubscribeNotification(LSCPEvent::event_channels); }
    break;

  case 25:
#line 112 "lscp.y"
    { yyval.String = LSCPSERVER->SubscribeNotification(LSCPEvent::event_voice_count); }
    break;

  case 26:
#line 113 "lscp.y"
    { yyval.String = LSCPSERVER->SubscribeNotification(LSCPEvent::event_stream_count); }
    break;

  case 27:
#line 114 "lscp.y"
    { yyval.String = LSCPSERVER->SubscribeNotification(LSCPEvent::event_buffer_fill); }
    break;

  case 28:
#line 115 "lscp.y"
    { yyval.String = LSCPSERVER->SubscribeNotification(LSCPEvent::event_info); }
    break;

  case 29:
#line 116 "lscp.y"
    { yyval.String = LSCPSERVER->SubscribeNotification(LSCPEvent::event_misc); }
    break;

  case 30:
#line 119 "lscp.y"
    { yyval.String = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_channels); }
    break;

  case 31:
#line 120 "lscp.y"
    { yyval.String = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_voice_count); }
    break;

  case 32:
#line 121 "lscp.y"
    { yyval.String = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_stream_count); }
    break;

  case 33:
#line 122 "lscp.y"
    { yyval.String = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_buffer_fill); }
    break;

  case 34:
#line 123 "lscp.y"
    { yyval.String = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_info); }
    break;

  case 35:
#line 124 "lscp.y"
    { yyval.String = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_misc); }
    break;

  case 36:
#line 127 "lscp.y"
    { yyval.String = LSCPSERVER->GetAvailableEngines();       }
    break;

  case 37:
#line 128 "lscp.y"
    { yyval.String = LSCPSERVER->GetAvailableMidiInputDrivers();       }
    break;

  case 38:
#line 129 "lscp.y"
    { yyval.String = LSCPSERVER->GetMidiInputDriverInfo(yyvsp[0].String);       }
    break;

  case 39:
#line 130 "lscp.y"
    { yyval.String = LSCPSERVER->GetMidiInputDriverParameterInfo(yyvsp[-2].String, yyvsp[0].String);       }
    break;

  case 40:
#line 131 "lscp.y"
    { yyval.String = LSCPSERVER->GetMidiInputDriverParameterInfo(yyvsp[-4].String, yyvsp[-2].String, yyvsp[0].KeyValList);       }
    break;

  case 41:
#line 132 "lscp.y"
    { yyval.String = LSCPSERVER->GetAvailableAudioOutputDrivers();       }
    break;

  case 42:
#line 133 "lscp.y"
    { yyval.String = LSCPSERVER->GetAudioOutputDriverInfo(yyvsp[0].String);       }
    break;

  case 43:
#line 134 "lscp.y"
    { yyval.String = LSCPSERVER->GetAudioOutputDriverParameterInfo(yyvsp[-2].String, yyvsp[0].String);       }
    break;

  case 44:
#line 135 "lscp.y"
    { yyval.String = LSCPSERVER->GetAudioOutputDriverParameterInfo(yyvsp[-4].String, yyvsp[-2].String, yyvsp[0].KeyValList);       }
    break;

  case 45:
#line 136 "lscp.y"
    { yyval.String = LSCPSERVER->GetAudioOutputDeviceCount();       }
    break;

  case 46:
#line 137 "lscp.y"
    { yyval.String = LSCPSERVER->GetMidiInputDeviceCount();       }
    break;

  case 47:
#line 138 "lscp.y"
    { yyval.String = LSCPSERVER->GetAudioOutputDeviceInfo(yyvsp[0].Number);       }
    break;

  case 48:
#line 139 "lscp.y"
    { yyval.String = LSCPSERVER->GetMidiInputDeviceInfo(yyvsp[0].Number);       }
    break;

  case 49:
#line 140 "lscp.y"
    { yyval.String = LSCPSERVER->GetMidiInputPortInfo(yyvsp[-2].Number, yyvsp[0].Number);       }
    break;

  case 50:
#line 141 "lscp.y"
    { yyval.String = LSCPSERVER->GetMidiInputPortParameterInfo(yyvsp[-4].Number, yyvsp[-2].Number, yyvsp[0].String);       }
    break;

  case 51:
#line 142 "lscp.y"
    { yyval.String = LSCPSERVER->GetAudioOutputChannelInfo(yyvsp[-2].Number, yyvsp[0].Number);       }
    break;

  case 52:
#line 143 "lscp.y"
    { yyval.String = LSCPSERVER->GetAudioOutputChannelParameterInfo(yyvsp[-4].Number, yyvsp[-2].Number, yyvsp[0].String);       }
    break;

  case 53:
#line 144 "lscp.y"
    { yyval.String = LSCPSERVER->GetChannels();       }
    break;

  case 54:
#line 145 "lscp.y"
    { yyval.String = LSCPSERVER->GetChannelInfo(yyvsp[0].Number);       }
    break;

  case 55:
#line 146 "lscp.y"
    { yyval.String = LSCPSERVER->GetBufferFill(yyvsp[-2].FillResponse, yyvsp[0].Number);       }
    break;

  case 56:
#line 147 "lscp.y"
    { yyval.String = LSCPSERVER->GetStreamCount(yyvsp[0].Number);       }
    break;

  case 57:
#line 148 "lscp.y"
    { yyval.String = LSCPSERVER->GetVoiceCount(yyvsp[0].Number);       }
    break;

  case 58:
#line 149 "lscp.y"
    { yyval.String = LSCPSERVER->GetEngineInfo(yyvsp[0].String);       }
    break;

  case 59:
#line 152 "lscp.y"
    { yyval.String = LSCPSERVER->SetAudioOutputDeviceParameter(yyvsp[-4].Number, yyvsp[-2].String, yyvsp[0].String);       }
    break;

  case 60:
#line 153 "lscp.y"
    { yyval.String = LSCPSERVER->SetAudioOutputChannelParameter(yyvsp[-6].Number, yyvsp[-4].Number, yyvsp[-2].String, yyvsp[0].String);       }
    break;

  case 61:
#line 154 "lscp.y"
    { yyval.String = LSCPSERVER->SetMidiInputDeviceParameter(yyvsp[-4].Number, yyvsp[-2].String, yyvsp[0].String);       }
    break;

  case 62:
#line 155 "lscp.y"
    { yyval.String = LSCPSERVER->SetMidiInputPortParameter(yyvsp[-6].Number, yyvsp[-4].Number, yyvsp[-2].String, yyvsp[0].String);       }
    break;

  case 63:
#line 156 "lscp.y"
    { yyval.String = yyvsp[0].String;                                                         }
    break;

  case 64:
#line 157 "lscp.y"
    { yyval.String = LSCPSERVER->SetEcho((yyparse_param_t*) yyparse_param, yyvsp[0].Dotnum);  }
    break;

  case 65:
#line 160 "lscp.y"
    { yyval.String = LSCPSERVER->CreateAudioOutputDevice(yyvsp[-2].String,yyvsp[0].KeyValList); }
    break;

  case 66:
#line 161 "lscp.y"
    { yyval.String = LSCPSERVER->CreateAudioOutputDevice(yyvsp[0].String);    }
    break;

  case 67:
#line 162 "lscp.y"
    { yyval.String = LSCPSERVER->CreateMidiInputDevice(yyvsp[-2].String,yyvsp[0].KeyValList);   }
    break;

  case 68:
#line 163 "lscp.y"
    { yyval.String = LSCPSERVER->CreateMidiInputDevice(yyvsp[0].String);      }
    break;

  case 69:
#line 166 "lscp.y"
    { yyval.String = LSCPSERVER->DestroyAudioOutputDevice(yyvsp[0].Number);       }
    break;

  case 70:
#line 167 "lscp.y"
    { yyval.String = LSCPSERVER->DestroyMidiInputDevice(yyvsp[0].Number);         }
    break;

  case 71:
#line 170 "lscp.y"
    { yyval.String = yyvsp[0].String; }
    break;

  case 72:
#line 171 "lscp.y"
    { yyval.String = yyvsp[0].String; }
    break;

  case 73:
#line 174 "lscp.y"
    { yyval.String = LSCPSERVER->SetAudioOutputDevice(yyvsp[0].Number, yyvsp[-2].Number);      }
    break;

  case 74:
#line 175 "lscp.y"
    { yyval.String = LSCPSERVER->SetAudioOutputChannel(yyvsp[-2].Number, yyvsp[0].Number, yyvsp[-4].Number); }
    break;

  case 75:
#line 176 "lscp.y"
    { yyval.String = LSCPSERVER->SetAudioOutputType(yyvsp[0].String, yyvsp[-2].Number);        }
    break;

  case 76:
#line 177 "lscp.y"
    { yyval.String = LSCPSERVER->SetMIDIInput(yyvsp[-4].Number, yyvsp[-2].Number, yyvsp[0].Number, yyvsp[-6].Number);  }
    break;

  case 77:
#line 178 "lscp.y"
    { yyval.String = LSCPSERVER->SetMIDIInputDevice(yyvsp[0].Number, yyvsp[-2].Number);        }
    break;

  case 78:
#line 179 "lscp.y"
    { yyval.String = LSCPSERVER->SetMIDIInputPort(yyvsp[0].Number, yyvsp[-2].Number);          }
    break;

  case 79:
#line 180 "lscp.y"
    { yyval.String = LSCPSERVER->SetMIDIInputChannel(yyvsp[0].Number, yyvsp[-2].Number);       }
    break;

  case 80:
#line 181 "lscp.y"
    { yyval.String = LSCPSERVER->SetMIDIInputType(yyvsp[0].String, yyvsp[-2].Number);          }
    break;

  case 81:
#line 182 "lscp.y"
    { yyval.String = LSCPSERVER->SetVolume(yyvsp[0].Dotnum, yyvsp[-2].Number);                 }
    break;

  case 82:
#line 185 "lscp.y"
    { yyval.KeyValList[yyvsp[-2].String] = yyvsp[0].String;          }
    break;

  case 83:
#line 186 "lscp.y"
    { yyval.KeyValList = yyvsp[-4].KeyValList; yyval.KeyValList[yyvsp[-2].String] = yyvsp[0].String; }
    break;

  case 84:
#line 189 "lscp.y"
    { yyval.FillResponse = fill_response_bytes;      }
    break;

  case 85:
#line 190 "lscp.y"
    { yyval.FillResponse = fill_response_percentage; }
    break;

  case 86:
#line 193 "lscp.y"
    { yyval.String = LSCPSERVER->GetAudioOutputDevices(); }
    break;

  case 87:
#line 194 "lscp.y"
    { yyval.String = LSCPSERVER->GetMidiInputDevices();   }
    break;

  case 88:
#line 195 "lscp.y"
    { yyval.String = LSCPSERVER->ListChannels();          }
    break;

  case 89:
#line 198 "lscp.y"
    { yyval.String = LSCPSERVER->LoadInstrument(yyvsp[-4].String, yyvsp[-2].Number, yyvsp[0].Number);       }
    break;

  case 90:
#line 199 "lscp.y"
    { yyval.String = LSCPSERVER->LoadInstrument(yyvsp[-4].String, yyvsp[-2].Number, yyvsp[0].Number, true);       }
    break;

  case 91:
#line 202 "lscp.y"
    { yyval.String = LSCPSERVER->LoadEngine(yyvsp[-2].String, yyvsp[0].Number);       }
    break;

  case 100:
#line 227 "lscp.y"
    { yyval.Dotnum = yyvsp[0].Number; }
    break;

  case 105:
#line 242 "lscp.y"
    { yyval.String = yyvsp[0].String;                                             }
    break;

  case 106:
#line 243 "lscp.y"
    { std::stringstream ss; ss << yyvsp[0].Number; yyval.String = ss.str();       }
    break;

  case 107:
#line 244 "lscp.y"
    { std::stringstream ss; ss << yyvsp[0].Dotnum; yyval.String = ss.str();       }
    break;

  case 108:
#line 247 "lscp.y"
    { yyval.Dotnum = yyvsp[0].Number; }
    break;

  case 109:
#line 248 "lscp.y"
    { yyval.Dotnum = -1; }
    break;

  case 110:
#line 251 "lscp.y"
    { std::string s; s = yyvsp[0].Char; yyval.String = s; }
    break;

  case 111:
#line 252 "lscp.y"
    { yyval.String = yyvsp[-1].String + yyvsp[0].Char;                  }
    break;


    }

/* Line 999 of yacc.c.  */
#line 1834 "y.tab.c"

  yyvsp -= yylen;
  yyssp -= yylen;


  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("syntax error, unexpected ") + 1;
	  yysize += yystrlen (yytname[yytype]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        {
	  /* Pop the error token.  */
          YYPOPSTACK;
	  /* Pop the rest of the stack.  */
	  while (yyss < yyssp)
	    {
	      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
	      yydestruct (yystos[*yyssp], yyvsp);
	      YYPOPSTACK;
	    }
	  YYABORT;
        }

      YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
      yydestruct (yytoken, &yylval);
      yychar = YYEMPTY;

    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*----------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action.  |
`----------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      yyvsp--;
      yystate = *--yyssp;

      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 255 "lscp.y"


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


