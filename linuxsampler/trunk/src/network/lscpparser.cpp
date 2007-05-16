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
#define YYLAST   5508

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  227
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  165
/* YYNRULES -- Number of rules.  */
#define YYNRULES  601
/* YYNRULES -- Number of states.  */
#define YYNSTATES  2038

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
      99,   101,   103,   105,   109,   117,   125,   131,   139,   141,
     145,   147,   149,   151,   153,   155,   157,   159,   161,   163,
     165,   167,   169,   171,   173,   175,   177,   179,   181,   183,
     185,   187,   189,   191,   193,   195,   197,   199,   201,   203,
     205,   207,   209,   211,   213,   215,   217,   219,   221,   223,
     225,   227,   229,   231,   233,   250,   269,   288,   309,   317,
     321,   325,   329,   335,   339,   343,   345,   347,   353,   361,
     371,   373,   379,   387,   397,   399,   401,   407,   413,   421,
     431,   439,   449,   451,   457,   465,   471,   477,   483,   487,
     489,   491,   495,   499,   509,   511,   517,   521,   529,   535,
     539,   545,   551,   555,   561,   563,   571,   581,   589,   599,
     603,   611,   621,   633,   643,   653,   661,   669,   677,   685,
     689,   693,   699,   703,   709,   713,   719,   727,   731,   735,
     739,   747,   753,   761,   767,   773,   779,   785,   791,   795,
     799,   805,   809,   813,   819,   827,   833,   843,   849,   855,
     861,   867,   873,   879,   885,   891,   897,   903,   904,   907,
     911,   917,   919,   921,   923,   925,   927,   929,   931,   933,
     937,   941,   943,   947,   953,   957,   963,   967,   973,   981,
     985,   987,   989,   991,   993,   995,   997,   999,  1001,  1003,
    1005,  1007,  1009,  1011,  1013,  1015,  1017,  1019,  1021,  1023,
    1025,  1027,  1029,  1031,  1033,  1035,  1037,  1039,  1043,  1045,
    1047,  1049,  1051,  1055,  1061,  1063,  1065,  1067,  1069,  1071,
    1074,  1078,  1083,  1088,  1090,  1093,  1095,  1097,  1099,  1101,
    1103,  1105,  1107,  1109,  1111,  1113,  1115,  1118,  1121,  1124,
    1127,  1130,  1133,  1136,  1139,  1142,  1144,  1146,  1148,  1150,
    1152,  1154,  1156,  1158,  1160,  1162,  1164,  1166,  1168,  1170,
    1172,  1174,  1176,  1178,  1180,  1182,  1184,  1186,  1188,  1190,
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
    1572,  1574,  1576,  1578,  1580,  1582,  1584,  1587,  1590,  1594,
    1598,  1600,  1602,  1604,  1608,  1612,  1616,  1622,  1628,  1633,
    1638,  1643,  1650,  1658,  1663,  1668,  1672,  1677,  1685,  1695,
    1702,  1706,  1716,  1728,  1736,  1754,  1785,  1794,  1799,  1825,
    1850,  1874,  1897,  1923,  1948,  1970,  1991,  2021,  2050,  2070,
    2089,  2103,  2116,  2130,  2143,  2155,  2168,  2180,  2198,  2220,
    2232,  2243,  2250,  2260,  2275,  2286,  2316,  2337,  2357,  2387,
    2407,  2438,  2459,  2477,  2506,  2534,  2560,  2579,  2597,  2625,
    2641,  2658,  2678,  2699,  2717,  2733,  2752,  2768,  2779,  2795,
    2803,  2812,  2836,  2862,  2877,  2891,  2903,  2909,  2914,  2924,
    2938,  2945,  2952,  2958,  2963,  2968,  2974,  2985,  2991,  3005,
    3010,  3015
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     228,     0,    -1,   229,   291,    -1,   229,   292,   291,    -1,
      -1,   230,    -1,   231,    -1,     1,    -1,     3,    -1,   230,
       3,    -1,   230,   290,    -1,   230,   286,    -1,   230,   282,
      -1,   293,   290,   232,    -1,   295,   290,   235,    -1,   296,
     290,   236,    -1,   294,   290,   238,    -1,   301,   290,   240,
      -1,   302,   290,   246,    -1,   303,   290,   252,    -1,   304,
     290,   247,    -1,   309,   290,   237,    -1,   310,   290,   239,
      -1,   311,   290,   233,    -1,   312,   290,   234,    -1,   387,
     290,   241,    -1,   297,   290,   242,    -1,   298,   290,   243,
      -1,   299,   290,   244,    -1,   300,   290,   245,    -1,   387,
      -1,   391,    -1,   313,    -1,   371,   290,   271,    -1,   373,
     290,   377,   290,   271,   290,   271,    -1,   373,   290,   379,
     290,   271,   290,   271,    -1,   373,   290,   271,   290,   271,
      -1,   373,   290,   271,   290,   271,   290,   268,    -1,   361,
      -1,   361,   290,   274,    -1,   318,    -1,   319,    -1,   320,
      -1,   321,    -1,   330,    -1,   336,    -1,   335,    -1,   334,
      -1,   331,    -1,   332,    -1,   333,    -1,   322,    -1,   323,
      -1,   324,    -1,   325,    -1,   326,    -1,   327,    -1,   328,
      -1,   329,    -1,   388,    -1,   337,    -1,   339,    -1,   318,
      -1,   319,    -1,   320,    -1,   321,    -1,   330,    -1,   336,
      -1,   335,    -1,   334,    -1,   331,    -1,   332,    -1,   333,
      -1,   322,    -1,   323,    -1,   324,    -1,   325,    -1,   326,
      -1,   327,    -1,   328,    -1,   329,    -1,   388,    -1,   337,
      -1,   339,    -1,   359,   290,   249,   262,   290,   263,   290,
     264,   290,   270,   290,   273,   290,   268,   290,   266,    -1,
     359,   290,   249,   262,   290,   263,   290,   264,   290,   270,
     290,   273,   290,   268,   290,   266,   290,   255,    -1,   359,
     290,   249,   262,   290,   263,   290,   264,   290,   270,   290,
     273,   290,   268,   290,   266,   290,   275,    -1,   359,   290,
     249,   262,   290,   263,   290,   264,   290,   270,   290,   273,
     290,   268,   290,   266,   290,   255,   290,   275,    -1,   359,
     290,   262,   290,   263,   290,   264,    -1,   313,   290,   267,
      -1,   361,   290,   262,    -1,   361,   290,   305,    -1,   371,
     290,   376,   290,   271,    -1,   371,   290,   271,    -1,   374,
     290,   271,    -1,   314,    -1,   353,    -1,   363,   290,   317,
     290,   282,    -1,   358,   290,   317,   290,   282,   290,   282,
      -1,   358,   290,   317,   290,   282,   290,   282,   290,   250,
      -1,   315,    -1,   349,   290,   317,   290,   282,    -1,   348,
     290,   317,   290,   282,   290,   282,    -1,   348,   290,   317,
     290,   282,   290,   282,   290,   250,    -1,   346,    -1,   356,
      -1,   347,   290,   317,   290,   286,    -1,   357,   290,   317,
     290,   286,    -1,   364,   290,   317,   290,   286,   290,   286,
      -1,   355,   290,   317,   290,   286,   290,   286,   290,   282,
      -1,   351,   290,   317,   290,   286,   290,   286,    -1,   350,
     290,   317,   290,   286,   290,   286,   290,   282,    -1,   316,
      -1,   313,   290,   317,   290,   267,    -1,   313,   290,   334,
     290,   251,   290,   267,    -1,   313,   290,   335,   290,   267,
      -1,   313,   290,   336,   290,   267,    -1,   341,   290,   317,
     290,   270,    -1,   380,   290,   317,    -1,   337,    -1,   338,
      -1,   360,   290,   262,    -1,   360,   290,   305,    -1,   359,
     290,   317,   290,   262,   290,   263,   290,   264,    -1,   362,
      -1,   361,   290,   317,   290,   262,    -1,   370,   290,   267,
      -1,   369,   290,   317,   290,   267,   290,   269,    -1,   372,
     290,   378,   290,   271,    -1,   372,   290,   271,    -1,   371,
     290,   317,   290,   271,    -1,   373,   290,   378,   290,   271,
      -1,   373,   290,   271,    -1,   374,   290,   317,   290,   271,
      -1,   381,    -1,   345,   290,   286,   290,   282,     4,   277,
      -1,   350,   290,   286,   290,   286,   290,   282,     4,   277,
      -1,   354,   290,   286,   290,   282,     4,   277,    -1,   355,
     290,   286,   290,   286,   290,   282,     4,   277,    -1,   313,
     290,   248,    -1,   361,   290,   389,   290,   262,   290,   274,
      -1,   369,   290,   389,   290,   267,   290,   269,   290,   276,
      -1,   369,   290,   351,   290,   267,   290,   269,   290,   257,
     290,   257,    -1,   369,   290,   368,   290,   267,   290,   269,
     290,   265,    -1,   369,   290,   382,   290,   267,   290,   269,
     290,   266,    -1,   371,   290,   389,   290,   271,   290,   272,
      -1,   371,   290,   375,   290,   271,   290,   289,    -1,   374,
     290,   389,   290,   271,   290,   272,    -1,   374,   290,   375,
     290,   271,   290,   289,    -1,   390,   290,   281,    -1,   381,
     290,   266,    -1,   347,   290,   282,   290,   250,    -1,   347,
     290,   282,    -1,   357,   290,   282,   290,   250,    -1,   357,
     290,   282,    -1,   369,   290,   267,   290,   265,    -1,   369,
     290,   267,   290,   265,   290,   276,    -1,   313,   290,   267,
      -1,   360,   290,   262,    -1,   360,   290,   305,    -1,   373,
     290,   379,   290,   271,   290,   279,    -1,   373,   290,   271,
     290,   279,    -1,   372,   290,   379,   290,   271,   290,   279,
      -1,   372,   290,   271,   290,   279,    -1,   371,   290,   271,
     290,   271,    -1,   374,   290,   271,   290,   271,    -1,   371,
     290,   271,   290,   271,    -1,   374,   290,   271,   290,   271,
      -1,   347,   290,   286,    -1,   357,   290,   286,    -1,   369,
     290,   267,   290,   269,    -1,   340,   290,   253,    -1,   341,
     290,   254,    -1,   347,   290,   267,   290,   256,    -1,   351,
     290,   267,   290,   257,   290,   257,    -1,   352,   290,   267,
     290,   258,    -1,   367,   290,   267,   290,   256,   290,   259,
     290,   260,    -1,   357,   290,   267,   290,   256,    -1,   364,
     290,   267,   290,   259,    -1,   365,   290,   267,   290,   260,
      -1,   366,   290,   267,   290,   261,    -1,   381,   290,   267,
     290,   266,    -1,   383,   290,   267,   290,   281,    -1,   384,
     290,   267,   290,   281,    -1,   361,   290,   267,   290,   262,
      -1,   361,   290,   267,   290,   306,    -1,   361,   290,   267,
     290,   307,    -1,    -1,   308,   290,    -1,   282,     4,   277,
      -1,   250,   290,   282,     4,   277,    -1,   385,    -1,   386,
      -1,   346,    -1,   356,    -1,   316,    -1,   314,    -1,   353,
      -1,   315,    -1,   360,   290,   262,    -1,   360,   290,   305,
      -1,   362,    -1,   370,   290,   267,    -1,   372,   290,   378,
     290,   271,    -1,   372,   290,   271,    -1,   373,   290,   378,
     290,   271,    -1,   373,   290,   271,    -1,   273,   290,   268,
     290,   267,    -1,   308,   290,   273,   290,   268,   290,   267,
      -1,   270,   290,   267,    -1,   342,    -1,   343,    -1,   344,
      -1,   286,    -1,   286,    -1,   282,    -1,   286,    -1,   286,
      -1,   305,    -1,   282,    -1,   286,    -1,   286,    -1,   286,
      -1,   286,    -1,   283,    -1,   286,    -1,   286,    -1,   286,
      -1,   286,    -1,   282,    -1,   289,    -1,   289,    -1,   289,
      -1,   289,    -1,   289,    -1,   289,    -1,   278,    -1,   277,
       5,   278,    -1,   282,    -1,   289,    -1,   286,    -1,   283,
      -1,   282,     4,   280,    -1,   279,   290,   282,     4,   280,
      -1,   282,    -1,   289,    -1,   286,    -1,   282,    -1,   287,
      -1,   282,   287,    -1,   284,     6,   284,    -1,     7,   284,
       6,   284,    -1,     8,   284,     6,   284,    -1,   285,    -1,
     284,   285,    -1,     9,    -1,    10,    -1,    11,    -1,    12,
      -1,    13,    -1,    14,    -1,    15,    -1,    16,    -1,    17,
      -1,    18,    -1,   285,    -1,    10,   284,    -1,    11,   284,
      -1,    12,   284,    -1,    13,   284,    -1,    14,   284,    -1,
      15,   284,    -1,    16,   284,    -1,    17,   284,    -1,    18,
     284,    -1,    19,    -1,    20,    -1,    21,    -1,    22,    -1,
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
     290,    -1,   282,    -1,   288,   290,    -1,   288,   282,    -1,
     222,   288,   222,    -1,   223,   288,   223,    -1,   224,    -1,
     225,    -1,   226,    -1,    19,    22,    22,    -1,    25,    23,
      38,    -1,    31,    19,    34,    -1,    39,    32,    31,    19,
      34,    -1,    21,    30,    23,    19,    36,    -1,    24,    27,
      32,    22,    -1,    31,    33,    40,    23,    -1,    21,    33,
      34,    43,    -1,    21,    36,    23,    19,    38,    23,    -1,
      22,    23,    37,    38,    36,    33,    43,    -1,    30,    27,
      37,    38,    -1,    30,    33,    19,    22,    -1,    19,    30,
      30,    -1,    32,    33,    32,    23,    -1,    22,    23,    24,
      19,    39,    30,    38,    -1,    32,    33,    32,    89,    31,
      33,    22,    19,    30,    -1,    36,    23,    31,    33,    40,
      23,    -1,    37,    23,    38,    -1,    37,    39,    20,    37,
      21,    36,    27,    20,    23,    -1,    39,    32,    37,    39,
      20,    37,    21,    36,    27,    20,    23,    -1,    21,    26,
      19,    32,    32,    23,    30,    -1,    19,    40,    19,    27,
      30,    19,    20,    30,    23,    89,    23,    32,    25,    27,
      32,    23,    37,    -1,    19,    40,    19,    27,    30,    19,
      20,    30,    23,    89,    19,    39,    22,    27,    33,    89,
      33,    39,    38,    34,    39,    38,    89,    22,    36,    27,
      40,    23,    36,    37,    -1,    21,    26,    19,    32,    32,
      23,    30,    37,    -1,    27,    32,    24,    33,    -1,    19,
      39,    22,    27,    33,    89,    33,    39,    38,    34,    39,
      38,    89,    22,    23,    40,    27,    21,    23,    89,    21,
      33,    39,    32,    38,    -1,    19,    39,    22,    27,    33,
      89,    33,    39,    38,    34,    39,    38,    89,    22,    23,
      40,    27,    21,    23,    89,    27,    32,    24,    33,    -1,
      31,    27,    22,    27,    89,    27,    32,    34,    39,    38,
      89,    22,    23,    40,    27,    21,    23,    89,    21,    33,
      39,    32,    38,    -1,    31,    27,    22,    27,    89,    27,
      32,    34,    39,    38,    89,    22,    23,    40,    27,    21,
      23,    89,    27,    32,    24,    33,    -1,    31,    27,    22,
      27,    89,    27,    32,    37,    38,    36,    39,    31,    23,
      32,    38,    89,    31,    19,    34,    89,    21,    33,    39,
      32,    38,    -1,    31,    27,    22,    27,    89,    27,    32,
      37,    38,    36,    39,    31,    23,    32,    38,    89,    31,
      19,    34,    89,    27,    32,    24,    33,    -1,    31,    27,
      22,    27,    89,    27,    32,    37,    38,    36,    39,    31,
      23,    32,    38,    89,    21,    33,    39,    32,    38,    -1,
      31,    27,    22,    27,    89,    27,    32,    37,    38,    36,
      39,    31,    23,    32,    38,    89,    27,    32,    24,    33,
      -1,    22,    20,    89,    27,    32,    37,    38,    36,    39,
      31,    23,    32,    38,    89,    22,    27,    36,    23,    21,
      38,    33,    36,    43,    89,    21,    33,    39,    32,    38,
      -1,    22,    20,    89,    27,    32,    37,    38,    36,    39,
      31,    23,    32,    38,    89,    22,    27,    36,    23,    21,
      38,    33,    36,    43,    89,    27,    32,    24,    33,    -1,
      22,    20,    89,    27,    32,    37,    38,    36,    39,    31,
      23,    32,    38,    89,    21,    33,    39,    32,    38,    -1,
      22,    20,    89,    27,    32,    37,    38,    36,    39,    31,
      23,    32,    38,    89,    27,    32,    24,    33,    -1,    21,
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
      -1,    22,    23,    37,    21,    36,    27,    34,    38,    27,
      33,    32,    -1,    24,    33,    36,    21,    23,    -1,    24,
      30,    19,    38,    -1,    36,    23,    21,    39,    36,    37,
      27,    40,    23,    -1,    32,    33,    32,    89,    36,    23,
      21,    39,    36,    37,    27,    40,    23,    -1,    37,    23,
      36,    40,    23,    36,    -1,    40,    33,    30,    39,    31,
      23,    -1,    30,    23,    40,    23,    30,    -1,    31,    39,
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
       0,    97,    97,    98,   101,   102,   103,   104,   107,   108,
     109,   110,   111,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   135,   136,   137,   138,   139,   140,   141,   142,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   193,   194,   195,   196,   199,   202,
     203,   204,   205,   206,   207,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   270,   271,   272,   273,   274,   275,   278,   281,   282,
     285,   286,   287,   288,   291,   292,   295,   296,   299,   300,
     301,   304,   305,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   324,   325,   328,
     329,   332,   333,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   352,   353,   356,
     359,   360,   361,   364,   367,   370,   373,   376,   377,   380,
     383,   386,   389,   392,   395,   396,   399,   402,   405,   408,
     411,   414,   417,   420,   423,   426,   429,   430,   433,   434,
     435,   436,   439,   440,   443,   444,   452,   453,   456,   457,
     460,   461,   462,   466,   467,   470,   471,   472,   473,   474,
     475,   476,   477,   478,   479,   482,   483,   484,   485,   486,
     487,   488,   489,   490,   491,   493,   493,   493,   493,   493,
     493,   493,   493,   493,   493,   493,   493,   493,   493,   493,
     493,   493,   493,   493,   493,   493,   493,   493,   493,   493,
     493,   494,   494,   494,   494,   494,   494,   494,   494,   494,
     494,   494,   494,   494,   494,   494,   494,   494,   494,   494,
     494,   494,   494,   494,   494,   494,   494,   495,   495,   495,
     495,   495,   495,   495,   495,   495,   495,   496,   496,   496,
     496,   496,   496,   496,   496,   496,   496,   496,   496,   496,
     497,   497,   497,   497,   497,   497,   497,   498,   498,   498,
     498,   498,   499,   499,   499,   499,   500,   500,   500,   501,
     501,   501,   502,   502,   502,   503,   503,   503,   504,   504,
     504,   505,   505,   505,   506,   506,   506,   507,   507,   507,
     508,   508,   508,   509,   509,   509,   510,   510,   510,   511,
     511,   511,   512,   512,   512,   513,   513,   513,   514,   514,
     514,   515,   515,   515,   516,   516,   516,   517,   517,   517,
     518,   518,   518,   519,   519,   519,   520,   520,   520,   521,
     521,   521,   522,   522,   522,   523,   523,   523,   524,   524,
     524,   525,   525,   525,   526,   526,   526,   527,   527,   527,
     528,   528,   528,   529,   529,   529,   530,   530,   530,   531,
     531,   531,   532,   532,   532,   533,   533,   533,   534,   534,
     534,   535,   535,   535,   536,   536,   536,   537,   537,   537,
     538,   538,   538,   539,   539,   539,   540,   540,   540,   541,
     541,   541,   542,   542,   545,   546,   547,   548,   551,   552,
     558,   561,   564,   567,   570,   573,   576,   579,   582,   585,
     588,   591,   594,   597,   600,   603,   606,   609,   612,   615,
     618,   621,   624,   627,   630,   633,   636,   639,   642,   645,
     648,   651,   654,   657,   660,   663,   666,   669,   672,   675,
     678,   681,   684,   687,   690,   693,   696,   699,   702,   705,
     708,   711,   714,   717,   720,   723,   726,   729,   732,   735,
     738,   741,   744,   747,   750,   753,   756,   759,   762,   765,
     768,   771,   774,   777,   780,   783,   786,   789,   792,   795,
     798,   801,   804,   807,   810,   813,   816,   819,   822,   825,
     828,   831,   834,   837,   840,   843,   846,   849,   852,   855,
     858,   861
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
  "param_val", "query_val_list", "query_val", "boolean", "string",
  "dotnum", "digits", "digit", "number", "char", "text", "stringval", "SP",
  "LF", "CR", "ADD", "GET", "MAP", "UNMAP", "CLEAR", "FIND", "MOVE",
  "COPY", "CREATE", "DESTROY", "LIST", "LOAD", "ALL", "NONE", "DEFAULT",
  "NON_MODAL", "REMOVE", "SET", "SUBSCRIBE", "UNSUBSCRIBE", "CHANNEL",
  "AVAILABLE_ENGINES", "AVAILABLE_AUDIO_OUTPUT_DRIVERS", "CHANNELS",
  "INFO", "AUDIO_OUTPUT_DEVICE_COUNT", "AUDIO_OUTPUT_DEVICE_INFO",
  "MIDI_INPUT_DEVICE_COUNT", "MIDI_INPUT_DEVICE_INFO",
  "MIDI_INSTRUMENT_MAP_COUNT", "MIDI_INSTRUMENT_MAP_INFO",
  "MIDI_INSTRUMENT_COUNT", "MIDI_INSTRUMENT_INFO",
  "DB_INSTRUMENT_DIRECTORY_COUNT", "DB_INSTRUMENT_DIRECTORY_INFO",
  "DB_INSTRUMENT_COUNT", "DB_INSTRUMENT_INFO", "CHANNEL_COUNT",
  "CHANNEL_INFO", "FX_SEND_COUNT", "FX_SEND_INFO", "BUFFER_FILL",
  "STREAM_COUNT", "VOICE_COUNT", "TOTAL_VOICE_COUNT",
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
  "DESCRIPTION", "FORCE", "FLAT", "RECURSIVE", "NON_RECURSIVE", "SERVER",
  "VOLUME", "LEVEL", "MUTE", "SOLO", "BYTES", "PERCENTAGE", "RESET",
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
     231,   231,   232,   232,   232,   232,   232,   232,   232,   232,
     233,   233,   233,   233,   233,   233,   233,   233,   233,   233,
     233,   233,   233,   233,   233,   233,   233,   233,   233,   233,
     233,   233,   234,   234,   234,   234,   234,   234,   234,   234,
     234,   234,   234,   234,   234,   234,   234,   234,   234,   234,
     234,   234,   234,   234,   235,   235,   235,   235,   236,   237,
     237,   237,   237,   237,   237,   238,   238,   238,   238,   238,
     238,   238,   238,   238,   238,   238,   238,   238,   238,   238,
     238,   238,   238,   238,   238,   238,   238,   238,   238,   238,
     238,   238,   238,   238,   238,   238,   238,   238,   238,   238,
     238,   238,   238,   238,   238,   239,   239,   239,   239,   239,
     239,   239,   239,   239,   239,   239,   239,   239,   239,   239,
     239,   240,   240,   240,   240,   240,   240,   241,   242,   242,
     243,   243,   243,   243,   244,   244,   245,   245,   246,   246,
     246,   247,   247,   248,   248,   248,   248,   248,   248,   248,
     248,   248,   248,   248,   248,   248,   248,   249,   249,   250,
     250,   251,   251,   252,   252,   252,   252,   252,   252,   252,
     252,   252,   252,   252,   252,   252,   252,   253,   253,   254,
     255,   255,   255,   256,   257,   258,   259,   260,   260,   261,
     262,   263,   264,   265,   266,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   277,   278,   278,
     278,   278,   279,   279,   280,   280,   281,   281,   282,   282,
     283,   283,   283,   284,   284,   285,   285,   285,   285,   285,
     285,   285,   285,   285,   285,   286,   286,   286,   286,   286,
     286,   286,   286,   286,   286,   287,   287,   287,   287,   287,
     287,   287,   287,   287,   287,   287,   287,   287,   287,   287,
     287,   287,   287,   287,   287,   287,   287,   287,   287,   287,
     287,   287,   287,   287,   287,   287,   287,   287,   287,   287,
     287,   287,   287,   287,   287,   287,   287,   287,   287,   287,
     287,   287,   287,   287,   287,   287,   287,   287,   287,   287,
     287,   287,   287,   287,   287,   287,   287,   287,   287,   287,
     287,   287,   287,   287,   287,   287,   287,   287,   287,   287,
     287,   287,   287,   287,   287,   287,   287,   287,   287,   287,
     287,   287,   287,   287,   287,   287,   287,   287,   287,   287,
     287,   287,   287,   287,   287,   287,   287,   287,   287,   287,
     287,   287,   287,   287,   287,   287,   287,   287,   287,   287,
     287,   287,   287,   287,   287,   287,   287,   287,   287,   287,
     287,   287,   287,   287,   287,   287,   287,   287,   287,   287,
     287,   287,   287,   287,   287,   287,   287,   287,   287,   287,
     287,   287,   287,   287,   287,   287,   287,   287,   287,   287,
     287,   287,   287,   287,   287,   287,   287,   287,   287,   287,
     287,   287,   287,   287,   287,   287,   287,   287,   287,   287,
     287,   287,   287,   287,   287,   287,   287,   287,   287,   287,
     287,   287,   287,   287,   287,   287,   287,   287,   287,   287,
     287,   287,   287,   287,   287,   287,   287,   287,   287,   287,
     287,   287,   287,   287,   287,   287,   287,   287,   287,   287,
     287,   287,   287,   287,   288,   288,   288,   288,   289,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   335,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   352,   353,   354,   355,   356,   357,   358,   359,
     360,   361,   362,   363,   364,   365,   366,   367,   368,   369,
     370,   371,   372,   373,   374,   375,   376,   377,   378,   379,
     380,   381,   382,   383,   384,   385,   386,   387,   388,   389,
     390,   391
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     3,     0,     1,     1,     1,     1,     2,
       2,     2,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     1,     1,     3,     7,     7,     5,     7,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,    16,    18,    18,    20,     7,     3,
       3,     3,     5,     3,     3,     1,     1,     5,     7,     9,
       1,     5,     7,     9,     1,     1,     5,     5,     7,     9,
       7,     9,     1,     5,     7,     5,     5,     5,     3,     1,
       1,     3,     3,     9,     1,     5,     3,     7,     5,     3,
       5,     5,     3,     5,     1,     7,     9,     7,     9,     3,
       7,     9,    11,     9,     9,     7,     7,     7,     7,     3,
       3,     5,     3,     5,     3,     5,     7,     3,     3,     3,
       7,     5,     7,     5,     5,     5,     5,     5,     3,     3,
       5,     3,     3,     5,     7,     5,     9,     5,     5,     5,
       5,     5,     5,     5,     5,     5,     5,     0,     2,     3,
       5,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     1,     3,     5,     3,     5,     3,     5,     7,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     1,     3,     5,     1,     1,     1,     1,     1,     2,
       3,     4,     4,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     1,     1,     1,     1,     1,
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
       1,     1,     1,     1,     1,     1,     2,     2,     3,     3,
       1,     1,     1,     3,     3,     3,     5,     5,     4,     4,
       4,     6,     7,     4,     4,     3,     4,     7,     9,     6,
       3,     9,    11,     7,    17,    30,     8,     4,    25,    24,
      23,    22,    25,    24,    21,    20,    29,    28,    19,    18,
      13,    12,    13,    12,    11,    12,    11,    17,    21,    11,
      10,     6,     9,    14,    10,    29,    20,    19,    29,    19,
      30,    20,    17,    28,    27,    25,    18,    17,    27,    15,
      16,    19,    20,    17,    15,    18,    15,    10,    15,     7,
       8,    23,    25,    14,    13,    11,     5,     4,     9,    13,
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
       0,     0,     1,   501,   502,     2,     0,     9,   353,   348,
     347,   345,   346,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   325,   326,   337,   339,   340,   341,   342,
     343,   344,   349,   350,   351,   352,   354,   355,   356,   357,
     358,   359,   360,   361,   362,   363,   364,   365,   366,   367,
     368,   369,   370,   371,   372,   373,   374,   375,   376,   377,
     378,   379,   380,   381,   382,   383,   384,   385,   386,   387,
     388,   389,   390,   391,   392,   393,   394,   395,   396,   397,
     398,   399,   400,   401,   402,   403,   404,   405,   406,   407,
     408,   409,   410,   411,   412,   413,   414,   415,   416,   417,
     418,   419,   420,   421,   422,   423,   424,   425,   426,   427,
     428,   429,   430,   431,   432,   433,   434,   435,   436,   437,
     438,   439,   440,   441,   442,   443,   444,   445,   446,   447,
     448,   449,   450,   451,   452,   453,   454,   455,   456,   457,
     458,   459,   460,   461,   462,   463,   464,   465,   466,   467,
     468,   469,   470,   471,   472,   473,   474,   475,   476,   477,
     478,   479,   480,   481,   482,   483,   484,   485,   486,   487,
     488,   489,   490,   491,   492,   493,   500,    12,   265,    11,
     248,    10,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   503,
       0,     0,     0,     0,     0,   504,     0,     0,   505,     0,
       0,     0,     0,   520,     0,     0,     0,     3,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   266,   253,
     267,   268,   269,   270,   271,   272,   273,   274,   338,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   336,   249,
       0,     0,     0,    13,    32,    38,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    16,     0,    95,
     100,   112,   119,   120,     0,   104,     0,     0,     0,     0,
       0,    96,     0,   105,     0,     0,     0,     0,     0,   124,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   134,
       0,    14,     0,    15,     0,     0,    26,     0,     0,    27,
       0,     0,     0,    28,     0,     0,    29,     0,     0,     0,
       0,     0,    17,     0,     0,     0,    18,     0,     0,     0,
       0,     0,     0,     0,    19,   196,   198,   195,   193,   197,
     194,     0,   201,     0,     0,     0,     0,    20,     0,     0,
      21,     0,     0,     0,     0,     0,     0,     0,    22,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      23,    40,    41,    42,    43,    51,    52,    53,    54,    55,
      56,    57,    58,    44,    48,    49,    50,    47,    46,    45,
      60,    61,    59,    24,    62,    63,    64,    65,    73,    74,
      75,    76,    77,    78,    79,    80,    66,    70,    71,    72,
      69,    68,    67,    82,    83,    81,    25,     0,     0,   510,
       0,     0,   508,   513,   514,   509,   601,     0,     0,     0,
       0,     0,   254,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   187,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   507,     0,     0,     0,   597,     0,   506,
       0,     0,     0,     0,     0,     0,    39,   233,    33,   230,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     256,   257,   258,   259,   260,   261,   262,   263,   264,     0,
     121,   220,   122,     0,     0,     0,     0,   126,   226,     0,
       0,   129,     0,   132,     0,     0,   118,     0,     0,     0,
       0,     0,     0,   158,   159,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   152,   154,
       0,   168,   169,     0,     0,     0,     0,     0,   199,   200,
     202,   204,     0,   206,     0,     0,   171,     0,   232,     0,
     172,     0,   229,    89,    90,    91,     0,    93,     0,    94,
       0,     0,     0,     0,     0,     0,   139,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   150,
     224,     0,   253,   225,   149,   247,   246,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   157,   511,
       0,   519,     0,     0,     0,     0,     0,   495,     0,   494,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   188,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   600,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   512,     0,     0,
       0,     0,     0,   498,   497,   496,   499,     0,     0,    36,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   113,     0,     0,     0,   191,   192,   115,
     116,   117,   106,     0,   101,     0,     0,     0,   107,     0,
       0,   515,   125,    97,     0,     0,   130,     0,   128,   131,
     133,     0,     0,     0,     0,   221,     0,     0,   163,     0,
       0,   161,     0,     0,   164,   165,   166,   167,     0,     0,
       0,   151,     0,   153,   155,   223,   170,   228,     0,     0,
       0,     0,   203,   205,     0,     0,   227,     0,   209,     0,
      92,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   250,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   587,     0,     0,     0,
       0,     0,     0,     0,     0,   551,     0,     0,   590,     0,
     591,   527,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   593,   594,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   599,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   251,   252,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   521,     0,
     523,     0,     0,     0,    37,    34,    35,     0,     0,   523,
       0,   579,     0,     0,     0,     0,   114,   102,     0,   110,
       0,    98,     0,   108,   127,     0,     0,     0,     0,    88,
     222,     0,     0,     0,   242,   244,   245,   162,   160,     0,
       0,   579,     0,     0,   345,   346,   189,   236,   238,   241,
     240,   239,   156,   235,     0,     0,     0,     0,     0,   207,
       0,   586,     0,     0,     0,     0,   173,   213,     0,   214,
     175,   215,   177,     0,     0,   184,   185,   186,   178,   216,
     179,   217,   218,   180,   219,     0,   181,   182,   183,   135,
       0,   137,     0,   140,     0,   592,     0,     0,     0,     0,
       0,     0,   146,   145,   231,   148,   147,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   526,     0,   580,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   522,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   595,     0,   103,   111,   109,    99,   123,
       0,     0,     0,     0,     0,     0,   243,     0,     0,     0,
     190,   237,     0,     0,     0,     0,   208,     0,     0,     0,
       0,   174,     0,     0,     0,   136,   138,     0,     0,     0,
     143,   144,   141,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     550,     0,     0,     0,     0,     0,   516,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   588,     0,
     518,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   176,     0,     0,   142,     0,
       0,   544,     0,     0,     0,     0,     0,   549,     0,     0,
       0,     0,     0,   546,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   577,     0,     0,     0,     0,     0,     0,   541,     0,
       0,   543,     0,     0,     0,   545,     0,     0,     0,     0,
       0,     0,     0,     0,   584,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   584,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   517,     0,     0,   585,
       0,   540,     0,   542,     0,     0,   598,     0,   583,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   596,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     589,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     574,   569,     0,   569,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   570,     0,     0,    84,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   524,     0,     0,   567,   573,     0,     0,
     547,     0,     0,     0,   567,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   574,   576,   578,     0,     0,     0,
       0,     0,     0,     0,     0,   547,     0,     0,     0,     0,
       0,     0,     0,     0,   566,     0,     0,     0,     0,     0,
       0,    85,    86,   234,   210,   211,   212,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     539,     0,     0,     0,     0,     0,   571,     0,   557,   559,
       0,     0,     0,     0,     0,   571,     0,     0,     0,     0,
       0,   557,     0,     0,     0,     0,     0,     0,   562,     0,
       0,   538,     0,     0,     0,     0,     0,     0,     0,   561,
     556,     0,     0,     0,     0,     0,     0,   572,     0,     0,
       0,    87,     0,     0,     0,     0,     0,   575,     0,     0,
       0,     0,     0,   535,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   548,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   534,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   561,     0,     0,     0,     0,   531,     0,     0,   581,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   530,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   529,
       0,     0,   533,     0,     0,     0,     0,   582,     0,   565,
       0,     0,     0,     0,   528,     0,     0,   532,     0,     0,
       0,     0,     0,   552,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   568,     0,   554,     0,   564,     0,     0,
       0,     0,     0,   563,     0,     0,     0,   537,     0,   558,
       0,     0,   555,   536,   560,   525,     0,   553
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    14,    15,    16,    17,   353,   480,   503,   401,   403,
     450,   367,   458,   422,   526,   406,   409,   413,   416,   426,
     447,   776,   719,  1041,   996,   434,   756,   760,  1821,  1286,
    1288,  1290,  1298,  1300,  1303,   700,  1024,  1249,  1044,   809,
     707,  1055,  1046,   761,   658,  1323,   757,   656,  1822,  1272,
    1266,  1267,  1028,  1254,   814,  1268,  1269,   811,   278,   708,
     280,   838,   659,  1150,    55,    56,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,  1302,  1296,
    1297,   720,    30,    31,    32,    33,   354,   369,   370,   371,
     676,   481,   482,   483,   484,   485,   486,   487,   488,   489,
     490,   491,   492,   493,   494,   495,   496,   497,   498,   499,
     372,   373,   501,   448,   374,  1824,  1825,  1826,   460,   375,
     376,   377,   378,   379,   380,   779,   381,   462,   382,   383,
     384,   385,   386,   387,   355,   389,   390,   391,   783,   784,
     785,   799,   392,   393,   356,   395,   357,   397,   803,   768,
     663,   712,   664,   398,   399,   800,   787,   788,   997,   998,
      34,   502,   794,   469,    35
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -1308
static const yytype_int16 yypact[] =
{
      45, -1308, -1308,    84,   258,   127,   105,   182,   140,   126,
     193,   184,    74,   210,   296,    61,  2430, -1308,   122,   122,
     122,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   122,   122, -1308,   285,   327,   351,   332,
     350,   378,   388,   393,   436,   442,   486,   495,   192,   493,
     512,   306, -1308, -1308, -1308, -1308,   308, -1308, -1308, -1308,
   -1308, -1308, -1308, -1308,   492,   492,   492,   492,   492,   492,
     492,   492,   492, -1308, -1308, -1308, -1308, -1308, -1308, -1308,
   -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308,
   -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308,
   -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308,
   -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308,
   -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308,
   -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308,
   -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308,
   -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308,
   -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308,
   -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308,
   -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308,
   -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308,
   -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308,
   -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308,
   -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308,
   -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308,
   -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308,
   -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308,
   -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308,
   -1308, -1308, -1308, -1308, -1308, -1308, -1308,  3316, -1308, -1308,
   -1308, -1308,    83,   139,   504,   504,   505,   515,   516,   516,
     249,   249,   179,   168,   219,   159,   117,   117,   513, -1308,
     520,   498,   523,   506,   521, -1308,   508,   525, -1308,   526,
     510,   517,   528, -1308,   518,   533,   514, -1308, -1308, -1308,
   -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308,   492, -1308,
     492,   492,   492,   492,   492,   492,   492,   492, -1308, -1308,
   -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308,
     530,   534,   531, -1308, -1308,   122,   122,   122,   227,   536,
     537,   527,   522,   538,   540,   535,   539, -1308,   122, -1308,
   -1308, -1308, -1308, -1308,   122, -1308,   122,   122,   122,   122,
     122, -1308,   122, -1308,   122,   122,   122,   122,   122, -1308,
     122,   122,   122,   122,   122,   122,   122,   122,   122, -1308,
     542, -1308,   122, -1308,   122,   543, -1308,   122,   546, -1308,
     122,   122,   547, -1308,   122,   122, -1308,   122,   122,   532,
     544,   550, -1308,   122,   122,   122, -1308,   122,   122,   122,
     279,   548,   545,   551, -1308, -1308, -1308, -1308, -1308, -1308,
   -1308,   122, -1308,   122,   122,   122,   541, -1308,   122,   122,
   -1308,   122,   122,   122,   122,   549,   558,   553, -1308,   122,
     122,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     566,   569,   556,   564,   567,   555,   563,   554,   577,   578,
   -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308,
   -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308,
   -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308,
   -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308,
   -1308, -1308, -1308, -1308, -1308, -1308, -1308,   122,   524, -1308,
     574,   582, -1308, -1308, -1308, -1308, -1308,   579,   584,   602,
     590,   605, -1308,   607,   552,   611,   174,   174,    13,   612,
     608,   616,   560,   615,   561,   620,   609,   606,   613,   107,
     624,   624,   624,   624,   624,   624,   624,   624,   624,   624,
     405,   624,   624,   624,   624,   503,   624,    22,    22,   624,
     624,   630,   621,   503,   632,   405,   568,     3,     3,   570,
     174,   174,   174,   174,   633,   585,   634,  3316,  3316,   503,
     503,   503,   503,   636,   665,   596,   664,   405,   503,    22,
      22,   654,    15,  3316,   503,   405,     8,   174,   670,   668,
     673,   109,   503,   503,   503,   503,   669,   156,   111,   111,
     482,  3535,   675,   676,   683,   614,   617,   674,   129,   672,
     671,   687,   503, -1308,   696,   688,   697, -1308,   690, -1308,
     691,   698,   702,   704,  2652,  2652, -1308, -1308, -1308, -1308,
     703,   699,   122,   122,   122,   707,   708,   705,   712,   713,
     709,   715,   710,   725,   714,   716,   122,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     492,   492,   492,   492,   492,   492,   492,   492,   492,   717,
   -1308, -1308, -1308,   122,   122,   122,   122, -1308, -1308,   122,
     726, -1308,   122, -1308,   122,   122, -1308,   724,   721,   503,
     122,   122,   728, -1308, -1308,   729,   122,   122,   122,   122,
     730,   122,   122,   122,   122,   732,   723,   753,  2652,  2652,
     122, -1308, -1308,   122,   754,   759,   749,   767, -1308, -1308,
   -1308, -1308,   122, -1308,   122,   757, -1308,   122, -1308,   122,
   -1308,   122,  3316, -1308, -1308, -1308,   763, -1308,   122, -1308,
     770,   765,   772,   761,   167,   768, -1308,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   783,   122,   764,   782,   779,   122,   122,
     122,   122,   784,   122,   122,   122,   122,   492,   492, -1308,
   -1308,   247,    23, -1308, -1308,  3316, -1308,   781,   785,   778,
     786,   774,   792,   787,   794,   793,   798,   797, -1308, -1308,
     776, -1308,   796,   799,   789,   795,   736,  3316,  1986, -1308,
    2208,   807,   800,   174,   174,   174,   801,   803,   814,   815,
     816,   805,   740,   808,   819,   804,   806,   503,   151,   503,
     503,  3316,   503,  3316,  3316,   503,   503,   503,   503,  3316,
     503,   820,   503,  3316,   503,   503,   174,   830,   174,   174,
     174,   766,   821,   122, -1308,   503,   769,   822,  3316,   174,
    3316,   174,   824,   174,   174,   174,   174,   826,   829,   771,
    3316,  3316,   503,   503,   828,   825,   839,   775,   174,   174,
     827,   503,   174,   503,   833,   174,   832, -1308,   777,   848,
     853,   841,   847,   503,   503,   503,   503,   503,   503,   503,
     503,   503,   503,   503,   503,  3316,   503,  3316,   503,   850,
     503,   860,   843,   862,   503,   503,   503,   503,   849,   174,
     174,   174,   174,   318,   450,   492,   852,   864,   856,   857,
     867,   873,   809,   870,   875,   865,   874, -1308,   876,   863,
     877,   866,   878, -1308,  3316, -1308, -1308,   869,   812,   122,
     122,   122,   813,   885,   883,   879,   887,   880,   884,   882,
     831,   890,   881, -1308,   872,   896,   122, -1308, -1308, -1308,
   -1308, -1308, -1308,  2652,  3316,   122,   122,   122, -1308,  2652,
     122, -1308, -1308,  3316,   122,   122, -1308,   886, -1308, -1308,
   -1308,   894,   834,   503,   122, -1308,   895,   889,   122,  3754,
     122,   122,   122,   891, -1308, -1308, -1308, -1308,   835,   897,
     900,   122,  3973,   122,   122, -1308, -1308, -1308,   842,   907,
     901,   905, -1308, -1308,   898,   122, -1308,   122, -1308,   913,
   -1308,   846,   909,   911,   912,   918,   910,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   122,   122,   122,  4192,
     122,  4411,   122,   922,   122,   920,   925,   923,   122,   122,
     122,   122,   928,   122,   122,   122,   122,   492,   492,   492,
     871,   915,   929,   916,   924,   927,   932,   931,   935,   888,
     892,   939,   940,   938,   933,   937, -1308,   934,   503,   174,
     174,   941,   952,   943,   944, -1308,   953,   946, -1308,   936,
   -1308, -1308,   945,   948,   503,  3316,   503,   503,   503,  3316,
     503,   503,   503,   949,   947,   955,   122,   503,   956,   954,
    3316,  2874,  3316,  3316,   957,   963,   978,   969,  3316,  3095,
     174,   970,   972,   982,   975,   979,   503,   503,   986,   980,
     983,   984,   930, -1308, -1308,   503,   503,  3316,   503,    78,
     503,   405,  3316,   503,   482,  3535,  3535,  3095,  3316,  3095,
    3316, -1308,   174,   985,   981,   942,   503,   503,   503,   503,
     976,   174,   174,   174,   174,   492,   492,   987,   951,   991,
     988,  1002,   974,   998,  1004,   992,   996,  1011, -1308,  1017,
   -1308,  1006,  1007,  1022, -1308, -1308, -1308,  1026,  1037,  1032,
    1034,  1039,   209,  1038,  1061,  1064, -1308,  2652,   122, -1308,
     122,  2652,   122, -1308, -1308,  1049,  1050,  1055,   503, -1308,
   -1308,  1052,  1054,  4630, -1308,  3316, -1308,   122,   122,  1056,
    1057, -1308,  1059,  4849,   492,   492,  1086, -1308,  3316, -1308,
   -1308, -1308, -1308, -1308,  1058,  1032,  1039,   320,  1071, -1308,
     122, -1308,  1067,   397,  1009,  1076, -1308, -1308,   122, -1308,
   -1308,  3316, -1308,  1084,  1075, -1308, -1308, -1308, -1308, -1308,
   -1308, -1308, -1308, -1308,  3316,   122, -1308, -1308, -1308,  1086,
    5068,  1086,  5287, -1308,  1020, -1308,  1089,   122,   122,   122,
     122,  1085, -1308, -1308, -1308, -1308, -1308,  1072,  1090,  1024,
    1079,  1027,  1091,   420,  1098,  1101,  1092,  1093,  1096,  1088,
    1094,  1102,  1095,  1105, -1308,  1097, -1308,  1100,  1099,  1104,
    1103,  1106,  3316,  3316,  3316,  3316,   503,  1107,  1111,  1113,
     122,  1112,  1115,  2874,  1116,  1114,  1117,  3095,  3095,  1119,
    1120,  1122,  1109,   503,  1125,  1127,  1118,  1126,   503,  1121,
    1132,   503,  3095,  3095,  1134,  1135,   503,   503,   482,   174,
    1136,  1131,  1144,   317,  1133,   321,  1142,  1137,  1139,  1143,
    1145,  1152,  1141, -1308,  1157,  1147,  1155,  1162,  1108,  1167,
    1161,  1164,  1180, -1308,  1174,   122,  3316,  3316,   122, -1308,
    1168,  1171,  1191,  3316,  1175,  1181, -1308,  1184,  1182,  1179,
    1086, -1308,  1185,  1189,  1187,  1192, -1308,  1186,  1193,  1194,
     435, -1308,  1199,  1209,   122,  1086,  1086,  1195,  1204,   122,
   -1308, -1308, -1308,  1200,  1203,  1210,  1206,  1211,  1216,  1208,
    1219,  1218,  1214,  1212,  1230,  1217,  1234,  1225,  1236,  1221,
    1226,  1222,   173,  1240,  1176,  1227,  1244,  1231,  1245,  1232,
    1243,   122,  1235,  1247,  1252,  1237,  1188,  1239,  1190,  1241,
   -1308,  1242,  1196,  1246,  1251,  1253, -1308,   405,  1248,  1256,
     503,  1255,  1257,  1261,  1259,  1271,  1260,  1266,  1275,  1267,
    1220,  1268,  1277,  1276,  1288,  1274,  1282,  1284,  1279,  1280,
    1278,  1287,  1293,  1289,   186,  1291,  1238,  1304, -1308,  1294,
   -1308,   174,  1297,  1292,  1298,  1295,  1307,  1299,  1310,  1308,
    1300,   187,  1301,  1302,  1311, -1308,  1309,  1306, -1308,  1313,
    1312, -1308,  1316,  1318,  1317,  1322,  1323, -1308,  1333,  1326,
    1319,  1321,  1272, -1308,  1328,  1337,  1340,  1283,  1342,  1344,
    1353,  1341,   161,  1345,  1358,  1361,  1360,  1363,   122,  1367,
    1362,  1365,  1315,  1368,  1320,  1373,  1375,  1324,  1378,  1350,
    1366,  1325,  1372,  1376,  1384,  1374,  1329,  1381, -1308,  1382,
    1383, -1308,  1399,  1400,  1387, -1308,  1404,    35,  1394,  1389,
     418,  1403,  1405,  1407,    37,  1391,  1408,  1401,  1395,  1406,
    1413,  1409,   503,  1411,    40,  1349,  1418,  1410,  1425,  1412,
    1416,   449,  1414,  1415,  1419,    77, -1308,  1424,  1423, -1308,
    1427, -1308,  1377, -1308,  1428,  1431, -1308,  1434, -1308,  1442,
    1432,  1446,  1445,   166,  1439,  1441,  1385,  1453,  1449,  1440,
    1443,  1444,  1447, -1308,  1450,   122,  1451,  1457,  1460,  1463,
    1464,  1465,  1455,  1468,  1472,  1469,  1459,  1402,  1473,  1467,
    1458,  1420,  1474,  1475,   293,  1478,  1470,  1471,  1480,  1422,
   -1308,  1483,  1476,  1485,  1429,  1490,  1492,  1493,  1496,  1499,
    1435,    41,  1491, -1308,   482,  1489,  1500,  1488,  1510,  1494,
    1511,    46,  1514,  1498,  1515,  1435,    87,  1521,  1505,  1508,
    1522,  1523,  1504,  1512,  1524,  1516,  1528,  1461,  1525,  1517,
    1527,  1529,  1532,  1520,  1530,  1518,  1533,  1531,  1541,  1534,
    1535, -1308,  1537,  1536,   122,  1540,  1539,  1548,  1545,  1550,
    1546,  1547,  1551,  1557,  1555,  1513,  1552,  1544,  1560,  1549,
    1559,  1553,  1554,  1563,  1566,   254,  1561,  1568,  1574,  1565,
    1577,  1572,  1562, -1308,  1569,  1579,  1567,  1519,  1581,  1586,
    1526,    29,  1583,  1588, -1308,  1589,  1567,  1592,  1575,  1591,
    1542,  1594,  1580,  1584, -1308, -1308, -1308,  1596,  1587,  1595,
    1590,  1543,  1593,  1597,  1601, -1308,  1600,  1599,  1602,  1607,
    1598,  1603,  1585,  1614, -1308,  1604,  1608,  1605,  1606,  1611,
    1613,   122, -1308, -1308, -1308, -1308, -1308,  1619,  1622,  1624,
    1616,  1625,  1628,  1618,  1621,  1631,  1632,  1633,  1623,  1641,
   -1308,   324,  1627,  1639,  1630,  1629, -1308,  1638,  1634,  1609,
    1635,  1636,  1637,  1651,  1653,  1640,  1654,  1610,  1642,   174,
    1643, -1308,  1634,  1640,  1646,  1615,  1660,  1648, -1308,  1652,
    1617, -1308,  1645,  1655,  1658,  1659,  1661,  1620,  1663,  1626,
   -1308,  1668,  1647,  1644,  1670,  1649,  1656, -1308,  1665,  1686,
    1677, -1308,  1683,  1626,  1684,  1681,  1696, -1308,   326,  1687,
    1682,  1698,  1685, -1308,   338,  1688,  1691,  1707,  1689,  1708,
    1693,  1712,  1709, -1308,  1711,  1710,  1699,  1717,  1719,  1713,
    1706,  1718,  1704,  1720,  1716, -1308,  1721,  1723,  1702,  1722,
    1715,  1664,  1724,    75,  1725,  1727,  1735,  1705,  1731,  1732,
    1736, -1308,  1730,  1746,  1728,  1734, -1308,  1739,  1749, -1308,
    1738,  1756,  1757,  1753,  1758,  1759,  1761,  1766,  1748,  1768,
    1765,  1760,  1762,  1700, -1308,  1764,  1767,  1771,  1763,  1755,
    1582,  1769,  1770,  1773,  1772,  1774,  1776,  1775,  1777, -1308,
     362,  1778, -1308,  1779,  1780,  1784,  1789, -1308,  1791, -1308,
    1799,  1790,  1800,  1801, -1308,  1792,  1794, -1308,  1804,  1793,
    1788,  1796,  1797,  1740,  1798,  1802,  1803,  1754,  1806,  1805,
    1811,  1812,  1807, -1308,  1815, -1308,  1814, -1308,  1810,  1813,
    1822,  1816,  1817, -1308,  1821,  1819,  1809, -1308,  1820, -1308,
    1826,  1808, -1308, -1308, -1308, -1308,  1827, -1308
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308,
   -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308,
   -1308, -1308, -1308,  -867, -1308, -1308, -1308, -1308, -1308, -1009,
   -1307, -1308,   417,    57, -1308,  -547,  -984, -1204,   412, -1164,
    -330, -1094, -1077,  -842,   868,   597,  -911,   610,   -11,   461,
   -1128,   489,  -863,   501,  -744,   507,  -609,   -15,   147,     6,
     284,  1213,  -154,   -16,  1818, -1308, -1308, -1308, -1308, -1308,
   -1308, -1308, -1308, -1308, -1308, -1308, -1308, -1308,  -484, -1308,
   -1308,  1254, -1308, -1308, -1308, -1308,  -130,  1573,  1612,  1650,
    -263,  1570,  1576,  1578,  1657,  1662,  1666,  1667,  1669,  1671,
    1672,  1673,  1674,  1675,  1676,  1678,  1679,  -267,  -266,  -264,
     177, -1308,  1680, -1308,  1690, -1308, -1308, -1308, -1308,  1692,
    -265, -1308, -1308,  1914,  -237, -1308,  1694, -1308,  2135,  2360,
    -248, -1308,   202,   114,  -254,  2361, -1308,  1250, -1308, -1308,
   -1308, -1308,    31,  2582,   -61,   -13,  -180,   -12,  1229, -1308,
   -1308,  -493,   -63, -1308,  -272, -1308, -1308, -1308, -1308, -1308,
   -1308,  2578,  -224, -1308, -1308
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -266
static const yytype_int16 yytable[] =
{
     281,  1057,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,  1001,
    1306,   810,   279,   468,  1224,   423,   427,  1031,  -265,   388,
     520,   521,   766,   522,  1043,   661,   721,   660,   723,  1146,
     452,   464,   424,   428,  1360,   661,     1,   718,     2,   328,
     330,   331,   332,   333,   334,   335,   336,   337,   710,  1309,
     748,  1311,  1819,  1820,     3,  1244,     4,     5,   764,     6,
       7,  1441,  1648,  1280,  1648,     8,     9,  1648,  1741,  1449,
      10,    11,    12,  1741,    13,   714,   702,   318,   690,   691,
     692,   693,   694,   695,   696,   697,   698,    49,  1678,  1583,
    1293,   724,  1954,   396,   350,   351,    36,   411,  1754,  1668,
    1294,  1679,   445,    50,   352,  1680,   752,   754,  1949,  1317,
    1318,  1319,  1320,   749,  1649,  1755,  1657,   471,   773,  1667,
    1742,   765,    41,   802,   675,  1750,   470,   471,   472,   473,
     774,   474,   475,   793,   477,    45,   775,   479,   476,   366,
      40,   823,  1419,   368,   477,   478,  1242,   479,   358,    46,
     359,   360,   361,   362,   451,   459,   824,    43,   527,  1292,
     363,   994,   883,    44,  1305,   795,   364,   365,   455,   366,
     350,   412,   456,   420,  1615,   995,   796,   797,   793,  1692,
     457,   361,  1520,  1548,   920,   446,  1521,  1616,   430,   366,
     431,   408,  1693,   432,  1522,    42,   921,    48,  1572,  1588,
     433,   329,   329,   329,   329,   329,   329,   329,   329,   329,
    1573,  1589,   394,   311,  1451,   654,   655,   414,   417,   312,
     654,   655,    47,   453,   466,   654,   655,   654,   655,  1430,
     350,   412,    51,  1347,   654,   655,  1348,  -265,  -265,  -265,
     352,   654,   655,   955,  1445,  1446,   318,   319,   320,   321,
     322,   323,   324,   325,   326,   327,   549,   550,   419,   740,
      -4,    -4,   743,   420,   410,  1802,   415,   418,   750,   444,
     421,  1803,   454,   467,   763,  1804,    53,    54,    37,  1257,
    1258,    38,   677,   678,    39,   679,    52,   680,   681,   682,
     683,   684,   685,   686,   687,   688,   689,   299,   703,   704,
     705,   706,   828,   709,  1723,  1724,   715,   716,   603,   550,
    1725,   425,   429,  1010,  1097,  1012,   465,   318,   319,   320,
     321,   322,   323,   324,   325,   326,   327,   315,  1456,   546,
     547,   548,  1459,   316,  1457,  1873,   276,  1920,  1460,   786,
     300,  1874,   559,  1921,  1370,   302,   777,  1371,   560,  1926,
     561,   562,   563,   564,   565,  1927,   566,   781,   567,   568,
     569,   570,   571,   780,   572,   573,   574,   575,   576,   577,
     578,   579,   580,  1995,   778,   301,   582,   303,   583,  1996,
     798,   585,   657,  1084,   587,   588,   654,   655,   590,   591,
     407,   592,   593,   801,   804,   806,   441,   597,   598,   599,
     304,   600,   601,   602,   318,   690,   691,   692,   693,   694,
     695,   696,   697,   698,   699,   607,   305,   608,   609,   610,
     306,  1375,   612,   613,  1340,   614,   615,   616,   617,  1652,
    1653,  1307,  1308,   621,   622,   623,   624,   625,   626,   627,
     628,   629,   630,   631,  1397,   307,  1098,  1398,   758,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,  1494,
    1673,  1674,  1340,   500,   523,   542,   308,   542,   542,   542,
     542,   542,   542,   542,   542,  1415,   402,   404,  1418,   807,
     808,   318,   690,   691,   692,   693,   694,   695,   696,   697,
     698,   318,   319,   320,   321,   322,   323,   324,   325,   326,
     327,   642,   318,   690,   691,   692,   693,   694,   695,   696,
     697,   698,   310,   277,   727,   729,   309,   993,  1665,   999,
    1000,   313,   314,    53,   350,   400,   405,   408,   412,   528,
    1744,   529,   530,   532,   531,  1015,   533,   534,   536,   535,
     537,   538,   540,   541,   544,   539,   543,   552,   545,   553,
     643,   349,   551,   556,   554,   555,   586,   589,   557,   581,
     584,   594,   558,   611,   604,   810,   701,   596,   606,   619,
     620,  1481,   634,  1058,   635,   637,   595,   605,   618,   701,
     638,   701,   639,  1067,  1068,  1069,  1070,  1071,  1072,  1073,
    1074,  1075,  1076,  1077,  1078,   632,   741,   742,   633,   636,
     640,   641,   644,   701,  1088,  1089,  1090,  1091,   645,   646,
    1578,   701,   647,   648,   649,   650,   651,   666,   789,   790,
     791,   792,  1295,   653,   665,   667,   813,   816,   839,   839,
     669,   652,   671,   674,   673,   672,   843,   844,   845,   668,
     670,   675,   717,   718,   722,   735,   737,   725,   744,   730,
     857,   858,   859,   860,   861,   862,   863,   864,   865,   866,
     867,   868,   869,   870,   736,   328,   330,   331,   332,   333,
     334,   335,   336,   337,   745,   746,   747,   872,   873,   874,
     875,   755,   770,   876,   771,   772,   878,   817,   879,   880,
     818,   793,   819,   820,   884,   885,   821,   822,   825,   826,
     888,   889,   890,   891,   827,   893,   894,   895,   896,   829,
     831,   830,   900,   901,   902,   701,   832,   903,   833,   835,
     834,   836,   842,   841,   846,   847,   908,   848,   909,   849,
     850,   911,   852,   912,   854,   913,   851,   871,   856,   877,
     853,   881,   915,   855,   882,   886,   887,   892,   758,   897,
     898,   923,   924,   925,   926,   927,   928,   929,   930,   931,
     932,   933,   934,   935,   936,   937,   938,   812,   940,   810,
     899,   904,   944,   945,   946,   947,   906,   949,   950,   951,
     952,   905,   953,   954,   907,   910,   914,   916,   917,   918,
     919,   922,   939,   941,  1236,   942,   943,   948,   956,   957,
     958,   960,   961,   959,   962,   963,   964,   965,   966,   967,
     969,   970,   975,   968,   975,   972,   977,   971,   987,   988,
     992,   989,   978,   983,   982,   991,  1279,   329,   329,   329,
     329,   329,   329,   329,   329,   329,   984,   985,   986,   990,
    1011,  1017,  1039,  1022,  1027,  1021,  1033,  1049,  1026,  1038,
    1040,  1048,  1050,  1054,  1051,  1061,  1062,  1023,  1002,  1059,
    1063,  1005,  1006,  1007,  1008,  1064,   701,  1066,   701,  1065,
    1014,  1083,  1085,  1086,  1087,  1100,  1092,  1101,  1102,  1103,
    1104,  1025,  1105,  1107,  1108,  1109,  1111,  1110,  1106,  1112,
    1113,  1117,  1121,  1114,  1122,  1115,  1123,  1116,  1045,  1047,
    1125,  1127,  1126,  1130,  1131,  1132,  1124,  1056,  1128,  1133,
    1129,  1144,  1148,  1145,  1155,  1143,  1149,  1157,  1154,  1156,
    1162,  1161,  1164,  1163,  1168,  1169,  1170,  1165,  1171,  1172,
    1099,  1173,  1080,  1174,  1082,  1191,   701,  1193,  1194,  1200,
    1195,  1208,  1209,  1210,   329,   329,  1211,  1212,   542,  1213,
    1207,  1214,  1218,  1118,  1119,  1120,  1215,  1219,  1220,  1222,
    1223,  1221,  1228,  1229,  1227,  1231,  1233,  1216,  1232,  1246,
    1134,  1217,  1230,  1234,  1235,  1245,  1247,  1135,  1251,  1136,
    1137,  1138,  1252,  1139,  1140,  1259,  1260,  1256,  1141,  1142,
    1261,  1262,  1275,  1274,  1276,  1271,  1273,  1277,  1147,  1281,
    1278,  1315,  1321,  1282,  1152,  1283,  1153,  1284,  1314,  1285,
    1327,  1329,   349,   349,  1331,  1158,  1330,  1158,  1160,  1025,
    1333,  1316,  1337,  1271,  1334,  1271,  1336,  1338,   657,  1166,
    1328,  1167,  1339,  1436,  1340,  1341,   349,  1322,  1324,  1325,
    1324,  1175,  1176,  1177,  1178,  1179,  1180,  1181,  1182,  1183,
    1184,  1185,  1186,  1332,  1188,  1342,  1190,  1343,  1192,  1344,
    1345,  1349,  1196,  1197,  1198,  1199,  1346,  1201,  1202,  1203,
    1204,  1335,  1205,  1206,  1350,  1351,  1357,  1358,  1359,  1361,
    1362,  1368,  1364,  1366,  1372,   810,  1365,  1369,  1376,   349,
     542,   542,   329,  1377,   738,   739,  1374,  1379,  1380,  1384,
    1385,  1391,  1390,  1393,  1392,  1394,  1395,  1399,  1396,  1403,
     762,   349,  1400,  1406,  1056,  1401,  1402,  1404,  1408,  1414,
    1248,  1412,  1405,  1407,  1420,  1422,  1409,  1411,   815,  1410,
    1413,  1435,  1238,  1239,  1240,  1442,  1025,  1243,  1047,  1421,
    1424,  1439,  1428,  1250,  1425,  1427,  1429,  1432,  1440,  1433,
    1434,   837,   837,  1437,  1443,  1270,  1438,  1447,  1448,  1454,
    1453,  1455,  1458,  1056,  1461,  1464,  1462,  1463,  1465,  1466,
    1467,  1287,  1289,  1469,  1287,   701,  1299,  1301,  1468,  1287,
     813,   816,   816,  1270,  1470,  1270,  1471,  1472,  1473,  1474,
    1475,  1476,  1047,  1047,  1047,  1047,  1477,  1479,  1478,  1256,
    1480,  1482,  1483,  1271,  1271,  1484,  1485,  1486,  1495,  1487,
    1491,  1352,  1353,  1489,  1354,  1355,  1356,  1488,  1271,  1271,
    1490,  1492,  1496,  1493,  1498,  1273,  1499,  1502,  1501,  1504,
    1503,  1507,  1509,  1505,   329,   329,   542,  1506,  1511,   953,
     954,  1508,  1510,  1512,  1250,  1514,  1513,  1515,   349,  1516,
    1517,  1519,  1518,  1523,  1373,  1524,  1525,  1526,  1528,  1527,
    1533,  1529,  1378,  1530,  1532,  1534,  1535,  1536,  1537,  1538,
    1539,  1540,  1549,  1554,  1542,  1541,  1546,   349,   349,  1381,
    1543,  1551,  1544,   349,  1547,  1553,  1550,   349,  1552,  1556,
    1557,  1386,  1387,  1388,  1389,  1555,   812,  1559,  1561,  1558,
    1560,  1562,  1563,   349,  1564,  1565,  1566,  1568,  1567,  1569,
    1570,  1571,  1574,  1576,  1580,  1577,   349,  1575,  1579,  1583,
    1581,   812,  1585,  1582,   812,  1590,   812,  1584,  1587,  1586,
    1591,  1592,  1594,  1593,  1423,   974,  1595,   974,  1597,  1599,
    1596,  1598,   542,   542,  1600,  1602,  1601,  1603,  1604,  1605,
    1608,  1606,  1250,   349,  1611,   349,  1607,  1609,   762,  1612,
    1003,  1004,  1610,  1270,  1270,  1613,  1009,   758,  1617,  1614,
    1013,  1618,  1619,  1633,  1289,  1620,  1621,  1299,  1270,  1270,
    1623,  1627,  1289,  1045,   813,  1029,  1629,  1029,  1630,  1158,
    1624,  1632,  1158,  1625,  1626,  1634,  1639,  1042,  1042,  1628,
    1636,   329,   329,  1631,  1635,  1637,   662,  1638,  1640,  1641,
    1642,  1643,  1644,  1645,  1646,  1647,  1650,  1661,  1497,  1651,
    1654,  1658,  1655,  1500,  1656,  1659,  1663,  1660,  1649,  1662,
    1668,  1664,  1079,  1666,  1081,   711,   713,  1670,  1672,  1683,
    1669,  1676,  1671,  1682,  1675,   726,   728,  1677,   731,   732,
     733,   734,  1681,  1686,  1688,  1531,  1684,  1687,  1685,  1690,
    1689,  1691,  1694,  1695,  1696,  1697,  1698,   751,   753,  1706,
    1699,  1700,  1701,  1707,   767,   769,  1702,  1709,  1703,  1705,
    1708,  1716,  1710,  1711,  1712,  1713,  1714,  1715,  1722,  1717,
    1718,  1719,  1731,  1301,  1721,  1726,  1289,  1729,  1727,  1720,
    1728,  1730,  1733,  1735,   812,   812,  1732,  1738,  1734,  1736,
    1737,   349,  1739,  1743,  1740,   349,  1741,  1745,  1746,   812,
     812,  1747,  1749,  1751,  1748,   812,  1753,   349,  1752,   349,
    1756,  1757,  1758,  1754,  1760,  1761,  1759,   349,  1763,  1764,
    1765,  1762,   349,  1767,  1545,  1773,  1792,  1766,  1768,  1770,
    1771,  1769,  1622,  1772,  1776,  1774,  1783,  1775,  1779,  1778,
    1777,  1784,  1785,  1786,  1780,   349,  1782,  1787,  1789,  1788,
    1790,  1791,  1794,  1795,  1793,  1796,  1797,  1800,   349,  1801,
    1799,  1806,  1798,  1807,   349,  1810,   349,  1808,  1809,  1805,
    1816,  1811,  1813,  1812,  1814,  1817,  1827,  1831,  1815,  1828,
    1829,  1830,  1832,  1834,  1835,  1818,  1836,  1837,  1839,  1838,
    1844,  1845,  1986,  1840,  1851,  1847,  1842,  1823,  1056,  1843,
    1848,  1833,  1841,  1846,  1849,  1852,  1858,  1856,  1853,  1855,
    1860,  1850,  1237,  1857,  1854,  1861,  1241,  1862,  1864,  1704,
    1863,  1865,  1866,  1867,  1868,  1869,  1870,  1253,  1255,  1029,
    1029,  1871,  1872,  1876,  1877,  1263,  1875,  1878,  1879,  1882,
    1885,  1880,  1886,  1888,  1883,  1884,  1893,  1887,  1890,  1895,
    1896,  1892,  1897,  1899,  1291,  1911,  1908,  1912,  1900,  1304,
    1901,  1902,   815,   815,  1903,  1310,  1905,  1312,  1881,  1889,
     349,   349,  1907,  1910,  1894,  1823,  1898,  1913,  1914,  1904,
     813,   979,   980,   981,  1915,  1906,  1916,  1918,  1917,  1919,
    1922,  1923,  1924,  1925,  1928,  1929,  1930,  1931,  1781,  1933,
    1932,  1934,  1935,  1909,  1936,  1938,  1939,  1937,  1940,  1942,
    1944,  1950,  1958,  1941,  1016,  1949,  1018,  1019,  1020,  1946,
    1943,  1951,  1945,  1952,  1947,  1948,  1955,  1030,  1954,  1032,
    1953,  1034,  1035,  1036,  1037,  1956,  1957,  1960,  1959,  1961,
    1962,  1963,  1964,  1966,  1967,  1968,  1052,  1053,  1965,  1969,
    1970,  1971,  1972,  1060,  1973,  1974,  1975,  1976,  1977,  1980,
    1983,  1985,  1978,  2018,  1984,  1979,  1981,  1991,  1444,  1450,
    1982,  1326,  1313,  1999,  1990,  1859,  1987,  1992,  1988,  1989,
    1998,  2000,  2001,  1993,  2002,  1994,  1997,  1093,  1094,  1095,
    1096,  2003,  2004,  2005,  2006,  2007,  2008,  2009,  2011,  2014,
    2019,  2010,  2012,  2013,  2021,  2022,  2015,  2025,  2036,  2017,
    2016,  2024,  2026,  2020,  2023,  2028,  2027,  2033,  1891,  2037,
    1452,   812,  2029,  2030,  2031,  2032,  2034,  1431,   805,  1042,
    1416,  1417,  1042,  2035,  1426,   435,   759,   504,   840,     0,
    1255,   782,     0,   505,   317,   506,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   436,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     762,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   437,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   507,     0,     0,     0,     0,   508,
       0,     0,     0,   509,   510,     0,   511,     0,   512,   513,
     514,   515,   516,   517,     0,   518,   519,   524,     0,     0,
       0,     0,     0,   449,   438,     0,   439,  1225,  1226,   338,
      58,    59,    60,    61,    62,   339,   340,   341,   342,   343,
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
     268,   269,   270,   271,   272,   273,   274,   275,   973,   461,
     276,   338,    58,    59,    60,    61,    62,   339,   340,   341,
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
     463,   976,   276,    57,    58,    59,    60,    61,    62,    63,
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
     274,   275,   440,   442,   276,   338,    58,    59,    60,    61,
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
     272,   273,   274,   275,   443,   525,   276,   338,    58,    59,
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
     270,   271,   272,   273,   274,   275,   654,   655,   338,    58,
      59,    60,  1264,  1265,    63,    64,    65,    66,    67,    68,
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
     269,   270,   271,   272,   273,   274,   275,   654,   655,   338,
      58,    59,    60,    61,    62,   339,   340,   341,   342,   343,
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
     268,   269,   270,   271,   272,   273,   274,   275,   338,    58,
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
     269,   270,   271,   272,   273,   274,   275,   338,  1151,    59,
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
     270,   271,   272,   273,   274,   275,   338,  1159,    59,    60,
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
     271,   272,   273,   274,   275,   338,  1187,    59,    60,    61,
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
     272,   273,   274,   275,   338,  1189,    59,    60,    61,    62,
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
     273,   274,   275,   338,  1363,    59,    60,    61,    62,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,    73,
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
     274,   275,   338,  1367,    59,    60,    61,    62,   339,   340,
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
     275,   338,  1382,    59,    60,    61,    62,   339,   340,   341,
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
     338,  1383,    59,    60,    61,    62,   339,   340,   341,   342,
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
     267,   268,   269,   270,   271,   272,   273,   274,   275
};

static const yytype_int16 yycheck[] =
{
      16,   912,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,   861,
    1184,   630,    16,   295,  1118,   290,   291,   890,     5,   283,
     297,   297,    24,   297,   901,    32,   583,    24,   585,  1023,
     294,   295,   290,   291,  1248,    32,     1,    32,     3,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    36,  1187,
     607,  1189,    33,    34,    19,  1142,    21,    22,   615,    24,
      25,  1378,    37,  1167,    37,    30,    31,    37,    37,  1386,
      35,    36,    37,    37,    39,   578,   570,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    23,    21,    22,
      22,   585,    27,   283,    21,    22,    22,   287,    21,    22,
      32,    34,   292,    39,    31,    38,   609,   610,    43,  1196,
    1197,  1198,  1199,   607,    89,    38,    89,    20,    19,    89,
      89,   615,    27,    22,    27,    89,    19,    20,    21,    22,
      31,    24,    25,    32,    37,    19,    37,    40,    31,    40,
      23,    22,  1356,   283,    37,    38,  1140,    40,    19,    33,
      21,    22,    23,    24,   294,   295,    37,    27,   298,  1178,
      31,    20,   719,    33,  1183,    19,    37,    38,    19,    40,
      21,    22,    23,    24,    23,    34,    30,    31,    32,    23,
      31,    23,    19,  1500,    27,    27,    23,    36,    19,    40,
      21,    22,    36,    24,    31,    23,    39,    23,    22,    22,
      31,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      34,    34,   283,    31,  1388,   222,   223,   288,   289,    37,
     222,   223,    39,   294,   295,   222,   223,   222,   223,  1367,
      21,    22,    32,    34,   222,   223,    37,   224,   225,   226,
      31,   222,   223,     6,  1382,  1383,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    39,    40,    19,   599,
     225,   226,   602,    24,   287,    21,   288,   289,   608,   292,
      31,    27,   294,   295,   614,    31,   225,   226,    30,  1152,
    1153,    33,   559,   559,    36,   559,     0,   560,   561,   562,
     563,   564,   565,   566,   567,   568,   569,    22,   571,   572,
     573,   574,   642,   576,    21,    22,   579,   580,    39,    40,
      27,   290,   291,   870,     6,   872,   295,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    31,    21,   355,
     356,   357,    21,    37,    27,    21,   224,    21,    27,   621,
      23,    27,   368,    27,    34,    23,   621,    37,   374,    21,
     376,   377,   378,   379,   380,    27,   382,   621,   384,   385,
     386,   387,   388,   621,   390,   391,   392,   393,   394,   395,
     396,   397,   398,    21,   621,    34,   402,    37,   404,    27,
     627,   407,   546,   940,   410,   411,   222,   223,   414,   415,
     286,   417,   418,   627,   628,   629,   292,   423,   424,   425,
      32,   427,   428,   429,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,   441,    38,   443,   444,   445,
      37,    34,   448,   449,    37,   451,   452,   453,   454,    21,
      22,  1185,  1186,   459,   460,   461,   462,   463,   464,   465,
     466,   467,   468,   469,    34,    19,     6,    37,   612,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    34,
      21,    22,    37,   296,   297,   328,    34,   330,   331,   332,
     333,   334,   335,   336,   337,  1352,   284,   285,  1355,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,   527,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    27,    16,   587,   588,    40,   857,  1622,   859,
     860,    38,    20,   225,    21,    31,    31,    22,    22,    19,
    1704,    43,    19,    22,    38,   875,    38,    22,    38,    23,
      33,    23,    19,    39,    20,    37,    26,    20,    27,    32,
      36,   277,    26,    23,    42,    27,    20,    20,    33,    27,
      27,    39,    33,    32,    26,  1184,   570,    27,    27,    21,
      27,  1423,    26,   913,    20,    30,    42,    42,    39,   583,
      27,   585,    38,   923,   924,   925,   926,   927,   928,   929,
     930,   931,   932,   933,   934,    39,   600,   601,    39,    42,
      33,    33,    38,   607,   944,   945,   946,   947,    36,    40,
    1531,   615,    38,    21,    34,    20,    19,    19,   622,   623,
     624,   625,  1179,    22,    22,    19,   630,   631,   654,   655,
      25,    89,    22,    30,    38,    36,   662,   663,   664,    89,
      89,    27,    22,    32,    22,    22,    22,    89,    22,    89,
     676,   677,   678,   679,   680,   681,   682,   683,   684,   685,
     686,   687,   688,   689,    89,   690,   691,   692,   693,   694,
     695,   696,   697,   698,    19,    89,    22,   703,   704,   705,
     706,    37,    22,   709,    26,    22,   712,    22,   714,   715,
      24,    32,    19,    89,   720,   721,    89,    33,    36,    38,
     726,   727,   728,   729,    27,   731,   732,   733,   734,    23,
      23,    33,   738,   739,   740,   719,    36,   743,    37,    27,
      32,    27,    33,    30,    27,    27,   752,    32,   754,    27,
      27,   757,    27,   759,    19,   761,    37,    30,    32,    23,
      40,    27,   768,    39,    33,    27,    27,    27,   912,    27,
      37,   777,   778,   779,   780,   781,   782,   783,   784,   785,
     786,   787,   788,   789,   790,   791,   792,   630,   794,  1388,
      27,    27,   798,   799,   800,   801,    37,   803,   804,   805,
     806,    32,   807,   808,    27,    38,    33,    27,    33,    27,
      39,    33,    19,    39,  1134,    23,    27,    23,    27,    24,
      32,    37,    20,    27,    27,    21,    23,    19,    21,    43,
      21,    32,   838,    27,   840,    89,    19,    32,    23,    89,
      24,    23,    32,    30,    33,    31,  1166,   690,   691,   692,
     693,   694,   695,   696,   697,   698,    32,    32,    32,    30,
      30,    21,    23,    32,    32,    89,    32,    32,    89,    33,
      89,    33,    23,    36,    89,    33,    89,   883,   862,    36,
      22,   865,   866,   867,   868,    22,   870,    30,   872,    38,
     874,    31,    22,    40,    22,    33,    37,    23,    32,    32,
      23,   885,    19,    23,    19,    30,    20,    23,    89,    36,
      23,    89,    89,    37,    19,    27,    23,    38,   902,   903,
      23,    27,    32,    23,    33,    43,    37,   911,    36,    23,
      89,    27,    27,    89,    89,    39,    37,    27,    37,    32,
      23,    89,    27,    32,    21,    89,    27,    39,    27,    27,
     955,    23,   936,    33,   938,    23,   940,    27,    23,    21,
      27,    36,    23,    37,   807,   808,    32,    30,   811,    27,
      89,    30,    23,   979,   980,   981,    31,    27,    30,    32,
      36,    38,    20,    30,    33,    22,    40,    89,    32,    32,
     996,    89,    38,    38,    36,    36,    31,  1003,    32,  1005,
    1006,  1007,    38,  1009,  1010,    38,    33,  1151,  1014,  1015,
      22,    32,    30,    33,    22,  1159,  1160,    32,  1024,    23,
      31,    30,    36,    33,  1030,    32,  1032,    33,    33,    89,
      33,    30,   738,   739,    22,  1041,    38,  1043,  1044,  1023,
      32,    89,    21,  1187,    30,  1189,    40,    20,  1192,  1055,
      89,  1057,    36,  1373,    37,    23,   762,  1201,  1202,  1203,
    1204,  1067,  1068,  1069,  1070,  1071,  1072,  1073,  1074,  1075,
    1076,  1077,  1078,    89,  1080,    39,  1082,    30,  1084,    37,
      36,    33,  1088,  1089,  1090,  1091,    37,  1093,  1094,  1095,
    1096,    89,  1097,  1098,    23,    21,    37,    37,    33,    37,
      36,     5,    36,    34,    23,  1704,    39,    39,    89,   815,
     953,   954,   955,    27,   597,   598,    39,    23,    33,    89,
      21,    39,    27,    89,    24,    36,    89,    19,    27,    23,
     613,   837,    21,    21,  1118,    33,    33,    39,    23,    23,
    1146,    27,    38,    38,    27,    22,    39,    38,   631,    39,
      37,    32,  1136,  1137,  1138,    24,  1140,  1141,  1142,    38,
      38,    33,    38,  1147,    39,    39,    39,    38,    32,    39,
      38,   654,   655,    38,    32,  1159,    39,    33,    33,    38,
      34,    27,    39,  1167,    32,    32,    39,    38,    33,    27,
      39,  1175,  1176,    36,  1178,  1179,  1180,  1181,    31,  1183,
    1184,  1185,  1186,  1187,    39,  1189,    34,    89,    31,    38,
      36,    21,  1196,  1197,  1198,  1199,    32,    36,    40,  1363,
      19,    36,    31,  1367,  1368,    31,    34,    38,    19,    34,
      34,  1237,  1238,    36,  1240,  1241,  1242,    38,  1382,  1383,
      38,    38,    23,    39,    39,  1389,    32,    34,    38,    33,
      30,    33,    24,    32,  1097,  1098,  1099,    31,    36,  1264,
    1265,    32,    38,    23,  1248,    21,    39,    32,   974,    23,
      39,    39,    36,    23,  1280,    89,    39,    23,    23,    38,
      23,    39,  1288,    30,    39,    23,    39,    89,    39,    89,
      39,    39,    27,    23,    38,    89,    38,  1003,  1004,  1305,
      39,    30,    39,  1009,    38,    24,    39,  1013,    39,    24,
      33,  1317,  1318,  1319,  1320,    39,  1159,    39,    32,    89,
      33,    23,    38,  1029,    32,    31,    37,    39,    38,    32,
      27,    32,    31,    19,    32,    31,  1042,    89,    31,    22,
      32,  1184,    22,    38,  1187,    34,  1189,    38,    38,    31,
      38,    30,    36,    34,  1360,   838,    33,   840,    32,    32,
      38,    33,  1205,  1206,    32,    22,    33,    31,    39,    38,
      23,    89,  1356,  1079,    22,  1081,    38,    27,   861,    25,
     863,   864,    89,  1367,  1368,    22,   869,  1531,    33,    38,
     873,    23,    21,    33,  1378,    25,    23,  1381,  1382,  1383,
      23,    23,  1386,  1387,  1388,   888,    23,   890,    23,  1415,
      38,    23,  1418,    38,    89,    39,    32,   900,   901,    89,
      38,  1264,  1265,    89,    89,    39,   548,    33,    89,    38,
      38,    38,    23,    23,    37,    21,    32,    32,  1444,    40,
      27,    40,    27,  1449,    27,    27,    23,    36,    89,    33,
      22,    32,   935,    32,   937,   577,   578,    22,    32,    22,
      40,    36,    40,    30,    40,   587,   588,    38,   590,   591,
     592,   593,    38,    32,    22,  1481,    89,    33,    40,    23,
      38,    26,    33,    32,    89,    22,    27,   609,   610,    22,
      40,    38,    38,    23,   616,   617,    39,    23,    38,    38,
      27,    89,    27,    38,    26,    23,    27,    38,    23,    26,
      33,    43,    19,  1497,    30,    27,  1500,    27,    38,    89,
      39,    89,    27,    23,  1367,  1368,    40,    21,    89,    27,
      27,  1237,    23,    32,    89,  1241,    37,    27,    40,  1382,
    1383,    21,    21,    19,    40,  1388,    21,  1253,    40,  1255,
      19,    36,    34,    21,    40,    33,    23,  1263,    32,    21,
      89,    27,  1268,    36,  1497,    37,    43,    32,    31,    27,
      40,    32,  1578,    33,    23,    32,    27,    36,    31,    34,
      36,    23,    27,    23,    38,  1291,    36,    31,    27,    32,
      23,    26,    38,    23,    32,    36,    27,    24,  1304,    23,
      36,    23,    39,    19,  1310,    23,  1312,    32,    21,    38,
      19,    39,    23,    34,    37,    19,    23,    32,    89,    21,
      21,    19,    21,    19,    34,    89,    32,    21,    23,    32,
      19,    21,    40,    33,    39,    23,    33,  1781,  1622,    32,
      23,    89,    89,    34,    36,    21,    23,    31,    34,    34,
      21,    38,  1135,    32,    36,    23,  1139,    23,    23,  1665,
      34,    23,    34,    32,    23,    23,    23,  1150,  1151,  1152,
    1153,    38,    21,    24,    34,  1158,    39,    38,    30,    34,
      19,    37,    19,    19,    38,    38,    30,    37,    36,    19,
      32,    38,    30,    38,  1177,    36,    39,    31,    33,  1182,
      32,    32,  1185,  1186,    33,  1188,    33,  1190,    89,    89,
    1416,  1417,    34,    33,    89,  1859,    89,    42,    22,    89,
    1704,   843,   844,   845,    37,    89,    33,    36,    34,    23,
      33,    39,    24,    38,    36,    34,    19,    38,  1744,    36,
      22,    19,    23,    89,    23,    36,    19,    27,    19,    33,
      36,    19,    37,    30,   876,    43,   878,   879,   880,    33,
      32,    36,    32,    89,    33,    32,    31,   889,    27,   891,
      36,   893,   894,   895,   896,    38,    31,    31,    36,    39,
      24,    43,    38,    24,    36,    19,   908,   909,    39,    22,
      27,    23,    23,   915,    23,    19,    38,    19,    23,    89,
      19,    36,    32,    39,    31,    33,    32,    23,  1381,  1387,
      33,  1204,  1192,    23,    32,  1821,    37,    31,    38,    36,
      31,    27,    23,    38,    23,    38,    38,   949,   950,   951,
     952,    22,    32,    23,    23,    33,    32,    23,    40,    89,
      24,    38,    36,    36,    23,    23,    38,    23,    30,    36,
      38,    26,    32,    38,    37,    23,    33,    38,  1859,    22,
    1389,  1704,    36,    36,    33,    36,    36,  1368,   629,  1352,
    1353,  1354,  1355,    37,  1363,   292,   612,   297,   655,    -1,
    1363,   621,    -1,   297,    56,   297,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   292,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1423,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   292,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   297,    -1,    -1,    -1,    -1,   297,
      -1,    -1,    -1,   297,   297,    -1,   297,    -1,   297,   297,
     297,   297,   297,   297,    -1,   297,   297,   297,    -1,    -1,
      -1,    -1,    -1,   293,   292,    -1,   292,  1119,  1120,     3,
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
     214,   215,   216,   217,   218,   219,   220,   221,   222,   295,
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
     295,   223,   224,     3,     4,     5,     6,     7,     8,     9,
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
     220,   221,   292,   292,   224,     3,     4,     5,     6,     7,
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
     218,   219,   220,   221,   292,   297,   224,     3,     4,     5,
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
     216,   217,   218,   219,   220,   221,   222,   223,     3,     4,
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
     213,   214,   215,   216,   217,   218,   219,   220,   221
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     1,     3,    19,    21,    22,    24,    25,    30,    31,
      35,    36,    37,    39,   228,   229,   230,   231,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     309,   310,   311,   312,   387,   391,    22,    30,    33,    36,
      23,    27,    23,    27,    33,    19,    33,    39,    23,    23,
      39,    32,     0,   225,   226,   291,   292,     3,     4,     5,
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
     216,   217,   218,   219,   220,   221,   224,   282,   285,   286,
     287,   290,   290,   290,   290,   290,   290,   290,   290,   290,
     290,   290,   290,   290,   290,   290,   290,   290,   290,    22,
      23,    34,    23,    37,    32,    38,    37,    19,    34,    40,
      27,    31,    37,    38,    20,    31,    37,   291,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,   284,   285,
     284,   284,   284,   284,   284,   284,   284,   284,     3,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,   287,
      21,    22,    31,   232,   313,   361,   371,   373,    19,    21,
      22,    23,    24,    31,    37,    38,    40,   238,   313,   314,
     315,   316,   337,   338,   341,   346,   347,   348,   349,   350,
     351,   353,   355,   356,   357,   358,   359,   360,   361,   362,
     363,   364,   369,   370,   371,   372,   373,   374,   380,   381,
      31,   235,   359,   236,   359,    31,   242,   360,    22,   243,
     372,   373,    22,   244,   371,   374,   245,   371,   374,    19,
      24,    31,   240,   347,   357,   369,   246,   347,   357,   369,
      19,    21,    24,    31,   252,   314,   315,   316,   346,   353,
     356,   360,   362,   370,   372,   373,    27,   247,   340,   341,
     237,   313,   361,   371,   374,    19,    23,    31,   239,   313,
     345,   350,   354,   355,   361,   369,   371,   374,   381,   390,
      19,    20,    21,    22,    24,    25,    31,    37,    38,    40,
     233,   318,   319,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   332,   333,   334,   335,   336,
     337,   339,   388,   234,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   327,   328,   329,   330,   331,   332,   333,
     334,   335,   336,   337,   339,   388,   241,   313,    19,    43,
      19,    38,    22,    38,    22,    23,    38,    33,    23,    37,
      19,    39,   285,    26,    20,    27,   290,   290,   290,    39,
      40,    26,    20,    32,    42,    27,    23,    33,    33,   290,
     290,   290,   290,   290,   290,   290,   290,   290,   290,   290,
     290,   290,   290,   290,   290,   290,   290,   290,   290,   290,
     290,    27,   290,   290,    27,   290,    20,   290,   290,    20,
     290,   290,   290,   290,    39,    42,    27,   290,   290,   290,
     290,   290,   290,    39,    26,    42,    27,   290,   290,   290,
     290,    32,   290,   290,   290,   290,   290,   290,    39,    21,
      27,   290,   290,   290,   290,   290,   290,   290,   290,   290,
     290,   290,    39,    39,    26,    20,    42,    30,    27,    38,
      33,    33,   290,    36,    38,    36,    40,    38,    21,    34,
      20,    19,    89,    22,   222,   223,   274,   289,   271,   289,
      24,    32,   271,   377,   379,    22,    19,    19,    89,    25,
      89,    22,    36,    38,    30,    27,   317,   334,   335,   336,
     317,   317,   317,   317,   317,   317,   317,   317,   317,   317,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
     262,   286,   305,   317,   317,   317,   317,   267,   286,   317,
      36,   271,   378,   271,   378,   317,   317,    22,    32,   249,
     308,   262,    22,   262,   305,    89,   271,   379,   271,   379,
      89,   271,   271,   271,   271,    22,    89,    22,   282,   282,
     267,   286,   286,   267,    22,    19,    89,    22,   262,   305,
     267,   271,   378,   271,   378,    37,   253,   273,   289,   308,
     254,   270,   282,   267,   262,   305,    24,   271,   376,   271,
      22,    26,    22,    19,    31,    37,   248,   347,   351,   352,
     357,   361,   364,   365,   366,   367,   381,   383,   384,   286,
     286,   286,   286,    32,   389,    19,    30,    31,   351,   368,
     382,   389,    22,   375,   389,   375,   389,     7,     8,   266,
     283,   284,   285,   286,   281,   282,   286,    22,    24,    19,
      89,    89,    33,    22,    37,    36,    38,    27,   267,    23,
      33,    23,    36,    37,    32,    27,    27,   282,   288,   290,
     288,    30,    33,   290,   290,   290,    27,    27,    32,    27,
      27,    37,    27,    40,    19,    39,    32,   290,   290,   290,
     290,   290,   290,   290,   290,   290,   290,   290,   290,   290,
     290,    30,   290,   290,   290,   290,   290,    23,   290,   290,
     290,    27,    33,   262,   290,   290,    27,    27,   290,   290,
     290,   290,    27,   290,   290,   290,   290,    27,    37,    27,
     290,   290,   290,   290,    27,    32,    37,    27,   290,   290,
      38,   290,   290,   290,    33,   290,    27,    33,    27,    39,
      27,    39,    33,   290,   290,   290,   290,   290,   290,   290,
     290,   290,   290,   290,   290,   290,   290,   290,   290,    19,
     290,    39,    23,    27,   290,   290,   290,   290,    23,   290,
     290,   290,   290,   284,   284,     6,    27,    24,    32,    27,
      37,    20,    27,    21,    23,    19,    21,    43,    27,    21,
      32,    32,    89,   222,   282,   290,   223,    19,    32,   271,
     271,   271,    33,    30,    32,    32,    32,    23,    89,    23,
      30,    31,    24,   267,    20,    34,   251,   385,   386,   267,
     267,   270,   286,   282,   282,   286,   286,   286,   286,   282,
     262,    30,   262,   282,   286,   267,   271,    21,   271,   271,
     271,    89,    32,   290,   263,   286,    89,    32,   279,   282,
     271,   279,   271,    32,   271,   271,   271,   271,    33,    23,
      89,   250,   282,   250,   265,   286,   269,   286,    33,    32,
      23,    89,   271,   271,    36,   268,   286,   273,   267,    36,
     271,    33,    89,    22,    22,    38,    30,   267,   267,   267,
     267,   267,   267,   267,   267,   267,   267,   267,   267,   282,
     286,   282,   286,    31,   262,    22,    40,    22,   267,   267,
     267,   267,    37,   271,   271,   271,   271,     6,     6,   284,
      33,    23,    32,    32,    23,    19,    89,    23,    19,    30,
      23,    20,    36,    23,    37,    27,    38,    89,   290,   290,
     290,    89,    19,    23,    37,    23,    32,    27,    36,    89,
      23,    33,    43,    23,   290,   290,   290,   290,   290,   290,
     290,   290,   290,    39,    27,    89,   263,   290,    27,    37,
     290,     4,   290,   290,    37,    89,    32,    27,   290,     4,
     290,    89,    23,    32,    27,    39,   290,   290,    21,    89,
      27,    27,    27,    23,    33,   290,   290,   290,   290,   290,
     290,   290,   290,   290,   290,   290,   290,     4,   290,     4,
     290,    23,   290,    27,    23,    27,   290,   290,   290,   290,
      21,   290,   290,   290,   290,   284,   284,    89,    36,    23,
      37,    32,    30,    27,    30,    31,    89,    89,    23,    27,
      30,    38,    32,    36,   268,   271,   271,    33,    20,    30,
      38,    22,    32,    40,    38,    36,   267,   282,   286,   286,
     286,   282,   263,   286,   269,    36,    32,    31,   290,   264,
     286,    32,    38,   282,   280,   282,   289,   279,   279,    38,
      33,    22,    32,   282,     7,     8,   277,   278,   282,   283,
     286,   289,   276,   289,    33,    30,    22,    32,    31,   267,
     268,    23,    33,    32,    33,    89,   256,   286,   257,   286,
     258,   282,   256,    22,    32,   262,   306,   307,   259,   286,
     260,   286,   305,   261,   282,   256,   266,   281,   281,   277,
     282,   277,   282,   274,    33,    30,    89,   269,   269,   269,
     269,    36,   289,   272,   289,   289,   272,    33,    89,    30,
      38,    22,    89,    32,    30,    89,    40,    21,    20,    36,
      37,    23,    39,    30,    37,    36,    37,    34,    37,    33,
      23,    21,   290,   290,   290,   290,   290,    37,    37,    33,
     264,    37,    36,     4,    36,    39,    34,     4,     5,    39,
      34,    37,    23,   290,    39,    34,    89,    27,   290,    23,
      33,   290,     4,     4,    89,    21,   290,   290,   290,   290,
      27,    39,    24,    89,    36,    89,    27,    34,    37,    19,
      21,    33,    33,    23,    39,    38,    21,    38,    23,    39,
      39,    38,    27,    37,    23,   250,   282,   282,   250,   264,
      27,    38,    22,   290,    38,    39,   280,    39,    38,    39,
     277,   278,    38,    39,    38,    32,   267,    38,    39,    33,
      32,   257,    24,    32,   259,   277,   277,    33,    33,   257,
     265,   266,   276,    34,    38,    27,    21,    27,    39,    21,
      27,    32,    39,    38,    32,    33,    27,    39,    31,    36,
      39,    34,    89,    31,    38,    36,    21,    32,    40,    36,
      19,   270,    36,    31,    31,    34,    38,    34,    38,    36,
      38,    34,    38,    39,    34,    19,    23,   290,    39,    32,
     290,    38,    34,    30,    33,    32,    31,    33,    32,    24,
      38,    36,    23,    39,    21,    32,    23,    39,    36,    39,
      19,    23,    31,    23,    89,    39,    23,    38,    23,    39,
      30,   290,    39,    23,    23,    39,    89,    39,    89,    39,
      39,    89,    38,    39,    39,   260,    38,    38,   257,    27,
      39,    30,    39,    24,    23,    39,    24,    33,    89,    39,
      33,    32,    23,    38,    32,    31,    37,    38,    39,    32,
      27,    32,    22,    34,    31,    89,    19,    31,   273,    31,
      32,    32,    38,    22,    38,    22,    31,    38,    22,    34,
      34,    38,    30,    34,    36,    33,    38,    32,    33,    32,
      32,    33,    22,    31,    39,    38,    89,    38,    23,    27,
      89,    22,    25,    22,    38,    23,    36,    33,    23,    21,
      25,    23,   290,    23,    38,    38,    89,    23,    89,    23,
      23,    89,    23,    33,    39,    89,    38,    39,    33,    32,
      89,    38,    38,    38,    23,    23,    37,    21,    37,    89,
      32,    40,    21,    22,    27,    27,    27,    89,    40,    27,
      36,    32,    33,    23,    32,   268,    32,    89,    22,    40,
      22,    40,    32,    21,    22,    40,    36,    38,    21,    34,
      38,    38,    30,    22,    89,    40,    32,    33,    22,    38,
      23,    26,    23,    36,    33,    32,    89,    22,    27,    40,
      38,    38,    39,    38,   290,    38,    22,    23,    27,    23,
      27,    38,    26,    23,    27,    38,    89,    26,    33,    43,
      89,    30,    23,    21,    22,    27,    27,    38,    39,    27,
      89,    19,    40,    27,    89,    23,    27,    27,    21,    23,
      89,    37,    89,    32,   266,    27,    40,    21,    40,    21,
      89,    19,    40,    21,    21,    38,    19,    36,    34,    23,
      40,    33,    27,    32,    21,    89,    32,    36,    31,    32,
      27,    40,    33,    37,    32,    36,    23,    36,    34,    31,
      38,   290,    36,    27,    23,    27,    23,    31,    32,    27,
      23,    26,    43,    32,    38,    23,    36,    27,    39,    36,
      24,    23,    21,    27,    31,    38,    23,    19,    32,    21,
      23,    39,    34,    23,    37,    89,    19,    19,    89,    33,
      34,   255,   275,   289,   342,   343,   344,    23,    21,    21,
      19,    32,    21,    89,    19,    34,    32,    21,    32,    23,
      33,    89,    33,    32,    19,    21,    34,    23,    23,    36,
      38,    39,    21,    34,    36,    34,    31,    32,    23,   290,
      21,    23,    23,    34,    23,    23,    34,    32,    23,    23,
      23,    38,    21,    21,    27,    39,    24,    34,    38,    30,
      37,    89,    34,    38,    38,    19,    19,    37,    19,    89,
      36,   275,    38,    30,    89,    19,    32,    30,    89,    38,
      33,    32,    32,    33,    89,    33,    89,    34,    39,    89,
      33,    36,    31,    42,    22,    37,    33,    34,    36,    23,
      21,    27,    33,    39,    24,    38,    21,    27,    36,    34,
      19,    38,    22,    36,    19,    23,    23,    27,    36,    19,
      19,    30,    33,    32,    36,    32,    33,    33,    32,    43,
      19,    36,    89,    36,    27,    31,    38,    31,    37,    36,
      31,    39,    24,    43,    38,    39,    24,    36,    19,    22,
      27,    23,    23,    23,    19,    38,    19,    23,    32,    33,
      89,    32,    33,    19,    31,    36,    40,    37,    38,    36,
      32,    23,    31,    38,    38,    21,    27,    38,    31,    23,
      27,    23,    23,    22,    32,    23,    23,    33,    32,    23,
      38,    40,    36,    36,    89,    38,    38,    36,    39,    24,
      38,    23,    23,    37,    26,    23,    32,    33,    23,    36,
      36,    33,    36,    38,    36,    37,    30,    22
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
    { (yyval.String) = LSCPSERVER->AddDbInstrumentsFlat((yyvsp[(5) - (7)].String),(yyvsp[(7) - (7)].String));         }
    break;

  case 35:
#line 138 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddDbInstrumentsNonrecursive((yyvsp[(5) - (7)].String),(yyvsp[(7) - (7)].String)); }
    break;

  case 36:
#line 139 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddDbInstruments((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].String));             }
    break;

  case 37:
#line 140 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddDbInstruments((yyvsp[(3) - (7)].String),(yyvsp[(5) - (7)].String),(yyvsp[(7) - (7)].Number));          }
    break;

  case 38:
#line 141 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddMidiInstrumentMap();                }
    break;

  case 39:
#line 142 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddMidiInstrumentMap((yyvsp[(3) - (3)].String));              }
    break;

  case 40:
#line 145 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_audio_device_count);   }
    break;

  case 41:
#line 146 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_audio_device_info);    }
    break;

  case 42:
#line 147 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_device_count);    }
    break;

  case 43:
#line 148 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_device_info);     }
    break;

  case 44:
#line 149 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_channel_count);        }
    break;

  case 45:
#line 150 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_voice_count);          }
    break;

  case 46:
#line 151 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_stream_count);         }
    break;

  case 47:
#line 152 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_buffer_fill);          }
    break;

  case 48:
#line 153 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_channel_info);         }
    break;

  case 49:
#line 154 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_fx_send_count);        }
    break;

  case 50:
#line 155 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_fx_send_info);         }
    break;

  case 51:
#line 156 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_instr_map_count); }
    break;

  case 52:
#line 157 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_instr_map_info);  }
    break;

  case 53:
#line 158 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_instr_count);     }
    break;

  case 54:
#line 159 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_instr_info);      }
    break;

  case 55:
#line 160 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_db_instr_dir_count);   }
    break;

  case 56:
#line 161 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_db_instr_dir_info);    }
    break;

  case 57:
#line 162 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_db_instr_count);       }
    break;

  case 58:
#line 163 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_db_instr_info);        }
    break;

  case 59:
#line 164 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_misc);                 }
    break;

  case 60:
#line 165 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_total_voice_count);    }
    break;

  case 61:
#line 166 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_global_info);          }
    break;

  case 62:
#line 169 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_audio_device_count);   }
    break;

  case 63:
#line 170 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_audio_device_info);    }
    break;

  case 64:
#line 171 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_device_count);    }
    break;

  case 65:
#line 172 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_device_info);     }
    break;

  case 66:
#line 173 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_channel_count);        }
    break;

  case 67:
#line 174 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_voice_count);          }
    break;

  case 68:
#line 175 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_stream_count);         }
    break;

  case 69:
#line 176 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_buffer_fill);          }
    break;

  case 70:
#line 177 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_channel_info);         }
    break;

  case 71:
#line 178 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_fx_send_count);        }
    break;

  case 72:
#line 179 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_fx_send_info);         }
    break;

  case 73:
#line 180 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_instr_map_count); }
    break;

  case 74:
#line 181 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_instr_map_info);  }
    break;

  case 75:
#line 182 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_instr_count);     }
    break;

  case 76:
#line 183 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_instr_info);      }
    break;

  case 77:
#line 184 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_db_instr_dir_count);   }
    break;

  case 78:
#line 185 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_db_instr_dir_info);    }
    break;

  case 79:
#line 186 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_db_instr_count);       }
    break;

  case 80:
#line 187 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_db_instr_info);        }
    break;

  case 81:
#line 188 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_misc);                 }
    break;

  case 82:
#line 189 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_total_voice_count);    }
    break;

  case 83:
#line 190 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_global_info);          }
    break;

  case 84:
#line 193 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping((yyvsp[(4) - (16)].Number),(yyvsp[(6) - (16)].Number),(yyvsp[(8) - (16)].Number),(yyvsp[(10) - (16)].String),(yyvsp[(12) - (16)].String),(yyvsp[(14) - (16)].Number),(yyvsp[(16) - (16)].Dotnum),MidiInstrumentMapper::VOID,"",(yyvsp[(3) - (16)].Bool)); }
    break;

  case 85:
#line 194 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping((yyvsp[(4) - (18)].Number),(yyvsp[(6) - (18)].Number),(yyvsp[(8) - (18)].Number),(yyvsp[(10) - (18)].String),(yyvsp[(12) - (18)].String),(yyvsp[(14) - (18)].Number),(yyvsp[(16) - (18)].Dotnum),(yyvsp[(18) - (18)].LoadMode),"",(yyvsp[(3) - (18)].Bool)); }
    break;

  case 86:
#line 195 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping((yyvsp[(4) - (18)].Number),(yyvsp[(6) - (18)].Number),(yyvsp[(8) - (18)].Number),(yyvsp[(10) - (18)].String),(yyvsp[(12) - (18)].String),(yyvsp[(14) - (18)].Number),(yyvsp[(16) - (18)].Dotnum),MidiInstrumentMapper::VOID,(yyvsp[(18) - (18)].String),(yyvsp[(3) - (18)].Bool)); }
    break;

  case 87:
#line 196 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping((yyvsp[(4) - (20)].Number),(yyvsp[(6) - (20)].Number),(yyvsp[(8) - (20)].Number),(yyvsp[(10) - (20)].String),(yyvsp[(12) - (20)].String),(yyvsp[(14) - (20)].Number),(yyvsp[(16) - (20)].Dotnum),(yyvsp[(18) - (20)].LoadMode),(yyvsp[(20) - (20)].String),(yyvsp[(3) - (20)].Bool)); }
    break;

  case 88:
#line 199 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveMIDIInstrumentMapping((yyvsp[(3) - (7)].Number),(yyvsp[(5) - (7)].Number),(yyvsp[(7) - (7)].Number)); }
    break;

  case 89:
#line 202 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveChannel((yyvsp[(3) - (3)].Number));                     }
    break;

  case 90:
#line 203 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveMidiInstrumentMap((yyvsp[(3) - (3)].Number));           }
    break;

  case 91:
#line 204 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveAllMidiInstrumentMaps();         }
    break;

  case 92:
#line 205 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveDbInstrumentDirectory((yyvsp[(5) - (5)].String), true); }
    break;

  case 93:
#line 206 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveDbInstrumentDirectory((yyvsp[(3) - (3)].String));       }
    break;

  case 94:
#line 207 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveDbInstrument((yyvsp[(3) - (3)].String));                }
    break;

  case 95:
#line 210 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAvailableEngines();                          }
    break;

  case 96:
#line 211 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAvailableMidiInputDrivers();                 }
    break;

  case 97:
#line 212 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDriverInfo((yyvsp[(5) - (5)].String));                     }
    break;

  case 98:
#line 213 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDriverParameterInfo((yyvsp[(5) - (7)].String), (yyvsp[(7) - (7)].String));        }
    break;

  case 99:
#line 214 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDriverParameterInfo((yyvsp[(5) - (9)].String), (yyvsp[(7) - (9)].String), (yyvsp[(9) - (9)].KeyValList));    }
    break;

  case 100:
#line 215 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAvailableAudioOutputDrivers();               }
    break;

  case 101:
#line 216 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDriverInfo((yyvsp[(5) - (5)].String));                   }
    break;

  case 102:
#line 217 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDriverParameterInfo((yyvsp[(5) - (7)].String), (yyvsp[(7) - (7)].String));      }
    break;

  case 103:
#line 218 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDriverParameterInfo((yyvsp[(5) - (9)].String), (yyvsp[(7) - (9)].String), (yyvsp[(9) - (9)].KeyValList));  }
    break;

  case 104:
#line 219 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDeviceCount();                    }
    break;

  case 105:
#line 220 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDeviceCount();                      }
    break;

  case 106:
#line 221 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDeviceInfo((yyvsp[(5) - (5)].Number));                   }
    break;

  case 107:
#line 222 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDeviceInfo((yyvsp[(5) - (5)].Number));                     }
    break;

  case 108:
#line 223 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputPortInfo((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number));                   }
    break;

  case 109:
#line 224 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputPortParameterInfo((yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].Number), (yyvsp[(9) - (9)].String));      }
    break;

  case 110:
#line 225 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputChannelInfo((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number));              }
    break;

  case 111:
#line 226 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputChannelParameterInfo((yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].Number), (yyvsp[(9) - (9)].String)); }
    break;

  case 112:
#line 227 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetChannels();                                  }
    break;

  case 113:
#line 228 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetChannelInfo((yyvsp[(5) - (5)].Number));                             }
    break;

  case 114:
#line 229 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetBufferFill((yyvsp[(5) - (7)].FillResponse), (yyvsp[(7) - (7)].Number));                          }
    break;

  case 115:
#line 230 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetStreamCount((yyvsp[(5) - (5)].Number));                             }
    break;

  case 116:
#line 231 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetVoiceCount((yyvsp[(5) - (5)].Number));                              }
    break;

  case 117:
#line 232 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetEngineInfo((yyvsp[(5) - (5)].String));                              }
    break;

  case 118:
#line 233 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetServerInfo();                                }
    break;

  case 119:
#line 234 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetTotalVoiceCount();                           }
    break;

  case 120:
#line 235 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetTotalVoiceCountMax();                        }
    break;

  case 121:
#line 236 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInstrumentMappings((yyvsp[(3) - (3)].Number));                  }
    break;

  case 122:
#line 237 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAllMidiInstrumentMappings();                 }
    break;

  case 123:
#line 238 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInstrumentMapping((yyvsp[(5) - (9)].Number),(yyvsp[(7) - (9)].Number),(yyvsp[(9) - (9)].Number));             }
    break;

  case 124:
#line 239 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInstrumentMaps();                        }
    break;

  case 125:
#line 240 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInstrumentMap((yyvsp[(5) - (5)].Number));                       }
    break;

  case 126:
#line 241 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetFxSends((yyvsp[(3) - (3)].Number));                                 }
    break;

  case 127:
#line 242 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetFxSendInfo((yyvsp[(5) - (7)].Number),(yyvsp[(7) - (7)].Number));                           }
    break;

  case 128:
#line 243 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetDbInstrumentDirectoryCount((yyvsp[(5) - (5)].String), true);        }
    break;

  case 129:
#line 244 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetDbInstrumentDirectoryCount((yyvsp[(3) - (3)].String), false);       }
    break;

  case 130:
#line 245 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetDbInstrumentDirectoryInfo((yyvsp[(5) - (5)].String));               }
    break;

  case 131:
#line 246 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetDbInstrumentCount((yyvsp[(5) - (5)].String), true);                 }
    break;

  case 132:
#line 247 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetDbInstrumentCount((yyvsp[(3) - (3)].String), false);                }
    break;

  case 133:
#line 248 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetDbInstrumentInfo((yyvsp[(5) - (5)].String));                        }
    break;

  case 134:
#line 249 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetGlobalVolume();                              }
    break;

  case 135:
#line 252 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputDeviceParameter((yyvsp[(3) - (7)].Number), (yyvsp[(5) - (7)].String), (yyvsp[(7) - (7)].String));      }
    break;

  case 136:
#line 253 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputChannelParameter((yyvsp[(3) - (9)].Number), (yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].String), (yyvsp[(9) - (9)].String)); }
    break;

  case 137:
#line 254 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMidiInputDeviceParameter((yyvsp[(3) - (7)].Number), (yyvsp[(5) - (7)].String), (yyvsp[(7) - (7)].String));        }
    break;

  case 138:
#line 255 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMidiInputPortParameter((yyvsp[(3) - (9)].Number), (yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].String), (yyvsp[(9) - (9)].String));      }
    break;

  case 139:
#line 256 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                         }
    break;

  case 140:
#line 257 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMidiInstrumentMapName((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].String));               }
    break;

  case 141:
#line 258 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetFxSendName((yyvsp[(5) - (9)].Number),(yyvsp[(7) - (9)].Number),(yyvsp[(9) - (9)].String));                        }
    break;

  case 142:
#line 259 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetFxSendAudioOutputChannel((yyvsp[(5) - (11)].Number),(yyvsp[(7) - (11)].Number),(yyvsp[(9) - (11)].Number),(yyvsp[(11) - (11)].Number)); }
    break;

  case 143:
#line 260 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetFxSendMidiController((yyvsp[(5) - (9)].Number),(yyvsp[(7) - (9)].Number),(yyvsp[(9) - (9)].Number));              }
    break;

  case 144:
#line 261 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetFxSendLevel((yyvsp[(5) - (9)].Number),(yyvsp[(7) - (9)].Number),(yyvsp[(9) - (9)].Dotnum));                       }
    break;

  case 145:
#line 262 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetDbInstrumentDirectoryName((yyvsp[(5) - (7)].String),(yyvsp[(7) - (7)].String));            }
    break;

  case 146:
#line 263 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetDbInstrumentDirectoryDescription((yyvsp[(5) - (7)].String),(yyvsp[(7) - (7)].String));     }
    break;

  case 147:
#line 264 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetDbInstrumentName((yyvsp[(5) - (7)].String),(yyvsp[(7) - (7)].String));                     }
    break;

  case 148:
#line 265 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetDbInstrumentDescription((yyvsp[(5) - (7)].String),(yyvsp[(7) - (7)].String));              }
    break;

  case 149:
#line 266 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetEcho((yyparse_param_t*) yyparse_param, (yyvsp[(3) - (3)].Dotnum));  }
    break;

  case 150:
#line 267 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetGlobalVolume((yyvsp[(3) - (3)].Dotnum));                            }
    break;

  case 151:
#line 270 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateAudioOutputDevice((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].KeyValList)); }
    break;

  case 152:
#line 271 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateAudioOutputDevice((yyvsp[(3) - (3)].String));    }
    break;

  case 153:
#line 272 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateMidiInputDevice((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].KeyValList));   }
    break;

  case 154:
#line 273 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateMidiInputDevice((yyvsp[(3) - (3)].String));      }
    break;

  case 155:
#line 274 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateFxSend((yyvsp[(3) - (5)].Number),(yyvsp[(5) - (5)].Number));            }
    break;

  case 156:
#line 275 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateFxSend((yyvsp[(3) - (7)].Number),(yyvsp[(5) - (7)].Number),(yyvsp[(7) - (7)].String)); }
    break;

  case 157:
#line 278 "lscp.y"
    { (yyval.String) = LSCPSERVER->ResetChannel((yyvsp[(3) - (3)].Number)); }
    break;

  case 158:
#line 281 "lscp.y"
    { (yyval.String) = LSCPSERVER->ClearMidiInstrumentMappings((yyvsp[(3) - (3)].Number));  }
    break;

  case 159:
#line 282 "lscp.y"
    { (yyval.String) = LSCPSERVER->ClearAllMidiInstrumentMappings(); }
    break;

  case 160:
#line 285 "lscp.y"
    { (yyval.String) = LSCPSERVER->FindDbInstruments((yyvsp[(5) - (7)].String),(yyvsp[(7) - (7)].KeyValList), false);           }
    break;

  case 161:
#line 286 "lscp.y"
    { (yyval.String) = LSCPSERVER->FindDbInstruments((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].KeyValList), true);            }
    break;

  case 162:
#line 287 "lscp.y"
    { (yyval.String) = LSCPSERVER->FindDbInstrumentDirectories((yyvsp[(5) - (7)].String),(yyvsp[(7) - (7)].KeyValList), false); }
    break;

  case 163:
#line 288 "lscp.y"
    { (yyval.String) = LSCPSERVER->FindDbInstrumentDirectories((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].KeyValList), true);  }
    break;

  case 164:
#line 291 "lscp.y"
    { (yyval.String) = LSCPSERVER->MoveDbInstrumentDirectory((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].String)); }
    break;

  case 165:
#line 292 "lscp.y"
    { (yyval.String) = LSCPSERVER->MoveDbInstrument((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].String));          }
    break;

  case 166:
#line 295 "lscp.y"
    { (yyval.String) = LSCPSERVER->CopyDbInstrumentDirectory((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].String)); }
    break;

  case 167:
#line 296 "lscp.y"
    { (yyval.String) = LSCPSERVER->CopyDbInstrument((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].String));          }
    break;

  case 168:
#line 299 "lscp.y"
    { (yyval.String) = LSCPSERVER->DestroyAudioOutputDevice((yyvsp[(3) - (3)].Number)); }
    break;

  case 169:
#line 300 "lscp.y"
    { (yyval.String) = LSCPSERVER->DestroyMidiInputDevice((yyvsp[(3) - (3)].Number));   }
    break;

  case 170:
#line 301 "lscp.y"
    { (yyval.String) = LSCPSERVER->DestroyFxSend((yyvsp[(3) - (5)].Number),(yyvsp[(5) - (5)].Number)); }
    break;

  case 171:
#line 304 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String); }
    break;

  case 172:
#line 305 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String); }
    break;

  case 173:
#line 308 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputDevice((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));      }
    break;

  case 174:
#line 309 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputChannel((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number), (yyvsp[(3) - (7)].Number)); }
    break;

  case 175:
#line 310 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputType((yyvsp[(5) - (5)].String), (yyvsp[(3) - (5)].Number));        }
    break;

  case 176:
#line 311 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInput((yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].Number), (yyvsp[(9) - (9)].Number), (yyvsp[(3) - (9)].Number));      }
    break;

  case 177:
#line 312 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputDevice((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));        }
    break;

  case 178:
#line 313 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputPort((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));          }
    break;

  case 179:
#line 314 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputChannel((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));       }
    break;

  case 180:
#line 315 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputType((yyvsp[(5) - (5)].String), (yyvsp[(3) - (5)].Number));          }
    break;

  case 181:
#line 316 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetVolume((yyvsp[(5) - (5)].Dotnum), (yyvsp[(3) - (5)].Number));                 }
    break;

  case 182:
#line 317 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMute((yyvsp[(5) - (5)].Dotnum), (yyvsp[(3) - (5)].Number));            }
    break;

  case 183:
#line 318 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelSolo((yyvsp[(5) - (5)].Dotnum), (yyvsp[(3) - (5)].Number));            }
    break;

  case 184:
#line 319 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMap((yyvsp[(3) - (5)].Number), (yyvsp[(5) - (5)].Number));             }
    break;

  case 185:
#line 320 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMap((yyvsp[(3) - (5)].Number), -1);             }
    break;

  case 186:
#line 321 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMap((yyvsp[(3) - (5)].Number), -2);             }
    break;

  case 187:
#line 324 "lscp.y"
    { (yyval.Bool) = true;  }
    break;

  case 188:
#line 325 "lscp.y"
    { (yyval.Bool) = false; }
    break;

  case 189:
#line 328 "lscp.y"
    { (yyval.KeyValList)[(yyvsp[(1) - (3)].String)] = (yyvsp[(3) - (3)].String);          }
    break;

  case 190:
#line 329 "lscp.y"
    { (yyval.KeyValList) = (yyvsp[(1) - (5)].KeyValList); (yyval.KeyValList)[(yyvsp[(3) - (5)].String)] = (yyvsp[(5) - (5)].String); }
    break;

  case 191:
#line 332 "lscp.y"
    { (yyval.FillResponse) = fill_response_bytes;      }
    break;

  case 192:
#line 333 "lscp.y"
    { (yyval.FillResponse) = fill_response_percentage; }
    break;

  case 193:
#line 336 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDevices();              }
    break;

  case 194:
#line 337 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDevices();                }
    break;

  case 195:
#line 338 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListChannels();                       }
    break;

  case 196:
#line 339 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableEngines();               }
    break;

  case 197:
#line 340 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableMidiInputDrivers();      }
    break;

  case 198:
#line 341 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableAudioOutputDrivers();    }
    break;

  case 199:
#line 342 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListMidiInstrumentMappings((yyvsp[(3) - (3)].Number));       }
    break;

  case 200:
#line 343 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAllMidiInstrumentMappings();      }
    break;

  case 201:
#line 344 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListMidiInstrumentMaps();             }
    break;

  case 202:
#line 345 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListFxSends((yyvsp[(3) - (3)].Number));                      }
    break;

  case 203:
#line 346 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetDbInstrumentDirectories((yyvsp[(5) - (5)].String), true); }
    break;

  case 204:
#line 347 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetDbInstrumentDirectories((yyvsp[(3) - (3)].String));       }
    break;

  case 205:
#line 348 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetDbInstruments((yyvsp[(5) - (5)].String), true);           }
    break;

  case 206:
#line 349 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetDbInstruments((yyvsp[(3) - (3)].String));                 }
    break;

  case 207:
#line 352 "lscp.y"
    { (yyval.String) = LSCPSERVER->LoadInstrument((yyvsp[(1) - (5)].String), (yyvsp[(3) - (5)].Number), (yyvsp[(5) - (5)].Number));       }
    break;

  case 208:
#line 353 "lscp.y"
    { (yyval.String) = LSCPSERVER->LoadInstrument((yyvsp[(3) - (7)].String), (yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number), true); }
    break;

  case 209:
#line 356 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetEngineType((yyvsp[(1) - (3)].String), (yyvsp[(3) - (3)].Number)); }
    break;

  case 210:
#line 359 "lscp.y"
    { (yyval.LoadMode) = MidiInstrumentMapper::ON_DEMAND;      }
    break;

  case 211:
#line 360 "lscp.y"
    { (yyval.LoadMode) = MidiInstrumentMapper::ON_DEMAND_HOLD; }
    break;

  case 212:
#line 361 "lscp.y"
    { (yyval.LoadMode) = MidiInstrumentMapper::PERSISTENT;     }
    break;

  case 218:
#line 377 "lscp.y"
    { (yyval.Number) = 16; }
    break;

  case 225:
#line 396 "lscp.y"
    { (yyval.Dotnum) = (yyvsp[(1) - (1)].Number); }
    break;

  case 237:
#line 430 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (3)].String) + "," + (yyvsp[(3) - (3)].String); }
    break;

  case 240:
#line 435 "lscp.y"
    { std::stringstream ss; ss << "\'" << (yyvsp[(1) - (1)].Number) << "\'"; (yyval.String) = ss.str(); }
    break;

  case 241:
#line 436 "lscp.y"
    { std::stringstream ss; ss << "\'" << (yyvsp[(1) - (1)].Dotnum) << "\'"; (yyval.String) = ss.str(); }
    break;

  case 242:
#line 439 "lscp.y"
    { (yyval.KeyValList)[(yyvsp[(1) - (3)].String)] = (yyvsp[(3) - (3)].String);          }
    break;

  case 243:
#line 440 "lscp.y"
    { (yyval.KeyValList) = (yyvsp[(1) - (5)].KeyValList); (yyval.KeyValList)[(yyvsp[(3) - (5)].String)] = (yyvsp[(5) - (5)].String); }
    break;

  case 246:
#line 452 "lscp.y"
    { (yyval.Dotnum) = (yyvsp[(1) - (1)].Number); }
    break;

  case 247:
#line 453 "lscp.y"
    { (yyval.Dotnum) = -1; }
    break;

  case 248:
#line 456 "lscp.y"
    { std::string s; s = (yyvsp[(1) - (1)].Char); (yyval.String) = s; }
    break;

  case 249:
#line 457 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + (yyvsp[(2) - (2)].Char);                  }
    break;

  case 250:
#line 460 "lscp.y"
    { (yyval.Dotnum) = atof(String((yyvsp[(1) - (3)].String) + "." + (yyvsp[(3) - (3)].String)).c_str());                         }
    break;

  case 251:
#line 461 "lscp.y"
    { String s = "+"; s += (yyvsp[(2) - (4)].String); s += "."; s += (yyvsp[(4) - (4)].String); (yyval.Dotnum) = atof(s.c_str()); }
    break;

  case 252:
#line 462 "lscp.y"
    { (yyval.Dotnum) = atof(String("-" + (yyvsp[(2) - (4)].String) + "." + (yyvsp[(4) - (4)].String)).c_str());                   }
    break;

  case 253:
#line 466 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (1)].Char);      }
    break;

  case 254:
#line 467 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + (yyvsp[(2) - (2)].Char); }
    break;

  case 255:
#line 470 "lscp.y"
    { (yyval.Char) = '0'; }
    break;

  case 256:
#line 471 "lscp.y"
    { (yyval.Char) = '1'; }
    break;

  case 257:
#line 472 "lscp.y"
    { (yyval.Char) = '2'; }
    break;

  case 258:
#line 473 "lscp.y"
    { (yyval.Char) = '3'; }
    break;

  case 259:
#line 474 "lscp.y"
    { (yyval.Char) = '4'; }
    break;

  case 260:
#line 475 "lscp.y"
    { (yyval.Char) = '5'; }
    break;

  case 261:
#line 476 "lscp.y"
    { (yyval.Char) = '6'; }
    break;

  case 262:
#line 477 "lscp.y"
    { (yyval.Char) = '7'; }
    break;

  case 263:
#line 478 "lscp.y"
    { (yyval.Char) = '8'; }
    break;

  case 264:
#line 479 "lscp.y"
    { (yyval.Char) = '9'; }
    break;

  case 265:
#line 482 "lscp.y"
    { (yyval.Number) = atoi(String(1, (yyvsp[(1) - (1)].Char)).c_str());      }
    break;

  case 266:
#line 483 "lscp.y"
    { (yyval.Number) = atoi(String(String("1") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 267:
#line 484 "lscp.y"
    { (yyval.Number) = atoi(String(String("2") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 268:
#line 485 "lscp.y"
    { (yyval.Number) = atoi(String(String("3") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 269:
#line 486 "lscp.y"
    { (yyval.Number) = atoi(String(String("4") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 270:
#line 487 "lscp.y"
    { (yyval.Number) = atoi(String(String("5") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 271:
#line 488 "lscp.y"
    { (yyval.Number) = atoi(String(String("6") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 272:
#line 489 "lscp.y"
    { (yyval.Number) = atoi(String(String("7") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 273:
#line 490 "lscp.y"
    { (yyval.Number) = atoi(String(String("8") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 274:
#line 491 "lscp.y"
    { (yyval.Number) = atoi(String(String("9") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 275:
#line 493 "lscp.y"
    { (yyval.Char) = 'A'; }
    break;

  case 276:
#line 493 "lscp.y"
    { (yyval.Char) = 'B'; }
    break;

  case 277:
#line 493 "lscp.y"
    { (yyval.Char) = 'C'; }
    break;

  case 278:
#line 493 "lscp.y"
    { (yyval.Char) = 'D'; }
    break;

  case 279:
#line 493 "lscp.y"
    { (yyval.Char) = 'E'; }
    break;

  case 280:
#line 493 "lscp.y"
    { (yyval.Char) = 'F'; }
    break;

  case 281:
#line 493 "lscp.y"
    { (yyval.Char) = 'G'; }
    break;

  case 282:
#line 493 "lscp.y"
    { (yyval.Char) = 'H'; }
    break;

  case 283:
#line 493 "lscp.y"
    { (yyval.Char) = 'I'; }
    break;

  case 284:
#line 493 "lscp.y"
    { (yyval.Char) = 'J'; }
    break;

  case 285:
#line 493 "lscp.y"
    { (yyval.Char) = 'K'; }
    break;

  case 286:
#line 493 "lscp.y"
    { (yyval.Char) = 'L'; }
    break;

  case 287:
#line 493 "lscp.y"
    { (yyval.Char) = 'M'; }
    break;

  case 288:
#line 493 "lscp.y"
    { (yyval.Char) = 'N'; }
    break;

  case 289:
#line 493 "lscp.y"
    { (yyval.Char) = 'O'; }
    break;

  case 290:
#line 493 "lscp.y"
    { (yyval.Char) = 'P'; }
    break;

  case 291:
#line 493 "lscp.y"
    { (yyval.Char) = 'Q'; }
    break;

  case 292:
#line 493 "lscp.y"
    { (yyval.Char) = 'R'; }
    break;

  case 293:
#line 493 "lscp.y"
    { (yyval.Char) = 'S'; }
    break;

  case 294:
#line 493 "lscp.y"
    { (yyval.Char) = 'T'; }
    break;

  case 295:
#line 493 "lscp.y"
    { (yyval.Char) = 'U'; }
    break;

  case 296:
#line 493 "lscp.y"
    { (yyval.Char) = 'V'; }
    break;

  case 297:
#line 493 "lscp.y"
    { (yyval.Char) = 'W'; }
    break;

  case 298:
#line 493 "lscp.y"
    { (yyval.Char) = 'X'; }
    break;

  case 299:
#line 493 "lscp.y"
    { (yyval.Char) = 'Y'; }
    break;

  case 300:
#line 493 "lscp.y"
    { (yyval.Char) = 'Z'; }
    break;

  case 301:
#line 494 "lscp.y"
    { (yyval.Char) = 'a'; }
    break;

  case 302:
#line 494 "lscp.y"
    { (yyval.Char) = 'b'; }
    break;

  case 303:
#line 494 "lscp.y"
    { (yyval.Char) = 'c'; }
    break;

  case 304:
#line 494 "lscp.y"
    { (yyval.Char) = 'd'; }
    break;

  case 305:
#line 494 "lscp.y"
    { (yyval.Char) = 'e'; }
    break;

  case 306:
#line 494 "lscp.y"
    { (yyval.Char) = 'f'; }
    break;

  case 307:
#line 494 "lscp.y"
    { (yyval.Char) = 'g'; }
    break;

  case 308:
#line 494 "lscp.y"
    { (yyval.Char) = 'h'; }
    break;

  case 309:
#line 494 "lscp.y"
    { (yyval.Char) = 'i'; }
    break;

  case 310:
#line 494 "lscp.y"
    { (yyval.Char) = 'j'; }
    break;

  case 311:
#line 494 "lscp.y"
    { (yyval.Char) = 'k'; }
    break;

  case 312:
#line 494 "lscp.y"
    { (yyval.Char) = 'l'; }
    break;

  case 313:
#line 494 "lscp.y"
    { (yyval.Char) = 'm'; }
    break;

  case 314:
#line 494 "lscp.y"
    { (yyval.Char) = 'n'; }
    break;

  case 315:
#line 494 "lscp.y"
    { (yyval.Char) = 'o'; }
    break;

  case 316:
#line 494 "lscp.y"
    { (yyval.Char) = 'p'; }
    break;

  case 317:
#line 494 "lscp.y"
    { (yyval.Char) = 'q'; }
    break;

  case 318:
#line 494 "lscp.y"
    { (yyval.Char) = 'r'; }
    break;

  case 319:
#line 494 "lscp.y"
    { (yyval.Char) = 's'; }
    break;

  case 320:
#line 494 "lscp.y"
    { (yyval.Char) = 't'; }
    break;

  case 321:
#line 494 "lscp.y"
    { (yyval.Char) = 'u'; }
    break;

  case 322:
#line 494 "lscp.y"
    { (yyval.Char) = 'v'; }
    break;

  case 323:
#line 494 "lscp.y"
    { (yyval.Char) = 'w'; }
    break;

  case 324:
#line 494 "lscp.y"
    { (yyval.Char) = 'x'; }
    break;

  case 325:
#line 494 "lscp.y"
    { (yyval.Char) = 'y'; }
    break;

  case 326:
#line 494 "lscp.y"
    { (yyval.Char) = 'z'; }
    break;

  case 327:
#line 495 "lscp.y"
    { (yyval.Char) = '0'; }
    break;

  case 328:
#line 495 "lscp.y"
    { (yyval.Char) = '1'; }
    break;

  case 329:
#line 495 "lscp.y"
    { (yyval.Char) = '2'; }
    break;

  case 330:
#line 495 "lscp.y"
    { (yyval.Char) = '3'; }
    break;

  case 331:
#line 495 "lscp.y"
    { (yyval.Char) = '4'; }
    break;

  case 332:
#line 495 "lscp.y"
    { (yyval.Char) = '5'; }
    break;

  case 333:
#line 495 "lscp.y"
    { (yyval.Char) = '6'; }
    break;

  case 334:
#line 495 "lscp.y"
    { (yyval.Char) = '7'; }
    break;

  case 335:
#line 495 "lscp.y"
    { (yyval.Char) = '8'; }
    break;

  case 336:
#line 495 "lscp.y"
    { (yyval.Char) = '9'; }
    break;

  case 337:
#line 496 "lscp.y"
    { (yyval.Char) = '!'; }
    break;

  case 338:
#line 496 "lscp.y"
    { (yyval.Char) = '#'; }
    break;

  case 339:
#line 496 "lscp.y"
    { (yyval.Char) = '$'; }
    break;

  case 340:
#line 496 "lscp.y"
    { (yyval.Char) = '%'; }
    break;

  case 341:
#line 496 "lscp.y"
    { (yyval.Char) = '&'; }
    break;

  case 342:
#line 496 "lscp.y"
    { (yyval.Char) = '('; }
    break;

  case 343:
#line 496 "lscp.y"
    { (yyval.Char) = ')'; }
    break;

  case 344:
#line 496 "lscp.y"
    { (yyval.Char) = '*'; }
    break;

  case 345:
#line 496 "lscp.y"
    { (yyval.Char) = '+'; }
    break;

  case 346:
#line 496 "lscp.y"
    { (yyval.Char) = '-'; }
    break;

  case 347:
#line 496 "lscp.y"
    { (yyval.Char) = '.'; }
    break;

  case 348:
#line 496 "lscp.y"
    { (yyval.Char) = ','; }
    break;

  case 349:
#line 496 "lscp.y"
    { (yyval.Char) = '/'; }
    break;

  case 350:
#line 497 "lscp.y"
    { (yyval.Char) = ':'; }
    break;

  case 351:
#line 497 "lscp.y"
    { (yyval.Char) = ';'; }
    break;

  case 352:
#line 497 "lscp.y"
    { (yyval.Char) = '<'; }
    break;

  case 353:
#line 497 "lscp.y"
    { (yyval.Char) = '='; }
    break;

  case 354:
#line 497 "lscp.y"
    { (yyval.Char) = '>'; }
    break;

  case 355:
#line 497 "lscp.y"
    { (yyval.Char) = '?'; }
    break;

  case 356:
#line 497 "lscp.y"
    { (yyval.Char) = '@'; }
    break;

  case 357:
#line 498 "lscp.y"
    { (yyval.Char) = '['; }
    break;

  case 358:
#line 498 "lscp.y"
    { (yyval.Char) = '\\'; }
    break;

  case 359:
#line 498 "lscp.y"
    { (yyval.Char) = ']'; }
    break;

  case 360:
#line 498 "lscp.y"
    { (yyval.Char) = '^'; }
    break;

  case 361:
#line 498 "lscp.y"
    { (yyval.Char) = '_'; }
    break;

  case 362:
#line 499 "lscp.y"
    { (yyval.Char) = '{'; }
    break;

  case 363:
#line 499 "lscp.y"
    { (yyval.Char) = '|'; }
    break;

  case 364:
#line 499 "lscp.y"
    { (yyval.Char) = '}'; }
    break;

  case 365:
#line 499 "lscp.y"
    { (yyval.Char) = '~'; }
    break;

  case 366:
#line 500 "lscp.y"
    { (yyval.Char) = '\200'; }
    break;

  case 367:
#line 500 "lscp.y"
    { (yyval.Char) = '\201'; }
    break;

  case 368:
#line 500 "lscp.y"
    { (yyval.Char) = '\202'; }
    break;

  case 369:
#line 501 "lscp.y"
    { (yyval.Char) = '\203'; }
    break;

  case 370:
#line 501 "lscp.y"
    { (yyval.Char) = '\204'; }
    break;

  case 371:
#line 501 "lscp.y"
    { (yyval.Char) = '\205'; }
    break;

  case 372:
#line 502 "lscp.y"
    { (yyval.Char) = '\206'; }
    break;

  case 373:
#line 502 "lscp.y"
    { (yyval.Char) = '\207'; }
    break;

  case 374:
#line 502 "lscp.y"
    { (yyval.Char) = '\210'; }
    break;

  case 375:
#line 503 "lscp.y"
    { (yyval.Char) = '\211'; }
    break;

  case 376:
#line 503 "lscp.y"
    { (yyval.Char) = '\212'; }
    break;

  case 377:
#line 503 "lscp.y"
    { (yyval.Char) = '\213'; }
    break;

  case 378:
#line 504 "lscp.y"
    { (yyval.Char) = '\214'; }
    break;

  case 379:
#line 504 "lscp.y"
    { (yyval.Char) = '\215'; }
    break;

  case 380:
#line 504 "lscp.y"
    { (yyval.Char) = '\216'; }
    break;

  case 381:
#line 505 "lscp.y"
    { (yyval.Char) = '\217'; }
    break;

  case 382:
#line 505 "lscp.y"
    { (yyval.Char) = '\220'; }
    break;

  case 383:
#line 505 "lscp.y"
    { (yyval.Char) = '\221'; }
    break;

  case 384:
#line 506 "lscp.y"
    { (yyval.Char) = '\222'; }
    break;

  case 385:
#line 506 "lscp.y"
    { (yyval.Char) = '\223'; }
    break;

  case 386:
#line 506 "lscp.y"
    { (yyval.Char) = '\224'; }
    break;

  case 387:
#line 507 "lscp.y"
    { (yyval.Char) = '\225'; }
    break;

  case 388:
#line 507 "lscp.y"
    { (yyval.Char) = '\226'; }
    break;

  case 389:
#line 507 "lscp.y"
    { (yyval.Char) = '\227'; }
    break;

  case 390:
#line 508 "lscp.y"
    { (yyval.Char) = '\230'; }
    break;

  case 391:
#line 508 "lscp.y"
    { (yyval.Char) = '\231'; }
    break;

  case 392:
#line 508 "lscp.y"
    { (yyval.Char) = '\232'; }
    break;

  case 393:
#line 509 "lscp.y"
    { (yyval.Char) = '\233'; }
    break;

  case 394:
#line 509 "lscp.y"
    { (yyval.Char) = '\234'; }
    break;

  case 395:
#line 509 "lscp.y"
    { (yyval.Char) = '\235'; }
    break;

  case 396:
#line 510 "lscp.y"
    { (yyval.Char) = '\236'; }
    break;

  case 397:
#line 510 "lscp.y"
    { (yyval.Char) = '\237'; }
    break;

  case 398:
#line 510 "lscp.y"
    { (yyval.Char) = '\240'; }
    break;

  case 399:
#line 511 "lscp.y"
    { (yyval.Char) = '\241'; }
    break;

  case 400:
#line 511 "lscp.y"
    { (yyval.Char) = '\242'; }
    break;

  case 401:
#line 511 "lscp.y"
    { (yyval.Char) = '\243'; }
    break;

  case 402:
#line 512 "lscp.y"
    { (yyval.Char) = '\244'; }
    break;

  case 403:
#line 512 "lscp.y"
    { (yyval.Char) = '\245'; }
    break;

  case 404:
#line 512 "lscp.y"
    { (yyval.Char) = '\246'; }
    break;

  case 405:
#line 513 "lscp.y"
    { (yyval.Char) = '\247'; }
    break;

  case 406:
#line 513 "lscp.y"
    { (yyval.Char) = '\250'; }
    break;

  case 407:
#line 513 "lscp.y"
    { (yyval.Char) = '\251'; }
    break;

  case 408:
#line 514 "lscp.y"
    { (yyval.Char) = '\252'; }
    break;

  case 409:
#line 514 "lscp.y"
    { (yyval.Char) = '\253'; }
    break;

  case 410:
#line 514 "lscp.y"
    { (yyval.Char) = '\254'; }
    break;

  case 411:
#line 515 "lscp.y"
    { (yyval.Char) = '\255'; }
    break;

  case 412:
#line 515 "lscp.y"
    { (yyval.Char) = '\256'; }
    break;

  case 413:
#line 515 "lscp.y"
    { (yyval.Char) = '\257'; }
    break;

  case 414:
#line 516 "lscp.y"
    { (yyval.Char) = '\260'; }
    break;

  case 415:
#line 516 "lscp.y"
    { (yyval.Char) = '\261'; }
    break;

  case 416:
#line 516 "lscp.y"
    { (yyval.Char) = '\262'; }
    break;

  case 417:
#line 517 "lscp.y"
    { (yyval.Char) = '\263'; }
    break;

  case 418:
#line 517 "lscp.y"
    { (yyval.Char) = '\264'; }
    break;

  case 419:
#line 517 "lscp.y"
    { (yyval.Char) = '\265'; }
    break;

  case 420:
#line 518 "lscp.y"
    { (yyval.Char) = '\266'; }
    break;

  case 421:
#line 518 "lscp.y"
    { (yyval.Char) = '\267'; }
    break;

  case 422:
#line 518 "lscp.y"
    { (yyval.Char) = '\270'; }
    break;

  case 423:
#line 519 "lscp.y"
    { (yyval.Char) = '\271'; }
    break;

  case 424:
#line 519 "lscp.y"
    { (yyval.Char) = '\272'; }
    break;

  case 425:
#line 519 "lscp.y"
    { (yyval.Char) = '\273'; }
    break;

  case 426:
#line 520 "lscp.y"
    { (yyval.Char) = '\274'; }
    break;

  case 427:
#line 520 "lscp.y"
    { (yyval.Char) = '\275'; }
    break;

  case 428:
#line 520 "lscp.y"
    { (yyval.Char) = '\276'; }
    break;

  case 429:
#line 521 "lscp.y"
    { (yyval.Char) = '\277'; }
    break;

  case 430:
#line 521 "lscp.y"
    { (yyval.Char) = '\300'; }
    break;

  case 431:
#line 521 "lscp.y"
    { (yyval.Char) = '\301'; }
    break;

  case 432:
#line 522 "lscp.y"
    { (yyval.Char) = '\302'; }
    break;

  case 433:
#line 522 "lscp.y"
    { (yyval.Char) = '\303'; }
    break;

  case 434:
#line 522 "lscp.y"
    { (yyval.Char) = '\304'; }
    break;

  case 435:
#line 523 "lscp.y"
    { (yyval.Char) = '\305'; }
    break;

  case 436:
#line 523 "lscp.y"
    { (yyval.Char) = '\306'; }
    break;

  case 437:
#line 523 "lscp.y"
    { (yyval.Char) = '\307'; }
    break;

  case 438:
#line 524 "lscp.y"
    { (yyval.Char) = '\310'; }
    break;

  case 439:
#line 524 "lscp.y"
    { (yyval.Char) = '\311'; }
    break;

  case 440:
#line 524 "lscp.y"
    { (yyval.Char) = '\312'; }
    break;

  case 441:
#line 525 "lscp.y"
    { (yyval.Char) = '\313'; }
    break;

  case 442:
#line 525 "lscp.y"
    { (yyval.Char) = '\314'; }
    break;

  case 443:
#line 525 "lscp.y"
    { (yyval.Char) = '\315'; }
    break;

  case 444:
#line 526 "lscp.y"
    { (yyval.Char) = '\316'; }
    break;

  case 445:
#line 526 "lscp.y"
    { (yyval.Char) = '\317'; }
    break;

  case 446:
#line 526 "lscp.y"
    { (yyval.Char) = '\320'; }
    break;

  case 447:
#line 527 "lscp.y"
    { (yyval.Char) = '\321'; }
    break;

  case 448:
#line 527 "lscp.y"
    { (yyval.Char) = '\322'; }
    break;

  case 449:
#line 527 "lscp.y"
    { (yyval.Char) = '\323'; }
    break;

  case 450:
#line 528 "lscp.y"
    { (yyval.Char) = '\324'; }
    break;

  case 451:
#line 528 "lscp.y"
    { (yyval.Char) = '\325'; }
    break;

  case 452:
#line 528 "lscp.y"
    { (yyval.Char) = '\326'; }
    break;

  case 453:
#line 529 "lscp.y"
    { (yyval.Char) = '\327'; }
    break;

  case 454:
#line 529 "lscp.y"
    { (yyval.Char) = '\330'; }
    break;

  case 455:
#line 529 "lscp.y"
    { (yyval.Char) = '\331'; }
    break;

  case 456:
#line 530 "lscp.y"
    { (yyval.Char) = '\332'; }
    break;

  case 457:
#line 530 "lscp.y"
    { (yyval.Char) = '\333'; }
    break;

  case 458:
#line 530 "lscp.y"
    { (yyval.Char) = '\334'; }
    break;

  case 459:
#line 531 "lscp.y"
    { (yyval.Char) = '\335'; }
    break;

  case 460:
#line 531 "lscp.y"
    { (yyval.Char) = '\336'; }
    break;

  case 461:
#line 531 "lscp.y"
    { (yyval.Char) = '\337'; }
    break;

  case 462:
#line 532 "lscp.y"
    { (yyval.Char) = '\340'; }
    break;

  case 463:
#line 532 "lscp.y"
    { (yyval.Char) = '\341'; }
    break;

  case 464:
#line 532 "lscp.y"
    { (yyval.Char) = '\342'; }
    break;

  case 465:
#line 533 "lscp.y"
    { (yyval.Char) = '\343'; }
    break;

  case 466:
#line 533 "lscp.y"
    { (yyval.Char) = '\344'; }
    break;

  case 467:
#line 533 "lscp.y"
    { (yyval.Char) = '\345'; }
    break;

  case 468:
#line 534 "lscp.y"
    { (yyval.Char) = '\346'; }
    break;

  case 469:
#line 534 "lscp.y"
    { (yyval.Char) = '\347'; }
    break;

  case 470:
#line 534 "lscp.y"
    { (yyval.Char) = '\350'; }
    break;

  case 471:
#line 535 "lscp.y"
    { (yyval.Char) = '\351'; }
    break;

  case 472:
#line 535 "lscp.y"
    { (yyval.Char) = '\352'; }
    break;

  case 473:
#line 535 "lscp.y"
    { (yyval.Char) = '\353'; }
    break;

  case 474:
#line 536 "lscp.y"
    { (yyval.Char) = '\354'; }
    break;

  case 475:
#line 536 "lscp.y"
    { (yyval.Char) = '\355'; }
    break;

  case 476:
#line 536 "lscp.y"
    { (yyval.Char) = '\356'; }
    break;

  case 477:
#line 537 "lscp.y"
    { (yyval.Char) = '\357'; }
    break;

  case 478:
#line 537 "lscp.y"
    { (yyval.Char) = '\360'; }
    break;

  case 479:
#line 537 "lscp.y"
    { (yyval.Char) = '\361'; }
    break;

  case 480:
#line 538 "lscp.y"
    { (yyval.Char) = '\362'; }
    break;

  case 481:
#line 538 "lscp.y"
    { (yyval.Char) = '\363'; }
    break;

  case 482:
#line 538 "lscp.y"
    { (yyval.Char) = '\364'; }
    break;

  case 483:
#line 539 "lscp.y"
    { (yyval.Char) = '\365'; }
    break;

  case 484:
#line 539 "lscp.y"
    { (yyval.Char) = '\366'; }
    break;

  case 485:
#line 539 "lscp.y"
    { (yyval.Char) = '\367'; }
    break;

  case 486:
#line 540 "lscp.y"
    { (yyval.Char) = '\370'; }
    break;

  case 487:
#line 540 "lscp.y"
    { (yyval.Char) = '\371'; }
    break;

  case 488:
#line 540 "lscp.y"
    { (yyval.Char) = '\372'; }
    break;

  case 489:
#line 541 "lscp.y"
    { (yyval.Char) = '\373'; }
    break;

  case 490:
#line 541 "lscp.y"
    { (yyval.Char) = '\374'; }
    break;

  case 491:
#line 541 "lscp.y"
    { (yyval.Char) = '\375'; }
    break;

  case 492:
#line 542 "lscp.y"
    { (yyval.Char) = '\376'; }
    break;

  case 493:
#line 542 "lscp.y"
    { (yyval.Char) = '\377'; }
    break;

  case 494:
#line 545 "lscp.y"
    { (yyval.String) = " ";      }
    break;

  case 496:
#line 547 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + " "; }
    break;

  case 497:
#line 548 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + (yyvsp[(2) - (2)].String);  }
    break;

  case 498:
#line 551 "lscp.y"
    { (yyval.String) = (yyvsp[(2) - (3)].String); }
    break;

  case 499:
#line 552 "lscp.y"
    { (yyval.String) = (yyvsp[(2) - (3)].String); }
    break;


/* Line 1267 of yacc.c.  */
#line 6016 "y.tab.c"
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


#line 864 "lscp.y"


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

