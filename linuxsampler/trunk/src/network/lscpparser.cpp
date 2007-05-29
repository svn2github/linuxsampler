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
#define YYFINAL  55
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   5603

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  227
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  170
/* YYNRULES -- Number of rules.  */
#define YYNRULES  614
/* YYNRULES -- Number of states.  */
#define YYNSTATES  2084

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
      99,   103,   105,   107,   109,   113,   123,   131,   139,   149,
     155,   163,   165,   169,   171,   173,   175,   177,   179,   181,
     183,   185,   187,   189,   191,   193,   195,   197,   199,   201,
     203,   205,   207,   209,   211,   213,   215,   217,   219,   221,
     223,   225,   227,   229,   231,   233,   235,   237,   239,   241,
     243,   245,   247,   249,   251,   253,   255,   257,   259,   261,
     278,   297,   316,   337,   345,   349,   353,   357,   363,   367,
     371,   373,   375,   381,   389,   399,   401,   407,   415,   425,
     427,   429,   435,   441,   449,   459,   467,   477,   479,   485,
     493,   499,   505,   511,   515,   517,   519,   523,   527,   537,
     539,   545,   549,   557,   563,   567,   573,   579,   583,   589,
     595,   597,   605,   615,   623,   633,   637,   645,   655,   667,
     677,   687,   695,   703,   711,   719,   723,   727,   733,   737,
     743,   747,   753,   761,   765,   769,   773,   781,   787,   795,
     801,   807,   813,   819,   825,   829,   833,   839,   843,   847,
     853,   861,   867,   877,   883,   889,   895,   901,   907,   913,
     919,   925,   931,   937,   941,   942,   945,   949,   955,   957,
     959,   961,   963,   965,   967,   969,   971,   975,   979,   981,
     985,   991,   995,  1001,  1005,  1011,  1019,  1023,  1025,  1027,
    1029,  1031,  1033,  1035,  1037,  1039,  1041,  1043,  1045,  1047,
    1049,  1051,  1053,  1055,  1057,  1059,  1061,  1063,  1065,  1067,
    1069,  1071,  1073,  1075,  1077,  1081,  1083,  1085,  1087,  1089,
    1093,  1099,  1101,  1103,  1105,  1107,  1109,  1111,  1113,  1115,
    1118,  1122,  1127,  1132,  1134,  1137,  1139,  1141,  1143,  1145,
    1147,  1149,  1151,  1153,  1155,  1157,  1159,  1162,  1165,  1168,
    1171,  1174,  1177,  1180,  1183,  1186,  1188,  1190,  1192,  1194,
    1196,  1198,  1200,  1202,  1204,  1206,  1208,  1210,  1212,  1214,
    1216,  1218,  1220,  1222,  1224,  1226,  1228,  1230,  1232,  1234,
    1236,  1238,  1240,  1242,  1244,  1246,  1248,  1250,  1252,  1254,
    1256,  1258,  1260,  1262,  1264,  1266,  1268,  1270,  1272,  1274,
    1276,  1278,  1280,  1282,  1284,  1286,  1288,  1290,  1292,  1294,
    1296,  1298,  1300,  1302,  1304,  1306,  1308,  1310,  1312,  1314,
    1316,  1318,  1320,  1322,  1324,  1326,  1328,  1330,  1332,  1334,
    1336,  1338,  1340,  1342,  1344,  1346,  1348,  1350,  1352,  1354,
    1356,  1358,  1360,  1362,  1364,  1366,  1368,  1370,  1372,  1374,
    1376,  1378,  1380,  1382,  1384,  1386,  1388,  1390,  1392,  1394,
    1396,  1398,  1400,  1402,  1404,  1406,  1408,  1410,  1412,  1414,
    1416,  1418,  1420,  1422,  1424,  1426,  1428,  1430,  1432,  1434,
    1436,  1438,  1440,  1442,  1444,  1446,  1448,  1450,  1452,  1454,
    1456,  1458,  1460,  1462,  1464,  1466,  1468,  1470,  1472,  1474,
    1476,  1478,  1480,  1482,  1484,  1486,  1488,  1490,  1492,  1494,
    1496,  1498,  1500,  1502,  1504,  1506,  1508,  1510,  1512,  1514,
    1516,  1518,  1520,  1522,  1524,  1526,  1528,  1530,  1532,  1534,
    1536,  1538,  1540,  1542,  1544,  1546,  1548,  1550,  1552,  1554,
    1556,  1558,  1560,  1562,  1564,  1566,  1568,  1570,  1572,  1574,
    1576,  1578,  1580,  1582,  1584,  1586,  1588,  1590,  1592,  1594,
    1596,  1598,  1600,  1602,  1604,  1606,  1608,  1610,  1612,  1614,
    1616,  1618,  1620,  1622,  1624,  1626,  1628,  1631,  1634,  1638,
    1642,  1644,  1646,  1648,  1652,  1656,  1660,  1666,  1672,  1677,
    1682,  1687,  1694,  1702,  1707,  1712,  1716,  1721,  1729,  1739,
    1746,  1750,  1760,  1772,  1780,  1798,  1829,  1838,  1843,  1869,
    1894,  1918,  1941,  1967,  1992,  2014,  2035,  2065,  2094,  2114,
    2133,  2157,  2171,  2184,  2198,  2211,  2223,  2236,  2248,  2266,
    2288,  2300,  2311,  2318,  2328,  2343,  2354,  2384,  2405,  2425,
    2455,  2475,  2506,  2527,  2545,  2574,  2602,  2628,  2647,  2665,
    2693,  2709,  2726,  2746,  2767,  2785,  2801,  2820,  2836,  2847,
    2863,  2871,  2880,  2904,  2930,  2945,  2959,  2978,  2990,  2996,
    3001,  3011,  3025,  3032,  3039,  3045,  3050,  3055,  3061,  3072,
    3077,  3083,  3097,  3102,  3107
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     228,     0,    -1,   229,   293,    -1,   229,   294,   293,    -1,
      -1,   230,    -1,   231,    -1,     1,    -1,     3,    -1,   230,
       3,    -1,   230,   292,    -1,   230,   288,    -1,   230,   284,
      -1,   295,   292,   232,    -1,   297,   292,   235,    -1,   298,
     292,   236,    -1,   296,   292,   238,    -1,   303,   292,   240,
      -1,   304,   292,   246,    -1,   305,   292,   253,    -1,   306,
     292,   247,    -1,   311,   292,   237,    -1,   312,   292,   239,
      -1,   313,   292,   233,    -1,   314,   292,   234,    -1,   392,
     292,   241,    -1,   299,   292,   242,    -1,   300,   292,   243,
      -1,   301,   292,   244,    -1,   302,   292,   245,    -1,   391,
     292,   249,    -1,   392,    -1,   396,    -1,   315,    -1,   374,
     292,   272,    -1,   376,   292,   310,   292,   282,   292,   272,
     292,   272,    -1,   376,   292,   282,   292,   272,   292,   272,
      -1,   376,   292,   310,   292,   272,   292,   272,    -1,   376,
     292,   310,   292,   272,   292,   272,   292,   269,    -1,   376,
     292,   272,   292,   272,    -1,   376,   292,   272,   292,   272,
     292,   269,    -1,   364,    -1,   364,   292,   275,    -1,   320,
      -1,   321,    -1,   322,    -1,   323,    -1,   333,    -1,   339,
      -1,   338,    -1,   337,    -1,   334,    -1,   335,    -1,   336,
      -1,   324,    -1,   325,    -1,   326,    -1,   327,    -1,   328,
      -1,   329,    -1,   330,    -1,   331,    -1,   332,    -1,   393,
      -1,   340,    -1,   342,    -1,   320,    -1,   321,    -1,   322,
      -1,   323,    -1,   333,    -1,   339,    -1,   338,    -1,   337,
      -1,   334,    -1,   335,    -1,   336,    -1,   324,    -1,   325,
      -1,   326,    -1,   327,    -1,   328,    -1,   329,    -1,   330,
      -1,   331,    -1,   332,    -1,   393,    -1,   340,    -1,   342,
      -1,   362,   292,   250,   263,   292,   264,   292,   265,   292,
     271,   292,   274,   292,   269,   292,   267,    -1,   362,   292,
     250,   263,   292,   264,   292,   265,   292,   271,   292,   274,
     292,   269,   292,   267,   292,   256,    -1,   362,   292,   250,
     263,   292,   264,   292,   265,   292,   271,   292,   274,   292,
     269,   292,   267,   292,   276,    -1,   362,   292,   250,   263,
     292,   264,   292,   265,   292,   271,   292,   274,   292,   269,
     292,   267,   292,   256,   292,   276,    -1,   362,   292,   263,
     292,   264,   292,   265,    -1,   315,   292,   268,    -1,   364,
     292,   263,    -1,   364,   292,   307,    -1,   374,   292,   380,
     292,   272,    -1,   374,   292,   272,    -1,   377,   292,   272,
      -1,   316,    -1,   356,    -1,   366,   292,   319,   292,   284,
      -1,   361,   292,   319,   292,   284,   292,   284,    -1,   361,
     292,   319,   292,   284,   292,   284,   292,   251,    -1,   317,
      -1,   352,   292,   319,   292,   284,    -1,   351,   292,   319,
     292,   284,   292,   284,    -1,   351,   292,   319,   292,   284,
     292,   284,   292,   251,    -1,   349,    -1,   359,    -1,   350,
     292,   319,   292,   288,    -1,   360,   292,   319,   292,   288,
      -1,   367,   292,   319,   292,   288,   292,   288,    -1,   358,
     292,   319,   292,   288,   292,   288,   292,   284,    -1,   354,
     292,   319,   292,   288,   292,   288,    -1,   353,   292,   319,
     292,   288,   292,   288,   292,   284,    -1,   318,    -1,   315,
     292,   319,   292,   268,    -1,   315,   292,   337,   292,   252,
     292,   268,    -1,   315,   292,   338,   292,   268,    -1,   315,
     292,   339,   292,   268,    -1,   344,   292,   319,   292,   271,
      -1,   384,   292,   319,    -1,   340,    -1,   341,    -1,   363,
     292,   263,    -1,   363,   292,   307,    -1,   362,   292,   319,
     292,   263,   292,   264,   292,   265,    -1,   365,    -1,   364,
     292,   319,   292,   263,    -1,   373,   292,   268,    -1,   372,
     292,   319,   292,   268,   292,   270,    -1,   375,   292,   382,
     292,   272,    -1,   375,   292,   272,    -1,   374,   292,   319,
     292,   272,    -1,   376,   292,   382,   292,   272,    -1,   376,
     292,   272,    -1,   377,   292,   319,   292,   272,    -1,   378,
     292,   319,   292,   288,    -1,   385,    -1,   348,   292,   288,
     292,   284,     4,   278,    -1,   353,   292,   288,   292,   288,
     292,   284,     4,   278,    -1,   357,   292,   288,   292,   284,
       4,   278,    -1,   358,   292,   288,   292,   288,   292,   284,
       4,   278,    -1,   315,   292,   248,    -1,   364,   292,   394,
     292,   263,   292,   275,    -1,   372,   292,   394,   292,   268,
     292,   270,   292,   277,    -1,   372,   292,   354,   292,   268,
     292,   270,   292,   258,   292,   258,    -1,   372,   292,   371,
     292,   268,   292,   270,   292,   266,    -1,   372,   292,   386,
     292,   268,   292,   270,   292,   267,    -1,   374,   292,   394,
     292,   272,   292,   273,    -1,   374,   292,   379,   292,   272,
     292,   291,    -1,   377,   292,   394,   292,   272,   292,   273,
      -1,   377,   292,   379,   292,   272,   292,   291,    -1,   395,
     292,   283,    -1,   385,   292,   267,    -1,   350,   292,   284,
     292,   251,    -1,   350,   292,   284,    -1,   360,   292,   284,
     292,   251,    -1,   360,   292,   284,    -1,   372,   292,   268,
     292,   266,    -1,   372,   292,   268,   292,   266,   292,   277,
      -1,   315,   292,   268,    -1,   363,   292,   263,    -1,   363,
     292,   307,    -1,   376,   292,   383,   292,   272,   292,   280,
      -1,   376,   292,   272,   292,   280,    -1,   375,   292,   383,
     292,   272,   292,   280,    -1,   375,   292,   272,   292,   280,
      -1,   374,   292,   272,   292,   272,    -1,   377,   292,   272,
     292,   272,    -1,   374,   292,   272,   292,   272,    -1,   377,
     292,   272,   292,   272,    -1,   350,   292,   288,    -1,   360,
     292,   288,    -1,   372,   292,   268,   292,   270,    -1,   343,
     292,   254,    -1,   344,   292,   255,    -1,   350,   292,   268,
     292,   257,    -1,   354,   292,   268,   292,   258,   292,   258,
      -1,   355,   292,   268,   292,   259,    -1,   370,   292,   268,
     292,   257,   292,   260,   292,   261,    -1,   360,   292,   268,
     292,   257,    -1,   367,   292,   268,   292,   260,    -1,   368,
     292,   268,   292,   261,    -1,   369,   292,   268,   292,   262,
      -1,   385,   292,   268,   292,   267,    -1,   387,   292,   268,
     292,   283,    -1,   388,   292,   268,   292,   283,    -1,   364,
     292,   268,   292,   263,    -1,   364,   292,   268,   292,   308,
      -1,   364,   292,   268,   292,   309,    -1,   343,   292,   268,
      -1,    -1,   310,   292,    -1,   284,     4,   278,    -1,   251,
     292,   284,     4,   278,    -1,   389,    -1,   390,    -1,   349,
      -1,   359,    -1,   318,    -1,   316,    -1,   356,    -1,   317,
      -1,   363,   292,   263,    -1,   363,   292,   307,    -1,   365,
      -1,   373,   292,   268,    -1,   375,   292,   382,   292,   272,
      -1,   375,   292,   272,    -1,   376,   292,   382,   292,   272,
      -1,   376,   292,   272,    -1,   274,   292,   269,   292,   268,
      -1,   310,   292,   274,   292,   269,   292,   268,    -1,   271,
     292,   268,    -1,   345,    -1,   346,    -1,   347,    -1,   288,
      -1,   288,    -1,   284,    -1,   288,    -1,   288,    -1,   307,
      -1,   284,    -1,   288,    -1,   288,    -1,   288,    -1,   288,
      -1,   285,    -1,   288,    -1,   288,    -1,   288,    -1,   288,
      -1,   284,    -1,   291,    -1,   291,    -1,   291,    -1,   291,
      -1,   291,    -1,   291,    -1,   279,    -1,   278,     5,   279,
      -1,   284,    -1,   291,    -1,   288,    -1,   285,    -1,   284,
       4,   281,    -1,   280,   292,   284,     4,   281,    -1,   284,
      -1,   291,    -1,   382,    -1,   383,    -1,   381,    -1,   288,
      -1,   284,    -1,   289,    -1,   284,   289,    -1,   286,     6,
     286,    -1,     7,   286,     6,   286,    -1,     8,   286,     6,
     286,    -1,   287,    -1,   286,   287,    -1,     9,    -1,    10,
      -1,    11,    -1,    12,    -1,    13,    -1,    14,    -1,    15,
      -1,    16,    -1,    17,    -1,    18,    -1,   287,    -1,    10,
     286,    -1,    11,   286,    -1,    12,   286,    -1,    13,   286,
      -1,    14,   286,    -1,    15,   286,    -1,    16,   286,    -1,
      17,   286,    -1,    18,   286,    -1,    19,    -1,    20,    -1,
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
     220,    -1,   221,    -1,   292,    -1,   284,    -1,   290,   292,
      -1,   290,   284,    -1,   222,   290,   222,    -1,   223,   290,
     223,    -1,   224,    -1,   225,    -1,   226,    -1,    19,    22,
      22,    -1,    25,    23,    38,    -1,    31,    19,    34,    -1,
      39,    32,    31,    19,    34,    -1,    21,    30,    23,    19,
      36,    -1,    24,    27,    32,    22,    -1,    31,    33,    40,
      23,    -1,    21,    33,    34,    43,    -1,    21,    36,    23,
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
      24,    33,    -1,    22,    20,    89,    27,    32,    37,    38,
      36,    39,    31,    23,    32,    38,    37,    89,    28,    33,
      20,    89,    27,    32,    24,    33,    -1,    21,    26,    19,
      32,    32,    23,    30,    89,    21,    33,    39,    32,    38,
      -1,    21,    26,    19,    32,    32,    23,    30,    89,    27,
      32,    24,    33,    -1,    24,    42,    89,    37,    23,    32,
      22,    89,    21,    33,    39,    32,    38,    -1,    24,    42,
      89,    37,    23,    32,    22,    89,    27,    32,    24,    33,
      -1,    20,    39,    24,    24,    23,    36,    89,    24,    27,
      30,    30,    -1,    37,    38,    36,    23,    19,    31,    89,
      21,    33,    39,    32,    38,    -1,    40,    33,    27,    21,
      23,    89,    21,    33,    39,    32,    38,    -1,    38,    33,
      38,    19,    30,    89,    40,    33,    27,    21,    23,    89,
      21,    33,    39,    32,    38,    -1,    38,    33,    38,    19,
      30,    89,    40,    33,    27,    21,    23,    89,    21,    33,
      39,    32,    38,    89,    31,    19,    42,    -1,    25,    30,
      33,    20,    19,    30,    89,    27,    32,    24,    33,    -1,
      27,    32,    37,    38,    36,    39,    31,    23,    32,    38,
      -1,    23,    32,    25,    27,    32,    23,    -1,    33,    32,
      89,    22,    23,    31,    19,    32,    22,    -1,    33,    32,
      89,    22,    23,    31,    19,    32,    22,    89,    26,    33,
      30,    22,    -1,    34,    23,    36,    37,    27,    37,    38,
      23,    32,    38,    -1,    19,    39,    22,    27,    33,    89,
      33,    39,    38,    34,    39,    38,    89,    22,    23,    40,
      27,    21,    23,    89,    34,    19,    36,    19,    31,    23,
      38,    23,    36,    -1,    19,    39,    22,    27,    33,    89,
      33,    39,    38,    34,    39,    38,    89,    22,    23,    40,
      27,    21,    23,    37,    -1,    19,    39,    22,    27,    33,
      89,    33,    39,    38,    34,    39,    38,    89,    22,    23,
      40,    27,    21,    23,    -1,    19,    39,    22,    27,    33,
      89,    33,    39,    38,    34,    39,    38,    89,    22,    36,
      27,    40,    23,    36,    89,    34,    19,    36,    19,    31,
      23,    38,    23,    36,    -1,    19,    39,    22,    27,    33,
      89,    33,    39,    38,    34,    39,    38,    89,    22,    36,
      27,    40,    23,    36,    -1,    19,    39,    22,    27,    33,
      89,    33,    39,    38,    34,    39,    38,    89,    21,    26,
      19,    32,    32,    23,    30,    89,    34,    19,    36,    19,
      31,    23,    38,    23,    36,    -1,    19,    39,    22,    27,
      33,    89,    33,    39,    38,    34,    39,    38,    89,    21,
      26,    19,    32,    32,    23,    30,    -1,    19,    39,    22,
      27,    33,    89,    33,    39,    38,    34,    39,    38,    89,
      38,    43,    34,    23,    -1,    19,    40,    19,    27,    30,
      19,    20,    30,    23,    89,    31,    27,    22,    27,    89,
      27,    32,    34,    39,    38,    89,    22,    36,    27,    40,
      23,    36,    37,    -1,    31,    27,    22,    27,    89,    27,
      32,    34,    39,    38,    89,    22,    23,    40,    27,    21,
      23,    89,    34,    19,    36,    19,    31,    23,    38,    23,
      36,    -1,    31,    27,    22,    27,    89,    27,    32,    34,
      39,    38,    89,    34,    33,    36,    38,    89,    34,    19,
      36,    19,    31,    23,    38,    23,    36,    -1,    31,    27,
      22,    27,    89,    27,    32,    34,    39,    38,    89,    22,
      23,    40,    27,    21,    23,    37,    -1,    31,    27,    22,
      27,    89,    27,    32,    34,    39,    38,    89,    22,    23,
      40,    27,    21,    23,    -1,    31,    27,    22,    27,    89,
      27,    32,    34,    39,    38,    89,    22,    36,    27,    40,
      23,    36,    89,    34,    19,    36,    19,    31,    23,    38,
      23,    36,    -1,    31,    27,    22,    27,    89,    27,    32,
      37,    38,    36,    39,    31,    23,    32,    38,    -1,    31,
      27,    22,    27,    89,    27,    32,    37,    38,    36,    39,
      31,    23,    32,    38,    37,    -1,    31,    27,    22,    27,
      89,    27,    32,    37,    38,    36,    39,    31,    23,    32,
      38,    89,    31,    19,    34,    -1,    31,    27,    22,    27,
      89,    27,    32,    37,    38,    36,    39,    31,    23,    32,
      38,    89,    31,    19,    34,    37,    -1,    31,    27,    22,
      27,    89,    27,    32,    34,    39,    38,    89,    22,    36,
      27,    40,    23,    36,    -1,    31,    27,    22,    27,    89,
      27,    32,    34,    39,    38,    89,    34,    33,    36,    38,
      -1,    31,    27,    22,    27,    89,    27,    32,    34,    39,
      38,    89,    21,    26,    19,    32,    32,    23,    30,    -1,
      31,    27,    22,    27,    89,    27,    32,    34,    39,    38,
      89,    38,    43,    34,    23,    -1,    31,    27,    22,    27,
      89,    27,    32,    34,    39,    38,    -1,    31,    27,    22,
      27,    89,    21,    33,    32,    38,    36,    33,    30,    30,
      23,    36,    -1,    24,    42,    89,    37,    23,    32,    22,
      -1,    24,    42,    89,    37,    23,    32,    22,    37,    -1,
      22,    20,    89,    27,    32,    37,    38,    36,    39,    31,
      23,    32,    38,    89,    22,    27,    36,    23,    21,    38,
      33,    36,    43,    -1,    22,    20,    89,    27,    32,    37,
      38,    36,    39,    31,    23,    32,    38,    89,    22,    27,
      36,    23,    21,    38,    33,    36,    27,    23,    37,    -1,
      22,    20,    89,    27,    32,    37,    38,    36,    39,    31,
      23,    32,    38,    37,    -1,    22,    20,    89,    27,    32,
      37,    38,    36,    39,    31,    23,    32,    38,    -1,    22,
      20,    89,    27,    32,    37,    38,    36,    39,    31,    23,
      32,    38,    37,    89,    28,    33,    20,    -1,    22,    23,
      37,    21,    36,    27,    34,    38,    27,    33,    32,    -1,
      24,    33,    36,    21,    23,    -1,    24,    30,    19,    38,
      -1,    36,    23,    21,    39,    36,    37,    27,    40,    23,
      -1,    32,    33,    32,    89,    36,    23,    21,    39,    36,
      37,    27,    40,    23,    -1,    37,    23,    36,    40,    23,
      36,    -1,    40,    33,    30,    39,    31,    23,    -1,    30,
      23,    40,    23,    30,    -1,    31,    39,    38,    23,    -1,
      37,    33,    30,    33,    -1,    20,    43,    38,    23,    37,
      -1,    34,    23,    36,    21,    23,    32,    38,    19,    25,
      23,    -1,    23,    22,    27,    38,    -1,    36,    23,    37,
      23,    38,    -1,    31,    27,    37,    21,    23,    30,    30,
      19,    32,    23,    33,    39,    37,    -1,    32,    19,    31,
      23,    -1,    23,    21,    26,    33,    -1,    35,    39,    27,
      38,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    97,    97,    98,   101,   102,   103,   104,   107,   108,
     109,   110,   111,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   198,
     199,   200,   201,   204,   207,   208,   209,   210,   211,   212,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   276,   277,   278,
     279,   280,   281,   284,   287,   288,   291,   292,   293,   294,
     297,   298,   301,   302,   305,   306,   307,   310,   311,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   330,   333,   334,   337,   338,   341,   342,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   361,   362,   365,   368,   369,   370,
     373,   376,   379,   382,   385,   386,   389,   392,   395,   398,
     401,   404,   405,   408,   411,   414,   417,   420,   423,   426,
     429,   432,   435,   438,   439,   442,   443,   444,   445,   448,
     449,   452,   453,   456,   457,   458,   466,   467,   470,   471,
     474,   475,   476,   480,   481,   484,   485,   486,   487,   488,
     489,   490,   491,   492,   493,   496,   497,   498,   499,   500,
     501,   502,   503,   504,   505,   507,   507,   507,   507,   507,
     507,   507,   507,   507,   507,   507,   507,   507,   507,   507,
     507,   507,   507,   507,   507,   507,   507,   507,   507,   507,
     507,   508,   508,   508,   508,   508,   508,   508,   508,   508,
     508,   508,   508,   508,   508,   508,   508,   508,   508,   508,
     508,   508,   508,   508,   508,   508,   508,   509,   509,   509,
     509,   509,   509,   509,   509,   509,   509,   510,   510,   510,
     510,   510,   510,   510,   510,   510,   510,   510,   510,   510,
     511,   511,   511,   511,   511,   511,   511,   512,   512,   512,
     512,   512,   513,   513,   513,   513,   514,   514,   514,   515,
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
     552,   552,   552,   553,   553,   553,   554,   554,   554,   555,
     555,   555,   556,   556,   559,   560,   561,   562,   565,   566,
     572,   575,   578,   581,   584,   587,   590,   593,   596,   599,
     602,   605,   608,   611,   614,   617,   620,   623,   626,   629,
     632,   635,   638,   641,   644,   647,   650,   653,   656,   659,
     662,   665,   668,   671,   674,   677,   680,   683,   686,   689,
     692,   695,   698,   701,   704,   707,   710,   713,   716,   719,
     722,   725,   728,   731,   734,   737,   740,   743,   746,   749,
     752,   755,   758,   761,   764,   767,   770,   773,   776,   779,
     782,   785,   788,   791,   794,   797,   800,   803,   806,   809,
     812,   815,   818,   821,   824,   827,   830,   833,   836,   839,
     842,   845,   848,   851,   854,   857,   860,   863,   866,   869,
     872,   875,   878,   881,   884
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
  "'\\233'", "'\\234'", "'\\235'", "'\\236'", "'\\237'", "' '", "'¡'",
  "'¢'", "'£'", "'¤'", "'¥'", "'¦'", "'§'", "'¨'", "'©'", "'ª'", "'«'",
  "'¬'", "'­'", "'®'", "'¯'", "'°'", "'±'", "'²'", "'³'", "'´'", "'µ'",
  "'¶'", "'·'", "'¸'", "'¹'", "'º'", "'»'", "'¼'", "'½'", "'¾'", "'¿'",
  "'À'", "'Á'", "'Â'", "'Ã'", "'Ä'", "'Å'", "'Æ'", "'Ç'", "'È'", "'É'",
  "'Ê'", "'Ë'", "'Ì'", "'Í'", "'Î'", "'Ï'", "'Ð'", "'Ñ'", "'Ò'", "'Ó'",
  "'Ô'", "'Õ'", "'Ö'", "'×'", "'Ø'", "'Ù'", "'Ú'", "'Û'", "'Ü'", "'Ý'",
  "'Þ'", "'ß'", "'à'", "'á'", "'â'", "'ã'", "'ä'", "'å'", "'æ'", "'ç'",
  "'è'", "'é'", "'ê'", "'ë'", "'ì'", "'í'", "'î'", "'ï'", "'ð'", "'ñ'",
  "'ò'", "'ó'", "'ô'", "'õ'", "'ö'", "'÷'", "'ø'", "'ù'", "'ú'", "'û'",
  "'ü'", "'ý'", "'þ'", "'ÿ'", "'''", "'\"'", "' '", "'\\n'", "'\\r'",
  "$accept", "input", "line", "comment", "command", "add_instruction",
  "subscribe_event", "unsubscribe_event", "map_instruction",
  "unmap_instruction", "remove_instruction", "get_instruction",
  "set_instruction", "create_instruction", "reset_instruction",
  "clear_instruction", "find_instruction", "move_instruction",
  "copy_instruction", "destroy_instruction", "load_instruction",
  "set_chan_instruction", "edit_instruction", "modal_arg", "key_val_list",
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
  "PERCENTAGE", "EDIT", "RESET", "MISCELLANEOUS", "NAME", "ECHO", "QUIT", 0
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
     231,   231,   231,   232,   232,   232,   232,   232,   232,   232,
     232,   232,   232,   233,   233,   233,   233,   233,   233,   233,
     233,   233,   233,   233,   233,   233,   233,   233,   233,   233,
     233,   233,   233,   233,   233,   233,   234,   234,   234,   234,
     234,   234,   234,   234,   234,   234,   234,   234,   234,   234,
     234,   234,   234,   234,   234,   234,   234,   234,   234,   235,
     235,   235,   235,   236,   237,   237,   237,   237,   237,   237,
     238,   238,   238,   238,   238,   238,   238,   238,   238,   238,
     238,   238,   238,   238,   238,   238,   238,   238,   238,   238,
     238,   238,   238,   238,   238,   238,   238,   238,   238,   238,
     238,   238,   238,   238,   238,   238,   238,   238,   238,   238,
     238,   239,   239,   239,   239,   239,   239,   239,   239,   239,
     239,   239,   239,   239,   239,   239,   239,   240,   240,   240,
     240,   240,   240,   241,   242,   242,   243,   243,   243,   243,
     244,   244,   245,   245,   246,   246,   246,   247,   247,   248,
     248,   248,   248,   248,   248,   248,   248,   248,   248,   248,
     248,   248,   248,   249,   250,   250,   251,   251,   252,   252,
     253,   253,   253,   253,   253,   253,   253,   253,   253,   253,
     253,   253,   253,   253,   254,   254,   255,   256,   256,   256,
     257,   258,   259,   260,   261,   261,   262,   263,   264,   265,
     266,   267,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   278,   279,   279,   279,   279,   280,
     280,   281,   281,   282,   282,   282,   283,   283,   284,   284,
     285,   285,   285,   286,   286,   287,   287,   287,   287,   287,
     287,   287,   287,   287,   287,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   290,   290,   290,   290,   291,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   325,   326,   327,   328,   329,   330,   331,
     332,   333,   334,   335,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,   353,   354,   355,   356,   357,   358,   359,   360,   361,
     362,   363,   364,   365,   366,   367,   368,   369,   370,   371,
     372,   373,   374,   375,   376,   377,   378,   379,   380,   381,
     382,   383,   384,   385,   386,   387,   388,   389,   390,   391,
     392,   393,   394,   395,   396
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     3,     0,     1,     1,     1,     1,     2,
       2,     2,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     1,     1,     3,     9,     7,     7,     9,     5,
       7,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,    16,
      18,    18,    20,     7,     3,     3,     3,     5,     3,     3,
       1,     1,     5,     7,     9,     1,     5,     7,     9,     1,
       1,     5,     5,     7,     9,     7,     9,     1,     5,     7,
       5,     5,     5,     3,     1,     1,     3,     3,     9,     1,
       5,     3,     7,     5,     3,     5,     5,     3,     5,     5,
       1,     7,     9,     7,     9,     3,     7,     9,    11,     9,
       9,     7,     7,     7,     7,     3,     3,     5,     3,     5,
       3,     5,     7,     3,     3,     3,     7,     5,     7,     5,
       5,     5,     5,     5,     3,     3,     5,     3,     3,     5,
       7,     5,     9,     5,     5,     5,     5,     5,     5,     5,
       5,     5,     5,     3,     0,     2,     3,     5,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     1,     3,
       5,     3,     5,     3,     5,     7,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     1,     1,     1,     3,
       5,     1,     1,     1,     1,     1,     1,     1,     1,     2,
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
      23,    13,    12,    13,    12,    11,    12,    11,    17,    21,
      11,    10,     6,     9,    14,    10,    29,    20,    19,    29,
      19,    30,    20,    17,    28,    27,    25,    18,    17,    27,
      15,    16,    19,    20,    17,    15,    18,    15,    10,    15,
       7,     8,    23,    25,    14,    13,    18,    11,     5,     4,
       9,    13,     6,     6,     5,     4,     4,     5,    10,     4,
       5,    13,     4,     4,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     7,     8,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     5,     6,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    31,    32,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     1,   511,   512,     2,     0,
       9,   363,   358,   357,   355,   356,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   336,   347,   349,
     350,   351,   352,   353,   354,   359,   360,   361,   362,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   438,   439,   440,   441,   442,   443,   444,
     445,   446,   447,   448,   449,   450,   451,   452,   453,   454,
     455,   456,   457,   458,   459,   460,   461,   462,   463,   464,
     465,   466,   467,   468,   469,   470,   471,   472,   473,   474,
     475,   476,   477,   478,   479,   480,   481,   482,   483,   484,
     485,   486,   487,   488,   489,   490,   491,   492,   493,   494,
     495,   496,   497,   498,   499,   500,   501,   502,   503,   510,
      12,   275,    11,   258,    10,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   513,     0,     0,     0,     0,     0,     0,
     514,     0,     0,   515,     0,     0,     0,     0,   530,     0,
       0,     0,     3,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   276,   263,   277,   278,   279,   280,   281,
     282,   283,   284,   348,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   259,     0,     0,     0,    13,    33,
      41,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    16,     0,   100,   105,   117,   124,   125,     0,
     109,     0,     0,     0,     0,     0,   101,     0,   110,     0,
       0,     0,     0,     0,   129,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   140,     0,    14,     0,    15,
       0,     0,    26,     0,     0,    27,     0,     0,     0,    28,
       0,     0,    29,     0,     0,     0,     0,     0,    17,     0,
       0,     0,    18,     0,     0,     0,     0,     0,     0,     0,
      19,   203,   205,   202,   200,   204,   201,     0,   208,     0,
       0,     0,     0,    20,     0,     0,    21,     0,     0,     0,
       0,     0,     0,     0,    22,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    23,    43,    44,    45,
      46,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      47,    51,    52,    53,    50,    49,    48,    64,    65,    63,
      24,    66,    67,    68,    69,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    70,    74,    75,    76,    73,    72,
      71,    87,    88,    86,    30,     0,    25,     0,     0,   520,
       0,     0,   609,   518,   523,   524,   519,   614,     0,     0,
       0,     0,     0,   264,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   194,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   517,     0,     0,     0,
     610,     0,   516,     0,     0,     0,     0,     0,     0,    42,
     240,    34,   237,     0,     0,     0,     0,     0,     0,   255,
     253,   254,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   266,   267,   268,
     269,   270,   271,   272,   273,   274,     0,   126,   227,   127,
       0,     0,     0,     0,   131,   233,     0,   134,     0,   137,
       0,     0,     0,   123,     0,     0,     0,     0,     0,     0,
     164,   165,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   158,   160,     0,   174,
     175,     0,     0,     0,     0,     0,   206,   207,   209,   211,
       0,   213,     0,     0,   177,     0,   239,     0,   178,     0,
     236,    94,    95,    96,     0,    98,     0,    99,     0,     0,
       0,     0,     0,     0,   145,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   156,   231,     0,
     263,   232,   155,   257,   256,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   193,   163,   521,     0,
     529,     0,     0,     0,     0,     0,   505,     0,   504,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   195,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   613,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   522,     0,
       0,     0,     0,     0,   508,   507,   506,   509,     0,     0,
       0,    39,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   118,     0,     0,     0,
     198,   199,   120,   121,   122,   111,     0,   106,     0,     0,
       0,   112,     0,     0,   525,   130,   102,     0,     0,   135,
     133,   136,   138,   139,     0,     0,     0,     0,   228,     0,
       0,     0,   169,     0,     0,   167,     0,     0,   170,   171,
     172,   173,     0,     0,     0,   157,     0,   159,   161,   230,
     176,   235,     0,     0,     0,     0,   210,   212,     0,     0,
     234,     0,   216,     0,    97,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   260,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     599,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   562,     0,     0,   602,     0,   603,   537,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   605,
     606,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   612,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   261,   262,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   531,     0,   533,     0,     0,     0,
       0,     0,    40,    36,    37,     0,     0,     0,   533,     0,
     590,     0,     0,     0,     0,   119,   107,     0,   115,     0,
     103,     0,   113,   132,     0,     0,    93,   229,     0,     0,
       0,   249,   251,   252,   168,   166,     0,     0,   590,     0,
       0,   355,   356,   196,   243,   245,   248,   247,   246,   162,
     242,     0,     0,     0,     0,     0,   214,     0,   598,     0,
       0,     0,     0,   179,   220,     0,   221,   181,   222,   183,
       0,     0,   190,   191,   192,   184,   223,   185,   224,   225,
     186,   226,     0,   187,   188,   189,   141,     0,   143,     0,
     146,     0,   604,     0,     0,     0,     0,     0,     0,   152,
     151,   238,   154,   153,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   536,     0,   591,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   532,     0,     0,     0,     0,     0,    38,    35,
       0,     0,     0,     0,     0,     0,   607,     0,   108,   116,
     114,   104,   128,     0,     0,     0,     0,   250,     0,     0,
       0,   197,   244,     0,     0,     0,     0,   215,     0,     0,
       0,     0,   180,     0,     0,     0,   142,   144,     0,     0,
       0,   149,   150,   147,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   561,     0,     0,     0,     0,     0,   526,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   528,
       0,   600,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   182,     0,     0,   148,
       0,     0,   555,     0,     0,     0,     0,     0,   560,     0,
       0,     0,     0,     0,   557,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   588,     0,     0,     0,     0,     0,     0,   552,
       0,     0,   554,     0,     0,     0,   556,     0,     0,     0,
       0,     0,     0,     0,     0,   595,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   595,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   527,     0,     0,
     597,     0,   551,     0,   553,     0,     0,   611,     0,   594,
       0,     0,     0,     0,     0,     0,     0,     0,   594,     0,
       0,     0,     0,     0,     0,   608,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   601,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   585,   580,     0,   580,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   581,     0,     0,
      89,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     534,     0,     0,     0,   578,   584,     0,     0,   558,     0,
       0,     0,   578,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   585,   587,   589,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   558,     0,     0,     0,     0,     0,
       0,     0,   596,     0,   577,     0,     0,     0,     0,     0,
       0,    90,    91,   241,   217,   218,   219,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   549,     0,     0,     0,     0,     0,   582,     0,   568,
     570,     0,     0,     0,     0,     0,   582,     0,     0,     0,
       0,     0,   568,     0,     0,     0,     0,     0,     0,   573,
       0,     0,     0,   548,     0,     0,     0,     0,     0,     0,
       0,   572,   567,     0,     0,     0,     0,     0,     0,   583,
       0,     0,     0,    92,     0,     0,     0,     0,     0,   586,
       0,     0,     0,     0,     0,     0,   545,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   559,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   544,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   572,     0,     0,     0,     0,
       0,   541,     0,     0,   592,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   550,     0,
     540,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   539,     0,     0,   543,     0,
       0,     0,     0,   593,     0,   576,     0,     0,     0,     0,
     538,     0,     0,   542,     0,     0,     0,     0,     0,   563,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   579,
       0,   565,     0,   575,     0,     0,     0,     0,     0,   574,
       0,     0,     0,   547,     0,   569,     0,     0,   566,   546,
     571,   535,     0,   564
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    15,    16,    17,    18,   358,   486,   510,   407,   409,
     456,   372,   464,   428,   536,   412,   415,   419,   422,   432,
     453,   794,   534,   736,  1065,  1019,   440,   774,   778,  1861,
    1313,  1315,  1317,  1325,  1327,  1330,   717,  1047,  1276,  1068,
     827,   724,  1079,  1070,   779,   671,  1350,   775,   669,  1862,
    1299,  1293,  1294,  1052,  1281,   677,   832,  1295,  1296,   829,
     281,   725,   283,   857,   672,  1176,    58,    59,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
    1329,  1323,  1324,   678,    31,    32,    33,    34,   359,   374,
     375,   376,   693,   487,   488,   489,   490,   491,   492,   493,
     494,   495,   496,   497,   498,   499,   500,   501,   502,   503,
     504,   505,   506,   377,   378,   508,   454,   379,  1864,  1865,
    1866,   466,   380,   381,   382,   383,   384,   385,   797,   386,
     468,   387,   388,   389,   390,   391,   392,   360,   394,   395,
     396,   801,   802,   803,   817,   397,   398,   361,   400,   362,
     402,   403,   821,   786,   679,   680,   681,   404,   405,   818,
     805,   806,  1020,  1021,    35,    36,   509,   812,   475,    37
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -1328
static const yytype_int16 yypact[] =
{
      46, -1328, -1328,    76,   149,   131,   101,   151,   189,   182,
     100,   218,   241,    70,   257,   293,   172,  2525, -1328,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83, -1328,   296,   299,
     304,   303,   322,   306,   318,   352,   378,   412,   401,   446,
     470,   269,   479,   499,   294, -1328, -1328, -1328, -1328,   323,
   -1328, -1328, -1328, -1328, -1328, -1328, -1328,   527,   527,   527,
     527,   527,   527,   527,   527,   527, -1328, -1328, -1328, -1328,
   -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328,
   -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328,
   -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328,
   -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328,
   -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328,
   -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328,
   -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328,
   -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328,
   -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328,
   -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328,
   -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328,
   -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328,
   -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328,
   -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328,
   -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328,
   -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328,
   -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328,
   -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328,
   -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328,
   -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328,
    3411, -1328, -1328, -1328, -1328,   153,    80,   518,   518,   530,
     543,   544,   544,   209,   209,   261,   130,   248,   103,   292,
     292,   540,   547, -1328,   550,   528,   551,   534,   535,   552,
   -1328,   537,   554, -1328,   555,   539,   546,   557, -1328,   545,
     562,   549, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328,
   -1328, -1328, -1328,   527, -1328,   527,   527,   527,   527,   527,
     527,   527,   527, -1328, -1328, -1328, -1328, -1328, -1328, -1328,
   -1328, -1328, -1328, -1328, -1328,   558,   563,   559, -1328, -1328,
      83,    83,    83,   405,   564,   565,   560,   566,   567,   568,
     569,   571, -1328,    83, -1328, -1328, -1328, -1328, -1328,    83,
   -1328,    83,    83,    83,    83,    83, -1328,    83, -1328,    83,
      83,    83,    83,    83, -1328,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83, -1328,   572, -1328,    83, -1328,
      83,   573, -1328,    83,   585, -1328,    83,    83,   586, -1328,
      83,    83, -1328,    83,    83,   578,   570,   580, -1328,    83,
      83,    83, -1328,    83,    83,    83,   407,   584,   579,   593,
   -1328, -1328, -1328, -1328, -1328, -1328, -1328,    83, -1328,    83,
      83,    83,   590, -1328,    83,    83, -1328,    83,    83,    83,
      83,   587,   602,   597, -1328,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,   588,   592,   606,   616,
     595,   608,   612,   607,   611,   613, -1328, -1328, -1328, -1328,
   -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328,
   -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328,
   -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328,
   -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328,
   -1328, -1328, -1328, -1328, -1328,    83, -1328,    83,   618, -1328,
     609,   619, -1328, -1328, -1328, -1328, -1328, -1328,   622,   615,
     635,   624,   643, -1328,   645,   576,   644,   238,   238,     9,
     646,   648,   654,   601,   649,   621,   653,   655,   663,   672,
     118,   680,   680,   680,   680,   680,   680,   680,   680,   680,
     680,   410,   680,   680,   680,   680,   542,   680,    43,    43,
     680,   680,   680,   686,   684,   542,   690,   410,   628,    14,
      14,   629,   238,   238,   238,   238,   697,   633,   701,  3411,
    3411,   542,   542,   542,   542,   702,   706,   637,   709,   410,
     542,    43,    43,   699,    16,  3411,   542,   410,    19,   238,
     715,   712,   721,   111,   542,   542,   542,   542,   713,   215,
     124,   124,   514,  3630,   724,   725,   729,   661,   662,   719,
      75,   718,   723,   730,   542,   542, -1328,   733,   726,   740,
   -1328,   728, -1328,   731,   734,   738,   743,  2747,  2747, -1328,
   -1328, -1328, -1328,   737,   739,   748,    83,    83,    83, -1328,
   -1328, -1328,   746,   747,   744,   750,   770,   761,   776,   735,
     789,   773,   777,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,   527,   527,   527,
     527,   527,   527,   527,   527,   527,   783, -1328, -1328, -1328,
      83,    83,    83,    83, -1328, -1328,    83, -1328,    83, -1328,
      83,    83,    83, -1328,   787,   782,   542,    83,    83,   790,
   -1328, -1328,   791,   786,    83,    83,    83,    83,   793,    83,
      83,    83,    83,   794,   779,   795,  2747,  2747,    83, -1328,
   -1328,    83,   796,   792,   788,   799, -1328, -1328, -1328, -1328,
      83, -1328,    83,   797, -1328,    83, -1328,    83, -1328,    83,
    3411, -1328, -1328, -1328,   798, -1328,    83, -1328,   800,   801,
     802,   807,   120,   803, -1328,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,   809,    83,   808,   810,   805,    83,    83,    83,    83,
     814,    83,    83,    83,    83,   527,   527, -1328, -1328,   453,
      26, -1328, -1328,  3411, -1328,   811,   806,   816,   812,   804,
     829,   823,   830,   831,   833,   832, -1328, -1328, -1328,   813,
   -1328,   828,   836,   826,   837,   781,  3411,  2081, -1328,  2303,
     849,   839,   851,   238,   238,    54,   840,   844,   843,   845,
     846,   853,   815,   856,   850,   852,   857,   542,   115,   542,
     542,  3411,   542,  3411,  3411,   542,   542,   542,   542,  3411,
     542,   854,   542,  3411,   542,   542,   238,   238,   238,   238,
     542,   818,   855,    83, -1328,   542,   819,   858,   863,  3411,
     238,  3411,   238,   865,   238,   238,   238,   238,   866,   859,
     824,  3411,  3411,   542,   542,   869,   871,   862,   825,   238,
     238,   876,   542,   238,   542,   879,   238,   872, -1328,   827,
     867,   895,   880,   889,   542,   542,   542,   542,   542,   542,
     542,   542,   542,   542,   542,   542,  3411,   542,  3411,   542,
     890,   542,   898,   882,   901,   542,   542,   542,   542,   887,
     238,   238,   238,   238,   466,   490,   527,   892,   903,   896,
     899,   904,   913,   847,   910,   915,   905,   917, -1328,   921,
     907,   922,   909,   920, -1328,  3411, -1328, -1328,   906,   860,
     911,    83,    83,    83,    83,   868,   929,   932,   919,   935,
     927,   933,   926,   875,   943,   936, -1328,   925,   947,    83,
   -1328, -1328, -1328, -1328, -1328, -1328,  2747,  3411,    83,    83,
      83, -1328,  2747,    83, -1328, -1328,  3411,    83,    83, -1328,
   -1328, -1328, -1328, -1328,   944,   883,   542,    83, -1328,   946,
     937,   886,    83,  3849,    83,    83,    83,   939, -1328, -1328,
   -1328, -1328,   891,   950,   952,    83,  4068,    83,    83, -1328,
   -1328, -1328,   894,   965,   957,   963, -1328, -1328,   953,    83,
   -1328,    83, -1328,   970, -1328,   908,   966,   967,   968,   973,
     971,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,  4287,    83,  4506,    83,   975,    83,   972,
     977,   974,    83,    83,    83,    83,   982,    83,    83,    83,
      83,   527,   527,   527,   916,   978,   983,   980,   976,   988,
     992,   993,   979,   918,   938,   999,   997,   995,   990,   994,
   -1328,   199,   996,   542,   238,   238,   238,   998,  1009,  1003,
    1000, -1328,  1012,  1004, -1328,  1001, -1328, -1328,  1002,  1006,
     542,  3411,   542,   542,   542,  3411,   542,   542,   542,  1011,
    1013,    83,   542,  1014,  1007,  1017,  3411,  2969,  3411,  3411,
    1016,  1022,  1025,  1024,  3411,  3190,   238,  1026,  1005,  1027,
    1028,  1030,   542,   542,  1034,  1032,  1031,  1033,   969, -1328,
   -1328,   542,   542,  3411,   542,   154,   542,   410,  3411,   542,
     514,  3630,  3630,  3190,  3411,  3190,  3411, -1328,   238,  1035,
    1037,   981,   542,   542,   542,   542,  1036,   238,   238,   238,
     238,   527,   527,  1040,  1010,  1039,  1048,  1066,  1015,  1058,
    1062,  1019,  1053,  1073, -1328,  1085, -1328,  1074,  1072,  1078,
    1089,  1076, -1328, -1328,    83,    83,  1075,  1088,  1082,  1079,
    1086,   271,  1091,  1099,  1104, -1328,  2747,    83, -1328,    83,
    2747,    83, -1328, -1328,  1092,   542, -1328, -1328,  1093,  1095,
    4725, -1328,  3411, -1328,    83,    83,  1096,  1094, -1328,  1100,
    4944,   527,   527,  1132, -1328,  3411, -1328, -1328, -1328, -1328,
   -1328,  1101,  1082,  1086,   355,  1115, -1328,    83, -1328,  1102,
     368,  1050,  1116, -1328, -1328,    83, -1328, -1328,  3411, -1328,
    1121,  1112, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328,
   -1328,  3411,    83, -1328, -1328, -1328,  1132,  5163,  1132,  5382,
   -1328,  1057, -1328,  1126,    83,    83,    83,    83,  1123, -1328,
   -1328, -1328, -1328, -1328,  1109,  1127,  1063,  1117,  1067,  1128,
     402,  1138,  1137,  1129,  1130,  1136,  1122,  1133,  1142,  1139,
    1140,   542,   238,  1141,  1143, -1328,  1144, -1328,  1145,  1147,
    1148,  1149,  1153,  3411,  3411,  3411,  3411,   542,  1150,    83,
    1151,  1154,  2969,  1155,  1152,  1156,  3190,  3190,  1158,  1159,
    1162,  1160,   542,  1163,  1164,  1169,  1165,   542,  1157,  1172,
     542,  3190,  3190,  1173,  1176,   542,   542,   514,   238,  1131,
    1167,  1187,   313,  1181,   325,  1190,  1186,  1194,  1201,  1202,
    1207,  1197, -1328,  1146,  1203,  1161,  1204,  1200, -1328, -1328,
    1210,  1098,  1214,  1208,  1205,  1227, -1328,  1219,    83,  3411,
    3411,    83, -1328,  1220,  3411,  1221,  1224, -1328,  1228,  1229,
    1223,  1132, -1328,  1230,  1231,  1222,  1232, -1328,  1233,  1234,
    1226,   475, -1328,  1243,  1245,    83,  1132,  1132,  1239,  1247,
      83, -1328, -1328, -1328,  1242,  1237,  1236,  1249,  1251,  1256,
    1255,  1257,  1267,  1258,  1261,  1270,  1260,  1273,  1271,  1279,
    1265,  1275,  1272,  1283,  1274,   244,  1286,  1225,  1277,  1287,
    1280,  1278,    83,  1281,  1288,  1289,  1282,  1235,  1292,  1244,
    1293, -1328,  1295,  1250,  1284,  1299,  1301, -1328,   410,  1303,
    1304,   542,  1298,  1305,  1296,  1306,  1319,  1323,  1308,  1324,
    1316,  1262,  1311,  1320,  1322,  1329,  1317,  1325,  1327, -1328,
    1326, -1328,  1318,  1321,  1332,  1334,  1336,   221,  1328,  1285,
    1300,  1335,   238,  1338,  1339,  1341,  1337,  1348,  1340,  1354,
    1349,  1343,   234,  1345,  1344,  1355, -1328,  1352,  1351, -1328,
    1356,  1350, -1328,  1358,  1359,  1362,  1363,  1364, -1328,  1369,
    1365,  1360,  1366,  1309, -1328,  1367,  1377,  1374,  1330,  1384,
    1382,  1386,  1371,    77,  1378,  1387,  1391,  1389,  1392,    83,
    1397,  1388,  1390,  1346,  1401,  1347,  1402,  1404,  1353,  1406,
    1399,  1394,  1357,  1400,  1398,  1407,  1409,  1361,  1410, -1328,
    1411,  1413, -1328,  1416,  1422,  1393, -1328,  1426,    25,  1420,
    1414,   452,  1428,  1429,  1430,    27,  1419,  1433,  1417,  1432,
    1434,  1438,  1436,   542,  1437,    47,  1376,  1444,  1431,  1448,
    1435,  1440,   489,  1439,  1441,  1442,   139, -1328,  1443,  1452,
   -1328,  1451, -1328,    50, -1328,  1445,  1446, -1328,  1450, -1328,
    1462,  1449,  1463,  1464,   114,  1455,  1457,  1403,  1408,  1469,
    1475,  1456,  1466,  1467,  1468, -1328,  1470,    83,  1471,  1489,
    1490,  1485,  1491,  1488,  1478,  1492,  1494,  1495,  1481,  1447,
    1497,  1496,  1482,  1453,  1500,  1498,  1458,   227,  1504,  1486,
    1493,  1508,  1461, -1328,  1521,  1487,  1514,  1465,  1522,  1517,
    1518,  1524,  1531,  1530,  1473,    52,  1523, -1328,   514,  1519,
    1532,  1525,  1536,  1526,  1546,    55,  1549,  1534,  1550,  1473,
     159,  1558,  1542,  1545,  1559,  1560,  1541,  1554,  1551,  1561,
    1553,  1565,  1501,  1555,  1557,  1563,  1564,  1562,  1566,  1567,
    1568,  1569,  1570,  1571,  1572,  1573,  1574, -1328,  1579,  1575,
      83,  1576,  1577,  1588,  1587,  1593,  1586,  1589,  1591,  1596,
    1594,  1548,  1590,  1585,  1614,  1602,  1612,  1607,  1603,  1605,
    1578,  1620,   263,  1606,  1622,  1580,  1618,  1630,  1629,  1615,
   -1328,  1619,  1635,  1633,  1621,  1509,  1638,  1641,  1581,    39,
    1639,  1640, -1328,  1642,  1621,  1645,  1634,  1644,  1582,  1648,
    1643,  1636, -1328, -1328, -1328,  1651,  1649,  1646,  1650,  1652,
    1592,  1653,  1647,  1655, -1328,  1654,  1656,  1659,  1660,  1657,
    1658,  1637, -1328,  1663, -1328,  1661,  1662,  1665,  1666,  1668,
    1664,    83, -1328, -1328, -1328, -1328, -1328,  1667,  1669,  1671,
    1670,  1678,  1679,  1672,  1673,  1680,  1684,  1685,  1600,  1674,
    1688, -1328,   326,  1675,  1686,  1677,  1681, -1328,  1683,  1687,
    1626,  1682,  1689,  1690,  1698,  1699,  1692,  1701,  1632,  1694,
     238,  1693, -1328,  1687,  1692,  1695,  1676,  1703,  1691, -1328,
    1696,  1697,  1705, -1328,  1700,  1702,  1704,  1707,  1708,  1710,
    1709,  1711, -1328,  1706,  1712,  1713,  1715,  1714,  1721, -1328,
    1716,  1723,  1717, -1328,  1720,  1711,  1722,  1719,  1736, -1328,
     328,  1728,  1731,  1727,  1737,  1729, -1328,   330,  1732,  1735,
    1724,  1733,  1748,  1738,  1753,  1750, -1328,  1752,  1749,  1741,
    1760,  1761,  1751,  1754,  1756,  1759,  1755,  1757,  1764, -1328,
    1770,  1758,  1762,  1765,  1771,  1725,  1772,    88,  1778,  1773,
    1779,  1775,  1786,  1780,  1784, -1328,  1782,  1768,  1785,  1774,
    1781, -1328,  1783,  1799, -1328,  1788,  1807,  1805,  1803,  1809,
    1811,  1812,  1817,  1800,  1818,  1816,  1808,  1810, -1328,  1763,
   -1328,  1813,  1814,  1823,  1815,  1819,  1820,  1821,  1824,  1825,
    1822,  1826,  1828,  1827,  1829, -1328,   333,  1830, -1328,  1832,
    1833,  1837,  1834, -1328,  1843, -1328,  1831,  1838,  1846,  1848,
   -1328,  1839,  1842, -1328,  1852,  1840,  1836,  1841,  1844,  1790,
    1845,  1847,  1850,  1849,  1857,  1851,  1859,  1861,  1854, -1328,
    1866, -1328,  1864, -1328,  1862,  1860,  1872,  1863,  1865, -1328,
    1867,  1868,  1858, -1328,  1869, -1328,  1870,  1873, -1328, -1328,
   -1328, -1328,  1875, -1328
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328,
   -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328,
   -1328, -1328, -1328, -1328,  -888, -1328, -1328, -1328, -1328, -1328,
    -918, -1327, -1328,  -228,    69, -1328,  -553, -1014, -1225,   275,
   -1188,   681, -1118, -1117,  -861,  -301,   504,  -932,   630,  -154,
     432, -1152,   454,  -883,   506,  1041,  -698,   617,  -621,   -15,
     152,     6,   467,  1240,  -276,   -17,  1853, -1328, -1328, -1328,
   -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328, -1328,
    -487, -1328, -1328,  -503, -1328, -1328, -1328, -1328,   -84,  1616,
    1623,  1624,  -384,  1609,  1610,  1613,  1625,  1627,  1628,  1631,
    1718,  1726,  1730,  1734,  1739,  1740,  1742,  1743,  1744,  1745,
    -273,  -261,  -260,   216, -1328,  1746,  1601,  1766, -1328, -1328,
   -1328, -1328,  1769,  -264, -1328, -1328,  1617,  -245, -1328,  1777,
   -1328,  1767,  1787,  -256, -1328,   246,   106,  -262,  2009, -1328,
    1290, -1328, -1328, -1328, -1328,   -20,  2230,   -81,    68,    29,
      44, -1328,  1291, -1328, -1328,  -493,   -53, -1328,  -272, -1328,
   -1328, -1328, -1328, -1328, -1328, -1328,  1747,  -230, -1328, -1328
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -276
static const yytype_int16 yytable[] =
{
     284,  1081,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
    1024,   828,  1333,   282,   393,  1252,   474,   528,  1055,   429,
     433,  -275,  1171,   673,  1067,   458,   470,   430,   434,   529,
     530,   674,   738,   784,   740,   675,   743,     1,   735,     2,
    1389,  1273,   333,   335,   336,   337,   338,   339,   340,   341,
     342,  1336,  1679,  1338,  1688,     3,   766,     4,     5,     6,
       7,     8,  1859,  1860,   782,  1307,     9,    10,   673,   675,
    1472,    11,    12,    13,  1679,    14,   743,  1716,  1480,  1777,
     675,   737,  1777,    52,   719,   728,   730,   841,    38,   363,
    1646,   364,   365,   366,   367,  1344,  1345,  1346,  1347,    53,
     741,   368,   842,  1647,  1680,  1999,  1689,   369,   370,    48,
     371,   777,   461,    43,   355,   418,   462,   426,   770,   772,
     791,  1994,   767,    49,   463,  1017,  1699,  1725,   477,  1717,
     783,  1778,   792,   371,  1786,   692,   820,   941,   793,  1018,
    1726,   371,  1271,   366,    42,   483,   811,   452,   485,   942,
    1710,  1614,  1452,   323,   707,   708,   709,   710,   711,   712,
     713,   714,   715,  1711,   355,   356,  1320,  1712,    44,    39,
    1790,  1700,    40,   903,   357,    41,  1321,   697,   698,   699,
     700,   701,   702,   703,   704,   705,   706,  1791,   720,   721,
     722,   723,   373,   726,  1579,   399,   731,   732,   733,    46,
     420,   423,    45,   457,   465,    47,   459,   472,   537,   334,
     334,   334,   334,   334,   334,   334,   334,   334,   425,  1482,
    1249,   667,   668,   426,   813,  1250,   667,   668,   667,   668,
     427,   667,   668,  1603,  1461,   814,   815,   811,  1758,  1759,
    -275,  -275,  -275,  1438,  1760,  1604,  1619,    50,   676,  1476,
    1477,   667,   668,  1553,    51,   667,   668,  1554,  1620,   355,
     418,    -4,    -4,   431,   435,  1555,   667,   668,   471,   357,
     436,   670,   437,   414,  1841,   438,  1319,   727,   729,    54,
    1842,  1332,   439,    55,  1843,  1284,  1285,   694,   744,   746,
     316,   749,   750,   751,   752,  1378,   317,   279,  1379,   695,
     696,   476,   477,   478,   479,   401,   480,   481,   303,   417,
     769,   771,   304,   482,   451,   320,   306,   785,   787,   483,
     484,   321,   485,   308,  1487,   421,   424,  1033,   305,  1035,
    1488,   460,   473,   557,   558,   559,  1490,  1915,   776,  1963,
     309,  1970,  1491,  1916,  2041,  1964,   570,  1971,   416,   307,
    2042,   804,   571,   450,   572,   573,   574,   575,   576,   795,
     577,   799,   578,   579,   580,   581,   582,   798,   583,   584,
     585,   586,   587,   588,   589,   590,   591,   592,   796,  1399,
     310,   594,  1400,   595,   816,   413,   597,    56,    57,   599,
     600,   447,  1404,   602,   603,  1367,   604,   605,  1108,   819,
     822,   824,   609,   610,   611,   311,   612,   613,   614,   323,
     707,   708,   709,   710,   711,   712,   713,   714,   715,   716,
     619,   312,   620,   621,   622,   313,  1426,   624,   625,  1427,
     626,   627,   628,   629,   560,   561,   615,   561,   633,   634,
     635,   636,   637,   638,   639,   640,   641,   642,   643,   976,
     667,   668,   323,   324,   325,   326,   327,   328,   329,   330,
     331,   332,  1121,  1683,  1684,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   553,   314,   553,   553,   553,
     553,   553,   553,   553,   553,  1448,  1122,   315,  1451,   323,
     324,   325,   326,   327,   328,   329,   330,   331,   332,  1525,
    1705,  1706,  1367,  1334,  1335,   507,   531,   318,   654,   319,
     655,   825,   826,   323,   707,   708,   709,   710,   711,   712,
     713,   714,   715,   408,   410,  1697,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   332,   745,   747,    56,   406,
    1780,   323,   707,   708,   709,   710,   711,   712,   713,   714,
     715,   411,  1001,  1002,  1003,   414,   418,   452,   355,   538,
     540,   539,   541,   542,   543,   544,   545,   547,   546,   548,
     549,   551,   550,   555,   554,   563,   556,   718,   552,   828,
     562,   567,   564,  1512,   566,  1039,  1040,  1041,  1042,   593,
     596,   718,   568,   718,   569,   598,   601,   608,   565,  1054,
     616,  1056,   607,  1058,  1059,  1060,  1061,   606,   759,   760,
     618,   617,   623,   631,   632,   718,   630,   644,  1076,  1077,
    1609,   645,   646,   718,   280,  1084,   647,   648,   649,   650,
     807,   808,   809,   810,   652,   651,   653,   657,   831,   834,
     858,   858,  1322,   660,   656,   658,   661,   776,   662,   863,
     864,   865,   659,   663,   664,   665,   666,   683,   682,  1117,
    1118,  1119,  1120,   684,   686,   688,   877,   878,   879,   880,
     881,   882,   883,   884,   885,   886,   887,   888,   889,   890,
     685,   689,   333,   335,   336,   337,   338,   339,   340,   341,
     342,   690,   691,   892,   893,   894,   895,   692,   734,   896,
     687,   897,   739,   898,   899,   900,   735,   742,   748,   753,
     904,   905,   754,   755,   762,   763,   764,   909,   910,   911,
     912,   765,   914,   915,   916,   917,   773,   788,   789,   921,
     922,   923,   718,   790,   924,   811,   835,   354,   837,   836,
     838,   839,   840,   929,   843,   930,   848,   845,   932,   849,
     933,   844,   934,   850,   851,   854,   853,   860,   852,   936,
     855,   862,   861,   866,   867,   873,   868,   869,   944,   945,
     946,   947,   948,   949,   950,   951,   952,   953,   954,   955,
     956,   957,   958,   959,   830,   961,   828,   870,   871,   965,
     966,   967,   968,   872,   970,   971,   972,   973,   874,   876,
     974,   975,   875,   891,   901,   902,   919,   906,   907,   908,
     913,   918,   920,   925,   926,   927,   928,   937,   960,   939,
     978,   935,   964,   963,   938,   931,   943,   969,   977,   980,
     996,   981,   996,  1253,  1254,  1255,   940,   962,   979,   982,
     983,   984,   986,   987,   985,   989,   988,   990,   991,   334,
     334,   334,   334,   334,   334,   334,   334,   334,   998,   992,
     993,   999,  1000,  1005,  1006,  1007,  1010,  1008,  1009,  1012,
    1013,  1015,  1063,  1014,  1034,  1074,  1046,  1045,  1025,  1087,
    1050,  1028,  1029,  1030,  1031,  1051,   718,  1057,   718,  1062,
    1037,  1283,  1072,  1073,  1011,  1085,  1043,  1044,  1049,  1298,
    1300,  1048,  1078,  1064,  1075,  1083,  1086,  1088,  1089,  1090,
    1109,  1107,  1110,  1111,  1116,  1124,  1125,  1128,  1126,  1069,
    1071,  1127,  1129,  1131,  1132,  1133,  1130,  1298,  1080,  1298,
    1134,  1135,   670,  1136,  1140,  1137,  1138,  1139,  1148,  1141,
    1142,  1349,  1351,  1352,  1351,  1149,  1150,  1147,  1151,  1152,
    1153,  1123,  1154,  1104,  1155,  1106,  1156,   718,  1158,  1157,
    1159,  1169,  1170,  1173,  1174,  1175,  1180,   334,   334,  1183,
    1181,   553,  1182,  1187,  1143,  1144,  1145,  1146,  1188,  1189,
    1190,  1194,  1191,  1196,  1197,  1198,  1199,  1195,  1217,  1219,
    1220,  1221,  1160,  1226,  1200,  1233,  1235,  1242,  1237,  1161,
    1241,  1162,  1163,  1164,  1234,  1165,  1166,  1236,  1238,  1239,
    1167,  1168,  1244,  1240,  1245,  1246,  1248,  1243,  1247,  1257,
    1172,  1256,  1251,  1258,  1260,  1302,  1261,  1178,  1259,  1179,
    1263,  1262,  1264,  1274,  1249,  1279,  1278,  1288,  1184,  1303,
    1184,  1186,  1048,  1250,  1286,  1287,  1289,  1308,  1312,  1301,
    1304,  1305,  1192,  1310,  1193,  1309,  1311,  1342,  1341,  1356,
    1343,  1439,  1348,  1354,  1201,  1202,  1203,  1204,  1205,  1206,
    1207,  1208,  1209,  1210,  1211,  1212,  1357,  1214,  1358,  1216,
    1360,  1218,  1361,  1363,  1364,  1222,  1223,  1224,  1225,  1355,
    1227,  1228,  1229,  1230,  1359,  1365,  1231,  1232,  1362,  1367,
    1366,  1368,  1369,  1370,  1373,  1376,  1283,   828,  1374,  1375,
    1298,  1298,  1381,  1377,  1380,  1382,   553,   553,   334,  1388,
    1390,  1391,  1393,  1394,  1395,  1298,  1298,  1397,  1401,  1405,
    1398,  1403,  1300,  1406,  1408,  1409,  1413,  1414,  1420,  1080,
    1419,  1421,  1422,  1423,  1275,  1425,  1424,  1428,  1429,  1432,
    1436,  1433,  1430,  1431,  1435,  1484,  1441,  1437,  1267,  1268,
    1269,  1434,  1048,  1272,  1071,  1445,  1447,  1499,  1277,  1440,
    1501,  1473,  1475,  1442,  1443,  1444,  1446,  1505,  1453,  1455,
    1459,  1297,  1466,  1456,  1458,  1460,  1463,  1471,  1464,  1080,
    1465,  1468,  1470,  1469,  1474,  1485,  1478,  1314,  1316,  1479,
    1314,   718,  1326,  1328,  1486,  1314,   831,   834,   834,  1297,
    1489,  1297,  1492,   354,   354,  1493,   756,   757,  1071,  1071,
    1071,  1071,  1494,  1495,  1497,  1496,  1498,  1371,  1372,  1500,
    1503,  1508,   780,  1502,  1504,  1506,  1507,   354,  1509,  1383,
    1384,  1510,  1385,  1386,  1387,  1514,  1511,  1513,  1520,  1515,
     833,  1517,  1526,  1516,  1518,  1524,  1534,  1522,  1527,  1519,
    1521,  1533,  1523,   334,   334,   553,   974,   975,  1529,  1530,
    1532,  1277,  1535,  1536,   856,   856,   776,  1537,  1538,  1539,
    1402,  1540,   758,  1543,  1545,   761,  1541,  1542,  1407,  1544,
     354,   768,  1547,  1546,  1548,  1549,  1551,   781,  1550,  1556,
    1559,  1564,  1565,  1552,  1557,  1410,  1558,  1561,  1560,  1607,
    1563,  1566,  1573,   354,  1567,  1580,  1582,  1415,  1416,  1417,
    1418,  1568,  1570,  1569,  1571,   846,   847,   830,  1574,  1572,
    1575,  1577,  1578,  1584,  1581,  1583,  1585,  1586,  1587,  1588,
    1590,  1589,  1593,  1591,  1592,  1594,  1598,  1595,  1596,  1605,
    1599,  1601,   830,  1597,  1600,   830,  1608,   830,  1602,  1610,
    1614,  1611,  1454,  1612,  1606,  1613,  1616,  1080,  1615,  1621,
    1617,  1618,  1622,   553,   553,  1623,  1624,  1625,  1627,  1626,
    1628,  1633,  1629,  1277,  1630,  1631,  1634,  1632,  1637,  1635,
    1639,  1640,  1297,  1297,  1636,  1638,  1642,  1643,  1644,  1645,
    1649,  1648,  1650,  1316,  1651,  1652,  1326,  1297,  1297,  1641,
    1654,  1316,  1069,   831,  1658,  1660,  1655,  1661,  1656,  1663,
    1677,  1184,  1664,  1665,  1184,  1657,  1659,  1668,  1667,  1675,
    1669,  1670,  1662,   334,   334,  1676,  1666,  1678,  1672,  1673,
    1671,  1674,  1681,  1692,  1682,  1685,  1686,  1687,  1528,  1690,
    1691,  1695,   354,  1531,  1693,  1680,  1700,  1694,  1696,  1698,
    1702,  1701,  1704,  1715,   995,  1703,   995,  1708,  1719,  1707,
    1709,  1713,  1714,  1720,  1721,  1718,  1723,  1722,  1727,  1728,
    1724,  1731,  1729,   354,   354,  1562,  1733,  1730,   780,   354,
    1026,  1027,  1732,   354,  1734,  1735,  1032,  1736,  1737,  1739,
    1036,  1740,  1742,  1741,  1743,  1744,  1745,  1747,  1746,  1749,
     354,  1756,  1748,  1751,  1762,  1753,  1053,  1767,  1053,  1752,
    1755,  1761,  1763,   354,  1328,  1764,  1750,  1316,  1066,  1066,
    1766,  1768,  1754,  1863,  1771,  1770,  1772,  1757,   830,   830,
    1765,  1773,  1774,  1775,  1769,  1779,  1777,  1783,  1016,  1781,
    1022,  1023,  1776,   830,   830,  1782,  1784,  1785,  1787,   830,
     354,  1789,   354,  1103,  1788,  1105,  1038,  1792,  1793,  1794,
    1790,  1796,  1797,  1795,  1798,  1800,  1801,  1803,  1799,  1807,
    1802,  1830,  1653,  1804,  1805,  1814,  1806,  1576,  1855,  1846,
    1809,  1811,  1839,  1812,  1821,  1810,  1808,  1813,  1816,  1815,
    1817,  1822,  1820,  1818,  1823,  1082,  1824,  1825,  1827,  1828,
    1829,  1826,  1831,  1832,  1863,  1091,  1092,  1093,  1094,  1095,
    1096,  1097,  1098,  1099,  1100,  1101,  1102,  1833,  1834,  1835,
    1836,  1838,  1837,  1840,  1844,  1845,  1112,  1113,  1114,  1115,
    1847,  1848,  1849,  1851,  1850,  1852,  1853,  1856,  1854,  1080,
    1857,  1868,  1867,  1869,  1870,  1872,  1871,  1874,  1876,  1878,
    1858,  1873,  1877,  1880,  1885,  1886,  1892,  1875,  1879,  1884,
    1738,  1882,  1888,  1889,  1893,  1881,  1883,  1899,  1901,  1912,
    1887,  1481,  1902,  1890,  1903,  1894,  1891,  1897,  1895,  1896,
    1898,  1905,  1906,  1909,  1904,  1908,  1907,  1910,  1911,  1914,
    1918,  1919,  1913,  1921,  1917,  1923,  1924,  1927,  1928,  1920,
    1930,  1931,  1937,  1938,  1922,  1935,  1939,  1925,  1926,  1929,
    1932,  1934,  1941,   354,  1353,  1943,  1944,   354,  1942,  1945,
    1950,  1946,  1948,  1974,   831,  1957,  1933,   354,  1953,   354,
    1954,  1951,  1955,  1959,  1958,  1961,  1960,   354,  1956,  1962,
    1965,  1968,   354,  1819,  1966,  1936,  1967,  1969,  1972,  1973,
    1976,  1975,  1978,  1979,  1977,  1980,  1981,  1982,  1266,  1983,
    1984,  1985,  1270,  1988,  1995,   354,  1940,  1986,  1987,  1990,
    1993,  1989,  2007,  1280,  1282,  1053,  1053,  1991,   354,  1947,
    1949,  1290,  1952,  1992,   354,  1994,   354,  1996,  1998,  2000,
    2002,  2001,  2003,  1999,  1997,  2005,  2004,  2009,  2008,  2010,
    1318,  2006,  2011,  2012,  2013,  1331,  2014,  2015,   833,   833,
    2016,  1337,  2017,  1339,  2018,  2019,  2020,  2022,  2021,  2023,
    2024,  1265,  2029,  2025,  1900,  2027,  2030,  2028,  1340,  2037,
    1483,  1462,  2026,  2049,  2036,  2031,  2045,  2047,  2033,  2038,
    2032,  2035,  2034,  2044,  2046,  2039,  2048,  2040,  2043,  2051,
    2050,  2052,  2053,  1306,  2054,  2055,  2057,  2058,  2056,  2060,
    2059,  2065,  2067,  2061,  2068,  2062,  2063,  2071,  2064,  2066,
     830,  2069,  2070,  2073,  2072,  2074,  2079,  2083,  1457,  2075,
    2077,  2076,   535,  2082,  2078,  2080,  1004,  2081,   859,   511,
     512,   441,   322,   513,     0,   467,   354,   354,   442,   443,
       0,     0,     0,   800,     0,   514,     0,   515,   516,     0,
       0,   517,   823,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1066,  1449,  1450,  1066,     0,     0,     0,     0,     0,  1282,
       0,     0,     0,     0,     0,     0,     0,     0,   518,     0,
       0,     0,     0,     0,     0,     0,   519,     0,     0,     0,
     520,     0,     0,     0,   521,     0,     0,     0,     0,   522,
     523,     0,   524,   525,   526,   527,   532,   533,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   455,     0,   444,   469,     0,     0,     0,     0,
       0,   780,   445,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   446,  1467,   343,    61,    62,    63,    64,    65,
     344,   345,   346,   347,   348,   349,   350,   351,   352,   353,
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
     276,   277,   278,   994,   448,   279,   343,    61,    62,    63,
      64,    65,   344,   345,   346,   347,   348,   349,   350,   351,
     352,   353,    76,    77,    78,    79,    80,    81,    82,    83,
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
     274,   275,   276,   277,   278,   449,   997,   279,    60,    61,
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
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,     0,     0,   279,
     343,    61,    62,    63,    64,    65,   344,   345,   346,   347,
     348,   349,   350,   351,   352,   353,    76,    77,    78,    79,
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
     270,   271,   272,   273,   274,   275,   276,   277,   278,     0,
       0,   279,   343,    61,    62,    63,    64,    65,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,    76,    77,
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
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   667,   668,   343,    61,    62,    63,  1291,  1292,    66,
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
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   667,   668,   343,    61,    62,    63,    64,    65,
     344,   345,   346,   347,   348,   349,   350,   351,   352,   353,
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
     276,   277,   278,   343,    61,    62,    63,    64,    65,    66,
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
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   343,  1177,    62,    63,    64,    65,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,    76,    77,
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
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   343,  1185,    62,    63,    64,    65,   344,   345,   346,
     347,   348,   349,   350,   351,   352,   353,    76,    77,    78,
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
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     343,  1213,    62,    63,    64,    65,   344,   345,   346,   347,
     348,   349,   350,   351,   352,   353,    76,    77,    78,    79,
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
     270,   271,   272,   273,   274,   275,   276,   277,   278,   343,
    1215,    62,    63,    64,    65,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,    76,    77,    78,    79,    80,
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
     271,   272,   273,   274,   275,   276,   277,   278,   343,  1392,
      62,    63,    64,    65,   344,   345,   346,   347,   348,   349,
     350,   351,   352,   353,    76,    77,    78,    79,    80,    81,
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
     272,   273,   274,   275,   276,   277,   278,   343,  1396,    62,
      63,    64,    65,   344,   345,   346,   347,   348,   349,   350,
     351,   352,   353,    76,    77,    78,    79,    80,    81,    82,
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
     273,   274,   275,   276,   277,   278,   343,  1411,    62,    63,
      64,    65,   344,   345,   346,   347,   348,   349,   350,   351,
     352,   353,    76,    77,    78,    79,    80,    81,    82,    83,
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
     274,   275,   276,   277,   278,   343,  1412,    62,    63,    64,
      65,   344,   345,   346,   347,   348,   349,   350,   351,   352,
     353,    76,    77,    78,    79,    80,    81,    82,    83,    84,
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
     275,   276,   277,   278
};

static const yytype_int16 yycheck[] =
{
      17,   933,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
     881,   642,  1210,    17,   286,  1143,   298,   300,   911,   293,
     294,     5,  1046,    24,   922,   297,   298,   293,   294,   300,
     300,    32,   595,    24,   597,    36,    32,     1,    32,     3,
    1275,  1168,    67,    68,    69,    70,    71,    72,    73,    74,
      75,  1213,    37,  1215,    37,    19,   619,    21,    22,    23,
      24,    25,    33,    34,   627,  1193,    30,    31,    24,    36,
    1407,    35,    36,    37,    37,    39,    32,    37,  1415,    37,
      36,   594,    37,    23,   581,   588,   589,    22,    22,    19,
      23,    21,    22,    23,    24,  1222,  1223,  1224,  1225,    39,
     597,    31,    37,    36,    89,    27,    89,    37,    38,    19,
      40,   624,    19,    22,    21,    22,    23,    24,   621,   622,
      19,    43,   619,    33,    31,    20,    89,    23,    20,    89,
     627,    89,    31,    40,    89,    27,    22,    27,    37,    34,
      36,    40,  1166,    23,    23,    37,    32,    27,    40,    39,
      21,    22,  1387,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    34,    21,    22,    22,    38,    27,    30,
      21,    22,    33,   736,    31,    36,    32,   571,   572,   573,
     574,   575,   576,   577,   578,   579,   580,    38,   582,   583,
     584,   585,   286,   587,  1531,   286,   590,   591,   592,    27,
     291,   292,    23,   297,   298,    33,   297,   298,   302,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    19,  1417,
      31,   222,   223,    24,    19,    36,   222,   223,   222,   223,
      31,   222,   223,    22,  1396,    30,    31,    32,    21,    22,
     224,   225,   226,  1371,    27,    34,    22,    39,   559,  1411,
    1412,   222,   223,    19,    23,   222,   223,    23,    34,    21,
      22,   225,   226,   293,   294,    31,   222,   223,   298,    31,
      19,   557,    21,    22,    21,    24,  1204,   588,   589,    32,
      27,  1209,    31,     0,    31,  1178,  1179,   570,   599,   600,
      31,   602,   603,   604,   605,    34,    37,   224,    37,   570,
     570,    19,    20,    21,    22,   286,    24,    25,    22,   290,
     621,   622,    23,    31,   295,    31,    23,   628,   629,    37,
      38,    37,    40,    27,    21,   291,   292,   890,    34,   892,
      27,   297,   298,   360,   361,   362,    21,    21,   624,    21,
      32,    21,    27,    27,    21,    27,   373,    27,   290,    37,
      27,   633,   379,   295,   381,   382,   383,   384,   385,   633,
     387,   633,   389,   390,   391,   392,   393,   633,   395,   396,
     397,   398,   399,   400,   401,   402,   403,   404,   633,    34,
      38,   408,    37,   410,   639,   289,   413,   225,   226,   416,
     417,   295,    34,   420,   421,    37,   423,   424,   961,   639,
     640,   641,   429,   430,   431,    37,   433,   434,   435,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
     447,    19,   449,   450,   451,    34,    34,   454,   455,    37,
     457,   458,   459,   460,    39,    40,    39,    40,   465,   466,
     467,   468,   469,   470,   471,   472,   473,   474,   475,     6,
     222,   223,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,     6,    21,    22,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,   333,    40,   335,   336,   337,
     338,   339,   340,   341,   342,  1383,     6,    27,  1386,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    34,
      21,    22,    37,  1211,  1212,   299,   300,    38,   535,    20,
     537,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,   287,   288,  1653,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,   599,   600,   225,    31,
    1738,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    31,   863,   864,   865,    22,    22,    27,    21,    19,
      19,    43,    38,    38,    22,    38,    22,    38,    23,    33,
      23,    19,    37,    20,    26,    20,    27,   581,    39,  1210,
      26,    23,    32,  1454,    27,   896,   897,   898,   899,    27,
      27,   595,    33,   597,    33,    20,    20,    27,    42,   910,
      26,   912,    42,   914,   915,   916,   917,    39,   612,   613,
      27,    42,    32,    21,    27,   619,    39,    39,   929,   930,
    1562,    39,    26,   627,    17,   936,    20,    42,    30,    27,
     634,   635,   636,   637,    33,    38,    33,    38,   642,   643,
     667,   668,  1205,    38,    36,    36,    21,   933,    34,   676,
     677,   678,    40,    20,    19,    89,    22,    19,    22,   970,
     971,   972,   973,    19,    25,    22,   693,   694,   695,   696,
     697,   698,   699,   700,   701,   702,   703,   704,   705,   706,
      89,    36,   707,   708,   709,   710,   711,   712,   713,   714,
     715,    38,    30,   720,   721,   722,   723,    27,    22,   726,
      89,   728,    22,   730,   731,   732,    32,    89,    89,    22,
     737,   738,    89,    22,    22,    19,    89,   744,   745,   746,
     747,    22,   749,   750,   751,   752,    37,    22,    26,   756,
     757,   758,   736,    22,   761,    32,    22,   280,    19,    24,
      89,    89,    33,   770,    36,   772,    23,    27,   775,    33,
     777,    38,   779,    23,    36,    27,    32,    30,    37,   786,
      27,    23,    33,    27,    27,    40,    32,    27,   795,   796,
     797,   798,   799,   800,   801,   802,   803,   804,   805,   806,
     807,   808,   809,   810,   642,   812,  1417,    27,    37,   816,
     817,   818,   819,    27,   821,   822,   823,   824,    19,    32,
     825,   826,    39,    30,    27,    33,    37,    27,    27,    33,
      27,    27,    27,    27,    32,    37,    27,    27,    19,    27,
      24,    33,    27,    23,    33,    38,    33,    23,    27,    27,
     857,    37,   859,  1144,  1145,  1146,    39,    39,    32,    20,
      27,    21,    19,    21,    23,    27,    43,    21,    32,   707,
     708,   709,   710,   711,   712,   713,   714,   715,    19,    32,
      89,    32,    21,    33,    30,    32,    23,    32,    32,    23,
      30,    24,    23,    31,    30,    23,   903,    32,   882,    22,
      32,   885,   886,   887,   888,    32,   890,    32,   892,    33,
     894,  1177,    33,    32,    89,    33,   900,    89,    89,  1185,
    1186,   905,    36,    89,    89,    36,    89,    22,    38,    30,
      22,    31,    40,    22,    37,    33,    23,    23,    32,   923,
     924,    32,    19,    23,    19,    30,    89,  1213,   932,  1215,
      23,    20,  1218,    36,    38,    23,    37,    27,    19,    89,
      39,  1227,  1228,  1229,  1230,    23,    37,    89,    23,    32,
      27,   976,    36,   957,    89,   959,    23,   961,    43,    33,
      23,    27,    89,    27,    37,    89,    37,   825,   826,    27,
      89,   829,    32,    89,  1001,  1002,  1003,  1004,    23,    32,
      27,    21,    39,    27,    27,    27,    23,    89,    23,    27,
      23,    27,  1019,    21,    33,    89,    23,    89,    32,  1026,
      31,  1028,  1029,  1030,    36,  1032,  1033,    37,    30,    27,
    1037,  1038,    23,    30,    27,    30,    32,    89,    38,    20,
    1047,    33,    36,    30,    22,    30,    32,  1054,    38,  1056,
      38,    40,    36,    32,    31,    38,    32,    22,  1065,    22,
    1067,  1068,  1046,    36,    38,    33,    32,    23,    89,    33,
      32,    31,  1079,    32,  1081,    33,    33,    30,    33,    30,
      89,  1372,    36,    33,  1091,  1092,  1093,  1094,  1095,  1096,
    1097,  1098,  1099,  1100,  1101,  1102,    38,  1104,    22,  1106,
      32,  1108,    30,    40,    21,  1112,  1113,  1114,  1115,    89,
    1117,  1118,  1119,  1120,    89,    20,  1121,  1122,    89,    37,
      36,    33,    23,    37,    39,    36,  1392,  1738,    30,    37,
    1396,  1397,    23,    37,    33,    21,   974,   975,   976,    37,
      37,    36,    36,    39,    34,  1411,  1412,     5,    23,    89,
      39,    39,  1418,    27,    23,    33,    89,    21,    39,  1143,
      27,    24,    89,    36,  1171,    27,    89,    19,    21,    23,
      21,    39,    33,    33,    22,    34,    23,    27,  1162,  1163,
    1164,    38,  1166,  1167,  1168,    27,    23,    31,  1172,    38,
      19,    24,  1410,    39,    39,    38,    37,    89,    38,    38,
      38,  1185,    32,    39,    39,    39,    38,    32,    39,  1193,
      38,    38,    33,    39,    32,    38,    33,  1201,  1202,    33,
    1204,  1205,  1206,  1207,    27,  1209,  1210,  1211,  1212,  1213,
      39,  1215,    32,   756,   757,    39,   609,   610,  1222,  1223,
    1224,  1225,    38,    32,    27,    33,    39,  1254,  1255,    36,
      40,    36,   625,    39,    34,    31,    38,   780,    21,  1266,
    1267,    32,  1269,  1270,  1271,    31,    36,    36,    36,    31,
     643,    38,    19,    34,    34,    39,    30,    34,    23,    38,
      38,    34,    38,  1121,  1122,  1123,  1291,  1292,    39,    32,
      38,  1275,    33,    32,   667,   668,  1562,    31,    33,    32,
    1307,    24,   611,    23,    21,   614,    38,    36,  1315,    39,
     833,   620,    23,    32,    39,    30,    23,   626,    36,    23,
      23,    23,    23,    39,    89,  1332,    39,    39,    38,    19,
      39,    39,    38,   856,    89,    27,    30,  1344,  1345,  1346,
    1347,    39,    39,    89,    39,   654,   655,  1185,    39,    89,
      39,    38,    38,    24,    39,    39,    23,    39,    24,    33,
      39,    89,    23,    33,    32,    38,    38,    32,    31,    31,
      39,    27,  1210,    37,    32,  1213,    31,  1215,    32,    31,
      22,    32,  1389,    32,    89,    38,    22,  1371,    38,    34,
      31,    38,    38,  1231,  1232,    30,    34,    36,    38,    33,
      32,    22,    33,  1387,    32,    32,    31,    33,    89,    39,
      23,    27,  1396,  1397,    38,    38,    22,    25,    22,    38,
      23,    33,    21,  1407,    25,    23,  1410,  1411,  1412,    89,
      23,  1415,  1416,  1417,    23,    23,    38,    23,    38,    23,
      37,  1448,    33,    39,  1451,    89,    89,    39,    38,    23,
      33,    32,    89,  1291,  1292,    23,    89,    21,    38,    38,
      89,    38,    32,    36,    40,    27,    27,    27,  1475,    40,
      27,    23,   995,  1480,    32,    89,    22,    33,    32,    32,
      22,    40,    32,    22,   857,    40,   859,    36,    32,    40,
      38,    38,    30,    33,    22,    40,    23,    38,    33,    32,
      26,    22,    89,  1026,  1027,  1512,    40,    89,   881,  1032,
     883,   884,    27,  1036,    38,    38,   889,    39,    38,    38,
     893,    22,    27,    23,    23,    27,    38,    23,    26,    38,
    1053,    23,    27,    26,    38,    43,   909,    40,   911,    33,
      30,    27,    39,  1066,  1528,    27,    89,  1531,   921,   922,
      19,    27,    89,  1819,    27,    23,    28,    89,  1396,  1397,
      89,    27,    21,    23,    89,    32,    37,    21,   877,    27,
     879,   880,    89,  1411,  1412,    40,    40,    21,    19,  1417,
    1103,    21,  1105,   956,    40,   958,   895,    19,    36,    34,
      21,    40,    28,    23,    33,    32,    21,    32,    27,    27,
      89,    43,  1609,    36,    31,    23,    32,  1528,    89,    19,
      33,    32,    24,    33,    27,    37,    40,    36,    34,    36,
      31,    23,    36,    38,    27,   934,    23,    31,    27,    23,
      26,    32,    32,    38,  1900,   944,   945,   946,   947,   948,
     949,   950,   951,   952,   953,   954,   955,    23,    36,    27,
      33,    36,    39,    23,    38,    23,   965,   966,   967,   968,
      32,    21,    23,    34,    39,    20,    23,    19,    37,  1653,
      19,    21,    23,    21,    19,    21,    32,    19,    32,    20,
      89,    89,    21,    23,    19,    21,    39,    34,    32,    32,
    1697,    89,    23,    23,    21,    33,    33,    23,    21,    89,
      34,  1416,    23,    36,    23,    34,    38,    31,    36,    34,
      32,    23,    23,    23,    34,    32,    34,    23,    23,    21,
      24,    34,    38,    30,    39,    89,    34,    19,    19,    38,
      19,    89,    19,    32,    37,    30,    30,    38,    38,    37,
      36,    38,    27,  1266,  1230,    33,    32,  1270,    38,    32,
      34,    33,    33,    19,  1738,    22,  1900,  1280,    33,  1282,
      36,    39,    31,    33,    37,    36,    34,  1290,    42,    23,
      32,    24,  1295,  1780,    33,    89,    39,    38,    36,    34,
      22,    38,    19,    23,    36,    23,    27,    36,  1161,    19,
      19,    30,  1165,    24,    19,  1318,    89,    33,    32,    32,
      32,    36,    24,  1176,  1177,  1178,  1179,    33,  1331,    89,
      89,  1184,    89,    33,  1337,    43,  1339,    36,    36,    31,
      31,    38,    37,    27,    89,    31,    36,    43,    33,    38,
    1203,    39,    39,    24,    36,  1208,    19,    22,  1211,  1212,
      27,  1214,    23,  1216,    23,    23,    19,    19,    38,    23,
      32,  1160,    19,    33,  1861,    32,    31,    33,  1218,    23,
    1418,  1397,    89,    22,    32,    36,    23,    23,    37,    31,
      40,    36,    38,    31,    27,    38,    23,    38,    38,    23,
      32,    23,    33,  1192,    32,    23,    40,    36,    38,    89,
      36,    24,    23,    38,    23,    38,    36,    23,    39,    38,
    1738,    37,    26,    33,    32,    23,    38,    22,  1392,    36,
      33,    36,   301,    30,    36,    36,   865,    37,   668,   300,
     300,   295,    59,   300,    -1,   298,  1449,  1450,   295,   295,
      -1,    -1,    -1,   633,    -1,   300,    -1,   300,   300,    -1,
      -1,   300,   641,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1383,  1384,  1385,  1386,    -1,    -1,    -1,    -1,    -1,  1392,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   300,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   300,    -1,    -1,    -1,
     300,    -1,    -1,    -1,   300,    -1,    -1,    -1,    -1,   300,
     300,    -1,   300,   300,   300,   300,   300,   300,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   296,    -1,   295,   298,    -1,    -1,    -1,    -1,
      -1,  1454,   295,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   295,  1402,     3,     4,     5,     6,     7,     8,
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
     219,   220,   221,   222,   295,   224,     3,     4,     5,     6,
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
     217,   218,   219,   220,   221,   295,   223,   224,     3,     4,
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
     213,   214,   215,   216,   217,   218,   219,   220,   221,    -1,
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
     218,   219,   220,   221
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     1,     3,    19,    21,    22,    23,    24,    25,    30,
      31,    35,    36,    37,    39,   228,   229,   230,   231,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   311,   312,   313,   314,   391,   392,   396,    22,    30,
      33,    36,    23,    22,    27,    23,    27,    33,    19,    33,
      39,    23,    23,    39,    32,     0,   225,   226,   293,   294,
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
     213,   214,   215,   216,   217,   218,   219,   220,   221,   224,
     284,   287,   288,   289,   292,   292,   292,   292,   292,   292,
     292,   292,   292,   292,   292,   292,   292,   292,   292,   292,
     292,   292,   292,    22,    23,    34,    23,    37,    27,    32,
      38,    37,    19,    34,    40,    27,    31,    37,    38,    20,
      31,    37,   293,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,   286,   287,   286,   286,   286,   286,   286,
     286,   286,   286,     3,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,   289,    21,    22,    31,   232,   315,
     364,   374,   376,    19,    21,    22,    23,    24,    31,    37,
      38,    40,   238,   315,   316,   317,   318,   340,   341,   344,
     349,   350,   351,   352,   353,   354,   356,   358,   359,   360,
     361,   362,   363,   364,   365,   366,   367,   372,   373,   374,
     375,   376,   377,   378,   384,   385,    31,   235,   362,   236,
     362,    31,   242,   363,    22,   243,   375,   376,    22,   244,
     374,   377,   245,   374,   377,    19,    24,    31,   240,   350,
     360,   372,   246,   350,   360,   372,    19,    21,    24,    31,
     253,   316,   317,   318,   349,   356,   359,   363,   365,   373,
     375,   376,    27,   247,   343,   344,   237,   315,   364,   374,
     377,    19,    23,    31,   239,   315,   348,   353,   357,   358,
     364,   372,   374,   377,   385,   395,    19,    20,    21,    22,
      24,    25,    31,    37,    38,    40,   233,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,   334,   335,   336,   337,   338,   339,   340,   342,   393,
     234,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,   340,   342,   393,   249,   343,   241,   315,    19,    43,
      19,    38,    38,    22,    38,    22,    23,    38,    33,    23,
      37,    19,    39,   287,    26,    20,    27,   292,   292,   292,
      39,    40,    26,    20,    32,    42,    27,    23,    33,    33,
     292,   292,   292,   292,   292,   292,   292,   292,   292,   292,
     292,   292,   292,   292,   292,   292,   292,   292,   292,   292,
     292,   292,   292,    27,   292,   292,    27,   292,    20,   292,
     292,    20,   292,   292,   292,   292,    39,    42,    27,   292,
     292,   292,   292,   292,   292,    39,    26,    42,    27,   292,
     292,   292,   292,    32,   292,   292,   292,   292,   292,   292,
      39,    21,    27,   292,   292,   292,   292,   292,   292,   292,
     292,   292,   292,   292,    39,    39,    26,    20,    42,    30,
      27,    38,    33,    33,   292,   292,    36,    38,    36,    40,
      38,    21,    34,    20,    19,    89,    22,   222,   223,   275,
     291,   272,   291,    24,    32,    36,   272,   282,   310,   381,
     382,   383,    22,    19,    19,    89,    25,    89,    22,    36,
      38,    30,    27,   319,   337,   338,   339,   319,   319,   319,
     319,   319,   319,   319,   319,   319,   319,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,   263,   288,   307,
     319,   319,   319,   319,   268,   288,   319,   272,   382,   272,
     382,   319,   319,   319,    22,    32,   250,   310,   263,    22,
     263,   307,    89,    32,   272,   383,   272,   383,    89,   272,
     272,   272,   272,    22,    89,    22,   284,   284,   268,   288,
     288,   268,    22,    19,    89,    22,   263,   307,   268,   272,
     382,   272,   382,    37,   254,   274,   291,   310,   255,   271,
     284,   268,   263,   307,    24,   272,   380,   272,    22,    26,
      22,    19,    31,    37,   248,   350,   354,   355,   360,   364,
     367,   368,   369,   370,   385,   387,   388,   288,   288,   288,
     288,    32,   394,    19,    30,    31,   354,   371,   386,   394,
      22,   379,   394,   379,   394,     7,     8,   267,   285,   286,
     287,   288,   283,   284,   288,    22,    24,    19,    89,    89,
      33,    22,    37,    36,    38,    27,   268,   268,    23,    33,
      23,    36,    37,    32,    27,    27,   284,   290,   292,   290,
      30,    33,    23,   292,   292,   292,    27,    27,    32,    27,
      27,    37,    27,    40,    19,    39,    32,   292,   292,   292,
     292,   292,   292,   292,   292,   292,   292,   292,   292,   292,
     292,    30,   292,   292,   292,   292,   292,   292,   292,   292,
     292,    27,    33,   263,   292,   292,    27,    27,    33,   292,
     292,   292,   292,    27,   292,   292,   292,   292,    27,    37,
      27,   292,   292,   292,   292,    27,    32,    37,    27,   292,
     292,    38,   292,   292,   292,    33,   292,    27,    33,    27,
      39,    27,    39,    33,   292,   292,   292,   292,   292,   292,
     292,   292,   292,   292,   292,   292,   292,   292,   292,   292,
      19,   292,    39,    23,    27,   292,   292,   292,   292,    23,
     292,   292,   292,   292,   286,   286,     6,    27,    24,    32,
      27,    37,    20,    27,    21,    23,    19,    21,    43,    27,
      21,    32,    32,    89,   222,   284,   292,   223,    19,    32,
      21,   272,   272,   272,   282,    33,    30,    32,    32,    32,
      23,    89,    23,    30,    31,    24,   268,    20,    34,   252,
     389,   390,   268,   268,   271,   288,   284,   284,   288,   288,
     288,   288,   284,   263,    30,   263,   284,   288,   268,   272,
     272,   272,   272,   288,    89,    32,   292,   264,   288,    89,
      32,    32,   280,   284,   272,   280,   272,    32,   272,   272,
     272,   272,    33,    23,    89,   251,   284,   251,   266,   288,
     270,   288,    33,    32,    23,    89,   272,   272,    36,   269,
     288,   274,   268,    36,   272,    33,    89,    22,    22,    38,
      30,   268,   268,   268,   268,   268,   268,   268,   268,   268,
     268,   268,   268,   284,   288,   284,   288,    31,   263,    22,
      40,    22,   268,   268,   268,   268,    37,   272,   272,   272,
     272,     6,     6,   286,    33,    23,    32,    32,    23,    19,
      89,    23,    19,    30,    23,    20,    36,    23,    37,    27,
      38,    89,    39,   292,   292,   292,   292,    89,    19,    23,
      37,    23,    32,    27,    36,    89,    23,    33,    43,    23,
     292,   292,   292,   292,   292,   292,   292,   292,   292,    27,
      89,   264,   292,    27,    37,    89,   292,     4,   292,   292,
      37,    89,    32,    27,   292,     4,   292,    89,    23,    32,
      27,    39,   292,   292,    21,    89,    27,    27,    27,    23,
      33,   292,   292,   292,   292,   292,   292,   292,   292,   292,
     292,   292,   292,     4,   292,     4,   292,    23,   292,    27,
      23,    27,   292,   292,   292,   292,    21,   292,   292,   292,
     292,   286,   286,    89,    36,    23,    37,    32,    30,    27,
      30,    31,    89,    89,    23,    27,    30,    38,    32,    31,
      36,    36,   269,   272,   272,   272,    33,    20,    30,    38,
      22,    32,    40,    38,    36,   268,   284,   288,   288,   288,
     284,   264,   288,   270,    32,   292,   265,   288,    32,    38,
     284,   281,   284,   291,   280,   280,    38,    33,    22,    32,
     284,     7,     8,   278,   279,   284,   285,   288,   291,   277,
     291,    33,    30,    22,    32,    31,   268,   269,    23,    33,
      32,    33,    89,   257,   288,   258,   288,   259,   284,   257,
      22,    32,   263,   308,   309,   260,   288,   261,   288,   307,
     262,   284,   257,   267,   283,   283,   278,   284,   278,   284,
     275,    33,    30,    89,   270,   270,   270,   270,    36,   291,
     273,   291,   291,   273,    33,    89,    30,    38,    22,    89,
      32,    30,    89,    40,    21,    20,    36,    37,    33,    23,
      37,   292,   292,    39,    30,    37,    36,    37,    34,    37,
      33,    23,    21,   292,   292,   292,   292,   292,    37,   265,
      37,    36,     4,    36,    39,    34,     4,     5,    39,    34,
      37,    23,   292,    39,    34,    89,    27,   292,    23,    33,
     292,     4,     4,    89,    21,   292,   292,   292,   292,    27,
      39,    24,    89,    36,    89,    27,    34,    37,    19,    21,
      33,    33,    23,    39,    38,    22,    21,    27,   269,   272,
      38,    23,    39,    39,    38,    27,    37,    23,   251,   284,
     284,   251,   265,    38,   292,    38,    39,   281,    39,    38,
      39,   278,   279,    38,    39,    38,    32,   268,    38,    39,
      33,    32,   258,    24,    32,   260,   278,   278,    33,    33,
     258,   266,   267,   277,    34,    38,    27,    21,    27,    39,
      21,    27,    32,    39,    38,    32,    33,    27,    39,    31,
      36,    19,    39,    40,    34,    89,    31,    38,    36,    21,
      32,    36,   271,    36,    31,    31,    34,    38,    34,    38,
      36,    38,    34,    38,    39,    34,    19,    23,   292,    39,
      32,   292,    38,    34,    30,    33,    32,    31,    33,    32,
      24,    38,    36,    23,    39,    21,    32,    23,    39,    30,
      36,    23,    39,    19,    23,    31,    23,    89,    39,    23,
      38,    39,   292,    39,    23,    23,    39,    89,    39,    89,
      39,    39,    89,    38,    39,    39,   261,    38,    38,   258,
      27,    39,    30,    39,    24,    23,    39,    24,    33,    89,
      39,    33,    32,    23,    38,    32,    31,    37,    38,    39,
      32,    27,    32,    22,    34,    31,    89,    19,    31,   274,
      31,    32,    32,    38,    22,    38,    22,    31,    38,    22,
      34,    34,    38,    30,    34,    36,    33,    38,    32,    33,
      32,    32,    33,    22,    31,    39,    38,    89,    38,    23,
      27,    89,    22,    25,    22,    38,    23,    36,    33,    23,
      21,    25,    23,   292,    23,    38,    38,    89,    23,    89,
      23,    23,    89,    23,    33,    39,    89,    38,    39,    33,
      32,    89,    38,    38,    38,    23,    23,    37,    21,    37,
      89,    32,    40,    21,    22,    27,    27,    27,    37,    89,
      40,    27,    36,    32,    33,    23,    32,   269,    32,    89,
      22,    40,    22,    40,    32,    21,    22,    40,    36,    38,
      21,    34,    38,    38,    30,    22,    37,    89,    40,    32,
      33,    22,    38,    23,    26,    23,    36,    33,    32,    89,
      89,    22,    27,    40,    38,    38,    39,    38,   292,    38,
      22,    23,    27,    23,    27,    38,    26,    23,    27,    38,
      89,    26,    33,    43,    89,    30,    23,    89,    21,    22,
      27,    27,    38,    39,    27,    89,    19,    40,    27,    89,
      23,    27,    28,    27,    21,    23,    89,    37,    89,    32,
     267,    27,    40,    21,    40,    21,    89,    19,    40,    21,
      21,    38,    19,    36,    34,    23,    40,    28,    33,    27,
      32,    21,    89,    32,    36,    31,    32,    27,    40,    33,
      37,    32,    33,    36,    23,    36,    34,    31,    38,   292,
      36,    27,    23,    27,    23,    31,    32,    27,    23,    26,
      43,    32,    38,    23,    36,    27,    33,    39,    36,    24,
      23,    21,    27,    31,    38,    23,    19,    32,    21,    23,
      39,    34,    20,    23,    37,    89,    19,    19,    89,    33,
      34,   256,   276,   291,   345,   346,   347,    23,    21,    21,
      19,    32,    21,    89,    19,    34,    32,    21,    20,    32,
      23,    33,    89,    33,    32,    19,    21,    34,    23,    23,
      36,    38,    39,    21,    34,    36,    34,    31,    32,    23,
     292,    21,    23,    23,    34,    23,    23,    34,    32,    23,
      23,    23,    89,    38,    21,    21,    27,    39,    24,    34,
      38,    30,    37,    89,    34,    38,    38,    19,    19,    37,
      19,    89,    36,   276,    38,    30,    89,    19,    32,    30,
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
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                }
    break;

  case 31:
#line 132 "lscp.y"
    { (yyval.String) = LSCPSERVER->ResetSampler();                        }
    break;

  case 32:
#line 133 "lscp.y"
    { LSCPSERVER->AnswerClient("Bye!\r\n"); return LSCP_QUIT; }
    break;

  case 33:
#line 136 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddChannel();                          }
    break;

  case 34:
#line 137 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddDbInstrumentDirectory((yyvsp[(3) - (3)].String));          }
    break;

  case 35:
#line 138 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddDbInstruments((yyvsp[(5) - (9)].String),(yyvsp[(7) - (9)].String),(yyvsp[(9) - (9)].String), true);  }
    break;

  case 36:
#line 139 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddDbInstruments((yyvsp[(3) - (7)].String),(yyvsp[(5) - (7)].String),(yyvsp[(7) - (7)].String));        }
    break;

  case 37:
#line 140 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddDbInstruments((yyvsp[(5) - (7)].String),(yyvsp[(7) - (7)].String), -1, true); }
    break;

  case 38:
#line 141 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddDbInstruments((yyvsp[(5) - (9)].String),(yyvsp[(7) - (9)].String),(yyvsp[(9) - (9)].Number), true);  }
    break;

  case 39:
#line 142 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddDbInstruments((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].String));           }
    break;

  case 40:
#line 143 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddDbInstruments((yyvsp[(3) - (7)].String),(yyvsp[(5) - (7)].String),(yyvsp[(7) - (7)].Number));        }
    break;

  case 41:
#line 144 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddMidiInstrumentMap();                }
    break;

  case 42:
#line 145 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddMidiInstrumentMap((yyvsp[(3) - (3)].String));              }
    break;

  case 43:
#line 148 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_audio_device_count);   }
    break;

  case 44:
#line 149 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_audio_device_info);    }
    break;

  case 45:
#line 150 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_device_count);    }
    break;

  case 46:
#line 151 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_device_info);     }
    break;

  case 47:
#line 152 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_channel_count);        }
    break;

  case 48:
#line 153 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_voice_count);          }
    break;

  case 49:
#line 154 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_stream_count);         }
    break;

  case 50:
#line 155 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_buffer_fill);          }
    break;

  case 51:
#line 156 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_channel_info);         }
    break;

  case 52:
#line 157 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_fx_send_count);        }
    break;

  case 53:
#line 158 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_fx_send_info);         }
    break;

  case 54:
#line 159 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_instr_map_count); }
    break;

  case 55:
#line 160 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_instr_map_info);  }
    break;

  case 56:
#line 161 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_instr_count);     }
    break;

  case 57:
#line 162 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_instr_info);      }
    break;

  case 58:
#line 163 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_db_instr_dir_count);   }
    break;

  case 59:
#line 164 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_db_instr_dir_info);    }
    break;

  case 60:
#line 165 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_db_instr_count);       }
    break;

  case 61:
#line 166 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_db_instr_info);        }
    break;

  case 62:
#line 167 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_db_instrs_job_info);   }
    break;

  case 63:
#line 168 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_misc);                 }
    break;

  case 64:
#line 169 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_total_voice_count);    }
    break;

  case 65:
#line 170 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_global_info);          }
    break;

  case 66:
#line 173 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_audio_device_count);   }
    break;

  case 67:
#line 174 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_audio_device_info);    }
    break;

  case 68:
#line 175 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_device_count);    }
    break;

  case 69:
#line 176 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_device_info);     }
    break;

  case 70:
#line 177 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_channel_count);        }
    break;

  case 71:
#line 178 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_voice_count);          }
    break;

  case 72:
#line 179 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_stream_count);         }
    break;

  case 73:
#line 180 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_buffer_fill);          }
    break;

  case 74:
#line 181 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_channel_info);         }
    break;

  case 75:
#line 182 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_fx_send_count);        }
    break;

  case 76:
#line 183 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_fx_send_info);         }
    break;

  case 77:
#line 184 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_instr_map_count); }
    break;

  case 78:
#line 185 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_instr_map_info);  }
    break;

  case 79:
#line 186 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_instr_count);     }
    break;

  case 80:
#line 187 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_instr_info);      }
    break;

  case 81:
#line 188 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_db_instr_dir_count);   }
    break;

  case 82:
#line 189 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_db_instr_dir_info);    }
    break;

  case 83:
#line 190 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_db_instr_count);       }
    break;

  case 84:
#line 191 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_db_instr_info);        }
    break;

  case 85:
#line 192 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_db_instrs_job_info);   }
    break;

  case 86:
#line 193 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_misc);                 }
    break;

  case 87:
#line 194 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_total_voice_count);    }
    break;

  case 88:
#line 195 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_global_info);          }
    break;

  case 89:
#line 198 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping((yyvsp[(4) - (16)].Number),(yyvsp[(6) - (16)].Number),(yyvsp[(8) - (16)].Number),(yyvsp[(10) - (16)].String),(yyvsp[(12) - (16)].String),(yyvsp[(14) - (16)].Number),(yyvsp[(16) - (16)].Dotnum),MidiInstrumentMapper::VOID,"",(yyvsp[(3) - (16)].Bool)); }
    break;

  case 90:
#line 199 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping((yyvsp[(4) - (18)].Number),(yyvsp[(6) - (18)].Number),(yyvsp[(8) - (18)].Number),(yyvsp[(10) - (18)].String),(yyvsp[(12) - (18)].String),(yyvsp[(14) - (18)].Number),(yyvsp[(16) - (18)].Dotnum),(yyvsp[(18) - (18)].LoadMode),"",(yyvsp[(3) - (18)].Bool)); }
    break;

  case 91:
#line 200 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping((yyvsp[(4) - (18)].Number),(yyvsp[(6) - (18)].Number),(yyvsp[(8) - (18)].Number),(yyvsp[(10) - (18)].String),(yyvsp[(12) - (18)].String),(yyvsp[(14) - (18)].Number),(yyvsp[(16) - (18)].Dotnum),MidiInstrumentMapper::VOID,(yyvsp[(18) - (18)].String),(yyvsp[(3) - (18)].Bool)); }
    break;

  case 92:
#line 201 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping((yyvsp[(4) - (20)].Number),(yyvsp[(6) - (20)].Number),(yyvsp[(8) - (20)].Number),(yyvsp[(10) - (20)].String),(yyvsp[(12) - (20)].String),(yyvsp[(14) - (20)].Number),(yyvsp[(16) - (20)].Dotnum),(yyvsp[(18) - (20)].LoadMode),(yyvsp[(20) - (20)].String),(yyvsp[(3) - (20)].Bool)); }
    break;

  case 93:
#line 204 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveMIDIInstrumentMapping((yyvsp[(3) - (7)].Number),(yyvsp[(5) - (7)].Number),(yyvsp[(7) - (7)].Number)); }
    break;

  case 94:
#line 207 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveChannel((yyvsp[(3) - (3)].Number));                     }
    break;

  case 95:
#line 208 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveMidiInstrumentMap((yyvsp[(3) - (3)].Number));           }
    break;

  case 96:
#line 209 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveAllMidiInstrumentMaps();         }
    break;

  case 97:
#line 210 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveDbInstrumentDirectory((yyvsp[(5) - (5)].String), true); }
    break;

  case 98:
#line 211 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveDbInstrumentDirectory((yyvsp[(3) - (3)].String));       }
    break;

  case 99:
#line 212 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveDbInstrument((yyvsp[(3) - (3)].String));                }
    break;

  case 100:
#line 215 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAvailableEngines();                          }
    break;

  case 101:
#line 216 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAvailableMidiInputDrivers();                 }
    break;

  case 102:
#line 217 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDriverInfo((yyvsp[(5) - (5)].String));                     }
    break;

  case 103:
#line 218 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDriverParameterInfo((yyvsp[(5) - (7)].String), (yyvsp[(7) - (7)].String));        }
    break;

  case 104:
#line 219 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDriverParameterInfo((yyvsp[(5) - (9)].String), (yyvsp[(7) - (9)].String), (yyvsp[(9) - (9)].KeyValList));    }
    break;

  case 105:
#line 220 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAvailableAudioOutputDrivers();               }
    break;

  case 106:
#line 221 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDriverInfo((yyvsp[(5) - (5)].String));                   }
    break;

  case 107:
#line 222 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDriverParameterInfo((yyvsp[(5) - (7)].String), (yyvsp[(7) - (7)].String));      }
    break;

  case 108:
#line 223 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDriverParameterInfo((yyvsp[(5) - (9)].String), (yyvsp[(7) - (9)].String), (yyvsp[(9) - (9)].KeyValList));  }
    break;

  case 109:
#line 224 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDeviceCount();                    }
    break;

  case 110:
#line 225 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDeviceCount();                      }
    break;

  case 111:
#line 226 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDeviceInfo((yyvsp[(5) - (5)].Number));                   }
    break;

  case 112:
#line 227 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDeviceInfo((yyvsp[(5) - (5)].Number));                     }
    break;

  case 113:
#line 228 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputPortInfo((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number));                   }
    break;

  case 114:
#line 229 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputPortParameterInfo((yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].Number), (yyvsp[(9) - (9)].String));      }
    break;

  case 115:
#line 230 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputChannelInfo((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number));              }
    break;

  case 116:
#line 231 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputChannelParameterInfo((yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].Number), (yyvsp[(9) - (9)].String)); }
    break;

  case 117:
#line 232 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetChannels();                                  }
    break;

  case 118:
#line 233 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetChannelInfo((yyvsp[(5) - (5)].Number));                             }
    break;

  case 119:
#line 234 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetBufferFill((yyvsp[(5) - (7)].FillResponse), (yyvsp[(7) - (7)].Number));                          }
    break;

  case 120:
#line 235 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetStreamCount((yyvsp[(5) - (5)].Number));                             }
    break;

  case 121:
#line 236 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetVoiceCount((yyvsp[(5) - (5)].Number));                              }
    break;

  case 122:
#line 237 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetEngineInfo((yyvsp[(5) - (5)].String));                              }
    break;

  case 123:
#line 238 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetServerInfo();                                }
    break;

  case 124:
#line 239 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetTotalVoiceCount();                           }
    break;

  case 125:
#line 240 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetTotalVoiceCountMax();                        }
    break;

  case 126:
#line 241 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInstrumentMappings((yyvsp[(3) - (3)].Number));                  }
    break;

  case 127:
#line 242 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAllMidiInstrumentMappings();                 }
    break;

  case 128:
#line 243 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInstrumentMapping((yyvsp[(5) - (9)].Number),(yyvsp[(7) - (9)].Number),(yyvsp[(9) - (9)].Number));             }
    break;

  case 129:
#line 244 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInstrumentMaps();                        }
    break;

  case 130:
#line 245 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInstrumentMap((yyvsp[(5) - (5)].Number));                       }
    break;

  case 131:
#line 246 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetFxSends((yyvsp[(3) - (3)].Number));                                 }
    break;

  case 132:
#line 247 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetFxSendInfo((yyvsp[(5) - (7)].Number),(yyvsp[(7) - (7)].Number));                           }
    break;

  case 133:
#line 248 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetDbInstrumentDirectoryCount((yyvsp[(5) - (5)].String), true);        }
    break;

  case 134:
#line 249 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetDbInstrumentDirectoryCount((yyvsp[(3) - (3)].String), false);       }
    break;

  case 135:
#line 250 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetDbInstrumentDirectoryInfo((yyvsp[(5) - (5)].String));               }
    break;

  case 136:
#line 251 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetDbInstrumentCount((yyvsp[(5) - (5)].String), true);                 }
    break;

  case 137:
#line 252 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetDbInstrumentCount((yyvsp[(3) - (3)].String), false);                }
    break;

  case 138:
#line 253 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetDbInstrumentInfo((yyvsp[(5) - (5)].String));                        }
    break;

  case 139:
#line 254 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetDbInstrumentsJobInfo((yyvsp[(5) - (5)].Number));                    }
    break;

  case 140:
#line 255 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetGlobalVolume();                              }
    break;

  case 141:
#line 258 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputDeviceParameter((yyvsp[(3) - (7)].Number), (yyvsp[(5) - (7)].String), (yyvsp[(7) - (7)].String));      }
    break;

  case 142:
#line 259 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputChannelParameter((yyvsp[(3) - (9)].Number), (yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].String), (yyvsp[(9) - (9)].String)); }
    break;

  case 143:
#line 260 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMidiInputDeviceParameter((yyvsp[(3) - (7)].Number), (yyvsp[(5) - (7)].String), (yyvsp[(7) - (7)].String));        }
    break;

  case 144:
#line 261 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMidiInputPortParameter((yyvsp[(3) - (9)].Number), (yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].String), (yyvsp[(9) - (9)].String));      }
    break;

  case 145:
#line 262 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                         }
    break;

  case 146:
#line 263 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMidiInstrumentMapName((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].String));               }
    break;

  case 147:
#line 264 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetFxSendName((yyvsp[(5) - (9)].Number),(yyvsp[(7) - (9)].Number),(yyvsp[(9) - (9)].String));                        }
    break;

  case 148:
#line 265 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetFxSendAudioOutputChannel((yyvsp[(5) - (11)].Number),(yyvsp[(7) - (11)].Number),(yyvsp[(9) - (11)].Number),(yyvsp[(11) - (11)].Number)); }
    break;

  case 149:
#line 266 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetFxSendMidiController((yyvsp[(5) - (9)].Number),(yyvsp[(7) - (9)].Number),(yyvsp[(9) - (9)].Number));              }
    break;

  case 150:
#line 267 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetFxSendLevel((yyvsp[(5) - (9)].Number),(yyvsp[(7) - (9)].Number),(yyvsp[(9) - (9)].Dotnum));                       }
    break;

  case 151:
#line 268 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetDbInstrumentDirectoryName((yyvsp[(5) - (7)].String),(yyvsp[(7) - (7)].String));            }
    break;

  case 152:
#line 269 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetDbInstrumentDirectoryDescription((yyvsp[(5) - (7)].String),(yyvsp[(7) - (7)].String));     }
    break;

  case 153:
#line 270 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetDbInstrumentName((yyvsp[(5) - (7)].String),(yyvsp[(7) - (7)].String));                     }
    break;

  case 154:
#line 271 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetDbInstrumentDescription((yyvsp[(5) - (7)].String),(yyvsp[(7) - (7)].String));              }
    break;

  case 155:
#line 272 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetEcho((yyparse_param_t*) yyparse_param, (yyvsp[(3) - (3)].Dotnum));  }
    break;

  case 156:
#line 273 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetGlobalVolume((yyvsp[(3) - (3)].Dotnum));                            }
    break;

  case 157:
#line 276 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateAudioOutputDevice((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].KeyValList)); }
    break;

  case 158:
#line 277 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateAudioOutputDevice((yyvsp[(3) - (3)].String));    }
    break;

  case 159:
#line 278 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateMidiInputDevice((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].KeyValList));   }
    break;

  case 160:
#line 279 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateMidiInputDevice((yyvsp[(3) - (3)].String));      }
    break;

  case 161:
#line 280 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateFxSend((yyvsp[(3) - (5)].Number),(yyvsp[(5) - (5)].Number));            }
    break;

  case 162:
#line 281 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateFxSend((yyvsp[(3) - (7)].Number),(yyvsp[(5) - (7)].Number),(yyvsp[(7) - (7)].String)); }
    break;

  case 163:
#line 284 "lscp.y"
    { (yyval.String) = LSCPSERVER->ResetChannel((yyvsp[(3) - (3)].Number)); }
    break;

  case 164:
#line 287 "lscp.y"
    { (yyval.String) = LSCPSERVER->ClearMidiInstrumentMappings((yyvsp[(3) - (3)].Number));  }
    break;

  case 165:
#line 288 "lscp.y"
    { (yyval.String) = LSCPSERVER->ClearAllMidiInstrumentMappings(); }
    break;

  case 166:
#line 291 "lscp.y"
    { (yyval.String) = LSCPSERVER->FindDbInstruments((yyvsp[(5) - (7)].String),(yyvsp[(7) - (7)].KeyValList), false);           }
    break;

  case 167:
#line 292 "lscp.y"
    { (yyval.String) = LSCPSERVER->FindDbInstruments((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].KeyValList), true);            }
    break;

  case 168:
