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
#line 205 "y.tab.c"

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
#define YYLAST   222

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  29
/* YYNRULES -- Number of rules. */
#define YYNRULES  81
/* YYNRULES -- Number of states. */
#define YYNSTATES  225

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   301

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
      45,    46
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     5,     9,    14,    15,    17,    19,    21,
      23,    26,    29,    32,    35,    39,    43,    47,    51,    55,
      59,    65,    69,    75,    81,    87,    89,    91,    93,    99,
     107,   117,   119,   125,   133,   143,   145,   151,   159,   165,
     171,   177,   185,   193,   203,   213,   217,   223,   227,   231,
     235,   241,   249,   255,   261,   267,   273,   277,   283,   285,
     287,   289,   295,   299,   301,   303,   305,   307,   309,   311,
     313,   315,   317,   319,   321,   323,   327,   329,   331,   334,
     337,   339
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      48,     0,    -1,    49,    -1,    48,     7,    49,    -1,    48,
       8,     7,    49,    -1,    -1,    50,    -1,    51,    -1,     1,
      -1,     9,    -1,    50,     9,    -1,    50,     6,    -1,    50,
       5,    -1,    50,    75,    -1,    11,     6,    23,    -1,    12,
       6,    52,    -1,    13,     6,    54,    -1,    14,     6,    55,
      -1,    15,     6,    60,    -1,    16,     6,    56,    -1,    17,
       6,    23,     6,    65,    -1,    18,     6,    53,    -1,    19,
       6,    24,     6,    67,    -1,    20,     6,    24,     6,    70,
      -1,    21,     6,    23,     6,    65,    -1,    22,    -1,    25,
      -1,    26,    -1,    39,     6,    28,     6,    75,    -1,    40,
       6,    28,     6,    75,     6,    75,    -1,    40,     6,    28,
       6,    75,     6,    75,     6,    58,    -1,    37,    -1,    36,
       6,    28,     6,     5,    -1,    34,     6,    28,     6,     5,
       6,     5,    -1,    35,     6,    28,     6,     5,     6,     5,
       6,    75,    -1,    27,    -1,    23,     6,    28,     6,    65,
      -1,    23,     6,    29,     6,    59,     6,    65,    -1,    23,
       6,    30,     6,    65,    -1,    23,     6,    31,     6,    65,
      -1,    33,     6,    28,     6,    71,    -1,    38,     6,     5,
       6,    75,     6,    74,    -1,    38,     6,     5,     6,    75,
      10,    74,    -1,    35,     6,     5,     6,     5,     6,    75,
       6,    74,    -1,    35,     6,     5,     6,     5,     6,    75,
      10,    74,    -1,    23,     6,    57,    -1,    36,     6,    75,
       6,    58,    -1,    36,     6,     5,    -1,    32,     6,    61,
      -1,    33,     6,    62,    -1,    36,     6,    65,     6,     5,
      -1,    34,     6,    65,     6,    68,     6,    68,    -1,    41,
       6,    65,     6,    72,    -1,    42,     6,    65,     6,    69,
      -1,    43,     6,    65,     6,    63,    -1,    44,     6,    65,
       6,    64,    -1,    75,    10,    74,    -1,    58,     6,    75,
      10,    74,    -1,    45,    -1,    46,    -1,    37,    -1,    73,
       6,    66,     6,    65,    -1,    71,     6,    65,    -1,    75,
      -1,     4,    -1,     5,    -1,     5,    -1,     5,    -1,     5,
      -1,     5,    -1,     5,    -1,    74,    -1,    75,    -1,    74,
      -1,    74,    -1,    73,     6,    74,    -1,    75,    -1,     5,
      -1,    74,    75,    -1,    74,     5,    -1,     3,    -1,    75,
       3,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned char yyrline[] =
{
       0,    75,    75,    76,    77,    80,    81,    82,    83,    86,
      87,    88,    89,    90,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   124,   125,   126,   127,   128,   131,   134,   137,   138,
     141,   142,   143,   144,   145,   146,   149,   150,   152,   153,
     156,   159,   162,   165,   168,   169,   172,   175,   178,   181,
     184,   187,   190,   193,   196,   197,   200,   201,   202,   203,
     206,   207
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CHAR", "DOTNUM", "NUMBER", "SP", "LF", 
  "CR", "HASH", "EQ", "ADD", "GET", "CREATE", "DESTROY", "LIST", "LOAD", 
  "REMOVE", "SET", "SUBSCRIBE", "UNSUBSCRIBE", "RESET", "QUIT", "CHANNEL", 
  "NOTIFICATION", "AVAILABLE_ENGINES", "AVAILABLE_AUDIO_OUTPUT_DRIVERS", 
  "CHANNELS", "INFO", "BUFFER_FILL", "STREAM_COUNT", "VOICE_COUNT", 
  "INSTRUMENT", "ENGINE", "AUDIO_OUTPUT_CHANNEL", 
  "AUDIO_OUTPUT_CHANNEL_PARAMETER", "AUDIO_OUTPUT_DEVICE", 
  "AUDIO_OUTPUT_DEVICES", "AUDIO_OUTPUT_DEVICE_PARAMETER", 
  "AUDIO_OUTPUT_DRIVER", "AUDIO_OUTPUT_DRIVER_PARAMETER", 
  "MIDI_INPUT_PORT", "MIDI_INPUT_CHANNEL", "MIDI_INPUT_TYPE", "VOLUME", 
  "BYTES", "PERCENTAGE", "$accept", "input", "line", "comment", "command", 
  "get_instruction", "set_instruction", "create_instruction", 
  "destroy_instruction", "load_instruction", "set_chan_instruction", 
  "key_val_list", "buffer_size_type", "list_instruction", 
  "load_instr_args", "load_engine_args", "midi_input_type", "volume", 
  "sampler_channel", "instrument_index", "udp_port", 
  "audio_output_channel", "midi_input_channel", "session_id", 
  "engine_name", "midi_input_port", "filename", "alpha_num_string", 
  "string", 0
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
     295,   296,   297,   298,   299,   300,   301
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    47,    48,    48,    48,    49,    49,    49,    49,    50,
      50,    50,    50,    50,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    53,    53,    53,    53,    53,    54,    55,    56,    56,
      57,    57,    57,    57,    57,    57,    58,    58,    59,    59,
      60,    61,    62,    63,    64,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    73,    74,    74,    74,    74,
      75,    75
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     3,     4,     0,     1,     1,     1,     1,
       2,     2,     2,     2,     3,     3,     3,     3,     3,     3,
       5,     3,     5,     5,     5,     1,     1,     1,     5,     7,
       9,     1,     5,     7,     9,     1,     5,     7,     5,     5,
       5,     7,     7,     9,     9,     3,     5,     3,     3,     3,
       5,     7,     5,     5,     5,     5,     3,     5,     1,     1,
       1,     5,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     1,     2,     2,
       1,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     8,     9,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    25,     0,     2,     6,     7,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,     0,     0,    80,    12,    11,    10,    13,    14,     0,
      26,    27,    35,     0,     0,     0,     0,    31,     0,     0,
      15,     0,    16,     0,    17,    60,    18,     0,     0,    19,
       0,     0,     0,     0,    21,     0,     0,     0,     3,     0,
      81,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     4,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    47,    77,    48,     0,    74,    76,    49,     0,    72,
      66,    20,     0,     0,     0,     0,     0,     0,    45,     0,
       0,    68,    22,    23,    71,    24,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    79,    78,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    36,
      58,    59,     0,    38,    39,    40,     0,     0,    32,    28,
       0,    46,     0,    77,     0,    75,    62,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    37,    33,     0,    29,     0,    56,    61,    69,     0,
      50,    52,    73,    70,    53,    54,    63,    64,    65,    55,
       0,    41,    42,     0,     0,     0,     0,     0,     0,    34,
      30,    57,    51,    43,    44
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,    15,    16,    17,    18,    50,    64,    52,    54,    59,
     118,   161,   152,    56,   103,   107,   205,   209,   111,   164,
     122,   199,   204,   123,   108,   201,   104,   105,   106
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -86
static const short yypact[] =
{
       3,   -86,   -86,    21,    25,    43,    67,    86,    91,    96,
     105,   106,   108,   109,   -86,    28,   -86,    84,   -86,   -14,
       7,    80,    85,    83,     5,    87,    22,    99,   100,   102,
     -86,     3,   115,   -86,   -86,   -86,   -86,   123,   -86,   121,
     -86,   -86,   -86,   122,   128,   129,   130,   -86,   131,   132,
     -86,   133,   -86,   134,   -86,   -86,   -86,   135,   136,   -86,
     137,   138,   139,   140,   -86,   141,   143,   144,   -86,     3,
     -86,   -23,   101,   124,   125,   126,   127,   142,   148,   151,
      45,   148,   152,    38,   153,   154,   155,    45,   152,   -86,
     157,   158,   159,   160,   161,   162,   166,   167,   168,   169,
      23,   -86,   -86,   -86,   170,    93,   123,   -86,   171,   123,
     -86,   -86,   172,   174,   175,   176,   177,   178,   -86,   180,
     181,   -86,   -86,   -86,    93,   -86,   152,    40,   152,   152,
     148,   183,   184,   185,   148,   148,   148,    98,   -86,   123,
     152,   152,   152,   152,   152,   152,   152,   186,   148,   -86,
     -86,   -86,   187,   -86,   -86,   -86,   192,   193,   -86,   123,
      72,   194,    73,   195,   196,    93,   -86,   197,   199,   202,
     203,   204,   205,   206,    52,   152,   208,   209,   148,   148,
      45,   152,   210,   211,    45,   212,   148,   104,   148,    45,
      45,   -86,   -86,   213,    88,    74,    93,   -86,   -86,   214,
     -86,   -86,    93,   -86,   -86,   -86,   123,   -86,   -86,   -86,
      53,    93,    93,   148,   148,    45,   210,    45,    45,   123,
     194,    93,   -86,    93,    93
};

/* YYPGOTO[NTERM-NUM].  */
static const yysigned_char yypgoto[] =
{
     -86,   -86,   -30,   -86,   -86,   -86,   -86,   -86,   -86,   -86,
     -86,   -22,   -86,   -86,   -86,   -86,   -86,   -86,   -75,   -86,
     -86,     2,   -86,   -86,    92,   -86,   -86,   -85,   -17
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -68
static const short yytable[] =
{
      37,    68,   124,    -5,     1,    90,    91,    92,    93,    38,
      -5,    -5,     2,   125,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    70,    19,    30,   136,
      39,    20,    40,    41,    42,    31,    32,    57,    58,    89,
      43,    44,    45,    46,    47,    61,    48,    49,    33,    21,
     102,   149,   165,   153,   154,    70,    70,    62,   189,   217,
      63,   100,   190,   218,   109,   166,   167,   168,   169,   170,
     171,   172,   112,    22,   113,    70,    70,    70,   178,   114,
     115,   116,   117,   180,   215,   150,   151,    33,   139,    34,
      35,    70,    23,    36,   214,   196,    33,    24,   138,   202,
     191,    33,    25,   163,   211,   212,   197,   139,   207,   208,
      60,    26,    27,   109,    28,    29,    51,   159,   160,   162,
      55,    53,    69,    65,    66,    67,    70,    71,    72,    94,
     221,   174,   223,   224,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,   139,    87,
      88,    33,    95,    96,    97,    98,   101,   110,   119,   120,
     121,   194,   195,   126,   127,   128,   129,   130,   131,   206,
      99,   210,   132,   133,   134,   135,   137,   140,   141,   139,
     142,   143,   144,   145,   146,   139,   147,   148,   156,   157,
     158,   173,   220,   175,   139,   139,   219,   162,   176,   177,
     179,   -67,   181,   182,   139,   183,   139,   139,   184,   185,
     186,   187,   188,   192,   193,   198,   200,   203,   222,   213,
     216,     0,   155
};

static const short yycheck[] =
{
      17,    31,    87,     0,     1,    28,    29,    30,    31,    23,
       7,     8,     9,    88,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,     3,     6,     0,     6,
      23,     6,    25,    26,    27,     7,     8,    32,    33,    69,
      33,    34,    35,    36,    37,    23,    39,    40,     3,     6,
       5,   126,   137,   128,   129,     3,     3,    35,     6,     6,
      38,    78,    10,    10,    81,   140,   141,   142,   143,   144,
     145,   146,    34,     6,    36,     3,     3,     3,     6,    41,
      42,    43,    44,    10,    10,    45,    46,     3,   105,     5,
       6,     3,     6,     9,     6,   180,     3,     6,     5,   184,
     175,     3,     6,     5,   189,   190,   181,   124,     4,     5,
      23,     6,     6,   130,     6,     6,    36,   134,   135,   136,
      37,    36,     7,    24,    24,    23,     3,     6,     6,    28,
     215,   148,   217,   218,     6,     6,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     6,     6,   165,     6,
       6,     3,    28,    28,    28,    28,     5,     5,     5,     5,
       5,   178,   179,     6,     6,     6,     6,     6,     6,   186,
      28,   188,     6,     6,     6,     6,     6,     6,     6,   196,
       6,     6,     6,     6,     6,   202,     6,     6,     5,     5,
       5,     5,   214,     6,   211,   212,   213,   214,     6,     6,
       6,     6,     6,     6,   221,     6,   223,   224,     6,     6,
       6,     6,     6,     5,     5,     5,     5,     5,   216,     6,
       6,    -1,   130
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     1,     9,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    48,    49,    50,    51,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       0,     7,     8,     3,     5,     6,     9,    75,    23,    23,
      25,    26,    27,    33,    34,    35,    36,    37,    39,    40,
      52,    36,    54,    36,    55,    37,    60,    32,    33,    56,
      23,    23,    35,    38,    53,    24,    24,    23,    49,     7,
       3,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     6,    49,
      28,    29,    30,    31,    28,    28,    28,    28,    28,    28,
      75,     5,     5,    61,    73,    74,    75,    62,    71,    75,
       5,    65,    34,    36,    41,    42,    43,    44,    57,     5,
       5,     5,    67,    70,    74,    65,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     5,    75,
       6,     6,     6,     6,     6,     6,     6,     6,     6,    65,
      45,    46,    59,    65,    65,    71,     5,     5,     5,    75,
      75,    58,    75,     5,    66,    74,    65,    65,    65,    65,
      65,    65,    65,     5,    75,     6,     6,     6,     6,     6,
      10,     6,     6,     6,     6,     6,     6,     6,     6,     6,
      10,    65,     5,     5,    75,    75,    74,    65,     5,    68,
       5,    72,    74,     5,    69,    63,    75,     4,     5,    64,
      75,    74,    74,     6,     6,    10,     6,     6,    10,    75,
      58,    74,    68,    74,    74
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
#line 82 "lscp.y"
    { LSCPSERVER->AnswerClient(yyvsp[0].String); }
    break;

  case 8:
#line 83 "lscp.y"
    { LSCPSERVER->AnswerClient("Err:0:Unknown command.\r\n"); RESTART; return LSCP_SYNTAX_ERROR; }
    break;

  case 14:
#line 93 "lscp.y"
    { yyval.String = LSCPSERVER->AddChannel();                  }
    break;

  case 15:
#line 94 "lscp.y"
    { yyval.String = yyvsp[0].String;                                        }
    break;

  case 16:
#line 95 "lscp.y"
    { yyval.String = yyvsp[0].String;                                        }
    break;

  case 17:
#line 96 "lscp.y"
    { yyval.String = yyvsp[0].String;                                        }
    break;

  case 18:
#line 97 "lscp.y"
    { yyval.String = yyvsp[0].String;                                        }
    break;

  case 19:
#line 98 "lscp.y"
    { yyval.String = yyvsp[0].String;                                        }
    break;

  case 20:
#line 99 "lscp.y"
    { yyval.String = LSCPSERVER->RemoveChannel(yyvsp[0].Number);             }
    break;

  case 21:
#line 100 "lscp.y"
    { yyval.String = yyvsp[0].String;                                        }
    break;

  case 22:
#line 101 "lscp.y"
    { yyval.String = LSCPSERVER->SubscribeNotification(yyvsp[0].Number);     }
    break;

  case 23:
#line 102 "lscp.y"
    { yyval.String = LSCPSERVER->UnsubscribeNotification(yyvsp[0].String);   }
    break;

  case 24:
#line 103 "lscp.y"
    { yyval.String = LSCPSERVER->ResetChannel(yyvsp[0].Number);              }
    break;

  case 25:
#line 104 "lscp.y"
    { LSCPSERVER->AnswerClient("Bye!\r\n"); return 0; }
    break;

  case 26:
#line 107 "lscp.y"
    { yyval.String = LSCPSERVER->GetAvailableEngines();                          }
    break;

  case 27:
#line 108 "lscp.y"
    { yyval.String = LSCPSERVER->GetAvailableAudioOutputDrivers();               }
    break;

  case 28:
#line 109 "lscp.y"
    { yyval.String = LSCPSERVER->GetAudioOutputDriverInfo(yyvsp[0].String);                   }
    break;

  case 29:
#line 110 "lscp.y"
    { yyval.String = LSCPSERVER->GetAudioOutputDriverParameterInfo(yyvsp[-2].String, yyvsp[0].String);      }
    break;

  case 30:
#line 111 "lscp.y"
    { yyval.String = LSCPSERVER->GetAudioOutputDriverParameterInfo(yyvsp[-4].String, yyvsp[-2].String, yyvsp[0].KeyValList);  }
    break;

  case 31:
#line 112 "lscp.y"
    { yyval.String = LSCPSERVER->GetAudioOutputDeviceCount();                    }
    break;

  case 32:
#line 113 "lscp.y"
    { yyval.String = LSCPSERVER->GetAudioOutputDeviceInfo(yyvsp[0].Number);                   }
    break;

  case 33:
#line 114 "lscp.y"
    { yyval.String = LSCPSERVER->GetAudioOutputChannelInfo(yyvsp[-2].Number, yyvsp[0].Number);              }
    break;

  case 34:
#line 115 "lscp.y"
    { yyval.String = LSCPSERVER->GetAudioOutputChannelParameterInfo(yyvsp[-4].Number, yyvsp[-2].Number, yyvsp[0].String); }
    break;

  case 35:
#line 116 "lscp.y"
    { yyval.String = LSCPSERVER->GetChannels();                                  }
    break;

  case 36:
#line 117 "lscp.y"
    { yyval.String = LSCPSERVER->GetChannelInfo(yyvsp[0].Number);                             }
    break;

  case 37:
#line 118 "lscp.y"
    { yyval.String = LSCPSERVER->GetBufferFill(yyvsp[-2].FillResponse, yyvsp[0].Number);                          }
    break;

  case 38:
#line 119 "lscp.y"
    { yyval.String = LSCPSERVER->GetStreamCount(yyvsp[0].Number);                             }
    break;

  case 39:
#line 120 "lscp.y"
    { yyval.String = LSCPSERVER->GetVoiceCount(yyvsp[0].Number);                              }
    break;

  case 40:
#line 121 "lscp.y"
    { yyval.String = LSCPSERVER->GetEngineInfo(yyvsp[0].String);                              }
    break;

  case 41:
#line 124 "lscp.y"
    { yyval.String = LSCPSERVER->SetAudioOutputDeviceParameter(yyvsp[-4].Number, yyvsp[-2].String, yyvsp[0].String);      }
    break;

  case 42:
#line 125 "lscp.y"
    { yyval.String = LSCPSERVER->SetAudioOutputDeviceParameter(yyvsp[-4].Number, yyvsp[-2].String, yyvsp[0].String);      }
    break;

  case 43:
#line 126 "lscp.y"
    { yyval.String = LSCPSERVER->SetAudioOutputChannelParameter(yyvsp[-6].Number, yyvsp[-4].Number, yyvsp[-2].String, yyvsp[0].String); }
    break;

  case 44:
#line 127 "lscp.y"
    { yyval.String = LSCPSERVER->SetAudioOutputChannelParameter(yyvsp[-6].Number, yyvsp[-4].Number, yyvsp[-2].String, yyvsp[0].String); }
    break;

  case 45:
#line 128 "lscp.y"
    { yyval.String = yyvsp[0].String;                                                         }
    break;

  case 46:
#line 131 "lscp.y"
    { yyval.String = LSCPSERVER->CreateAudioOutputDevice(yyvsp[-2].String,yyvsp[0].KeyValList); }
    break;

  case 47:
#line 134 "lscp.y"
    { yyval.String = LSCPSERVER->DestroyAudioOutputDevice(yyvsp[0].Number); }
    break;

  case 48:
#line 137 "lscp.y"
    { yyval.String = yyvsp[0].String; }
    break;

  case 49:
#line 138 "lscp.y"
    { yyval.String = yyvsp[0].String; }
    break;

  case 50:
#line 141 "lscp.y"
    { yyval.String = LSCPSERVER->SetAudioOutputDevice(yyvsp[0].Number, yyvsp[-2].Number);      }
    break;

  case 51:
#line 142 "lscp.y"
    { yyval.String = LSCPSERVER->SetAudioOutputChannel(yyvsp[-2].Number, yyvsp[0].Number, yyvsp[-4].Number); }
    break;

  case 52:
#line 143 "lscp.y"
    { yyval.String = LSCPSERVER->SetMIDIInputPort(yyvsp[0].String, yyvsp[-2].Number);          }
    break;

  case 53:
#line 144 "lscp.y"
    { yyval.String = LSCPSERVER->SetMIDIInputChannel(yyvsp[0].Number, yyvsp[-2].Number);       }
    break;

  case 54:
#line 145 "lscp.y"
    { yyval.String = LSCPSERVER->SetMIDIInputType(yyvsp[0].String, yyvsp[-2].Number);          }
    break;

  case 55:
#line 146 "lscp.y"
    { yyval.String = LSCPSERVER->SetVolume(yyvsp[0].Dotnum, yyvsp[-2].Number);                 }
    break;

  case 56:
#line 149 "lscp.y"
    { yyval.KeyValList[yyvsp[-2].String] = yyvsp[0].String;          }
    break;

  case 57:
#line 150 "lscp.y"
    { yyval.KeyValList = yyvsp[-4].KeyValList; yyval.KeyValList[yyvsp[-2].String] = yyvsp[0].String; }
    break;

  case 58:
#line 152 "lscp.y"
    { yyval.FillResponse = fill_response_bytes;      }
    break;

  case 59:
#line 153 "lscp.y"
    { yyval.FillResponse = fill_response_percentage; }
    break;

  case 60:
#line 156 "lscp.y"
    { yyval.String = LSCPSERVER->GetAudioOutputDevices(); }
    break;

  case 61:
#line 159 "lscp.y"
    { yyval.String = LSCPSERVER->LoadInstrument(yyvsp[-4].String, yyvsp[-2].Number, yyvsp[0].Number); }
    break;

  case 62:
#line 162 "lscp.y"
    { yyval.String = LSCPSERVER->LoadEngine(yyvsp[-2].String, yyvsp[0].Number); }
    break;

  case 65:
#line 169 "lscp.y"
    { yyval.Dotnum = yyvsp[0].Number; }
    break;

  case 75:
#line 197 "lscp.y"
    { yyval.String = yyvsp[-2].String + ' ' + yyvsp[0].String; }
    break;

  case 76:
#line 200 "lscp.y"
    { yyval.String = yyvsp[0].String;                                             }
    break;

  case 77:
#line 201 "lscp.y"
    { std::stringstream ss; ss << yyvsp[0].Number; yyval.String = ss.str();       }
    break;

  case 78:
#line 202 "lscp.y"
    { yyval.String = yyvsp[-1].String + yyvsp[0].String;                                        }
    break;

  case 79:
#line 203 "lscp.y"
    { std::stringstream ss; ss << yyvsp[-1].String << yyvsp[0].Number; yyval.String = ss.str(); }
    break;

  case 80:
#line 206 "lscp.y"
    { std::string s; s = yyvsp[0].Char; yyval.String = s; }
    break;

  case 81:
#line 207 "lscp.y"
    { yyval.String = yyvsp[-1].String + yyvsp[0].Char;                  }
    break;


    }

/* Line 999 of yacc.c.  */
#line 1567 "y.tab.c"

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


#line 210 "lscp.y"


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


