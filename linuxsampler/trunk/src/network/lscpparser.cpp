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
     LOAD_BACKGROUND = 273,
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
     MIDI_INPUT_PORT = 298,
     MIDI_INPUT_CHANNEL = 299,
     MIDI_INPUT_TYPE = 300,
     VOLUME = 301,
     BYTES = 302,
     PERCENTAGE = 303,
     MISCELLANEOUS = 304
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
#define LOAD_BACKGROUND 273
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
#define MIDI_INPUT_PORT 298
#define MIDI_INPUT_CHANNEL 299
#define MIDI_INPUT_TYPE 300
#define VOLUME 301
#define BYTES 302
#define PERCENTAGE 303
#define MISCELLANEOUS 304




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

bool background;


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
#line 211 "y.tab.c"

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
#define YYFINAL  32
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   219

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  29
/* YYNRULES -- Number of rules. */
#define YYNRULES  89
/* YYNRULES -- Number of states. */
#define YYNSTATES  228

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   304

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
      45,    46,    47,    48,    49
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     5,     9,    14,    15,    17,    19,    21,
      23,    26,    29,    32,    35,    39,    43,    47,    51,    55,
      59,    63,    69,    73,    77,    81,    87,    89,    91,    93,
      95,    97,    99,   101,   103,   105,   107,   109,   111,   113,
     115,   117,   123,   131,   141,   143,   149,   157,   167,   169,
     175,   183,   189,   195,   201,   209,   219,   223,   229,   233,
     237,   241,   245,   251,   259,   265,   271,   277,   283,   287,
     293,   295,   297,   299,   305,   309,   311,   313,   315,   317,
     319,   321,   323,   325,   327,   329,   331,   333,   335,   337
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      51,     0,    -1,    52,    -1,    51,     8,    52,    -1,    51,
       9,     8,    52,    -1,    -1,    53,    -1,    54,    -1,     1,
      -1,    10,    -1,    53,    10,    -1,    53,     7,    -1,    53,
       5,    -1,    53,    78,    -1,    12,     7,    25,    -1,    13,
       7,    57,    -1,    14,     7,    59,    -1,    15,     7,    60,
      -1,    16,     7,    65,    -1,    17,     7,    61,    -1,    18,
       7,    61,    -1,    19,     7,    25,     7,    70,    -1,    20,
       7,    58,    -1,    21,     7,    55,    -1,    22,     7,    56,
      -1,    23,     7,    25,     7,    70,    -1,    24,    -1,    29,
      -1,    33,    -1,    32,    -1,    31,    -1,    30,    -1,    49,
      -1,    29,    -1,    33,    -1,    32,    -1,    31,    -1,    30,
      -1,    49,    -1,    27,    -1,    28,    -1,    41,     7,    30,
       7,    78,    -1,    42,     7,    30,     7,    78,     7,    78,
      -1,    42,     7,    30,     7,    78,     7,    78,     7,    63,
      -1,    39,    -1,    38,     7,    30,     7,     5,    -1,    36,
       7,    30,     7,     5,     7,     5,    -1,    37,     7,    30,
       7,     5,     7,     5,     7,    78,    -1,    29,    -1,    25,
       7,    30,     7,    70,    -1,    25,     7,    31,     7,    64,
       7,    70,    -1,    25,     7,    32,     7,    70,    -1,    25,
       7,    33,     7,    70,    -1,    35,     7,    30,     7,    74,
      -1,    40,     7,     5,     7,    78,    11,    77,    -1,    37,
       7,     5,     7,     5,     7,    78,    11,    77,    -1,    25,
       7,    62,    -1,    38,     7,    78,     7,    63,    -1,    38,
       7,    78,    -1,    38,     7,     5,    -1,    34,     7,    66,
      -1,    35,     7,    67,    -1,    38,     7,    70,     7,     5,
      -1,    36,     7,    70,     7,    72,     7,    72,    -1,    43,
       7,    70,     7,    75,    -1,    44,     7,    70,     7,    73,
      -1,    45,     7,    70,     7,    68,    -1,    46,     7,    70,
       7,    69,    -1,    78,    11,    77,    -1,    63,     7,    78,
      11,    77,    -1,    47,    -1,    48,    -1,    39,    -1,    76,
       7,    71,     7,    70,    -1,    74,     7,    70,    -1,    78,
      -1,     4,    -1,     5,    -1,     5,    -1,     5,    -1,     5,
      -1,     5,    -1,    78,    -1,     6,    -1,     6,    -1,     6,
      -1,     5,    -1,     4,    -1,     3,    -1,    78,     3,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned char yyrline[] =
{
       0,    78,    78,    79,    80,    83,    84,    85,    86,    89,
      90,    91,    92,    93,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   111,   112,   113,
     114,   115,   116,   119,   120,   121,   122,   123,   124,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   144,   145,   146,   149,   150,   153,
     156,   157,   160,   161,   162,   163,   164,   165,   168,   169,
     172,   173,   176,   179,   182,   185,   188,   189,   192,   195,
     198,   201,   204,   207,   210,   213,   214,   215,   218,   219
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CHAR", "DOTNUM", "NUMBER", "STRINGVAL", 
  "SP", "LF", "CR", "HASH", "EQ", "ADD", "GET", "CREATE", "DESTROY", 
  "LIST", "LOAD", "LOAD_BACKGROUND", "REMOVE", "SET", "SUBSCRIBE", 
  "UNSUBSCRIBE", "RESET", "QUIT", "CHANNEL", "NOTIFICATION", 
  "AVAILABLE_ENGINES", "AVAILABLE_AUDIO_OUTPUT_DRIVERS", "CHANNELS", 
  "INFO", "BUFFER_FILL", "STREAM_COUNT", "VOICE_COUNT", "INSTRUMENT", 
  "ENGINE", "AUDIO_OUTPUT_CHANNEL", "AUDIO_OUTPUT_CHANNEL_PARAMETER", 
  "AUDIO_OUTPUT_DEVICE", "AUDIO_OUTPUT_DEVICES", 
  "AUDIO_OUTPUT_DEVICE_PARAMETER", "AUDIO_OUTPUT_DRIVER", 
  "AUDIO_OUTPUT_DRIVER_PARAMETER", "MIDI_INPUT_PORT", 
  "MIDI_INPUT_CHANNEL", "MIDI_INPUT_TYPE", "VOLUME", "BYTES", 
  "PERCENTAGE", "MISCELLANEOUS", "$accept", "input", "line", "comment", 
  "command", "subscribe_event", "unsubscribe_event", "get_instruction", 
  "set_instruction", "create_instruction", "destroy_instruction", 
  "load_instruction", "set_chan_instruction", "key_val_list", 
  "buffer_size_type", "list_instruction", "load_instr_args", 
  "load_engine_args", "midi_input_type", "volume", "sampler_channel", 
  "instrument_index", "audio_output_channel", "midi_input_channel", 
  "engine_name", "midi_input_port", "filename", "param_val", "string", 0
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
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    50,    51,    51,    51,    52,    52,    52,    52,    53,
      53,    53,    53,    53,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    55,    55,    55,
      55,    55,    55,    56,    56,    56,    56,    56,    56,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    58,    58,    58,    59,    59,    60,
      61,    61,    62,    62,    62,    62,    62,    62,    63,    63,
      64,    64,    65,    66,    67,    68,    69,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    77,    77,    78,    78
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     3,     4,     0,     1,     1,     1,     1,
       2,     2,     2,     2,     3,     3,     3,     3,     3,     3,
       3,     5,     3,     3,     3,     5,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     5,     7,     9,     1,     5,     7,     9,     1,     5,
       7,     5,     5,     5,     7,     9,     3,     5,     3,     3,
       3,     3,     5,     7,     5,     5,     5,     5,     3,     5,
       1,     1,     1,     5,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     8,     9,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    26,     0,     2,     6,     7,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,     0,     0,    88,    12,    11,    10,    13,
      14,     0,    39,    40,    48,     0,     0,     0,     0,    44,
       0,     0,    15,     0,    16,     0,    17,    72,    18,     0,
       0,    19,    20,     0,     0,     0,     0,    22,    27,    31,
      30,    29,    28,    32,    23,    33,    37,    36,    35,    34,
      38,    24,     0,     3,     0,    89,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     4,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    58,    59,    84,    60,     0,    61,     0,
      82,    78,    21,     0,     0,     0,     0,     0,     0,    56,
       0,     0,    25,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    49,    70,    71,     0,    51,    52,
      53,     0,     0,    45,    41,     0,    57,     0,    79,     0,
      74,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    50,    46,     0,    42,     0,    87,
      86,    85,    68,    73,    80,     0,    62,    83,    64,    81,
      65,    66,    75,    76,    77,    67,     0,    54,     0,     0,
       0,     0,     0,    47,    43,    69,    63,    55
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,    16,    17,    18,    19,    74,    81,    52,    67,    54,
      56,    61,   129,   166,   157,    58,   116,   118,   211,   215,
     122,   169,   205,   210,   119,   208,   117,   202,   120
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -191
static const short yypact[] =
{
       4,  -191,  -191,     2,    22,    24,    37,    85,    87,    96,
      99,   107,   109,   110,   111,  -191,    34,  -191,    97,  -191,
     -14,    45,   -23,    77,    80,   -27,   -27,    95,    27,     8,
      29,   101,  -191,     4,   113,  -191,  -191,  -191,  -191,   119,
    -191,   120,  -191,  -191,  -191,   121,   122,   123,   124,  -191,
     125,   126,  -191,   127,  -191,   129,  -191,  -191,  -191,   130,
     131,  -191,  -191,   132,   133,   134,   135,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
    -191,  -191,   136,  -191,     4,  -191,    78,   114,   115,   116,
     117,   118,   128,   146,   145,   147,   146,   149,    52,   150,
     151,   149,  -191,   144,   152,   153,   154,   155,   156,   159,
     160,   161,   162,     3,  -191,  -191,  -191,   163,  -191,   164,
     119,  -191,  -191,   166,   168,   169,   170,   171,   172,  -191,
     173,   174,  -191,   149,    18,   149,   149,   146,   177,   178,
     179,   146,   146,   146,   180,   149,   149,   149,   149,   149,
     149,   149,   181,   146,  -191,  -191,  -191,   182,  -191,  -191,
    -191,   183,   184,  -191,   119,    86,   185,    60,  -191,   186,
    -191,   187,   188,   189,   190,   191,   192,   195,    65,   149,
     198,   199,   146,   146,    50,   149,   200,   201,   202,   204,
     146,   108,   146,    50,  -191,  -191,   203,    98,    66,  -191,
    -191,  -191,  -191,  -191,  -191,   205,  -191,  -191,  -191,  -191,
    -191,  -191,   119,  -191,  -191,  -191,    88,  -191,   146,   146,
      50,   200,    50,   119,   185,  -191,  -191,  -191
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
    -191,  -191,   -31,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
    -191,   193,  -191,   -67,  -191,  -191,  -191,  -191,  -191,  -191,
    -100,  -191,   -64,  -191,    51,  -191,  -191,  -190,   -18
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -6
static const short yytable[] =
{
      39,   132,    83,   217,    -5,     1,    85,    59,    60,    20,
     143,    40,    -5,    -5,     2,    53,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    21,
     225,    22,   227,   154,    32,   158,   159,    68,    69,    70,
      71,    72,    33,    34,    23,   170,   171,   172,   173,   174,
     175,   176,    64,   102,   199,   200,   201,    73,    75,    76,
      77,    78,    79,    85,    65,   155,   156,    66,    85,    85,
      41,   184,    42,    43,    44,   113,   193,   220,    80,   194,
      45,    46,    47,    48,    49,   203,    50,    51,   123,    85,
     124,    85,    24,   182,    25,   125,   126,   127,   128,   222,
      35,    85,    36,    26,    37,   219,    27,    38,   103,   104,
     105,   106,   213,   214,    28,    55,    29,    30,    31,    57,
      63,    84,    85,   164,   165,   167,    82,    86,    87,    88,
      89,    90,    91,    92,    93,   178,    94,    95,    96,    97,
      98,    99,   100,   101,   107,   108,   109,   110,   111,    35,
     114,   133,   224,   115,   121,   130,   131,   226,   112,   134,
     135,   136,   137,   138,   197,   198,   139,   140,   141,   142,
     144,   145,   212,   146,   216,   147,   148,   149,   150,   151,
     152,   153,   161,   162,   163,   168,   177,     0,   160,   179,
     180,   181,   183,   185,   186,   187,   188,   189,   190,   191,
     223,   167,   192,   195,   196,   204,   206,     0,   207,   209,
     218,     0,   221,     0,     0,     0,     0,     0,     0,    62
};

static const short yycheck[] =
{
      18,   101,    33,   193,     0,     1,     3,    34,    35,     7,
       7,    25,     8,     9,    10,    38,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,     7,
     220,     7,   222,   133,     0,   135,   136,    29,    30,    31,
      32,    33,     8,     9,     7,   145,   146,   147,   148,   149,
     150,   151,    25,    84,     4,     5,     6,    49,    29,    30,
      31,    32,    33,     3,    37,    47,    48,    40,     3,     3,
      25,    11,    27,    28,    29,    93,    11,    11,    49,   179,
      35,    36,    37,    38,    39,   185,    41,    42,    36,     3,
      38,     3,     7,     7,     7,    43,    44,    45,    46,    11,
       3,     3,     5,     7,     7,     7,     7,    10,    30,    31,
      32,    33,     4,     5,     7,    38,     7,     7,     7,    39,
      25,     8,     3,   141,   142,   143,    25,     7,     7,     7,
       7,     7,     7,     7,     7,   153,     7,     7,     7,     7,
       7,     7,     7,     7,    30,    30,    30,    30,    30,     3,
       5,     7,   219,     6,     5,     5,     5,   221,    30,     7,
       7,     7,     7,     7,   182,   183,     7,     7,     7,     7,
       7,     7,   190,     7,   192,     7,     7,     7,     7,     7,
       7,     7,     5,     5,     5,     5,     5,    -1,   137,     7,
       7,     7,     7,     7,     7,     7,     7,     7,     7,     7,
     218,   219,     7,     5,     5,     5,     5,    -1,     6,     5,
       7,    -1,     7,    -1,    -1,    -1,    -1,    -1,    -1,    26
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     1,    10,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    51,    52,    53,    54,
       7,     7,     7,     7,     7,     7,     7,     7,     7,     7,
       7,     7,     0,     8,     9,     3,     5,     7,    10,    78,
      25,    25,    27,    28,    29,    35,    36,    37,    38,    39,
      41,    42,    57,    38,    59,    38,    60,    39,    65,    34,
      35,    61,    61,    25,    25,    37,    40,    58,    29,    30,
      31,    32,    33,    49,    55,    29,    30,    31,    32,    33,
      49,    56,    25,    52,     8,     3,     7,     7,     7,     7,
       7,     7,     7,     7,     7,     7,     7,     7,     7,     7,
       7,     7,    52,    30,    31,    32,    33,    30,    30,    30,
      30,    30,    30,    78,     5,     6,    66,    76,    67,    74,
      78,     5,    70,    36,    38,    43,    44,    45,    46,    62,
       5,     5,    70,     7,     7,     7,     7,     7,     7,     7,
       7,     7,     7,     7,     7,     7,     7,     7,     7,     7,
       7,     7,     7,     7,    70,    47,    48,    64,    70,    70,
      74,     5,     5,     5,    78,    78,    63,    78,     5,    71,
      70,    70,    70,    70,    70,    70,    70,     5,    78,     7,
       7,     7,     7,     7,    11,     7,     7,     7,     7,     7,
       7,     7,     7,    11,    70,     5,     5,    78,    78,     4,
       5,     6,    77,    70,     5,    72,     5,     6,    75,     5,
      73,    68,    78,     4,     5,    69,    78,    77,     7,     7,
      11,     7,    11,    78,    63,    77,    72,    77
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
#line 85 "lscp.y"
    { LSCPSERVER->AnswerClient(yyvsp[0].String); }
    break;

  case 8:
#line 86 "lscp.y"
    { LSCPSERVER->AnswerClient("Err:0:Unknown command.\r\n"); RESTART; return LSCP_SYNTAX_ERROR; }
    break;

  case 14:
#line 96 "lscp.y"
    { yyval.String = LSCPSERVER->AddChannel();                  }
    break;

  case 15:
#line 97 "lscp.y"
    { yyval.String = yyvsp[0].String;                                        }
    break;

  case 16:
#line 98 "lscp.y"
    { yyval.String = yyvsp[0].String;                                        }
    break;

  case 17:
#line 99 "lscp.y"
    { yyval.String = yyvsp[0].String;                                        }
    break;

  case 18:
#line 100 "lscp.y"
    { yyval.String = yyvsp[0].String;                                        }
    break;

  case 19:
#line 101 "lscp.y"
    { yyval.String = yyvsp[0].String; background = false;                    }
    break;

  case 20:
#line 102 "lscp.y"
    { yyval.String = yyvsp[0].String; background = true;                     }
    break;

  case 21:
#line 103 "lscp.y"
    { yyval.String = LSCPSERVER->RemoveChannel(yyvsp[0].Number);             }
    break;

  case 22:
#line 104 "lscp.y"
    { yyval.String = yyvsp[0].String;                                        }
    break;

  case 23:
#line 105 "lscp.y"
    { yyval.String = yyvsp[0].String;                                        }
    break;

  case 24:
#line 106 "lscp.y"
    { yyval.String = yyvsp[0].String;                                        }
    break;

  case 25:
#line 107 "lscp.y"
    { yyval.String = LSCPSERVER->ResetChannel(yyvsp[0].Number);              }
    break;

  case 26:
#line 108 "lscp.y"
    { LSCPSERVER->AnswerClient("Bye!\r\n"); return 0; }
    break;

  case 27:
#line 111 "lscp.y"
    { yyval.String = LSCPSERVER->SubscribeNotification(event_channels); }
    break;

  case 28:
#line 112 "lscp.y"
    { yyval.String = LSCPSERVER->SubscribeNotification(event_voice_count); }
    break;

  case 29:
#line 113 "lscp.y"
    { yyval.String = LSCPSERVER->SubscribeNotification(event_stream_count); }
    break;

  case 30:
#line 114 "lscp.y"
    { yyval.String = LSCPSERVER->SubscribeNotification(event_channel_buffer_fill); }
    break;

  case 31:
#line 115 "lscp.y"
    { yyval.String = LSCPSERVER->SubscribeNotification(event_channel_info); }
    break;

  case 32:
#line 116 "lscp.y"
    { yyval.String = LSCPSERVER->SubscribeNotification(event_misc); }
    break;

  case 33:
#line 119 "lscp.y"
    { yyval.String = LSCPSERVER->UnsubscribeNotification(event_channels); }
    break;

  case 34:
#line 120 "lscp.y"
    { yyval.String = LSCPSERVER->UnsubscribeNotification(event_voice_count); }
    break;

  case 35:
#line 121 "lscp.y"
    { yyval.String = LSCPSERVER->UnsubscribeNotification(event_stream_count); }
    break;

  case 36:
#line 122 "lscp.y"
    { yyval.String = LSCPSERVER->UnsubscribeNotification(event_channel_buffer_fill); }
    break;

  case 37:
#line 123 "lscp.y"
    { yyval.String = LSCPSERVER->UnsubscribeNotification(event_channel_info); }
    break;

  case 38:
#line 124 "lscp.y"
    { yyval.String = LSCPSERVER->UnsubscribeNotification(event_misc); }
    break;

  case 39:
#line 127 "lscp.y"
    { yyval.String = LSCPSERVER->GetAvailableEngines();                          }
    break;

  case 40:
#line 128 "lscp.y"
    { yyval.String = LSCPSERVER->GetAvailableAudioOutputDrivers();               }
    break;

  case 41:
#line 129 "lscp.y"
    { yyval.String = LSCPSERVER->GetAudioOutputDriverInfo(yyvsp[0].String);                   }
    break;

  case 42:
#line 130 "lscp.y"
    { yyval.String = LSCPSERVER->GetAudioOutputDriverParameterInfo(yyvsp[-2].String, yyvsp[0].String);      }
    break;

  case 43:
#line 131 "lscp.y"
    { yyval.String = LSCPSERVER->GetAudioOutputDriverParameterInfo(yyvsp[-4].String, yyvsp[-2].String, yyvsp[0].KeyValList);  }
    break;

  case 44:
#line 132 "lscp.y"
    { yyval.String = LSCPSERVER->GetAudioOutputDeviceCount();                    }
    break;

  case 45:
#line 133 "lscp.y"
    { yyval.String = LSCPSERVER->GetAudioOutputDeviceInfo(yyvsp[0].Number);                   }
    break;

  case 46:
#line 134 "lscp.y"
    { yyval.String = LSCPSERVER->GetAudioOutputChannelInfo(yyvsp[-2].Number, yyvsp[0].Number);              }
    break;

  case 47:
#line 135 "lscp.y"
    { yyval.String = LSCPSERVER->GetAudioOutputChannelParameterInfo(yyvsp[-4].Number, yyvsp[-2].Number, yyvsp[0].String); }
    break;

  case 48:
#line 136 "lscp.y"
    { yyval.String = LSCPSERVER->GetChannels();                                  }
    break;

  case 49:
#line 137 "lscp.y"
    { yyval.String = LSCPSERVER->GetChannelInfo(yyvsp[0].Number);                             }
    break;

  case 50:
#line 138 "lscp.y"
    { yyval.String = LSCPSERVER->GetBufferFill(yyvsp[-2].FillResponse, yyvsp[0].Number);                          }
    break;

  case 51:
#line 139 "lscp.y"
    { yyval.String = LSCPSERVER->GetStreamCount(yyvsp[0].Number);                             }
    break;

  case 52:
#line 140 "lscp.y"
    { yyval.String = LSCPSERVER->GetVoiceCount(yyvsp[0].Number);                              }
    break;

  case 53:
#line 141 "lscp.y"
    { yyval.String = LSCPSERVER->GetEngineInfo(yyvsp[0].String);                              }
    break;

  case 54:
#line 144 "lscp.y"
    { yyval.String = LSCPSERVER->SetAudioOutputDeviceParameter(yyvsp[-4].Number, yyvsp[-2].String, yyvsp[0].String);      }
    break;

  case 55:
#line 145 "lscp.y"
    { yyval.String = LSCPSERVER->SetAudioOutputChannelParameter(yyvsp[-6].Number, yyvsp[-4].Number, yyvsp[-2].String, yyvsp[0].String); }
    break;

  case 56:
#line 146 "lscp.y"
    { yyval.String = yyvsp[0].String;                                                         }
    break;

  case 57:
#line 149 "lscp.y"
    { yyval.String = LSCPSERVER->CreateAudioOutputDevice(yyvsp[-2].String,yyvsp[0].KeyValList); }
    break;

  case 58:
#line 150 "lscp.y"
    { yyval.String = LSCPSERVER->CreateAudioOutputDevice(yyvsp[0].String); }
    break;

  case 59:
#line 153 "lscp.y"
    { yyval.String = LSCPSERVER->DestroyAudioOutputDevice(yyvsp[0].Number); }
    break;

  case 60:
#line 156 "lscp.y"
    { yyval.String = yyvsp[0].String; }
    break;

  case 61:
#line 157 "lscp.y"
    { yyval.String = yyvsp[0].String; }
    break;

  case 62:
#line 160 "lscp.y"
    { yyval.String = LSCPSERVER->SetAudioOutputDevice(yyvsp[0].Number, yyvsp[-2].Number);      }
    break;

  case 63:
#line 161 "lscp.y"
    { yyval.String = LSCPSERVER->SetAudioOutputChannel(yyvsp[-2].Number, yyvsp[0].Number, yyvsp[-4].Number); }
    break;

  case 64:
#line 162 "lscp.y"
    { yyval.String = LSCPSERVER->SetMIDIInputPort(yyvsp[0].String, yyvsp[-2].Number);          }
    break;

  case 65:
#line 163 "lscp.y"
    { yyval.String = LSCPSERVER->SetMIDIInputChannel(yyvsp[0].Number, yyvsp[-2].Number);       }
    break;

  case 66:
#line 164 "lscp.y"
    { yyval.String = LSCPSERVER->SetMIDIInputType(yyvsp[0].String, yyvsp[-2].Number);          }
    break;

  case 67:
#line 165 "lscp.y"
    { yyval.String = LSCPSERVER->SetVolume(yyvsp[0].Dotnum, yyvsp[-2].Number);                 }
    break;

  case 68:
#line 168 "lscp.y"
    { yyval.KeyValList[yyvsp[-2].String] = yyvsp[0].String;          }
    break;

  case 69:
#line 169 "lscp.y"
    { yyval.KeyValList = yyvsp[-4].KeyValList; yyval.KeyValList[yyvsp[-2].String] = yyvsp[0].String; }
    break;

  case 70:
#line 172 "lscp.y"
    { yyval.FillResponse = fill_response_bytes;      }
    break;

  case 71:
#line 173 "lscp.y"
    { yyval.FillResponse = fill_response_percentage; }
    break;

  case 72:
#line 176 "lscp.y"
    { yyval.String = LSCPSERVER->GetAudioOutputDevices(); }
    break;

  case 73:
#line 179 "lscp.y"
    { yyval.String = LSCPSERVER->LoadInstrument(yyvsp[-4].String, yyvsp[-2].Number, yyvsp[0].Number, background); }
    break;

  case 74:
#line 182 "lscp.y"
    { yyval.String = LSCPSERVER->LoadEngine(yyvsp[-2].String, yyvsp[0].Number); }
    break;

  case 77:
#line 189 "lscp.y"
    { yyval.Dotnum = yyvsp[0].Number; }
    break;

  case 85:
#line 213 "lscp.y"
    { yyval.String = yyvsp[0].String;                                             }
    break;

  case 86:
#line 214 "lscp.y"
    { std::stringstream ss; ss << yyvsp[0].Number; yyval.String = ss.str();       }
    break;

  case 87:
#line 215 "lscp.y"
    { std::stringstream ss; ss << yyvsp[0].Dotnum; yyval.String = ss.str();       }
    break;

  case 88:
#line 218 "lscp.y"
    { std::string s; s = yyvsp[0].Char; yyval.String = s; }
    break;

  case 89:
#line 219 "lscp.y"
    { yyval.String = yyvsp[-1].String + yyvsp[0].Char;                  }
    break;


    }

/* Line 999 of yacc.c.  */
#line 1620 "y.tab.c"

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


#line 78 "lscp.y"


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