#line 293 "lscp.y"
    { (yyval.String) = LSCPSERVER->FindDbInstrumentDirectories((yyvsp[(5) - (7)].String),(yyvsp[(7) - (7)].KeyValList), false); }
    break;

  case 169:
#line 294 "lscp.y"
    { (yyval.String) = LSCPSERVER->FindDbInstrumentDirectories((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].KeyValList), true);  }
    break;

  case 170:
#line 297 "lscp.y"
    { (yyval.String) = LSCPSERVER->MoveDbInstrumentDirectory((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].String)); }
    break;

  case 171:
#line 298 "lscp.y"
    { (yyval.String) = LSCPSERVER->MoveDbInstrument((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].String));          }
    break;

  case 172:
#line 301 "lscp.y"
    { (yyval.String) = LSCPSERVER->CopyDbInstrumentDirectory((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].String)); }
    break;

  case 173:
#line 302 "lscp.y"
    { (yyval.String) = LSCPSERVER->CopyDbInstrument((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].String));          }
    break;

  case 174:
#line 305 "lscp.y"
    { (yyval.String) = LSCPSERVER->DestroyAudioOutputDevice((yyvsp[(3) - (3)].Number)); }
    break;

  case 175:
#line 306 "lscp.y"
    { (yyval.String) = LSCPSERVER->DestroyMidiInputDevice((yyvsp[(3) - (3)].Number));   }
    break;

  case 176:
#line 307 "lscp.y"
    { (yyval.String) = LSCPSERVER->DestroyFxSend((yyvsp[(3) - (5)].Number),(yyvsp[(5) - (5)].Number)); }
    break;

  case 177:
#line 310 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String); }
    break;

  case 178:
#line 311 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String); }
    break;

  case 179:
#line 314 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputDevice((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));      }
    break;

  case 180:
#line 315 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputChannel((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number), (yyvsp[(3) - (7)].Number)); }
    break;

  case 181:
#line 316 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputType((yyvsp[(5) - (5)].String), (yyvsp[(3) - (5)].Number));        }
    break;

  case 182:
#line 317 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInput((yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].Number), (yyvsp[(9) - (9)].Number), (yyvsp[(3) - (9)].Number));      }
    break;

  case 183:
#line 318 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputDevice((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));        }
    break;

  case 184:
#line 319 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputPort((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));          }
    break;

  case 185:
#line 320 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputChannel((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));       }
    break;

  case 186:
#line 321 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputType((yyvsp[(5) - (5)].String), (yyvsp[(3) - (5)].Number));          }
    break;

  case 187:
#line 322 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetVolume((yyvsp[(5) - (5)].Dotnum), (yyvsp[(3) - (5)].Number));                 }
    break;

  case 188:
#line 323 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMute((yyvsp[(5) - (5)].Dotnum), (yyvsp[(3) - (5)].Number));            }
    break;

  case 189:
#line 324 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelSolo((yyvsp[(5) - (5)].Dotnum), (yyvsp[(3) - (5)].Number));            }
    break;

  case 190:
#line 325 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMap((yyvsp[(3) - (5)].Number), (yyvsp[(5) - (5)].Number));             }
    break;

  case 191:
#line 326 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMap((yyvsp[(3) - (5)].Number), -1);             }
    break;

  case 192:
#line 327 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMap((yyvsp[(3) - (5)].Number), -2);             }
    break;

  case 193:
#line 330 "lscp.y"
    { (yyval.String) = LSCPSERVER->EditSamplerChannelInstrument((yyvsp[(3) - (3)].Number)); }
    break;

  case 194:
#line 333 "lscp.y"
    { (yyval.Bool) = true;  }
    break;

  case 195:
#line 334 "lscp.y"
    { (yyval.Bool) = false; }
    break;

  case 196:
#line 337 "lscp.y"
    { (yyval.KeyValList)[(yyvsp[(1) - (3)].String)] = (yyvsp[(3) - (3)].String);          }
    break;

  case 197:
#line 338 "lscp.y"
    { (yyval.KeyValList) = (yyvsp[(1) - (5)].KeyValList); (yyval.KeyValList)[(yyvsp[(3) - (5)].String)] = (yyvsp[(5) - (5)].String); }
    break;

  case 198:
#line 341 "lscp.y"
    { (yyval.FillResponse) = fill_response_bytes;      }
    break;

  case 199:
#line 342 "lscp.y"
    { (yyval.FillResponse) = fill_response_percentage; }
    break;

  case 200:
#line 345 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDevices();              }
    break;

  case 201:
#line 346 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDevices();                }
    break;

  case 202:
#line 347 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListChannels();                       }
    break;

  case 203:
#line 348 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableEngines();               }
    break;

  case 204:
#line 349 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableMidiInputDrivers();      }
    break;

  case 205:
#line 350 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableAudioOutputDrivers();    }
    break;

  case 206:
#line 351 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListMidiInstrumentMappings((yyvsp[(3) - (3)].Number));       }
    break;

  case 207:
#line 352 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAllMidiInstrumentMappings();      }
    break;

  case 208:
#line 353 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListMidiInstrumentMaps();             }
    break;

  case 209:
#line 354 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListFxSends((yyvsp[(3) - (3)].Number));                      }
    break;

  case 210:
#line 355 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetDbInstrumentDirectories((yyvsp[(5) - (5)].String), true); }
    break;

  case 211:
#line 356 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetDbInstrumentDirectories((yyvsp[(3) - (3)].String));       }
    break;

  case 212:
#line 357 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetDbInstruments((yyvsp[(5) - (5)].String), true);           }
    break;

  case 213:
#line 358 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetDbInstruments((yyvsp[(3) - (3)].String));                 }
    break;

  case 214:
#line 361 "lscp.y"
    { (yyval.String) = LSCPSERVER->LoadInstrument((yyvsp[(1) - (5)].String), (yyvsp[(3) - (5)].Number), (yyvsp[(5) - (5)].Number));       }
    break;

  case 215:
#line 362 "lscp.y"
    { (yyval.String) = LSCPSERVER->LoadInstrument((yyvsp[(3) - (7)].String), (yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number), true); }
    break;

  case 216:
#line 365 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetEngineType((yyvsp[(1) - (3)].String), (yyvsp[(3) - (3)].Number)); }
    break;

  case 217:
#line 368 "lscp.y"
    { (yyval.LoadMode) = MidiInstrumentMapper::ON_DEMAND;      }
    break;

  case 218:
#line 369 "lscp.y"
    { (yyval.LoadMode) = MidiInstrumentMapper::ON_DEMAND_HOLD; }
    break;

  case 219:
#line 370 "lscp.y"
    { (yyval.LoadMode) = MidiInstrumentMapper::PERSISTENT;     }
    break;

  case 225:
#line 386 "lscp.y"
    { (yyval.Number) = 16; }
    break;

  case 232:
#line 405 "lscp.y"
    { (yyval.Dotnum) = (yyvsp[(1) - (1)].Number); }
    break;

  case 244:
#line 439 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (3)].String) + "," + (yyvsp[(3) - (3)].String); }
    break;

  case 247:
#line 444 "lscp.y"
    { std::stringstream ss; ss << "\'" << (yyvsp[(1) - (1)].Number) << "\'"; (yyval.String) = ss.str(); }
    break;

  case 248:
#line 445 "lscp.y"
    { std::stringstream ss; ss << "\'" << (yyvsp[(1) - (1)].Dotnum) << "\'"; (yyval.String) = ss.str(); }
    break;

  case 249:
#line 448 "lscp.y"
    { (yyval.KeyValList)[(yyvsp[(1) - (3)].String)] = (yyvsp[(3) - (3)].String);          }
    break;

  case 250:
#line 449 "lscp.y"
    { (yyval.KeyValList) = (yyvsp[(1) - (5)].KeyValList); (yyval.KeyValList)[(yyvsp[(3) - (5)].String)] = (yyvsp[(5) - (5)].String); }
    break;

  case 253:
#line 456 "lscp.y"
    { (yyval.String) = "RECURSIVE"; }
    break;

  case 254:
#line 457 "lscp.y"
    { (yyval.String) = "NON_RECURSIVE"; }
    break;

  case 255:
#line 458 "lscp.y"
    { (yyval.String) = "FLAT"; }
    break;

  case 256:
#line 466 "lscp.y"
    { (yyval.Dotnum) = (yyvsp[(1) - (1)].Number); }
    break;

  case 257:
#line 467 "lscp.y"
    { (yyval.Dotnum) = -1; }
    break;

  case 258:
#line 470 "lscp.y"
    { std::string s; s = (yyvsp[(1) - (1)].Char); (yyval.String) = s; }
    break;

  case 259:
#line 471 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + (yyvsp[(2) - (2)].Char);                  }
    break;

  case 260:
#line 474 "lscp.y"
    { (yyval.Dotnum) = atof(String((yyvsp[(1) - (3)].String) + "." + (yyvsp[(3) - (3)].String)).c_str());                         }
    break;

  case 261:
#line 475 "lscp.y"
    { String s = "+"; s += (yyvsp[(2) - (4)].String); s += "."; s += (yyvsp[(4) - (4)].String); (yyval.Dotnum) = atof(s.c_str()); }
    break;

  case 262:
#line 476 "lscp.y"
    { (yyval.Dotnum) = atof(String("-" + (yyvsp[(2) - (4)].String) + "." + (yyvsp[(4) - (4)].String)).c_str());                   }
    break;

  case 263:
#line 480 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (1)].Char);      }
    break;

  case 264:
#line 481 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + (yyvsp[(2) - (2)].Char); }
    break;

  case 265:
#line 484 "lscp.y"
    { (yyval.Char) = '0'; }
    break;

  case 266:
#line 485 "lscp.y"
    { (yyval.Char) = '1'; }
    break;

  case 267:
#line 486 "lscp.y"
    { (yyval.Char) = '2'; }
    break;

  case 268:
#line 487 "lscp.y"
    { (yyval.Char) = '3'; }
    break;

  case 269:
#line 488 "lscp.y"
    { (yyval.Char) = '4'; }
    break;

  case 270:
#line 489 "lscp.y"
    { (yyval.Char) = '5'; }
    break;

  case 271:
#line 490 "lscp.y"
    { (yyval.Char) = '6'; }
    break;

  case 272:
#line 491 "lscp.y"
    { (yyval.Char) = '7'; }
    break;

  case 273:
#line 492 "lscp.y"
    { (yyval.Char) = '8'; }
    break;

  case 274:
#line 493 "lscp.y"
    { (yyval.Char) = '9'; }
    break;

  case 275:
#line 496 "lscp.y"
    { (yyval.Number) = atoi(String(1, (yyvsp[(1) - (1)].Char)).c_str());      }
    break;

  case 276:
#line 497 "lscp.y"
    { (yyval.Number) = atoi(String(String("1") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 277:
#line 498 "lscp.y"
    { (yyval.Number) = atoi(String(String("2") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 278:
#line 499 "lscp.y"
    { (yyval.Number) = atoi(String(String("3") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 279:
#line 500 "lscp.y"
    { (yyval.Number) = atoi(String(String("4") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 280:
#line 501 "lscp.y"
    { (yyval.Number) = atoi(String(String("5") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 281:
#line 502 "lscp.y"
    { (yyval.Number) = atoi(String(String("6") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 282:
#line 503 "lscp.y"
    { (yyval.Number) = atoi(String(String("7") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 283:
#line 504 "lscp.y"
    { (yyval.Number) = atoi(String(String("8") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 284:
#line 505 "lscp.y"
    { (yyval.Number) = atoi(String(String("9") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 285:
#line 507 "lscp.y"
    { (yyval.Char) = 'A'; }
    break;

  case 286:
#line 507 "lscp.y"
    { (yyval.Char) = 'B'; }
    break;

  case 287:
#line 507 "lscp.y"
    { (yyval.Char) = 'C'; }
    break;

  case 288:
#line 507 "lscp.y"
    { (yyval.Char) = 'D'; }
    break;

  case 289:
#line 507 "lscp.y"
    { (yyval.Char) = 'E'; }
    break;

  case 290:
#line 507 "lscp.y"
    { (yyval.Char) = 'F'; }
    break;

  case 291:
#line 507 "lscp.y"
    { (yyval.Char) = 'G'; }
    break;

  case 292:
#line 507 "lscp.y"
    { (yyval.Char) = 'H'; }
    break;

  case 293:
#line 507 "lscp.y"
    { (yyval.Char) = 'I'; }
    break;

  case 294:
#line 507 "lscp.y"
    { (yyval.Char) = 'J'; }
    break;

  case 295:
#line 507 "lscp.y"
    { (yyval.Char) = 'K'; }
    break;

  case 296:
#line 507 "lscp.y"
    { (yyval.Char) = 'L'; }
    break;

  case 297:
#line 507 "lscp.y"
    { (yyval.Char) = 'M'; }
    break;

  case 298:
#line 507 "lscp.y"
    { (yyval.Char) = 'N'; }
    break;

  case 299:
#line 507 "lscp.y"
    { (yyval.Char) = 'O'; }
    break;

  case 300:
#line 507 "lscp.y"
    { (yyval.Char) = 'P'; }
    break;

  case 301:
#line 507 "lscp.y"
    { (yyval.Char) = 'Q'; }
    break;

  case 302:
#line 507 "lscp.y"
    { (yyval.Char) = 'R'; }
    break;

  case 303:
#line 507 "lscp.y"
    { (yyval.Char) = 'S'; }
    break;

  case 304:
#line 507 "lscp.y"
    { (yyval.Char) = 'T'; }
    break;

  case 305:
#line 507 "lscp.y"
    { (yyval.Char) = 'U'; }
    break;

  case 306:
#line 507 "lscp.y"
    { (yyval.Char) = 'V'; }
    break;

  case 307:
#line 507 "lscp.y"
    { (yyval.Char) = 'W'; }
    break;

  case 308:
#line 507 "lscp.y"
    { (yyval.Char) = 'X'; }
    break;

  case 309:
#line 507 "lscp.y"
    { (yyval.Char) = 'Y'; }
    break;

  case 310:
#line 507 "lscp.y"
    { (yyval.Char) = 'Z'; }
    break;

  case 311:
#line 508 "lscp.y"
    { (yyval.Char) = 'a'; }
    break;

  case 312:
#line 508 "lscp.y"
    { (yyval.Char) = 'b'; }
    break;

  case 313:
#line 508 "lscp.y"
    { (yyval.Char) = 'c'; }
    break;

  case 314:
#line 508 "lscp.y"
    { (yyval.Char) = 'd'; }
    break;

  case 315:
#line 508 "lscp.y"
    { (yyval.Char) = 'e'; }
    break;

  case 316:
#line 508 "lscp.y"
    { (yyval.Char) = 'f'; }
    break;

  case 317:
#line 508 "lscp.y"
    { (yyval.Char) = 'g'; }
    break;

  case 318:
#line 508 "lscp.y"
    { (yyval.Char) = 'h'; }
    break;

  case 319:
#line 508 "lscp.y"
    { (yyval.Char) = 'i'; }
    break;

  case 320:
#line 508 "lscp.y"
    { (yyval.Char) = 'j'; }
    break;

  case 321:
#line 508 "lscp.y"
    { (yyval.Char) = 'k'; }
    break;

  case 322:
#line 508 "lscp.y"
    { (yyval.Char) = 'l'; }
    break;

  case 323:
#line 508 "lscp.y"
    { (yyval.Char) = 'm'; }
    break;

  case 324:
#line 508 "lscp.y"
    { (yyval.Char) = 'n'; }
    break;

  case 325:
#line 508 "lscp.y"
    { (yyval.Char) = 'o'; }
    break;

  case 326:
#line 508 "lscp.y"
    { (yyval.Char) = 'p'; }
    break;

  case 327:
#line 508 "lscp.y"
    { (yyval.Char) = 'q'; }
    break;

  case 328:
#line 508 "lscp.y"
    { (yyval.Char) = 'r'; }
    break;

  case 329:
#line 508 "lscp.y"
    { (yyval.Char) = 's'; }
    break;

  case 330:
#line 508 "lscp.y"
    { (yyval.Char) = 't'; }
    break;

  case 331:
#line 508 "lscp.y"
    { (yyval.Char) = 'u'; }
    break;

  case 332:
#line 508 "lscp.y"
    { (yyval.Char) = 'v'; }
    break;

  case 333:
#line 508 "lscp.y"
    { (yyval.Char) = 'w'; }
    break;

  case 334:
#line 508 "lscp.y"
    { (yyval.Char) = 'x'; }
    break;

  case 335:
#line 508 "lscp.y"
    { (yyval.Char) = 'y'; }
    break;

  case 336:
#line 508 "lscp.y"
    { (yyval.Char) = 'z'; }
    break;

  case 337:
#line 509 "lscp.y"
    { (yyval.Char) = '0'; }
    break;

  case 338:
#line 509 "lscp.y"
    { (yyval.Char) = '1'; }
    break;

  case 339:
#line 509 "lscp.y"
    { (yyval.Char) = '2'; }
    break;

  case 340:
#line 509 "lscp.y"
    { (yyval.Char) = '3'; }
    break;

  case 341:
#line 509 "lscp.y"
    { (yyval.Char) = '4'; }
    break;

  case 342:
#line 509 "lscp.y"
    { (yyval.Char) = '5'; }
    break;

  case 343:
#line 509 "lscp.y"
    { (yyval.Char) = '6'; }
    break;

  case 344:
#line 509 "lscp.y"
    { (yyval.Char) = '7'; }
    break;

  case 345:
#line 509 "lscp.y"
    { (yyval.Char) = '8'; }
    break;

  case 346:
#line 509 "lscp.y"
    { (yyval.Char) = '9'; }
    break;

  case 347:
#line 510 "lscp.y"
    { (yyval.Char) = '!'; }
    break;

  case 348:
#line 510 "lscp.y"
    { (yyval.Char) = '#'; }
    break;

  case 349:
#line 510 "lscp.y"
    { (yyval.Char) = '$'; }
    break;

  case 350:
#line 510 "lscp.y"
    { (yyval.Char) = '%'; }
    break;

  case 351:
#line 510 "lscp.y"
    { (yyval.Char) = '&'; }
    break;

  case 352:
#line 510 "lscp.y"
    { (yyval.Char) = '('; }
    break;

  case 353:
#line 510 "lscp.y"
    { (yyval.Char) = ')'; }
    break;

  case 354:
#line 510 "lscp.y"
    { (yyval.Char) = '*'; }
    break;

  case 355:
#line 510 "lscp.y"
    { (yyval.Char) = '+'; }
    break;

  case 356:
#line 510 "lscp.y"
    { (yyval.Char) = '-'; }
    break;

  case 357:
#line 510 "lscp.y"
    { (yyval.Char) = '.'; }
    break;

  case 358:
#line 510 "lscp.y"
    { (yyval.Char) = ','; }
    break;

  case 359:
#line 510 "lscp.y"
    { (yyval.Char) = '/'; }
    break;

  case 360:
#line 511 "lscp.y"
    { (yyval.Char) = ':'; }
    break;

  case 361:
#line 511 "lscp.y"
    { (yyval.Char) = ';'; }
    break;

  case 362:
#line 511 "lscp.y"
    { (yyval.Char) = '<'; }
    break;

  case 363:
#line 511 "lscp.y"
    { (yyval.Char) = '='; }
    break;

  case 364:
#line 511 "lscp.y"
    { (yyval.Char) = '>'; }
    break;

  case 365:
#line 511 "lscp.y"
    { (yyval.Char) = '?'; }
    break;

  case 366:
#line 511 "lscp.y"
    { (yyval.Char) = '@'; }
    break;

  case 367:
#line 512 "lscp.y"
    { (yyval.Char) = '['; }
    break;

  case 368:
#line 512 "lscp.y"
    { (yyval.Char) = '\\'; }
    break;

  case 369:
#line 512 "lscp.y"
    { (yyval.Char) = ']'; }
    break;

  case 370:
#line 512 "lscp.y"
    { (yyval.Char) = '^'; }
    break;

  case 371:
#line 512 "lscp.y"
    { (yyval.Char) = '_'; }
    break;

  case 372:
#line 513 "lscp.y"
    { (yyval.Char) = '{'; }
    break;

  case 373:
#line 513 "lscp.y"
    { (yyval.Char) = '|'; }
    break;

  case 374:
#line 513 "lscp.y"
    { (yyval.Char) = '}'; }
    break;

  case 375:
#line 513 "lscp.y"
    { (yyval.Char) = '~'; }
    break;

  case 376:
#line 514 "lscp.y"
    { (yyval.Char) = '\200'; }
    break;

  case 377:
#line 514 "lscp.y"
    { (yyval.Char) = '\201'; }
    break;

  case 378:
#line 514 "lscp.y"
    { (yyval.Char) = '\202'; }
    break;

  case 379:
#line 515 "lscp.y"
    { (yyval.Char) = '\203'; }
    break;

  case 380:
#line 515 "lscp.y"
    { (yyval.Char) = '\204'; }
    break;

  case 381:
#line 515 "lscp.y"
    { (yyval.Char) = '\205'; }
    break;

  case 382:
#line 516 "lscp.y"
    { (yyval.Char) = '\206'; }
    break;

  case 383:
#line 516 "lscp.y"
    { (yyval.Char) = '\207'; }
    break;

  case 384:
#line 516 "lscp.y"
    { (yyval.Char) = '\210'; }
    break;

  case 385:
#line 517 "lscp.y"
    { (yyval.Char) = '\211'; }
    break;

  case 386:
#line 517 "lscp.y"
    { (yyval.Char) = '\212'; }
    break;

  case 387:
#line 517 "lscp.y"
    { (yyval.Char) = '\213'; }
    break;

  case 388:
#line 518 "lscp.y"
    { (yyval.Char) = '\214'; }
    break;

  case 389:
#line 518 "lscp.y"
    { (yyval.Char) = '\215'; }
    break;

  case 390:
#line 518 "lscp.y"
    { (yyval.Char) = '\216'; }
    break;

  case 391:
#line 519 "lscp.y"
    { (yyval.Char) = '\217'; }
    break;

  case 392:
#line 519 "lscp.y"
    { (yyval.Char) = '\220'; }
    break;

  case 393:
#line 519 "lscp.y"
    { (yyval.Char) = '\221'; }
    break;

  case 394:
#line 520 "lscp.y"
    { (yyval.Char) = '\222'; }
    break;

  case 395:
#line 520 "lscp.y"
    { (yyval.Char) = '\223'; }
    break;

  case 396:
#line 520 "lscp.y"
    { (yyval.Char) = '\224'; }
    break;

  case 397:
#line 521 "lscp.y"
    { (yyval.Char) = '\225'; }
    break;

  case 398:
#line 521 "lscp.y"
    { (yyval.Char) = '\226'; }
    break;

  case 399:
#line 521 "lscp.y"
    { (yyval.Char) = '\227'; }
    break;

  case 400:
#line 522 "lscp.y"
    { (yyval.Char) = '\230'; }
    break;

  case 401:
#line 522 "lscp.y"
    { (yyval.Char) = '\231'; }
    break;

  case 402:
#line 522 "lscp.y"
    { (yyval.Char) = '\232'; }
    break;

  case 403:
#line 523 "lscp.y"
    { (yyval.Char) = '\233'; }
    break;

  case 404:
#line 523 "lscp.y"
    { (yyval.Char) = '\234'; }
    break;

  case 405:
#line 523 "lscp.y"
    { (yyval.Char) = '\235'; }
    break;

  case 406:
#line 524 "lscp.y"
    { (yyval.Char) = '\236'; }
    break;

  case 407:
#line 524 "lscp.y"
    { (yyval.Char) = '\237'; }
    break;

  case 408:
#line 524 "lscp.y"
    { (yyval.Char) = '\240'; }
    break;

  case 409:
#line 525 "lscp.y"
    { (yyval.Char) = '\241'; }
    break;

  case 410:
#line 525 "lscp.y"
    { (yyval.Char) = '\242'; }
    break;

  case 411:
#line 525 "lscp.y"
    { (yyval.Char) = '\243'; }
    break;

  case 412:
#line 526 "lscp.y"
    { (yyval.Char) = '\244'; }
    break;

  case 413:
#line 526 "lscp.y"
    { (yyval.Char) = '\245'; }
    break;

  case 414:
#line 526 "lscp.y"
    { (yyval.Char) = '\246'; }
    break;

  case 415:
#line 527 "lscp.y"
    { (yyval.Char) = '\247'; }
    break;

  case 416:
#line 527 "lscp.y"
    { (yyval.Char) = '\250'; }
    break;

  case 417:
#line 527 "lscp.y"
    { (yyval.Char) = '\251'; }
    break;

  case 418:
#line 528 "lscp.y"
    { (yyval.Char) = '\252'; }
    break;

  case 419:
#line 528 "lscp.y"
    { (yyval.Char) = '\253'; }
    break;

  case 420:
#line 528 "lscp.y"
    { (yyval.Char) = '\254'; }
    break;

  case 421:
#line 529 "lscp.y"
    { (yyval.Char) = '\255'; }
    break;

  case 422:
#line 529 "lscp.y"
    { (yyval.Char) = '\256'; }
    break;

  case 423:
#line 529 "lscp.y"
    { (yyval.Char) = '\257'; }
    break;

  case 424:
#line 530 "lscp.y"
    { (yyval.Char) = '\260'; }
    break;

  case 425:
#line 530 "lscp.y"
    { (yyval.Char) = '\261'; }
    break;

  case 426:
#line 530 "lscp.y"
    { (yyval.Char) = '\262'; }
    break;

  case 427:
#line 531 "lscp.y"
    { (yyval.Char) = '\263'; }
    break;

  case 428:
#line 531 "lscp.y"
    { (yyval.Char) = '\264'; }
    break;

  case 429:
#line 531 "lscp.y"
    { (yyval.Char) = '\265'; }
    break;

  case 430:
#line 532 "lscp.y"
    { (yyval.Char) = '\266'; }
    break;

  case 431:
#line 532 "lscp.y"
    { (yyval.Char) = '\267'; }
    break;

  case 432:
#line 532 "lscp.y"
    { (yyval.Char) = '\270'; }
    break;

  case 433:
#line 533 "lscp.y"
    { (yyval.Char) = '\271'; }
    break;

  case 434:
#line 533 "lscp.y"
    { (yyval.Char) = '\272'; }
    break;

  case 435:
#line 533 "lscp.y"
    { (yyval.Char) = '\273'; }
    break;

  case 436:
#line 534 "lscp.y"
    { (yyval.Char) = '\274'; }
    break;

  case 437:
#line 534 "lscp.y"
    { (yyval.Char) = '\275'; }
    break;

  case 438:
#line 534 "lscp.y"
    { (yyval.Char) = '\276'; }
    break;

  case 439:
#line 535 "lscp.y"
    { (yyval.Char) = '\277'; }
    break;

  case 440:
#line 535 "lscp.y"
    { (yyval.Char) = '\300'; }
    break;

  case 441:
#line 535 "lscp.y"
    { (yyval.Char) = '\301'; }
    break;

  case 442:
#line 536 "lscp.y"
    { (yyval.Char) = '\302'; }
    break;

  case 443:
#line 536 "lscp.y"
    { (yyval.Char) = '\303'; }
    break;

  case 444:
#line 536 "lscp.y"
    { (yyval.Char) = '\304'; }
    break;

  case 445:
#line 537 "lscp.y"
    { (yyval.Char) = '\305'; }
    break;

  case 446:
#line 537 "lscp.y"
    { (yyval.Char) = '\306'; }
    break;

  case 447:
#line 537 "lscp.y"
    { (yyval.Char) = '\307'; }
    break;

  case 448:
#line 538 "lscp.y"
    { (yyval.Char) = '\310'; }
    break;

  case 449:
#line 538 "lscp.y"
    { (yyval.Char) = '\311'; }
    break;

  case 450:
#line 538 "lscp.y"
    { (yyval.Char) = '\312'; }
    break;

  case 451:
#line 539 "lscp.y"
    { (yyval.Char) = '\313'; }
    break;

  case 452:
#line 539 "lscp.y"
    { (yyval.Char) = '\314'; }
    break;

  case 453:
#line 539 "lscp.y"
    { (yyval.Char) = '\315'; }
    break;

  case 454:
#line 540 "lscp.y"
    { (yyval.Char) = '\316'; }
    break;

  case 455:
#line 540 "lscp.y"
    { (yyval.Char) = '\317'; }
    break;

  case 456:
#line 540 "lscp.y"
    { (yyval.Char) = '\320'; }
    break;

  case 457:
#line 541 "lscp.y"
    { (yyval.Char) = '\321'; }
    break;

  case 458:
#line 541 "lscp.y"
    { (yyval.Char) = '\322'; }
    break;

  case 459:
#line 541 "lscp.y"
    { (yyval.Char) = '\323'; }
    break;

  case 460:
#line 542 "lscp.y"
    { (yyval.Char) = '\324'; }
    break;

  case 461:
#line 542 "lscp.y"
    { (yyval.Char) = '\325'; }
    break;

  case 462:
#line 542 "lscp.y"
    { (yyval.Char) = '\326'; }
    break;

  case 463:
#line 543 "lscp.y"
    { (yyval.Char) = '\327'; }
    break;

  case 464:
#line 543 "lscp.y"
    { (yyval.Char) = '\330'; }
    break;

  case 465:
#line 543 "lscp.y"
    { (yyval.Char) = '\331'; }
    break;

  case 466:
#line 544 "lscp.y"
    { (yyval.Char) = '\332'; }
    break;

  case 467:
#line 544 "lscp.y"
    { (yyval.Char) = '\333'; }
    break;

  case 468:
#line 544 "lscp.y"
    { (yyval.Char) = '\334'; }
    break;

  case 469:
#line 545 "lscp.y"
    { (yyval.Char) = '\335'; }
    break;

  case 470:
#line 545 "lscp.y"
    { (yyval.Char) = '\336'; }
    break;

  case 471:
#line 545 "lscp.y"
    { (yyval.Char) = '\337'; }
    break;

  case 472:
#line 546 "lscp.y"
    { (yyval.Char) = '\340'; }
    break;

  case 473:
#line 546 "lscp.y"
    { (yyval.Char) = '\341'; }
    break;

  case 474:
#line 546 "lscp.y"
    { (yyval.Char) = '\342'; }
    break;

  case 475:
#line 547 "lscp.y"
    { (yyval.Char) = '\343'; }
    break;

  case 476:
#line 547 "lscp.y"
    { (yyval.Char) = '\344'; }
    break;

  case 477:
#line 547 "lscp.y"
    { (yyval.Char) = '\345'; }
    break;

  case 478:
#line 548 "lscp.y"
    { (yyval.Char) = '\346'; }
    break;

  case 479:
#line 548 "lscp.y"
    { (yyval.Char) = '\347'; }
    break;

  case 480:
#line 548 "lscp.y"
    { (yyval.Char) = '\350'; }
    break;

  case 481:
#line 549 "lscp.y"
    { (yyval.Char) = '\351'; }
    break;

  case 482:
#line 549 "lscp.y"
    { (yyval.Char) = '\352'; }
    break;

  case 483:
#line 549 "lscp.y"
    { (yyval.Char) = '\353'; }
    break;

  case 484:
#line 550 "lscp.y"
    { (yyval.Char) = '\354'; }
    break;

  case 485:
#line 550 "lscp.y"
    { (yyval.Char) = '\355'; }
    break;

  case 486:
#line 550 "lscp.y"
    { (yyval.Char) = '\356'; }
    break;

  case 487:
#line 551 "lscp.y"
    { (yyval.Char) = '\357'; }
    break;

  case 488:
#line 551 "lscp.y"
    { (yyval.Char) = '\360'; }
    break;

  case 489:
#line 551 "lscp.y"
    { (yyval.Char) = '\361'; }
    break;

  case 490:
#line 552 "lscp.y"
    { (yyval.Char) = '\362'; }
    break;

  case 491:
#line 552 "lscp.y"
    { (yyval.Char) = '\363'; }
    break;

  case 492:
#line 552 "lscp.y"
    { (yyval.Char) = '\364'; }
    break;

  case 493:
#line 553 "lscp.y"
    { (yyval.Char) = '\365'; }
    break;

  case 494:
#line 553 "lscp.y"
    { (yyval.Char) = '\366'; }
    break;

  case 495:
#line 553 "lscp.y"
    { (yyval.Char) = '\367'; }
    break;

  case 496:
#line 554 "lscp.y"
    { (yyval.Char) = '\370'; }
    break;

  case 497:
#line 554 "lscp.y"
    { (yyval.Char) = '\371'; }
    break;

  case 498:
#line 554 "lscp.y"
    { (yyval.Char) = '\372'; }
    break;

  case 499:
#line 555 "lscp.y"
    { (yyval.Char) = '\373'; }
    break;

  case 500:
#line 555 "lscp.y"
    { (yyval.Char) = '\374'; }
    break;

  case 501:
#line 555 "lscp.y"
    { (yyval.Char) = '\375'; }
    break;

  case 502:
#line 556 "lscp.y"
    { (yyval.Char) = '\376'; }
    break;

  case 503:
#line 556 "lscp.y"
    { (yyval.Char) = '\377'; }
    break;

  case 504:
#line 559 "lscp.y"
    { (yyval.String) = " ";      }
    break;

  case 506:
#line 561 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + " "; }
    break;

  case 507:
#line 562 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + (yyvsp[(2) - (2)].String);  }
    break;

  case 508:
#line 565 "lscp.y"
    { (yyval.String) = (yyvsp[(2) - (3)].String); }
    break;

  case 509:
#line 566 "lscp.y"
    { (yyval.String) = (yyvsp[(2) - (3)].String); }
    break;


/* Line 1267 of yacc.c.  */
#line 6110 "y.tab.c"
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


#line 887 "lscp.y"


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

