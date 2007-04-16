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
#define YYFINAL  47
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   4799

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  227
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  158
/* YYNRULES -- Number of rules.  */
#define YYNRULES  582
/* YYNRULES -- Number of states.  */
#define YYNSTATES  1965

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
      95,    97,   101,   109,   117,   123,   131,   133,   137,   139,
     141,   143,   145,   147,   149,   151,   153,   155,   157,   159,
     161,   163,   165,   167,   169,   171,   173,   175,   177,   179,
     181,   183,   185,   187,   189,   191,   193,   195,   197,   199,
     201,   203,   205,   207,   209,   211,   213,   215,   217,   219,
     221,   223,   225,   242,   261,   280,   301,   309,   313,   317,
     321,   327,   331,   335,   337,   339,   345,   353,   363,   365,
     371,   379,   389,   391,   393,   399,   405,   413,   423,   431,
     441,   443,   449,   457,   463,   469,   475,   479,   481,   483,
     487,   491,   501,   503,   509,   513,   521,   525,   531,   535,
     541,   543,   551,   561,   569,   579,   583,   591,   601,   613,
     623,   633,   641,   649,   657,   665,   669,   673,   679,   683,
     689,   693,   699,   707,   711,   715,   719,   725,   731,   735,
     739,   745,   749,   753,   759,   767,   773,   783,   789,   795,
     801,   807,   813,   819,   825,   831,   837,   843,   844,   847,
     851,   857,   859,   861,   863,   865,   867,   869,   871,   873,
     877,   881,   883,   887,   891,   895,   901,   909,   913,   915,
     917,   919,   921,   923,   925,   927,   929,   931,   933,   935,
     937,   939,   941,   943,   945,   947,   949,   951,   953,   955,
     957,   959,   961,   963,   965,   967,   971,   973,   975,   977,
     979,   981,   983,   985,   988,   992,   997,  1002,  1004,  1007,
    1009,  1011,  1013,  1015,  1017,  1019,  1021,  1023,  1025,  1027,
    1029,  1032,  1035,  1038,  1041,  1044,  1047,  1050,  1053,  1056,
    1058,  1060,  1062,  1064,  1066,  1068,  1070,  1072,  1074,  1076,
    1078,  1080,  1082,  1084,  1086,  1088,  1090,  1092,  1094,  1096,
    1098,  1100,  1102,  1104,  1106,  1108,  1110,  1112,  1114,  1116,
    1118,  1120,  1122,  1124,  1126,  1128,  1130,  1132,  1134,  1136,
    1138,  1140,  1142,  1144,  1146,  1148,  1150,  1152,  1154,  1156,
    1158,  1160,  1162,  1164,  1166,  1168,  1170,  1172,  1174,  1176,
    1178,  1180,  1182,  1184,  1186,  1188,  1190,  1192,  1194,  1196,
    1198,  1200,  1202,  1204,  1206,  1208,  1210,  1212,  1214,  1216,
    1218,  1220,  1222,  1224,  1226,  1228,  1230,  1232,  1234,  1236,
    1238,  1240,  1242,  1244,  1246,  1248,  1250,  1252,  1254,  1256,
    1258,  1260,  1262,  1264,  1266,  1268,  1270,  1272,  1274,  1276,
    1278,  1280,  1282,  1284,  1286,  1288,  1290,  1292,  1294,  1296,
    1298,  1300,  1302,  1304,  1306,  1308,  1310,  1312,  1314,  1316,
    1318,  1320,  1322,  1324,  1326,  1328,  1330,  1332,  1334,  1336,
    1338,  1340,  1342,  1344,  1346,  1348,  1350,  1352,  1354,  1356,
    1358,  1360,  1362,  1364,  1366,  1368,  1370,  1372,  1374,  1376,
    1378,  1380,  1382,  1384,  1386,  1388,  1390,  1392,  1394,  1396,
    1398,  1400,  1402,  1404,  1406,  1408,  1410,  1412,  1414,  1416,
    1418,  1420,  1422,  1424,  1426,  1428,  1430,  1432,  1434,  1436,
    1438,  1440,  1442,  1444,  1446,  1448,  1450,  1452,  1454,  1456,
    1458,  1460,  1462,  1464,  1466,  1468,  1470,  1472,  1474,  1476,
    1478,  1480,  1482,  1484,  1486,  1488,  1490,  1492,  1494,  1496,
    1498,  1501,  1504,  1508,  1512,  1514,  1516,  1518,  1522,  1526,
    1530,  1536,  1542,  1547,  1554,  1562,  1567,  1572,  1576,  1581,
    1589,  1599,  1606,  1610,  1620,  1632,  1640,  1658,  1689,  1698,
    1703,  1729,  1754,  1778,  1801,  1827,  1852,  1874,  1895,  1925,
    1954,  1974,  1993,  2007,  2020,  2034,  2047,  2059,  2072,  2084,
    2102,  2124,  2136,  2147,  2154,  2164,  2179,  2190,  2220,  2241,
    2261,  2291,  2311,  2342,  2363,  2381,  2410,  2438,  2464,  2483,
    2501,  2529,  2545,  2562,  2582,  2603,  2621,  2637,  2656,  2672,
    2683,  2699,  2707,  2716,  2740,  2766,  2781,  2795,  2807,  2813,
    2818,  2832,  2839,  2846,  2852,  2857,  2862,  2868,  2879,  2885,
    2899,  2904,  2909
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     228,     0,    -1,   229,   287,    -1,   229,   288,   287,    -1,
      -1,   230,    -1,   231,    -1,     1,    -1,     3,    -1,   230,
       3,    -1,   230,   286,    -1,   230,   282,    -1,   230,   278,
      -1,   289,   286,   232,    -1,   291,   286,   235,    -1,   292,
     286,   236,    -1,   290,   286,   238,    -1,   295,   286,   240,
      -1,   296,   286,   244,    -1,   297,   286,   250,    -1,   298,
     286,   245,    -1,   303,   286,   237,    -1,   304,   286,   239,
      -1,   305,   286,   233,    -1,   306,   286,   234,    -1,   380,
     286,   241,    -1,   293,   286,   242,    -1,   294,   286,   243,
      -1,   380,    -1,   384,    -1,   307,    -1,   365,   286,   269,
      -1,   367,   286,   371,   286,   269,   286,   269,    -1,   367,
     286,   372,   286,   269,   286,   269,    -1,   367,   286,   269,
     286,   269,    -1,   367,   286,   269,   286,   269,   286,   266,
      -1,   355,    -1,   355,   286,   272,    -1,   312,    -1,   313,
      -1,   314,    -1,   315,    -1,   324,    -1,   330,    -1,   329,
      -1,   328,    -1,   325,    -1,   326,    -1,   327,    -1,   316,
      -1,   317,    -1,   318,    -1,   319,    -1,   320,    -1,   321,
      -1,   322,    -1,   323,    -1,   381,    -1,   331,    -1,   333,
      -1,   312,    -1,   313,    -1,   314,    -1,   315,    -1,   324,
      -1,   330,    -1,   329,    -1,   328,    -1,   325,    -1,   326,
      -1,   327,    -1,   316,    -1,   317,    -1,   318,    -1,   319,
      -1,   320,    -1,   321,    -1,   322,    -1,   323,    -1,   381,
      -1,   331,    -1,   333,    -1,   353,   286,   247,   260,   286,
     261,   286,   262,   286,   268,   286,   271,   286,   266,   286,
     264,    -1,   353,   286,   247,   260,   286,   261,   286,   262,
     286,   268,   286,   271,   286,   266,   286,   264,   286,   253,
      -1,   353,   286,   247,   260,   286,   261,   286,   262,   286,
     268,   286,   271,   286,   266,   286,   264,   286,   273,    -1,
     353,   286,   247,   260,   286,   261,   286,   262,   286,   268,
     286,   271,   286,   266,   286,   264,   286,   253,   286,   273,
      -1,   353,   286,   260,   286,   261,   286,   262,    -1,   307,
     286,   265,    -1,   355,   286,   260,    -1,   355,   286,   299,
      -1,   365,   286,   370,   286,   269,    -1,   365,   286,   269,
      -1,   368,   286,   269,    -1,   308,    -1,   347,    -1,   357,
     286,   311,   286,   278,    -1,   352,   286,   311,   286,   278,
     286,   278,    -1,   352,   286,   311,   286,   278,   286,   278,
     286,   248,    -1,   309,    -1,   343,   286,   311,   286,   278,
      -1,   342,   286,   311,   286,   278,   286,   278,    -1,   342,
     286,   311,   286,   278,   286,   278,   286,   248,    -1,   340,
      -1,   350,    -1,   341,   286,   311,   286,   282,    -1,   351,
     286,   311,   286,   282,    -1,   358,   286,   311,   286,   282,
     286,   282,    -1,   349,   286,   311,   286,   282,   286,   282,
     286,   278,    -1,   345,   286,   311,   286,   282,   286,   282,
      -1,   344,   286,   311,   286,   282,   286,   282,   286,   278,
      -1,   310,    -1,   307,   286,   311,   286,   265,    -1,   307,
     286,   328,   286,   249,   286,   265,    -1,   307,   286,   329,
     286,   265,    -1,   307,   286,   330,   286,   265,    -1,   335,
     286,   311,   286,   268,    -1,   373,   286,   311,    -1,   331,
      -1,   332,    -1,   354,   286,   260,    -1,   354,   286,   299,
      -1,   353,   286,   311,   286,   260,   286,   261,   286,   262,
      -1,   356,    -1,   355,   286,   311,   286,   260,    -1,   364,
     286,   265,    -1,   363,   286,   311,   286,   265,   286,   267,
      -1,   366,   286,   269,    -1,   365,   286,   311,   286,   269,
      -1,   367,   286,   269,    -1,   368,   286,   311,   286,   269,
      -1,   374,    -1,   339,   286,   282,   286,   278,     4,   275,
      -1,   344,   286,   282,   286,   282,   286,   278,     4,   275,
      -1,   348,   286,   282,   286,   278,     4,   275,    -1,   349,
     286,   282,   286,   282,   286,   278,     4,   275,    -1,   307,
     286,   246,    -1,   355,   286,   382,   286,   260,   286,   272,
      -1,   363,   286,   382,   286,   265,   286,   267,   286,   274,
      -1,   363,   286,   345,   286,   265,   286,   267,   286,   255,
     286,   255,    -1,   363,   286,   362,   286,   265,   286,   267,
     286,   263,    -1,   363,   286,   375,   286,   265,   286,   267,
     286,   264,    -1,   365,   286,   382,   286,   269,   286,   270,
      -1,   365,   286,   369,   286,   269,   286,   285,    -1,   368,
     286,   382,   286,   269,   286,   270,    -1,   368,   286,   369,
     286,   269,   286,   285,    -1,   383,   286,   277,    -1,   374,
     286,   264,    -1,   341,   286,   278,   286,   248,    -1,   341,
     286,   278,    -1,   351,   286,   278,   286,   248,    -1,   351,
     286,   278,    -1,   363,   286,   265,   286,   263,    -1,   363,
     286,   265,   286,   263,   286,   274,    -1,   307,   286,   265,
      -1,   354,   286,   260,    -1,   354,   286,   299,    -1,   365,
     286,   269,   286,   269,    -1,   368,   286,   269,   286,   269,
      -1,   341,   286,   282,    -1,   351,   286,   282,    -1,   363,
     286,   265,   286,   267,    -1,   334,   286,   251,    -1,   335,
     286,   252,    -1,   341,   286,   265,   286,   254,    -1,   345,
     286,   265,   286,   255,   286,   255,    -1,   346,   286,   265,
     286,   256,    -1,   361,   286,   265,   286,   254,   286,   257,
     286,   258,    -1,   351,   286,   265,   286,   254,    -1,   358,
     286,   265,   286,   257,    -1,   359,   286,   265,   286,   258,
      -1,   360,   286,   265,   286,   259,    -1,   374,   286,   265,
     286,   264,    -1,   376,   286,   265,   286,   277,    -1,   377,
     286,   265,   286,   277,    -1,   355,   286,   265,   286,   260,
      -1,   355,   286,   265,   286,   300,    -1,   355,   286,   265,
     286,   301,    -1,    -1,   302,   286,    -1,   278,     4,   275,
      -1,   248,   286,   278,     4,   275,    -1,   378,    -1,   379,
      -1,   340,    -1,   350,    -1,   310,    -1,   308,    -1,   347,
      -1,   309,    -1,   354,   286,   260,    -1,   354,   286,   299,
      -1,   356,    -1,   364,   286,   265,    -1,   366,   286,   269,
      -1,   367,   286,   269,    -1,   271,   286,   266,   286,   265,
      -1,   302,   286,   271,   286,   266,   286,   265,    -1,   268,
     286,   265,    -1,   336,    -1,   337,    -1,   338,    -1,   282,
      -1,   282,    -1,   278,    -1,   282,    -1,   282,    -1,   299,
      -1,   278,    -1,   282,    -1,   282,    -1,   282,    -1,   282,
      -1,   279,    -1,   282,    -1,   282,    -1,   282,    -1,   282,
      -1,   278,    -1,   285,    -1,   285,    -1,   285,    -1,   285,
      -1,   285,    -1,   285,    -1,   276,    -1,   275,     5,   276,
      -1,   278,    -1,   285,    -1,   282,    -1,   279,    -1,   282,
      -1,   278,    -1,   283,    -1,   278,   283,    -1,   280,     6,
     280,    -1,     7,   280,     6,   280,    -1,     8,   280,     6,
     280,    -1,   281,    -1,   280,   281,    -1,     9,    -1,    10,
      -1,    11,    -1,    12,    -1,    13,    -1,    14,    -1,    15,
      -1,    16,    -1,    17,    -1,    18,    -1,   281,    -1,    10,
     280,    -1,    11,   280,    -1,    12,   280,    -1,    13,   280,
      -1,    14,   280,    -1,    15,   280,    -1,    16,   280,    -1,
      17,   280,    -1,    18,   280,    -1,    19,    -1,    20,    -1,
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
     220,    -1,   221,    -1,   286,    -1,   278,    -1,   284,   286,
      -1,   284,   278,    -1,   222,   284,   222,    -1,   223,   284,
     223,    -1,   224,    -1,   225,    -1,   226,    -1,    19,    22,
      22,    -1,    25,    23,    38,    -1,    31,    19,    34,    -1,
      39,    32,    31,    19,    34,    -1,    21,    30,    23,    19,
      36,    -1,    31,    33,    40,    23,    -1,    21,    36,    23,
      19,    38,    23,    -1,    22,    23,    37,    38,    36,    33,
      43,    -1,    30,    27,    37,    38,    -1,    30,    33,    19,
      22,    -1,    19,    30,    30,    -1,    32,    33,    32,    23,
      -1,    22,    23,    24,    19,    39,    30,    38,    -1,    32,
      33,    32,    89,    31,    33,    22,    19,    30,    -1,    36,
      23,    31,    33,    40,    23,    -1,    37,    23,    38,    -1,
      37,    39,    20,    37,    21,    36,    27,    20,    23,    -1,
      39,    32,    37,    39,    20,    37,    21,    36,    27,    20,
      23,    -1,    21,    26,    19,    32,    32,    23,    30,    -1,
      19,    40,    19,    27,    30,    19,    20,    30,    23,    89,
      23,    32,    25,    27,    32,    23,    37,    -1,    19,    40,
      19,    27,    30,    19,    20,    30,    23,    89,    19,    39,
      22,    27,    33,    89,    33,    39,    38,    34,    39,    38,
      89,    22,    36,    27,    40,    23,    36,    37,    -1,    21,
      26,    19,    32,    32,    23,    30,    37,    -1,    27,    32,
      24,    33,    -1,    19,    39,    22,    27,    33,    89,    33,
      39,    38,    34,    39,    38,    89,    22,    23,    40,    27,
      21,    23,    89,    21,    33,    39,    32,    38,    -1,    19,
      39,    22,    27,    33,    89,    33,    39,    38,    34,    39,
      38,    89,    22,    23,    40,    27,    21,    23,    89,    27,
      32,    24,    33,    -1,    31,    27,    22,    27,    89,    27,
      32,    34,    39,    38,    89,    22,    23,    40,    27,    21,
      23,    89,    21,    33,    39,    32,    38,    -1,    31,    27,
      22,    27,    89,    27,    32,    34,    39,    38,    89,    22,
      23,    40,    27,    21,    23,    89,    27,    32,    24,    33,
      -1,    31,    27,    22,    27,    89,    27,    32,    37,    38,
      36,    39,    31,    23,    32,    38,    89,    31,    19,    34,
      89,    21,    33,    39,    32,    38,    -1,    31,    27,    22,
      27,    89,    27,    32,    37,    38,    36,    39,    31,    23,
      32,    38,    89,    31,    19,    34,    89,    27,    32,    24,
      33,    -1,    31,    27,    22,    27,    89,    27,    32,    37,
      38,    36,    39,    31,    23,    32,    38,    89,    21,    33,
      39,    32,    38,    -1,    31,    27,    22,    27,    89,    27,
      32,    37,    38,    36,    39,    31,    23,    32,    38,    89,
      27,    32,    24,    33,    -1,    22,    20,    89,    27,    32,
      37,    38,    36,    39,    31,    23,    32,    38,    89,    22,
      27,    36,    23,    21,    38,    33,    36,    43,    89,    21,
      33,    39,    32,    38,    -1,    22,    20,    89,    27,    32,
      37,    38,    36,    39,    31,    23,    32,    38,    89,    22,
      27,    36,    23,    21,    38,    33,    36,    43,    89,    27,
      32,    24,    33,    -1,    22,    20,    89,    27,    32,    37,
      38,    36,    39,    31,    23,    32,    38,    89,    21,    33,
      39,    32,    38,    -1,    22,    20,    89,    27,    32,    37,
      38,    36,    39,    31,    23,    32,    38,    89,    27,    32,
      24,    33,    -1,    21,    26,    19,    32,    32,    23,    30,
      89,    21,    33,    39,    32,    38,    -1,    21,    26,    19,
      32,    32,    23,    30,    89,    27,    32,    24,    33,    -1,
      24,    42,    89,    37,    23,    32,    22,    89,    21,    33,
      39,    32,    38,    -1,    24,    42,    89,    37,    23,    32,
      22,    89,    27,    32,    24,    33,    -1,    20,    39,    24,
      24,    23,    36,    89,    24,    27,    30,    30,    -1,    37,
      38,    36,    23,    19,    31,    89,    21,    33,    39,    32,
      38,    -1,    40,    33,    27,    21,    23,    89,    21,    33,
      39,    32,    38,    -1,    38,    33,    38,    19,    30,    89,
      40,    33,    27,    21,    23,    89,    21,    33,    39,    32,
      38,    -1,    38,    33,    38,    19,    30,    89,    40,    33,
      27,    21,    23,    89,    21,    33,    39,    32,    38,    89,
      31,    19,    42,    -1,    25,    30,    33,    20,    19,    30,
      89,    27,    32,    24,    33,    -1,    27,    32,    37,    38,
      36,    39,    31,    23,    32,    38,    -1,    23,    32,    25,
      27,    32,    23,    -1,    33,    32,    89,    22,    23,    31,
      19,    32,    22,    -1,    33,    32,    89,    22,    23,    31,
      19,    32,    22,    89,    26,    33,    30,    22,    -1,    34,
      23,    36,    37,    27,    37,    38,    23,    32,    38,    -1,
      19,    39,    22,    27,    33,    89,    33,    39,    38,    34,
      39,    38,    89,    22,    23,    40,    27,    21,    23,    89,
      34,    19,    36,    19,    31,    23,    38,    23,    36,    -1,
      19,    39,    22,    27,    33,    89,    33,    39,    38,    34,
      39,    38,    89,    22,    23,    40,    27,    21,    23,    37,
      -1,    19,    39,    22,    27,    33,    89,    33,    39,    38,
      34,    39,    38,    89,    22,    23,    40,    27,    21,    23,
      -1,    19,    39,    22,    27,    33,    89,    33,    39,    38,
      34,    39,    38,    89,    22,    36,    27,    40,    23,    36,
      89,    34,    19,    36,    19,    31,    23,    38,    23,    36,
      -1,    19,    39,    22,    27,    33,    89,    33,    39,    38,
      34,    39,    38,    89,    22,    36,    27,    40,    23,    36,
      -1,    19,    39,    22,    27,    33,    89,    33,    39,    38,
      34,    39,    38,    89,    21,    26,    19,    32,    32,    23,
      30,    89,    34,    19,    36,    19,    31,    23,    38,    23,
      36,    -1,    19,    39,    22,    27,    33,    89,    33,    39,
      38,    34,    39,    38,    89,    21,    26,    19,    32,    32,
      23,    30,    -1,    19,    39,    22,    27,    33,    89,    33,
      39,    38,    34,    39,    38,    89,    38,    43,    34,    23,
      -1,    19,    40,    19,    27,    30,    19,    20,    30,    23,
      89,    31,    27,    22,    27,    89,    27,    32,    34,    39,
      38,    89,    22,    36,    27,    40,    23,    36,    37,    -1,
      31,    27,    22,    27,    89,    27,    32,    34,    39,    38,
      89,    22,    23,    40,    27,    21,    23,    89,    34,    19,
      36,    19,    31,    23,    38,    23,    36,    -1,    31,    27,
      22,    27,    89,    27,    32,    34,    39,    38,    89,    34,
      33,    36,    38,    89,    34,    19,    36,    19,    31,    23,
      38,    23,    36,    -1,    31,    27,    22,    27,    89,    27,
      32,    34,    39,    38,    89,    22,    23,    40,    27,    21,
      23,    37,    -1,    31,    27,    22,    27,    89,    27,    32,
      34,    39,    38,    89,    22,    23,    40,    27,    21,    23,
      -1,    31,    27,    22,    27,    89,    27,    32,    34,    39,
      38,    89,    22,    36,    27,    40,    23,    36,    89,    34,
      19,    36,    19,    31,    23,    38,    23,    36,    -1,    31,
      27,    22,    27,    89,    27,    32,    37,    38,    36,    39,
      31,    23,    32,    38,    -1,    31,    27,    22,    27,    89,
      27,    32,    37,    38,    36,    39,    31,    23,    32,    38,
      37,    -1,    31,    27,    22,    27,    89,    27,    32,    37,
      38,    36,    39,    31,    23,    32,    38,    89,    31,    19,
      34,    -1,    31,    27,    22,    27,    89,    27,    32,    37,
      38,    36,    39,    31,    23,    32,    38,    89,    31,    19,
      34,    37,    -1,    31,    27,    22,    27,    89,    27,    32,
      34,    39,    38,    89,    22,    36,    27,    40,    23,    36,
      -1,    31,    27,    22,    27,    89,    27,    32,    34,    39,
      38,    89,    34,    33,    36,    38,    -1,    31,    27,    22,
      27,    89,    27,    32,    34,    39,    38,    89,    21,    26,
      19,    32,    32,    23,    30,    -1,    31,    27,    22,    27,
      89,    27,    32,    34,    39,    38,    89,    38,    43,    34,
      23,    -1,    31,    27,    22,    27,    89,    27,    32,    34,
      39,    38,    -1,    31,    27,    22,    27,    89,    21,    33,
      32,    38,    36,    33,    30,    30,    23,    36,    -1,    24,
      42,    89,    37,    23,    32,    22,    -1,    24,    42,    89,
      37,    23,    32,    22,    37,    -1,    22,    20,    89,    27,
      32,    37,    38,    36,    39,    31,    23,    32,    38,    89,
      22,    27,    36,    23,    21,    38,    33,    36,    43,    -1,
      22,    20,    89,    27,    32,    37,    38,    36,    39,    31,
      23,    32,    38,    89,    22,    27,    36,    23,    21,    38,
      33,    36,    27,    23,    37,    -1,    22,    20,    89,    27,
      32,    37,    38,    36,    39,    31,    23,    32,    38,    37,
      -1,    22,    20,    89,    27,    32,    37,    38,    36,    39,
      31,    23,    32,    38,    -1,    22,    23,    37,    21,    36,
      27,    34,    38,    27,    33,    32,    -1,    24,    33,    36,
      21,    23,    -1,    24,    30,    19,    38,    -1,    32,    33,
      32,    89,    36,    23,    21,    39,    36,    37,    27,    40,
      23,    -1,    37,    23,    36,    40,    23,    36,    -1,    40,
      33,    30,    39,    31,    23,    -1,    30,    23,    40,    23,
      30,    -1,    31,    39,    38,    23,    -1,    37,    33,    30,
      33,    -1,    20,    43,    38,    23,    37,    -1,    34,    23,
      36,    21,    23,    32,    38,    19,    25,    23,    -1,    36,
      23,    37,    23,    38,    -1,    31,    27,    37,    21,    23,
      30,    30,    19,    32,    23,    33,    39,    37,    -1,    32,
      19,    31,    23,    -1,    23,    21,    26,    33,    -1,    35,
      39,    27,    38,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    97,    97,    98,   101,   102,   103,   104,   107,   108,
     109,   110,   111,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     133,   134,   135,   136,   137,   138,   139,   140,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   191,   192,   193,   194,   197,   200,   201,   202,
     203,   204,   205,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   266,   267,   268,
     269,   270,   271,   274,   277,   278,   281,   282,   285,   286,
     287,   290,   291,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   310,   311,   314,
     315,   318,   319,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   336,   337,   340,   343,   344,
     345,   348,   351,   354,   357,   360,   361,   364,   367,   370,
     373,   376,   379,   380,   383,   386,   389,   392,   395,   398,
     401,   404,   407,   410,   413,   414,   417,   418,   419,   420,
     428,   429,   432,   433,   436,   437,   438,   442,   443,   446,
     447,   448,   449,   450,   451,   452,   453,   454,   455,   458,
     459,   460,   461,   462,   463,   464,   465,   466,   467,   469,
     469,   469,   469,   469,   469,   469,   469,   469,   469,   469,
     469,   469,   469,   469,   469,   469,   469,   469,   469,   469,
     469,   469,   469,   469,   469,   470,   470,   470,   470,   470,
     470,   470,   470,   470,   470,   470,   470,   470,   470,   470,
     470,   470,   470,   470,   470,   470,   470,   470,   470,   470,
     470,   471,   471,   471,   471,   471,   471,   471,   471,   471,
     471,   472,   472,   472,   472,   472,   472,   472,   472,   472,
     472,   472,   472,   472,   473,   473,   473,   473,   473,   473,
     473,   474,   474,   474,   474,   474,   475,   475,   475,   475,
     476,   476,   476,   477,   477,   477,   478,   478,   478,   479,
     479,   479,   480,   480,   480,   481,   481,   481,   482,   482,
     482,   483,   483,   483,   484,   484,   484,   485,   485,   485,
     486,   486,   486,   487,   487,   487,   488,   488,   488,   489,
     489,   489,   490,   490,   490,   491,   491,   491,   492,   492,
     492,   493,   493,   493,   494,   494,   494,   495,   495,   495,
     496,   496,   496,   497,   497,   497,   498,   498,   498,   499,
     499,   499,   500,   500,   500,   501,   501,   501,   502,   502,
     502,   503,   503,   503,   504,   504,   504,   505,   505,   505,
     506,   506,   506,   507,   507,   507,   508,   508,   508,   509,
     509,   509,   510,   510,   510,   511,   511,   511,   512,   512,
     512,   513,   513,   513,   514,   514,   514,   515,   515,   515,
     516,   516,   516,   517,   517,   517,   518,   518,   521,   522,
     523,   524,   527,   528,   534,   537,   540,   543,   546,   549,
     552,   555,   558,   561,   564,   567,   570,   573,   576,   579,
     582,   585,   588,   591,   594,   597,   600,   603,   606,   609,
     612,   615,   618,   621,   624,   627,   630,   633,   636,   639,
     642,   645,   648,   651,   654,   657,   660,   663,   666,   669,
     672,   675,   678,   681,   684,   687,   690,   693,   696,   699,
     702,   705,   708,   711,   714,   717,   720,   723,   726,   729,
     732,   735,   738,   741,   744,   747,   750,   753,   756,   759,
     762,   765,   768,   771,   774,   777,   780,   783,   786,   789,
     792,   795,   798,   801,   804,   807,   810,   813,   816,   819,
     822,   825,   828
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
  "reset_instruction", "clear_instruction", "move_instruction",
  "destroy_instruction", "load_instruction", "set_chan_instruction",
  "modal_arg", "key_val_list", "buffer_size_type", "list_instruction",
  "load_instr_args", "load_engine_args", "instr_load_mode", "device_index",
  "audio_channel_index", "audio_output_type_name", "midi_input_port_index",
  "midi_input_channel_index", "midi_input_type_name", "midi_map",
  "midi_bank", "midi_prog", "midi_ctrl", "volume_value", "sampler_channel",
  "instrument_index", "fx_send_id", "engine_name", "pathname", "dirname",
  "filename", "map_name", "entry_name", "fx_send_name", "param_val_list",
  "param_val", "boolean", "string", "dotnum", "digits", "digit", "number",
  "char", "text", "stringval", "SP", "LF", "CR", "ADD", "GET", "MAP",
  "UNMAP", "CLEAR", "MOVE", "CREATE", "DESTROY", "LIST", "LOAD", "ALL",
  "NONE", "DEFAULT", "NON_MODAL", "REMOVE", "SET", "SUBSCRIBE",
  "UNSUBSCRIBE", "CHANNEL", "AVAILABLE_ENGINES",
  "AVAILABLE_AUDIO_OUTPUT_DRIVERS", "CHANNELS", "INFO",
  "AUDIO_OUTPUT_DEVICE_COUNT", "AUDIO_OUTPUT_DEVICE_INFO",
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
  "DESCRIPTION", "FORCE", "FLAT", "NON_RECURSIVE", "SERVER", "VOLUME",
  "LEVEL", "MUTE", "SOLO", "BYTES", "PERCENTAGE", "RESET", "MISCELLANEOUS",
  "NAME", "ECHO", "QUIT", 0
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
     232,   232,   232,   232,   232,   232,   232,   232,   233,   233,
     233,   233,   233,   233,   233,   233,   233,   233,   233,   233,
     233,   233,   233,   233,   233,   233,   233,   233,   233,   233,
     234,   234,   234,   234,   234,   234,   234,   234,   234,   234,
     234,   234,   234,   234,   234,   234,   234,   234,   234,   234,
     234,   234,   235,   235,   235,   235,   236,   237,   237,   237,
     237,   237,   237,   238,   238,   238,   238,   238,   238,   238,
     238,   238,   238,   238,   238,   238,   238,   238,   238,   238,
     238,   238,   238,   238,   238,   238,   238,   238,   238,   238,
     238,   238,   238,   238,   238,   238,   238,   238,   238,   238,
     238,   239,   239,   239,   239,   239,   239,   239,   239,   239,
     239,   239,   239,   239,   239,   239,   239,   240,   240,   240,
     240,   240,   240,   241,   242,   242,   243,   243,   244,   244,
     244,   245,   245,   246,   246,   246,   246,   246,   246,   246,
     246,   246,   246,   246,   246,   246,   246,   247,   247,   248,
     248,   249,   249,   250,   250,   250,   250,   250,   250,   250,
     250,   250,   250,   250,   250,   251,   251,   252,   253,   253,
     253,   254,   255,   256,   257,   258,   258,   259,   260,   261,
     262,   263,   264,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   275,   276,   276,   276,   276,
     277,   277,   278,   278,   279,   279,   279,   280,   280,   281,
     281,   281,   281,   281,   281,   281,   281,   281,   281,   282,
     282,   282,   282,   282,   282,   282,   282,   282,   282,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   284,   284,
     284,   284,   285,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   325,   326,   327,   328,   329,   330,   331,
     332,   333,   334,   335,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,   353,   354,   355,   356,   357,   358,   359,   360,   361,
     362,   363,   364,   365,   366,   367,   368,   369,   370,   371,
     372,   373,   374,   375,   376,   377,   378,   379,   380,   381,
     382,   383,   384
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     3,     0,     1,     1,     1,     1,     2,
       2,     2,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     1,
       1,     3,     7,     7,     5,     7,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,    16,    18,    18,    20,     7,     3,     3,     3,
       5,     3,     3,     1,     1,     5,     7,     9,     1,     5,
       7,     9,     1,     1,     5,     5,     7,     9,     7,     9,
       1,     5,     7,     5,     5,     5,     3,     1,     1,     3,
       3,     9,     1,     5,     3,     7,     3,     5,     3,     5,
       1,     7,     9,     7,     9,     3,     7,     9,    11,     9,
       9,     7,     7,     7,     7,     3,     3,     5,     3,     5,
       3,     5,     7,     3,     3,     3,     5,     5,     3,     3,
       5,     3,     3,     5,     7,     5,     9,     5,     5,     5,
       5,     5,     5,     5,     5,     5,     5,     0,     2,     3,
       5,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     1,     3,     3,     3,     5,     7,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     2,     3,     4,     4,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     1,
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
       2,     2,     3,     3,     1,     1,     1,     3,     3,     3,
       5,     5,     4,     6,     7,     4,     4,     3,     4,     7,
       9,     6,     3,     9,    11,     7,    17,    30,     8,     4,
      25,    24,    23,    22,    25,    24,    21,    20,    29,    28,
      19,    18,    13,    12,    13,    12,    11,    12,    11,    17,
      21,    11,    10,     6,     9,    14,    10,    29,    20,    19,
      29,    19,    30,    20,    17,    28,    27,    25,    18,    17,
      27,    15,    16,    19,    20,    17,    15,    18,    15,    10,
      15,     7,     8,    23,    25,    14,    13,    11,     5,     4,
      13,     6,     6,     5,     4,     4,     5,    10,     5,    13,
       4,     4,     4
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
       0,     0,     0,     0,     0,     0,     0,     1,   485,   486,
       2,     0,     9,   337,   332,   331,   329,   330,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     321,   323,   324,   325,   326,   327,   328,   333,   334,   335,
     336,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,   353,   354,   355,   356,
     357,   358,   359,   360,   361,   362,   363,   364,   365,   366,
     367,   368,   369,   370,   371,   372,   373,   374,   375,   376,
     377,   378,   379,   380,   381,   382,   383,   384,   385,   386,
     387,   388,   389,   390,   391,   392,   393,   394,   395,   396,
     397,   398,   399,   400,   401,   402,   403,   404,   405,   406,
     407,   408,   409,   410,   411,   412,   413,   414,   415,   416,
     417,   418,   419,   420,   421,   422,   423,   424,   425,   426,
     427,   428,   429,   430,   431,   432,   433,   434,   435,   436,
     437,   438,   439,   440,   441,   442,   443,   444,   445,   446,
     447,   448,   449,   450,   451,   452,   453,   454,   455,   456,
     457,   458,   459,   460,   461,   462,   463,   464,   465,   466,
     467,   468,   469,   470,   471,   472,   473,   474,   475,   476,
     477,   484,    12,   249,    11,   232,    10,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   487,     0,     0,     0,   488,     0,     0,   489,
       0,     0,     0,     0,   502,     0,     0,     0,     3,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   250,
     237,   251,   252,   253,   254,   255,   256,   257,   258,   322,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
     233,     0,     0,     0,    13,    30,    36,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    16,     0,
      93,    98,   110,   117,   118,     0,   102,     0,     0,     0,
       0,     0,    94,     0,   103,     0,     0,     0,     0,     0,
     122,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     130,     0,    14,     0,    15,     0,     0,    26,     0,     0,
      27,     0,     0,     0,     0,     0,    17,     0,     0,     0,
      18,     0,     0,     0,     0,     0,     0,     0,     0,    19,
     186,   188,   185,   183,   187,   184,     0,   191,     0,     0,
       0,     0,    20,     0,     0,    21,     0,     0,     0,     0,
       0,     0,     0,    22,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    23,    38,    39,    40,    41,
      49,    50,    51,    52,    53,    54,    55,    56,    42,    46,
      47,    48,    45,    44,    43,    58,    59,    57,    24,    60,
      61,    62,    63,    71,    72,    73,    74,    75,    76,    77,
      78,    64,    68,    69,    70,    67,    66,    65,    80,    81,
      79,    25,     0,     0,     0,     0,   495,   496,   492,   582,
       0,     0,     0,     0,     0,   238,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   177,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   491,     0,     0,     0,   578,     0,   490,     0,
       0,     0,     0,     0,     0,    37,   221,    31,   218,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   240,
     241,   242,   243,   244,   245,   246,   247,   248,     0,   119,
     208,   120,     0,     0,     0,     0,   124,   214,     0,   126,
     128,     0,   116,     0,     0,     0,     0,     0,     0,   154,
     155,     0,     0,     0,     0,     0,     0,   148,   150,     0,
     158,   159,     0,     0,     0,     0,     0,     0,   189,   190,
     192,   193,   194,     0,   161,     0,   220,     0,   162,     0,
     217,    87,    88,    89,     0,    91,     0,    92,     0,     0,
       0,     0,     0,     0,   135,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   146,   212,     0,
     237,   213,   145,   231,   230,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   153,   493,     0,   501,
       0,     0,     0,     0,     0,   479,     0,   478,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   178,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   581,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   494,     0,     0,     0,     0,     0,
     482,   481,   480,   483,     0,     0,    34,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     111,     0,     0,     0,   181,   182,   113,   114,   115,   104,
       0,    99,     0,     0,     0,   105,     0,     0,   497,   123,
      95,     0,     0,   127,   129,     0,     0,     0,     0,   209,
       0,     0,   156,   157,     0,     0,     0,   147,     0,   149,
     151,   211,   160,   216,     0,     0,     0,     0,     0,     0,
       0,   215,     0,   197,     0,    90,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   234,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   569,     0,     0,     0,     0,     0,     0,     0,     0,
     533,     0,     0,   571,     0,   572,   509,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   574,   575,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   580,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   235,   236,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   503,     0,
     505,     0,     0,     0,    35,    32,    33,     0,     0,   505,
       0,   561,     0,     0,     0,     0,   112,   100,     0,   108,
       0,    96,     0,   106,   125,     0,     0,     0,    86,   210,
       0,     0,     0,   561,     0,     0,   329,   330,   179,   224,
     226,   229,   228,   227,   152,   223,     0,     0,     0,     0,
       0,     0,   195,     0,   568,     0,     0,     0,     0,   163,
     201,     0,   202,   165,   203,   167,     0,     0,   174,   175,
     176,   168,   204,   169,   205,   206,   170,   207,     0,   171,
     172,   173,   131,     0,   133,     0,   136,     0,   573,     0,
       0,     0,     0,     0,     0,   142,   141,   219,   144,   143,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   508,     0,   562,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   504,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   576,     0,   101,   109,   107,    97,
     121,     0,     0,     0,     0,     0,     0,     0,   180,   225,
       0,     0,     0,     0,     0,   196,     0,     0,     0,     0,
     164,     0,     0,     0,   132,   134,     0,     0,     0,   139,
     140,   137,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   532,     0,
       0,     0,     0,     0,   498,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   500,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   166,     0,     0,   138,     0,     0,   526,     0,
       0,     0,     0,     0,   531,     0,     0,     0,     0,     0,
     528,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   559,     0,
       0,     0,     0,     0,     0,   523,     0,     0,   525,     0,
       0,     0,   527,     0,     0,     0,     0,     0,     0,     0,
       0,   566,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   566,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   499,     0,     0,   567,     0,   522,     0,
     524,     0,     0,   579,     0,   565,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     577,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   570,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   556,   551,     0,
     551,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   552,     0,
       0,    82,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     506,     0,     0,   549,   555,     0,     0,   529,     0,     0,
     549,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   556,   558,   560,     0,     0,     0,     0,     0,     0,
       0,     0,   529,     0,     0,     0,     0,     0,     0,     0,
       0,   548,     0,     0,     0,     0,     0,     0,    83,    84,
     222,   198,   199,   200,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   521,     0,     0,
       0,     0,     0,   553,     0,   539,   541,     0,     0,     0,
       0,     0,   553,     0,     0,     0,     0,   539,     0,     0,
       0,     0,     0,     0,     0,   544,     0,     0,   520,     0,
       0,     0,     0,     0,     0,     0,   543,   538,     0,     0,
       0,     0,     0,     0,   554,     0,     0,     0,    85,     0,
       0,     0,     0,     0,   557,     0,     0,     0,     0,     0,
     517,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     530,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   516,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   543,     0,
       0,     0,     0,   513,     0,     0,   563,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   512,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   511,     0,     0,   515,
       0,     0,     0,     0,   564,     0,   547,     0,     0,     0,
       0,   510,     0,     0,   514,     0,     0,     0,     0,     0,
     534,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     550,     0,   536,     0,   546,     0,     0,     0,     0,     0,
     545,     0,     0,     0,   519,     0,   540,     0,     0,   537,
     518,   542,   507,     0,   535
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    13,    14,    15,    16,   344,   465,   488,   392,   394,
     435,   358,   443,   406,   511,   397,   400,   410,   432,   744,
     695,   987,   953,   419,   724,   728,  1748,  1219,  1221,  1223,
    1231,  1233,  1236,   679,   978,  1188,   990,   777,   686,  1000,
     992,   729,   637,  1256,   725,   635,  1749,  1204,  1198,  1199,
     782,  1200,  1201,   779,   273,   687,   275,   806,   638,  1097,
      50,    51,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,  1235,  1229,  1230,   696,    27,    28,    29,    30,
     345,   360,   361,   362,   655,   466,   467,   468,   469,   470,
     471,   472,   473,   474,   475,   476,   477,   478,   479,   480,
     481,   482,   483,   484,   363,   364,   486,   433,   365,  1751,
    1752,  1753,   445,   366,   367,   368,   369,   370,   371,   747,
     372,   447,   373,   374,   375,   376,   377,   378,   346,   380,
     381,   382,   751,   752,   753,   767,   383,   384,   347,   386,
     348,   388,   771,   736,   642,   643,   389,   390,   768,   755,
     756,   954,   955,    31,   487,   762,   454,    32
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -1267
static const yytype_int16 yypact[] =
{
      38, -1267, -1267,    97,    79,   115,   157,   160,    34,     8,
     208,    66,   140,   214,   112,  2369, -1267,   -33,   -33,   -33,
     -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,
     -33,   -33, -1267,   227,   228,   230,   223,   275,   288,   315,
     313,   303,   322,   187,   327,   331,   248, -1267, -1267, -1267,
   -1267,   150, -1267, -1267, -1267, -1267, -1267, -1267, -1267,   525,
     525,   525,   525,   525,   525,   525,   525,   525, -1267, -1267,
   -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267,
   -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267,
   -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267,
   -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267,
   -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267,
   -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267,
   -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267,
   -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267,
   -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267,
   -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267,
   -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267,
   -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267,
   -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267,
   -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267,
   -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267,
   -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267,
   -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267,
   -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267,
   -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267,
   -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267,
   -1267, -1267,  3034, -1267, -1267, -1267, -1267,   133,   144,   346,
     346,   364,   390,   191,   191,   221,    93,   215,   155,   121,
     121,   399, -1267,   425,   426,   408, -1267,   409,   428, -1267,
     430,   410,   418,   431, -1267,   419,   436,   420, -1267, -1267,
   -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267,   525,
   -1267,   525,   525,   525,   525,   525,   525,   525,   525, -1267,
   -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267,
   -1267,   432,   441,   447, -1267, -1267,   -33,   -33,   -33,   243,
     449,   478,   468,   457,   474,   479,   472,   473, -1267,   -33,
   -1267, -1267, -1267, -1267, -1267,   -33, -1267,   -33,   -33,   -33,
     -33,   -33, -1267,   -33, -1267,   -33,   -33,   -33,   -33,   -33,
   -1267,   -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,
   -1267,   480, -1267,   -33, -1267,   -33,   482, -1267,   -33,   490,
   -1267,   -33,   -33,   485,   484,   500, -1267,   -33,   -33,   -33,
   -1267,   -33,   -33,   -33,   349,   503,   510,   512,   528, -1267,
   -1267, -1267, -1267, -1267, -1267, -1267,   -33, -1267,   -33,   -33,
     -33,   524, -1267,   -33,   -33, -1267,   -33,   -33,   -33,   -33,
     493,   537,   532, -1267,   -33,   -33,   -33,   -33,   -33,   -33,
     -33,   -33,   -33,   -33,   -33,   521,   522,   536,   543,   527,
     534,   544,   538,   540,   541, -1267, -1267, -1267, -1267, -1267,
   -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267,
   -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267,
   -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267,
   -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267,
   -1267, -1267,   -33,   539,   542,   548, -1267, -1267, -1267, -1267,
     545,   550,   556,   555,   558, -1267,   560,   502,   570,   168,
     168,    12,   571,   575,   576,   507,   572,   511,   577,   565,
     564,   573,   172,   583,   583,   583,   583,   583,   583,   583,
     583,   583,   583,   477,   583,   583,   583,   583,   535,   583,
     168,   168,   583,   583,   582,   579,   535,   590,   477,   533,
     168,   168,   594,   546,   599,  3034,  3034,   535,   535,   535,
     535,   601,   605,   547,   549,   603,   477,   535,   168,   168,
     596,    10,  3034,   535,   477,     5,   168,   612,   611,   617,
      81,   535,   535,   535,   535,   622,   166,    54,    54,   392,
    3253,   633,   632,   638,   569,   574,   626,    86,   624,   627,
     634,   535, -1267,   639,   631,   643, -1267,   635, -1267,   637,
     640,   648,   650,  2591,  2591, -1267, -1267, -1267, -1267,   649,
     645,   -33,   -33,   -33,   653,   656,   652,   658,   659,   654,
     662,   655,   671,   657,   666,   -33,   -33,   -33,   -33,   -33,
     -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,   525,
     525,   525,   525,   525,   525,   525,   525,   525,   679, -1267,
   -1267, -1267,   -33,   -33,   -33,   -33, -1267, -1267,   -33, -1267,
   -1267,   -33, -1267,   684,   680,   535,   -33,   -33,   688, -1267,
   -1267,   689,   -33,   -33,   690,   681,   692,  2591,  2591,   -33,
   -1267, -1267,   -33,   693,   694,   695,   709,   698, -1267, -1267,
   -1267, -1267, -1267,   691, -1267,   -33, -1267,   -33, -1267,   -33,
    3034, -1267, -1267, -1267,   715, -1267,   -33, -1267,   700,   716,
     728,   721,   184,   729, -1267,   -33,   -33,   -33,   -33,   -33,
     -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,
     -33,   742,   -33,   724,   741,   738,   -33,   -33,   -33,   -33,
     743,   -33,   -33,   -33,   -33,   525,   525, -1267, -1267,   259,
      33, -1267, -1267,  3034, -1267,   740,   744,   737,   745,   733,
     751,   746,   753,   752,   757,   756, -1267, -1267,   735, -1267,
     754,   758,   748,   750,   699,  3034,  1925, -1267,  2147,   764,
     755,   168,   168,   168,   759,   760,   762,   763,   765,   761,
     707,   766,   768,   769,   775,   535,   102,   535,   535,  3034,
     535,  3034,  3034,   535,   535,   535,   535,  3034,   535,   773,
     535,  3034,   535,   535,   168,   168,   720,   772,   -33, -1267,
     535,   730,   788,   168,   168,   789,   782,   732,  3034,  3034,
     535,   535,   790,   792,   793,   803,   739,   791,   535,   168,
     535,   794,   168,   796, -1267,   747,   809,   810,   797,   811,
     535,   535,   535,   535,   535,   535,   535,   535,   535,   535,
     535,   535,  3034,   535,  3034,   535,   812,   535,   823,   807,
     826,   535,   535,   535,   535,   813,   168,   168,   168,   168,
     467,   505,   525,   816,   830,   824,   825,   832,   839,   770,
     837,   842,   833,   843, -1267,   847,   834,   846,   836,   835,
   -1267,  3034, -1267, -1267,   838,   785,   -33,   -33,   -33,   786,
     852,   854,   841,   856,   848,   855,   845,   795,   860,   857,
   -1267,   844,   862,   -33, -1267, -1267, -1267, -1267, -1267, -1267,
    2591,  3034,   -33,   -33,   -33, -1267,  2591,   -33, -1267, -1267,
    3034,   -33,   -33, -1267, -1267,   861,   800,   535,   -33, -1267,
     864,   858, -1267, -1267,   805,   866,   869,   -33,  3472,   -33,
     -33, -1267, -1267, -1267,   814,   877,   865,   872,   878,   867,
     -33, -1267,   -33, -1267,   886, -1267,   819,   884,   885,   887,
     890,   891,   -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,
     -33,   -33,   -33,   -33,  3691,   -33,  3910,   -33,   895,   -33,
     892,   902,   899,   -33,   -33,   -33,   -33,   906,   -33,   -33,
     -33,   -33,   525,   525,   525,   840,   894,   905,   896,   900,
     901,   907,   909,   904,   851,   853,   913,   910,   911,   912,
     921, -1267,   908,   535,   168,   168,   922,   934,   928,   923,
   -1267,   937,   930, -1267,   920, -1267, -1267,   926,   929,   535,
    3034,   535,   535,   535,  3034,   535,   535,   535,   935,   938,
     -33,   535,   939,   932,   933,   950,   941,  3034,  2813,   168,
     943,   944,   940,   955,   947,   949,   535,   535,   959,   951,
     954,   956,   903, -1267, -1267,   535,   535,  3034,   535,   117,
     535,   477,  3034,   535,   392,  3253,  3253,  2813,  3034,  2813,
    3034, -1267,   168,   958,   953,   924,   535,   535,   535,   535,
     952,   168,   168,   168,   168,   525,   525,   960,   927,   964,
     957,   974,   942,   977,   981,   945,   975,   996, -1267,  1002,
   -1267,   991,   992,  1005, -1267, -1267, -1267,   993,  1000,   998,
     997,   999,   207,  1004,  1015,  1018, -1267,  2591,   -33, -1267,
     -33,  2591,   -33, -1267, -1267,  1006,  1008,   535, -1267, -1267,
    1007,  1009,  1003, -1267,  1012,  4129,   525,   525,  1042, -1267,
    3034, -1267, -1267, -1267, -1267, -1267,  1010,   998,  1014,   999,
     244,  1025, -1267,   -33, -1267,  1016,   342,   965,  1029, -1267,
   -1267,   -33, -1267, -1267,  3034, -1267,  1034,  1026, -1267, -1267,
   -1267, -1267, -1267, -1267, -1267, -1267, -1267,  3034,   -33, -1267,
   -1267, -1267,  1042,  4348,  1042,  4567, -1267,   969, -1267,  1039,
     -33,   -33,   -33,   -33,  1035, -1267, -1267, -1267, -1267, -1267,
    1022,  1040,   976,  1027,   979,  1043,   347,  1047,  1048,  1038,
    1044,  1049,  1037,  1041,  1057,  1045,  1058, -1267,  1053, -1267,
    1054,  1050,  1067,  1059,  1074,  3034,  3034,  3034,  3034,   535,
    1060,  1077,   -33,  1062,  1064,  1063,  1065,  2813,  2813,  1068,
    1070,  1071,  1076,  1080,   535,  1083,  1079,  1082,  1094,   535,
    1056,  1100,   535,  2813,  2813,  1103,  1104,   535,   535,   392,
     168,  1105,  1106,  1111,   269,  1108,   274,  1116,  1110,  1112,
    1120,  1121,  1126,  1117, -1267,  1127,  1123,  1118,  1130,  1072,
    1129,  1131,  1135,  1151, -1267,  1142,   -33,  3034,  3034,   -33,
   -1267,  1139,  1157,  3034,  1141,  1147,  1145,  1143,  1042, -1267,
    1146,  1155,  1144,  1152,  1149, -1267,  1156,  1154,  1150,   348,
   -1267,  1174,  1171,   -33,  1042,  1042,  1158,  1163,   -33, -1267,
   -1267, -1267,  1161,  1167,  1172,  1175,  1173,  1176,  1179,  1181,
    1180,  1177,  1178,  1194,  1182,  1197,  1187,  1199,  1185,  1184,
    1186,   194,  1203,  1140,  1191,  1208,  1195,  1193,  1204,   -33,
    1201,  1218,  1206,  1153,  1207,  1220,  1159,  1210, -1267,  1211,
    1162,  1209,  1213,  1214, -1267,   477,  1216,  1217,   535,  1229,
    1219,  1227,  1221,  1235,  1238,  1223,  1239,  1231,  1183,  1228,
    1233,  1237,  1248,  1240,  1241,  1244,  1242,  1243,  1245,  1250,
    1249,  1251,   122,  1254,  1200,  1261,  1257, -1267,   168,  1259,
    1260,  1253,  1272,  1258,  1263,  1275,  1267,  1262,   149,  1265,
    1266,  1273, -1267,  1271,  1270, -1267,  1274,  1276, -1267,  1277,
    1278,  1280,  1283,  1286, -1267,  1288,  1289,  1269,  1287,  1246,
   -1267,  1290,  1301,  1299,  1247,  1305,  1304,  1308,  1293,    88,
    1300,  1309,  1313,  1314,  1317,   -33,  1318,  1306,  1256,  1319,
    1264,  1310,  1320,  1323,  1268,  1324,  1316,  1311,  1279,  1321,
    1312,  1322,  1329,  1281,  1326, -1267,  1327,  1331, -1267,  1344,
    1348,  1315, -1267,  1333,    17,  1340,  1334,   395,  1349,  1350,
    1351,    18,  1335,  1352,  1345,  1354,  1355,  1359,  1357,   535,
    1358,  1294,  1362,  1347,  1369,    21,  1356,  1360,   404,  1363,
    1361,  1367,    49, -1267,  1370,  1365, -1267,  1377, -1267,  1325,
   -1267,  1371,  1368, -1267,  1374, -1267,  1388,  1375,  1389,  1390,
     114,  1382,  1385,  1330,  1396,  1393,  1381,  1386,  1387,  1384,
   -1267,  1395,   -33,  1397,  1403,  1400,  1408,  1412,  1409,  1399,
    1414,  1418,  1415,  1405,  1364,  1419,  1411,  1404,  1372,  1416,
    1426,   167,  1425,  1420,  1417,  1430,  1373, -1267,  1440,  1423,
    1437,  1376,  1444,  1441,  1442,  1449,  1448,  1383,    24,  1443,
   -1267,   392,  1436,  1434,  1455,  1438,  1450,  1458,    25,  1461,
    1445,  1460,  1383,    43,  1463,  1447,  1452,  1466,  1465,  1451,
    1456,  1457,  1462,  1471,  1406,  1464,  1479,  1467,  1468,  1470,
    1459,  1469,  1480,  1484,  1482,  1478,  1483,  1486, -1267,  1490,
    1485,   -33,  1495,  1505,  1502,  1494,  1508,  1503,  1504,  1510,
    1512,  1513,  1497,  1506,  1507,  1518,  1511,  1515,  1509,  1514,
    1519,  1521,   297,  1516,  1523,  1530,  1520,  1534,  1528,  1517,
   -1267,  1524,  1536,  1529,  1476,  1538,  1541,  1481,    16,  1546,
   -1267,  1547,  1548,  1529,  1550,  1540,  1552,  1487,  1555,  1544,
    1543, -1267, -1267, -1267,  1558,  1549,  1557,  1551,  1493,  1553,
    1556,  1564, -1267,  1566,  1559,  1562,  1567,  1560,  1554,  1561,
    1568, -1267,  1563,  1565,  1569,  1571,  1572,  1575,   -33, -1267,
   -1267, -1267, -1267, -1267,  1576,  1582,  1570,  1573,  1583,  1585,
    1577,  1578,  1586,  1589,  1590,  1579,  1574, -1267,   299,  1580,
    1591,  1584,  1587, -1267,  1592,  1593,  1525,  1594,  1588,  1595,
    1597,  1601,  1599,  1602,  1535,  1596,   168, -1267,  1593,  1600,
    1599,  1604,  1542,  1608,  1605, -1267,  1609,  1581, -1267,  1603,
    1607,  1610,  1611,  1612,  1598,  1613,  1606, -1267,  1614,  1615,
    1616,  1617,  1619,  1618, -1267,  1620,  1622,  1621, -1267,  1624,
    1606,  1625,  1627,  1628, -1267,   300,  1631,  1626,  1623,  1629,
   -1267,   308,  1630,  1634,  1633,  1635,  1638,  1636,  1642,  1646,
   -1267,  1648,  1647,  1639,  1657,  1658,  1649,  1645,  1650,  1644,
    1651,  1652, -1267,  1653,  1656,  1641,  1662,  1654,  1632,  1655,
      45,  1661,  1659,  1663,  1664,  1666,  1660,  1667, -1267,  1665,
    1675,  1668,  1669, -1267,  1670,  1676, -1267,  1672,  1684,  1688,
    1679,  1689,  1690,  1691,  1696,  1678,  1698,  1695,  1687,  1692,
    1637, -1267,  1699,  1694,  1701,  1693,  1686,  1683,  1697,  1700,
    1703,  1704,  1705,  1706,  1702,  1707, -1267,   309,  1708, -1267,
    1710,  1709,  1715,  1712, -1267,  1720, -1267,  1722,  1716,  1724,
    1726, -1267,  1717,  1719, -1267,  1729,  1718,  1713,  1721,  1723,
    1671,  1725,  1727,  1728,  1730,  1731,  1732,  1735,  1738,  1734,
   -1267,  1736, -1267,  1743, -1267,  1741,  1742,  1744,  1740,  1745,
   -1267,  1746,  1747,  1739, -1267,  1748, -1267,  1737,  1750, -1267,
   -1267, -1267, -1267,  1756, -1267
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267,
   -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267,
   -1267,  -836, -1267, -1267, -1267, -1267, -1267,  -897, -1266, -1267,
     282,   198, -1267,  -538,  -932, -1141,   335, -1103,   623, -1041,
   -1035,  -828,  -341,   586,  -849,   557,   -32,   448, -1047,   487,
    -698,   276,  -591,    31,   141,     4,   185,  1148,  -512,   -15,
    1749, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267, -1267,
   -1267, -1267,  -469, -1267, -1267,  1196, -1267, -1267, -1267, -1267,
    -118,  1501,  1522,  1526,  -240,  1498,  1499,  1500,  1527,  1531,
    1532,  1533,  1537,  1539,  1545,  1858,  2079,  2301,  2302,  2523,
    2524,  -255,  -253,  -250,   151, -1267,  4499, -1267,  1640, -1267,
   -1267, -1267, -1267,  4505,  -258, -1267, -1267,  4503,  -320, -1267,
    4507, -1267,  4506,  4508,  -252, -1267,   163,  -134,  -254,  4510,
   -1267,  1192, -1267, -1267, -1267, -1267,    57,  4511,     6,  4512,
    -200,   -26,  1188, -1267, -1267, -1267, -1267,  -261, -1267, -1267,
   -1267, -1267, -1267, -1267,  4509,  -309, -1267, -1267
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -250
static const yytype_int16 yytable[] =
{
     276,   958,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   636,   778,   274,
    1002,  1239,  1164,   989,   379,   407,   411,   453,   697,   734,
     699,   408,   412,   437,   449,   505,   639,   506,  -249,     1,
     507,     2,   694,  1370,   640,  1090,  1292,    42,   718,  1746,
    1747,  1378,  1184,    40,  1575,  1575,   732,     3,  1575,     4,
       5,  1668,  1668,     6,  1681,  1594,  1213,    41,     7,     8,
    1605,  1509,  1881,     9,    10,    11,   770,    12,   387,   726,
    1242,  1682,  1244,  1606,   681,   430,   761,  1607,  1876,    44,
     319,   321,   322,   323,   324,   325,   326,   327,   328,   700,
     741,  1250,  1251,  1252,  1253,    45,  1576,  1584,   791,    34,
    1597,  1542,   742,  1669,  1677,    35,   352,   719,   743,    33,
     431,   357,   951,   792,  1543,   733,   309,   669,   670,   671,
     672,   673,   674,   675,   676,   677,   952,  1619,    36,  1226,
     455,   456,   457,   458,  1499,   459,   460,   398,  1350,  1227,
    1620,   426,   461,  1182,   341,   342,  1500,   848,   462,   463,
     359,   464,  1475,   349,   343,   350,   351,   352,   353,   436,
     444,  1515,    46,   512,   440,   354,   341,   399,   441,   404,
      37,   355,   356,  1516,   357,   763,   442,    38,  1650,  1651,
     641,   271,   456,    39,  1652,   357,   764,   765,   761,   654,
     320,   320,   320,   320,   320,   320,   320,   320,   320,   462,
     403,   877,   464,  1448,    47,   404,  1380,  1449,   302,   689,
     690,  1225,   405,   878,   303,  1450,  1238,   633,   634,   702,
     703,    43,   633,   634,   633,   634,   341,   399,   633,   634,
     414,  1280,   415,   416,  1281,   417,   343,   721,   722,   292,
    1358,   293,   418,   294,   735,   737,   402,  -249,  -249,  -249,
     295,   439,   452,    -4,    -4,   912,  1374,  1375,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,  1301,   306,
     746,  1302,   532,   533,   385,   307,   766,   656,   401,   657,
    1385,   272,   658,   438,   451,  1388,  1386,   769,   772,   774,
     967,  1389,   969,   659,   660,   661,   662,   663,   664,   665,
     666,   667,   668,   296,   682,   683,   684,   685,  1729,   688,
    1800,  1847,   691,   692,  1730,   297,  1801,  1848,  1731,  1853,
    1922,   529,   530,   531,   298,  1854,  1923,    48,    49,   754,
     409,   413,   745,   300,   542,   450,   749,   299,   748,   301,
     543,   305,   544,   545,   546,   547,   548,   726,   549,  1029,
     550,   551,   552,   553,   554,   304,   555,   556,   557,   558,
     559,   560,   561,   562,   563,    48,  1306,   391,   565,  1273,
     566,  1328,  1422,   568,  1329,  1273,   570,   571,   581,   533,
     633,   634,   575,   576,   577,   396,   578,   579,   580,   775,
     776,   309,   669,   670,   671,   672,   673,   674,   675,   676,
     677,   586,   399,   587,   588,   589,  1579,  1580,   591,   592,
     341,   593,   594,   595,   596,  1600,  1601,  1240,  1241,   600,
     601,   602,   603,   604,   605,   606,   607,   608,   609,   610,
     485,   508,   393,   395,   513,   514,   515,   516,   519,  1346,
     517,   520,  1349,   518,   521,   523,   522,   340,   526,   524,
     525,   527,   525,   525,   525,   525,   525,   525,   525,   525,
     936,   937,   938,  1042,   528,   534,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   309,   669,   670,   671,
     672,   673,   674,   675,   676,   677,   678,   621,   535,   537,
     536,   538,   539,   973,   974,   540,   541,   564,  1592,   567,
     569,  1043,   982,   983,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   572,  1409,   573,   574,  1671,   582,
     583,  1005,   597,   778,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   309,   669,   670,   671,   672,   673,
     674,   675,   676,   677,   584,   585,   590,   680,   598,   599,
     611,   612,   613,   614,   616,  1038,  1039,  1040,  1041,   615,
     680,   617,   680,   619,   620,   622,   618,   627,   629,   630,
     623,  1228,   710,   711,   624,   625,  1203,  1205,   626,   628,
     680,   631,   632,   644,   645,   646,   647,   648,   680,   650,
     649,   651,   652,   653,   693,   757,   758,   759,   760,  1505,
     654,   694,   698,   781,   784,  1203,   704,  1203,   807,   807,
     636,   706,   701,   713,   714,   717,   811,   812,   813,  1255,
    1257,  1258,  1257,   723,   738,   705,   715,   739,   716,   740,
     825,   826,   827,   828,   829,   830,   831,   832,   833,   834,
     835,   836,   837,   838,   761,   785,   786,   787,   788,   790,
     793,   795,   797,   789,   798,   794,   799,   840,   841,   842,
     843,   800,   802,   844,   801,   803,   845,   804,   810,   809,
     814,   849,   850,   815,   816,   817,   818,   853,   854,   820,
     822,   819,   858,   859,   860,   821,   823,   861,   824,   680,
     319,   321,   322,   323,   324,   325,   326,   327,   328,   839,
     868,   846,   869,   847,   870,   851,   852,   855,   856,   857,
     862,   872,   864,  1165,  1166,   866,   863,   873,   778,   867,
     880,   881,   882,   883,   884,   885,   886,   887,   888,   889,
     890,   891,   892,   893,   894,   895,   865,   897,   871,   874,
     780,   901,   902,   903,   904,   875,   906,   907,   908,   909,
     876,   896,   879,   898,   899,   900,   905,   913,   914,   915,
     917,   918,   916,   919,   920,   921,   922,   923,   924,   926,
     927,   925,   928,   934,   944,  1203,  1203,   935,   929,   946,
     940,   932,   939,   932,   941,   942,   945,   943,   947,   949,
     948,  1203,  1203,   968,   976,   985,   910,   911,  1205,   975,
     320,   320,   320,   320,   320,   320,   320,   320,   320,   980,
     981,   986,   984,   994,   995,   996,   997,   999,   998,  1006,
    1004,  1008,  1009,   977,   959,  1010,  1007,   962,   963,   964,
     965,  1011,   680,  1028,   680,  1030,   971,  1031,  1032,  1045,
    1037,   707,   708,  1046,   979,  1049,  1047,  1048,  1050,  1051,
    1052,  1053,  1060,  1054,   991,   993,  1055,  1056,   730,  1058,
    1057,  1067,  1001,  1059,  1062,  1066,  1061,  1068,  1069,  1070,
    1071,  1073,  1072,  1075,  1074,  1078,   783,  1077,  1088,  1089,
    1076,  1092,   340,   340,  1094,  1093,  1096,  1025,  1095,  1027,
    1101,   680,  1102,  1100,  1103,  1104,  1105,  1108,  1109,   805,
     805,  1110,  1111,  1113,  1112,   340,   320,   320,  1131,  1133,
     525,  1063,  1064,  1065,  1114,  1134,  1135,  1140,  1149,  1147,
    1148,  1152,  1151,  1150,  1153,  1155,  1158,  1159,  1079,  1154,
    1156,  1160,  1157,  1044,  1163,  1080,   726,  1081,  1082,  1083,
    1161,  1084,  1085,  1162,  1168,  1167,  1086,  1087,  1169,  1171,
    1173,  1170,  1172,  1091,  1174,  1175,  1192,  1185,   340,  1186,
    1191,  1190,  1193,  1194,  1207,  1099,  1206,  1209,  1208,  1210,
    1211,   979,  1214,  1248,  1215,  1106,  1216,  1107,  1254,  1217,
     340,  1247,  1218,  1260,  1262,  1263,  1264,  1115,  1116,  1117,
    1118,  1119,  1120,  1121,  1122,  1123,  1124,  1125,  1126,  1266,
    1128,  1267,  1130,  1249,  1132,  1269,  1261,  1270,  1136,  1137,
    1138,  1139,  1271,  1141,  1142,  1143,  1144,  1272,  1274,  1273,
    1276,  1265,  1275,  1278,  1268,  1277,  1279,  1282,  1283,  1284,
     778,  1291,  1295,  1290,  1293,  1294,  1296,  1298,  1303,  1299,
    1300,   525,   525,   320,  1307,  1305,  1308,  1310,  1315,  1311,
    1316,  1322,  1321,  1325,  1323,  1324,  1330,  1001,  1326,  1331,
    1327,  1332,  1334,  1145,  1146,  1187,  1335,  1333,  1337,  1336,
    1371,  1339,   931,  1338,   931,  1178,  1179,  1180,  1342,   979,
    1183,   993,  1340,  1341,  1343,  1189,  1344,  1345,  1351,  1352,
    1354,  1356,  1202,  1355,  1357,   730,  1360,   960,   961,  1361,
    1362,  1001,  1364,   966,  1363,  1368,   340,   970,  1367,  1220,
    1222,  1366,  1220,   680,  1232,  1234,  1369,  1220,   781,   784,
     784,  1202,  1372,  1202,   988,   988,  1376,  1377,  1384,  1382,
     993,   993,   993,   993,  1383,   340,   340,  1387,  1390,  1391,
    1392,   340,  1393,  1395,  1394,   340,  1396,  1399,  1397,  1398,
    1402,  1401,  1285,  1286,  1400,  1287,  1288,  1289,  1024,  1403,
    1026,  1404,  1405,   340,  1406,  1407,  1408,  1410,  1411,  1412,
    1414,  1413,  1416,   320,   320,   525,  1415,  1418,  1417,  1421,
    1419,  1189,  1420,  1423,  1424,  1427,  1750,  1426,  1304,  1429,
     709,  1430,  1431,   712,  1437,  1433,  1309,  1434,  1432,   340,
     720,   340,  1435,  1436,  1439,  1438,   731,  1440,  1442,  1443,
    1446,  1441,  1444,  1312,  1445,  1447,  1451,   910,   911,  1452,
    1453,  1454,  1456,  1455,  1457,  1317,  1318,  1319,  1320,   780,
    1459,  1460,  1462,  1464,   796,  1461,  1463,  1469,  1465,  1466,
    1467,  1468,  1470,  1471,  1473,  1474,  1476,  1478,  1477,  1480,
    1479,  1481,  1482,  1483,  1484,   780,  1487,  1486,   780,  1488,
     780,  1489,  1485,  1491,  1750,  1492,  1497,  1353,  1490,  1493,
    1503,  1494,  1496,  1498,  1495,  1501,   525,   525,  1504,  1502,
    1506,  1508,  1507,  1189,  1509,  1511,  1510,  1512,  1513,  1517,
    1514,  1202,  1202,  1519,  1518,  1520,  1521,  1522,  1531,  1524,
    1529,  1525,  1526,  1222,  1523,  1527,  1232,  1202,  1202,  1528,
    1530,  1222,   991,   781,  1535,  1532,  1536,  1538,  1534,  1539,
    1540,  1541,  1545,  1544,  1546,  1533,  1537,   320,   320,  1547,
    1548,  1550,  1553,  1556,  1551,  1552,  1557,  1559,  1555,  1560,
    1561,  1564,  1573,  1554,  1574,  1565,  1177,  1558,  1425,  1563,
    1181,  1566,   340,  1428,  1568,  1569,   340,  1571,  1562,  1570,
    1567,  1572,  1577,  1195,  1578,  1585,  1581,  1582,  1583,  1586,
     340,  1587,  1590,  1576,  1594,   340,  1588,  1595,  1589,  1591,
    1593,  1596,  1599,  1224,  1458,  1609,  1598,  1603,  1237,  1610,
    1613,   783,   783,  1602,  1243,  1604,  1245,  1614,  1608,   340,
    1615,  1612,  1617,  1616,  1611,  1621,  1618,  1622,  1624,  1623,
    1625,  1626,   340,  1629,  1627,  1628,  1633,  1634,   340,  1234,
     340,  1635,  1222,  1630,  1636,  1632,  1637,  1638,   780,   780,
    1639,  1640,  1641,  1642,  1645,  1644,  1648,  1646,   950,  1649,
     956,   957,  1653,  1643,   780,   780,  1655,  1656,  1654,  1658,
     780,  1647,  1657,  1659,  1660,  1661,   972,  1662,  1663,  1664,
    1665,  1666,  1667,  1668,  1672,  1670,  1673,  1675,  1674,  1676,
    1678,  1680,  1683,  1684,  1689,  1679,  1685,  1681,  1686,  1688,
    1549,  1687,  1691,  1003,  1690,  1692,  1693,  1697,  1695,  1698,
    1696,  1703,  1699,  1012,  1013,  1014,  1015,  1016,  1017,  1018,
    1019,  1020,  1021,  1022,  1023,  1694,  1701,  1700,  1702,  1704,
    1705,  1706,  1709,  1707,  1033,  1034,  1035,  1036,  1710,  1711,
    1712,  1713,   340,   340,  1714,  1717,  1715,  1716,  1720,  1718,
    1719,  1722,  1724,  1727,  1728,  1721,  1733,  1723,  1725,  1734,
    1726,  1737,  1735,  1001,  1732,  1736,  1738,  1743,  1739,  1740,
    1744,   988,  1347,  1348,   988,  1742,  1741,  1754,  1755,  1757,
    1745,  1756,  1758,  1759,  1761,  1763,  1760,  1631,  1762,  1764,
    1766,  1765,  1768,  1771,  1767,  1774,  1769,  1772,  1770,  1779,
    1775,  1789,  1777,  1773,  1373,  1799,  1776,  1780,  1785,  1787,
    1778,  1781,  1783,  1782,  1784,  1788,  1791,  1790,  1792,  1795,
    1794,  1793,  1796,  1797,  1808,  1803,  1812,  1798,  1804,  1802,
    1813,  1815,  1806,  1472,  1816,  1805,  1810,  1822,  1809,   730,
    1807,  1821,  1817,  1811,  1820,   781,  1814,  1823,  1819,  1824,
    1827,  1826,  1828,  1829,  1841,  1830,  1832,  1851,  1834,  1839,
    1837,  1846,  1857,  1379,  1835,  1838,  1708,  1843,  1842,  1844,
    1859,  1861,  1840,  1845,  1849,  1850,  1855,  1852,  1856,  1862,
    1825,  1863,  1860,  1858,  1864,  1865,  1866,  1867,  1869,  1868,
    1871,  1877,  1870,  1872,  1876,  1873,  1874,  1831,  1875,  1246,
    1878,  1880,  1882,  1881,  1884,  1833,  1886,  1883,  1887,  1889,
    1893,  1885,  1176,  1895,  1888,  1836,  1897,  1891,  1894,  1892,
    1896,  1890,  1898,  1899,  1900,  1901,  1902,  1903,  1904,  1905,
    1910,  1879,  1912,  1913,  1911,  1906,  1907,  1909,  1918,  1212,
    1259,  1908,  1926,  1786,  1914,  1928,  1917,  1919,  1915,  1916,
    1920,  1925,  1927,  1929,  1930,  1921,  1924,  1932,  1931,  1933,
    1934,  1935,  1936,  1938,  1818,  1946,  1937,  1939,  1948,  1940,
    1941,  1949,  1951,  1942,  1944,  1943,  1952,  1955,  1381,  1945,
    1947,  1950,   780,  1953,  1962,  1954,  1956,  1960,  1964,  1958,
    1963,  1957,   808,  1959,  1961,  1359,   420,   727,   489,   490,
     491,     0,   750,     0,     0,     0,   773,     0,     0,     0,
     308,     0,     0,     0,     0,     0,     0,   421,     0,     0,
       0,   422,     0,     0,     0,     0,     0,   492,     0,     0,
       0,   493,   494,   495,     0,     0,     0,   496,     0,   497,
       0,     0,     0,     0,     0,   498,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   434,  1365,   329,    53,
      54,    55,    56,    57,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   339,    68,    69,    70,    71,    72,    73,
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
     264,   265,   266,   267,   268,   269,   270,   930,   499,   271,
     329,    53,    54,    55,    56,    57,   330,   331,   332,   333,
     334,   335,   336,   337,   338,   339,    68,    69,    70,    71,
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
     262,   263,   264,   265,   266,   267,   268,   269,   270,   500,
     933,   271,    52,    53,    54,    55,    56,    57,    58,    59,
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
     270,   501,   502,   271,   329,    53,    54,    55,    56,    57,
     330,   331,   332,   333,   334,   335,   336,   337,   338,   339,
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
     268,   269,   270,   503,   504,   271,   329,    53,    54,    55,
    1196,  1197,    58,    59,    60,    61,    62,    63,    64,    65,
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
     266,   267,   268,   269,   270,   633,   634,   329,    53,    54,
      55,    56,    57,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,    68,    69,    70,    71,    72,    73,    74,
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
     265,   266,   267,   268,   269,   270,   329,    53,    54,    55,
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
     266,   267,   268,   269,   270,   329,  1098,    54,    55,    56,
      57,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,    68,    69,    70,    71,    72,    73,    74,    75,    76,
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
     267,   268,   269,   270,   329,  1127,    54,    55,    56,    57,
     330,   331,   332,   333,   334,   335,   336,   337,   338,   339,
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
     268,   269,   270,   329,  1129,    54,    55,    56,    57,   330,
     331,   332,   333,   334,   335,   336,   337,   338,   339,    68,
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
     269,   270,   329,  1297,    54,    55,    56,    57,   330,   331,
     332,   333,   334,   335,   336,   337,   338,   339,    68,    69,
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
     270,   329,  1313,    54,    55,    56,    57,   330,   331,   332,
     333,   334,   335,   336,   337,   338,   339,    68,    69,    70,
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
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     329,  1314,    54,    55,    56,    57,   330,   331,   332,   333,
     334,   335,   336,   337,   338,   339,    68,    69,    70,    71,
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
     262,   263,   264,   265,   266,   267,   268,   269,   270,   509,
     423,   446,   424,   425,   448,   427,   428,   429,     0,   510
};

static const yytype_int16 yycheck[] =
{
      15,   829,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,   529,   609,    15,
     869,  1124,  1063,   859,   278,   283,   284,   288,   566,    24,
     568,   283,   284,   287,   288,   290,    24,   290,     5,     1,
     290,     3,    32,  1309,    32,   977,  1187,    39,   586,    33,
      34,  1317,  1087,    19,    37,    37,   594,    19,    37,    21,
      22,    37,    37,    25,    21,    22,  1107,    33,    30,    31,
      21,    22,    27,    35,    36,    37,    22,    39,   278,   591,
    1127,    38,  1129,    34,   553,   285,    32,    38,    43,    23,
      59,    60,    61,    62,    63,    64,    65,    66,    67,   568,
      19,  1136,  1137,  1138,  1139,    39,    89,    89,    22,    30,
      89,    23,    31,    89,    89,    36,    23,   586,    37,    22,
      27,    40,    20,    37,    36,   594,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    34,    23,    23,    22,
      19,    20,    21,    22,    22,    24,    25,   281,  1289,    32,
      36,   285,    31,  1085,    21,    22,    34,   695,    37,    38,
     278,    40,  1428,    19,    31,    21,    22,    23,    24,   287,
     288,    22,    32,   291,    19,    31,    21,    22,    23,    24,
      23,    37,    38,    34,    40,    19,    31,    27,    21,    22,
     531,   224,    20,    33,    27,    40,    30,    31,    32,    27,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    37,
      19,    27,    40,    19,     0,    24,  1319,    23,    31,   560,
     561,  1118,    31,    39,    37,    31,  1123,   222,   223,   570,
     571,    23,   222,   223,   222,   223,    21,    22,   222,   223,
      19,    34,    21,    22,    37,    24,    31,   588,   589,    22,
    1297,    23,    31,    23,   595,   596,   282,   224,   225,   226,
      37,   287,   288,   225,   226,     6,  1313,  1314,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    34,    31,
     600,    37,    39,    40,   278,    37,   606,   542,   282,   542,
      21,    15,   542,   287,   288,    21,    27,   606,   607,   608,
     838,    27,   840,   543,   544,   545,   546,   547,   548,   549,
     550,   551,   552,    38,   554,   555,   556,   557,    21,   559,
      21,    21,   562,   563,    27,    37,    27,    27,    31,    21,
      21,   346,   347,   348,    19,    27,    27,   225,   226,   600,
     283,   284,   600,    40,   359,   288,   600,    34,   600,    27,
     365,    20,   367,   368,   369,   370,   371,   869,   373,   897,
     375,   376,   377,   378,   379,    38,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   225,    34,    31,   393,    37,
     395,    34,    34,   398,    37,    37,   401,   402,    39,    40,
     222,   223,   407,   408,   409,    31,   411,   412,   413,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,   426,    22,   428,   429,   430,    21,    22,   433,   434,
      21,   436,   437,   438,   439,    21,    22,  1125,  1126,   444,
     445,   446,   447,   448,   449,   450,   451,   452,   453,   454,
     289,   290,   279,   280,    19,    19,    38,    38,    38,  1285,
      22,    33,  1288,    23,    23,    19,    37,   272,    26,    39,
     319,    20,   321,   322,   323,   324,   325,   326,   327,   328,
     811,   812,   813,     6,    27,    26,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,   512,    20,    42,
      32,    27,    23,   844,   845,    33,    33,    27,  1549,    27,
      20,     6,   853,   854,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    39,  1353,    42,    27,  1631,    26,
      20,   872,    39,  1124,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    42,    27,    32,   553,    21,    27,
      39,    39,    26,    20,    30,   906,   907,   908,   909,    42,
     566,    27,   568,    33,    33,    36,    38,    21,    20,    19,
      38,  1119,   578,   579,    36,    40,  1098,  1099,    38,    34,
     586,    89,    22,    22,    19,    19,    89,    25,   594,    22,
      89,    36,    38,    30,    22,   601,   602,   603,   604,  1458,
      27,    32,    22,   609,   610,  1127,    22,  1129,   633,   634,
    1132,    22,    89,    22,    19,    22,   641,   642,   643,  1141,
    1142,  1143,  1144,    37,    22,    89,    89,    26,    89,    22,
     655,   656,   657,   658,   659,   660,   661,   662,   663,   664,
     665,   666,   667,   668,    32,    22,    24,    19,    89,    33,
      36,    27,    23,    89,    33,    38,    23,   682,   683,   684,
     685,    36,    32,   688,    37,    27,   691,    27,    33,    30,
      27,   696,   697,    27,    32,    27,    27,   702,   703,    27,
      19,    37,   707,   708,   709,    40,    39,   712,    32,   695,
     669,   670,   671,   672,   673,   674,   675,   676,   677,    30,
     725,    27,   727,    33,   729,    27,    27,    27,    37,    27,
      27,   736,    27,  1064,  1065,    27,    32,    27,  1319,    38,
     745,   746,   747,   748,   749,   750,   751,   752,   753,   754,
     755,   756,   757,   758,   759,   760,    37,   762,    33,    33,
     609,   766,   767,   768,   769,    27,   771,   772,   773,   774,
      39,    19,    33,    39,    23,    27,    23,    27,    24,    32,
      37,    20,    27,    27,    21,    23,    19,    21,    43,    21,
      32,    27,    32,    19,    23,  1297,  1298,    32,    89,    23,
      30,   806,    33,   808,    32,    32,    89,    32,    30,    24,
      31,  1313,  1314,    30,    32,    23,   775,   776,  1320,    89,
     669,   670,   671,   672,   673,   674,   675,   676,   677,    89,
      32,    89,    33,    33,    32,    32,    23,    36,    89,    33,
      36,    22,    22,   848,   830,    38,    89,   833,   834,   835,
     836,    30,   838,    31,   840,    22,   842,    40,    22,    33,
      37,   575,   576,    23,   850,    23,    32,    32,    19,    89,
      23,    19,    27,    30,   860,   861,    23,    20,   592,    23,
      36,    19,   868,    37,    89,    89,    38,    23,    37,    23,
      32,    36,    27,    23,    89,    23,   610,    43,    27,    89,
      33,    27,   707,   708,    89,    37,    27,   893,    32,   895,
      23,   897,    37,    89,    32,    27,    39,    21,    89,   633,
     634,    27,    27,    23,    27,   730,   775,   776,    23,    27,
     779,   936,   937,   938,    33,    23,    27,    21,    23,    89,
      36,    30,    32,    37,    27,    31,    23,    27,   953,    30,
      89,    30,    89,   912,    36,   960,  1458,   962,   963,   964,
      38,   966,   967,    32,    20,    33,   971,   972,    30,    22,
      40,    38,    32,   978,    38,    36,    33,    32,   783,    31,
      38,    32,    22,    32,    30,   990,    33,    22,    38,    32,
      31,   977,    23,    30,    33,  1000,    32,  1002,    36,    33,
     805,    33,    89,    33,    30,    38,    22,  1012,  1013,  1014,
    1015,  1016,  1017,  1018,  1019,  1020,  1021,  1022,  1023,    32,
    1025,    30,  1027,    89,  1029,    40,    89,    21,  1033,  1034,
    1035,  1036,    20,  1038,  1039,  1040,  1041,    36,    23,    37,
      30,    89,    39,    36,    89,    37,    37,    33,    23,    21,
    1631,    33,    39,    37,    37,    36,    34,     5,    23,    39,
      36,   910,   911,   912,    89,    39,    27,    23,    89,    33,
      21,    39,    27,    36,    24,    89,    19,  1063,    89,    21,
      27,    33,    23,  1042,  1043,  1090,    39,    33,    21,    38,
      24,    23,   806,    38,   808,  1081,  1082,  1083,    38,  1085,
    1086,  1087,    39,    39,    27,  1091,    37,    23,    38,    22,
      38,    38,  1098,    39,    39,   829,    38,   831,   832,    39,
      39,  1107,    32,   837,    38,    33,   931,   841,    39,  1115,
    1116,    38,  1118,  1119,  1120,  1121,    32,  1123,  1124,  1125,
    1126,  1127,    32,  1129,   858,   859,    33,    33,    27,    34,
    1136,  1137,  1138,  1139,    38,   960,   961,    39,    32,    39,
      38,   966,    32,    27,    33,   970,    39,    39,    31,    36,
      31,    89,  1177,  1178,    34,  1180,  1181,  1182,   892,    38,
     894,    36,    21,   988,    32,    36,    19,    36,    31,    34,
      34,    38,    38,  1042,  1043,  1044,    31,    38,    36,    39,
      34,  1187,    38,    19,    23,    32,  1708,    39,  1213,    38,
     577,    34,    30,   580,    24,    32,  1221,    31,    33,  1024,
     587,  1026,    33,    32,    36,    38,   593,    23,    21,    32,
      36,    39,    23,  1238,    39,    39,    23,  1196,  1197,    89,
      39,    23,    39,    38,    30,  1250,  1251,  1252,  1253,  1098,
      39,    23,    89,    23,   621,    39,    39,    38,    89,    39,
      39,    89,    39,    39,    38,    38,    27,    30,    39,    24,
      39,    23,    39,    24,    33,  1124,    33,    39,  1127,    32,
    1129,    23,    89,    32,  1786,    31,    27,  1292,    38,    37,
      19,    38,    32,    32,    39,    31,  1145,  1146,    31,    89,
      31,    38,    32,  1289,    22,    32,    38,    22,    31,    34,
      38,  1297,  1298,    30,    38,    34,    36,    33,    39,    32,
      22,    33,    32,  1309,    38,    32,  1312,  1313,  1314,    33,
      31,  1317,  1318,  1319,    23,    38,    27,    22,    38,    25,
      22,    38,    23,    33,    21,    89,    89,  1196,  1197,    25,
      23,    23,    23,    23,    38,    89,    23,    23,    38,    33,
      39,    39,    37,    89,    21,    33,  1080,    89,  1373,    38,
    1084,    32,  1177,  1378,    38,    38,  1181,    23,    89,    38,
      89,    23,    32,  1097,    40,    40,    27,    27,    27,    27,
    1195,    36,    23,    89,    22,  1200,    32,    40,    33,    32,
      32,    22,    32,  1117,  1409,    30,    40,    36,  1122,    22,
      32,  1125,  1126,    40,  1128,    38,  1130,    33,    38,  1224,
      22,    40,    23,    38,    89,    33,    26,    32,    22,    89,
      27,    40,  1237,    39,    38,    38,    23,    27,  1243,  1425,
    1245,    23,  1428,    38,    22,    38,    27,    38,  1297,  1298,
      26,    23,    27,    38,    33,    26,    30,    43,   825,    23,
     827,   828,    27,    89,  1313,  1314,    39,    27,    38,    19,
    1319,    89,    89,    40,    27,    89,   843,    23,    27,    27,
      21,    23,    89,    37,    40,    32,    21,    27,    40,    21,
      19,    21,    19,    36,    27,    40,    34,    21,    23,    33,
    1505,    40,    21,   870,    32,    89,    32,    27,    31,    40,
      32,    23,    33,   880,   881,   882,   883,   884,   885,   886,
     887,   888,   889,   890,   891,    36,    32,    37,    36,    36,
      34,    31,    27,    38,   901,   902,   903,   904,    23,    27,
      36,    23,  1347,  1348,    31,    23,    32,    27,    32,    26,
      43,    23,    27,    24,    23,    38,    23,    36,    39,    19,
      36,    23,    32,  1549,    38,    21,    39,    19,    34,    23,
      19,  1285,  1286,  1287,  1288,    89,    37,    21,    21,    19,
      89,    23,    32,    21,    19,    32,    89,  1592,    34,    21,
      23,    32,    89,    19,    33,    23,    33,    21,    32,    21,
      23,    21,    38,    34,  1312,    21,    36,    34,    23,    23,
      39,    36,    31,    34,    32,    23,    23,    34,    23,    23,
      32,    34,    23,    23,    89,    24,    19,    38,    34,    39,
      19,    19,    30,  1425,    89,    38,    38,    19,    34,  1353,
      37,    89,    36,    38,    30,  1631,    37,    32,    38,    30,
      33,    38,    32,    32,    22,    33,    33,    24,    34,    31,
      33,    23,    19,  1318,    39,    36,  1671,    33,    37,    34,
      22,    19,    42,    36,    33,    39,    36,    38,    34,    23,
      89,    23,    36,    38,    27,    36,    19,    19,    33,    30,
      36,    19,    32,    32,    43,    33,    33,    89,    32,  1132,
      36,    36,    31,    27,    31,    89,    36,    38,    31,    24,
      24,    37,  1079,    19,    39,    89,    27,    38,    36,    39,
      22,    43,    23,    23,    23,    19,    38,    19,    23,    32,
      19,    89,    36,    40,    31,    33,    89,    33,    23,  1106,
    1144,    32,    23,  1748,    37,    23,    32,    31,    38,    36,
      38,    31,    27,    23,    22,    38,    38,    23,    32,    23,
      33,    32,    23,    40,  1786,    24,    38,    36,    23,    36,
      89,    23,    26,    38,    36,    38,    23,    23,  1320,    39,
      38,    37,  1631,    32,    37,    33,    36,    38,    22,    33,
      30,    36,   634,    36,    36,  1298,   285,   591,   290,   290,
     290,    -1,   600,    -1,    -1,    -1,   608,    -1,    -1,    -1,
      51,    -1,    -1,    -1,    -1,    -1,    -1,   285,    -1,    -1,
      -1,   285,    -1,    -1,    -1,    -1,    -1,   290,    -1,    -1,
      -1,   290,   290,   290,    -1,    -1,    -1,   290,    -1,   290,
      -1,    -1,    -1,    -1,    -1,   290,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   286,  1304,     3,     4,
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
     215,   216,   217,   218,   219,   220,   221,   222,   290,   224,
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
     213,   214,   215,   216,   217,   218,   219,   220,   221,   290,
     223,   224,     3,     4,     5,     6,     7,     8,     9,    10,
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
     221,   290,   290,   224,     3,     4,     5,     6,     7,     8,
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
     219,   220,   221,   290,   290,   224,     3,     4,     5,     6,
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
     217,   218,   219,   220,   221,   222,   223,     3,     4,     5,
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
     213,   214,   215,   216,   217,   218,   219,   220,   221,   290,
     285,   288,   285,   285,   288,   285,   285,   285,    -1,   290
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     1,     3,    19,    21,    22,    25,    30,    31,    35,
      36,    37,    39,   228,   229,   230,   231,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   303,   304,   305,
     306,   380,   384,    22,    30,    36,    23,    23,    27,    33,
      19,    33,    39,    23,    23,    39,    32,     0,   225,   226,
     287,   288,     3,     4,     5,     6,     7,     8,     9,    10,
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
     221,   224,   278,   281,   282,   283,   286,   286,   286,   286,
     286,   286,   286,   286,   286,   286,   286,   286,   286,   286,
     286,   286,    22,    23,    23,    37,    38,    37,    19,    34,
      40,    27,    31,    37,    38,    20,    31,    37,   287,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,   280,
     281,   280,   280,   280,   280,   280,   280,   280,   280,     3,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
     283,    21,    22,    31,   232,   307,   355,   365,   367,    19,
      21,    22,    23,    24,    31,    37,    38,    40,   238,   307,
     308,   309,   310,   331,   332,   335,   340,   341,   342,   343,
     344,   345,   347,   349,   350,   351,   352,   353,   354,   355,
     356,   357,   358,   363,   364,   365,   366,   367,   368,   373,
     374,    31,   235,   353,   236,   353,    31,   242,   354,    22,
     243,   365,   368,    19,    24,    31,   240,   341,   351,   363,
     244,   341,   351,   363,    19,    21,    22,    24,    31,   250,
     308,   309,   310,   340,   347,   350,   354,   356,   364,   366,
     367,    27,   245,   334,   335,   237,   307,   355,   365,   368,
      19,    23,    31,   239,   307,   339,   344,   348,   349,   355,
     363,   365,   368,   374,   383,    19,    20,    21,    22,    24,
      25,    31,    37,    38,    40,   233,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   333,   381,   234,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   333,
     381,   241,   307,    19,    19,    38,    38,    22,    23,    38,
      33,    23,    37,    19,    39,   281,    26,    20,    27,   286,
     286,   286,    39,    40,    26,    20,    32,    42,    27,    23,
      33,    33,   286,   286,   286,   286,   286,   286,   286,   286,
     286,   286,   286,   286,   286,   286,   286,   286,   286,   286,
     286,   286,   286,   286,    27,   286,   286,    27,   286,    20,
     286,   286,    39,    42,    27,   286,   286,   286,   286,   286,
     286,    39,    26,    20,    42,    27,   286,   286,   286,   286,
      32,   286,   286,   286,   286,   286,   286,    39,    21,    27,
     286,   286,   286,   286,   286,   286,   286,   286,   286,   286,
     286,    39,    39,    26,    20,    42,    30,    27,    38,    33,
      33,   286,    36,    38,    36,    40,    38,    21,    34,    20,
      19,    89,    22,   222,   223,   272,   285,   269,   285,    24,
      32,   269,   371,   372,    22,    19,    19,    89,    25,    89,
      22,    36,    38,    30,    27,   311,   328,   329,   330,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   311,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,   260,
     282,   299,   311,   311,   311,   311,   265,   282,   311,   269,
     269,   311,   311,    22,    32,   247,   302,   260,    22,   260,
     299,    89,   269,   269,    22,    89,    22,   278,   278,   265,
     282,   282,   265,    22,    19,    89,    89,    22,   260,   299,
     265,   269,   269,    37,   251,   271,   285,   302,   252,   268,
     278,   265,   260,   299,    24,   269,   370,   269,    22,    26,
      22,    19,    31,    37,   246,   341,   345,   346,   351,   355,
     358,   359,   360,   361,   374,   376,   377,   282,   282,   282,
     282,    32,   382,    19,    30,    31,   345,   362,   375,   382,
      22,   369,   382,   369,   382,     7,     8,   264,   279,   280,
     281,   282,   277,   278,   282,    22,    24,    19,    89,    89,
      33,    22,    37,    36,    38,    27,   265,    23,    33,    23,
      36,    37,    32,    27,    27,   278,   284,   286,   284,    30,
      33,   286,   286,   286,    27,    27,    32,    27,    27,    37,
      27,    40,    19,    39,    32,   286,   286,   286,   286,   286,
     286,   286,   286,   286,   286,   286,   286,   286,   286,    30,
     286,   286,   286,   286,   286,   286,    27,    33,   260,   286,
     286,    27,    27,   286,   286,    27,    37,    27,   286,   286,
     286,   286,    27,    32,    27,    37,    27,    38,   286,   286,
     286,    33,   286,    27,    33,    27,    39,    27,    39,    33,
     286,   286,   286,   286,   286,   286,   286,   286,   286,   286,
     286,   286,   286,   286,   286,   286,    19,   286,    39,    23,
      27,   286,   286,   286,   286,    23,   286,   286,   286,   286,
     280,   280,     6,    27,    24,    32,    27,    37,    20,    27,
      21,    23,    19,    21,    43,    27,    21,    32,    32,    89,
     222,   278,   286,   223,    19,    32,   269,   269,   269,    33,
      30,    32,    32,    32,    23,    89,    23,    30,    31,    24,
     265,    20,    34,   249,   378,   379,   265,   265,   268,   282,
     278,   278,   282,   282,   282,   282,   278,   260,    30,   260,
     278,   282,   265,   269,   269,    89,    32,   286,   261,   282,
      89,    32,   269,   269,    33,    23,    89,   248,   278,   248,
     263,   282,   267,   282,    33,    32,    32,    23,    89,    36,
     266,   282,   271,   265,    36,   269,    33,    89,    22,    22,
      38,    30,   265,   265,   265,   265,   265,   265,   265,   265,
     265,   265,   265,   265,   278,   282,   278,   282,    31,   260,
      22,    40,    22,   265,   265,   265,   265,    37,   269,   269,
     269,   269,     6,     6,   280,    33,    23,    32,    32,    23,
      19,    89,    23,    19,    30,    23,    20,    36,    23,    37,
      27,    38,    89,   286,   286,   286,    89,    19,    23,    37,
      23,    32,    27,    36,    89,    23,    33,    43,    23,   286,
     286,   286,   286,   286,   286,   286,   286,   286,    27,    89,
     261,   286,    27,    37,    89,    32,    27,   286,     4,   286,
      89,    23,    37,    32,    27,    39,   286,   286,    21,    89,
      27,    27,    27,    23,    33,   286,   286,   286,   286,   286,
     286,   286,   286,   286,   286,   286,   286,     4,   286,     4,
     286,    23,   286,    27,    23,    27,   286,   286,   286,   286,
      21,   286,   286,   286,   286,   280,   280,    89,    36,    23,
      37,    32,    30,    27,    30,    31,    89,    89,    23,    27,
      30,    38,    32,    36,   266,   269,   269,    33,    20,    30,
      38,    22,    32,    40,    38,    36,   265,   278,   282,   282,
     282,   278,   261,   282,   267,    32,    31,   286,   262,   282,
      32,    38,    33,    22,    32,   278,     7,     8,   275,   276,
     278,   279,   282,   285,   274,   285,    33,    30,    38,    22,
      32,    31,   265,   266,    23,    33,    32,    33,    89,   254,
     282,   255,   282,   256,   278,   254,    22,    32,   260,   300,
     301,   257,   282,   258,   282,   299,   259,   278,   254,   264,
     277,   277,   275,   278,   275,   278,   272,    33,    30,    89,
     267,   267,   267,   267,    36,   285,   270,   285,   285,   270,
      33,    89,    30,    38,    22,    89,    32,    30,    89,    40,
      21,    20,    36,    37,    23,    39,    30,    37,    36,    37,
      34,    37,    33,    23,    21,   286,   286,   286,   286,   286,
      37,    33,   262,    37,    36,    39,    34,     4,     5,    39,
      36,    34,    37,    23,   286,    39,    34,    89,    27,   286,
      23,    33,   286,     4,     4,    89,    21,   286,   286,   286,
     286,    27,    39,    24,    89,    36,    89,    27,    34,    37,
      19,    21,    33,    33,    23,    39,    38,    21,    38,    23,
      39,    39,    38,    27,    37,    23,   248,   278,   278,   248,
     262,    38,    22,   286,    38,    39,    38,    39,   275,   276,
      38,    39,    39,    38,    32,   265,    38,    39,    33,    32,
     255,    24,    32,   257,   275,   275,    33,    33,   255,   263,
     264,   274,    34,    38,    27,    21,    27,    39,    21,    27,
      32,    39,    38,    32,    33,    27,    39,    31,    36,    39,
      34,    89,    31,    38,    36,    21,    32,    36,    19,   268,
      36,    31,    34,    38,    34,    31,    38,    36,    38,    34,
      38,    39,    34,    19,    23,   286,    39,    32,   286,    38,
      34,    30,    33,    32,    31,    33,    32,    24,    38,    36,
      23,    39,    21,    32,    23,    39,    36,    39,    19,    23,
      31,    23,    89,    39,    23,    38,    39,    30,   286,    39,
      23,    39,    89,    39,    23,    89,    39,    39,    89,    38,
      39,    39,   258,    38,    38,   255,    27,    39,    30,    39,
      24,    23,    39,    24,    33,    89,    39,    33,    32,    23,
      38,    32,    31,    37,    38,    39,    32,    27,    32,    22,
      34,    31,    89,    19,    31,   271,    31,    32,    38,    22,
      38,    32,    22,    31,    38,    22,    34,    34,    38,    30,
      34,    36,    33,    38,    32,    33,    32,    32,    33,    22,
      31,    39,    38,    89,    38,    23,    27,    89,    22,    25,
      22,    38,    23,    36,    33,    23,    21,    25,    23,   286,
      23,    38,    89,    23,    89,    38,    23,    23,    89,    23,
      33,    39,    89,    38,    39,    33,    32,    89,    38,    38,
      38,    23,    23,    37,    21,    37,    89,    32,    40,    21,
      22,    27,    27,    27,    89,    40,    27,    36,    32,    33,
      23,    32,   266,    32,    22,    40,    22,    89,    40,    32,
      21,    22,    40,    36,    38,    21,    34,    38,    38,    30,
      22,    89,    40,    32,    33,    22,    38,    23,    26,    23,
      36,    33,    32,    89,    22,    27,    40,    38,    38,    39,
      38,   286,    38,    23,    27,    23,    22,    27,    38,    26,
      23,    27,    38,    89,    26,    33,    43,    89,    30,    23,
      21,    22,    27,    27,    38,    39,    27,    89,    19,    40,
      27,    89,    23,    27,    27,    21,    23,    89,    37,    89,
      32,   264,    40,    21,    40,    27,    21,    89,    19,    40,
      21,    21,    38,    19,    36,    34,    23,    40,    33,    27,
      32,    21,    89,    32,    36,    31,    32,    27,    40,    33,
      37,    32,    36,    23,    36,    34,    31,    38,   286,    27,
      23,    27,    36,    23,    31,    32,    27,    23,    26,    43,
      32,    38,    23,    36,    27,    39,    36,    24,    23,    21,
      27,    31,    38,    23,    19,    32,    21,    23,    39,    34,
      23,    37,    89,    19,    19,    89,    33,    34,   253,   273,
     285,   336,   337,   338,    21,    21,    23,    19,    32,    21,
      89,    19,    34,    32,    21,    32,    23,    33,    89,    33,
      32,    19,    21,    34,    23,    23,    36,    38,    39,    21,
      34,    36,    34,    31,    32,    23,   286,    23,    23,    21,
      34,    23,    23,    34,    32,    23,    23,    23,    38,    21,
      21,    27,    39,    24,    34,    38,    30,    37,    89,    34,
      38,    38,    19,    19,    37,    19,    89,    36,   273,    38,
      30,    89,    19,    32,    30,    89,    38,    33,    32,    32,
      33,    89,    33,    89,    34,    39,    89,    33,    36,    31,
      42,    22,    37,    33,    34,    36,    23,    21,    27,    33,
      39,    24,    38,    21,    27,    36,    34,    19,    38,    22,
      36,    19,    23,    23,    27,    36,    19,    19,    30,    33,
      32,    36,    32,    33,    33,    32,    43,    19,    36,    89,
      36,    27,    31,    38,    31,    37,    36,    31,    39,    24,
      43,    38,    39,    24,    36,    19,    22,    27,    23,    23,
      23,    19,    38,    19,    23,    32,    33,    89,    32,    33,
      19,    31,    36,    40,    37,    38,    36,    32,    23,    31,
      38,    38,    21,    27,    38,    31,    23,    27,    23,    23,
      22,    32,    23,    23,    33,    32,    23,    38,    40,    36,
      36,    89,    38,    38,    36,    39,    24,    38,    23,    23,
      37,    26,    23,    32,    33,    23,    36,    36,    33,    36,
      38,    36,    37,    30,    22
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
    { (yyval.String) = LSCPSERVER->ResetSampler();                        }
    break;

  case 29:
#line 130 "lscp.y"
    { LSCPSERVER->AnswerClient("Bye!\r\n"); return LSCP_QUIT; }
    break;

  case 30:
#line 133 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddChannel();                          }
    break;

  case 31:
#line 134 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddDbInstrumentDirectory((yyvsp[(3) - (3)].String));          }
    break;

  case 32:
#line 135 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddDbInstrumentsFlat((yyvsp[(5) - (7)].String),(yyvsp[(7) - (7)].String));         }
    break;

  case 33:
#line 136 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddDbInstrumentsNonrecursive((yyvsp[(5) - (7)].String),(yyvsp[(7) - (7)].String)); }
    break;

  case 34:
#line 137 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddDbInstruments((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].String));             }
    break;

  case 35:
#line 138 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddDbInstruments((yyvsp[(3) - (7)].String),(yyvsp[(5) - (7)].String),(yyvsp[(7) - (7)].Number));          }
    break;

  case 36:
#line 139 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddMidiInstrumentMap();                }
    break;

  case 37:
#line 140 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddMidiInstrumentMap((yyvsp[(3) - (3)].String));              }
    break;

  case 38:
#line 143 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_audio_device_count);   }
    break;

  case 39:
#line 144 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_audio_device_info);    }
    break;

  case 40:
#line 145 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_device_count);    }
    break;

  case 41:
#line 146 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_device_info);     }
    break;

  case 42:
#line 147 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_channel_count);        }
    break;

  case 43:
#line 148 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_voice_count);          }
    break;

  case 44:
#line 149 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_stream_count);         }
    break;

  case 45:
#line 150 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_buffer_fill);          }
    break;

  case 46:
#line 151 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_channel_info);         }
    break;

  case 47:
#line 152 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_fx_send_count);        }
    break;

  case 48:
#line 153 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_fx_send_info);         }
    break;

  case 49:
#line 154 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_instr_map_count); }
    break;

  case 50:
#line 155 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_instr_map_info);  }
    break;

  case 51:
#line 156 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_instr_count);     }
    break;

  case 52:
#line 157 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_instr_info);      }
    break;

  case 53:
#line 158 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_db_instr_dir_count);   }
    break;

  case 54:
#line 159 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_db_instr_dir_info);    }
    break;

  case 55:
#line 160 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_db_instr_count);       }
    break;

  case 56:
#line 161 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_db_instr_info);        }
    break;

  case 57:
#line 162 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_misc);                 }
    break;

  case 58:
#line 163 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_total_voice_count);    }
    break;

  case 59:
#line 164 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_global_info);          }
    break;

  case 60:
#line 167 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_audio_device_count);   }
    break;

  case 61:
#line 168 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_audio_device_info);    }
    break;

  case 62:
#line 169 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_device_count);    }
    break;

  case 63:
#line 170 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_device_info);     }
    break;

  case 64:
#line 171 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_channel_count);        }
    break;

  case 65:
#line 172 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_voice_count);          }
    break;

  case 66:
#line 173 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_stream_count);         }
    break;

  case 67:
#line 174 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_buffer_fill);          }
    break;

  case 68:
#line 175 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_channel_info);         }
    break;

  case 69:
#line 176 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_fx_send_count);        }
    break;

  case 70:
#line 177 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_fx_send_info);         }
    break;

  case 71:
#line 178 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_instr_map_count); }
    break;

  case 72:
#line 179 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_instr_map_info);  }
    break;

  case 73:
#line 180 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_instr_count);     }
    break;

  case 74:
#line 181 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_instr_info);      }
    break;

  case 75:
#line 182 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_db_instr_dir_count);   }
    break;

  case 76:
#line 183 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_db_instr_dir_info);    }
    break;

  case 77:
#line 184 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_db_instr_count);       }
    break;

  case 78:
#line 185 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_db_instr_info);        }
    break;

  case 79:
#line 186 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_misc);                 }
    break;

  case 80:
#line 187 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_total_voice_count);    }
    break;

  case 81:
#line 188 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_global_info);          }
    break;

  case 82:
#line 191 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping((yyvsp[(4) - (16)].Number),(yyvsp[(6) - (16)].Number),(yyvsp[(8) - (16)].Number),(yyvsp[(10) - (16)].String),(yyvsp[(12) - (16)].String),(yyvsp[(14) - (16)].Number),(yyvsp[(16) - (16)].Dotnum),MidiInstrumentMapper::VOID,"",(yyvsp[(3) - (16)].Bool)); }
    break;

  case 83:
#line 192 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping((yyvsp[(4) - (18)].Number),(yyvsp[(6) - (18)].Number),(yyvsp[(8) - (18)].Number),(yyvsp[(10) - (18)].String),(yyvsp[(12) - (18)].String),(yyvsp[(14) - (18)].Number),(yyvsp[(16) - (18)].Dotnum),(yyvsp[(18) - (18)].LoadMode),"",(yyvsp[(3) - (18)].Bool)); }
    break;

  case 84:
#line 193 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping((yyvsp[(4) - (18)].Number),(yyvsp[(6) - (18)].Number),(yyvsp[(8) - (18)].Number),(yyvsp[(10) - (18)].String),(yyvsp[(12) - (18)].String),(yyvsp[(14) - (18)].Number),(yyvsp[(16) - (18)].Dotnum),MidiInstrumentMapper::VOID,(yyvsp[(18) - (18)].String),(yyvsp[(3) - (18)].Bool)); }
    break;

  case 85:
#line 194 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping((yyvsp[(4) - (20)].Number),(yyvsp[(6) - (20)].Number),(yyvsp[(8) - (20)].Number),(yyvsp[(10) - (20)].String),(yyvsp[(12) - (20)].String),(yyvsp[(14) - (20)].Number),(yyvsp[(16) - (20)].Dotnum),(yyvsp[(18) - (20)].LoadMode),(yyvsp[(20) - (20)].String),(yyvsp[(3) - (20)].Bool)); }
    break;

  case 86:
#line 197 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveMIDIInstrumentMapping((yyvsp[(3) - (7)].Number),(yyvsp[(5) - (7)].Number),(yyvsp[(7) - (7)].Number)); }
    break;

  case 87:
#line 200 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveChannel((yyvsp[(3) - (3)].Number));                     }
    break;

  case 88:
#line 201 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveMidiInstrumentMap((yyvsp[(3) - (3)].Number));           }
    break;

  case 89:
#line 202 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveAllMidiInstrumentMaps();         }
    break;

  case 90:
#line 203 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveDbInstrumentDirectory((yyvsp[(5) - (5)].String), true); }
    break;

  case 91:
#line 204 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveDbInstrumentDirectory((yyvsp[(3) - (3)].String));       }
    break;

  case 92:
#line 205 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveDbInstrument((yyvsp[(3) - (3)].String));                }
    break;

  case 93:
#line 208 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAvailableEngines();                          }
    break;

  case 94:
#line 209 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAvailableMidiInputDrivers();                 }
    break;

  case 95:
#line 210 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDriverInfo((yyvsp[(5) - (5)].String));                     }
    break;

  case 96:
#line 211 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDriverParameterInfo((yyvsp[(5) - (7)].String), (yyvsp[(7) - (7)].String));        }
    break;

  case 97:
#line 212 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDriverParameterInfo((yyvsp[(5) - (9)].String), (yyvsp[(7) - (9)].String), (yyvsp[(9) - (9)].KeyValList));    }
    break;

  case 98:
#line 213 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAvailableAudioOutputDrivers();               }
    break;

  case 99:
#line 214 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDriverInfo((yyvsp[(5) - (5)].String));                   }
    break;

  case 100:
#line 215 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDriverParameterInfo((yyvsp[(5) - (7)].String), (yyvsp[(7) - (7)].String));      }
    break;

  case 101:
#line 216 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDriverParameterInfo((yyvsp[(5) - (9)].String), (yyvsp[(7) - (9)].String), (yyvsp[(9) - (9)].KeyValList));  }
    break;

  case 102:
#line 217 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDeviceCount();                    }
    break;

  case 103:
#line 218 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDeviceCount();                      }
    break;

  case 104:
#line 219 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDeviceInfo((yyvsp[(5) - (5)].Number));                   }
    break;

  case 105:
#line 220 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDeviceInfo((yyvsp[(5) - (5)].Number));                     }
    break;

  case 106:
#line 221 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputPortInfo((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number));                   }
    break;

  case 107:
#line 222 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputPortParameterInfo((yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].Number), (yyvsp[(9) - (9)].String));      }
    break;

  case 108:
#line 223 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputChannelInfo((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number));              }
    break;

  case 109:
#line 224 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputChannelParameterInfo((yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].Number), (yyvsp[(9) - (9)].String)); }
    break;

  case 110:
#line 225 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetChannels();                                  }
    break;

  case 111:
#line 226 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetChannelInfo((yyvsp[(5) - (5)].Number));                             }
    break;

  case 112:
#line 227 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetBufferFill((yyvsp[(5) - (7)].FillResponse), (yyvsp[(7) - (7)].Number));                          }
    break;

  case 113:
#line 228 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetStreamCount((yyvsp[(5) - (5)].Number));                             }
    break;

  case 114:
#line 229 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetVoiceCount((yyvsp[(5) - (5)].Number));                              }
    break;

  case 115:
#line 230 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetEngineInfo((yyvsp[(5) - (5)].String));                              }
    break;

  case 116:
#line 231 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetServerInfo();                                }
    break;

  case 117:
#line 232 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetTotalVoiceCount();                           }
    break;

  case 118:
#line 233 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetTotalVoiceCountMax();                        }
    break;

  case 119:
#line 234 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInstrumentMappings((yyvsp[(3) - (3)].Number));                  }
    break;

  case 120:
#line 235 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAllMidiInstrumentMappings();                 }
    break;

  case 121:
#line 236 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInstrumentMapping((yyvsp[(5) - (9)].Number),(yyvsp[(7) - (9)].Number),(yyvsp[(9) - (9)].Number));             }
    break;

  case 122:
#line 237 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInstrumentMaps();                        }
    break;

  case 123:
#line 238 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInstrumentMap((yyvsp[(5) - (5)].Number));                       }
    break;

  case 124:
#line 239 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetFxSends((yyvsp[(3) - (3)].Number));                                 }
    break;

  case 125:
#line 240 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetFxSendInfo((yyvsp[(5) - (7)].Number),(yyvsp[(7) - (7)].Number));                           }
    break;

  case 126:
#line 241 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetDbInstrumentDirectoryCount((yyvsp[(3) - (3)].String));              }
    break;

  case 127:
#line 242 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetDbInstrumentDirectoryInfo((yyvsp[(5) - (5)].String));               }
    break;

  case 128:
#line 243 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetDbInstrumentCount((yyvsp[(3) - (3)].String));                       }
    break;

  case 129:
#line 244 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetDbInstrumentInfo((yyvsp[(5) - (5)].String));                        }
    break;

  case 130:
#line 245 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetGlobalVolume();                              }
    break;

  case 131:
#line 248 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputDeviceParameter((yyvsp[(3) - (7)].Number), (yyvsp[(5) - (7)].String), (yyvsp[(7) - (7)].String));      }
    break;

  case 132:
#line 249 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputChannelParameter((yyvsp[(3) - (9)].Number), (yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].String), (yyvsp[(9) - (9)].String)); }
    break;

  case 133:
#line 250 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMidiInputDeviceParameter((yyvsp[(3) - (7)].Number), (yyvsp[(5) - (7)].String), (yyvsp[(7) - (7)].String));        }
    break;

  case 134:
#line 251 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMidiInputPortParameter((yyvsp[(3) - (9)].Number), (yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].String), (yyvsp[(9) - (9)].String));      }
    break;

  case 135:
#line 252 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                         }
    break;

  case 136:
#line 253 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMidiInstrumentMapName((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].String));               }
    break;

  case 137:
#line 254 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetFxSendName((yyvsp[(5) - (9)].Number),(yyvsp[(7) - (9)].Number),(yyvsp[(9) - (9)].String));                        }
    break;

  case 138:
#line 255 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetFxSendAudioOutputChannel((yyvsp[(5) - (11)].Number),(yyvsp[(7) - (11)].Number),(yyvsp[(9) - (11)].Number),(yyvsp[(11) - (11)].Number)); }
    break;

  case 139:
#line 256 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetFxSendMidiController((yyvsp[(5) - (9)].Number),(yyvsp[(7) - (9)].Number),(yyvsp[(9) - (9)].Number));              }
    break;

  case 140:
#line 257 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetFxSendLevel((yyvsp[(5) - (9)].Number),(yyvsp[(7) - (9)].Number),(yyvsp[(9) - (9)].Dotnum));                       }
    break;

  case 141:
#line 258 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetDbInstrumentDirectoryName((yyvsp[(5) - (7)].String),(yyvsp[(7) - (7)].String));            }
    break;

  case 142:
#line 259 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetDbInstrumentDirectoryDescription((yyvsp[(5) - (7)].String),(yyvsp[(7) - (7)].String));     }
    break;

  case 143:
#line 260 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetDbInstrumentName((yyvsp[(5) - (7)].String),(yyvsp[(7) - (7)].String));                     }
    break;

  case 144:
#line 261 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetDbInstrumentDescription((yyvsp[(5) - (7)].String),(yyvsp[(7) - (7)].String));              }
    break;

  case 145:
#line 262 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetEcho((yyparse_param_t*) yyparse_param, (yyvsp[(3) - (3)].Dotnum));  }
    break;

  case 146:
#line 263 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetGlobalVolume((yyvsp[(3) - (3)].Dotnum));                            }
    break;

  case 147:
#line 266 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateAudioOutputDevice((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].KeyValList)); }
    break;

  case 148:
#line 267 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateAudioOutputDevice((yyvsp[(3) - (3)].String));    }
    break;

  case 149:
#line 268 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateMidiInputDevice((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].KeyValList));   }
    break;

  case 150:
#line 269 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateMidiInputDevice((yyvsp[(3) - (3)].String));      }
    break;

  case 151:
#line 270 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateFxSend((yyvsp[(3) - (5)].Number),(yyvsp[(5) - (5)].Number));            }
    break;

  case 152:
#line 271 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateFxSend((yyvsp[(3) - (7)].Number),(yyvsp[(5) - (7)].Number),(yyvsp[(7) - (7)].String)); }
    break;

  case 153:
#line 274 "lscp.y"
    { (yyval.String) = LSCPSERVER->ResetChannel((yyvsp[(3) - (3)].Number)); }
    break;

  case 154:
#line 277 "lscp.y"
    { (yyval.String) = LSCPSERVER->ClearMidiInstrumentMappings((yyvsp[(3) - (3)].Number));  }
    break;

  case 155:
#line 278 "lscp.y"
    { (yyval.String) = LSCPSERVER->ClearAllMidiInstrumentMappings(); }
    break;

  case 156:
#line 281 "lscp.y"
    { (yyval.String) = LSCPSERVER->MoveDbInstrumentDirectory((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].String)); }
    break;

  case 157:
#line 282 "lscp.y"
    { (yyval.String) = LSCPSERVER->MoveDbInstrument((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].String));          }
    break;

  case 158:
#line 285 "lscp.y"
    { (yyval.String) = LSCPSERVER->DestroyAudioOutputDevice((yyvsp[(3) - (3)].Number)); }
    break;

  case 159:
#line 286 "lscp.y"
    { (yyval.String) = LSCPSERVER->DestroyMidiInputDevice((yyvsp[(3) - (3)].Number));   }
    break;

  case 160:
#line 287 "lscp.y"
    { (yyval.String) = LSCPSERVER->DestroyFxSend((yyvsp[(3) - (5)].Number),(yyvsp[(5) - (5)].Number)); }
    break;

  case 161:
#line 290 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String); }
    break;

  case 162:
#line 291 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String); }
    break;

  case 163:
#line 294 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputDevice((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));      }
    break;

  case 164:
#line 295 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputChannel((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number), (yyvsp[(3) - (7)].Number)); }
    break;

  case 165:
#line 296 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputType((yyvsp[(5) - (5)].String), (yyvsp[(3) - (5)].Number));        }
    break;

  case 166:
#line 297 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInput((yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].Number), (yyvsp[(9) - (9)].Number), (yyvsp[(3) - (9)].Number));      }
    break;

  case 167:
#line 298 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputDevice((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));        }
    break;

  case 168:
#line 299 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputPort((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));          }
    break;

  case 169:
#line 300 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputChannel((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));       }
    break;

  case 170:
#line 301 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputType((yyvsp[(5) - (5)].String), (yyvsp[(3) - (5)].Number));          }
    break;

  case 171:
#line 302 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetVolume((yyvsp[(5) - (5)].Dotnum), (yyvsp[(3) - (5)].Number));                 }
    break;

  case 172:
#line 303 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMute((yyvsp[(5) - (5)].Dotnum), (yyvsp[(3) - (5)].Number));            }
    break;

  case 173:
#line 304 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelSolo((yyvsp[(5) - (5)].Dotnum), (yyvsp[(3) - (5)].Number));            }
    break;

  case 174:
#line 305 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMap((yyvsp[(3) - (5)].Number), (yyvsp[(5) - (5)].Number));             }
    break;

  case 175:
#line 306 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMap((yyvsp[(3) - (5)].Number), -1);             }
    break;

  case 176:
#line 307 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMap((yyvsp[(3) - (5)].Number), -2);             }
    break;

  case 177:
#line 310 "lscp.y"
    { (yyval.Bool) = true;  }
    break;

  case 178:
#line 311 "lscp.y"
    { (yyval.Bool) = false; }
    break;

  case 179:
#line 314 "lscp.y"
    { (yyval.KeyValList)[(yyvsp[(1) - (3)].String)] = (yyvsp[(3) - (3)].String);          }
    break;

  case 180:
#line 315 "lscp.y"
    { (yyval.KeyValList) = (yyvsp[(1) - (5)].KeyValList); (yyval.KeyValList)[(yyvsp[(3) - (5)].String)] = (yyvsp[(5) - (5)].String); }
    break;

  case 181:
#line 318 "lscp.y"
    { (yyval.FillResponse) = fill_response_bytes;      }
    break;

  case 182:
#line 319 "lscp.y"
    { (yyval.FillResponse) = fill_response_percentage; }
    break;

  case 183:
#line 322 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDevices();           }
    break;

  case 184:
#line 323 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDevices();             }
    break;

  case 185:
#line 324 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListChannels();                    }
    break;

  case 186:
#line 325 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableEngines();            }
    break;

  case 187:
#line 326 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableMidiInputDrivers();   }
    break;

  case 188:
#line 327 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableAudioOutputDrivers(); }
    break;

  case 189:
#line 328 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListMidiInstrumentMappings((yyvsp[(3) - (3)].Number));    }
    break;

  case 190:
#line 329 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAllMidiInstrumentMappings();   }
    break;

  case 191:
#line 330 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListMidiInstrumentMaps();          }
    break;

  case 192:
#line 331 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListFxSends((yyvsp[(3) - (3)].Number));                   }
    break;

  case 193:
