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
#define YYFINAL  52
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   5505

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  227
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  168
/* YYNRULES -- Number of rules.  */
#define YYNRULES  611
/* YYNRULES -- Number of states.  */
#define YYNSTATES  2074

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
      59,    63,    67,    71,    75,    79,    83,    87,    91,    95,
      99,   101,   103,   105,   109,   119,   127,   135,   145,   151,
     159,   161,   165,   167,   169,   171,   173,   175,   177,   179,
     181,   183,   185,   187,   189,   191,   193,   195,   197,   199,
     201,   203,   205,   207,   209,   211,   213,   215,   217,   219,
     221,   223,   225,   227,   229,   231,   233,   235,   237,   239,
     241,   243,   245,   247,   249,   251,   253,   255,   257,   274,
     293,   312,   333,   341,   345,   349,   353,   359,   363,   367,
     369,   371,   377,   385,   395,   397,   403,   411,   421,   423,
     425,   431,   437,   445,   455,   463,   473,   475,   481,   489,
     495,   501,   507,   511,   513,   515,   519,   523,   533,   535,
     541,   545,   553,   559,   563,   569,   575,   579,   585,   591,
     593,   601,   611,   619,   629,   633,   641,   651,   663,   673,
     683,   691,   699,   707,   715,   719,   723,   729,   733,   739,
     743,   749,   757,   761,   765,   769,   777,   783,   791,   797,
     803,   809,   815,   821,   825,   829,   835,   839,   843,   849,
     857,   863,   873,   879,   885,   891,   897,   903,   909,   915,
     921,   927,   933,   934,   937,   941,   947,   949,   951,   953,
     955,   957,   959,   961,   963,   967,   971,   973,   977,   983,
     987,   993,   997,  1003,  1011,  1015,  1017,  1019,  1021,  1023,
    1025,  1027,  1029,  1031,  1033,  1035,  1037,  1039,  1041,  1043,
    1045,  1047,  1049,  1051,  1053,  1055,  1057,  1059,  1061,  1063,
    1065,  1067,  1069,  1073,  1075,  1077,  1079,  1081,  1085,  1091,
    1093,  1095,  1097,  1099,  1101,  1103,  1105,  1107,  1110,  1114,
    1119,  1124,  1126,  1129,  1131,  1133,  1135,  1137,  1139,  1141,
    1143,  1145,  1147,  1149,  1151,  1154,  1157,  1160,  1163,  1166,
    1169,  1172,  1175,  1178,  1180,  1182,  1184,  1186,  1188,  1190,
    1192,  1194,  1196,  1198,  1200,  1202,  1204,  1206,  1208,  1210,
    1212,  1214,  1216,  1218,  1220,  1222,  1224,  1226,  1228,  1230,
    1232,  1234,  1236,  1238,  1240,  1242,  1244,  1246,  1248,  1250,
    1252,  1254,  1256,  1258,  1260,  1262,  1264,  1266,  1268,  1270,
    1272,  1274,  1276,  1278,  1280,  1282,  1284,  1286,  1288,  1290,
    1292,  1294,  1296,  1298,  1300,  1302,  1304,  1306,  1308,  1310,
    1312,  1314,  1316,  1318,  1320,  1322,  1324,  1326,  1328,  1330,
    1332,  1334,  1336,  1338,  1340,  1342,  1344,  1346,  1348,  1350,
    1352,  1354,  1356,  1358,  1360,  1362,  1364,  1366,  1368,  1370,
    1372,  1374,  1376,  1378,  1380,  1382,  1384,  1386,  1388,  1390,
    1392,  1394,  1396,  1398,  1400,  1402,  1404,  1406,  1408,  1410,
    1412,  1414,  1416,  1418,  1420,  1422,  1424,  1426,  1428,  1430,
    1432,  1434,  1436,  1438,  1440,  1442,  1444,  1446,  1448,  1450,
    1452,  1454,  1456,  1458,  1460,  1462,  1464,  1466,  1468,  1470,
    1472,  1474,  1476,  1478,  1480,  1482,  1484,  1486,  1488,  1490,
    1492,  1494,  1496,  1498,  1500,  1502,  1504,  1506,  1508,  1510,
    1512,  1514,  1516,  1518,  1520,  1522,  1524,  1526,  1528,  1530,
    1532,  1534,  1536,  1538,  1540,  1542,  1544,  1546,  1548,  1550,
    1552,  1554,  1556,  1558,  1560,  1562,  1564,  1566,  1568,  1570,
    1572,  1574,  1576,  1578,  1580,  1582,  1584,  1586,  1588,  1590,
    1592,  1594,  1596,  1598,  1600,  1602,  1604,  1606,  1608,  1610,
    1612,  1614,  1616,  1618,  1620,  1623,  1626,  1630,  1634,  1636,
    1638,  1640,  1644,  1648,  1652,  1658,  1664,  1669,  1674,  1679,
    1686,  1694,  1699,  1704,  1708,  1713,  1721,  1731,  1738,  1742,
    1752,  1764,  1772,  1790,  1821,  1830,  1835,  1861,  1886,  1910,
    1933,  1959,  1984,  2006,  2027,  2057,  2086,  2106,  2125,  2149,
    2163,  2176,  2190,  2203,  2215,  2228,  2240,  2258,  2280,  2292,
    2303,  2310,  2320,  2335,  2346,  2376,  2397,  2417,  2447,  2467,
    2498,  2519,  2537,  2566,  2594,  2620,  2639,  2657,  2685,  2701,
    2718,  2738,  2759,  2777,  2793,  2812,  2828,  2839,  2855,  2863,
    2872,  2896,  2922,  2937,  2951,  2970,  2982,  2988,  2993,  3003,
    3017,  3024,  3031,  3037,  3042,  3047,  3053,  3064,  3070,  3084,
    3089,  3094
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     228,     0,    -1,   229,   292,    -1,   229,   293,   292,    -1,
      -1,   230,    -1,   231,    -1,     1,    -1,     3,    -1,   230,
       3,    -1,   230,   291,    -1,   230,   287,    -1,   230,   283,
      -1,   294,   291,   232,    -1,   296,   291,   235,    -1,   297,
     291,   236,    -1,   295,   291,   238,    -1,   302,   291,   240,
      -1,   303,   291,   246,    -1,   304,   291,   252,    -1,   305,
     291,   247,    -1,   310,   291,   237,    -1,   311,   291,   239,
      -1,   312,   291,   233,    -1,   313,   291,   234,    -1,   390,
     291,   241,    -1,   298,   291,   242,    -1,   299,   291,   243,
      -1,   300,   291,   244,    -1,   301,   291,   245,    -1,   390,
      -1,   394,    -1,   314,    -1,   373,   291,   271,    -1,   375,
     291,   309,   291,   281,   291,   271,   291,   271,    -1,   375,
     291,   281,   291,   271,   291,   271,    -1,   375,   291,   309,
     291,   271,   291,   271,    -1,   375,   291,   309,   291,   271,
     291,   271,   291,   268,    -1,   375,   291,   271,   291,   271,
      -1,   375,   291,   271,   291,   271,   291,   268,    -1,   363,
      -1,   363,   291,   274,    -1,   319,    -1,   320,    -1,   321,
      -1,   322,    -1,   332,    -1,   338,    -1,   337,    -1,   336,
      -1,   333,    -1,   334,    -1,   335,    -1,   323,    -1,   324,
      -1,   325,    -1,   326,    -1,   327,    -1,   328,    -1,   329,
      -1,   330,    -1,   331,    -1,   391,    -1,   339,    -1,   341,
      -1,   319,    -1,   320,    -1,   321,    -1,   322,    -1,   332,
      -1,   338,    -1,   337,    -1,   336,    -1,   333,    -1,   334,
      -1,   335,    -1,   323,    -1,   324,    -1,   325,    -1,   326,
      -1,   327,    -1,   328,    -1,   329,    -1,   330,    -1,   331,
      -1,   391,    -1,   339,    -1,   341,    -1,   361,   291,   249,
     262,   291,   263,   291,   264,   291,   270,   291,   273,   291,
     268,   291,   266,    -1,   361,   291,   249,   262,   291,   263,
     291,   264,   291,   270,   291,   273,   291,   268,   291,   266,
     291,   255,    -1,   361,   291,   249,   262,   291,   263,   291,
     264,   291,   270,   291,   273,   291,   268,   291,   266,   291,
     275,    -1,   361,   291,   249,   262,   291,   263,   291,   264,
     291,   270,   291,   273,   291,   268,   291,   266,   291,   255,
     291,   275,    -1,   361,   291,   262,   291,   263,   291,   264,
      -1,   314,   291,   267,    -1,   363,   291,   262,    -1,   363,
     291,   306,    -1,   373,   291,   379,   291,   271,    -1,   373,
     291,   271,    -1,   376,   291,   271,    -1,   315,    -1,   355,
      -1,   365,   291,   318,   291,   283,    -1,   360,   291,   318,
     291,   283,   291,   283,    -1,   360,   291,   318,   291,   283,
     291,   283,   291,   250,    -1,   316,    -1,   351,   291,   318,
     291,   283,    -1,   350,   291,   318,   291,   283,   291,   283,
      -1,   350,   291,   318,   291,   283,   291,   283,   291,   250,
      -1,   348,    -1,   358,    -1,   349,   291,   318,   291,   287,
      -1,   359,   291,   318,   291,   287,    -1,   366,   291,   318,
     291,   287,   291,   287,    -1,   357,   291,   318,   291,   287,
     291,   287,   291,   283,    -1,   353,   291,   318,   291,   287,
     291,   287,    -1,   352,   291,   318,   291,   287,   291,   287,
     291,   283,    -1,   317,    -1,   314,   291,   318,   291,   267,
      -1,   314,   291,   336,   291,   251,   291,   267,    -1,   314,
     291,   337,   291,   267,    -1,   314,   291,   338,   291,   267,
      -1,   343,   291,   318,   291,   270,    -1,   383,   291,   318,
      -1,   339,    -1,   340,    -1,   362,   291,   262,    -1,   362,
     291,   306,    -1,   361,   291,   318,   291,   262,   291,   263,
     291,   264,    -1,   364,    -1,   363,   291,   318,   291,   262,
      -1,   372,   291,   267,    -1,   371,   291,   318,   291,   267,
     291,   269,    -1,   374,   291,   381,   291,   271,    -1,   374,
     291,   271,    -1,   373,   291,   318,   291,   271,    -1,   375,
     291,   381,   291,   271,    -1,   375,   291,   271,    -1,   376,
     291,   318,   291,   271,    -1,   377,   291,   318,   291,   287,
      -1,   384,    -1,   347,   291,   287,   291,   283,     4,   277,
      -1,   352,   291,   287,   291,   287,   291,   283,     4,   277,
      -1,   356,   291,   287,   291,   283,     4,   277,    -1,   357,
     291,   287,   291,   287,   291,   283,     4,   277,    -1,   314,
     291,   248,    -1,   363,   291,   392,   291,   262,   291,   274,
      -1,   371,   291,   392,   291,   267,   291,   269,   291,   276,
      -1,   371,   291,   353,   291,   267,   291,   269,   291,   257,
     291,   257,    -1,   371,   291,   370,   291,   267,   291,   269,
     291,   265,    -1,   371,   291,   385,   291,   267,   291,   269,
     291,   266,    -1,   373,   291,   392,   291,   271,   291,   272,
      -1,   373,   291,   378,   291,   271,   291,   290,    -1,   376,
     291,   392,   291,   271,   291,   272,    -1,   376,   291,   378,
     291,   271,   291,   290,    -1,   393,   291,   282,    -1,   384,
     291,   266,    -1,   349,   291,   283,   291,   250,    -1,   349,
     291,   283,    -1,   359,   291,   283,   291,   250,    -1,   359,
     291,   283,    -1,   371,   291,   267,   291,   265,    -1,   371,
     291,   267,   291,   265,   291,   276,    -1,   314,   291,   267,
      -1,   362,   291,   262,    -1,   362,   291,   306,    -1,   375,
     291,   382,   291,   271,   291,   279,    -1,   375,   291,   271,
     291,   279,    -1,   374,   291,   382,   291,   271,   291,   279,
      -1,   374,   291,   271,   291,   279,    -1,   373,   291,   271,
     291,   271,    -1,   376,   291,   271,   291,   271,    -1,   373,
     291,   271,   291,   271,    -1,   376,   291,   271,   291,   271,
      -1,   349,   291,   287,    -1,   359,   291,   287,    -1,   371,
     291,   267,   291,   269,    -1,   342,   291,   253,    -1,   343,
     291,   254,    -1,   349,   291,   267,   291,   256,    -1,   353,
     291,   267,   291,   257,   291,   257,    -1,   354,   291,   267,
     291,   258,    -1,   369,   291,   267,   291,   256,   291,   259,
     291,   260,    -1,   359,   291,   267,   291,   256,    -1,   366,
     291,   267,   291,   259,    -1,   367,   291,   267,   291,   260,
      -1,   368,   291,   267,   291,   261,    -1,   384,   291,   267,
     291,   266,    -1,   386,   291,   267,   291,   282,    -1,   387,
     291,   267,   291,   282,    -1,   363,   291,   267,   291,   262,
      -1,   363,   291,   267,   291,   307,    -1,   363,   291,   267,
     291,   308,    -1,    -1,   309,   291,    -1,   283,     4,   277,
      -1,   250,   291,   283,     4,   277,    -1,   388,    -1,   389,
      -1,   348,    -1,   358,    -1,   317,    -1,   315,    -1,   355,
      -1,   316,    -1,   362,   291,   262,    -1,   362,   291,   306,
      -1,   364,    -1,   372,   291,   267,    -1,   374,   291,   381,
     291,   271,    -1,   374,   291,   271,    -1,   375,   291,   381,
     291,   271,    -1,   375,   291,   271,    -1,   273,   291,   268,
     291,   267,    -1,   309,   291,   273,   291,   268,   291,   267,
      -1,   270,   291,   267,    -1,   344,    -1,   345,    -1,   346,
      -1,   287,    -1,   287,    -1,   283,    -1,   287,    -1,   287,
      -1,   306,    -1,   283,    -1,   287,    -1,   287,    -1,   287,
      -1,   287,    -1,   284,    -1,   287,    -1,   287,    -1,   287,
      -1,   287,    -1,   283,    -1,   290,    -1,   290,    -1,   290,
      -1,   290,    -1,   290,    -1,   290,    -1,   278,    -1,   277,
       5,   278,    -1,   283,    -1,   290,    -1,   287,    -1,   284,
      -1,   283,     4,   280,    -1,   279,   291,   283,     4,   280,
      -1,   283,    -1,   290,    -1,   381,    -1,   382,    -1,   380,
      -1,   287,    -1,   283,    -1,   288,    -1,   283,   288,    -1,
     285,     6,   285,    -1,     7,   285,     6,   285,    -1,     8,
     285,     6,   285,    -1,   286,    -1,   285,   286,    -1,     9,
      -1,    10,    -1,    11,    -1,    12,    -1,    13,    -1,    14,
      -1,    15,    -1,    16,    -1,    17,    -1,    18,    -1,   286,
      -1,    10,   285,    -1,    11,   285,    -1,    12,   285,    -1,
      13,   285,    -1,    14,   285,    -1,    15,   285,    -1,    16,
     285,    -1,    17,   285,    -1,    18,   285,    -1,    19,    -1,
      20,    -1,    21,    -1,    22,    -1,    23,    -1,    24,    -1,
      25,    -1,    26,    -1,    27,    -1,    28,    -1,    29,    -1,
      30,    -1,    31,    -1,    32,    -1,    33,    -1,    34,    -1,
      35,    -1,    36,    -1,    37,    -1,    38,    -1,    39,    -1,
      40,    -1,    41,    -1,    42,    -1,    43,    -1,    44,    -1,
      45,    -1,    46,    -1,    47,    -1,    48,    -1,    49,    -1,
      50,    -1,    51,    -1,    52,    -1,    53,    -1,    54,    -1,
      55,    -1,    56,    -1,    57,    -1,    58,    -1,    59,    -1,
      60,    -1,    61,    -1,    62,    -1,    63,    -1,    64,    -1,
      65,    -1,    66,    -1,    67,    -1,    68,    -1,    69,    -1,
      70,    -1,     9,    -1,    10,    -1,    11,    -1,    12,    -1,
      13,    -1,    14,    -1,    15,    -1,    16,    -1,    17,    -1,
      18,    -1,    71,    -1,     3,    -1,    72,    -1,    73,    -1,
      74,    -1,    75,    -1,    76,    -1,    77,    -1,     7,    -1,
       8,    -1,     6,    -1,     5,    -1,    78,    -1,    79,    -1,
      80,    -1,    81,    -1,     4,    -1,    82,    -1,    83,    -1,
      84,    -1,    85,    -1,    86,    -1,    87,    -1,    88,    -1,
      89,    -1,    90,    -1,    91,    -1,    92,    -1,    93,    -1,
      94,    -1,    95,    -1,    96,    -1,    97,    -1,    98,    -1,
      99,    -1,   100,    -1,   101,    -1,   102,    -1,   103,    -1,
     104,    -1,   105,    -1,   106,    -1,   107,    -1,   108,    -1,
     109,    -1,   110,    -1,   111,    -1,   112,    -1,   113,    -1,
     114,    -1,   115,    -1,   116,    -1,   117,    -1,   118,    -1,
     119,    -1,   120,    -1,   121,    -1,   122,    -1,   123,    -1,
     124,    -1,   125,    -1,   126,    -1,   127,    -1,   128,    -1,
     129,    -1,   130,    -1,   131,    -1,   132,    -1,   133,    -1,
     134,    -1,   135,    -1,   136,    -1,   137,    -1,   138,    -1,
     139,    -1,   140,    -1,   141,    -1,   142,    -1,   143,    -1,
     144,    -1,   145,    -1,   146,    -1,   147,    -1,   148,    -1,
     149,    -1,   150,    -1,   151,    -1,   152,    -1,   153,    -1,
     154,    -1,   155,    -1,   156,    -1,   157,    -1,   158,    -1,
     159,    -1,   160,    -1,   161,    -1,   162,    -1,   163,    -1,
     164,    -1,   165,    -1,   166,    -1,   167,    -1,   168,    -1,
     169,    -1,   170,    -1,   171,    -1,   172,    -1,   173,    -1,
     174,    -1,   175,    -1,   176,    -1,   177,    -1,   178,    -1,
     179,    -1,   180,    -1,   181,    -1,   182,    -1,   183,    -1,
     184,    -1,   185,    -1,   186,    -1,   187,    -1,   188,    -1,
     189,    -1,   190,    -1,   191,    -1,   192,    -1,   193,    -1,
     194,    -1,   195,    -1,   196,    -1,   197,    -1,   198,    -1,
     199,    -1,   200,    -1,   201,    -1,   202,    -1,   203,    -1,
     204,    -1,   205,    -1,   206,    -1,   207,    -1,   208,    -1,
     209,    -1,   210,    -1,   211,    -1,   212,    -1,   213,    -1,
     214,    -1,   215,    -1,   216,    -1,   217,    -1,   218,    -1,
     219,    -1,   220,    -1,   221,    -1,   291,    -1,   283,    -1,
     289,   291,    -1,   289,   283,    -1,   222,   289,   222,    -1,
     223,   289,   223,    -1,   224,    -1,   225,    -1,   226,    -1,
      19,    22,    22,    -1,    25,    23,    38,    -1,    31,    19,
      34,    -1,    39,    32,    31,    19,    34,    -1,    21,    30,
      23,    19,    36,    -1,    24,    27,    32,    22,    -1,    31,
      33,    40,    23,    -1,    21,    33,    34,    43,    -1,    21,
      36,    23,    19,    38,    23,    -1,    22,    23,    37,    38,
      36,    33,    43,    -1,    30,    27,    37,    38,    -1,    30,
      33,    19,    22,    -1,    19,    30,    30,    -1,    32,    33,
      32,    23,    -1,    22,    23,    24,    19,    39,    30,    38,
      -1,    32,    33,    32,    89,    31,    33,    22,    19,    30,
      -1,    36,    23,    31,    33,    40,    23,    -1,    37,    23,
      38,    -1,    37,    39,    20,    37,    21,    36,    27,    20,
      23,    -1,    39,    32,    37,    39,    20,    37,    21,    36,
      27,    20,    23,    -1,    21,    26,    19,    32,    32,    23,
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
      38,    89,    27,    32,    24,    33,    -1,    22,    20,    89,
      27,    32,    37,    38,    36,    39,    31,    23,    32,    38,
      89,    22,    27,    36,    23,    21,    38,    33,    36,    43,
      89,    21,    33,    39,    32,    38,    -1,    22,    20,    89,
      27,    32,    37,    38,    36,    39,    31,    23,    32,    38,
      89,    22,    27,    36,    23,    21,    38,    33,    36,    43,
      89,    27,    32,    24,    33,    -1,    22,    20,    89,    27,
      32,    37,    38,    36,    39,    31,    23,    32,    38,    89,
      21,    33,    39,    32,    38,    -1,    22,    20,    89,    27,
      32,    37,    38,    36,    39,    31,    23,    32,    38,    89,
      27,    32,    24,    33,    -1,    22,    20,    89,    27,    32,
      37,    38,    36,    39,    31,    23,    32,    38,    37,    89,
      28,    33,    20,    89,    27,    32,    24,    33,    -1,    21,
      26,    19,    32,    32,    23,    30,    89,    21,    33,    39,
      32,    38,    -1,    21,    26,    19,    32,    32,    23,    30,
      89,    27,    32,    24,    33,    -1,    24,    42,    89,    37,
      23,    32,    22,    89,    21,    33,    39,    32,    38,    -1,
      24,    42,    89,    37,    23,    32,    22,    89,    27,    32,
      24,    33,    -1,    20,    39,    24,    24,    23,    36,    89,
      24,    27,    30,    30,    -1,    37,    38,    36,    23,    19,
      31,    89,    21,    33,    39,    32,    38,    -1,    40,    33,
      27,    21,    23,    89,    21,    33,    39,    32,    38,    -1,
      38,    33,    38,    19,    30,    89,    40,    33,    27,    21,
      23,    89,    21,    33,    39,    32,    38,    -1,    38,    33,
      38,    19,    30,    89,    40,    33,    27,    21,    23,    89,
      21,    33,    39,    32,    38,    89,    31,    19,    42,    -1,
      25,    30,    33,    20,    19,    30,    89,    27,    32,    24,
      33,    -1,    27,    32,    37,    38,    36,    39,    31,    23,
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
      22,    27,    89,    27,    32,    37,    38,    36,    39,    31,
      23,    32,    38,    89,    31,    19,    34,    -1,    31,    27,
      22,    27,    89,    27,    32,    37,    38,    36,    39,    31,
      23,    32,    38,    89,    31,    19,    34,    37,    -1,    31,
      27,    22,    27,    89,    27,    32,    34,    39,    38,    89,
      22,    36,    27,    40,    23,    36,    -1,    31,    27,    22,
      27,    89,    27,    32,    34,    39,    38,    89,    34,    33,
      36,    38,    -1,    31,    27,    22,    27,    89,    27,    32,
      34,    39,    38,    89,    21,    26,    19,    32,    32,    23,
      30,    -1,    31,    27,    22,    27,    89,    27,    32,    34,
      39,    38,    89,    38,    43,    34,    23,    -1,    31,    27,
      22,    27,    89,    27,    32,    34,    39,    38,    -1,    31,
      27,    22,    27,    89,    21,    33,    32,    38,    36,    33,
      30,    30,    23,    36,    -1,    24,    42,    89,    37,    23,
      32,    22,    -1,    24,    42,    89,    37,    23,    32,    22,
      37,    -1,    22,    20,    89,    27,    32,    37,    38,    36,
      39,    31,    23,    32,    38,    89,    22,    27,    36,    23,
      21,    38,    33,    36,    43,    -1,    22,    20,    89,    27,
      32,    37,    38,    36,    39,    31,    23,    32,    38,    89,
      22,    27,    36,    23,    21,    38,    33,    36,    27,    23,
      37,    -1,    22,    20,    89,    27,    32,    37,    38,    36,
      39,    31,    23,    32,    38,    37,    -1,    22,    20,    89,
      27,    32,    37,    38,    36,    39,    31,    23,    32,    38,
      -1,    22,    20,    89,    27,    32,    37,    38,    36,    39,
      31,    23,    32,    38,    37,    89,    28,    33,    20,    -1,
      22,    23,    37,    21,    36,    27,    34,    38,    27,    33,
      32,    -1,    24,    33,    36,    21,    23,    -1,    24,    30,
      19,    38,    -1,    36,    23,    21,    39,    36,    37,    27,
      40,    23,    -1,    32,    33,    32,    89,    36,    23,    21,
      39,    36,    37,    27,    40,    23,    -1,    37,    23,    36,
      40,    23,    36,    -1,    40,    33,    30,    39,    31,    23,
      -1,    30,    23,    40,    23,    30,    -1,    31,    39,    38,
      23,    -1,    37,    33,    30,    33,    -1,    20,    43,    38,
      23,    37,    -1,    34,    23,    36,    21,    23,    32,    38,
      19,    25,    23,    -1,    36,    23,    37,    23,    38,    -1,
      31,    27,    37,    21,    23,    30,    30,    19,    32,    23,
      33,    39,    37,    -1,    32,    19,    31,    23,    -1,    23,
      21,    26,    33,    -1,    35,    39,    27,    38,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    97,    97,    98,   101,   102,   103,   104,   107,   108,
     109,   110,   111,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   197,   198,
     199,   200,   203,   206,   207,   208,   209,   210,   211,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   275,   276,   277,   278,
     279,   280,   283,   286,   287,   290,   291,   292,   293,   296,
     297,   300,   301,   304,   305,   306,   309,   310,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   329,   330,   333,   334,   337,   338,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
     353,   354,   357,   358,   361,   364,   365,   366,   369,   372,
     375,   378,   381,   382,   385,   388,   391,   394,   397,   400,
     401,   404,   407,   410,   413,   416,   419,   422,   425,   428,
     431,   434,   435,   438,   439,   440,   441,   444,   445,   448,
     449,   452,   453,   454,   462,   463,   466,   467,   470,   471,
     472,   476,   477,   480,   481,   482,   483,   484,   485,   486,
     487,   488,   489,   492,   493,   494,   495,   496,   497,   498,
     499,   500,   501,   503,   503,   503,   503,   503,   503,   503,
     503,   503,   503,   503,   503,   503,   503,   503,   503,   503,
     503,   503,   503,   503,   503,   503,   503,   503,   503,   504,
     504,   504,   504,   504,   504,   504,   504,   504,   504,   504,
     504,   504,   504,   504,   504,   504,   504,   504,   504,   504,
     504,   504,   504,   504,   504,   505,   505,   505,   505,   505,
     505,   505,   505,   505,   505,   506,   506,   506,   506,   506,
     506,   506,   506,   506,   506,   506,   506,   506,   507,   507,
     507,   507,   507,   507,   507,   508,   508,   508,   508,   508,
     509,   509,   509,   509,   510,   510,   510,   511,   511,   511,
     512,   512,   512,   513,   513,   513,   514,   514,   514,   515,
     515,   515,   516,   516,   516,   517,   517,   517,   518,   518,
     518,   519,   519,   519,   520,   520,   520,   521,   521,   521,
     522,   522,   522,   523,   523,   523,   524,   524,   524,   525,
     525,   525,   526,   526,   526,   527,   527,   527,   528,   528,
     528,   529,   529,   529,   530,   530,   530,   531,   531,   531,
     532,   532,   532,   533,   533,   533,   534,   534,   534,   535,
     535,   535,   536,   536,   536,   537,   537,   537,   538,   538,
     538,   539,   539,   539,   540,   540,   540,   541,   541,   541,
     542,   542,   542,   543,   543,   543,   544,   544,   544,   545,
     545,   545,   546,   546,   546,   547,   547,   547,   548,   548,
     548,   549,   549,   549,   550,   550,   550,   551,   551,   551,
     552,   552,   555,   556,   557,   558,   561,   562,   568,   571,
     574,   577,   580,   583,   586,   589,   592,   595,   598,   601,
     604,   607,   610,   613,   616,   619,   622,   625,   628,   631,
     634,   637,   640,   643,   646,   649,   652,   655,   658,   661,
     664,   667,   670,   673,   676,   679,   682,   685,   688,   691,
     694,   697,   700,   703,   706,   709,   712,   715,   718,   721,
     724,   727,   730,   733,   736,   739,   742,   745,   748,   751,
     754,   757,   760,   763,   766,   769,   772,   775,   778,   781,
     784,   787,   790,   793,   796,   799,   802,   805,   808,   811,
     814,   817,   820,   823,   826,   829,   832,   835,   838,   841,
     844,   847,   850,   853,   856,   859,   862,   865,   868,   871,
     874,   877
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
  "reset_instruction", "clear_instruction", "find_instruction",
  "move_instruction", "copy_instruction", "destroy_instruction",
  "load_instruction", "set_chan_instruction", "modal_arg", "key_val_list",
  "buffer_size_type", "list_instruction", "load_instr_args",
  "load_engine_args", "instr_load_mode", "device_index",
  "audio_channel_index", "audio_output_type_name", "midi_input_port_index",
  "midi_input_channel_index", "midi_input_type_name", "midi_map",
  "midi_bank", "midi_prog", "midi_ctrl", "volume_value", "sampler_channel",
  "instrument_index", "fx_send_id", "engine_name", "pathname", "dirname",
  "filename", "map_name", "entry_name", "fx_send_name", "param_val_list",
  "param_val", "query_val_list", "query_val", "scan_mode", "boolean",
  "string", "dotnum", "digits", "digit", "number", "char", "text",
  "stringval", "SP", "LF", "CR", "ADD", "GET", "MAP", "UNMAP", "CLEAR",
  "FIND", "MOVE", "COPY", "CREATE", "DESTROY", "LIST", "LOAD", "ALL",
  "NONE", "DEFAULT", "NON_MODAL", "REMOVE", "SET", "SUBSCRIBE",
  "UNSUBSCRIBE", "CHANNEL", "AVAILABLE_ENGINES",
  "AVAILABLE_AUDIO_OUTPUT_DRIVERS", "CHANNELS", "INFO",
  "AUDIO_OUTPUT_DEVICE_COUNT", "AUDIO_OUTPUT_DEVICE_INFO",
  "MIDI_INPUT_DEVICE_COUNT", "MIDI_INPUT_DEVICE_INFO",
  "MIDI_INSTRUMENT_MAP_COUNT", "MIDI_INSTRUMENT_MAP_INFO",
  "MIDI_INSTRUMENT_COUNT", "MIDI_INSTRUMENT_INFO",
  "DB_INSTRUMENT_DIRECTORY_COUNT", "DB_INSTRUMENT_DIRECTORY_INFO",
  "DB_INSTRUMENT_COUNT", "DB_INSTRUMENT_INFO", "DB_INSTRUMENTS_JOB_INFO",
  "CHANNEL_COUNT", "CHANNEL_INFO", "FX_SEND_COUNT", "FX_SEND_INFO",
  "BUFFER_FILL", "STREAM_COUNT", "VOICE_COUNT", "TOTAL_VOICE_COUNT",
  "TOTAL_VOICE_COUNT_MAX", "GLOBAL_INFO", "INSTRUMENT", "ENGINE",
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
  "MIDI_CONTROLLER", "FX_SEND", "FX_SENDS", "DB_INSTRUMENT_DIRECTORY",
  "DB_INSTRUMENT_DIRECTORIES", "DB_INSTRUMENTS", "DB_INSTRUMENT",
  "DB_INSTRUMENTS_JOB", "DESCRIPTION", "FORCE", "FLAT", "RECURSIVE",
  "NON_RECURSIVE", "SERVER", "VOLUME", "LEVEL", "MUTE", "SOLO", "BYTES",
  "PERCENTAGE", "RESET", "MISCELLANEOUS", "NAME", "ECHO", "QUIT", 0
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
     231,   231,   232,   232,   232,   232,   232,   232,   232,   232,
     232,   232,   233,   233,   233,   233,   233,   233,   233,   233,
     233,   233,   233,   233,   233,   233,   233,   233,   233,   233,
     233,   233,   233,   233,   233,   234,   234,   234,   234,   234,
     234,   234,   234,   234,   234,   234,   234,   234,   234,   234,
     234,   234,   234,   234,   234,   234,   234,   234,   235,   235,
     235,   235,   236,   237,   237,   237,   237,   237,   237,   238,
     238,   238,   238,   238,   238,   238,   238,   238,   238,   238,
     238,   238,   238,   238,   238,   238,   238,   238,   238,   238,
     238,   238,   238,   238,   238,   238,   238,   238,   238,   238,
     238,   238,   238,   238,   238,   238,   238,   238,   238,   238,
     239,   239,   239,   239,   239,   239,   239,   239,   239,   239,
     239,   239,   239,   239,   239,   239,   240,   240,   240,   240,
     240,   240,   241,   242,   242,   243,   243,   243,   243,   244,
     244,   245,   245,   246,   246,   246,   247,   247,   248,   248,
     248,   248,   248,   248,   248,   248,   248,   248,   248,   248,
     248,   248,   249,   249,   250,   250,   251,   251,   252,   252,
     252,   252,   252,   252,   252,   252,   252,   252,   252,   252,
     252,   252,   253,   253,   254,   255,   255,   255,   256,   257,
     258,   259,   260,   260,   261,   262,   263,   264,   265,   266,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   277,   278,   278,   278,   278,   279,   279,   280,
     280,   281,   281,   281,   282,   282,   283,   283,   284,   284,
     284,   285,   285,   286,   286,   286,   286,   286,   286,   286,
     286,   286,   286,   287,   287,   287,   287,   287,   287,   287,
     287,   287,   287,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   289,   289,   289,   289,   290,   290,   291,   292,
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
     393,   394
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     3,     0,     1,     1,     1,     1,     2,
       2,     2,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     1,     1,     3,     9,     7,     7,     9,     5,     7,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,    16,    18,
      18,    20,     7,     3,     3,     3,     5,     3,     3,     1,
       1,     5,     7,     9,     1,     5,     7,     9,     1,     1,
       5,     5,     7,     9,     7,     9,     1,     5,     7,     5,
       5,     5,     3,     1,     1,     3,     3,     9,     1,     5,
       3,     7,     5,     3,     5,     5,     3,     5,     5,     1,
       7,     9,     7,     9,     3,     7,     9,    11,     9,     9,
       7,     7,     7,     7,     3,     3,     5,     3,     5,     3,
       5,     7,     3,     3,     3,     7,     5,     7,     5,     5,
       5,     5,     5,     3,     3,     5,     3,     3,     5,     7,
       5,     9,     5,     5,     5,     5,     5,     5,     5,     5,
       5,     5,     0,     2,     3,     5,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     1,     3,     5,     3,
       5,     3,     5,     7,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     1,     3,     5,     1,
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
       1,     3,     3,     3,     5,     5,     4,     4,     4,     6,
       7,     4,     4,     3,     4,     7,     9,     6,     3,     9,
      11,     7,    17,    30,     8,     4,    25,    24,    23,    22,
      25,    24,    21,    20,    29,    28,    19,    18,    23,    13,
      12,    13,    12,    11,    12,    11,    17,    21,    11,    10,
       6,     9,    14,    10,    29,    20,    19,    29,    19,    30,
      20,    17,    28,    27,    25,    18,    17,    27,    15,    16,
      19,    20,    17,    15,    18,    15,    10,    15,     7,     8,
      23,    25,    14,    13,    18,    11,     5,     4,     9,    13,
       6,     6,     5,     4,     4,     5,    10,     5,    13,     4,
       4,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     7,     8,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     5,     6,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    30,    31,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,   509,   510,     2,     0,     9,   361,   356,
     355,   353,   354,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   345,   347,   348,   349,   350,
     351,   352,   357,   358,   359,   360,   362,   363,   364,   365,
     366,   367,   368,   369,   370,   371,   372,   373,   374,   375,
     376,   377,   378,   379,   380,   381,   382,   383,   384,   385,
     386,   387,   388,   389,   390,   391,   392,   393,   394,   395,
     396,   397,   398,   399,   400,   401,   402,   403,   404,   405,
     406,   407,   408,   409,   410,   411,   412,   413,   414,   415,
     416,   417,   418,   419,   420,   421,   422,   423,   424,   425,
     426,   427,   428,   429,   430,   431,   432,   433,   434,   435,
     436,   437,   438,   439,   440,   441,   442,   443,   444,   445,
     446,   447,   448,   449,   450,   451,   452,   453,   454,   455,
     456,   457,   458,   459,   460,   461,   462,   463,   464,   465,
     466,   467,   468,   469,   470,   471,   472,   473,   474,   475,
     476,   477,   478,   479,   480,   481,   482,   483,   484,   485,
     486,   487,   488,   489,   490,   491,   492,   493,   494,   495,
     496,   497,   498,   499,   500,   501,   508,    12,   273,    11,
     256,    10,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   511,
       0,     0,     0,     0,     0,   512,     0,     0,   513,     0,
       0,     0,     0,   528,     0,     0,     0,     3,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   274,   261,
     275,   276,   277,   278,   279,   280,   281,   282,   346,   335,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   257,
       0,     0,     0,    13,    32,    40,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    16,     0,    99,
     104,   116,   123,   124,     0,   108,     0,     0,     0,     0,
       0,   100,     0,   109,     0,     0,     0,     0,     0,   128,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     139,     0,    14,     0,    15,     0,     0,    26,     0,     0,
      27,     0,     0,     0,    28,     0,     0,    29,     0,     0,
       0,     0,     0,    17,     0,     0,     0,    18,     0,     0,
       0,     0,     0,     0,     0,    19,   201,   203,   200,   198,
     202,   199,     0,   206,     0,     0,     0,     0,    20,     0,
       0,    21,     0,     0,     0,     0,     0,     0,     0,    22,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    23,    42,    43,    44,    45,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    46,    50,    51,    52,    49,
      48,    47,    63,    64,    62,    24,    65,    66,    67,    68,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    69,
      73,    74,    75,    72,    71,    70,    86,    87,    85,    25,
       0,     0,   518,     0,     0,   516,   521,   522,   517,   611,
       0,     0,     0,     0,     0,   262,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   192,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   515,     0,     0,
       0,   607,     0,   514,     0,     0,     0,     0,     0,     0,
      41,   238,    33,   235,     0,     0,     0,     0,     0,     0,
     253,   251,   252,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   264,   265,
     266,   267,   268,   269,   270,   271,   272,     0,   125,   225,
     126,     0,     0,     0,     0,   130,   231,     0,   133,     0,
     136,     0,     0,     0,   122,     0,     0,     0,     0,     0,
       0,   163,   164,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   157,   159,     0,
     173,   174,     0,     0,     0,     0,     0,   204,   205,   207,
     209,     0,   211,     0,     0,   176,     0,   237,     0,   177,
       0,   234,    93,    94,    95,     0,    97,     0,    98,     0,
       0,     0,     0,     0,     0,   144,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   155,   229,
       0,   261,   230,   154,   255,   254,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   162,   519,     0,
     527,     0,     0,     0,     0,     0,   503,     0,   502,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   193,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   610,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   520,     0,
       0,     0,     0,     0,   506,   505,   504,   507,     0,     0,
       0,    38,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   117,     0,     0,     0,
     196,   197,   119,   120,   121,   110,     0,   105,     0,     0,
       0,   111,     0,     0,   523,   129,   101,     0,     0,   134,
     132,   135,   137,   138,     0,     0,     0,     0,   226,     0,
       0,     0,   168,     0,     0,   166,     0,     0,   169,   170,
     171,   172,     0,     0,     0,   156,     0,   158,   160,   228,
     175,   233,     0,     0,     0,     0,   208,   210,     0,     0,
     232,     0,   214,     0,    96,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   258,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     597,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   560,     0,     0,   600,     0,   601,   535,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   603,
     604,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   609,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   259,   260,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   529,     0,   531,     0,     0,     0,
       0,     0,    39,    35,    36,     0,     0,     0,   531,     0,
     588,     0,     0,     0,     0,   118,   106,     0,   114,     0,
     102,     0,   112,   131,     0,     0,    92,   227,     0,     0,
       0,   247,   249,   250,   167,   165,     0,     0,   588,     0,
       0,   353,   354,   194,   241,   243,   246,   245,   244,   161,
     240,     0,     0,     0,     0,     0,   212,     0,   596,     0,
       0,     0,     0,   178,   218,     0,   219,   180,   220,   182,
       0,     0,   189,   190,   191,   183,   221,   184,   222,   223,
     185,   224,     0,   186,   187,   188,   140,     0,   142,     0,
     145,     0,   602,     0,     0,     0,     0,     0,     0,   151,
     150,   236,   153,   152,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   534,     0,   589,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   530,     0,     0,     0,     0,     0,    37,    34,
       0,     0,     0,     0,     0,     0,   605,     0,   107,   115,
     113,   103,   127,     0,     0,     0,     0,   248,     0,     0,
       0,   195,   242,     0,     0,     0,     0,   213,     0,     0,
       0,     0,   179,     0,     0,     0,   141,   143,     0,     0,
       0,   148,   149,   146,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   559,     0,     0,     0,     0,     0,   524,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   526,
       0,   598,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   181,     0,     0,   147,
       0,     0,   553,     0,     0,     0,     0,     0,   558,     0,
       0,     0,     0,     0,   555,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   586,     0,     0,     0,     0,     0,     0,   550,
       0,     0,   552,     0,     0,     0,   554,     0,     0,     0,
       0,     0,     0,     0,     0,   593,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   593,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   525,     0,     0,
     595,     0,   549,     0,   551,     0,     0,   608,     0,   592,
       0,     0,     0,     0,     0,     0,     0,     0,   592,     0,
       0,     0,     0,     0,     0,   606,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   599,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   583,   578,     0,   578,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   579,     0,     0,
      88,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     532,     0,     0,     0,   576,   582,     0,     0,   556,     0,
       0,     0,   576,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   583,   585,   587,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   556,     0,     0,     0,     0,     0,
       0,     0,   594,     0,   575,     0,     0,     0,     0,     0,
       0,    89,    90,   239,   215,   216,   217,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   547,     0,     0,     0,     0,     0,   580,     0,   566,
     568,     0,     0,     0,     0,     0,   580,     0,     0,     0,
       0,     0,   566,     0,     0,     0,     0,     0,     0,   571,
       0,     0,     0,   546,     0,     0,     0,     0,     0,     0,
       0,   570,   565,     0,     0,     0,     0,     0,     0,   581,
       0,     0,     0,    91,     0,     0,     0,     0,     0,   584,
       0,     0,     0,     0,     0,     0,   543,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   557,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   542,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   570,     0,     0,     0,     0,
       0,   539,     0,     0,   590,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   548,     0,
     538,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   537,     0,     0,   541,     0,
       0,     0,     0,   591,     0,   574,     0,     0,     0,     0,
     536,     0,     0,   540,     0,     0,     0,     0,     0,   561,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   577,
       0,   563,     0,   573,     0,     0,     0,     0,     0,   572,
       0,     0,     0,   545,     0,   567,     0,     0,   564,   544,
     569,   533,     0,   562
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    14,    15,    16,    17,   353,   481,   505,   402,   404,
     451,   367,   459,   423,   529,   407,   410,   414,   417,   427,
     448,   785,   727,  1055,  1009,   435,   765,   769,  1851,  1303,
    1305,  1307,  1315,  1317,  1320,   708,  1037,  1266,  1058,   818,
     715,  1069,  1060,   770,   662,  1340,   766,   660,  1852,  1289,
    1283,  1284,  1042,  1271,   668,   823,  1285,  1286,   820,   278,
     716,   280,   847,   663,  1166,    55,    56,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,  1319,
    1313,  1314,   669,    30,    31,    32,    33,   354,   369,   370,
     371,   684,   482,   483,   484,   485,   486,   487,   488,   489,
     490,   491,   492,   493,   494,   495,   496,   497,   498,   499,
     500,   501,   372,   373,   503,   449,   374,  1854,  1855,  1856,
     461,   375,   376,   377,   378,   379,   380,   788,   381,   463,
     382,   383,   384,   385,   386,   387,   355,   389,   390,   391,
     792,   793,   794,   808,   392,   393,   356,   395,   357,   397,
     398,   812,   777,   670,   671,   672,   399,   400,   809,   796,
     797,  1010,  1011,    34,   504,   803,   470,    35
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -1336
static const yytype_int16 yypact[] =
{
      44, -1336, -1336,   110,   317,   138,   158,   188,   106,    81,
     189,   229,    85,   230,   298,   130,  2405, -1336,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48, -1336,   296,   311,   302,   325,
     336,   354,   360,   369,   412,   447,   400,   465,   125,   496,
     509,   195, -1336, -1336, -1336, -1336,   314, -1336, -1336, -1336,
   -1336, -1336, -1336, -1336,   495,   495,   495,   495,   495,   495,
     495,   495,   495, -1336, -1336, -1336, -1336, -1336, -1336, -1336,
   -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336,
   -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336,
   -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336,
   -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336,
   -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336,
   -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336,
   -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336,
   -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336,
   -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336,
   -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336,
   -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336,
   -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336,
   -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336,
   -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336,
   -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336,
   -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336,
   -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336,
   -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336,
   -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336,
   -1336, -1336, -1336, -1336, -1336, -1336, -1336,  3291, -1336, -1336,
   -1336, -1336,   183,   136,   516,   516,   529,   539,   540,   540,
     214,   214,   285,   370,   257,   242,    82,    82,   542, -1336,
     545,   523,   546,   530,   547, -1336,   532,   549, -1336,   544,
     535,   541,   552, -1336,   543,   553,   537, -1336, -1336, -1336,
   -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336,   495, -1336,
     495,   495,   495,   495,   495,   495,   495,   495, -1336, -1336,
   -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336,
     551,   558,   554, -1336, -1336,    48,    48,    48,   403,   556,
     559,   561,   548,   557,   562,   565,   568, -1336,    48, -1336,
   -1336, -1336, -1336, -1336,    48, -1336,    48,    48,    48,    48,
      48, -1336,    48, -1336,    48,    48,    48,    48,    48, -1336,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
   -1336,   564, -1336,    48, -1336,    48,   567, -1336,    48,   575,
   -1336,    48,    48,   583, -1336,    48,    48, -1336,    48,    48,
     569,   570,   582, -1336,    48,    48,    48, -1336,    48,    48,
      48,   417,   584,   571,   589, -1336, -1336, -1336, -1336, -1336,
   -1336, -1336,    48, -1336,    48,    48,    48,   579, -1336,    48,
      48, -1336,    48,    48,    48,    48,   578,   597,   595, -1336,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,   585,   586,   601,   603,   590,   598,   604,   596,   600,
     602, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336,
   -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336,
   -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336,
   -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336,
   -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336,
      48,   605, -1336,   608,   611, -1336, -1336, -1336, -1336, -1336,
     610,   616,   619,   621,   636, -1336,   638,   576,   637,   318,
     318,     7,   642,   639,   647,   593,   667,   613,   645,   657,
     656,   669,    72,   673,   673,   673,   673,   673,   673,   673,
     673,   673,   673,   406,   673,   673,   673,   673,   506,   673,
      31,    31,   673,   673,   673,   682,   676,   506,   687,   406,
     622,    12,    12,   625,   318,   318,   318,   318,   688,   626,
     694,  3291,  3291,   506,   506,   506,   506,   695,   699,   634,
     706,   406,   506,    31,    31,   692,    14,  3291,   506,   406,
      17,   318,   708,   709,   712,   144,   506,   506,   506,   506,
     707,   147,   228,   228,   461,  3510,   716,   717,   721,   653,
     654,   711,   101,   710,   713,   722,   506, -1336,   730,   723,
     732, -1336,   724, -1336,   720,   726,   735,   736,  2627,  2627,
   -1336, -1336, -1336, -1336,   729,   731,   742,    48,    48,    48,
   -1336, -1336, -1336,   739,   740,   737,   741,   761,   752,   763,
     755,   781,   765,   773,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,   495,   495,
     495,   495,   495,   495,   495,   495,   495,   776, -1336, -1336,
   -1336,    48,    48,    48,    48, -1336, -1336,    48, -1336,    48,
   -1336,    48,    48,    48, -1336,   780,   775,   506,    48,    48,
     782, -1336, -1336,   783,   778,    48,    48,    48,    48,   785,
      48,    48,    48,    48,   786,   777,   788,  2627,  2627,    48,
   -1336, -1336,    48,   789,   787,   784,   790, -1336, -1336, -1336,
   -1336,    48, -1336,    48,   791, -1336,    48, -1336,    48, -1336,
      48,  3291, -1336, -1336, -1336,   792, -1336,    48, -1336,   793,
     794,   795,   779,   143,   797, -1336,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,   804,    48,   798,   801,   799,    48,    48,    48,
      48,   805,    48,    48,    48,    48,   495,   495, -1336, -1336,
     313,    32, -1336, -1336,  3291, -1336,   811,   808,   807,   813,
     806,   821,   815,   823,   822,   827,   826, -1336, -1336,   816,
   -1336,   833,   828,   829,   830,   759,  3291,  1961, -1336,  2183,
     844,   832,   845,   318,   318,    54,   834,   835,   836,   837,
     838,   848,   800,   849,   843,   847,   850,   506,   117,   506,
     506,  3291,   506,  3291,  3291,   506,   506,   506,   506,  3291,
     506,   846,   506,  3291,   506,   506,   318,   318,   318,   318,
     506,   802,   851,    48, -1336,   506,   809,   852,   863,  3291,
     318,  3291,   318,   864,   318,   318,   318,   318,   842,   856,
     810,  3291,  3291,   506,   506,   870,   865,   857,   817,   318,
     318,   868,   506,   318,   506,   871,   318,   875, -1336,   820,
     859,   888,   873,   882,   506,   506,   506,   506,   506,   506,
     506,   506,   506,   506,   506,   506,  3291,   506,  3291,   506,
     883,   506,   891,   876,   893,   506,   506,   506,   506,   880,
     318,   318,   318,   318,   449,   485,   495,   885,   896,   889,
     890,   897,   906,   839,   903,   908,   900,   910, -1336,   915,
     901,   913,   902,   911, -1336,  3291, -1336, -1336,   904,   858,
     909,    48,    48,    48,    48,   860,   921,   918,   916,   927,
     920,   928,   922,   867,   931,   929, -1336,   917,   940,    48,
   -1336, -1336, -1336, -1336, -1336, -1336,  2627,  3291,    48,    48,
      48, -1336,  2627,    48, -1336, -1336,  3291,    48,    48, -1336,
   -1336, -1336, -1336, -1336,   937,   877,   506,    48, -1336,   938,
     930,   881,    48,  3729,    48,    48,    48,   934, -1336, -1336,
   -1336, -1336,   884,   942,   952,    48,  3948,    48,    48, -1336,
   -1336, -1336,   892,   957,   950,   956, -1336, -1336,   945,    48,
   -1336,    48, -1336,   964, -1336,   898,   959,   961,   962,   967,
     958,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    48,  4167,    48,  4386,    48,   969,    48,   968,
     971,   970,    48,    48,    48,    48,   975,    48,    48,    48,
      48,   495,   495,   495,   912,   963,   982,   972,   966,   978,
     983,   984,   985,   924,   926,   994,   991,   989,   986,   988,
   -1336,   279,   987,   506,   318,   318,   318,   992,  1002,   996,
     993, -1336,  1005,   997, -1336,   995, -1336, -1336,   998,  1001,
     506,  3291,   506,   506,   506,  3291,   506,   506,   506,  1000,
    1003,    48,   506,  1006,  1007,  1004,  3291,  2849,  3291,  3291,
    1009,  1010,  1011,  1012,  3291,  3070,   318,  1015,  1019,  1028,
    1020,  1023,   506,   506,  1033,  1018,  1025,  1026,   974, -1336,
   -1336,   506,   506,  3291,   506,   132,   506,   406,  3291,   506,
     461,  3510,  3510,  3070,  3291,  3070,  3291, -1336,   318,  1027,
    1031,   990,   506,   506,   506,   506,  1022,   318,   318,   318,
     318,   495,   495,  1044,  1013,  1034,  1043,  1061,  1014,  1052,
    1055,  1016,  1050,  1074, -1336,  1078, -1336,  1063,  1064,  1067,
    1081,  1069, -1336, -1336,    48,    48,  1068,  1079,  1073,  1075,
    1077,    59,  1082,  1096,  1101, -1336,  2627,    48, -1336,    48,
    2627,    48, -1336, -1336,  1086,   506, -1336, -1336,  1088,  1090,
    4605, -1336,  3291, -1336,    48,    48,  1093,  1091, -1336,  1097,
    4824,   495,   495,  1127, -1336,  3291, -1336, -1336, -1336, -1336,
   -1336,  1094,  1073,  1077,   175,  1112, -1336,    48, -1336,  1099,
     207,  1053,  1114, -1336, -1336,    48, -1336, -1336,  3291, -1336,
    1116,  1111, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336,
   -1336,  3291,    48, -1336, -1336, -1336,  1127,  5043,  1127,  5262,
   -1336,  1058, -1336,  1128,    48,    48,    48,    48,  1121, -1336,
   -1336, -1336, -1336, -1336,  1117,  1126,  1062,  1119,  1070,  1130,
     237,  1134,  1137,  1132,  1136,  1138,  1131,  1122,  1149,  1152,
    1147,   506,   318,  1141,  1153, -1336,  1142, -1336,  1143,  1145,
    1148,  1150,  1161,  3291,  3291,  3291,  3291,   506,  1151,    48,
    1154,  1155,  2849,  1156,  1158,  1159,  3070,  3070,  1162,  1160,
    1165,  1176,   506,  1178,  1175,  1157,  1185,   506,  1164,  1188,
     506,  3070,  3070,  1193,  1194,   506,   506,   461,   318,  1163,
    1183,  1203,   290,  1192,   367,  1200,  1195,  1197,  1201,  1204,
    1209,  1199, -1336,  1208,  1210,  1167,  1211,  1207, -1336, -1336,
    1214,  1102,  1218,  1213,  1216,  1232, -1336,  1222,    48,  3291,
    3291,    48, -1336,  1219,  3291,  1220,  1226, -1336,  1227,  1225,
    1223,  1127, -1336,  1228,  1230,  1224,  1231, -1336,  1236,  1233,
    1234,   491, -1336,  1253,  1251,    48,  1127,  1127,  1237,  1245,
      48, -1336, -1336, -1336,  1241,  1246,  1252,  1250,  1254,  1256,
    1255,  1258,  1260,  1247,  1257,  1268,  1259,  1271,  1262,  1273,
    1261,  1267,  1263,  1278,  1264,   236,  1279,  1215,  1266,  1284,
    1270,  1272,    48,  1274,  1286,  1287,  1275,  1235,  1276,  1239,
    1277, -1336,  1283,  1240,  1285,  1291,  1292, -1336,   406,  1288,
    1294,   506,  1298,  1295,  1282,  1296,  1309,  1313,  1299,  1315,
    1304,  1265,  1301,  1308,  1310,  1320,  1306,  1314,  1316, -1336,
    1311, -1336,  1307,  1312,  1317,  1323,  1321,   149,  1325,  1269,
    1340,  1329,   318,  1330,  1332,  1333,  1324,  1345,  1331,  1348,
    1341,  1337,   191,  1342,  1339,  1349, -1336,  1344,  1346, -1336,
    1347,  1343, -1336,  1351,  1352,  1354,  1356,  1358, -1336,  1362,
    1363,  1350,  1357,  1319, -1336,  1361,  1377,  1378,  1334,  1384,
    1388,  1387,  1376,   174,  1391,  1398,  1405,  1402,  1406,    48,
    1409,  1390,  1397,  1353,  1413,  1355,  1414,  1415,  1359,  1416,
    1407,  1404,  1364,  1403,  1408,  1412,  1418,  1366,  1419, -1336,
    1421,  1422, -1336,  1423,  1428,  1424, -1336,  1431,    36,  1430,
    1426,   522,  1436,  1437,  1453,    39,  1441,  1455,  1447,  1452,
    1461,  1462,  1463,   506,  1464,    40,  1410,  1476,  1460,  1479,
    1465,  1470,   524,  1466,  1467,  1469,   131, -1336,  1471,  1474,
   -1336,  1486, -1336,    45, -1336,  1472,  1478, -1336,  1480, -1336,
    1489,  1477,  1493,  1491,   179,  1485,  1487,  1432,  1433,  1498,
    1496,  1484,  1488,  1492,  1490, -1336,  1494,    48,  1495,  1503,
    1511,  1509,  1514,  1513,  1504,  1515,  1520,  1517,  1507,  1457,
    1521,  1516,  1505,  1468,  1522,  1527,  1473,   278,  1524,  1518,
    1519,  1528,  1481, -1336,  1541,  1523,  1534,  1482,  1542,  1540,
    1544,  1546,  1547,  1551,  1497,    47,  1537, -1336,   461,  1538,
    1549,  1539,  1556,  1545,  1557,    51,  1561,  1548,  1560,  1497,
      73,  1563,  1553,  1550,  1566,  1567,  1552,  1565,  1558,  1568,
    1562,  1575,  1508,  1569,  1564,  1571,  1572,  1576,  1559,  1573,
    1570,  1577,  1578,  1574,  1582,  1579,  1580, -1336,  1581,  1583,
      48,  1584,  1586,  1585,  1590,  1595,  1588,  1591,  1597,  1599,
    1600,  1555,  1593,  1589,  1605,  1594,  1602,  1598,  1596,  1601,
    1608,  1610,   281,  1603,  1611,  1617,  1606,  1618,  1619,  1604,
   -1336,  1612,  1620,  1621,  1613,  1587,  1626,  1628,  1592,    25,
    1625,  1630, -1336,  1631,  1613,  1635,  1623,  1636,  1607,  1637,
    1615,  1627, -1336, -1336, -1336,  1639,  1638,  1629,  1640,  1632,
    1609,  1633,  1641,  1643, -1336,  1646,  1634,  1649,  1652,  1642,
    1644,  1650, -1336,  1648, -1336,  1645,  1647,  1656,  1660,  1662,
    1654,    48, -1336, -1336, -1336, -1336, -1336,  1659,  1669,  1672,
    1663,  1676,  1677,  1667,  1670,  1680,  1681,  1682,  1622,  1668,
    1686, -1336,   380,  1671,  1684,  1675,  1688, -1336,  1683,  1678,
    1651,  1685,  1690,  1691,  1695,  1699,  1687,  1703,  1653,  1694,
     318,  1696, -1336,  1678,  1687,  1702,  1655,  1714,  1704, -1336,
    1705,  1657,  1710, -1336,  1701,  1712,  1715,  1716,  1717,  1664,
    1719,  1666, -1336,  1723,  1720,  1673,  1725,  1713,  1729, -1336,
    1721,  1739,  1727, -1336,  1732,  1666,  1733,  1730,  1745, -1336,
     384,  1737,  1738,  1731,  1748,  1735, -1336,   414,  1740,  1741,
    1755,  1742,  1756,  1746,  1758,  1760, -1336,  1761,  1754,  1749,
    1767,  1768,  1759,  1757,  1762,  1764,  1763,  1765,  1769, -1336,
    1770,  1772,  1750,  1776,  1771,  1707,  1773,    83,  1774,  1753,
    1775,  1777,  1781,  1779,  1780, -1336,  1778,  1786,  1783,  1782,
    1784, -1336,  1785,  1788, -1336,  1787,  1794,  1796,  1792,  1797,
    1798,  1803,  1808,  1790,  1810,  1807,  1799,  1800, -1336,  1743,
   -1336,  1802,  1804,  1817,  1809,  1805,  1624,  1801,  1806,  1811,
    1813,  1816,  1812,  1814,  1815, -1336,   505,  1818, -1336,  1819,
    1823,  1821,  1826, -1336,  1828, -1336,  1820,  1822,  1832,  1834,
   -1336,  1825,  1827, -1336,  1837,  1824,  1829,  1830,  1831,  1789,
    1833,  1835,  1836,  1838,  1839,  1841,  1842,  1845,  1844, -1336,
    1848, -1336,  1847, -1336,  1843,  1849,  1853,  1850,  1851, -1336,
    1852,  1854,  1846, -1336,  1855, -1336,  1859,  1858, -1336, -1336,
   -1336, -1336,  1861, -1336
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336,
   -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336,
   -1336, -1336, -1336,  -883, -1336, -1336, -1336, -1336, -1336,  -848,
   -1335, -1336,   401,   343, -1336,  -547,  -988, -1205,   458, -1180,
     534, -1112, -1097,  -852,  -300,   677,  -922,   681,     8,   492,
   -1118,   512,  -879,   520,  1048,  -652,   519,  -604,   -15,   152,
      10,   471,  1248,  -274,   -16,  1856, -1336, -1336, -1336, -1336,
   -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336, -1336,  -484,
   -1336, -1336,  -495, -1336, -1336, -1336, -1336,   -52,  1614,  1616,
    1658,  -376,  1661,  1665,  1887,  2108,  2330,  2331,  2552,  2553,
    5187,  5188,  5189,  5190,  5191,  5192,  5193,  5194,  5195,  -269,
    -261,  -259,   255, -1336,  5196, -1336,  5201, -1336, -1336, -1336,
   -1336,  5203,  -266, -1336, -1336,  5202,   -98, -1336,  5204, -1336,
    5205,  5206,  -258, -1336,   272,   244,  -260,  5207, -1336,  1280,
   -1336, -1336, -1336, -1336,   247,  5209,    49,   140,    62,    96,
   -1336,  1281, -1336, -1336,  -483,   -33, -1336,  -268, -1336, -1336,
   -1336, -1336, -1336, -1336,  5208,  -346, -1336, -1336
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -274
static const yytype_int16 yytable[] =
{
     281,  1071,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,  1014,
    1323,  1242,  1045,   388,   424,   428,   279,   469,   523,  1057,
     819,   664,   425,   429,   453,   465,   524,  -273,   525,   665,
     729,   775,   731,   666,   734,     1,   726,     2,  1161,   328,
     330,   331,   332,   333,   334,   335,   336,   337,  1849,  1850,
    1379,  1263,  1462,     3,   757,     4,     5,   666,     6,     7,
    1470,  1297,   773,  1669,     8,     9,  1678,  1669,   664,    10,
      11,    12,  1706,    13,  1767,  1326,   734,  1328,  1767,   710,
     666,   728,   472,  1368,  1780,  1690,  1369,   719,   721,   683,
      45,   471,   472,   473,   474,   732,   475,   476,    49,   478,
    1989,  1781,   480,   477,    46,  1334,  1335,  1336,  1337,   478,
     479,   768,   480,   832,    50,  1670,  1984,   758,  1679,  1689,
     761,   763,    36,    43,  1707,   774,  1768,  1007,   833,    44,
    1776,   318,   698,   699,   700,   701,   702,   703,   704,   705,
     706,  1008,  1700,  1604,  1310,   358,   311,   359,   360,   361,
     362,    40,   312,   782,  1311,  1701,   804,   363,  1261,  1702,
     931,  1593,  1442,   364,   365,   783,   366,   805,   806,   802,
     893,   784,   932,  1594,   366,    41,  1569,   688,   689,   690,
     691,   692,   693,   694,   695,   696,   697,  1636,   711,   712,
     713,   714,  1715,   717,   350,   351,   722,   723,   724,  1389,
    1637,    42,  1390,  1609,   352,  1716,   329,   329,   329,   329,
     329,   329,   329,   329,   329,  1610,   315,  1472,    47,   658,
     659,   368,   316,   420,   658,   659,   658,   659,   421,   658,
     659,  1394,   452,   460,  1357,   422,   530,   658,   659,  1428,
     811,   667,    48,   658,   659,  1543,  -273,  -273,  -273,  1544,
     802,   456,    51,   350,   413,   457,   421,  1545,  1451,    -4,
      -4,  1416,   276,   458,  1417,   661,   658,   659,   350,   413,
     718,   720,   366,  1466,  1467,   810,   813,   815,   352,  1274,
    1275,   735,   737,   685,   740,   741,   742,   743,    52,  1748,
    1749,   686,  1831,   687,   431,  1750,   432,   409,  1832,   433,
    1239,  1477,  1833,   760,   762,  1240,   434,  1478,   299,   966,
     776,   778,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   394,  1023,   300,  1025,   301,   415,   418,   549,
     550,   551,   767,   454,   467,   396,  1309,    37,   302,   412,
      38,  1322,   562,    39,   446,    53,    54,   795,   563,   786,
     564,   565,   566,   567,   568,   790,   569,   789,   570,   571,
     572,   573,   574,   303,   575,   576,   577,   578,   579,   580,
     581,   582,   583,   584,   416,   419,   304,   586,  1480,   587,
     455,   468,   589,   361,  1481,   591,   592,   447,   305,   594,
     595,  1905,   596,   597,  1098,  1953,   306,  1906,   601,   602,
     603,  1954,   604,   605,   606,   318,   698,   699,   700,   701,
     702,   703,   704,   705,   706,   707,   611,   411,   612,   613,
     614,   307,   445,   616,   617,  1960,   618,   619,   620,   621,
     309,  1961,   552,   553,   625,   626,   627,   628,   629,   630,
     631,   632,   633,   634,   635,  1111,   607,   553,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   816,   817,
     318,   698,   699,   700,   701,   702,   703,   704,   705,   706,
     545,   308,   545,   545,   545,   545,   545,   545,   545,   545,
    1438,  1112,   310,  1441,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   327,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   327,   646,   318,   698,   699,   700,   701,
     702,   703,   704,   705,   706,  1515,  2031,   787,  1357,   314,
     408,  1687,  2032,   807,   313,   277,   442,   426,   430,    53,
     658,   659,   466,  1673,  1674,  1695,  1696,   401,  1770,  1324,
    1325,   502,   526,   991,   992,   993,   403,   405,   736,   738,
     406,   409,   413,   350,   531,   533,   532,   538,   534,   535,
     536,   537,   543,   539,   540,   541,   544,   546,   547,   555,
     542,   548,   554,   709,   558,   559,  1029,  1030,  1031,  1032,
     557,   585,  1502,   556,   588,   590,   819,   709,   560,   709,
    1044,   561,  1046,   593,  1048,  1049,  1050,  1051,   598,   600,
     608,   615,   599,   609,   750,   751,   610,   622,   623,  1066,
    1067,   709,   624,   639,   636,   637,  1074,   638,   641,   709,
    1599,   642,   640,   644,   643,   645,   798,   799,   800,   801,
     652,   647,   848,   848,   822,   825,   648,   649,  1312,   767,
     650,   853,   854,   855,   651,   653,   654,   655,   674,   657,
    1107,  1108,  1109,  1110,   673,   656,   675,   679,   867,   868,
     869,   870,   871,   872,   873,   874,   875,   876,   877,   878,
     879,   880,   676,   328,   330,   331,   332,   333,   334,   335,
     336,   337,   677,   680,   681,   882,   883,   884,   885,   682,
     683,   886,   678,   887,   725,   888,   889,   890,   726,   730,
     744,   733,   894,   895,   739,   745,   746,   753,   754,   899,
     900,   901,   902,   755,   904,   905,   906,   907,   756,   764,
     779,   911,   912,   913,   781,   780,   914,   709,   826,   802,
     828,   827,   829,   830,   831,   919,   834,   920,   349,   836,
     922,   835,   923,   838,   924,   840,   839,   842,   843,   850,
     841,   926,   844,   845,   851,   852,   856,   857,   859,   858,
     934,   935,   936,   937,   938,   939,   940,   941,   942,   943,
     944,   945,   946,   947,   948,   949,   821,   951,   860,   861,
     862,   955,   956,   957,   958,   863,   960,   961,   962,   963,
     864,   964,   965,   819,   865,   866,   881,   891,   892,   896,
     897,   898,   903,   908,   909,   910,   915,   918,   930,   916,
     927,   917,   929,   950,   953,   925,   954,   928,   959,   921,
     933,   986,   968,   986,  1243,  1244,  1245,   952,   967,   969,
     970,   972,   973,   971,   974,   975,   976,   977,   983,   980,
     329,   329,   329,   329,   329,   329,   329,   329,   329,   978,
     979,   981,   982,   988,   989,   996,   990,   995,   997,   998,
     999,  1000,  1002,  1003,  1005,  1052,  1024,  1036,  1004,  1053,
    1064,  1077,  1015,  1035,  1040,  1018,  1019,  1020,  1021,  1001,
     709,  1034,   709,  1273,  1027,  1041,  1047,  1063,  1039,  1054,
    1033,  1288,  1290,  1062,  1068,  1038,  1065,  1073,  1075,  1076,
    1078,  1079,  1080,  1099,  1097,  1101,  1100,  1106,  1114,  1115,
    1118,  1116,  1117,  1059,  1061,  1119,  1121,  1122,  1120,  1288,
    1123,  1288,  1070,  1124,   661,  1125,  1127,  1126,  1129,  1128,
    1138,  1139,  1130,  1339,  1341,  1342,  1341,  1131,  1132,  1137,
    1141,  1113,  1142,  1140,  1146,  1143,  1145,  1094,  1144,  1096,
    1148,   709,  1147,  1149,  1159,  1163,  1160,  1164,   329,   329,
    1165,  1170,   545,  1171,  1172,  1133,  1134,  1135,  1136,  1173,
    1178,  1177,  1179,  1180,  1181,  1184,  1186,  1185,  1187,  1188,
    1189,  1190,  1207,  1150,  1210,  1209,  1216,  1211,  1227,  1224,
    1151,  1223,  1152,  1153,  1154,  1225,  1155,  1156,  1228,  1226,
    1229,  1157,  1158,  1232,  1230,  1233,  1231,  1234,  1235,  1236,
    1238,  1162,  1247,  1241,  1237,  1246,  1248,  1250,  1168,  1251,
    1169,  1249,  1264,  1278,  1239,  1252,  1253,  1254,  1268,  1174,
    1240,  1174,  1176,  1277,  1279,  1269,  1038,  1276,  1291,  1292,
    1293,  1299,  1294,  1182,  1295,  1183,  1298,  1300,  1338,  1301,
    1331,  1332,  1429,  1302,  1346,  1191,  1192,  1193,  1194,  1195,
    1196,  1197,  1198,  1199,  1200,  1201,  1202,  1344,  1204,  1333,
    1206,  1347,  1208,  1348,  1350,  1351,  1212,  1213,  1214,  1215,
    1353,  1217,  1218,  1219,  1220,  1354,  1221,  1222,  1355,  1356,
    1358,  1357,  1345,  1349,  1359,  1352,  1360,  1363,  1273,  1364,
    1365,  1366,  1288,  1288,  1367,  1370,   545,   545,   329,  1371,
     747,   748,  1372,  1378,   819,  1380,  1381,  1288,  1288,  1383,
    1384,  1385,  1387,  1388,  1290,  1391,   771,   749,  1393,  1398,
     752,  1396,  1395,  1070,  1399,  1265,   759,  1403,  1409,  1404,
    1411,  1412,   772,  1418,   824,  1413,  1410,  1415,  1419,  1414,
    1424,  1422,  1257,  1258,  1259,  1420,  1038,  1262,  1061,  1421,
    1423,  1425,  1267,  1426,  1427,  1435,  1431,   846,   846,  1430,
     837,  1432,  1433,  1434,  1437,  1287,  1491,  1436,  1463,  1443,
    1460,  1495,  1445,  1070,  1446,  1448,  1449,  1474,  1450,  1454,
    1453,  1304,  1306,  1455,  1304,   709,  1316,  1318,  1456,  1304,
     822,   825,   825,  1287,  1459,  1287,  1458,  1461,   349,   349,
    1464,  1475,  1061,  1061,  1061,  1061,  1468,  1469,  1361,  1362,
    1476,  1479,  1482,  1485,  1483,  1484,  1487,  1486,  1488,  1489,
    1373,  1374,   349,  1375,  1376,  1377,  1490,  1493,  1494,  1496,
    1492,  1497,  1498,  1499,  1500,  1501,  1503,  1504,  1505,  1506,
    1510,  1507,  1508,   329,   329,   545,   964,   965,  1509,  1511,
    1512,  1513,  1516,  1514,  1517,  1267,  1519,  1520,   767,  1522,
    1523,  1392,  1524,  1525,  1530,  1531,  1526,  1527,  1528,  1397,
    1529,  1533,  1535,  1532,  1536,   349,  1537,  1539,  1534,  1540,
    1538,  1541,  1546,  1542,  1547,  1548,  1400,  1549,  1550,  1554,
    1555,  1551,  1572,  1553,  1556,  1558,  1560,   349,  1405,  1406,
    1407,  1408,  1561,  1563,  1557,  1570,  1567,   821,  1559,  1562,
    1564,  1565,  1568,  1574,  1571,  1573,  1575,  1578,  1576,  1577,
    1580,  1581,  1582,  1583,  1584,  1588,  1585,  1586,  1587,  1590,
    1591,  1589,   821,  1592,  1579,   821,  1595,   821,  1596,  1597,
    1598,  1600,  1603,  1444,  1601,  1602,   985,  1604,   985,  1605,
    1606,  1070,  1607,   545,   545,  1608,  1611,  1612,  1614,  1613,
    1616,  1617,  1615,  1618,  1623,  1619,  1620,  1267,  1621,  1625,
     771,  1622,  1016,  1017,  1624,  1626,  1287,  1287,  1022,  1628,
    1629,  1006,  1026,  1012,  1013,  1630,  1632,  1306,  1627,  1634,
    1316,  1287,  1287,  1633,  1635,  1306,  1059,   822,  1043,  1028,
    1043,  1639,  1174,  1631,  1638,  1174,  1640,  1641,  1645,  1642,
    1056,  1056,  1644,   329,   329,  1646,  1648,  1650,  1651,  1653,
    1654,  1657,  1647,  1655,  1649,  1659,  1665,  1658,  1652,  1518,
    1660,  1666,  1668,  1656,  1521,  1661,   349,  1662,  1072,  1663,
    1664,  1667,  1671,  1675,  1676,  1093,  1672,  1095,  1081,  1082,
    1083,  1084,  1085,  1086,  1087,  1088,  1089,  1090,  1091,  1092,
    1677,  1680,  1681,  1682,  1683,  1685,  1552,   349,   349,  1102,
    1103,  1104,  1105,   349,  1684,  1686,  1688,   349,  1690,  1670,
    1691,  1692,  1694,  1698,  1704,  1693,  1697,  1699,  1705,  1703,
    1709,  1711,  1708,  1710,   349,  1712,  1713,  1714,  1717,  1718,
    1721,  1719,  1720,  1722,  1723,  1730,  1724,   349,  1318,  1726,
    1725,  1306,  1727,  1729,  1731,  1853,  1732,  1733,   821,   821,
    1734,  1736,  1735,  1737,  1738,  1739,  1740,  1741,  1743,  1742,
    1746,  1751,  1745,   821,   821,  1754,  1752,  1744,  1753,   821,
    1756,  1758,  1747,  1757,   349,  1760,   349,  1761,  1764,  1769,
    1755,  1759,  1762,  1763,  1765,  1767,  1771,  1773,  1775,  1772,
    1777,  1779,  1782,  1643,  1784,  1774,  1766,  1780,  1778,  1783,
    1785,  1788,  1786,  1787,  1790,  1789,  1791,  1792,  1820,  1798,
    1794,  1793,  1795,  1797,  1796,  1804,  1799,  1800,  1812,  1801,
    1803,  1802,  1807,  1811,  1806,  1805,  1853,  1813,  1814,  1815,
    1810,  1808,  1818,  1816,  1817,  1821,  1819,  1822,  1823,  1825,
    1824,  1826,  1829,  1830,  1835,  1827,  1836,  1828,  1837,  1838,
    1842,  1834,  1839,  1840,  1843,  1846,  1841,  1847,  1857,  1865,
    1844,  1858,  1859,  1070,  1860,  1861,  1864,  1862,  1868,  1866,
    1867,  1869,  1875,  1870,  2022,  1871,  1873,  1876,  1877,  1883,
    1256,  1728,  1878,  1874,  1260,  1879,  1845,  1889,  1880,  1884,
    1891,  1848,  1881,  1885,  1255,  1270,  1272,  1043,  1043,  1882,
    1886,  1887,  1892,  1280,  1888,  1893,  1863,  1894,  1872,  1895,
    1896,  1897,  1898,  1899,  1900,  1901,  1903,  1904,  1908,  1909,
    1907,  1902,  1308,  1911,  1917,  1912,  1296,  1321,  1918,  1914,
     824,   824,  1920,  1327,  1919,  1329,  1910,   349,  1915,  1916,
    1922,   349,  1925,  1927,  1924,  1929,  1928,  1931,   822,  1932,
    1913,   349,  1921,   349,  1926,  1933,  1930,  1934,  1935,  1944,
    1936,   349,  1938,  1937,  1809,  1939,   349,  1940,  1943,  1941,
    1945,  1947,  1942,  1946,  1948,  1949,  1951,  1950,  1952,  1955,
    1957,  1956,  1958,  1959,  1964,  1963,  1962,  1968,  1966,   349,
    1965,  1971,  1967,  1969,  1970,  1972,  1973,  1974,  1978,  1975,
    1976,  1991,   349,  1984,  1977,  1985,  1987,  1980,   349,  1979,
     349,  1465,  1981,  1982,  1983,  1990,  1992,  1986,  1989,  1988,
    1997,  1995,  2002,  2004,  1993,  1994,  1998,  1996,  2005,  2006,
    2007,  2008,  2000,  2003,  2001,  1999,  2009,  2010,  2011,  2012,
    2013,  2014,  2016,  2015,  2017,  1890,  2019,  2018,  2023,  2027,
    2020,  2021,  2039,  2028,  2024,  2026,  2035,  2025,  2036,  2037,
    2034,  2038,  2029,  2030,  2040,  2041,  2033,  2042,  2043,  2044,
    2045,  1566,  2046,  2055,  1471,  2057,  2048,  2049,  2058,  2047,
    2061,  2051,  2053,  2052,  2060,  2062,  2064,  2054,  2050,  2056,
     821,  2059,  2063,  2073,  2069,  2067,  2065,  2066,  2072,  1330,
    2068,  2070,  1056,  1439,  1440,  1056,  2071,  1343,  1923,  1452,
    1473,  1272,  1447,   994,     0,   791,   436,   849,   437,     0,
     349,   349,   317,     0,   814,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1457,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     438,     0,     0,     0,     0,     0,     0,     0,   506,     0,
       0,     0,   507,   771,   338,    58,    59,    60,    61,    62,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
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
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   984,   508,   276,   338,    58,    59,    60,
      61,    62,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,    73,    74,    75,    76,    77,    78,    79,    80,
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
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   509,   987,   276,    57,    58,
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
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   510,   511,   276,
     338,    58,    59,    60,    61,    62,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,    73,    74,    75,    76,
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
     267,   268,   269,   270,   271,   272,   273,   274,   275,   512,
     513,   276,   338,    58,    59,    60,    61,    62,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,    73,    74,
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
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   658,   659,   338,    58,    59,    60,  1281,  1282,    63,
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
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   658,   659,   338,    58,    59,    60,    61,    62,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
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
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   338,    58,    59,    60,    61,    62,    63,
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
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   338,  1167,    59,    60,    61,    62,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,    73,    74,
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
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   338,  1175,    59,    60,    61,    62,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,    73,    74,    75,
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
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     338,  1203,    59,    60,    61,    62,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,    73,    74,    75,    76,
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
     267,   268,   269,   270,   271,   272,   273,   274,   275,   338,
    1205,    59,    60,    61,    62,   339,   340,   341,   342,   343,
     344,   345,   346,   347,   348,    73,    74,    75,    76,    77,
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
     268,   269,   270,   271,   272,   273,   274,   275,   338,  1382,
      59,    60,    61,    62,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,    73,    74,    75,    76,    77,    78,
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
     269,   270,   271,   272,   273,   274,   275,   338,  1386,    59,
      60,    61,    62,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   348,    73,    74,    75,    76,    77,    78,    79,
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
     270,   271,   272,   273,   274,   275,   338,  1401,    59,    60,
      61,    62,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,    73,    74,    75,    76,    77,    78,    79,    80,
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
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   338,  1402,    59,    60,    61,
      62,   339,   340,   341,   342,   343,   344,   345,   346,   347,
     348,    73,    74,    75,    76,    77,    78,    79,    80,    81,
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
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   514,   515,   516,   517,   518,   519,
     520,   521,   522,   527,   450,   439,   440,   462,   441,   443,
     464,   444,     0,     0,     0,   528
};

static const yytype_int16 yycheck[] =
{
      16,   923,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,   871,
    1200,  1133,   901,   283,   290,   291,    16,   295,   297,   912,
     634,    24,   290,   291,   294,   295,   297,     5,   297,    32,
     587,    24,   589,    36,    32,     1,    32,     3,  1036,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    33,    34,
    1265,  1158,  1397,    19,   611,    21,    22,    36,    24,    25,
    1405,  1183,   619,    37,    30,    31,    37,    37,    24,    35,
      36,    37,    37,    39,    37,  1203,    32,  1205,    37,   573,
      36,   586,    20,    34,    21,    22,    37,   580,   581,    27,
      19,    19,    20,    21,    22,   589,    24,    25,    23,    37,
      27,    38,    40,    31,    33,  1212,  1213,  1214,  1215,    37,
      38,   616,    40,    22,    39,    89,    43,   611,    89,    89,
     613,   614,    22,    27,    89,   619,    89,    20,    37,    33,
      89,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    34,    21,    22,    22,    19,    31,    21,    22,    23,
      24,    23,    37,    19,    32,    34,    19,    31,  1156,    38,
      27,    22,  1377,    37,    38,    31,    40,    30,    31,    32,
     727,    37,    39,    34,    40,    27,  1521,   563,   564,   565,
     566,   567,   568,   569,   570,   571,   572,    23,   574,   575,
     576,   577,    23,   579,    21,    22,   582,   583,   584,    34,
      36,    23,    37,    22,    31,    36,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    34,    31,  1407,    39,   222,
     223,   283,    37,    19,   222,   223,   222,   223,    24,   222,
     223,    34,   294,   295,    37,    31,   298,   222,   223,  1361,
      22,   551,    23,   222,   223,    19,   224,   225,   226,    23,
      32,    19,    32,    21,    22,    23,    24,    31,  1386,   225,
     226,    34,   224,    31,    37,   549,   222,   223,    21,    22,
     580,   581,    40,  1401,  1402,   631,   632,   633,    31,  1168,
    1169,   591,   592,   562,   594,   595,   596,   597,     0,    21,
      22,   562,    21,   562,    19,    27,    21,    22,    27,    24,
      31,    21,    31,   613,   614,    36,    31,    27,    22,     6,
     620,   621,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,   283,   880,    23,   882,    34,   288,   289,   355,
     356,   357,   616,   294,   295,   283,  1194,    30,    23,   287,
      33,  1199,   368,    36,   292,   225,   226,   625,   374,   625,
     376,   377,   378,   379,   380,   625,   382,   625,   384,   385,
     386,   387,   388,    37,   390,   391,   392,   393,   394,   395,
     396,   397,   398,   399,   288,   289,    32,   403,    21,   405,
     294,   295,   408,    23,    27,   411,   412,    27,    38,   415,
     416,    21,   418,   419,   951,    21,    37,    27,   424,   425,
     426,    27,   428,   429,   430,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,   442,   287,   444,   445,
     446,    19,   292,   449,   450,    21,   452,   453,   454,   455,
      40,    27,    39,    40,   460,   461,   462,   463,   464,   465,
     466,   467,   468,   469,   470,     6,    39,    40,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
     328,    34,   330,   331,   332,   333,   334,   335,   336,   337,
    1373,     6,    27,  1376,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,   530,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    34,    21,   625,    37,    20,
     286,  1643,    27,   631,    38,    16,   292,   290,   291,   225,
     222,   223,   295,    21,    22,    21,    22,    31,  1728,  1201,
    1202,   296,   297,   853,   854,   855,   284,   285,   591,   592,
      31,    22,    22,    21,    19,    19,    43,    23,    38,    22,
      38,    22,    19,    38,    33,    23,    39,    26,    20,    20,
      37,    27,    26,   573,    27,    23,   886,   887,   888,   889,
      42,    27,  1444,    32,    27,    20,  1200,   587,    33,   589,
     900,    33,   902,    20,   904,   905,   906,   907,    39,    27,
      26,    32,    42,    42,   604,   605,    27,    39,    21,   919,
     920,   611,    27,    20,    39,    39,   926,    26,    30,   619,
    1552,    27,    42,    33,    38,    33,   626,   627,   628,   629,
      21,    36,   658,   659,   634,   635,    38,    36,  1195,   923,
      40,   667,   668,   669,    38,    34,    20,    19,    19,    22,
     960,   961,   962,   963,    22,    89,    19,    22,   684,   685,
     686,   687,   688,   689,   690,   691,   692,   693,   694,   695,
     696,   697,    89,   698,   699,   700,   701,   702,   703,   704,
     705,   706,    25,    36,    38,   711,   712,   713,   714,    30,
      27,   717,    89,   719,    22,   721,   722,   723,    32,    22,
      22,    89,   728,   729,    89,    89,    22,    22,    19,   735,
     736,   737,   738,    89,   740,   741,   742,   743,    22,    37,
      22,   747,   748,   749,    22,    26,   752,   727,    22,    32,
      19,    24,    89,    89,    33,   761,    36,   763,   277,    27,
     766,    38,   768,    23,   770,    23,    33,    37,    32,    30,
      36,   777,    27,    27,    33,    23,    27,    27,    27,    32,
     786,   787,   788,   789,   790,   791,   792,   793,   794,   795,
     796,   797,   798,   799,   800,   801,   634,   803,    27,    37,
      27,   807,   808,   809,   810,    40,   812,   813,   814,   815,
      19,   816,   817,  1407,    39,    32,    30,    27,    33,    27,
      27,    33,    27,    27,    37,    27,    27,    27,    39,    32,
      27,    37,    27,    19,    23,    33,    27,    33,    23,    38,
      33,   847,    24,   849,  1134,  1135,  1136,    39,    27,    32,
      27,    20,    27,    37,    21,    23,    19,    21,    89,    21,
     698,   699,   700,   701,   702,   703,   704,   705,   706,    43,
      27,    32,    32,    19,    32,    30,    21,    33,    32,    32,
      32,    23,    23,    30,    24,    33,    30,   893,    31,    23,
      23,    22,   872,    32,    32,   875,   876,   877,   878,    89,
     880,    89,   882,  1167,   884,    32,    32,    32,    89,    89,
     890,  1175,  1176,    33,    36,   895,    89,    36,    33,    89,
      22,    38,    30,    22,    31,    22,    40,    37,    33,    23,
      23,    32,    32,   913,   914,    19,    23,    19,    89,  1203,
      30,  1205,   922,    23,  1208,    20,    23,    36,    27,    37,
      19,    23,    38,  1217,  1218,  1219,  1220,    89,    39,    89,
      23,   966,    32,    37,    23,    27,    89,   947,    36,   949,
      43,   951,    33,    23,    27,    27,    89,    37,   816,   817,
      89,    37,   820,    89,    32,   991,   992,   993,   994,    27,
      23,    89,    32,    27,    39,    21,    27,    89,    27,    27,
      23,    33,    23,  1009,    23,    27,    21,    27,    32,    36,
    1016,    89,  1018,  1019,  1020,    23,  1022,  1023,    30,    37,
      27,  1027,  1028,    89,    30,    89,    31,    23,    27,    30,
      32,  1037,    20,    36,    38,    33,    30,    22,  1044,    32,
    1046,    38,    32,    22,    31,    40,    38,    36,    32,  1055,
      36,  1057,  1058,    33,    32,    38,  1036,    38,    33,    30,
      22,    33,    32,  1069,    31,  1071,    23,    32,    36,    33,
      33,    30,  1362,    89,    30,  1081,  1082,  1083,  1084,  1085,
    1086,  1087,  1088,  1089,  1090,  1091,  1092,    33,  1094,    89,
    1096,    38,  1098,    22,    32,    30,  1102,  1103,  1104,  1105,
      40,  1107,  1108,  1109,  1110,    21,  1111,  1112,    20,    36,
      33,    37,    89,    89,    23,    89,    37,    39,  1382,    30,
      37,    36,  1386,  1387,    37,    33,   964,   965,   966,    23,
     601,   602,    21,    37,  1728,    37,    36,  1401,  1402,    36,
      39,    34,     5,    39,  1408,    23,   617,   603,    39,    23,
     606,    27,    89,  1133,    33,  1161,   612,    89,    27,    21,
      24,    89,   618,    19,   635,    36,    39,    27,    21,    89,
      38,    23,  1152,  1153,  1154,    33,  1156,  1157,  1158,    33,
      39,    22,  1162,    21,    27,    27,    23,   658,   659,    38,
     646,    39,    39,    38,    23,  1175,    19,    37,    24,    38,
      33,    89,    38,  1183,    39,    39,    38,    34,    39,    39,
      38,  1191,  1192,    38,  1194,  1195,  1196,  1197,    32,  1199,
    1200,  1201,  1202,  1203,    39,  1205,    38,    32,   747,   748,
      32,    38,  1212,  1213,  1214,  1215,    33,    33,  1244,  1245,
      27,    39,    32,    32,    39,    38,    27,    33,    39,    31,
    1256,  1257,   771,  1259,  1260,  1261,    36,    40,    34,    31,
      39,    38,    36,    21,    32,    36,    36,    31,    31,    34,
      36,    38,    34,  1111,  1112,  1113,  1281,  1282,    38,    38,
      34,    38,    19,    39,    23,  1265,    39,    32,  1552,    38,
      34,  1297,    30,    33,    24,    38,    32,    31,    33,  1305,
      32,    23,    21,    36,    32,   824,    23,    30,    39,    36,
      39,    23,    23,    39,    89,    39,  1322,    23,    38,    23,
      23,    39,    30,    39,    39,    39,    39,   846,  1334,  1335,
    1336,  1337,    39,    38,    89,    27,    38,  1175,    89,    89,
      39,    39,    38,    24,    39,    39,    23,    33,    39,    24,
      39,    33,    32,    23,    38,    38,    32,    31,    37,    32,
      27,    39,  1200,    32,    89,  1203,    31,  1205,    89,    19,
      31,    31,    38,  1379,    32,    32,   847,    22,   849,    38,
      22,  1361,    31,  1221,  1222,    38,    34,    38,    34,    30,
      33,    38,    36,    32,    22,    33,    32,  1377,    32,    39,
     871,    33,   873,   874,    31,    38,  1386,  1387,   879,    38,
      23,   867,   883,   869,   870,    27,    22,  1397,    89,    22,
    1400,  1401,  1402,    25,    38,  1405,  1406,  1407,   899,   885,
     901,    23,  1438,    89,    33,  1441,    21,    25,    38,    23,
     911,   912,    23,  1281,  1282,    38,    23,    23,    23,    23,
      33,    38,    89,    39,    89,    33,    23,    39,    89,  1465,
      32,    23,    21,    89,  1470,    89,   985,    38,   924,    38,
      38,    37,    32,    27,    27,   946,    40,   948,   934,   935,
     936,   937,   938,   939,   940,   941,   942,   943,   944,   945,
      27,    40,    27,    36,    32,    23,  1502,  1016,  1017,   955,
     956,   957,   958,  1022,    33,    32,    32,  1026,    22,    89,
      40,    22,    32,    36,    30,    40,    40,    38,    22,    38,
      32,    22,    40,    33,  1043,    38,    23,    26,    33,    32,
      22,    89,    89,    27,    40,    22,    38,  1056,  1518,    39,
      38,  1521,    38,    38,    23,  1809,    27,    23,  1386,  1387,
      27,    26,    38,    23,    27,    38,    89,    26,    43,    33,
      23,    27,    30,  1401,  1402,    27,    38,    89,    39,  1407,
      19,    27,    89,    40,  1093,    23,  1095,    27,    21,    32,
      89,    89,    28,    27,    23,    37,    27,    21,    21,    40,
      19,    21,    19,  1599,    34,    40,    89,    21,    40,    36,
      23,    33,    40,    28,    32,    27,    21,    89,    43,    40,
      36,    32,    31,    27,    32,    23,    33,    37,    23,    32,
      36,    33,    31,    27,    34,    36,  1890,    27,    23,    31,
      36,    38,    23,    32,    27,    32,    26,    38,    23,    27,
      36,    33,    24,    23,    23,    39,    19,    36,    32,    21,
      20,    38,    23,    39,    23,    19,    34,    19,    23,    34,
      37,    21,    21,  1643,    19,    32,    19,    21,    20,    32,
      21,    32,    19,    23,    40,    33,    33,    21,    34,    21,
    1151,  1687,    23,    32,  1155,    23,    89,    23,    36,    34,
      21,    89,    38,    36,  1150,  1166,  1167,  1168,  1169,    39,
      34,    31,    23,  1174,    32,    23,    89,    34,    89,    23,
      23,    34,    32,    23,    23,    23,    38,    21,    24,    34,
      39,    89,  1193,    30,    19,    37,  1182,  1198,    19,    34,
    1201,  1202,    19,  1204,    37,  1206,    38,  1256,    38,    38,
      36,  1260,    30,    19,    38,    30,    32,    27,  1728,    38,
      89,  1270,    89,  1272,    89,    33,    89,    32,    32,    36,
      33,  1280,    33,    89,  1770,    89,  1285,    34,    33,    39,
      31,    22,    89,    42,    37,    33,    36,    34,    23,    32,
      39,    33,    24,    38,    19,    34,    36,    19,    22,  1308,
      38,    27,    36,    23,    23,    36,    19,    19,    24,    30,
      33,    38,  1321,    43,    32,    19,    89,    32,  1327,    36,
    1329,  1400,    33,    33,    32,    31,    31,    36,    27,    36,
      24,    31,    24,    19,    37,    36,    33,    39,    22,    27,
      23,    23,    38,    36,    39,    43,    23,    19,    38,    19,
      23,    32,    89,    33,    32,  1851,    19,    33,    37,    23,
      31,    36,    22,    31,    38,    32,    23,    36,    27,    23,
      31,    23,    38,    38,    32,    23,    38,    23,    33,    32,
      23,  1518,    38,    24,  1406,    23,    36,    36,    23,    40,
      23,    38,    36,    38,    26,    32,    23,    39,    89,    38,
    1728,    37,    33,    22,    38,    33,    36,    36,    30,  1208,
      36,    36,  1373,  1374,  1375,  1376,    37,  1220,  1890,  1387,
    1408,  1382,  1382,   855,    -1,   625,   292,   659,   292,    -1,
    1439,  1440,    56,    -1,   633,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1392,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     292,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   297,    -1,
      -1,    -1,   297,  1444,     3,     4,     5,     6,     7,     8,
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
     219,   220,   221,   222,   297,   224,     3,     4,     5,     6,
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
     217,   218,   219,   220,   221,   297,   223,   224,     3,     4,
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
     215,   216,   217,   218,   219,   220,   221,   297,   297,   224,
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
     213,   214,   215,   216,   217,   218,   219,   220,   221,   297,
     297,   224,     3,     4,     5,     6,     7,     8,     9,    10,
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
     221,   222,   223,     3,     4,     5,     6,     7,     8,     9,
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
     220,   221,   222,   223,     3,     4,     5,     6,     7,     8,
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
     218,   219,   220,   221,   297,   297,   297,   297,   297,   297,
     297,   297,   297,   297,   293,   292,   292,   295,   292,   292,
     295,   292,    -1,    -1,    -1,   297
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     1,     3,    19,    21,    22,    24,    25,    30,    31,
      35,    36,    37,    39,   228,   229,   230,   231,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     310,   311,   312,   313,   390,   394,    22,    30,    33,    36,
      23,    27,    23,    27,    33,    19,    33,    39,    23,    23,
      39,    32,     0,   225,   226,   292,   293,     3,     4,     5,
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
     216,   217,   218,   219,   220,   221,   224,   283,   286,   287,
     288,   291,   291,   291,   291,   291,   291,   291,   291,   291,
     291,   291,   291,   291,   291,   291,   291,   291,   291,    22,
      23,    34,    23,    37,    32,    38,    37,    19,    34,    40,
      27,    31,    37,    38,    20,    31,    37,   292,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,   285,   286,
     285,   285,   285,   285,   285,   285,   285,   285,     3,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,   288,
      21,    22,    31,   232,   314,   363,   373,   375,    19,    21,
      22,    23,    24,    31,    37,    38,    40,   238,   314,   315,
     316,   317,   339,   340,   343,   348,   349,   350,   351,   352,
     353,   355,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   371,   372,   373,   374,   375,   376,   377,   383,
     384,    31,   235,   361,   236,   361,    31,   242,   362,    22,
     243,   374,   375,    22,   244,   373,   376,   245,   373,   376,
      19,    24,    31,   240,   349,   359,   371,   246,   349,   359,
     371,    19,    21,    24,    31,   252,   315,   316,   317,   348,
     355,   358,   362,   364,   372,   374,   375,    27,   247,   342,
     343,   237,   314,   363,   373,   376,    19,    23,    31,   239,
     314,   347,   352,   356,   357,   363,   371,   373,   376,   384,
     393,    19,    20,    21,    22,    24,    25,    31,    37,    38,
      40,   233,   319,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,   341,   391,   234,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,   334,   335,   336,   337,   338,   339,   341,   391,   241,
     314,    19,    43,    19,    38,    22,    38,    22,    23,    38,
      33,    23,    37,    19,    39,   286,    26,    20,    27,   291,
     291,   291,    39,    40,    26,    20,    32,    42,    27,    23,
      33,    33,   291,   291,   291,   291,   291,   291,   291,   291,
     291,   291,   291,   291,   291,   291,   291,   291,   291,   291,
     291,   291,   291,   291,   291,    27,   291,   291,    27,   291,
      20,   291,   291,    20,   291,   291,   291,   291,    39,    42,
      27,   291,   291,   291,   291,   291,   291,    39,    26,    42,
      27,   291,   291,   291,   291,    32,   291,   291,   291,   291,
     291,   291,    39,    21,    27,   291,   291,   291,   291,   291,
     291,   291,   291,   291,   291,   291,    39,    39,    26,    20,
      42,    30,    27,    38,    33,    33,   291,    36,    38,    36,
      40,    38,    21,    34,    20,    19,    89,    22,   222,   223,
     274,   290,   271,   290,    24,    32,    36,   271,   281,   309,
     380,   381,   382,    22,    19,    19,    89,    25,    89,    22,
      36,    38,    30,    27,   318,   336,   337,   338,   318,   318,
     318,   318,   318,   318,   318,   318,   318,   318,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,   262,   287,
     306,   318,   318,   318,   318,   267,   287,   318,   271,   381,
     271,   381,   318,   318,   318,    22,    32,   249,   309,   262,
      22,   262,   306,    89,    32,   271,   382,   271,   382,    89,
     271,   271,   271,   271,    22,    89,    22,   283,   283,   267,
     287,   287,   267,    22,    19,    89,    22,   262,   306,   267,
     271,   381,   271,   381,    37,   253,   273,   290,   309,   254,
     270,   283,   267,   262,   306,    24,   271,   379,   271,    22,
      26,    22,    19,    31,    37,   248,   349,   353,   354,   359,
     363,   366,   367,   368,   369,   384,   386,   387,   287,   287,
     287,   287,    32,   392,    19,    30,    31,   353,   370,   385,
     392,    22,   378,   392,   378,   392,     7,     8,   266,   284,
     285,   286,   287,   282,   283,   287,    22,    24,    19,    89,
      89,    33,    22,    37,    36,    38,    27,   267,    23,    33,
      23,    36,    37,    32,    27,    27,   283,   289,   291,   289,
      30,    33,    23,   291,   291,   291,    27,    27,    32,    27,
      27,    37,    27,    40,    19,    39,    32,   291,   291,   291,
     291,   291,   291,   291,   291,   291,   291,   291,   291,   291,
     291,    30,   291,   291,   291,   291,   291,   291,   291,   291,
     291,    27,    33,   262,   291,   291,    27,    27,    33,   291,
     291,   291,   291,    27,   291,   291,   291,   291,    27,    37,
      27,   291,   291,   291,   291,    27,    32,    37,    27,   291,
     291,    38,   291,   291,   291,    33,   291,    27,    33,    27,
      39,    27,    39,    33,   291,   291,   291,   291,   291,   291,
     291,   291,   291,   291,   291,   291,   291,   291,   291,   291,
      19,   291,    39,    23,    27,   291,   291,   291,   291,    23,
     291,   291,   291,   291,   285,   285,     6,    27,    24,    32,
      27,    37,    20,    27,    21,    23,    19,    21,    43,    27,
      21,    32,    32,    89,   222,   283,   291,   223,    19,    32,
      21,   271,   271,   271,   281,    33,    30,    32,    32,    32,
      23,    89,    23,    30,    31,    24,   267,    20,    34,   251,
     388,   389,   267,   267,   270,   287,   283,   283,   287,   287,
     287,   287,   283,   262,    30,   262,   283,   287,   267,   271,
     271,   271,   271,   287,    89,    32,   291,   263,   287,    89,
      32,    32,   279,   283,   271,   279,   271,    32,   271,   271,
     271,   271,    33,    23,    89,   250,   283,   250,   265,   287,
     269,   287,    33,    32,    23,    89,   271,   271,    36,   268,
     287,   273,   267,    36,   271,    33,    89,    22,    22,    38,
      30,   267,   267,   267,   267,   267,   267,   267,   267,   267,
     267,   267,   267,   283,   287,   283,   287,    31,   262,    22,
      40,    22,   267,   267,   267,   267,    37,   271,   271,   271,
     271,     6,     6,   285,    33,    23,    32,    32,    23,    19,
      89,    23,    19,    30,    23,    20,    36,    23,    37,    27,
      38,    89,    39,   291,   291,   291,   291,    89,    19,    23,
      37,    23,    32,    27,    36,    89,    23,    33,    43,    23,
     291,   291,   291,   291,   291,   291,   291,   291,   291,    27,
      89,   263,   291,    27,    37,    89,   291,     4,   291,   291,
      37,    89,    32,    27,   291,     4,   291,    89,    23,    32,
      27,    39,   291,   291,    21,    89,    27,    27,    27,    23,
      33,   291,   291,   291,   291,   291,   291,   291,   291,   291,
     291,   291,   291,     4,   291,     4,   291,    23,   291,    27,
      23,    27,   291,   291,   291,   291,    21,   291,   291,   291,
     291,   285,   285,    89,    36,    23,    37,    32,    30,    27,
      30,    31,    89,    89,    23,    27,    30,    38,    32,    31,
      36,    36,   268,   271,   271,   271,    33,    20,    30,    38,
      22,    32,    40,    38,    36,   267,   283,   287,   287,   287,
     283,   263,   287,   269,    32,   291,   264,   287,    32,    38,
     283,   280,   283,   290,   279,   279,    38,    33,    22,    32,
     283,     7,     8,   277,   278,   283,   284,   287,   290,   276,
     290,    33,    30,    22,    32,    31,   267,   268,    23,    33,
      32,    33,    89,   256,   287,   257,   287,   258,   283,   256,
      22,    32,   262,   307,   308,   259,   287,   260,   287,   306,
     261,   283,   256,   266,   282,   282,   277,   283,   277,   283,
     274,    33,    30,    89,   269,   269,   269,   269,    36,   290,
     272,   290,   290,   272,    33,    89,    30,    38,    22,    89,
      32,    30,    89,    40,    21,    20,    36,    37,    33,    23,
      37,   291,   291,    39,    30,    37,    36,    37,    34,    37,
      33,    23,    21,   291,   291,   291,   291,   291,    37,   264,
      37,    36,     4,    36,    39,    34,     4,     5,    39,    34,
      37,    23,   291,    39,    34,    89,    27,   291,    23,    33,
     291,     4,     4,    89,    21,   291,   291,   291,   291,    27,
      39,    24,    89,    36,    89,    27,    34,    37,    19,    21,
      33,    33,    23,    39,    38,    22,    21,    27,   268,   271,
      38,    23,    39,    39,    38,    27,    37,    23,   250,   283,
     283,   250,   264,    38,   291,    38,    39,   280,    39,    38,
      39,   277,   278,    38,    39,    38,    32,   267,    38,    39,
      33,    32,   257,    24,    32,   259,   277,   277,    33,    33,
     257,   265,   266,   276,    34,    38,    27,    21,    27,    39,
      21,    27,    32,    39,    38,    32,    33,    27,    39,    31,
      36,    19,    39,    40,    34,    89,    31,    38,    36,    21,
      32,    36,   270,    36,    31,    31,    34,    38,    34,    38,
      36,    38,    34,    38,    39,    34,    19,    23,   291,    39,
      32,   291,    38,    34,    30,    33,    32,    31,    33,    32,
      24,    38,    36,    23,    39,    21,    32,    23,    39,    30,
      36,    23,    39,    19,    23,    31,    23,    89,    39,    23,
      38,    39,   291,    39,    23,    23,    39,    89,    39,    89,
      39,    39,    89,    38,    39,    39,   260,    38,    38,   257,
      27,    39,    30,    39,    24,    23,    39,    24,    33,    89,
      39,    33,    32,    23,    38,    32,    31,    37,    38,    39,
      32,    27,    32,    22,    34,    31,    89,    19,    31,   273,
      31,    32,    32,    38,    22,    38,    22,    31,    38,    22,
      34,    34,    38,    30,    34,    36,    33,    38,    32,    33,
      32,    32,    33,    22,    31,    39,    38,    89,    38,    23,
      27,    89,    22,    25,    22,    38,    23,    36,    33,    23,
      21,    25,    23,   291,    23,    38,    38,    89,    23,    89,
      23,    23,    89,    23,    33,    39,    89,    38,    39,    33,
      32,    89,    38,    38,    38,    23,    23,    37,    21,    37,
      89,    32,    40,    21,    22,    27,    27,    27,    37,    89,
      40,    27,    36,    32,    33,    23,    32,   268,    32,    89,
      22,    40,    22,    40,    32,    21,    22,    40,    36,    38,
      21,    34,    38,    38,    30,    22,    37,    89,    40,    32,
      33,    22,    38,    23,    26,    23,    36,    33,    32,    89,
      89,    22,    27,    40,    38,    38,    39,    38,   291,    38,
      22,    23,    27,    23,    27,    38,    26,    23,    27,    38,
      89,    26,    33,    43,    89,    30,    23,    89,    21,    22,
      27,    27,    38,    39,    27,    89,    19,    40,    27,    89,
      23,    27,    28,    27,    21,    23,    89,    37,    89,    32,
     266,    27,    40,    21,    40,    21,    89,    19,    40,    21,
      21,    38,    19,    36,    34,    23,    40,    28,    33,    27,
      32,    21,    89,    32,    36,    31,    32,    27,    40,    33,
      37,    32,    33,    36,    23,    36,    34,    31,    38,   291,
      36,    27,    23,    27,    23,    31,    32,    27,    23,    26,
      43,    32,    38,    23,    36,    27,    33,    39,    36,    24,
      23,    21,    27,    31,    38,    23,    19,    32,    21,    23,
      39,    34,    20,    23,    37,    89,    19,    19,    89,    33,
      34,   255,   275,   290,   344,   345,   346,    23,    21,    21,
      19,    32,    21,    89,    19,    34,    32,    21,    20,    32,
      23,    33,    89,    33,    32,    19,    21,    34,    23,    23,
      36,    38,    39,    21,    34,    36,    34,    31,    32,    23,
     291,    21,    23,    23,    34,    23,    23,    34,    32,    23,
      23,    23,    89,    38,    21,    21,    27,    39,    24,    34,
      38,    30,    37,    89,    34,    38,    38,    19,    19,    37,
      19,    89,    36,   275,    38,    30,    89,    19,    32,    30,
      89,    27,    38,    33,    32,    32,    33,    89,    33,    89,
      34,    39,    89,    33,    36,    31,    42,    22,    37,    33,
      34,    36,    23,    21,    27,    32,    33,    39,    24,    38,
      21,    27,    36,    34,    19,    38,    22,    36,    19,    23,
      23,    27,    36,    19,    19,    30,    33,    32,    24,    36,
      32,    33,    33,    32,    43,    19,    36,    89,    36,    27,
      31,    38,    31,    37,    36,    31,    39,    24,    33,    43,
      38,    39,    24,    36,    19,    22,    27,    23,    23,    23,
      19,    38,    19,    23,    32,    33,    89,    32,    33,    19,
      31,    36,    40,    37,    38,    36,    32,    23,    31,    38,
      38,    21,    27,    38,    31,    23,    27,    23,    23,    22,
      32,    23,    23,    33,    32,    23,    38,    40,    36,    36,
      89,    38,    38,    36,    39,    24,    38,    23,    23,    37,
      26,    23,    32,    33,    23,    36,    36,    33,    36,    38,
      36,    37,    30,    22
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
#line 101 "lscp.y"
    { return LSCP_DONE; }
    break;

  case 5:
#line 102 "lscp.y"
    { return LSCP_DONE; }
    break;

  case 6:
#line 103 "lscp.y"
    { LSCPSERVER->AnswerClient((yyvsp[(1) - (1)].String)); return LSCP_DONE; }
    break;

  case 7:
#line 104 "lscp.y"
    { LSCPSERVER->AnswerClient("ERR:0:Unknown command.\r\n"); RESTART; return LSCP_SYNTAX_ERROR; }
    break;

  case 13:
#line 114 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                }
    break;

  case 14:
#line 115 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                }
    break;

  case 15:
#line 116 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                }
    break;

  case 16:
#line 117 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                }
    break;

  case 17:
#line 118 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                }
    break;

  case 18:
#line 119 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                }
    break;

  case 19:
#line 120 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                }
    break;

  case 20:
#line 121 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                }
    break;

  case 21:
#line 122 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                }
    break;

  case 22:
#line 123 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                }
    break;

  case 23:
#line 124 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                }
    break;

  case 24:
#line 125 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                }
    break;

  case 25:
#line 126 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                }
    break;

  case 26:
#line 127 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                }
    break;

  case 27:
#line 128 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                }
    break;

  case 28:
#line 129 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                }
    break;

  case 29:
#line 130 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                }
    break;

  case 30:
#line 131 "lscp.y"
    { (yyval.String) = LSCPSERVER->ResetSampler();                        }
    break;

  case 31:
#line 132 "lscp.y"
    { LSCPSERVER->AnswerClient("Bye!\r\n"); return LSCP_QUIT; }
    break;

  case 32:
#line 135 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddChannel();                          }
    break;

  case 33:
#line 136 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddDbInstrumentDirectory((yyvsp[(3) - (3)].String));          }
    break;

  case 34:
#line 137 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddDbInstruments((yyvsp[(5) - (9)].String),(yyvsp[(7) - (9)].String),(yyvsp[(9) - (9)].String), true);  }
    break;

  case 35:
#line 138 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddDbInstruments((yyvsp[(3) - (7)].String),(yyvsp[(5) - (7)].String),(yyvsp[(7) - (7)].String));        }
    break;

  case 36:
#line 139 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddDbInstruments((yyvsp[(5) - (7)].String),(yyvsp[(7) - (7)].String), -1, true); }
    break;

  case 37:
#line 140 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddDbInstruments((yyvsp[(5) - (9)].String),(yyvsp[(7) - (9)].String),(yyvsp[(9) - (9)].Number), true);  }
    break;

  case 38:
#line 141 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddDbInstruments((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].String));           }
    break;

  case 39:
#line 142 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddDbInstruments((yyvsp[(3) - (7)].String),(yyvsp[(5) - (7)].String),(yyvsp[(7) - (7)].Number));        }
    break;

  case 40:
#line 143 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddMidiInstrumentMap();                }
    break;

  case 41:
#line 144 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddMidiInstrumentMap((yyvsp[(3) - (3)].String));              }
    break;

  case 42:
#line 147 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_audio_device_count);   }
    break;

  case 43:
#line 148 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_audio_device_info);    }
    break;

  case 44:
#line 149 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_device_count);    }
    break;

  case 45:
#line 150 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_device_info);     }
    break;

  case 46:
#line 151 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_channel_count);        }
    break;

  case 47:
#line 152 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_voice_count);          }
    break;

  case 48:
#line 153 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_stream_count);         }
    break;

  case 49:
#line 154 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_buffer_fill);          }
    break;

  case 50:
#line 155 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_channel_info);         }
    break;

  case 51:
#line 156 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_fx_send_count);        }
    break;

  case 52:
#line 157 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_fx_send_info);         }
    break;

  case 53:
#line 158 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_instr_map_count); }
    break;

  case 54:
#line 159 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_instr_map_info);  }
    break;

  case 55:
#line 160 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_instr_count);     }
    break;

  case 56:
#line 161 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_instr_info);      }
    break;

  case 57:
#line 162 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_db_instr_dir_count);   }
    break;

  case 58:
#line 163 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_db_instr_dir_info);    }
    break;

  case 59:
#line 164 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_db_instr_count);       }
    break;

  case 60:
#line 165 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_db_instr_info);        }
    break;

  case 61:
#line 166 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_db_instrs_job_info);   }
    break;

  case 62:
#line 167 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_misc);                 }
    break;

  case 63:
#line 168 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_total_voice_count);    }
    break;

  case 64:
#line 169 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_global_info);          }
    break;

  case 65:
#line 172 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_audio_device_count);   }
    break;

  case 66:
#line 173 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_audio_device_info);    }
    break;

  case 67:
#line 174 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_device_count);    }
    break;

  case 68:
#line 175 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_device_info);     }
    break;

  case 69:
#line 176 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_channel_count);        }
    break;

  case 70:
#line 177 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_voice_count);          }
    break;

  case 71:
#line 178 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_stream_count);         }
    break;

  case 72:
#line 179 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_buffer_fill);          }
    break;

  case 73:
#line 180 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_channel_info);         }
    break;

  case 74:
#line 181 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_fx_send_count);        }
    break;

  case 75:
#line 182 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_fx_send_info);         }
    break;

  case 76:
#line 183 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_instr_map_count); }
    break;

  case 77:
#line 184 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_instr_map_info);  }
    break;

  case 78:
#line 185 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_instr_count);     }
    break;

  case 79:
#line 186 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_instr_info);      }
    break;

  case 80:
#line 187 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_db_instr_dir_count);   }
    break;

  case 81:
#line 188 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_db_instr_dir_info);    }
    break;

  case 82:
#line 189 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_db_instr_count);       }
    break;

  case 83:
#line 190 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_db_instr_info);        }
    break;

  case 84:
#line 191 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_db_instrs_job_info);   }
    break;

  case 85:
#line 192 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_misc);                 }
    break;

  case 86:
#line 193 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_total_voice_count);    }
    break;

  case 87:
#line 194 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_global_info);          }
    break;

  case 88:
#line 197 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping((yyvsp[(4) - (16)].Number),(yyvsp[(6) - (16)].Number),(yyvsp[(8) - (16)].Number),(yyvsp[(10) - (16)].String),(yyvsp[(12) - (16)].String),(yyvsp[(14) - (16)].Number),(yyvsp[(16) - (16)].Dotnum),MidiInstrumentMapper::VOID,"",(yyvsp[(3) - (16)].Bool)); }
    break;

  case 89:
#line 198 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping((yyvsp[(4) - (18)].Number),(yyvsp[(6) - (18)].Number),(yyvsp[(8) - (18)].Number),(yyvsp[(10) - (18)].String),(yyvsp[(12) - (18)].String),(yyvsp[(14) - (18)].Number),(yyvsp[(16) - (18)].Dotnum),(yyvsp[(18) - (18)].LoadMode),"",(yyvsp[(3) - (18)].Bool)); }
    break;

  case 90:
#line 199 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping((yyvsp[(4) - (18)].Number),(yyvsp[(6) - (18)].Number),(yyvsp[(8) - (18)].Number),(yyvsp[(10) - (18)].String),(yyvsp[(12) - (18)].String),(yyvsp[(14) - (18)].Number),(yyvsp[(16) - (18)].Dotnum),MidiInstrumentMapper::VOID,(yyvsp[(18) - (18)].String),(yyvsp[(3) - (18)].Bool)); }
    break;

  case 91:
#line 200 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping((yyvsp[(4) - (20)].Number),(yyvsp[(6) - (20)].Number),(yyvsp[(8) - (20)].Number),(yyvsp[(10) - (20)].String),(yyvsp[(12) - (20)].String),(yyvsp[(14) - (20)].Number),(yyvsp[(16) - (20)].Dotnum),(yyvsp[(18) - (20)].LoadMode),(yyvsp[(20) - (20)].String),(yyvsp[(3) - (20)].Bool)); }
    break;

  case 92:
#line 203 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveMIDIInstrumentMapping((yyvsp[(3) - (7)].Number),(yyvsp[(5) - (7)].Number),(yyvsp[(7) - (7)].Number)); }
    break;

  case 93:
#line 206 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveChannel((yyvsp[(3) - (3)].Number));                     }
    break;

  case 94:
#line 207 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveMidiInstrumentMap((yyvsp[(3) - (3)].Number));           }
    break;

  case 95:
#line 208 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveAllMidiInstrumentMaps();         }
    break;

  case 96:
#line 209 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveDbInstrumentDirectory((yyvsp[(5) - (5)].String), true); }
    break;

  case 97:
#line 210 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveDbInstrumentDirectory((yyvsp[(3) - (3)].String));       }
    break;

  case 98:
#line 211 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveDbInstrument((yyvsp[(3) - (3)].String));                }
    break;

  case 99:
#line 214 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAvailableEngines();                          }
    break;

  case 100:
#line 215 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAvailableMidiInputDrivers();                 }
    break;

  case 101:
#line 216 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDriverInfo((yyvsp[(5) - (5)].String));                     }
    break;

  case 102:
#line 217 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDriverParameterInfo((yyvsp[(5) - (7)].String), (yyvsp[(7) - (7)].String));        }
    break;

  case 103:
#line 218 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDriverParameterInfo((yyvsp[(5) - (9)].String), (yyvsp[(7) - (9)].String), (yyvsp[(9) - (9)].KeyValList));    }
    break;

  case 104:
#line 219 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAvailableAudioOutputDrivers();               }
    break;

  case 105:
#line 220 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDriverInfo((yyvsp[(5) - (5)].String));                   }
    break;

  case 106:
#line 221 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDriverParameterInfo((yyvsp[(5) - (7)].String), (yyvsp[(7) - (7)].String));      }
    break;

  case 107:
#line 222 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDriverParameterInfo((yyvsp[(5) - (9)].String), (yyvsp[(7) - (9)].String), (yyvsp[(9) - (9)].KeyValList));  }
    break;

  case 108:
#line 223 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDeviceCount();                    }
    break;

  case 109:
#line 224 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDeviceCount();                      }
    break;

  case 110:
#line 225 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDeviceInfo((yyvsp[(5) - (5)].Number));                   }
    break;

  case 111:
#line 226 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDeviceInfo((yyvsp[(5) - (5)].Number));                     }
    break;

  case 112:
#line 227 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputPortInfo((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number));                   }
    break;

  case 113:
#line 228 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputPortParameterInfo((yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].Number), (yyvsp[(9) - (9)].String));      }
    break;

  case 114:
#line 229 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputChannelInfo((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number));              }
    break;

  case 115:
#line 230 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputChannelParameterInfo((yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].Number), (yyvsp[(9) - (9)].String)); }
    break;

  case 116:
#line 231 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetChannels();                                  }
    break;

  case 117:
#line 232 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetChannelInfo((yyvsp[(5) - (5)].Number));                             }
    break;

  case 118:
#line 233 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetBufferFill((yyvsp[(5) - (7)].FillResponse), (yyvsp[(7) - (7)].Number));                          }
    break;

  case 119:
#line 234 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetStreamCount((yyvsp[(5) - (5)].Number));                             }
    break;

  case 120:
#line 235 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetVoiceCount((yyvsp[(5) - (5)].Number));                              }
    break;

  case 121:
#line 236 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetEngineInfo((yyvsp[(5) - (5)].String));                              }
    break;

  case 122:
#line 237 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetServerInfo();                                }
    break;

  case 123:
#line 238 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetTotalVoiceCount();                           }
    break;

  case 124:
#line 239 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetTotalVoiceCountMax();                        }
    break;

  case 125:
#line 240 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInstrumentMappings((yyvsp[(3) - (3)].Number));                  }
    break;

  case 126:
#line 241 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAllMidiInstrumentMappings();                 }
    break;

  case 127:
#line 242 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInstrumentMapping((yyvsp[(5) - (9)].Number),(yyvsp[(7) - (9)].Number),(yyvsp[(9) - (9)].Number));             }
    break;

  case 128:
#line 243 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInstrumentMaps();                        }
    break;

  case 129:
#line 244 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInstrumentMap((yyvsp[(5) - (5)].Number));                       }
    break;

  case 130:
#line 245 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetFxSends((yyvsp[(3) - (3)].Number));                                 }
    break;

  case 131:
#line 246 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetFxSendInfo((yyvsp[(5) - (7)].Number),(yyvsp[(7) - (7)].Number));                           }
    break;

  case 132:
#line 247 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetDbInstrumentDirectoryCount((yyvsp[(5) - (5)].String), true);        }
    break;

  case 133:
#line 248 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetDbInstrumentDirectoryCount((yyvsp[(3) - (3)].String), false);       }
    break;

  case 134:
#line 249 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetDbInstrumentDirectoryInfo((yyvsp[(5) - (5)].String));               }
    break;

  case 135:
#line 250 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetDbInstrumentCount((yyvsp[(5) - (5)].String), true);                 }
    break;

  case 136:
#line 251 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetDbInstrumentCount((yyvsp[(3) - (3)].String), false);                }
    break;

  case 137:
#line 252 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetDbInstrumentInfo((yyvsp[(5) - (5)].String));                        }
    break;

  case 138:
#line 253 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetDbInstrumentsJobInfo((yyvsp[(5) - (5)].Number));                    }
    break;

  case 139:
#line 254 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetGlobalVolume();                              }
    break;

  case 140:
#line 257 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputDeviceParameter((yyvsp[(3) - (7)].Number), (yyvsp[(5) - (7)].String), (yyvsp[(7) - (7)].String));      }
    break;

  case 141:
#line 258 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputChannelParameter((yyvsp[(3) - (9)].Number), (yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].String), (yyvsp[(9) - (9)].String)); }
    break;

  case 142:
#line 259 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMidiInputDeviceParameter((yyvsp[(3) - (7)].Number), (yyvsp[(5) - (7)].String), (yyvsp[(7) - (7)].String));        }
    break;

  case 143:
#line 260 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMidiInputPortParameter((yyvsp[(3) - (9)].Number), (yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].String), (yyvsp[(9) - (9)].String));      }
    break;

  case 144:
#line 261 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                         }
    break;

  case 145:
#line 262 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMidiInstrumentMapName((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].String));               }
    break;

  case 146:
#line 263 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetFxSendName((yyvsp[(5) - (9)].Number),(yyvsp[(7) - (9)].Number),(yyvsp[(9) - (9)].String));                        }
    break;

  case 147:
#line 264 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetFxSendAudioOutputChannel((yyvsp[(5) - (11)].Number),(yyvsp[(7) - (11)].Number),(yyvsp[(9) - (11)].Number),(yyvsp[(11) - (11)].Number)); }
    break;

  case 148:
#line 265 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetFxSendMidiController((yyvsp[(5) - (9)].Number),(yyvsp[(7) - (9)].Number),(yyvsp[(9) - (9)].Number));              }
    break;

  case 149:
#line 266 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetFxSendLevel((yyvsp[(5) - (9)].Number),(yyvsp[(7) - (9)].Number),(yyvsp[(9) - (9)].Dotnum));                       }
    break;

  case 150:
#line 267 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetDbInstrumentDirectoryName((yyvsp[(5) - (7)].String),(yyvsp[(7) - (7)].String));            }
    break;

  case 151:
#line 268 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetDbInstrumentDirectoryDescription((yyvsp[(5) - (7)].String),(yyvsp[(7) - (7)].String));     }
    break;

  case 152:
#line 269 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetDbInstrumentName((yyvsp[(5) - (7)].String),(yyvsp[(7) - (7)].String));                     }
    break;

  case 153:
#line 270 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetDbInstrumentDescription((yyvsp[(5) - (7)].String),(yyvsp[(7) - (7)].String));              }
    break;

  case 154:
#line 271 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetEcho((yyparse_param_t*) yyparse_param, (yyvsp[(3) - (3)].Dotnum));  }
    break;

  case 155:
#line 272 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetGlobalVolume((yyvsp[(3) - (3)].Dotnum));                            }
    break;

  case 156:
#line 275 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateAudioOutputDevice((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].KeyValList)); }
    break;

  case 157:
#line 276 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateAudioOutputDevice((yyvsp[(3) - (3)].String));    }
    break;

  case 158:
#line 277 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateMidiInputDevice((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].KeyValList));   }
    break;

  case 159:
#line 278 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateMidiInputDevice((yyvsp[(3) - (3)].String));      }
    break;

  case 160:
#line 279 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateFxSend((yyvsp[(3) - (5)].Number),(yyvsp[(5) - (5)].Number));            }
    break;

  case 161:
#line 280 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateFxSend((yyvsp[(3) - (7)].Number),(yyvsp[(5) - (7)].Number),(yyvsp[(7) - (7)].String)); }
    break;

  case 162:
#line 283 "lscp.y"
    { (yyval.String) = LSCPSERVER->ResetChannel((yyvsp[(3) - (3)].Number)); }
    break;

  case 163:
#line 286 "lscp.y"
    { (yyval.String) = LSCPSERVER->ClearMidiInstrumentMappings((yyvsp[(3) - (3)].Number));  }
    break;

  case 164:
#line 287 "lscp.y"
    { (yyval.String) = LSCPSERVER->ClearAllMidiInstrumentMappings(); }
    break;

  case 165:
#line 290 "lscp.y"
    { (yyval.String) = LSCPSERVER->FindDbInstruments((yyvsp[(5) - (7)].String),(yyvsp[(7) - (7)].KeyValList), false);           }
    break;

  case 166:
#line 291 "lscp.y"
    { (yyval.String) = LSCPSERVER->FindDbInstruments((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].KeyValList), true);            }
    break;

  case 167:
#line 292 "lscp.y"
    { (yyval.String) = LSCPSERVER->FindDbInstrumentDirectories((yyvsp[(5) - (7)].String),(yyvsp[(7) - (7)].KeyValList), false); }
    break;

  case 168:
#line 293 "lscp.y"
    { (yyval.String) = LSCPSERVER->FindDbInstrumentDirectories((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].KeyValList), true);  }
    break;

  case 169:
