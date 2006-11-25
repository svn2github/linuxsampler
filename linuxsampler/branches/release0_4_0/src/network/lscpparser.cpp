/* A Bison parser, made by GNU Bison 2.1.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005 Free Software Foundation, Inc.

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
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Bison version.  */
#define YYBISON_VERSION "2.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Using locations.  */
#define YYLSP_NEEDED 0







/* Copy the first part of user declarations.  */
#line 27 "lscp.y"


#include "lscpparser.h"
#include "lscpserver.h"
#include "lscpevent.h"

// to save us typing work in the rules action definitions
#define LSCPSERVER ((yyparse_param_t*) yyparse_param)->pServer

// clears input buffer
void restart(yyparse_param_t* pparam, int& yychar);
#define RESTART restart((yyparse_param_t*) YYPARSE_PARAM, yychar)

// we provide our own version of yyerror() so we don't have to link against the yacc library
void yyerror(const char* s);

static char buf[1024]; // input buffer to feed the parser with new characters
static int bytes = 0;  // current number of characters in the input buffer
static int ptr   = 0;  // current position in the input buffer

// external reference to the function which actually reads from the socket
extern int GetLSCPCommand( void *buf, int max_size);

// custom scanner function which reads from the socket
int yylex(YYSTYPE* yylval) {
    // check if we have to read new characters
    if (ptr >= bytes) {
        bytes = GetLSCPCommand(buf, 1023);
        ptr   = 0;
        if (bytes < 0) {
            bytes = 0;
            return 0;
        }
    }
    return (int) buf[ptr++];
}



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

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 219 of yacc.c.  */
#line 130 "y.tab.c"

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T) && (defined (__STDC__) || defined (__cplusplus))
# include <stddef.h> /* INFRINGES ON USER NAME SPACE */
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if defined (__STDC__) || defined (__cplusplus)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     define YYINCLUDED_STDLIB_H
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2005 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM ((YYSIZE_T) -1)
#  endif
#  ifdef __cplusplus
extern "C" {
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if (! defined (malloc) && ! defined (YYINCLUDED_STDLIB_H) \
	&& (defined (__STDC__) || defined (__cplusplus)))
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if (! defined (free) && ! defined (YYINCLUDED_STDLIB_H) \
	&& (defined (__STDC__) || defined (__cplusplus)))
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifdef __cplusplus
}
#  endif
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short int yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short int) + sizeof (YYSTYPE))			\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined (__GNUC__) && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
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
   typedef short int yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  40
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   4080

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  227
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  99
/* YYNRULES -- Number of rules. */
#define YYNRULES  436
/* YYNRULES -- Number of states. */
#define YYNSTATES  1235

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   257

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     225,     2,     2,   226,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,   224,    71,   223,     3,    72,    73,    74,   222,
      75,    76,    77,     7,     5,     8,     6,    78,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    79,    80,
      81,     4,    82,    83,    84,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    85,    86,    87,    88,    89,     2,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    90,    91,    92,    93,     2,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,     1,     2
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short int yyprhs[] =
{
       0,     0,     3,     6,    10,    11,    13,    15,    17,    19,
      22,    25,    28,    31,    35,    39,    43,    47,    51,    55,
      61,    65,    69,    73,    77,    83,    85,    87,    89,    91,
      93,    95,    97,    99,   101,   103,   105,   107,   109,   111,
     113,   115,   117,   119,   125,   133,   143,   145,   151,   159,
     169,   171,   173,   179,   185,   193,   203,   211,   221,   223,
     229,   237,   243,   249,   255,   259,   261,   263,   271,   281,
     289,   299,   303,   307,   313,   317,   323,   327,   331,   335,
     339,   343,   349,   357,   363,   373,   379,   385,   391,   397,
     403,   409,   415,   419,   425,   427,   429,   431,   433,   435,
     437,   439,   441,   447,   455,   459,   461,   463,   465,   467,
     469,   471,   473,   475,   477,   479,   481,   483,   485,   487,
     491,   493,   495,   497,   499,   501,   503,   505,   508,   512,
     517,   522,   524,   527,   529,   531,   533,   535,   537,   539,
     541,   543,   545,   547,   549,   552,   555,   558,   561,   564,
     567,   570,   573,   576,   578,   580,   582,   584,   586,   588,
     590,   592,   594,   596,   598,   600,   602,   604,   606,   608,
     610,   612,   614,   616,   618,   620,   622,   624,   626,   628,
     630,   632,   634,   636,   638,   640,   642,   644,   646,   648,
     650,   652,   654,   656,   658,   660,   662,   664,   666,   668,
     670,   672,   674,   676,   678,   680,   682,   684,   686,   688,
     690,   692,   694,   696,   698,   700,   702,   704,   706,   708,
     710,   712,   714,   716,   718,   720,   722,   724,   726,   728,
     730,   732,   734,   736,   738,   740,   742,   744,   746,   748,
     750,   752,   754,   756,   758,   760,   762,   764,   766,   768,
     770,   772,   774,   776,   778,   780,   782,   784,   786,   788,
     790,   792,   794,   796,   798,   800,   802,   804,   806,   808,
     810,   812,   814,   816,   818,   820,   822,   824,   826,   828,
     830,   832,   834,   836,   838,   840,   842,   844,   846,   848,
     850,   852,   854,   856,   858,   860,   862,   864,   866,   868,
     870,   872,   874,   876,   878,   880,   882,   884,   886,   888,
     890,   892,   894,   896,   898,   900,   902,   904,   906,   908,
     910,   912,   914,   916,   918,   920,   922,   924,   926,   928,
     930,   932,   934,   936,   938,   940,   942,   944,   946,   948,
     950,   952,   954,   956,   958,   960,   962,   964,   966,   968,
     970,   972,   974,   976,   978,   980,   982,   984,   986,   988,
     990,   992,   994,   996,   998,  1000,  1002,  1004,  1006,  1008,
    1010,  1012,  1014,  1016,  1018,  1021,  1024,  1028,  1032,  1034,
    1036,  1038,  1042,  1046,  1053,  1061,  1066,  1071,  1075,  1085,
    1092,  1096,  1106,  1118,  1125,  1133,  1151,  1182,  1191,  1196,
    1210,  1223,  1235,  1248,  1260,  1278,  1300,  1311,  1318,  1348,
    1369,  1389,  1419,  1439,  1470,  1491,  1509,  1538,  1566,  1592,
    1611,  1629,  1657,  1675,  1691,  1710,  1726,  1737,  1744,  1751,
    1756,  1761,  1767,  1778,  1784,  1798,  1803
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short int yyrhs[] =
{
     228,     0,    -1,   229,   268,    -1,   229,   269,   268,    -1,
      -1,   230,    -1,   231,    -1,     1,    -1,     3,    -1,   230,
       3,    -1,   230,   267,    -1,   230,   263,    -1,   230,   259,
      -1,   270,   267,   283,    -1,   271,   267,   234,    -1,   272,
     267,   236,    -1,   273,   267,   237,    -1,   274,   267,   242,
      -1,   275,   267,   238,    -1,   278,   267,   283,   267,   252,
      -1,   279,   267,   235,    -1,   280,   267,   232,    -1,   281,
     267,   233,    -1,   282,   267,   265,    -1,   322,   267,   283,
     267,   252,    -1,   322,    -1,   325,    -1,   288,    -1,   292,
      -1,   291,    -1,   290,    -1,   289,    -1,   323,    -1,   293,
      -1,   288,    -1,   292,    -1,   291,    -1,   290,    -1,   289,
      -1,   323,    -1,   293,    -1,   284,    -1,   305,    -1,   311,
     267,   287,   267,   259,    -1,   310,   267,   287,   267,   259,
     267,   259,    -1,   310,   267,   287,   267,   259,   267,   259,
     267,   240,    -1,   285,    -1,   301,   267,   287,   267,   259,
      -1,   300,   267,   287,   267,   259,   267,   259,    -1,   300,
     267,   287,   267,   259,   267,   259,   267,   240,    -1,   298,
      -1,   308,    -1,   299,   267,   287,   267,   263,    -1,   309,
     267,   287,   267,   263,    -1,   312,   267,   287,   267,   263,
     267,   263,    -1,   307,   267,   287,   267,   263,   267,   263,
     267,   259,    -1,   303,   267,   287,   267,   263,   267,   263,
      -1,   302,   267,   287,   267,   263,   267,   263,   267,   259,
      -1,   286,    -1,   283,   267,   287,   267,   252,    -1,   283,
     267,   290,   267,   241,   267,   252,    -1,   283,   267,   291,
     267,   252,    -1,   283,   267,   292,   267,   252,    -1,   296,
     267,   287,   267,   254,    -1,   316,   267,   287,    -1,   293,
      -1,   294,    -1,   297,   267,   263,   267,   259,     4,   256,
      -1,   302,   267,   263,   267,   263,   267,   259,     4,   256,
      -1,   306,   267,   263,   267,   259,     4,   256,    -1,   307,
     267,   263,   267,   263,   267,   259,     4,   256,    -1,   283,
     267,   239,    -1,   324,   267,   258,    -1,   299,   267,   259,
     267,   240,    -1,   299,   267,   259,    -1,   309,   267,   259,
     267,   240,    -1,   309,   267,   259,    -1,   299,   267,   263,
      -1,   309,   267,   263,    -1,   295,   267,   243,    -1,   296,
     267,   244,    -1,   299,   267,   252,   267,   245,    -1,   303,
     267,   252,   267,   246,   267,   246,    -1,   304,   267,   252,
     267,   247,    -1,   315,   267,   252,   267,   245,   267,   248,
     267,   249,    -1,   309,   267,   252,   267,   245,    -1,   312,
     267,   252,   267,   248,    -1,   313,   267,   252,   267,   249,
      -1,   314,   267,   252,   267,   250,    -1,   317,   267,   252,
     267,   251,    -1,   318,   267,   252,   267,   258,    -1,   319,
     267,   252,   267,   258,    -1,   259,     4,   256,    -1,   240,
     267,   259,     4,   256,    -1,   320,    -1,   321,    -1,   298,
      -1,   308,    -1,   286,    -1,   284,    -1,   305,    -1,   285,
      -1,   255,   267,   253,   267,   252,    -1,   277,   267,   255,
     267,   253,   267,   252,    -1,   254,   267,   252,    -1,   263,
      -1,   263,    -1,   259,    -1,   263,    -1,   263,    -1,   276,
      -1,   259,    -1,   260,    -1,   263,    -1,   263,    -1,   263,
      -1,   259,    -1,   266,    -1,   257,    -1,   256,     5,   257,
      -1,   259,    -1,   266,    -1,   263,    -1,   260,    -1,   263,
      -1,   259,    -1,   264,    -1,   259,   264,    -1,   261,     6,
     261,    -1,     7,   261,     6,   261,    -1,     8,   261,     6,
     261,    -1,   262,    -1,   261,   262,    -1,     9,    -1,    10,
      -1,    11,    -1,    12,    -1,    13,    -1,    14,    -1,    15,
      -1,    16,    -1,    17,    -1,    18,    -1,   262,    -1,    10,
     261,    -1,    11,   261,    -1,    12,   261,    -1,    13,   261,
      -1,    14,   261,    -1,    15,   261,    -1,    16,   261,    -1,
      17,   261,    -1,    18,   261,    -1,    19,    -1,    20,    -1,
      21,    -1,    22,    -1,    23,    -1,    24,    -1,    25,    -1,
      26,    -1,    27,    -1,    28,    -1,    29,    -1,    30,    -1,
      31,    -1,    32,    -1,    33,    -1,    34,    -1,    35,    -1,
      36,    -1,    37,    -1,    38,    -1,    39,    -1,    40,    -1,
      41,    -1,    42,    -1,    43,    -1,    44,    -1,    45,    -1,
      46,    -1,    47,    -1,    48,    -1,    49,    -1,    50,    -1,
      51,    -1,    52,    -1,    53,    -1,    54,    -1,    55,    -1,
      56,    -1,    57,    -1,    58,    -1,    59,    -1,    60,    -1,
      61,    -1,    62,    -1,    63,    -1,    64,    -1,    65,    -1,
      66,    -1,    67,    -1,    68,    -1,    69,    -1,    70,    -1,
       9,    -1,    10,    -1,    11,    -1,    12,    -1,    13,    -1,
      14,    -1,    15,    -1,    16,    -1,    17,    -1,    18,    -1,
      71,    -1,     3,    -1,    72,    -1,    73,    -1,    74,    -1,
      75,    -1,    76,    -1,    77,    -1,     7,    -1,     8,    -1,
       6,    -1,     5,    -1,    78,    -1,    79,    -1,    80,    -1,
      81,    -1,     4,    -1,    82,    -1,    83,    -1,    84,    -1,
      85,    -1,    86,    -1,    87,    -1,    88,    -1,    89,    -1,
      90,    -1,    91,    -1,    92,    -1,    93,    -1,    94,    -1,
      95,    -1,    96,    -1,    97,    -1,    98,    -1,    99,    -1,
     100,    -1,   101,    -1,   102,    -1,   103,    -1,   104,    -1,
     105,    -1,   106,    -1,   107,    -1,   108,    -1,   109,    -1,
     110,    -1,   111,    -1,   112,    -1,   113,    -1,   114,    -1,
     115,    -1,   116,    -1,   117,    -1,   118,    -1,   119,    -1,
     120,    -1,   121,    -1,   122,    -1,   123,    -1,   124,    -1,
     125,    -1,   126,    -1,   127,    -1,   128,    -1,   129,    -1,
     130,    -1,   131,    -1,   132,    -1,   133,    -1,   134,    -1,
     135,    -1,   136,    -1,   137,    -1,   138,    -1,   139,    -1,
     140,    -1,   141,    -1,   142,    -1,   143,    -1,   144,    -1,
     145,    -1,   146,    -1,   147,    -1,   148,    -1,   149,    -1,
     150,    -1,   151,    -1,   152,    -1,   153,    -1,   154,    -1,
     155,    -1,   156,    -1,   157,    -1,   158,    -1,   159,    -1,
     160,    -1,   161,    -1,   162,    -1,   163,    -1,   164,    -1,
     165,    -1,   166,    -1,   167,    -1,   168,    -1,   169,    -1,
     170,    -1,   171,    -1,   172,    -1,   173,    -1,   174,    -1,
     175,    -1,   176,    -1,   177,    -1,   178,    -1,   179,    -1,
     180,    -1,   181,    -1,   182,    -1,   183,    -1,   184,    -1,
     185,    -1,   186,    -1,   187,    -1,   188,    -1,   189,    -1,
     190,    -1,   191,    -1,   192,    -1,   193,    -1,   194,    -1,
     195,    -1,   196,    -1,   197,    -1,   198,    -1,   199,    -1,
     200,    -1,   201,    -1,   202,    -1,   203,    -1,   204,    -1,
     205,    -1,   206,    -1,   207,    -1,   208,    -1,   209,    -1,
     210,    -1,   211,    -1,   212,    -1,   213,    -1,   214,    -1,
     215,    -1,   216,    -1,   217,    -1,   218,    -1,   219,    -1,
     220,    -1,   221,    -1,   267,    -1,   259,    -1,   265,   267,
      -1,   265,   259,    -1,   222,   265,   222,    -1,   223,   265,
     223,    -1,   224,    -1,   225,    -1,   226,    -1,    19,    22,
      22,    -1,    25,    23,    38,    -1,    21,    36,    23,    19,
      38,    23,    -1,    22,    23,    37,    38,    36,    33,    43,
      -1,    30,    27,    37,    38,    -1,    30,    33,    19,    22,
      -1,    19,    30,    30,    -1,    32,    33,    32,    89,    31,
      33,    22,    19,    30,    -1,    36,    23,    31,    33,    40,
      23,    -1,    37,    23,    38,    -1,    37,    39,    20,    37,
      21,    36,    27,    20,    23,    -1,    39,    32,    37,    39,
      20,    37,    21,    36,    27,    20,    23,    -1,    37,    23,
      30,    23,    21,    38,    -1,    21,    26,    19,    32,    32,
      23,    30,    -1,    19,    40,    19,    27,    30,    19,    20,
      30,    23,    89,    23,    32,    25,    27,    32,    23,    37,
      -1,    19,    40,    19,    27,    30,    19,    20,    30,    23,
      89,    19,    39,    22,    27,    33,    89,    33,    39,    38,
      34,    39,    38,    89,    22,    36,    27,    40,    23,    36,
      37,    -1,    21,    26,    19,    32,    32,    23,    30,    37,
      -1,    27,    32,    24,    33,    -1,    21,    26,    19,    32,
      32,    23,    30,    89,    21,    33,    39,    32,    38,    -1,
      21,    26,    19,    32,    32,    23,    30,    89,    27,    32,
      24,    33,    -1,    20,    39,    24,    24,    23,    36,    89,
      24,    27,    30,    30,    -1,    37,    38,    36,    23,    19,
      31,    89,    21,    33,    39,    32,    38,    -1,    40,    33,
      27,    21,    23,    89,    21,    33,    39,    32,    38,    -1,
      38,    33,    38,    19,    30,    89,    40,    33,    27,    21,
      23,    89,    21,    33,    39,    32,    38,    -1,    38,    33,
      38,    19,    30,    89,    40,    33,    27,    21,    23,    89,
      21,    33,    39,    32,    38,    89,    31,    19,    42,    -1,
      27,    32,    37,    38,    36,    39,    31,    23,    32,    38,
      -1,    23,    32,    25,    27,    32,    23,    -1,    19,    39,
      22,    27,    33,    89,    33,    39,    38,    34,    39,    38,
      89,    22,    23,    40,    27,    21,    23,    89,    34,    19,
      36,    19,    31,    23,    38,    23,    36,    -1,    19,    39,
      22,    27,    33,    89,    33,    39,    38,    34,    39,    38,
      89,    22,    23,    40,    27,    21,    23,    37,    -1,    19,
      39,    22,    27,    33,    89,    33,    39,    38,    34,    39,
      38,    89,    22,    23,    40,    27,    21,    23,    -1,    19,
      39,    22,    27,    33,    89,    33,    39,    38,    34,    39,
      38,    89,    22,    36,    27,    40,    23,    36,    89,    34,
      19,    36,    19,    31,    23,    38,    23,    36,    -1,    19,
      39,    22,    27,    33,    89,    33,    39,    38,    34,    39,
      38,    89,    22,    36,    27,    40,    23,    36,    -1,    19,
      39,    22,    27,    33,    89,    33,    39,    38,    34,    39,
      38,    89,    21,    26,    19,    32,    32,    23,    30,    89,
      34,    19,    36,    19,    31,    23,    38,    23,    36,    -1,
      19,    39,    22,    27,    33,    89,    33,    39,    38,    34,
      39,    38,    89,    21,    26,    19,    32,    32,    23,    30,
      -1,    19,    39,    22,    27,    33,    89,    33,    39,    38,
      34,    39,    38,    89,    38,    43,    34,    23,    -1,    19,
      40,    19,    27,    30,    19,    20,    30,    23,    89,    31,
      27,    22,    27,    89,    27,    32,    34,    39,    38,    89,
      22,    36,    27,    40,    23,    36,    37,    -1,    31,    27,
      22,    27,    89,    27,    32,    34,    39,    38,    89,    22,
      23,    40,    27,    21,    23,    89,    34,    19,    36,    19,
      31,    23,    38,    23,    36,    -1,    31,    27,    22,    27,
      89,    27,    32,    34,    39,    38,    89,    34,    33,    36,
      38,    89,    34,    19,    36,    19,    31,    23,    38,    23,
      36,    -1,    31,    27,    22,    27,    89,    27,    32,    34,
      39,    38,    89,    22,    23,    40,    27,    21,    23,    37,
      -1,    31,    27,    22,    27,    89,    27,    32,    34,    39,
      38,    89,    22,    23,    40,    27,    21,    23,    -1,    31,
      27,    22,    27,    89,    27,    32,    34,    39,    38,    89,
      22,    36,    27,    40,    23,    36,    89,    34,    19,    36,
      19,    31,    23,    38,    23,    36,    -1,    31,    27,    22,
      27,    89,    27,    32,    34,    39,    38,    89,    22,    36,
      27,    40,    23,    36,    -1,    31,    27,    22,    27,    89,
      27,    32,    34,    39,    38,    89,    34,    33,    36,    38,
      -1,    31,    27,    22,    27,    89,    27,    32,    34,    39,
      38,    89,    21,    26,    19,    32,    32,    23,    30,    -1,
      31,    27,    22,    27,    89,    27,    32,    34,    39,    38,
      89,    38,    43,    34,    23,    -1,    31,    27,    22,    27,
      89,    27,    32,    34,    39,    38,    -1,    37,    23,    36,
      40,    23,    36,    -1,    40,    33,    30,    39,    31,    23,
      -1,    31,    39,    38,    23,    -1,    37,    33,    30,    33,
      -1,    20,    43,    38,    23,    37,    -1,    34,    23,    36,
      21,    23,    32,    38,    19,    25,    23,    -1,    36,    23,
      37,    23,    38,    -1,    31,    27,    37,    21,    23,    30,
      30,    19,    32,    23,    33,    39,    37,    -1,    23,    21,
      26,    33,    -1,    35,    39,    27,    38,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,    90,    90,    91,    94,    95,    96,    97,   100,   101,
     102,   103,   104,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   123,   124,   125,
     126,   127,   128,   129,   132,   133,   134,   135,   136,   137,
     138,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   169,   170,   171,
     172,   173,   174,   177,   178,   179,   180,   183,   184,   187,
     188,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   204,   205,   208,   209,   212,   213,   214,   215,
     216,   217,   220,   221,   224,   227,   230,   233,   236,   239,
     240,   243,   246,   247,   250,   253,   256,   259,   262,   263,
     266,   267,   268,   269,   277,   278,   281,   282,   285,   286,
     287,   291,   292,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   318,   318,   318,   318,   318,   318,   318,
     318,   318,   318,   318,   318,   318,   318,   318,   318,   318,
     318,   318,   318,   318,   318,   318,   318,   318,   318,   319,
     319,   319,   319,   319,   319,   319,   319,   319,   319,   319,
     319,   319,   319,   319,   319,   319,   319,   319,   319,   319,
     319,   319,   319,   319,   319,   320,   320,   320,   320,   320,
     320,   320,   320,   320,   320,   321,   321,   321,   321,   321,
     321,   321,   321,   321,   321,   321,   321,   321,   322,   322,
     322,   322,   322,   322,   322,   323,   323,   323,   323,   323,
     324,   324,   324,   324,   325,   325,   325,   326,   326,   326,
     327,   327,   327,   328,   328,   328,   329,   329,   329,   330,
     330,   330,   331,   331,   331,   332,   332,   332,   333,   333,
     333,   334,   334,   334,   335,   335,   335,   336,   336,   336,
     337,   337,   337,   338,   338,   338,   339,   339,   339,   340,
     340,   340,   341,   341,   341,   342,   342,   342,   343,   343,
     343,   344,   344,   344,   345,   345,   345,   346,   346,   346,
     347,   347,   347,   348,   348,   348,   349,   349,   349,   350,
     350,   350,   351,   351,   351,   352,   352,   352,   353,   353,
     353,   354,   354,   354,   355,   355,   355,   356,   356,   356,
     357,   357,   357,   358,   358,   358,   359,   359,   359,   360,
     360,   360,   361,   361,   361,   362,   362,   362,   363,   363,
     363,   364,   364,   364,   365,   365,   365,   366,   366,   366,
     367,   367,   370,   371,   372,   373,   376,   377,   383,   386,
     389,   392,   395,   398,   401,   404,   407,   410,   413,   416,
     419,   422,   425,   428,   431,   434,   437,   440,   443,   446,
     449,   452,   455,   458,   461,   464,   467,   470,   473,   476,
     479,   482,   485,   488,   491,   494,   497,   500,   503,   506,
     509,   512,   515,   518,   521,   524,   527,   530,   533,   536,
     539,   542,   545,   548,   551,   554,   557
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "'#'", "'='", "','", "'.'", "'+'", "'-'",
  "'0'", "'1'", "'2'", "'3'", "'4'", "'5'", "'6'", "'7'", "'8'", "'9'",
  "'A'", "'B'", "'C'", "'D'", "'E'", "'F'", "'G'", "'H'", "'I'", "'J'",
  "'K'", "'L'", "'M'", "'N'", "'O'", "'P'", "'Q'", "'R'", "'S'", "'T'",
  "'U'", "'V'", "'W'", "'X'", "'Y'", "'Z'", "'a'", "'b'", "'c'", "'d'",
  "'e'", "'f'", "'g'", "'h'", "'i'", "'j'", "'k'", "'l'", "'m'", "'n'",
  "'o'", "'p'", "'q'", "'r'", "'s'", "'t'", "'u'", "'v'", "'w'", "'x'",
  "'y'", "'z'", "'!'", "'$'", "'%'", "'&'", "'('", "')'", "'*'", "'/'",
  "':'", "';'", "'<'", "'>'", "'?'", "'@'", "'['", "'\\\\'", "']'", "'^'",
  "'_'", "'{'", "'|'", "'}'", "'~'", "'\\200'", "'\\201'", "'\\202'",
  "'\\203'", "'\\204'", "'\\205'", "'\\206'", "'\\207'", "'\\210'",
  "'\\211'", "'\\212'", "'\\213'", "'\\214'", "'\\215'", "'\\216'",
  "'\\217'", "'\\220'", "'\\221'", "'\\222'", "'\\223'", "'\\224'",
  "'\\225'", "'\\226'", "'\\227'", "'\\230'", "'\\231'", "'\\232'",
  "'\\233'", "'\\234'", "'\\235'", "'\\236'", "'\\237'", "'\\240'",
  "'\\241'", "'\\242'", "'\\243'", "'\\244'", "'\\245'", "'\\246'",
  "'\\247'", "'\\250'", "'\\251'", "'\\252'", "'\\253'", "'\\254'",
  "'\\255'", "'\\256'", "'\\257'", "'\\260'", "'\\261'", "'\\262'",
  "'\\263'", "'\\264'", "'\\265'", "'\\266'", "'\\267'", "'\\270'",
  "'\\271'", "'\\272'", "'\\273'", "'\\274'", "'\\275'", "'\\276'",
  "'\\277'", "'\\300'", "'\\301'", "'\\302'", "'\\303'", "'\\304'",
  "'\\305'", "'\\306'", "'\\307'", "'\\310'", "'\\311'", "'\\312'",
  "'\\313'", "'\\314'", "'\\315'", "'\\316'", "'\\317'", "'\\320'",
  "'\\321'", "'\\322'", "'\\323'", "'\\324'", "'\\325'", "'\\326'",
  "'\\327'", "'\\330'", "'\\331'", "'\\332'", "'\\333'", "'\\334'",
  "'\\335'", "'\\336'", "'\\337'", "'\\340'", "'\\341'", "'\\342'",
  "'\\343'", "'\\344'", "'\\345'", "'\\346'", "'\\347'", "'\\350'",
  "'\\351'", "'\\352'", "'\\353'", "'\\354'", "'\\355'", "'\\356'",
  "'\\357'", "'\\360'", "'\\361'", "'\\362'", "'\\363'", "'\\364'",
  "'\\365'", "'\\366'", "'\\367'", "'\\370'", "'\\371'", "'\\372'",
  "'\\373'", "'\\374'", "'\\375'", "'\\376'", "'\\377'", "'''", "'\"'",
  "' '", "'\\n'", "'\\r'", "$accept", "input", "line", "comment",
  "command", "subscribe_event", "unsubscribe_event", "get_instruction",
  "set_instruction", "create_instruction", "destroy_instruction",
  "load_instruction", "set_chan_instruction", "key_val_list",
  "buffer_size_type", "list_instruction", "load_instr_args",
  "load_engine_args", "device_index", "audio_channel_index",
  "audio_output_type_name", "midi_input_port_index",
  "midi_input_channel_index", "midi_input_type_name", "volume_value",
  "sampler_channel", "instrument_index", "engine_name", "filename",
  "param_val_list", "param_val", "boolean", "string", "dotnum", "digits",
  "digit", "number", "char", "text", "stringval", "SP", "LF", "CR", "ADD",
  "GET", "CREATE", "DESTROY", "LIST", "LOAD", "ALL", "NON_MODAL", "REMOVE",
  "SET", "SUBSCRIBE", "UNSUBSCRIBE", "SELECT", "CHANNEL",
  "AVAILABLE_ENGINES", "AVAILABLE_AUDIO_OUTPUT_DRIVERS", "CHANNELS",
  "INFO", "CHANNEL_COUNT", "CHANNEL_INFO", "BUFFER_FILL", "STREAM_COUNT",
  "VOICE_COUNT", "TOTAL_VOICE_COUNT", "TOTAL_VOICE_COUNT_MAX",
  "INSTRUMENT", "ENGINE", "AUDIO_OUTPUT_DEVICE_PARAMETER",
  "AUDIO_OUTPUT_DEVICES", "AUDIO_OUTPUT_DEVICE",
  "AUDIO_OUTPUT_DRIVER_PARAMETER", "AUDIO_OUTPUT_DRIVER",
  "AUDIO_OUTPUT_CHANNEL_PARAMETER", "AUDIO_OUTPUT_CHANNEL",
  "AUDIO_OUTPUT_TYPE", "AVAILABLE_MIDI_INPUT_DRIVERS",
  "MIDI_INPUT_DEVICE_PARAMETER", "MIDI_INPUT_PORT_PARAMETER",
  "MIDI_INPUT_DEVICES", "MIDI_INPUT_DEVICE", "MIDI_INPUT_DRIVER_PARAMETER",
  "MIDI_INPUT_DRIVER", "MIDI_INPUT_PORT", "MIDI_INPUT_CHANNEL",
  "MIDI_INPUT_TYPE", "MIDI_INPUT", "SERVER", "VOLUME", "MUTE", "SOLO",
  "BYTES", "PERCENTAGE", "RESET", "MISCELLANEOUS", "ECHO", "QUIT", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short int yytoknum[] =
{
       0,   256,   257,    35,    61,    44,    46,    43,    45,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,    33,    36,    37,    38,    40,    41,    42,    47,    58,
      59,    60,    62,    63,    64,    91,    92,    93,    94,    95,
     123,   124,   125,   126,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,    39,    34,    32,    10,    13
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned short int yyr1[] =
{
       0,   227,   228,   228,   229,   229,   229,   229,   230,   230,
     230,   230,   230,   231,   231,   231,   231,   231,   231,   231,
     231,   231,   231,   231,   231,   231,   231,   232,   232,   232,
     232,   232,   232,   232,   233,   233,   233,   233,   233,   233,
     233,   234,   234,   234,   234,   234,   234,   234,   234,   234,
     234,   234,   234,   234,   234,   234,   234,   234,   234,   234,
     234,   234,   234,   234,   234,   234,   234,   235,   235,   235,
     235,   235,   235,   236,   236,   236,   236,   237,   237,   238,
     238,   239,   239,   239,   239,   239,   239,   239,   239,   239,
     239,   239,   240,   240,   241,   241,   242,   242,   242,   242,
     242,   242,   243,   243,   244,   245,   246,   247,   248,   249,
     249,   250,   251,   251,   252,   253,   254,   255,   256,   256,
     257,   257,   257,   257,   258,   258,   259,   259,   260,   260,
     260,   261,   261,   262,   262,   262,   262,   262,   262,   262,
     262,   262,   262,   263,   263,   263,   263,   263,   263,   263,
     263,   263,   263,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   265,   265,   265,   265,   266,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     2,     3,     0,     1,     1,     1,     1,     2,
       2,     2,     2,     3,     3,     3,     3,     3,     3,     5,
       3,     3,     3,     3,     5,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     5,     7,     9,     1,     5,     7,     9,
       1,     1,     5,     5,     7,     9,     7,     9,     1,     5,
       7,     5,     5,     5,     3,     1,     1,     7,     9,     7,
       9,     3,     3,     5,     3,     5,     3,     3,     3,     3,
       3,     5,     7,     5,     9,     5,     5,     5,     5,     5,
       5,     5,     3,     5,     1,     1,     1,     1,     1,     1,
       1,     1,     5,     7,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     2,     3,     4,
       4,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     3,     3,     1,     1,
       1,     3,     3,     6,     7,     4,     4,     3,     9,     6,
       3,     9,    11,     6,     7,    17,    30,     8,     4,    13,
      12,    11,    12,    11,    17,    21,    10,     6,    29,    20,
      19,    29,    19,    30,    20,    17,    28,    27,    25,    18,
      17,    27,    17,    15,    18,    15,    10,     6,     6,     4,
       4,     5,    10,     5,    13,     4,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned short int yydefact[] =
{
       0,     7,     8,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     5,     6,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    25,    26,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,   379,   380,     2,     0,     9,   231,   226,   225,   223,
     224,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   215,   217,   218,   219,   220,   221,   222,
     227,   228,   229,   230,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   352,   353,   354,   355,   356,   357,
     358,   359,   360,   361,   362,   363,   364,   365,   366,   367,
     368,   369,   370,   371,   378,    12,   143,    11,   126,    10,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   381,     0,     0,   382,     0,     0,     0,     0,
       0,     0,   390,     0,     0,     3,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   144,   131,   145,   146,
     147,   148,   149,   150,   151,   152,   216,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   127,     0,    13,
       0,     0,     0,     0,     0,     0,    14,     0,    41,    46,
      58,    65,    66,     0,    50,     0,     0,     0,     0,     0,
      42,     0,    51,     0,     0,     0,     0,     0,     0,     0,
      15,     0,     0,    16,     0,     0,     0,     0,     0,    17,
      99,   101,    98,    96,   100,    97,     0,    18,     0,     0,
       0,     0,     0,     0,    20,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    21,    27,    31,
      30,    29,    28,    33,    32,    22,    34,    38,    37,    36,
      35,    40,    39,   373,    23,   372,     0,     0,     0,   385,
     386,   436,     0,     0,     0,     0,     0,   132,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   375,   374,     0,
       0,     0,     0,   433,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    64,     0,     0,    74,    76,   134,   135,   136,   137,
     138,   139,   140,   141,   142,    77,    78,     0,     0,     0,
       0,     0,     0,     0,    79,     0,   117,     0,    80,     0,
     116,    19,   114,     0,     0,     0,     0,     0,     0,     0,
      71,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    72,   125,   124,     0,
       0,     0,     0,     0,     0,    24,   383,     0,   389,   393,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   435,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   384,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    59,     0,     0,     0,    94,    95,    61,    62,    63,
      52,     0,    47,     0,     0,     0,    53,     0,    43,     0,
       0,     0,    73,     0,    75,     0,     0,     0,     0,     0,
     376,   377,     0,   115,     0,   104,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     407,     0,   427,     0,   398,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   429,
     430,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   391,     0,   394,     0,     0,   394,     0,
       0,     0,     0,    60,    48,     0,    56,     0,    44,    54,
       0,     0,     0,   223,   224,    92,   118,   120,   123,     0,
     131,   122,   121,     0,     0,     0,     0,     0,   102,     0,
       0,     0,     0,     0,     0,    81,   105,     0,   106,    83,
     107,    85,    86,   108,     0,    87,   109,   110,    88,   111,
       0,     0,     0,    89,   112,   113,    90,    91,    67,     0,
      69,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   397,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   428,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   392,     0,
       0,     0,     0,   431,     0,    49,    57,    55,    45,     0,
       0,    93,     0,     0,   119,   128,     0,     0,     0,     0,
     103,     0,     0,     0,     0,    82,   387,     0,    68,    70,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   129,   130,     0,     0,   406,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   388,     0,     0,     0,     0,    84,   401,
       0,     0,     0,     0,     0,   403,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   426,     0,   400,     0,   402,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   399,   434,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   432,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     423,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   395,     0,   420,   422,     0,   404,     0,   420,
       0,     0,     0,     0,     0,     0,     0,     0,   423,   425,
     404,     0,     0,     0,     0,     0,   419,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   410,
     412,     0,     0,     0,     0,     0,   410,     0,     0,     0,
       0,     0,   415,     0,   414,   409,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   424,     0,     0,     0,
       0,     0,     0,   405,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   414,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   418,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   421,     0,   417,     0,     0,     0,   416,     0,     0,
     411,     0,   408,   413,   396
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,    12,    13,    14,    15,   397,   405,   336,   384,   360,
     363,   377,   550,   682,   664,   369,   534,   538,   825,   827,
     829,   832,   835,   838,   843,   541,   692,   539,   535,   805,
     806,   566,   807,   808,   809,   266,   542,   268,   414,   812,
     746,    43,    44,    16,    17,    18,    19,    20,    21,   837,
     537,    22,    23,    24,    25,    26,   329,   338,   339,   340,
     496,   398,   399,   400,   401,   402,   341,   342,   378,   343,
     386,   344,   345,   346,   347,   348,   349,   553,   350,   388,
     351,   352,   353,   354,   355,   356,   556,   557,   558,   357,
     559,   560,   561,   665,   666,    27,   404,   390,    28
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -748
static const short int yypact[] =
{
      56,  -748,  -748,    63,    29,    92,    99,   112,   108,   162,
      37,   146,   222,  -193,  1661,  -748,    25,    25,    25,    25,
      25,    25,    25,    25,    25,    25,    25,    25,  -748,   228,
     230,   214,   216,   215,   236,   232,   109,    26,   237,   219,
    -748,  -748,  -748,  -748,    38,  -748,  -748,  -748,  -748,  -748,
    -748,  -748,   274,   274,   274,   274,   274,   274,   274,   274,
     274,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,
    -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,
    -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,
    -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,
    -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,
    -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,
    -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,
    -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,
    -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,
    -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,
    -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,
    -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,
    -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,
    -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,
    -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,
    -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,
    -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,
    -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,
    -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,
    -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,
    -748,  -748,  -748,  -748,  -748,  2326,  -748,  -748,  -748,  -748,
     241,    82,    69,    69,    90,     8,   241,    87,    59,    59,
    1883,   241,  -748,   245,   227,  -748,   233,   244,   234,   235,
     247,   250,  -748,   238,   239,  -748,  -748,  -748,  -748,  -748,
    -748,  -748,  -748,  -748,  -748,  -748,   274,  -748,   274,   274,
     274,   274,   274,   274,   274,   274,  -748,  -748,  -748,  -748,
    -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,   248,  -748,
      23,   251,   261,   240,   256,   262,  -748,    25,  -748,  -748,
    -748,  -748,  -748,    25,  -748,    25,    25,    25,    25,    25,
    -748,    25,  -748,    25,    25,    25,    25,    25,   255,   253,
    -748,    25,    25,  -748,    25,    25,    43,   271,   289,  -748,
    -748,  -748,  -748,  -748,  -748,  -748,   285,  -748,    25,    25,
      25,   279,   298,   293,  -748,    25,    25,    25,    25,    25,
      25,   282,   296,   301,   286,   290,   292,  -748,  -748,  -748,
    -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,
    -748,  -748,  -748,  2326,  1883,  -748,    25,   291,   294,  -748,
    -748,  -748,   287,   295,   310,   318,   321,  -748,   328,   326,
     330,   333,   331,   335,   319,   320,    67,   332,   332,   332,
     332,   332,   332,   332,   332,   332,   332,   332,   332,   338,
     339,  2326,  2326,   297,   297,   340,   344,   343,   329,    -9,
    2326,   297,   348,   345,   351,    21,   297,   297,   297,   297,
    2545,   356,   353,   346,   349,   352,   354,  2326,  -748,   297,
     359,   355,   361,  -748,   357,   358,   360,   364,   362,   365,
     366,   372,   373,   347,   367,   369,    25,    25,    25,    25,
      25,    25,    25,    25,    25,    25,    25,    25,    25,    25,
      25,  -748,   375,   379,  1883,  1883,   274,   274,   274,   274,
     274,   274,   274,   274,   274,  -748,  -748,   380,   376,   382,
     374,   377,  1883,  1883,  -748,    25,  -748,    25,  -748,    25,
    2326,  -748,  -748,   384,   381,   386,   378,    85,   383,   385,
    -748,    25,    25,    25,    25,    25,    25,    25,    25,    25,
      25,    25,    25,    25,    25,    25,  -748,  2326,  -748,   391,
     387,   370,   397,   402,   401,  -748,  -748,   388,  -748,  -748,
     396,   403,   393,   394,   363,   398,   400,   337,   405,   399,
     409,   297,    64,   297,   297,  2326,   297,  2326,  2326,   297,
     297,   297,   297,  2326,  2326,   297,   404,   368,  2326,  2326,
     408,   406,   371,   407,   410,  1217,  1439,   297,   -59,   297,
     411,  -748,   389,   412,   413,   420,   415,   416,   297,   297,
     297,   297,   297,   297,   297,   297,   297,   297,   297,  2326,
     297,  2326,   297,   424,   417,   425,   431,   421,   436,  -748,
     441,   426,   440,   390,   445,   442,   443,   444,   432,   392,
     434,  -748,   427,   446,    25,  -748,  -748,  -748,  -748,  -748,
    -748,  1883,  2326,    25,    25,    25,  -748,  1883,  2326,    25,
     395,   447,    25,  2764,    25,   428,   449,   448,   437,   429,
    -748,  -748,    25,  -748,    25,  -748,   430,   450,   453,   455,
     460,   467,   462,    25,    25,    25,    25,    25,    25,    25,
      25,    25,    25,    25,  2983,    25,  3202,    25,   466,   482,
     485,   489,   438,   468,   493,   496,   495,   506,   509,   525,
    -748,   524,  -748,   433,  -748,   520,   523,   297,  2326,   297,
     297,   297,  2326,   297,   527,   529,  2326,  2105,   530,   532,
     534,   533,   536,   297,   297,   535,   537,   538,   481,  -748,
    -748,   541,   297,   297,  2326,   297,   297,   229,  2326,   297,
     189,  2545,  2545,  2105,  2326,  2105,  2326,   484,   544,   545,
     487,   539,   556,  -748,   558,  -748,   542,   550,   546,   555,
     551,   567,   571,  -748,  1883,    25,  -748,    25,  1883,  -748,
     554,   560,  3421,   274,   274,   590,  -748,  2326,  -748,   117,
      -1,  -748,  -748,   557,   546,   563,   575,   566,  -748,    25,
     561,   568,   512,   579,   584,  -748,  -748,    25,  -748,  -748,
    2326,  -748,  -748,  -748,   578,  -748,  -748,  -748,  -748,  2326,
      25,   274,   274,  -748,  -748,  -748,  -748,  -748,   590,  3640,
     590,  3859,   585,   521,   592,   591,   580,   581,   593,   577,
     594,  -748,   582,   595,   583,   596,  2326,  2326,  2326,  2326,
     586,   588,  2105,   156,   177,  2105,   274,   587,   597,   599,
     414,   297,   600,   598,   601,   603,  -748,   297,   602,   297,
    2105,  2105,   606,   154,   607,   608,   613,   604,  -748,   589,
     540,   609,   621,  -748,   612,    25,  2326,  2326,    25,   611,
     610,   590,   274,   274,  -748,   274,   615,   614,   616,   627,
    -748,   617,   618,   619,   623,  -748,  -748,    25,   590,   590,
     620,   622,   629,   636,   626,   646,   637,   631,   118,   625,
     648,   634,   635,   628,   274,   274,   638,   630,  -748,   643,
     639,   632,   641,   645,   229,   650,   647,   651,   649,   644,
     662,   652,   653,   664,   655,   661,   114,   633,   670,   667,
     685,   671,   686,  -748,   672,   116,   677,   674,  -748,  -748,
     683,   687,   679,   678,   642,  -748,   654,   701,   699,   706,
      18,   697,   711,   709,   656,   712,   657,   713,   658,   715,
     708,   700,   665,   704,  -748,   707,  -748,   729,   155,   735,
     739,   740,   728,   742,   734,   738,   749,   751,   736,   752,
     741,   187,   745,   743,   737,    17,  -748,  -748,   747,   756,
      66,   755,   746,   702,   762,   750,   754,   757,  -748,   772,
     770,   775,   773,   777,   781,   778,   768,   718,   783,   779,
     776,   774,   792,   782,   794,   744,   800,   797,   804,   803,
     748,   795,   788,   809,   796,   813,   816,   798,   818,   748,
      15,   822,   806,   810,   811,   814,   820,   805,   815,   812,
     819,   827,   817,   823,   821,   825,   831,   833,   845,   837,
     843,   848,   846,   835,   842,   841,   861,   847,   854,   866,
     865,   850,  -748,   857,   855,   807,   874,   808,   873,  -748,
     877,   855,   863,   878,   824,   881,   867,   872,  -748,  -748,
    -748,   883,   884,   875,   870,   871,  -748,   880,   876,   886,
     892,   895,   896,   897,   887,   890,   900,   901,   879,   888,
     839,   898,   891,   911,   912,   914,  -748,   888,   906,   849,
     918,   907,  -748,   913,   852,  -748,   908,   905,   860,   910,
     919,   576,   852,   917,   916,   932,  -748,   922,   938,   923,
     940,   941,   944,  -748,   945,   949,   933,   950,   934,   885,
     937,   948,   942,   939,   951,  -748,   952,   957,   959,   958,
     961,   963,   968,   967,   973,   962,   960,   954,   964,   965,
     966,   969,   972,   975,   977,   976,   982,  -748,   983,   985,
     986,   974,   955,   979,   981,   980,   984,   987,   988,   990,
     989,  -748,   996,  -748,   998,   991,   992,  -748,   993,   994,
    -748,   995,  -748,  -748,  -748
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,
    -748,  -748,  -748,  -608,  -748,  -748,  -748,  -748,  -554,   113,
    -748,   121,    68,  -748,  -748,  -477,   269,   439,   418,  -747,
     149,  -555,   350,   263,    14,   -10,   -14,   300,  -314,  -438,
     -11,   997,  -748,  -748,  -748,  -748,  -748,  -748,  -748,  -748,
    -748,  -748,  -748,  -748,  -748,  -748,  -247,   761,   763,   764,
    -211,   760,   765,  -257,  -254,  -252,   -58,  -748,  -748,   767,
    -748,   766,  -255,  -748,  -748,   769,   605,  -748,   771,  -748,
     780,   784,  -253,  -748,  -748,   624,  -748,  -748,  -748,  -748,
    -748,  -748,  -748,  -748,  -748,  -748,   785,  -748,  -748
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -144
static const short int yytable[] =
{
     267,   684,   575,   269,  -143,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   361,   364,   362,
     365,   536,   408,   531,   337,   409,   848,   410,   850,   380,
     385,   332,    41,    42,   416,   376,  1092,  1039,  1048,   995,
     546,  1012,   307,   307,   307,   307,   307,   307,   307,   307,
     307,  1049,   547,  1093,  1013,  1050,   291,     1,   548,     2,
      37,   549,   429,   430,   292,    30,   306,   308,   309,   310,
     311,   312,   313,   314,   315,     3,    38,     4,     5,   391,
     392,     6,   455,   430,   662,    29,     7,   391,   358,  1053,
     393,     8,     9,    10,   495,    11,   394,   395,   663,   396,
     359,   330,  1054,   331,   394,   332,   381,   396,   328,   366,
     382,   367,   624,   333,   661,    31,   667,   668,   383,   334,
     335,   368,    32,   876,   625,   911,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   990,   963,   999,    33,
     289,   964,   695,   928,   929,    34,   290,    35,   991,   965,
    1000,   703,   704,   705,   706,   707,   708,   709,   710,   711,
     712,   713,   912,   532,   533,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   931,  1029,  1030,    39,   497,
     536,   932,   498,   913,   499,    36,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   841,   842,   296,   516,
     517,   518,   519,   520,   521,   522,   523,   524,  1043,  1044,
     551,   831,   554,   532,   533,   840,   846,   847,   615,   616,
     403,   411,    40,  -143,  -143,  -143,   500,   501,   502,   503,
     504,   505,   506,   507,   508,   509,   510,   511,   296,   516,
     517,   518,   519,   520,   521,   522,   523,   524,   834,   264,
     282,   284,   286,   283,   285,   287,   294,   293,   905,   288,
     793,   908,   328,    41,   417,   418,   420,   433,   422,   415,
     423,   419,   421,   424,   428,   425,   818,   431,   426,   434,
     450,    -4,    -4,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   432,   449,   435,   427,   456,   427,   427,
     427,   427,   427,   427,   427,   427,   296,   516,   517,   518,
     519,   520,   521,   522,   523,   524,   457,   458,   462,   463,
     464,   471,   472,   475,   474,   476,   436,   482,   473,   480,
     481,   484,   437,   483,   438,   439,   440,   441,   442,   485,
     443,   486,   444,   445,   446,   447,   448,   487,   488,   489,
     451,   452,   490,   453,   454,   493,   491,   492,   494,   495,
     512,   513,   527,   528,   265,   529,   530,   459,   460,   461,
     543,   544,   570,   545,   465,   466,   467,   468,   469,   470,
     569,   574,   576,   571,   578,   572,   589,   588,   577,   583,
     573,   645,   584,   654,   580,   579,   582,   581,   585,   586,
     587,   590,   606,   478,   920,   479,   607,   610,   611,   612,
     614,   620,   613,   622,   621,   643,   626,   623,   627,   644,
     646,   647,   648,   650,   651,   652,   657,   653,   658,   659,
     655,   649,   656,   660,   698,   699,   919,   680,   686,   525,
     526,   685,   689,   688,   696,   701,   702,   718,   720,   719,
     721,   722,   562,   563,   564,   565,   568,   681,   700,   723,
     687,   724,   725,   726,   728,   729,   730,   734,   732,   736,
     735,   731,   749,   790,   745,   750,   751,   756,   697,   727,
     757,   733,   758,   759,   744,   591,   592,   593,   594,   595,
     596,   597,   598,   599,   600,   601,   602,   603,   604,   605,
     760,   761,   777,   608,   609,   778,   307,   307,   307,   307,
     307,   307,   307,   307,   307,   779,   783,   748,   752,   755,
     780,   415,   415,   784,   617,   785,   618,   781,   619,   787,
     306,   308,   309,   310,   311,   312,   313,   314,   315,   786,
     628,   629,   630,   631,   632,   633,   634,   635,   636,   637,
     638,   639,   640,   641,   642,   788,   789,   782,   791,   792,
     800,   801,   814,   813,   816,   327,   815,   817,   820,   821,
     823,   822,   824,   852,   853,   854,   855,   857,   858,   856,
     860,   859,   670,   861,   863,   673,   674,   675,   676,   862,
     864,   679,   865,   870,   871,   875,   877,   878,   879,   880,
     882,   884,   883,   693,   478,   478,   885,   886,   888,   892,
     893,   894,   895,   896,   897,   899,   898,   900,  1173,   904,
     903,   901,   902,   937,   909,   916,   715,   910,   717,   938,
     413,   918,   926,   930,   923,   924,   917,   922,   921,   933,
     935,   934,   940,   936,   941,   942,   949,   939,   943,   946,
     955,   950,   947,   737,   948,   956,   951,   953,   952,   958,
     738,   957,   739,   740,   741,   959,   742,   960,   743,   961,
     962,   967,   968,   973,   969,   981,   983,   971,   974,   976,
     979,   753,   982,   754,   977,   984,   980,   988,   989,   993,
     985,   986,   762,   763,   764,   765,   766,   767,   768,   769,
     770,   771,   772,   987,   774,   994,   776,   995,   997,   996,
     998,  1001,  1002,   327,   966,  1003,  1006,   970,  1005,   972,
    1004,   975,   992,  1009,  1010,   795,   796,   797,  1011,   799,
    1014,  1007,  1015,   811,  1016,  1018,  1020,   810,  1022,  1024,
     693,  1023,  1026,  1008,  1027,  1017,  1019,  1021,   826,   828,
    1028,   826,   833,   836,  1025,   826,   845,   568,   568,   811,
     810,   811,  1031,   810,   477,   810,  1032,  1033,  1034,  1035,
    1036,  1037,  1038,  1039,  1041,  1047,  1040,   327,  1056,  1046,
    1051,  1042,  1052,   866,   867,  1045,   868,   869,  1055,  1058,
    1059,  1057,  1060,   307,   307,  1062,  1061,  1063,  1064,   427,
    1065,   514,   515,  1066,  1067,  1068,  1069,  1070,   881,  1071,
     540,  1075,  1072,  1074,   327,   327,   887,   873,   874,  1073,
     567,  1077,  1076,  1079,  1080,  1081,  1082,  1084,  1085,   889,
    1086,   307,   307,  1078,  1088,  1089,  1087,  1083,  1090,  1091,
     327,  1094,  1095,  1097,  1096,  1100,  1098,  1099,  1101,  1102,
    1104,  1103,  1108,  1105,  1109,   873,   874,  1106,   811,  1107,
    1110,   811,   810,   427,   427,   810,   307,   327,  1111,  1112,
    1113,  1114,  1115,   828,  1117,   833,   811,   811,  1116,  1118,
     810,   810,   413,   413,  1119,  1120,  1121,  1122,  1123,  1124,
     915,  1125,  1126,  1128,  1130,  1132,  1127,  1129,  1131,  1133,
    1135,  1136,   307,   307,  1137,   427,  1138,  1139,  1141,  1154,
    1142,  1140,  1144,  1134,  1143,  1146,   954,  1145,  1147,  1148,
    1149,  1150,  1151,  1152,  1153,  1155,   944,   945,  1156,  1158,
    1159,  1160,  1157,  1161,   427,   427,  1162,  1164,  1163,  1165,
     836,  1167,  1168,  1166,  1169,   540,  1171,   671,   672,  1170,
    1172,  1174,  1175,   677,   678,  1176,  1177,  1178,   683,   683,
    1181,  1179,  1180,  1185,  1183,   477,   477,  1182,  1184,  1186,
    1187,   327,   327,  1189,  1188,  1192,  1195,   327,   327,  1190,
    1191,  1196,  1193,   327,  1198,  1197,  1199,  1200,  1194,   714,
    1201,   716,  1202,  1203,  1205,  1219,  1204,  1208,  1211,  1213,
     925,  1207,  1206,  1210,  1212,  1214,  1215,  1209,  1216,  1217,
     927,  1225,  1218,  1226,   327,  1220,   327,  1221,  1222,  1228,
    1223,  1229,   978,   819,   914,  1224,  1227,  1230,  1231,  1232,
    1233,     0,  1234,   844,   669,   370,   694,   371,   372,   406,
     373,   295,   379,     0,   407,   374,   387,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   389,   375,     0,
       0,     0,     0,     0,   412,     0,     0,     0,     0,     0,
     552,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   794,   555,
       0,     0,   798,     0,   327,     0,   802,     0,   327,     0,
       0,     0,   327,     0,     0,     0,     0,   327,     0,     0,
       0,     0,     0,     0,   830,     0,     0,     0,   839,     0,
       0,   567,   567,     0,   849,     0,   851,     0,     0,     0,
     327,     0,     0,     0,     0,     0,     0,     0,     0,   327,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   327,
       0,   327,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   327,   327,     0,     0,
       0,     0,     0,     0,     0,     0,   683,   906,   907,   683,
     316,    46,    47,    48,    49,    50,   317,   318,   319,   320,
     321,   322,   323,   324,   325,   326,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   690,
       0,   264,   316,    46,    47,    48,    49,    50,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,     0,   691,   264,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,     0,     0,   264,   316,    46,    47,    48,
      49,    50,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,     0,     0,   264,   316,    46,
      47,    48,   803,   804,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   532,   533,   316,
      46,    47,    48,    49,    50,   317,   318,   319,   320,   321,
     322,   323,   324,   325,   326,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   316,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   316,   747,    47,
      48,    49,    50,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   326,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   316,   773,    47,    48,
      49,    50,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   316,   775,    47,    48,    49,
      50,   317,   318,   319,   320,   321,   322,   323,   324,   325,
     326,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   316,   872,    47,    48,    49,    50,
     317,   318,   319,   320,   321,   322,   323,   324,   325,   326,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   316,   890,    47,    48,    49,    50,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   316,   891,    47,    48,    49,    50,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263
};

static const short int yycheck[] =
{
      14,   609,   479,    14,     5,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,   272,   273,   272,
     273,   459,   279,    32,   271,   279,   773,   279,   775,   276,
     277,    23,   225,   226,   281,    27,    21,    22,    21,    22,
      19,    23,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    34,    31,    38,    36,    38,    30,     1,    37,     3,
      23,    40,    39,    40,    38,    36,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    19,    39,    21,    22,    20,
      21,    25,    39,    40,    20,    22,    30,    20,    19,    23,
      31,    35,    36,    37,    27,    39,    37,    38,    34,    40,
      31,    19,    36,    21,    37,    23,    19,    40,    21,    19,
      23,    21,    27,    31,   591,    23,   593,   594,    31,    37,
      38,    31,    23,     6,    39,   872,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    22,    19,    22,    27,
      31,    23,   619,   890,   891,    33,    37,    39,    34,    31,
      34,   628,   629,   630,   631,   632,   633,   634,   635,   636,
     637,   638,     6,   222,   223,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    21,    21,    22,    32,   436,
     618,    27,   436,     6,   436,    23,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    21,    22,
     465,   765,   465,   222,   223,   769,   771,   772,   532,   533,
     278,   279,     0,   224,   225,   226,   437,   438,   439,   440,
     441,   442,   443,   444,   445,   446,   447,   448,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,   224,
      22,    37,    37,    23,    38,    19,    37,    20,   866,    27,
     737,   869,    21,   225,    19,    38,    22,    27,    33,   280,
      23,    38,    38,    23,    26,    37,   753,    26,    39,    23,
      27,   225,   226,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    32,    39,    33,   306,    26,   308,   309,
     310,   311,   312,   313,   314,   315,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    27,    32,    39,    21,
      27,    39,    26,    33,    38,    33,   337,    40,    27,    38,
      36,    21,   343,    38,   345,   346,   347,   348,   349,    21,
     351,    20,   353,   354,   355,   356,   357,    19,    22,    19,
     361,   362,    19,   364,   365,    36,    25,    22,    38,    27,
      22,    22,    22,    19,    14,    22,    37,   378,   379,   380,
      22,    26,    19,    22,   385,   386,   387,   388,   389,   390,
      24,    27,    23,    37,    23,    36,    19,    40,    33,    27,
      38,    21,    27,    30,    36,    38,    32,    37,    32,    27,
      27,    32,    27,   414,   881,   416,    27,    27,    32,    27,
      33,    27,    38,    27,    33,    24,    33,    39,    33,    32,
      23,    19,    21,    27,    21,    32,    89,    33,    23,    30,
      32,    43,    32,    24,    22,    22,    22,    33,    32,   453,
     454,    33,    32,    36,    33,    30,    30,    23,    23,    32,
      19,    30,   466,   467,   468,   469,   470,    89,    38,    23,
      89,    20,    36,    23,    19,    23,    23,    33,    36,    23,
      43,    27,    23,    40,    27,    27,    39,    27,    89,    89,
      27,    89,    27,    23,    89,   496,   497,   498,   499,   500,
     501,   502,   503,   504,   505,   506,   507,   508,   509,   510,
      33,    39,    36,   514,   515,    23,   516,   517,   518,   519,
     520,   521,   522,   523,   524,    30,    23,    89,    89,    89,
      31,   532,   533,    27,   535,    30,   537,    89,   539,    20,
     516,   517,   518,   519,   520,   521,   522,   523,   524,    33,
     551,   552,   553,   554,   555,   556,   557,   558,   559,   560,
     561,   562,   563,   564,   565,    30,    32,    89,    38,    36,
      33,    32,    30,    33,    31,   265,    32,    31,    33,    32,
      89,    33,    31,    89,    30,    30,    89,    21,    20,    40,
      30,    39,   596,    37,    33,   599,   600,   601,   602,    34,
      23,   605,    21,    39,    34,     5,    39,    34,    23,    33,
      39,    89,    34,   617,   615,   616,    27,    23,    30,    24,
      89,    19,    21,    33,    33,    38,    23,    23,    42,    23,
      37,    39,    27,    34,    38,    38,   640,    39,   642,    89,
     280,    32,    30,    27,    33,    32,    39,    39,    38,    32,
      27,    33,    21,    39,    32,    34,    19,    38,    38,    34,
      30,    34,    38,   664,    38,    33,    38,    34,    39,    23,
     671,    32,   673,   674,   675,    39,   677,    21,   679,    32,
      39,    23,    38,    30,    39,    24,    32,    39,    39,    38,
      30,   692,    33,   694,    39,    23,    39,    32,    27,    19,
      38,    38,   703,   704,   705,   706,   707,   708,   709,   710,
     711,   712,   713,    39,   715,    38,   717,    22,    22,    38,
      38,    34,    38,   413,    89,    32,    38,    89,    39,    89,
      33,    89,    89,    22,    25,   739,   740,   741,    22,   743,
      33,    89,    21,   747,    25,    23,    23,   747,    23,    39,
     754,    33,    38,    89,    37,    89,    89,    89,   762,   763,
      21,   765,   766,   767,    89,   769,   770,   771,   772,   773,
     770,   775,    27,   773,   414,   775,    27,    27,    40,    27,
      36,    33,    23,    22,    22,    38,    40,   477,    32,    36,
      33,    40,    26,   794,   795,    40,   797,   798,    33,    27,
      40,    89,    38,   803,   804,    23,    39,    27,    23,   809,
      27,   451,   452,    26,    23,    27,    38,    89,   819,    26,
     460,    19,    33,    39,   514,   515,   827,   803,   804,    43,
     470,    27,    40,    23,    27,    21,    23,    32,    40,   840,
      21,   841,   842,    89,    21,    19,    40,    89,    40,    21,
     540,    19,    36,    32,    34,    40,    32,    27,    33,    37,
      23,    32,    27,    36,    23,   841,   842,    34,   872,    38,
      27,   875,   872,   873,   874,   875,   876,   567,    23,    32,
      27,    23,    26,   887,    32,   889,   890,   891,    43,    38,
     890,   891,   532,   533,    23,    38,    32,    21,    23,    39,
     876,    34,    37,    19,    21,    32,    89,    89,    21,    21,
      19,    34,   912,   913,    32,   915,    23,    23,    38,    30,
      39,    36,    36,    89,    34,    23,   927,    31,    23,    23,
      23,    34,    32,    23,    23,    37,   912,   913,    89,    38,
      19,    19,    34,    19,   944,   945,    30,    19,    89,    32,
     954,    89,    34,    30,    39,   595,    36,   597,   598,    89,
      31,    34,    36,   603,   604,    23,    34,    19,   608,   609,
      19,    38,    22,    30,    19,   615,   616,    23,    19,    19,
      36,   671,   672,    36,    89,    36,    19,   677,   678,    31,
      38,    22,    31,   683,    23,    27,    23,    19,    36,   639,
      23,   641,    19,    31,    40,    40,    36,    31,    23,    23,
     887,    36,    38,    31,    27,    23,    23,    38,    23,    23,
     889,    23,    38,    23,   714,    36,   716,    36,    38,    23,
      36,    23,   954,   754,   875,    38,    37,    36,    36,    36,
      36,    -1,    37,   770,   595,   274,   618,   274,   274,   279,
     274,    44,   275,    -1,   279,   274,   277,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   277,   274,    -1,
      -1,    -1,    -1,    -1,   279,    -1,    -1,    -1,    -1,    -1,
     465,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   738,   465,
      -1,    -1,   742,    -1,   794,    -1,   746,    -1,   798,    -1,
      -1,    -1,   802,    -1,    -1,    -1,    -1,   807,    -1,    -1,
      -1,    -1,    -1,    -1,   764,    -1,    -1,    -1,   768,    -1,
      -1,   771,   772,    -1,   774,    -1,   776,    -1,    -1,    -1,
     830,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   839,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   849,
      -1,   851,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   906,   907,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   866,   867,   868,   869,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
      -1,   224,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,    -1,   223,   224,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,    -1,    -1,   224,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,    -1,    -1,   224,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned short int yystos[] =
{
       0,     1,     3,    19,    21,    22,    25,    30,    35,    36,
      37,    39,   228,   229,   230,   231,   270,   271,   272,   273,
     274,   275,   278,   279,   280,   281,   282,   322,   325,    22,
      36,    23,    23,    27,    33,    39,    23,    23,    39,    32,
       0,   225,   226,   268,   269,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   224,   259,   262,   263,   264,   267,
     267,   267,   267,   267,   267,   267,   267,   267,   267,   267,
     267,   267,    22,    23,    37,    38,    37,    19,    27,    31,
      37,    30,    38,    20,    37,   268,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,   261,   262,   261,   261,
     261,   261,   261,   261,   261,   261,     3,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,   264,    21,   283,
      19,    21,    23,    31,    37,    38,   234,   283,   284,   285,
     286,   293,   294,   296,   298,   299,   300,   301,   302,   303,
     305,   307,   308,   309,   310,   311,   312,   316,    19,    31,
     236,   299,   309,   237,   299,   309,    19,    21,    31,   242,
     284,   285,   286,   298,   305,   308,    27,   238,   295,   296,
     283,    19,    23,    31,   235,   283,   297,   302,   306,   307,
     324,    20,    21,    31,    37,    38,    40,   232,   288,   289,
     290,   291,   292,   293,   323,   233,   288,   289,   290,   291,
     292,   293,   323,   259,   265,   267,   283,    19,    38,    38,
      22,    38,    33,    23,    23,    37,    39,   262,    26,    39,
      40,    26,    32,    27,    23,    33,   267,   267,   267,   267,
     267,   267,   267,   267,   267,   267,   267,   267,   267,    39,
      27,   267,   267,   267,   267,    39,    26,    27,    32,   267,
     267,   267,    39,    21,    27,   267,   267,   267,   267,   267,
     267,    39,    26,    27,    38,    33,    33,   259,   267,   267,
      38,    36,    40,    38,    21,    21,    20,    19,    22,    19,
      19,    25,    22,    36,    38,    27,   287,   290,   291,   292,
     287,   287,   287,   287,   287,   287,   287,   287,   287,   287,
     287,   287,    22,    22,   259,   259,    10,    11,    12,    13,
      14,    15,    16,    17,    18,   263,   263,    22,    19,    22,
      37,    32,   222,   223,   243,   255,   266,   277,   244,   254,
     259,   252,   263,    22,    26,    22,    19,    31,    37,    40,
     239,   299,   303,   304,   309,   312,   313,   314,   315,   317,
     318,   319,   263,   263,   263,   263,   258,   259,   263,    24,
      19,    37,    36,    38,    27,   252,    23,    33,    23,    38,
      36,    37,    32,    27,    27,    32,    27,    27,    40,    19,
      32,   267,   267,   267,   267,   267,   267,   267,   267,   267,
     267,   267,   267,   267,   267,   267,    27,    27,   267,   267,
      27,    32,    27,    38,    33,   265,   265,   267,   267,   267,
      27,    33,    27,    39,    27,    39,    33,    33,   267,   267,
     267,   267,   267,   267,   267,   267,   267,   267,   267,   267,
     267,   267,   267,    24,    32,    21,    23,    19,    21,    43,
      27,    21,    32,    33,    30,    32,    32,    89,    23,    30,
      24,   252,    20,    34,   241,   320,   321,   252,   252,   254,
     263,   259,   259,   263,   263,   263,   263,   259,   259,   263,
      33,    89,   240,   259,   240,    33,    32,    89,    36,    32,
     222,   223,   253,   263,   255,   252,    33,    89,    22,    22,
      38,    30,    30,   252,   252,   252,   252,   252,   252,   252,
     252,   252,   252,   252,   259,   263,   259,   263,    23,    32,
      23,    19,    30,    23,    20,    36,    23,    89,    19,    23,
      23,    27,    36,    89,    33,    43,    23,   267,   267,   267,
     267,   267,   267,   267,    89,    27,   267,     4,    89,    23,
      27,    39,    89,   267,   267,    89,    27,    27,    27,    23,
      33,    39,   267,   267,   267,   267,   267,   267,   267,   267,
     267,   267,   267,     4,   267,     4,   267,    36,    23,    30,
      31,    89,    89,    23,    27,    30,    33,    20,    30,    32,
      40,    38,    36,   252,   259,   263,   263,   263,   259,   263,
      33,    32,   259,     7,     8,   256,   257,   259,   260,   261,
     262,   263,   266,    33,    30,    32,    31,    31,   252,   253,
      33,    32,    33,    89,    31,   245,   263,   246,   263,   247,
     259,   245,   248,   263,    19,   249,   263,   276,   250,   259,
     245,     7,     8,   251,   260,   263,   258,   258,   256,   259,
     256,   259,    89,    30,    30,    89,    40,    21,    20,    39,
      30,    37,    34,    33,    23,    21,   267,   267,   267,   267,
      39,    34,     4,   261,   261,     5,     6,    39,    34,    23,
      33,   267,    39,    34,    89,    27,    23,   267,    30,   267,
       4,     4,    24,    89,    19,    21,    33,    33,    23,    38,
      23,    39,    27,    37,    23,   240,   259,   259,   240,    38,
      39,   256,     6,     6,   257,   261,    38,    39,    32,    22,
     252,    38,    39,    33,    32,   246,    30,   248,   256,   256,
      27,    21,    27,    32,    33,    27,    39,    34,    89,    38,
      21,    32,    34,    38,   261,   261,    34,    38,    38,    19,
      34,    38,    39,    34,   267,    30,    33,    32,    23,    39,
      21,    32,    39,    19,    23,    31,    89,    23,    38,    39,
      89,    39,    89,    30,    39,    89,    38,    39,   249,    30,
      39,    24,    33,    32,    23,    38,    38,    39,    32,    27,
      22,    34,    89,    19,    38,    22,    38,    22,    38,    22,
      34,    34,    38,    32,    33,    39,    38,    89,    89,    22,
      25,    22,    23,    36,    33,    21,    25,    89,    23,    89,
      23,    89,    23,    33,    39,    89,    38,    37,    21,    21,
      22,    27,    27,    27,    40,    27,    36,    33,    23,    22,
      40,    22,    40,    21,    22,    40,    36,    38,    21,    34,
      38,    33,    26,    23,    36,    33,    32,    89,    27,    40,
      38,    39,    23,    27,    23,    27,    26,    23,    27,    38,
      89,    26,    33,    43,    39,    19,    40,    27,    89,    23,
      27,    21,    23,    89,    32,    40,    21,    40,    21,    19,
      40,    21,    21,    38,    19,    36,    34,    32,    32,    27,
      40,    33,    37,    32,    23,    36,    34,    38,    27,    23,
      27,    23,    32,    27,    23,    26,    43,    32,    38,    23,
      38,    32,    21,    23,    39,    34,    37,    89,    19,    89,
      21,    21,    32,    21,    89,    19,    34,    32,    23,    23,
      36,    38,    39,    34,    36,    31,    23,    23,    23,    23,
      34,    32,    23,    23,    30,    37,    89,    34,    38,    19,
      19,    19,    30,    89,    19,    32,    30,    89,    34,    39,
      89,    36,    31,    42,    34,    36,    23,    34,    19,    38,
      22,    19,    23,    19,    19,    30,    19,    36,    89,    36,
      31,    38,    36,    31,    36,    19,    22,    27,    23,    23,
      19,    23,    19,    31,    36,    40,    38,    36,    31,    38,
      31,    23,    27,    23,    23,    23,    23,    23,    38,    40,
      36,    36,    38,    36,    38,    23,    23,    37,    23,    23,
      36,    36,    36,    36,    37
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


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
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (0)


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (N)								\
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (0)
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
              (Loc).first_line, (Loc).first_column,	\
              (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
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

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr,					\
                  Type, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short int *bottom, short int *top)
#else
static void
yy_stack_print (bottom, top)
    short int *bottom;
    short int *top;
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
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname[yyr1[yyrule]]);
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
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

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
  const char *yys = yystr;

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
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      size_t yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

#endif /* YYERROR_VERBOSE */



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
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);


# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

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
    ;
#endif
#endif
{
  /* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;

  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short int yyssa[YYINITDEPTH];
  short int *yyss = yyssa;
  short int *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



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
	short int *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short int *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
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
/* Read a look-ahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to look-ahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
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

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

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
        case 4:
#line 94 "lscp.y"
    { return LSCP_DONE; }
    break;

  case 5:
#line 95 "lscp.y"
    { return LSCP_DONE; }
    break;

  case 6:
#line 96 "lscp.y"
    { LSCPSERVER->AnswerClient((yyvsp[0].String)); return LSCP_DONE; }
    break;

  case 7:
#line 97 "lscp.y"
    { LSCPSERVER->AnswerClient("ERR:0:Unknown command.\r\n"); RESTART; return LSCP_SYNTAX_ERROR; }
    break;

  case 13:
#line 107 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddChannel();                          }
    break;

  case 14:
#line 108 "lscp.y"
    { (yyval.String) = (yyvsp[0].String);                                                }
    break;

  case 15:
#line 109 "lscp.y"
    { (yyval.String) = (yyvsp[0].String);                                                }
    break;

  case 16:
#line 110 "lscp.y"
    { (yyval.String) = (yyvsp[0].String);                                                }
    break;

  case 17:
#line 111 "lscp.y"
    { (yyval.String) = (yyvsp[0].String);                                                }
    break;

  case 18:
#line 112 "lscp.y"
    { (yyval.String) = (yyvsp[0].String);                                                }
    break;

  case 19:
#line 113 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveChannel((yyvsp[0].Number));                     }
    break;

  case 20:
#line 114 "lscp.y"
    { (yyval.String) = (yyvsp[0].String);                                                }
    break;

  case 21:
#line 115 "lscp.y"
    { (yyval.String) = (yyvsp[0].String);                                                }
    break;

  case 22:
#line 116 "lscp.y"
    { (yyval.String) = (yyvsp[0].String);                                                }
    break;

  case 23:
#line 117 "lscp.y"
    { (yyval.String) = LSCPSERVER->QueryDatabase((yyvsp[0].String));                     }
    break;

  case 24:
#line 118 "lscp.y"
    { (yyval.String) = LSCPSERVER->ResetChannel((yyvsp[0].Number));                      }
    break;

  case 25:
#line 119 "lscp.y"
    { (yyval.String) = LSCPSERVER->ResetSampler();                        }
    break;

  case 26:
#line 120 "lscp.y"
    { LSCPSERVER->AnswerClient("Bye!\r\n"); return LSCP_QUIT; }
    break;

  case 27:
#line 123 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_channel_count);     }
    break;

  case 28:
#line 124 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_voice_count);       }
    break;

  case 29:
#line 125 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_stream_count);      }
    break;

  case 30:
#line 126 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_buffer_fill);       }
    break;

  case 31:
#line 127 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_channel_info);      }
    break;

  case 32:
#line 128 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_misc);              }
    break;

  case 33:
#line 129 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_total_voice_count); }
    break;

  case 34:
#line 132 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_channel_count);     }
    break;

  case 35:
#line 133 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_voice_count);       }
    break;

  case 36:
#line 134 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_stream_count);      }
    break;

  case 37:
#line 135 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_buffer_fill);       }
    break;

  case 38:
#line 136 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_channel_info);      }
    break;

  case 39:
#line 137 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_misc);              }
    break;

  case 40:
#line 138 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_total_voice_count); }
    break;

  case 41:
#line 141 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAvailableEngines();                          }
    break;

  case 42:
#line 142 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAvailableMidiInputDrivers();                 }
    break;

  case 43:
#line 143 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDriverInfo((yyvsp[0].String));                     }
    break;

  case 44:
#line 144 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDriverParameterInfo((yyvsp[-2].String), (yyvsp[0].String));        }
    break;

  case 45:
#line 145 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDriverParameterInfo((yyvsp[-4].String), (yyvsp[-2].String), (yyvsp[0].KeyValList));    }
    break;

  case 46:
#line 146 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAvailableAudioOutputDrivers();               }
    break;

  case 47:
#line 147 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDriverInfo((yyvsp[0].String));                   }
    break;

  case 48:
#line 148 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDriverParameterInfo((yyvsp[-2].String), (yyvsp[0].String));      }
    break;

  case 49:
#line 149 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDriverParameterInfo((yyvsp[-4].String), (yyvsp[-2].String), (yyvsp[0].KeyValList));  }
    break;

  case 50:
#line 150 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDeviceCount();                    }
    break;

  case 51:
#line 151 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDeviceCount();                      }
    break;

  case 52:
#line 152 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDeviceInfo((yyvsp[0].Number));                   }
    break;

  case 53:
#line 153 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDeviceInfo((yyvsp[0].Number));                     }
    break;

  case 54:
#line 154 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputPortInfo((yyvsp[-2].Number), (yyvsp[0].Number));                   }
    break;

  case 55:
#line 155 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputPortParameterInfo((yyvsp[-4].Number), (yyvsp[-2].Number), (yyvsp[0].String));      }
    break;

  case 56:
#line 156 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputChannelInfo((yyvsp[-2].Number), (yyvsp[0].Number));              }
    break;

  case 57:
#line 157 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputChannelParameterInfo((yyvsp[-4].Number), (yyvsp[-2].Number), (yyvsp[0].String)); }
    break;

  case 58:
#line 158 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetChannels();                                  }
    break;

  case 59:
#line 159 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetChannelInfo((yyvsp[0].Number));                             }
    break;

  case 60:
#line 160 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetBufferFill((yyvsp[-2].FillResponse), (yyvsp[0].Number));                          }
    break;

  case 61:
#line 161 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetStreamCount((yyvsp[0].Number));                             }
    break;

  case 62:
#line 162 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetVoiceCount((yyvsp[0].Number));                              }
    break;

  case 63:
#line 163 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetEngineInfo((yyvsp[0].String));                              }
    break;

  case 64:
#line 164 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetServerInfo();                                }
    break;

  case 65:
#line 165 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetTotalVoiceCount();                                }
    break;

  case 66:
#line 166 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetTotalVoiceCountMax();                        }
    break;

  case 67:
#line 169 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputDeviceParameter((yyvsp[-4].Number), (yyvsp[-2].String), (yyvsp[0].String));      }
    break;

  case 68:
#line 170 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputChannelParameter((yyvsp[-6].Number), (yyvsp[-4].Number), (yyvsp[-2].String), (yyvsp[0].String)); }
    break;

  case 69:
#line 171 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMidiInputDeviceParameter((yyvsp[-4].Number), (yyvsp[-2].String), (yyvsp[0].String));        }
    break;

  case 70:
#line 172 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMidiInputPortParameter((yyvsp[-6].Number), (yyvsp[-4].Number), (yyvsp[-2].String), (yyvsp[0].String));      }
    break;

  case 71:
#line 173 "lscp.y"
    { (yyval.String) = (yyvsp[0].String);                                                         }
    break;

  case 72:
#line 174 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetEcho((yyparse_param_t*) yyparse_param, (yyvsp[0].Dotnum));  }
    break;

  case 73:
#line 177 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateAudioOutputDevice((yyvsp[-2].String),(yyvsp[0].KeyValList)); }
    break;

  case 74:
#line 178 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateAudioOutputDevice((yyvsp[0].String));    }
    break;

  case 75:
#line 179 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateMidiInputDevice((yyvsp[-2].String),(yyvsp[0].KeyValList));   }
    break;

  case 76:
#line 180 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateMidiInputDevice((yyvsp[0].String));      }
    break;

  case 77:
#line 183 "lscp.y"
    { (yyval.String) = LSCPSERVER->DestroyAudioOutputDevice((yyvsp[0].Number)); }
    break;

  case 78:
#line 184 "lscp.y"
    { (yyval.String) = LSCPSERVER->DestroyMidiInputDevice((yyvsp[0].Number));   }
    break;

  case 79:
#line 187 "lscp.y"
    { (yyval.String) = (yyvsp[0].String); }
    break;

  case 80:
#line 188 "lscp.y"
    { (yyval.String) = (yyvsp[0].String); }
    break;

  case 81:
#line 191 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputDevice((yyvsp[0].Number), (yyvsp[-2].Number));      }
    break;

  case 82:
#line 192 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputChannel((yyvsp[-2].Number), (yyvsp[0].Number), (yyvsp[-4].Number)); }
    break;

  case 83:
#line 193 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputType((yyvsp[0].String), (yyvsp[-2].Number));        }
    break;

  case 84:
#line 194 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInput((yyvsp[-4].Number), (yyvsp[-2].Number), (yyvsp[0].Number), (yyvsp[-6].Number));      }
    break;

  case 85:
#line 195 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputDevice((yyvsp[0].Number), (yyvsp[-2].Number));        }
    break;

  case 86:
#line 196 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputPort((yyvsp[0].Number), (yyvsp[-2].Number));          }
    break;

  case 87:
#line 197 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputChannel((yyvsp[0].Number), (yyvsp[-2].Number));       }
    break;

  case 88:
#line 198 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputType((yyvsp[0].String), (yyvsp[-2].Number));          }
    break;

  case 89:
#line 199 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetVolume((yyvsp[0].Dotnum), (yyvsp[-2].Number));                 }
    break;

  case 90:
#line 200 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMute((yyvsp[0].Dotnum), (yyvsp[-2].Number));            }
    break;

  case 91:
#line 201 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelSolo((yyvsp[0].Dotnum), (yyvsp[-2].Number));            }
    break;

  case 92:
#line 204 "lscp.y"
    { (yyval.KeyValList)[(yyvsp[-2].String)] = (yyvsp[0].String);          }
    break;

  case 93:
#line 205 "lscp.y"
    { (yyval.KeyValList) = (yyvsp[-4].KeyValList); (yyval.KeyValList)[(yyvsp[-2].String)] = (yyvsp[0].String); }
    break;

  case 94:
#line 208 "lscp.y"
    { (yyval.FillResponse) = fill_response_bytes;      }
    break;

  case 95:
#line 209 "lscp.y"
    { (yyval.FillResponse) = fill_response_percentage; }
    break;

  case 96:
#line 212 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDevices();           }
    break;

  case 97:
#line 213 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDevices();             }
    break;

  case 98:
#line 214 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListChannels();                    }
    break;

  case 99:
#line 215 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableEngines();            }
    break;

  case 100:
#line 216 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableMidiInputDrivers();   }
    break;

  case 101:
#line 217 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableAudioOutputDrivers(); }
    break;

  case 102:
#line 220 "lscp.y"
    { (yyval.String) = LSCPSERVER->LoadInstrument((yyvsp[-4].String), (yyvsp[-2].Number), (yyvsp[0].Number));       }
    break;

  case 103:
#line 221 "lscp.y"
    { (yyval.String) = LSCPSERVER->LoadInstrument((yyvsp[-4].String), (yyvsp[-2].Number), (yyvsp[0].Number), true); }
    break;

  case 104:
#line 224 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetEngineType((yyvsp[-2].String), (yyvsp[0].Number)); }
    break;

  case 110:
#line 240 "lscp.y"
    { (yyval.Number) = 16; }
    break;

  case 113:
#line 247 "lscp.y"
    { (yyval.Dotnum) = (yyvsp[0].Number); }
    break;

  case 119:
#line 263 "lscp.y"
    { (yyval.String) = (yyvsp[-2].String) + "," + (yyvsp[0].String); }
    break;

  case 122:
#line 268 "lscp.y"
    { std::stringstream ss; ss << "\'" << (yyvsp[0].Number) << "\'"; (yyval.String) = ss.str(); }
    break;

  case 123:
#line 269 "lscp.y"
    { std::stringstream ss; ss << "\'" << (yyvsp[0].Dotnum) << "\'"; (yyval.String) = ss.str(); }
    break;

  case 124:
#line 277 "lscp.y"
    { (yyval.Dotnum) = (yyvsp[0].Number); }
    break;

  case 125:
#line 278 "lscp.y"
    { (yyval.Dotnum) = -1; }
    break;

  case 126:
#line 281 "lscp.y"
    { std::string s; s = (yyvsp[0].Char); (yyval.String) = s; }
    break;

  case 127:
#line 282 "lscp.y"
    { (yyval.String) = (yyvsp[-1].String) + (yyvsp[0].Char);                  }
    break;

  case 128:
#line 285 "lscp.y"
    { (yyval.Dotnum) = atof(String((yyvsp[-2].String) + "." + (yyvsp[0].String)).c_str());                         }
    break;

  case 129:
#line 286 "lscp.y"
    { String s = "+"; s += (yyvsp[-2].String); s += "."; s += (yyvsp[0].String); (yyval.Dotnum) = atof(s.c_str()); }
    break;

  case 130:
#line 287 "lscp.y"
    { (yyval.Dotnum) = atof(String("-" + (yyvsp[-2].String) + "." + (yyvsp[0].String)).c_str());                   }
    break;

  case 131:
#line 291 "lscp.y"
    { (yyval.String) = (yyvsp[0].Char);      }
    break;

  case 132:
#line 292 "lscp.y"
    { (yyval.String) = (yyvsp[-1].String) + (yyvsp[0].Char); }
    break;

  case 133:
#line 295 "lscp.y"
    { (yyval.Char) = '0'; }
    break;

  case 134:
#line 296 "lscp.y"
    { (yyval.Char) = '1'; }
    break;

  case 135:
#line 297 "lscp.y"
    { (yyval.Char) = '2'; }
    break;

  case 136:
#line 298 "lscp.y"
    { (yyval.Char) = '3'; }
    break;

  case 137:
#line 299 "lscp.y"
    { (yyval.Char) = '4'; }
    break;

  case 138:
#line 300 "lscp.y"
    { (yyval.Char) = '5'; }
    break;

  case 139:
#line 301 "lscp.y"
    { (yyval.Char) = '6'; }
    break;

  case 140:
#line 302 "lscp.y"
    { (yyval.Char) = '7'; }
    break;

  case 141:
#line 303 "lscp.y"
    { (yyval.Char) = '8'; }
    break;

  case 142:
#line 304 "lscp.y"
    { (yyval.Char) = '9'; }
    break;

  case 143:
#line 307 "lscp.y"
    { (yyval.Number) = atoi(String(1, (yyvsp[0].Char)).c_str());      }
    break;

  case 144:
#line 308 "lscp.y"
    { (yyval.Number) = atoi(String(String("1") + (yyvsp[0].String)).c_str()); }
    break;

  case 145:
#line 309 "lscp.y"
    { (yyval.Number) = atoi(String(String("2") + (yyvsp[0].String)).c_str()); }
    break;

  case 146:
#line 310 "lscp.y"
    { (yyval.Number) = atoi(String(String("3") + (yyvsp[0].String)).c_str()); }
    break;

  case 147:
#line 311 "lscp.y"
    { (yyval.Number) = atoi(String(String("4") + (yyvsp[0].String)).c_str()); }
    break;

  case 148:
#line 312 "lscp.y"
    { (yyval.Number) = atoi(String(String("5") + (yyvsp[0].String)).c_str()); }
    break;

  case 149:
#line 313 "lscp.y"
    { (yyval.Number) = atoi(String(String("6") + (yyvsp[0].String)).c_str()); }
    break;

  case 150:
#line 314 "lscp.y"
    { (yyval.Number) = atoi(String(String("7") + (yyvsp[0].String)).c_str()); }
    break;

  case 151:
#line 315 "lscp.y"
    { (yyval.Number) = atoi(String(String("8") + (yyvsp[0].String)).c_str()); }
    break;

  case 152:
#line 316 "lscp.y"
    { (yyval.Number) = atoi(String(String("9") + (yyvsp[0].String)).c_str()); }
    break;

  case 153:
#line 318 "lscp.y"
    { (yyval.Char) = 'A'; }
    break;

  case 154:
#line 318 "lscp.y"
    { (yyval.Char) = 'B'; }
    break;

  case 155:
#line 318 "lscp.y"
    { (yyval.Char) = 'C'; }
    break;

  case 156:
#line 318 "lscp.y"
    { (yyval.Char) = 'D'; }
    break;

  case 157:
#line 318 "lscp.y"
    { (yyval.Char) = 'E'; }
    break;

  case 158:
#line 318 "lscp.y"
    { (yyval.Char) = 'F'; }
    break;

  case 159:
#line 318 "lscp.y"
    { (yyval.Char) = 'G'; }
    break;

  case 160:
#line 318 "lscp.y"
    { (yyval.Char) = 'H'; }
    break;

  case 161:
#line 318 "lscp.y"
    { (yyval.Char) = 'I'; }
    break;

  case 162:
#line 318 "lscp.y"
    { (yyval.Char) = 'J'; }
    break;

  case 163:
#line 318 "lscp.y"
    { (yyval.Char) = 'K'; }
    break;

  case 164:
#line 318 "lscp.y"
    { (yyval.Char) = 'L'; }
    break;

  case 165:
#line 318 "lscp.y"
    { (yyval.Char) = 'M'; }
    break;

  case 166:
#line 318 "lscp.y"
    { (yyval.Char) = 'N'; }
    break;

  case 167:
#line 318 "lscp.y"
    { (yyval.Char) = 'O'; }
    break;

  case 168:
#line 318 "lscp.y"
    { (yyval.Char) = 'P'; }
    break;

  case 169:
#line 318 "lscp.y"
    { (yyval.Char) = 'Q'; }
    break;

  case 170:
#line 318 "lscp.y"
    { (yyval.Char) = 'R'; }
    break;

  case 171:
#line 318 "lscp.y"
    { (yyval.Char) = 'S'; }
    break;

  case 172:
#line 318 "lscp.y"
    { (yyval.Char) = 'T'; }
    break;

  case 173:
#line 318 "lscp.y"
    { (yyval.Char) = 'U'; }
    break;

  case 174:
#line 318 "lscp.y"
    { (yyval.Char) = 'V'; }
    break;

  case 175:
#line 318 "lscp.y"
    { (yyval.Char) = 'W'; }
    break;

  case 176:
#line 318 "lscp.y"
    { (yyval.Char) = 'X'; }
    break;

  case 177:
#line 318 "lscp.y"
    { (yyval.Char) = 'Y'; }
    break;

  case 178:
#line 318 "lscp.y"
    { (yyval.Char) = 'Z'; }
    break;

  case 179:
#line 319 "lscp.y"
    { (yyval.Char) = 'a'; }
    break;

  case 180:
#line 319 "lscp.y"
    { (yyval.Char) = 'b'; }
    break;

  case 181:
#line 319 "lscp.y"
    { (yyval.Char) = 'c'; }
    break;

  case 182:
#line 319 "lscp.y"
    { (yyval.Char) = 'd'; }
    break;

  case 183:
#line 319 "lscp.y"
    { (yyval.Char) = 'e'; }
    break;

  case 184:
#line 319 "lscp.y"
    { (yyval.Char) = 'f'; }
    break;

  case 185:
#line 319 "lscp.y"
    { (yyval.Char) = 'g'; }
    break;

  case 186:
#line 319 "lscp.y"
    { (yyval.Char) = 'h'; }
    break;

  case 187:
#line 319 "lscp.y"
    { (yyval.Char) = 'i'; }
    break;

  case 188:
#line 319 "lscp.y"
    { (yyval.Char) = 'j'; }
    break;

  case 189:
#line 319 "lscp.y"
    { (yyval.Char) = 'k'; }
    break;

  case 190:
#line 319 "lscp.y"
    { (yyval.Char) = 'l'; }
    break;

  case 191:
#line 319 "lscp.y"
    { (yyval.Char) = 'm'; }
    break;

  case 192:
#line 319 "lscp.y"
    { (yyval.Char) = 'n'; }
    break;

  case 193:
#line 319 "lscp.y"
    { (yyval.Char) = 'o'; }
    break;

  case 194:
#line 319 "lscp.y"
    { (yyval.Char) = 'p'; }
    break;

  case 195:
#line 319 "lscp.y"
    { (yyval.Char) = 'q'; }
    break;

  case 196:
#line 319 "lscp.y"
    { (yyval.Char) = 'r'; }
    break;

  case 197:
#line 319 "lscp.y"
    { (yyval.Char) = 's'; }
    break;

  case 198:
#line 319 "lscp.y"
    { (yyval.Char) = 't'; }
    break;

  case 199:
#line 319 "lscp.y"
    { (yyval.Char) = 'u'; }
    break;

  case 200:
#line 319 "lscp.y"
    { (yyval.Char) = 'v'; }
    break;

  case 201:
#line 319 "lscp.y"
    { (yyval.Char) = 'w'; }
    break;

  case 202:
#line 319 "lscp.y"
    { (yyval.Char) = 'x'; }
    break;

  case 203:
#line 319 "lscp.y"
    { (yyval.Char) = 'y'; }
    break;

  case 204:
#line 319 "lscp.y"
    { (yyval.Char) = 'z'; }
    break;

  case 205:
#line 320 "lscp.y"
    { (yyval.Char) = '0'; }
    break;

  case 206:
#line 320 "lscp.y"
    { (yyval.Char) = '1'; }
    break;

  case 207:
#line 320 "lscp.y"
    { (yyval.Char) = '2'; }
    break;

  case 208:
#line 320 "lscp.y"
    { (yyval.Char) = '3'; }
    break;

  case 209:
#line 320 "lscp.y"
    { (yyval.Char) = '4'; }
    break;

  case 210:
#line 320 "lscp.y"
    { (yyval.Char) = '5'; }
    break;

  case 211:
#line 320 "lscp.y"
    { (yyval.Char) = '6'; }
    break;

  case 212:
#line 320 "lscp.y"
    { (yyval.Char) = '7'; }
    break;

  case 213:
#line 320 "lscp.y"
    { (yyval.Char) = '8'; }
    break;

  case 214:
#line 320 "lscp.y"
    { (yyval.Char) = '9'; }
    break;

  case 215:
#line 321 "lscp.y"
    { (yyval.Char) = '!'; }
    break;

  case 216:
#line 321 "lscp.y"
    { (yyval.Char) = '#'; }
    break;

  case 217:
#line 321 "lscp.y"
    { (yyval.Char) = '$'; }
    break;

  case 218:
#line 321 "lscp.y"
    { (yyval.Char) = '%'; }
    break;

  case 219:
#line 321 "lscp.y"
    { (yyval.Char) = '&'; }
    break;

  case 220:
#line 321 "lscp.y"
    { (yyval.Char) = '('; }
    break;

  case 221:
#line 321 "lscp.y"
    { (yyval.Char) = ')'; }
    break;

  case 222:
#line 321 "lscp.y"
    { (yyval.Char) = '*'; }
    break;

  case 223:
#line 321 "lscp.y"
    { (yyval.Char) = '+'; }
    break;

  case 224:
#line 321 "lscp.y"
    { (yyval.Char) = '-'; }
    break;

  case 225:
#line 321 "lscp.y"
    { (yyval.Char) = '.'; }
    break;

  case 226:
#line 321 "lscp.y"
    { (yyval.Char) = ','; }
    break;

  case 227:
#line 321 "lscp.y"
    { (yyval.Char) = '/'; }
    break;

  case 228:
#line 322 "lscp.y"
    { (yyval.Char) = ':'; }
    break;

  case 229:
#line 322 "lscp.y"
    { (yyval.Char) = ';'; }
    break;

  case 230:
#line 322 "lscp.y"
    { (yyval.Char) = '<'; }
    break;

  case 231:
#line 322 "lscp.y"
    { (yyval.Char) = '='; }
    break;

  case 232:
#line 322 "lscp.y"
    { (yyval.Char) = '>'; }
    break;

  case 233:
#line 322 "lscp.y"
    { (yyval.Char) = '?'; }
    break;

  case 234:
#line 322 "lscp.y"
    { (yyval.Char) = '@'; }
    break;

  case 235:
#line 323 "lscp.y"
    { (yyval.Char) = '['; }
    break;

  case 236:
#line 323 "lscp.y"
    { (yyval.Char) = '\\'; }
    break;

  case 237:
#line 323 "lscp.y"
    { (yyval.Char) = ']'; }
    break;

  case 238:
#line 323 "lscp.y"
    { (yyval.Char) = '^'; }
    break;

  case 239:
#line 323 "lscp.y"
    { (yyval.Char) = '_'; }
    break;

  case 240:
#line 324 "lscp.y"
    { (yyval.Char) = '{'; }
    break;

  case 241:
#line 324 "lscp.y"
    { (yyval.Char) = '|'; }
    break;

  case 242:
#line 324 "lscp.y"
    { (yyval.Char) = '}'; }
    break;

  case 243:
#line 324 "lscp.y"
    { (yyval.Char) = '~'; }
    break;

  case 244:
#line 325 "lscp.y"
    { (yyval.Char) = '\200'; }
    break;

  case 245:
#line 325 "lscp.y"
    { (yyval.Char) = '\201'; }
    break;

  case 246:
#line 325 "lscp.y"
    { (yyval.Char) = '\202'; }
    break;

  case 247:
#line 326 "lscp.y"
    { (yyval.Char) = '\203'; }
    break;

  case 248:
#line 326 "lscp.y"
    { (yyval.Char) = '\204'; }
    break;

  case 249:
#line 326 "lscp.y"
    { (yyval.Char) = '\205'; }
    break;

  case 250:
#line 327 "lscp.y"
    { (yyval.Char) = '\206'; }
    break;

  case 251:
#line 327 "lscp.y"
    { (yyval.Char) = '\207'; }
    break;

  case 252:
#line 327 "lscp.y"
    { (yyval.Char) = '\210'; }
    break;

  case 253:
#line 328 "lscp.y"
    { (yyval.Char) = '\211'; }
    break;

  case 254:
#line 328 "lscp.y"
    { (yyval.Char) = '\212'; }
    break;

  case 255:
#line 328 "lscp.y"
    { (yyval.Char) = '\213'; }
    break;

  case 256:
#line 329 "lscp.y"
    { (yyval.Char) = '\214'; }
    break;

  case 257:
#line 329 "lscp.y"
    { (yyval.Char) = '\215'; }
    break;

  case 258:
#line 329 "lscp.y"
    { (yyval.Char) = '\216'; }
    break;

  case 259:
#line 330 "lscp.y"
    { (yyval.Char) = '\217'; }
    break;

  case 260:
#line 330 "lscp.y"
    { (yyval.Char) = '\220'; }
    break;

  case 261:
#line 330 "lscp.y"
    { (yyval.Char) = '\221'; }
    break;

  case 262:
#line 331 "lscp.y"
    { (yyval.Char) = '\222'; }
    break;

  case 263:
#line 331 "lscp.y"
    { (yyval.Char) = '\223'; }
    break;

  case 264:
#line 331 "lscp.y"
    { (yyval.Char) = '\224'; }
    break;

  case 265:
#line 332 "lscp.y"
    { (yyval.Char) = '\225'; }
    break;

  case 266:
#line 332 "lscp.y"
    { (yyval.Char) = '\226'; }
    break;

  case 267:
#line 332 "lscp.y"
    { (yyval.Char) = '\227'; }
    break;

  case 268:
#line 333 "lscp.y"
    { (yyval.Char) = '\230'; }
    break;

  case 269:
#line 333 "lscp.y"
    { (yyval.Char) = '\231'; }
    break;

  case 270:
#line 333 "lscp.y"
    { (yyval.Char) = '\232'; }
    break;

  case 271:
#line 334 "lscp.y"
    { (yyval.Char) = '\233'; }
    break;

  case 272:
#line 334 "lscp.y"
    { (yyval.Char) = '\234'; }
    break;

  case 273:
#line 334 "lscp.y"
    { (yyval.Char) = '\235'; }
    break;

  case 274:
#line 335 "lscp.y"
    { (yyval.Char) = '\236'; }
    break;

  case 275:
#line 335 "lscp.y"
    { (yyval.Char) = '\237'; }
    break;

  case 276:
#line 335 "lscp.y"
    { (yyval.Char) = '\240'; }
    break;

  case 277:
#line 336 "lscp.y"
    { (yyval.Char) = '\241'; }
    break;

  case 278:
#line 336 "lscp.y"
    { (yyval.Char) = '\242'; }
    break;

  case 279:
#line 336 "lscp.y"
    { (yyval.Char) = '\243'; }
    break;

  case 280:
#line 337 "lscp.y"
    { (yyval.Char) = '\244'; }
    break;

  case 281:
#line 337 "lscp.y"
    { (yyval.Char) = '\245'; }
    break;

  case 282:
#line 337 "lscp.y"
    { (yyval.Char) = '\246'; }
    break;

  case 283:
#line 338 "lscp.y"
    { (yyval.Char) = '\247'; }
    break;

  case 284:
#line 338 "lscp.y"
    { (yyval.Char) = '\250'; }
    break;

  case 285:
#line 338 "lscp.y"
    { (yyval.Char) = '\251'; }
    break;

  case 286:
#line 339 "lscp.y"
    { (yyval.Char) = '\252'; }
    break;

  case 287:
#line 339 "lscp.y"
    { (yyval.Char) = '\253'; }
    break;

  case 288:
#line 339 "lscp.y"
    { (yyval.Char) = '\254'; }
    break;

  case 289:
#line 340 "lscp.y"
    { (yyval.Char) = '\255'; }
    break;

  case 290:
#line 340 "lscp.y"
    { (yyval.Char) = '\256'; }
    break;

  case 291:
#line 340 "lscp.y"
    { (yyval.Char) = '\257'; }
    break;

  case 292:
#line 341 "lscp.y"
    { (yyval.Char) = '\260'; }
    break;

  case 293:
#line 341 "lscp.y"
    { (yyval.Char) = '\261'; }
    break;

  case 294:
#line 341 "lscp.y"
    { (yyval.Char) = '\262'; }
    break;

  case 295:
#line 342 "lscp.y"
    { (yyval.Char) = '\263'; }
    break;

  case 296:
#line 342 "lscp.y"
    { (yyval.Char) = '\264'; }
    break;

  case 297:
#line 342 "lscp.y"
    { (yyval.Char) = '\265'; }
    break;

  case 298:
#line 343 "lscp.y"
    { (yyval.Char) = '\266'; }
    break;

  case 299:
#line 343 "lscp.y"
    { (yyval.Char) = '\267'; }
    break;

  case 300:
#line 343 "lscp.y"
    { (yyval.Char) = '\270'; }
    break;

  case 301:
#line 344 "lscp.y"
    { (yyval.Char) = '\271'; }
    break;

  case 302:
#line 344 "lscp.y"
    { (yyval.Char) = '\272'; }
    break;

  case 303:
#line 344 "lscp.y"
    { (yyval.Char) = '\273'; }
    break;

  case 304:
#line 345 "lscp.y"
    { (yyval.Char) = '\274'; }
    break;

  case 305:
#line 345 "lscp.y"
    { (yyval.Char) = '\275'; }
    break;

  case 306:
#line 345 "lscp.y"
    { (yyval.Char) = '\276'; }
    break;

  case 307:
#line 346 "lscp.y"
    { (yyval.Char) = '\277'; }
    break;

  case 308:
#line 346 "lscp.y"
    { (yyval.Char) = '\300'; }
    break;

  case 309:
#line 346 "lscp.y"
    { (yyval.Char) = '\301'; }
    break;

  case 310:
#line 347 "lscp.y"
    { (yyval.Char) = '\302'; }
    break;

  case 311:
#line 347 "lscp.y"
    { (yyval.Char) = '\303'; }
    break;

  case 312:
#line 347 "lscp.y"
    { (yyval.Char) = '\304'; }
    break;

  case 313:
#line 348 "lscp.y"
    { (yyval.Char) = '\305'; }
    break;

  case 314:
#line 348 "lscp.y"
    { (yyval.Char) = '\306'; }
    break;

  case 315:
#line 348 "lscp.y"
    { (yyval.Char) = '\307'; }
    break;

  case 316:
#line 349 "lscp.y"
    { (yyval.Char) = '\310'; }
    break;

  case 317:
#line 349 "lscp.y"
    { (yyval.Char) = '\311'; }
    break;

  case 318:
#line 349 "lscp.y"
    { (yyval.Char) = '\312'; }
    break;

  case 319:
#line 350 "lscp.y"
    { (yyval.Char) = '\313'; }
    break;

  case 320:
#line 350 "lscp.y"
    { (yyval.Char) = '\314'; }
    break;

  case 321:
#line 350 "lscp.y"
    { (yyval.Char) = '\315'; }
    break;

  case 322:
#line 351 "lscp.y"
    { (yyval.Char) = '\316'; }
    break;

  case 323:
#line 351 "lscp.y"
    { (yyval.Char) = '\317'; }
    break;

  case 324:
#line 351 "lscp.y"
    { (yyval.Char) = '\320'; }
    break;

  case 325:
#line 352 "lscp.y"
    { (yyval.Char) = '\321'; }
    break;

  case 326:
#line 352 "lscp.y"
    { (yyval.Char) = '\322'; }
    break;

  case 327:
#line 352 "lscp.y"
    { (yyval.Char) = '\323'; }
    break;

  case 328:
#line 353 "lscp.y"
    { (yyval.Char) = '\324'; }
    break;

  case 329:
#line 353 "lscp.y"
    { (yyval.Char) = '\325'; }
    break;

  case 330:
#line 353 "lscp.y"
    { (yyval.Char) = '\326'; }
    break;

  case 331:
#line 354 "lscp.y"
    { (yyval.Char) = '\327'; }
    break;

  case 332:
#line 354 "lscp.y"
    { (yyval.Char) = '\330'; }
    break;

  case 333:
#line 354 "lscp.y"
    { (yyval.Char) = '\331'; }
    break;

  case 334:
#line 355 "lscp.y"
    { (yyval.Char) = '\332'; }
    break;

  case 335:
#line 355 "lscp.y"
    { (yyval.Char) = '\333'; }
    break;

  case 336:
#line 355 "lscp.y"
    { (yyval.Char) = '\334'; }
    break;

  case 337:
#line 356 "lscp.y"
    { (yyval.Char) = '\335'; }
    break;

  case 338:
#line 356 "lscp.y"
    { (yyval.Char) = '\336'; }
    break;

  case 339:
#line 356 "lscp.y"
    { (yyval.Char) = '\337'; }
    break;

  case 340:
#line 357 "lscp.y"
    { (yyval.Char) = '\340'; }
    break;

  case 341:
#line 357 "lscp.y"
    { (yyval.Char) = '\341'; }
    break;

  case 342:
#line 357 "lscp.y"
    { (yyval.Char) = '\342'; }
    break;

  case 343:
#line 358 "lscp.y"
    { (yyval.Char) = '\343'; }
    break;

  case 344:
#line 358 "lscp.y"
    { (yyval.Char) = '\344'; }
    break;

  case 345:
#line 358 "lscp.y"
    { (yyval.Char) = '\345'; }
    break;

  case 346:
#line 359 "lscp.y"
    { (yyval.Char) = '\346'; }
    break;

  case 347:
#line 359 "lscp.y"
    { (yyval.Char) = '\347'; }
    break;

  case 348:
#line 359 "lscp.y"
    { (yyval.Char) = '\350'; }
    break;

  case 349:
#line 360 "lscp.y"
    { (yyval.Char) = '\351'; }
    break;

  case 350:
#line 360 "lscp.y"
    { (yyval.Char) = '\352'; }
    break;

  case 351:
#line 360 "lscp.y"
    { (yyval.Char) = '\353'; }
    break;

  case 352:
#line 361 "lscp.y"
    { (yyval.Char) = '\354'; }
    break;

  case 353:
#line 361 "lscp.y"
    { (yyval.Char) = '\355'; }
    break;

  case 354:
#line 361 "lscp.y"
    { (yyval.Char) = '\356'; }
    break;

  case 355:
#line 362 "lscp.y"
    { (yyval.Char) = '\357'; }
    break;

  case 356:
#line 362 "lscp.y"
    { (yyval.Char) = '\360'; }
    break;

  case 357:
#line 362 "lscp.y"
    { (yyval.Char) = '\361'; }
    break;

  case 358:
#line 363 "lscp.y"
    { (yyval.Char) = '\362'; }
    break;

  case 359:
#line 363 "lscp.y"
    { (yyval.Char) = '\363'; }
    break;

  case 360:
#line 363 "lscp.y"
    { (yyval.Char) = '\364'; }
    break;

  case 361:
#line 364 "lscp.y"
    { (yyval.Char) = '\365'; }
    break;

  case 362:
#line 364 "lscp.y"
    { (yyval.Char) = '\366'; }
    break;

  case 363:
#line 364 "lscp.y"
    { (yyval.Char) = '\367'; }
    break;

  case 364:
#line 365 "lscp.y"
    { (yyval.Char) = '\370'; }
    break;

  case 365:
#line 365 "lscp.y"
    { (yyval.Char) = '\371'; }
    break;

  case 366:
#line 365 "lscp.y"
    { (yyval.Char) = '\372'; }
    break;

  case 367:
#line 366 "lscp.y"
    { (yyval.Char) = '\373'; }
    break;

  case 368:
#line 366 "lscp.y"
    { (yyval.Char) = '\374'; }
    break;

  case 369:
#line 366 "lscp.y"
    { (yyval.Char) = '\375'; }
    break;

  case 370:
#line 367 "lscp.y"
    { (yyval.Char) = '\376'; }
    break;

  case 371:
#line 367 "lscp.y"
    { (yyval.Char) = '\377'; }
    break;

  case 372:
#line 370 "lscp.y"
    { (yyval.String) = " ";      }
    break;

  case 374:
#line 372 "lscp.y"
    { (yyval.String) = (yyvsp[-1].String) + " "; }
    break;

  case 375:
#line 373 "lscp.y"
    { (yyval.String) = (yyvsp[-1].String) + (yyvsp[0].String);  }
    break;

  case 376:
#line 376 "lscp.y"
    { (yyval.String) = (yyvsp[-1].String); }
    break;

  case 377:
#line 377 "lscp.y"
    { (yyval.String) = (yyvsp[-1].String); }
    break;


      default: break;
    }

/* Line 1126 of yacc.c.  */
#line 4505 "y.tab.c"

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
	  int yytype = YYTRANSLATE (yychar);
	  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
	  YYSIZE_T yysize = yysize0;
	  YYSIZE_T yysize1;
	  int yysize_overflow = 0;
	  char *yymsg = 0;
#	  define YYERROR_VERBOSE_ARGS_MAXIMUM 5
	  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
	  int yyx;

#if 0
	  /* This is so xgettext sees the translatable formats that are
	     constructed on the fly.  */
	  YY_("syntax error, unexpected %s");
	  YY_("syntax error, unexpected %s, expecting %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s or %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
#endif
	  char *yyfmt;
	  char const *yyf;
	  static char const yyunexpected[] = "syntax error, unexpected %s";
	  static char const yyexpecting[] = ", expecting %s";
	  static char const yyor[] = " or %s";
	  char yyformat[sizeof yyunexpected
			+ sizeof yyexpecting - 1
			+ ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
			   * (sizeof yyor - 1))];
	  char const *yyprefix = yyexpecting;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 1;

	  yyarg[0] = yytname[yytype];
	  yyfmt = yystpcpy (yyformat, yyunexpected);

	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
		  {
		    yycount = 1;
		    yysize = yysize0;
		    yyformat[sizeof yyunexpected - 1] = '\0';
		    break;
		  }
		yyarg[yycount++] = yytname[yyx];
		yysize1 = yysize + yytnamerr (0, yytname[yyx]);
		yysize_overflow |= yysize1 < yysize;
		yysize = yysize1;
		yyfmt = yystpcpy (yyfmt, yyprefix);
		yyprefix = yyor;
	      }

	  yyf = YY_(yyformat);
	  yysize1 = yysize + yystrlen (yyf);
	  yysize_overflow |= yysize1 < yysize;
	  yysize = yysize1;

	  if (!yysize_overflow && yysize <= YYSTACK_ALLOC_MAXIMUM)
	    yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg)
	    {
	      /* Avoid sprintf, as that infringes on the user's name space.
		 Don't have undefined behavior even if the translation
		 produced a string with the wrong number of "%s"s.  */
	      char *yyp = yymsg;
	      int yyi = 0;
	      while ((*yyp = *yyf))
		{
		  if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		    {
		      yyp += yytnamerr (yyp, yyarg[yyi++]);
		      yyf += 2;
		    }
		  else
		    {
		      yyp++;
		      yyf++;
		    }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    {
	      yyerror (YY_("syntax error"));
	      goto yyexhaustedlab;
	    }
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror (YY_("syntax error"));
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
        {
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
        }
      else
	{
	  yydestruct ("Error: discarding", yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (0)
     goto yyerrorlab;

yyvsp -= yylen;
  yyssp -= yylen;
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
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


      yydestruct ("Error: popping", yystos[yystate], yyvsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token. */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK;
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 560 "lscp.y"


/**
 * Will be called when an error occured (usually syntax error).
 */
void yyerror(const char* s) {
    dmsg(2,("LSCPParser: %s\n", s));
}

/**
 * Clears input buffer.
 */
void restart(yyparse_param_t* pparam, int& yychar) {
    bytes = 0;
    ptr   = 0;
}


