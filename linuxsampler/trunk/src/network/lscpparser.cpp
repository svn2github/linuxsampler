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
#define YYLAST   4543

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  227
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  143
/* YYNRULES -- Number of rules.  */
#define YYNRULES  539
/* YYNRULES -- Number of states.  */
#define YYNSTATES  1705

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
     157,   159,   161,   163,   165,   167,   169,   171,   173,   175,
     192,   211,   230,   251,   259,   263,   267,   271,   273,   275,
     281,   289,   299,   301,   307,   315,   325,   327,   329,   335,
     341,   349,   359,   367,   377,   379,   385,   393,   399,   405,
     411,   415,   417,   419,   423,   427,   437,   439,   445,   449,
     457,   459,   467,   477,   485,   495,   499,   507,   519,   529,
     539,   543,   547,   553,   557,   563,   567,   573,   581,   585,
     589,   593,   597,   601,   607,   611,   615,   621,   629,   635,
     645,   651,   657,   663,   669,   675,   681,   687,   693,   699,
     705,   706,   709,   713,   719,   721,   723,   725,   727,   729,
     731,   733,   735,   739,   743,   745,   749,   755,   763,   767,
     769,   771,   773,   775,   777,   779,   781,   783,   785,   787,
     789,   791,   793,   795,   797,   799,   801,   803,   805,   807,
     809,   811,   813,   815,   817,   821,   823,   825,   827,   829,
     831,   833,   835,   838,   842,   847,   852,   854,   857,   859,
     861,   863,   865,   867,   869,   871,   873,   875,   877,   879,
     882,   885,   888,   891,   894,   897,   900,   903,   906,   908,
     910,   912,   914,   916,   918,   920,   922,   924,   926,   928,
     930,   932,   934,   936,   938,   940,   942,   944,   946,   948,
     950,   952,   954,   956,   958,   960,   962,   964,   966,   968,
     970,   972,   974,   976,   978,   980,   982,   984,   986,   988,
     990,   992,   994,   996,   998,  1000,  1002,  1004,  1006,  1008,
    1010,  1012,  1014,  1016,  1018,  1020,  1022,  1024,  1026,  1028,
    1030,  1032,  1034,  1036,  1038,  1040,  1042,  1044,  1046,  1048,
    1050,  1052,  1054,  1056,  1058,  1060,  1062,  1064,  1066,  1068,
    1070,  1072,  1074,  1076,  1078,  1080,  1082,  1084,  1086,  1088,
    1090,  1092,  1094,  1096,  1098,  1100,  1102,  1104,  1106,  1108,
    1110,  1112,  1114,  1116,  1118,  1120,  1122,  1124,  1126,  1128,
    1130,  1132,  1134,  1136,  1138,  1140,  1142,  1144,  1146,  1148,
    1150,  1152,  1154,  1156,  1158,  1160,  1162,  1164,  1166,  1168,
    1170,  1172,  1174,  1176,  1178,  1180,  1182,  1184,  1186,  1188,
    1190,  1192,  1194,  1196,  1198,  1200,  1202,  1204,  1206,  1208,
    1210,  1212,  1214,  1216,  1218,  1220,  1222,  1224,  1226,  1228,
    1230,  1232,  1234,  1236,  1238,  1240,  1242,  1244,  1246,  1248,
    1250,  1252,  1254,  1256,  1258,  1260,  1262,  1264,  1266,  1268,
    1270,  1272,  1274,  1276,  1278,  1280,  1282,  1284,  1286,  1288,
    1290,  1292,  1294,  1296,  1298,  1300,  1302,  1304,  1306,  1308,
    1310,  1312,  1314,  1316,  1318,  1320,  1322,  1324,  1326,  1328,
    1330,  1332,  1334,  1336,  1338,  1340,  1342,  1344,  1346,  1348,
    1351,  1354,  1358,  1362,  1364,  1366,  1368,  1372,  1376,  1380,
    1386,  1392,  1399,  1407,  1412,  1417,  1421,  1426,  1434,  1444,
    1451,  1455,  1465,  1477,  1484,  1492,  1510,  1541,  1550,  1555,
    1581,  1606,  1630,  1653,  1679,  1704,  1726,  1747,  1761,  1774,
    1788,  1801,  1813,  1826,  1838,  1856,  1878,  1890,  1901,  1908,
    1918,  1933,  1944,  1974,  1995,  2015,  2045,  2065,  2096,  2117,
    2135,  2164,  2192,  2218,  2237,  2255,  2283,  2299,  2316,  2336,
    2357,  2375,  2391,  2410,  2426,  2437,  2453,  2461,  2470,  2477,
    2484,  2490,  2495,  2500,  2506,  2517,  2523,  2537,  2542,  2547
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     228,     0,    -1,   229,   284,    -1,   229,   285,   284,    -1,
      -1,   230,    -1,   231,    -1,     1,    -1,     3,    -1,   230,
       3,    -1,   230,   283,    -1,   230,   279,    -1,   230,   275,
      -1,   286,   283,   232,    -1,   288,   283,   235,    -1,   289,
     283,   236,    -1,   287,   283,   238,    -1,   291,   283,   240,
      -1,   292,   283,   243,    -1,   293,   283,   249,    -1,   294,
     283,   244,    -1,   299,   283,   237,    -1,   300,   283,   239,
      -1,   301,   283,   233,    -1,   302,   283,   234,    -1,   303,
     283,   281,    -1,   365,   283,   241,    -1,   290,   283,   242,
      -1,   365,    -1,   369,    -1,   304,    -1,   348,    -1,   348,
     283,   269,    -1,   309,    -1,   310,    -1,   311,    -1,   312,
      -1,   317,    -1,   323,    -1,   322,    -1,   321,    -1,   318,
      -1,   319,    -1,   320,    -1,   313,    -1,   314,    -1,   315,
      -1,   316,    -1,   366,    -1,   324,    -1,   326,    -1,   309,
      -1,   310,    -1,   311,    -1,   312,    -1,   317,    -1,   323,
      -1,   322,    -1,   321,    -1,   318,    -1,   319,    -1,   320,
      -1,   313,    -1,   314,    -1,   315,    -1,   316,    -1,   366,
      -1,   324,    -1,   326,    -1,   346,   283,   246,   259,   283,
     260,   283,   261,   283,   267,   283,   268,   283,   265,   283,
     263,    -1,   346,   283,   246,   259,   283,   260,   283,   261,
     283,   267,   283,   268,   283,   265,   283,   263,   283,   252,
      -1,   346,   283,   246,   259,   283,   260,   283,   261,   283,
     267,   283,   268,   283,   265,   283,   263,   283,   270,    -1,
     346,   283,   246,   259,   283,   260,   283,   261,   283,   267,
     283,   268,   283,   265,   283,   263,   283,   252,   283,   270,
      -1,   346,   283,   259,   283,   260,   283,   261,    -1,   304,
     283,   264,    -1,   348,   283,   259,    -1,   348,   283,   295,
      -1,   305,    -1,   340,    -1,   350,   283,   308,   283,   275,
      -1,   345,   283,   308,   283,   275,   283,   275,    -1,   345,
     283,   308,   283,   275,   283,   275,   283,   247,    -1,   306,
      -1,   336,   283,   308,   283,   275,    -1,   335,   283,   308,
     283,   275,   283,   275,    -1,   335,   283,   308,   283,   275,
     283,   275,   283,   247,    -1,   333,    -1,   343,    -1,   334,
     283,   308,   283,   279,    -1,   344,   283,   308,   283,   279,
      -1,   351,   283,   308,   283,   279,   283,   279,    -1,   342,
     283,   308,   283,   279,   283,   279,   283,   275,    -1,   338,
     283,   308,   283,   279,   283,   279,    -1,   337,   283,   308,
     283,   279,   283,   279,   283,   275,    -1,   307,    -1,   304,
     283,   308,   283,   264,    -1,   304,   283,   321,   283,   248,
     283,   264,    -1,   304,   283,   322,   283,   264,    -1,   304,
     283,   323,   283,   264,    -1,   328,   283,   308,   283,   267,
      -1,   358,   283,   308,    -1,   324,    -1,   325,    -1,   347,
     283,   259,    -1,   347,   283,   295,    -1,   346,   283,   308,
     283,   259,   283,   260,   283,   261,    -1,   349,    -1,   348,
     283,   308,   283,   259,    -1,   357,   283,   264,    -1,   356,
     283,   308,   283,   264,   283,   266,    -1,   359,    -1,   332,
     283,   279,   283,   275,     4,   272,    -1,   337,   283,   279,
     283,   279,   283,   275,     4,   272,    -1,   341,   283,   279,
     283,   275,     4,   272,    -1,   342,   283,   279,   283,   279,
     283,   275,     4,   272,    -1,   304,   283,   245,    -1,   348,
     283,   367,   283,   259,   283,   269,    -1,   356,   283,   338,
     283,   264,   283,   266,   283,   254,   283,   254,    -1,   356,
     283,   355,   283,   264,   283,   266,   283,   262,    -1,   356,
     283,   360,   283,   264,   283,   266,   283,   263,    -1,   368,
     283,   274,    -1,   359,   283,   263,    -1,   334,   283,   275,
     283,   247,    -1,   334,   283,   275,    -1,   344,   283,   275,
     283,   247,    -1,   344,   283,   275,    -1,   356,   283,   264,
     283,   262,    -1,   356,   283,   264,   283,   262,   283,   271,
      -1,   304,   283,   264,    -1,   347,   283,   259,    -1,   347,
     283,   295,    -1,   334,   283,   279,    -1,   344,   283,   279,
      -1,   356,   283,   264,   283,   266,    -1,   327,   283,   250,
      -1,   328,   283,   251,    -1,   334,   283,   264,   283,   253,
      -1,   338,   283,   264,   283,   254,   283,   254,    -1,   339,
     283,   264,   283,   255,    -1,   354,   283,   264,   283,   253,
     283,   256,   283,   257,    -1,   344,   283,   264,   283,   253,
      -1,   351,   283,   264,   283,   256,    -1,   352,   283,   264,
     283,   257,    -1,   353,   283,   264,   283,   258,    -1,   359,
     283,   264,   283,   263,    -1,   361,   283,   264,   283,   274,
      -1,   362,   283,   264,   283,   274,    -1,   348,   283,   264,
     283,   259,    -1,   348,   283,   264,   283,   296,    -1,   348,
     283,   264,   283,   297,    -1,    -1,   298,   283,    -1,   275,
       4,   272,    -1,   247,   283,   275,     4,   272,    -1,   363,
      -1,   364,    -1,   333,    -1,   343,    -1,   307,    -1,   305,
      -1,   340,    -1,   306,    -1,   347,   283,   259,    -1,   347,
     283,   295,    -1,   349,    -1,   357,   283,   264,    -1,   268,
     283,   265,   283,   264,    -1,   298,   283,   268,   283,   265,
     283,   264,    -1,   267,   283,   264,    -1,   329,    -1,   330,
      -1,   331,    -1,   279,    -1,   279,    -1,   275,    -1,   279,
      -1,   279,    -1,   295,    -1,   275,    -1,   279,    -1,   279,
      -1,   279,    -1,   279,    -1,   276,    -1,   279,    -1,   279,
      -1,   279,    -1,   279,    -1,   275,    -1,   282,    -1,   282,
      -1,   282,    -1,   282,    -1,   273,    -1,   272,     5,   273,
      -1,   275,    -1,   282,    -1,   279,    -1,   276,    -1,   279,
      -1,   275,    -1,   280,    -1,   275,   280,    -1,   277,     6,
     277,    -1,     7,   277,     6,   277,    -1,     8,   277,     6,
     277,    -1,   278,    -1,   277,   278,    -1,     9,    -1,    10,
      -1,    11,    -1,    12,    -1,    13,    -1,    14,    -1,    15,
      -1,    16,    -1,    17,    -1,    18,    -1,   278,    -1,    10,
     277,    -1,    11,   277,    -1,    12,   277,    -1,    13,   277,
      -1,    14,   277,    -1,    15,   277,    -1,    16,   277,    -1,
      17,   277,    -1,    18,   277,    -1,    19,    -1,    20,    -1,
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
     220,    -1,   221,    -1,   283,    -1,   275,    -1,   281,   283,
      -1,   281,   275,    -1,   222,   281,   222,    -1,   223,   281,
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
      37,    23,    36,    40,    23,    36,    -1,    40,    33,    30,
      39,    31,    23,    -1,    30,    23,    40,    23,    30,    -1,
      31,    39,    38,    23,    -1,    37,    33,    30,    33,    -1,
      20,    43,    38,    23,    37,    -1,    34,    23,    36,    21,
      23,    32,    38,    19,    25,    23,    -1,    36,    23,    37,
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
     133,   134,   135,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   178,
     179,   180,   181,   184,   187,   188,   189,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   241,   242,   243,   244,   245,   246,   249,   252,
     253,   256,   257,   258,   261,   262,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     281,   282,   285,   286,   289,   290,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   302,   305,   306,   309,   312,
     313,   314,   317,   320,   323,   326,   329,   330,   333,   336,
     339,   342,   345,   348,   349,   352,   355,   358,   361,   364,
     367,   370,   373,   376,   377,   380,   381,   382,   383,   391,
     392,   395,   396,   399,   400,   401,   405,   406,   409,   410,
     411,   412,   413,   414,   415,   416,   417,   418,   421,   422,
     423,   424,   425,   426,   427,   428,   429,   430,   432,   432,
     432,   432,   432,   432,   432,   432,   432,   432,   432,   432,
     432,   432,   432,   432,   432,   432,   432,   432,   432,   432,
     432,   432,   432,   432,   433,   433,   433,   433,   433,   433,
     433,   433,   433,   433,   433,   433,   433,   433,   433,   433,
     433,   433,   433,   433,   433,   433,   433,   433,   433,   433,
     434,   434,   434,   434,   434,   434,   434,   434,   434,   434,
     435,   435,   435,   435,   435,   435,   435,   435,   435,   435,
     435,   435,   435,   436,   436,   436,   436,   436,   436,   436,
     437,   437,   437,   437,   437,   438,   438,   438,   438,   439,
     439,   439,   440,   440,   440,   441,   441,   441,   442,   442,
     442,   443,   443,   443,   444,   444,   444,   445,   445,   445,
     446,   446,   446,   447,   447,   447,   448,   448,   448,   449,
     449,   449,   450,   450,   450,   451,   451,   451,   452,   452,
     452,   453,   453,   453,   454,   454,   454,   455,   455,   455,
     456,   456,   456,   457,   457,   457,   458,   458,   458,   459,
     459,   459,   460,   460,   460,   461,   461,   461,   462,   462,
     462,   463,   463,   463,   464,   464,   464,   465,   465,   465,
     466,   466,   466,   467,   467,   467,   468,   468,   468,   469,
     469,   469,   470,   470,   470,   471,   471,   471,   472,   472,
     472,   473,   473,   473,   474,   474,   474,   475,   475,   475,
     476,   476,   476,   477,   477,   477,   478,   478,   478,   479,
     479,   479,   480,   480,   480,   481,   481,   484,   485,   486,
     487,   490,   491,   497,   500,   503,   506,   509,   512,   515,
     518,   521,   524,   527,   530,   533,   536,   539,   542,   545,
     548,   551,   554,   557,   560,   563,   566,   569,   572,   575,
     578,   581,   584,   587,   590,   593,   596,   599,   602,   605,
     608,   611,   614,   617,   620,   623,   626,   629,   632,   635,
     638,   641,   644,   647,   650,   653,   656,   659,   662,   665,
     668,   671,   674,   677,   680,   683,   686,   689,   692,   695,
     698,   701,   704,   707,   710,   713,   716,   719,   722,   725,
     728,   731,   734,   737,   740,   743,   746,   749,   752,   755
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
  "load_instruction", "set_chan_instruction", "modal_arg", "key_val_list",
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
  "MIDI_INSTRUMENT_INFO", "CHANNEL_COUNT", "CHANNEL_INFO", "FX_SEND_COUNT",
  "FX_SEND_INFO", "BUFFER_FILL", "STREAM_COUNT", "VOICE_COUNT",
  "TOTAL_VOICE_COUNT", "TOTAL_VOICE_COUNT_MAX", "GLOBAL_INFO",
  "INSTRUMENT", "ENGINE", "ON_DEMAND", "ON_DEMAND_HOLD", "PERSISTENT",
  "AUDIO_OUTPUT_DEVICE_PARAMETER", "AUDIO_OUTPUT_DEVICES",
  "AUDIO_OUTPUT_DEVICE", "AUDIO_OUTPUT_DRIVER_PARAMETER",
  "AUDIO_OUTPUT_DRIVER", "AUDIO_OUTPUT_CHANNEL_PARAMETER",
  "AUDIO_OUTPUT_CHANNEL", "AUDIO_OUTPUT_TYPE",
  "AVAILABLE_MIDI_INPUT_DRIVERS", "MIDI_INPUT_DEVICE_PARAMETER",
  "MIDI_INPUT_PORT_PARAMETER", "MIDI_INPUT_DEVICES", "MIDI_INPUT_DEVICE",
  "MIDI_INPUT_DRIVER_PARAMETER", "MIDI_INSTRUMENT", "MIDI_INSTRUMENTS",
  "MIDI_INSTRUMENT_MAP", "MIDI_INSTRUMENT_MAPS", "MIDI_INPUT_DRIVER",
  "MIDI_INPUT_PORT", "MIDI_INPUT_CHANNEL", "MIDI_INPUT_TYPE", "MIDI_INPUT",
  "MIDI_CONTROLLER", "FX_SEND", "FX_SENDS", "SERVER", "VOLUME", "LEVEL",
  "MUTE", "SOLO", "BYTES", "PERCENTAGE", "RESET", "MISCELLANEOUS", "NAME",
  "ECHO", "QUIT", 0
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
     233,   233,   233,   233,   233,   233,   233,   233,   233,   233,
     233,   234,   234,   234,   234,   234,   234,   234,   234,   234,
     234,   234,   234,   234,   234,   234,   234,   234,   234,   235,
     235,   235,   235,   236,   237,   237,   237,   238,   238,   238,
     238,   238,   238,   238,   238,   238,   238,   238,   238,   238,
     238,   238,   238,   238,   238,   238,   238,   238,   238,   238,
     238,   238,   238,   238,   238,   238,   238,   238,   238,   238,
     238,   239,   239,   239,   239,   239,   239,   239,   239,   239,
     239,   239,   240,   240,   240,   240,   240,   240,   241,   242,
     242,   243,   243,   243,   244,   244,   245,   245,   245,   245,
     245,   245,   245,   245,   245,   245,   245,   245,   245,   245,
     246,   246,   247,   247,   248,   248,   249,   249,   249,   249,
     249,   249,   249,   249,   249,   249,   250,   250,   251,   252,
     252,   252,   253,   254,   255,   256,   257,   257,   258,   259,
     260,   261,   262,   263,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   272,   273,   273,   273,   273,   274,
     274,   275,   275,   276,   276,   276,   277,   277,   278,   278,
     278,   278,   278,   278,   278,   278,   278,   278,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   280,   280,
     280,   280,   280,   280,   280,   280,   280,   280,   280,   280,
     280,   280,   280,   280,   280,   280,   280,   280,   280,   280,
     280,   280,   280,   280,   280,   280,   280,   280,   280,   280,
     280,   280,   280,   280,   280,   280,   280,   280,   280,   280,
     280,   280,   280,   280,   280,   280,   280,   280,   280,   280,
     280,   280,   280,   280,   280,   280,   280,   280,   280,   280,
     280,   280,   280,   280,   280,   280,   280,   280,   280,   280,
     280,   280,   280,   280,   280,   280,   280,   280,   280,   280,
     280,   280,   280,   280,   280,   280,   280,   280,   280,   280,
     280,   280,   280,   280,   280,   280,   280,   280,   280,   280,
     280,   280,   280,   280,   280,   280,   280,   280,   280,   280,
     280,   280,   280,   280,   280,   280,   280,   280,   280,   280,
     280,   280,   280,   280,   280,   280,   280,   280,   280,   280,
     280,   280,   280,   280,   280,   280,   280,   280,   280,   280,
     280,   280,   280,   280,   280,   280,   280,   280,   280,   280,
     280,   280,   280,   280,   280,   280,   280,   280,   280,   280,
     280,   280,   280,   280,   280,   280,   280,   280,   280,   280,
     280,   280,   280,   280,   280,   280,   280,   280,   280,   280,
     280,   280,   280,   280,   280,   280,   280,   280,   280,   280,
     280,   280,   280,   280,   280,   280,   280,   280,   280,   280,
     280,   280,   280,   280,   280,   280,   280,   280,   280,   280,
     280,   280,   280,   280,   280,   280,   280,   281,   281,   281,
     281,   282,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   335,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   352,   353,   354,   355,   356,   357,   358,   359,
     360,   361,   362,   363,   364,   365,   366,   367,   368,   369
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,    16,
      18,    18,    20,     7,     3,     3,     3,     1,     1,     5,
       7,     9,     1,     5,     7,     9,     1,     1,     5,     5,
       7,     9,     7,     9,     1,     5,     7,     5,     5,     5,
       3,     1,     1,     3,     3,     9,     1,     5,     3,     7,
       1,     7,     9,     7,     9,     3,     7,    11,     9,     9,
       3,     3,     5,     3,     5,     3,     5,     7,     3,     3,
       3,     3,     3,     5,     3,     3,     5,     7,     5,     9,
       5,     5,     5,     5,     5,     5,     5,     5,     5,     5,
       0,     2,     3,     5,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     1,     3,     5,     7,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     2,     3,     4,     4,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     1,     1,
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     3,     3,     1,     1,     1,     3,     3,     3,     5,
       5,     6,     7,     4,     4,     3,     4,     7,     9,     6,
       3,     9,    11,     6,     7,    17,    30,     8,     4,    25,
      24,    23,    22,    25,    24,    21,    20,    13,    12,    13,
      12,    11,    12,    11,    17,    21,    11,    10,     6,     9,
      14,    10,    29,    20,    19,    29,    19,    30,    20,    17,
      28,    27,    25,    18,    17,    27,    15,    16,    19,    20,
      17,    15,    18,    15,    10,    15,     7,     8,     6,     6,
       5,     4,     4,     5,    10,     5,    13,     4,     4,     4
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
       0,     0,     0,     0,     0,     0,     1,   454,   455,     2,
       0,     9,   306,   301,   300,   298,   299,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   290,
     292,   293,   294,   295,   296,   297,   302,   303,   304,   305,
     307,   308,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
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
     453,    12,   218,    11,   201,    10,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   456,     0,     0,     0,   457,     0,     0,   458,     0,
       0,     0,     0,   470,     0,     0,     0,     3,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   219,   206,
     220,   221,   222,   223,   224,   225,   226,   227,   291,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   202,
       0,     0,    13,    30,    31,     0,     0,     0,     0,     0,
       0,     0,     0,    16,     0,    77,    82,    94,   101,   102,
       0,    86,     0,     0,     0,     0,     0,    78,     0,    87,
       0,     0,     0,     0,     0,   106,     0,     0,     0,     0,
       0,   110,     0,    14,     0,    15,     0,     0,    27,     0,
       0,     0,     0,    17,     0,     0,     0,    18,     0,     0,
       0,     0,     0,     0,     0,    19,   159,   161,   158,   156,
     160,   157,     0,   164,     0,     0,    20,     0,     0,    21,
       0,     0,     0,     0,     0,    22,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    23,    33,    34,    35,    36,    44,
      45,    46,    47,    37,    41,    42,    43,    40,    39,    38,
      49,    50,    48,    24,    51,    52,    53,    54,    62,    63,
      64,    65,    55,    59,    60,    61,    58,    57,    56,    67,
      68,    66,   448,    25,   447,    26,     0,     0,     0,     0,
     463,   464,   539,     0,     0,     0,     0,     0,     0,   207,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   150,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   450,   449,     0,   460,
       0,     0,     0,   535,     0,     0,   459,     0,     0,     0,
       0,     0,    32,   190,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   209,   210,
     211,   212,   213,   214,   215,   216,   217,     0,   103,   179,
     104,     0,     0,     0,     0,   108,   185,   100,     0,     0,
       0,     0,     0,     0,   129,   130,     0,     0,     0,   123,
     125,     0,   131,   132,     0,     0,     0,     0,     0,   162,
     163,   165,     0,   134,     0,   189,     0,   135,     0,   188,
      74,    75,    76,     0,     0,     0,     0,     0,     0,   115,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   121,   183,     0,   206,
     184,   120,   200,   199,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   128,   461,     0,   469,   473,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   151,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   538,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   462,
       0,     0,     0,     0,   451,   452,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    95,     0,     0,     0,
     154,   155,    97,    98,    99,    88,     0,    83,     0,     0,
       0,    89,     0,     0,   465,   107,    79,     0,     0,     0,
       0,     0,     0,   180,     0,     0,     0,     0,   122,     0,
     124,   126,   182,   133,   187,     0,     0,     0,     0,     0,
       0,   186,     0,   168,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   203,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   498,     0,     0,   528,     0,   529,
     478,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   531,   532,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   537,     0,     0,     0,     0,     0,     0,     0,
     204,   205,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   471,     0,   474,     0,     0,     0,   474,   526,
       0,     0,     0,     0,    96,    84,     0,    92,     0,    80,
       0,    90,   109,     0,     0,     0,    73,   181,     0,     0,
     526,     0,     0,   298,   299,   152,   193,   195,   198,   197,
     196,   127,   192,     0,     0,     0,     0,     0,   166,     0,
       0,     0,     0,     0,   136,   172,     0,   173,   138,   174,
     140,     0,     0,   147,   148,   149,   141,   175,   142,   176,
     177,   143,   178,     0,   144,   145,   146,   111,     0,   113,
       0,   116,     0,   530,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   477,   527,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   472,     0,     0,     0,     0,     0,     0,
     533,     0,    85,    93,    91,    81,   105,     0,     0,     0,
       0,     0,     0,   153,   194,     0,     0,     0,     0,   167,
       0,     0,     0,     0,   137,     0,     0,     0,   112,   114,
       0,     0,     0,   118,   119,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   497,     0,     0,     0,     0,     0,
     466,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   468,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   139,     0,     0,   117,     0,   491,     0,     0,     0,
       0,   496,     0,     0,     0,     0,     0,   493,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     524,     0,     0,     0,     0,     0,   488,     0,   490,     0,
       0,     0,   492,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   467,     0,
       0,     0,   487,   489,     0,     0,   536,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   534,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   521,   516,     0,   516,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   517,     0,     0,    69,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   475,     0,   514,   520,     0,     0,   494,
       0,     0,   514,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   521,   523,   525,     0,     0,     0,     0,     0,
     494,     0,     0,     0,     0,     0,     0,   513,     0,     0,
       0,     0,     0,     0,    70,    71,   191,   169,   170,   171,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   518,     0,   504,   506,     0,     0,
       0,     0,   518,     0,     0,     0,     0,   504,     0,     0,
       0,     0,     0,     0,   509,     0,     0,     0,     0,     0,
       0,     0,   508,   503,     0,     0,     0,     0,     0,   519,
       0,     0,     0,    72,     0,     0,     0,     0,   522,     0,
       0,     0,     0,   486,     0,     0,     0,     0,     0,     0,
       0,   495,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   485,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   508,     0,     0,     0,   482,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   481,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   480,     0,   484,
       0,     0,     0,     0,     0,   512,     0,     0,     0,     0,
     479,   483,     0,     0,     0,     0,     0,   499,     0,     0,
       0,     0,     0,     0,     0,   515,     0,   501,     0,   511,
       0,     0,     0,   510,     0,     0,     0,   505,     0,     0,
     502,   507,   476,     0,   500
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    13,    14,    15,    16,   342,   444,   463,   383,   385,
     419,   353,   425,   393,   485,   388,   397,   416,   679,   640,
     878,   849,   405,   663,   667,  1524,  1074,  1076,  1078,  1086,
    1088,  1091,   628,   872,  1046,   881,   706,   635,   890,   883,
     668,   664,   592,  1525,  1061,  1055,  1056,   711,  1057,  1058,
     708,   272,   636,   274,   483,  1060,   970,    49,    50,    17,
      18,    19,    20,    21,    22,    23,    24,    25,  1090,  1084,
    1085,   641,    26,    27,    28,    29,    30,   343,   355,   356,
     357,   604,   445,   446,   447,   448,   449,   450,   451,   452,
     453,   454,   455,   456,   457,   458,   459,   358,   359,   461,
     417,   360,  1527,  1528,  1529,   427,   361,   362,   363,   364,
     365,   366,   682,   367,   429,   368,   369,   370,   371,   372,
     373,   344,   375,   376,   377,   686,   687,   688,   702,   378,
     379,   380,   381,   703,   690,   691,   850,   851,    31,   462,
     697,   434,    32
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -1118
static const yytype_int16 yypact[] =
{
      57, -1118, -1118,    19,   165,    48,    74,   223,   115,   126,
     132,    60,   178,   172,   -34,  2124, -1118,    16,    16,    16,
      16,    16,    16,    16,    16,    16,    16,    16,    16,    16,
      16,    16, -1118,   233,   280,   299,   242,   306,   309,   333,
     320,   339,   263,   164,   340,   286, -1118, -1118, -1118, -1118,
     145, -1118, -1118, -1118, -1118, -1118, -1118, -1118,   489,   489,
     489,   489,   489,   489,   489,   489,   489, -1118, -1118, -1118,
   -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118,
   -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118,
   -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118,
   -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118,
   -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118,
   -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118,
   -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118,
   -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118,
   -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118,
   -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118,
   -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118,
   -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118,
   -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118,
   -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118,
   -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118,
   -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118,
   -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118,
   -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118,
   -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118,
   -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118,
   -1118,  2789, -1118, -1118, -1118, -1118,   140,   166,   342,   342,
     351,   109,   109,   138,   184,   140,    79,    87,    87,  2346,
     375, -1118,   379,   381,   366, -1118,   369,   386, -1118,   371,
     377,   398,   410, -1118,   397,   416,   407, -1118, -1118, -1118,
   -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118,   489, -1118,
     489,   489,   489,   489,   489,   489,   489,   489, -1118, -1118,
   -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118,
     411,   420, -1118, -1118,    16,   256,   422,   418,   409,   426,
     431,   423,   424, -1118,    16, -1118, -1118, -1118, -1118, -1118,
      16, -1118,    16,    16,    16,    16,    16, -1118,    16, -1118,
      16,    16,    16,    16,    16, -1118,    16,    16,    16,    16,
      16, -1118,   428, -1118,    16, -1118,    16,   432, -1118,    16,
     419,   421,   434, -1118,    16,    16,    16, -1118,    16,    16,
      16,   281,   436,   425,   437, -1118, -1118, -1118, -1118, -1118,
   -1118, -1118,    16, -1118,    16,   433, -1118,    16,    16, -1118,
      16,    16,   430,   449,   445, -1118,    16,    16,    16,    16,
      16,    16,    16,    16,    16,   435,   438,   447,   439,   446,
     448,   440,   450,   451, -1118, -1118, -1118, -1118, -1118, -1118,
   -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118,
   -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118,
   -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118,
   -1118, -1118,  2789,  2346, -1118, -1118,    16,   444,   452,   453,
   -1118, -1118, -1118,   442,   454,   464,   465,   459,   467, -1118,
     475,   473,   120,   474,   501,   502,   497,   441,   504,   487,
     486,   498,   133,   505,   505,   505,   505,   505,   505,   505,
     505,   505,   505,   568,   505,   505,   505,   505,   500,   505,
     507,   495,   500,   509,   568,   511,   456,   513,  2789,  2789,
     500,   500,   500,   500,   515,   519,   457,   517,   568,   500,
     503,     4,  2789,   500,   568,   520,   521,   526,   101,   500,
     500,   500,   500,   522,   144,   255,  3008,   527,   528,   532,
     466,   508,    47,   523,   531,   530,  2789, -1118,   500, -1118,
     535,   533,   537, -1118,   534,   529, -1118,   516,   538,   544,
    2346,  2346, -1118, -1118,   546,   547,   556,   576,   577,   586,
     580,   602,   583,   591,    16,    16,    16,    16,    16,    16,
      16,    16,    16,    16,    16,    16,    16,    16,   489,   489,
     489,   489,   489,   489,   489,   489,   489,   594, -1118, -1118,
   -1118,    16,    16,    16,    16, -1118, -1118, -1118,   598,   595,
     500,    16,    16,   603, -1118, -1118,   604,   592,   605,  2346,
    2346,    16, -1118, -1118,    16,   610,   606,   607,   613, -1118,
   -1118, -1118,   608, -1118,    16, -1118,    16, -1118,    16,  2789,
   -1118, -1118, -1118,   614,   612,   616,   609,   159,   617, -1118,
      16,    16,    16,    16,    16,    16,    16,    16,    16,    16,
      16,    16,    16,    16,    16,    16,   628,    16,   615,   629,
     630,    16,    16,    16,   489,   489, -1118, -1118,   207,    27,
   -1118, -1118,  2789, -1118,   631,   632,   623,   624,   640,   635,
     642,   641,   662,   663, -1118, -1118,   646, -1118, -1118,   658,
     671,   661,   611,  1680,  1902,   664,   665,   666,   667,   673,
     618,   678,   672,   674,   670,   500,    89,   500,   500,  2789,
     500,  2789,  2789,   500,   500,   500,   500,  2789,   500,   676,
     500,  2789,   500,   500,   619,   677,    16, -1118,   500,   621,
     679,   680,   622,  2789,  2789,   500,   500,   681,   683,   690,
     627,   668,   500,   120,   500,   684, -1118,   633,   698,   699,
     685,   694,   500,   500,   500,   500,   500,   500,   500,   500,
     500,   500,   500,   500,  2789,   500,  2789,   500,   695,   500,
     703,   688,   707,   500,   500,   500,   275,   414,   489,   697,
     708,   700,   710,   715,   656,   712,   727,   717,   725, -1118,
     729,   714,   730,   732, -1118, -1118,   682,   735,   738,   740,
     733,   739,   731,   686,   745,   736, -1118,   737,   749,    16,
   -1118, -1118, -1118, -1118, -1118, -1118,  2346,  2789,    16,    16,
      16, -1118,  2346,    16, -1118, -1118,  2789,    16,    16,   746,
     687,   500,    16, -1118,   747,   692,   751,   752,    16,  3227,
      16,    16, -1118, -1118, -1118,   696,   763,   755,   761,   750,
      16, -1118,    16, -1118,   701,   764,   765,   766,   771,   769,
      16,    16,    16,    16,    16,    16,    16,    16,    16,    16,
      16,    16,  3446,    16,  3665,    16,   773,    16,   770,   775,
     772,    16,    16,    16,   489,   489,   489,   716,   767,   783,
     776,   780,   785,   784,   782,   726,   728,   793,   791,   789,
     792,   788,   805,   797, -1118,   806,   798, -1118,   795, -1118,
   -1118,   794,   800,   500,  2789,   500,   500,   500,  2789,   500,
     500,   500,   799,   802,    16,   500,   807,   796,   815,   808,
    2789,  2568,   120,   809,   816,   827,   818,   820,   500,   500,
     821,   823,   825,   778, -1118, -1118,   500,   500,  2789,   500,
     134,   500,   568,  2789,   500,   255,  3008,  3008,  2568,  2789,
    2568,  2789, -1118,   120,   826,   830,   779,   500,   500,   500,
     489,   489,   828,   781,   832,   834,   787,   833,   839,   810,
     824,   817, -1118,   851, -1118,   835,   841,   844,   845,   846,
     102,   848,   855,   863, -1118,  2346,    16, -1118,    16,  2346,
      16, -1118, -1118,   860,   868,   500, -1118, -1118,   866,   865,
   -1118,   871,  3884,   489,   489,   904, -1118,  2789, -1118, -1118,
   -1118, -1118, -1118,   873,   845,   846,   175,   890, -1118,    16,
     875,   211,   829,   888, -1118, -1118,    16, -1118, -1118,  2789,
   -1118,   893,   884, -1118, -1118, -1118, -1118, -1118, -1118, -1118,
   -1118, -1118,  2789,    16, -1118, -1118, -1118,   904,  4103,   904,
    4322, -1118,   831, -1118,   898,    16,    16,    16,   882,   899,
     836,   837,   895,   241,   905,   906,   896,   897,   908,   894,
     900,   910, -1118, -1118,   889,   901,   913,   907,   914,  2789,
    2789,  2789,  2789,   500,   903,   920,    16,   909,   912,   915,
    2568,  2568,   917,   921,   918,   911,   500,   926,   927,   919,
     916,   500,   922,   933,   500,  2568,  2568,   935,   936,   500,
     500,   255,   932,   924,   297,   298,   939,   938,   934,   942,
     945,   948,   940, -1118,   944,   949,   856,   946,   950,   961,
   -1118,   953,    16,  2789,  2789,    16, -1118,   951,   971,  2789,
     959,   967,   965,   904, -1118,   970,   974,   969,   976, -1118,
     981,   978,   979,   243, -1118,  1000,   930,    16,   904,   904,
     983,   994,    16, -1118, -1118,   993,   998,   996,  1001,  1002,
    1004,  1010,   999,  1005,  1015,  1007,  1027,  1017,  1011,  1012,
     177,   963,  1014,  1032,  1018,  1019,  1030,    16,  1023,  1025,
     968,  1028,   977,  1029, -1118,  1031,   980,  1033,  1034,  1035,
   -1118,   568,  1037,  1038,   500,  1040,  1047,  1041,  1057,  1043,
    1061,  1053,  1006,  1048,  1055,  1062,  1070,  1058,  1066,  1060,
    1063,  1067,  1073,    52,  1072,  1016,  1082,  1075, -1118,   120,
    1076,  1071,  1086,  1074,  1088,  1080,  1077,   171,  1083,  1081,
    1084, -1118,  1089,  1068, -1118,  1087, -1118,  1090,  1091,  1094,
    1097, -1118,  1098,  1096,  1092,  1095,  1045, -1118,  1109,  1049,
    1114,  1112,  1117,    54,  1107,  1118,  1123,  1120,  1124,    16,
    1125,  1065,  1126,  1078,  1127,  1128,  1079,  1129,  1113,  1116,
    1085,  1121,  1130,  1131,  1093,  1122, -1118,  1132, -1118,  1142,
    1143,  1136, -1118,  1154,  1144,   354,  1150,  1151,  1152,  1140,
    1156,  1145,  1153,  1155,  1161,  1157,   500,  1159,  1165,  1158,
    1171,  1160,  1162,   356,  1164,  1163,  1167,    51, -1118,  1168,
    1166,  1173, -1118, -1118,  1169,  1170, -1118,  1174,  1172,  1175,
     131,  1178,  1180,  1134,  1186,  1176,  1177,  1179,  1181, -1118,
    1183,    16,  1187,  1191,  1192,  1195,  1197,  1190,  1203,  1208,
    1205,  1196,  1146,  1207,  1204,  1193,  1149,  1209,  1217,  1214,
    1210,  1213,  1182,  1227,  1215,  1220,  1188,  1234,  1233,  1240,
    1239,  1189,    24,  1231, -1118,   255,  1228,  1224,  1247,  1229,
    1249,    28,  1253,  1235,  1255,  1189,    83,  1261,  1245,  1248,
    1262,  1263,  1244,  1264,  1198,  1256,  1258,  1259,  1265,  1250,
    1260,  1257,  1266,  1272,  1267,  1268, -1118,  1269,  1270,    16,
    1274,  1273,  1278,  1283,  1276,  1277,  1284,  1287,  1286,  1271,
    1281,  1279,  1292,  1280,  1291,  1296,   137,  1282,  1302,  1290,
    1303,  1300,  1288, -1118,  1294,  1289,  1236,  1310,  1311,  1242,
       6,  1312, -1118,  1315,  1289,  1313,  1305,  1317,  1251,  1320,
    1307,  1314, -1118, -1118, -1118,  1321,  1254,  1316,  1318,  1325,
   -1118,  1319,  1322,  1324,  1323,  1326,  1309, -1118,  1327,  1329,
    1328,  1332,  1334,  1331,    16, -1118, -1118, -1118, -1118, -1118,
    1333,  1337,  1335,  1344,  1345,  1336,  1339,  1349,  1350,  1351,
     310,  1338,  1354,  1341, -1118,  1352,  1342,  1295,  1346,  1343,
    1364,  1366,  1353,  1367,  1298,  1355,   120, -1118,  1342,  1353,
    1358,  1304,  1370,  1360, -1118,  1365,  1308,  1361,  1368,  1369,
    1363,  1330,  1340, -1118,  1371,  1359,  1347,  1372,  1373, -1118,
    1357,  1380,  1374, -1118,  1340,  1375,  1376,  1383, -1118,   311,
    1377,  1379,  1382, -1118,   313,  1381,  1388,  1384,  1391,  1395,
    1387, -1118,  1394,  1396,  1399,  1402,  1398,  1392,  1400,  1401,
    1393, -1118,  1397,  1403,  1405,  1404,  1348,  1406,  1407,  1408,
    1410,  1411,  1409,  1412, -1118,  1413,  1415,  1416, -1118,  1414,
    1425,  1419,  1431,  1434,  1430,  1435,  1436,  1441,  1423,  1443,
    1442,  1432,  1433, -1118,  1437,  1438,  1448,  1439,  1440,  1428,
    1444,  1447,  1445,  1449,  1453,  1450,  1455, -1118,  1457, -1118,
    1454,  1451,  1446,  1452,  1456, -1118,  1458,  1459,  1464,  1473,
   -1118, -1118,  1474,  1460,  1461,  1463,  1466,  1389,  1462,  1465,
    1468,  1467,  1483,  1484,  1471, -1118,  1485, -1118,  1487, -1118,
    1489,  1477,  1478, -1118,  1482,  1480,  1481, -1118,  1486,  1488,
   -1118, -1118, -1118,  1497, -1118
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118,
   -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118,
    -743, -1118, -1118, -1118, -1118, -1118,  -914, -1117, -1118,   197,
     104, -1118,  -511,  -833,  -991,   192,  -973,  -487,  -955,  -893,
    -729,  -782,   518,  -199, -1118,  -941,   290,  -609,   493,  -546,
     -14,   118,     2,   151,  -200,  -484,   -15,  1470, -1118, -1118,
   -1118, -1118, -1118, -1118, -1118, -1118, -1118, -1118,  -453, -1118,
   -1118,   883, -1118, -1118, -1118, -1118, -1118,  -155,  1241,  1243,
    1246,  -283,  1237,  1252,  1275,  1285,  1293,  1297,  1299,  1301,
    1306,  1356,  1362,  1378,  -258,  -255,  -253,   105, -1118,  1385,
   -1118,  1238, -1118, -1118, -1118, -1118,  1386,  -256, -1118, -1118,
    1390,  -223, -1118,  1620, -1118,  1838,  2063,  -254, -1118,   116,
      50,  -222,  2064, -1118,   972, -1118, -1118, -1118, -1118,    86,
    2285, -1118,  -257, -1118, -1118, -1118, -1118, -1118, -1118,  2281,
   -1118, -1118, -1118
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -219
static const yytype_int16 yytable[] =
{
     275,   892,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   273,   593,   707,
     854,   642,  1094,   644,  1069,   394,   398,   395,   399,   433,
     476,   880,  -218,   477,  1204,   478,   639,   659,   964,  1522,
    1523,    33,  1212,   671,   318,   320,   321,   322,   323,   324,
     325,   326,   327,   651,  1136,   374,   654,  1097,     1,  1099,
       2,  1456,   661,   421,   431,  1456,   670,   665,  1042,   719,
     630,    36,  1403,  1322,  1313,  1080,     3,  1349,     4,     5,
    1093,   645,     6,    43,   720,  1404,  1314,     7,     8,  1405,
    1350,   724,     9,    10,    11,   660,    12,    37,   422,    44,
     340,   672,   423,   391,  1468,  1393,   435,   436,   437,   847,
     424,   438,   439,  1457,  1105,  1106,  1107,  1464,   440,   352,
     676,  1469,   354,   848,   441,   442,  1040,   443,   390,   766,
     420,   426,   677,   391,    40,   486,  1124,  1294,   678,  1125,
     392,   352,  1186,   308,   618,   619,   620,   621,   622,   623,
     624,   625,   626,   436,  1414,    42,  1081,   401,  1507,   402,
     603,   340,   403,   698,  1508,    41,  1082,  1415,  1509,   404,
     441,   341,    46,   443,   699,   700,   319,   319,   319,   319,
     319,   319,   319,   319,   319,   345,   789,   346,  1214,   347,
     348,    47,    48,  1327,   302,    34,  1270,   349,   790,  1193,
    1271,    35,   303,   350,   351,  1328,   352,   347,  1272,  1143,
      45,   415,  1144,   818,  1208,  1209,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   590,   591,   590,   591,
     608,   609,   610,   611,   612,   613,   614,   615,   616,   617,
     270,   631,   632,   633,   634,  1148,   637,   863,  1119,   865,
      38,  -218,  -218,  -218,   605,   291,    39,   606,   846,   607,
     852,   853,   704,   705,   308,   618,   619,   620,   621,   622,
     623,   624,   625,   626,   484,  1167,   868,  1248,  1168,   294,
    1119,   924,    -4,    -4,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   300,   503,   504,   893,   917,   665,
     301,   689,   680,   292,   683,   900,   901,   902,   903,   904,
     905,   906,   907,   908,   909,   910,   911,   305,  1217,  1219,
     544,   504,   293,   306,  1218,  1220,   921,   922,   923,   502,
     389,  1567,  1607,   412,  1612,   681,   684,  1568,  1608,   512,
    1613,   701,   590,   591,   295,   513,   296,   514,   515,   516,
     517,   518,   297,   519,   298,   520,   521,   522,   523,   524,
     304,   525,   526,   527,   528,   529,   299,   396,   400,   531,
      47,   532,   432,   382,   534,  1379,  1380,  1398,  1399,   538,
     539,   540,   387,   541,   542,   543,  1182,  1095,  1096,  1185,
     733,   734,   460,   479,   384,   386,   340,   548,   487,   549,
     488,  1391,   551,   552,   489,   553,   554,   490,   491,   492,
     493,   558,   559,   560,   561,   562,   563,   564,   565,   566,
     925,   494,   339,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   495,   496,   497,   499,   500,   499,   499,
     499,   499,   499,   499,   499,   499,   498,   501,   505,   707,
     506,   507,  1459,   508,   509,   530,   510,   511,   535,   533,
    1237,   537,   545,   536,   547,   550,  1034,   546,   577,   555,
     556,   578,   557,   569,   567,   572,   571,   568,   573,  1083,
     579,   570,   582,   574,   575,   584,   585,   587,  1062,   581,
     580,  1068,   583,   586,   588,   589,   594,  1319,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   271,   308,
     618,   619,   620,   621,   622,   623,   624,   625,   626,   593,
     595,   596,   597,   600,   601,   629,   599,   639,   602,   638,
     598,   643,   603,   646,   629,   648,   629,   655,   656,   658,
     662,   718,   673,   652,   653,   647,   657,   674,   675,   714,
     629,   716,   715,   730,   696,   717,   629,   723,   725,   721,
     727,   692,   693,   694,   695,   729,   726,   710,   713,   722,
     731,   732,   728,   735,   736,   484,   484,   308,   618,   619,
     620,   621,   622,   623,   624,   625,   626,   627,   737,   745,
     746,   747,   748,   749,   750,   751,   752,   753,   754,   755,
     756,   757,   758,   738,   318,   320,   321,   322,   323,   324,
     325,   326,   327,   740,   739,   707,   760,   761,   762,   763,
     741,   742,   743,   744,   759,   764,   767,   768,   765,   771,
     769,   770,   772,   339,   773,   774,   775,   777,   778,   776,
     780,   785,   629,   787,   779,   786,   781,   808,   788,   782,
     791,   783,   811,   784,   810,   821,   820,   812,   819,  1199,
     823,   822,   824,   825,   826,   792,   793,   794,   795,   796,
     797,   798,   799,   800,   801,   802,   803,   804,   805,   806,
     807,   827,   809,   709,   828,   830,   813,   814,   815,   829,
     816,   817,   831,   832,   845,   837,   840,   836,   838,   839,
     833,   842,   843,   876,   889,   844,   864,   841,   869,   870,
     874,   877,   875,   887,   885,   886,   888,   894,   577,   577,
     896,   897,   895,   898,   899,   918,   916,   339,   919,   920,
     927,   928,   929,   930,   931,   933,   319,   319,   319,   319,
     319,   319,   319,   319,   319,   932,   934,   935,   936,   937,
     938,   871,   855,   939,   942,   858,   859,   860,   861,   940,
     629,   943,   629,   944,   867,   945,   946,   947,   949,   950,
     873,   941,   952,   962,   966,   948,   963,   882,   884,   969,
     951,   967,   482,   968,   891,   973,   974,   975,   976,   977,
     980,   981,   982,   983,   984,   665,  1002,  1004,  1005,  1006,
     339,   339,   985,  1013,   926,  1012,  1014,   913,  1015,   915,
    1016,   629,  1017,  1019,  1018,  1020,  1022,  1021,  1023,  1024,
     339,  1026,   319,   319,  1025,  1027,   499,  1028,  1029,  1049,
    1030,  1043,  1032,  1044,   953,  1031,  1033,  1050,  1117,  1048,
    1051,   954,  1063,   955,   956,   957,  1064,   958,   959,  1065,
    1066,  1067,   960,   961,  1070,  1071,  1111,   965,  1072,  1102,
    1103,  1108,  1110,   339,  1116,  1113,   972,  1073,  1104,  1114,
    1109,  1118,  1119,   873,  1121,   978,  1112,   979,  1127,   707,
    1120,  1126,  1122,  1123,  1128,   986,   987,   988,   989,   990,
     991,   992,   993,   994,   995,   996,   997,  1134,   999,  1115,
    1001,  1135,  1003,  1137,  1138,  1139,  1007,  1008,  1009,  1141,
    1010,  1011,  1142,  1145,  1147,  1150,  1152,  1153,  1149,  1158,
    1157,  1162,  1166,  1163,  1169,  1164,  1165,  1170,  1177,  1171,
    1172,  1173,  1174,  1176,   499,   499,   319,  1181,  1175,  1178,
    1179,  1187,  1188,  1198,  1180,  1230,  1205,  1190,  1203,  1045,
    1191,  1216,  1202,  1250,  1192,  1195,  1197,  1036,  1037,  1038,
    1196,   873,  1041,   884,  1200,  1206,  1201,  1047,  1210,  1211,
    1215,  1221,  1223,  1059,  1224,  1226,   576,  1222,  1225,  1227,
    1228,   891,  1233,  1229,  1231,  1234,  1232,  1235,  1075,  1077,
    1236,  1075,   629,  1087,  1089,  1238,  1075,   710,   713,   713,
    1059,  1239,  1059,  1240,  1241,  1243,  1526,   339,   339,   884,
     884,   884,  1242,   339,  1244,  1245,  1246,   339,  1247,  1249,
    1129,  1130,  1252,  1131,  1132,  1133,  1253,  1255,  1256,  1257,
     339,   649,   650,  1258,  1261,  1259,  1260,  1262,  1264,   816,
     817,  1263,   319,   319,   499,   669,  1265,  1047,  1266,  1267,
    1268,  1269,  1273,  1274,  1146,  1275,  1276,  1282,  1277,   712,
    1278,  1151,  1280,   339,  1281,   339,  1284,  1283,  1285,  1287,
    1286,  1288,  1526,  1289,  1290,  1292,  1293,  1296,  1154,  1295,
    1297,  1298,  1299,   482,   482,  1300,  1301,  1303,  1304,   709,
    1159,  1160,  1161,  1306,  1305,  1302,  1307,  1308,  1309,  1311,
    1312,  1317,  1310,  1315,  1333,  1316,  1318,  1320,  1322,  1321,
    1324,  1325,  1323,   709,  1331,  1326,   709,  1329,   709,  1330,
    1339,  1189,  1335,  1332,  1336,  1334,  1337,  1340,   499,   499,
    1338,  1341,  1344,  1342,  1343,  1047,  1346,  1347,  1345,  1348,
    1351,  1352,  1059,  1059,  1353,  1354,  1365,  1355,  1357,  1359,
    1361,  1362,  1364,  1077,  1358,  1366,  1087,  1059,  1059,  1368,
    1372,  1077,   882,   710,  1370,  1374,  1375,  1360,  1363,  1369,
    1373,   319,   319,  1376,  1367,  1377,  1378,  1381,  1382,  1383,
    1384,  1386,  1371,  1385,  1389,  1387,   339,  1393,  1388,  1390,
     339,  1392,  1251,  1395,  1397,  1408,  1407,  1254,  1394,  1401,
    1396,  1413,  1410,   339,  1400,  1402,  1406,  1411,   339,  1409,
    1412,  1416,  1417,  1419,  1427,  1421,  1420,  1422,  1429,  1428,
    1423,  1424,  1279,  1418,  1430,  1426,   576,   576,  1431,  1432,
     339,  1433,  1434,  1437,  1435,  1436,  1439,  1438,  1440,  1441,
    1442,  1443,   669,   339,   856,   857,  1447,  1449,  1444,   339,
     862,   339,  1445,  1089,   866,  1448,  1077,  1451,   709,   709,
    1452,  1453,  1454,  1458,  1460,  1456,   879,   879,  1461,  1462,
    1463,  1446,  1465,   709,   709,  1466,  1467,  1450,  1455,   709,
    1470,  1471,  1472,  1468,  1474,  1475,  1473,  1476,  1477,  1478,
    1481,  1479,  1480,  1482,  1483,  1485,  1492,   912,  1484,   914,
    1488,  1491,  1487,  1486,  1356,  1493,  1494,  1495,  1489,  1496,
    1498,  1497,  1499,  1501,  1500,  1503,  1504,  1502,  1505,  1506,
    1510,  1511,  1512,  1514,  1513,  1518,  1517,  1515,  1516,  1519,
    1520,  1521,  1532,  1530,   339,   339,  1531,  1533,  1534,  1536,
    1535,  1537,  1539,  1540,  1543,  1545,  1538,  1546,  1549,  1541,
    1542,  1207,  1213,  1544,  1555,  1291,  1557,  1583,   891,  1547,
    1558,  1550,  1552,  1553,  1548,  1551,  1554,  1560,  1561,  1559,
    1562,  1563,  1564,  1565,  1566,  1571,  1425,  1569,  1570,  1573,
    1575,  1576,  1572,  1577,  1574,  1578,  1580,  1581,  1584,  1586,
    1579,  1582,  1587,  1585,  1590,  1588,  1593,  1589,  1597,  1601,
    1591,  1592,  1602,  1610,  1600,  1596,  1606,  1615,  1599,  1604,
    1619,  1603,  1605,  1617,  1618,  1614,  1609,  1620,  1622,  1594,
    1611,  1623,  1616,  1621,  1631,  1625,  1628,   710,  1624,  1595,
    1629,  1194,  1626,  1627,   666,  1630,  1598,  1633,  1635,  1642,
    1632,  1637,  1634,  1640,  1490,  1639,  1636,  1035,  1638,  1645,
    1647,  1039,  1641,  1644,  1643,  1646,  1648,  1649,  1650,  1651,
    1652,  1653,  1654,  1052,  1656,  1655,  1657,  1660,  1663,  1658,
    1661,  1659,  1667,  1674,  1673,  1675,  1662,  1666,  1686,  1676,
    1677,  1079,  1664,  1665,  1668,  1672,  1092,  1679,  1669,   712,
     712,  1678,  1098,  1670,  1100,  1671,  1680,  1681,  1682,  1684,
    1687,  1683,  1685,  1688,  1689,  1690,  1691,  1692,  1693,  1556,
    1695,  1694,  1696,  1697,  1698,  1699,  1700,  1701,  1703,  1704,
     307,  1101,   418,  1702,   406,   464,   407,     0,     0,   408,
     685,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     465,     0,     0,   709,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   466,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   467,     0,     0,     0,     0,     0,     0,
       0,   468,     0,     0,     0,   469,     0,   470,     0,   471,
       0,     0,     0,     0,   472,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   879,  1183,  1184,   879,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   473,     0,     0,     0,     0,     0,
     474,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   475,     0,     0,   409,
       0,     0,     0,   480,     0,     0,   428,     0,     0,     0,
       0,     0,   669,   328,    52,    53,    54,    55,    56,   329,
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
     268,   269,   834,   410,   270,   328,    52,    53,    54,    55,
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
     266,   267,   268,   269,   430,   835,   270,    51,    52,    53,
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
     264,   265,   266,   267,   268,   269,   411,   413,   270,   328,
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
     262,   263,   264,   265,   266,   267,   268,   269,   414,   481,
     270,   328,    52,    53,    54,  1053,  1054,    57,    58,    59,
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
     590,   591,   328,    52,    53,    54,    55,    56,   329,   330,
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
     328,   971,    53,    54,    55,    56,   329,   330,   331,   332,
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
     998,    53,    54,    55,    56,   329,   330,   331,   332,   333,
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
     262,   263,   264,   265,   266,   267,   268,   269,   328,  1000,
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
     263,   264,   265,   266,   267,   268,   269,   328,  1140,    53,
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
     264,   265,   266,   267,   268,   269,   328,  1155,    53,    54,
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
     265,   266,   267,   268,   269,   328,  1156,    53,    54,    55,
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
      15,   783,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    15,   502,   565,
     749,   532,   995,   534,   979,   281,   282,   281,   282,   286,
     288,   774,     5,   288,  1151,   288,    32,   548,   871,    33,
      34,    22,  1159,   554,    58,    59,    60,    61,    62,    63,
      64,    65,    66,   540,  1045,   277,   543,   998,     1,  1000,
       3,    37,   549,   285,   286,    37,   553,   551,   961,    22,
     523,    23,    21,    22,    22,   989,    19,    23,    21,    22,
     994,   534,    25,    23,    37,    34,    34,    30,    31,    38,
      36,   578,    35,    36,    37,   548,    39,    23,    19,    39,
      21,   554,    23,    24,    21,    22,    19,    20,    21,    20,
      31,    24,    25,    89,  1007,  1008,  1009,    89,    31,    40,
      19,    38,   277,    34,    37,    38,   959,    40,    19,   640,
     285,   286,    31,    24,    19,   290,    34,  1254,    37,    37,
      31,    40,  1133,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    20,    23,    23,    22,    19,    21,    21,
      27,    21,    24,    19,    27,    39,    32,    36,    31,    31,
      37,    31,     0,    40,    30,    31,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    19,    27,    21,  1161,    23,
      24,   225,   226,    22,    30,    30,    19,    31,    39,  1140,
      23,    36,    38,    37,    38,    34,    40,    23,    31,    34,
      32,    27,    37,     6,  1155,  1156,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,   222,   223,   222,   223,
     513,   514,   515,   516,   517,   518,   519,   520,   521,   522,
     224,   524,   525,   526,   527,    34,   529,   758,    37,   760,
      27,   224,   225,   226,   512,    22,    33,   512,   745,   512,
     747,   748,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,   289,    34,   763,    34,    37,    37,
      37,     6,   225,   226,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    31,    39,    40,   784,   809,   783,
      37,   558,   558,    23,   558,   792,   793,   794,   795,   796,
     797,   798,   799,   800,   801,   802,   803,    31,    21,    21,
      39,    40,    23,    37,    27,    27,   813,   814,   815,   344,
     280,    21,    21,   283,    21,   558,   558,    27,    27,   354,
      27,   564,   222,   223,    38,   360,    37,   362,   363,   364,
     365,   366,    19,   368,    34,   370,   371,   372,   373,   374,
      20,   376,   377,   378,   379,   380,    27,   281,   282,   384,
     225,   386,   286,    31,   389,    21,    22,    21,    22,   394,
     395,   396,    31,   398,   399,   400,  1129,   996,   997,  1132,
     590,   591,   287,   288,   278,   279,    21,   412,    19,   414,
      19,  1356,   417,   418,    38,   420,   421,    38,    22,    38,
      33,   426,   427,   428,   429,   430,   431,   432,   433,   434,
       6,    23,   271,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    23,    37,    19,   318,    26,   320,   321,
     322,   323,   324,   325,   326,   327,    39,    27,    26,   995,
      32,    42,  1425,    27,    23,    27,    33,    33,    39,    27,
    1189,    27,    26,    42,    27,    32,   953,    42,   483,    39,
      21,   486,    27,    26,    39,    27,    30,    39,    38,   990,
      36,    42,    40,    33,    33,    21,    21,    20,   972,    36,
      38,   978,    38,    34,    19,    22,    22,  1279,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    15,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,  1003,
      19,    19,    25,    36,    38,   523,    22,    32,    30,    22,
      89,    22,    27,    22,   532,    22,   534,    22,    19,    22,
      37,    33,    22,   541,   542,    89,    89,    26,    22,    22,
     548,    19,    24,    37,    32,    89,   554,    27,    23,    36,
      23,   559,   560,   561,   562,    36,    33,   565,   566,    38,
      32,    27,    38,    27,    27,   590,   591,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    32,   604,
     605,   606,   607,   608,   609,   610,   611,   612,   613,   614,
     615,   616,   617,    27,   618,   619,   620,   621,   622,   623,
     624,   625,   626,    27,    37,  1161,   631,   632,   633,   634,
      40,    19,    39,    32,    30,    27,   641,   642,    33,    37,
      27,    27,    27,   482,   649,   650,   651,    27,    32,   654,
      27,    27,   640,    27,    37,    33,    38,    19,    39,   664,
      33,   666,    23,   668,    39,    32,    24,    27,    27,  1146,
      20,    37,    27,    21,    23,   680,   681,   682,   683,   684,
     685,   686,   687,   688,   689,   690,   691,   692,   693,   694,
     695,    19,   697,   565,    21,    27,   701,   702,   703,    43,
     704,   705,    21,    32,    24,    30,    23,    33,    32,    32,
      89,    23,    30,    23,    36,    31,    30,    89,    89,    32,
      89,    89,    33,    23,    33,    32,    89,    33,   733,   734,
      22,    22,    89,    38,    30,    22,    31,   576,    40,    22,
      33,    23,    32,    23,    19,    23,   618,   619,   620,   621,
     622,   623,   624,   625,   626,    89,    19,    30,    23,    20,
      36,   766,   750,    23,    19,   753,   754,   755,   756,    27,
     758,    23,   760,    23,   762,    32,    27,    36,    23,    33,
     768,    89,    23,    27,    27,    89,    89,   775,   776,    27,
      43,    89,   289,    32,   782,    89,    23,    32,    27,    39,
      89,    27,    27,    27,    23,  1279,    23,    27,    23,    27,
     649,   650,    33,    36,   818,    89,    23,   805,    32,   807,
      30,   809,    27,    31,    30,    89,    23,    89,    27,    30,
     669,    33,   704,   705,    32,    20,   708,    30,    22,    33,
      32,    32,    38,    31,   849,    40,    36,    22,    21,    32,
      32,   856,    33,   858,   859,   860,    30,   862,   863,    22,
      32,    31,   867,   868,    33,    32,    22,   872,    33,    33,
      30,    33,    30,   712,    40,    32,   881,    89,    89,    30,
      89,    20,    37,   871,    30,   890,    89,   892,    23,  1425,
      39,    33,    37,    37,    21,   900,   901,   902,   903,   904,
     905,   906,   907,   908,   909,   910,   911,    37,   913,    89,
     915,    33,   917,    37,    39,    34,   921,   922,   923,     5,
     924,   925,    39,    23,    39,    27,    23,    33,    89,    21,
      89,    39,    27,    24,    19,    89,    89,    21,    39,    33,
      33,    23,    38,    23,   816,   817,   818,    23,    38,    38,
      27,    38,    22,    32,    37,    89,    24,    38,    32,   964,
      38,    27,    33,    23,    39,    38,    38,   955,   956,   957,
      39,   959,   960,   961,    38,    32,    39,   965,    33,    33,
      38,    32,    38,   971,    32,    27,   483,    39,    33,    39,
      36,   979,    21,    34,    38,    32,    36,    36,   986,   987,
      19,   989,   990,   991,   992,    36,   994,   995,   996,   997,
     998,    34,  1000,    38,    34,    36,  1490,   856,   857,  1007,
    1008,  1009,    38,   862,    38,    34,    38,   866,    39,    19,
    1035,  1036,    39,  1038,  1039,  1040,    32,    34,    30,    33,
     879,   538,   539,    32,    24,    33,    32,    38,    23,  1053,
    1054,    36,   924,   925,   926,   552,    39,  1045,    21,    32,
      39,    39,    89,    39,  1069,    23,    38,    89,    39,   566,
      30,  1076,    39,   912,    39,   914,    89,    39,    39,    89,
      39,    38,  1556,    39,    39,    38,    38,    30,  1093,    39,
      39,    24,    39,   590,   591,    24,    33,    39,    33,   971,
    1105,  1106,  1107,    23,    32,    89,    38,    31,    38,    32,
      27,    19,    39,    31,    36,    89,    31,    31,    22,    38,
      22,    31,    38,   995,    30,    38,   998,    34,  1000,    38,
      22,  1136,    32,    34,    33,    38,    32,    31,  1010,  1011,
      33,    39,    23,    38,    89,  1133,    22,    25,    89,    22,
      33,    23,  1140,  1141,    21,    25,    33,    23,    23,    23,
      23,    23,    23,  1151,    89,    39,  1154,  1155,  1156,    38,
      38,  1159,  1160,  1161,    33,    23,    23,    89,    89,    39,
      38,  1053,  1054,    37,    89,    21,    32,    27,    27,    27,
      40,    36,    89,    27,    23,    32,  1035,    22,    33,    32,
    1039,    32,  1207,    22,    32,    22,    30,  1212,    40,    36,
      40,    26,    32,  1052,    40,    38,    38,    33,  1057,    40,
      38,    33,    32,    27,    23,    38,    40,    38,    23,    27,
      39,    38,  1237,    89,    27,    38,   733,   734,    38,    26,
    1079,    23,    27,    26,    38,    89,    43,    33,    89,    30,
      23,    27,   749,  1092,   751,   752,    19,    27,    38,  1098,
     757,  1100,    39,  1251,   761,    40,  1254,    23,  1140,  1141,
      27,    21,    23,    32,    40,    37,   773,   774,    21,    40,
      21,    89,    19,  1155,  1156,    40,    21,    89,    89,  1161,
      19,    36,    34,    21,    40,    21,    23,    89,    32,    31,
      40,    32,    27,    33,    37,    23,    23,   804,    32,   806,
      31,    27,    34,    36,  1319,    27,    23,    31,    38,    32,
      23,    27,    26,    32,    43,    23,    36,    38,    27,    23,
      38,    19,    32,    23,    21,    89,    37,    39,    34,    19,
      19,    89,    19,    21,  1183,  1184,    21,    32,    21,    19,
      89,    34,    21,    89,    19,    23,    32,    23,    39,    33,
      32,  1154,  1160,    34,    23,  1251,    23,  1556,  1356,    36,
      23,    34,    34,    31,    38,    36,    32,    23,    23,    34,
      34,    32,    23,    23,    23,    34,  1391,    39,    24,    37,
      34,    38,    30,    19,    89,    19,    19,    89,    30,    19,
      37,    36,    32,    89,    33,    30,    33,    89,    39,    42,
      32,    32,    22,    24,    31,    34,    23,    19,    36,    34,
      23,    37,    36,    22,    19,    34,    39,    23,    19,    89,
      38,    19,    38,    27,    19,    33,    33,  1425,    30,    89,
      33,  1141,    32,    32,   551,    32,    89,    89,    31,    24,
      36,    31,    36,    31,  1459,    36,    38,   954,    37,    24,
      19,   958,    39,    39,    38,    36,    22,    27,    23,    23,
      19,    38,    19,   970,    32,    23,    33,    19,    40,    32,
      31,    33,    23,    27,    23,    23,    36,    32,    89,    23,
      22,   988,    38,    36,    31,    31,   993,    23,    38,   996,
     997,    32,   999,    38,  1001,    38,    23,    23,    38,    36,
      38,    40,    36,    38,    36,    38,    23,    23,    37,  1524,
      23,    26,    23,    36,    36,    33,    36,    36,    30,    22,
      50,  1003,   284,    37,   283,   288,   283,    -1,    -1,   283,
     558,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     288,    -1,    -1,  1425,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   288,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   288,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   288,    -1,    -1,    -1,   288,    -1,   288,    -1,   288,
      -1,    -1,    -1,    -1,   288,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1129,  1130,  1131,  1132,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   288,    -1,    -1,    -1,    -1,    -1,
     288,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   288,    -1,    -1,   283,
      -1,    -1,    -1,   288,    -1,    -1,   286,    -1,    -1,    -1,
      -1,    -1,  1189,     3,     4,     5,     6,     7,     8,     9,
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
     220,   221,   222,   283,   224,     3,     4,     5,     6,     7,
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
     218,   219,   220,   221,   286,   223,   224,     3,     4,     5,
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
     216,   217,   218,   219,   220,   221,   283,   283,   224,     3,
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
     214,   215,   216,   217,   218,   219,   220,   221,   283,   288,
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
      36,    37,    39,   228,   229,   230,   231,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   299,   300,   301,   302,
     303,   365,   369,    22,    30,    36,    23,    23,    27,    33,
      19,    39,    23,    23,    39,    32,     0,   225,   226,   284,
     285,     3,     4,     5,     6,     7,     8,     9,    10,    11,
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
     224,   275,   278,   279,   280,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   283,   283,
     283,    22,    23,    23,    37,    38,    37,    19,    34,    27,
      31,    37,    30,    38,    20,    31,    37,   284,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,   277,   278,
     277,   277,   277,   277,   277,   277,   277,   277,     3,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,   280,
      21,    31,   232,   304,   348,    19,    21,    23,    24,    31,
      37,    38,    40,   238,   304,   305,   306,   307,   324,   325,
     328,   333,   334,   335,   336,   337,   338,   340,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,   356,   357,
     358,   359,    31,   235,   346,   236,   346,    31,   242,   347,
      19,    24,    31,   240,   334,   344,   356,   243,   334,   344,
     356,    19,    21,    24,    31,   249,   305,   306,   307,   333,
     340,   343,   347,   349,   357,    27,   244,   327,   328,   237,
     304,   348,    19,    23,    31,   239,   304,   332,   337,   341,
     342,   348,   356,   359,   368,    19,    20,    21,    24,    25,
      31,    37,    38,    40,   233,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   326,   366,   234,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     326,   366,   275,   281,   283,   241,   304,    19,    19,    38,
      38,    22,    38,    33,    23,    23,    37,    19,    39,   278,
      26,    27,   283,    39,    40,    26,    32,    42,    27,    23,
      33,    33,   283,   283,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   283,   283,
      27,   283,   283,    27,   283,    39,    42,    27,   283,   283,
     283,   283,   283,   283,    39,    26,    42,    27,   283,   283,
      32,   283,   283,   283,   283,    39,    21,    27,   283,   283,
     283,   283,   283,   283,   283,   283,   283,    39,    39,    26,
      42,    30,    27,    38,    33,    33,   275,   283,   283,    36,
      38,    36,    40,    38,    21,    21,    34,    20,    19,    22,
     222,   223,   269,   282,    22,    19,    19,    25,    89,    22,
      36,    38,    30,    27,   308,   321,   322,   323,   308,   308,
     308,   308,   308,   308,   308,   308,   308,   308,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,   259,   279,
     295,   308,   308,   308,   308,   264,   279,   308,    22,    32,
     246,   298,   259,    22,   259,   295,    22,    89,    22,   275,
     275,   264,   279,   279,   264,    22,    19,    89,    22,   259,
     295,   264,    37,   250,   268,   282,   298,   251,   267,   275,
     264,   259,   295,    22,    26,    22,    19,    31,    37,   245,
     334,   338,   339,   344,   348,   351,   352,   353,   354,   359,
     361,   362,   279,   279,   279,   279,    32,   367,    19,    30,
      31,   338,   355,   360,     7,     8,   263,   276,   277,   278,
     279,   274,   275,   279,    22,    24,    19,    89,    33,    22,
      37,    36,    38,    27,   264,    23,    33,    23,    38,    36,
      37,    32,    27,   281,   281,    27,    27,    32,    27,    37,
      27,    40,    19,    39,    32,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   283,    30,
     283,   283,   283,   283,    27,    33,   259,   283,   283,    27,
      27,    37,    27,   283,   283,   283,   283,    27,    32,    37,
      27,    38,   283,   283,   283,    27,    33,    27,    39,    27,
      39,    33,   283,   283,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,    19,   283,
      39,    23,    27,   283,   283,   283,   277,   277,     6,    27,
      24,    32,    37,    20,    27,    21,    23,    19,    21,    43,
      27,    21,    32,    89,   222,   223,    33,    30,    32,    32,
      23,    89,    23,    30,    31,    24,   264,    20,    34,   248,
     363,   364,   264,   264,   267,   279,   275,   275,   279,   279,
     279,   279,   275,   259,    30,   259,   275,   279,   264,    89,
      32,   283,   260,   279,    89,    33,    23,    89,   247,   275,
     247,   262,   279,   266,   279,    33,    32,    23,    89,    36,
     265,   279,   268,   264,    33,    89,    22,    22,    38,    30,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   275,   279,   275,   279,    31,   259,    22,    40,
      22,   264,   264,   264,     6,     6,   277,    33,    23,    32,
      23,    19,    89,    23,    19,    30,    23,    20,    36,    23,
      27,    89,    19,    23,    23,    32,    27,    36,    89,    23,
      33,    43,    23,   283,   283,   283,   283,   283,   283,   283,
     283,   283,    27,    89,   260,   283,    27,    89,    32,    27,
     283,     4,   283,    89,    23,    32,    27,    39,   283,   283,
      89,    27,    27,    27,    23,    33,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,     4,   283,
       4,   283,    23,   283,    27,    23,    27,   283,   283,   283,
     277,   277,    89,    36,    23,    32,    30,    27,    30,    31,
      89,    89,    23,    27,    30,    32,    33,    20,    30,    22,
      32,    40,    38,    36,   264,   275,   279,   279,   279,   275,
     260,   279,   266,    32,    31,   283,   261,   279,    32,    33,
      22,    32,   275,     7,     8,   272,   273,   275,   276,   279,
     282,   271,   282,    33,    30,    22,    32,    31,   264,   265,
      33,    32,    33,    89,   253,   279,   254,   279,   255,   275,
     253,    22,    32,   259,   296,   297,   256,   279,   257,   279,
     295,   258,   275,   253,   263,   274,   274,   272,   275,   272,
     275,   269,    33,    30,    89,   266,   266,   266,    33,    89,
      30,    22,    89,    32,    30,    89,    40,    21,    20,    37,
      39,    30,    37,    37,    34,    37,    33,    23,    21,   283,
     283,   283,   283,   283,    37,    33,   261,    37,    39,    34,
       4,     5,    39,    34,    37,    23,   283,    39,    34,    89,
      27,   283,    23,    33,   283,     4,     4,    89,    21,   283,
     283,   283,    39,    24,    89,    89,    27,    34,    37,    19,
      21,    33,    33,    23,    38,    38,    23,    39,    38,    27,
      37,    23,   247,   275,   275,   247,   261,    38,    22,   283,
      38,    38,    39,   272,   273,    38,    39,    38,    32,   264,
      38,    39,    33,    32,   254,    24,    32,   256,   272,   272,
      33,    33,   254,   262,   263,    38,    27,    21,    27,    21,
      27,    32,    39,    38,    32,    33,    27,    39,    36,    34,
      89,    38,    36,    21,    32,    36,    19,   267,    36,    34,
      38,    34,    38,    36,    38,    34,    38,    39,    34,    19,
      23,   283,    39,    32,   283,    34,    30,    33,    32,    33,
      32,    24,    38,    36,    23,    39,    21,    32,    39,    39,
      19,    23,    31,    89,    39,    23,    38,    39,    30,   283,
      39,    39,    89,    39,    89,    39,    39,    89,    38,    39,
      39,   257,    38,    38,   254,    39,    30,    39,    24,    39,
      24,    33,    89,    39,    33,    32,    23,    38,    31,    38,
      39,    32,    27,    22,    34,    31,    89,    19,    31,   268,
      31,    38,    22,    38,    22,    31,    38,    22,    34,    34,
      38,    30,    34,    36,    38,    32,    33,    32,    33,    22,
      31,    39,    38,    89,    23,    89,    22,    25,    22,    23,
      36,    33,    23,    21,    25,    23,   283,    23,    89,    23,
      89,    23,    23,    89,    23,    33,    39,    89,    38,    39,
      33,    89,    38,    38,    23,    23,    37,    21,    32,    21,
      22,    27,    27,    27,    40,    27,    36,    32,    33,    23,
      32,   265,    32,    22,    40,    22,    40,    32,    21,    22,
      40,    36,    38,    21,    34,    38,    38,    30,    22,    40,
      32,    33,    38,    26,    23,    36,    33,    32,    89,    27,
      40,    38,    38,    39,    38,   283,    38,    23,    27,    23,
      27,    38,    26,    23,    27,    38,    89,    26,    33,    43,
      89,    30,    23,    27,    38,    39,    89,    19,    40,    27,
      89,    23,    27,    21,    23,    89,    37,    89,    32,   263,
      40,    21,    40,    21,    89,    19,    40,    21,    21,    38,
      19,    36,    34,    23,    40,    21,    89,    32,    31,    32,
      27,    40,    33,    37,    32,    23,    36,    34,    31,    38,
     283,    27,    23,    27,    23,    31,    32,    27,    23,    26,
      43,    32,    38,    23,    36,    27,    23,    21,    27,    31,
      38,    19,    32,    21,    23,    39,    34,    37,    89,    19,
      19,    89,    33,    34,   252,   270,   282,   329,   330,   331,
      21,    21,    19,    32,    21,    89,    19,    34,    32,    21,
      89,    33,    32,    19,    34,    23,    23,    36,    38,    39,
      34,    36,    34,    31,    32,    23,   283,    23,    23,    34,
      23,    23,    34,    32,    23,    23,    23,    21,    27,    39,
      24,    34,    30,    37,    89,    34,    38,    19,    19,    37,
      19,    89,    36,   270,    30,    89,    19,    32,    30,    89,
      33,    32,    32,    33,    89,    89,    34,    39,    89,    36,
      31,    42,    22,    37,    34,    36,    23,    21,    27,    39,
      24,    38,    21,    27,    34,    19,    38,    22,    19,    23,
      23,    27,    19,    19,    30,    33,    32,    32,    33,    33,
      32,    19,    36,    89,    36,    31,    38,    31,    37,    36,
      31,    39,    24,    38,    39,    24,    36,    19,    22,    27,
      23,    23,    19,    38,    19,    23,    32,    33,    32,    33,
      19,    31,    36,    40,    38,    36,    32,    23,    31,    38,
      38,    38,    31,    23,    27,    23,    23,    22,    32,    23,
      23,    23,    38,    40,    36,    36,    89,    38,    38,    36,
      38,    23,    23,    37,    26,    23,    23,    36,    36,    33,
      36,    36,    37,    30,    22
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
    { (yyval.String) = LSCPSERVER->QueryDatabase((yyvsp[(3) - (3)].String));                     }
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
    { (yyval.String) = LSCPSERVER->AddMidiInstrumentMap();                }
    break;

  case 32:
#line 135 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddMidiInstrumentMap((yyvsp[(3) - (3)].String));              }
    break;

  case 33:
#line 138 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_audio_device_count);   }
    break;

  case 34:
#line 139 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_audio_device_info);    }
    break;

  case 35:
#line 140 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_device_count);    }
    break;

  case 36:
#line 141 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_device_info);     }
    break;

  case 37:
#line 142 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_channel_count);        }
    break;

  case 38:
#line 143 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_voice_count);          }
    break;

  case 39:
#line 144 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_stream_count);         }
    break;

  case 40:
#line 145 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_buffer_fill);          }
    break;

  case 41:
#line 146 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_channel_info);         }
    break;

  case 42:
#line 147 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_fx_send_count);        }
    break;

  case 43:
#line 148 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_fx_send_info);         }
    break;

  case 44:
#line 149 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_instr_map_count); }
    break;

  case 45:
#line 150 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_instr_map_info);  }
    break;

  case 46:
#line 151 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_instr_count);     }
    break;

  case 47:
#line 152 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_instr_info);      }
    break;

  case 48:
#line 153 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_misc);                 }
    break;

  case 49:
#line 154 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_total_voice_count);    }
    break;

  case 50:
#line 155 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_global_info);          }
    break;

  case 51:
#line 158 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_audio_device_count);   }
    break;

  case 52:
#line 159 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_audio_device_info);    }
    break;

  case 53:
#line 160 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_device_count);    }
    break;

  case 54:
#line 161 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_device_info);     }
    break;

  case 55:
#line 162 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_channel_count);        }
    break;

  case 56:
#line 163 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_voice_count);          }
    break;

  case 57:
#line 164 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_stream_count);         }
    break;

  case 58:
#line 165 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_buffer_fill);          }
    break;

  case 59:
#line 166 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_channel_info);         }
    break;

  case 60:
#line 167 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_fx_send_count);        }
    break;

  case 61:
#line 168 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_fx_send_info);         }
    break;

  case 62:
#line 169 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_instr_map_count); }
    break;

  case 63:
#line 170 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_instr_map_info);  }
    break;

  case 64:
#line 171 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_instr_count);     }
    break;

  case 65:
#line 172 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_instr_info);      }
    break;

  case 66:
#line 173 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_misc);                 }
    break;

  case 67:
#line 174 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_total_voice_count);    }
    break;

  case 68:
#line 175 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_global_info);          }
    break;

  case 69:
#line 178 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping((yyvsp[(4) - (16)].Number),(yyvsp[(6) - (16)].Number),(yyvsp[(8) - (16)].Number),(yyvsp[(10) - (16)].String),(yyvsp[(12) - (16)].String),(yyvsp[(14) - (16)].Number),(yyvsp[(16) - (16)].Dotnum),MidiInstrumentMapper::VOID,"",(yyvsp[(3) - (16)].Bool)); }
    break;

  case 70:
#line 179 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping((yyvsp[(4) - (18)].Number),(yyvsp[(6) - (18)].Number),(yyvsp[(8) - (18)].Number),(yyvsp[(10) - (18)].String),(yyvsp[(12) - (18)].String),(yyvsp[(14) - (18)].Number),(yyvsp[(16) - (18)].Dotnum),(yyvsp[(18) - (18)].LoadMode),"",(yyvsp[(3) - (18)].Bool)); }
    break;

  case 71:
#line 180 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping((yyvsp[(4) - (18)].Number),(yyvsp[(6) - (18)].Number),(yyvsp[(8) - (18)].Number),(yyvsp[(10) - (18)].String),(yyvsp[(12) - (18)].String),(yyvsp[(14) - (18)].Number),(yyvsp[(16) - (18)].Dotnum),MidiInstrumentMapper::VOID,(yyvsp[(18) - (18)].String),(yyvsp[(3) - (18)].Bool)); }
    break;

  case 72:
#line 181 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping((yyvsp[(4) - (20)].Number),(yyvsp[(6) - (20)].Number),(yyvsp[(8) - (20)].Number),(yyvsp[(10) - (20)].String),(yyvsp[(12) - (20)].String),(yyvsp[(14) - (20)].Number),(yyvsp[(16) - (20)].Dotnum),(yyvsp[(18) - (20)].LoadMode),(yyvsp[(20) - (20)].String),(yyvsp[(3) - (20)].Bool)); }
    break;

  case 73:
#line 184 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveMIDIInstrumentMapping((yyvsp[(3) - (7)].Number),(yyvsp[(5) - (7)].Number),(yyvsp[(7) - (7)].Number)); }
    break;

  case 74:
#line 187 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveChannel((yyvsp[(3) - (3)].Number));             }
    break;

  case 75:
#line 188 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveMidiInstrumentMap((yyvsp[(3) - (3)].Number));   }
    break;

  case 76:
#line 189 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveAllMidiInstrumentMaps(); }
    break;

  case 77:
#line 192 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAvailableEngines();                          }
    break;

  case 78:
#line 193 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAvailableMidiInputDrivers();                 }
    break;

  case 79:
#line 194 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDriverInfo((yyvsp[(5) - (5)].String));                     }
    break;

  case 80:
#line 195 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDriverParameterInfo((yyvsp[(5) - (7)].String), (yyvsp[(7) - (7)].String));        }
    break;

  case 81:
#line 196 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDriverParameterInfo((yyvsp[(5) - (9)].String), (yyvsp[(7) - (9)].String), (yyvsp[(9) - (9)].KeyValList));    }
    break;

  case 82:
#line 197 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAvailableAudioOutputDrivers();               }
    break;

  case 83:
#line 198 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDriverInfo((yyvsp[(5) - (5)].String));                   }
    break;

  case 84:
#line 199 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDriverParameterInfo((yyvsp[(5) - (7)].String), (yyvsp[(7) - (7)].String));      }
    break;

  case 85:
#line 200 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDriverParameterInfo((yyvsp[(5) - (9)].String), (yyvsp[(7) - (9)].String), (yyvsp[(9) - (9)].KeyValList));  }
    break;

  case 86:
#line 201 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDeviceCount();                    }
    break;

  case 87:
#line 202 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDeviceCount();                      }
    break;

  case 88:
#line 203 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDeviceInfo((yyvsp[(5) - (5)].Number));                   }
    break;

  case 89:
#line 204 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDeviceInfo((yyvsp[(5) - (5)].Number));                     }
    break;

  case 90:
#line 205 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputPortInfo((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number));                   }
    break;

  case 91:
#line 206 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputPortParameterInfo((yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].Number), (yyvsp[(9) - (9)].String));      }
    break;

  case 92:
#line 207 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputChannelInfo((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number));              }
    break;

  case 93:
#line 208 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputChannelParameterInfo((yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].Number), (yyvsp[(9) - (9)].String)); }
    break;

  case 94:
#line 209 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetChannels();                                  }
    break;

  case 95:
#line 210 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetChannelInfo((yyvsp[(5) - (5)].Number));                             }
    break;

  case 96:
#line 211 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetBufferFill((yyvsp[(5) - (7)].FillResponse), (yyvsp[(7) - (7)].Number));                          }
    break;

  case 97:
#line 212 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetStreamCount((yyvsp[(5) - (5)].Number));                             }
    break;

  case 98:
#line 213 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetVoiceCount((yyvsp[(5) - (5)].Number));                              }
    break;

  case 99:
#line 214 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetEngineInfo((yyvsp[(5) - (5)].String));                              }
    break;

  case 100:
#line 215 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetServerInfo();                                }
    break;

  case 101:
#line 216 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetTotalVoiceCount();                                }
    break;

  case 102:
#line 217 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetTotalVoiceCountMax();                        }
    break;

  case 103:
#line 218 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInstrumentMappings((yyvsp[(3) - (3)].Number));                  }
    break;

  case 104:
#line 219 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAllMidiInstrumentMappings();                 }
    break;

  case 105:
#line 220 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInstrumentMapping((yyvsp[(5) - (9)].Number),(yyvsp[(7) - (9)].Number),(yyvsp[(9) - (9)].Number));             }
    break;

  case 106:
#line 221 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInstrumentMaps();                        }
    break;

  case 107:
#line 222 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInstrumentMap((yyvsp[(5) - (5)].Number));                       }
    break;

  case 108:
#line 223 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetFxSends((yyvsp[(3) - (3)].Number));                                 }
    break;

  case 109:
#line 224 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetFxSendInfo((yyvsp[(5) - (7)].Number),(yyvsp[(7) - (7)].Number));                           }
    break;

  case 110:
#line 225 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetGlobalVolume();                              }
    break;

  case 111:
#line 228 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputDeviceParameter((yyvsp[(3) - (7)].Number), (yyvsp[(5) - (7)].String), (yyvsp[(7) - (7)].String));      }
    break;

  case 112:
#line 229 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputChannelParameter((yyvsp[(3) - (9)].Number), (yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].String), (yyvsp[(9) - (9)].String)); }
    break;

  case 113:
#line 230 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMidiInputDeviceParameter((yyvsp[(3) - (7)].Number), (yyvsp[(5) - (7)].String), (yyvsp[(7) - (7)].String));        }
    break;

  case 114:
#line 231 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMidiInputPortParameter((yyvsp[(3) - (9)].Number), (yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].String), (yyvsp[(9) - (9)].String));      }
    break;

  case 115:
#line 232 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                         }
    break;

  case 116:
#line 233 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMidiInstrumentMapName((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].String));               }
    break;

  case 117:
#line 234 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetFxSendAudioOutputChannel((yyvsp[(5) - (11)].Number),(yyvsp[(7) - (11)].Number),(yyvsp[(9) - (11)].Number),(yyvsp[(11) - (11)].Number)); }
    break;

  case 118:
#line 235 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetFxSendMidiController((yyvsp[(5) - (9)].Number),(yyvsp[(7) - (9)].Number),(yyvsp[(9) - (9)].Number));              }
    break;

  case 119:
#line 236 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetFxSendLevel((yyvsp[(5) - (9)].Number),(yyvsp[(7) - (9)].Number),(yyvsp[(9) - (9)].Dotnum));                       }
    break;

  case 120:
#line 237 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetEcho((yyparse_param_t*) yyparse_param, (yyvsp[(3) - (3)].Dotnum));  }
    break;

  case 121:
#line 238 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetGlobalVolume((yyvsp[(3) - (3)].Dotnum));                            }
    break;

  case 122:
#line 241 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateAudioOutputDevice((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].KeyValList)); }
    break;

  case 123:
#line 242 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateAudioOutputDevice((yyvsp[(3) - (3)].String));    }
    break;

  case 124:
#line 243 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateMidiInputDevice((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].KeyValList));   }
    break;

  case 125:
#line 244 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateMidiInputDevice((yyvsp[(3) - (3)].String));      }
    break;

  case 126:
#line 245 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateFxSend((yyvsp[(3) - (5)].Number),(yyvsp[(5) - (5)].Number));            }
    break;

  case 127:
#line 246 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateFxSend((yyvsp[(3) - (7)].Number),(yyvsp[(5) - (7)].Number),(yyvsp[(7) - (7)].String)); }
    break;

  case 128:
#line 249 "lscp.y"
    { (yyval.String) = LSCPSERVER->ResetChannel((yyvsp[(3) - (3)].Number)); }
    break;

  case 129:
#line 252 "lscp.y"
    { (yyval.String) = LSCPSERVER->ClearMidiInstrumentMappings((yyvsp[(3) - (3)].Number));  }
    break;

  case 130:
#line 253 "lscp.y"
    { (yyval.String) = LSCPSERVER->ClearAllMidiInstrumentMappings(); }
    break;

  case 131:
#line 256 "lscp.y"
    { (yyval.String) = LSCPSERVER->DestroyAudioOutputDevice((yyvsp[(3) - (3)].Number)); }
    break;

  case 132:
#line 257 "lscp.y"
    { (yyval.String) = LSCPSERVER->DestroyMidiInputDevice((yyvsp[(3) - (3)].Number));   }
    break;

  case 133:
#line 258 "lscp.y"
    { (yyval.String) = LSCPSERVER->DestroyFxSend((yyvsp[(3) - (5)].Number),(yyvsp[(5) - (5)].Number)); }
    break;

  case 134:
#line 261 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String); }
    break;

  case 135:
#line 262 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String); }
    break;

  case 136:
#line 265 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputDevice((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));      }
    break;

  case 137:
#line 266 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputChannel((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number), (yyvsp[(3) - (7)].Number)); }
    break;

  case 138:
#line 267 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputType((yyvsp[(5) - (5)].String), (yyvsp[(3) - (5)].Number));        }
    break;

  case 139:
#line 268 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInput((yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].Number), (yyvsp[(9) - (9)].Number), (yyvsp[(3) - (9)].Number));      }
    break;

  case 140:
#line 269 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputDevice((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));        }
    break;

  case 141:
#line 270 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputPort((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));          }
    break;

  case 142:
#line 271 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputChannel((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));       }
    break;

  case 143:
#line 272 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputType((yyvsp[(5) - (5)].String), (yyvsp[(3) - (5)].Number));          }
    break;

  case 144:
#line 273 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetVolume((yyvsp[(5) - (5)].Dotnum), (yyvsp[(3) - (5)].Number));                 }
    break;

  case 145:
#line 274 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMute((yyvsp[(5) - (5)].Dotnum), (yyvsp[(3) - (5)].Number));            }
    break;

  case 146:
#line 275 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelSolo((yyvsp[(5) - (5)].Dotnum), (yyvsp[(3) - (5)].Number));            }
    break;

  case 147:
#line 276 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMap((yyvsp[(3) - (5)].Number), (yyvsp[(5) - (5)].Number));             }
    break;

  case 148:
#line 277 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMap((yyvsp[(3) - (5)].Number), -1);             }
    break;

  case 149:
#line 278 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMap((yyvsp[(3) - (5)].Number), -2);             }
    break;

  case 150:
#line 281 "lscp.y"
    { (yyval.Bool) = true;  }
    break;

  case 151:
#line 282 "lscp.y"
    { (yyval.Bool) = false; }
    break;

  case 152:
#line 285 "lscp.y"
    { (yyval.KeyValList)[(yyvsp[(1) - (3)].String)] = (yyvsp[(3) - (3)].String);          }
    break;

  case 153:
#line 286 "lscp.y"
    { (yyval.KeyValList) = (yyvsp[(1) - (5)].KeyValList); (yyval.KeyValList)[(yyvsp[(3) - (5)].String)] = (yyvsp[(5) - (5)].String); }
    break;

  case 154:
#line 289 "lscp.y"
    { (yyval.FillResponse) = fill_response_bytes;      }
    break;

  case 155:
#line 290 "lscp.y"
    { (yyval.FillResponse) = fill_response_percentage; }
    break;

  case 156:
#line 293 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDevices();           }
    break;

  case 157:
#line 294 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDevices();             }
    break;

  case 158:
#line 295 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListChannels();                    }
    break;

  case 159:
#line 296 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableEngines();            }
    break;

  case 160:
#line 297 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableMidiInputDrivers();   }
    break;

  case 161:
#line 298 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableAudioOutputDrivers(); }
    break;

  case 162:
#line 299 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListMidiInstrumentMappings((yyvsp[(3) - (3)].Number));    }
    break;

  case 163:
#line 300 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAllMidiInstrumentMappings();   }
    break;

  case 164:
#line 301 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListMidiInstrumentMaps();          }
    break;

  case 165:
#line 302 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListFxSends((yyvsp[(3) - (3)].Number));                   }
    break;

  case 166:
#line 305 "lscp.y"
    { (yyval.String) = LSCPSERVER->LoadInstrument((yyvsp[(1) - (5)].String), (yyvsp[(3) - (5)].Number), (yyvsp[(5) - (5)].Number));       }
    break;

  case 167:
#line 306 "lscp.y"
    { (yyval.String) = LSCPSERVER->LoadInstrument((yyvsp[(3) - (7)].String), (yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number), true); }
    break;

  case 168:
#line 309 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetEngineType((yyvsp[(1) - (3)].String), (yyvsp[(3) - (3)].Number)); }
    break;

  case 169:
#line 312 "lscp.y"
    { (yyval.LoadMode) = MidiInstrumentMapper::ON_DEMAND;      }
    break;

  case 170:
#line 313 "lscp.y"
    { (yyval.LoadMode) = MidiInstrumentMapper::ON_DEMAND_HOLD; }
    break;

  case 171:
#line 314 "lscp.y"
    { (yyval.LoadMode) = MidiInstrumentMapper::PERSISTENT;     }
    break;

  case 177:
#line 330 "lscp.y"
    { (yyval.Number) = 16; }
    break;

  case 184:
#line 349 "lscp.y"
    { (yyval.Dotnum) = (yyvsp[(1) - (1)].Number); }
    break;

  case 194:
#line 377 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (3)].String) + "," + (yyvsp[(3) - (3)].String); }
    break;

  case 197:
#line 382 "lscp.y"
    { std::stringstream ss; ss << "\'" << (yyvsp[(1) - (1)].Number) << "\'"; (yyval.String) = ss.str(); }
    break;

  case 198:
#line 383 "lscp.y"
    { std::stringstream ss; ss << "\'" << (yyvsp[(1) - (1)].Dotnum) << "\'"; (yyval.String) = ss.str(); }
    break;

  case 199:
#line 391 "lscp.y"
    { (yyval.Dotnum) = (yyvsp[(1) - (1)].Number); }
    break;

  case 200:
#line 392 "lscp.y"
    { (yyval.Dotnum) = -1; }
    break;

  case 201:
#line 395 "lscp.y"
    { std::string s; s = (yyvsp[(1) - (1)].Char); (yyval.String) = s; }
    break;

  case 202:
#line 396 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + (yyvsp[(2) - (2)].Char);                  }
    break;

  case 203:
#line 399 "lscp.y"
    { (yyval.Dotnum) = atof(String((yyvsp[(1) - (3)].String) + "." + (yyvsp[(3) - (3)].String)).c_str());                         }
    break;

  case 204:
#line 400 "lscp.y"
    { String s = "+"; s += (yyvsp[(2) - (4)].String); s += "."; s += (yyvsp[(4) - (4)].String); (yyval.Dotnum) = atof(s.c_str()); }
    break;

  case 205:
#line 401 "lscp.y"
    { (yyval.Dotnum) = atof(String("-" + (yyvsp[(2) - (4)].String) + "." + (yyvsp[(4) - (4)].String)).c_str());                   }
    break;

  case 206:
#line 405 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (1)].Char);      }
    break;

  case 207:
#line 406 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + (yyvsp[(2) - (2)].Char); }
    break;

  case 208:
#line 409 "lscp.y"
    { (yyval.Char) = '0'; }
    break;

  case 209:
#line 410 "lscp.y"
    { (yyval.Char) = '1'; }
    break;

  case 210:
#line 411 "lscp.y"
    { (yyval.Char) = '2'; }
    break;

  case 211:
#line 412 "lscp.y"
    { (yyval.Char) = '3'; }
    break;

  case 212:
#line 413 "lscp.y"
    { (yyval.Char) = '4'; }
    break;

  case 213:
#line 414 "lscp.y"
    { (yyval.Char) = '5'; }
    break;

  case 214:
#line 415 "lscp.y"
    { (yyval.Char) = '6'; }
    break;

  case 215:
#line 416 "lscp.y"
    { (yyval.Char) = '7'; }
    break;

  case 216:
#line 417 "lscp.y"
    { (yyval.Char) = '8'; }
    break;

  case 217:
#line 418 "lscp.y"
    { (yyval.Char) = '9'; }
    break;

  case 218:
#line 421 "lscp.y"
    { (yyval.Number) = atoi(String(1, (yyvsp[(1) - (1)].Char)).c_str());      }
    break;

  case 219:
#line 422 "lscp.y"
    { (yyval.Number) = atoi(String(String("1") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 220:
#line 423 "lscp.y"
    { (yyval.Number) = atoi(String(String("2") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 221:
#line 424 "lscp.y"
    { (yyval.Number) = atoi(String(String("3") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 222:
#line 425 "lscp.y"
    { (yyval.Number) = atoi(String(String("4") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 223:
#line 426 "lscp.y"
    { (yyval.Number) = atoi(String(String("5") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 224:
#line 427 "lscp.y"
    { (yyval.Number) = atoi(String(String("6") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 225:
#line 428 "lscp.y"
    { (yyval.Number) = atoi(String(String("7") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 226:
#line 429 "lscp.y"
    { (yyval.Number) = atoi(String(String("8") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 227:
#line 430 "lscp.y"
    { (yyval.Number) = atoi(String(String("9") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 228:
#line 432 "lscp.y"
    { (yyval.Char) = 'A'; }
    break;

  case 229:
#line 432 "lscp.y"
    { (yyval.Char) = 'B'; }
    break;

  case 230:
#line 432 "lscp.y"
    { (yyval.Char) = 'C'; }
    break;

  case 231:
#line 432 "lscp.y"
    { (yyval.Char) = 'D'; }
    break;

  case 232:
#line 432 "lscp.y"
    { (yyval.Char) = 'E'; }
    break;

  case 233:
#line 432 "lscp.y"
    { (yyval.Char) = 'F'; }
    break;

  case 234:
#line 432 "lscp.y"
    { (yyval.Char) = 'G'; }
    break;

  case 235:
#line 432 "lscp.y"
    { (yyval.Char) = 'H'; }
    break;

  case 236:
#line 432 "lscp.y"
    { (yyval.Char) = 'I'; }
    break;

  case 237:
#line 432 "lscp.y"
    { (yyval.Char) = 'J'; }
    break;

  case 238:
#line 432 "lscp.y"
    { (yyval.Char) = 'K'; }
    break;

  case 239:
#line 432 "lscp.y"
    { (yyval.Char) = 'L'; }
    break;

  case 240:
#line 432 "lscp.y"
    { (yyval.Char) = 'M'; }
    break;

  case 241:
#line 432 "lscp.y"
    { (yyval.Char) = 'N'; }
    break;

  case 242:
#line 432 "lscp.y"
    { (yyval.Char) = 'O'; }
    break;

  case 243:
#line 432 "lscp.y"
    { (yyval.Char) = 'P'; }
    break;

  case 244:
#line 432 "lscp.y"
    { (yyval.Char) = 'Q'; }
    break;

  case 245:
#line 432 "lscp.y"
    { (yyval.Char) = 'R'; }
    break;

  case 246:
#line 432 "lscp.y"
    { (yyval.Char) = 'S'; }
    break;

  case 247:
#line 432 "lscp.y"
    { (yyval.Char) = 'T'; }
    break;

  case 248:
#line 432 "lscp.y"
    { (yyval.Char) = 'U'; }
    break;

  case 249:
#line 432 "lscp.y"
    { (yyval.Char) = 'V'; }
    break;

  case 250:
#line 432 "lscp.y"
    { (yyval.Char) = 'W'; }
    break;

  case 251:
#line 432 "lscp.y"
    { (yyval.Char) = 'X'; }
    break;

  case 252:
#line 432 "lscp.y"
    { (yyval.Char) = 'Y'; }
    break;

  case 253:
#line 432 "lscp.y"
    { (yyval.Char) = 'Z'; }
    break;

  case 254:
#line 433 "lscp.y"
    { (yyval.Char) = 'a'; }
    break;

  case 255:
#line 433 "lscp.y"
    { (yyval.Char) = 'b'; }
    break;

  case 256:
#line 433 "lscp.y"
    { (yyval.Char) = 'c'; }
    break;

  case 257:
#line 433 "lscp.y"
    { (yyval.Char) = 'd'; }
    break;

  case 258:
#line 433 "lscp.y"
    { (yyval.Char) = 'e'; }
    break;

  case 259:
#line 433 "lscp.y"
    { (yyval.Char) = 'f'; }
    break;

  case 260:
#line 433 "lscp.y"
    { (yyval.Char) = 'g'; }
    break;

  case 261:
#line 433 "lscp.y"
    { (yyval.Char) = 'h'; }
    break;

  case 262:
#line 433 "lscp.y"
    { (yyval.Char) = 'i'; }
    break;

  case 263:
#line 433 "lscp.y"
    { (yyval.Char) = 'j'; }
    break;

  case 264:
#line 433 "lscp.y"
    { (yyval.Char) = 'k'; }
    break;

  case 265:
#line 433 "lscp.y"
    { (yyval.Char) = 'l'; }
    break;

  case 266:
#line 433 "lscp.y"
    { (yyval.Char) = 'm'; }
    break;

  case 267:
#line 433 "lscp.y"
    { (yyval.Char) = 'n'; }
    break;

  case 268:
#line 433 "lscp.y"
    { (yyval.Char) = 'o'; }
    break;

  case 269:
#line 433 "lscp.y"
    { (yyval.Char) = 'p'; }
    break;

  case 270:
#line 433 "lscp.y"
    { (yyval.Char) = 'q'; }
    break;

  case 271:
#line 433 "lscp.y"
    { (yyval.Char) = 'r'; }
    break;

  case 272:
#line 433 "lscp.y"
    { (yyval.Char) = 's'; }
    break;

  case 273:
#line 433 "lscp.y"
    { (yyval.Char) = 't'; }
    break;

  case 274:
#line 433 "lscp.y"
    { (yyval.Char) = 'u'; }
    break;

  case 275:
#line 433 "lscp.y"
    { (yyval.Char) = 'v'; }
    break;

  case 276:
#line 433 "lscp.y"
    { (yyval.Char) = 'w'; }
    break;

  case 277:
#line 433 "lscp.y"
    { (yyval.Char) = 'x'; }
    break;

  case 278:
#line 433 "lscp.y"
    { (yyval.Char) = 'y'; }
    break;

  case 279:
#line 433 "lscp.y"
    { (yyval.Char) = 'z'; }
    break;

  case 280:
#line 434 "lscp.y"
    { (yyval.Char) = '0'; }
    break;

  case 281:
#line 434 "lscp.y"
    { (yyval.Char) = '1'; }
    break;

  case 282:
#line 434 "lscp.y"
    { (yyval.Char) = '2'; }
    break;

  case 283:
#line 434 "lscp.y"
    { (yyval.Char) = '3'; }
    break;

  case 284:
#line 434 "lscp.y"
    { (yyval.Char) = '4'; }
    break;

  case 285:
#line 434 "lscp.y"
    { (yyval.Char) = '5'; }
    break;

  case 286:
#line 434 "lscp.y"
    { (yyval.Char) = '6'; }
    break;

  case 287:
#line 434 "lscp.y"
    { (yyval.Char) = '7'; }
    break;

  case 288:
#line 434 "lscp.y"
    { (yyval.Char) = '8'; }
    break;

  case 289:
#line 434 "lscp.y"
    { (yyval.Char) = '9'; }
    break;

  case 290:
#line 435 "lscp.y"
    { (yyval.Char) = '!'; }
    break;

  case 291:
#line 435 "lscp.y"
    { (yyval.Char) = '#'; }
    break;

  case 292:
#line 435 "lscp.y"
    { (yyval.Char) = '$'; }
    break;

  case 293:
#line 435 "lscp.y"
    { (yyval.Char) = '%'; }
    break;

  case 294:
#line 435 "lscp.y"
    { (yyval.Char) = '&'; }
    break;

  case 295:
#line 435 "lscp.y"
    { (yyval.Char) = '('; }
    break;

  case 296:
#line 435 "lscp.y"
    { (yyval.Char) = ')'; }
    break;

  case 297:
#line 435 "lscp.y"
    { (yyval.Char) = '*'; }
    break;

  case 298:
#line 435 "lscp.y"
    { (yyval.Char) = '+'; }
    break;

  case 299:
#line 435 "lscp.y"
    { (yyval.Char) = '-'; }
    break;

  case 300:
#line 435 "lscp.y"
    { (yyval.Char) = '.'; }
    break;

  case 301:
#line 435 "lscp.y"
    { (yyval.Char) = ','; }
    break;

  case 302:
#line 435 "lscp.y"
    { (yyval.Char) = '/'; }
    break;

  case 303:
#line 436 "lscp.y"
    { (yyval.Char) = ':'; }
    break;

  case 304:
#line 436 "lscp.y"
    { (yyval.Char) = ';'; }
    break;

  case 305:
#line 436 "lscp.y"
    { (yyval.Char) = '<'; }
    break;

  case 306:
#line 436 "lscp.y"
    { (yyval.Char) = '='; }
    break;

  case 307:
#line 436 "lscp.y"
    { (yyval.Char) = '>'; }
    break;

  case 308:
#line 436 "lscp.y"
    { (yyval.Char) = '?'; }
    break;

  case 309:
#line 436 "lscp.y"
    { (yyval.Char) = '@'; }
    break;

  case 310:
#line 437 "lscp.y"
    { (yyval.Char) = '['; }
    break;

  case 311:
#line 437 "lscp.y"
    { (yyval.Char) = '\\'; }
    break;

  case 312:
#line 437 "lscp.y"
    { (yyval.Char) = ']'; }
    break;

  case 313:
#line 437 "lscp.y"
    { (yyval.Char) = '^'; }
    break;

  case 314:
#line 437 "lscp.y"
    { (yyval.Char) = '_'; }
    break;

  case 315:
#line 438 "lscp.y"
    { (yyval.Char) = '{'; }
    break;

  case 316:
#line 438 "lscp.y"
    { (yyval.Char) = '|'; }
    break;

  case 317:
#line 438 "lscp.y"
    { (yyval.Char) = '}'; }
    break;

  case 318:
#line 438 "lscp.y"
    { (yyval.Char) = '~'; }
    break;

  case 319:
#line 439 "lscp.y"
    { (yyval.Char) = '\200'; }
    break;

  case 320:
#line 439 "lscp.y"
    { (yyval.Char) = '\201'; }
    break;

  case 321:
#line 439 "lscp.y"
    { (yyval.Char) = '\202'; }
    break;

  case 322:
#line 440 "lscp.y"
    { (yyval.Char) = '\203'; }
    break;

  case 323:
#line 440 "lscp.y"
    { (yyval.Char) = '\204'; }
    break;

  case 324:
#line 440 "lscp.y"
    { (yyval.Char) = '\205'; }
    break;

  case 325:
#line 441 "lscp.y"
    { (yyval.Char) = '\206'; }
    break;

  case 326:
#line 441 "lscp.y"
    { (yyval.Char) = '\207'; }
    break;

  case 327:
#line 441 "lscp.y"
    { (yyval.Char) = '\210'; }
    break;

  case 328:
#line 442 "lscp.y"
    { (yyval.Char) = '\211'; }
    break;

  case 329:
#line 442 "lscp.y"
    { (yyval.Char) = '\212'; }
    break;

  case 330:
#line 442 "lscp.y"
    { (yyval.Char) = '\213'; }
    break;

  case 331:
#line 443 "lscp.y"
    { (yyval.Char) = '\214'; }
    break;

  case 332:
#line 443 "lscp.y"
    { (yyval.Char) = '\215'; }
    break;

  case 333:
#line 443 "lscp.y"
    { (yyval.Char) = '\216'; }
    break;

  case 334:
#line 444 "lscp.y"
    { (yyval.Char) = '\217'; }
    break;

  case 335:
#line 444 "lscp.y"
    { (yyval.Char) = '\220'; }
    break;

  case 336:
#line 444 "lscp.y"
    { (yyval.Char) = '\221'; }
    break;

  case 337:
#line 445 "lscp.y"
    { (yyval.Char) = '\222'; }
    break;

  case 338:
#line 445 "lscp.y"
    { (yyval.Char) = '\223'; }
    break;

  case 339:
#line 445 "lscp.y"
    { (yyval.Char) = '\224'; }
    break;

  case 340:
#line 446 "lscp.y"
    { (yyval.Char) = '\225'; }
    break;

  case 341:
#line 446 "lscp.y"
    { (yyval.Char) = '\226'; }
    break;

  case 342:
#line 446 "lscp.y"
    { (yyval.Char) = '\227'; }
    break;

  case 343:
#line 447 "lscp.y"
    { (yyval.Char) = '\230'; }
    break;

  case 344:
#line 447 "lscp.y"
    { (yyval.Char) = '\231'; }
    break;

  case 345:
#line 447 "lscp.y"
    { (yyval.Char) = '\232'; }
    break;

  case 346:
#line 448 "lscp.y"
    { (yyval.Char) = '\233'; }
    break;

  case 347:
#line 448 "lscp.y"
    { (yyval.Char) = '\234'; }
    break;

  case 348:
#line 448 "lscp.y"
    { (yyval.Char) = '\235'; }
    break;

  case 349:
#line 449 "lscp.y"
    { (yyval.Char) = '\236'; }
    break;

  case 350:
#line 449 "lscp.y"
    { (yyval.Char) = '\237'; }
    break;

  case 351:
#line 449 "lscp.y"
    { (yyval.Char) = '\240'; }
    break;

  case 352:
#line 450 "lscp.y"
    { (yyval.Char) = '\241'; }
    break;

  case 353:
#line 450 "lscp.y"
    { (yyval.Char) = '\242'; }
    break;

  case 354:
#line 450 "lscp.y"
    { (yyval.Char) = '\243'; }
    break;

  case 355:
#line 451 "lscp.y"
    { (yyval.Char) = '\244'; }
    break;

  case 356:
#line 451 "lscp.y"
    { (yyval.Char) = '\245'; }
    break;

  case 357:
#line 451 "lscp.y"
    { (yyval.Char) = '\246'; }
    break;

  case 358:
#line 452 "lscp.y"
    { (yyval.Char) = '\247'; }
    break;

  case 359:
#line 452 "lscp.y"
    { (yyval.Char) = '\250'; }
    break;

  case 360:
#line 452 "lscp.y"
    { (yyval.Char) = '\251'; }
    break;

  case 361:
#line 453 "lscp.y"
    { (yyval.Char) = '\252'; }
    break;

  case 362:
#line 453 "lscp.y"
    { (yyval.Char) = '\253'; }
    break;

  case 363:
#line 453 "lscp.y"
    { (yyval.Char) = '\254'; }
    break;

  case 364:
#line 454 "lscp.y"
    { (yyval.Char) = '\255'; }
    break;

  case 365:
#line 454 "lscp.y"
    { (yyval.Char) = '\256'; }
    break;

  case 366:
#line 454 "lscp.y"
    { (yyval.Char) = '\257'; }
    break;

  case 367:
#line 455 "lscp.y"
    { (yyval.Char) = '\260'; }
    break;

  case 368:
#line 455 "lscp.y"
    { (yyval.Char) = '\261'; }
    break;

  case 369:
#line 455 "lscp.y"
    { (yyval.Char) = '\262'; }
    break;

  case 370:
#line 456 "lscp.y"
    { (yyval.Char) = '\263'; }
    break;

  case 371:
#line 456 "lscp.y"
    { (yyval.Char) = '\264'; }
    break;

  case 372:
#line 456 "lscp.y"
    { (yyval.Char) = '\265'; }
    break;

  case 373:
#line 457 "lscp.y"
    { (yyval.Char) = '\266'; }
    break;

  case 374:
#line 457 "lscp.y"
    { (yyval.Char) = '\267'; }
    break;

  case 375:
#line 457 "lscp.y"
    { (yyval.Char) = '\270'; }
    break;

  case 376:
#line 458 "lscp.y"
    { (yyval.Char) = '\271'; }
    break;

  case 377:
#line 458 "lscp.y"
    { (yyval.Char) = '\272'; }
    break;

  case 378:
#line 458 "lscp.y"
    { (yyval.Char) = '\273'; }
    break;

  case 379:
#line 459 "lscp.y"
    { (yyval.Char) = '\274'; }
    break;

  case 380:
#line 459 "lscp.y"
    { (yyval.Char) = '\275'; }
    break;

  case 381:
#line 459 "lscp.y"
    { (yyval.Char) = '\276'; }
    break;

  case 382:
#line 460 "lscp.y"
    { (yyval.Char) = '\277'; }
    break;

  case 383:
#line 460 "lscp.y"
    { (yyval.Char) = '\300'; }
    break;

  case 384:
#line 460 "lscp.y"
    { (yyval.Char) = '\301'; }
    break;

  case 385:
#line 461 "lscp.y"
    { (yyval.Char) = '\302'; }
    break;

  case 386:
#line 461 "lscp.y"
    { (yyval.Char) = '\303'; }
    break;

  case 387:
#line 461 "lscp.y"
    { (yyval.Char) = '\304'; }
    break;

  case 388:
#line 462 "lscp.y"
    { (yyval.Char) = '\305'; }
    break;

  case 389:
#line 462 "lscp.y"
    { (yyval.Char) = '\306'; }
    break;

  case 390:
#line 462 "lscp.y"
    { (yyval.Char) = '\307'; }
    break;

  case 391:
#line 463 "lscp.y"
    { (yyval.Char) = '\310'; }
    break;

  case 392:
#line 463 "lscp.y"
    { (yyval.Char) = '\311'; }
    break;

  case 393:
#line 463 "lscp.y"
    { (yyval.Char) = '\312'; }
    break;

  case 394:
#line 464 "lscp.y"
    { (yyval.Char) = '\313'; }
    break;

  case 395:
#line 464 "lscp.y"
    { (yyval.Char) = '\314'; }
    break;

  case 396:
#line 464 "lscp.y"
    { (yyval.Char) = '\315'; }
    break;

  case 397:
#line 465 "lscp.y"
    { (yyval.Char) = '\316'; }
    break;

  case 398:
#line 465 "lscp.y"
    { (yyval.Char) = '\317'; }
    break;

  case 399:
#line 465 "lscp.y"
    { (yyval.Char) = '\320'; }
    break;

  case 400:
#line 466 "lscp.y"
    { (yyval.Char) = '\321'; }
    break;

  case 401:
#line 466 "lscp.y"
    { (yyval.Char) = '\322'; }
    break;

  case 402:
#line 466 "lscp.y"
    { (yyval.Char) = '\323'; }
    break;

  case 403:
#line 467 "lscp.y"
    { (yyval.Char) = '\324'; }
    break;

  case 404:
#line 467 "lscp.y"
    { (yyval.Char) = '\325'; }
    break;

  case 405:
#line 467 "lscp.y"
    { (yyval.Char) = '\326'; }
    break;

  case 406:
#line 468 "lscp.y"
    { (yyval.Char) = '\327'; }
    break;

  case 407:
#line 468 "lscp.y"
    { (yyval.Char) = '\330'; }
    break;

  case 408:
#line 468 "lscp.y"
    { (yyval.Char) = '\331'; }
    break;

  case 409:
#line 469 "lscp.y"
    { (yyval.Char) = '\332'; }
    break;

  case 410:
#line 469 "lscp.y"
    { (yyval.Char) = '\333'; }
    break;

  case 411:
#line 469 "lscp.y"
    { (yyval.Char) = '\334'; }
    break;

  case 412:
#line 470 "lscp.y"
    { (yyval.Char) = '\335'; }
    break;

  case 413:
#line 470 "lscp.y"
    { (yyval.Char) = '\336'; }
    break;

  case 414:
#line 470 "lscp.y"
    { (yyval.Char) = '\337'; }
    break;

  case 415:
#line 471 "lscp.y"
    { (yyval.Char) = '\340'; }
    break;

  case 416:
#line 471 "lscp.y"
    { (yyval.Char) = '\341'; }
    break;

  case 417:
#line 471 "lscp.y"
    { (yyval.Char) = '\342'; }
    break;

  case 418:
#line 472 "lscp.y"
    { (yyval.Char) = '\343'; }
    break;

  case 419:
#line 472 "lscp.y"
    { (yyval.Char) = '\344'; }
    break;

  case 420:
#line 472 "lscp.y"
    { (yyval.Char) = '\345'; }
    break;

  case 421:
#line 473 "lscp.y"
    { (yyval.Char) = '\346'; }
    break;

  case 422:
#line 473 "lscp.y"
    { (yyval.Char) = '\347'; }
    break;

  case 423:
#line 473 "lscp.y"
    { (yyval.Char) = '\350'; }
    break;

  case 424:
#line 474 "lscp.y"
    { (yyval.Char) = '\351'; }
    break;

  case 425:
#line 474 "lscp.y"
    { (yyval.Char) = '\352'; }
    break;

  case 426:
#line 474 "lscp.y"
    { (yyval.Char) = '\353'; }
    break;

  case 427:
#line 475 "lscp.y"
    { (yyval.Char) = '\354'; }
    break;

  case 428:
#line 475 "lscp.y"
    { (yyval.Char) = '\355'; }
    break;

  case 429:
#line 475 "lscp.y"
    { (yyval.Char) = '\356'; }
    break;

  case 430:
#line 476 "lscp.y"
    { (yyval.Char) = '\357'; }
    break;

  case 431:
#line 476 "lscp.y"
    { (yyval.Char) = '\360'; }
    break;

  case 432:
#line 476 "lscp.y"
    { (yyval.Char) = '\361'; }
    break;

  case 433:
#line 477 "lscp.y"
    { (yyval.Char) = '\362'; }
    break;

  case 434:
#line 477 "lscp.y"
    { (yyval.Char) = '\363'; }
    break;

  case 435:
#line 477 "lscp.y"
    { (yyval.Char) = '\364'; }
    break;

  case 436:
#line 478 "lscp.y"
    { (yyval.Char) = '\365'; }
    break;

  case 437:
#line 478 "lscp.y"
    { (yyval.Char) = '\366'; }
    break;

  case 438:
#line 478 "lscp.y"
    { (yyval.Char) = '\367'; }
    break;

  case 439:
#line 479 "lscp.y"
    { (yyval.Char) = '\370'; }
    break;

  case 440:
#line 479 "lscp.y"
    { (yyval.Char) = '\371'; }
    break;

  case 441:
#line 479 "lscp.y"
    { (yyval.Char) = '\372'; }
    break;

  case 442:
#line 480 "lscp.y"
    { (yyval.Char) = '\373'; }
    break;

  case 443:
#line 480 "lscp.y"
    { (yyval.Char) = '\374'; }
    break;

  case 444:
#line 480 "lscp.y"
    { (yyval.Char) = '\375'; }
    break;

  case 445:
#line 481 "lscp.y"
    { (yyval.Char) = '\376'; }
    break;

  case 446:
#line 481 "lscp.y"
    { (yyval.Char) = '\377'; }
    break;

  case 447:
#line 484 "lscp.y"
    { (yyval.String) = " ";      }
    break;

  case 449:
#line 486 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + " "; }
    break;

  case 450:
#line 487 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + (yyvsp[(2) - (2)].String);  }
    break;

  case 451:
#line 490 "lscp.y"
    { (yyval.String) = (yyvsp[(2) - (3)].String); }
    break;

  case 452:
#line 491 "lscp.y"
    { (yyval.String) = (yyvsp[(2) - (3)].String); }
    break;


/* Line 1267 of yacc.c.  */
#line 5426 "y.tab.c"
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


#line 758 "lscp.y"


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