#line 332 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetDbInstrumentDirectories((yyvsp[(3) - (3)].String));    }
    break;

  case 194:
#line 333 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetDbInstruments((yyvsp[(3) - (3)].String));              }
    break;

  case 195:
#line 336 "lscp.y"
    { (yyval.String) = LSCPSERVER->LoadInstrument((yyvsp[(1) - (5)].String), (yyvsp[(3) - (5)].Number), (yyvsp[(5) - (5)].Number));       }
    break;

  case 196:
#line 337 "lscp.y"
    { (yyval.String) = LSCPSERVER->LoadInstrument((yyvsp[(3) - (7)].String), (yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number), true); }
    break;

  case 197:
#line 340 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetEngineType((yyvsp[(1) - (3)].String), (yyvsp[(3) - (3)].Number)); }
    break;

  case 198:
#line 343 "lscp.y"
    { (yyval.LoadMode) = MidiInstrumentMapper::ON_DEMAND;      }
    break;

  case 199:
#line 344 "lscp.y"
    { (yyval.LoadMode) = MidiInstrumentMapper::ON_DEMAND_HOLD; }
    break;

  case 200:
#line 345 "lscp.y"
    { (yyval.LoadMode) = MidiInstrumentMapper::PERSISTENT;     }
    break;

  case 206:
#line 361 "lscp.y"
    { (yyval.Number) = 16; }
    break;

  case 213:
#line 380 "lscp.y"
    { (yyval.Dotnum) = (yyvsp[(1) - (1)].Number); }
    break;

  case 225:
#line 414 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (3)].String) + "," + (yyvsp[(3) - (3)].String); }
    break;

  case 228:
#line 419 "lscp.y"
    { std::stringstream ss; ss << "\'" << (yyvsp[(1) - (1)].Number) << "\'"; (yyval.String) = ss.str(); }
    break;

  case 229:
#line 420 "lscp.y"
    { std::stringstream ss; ss << "\'" << (yyvsp[(1) - (1)].Dotnum) << "\'"; (yyval.String) = ss.str(); }
    break;

  case 230:
#line 428 "lscp.y"
    { (yyval.Dotnum) = (yyvsp[(1) - (1)].Number); }
    break;

  case 231:
#line 429 "lscp.y"
    { (yyval.Dotnum) = -1; }
    break;

  case 232:
#line 432 "lscp.y"
    { std::string s; s = (yyvsp[(1) - (1)].Char); (yyval.String) = s; }
    break;

  case 233:
#line 433 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + (yyvsp[(2) - (2)].Char);                  }
    break;

  case 234:
#line 436 "lscp.y"
    { (yyval.Dotnum) = atof(String((yyvsp[(1) - (3)].String) + "." + (yyvsp[(3) - (3)].String)).c_str());                         }
    break;

  case 235:
#line 437 "lscp.y"
    { String s = "+"; s += (yyvsp[(2) - (4)].String); s += "."; s += (yyvsp[(4) - (4)].String); (yyval.Dotnum) = atof(s.c_str()); }
    break;

  case 236:
#line 438 "lscp.y"
    { (yyval.Dotnum) = atof(String("-" + (yyvsp[(2) - (4)].String) + "." + (yyvsp[(4) - (4)].String)).c_str());                   }
    break;

  case 237:
#line 442 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (1)].Char);      }
    break;

  case 238:
#line 443 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + (yyvsp[(2) - (2)].Char); }
    break;

  case 239:
#line 446 "lscp.y"
    { (yyval.Char) = '0'; }
    break;

  case 240:
#line 447 "lscp.y"
    { (yyval.Char) = '1'; }
    break;

  case 241:
#line 448 "lscp.y"
    { (yyval.Char) = '2'; }
    break;

  case 242:
#line 449 "lscp.y"
    { (yyval.Char) = '3'; }
    break;

  case 243:
#line 450 "lscp.y"
    { (yyval.Char) = '4'; }
    break;

  case 244:
#line 451 "lscp.y"
    { (yyval.Char) = '5'; }
    break;

  case 245:
#line 452 "lscp.y"
    { (yyval.Char) = '6'; }
    break;

  case 246:
#line 453 "lscp.y"
    { (yyval.Char) = '7'; }
    break;

  case 247:
#line 454 "lscp.y"
    { (yyval.Char) = '8'; }
    break;

  case 248:
#line 455 "lscp.y"
    { (yyval.Char) = '9'; }
    break;

  case 249:
#line 458 "lscp.y"
    { (yyval.Number) = atoi(String(1, (yyvsp[(1) - (1)].Char)).c_str());      }
    break;

  case 250:
#line 459 "lscp.y"
    { (yyval.Number) = atoi(String(String("1") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 251:
#line 460 "lscp.y"
    { (yyval.Number) = atoi(String(String("2") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 252:
#line 461 "lscp.y"
    { (yyval.Number) = atoi(String(String("3") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 253:
#line 462 "lscp.y"
    { (yyval.Number) = atoi(String(String("4") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 254:
#line 463 "lscp.y"
    { (yyval.Number) = atoi(String(String("5") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 255:
#line 464 "lscp.y"
    { (yyval.Number) = atoi(String(String("6") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 256:
#line 465 "lscp.y"
    { (yyval.Number) = atoi(String(String("7") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 257:
#line 466 "lscp.y"
    { (yyval.Number) = atoi(String(String("8") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 258:
#line 467 "lscp.y"
    { (yyval.Number) = atoi(String(String("9") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 259:
#line 469 "lscp.y"
    { (yyval.Char) = 'A'; }
    break;

  case 260:
#line 469 "lscp.y"
    { (yyval.Char) = 'B'; }
    break;

  case 261:
#line 469 "lscp.y"
    { (yyval.Char) = 'C'; }
    break;

  case 262:
#line 469 "lscp.y"
    { (yyval.Char) = 'D'; }
    break;

  case 263:
#line 469 "lscp.y"
    { (yyval.Char) = 'E'; }
    break;

  case 264:
#line 469 "lscp.y"
    { (yyval.Char) = 'F'; }
    break;

  case 265:
#line 469 "lscp.y"
    { (yyval.Char) = 'G'; }
    break;

  case 266:
#line 469 "lscp.y"
    { (yyval.Char) = 'H'; }
    break;

  case 267:
#line 469 "lscp.y"
    { (yyval.Char) = 'I'; }
    break;

  case 268:
#line 469 "lscp.y"
    { (yyval.Char) = 'J'; }
    break;

  case 269:
#line 469 "lscp.y"
    { (yyval.Char) = 'K'; }
    break;

  case 270:
#line 469 "lscp.y"
    { (yyval.Char) = 'L'; }
    break;

  case 271:
#line 469 "lscp.y"
    { (yyval.Char) = 'M'; }
    break;

  case 272:
#line 469 "lscp.y"
    { (yyval.Char) = 'N'; }
    break;

  case 273:
#line 469 "lscp.y"
    { (yyval.Char) = 'O'; }
    break;

  case 274:
#line 469 "lscp.y"
    { (yyval.Char) = 'P'; }
    break;

  case 275:
#line 469 "lscp.y"
    { (yyval.Char) = 'Q'; }
    break;

  case 276:
#line 469 "lscp.y"
    { (yyval.Char) = 'R'; }
    break;

  case 277:
#line 469 "lscp.y"
    { (yyval.Char) = 'S'; }
    break;

  case 278:
#line 469 "lscp.y"
    { (yyval.Char) = 'T'; }
    break;

  case 279:
#line 469 "lscp.y"
    { (yyval.Char) = 'U'; }
    break;

  case 280:
#line 469 "lscp.y"
    { (yyval.Char) = 'V'; }
    break;

  case 281:
#line 469 "lscp.y"
    { (yyval.Char) = 'W'; }
    break;

  case 282:
#line 469 "lscp.y"
    { (yyval.Char) = 'X'; }
    break;

  case 283:
#line 469 "lscp.y"
    { (yyval.Char) = 'Y'; }
    break;

  case 284:
#line 469 "lscp.y"
    { (yyval.Char) = 'Z'; }
    break;

  case 285:
#line 470 "lscp.y"
    { (yyval.Char) = 'a'; }
    break;

  case 286:
#line 470 "lscp.y"
    { (yyval.Char) = 'b'; }
    break;

  case 287:
#line 470 "lscp.y"
    { (yyval.Char) = 'c'; }
    break;

  case 288:
#line 470 "lscp.y"
    { (yyval.Char) = 'd'; }
    break;

  case 289:
#line 470 "lscp.y"
    { (yyval.Char) = 'e'; }
    break;

  case 290:
#line 470 "lscp.y"
    { (yyval.Char) = 'f'; }
    break;

  case 291:
#line 470 "lscp.y"
    { (yyval.Char) = 'g'; }
    break;

  case 292:
#line 470 "lscp.y"
    { (yyval.Char) = 'h'; }
    break;

  case 293:
#line 470 "lscp.y"
    { (yyval.Char) = 'i'; }
    break;

  case 294:
#line 470 "lscp.y"
    { (yyval.Char) = 'j'; }
    break;

  case 295:
#line 470 "lscp.y"
    { (yyval.Char) = 'k'; }
    break;

  case 296:
#line 470 "lscp.y"
    { (yyval.Char) = 'l'; }
    break;

  case 297:
#line 470 "lscp.y"
    { (yyval.Char) = 'm'; }
    break;

  case 298:
#line 470 "lscp.y"
    { (yyval.Char) = 'n'; }
    break;

  case 299:
#line 470 "lscp.y"
    { (yyval.Char) = 'o'; }
    break;

  case 300:
#line 470 "lscp.y"
    { (yyval.Char) = 'p'; }
    break;

  case 301:
#line 470 "lscp.y"
    { (yyval.Char) = 'q'; }
    break;

  case 302:
#line 470 "lscp.y"
    { (yyval.Char) = 'r'; }
    break;

  case 303:
#line 470 "lscp.y"
    { (yyval.Char) = 's'; }
    break;

  case 304:
#line 470 "lscp.y"
    { (yyval.Char) = 't'; }
    break;

  case 305:
#line 470 "lscp.y"
    { (yyval.Char) = 'u'; }
    break;

  case 306:
#line 470 "lscp.y"
    { (yyval.Char) = 'v'; }
    break;

  case 307:
#line 470 "lscp.y"
    { (yyval.Char) = 'w'; }
    break;

  case 308:
#line 470 "lscp.y"
    { (yyval.Char) = 'x'; }
    break;

  case 309:
#line 470 "lscp.y"
    { (yyval.Char) = 'y'; }
    break;

  case 310:
#line 470 "lscp.y"
    { (yyval.Char) = 'z'; }
    break;

  case 311:
#line 471 "lscp.y"
    { (yyval.Char) = '0'; }
    break;

  case 312:
#line 471 "lscp.y"
    { (yyval.Char) = '1'; }
    break;

  case 313:
#line 471 "lscp.y"
    { (yyval.Char) = '2'; }
    break;

  case 314:
#line 471 "lscp.y"
    { (yyval.Char) = '3'; }
    break;

  case 315:
#line 471 "lscp.y"
    { (yyval.Char) = '4'; }
    break;

  case 316:
#line 471 "lscp.y"
    { (yyval.Char) = '5'; }
    break;

  case 317:
#line 471 "lscp.y"
    { (yyval.Char) = '6'; }
    break;

  case 318:
#line 471 "lscp.y"
    { (yyval.Char) = '7'; }
    break;

  case 319:
#line 471 "lscp.y"
    { (yyval.Char) = '8'; }
    break;

  case 320:
#line 471 "lscp.y"
    { (yyval.Char) = '9'; }
    break;

  case 321:
#line 472 "lscp.y"
    { (yyval.Char) = '!'; }
    break;

  case 322:
#line 472 "lscp.y"
    { (yyval.Char) = '#'; }
    break;

  case 323:
#line 472 "lscp.y"
    { (yyval.Char) = '$'; }
    break;

  case 324:
#line 472 "lscp.y"
    { (yyval.Char) = '%'; }
    break;

  case 325:
#line 472 "lscp.y"
    { (yyval.Char) = '&'; }
    break;

  case 326:
#line 472 "lscp.y"
    { (yyval.Char) = '('; }
    break;

  case 327:
#line 472 "lscp.y"
    { (yyval.Char) = ')'; }
    break;

  case 328:
#line 472 "lscp.y"
    { (yyval.Char) = '*'; }
    break;

  case 329:
#line 472 "lscp.y"
    { (yyval.Char) = '+'; }
    break;

  case 330:
#line 472 "lscp.y"
    { (yyval.Char) = '-'; }
    break;

  case 331:
#line 472 "lscp.y"
    { (yyval.Char) = '.'; }
    break;

  case 332:
#line 472 "lscp.y"
    { (yyval.Char) = ','; }
    break;

  case 333:
#line 472 "lscp.y"
    { (yyval.Char) = '/'; }
    break;

  case 334:
#line 473 "lscp.y"
    { (yyval.Char) = ':'; }
    break;

  case 335:
#line 473 "lscp.y"
    { (yyval.Char) = ';'; }
    break;

  case 336:
#line 473 "lscp.y"
    { (yyval.Char) = '<'; }
    break;

  case 337:
#line 473 "lscp.y"
    { (yyval.Char) = '='; }
    break;

  case 338:
#line 473 "lscp.y"
    { (yyval.Char) = '>'; }
    break;

  case 339:
#line 473 "lscp.y"
    { (yyval.Char) = '?'; }
    break;

  case 340:
#line 473 "lscp.y"
    { (yyval.Char) = '@'; }
    break;

  case 341:
#line 474 "lscp.y"
    { (yyval.Char) = '['; }
    break;

  case 342:
#line 474 "lscp.y"
    { (yyval.Char) = '\\'; }
    break;

  case 343:
#line 474 "lscp.y"
    { (yyval.Char) = ']'; }
    break;

  case 344:
#line 474 "lscp.y"
    { (yyval.Char) = '^'; }
    break;

  case 345:
#line 474 "lscp.y"
    { (yyval.Char) = '_'; }
    break;

  case 346:
#line 475 "lscp.y"
    { (yyval.Char) = '{'; }
    break;

  case 347:
#line 475 "lscp.y"
    { (yyval.Char) = '|'; }
    break;

  case 348:
#line 475 "lscp.y"
    { (yyval.Char) = '}'; }
    break;

  case 349:
#line 475 "lscp.y"
    { (yyval.Char) = '~'; }
    break;

  case 350:
#line 476 "lscp.y"
    { (yyval.Char) = '\200'; }
    break;

  case 351:
#line 476 "lscp.y"
    { (yyval.Char) = '\201'; }
    break;

  case 352:
#line 476 "lscp.y"
    { (yyval.Char) = '\202'; }
    break;

  case 353:
#line 477 "lscp.y"
    { (yyval.Char) = '\203'; }
    break;

  case 354:
#line 477 "lscp.y"
    { (yyval.Char) = '\204'; }
    break;

  case 355:
#line 477 "lscp.y"
    { (yyval.Char) = '\205'; }
    break;

  case 356:
#line 478 "lscp.y"
    { (yyval.Char) = '\206'; }
    break;

  case 357:
#line 478 "lscp.y"
    { (yyval.Char) = '\207'; }
    break;

  case 358:
#line 478 "lscp.y"
    { (yyval.Char) = '\210'; }
    break;

  case 359:
#line 479 "lscp.y"
    { (yyval.Char) = '\211'; }
    break;

  case 360:
#line 479 "lscp.y"
    { (yyval.Char) = '\212'; }
    break;

  case 361:
#line 479 "lscp.y"
    { (yyval.Char) = '\213'; }
    break;

  case 362:
#line 480 "lscp.y"
    { (yyval.Char) = '\214'; }
    break;

  case 363:
#line 480 "lscp.y"
    { (yyval.Char) = '\215'; }
    break;

  case 364:
#line 480 "lscp.y"
    { (yyval.Char) = '\216'; }
    break;

  case 365:
#line 481 "lscp.y"
    { (yyval.Char) = '\217'; }
    break;

  case 366:
#line 481 "lscp.y"
    { (yyval.Char) = '\220'; }
    break;

  case 367:
#line 481 "lscp.y"
    { (yyval.Char) = '\221'; }
    break;

  case 368:
#line 482 "lscp.y"
    { (yyval.Char) = '\222'; }
    break;

  case 369:
#line 482 "lscp.y"
    { (yyval.Char) = '\223'; }
    break;

  case 370:
#line 482 "lscp.y"
    { (yyval.Char) = '\224'; }
    break;

  case 371:
#line 483 "lscp.y"
    { (yyval.Char) = '\225'; }
    break;

  case 372:
#line 483 "lscp.y"
    { (yyval.Char) = '\226'; }
    break;

  case 373:
#line 483 "lscp.y"
    { (yyval.Char) = '\227'; }
    break;

  case 374:
#line 484 "lscp.y"
    { (yyval.Char) = '\230'; }
    break;

  case 375:
#line 484 "lscp.y"
    { (yyval.Char) = '\231'; }
    break;

  case 376:
#line 484 "lscp.y"
    { (yyval.Char) = '\232'; }
    break;

  case 377:
#line 485 "lscp.y"
    { (yyval.Char) = '\233'; }
    break;

  case 378:
#line 485 "lscp.y"
    { (yyval.Char) = '\234'; }
    break;

  case 379:
#line 485 "lscp.y"
    { (yyval.Char) = '\235'; }
    break;

  case 380:
#line 486 "lscp.y"
    { (yyval.Char) = '\236'; }
    break;

  case 381:
#line 486 "lscp.y"
    { (yyval.Char) = '\237'; }
    break;

  case 382:
#line 486 "lscp.y"
    { (yyval.Char) = '\240'; }
    break;

  case 383:
#line 487 "lscp.y"
    { (yyval.Char) = '\241'; }
    break;

  case 384:
#line 487 "lscp.y"
    { (yyval.Char) = '\242'; }
    break;

  case 385:
#line 487 "lscp.y"
    { (yyval.Char) = '\243'; }
    break;

  case 386:
#line 488 "lscp.y"
    { (yyval.Char) = '\244'; }
    break;

  case 387:
#line 488 "lscp.y"
    { (yyval.Char) = '\245'; }
    break;

  case 388:
#line 488 "lscp.y"
    { (yyval.Char) = '\246'; }
    break;

  case 389:
#line 489 "lscp.y"
    { (yyval.Char) = '\247'; }
    break;

  case 390:
#line 489 "lscp.y"
    { (yyval.Char) = '\250'; }
    break;

  case 391:
#line 489 "lscp.y"
    { (yyval.Char) = '\251'; }
    break;

  case 392:
#line 490 "lscp.y"
    { (yyval.Char) = '\252'; }
    break;

  case 393:
#line 490 "lscp.y"
    { (yyval.Char) = '\253'; }
    break;

  case 394:
#line 490 "lscp.y"
    { (yyval.Char) = '\254'; }
    break;

  case 395:
#line 491 "lscp.y"
    { (yyval.Char) = '\255'; }
    break;

  case 396:
#line 491 "lscp.y"
    { (yyval.Char) = '\256'; }
    break;

  case 397:
#line 491 "lscp.y"
    { (yyval.Char) = '\257'; }
    break;

  case 398:
#line 492 "lscp.y"
    { (yyval.Char) = '\260'; }
    break;

  case 399:
#line 492 "lscp.y"
    { (yyval.Char) = '\261'; }
    break;

  case 400:
#line 492 "lscp.y"
    { (yyval.Char) = '\262'; }
    break;

  case 401:
#line 493 "lscp.y"
    { (yyval.Char) = '\263'; }
    break;

  case 402:
#line 493 "lscp.y"
    { (yyval.Char) = '\264'; }
    break;

  case 403:
#line 493 "lscp.y"
    { (yyval.Char) = '\265'; }
    break;

  case 404:
#line 494 "lscp.y"
    { (yyval.Char) = '\266'; }
    break;

  case 405:
#line 494 "lscp.y"
    { (yyval.Char) = '\267'; }
    break;

  case 406:
#line 494 "lscp.y"
    { (yyval.Char) = '\270'; }
    break;

  case 407:
#line 495 "lscp.y"
    { (yyval.Char) = '\271'; }
    break;

  case 408:
#line 495 "lscp.y"
    { (yyval.Char) = '\272'; }
    break;

  case 409:
#line 495 "lscp.y"
    { (yyval.Char) = '\273'; }
    break;

  case 410:
#line 496 "lscp.y"
    { (yyval.Char) = '\274'; }
    break;

  case 411:
#line 496 "lscp.y"
    { (yyval.Char) = '\275'; }
    break;

  case 412:
#line 496 "lscp.y"
    { (yyval.Char) = '\276'; }
    break;

  case 413:
#line 497 "lscp.y"
    { (yyval.Char) = '\277'; }
    break;

  case 414:
#line 497 "lscp.y"
    { (yyval.Char) = '\300'; }
    break;

  case 415:
#line 497 "lscp.y"
    { (yyval.Char) = '\301'; }
    break;

  case 416:
#line 498 "lscp.y"
    { (yyval.Char) = '\302'; }
    break;

  case 417:
#line 498 "lscp.y"
    { (yyval.Char) = '\303'; }
    break;

  case 418:
#line 498 "lscp.y"
    { (yyval.Char) = '\304'; }
    break;

  case 419:
#line 499 "lscp.y"
    { (yyval.Char) = '\305'; }
    break;

  case 420:
#line 499 "lscp.y"
    { (yyval.Char) = '\306'; }
    break;

  case 421:
#line 499 "lscp.y"
    { (yyval.Char) = '\307'; }
    break;

  case 422:
#line 500 "lscp.y"
    { (yyval.Char) = '\310'; }
    break;

  case 423:
#line 500 "lscp.y"
    { (yyval.Char) = '\311'; }
    break;

  case 424:
#line 500 "lscp.y"
    { (yyval.Char) = '\312'; }
    break;

  case 425:
#line 501 "lscp.y"
    { (yyval.Char) = '\313'; }
    break;

  case 426:
#line 501 "lscp.y"
    { (yyval.Char) = '\314'; }
    break;

  case 427:
#line 501 "lscp.y"
    { (yyval.Char) = '\315'; }
    break;

  case 428:
#line 502 "lscp.y"
    { (yyval.Char) = '\316'; }
    break;

  case 429:
#line 502 "lscp.y"
    { (yyval.Char) = '\317'; }
    break;

  case 430:
#line 502 "lscp.y"
    { (yyval.Char) = '\320'; }
    break;

  case 431:
#line 503 "lscp.y"
    { (yyval.Char) = '\321'; }
    break;

  case 432:
#line 503 "lscp.y"
    { (yyval.Char) = '\322'; }
    break;

  case 433:
#line 503 "lscp.y"
    { (yyval.Char) = '\323'; }
    break;

  case 434:
#line 504 "lscp.y"
    { (yyval.Char) = '\324'; }
    break;

  case 435:
#line 504 "lscp.y"
    { (yyval.Char) = '\325'; }
    break;

  case 436:
#line 504 "lscp.y"
    { (yyval.Char) = '\326'; }
    break;

  case 437:
#line 505 "lscp.y"
    { (yyval.Char) = '\327'; }
    break;

  case 438:
#line 505 "lscp.y"
    { (yyval.Char) = '\330'; }
    break;

  case 439:
#line 505 "lscp.y"
    { (yyval.Char) = '\331'; }
    break;

  case 440:
#line 506 "lscp.y"
    { (yyval.Char) = '\332'; }
    break;

  case 441:
#line 506 "lscp.y"
    { (yyval.Char) = '\333'; }
    break;

  case 442:
#line 506 "lscp.y"
    { (yyval.Char) = '\334'; }
    break;

  case 443:
#line 507 "lscp.y"
    { (yyval.Char) = '\335'; }
    break;

  case 444:
#line 507 "lscp.y"
    { (yyval.Char) = '\336'; }
    break;

  case 445:
#line 507 "lscp.y"
    { (yyval.Char) = '\337'; }
    break;

  case 446:
#line 508 "lscp.y"
    { (yyval.Char) = '\340'; }
    break;

  case 447:
#line 508 "lscp.y"
    { (yyval.Char) = '\341'; }
    break;

  case 448:
#line 508 "lscp.y"
    { (yyval.Char) = '\342'; }
    break;

  case 449:
#line 509 "lscp.y"
    { (yyval.Char) = '\343'; }
    break;

  case 450:
#line 509 "lscp.y"
    { (yyval.Char) = '\344'; }
    break;

  case 451:
#line 509 "lscp.y"
    { (yyval.Char) = '\345'; }
    break;

  case 452:
#line 510 "lscp.y"
    { (yyval.Char) = '\346'; }
    break;

  case 453:
#line 510 "lscp.y"
    { (yyval.Char) = '\347'; }
    break;

  case 454:
#line 510 "lscp.y"
    { (yyval.Char) = '\350'; }
    break;

  case 455:
#line 511 "lscp.y"
    { (yyval.Char) = '\351'; }
    break;

  case 456:
#line 511 "lscp.y"
    { (yyval.Char) = '\352'; }
    break;

  case 457:
#line 511 "lscp.y"
    { (yyval.Char) = '\353'; }
    break;

  case 458:
#line 512 "lscp.y"
    { (yyval.Char) = '\354'; }
    break;

  case 459:
#line 512 "lscp.y"
    { (yyval.Char) = '\355'; }
    break;

  case 460:
#line 512 "lscp.y"
    { (yyval.Char) = '\356'; }
    break;

  case 461:
#line 513 "lscp.y"
    { (yyval.Char) = '\357'; }
    break;

  case 462:
#line 513 "lscp.y"
    { (yyval.Char) = '\360'; }
    break;

  case 463:
#line 513 "lscp.y"
    { (yyval.Char) = '\361'; }
    break;

  case 464:
#line 514 "lscp.y"
    { (yyval.Char) = '\362'; }
    break;

  case 465:
#line 514 "lscp.y"
    { (yyval.Char) = '\363'; }
    break;

  case 466:
#line 514 "lscp.y"
    { (yyval.Char) = '\364'; }
    break;

  case 467:
#line 515 "lscp.y"
    { (yyval.Char) = '\365'; }
    break;

  case 468:
#line 515 "lscp.y"
    { (yyval.Char) = '\366'; }
    break;

  case 469:
#line 515 "lscp.y"
    { (yyval.Char) = '\367'; }
    break;

  case 470:
#line 516 "lscp.y"
    { (yyval.Char) = '\370'; }
    break;

  case 471:
#line 516 "lscp.y"
    { (yyval.Char) = '\371'; }
    break;

  case 472:
#line 516 "lscp.y"
    { (yyval.Char) = '\372'; }
    break;

  case 473:
#line 517 "lscp.y"
    { (yyval.Char) = '\373'; }
    break;

  case 474:
#line 517 "lscp.y"
    { (yyval.Char) = '\374'; }
    break;

  case 475:
#line 517 "lscp.y"
    { (yyval.Char) = '\375'; }
    break;

  case 476:
#line 518 "lscp.y"
    { (yyval.Char) = '\376'; }
    break;

  case 477:
#line 518 "lscp.y"
    { (yyval.Char) = '\377'; }
    break;

  case 478:
#line 521 "lscp.y"
    { (yyval.String) = " ";      }
    break;

  case 480:
#line 523 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + " "; }
    break;

  case 481:
#line 524 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + (yyvsp[(2) - (2)].String);  }
    break;

  case 482:
#line 527 "lscp.y"
    { (yyval.String) = (yyvsp[(2) - (3)].String); }
    break;

  case 483:
#line 528 "lscp.y"
    { (yyval.String) = (yyvsp[(2) - (3)].String); }
    break;


/* Line 1267 of yacc.c.  */
#line 5762 "y.tab.c"
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


#line 831 "lscp.y"


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

