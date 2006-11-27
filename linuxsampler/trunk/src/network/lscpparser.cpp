/* A Bison parser, made by GNU Bison 2.2.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

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

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Using locations.  */
#define YYLSP_NEEDED 0







/* Copy the first part of user declarations.  */
#line 31 "lscp.y"


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

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 140 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
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
      while (YYID (0))
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
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  46
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   4233

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  227
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  117
/* YYNRULES -- Number of rules.  */
#define YYNRULES  465
/* YYNRULES -- Number of states.  */
#define YYNSTATES  1365

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   257

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,    10,    11,    13,    15,    17,    19,
      22,    25,    28,    31,    35,    39,    43,    47,    51,    55,
      59,    63,    67,    71,    75,    79,    83,    87,    91,    93,
      95,    97,    99,   101,   103,   105,   107,   109,   111,   113,
     115,   117,   119,   121,   123,   139,   157,   175,   195,   203,
     207,   209,   211,   217,   225,   235,   237,   243,   251,   261,
     263,   265,   271,   277,   285,   295,   303,   313,   315,   321,
     329,   335,   341,   347,   351,   353,   355,   357,   367,   375,
     385,   393,   403,   407,   411,   417,   421,   427,   431,   435,
     437,   441,   445,   449,   453,   459,   467,   473,   483,   489,
     495,   501,   507,   513,   519,   525,   529,   535,   537,   539,
     541,   543,   545,   547,   549,   551,   553,   559,   567,   571,
     573,   575,   577,   579,   581,   583,   585,   587,   589,   591,
     593,   595,   597,   599,   601,   603,   605,   607,   609,   611,
     613,   617,   619,   621,   623,   625,   627,   629,   631,   634,
     638,   643,   648,   650,   653,   655,   657,   659,   661,   663,
     665,   667,   669,   671,   673,   675,   678,   681,   684,   687,
     690,   693,   696,   699,   702,   704,   706,   708,   710,   712,
     714,   716,   718,   720,   722,   724,   726,   728,   730,   732,
     734,   736,   738,   740,   742,   744,   746,   748,   750,   752,
     754,   756,   758,   760,   762,   764,   766,   768,   770,   772,
     774,   776,   778,   780,   782,   784,   786,   788,   790,   792,
     794,   796,   798,   800,   802,   804,   806,   808,   810,   812,
     814,   816,   818,   820,   822,   824,   826,   828,   830,   832,
     834,   836,   838,   840,   842,   844,   846,   848,   850,   852,
     854,   856,   858,   860,   862,   864,   866,   868,   870,   872,
     874,   876,   878,   880,   882,   884,   886,   888,   890,   892,
     894,   896,   898,   900,   902,   904,   906,   908,   910,   912,
     914,   916,   918,   920,   922,   924,   926,   928,   930,   932,
     934,   936,   938,   940,   942,   944,   946,   948,   950,   952,
     954,   956,   958,   960,   962,   964,   966,   968,   970,   972,
     974,   976,   978,   980,   982,   984,   986,   988,   990,   992,
     994,   996,   998,  1000,  1002,  1004,  1006,  1008,  1010,  1012,
    1014,  1016,  1018,  1020,  1022,  1024,  1026,  1028,  1030,  1032,
    1034,  1036,  1038,  1040,  1042,  1044,  1046,  1048,  1050,  1052,
    1054,  1056,  1058,  1060,  1062,  1064,  1066,  1068,  1070,  1072,
    1074,  1076,  1078,  1080,  1082,  1084,  1086,  1088,  1090,  1092,
    1094,  1096,  1098,  1100,  1102,  1104,  1106,  1108,  1110,  1112,
    1114,  1116,  1118,  1120,  1122,  1124,  1126,  1128,  1130,  1132,
    1134,  1136,  1138,  1140,  1142,  1144,  1147,  1150,  1154,  1158,
    1160,  1162,  1164,  1168,  1172,  1176,  1182,  1188,  1195,  1203,
    1208,  1213,  1217,  1227,  1234,  1238,  1248,  1260,  1267,  1275,
    1293,  1324,  1333,  1338,  1352,  1365,  1377,  1390,  1402,  1420,
    1442,  1453,  1460,  1470,  1485,  1496,  1526,  1547,  1567,  1597,
    1617,  1648,  1669,  1687,  1716,  1744,  1770,  1789,  1807,  1835,
    1851,  1868,  1886,  1902,  1921,  1937,  1948,  1955,  1962,  1967,
    1972,  1978,  1989,  1995,  2009,  2014
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     228,     0,    -1,   229,   278,    -1,   229,   279,   278,    -1,
      -1,   230,    -1,   231,    -1,     1,    -1,     3,    -1,   230,
       3,    -1,   230,   277,    -1,   230,   273,    -1,   230,   269,
      -1,   280,   277,   296,    -1,   282,   277,   234,    -1,   283,
     277,   235,    -1,   281,   277,   237,    -1,   285,   277,   239,
      -1,   286,   277,   242,    -1,   287,   277,   247,    -1,   288,
     277,   243,    -1,   291,   277,   236,    -1,   292,   277,   238,
      -1,   293,   277,   232,    -1,   294,   277,   233,    -1,   295,
     277,   275,    -1,   340,   277,   240,    -1,   284,   277,   241,
      -1,   340,    -1,   343,    -1,   301,    -1,   305,    -1,   304,
      -1,   303,    -1,   302,    -1,   341,    -1,   306,    -1,   301,
      -1,   305,    -1,   304,    -1,   303,    -1,   302,    -1,   341,
      -1,   306,    -1,   327,   277,   257,   277,   258,   277,   259,
     277,   263,   277,   264,   277,   262,   277,   260,    -1,   327,
     277,   257,   277,   258,   277,   259,   277,   263,   277,   264,
     277,   262,   277,   260,   277,   250,    -1,   327,   277,   257,
     277,   258,   277,   259,   277,   263,   277,   264,   277,   262,
     277,   260,   277,   265,    -1,   327,   277,   257,   277,   258,
     277,   259,   277,   263,   277,   264,   277,   262,   277,   260,
     277,   250,   277,   265,    -1,   327,   277,   257,   277,   258,
     277,   259,    -1,   296,   277,   261,    -1,   297,    -1,   321,
      -1,   329,   277,   300,   277,   269,    -1,   326,   277,   300,
     277,   269,   277,   269,    -1,   326,   277,   300,   277,   269,
     277,   269,   277,   245,    -1,   298,    -1,   317,   277,   300,
     277,   269,    -1,   316,   277,   300,   277,   269,   277,   269,
      -1,   316,   277,   300,   277,   269,   277,   269,   277,   245,
      -1,   314,    -1,   324,    -1,   315,   277,   300,   277,   273,
      -1,   325,   277,   300,   277,   273,    -1,   330,   277,   300,
     277,   273,   277,   273,    -1,   323,   277,   300,   277,   273,
     277,   273,   277,   269,    -1,   319,   277,   300,   277,   273,
     277,   273,    -1,   318,   277,   300,   277,   273,   277,   273,
     277,   269,    -1,   299,    -1,   296,   277,   300,   277,   261,
      -1,   296,   277,   303,   277,   246,   277,   261,    -1,   296,
     277,   304,   277,   261,    -1,   296,   277,   305,   277,   261,
      -1,   309,   277,   300,   277,   263,    -1,   334,   277,   300,
      -1,   306,    -1,   307,    -1,   328,    -1,   327,   277,   300,
     277,   257,   277,   258,   277,   259,    -1,   313,   277,   273,
     277,   269,     4,   266,    -1,   318,   277,   273,   277,   273,
     277,   269,     4,   266,    -1,   322,   277,   273,   277,   269,
       4,   266,    -1,   323,   277,   273,   277,   273,   277,   269,
       4,   266,    -1,   296,   277,   244,    -1,   342,   277,   268,
      -1,   315,   277,   269,   277,   245,    -1,   315,   277,   269,
      -1,   325,   277,   269,   277,   245,    -1,   325,   277,   269,
      -1,   296,   277,   261,    -1,   328,    -1,   315,   277,   273,
      -1,   325,   277,   273,    -1,   308,   277,   248,    -1,   309,
     277,   249,    -1,   315,   277,   261,   277,   251,    -1,   319,
     277,   261,   277,   252,   277,   252,    -1,   320,   277,   261,
     277,   253,    -1,   333,   277,   261,   277,   251,   277,   254,
     277,   255,    -1,   325,   277,   261,   277,   251,    -1,   330,
     277,   261,   277,   254,    -1,   331,   277,   261,   277,   255,
      -1,   332,   277,   261,   277,   256,    -1,   335,   277,   261,
     277,   260,    -1,   336,   277,   261,   277,   268,    -1,   337,
     277,   261,   277,   268,    -1,   269,     4,   266,    -1,   245,
     277,   269,     4,   266,    -1,   338,    -1,   339,    -1,   314,
      -1,   324,    -1,   299,    -1,   297,    -1,   321,    -1,   298,
      -1,   328,    -1,   264,   277,   262,   277,   261,    -1,   290,
     277,   264,   277,   262,   277,   261,    -1,   263,   277,   261,
      -1,   310,    -1,   311,    -1,   312,    -1,   273,    -1,   273,
      -1,   269,    -1,   273,    -1,   273,    -1,   289,    -1,   269,
      -1,   273,    -1,   273,    -1,   273,    -1,   270,    -1,   273,
      -1,   273,    -1,   273,    -1,   269,    -1,   276,    -1,   276,
      -1,   267,    -1,   266,     5,   267,    -1,   269,    -1,   276,
      -1,   273,    -1,   270,    -1,   273,    -1,   269,    -1,   274,
      -1,   269,   274,    -1,   271,     6,   271,    -1,     7,   271,
       6,   271,    -1,     8,   271,     6,   271,    -1,   272,    -1,
     271,   272,    -1,     9,    -1,    10,    -1,    11,    -1,    12,
      -1,    13,    -1,    14,    -1,    15,    -1,    16,    -1,    17,
      -1,    18,    -1,   272,    -1,    10,   271,    -1,    11,   271,
      -1,    12,   271,    -1,    13,   271,    -1,    14,   271,    -1,
      15,   271,    -1,    16,   271,    -1,    17,   271,    -1,    18,
     271,    -1,    19,    -1,    20,    -1,    21,    -1,    22,    -1,
      23,    -1,    24,    -1,    25,    -1,    26,    -1,    27,    -1,
      28,    -1,    29,    -1,    30,    -1,    31,    -1,    32,    -1,
      33,    -1,    34,    -1,    35,    -1,    36,    -1,    37,    -1,
      38,    -1,    39,    -1,    40,    -1,    41,    -1,    42,    -1,
      43,    -1,    44,    -1,    45,    -1,    46,    -1,    47,    -1,
      48,    -1,    49,    -1,    50,    -1,    51,    -1,    52,    -1,
      53,    -1,    54,    -1,    55,    -1,    56,    -1,    57,    -1,
      58,    -1,    59,    -1,    60,    -1,    61,    -1,    62,    -1,
      63,    -1,    64,    -1,    65,    -1,    66,    -1,    67,    -1,
      68,    -1,    69,    -1,    70,    -1,     9,    -1,    10,    -1,
      11,    -1,    12,    -1,    13,    -1,    14,    -1,    15,    -1,
      16,    -1,    17,    -1,    18,    -1,    71,    -1,     3,    -1,
      72,    -1,    73,    -1,    74,    -1,    75,    -1,    76,    -1,
      77,    -1,     7,    -1,     8,    -1,     6,    -1,     5,    -1,
      78,    -1,    79,    -1,    80,    -1,    81,    -1,     4,    -1,
      82,    -1,    83,    -1,    84,    -1,    85,    -1,    86,    -1,
      87,    -1,    88,    -1,    89,    -1,    90,    -1,    91,    -1,
      92,    -1,    93,    -1,    94,    -1,    95,    -1,    96,    -1,
      97,    -1,    98,    -1,    99,    -1,   100,    -1,   101,    -1,
     102,    -1,   103,    -1,   104,    -1,   105,    -1,   106,    -1,
     107,    -1,   108,    -1,   109,    -1,   110,    -1,   111,    -1,
     112,    -1,   113,    -1,   114,    -1,   115,    -1,   116,    -1,
     117,    -1,   118,    -1,   119,    -1,   120,    -1,   121,    -1,
     122,    -1,   123,    -1,   124,    -1,   125,    -1,   126,    -1,
     127,    -1,   128,    -1,   129,    -1,   130,    -1,   131,    -1,
     132,    -1,   133,    -1,   134,    -1,   135,    -1,   136,    -1,
     137,    -1,   138,    -1,   139,    -1,   140,    -1,   141,    -1,
     142,    -1,   143,    -1,   144,    -1,   145,    -1,   146,    -1,
     147,    -1,   148,    -1,   149,    -1,   150,    -1,   151,    -1,
     152,    -1,   153,    -1,   154,    -1,   155,    -1,   156,    -1,
     157,    -1,   158,    -1,   159,    -1,   160,    -1,   161,    -1,
     162,    -1,   163,    -1,   164,    -1,   165,    -1,   166,    -1,
     167,    -1,   168,    -1,   169,    -1,   170,    -1,   171,    -1,
     172,    -1,   173,    -1,   174,    -1,   175,    -1,   176,    -1,
     177,    -1,   178,    -1,   179,    -1,   180,    -1,   181,    -1,
     182,    -1,   183,    -1,   184,    -1,   185,    -1,   186,    -1,
     187,    -1,   188,    -1,   189,    -1,   190,    -1,   191,    -1,
     192,    -1,   193,    -1,   194,    -1,   195,    -1,   196,    -1,
     197,    -1,   198,    -1,   199,    -1,   200,    -1,   201,    -1,
     202,    -1,   203,    -1,   204,    -1,   205,    -1,   206,    -1,
     207,    -1,   208,    -1,   209,    -1,   210,    -1,   211,    -1,
     212,    -1,   213,    -1,   214,    -1,   215,    -1,   216,    -1,
     217,    -1,   218,    -1,   219,    -1,   220,    -1,   221,    -1,
     277,    -1,   269,    -1,   275,   277,    -1,   275,   269,    -1,
     222,   275,   222,    -1,   223,   275,   223,    -1,   224,    -1,
     225,    -1,   226,    -1,    19,    22,    22,    -1,    25,    23,
      38,    -1,    31,    19,    34,    -1,    39,    32,    31,    19,
      34,    -1,    21,    30,    23,    19,    36,    -1,    21,    36,
      23,    19,    38,    23,    -1,    22,    23,    37,    38,    36,
      33,    43,    -1,    30,    27,    37,    38,    -1,    30,    33,
      19,    22,    -1,    19,    30,    30,    -1,    32,    33,    32,
      89,    31,    33,    22,    19,    30,    -1,    36,    23,    31,
      33,    40,    23,    -1,    37,    23,    38,    -1,    37,    39,
      20,    37,    21,    36,    27,    20,    23,    -1,    39,    32,
      37,    39,    20,    37,    21,    36,    27,    20,    23,    -1,
      37,    23,    30,    23,    21,    38,    -1,    21,    26,    19,
      32,    32,    23,    30,    -1,    19,    40,    19,    27,    30,
      19,    20,    30,    23,    89,    23,    32,    25,    27,    32,
      23,    37,    -1,    19,    40,    19,    27,    30,    19,    20,
      30,    23,    89,    19,    39,    22,    27,    33,    89,    33,
      39,    38,    34,    39,    38,    89,    22,    36,    27,    40,
      23,    36,    37,    -1,    21,    26,    19,    32,    32,    23,
      30,    37,    -1,    27,    32,    24,    33,    -1,    21,    26,
      19,    32,    32,    23,    30,    89,    21,    33,    39,    32,
      38,    -1,    21,    26,    19,    32,    32,    23,    30,    89,
      27,    32,    24,    33,    -1,    20,    39,    24,    24,    23,
      36,    89,    24,    27,    30,    30,    -1,    37,    38,    36,
      23,    19,    31,    89,    21,    33,    39,    32,    38,    -1,
      40,    33,    27,    21,    23,    89,    21,    33,    39,    32,
      38,    -1,    38,    33,    38,    19,    30,    89,    40,    33,
      27,    21,    23,    89,    21,    33,    39,    32,    38,    -1,
      38,    33,    38,    19,    30,    89,    40,    33,    27,    21,
      23,    89,    21,    33,    39,    32,    38,    89,    31,    19,
      42,    -1,    27,    32,    37,    38,    36,    39,    31,    23,
      32,    38,    -1,    23,    32,    25,    27,    32,    23,    -1,
      33,    32,    89,    22,    23,    31,    19,    32,    22,    -1,
      33,    32,    89,    22,    23,    31,    19,    32,    22,    89,
      26,    33,    30,    22,    -1,    34,    23,    36,    37,    27,
      37,    38,    23,    32,    38,    -1,    19,    39,    22,    27,
      33,    89,    33,    39,    38,    34,    39,    38,    89,    22,
      23,    40,    27,    21,    23,    89,    34,    19,    36,    19,
      31,    23,    38,    23,    36,    -1,    19,    39,    22,    27,
      33,    89,    33,    39,    38,    34,    39,    38,    89,    22,
      23,    40,    27,    21,    23,    37,    -1,    19,    39,    22,
      27,    33,    89,    33,    39,    38,    34,    39,    38,    89,
      22,    23,    40,    27,    21,    23,    -1,    19,    39,    22,
      27,    33,    89,    33,    39,    38,    34,    39,    38,    89,
      22,    36,    27,    40,    23,    36,    89,    34,    19,    36,
      19,    31,    23,    38,    23,    36,    -1,    19,    39,    22,
      27,    33,    89,    33,    39,    38,    34,    39,    38,    89,
      22,    36,    27,    40,    23,    36,    -1,    19,    39,    22,
      27,    33,    89,    33,    39,    38,    34,    39,    38,    89,
      21,    26,    19,    32,    32,    23,    30,    89,    34,    19,
      36,    19,    31,    23,    38,    23,    36,    -1,    19,    39,
      22,    27,    33,    89,    33,    39,    38,    34,    39,    38,
      89,    21,    26,    19,    32,    32,    23,    30,    -1,    19,
      39,    22,    27,    33,    89,    33,    39,    38,    34,    39,
      38,    89,    38,    43,    34,    23,    -1,    19,    40,    19,
      27,    30,    19,    20,    30,    23,    89,    31,    27,    22,
      27,    89,    27,    32,    34,    39,    38,    89,    22,    36,
      27,    40,    23,    36,    37,    -1,    31,    27,    22,    27,
      89,    27,    32,    34,    39,    38,    89,    22,    23,    40,
      27,    21,    23,    89,    34,    19,    36,    19,    31,    23,
      38,    23,    36,    -1,    31,    27,    22,    27,    89,    27,
      32,    34,    39,    38,    89,    34,    33,    36,    38,    89,
      34,    19,    36,    19,    31,    23,    38,    23,    36,    -1,
      31,    27,    22,    27,    89,    27,    32,    34,    39,    38,
      89,    22,    23,    40,    27,    21,    23,    37,    -1,    31,
      27,    22,    27,    89,    27,    32,    34,    39,    38,    89,
      22,    23,    40,    27,    21,    23,    -1,    31,    27,    22,
      27,    89,    27,    32,    34,    39,    38,    89,    22,    36,
      27,    40,    23,    36,    89,    34,    19,    36,    19,    31,
      23,    38,    23,    36,    -1,    31,    27,    22,    27,    89,
      27,    32,    37,    38,    36,    39,    31,    23,    32,    38,
      -1,    31,    27,    22,    27,    89,    27,    32,    37,    38,
      36,    39,    31,    23,    32,    38,    37,    -1,    31,    27,
      22,    27,    89,    27,    32,    34,    39,    38,    89,    22,
      36,    27,    40,    23,    36,    -1,    31,    27,    22,    27,
      89,    27,    32,    34,    39,    38,    89,    34,    33,    36,
      38,    -1,    31,    27,    22,    27,    89,    27,    32,    34,
      39,    38,    89,    21,    26,    19,    32,    32,    23,    30,
      -1,    31,    27,    22,    27,    89,    27,    32,    34,    39,
      38,    89,    38,    43,    34,    23,    -1,    31,    27,    22,
      27,    89,    27,    32,    34,    39,    38,    -1,    37,    23,
      36,    40,    23,    36,    -1,    40,    33,    30,    39,    31,
      23,    -1,    31,    39,    38,    23,    -1,    37,    33,    30,
      33,    -1,    20,    43,    38,    23,    37,    -1,    34,    23,
      36,    21,    23,    32,    38,    19,    25,    23,    -1,    36,
      23,    37,    23,    38,    -1,    31,    27,    37,    21,    23,
      30,    30,    19,    32,    23,    33,    39,    37,    -1,    23,
      21,    26,    33,    -1,    35,    39,    27,    38,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    95,    95,    96,    99,   100,   101,   102,   105,   106,
     107,   108,   109,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   122,   123,   124,   125,   126,   127,   128,   129,
     132,   133,   134,   135,   136,   137,   138,   141,   142,   143,
     144,   145,   146,   147,   150,   151,   152,   153,   156,   159,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   192,   193,
     194,   195,   196,   197,   200,   201,   202,   203,   206,   209,
     212,   213,   216,   217,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   233,   234,   237,   238,   241,
     242,   243,   244,   245,   246,   247,   250,   251,   254,   257,
     258,   259,   262,   265,   268,   271,   274,   275,   278,   281,
     284,   287,   290,   291,   294,   297,   300,   303,   306,   309,
     310,   313,   314,   315,   316,   324,   325,   328,   329,   332,
     333,   334,   338,   339,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   354,   355,   356,   357,   358,   359,
     360,   361,   362,   363,   365,   365,   365,   365,   365,   365,
     365,   365,   365,   365,   365,   365,   365,   365,   365,   365,
     365,   365,   365,   365,   365,   365,   365,   365,   365,   365,
     366,   366,   366,   366,   366,   366,   366,   366,   366,   366,
     366,   366,   366,   366,   366,   366,   366,   366,   366,   366,
     366,   366,   366,   366,   366,   366,   367,   367,   367,   367,
     367,   367,   367,   367,   367,   367,   368,   368,   368,   368,
     368,   368,   368,   368,   368,   368,   368,   368,   368,   369,
     369,   369,   369,   369,   369,   369,   370,   370,   370,   370,
     370,   371,   371,   371,   371,   372,   372,   372,   373,   373,
     373,   374,   374,   374,   375,   375,   375,   376,   376,   376,
     377,   377,   377,   378,   378,   378,   379,   379,   379,   380,
     380,   380,   381,   381,   381,   382,   382,   382,   383,   383,
     383,   384,   384,   384,   385,   385,   385,   386,   386,   386,
     387,   387,   387,   388,   388,   388,   389,   389,   389,   390,
     390,   390,   391,   391,   391,   392,   392,   392,   393,   393,
     393,   394,   394,   394,   395,   395,   395,   396,   396,   396,
     397,   397,   397,   398,   398,   398,   399,   399,   399,   400,
     400,   400,   401,   401,   401,   402,   402,   402,   403,   403,
     403,   404,   404,   404,   405,   405,   405,   406,   406,   406,
     407,   407,   407,   408,   408,   408,   409,   409,   409,   410,
     410,   410,   411,   411,   411,   412,   412,   412,   413,   413,
     413,   414,   414,   417,   418,   419,   420,   423,   424,   430,
     433,   436,   439,   442,   445,   448,   451,   454,   457,   460,
     463,   466,   469,   472,   475,   478,   481,   484,   487,   490,
     493,   496,   499,   502,   505,   508,   511,   514,   517,   520,
     523,   526,   529,   532,   535,   538,   541,   544,   547,   550,
     553,   556,   559,   562,   565,   568,   571,   574,   577,   580,
     583,   586,   589,   592,   595,   598,   601,   604,   607,   610,
     613,   616,   619,   622,   625,   628
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
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
  "command", "subscribe_event", "unsubscribe_event", "map_instruction",
  "unmap_instruction", "remove_instruction", "get_instruction",
  "set_instruction", "create_instruction", "reset_instruction",
  "clear_instruction", "destroy_instruction", "load_instruction",
  "set_chan_instruction", "key_val_list", "buffer_size_type",
  "list_instruction", "load_instr_args", "load_engine_args",
  "instr_load_mode", "device_index", "audio_channel_index",
  "audio_output_type_name", "midi_input_port_index",
  "midi_input_channel_index", "midi_input_type_name", "midi_bank_msb",
  "midi_bank_lsb", "midi_prog", "volume_value", "sampler_channel",
  "instrument_index", "engine_name", "filename", "entry_name",
  "param_val_list", "param_val", "boolean", "string", "dotnum", "digits",
  "digit", "number", "char", "text", "stringval", "SP", "LF", "CR", "ADD",
  "GET", "MAP", "UNMAP", "CLEAR", "CREATE", "DESTROY", "LIST", "LOAD",
  "ALL", "NON_MODAL", "REMOVE", "SET", "SUBSCRIBE", "UNSUBSCRIBE",
  "SELECT", "CHANNEL", "AVAILABLE_ENGINES",
  "AVAILABLE_AUDIO_OUTPUT_DRIVERS", "CHANNELS", "INFO", "CHANNEL_COUNT",
  "CHANNEL_INFO", "BUFFER_FILL", "STREAM_COUNT", "VOICE_COUNT",
  "TOTAL_VOICE_COUNT", "TOTAL_VOICE_COUNT_MAX", "INSTRUMENT", "ENGINE",
  "ON_DEMAND", "ON_DEMAND_HOLD", "PERSISTENT",
  "AUDIO_OUTPUT_DEVICE_PARAMETER", "AUDIO_OUTPUT_DEVICES",
  "AUDIO_OUTPUT_DEVICE", "AUDIO_OUTPUT_DRIVER_PARAMETER",
  "AUDIO_OUTPUT_DRIVER", "AUDIO_OUTPUT_CHANNEL_PARAMETER",
  "AUDIO_OUTPUT_CHANNEL", "AUDIO_OUTPUT_TYPE",
  "AVAILABLE_MIDI_INPUT_DRIVERS", "MIDI_INPUT_DEVICE_PARAMETER",
  "MIDI_INPUT_PORT_PARAMETER", "MIDI_INPUT_DEVICES", "MIDI_INPUT_DEVICE",
  "MIDI_INPUT_DRIVER_PARAMETER", "MIDI_INSTRUMENT", "MIDI_INSTRUMENTS",
  "MIDI_INPUT_DRIVER", "MIDI_INPUT_PORT", "MIDI_INPUT_CHANNEL",
  "MIDI_INPUT_TYPE", "MIDI_INPUT", "SERVER", "VOLUME", "MUTE", "SOLO",
  "BYTES", "PERCENTAGE", "RESET", "MISCELLANEOUS", "ECHO", "QUIT", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
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
static const yytype_uint16 yyr1[] =
{
       0,   227,   228,   228,   229,   229,   229,   229,   230,   230,
     230,   230,   230,   231,   231,   231,   231,   231,   231,   231,
     231,   231,   231,   231,   231,   231,   231,   231,   231,   231,
     232,   232,   232,   232,   232,   232,   232,   233,   233,   233,
     233,   233,   233,   233,   234,   234,   234,   234,   235,   236,
     237,   237,   237,   237,   237,   237,   237,   237,   237,   237,
     237,   237,   237,   237,   237,   237,   237,   237,   237,   237,
     237,   237,   237,   237,   237,   237,   237,   237,   238,   238,
     238,   238,   238,   238,   239,   239,   239,   239,   240,   241,
     242,   242,   243,   243,   244,   244,   244,   244,   244,   244,
     244,   244,   244,   244,   244,   245,   245,   246,   246,   247,
     247,   247,   247,   247,   247,   247,   248,   248,   249,   250,
     250,   250,   251,   252,   253,   254,   255,   255,   256,   257,
     258,   259,   260,   260,   261,   262,   263,   264,   265,   266,
     266,   267,   267,   267,   267,   268,   268,   269,   269,   270,
     270,   270,   271,   271,   272,   272,   272,   272,   272,   272,
     272,   272,   272,   272,   273,   273,   273,   273,   273,   273,
     273,   273,   273,   273,   274,   274,   274,   274,   274,   274,
     274,   274,   274,   274,   274,   274,   274,   274,   274,   274,
     274,   274,   274,   274,   274,   274,   274,   274,   274,   274,
     274,   274,   274,   274,   274,   274,   274,   274,   274,   274,
     274,   274,   274,   274,   274,   274,   274,   274,   274,   274,
     274,   274,   274,   274,   274,   274,   274,   274,   274,   274,
     274,   274,   274,   274,   274,   274,   274,   274,   274,   274,
     274,   274,   274,   274,   274,   274,   274,   274,   274,   274,
     274,   274,   274,   274,   274,   274,   274,   274,   274,   274,
     274,   274,   274,   274,   274,   274,   274,   274,   274,   274,
     274,   274,   274,   274,   274,   274,   274,   274,   274,   274,
     274,   274,   274,   274,   274,   274,   274,   274,   274,   274,
     274,   274,   274,   274,   274,   274,   274,   274,   274,   274,
     274,   274,   274,   274,   274,   274,   274,   274,   274,   274,
     274,   274,   274,   274,   274,   274,   274,   274,   274,   274,
     274,   274,   274,   274,   274,   274,   274,   274,   274,   274,
     274,   274,   274,   274,   274,   274,   274,   274,   274,   274,
     274,   274,   274,   274,   274,   274,   274,   274,   274,   274,
     274,   274,   274,   274,   274,   274,   274,   274,   274,   274,
     274,   274,   274,   274,   274,   274,   274,   274,   274,   274,
     274,   274,   274,   274,   274,   274,   274,   274,   274,   274,
     274,   274,   274,   274,   274,   274,   274,   274,   274,   274,
     274,   274,   274,   275,   275,   275,   275,   276,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,   339,   340,   341,   342,   343
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     3,     0,     1,     1,     1,     1,     2,
       2,     2,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,    15,    17,    17,    19,     7,     3,
       1,     1,     5,     7,     9,     1,     5,     7,     9,     1,
       1,     5,     5,     7,     9,     7,     9,     1,     5,     7,
       5,     5,     5,     3,     1,     1,     1,     9,     7,     9,
       7,     9,     3,     3,     5,     3,     5,     3,     3,     1,
       3,     3,     3,     3,     5,     7,     5,     9,     5,     5,
       5,     5,     5,     5,     5,     3,     5,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     5,     7,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     2,     3,
       4,     4,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     1,     1,     1,     1,     1,     1,
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
       1,     1,     1,     1,     1,     2,     2,     3,     3,     1,
       1,     1,     3,     3,     3,     5,     5,     6,     7,     4,
       4,     3,     9,     6,     3,     9,    11,     6,     7,    17,
      30,     8,     4,    13,    12,    11,    12,    11,    17,    21,
      10,     6,     9,    14,    10,    29,    20,    19,    29,    19,
      30,    20,    17,    28,    27,    25,    18,    17,    27,    15,
      16,    17,    15,    18,    15,    10,     6,     6,     4,     4,
       5,    10,     5,    13,     4,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     7,     8,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     5,     6,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    28,    29,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,   400,   401,     2,
       0,     9,   252,   247,   246,   244,   245,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   236,
     238,   239,   240,   241,   242,   243,   248,   249,   250,   251,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,   334,   335,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
     353,   354,   355,   356,   357,   358,   359,   360,   361,   362,
     363,   364,   365,   366,   367,   368,   369,   370,   371,   372,
     373,   374,   375,   376,   377,   378,   379,   380,   381,   382,
     383,   384,   385,   386,   387,   388,   389,   390,   391,   392,
     399,    12,   164,    11,   147,    10,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   402,     0,     0,     0,   403,     0,     0,   404,     0,
       0,     0,     0,   414,     0,     0,     0,     3,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   165,   152,
     166,   167,   168,   169,   170,   171,   172,   173,   237,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   148,
       0,    13,     0,     0,     0,     0,     0,     0,    16,     0,
      50,    55,    67,    74,    75,     0,    59,     0,     0,     0,
       0,     0,    51,     0,    60,     0,     0,     0,    76,     0,
       0,     0,     0,    14,     0,    15,     0,     0,    27,    89,
       0,     0,    17,     0,     0,    18,     0,     0,     0,     0,
       0,    19,   112,   114,   111,   109,   113,   110,   115,     0,
      20,     0,     0,    21,     0,     0,     0,     0,    22,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    23,    30,    34,    33,    32,    31,    36,    35,    24,
      37,    41,    40,    39,    38,    43,    42,   394,    25,   393,
      26,     0,     0,     0,     0,   409,   410,   465,     0,     0,
       0,     0,     0,     0,   153,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   396,
     395,     0,   406,     0,     0,     0,   462,     0,     0,   405,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    73,     0,   155,   156,
     157,   158,   159,   160,   161,   162,   163,     0,   129,     0,
       0,     0,     0,    85,    87,    90,    91,     0,     0,     0,
       0,     0,     0,     0,    92,     0,   137,     0,    93,     0,
     136,    49,   134,     0,     0,     0,     0,     0,     0,     0,
      82,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    83,   146,   145,     0,
       0,     0,     0,     0,     0,    88,   407,     0,   413,   417,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   464,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   408,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    68,     0,     0,     0,
     107,   108,    70,    71,    72,    61,     0,    56,     0,     0,
       0,    62,     0,     0,    52,     0,     0,     0,   130,     0,
       0,     0,     0,    84,     0,    86,     0,     0,     0,     0,
       0,   397,   398,     0,   135,     0,   118,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   431,     0,   456,     0,   422,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   458,   459,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   415,
       0,   418,     0,     0,   418,     0,     0,     0,     0,    69,
      57,     0,    65,     0,    53,     0,    63,     0,     0,   131,
      48,     0,     0,     0,     0,   244,   245,   105,   139,   141,
     144,     0,   152,   143,   142,     0,     0,     0,     0,     0,
     116,     0,     0,     0,     0,     0,     0,    94,   122,     0,
     123,    96,   124,    98,    99,   125,     0,   100,   126,   127,
     101,   128,     0,     0,     0,   102,   132,   133,   103,   104,
      78,     0,    80,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   421,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   457,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   416,     0,     0,     0,     0,
       0,   460,     0,    58,    66,    64,    54,    77,     0,     0,
       0,     0,     0,   106,     0,     0,   140,   149,     0,     0,
       0,     0,   117,     0,     0,     0,     0,    95,   411,     0,
      79,    81,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     150,   151,     0,     0,   430,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   412,     0,     0,     0,     0,    97,   425,
       0,     0,     0,     0,     0,   427,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   455,     0,   424,     0,
     426,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   423,   463,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   461,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   452,   449,     0,   449,    44,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     450,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     419,     0,   447,   451,     0,   428,     0,     0,    45,    46,
     138,   119,   120,   121,     0,   447,     0,     0,     0,     0,
       0,     0,     0,     0,   452,   454,   428,     0,     0,     0,
       0,     0,   446,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   437,   439,
       0,     0,     0,     0,     0,     0,     0,    47,   437,     0,
       0,     0,     0,     0,   442,     0,   441,   436,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     453,     0,     0,     0,     0,     0,     0,   429,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   441,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   445,
     432,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     434,     0,     0,     0,     0,     0,     0,   448,     0,     0,
     444,     0,     0,     0,   443,     0,     0,     0,   438,     0,
       0,   435,   440,   420,   433
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    13,    14,    15,    16,   421,   429,   373,   375,   403,
     348,   408,   382,   440,   378,   385,   400,   590,   733,   709,
     391,   574,   578,  1208,   887,   889,   891,   894,   897,   900,
     557,   727,   858,   905,   581,   743,   579,   575,  1209,   867,
     868,   606,   869,   870,   871,   272,   582,   274,   438,   874,
     802,    49,    50,    17,    18,    19,    20,    21,    22,    23,
      24,    25,   899,   577,    26,    27,    28,    29,    30,   341,
     350,   351,   352,   530,   422,   423,   424,   425,   426,   353,
     354,   401,   355,  1211,  1212,  1213,   410,   356,   357,   358,
     359,   360,   361,   593,   362,   412,   363,   364,   365,   366,
     367,   368,   369,   370,   596,   597,   598,   371,   599,   600,
     601,   710,   711,    31,   428,   414,    32
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -808
static const yytype_int16 yypact[] =
{
      23,  -808,  -808,    18,    59,    47,    57,   111,    93,     8,
     102,    29,    95,   132,   -49,  1814,  -808,   -79,   -79,   -79,
     -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,
     -79,   -79,  -808,   142,   146,   195,   205,   225,   227,   246,
     232,   240,   134,    60,   248,   135,  -808,  -808,  -808,  -808,
      44,  -808,  -808,  -808,  -808,  -808,  -808,  -808,   183,   183,
     183,   183,   183,   183,   183,   183,   183,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  2479,  -808,  -808,  -808,  -808,   249,    56,   242,   242,
     254,    32,    32,    50,   120,   249,   105,    36,    36,  2036,
     249,  -808,   252,   267,   250,  -808,   253,   265,  -808,   255,
     257,   269,   272,  -808,   259,   279,   260,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,   183,  -808,
     183,   183,   183,   183,   183,   183,   183,   183,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
     287,  -808,   173,   288,   284,   290,   295,   286,  -808,   -79,
    -808,  -808,  -808,  -808,  -808,   -79,  -808,   -79,   -79,   -79,
     -79,   -79,  -808,   -79,  -808,   -79,   -79,   -79,  -808,   -79,
     -79,   -79,   308,  -808,   -79,  -808,   -79,   309,  -808,  -808,
     282,   310,  -808,   -79,   -79,  -808,   -79,   -79,   175,   312,
     320,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,   307,
    -808,   -79,   -79,  -808,   -79,   302,   328,   326,  -808,   -79,
     -79,   -79,   -79,   -79,   -79,   318,   332,   333,   324,   330,
     331,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  2479,  2036,  -808,
    -808,   -79,   329,   345,   334,  -808,  -808,  -808,   327,   346,
     364,   367,   356,   371,  -808,   347,   370,   374,   392,   385,
     390,   377,   376,    45,   388,   388,   388,   388,   388,   388,
     388,   388,   388,   388,   388,   388,   388,   394,   391,   391,
     395,   396,   398,  2479,  2479,   391,   391,   399,   400,   402,
     393,    -3,  2479,   391,   405,   403,   406,    24,   391,   391,
     391,   391,  2698,   407,   413,   401,   386,   404,   408,  2479,
    -808,   391,  -808,   411,   412,   414,  -808,   409,   415,  -808,
     416,   417,   419,   421,   418,   425,   428,   420,   422,   424,
     -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,
     -79,   -79,   -79,   -79,   -79,   -79,  -808,   430,   183,   183,
     183,   183,   183,   183,   183,   183,   183,   -79,  -808,   -79,
     431,   432,   434,  2036,  2036,  -808,  -808,   435,   436,   439,
     429,   437,  2036,  2036,  -808,   -79,  -808,   -79,  -808,   -79,
    2479,  -808,  -808,   442,   440,   447,   438,    84,   443,   445,
    -808,   -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,
     -79,   -79,   -79,   -79,   -79,   -79,  -808,  2479,  -808,   451,
     448,   423,   456,   444,   460,  -808,  -808,   446,  -808,  -808,
     455,   462,   458,   459,   461,   463,   464,   344,   470,   467,
     474,   391,    58,   391,   391,  2479,   391,  2479,  2479,   391,
     391,   391,   391,  2479,   391,  2479,   391,   350,   391,   391,
     351,   466,   354,  2479,  2479,   468,   471,   449,   469,   472,
    1370,  1592,   391,    -6,   391,   473,  -808,   450,   478,   480,
     475,   477,   479,   391,   391,   391,   391,   391,   391,   391,
     391,   391,   391,   391,  2479,   391,  2479,   391,   485,   482,
     487,   492,   501,   489,  -808,   512,   497,   511,   452,   516,
     513,   514,   518,   504,   457,   517,  -808,   508,   524,   -79,
    -808,  -808,  -808,  -808,  -808,  -808,  2036,  2479,   -79,   -79,
     -79,  -808,  2036,   -79,  2479,   -79,   525,   -79,  -808,   -79,
     526,   465,   528,   -79,  2917,   -79,   476,   533,   532,   522,
     481,  -808,  -808,   -79,  -808,   -79,  -808,   483,   536,   539,
     540,   545,   538,   530,   -79,   -79,   -79,   -79,   -79,   -79,
     -79,   -79,   -79,   -79,   -79,  3136,   -79,  3355,   -79,   537,
     551,   570,   544,   523,   527,   578,   575,   583,   581,   595,
     587,  -808,   586,  -808,   454,  -808,   582,   585,   391,  2479,
     391,   391,   391,  2479,   391,   391,   591,   391,   391,   592,
     596,   599,  2479,  2258,   600,   589,   604,   606,   607,   391,
     391,   608,   610,   611,   550,  -808,  -808,   609,   391,   391,
    2479,   391,   391,   314,  2479,   391,   294,  2698,  2698,  2258,
    2479,  2258,  2479,   554,   617,   619,   561,   612,   630,  -808,
     633,  -808,   615,   625,   620,    54,   623,   635,   638,  -808,
    2036,   -79,  -808,   -79,  2036,   -79,  -808,   624,   -79,  -808,
    -808,   626,   621,   628,  3574,   183,   183,   659,  -808,  2479,
    -808,   215,    20,  -808,  -808,   627,   620,   169,   642,   634,
    -808,   -79,   631,   640,   580,   645,   652,  -808,  -808,   -79,
    -808,  -808,  2479,  -808,  -808,  -808,   646,  -808,  -808,  -808,
    -808,  2479,   -79,   183,   183,  -808,  -808,  -808,  -808,  -808,
     659,  3793,   659,  4012,   653,   590,   661,   657,   648,   649,
     660,   647,   663,  -808,   650,   654,   664,   651,   667,  2479,
    2479,  2479,  2479,   391,   655,  2479,   658,   662,   656,  2258,
     244,   266,  2258,   183,   668,   672,   665,   676,   391,   675,
     677,   669,   683,  -808,   391,   687,   391,  2258,  2258,   691,
     121,   688,   686,   694,   684,  -808,   690,   598,   689,   693,
     701,  -808,   699,   -79,  2479,  2479,   -79,  -808,   696,   -79,
     697,   692,   698,   659,   183,   183,  -808,   183,   700,   712,
     714,   706,  -808,   703,   716,   717,   704,  -808,  -808,   -79,
     659,   659,   705,   722,   725,   735,   720,   739,   729,   723,
     110,   674,   727,   741,   730,   728,    -6,   731,   732,   680,
     183,   183,   733,   685,  -808,   743,   736,   702,   744,   740,
     314,   755,   747,   763,   757,   756,   769,   759,   760,   754,
     762,   768,   112,   770,   710,   781,   771,   -79,   772,   778,
     784,   780,   788,  -808,   782,   141,   785,   783,  -808,  -808,
     790,   791,   786,   789,   734,  -808,   737,   806,   804,   808,
      63,   798,   809,   812,   816,   814,   391,   819,   758,   821,
     761,   822,   764,   823,   818,   810,   765,   817,  -808,   815,
    -808,   835,   187,   830,   832,   833,   644,   834,   826,   831,
     836,   841,   838,   -79,   839,   843,   827,   846,   837,   213,
     840,   842,   844,    62,  -808,  -808,   850,   847,    74,   852,
     856,   787,   845,   849,   853,   854,   851,  -808,   857,   294,
     858,   874,   848,   875,   872,   877,   878,   873,   866,   824,
     879,   881,   864,   871,   860,   876,   884,   828,   892,   891,
     901,   900,   859,   887,   895,  -808,   -79,   887,   889,   909,
     893,   910,   913,   894,   914,   859,    28,   917,   902,   903,
     907,   918,   922,   905,   908,   915,   919,   930,   920,   921,
    -808,   916,     0,   935,   934,   936,   942,   937,   939,   944,
     945,   925,   938,   940,   949,   941,   943,   952,   951,   946,
    -808,   947,   950,   899,   957,   904,   948,   966,   -79,  -808,
    -808,  -808,  -808,  -808,   969,  -808,   970,   950,   960,   978,
     911,   982,   968,   971,  -808,  -808,  -808,   983,   984,   972,
     967,   975,  -808,   976,   973,   980,   926,   981,    -6,   995,
     996,   997,   998,   988,   991,  1001,  1002,   999,   989,   954,
    1000,   992,  1012,  1014,  1016,  1015,  1004,  -808,  -808,   989,
    1006,   955,  1019,  1017,  -808,  1020,   962,  -808,  1018,  1007,
     965,  1021,  1025,  1023,  1035,  1032,   962,  1026,  1030,  1038,
    -808,  1033,  1049,  1031,  1050,  1054,  1051,  -808,  1046,  1041,
    1060,  1061,  1052,  1062,  1047,  1003,  1048,  1055,  1053,  1066,
    1057,  1063,  1056,  -808,  1064,  1070,  1068,  1071,  1074,  1078,
    1072,  1079,  1084,  1082,  1087,  1076,  1073,  1077,  1080,  1075,
    1086,  1088,  1081,  1085,  1091,  1093,  1083,  1101,  1102,  -808,
    1037,  1089,  1105,  1106,  1107,  1094,  1095,  1097,  1098,  1067,
    -808,  1099,  1100,  1104,  1115,  1116,  1103,  -808,  1110,  1121,
    -808,  1122,  1111,  1112,  -808,  1119,  1114,  1117,  -808,  1109,
    1129,  -808,  -808,  -808,  -808
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -632,  -808,
    -808,  -808,  -808,  -808,  -647,  -518,  -808,   196,   124,  -808,
    -442,  -603,  -760,    26,  -494,  -787,  -615,  -642,   -82,  -790,
     216,  -591,   410,  -807,    43,    55,   -14,   397,  -334,  -473,
     -15,  1113,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -808,  -155,
     882,   883,   885,  -314,   869,   886,  -258,  -253,  -252,   -47,
    -808,  -808,   888,  -808,  -808,  -808,  -808,   890,  -254,  -808,
    -808,   896,   670,  -808,   897,  -808,   906,   898,  -250,  -808,
     -27,   -76,  -808,   673,  -808,  -808,  -808,  -808,  -808,  -808,
    -808,  -808,  -808,  -808,   912,  -808,  -808
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -165
static const yytype_int16 yytable[] =
{
     275,   273,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   615,   576,   906,
     714,   745,   735,   881,     1,  -164,     2,   383,   386,   571,
     432,   384,   387,  1206,  1207,   433,   434,   559,   860,   910,
      33,   912,     3,   586,     4,     5,   729,    41,     6,  1190,
    1131,   380,    43,     7,     8,   587,   415,   416,     9,    10,
      11,   588,    12,   381,   589,   415,  1191,   417,    44,   388,
      36,   389,   529,   418,   419,   342,   420,   343,   707,   344,
      37,   390,   418,  1140,  1079,   420,  1096,   345,   924,    34,
     302,   925,   708,   346,   347,    35,  1141,  1145,   303,  1097,
    1142,   318,   320,   321,   322,   323,   324,   325,   326,   327,
    1146,   669,    40,   319,   319,   319,   319,   319,   319,   319,
     319,   319,   349,   670,   405,    42,   340,    45,   406,  1039,
     404,   409,    46,  1040,  1070,   441,   407,   706,    38,   712,
     713,  1041,  1003,   344,    39,   270,  1071,   399,  1004,   983,
     534,   535,   536,   537,   538,   539,   540,   541,   542,   543,
     544,   545,   546,  1083,   291,   300,   305,  1000,  1001,   292,
     746,   301,   306,   977,   893,  1084,    47,    48,   902,   754,
     755,   756,   757,   758,   759,   760,   761,   762,   763,   764,
     576,   855,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   723,   945,   379,   531,   936,   398,  1117,  1118,
     532,   533,   456,   457,   487,   457,   572,   573,   293,   572,
     573,   943,   572,   573,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,  1135,  1136,   908,   909,   660,   661,
     427,   435,   294,   591,  -164,  -164,  -164,   594,    -4,    -4,
     984,   374,   376,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   295,   296,   297,   298,   299,   304,    47,
     340,   442,   985,   372,   439,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   377,   443,   446,   444,  1103,
     448,   445,   449,   447,   849,   450,   451,   973,   452,   453,
     976,   903,   904,   308,   548,   549,   550,   551,   552,   553,
     554,   555,   556,   455,   458,   880,   459,   460,   461,   462,
     979,   481,   906,   308,   548,   549,   550,   551,   552,   553,
     554,   555,   556,   896,   463,   477,   480,   482,   488,   490,
     464,   494,   465,   466,   467,   468,   469,   489,   470,   495,
     471,   472,   473,   496,   474,   475,   476,   503,   504,   478,
     505,   479,   506,   507,   508,   512,   521,   515,   483,   484,
     514,   485,   486,   454,  1047,   454,   454,   454,   454,   454,
     454,   454,   454,   513,   516,   517,   491,   492,   518,   493,
     519,   520,   522,   523,   497,   498,   499,   500,   501,   502,
     308,   548,   549,   550,   551,   552,   553,   554,   555,   556,
     525,   524,   526,   527,   528,   529,   547,   560,   561,   568,
     562,   567,   612,   510,   569,   271,   511,   583,   585,   584,
     570,   609,   610,   702,   616,   614,   997,   618,   611,   726,
     730,   629,   613,   732,   690,   617,   623,   619,   624,   622,
     625,   620,   626,   621,   992,   627,   630,   647,   650,   651,
     628,   652,   655,   692,   558,   558,   657,   658,   656,   665,
     659,   565,   566,   666,   667,   688,   671,   668,   672,   691,
     689,   693,   695,   696,   602,   603,   604,   605,   608,   694,
     697,   699,   698,   703,   846,   700,   701,   704,   705,   731,
     749,   736,   750,   737,   740,   739,   747,   752,   769,   753,
     771,   772,   774,   751,   770,   631,   632,   633,   634,   635,
     636,   637,   638,   639,   640,   641,   642,   643,   644,   645,
     646,   773,   775,   776,   777,   779,   780,   781,   738,   748,
     783,   778,   648,   576,   649,   782,   784,   787,   653,   654,
     785,   786,   796,   799,   800,   801,   805,   439,   439,   806,
     662,   807,   663,   812,   664,   804,   813,   814,   815,   817,
     808,   816,   811,   833,   834,   836,   673,   674,   675,   676,
     677,   678,   679,   680,   681,   682,   683,   684,   685,   686,
     687,   318,   320,   321,   322,   323,   324,   325,   326,   327,
     835,   839,   840,   319,   319,   319,   319,   319,   319,   319,
     319,   319,   837,   841,   842,   843,   838,   844,   845,   876,
     847,   848,   715,   857,   861,   718,   719,   720,   721,   862,
     558,   863,   725,   875,   728,   728,   877,   878,   879,   885,
     886,   882,   883,   914,   884,   510,   510,   915,   744,   916,
     917,   919,   918,   920,   921,   922,   926,   923,   927,   928,
     937,   934,   938,   936,   942,   946,   944,   947,   339,   951,
     949,   766,   952,   768,   950,   953,   955,   959,   962,   960,
     961,   963,   964,   965,  1122,   966,   967,  1010,   971,   968,
     972,   970,   969,   978,   788,   982,   980,   990,   991,   437,
     981,   789,   995,   790,   791,   792,   988,   793,   794,  1210,
     795,   989,   797,   993,   798,   996,   994,   998,  1002,  1006,
    1005,  1007,  1013,  1008,  1009,  1025,  1018,  1011,   809,  1012,
     810,  1014,  1015,  1017,  1022,  1031,  1019,  1026,  1029,   818,
     819,   820,   821,   822,   823,   824,   825,   826,   827,   828,
    1023,   830,  1024,   832,  1027,  1032,  1028,  1033,  1034,  1035,
    1036,  1037,  1038,  1042,  1044,  1210,  1043,  1046,  1045,  1050,
    1048,  1049,  1051,  1053,  1052,  1054,   851,   852,   853,  1057,
     728,   856,  1056,   859,   859,  1059,  1060,  1061,  1063,   873,
    1062,  1055,  1064,  1067,  1068,  1069,   744,  1065,  1066,  1073,
    1074,  1072,  1075,  1077,   888,   890,  1079,   888,   895,   898,
    1081,   888,   907,   608,   608,   873,  1078,   873,  1080,  1085,
    1082,  1086,  1087,  1091,  1088,  1089,  1092,  1090,  1093,  1094,
    1095,  1098,  1099,  1100,   339,   929,   930,  1102,   931,   932,
     933,  1101,  1104,   935,  1106,  1108,  1110,  1105,   509,  1112,
    1107,  1111,  1115,  1109,  1113,  1114,  1116,  1119,   872,  1120,
    1121,  1123,  1124,  1125,  1127,  1131,   948,  1132,  1133,  1126,
    1128,  1130,  1150,  1144,   954,  1159,  1149,  1134,  1138,  1171,
    1137,   872,  1139,  1143,   872,  1147,   872,   956,  1148,  1151,
    1154,  1152,  1153,   563,   564,  1155,  1157,  1158,  1160,  1161,
    1164,  1163,   580,  1162,  1165,  1167,   339,  1169,   940,   941,
    1170,  1173,   607,  1166,  1168,  1175,  1172,  1174,  1176,   859,
     319,   319,  1177,  1178,  1180,   873,   454,  1181,   873,  1183,
    1184,  1186,  1187,  1185,  1188,  1189,  1192,  1194,  1193,  1195,
     890,  1199,   895,   873,   873,  1198,   940,   941,  1179,  1197,
    1196,  1201,  1200,  1202,  1205,  1204,  1203,  1215,   319,   319,
     339,   339,  1214,  1216,  1016,  1217,  1219,  1220,  1222,  1218,
    1223,  1221,  1225,  1228,  1229,  1227,  1234,   339,  1224,  1226,
    1236,  1231,   437,   437,  1030,  1230,   987,  1232,  1233,  1237,
    1239,  1240,  1241,  1235,   872,   454,   454,   872,   319,  1242,
    1243,  1244,  1245,  1246,   339,  1250,  1247,  1248,  1249,  1253,
    1252,  1254,   872,   872,  1251,  1255,   898,  1256,  1258,  1259,
    1260,  1261,  1262,  1263,  1264,  1265,  1267,  1020,  1021,  1266,
    1270,  1271,  1076,  1272,  1269,  1273,  1276,  1274,  1278,   319,
     319,  1275,   454,  1268,  1277,   580,  1283,   716,   717,  1279,
    1280,  1281,  1282,   722,  1284,   724,  1286,  1285,  1288,  1289,
    1290,  1292,   744,   734,   734,  1287,  1291,  1293,  1294,  1295,
     509,   509,  1296,  1297,  1298,   454,   454,  1299,  1300,  1301,
    1302,  1304,  1303,  1305,  1307,  1310,  1308,  1313,  1129,  1315,
    1316,  1309,  1306,  1348,   765,  1311,   767,  1318,  1317,  1312,
    1314,  1319,  1321,  1322,  1320,  1323,  1324,  1325,  1330,  1326,
    1336,  1329,  1332,   339,   339,   907,  1335,  1327,  1328,   339,
    1331,   339,  1334,  1333,  1337,  1338,  1339,  1340,  1341,  1342,
    1343,   339,  1344,  1346,  1347,  1345,  1350,  1349,  1352,  1353,
    1354,  1182,  1351,  1355,  1356,  1357,  1363,  1358,  1359,  1360,
    1361,  1364,   999,  1362,  1058,  1156,  1257,   430,   986,     0,
       0,     0,   339,   307,   339,   392,   393,   592,   394,     0,
     595,     0,   402,   395,   431,     0,     0,     0,     0,     0,
     396,   397,   411,     0,   872,     0,     0,     0,     0,     0,
       0,     0,   413,  1238,     0,     0,     0,     0,     0,   850,
     436,     0,     0,   854,     0,     0,     0,     0,     0,     0,
       0,     0,   864,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     892,     0,     0,     0,   901,     0,     0,   607,   607,     0,
     911,     0,   913,     0,     0,     0,     0,   339,     0,     0,
       0,   339,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   339,     0,     0,     0,     0,   339,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   339,
       0,     0,     0,     0,     0,     0,     0,     0,   339,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   339,     0,
     339,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   734,
     974,   975,   734,     0,     0,   580,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   339,   339,   328,    52,    53,    54,    55,    56,   329,
     330,   331,   332,   333,   334,   335,   336,   337,   338,    67,
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
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   741,     0,   270,   328,    52,    53,    54,    55,
      56,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,    67,    68,    69,    70,    71,    72,    73,    74,    75,
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
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,     0,   742,   270,    51,    52,    53,
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
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,     0,     0,   270,   328,
      52,    53,    54,    55,    56,   329,   330,   331,   332,   333,
     334,   335,   336,   337,   338,    67,    68,    69,    70,    71,
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
     262,   263,   264,   265,   266,   267,   268,   269,     0,     0,
     270,   328,    52,    53,    54,   865,   866,    57,    58,    59,
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
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     572,   573,   328,    52,    53,    54,    55,    56,   329,   330,
     331,   332,   333,   334,   335,   336,   337,   338,    67,    68,
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
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   328,    52,    53,    54,    55,    56,    57,    58,    59,
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
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     328,   803,    53,    54,    55,    56,   329,   330,   331,   332,
     333,   334,   335,   336,   337,   338,    67,    68,    69,    70,
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
     261,   262,   263,   264,   265,   266,   267,   268,   269,   328,
     829,    53,    54,    55,    56,   329,   330,   331,   332,   333,
     334,   335,   336,   337,   338,    67,    68,    69,    70,    71,
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
     262,   263,   264,   265,   266,   267,   268,   269,   328,   831,
      53,    54,    55,    56,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,    67,    68,    69,    70,    71,    72,
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
     263,   264,   265,   266,   267,   268,   269,   328,   939,    53,
      54,    55,    56,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,    67,    68,    69,    70,    71,    72,    73,
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
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   328,   957,    53,    54,
      55,    56,   329,   330,   331,   332,   333,   334,   335,   336,
     337,   338,    67,    68,    69,    70,    71,    72,    73,    74,
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
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   328,   958,    53,    54,    55,
      56,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,    67,    68,    69,    70,    71,    72,    73,    74,    75,
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
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269
};

static const yytype_int16 yycheck[] =
{
      15,    15,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,   511,   491,   826,
     635,   663,   654,   810,     1,     5,     3,   281,   282,    32,
     288,   281,   282,    33,    34,   288,   288,   479,   798,   829,
      22,   831,    19,    19,    21,    22,   649,    39,    25,    21,
      22,    19,    23,    30,    31,    31,    20,    21,    35,    36,
      37,    37,    39,    31,    40,    20,    38,    31,    39,    19,
      23,    21,    27,    37,    38,    19,    40,    21,    20,    23,
      23,    31,    37,    21,    22,    40,    23,    31,    34,    30,
      30,    37,    34,    37,    38,    36,    34,    23,    38,    36,
      38,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      36,    27,    19,    58,    59,    60,    61,    62,    63,    64,
      65,    66,   277,    39,    19,    23,    21,    32,    23,    19,
     285,   286,     0,    23,    22,   290,    31,   631,    27,   633,
     634,    31,    21,    23,    33,   224,    34,    27,    27,   939,
     464,   465,   466,   467,   468,   469,   470,   471,   472,   473,
     474,   475,   476,    22,    22,    31,    31,   957,   958,    23,
     664,    37,    37,   933,   821,    34,   225,   226,   825,   673,
     674,   675,   676,   677,   678,   679,   680,   681,   682,   683,
     663,   794,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,   644,    34,   280,   463,    37,   283,    21,    22,
     463,   463,    39,    40,    39,    40,   222,   223,    23,   222,
     223,     6,   222,   223,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    21,    22,   827,   828,   572,   573,
     287,   288,    37,   497,   224,   225,   226,   497,   225,   226,
       6,   278,   279,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    38,    37,    19,    34,    27,    20,   225,
      21,    19,     6,    31,   289,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    31,    19,    22,    38,  1076,
      33,    38,    23,    38,   788,    23,    37,   929,    19,    39,
     932,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    26,    26,   809,    32,    27,    23,    33,
     935,    39,  1129,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,   349,    27,    27,    27,    26,    32,
     355,    39,   357,   358,   359,   360,   361,    27,   363,    21,
     365,   366,   367,    27,   369,   370,   371,    39,    26,   374,
      27,   376,    38,    33,    33,    36,    19,    40,   383,   384,
      36,   386,   387,   318,  1016,   320,   321,   322,   323,   324,
     325,   326,   327,    38,    38,    21,   401,   402,    21,   404,
      34,    20,    22,    19,   409,   410,   411,   412,   413,   414,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      25,    19,    22,    36,    38,    27,    22,    22,    22,    19,
      22,    22,    36,   438,    22,    15,   441,    22,    22,    26,
      37,    24,    19,    89,    23,    27,   954,    23,    37,    89,
      89,    19,    38,    89,    21,    33,    27,    38,    27,    32,
      32,    36,    27,    37,   948,    27,    32,    27,    27,    27,
      40,    27,    27,    19,   478,   479,    27,    38,    32,    27,
      33,   485,   486,    33,    27,    24,    33,    39,    33,    23,
      32,    21,    27,    21,   498,   499,   500,   501,   502,    43,
      32,    30,    33,    23,    40,    32,    32,    30,    24,    33,
      22,    33,    22,    32,    32,    36,    33,    30,    23,    30,
      23,    19,    23,    38,    32,   530,   531,   532,   533,   534,
     535,   536,   537,   538,   539,   540,   541,   542,   543,   544,
     545,    30,    20,    36,    23,    19,    23,    23,    89,    89,
      36,    89,   557,  1016,   559,    27,    89,    23,   563,   564,
      33,    43,    27,    27,    89,    27,    23,   572,   573,    27,
     575,    39,   577,    27,   579,    89,    27,    27,    23,    39,
      89,    33,    89,    36,    23,    31,   591,   592,   593,   594,
     595,   596,   597,   598,   599,   600,   601,   602,   603,   604,
     605,   548,   549,   550,   551,   552,   553,   554,   555,   556,
      30,    23,    27,   548,   549,   550,   551,   552,   553,   554,
     555,   556,    89,    30,    33,    20,    89,    30,    32,    30,
      38,    36,   636,    32,    32,   639,   640,   641,   642,    33,
     644,    32,   646,    33,   648,   649,    32,    31,    31,    89,
      31,    33,    32,    89,    33,   660,   661,    30,   662,    30,
      89,    21,    40,    20,    39,    30,    33,    37,    23,    21,
      39,    37,    34,    37,     5,    23,    39,    33,   271,    89,
      39,   685,    27,   687,    34,    23,    30,    24,    21,    89,
      19,    33,    33,    23,    40,    38,    23,    89,    37,    39,
      23,    27,    38,    38,   709,    39,    38,    32,    22,   289,
      38,   716,    33,   718,   719,   720,    38,   722,   723,  1182,
     725,    39,   727,    38,   729,    32,    39,    30,    27,    33,
      32,    27,    21,    39,    34,    19,    34,    38,   743,    36,
     745,    32,    36,    36,    34,    30,    38,    34,    34,   754,
     755,   756,   757,   758,   759,   760,   761,   762,   763,   764,
      38,   766,    38,   768,    38,    33,    39,    32,    23,    39,
      21,    32,    39,    89,    23,  1238,    39,    39,    38,    89,
      39,    39,    39,    30,    89,    39,   790,   791,   792,    39,
     794,   795,    38,   797,   798,    30,    39,    24,    32,   803,
      33,    89,    23,    39,    32,    27,   810,    38,    38,    89,
      19,    31,    31,    31,   818,   819,    22,   821,   822,   823,
      22,   825,   826,   827,   828,   829,    38,   831,    38,    34,
      38,    38,    32,    89,    33,    39,    89,    38,    22,    25,
      22,    33,    23,    21,   437,   850,   851,    23,   853,   854,
     855,    25,    23,   858,    23,    23,    23,    89,   438,    39,
      89,    33,    37,    89,    89,    38,    21,    27,   803,    27,
      27,    27,    36,    32,    23,    22,   881,    40,    22,    33,
      32,    32,    27,    26,   889,    27,    89,    40,    36,    19,
      40,   826,    38,    33,   829,    33,   831,   902,    32,    40,
      39,    38,    38,   483,   484,    38,    38,    23,    23,    27,
      27,    23,   492,    26,    38,    26,   509,    43,   865,   866,
      39,    27,   502,    89,    33,    23,    40,    89,    27,   933,
     865,   866,    21,    23,    37,   939,   871,    32,   942,    40,
      21,    21,    19,    40,    40,    21,    19,    34,    36,    32,
     954,    33,   956,   957,   958,    40,   903,   904,    89,    27,
      32,    32,    37,    23,    38,    34,    36,    23,   903,   904,
     563,   564,    27,    27,   979,    23,    27,    23,    43,    32,
      32,    26,    23,    21,    23,    32,    19,   580,    38,    38,
      32,    34,   572,   573,   999,    39,   943,    37,    89,    23,
      21,    21,    32,    89,   939,   940,   941,   942,   943,    21,
      89,    19,    34,    32,   607,    38,    23,    23,    36,    36,
      34,    31,   957,   958,    39,    89,  1030,    36,    23,    23,
      23,    23,    34,    32,    23,    23,    37,   984,   985,    30,
      38,    19,  1047,    19,    34,    19,    30,    22,    19,   984,
     985,    37,   987,    89,    89,   635,    39,   637,   638,    32,
      30,    89,    34,   643,    89,   645,    31,    36,    23,    27,
      34,    23,  1076,   653,   654,    42,    36,    34,    19,    38,
     660,   661,    22,    19,    23,  1020,  1021,    31,    37,    19,
      19,    19,    30,    36,    36,    19,    31,    31,  1103,    19,
      22,    38,    89,    26,   684,    38,   686,    23,    27,    36,
      36,    23,    23,    19,    32,    23,    19,    31,    22,    36,
      27,    36,    31,   716,   717,  1129,    23,    40,    38,   722,
      32,   724,    31,    38,    23,    23,    89,    38,    23,    23,
      23,   734,    38,    36,    36,    40,    36,    38,    23,    23,
      37,  1156,    38,    33,    23,    23,    37,    36,    36,    30,
      36,    22,   956,    36,  1030,  1129,  1238,   288,   942,    -1,
      -1,    -1,   765,    50,   767,   283,   283,   497,   283,    -1,
     497,    -1,   284,   283,   288,    -1,    -1,    -1,    -1,    -1,
     283,   283,   286,    -1,  1129,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   286,  1208,    -1,    -1,    -1,    -1,    -1,   789,
     288,    -1,    -1,   793,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   802,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     820,    -1,    -1,    -1,   824,    -1,    -1,   827,   828,    -1,
     830,    -1,   832,    -1,    -1,    -1,    -1,   850,    -1,    -1,
      -1,   854,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   864,    -1,    -1,    -1,    -1,   869,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   892,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   901,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   911,    -1,
     913,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   929,
     930,   931,   932,    -1,    -1,   935,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   974,   975,     3,     4,     5,     6,     7,     8,     9,
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
     220,   221,   222,    -1,   224,     3,     4,     5,     6,     7,
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
     218,   219,   220,   221,    -1,   223,   224,     3,     4,     5,
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
     216,   217,   218,   219,   220,   221,    -1,    -1,   224,     3,
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
     214,   215,   216,   217,   218,   219,   220,   221,    -1,    -1,
     224,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
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
     222,   223,     3,     4,     5,     6,     7,     8,     9,    10,
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
     221,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
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
     213,   214,   215,   216,   217,   218,   219,   220,   221,     3,
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
     218,   219,   220,   221
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     1,     3,    19,    21,    22,    25,    30,    31,    35,
      36,    37,    39,   228,   229,   230,   231,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   291,   292,   293,   294,
     295,   340,   343,    22,    30,    36,    23,    23,    27,    33,
      19,    39,    23,    23,    39,    32,     0,   225,   226,   278,
     279,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
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
     224,   269,   272,   273,   274,   277,   277,   277,   277,   277,
     277,   277,   277,   277,   277,   277,   277,   277,   277,   277,
     277,    22,    23,    23,    37,    38,    37,    19,    34,    27,
      31,    37,    30,    38,    20,    31,    37,   278,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,   271,   272,
     271,   271,   271,   271,   271,   271,   271,   271,     3,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,   274,
      21,   296,    19,    21,    23,    31,    37,    38,   237,   296,
     297,   298,   299,   306,   307,   309,   314,   315,   316,   317,
     318,   319,   321,   323,   324,   325,   326,   327,   328,   329,
     330,   334,    31,   234,   327,   235,   327,    31,   241,   328,
      19,    31,   239,   315,   325,   242,   315,   325,    19,    21,
      31,   247,   297,   298,   299,   314,   321,   324,   328,    27,
     243,   308,   309,   236,   296,    19,    23,    31,   238,   296,
     313,   318,   322,   323,   342,    20,    21,    31,    37,    38,
      40,   232,   301,   302,   303,   304,   305,   306,   341,   233,
     301,   302,   303,   304,   305,   306,   341,   269,   275,   277,
     240,   296,    19,    19,    38,    38,    22,    38,    33,    23,
      23,    37,    19,    39,   272,    26,    39,    40,    26,    32,
      27,    23,    33,   277,   277,   277,   277,   277,   277,   277,
     277,   277,   277,   277,   277,   277,   277,    27,   277,   277,
      27,    39,    27,   277,   277,   277,   277,    39,    26,    27,
      32,   277,   277,   277,    39,    21,    27,   277,   277,   277,
     277,   277,   277,    39,    26,    27,    38,    33,    33,   269,
     277,   277,    36,    38,    36,    40,    38,    21,    21,    34,
      20,    19,    22,    19,    19,    25,    22,    36,    38,    27,
     300,   303,   304,   305,   300,   300,   300,   300,   300,   300,
     300,   300,   300,   300,   300,   300,   300,    22,    10,    11,
      12,    13,    14,    15,    16,    17,    18,   257,   273,   257,
      22,    22,    22,   269,   269,   273,   273,    22,    19,    22,
      37,    32,   222,   223,   248,   264,   276,   290,   249,   263,
     269,   261,   273,    22,    26,    22,    19,    31,    37,    40,
     244,   315,   319,   320,   325,   330,   331,   332,   333,   335,
     336,   337,   273,   273,   273,   273,   268,   269,   273,    24,
      19,    37,    36,    38,    27,   261,    23,    33,    23,    38,
      36,    37,    32,    27,    27,    32,    27,    27,    40,    19,
      32,   277,   277,   277,   277,   277,   277,   277,   277,   277,
     277,   277,   277,   277,   277,   277,   277,    27,   277,   277,
      27,    27,    27,   277,   277,    27,    32,    27,    38,    33,
     275,   275,   277,   277,   277,    27,    33,    27,    39,    27,
      39,    33,    33,   277,   277,   277,   277,   277,   277,   277,
     277,   277,   277,   277,   277,   277,   277,   277,    24,    32,
      21,    23,    19,    21,    43,    27,    21,    32,    33,    30,
      32,    32,    89,    23,    30,    24,   261,    20,    34,   246,
     338,   339,   261,   261,   263,   273,   269,   269,   273,   273,
     273,   273,   269,   257,   269,   273,    89,   258,   273,   258,
      89,    33,    89,   245,   269,   245,    33,    32,    89,    36,
      32,   222,   223,   262,   273,   264,   261,    33,    89,    22,
      22,    38,    30,    30,   261,   261,   261,   261,   261,   261,
     261,   261,   261,   261,   261,   269,   273,   269,   273,    23,
      32,    23,    19,    30,    23,    20,    36,    23,    89,    19,
      23,    23,    27,    36,    89,    33,    43,    23,   277,   277,
     277,   277,   277,   277,   277,   277,    27,   277,   277,    27,
      89,    27,   277,     4,    89,    23,    27,    39,    89,   277,
     277,    89,    27,    27,    27,    23,    33,    39,   277,   277,
     277,   277,   277,   277,   277,   277,   277,   277,   277,     4,
     277,     4,   277,    36,    23,    30,    31,    89,    89,    23,
      27,    30,    33,    20,    30,    32,    40,    38,    36,   261,
     269,   273,   273,   273,   269,   258,   273,    32,   259,   273,
     259,    32,    33,    32,   269,     7,     8,   266,   267,   269,
     270,   271,   272,   273,   276,    33,    30,    32,    31,    31,
     261,   262,    33,    32,    33,    89,    31,   251,   273,   252,
     273,   253,   269,   251,   254,   273,    19,   255,   273,   289,
     256,   269,   251,     7,     8,   260,   270,   273,   268,   268,
     266,   269,   266,   269,    89,    30,    30,    89,    40,    21,
      20,    39,    30,    37,    34,    37,    33,    23,    21,   277,
     277,   277,   277,   277,    37,   277,    37,    39,    34,     4,
     271,   271,     5,     6,    39,    34,    23,    33,   277,    39,
      34,    89,    27,    23,   277,    30,   277,     4,     4,    24,
      89,    19,    21,    33,    33,    23,    38,    23,    39,    38,
      27,    37,    23,   245,   269,   269,   245,   259,    38,   263,
      38,    38,    39,   266,     6,     6,   267,   271,    38,    39,
      32,    22,   261,    38,    39,    33,    32,   252,    30,   254,
     266,   266,    27,    21,    27,    32,    33,    27,    39,    34,
      89,    38,    36,    21,    32,    36,   277,    36,    34,    38,
     271,   271,    34,    38,    38,    19,    34,    38,    39,    34,
     277,    30,    33,    32,    23,    39,    21,    32,    39,    19,
      23,    31,    89,    39,    23,    38,    39,   264,    39,    39,
      89,    39,    89,    30,    39,    89,    38,    39,   255,    30,
      39,    24,    33,    32,    23,    38,    38,    39,    32,    27,
      22,    34,    31,    89,    19,    31,   277,    31,    38,    22,
      38,    22,    38,    22,    34,    34,    38,    32,    33,    39,
      38,    89,    89,    22,    25,    22,    23,    36,    33,    23,
      21,    25,    23,   262,    23,    89,    23,    89,    23,    89,
      23,    33,    39,    89,    38,    37,    21,    21,    22,    27,
      27,    27,    40,    27,    36,    32,    33,    23,    32,   277,
      32,    22,    40,    22,    40,    21,    22,    40,    36,    38,
      21,    34,    38,    33,    26,    23,    36,    33,    32,    89,
      27,    40,    38,    38,    39,    38,   260,    38,    23,    27,
      23,    27,    26,    23,    27,    38,    89,    26,    33,    43,
      39,    19,    40,    27,    89,    23,    27,    21,    23,    89,
      37,    32,   277,    40,    21,    40,    21,    19,    40,    21,
      21,    38,    19,    36,    34,    32,    32,    27,    40,    33,
      37,    32,    23,    36,    34,    38,    33,    34,   250,   265,
     276,   310,   311,   312,    27,    23,    27,    23,    32,    27,
      23,    26,    43,    32,    38,    23,    38,    32,    21,    23,
      39,    34,    37,    89,    19,    89,    32,    23,   277,    21,
      21,    32,    21,    89,    19,    34,    32,    23,    23,    36,
      38,    39,    34,    36,    31,    89,    36,   265,    23,    23,
      23,    23,    34,    32,    23,    23,    30,    37,    89,    34,
      38,    19,    19,    19,    22,    37,    30,    89,    19,    32,
      30,    89,    34,    39,    89,    36,    31,    42,    23,    27,
      34,    36,    23,    34,    19,    38,    22,    19,    23,    31,
      37,    19,    19,    30,    19,    36,    89,    36,    31,    38,
      19,    38,    36,    31,    36,    19,    22,    27,    23,    23,
      32,    23,    19,    23,    19,    31,    36,    40,    38,    36,
      22,    32,    31,    38,    31,    23,    27,    23,    23,    89,
      38,    23,    23,    23,    38,    40,    36,    36,    26,    38,
      36,    38,    23,    23,    37,    33,    23,    23,    36,    36,
      30,    36,    36,    37,    22
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
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
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
    while (YYID (0))
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
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, const YYSTYPE * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    const YYSTYPE * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, const YYSTYPE * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    const YYSTYPE * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, 
		   int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule
		   )
    YYSTYPE *yyvsp;
    
		   int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
      YYSIZE_T yyn = 0;
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
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
      int yychecklim = YYLAST - yyn + 1;
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
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
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
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  YYUSE (yyvaluep);

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
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */






/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

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
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

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
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


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
	yytype_int16 *yyss1 = yyss;
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

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

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

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
#line 99 "lscp.y"
    { return LSCP_DONE; }
    break;

  case 5:
#line 100 "lscp.y"
    { return LSCP_DONE; }
    break;

  case 6:
#line 101 "lscp.y"
    { LSCPSERVER->AnswerClient((yyvsp[(1) - (1)].String)); return LSCP_DONE; }
    break;

  case 7:
#line 102 "lscp.y"
    { LSCPSERVER->AnswerClient("ERR:0:Unknown command.\r\n"); RESTART; return LSCP_SYNTAX_ERROR; }
    break;

  case 13:
#line 112 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddChannel(); }
    break;

  case 14:
#line 113 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                       }
    break;

  case 15:
#line 114 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                       }
    break;

  case 16:
#line 115 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                       }
    break;

  case 17:
#line 116 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                       }
    break;

  case 18:
#line 117 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                       }
    break;

  case 19:
#line 118 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                       }
    break;

  case 20:
#line 119 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                       }
    break;

  case 21:
#line 120 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                       }
    break;

  case 22:
#line 122 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                }
    break;

  case 23:
#line 123 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                }
    break;

  case 24:
#line 124 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                }
    break;

  case 25:
#line 125 "lscp.y"
    { (yyval.String) = LSCPSERVER->QueryDatabase((yyvsp[(3) - (3)].String));                     }
    break;

  case 26:
#line 126 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                }
    break;

  case 27:
#line 127 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                }
    break;

  case 28:
#line 128 "lscp.y"
    { (yyval.String) = LSCPSERVER->ResetSampler();                        }
    break;

  case 29:
#line 129 "lscp.y"
    { LSCPSERVER->AnswerClient("Bye!\r\n"); return LSCP_QUIT; }
    break;

  case 30:
#line 132 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_channel_count);     }
    break;

  case 31:
#line 133 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_voice_count);       }
    break;

  case 32:
#line 134 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_stream_count);      }
    break;

  case 33:
#line 135 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_buffer_fill);       }
    break;

  case 34:
#line 136 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_channel_info);      }
    break;

  case 35:
#line 137 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_misc);              }
    break;

  case 36:
#line 138 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_total_voice_count); }
    break;

  case 37:
#line 141 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_channel_count);     }
    break;

  case 38:
#line 142 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_voice_count);       }
    break;

  case 39:
#line 143 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_stream_count);      }
    break;

  case 40:
#line 144 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_buffer_fill);       }
    break;

  case 41:
#line 145 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_channel_info);      }
    break;

  case 42:
#line 146 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_misc);              }
    break;

  case 43:
#line 147 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_total_voice_count); }
    break;

  case 44:
#line 150 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping((yyvsp[(3) - (15)].Number),(yyvsp[(5) - (15)].Number),(yyvsp[(7) - (15)].Number),(yyvsp[(9) - (15)].String),(yyvsp[(11) - (15)].String),(yyvsp[(13) - (15)].Number),(yyvsp[(15) - (15)].Dotnum),MidiInstrumentMapper::VOID,""); }
    break;

  case 45:
#line 151 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping((yyvsp[(3) - (17)].Number),(yyvsp[(5) - (17)].Number),(yyvsp[(7) - (17)].Number),(yyvsp[(9) - (17)].String),(yyvsp[(11) - (17)].String),(yyvsp[(13) - (17)].Number),(yyvsp[(15) - (17)].Dotnum),(yyvsp[(17) - (17)].LoadMode),""); }
    break;

  case 46:
#line 152 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping((yyvsp[(3) - (17)].Number),(yyvsp[(5) - (17)].Number),(yyvsp[(7) - (17)].Number),(yyvsp[(9) - (17)].String),(yyvsp[(11) - (17)].String),(yyvsp[(13) - (17)].Number),(yyvsp[(15) - (17)].Dotnum),MidiInstrumentMapper::VOID,(yyvsp[(17) - (17)].String)); }
    break;

  case 47:
#line 153 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping((yyvsp[(3) - (19)].Number),(yyvsp[(5) - (19)].Number),(yyvsp[(7) - (19)].Number),(yyvsp[(9) - (19)].String),(yyvsp[(11) - (19)].String),(yyvsp[(13) - (19)].Number),(yyvsp[(15) - (19)].Dotnum),(yyvsp[(17) - (19)].LoadMode),(yyvsp[(19) - (19)].String)); }
    break;

  case 48:
#line 156 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveMIDIInstrumentMapping((yyvsp[(3) - (7)].Number),(yyvsp[(5) - (7)].Number),(yyvsp[(7) - (7)].Number)); }
    break;

  case 49:
#line 159 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveChannel((yyvsp[(3) - (3)].Number)); }
    break;

  case 50:
#line 162 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAvailableEngines();                          }
    break;

  case 51:
#line 163 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAvailableMidiInputDrivers();                 }
    break;

  case 52:
#line 164 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDriverInfo((yyvsp[(5) - (5)].String));                     }
    break;

  case 53:
#line 165 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDriverParameterInfo((yyvsp[(5) - (7)].String), (yyvsp[(7) - (7)].String));        }
    break;

  case 54:
#line 166 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDriverParameterInfo((yyvsp[(5) - (9)].String), (yyvsp[(7) - (9)].String), (yyvsp[(9) - (9)].KeyValList));    }
    break;

  case 55:
#line 167 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAvailableAudioOutputDrivers();               }
    break;

  case 56:
#line 168 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDriverInfo((yyvsp[(5) - (5)].String));                   }
    break;

  case 57:
#line 169 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDriverParameterInfo((yyvsp[(5) - (7)].String), (yyvsp[(7) - (7)].String));      }
    break;

  case 58:
#line 170 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDriverParameterInfo((yyvsp[(5) - (9)].String), (yyvsp[(7) - (9)].String), (yyvsp[(9) - (9)].KeyValList));  }
    break;

  case 59:
#line 171 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDeviceCount();                    }
    break;

  case 60:
#line 172 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDeviceCount();                      }
    break;

  case 61:
#line 173 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDeviceInfo((yyvsp[(5) - (5)].Number));                   }
    break;

  case 62:
#line 174 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDeviceInfo((yyvsp[(5) - (5)].Number));                     }
    break;

  case 63:
#line 175 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputPortInfo((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number));                   }
    break;

  case 64:
#line 176 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputPortParameterInfo((yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].Number), (yyvsp[(9) - (9)].String));      }
    break;

  case 65:
#line 177 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputChannelInfo((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number));              }
    break;

  case 66:
#line 178 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputChannelParameterInfo((yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].Number), (yyvsp[(9) - (9)].String)); }
    break;

  case 67:
#line 179 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetChannels();                                  }
    break;

  case 68:
#line 180 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetChannelInfo((yyvsp[(5) - (5)].Number));                             }
    break;

  case 69:
#line 181 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetBufferFill((yyvsp[(5) - (7)].FillResponse), (yyvsp[(7) - (7)].Number));                          }
    break;

  case 70:
#line 182 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetStreamCount((yyvsp[(5) - (5)].Number));                             }
    break;

  case 71:
#line 183 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetVoiceCount((yyvsp[(5) - (5)].Number));                              }
    break;

  case 72:
#line 184 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetEngineInfo((yyvsp[(5) - (5)].String));                              }
    break;

  case 73:
#line 185 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetServerInfo();                                }
    break;

  case 74:
#line 186 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetTotalVoiceCount();                                }
    break;

  case 75:
#line 187 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetTotalVoiceCountMax();                        }
    break;

  case 76:
#line 188 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiIstrumentMappings();                     }
    break;

  case 77:
#line 189 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInstrumentMapping((yyvsp[(5) - (9)].Number),(yyvsp[(7) - (9)].Number),(yyvsp[(9) - (9)].Number));             }
    break;

  case 78:
#line 192 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputDeviceParameter((yyvsp[(3) - (7)].Number), (yyvsp[(5) - (7)].String), (yyvsp[(7) - (7)].String));      }
    break;

  case 79:
#line 193 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputChannelParameter((yyvsp[(3) - (9)].Number), (yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].String), (yyvsp[(9) - (9)].String)); }
    break;

  case 80:
#line 194 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMidiInputDeviceParameter((yyvsp[(3) - (7)].Number), (yyvsp[(5) - (7)].String), (yyvsp[(7) - (7)].String));        }
    break;

  case 81:
#line 195 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMidiInputPortParameter((yyvsp[(3) - (9)].Number), (yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].String), (yyvsp[(9) - (9)].String));      }
    break;

  case 82:
#line 196 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                         }
    break;

  case 83:
#line 197 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetEcho((yyparse_param_t*) yyparse_param, (yyvsp[(3) - (3)].Dotnum));  }
    break;

  case 84:
#line 200 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateAudioOutputDevice((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].KeyValList)); }
    break;

  case 85:
#line 201 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateAudioOutputDevice((yyvsp[(3) - (3)].String));    }
    break;

  case 86:
#line 202 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateMidiInputDevice((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].KeyValList));   }
    break;

  case 87:
#line 203 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateMidiInputDevice((yyvsp[(3) - (3)].String));      }
    break;

  case 88:
#line 206 "lscp.y"
    { (yyval.String) = LSCPSERVER->ResetChannel((yyvsp[(3) - (3)].Number)); }
    break;

  case 89:
#line 209 "lscp.y"
    { (yyval.String) = LSCPSERVER->ClearMidiInstrumentMappings(); }
    break;

  case 90:
#line 212 "lscp.y"
    { (yyval.String) = LSCPSERVER->DestroyAudioOutputDevice((yyvsp[(3) - (3)].Number)); }
    break;

  case 91:
#line 213 "lscp.y"
    { (yyval.String) = LSCPSERVER->DestroyMidiInputDevice((yyvsp[(3) - (3)].Number));   }
    break;

  case 92:
#line 216 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String); }
    break;

  case 93:
#line 217 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String); }
    break;

  case 94:
#line 220 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputDevice((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));      }
    break;

  case 95:
#line 221 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputChannel((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number), (yyvsp[(3) - (7)].Number)); }
    break;

  case 96:
#line 222 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputType((yyvsp[(5) - (5)].String), (yyvsp[(3) - (5)].Number));        }
    break;

  case 97:
#line 223 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInput((yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].Number), (yyvsp[(9) - (9)].Number), (yyvsp[(3) - (9)].Number));      }
    break;

  case 98:
#line 224 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputDevice((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));        }
    break;

  case 99:
#line 225 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputPort((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));          }
    break;

  case 100:
#line 226 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputChannel((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));       }
    break;

  case 101:
#line 227 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputType((yyvsp[(5) - (5)].String), (yyvsp[(3) - (5)].Number));          }
    break;

  case 102:
#line 228 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetVolume((yyvsp[(5) - (5)].Dotnum), (yyvsp[(3) - (5)].Number));                 }
    break;

  case 103:
#line 229 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMute((yyvsp[(5) - (5)].Dotnum), (yyvsp[(3) - (5)].Number));            }
    break;

  case 104:
#line 230 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelSolo((yyvsp[(5) - (5)].Dotnum), (yyvsp[(3) - (5)].Number));            }
    break;

  case 105:
#line 233 "lscp.y"
    { (yyval.KeyValList)[(yyvsp[(1) - (3)].String)] = (yyvsp[(3) - (3)].String);          }
    break;

  case 106:
#line 234 "lscp.y"
    { (yyval.KeyValList) = (yyvsp[(1) - (5)].KeyValList); (yyval.KeyValList)[(yyvsp[(3) - (5)].String)] = (yyvsp[(5) - (5)].String); }
    break;

  case 107:
#line 237 "lscp.y"
    { (yyval.FillResponse) = fill_response_bytes;      }
    break;

  case 108:
#line 238 "lscp.y"
    { (yyval.FillResponse) = fill_response_percentage; }
    break;

  case 109:
#line 241 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDevices();           }
    break;

  case 110:
#line 242 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDevices();             }
    break;

  case 111:
#line 243 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListChannels();                    }
    break;

  case 112:
#line 244 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableEngines();            }
    break;

  case 113:
#line 245 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableMidiInputDrivers();   }
    break;

  case 114:
#line 246 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableAudioOutputDrivers(); }
    break;

  case 115:
#line 247 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListMidiInstrumentMappings();      }
    break;

  case 116:
#line 250 "lscp.y"
    { (yyval.String) = LSCPSERVER->LoadInstrument((yyvsp[(1) - (5)].String), (yyvsp[(3) - (5)].Number), (yyvsp[(5) - (5)].Number));       }
    break;

  case 117:
#line 251 "lscp.y"
    { (yyval.String) = LSCPSERVER->LoadInstrument((yyvsp[(3) - (7)].String), (yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number), true); }
    break;

  case 118:
#line 254 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetEngineType((yyvsp[(1) - (3)].String), (yyvsp[(3) - (3)].Number)); }
    break;

  case 119:
#line 257 "lscp.y"
    { (yyval.LoadMode) = MidiInstrumentMapper::ON_DEMAND;      }
    break;

  case 120:
#line 258 "lscp.y"
    { (yyval.LoadMode) = MidiInstrumentMapper::ON_DEMAND_HOLD; }
    break;

  case 121:
#line 259 "lscp.y"
    { (yyval.LoadMode) = MidiInstrumentMapper::PERSISTENT;     }
    break;

  case 127:
#line 275 "lscp.y"
    { (yyval.Number) = 16; }
    break;

  case 133:
#line 291 "lscp.y"
    { (yyval.Dotnum) = (yyvsp[(1) - (1)].Number); }
    break;

  case 140:
#line 310 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (3)].String) + "," + (yyvsp[(3) - (3)].String); }
    break;

  case 143:
#line 315 "lscp.y"
    { std::stringstream ss; ss << "\'" << (yyvsp[(1) - (1)].Number) << "\'"; (yyval.String) = ss.str(); }
    break;

  case 144:
#line 316 "lscp.y"
    { std::stringstream ss; ss << "\'" << (yyvsp[(1) - (1)].Dotnum) << "\'"; (yyval.String) = ss.str(); }
    break;

  case 145:
#line 324 "lscp.y"
    { (yyval.Dotnum) = (yyvsp[(1) - (1)].Number); }
    break;

  case 146:
#line 325 "lscp.y"
    { (yyval.Dotnum) = -1; }
    break;

  case 147:
#line 328 "lscp.y"
    { std::string s; s = (yyvsp[(1) - (1)].Char); (yyval.String) = s; }
    break;

  case 148:
#line 329 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + (yyvsp[(2) - (2)].Char);                  }
    break;

  case 149:
#line 332 "lscp.y"
    { (yyval.Dotnum) = atof(String((yyvsp[(1) - (3)].String) + "." + (yyvsp[(3) - (3)].String)).c_str());                         }
    break;

  case 150:
#line 333 "lscp.y"
    { String s = "+"; s += (yyvsp[(2) - (4)].String); s += "."; s += (yyvsp[(4) - (4)].String); (yyval.Dotnum) = atof(s.c_str()); }
    break;

  case 151:
#line 334 "lscp.y"
    { (yyval.Dotnum) = atof(String("-" + (yyvsp[(2) - (4)].String) + "." + (yyvsp[(4) - (4)].String)).c_str());                   }
    break;

  case 152:
#line 338 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (1)].Char);      }
    break;

  case 153:
#line 339 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + (yyvsp[(2) - (2)].Char); }
    break;

  case 154:
#line 342 "lscp.y"
    { (yyval.Char) = '0'; }
    break;

  case 155:
#line 343 "lscp.y"
    { (yyval.Char) = '1'; }
    break;

  case 156:
#line 344 "lscp.y"
    { (yyval.Char) = '2'; }
    break;

  case 157:
#line 345 "lscp.y"
    { (yyval.Char) = '3'; }
    break;

  case 158:
#line 346 "lscp.y"
    { (yyval.Char) = '4'; }
    break;

  case 159:
#line 347 "lscp.y"
    { (yyval.Char) = '5'; }
    break;

  case 160:
#line 348 "lscp.y"
    { (yyval.Char) = '6'; }
    break;

  case 161:
#line 349 "lscp.y"
    { (yyval.Char) = '7'; }
    break;

  case 162:
#line 350 "lscp.y"
    { (yyval.Char) = '8'; }
    break;

  case 163:
#line 351 "lscp.y"
    { (yyval.Char) = '9'; }
    break;

  case 164:
#line 354 "lscp.y"
    { (yyval.Number) = atoi(String(1, (yyvsp[(1) - (1)].Char)).c_str());      }
    break;

  case 165:
#line 355 "lscp.y"
    { (yyval.Number) = atoi(String(String("1") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 166:
#line 356 "lscp.y"
    { (yyval.Number) = atoi(String(String("2") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 167:
#line 357 "lscp.y"
    { (yyval.Number) = atoi(String(String("3") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 168:
#line 358 "lscp.y"
    { (yyval.Number) = atoi(String(String("4") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 169:
#line 359 "lscp.y"
    { (yyval.Number) = atoi(String(String("5") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 170:
#line 360 "lscp.y"
    { (yyval.Number) = atoi(String(String("6") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 171:
#line 361 "lscp.y"
    { (yyval.Number) = atoi(String(String("7") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 172:
#line 362 "lscp.y"
    { (yyval.Number) = atoi(String(String("8") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 173:
#line 363 "lscp.y"
    { (yyval.Number) = atoi(String(String("9") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 174:
#line 365 "lscp.y"
    { (yyval.Char) = 'A'; }
    break;

  case 175:
#line 365 "lscp.y"
    { (yyval.Char) = 'B'; }
    break;

  case 176:
#line 365 "lscp.y"
    { (yyval.Char) = 'C'; }
    break;

  case 177:
#line 365 "lscp.y"
    { (yyval.Char) = 'D'; }
    break;

  case 178:
#line 365 "lscp.y"
    { (yyval.Char) = 'E'; }
    break;

  case 179:
#line 365 "lscp.y"
    { (yyval.Char) = 'F'; }
    break;

  case 180:
#line 365 "lscp.y"
    { (yyval.Char) = 'G'; }
    break;

  case 181:
#line 365 "lscp.y"
    { (yyval.Char) = 'H'; }
    break;

  case 182:
#line 365 "lscp.y"
    { (yyval.Char) = 'I'; }
    break;

  case 183:
#line 365 "lscp.y"
    { (yyval.Char) = 'J'; }
    break;

  case 184:
#line 365 "lscp.y"
    { (yyval.Char) = 'K'; }
    break;

  case 185:
#line 365 "lscp.y"
    { (yyval.Char) = 'L'; }
    break;

  case 186:
#line 365 "lscp.y"
    { (yyval.Char) = 'M'; }
    break;

  case 187:
#line 365 "lscp.y"
    { (yyval.Char) = 'N'; }
    break;

  case 188:
#line 365 "lscp.y"
    { (yyval.Char) = 'O'; }
    break;

  case 189:
#line 365 "lscp.y"
    { (yyval.Char) = 'P'; }
    break;

  case 190:
#line 365 "lscp.y"
    { (yyval.Char) = 'Q'; }
    break;

  case 191:
#line 365 "lscp.y"
    { (yyval.Char) = 'R'; }
    break;

  case 192:
#line 365 "lscp.y"
    { (yyval.Char) = 'S'; }
    break;

  case 193:
#line 365 "lscp.y"
    { (yyval.Char) = 'T'; }
    break;

  case 194:
#line 365 "lscp.y"
    { (yyval.Char) = 'U'; }
    break;

  case 195:
#line 365 "lscp.y"
    { (yyval.Char) = 'V'; }
    break;

  case 196:
#line 365 "lscp.y"
    { (yyval.Char) = 'W'; }
    break;

  case 197:
#line 365 "lscp.y"
    { (yyval.Char) = 'X'; }
    break;

  case 198:
#line 365 "lscp.y"
    { (yyval.Char) = 'Y'; }
    break;

  case 199:
#line 365 "lscp.y"
    { (yyval.Char) = 'Z'; }
    break;

  case 200:
#line 366 "lscp.y"
    { (yyval.Char) = 'a'; }
    break;

  case 201:
#line 366 "lscp.y"
    { (yyval.Char) = 'b'; }
    break;

  case 202:
#line 366 "lscp.y"
    { (yyval.Char) = 'c'; }
    break;

  case 203:
#line 366 "lscp.y"
    { (yyval.Char) = 'd'; }
    break;

  case 204:
#line 366 "lscp.y"
    { (yyval.Char) = 'e'; }
    break;

  case 205:
#line 366 "lscp.y"
    { (yyval.Char) = 'f'; }
    break;

  case 206:
#line 366 "lscp.y"
    { (yyval.Char) = 'g'; }
    break;

  case 207:
#line 366 "lscp.y"
    { (yyval.Char) = 'h'; }
    break;

  case 208:
#line 366 "lscp.y"
    { (yyval.Char) = 'i'; }
    break;

  case 209:
#line 366 "lscp.y"
    { (yyval.Char) = 'j'; }
    break;

  case 210:
#line 366 "lscp.y"
    { (yyval.Char) = 'k'; }
    break;

  case 211:
#line 366 "lscp.y"
    { (yyval.Char) = 'l'; }
    break;

  case 212:
#line 366 "lscp.y"
    { (yyval.Char) = 'm'; }
    break;

  case 213:
#line 366 "lscp.y"
    { (yyval.Char) = 'n'; }
    break;

  case 214:
#line 366 "lscp.y"
    { (yyval.Char) = 'o'; }
    break;

  case 215:
#line 366 "lscp.y"
    { (yyval.Char) = 'p'; }
    break;

  case 216:
#line 366 "lscp.y"
    { (yyval.Char) = 'q'; }
    break;

  case 217:
#line 366 "lscp.y"
    { (yyval.Char) = 'r'; }
    break;

  case 218:
#line 366 "lscp.y"
    { (yyval.Char) = 's'; }
    break;

  case 219:
#line 366 "lscp.y"
    { (yyval.Char) = 't'; }
    break;

  case 220:
#line 366 "lscp.y"
    { (yyval.Char) = 'u'; }
    break;

  case 221:
#line 366 "lscp.y"
    { (yyval.Char) = 'v'; }
    break;

  case 222:
#line 366 "lscp.y"
    { (yyval.Char) = 'w'; }
    break;

  case 223:
#line 366 "lscp.y"
    { (yyval.Char) = 'x'; }
    break;

  case 224:
#line 366 "lscp.y"
    { (yyval.Char) = 'y'; }
    break;

  case 225:
#line 366 "lscp.y"
    { (yyval.Char) = 'z'; }
    break;

  case 226:
#line 367 "lscp.y"
    { (yyval.Char) = '0'; }
    break;

  case 227:
#line 367 "lscp.y"
    { (yyval.Char) = '1'; }
    break;

  case 228:
#line 367 "lscp.y"
    { (yyval.Char) = '2'; }
    break;

  case 229:
#line 367 "lscp.y"
    { (yyval.Char) = '3'; }
    break;

  case 230:
#line 367 "lscp.y"
    { (yyval.Char) = '4'; }
    break;

  case 231:
#line 367 "lscp.y"
    { (yyval.Char) = '5'; }
    break;

  case 232:
#line 367 "lscp.y"
    { (yyval.Char) = '6'; }
    break;

  case 233:
#line 367 "lscp.y"
    { (yyval.Char) = '7'; }
    break;

  case 234:
#line 367 "lscp.y"
    { (yyval.Char) = '8'; }
    break;

  case 235:
#line 367 "lscp.y"
    { (yyval.Char) = '9'; }
    break;

  case 236:
#line 368 "lscp.y"
    { (yyval.Char) = '!'; }
    break;

  case 237:
#line 368 "lscp.y"
    { (yyval.Char) = '#'; }
    break;

  case 238:
#line 368 "lscp.y"
    { (yyval.Char) = '$'; }
    break;

  case 239:
#line 368 "lscp.y"
    { (yyval.Char) = '%'; }
    break;

  case 240:
#line 368 "lscp.y"
    { (yyval.Char) = '&'; }
    break;

  case 241:
#line 368 "lscp.y"
    { (yyval.Char) = '('; }
    break;

  case 242:
#line 368 "lscp.y"
    { (yyval.Char) = ')'; }
    break;

  case 243:
#line 368 "lscp.y"
    { (yyval.Char) = '*'; }
    break;

  case 244:
#line 368 "lscp.y"
    { (yyval.Char) = '+'; }
    break;

  case 245:
#line 368 "lscp.y"
    { (yyval.Char) = '-'; }
    break;

  case 246:
#line 368 "lscp.y"
    { (yyval.Char) = '.'; }
    break;

  case 247:
#line 368 "lscp.y"
    { (yyval.Char) = ','; }
    break;

  case 248:
#line 368 "lscp.y"
    { (yyval.Char) = '/'; }
    break;

  case 249:
#line 369 "lscp.y"
    { (yyval.Char) = ':'; }
    break;

  case 250:
#line 369 "lscp.y"
    { (yyval.Char) = ';'; }
    break;

  case 251:
#line 369 "lscp.y"
    { (yyval.Char) = '<'; }
    break;

  case 252:
#line 369 "lscp.y"
    { (yyval.Char) = '='; }
    break;

  case 253:
#line 369 "lscp.y"
    { (yyval.Char) = '>'; }
    break;

  case 254:
#line 369 "lscp.y"
    { (yyval.Char) = '?'; }
    break;

  case 255:
#line 369 "lscp.y"
    { (yyval.Char) = '@'; }
    break;

  case 256:
#line 370 "lscp.y"
    { (yyval.Char) = '['; }
    break;

  case 257:
#line 370 "lscp.y"
    { (yyval.Char) = '\\'; }
    break;

  case 258:
#line 370 "lscp.y"
    { (yyval.Char) = ']'; }
    break;

  case 259:
#line 370 "lscp.y"
    { (yyval.Char) = '^'; }
    break;

  case 260:
#line 370 "lscp.y"
    { (yyval.Char) = '_'; }
    break;

  case 261:
#line 371 "lscp.y"
    { (yyval.Char) = '{'; }
    break;

  case 262:
#line 371 "lscp.y"
    { (yyval.Char) = '|'; }
    break;

  case 263:
#line 371 "lscp.y"
    { (yyval.Char) = '}'; }
    break;

  case 264:
#line 371 "lscp.y"
    { (yyval.Char) = '~'; }
    break;

  case 265:
#line 372 "lscp.y"
    { (yyval.Char) = '\200'; }
    break;

  case 266:
#line 372 "lscp.y"
    { (yyval.Char) = '\201'; }
    break;

  case 267:
#line 372 "lscp.y"
    { (yyval.Char) = '\202'; }
    break;

  case 268:
#line 373 "lscp.y"
    { (yyval.Char) = '\203'; }
    break;

  case 269:
#line 373 "lscp.y"
    { (yyval.Char) = '\204'; }
    break;

  case 270:
#line 373 "lscp.y"
    { (yyval.Char) = '\205'; }
    break;

  case 271:
#line 374 "lscp.y"
    { (yyval.Char) = '\206'; }
    break;

  case 272:
#line 374 "lscp.y"
    { (yyval.Char) = '\207'; }
    break;

  case 273:
#line 374 "lscp.y"
    { (yyval.Char) = '\210'; }
    break;

  case 274:
#line 375 "lscp.y"
    { (yyval.Char) = '\211'; }
    break;

  case 275:
#line 375 "lscp.y"
    { (yyval.Char) = '\212'; }
    break;

  case 276:
#line 375 "lscp.y"
    { (yyval.Char) = '\213'; }
    break;

  case 277:
#line 376 "lscp.y"
    { (yyval.Char) = '\214'; }
    break;

  case 278:
#line 376 "lscp.y"
    { (yyval.Char) = '\215'; }
    break;

  case 279:
#line 376 "lscp.y"
    { (yyval.Char) = '\216'; }
    break;

  case 280:
#line 377 "lscp.y"
    { (yyval.Char) = '\217'; }
    break;

  case 281:
#line 377 "lscp.y"
    { (yyval.Char) = '\220'; }
    break;

  case 282:
#line 377 "lscp.y"
    { (yyval.Char) = '\221'; }
    break;

  case 283:
#line 378 "lscp.y"
    { (yyval.Char) = '\222'; }
    break;

  case 284:
#line 378 "lscp.y"
    { (yyval.Char) = '\223'; }
    break;

  case 285:
#line 378 "lscp.y"
    { (yyval.Char) = '\224'; }
    break;

  case 286:
#line 379 "lscp.y"
    { (yyval.Char) = '\225'; }
    break;

  case 287:
#line 379 "lscp.y"
    { (yyval.Char) = '\226'; }
    break;

  case 288:
#line 379 "lscp.y"
    { (yyval.Char) = '\227'; }
    break;

  case 289:
#line 380 "lscp.y"
    { (yyval.Char) = '\230'; }
    break;

  case 290:
#line 380 "lscp.y"
    { (yyval.Char) = '\231'; }
    break;

  case 291:
#line 380 "lscp.y"
    { (yyval.Char) = '\232'; }
    break;

  case 292:
#line 381 "lscp.y"
    { (yyval.Char) = '\233'; }
    break;

  case 293:
#line 381 "lscp.y"
    { (yyval.Char) = '\234'; }
    break;

  case 294:
#line 381 "lscp.y"
    { (yyval.Char) = '\235'; }
    break;

  case 295:
#line 382 "lscp.y"
    { (yyval.Char) = '\236'; }
    break;

  case 296:
#line 382 "lscp.y"
    { (yyval.Char) = '\237'; }
    break;

  case 297:
#line 382 "lscp.y"
    { (yyval.Char) = '\240'; }
    break;

  case 298:
#line 383 "lscp.y"
    { (yyval.Char) = '\241'; }
    break;

  case 299:
#line 383 "lscp.y"
    { (yyval.Char) = '\242'; }
    break;

  case 300:
#line 383 "lscp.y"
    { (yyval.Char) = '\243'; }
    break;

  case 301:
#line 384 "lscp.y"
    { (yyval.Char) = '\244'; }
    break;

  case 302:
#line 384 "lscp.y"
    { (yyval.Char) = '\245'; }
    break;

  case 303:
#line 384 "lscp.y"
    { (yyval.Char) = '\246'; }
    break;

  case 304:
#line 385 "lscp.y"
    { (yyval.Char) = '\247'; }
    break;

  case 305:
#line 385 "lscp.y"
    { (yyval.Char) = '\250'; }
    break;

  case 306:
#line 385 "lscp.y"
    { (yyval.Char) = '\251'; }
    break;

  case 307:
#line 386 "lscp.y"
    { (yyval.Char) = '\252'; }
    break;

  case 308:
#line 386 "lscp.y"
    { (yyval.Char) = '\253'; }
    break;

  case 309:
#line 386 "lscp.y"
    { (yyval.Char) = '\254'; }
    break;

  case 310:
#line 387 "lscp.y"
    { (yyval.Char) = '\255'; }
    break;

  case 311:
#line 387 "lscp.y"
    { (yyval.Char) = '\256'; }
    break;

  case 312:
#line 387 "lscp.y"
    { (yyval.Char) = '\257'; }
    break;

  case 313:
#line 388 "lscp.y"
    { (yyval.Char) = '\260'; }
    break;

  case 314:
#line 388 "lscp.y"
    { (yyval.Char) = '\261'; }
    break;

  case 315:
#line 388 "lscp.y"
    { (yyval.Char) = '\262'; }
    break;

  case 316:
#line 389 "lscp.y"
    { (yyval.Char) = '\263'; }
    break;

  case 317:
#line 389 "lscp.y"
    { (yyval.Char) = '\264'; }
    break;

  case 318:
#line 389 "lscp.y"
    { (yyval.Char) = '\265'; }
    break;

  case 319:
#line 390 "lscp.y"
    { (yyval.Char) = '\266'; }
    break;

  case 320:
#line 390 "lscp.y"
    { (yyval.Char) = '\267'; }
    break;

  case 321:
#line 390 "lscp.y"
    { (yyval.Char) = '\270'; }
    break;

  case 322:
#line 391 "lscp.y"
    { (yyval.Char) = '\271'; }
    break;

  case 323:
#line 391 "lscp.y"
    { (yyval.Char) = '\272'; }
    break;

  case 324:
#line 391 "lscp.y"
    { (yyval.Char) = '\273'; }
    break;

  case 325:
#line 392 "lscp.y"
    { (yyval.Char) = '\274'; }
    break;

  case 326:
#line 392 "lscp.y"
    { (yyval.Char) = '\275'; }
    break;

  case 327:
#line 392 "lscp.y"
    { (yyval.Char) = '\276'; }
    break;

  case 328:
#line 393 "lscp.y"
    { (yyval.Char) = '\277'; }
    break;

  case 329:
#line 393 "lscp.y"
    { (yyval.Char) = '\300'; }
    break;

  case 330:
#line 393 "lscp.y"
    { (yyval.Char) = '\301'; }
    break;

  case 331:
#line 394 "lscp.y"
    { (yyval.Char) = '\302'; }
    break;

  case 332:
#line 394 "lscp.y"
    { (yyval.Char) = '\303'; }
    break;

  case 333:
#line 394 "lscp.y"
    { (yyval.Char) = '\304'; }
    break;

  case 334:
#line 395 "lscp.y"
    { (yyval.Char) = '\305'; }
    break;

  case 335:
#line 395 "lscp.y"
    { (yyval.Char) = '\306'; }
    break;

  case 336:
#line 395 "lscp.y"
    { (yyval.Char) = '\307'; }
    break;

  case 337:
#line 396 "lscp.y"
    { (yyval.Char) = '\310'; }
    break;

  case 338:
#line 396 "lscp.y"
    { (yyval.Char) = '\311'; }
    break;

  case 339:
#line 396 "lscp.y"
    { (yyval.Char) = '\312'; }
    break;

  case 340:
#line 397 "lscp.y"
    { (yyval.Char) = '\313'; }
    break;

  case 341:
#line 397 "lscp.y"
    { (yyval.Char) = '\314'; }
    break;

  case 342:
#line 397 "lscp.y"
    { (yyval.Char) = '\315'; }
    break;

  case 343:
#line 398 "lscp.y"
    { (yyval.Char) = '\316'; }
    break;

  case 344:
#line 398 "lscp.y"
    { (yyval.Char) = '\317'; }
    break;

  case 345:
#line 398 "lscp.y"
    { (yyval.Char) = '\320'; }
    break;

  case 346:
#line 399 "lscp.y"
    { (yyval.Char) = '\321'; }
    break;

  case 347:
#line 399 "lscp.y"
    { (yyval.Char) = '\322'; }
    break;

  case 348:
#line 399 "lscp.y"
    { (yyval.Char) = '\323'; }
    break;

  case 349:
#line 400 "lscp.y"
    { (yyval.Char) = '\324'; }
    break;

  case 350:
#line 400 "lscp.y"
    { (yyval.Char) = '\325'; }
    break;

  case 351:
#line 400 "lscp.y"
    { (yyval.Char) = '\326'; }
    break;

  case 352:
#line 401 "lscp.y"
    { (yyval.Char) = '\327'; }
    break;

  case 353:
#line 401 "lscp.y"
    { (yyval.Char) = '\330'; }
    break;

  case 354:
#line 401 "lscp.y"
    { (yyval.Char) = '\331'; }
    break;

  case 355:
#line 402 "lscp.y"
    { (yyval.Char) = '\332'; }
    break;

  case 356:
#line 402 "lscp.y"
    { (yyval.Char) = '\333'; }
    break;

  case 357:
#line 402 "lscp.y"
    { (yyval.Char) = '\334'; }
    break;

  case 358:
#line 403 "lscp.y"
    { (yyval.Char) = '\335'; }
    break;

  case 359:
#line 403 "lscp.y"
    { (yyval.Char) = '\336'; }
    break;

  case 360:
#line 403 "lscp.y"
    { (yyval.Char) = '\337'; }
    break;

  case 361:
#line 404 "lscp.y"
    { (yyval.Char) = '\340'; }
    break;

  case 362:
#line 404 "lscp.y"
    { (yyval.Char) = '\341'; }
    break;

  case 363:
#line 404 "lscp.y"
    { (yyval.Char) = '\342'; }
    break;

  case 364:
#line 405 "lscp.y"
    { (yyval.Char) = '\343'; }
    break;

  case 365:
#line 405 "lscp.y"
    { (yyval.Char) = '\344'; }
    break;

  case 366:
#line 405 "lscp.y"
    { (yyval.Char) = '\345'; }
    break;

  case 367:
#line 406 "lscp.y"
    { (yyval.Char) = '\346'; }
    break;

  case 368:
#line 406 "lscp.y"
    { (yyval.Char) = '\347'; }
    break;

  case 369:
#line 406 "lscp.y"
    { (yyval.Char) = '\350'; }
    break;

  case 370:
#line 407 "lscp.y"
    { (yyval.Char) = '\351'; }
    break;

  case 371:
#line 407 "lscp.y"
    { (yyval.Char) = '\352'; }
    break;

  case 372:
#line 407 "lscp.y"
    { (yyval.Char) = '\353'; }
    break;

  case 373:
#line 408 "lscp.y"
    { (yyval.Char) = '\354'; }
    break;

  case 374:
#line 408 "lscp.y"
    { (yyval.Char) = '\355'; }
    break;

  case 375:
#line 408 "lscp.y"
    { (yyval.Char) = '\356'; }
    break;

  case 376:
#line 409 "lscp.y"
    { (yyval.Char) = '\357'; }
    break;

  case 377:
#line 409 "lscp.y"
    { (yyval.Char) = '\360'; }
    break;

  case 378:
#line 409 "lscp.y"
    { (yyval.Char) = '\361'; }
    break;

  case 379:
#line 410 "lscp.y"
    { (yyval.Char) = '\362'; }
    break;

  case 380:
#line 410 "lscp.y"
    { (yyval.Char) = '\363'; }
    break;

  case 381:
#line 410 "lscp.y"
    { (yyval.Char) = '\364'; }
    break;

  case 382:
#line 411 "lscp.y"
    { (yyval.Char) = '\365'; }
    break;

  case 383:
#line 411 "lscp.y"
    { (yyval.Char) = '\366'; }
    break;

  case 384:
#line 411 "lscp.y"
    { (yyval.Char) = '\367'; }
    break;

  case 385:
#line 412 "lscp.y"
    { (yyval.Char) = '\370'; }
    break;

  case 386:
#line 412 "lscp.y"
    { (yyval.Char) = '\371'; }
    break;

  case 387:
#line 412 "lscp.y"
    { (yyval.Char) = '\372'; }
    break;

  case 388:
#line 413 "lscp.y"
    { (yyval.Char) = '\373'; }
    break;

  case 389:
#line 413 "lscp.y"
    { (yyval.Char) = '\374'; }
    break;

  case 390:
#line 413 "lscp.y"
    { (yyval.Char) = '\375'; }
    break;

  case 391:
#line 414 "lscp.y"
    { (yyval.Char) = '\376'; }
    break;

  case 392:
#line 414 "lscp.y"
    { (yyval.Char) = '\377'; }
    break;

  case 393:
#line 417 "lscp.y"
    { (yyval.String) = " ";      }
    break;

  case 395:
#line 419 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + " "; }
    break;

  case 396:
#line 420 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + (yyvsp[(2) - (2)].String);  }
    break;

  case 397:
#line 423 "lscp.y"
    { (yyval.String) = (yyvsp[(2) - (3)].String); }
    break;

  case 398:
#line 424 "lscp.y"
    { (yyval.String) = (yyvsp[(2) - (3)].String); }
    break;


/* Line 1267 of yacc.c.  */
#line 4920 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
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
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
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
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
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
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
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
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}


#line 631 "lscp.y"


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

