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
#define YYLAST   4282

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  227
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  124
/* YYNRULES -- Number of rules.  */
#define YYNRULES  486
/* YYNRULES -- Number of states.  */
#define YYNSTATES  1455

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
      95,    97,    99,   103,   105,   107,   109,   111,   113,   115,
     117,   119,   121,   123,   125,   127,   129,   131,   147,   165,
     183,   203,   211,   215,   219,   223,   225,   227,   233,   241,
     251,   253,   259,   267,   277,   279,   281,   287,   293,   301,
     311,   319,   329,   331,   337,   345,   351,   357,   363,   367,
     369,   371,   375,   379,   389,   391,   397,   405,   415,   423,
     433,   437,   445,   449,   455,   459,   465,   469,   473,   477,
     481,   485,   489,   493,   497,   503,   511,   517,   527,   533,
     539,   545,   551,   557,   563,   569,   575,   581,   587,   591,
     597,   599,   601,   603,   605,   607,   609,   611,   613,   617,
     621,   623,   629,   637,   641,   643,   645,   647,   649,   651,
     653,   655,   657,   659,   661,   663,   665,   667,   669,   671,
     673,   675,   677,   679,   681,   683,   685,   689,   691,   693,
     695,   697,   699,   701,   703,   706,   710,   715,   720,   722,
     725,   727,   729,   731,   733,   735,   737,   739,   741,   743,
     745,   747,   750,   753,   756,   759,   762,   765,   768,   771,
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
    1134,  1136,  1138,  1140,  1142,  1144,  1146,  1148,  1150,  1152,
    1154,  1156,  1158,  1160,  1162,  1164,  1166,  1168,  1170,  1172,
    1174,  1176,  1178,  1180,  1182,  1184,  1186,  1188,  1190,  1192,
    1194,  1196,  1198,  1200,  1202,  1204,  1206,  1208,  1210,  1212,
    1214,  1216,  1219,  1222,  1226,  1230,  1232,  1234,  1236,  1240,
    1244,  1248,  1254,  1260,  1267,  1275,  1280,  1285,  1289,  1294,
    1302,  1312,  1319,  1323,  1333,  1345,  1352,  1360,  1378,  1409,
    1418,  1423,  1437,  1450,  1462,  1475,  1487,  1505,  1527,  1538,
    1545,  1555,  1570,  1581,  1611,  1632,  1652,  1682,  1702,  1733,
    1754,  1772,  1801,  1829,  1855,  1874,  1892,  1920,  1936,  1953,
    1973,  1994,  2012,  2028,  2047,  2063,  2074,  2081,  2088,  2093,
    2098,  2104,  2115,  2121,  2135,  2140,  2145
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     228,     0,    -1,   229,   280,    -1,   229,   281,   280,    -1,
      -1,   230,    -1,   231,    -1,     1,    -1,     3,    -1,   230,
       3,    -1,   230,   279,    -1,   230,   275,    -1,   230,   271,
      -1,   282,   279,   232,    -1,   284,   279,   235,    -1,   285,
     279,   236,    -1,   283,   279,   238,    -1,   287,   279,   240,
      -1,   288,   279,   243,    -1,   289,   279,   248,    -1,   290,
     279,   244,    -1,   295,   279,   237,    -1,   296,   279,   239,
      -1,   297,   279,   233,    -1,   298,   279,   234,    -1,   299,
     279,   277,    -1,   346,   279,   241,    -1,   286,   279,   242,
      -1,   346,    -1,   350,    -1,   300,    -1,   333,    -1,   333,
     279,   266,    -1,   305,    -1,   309,    -1,   308,    -1,   307,
      -1,   306,    -1,   347,    -1,   310,    -1,   305,    -1,   309,
      -1,   308,    -1,   307,    -1,   306,    -1,   347,    -1,   310,
      -1,   331,   279,   258,   279,   259,   279,   260,   279,   264,
     279,   265,   279,   263,   279,   261,    -1,   331,   279,   258,
     279,   259,   279,   260,   279,   264,   279,   265,   279,   263,
     279,   261,   279,   251,    -1,   331,   279,   258,   279,   259,
     279,   260,   279,   264,   279,   265,   279,   263,   279,   261,
     279,   267,    -1,   331,   279,   258,   279,   259,   279,   260,
     279,   264,   279,   265,   279,   263,   279,   261,   279,   251,
     279,   267,    -1,   331,   279,   258,   279,   259,   279,   260,
      -1,   300,   279,   262,    -1,   333,   279,   258,    -1,   333,
     279,   291,    -1,   301,    -1,   325,    -1,   335,   279,   304,
     279,   271,    -1,   330,   279,   304,   279,   271,   279,   271,
      -1,   330,   279,   304,   279,   271,   279,   271,   279,   246,
      -1,   302,    -1,   321,   279,   304,   279,   271,    -1,   320,
     279,   304,   279,   271,   279,   271,    -1,   320,   279,   304,
     279,   271,   279,   271,   279,   246,    -1,   318,    -1,   328,
      -1,   319,   279,   304,   279,   275,    -1,   329,   279,   304,
     279,   275,    -1,   336,   279,   304,   279,   275,   279,   275,
      -1,   327,   279,   304,   279,   275,   279,   275,   279,   271,
      -1,   323,   279,   304,   279,   275,   279,   275,    -1,   322,
     279,   304,   279,   275,   279,   275,   279,   271,    -1,   303,
      -1,   300,   279,   304,   279,   262,    -1,   300,   279,   307,
     279,   247,   279,   262,    -1,   300,   279,   308,   279,   262,
      -1,   300,   279,   309,   279,   262,    -1,   313,   279,   304,
     279,   264,    -1,   340,   279,   304,    -1,   310,    -1,   311,
      -1,   332,   279,   258,    -1,   332,   279,   291,    -1,   331,
     279,   304,   279,   258,   279,   259,   279,   260,    -1,   334,
      -1,   333,   279,   304,   279,   258,    -1,   317,   279,   275,
     279,   271,     4,   268,    -1,   322,   279,   275,   279,   275,
     279,   271,     4,   268,    -1,   326,   279,   275,   279,   271,
       4,   268,    -1,   327,   279,   275,   279,   275,   279,   271,
       4,   268,    -1,   300,   279,   245,    -1,   333,   279,   348,
     279,   258,   279,   266,    -1,   349,   279,   270,    -1,   319,
     279,   271,   279,   246,    -1,   319,   279,   271,    -1,   329,
     279,   271,   279,   246,    -1,   329,   279,   271,    -1,   300,
     279,   262,    -1,   332,   279,   258,    -1,   332,   279,   291,
      -1,   319,   279,   275,    -1,   329,   279,   275,    -1,   312,
     279,   249,    -1,   313,   279,   250,    -1,   319,   279,   262,
     279,   252,    -1,   323,   279,   262,   279,   253,   279,   253,
      -1,   324,   279,   262,   279,   254,    -1,   339,   279,   262,
     279,   252,   279,   255,   279,   256,    -1,   329,   279,   262,
     279,   252,    -1,   336,   279,   262,   279,   255,    -1,   337,
     279,   262,   279,   256,    -1,   338,   279,   262,   279,   257,
      -1,   341,   279,   262,   279,   261,    -1,   342,   279,   262,
     279,   270,    -1,   343,   279,   262,   279,   270,    -1,   333,
     279,   262,   279,   258,    -1,   333,   279,   262,   279,   292,
      -1,   333,   279,   262,   279,   293,    -1,   271,     4,   268,
      -1,   246,   279,   271,     4,   268,    -1,   344,    -1,   345,
      -1,   318,    -1,   328,    -1,   303,    -1,   301,    -1,   325,
      -1,   302,    -1,   332,   279,   258,    -1,   332,   279,   291,
      -1,   334,    -1,   265,   279,   263,   279,   262,    -1,   294,
     279,   265,   279,   263,   279,   262,    -1,   264,   279,   262,
      -1,   314,    -1,   315,    -1,   316,    -1,   275,    -1,   275,
      -1,   271,    -1,   275,    -1,   275,    -1,   291,    -1,   271,
      -1,   275,    -1,   275,    -1,   275,    -1,   272,    -1,   275,
      -1,   275,    -1,   275,    -1,   271,    -1,   278,    -1,   278,
      -1,   278,    -1,   269,    -1,   268,     5,   269,    -1,   271,
      -1,   278,    -1,   275,    -1,   272,    -1,   275,    -1,   271,
      -1,   276,    -1,   271,   276,    -1,   273,     6,   273,    -1,
       7,   273,     6,   273,    -1,     8,   273,     6,   273,    -1,
     274,    -1,   273,   274,    -1,     9,    -1,    10,    -1,    11,
      -1,    12,    -1,    13,    -1,    14,    -1,    15,    -1,    16,
      -1,    17,    -1,    18,    -1,   274,    -1,    10,   273,    -1,
      11,   273,    -1,    12,   273,    -1,    13,   273,    -1,    14,
     273,    -1,    15,   273,    -1,    16,   273,    -1,    17,   273,
      -1,    18,   273,    -1,    19,    -1,    20,    -1,    21,    -1,
      22,    -1,    23,    -1,    24,    -1,    25,    -1,    26,    -1,
      27,    -1,    28,    -1,    29,    -1,    30,    -1,    31,    -1,
      32,    -1,    33,    -1,    34,    -1,    35,    -1,    36,    -1,
      37,    -1,    38,    -1,    39,    -1,    40,    -1,    41,    -1,
      42,    -1,    43,    -1,    44,    -1,    45,    -1,    46,    -1,
      47,    -1,    48,    -1,    49,    -1,    50,    -1,    51,    -1,
      52,    -1,    53,    -1,    54,    -1,    55,    -1,    56,    -1,
      57,    -1,    58,    -1,    59,    -1,    60,    -1,    61,    -1,
      62,    -1,    63,    -1,    64,    -1,    65,    -1,    66,    -1,
      67,    -1,    68,    -1,    69,    -1,    70,    -1,     9,    -1,
      10,    -1,    11,    -1,    12,    -1,    13,    -1,    14,    -1,
      15,    -1,    16,    -1,    17,    -1,    18,    -1,    71,    -1,
       3,    -1,    72,    -1,    73,    -1,    74,    -1,    75,    -1,
      76,    -1,    77,    -1,     7,    -1,     8,    -1,     6,    -1,
       5,    -1,    78,    -1,    79,    -1,    80,    -1,    81,    -1,
       4,    -1,    82,    -1,    83,    -1,    84,    -1,    85,    -1,
      86,    -1,    87,    -1,    88,    -1,    89,    -1,    90,    -1,
      91,    -1,    92,    -1,    93,    -1,    94,    -1,    95,    -1,
      96,    -1,    97,    -1,    98,    -1,    99,    -1,   100,    -1,
     101,    -1,   102,    -1,   103,    -1,   104,    -1,   105,    -1,
     106,    -1,   107,    -1,   108,    -1,   109,    -1,   110,    -1,
     111,    -1,   112,    -1,   113,    -1,   114,    -1,   115,    -1,
     116,    -1,   117,    -1,   118,    -1,   119,    -1,   120,    -1,
     121,    -1,   122,    -1,   123,    -1,   124,    -1,   125,    -1,
     126,    -1,   127,    -1,   128,    -1,   129,    -1,   130,    -1,
     131,    -1,   132,    -1,   133,    -1,   134,    -1,   135,    -1,
     136,    -1,   137,    -1,   138,    -1,   139,    -1,   140,    -1,
     141,    -1,   142,    -1,   143,    -1,   144,    -1,   145,    -1,
     146,    -1,   147,    -1,   148,    -1,   149,    -1,   150,    -1,
     151,    -1,   152,    -1,   153,    -1,   154,    -1,   155,    -1,
     156,    -1,   157,    -1,   158,    -1,   159,    -1,   160,    -1,
     161,    -1,   162,    -1,   163,    -1,   164,    -1,   165,    -1,
     166,    -1,   167,    -1,   168,    -1,   169,    -1,   170,    -1,
     171,    -1,   172,    -1,   173,    -1,   174,    -1,   175,    -1,
     176,    -1,   177,    -1,   178,    -1,   179,    -1,   180,    -1,
     181,    -1,   182,    -1,   183,    -1,   184,    -1,   185,    -1,
     186,    -1,   187,    -1,   188,    -1,   189,    -1,   190,    -1,
     191,    -1,   192,    -1,   193,    -1,   194,    -1,   195,    -1,
     196,    -1,   197,    -1,   198,    -1,   199,    -1,   200,    -1,
     201,    -1,   202,    -1,   203,    -1,   204,    -1,   205,    -1,
     206,    -1,   207,    -1,   208,    -1,   209,    -1,   210,    -1,
     211,    -1,   212,    -1,   213,    -1,   214,    -1,   215,    -1,
     216,    -1,   217,    -1,   218,    -1,   219,    -1,   220,    -1,
     221,    -1,   279,    -1,   271,    -1,   277,   279,    -1,   277,
     271,    -1,   222,   277,   222,    -1,   223,   277,   223,    -1,
     224,    -1,   225,    -1,   226,    -1,    19,    22,    22,    -1,
      25,    23,    38,    -1,    31,    19,    34,    -1,    39,    32,
      31,    19,    34,    -1,    21,    30,    23,    19,    36,    -1,
      21,    36,    23,    19,    38,    23,    -1,    22,    23,    37,
      38,    36,    33,    43,    -1,    30,    27,    37,    38,    -1,
      30,    33,    19,    22,    -1,    19,    30,    30,    -1,    32,
      33,    32,    23,    -1,    22,    23,    24,    19,    39,    30,
      38,    -1,    32,    33,    32,    89,    31,    33,    22,    19,
      30,    -1,    36,    23,    31,    33,    40,    23,    -1,    37,
      23,    38,    -1,    37,    39,    20,    37,    21,    36,    27,
      20,    23,    -1,    39,    32,    37,    39,    20,    37,    21,
      36,    27,    20,    23,    -1,    37,    23,    30,    23,    21,
      38,    -1,    21,    26,    19,    32,    32,    23,    30,    -1,
      19,    40,    19,    27,    30,    19,    20,    30,    23,    89,
      23,    32,    25,    27,    32,    23,    37,    -1,    19,    40,
      19,    27,    30,    19,    20,    30,    23,    89,    19,    39,
      22,    27,    33,    89,    33,    39,    38,    34,    39,    38,
      89,    22,    36,    27,    40,    23,    36,    37,    -1,    21,
      26,    19,    32,    32,    23,    30,    37,    -1,    27,    32,
      24,    33,    -1,    21,    26,    19,    32,    32,    23,    30,
      89,    21,    33,    39,    32,    38,    -1,    21,    26,    19,
      32,    32,    23,    30,    89,    27,    32,    24,    33,    -1,
      20,    39,    24,    24,    23,    36,    89,    24,    27,    30,
      30,    -1,    37,    38,    36,    23,    19,    31,    89,    21,
      33,    39,    32,    38,    -1,    40,    33,    27,    21,    23,
      89,    21,    33,    39,    32,    38,    -1,    38,    33,    38,
      19,    30,    89,    40,    33,    27,    21,    23,    89,    21,
      33,    39,    32,    38,    -1,    38,    33,    38,    19,    30,
      89,    40,    33,    27,    21,    23,    89,    21,    33,    39,
      32,    38,    89,    31,    19,    42,    -1,    27,    32,    37,
      38,    36,    39,    31,    23,    32,    38,    -1,    23,    32,
      25,    27,    32,    23,    -1,    33,    32,    89,    22,    23,
      31,    19,    32,    22,    -1,    33,    32,    89,    22,    23,
      31,    19,    32,    22,    89,    26,    33,    30,    22,    -1,
      34,    23,    36,    37,    27,    37,    38,    23,    32,    38,
      -1,    19,    39,    22,    27,    33,    89,    33,    39,    38,
      34,    39,    38,    89,    22,    23,    40,    27,    21,    23,
      89,    34,    19,    36,    19,    31,    23,    38,    23,    36,
      -1,    19,    39,    22,    27,    33,    89,    33,    39,    38,
      34,    39,    38,    89,    22,    23,    40,    27,    21,    23,
      37,    -1,    19,    39,    22,    27,    33,    89,    33,    39,
      38,    34,    39,    38,    89,    22,    23,    40,    27,    21,
      23,    -1,    19,    39,    22,    27,    33,    89,    33,    39,
      38,    34,    39,    38,    89,    22,    36,    27,    40,    23,
      36,    89,    34,    19,    36,    19,    31,    23,    38,    23,
      36,    -1,    19,    39,    22,    27,    33,    89,    33,    39,
      38,    34,    39,    38,    89,    22,    36,    27,    40,    23,
      36,    -1,    19,    39,    22,    27,    33,    89,    33,    39,
      38,    34,    39,    38,    89,    21,    26,    19,    32,    32,
      23,    30,    89,    34,    19,    36,    19,    31,    23,    38,
      23,    36,    -1,    19,    39,    22,    27,    33,    89,    33,
      39,    38,    34,    39,    38,    89,    21,    26,    19,    32,
      32,    23,    30,    -1,    19,    39,    22,    27,    33,    89,
      33,    39,    38,    34,    39,    38,    89,    38,    43,    34,
      23,    -1,    19,    40,    19,    27,    30,    19,    20,    30,
      23,    89,    31,    27,    22,    27,    89,    27,    32,    34,
      39,    38,    89,    22,    36,    27,    40,    23,    36,    37,
      -1,    31,    27,    22,    27,    89,    27,    32,    34,    39,
      38,    89,    22,    23,    40,    27,    21,    23,    89,    34,
      19,    36,    19,    31,    23,    38,    23,    36,    -1,    31,
      27,    22,    27,    89,    27,    32,    34,    39,    38,    89,
      34,    33,    36,    38,    89,    34,    19,    36,    19,    31,
      23,    38,    23,    36,    -1,    31,    27,    22,    27,    89,
      27,    32,    34,    39,    38,    89,    22,    23,    40,    27,
      21,    23,    37,    -1,    31,    27,    22,    27,    89,    27,
      32,    34,    39,    38,    89,    22,    23,    40,    27,    21,
      23,    -1,    31,    27,    22,    27,    89,    27,    32,    34,
      39,    38,    89,    22,    36,    27,    40,    23,    36,    89,
      34,    19,    36,    19,    31,    23,    38,    23,    36,    -1,
      31,    27,    22,    27,    89,    27,    32,    37,    38,    36,
      39,    31,    23,    32,    38,    -1,    31,    27,    22,    27,
      89,    27,    32,    37,    38,    36,    39,    31,    23,    32,
      38,    37,    -1,    31,    27,    22,    27,    89,    27,    32,
      37,    38,    36,    39,    31,    23,    32,    38,    89,    31,
      19,    34,    -1,    31,    27,    22,    27,    89,    27,    32,
      37,    38,    36,    39,    31,    23,    32,    38,    89,    31,
      19,    34,    37,    -1,    31,    27,    22,    27,    89,    27,
      32,    34,    39,    38,    89,    22,    36,    27,    40,    23,
      36,    -1,    31,    27,    22,    27,    89,    27,    32,    34,
      39,    38,    89,    34,    33,    36,    38,    -1,    31,    27,
      22,    27,    89,    27,    32,    34,    39,    38,    89,    21,
      26,    19,    32,    32,    23,    30,    -1,    31,    27,    22,
      27,    89,    27,    32,    34,    39,    38,    89,    38,    43,
      34,    23,    -1,    31,    27,    22,    27,    89,    27,    32,
      34,    39,    38,    -1,    37,    23,    36,    40,    23,    36,
      -1,    40,    33,    30,    39,    31,    23,    -1,    31,    39,
      38,    23,    -1,    37,    33,    30,    33,    -1,    20,    43,
      38,    23,    37,    -1,    34,    23,    36,    21,    23,    32,
      38,    19,    25,    23,    -1,    36,    23,    37,    23,    38,
      -1,    31,    27,    37,    21,    23,    30,    30,    19,    32,
      23,    33,    39,    37,    -1,    32,    19,    31,    23,    -1,
      23,    21,    26,    33,    -1,    35,    39,    27,    38,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    96,    96,    97,   100,   101,   102,   103,   106,   107,
     108,   109,   110,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     132,   133,   134,   137,   138,   139,   140,   141,   142,   143,
     146,   147,   148,   149,   150,   151,   152,   155,   156,   157,
     158,   161,   164,   165,   166,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   202,   203,   204,   205,
     206,   207,   208,   211,   212,   213,   214,   217,   220,   221,
     224,   225,   228,   229,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   248,   249,
     252,   253,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   267,   268,   271,   274,   275,   276,   279,   282,   285,
     288,   291,   292,   295,   298,   301,   304,   307,   308,   311,
     314,   317,   320,   323,   326,   329,   330,   333,   334,   335,
     336,   344,   345,   348,   349,   352,   353,   354,   358,   359,
     362,   363,   364,   365,   366,   367,   368,   369,   370,   371,
     374,   375,   376,   377,   378,   379,   380,   381,   382,   383,
     385,   385,   385,   385,   385,   385,   385,   385,   385,   385,
     385,   385,   385,   385,   385,   385,   385,   385,   385,   385,
     385,   385,   385,   385,   385,   385,   386,   386,   386,   386,
     386,   386,   386,   386,   386,   386,   386,   386,   386,   386,
     386,   386,   386,   386,   386,   386,   386,   386,   386,   386,
     386,   386,   387,   387,   387,   387,   387,   387,   387,   387,
     387,   387,   388,   388,   388,   388,   388,   388,   388,   388,
     388,   388,   388,   388,   388,   389,   389,   389,   389,   389,
     389,   389,   390,   390,   390,   390,   390,   391,   391,   391,
     391,   392,   392,   392,   393,   393,   393,   394,   394,   394,
     395,   395,   395,   396,   396,   396,   397,   397,   397,   398,
     398,   398,   399,   399,   399,   400,   400,   400,   401,   401,
     401,   402,   402,   402,   403,   403,   403,   404,   404,   404,
     405,   405,   405,   406,   406,   406,   407,   407,   407,   408,
     408,   408,   409,   409,   409,   410,   410,   410,   411,   411,
     411,   412,   412,   412,   413,   413,   413,   414,   414,   414,
     415,   415,   415,   416,   416,   416,   417,   417,   417,   418,
     418,   418,   419,   419,   419,   420,   420,   420,   421,   421,
     421,   422,   422,   422,   423,   423,   423,   424,   424,   424,
     425,   425,   425,   426,   426,   426,   427,   427,   427,   428,
     428,   428,   429,   429,   429,   430,   430,   430,   431,   431,
     431,   432,   432,   432,   433,   433,   433,   434,   434,   437,
     438,   439,   440,   443,   444,   450,   453,   456,   459,   462,
     465,   468,   471,   474,   477,   480,   483,   486,   489,   492,
     495,   498,   501,   504,   507,   510,   513,   516,   519,   522,
     525,   528,   531,   534,   537,   540,   543,   546,   549,   552,
     555,   558,   561,   564,   567,   570,   573,   576,   579,   582,
     585,   588,   591,   594,   597,   600,   603,   606,   609,   612,
     615,   618,   621,   624,   627,   630,   633,   636,   639,   642,
     645,   648,   651,   654,   657,   660,   663
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
  "command", "add_instruction", "subscribe_event", "unsubscribe_event",
  "map_instruction", "unmap_instruction", "remove_instruction",
  "get_instruction", "set_instruction", "create_instruction",
  "reset_instruction", "clear_instruction", "destroy_instruction",
  "load_instruction", "set_chan_instruction", "key_val_list",
  "buffer_size_type", "list_instruction", "load_instr_args",
  "load_engine_args", "instr_load_mode", "device_index",
  "audio_channel_index", "audio_output_type_name", "midi_input_port_index",
  "midi_input_channel_index", "midi_input_type_name", "midi_map",
  "midi_bank", "midi_prog", "volume_value", "sampler_channel",
  "instrument_index", "engine_name", "filename", "map_name", "entry_name",
  "param_val_list", "param_val", "boolean", "string", "dotnum", "digits",
  "digit", "number", "char", "text", "stringval", "SP", "LF", "CR", "ADD",
  "GET", "MAP", "UNMAP", "CLEAR", "CREATE", "DESTROY", "LIST", "LOAD",
  "ALL", "NONE", "DEFAULT", "NON_MODAL", "REMOVE", "SET", "SUBSCRIBE",
  "UNSUBSCRIBE", "SELECT", "CHANNEL", "AVAILABLE_ENGINES",
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
  "MIDI_INSTRUMENT_MAP", "MIDI_INSTRUMENT_MAPS", "MIDI_INPUT_DRIVER",
  "MIDI_INPUT_PORT", "MIDI_INPUT_CHANNEL", "MIDI_INPUT_TYPE", "MIDI_INPUT",
  "SERVER", "VOLUME", "MUTE", "SOLO", "BYTES", "PERCENTAGE", "RESET",
  "MISCELLANEOUS", "NAME", "ECHO", "QUIT", 0
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
     232,   232,   232,   233,   233,   233,   233,   233,   233,   233,
     234,   234,   234,   234,   234,   234,   234,   235,   235,   235,
     235,   236,   237,   237,   237,   238,   238,   238,   238,   238,
     238,   238,   238,   238,   238,   238,   238,   238,   238,   238,
     238,   238,   238,   238,   238,   238,   238,   238,   238,   238,
     238,   238,   238,   238,   238,   238,   239,   239,   239,   239,
     239,   239,   239,   240,   240,   240,   240,   241,   242,   242,
     243,   243,   244,   244,   245,   245,   245,   245,   245,   245,
     245,   245,   245,   245,   245,   245,   245,   245,   246,   246,
     247,   247,   248,   248,   248,   248,   248,   248,   248,   248,
     248,   249,   249,   250,   251,   251,   251,   252,   253,   254,
     255,   256,   256,   257,   258,   259,   260,   261,   261,   262,
     263,   264,   265,   266,   267,   268,   268,   269,   269,   269,
     269,   270,   270,   271,   271,   272,   272,   272,   273,   273,
     274,   274,   274,   274,   274,   274,   274,   274,   274,   274,
     275,   275,   275,   275,   275,   275,   275,   275,   275,   275,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   277,
     277,   277,   277,   278,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   327,   328,   329,   330,   331,   332,   333,
     334,   335,   336,   337,   338,   339,   340,   341,   342,   343,
     344,   345,   346,   347,   348,   349,   350
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     3,     0,     1,     1,     1,     1,     2,
       2,     2,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     1,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,    15,    17,    17,
      19,     7,     3,     3,     3,     1,     1,     5,     7,     9,
       1,     5,     7,     9,     1,     1,     5,     5,     7,     9,
       7,     9,     1,     5,     7,     5,     5,     5,     3,     1,
       1,     3,     3,     9,     1,     5,     7,     9,     7,     9,
       3,     7,     3,     5,     3,     5,     3,     3,     3,     3,
       3,     3,     3,     3,     5,     7,     5,     9,     5,     5,
       5,     5,     5,     5,     5,     5,     5,     5,     3,     5,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       1,     5,     7,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     2,     3,     4,     4,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     3,     3,     1,     1,     1,     3,     3,
       3,     5,     5,     6,     7,     4,     4,     3,     4,     7,
       9,     6,     3,     9,    11,     6,     7,    17,    30,     8,
       4,    13,    12,    11,    12,    11,    17,    21,    10,     6,
       9,    14,    10,    29,    20,    19,    29,    19,    30,    20,
      17,    28,    27,    25,    18,    17,    27,    15,    16,    19,
      20,    17,    15,    18,    15,    10,     6,     6,     4,     4,
       5,    10,     5,    13,     4,     4,     4
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
       0,     0,     0,     0,     0,     0,     1,   416,   417,     2,
       0,     9,   268,   263,   262,   260,   261,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   252,
     254,   255,   256,   257,   258,   259,   264,   265,   266,   267,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,   354,   355,   356,   357,   358,
     359,   360,   361,   362,   363,   364,   365,   366,   367,   368,
     369,   370,   371,   372,   373,   374,   375,   376,   377,   378,
     379,   380,   381,   382,   383,   384,   385,   386,   387,   388,
     389,   390,   391,   392,   393,   394,   395,   396,   397,   398,
     399,   400,   401,   402,   403,   404,   405,   406,   407,   408,
     415,    12,   180,    11,   163,    10,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   418,     0,     0,     0,   419,     0,     0,   420,     0,
       0,     0,     0,   432,     0,     0,     0,     3,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   181,   168,
     182,   183,   184,   185,   186,   187,   188,   189,   253,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   164,
       0,     0,    13,    30,    31,     0,     0,     0,     0,     0,
       0,    16,     0,    55,    60,    72,    79,    80,     0,    64,
       0,     0,     0,     0,     0,    56,     0,    65,     0,     0,
       0,     0,     0,    84,     0,     0,     0,     0,    14,     0,
      15,     0,     0,    27,     0,     0,     0,    17,     0,     0,
      18,     0,     0,     0,     0,     0,    19,   125,   127,   124,
     122,   126,   123,     0,   130,     0,    20,     0,     0,    21,
       0,     0,     0,     0,     0,    22,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    23,
      33,    37,    36,    35,    34,    39,    38,    24,    40,    44,
      43,    42,    41,    46,    45,   410,    25,   409,    26,     0,
       0,     0,     0,   425,   426,   486,     0,     0,     0,     0,
       0,     0,   169,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   412,   411,     0,   422,     0,
       0,     0,   482,     0,     0,   421,     0,     0,     0,     0,
       0,    32,   153,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   171,   172,   173,   174,   175,
     176,   177,   178,   179,     0,    81,   144,    82,     0,     0,
       0,    78,     0,     0,     0,     0,    98,    99,     0,     0,
      94,    96,   100,   101,     0,     0,     0,   128,   129,     0,
       0,   102,     0,   152,     0,   103,     0,   151,    52,   149,
      53,    54,     0,     0,     0,     0,     0,     0,     0,    90,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    92,   162,
     161,     0,     0,     0,     0,     0,     0,    97,   423,     0,
     431,   435,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   485,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   424,     0,     0,     0,     0,   413,   414,     0,
       0,     0,     0,     0,     0,     0,     0,    73,     0,     0,
       0,   120,   121,    75,    76,    77,    66,     0,    61,     0,
       0,     0,    67,     0,     0,   427,    85,    57,     0,     0,
       0,   145,     0,     0,     0,     0,    93,     0,    95,     0,
       0,     0,     0,     0,     0,   150,     0,   133,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   449,     0,   476,     0,
     440,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     478,   479,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   484,
       0,     0,     0,     0,     0,     0,     0,   433,     0,   436,
       0,     0,     0,   436,     0,     0,     0,     0,    74,    62,
       0,    70,     0,    58,     0,    68,     0,     0,   146,    51,
       0,     0,     0,     0,   260,   261,   118,   155,   157,   160,
       0,   168,   159,   158,     0,     0,     0,     0,     0,   131,
       0,     0,     0,     0,     0,     0,   104,   137,     0,   138,
     106,   139,   108,     0,     0,   115,   116,   117,   109,   140,
     110,   141,   142,   111,   143,     0,     0,     0,   112,   147,
     148,   113,   114,    86,     0,    88,     0,    91,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   439,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   477,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   434,     0,     0,     0,     0,     0,     0,   480,
       0,    63,    71,    69,    59,    83,     0,     0,     0,     0,
       0,   119,     0,     0,   156,   165,     0,     0,     0,     0,
       0,   132,     0,     0,     0,     0,   105,     0,     0,     0,
      87,    89,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   166,   167,     0,     0,     0,   448,     0,     0,     0,
       0,     0,     0,   428,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   430,
       0,     0,     0,     0,     0,   107,   443,     0,     0,     0,
       0,     0,   445,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   475,     0,     0,   442,     0,
     444,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   429,   441,   483,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   481,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   472,   467,
       0,   467,    47,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   468,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   437,     0,   465,   471,     0,     0,   446,     0,     0,
      48,    49,   154,   134,   135,   136,     0,   465,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   472,   474,   446,
       0,     0,     0,     0,     0,     0,   464,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   469,     0,   455,   457,     0,     0,     0,
       0,   469,     0,     0,     0,    50,   455,     0,     0,     0,
       0,     0,     0,   460,     0,   459,   454,     0,     0,     0,
       0,     0,   470,     0,     0,     0,     0,     0,     0,     0,
     473,     0,     0,     0,     0,     0,     0,   447,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   459,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   463,
     450,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     452,     0,     0,     0,     0,     0,     0,   466,     0,     0,
     462,     0,     0,     0,   461,     0,     0,     0,   456,     0,
       0,   453,   458,   438,   451
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    13,    14,    15,    16,   342,   429,   437,   378,   380,
     409,   351,   415,   387,   448,   383,   390,   406,   619,   776,
     750,   396,   601,   605,  1290,   936,   938,   940,   948,   950,
     953,   575,   770,   907,   958,   608,   784,   606,   602,   541,
    1291,   916,   917,   638,   918,   919,   920,   272,   609,   274,
     446,   923,   847,    49,    50,    17,    18,    19,    20,    21,
      22,    23,    24,    25,   952,   946,   947,   604,    26,    27,
      28,    29,    30,   343,   353,   354,   355,   551,   430,   431,
     432,   433,   434,   356,   357,   407,   358,  1293,  1294,  1295,
     417,   359,   360,   361,   362,   363,   364,   622,   365,   419,
     366,   367,   368,   369,   370,   371,   344,   373,   374,   375,
     626,   627,   628,   376,   629,   630,   631,   751,   752,    31,
     436,   637,   422,    32
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -841
static const yytype_int16 yypact[] =
{
      64,  -841,  -841,    52,   167,    92,   120,   177,   126,   132,
     189,    59,   168,   228,    37,  1863,  -841,    16,    16,    16,
      16,    16,    16,    16,    16,    16,    16,    16,    16,    16,
      16,    16,  -841,   243,   237,   252,   274,   242,   275,   298,
     296,   304,   178,   137,   312,   198,  -841,  -841,  -841,  -841,
     108,  -841,  -841,  -841,  -841,  -841,  -841,  -841,   238,   238,
     238,   238,   238,   238,   238,   238,   238,  -841,  -841,  -841,
    -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,
    -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,
    -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,
    -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,
    -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,
    -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,
    -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,
    -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,
    -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,
    -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,
    -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,
    -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,
    -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,
    -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,
    -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,
    -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,
    -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,
    -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,
    -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,
    -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,
    -841,  2528,  -841,  -841,  -841,  -841,   117,   109,   303,   303,
     305,   100,   100,   174,    70,   117,   147,   104,   104,  2085,
     314,  -841,   319,   320,   302,  -841,   306,   330,  -841,   327,
     309,   335,   344,  -841,   331,   351,   332,  -841,  -841,  -841,
    -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,   238,  -841,
     238,   238,   238,   238,   238,   238,   238,   238,  -841,  -841,
    -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,
     346,   348,  -841,  -841,    16,   229,   363,   358,   364,   371,
     365,  -841,    16,  -841,  -841,  -841,  -841,  -841,    16,  -841,
      16,    16,    16,    16,    16,  -841,    16,  -841,    16,    16,
      16,    16,    16,  -841,    16,    16,    16,   372,  -841,    16,
    -841,    16,   373,  -841,    16,   370,   381,  -841,    16,    16,
    -841,    16,    16,   231,   384,   385,  -841,  -841,  -841,  -841,
    -841,  -841,  -841,    16,  -841,   379,  -841,    16,    16,  -841,
      16,    16,   374,   393,   388,  -841,    16,    16,    16,    16,
      16,    16,    16,   377,   391,   405,   395,   402,   403,  -841,
    -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,
    -841,  -841,  -841,  -841,  -841,  2528,  2085,  -841,  -841,    16,
     401,   400,   404,  -841,  -841,  -841,   399,   406,   420,   421,
     411,   439,  -841,   441,   436,    55,   440,   442,   444,   443,
     445,   428,   427,    50,   446,   446,   446,   446,   446,   446,
     446,   446,   446,   446,   438,   446,   446,   446,   446,   447,
     369,   369,   449,   438,   450,   452,  2528,  2528,   369,   369,
     453,   459,   458,   438,   429,    11,  2528,   369,   438,   460,
     455,   461,    83,   369,   369,   369,   369,   454,  2747,   463,
     469,   456,   462,   457,   464,  2528,  -841,   369,  -841,   467,
     470,   473,  -841,   468,   471,  -841,   472,   465,   478,  2085,
    2085,  -841,  -841,   481,   483,   479,   486,   487,   475,   497,
     485,    16,    16,    16,    16,    16,    16,    16,    16,    16,
      16,    16,    16,    16,    16,   238,   238,   238,   238,   238,
     238,   238,   238,   238,   488,  -841,  -841,  -841,    16,    16,
      16,  -841,   492,    16,    16,   493,  -841,  -841,   494,   495,
    2085,  2085,  -841,  -841,   496,   503,   523,  -841,  -841,   513,
     528,  -841,    16,  -841,    16,  -841,    16,  2528,  -841,  -841,
    -841,  -841,   535,   533,   540,   531,   110,   538,   539,  -841,
      16,    16,    16,    16,    16,    16,    16,    16,    16,    16,
      16,    16,    16,    16,    16,    16,   554,    16,  -841,  2528,
    -841,   550,   545,   558,   557,   562,   561,  -841,  -841,   541,
    -841,  -841,   556,   564,   560,   499,  1419,  1641,   553,   563,
     565,   566,   501,   571,   569,   572,   369,   102,   369,   369,
    2528,   369,  2528,  2528,   369,   369,   369,   369,  2528,   369,
     570,   369,  2528,   369,   506,   369,   369,   512,   588,   514,
    2528,  2528,   590,   592,   515,   589,   594,   369,    55,   369,
     595,  -841,   542,   580,   605,   591,   600,   602,   369,   369,
     369,   369,   369,   369,   369,   369,   369,   369,   369,   369,
    2528,   369,  2528,   369,   603,   369,   610,   604,   612,   618,
     608,   616,  -841,   623,   609,   621,   619,  -841,  -841,   559,
     628,   626,   627,   624,   617,   567,   622,  -841,   611,   629,
      16,  -841,  -841,  -841,  -841,  -841,  -841,  2085,  2528,    16,
      16,    16,  -841,  2085,    16,  -841,  -841,  2528,    16,   631,
      16,  -841,    16,   632,   575,   639,    16,  2966,    16,   579,
     647,   646,   635,   586,    16,  -841,    16,  -841,   587,   650,
     651,   652,   657,   648,   643,    16,    16,    16,    16,    16,
      16,    16,    16,    16,    16,    16,    16,  3185,    16,  3404,
      16,   661,    16,   649,   663,   658,   656,   601,   606,   666,
     664,   662,   665,   660,   674,   668,  -841,   667,  -841,   670,
    -841,   675,   669,   369,  2528,   369,   369,   369,  2528,   369,
     369,   671,   369,   369,   672,   673,   676,  2528,  2307,   679,
     684,   683,   685,   686,   369,   369,   688,   687,   689,   607,
    -841,  -841,   692,   369,   369,  2528,   369,    95,   369,   438,
    2528,   369,   412,  2747,  2747,  2307,  2528,  2307,  2528,  -841,
      55,   613,   694,   695,   637,   678,   680,  -841,   707,  -841,
     691,   690,   700,   696,   135,   698,   677,   711,  -841,  2085,
      16,  -841,    16,  2085,    16,  -841,   697,    16,  -841,  -841,
     699,   701,   703,  3623,   238,   238,   733,  -841,  2528,  -841,
     173,    33,  -841,  -841,   702,   696,   162,   716,   710,  -841,
      16,   708,   202,   681,   723,   728,  -841,  -841,    16,  -841,
    -841,  2528,  -841,   731,   725,  -841,  -841,  -841,  -841,  -841,
    -841,  -841,  -841,  -841,  2528,    16,   238,   238,  -841,  -841,
    -841,  -841,  -841,   733,  3842,   733,  4061,  -841,   732,   705,
     740,   739,   729,   730,   738,   726,   727,   743,  -841,   734,
     736,   741,   735,   744,  2528,  2528,  2528,  2528,   369,   737,
    2528,   754,   758,   759,  2307,   285,   310,  2307,   238,   761,
     762,   764,   745,   756,   369,   765,   766,   746,   768,  -841,
     369,   752,   772,   369,  2307,  2307,   779,   210,   775,   777,
     781,   773,  -841,   778,   782,   722,   780,   783,   792,  -841,
     785,    16,  2528,  2528,    16,  -841,   784,    16,   791,   796,
     793,   733,   238,   238,  -841,   238,   801,   799,   803,   802,
     823,  -841,   809,   806,   776,   204,  -841,   826,   824,    16,
     733,   733,   816,   815,   819,   833,   825,   841,   834,   828,
     829,   175,   789,   830,   842,   832,   835,    55,   840,   843,
     794,   238,   238,   851,   804,   852,  -841,   850,   855,   807,
     857,   860,   861,  -841,   438,   873,   865,   847,   839,   874,
     882,   869,   877,   871,   872,   878,   846,   139,   881,   827,
     894,   888,    16,   889,   883,   900,   886,   903,   895,  -841,
     891,   158,   896,   893,   902,  -841,  -841,   901,   905,   897,
     904,   845,  -841,   912,   856,   917,   916,   925,    93,   915,
     927,   930,   928,   929,   369,   931,   875,   937,   876,   938,
     939,   879,   940,   933,   934,   880,   941,   943,  -841,   935,
    -841,   946,   945,   251,   951,   955,   957,   947,   959,   952,
     958,   956,   968,   960,    16,   961,   972,   962,   973,   965,
     966,   271,   967,   974,   970,    54,  -841,  -841,  -841,   964,
     971,   466,   103,   978,   980,   924,   987,   975,   979,   981,
     977,  -841,   982,   412,   983,   995,   996,  1001,   998,   988,
    1002,  1004,  1005,   993,   944,  1008,  1003,   992,   999,   948,
    1020,  1000,  1014,   963,  1022,  1019,  1026,  1025,   969,    29,
    1017,  -841,    16,  1013,  1011,  1032,  1015,  1033,    32,  1037,
    1021,  1036,   969,   112,  1040,  1024,  1028,  1031,  1035,  1039,
    1041,  1027,  1042,  1044,  1045,  1046,  1043,  1038,  -841,  1047,
    1048,    22,  1049,  1050,  1055,  1060,  1054,  1057,  1063,  1068,
    1066,  1051,  1061,  1058,  1072,  1062,  1079,  1067,  1081,  1082,
    1069,  -841,  1073,  1074,  1023,  1087,  1091,  1029,  1083,  1094,
      16,  -841,  -841,  -841,  -841,  -841,  1098,  -841,  1099,  1074,
    1104,  1092,  1105,  1052,  1106,  1093,  1096,  -841,  -841,  -841,
    1095,  1108,  1109,  1097,  1100,  1101,  -841,  1102,  1103,  1110,
    1111,  1056,  1107,    55,  1112,  1114,  1113,  1123,  1125,  1115,
    1118,  1129,  1131,  -841,  1126,  1120,  1071,  1121,  1124,  1139,
    1142,  1128,  1144,  1145,  1132,  -841,  -841,  1120,  1128,  1136,
    1084,  1149,  1138,  -841,  1141,  1085,  -841,  1143,  1133,  1086,
    1140,  1147,  -841,  1137,  1157,  1154,  1085,  1148,  1150,  1160,
    -841,  1151,  1165,  1152,  1166,  1168,  1169,  -841,  1162,  1158,
    1172,  1175,  1167,  1177,  1163,  1116,  1164,  1170,  1171,  1179,
    1173,  1176,  1182,  -841,  1178,  1183,  1181,  1180,  1185,  1192,
    1184,  1195,  1200,  1198,  1203,  1193,  1187,  1186,  1189,  1194,
    1206,  1197,  1201,  1196,  1202,  1208,  1209,  1212,  1214,  -841,
    1153,  1205,  1215,  1216,  1217,  1207,  1204,  1210,  1211,  1223,
    -841,  1213,  1218,  1219,  1227,  1229,  1221,  -841,  1220,  1232,
    -841,  1233,  1224,  1226,  -841,  1174,  1228,  1230,  -841,  1222,
    1241,  -841,  -841,  -841,  -841
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,
    -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -674,
    -841,  -841,  -841,  -841,  -841,  -793,   124,  -841,   254,   176,
    -841,  -449,  -626,  -780,    38,  -492,  -826,  -640,  -680,   392,
     -55,  -813,   277,  -569,   431,  -840,   -13,   -39,   -14,   307,
    -233,  -437,   -15,  1231,  -841,  -841,  -841,  -841,  -841,  -841,
    -841,  -841,  -841,  -841,  -412,  -841,  -841,  -841,  -841,  -841,
    -841,  -841,  -841,  -206,   994,   997,  1006,  -323,   991,  1007,
    -231,  -230,  -227,    21,  -841,  -841,  1009,  -841,  -841,  -841,
    -841,  1016,  -248,  -841,  -841,   990,   770,  -841,  1030,  -841,
    1012,  1034,  -245,  -841,    36,   -69,  -246,  1053,  -841,   771,
    -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,
    1018,  -841,  -841,  -841
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -181
static const yytype_int16 yytable[] =
{
     275,   273,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   778,   786,   319,
     319,   319,   319,   319,   319,   319,   319,   319,   542,   930,
     755,   372,   959,   388,   391,   647,   389,   392,  -180,   411,
     421,   583,   584,   600,   586,   318,   320,   321,   322,   323,
     324,   325,   326,   327,   597,  1288,  1289,   440,   441,   610,
     772,   442,   963,   909,   965,     1,  1258,     2,   603,  1258,
     423,   352,   577,   942,    33,  1215,  1147,   550,   955,   410,
     416,   587,    43,     3,   449,     4,     5,   426,  1216,     6,
     428,   598,  1217,   347,     7,     8,   611,   405,    44,     9,
      10,    11,   615,    12,   308,   565,   566,   567,   568,   569,
     570,   571,   572,   573,   616,    36,  1167,   943,  1259,   385,
     617,  1266,   748,   618,   423,   424,  1221,   944,   345,  1168,
     346,   386,   347,  1270,  1205,   425,   749,   704,   340,  1222,
     348,   426,   427,    37,   428,    40,   349,   350,   341,   705,
    1271,   555,   556,   557,   558,   559,   560,   561,   562,   563,
     564,  1138,   578,   579,   580,   581,   412,   302,   340,   979,
     413,    41,   980,  1139,   747,   303,   753,   754,   414,   998,
    1152,  1041,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,  1153,   393,  1104,   394,  1000,    34,  1105,  1001,
      45,  1060,  1061,    35,    38,   395,  1106,   787,  1035,   300,
      39,   384,    42,   904,   403,   301,   795,   796,   797,   798,
     799,   800,   801,   802,   803,   804,   805,   806,    46,   305,
     764,  1063,   766,   539,   540,   306,  1006,  1064,  1091,   975,
     270,   975,   552,   553,   539,   540,   554,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,  -180,  -180,  -180,
     292,   603,    47,    48,   620,   291,   624,   623,   466,   467,
     500,   467,  1191,  1192,   447,   293,   812,   539,   540,   462,
     295,   462,   462,   462,   462,   462,   462,   462,   462,    -4,
      -4,  1042,  1210,  1211,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   961,   962,   656,   657,   435,   443,
    1031,   294,   296,  1034,   379,   381,  1043,   297,  1174,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   465,
     298,   299,   304,    47,   377,   340,   382,   473,   450,   451,
     452,   898,   456,   474,   453,   475,   476,   477,   478,   479,
    1037,   480,   454,   481,   482,   483,   484,   485,   457,   486,
     487,   488,   929,   959,   490,   455,   491,   458,   459,   493,
     460,   461,   463,   496,   497,   464,   498,   499,   308,   565,
     566,   567,   568,   569,   570,   571,   572,   573,   503,   468,
     469,   470,   505,   506,   471,   507,   508,  1112,   472,   489,
     492,   512,   513,   514,   515,   516,   517,   518,   495,   494,
     501,   504,   502,   509,   510,   511,   519,   520,   945,   956,
     957,   308,   565,   566,   567,   568,   569,   570,   571,   572,
     573,   526,   521,   522,   527,   523,   524,   528,   529,   531,
     530,   533,   534,   542,   532,   535,   271,   308,   565,   566,
     567,   568,   569,   570,   571,   572,   573,   574,   538,   536,
     537,   544,   543,   545,   548,   549,   599,   547,   546,   582,
     576,   585,   588,   550,   589,   594,   576,   576,   595,   576,
     596,   613,   612,   614,   592,   593,   636,   641,   642,   576,
     648,   646,  1220,   643,   576,   645,   650,   654,   644,   632,
     633,   634,   635,   649,   640,   655,   651,   652,   658,   653,
     659,   660,  1051,   661,   662,   663,   664,   665,   680,   684,
     687,   688,   689,   692,   447,   447,   319,   319,   319,   319,
     319,   319,   319,   319,   319,   693,   666,   667,   668,   669,
     670,   671,   672,   673,   674,   675,   676,   677,   678,   679,
     694,   695,   318,   320,   321,   322,   323,   324,   325,   326,
     327,   696,   700,   681,   682,   683,   701,   702,   685,   686,
     703,   706,   707,   724,   726,   690,   691,   727,   339,   728,
     729,   730,   731,   733,   732,   734,   739,   697,   736,   698,
     743,   699,   735,   740,   744,   769,   746,   741,   742,   745,
     765,   773,   790,   775,   781,   708,   709,   710,   711,   712,
     713,   714,   715,   716,   717,   718,   719,   720,   721,   722,
     723,   774,   725,   779,   780,   782,   783,   791,   788,   792,
     793,   789,   794,   813,   811,   815,   814,   816,   817,   818,
     603,   526,   526,   819,   821,   820,   822,   824,   823,   825,
     826,   827,   832,   828,   831,   830,   829,   756,   841,   844,
     759,   760,   761,   762,   845,   576,   846,   576,   849,   768,
     850,   771,   771,   851,   852,   853,   856,   857,   858,   859,
     860,   861,   862,   785,   879,   881,   882,   884,   883,   887,
     885,   888,   889,   891,   892,   886,   934,   890,   893,   894,
     982,   973,   968,   906,   910,   897,   911,   808,   912,   810,
     895,   576,   924,   896,   925,   926,   927,   928,   972,   932,
     445,   931,   933,   935,   969,   970,   971,   974,   975,   976,
     977,   981,   983,   978,   989,   833,   991,   993,   997,  1002,
     992,   999,   834,  1003,   835,   836,   837,  1005,   838,   839,
    1008,  1009,   339,   840,  1011,   842,  1016,   843,  1012,  1018,
    1019,  1022,  1020,  1021,  1023,  1024,  1025,  1030,  1028,   854,
    1007,   855,  1029,  1026,  1027,  1036,  1057,  1049,  1050,  1054,
     863,   864,   865,   866,   867,   868,   869,   870,   871,   872,
     873,   874,  1038,   876,  1017,   878,  1039,   880,  1040,  1046,
    1055,  1047,  1048,  1052,  1058,  1053,  1062,  1065,  1067,   921,
    1066,  1071,  1068,  1074,  1069,  1090,  1070,  1075,  1072,  1073,
    1076,   900,   901,   902,  1292,   771,   905,  1078,   908,   908,
    1079,  1080,   339,   921,   922,  1083,   921,  1084,   921,  1085,
    1086,   785,  1087,  1088,  1089,  1092,  1095,  1093,  1096,   937,
     939,  1097,   937,   576,   949,   951,  1098,   937,   960,   640,
     640,   922,  1100,   922,  1099,  1109,  1101,  1102,  1103,  1108,
    1110,  1128,  1129,  1137,  1111,   319,   319,   525,  1107,  1113,
    1119,   462,  1114,  1115,   984,   985,  1292,   986,   987,   988,
    1116,  1118,   990,  1117,  1120,  1122,  1121,   339,   339,  1123,
    1124,   995,   996,  1126,  1127,  1131,  1130,  1132,  1133,  1134,
    1136,  1135,  1140,  1142,   339,  1004,  1141,   319,   319,  1143,
    1145,  1146,  1147,  1010,  1148,  1149,  1150,   590,   591,  1151,
    1154,  1155,  1156,  1157,  1161,  1162,  1159,   607,  1158,  1164,
    1013,  1165,  1160,   995,   996,  1163,   339,  1166,  1169,   639,
    1170,  1171,  1173,  1172,  1175,   921,   462,   462,   921,   319,
    1177,  1179,  1180,  1182,  1176,  1178,  1183,  1189,  1181,  1185,
     445,   445,  1188,  1184,   908,   921,   921,  1190,  1193,  1186,
     922,  1187,  1194,   922,  1195,  1045,  1197,  1196,  1198,  1200,
    1199,  1201,  1202,  1204,  1205,  1207,   939,  1218,  1209,   949,
     922,   922,  1206,   319,   319,  1208,   462,  1212,  1214,  1219,
    1213,  1223,  1224,  1225,  1226,  1227,  1230,  1228,  1234,  1229,
    1231,  1233,  1077,  1235,  1236,  1237,  1238,  1240,  1239,  1081,
    1082,  1242,  1241,  1243,  1244,  1246,  1245,  1248,  1247,  1249,
    1250,  1251,   462,   462,  1094,  1253,  1254,  1255,  1256,  1260,
    1258,  1262,  1252,  1263,  1265,  1264,  1267,  1269,  1257,  1272,
    1273,  1268,  1274,  1275,   339,   339,  1276,  1279,  1278,  1283,
     339,  1277,  1285,  1297,   339,  1280,  1296,  1282,  1286,  1284,
     951,  1281,  1298,  1299,   339,  1300,  1287,   525,   525,  1301,
    1302,  1303,  1304,  1306,  1305,  1308,  1307,  1144,  1310,  1311,
    1309,   607,  1312,   757,   758,  1313,  1318,  1315,  1314,   763,
    1319,  1316,  1317,   767,   339,  1321,   339,  1322,  1320,  1324,
    1325,   777,   777,  1326,  1327,  1330,  1328,  1331,  1332,  1333,
     785,  1334,  1335,  1336,  1056,  1346,  1339,  1347,  1337,  1340,
    1338,  1329,  1342,  1344,  1341,  1343,  1349,  1348,  1350,  1351,
    1352,   807,  1353,   809,  1354,  1358,  1355,  1356,  1360,  1203,
    1357,  1361,  1359,  1363,   921,  1362,  1366,  1364,  1368,  1365,
    1369,  1370,  1373,  1367,  1371,  1374,  1375,  1372,  1376,  1377,
    1378,  1379,  1380,  1382,  1384,  1383,  1381,  1387,  1386,   960,
    1385,  1391,  1388,  1389,  1392,  1390,  1394,  1393,  1400,  1395,
    1397,  1398,  1405,  1406,  1450,  1396,   339,  1407,  1408,  1399,
     339,  1401,  1402,  1403,  1404,  1409,  1410,  1261,  1411,  1412,
     339,  1413,  1414,  1416,  1415,   339,  1417,  1418,  1420,  1421,
    1419,  1425,  1422,  1424,  1423,  1427,  1426,  1428,  1431,  1432,
    1433,  1232,  1429,  1430,  1435,  1434,  1436,  1437,   339,  1438,
    1442,  1439,  1443,  1445,  1440,  1446,  1447,  1441,  1444,  1453,
    1448,   339,  1449,  1454,  1451,   899,  1452,  1059,  1345,   903,
    1125,   339,   967,   339,  1044,  1323,   418,   397,   913,   438,
     398,   307,   621,   625,     0,     0,     0,     0,     0,   399,
       0,     0,     0,   408,     0,   439,   941,     0,   420,   400,
       0,   954,     0,     0,   639,   639,   444,   964,     0,   966,
       0,     0,     0,   401,     0,     0,     0,   402,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   404,     0,     0,   339,
     339,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   777,  1032,  1033,   777,     0,
       0,   607,   328,    52,    53,    54,    55,    56,   329,   330,
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
     269,   737,     0,   270,   328,    52,    53,    54,    55,    56,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
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
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,     0,   738,   270,    51,    52,    53,    54,
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
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,     0,     0,   270,   328,    52,
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
     263,   264,   265,   266,   267,   268,   269,     0,     0,   270,
     328,    52,    53,    54,   914,   915,    57,    58,    59,    60,
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
     261,   262,   263,   264,   265,   266,   267,   268,   269,   539,
     540,   328,    52,    53,    54,    55,    56,   329,   330,   331,
     332,   333,   334,   335,   336,   337,   338,    67,    68,    69,
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
     328,    52,    53,    54,    55,    56,    57,    58,    59,    60,
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
     261,   262,   263,   264,   265,   266,   267,   268,   269,   328,
     848,    53,    54,    55,    56,   329,   330,   331,   332,   333,
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
     262,   263,   264,   265,   266,   267,   268,   269,   328,   875,
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
     263,   264,   265,   266,   267,   268,   269,   328,   877,    53,
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
     264,   265,   266,   267,   268,   269,   328,   994,    53,    54,
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
     265,   266,   267,   268,   269,   328,  1014,    53,    54,    55,
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
     266,   267,   268,   269,   328,  1015,    53,    54,    55,    56,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
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
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269
};

static const yytype_int16 yycheck[] =
{
      15,    15,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,   691,   698,    58,
      59,    60,    61,    62,    63,    64,    65,    66,   465,   855,
     670,   277,   872,   281,   282,   527,   281,   282,     5,   285,
     286,   490,   491,    32,   493,    58,    59,    60,    61,    62,
      63,    64,    65,    66,   503,    33,    34,   288,   288,   508,
     686,   288,   875,   843,   877,     1,    37,     3,   505,    37,
      20,   277,   484,   866,    22,    21,    22,    27,   871,   285,
     286,   493,    23,    19,   290,    21,    22,    37,    34,    25,
      40,   503,    38,    23,    30,    31,   508,    27,    39,    35,
      36,    37,    19,    39,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    31,    23,    23,    22,    89,    19,
      37,    89,    20,    40,    20,    21,    23,    32,    19,    36,
      21,    31,    23,    21,    22,    31,    34,    27,    21,    36,
      31,    37,    38,    23,    40,    19,    37,    38,    31,    39,
      38,   474,   475,   476,   477,   478,   479,   480,   481,   482,
     483,    22,   485,   486,   487,   488,    19,    30,    21,    34,
      23,    39,    37,    34,   666,    38,   668,   669,    31,     6,
      22,   994,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    34,    19,    19,    21,    34,    30,    23,    37,
      32,  1014,  1015,    36,    27,    31,    31,   699,   988,    31,
      33,   280,    23,   839,   283,    37,   708,   709,   710,   711,
     712,   713,   714,   715,   716,   717,   718,   719,     0,    31,
     679,    21,   681,   222,   223,    37,    34,    27,    34,    37,
     224,    37,   473,   473,   222,   223,   473,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,   224,   225,   226,
      23,   698,   225,   226,   512,    22,   512,   512,    39,    40,
      39,    40,    21,    22,   289,    23,   725,   222,   223,   318,
      38,   320,   321,   322,   323,   324,   325,   326,   327,   225,
     226,     6,    21,    22,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,   873,   874,   539,   540,   287,   288,
     984,    37,    37,   987,   278,   279,     6,    19,  1144,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,   344,
      34,    27,    20,   225,    31,    21,    31,   352,    19,    19,
      38,   833,    33,   358,    38,   360,   361,   362,   363,   364,
     990,   366,    22,   368,   369,   370,   371,   372,    23,   374,
     375,   376,   854,  1203,   379,    38,   381,    23,    37,   384,
      19,    39,    26,   388,   389,    27,   391,   392,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,   403,    26,
      32,    27,   407,   408,    23,   410,   411,  1077,    33,    27,
      27,   416,   417,   418,   419,   420,   421,   422,    27,    39,
      26,    32,    27,    39,    21,    27,    39,    26,   867,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,   446,    27,    38,   449,    33,    33,    36,    38,    40,
      36,    21,    21,   880,    38,    34,    15,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    22,    20,
      19,    19,    22,    19,    36,    38,    37,    22,    25,    22,
     484,    22,    22,    27,    22,    22,   490,   491,    19,   493,
      22,    26,    22,    22,   498,   499,    32,    24,    19,   503,
      23,    27,    26,    37,   508,    38,    23,    32,    36,   513,
     514,   515,   516,    33,   518,    27,    38,    36,    27,    37,
      27,    32,  1004,    27,    27,    40,    19,    32,    30,    27,
      27,    27,    27,    27,   539,   540,   565,   566,   567,   568,
     569,   570,   571,   572,   573,    32,   551,   552,   553,   554,
     555,   556,   557,   558,   559,   560,   561,   562,   563,   564,
      27,    38,   565,   566,   567,   568,   569,   570,   571,   572,
     573,    33,    27,   578,   579,   580,    33,    27,   583,   584,
      39,    33,    33,    19,    24,   590,   591,    32,   271,    21,
      23,    19,    21,    27,    43,    21,    33,   602,    89,   604,
      89,   606,    32,    30,    23,    89,    24,    32,    32,    30,
      30,    89,    22,    89,    89,   620,   621,   622,   623,   624,
     625,   626,   627,   628,   629,   630,   631,   632,   633,   634,
     635,    33,   637,    33,    32,    36,    32,    22,    33,    38,
      30,    89,    30,    23,    31,    23,    32,    19,    30,    23,
    1077,   656,   657,    20,    23,    36,    27,    19,    89,    23,
      23,    27,    23,    36,    43,    33,    89,   671,    27,    27,
     674,   675,   676,   677,    89,   679,    27,   681,    89,   683,
      23,   685,   686,    27,    39,    89,    89,    27,    27,    27,
      23,    33,    39,   697,    23,    36,    23,    31,    30,    23,
      89,    27,    30,    33,    20,    89,    89,    32,    30,    32,
      23,    21,    89,    32,    32,    36,    33,   721,    32,   723,
      40,   725,    33,    38,    30,    32,    31,    31,    40,    32,
     289,    33,    33,    31,    30,    30,    89,    20,    37,    39,
      30,    33,    21,    37,    37,   750,    37,    34,     5,    23,
      39,    39,   757,    33,   759,   760,   761,    39,   763,   764,
      27,    23,   445,   768,    23,   770,    24,   772,    33,    19,
      21,    23,    33,    33,    38,    38,    23,    23,    27,   784,
      89,   786,    37,    39,    38,    38,    24,    32,    22,    33,
     795,   796,   797,   798,   799,   800,   801,   802,   803,   804,
     805,   806,    38,   808,    89,   810,    38,   812,    39,    38,
      32,    39,    38,    38,    32,    39,    27,    32,    27,   848,
      33,    89,    39,    21,    36,    39,    34,    32,    38,    36,
      36,   835,   836,   837,  1261,   839,   840,    36,   842,   843,
      34,    38,   525,   872,   848,    34,   875,    38,   877,    36,
      38,   855,    19,    34,    38,    19,    30,    23,    33,   863,
     864,    32,   866,   867,   868,   869,    23,   871,   872,   873,
     874,   875,    21,   877,    39,    23,    32,    39,    39,    39,
      38,    24,    33,    27,    39,   914,   915,   446,    89,    39,
      30,   920,    39,    89,   899,   900,  1323,   902,   903,   904,
      39,    39,   907,    89,    39,    38,    89,   590,   591,    39,
      39,   914,   915,    30,    39,    23,    32,    38,    31,    38,
      32,    39,    31,    19,   607,   930,    89,   956,   957,    31,
      31,    38,    22,   938,    38,    22,    31,   496,   497,    38,
      34,    38,    30,    32,    89,    23,    39,   506,    33,    22,
     955,    25,    38,   956,   957,    89,   639,    22,    33,   518,
      23,    21,    23,    25,    23,   994,   995,   996,   997,   998,
      23,    23,    23,    23,    89,    89,    33,    21,    89,    89,
     539,   540,    37,    39,   988,  1014,  1015,    32,    27,    38,
     994,    38,    27,   997,    27,   998,    27,    40,    36,    33,
      32,    23,    32,    32,    22,    22,  1010,    33,    32,  1013,
    1014,  1015,    40,  1042,  1043,    40,  1045,    40,    38,    38,
      36,    33,    32,    89,    27,    40,    39,    38,    23,    38,
      38,    38,  1037,    27,    23,    27,    38,    23,    26,  1042,
    1043,    38,    27,    89,    26,    43,    33,    89,    39,    19,
      40,    27,  1081,  1082,  1059,    23,    27,    21,    23,    32,
      37,    40,    89,    21,    21,    40,    19,    21,    89,    19,
      36,    40,    34,    32,   757,   758,    31,    40,    27,    23,
     763,    32,    34,    23,   767,    33,    27,    32,    31,    36,
    1094,    37,    27,    23,   777,    31,    38,   656,   657,    32,
      27,    23,    26,    32,    43,    23,    38,  1112,    19,    32,
      38,   670,    21,   672,   673,    23,    19,    34,    39,   678,
      19,    37,    89,   682,   807,    32,   809,    23,    89,    21,
      21,   690,   691,    19,    32,    19,    21,    34,    32,    34,
    1144,    23,    23,    36,  1010,    23,    34,    23,    38,    36,
      39,    89,    31,    36,    34,    89,    23,    34,    23,    34,
      32,   720,    23,   722,    23,    34,    30,    37,    19,  1174,
      89,    19,    38,    19,  1203,    37,    30,    22,    19,    37,
      32,    30,    39,    89,    89,    89,    36,    34,    31,    42,
      23,    27,    34,    23,    19,    34,    36,    19,    22,  1203,
      38,    19,    23,    31,    19,    37,    19,    30,    19,    36,
      36,    31,    19,    22,    30,    89,   899,    27,    23,    38,
     903,    38,    36,    31,    36,    23,    32,  1232,    23,    19,
     913,    23,    19,    36,    31,   918,    40,    38,    22,    32,
      36,    23,    31,    31,    38,    23,    27,    23,    23,    23,
      23,  1203,    89,    38,    40,    38,    36,    36,   941,    26,
      23,    38,    23,    33,    36,    23,    23,    38,    37,    37,
      36,   954,    36,    22,    36,   834,    36,  1013,  1323,   838,
    1094,   964,   880,   966,   997,  1290,   286,   283,   847,   288,
     283,    50,   512,   512,    -1,    -1,    -1,    -1,    -1,   283,
      -1,    -1,    -1,   284,    -1,   288,   865,    -1,   286,   283,
      -1,   870,    -1,    -1,   873,   874,   288,   876,    -1,   878,
      -1,    -1,    -1,   283,    -1,    -1,    -1,   283,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   283,    -1,    -1,  1032,
    1033,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   984,   985,   986,   987,    -1,
      -1,   990,     3,     4,     5,     6,     7,     8,     9,    10,
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
     221,   222,    -1,   224,     3,     4,     5,     6,     7,     8,
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
     219,   220,   221,    -1,   223,   224,     3,     4,     5,     6,
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
     215,   216,   217,   218,   219,   220,   221,    -1,    -1,   224,
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
     223,     3,     4,     5,     6,     7,     8,     9,    10,    11,
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
     219,   220,   221
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     1,     3,    19,    21,    22,    25,    30,    31,    35,
      36,    37,    39,   228,   229,   230,   231,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   295,   296,   297,   298,
     299,   346,   350,    22,    30,    36,    23,    23,    27,    33,
      19,    39,    23,    23,    39,    32,     0,   225,   226,   280,
     281,     3,     4,     5,     6,     7,     8,     9,    10,    11,
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
     224,   271,   274,   275,   276,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,    22,    23,    23,    37,    38,    37,    19,    34,    27,
      31,    37,    30,    38,    20,    31,    37,   280,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,   273,   274,
     273,   273,   273,   273,   273,   273,   273,   273,     3,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,   276,
      21,    31,   232,   300,   333,    19,    21,    23,    31,    37,
      38,   238,   300,   301,   302,   303,   310,   311,   313,   318,
     319,   320,   321,   322,   323,   325,   327,   328,   329,   330,
     331,   332,   333,   334,   335,   336,   340,    31,   235,   331,
     236,   331,    31,   242,   332,    19,    31,   240,   319,   329,
     243,   319,   329,    19,    21,    31,   248,   301,   302,   303,
     318,   325,   328,   332,   334,    27,   244,   312,   313,   237,
     300,   333,    19,    23,    31,   239,   300,   317,   322,   326,
     327,   333,   349,    20,    21,    31,    37,    38,    40,   233,
     305,   306,   307,   308,   309,   310,   347,   234,   305,   306,
     307,   308,   309,   310,   347,   271,   277,   279,   241,   300,
      19,    19,    38,    38,    22,    38,    33,    23,    23,    37,
      19,    39,   274,    26,    27,   279,    39,    40,    26,    32,
      27,    23,    33,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,    27,
     279,   279,    27,   279,    39,    27,   279,   279,   279,   279,
      39,    26,    27,   279,    32,   279,   279,   279,   279,    39,
      21,    27,   279,   279,   279,   279,   279,   279,   279,    39,
      26,    27,    38,    33,    33,   271,   279,   279,    36,    38,
      36,    40,    38,    21,    21,    34,    20,    19,    22,   222,
     223,   266,   278,    22,    19,    19,    25,    22,    36,    38,
      27,   304,   307,   308,   309,   304,   304,   304,   304,   304,
     304,   304,   304,   304,   304,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,   258,   275,   291,   304,   304,
     304,   304,    22,   258,   258,    22,   258,   291,    22,    22,
     271,   271,   275,   275,    22,    19,    22,   258,   291,    37,
      32,   249,   265,   278,   294,   250,   264,   271,   262,   275,
     258,   291,    22,    26,    22,    19,    31,    37,    40,   245,
     319,   323,   324,   329,   333,   336,   337,   338,   339,   341,
     342,   343,   275,   275,   275,   275,    32,   348,   270,   271,
     275,    24,    19,    37,    36,    38,    27,   262,    23,    33,
      23,    38,    36,    37,    32,    27,   277,   277,    27,    27,
      32,    27,    27,    40,    19,    32,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
      30,   279,   279,   279,    27,   279,   279,    27,    27,    27,
     279,   279,    27,    32,    27,    38,    33,   279,   279,   279,
      27,    33,    27,    39,    27,    39,    33,    33,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,    19,   279,    24,    32,    21,    23,
      19,    21,    43,    27,    21,    32,    89,   222,   223,    33,
      30,    32,    32,    89,    23,    30,    24,   262,    20,    34,
     247,   344,   345,   262,   262,   264,   275,   271,   271,   275,
     275,   275,   275,   271,   258,    30,   258,   271,   275,    89,
     259,   275,   259,    89,    33,    89,   246,   271,   246,    33,
      32,    89,    36,    32,   263,   275,   265,   262,    33,    89,
      22,    22,    38,    30,    30,   262,   262,   262,   262,   262,
     262,   262,   262,   262,   262,   262,   262,   271,   275,   271,
     275,    31,   258,    23,    32,    23,    19,    30,    23,    20,
      36,    23,    27,    89,    19,    23,    23,    27,    36,    89,
      33,    43,    23,   279,   279,   279,   279,   279,   279,   279,
     279,    27,   279,   279,    27,    89,    27,   279,     4,    89,
      23,    27,    39,    89,   279,   279,    89,    27,    27,    27,
      23,    33,    39,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,     4,   279,     4,   279,    23,
     279,    36,    23,    30,    31,    89,    89,    23,    27,    30,
      32,    33,    20,    30,    32,    40,    38,    36,   262,   271,
     275,   275,   275,   271,   259,   275,    32,   260,   275,   260,
      32,    33,    32,   271,     7,     8,   268,   269,   271,   272,
     273,   274,   275,   278,    33,    30,    32,    31,    31,   262,
     263,    33,    32,    33,    89,    31,   252,   275,   253,   275,
     254,   271,   252,    22,    32,   258,   292,   293,   255,   275,
     256,   275,   291,   257,   271,   252,     7,     8,   261,   272,
     275,   270,   270,   268,   271,   268,   271,   266,    89,    30,
      30,    89,    40,    21,    20,    37,    39,    30,    37,    34,
      37,    33,    23,    21,   279,   279,   279,   279,   279,    37,
     279,    37,    39,    34,     4,   273,   273,     5,     6,    39,
      34,    37,    23,    33,   279,    39,    34,    89,    27,    23,
     279,    23,    33,   279,     4,     4,    24,    89,    19,    21,
      33,    33,    23,    38,    38,    23,    39,    38,    27,    37,
      23,   246,   271,   271,   246,   260,    38,   264,    38,    38,
      39,   268,     6,     6,   269,   273,    38,    39,    38,    32,
      22,   262,    38,    39,    33,    32,   253,    24,    32,   255,
     268,   268,    27,    21,    27,    32,    33,    27,    39,    36,
      34,    89,    38,    36,    21,    32,    36,   279,    36,    34,
      38,   273,   273,    34,    38,    36,    38,    19,    34,    38,
      39,    34,    19,    23,   279,    30,    33,    32,    23,    39,
      21,    32,    39,    39,    19,    23,    31,    89,    39,    23,
      38,    39,   265,    39,    39,    89,    39,    89,    39,    30,
      39,    89,    38,    39,    39,   256,    30,    39,    24,    33,
      32,    23,    38,    31,    38,    39,    32,    27,    22,    34,
      31,    89,    19,    31,   279,    31,    38,    22,    38,    22,
      31,    38,    22,    34,    34,    38,    30,    32,    33,    39,
      38,    89,    23,    89,    22,    25,    22,    23,    36,    33,
      23,    21,    25,    23,   263,    23,    89,    23,    89,    23,
      23,    89,    23,    33,    39,    89,    38,    38,    37,    21,
      32,    21,    22,    27,    27,    27,    40,    27,    36,    32,
      33,    23,    32,   279,    32,    22,    40,    22,    40,    32,
      21,    22,    40,    36,    38,    21,    34,    38,    33,    38,
      26,    23,    36,    33,    32,    89,    27,    40,    38,    38,
      39,    38,   261,    38,    23,    27,    23,    27,    38,    26,
      23,    27,    38,    89,    26,    33,    43,    39,    89,    19,
      40,    27,    89,    23,    27,    21,    23,    89,    37,    89,
      32,   279,    40,    21,    40,    21,    89,    19,    40,    21,
      21,    38,    19,    36,    34,    32,    31,    32,    27,    40,
      33,    37,    32,    23,    36,    34,    31,    38,    33,    34,
     251,   267,   278,   314,   315,   316,    27,    23,    27,    23,
      31,    32,    27,    23,    26,    43,    32,    38,    23,    38,
      19,    32,    21,    23,    39,    34,    37,    89,    19,    19,
      89,    32,    23,   279,    21,    21,    19,    32,    21,    89,
      19,    34,    32,    34,    23,    23,    36,    38,    39,    34,
      36,    34,    31,    89,    36,   267,    23,    23,    34,    23,
      23,    34,    32,    23,    23,    30,    37,    89,    34,    38,
      19,    19,    37,    19,    22,    37,    30,    89,    19,    32,
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
#line 100 "lscp.y"
    { return LSCP_DONE; }
    break;

  case 5:
#line 101 "lscp.y"
    { return LSCP_DONE; }
    break;

  case 6:
#line 102 "lscp.y"
    { LSCPSERVER->AnswerClient((yyvsp[(1) - (1)].String)); return LSCP_DONE; }
    break;

  case 7:
#line 103 "lscp.y"
    { LSCPSERVER->AnswerClient("ERR:0:Unknown command.\r\n"); RESTART; return LSCP_SYNTAX_ERROR; }
    break;

  case 13:
#line 113 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                }
    break;

  case 14:
#line 114 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                }
    break;

  case 15:
#line 115 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                }
    break;

  case 16:
#line 116 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                }
    break;

  case 17:
#line 117 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                }
    break;

  case 18:
#line 118 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                }
    break;

  case 19:
#line 119 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                }
    break;

  case 20:
#line 120 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                }
    break;

  case 21:
#line 121 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                }
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
    { (yyval.String) = LSCPSERVER->AddChannel();                          }
    break;

  case 31:
#line 133 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddMidiInstrumentMap();                }
    break;

  case 32:
#line 134 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddMidiInstrumentMap((yyvsp[(3) - (3)].String));              }
    break;

  case 33:
#line 137 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_channel_count);     }
    break;

  case 34:
#line 138 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_voice_count);       }
    break;

  case 35:
#line 139 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_stream_count);      }
    break;

  case 36:
#line 140 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_buffer_fill);       }
    break;

  case 37:
#line 141 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_channel_info);      }
    break;

  case 38:
#line 142 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_misc);              }
    break;

  case 39:
#line 143 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_total_voice_count); }
    break;

  case 40:
#line 146 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_channel_count);     }
    break;

  case 41:
#line 147 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_voice_count);       }
    break;

  case 42:
#line 148 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_stream_count);      }
    break;

  case 43:
#line 149 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_buffer_fill);       }
    break;

  case 44:
#line 150 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_channel_info);      }
    break;

  case 45:
#line 151 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_misc);              }
    break;

  case 46:
#line 152 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_total_voice_count); }
    break;

  case 47:
#line 155 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping((yyvsp[(3) - (15)].Number),(yyvsp[(5) - (15)].Number),(yyvsp[(7) - (15)].Number),(yyvsp[(9) - (15)].String),(yyvsp[(11) - (15)].String),(yyvsp[(13) - (15)].Number),(yyvsp[(15) - (15)].Dotnum),MidiInstrumentMapper::VOID,""); }
    break;

  case 48:
#line 156 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping((yyvsp[(3) - (17)].Number),(yyvsp[(5) - (17)].Number),(yyvsp[(7) - (17)].Number),(yyvsp[(9) - (17)].String),(yyvsp[(11) - (17)].String),(yyvsp[(13) - (17)].Number),(yyvsp[(15) - (17)].Dotnum),(yyvsp[(17) - (17)].LoadMode),""); }
    break;

  case 49:
#line 157 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping((yyvsp[(3) - (17)].Number),(yyvsp[(5) - (17)].Number),(yyvsp[(7) - (17)].Number),(yyvsp[(9) - (17)].String),(yyvsp[(11) - (17)].String),(yyvsp[(13) - (17)].Number),(yyvsp[(15) - (17)].Dotnum),MidiInstrumentMapper::VOID,(yyvsp[(17) - (17)].String)); }
    break;

  case 50:
#line 158 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping((yyvsp[(3) - (19)].Number),(yyvsp[(5) - (19)].Number),(yyvsp[(7) - (19)].Number),(yyvsp[(9) - (19)].String),(yyvsp[(11) - (19)].String),(yyvsp[(13) - (19)].Number),(yyvsp[(15) - (19)].Dotnum),(yyvsp[(17) - (19)].LoadMode),(yyvsp[(19) - (19)].String)); }
    break;

  case 51:
#line 161 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveMIDIInstrumentMapping((yyvsp[(3) - (7)].Number),(yyvsp[(5) - (7)].Number),(yyvsp[(7) - (7)].Number)); }
    break;

  case 52:
#line 164 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveChannel((yyvsp[(3) - (3)].Number));             }
    break;

  case 53:
#line 165 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveMidiInstrumentMap((yyvsp[(3) - (3)].Number));   }
    break;

  case 54:
#line 166 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveAllMidiInstrumentMaps(); }
    break;

  case 55:
#line 169 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAvailableEngines();                          }
    break;

  case 56:
#line 170 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAvailableMidiInputDrivers();                 }
    break;

  case 57:
#line 171 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDriverInfo((yyvsp[(5) - (5)].String));                     }
    break;

  case 58:
#line 172 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDriverParameterInfo((yyvsp[(5) - (7)].String), (yyvsp[(7) - (7)].String));        }
    break;

  case 59:
#line 173 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDriverParameterInfo((yyvsp[(5) - (9)].String), (yyvsp[(7) - (9)].String), (yyvsp[(9) - (9)].KeyValList));    }
    break;

  case 60:
#line 174 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAvailableAudioOutputDrivers();               }
    break;

  case 61:
#line 175 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDriverInfo((yyvsp[(5) - (5)].String));                   }
    break;

  case 62:
#line 176 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDriverParameterInfo((yyvsp[(5) - (7)].String), (yyvsp[(7) - (7)].String));      }
    break;

  case 63:
#line 177 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDriverParameterInfo((yyvsp[(5) - (9)].String), (yyvsp[(7) - (9)].String), (yyvsp[(9) - (9)].KeyValList));  }
    break;

  case 64:
#line 178 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDeviceCount();                    }
    break;

  case 65:
#line 179 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDeviceCount();                      }
    break;

  case 66:
#line 180 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDeviceInfo((yyvsp[(5) - (5)].Number));                   }
    break;

  case 67:
#line 181 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDeviceInfo((yyvsp[(5) - (5)].Number));                     }
    break;

  case 68:
#line 182 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputPortInfo((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number));                   }
    break;

  case 69:
#line 183 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputPortParameterInfo((yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].Number), (yyvsp[(9) - (9)].String));      }
    break;

  case 70:
#line 184 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputChannelInfo((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number));              }
    break;

  case 71:
#line 185 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputChannelParameterInfo((yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].Number), (yyvsp[(9) - (9)].String)); }
    break;

  case 72:
#line 186 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetChannels();                                  }
    break;

  case 73:
#line 187 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetChannelInfo((yyvsp[(5) - (5)].Number));                             }
    break;

  case 74:
#line 188 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetBufferFill((yyvsp[(5) - (7)].FillResponse), (yyvsp[(7) - (7)].Number));                          }
    break;

  case 75:
#line 189 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetStreamCount((yyvsp[(5) - (5)].Number));                             }
    break;

  case 76:
#line 190 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetVoiceCount((yyvsp[(5) - (5)].Number));                              }
    break;

  case 77:
#line 191 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetEngineInfo((yyvsp[(5) - (5)].String));                              }
    break;

  case 78:
#line 192 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetServerInfo();                                }
    break;

  case 79:
#line 193 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetTotalVoiceCount();                                }
    break;

  case 80:
#line 194 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetTotalVoiceCountMax();                        }
    break;

  case 81:
#line 195 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInstrumentMappings((yyvsp[(3) - (3)].Number));                  }
    break;

  case 82:
#line 196 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAllMidiInstrumentMappings();                 }
    break;

  case 83:
#line 197 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInstrumentMapping((yyvsp[(5) - (9)].Number),(yyvsp[(7) - (9)].Number),(yyvsp[(9) - (9)].Number));             }
    break;

  case 84:
#line 198 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInstrumentMaps();                        }
    break;

  case 85:
#line 199 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInstrumentMap((yyvsp[(5) - (5)].Number));                       }
    break;

  case 86:
#line 202 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputDeviceParameter((yyvsp[(3) - (7)].Number), (yyvsp[(5) - (7)].String), (yyvsp[(7) - (7)].String));      }
    break;

  case 87:
#line 203 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputChannelParameter((yyvsp[(3) - (9)].Number), (yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].String), (yyvsp[(9) - (9)].String)); }
    break;

  case 88:
#line 204 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMidiInputDeviceParameter((yyvsp[(3) - (7)].Number), (yyvsp[(5) - (7)].String), (yyvsp[(7) - (7)].String));        }
    break;

  case 89:
#line 205 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMidiInputPortParameter((yyvsp[(3) - (9)].Number), (yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].String), (yyvsp[(9) - (9)].String));      }
    break;

  case 90:
#line 206 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                         }
    break;

  case 91:
#line 207 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMidiInstrumentMapName((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].String));               }
    break;

  case 92:
#line 208 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetEcho((yyparse_param_t*) yyparse_param, (yyvsp[(3) - (3)].Dotnum));  }
    break;

  case 93:
#line 211 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateAudioOutputDevice((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].KeyValList)); }
    break;

  case 94:
#line 212 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateAudioOutputDevice((yyvsp[(3) - (3)].String));    }
    break;

  case 95:
#line 213 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateMidiInputDevice((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].KeyValList));   }
    break;

  case 96:
#line 214 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateMidiInputDevice((yyvsp[(3) - (3)].String));      }
    break;

  case 97:
#line 217 "lscp.y"
    { (yyval.String) = LSCPSERVER->ResetChannel((yyvsp[(3) - (3)].Number)); }
    break;

  case 98:
#line 220 "lscp.y"
    { (yyval.String) = LSCPSERVER->ClearMidiInstrumentMappings((yyvsp[(3) - (3)].Number));  }
    break;

  case 99:
#line 221 "lscp.y"
    { (yyval.String) = LSCPSERVER->ClearAllMidiInstrumentMappings(); }
    break;

  case 100:
#line 224 "lscp.y"
    { (yyval.String) = LSCPSERVER->DestroyAudioOutputDevice((yyvsp[(3) - (3)].Number)); }
    break;

  case 101:
#line 225 "lscp.y"
    { (yyval.String) = LSCPSERVER->DestroyMidiInputDevice((yyvsp[(3) - (3)].Number));   }
    break;

  case 102:
#line 228 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String); }
    break;

  case 103:
#line 229 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String); }
    break;

  case 104:
#line 232 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputDevice((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));      }
    break;

  case 105:
#line 233 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputChannel((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number), (yyvsp[(3) - (7)].Number)); }
    break;

  case 106:
#line 234 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputType((yyvsp[(5) - (5)].String), (yyvsp[(3) - (5)].Number));        }
    break;

  case 107:
#line 235 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInput((yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].Number), (yyvsp[(9) - (9)].Number), (yyvsp[(3) - (9)].Number));      }
    break;

  case 108:
#line 236 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputDevice((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));        }
    break;

  case 109:
#line 237 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputPort((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));          }
    break;

  case 110:
#line 238 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputChannel((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));       }
    break;

  case 111:
#line 239 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputType((yyvsp[(5) - (5)].String), (yyvsp[(3) - (5)].Number));          }
    break;

  case 112:
#line 240 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetVolume((yyvsp[(5) - (5)].Dotnum), (yyvsp[(3) - (5)].Number));                 }
    break;

  case 113:
#line 241 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMute((yyvsp[(5) - (5)].Dotnum), (yyvsp[(3) - (5)].Number));            }
    break;

  case 114:
#line 242 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelSolo((yyvsp[(5) - (5)].Dotnum), (yyvsp[(3) - (5)].Number));            }
    break;

  case 115:
#line 243 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMap((yyvsp[(3) - (5)].Number), (yyvsp[(5) - (5)].Number));             }
    break;

  case 116:
#line 244 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMap((yyvsp[(3) - (5)].Number), -1);             }
    break;

  case 117:
#line 245 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMap((yyvsp[(3) - (5)].Number), -2);             }
    break;

  case 118:
#line 248 "lscp.y"
    { (yyval.KeyValList)[(yyvsp[(1) - (3)].String)] = (yyvsp[(3) - (3)].String);          }
    break;

  case 119:
#line 249 "lscp.y"
    { (yyval.KeyValList) = (yyvsp[(1) - (5)].KeyValList); (yyval.KeyValList)[(yyvsp[(3) - (5)].String)] = (yyvsp[(5) - (5)].String); }
    break;

  case 120:
#line 252 "lscp.y"
    { (yyval.FillResponse) = fill_response_bytes;      }
    break;

  case 121:
#line 253 "lscp.y"
    { (yyval.FillResponse) = fill_response_percentage; }
    break;

  case 122:
#line 256 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDevices();           }
    break;

  case 123:
#line 257 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDevices();             }
    break;

  case 124:
#line 258 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListChannels();                    }
    break;

  case 125:
#line 259 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableEngines();            }
    break;

  case 126:
#line 260 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableMidiInputDrivers();   }
    break;

  case 127:
#line 261 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableAudioOutputDrivers(); }
    break;

  case 128:
#line 262 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListMidiInstrumentMappings((yyvsp[(3) - (3)].Number));    }
    break;

  case 129:
#line 263 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAllMidiInstrumentMappings();   }
    break;

  case 130:
#line 264 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListMidiInstrumentMaps();          }
    break;

  case 131:
#line 267 "lscp.y"
    { (yyval.String) = LSCPSERVER->LoadInstrument((yyvsp[(1) - (5)].String), (yyvsp[(3) - (5)].Number), (yyvsp[(5) - (5)].Number));       }
    break;

  case 132:
#line 268 "lscp.y"
    { (yyval.String) = LSCPSERVER->LoadInstrument((yyvsp[(3) - (7)].String), (yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number), true); }
    break;

  case 133:
#line 271 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetEngineType((yyvsp[(1) - (3)].String), (yyvsp[(3) - (3)].Number)); }
    break;

  case 134:
#line 274 "lscp.y"
    { (yyval.LoadMode) = MidiInstrumentMapper::ON_DEMAND;      }
    break;

  case 135:
#line 275 "lscp.y"
    { (yyval.LoadMode) = MidiInstrumentMapper::ON_DEMAND_HOLD; }
    break;

  case 136:
#line 276 "lscp.y"
    { (yyval.LoadMode) = MidiInstrumentMapper::PERSISTENT;     }
    break;

  case 142:
#line 292 "lscp.y"
    { (yyval.Number) = 16; }
    break;

  case 148:
#line 308 "lscp.y"
    { (yyval.Dotnum) = (yyvsp[(1) - (1)].Number); }
    break;

  case 156:
#line 330 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (3)].String) + "," + (yyvsp[(3) - (3)].String); }
    break;

  case 159:
#line 335 "lscp.y"
    { std::stringstream ss; ss << "\'" << (yyvsp[(1) - (1)].Number) << "\'"; (yyval.String) = ss.str(); }
    break;

  case 160:
#line 336 "lscp.y"
    { std::stringstream ss; ss << "\'" << (yyvsp[(1) - (1)].Dotnum) << "\'"; (yyval.String) = ss.str(); }
    break;

  case 161:
#line 344 "lscp.y"
    { (yyval.Dotnum) = (yyvsp[(1) - (1)].Number); }
    break;

  case 162:
#line 345 "lscp.y"
    { (yyval.Dotnum) = -1; }
    break;

  case 163:
#line 348 "lscp.y"
    { std::string s; s = (yyvsp[(1) - (1)].Char); (yyval.String) = s; }
    break;

  case 164:
#line 349 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + (yyvsp[(2) - (2)].Char);                  }
    break;

  case 165:
#line 352 "lscp.y"
    { (yyval.Dotnum) = atof(String((yyvsp[(1) - (3)].String) + "." + (yyvsp[(3) - (3)].String)).c_str());                         }
    break;

  case 166:
#line 353 "lscp.y"
    { String s = "+"; s += (yyvsp[(2) - (4)].String); s += "."; s += (yyvsp[(4) - (4)].String); (yyval.Dotnum) = atof(s.c_str()); }
    break;

  case 167:
#line 354 "lscp.y"
    { (yyval.Dotnum) = atof(String("-" + (yyvsp[(2) - (4)].String) + "." + (yyvsp[(4) - (4)].String)).c_str());                   }
    break;

  case 168:
#line 358 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (1)].Char);      }
    break;

  case 169:
#line 359 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + (yyvsp[(2) - (2)].Char); }
    break;

  case 170:
#line 362 "lscp.y"
    { (yyval.Char) = '0'; }
    break;

  case 171:
#line 363 "lscp.y"
    { (yyval.Char) = '1'; }
    break;

  case 172:
#line 364 "lscp.y"
    { (yyval.Char) = '2'; }
    break;

  case 173:
#line 365 "lscp.y"
    { (yyval.Char) = '3'; }
    break;

  case 174:
#line 366 "lscp.y"
    { (yyval.Char) = '4'; }
    break;

  case 175:
#line 367 "lscp.y"
    { (yyval.Char) = '5'; }
    break;

  case 176:
#line 368 "lscp.y"
    { (yyval.Char) = '6'; }
    break;

  case 177:
#line 369 "lscp.y"
    { (yyval.Char) = '7'; }
    break;

  case 178:
#line 370 "lscp.y"
    { (yyval.Char) = '8'; }
    break;

  case 179:
#line 371 "lscp.y"
    { (yyval.Char) = '9'; }
    break;

  case 180:
#line 374 "lscp.y"
    { (yyval.Number) = atoi(String(1, (yyvsp[(1) - (1)].Char)).c_str());      }
    break;

  case 181:
#line 375 "lscp.y"
    { (yyval.Number) = atoi(String(String("1") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 182:
#line 376 "lscp.y"
    { (yyval.Number) = atoi(String(String("2") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 183:
#line 377 "lscp.y"
    { (yyval.Number) = atoi(String(String("3") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 184:
#line 378 "lscp.y"
    { (yyval.Number) = atoi(String(String("4") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 185:
#line 379 "lscp.y"
    { (yyval.Number) = atoi(String(String("5") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 186:
#line 380 "lscp.y"
    { (yyval.Number) = atoi(String(String("6") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 187:
#line 381 "lscp.y"
    { (yyval.Number) = atoi(String(String("7") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 188:
#line 382 "lscp.y"
    { (yyval.Number) = atoi(String(String("8") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 189:
#line 383 "lscp.y"
    { (yyval.Number) = atoi(String(String("9") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 190:
#line 385 "lscp.y"
    { (yyval.Char) = 'A'; }
    break;

  case 191:
#line 385 "lscp.y"
    { (yyval.Char) = 'B'; }
    break;

  case 192:
#line 385 "lscp.y"
    { (yyval.Char) = 'C'; }
    break;

  case 193:
#line 385 "lscp.y"
    { (yyval.Char) = 'D'; }
    break;

  case 194:
#line 385 "lscp.y"
    { (yyval.Char) = 'E'; }
    break;

  case 195:
#line 385 "lscp.y"
    { (yyval.Char) = 'F'; }
    break;

  case 196:
#line 385 "lscp.y"
    { (yyval.Char) = 'G'; }
    break;

  case 197:
#line 385 "lscp.y"
    { (yyval.Char) = 'H'; }
    break;

  case 198:
#line 385 "lscp.y"
    { (yyval.Char) = 'I'; }
    break;

  case 199:
#line 385 "lscp.y"
    { (yyval.Char) = 'J'; }
    break;

  case 200:
#line 385 "lscp.y"
    { (yyval.Char) = 'K'; }
    break;

  case 201:
#line 385 "lscp.y"
    { (yyval.Char) = 'L'; }
    break;

  case 202:
#line 385 "lscp.y"
    { (yyval.Char) = 'M'; }
    break;

  case 203:
#line 385 "lscp.y"
    { (yyval.Char) = 'N'; }
    break;

  case 204:
#line 385 "lscp.y"
    { (yyval.Char) = 'O'; }
    break;

  case 205:
#line 385 "lscp.y"
    { (yyval.Char) = 'P'; }
    break;

  case 206:
#line 385 "lscp.y"
    { (yyval.Char) = 'Q'; }
    break;

  case 207:
#line 385 "lscp.y"
    { (yyval.Char) = 'R'; }
    break;

  case 208:
#line 385 "lscp.y"
    { (yyval.Char) = 'S'; }
    break;

  case 209:
#line 385 "lscp.y"
    { (yyval.Char) = 'T'; }
    break;

  case 210:
#line 385 "lscp.y"
    { (yyval.Char) = 'U'; }
    break;

  case 211:
#line 385 "lscp.y"
    { (yyval.Char) = 'V'; }
    break;

  case 212:
#line 385 "lscp.y"
    { (yyval.Char) = 'W'; }
    break;

  case 213:
#line 385 "lscp.y"
    { (yyval.Char) = 'X'; }
    break;

  case 214:
#line 385 "lscp.y"
    { (yyval.Char) = 'Y'; }
    break;

  case 215:
#line 385 "lscp.y"
    { (yyval.Char) = 'Z'; }
    break;

  case 216:
#line 386 "lscp.y"
    { (yyval.Char) = 'a'; }
    break;

  case 217:
#line 386 "lscp.y"
    { (yyval.Char) = 'b'; }
    break;

  case 218:
#line 386 "lscp.y"
    { (yyval.Char) = 'c'; }
    break;

  case 219:
#line 386 "lscp.y"
    { (yyval.Char) = 'd'; }
    break;

  case 220:
#line 386 "lscp.y"
    { (yyval.Char) = 'e'; }
    break;

  case 221:
#line 386 "lscp.y"
    { (yyval.Char) = 'f'; }
    break;

  case 222:
#line 386 "lscp.y"
    { (yyval.Char) = 'g'; }
    break;

  case 223:
#line 386 "lscp.y"
    { (yyval.Char) = 'h'; }
    break;

  case 224:
#line 386 "lscp.y"
    { (yyval.Char) = 'i'; }
    break;

  case 225:
#line 386 "lscp.y"
    { (yyval.Char) = 'j'; }
    break;

  case 226:
#line 386 "lscp.y"
    { (yyval.Char) = 'k'; }
    break;

  case 227:
#line 386 "lscp.y"
    { (yyval.Char) = 'l'; }
    break;

  case 228:
#line 386 "lscp.y"
    { (yyval.Char) = 'm'; }
    break;

  case 229:
#line 386 "lscp.y"
    { (yyval.Char) = 'n'; }
    break;

  case 230:
#line 386 "lscp.y"
    { (yyval.Char) = 'o'; }
    break;

  case 231:
#line 386 "lscp.y"
    { (yyval.Char) = 'p'; }
    break;

  case 232:
#line 386 "lscp.y"
    { (yyval.Char) = 'q'; }
    break;

  case 233:
#line 386 "lscp.y"
    { (yyval.Char) = 'r'; }
    break;

  case 234:
#line 386 "lscp.y"
    { (yyval.Char) = 's'; }
    break;

  case 235:
#line 386 "lscp.y"
    { (yyval.Char) = 't'; }
    break;

  case 236:
#line 386 "lscp.y"
    { (yyval.Char) = 'u'; }
    break;

  case 237:
#line 386 "lscp.y"
    { (yyval.Char) = 'v'; }
    break;

  case 238:
#line 386 "lscp.y"
    { (yyval.Char) = 'w'; }
    break;

  case 239:
#line 386 "lscp.y"
    { (yyval.Char) = 'x'; }
    break;

  case 240:
#line 386 "lscp.y"
    { (yyval.Char) = 'y'; }
    break;

  case 241:
#line 386 "lscp.y"
    { (yyval.Char) = 'z'; }
    break;

  case 242:
#line 387 "lscp.y"
    { (yyval.Char) = '0'; }
    break;

  case 243:
#line 387 "lscp.y"
    { (yyval.Char) = '1'; }
    break;

  case 244:
#line 387 "lscp.y"
    { (yyval.Char) = '2'; }
    break;

  case 245:
#line 387 "lscp.y"
    { (yyval.Char) = '3'; }
    break;

  case 246:
#line 387 "lscp.y"
    { (yyval.Char) = '4'; }
    break;

  case 247:
#line 387 "lscp.y"
    { (yyval.Char) = '5'; }
    break;

  case 248:
#line 387 "lscp.y"
    { (yyval.Char) = '6'; }
    break;

  case 249:
#line 387 "lscp.y"
    { (yyval.Char) = '7'; }
    break;

  case 250:
#line 387 "lscp.y"
    { (yyval.Char) = '8'; }
    break;

  case 251:
#line 387 "lscp.y"
    { (yyval.Char) = '9'; }
    break;

  case 252:
#line 388 "lscp.y"
    { (yyval.Char) = '!'; }
    break;

  case 253:
#line 388 "lscp.y"
    { (yyval.Char) = '#'; }
    break;

  case 254:
#line 388 "lscp.y"
    { (yyval.Char) = '$'; }
    break;

  case 255:
#line 388 "lscp.y"
    { (yyval.Char) = '%'; }
    break;

  case 256:
#line 388 "lscp.y"
    { (yyval.Char) = '&'; }
    break;

  case 257:
#line 388 "lscp.y"
    { (yyval.Char) = '('; }
    break;

  case 258:
#line 388 "lscp.y"
    { (yyval.Char) = ')'; }
    break;

  case 259:
#line 388 "lscp.y"
    { (yyval.Char) = '*'; }
    break;

  case 260:
#line 388 "lscp.y"
    { (yyval.Char) = '+'; }
    break;

  case 261:
#line 388 "lscp.y"
    { (yyval.Char) = '-'; }
    break;

  case 262:
#line 388 "lscp.y"
    { (yyval.Char) = '.'; }
    break;

  case 263:
#line 388 "lscp.y"
    { (yyval.Char) = ','; }
    break;

  case 264:
#line 388 "lscp.y"
    { (yyval.Char) = '/'; }
    break;

  case 265:
#line 389 "lscp.y"
    { (yyval.Char) = ':'; }
    break;

  case 266:
#line 389 "lscp.y"
    { (yyval.Char) = ';'; }
    break;

  case 267:
#line 389 "lscp.y"
    { (yyval.Char) = '<'; }
    break;

  case 268:
#line 389 "lscp.y"
    { (yyval.Char) = '='; }
    break;

  case 269:
#line 389 "lscp.y"
    { (yyval.Char) = '>'; }
    break;

  case 270:
#line 389 "lscp.y"
    { (yyval.Char) = '?'; }
    break;

  case 271:
#line 389 "lscp.y"
    { (yyval.Char) = '@'; }
    break;

  case 272:
#line 390 "lscp.y"
    { (yyval.Char) = '['; }
    break;

  case 273:
#line 390 "lscp.y"
    { (yyval.Char) = '\\'; }
    break;

  case 274:
#line 390 "lscp.y"
    { (yyval.Char) = ']'; }
    break;

  case 275:
#line 390 "lscp.y"
    { (yyval.Char) = '^'; }
    break;

  case 276:
#line 390 "lscp.y"
    { (yyval.Char) = '_'; }
    break;

  case 277:
#line 391 "lscp.y"
    { (yyval.Char) = '{'; }
    break;

  case 278:
#line 391 "lscp.y"
    { (yyval.Char) = '|'; }
    break;

  case 279:
#line 391 "lscp.y"
    { (yyval.Char) = '}'; }
    break;

  case 280:
#line 391 "lscp.y"
    { (yyval.Char) = '~'; }
    break;

  case 281:
#line 392 "lscp.y"
    { (yyval.Char) = '\200'; }
    break;

  case 282:
#line 392 "lscp.y"
    { (yyval.Char) = '\201'; }
    break;

  case 283:
#line 392 "lscp.y"
    { (yyval.Char) = '\202'; }
    break;

  case 284:
#line 393 "lscp.y"
    { (yyval.Char) = '\203'; }
    break;

  case 285:
#line 393 "lscp.y"
    { (yyval.Char) = '\204'; }
    break;

  case 286:
#line 393 "lscp.y"
    { (yyval.Char) = '\205'; }
    break;

  case 287:
#line 394 "lscp.y"
    { (yyval.Char) = '\206'; }
    break;

  case 288:
#line 394 "lscp.y"
    { (yyval.Char) = '\207'; }
    break;

  case 289:
#line 394 "lscp.y"
    { (yyval.Char) = '\210'; }
    break;

  case 290:
#line 395 "lscp.y"
    { (yyval.Char) = '\211'; }
    break;

  case 291:
#line 395 "lscp.y"
    { (yyval.Char) = '\212'; }
    break;

  case 292:
#line 395 "lscp.y"
    { (yyval.Char) = '\213'; }
    break;

  case 293:
#line 396 "lscp.y"
    { (yyval.Char) = '\214'; }
    break;

  case 294:
#line 396 "lscp.y"
    { (yyval.Char) = '\215'; }
    break;

  case 295:
#line 396 "lscp.y"
    { (yyval.Char) = '\216'; }
    break;

  case 296:
#line 397 "lscp.y"
    { (yyval.Char) = '\217'; }
    break;

  case 297:
#line 397 "lscp.y"
    { (yyval.Char) = '\220'; }
    break;

  case 298:
#line 397 "lscp.y"
    { (yyval.Char) = '\221'; }
    break;

  case 299:
#line 398 "lscp.y"
    { (yyval.Char) = '\222'; }
    break;

  case 300:
#line 398 "lscp.y"
    { (yyval.Char) = '\223'; }
    break;

  case 301:
#line 398 "lscp.y"
    { (yyval.Char) = '\224'; }
    break;

  case 302:
#line 399 "lscp.y"
    { (yyval.Char) = '\225'; }
    break;

  case 303:
#line 399 "lscp.y"
    { (yyval.Char) = '\226'; }
    break;

  case 304:
#line 399 "lscp.y"
    { (yyval.Char) = '\227'; }
    break;

  case 305:
#line 400 "lscp.y"
    { (yyval.Char) = '\230'; }
    break;

  case 306:
#line 400 "lscp.y"
    { (yyval.Char) = '\231'; }
    break;

  case 307:
#line 400 "lscp.y"
    { (yyval.Char) = '\232'; }
    break;

  case 308:
#line 401 "lscp.y"
    { (yyval.Char) = '\233'; }
    break;

  case 309:
#line 401 "lscp.y"
    { (yyval.Char) = '\234'; }
    break;

  case 310:
#line 401 "lscp.y"
    { (yyval.Char) = '\235'; }
    break;

  case 311:
#line 402 "lscp.y"
    { (yyval.Char) = '\236'; }
    break;

  case 312:
#line 402 "lscp.y"
    { (yyval.Char) = '\237'; }
    break;

  case 313:
#line 402 "lscp.y"
    { (yyval.Char) = '\240'; }
    break;

  case 314:
#line 403 "lscp.y"
    { (yyval.Char) = '\241'; }
    break;

  case 315:
#line 403 "lscp.y"
    { (yyval.Char) = '\242'; }
    break;

  case 316:
#line 403 "lscp.y"
    { (yyval.Char) = '\243'; }
    break;

  case 317:
#line 404 "lscp.y"
    { (yyval.Char) = '\244'; }
    break;

  case 318:
#line 404 "lscp.y"
    { (yyval.Char) = '\245'; }
    break;

  case 319:
#line 404 "lscp.y"
    { (yyval.Char) = '\246'; }
    break;

  case 320:
#line 405 "lscp.y"
    { (yyval.Char) = '\247'; }
    break;

  case 321:
#line 405 "lscp.y"
    { (yyval.Char) = '\250'; }
    break;

  case 322:
#line 405 "lscp.y"
    { (yyval.Char) = '\251'; }
    break;

  case 323:
#line 406 "lscp.y"
    { (yyval.Char) = '\252'; }
    break;

  case 324:
#line 406 "lscp.y"
    { (yyval.Char) = '\253'; }
    break;

  case 325:
#line 406 "lscp.y"
    { (yyval.Char) = '\254'; }
    break;

  case 326:
#line 407 "lscp.y"
    { (yyval.Char) = '\255'; }
    break;

  case 327:
#line 407 "lscp.y"
    { (yyval.Char) = '\256'; }
    break;

  case 328:
#line 407 "lscp.y"
    { (yyval.Char) = '\257'; }
    break;

  case 329:
#line 408 "lscp.y"
    { (yyval.Char) = '\260'; }
    break;

  case 330:
#line 408 "lscp.y"
    { (yyval.Char) = '\261'; }
    break;

  case 331:
#line 408 "lscp.y"
    { (yyval.Char) = '\262'; }
    break;

  case 332:
#line 409 "lscp.y"
    { (yyval.Char) = '\263'; }
    break;

  case 333:
#line 409 "lscp.y"
    { (yyval.Char) = '\264'; }
    break;

  case 334:
#line 409 "lscp.y"
    { (yyval.Char) = '\265'; }
    break;

  case 335:
#line 410 "lscp.y"
    { (yyval.Char) = '\266'; }
    break;

  case 336:
#line 410 "lscp.y"
    { (yyval.Char) = '\267'; }
    break;

  case 337:
#line 410 "lscp.y"
    { (yyval.Char) = '\270'; }
    break;

  case 338:
#line 411 "lscp.y"
    { (yyval.Char) = '\271'; }
    break;

  case 339:
#line 411 "lscp.y"
    { (yyval.Char) = '\272'; }
    break;

  case 340:
#line 411 "lscp.y"
    { (yyval.Char) = '\273'; }
    break;

  case 341:
#line 412 "lscp.y"
    { (yyval.Char) = '\274'; }
    break;

  case 342:
#line 412 "lscp.y"
    { (yyval.Char) = '\275'; }
    break;

  case 343:
#line 412 "lscp.y"
    { (yyval.Char) = '\276'; }
    break;

  case 344:
#line 413 "lscp.y"
    { (yyval.Char) = '\277'; }
    break;

  case 345:
#line 413 "lscp.y"
    { (yyval.Char) = '\300'; }
    break;

  case 346:
#line 413 "lscp.y"
    { (yyval.Char) = '\301'; }
    break;

  case 347:
#line 414 "lscp.y"
    { (yyval.Char) = '\302'; }
    break;

  case 348:
#line 414 "lscp.y"
    { (yyval.Char) = '\303'; }
    break;

  case 349:
#line 414 "lscp.y"
    { (yyval.Char) = '\304'; }
    break;

  case 350:
#line 415 "lscp.y"
    { (yyval.Char) = '\305'; }
    break;

  case 351:
#line 415 "lscp.y"
    { (yyval.Char) = '\306'; }
    break;

  case 352:
#line 415 "lscp.y"
    { (yyval.Char) = '\307'; }
    break;

  case 353:
#line 416 "lscp.y"
    { (yyval.Char) = '\310'; }
    break;

  case 354:
#line 416 "lscp.y"
    { (yyval.Char) = '\311'; }
    break;

  case 355:
#line 416 "lscp.y"
    { (yyval.Char) = '\312'; }
    break;

  case 356:
#line 417 "lscp.y"
    { (yyval.Char) = '\313'; }
    break;

  case 357:
#line 417 "lscp.y"
    { (yyval.Char) = '\314'; }
    break;

  case 358:
#line 417 "lscp.y"
    { (yyval.Char) = '\315'; }
    break;

  case 359:
#line 418 "lscp.y"
    { (yyval.Char) = '\316'; }
    break;

  case 360:
#line 418 "lscp.y"
    { (yyval.Char) = '\317'; }
    break;

  case 361:
#line 418 "lscp.y"
    { (yyval.Char) = '\320'; }
    break;

  case 362:
#line 419 "lscp.y"
    { (yyval.Char) = '\321'; }
    break;

  case 363:
#line 419 "lscp.y"
    { (yyval.Char) = '\322'; }
    break;

  case 364:
#line 419 "lscp.y"
    { (yyval.Char) = '\323'; }
    break;

  case 365:
#line 420 "lscp.y"
    { (yyval.Char) = '\324'; }
    break;

  case 366:
#line 420 "lscp.y"
    { (yyval.Char) = '\325'; }
    break;

  case 367:
#line 420 "lscp.y"
    { (yyval.Char) = '\326'; }
    break;

  case 368:
#line 421 "lscp.y"
    { (yyval.Char) = '\327'; }
    break;

  case 369:
#line 421 "lscp.y"
    { (yyval.Char) = '\330'; }
    break;

  case 370:
#line 421 "lscp.y"
    { (yyval.Char) = '\331'; }
    break;

  case 371:
#line 422 "lscp.y"
    { (yyval.Char) = '\332'; }
    break;

  case 372:
#line 422 "lscp.y"
    { (yyval.Char) = '\333'; }
    break;

  case 373:
#line 422 "lscp.y"
    { (yyval.Char) = '\334'; }
    break;

  case 374:
#line 423 "lscp.y"
    { (yyval.Char) = '\335'; }
    break;

  case 375:
#line 423 "lscp.y"
    { (yyval.Char) = '\336'; }
    break;

  case 376:
#line 423 "lscp.y"
    { (yyval.Char) = '\337'; }
    break;

  case 377:
#line 424 "lscp.y"
    { (yyval.Char) = '\340'; }
    break;

  case 378:
#line 424 "lscp.y"
    { (yyval.Char) = '\341'; }
    break;

  case 379:
#line 424 "lscp.y"
    { (yyval.Char) = '\342'; }
    break;

  case 380:
#line 425 "lscp.y"
    { (yyval.Char) = '\343'; }
    break;

  case 381:
#line 425 "lscp.y"
    { (yyval.Char) = '\344'; }
    break;

  case 382:
#line 425 "lscp.y"
    { (yyval.Char) = '\345'; }
    break;

  case 383:
#line 426 "lscp.y"
    { (yyval.Char) = '\346'; }
    break;

  case 384:
#line 426 "lscp.y"
    { (yyval.Char) = '\347'; }
    break;

  case 385:
#line 426 "lscp.y"
    { (yyval.Char) = '\350'; }
    break;

  case 386:
#line 427 "lscp.y"
    { (yyval.Char) = '\351'; }
    break;

  case 387:
#line 427 "lscp.y"
    { (yyval.Char) = '\352'; }
    break;

  case 388:
#line 427 "lscp.y"
    { (yyval.Char) = '\353'; }
    break;

  case 389:
#line 428 "lscp.y"
    { (yyval.Char) = '\354'; }
    break;

  case 390:
#line 428 "lscp.y"
    { (yyval.Char) = '\355'; }
    break;

  case 391:
#line 428 "lscp.y"
    { (yyval.Char) = '\356'; }
    break;

  case 392:
#line 429 "lscp.y"
    { (yyval.Char) = '\357'; }
    break;

  case 393:
#line 429 "lscp.y"
    { (yyval.Char) = '\360'; }
    break;

  case 394:
#line 429 "lscp.y"
    { (yyval.Char) = '\361'; }
    break;

  case 395:
#line 430 "lscp.y"
    { (yyval.Char) = '\362'; }
    break;

  case 396:
#line 430 "lscp.y"
    { (yyval.Char) = '\363'; }
    break;

  case 397:
#line 430 "lscp.y"
    { (yyval.Char) = '\364'; }
    break;

  case 398:
#line 431 "lscp.y"
    { (yyval.Char) = '\365'; }
    break;

  case 399:
#line 431 "lscp.y"
    { (yyval.Char) = '\366'; }
    break;

  case 400:
#line 431 "lscp.y"
    { (yyval.Char) = '\367'; }
    break;

  case 401:
#line 432 "lscp.y"
    { (yyval.Char) = '\370'; }
    break;

  case 402:
#line 432 "lscp.y"
    { (yyval.Char) = '\371'; }
    break;

  case 403:
#line 432 "lscp.y"
    { (yyval.Char) = '\372'; }
    break;

  case 404:
#line 433 "lscp.y"
    { (yyval.Char) = '\373'; }
    break;

  case 405:
#line 433 "lscp.y"
    { (yyval.Char) = '\374'; }
    break;

  case 406:
#line 433 "lscp.y"
    { (yyval.Char) = '\375'; }
    break;

  case 407:
#line 434 "lscp.y"
    { (yyval.Char) = '\376'; }
    break;

  case 408:
#line 434 "lscp.y"
    { (yyval.Char) = '\377'; }
    break;

  case 409:
#line 437 "lscp.y"
    { (yyval.String) = " ";      }
    break;

  case 411:
#line 439 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + " "; }
    break;

  case 412:
#line 440 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + (yyvsp[(2) - (2)].String);  }
    break;

  case 413:
#line 443 "lscp.y"
    { (yyval.String) = (yyvsp[(2) - (3)].String); }
    break;

  case 414:
#line 444 "lscp.y"
    { (yyval.String) = (yyvsp[(2) - (3)].String); }
    break;


/* Line 1267 of yacc.c.  */
#line 5056 "y.tab.c"
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


#line 666 "lscp.y"


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

