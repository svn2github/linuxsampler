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
#line 187 "y.tab.c"

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
#define YYFINAL  22
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   123

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  24
/* YYNRULES -- Number of rules. */
#define YYNRULES  56
/* YYNRULES -- Number of states. */
#define YYNSTATES  136

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

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
      35,    36,    37
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned char yyprhs[] =
{
       0,     0,     3,     5,     9,    14,    15,    17,    19,    23,
      27,    31,    37,    43,    49,    55,    61,    63,    65,    67,
      73,    81,    87,    93,    99,   103,   107,   113,   119,   125,
     131,   137,   143,   145,   147,   153,   157,   159,   161,   163,
     165,   167,   169,   171,   173,   175,   177,   179,   181,   183,
     185,   189,   191,   193,   196,   199,   201
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      39,     0,    -1,    40,    -1,    39,     7,    40,    -1,    39,
       8,     7,    40,    -1,    -1,    41,    -1,     1,    -1,     9,
       6,    18,    -1,    10,     6,    42,    -1,    11,     6,    43,
      -1,    12,     6,    18,     6,    51,    -1,    13,     6,    18,
       6,    44,    -1,    14,     6,    19,     6,    53,    -1,    15,
       6,    19,     6,    56,    -1,    16,     6,    18,     6,    51,
      -1,    17,    -1,    20,    -1,    21,    -1,    18,     6,    22,
       6,    51,    -1,    18,     6,    23,     6,    45,     6,    51,
      -1,    18,     6,    24,     6,    51,    -1,    18,     6,    25,
       6,    51,    -1,    27,     6,    22,     6,    57,    -1,    26,
       6,    46,    -1,    27,     6,    47,    -1,    28,     6,    51,
       6,    54,    -1,    29,     6,    51,     6,    48,    -1,    30,
       6,    51,     6,    58,    -1,    31,     6,    51,     6,    55,
      -1,    32,     6,    51,     6,    49,    -1,    33,     6,    51,
       6,    50,    -1,    34,    -1,    35,    -1,    59,     6,    52,
       6,    51,    -1,    57,     6,    51,    -1,    36,    -1,    37,
      -1,    36,    -1,     4,    -1,     5,    -1,     5,    -1,     5,
      -1,     5,    -1,     5,    -1,     5,    -1,    60,    -1,    61,
      -1,    60,    -1,    60,    -1,    59,     6,    60,    -1,    61,
      -1,     5,    -1,    60,    61,    -1,    60,     5,    -1,     3,
      -1,    61,     3,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned char yyrline[] =
{
       0,    77,    77,    78,    79,    82,    83,    84,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    98,    99,   100,
     101,   102,   103,   104,   107,   108,   111,   112,   113,   114,
     115,   116,   119,   120,   123,   126,   129,   130,   133,   136,
     137,   140,   143,   146,   149,   152,   155,   158,   161,   164,
     165,   168,   169,   170,   171,   174,   175
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CHAR", "DOTNUM", "NUMBER", "SP", "LF", 
  "CR", "ADD", "GET", "LOAD", "REMOVE", "SET", "SUBSCRIBE", "UNSUBSCRIBE", 
  "RESET", "QUIT", "CHANNEL", "NOTIFICATION", "AVAILABLE_ENGINES", 
  "CHANNELS", "INFO", "BUFFER_FILL", "STREAM_COUNT", "VOICE_COUNT", 
  "INSTRUMENT", "ENGINE", "AUDIO_OUTPUT_CHANNEL", "AUDIO_OUTPUT_TYPE", 
  "MIDI_INPUT_PORT", "MIDI_INPUT_CHANNEL", "MIDI_INPUT_TYPE", "VOLUME", 
  "BYTES", "PERCENTAGE", "ALSA", "JACK", "$accept", "input", "line", 
  "command", "get_instruction", "load_instruction", 
  "set_chan_instruction", "buffer_size_type", "load_instr_args", 
  "load_engine_args", "audio_output_type", "midi_input_type", "volume", 
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
     285,   286,   287,   288,   289,   290,   291,   292
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    38,    39,    39,    39,    40,    40,    40,    41,    41,
      41,    41,    41,    41,    41,    41,    41,    42,    42,    42,
      42,    42,    42,    42,    43,    43,    44,    44,    44,    44,
      44,    44,    45,    45,    46,    47,    48,    48,    49,    50,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      59,    60,    60,    60,    60,    61,    61
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     3,     4,     0,     1,     1,     3,     3,
       3,     5,     5,     5,     5,     5,     1,     1,     1,     5,
       7,     5,     5,     5,     3,     3,     5,     5,     5,     5,
       5,     5,     1,     1,     5,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     1,     2,     2,     1,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     7,     0,     0,     0,     0,     0,     0,     0,     0,
      16,     0,     2,     6,     0,     0,     0,     0,     0,     0,
       0,     0,     1,     0,     0,     8,     0,    17,    18,     0,
       9,     0,     0,    10,     0,     0,     0,     0,     0,     3,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       4,     0,     0,     0,     0,     0,    55,    52,    24,     0,
      49,    51,    25,     0,    47,    41,    11,     0,     0,     0,
       0,     0,     0,    12,    43,    13,    14,    46,    15,     0,
       0,     0,     0,     0,     0,    54,    53,    56,     0,     0,
       0,     0,     0,     0,     0,    19,    32,    33,     0,    21,
      22,    23,    52,     0,    50,    35,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      20,    34,    44,    26,    36,    37,    27,    28,    48,    45,
      29,    38,    30,    39,    40,    31
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,    11,    12,    13,    30,    33,    73,    98,    58,    62,
     126,   132,   135,    66,   103,    75,   123,   130,    76,    63,
     127,    59,    60,    61
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -48
static const yysigned_char yypact[] =
{
      10,   -48,    -4,     3,    25,    40,    56,    60,    64,    70,
     -48,    28,   -48,   -48,    16,   -14,   -12,    57,    59,    61,
      62,    65,   -48,    10,    71,   -48,    73,   -48,   -48,    76,
     -48,    79,    80,   -48,    81,    82,    83,    84,    85,   -48,
      10,    20,    72,     0,    89,    88,    26,    90,     0,    88,
     -48,    91,    92,    93,    94,    95,   -48,   -48,   -48,    96,
      27,   100,   -48,    98,   100,   -48,   -48,    99,   101,   102,
     103,   104,   105,   -48,   -48,   -48,   -48,    27,   -48,    88,
      30,    88,    88,    89,    58,   -48,   100,   -48,    88,    88,
      88,    88,    88,    88,    88,   -48,   -48,   -48,   106,   -48,
     -48,   -48,   107,   108,    27,   -48,   109,   110,   111,   112,
     113,   114,    88,    88,   116,    31,     0,   117,    87,    69,
     -48,   -48,   -48,   -48,   -48,   -48,   -48,   -48,    27,   -48,
     -48,   -48,   -48,   -48,   -48,   -48
};

/* YYPGOTO[NTERM-NUM].  */
static const yysigned_char yypgoto[] =
{
     -48,   -48,   -11,   -48,   -48,   -48,   -48,   -48,   -48,   -48,
     -48,   -48,   -48,   -41,   -48,   -48,   -48,   -48,   -48,    13,
     -48,   -48,   -47,   -44
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -43
static const short yytable[] =
{
      64,    77,    14,    56,    26,    57,    27,    28,    78,    15,
      -5,     1,    39,    29,    31,    32,    86,    -5,    -5,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    22,    50,
      56,    16,    85,    86,    25,    23,    24,   104,    95,    64,
      99,   100,    51,    52,    53,    54,    17,   105,   106,   107,
     108,   109,   110,   111,    67,    68,    69,    70,    71,    72,
      86,    56,    18,   102,    96,    97,    19,   124,   125,   128,
      20,   120,   121,   133,   134,    34,    21,    35,    40,    41,
      36,    37,    42,    38,    86,    43,    44,    45,    46,    47,
      48,    49,    56,    65,    55,    74,   101,    79,    80,    81,
      82,    83,    84,    87,    88,    89,     0,    90,    91,    92,
      93,    94,   112,   -42,   113,   114,   115,   116,   117,   118,
     119,   122,   129,   131
};

static const short yycheck[] =
{
      44,    48,     6,     3,    18,     5,    20,    21,    49,     6,
       0,     1,    23,    27,    26,    27,    60,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,     0,    40,
       3,     6,     5,    77,    18,     7,     8,    84,    79,    83,
      81,    82,    22,    23,    24,    25,     6,    88,    89,    90,
      91,    92,    93,    94,    28,    29,    30,    31,    32,    33,
     104,     3,     6,     5,    34,    35,     6,    36,    37,   116,
       6,   112,   113,     4,     5,    18,     6,    18,     7,     6,
      19,    19,     6,    18,   128,     6,     6,     6,     6,     6,
       6,     6,     3,     5,    22,     5,    83,     6,     6,     6,
       6,     6,     6,     3,     6,     6,    -1,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     5,     5,    36
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     1,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    39,    40,    41,     6,     6,     6,     6,     6,     6,
       6,     6,     0,     7,     8,    18,    18,    20,    21,    27,
      42,    26,    27,    43,    18,    18,    19,    19,    18,    40,
       7,     6,     6,     6,     6,     6,     6,     6,     6,     6,
      40,    22,    23,    24,    25,    22,     3,     5,    46,    59,
      60,    61,    47,    57,    61,     5,    51,    28,    29,    30,
      31,    32,    33,    44,     5,    53,    56,    60,    51,     6,
       6,     6,     6,     6,     6,     5,    61,     3,     6,     6,
       6,     6,     6,     6,     6,    51,    34,    35,    45,    51,
      51,    57,     5,    52,    60,    51,    51,    51,    51,    51,
      51,    51,     6,     6,     6,     6,     6,     6,     6,     6,
      51,    51,     5,    54,    36,    37,    48,    58,    60,     5,
      55,    36,    49,     4,     5,    50
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
        case 6:
#line 83 "lscp.y"
    { LSCPSERVER->AnswerClient(yyvsp[0].String); }
    break;

  case 7:
#line 84 "lscp.y"
    { LSCPSERVER->AnswerClient("Err:0:Unknown command.\r\n"); RESTART; return LSCP_SYNTAX_ERROR; }
    break;

  case 8:
#line 87 "lscp.y"
    { yyval.String = LSCPSERVER->AddChannel();                  }
    break;

  case 9:
#line 88 "lscp.y"
    { yyval.String = yyvsp[0].String;                                        }
    break;

  case 10:
#line 89 "lscp.y"
    { yyval.String = yyvsp[0].String;                                        }
    break;

  case 11:
#line 90 "lscp.y"
    { yyval.String = LSCPSERVER->RemoveChannel(yyvsp[0].Number);             }
    break;

  case 12:
#line 91 "lscp.y"
    { yyval.String = yyvsp[0].String;                                        }
    break;

  case 13:
#line 92 "lscp.y"
    { yyval.String = LSCPSERVER->SubscribeNotification(yyvsp[0].Number);     }
    break;

  case 14:
#line 93 "lscp.y"
    { yyval.String = LSCPSERVER->UnsubscribeNotification(yyvsp[0].String);   }
    break;

  case 15:
#line 94 "lscp.y"
    { yyval.String = LSCPSERVER->ResetChannel(yyvsp[0].Number);              }
    break;

  case 16:
#line 95 "lscp.y"
    { LSCPSERVER->AnswerClient("Bye!\r\n"); return 0; }
    break;

  case 17:
#line 98 "lscp.y"
    { yyval.String = LSCPSERVER->GetAvailableEngines(); }
    break;

  case 18:
#line 99 "lscp.y"
    { yyval.String = LSCPSERVER->GetChannels();         }
    break;

  case 19:
#line 100 "lscp.y"
    { yyval.String = LSCPSERVER->GetChannelInfo(yyvsp[0].Number);    }
    break;

  case 20:
#line 101 "lscp.y"
    { yyval.String = LSCPSERVER->GetBufferFill(yyvsp[-2].FillResponse, yyvsp[0].Number); }
    break;

  case 21:
#line 102 "lscp.y"
    { yyval.String = LSCPSERVER->GetStreamCount(yyvsp[0].Number);    }
    break;

  case 22:
#line 103 "lscp.y"
    { yyval.String = LSCPSERVER->GetVoiceCount(yyvsp[0].Number);     }
    break;

  case 23:
#line 104 "lscp.y"
    { yyval.String = LSCPSERVER->GetEngineInfo(yyvsp[0].String);     }
    break;

  case 24:
#line 107 "lscp.y"
    { yyval.String = yyvsp[0].String; }
    break;

  case 25:
#line 108 "lscp.y"
    { yyval.String = yyvsp[0].String; }
    break;

  case 26:
#line 111 "lscp.y"
    { yyval.String = LSCPSERVER->SetAudioOutputChannel(yyvsp[0].Number, yyvsp[-2].Number); }
    break;

  case 27:
#line 112 "lscp.y"
    { yyval.String = LSCPSERVER->SetAudioOutputType(yyvsp[0].AudioOutput, yyvsp[-2].Number);    }
    break;

  case 28:
#line 113 "lscp.y"
    { yyval.String = LSCPSERVER->SetMIDIInputPort(yyvsp[0].String, yyvsp[-2].Number);      }
    break;

  case 29:
#line 114 "lscp.y"
    { yyval.String = LSCPSERVER->SetMIDIInputChannel(yyvsp[0].Number, yyvsp[-2].Number);   }
    break;

  case 30:
#line 115 "lscp.y"
    { yyval.String = LSCPSERVER->SetMIDIInputType(yyvsp[0].MidiInput, yyvsp[-2].Number);      }
    break;

  case 31:
#line 116 "lscp.y"
    { yyval.String = LSCPSERVER->SetVolume(yyvsp[0].Dotnum, yyvsp[-2].Number);             }
    break;

  case 32:
#line 119 "lscp.y"
    { yyval.FillResponse = fill_response_bytes;      }
    break;

  case 33:
#line 120 "lscp.y"
    { yyval.FillResponse = fill_response_percentage; }
    break;

  case 34:
#line 123 "lscp.y"
    { yyval.String = LSCPSERVER->LoadInstrument(yyvsp[-4].String, yyvsp[-2].Number, yyvsp[0].Number); }
    break;

  case 35:
#line 126 "lscp.y"
    { yyval.String = LSCPSERVER->LoadEngine(yyvsp[-2].String, yyvsp[0].Number); }
    break;

  case 36:
#line 129 "lscp.y"
    { yyval.AudioOutput = AudioOutputDevice::type_alsa; }
    break;

  case 37:
#line 130 "lscp.y"
    { yyval.AudioOutput = AudioOutputDevice::type_jack; }
    break;

  case 38:
#line 133 "lscp.y"
    { yyval.MidiInput = MidiInputDevice::type_alsa; }
    break;

  case 40:
#line 137 "lscp.y"
    { yyval.Dotnum = yyvsp[0].Number; }
    break;

  case 50:
#line 165 "lscp.y"
    { yyval.String = yyvsp[-2].String + ' ' + yyvsp[0].String; }
    break;

  case 51:
#line 168 "lscp.y"
    { yyval.String = yyvsp[0].String;                                             }
    break;

  case 52:
#line 169 "lscp.y"
    { std::stringstream ss; ss << yyvsp[0].Number; yyval.String = ss.str();       }
    break;

  case 53:
#line 170 "lscp.y"
    { yyval.String = yyvsp[-1].String + yyvsp[0].String;                                        }
    break;

  case 54:
#line 171 "lscp.y"
    { std::stringstream ss; ss << yyvsp[-1].String << yyvsp[0].Number; yyval.String = ss.str(); }
    break;

  case 55:
#line 174 "lscp.y"
    { std::string s; s = yyvsp[0].Char; yyval.String = s; }
    break;

  case 56:
#line 175 "lscp.y"
    { yyval.String = yyvsp[-1].String + yyvsp[0].Char;                  }
    break;


    }

/* Line 999 of yacc.c.  */
#line 1379 "y.tab.c"

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


#line 178 "lscp.y"


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


