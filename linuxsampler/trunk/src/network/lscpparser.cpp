/* A Bison parser, made by GNU Bison 2.3.  */

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
#define YYBISON_VERSION "2.3"

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
#define YYLAST   4801

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  227
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  139
/* YYNRULES -- Number of rules.  */
#define YYNRULES  528
/* YYNRULES -- Number of states.  */
#define YYNSTATES  1668

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
     117,   119,   121,   123,   125,   127,   129,   131,   133,   135,
     137,   139,   141,   143,   145,   147,   149,   151,   153,   155,
     157,   159,   161,   163,   179,   197,   215,   235,   243,   247,
     251,   255,   257,   259,   265,   273,   283,   285,   291,   299,
     309,   311,   313,   319,   325,   333,   343,   351,   361,   363,
     369,   377,   383,   389,   395,   399,   401,   403,   407,   411,
     421,   423,   429,   433,   441,   443,   451,   461,   469,   479,
     483,   491,   503,   513,   523,   527,   531,   537,   541,   547,
     551,   557,   565,   569,   573,   577,   581,   585,   591,   595,
     599,   605,   613,   619,   629,   635,   641,   647,   653,   659,
     665,   671,   677,   683,   689,   693,   699,   701,   703,   705,
     707,   709,   711,   713,   715,   719,   723,   725,   729,   735,
     743,   747,   749,   751,   753,   755,   757,   759,   761,   763,
     765,   767,   769,   771,   773,   775,   777,   779,   781,   783,
     785,   787,   789,   791,   793,   795,   797,   801,   803,   805,
     807,   809,   811,   813,   815,   818,   822,   827,   832,   834,
     837,   839,   841,   843,   845,   847,   849,   851,   853,   855,
     857,   859,   862,   865,   868,   871,   874,   877,   880,   883,
     886,   888,   890,   892,   894,   896,   898,   900,   902,   904,
     906,   908,   910,   912,   914,   916,   918,   920,   922,   924,
     926,   928,   930,   932,   934,   936,   938,   940,   942,   944,
     946,   948,   950,   952,   954,   956,   958,   960,   962,   964,
     966,   968,   970,   972,   974,   976,   978,   980,   982,   984,
     986,   988,   990,   992,   994,   996,   998,  1000,  1002,  1004,
    1006,  1008,  1010,  1012,  1014,  1016,  1018,  1020,  1022,  1024,
    1026,  1028,  1030,  1032,  1034,  1036,  1038,  1040,  1042,  1044,
    1046,  1048,  1050,  1052,  1054,  1056,  1058,  1060,  1062,  1064,
    1066,  1068,  1070,  1072,  1074,  1076,  1078,  1080,  1082,  1084,
    1086,  1088,  1090,  1092,  1094,  1096,  1098,  1100,  1102,  1104,
    1106,  1108,  1110,  1112,  1114,  1116,  1118,  1120,  1122,  1124,
    1126,  1128,  1130,  1132,  1134,  1136,  1138,  1140,  1142,  1144,
    1146,  1148,  1150,  1152,  1154,  1156,  1158,  1160,  1162,  1164,
    1166,  1168,  1170,  1172,  1174,  1176,  1178,  1180,  1182,  1184,
    1186,  1188,  1190,  1192,  1194,  1196,  1198,  1200,  1202,  1204,
    1206,  1208,  1210,  1212,  1214,  1216,  1218,  1220,  1222,  1224,
    1226,  1228,  1230,  1232,  1234,  1236,  1238,  1240,  1242,  1244,
    1246,  1248,  1250,  1252,  1254,  1256,  1258,  1260,  1262,  1264,
    1266,  1268,  1270,  1272,  1274,  1276,  1278,  1280,  1282,  1284,
    1286,  1288,  1290,  1292,  1294,  1296,  1298,  1300,  1302,  1304,
    1306,  1308,  1310,  1312,  1314,  1316,  1318,  1320,  1322,  1324,
    1326,  1328,  1331,  1334,  1338,  1342,  1344,  1346,  1348,  1352,
    1356,  1360,  1366,  1372,  1379,  1387,  1392,  1397,  1401,  1406,
    1414,  1424,  1431,  1435,  1445,  1457,  1464,  1472,  1490,  1521,
    1530,  1535,  1561,  1586,  1610,  1633,  1659,  1684,  1706,  1727,
    1741,  1754,  1766,  1779,  1791,  1809,  1831,  1842,  1849,  1859,
    1874,  1885,  1915,  1936,  1956,  1986,  2006,  2037,  2058,  2076,
    2105,  2133,  2159,  2178,  2196,  2224,  2240,  2257,  2277,  2298,
    2316,  2332,  2351,  2367,  2378,  2394,  2402,  2411,  2418,  2425,
    2431,  2436,  2441,  2447,  2458,  2464,  2478,  2483,  2488
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     228,     0,    -1,   229,   283,    -1,   229,   284,   283,    -1,
      -1,   230,    -1,   231,    -1,     1,    -1,     3,    -1,   230,
       3,    -1,   230,   282,    -1,   230,   278,    -1,   230,   274,
      -1,   285,   282,   232,    -1,   287,   282,   235,    -1,   288,
     282,   236,    -1,   286,   282,   238,    -1,   290,   282,   240,
      -1,   291,   282,   243,    -1,   292,   282,   248,    -1,   293,
     282,   244,    -1,   298,   282,   237,    -1,   299,   282,   239,
      -1,   300,   282,   233,    -1,   301,   282,   234,    -1,   302,
     282,   280,    -1,   361,   282,   241,    -1,   289,   282,   242,
      -1,   361,    -1,   365,    -1,   303,    -1,   344,    -1,   344,
     282,   268,    -1,   308,    -1,   309,    -1,   310,    -1,   311,
      -1,   316,    -1,   320,    -1,   319,    -1,   318,    -1,   317,
      -1,   312,    -1,   313,    -1,   314,    -1,   315,    -1,   362,
      -1,   321,    -1,   308,    -1,   309,    -1,   310,    -1,   311,
      -1,   316,    -1,   320,    -1,   319,    -1,   318,    -1,   317,
      -1,   312,    -1,   313,    -1,   314,    -1,   315,    -1,   362,
      -1,   321,    -1,   342,   282,   258,   282,   259,   282,   260,
     282,   266,   282,   267,   282,   264,   282,   262,    -1,   342,
     282,   258,   282,   259,   282,   260,   282,   266,   282,   267,
     282,   264,   282,   262,   282,   251,    -1,   342,   282,   258,
     282,   259,   282,   260,   282,   266,   282,   267,   282,   264,
     282,   262,   282,   269,    -1,   342,   282,   258,   282,   259,
     282,   260,   282,   266,   282,   267,   282,   264,   282,   262,
     282,   251,   282,   269,    -1,   342,   282,   258,   282,   259,
     282,   260,    -1,   303,   282,   263,    -1,   344,   282,   258,
      -1,   344,   282,   294,    -1,   304,    -1,   336,    -1,   346,
     282,   307,   282,   274,    -1,   341,   282,   307,   282,   274,
     282,   274,    -1,   341,   282,   307,   282,   274,   282,   274,
     282,   246,    -1,   305,    -1,   332,   282,   307,   282,   274,
      -1,   331,   282,   307,   282,   274,   282,   274,    -1,   331,
     282,   307,   282,   274,   282,   274,   282,   246,    -1,   329,
      -1,   339,    -1,   330,   282,   307,   282,   278,    -1,   340,
     282,   307,   282,   278,    -1,   347,   282,   307,   282,   278,
     282,   278,    -1,   338,   282,   307,   282,   278,   282,   278,
     282,   274,    -1,   334,   282,   307,   282,   278,   282,   278,
      -1,   333,   282,   307,   282,   278,   282,   278,   282,   274,
      -1,   306,    -1,   303,   282,   307,   282,   263,    -1,   303,
     282,   318,   282,   247,   282,   263,    -1,   303,   282,   319,
     282,   263,    -1,   303,   282,   320,   282,   263,    -1,   324,
     282,   307,   282,   266,    -1,   354,   282,   307,    -1,   321,
      -1,   322,    -1,   343,   282,   258,    -1,   343,   282,   294,
      -1,   342,   282,   307,   282,   258,   282,   259,   282,   260,
      -1,   345,    -1,   344,   282,   307,   282,   258,    -1,   353,
     282,   263,    -1,   352,   282,   307,   282,   263,   282,   265,
      -1,   355,    -1,   328,   282,   278,   282,   274,     4,   271,
      -1,   333,   282,   278,   282,   278,   282,   274,     4,   271,
      -1,   337,   282,   278,   282,   274,     4,   271,    -1,   338,
     282,   278,   282,   278,   282,   274,     4,   271,    -1,   303,
     282,   245,    -1,   344,   282,   363,   282,   258,   282,   268,
      -1,   352,   282,   334,   282,   263,   282,   265,   282,   253,
     282,   253,    -1,   352,   282,   351,   282,   263,   282,   265,
     282,   261,    -1,   352,   282,   356,   282,   263,   282,   265,
     282,   262,    -1,   364,   282,   273,    -1,   355,   282,   262,
      -1,   330,   282,   274,   282,   246,    -1,   330,   282,   274,
      -1,   340,   282,   274,   282,   246,    -1,   340,   282,   274,
      -1,   352,   282,   263,   282,   261,    -1,   352,   282,   263,
     282,   261,   282,   270,    -1,   303,   282,   263,    -1,   343,
     282,   258,    -1,   343,   282,   294,    -1,   330,   282,   278,
      -1,   340,   282,   278,    -1,   352,   282,   263,   282,   265,
      -1,   323,   282,   249,    -1,   324,   282,   250,    -1,   330,
     282,   263,   282,   252,    -1,   334,   282,   263,   282,   253,
     282,   253,    -1,   335,   282,   263,   282,   254,    -1,   350,
     282,   263,   282,   252,   282,   255,   282,   256,    -1,   340,
     282,   263,   282,   252,    -1,   347,   282,   263,   282,   255,
      -1,   348,   282,   263,   282,   256,    -1,   349,   282,   263,
     282,   257,    -1,   355,   282,   263,   282,   262,    -1,   357,
     282,   263,   282,   273,    -1,   358,   282,   263,   282,   273,
      -1,   344,   282,   263,   282,   258,    -1,   344,   282,   263,
     282,   295,    -1,   344,   282,   263,   282,   296,    -1,   274,
       4,   271,    -1,   246,   282,   274,     4,   271,    -1,   359,
      -1,   360,    -1,   329,    -1,   339,    -1,   306,    -1,   304,
      -1,   336,    -1,   305,    -1,   343,   282,   258,    -1,   343,
     282,   294,    -1,   345,    -1,   353,   282,   263,    -1,   267,
     282,   264,   282,   263,    -1,   297,   282,   267,   282,   264,
     282,   263,    -1,   266,   282,   263,    -1,   325,    -1,   326,
      -1,   327,    -1,   278,    -1,   278,    -1,   274,    -1,   278,
      -1,   278,    -1,   294,    -1,   274,    -1,   278,    -1,   278,
      -1,   278,    -1,   278,    -1,   275,    -1,   278,    -1,   278,
      -1,   278,    -1,   278,    -1,   274,    -1,   281,    -1,   281,
      -1,   281,    -1,   281,    -1,   272,    -1,   271,     5,   272,
      -1,   274,    -1,   281,    -1,   278,    -1,   275,    -1,   278,
      -1,   274,    -1,   279,    -1,   274,   279,    -1,   276,     6,
     276,    -1,     7,   276,     6,   276,    -1,     8,   276,     6,
     276,    -1,   277,    -1,   276,   277,    -1,     9,    -1,    10,
      -1,    11,    -1,    12,    -1,    13,    -1,    14,    -1,    15,
      -1,    16,    -1,    17,    -1,    18,    -1,   277,    -1,    10,
     276,    -1,    11,   276,    -1,    12,   276,    -1,    13,   276,
      -1,    14,   276,    -1,    15,   276,    -1,    16,   276,    -1,
      17,   276,    -1,    18,   276,    -1,    19,    -1,    20,    -1,
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
     220,    -1,   221,    -1,   282,    -1,   274,    -1,   280,   282,
      -1,   280,   274,    -1,   222,   280,   222,    -1,   223,   280,
     223,    -1,   224,    -1,   225,    -1,   226,    -1,    19,    22,
      22,    -1,    25,    23,    38,    -1,    31,    19,    34,    -1,
      39,    32,    31,    19,    34,    -1,    21,    30,    23,    19,
      36,    -1,    21,    36,    23,    19,    38,    23,    -1,    22,
      23,    37,    38,    36,    33,    43,    -1,    30,    27,    37,
      38,    -1,    30,    33,    19,    22,    -1,    19,    30,    30,
      -1,    32,    33,    32,    23,    -1,    22,    23,    24,    19,
      39,    30,    38,    -1,    32,    33,    32,    89,    31,    33,
      22,    19,    30,    -1,    36,    23,    31,    33,    40,    23,
      -1,    37,    23,    38,    -1,    37,    39,    20,    37,    21,
      36,    27,    20,    23,    -1,    39,    32,    37,    39,    20,
      37,    21,    36,    27,    20,    23,    -1,    37,    23,    30,
      23,    21,    38,    -1,    21,    26,    19,    32,    32,    23,
      30,    -1,    19,    40,    19,    27,    30,    19,    20,    30,
      23,    89,    23,    32,    25,    27,    32,    23,    37,    -1,
      19,    40,    19,    27,    30,    19,    20,    30,    23,    89,
      19,    39,    22,    27,    33,    89,    33,    39,    38,    34,
      39,    38,    89,    22,    36,    27,    40,    23,    36,    37,
      -1,    21,    26,    19,    32,    32,    23,    30,    37,    -1,
      27,    32,    24,    33,    -1,    19,    39,    22,    27,    33,
      89,    33,    39,    38,    34,    39,    38,    89,    22,    23,
      40,    27,    21,    23,    89,    21,    33,    39,    32,    38,
      -1,    19,    39,    22,    27,    33,    89,    33,    39,    38,
      34,    39,    38,    89,    22,    23,    40,    27,    21,    23,
      89,    27,    32,    24,    33,    -1,    31,    27,    22,    27,
      89,    27,    32,    34,    39,    38,    89,    22,    23,    40,
      27,    21,    23,    89,    21,    33,    39,    32,    38,    -1,
      31,    27,    22,    27,    89,    27,    32,    34,    39,    38,
      89,    22,    23,    40,    27,    21,    23,    89,    27,    32,
      24,    33,    -1,    31,    27,    22,    27,    89,    27,    32,
      37,    38,    36,    39,    31,    23,    32,    38,    89,    31,
      19,    34,    89,    21,    33,    39,    32,    38,    -1,    31,
      27,    22,    27,    89,    27,    32,    37,    38,    36,    39,
      31,    23,    32,    38,    89,    31,    19,    34,    89,    27,
      32,    24,    33,    -1,    31,    27,    22,    27,    89,    27,
      32,    37,    38,    36,    39,    31,    23,    32,    38,    89,
      21,    33,    39,    32,    38,    -1,    31,    27,    22,    27,
      89,    27,    32,    37,    38,    36,    39,    31,    23,    32,
      38,    89,    27,    32,    24,    33,    -1,    21,    26,    19,
      32,    32,    23,    30,    89,    21,    33,    39,    32,    38,
      -1,    21,    26,    19,    32,    32,    23,    30,    89,    27,
      32,    24,    33,    -1,    20,    39,    24,    24,    23,    36,
      89,    24,    27,    30,    30,    -1,    37,    38,    36,    23,
      19,    31,    89,    21,    33,    39,    32,    38,    -1,    40,
      33,    27,    21,    23,    89,    21,    33,    39,    32,    38,
      -1,    38,    33,    38,    19,    30,    89,    40,    33,    27,
      21,    23,    89,    21,    33,    39,    32,    38,    -1,    38,
      33,    38,    19,    30,    89,    40,    33,    27,    21,    23,
      89,    21,    33,    39,    32,    38,    89,    31,    19,    42,
      -1,    27,    32,    37,    38,    36,    39,    31,    23,    32,
      38,    -1,    23,    32,    25,    27,    32,    23,    -1,    33,
      32,    89,    22,    23,    31,    19,    32,    22,    -1,    33,
      32,    89,    22,    23,    31,    19,    32,    22,    89,    26,
      33,    30,    22,    -1,    34,    23,    36,    37,    27,    37,
      38,    23,    32,    38,    -1,    19,    39,    22,    27,    33,
      89,    33,    39,    38,    34,    39,    38,    89,    22,    23,
      40,    27,    21,    23,    89,    34,    19,    36,    19,    31,
      23,    38,    23,    36,    -1,    19,    39,    22,    27,    33,
      89,    33,    39,    38,    34,    39,    38,    89,    22,    23,
      40,    27,    21,    23,    37,    -1,    19,    39,    22,    27,
      33,    89,    33,    39,    38,    34,    39,    38,    89,    22,
      23,    40,    27,    21,    23,    -1,    19,    39,    22,    27,
      33,    89,    33,    39,    38,    34,    39,    38,    89,    22,
      36,    27,    40,    23,    36,    89,    34,    19,    36,    19,
      31,    23,    38,    23,    36,    -1,    19,    39,    22,    27,
      33,    89,    33,    39,    38,    34,    39,    38,    89,    22,
      36,    27,    40,    23,    36,    -1,    19,    39,    22,    27,
      33,    89,    33,    39,    38,    34,    39,    38,    89,    21,
      26,    19,    32,    32,    23,    30,    89,    34,    19,    36,
      19,    31,    23,    38,    23,    36,    -1,    19,    39,    22,
      27,    33,    89,    33,    39,    38,    34,    39,    38,    89,
      21,    26,    19,    32,    32,    23,    30,    -1,    19,    39,
      22,    27,    33,    89,    33,    39,    38,    34,    39,    38,
      89,    38,    43,    34,    23,    -1,    19,    40,    19,    27,
      30,    19,    20,    30,    23,    89,    31,    27,    22,    27,
      89,    27,    32,    34,    39,    38,    89,    22,    36,    27,
      40,    23,    36,    37,    -1,    31,    27,    22,    27,    89,
      27,    32,    34,    39,    38,    89,    22,    23,    40,    27,
      21,    23,    89,    34,    19,    36,    19,    31,    23,    38,
      23,    36,    -1,    31,    27,    22,    27,    89,    27,    32,
      34,    39,    38,    89,    34,    33,    36,    38,    89,    34,
      19,    36,    19,    31,    23,    38,    23,    36,    -1,    31,
      27,    22,    27,    89,    27,    32,    34,    39,    38,    89,
      22,    23,    40,    27,    21,    23,    37,    -1,    31,    27,
      22,    27,    89,    27,    32,    34,    39,    38,    89,    22,
      23,    40,    27,    21,    23,    -1,    31,    27,    22,    27,
      89,    27,    32,    34,    39,    38,    89,    22,    36,    27,
      40,    23,    36,    89,    34,    19,    36,    19,    31,    23,
      38,    23,    36,    -1,    31,    27,    22,    27,    89,    27,
      32,    37,    38,    36,    39,    31,    23,    32,    38,    -1,
      31,    27,    22,    27,    89,    27,    32,    37,    38,    36,
      39,    31,    23,    32,    38,    37,    -1,    31,    27,    22,
      27,    89,    27,    32,    37,    38,    36,    39,    31,    23,
      32,    38,    89,    31,    19,    34,    -1,    31,    27,    22,
      27,    89,    27,    32,    37,    38,    36,    39,    31,    23,
      32,    38,    89,    31,    19,    34,    37,    -1,    31,    27,
      22,    27,    89,    27,    32,    34,    39,    38,    89,    22,
      36,    27,    40,    23,    36,    -1,    31,    27,    22,    27,
      89,    27,    32,    34,    39,    38,    89,    34,    33,    36,
      38,    -1,    31,    27,    22,    27,    89,    27,    32,    34,
      39,    38,    89,    21,    26,    19,    32,    32,    23,    30,
      -1,    31,    27,    22,    27,    89,    27,    32,    34,    39,
      38,    89,    38,    43,    34,    23,    -1,    31,    27,    22,
      27,    89,    27,    32,    34,    39,    38,    -1,    31,    27,
      22,    27,    89,    21,    33,    32,    38,    36,    33,    30,
      30,    23,    36,    -1,    24,    42,    89,    37,    23,    32,
      22,    -1,    24,    42,    89,    37,    23,    32,    22,    37,
      -1,    37,    23,    36,    40,    23,    36,    -1,    40,    33,
      30,    39,    31,    23,    -1,    30,    23,    40,    23,    30,
      -1,    31,    39,    38,    23,    -1,    37,    33,    30,    33,
      -1,    20,    43,    38,    23,    37,    -1,    34,    23,    36,
      21,    23,    32,    38,    19,    25,    23,    -1,    36,    23,
      37,    23,    38,    -1,    31,    27,    37,    21,    23,    30,
      30,    19,    32,    23,    33,    39,    37,    -1,    32,    19,
      31,    23,    -1,    23,    21,    26,    33,    -1,    35,    39,
      27,    38,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    96,    96,    97,   100,   101,   102,   103,   106,   107,
     108,   109,   110,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     132,   133,   134,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   171,   172,   173,   174,   177,   180,   181,
     182,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   234,   235,   236,   237,
     238,   239,   242,   245,   246,   249,   250,   251,   254,   255,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   274,   275,   278,   279,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   294,   295,
     298,   301,   302,   303,   306,   309,   312,   315,   318,   319,
     322,   325,   328,   331,   334,   337,   338,   341,   344,   347,
     350,   353,   356,   359,   362,   365,   366,   369,   370,   371,
     372,   380,   381,   384,   385,   388,   389,   390,   394,   395,
     398,   399,   400,   401,   402,   403,   404,   405,   406,   407,
     410,   411,   412,   413,   414,   415,   416,   417,   418,   419,
     421,   421,   421,   421,   421,   421,   421,   421,   421,   421,
     421,   421,   421,   421,   421,   421,   421,   421,   421,   421,
     421,   421,   421,   421,   421,   421,   422,   422,   422,   422,
     422,   422,   422,   422,   422,   422,   422,   422,   422,   422,
     422,   422,   422,   422,   422,   422,   422,   422,   422,   422,
     422,   422,   423,   423,   423,   423,   423,   423,   423,   423,
     423,   423,   424,   424,   424,   424,   424,   424,   424,   424,
     424,   424,   424,   424,   424,   425,   425,   425,   425,   425,
     425,   425,   426,   426,   426,   426,   426,   427,   427,   427,
     427,   428,   428,   428,   429,   429,   429,   430,   430,   430,
     431,   431,   431,   432,   432,   432,   433,   433,   433,   434,
     434,   434,   435,   435,   435,   436,   436,   436,   437,   437,
     437,   438,   438,   438,   439,   439,   439,   440,   440,   440,
     441,   441,   441,   442,   442,   442,   443,   443,   443,   444,
     444,   444,   445,   445,   445,   446,   446,   446,   447,   447,
     447,   448,   448,   448,   449,   449,   449,   450,   450,   450,
     451,   451,   451,   452,   452,   452,   453,   453,   453,   454,
     454,   454,   455,   455,   455,   456,   456,   456,   457,   457,
     457,   458,   458,   458,   459,   459,   459,   460,   460,   460,
     461,   461,   461,   462,   462,   462,   463,   463,   463,   464,
     464,   464,   465,   465,   465,   466,   466,   466,   467,   467,
     467,   468,   468,   468,   469,   469,   469,   470,   470,   473,
     474,   475,   476,   479,   480,   486,   489,   492,   495,   498,
     501,   504,   507,   510,   513,   516,   519,   522,   525,   528,
     531,   534,   537,   540,   543,   546,   549,   552,   555,   558,
     561,   564,   567,   570,   573,   576,   579,   582,   585,   588,
     591,   594,   597,   600,   603,   606,   609,   612,   615,   618,
     621,   624,   627,   630,   633,   636,   639,   642,   645,   648,
     651,   654,   657,   660,   663,   666,   669,   672,   675,   678,
     681,   684,   687,   690,   693,   696,   699,   702,   705,   708,
     711,   714,   717,   720,   723,   726,   729,   732,   735
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
  "midi_bank", "midi_prog", "midi_ctrl", "volume_value", "sampler_channel",
  "instrument_index", "fx_send_id", "engine_name", "filename", "map_name",
  "entry_name", "fx_send_name", "param_val_list", "param_val", "boolean",
  "string", "dotnum", "digits", "digit", "number", "char", "text",
  "stringval", "SP", "LF", "CR", "ADD", "GET", "MAP", "UNMAP", "CLEAR",
  "CREATE", "DESTROY", "LIST", "LOAD", "ALL", "NONE", "DEFAULT",
  "NON_MODAL", "REMOVE", "SET", "SUBSCRIBE", "UNSUBSCRIBE", "SELECT",
  "CHANNEL", "AVAILABLE_ENGINES", "AVAILABLE_AUDIO_OUTPUT_DRIVERS",
  "CHANNELS", "INFO", "AUDIO_OUTPUT_DEVICE_COUNT",
  "AUDIO_OUTPUT_DEVICE_INFO", "MIDI_INPUT_DEVICE_COUNT",
  "MIDI_INPUT_DEVICE_INFO", "MIDI_INSTRUMENT_MAP_COUNT",
  "MIDI_INSTRUMENT_MAP_INFO", "MIDI_INSTRUMENT_COUNT",
  "MIDI_INSTRUMENT_INFO", "CHANNEL_COUNT", "CHANNEL_INFO", "BUFFER_FILL",
  "STREAM_COUNT", "VOICE_COUNT", "TOTAL_VOICE_COUNT",
  "TOTAL_VOICE_COUNT_MAX", "INSTRUMENT", "ENGINE", "ON_DEMAND",
  "ON_DEMAND_HOLD", "PERSISTENT", "AUDIO_OUTPUT_DEVICE_PARAMETER",
  "AUDIO_OUTPUT_DEVICES", "AUDIO_OUTPUT_DEVICE",
  "AUDIO_OUTPUT_DRIVER_PARAMETER", "AUDIO_OUTPUT_DRIVER",
  "AUDIO_OUTPUT_CHANNEL_PARAMETER", "AUDIO_OUTPUT_CHANNEL",
  "AUDIO_OUTPUT_TYPE", "AVAILABLE_MIDI_INPUT_DRIVERS",
  "MIDI_INPUT_DEVICE_PARAMETER", "MIDI_INPUT_PORT_PARAMETER",
  "MIDI_INPUT_DEVICES", "MIDI_INPUT_DEVICE", "MIDI_INPUT_DRIVER_PARAMETER",
  "MIDI_INSTRUMENT", "MIDI_INSTRUMENTS", "MIDI_INSTRUMENT_MAP",
  "MIDI_INSTRUMENT_MAPS", "MIDI_INPUT_DRIVER", "MIDI_INPUT_PORT",
  "MIDI_INPUT_CHANNEL", "MIDI_INPUT_TYPE", "MIDI_INPUT", "MIDI_CONTROLLER",
  "FX_SEND", "FX_SENDS", "SERVER", "VOLUME", "LEVEL", "MUTE", "SOLO",
  "BYTES", "PERCENTAGE", "RESET", "MISCELLANEOUS", "NAME", "ECHO", "QUIT", 0
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
     233,   233,   233,   233,   233,   233,   233,   233,   234,   234,
     234,   234,   234,   234,   234,   234,   234,   234,   234,   234,
     234,   234,   234,   235,   235,   235,   235,   236,   237,   237,
     237,   238,   238,   238,   238,   238,   238,   238,   238,   238,
     238,   238,   238,   238,   238,   238,   238,   238,   238,   238,
     238,   238,   238,   238,   238,   238,   238,   238,   238,   238,
     238,   238,   238,   238,   238,   239,   239,   239,   239,   239,
     239,   239,   239,   239,   239,   239,   240,   240,   240,   240,
     240,   240,   241,   242,   242,   243,   243,   243,   244,   244,
     245,   245,   245,   245,   245,   245,   245,   245,   245,   245,
     245,   245,   245,   245,   246,   246,   247,   247,   248,   248,
     248,   248,   248,   248,   248,   248,   248,   248,   249,   249,
     250,   251,   251,   251,   252,   253,   254,   255,   256,   256,
     257,   258,   259,   260,   261,   262,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   271,   272,   272,   272,
     272,   273,   273,   274,   274,   275,   275,   275,   276,   276,
     277,   277,   277,   277,   277,   277,   277,   277,   277,   277,
     278,   278,   278,   278,   278,   278,   278,   278,   278,   278,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   280,
     280,   280,   280,   281,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,   353,   354,   355,   356,
     357,   358,   359,   360,   361,   362,   363,   364,   365
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     3,     0,     1,     1,     1,     1,     2,
       2,     2,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     1,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,    15,    17,    17,    19,     7,     3,     3,
       3,     1,     1,     5,     7,     9,     1,     5,     7,     9,
       1,     1,     5,     5,     7,     9,     7,     9,     1,     5,
       7,     5,     5,     5,     3,     1,     1,     3,     3,     9,
       1,     5,     3,     7,     1,     7,     9,     7,     9,     3,
       7,    11,     9,     9,     3,     3,     5,     3,     5,     3,
       5,     7,     3,     3,     3,     3,     3,     5,     3,     3,
       5,     7,     5,     9,     5,     5,     5,     5,     5,     5,
       5,     5,     5,     5,     3,     5,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     1,     3,     5,     7,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
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
       4,    25,    24,    23,    22,    25,    24,    21,    20,    13,
      12,    11,    12,    11,    17,    21,    10,     6,     9,    14,
      10,    29,    20,    19,    29,    19,    30,    20,    17,    28,
      27,    25,    18,    17,    27,    15,    16,    19,    20,    17,
      15,    18,    15,    10,    15,     7,     8,     6,     6,     5,
       4,     4,     5,    10,     5,    13,     4,     4,     4
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
       0,     0,     0,     0,     0,     0,     1,   446,   447,     2,
       0,     9,   298,   293,   292,   290,   291,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   282,
     284,   285,   286,   287,   288,   289,   294,   295,   296,   297,
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
     409,   410,   411,   412,   413,   414,   415,   416,   417,   418,
     419,   420,   421,   422,   423,   424,   425,   426,   427,   428,
     429,   430,   431,   432,   433,   434,   435,   436,   437,   438,
     445,    12,   210,    11,   193,    10,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   448,     0,     0,     0,   449,     0,     0,   450,     0,
       0,     0,     0,   462,     0,     0,     0,     3,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   211,   198,
     212,   213,   214,   215,   216,   217,   218,   219,   283,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   194,
       0,     0,    13,    30,    31,     0,     0,     0,     0,     0,
       0,     0,     0,    16,     0,    71,    76,    88,    95,    96,
       0,    80,     0,     0,     0,     0,     0,    72,     0,    81,
       0,     0,     0,     0,     0,   100,     0,     0,     0,     0,
       0,   104,     0,    14,     0,    15,     0,     0,    27,     0,
       0,     0,     0,    17,     0,     0,     0,    18,     0,     0,
       0,     0,     0,     0,     0,    19,   151,   153,   150,   148,
     152,   149,     0,   156,     0,     0,    20,     0,     0,    21,
       0,     0,     0,     0,     0,    22,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    23,    33,    34,    35,    36,    42,    43,    44,
      45,    37,    41,    40,    39,    38,    47,    46,    24,    48,
      49,    50,    51,    57,    58,    59,    60,    52,    56,    55,
      54,    53,    62,    61,   440,    25,   439,    26,     0,     0,
       0,     0,   455,   456,   528,     0,     0,     0,     0,     0,
       0,   199,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   442,   441,     0,   452,
       0,     0,     0,   524,     0,     0,   451,     0,     0,     0,
       0,     0,    32,   182,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   201,   202,
     203,   204,   205,   206,   207,   208,   209,     0,    97,   171,
      98,     0,     0,     0,     0,   102,   177,    94,     0,     0,
       0,     0,   123,   124,     0,     0,     0,   117,   119,     0,
     125,   126,     0,     0,     0,     0,     0,   154,   155,   157,
       0,     0,   128,     0,   181,     0,   129,     0,   180,    68,
      69,    70,     0,     0,     0,     0,     0,     0,   109,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   115,   175,     0,   198,   176,
     114,   192,   191,     0,     0,     0,     0,     0,     0,     0,
       0,   122,   453,     0,   461,   465,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   527,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   454,     0,     0,     0,     0,   443,   444,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      89,     0,     0,     0,   146,   147,    91,    92,    93,    82,
       0,    77,     0,     0,     0,    83,     0,     0,   457,   101,
      73,     0,     0,     0,     0,   172,     0,     0,     0,     0,
       0,   116,     0,   118,   120,   174,   127,   179,     0,     0,
       0,     0,     0,     0,     0,   178,     0,   160,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     195,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   487,     0,     0,   517,
       0,   518,   470,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   520,   521,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   526,     0,     0,     0,     0,     0,
       0,     0,   196,   197,     0,     0,     0,     0,     0,     0,
       0,     0,   463,     0,   466,     0,     0,     0,   466,   515,
       0,     0,     0,     0,    90,    78,     0,    86,     0,    74,
       0,    84,   103,     0,     0,   173,    67,     0,     0,   515,
       0,     0,   290,   291,   144,   185,   187,   190,   189,   188,
     121,   184,     0,     0,     0,     0,     0,     0,   158,     0,
       0,     0,     0,     0,   130,   164,     0,   165,   132,   166,
     134,     0,     0,   141,   142,   143,   135,   167,   136,   168,
     169,   137,   170,     0,   138,   139,   140,   105,     0,   107,
       0,   110,     0,   519,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     469,   516,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   464,
       0,     0,     0,     0,     0,     0,   522,     0,    79,    87,
      85,    75,    99,     0,     0,     0,     0,     0,   145,   186,
       0,     0,     0,     0,     0,   159,     0,     0,     0,     0,
     131,     0,     0,     0,   106,   108,     0,     0,     0,   112,
     113,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   486,     0,     0,     0,
       0,     0,     0,   458,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   460,     0,     0,     0,     0,
       0,   133,     0,     0,   111,     0,   481,     0,     0,     0,
       0,     0,     0,     0,   483,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   513,     0,     0,
       0,     0,     0,   480,     0,     0,     0,   482,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   459,     0,     0,     0,   479,     0,     0,
     525,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   523,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   510,   505,     0,   505,    63,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     506,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   467,     0,   503,
     509,     0,     0,   484,     0,     0,    64,    65,   183,   161,
     162,   163,     0,   503,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   510,   512,   514,     0,     0,     0,     0,
       0,   484,     0,     0,     0,     0,     0,     0,   502,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     507,     0,   493,   495,     0,     0,     0,     0,   507,     0,
       0,     0,    66,   493,     0,     0,     0,     0,     0,     0,
     498,     0,     0,     0,     0,     0,     0,     0,   497,   492,
       0,     0,     0,     0,     0,   508,     0,     0,     0,     0,
       0,     0,     0,   511,     0,     0,     0,     0,   478,     0,
       0,     0,     0,     0,     0,     0,   485,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   477,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   497,
       0,     0,     0,   474,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   473,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   472,     0,   476,     0,     0,     0,     0,     0,
     501,   488,     0,     0,     0,   471,   475,     0,     0,     0,
       0,     0,     0,   490,     0,     0,     0,     0,     0,     0,
     504,     0,     0,   500,     0,     0,     0,   499,     0,     0,
       0,   494,     0,     0,   491,   496,   468,   489
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    13,    14,    15,    16,   342,   442,   458,   383,   385,
     419,   353,   425,   393,   477,   388,   397,   416,   668,   861,
     833,   405,   652,   656,  1456,  1054,  1056,  1058,  1066,  1068,
    1071,   618,   854,  1024,   864,   695,   625,   874,   866,   657,
     653,   582,  1457,  1040,  1034,  1035,   700,  1036,  1037,   697,
     272,   626,   274,   475,  1039,   951,    49,    50,    17,    18,
      19,    20,    21,    22,    23,    24,    25,  1070,  1064,  1065,
     655,    26,    27,    28,    29,    30,   343,   355,   356,   357,
     594,   443,   444,   445,   446,   447,   448,   449,   450,   451,
     452,   453,   454,   455,   358,   359,   417,   360,  1459,  1460,
    1461,   427,   361,   362,   363,   364,   365,   366,   671,   367,
     429,   368,   369,   370,   371,   372,   373,   344,   375,   376,
     377,   675,   676,   677,   691,   378,   379,   380,   381,   692,
     679,   680,   834,   835,    31,   457,   686,   434,    32
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -1068
static const yytype_int16 yypact[] =
{
      68, -1068, -1068,    89,   175,    79,   103,   203,    55,   102,
     127,    69,    59,   157,    80,  2382, -1068,   -23,   -23,   -23,
     -23,   -23,   -23,   -23,   -23,   -23,   -23,   -23,   -23,   -23,
     -23,   -23, -1068,   188,   211,   234,   227,   224,   232,   268,
     239,   262,   165,   174,   275,   202, -1068, -1068, -1068, -1068,
     110, -1068, -1068, -1068, -1068, -1068, -1068, -1068,   377,   377,
     377,   377,   377,   377,   377,   377,   377, -1068, -1068, -1068,
   -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068,
   -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068,
   -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068,
   -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068,
   -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068,
   -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068,
   -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068,
   -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068,
   -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068,
   -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068,
   -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068,
   -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068,
   -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068,
   -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068,
   -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068,
   -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068,
   -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068,
   -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068,
   -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068,
   -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068,
   -1068,  3047, -1068, -1068, -1068, -1068,    52,    57,   269,   269,
     307,   166,   166,   162,   228,    52,   114,   111,   111,  2604,
     311, -1068,   325,   327,   316, -1068,   322,   346, -1068,   332,
     339,   352,   359, -1068,   364,   385,   357, -1068, -1068, -1068,
   -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068,   377, -1068,
     377,   377,   377,   377,   377,   377,   377,   377, -1068, -1068,
   -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068,
     407,   409, -1068, -1068,   -23,   297,   412,   405,   397,   414,
     430,   421,   422, -1068,   -23, -1068, -1068, -1068, -1068, -1068,
     -23, -1068,   -23,   -23,   -23,   -23,   -23, -1068,   -23, -1068,
     -23,   -23,   -23,   -23,   -23, -1068,   -23,   -23,   -23,   -23,
     -23, -1068,   429, -1068,   -23, -1068,   -23,   431, -1068,   -23,
     420,   419,   435, -1068,   -23,   -23,   -23, -1068,   -23,   -23,
     -23,   301,   439,   424,   441, -1068, -1068, -1068, -1068, -1068,
   -1068, -1068,   -23, -1068,   -23,   437, -1068,   -23,   -23, -1068,
     -23,   -23,   432,   449,   445, -1068,   -23,   -23,   -23,   -23,
     -23,   -23,   -23,   -23,   -23,   436,   448,   447,   461,   451,
     457,   458, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068,
   -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068,
   -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068,
   -1068, -1068, -1068, -1068,  3047,  2604, -1068, -1068,   -23,   456,
     455,   459, -1068, -1068, -1068,   454,   460,   475,   476,   465,
     480, -1068,   483,   481,   120,   482,   486,   487,   488,   418,
     492,   479,   478,   491,   116,   490,   490,   490,   490,   490,
     490,   490,   490,   490,   490,   209,   490,   490,   490,   490,
     411,   490,   500,   411,   411,   501,   209,   502,   438,   503,
    3047,  3047,   411,   411,   411,   411,   506,   499,   440,   508,
     209,   411,   494,    -6,  3047,   411,   209,   511,   509,   512,
     115,   411,   411,   411,   411,   504,   128,   310,  3266,   519,
     518,   526,    42,   510,   513,   520,  3047, -1068,   411, -1068,
     525,   516,   527, -1068,   514,   517, -1068,   521,   522,   528,
    2604,  2604, -1068, -1068,   529,   530,   531,   532,   523,   534,
     524,   543,   533,   535,   -23,   -23,   -23,   -23,   -23,   -23,
     -23,   -23,   -23,   -23,   -23,   -23,   -23,   -23,   377,   377,
     377,   377,   377,   377,   377,   377,   377,   538, -1068, -1068,
   -1068,   -23,   -23,   -23,   -23, -1068, -1068, -1068,   542,   -23,
     -23,   544, -1068, -1068,   546,   537,   548,  2604,  2604,   -23,
   -1068, -1068,   -23,   549,   545,   541,   566, -1068, -1068, -1068,
     556,   572, -1068,   -23, -1068,   -23, -1068,   -23,  3047, -1068,
   -1068, -1068,   583,   578,   586,   573,   160,   584, -1068,   -23,
     -23,   -23,   -23,   -23,   -23,   -23,   -23,   -23,   -23,   -23,
     -23,   -23,   -23,   -23,   -23,   551,   -23,   577,   595,   592,
     -23,   -23,   -23,   377,   377, -1068, -1068,   298,    35, -1068,
   -1068,  3047, -1068,   593,   601,   594,   602,   607,   608,   611,
     612, -1068, -1068,   589, -1068, -1068,   609,   613,   603,   550,
    1938,  2160,   604,   622,   621,   638,   618,   590,   649,   643,
     647,   650,   411,    48,   411,   411,  3047,   411,  3047,  3047,
     411,   411,   411,   411,  3047,   411,   652,   411,  3047,   411,
     411,   596,   411,   411,   597,   651,   660,   598,  3047,  3047,
     411,   411,   655,   657,   667,   605,   656,   659,   411,   120,
     411,   662, -1068,   610,   671,   675,   663,   668,   411,   411,
     411,   411,   411,   411,   411,   411,   411,   411,   411,   411,
    3047,   411,  3047,   411,   669,   411,   680,   664,   681,   411,
     411,   411,   434,   468,   377,   674,   685,   677,   623,   687,
     692,   683,   691, -1068,   695,   682,   693,   690, -1068, -1068,
     630,   701,   698,   699,   702,   697,   689,   641,   713,   704,
   -1068,   700,   717,   -23, -1068, -1068, -1068, -1068, -1068, -1068,
    2604,  3047,   -23,   -23,   -23, -1068,  2604,   -23, -1068, -1068,
    3047,   -23,   -23,   714,   -23, -1068,   -23,   715,   661,   712,
     718,   -23,  3485,   -23,   -23, -1068, -1068, -1068,   666,   725,
     719,   722,   720,   672,   -23, -1068,   -23, -1068,   673,   726,
     729,   730,   735,   727,   -23,   -23,   -23,   -23,   -23,   -23,
     -23,   -23,   -23,   -23,   -23,   -23,  3704,   -23,  3923,   -23,
     740,   -23,   737,   742,   739,   -23,   -23,   -23,   377,   377,
     377,   678,   716,   745,   743,   741,   738,   684,   686,   749,
     747,   746,   748,   750,   758,   752, -1068,   762,   754, -1068,
     753, -1068, -1068,   751,   756,   411,  3047,   411,   411,   411,
    3047,   411,   411,   411,   755,   411,   411,   763,   757,   766,
     764,  3047,  2826,   120,   761,   767,   776,   768,   770,   771,
     411,   411,   772,   774,   775,   710, -1068, -1068,   411,   411,
    3047,   411,   107,   411,   209,  3047,   411,   310,  3266,  3266,
    2826,  3047,  2826,  3047, -1068,   120,   777,   773,   723,   411,
     411,   411,   377,   377,   778,   724,   779,   782,   785,   728,
     781,   783, -1068,   787, -1068,   786,   780,   792,   789,   793,
      75,   791,   810,   795, -1068,  2604,   -23, -1068,   -23,  2604,
     -23, -1068, -1068,   797,   -23, -1068, -1068,   798,   799, -1068,
     806,  4142,   377,   377,   837, -1068,  3047, -1068, -1068, -1068,
   -1068, -1068,   804,   789,   793,   229,   821,   812, -1068,   -23,
     807,   231,   759,   820, -1068, -1068,   -23, -1068, -1068,  3047,
   -1068,   827,   818, -1068, -1068, -1068, -1068, -1068, -1068, -1068,
   -1068, -1068,  3047,   -23, -1068, -1068, -1068,   837,  4361,   837,
    4580, -1068,   765, -1068,   831,   -23,   -23,   -23,   814,   832,
     769,   254,   836,   839,   824,   829,   840,   826,   828,   842,
   -1068, -1068,   844,   830,   854,   848,   864,  3047,  3047,  3047,
    3047,   411,   850,  3047,   851,   855,   858,  2826,  2826,   856,
     859,   862,   835,   879,   411,   866,   863,   880,   882,   411,
     891,   884,   411,  2826,  2826,   885,   886,   411,   411,   310,
     883,   890,   214,   881,   888,   898,   889,   906,   895, -1068,
     899,   902,   852,   901,   904,   916, -1068,   910,   -23,  3047,
    3047,   -23, -1068,   907,   -23,   908,   911,   912,   837, -1068,
     914,   913,   917,   918,   930, -1068,   927,   929,   931,   296,
   -1068,   933,   946,   -23,   837,   837,   934,   940,   -23, -1068,
   -1068,   944,   949,   941,   948,   943,   947,   959,   945,   964,
     954,   950,   951,   169,   903,   955,   965,   957,   958,   120,
     960,   963,   909,   967,   919,   968, -1068,   966,   971,   922,
     974,   975,   976, -1068,   209,   978,   979,   411,   982,   983,
     984,   969,   935,   986,   989,   996,  1006,   992,   956,   993,
     994,  1000,  1008,   172,  1005,   953,  1018,  1007,   -23,  1012,
    1001,  1022,  1009,  1023,  1015, -1068,  1010,   173,  1016,  1011,
    1021, -1068,  1019,  1020, -1068,  1014, -1068,  1025,  1026,  1033,
    1029,  1027,  1030,   972, -1068,  1041,   980,  1043,  1042,  1051,
     153,  1045,  1052,  1053,  1054,  1057,   411,  1058,   995,  1059,
     997,  1062,  1064,   999,  1066,  1060,  1055,  1002,  1061,  1056,
    1063,  1003,  1067, -1068,  1075,  1077,  1065, -1068,  1069,  1074,
     345,  1080,  1081,  1082,  1070,  1084,  1076,  1085,  1068,  1090,
    1089,   -23,  1095,  1092,  1088,  1094,  1091,  1097,   356,  1093,
    1086,  1096,   106, -1068,  1098,  1100,  1110, -1068,  1099,  1103,
   -1068,  1104,  1102,  1112,   155,  1108,  1111,  1071,  1117,  1105,
    1109,  1113,  1107, -1068,  1114,   310,  1115,  1125,  1123,  1131,
    1128,  1118,  1132,  1134,  1135,  1121,  1072,  1137,  1133,  1122,
    1078,  1139,  1141,  1143,  1136,  1138,  1083,  1152,  1140,  1148,
    1087,  1155,  1154,  1158,  1159,  1101,     7,  1151, -1068,   -23,
    1147,  1145,  1165,  1149,  1166,    21,  1169,  1162,  1170,  1101,
      63,  1173,  1167,  1171,  1183,  1184,  1168,  1185,  1120,  1179,
    1181,  1182,  1188,  1178,  1186,  1187,  1189,  1197,  1190,  1191,
   -1068,  1192,  1193,    26,  1195,  1204,  1201,  1206,  1199,  1205,
    1209,  1215,  1213,  1198,  1210,  1207,  1220,  1211,  1219,  1225,
     182,  1212,  1230,  1221,  1231,  1228,  1217, -1068,  1223,  1222,
    1172,  1239,  1241,  1174,  1232,  1244,   -23, -1068, -1068, -1068,
   -1068, -1068,  1247, -1068,  1248,  1222,  1243,  1238,  1252,  1194,
    1255,  1242,  1245, -1068, -1068, -1068,  1259,  1196,  1251,  1249,
    1270, -1068,  1256,  1268,  1269,  1257,  1258,  1260, -1068,  1261,
    1262,  1263,  1271,  1214,  1264,   120,  1278,  1281,  1273,  1282,
    1285,  1275,  1279,  1287,  1289,  1290,   216,  1276,  1292,  1280,
   -1068,  1288,  1283,  1233,  1291,  1286,  1298,  1300,  1293,  1307,
    1272,  1294, -1068, -1068,  1283,  1293,  1297,  1240,  1309,  1301,
   -1068,  1302,  1246,  1303,  1305,  1306,  1310,  1250,  1253, -1068,
    1311,  1295,  1265,  1304,  1313, -1068,  1308,  1323,  1320,  1253,
    1314,  1315,  1326, -1068,   217,  1316,  1328,  1318, -1068,   225,
    1319,  1338,  1321,  1336,  1341,  1339, -1068,  1330,  1327,  1344,
    1346,  1337,  1333,  1340,  1343,  1335, -1068,  1345,  1347,  1350,
    1334,  1284,  1348,  1349,  1352,  1357,  1353,  1356,  1351, -1068,
    1332,  1359,  1355, -1068,  1342,  1361,  1358,  1367,  1373,  1369,
    1354,  1374,  1366,  1376,  1381,  1378,  1370,  1371, -1068,  1375,
    1372,  1384,  1377,  1379,  1380,  1368,  1382,  1387,  1385,  1383,
    1386,  1388, -1068,  1389, -1068,  1390,  1393,  1392,  1399,  1400,
   -1068,  1322,  1391,  1402,  1405, -1068, -1068,  1407,  1395,  1394,
    1401,  1403,  1409, -1068,  1404,  1410,  1411,  1408,  1415,  1406,
   -1068,  1412,  1425, -1068,  1427,  1416,  1417, -1068,  1421,  1418,
    1419, -1068,  1420,  1436, -1068, -1068, -1068, -1068
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068,
   -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068, -1068,  -734,
   -1068, -1068, -1068, -1068, -1068,  -899, -1067, -1068,   278,   189,
   -1068,  -505,  -696,  -903,   274,  -957,  -503,  -934,  -876,  -713,
    -745,   474,   -35, -1068,  -919,   344,  -571,   496,  -535,   -13,
     585,   -14,   425,  -171,  -477,   -15,  1413, -1068, -1068, -1068,
   -1068, -1068, -1068, -1068, -1068, -1068, -1068,  -440, -1068, -1068,
   -1068, -1068, -1068, -1068, -1068, -1068,  -106,  1200,  1202,  1203,
    -344,  1176,  1177,  1180,  1208,  1216,  1218,  1224,  1226,  1227,
    1229,  -234,  -233,  -232,   143, -1068, -1068,  1234, -1068, -1068,
   -1068, -1068,  1236,  -251, -1068, -1068,  1235,  -300, -1068,  1237,
   -1068,  1254,  1266,  -248, -1068,   156,    51,  -249,  1267, -1068,
     920, -1068, -1068, -1068, -1068,   -28,  1274, -1068,  -247, -1068,
   -1068, -1068, -1068, -1068, -1068,  1299, -1068, -1068, -1068
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -211
static const yytype_int16 yytable[] =
{
     275,   273,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   583,   629,   630,
    1074,   632,   696,   838,   876,   863,   651,  1049,   374,   639,
     394,   398,   642,   395,   399,   647,   421,   431,   649,   433,
    -210,   660,   659,  1026,  1420,   318,   320,   321,   322,   323,
     324,   325,   326,   327,   469,   470,   471,   856,  1420,  1454,
    1455,  1077,  1180,  1079,   706,   711,   654,  1022,   831,     1,
    1188,     2,  1060,   340,    40,   620,   345,  1073,   346,   707,
     347,   348,   832,   341,  1432,  1357,   633,     3,   349,     4,
       5,    45,    43,     6,   350,   351,  1421,   352,     7,     8,
     648,  1433,    36,     9,    10,    11,   661,    12,    44,  1102,
    1428,    33,  1103,  1085,  1086,  1087,   308,   608,   609,   610,
     611,   612,   613,   614,   615,   616,    37,  1367,  1289,  1061,
     435,   436,   437,   422,   665,   340,   436,   423,   391,  1062,
    1368,    41,   438,   593,  1369,   424,   666,   687,   439,   440,
      42,   441,   667,   439,   352,   352,   441,    46,   688,   689,
    1264,   598,   599,   600,   601,   602,   603,   604,   605,   606,
     607,   354,   621,   622,   623,   624,  1314,   627,  1378,   420,
     426,   401,  1190,   402,   478,   390,   403,   775,  1240,  1315,
     391,  1379,  1241,   404,  1280,  1294,   300,   392,  1168,   776,
    1242,   270,   301,  1478,   302,    34,  1281,  1295,  1162,  1479,
     291,    35,   303,  1480,  1184,  1185,   580,   581,   308,   608,
     609,   610,   611,   612,   613,   614,   615,   616,   617,   830,
      38,   836,   837,   305,   292,  1193,    39,  1533,  1572,   306,
     847,  1194,   849,  1534,  1573,  1020,  1577,   852,   580,   581,
     670,   347,  1578,   396,   400,   415,   690,   293,   432,  -210,
    -210,  -210,   295,  1120,   294,  1126,  1121,   877,  1097,   296,
     595,   596,   597,   298,   476,   884,   885,   886,   887,   888,
     889,   890,   891,   892,   893,   894,   895,   297,  1143,   299,
     901,  1144,   654,    -4,    -4,   304,   905,   906,   907,   669,
     382,   673,   672,   678,   804,    47,    48,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   693,   694,   308,
     608,   609,   610,   611,   612,   613,   614,   615,   616,   494,
    1221,   389,   340,  1097,   412,    47,   495,   496,   387,   504,
     536,   496,   580,   581,   479,   505,   480,   506,   507,   508,
     509,   510,  1321,   511,   481,   512,   513,   514,   515,   516,
     482,   517,   518,   519,   520,   521,  1343,  1344,   483,   523,
     484,   524,   485,  1158,   526,   486,  1161,  1362,  1363,   530,
     531,   532,   487,   533,   534,   535,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   490,   540,  1389,   541,
    1164,   488,   543,   544,   489,   545,   546,  1075,  1076,   720,
     721,   550,   551,   552,   553,   554,   555,   556,   557,   558,
     308,   608,   609,   610,   611,   612,   613,   614,   615,   616,
     456,   472,  1014,   492,   384,   386,   493,   498,   497,   499,
     908,   500,   696,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   501,   502,   503,   522,  1048,   525,   527,
     567,   528,   529,   568,  1248,   537,   538,  1063,   539,   542,
     548,   547,   549,   561,   909,   559,  1041,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   560,   562,   563,
     564,   565,   569,   570,   572,   571,   574,   575,   573,   576,
     577,   619,   578,   579,   584,   585,   586,   588,   583,   619,
     619,   271,   619,   587,   589,   590,   591,   593,   644,   640,
     641,   592,   628,   631,   634,   636,   619,   635,   643,   645,
     646,   650,   619,   662,   664,   663,   685,   681,   682,   683,
     684,   703,   704,   699,   702,   705,   708,   710,   712,   713,
     714,   709,   715,   716,   718,   719,   722,   723,   717,   725,
     726,   727,   729,   724,   728,   476,   476,   731,   746,   751,
     794,   754,   730,   755,   756,   757,   762,   763,   764,   732,
     733,   734,   735,   736,   737,   738,   739,   740,   741,   742,
     743,   744,   745,   765,   766,   318,   320,   321,   322,   323,
     324,   325,   326,   327,   696,   767,   747,   748,   749,   750,
     771,   772,   774,   773,   752,   753,   796,   777,   797,   798,
     805,  1175,   758,   759,   760,   806,   807,   761,   809,   808,
     811,   810,   813,   812,   815,   816,   814,   820,   768,   817,
     769,   824,   770,   319,   319,   319,   319,   319,   319,   319,
     319,   319,   821,   822,   778,   779,   780,   781,   782,   783,
     784,   785,   786,   787,   788,   789,   790,   791,   792,   793,
     823,   795,   826,   827,   829,   799,   800,   801,   828,   825,
     802,   803,   848,   859,   858,   853,   857,   860,   868,   869,
     870,   873,   872,   880,   871,   878,   339,   881,   883,   879,
     900,   882,   902,   904,   903,   567,   567,   911,   912,   913,
     915,   916,   914,   917,   918,   919,   921,   922,   920,   923,
     924,   925,   926,   839,   928,   929,   842,   843,   844,   845,
     930,   619,   654,   619,   927,   851,   931,   932,   855,   855,
     934,   944,   947,   933,   949,   950,   865,   867,   955,   957,
     948,   956,   995,   963,   875,   954,   964,   965,   966,   958,
     967,   959,   962,   984,   986,   987,   988,   994,   996,   999,
     997,   998,  1002,  1000,  1003,  1001,  1004,   897,  1007,   899,
    1005,   619,  1008,  1006,  1009,   474,  1010,  1023,  1029,  1012,
    1028,   910,  1013,  1011,  1042,  1027,  1030,  1043,  1044,  1053,
    1045,  1046,  1047,  1083,  1095,  1050,  1051,  1096,  1052,  1090,
    1082,  1088,  1084,  1089,  1091,  1092,  1106,  1093,   935,  1098,
     696,  1094,  1099,  1097,  1104,   936,  1100,   937,   938,   939,
    1101,   940,   941,  1105,  1112,  1114,   942,   943,  1115,   945,
    1116,   946,  1118,  1119,  1122,  1123,  1125,  1128,  1127,   953,
    1130,  1131,  1136,  1140,  1135,  1145,  1141,  1147,  1142,   960,
    1146,   961,  1148,  1149,  1150,  1152,  1151,  1173,  1154,   968,
     969,   970,   971,   972,   973,   974,   975,   976,   977,   978,
     979,  1155,   981,  1153,   983,  1156,   985,  1157,  1163,  1165,
     989,   990,   991,  1166,  1170,   992,   993,  1167,  1171,   339,
    1172,  1174,  1177,   491,  1176,   491,   491,   491,   491,   491,
     491,   491,   491,  1178,  1179,  1181,  1182,  1192,  1186,  1187,
    1195,  1191,  1198,  1016,  1017,  1018,  1196,   855,  1021,   867,
    1197,  1025,  1025,  1199,  1200,  1201,  1202,  1206,  1038,  1204,
    1205,  1203,  1207,  1208,  1210,  1211,  1458,   875,  1213,  1217,
    1212,  1214,  1222,  1215,  1055,  1057,  1216,  1055,   619,  1067,
    1069,  1218,  1055,   699,   702,   702,  1038,  1219,  1038,  1223,
    1220,   566,  1226,  1225,  1230,   867,   867,   867,  1228,  1229,
    1231,  1232,  1234,  1233,  1235,  1236,  1237,  1275,  1245,  1238,
    1239,   339,  1243,  1268,  1244,  1246,  1255,  1247,  1251,  1249,
    1107,  1108,  1250,  1109,  1110,  1111,  1252,  1254,  1253,  1113,
    1256,  1257,  1258,  1266,  1259,  1260,  1262,  1263,  1458,   802,
     803,  1265,  1271,  1267,  1269,  1270,   637,   638,  1272,  1273,
    1274,  1276,  1278,  1277,  1124,  1279,  1282,  1284,  1285,  1288,
     658,  1129,  1283,  1287,  1289,  1291,  1292,  1290,  1293,  1297,
    1296,  1298,  1301,  1299,   701,  1304,  1300,  1302,  1132,  1303,
    1305,  1308,   339,   339,  1309,  1311,  1306,  1312,  1307,  1310,
    1137,  1138,  1139,  1313,  1318,  1317,   474,   474,  1316,  1319,
    1320,  1322,  1324,   339,  1323,  1326,  1325,  1327,  1328,  1329,
    1341,  1332,  1336,  1330,  1331,  1334,  1335,  1025,  1338,  1333,
    1339,  1352,  1340,  1038,  1038,  1337,  1342,  1345,  1346,  1347,
    1348,  1349,  1350,  1353,  1357,  1057,  1359,  1351,  1067,  1038,
    1038,  1354,  1365,  1057,   865,   699,   339,  1356,  1358,  1361,
    1371,  1360,  1372,  1364,  1366,  1374,  1370,  1375,  1377,  1373,
    1376,  1380,   698,  1381,  1383,  1384,  1387,  1385,  1391,  1209,
    1392,  1386,  1388,  1390,  1393,  1394,  1395,  1397,  1396,  1399,
    1382,  1400,  1398,  1401,  1406,  1403,  1402,  1404,  1224,  1405,
    1407,  1411,  1410,  1227,  1408,  1413,  1414,  1409,  1415,  1417,
    1412,  1416,  1418,  1422,  1420,  1424,  1425,  1427,  1429,  1426,
    1419,  1431,  1434,   319,   319,   319,   319,   319,   319,   319,
     319,   319,  1430,  1435,  1432,  1436,  1439,  1437,  1438,  1440,
    1069,  1441,  1442,  1057,  1443,  1444,   566,   566,  1445,  1446,
    1449,  1448,  1462,  1452,  1447,  1451,  1450,  1463,  1464,  1465,
    1466,  1453,   658,  1286,   840,   841,  1468,  1467,  1469,  1470,
     846,  1471,  1472,  1474,   850,  1473,  1476,  1475,  1477,  1482,
    1481,  1485,  1484,  1483,   862,   862,  1486,  1487,  1490,  1488,
    1491,  1489,  1498,  1492,  1493,   339,   339,  1494,  1496,  1497,
    1499,   339,   875,  1500,  1502,   339,  1503,  1504,   319,   319,
    1505,  1508,   491,  1501,  1507,  1506,   896,   339,   898,  1509,
    1510,  1511,  1512,  1513,  1547,  1516,  1514,  1518,  1517,  1515,
    1521,  1523,  1519,  1520,  1524,  1526,  1355,  1525,  1527,  1528,
    1530,  1529,  1531,  1532,  1537,  1535,  1536,  1543,  1538,  1544,
    1539,   339,  1540,   339,  1542,  1541,  1546,  1549,  1551,  1550,
    1545,  1548,  1553,  1552,  1562,  1554,  1555,  1556,  1557,  1559,
    1564,   699,  1560,  1558,  1565,  1561,  1567,  1568,  1569,  1571,
    1566,  1570,  1575,  1579,  1563,  1574,  1576,  1580,  1582,  1581,
    1583,  1585,  1584,  1587,  1586,  1588,  1590,  1589,  1593,  1596,
    1597,  1606,  1591,  1598,  1423,  1592,  1602,  1615,  1594,  1595,
    1600,  1609,  1605,  1607,  1599,  1610,  1612,   491,   491,   319,
    1601,  1603,  1604,  1608,  1611,  1613,  1614,  1616,  1617,  1618,
    1619,  1620,  1621,  1625,  1622,  1624,  1629,  1623,  1626,  1631,
    1183,  1642,  1189,  1261,  1633,  1627,  1638,  1632,  1630,  1639,
    1628,  1637,  1640,  1641,  1634,  1644,  1635,  1636,  1645,  1643,
    1646,  1655,  1015,  1647,  1648,  1651,  1019,  1649,  1656,  1650,
     339,  1495,  1652,  1657,   339,  1658,  1653,  1031,  1659,  1654,
    1660,  1663,  1661,  1662,  1664,  1665,   339,  1666,  1667,  1081,
    1522,   339,  1169,   307,   459,   460,  1059,     0,   461,     0,
     674,  1072,     0,     0,   701,   701,     0,  1078,     0,  1080,
       0,     0,     0,   406,   339,   407,   408,     0,     0,     0,
       0,     0,     0,   319,   319,   491,   462,   339,     0,     0,
       0,     0,     0,   339,   463,   339,   464,     0,     0,     0,
       0,     0,   465,     0,   466,   467,     0,   468,   418,   409,
     410,   428,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   698,     0,     0,
     430,     0,     0,     0,     0,     0,     0,     0,     0,   411,
     413,     0,     0,     0,     0,     0,     0,   414,     0,     0,
       0,     0,   698,     0,     0,   698,     0,   698,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   491,   491,     0,
       0,     0,     0,     0,   339,   339,     0,   473,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   862,  1159,  1160,   862,     0,     0,   658,
       0,     0,     0,     0,     0,     0,     0,   319,   319,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   698,   698,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   698,   698,
       0,     0,     0,     0,   698,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     698,   328,    52,    53,    54,    55,    56,   329,   330,   331,
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
     818,     0,   270,   328,    52,    53,    54,    55,    56,   329,
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
     268,   269,     0,   819,   270,    51,    52,    53,    54,    55,
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
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,     0,     0,   270,   328,    52,    53,
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
     264,   265,   266,   267,   268,   269,     0,     0,   270,   328,
      52,    53,    54,  1032,  1033,    57,    58,    59,    60,    61,
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
     262,   263,   264,   265,   266,   267,   268,   269,   580,   581,
     328,    52,    53,    54,    55,    56,   329,   330,   331,   332,
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
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   328,   952,
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
     263,   264,   265,   266,   267,   268,   269,   328,   980,    53,
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
     264,   265,   266,   267,   268,   269,   328,   982,    53,    54,
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
     265,   266,   267,   268,   269,   328,  1117,    53,    54,    55,
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
     266,   267,   268,   269,   328,  1133,    53,    54,    55,    56,
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
     267,   268,   269,   328,  1134,    53,    54,    55,    56,   329,
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
     268,   269
};

static const yytype_int16 yycheck[] =
{
      15,    15,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,   494,   523,   524,
     977,   526,   557,   736,   769,   759,    32,   961,   277,   532,
     281,   282,   535,   281,   282,   540,   285,   286,   541,   286,
       5,   546,   545,   946,    37,    58,    59,    60,    61,    62,
      63,    64,    65,    66,   288,   288,   288,   753,    37,    33,
      34,   980,  1129,   982,    22,   568,   543,   943,    20,     1,
    1137,     3,   971,    21,    19,   515,    19,   976,    21,    37,
      23,    24,    34,    31,    21,    22,   526,    19,    31,    21,
      22,    32,    23,    25,    37,    38,    89,    40,    30,    31,
     540,    38,    23,    35,    36,    37,   546,    39,    39,    34,
      89,    22,    37,   989,   990,   991,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    23,    21,    22,    22,
      19,    20,    21,    19,    19,    21,    20,    23,    24,    32,
      34,    39,    31,    27,    38,    31,    31,    19,    37,    38,
      23,    40,    37,    37,    40,    40,    40,     0,    30,    31,
    1227,   505,   506,   507,   508,   509,   510,   511,   512,   513,
     514,   277,   516,   517,   518,   519,    23,   521,    23,   285,
     286,    19,  1139,    21,   290,    19,    24,    27,    19,    36,
      24,    36,    23,    31,    22,    22,    31,    31,  1117,    39,
      31,   224,    37,    21,    30,    30,    34,    34,  1111,    27,
      22,    36,    38,    31,  1133,  1134,   222,   223,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,   732,
      27,   734,   735,    31,    23,    21,    33,    21,    21,    37,
     745,    27,   747,    27,    27,   941,    21,   750,   222,   223,
     550,    23,    27,   281,   282,    27,   556,    23,   286,   224,
     225,   226,    38,    34,    37,    34,    37,   770,    37,    37,
     504,   504,   504,    34,   289,   778,   779,   780,   781,   782,
     783,   784,   785,   786,   787,   788,   789,    19,    34,    27,
     795,    37,   769,   225,   226,    20,   799,   800,   801,   550,
      31,   550,   550,   550,     6,   225,   226,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,   344,
      34,   280,    21,    37,   283,   225,    39,    40,    31,   354,
      39,    40,   222,   223,    19,   360,    19,   362,   363,   364,
     365,   366,  1286,   368,    38,   370,   371,   372,   373,   374,
      38,   376,   377,   378,   379,   380,    21,    22,    22,   384,
      38,   386,    33,  1107,   389,    23,  1110,    21,    22,   394,
     395,   396,    23,   398,   399,   400,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    39,   412,  1355,   414,
    1113,    37,   417,   418,    19,   420,   421,   978,   979,   580,
     581,   426,   427,   428,   429,   430,   431,   432,   433,   434,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
     287,   288,   935,    26,   278,   279,    27,    32,    26,    42,
       6,    27,   977,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    23,    33,    33,    27,   960,    27,    39,
     475,    42,    27,   478,  1209,    26,    42,   972,    27,    32,
      21,    39,    27,    26,     6,    39,   953,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    39,    27,    38,
      33,    33,    36,    38,    40,    36,    21,    21,    38,    34,
      20,   515,    19,    22,    22,    19,    19,    89,   985,   523,
     524,    15,   526,    25,    22,    36,    38,    27,    19,   533,
     534,    30,    22,    22,    22,    22,   540,    89,    22,    89,
      22,    37,   546,    22,    22,    26,    32,   551,   552,   553,
     554,    22,    24,   557,   558,    19,    36,    27,    23,    33,
      23,    38,    38,    36,    32,    27,    27,    27,    37,    27,
      37,    27,    19,    32,    40,   580,   581,    32,    30,    27,
      19,    27,    39,    27,    37,    27,    27,    32,    37,   594,
     595,   596,   597,   598,   599,   600,   601,   602,   603,   604,
     605,   606,   607,    27,    38,   608,   609,   610,   611,   612,
     613,   614,   615,   616,  1139,    33,   621,   622,   623,   624,
      27,    33,    39,    27,   629,   630,    39,    33,    23,    27,
      27,  1124,   637,   638,   639,    24,    32,   642,    21,    27,
      19,    23,    43,    21,    21,    32,    27,    33,   653,    89,
     655,    23,   657,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    30,    32,   669,   670,   671,   672,   673,   674,
     675,   676,   677,   678,   679,   680,   681,   682,   683,   684,
      32,   686,    23,    30,    24,   690,   691,   692,    31,    89,
     693,   694,    30,    23,    33,    89,    89,    89,    33,    32,
      23,    32,    36,    22,    89,    33,   271,    22,    30,    89,
      31,    38,    22,    22,    40,   720,   721,    33,    23,    32,
      23,    19,    89,    30,    23,    20,    23,    27,    36,    89,
      19,    23,    23,   737,    27,    36,   740,   741,   742,   743,
      89,   745,  1209,   747,    32,   749,    23,    33,   752,   753,
      23,    27,    27,    43,    32,    27,   760,   761,    23,    27,
      89,    32,    36,    27,   768,    89,    27,    27,    23,    39,
      33,    89,    89,    23,    27,    23,    27,    89,    23,    31,
      27,    30,    23,    89,    27,    89,    30,   791,    20,   793,
      32,   795,    30,    33,    22,   289,    32,    32,    22,    38,
      33,   804,    36,    40,    33,    32,    32,    30,    22,    89,
      32,    31,    31,    30,    21,    33,    32,    20,    33,    30,
      33,    33,    89,    89,    32,    30,    21,    89,   833,    39,
    1355,    40,    30,    37,    33,   840,    37,   842,   843,   844,
      37,   846,   847,    23,    37,    37,   851,   852,    39,   854,
      34,   856,     5,    39,    23,    33,    39,    27,    89,   864,
      23,    33,    21,    39,    89,    19,    24,    33,    89,   874,
      21,   876,    33,    23,    38,    23,    38,    32,    38,   884,
     885,   886,   887,   888,   889,   890,   891,   892,   893,   894,
     895,    27,   897,    39,   899,    37,   901,    23,    38,    38,
     905,   906,   907,    38,    38,   908,   909,    39,    39,   474,
      38,    22,    39,   318,    38,   320,   321,   322,   323,   324,
     325,   326,   327,    33,    32,    24,    32,    27,    33,    33,
      39,    38,    33,   937,   938,   939,    38,   941,   942,   943,
      32,   945,   946,    27,    39,    36,    34,    21,   952,    38,
      36,    89,    32,    36,    36,    34,  1423,   961,    34,    19,
      38,    38,    19,    36,   968,   969,    38,   971,   972,   973,
     974,    34,   976,   977,   978,   979,   980,    38,   982,    23,
      39,   475,    32,    39,    33,   989,   990,   991,    34,    30,
      32,    38,    23,    36,    39,    21,    32,    31,    23,    39,
      39,   566,    89,    24,    39,    38,    30,    39,    89,    39,
    1015,  1016,    39,  1018,  1019,  1020,    39,    39,    89,  1024,
      39,    89,    38,    30,    39,    39,    38,    38,  1495,  1032,
    1033,    39,    33,    39,    89,    39,   530,   531,    32,    23,
      38,    38,    32,    39,  1049,    27,    31,    19,    31,    38,
     544,  1056,    89,    31,    22,    22,    31,    38,    38,    38,
      34,    30,    38,    34,   558,    22,    36,    32,  1073,    33,
      31,    89,   637,   638,    23,    22,    39,    25,    38,    89,
    1085,  1086,  1087,    22,    21,    23,   580,   581,    33,    25,
      23,    23,    23,   658,    89,    23,    89,    23,    89,    23,
      21,    89,    89,    33,    39,    39,    33,  1111,    23,    38,
      23,    33,    37,  1117,  1118,    38,    32,    27,    27,    27,
      40,    27,    36,    23,    22,  1129,    22,    32,  1132,  1133,
    1134,    32,    36,  1137,  1138,  1139,   701,    32,    40,    32,
      30,    40,    22,    40,    38,    32,    38,    33,    26,    40,
      38,    33,   557,    32,    27,    40,    39,    38,    23,  1164,
      27,    38,    38,    38,    23,    27,    38,    23,    26,    38,
      89,    89,    27,    26,    23,    43,    33,    89,  1183,    30,
      27,    19,    89,  1188,    38,    27,    89,    39,    23,    21,
      40,    27,    23,    32,    37,    40,    21,    21,    19,    40,
      89,    21,    19,   608,   609,   610,   611,   612,   613,   614,
     615,   616,    40,    36,    21,    34,    21,    23,    40,    89,
    1224,    32,    31,  1227,    32,    27,   720,   721,    40,    33,
      23,    32,    27,    31,    37,    34,    36,    23,    27,    23,
      31,    38,   736,  1248,   738,   739,    27,    32,    23,    26,
     744,    43,    32,    23,   748,    38,    27,    36,    23,    19,
      38,    23,    21,    32,   758,   759,    39,    34,    19,    37,
      19,    89,    19,    89,    32,   840,   841,    23,    21,    21,
      32,   846,  1286,    21,    19,   850,    34,    32,   693,   694,
      21,    32,   697,    89,    33,    89,   790,   862,   792,    19,
      34,    23,    23,    36,    22,    34,    38,    34,    36,    39,
      36,    23,    31,    89,    23,    23,  1321,    34,    23,    34,
      23,    32,    23,    23,    34,    39,    24,    19,    30,    19,
      37,   896,    89,   898,    38,    34,    19,    30,    19,    89,
      37,    37,    30,    32,    39,    89,    33,    32,    32,    89,
      36,  1355,    89,    33,    31,    34,    23,    27,    34,    23,
      42,    36,    24,    34,    89,    39,    38,    19,    22,    38,
      19,    31,    23,    19,    37,    19,    33,    30,    33,    19,
      36,    39,    32,    89,  1389,    32,    19,    23,    33,    32,
      31,    39,    31,    24,    36,    24,    19,   802,   803,   804,
      38,    38,    36,    38,    36,    22,    27,    23,    32,    23,
      19,    23,    32,    19,    33,    33,    38,    32,    31,    22,
    1132,    89,  1138,  1224,    31,    36,    23,    32,    36,    27,
      40,    31,    23,    23,    38,    23,    38,    38,    23,    38,
      23,    23,   936,    38,    40,    26,   940,    36,    23,    36,
    1015,  1456,    38,    37,  1019,    33,    36,   951,    23,    38,
      23,    30,    36,    36,    36,    36,  1031,    37,    22,   985,
    1495,  1036,  1118,    50,   288,   288,   970,    -1,   288,    -1,
     550,   975,    -1,    -1,   978,   979,    -1,   981,    -1,   983,
      -1,    -1,    -1,   283,  1059,   283,   283,    -1,    -1,    -1,
      -1,    -1,    -1,   908,   909,   910,   288,  1072,    -1,    -1,
      -1,    -1,    -1,  1078,   288,  1080,   288,    -1,    -1,    -1,
      -1,    -1,   288,    -1,   288,   288,    -1,   288,   284,   283,
     283,   286,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   952,    -1,    -1,
     286,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   283,
     283,    -1,    -1,    -1,    -1,    -1,    -1,   283,    -1,    -1,
      -1,    -1,   977,    -1,    -1,   980,    -1,   982,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   992,   993,    -1,
      -1,    -1,    -1,    -1,  1159,  1160,    -1,   288,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1107,  1108,  1109,  1110,    -1,    -1,  1113,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1032,  1033,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1117,  1118,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1133,  1134,
      -1,    -1,    -1,    -1,  1139,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1355,     3,     4,     5,     6,     7,     8,     9,    10,    11,
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
     222,    -1,   224,     3,     4,     5,     6,     7,     8,     9,
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
     220,   221,    -1,   223,   224,     3,     4,     5,     6,     7,
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
     218,   219,   220,   221,    -1,    -1,   224,     3,     4,     5,
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
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
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
     220,   221
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     1,     3,    19,    21,    22,    25,    30,    31,    35,
      36,    37,    39,   228,   229,   230,   231,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   298,   299,   300,   301,
     302,   361,   365,    22,    30,    36,    23,    23,    27,    33,
      19,    39,    23,    23,    39,    32,     0,   225,   226,   283,
     284,     3,     4,     5,     6,     7,     8,     9,    10,    11,
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
     224,   274,   277,   278,   279,   282,   282,   282,   282,   282,
     282,   282,   282,   282,   282,   282,   282,   282,   282,   282,
     282,    22,    23,    23,    37,    38,    37,    19,    34,    27,
      31,    37,    30,    38,    20,    31,    37,   283,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,   276,   277,
     276,   276,   276,   276,   276,   276,   276,   276,     3,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,   279,
      21,    31,   232,   303,   344,    19,    21,    23,    24,    31,
      37,    38,    40,   238,   303,   304,   305,   306,   321,   322,
     324,   329,   330,   331,   332,   333,   334,   336,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   352,   353,
     354,   355,    31,   235,   342,   236,   342,    31,   242,   343,
      19,    24,    31,   240,   330,   340,   352,   243,   330,   340,
     352,    19,    21,    24,    31,   248,   304,   305,   306,   329,
     336,   339,   343,   345,   353,    27,   244,   323,   324,   237,
     303,   344,    19,    23,    31,   239,   303,   328,   333,   337,
     338,   344,   352,   355,   364,    19,    20,    21,    31,    37,
      38,    40,   233,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   362,   234,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   362,   274,   280,   282,   241,   303,    19,
      19,    38,    38,    22,    38,    33,    23,    23,    37,    19,
      39,   277,    26,    27,   282,    39,    40,    26,    32,    42,
      27,    23,    33,    33,   282,   282,   282,   282,   282,   282,
     282,   282,   282,   282,   282,   282,   282,   282,   282,   282,
     282,   282,    27,   282,   282,    27,   282,    39,    42,    27,
     282,   282,   282,   282,   282,   282,    39,    26,    42,    27,
     282,   282,    32,   282,   282,   282,   282,    39,    21,    27,
     282,   282,   282,   282,   282,   282,   282,   282,   282,    39,
      39,    26,    27,    38,    33,    33,   274,   282,   282,    36,
      38,    36,    40,    38,    21,    21,    34,    20,    19,    22,
     222,   223,   268,   281,    22,    19,    19,    25,    89,    22,
      36,    38,    30,    27,   307,   318,   319,   320,   307,   307,
     307,   307,   307,   307,   307,   307,   307,   307,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,   258,   278,
     294,   307,   307,   307,   307,   263,   278,   307,    22,   258,
     258,    22,   258,   294,    22,    89,    22,   274,   274,   263,
     278,   278,   263,    22,    19,    89,    22,   258,   294,   263,
      37,    32,   249,   267,   281,   297,   250,   266,   274,   263,
     258,   294,    22,    26,    22,    19,    31,    37,   245,   330,
     334,   335,   340,   344,   347,   348,   349,   350,   355,   357,
     358,   278,   278,   278,   278,    32,   363,    19,    30,    31,
     334,   351,   356,     7,     8,   262,   275,   276,   277,   278,
     273,   274,   278,    22,    24,    19,    22,    37,    36,    38,
      27,   263,    23,    33,    23,    38,    36,    37,    32,    27,
     280,   280,    27,    27,    32,    27,    37,    27,    40,    19,
      39,    32,   282,   282,   282,   282,   282,   282,   282,   282,
     282,   282,   282,   282,   282,   282,    30,   282,   282,   282,
     282,    27,   282,   282,    27,    27,    37,    27,   282,   282,
     282,   282,    27,    32,    37,    27,    38,    33,   282,   282,
     282,    27,    33,    27,    39,    27,    39,    33,   282,   282,
     282,   282,   282,   282,   282,   282,   282,   282,   282,   282,
     282,   282,   282,   282,    19,   282,    39,    23,    27,   282,
     282,   282,   276,   276,     6,    27,    24,    32,    27,    21,
      23,    19,    21,    43,    27,    21,    32,    89,   222,   223,
      33,    30,    32,    32,    23,    89,    23,    30,    31,    24,
     263,    20,    34,   247,   359,   360,   263,   263,   266,   278,
     274,   274,   278,   278,   278,   278,   274,   258,    30,   258,
     274,   278,   263,    89,   259,   278,   259,    89,    33,    23,
      89,   246,   274,   246,   261,   278,   265,   278,    33,    32,
      23,    89,    36,    32,   264,   278,   267,   263,    33,    89,
      22,    22,    38,    30,   263,   263,   263,   263,   263,   263,
     263,   263,   263,   263,   263,   263,   274,   278,   274,   278,
      31,   258,    22,    40,    22,   263,   263,   263,     6,     6,
     276,    33,    23,    32,    89,    23,    19,    30,    23,    20,
      36,    23,    27,    89,    19,    23,    23,    32,    27,    36,
      89,    23,    33,    43,    23,   282,   282,   282,   282,   282,
     282,   282,   282,   282,    27,   282,   282,    27,    89,    32,
      27,   282,     4,   282,    89,    23,    32,    27,    39,    89,
     282,   282,    89,    27,    27,    27,    23,    33,   282,   282,
     282,   282,   282,   282,   282,   282,   282,   282,   282,   282,
       4,   282,     4,   282,    23,   282,    27,    23,    27,   282,
     282,   282,   276,   276,    89,    36,    23,    27,    30,    31,
      89,    89,    23,    27,    30,    32,    33,    20,    30,    22,
      32,    40,    38,    36,   263,   274,   278,   278,   278,   274,
     259,   278,   265,    32,   260,   278,   260,    32,    33,    22,
      32,   274,     7,     8,   271,   272,   274,   275,   278,   281,
     270,   281,    33,    30,    22,    32,    31,    31,   263,   264,
      33,    32,    33,    89,   252,   278,   253,   278,   254,   274,
     252,    22,    32,   258,   295,   296,   255,   278,   256,   278,
     294,   257,   274,   252,   262,   273,   273,   271,   274,   271,
     274,   268,    33,    30,    89,   265,   265,   265,    33,    89,
      30,    32,    30,    89,    40,    21,    20,    37,    39,    30,
      37,    37,    34,    37,    33,    23,    21,   282,   282,   282,
     282,   282,    37,   282,    37,    39,    34,     4,     5,    39,
      34,    37,    23,    33,   282,    39,    34,    89,    27,   282,
      23,    33,   282,     4,     4,    89,    21,   282,   282,   282,
      39,    24,    89,    34,    37,    19,    21,    33,    33,    23,
      38,    38,    23,    39,    38,    27,    37,    23,   246,   274,
     274,   246,   260,    38,   266,    38,    38,    39,   271,   272,
      38,    39,    38,    32,    22,   263,    38,    39,    33,    32,
     253,    24,    32,   255,   271,   271,    33,    33,   253,   261,
     262,    38,    27,    21,    27,    39,    38,    32,    33,    27,
      39,    36,    34,    89,    38,    36,    21,    32,    36,   282,
      36,    34,    38,    34,    38,    36,    38,    19,    34,    38,
      39,    34,    19,    23,   282,    39,    32,   282,    34,    30,
      33,    32,    38,    36,    23,    39,    21,    32,    39,    39,
      19,    23,    31,    89,    39,    23,    38,    39,   267,    39,
      39,    89,    39,    89,    39,    30,    39,    89,    38,    39,
      39,   256,    38,    38,   253,    39,    30,    39,    24,    89,
      39,    33,    32,    23,    38,    31,    38,    39,    32,    27,
      22,    34,    31,    89,    19,    31,   282,    31,    38,    22,
      38,    22,    31,    38,    22,    34,    34,    38,    30,    34,
      36,    38,    32,    33,    22,    31,    39,    38,    89,    23,
      89,    22,    25,    22,    23,    36,    33,    23,    21,    25,
      23,   264,    23,    89,    23,    89,    23,    23,    89,    23,
      33,    39,    89,    38,    39,    33,    89,    38,    23,    23,
      37,    21,    32,    21,    22,    27,    27,    27,    40,    27,
      36,    32,    33,    23,    32,   282,    32,    22,    40,    22,
      40,    32,    21,    22,    40,    36,    38,    21,    34,    38,
      38,    30,    22,    40,    32,    33,    38,    26,    23,    36,
      33,    32,    89,    27,    40,    38,    38,    39,    38,   262,
      38,    23,    27,    23,    27,    38,    26,    23,    27,    38,
      89,    26,    33,    43,    89,    30,    23,    27,    38,    39,
      89,    19,    40,    27,    89,    23,    27,    21,    23,    89,
      37,    89,    32,   282,    40,    21,    40,    21,    89,    19,
      40,    21,    21,    38,    19,    36,    34,    23,    40,    21,
      89,    32,    31,    32,    27,    40,    33,    37,    32,    23,
      36,    34,    31,    38,    33,    34,   251,   269,   281,   325,
     326,   327,    27,    23,    27,    23,    31,    32,    27,    23,
      26,    43,    32,    38,    23,    36,    27,    23,    21,    27,
      31,    38,    19,    32,    21,    23,    39,    34,    37,    89,
      19,    19,    89,    32,    23,   282,    21,    21,    19,    32,
      21,    89,    19,    34,    32,    21,    89,    33,    32,    19,
      34,    23,    23,    36,    38,    39,    34,    36,    34,    31,
      89,    36,   269,    23,    23,    34,    23,    23,    34,    32,
      23,    23,    23,    21,    27,    39,    24,    34,    30,    37,
      89,    34,    38,    19,    19,    37,    19,    22,    37,    30,
      89,    19,    32,    30,    89,    33,    32,    32,    33,    89,
      89,    34,    39,    89,    36,    31,    42,    23,    27,    34,
      36,    23,    21,    27,    39,    24,    38,    21,    27,    34,
      19,    38,    22,    19,    23,    31,    37,    19,    19,    30,
      33,    32,    32,    33,    33,    32,    19,    36,    89,    36,
      31,    38,    19,    38,    36,    31,    39,    24,    38,    39,
      24,    36,    19,    22,    27,    23,    23,    32,    23,    19,
      23,    32,    33,    32,    33,    19,    31,    36,    40,    38,
      36,    22,    32,    31,    38,    38,    38,    31,    23,    27,
      23,    23,    89,    38,    23,    23,    23,    38,    40,    36,
      36,    26,    38,    36,    38,    23,    23,    37,    33,    23,
      23,    36,    36,    30,    36,    36,    37,    22
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
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
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_audio_device_count);   }
    break;

  case 34:
#line 138 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_audio_device_info);    }
    break;

  case 35:
#line 139 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_device_count);    }
    break;

  case 36:
#line 140 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_device_info);     }
    break;

  case 37:
#line 141 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_channel_count);        }
    break;

  case 38:
#line 142 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_voice_count);          }
    break;

  case 39:
#line 143 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_stream_count);         }
    break;

  case 40:
#line 144 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_buffer_fill);          }
    break;

  case 41:
#line 145 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_channel_info);         }
    break;

  case 42:
#line 146 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_instr_map_count); }
    break;

  case 43:
#line 147 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_instr_map_info);  }
    break;

  case 44:
#line 148 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_instr_count);     }
    break;

  case 45:
#line 149 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_instr_info);      }
    break;

  case 46:
#line 150 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_misc);                 }
    break;

  case 47:
#line 151 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_total_voice_count);    }
    break;

  case 48:
#line 154 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_audio_device_count);   }
    break;

  case 49:
#line 155 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_audio_device_info);    }
    break;

  case 50:
#line 156 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_device_count);    }
    break;

  case 51:
#line 157 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_device_info);     }
    break;

  case 52:
#line 158 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_channel_count);        }
    break;

  case 53:
#line 159 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_voice_count);          }
    break;

  case 54:
#line 160 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_stream_count);         }
    break;

  case 55:
