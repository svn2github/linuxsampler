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




/* Copy the first part of user declarations.  */
#line 23 "lscp.y"


#include "lscpparser.h"
#include "lscpserver.h"

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
#line 212 "y.tab.c"

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
#define YYLAST   225

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  30
/* YYNRULES -- Number of rules. */
#define YYNRULES  92
/* YYNRULES -- Number of states. */
#define YYNSTATES  239

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   305

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
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     5,     9,    14,    15,    17,    19,    21,
      23,    26,    29,    32,    35,    39,    43,    47,    51,    55,
      59,    65,    69,    73,    77,    83,    85,    87,    89,    91,
      93,    95,    97,    99,   101,   103,   105,   107,   109,   111,
     113,   119,   127,   137,   139,   145,   153,   163,   165,   171,
     179,   185,   191,   197,   205,   215,   219,   225,   229,   233,
     237,   241,   247,   255,   261,   267,   273,   279,   285,   289,
     295,   297,   299,   301,   307,   315,   319,   321,   323,   325,
     327,   329,   331,   333,   335,   337,   339,   341,   343,   345,
     347,   349,   351
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      52,     0,    -1,    53,    -1,    52,     8,    53,    -1,    52,
       9,     8,    53,    -1,    -1,    54,    -1,    55,    -1,     1,
      -1,    10,    -1,    54,    10,    -1,    54,     7,    -1,    54,
       5,    -1,    54,    80,    -1,    12,     7,    25,    -1,    13,
       7,    58,    -1,    14,     7,    60,    -1,    15,     7,    61,
      -1,    16,     7,    66,    -1,    17,     7,    62,    -1,    19,
       7,    25,     7,    72,    -1,    20,     7,    59,    -1,    21,
       7,    56,    -1,    22,     7,    57,    -1,    23,     7,    25,
       7,    72,    -1,    24,    -1,    29,    -1,    33,    -1,    32,
      -1,    31,    -1,    30,    -1,    50,    -1,    29,    -1,    33,
      -1,    32,    -1,    31,    -1,    30,    -1,    50,    -1,    27,
      -1,    28,    -1,    41,     7,    30,     7,    80,    -1,    42,
       7,    30,     7,    80,     7,    80,    -1,    42,     7,    30,
       7,    80,     7,    80,     7,    64,    -1,    39,    -1,    38,
       7,    30,     7,     5,    -1,    36,     7,    30,     7,     5,
       7,     5,    -1,    37,     7,    30,     7,     5,     7,     5,
       7,    80,    -1,    29,    -1,    25,     7,    30,     7,    72,
      -1,    25,     7,    31,     7,    65,     7,    72,    -1,    25,
       7,    32,     7,    72,    -1,    25,     7,    33,     7,    72,
      -1,    35,     7,    30,     7,    76,    -1,    40,     7,     5,
       7,    80,    11,    79,    -1,    37,     7,     5,     7,     5,
       7,    80,    11,    79,    -1,    25,     7,    63,    -1,    38,
       7,    80,     7,    64,    -1,    38,     7,    80,    -1,    38,
       7,     5,    -1,    34,     7,    67,    -1,    35,     7,    68,
      -1,    38,     7,    72,     7,     5,    -1,    36,     7,    72,
       7,    74,     7,    74,    -1,    43,     7,    72,     7,    69,
      -1,    44,     7,    72,     7,    77,    -1,    45,     7,    72,
       7,    75,    -1,    46,     7,    72,     7,    70,    -1,    47,
       7,    72,     7,    71,    -1,    80,    11,    79,    -1,    64,
       7,    80,    11,    79,    -1,    48,    -1,    49,    -1,    39,
      -1,    78,     7,    73,     7,    72,    -1,    18,     7,    78,
       7,    73,     7,    72,    -1,    76,     7,    72,    -1,    80,
      -1,    80,    -1,     4,    -1,     5,    -1,     5,    -1,     5,
      -1,     5,    -1,     5,    -1,    80,    -1,     6,    -1,     6,
      -1,    80,    -1,     6,    -1,     5,    -1,     4,    -1,     3,
      -1,    80,     3,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned char yyrline[] =
{
       0,    77,    77,    78,    79,    82,    83,    84,    85,    88,
      89,    90,    91,    92,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   109,   110,   111,   112,
     113,   114,   117,   118,   119,   120,   121,   122,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   142,   143,   144,   147,   148,   151,   154,
     155,   158,   159,   160,   161,   162,   163,   164,   167,   168,
     171,   172,   175,   178,   179,   182,   185,   188,   191,   192,
     195,   198,   201,   204,   207,   210,   213,   214,   217,   218,
     219,   222,   223
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
  "UNSUBSCRIBE", "RESET", "QUIT", "CHANNEL", "NOTIFICATION", 
  "AVAILABLE_ENGINES", "AVAILABLE_AUDIO_OUTPUT_DRIVERS", "CHANNELS", 
  "INFO", "BUFFER_FILL", "STREAM_COUNT", "VOICE_COUNT", "INSTRUMENT", 
  "ENGINE", "AUDIO_OUTPUT_CHANNEL", "AUDIO_OUTPUT_CHANNEL_PARAMETER", 
  "AUDIO_OUTPUT_DEVICE", "AUDIO_OUTPUT_DEVICES", 
  "AUDIO_OUTPUT_DEVICE_PARAMETER", "AUDIO_OUTPUT_DRIVER", 
  "AUDIO_OUTPUT_DRIVER_PARAMETER", "AUDIO_OUTPUT_TYPE", "MIDI_INPUT_PORT", 
  "MIDI_INPUT_CHANNEL", "MIDI_INPUT_TYPE", "VOLUME", "BYTES", 
  "PERCENTAGE", "MISCELLANEOUS", "$accept", "input", "line", "comment", 
  "command", "subscribe_event", "unsubscribe_event", "get_instruction", 
  "set_instruction", "create_instruction", "destroy_instruction", 
  "load_instruction", "set_chan_instruction", "key_val_list", 
  "buffer_size_type", "list_instruction", "load_instr_args", 
  "load_engine_args", "audio_output_type", "midi_input_type", "volume", 
  "sampler_channel", "instrument_index", "audio_output_channel", 
  "midi_input_channel", "engine_name", "midi_input_port", "filename", 
  "param_val", "string", 0
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
     305
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    51,    52,    52,    52,    53,    53,    53,    53,    54,
      54,    54,    54,    54,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    56,    56,    56,    56,
      56,    56,    57,    57,    57,    57,    57,    57,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    59,    59,    59,    60,    60,    61,    62,
      62,    63,    63,    63,    63,    63,    63,    63,    64,    64,
      65,    65,    66,    67,    67,    68,    69,    70,    71,    71,
      72,    73,    74,    75,    76,    77,    78,    78,    79,    79,
      79,    80,    80
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     3,     4,     0,     1,     1,     1,     1,
       2,     2,     2,     2,     3,     3,     3,     3,     3,     3,
       5,     3,     3,     3,     5,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       5,     7,     9,     1,     5,     7,     9,     1,     5,     7,
       5,     5,     5,     7,     9,     3,     5,     3,     3,     3,
       3,     5,     7,     5,     5,     5,     5,     5,     3,     5,
       1,     1,     1,     5,     7,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     8,     9,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    25,     0,     2,     6,     7,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,     0,     0,    91,    12,    11,    10,    13,    14,     0,
      38,    39,    47,     0,     0,     0,     0,    43,     0,     0,
      15,     0,    16,     0,    17,    72,    18,     0,     0,    19,
       0,     0,     0,     0,    21,    26,    30,    29,    28,    27,
      31,    22,    32,    36,    35,    34,    33,    37,    23,     0,
       3,     0,    92,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     4,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      57,    58,    86,     0,    59,     0,    87,    60,     0,    84,
      80,    20,     0,     0,     0,     0,     0,     0,     0,    55,
       0,     0,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    48,    70,    71,     0,
      50,    51,    52,     0,     0,    44,    40,     0,    56,     0,
       0,    81,     0,    75,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      49,    45,     0,    41,     0,    90,    89,    88,    68,     0,
      73,    82,     0,    61,    63,    76,    85,    64,    83,    65,
      66,    77,    78,    79,    67,     0,    53,     0,     0,     0,
       0,     0,     0,    46,    42,    69,    74,    62,    54
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,    15,    16,    17,    18,    71,    78,    50,    64,    52,
      54,    59,   129,   168,   159,    56,   114,   117,   214,   220,
     224,   121,   172,   212,   219,   118,   217,   115,   208,   116
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -198
static const short yypact[] =
{
       3,  -198,  -198,    -1,     1,    30,    53,    81,    83,   115,
     116,   120,   121,   122,  -198,    21,  -198,    98,  -198,    22,
      43,   -10,    20,    82,    40,   105,     8,    11,    33,   106,
    -198,     3,   124,  -198,  -198,  -198,  -198,   131,  -198,   128,
    -198,  -198,  -198,   129,   130,   132,   133,  -198,   134,   135,
    -198,   136,  -198,   137,  -198,  -198,  -198,   138,   139,  -198,
     140,   141,   142,   143,  -198,  -198,  -198,  -198,  -198,  -198,
    -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,   144,
    -198,     3,  -198,    79,   123,   125,   126,   127,   145,   147,
     149,   153,    28,   149,   154,    51,   155,   156,   154,  -198,
     157,   158,   159,   160,   161,   164,   165,   166,   167,   171,
       2,  -198,  -198,   173,  -198,   175,   131,  -198,   176,   131,
    -198,  -198,   177,   178,   179,   180,   181,   182,   183,  -198,
     184,   185,  -198,   154,    68,   154,   154,   149,   188,   189,
     190,   149,   149,   149,   101,   191,   154,   154,   154,   154,
     154,   154,   154,   154,   192,   149,  -198,  -198,  -198,   193,
    -198,  -198,  -198,   194,   195,  -198,   131,     7,   196,    56,
     197,  -198,   198,  -198,   199,   200,   201,   202,   205,   206,
     207,   208,    66,   154,   211,   212,   149,   149,   109,   191,
     154,   213,   214,   149,   148,   215,   149,   114,   149,   109,
    -198,  -198,   216,    99,    88,  -198,  -198,  -198,  -198,   217,
    -198,  -198,   218,  -198,  -198,   131,  -198,  -198,  -198,  -198,
    -198,   131,  -198,  -198,  -198,    89,  -198,   149,   149,   109,
     154,   213,   109,   131,   196,  -198,  -198,  -198,  -198
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
    -198,  -198,   -24,  -198,  -198,  -198,  -198,  -198,  -198,  -198,
    -198,  -198,  -198,   -66,  -198,  -198,  -198,  -198,  -198,  -198,
    -198,   -97,   -26,   -33,  -198,    62,  -198,    77,  -197,   -17
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -6
static const short yytable[] =
{
      37,   132,   226,    -5,     1,    82,    19,    80,    20,   143,
      82,    -5,    -5,     2,   186,     3,     4,     5,     6,     7,
       8,    30,     9,    10,    11,    12,    13,    14,    51,    31,
      32,    33,   235,    61,   112,   238,   156,    21,   160,   161,
      65,    66,    67,    68,    69,    62,   113,    38,    63,   173,
     174,   175,   176,   177,   178,   179,   180,    99,    53,    82,
      22,    70,    72,    73,    74,    75,    76,   188,    39,    82,
      40,    41,    42,   110,    57,    58,   119,   199,    43,    44,
      45,    46,    47,    77,    48,    49,   200,   122,    23,   123,
      24,    82,    82,   210,   124,   125,   126,   127,   128,   229,
     232,    33,    82,    34,    33,    35,   228,   112,    36,   100,
     101,   102,   103,   205,   206,   207,   157,   158,   222,   223,
     119,    55,    25,    26,   166,   167,   169,    27,    28,    29,
      60,    79,    81,   236,    82,    83,    84,    85,   182,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    33,   104,   216,   105,   106,   107,   111,   120,
     130,   131,   234,   209,   133,   134,   135,   136,   137,   203,
     204,   138,   139,   140,   141,   108,   215,   109,   142,   221,
     144,   225,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   163,   164,   165,   171,   181,   237,   162,
     183,   184,   185,   187,   189,   190,   191,   192,   193,   194,
     233,   169,   195,   196,   197,   198,   201,   202,   211,   213,
     218,   170,     0,   227,   230,   231
};

static const short yycheck[] =
{
      17,    98,   199,     0,     1,     3,     7,    31,     7,     7,
       3,     8,     9,    10,     7,    12,    13,    14,    15,    16,
      17,     0,    19,    20,    21,    22,    23,    24,    38,     8,
       9,     3,   229,    25,     6,   232,   133,     7,   135,   136,
      29,    30,    31,    32,    33,    37,    18,    25,    40,   146,
     147,   148,   149,   150,   151,   152,   153,    81,    38,     3,
       7,    50,    29,    30,    31,    32,    33,    11,    25,     3,
      27,    28,    29,    90,    34,    35,    93,    11,    35,    36,
      37,    38,    39,    50,    41,    42,   183,    36,     7,    38,
       7,     3,     3,   190,    43,    44,    45,    46,    47,    11,
      11,     3,     3,     5,     3,     7,     7,     6,    10,    30,
      31,    32,    33,     4,     5,     6,    48,    49,     4,     5,
     137,    39,     7,     7,   141,   142,   143,     7,     7,     7,
      25,    25,     8,   230,     3,     7,     7,     7,   155,     7,
       7,     7,     7,     7,     7,     7,     7,     7,     7,     7,
       7,     7,     3,    30,     6,    30,    30,    30,     5,     5,
       5,     5,   228,   189,     7,     7,     7,     7,     7,   186,
     187,     7,     7,     7,     7,    30,   193,    30,     7,   196,
       7,   198,     7,     7,     7,     7,     7,     7,     7,     7,
       7,     7,     7,     5,     5,     5,     5,     5,   231,   137,
       7,     7,     7,     7,     7,     7,     7,     7,     7,     7,
     227,   228,     7,     7,     7,     7,     5,     5,     5,     5,
       5,   144,    -1,     7,     7,     7
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     1,    10,    12,    13,    14,    15,    16,    17,    19,
      20,    21,    22,    23,    24,    52,    53,    54,    55,     7,
       7,     7,     7,     7,     7,     7,     7,     7,     7,     7,
       0,     8,     9,     3,     5,     7,    10,    80,    25,    25,
      27,    28,    29,    35,    36,    37,    38,    39,    41,    42,
      58,    38,    60,    38,    61,    39,    66,    34,    35,    62,
      25,    25,    37,    40,    59,    29,    30,    31,    32,    33,
      50,    56,    29,    30,    31,    32,    33,    50,    57,    25,
      53,     8,     3,     7,     7,     7,     7,     7,     7,     7,
       7,     7,     7,     7,     7,     7,     7,     7,     7,    53,
      30,    31,    32,    33,    30,    30,    30,    30,    30,    30,
      80,     5,     6,    18,    67,    78,    80,    68,    76,    80,
       5,    72,    36,    38,    43,    44,    45,    46,    47,    63,
       5,     5,    72,     7,     7,     7,     7,     7,     7,     7,
       7,     7,     7,     7,     7,     7,     7,     7,     7,     7,
       7,     7,     7,     7,     7,     7,    72,    48,    49,    65,
      72,    72,    76,     5,     5,     5,    80,    80,    64,    80,
      78,     5,    73,    72,    72,    72,    72,    72,    72,    72,
      72,     5,    80,     7,     7,     7,     7,     7,    11,     7,
       7,     7,     7,     7,     7,     7,     7,     7,     7,    11,
      72,     5,     5,    80,    80,     4,     5,     6,    79,    73,
      72,     5,    74,     5,    69,    80,     6,    77,     5,    75,
      70,    80,     4,     5,    71,    80,    79,     7,     7,    11,
       7,     7,    11,    80,    64,    79,    72,    74,    79
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
        case 7:
#line 84 "lscp.y"
    { LSCPSERVER->AnswerClient(yyvsp[0].String); }
    break;

  case 8:
#line 85 "lscp.y"
    { LSCPSERVER->AnswerClient("Err:0:Unknown command.\r\n"); RESTART; return LSCP_SYNTAX_ERROR; }
    break;

  case 14:
#line 95 "lscp.y"
    { yyval.String = LSCPSERVER->AddChannel();                  }
    break;

  case 15:
#line 96 "lscp.y"
    { yyval.String = yyvsp[0].String;                                        }
    break;

  case 16:
#line 97 "lscp.y"
    { yyval.String = yyvsp[0].String;                                        }
    break;

  case 17:
#line 98 "lscp.y"
    { yyval.String = yyvsp[0].String;                                        }
    break;

  case 18:
#line 99 "lscp.y"
    { yyval.String = yyvsp[0].String;                                        }
    break;

  case 19:
#line 100 "lscp.y"
    { yyval.String = yyvsp[0].String;                                        }
    break;

  case 20:
#line 101 "lscp.y"
    { yyval.String = LSCPSERVER->RemoveChannel(yyvsp[0].Number);             }
    break;

  case 21:
#line 102 "lscp.y"
    { yyval.String = yyvsp[0].String;                                        }
    break;

  case 22:
#line 103 "lscp.y"
    { yyval.String = yyvsp[0].String;                                        }
    break;

  case 23:
#line 104 "lscp.y"
    { yyval.String = yyvsp[0].String;                                        }
    break;

  case 24:
#line 105 "lscp.y"
    { yyval.String = LSCPSERVER->ResetChannel(yyvsp[0].Number);              }
    break;

  case 25:
#line 106 "lscp.y"
    { LSCPSERVER->AnswerClient("Bye!\r\n"); return 0; }
    break;

  case 26:
#line 109 "lscp.y"
    { yyval.String = LSCPSERVER->SubscribeNotification(event_channels); }
    break;

  case 27:
#line 110 "lscp.y"
    { yyval.String = LSCPSERVER->SubscribeNotification(event_voice_count); }
    break;

  case 28:
#line 111 "lscp.y"
    { yyval.String = LSCPSERVER->SubscribeNotification(event_stream_count); }
    break;

  case 29:
#line 112 "lscp.y"
    { yyval.String = LSCPSERVER->SubscribeNotification(event_channel_buffer_fill); }
    break;

  case 30:
#line 113 "lscp.y"
    { yyval.String = LSCPSERVER->SubscribeNotification(event_channel_info); }
    break;

  case 31:
#line 114 "lscp.y"
    { yyval.String = LSCPSERVER->SubscribeNotification(event_misc); }
    break;

  case 32:
#line 117 "lscp.y"
    { yyval.String = LSCPSERVER->UnsubscribeNotification(event_channels); }
    break;

  case 33:
#line 118 "lscp.y"
    { yyval.String = LSCPSERVER->UnsubscribeNotification(event_voice_count); }
    break;

  case 34:
#line 119 "lscp.y"
    { yyval.String = LSCPSERVER->UnsubscribeNotification(event_stream_count); }
    break;

  case 35:
#line 120 "lscp.y"
    { yyval.String = LSCPSERVER->UnsubscribeNotification(event_channel_buffer_fill); }
    break;

  case 36:
#line 121 "lscp.y"
    { yyval.String = LSCPSERVER->UnsubscribeNotification(event_channel_info); }
    break;

  case 37:
#line 122 "lscp.y"
    { yyval.String = LSCPSERVER->UnsubscribeNotification(event_misc); }
    break;

  case 38:
#line 125 "lscp.y"
    { yyval.String = LSCPSERVER->GetAvailableEngines();                          }
    break;

  case 39:
#line 126 "lscp.y"
    { yyval.String = LSCPSERVER->GetAvailableAudioOutputDrivers();               }
    break;

  case 40:
#line 127 "lscp.y"
    { yyval.String = LSCPSERVER->GetAudioOutputDriverInfo(yyvsp[0].String);                   }
    break;

  case 41:
#line 128 "lscp.y"
    { yyval.String = LSCPSERVER->GetAudioOutputDriverParameterInfo(yyvsp[-2].String, yyvsp[0].String);      }
    break;

  case 42:
#line 129 "lscp.y"
    { yyval.String = LSCPSERVER->GetAudioOutputDriverParameterInfo(yyvsp[-4].String, yyvsp[-2].String, yyvsp[0].KeyValList);  }
    break;

  case 43:
#line 130 "lscp.y"
    { yyval.String = LSCPSERVER->GetAudioOutputDeviceCount();                    }
    break;

  case 44:
#line 131 "lscp.y"
    { yyval.String = LSCPSERVER->GetAudioOutputDeviceInfo(yyvsp[0].Number);                   }
    break;

  case 45:
#line 132 "lscp.y"
    { yyval.String = LSCPSERVER->GetAudioOutputChannelInfo(yyvsp[-2].Number, yyvsp[0].Number);              }
    break;

  case 46:
#line 133 "lscp.y"
    { yyval.String = LSCPSERVER->GetAudioOutputChannelParameterInfo(yyvsp[-4].Number, yyvsp[-2].Number, yyvsp[0].String); }
    break;

  case 47:
#line 134 "lscp.y"
    { yyval.String = LSCPSERVER->GetChannels();                                  }
    break;

  case 48:
#line 135 "lscp.y"
    { yyval.String = LSCPSERVER->GetChannelInfo(yyvsp[0].Number);                             }
    break;

  case 49:
#line 136 "lscp.y"
    { yyval.String = LSCPSERVER->GetBufferFill(yyvsp[-2].FillResponse, yyvsp[0].Number);                          }
    break;

  case 50:
#line 137 "lscp.y"
    { yyval.String = LSCPSERVER->GetStreamCount(yyvsp[0].Number);                             }
    break;

  case 51:
#line 138 "lscp.y"
    { yyval.String = LSCPSERVER->GetVoiceCount(yyvsp[0].Number);                              }
    break;

  case 52:
#line 139 "lscp.y"
    { yyval.String = LSCPSERVER->GetEngineInfo(yyvsp[0].String);                              }
    break;

  case 53:
#line 142 "lscp.y"
    { yyval.String = LSCPSERVER->SetAudioOutputDeviceParameter(yyvsp[-4].Number, yyvsp[-2].String, yyvsp[0].String);      }
    break;

  case 54:
#line 143 "lscp.y"
    { yyval.String = LSCPSERVER->SetAudioOutputChannelParameter(yyvsp[-6].Number, yyvsp[-4].Number, yyvsp[-2].String, yyvsp[0].String); }
    break;

  case 55:
#line 144 "lscp.y"
    { yyval.String = yyvsp[0].String;                                                         }
    break;

  case 56:
#line 147 "lscp.y"
    { yyval.String = LSCPSERVER->CreateAudioOutputDevice(yyvsp[-2].String,yyvsp[0].KeyValList); }
    break;

  case 57:
#line 148 "lscp.y"
    { yyval.String = LSCPSERVER->CreateAudioOutputDevice(yyvsp[0].String); }
    break;

  case 58:
#line 151 "lscp.y"
    { yyval.String = LSCPSERVER->DestroyAudioOutputDevice(yyvsp[0].Number); }
    break;

  case 59:
#line 154 "lscp.y"
    { yyval.String = yyvsp[0].String; }
    break;

  case 60:
#line 155 "lscp.y"
    { yyval.String = yyvsp[0].String; }
    break;

  case 61:
#line 158 "lscp.y"
    { yyval.String = LSCPSERVER->SetAudioOutputDevice(yyvsp[0].Number, yyvsp[-2].Number);      }
    break;

  case 62:
#line 159 "lscp.y"
    { yyval.String = LSCPSERVER->SetAudioOutputChannel(yyvsp[-2].Number, yyvsp[0].Number, yyvsp[-4].Number); }
    break;

  case 63:
#line 160 "lscp.y"
    { yyval.String = LSCPSERVER->SetAudioOutputType(yyvsp[0].String, yyvsp[-2].Number);        }
    break;

  case 64:
#line 161 "lscp.y"
    { yyval.String = LSCPSERVER->SetMIDIInputPort(yyvsp[0].String, yyvsp[-2].Number);          }
    break;

  case 65:
#line 162 "lscp.y"
    { yyval.String = LSCPSERVER->SetMIDIInputChannel(yyvsp[0].Number, yyvsp[-2].Number);       }
    break;

  case 66:
#line 163 "lscp.y"
    { yyval.String = LSCPSERVER->SetMIDIInputType(yyvsp[0].String, yyvsp[-2].Number);          }
    break;

  case 67:
#line 164 "lscp.y"
    { yyval.String = LSCPSERVER->SetVolume(yyvsp[0].Dotnum, yyvsp[-2].Number);                 }
    break;

  case 68:
#line 167 "lscp.y"
    { yyval.KeyValList[yyvsp[-2].String] = yyvsp[0].String;          }
    break;

  case 69:
#line 168 "lscp.y"
    { yyval.KeyValList = yyvsp[-4].KeyValList; yyval.KeyValList[yyvsp[-2].String] = yyvsp[0].String; }
    break;

  case 70:
#line 171 "lscp.y"
    { yyval.FillResponse = fill_response_bytes;      }
    break;

  case 71:
#line 172 "lscp.y"
    { yyval.FillResponse = fill_response_percentage; }
    break;

  case 72:
#line 175 "lscp.y"
    { yyval.String = LSCPSERVER->GetAudioOutputDevices(); }
    break;

  case 73:
#line 178 "lscp.y"
    { yyval.String = LSCPSERVER->LoadInstrument(yyvsp[-4].String, yyvsp[-2].Number, yyvsp[0].Number); }
    break;

  case 74:
#line 179 "lscp.y"
    { yyval.String = LSCPSERVER->LoadInstrument(yyvsp[-4].String, yyvsp[-2].Number, yyvsp[0].Number, true); }
    break;

  case 75:
#line 182 "lscp.y"
    { yyval.String = LSCPSERVER->LoadEngine(yyvsp[-2].String, yyvsp[0].Number); }
    break;

  case 79:
#line 192 "lscp.y"
    { yyval.Dotnum = yyvsp[0].Number; }
    break;

  case 88:
#line 217 "lscp.y"
    { yyval.String = yyvsp[0].String;                                             }
    break;

  case 89:
#line 218 "lscp.y"
    { std::stringstream ss; ss << yyvsp[0].Number; yyval.String = ss.str();       }
    break;

  case 90:
#line 219 "lscp.y"
    { std::stringstream ss; ss << yyvsp[0].Dotnum; yyval.String = ss.str();       }
    break;

  case 91:
#line 222 "lscp.y"
    { std::string s; s = yyvsp[0].Char; yyval.String = s; }
    break;

  case 92:
#line 223 "lscp.y"
    { yyval.String = yyvsp[-1].String + yyvsp[0].Char;                  }
    break;


    }

/* Line 999 of yacc.c.  */
#line 1639 "y.tab.c"

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


#line 77 "lscp.y"


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
    // flush input buffer
    static char buf[1024];
    while(recv(hSession, buf, 1024, MSG_DONTWAIT) > 0);
    // reset lookahead symbol
    yyclearin;
}