#line 296 "lscp.y"
    { (yyval.String) = LSCPSERVER->MoveDbInstrumentDirectory((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].String)); }
    break;

  case 170:
#line 297 "lscp.y"
    { (yyval.String) = LSCPSERVER->MoveDbInstrument((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].String));          }
    break;

  case 171:
#line 300 "lscp.y"
    { (yyval.String) = LSCPSERVER->CopyDbInstrumentDirectory((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].String)); }
    break;

  case 172:
#line 301 "lscp.y"
    { (yyval.String) = LSCPSERVER->CopyDbInstrument((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].String));          }
    break;

  case 173:
#line 304 "lscp.y"
    { (yyval.String) = LSCPSERVER->DestroyAudioOutputDevice((yyvsp[(3) - (3)].Number)); }
    break;

  case 174:
#line 305 "lscp.y"
    { (yyval.String) = LSCPSERVER->DestroyMidiInputDevice((yyvsp[(3) - (3)].Number));   }
    break;

  case 175:
#line 306 "lscp.y"
    { (yyval.String) = LSCPSERVER->DestroyFxSend((yyvsp[(3) - (5)].Number),(yyvsp[(5) - (5)].Number)); }
    break;

  case 176:
#line 309 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String); }
    break;

  case 177:
#line 310 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String); }
    break;

  case 178:
#line 313 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputDevice((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));      }
    break;

  case 179:
#line 314 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputChannel((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number), (yyvsp[(3) - (7)].Number)); }
    break;

  case 180:
#line 315 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputType((yyvsp[(5) - (5)].String), (yyvsp[(3) - (5)].Number));        }
    break;

  case 181:
#line 316 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInput((yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].Number), (yyvsp[(9) - (9)].Number), (yyvsp[(3) - (9)].Number));      }
    break;

  case 182:
#line 317 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputDevice((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));        }
    break;

  case 183:
#line 318 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputPort((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));          }
    break;

  case 184:
#line 319 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputChannel((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));       }
    break;

  case 185:
#line 320 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputType((yyvsp[(5) - (5)].String), (yyvsp[(3) - (5)].Number));          }
    break;

  case 186:
#line 321 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetVolume((yyvsp[(5) - (5)].Dotnum), (yyvsp[(3) - (5)].Number));                 }
    break;

  case 187:
#line 322 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMute((yyvsp[(5) - (5)].Dotnum), (yyvsp[(3) - (5)].Number));            }
    break;

  case 188:
#line 323 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelSolo((yyvsp[(5) - (5)].Dotnum), (yyvsp[(3) - (5)].Number));            }
    break;

  case 189:
#line 324 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMap((yyvsp[(3) - (5)].Number), (yyvsp[(5) - (5)].Number));             }
    break;

  case 190:
#line 325 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMap((yyvsp[(3) - (5)].Number), -1);             }
    break;

  case 191:
#line 326 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMap((yyvsp[(3) - (5)].Number), -2);             }
    break;

  case 192:
#line 329 "lscp.y"
    { (yyval.Bool) = true;  }
    break;

  case 193:
#line 330 "lscp.y"
    { (yyval.Bool) = false; }
    break;

  case 194:
#line 333 "lscp.y"
    { (yyval.KeyValList)[(yyvsp[(1) - (3)].String)] = (yyvsp[(3) - (3)].String);          }
    break;

  case 195:
#line 334 "lscp.y"
    { (yyval.KeyValList) = (yyvsp[(1) - (5)].KeyValList); (yyval.KeyValList)[(yyvsp[(3) - (5)].String)] = (yyvsp[(5) - (5)].String); }
    break;

  case 196:
#line 337 "lscp.y"
    { (yyval.FillResponse) = fill_response_bytes;      }
    break;

  case 197:
#line 338 "lscp.y"
    { (yyval.FillResponse) = fill_response_percentage; }
    break;

  case 198:
#line 341 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDevices();              }
    break;

  case 199:
#line 342 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDevices();                }
    break;

  case 200:
#line 343 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListChannels();                       }
    break;

  case 201:
#line 344 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableEngines();               }
    break;

  case 202:
#line 345 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableMidiInputDrivers();      }
    break;

  case 203:
#line 346 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableAudioOutputDrivers();    }
    break;

  case 204:
#line 347 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListMidiInstrumentMappings((yyvsp[(3) - (3)].Number));       }
    break;

  case 205:
#line 348 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAllMidiInstrumentMappings();      }
    break;

  case 206:
#line 349 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListMidiInstrumentMaps();             }
    break;

  case 207:
#line 350 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListFxSends((yyvsp[(3) - (3)].Number));                      }
    break;

  case 208:
#line 351 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetDbInstrumentDirectories((yyvsp[(5) - (5)].String), true); }
    break;

  case 209:
#line 352 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetDbInstrumentDirectories((yyvsp[(3) - (3)].String));       }
    break;

  case 210:
#line 353 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetDbInstruments((yyvsp[(5) - (5)].String), true);           }
    break;

  case 211:
#line 354 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetDbInstruments((yyvsp[(3) - (3)].String));                 }
    break;

  case 212:
#line 357 "lscp.y"
    { (yyval.String) = LSCPSERVER->LoadInstrument((yyvsp[(1) - (5)].String), (yyvsp[(3) - (5)].Number), (yyvsp[(5) - (5)].Number));       }
    break;

  case 213:
#line 358 "lscp.y"
    { (yyval.String) = LSCPSERVER->LoadInstrument((yyvsp[(3) - (7)].String), (yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number), true); }
    break;

  case 214:
#line 361 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetEngineType((yyvsp[(1) - (3)].String), (yyvsp[(3) - (3)].Number)); }
    break;

  case 215:
#line 364 "lscp.y"
    { (yyval.LoadMode) = MidiInstrumentMapper::ON_DEMAND;      }
    break;

  case 216:
#line 365 "lscp.y"
    { (yyval.LoadMode) = MidiInstrumentMapper::ON_DEMAND_HOLD; }
    break;

  case 217:
#line 366 "lscp.y"
    { (yyval.LoadMode) = MidiInstrumentMapper::PERSISTENT;     }
    break;

  case 223:
#line 382 "lscp.y"
    { (yyval.Number) = 16; }
    break;

  case 230:
#line 401 "lscp.y"
    { (yyval.Dotnum) = (yyvsp[(1) - (1)].Number); }
    break;

  case 242:
#line 435 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (3)].String) + "," + (yyvsp[(3) - (3)].String); }
    break;

  case 245:
#line 440 "lscp.y"
    { std::stringstream ss; ss << "\'" << (yyvsp[(1) - (1)].Number) << "\'"; (yyval.String) = ss.str(); }
    break;

  case 246:
#line 441 "lscp.y"
    { std::stringstream ss; ss << "\'" << (yyvsp[(1) - (1)].Dotnum) << "\'"; (yyval.String) = ss.str(); }
    break;

  case 247:
#line 444 "lscp.y"
    { (yyval.KeyValList)[(yyvsp[(1) - (3)].String)] = (yyvsp[(3) - (3)].String);          }
    break;

  case 248:
#line 445 "lscp.y"
    { (yyval.KeyValList) = (yyvsp[(1) - (5)].KeyValList); (yyval.KeyValList)[(yyvsp[(3) - (5)].String)] = (yyvsp[(5) - (5)].String); }
    break;

  case 251:
#line 452 "lscp.y"
    { (yyval.String) = "RECURSIVE"; }
    break;

  case 252:
#line 453 "lscp.y"
    { (yyval.String) = "NON_RECURSIVE"; }
    break;

  case 253:
#line 454 "lscp.y"
    { (yyval.String) = "FLAT"; }
    break;

  case 254:
#line 462 "lscp.y"
    { (yyval.Dotnum) = (yyvsp[(1) - (1)].Number); }
    break;

  case 255:
#line 463 "lscp.y"
    { (yyval.Dotnum) = -1; }
    break;

  case 256:
#line 466 "lscp.y"
    { std::string s; s = (yyvsp[(1) - (1)].Char); (yyval.String) = s; }
    break;

  case 257:
#line 467 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + (yyvsp[(2) - (2)].Char);                  }
    break;

  case 258:
#line 470 "lscp.y"
    { (yyval.Dotnum) = atof(String((yyvsp[(1) - (3)].String) + "." + (yyvsp[(3) - (3)].String)).c_str());                         }
    break;

  case 259:
#line 471 "lscp.y"
    { String s = "+"; s += (yyvsp[(2) - (4)].String); s += "."; s += (yyvsp[(4) - (4)].String); (yyval.Dotnum) = atof(s.c_str()); }
    break;

  case 260:
#line 472 "lscp.y"
    { (yyval.Dotnum) = atof(String("-" + (yyvsp[(2) - (4)].String) + "." + (yyvsp[(4) - (4)].String)).c_str());                   }
    break;

  case 261:
#line 476 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (1)].Char);      }
    break;

  case 262:
#line 477 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + (yyvsp[(2) - (2)].Char); }
    break;

  case 263:
#line 480 "lscp.y"
    { (yyval.Char) = '0'; }
    break;

  case 264:
#line 481 "lscp.y"
    { (yyval.Char) = '1'; }
    break;

  case 265:
#line 482 "lscp.y"
    { (yyval.Char) = '2'; }
    break;

  case 266:
#line 483 "lscp.y"
    { (yyval.Char) = '3'; }
    break;

  case 267:
#line 484 "lscp.y"
    { (yyval.Char) = '4'; }
    break;

  case 268:
#line 485 "lscp.y"
    { (yyval.Char) = '5'; }
    break;

  case 269:
#line 486 "lscp.y"
    { (yyval.Char) = '6'; }
    break;

  case 270:
#line 487 "lscp.y"
    { (yyval.Char) = '7'; }
    break;

  case 271:
#line 488 "lscp.y"
    { (yyval.Char) = '8'; }
    break;

  case 272:
#line 489 "lscp.y"
    { (yyval.Char) = '9'; }
    break;

  case 273:
#line 492 "lscp.y"
    { (yyval.Number) = atoi(String(1, (yyvsp[(1) - (1)].Char)).c_str());      }
    break;

  case 274:
#line 493 "lscp.y"
    { (yyval.Number) = atoi(String(String("1") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 275:
#line 494 "lscp.y"
    { (yyval.Number) = atoi(String(String("2") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 276:
#line 495 "lscp.y"
    { (yyval.Number) = atoi(String(String("3") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 277:
#line 496 "lscp.y"
    { (yyval.Number) = atoi(String(String("4") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 278:
#line 497 "lscp.y"
    { (yyval.Number) = atoi(String(String("5") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 279:
#line 498 "lscp.y"
    { (yyval.Number) = atoi(String(String("6") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 280:
#line 499 "lscp.y"
    { (yyval.Number) = atoi(String(String("7") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 281:
#line 500 "lscp.y"
    { (yyval.Number) = atoi(String(String("8") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 282:
#line 501 "lscp.y"
    { (yyval.Number) = atoi(String(String("9") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 283:
#line 503 "lscp.y"
    { (yyval.Char) = 'A'; }
    break;

  case 284:
#line 503 "lscp.y"
    { (yyval.Char) = 'B'; }
    break;

  case 285:
#line 503 "lscp.y"
    { (yyval.Char) = 'C'; }
    break;

  case 286:
#line 503 "lscp.y"
    { (yyval.Char) = 'D'; }
    break;

  case 287:
#line 503 "lscp.y"
    { (yyval.Char) = 'E'; }
    break;

  case 288:
#line 503 "lscp.y"
    { (yyval.Char) = 'F'; }
    break;

  case 289:
#line 503 "lscp.y"
    { (yyval.Char) = 'G'; }
    break;

  case 290:
#line 503 "lscp.y"
    { (yyval.Char) = 'H'; }
    break;

  case 291:
#line 503 "lscp.y"
    { (yyval.Char) = 'I'; }
    break;

  case 292:
#line 503 "lscp.y"
    { (yyval.Char) = 'J'; }
    break;

  case 293:
#line 503 "lscp.y"
    { (yyval.Char) = 'K'; }
    break;

  case 294:
#line 503 "lscp.y"
    { (yyval.Char) = 'L'; }
    break;

  case 295:
#line 503 "lscp.y"
    { (yyval.Char) = 'M'; }
    break;

  case 296:
#line 503 "lscp.y"
    { (yyval.Char) = 'N'; }
    break;

  case 297:
#line 503 "lscp.y"
    { (yyval.Char) = 'O'; }
    break;

  case 298:
#line 503 "lscp.y"
    { (yyval.Char) = 'P'; }
    break;

  case 299:
#line 503 "lscp.y"
    { (yyval.Char) = 'Q'; }
    break;

  case 300:
#line 503 "lscp.y"
    { (yyval.Char) = 'R'; }
    break;

  case 301:
#line 503 "lscp.y"
    { (yyval.Char) = 'S'; }
    break;

  case 302:
#line 503 "lscp.y"
    { (yyval.Char) = 'T'; }
    break;

  case 303:
#line 503 "lscp.y"
    { (yyval.Char) = 'U'; }
    break;

  case 304:
#line 503 "lscp.y"
    { (yyval.Char) = 'V'; }
    break;

  case 305:
#line 503 "lscp.y"
    { (yyval.Char) = 'W'; }
    break;

  case 306:
#line 503 "lscp.y"
    { (yyval.Char) = 'X'; }
    break;

  case 307:
#line 503 "lscp.y"
    { (yyval.Char) = 'Y'; }
    break;

  case 308:
#line 503 "lscp.y"
    { (yyval.Char) = 'Z'; }
    break;

  case 309:
#line 504 "lscp.y"
    { (yyval.Char) = 'a'; }
    break;

  case 310:
#line 504 "lscp.y"
    { (yyval.Char) = 'b'; }
    break;

  case 311:
#line 504 "lscp.y"
    { (yyval.Char) = 'c'; }
    break;

  case 312:
#line 504 "lscp.y"
    { (yyval.Char) = 'd'; }
    break;

  case 313:
#line 504 "lscp.y"
    { (yyval.Char) = 'e'; }
    break;

  case 314:
#line 504 "lscp.y"
    { (yyval.Char) = 'f'; }
    break;

  case 315:
#line 504 "lscp.y"
    { (yyval.Char) = 'g'; }
    break;

  case 316:
#line 504 "lscp.y"
    { (yyval.Char) = 'h'; }
    break;

  case 317:
#line 504 "lscp.y"
    { (yyval.Char) = 'i'; }
    break;

  case 318:
#line 504 "lscp.y"
    { (yyval.Char) = 'j'; }
    break;

  case 319:
#line 504 "lscp.y"
    { (yyval.Char) = 'k'; }
    break;

  case 320:
#line 504 "lscp.y"
    { (yyval.Char) = 'l'; }
    break;

  case 321:
#line 504 "lscp.y"
    { (yyval.Char) = 'm'; }
    break;

  case 322:
#line 504 "lscp.y"
    { (yyval.Char) = 'n'; }
    break;

  case 323:
#line 504 "lscp.y"
    { (yyval.Char) = 'o'; }
    break;

  case 324:
#line 504 "lscp.y"
    { (yyval.Char) = 'p'; }
    break;

  case 325:
#line 504 "lscp.y"
    { (yyval.Char) = 'q'; }
    break;

  case 326:
#line 504 "lscp.y"
    { (yyval.Char) = 'r'; }
    break;

  case 327:
#line 504 "lscp.y"
    { (yyval.Char) = 's'; }
    break;

  case 328:
#line 504 "lscp.y"
    { (yyval.Char) = 't'; }
    break;

  case 329:
#line 504 "lscp.y"
    { (yyval.Char) = 'u'; }
    break;

  case 330:
#line 504 "lscp.y"
    { (yyval.Char) = 'v'; }
    break;

  case 331:
#line 504 "lscp.y"
    { (yyval.Char) = 'w'; }
    break;

  case 332:
#line 504 "lscp.y"
    { (yyval.Char) = 'x'; }
    break;

  case 333:
#line 504 "lscp.y"
    { (yyval.Char) = 'y'; }
    break;

  case 334:
#line 504 "lscp.y"
    { (yyval.Char) = 'z'; }
    break;

  case 335:
#line 505 "lscp.y"
    { (yyval.Char) = '0'; }
    break;

  case 336:
#line 505 "lscp.y"
    { (yyval.Char) = '1'; }
    break;

  case 337:
#line 505 "lscp.y"
    { (yyval.Char) = '2'; }
    break;

  case 338:
#line 505 "lscp.y"
    { (yyval.Char) = '3'; }
    break;

  case 339:
#line 505 "lscp.y"
    { (yyval.Char) = '4'; }
    break;

  case 340:
#line 505 "lscp.y"
    { (yyval.Char) = '5'; }
    break;

  case 341:
#line 505 "lscp.y"
    { (yyval.Char) = '6'; }
    break;

  case 342:
#line 505 "lscp.y"
    { (yyval.Char) = '7'; }
    break;

  case 343:
#line 505 "lscp.y"
    { (yyval.Char) = '8'; }
    break;

  case 344:
#line 505 "lscp.y"
    { (yyval.Char) = '9'; }
    break;

  case 345:
#line 506 "lscp.y"
    { (yyval.Char) = '!'; }
    break;

  case 346:
#line 506 "lscp.y"
    { (yyval.Char) = '#'; }
    break;

  case 347:
#line 506 "lscp.y"
    { (yyval.Char) = '$'; }
    break;

  case 348:
#line 506 "lscp.y"
    { (yyval.Char) = '%'; }
    break;

  case 349:
#line 506 "lscp.y"
    { (yyval.Char) = '&'; }
    break;

  case 350:
#line 506 "lscp.y"
    { (yyval.Char) = '('; }
    break;

  case 351:
#line 506 "lscp.y"
    { (yyval.Char) = ')'; }
    break;

  case 352:
#line 506 "lscp.y"
    { (yyval.Char) = '*'; }
    break;

  case 353:
#line 506 "lscp.y"
    { (yyval.Char) = '+'; }
    break;

  case 354:
#line 506 "lscp.y"
    { (yyval.Char) = '-'; }
    break;

  case 355:
#line 506 "lscp.y"
    { (yyval.Char) = '.'; }
    break;

  case 356:
#line 506 "lscp.y"
    { (yyval.Char) = ','; }
    break;

  case 357:
#line 506 "lscp.y"
    { (yyval.Char) = '/'; }
    break;

  case 358:
#line 507 "lscp.y"
    { (yyval.Char) = ':'; }
    break;

  case 359:
#line 507 "lscp.y"
    { (yyval.Char) = ';'; }
    break;

  case 360:
#line 507 "lscp.y"
    { (yyval.Char) = '<'; }
    break;

  case 361:
#line 507 "lscp.y"
    { (yyval.Char) = '='; }
    break;

  case 362:
#line 507 "lscp.y"
    { (yyval.Char) = '>'; }
    break;

  case 363:
#line 507 "lscp.y"
    { (yyval.Char) = '?'; }
    break;

  case 364:
#line 507 "lscp.y"
    { (yyval.Char) = '@'; }
    break;

  case 365:
#line 508 "lscp.y"
    { (yyval.Char) = '['; }
    break;

  case 366:
#line 508 "lscp.y"
    { (yyval.Char) = '\\'; }
    break;

  case 367:
#line 508 "lscp.y"
    { (yyval.Char) = ']'; }
    break;

  case 368:
#line 508 "lscp.y"
    { (yyval.Char) = '^'; }
    break;

  case 369:
#line 508 "lscp.y"
    { (yyval.Char) = '_'; }
    break;

  case 370:
#line 509 "lscp.y"
    { (yyval.Char) = '{'; }
    break;

  case 371:
#line 509 "lscp.y"
    { (yyval.Char) = '|'; }
    break;

  case 372:
#line 509 "lscp.y"
    { (yyval.Char) = '}'; }
    break;

  case 373:
#line 509 "lscp.y"
    { (yyval.Char) = '~'; }
    break;

  case 374:
#line 510 "lscp.y"
    { (yyval.Char) = '\200'; }
    break;

  case 375:
#line 510 "lscp.y"
    { (yyval.Char) = '\201'; }
    break;

  case 376:
#line 510 "lscp.y"
    { (yyval.Char) = '\202'; }
    break;

  case 377:
#line 511 "lscp.y"
    { (yyval.Char) = '\203'; }
    break;

  case 378:
#line 511 "lscp.y"
    { (yyval.Char) = '\204'; }
    break;

  case 379:
#line 511 "lscp.y"
    { (yyval.Char) = '\205'; }
    break;

  case 380:
#line 512 "lscp.y"
    { (yyval.Char) = '\206'; }
    break;

  case 381:
#line 512 "lscp.y"
    { (yyval.Char) = '\207'; }
    break;

  case 382:
#line 512 "lscp.y"
    { (yyval.Char) = '\210'; }
    break;

  case 383:
#line 513 "lscp.y"
    { (yyval.Char) = '\211'; }
    break;

  case 384:
#line 513 "lscp.y"
    { (yyval.Char) = '\212'; }
    break;

  case 385:
#line 513 "lscp.y"
    { (yyval.Char) = '\213'; }
    break;

  case 386:
#line 514 "lscp.y"
    { (yyval.Char) = '\214'; }
    break;

  case 387:
#line 514 "lscp.y"
    { (yyval.Char) = '\215'; }
    break;

  case 388:
#line 514 "lscp.y"
    { (yyval.Char) = '\216'; }
    break;

  case 389:
#line 515 "lscp.y"
    { (yyval.Char) = '\217'; }
    break;

  case 390:
#line 515 "lscp.y"
    { (yyval.Char) = '\220'; }
    break;

  case 391:
#line 515 "lscp.y"
    { (yyval.Char) = '\221'; }
    break;

  case 392:
#line 516 "lscp.y"
    { (yyval.Char) = '\222'; }
    break;

  case 393:
#line 516 "lscp.y"
    { (yyval.Char) = '\223'; }
    break;

  case 394:
#line 516 "lscp.y"
    { (yyval.Char) = '\224'; }
    break;

  case 395:
#line 517 "lscp.y"
    { (yyval.Char) = '\225'; }
    break;

  case 396:
#line 517 "lscp.y"
    { (yyval.Char) = '\226'; }
    break;

  case 397:
#line 517 "lscp.y"
    { (yyval.Char) = '\227'; }
    break;

  case 398:
#line 518 "lscp.y"
    { (yyval.Char) = '\230'; }
    break;

  case 399:
#line 518 "lscp.y"
    { (yyval.Char) = '\231'; }
    break;

  case 400:
#line 518 "lscp.y"
    { (yyval.Char) = '\232'; }
    break;

  case 401:
#line 519 "lscp.y"
    { (yyval.Char) = '\233'; }
    break;

  case 402:
#line 519 "lscp.y"
    { (yyval.Char) = '\234'; }
    break;

  case 403:
#line 519 "lscp.y"
    { (yyval.Char) = '\235'; }
    break;

  case 404:
#line 520 "lscp.y"
    { (yyval.Char) = '\236'; }
    break;

  case 405:
#line 520 "lscp.y"
    { (yyval.Char) = '\237'; }
    break;

  case 406:
#line 520 "lscp.y"
    { (yyval.Char) = '\240'; }
    break;

  case 407:
#line 521 "lscp.y"
    { (yyval.Char) = '\241'; }
    break;

  case 408:
#line 521 "lscp.y"
    { (yyval.Char) = '\242'; }
    break;

  case 409:
#line 521 "lscp.y"
    { (yyval.Char) = '\243'; }
    break;

  case 410:
#line 522 "lscp.y"
    { (yyval.Char) = '\244'; }
    break;

  case 411:
#line 522 "lscp.y"
    { (yyval.Char) = '\245'; }
    break;

  case 412:
#line 522 "lscp.y"
    { (yyval.Char) = '\246'; }
    break;

  case 413:
#line 523 "lscp.y"
    { (yyval.Char) = '\247'; }
    break;

  case 414:
#line 523 "lscp.y"
    { (yyval.Char) = '\250'; }
    break;

  case 415:
#line 523 "lscp.y"
    { (yyval.Char) = '\251'; }
    break;

  case 416:
#line 524 "lscp.y"
    { (yyval.Char) = '\252'; }
    break;

  case 417:
#line 524 "lscp.y"
    { (yyval.Char) = '\253'; }
    break;

  case 418:
#line 524 "lscp.y"
    { (yyval.Char) = '\254'; }
    break;

  case 419:
#line 525 "lscp.y"
    { (yyval.Char) = '\255'; }
    break;

  case 420:
#line 525 "lscp.y"
    { (yyval.Char) = '\256'; }
    break;

  case 421:
#line 525 "lscp.y"
    { (yyval.Char) = '\257'; }
    break;

  case 422:
#line 526 "lscp.y"
    { (yyval.Char) = '\260'; }
    break;

  case 423:
#line 526 "lscp.y"
    { (yyval.Char) = '\261'; }
    break;

  case 424:
#line 526 "lscp.y"
    { (yyval.Char) = '\262'; }
    break;

  case 425:
#line 527 "lscp.y"
    { (yyval.Char) = '\263'; }
    break;

  case 426:
#line 527 "lscp.y"
    { (yyval.Char) = '\264'; }
    break;

  case 427:
#line 527 "lscp.y"
    { (yyval.Char) = '\265'; }
    break;

  case 428:
#line 528 "lscp.y"
    { (yyval.Char) = '\266'; }
    break;

  case 429:
#line 528 "lscp.y"
    { (yyval.Char) = '\267'; }
    break;

  case 430:
#line 528 "lscp.y"
    { (yyval.Char) = '\270'; }
    break;

  case 431:
#line 529 "lscp.y"
    { (yyval.Char) = '\271'; }
    break;

  case 432:
#line 529 "lscp.y"
    { (yyval.Char) = '\272'; }
    break;

  case 433:
#line 529 "lscp.y"
    { (yyval.Char) = '\273'; }
    break;

  case 434:
#line 530 "lscp.y"
    { (yyval.Char) = '\274'; }
    break;

  case 435:
#line 530 "lscp.y"
    { (yyval.Char) = '\275'; }
    break;

  case 436:
#line 530 "lscp.y"
    { (yyval.Char) = '\276'; }
    break;

  case 437:
#line 531 "lscp.y"
    { (yyval.Char) = '\277'; }
    break;

  case 438:
#line 531 "lscp.y"
    { (yyval.Char) = '\300'; }
    break;

  case 439:
#line 531 "lscp.y"
    { (yyval.Char) = '\301'; }
    break;

  case 440:
#line 532 "lscp.y"
    { (yyval.Char) = '\302'; }
    break;

  case 441:
#line 532 "lscp.y"
    { (yyval.Char) = '\303'; }
    break;

  case 442:
#line 532 "lscp.y"
    { (yyval.Char) = '\304'; }
    break;

  case 443:
#line 533 "lscp.y"
    { (yyval.Char) = '\305'; }
    break;

  case 444:
#line 533 "lscp.y"
    { (yyval.Char) = '\306'; }
    break;

  case 445:
#line 533 "lscp.y"
    { (yyval.Char) = '\307'; }
    break;

  case 446:
#line 534 "lscp.y"
    { (yyval.Char) = '\310'; }
    break;

  case 447:
#line 534 "lscp.y"
    { (yyval.Char) = '\311'; }
    break;

  case 448:
#line 534 "lscp.y"
    { (yyval.Char) = '\312'; }
    break;

  case 449:
#line 535 "lscp.y"
    { (yyval.Char) = '\313'; }
    break;

  case 450:
#line 535 "lscp.y"
    { (yyval.Char) = '\314'; }
    break;

  case 451:
#line 535 "lscp.y"
    { (yyval.Char) = '\315'; }
    break;

  case 452:
#line 536 "lscp.y"
    { (yyval.Char) = '\316'; }
    break;

  case 453:
#line 536 "lscp.y"
    { (yyval.Char) = '\317'; }
    break;

  case 454:
#line 536 "lscp.y"
    { (yyval.Char) = '\320'; }
    break;

  case 455:
#line 537 "lscp.y"
    { (yyval.Char) = '\321'; }
    break;

  case 456:
#line 537 "lscp.y"
    { (yyval.Char) = '\322'; }
    break;

  case 457:
#line 537 "lscp.y"
    { (yyval.Char) = '\323'; }
    break;

  case 458:
#line 538 "lscp.y"
    { (yyval.Char) = '\324'; }
    break;

  case 459:
#line 538 "lscp.y"
    { (yyval.Char) = '\325'; }
    break;

  case 460:
#line 538 "lscp.y"
    { (yyval.Char) = '\326'; }
    break;

  case 461:
#line 539 "lscp.y"
    { (yyval.Char) = '\327'; }
    break;

  case 462:
#line 539 "lscp.y"
    { (yyval.Char) = '\330'; }
    break;

  case 463:
#line 539 "lscp.y"
    { (yyval.Char) = '\331'; }
    break;

  case 464:
#line 540 "lscp.y"
    { (yyval.Char) = '\332'; }
    break;

  case 465:
#line 540 "lscp.y"
    { (yyval.Char) = '\333'; }
    break;

  case 466:
#line 540 "lscp.y"
    { (yyval.Char) = '\334'; }
    break;

  case 467:
#line 541 "lscp.y"
    { (yyval.Char) = '\335'; }
    break;

  case 468:
#line 541 "lscp.y"
    { (yyval.Char) = '\336'; }
    break;

  case 469:
#line 541 "lscp.y"
    { (yyval.Char) = '\337'; }
    break;

  case 470:
#line 542 "lscp.y"
    { (yyval.Char) = '\340'; }
    break;

  case 471:
#line 542 "lscp.y"
    { (yyval.Char) = '\341'; }
    break;

  case 472:
#line 542 "lscp.y"
    { (yyval.Char) = '\342'; }
    break;

  case 473:
#line 543 "lscp.y"
    { (yyval.Char) = '\343'; }
    break;

  case 474:
#line 543 "lscp.y"
    { (yyval.Char) = '\344'; }
    break;

  case 475:
#line 543 "lscp.y"
    { (yyval.Char) = '\345'; }
    break;

  case 476:
#line 544 "lscp.y"
    { (yyval.Char) = '\346'; }
    break;

  case 477:
#line 544 "lscp.y"
    { (yyval.Char) = '\347'; }
    break;

  case 478:
#line 544 "lscp.y"
    { (yyval.Char) = '\350'; }
    break;

  case 479:
#line 545 "lscp.y"
    { (yyval.Char) = '\351'; }
    break;

  case 480:
#line 545 "lscp.y"
    { (yyval.Char) = '\352'; }
    break;

  case 481:
#line 545 "lscp.y"
    { (yyval.Char) = '\353'; }
    break;

  case 482:
#line 546 "lscp.y"
    { (yyval.Char) = '\354'; }
    break;

  case 483:
#line 546 "lscp.y"
    { (yyval.Char) = '\355'; }
    break;

  case 484:
#line 546 "lscp.y"
    { (yyval.Char) = '\356'; }
    break;

  case 485:
#line 547 "lscp.y"
    { (yyval.Char) = '\357'; }
    break;

  case 486:
#line 547 "lscp.y"
    { (yyval.Char) = '\360'; }
    break;

  case 487:
#line 547 "lscp.y"
    { (yyval.Char) = '\361'; }
    break;

  case 488:
#line 548 "lscp.y"
    { (yyval.Char) = '\362'; }
    break;

  case 489:
#line 548 "lscp.y"
    { (yyval.Char) = '\363'; }
    break;

  case 490:
#line 548 "lscp.y"
    { (yyval.Char) = '\364'; }
    break;

  case 491:
#line 549 "lscp.y"
    { (yyval.Char) = '\365'; }
    break;

  case 492:
#line 549 "lscp.y"
    { (yyval.Char) = '\366'; }
    break;

  case 493:
#line 549 "lscp.y"
    { (yyval.Char) = '\367'; }
    break;

  case 494:
#line 550 "lscp.y"
    { (yyval.Char) = '\370'; }
    break;

  case 495:
#line 550 "lscp.y"
    { (yyval.Char) = '\371'; }
    break;

  case 496:
#line 550 "lscp.y"
    { (yyval.Char) = '\372'; }
    break;

  case 497:
#line 551 "lscp.y"
    { (yyval.Char) = '\373'; }
    break;

  case 498:
#line 551 "lscp.y"
    { (yyval.Char) = '\374'; }
    break;

  case 499:
#line 551 "lscp.y"
    { (yyval.Char) = '\375'; }
    break;

  case 500:
#line 552 "lscp.y"
    { (yyval.Char) = '\376'; }
    break;

  case 501:
#line 552 "lscp.y"
    { (yyval.Char) = '\377'; }
    break;

  case 502:
#line 555 "lscp.y"
    { (yyval.String) = " ";      }
    break;

  case 504:
#line 557 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + " "; }
    break;

  case 505:
#line 558 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + (yyvsp[(2) - (2)].String);  }
    break;

  case 506:
#line 561 "lscp.y"
    { (yyval.String) = (yyvsp[(2) - (3)].String); }
    break;

  case 507:
#line 562 "lscp.y"
    { (yyval.String) = (yyvsp[(2) - (3)].String); }
    break;


/* Line 1267 of yacc.c.  */
#line 6081 "y.tab.c"
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


#line 880 "lscp.y"


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