#line 161 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_buffer_fill);          }
    break;

  case 56:
#line 162 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_channel_info);         }
    break;

  case 57:
#line 163 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_instr_map_count); }
    break;

  case 58:
#line 164 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_instr_map_info);  }
    break;

  case 59:
#line 165 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_instr_count);     }
    break;

  case 60:
#line 166 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_instr_info);      }
    break;

  case 61:
#line 167 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_misc);                 }
    break;

  case 62:
#line 168 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_total_voice_count);    }
    break;

  case 63:
#line 171 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping((yyvsp[(3) - (15)].Number),(yyvsp[(5) - (15)].Number),(yyvsp[(7) - (15)].Number),(yyvsp[(9) - (15)].String),(yyvsp[(11) - (15)].String),(yyvsp[(13) - (15)].Number),(yyvsp[(15) - (15)].Dotnum),MidiInstrumentMapper::VOID,""); }
    break;

  case 64:
#line 172 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping((yyvsp[(3) - (17)].Number),(yyvsp[(5) - (17)].Number),(yyvsp[(7) - (17)].Number),(yyvsp[(9) - (17)].String),(yyvsp[(11) - (17)].String),(yyvsp[(13) - (17)].Number),(yyvsp[(15) - (17)].Dotnum),(yyvsp[(17) - (17)].LoadMode),""); }
    break;

  case 65:
#line 173 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping((yyvsp[(3) - (17)].Number),(yyvsp[(5) - (17)].Number),(yyvsp[(7) - (17)].Number),(yyvsp[(9) - (17)].String),(yyvsp[(11) - (17)].String),(yyvsp[(13) - (17)].Number),(yyvsp[(15) - (17)].Dotnum),MidiInstrumentMapper::VOID,(yyvsp[(17) - (17)].String)); }
    break;

  case 66:
#line 174 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping((yyvsp[(3) - (19)].Number),(yyvsp[(5) - (19)].Number),(yyvsp[(7) - (19)].Number),(yyvsp[(9) - (19)].String),(yyvsp[(11) - (19)].String),(yyvsp[(13) - (19)].Number),(yyvsp[(15) - (19)].Dotnum),(yyvsp[(17) - (19)].LoadMode),(yyvsp[(19) - (19)].String)); }
    break;

  case 67:
#line 177 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveMIDIInstrumentMapping((yyvsp[(3) - (7)].Number),(yyvsp[(5) - (7)].Number),(yyvsp[(7) - (7)].Number)); }
    break;

  case 68:
#line 180 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveChannel((yyvsp[(3) - (3)].Number));             }
    break;

  case 69:
#line 181 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveMidiInstrumentMap((yyvsp[(3) - (3)].Number));   }
    break;

  case 70:
#line 182 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveAllMidiInstrumentMaps(); }
    break;

  case 71:
#line 185 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAvailableEngines();                          }
    break;

  case 72:
#line 186 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAvailableMidiInputDrivers();                 }
    break;

  case 73:
#line 187 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDriverInfo((yyvsp[(5) - (5)].String));                     }
    break;

  case 74:
#line 188 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDriverParameterInfo((yyvsp[(5) - (7)].String), (yyvsp[(7) - (7)].String));        }
    break;

  case 75:
#line 189 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDriverParameterInfo((yyvsp[(5) - (9)].String), (yyvsp[(7) - (9)].String), (yyvsp[(9) - (9)].KeyValList));    }
    break;

  case 76:
#line 190 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAvailableAudioOutputDrivers();               }
    break;

  case 77:
#line 191 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDriverInfo((yyvsp[(5) - (5)].String));                   }
    break;

  case 78:
#line 192 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDriverParameterInfo((yyvsp[(5) - (7)].String), (yyvsp[(7) - (7)].String));      }
    break;

  case 79:
#line 193 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDriverParameterInfo((yyvsp[(5) - (9)].String), (yyvsp[(7) - (9)].String), (yyvsp[(9) - (9)].KeyValList));  }
    break;

  case 80:
#line 194 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDeviceCount();                    }
    break;

  case 81:
#line 195 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDeviceCount();                      }
    break;

  case 82:
#line 196 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDeviceInfo((yyvsp[(5) - (5)].Number));                   }
    break;

  case 83:
#line 197 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDeviceInfo((yyvsp[(5) - (5)].Number));                     }
    break;

  case 84:
#line 198 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputPortInfo((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number));                   }
    break;

  case 85:
#line 199 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputPortParameterInfo((yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].Number), (yyvsp[(9) - (9)].String));      }
    break;

  case 86:
#line 200 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputChannelInfo((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number));              }
    break;

  case 87:
#line 201 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputChannelParameterInfo((yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].Number), (yyvsp[(9) - (9)].String)); }
    break;

  case 88:
#line 202 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetChannels();                                  }
    break;

  case 89:
#line 203 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetChannelInfo((yyvsp[(5) - (5)].Number));                             }
    break;

  case 90:
#line 204 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetBufferFill((yyvsp[(5) - (7)].FillResponse), (yyvsp[(7) - (7)].Number));                          }
    break;

  case 91:
#line 205 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetStreamCount((yyvsp[(5) - (5)].Number));                             }
    break;

  case 92:
#line 206 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetVoiceCount((yyvsp[(5) - (5)].Number));                              }
    break;

  case 93:
#line 207 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetEngineInfo((yyvsp[(5) - (5)].String));                              }
    break;

  case 94:
#line 208 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetServerInfo();                                }
    break;

  case 95:
#line 209 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetTotalVoiceCount();                                }
    break;

  case 96:
#line 210 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetTotalVoiceCountMax();                        }
    break;

  case 97:
#line 211 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInstrumentMappings((yyvsp[(3) - (3)].Number));                  }
    break;

  case 98:
#line 212 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAllMidiInstrumentMappings();                 }
    break;

  case 99:
#line 213 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInstrumentMapping((yyvsp[(5) - (9)].Number),(yyvsp[(7) - (9)].Number),(yyvsp[(9) - (9)].Number));             }
    break;

  case 100:
#line 214 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInstrumentMaps();                        }
    break;

  case 101:
#line 215 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInstrumentMap((yyvsp[(5) - (5)].Number));                       }
    break;

  case 102:
#line 216 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetFxSends((yyvsp[(3) - (3)].Number));                                 }
    break;

  case 103:
#line 217 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetFxSendInfo((yyvsp[(5) - (7)].Number),(yyvsp[(7) - (7)].Number));                           }
    break;

  case 104:
#line 218 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetGlobalVolume();                              }
    break;

  case 105:
#line 221 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputDeviceParameter((yyvsp[(3) - (7)].Number), (yyvsp[(5) - (7)].String), (yyvsp[(7) - (7)].String));      }
    break;

  case 106:
#line 222 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputChannelParameter((yyvsp[(3) - (9)].Number), (yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].String), (yyvsp[(9) - (9)].String)); }
    break;

  case 107:
#line 223 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMidiInputDeviceParameter((yyvsp[(3) - (7)].Number), (yyvsp[(5) - (7)].String), (yyvsp[(7) - (7)].String));        }
    break;

  case 108:
#line 224 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMidiInputPortParameter((yyvsp[(3) - (9)].Number), (yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].String), (yyvsp[(9) - (9)].String));      }
    break;

  case 109:
#line 225 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                         }
    break;

  case 110:
#line 226 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMidiInstrumentMapName((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].String));               }
    break;

  case 111:
#line 227 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetFxSendAudioOutputChannel((yyvsp[(5) - (11)].Number),(yyvsp[(7) - (11)].Number),(yyvsp[(9) - (11)].Number),(yyvsp[(11) - (11)].Number)); }
    break;

  case 112:
#line 228 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetFxSendMidiController((yyvsp[(5) - (9)].Number),(yyvsp[(7) - (9)].Number),(yyvsp[(9) - (9)].Number));              }
    break;

  case 113:
#line 229 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetFxSendLevel((yyvsp[(5) - (9)].Number),(yyvsp[(7) - (9)].Number),(yyvsp[(9) - (9)].Dotnum));                       }
    break;

  case 114:
#line 230 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetEcho((yyparse_param_t*) yyparse_param, (yyvsp[(3) - (3)].Dotnum));  }
    break;

  case 115:
#line 231 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetGlobalVolume((yyvsp[(3) - (3)].Dotnum));                            }
    break;

  case 116:
#line 234 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateAudioOutputDevice((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].KeyValList)); }
    break;

  case 117:
#line 235 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateAudioOutputDevice((yyvsp[(3) - (3)].String));    }
    break;

  case 118:
#line 236 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateMidiInputDevice((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].KeyValList));   }
    break;

  case 119:
#line 237 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateMidiInputDevice((yyvsp[(3) - (3)].String));      }
    break;

  case 120:
#line 238 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateFxSend((yyvsp[(3) - (5)].Number),(yyvsp[(5) - (5)].Number));            }
    break;

  case 121:
#line 239 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateFxSend((yyvsp[(3) - (7)].Number),(yyvsp[(5) - (7)].Number),(yyvsp[(7) - (7)].String)); }
    break;

  case 122:
#line 242 "lscp.y"
    { (yyval.String) = LSCPSERVER->ResetChannel((yyvsp[(3) - (3)].Number)); }
    break;

  case 123:
#line 245 "lscp.y"
    { (yyval.String) = LSCPSERVER->ClearMidiInstrumentMappings((yyvsp[(3) - (3)].Number));  }
    break;

  case 124:
#line 246 "lscp.y"
    { (yyval.String) = LSCPSERVER->ClearAllMidiInstrumentMappings(); }
    break;

  case 125:
#line 249 "lscp.y"
    { (yyval.String) = LSCPSERVER->DestroyAudioOutputDevice((yyvsp[(3) - (3)].Number)); }
    break;

  case 126:
#line 250 "lscp.y"
    { (yyval.String) = LSCPSERVER->DestroyMidiInputDevice((yyvsp[(3) - (3)].Number));   }
    break;

  case 127:
#line 251 "lscp.y"
    { (yyval.String) = LSCPSERVER->DestroyFxSend((yyvsp[(3) - (5)].Number),(yyvsp[(5) - (5)].Number)); }
    break;

  case 128:
#line 254 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String); }
    break;

  case 129:
#line 255 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String); }
    break;

  case 130:
#line 258 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputDevice((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));      }
    break;

  case 131:
#line 259 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputChannel((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number), (yyvsp[(3) - (7)].Number)); }
    break;

  case 132:
#line 260 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputType((yyvsp[(5) - (5)].String), (yyvsp[(3) - (5)].Number));        }
    break;

  case 133:
#line 261 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInput((yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].Number), (yyvsp[(9) - (9)].Number), (yyvsp[(3) - (9)].Number));      }
    break;

  case 134:
#line 262 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputDevice((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));        }
    break;

  case 135:
#line 263 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputPort((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));          }
    break;

  case 136:
#line 264 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputChannel((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));       }
    break;

  case 137:
#line 265 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputType((yyvsp[(5) - (5)].String), (yyvsp[(3) - (5)].Number));          }
    break;

  case 138:
#line 266 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetVolume((yyvsp[(5) - (5)].Dotnum), (yyvsp[(3) - (5)].Number));                 }
    break;

  case 139:
#line 267 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMute((yyvsp[(5) - (5)].Dotnum), (yyvsp[(3) - (5)].Number));            }
    break;

  case 140:
#line 268 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelSolo((yyvsp[(5) - (5)].Dotnum), (yyvsp[(3) - (5)].Number));            }
    break;

  case 141:
#line 269 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMap((yyvsp[(3) - (5)].Number), (yyvsp[(5) - (5)].Number));             }
    break;

  case 142:
#line 270 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMap((yyvsp[(3) - (5)].Number), -1);             }
    break;

  case 143:
#line 271 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMap((yyvsp[(3) - (5)].Number), -2);             }
    break;

  case 144:
#line 274 "lscp.y"
    { (yyval.KeyValList)[(yyvsp[(1) - (3)].String)] = (yyvsp[(3) - (3)].String);          }
    break;

  case 145:
#line 275 "lscp.y"
    { (yyval.KeyValList) = (yyvsp[(1) - (5)].KeyValList); (yyval.KeyValList)[(yyvsp[(3) - (5)].String)] = (yyvsp[(5) - (5)].String); }
    break;

  case 146:
#line 278 "lscp.y"
    { (yyval.FillResponse) = fill_response_bytes;      }
    break;

  case 147:
#line 279 "lscp.y"
    { (yyval.FillResponse) = fill_response_percentage; }
    break;

  case 148:
#line 282 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDevices();           }
    break;

  case 149:
#line 283 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDevices();             }
    break;

  case 150:
#line 284 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListChannels();                    }
    break;

  case 151:
#line 285 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableEngines();            }
    break;

  case 152:
#line 286 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableMidiInputDrivers();   }
    break;

  case 153:
#line 287 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableAudioOutputDrivers(); }
    break;

  case 154:
#line 288 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListMidiInstrumentMappings((yyvsp[(3) - (3)].Number));    }
    break;

  case 155:
#line 289 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAllMidiInstrumentMappings();   }
    break;

  case 156:
#line 290 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListMidiInstrumentMaps();          }
    break;

  case 157:
#line 291 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListFxSends((yyvsp[(3) - (3)].Number));                   }
    break;

  case 158:
#line 294 "lscp.y"
    { (yyval.String) = LSCPSERVER->LoadInstrument((yyvsp[(1) - (5)].String), (yyvsp[(3) - (5)].Number), (yyvsp[(5) - (5)].Number));       }
    break;

  case 159:
#line 295 "lscp.y"
    { (yyval.String) = LSCPSERVER->LoadInstrument((yyvsp[(3) - (7)].String), (yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number), true); }
    break;

  case 160:
#line 298 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetEngineType((yyvsp[(1) - (3)].String), (yyvsp[(3) - (3)].Number)); }
    break;

  case 161:
#line 301 "lscp.y"
    { (yyval.LoadMode) = MidiInstrumentMapper::ON_DEMAND;      }
    break;

  case 162:
#line 302 "lscp.y"
    { (yyval.LoadMode) = MidiInstrumentMapper::ON_DEMAND_HOLD; }
    break;

  case 163:
#line 303 "lscp.y"
    { (yyval.LoadMode) = MidiInstrumentMapper::PERSISTENT;     }
    break;

  case 169:
#line 319 "lscp.y"
    { (yyval.Number) = 16; }
    break;

  case 176:
#line 338 "lscp.y"
    { (yyval.Dotnum) = (yyvsp[(1) - (1)].Number); }
    break;

  case 186:
#line 366 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (3)].String) + "," + (yyvsp[(3) - (3)].String); }
    break;

  case 189:
#line 371 "lscp.y"
    { std::stringstream ss; ss << "\'" << (yyvsp[(1) - (1)].Number) << "\'"; (yyval.String) = ss.str(); }
    break;

  case 190:
#line 372 "lscp.y"
    { std::stringstream ss; ss << "\'" << (yyvsp[(1) - (1)].Dotnum) << "\'"; (yyval.String) = ss.str(); }
    break;

  case 191:
#line 380 "lscp.y"
    { (yyval.Dotnum) = (yyvsp[(1) - (1)].Number); }
    break;

  case 192:
#line 381 "lscp.y"
    { (yyval.Dotnum) = -1; }
    break;

  case 193:
#line 384 "lscp.y"
    { std::string s; s = (yyvsp[(1) - (1)].Char); (yyval.String) = s; }
    break;

  case 194:
#line 385 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + (yyvsp[(2) - (2)].Char);                  }
    break;

  case 195:
#line 388 "lscp.y"
    { (yyval.Dotnum) = atof(String((yyvsp[(1) - (3)].String) + "." + (yyvsp[(3) - (3)].String)).c_str());                         }
    break;

  case 196:
#line 389 "lscp.y"
    { String s = "+"; s += (yyvsp[(2) - (4)].String); s += "."; s += (yyvsp[(4) - (4)].String); (yyval.Dotnum) = atof(s.c_str()); }
    break;

  case 197:
#line 390 "lscp.y"
    { (yyval.Dotnum) = atof(String("-" + (yyvsp[(2) - (4)].String) + "." + (yyvsp[(4) - (4)].String)).c_str());                   }
    break;

  case 198:
#line 394 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (1)].Char);      }
    break;

  case 199:
#line 395 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + (yyvsp[(2) - (2)].Char); }
    break;

  case 200:
#line 398 "lscp.y"
    { (yyval.Char) = '0'; }
    break;

  case 201:
#line 399 "lscp.y"
    { (yyval.Char) = '1'; }
    break;

  case 202:
#line 400 "lscp.y"
    { (yyval.Char) = '2'; }
    break;

  case 203:
#line 401 "lscp.y"
    { (yyval.Char) = '3'; }
    break;

  case 204:
#line 402 "lscp.y"
    { (yyval.Char) = '4'; }
    break;

  case 205:
#line 403 "lscp.y"
    { (yyval.Char) = '5'; }
    break;

  case 206:
#line 404 "lscp.y"
    { (yyval.Char) = '6'; }
    break;

  case 207:
#line 405 "lscp.y"
    { (yyval.Char) = '7'; }
    break;

  case 208:
#line 406 "lscp.y"
    { (yyval.Char) = '8'; }
    break;

  case 209:
#line 407 "lscp.y"
    { (yyval.Char) = '9'; }
    break;

  case 210:
#line 410 "lscp.y"
    { (yyval.Number) = atoi(String(1, (yyvsp[(1) - (1)].Char)).c_str());      }
    break;

  case 211:
#line 411 "lscp.y"
    { (yyval.Number) = atoi(String(String("1") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 212:
#line 412 "lscp.y"
    { (yyval.Number) = atoi(String(String("2") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 213:
#line 413 "lscp.y"
    { (yyval.Number) = atoi(String(String("3") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 214:
#line 414 "lscp.y"
    { (yyval.Number) = atoi(String(String("4") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 215:
#line 415 "lscp.y"
    { (yyval.Number) = atoi(String(String("5") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 216:
#line 416 "lscp.y"
    { (yyval.Number) = atoi(String(String("6") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 217:
#line 417 "lscp.y"
    { (yyval.Number) = atoi(String(String("7") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 218:
#line 418 "lscp.y"
    { (yyval.Number) = atoi(String(String("8") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 219:
#line 419 "lscp.y"
    { (yyval.Number) = atoi(String(String("9") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 220:
#line 421 "lscp.y"
    { (yyval.Char) = 'A'; }
    break;

  case 221:
#line 421 "lscp.y"
    { (yyval.Char) = 'B'; }
    break;

  case 222:
#line 421 "lscp.y"
    { (yyval.Char) = 'C'; }
    break;

  case 223:
#line 421 "lscp.y"
    { (yyval.Char) = 'D'; }
    break;

  case 224:
#line 421 "lscp.y"
    { (yyval.Char) = 'E'; }
    break;

  case 225:
#line 421 "lscp.y"
    { (yyval.Char) = 'F'; }
    break;

  case 226:
#line 421 "lscp.y"
    { (yyval.Char) = 'G'; }
    break;

  case 227:
#line 421 "lscp.y"
    { (yyval.Char) = 'H'; }
    break;

  case 228:
#line 421 "lscp.y"
    { (yyval.Char) = 'I'; }
    break;

  case 229:
#line 421 "lscp.y"
    { (yyval.Char) = 'J'; }
    break;

  case 230:
#line 421 "lscp.y"
    { (yyval.Char) = 'K'; }
    break;

  case 231:
#line 421 "lscp.y"
    { (yyval.Char) = 'L'; }
    break;

  case 232:
#line 421 "lscp.y"
    { (yyval.Char) = 'M'; }
    break;

  case 233:
#line 421 "lscp.y"
    { (yyval.Char) = 'N'; }
    break;

  case 234:
#line 421 "lscp.y"
    { (yyval.Char) = 'O'; }
    break;

  case 235:
#line 421 "lscp.y"
    { (yyval.Char) = 'P'; }
    break;

  case 236:
#line 421 "lscp.y"
    { (yyval.Char) = 'Q'; }
    break;

  case 237:
#line 421 "lscp.y"
    { (yyval.Char) = 'R'; }
    break;

  case 238:
#line 421 "lscp.y"
    { (yyval.Char) = 'S'; }
    break;

  case 239:
#line 421 "lscp.y"
    { (yyval.Char) = 'T'; }
    break;

  case 240:
#line 421 "lscp.y"
    { (yyval.Char) = 'U'; }
    break;

  case 241:
#line 421 "lscp.y"
    { (yyval.Char) = 'V'; }
    break;

  case 242:
#line 421 "lscp.y"
    { (yyval.Char) = 'W'; }
    break;

  case 243:
#line 421 "lscp.y"
    { (yyval.Char) = 'X'; }
    break;

  case 244:
#line 421 "lscp.y"
    { (yyval.Char) = 'Y'; }
    break;

  case 245:
#line 421 "lscp.y"
    { (yyval.Char) = 'Z'; }
    break;

  case 246:
#line 422 "lscp.y"
    { (yyval.Char) = 'a'; }
    break;

  case 247:
#line 422 "lscp.y"
    { (yyval.Char) = 'b'; }
    break;

  case 248:
#line 422 "lscp.y"
    { (yyval.Char) = 'c'; }
    break;

  case 249:
#line 422 "lscp.y"
    { (yyval.Char) = 'd'; }
    break;

  case 250:
#line 422 "lscp.y"
    { (yyval.Char) = 'e'; }
    break;

  case 251:
#line 422 "lscp.y"
    { (yyval.Char) = 'f'; }
    break;

  case 252:
#line 422 "lscp.y"
    { (yyval.Char) = 'g'; }
    break;

  case 253:
#line 422 "lscp.y"
    { (yyval.Char) = 'h'; }
    break;

  case 254:
#line 422 "lscp.y"
    { (yyval.Char) = 'i'; }
    break;

  case 255:
#line 422 "lscp.y"
    { (yyval.Char) = 'j'; }
    break;

  case 256:
#line 422 "lscp.y"
    { (yyval.Char) = 'k'; }
    break;

  case 257:
#line 422 "lscp.y"
    { (yyval.Char) = 'l'; }
    break;

  case 258:
#line 422 "lscp.y"
    { (yyval.Char) = 'm'; }
    break;

  case 259:
#line 422 "lscp.y"
    { (yyval.Char) = 'n'; }
    break;

  case 260:
#line 422 "lscp.y"
    { (yyval.Char) = 'o'; }
    break;

  case 261:
#line 422 "lscp.y"
    { (yyval.Char) = 'p'; }
    break;

  case 262:
#line 422 "lscp.y"
    { (yyval.Char) = 'q'; }
    break;

  case 263:
#line 422 "lscp.y"
    { (yyval.Char) = 'r'; }
    break;

  case 264:
#line 422 "lscp.y"
    { (yyval.Char) = 's'; }
    break;

  case 265:
#line 422 "lscp.y"
    { (yyval.Char) = 't'; }
    break;

  case 266:
#line 422 "lscp.y"
    { (yyval.Char) = 'u'; }
    break;

  case 267:
#line 422 "lscp.y"
    { (yyval.Char) = 'v'; }
    break;

  case 268:
#line 422 "lscp.y"
    { (yyval.Char) = 'w'; }
    break;

  case 269:
#line 422 "lscp.y"
    { (yyval.Char) = 'x'; }
    break;

  case 270:
#line 422 "lscp.y"
    { (yyval.Char) = 'y'; }
    break;

  case 271:
#line 422 "lscp.y"
    { (yyval.Char) = 'z'; }
    break;

  case 272:
#line 423 "lscp.y"
    { (yyval.Char) = '0'; }
    break;

  case 273:
#line 423 "lscp.y"
    { (yyval.Char) = '1'; }
    break;

  case 274:
#line 423 "lscp.y"
    { (yyval.Char) = '2'; }
    break;

  case 275:
#line 423 "lscp.y"
    { (yyval.Char) = '3'; }
    break;

  case 276:
#line 423 "lscp.y"
    { (yyval.Char) = '4'; }
    break;

  case 277:
#line 423 "lscp.y"
    { (yyval.Char) = '5'; }
    break;

  case 278:
#line 423 "lscp.y"
    { (yyval.Char) = '6'; }
    break;

  case 279:
#line 423 "lscp.y"
    { (yyval.Char) = '7'; }
    break;

  case 280:
#line 423 "lscp.y"
    { (yyval.Char) = '8'; }
    break;

  case 281:
#line 423 "lscp.y"
    { (yyval.Char) = '9'; }
    break;

  case 282:
#line 424 "lscp.y"
    { (yyval.Char) = '!'; }
    break;

  case 283:
#line 424 "lscp.y"
    { (yyval.Char) = '#'; }
    break;

  case 284:
#line 424 "lscp.y"
    { (yyval.Char) = '$'; }
    break;

  case 285:
#line 424 "lscp.y"
    { (yyval.Char) = '%'; }
    break;

  case 286:
#line 424 "lscp.y"
    { (yyval.Char) = '&'; }
    break;

  case 287:
#line 424 "lscp.y"
    { (yyval.Char) = '('; }
    break;

  case 288:
#line 424 "lscp.y"
    { (yyval.Char) = ')'; }
    break;

  case 289:
#line 424 "lscp.y"
    { (yyval.Char) = '*'; }
    break;

  case 290:
#line 424 "lscp.y"
    { (yyval.Char) = '+'; }
    break;

  case 291:
#line 424 "lscp.y"
    { (yyval.Char) = '-'; }
    break;

  case 292:
#line 424 "lscp.y"
    { (yyval.Char) = '.'; }
    break;

  case 293:
#line 424 "lscp.y"
    { (yyval.Char) = ','; }
    break;

  case 294:
#line 424 "lscp.y"
    { (yyval.Char) = '/'; }
    break;

  case 295:
#line 425 "lscp.y"
    { (yyval.Char) = ':'; }
    break;

  case 296:
#line 425 "lscp.y"
    { (yyval.Char) = ';'; }
    break;

  case 297:
#line 425 "lscp.y"
    { (yyval.Char) = '<'; }
    break;

  case 298:
#line 425 "lscp.y"
    { (yyval.Char) = '='; }
    break;

  case 299:
#line 425 "lscp.y"
    { (yyval.Char) = '>'; }
    break;

  case 300:
#line 425 "lscp.y"
    { (yyval.Char) = '?'; }
    break;

  case 301:
#line 425 "lscp.y"
    { (yyval.Char) = '@'; }
    break;

  case 302:
#line 426 "lscp.y"
    { (yyval.Char) = '['; }
    break;

  case 303:
#line 426 "lscp.y"
    { (yyval.Char) = '\\'; }
    break;

  case 304:
#line 426 "lscp.y"
    { (yyval.Char) = ']'; }
    break;

  case 305:
#line 426 "lscp.y"
    { (yyval.Char) = '^'; }
    break;

  case 306:
#line 426 "lscp.y"
    { (yyval.Char) = '_'; }
    break;

  case 307:
#line 427 "lscp.y"
    { (yyval.Char) = '{'; }
    break;

  case 308:
#line 427 "lscp.y"
    { (yyval.Char) = '|'; }
    break;

  case 309:
#line 427 "lscp.y"
    { (yyval.Char) = '}'; }
    break;

  case 310:
#line 427 "lscp.y"
    { (yyval.Char) = '~'; }
    break;

  case 311:
#line 428 "lscp.y"
    { (yyval.Char) = '\200'; }
    break;

  case 312:
#line 428 "lscp.y"
    { (yyval.Char) = '\201'; }
    break;

  case 313:
#line 428 "lscp.y"
    { (yyval.Char) = '\202'; }
    break;

  case 314:
#line 429 "lscp.y"
    { (yyval.Char) = '\203'; }
    break;

  case 315:
#line 429 "lscp.y"
    { (yyval.Char) = '\204'; }
    break;

  case 316:
#line 429 "lscp.y"
    { (yyval.Char) = '\205'; }
    break;

  case 317:
#line 430 "lscp.y"
    { (yyval.Char) = '\206'; }
    break;

  case 318:
#line 430 "lscp.y"
    { (yyval.Char) = '\207'; }
    break;

  case 319:
#line 430 "lscp.y"
    { (yyval.Char) = '\210'; }
    break;

  case 320:
#line 431 "lscp.y"
    { (yyval.Char) = '\211'; }
    break;

  case 321:
#line 431 "lscp.y"
    { (yyval.Char) = '\212'; }
    break;

  case 322:
#line 431 "lscp.y"
    { (yyval.Char) = '\213'; }
    break;

  case 323:
#line 432 "lscp.y"
    { (yyval.Char) = '\214'; }
    break;

  case 324:
#line 432 "lscp.y"
    { (yyval.Char) = '\215'; }
    break;

  case 325:
#line 432 "lscp.y"
    { (yyval.Char) = '\216'; }
    break;

  case 326:
#line 433 "lscp.y"
    { (yyval.Char) = '\217'; }
    break;

  case 327:
#line 433 "lscp.y"
    { (yyval.Char) = '\220'; }
    break;

  case 328:
#line 433 "lscp.y"
    { (yyval.Char) = '\221'; }
    break;

  case 329:
#line 434 "lscp.y"
    { (yyval.Char) = '\222'; }
    break;

  case 330:
#line 434 "lscp.y"
    { (yyval.Char) = '\223'; }
    break;

  case 331:
#line 434 "lscp.y"
    { (yyval.Char) = '\224'; }
    break;

  case 332:
#line 435 "lscp.y"
    { (yyval.Char) = '\225'; }
    break;

  case 333:
#line 435 "lscp.y"
    { (yyval.Char) = '\226'; }
    break;

  case 334:
#line 435 "lscp.y"
    { (yyval.Char) = '\227'; }
    break;

  case 335:
#line 436 "lscp.y"
    { (yyval.Char) = '\230'; }
    break;

  case 336:
#line 436 "lscp.y"
    { (yyval.Char) = '\231'; }
    break;

  case 337:
#line 436 "lscp.y"
    { (yyval.Char) = '\232'; }
    break;

  case 338:
#line 437 "lscp.y"
    { (yyval.Char) = '\233'; }
    break;

  case 339:
#line 437 "lscp.y"
    { (yyval.Char) = '\234'; }
    break;

  case 340:
#line 437 "lscp.y"
    { (yyval.Char) = '\235'; }
    break;

  case 341:
#line 438 "lscp.y"
    { (yyval.Char) = '\236'; }
    break;

  case 342:
#line 438 "lscp.y"
    { (yyval.Char) = '\237'; }
    break;

  case 343:
#line 438 "lscp.y"
    { (yyval.Char) = '\240'; }
    break;

  case 344:
#line 439 "lscp.y"
    { (yyval.Char) = '\241'; }
    break;

  case 345:
#line 439 "lscp.y"
    { (yyval.Char) = '\242'; }
    break;

  case 346:
#line 439 "lscp.y"
    { (yyval.Char) = '\243'; }
    break;

  case 347:
#line 440 "lscp.y"
    { (yyval.Char) = '\244'; }
    break;

  case 348:
#line 440 "lscp.y"
    { (yyval.Char) = '\245'; }
    break;

  case 349:
#line 440 "lscp.y"
    { (yyval.Char) = '\246'; }
    break;

  case 350:
#line 441 "lscp.y"
    { (yyval.Char) = '\247'; }
    break;

  case 351:
#line 441 "lscp.y"
    { (yyval.Char) = '\250'; }
    break;

  case 352:
#line 441 "lscp.y"
    { (yyval.Char) = '\251'; }
    break;

  case 353:
#line 442 "lscp.y"
    { (yyval.Char) = '\252'; }
    break;

  case 354:
#line 442 "lscp.y"
    { (yyval.Char) = '\253'; }
    break;

  case 355:
#line 442 "lscp.y"
    { (yyval.Char) = '\254'; }
    break;

  case 356:
#line 443 "lscp.y"
    { (yyval.Char) = '\255'; }
    break;

  case 357:
#line 443 "lscp.y"
    { (yyval.Char) = '\256'; }
    break;

  case 358:
#line 443 "lscp.y"
    { (yyval.Char) = '\257'; }
    break;

  case 359:
#line 444 "lscp.y"
    { (yyval.Char) = '\260'; }
    break;

  case 360:
#line 444 "lscp.y"
    { (yyval.Char) = '\261'; }
    break;

  case 361:
#line 444 "lscp.y"
    { (yyval.Char) = '\262'; }
    break;

  case 362:
#line 445 "lscp.y"
    { (yyval.Char) = '\263'; }
    break;

  case 363:
#line 445 "lscp.y"
    { (yyval.Char) = '\264'; }
    break;

  case 364:
#line 445 "lscp.y"
    { (yyval.Char) = '\265'; }
    break;

  case 365:
#line 446 "lscp.y"
    { (yyval.Char) = '\266'; }
    break;

  case 366:
#line 446 "lscp.y"
    { (yyval.Char) = '\267'; }
    break;

  case 367:
#line 446 "lscp.y"
    { (yyval.Char) = '\270'; }
    break;

  case 368:
#line 447 "lscp.y"
    { (yyval.Char) = '\271'; }
    break;

  case 369:
#line 447 "lscp.y"
    { (yyval.Char) = '\272'; }
    break;

  case 370:
#line 447 "lscp.y"
    { (yyval.Char) = '\273'; }
    break;

  case 371:
#line 448 "lscp.y"
    { (yyval.Char) = '\274'; }
    break;

  case 372:
#line 448 "lscp.y"
    { (yyval.Char) = '\275'; }
    break;

  case 373:
#line 448 "lscp.y"
    { (yyval.Char) = '\276'; }
    break;

  case 374:
#line 449 "lscp.y"
    { (yyval.Char) = '\277'; }
    break;

  case 375:
#line 449 "lscp.y"
    { (yyval.Char) = '\300'; }
    break;

  case 376:
#line 449 "lscp.y"
    { (yyval.Char) = '\301'; }
    break;

  case 377:
#line 450 "lscp.y"
    { (yyval.Char) = '\302'; }
    break;

  case 378:
#line 450 "lscp.y"
    { (yyval.Char) = '\303'; }
    break;

  case 379:
#line 450 "lscp.y"
    { (yyval.Char) = '\304'; }
    break;

  case 380:
#line 451 "lscp.y"
    { (yyval.Char) = '\305'; }
    break;

  case 381:
#line 451 "lscp.y"
    { (yyval.Char) = '\306'; }
    break;

  case 382:
#line 451 "lscp.y"
    { (yyval.Char) = '\307'; }
    break;

  case 383:
#line 452 "lscp.y"
    { (yyval.Char) = '\310'; }
    break;

  case 384:
#line 452 "lscp.y"
    { (yyval.Char) = '\311'; }
    break;

  case 385:
#line 452 "lscp.y"
    { (yyval.Char) = '\312'; }
    break;

  case 386:
#line 453 "lscp.y"
    { (yyval.Char) = '\313'; }
    break;

  case 387:
#line 453 "lscp.y"
    { (yyval.Char) = '\314'; }
    break;

  case 388:
#line 453 "lscp.y"
    { (yyval.Char) = '\315'; }
    break;

  case 389:
#line 454 "lscp.y"
    { (yyval.Char) = '\316'; }
    break;

  case 390:
#line 454 "lscp.y"
    { (yyval.Char) = '\317'; }
    break;

  case 391:
#line 454 "lscp.y"
    { (yyval.Char) = '\320'; }
    break;

  case 392:
#line 455 "lscp.y"
    { (yyval.Char) = '\321'; }
    break;

  case 393:
#line 455 "lscp.y"
    { (yyval.Char) = '\322'; }
    break;

  case 394:
#line 455 "lscp.y"
    { (yyval.Char) = '\323'; }
    break;

  case 395:
#line 456 "lscp.y"
    { (yyval.Char) = '\324'; }
    break;

  case 396:
#line 456 "lscp.y"
    { (yyval.Char) = '\325'; }
    break;

  case 397:
#line 456 "lscp.y"
    { (yyval.Char) = '\326'; }
    break;

  case 398:
#line 457 "lscp.y"
    { (yyval.Char) = '\327'; }
    break;

  case 399:
#line 457 "lscp.y"
    { (yyval.Char) = '\330'; }
    break;

  case 400:
#line 457 "lscp.y"
    { (yyval.Char) = '\331'; }
    break;

  case 401:
#line 458 "lscp.y"
    { (yyval.Char) = '\332'; }
    break;

  case 402:
#line 458 "lscp.y"
    { (yyval.Char) = '\333'; }
    break;

  case 403:
#line 458 "lscp.y"
    { (yyval.Char) = '\334'; }
    break;

  case 404:
#line 459 "lscp.y"
    { (yyval.Char) = '\335'; }
    break;

  case 405:
#line 459 "lscp.y"
    { (yyval.Char) = '\336'; }
    break;

  case 406:
#line 459 "lscp.y"
    { (yyval.Char) = '\337'; }
    break;

  case 407:
#line 460 "lscp.y"
    { (yyval.Char) = '\340'; }
    break;

  case 408:
#line 460 "lscp.y"
    { (yyval.Char) = '\341'; }
    break;

  case 409:
#line 460 "lscp.y"
    { (yyval.Char) = '\342'; }
    break;

  case 410:
#line 461 "lscp.y"
    { (yyval.Char) = '\343'; }
    break;

  case 411:
#line 461 "lscp.y"
    { (yyval.Char) = '\344'; }
    break;

  case 412:
#line 461 "lscp.y"
    { (yyval.Char) = '\345'; }
    break;

  case 413:
#line 462 "lscp.y"
    { (yyval.Char) = '\346'; }
    break;

  case 414:
#line 462 "lscp.y"
    { (yyval.Char) = '\347'; }
    break;

  case 415:
#line 462 "lscp.y"
    { (yyval.Char) = '\350'; }
    break;

  case 416:
#line 463 "lscp.y"
    { (yyval.Char) = '\351'; }
    break;

  case 417:
#line 463 "lscp.y"
    { (yyval.Char) = '\352'; }
    break;

  case 418:
#line 463 "lscp.y"
    { (yyval.Char) = '\353'; }
    break;

  case 419:
#line 464 "lscp.y"
    { (yyval.Char) = '\354'; }
    break;

  case 420:
#line 464 "lscp.y"
    { (yyval.Char) = '\355'; }
    break;

  case 421:
#line 464 "lscp.y"
    { (yyval.Char) = '\356'; }
    break;

  case 422:
#line 465 "lscp.y"
    { (yyval.Char) = '\357'; }
    break;

  case 423:
#line 465 "lscp.y"
    { (yyval.Char) = '\360'; }
    break;

  case 424:
#line 465 "lscp.y"
    { (yyval.Char) = '\361'; }
    break;

  case 425:
#line 466 "lscp.y"
    { (yyval.Char) = '\362'; }
    break;

  case 426:
#line 466 "lscp.y"
    { (yyval.Char) = '\363'; }
    break;

  case 427:
#line 466 "lscp.y"
    { (yyval.Char) = '\364'; }
    break;

  case 428:
#line 467 "lscp.y"
    { (yyval.Char) = '\365'; }
    break;

  case 429:
#line 467 "lscp.y"
    { (yyval.Char) = '\366'; }
    break;

  case 430:
#line 467 "lscp.y"
    { (yyval.Char) = '\367'; }
    break;

  case 431:
#line 468 "lscp.y"
    { (yyval.Char) = '\370'; }
    break;

  case 432:
#line 468 "lscp.y"
    { (yyval.Char) = '\371'; }
    break;

  case 433:
#line 468 "lscp.y"
    { (yyval.Char) = '\372'; }
    break;

  case 434:
#line 469 "lscp.y"
    { (yyval.Char) = '\373'; }
    break;

  case 435:
#line 469 "lscp.y"
    { (yyval.Char) = '\374'; }
    break;

  case 436:
#line 469 "lscp.y"
    { (yyval.Char) = '\375'; }
    break;

  case 437:
#line 470 "lscp.y"
    { (yyval.Char) = '\376'; }
    break;

  case 438:
#line 470 "lscp.y"
    { (yyval.Char) = '\377'; }
    break;

  case 439:
#line 473 "lscp.y"
    { (yyval.String) = " ";      }
    break;

  case 441:
#line 475 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + " "; }
    break;

  case 442:
#line 476 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + (yyvsp[(2) - (2)].String);  }
    break;

  case 443:
#line 479 "lscp.y"
    { (yyval.String) = (yyvsp[(2) - (3)].String); }
    break;

  case 444:
#line 480 "lscp.y"
    { (yyval.String) = (yyvsp[(2) - (3)].String); }
    break;


/* Line 1267 of yacc.c.  */
#line 5413 "y.tab.c"
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 738 "lscp.y"


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

