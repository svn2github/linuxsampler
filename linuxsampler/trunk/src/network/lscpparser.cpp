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
#define YYLAST   4512

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  227
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  140
/* YYNRULES -- Number of rules.  */
#define YYNRULES  530
/* YYNRULES -- Number of states.  */
#define YYNSTATES  1671

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
     157,   159,   161,   163,   180,   199,   218,   239,   247,   251,
     255,   259,   261,   263,   269,   277,   287,   289,   295,   303,
     313,   315,   317,   323,   329,   337,   347,   355,   365,   367,
     373,   381,   387,   393,   399,   403,   405,   407,   411,   415,
     425,   427,   433,   437,   445,   447,   455,   465,   473,   483,
     487,   495,   507,   517,   527,   531,   535,   541,   545,   551,
     555,   561,   569,   573,   577,   581,   585,   589,   595,   599,
     603,   609,   617,   623,   633,   639,   645,   651,   657,   663,
     669,   675,   681,   687,   693,   694,   697,   701,   707,   709,
     711,   713,   715,   717,   719,   721,   723,   727,   731,   733,
     737,   743,   751,   755,   757,   759,   761,   763,   765,   767,
     769,   771,   773,   775,   777,   779,   781,   783,   785,   787,
     789,   791,   793,   795,   797,   799,   801,   803,   805,   809,
     811,   813,   815,   817,   819,   821,   823,   826,   830,   835,
     840,   842,   845,   847,   849,   851,   853,   855,   857,   859,
     861,   863,   865,   867,   870,   873,   876,   879,   882,   885,
     888,   891,   894,   896,   898,   900,   902,   904,   906,   908,
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
    1330,  1332,  1334,  1336,  1339,  1342,  1346,  1350,  1352,  1354,
    1356,  1360,  1364,  1368,  1374,  1380,  1387,  1395,  1400,  1405,
    1409,  1414,  1422,  1432,  1439,  1443,  1453,  1465,  1472,  1480,
    1498,  1529,  1538,  1543,  1569,  1594,  1618,  1641,  1667,  1692,
    1714,  1735,  1749,  1762,  1774,  1787,  1799,  1817,  1839,  1850,
    1857,  1867,  1882,  1893,  1923,  1944,  1964,  1994,  2014,  2045,
    2066,  2084,  2113,  2141,  2167,  2186,  2204,  2232,  2248,  2265,
    2285,  2306,  2324,  2340,  2359,  2375,  2386,  2402,  2410,  2419,
    2426,  2433,  2439,  2444,  2449,  2455,  2466,  2472,  2486,  2491,
    2496
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
     283,   281,    -1,   362,   283,   241,    -1,   290,   283,   242,
      -1,   362,    -1,   366,    -1,   304,    -1,   345,    -1,   345,
     283,   269,    -1,   309,    -1,   310,    -1,   311,    -1,   312,
      -1,   317,    -1,   321,    -1,   320,    -1,   319,    -1,   318,
      -1,   313,    -1,   314,    -1,   315,    -1,   316,    -1,   363,
      -1,   322,    -1,   309,    -1,   310,    -1,   311,    -1,   312,
      -1,   317,    -1,   321,    -1,   320,    -1,   319,    -1,   318,
      -1,   313,    -1,   314,    -1,   315,    -1,   316,    -1,   363,
      -1,   322,    -1,   343,   283,   246,   259,   283,   260,   283,
     261,   283,   267,   283,   268,   283,   265,   283,   263,    -1,
     343,   283,   246,   259,   283,   260,   283,   261,   283,   267,
     283,   268,   283,   265,   283,   263,   283,   252,    -1,   343,
     283,   246,   259,   283,   260,   283,   261,   283,   267,   283,
     268,   283,   265,   283,   263,   283,   270,    -1,   343,   283,
     246,   259,   283,   260,   283,   261,   283,   267,   283,   268,
     283,   265,   283,   263,   283,   252,   283,   270,    -1,   343,
     283,   259,   283,   260,   283,   261,    -1,   304,   283,   264,
      -1,   345,   283,   259,    -1,   345,   283,   295,    -1,   305,
      -1,   337,    -1,   347,   283,   308,   283,   275,    -1,   342,
     283,   308,   283,   275,   283,   275,    -1,   342,   283,   308,
     283,   275,   283,   275,   283,   247,    -1,   306,    -1,   333,
     283,   308,   283,   275,    -1,   332,   283,   308,   283,   275,
     283,   275,    -1,   332,   283,   308,   283,   275,   283,   275,
     283,   247,    -1,   330,    -1,   340,    -1,   331,   283,   308,
     283,   279,    -1,   341,   283,   308,   283,   279,    -1,   348,
     283,   308,   283,   279,   283,   279,    -1,   339,   283,   308,
     283,   279,   283,   279,   283,   275,    -1,   335,   283,   308,
     283,   279,   283,   279,    -1,   334,   283,   308,   283,   279,
     283,   279,   283,   275,    -1,   307,    -1,   304,   283,   308,
     283,   264,    -1,   304,   283,   319,   283,   248,   283,   264,
      -1,   304,   283,   320,   283,   264,    -1,   304,   283,   321,
     283,   264,    -1,   325,   283,   308,   283,   267,    -1,   355,
     283,   308,    -1,   322,    -1,   323,    -1,   344,   283,   259,
      -1,   344,   283,   295,    -1,   343,   283,   308,   283,   259,
     283,   260,   283,   261,    -1,   346,    -1,   345,   283,   308,
     283,   259,    -1,   354,   283,   264,    -1,   353,   283,   308,
     283,   264,   283,   266,    -1,   356,    -1,   329,   283,   279,
     283,   275,     4,   272,    -1,   334,   283,   279,   283,   279,
     283,   275,     4,   272,    -1,   338,   283,   279,   283,   275,
       4,   272,    -1,   339,   283,   279,   283,   279,   283,   275,
       4,   272,    -1,   304,   283,   245,    -1,   345,   283,   364,
     283,   259,   283,   269,    -1,   353,   283,   335,   283,   264,
     283,   266,   283,   254,   283,   254,    -1,   353,   283,   352,
     283,   264,   283,   266,   283,   262,    -1,   353,   283,   357,
     283,   264,   283,   266,   283,   263,    -1,   365,   283,   274,
      -1,   356,   283,   263,    -1,   331,   283,   275,   283,   247,
      -1,   331,   283,   275,    -1,   341,   283,   275,   283,   247,
      -1,   341,   283,   275,    -1,   353,   283,   264,   283,   262,
      -1,   353,   283,   264,   283,   262,   283,   271,    -1,   304,
     283,   264,    -1,   344,   283,   259,    -1,   344,   283,   295,
      -1,   331,   283,   279,    -1,   341,   283,   279,    -1,   353,
     283,   264,   283,   266,    -1,   324,   283,   250,    -1,   325,
     283,   251,    -1,   331,   283,   264,   283,   253,    -1,   335,
     283,   264,   283,   254,   283,   254,    -1,   336,   283,   264,
     283,   255,    -1,   351,   283,   264,   283,   253,   283,   256,
     283,   257,    -1,   341,   283,   264,   283,   253,    -1,   348,
     283,   264,   283,   256,    -1,   349,   283,   264,   283,   257,
      -1,   350,   283,   264,   283,   258,    -1,   356,   283,   264,
     283,   263,    -1,   358,   283,   264,   283,   274,    -1,   359,
     283,   264,   283,   274,    -1,   345,   283,   264,   283,   259,
      -1,   345,   283,   264,   283,   296,    -1,   345,   283,   264,
     283,   297,    -1,    -1,   298,   283,    -1,   275,     4,   272,
      -1,   247,   283,   275,     4,   272,    -1,   360,    -1,   361,
      -1,   330,    -1,   340,    -1,   307,    -1,   305,    -1,   337,
      -1,   306,    -1,   344,   283,   259,    -1,   344,   283,   295,
      -1,   346,    -1,   354,   283,   264,    -1,   268,   283,   265,
     283,   264,    -1,   298,   283,   268,   283,   265,   283,   264,
      -1,   267,   283,   264,    -1,   326,    -1,   327,    -1,   328,
      -1,   279,    -1,   279,    -1,   275,    -1,   279,    -1,   279,
      -1,   295,    -1,   275,    -1,   279,    -1,   279,    -1,   279,
      -1,   279,    -1,   276,    -1,   279,    -1,   279,    -1,   279,
      -1,   279,    -1,   275,    -1,   282,    -1,   282,    -1,   282,
      -1,   282,    -1,   273,    -1,   272,     5,   273,    -1,   275,
      -1,   282,    -1,   279,    -1,   276,    -1,   279,    -1,   275,
      -1,   280,    -1,   275,   280,    -1,   277,     6,   277,    -1,
       7,   277,     6,   277,    -1,     8,   277,     6,   277,    -1,
     278,    -1,   277,   278,    -1,     9,    -1,    10,    -1,    11,
      -1,    12,    -1,    13,    -1,    14,    -1,    15,    -1,    16,
      -1,    17,    -1,    18,    -1,   278,    -1,    10,   277,    -1,
      11,   277,    -1,    12,   277,    -1,    13,   277,    -1,    14,
     277,    -1,    15,   277,    -1,    16,   277,    -1,    17,   277,
      -1,    18,   277,    -1,    19,    -1,    20,    -1,    21,    -1,
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
     221,    -1,   283,    -1,   275,    -1,   281,   283,    -1,   281,
     275,    -1,   222,   281,   222,    -1,   223,   281,   223,    -1,
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
      27,    32,    24,    33,    -1,    21,    26,    19,    32,    32,
      23,    30,    89,    21,    33,    39,    32,    38,    -1,    21,
      26,    19,    32,    32,    23,    30,    89,    27,    32,    24,
      33,    -1,    20,    39,    24,    24,    23,    36,    89,    24,
      27,    30,    30,    -1,    37,    38,    36,    23,    19,    31,
      89,    21,    33,    39,    32,    38,    -1,    40,    33,    27,
      21,    23,    89,    21,    33,    39,    32,    38,    -1,    38,
      33,    38,    19,    30,    89,    40,    33,    27,    21,    23,
      89,    21,    33,    39,    32,    38,    -1,    38,    33,    38,
      19,    30,    89,    40,    33,    27,    21,    23,    89,    21,
      33,    39,    32,    38,    89,    31,    19,    42,    -1,    27,
      32,    37,    38,    36,    39,    31,    23,    32,    38,    -1,
      23,    32,    25,    27,    32,    23,    -1,    33,    32,    89,
      22,    23,    31,    19,    32,    22,    -1,    33,    32,    89,
      22,    23,    31,    19,    32,    22,    89,    26,    33,    30,
      22,    -1,    34,    23,    36,    37,    27,    37,    38,    23,
      32,    38,    -1,    19,    39,    22,    27,    33,    89,    33,
      39,    38,    34,    39,    38,    89,    22,    23,    40,    27,
      21,    23,    89,    34,    19,    36,    19,    31,    23,    38,
      23,    36,    -1,    19,    39,    22,    27,    33,    89,    33,
      39,    38,    34,    39,    38,    89,    22,    23,    40,    27,
      21,    23,    37,    -1,    19,    39,    22,    27,    33,    89,
      33,    39,    38,    34,    39,    38,    89,    22,    23,    40,
      27,    21,    23,    -1,    19,    39,    22,    27,    33,    89,
      33,    39,    38,    34,    39,    38,    89,    22,    36,    27,
      40,    23,    36,    89,    34,    19,    36,    19,    31,    23,
      38,    23,    36,    -1,    19,    39,    22,    27,    33,    89,
      33,    39,    38,    34,    39,    38,    89,    22,    36,    27,
      40,    23,    36,    -1,    19,    39,    22,    27,    33,    89,
      33,    39,    38,    34,    39,    38,    89,    21,    26,    19,
      32,    32,    23,    30,    89,    34,    19,    36,    19,    31,
      23,    38,    23,    36,    -1,    19,    39,    22,    27,    33,
      89,    33,    39,    38,    34,    39,    38,    89,    21,    26,
      19,    32,    32,    23,    30,    -1,    19,    39,    22,    27,
      33,    89,    33,    39,    38,    34,    39,    38,    89,    38,
      43,    34,    23,    -1,    19,    40,    19,    27,    30,    19,
      20,    30,    23,    89,    31,    27,    22,    27,    89,    27,
      32,    34,    39,    38,    89,    22,    36,    27,    40,    23,
      36,    37,    -1,    31,    27,    22,    27,    89,    27,    32,
      34,    39,    38,    89,    22,    23,    40,    27,    21,    23,
      89,    34,    19,    36,    19,    31,    23,    38,    23,    36,
      -1,    31,    27,    22,    27,    89,    27,    32,    34,    39,
      38,    89,    34,    33,    36,    38,    89,    34,    19,    36,
      19,    31,    23,    38,    23,    36,    -1,    31,    27,    22,
      27,    89,    27,    32,    34,    39,    38,    89,    22,    23,
      40,    27,    21,    23,    37,    -1,    31,    27,    22,    27,
      89,    27,    32,    34,    39,    38,    89,    22,    23,    40,
      27,    21,    23,    -1,    31,    27,    22,    27,    89,    27,
      32,    34,    39,    38,    89,    22,    36,    27,    40,    23,
      36,    89,    34,    19,    36,    19,    31,    23,    38,    23,
      36,    -1,    31,    27,    22,    27,    89,    27,    32,    37,
      38,    36,    39,    31,    23,    32,    38,    -1,    31,    27,
      22,    27,    89,    27,    32,    37,    38,    36,    39,    31,
      23,    32,    38,    37,    -1,    31,    27,    22,    27,    89,
      27,    32,    37,    38,    36,    39,    31,    23,    32,    38,
      89,    31,    19,    34,    -1,    31,    27,    22,    27,    89,
      27,    32,    37,    38,    36,    39,    31,    23,    32,    38,
      89,    31,    19,    34,    37,    -1,    31,    27,    22,    27,
      89,    27,    32,    34,    39,    38,    89,    22,    36,    27,
      40,    23,    36,    -1,    31,    27,    22,    27,    89,    27,
      32,    34,    39,    38,    89,    34,    33,    36,    38,    -1,
      31,    27,    22,    27,    89,    27,    32,    34,    39,    38,
      89,    21,    26,    19,    32,    32,    23,    30,    -1,    31,
      27,    22,    27,    89,    27,    32,    34,    39,    38,    89,
      38,    43,    34,    23,    -1,    31,    27,    22,    27,    89,
      27,    32,    34,    39,    38,    -1,    31,    27,    22,    27,
      89,    21,    33,    32,    38,    36,    33,    30,    30,    23,
      36,    -1,    24,    42,    89,    37,    23,    32,    22,    -1,
      24,    42,    89,    37,    23,    32,    22,    37,    -1,    37,
      23,    36,    40,    23,    36,    -1,    40,    33,    30,    39,
      31,    23,    -1,    30,    23,    40,    23,    30,    -1,    31,
      39,    38,    23,    -1,    37,    33,    30,    33,    -1,    20,
      43,    38,    23,    37,    -1,    34,    23,    36,    21,    23,
      32,    38,    19,    25,    23,    -1,    36,    23,    37,    23,
      38,    -1,    31,    27,    37,    21,    23,    30,    30,    19,
      32,    23,    33,    39,    37,    -1,    32,    19,    31,    23,
      -1,    23,    21,    26,    33,    -1,    35,    39,    27,    38,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    97,    97,    98,   101,   102,   103,   104,   107,   108,
     109,   110,   111,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     133,   134,   135,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   172,   173,   174,   175,   178,   181,   182,
     183,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   235,   236,   237,   238,
     239,   240,   243,   246,   247,   250,   251,   252,   255,   256,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   275,   276,   279,   280,   283,   284,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     299,   300,   303,   306,   307,   308,   311,   314,   317,   320,
     323,   324,   327,   330,   333,   336,   339,   342,   343,   346,
     349,   352,   355,   358,   361,   364,   367,   370,   371,   374,
     375,   376,   377,   385,   386,   389,   390,   393,   394,   395,
     399,   400,   403,   404,   405,   406,   407,   408,   409,   410,
     411,   412,   415,   416,   417,   418,   419,   420,   421,   422,
     423,   424,   426,   426,   426,   426,   426,   426,   426,   426,
     426,   426,   426,   426,   426,   426,   426,   426,   426,   426,
     426,   426,   426,   426,   426,   426,   426,   426,   427,   427,
     427,   427,   427,   427,   427,   427,   427,   427,   427,   427,
     427,   427,   427,   427,   427,   427,   427,   427,   427,   427,
     427,   427,   427,   427,   428,   428,   428,   428,   428,   428,
     428,   428,   428,   428,   429,   429,   429,   429,   429,   429,
     429,   429,   429,   429,   429,   429,   429,   430,   430,   430,
     430,   430,   430,   430,   431,   431,   431,   431,   431,   432,
     432,   432,   432,   433,   433,   433,   434,   434,   434,   435,
     435,   435,   436,   436,   436,   437,   437,   437,   438,   438,
     438,   439,   439,   439,   440,   440,   440,   441,   441,   441,
     442,   442,   442,   443,   443,   443,   444,   444,   444,   445,
     445,   445,   446,   446,   446,   447,   447,   447,   448,   448,
     448,   449,   449,   449,   450,   450,   450,   451,   451,   451,
     452,   452,   452,   453,   453,   453,   454,   454,   454,   455,
     455,   455,   456,   456,   456,   457,   457,   457,   458,   458,
     458,   459,   459,   459,   460,   460,   460,   461,   461,   461,
     462,   462,   462,   463,   463,   463,   464,   464,   464,   465,
     465,   465,   466,   466,   466,   467,   467,   467,   468,   468,
     468,   469,   469,   469,   470,   470,   470,   471,   471,   471,
     472,   472,   472,   473,   473,   473,   474,   474,   474,   475,
     475,   478,   479,   480,   481,   484,   485,   491,   494,   497,
     500,   503,   506,   509,   512,   515,   518,   521,   524,   527,
     530,   533,   536,   539,   542,   545,   548,   551,   554,   557,
     560,   563,   566,   569,   572,   575,   578,   581,   584,   587,
     590,   593,   596,   599,   602,   605,   608,   611,   614,   617,
     620,   623,   626,   629,   632,   635,   638,   641,   644,   647,
     650,   653,   656,   659,   662,   665,   668,   671,   674,   677,
     680,   683,   686,   689,   692,   695,   698,   701,   704,   707,
     710,   713,   716,   719,   722,   725,   728,   731,   734,   737,
     740
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
  "clear_instruction", "destroy_instruction", "load_instruction",
  "set_chan_instruction", "modal_arg", "key_val_list", "buffer_size_type",
  "list_instruction", "load_instr_args", "load_engine_args",
  "instr_load_mode", "device_index", "audio_channel_index",
  "audio_output_type_name", "midi_input_port_index",
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
     249,   249,   249,   249,   249,   249,   249,   249,   249,   249,
     250,   250,   251,   252,   252,   252,   253,   254,   255,   256,
     257,   257,   258,   259,   260,   261,   262,   263,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   272,   273,
     273,   273,   273,   274,   274,   275,   275,   276,   276,   276,
     277,   277,   278,   278,   278,   278,   278,   278,   278,   278,
     278,   278,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   280,   280,   280,   280,   280,   280,   280,   280,
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
     280,   281,   281,   281,   281,   282,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   354,   355,
     356,   357,   358,   359,   360,   361,   362,   363,   364,   365,
     366
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
       1,     1,     1,    16,    18,    18,    20,     7,     3,     3,
       3,     1,     1,     5,     7,     9,     1,     5,     7,     9,
       1,     1,     5,     5,     7,     9,     7,     9,     1,     5,
       7,     5,     5,     5,     3,     1,     1,     3,     3,     9,
       1,     5,     3,     7,     1,     7,     9,     7,     9,     3,
       7,    11,     9,     9,     3,     3,     5,     3,     5,     3,
       5,     7,     3,     3,     3,     3,     3,     5,     3,     3,
       5,     7,     5,     9,     5,     5,     5,     5,     5,     5,
       5,     5,     5,     5,     0,     2,     3,     5,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     1,     3,
       5,     7,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     2,     3,     4,     4,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     1,
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
       1,     1,     1,     2,     2,     3,     3,     1,     1,     1,
       3,     3,     3,     5,     5,     6,     7,     4,     4,     3,
       4,     7,     9,     6,     3,     9,    11,     6,     7,    17,
      30,     8,     4,    25,    24,    23,    22,    25,    24,    21,
      20,    13,    12,    11,    12,    11,    17,    21,    10,     6,
       9,    14,    10,    29,    20,    19,    29,    19,    30,    20,
      17,    28,    27,    25,    18,    17,    27,    15,    16,    19,
      20,    17,    15,    18,    15,    10,    15,     7,     8,     6,
       6,     5,     4,     4,     5,    10,     5,    13,     4,     4,
       4
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
       0,     0,     0,     0,     0,     0,     1,   448,   449,     2,
       0,     9,   300,   295,   294,   292,   293,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   284,
     286,   287,   288,   289,   290,   291,   296,   297,   298,   299,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   324,   325,   326,   327,   328,   329,   330,
     331,   332,   333,   334,   335,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,   353,   354,   355,   356,   357,   358,   359,   360,
     361,   362,   363,   364,   365,   366,   367,   368,   369,   370,
     371,   372,   373,   374,   375,   376,   377,   378,   379,   380,
     381,   382,   383,   384,   385,   386,   387,   388,   389,   390,
     391,   392,   393,   394,   395,   396,   397,   398,   399,   400,
     401,   402,   403,   404,   405,   406,   407,   408,   409,   410,
     411,   412,   413,   414,   415,   416,   417,   418,   419,   420,
     421,   422,   423,   424,   425,   426,   427,   428,   429,   430,
     431,   432,   433,   434,   435,   436,   437,   438,   439,   440,
     447,    12,   212,    11,   195,    10,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   450,     0,     0,     0,   451,     0,     0,   452,     0,
       0,     0,     0,   464,     0,     0,     0,     3,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   213,   200,
     214,   215,   216,   217,   218,   219,   220,   221,   285,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   196,
       0,     0,    13,    30,    31,     0,     0,     0,     0,     0,
       0,     0,     0,    16,     0,    71,    76,    88,    95,    96,
       0,    80,     0,     0,     0,     0,     0,    72,     0,    81,
       0,     0,     0,     0,     0,   100,     0,     0,     0,     0,
       0,   104,     0,    14,     0,    15,     0,     0,    27,     0,
       0,     0,     0,    17,     0,     0,     0,    18,     0,     0,
       0,     0,     0,     0,     0,    19,   153,   155,   152,   150,
     154,   151,     0,   158,     0,     0,    20,     0,     0,    21,
       0,     0,     0,     0,     0,    22,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    23,    33,    34,    35,    36,    42,    43,    44,
      45,    37,    41,    40,    39,    38,    47,    46,    24,    48,
      49,    50,    51,    57,    58,    59,    60,    52,    56,    55,
      54,    53,    62,    61,   442,    25,   441,    26,     0,     0,
       0,     0,   457,   458,   530,     0,     0,     0,     0,     0,
       0,   201,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   144,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   444,   443,     0,   454,
       0,     0,     0,   526,     0,     0,   453,     0,     0,     0,
       0,     0,    32,   184,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   203,   204,
     205,   206,   207,   208,   209,   210,   211,     0,    97,   173,
      98,     0,     0,     0,     0,   102,   179,    94,     0,     0,
       0,     0,     0,     0,   123,   124,     0,     0,     0,   117,
     119,     0,   125,   126,     0,     0,     0,     0,     0,   156,
     157,   159,     0,   128,     0,   183,     0,   129,     0,   182,
      68,    69,    70,     0,     0,     0,     0,     0,     0,   109,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   115,   177,     0,   200,
     178,   114,   194,   193,     0,     0,     0,     0,     0,     0,
       0,     0,   122,   455,     0,   463,   467,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   145,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   529,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   456,     0,     0,     0,     0,
     445,   446,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    89,     0,     0,     0,   148,   149,    91,    92,
      93,    82,     0,    77,     0,     0,     0,    83,     0,     0,
     459,   101,    73,     0,     0,     0,     0,     0,     0,   174,
       0,     0,     0,     0,   116,     0,   118,   120,   176,   127,
     181,     0,     0,     0,     0,     0,     0,   180,     0,   162,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   197,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   489,     0,
       0,   519,     0,   520,   472,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   522,   523,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   528,     0,     0,     0,
       0,     0,     0,     0,   198,   199,     0,     0,     0,     0,
       0,     0,     0,     0,   465,     0,   468,     0,     0,     0,
     468,   517,     0,     0,     0,     0,    90,    78,     0,    86,
       0,    74,     0,    84,   103,     0,     0,     0,    67,   175,
       0,     0,   517,     0,     0,   292,   293,   146,   187,   189,
     192,   191,   190,   121,   186,     0,     0,     0,     0,     0,
     160,     0,     0,     0,     0,     0,   130,   166,     0,   167,
     132,   168,   134,     0,     0,   141,   142,   143,   135,   169,
     136,   170,   171,   137,   172,     0,   138,   139,   140,   105,
       0,   107,     0,   110,     0,   521,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   471,   518,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   466,     0,     0,     0,     0,     0,     0,   524,     0,
      79,    87,    85,    75,    99,     0,     0,     0,     0,     0,
       0,   147,   188,     0,     0,     0,     0,   161,     0,     0,
       0,     0,   131,     0,     0,     0,   106,   108,     0,     0,
       0,   112,   113,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   488,
       0,     0,     0,     0,     0,   460,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     462,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   133,     0,     0,   111,     0,   483,     0,
       0,     0,     0,     0,     0,     0,   485,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   515,
       0,     0,     0,     0,     0,   482,     0,     0,     0,   484,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   461,     0,     0,     0,   481,
       0,     0,   527,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   525,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   512,   507,     0,
     507,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   508,     0,     0,    63,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   469,
       0,   505,   511,     0,     0,   486,     0,     0,   505,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   512,   514,
     516,     0,     0,     0,     0,     0,   486,     0,     0,     0,
       0,     0,     0,   504,     0,     0,     0,     0,     0,     0,
      64,    65,   185,   163,   164,   165,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     509,     0,   495,   497,     0,     0,     0,     0,   509,     0,
       0,     0,     0,   495,     0,     0,     0,     0,     0,     0,
     500,     0,     0,     0,     0,     0,     0,     0,   499,   494,
       0,     0,     0,     0,     0,   510,     0,     0,     0,    66,
       0,     0,     0,     0,   513,     0,     0,     0,     0,   480,
       0,     0,     0,     0,     0,     0,     0,   487,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   479,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     499,     0,     0,     0,   476,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   475,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   474,     0,   478,     0,     0,     0,     0,
       0,   503,     0,     0,     0,     0,   473,   477,     0,     0,
       0,     0,     0,   490,     0,     0,     0,     0,     0,     0,
       0,   506,     0,   492,     0,   502,     0,     0,     0,   501,
       0,     0,     0,   496,     0,     0,   493,   498,   470,     0,
     491
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    13,    14,    15,    16,   342,   442,   458,   383,   385,
     419,   353,   425,   393,   477,   388,   397,   416,   669,   630,
     864,   835,   405,   653,   657,  1490,  1056,  1058,  1060,  1068,
    1070,  1073,   618,   858,  1028,   867,   696,   625,   876,   869,
     658,   654,   582,  1491,  1043,  1037,  1038,   701,  1039,  1040,
     698,   272,   626,   274,   475,  1042,   954,    49,    50,    17,
      18,    19,    20,    21,    22,    23,    24,    25,  1072,  1066,
    1067,   631,    26,    27,    28,    29,    30,   343,   355,   356,
     357,   594,   443,   444,   445,   446,   447,   448,   449,   450,
     451,   452,   453,   454,   455,   358,   359,   417,   360,  1493,
    1494,  1495,   427,   361,   362,   363,   364,   365,   366,   672,
     367,   429,   368,   369,   370,   371,   372,   373,   344,   375,
     376,   377,   676,   677,   678,   692,   378,   379,   380,   381,
     693,   680,   681,   836,   837,    31,   457,   687,   434,    32
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -1079
static const yytype_int16 yypact[] =
{
      64, -1079, -1079,    98,    39,   148,   176,   135,   190,   210,
     240,    45,   239,   302,  -152,  2093, -1079,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86, -1079,   304,   305,   307,   290,   293,   295,   314,
     300,   308,   199,   125,   316,   204, -1079, -1079, -1079, -1079,
     112, -1079, -1079, -1079, -1079, -1079, -1079, -1079,   411,   411,
     411,   411,   411,   411,   411,   411,   411, -1079, -1079, -1079,
   -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079,
   -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079,
   -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079,
   -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079,
   -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079,
   -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079,
   -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079,
   -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079,
   -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079,
   -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079,
   -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079,
   -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079,
   -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079,
   -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079,
   -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079,
   -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079,
   -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079,
   -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079,
   -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079,
   -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079,
   -1079,  2758, -1079, -1079, -1079, -1079,   116,   119,   309,   309,
     310,   167,   167,   166,   234,   116,    57,   163,   163,  2315,
     317, -1079,   323,   324,   306, -1079,   322,   330, -1079,   328,
     313,   331,   344, -1079,   333,   349,   334, -1079, -1079, -1079,
   -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079,   411, -1079,
     411,   411,   411,   411,   411,   411,   411,   411, -1079, -1079,
   -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079,
     350,   351, -1079, -1079,    86,   130,   372,   345,   358,   374,
     381,   375,   376, -1079,    86, -1079, -1079, -1079, -1079, -1079,
      86, -1079,    86,    86,    86,    86,    86, -1079,    86, -1079,
      86,    86,    86,    86,    86, -1079,    86,    86,    86,    86,
      86, -1079,   380, -1079,    86, -1079,    86,   383, -1079,    86,
     391,   401,   417, -1079,    86,    86,    86, -1079,    86,    86,
      86,   149,   419,   404,   420, -1079, -1079, -1079, -1079, -1079,
   -1079, -1079,    86, -1079,    86,   418, -1079,    86,    86, -1079,
      86,    86,   410,   430,   425, -1079,    86,    86,    86,    86,
      86,    86,    86,    86,    86,   414,   415,   429,   432,   424,
     423,   441, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079,
   -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079,
   -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079,
   -1079, -1079, -1079, -1079,  2758,  2315, -1079, -1079,    86,   421,
     437,   442, -1079, -1079, -1079,   439,   444,   456,   459,   449,
     464, -1079,   468,   490,    16,   491,   495,   496,   494,   431,
     499,   482,   485,   492,    50,   497,   497,   497,   497,   497,
     497,   497,   497,   497,   497,   377,   497,   497,   497,   497,
     558,   497,   503,   498,   558,   505,   377,   507,   443,   509,
    2758,  2758,   558,   558,   558,   558,   511,   515,   448,   516,
     377,   558,   502,    11,  2758,   558,   377,   518,   517,   519,
     127,   558,   558,   558,   558,   512,    88,   493,  2977,   523,
     522,   528,    87,   513,   514,   524,  2758, -1079,   558, -1079,
     527,   525,   534, -1079,   526,   541, -1079,   556,   529,   535,
    2315,  2315, -1079, -1079,   536,   551,   571,   578,   573,   584,
     572,   594,   575,   583,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,   411,   411,
     411,   411,   411,   411,   411,   411,   411,   588, -1079, -1079,
   -1079,    86,    86,    86,    86, -1079, -1079, -1079,   592,   587,
     558,    86,    86,   596, -1079, -1079,   600,   591,   603,  2315,
    2315,    86, -1079, -1079,    86,   604,   589,   597,   606, -1079,
   -1079, -1079,   598, -1079,    86, -1079,    86, -1079,    86,  2758,
   -1079, -1079, -1079,   608,   605,   610,   601,   165,   609, -1079,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,   625,    86,   607,   622,
     620,    86,    86,    86,   411,   411, -1079, -1079,   303,    29,
   -1079, -1079,  2758, -1079,   621,   626,   617,   624,   631,   630,
     635,   652, -1079, -1079,   632, -1079, -1079,   647,   661,   651,
     595,  1649,  1871,   653,   655,   656,   657,   664,   602,   667,
     662,   663,   669,   558,    59,   558,   558,  2758,   558,  2758,
    2758,   558,   558,   558,   558,  2758,   558,   665,   558,  2758,
     558,   558,   611,   666,    86, -1079,   558,   612,   670,   673,
     613,  2758,  2758,   558,   558,   671,   676,   674,   616,   675,
     558,    16,   558,   677, -1079,   623,   687,   691,   678,   684,
     558,   558,   558,   558,   558,   558,   558,   558,   558,   558,
     558,   558,  2758,   558,  2758,   558,   668,   558,   693,   679,
     695,   558,   558,   558,   455,   480,   411,   685,   697,   689,
     642,   709,   714,   704,   712, -1079,   716,   701,   715,   720,
   -1079, -1079,   660,   722,   719,   728,   721,   727,   723,   672,
     732,   724, -1079,   713,   737,    86, -1079, -1079, -1079, -1079,
   -1079, -1079,  2315,  2758,    86,    86,    86, -1079,  2315,    86,
   -1079, -1079,  2758,    86,    86,   735,   680,   558,    86, -1079,
     736,   681,   742,   740,    86,  3196,    86,    86, -1079, -1079,
   -1079,   686,   741,   744,   750,   729,    86, -1079,    86, -1079,
     690,   751,   754,   755,   760,   752,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,  3415,    86,
    3634,    86,   761,    86,   759,   764,   762,    86,    86,    86,
     411,   411,   411,   699,   757,   767,   769,   768,   763,   702,
     711,   778,   775,   773,   772,   774,   785,   776, -1079,   788,
     779, -1079,   777, -1079, -1079,   780,   783,   558,  2758,   558,
     558,   558,  2758,   558,   558,   558,   781,   784,    86,   558,
     782,   789,   794,   791,  2758,  2537,    16,   792,   796,   799,
     800,   793,   558,   558,   795,   803,   804,   747, -1079, -1079,
     558,   558,  2758,   558,   117,   558,   377,  2758,   558,   493,
    2977,  2977,  2537,  2758,  2537,  2758, -1079,    16,   807,   811,
     753,   558,   558,   558,   411,   411,   813,   758,   818,   817,
     820,   766,   816,   830, -1079,   833, -1079,   821,   823,   827,
     828,   829,   230,   834,   837,   847, -1079,  2315,    86, -1079,
      86,  2315,    86, -1079, -1079,   832,   850,   558, -1079, -1079,
     848,   831, -1079,   853,  3853,   411,   411,   884, -1079,  2758,
   -1079, -1079, -1079, -1079, -1079,   851,   828,   829,   232,   868,
   -1079,    86,   856,   236,   809,   872, -1079, -1079,    86, -1079,
   -1079,  2758, -1079,   877,   869, -1079, -1079, -1079, -1079, -1079,
   -1079, -1079, -1079, -1079,  2758,    86, -1079, -1079, -1079,   884,
    4072,   884,  4291, -1079,   812, -1079,   882,    86,    86,    86,
     865,   881,   819,   238,   887,   888,   878,   879,   890,   876,
     883,   892, -1079, -1079,   871,   885,   889,   880,   899,  2758,
    2758,  2758,  2758,   558,   886,   903,    86,   891,   893,   895,
    2537,  2537,   894,   896,   898,   905,   558,   900,   901,   897,
     907,   558,   902,   912,   558,  2537,  2537,   915,   916,   558,
     558,   493,   914,   923,   216,   917,   920,   921,   922,   927,
     924, -1079,   925,   926,   838,   928,   931,   941, -1079,   932,
      86,  2758,  2758,    86, -1079,   933,   909,  2758,   934,   937,
     930,   884, -1079,   940,   949,   943,   950, -1079,   955,   952,
     953,   259, -1079,   972,   973,    86,   884,   884,   958,   966,
      86, -1079, -1079,   965,   970,   968,   976,   971,   974,   981,
     977,   990,   980,   978,   979,   122,   938,   984,   996,   975,
     991,  1001,    86,   993,   994,   945,   998,   946,   999, -1079,
    1000,   951,   982,  1002,  1005, -1079,   377,  1007,  1008,   558,
    1010,  1020,  1013,  1030,   967,  1016,  1025,  1027,  1038,  1024,
    1032,  1028,  1029,  1035,  1044,   132,  1045,   986,  1058,  1047,
   -1079,    16,  1048,  1042,  1059,  1046,  1060,  1052,  1049,   171,
    1051,  1050,  1056, -1079,  1055,  1054, -1079,  1053, -1079,  1062,
    1064,  1070,  1068,  1061,  1057,  1015, -1079,  1079,  1017,  1085,
    1086,  1088,    75,  1080,  1089,  1093,  1091,  1094,    86,  1095,
    1031,  1096,  1036,  1098,  1101,  1037,  1104,  1097,  1090,  1039,
    1102,  1092,  1099,  1063,  1106, -1079,  1111,  1112,  1108, -1079,
    1118,  1114,   186,  1120,  1121,  1124,  1113,  1127,  1119,  1125,
    1123,  1135,  1128,   558,  1129,  1137,  1122,  1141,  1126,  1132,
     270,  1131,  1133,  1130,    70, -1079,  1134,  1143,  1145, -1079,
    1136,  1142, -1079,  1144,  1140,  1139,   100,  1146,  1148,  1100,
    1154,  1147,  1150,  1152,  1153, -1079,  1155,    86,  1156,  1159,
    1157,  1160,  1158,  1161,  1165,  1163,  1168,  1162,  1107,  1172,
    1169,  1164,  1115,  1171,  1180,  1181,  1173,  1170,  1138,  1191,
    1174,  1185,  1149,  1190,  1188,  1195,  1194,  1151,    21,  1186,
   -1079,   493,  1182,  1192,  1199,  1196,  1204,    26,  1211,  1197,
    1220,  1151,    84,  1223,  1207,  1213,  1227,  1228,  1212,  1232,
    1167,  1222,  1226,  1229,  1231,  1219,  1230,  1225,  1233,  1237,
    1234,  1235, -1079,  1236,  1239,    86,  1241,  1248,  1245,  1251,
    1244,  1249,  1253,  1259,  1238,  1240,  1252,  1250,  1263,  1254,
    1262,  1268,   175,  1255,  1273,  1264,  1274,  1271,  1258, -1079,
    1265,  1261,  1214,  1281,  1282,  1215,    22,  1284, -1079,  1285,
    1261,  1283,  1275,  1287,  1221,  1290,  1277,  1280, -1079, -1079,
   -1079,  1292,  1242,  1286,  1288,  1295, -1079,  1289,  1293,  1294,
    1279,  1291,  1296, -1079,  1298,  1297,  1300,  1299,  1304,  1301,
      86, -1079, -1079, -1079, -1079, -1079,  1303,  1305,  1306,  1314,
    1315,  1307,  1311,  1316,  1321,  1322,   219,  1308,  1324,  1312,
   -1079,  1319,  1313,  1266,  1317,  1318,  1302,  1333,  1320,  1334,
    1269,  1323,    16, -1079,  1313,  1320,  1330,  1272,  1335,  1331,
   -1079,  1332,  1276,  1336,  1338,  1339,  1340,  1309,  1310, -1079,
    1341,  1325,  1326,  1342,  1337, -1079,  1343,  1350,  1344, -1079,
    1310,  1345,  1346,  1351, -1079,   221,  1347,  1352,  1349, -1079,
     229,  1354,  1358,  1353,  1361,  1365,  1357, -1079,  1366,  1363,
    1373,  1375,  1367,  1362,  1364,  1368,  1369, -1079,  1370,  1372,
    1382,  1371,  1327,  1376,  1374,  1379,  1377,  1381,  1378,  1380,
   -1079,  1384,  1385,  1383, -1079,  1386,  1389,  1388,  1387,  1397,
    1393,  1404,  1405,  1410,  1392,  1412,  1409,  1401,  1402, -1079,
    1407,  1403,  1415,  1406,  1408,  1278,  1411,  1414,  1413,  1417,
    1416,  1419,  1420, -1079,  1421, -1079,  1422,  1418,  1424,  1423,
    1425, -1079,  1430,  1428,  1431,  1432, -1079, -1079,  1439,  1433,
    1426,  1427,  1434,  1390,  1435,  1436,  1440,  1442,  1445,  1449,
    1441, -1079,  1451, -1079,  1458, -1079,  1459,  1447,  1448, -1079,
    1452,  1450,  1453, -1079,  1454,  1457, -1079, -1079, -1079,  1466,
   -1079
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079,
   -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079,
    -737, -1079, -1079, -1079, -1079, -1079,  -751, -1078, -1079,   188,
     101, -1079,  -486,  -818,  -965,   352,  -960,  -504,  -941,  -879,
    -719,  -770,   506,   -80, -1079,  -925,   369,  -676,   484,  -537,
     -14,   114,     2,   205,  -273,  -471,   -15,  1444, -1079, -1079,
   -1079, -1079, -1079, -1079, -1079, -1079, -1079, -1079,  -444, -1079,
   -1079,   954, -1079, -1079, -1079, -1079, -1079,  -125,  1216,  1217,
    1218,  -293,  1208,  1210,  1224,  1243,  1246,  1247,  1256,  1257,
    1260,  1267,  -253,  -252,  -246,    35, -1079, -1079,  1270, -1079,
   -1079, -1079, -1079,  1328,  -255, -1079, -1079,  1209,  -291, -1079,
    1329, -1079,  1348,  1355,  -249, -1079,    46,    23,  -256,  1356,
   -1079,   956, -1079, -1079, -1079, -1079,  -165,  1359, -1079,  -262,
   -1079, -1079, -1079, -1079, -1079, -1079,  1360, -1079, -1079, -1079
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -213
static const yytype_int16 yytable[] =
{
     275,   878,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   273,   840,  1076,
     697,   374,  1051,   583,   433,   866,   394,   398,   641,   421,
     431,   644,   395,   399,  -212,   469,   470,   651,   632,   948,
     634,   660,   471,   629,   318,   320,   321,   322,   323,   324,
     325,   326,   327,  1182,   649,  1488,  1489,  1079,  1422,  1081,
     661,  1190,  1116,  1422,   712,     1,  1024,     2,    43,    34,
     436,   620,   655,    47,    48,    35,   422,   593,   340,   833,
     423,   391,   635,     3,    44,     4,     5,   439,   424,     6,
     441,  1369,  1291,   834,     7,     8,   650,   352,  1316,     9,
      10,    11,   662,    12,  1370,  1434,  1359,   688,  1371,   707,
    1423,  1317,  1087,  1088,  1089,  1430,   396,   400,   689,   690,
      33,   432,  1435,  1380,   708,  1022,   308,   608,   609,   610,
     611,   612,   613,   614,   615,   616,  1381,   340,   345,  1063,
     346,  1242,   347,   348,   754,  1243,   666,   341,  1164,  1064,
     349,  1266,   354,  1244,  1282,   302,   350,   351,   667,   352,
     420,   426,    38,   303,   668,   478,  1283,   352,    39,   495,
     496,    36,   319,   319,   319,   319,   319,   319,   319,   319,
     319,  1192,   435,   436,   437,   401,   390,   402,   536,   496,
     403,   391,   777,  1296,   438,  1171,  1473,   404,   392,    37,
     439,   440,  1474,   441,   778,  1297,  1475,  1345,  1346,    40,
    1186,  1187,   598,   599,   600,   601,   602,   603,   604,   605,
     606,   607,  1062,   621,   622,   623,   624,  1075,   627,   832,
     300,   838,   839,   580,   581,   305,   301,  1195,   580,   581,
    1533,   306,  1573,  1196,   580,   581,  1534,   854,  1574,    41,
    1578,   595,   596,  -212,  -212,  -212,  1579,   347,   597,   671,
     849,   415,   851,    42,  1104,   691,  1123,  1105,   879,  1124,
    1128,    45,  1145,  1099,   476,  1146,   886,   887,   888,   889,
     890,   891,   892,   893,   894,   895,   896,   897,   679,    -4,
      -4,  1364,  1365,  1223,   674,   670,  1099,   907,   908,   909,
     655,   673,    46,   389,  1077,  1078,   412,   721,   722,   806,
     270,   903,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   456,   472,   384,   386,   291,   294,   292,   494,
     293,   295,   296,   297,   298,   299,   304,    47,   340,   504,
     382,   387,   479,   480,   481,   505,   485,   506,   507,   508,
     509,   510,   483,   511,   486,   512,   513,   514,   515,   516,
     482,   517,   518,   519,   520,   521,   484,   487,   489,   523,
     488,   524,  1160,   490,   526,  1163,   492,   498,   493,   530,
     531,   532,  1357,   533,   534,   535,   308,   608,   609,   610,
     611,   612,   613,   614,   615,   616,   617,   540,   497,   541,
     499,   500,   543,   544,   501,   545,   546,   522,   502,   503,
     525,   550,   551,   552,   553,   554,   555,   556,   557,   558,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     527,  1425,   491,  1016,   491,   491,   491,   491,   491,   491,
     491,   491,   697,   528,   529,   537,   538,   539,  1212,   547,
     542,   548,   549,   559,   560,   561,   564,   569,  1050,   562,
     567,   910,   563,   568,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   565,   570,   339,   574,   571,   572,
     575,  1288,   573,   576,   577,  1044,   911,   578,  1065,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   271,
     694,   695,   308,   608,   609,   610,   611,   612,   613,   614,
     615,   616,   579,   584,   585,   586,   583,   619,   590,   587,
     588,   589,   592,   591,   593,   628,   619,   633,   619,   636,
     629,   638,   637,   645,   646,   642,   643,   647,   648,   652,
     663,   665,   619,   664,   686,   704,   705,   706,   619,   709,
     713,   711,   710,   682,   683,   684,   685,   715,   714,   700,
     703,   719,   720,   723,   716,   476,   476,   308,   608,   609,
     610,   611,   612,   613,   614,   615,   616,   717,   724,   733,
     734,   735,   736,   737,   738,   739,   740,   741,   742,   743,
     744,   745,   746,   718,   318,   320,   321,   322,   323,   324,
     325,   326,   327,   725,   697,   726,   748,   749,   750,   751,
     727,   728,   729,   730,   731,   732,   755,   756,   747,   752,
     753,   766,  1177,   757,   761,   762,   763,   758,   759,   764,
     760,   765,   619,   768,   767,   773,   769,   775,   774,   770,
     776,   771,   779,   772,   796,   799,   798,   800,   807,   809,
     808,   810,   811,   812,   813,   780,   781,   782,   783,   784,
     785,   786,   787,   788,   789,   790,   791,   792,   793,   794,
     795,   699,   797,   814,   816,   815,   801,   802,   803,   339,
     804,   805,   817,   818,   819,   823,   822,   826,   824,   825,
     828,   827,   829,   831,   830,   850,   862,   873,   856,   902,
     855,   860,   863,   861,   871,   874,   567,   567,   872,   882,
     880,   875,   881,   883,   885,   904,   884,   906,   913,   905,
     914,   915,   319,   319,   319,   319,   319,   319,   319,   319,
     319,   916,   917,   918,   919,   920,   921,   922,   923,   857,
     841,   926,   927,   844,   845,   846,   847,   924,   619,   925,
     619,   928,   853,   929,   930,   933,   935,   934,   859,   931,
     936,   932,   946,   950,   958,   868,   870,   953,   961,   947,
     951,   339,   877,   474,   952,   957,   959,   960,   965,   964,
     655,   966,   967,   968,   986,   969,   988,   989,   996,   990,
     998,  1002,   912,   997,  1001,   899,   999,   901,  1000,   619,
    1003,  1004,  1005,  1006,  1007,  1009,  1010,  1008,   319,   319,
    1011,  1012,   491,  1025,  1030,  1026,  1032,  1013,  1014,  1015,
     937,  1047,  1031,  1033,  1049,  1045,  1046,   938,  1052,   939,
     940,   941,  1048,   942,   943,  1053,  1055,  1054,   944,   945,
    1084,  1085,  1086,   949,   339,   339,  1090,  1091,  1092,  1093,
    1094,  1097,   956,  1098,   697,  1095,  1096,  1101,  1099,   859,
    1107,   962,  1100,   963,   339,  1102,  1103,  1106,  1108,  1114,
    1118,   970,   971,   972,   973,   974,   975,   976,   977,   978,
     979,   980,   981,  1115,   983,  1117,   985,  1119,   987,  1121,
    1122,  1125,   991,   992,   993,  1127,   994,   995,  1129,  1130,
    1132,  1137,  1133,  1138,  1142,  1143,  1147,   339,  1144,  1148,
    1155,  1149,  1150,  1151,  1152,  1154,  1157,  1158,   491,   491,
     319,  1153,  1159,  1156,  1165,  1166,  1183,  1205,  1211,  1168,
    1180,  1169,  1173,  1027,  1170,  1174,  1175,  1176,  1178,  1181,
    1179,  1018,  1019,  1020,  1184,   859,  1023,   870,  1188,  1189,
    1194,  1029,  1193,  1199,  1201,  1200,  1197,  1041,  1198,   566,
    1204,  1203,  1208,  1202,  1209,   877,  1206,  1207,  1215,  1210,
    1213,  1214,  1057,  1059,  1216,  1057,   619,  1069,  1071,  1218,
    1057,   700,   703,   703,  1041,  1492,  1041,  1217,  1219,  1220,
    1221,  1224,  1222,   870,   870,   870,  1225,  1227,  1228,  1230,
    1231,  1232,  1109,  1110,  1236,  1111,  1112,  1113,  1233,  1234,
    1235,  1238,  1239,  1248,   639,   640,  1237,  1240,  1241,  1247,
    1260,   804,   805,  1246,   319,   319,   491,  1245,   659,  1029,
    1249,  1250,  1252,  1253,  1254,  1256,  1126,  1255,  1257,  1258,
    1259,  1261,   702,  1131,  1262,  1264,  1265,   339,   339,  1267,
    1268,  1492,  1269,   339,  1270,  1272,  1271,   339,  1273,  1274,
    1134,  1275,  1276,  1277,   474,   474,  1278,  1280,  1279,   699,
     339,  1281,  1139,  1140,  1141,  1285,  1284,  1286,  1287,  1289,
    1290,  1291,  1293,  1294,  1292,  1298,  1300,  1295,  1299,  1301,
    1302,  1303,  1306,   699,  1304,  1309,   699,  1305,   699,  1307,
    1308,  1167,  1311,   339,  1310,   339,  1312,  1313,   491,   491,
    1315,  1314,  1319,  1318,  1320,  1029,  1321,  1322,  1324,  1326,
    1325,  1328,  1041,  1041,  1329,  1327,  1330,  1331,  1334,  1333,
    1332,  1336,  1337,  1059,  1340,  1341,  1069,  1041,  1041,  1343,
    1335,  1059,   868,   700,  1339,  1342,  1344,  1347,  1348,   319,
     319,  1349,  1338,  1350,  1351,  1352,  1354,  1353,  1355,  1359,
    1356,  1358,  1360,  1361,  1363,  1379,  1362,  1374,  1368,  1367,
    1226,  1366,  1372,  1373,  1376,  1229,  1375,  1377,  1378,  1382,
    1383,  1385,  1393,  1395,  1394,  1396,  1399,  1386,  1387,  1384,
    1388,  1398,  1389,  1390,  1392,  1400,  1402,  1251,  1403,  1397,
    1401,  1407,  1404,  1408,  1406,   566,   566,  1405,  1409,  1411,
    1413,  1410,  1415,  1417,  1414,  1418,  1419,  1420,  1424,  1422,
    1427,   659,   339,   842,   843,  1429,   339,  1412,  1071,   848,
    1431,  1059,  1426,   852,   699,   699,  1428,  1432,  1416,   339,
    1421,  1433,  1436,  1437,   339,   865,   865,  1438,  1434,   699,
     699,  1439,  1440,  1441,  1443,   699,  1442,  1444,  1446,  1447,
    1451,  1445,  1449,  1448,  1465,  1450,   339,  1454,  1457,  1453,
    1452,  1458,  1459,  1323,  1460,  1461,   898,  1455,   900,   339,
    1463,  1462,  1464,  1466,  1467,   339,  1469,   339,  1468,  1471,
    1470,  1472,  1477,  1476,  1480,  1479,  1478,  1481,  1483,  1482,
    1485,  1486,  1498,  1484,  1487,  1496,  1497,  1499,  1500,  1502,
    1501,  1503,  1504,  1505,  1509,  1513,  1511,  1512,  1629,  1507,
    1508,  1543,  1185,  1510,  1521,   877,  1523,  1263,  1524,  1514,
    1519,  1506,  1516,  1517,  1518,  1515,  1520,  1526,  1527,  1530,
    1525,  1528,  1391,  1529,  1531,  1532,  1537,  1535,  1536,  1538,
    1539,  1541,  1544,  1546,  1552,  1540,  1542,  1545,  1547,  1548,
    1550,  1551,  1554,  1553,  1563,  1555,   339,   339,  1566,  1556,
    1557,  1558,  1568,  1559,  1572,  1562,  1576,  1581,  1565,  1570,
    1585,  1569,  1571,  1583,  1584,  1567,  1575,  1577,  1580,  1586,
    1587,  1582,  1588,   700,  1589,  1591,  1592,  1590,  1560,  1561,
    1593,  1597,  1594,  1595,  1596,  1601,  1613,  1598,  1603,  1608,
    1456,  1606,  1600,  1611,  1605,  1564,  1599,  1602,  1604,  1614,
    1615,  1609,  1017,  1607,  1612,  1610,  1021,  1616,  1617,  1618,
    1619,  1620,  1621,  1622,  1626,  1623,  1625,  1627,  1034,  1624,
    1633,  1639,  1549,     0,  1628,  1632,  1641,  1634,  1642,  1630,
    1631,  1640,  1643,  1638,  1645,  1646,  1061,  1635,  1636,  1637,
    1644,  1074,  1647,  1650,   702,   702,  1649,  1080,  1657,  1082,
    1651,  1648,  1658,  1653,  1654,  1522,  1655,  1660,  1659,  1652,
    1656,  1661,  1662,  1663,  1664,  1665,  1666,  1669,  1670,  1667,
    1172,  1668,  1191,  1083,   307,   428,   459,   656,   460,   406,
     407,   408,     0,     0,     0,   699,   675,     0,     0,     0,
       0,     0,   461,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   462,     0,     0,   463,   464,     0,     0,     0,     0,
       0,     0,     0,     0,   465,   466,     0,     0,   467,     0,
       0,     0,     0,     0,   418,   468,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   865,  1161,  1162,   865,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   409,   410,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   430,     0,     0,     0,   411,   413,
       0,     0,   414,     0,     0,     0,     0,     0,   473,     0,
       0,   659,   328,    52,    53,    54,    55,    56,   329,   330,
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
     269,   820,     0,   270,   328,    52,    53,    54,    55,    56,
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
     267,   268,   269,     0,   821,   270,    51,    52,    53,    54,
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
     328,    52,    53,    54,  1035,  1036,    57,    58,    59,    60,
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
     261,   262,   263,   264,   265,   266,   267,   268,   269,   580,
     581,   328,    52,    53,    54,    55,    56,   329,   330,   331,
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
     955,    53,    54,    55,    56,   329,   330,   331,   332,   333,
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
     262,   263,   264,   265,   266,   267,   268,   269,   328,   982,
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
     263,   264,   265,   266,   267,   268,   269,   328,   984,    53,
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
     264,   265,   266,   267,   268,   269,   328,  1120,    53,    54,
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
     265,   266,   267,   268,   269,   328,  1135,    53,    54,    55,
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
     266,   267,   268,   269,   328,  1136,    53,    54,    55,    56,
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
      15,   771,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    15,   737,   979,
     557,   277,   963,   494,   286,   762,   281,   282,   532,   285,
     286,   535,   281,   282,     5,   288,   288,   541,   524,   857,
     526,   545,   288,    32,    58,    59,    60,    61,    62,    63,
      64,    65,    66,  1131,   540,    33,    34,   982,    37,   984,
     546,  1139,  1027,    37,   568,     1,   945,     3,    23,    30,
      20,   515,   543,   225,   226,    36,    19,    27,    21,    20,
      23,    24,   526,    19,    39,    21,    22,    37,    31,    25,
      40,    21,    22,    34,    30,    31,   540,    40,    23,    35,
      36,    37,   546,    39,    34,    21,    22,    19,    38,    22,
      89,    36,   991,   992,   993,    89,   281,   282,    30,    31,
      22,   286,    38,    23,    37,   943,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    36,    21,    19,    22,
      21,    19,    23,    24,   630,    23,    19,    31,  1113,    32,
      31,  1229,   277,    31,    22,    30,    37,    38,    31,    40,
     285,   286,    27,    38,    37,   290,    34,    40,    33,    39,
      40,    23,    58,    59,    60,    61,    62,    63,    64,    65,
      66,  1141,    19,    20,    21,    19,    19,    21,    39,    40,
      24,    24,    27,    22,    31,  1120,    21,    31,    31,    23,
      37,    38,    27,    40,    39,    34,    31,    21,    22,    19,
    1135,  1136,   505,   506,   507,   508,   509,   510,   511,   512,
     513,   514,   973,   516,   517,   518,   519,   978,   521,   733,
      31,   735,   736,   222,   223,    31,    37,    21,   222,   223,
      21,    37,    21,    27,   222,   223,    27,   751,    27,    39,
      21,   504,   504,   224,   225,   226,    27,    23,   504,   550,
     746,    27,   748,    23,    34,   556,    34,    37,   772,    37,
      34,    32,    34,    37,   289,    37,   780,   781,   782,   783,
     784,   785,   786,   787,   788,   789,   790,   791,   550,   225,
     226,    21,    22,    34,   550,   550,    37,   801,   802,   803,
     771,   550,     0,   280,   980,   981,   283,   580,   581,     6,
     224,   797,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,   287,   288,   278,   279,    22,    37,    23,   344,
      23,    38,    37,    19,    34,    27,    20,   225,    21,   354,
      31,    31,    19,    19,    38,   360,    33,   362,   363,   364,
     365,   366,    22,   368,    23,   370,   371,   372,   373,   374,
      38,   376,   377,   378,   379,   380,    38,    23,    19,   384,
      37,   386,  1109,    39,   389,  1112,    26,    32,    27,   394,
     395,   396,  1323,   398,   399,   400,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,   412,    26,   414,
      42,    27,   417,   418,    23,   420,   421,    27,    33,    33,
      27,   426,   427,   428,   429,   430,   431,   432,   433,   434,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      39,  1391,   318,   937,   320,   321,   322,   323,   324,   325,
     326,   327,   979,    42,    27,    26,    42,    27,  1167,    39,
      32,    21,    27,    39,    39,    26,    33,    36,   962,    27,
     475,     6,    38,   478,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    33,    38,   271,    21,    36,    40,
      21,  1251,    38,    34,    20,   956,     6,    19,   974,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    15,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    22,    22,    19,    19,   987,   515,    36,    25,
      89,    22,    30,    38,    27,    22,   524,    22,   526,    22,
      32,    22,    89,    22,    19,   533,   534,    89,    22,    37,
      22,    22,   540,    26,    32,    22,    24,    19,   546,    36,
      23,    27,    38,   551,   552,   553,   554,    23,    33,   557,
     558,    32,    27,    27,    38,   580,   581,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    36,    27,   594,
     595,   596,   597,   598,   599,   600,   601,   602,   603,   604,
     605,   606,   607,    37,   608,   609,   610,   611,   612,   613,
     614,   615,   616,    32,  1141,    27,   621,   622,   623,   624,
      37,    27,    40,    19,    39,    32,   631,   632,    30,    27,
      33,    32,  1126,    27,   639,   640,   641,    27,    37,   644,
      27,    27,   630,    27,    37,    27,    38,    27,    33,   654,
      39,   656,    33,   658,    19,    23,    39,    27,    27,    32,
      24,    27,    21,    23,    19,   670,   671,   672,   673,   674,
     675,   676,   677,   678,   679,   680,   681,   682,   683,   684,
     685,   557,   687,    21,    27,    43,   691,   692,   693,   474,
     694,   695,    21,    32,    89,    30,    33,    23,    32,    32,
      23,    89,    30,    24,    31,    30,    23,    23,    32,    31,
      89,    89,    89,    33,    33,    89,   721,   722,    32,    22,
      33,    36,    89,    22,    30,    22,    38,    22,    33,    40,
      23,    32,   608,   609,   610,   611,   612,   613,   614,   615,
     616,    89,    23,    19,    30,    23,    20,    36,    23,   754,
     738,    19,    23,   741,   742,   743,   744,    27,   746,    89,
     748,    23,   750,    32,    27,    23,    43,    33,   756,    36,
      23,    89,    27,    27,    23,   763,   764,    27,    39,    89,
      89,   566,   770,   289,    32,    89,    32,    27,    27,    89,
    1251,    27,    27,    23,    23,    33,    27,    23,    89,    27,
      23,    89,   806,    36,    31,   793,    27,   795,    30,   797,
      89,    23,    27,    30,    32,    20,    30,    33,   694,   695,
      22,    32,   698,    32,    32,    31,    22,    40,    38,    36,
     835,    22,    33,    32,    31,    33,    30,   842,    33,   844,
     845,   846,    32,   848,   849,    32,    89,    33,   853,   854,
      33,    30,    89,   858,   639,   640,    33,    89,    30,    32,
      30,    21,   867,    20,  1391,    89,    40,    30,    37,   857,
      23,   876,    39,   878,   659,    37,    37,    33,    21,    37,
      39,   886,   887,   888,   889,   890,   891,   892,   893,   894,
     895,   896,   897,    33,   899,    37,   901,    34,   903,     5,
      39,    23,   907,   908,   909,    39,   910,   911,    89,    27,
      23,    89,    33,    21,    39,    24,    19,   702,    89,    21,
      39,    33,    33,    23,    38,    23,    27,    37,   804,   805,
     806,    38,    23,    38,    38,    22,    24,    89,    19,    38,
      33,    38,    38,   948,    39,    39,    38,    32,    38,    32,
      39,   939,   940,   941,    32,   943,   944,   945,    33,    33,
      27,   949,    38,    32,    27,    33,    39,   955,    38,   475,
      34,    36,    21,    39,    32,   963,    38,    36,    38,    36,
      36,    34,   970,   971,    34,   973,   974,   975,   976,    36,
     978,   979,   980,   981,   982,  1456,   984,    38,    38,    34,
      38,    19,    39,   991,   992,   993,    23,    39,    32,    34,
      30,    33,  1017,  1018,    23,  1020,  1021,  1022,    32,    38,
      36,    21,    32,    38,   530,   531,    39,    39,    39,    23,
      38,  1035,  1036,    39,   910,   911,   912,    89,   544,  1027,
      39,    30,    39,    39,    89,    89,  1051,    39,    39,    39,
      89,    39,   558,  1058,    39,    38,    38,   842,   843,    39,
      30,  1522,    39,   848,    24,    39,    89,   852,    33,    32,
    1075,    23,    38,    31,   580,   581,    38,    32,    39,   955,
     865,    27,  1087,  1088,  1089,    89,    31,    19,    31,    31,
      38,    22,    22,    31,    38,    34,    30,    38,    38,    34,
      36,    38,    22,   979,    32,    38,   982,    33,   984,    31,
      39,  1116,    23,   898,    89,   900,    89,    22,   994,   995,
      22,    25,    23,    33,    21,  1113,    25,    23,    23,    23,
      89,    23,  1120,  1121,    23,    89,    89,    23,    89,    39,
      33,    39,    33,  1131,    23,    23,  1134,  1135,  1136,    21,
      38,  1139,  1140,  1141,    38,    37,    32,    27,    27,  1035,
    1036,    27,    89,    40,    27,    36,    33,    32,    23,    22,
      32,    32,    40,    22,    32,    26,    40,    22,    38,    36,
    1185,    40,    38,    30,    32,  1190,    40,    33,    38,    33,
      32,    27,    23,    23,    27,    27,    23,    40,    38,    89,
      38,    26,    39,    38,    38,    27,    89,  1212,    26,    38,
      38,    30,    33,    23,    89,   721,   722,    43,    27,    39,
      19,    38,    27,    23,    40,    27,    21,    23,    32,    37,
      21,   737,  1017,   739,   740,    21,  1021,    89,  1226,   745,
      19,  1229,    40,   749,  1120,  1121,    40,    40,    89,  1034,
      89,    21,    19,    36,  1039,   761,   762,    34,    21,  1135,
    1136,    23,    40,    21,    32,  1141,    89,    31,    27,    40,
      23,    32,    37,    33,    26,    32,  1061,    31,    27,    34,
      36,    23,    27,  1288,    23,    31,   792,    38,   794,  1074,
      27,    32,    23,    43,    32,  1080,    23,  1082,    38,    27,
      36,    23,    19,    38,    23,    21,    32,    39,    37,    34,
      19,    19,    19,    89,    89,    21,    21,    32,    21,    19,
      89,    34,    32,    21,    19,    36,    23,    23,    40,    33,
      32,    19,  1134,    34,    23,  1323,    23,  1226,    23,    38,
      31,    89,    34,    36,    34,    39,    32,    23,    23,    23,
      34,    34,  1357,    32,    23,    23,    34,    39,    24,    30,
      37,    34,    19,    19,    19,    89,    38,    37,    89,    36,
      30,    89,    30,    32,    39,    89,  1161,  1162,    31,    33,
      32,    32,    22,    33,    23,    34,    24,    19,    36,    34,
      23,    37,    36,    22,    19,    42,    39,    38,    34,    23,
      27,    38,    19,  1391,    19,    33,    32,    30,    89,    89,
      32,    19,    33,    33,    32,    31,    19,    36,    31,    24,
    1425,    31,    36,    24,    36,    89,    89,    38,    37,    22,
      27,    38,   938,    39,    36,    39,   942,    23,    23,    19,
      38,    19,    23,    32,    19,    33,    33,    31,   954,    32,
      23,    23,  1522,    -1,    36,    32,    23,    31,    23,    38,
      36,    27,    22,    31,    23,    23,   972,    38,    38,    38,
      32,   977,    23,    36,   980,   981,    40,   983,    23,   985,
      36,    38,    23,    38,    38,  1490,    36,    26,    37,    89,
      38,    23,    23,    36,    36,    33,    36,    30,    22,    36,
    1121,    37,  1140,   987,    50,   286,   288,   543,   288,   283,
     283,   283,    -1,    -1,    -1,  1391,   550,    -1,    -1,    -1,
      -1,    -1,   288,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   288,    -1,    -1,   288,   288,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   288,   288,    -1,    -1,   288,    -1,
      -1,    -1,    -1,    -1,   284,   288,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1109,  1110,  1111,  1112,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   283,   283,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   286,    -1,    -1,    -1,   283,   283,
      -1,    -1,   283,    -1,    -1,    -1,    -1,    -1,   288,    -1,
      -1,  1167,     3,     4,     5,     6,     7,     8,     9,    10,
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
      36,    37,    39,   228,   229,   230,   231,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   299,   300,   301,   302,
     303,   362,   366,    22,    30,    36,    23,    23,    27,    33,
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
      21,    31,   232,   304,   345,    19,    21,    23,    24,    31,
      37,    38,    40,   238,   304,   305,   306,   307,   322,   323,
     325,   330,   331,   332,   333,   334,   335,   337,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   353,   354,
     355,   356,    31,   235,   343,   236,   343,    31,   242,   344,
      19,    24,    31,   240,   331,   341,   353,   243,   331,   341,
     353,    19,    21,    24,    31,   249,   305,   306,   307,   330,
     337,   340,   344,   346,   354,    27,   244,   324,   325,   237,
     304,   345,    19,    23,    31,   239,   304,   329,   334,   338,
     339,   345,   353,   356,   365,    19,    20,    21,    31,    37,
      38,    40,   233,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   363,   234,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   363,   275,   281,   283,   241,   304,    19,
      19,    38,    38,    22,    38,    33,    23,    23,    37,    19,
      39,   278,    26,    27,   283,    39,    40,    26,    32,    42,
      27,    23,    33,    33,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   283,   283,
     283,   283,    27,   283,   283,    27,   283,    39,    42,    27,
     283,   283,   283,   283,   283,   283,    39,    26,    42,    27,
     283,   283,    32,   283,   283,   283,   283,    39,    21,    27,
     283,   283,   283,   283,   283,   283,   283,   283,   283,    39,
      39,    26,    27,    38,    33,    33,   275,   283,   283,    36,
      38,    36,    40,    38,    21,    21,    34,    20,    19,    22,
     222,   223,   269,   282,    22,    19,    19,    25,    89,    22,
      36,    38,    30,    27,   308,   319,   320,   321,   308,   308,
     308,   308,   308,   308,   308,   308,   308,   308,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,   259,   279,
     295,   308,   308,   308,   308,   264,   279,   308,    22,    32,
     246,   298,   259,    22,   259,   295,    22,    89,    22,   275,
     275,   264,   279,   279,   264,    22,    19,    89,    22,   259,
     295,   264,    37,   250,   268,   282,   298,   251,   267,   275,
     264,   259,   295,    22,    26,    22,    19,    31,    37,   245,
     331,   335,   336,   341,   345,   348,   349,   350,   351,   356,
     358,   359,   279,   279,   279,   279,    32,   364,    19,    30,
      31,   335,   352,   357,     7,     8,   263,   276,   277,   278,
     279,   274,   275,   279,    22,    24,    19,    22,    37,    36,
      38,    27,   264,    23,    33,    23,    38,    36,    37,    32,
      27,   281,   281,    27,    27,    32,    27,    37,    27,    40,
      19,    39,    32,   283,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,    30,   283,   283,
     283,   283,    27,    33,   259,   283,   283,    27,    27,    37,
      27,   283,   283,   283,   283,    27,    32,    37,    27,    38,
     283,   283,   283,    27,    33,    27,    39,    27,    39,    33,
     283,   283,   283,   283,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,    19,   283,    39,    23,
      27,   283,   283,   283,   277,   277,     6,    27,    24,    32,
      27,    21,    23,    19,    21,    43,    27,    21,    32,    89,
     222,   223,    33,    30,    32,    32,    23,    89,    23,    30,
      31,    24,   264,    20,    34,   248,   360,   361,   264,   264,
     267,   279,   275,   275,   279,   279,   279,   279,   275,   259,
      30,   259,   275,   279,   264,    89,    32,   283,   260,   279,
      89,    33,    23,    89,   247,   275,   247,   262,   279,   266,
     279,    33,    32,    23,    89,    36,   265,   279,   268,   264,
      33,    89,    22,    22,    38,    30,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   275,   279,
     275,   279,    31,   259,    22,    40,    22,   264,   264,   264,
       6,     6,   277,    33,    23,    32,    89,    23,    19,    30,
      23,    20,    36,    23,    27,    89,    19,    23,    23,    32,
      27,    36,    89,    23,    33,    43,    23,   283,   283,   283,
     283,   283,   283,   283,   283,   283,    27,    89,   260,   283,
      27,    89,    32,    27,   283,     4,   283,    89,    23,    32,
      27,    39,   283,   283,    89,    27,    27,    27,    23,    33,
     283,   283,   283,   283,   283,   283,   283,   283,   283,   283,
     283,   283,     4,   283,     4,   283,    23,   283,    27,    23,
      27,   283,   283,   283,   277,   277,    89,    36,    23,    27,
      30,    31,    89,    89,    23,    27,    30,    32,    33,    20,
      30,    22,    32,    40,    38,    36,   264,   275,   279,   279,
     279,   275,   260,   279,   266,    32,    31,   283,   261,   279,
      32,    33,    22,    32,   275,     7,     8,   272,   273,   275,
     276,   279,   282,   271,   282,    33,    30,    22,    32,    31,
     264,   265,    33,    32,    33,    89,   253,   279,   254,   279,
     255,   275,   253,    22,    32,   259,   296,   297,   256,   279,
     257,   279,   295,   258,   275,   253,   263,   274,   274,   272,
     275,   272,   275,   269,    33,    30,    89,   266,   266,   266,
      33,    89,    30,    32,    30,    89,    40,    21,    20,    37,
      39,    30,    37,    37,    34,    37,    33,    23,    21,   283,
     283,   283,   283,   283,    37,    33,   261,    37,    39,    34,
       4,     5,    39,    34,    37,    23,   283,    39,    34,    89,
      27,   283,    23,    33,   283,     4,     4,    89,    21,   283,
     283,   283,    39,    24,    89,    34,    37,    19,    21,    33,
      33,    23,    38,    38,    23,    39,    38,    27,    37,    23,
     247,   275,   275,   247,   261,    38,    22,   283,    38,    38,
      39,   272,   273,    38,    39,    38,    32,   264,    38,    39,
      33,    32,   254,    24,    32,   256,   272,   272,    33,    33,
     254,   262,   263,    38,    27,    21,    27,    39,    38,    32,
      33,    27,    39,    36,    34,    89,    38,    36,    21,    32,
      36,    19,   267,    36,    34,    38,    34,    38,    36,    38,
      34,    38,    39,    34,    19,    23,   283,    39,    32,   283,
      34,    30,    33,    32,    38,    36,    23,    39,    21,    32,
      39,    39,    19,    23,    31,    89,    39,    23,    38,    39,
      30,   283,    39,    39,    89,    39,    89,    39,    39,    89,
      38,    39,    39,   257,    38,    38,   254,    39,    30,    39,
      24,    89,    39,    33,    32,    23,    38,    31,    38,    39,
      32,    27,    22,    34,    31,    89,    19,    31,   268,    31,
      38,    22,    38,    22,    31,    38,    22,    34,    34,    38,
      30,    34,    36,    38,    32,    33,    22,    31,    39,    38,
      89,    23,    89,    22,    25,    22,    23,    36,    33,    23,
      21,    25,    23,   283,    23,    89,    23,    89,    23,    23,
      89,    23,    33,    39,    89,    38,    39,    33,    89,    38,
      23,    23,    37,    21,    32,    21,    22,    27,    27,    27,
      40,    27,    36,    32,    33,    23,    32,   265,    32,    22,
      40,    22,    40,    32,    21,    22,    40,    36,    38,    21,
      34,    38,    38,    30,    22,    40,    32,    33,    38,    26,
      23,    36,    33,    32,    89,    27,    40,    38,    38,    39,
      38,   283,    38,    23,    27,    23,    27,    38,    26,    23,
      27,    38,    89,    26,    33,    43,    89,    30,    23,    27,
      38,    39,    89,    19,    40,    27,    89,    23,    27,    21,
      23,    89,    37,    89,    32,   263,    40,    21,    40,    21,
      89,    19,    40,    21,    21,    38,    19,    36,    34,    23,
      40,    21,    89,    32,    31,    32,    27,    40,    33,    37,
      32,    23,    36,    34,    31,    38,   283,    27,    23,    27,
      23,    31,    32,    27,    23,    26,    43,    32,    38,    23,
      36,    27,    23,    21,    27,    31,    38,    19,    32,    21,
      23,    39,    34,    37,    89,    19,    19,    89,    33,    34,
     252,   270,   282,   326,   327,   328,    21,    21,    19,    32,
      21,    89,    19,    34,    32,    21,    89,    33,    32,    19,
      34,    23,    23,    36,    38,    39,    34,    36,    34,    31,
      32,    23,   283,    23,    23,    34,    23,    23,    34,    32,
      23,    23,    23,    21,    27,    39,    24,    34,    30,    37,
      89,    34,    38,    19,    19,    37,    19,    89,    36,   270,
      30,    89,    19,    32,    30,    89,    33,    32,    32,    33,
      89,    89,    34,    39,    89,    36,    31,    42,    22,    37,
      34,    36,    23,    21,    27,    39,    24,    38,    21,    27,
      34,    19,    38,    22,    19,    23,    23,    27,    19,    19,
      30,    33,    32,    32,    33,    33,    32,    19,    36,    89,
      36,    31,    38,    31,    37,    36,    31,    39,    24,    38,
      39,    24,    36,    19,    22,    27,    23,    23,    19,    38,
      19,    23,    32,    33,    32,    33,    19,    31,    36,    40,
      38,    36,    32,    23,    31,    38,    38,    38,    31,    23,
      27,    23,    23,    22,    32,    23,    23,    23,    38,    40,
      36,    36,    89,    38,    38,    36,    38,    23,    23,    37,
      26,    23,    23,    36,    36,    33,    36,    36,    37,    30,
      22
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
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_instr_map_count); }
    break;

  case 43:
#line 148 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_instr_map_info);  }
    break;

  case 44:
#line 149 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_instr_count);     }
    break;

  case 45:
#line 150 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_midi_instr_info);      }
    break;

  case 46:
#line 151 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_misc);                 }
    break;

  case 47:
#line 152 "lscp.y"
    { (yyval.String) = LSCPSERVER->SubscribeNotification(LSCPEvent::event_total_voice_count);    }
    break;

  case 48:
#line 155 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_audio_device_count);   }
    break;

  case 49:
#line 156 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_audio_device_info);    }
    break;

  case 50:
#line 157 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_device_count);    }
    break;

  case 51:
#line 158 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_device_info);     }
    break;

  case 52:
#line 159 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_channel_count);        }
    break;

  case 53:
#line 160 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_voice_count);          }
    break;

  case 54:
#line 161 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_stream_count);         }
    break;

  case 55:
#line 162 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_buffer_fill);          }
    break;

  case 56:
#line 163 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_channel_info);         }
    break;

  case 57:
#line 164 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_instr_map_count); }
    break;

  case 58:
#line 165 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_instr_map_info);  }
    break;

  case 59:
#line 166 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_instr_count);     }
    break;

  case 60:
#line 167 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_midi_instr_info);      }
    break;

  case 61:
#line 168 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_misc);                 }
    break;

  case 62:
#line 169 "lscp.y"
    { (yyval.String) = LSCPSERVER->UnsubscribeNotification(LSCPEvent::event_total_voice_count);    }
    break;

  case 63:
#line 172 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping((yyvsp[(4) - (16)].Number),(yyvsp[(6) - (16)].Number),(yyvsp[(8) - (16)].Number),(yyvsp[(10) - (16)].String),(yyvsp[(12) - (16)].String),(yyvsp[(14) - (16)].Number),(yyvsp[(16) - (16)].Dotnum),MidiInstrumentMapper::VOID,"",(yyvsp[(3) - (16)].Bool)); }
    break;

  case 64:
#line 173 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping((yyvsp[(4) - (18)].Number),(yyvsp[(6) - (18)].Number),(yyvsp[(8) - (18)].Number),(yyvsp[(10) - (18)].String),(yyvsp[(12) - (18)].String),(yyvsp[(14) - (18)].Number),(yyvsp[(16) - (18)].Dotnum),(yyvsp[(18) - (18)].LoadMode),"",(yyvsp[(3) - (18)].Bool)); }
    break;

  case 65:
#line 174 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping((yyvsp[(4) - (18)].Number),(yyvsp[(6) - (18)].Number),(yyvsp[(8) - (18)].Number),(yyvsp[(10) - (18)].String),(yyvsp[(12) - (18)].String),(yyvsp[(14) - (18)].Number),(yyvsp[(16) - (18)].Dotnum),MidiInstrumentMapper::VOID,(yyvsp[(18) - (18)].String),(yyvsp[(3) - (18)].Bool)); }
    break;

  case 66:
#line 175 "lscp.y"
    { (yyval.String) = LSCPSERVER->AddOrReplaceMIDIInstrumentMapping((yyvsp[(4) - (20)].Number),(yyvsp[(6) - (20)].Number),(yyvsp[(8) - (20)].Number),(yyvsp[(10) - (20)].String),(yyvsp[(12) - (20)].String),(yyvsp[(14) - (20)].Number),(yyvsp[(16) - (20)].Dotnum),(yyvsp[(18) - (20)].LoadMode),(yyvsp[(20) - (20)].String),(yyvsp[(3) - (20)].Bool)); }
    break;

  case 67:
#line 178 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveMIDIInstrumentMapping((yyvsp[(3) - (7)].Number),(yyvsp[(5) - (7)].Number),(yyvsp[(7) - (7)].Number)); }
    break;

  case 68:
#line 181 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveChannel((yyvsp[(3) - (3)].Number));             }
    break;

  case 69:
#line 182 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveMidiInstrumentMap((yyvsp[(3) - (3)].Number));   }
    break;

  case 70:
#line 183 "lscp.y"
    { (yyval.String) = LSCPSERVER->RemoveAllMidiInstrumentMaps(); }
    break;

  case 71:
#line 186 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAvailableEngines();                          }
    break;

  case 72:
#line 187 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAvailableMidiInputDrivers();                 }
    break;

  case 73:
#line 188 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDriverInfo((yyvsp[(5) - (5)].String));                     }
    break;

  case 74:
#line 189 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDriverParameterInfo((yyvsp[(5) - (7)].String), (yyvsp[(7) - (7)].String));        }
    break;

  case 75:
#line 190 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDriverParameterInfo((yyvsp[(5) - (9)].String), (yyvsp[(7) - (9)].String), (yyvsp[(9) - (9)].KeyValList));    }
    break;

  case 76:
#line 191 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAvailableAudioOutputDrivers();               }
    break;

  case 77:
#line 192 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDriverInfo((yyvsp[(5) - (5)].String));                   }
    break;

  case 78:
#line 193 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDriverParameterInfo((yyvsp[(5) - (7)].String), (yyvsp[(7) - (7)].String));      }
    break;

  case 79:
#line 194 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDriverParameterInfo((yyvsp[(5) - (9)].String), (yyvsp[(7) - (9)].String), (yyvsp[(9) - (9)].KeyValList));  }
    break;

  case 80:
#line 195 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDeviceCount();                    }
    break;

  case 81:
#line 196 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDeviceCount();                      }
    break;

  case 82:
#line 197 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDeviceInfo((yyvsp[(5) - (5)].Number));                   }
    break;

  case 83:
#line 198 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDeviceInfo((yyvsp[(5) - (5)].Number));                     }
    break;

  case 84:
#line 199 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputPortInfo((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number));                   }
    break;

  case 85:
#line 200 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputPortParameterInfo((yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].Number), (yyvsp[(9) - (9)].String));      }
    break;

  case 86:
#line 201 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputChannelInfo((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number));              }
    break;

  case 87:
#line 202 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputChannelParameterInfo((yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].Number), (yyvsp[(9) - (9)].String)); }
    break;

  case 88:
#line 203 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetChannels();                                  }
    break;

  case 89:
#line 204 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetChannelInfo((yyvsp[(5) - (5)].Number));                             }
    break;

  case 90:
#line 205 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetBufferFill((yyvsp[(5) - (7)].FillResponse), (yyvsp[(7) - (7)].Number));                          }
    break;

  case 91:
#line 206 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetStreamCount((yyvsp[(5) - (5)].Number));                             }
    break;

  case 92:
#line 207 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetVoiceCount((yyvsp[(5) - (5)].Number));                              }
    break;

  case 93:
#line 208 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetEngineInfo((yyvsp[(5) - (5)].String));                              }
    break;

  case 94:
#line 209 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetServerInfo();                                }
    break;

  case 95:
#line 210 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetTotalVoiceCount();                                }
    break;

  case 96:
#line 211 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetTotalVoiceCountMax();                        }
    break;

  case 97:
#line 212 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInstrumentMappings((yyvsp[(3) - (3)].Number));                  }
    break;

  case 98:
#line 213 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAllMidiInstrumentMappings();                 }
    break;

  case 99:
#line 214 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInstrumentMapping((yyvsp[(5) - (9)].Number),(yyvsp[(7) - (9)].Number),(yyvsp[(9) - (9)].Number));             }
    break;

  case 100:
#line 215 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInstrumentMaps();                        }
    break;

  case 101:
#line 216 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInstrumentMap((yyvsp[(5) - (5)].Number));                       }
    break;

  case 102:
#line 217 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetFxSends((yyvsp[(3) - (3)].Number));                                 }
    break;

  case 103:
#line 218 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetFxSendInfo((yyvsp[(5) - (7)].Number),(yyvsp[(7) - (7)].Number));                           }
    break;

  case 104:
#line 219 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetGlobalVolume();                              }
    break;

  case 105:
#line 222 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputDeviceParameter((yyvsp[(3) - (7)].Number), (yyvsp[(5) - (7)].String), (yyvsp[(7) - (7)].String));      }
    break;

  case 106:
#line 223 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputChannelParameter((yyvsp[(3) - (9)].Number), (yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].String), (yyvsp[(9) - (9)].String)); }
    break;

  case 107:
#line 224 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMidiInputDeviceParameter((yyvsp[(3) - (7)].Number), (yyvsp[(5) - (7)].String), (yyvsp[(7) - (7)].String));        }
    break;

  case 108:
#line 225 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMidiInputPortParameter((yyvsp[(3) - (9)].Number), (yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].String), (yyvsp[(9) - (9)].String));      }
    break;

  case 109:
#line 226 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                         }
    break;

  case 110:
#line 227 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMidiInstrumentMapName((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].String));               }
    break;

  case 111:
#line 228 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetFxSendAudioOutputChannel((yyvsp[(5) - (11)].Number),(yyvsp[(7) - (11)].Number),(yyvsp[(9) - (11)].Number),(yyvsp[(11) - (11)].Number)); }
    break;

  case 112:
#line 229 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetFxSendMidiController((yyvsp[(5) - (9)].Number),(yyvsp[(7) - (9)].Number),(yyvsp[(9) - (9)].Number));              }
    break;

  case 113:
#line 230 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetFxSendLevel((yyvsp[(5) - (9)].Number),(yyvsp[(7) - (9)].Number),(yyvsp[(9) - (9)].Dotnum));                       }
    break;

  case 114:
#line 231 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetEcho((yyparse_param_t*) yyparse_param, (yyvsp[(3) - (3)].Dotnum));  }
    break;

  case 115:
#line 232 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetGlobalVolume((yyvsp[(3) - (3)].Dotnum));                            }
    break;

  case 116:
#line 235 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateAudioOutputDevice((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].KeyValList)); }
    break;

  case 117:
#line 236 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateAudioOutputDevice((yyvsp[(3) - (3)].String));    }
    break;

  case 118:
#line 237 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateMidiInputDevice((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].KeyValList));   }
    break;

  case 119:
#line 238 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateMidiInputDevice((yyvsp[(3) - (3)].String));      }
    break;

  case 120:
#line 239 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateFxSend((yyvsp[(3) - (5)].Number),(yyvsp[(5) - (5)].Number));            }
    break;

  case 121:
#line 240 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateFxSend((yyvsp[(3) - (7)].Number),(yyvsp[(5) - (7)].Number),(yyvsp[(7) - (7)].String)); }
    break;

  case 122:
#line 243 "lscp.y"
    { (yyval.String) = LSCPSERVER->ResetChannel((yyvsp[(3) - (3)].Number)); }
    break;

  case 123:
#line 246 "lscp.y"
    { (yyval.String) = LSCPSERVER->ClearMidiInstrumentMappings((yyvsp[(3) - (3)].Number));  }
    break;

  case 124:
#line 247 "lscp.y"
    { (yyval.String) = LSCPSERVER->ClearAllMidiInstrumentMappings(); }
    break;

  case 125:
#line 250 "lscp.y"
    { (yyval.String) = LSCPSERVER->DestroyAudioOutputDevice((yyvsp[(3) - (3)].Number)); }
    break;

  case 126:
#line 251 "lscp.y"
    { (yyval.String) = LSCPSERVER->DestroyMidiInputDevice((yyvsp[(3) - (3)].Number));   }
    break;

  case 127:
#line 252 "lscp.y"
    { (yyval.String) = LSCPSERVER->DestroyFxSend((yyvsp[(3) - (5)].Number),(yyvsp[(5) - (5)].Number)); }
    break;

  case 128:
#line 255 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String); }
    break;

  case 129:
#line 256 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String); }
    break;

  case 130:
#line 259 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputDevice((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));      }
    break;

  case 131:
#line 260 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputChannel((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number), (yyvsp[(3) - (7)].Number)); }
    break;

  case 132:
#line 261 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputType((yyvsp[(5) - (5)].String), (yyvsp[(3) - (5)].Number));        }
    break;

  case 133:
#line 262 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInput((yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].Number), (yyvsp[(9) - (9)].Number), (yyvsp[(3) - (9)].Number));      }
    break;

  case 134:
#line 263 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputDevice((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));        }
    break;

  case 135:
#line 264 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputPort((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));          }
    break;

  case 136:
#line 265 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputChannel((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));       }
    break;

  case 137:
#line 266 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputType((yyvsp[(5) - (5)].String), (yyvsp[(3) - (5)].Number));          }
    break;

  case 138:
#line 267 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetVolume((yyvsp[(5) - (5)].Dotnum), (yyvsp[(3) - (5)].Number));                 }
    break;

  case 139:
#line 268 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMute((yyvsp[(5) - (5)].Dotnum), (yyvsp[(3) - (5)].Number));            }
    break;

  case 140:
#line 269 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelSolo((yyvsp[(5) - (5)].Dotnum), (yyvsp[(3) - (5)].Number));            }
    break;

  case 141:
#line 270 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMap((yyvsp[(3) - (5)].Number), (yyvsp[(5) - (5)].Number));             }
    break;

  case 142:
#line 271 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMap((yyvsp[(3) - (5)].Number), -1);             }
    break;

  case 143:
#line 272 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMap((yyvsp[(3) - (5)].Number), -2);             }
    break;

  case 144:
#line 275 "lscp.y"
    { (yyval.Bool) = true;  }
    break;

  case 145:
#line 276 "lscp.y"
    { (yyval.Bool) = false; }
    break;

  case 146:
#line 279 "lscp.y"
    { (yyval.KeyValList)[(yyvsp[(1) - (3)].String)] = (yyvsp[(3) - (3)].String);          }
    break;

  case 147:
#line 280 "lscp.y"
    { (yyval.KeyValList) = (yyvsp[(1) - (5)].KeyValList); (yyval.KeyValList)[(yyvsp[(3) - (5)].String)] = (yyvsp[(5) - (5)].String); }
    break;

  case 148:
#line 283 "lscp.y"
    { (yyval.FillResponse) = fill_response_bytes;      }
    break;

  case 149:
#line 284 "lscp.y"
    { (yyval.FillResponse) = fill_response_percentage; }
    break;

  case 150:
#line 287 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDevices();           }
    break;

  case 151:
#line 288 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDevices();             }
    break;

  case 152:
#line 289 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListChannels();                    }
    break;

  case 153:
#line 290 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableEngines();            }
    break;

  case 154:
#line 291 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableMidiInputDrivers();   }
    break;

  case 155:
#line 292 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableAudioOutputDrivers(); }
    break;

  case 156:
#line 293 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListMidiInstrumentMappings((yyvsp[(3) - (3)].Number));    }
    break;

  case 157:
#line 294 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAllMidiInstrumentMappings();   }
    break;

  case 158:
#line 295 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListMidiInstrumentMaps();          }
    break;

  case 159:
#line 296 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListFxSends((yyvsp[(3) - (3)].Number));                   }
    break;

  case 160:
#line 299 "lscp.y"
    { (yyval.String) = LSCPSERVER->LoadInstrument((yyvsp[(1) - (5)].String), (yyvsp[(3) - (5)].Number), (yyvsp[(5) - (5)].Number));       }
    break;

  case 161:
#line 300 "lscp.y"
    { (yyval.String) = LSCPSERVER->LoadInstrument((yyvsp[(3) - (7)].String), (yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number), true); }
    break;

  case 162:
#line 303 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetEngineType((yyvsp[(1) - (3)].String), (yyvsp[(3) - (3)].Number)); }
    break;

  case 163:
#line 306 "lscp.y"
    { (yyval.LoadMode) = MidiInstrumentMapper::ON_DEMAND;      }
    break;

  case 164:
#line 307 "lscp.y"
    { (yyval.LoadMode) = MidiInstrumentMapper::ON_DEMAND_HOLD; }
    break;

  case 165:
#line 308 "lscp.y"
    { (yyval.LoadMode) = MidiInstrumentMapper::PERSISTENT;     }
    break;

  case 171:
#line 324 "lscp.y"
    { (yyval.Number) = 16; }
    break;

  case 178:
#line 343 "lscp.y"
    { (yyval.Dotnum) = (yyvsp[(1) - (1)].Number); }
    break;

  case 188:
#line 371 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (3)].String) + "," + (yyvsp[(3) - (3)].String); }
    break;

  case 191:
#line 376 "lscp.y"
    { std::stringstream ss; ss << "\'" << (yyvsp[(1) - (1)].Number) << "\'"; (yyval.String) = ss.str(); }
    break;

  case 192:
#line 377 "lscp.y"
    { std::stringstream ss; ss << "\'" << (yyvsp[(1) - (1)].Dotnum) << "\'"; (yyval.String) = ss.str(); }
    break;

  case 193:
#line 385 "lscp.y"
    { (yyval.Dotnum) = (yyvsp[(1) - (1)].Number); }
    break;

  case 194:
#line 386 "lscp.y"
    { (yyval.Dotnum) = -1; }
    break;

  case 195:
#line 389 "lscp.y"
    { std::string s; s = (yyvsp[(1) - (1)].Char); (yyval.String) = s; }
    break;

  case 196:
#line 390 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + (yyvsp[(2) - (2)].Char);                  }
    break;

  case 197:
#line 393 "lscp.y"
    { (yyval.Dotnum) = atof(String((yyvsp[(1) - (3)].String) + "." + (yyvsp[(3) - (3)].String)).c_str());                         }
    break;

  case 198:
#line 394 "lscp.y"
    { String s = "+"; s += (yyvsp[(2) - (4)].String); s += "."; s += (yyvsp[(4) - (4)].String); (yyval.Dotnum) = atof(s.c_str()); }
    break;

  case 199:
#line 395 "lscp.y"
    { (yyval.Dotnum) = atof(String("-" + (yyvsp[(2) - (4)].String) + "." + (yyvsp[(4) - (4)].String)).c_str());                   }
    break;

  case 200:
#line 399 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (1)].Char);      }
    break;

  case 201:
#line 400 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + (yyvsp[(2) - (2)].Char); }
    break;

  case 202:
#line 403 "lscp.y"
    { (yyval.Char) = '0'; }
    break;

  case 203:
#line 404 "lscp.y"
    { (yyval.Char) = '1'; }
    break;

  case 204:
#line 405 "lscp.y"
    { (yyval.Char) = '2'; }
    break;

  case 205:
#line 406 "lscp.y"
    { (yyval.Char) = '3'; }
    break;

  case 206:
#line 407 "lscp.y"
    { (yyval.Char) = '4'; }
    break;

  case 207:
#line 408 "lscp.y"
    { (yyval.Char) = '5'; }
    break;

  case 208:
#line 409 "lscp.y"
    { (yyval.Char) = '6'; }
    break;

  case 209:
#line 410 "lscp.y"
    { (yyval.Char) = '7'; }
    break;

  case 210:
#line 411 "lscp.y"
    { (yyval.Char) = '8'; }
    break;

  case 211:
#line 412 "lscp.y"
    { (yyval.Char) = '9'; }
    break;

  case 212:
#line 415 "lscp.y"
    { (yyval.Number) = atoi(String(1, (yyvsp[(1) - (1)].Char)).c_str());      }
    break;

  case 213:
#line 416 "lscp.y"
    { (yyval.Number) = atoi(String(String("1") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 214:
#line 417 "lscp.y"
    { (yyval.Number) = atoi(String(String("2") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 215:
#line 418 "lscp.y"
    { (yyval.Number) = atoi(String(String("3") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 216:
#line 419 "lscp.y"
    { (yyval.Number) = atoi(String(String("4") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 217:
#line 420 "lscp.y"
    { (yyval.Number) = atoi(String(String("5") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 218:
#line 421 "lscp.y"
    { (yyval.Number) = atoi(String(String("6") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 219:
#line 422 "lscp.y"
    { (yyval.Number) = atoi(String(String("7") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 220:
#line 423 "lscp.y"
    { (yyval.Number) = atoi(String(String("8") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 221:
#line 424 "lscp.y"
    { (yyval.Number) = atoi(String(String("9") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 222:
#line 426 "lscp.y"
    { (yyval.Char) = 'A'; }
    break;

  case 223:
#line 426 "lscp.y"
    { (yyval.Char) = 'B'; }
    break;

  case 224:
#line 426 "lscp.y"
    { (yyval.Char) = 'C'; }
    break;

  case 225:
#line 426 "lscp.y"
    { (yyval.Char) = 'D'; }
    break;

  case 226:
#line 426 "lscp.y"
    { (yyval.Char) = 'E'; }
    break;

  case 227:
#line 426 "lscp.y"
    { (yyval.Char) = 'F'; }
    break;

  case 228:
#line 426 "lscp.y"
    { (yyval.Char) = 'G'; }
    break;

  case 229:
#line 426 "lscp.y"
    { (yyval.Char) = 'H'; }
    break;

  case 230:
#line 426 "lscp.y"
    { (yyval.Char) = 'I'; }
    break;

  case 231:
#line 426 "lscp.y"
    { (yyval.Char) = 'J'; }
    break;

  case 232:
#line 426 "lscp.y"
    { (yyval.Char) = 'K'; }
    break;

  case 233:
#line 426 "lscp.y"
    { (yyval.Char) = 'L'; }
    break;

  case 234:
#line 426 "lscp.y"
    { (yyval.Char) = 'M'; }
    break;

  case 235:
#line 426 "lscp.y"
    { (yyval.Char) = 'N'; }
    break;

  case 236:
#line 426 "lscp.y"
    { (yyval.Char) = 'O'; }
    break;

  case 237:
#line 426 "lscp.y"
    { (yyval.Char) = 'P'; }
    break;

  case 238:
#line 426 "lscp.y"
    { (yyval.Char) = 'Q'; }
    break;

  case 239:
#line 426 "lscp.y"
    { (yyval.Char) = 'R'; }
    break;

  case 240:
#line 426 "lscp.y"
    { (yyval.Char) = 'S'; }
    break;

  case 241:
#line 426 "lscp.y"
    { (yyval.Char) = 'T'; }
    break;

  case 242:
#line 426 "lscp.y"
    { (yyval.Char) = 'U'; }
    break;

  case 243:
#line 426 "lscp.y"
    { (yyval.Char) = 'V'; }
    break;

  case 244:
#line 426 "lscp.y"
    { (yyval.Char) = 'W'; }
    break;

  case 245:
#line 426 "lscp.y"
    { (yyval.Char) = 'X'; }
    break;

  case 246:
#line 426 "lscp.y"
    { (yyval.Char) = 'Y'; }
    break;

  case 247:
#line 426 "lscp.y"
    { (yyval.Char) = 'Z'; }
    break;

  case 248:
#line 427 "lscp.y"
    { (yyval.Char) = 'a'; }
    break;

  case 249:
#line 427 "lscp.y"
    { (yyval.Char) = 'b'; }
    break;

  case 250:
#line 427 "lscp.y"
    { (yyval.Char) = 'c'; }
    break;

  case 251:
#line 427 "lscp.y"
    { (yyval.Char) = 'd'; }
    break;

  case 252:
#line 427 "lscp.y"
    { (yyval.Char) = 'e'; }
    break;

  case 253:
#line 427 "lscp.y"
    { (yyval.Char) = 'f'; }
    break;

  case 254:
#line 427 "lscp.y"
    { (yyval.Char) = 'g'; }
    break;

  case 255:
#line 427 "lscp.y"
    { (yyval.Char) = 'h'; }
    break;

  case 256:
#line 427 "lscp.y"
    { (yyval.Char) = 'i'; }
    break;

  case 257:
#line 427 "lscp.y"
    { (yyval.Char) = 'j'; }
    break;

  case 258:
#line 427 "lscp.y"
    { (yyval.Char) = 'k'; }
    break;

  case 259:
#line 427 "lscp.y"
    { (yyval.Char) = 'l'; }
    break;

  case 260:
#line 427 "lscp.y"
    { (yyval.Char) = 'm'; }
    break;

  case 261:
#line 427 "lscp.y"
    { (yyval.Char) = 'n'; }
    break;

  case 262:
#line 427 "lscp.y"
    { (yyval.Char) = 'o'; }
    break;

  case 263:
#line 427 "lscp.y"
    { (yyval.Char) = 'p'; }
    break;

  case 264:
#line 427 "lscp.y"
    { (yyval.Char) = 'q'; }
    break;

  case 265:
#line 427 "lscp.y"
    { (yyval.Char) = 'r'; }
    break;

  case 266:
#line 427 "lscp.y"
    { (yyval.Char) = 's'; }
    break;

  case 267:
#line 427 "lscp.y"
    { (yyval.Char) = 't'; }
    break;

  case 268:
#line 427 "lscp.y"
    { (yyval.Char) = 'u'; }
    break;

  case 269:
#line 427 "lscp.y"
    { (yyval.Char) = 'v'; }
    break;

  case 270:
#line 427 "lscp.y"
    { (yyval.Char) = 'w'; }
    break;

  case 271:
#line 427 "lscp.y"
    { (yyval.Char) = 'x'; }
    break;

  case 272:
#line 427 "lscp.y"
    { (yyval.Char) = 'y'; }
    break;

  case 273:
#line 427 "lscp.y"
    { (yyval.Char) = 'z'; }
    break;

  case 274:
#line 428 "lscp.y"
    { (yyval.Char) = '0'; }
    break;

  case 275:
#line 428 "lscp.y"
    { (yyval.Char) = '1'; }
    break;

  case 276:
#line 428 "lscp.y"
    { (yyval.Char) = '2'; }
    break;

  case 277:
#line 428 "lscp.y"
    { (yyval.Char) = '3'; }
    break;

  case 278:
#line 428 "lscp.y"
    { (yyval.Char) = '4'; }
    break;

  case 279:
#line 428 "lscp.y"
    { (yyval.Char) = '5'; }
    break;

  case 280:
#line 428 "lscp.y"
    { (yyval.Char) = '6'; }
    break;

  case 281:
#line 428 "lscp.y"
    { (yyval.Char) = '7'; }
    break;

  case 282:
#line 428 "lscp.y"
    { (yyval.Char) = '8'; }
    break;

  case 283:
#line 428 "lscp.y"
    { (yyval.Char) = '9'; }
    break;

  case 284:
#line 429 "lscp.y"
    { (yyval.Char) = '!'; }
    break;

  case 285:
#line 429 "lscp.y"
    { (yyval.Char) = '#'; }
    break;

  case 286:
#line 429 "lscp.y"
    { (yyval.Char) = '$'; }
    break;

  case 287:
#line 429 "lscp.y"
    { (yyval.Char) = '%'; }
    break;

  case 288:
#line 429 "lscp.y"
    { (yyval.Char) = '&'; }
    break;

  case 289:
#line 429 "lscp.y"
    { (yyval.Char) = '('; }
    break;

  case 290:
#line 429 "lscp.y"
    { (yyval.Char) = ')'; }
    break;

  case 291:
#line 429 "lscp.y"
    { (yyval.Char) = '*'; }
    break;

  case 292:
#line 429 "lscp.y"
    { (yyval.Char) = '+'; }
    break;

  case 293:
#line 429 "lscp.y"
    { (yyval.Char) = '-'; }
    break;

  case 294:
#line 429 "lscp.y"
    { (yyval.Char) = '.'; }
    break;

  case 295:
#line 429 "lscp.y"
    { (yyval.Char) = ','; }
    break;

  case 296:
#line 429 "lscp.y"
    { (yyval.Char) = '/'; }
    break;

  case 297:
#line 430 "lscp.y"
    { (yyval.Char) = ':'; }
    break;

  case 298:
#line 430 "lscp.y"
    { (yyval.Char) = ';'; }
    break;

  case 299:
#line 430 "lscp.y"
    { (yyval.Char) = '<'; }
    break;

  case 300:
#line 430 "lscp.y"
    { (yyval.Char) = '='; }
    break;

  case 301:
#line 430 "lscp.y"
    { (yyval.Char) = '>'; }
    break;

  case 302:
#line 430 "lscp.y"
    { (yyval.Char) = '?'; }
    break;

  case 303:
#line 430 "lscp.y"
    { (yyval.Char) = '@'; }
    break;

  case 304:
#line 431 "lscp.y"
    { (yyval.Char) = '['; }
    break;

  case 305:
#line 431 "lscp.y"
    { (yyval.Char) = '\\'; }
    break;

  case 306:
#line 431 "lscp.y"
    { (yyval.Char) = ']'; }
    break;

  case 307:
#line 431 "lscp.y"
    { (yyval.Char) = '^'; }
    break;

  case 308:
#line 431 "lscp.y"
    { (yyval.Char) = '_'; }
    break;

  case 309:
#line 432 "lscp.y"
    { (yyval.Char) = '{'; }
    break;

  case 310:
#line 432 "lscp.y"
    { (yyval.Char) = '|'; }
    break;

  case 311:
#line 432 "lscp.y"
    { (yyval.Char) = '}'; }
    break;

  case 312:
#line 432 "lscp.y"
    { (yyval.Char) = '~'; }
    break;

  case 313:
#line 433 "lscp.y"
    { (yyval.Char) = '\200'; }
    break;

  case 314:
#line 433 "lscp.y"
    { (yyval.Char) = '\201'; }
    break;

  case 315:
#line 433 "lscp.y"
    { (yyval.Char) = '\202'; }
    break;

  case 316:
#line 434 "lscp.y"
    { (yyval.Char) = '\203'; }
    break;

  case 317:
#line 434 "lscp.y"
    { (yyval.Char) = '\204'; }
    break;

  case 318:
#line 434 "lscp.y"
    { (yyval.Char) = '\205'; }
    break;

  case 319:
#line 435 "lscp.y"
    { (yyval.Char) = '\206'; }
    break;

  case 320:
#line 435 "lscp.y"
    { (yyval.Char) = '\207'; }
    break;

  case 321:
#line 435 "lscp.y"
    { (yyval.Char) = '\210'; }
    break;

  case 322:
#line 436 "lscp.y"
    { (yyval.Char) = '\211'; }
    break;

  case 323:
#line 436 "lscp.y"
    { (yyval.Char) = '\212'; }
    break;

  case 324:
#line 436 "lscp.y"
    { (yyval.Char) = '\213'; }
    break;

  case 325:
#line 437 "lscp.y"
    { (yyval.Char) = '\214'; }
    break;

  case 326:
#line 437 "lscp.y"
    { (yyval.Char) = '\215'; }
    break;

  case 327:
#line 437 "lscp.y"
    { (yyval.Char) = '\216'; }
    break;

  case 328:
#line 438 "lscp.y"
    { (yyval.Char) = '\217'; }
    break;

  case 329:
#line 438 "lscp.y"
    { (yyval.Char) = '\220'; }
    break;

  case 330:
#line 438 "lscp.y"
    { (yyval.Char) = '\221'; }
    break;

  case 331:
#line 439 "lscp.y"
    { (yyval.Char) = '\222'; }
    break;

  case 332:
#line 439 "lscp.y"
    { (yyval.Char) = '\223'; }
    break;

  case 333:
#line 439 "lscp.y"
    { (yyval.Char) = '\224'; }
    break;

  case 334:
#line 440 "lscp.y"
    { (yyval.Char) = '\225'; }
    break;

  case 335:
#line 440 "lscp.y"
    { (yyval.Char) = '\226'; }
    break;

  case 336:
#line 440 "lscp.y"
    { (yyval.Char) = '\227'; }
    break;

  case 337:
#line 441 "lscp.y"
    { (yyval.Char) = '\230'; }
    break;

  case 338:
#line 441 "lscp.y"
    { (yyval.Char) = '\231'; }
    break;

  case 339:
#line 441 "lscp.y"
    { (yyval.Char) = '\232'; }
    break;

  case 340:
#line 442 "lscp.y"
    { (yyval.Char) = '\233'; }
    break;

  case 341:
#line 442 "lscp.y"
    { (yyval.Char) = '\234'; }
    break;

  case 342:
#line 442 "lscp.y"
    { (yyval.Char) = '\235'; }
    break;

  case 343:
#line 443 "lscp.y"
    { (yyval.Char) = '\236'; }
    break;

  case 344:
#line 443 "lscp.y"
    { (yyval.Char) = '\237'; }
    break;

  case 345:
#line 443 "lscp.y"
    { (yyval.Char) = '\240'; }
    break;

  case 346:
#line 444 "lscp.y"
    { (yyval.Char) = '\241'; }
    break;

  case 347:
#line 444 "lscp.y"
    { (yyval.Char) = '\242'; }
    break;

  case 348:
#line 444 "lscp.y"
    { (yyval.Char) = '\243'; }
    break;

  case 349:
#line 445 "lscp.y"
    { (yyval.Char) = '\244'; }
    break;

  case 350:
#line 445 "lscp.y"
    { (yyval.Char) = '\245'; }
    break;

  case 351:
#line 445 "lscp.y"
    { (yyval.Char) = '\246'; }
    break;

  case 352:
#line 446 "lscp.y"
    { (yyval.Char) = '\247'; }
    break;

  case 353:
#line 446 "lscp.y"
    { (yyval.Char) = '\250'; }
    break;

  case 354:
#line 446 "lscp.y"
    { (yyval.Char) = '\251'; }
    break;

  case 355:
#line 447 "lscp.y"
    { (yyval.Char) = '\252'; }
    break;

  case 356:
#line 447 "lscp.y"
    { (yyval.Char) = '\253'; }
    break;

  case 357:
#line 447 "lscp.y"
    { (yyval.Char) = '\254'; }
    break;

  case 358:
#line 448 "lscp.y"
    { (yyval.Char) = '\255'; }
    break;

  case 359:
#line 448 "lscp.y"
    { (yyval.Char) = '\256'; }
    break;

  case 360:
#line 448 "lscp.y"
    { (yyval.Char) = '\257'; }
    break;

  case 361:
#line 449 "lscp.y"
    { (yyval.Char) = '\260'; }
    break;

  case 362:
#line 449 "lscp.y"
    { (yyval.Char) = '\261'; }
    break;

  case 363:
#line 449 "lscp.y"
    { (yyval.Char) = '\262'; }
    break;

  case 364:
#line 450 "lscp.y"
    { (yyval.Char) = '\263'; }
    break;

  case 365:
#line 450 "lscp.y"
    { (yyval.Char) = '\264'; }
    break;

  case 366:
#line 450 "lscp.y"
    { (yyval.Char) = '\265'; }
    break;

  case 367:
#line 451 "lscp.y"
    { (yyval.Char) = '\266'; }
    break;

  case 368:
#line 451 "lscp.y"
    { (yyval.Char) = '\267'; }
    break;

  case 369:
#line 451 "lscp.y"
    { (yyval.Char) = '\270'; }
    break;

  case 370:
#line 452 "lscp.y"
    { (yyval.Char) = '\271'; }
    break;

  case 371:
#line 452 "lscp.y"
    { (yyval.Char) = '\272'; }
    break;

  case 372:
#line 452 "lscp.y"
    { (yyval.Char) = '\273'; }
    break;

  case 373:
#line 453 "lscp.y"
    { (yyval.Char) = '\274'; }
    break;

  case 374:
#line 453 "lscp.y"
    { (yyval.Char) = '\275'; }
    break;

  case 375:
#line 453 "lscp.y"
    { (yyval.Char) = '\276'; }
    break;

  case 376:
#line 454 "lscp.y"
    { (yyval.Char) = '\277'; }
    break;

  case 377:
#line 454 "lscp.y"
    { (yyval.Char) = '\300'; }
    break;

  case 378:
#line 454 "lscp.y"
    { (yyval.Char) = '\301'; }
    break;

  case 379:
#line 455 "lscp.y"
    { (yyval.Char) = '\302'; }
    break;

  case 380:
#line 455 "lscp.y"
    { (yyval.Char) = '\303'; }
    break;

  case 381:
#line 455 "lscp.y"
    { (yyval.Char) = '\304'; }
    break;

  case 382:
#line 456 "lscp.y"
    { (yyval.Char) = '\305'; }
    break;

  case 383:
#line 456 "lscp.y"
    { (yyval.Char) = '\306'; }
    break;

  case 384:
#line 456 "lscp.y"
    { (yyval.Char) = '\307'; }
    break;

  case 385:
#line 457 "lscp.y"
    { (yyval.Char) = '\310'; }
    break;

  case 386:
#line 457 "lscp.y"
    { (yyval.Char) = '\311'; }
    break;

  case 387:
#line 457 "lscp.y"
    { (yyval.Char) = '\312'; }
    break;

  case 388:
#line 458 "lscp.y"
    { (yyval.Char) = '\313'; }
    break;

  case 389:
#line 458 "lscp.y"
    { (yyval.Char) = '\314'; }
    break;

  case 390:
#line 458 "lscp.y"
    { (yyval.Char) = '\315'; }
    break;

  case 391:
#line 459 "lscp.y"
    { (yyval.Char) = '\316'; }
    break;

  case 392:
#line 459 "lscp.y"
    { (yyval.Char) = '\317'; }
    break;

  case 393:
#line 459 "lscp.y"
    { (yyval.Char) = '\320'; }
    break;

  case 394:
#line 460 "lscp.y"
    { (yyval.Char) = '\321'; }
    break;

  case 395:
#line 460 "lscp.y"
    { (yyval.Char) = '\322'; }
    break;

  case 396:
#line 460 "lscp.y"
    { (yyval.Char) = '\323'; }
    break;

  case 397:
#line 461 "lscp.y"
    { (yyval.Char) = '\324'; }
    break;

  case 398:
#line 461 "lscp.y"
    { (yyval.Char) = '\325'; }
    break;

  case 399:
#line 461 "lscp.y"
    { (yyval.Char) = '\326'; }
    break;

  case 400:
#line 462 "lscp.y"
    { (yyval.Char) = '\327'; }
    break;

  case 401:
#line 462 "lscp.y"
    { (yyval.Char) = '\330'; }
    break;

  case 402:
#line 462 "lscp.y"
    { (yyval.Char) = '\331'; }
    break;

  case 403:
#line 463 "lscp.y"
    { (yyval.Char) = '\332'; }
    break;

  case 404:
#line 463 "lscp.y"
    { (yyval.Char) = '\333'; }
    break;

  case 405:
#line 463 "lscp.y"
    { (yyval.Char) = '\334'; }
    break;

  case 406:
#line 464 "lscp.y"
    { (yyval.Char) = '\335'; }
    break;

  case 407:
#line 464 "lscp.y"
    { (yyval.Char) = '\336'; }
    break;

  case 408:
#line 464 "lscp.y"
    { (yyval.Char) = '\337'; }
    break;

  case 409:
#line 465 "lscp.y"
    { (yyval.Char) = '\340'; }
    break;

  case 410:
#line 465 "lscp.y"
    { (yyval.Char) = '\341'; }
    break;

  case 411:
#line 465 "lscp.y"
    { (yyval.Char) = '\342'; }
    break;

  case 412:
#line 466 "lscp.y"
    { (yyval.Char) = '\343'; }
    break;

  case 413:
#line 466 "lscp.y"
    { (yyval.Char) = '\344'; }
    break;

  case 414:
#line 466 "lscp.y"
    { (yyval.Char) = '\345'; }
    break;

  case 415:
#line 467 "lscp.y"
    { (yyval.Char) = '\346'; }
    break;

  case 416:
#line 467 "lscp.y"
    { (yyval.Char) = '\347'; }
    break;

  case 417:
#line 467 "lscp.y"
    { (yyval.Char) = '\350'; }
    break;

  case 418:
#line 468 "lscp.y"
    { (yyval.Char) = '\351'; }
    break;

  case 419:
#line 468 "lscp.y"
    { (yyval.Char) = '\352'; }
    break;

  case 420:
#line 468 "lscp.y"
    { (yyval.Char) = '\353'; }
    break;

  case 421:
#line 469 "lscp.y"
    { (yyval.Char) = '\354'; }
    break;

  case 422:
#line 469 "lscp.y"
    { (yyval.Char) = '\355'; }
    break;

  case 423:
#line 469 "lscp.y"
    { (yyval.Char) = '\356'; }
    break;

  case 424:
#line 470 "lscp.y"
    { (yyval.Char) = '\357'; }
    break;

  case 425:
#line 470 "lscp.y"
    { (yyval.Char) = '\360'; }
    break;

  case 426:
#line 470 "lscp.y"
    { (yyval.Char) = '\361'; }
    break;

  case 427:
#line 471 "lscp.y"
    { (yyval.Char) = '\362'; }
    break;

  case 428:
#line 471 "lscp.y"
    { (yyval.Char) = '\363'; }
    break;

  case 429:
#line 471 "lscp.y"
    { (yyval.Char) = '\364'; }
    break;

  case 430:
#line 472 "lscp.y"
    { (yyval.Char) = '\365'; }
    break;

  case 431:
#line 472 "lscp.y"
    { (yyval.Char) = '\366'; }
    break;

  case 432:
#line 472 "lscp.y"
    { (yyval.Char) = '\367'; }
    break;

  case 433:
#line 473 "lscp.y"
    { (yyval.Char) = '\370'; }
    break;

  case 434:
#line 473 "lscp.y"
    { (yyval.Char) = '\371'; }
    break;

  case 435:
#line 473 "lscp.y"
    { (yyval.Char) = '\372'; }
    break;

  case 436:
#line 474 "lscp.y"
    { (yyval.Char) = '\373'; }
    break;

  case 437:
#line 474 "lscp.y"
    { (yyval.Char) = '\374'; }
    break;

  case 438:
#line 474 "lscp.y"
    { (yyval.Char) = '\375'; }
    break;

  case 439:
#line 475 "lscp.y"
    { (yyval.Char) = '\376'; }
    break;

  case 440:
#line 475 "lscp.y"
    { (yyval.Char) = '\377'; }
    break;

  case 441:
#line 478 "lscp.y"
    { (yyval.String) = " ";      }
    break;

  case 443:
#line 480 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + " "; }
    break;

  case 444:
#line 481 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + (yyvsp[(2) - (2)].String);  }
    break;

  case 445:
#line 484 "lscp.y"
    { (yyval.String) = (yyvsp[(2) - (3)].String); }
    break;

  case 446:
#line 485 "lscp.y"
    { (yyval.String) = (yyvsp[(2) - (3)].String); }
    break;


/* Line 1267 of yacc.c.  */
#line 5367 "y.tab.c"
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


#line 743 "lscp.y"


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

