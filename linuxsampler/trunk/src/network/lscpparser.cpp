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
#define YYLAST   4536

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  227
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  143
/* YYNRULES -- Number of rules.  */
#define YYNRULES  540
/* YYNRULES -- Number of states.  */
#define YYNSTATES  1712

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
     457,   459,   467,   477,   485,   495,   499,   507,   517,   529,
     539,   549,   553,   557,   563,   567,   573,   577,   583,   591,
     595,   599,   603,   607,   611,   617,   621,   625,   631,   639,
     645,   655,   661,   667,   673,   679,   685,   691,   697,   703,
     709,   715,   716,   719,   723,   729,   731,   733,   735,   737,
     739,   741,   743,   745,   749,   753,   755,   759,   765,   773,
     777,   779,   781,   783,   785,   787,   789,   791,   793,   795,
     797,   799,   801,   803,   805,   807,   809,   811,   813,   815,
     817,   819,   821,   823,   825,   827,   831,   833,   835,   837,
     839,   841,   843,   845,   848,   852,   857,   862,   864,   867,
     869,   871,   873,   875,   877,   879,   881,   883,   885,   887,
     889,   892,   895,   898,   901,   904,   907,   910,   913,   916,
     918,   920,   922,   924,   926,   928,   930,   932,   934,   936,
     938,   940,   942,   944,   946,   948,   950,   952,   954,   956,
     958,   960,   962,   964,   966,   968,   970,   972,   974,   976,
     978,   980,   982,   984,   986,   988,   990,   992,   994,   996,
     998,  1000,  1002,  1004,  1006,  1008,  1010,  1012,  1014,  1016,
    1018,  1020,  1022,  1024,  1026,  1028,  1030,  1032,  1034,  1036,
    1038,  1040,  1042,  1044,  1046,  1048,  1050,  1052,  1054,  1056,
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
    1358,  1361,  1364,  1368,  1372,  1374,  1376,  1378,  1382,  1386,
    1390,  1396,  1402,  1409,  1417,  1422,  1427,  1431,  1436,  1444,
    1454,  1461,  1465,  1475,  1487,  1494,  1502,  1520,  1551,  1560,
    1565,  1591,  1616,  1640,  1663,  1689,  1714,  1736,  1757,  1771,
    1784,  1798,  1811,  1823,  1836,  1848,  1866,  1888,  1900,  1911,
    1918,  1928,  1943,  1954,  1984,  2005,  2025,  2055,  2075,  2106,
    2127,  2145,  2174,  2202,  2228,  2247,  2265,  2293,  2309,  2326,
    2346,  2367,  2385,  2401,  2420,  2436,  2447,  2463,  2471,  2480,
    2487,  2494,  2500,  2505,  2510,  2516,  2527,  2533,  2547,  2552,
    2557
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
     283,   367,   283,   259,   283,   269,    -1,   356,   283,   367,
     283,   264,   283,   266,   283,   271,    -1,   356,   283,   338,
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
     237,   238,   239,   242,   243,   244,   245,   246,   247,   250,
     253,   254,   257,   258,   259,   262,   263,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   282,   283,   286,   287,   290,   291,   294,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   306,   307,   310,
     313,   314,   315,   318,   321,   324,   327,   330,   331,   334,
     337,   340,   343,   346,   349,   350,   353,   356,   359,   362,
     365,   368,   371,   374,   377,   378,   381,   382,   383,   384,
     392,   393,   396,   397,   400,   401,   402,   406,   407,   410,
     411,   412,   413,   414,   415,   416,   417,   418,   419,   422,
     423,   424,   425,   426,   427,   428,   429,   430,   431,   433,
     433,   433,   433,   433,   433,   433,   433,   433,   433,   433,
     433,   433,   433,   433,   433,   433,   433,   433,   433,   433,
     433,   433,   433,   433,   433,   434,   434,   434,   434,   434,
     434,   434,   434,   434,   434,   434,   434,   434,   434,   434,
     434,   434,   434,   434,   434,   434,   434,   434,   434,   434,
     434,   435,   435,   435,   435,   435,   435,   435,   435,   435,
     435,   436,   436,   436,   436,   436,   436,   436,   436,   436,
     436,   436,   436,   436,   437,   437,   437,   437,   437,   437,
     437,   438,   438,   438,   438,   438,   439,   439,   439,   439,
     440,   440,   440,   441,   441,   441,   442,   442,   442,   443,
     443,   443,   444,   444,   444,   445,   445,   445,   446,   446,
     446,   447,   447,   447,   448,   448,   448,   449,   449,   449,
     450,   450,   450,   451,   451,   451,   452,   452,   452,   453,
     453,   453,   454,   454,   454,   455,   455,   455,   456,   456,
     456,   457,   457,   457,   458,   458,   458,   459,   459,   459,
     460,   460,   460,   461,   461,   461,   462,   462,   462,   463,
     463,   463,   464,   464,   464,   465,   465,   465,   466,   466,
     466,   467,   467,   467,   468,   468,   468,   469,   469,   469,
     470,   470,   470,   471,   471,   471,   472,   472,   472,   473,
     473,   473,   474,   474,   474,   475,   475,   475,   476,   476,
     476,   477,   477,   477,   478,   478,   478,   479,   479,   479,
     480,   480,   480,   481,   481,   481,   482,   482,   485,   486,
     487,   488,   491,   492,   498,   501,   504,   507,   510,   513,
     516,   519,   522,   525,   528,   531,   534,   537,   540,   543,
     546,   549,   552,   555,   558,   561,   564,   567,   570,   573,
     576,   579,   582,   585,   588,   591,   594,   597,   600,   603,
     606,   609,   612,   615,   618,   621,   624,   627,   630,   633,
     636,   639,   642,   645,   648,   651,   654,   657,   660,   663,
     666,   669,   672,   675,   678,   681,   684,   687,   690,   693,
     696,   699,   702,   705,   708,   711,   714,   717,   720,   723,
     726,   729,   732,   735,   738,   741,   744,   747,   750,   753,
     756
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
     239,   239,   239,   240,   240,   240,   240,   240,   240,   241,
     242,   242,   243,   243,   243,   244,   244,   245,   245,   245,
     245,   245,   245,   245,   245,   245,   245,   245,   245,   245,
     245,   246,   246,   247,   247,   248,   248,   249,   249,   249,
     249,   249,   249,   249,   249,   249,   249,   250,   250,   251,
     252,   252,   252,   253,   254,   255,   256,   257,   257,   258,
     259,   260,   261,   262,   263,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   272,   273,   273,   273,   273,
     274,   274,   275,   275,   276,   276,   276,   277,   277,   278,
     278,   278,   278,   278,   278,   278,   278,   278,   278,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   280,
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
     280,   280,   280,   280,   280,   280,   280,   280,   281,   281,
     281,   281,   282,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,   354,   355,   356,   357,   358,
     359,   360,   361,   362,   363,   364,   365,   366,   367,   368,
     369
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
       1,     7,     9,     7,     9,     3,     7,     9,    11,     9,
       9,     3,     3,     5,     3,     5,     3,     5,     7,     3,
       3,     3,     3,     3,     5,     3,     3,     5,     7,     5,
       9,     5,     5,     5,     5,     5,     5,     5,     5,     5,
       5,     0,     2,     3,     5,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     1,     3,     5,     7,     3,
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
       5,     5,     6,     7,     4,     4,     3,     4,     7,     9,
       6,     3,     9,    11,     6,     7,    17,    30,     8,     4,
      25,    24,    23,    22,    25,    24,    21,    20,    13,    12,
      13,    12,    11,    12,    11,    17,    21,    11,    10,     6,
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
       0,     0,     0,     0,     0,     0,     1,   455,   456,     2,
       0,     9,   307,   302,   301,   299,   300,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   291,
     293,   294,   295,   296,   297,   298,   303,   304,   305,   306,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   352,   353,   354,   355,   356,   357,
     358,   359,   360,   361,   362,   363,   364,   365,   366,   367,
     368,   369,   370,   371,   372,   373,   374,   375,   376,   377,
     378,   379,   380,   381,   382,   383,   384,   385,   386,   387,
     388,   389,   390,   391,   392,   393,   394,   395,   396,   397,
     398,   399,   400,   401,   402,   403,   404,   405,   406,   407,
     408,   409,   410,   411,   412,   413,   414,   415,   416,   417,
     418,   419,   420,   421,   422,   423,   424,   425,   426,   427,
     428,   429,   430,   431,   432,   433,   434,   435,   436,   437,
     438,   439,   440,   441,   442,   443,   444,   445,   446,   447,
     454,    12,   219,    11,   202,    10,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   457,     0,     0,     0,   458,     0,     0,   459,     0,
       0,     0,     0,   471,     0,     0,     0,     3,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   220,   207,
     221,   222,   223,   224,   225,   226,   227,   228,   292,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   203,
       0,     0,    13,    30,    31,     0,     0,     0,     0,     0,
       0,     0,     0,    16,     0,    77,    82,    94,   101,   102,
       0,    86,     0,     0,     0,     0,     0,    78,     0,    87,
       0,     0,     0,     0,     0,   106,     0,     0,     0,     0,
       0,   110,     0,    14,     0,    15,     0,     0,    27,     0,
       0,     0,     0,    17,     0,     0,     0,    18,     0,     0,
       0,     0,     0,     0,     0,    19,   160,   162,   159,   157,
     161,   158,     0,   165,     0,     0,    20,     0,     0,    21,
       0,     0,     0,     0,     0,    22,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    23,    33,    34,    35,    36,    44,
      45,    46,    47,    37,    41,    42,    43,    40,    39,    38,
      49,    50,    48,    24,    51,    52,    53,    54,    62,    63,
      64,    65,    55,    59,    60,    61,    58,    57,    56,    67,
      68,    66,   449,    25,   448,    26,     0,     0,     0,     0,
     464,   465,   540,     0,     0,     0,     0,     0,     0,   208,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   151,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   451,   450,     0,   461,
       0,     0,     0,   536,     0,     0,   460,     0,     0,     0,
       0,     0,    32,   191,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   210,   211,
     212,   213,   214,   215,   216,   217,   218,     0,   103,   180,
     104,     0,     0,     0,     0,   108,   186,   100,     0,     0,
       0,     0,     0,     0,   130,   131,     0,     0,     0,   124,
     126,     0,   132,   133,     0,     0,     0,     0,     0,   163,
     164,   166,     0,   135,     0,   190,     0,   136,     0,   189,
      74,    75,    76,     0,     0,     0,     0,     0,     0,   115,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   122,   184,     0,
     207,   185,   121,   201,   200,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   129,   462,     0,   470,   474,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   152,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   539,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   463,     0,     0,     0,     0,   452,   453,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    95,     0,
       0,     0,   155,   156,    97,    98,    99,    88,     0,    83,
       0,     0,     0,    89,     0,     0,   466,   107,    79,     0,
       0,     0,     0,     0,     0,   181,     0,     0,     0,     0,
     123,     0,   125,   127,   183,   134,   188,     0,     0,     0,
       0,     0,     0,   187,     0,   169,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   204,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   499,     0,     0,
     529,     0,   530,   479,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   532,   533,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   538,     0,     0,     0,     0,
       0,     0,     0,     0,   205,   206,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   472,     0,   475,     0,
       0,     0,   475,   527,     0,     0,     0,     0,    96,    84,
       0,    92,     0,    80,     0,    90,   109,     0,     0,     0,
      73,   182,     0,     0,   527,     0,     0,   299,   300,   153,
     194,   196,   199,   198,   197,   128,   193,     0,     0,     0,
       0,     0,   167,     0,     0,     0,     0,     0,   137,   173,
       0,   174,   139,   175,   141,     0,     0,   148,   149,   150,
     142,   176,   143,   177,   178,   144,   179,     0,   145,   146,
     147,   111,     0,   113,     0,   116,     0,   531,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   478,   528,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   473,
       0,     0,     0,     0,     0,     0,   534,     0,    85,    93,
      91,    81,   105,     0,     0,     0,     0,     0,     0,   154,
     195,     0,     0,     0,     0,   168,     0,     0,     0,     0,
     138,     0,     0,     0,   112,   114,     0,     0,     0,   119,
     120,   117,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   498,     0,     0,     0,     0,     0,   467,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   469,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   140,     0,
       0,   118,     0,   492,     0,     0,     0,     0,   497,     0,
       0,     0,     0,     0,   494,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   525,     0,     0,
       0,     0,     0,   489,     0,   491,     0,     0,     0,   493,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   468,     0,     0,     0,   488,
     490,     0,     0,   537,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   535,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   522,   517,
       0,   517,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   518,     0,     0,    69,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     476,     0,   515,   521,     0,     0,   495,     0,     0,   515,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   522,
     524,   526,     0,     0,     0,     0,     0,   495,     0,     0,
       0,     0,     0,     0,   514,     0,     0,     0,     0,     0,
       0,    70,    71,   192,   170,   171,   172,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   519,     0,   505,   507,     0,     0,     0,     0,   519,
       0,     0,     0,     0,   505,     0,     0,     0,     0,     0,
       0,   510,     0,     0,     0,     0,     0,     0,     0,   509,
     504,     0,     0,     0,     0,     0,   520,     0,     0,     0,
      72,     0,     0,     0,     0,   523,     0,     0,     0,     0,
     487,     0,     0,     0,     0,     0,     0,     0,   496,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   486,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   509,     0,     0,     0,   483,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     482,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   481,     0,   485,     0,     0,     0,
       0,     0,   513,     0,     0,     0,     0,   480,   484,     0,
       0,     0,     0,     0,   500,     0,     0,     0,     0,     0,
       0,     0,   516,     0,   502,     0,   512,     0,     0,     0,
     511,     0,     0,     0,   506,     0,     0,   503,   508,   477,
       0,   501
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    13,    14,    15,    16,   342,   444,   463,   383,   385,
     419,   353,   425,   393,   485,   388,   397,   416,   679,   640,
     880,   851,   405,   663,   667,  1531,  1078,  1080,  1082,  1090,
    1092,  1095,   628,   874,  1050,   883,   707,   635,   892,   885,
     668,   664,   592,  1532,  1065,  1059,  1060,   712,  1061,  1062,
     709,   272,   636,   274,   483,  1064,   973,    49,    50,    17,
      18,    19,    20,    21,    22,    23,    24,    25,  1094,  1088,
    1089,   641,    26,    27,    28,    29,    30,   343,   355,   356,
     357,   604,   445,   446,   447,   448,   449,   450,   451,   452,
     453,   454,   455,   456,   457,   458,   459,   358,   359,   461,
     417,   360,  1534,  1535,  1536,   427,   361,   362,   363,   364,
     365,   366,   682,   367,   429,   368,   369,   370,   371,   372,
     373,   344,   375,   376,   377,   686,   687,   688,   702,   378,
     379,   380,   381,   703,   690,   691,   852,   853,    31,   462,
     697,   434,    32
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -1105
static const yytype_int16 yypact[] =
{
      45, -1105, -1105,   104,   156,    36,   179,   100,   197,   181,
     214,    48,   223,   257,    10,  2117, -1105,    44,    44,    44,
      44,    44,    44,    44,    44,    44,    44,    44,    44,    44,
      44,    44, -1105,   242,   249,   255,   262,   263,   269,   261,
     252,   288,   128,    27,   314,   162, -1105, -1105, -1105, -1105,
     113, -1105, -1105, -1105, -1105, -1105, -1105, -1105,   594,   594,
     594,   594,   594,   594,   594,   594,   594, -1105, -1105, -1105,
   -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105,
   -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105,
   -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105,
   -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105,
   -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105,
   -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105,
   -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105,
   -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105,
   -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105,
   -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105,
   -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105,
   -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105,
   -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105,
   -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105,
   -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105,
   -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105,
   -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105,
   -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105,
   -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105,
   -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105,
   -1105,  2782, -1105, -1105, -1105, -1105,    69,   166,   311,   311,
     315,   188,   188,   137,    70,    69,   177,   129,   129,  2339,
     331, -1105,   335,   341,   330, -1105,   332,   350, -1105,   337,
     340,   353,   354, -1105,   345,   359,   348, -1105, -1105, -1105,
   -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105,   594, -1105,
     594,   594,   594,   594,   594,   594,   594,   594, -1105, -1105,
   -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105,
     362,   363, -1105, -1105,    44,   243,   365,   360,   351,   367,
     372,   368,   374, -1105,    44, -1105, -1105, -1105, -1105, -1105,
      44, -1105,    44,    44,    44,    44,    44, -1105,    44, -1105,
      44,    44,    44,    44,    44, -1105,    44,    44,    44,    44,
      44, -1105,   369, -1105,    44, -1105,    44,   371, -1105,    44,
     361,   366,   382, -1105,    44,    44,    44, -1105,    44,    44,
      44,   245,   384,   379,   395, -1105, -1105, -1105, -1105, -1105,
   -1105, -1105,    44, -1105,    44,   401, -1105,    44,    44, -1105,
      44,    44,   396,   423,   418, -1105,    44,    44,    44,    44,
      44,    44,    44,    44,    44,   407,   408,   422,   409,   419,
     426,   417,   424,   425, -1105, -1105, -1105, -1105, -1105, -1105,
   -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105,
   -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105,
   -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105,
   -1105, -1105,  2782,  2339, -1105, -1105,    44,   420,   421,   428,
   -1105, -1105, -1105,   427,   431,   439,   440,   432,   442, -1105,
     446,   448,    82,   450,   454,   455,   451,   388,   456,   443,
     444,   464,    59,   453,   453,   453,   453,   453,   453,   453,
     453,   453,   453,   568,   453,   453,   453,   453,   645,   453,
     474,   465,   645,   477,   568,   478,   412,   494,  2782,  2782,
     645,   645,   645,   645,   495,   483,   429,   498,   568,   645,
     482,     0,  2782,   645,   568,   499,   496,   501,    54,   645,
     645,   645,   645,   492,   132,   497,  3001,   504,   503,   509,
     441,   500,    55,   502,   493,   505,  2782, -1105,   645, -1105,
     512,   506,   514, -1105,   507,   510, -1105,   511,   508,   515,
    2339,  2339, -1105, -1105,   520,   522,   519,   525,   516,   527,
     517,   536,   521,   526,    44,    44,    44,    44,    44,    44,
      44,    44,    44,    44,    44,    44,    44,    44,   594,   594,
     594,   594,   594,   594,   594,   594,   594,   529, -1105, -1105,
   -1105,    44,    44,    44,    44, -1105, -1105, -1105,   538,   533,
     645,    44,    44,   542, -1105, -1105,   543,   534,   545,  2339,
    2339,    44, -1105, -1105,    44,   546,   556,   537,   586, -1105,
   -1105, -1105,   576, -1105,    44, -1105,    44, -1105,    44,  2782,
   -1105, -1105, -1105,   588,   589,   596,   582,   144,   591, -1105,
      44,    44,    44,    44,    44,    44,    44,    44,    44,    44,
      44,    44,    44,    44,    44,    44,   606,    44,   590,   518,
     601,    44,    44,    44,    44,   594,   594, -1105, -1105,   215,
      37, -1105, -1105,  2782, -1105,   603,   607,   600,   604,   613,
     610,   617,   620,   621,   623, -1105, -1105,   605, -1105, -1105,
     619,   626,   618,   563,  1673,  1895,   631,   653,   652,   659,
     662,   608,   669,   663,   664,   670,   645,   103,   645,   645,
    2782,   645,  2782,  2782,   645,   645,   645,   645,  2782,   645,
     666,   645,  2782,   645,   645,   609,   676,    44, -1105,   645,
     622,   677,   686,   624,  2782,  2782,   645,   645,   679,   682,
     692,   627,   681,   645,    82,   645,   685, -1105,   632,   700,
     701,   687,   694,   645,   645,   645,   645,   645,   645,   645,
     645,   645,   645,   645,   645,  2782,   645,  2782,   645,   695,
     645,   705,   688,   708,   645,   645,   645,   645,   414,   475,
     594,   698,   709,   711,   710,   725,   656,   723,   728,   718,
     726, -1105,   730,   715,   731,   733, -1105, -1105,   673,   736,
     741,   743,   735,   745,   732,   684,   747,   742, -1105,   734,
     751,    44, -1105, -1105, -1105, -1105, -1105, -1105,  2339,  2782,
      44,    44,    44, -1105,  2339,    44, -1105, -1105,  2782,    44,
      44,   749,   691,   645,    44, -1105,   754,   693,   752,   756,
      44,  3220,    44,    44, -1105, -1105, -1105,   699,   766,   758,
     764,   753,    44, -1105,    44, -1105,   704,   767,   768,   769,
     774,   765,    44,    44,    44,    44,    44,    44,    44,    44,
      44,    44,    44,    44,  3439,    44,  3658,    44,   776,    44,
     773,   778,   775,    44,    44,    44,    44,   594,   594,   594,
     714,   770,   781,   779,   777,   786,   784,   785,   716,   729,
     792,   790,   789,   788,   791,   803,   796, -1105,   805,   797,
   -1105,   793, -1105, -1105,   794,   795,   645,  2782,   645,   645,
     645,  2782,   645,   645,   645,   798,   804,    44,   645,   802,
     806,   815,   808,  2782,  2561,    82,   809,   811,   816,   812,
     817,   645,   645,   818,   820,   823,   739, -1105, -1105,   645,
     645,  2782,   645,    99,   645,   568,  2782,   645,   497,  3001,
    3001,  2561,  2782,  2561,  2782, -1105,    82,   824,   828,   771,
     645,   645,   645,   645,   594,   594,   829,   772,   833,   831,
     780,   832,   835,   782,   826,   846, -1105,   850, -1105,   836,
     837,   842,   841,   843,    61,   848,   851,   861, -1105,  2339,
      44, -1105,    44,  2339,    44, -1105, -1105,   847,   852,   645,
   -1105, -1105,   862,   844, -1105,   869,  3877,   594,   594,   900,
   -1105,  2782, -1105, -1105, -1105, -1105, -1105,   867,   841,   843,
     118,   884, -1105,    44,   873,   136,   825,   886, -1105, -1105,
      44, -1105, -1105,  2782, -1105,   892,   883, -1105, -1105, -1105,
   -1105, -1105, -1105, -1105, -1105, -1105,  2782,    44, -1105, -1105,
   -1105,   900,  4096,   900,  4315, -1105,   830, -1105,   896,    44,
      44,    44,    44,   879,   897,   834,   838,   893,   157,   903,
     904,   891,   895,   906,   888,   894,   907, -1105, -1105,   898,
     901,   911,   905,   908,  2782,  2782,  2782,  2782,   645,   909,
     919,    44,   910,   912,   914,  2561,  2561,   913,   915,   917,
     924,   645,   920,   918,   916,   927,   645,   921,   935,   645,
    2561,  2561,   936,   938,   645,   645,   497,    82,   930,   945,
     108,   227,   941,   939,   937,   942,   944,   952,   943, -1105,
     947,   899,   854,   948,   949,   923, -1105,   955,    44,  2782,
    2782,    44, -1105,   953,   961,  2782,   954,   959,   950,   900,
   -1105,   964,   966,   970,   969, -1105,   976,   973,   977,   210,
   -1105,   962,   994,    44,   900,   900,   982,   990,    44, -1105,
   -1105, -1105,   989,   996,   997,   999,  1000,  1003,   922,   998,
    1001,  1015,  1002,  1018,  1008,  1009,  1010,   222,   958,  1011,
    1019,  1014,  1016,  1023,    44,  1017,  1020,   965,  1021,   968,
    1022, -1105,  1024,   975,  1028,  1029,  1030, -1105,   568,  1034,
    1035,   645,  1036,  1032,  1037,  1043,  1038,  1050,  1045,   991,
    1040,  1048,  1051,  1061,  1047,  1056,  1053,  1049,  1057,  1065,
     150,  1062,  1012,  1079,  1068, -1105,    82,  1069,  1064,  1081,
    1066,  1083,  1075,  1071,   212,  1076,  1073,  1082, -1105,  1084,
    1077, -1105,  1078, -1105,  1088,  1089,  1091,  1092, -1105,  1093,
    1090,  1085,  1094,  1039, -1105,  1106,  1044,  1112,  1110,  1114,
      65,  1104,  1118,  1121,  1119,  1120,    44,  1122,  1060,  1123,
    1063,  1127,  1128,  1067,  1130,  1124,  1115,  1070,  1117,  1125,
    1132,  1080,  1134, -1105,  1137, -1105,  1147,  1153,  1140, -1105,
    1139,  1146,   292,  1152,  1154,  1155,  1143,  1157,  1144,  1156,
    1158,  1162,  1160,   645,  1161,  1164,  1149,  1165,  1150,  1163,
     296,  1159,  1166,  1167,    98, -1105,  1168,  1170,  1172, -1105,
   -1105,  1169,  1175, -1105,  1171,  1173,  1182,   102,  1177,  1180,
    1107,  1174,  1176,  1179,  1181,  1183, -1105,  1185,    44,  1186,
    1190,  1191,  1197,  1194,  1187,  1200,  1204,  1201,  1193,  1108,
    1208,  1202,  1196,  1148,  1206,  1217,  1214,  1205,  1207,  1178,
    1225,  1209,  1218,  1184,  1224,  1221,  1229,  1228,  1189,    17,
    1220, -1105,   497,  1216,  1219,  1235,  1226,  1236,    18,  1239,
    1230,  1243,  1189,    40,  1246,  1232,  1237,  1248,  1249,  1234,
    1254,  1192,  1247,  1252,  1256,  1253,  1244,  1257,  1255,  1259,
    1263,  1258,  1261, -1105,  1262,  1251,    44,  1269,  1274,  1271,
    1276,  1270,  1268,  1275,  1280,  1278,  1264,  1273,  1272,  1283,
    1277,  1281,  1286,    97,  1282,  1293,  1287,  1294,  1291,  1279,
   -1105,  1289,  1284,  1238,  1305,  1306,  1240,    16,  1307, -1105,
    1309,  1284,  1312,  1300,  1313,  1260,  1314,  1301,  1304, -1105,
   -1105, -1105,  1316,  1265,  1308,  1310,  1319, -1105,  1311,  1317,
    1320,  1315,  1318,  1321, -1105,  1323,  1322,  1325,  1324,  1329,
    1327,    44, -1105, -1105, -1105, -1105, -1105,  1330,  1339,  1332,
    1340,  1341,  1333,  1336,  1346,  1347,  1348,   239,  1334,  1328,
    1342, -1105,  1345,  1343,  1288,  1344,  1349,  1360,  1362,  1351,
    1363,  1295,  1350,    82, -1105,  1343,  1351,  1355,  1302,  1370,
    1358, -1105,  1364,  1303,  1365,  1361,  1367,  1368,  1326,  1331,
   -1105,  1366,  1356,  1335,  1369,  1371, -1105,  1354,  1375,  1372,
   -1105,  1331,  1373,  1374,  1380, -1105,   246,  1377,  1382,  1376,
   -1105,   248,  1378,  1385,  1379,  1386,  1392,  1390, -1105,  1395,
    1394,  1400,  1403,  1393,  1396,  1398,  1399,  1402, -1105,  1405,
    1401,  1406,  1391,  1337,  1404,  1397,  1407,  1408,  1409,  1411,
    1412, -1105,  1410,  1418,  1414, -1105,  1415,  1420,  1419,  1413,
    1426,  1423,  1433,  1434,  1417,  1421,  1439,  1437,  1429,  1430,
   -1105,  1432,  1435,  1443,  1436,  1438,  1425,  1428,  1441,  1440,
    1446,  1442,  1445,  1447, -1105,  1448, -1105,  1444,  1455,  1454,
    1464,  1465, -1105,  1467,  1458,  1468,  1469, -1105, -1105,  1470,
    1456,  1459,  1460,  1462,  1381,  1457,  1466,  1471,  1472,  1477,
    1479,  1474, -1105,  1480, -1105,  1482, -1105,  1485,  1473,  1476,
   -1105,  1484,  1486,  1487, -1105,  1478,  1483, -1105, -1105, -1105,
    1481, -1105
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105,
   -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105,
    -748, -1105, -1105, -1105, -1105, -1105,  -929, -1104, -1105,   185,
      89, -1105,  -510,  -840, -1004,   183,  -978,  -506,  -959,  -908,
    -732,  -783,   523,  -217,   357,  -950,   375,  -663,   480,  -546,
      81,   116,     2,   458,  -250,  -477,   -15,  1475, -1105, -1105,
   -1105, -1105, -1105, -1105, -1105, -1105, -1105, -1105,  -465, -1105,
   -1105,   967, -1105, -1105, -1105, -1105, -1105,   -72,  1245,  1250,
    1266,  -194,  1242,  1267,  1285,  1290,  1292,  1296,  1297,  1298,
    1299,  1338,  1352,  1353,  -262,  -260,  -247,    56, -1105,  1357,
   -1105,  1359, -1105, -1105, -1105, -1105,  1383,  -246, -1105, -1105,
    1241,  -349, -1105,  1384, -1105,  1387,  1388,  -242, -1105,    88,
     -24,  -256,  1389, -1105,   974, -1105, -1105, -1105, -1105,    -5,
    1613, -1105,  -255, -1105, -1105, -1105, -1105, -1105, -1105,  1829,
     956, -1105, -1105
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -220
static const yytype_int16 yytable[] =
{
     275,   894,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   273,   856,   708,
    1098,   374,   642,  1073,   644,   593,   476,   882,   477,   421,
     431,   433,   639,   967,   651,   394,   398,   654,   659,   395,
     399,   478,  -219,   661,   671,  1141,     1,   670,     2,  1529,
    1530,  1101,  1210,  1103,  1463,  1463,  1046,   302,   630,    36,
    1218,  1475,  1400,  1084,     3,   303,     4,     5,  1097,   645,
       6,    43,   725,   676,   665,     7,     8,   720,  1476,   436,
       9,    10,    11,   660,    12,   677,   603,    44,  1356,   672,
     340,   678,   721,   347,   352,  1129,   441,   415,  1130,   443,
     341,  1357,  1109,  1110,  1111,  1112,  1464,  1471,   308,   618,
     619,   620,   621,   622,   623,   624,   625,   626,  1514,  1410,
    1329,  1085,  1044,   849,  1515,  1421,    33,    38,  1516,  1224,
     767,  1086,  1411,    39,  1192,  1225,  1412,   850,  1422,   318,
     320,   321,   322,   323,   324,   325,   326,   327,   435,   436,
     437,   698,  1148,   438,   439,  1149,   401,  1301,   402,   300,
     440,   403,   699,   700,   696,   301,   441,   442,   404,   443,
    1153,   790,  1320,  1124,   319,   319,   319,   319,   319,   319,
     319,   319,   319,   791,  1321,   345,    34,   346,  1220,   347,
     348,  1173,    35,   305,  1174,  1199,   422,   349,   340,   306,
     423,   391,    37,   350,   351,   354,   352,   390,   424,   681,
    1214,  1215,   391,   420,   426,   701,    40,   352,   486,   392,
      41,   820,   590,   591,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,  1334,    47,    48,    42,   590,   591,
     848,  1277,   854,   855,  1255,  1278,  1335,  1124,  1226,   865,
     605,   867,   606,  1279,  1227,    45,   389,    46,   870,   412,
    1574,  -219,  -219,  -219,   291,   607,  1575,  1614,   270,  1619,
      -4,    -4,   292,  1615,   484,  1620,   396,   400,   293,   895,
     297,   432,   503,   504,   544,   504,   298,   902,   903,   904,
     905,   906,   907,   908,   909,   910,   911,   912,   913,   294,
     919,   295,   684,   689,   590,   591,   296,   665,   923,   924,
     925,   926,   680,  1386,  1387,   299,   683,  1405,  1406,   608,
     609,   610,   611,   612,   613,   614,   615,   616,   617,   502,
     631,   632,   633,   634,   304,   637,  1099,  1100,    47,   512,
     734,   735,   382,   460,   479,   513,   387,   514,   515,   516,
     517,   518,   340,   519,   487,   520,   521,   522,   523,   524,
     488,   525,   526,   527,   528,   529,   384,   386,   489,   531,
     490,   532,   491,   493,   534,   492,   494,   495,   497,   538,
     539,   540,   496,   541,   542,   543,  1188,   498,   500,  1191,
     501,   505,   506,   507,   508,   509,   530,   548,   533,   549,
     535,   510,   551,   552,  1398,   553,   554,   511,   536,   537,
     545,   558,   559,   560,   561,   562,   563,   564,   565,   566,
     927,   546,   547,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   550,   499,   555,   499,   499,   499,   499,
     499,   499,   499,   499,   556,   557,   567,   568,   569,   571,
    1038,   570,   708,   572,  1466,   573,   579,   574,   575,   580,
     584,   585,   587,  1244,   581,   588,   586,   582,   577,   583,
     589,   578,   594,   595,   596,  1072,   597,   598,   599,   600,
     603,   928,   601,  1087,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   602,   271,   638,   639,  1066,   643,
     646,   647,   656,  1326,   705,   706,   308,   618,   619,   620,
     621,   622,   623,   624,   625,   626,   648,   655,   657,   662,
     658,   673,   674,   675,   696,   629,   715,   716,   717,   593,
     718,   723,   724,   719,   629,   726,   629,   728,   722,   727,
     732,   812,   733,   652,   653,   729,   730,   736,   731,   737,
     629,   738,   739,   740,   741,   743,   629,   742,   745,   760,
     744,   692,   693,   694,   695,   765,   766,   711,   714,   770,
     771,   772,   773,   778,   780,   484,   484,   308,   618,   619,
     620,   621,   622,   623,   624,   625,   626,   627,   779,   746,
     747,   748,   749,   750,   751,   752,   753,   754,   755,   756,
     757,   758,   759,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   781,   782,   786,   761,   762,   763,   764,
     708,   789,   787,   788,   792,   809,   768,   769,   813,   811,
     821,   822,   823,   825,   774,   775,   776,   826,   827,   777,
     829,   824,   629,   828,   830,  1205,   832,   833,   831,   783,
     834,   784,   835,   785,   308,   618,   619,   620,   621,   622,
     623,   624,   625,   626,   838,   793,   794,   795,   796,   797,
     798,   799,   800,   801,   802,   803,   804,   805,   806,   807,
     808,   710,   810,   839,   840,   842,   814,   815,   816,   817,
    1066,   841,   844,   845,   847,   846,   866,   843,   871,   318,
     320,   321,   322,   323,   324,   325,   326,   327,   872,   878,
     877,   876,   887,   879,   888,   889,   890,   891,   896,   577,
     577,   897,   898,   899,   901,   900,   918,   920,   921,   339,
     922,   930,   931,   933,   319,   319,   319,   319,   319,   319,
     319,   319,   319,   932,   934,   935,   936,   937,   938,   939,
     940,   941,   873,   857,   942,   945,   860,   861,   862,   863,
     943,   629,   944,   629,   946,   869,   947,   948,   950,   482,
     952,   875,   949,   951,   955,   953,   965,   954,   884,   886,
     966,   969,   970,   972,   971,   893,   818,   819,   976,   977,
     978,   979,   980,   983,   984,   985,   986,   987,   988,  1005,
    1007,  1008,  1009,  1016,  1018,  1024,  1017,  1020,   915,   665,
     917,  1019,   629,  1021,  1022,  1026,  1023,  1027,  1025,  1028,
    1029,   319,   319,  1031,  1030,   499,  1032,  1033,  1077,  1034,
    1047,  1037,  1036,  1035,  1052,  1048,   956,  1054,  1069,  1053,
    1055,  1068,  1067,   957,  1070,   958,   959,   960,  1071,   961,
     962,  1074,  1075,  1116,   963,   964,  1076,  1106,  1107,   968,
    1108,  1114,  1113,  1115,  1118,  1119,  1121,  1122,   975,  1117,
    1123,  1120,  1126,  1124,  1132,   875,  1125,   981,  1127,   982,
    1128,  1131,  1133,  1143,  1139,  1140,   708,   989,   990,   991,
     992,   993,   994,   995,   996,   997,   998,   999,  1000,  1142,
    1002,   929,  1004,  1144,  1006,  1146,  1147,  1150,  1010,  1011,
    1012,  1013,  1152,  1155,  1154,  1157,  1158,  1163,  1168,  1162,
    1172,  1169,  1175,  1170,  1177,  1176,  1180,  1171,  1178,  1179,
    1182,  1187,  1181,  1236,   499,   499,   319,  1183,  1185,  1184,
     339,  1194,  1186,  1237,  1240,  1211,  1268,  1193,  1196,  1208,
    1197,  1201,  1049,  1198,  1202,  1203,  1204,  1207,  1206,  1209,
    1040,  1041,  1042,   576,   875,  1045,   886,  1212,  1222,  1216,
    1051,  1217,  1223,  1228,  1231,  1230,  1063,  1232,  1229,  1233,
    1243,  1256,  1234,  1235,   893,  1239,  1238,  1241,  1247,  1242,
    1245,  1079,  1081,  1246,  1079,   629,  1091,  1093,  1248,  1079,
     711,   714,   714,  1063,  1249,  1063,  1250,  1251,  1014,  1015,
    1252,  1253,   886,   886,   886,   886,  1254,  1257,   649,   650,
    1533,  1259,  1260,  1262,  1134,  1135,  1263,  1136,  1137,  1138,
    1264,  1265,   669,  1266,   339,  1267,  1269,  1270,  1271,  1273,
    1274,  1272,  1282,   319,   319,   499,   713,  1280,  1275,  1276,
    1281,  1051,  1283,  1285,  1289,  1284,  1287,  1291,  1151,  1288,
    1290,  1292,  1303,  1293,  1294,  1156,  1295,  1305,  1296,  1297,
     482,   482,  1299,  1300,  1307,  1302,  1304,  1306,  1308,  1310,
    1309,  1311,  1159,  1312,  1313,  1314,  1533,  1315,  1317,  1318,
     710,  1316,  1319,  1322,  1164,  1165,  1166,  1167,  1324,  1325,
    1327,  1323,  1328,  1329,  1330,  1331,  1332,   339,   339,  1333,
    1336,  1337,  1338,  1340,   710,  1346,  1341,   710,  1339,   710,
    1342,  1347,  1343,  1344,  1348,  1345,  1195,   339,  1350,  1351,
     499,   499,  1349,  1352,  1353,  1354,  1355,  1358,   818,   819,
    1051,  1359,  1360,  1362,  1361,  1364,  1366,  1063,  1063,  1365,
    1368,  1369,  1367,  1371,  1373,  1375,  1370,  1372,  1081,  1374,
    1384,  1091,  1063,  1063,  1376,  1377,  1081,   884,   711,  1378,
    1381,   339,  1379,   319,   319,  1380,  1382,  1383,  1385,  1388,
    1393,  1389,  1390,  1391,  1392,  1396,  1400,  1402,  1394,  1401,
    1403,  1395,  1397,  1399,  1415,  1404,  1425,  1443,  1258,  1407,
    1414,  1426,  1408,  1261,  1418,  1409,  1413,  1417,  1420,  1416,
    1423,  1419,  1424,  1434,   576,   576,  1427,  1428,  1435,  1429,
    1436,  1437,  1430,  1431,  1433,  1438,  1439,  1440,  1441,  1286,
     669,  1442,   858,   859,  1444,  1445,  1448,  1447,   864,  1446,
    1449,  1450,   868,  1451,  1454,  1456,  1452,  1458,  1459,  1455,
    1460,  1461,  1465,  1463,   881,   881,  1468,  1470,  1472,  1467,
    1093,   710,   710,  1081,  1474,  1477,  1469,  1453,  1478,  1475,
    1473,  1479,  1480,  1457,  1481,  1482,   710,   710,  1462,  1484,
    1487,  1483,   710,  1485,  1488,   914,  1492,   916,  1486,  1496,
    1489,  1491,  1490,  1495,  1493,  1494,  1498,  1499,  1500,  1501,
    1503,  1502,  1504,  1505,  1506,  1508,  1510,  1507,  1512,  1513,
    1509,  1363,  1518,  1511,  1521,  1520,   339,   339,  1522,  1519,
    1517,  1524,   339,  1523,  1526,  1527,   339,  1525,  1537,  1528,
    1538,  1539,  1540,  1543,  1541,  1544,  1545,  1546,  1550,   339,
    1552,  1548,  1549,  1553,  1213,  1551,  1590,  1298,  1219,  1542,
    1562,  1554,  1577,  1564,  1547,  1560,  1555,  1557,  1558,  1559,
    1556,  1561,  1565,  1567,  1568,   893,  1566,  1569,  1570,  1571,
    1572,  1573,   339,  1576,   339,  1579,  1578,  1581,  1582,  1584,
    1580,  1585,  1587,  1432,  1588,  1591,  1589,  1583,  1586,  1593,
    1594,  1592,  1596,  1598,  1595,  1604,  1608,  1609,  1597,  1599,
    1603,  1600,  1607,  1613,  1622,  1606,  1617,  1611,  1624,  1610,
    1612,  1625,  1621,  1626,  1618,  1601,  1616,  1623,  1627,  1629,
    1602,  1628,  1630,  1631,  1605,  1638,  1640,  1639,  1642,  1632,
    1633,  1634,  1654,  1637,   711,  1635,  1659,  1039,  1636,  1644,
    1641,  1043,  1649,  1647,  1652,  1643,  1645,  1646,  1655,  1648,
    1656,  1497,  1650,  1056,  1651,  1653,  1657,  1658,  1661,  1660,
    1662,  1663,  1667,  1664,  1665,  1670,  1671,  1668,  1666,  1674,
    1693,  1083,  1673,  1675,  1669,  1679,  1096,  1672,  1680,   713,
     713,  1681,  1102,  1676,  1104,  1677,  1678,  1682,  1683,  1684,
    1685,  1686,  1687,  1688,  1689,  1694,  1691,   339,  1692,  1690,
    1698,   339,  1699,  1711,  1695,  1702,  1701,  1696,  1703,  1704,
    1697,  1700,  1705,  1710,   339,  1709,  1563,  1706,   666,   339,
     704,  1200,  1707,  1708,  1221,   307,     0,   428,   406,  1105,
     464,     0,   685,   407,     0,     0,     0,     0,     0,     0,
       0,   339,     0,     0,     0,     0,     0,     0,   710,   408,
       0,     0,     0,     0,   339,   465,     0,     0,     0,     0,
     339,     0,   339,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   466,     0,     0,     0,     0,   467,     0,
     468,     0,     0,     0,   469,   470,   471,   472,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   881,  1189,  1190,   881,     0,     0,
       0,     0,     0,     0,     0,     0,   473,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     474,   475,     0,   418,     0,   480,     0,   339,   339,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   409,   410,     0,     0,
       0,   411,   413,   430,     0,   669,   328,    52,    53,    54,
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
     265,   266,   267,   268,   269,   836,   414,   270,   328,    52,
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
     263,   264,   265,   266,   267,   268,   269,   481,   837,   270,
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
     261,   262,   263,   264,   265,   266,   267,   268,   269,     0,
       0,   270,   328,    52,    53,    54,    55,    56,   329,   330,
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
     269,     0,     0,   270,   328,    52,    53,    54,  1057,  1058,
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
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   590,   591,   328,    52,    53,    54,    55,
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
     266,   267,   268,   269,   328,    52,    53,    54,    55,    56,
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
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   328,   974,    53,    54,    55,    56,   329,
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
     268,   269,   328,  1001,    53,    54,    55,    56,   329,   330,
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
     269,   328,  1003,    53,    54,    55,    56,   329,   330,   331,
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
     328,  1145,    53,    54,    55,    56,   329,   330,   331,   332,
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
    1160,    53,    54,    55,    56,   329,   330,   331,   332,   333,
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
     262,   263,   264,   265,   266,   267,   268,   269,   328,  1161,
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
     263,   264,   265,   266,   267,   268,   269
};

static const yytype_int16 yycheck[] =
{
      15,   784,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    15,   750,   565,
     998,   277,   532,   982,   534,   502,   288,   775,   288,   285,
     286,   286,    32,   873,   540,   281,   282,   543,   548,   281,
     282,   288,     5,   549,   554,  1049,     1,   553,     3,    33,
      34,  1001,  1156,  1003,    37,    37,   964,    30,   523,    23,
    1164,    21,    22,   992,    19,    38,    21,    22,   997,   534,
      25,    23,   578,    19,   551,    30,    31,    22,    38,    20,
      35,    36,    37,   548,    39,    31,    27,    39,    23,   554,
      21,    37,    37,    23,    40,    34,    37,    27,    37,    40,
      31,    36,  1010,  1011,  1012,  1013,    89,    89,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    21,    21,
      22,    22,   962,    20,    27,    23,    22,    27,    31,    21,
     640,    32,    34,    33,  1138,    27,    38,    34,    36,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    19,    20,
      21,    19,    34,    24,    25,    37,    19,  1261,    21,    31,
      31,    24,    30,    31,    32,    37,    37,    38,    31,    40,
      34,    27,    22,    37,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    39,    34,    19,    30,    21,  1166,    23,
      24,    34,    36,    31,    37,  1145,    19,    31,    21,    37,
      23,    24,    23,    37,    38,   277,    40,    19,    31,   558,
    1160,  1161,    24,   285,   286,   564,    19,    40,   290,    31,
      39,     6,   222,   223,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    22,   225,   226,    23,   222,   223,
     746,    19,   748,   749,    34,    23,    34,    37,    21,   759,
     512,   761,   512,    31,    27,    32,   280,     0,   764,   283,
      21,   224,   225,   226,    22,   512,    27,    21,   224,    21,
     225,   226,    23,    27,   289,    27,   281,   282,    23,   785,
      19,   286,    39,    40,    39,    40,    34,   793,   794,   795,
     796,   797,   798,   799,   800,   801,   802,   803,   804,    37,
     810,    38,   558,   558,   222,   223,    37,   784,   814,   815,
     816,   817,   558,    21,    22,    27,   558,    21,    22,   513,
     514,   515,   516,   517,   518,   519,   520,   521,   522,   344,
     524,   525,   526,   527,    20,   529,   999,  1000,   225,   354,
     590,   591,    31,   287,   288,   360,    31,   362,   363,   364,
     365,   366,    21,   368,    19,   370,   371,   372,   373,   374,
      19,   376,   377,   378,   379,   380,   278,   279,    38,   384,
      38,   386,    22,    33,   389,    38,    23,    23,    19,   394,
     395,   396,    37,   398,   399,   400,  1134,    39,    26,  1137,
      27,    26,    32,    42,    27,    23,    27,   412,    27,   414,
      39,    33,   417,   418,  1363,   420,   421,    33,    42,    27,
      26,   426,   427,   428,   429,   430,   431,   432,   433,   434,
       6,    42,    27,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    32,   318,    39,   320,   321,   322,   323,
     324,   325,   326,   327,    21,    27,    39,    39,    26,    30,
     956,    42,   998,    27,  1432,    38,    36,    33,    33,    38,
      21,    21,    20,  1195,    36,    19,    34,    40,   483,    38,
      22,   486,    22,    19,    19,   981,    25,    89,    22,    36,
      27,     6,    38,   993,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    30,    15,    22,    32,   975,    22,
      22,    89,    19,  1286,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    22,    22,    89,    37,
      22,    22,    26,    22,    32,   523,    22,    24,    19,  1006,
      89,    38,    27,    33,   532,    23,   534,    23,    36,    33,
      32,    23,    27,   541,   542,    38,    36,    27,    37,    27,
     548,    32,    27,    37,    27,    19,   554,    40,    32,    30,
      39,   559,   560,   561,   562,    27,    33,   565,   566,    27,
      27,    37,    27,    27,    37,   590,   591,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    32,   604,
     605,   606,   607,   608,   609,   610,   611,   612,   613,   614,
     615,   616,   617,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    27,    38,    27,   631,   632,   633,   634,
    1166,    39,    33,    27,    33,    19,   641,   642,    27,    39,
      27,    24,    32,    20,   649,   650,   651,    27,    21,   654,
      19,    37,   640,    23,    21,  1151,    27,    21,    43,   664,
      32,   666,    89,   668,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    33,   680,   681,   682,   683,   684,
     685,   686,   687,   688,   689,   690,   691,   692,   693,   694,
     695,   565,   697,    30,    32,    23,   701,   702,   703,   704,
    1167,    32,    23,    30,    24,    31,    30,    89,    89,   618,
     619,   620,   621,   622,   623,   624,   625,   626,    32,    23,
      33,    89,    33,    89,    32,    23,    89,    36,    33,   734,
     735,    89,    22,    22,    30,    38,    31,    22,    40,   271,
      22,    33,    23,    23,   618,   619,   620,   621,   622,   623,
     624,   625,   626,    32,    19,    89,    23,    19,    30,    23,
      20,    36,   767,   751,    23,    19,   754,   755,   756,   757,
      27,   759,    89,   761,    23,   763,    23,    32,    36,   289,
      23,   769,    27,    89,    23,    33,    27,    43,   776,   777,
      89,    27,    89,    27,    32,   783,   705,   706,    89,    23,
      32,    27,    39,    89,    27,    27,    27,    23,    33,    23,
      27,    23,    27,    89,    23,    89,    36,    30,   806,  1286,
     808,    32,   810,    27,    30,    23,    31,    27,    89,    30,
      32,   705,   706,    20,    33,   709,    30,    22,    89,    32,
      32,    36,    38,    40,    32,    31,   851,    22,    22,    33,
      32,    30,    33,   858,    32,   860,   861,   862,    31,   864,
     865,    33,    32,    22,   869,   870,    33,    33,    30,   874,
      89,    89,    33,    30,    32,    30,    40,    21,   883,    89,
      20,    89,    30,    37,    23,   873,    39,   892,    37,   894,
      37,    33,    21,    39,    37,    33,  1432,   902,   903,   904,
     905,   906,   907,   908,   909,   910,   911,   912,   913,    37,
     915,   820,   917,    34,   919,     5,    39,    23,   923,   924,
     925,   926,    39,    27,    89,    23,    33,    21,    39,    89,
      27,    24,    19,    89,    33,    21,    38,    89,    33,    23,
      23,    23,    38,    34,   818,   819,   820,    39,    27,    38,
     482,    22,    37,    89,    21,    24,    24,    38,    38,    33,
      38,    38,   967,    39,    39,    38,    32,    39,    38,    32,
     958,   959,   960,   483,   962,   963,   964,    32,    38,    33,
     968,    33,    27,    32,    32,    38,   974,    33,    39,    27,
      19,    19,    39,    36,   982,    36,    38,    32,    38,    36,
      36,   989,   990,    34,   992,   993,   994,   995,    34,   997,
     998,   999,  1000,  1001,    38,  1003,    36,    38,   927,   928,
      34,    38,  1010,  1011,  1012,  1013,    39,    23,   538,   539,
    1497,    39,    32,    34,  1039,  1040,    30,  1042,  1043,  1044,
      33,    32,   552,    33,   576,    32,    38,    36,    23,    21,
      32,    39,    23,   927,   928,   929,   566,    89,    39,    39,
      39,  1049,    38,    30,    89,    39,    39,    89,  1073,    39,
      39,    39,    30,    39,    89,  1080,    38,    24,    39,    39,
     590,   591,    38,    38,    24,    39,    39,    39,    33,    39,
      89,    33,  1097,    32,    23,    38,  1563,    31,    39,    32,
     974,    38,    27,    31,  1109,  1110,  1111,  1112,    19,    31,
      31,    89,    38,    22,    38,    22,    31,   649,   650,    38,
      34,    38,    30,    36,   998,    22,    38,  1001,    34,  1003,
      32,    31,    33,    32,    39,    33,  1141,   669,    89,    23,
    1014,  1015,    38,    89,    22,    25,    22,    33,  1057,  1058,
    1138,    23,    21,    23,    25,    23,    23,  1145,  1146,    89,
      23,    23,    89,    23,    39,    38,    89,    33,  1156,    89,
      21,  1159,  1160,  1161,    39,    33,  1164,  1165,  1166,    89,
      23,   713,    38,  1057,  1058,    38,    23,    37,    32,    27,
      36,    27,    27,    40,    27,    23,    22,    22,    32,    40,
      40,    33,    32,    32,    22,    32,    89,    89,  1213,    40,
      30,    27,    36,  1218,    33,    38,    38,    32,    26,    40,
      33,    38,    32,    23,   734,   735,    40,    38,    27,    38,
      23,    27,    39,    38,    38,    38,    26,    23,    27,  1244,
     750,    38,   752,   753,    26,    33,    30,    89,   758,    43,
      23,    27,   762,    38,    19,    27,    39,    23,    27,    40,
      21,    23,    32,    37,   774,   775,    21,    21,    19,    40,
    1258,  1145,  1146,  1261,    21,    19,    40,    89,    36,    21,
      40,    34,    23,    89,    40,    21,  1160,  1161,    89,    32,
      27,    89,  1166,    31,    40,   805,    23,   807,    32,    38,
      33,    32,    37,    31,    36,    34,    27,    23,    27,    23,
      32,    31,    27,    23,    26,    32,    23,    43,    27,    23,
      38,  1326,    19,    36,    23,    21,   858,   859,    39,    32,
      38,    37,   864,    34,    19,    19,   868,    89,    21,    89,
      21,    19,    32,    19,    21,    34,    32,    21,    19,   881,
      23,    33,    32,    23,  1159,    34,  1563,  1258,  1165,    89,
      23,    36,    24,    23,    89,    31,    38,    34,    36,    34,
      39,    32,    23,    23,    23,  1363,    34,    34,    32,    23,
      23,    23,   914,    39,   916,    30,    34,    89,    34,    19,
      37,    19,    19,  1398,    89,    30,    36,    38,    37,    19,
      32,    89,    89,    32,    30,    39,    42,    22,    33,    32,
      34,    33,    31,    23,    19,    36,    24,    34,    22,    37,
      36,    19,    34,    23,    38,    89,    39,    38,    23,    19,
      89,    27,    19,    30,    89,    19,    89,    36,    31,    33,
      32,    32,    19,    32,  1432,    33,    19,   957,    33,    31,
      36,   961,    24,    31,    24,    38,    37,    36,    22,    39,
      27,  1466,    38,   973,    39,    36,    23,    23,    19,    38,
      23,    32,    19,    33,    32,    40,    38,    31,    33,    23,
      89,   991,    32,    31,    36,    31,   996,    36,    23,   999,
    1000,    27,  1002,    38,  1004,    38,    38,    23,    23,    22,
      32,    23,    23,    23,    38,    38,    36,  1039,    36,    40,
      23,  1043,    23,    22,    38,    23,    26,    36,    23,    36,
      38,    37,    36,    30,  1056,    37,  1531,    33,   551,  1061,
     564,  1146,    36,    36,  1167,    50,    -1,   286,   283,  1006,
     288,    -1,   558,   283,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1083,    -1,    -1,    -1,    -1,    -1,    -1,  1432,   283,
      -1,    -1,    -1,    -1,  1096,   288,    -1,    -1,    -1,    -1,
    1102,    -1,  1104,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   288,    -1,    -1,    -1,    -1,   288,    -1,
     288,    -1,    -1,    -1,   288,   288,   288,   288,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1134,  1135,  1136,  1137,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   288,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     288,   288,    -1,   284,    -1,   288,    -1,  1189,  1190,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   283,   283,    -1,    -1,
      -1,   283,   283,   286,    -1,  1195,     3,     4,     5,     6,
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
     217,   218,   219,   220,   221,   222,   283,   224,     3,     4,
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
     215,   216,   217,   218,   219,   220,   221,   288,   223,   224,
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
     221,    -1,    -1,   224,     3,     4,     5,     6,     7,     8,
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
     219,   220,   221,   222,   223,     3,     4,     5,     6,     7,
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
     215,   216,   217,   218,   219,   220,   221
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
      31,   338,   355,   360,   367,     7,     8,   263,   276,   277,
     278,   279,   274,   275,   279,    22,    24,    19,    89,    33,
      22,    37,    36,    38,    27,   264,    23,    33,    23,    38,
      36,    37,    32,    27,   281,   281,    27,    27,    32,    27,
      37,    27,    40,    19,    39,    32,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   283,   283,
      30,   283,   283,   283,   283,    27,    33,   259,   283,   283,
      27,    27,    37,    27,   283,   283,   283,   283,    27,    32,
      37,    27,    38,   283,   283,   283,    27,    33,    27,    39,
      27,    39,    33,   283,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   283,    19,
     283,    39,    23,    27,   283,   283,   283,   283,   277,   277,
       6,    27,    24,    32,    37,    20,    27,    21,    23,    19,
      21,    43,    27,    21,    32,    89,   222,   223,    33,    30,
      32,    32,    23,    89,    23,    30,    31,    24,   264,    20,
      34,   248,   363,   364,   264,   264,   267,   279,   275,   275,
     279,   279,   279,   279,   275,   259,    30,   259,   275,   279,
     264,    89,    32,   283,   260,   279,    89,    33,    23,    89,
     247,   275,   247,   262,   279,   266,   279,    33,    32,    23,
      89,    36,   265,   279,   268,   264,    33,    89,    22,    22,
      38,    30,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   275,   279,   275,   279,    31,   259,
      22,    40,    22,   264,   264,   264,   264,     6,     6,   277,
      33,    23,    32,    23,    19,    89,    23,    19,    30,    23,
      20,    36,    23,    27,    89,    19,    23,    23,    32,    27,
      36,    89,    23,    33,    43,    23,   283,   283,   283,   283,
     283,   283,   283,   283,   283,    27,    89,   260,   283,    27,
      89,    32,    27,   283,     4,   283,    89,    23,    32,    27,
      39,   283,   283,    89,    27,    27,    27,    23,    33,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   283,   283,
     283,     4,   283,     4,   283,    23,   283,    27,    23,    27,
     283,   283,   283,   283,   277,   277,    89,    36,    23,    32,
      30,    27,    30,    31,    89,    89,    23,    27,    30,    32,
      33,    20,    30,    22,    32,    40,    38,    36,   264,   275,
     279,   279,   279,   275,   260,   279,   266,    32,    31,   283,
     261,   279,    32,    33,    22,    32,   275,     7,     8,   272,
     273,   275,   276,   279,   282,   271,   282,    33,    30,    22,
      32,    31,   264,   265,    33,    32,    33,    89,   253,   279,
     254,   279,   255,   275,   253,    22,    32,   259,   296,   297,
     256,   279,   257,   279,   295,   258,   275,   253,   263,   274,
     274,   272,   275,   272,   275,   269,    33,    30,    89,   266,
     266,   266,   266,    33,    89,    30,    22,    89,    32,    30,
      89,    40,    21,    20,    37,    39,    30,    37,    37,    34,
      37,    33,    23,    21,   283,   283,   283,   283,   283,    37,
      33,   261,    37,    39,    34,     4,     5,    39,    34,    37,
      23,   283,    39,    34,    89,    27,   283,    23,    33,   283,
       4,     4,    89,    21,   283,   283,   283,   283,    39,    24,
      89,    89,    27,    34,    37,    19,    21,    33,    33,    23,
      38,    38,    23,    39,    38,    27,    37,    23,   247,   275,
     275,   247,   261,    38,    22,   283,    38,    38,    39,   272,
     273,    38,    39,    38,    32,   264,    38,    39,    33,    32,
     254,    24,    32,   256,   272,   272,    33,    33,   254,   262,
     263,   271,    38,    27,    21,    27,    21,    27,    32,    39,
      38,    32,    33,    27,    39,    36,    34,    89,    38,    36,
      21,    32,    36,    19,   267,    36,    34,    38,    34,    38,
      36,    38,    34,    38,    39,    34,    19,    23,   283,    39,
      32,   283,    34,    30,    33,    32,    33,    32,    24,    38,
      36,    23,    39,    21,    32,    39,    39,    19,    23,    31,
      89,    39,    23,    38,    39,    30,   283,    39,    39,    89,
      39,    89,    39,    39,    89,    38,    39,    39,   257,    38,
      38,   254,    39,    30,    39,    24,    39,    24,    33,    89,
      39,    33,    32,    23,    38,    31,    38,    39,    32,    27,
      22,    34,    31,    89,    19,    31,   268,    31,    38,    22,
      38,    22,    31,    38,    22,    34,    34,    38,    30,    34,
      36,    38,    32,    33,    32,    33,    22,    31,    39,    38,
      89,    23,    89,    22,    25,    22,    23,    36,    33,    23,
      21,    25,    23,   283,    23,    89,    23,    89,    23,    23,
      89,    23,    33,    39,    89,    38,    39,    33,    89,    38,
      38,    23,    23,    37,    21,    32,    21,    22,    27,    27,
      27,    40,    27,    36,    32,    33,    23,    32,   265,    32,
      22,    40,    22,    40,    32,    21,    22,    40,    36,    38,
      21,    34,    38,    38,    30,    22,    40,    32,    33,    38,
      26,    23,    36,    33,    32,    89,    27,    40,    38,    38,
      39,    38,   283,    38,    23,    27,    23,    27,    38,    26,
      23,    27,    38,    89,    26,    33,    43,    89,    30,    23,
      27,    38,    39,    89,    19,    40,    27,    89,    23,    27,
      21,    23,    89,    37,    89,    32,   263,    40,    21,    40,
      21,    89,    19,    40,    21,    21,    38,    19,    36,    34,
      23,    40,    21,    89,    32,    31,    32,    27,    40,    33,
      37,    32,    23,    36,    34,    31,    38,   283,    27,    23,
      27,    23,    31,    32,    27,    23,    26,    43,    32,    38,
      23,    36,    27,    23,    21,    27,    31,    38,    19,    32,
      21,    23,    39,    34,    37,    89,    19,    19,    89,    33,
      34,   252,   270,   282,   329,   330,   331,    21,    21,    19,
      32,    21,    89,    19,    34,    32,    21,    89,    33,    32,
      19,    34,    23,    23,    36,    38,    39,    34,    36,    34,
      31,    32,    23,   283,    23,    23,    34,    23,    23,    34,
      32,    23,    23,    23,    21,    27,    39,    24,    34,    30,
      37,    89,    34,    38,    19,    19,    37,    19,    89,    36,
     270,    30,    89,    19,    32,    30,    89,    33,    32,    32,
      33,    89,    89,    34,    39,    89,    36,    31,    42,    22,
      37,    34,    36,    23,    21,    27,    39,    24,    38,    21,
      27,    34,    19,    38,    22,    19,    23,    23,    27,    19,
      19,    30,    33,    32,    32,    33,    33,    32,    19,    36,
      89,    36,    31,    38,    31,    37,    36,    31,    39,    24,
      38,    39,    24,    36,    19,    22,    27,    23,    23,    19,
      38,    19,    23,    32,    33,    32,    33,    19,    31,    36,
      40,    38,    36,    32,    23,    31,    38,    38,    38,    31,
      23,    27,    23,    23,    22,    32,    23,    23,    23,    38,
      40,    36,    36,    89,    38,    38,    36,    38,    23,    23,
      37,    26,    23,    23,    36,    36,    33,    36,    36,    37,
      30,    22
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
    { (yyval.String) = LSCPSERVER->SetFxSendName((yyvsp[(5) - (9)].Number),(yyvsp[(7) - (9)].Number),(yyvsp[(9) - (9)].String));                        }
    break;

  case 118:
#line 235 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetFxSendAudioOutputChannel((yyvsp[(5) - (11)].Number),(yyvsp[(7) - (11)].Number),(yyvsp[(9) - (11)].Number),(yyvsp[(11) - (11)].Number)); }
    break;

  case 119:
#line 236 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetFxSendMidiController((yyvsp[(5) - (9)].Number),(yyvsp[(7) - (9)].Number),(yyvsp[(9) - (9)].Number));              }
    break;

  case 120:
#line 237 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetFxSendLevel((yyvsp[(5) - (9)].Number),(yyvsp[(7) - (9)].Number),(yyvsp[(9) - (9)].Dotnum));                       }
    break;

  case 121:
#line 238 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetEcho((yyparse_param_t*) yyparse_param, (yyvsp[(3) - (3)].Dotnum));  }
    break;

  case 122:
#line 239 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetGlobalVolume((yyvsp[(3) - (3)].Dotnum));                            }
    break;

  case 123:
#line 242 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateAudioOutputDevice((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].KeyValList)); }
    break;

  case 124:
#line 243 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateAudioOutputDevice((yyvsp[(3) - (3)].String));    }
    break;

  case 125:
#line 244 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateMidiInputDevice((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].KeyValList));   }
    break;

  case 126:
#line 245 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateMidiInputDevice((yyvsp[(3) - (3)].String));      }
    break;

  case 127:
#line 246 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateFxSend((yyvsp[(3) - (5)].Number),(yyvsp[(5) - (5)].Number));            }
    break;

  case 128:
#line 247 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateFxSend((yyvsp[(3) - (7)].Number),(yyvsp[(5) - (7)].Number),(yyvsp[(7) - (7)].String)); }
    break;

  case 129:
#line 250 "lscp.y"
    { (yyval.String) = LSCPSERVER->ResetChannel((yyvsp[(3) - (3)].Number)); }
    break;

  case 130:
#line 253 "lscp.y"
    { (yyval.String) = LSCPSERVER->ClearMidiInstrumentMappings((yyvsp[(3) - (3)].Number));  }
    break;

  case 131:
#line 254 "lscp.y"
    { (yyval.String) = LSCPSERVER->ClearAllMidiInstrumentMappings(); }
    break;

  case 132:
#line 257 "lscp.y"
    { (yyval.String) = LSCPSERVER->DestroyAudioOutputDevice((yyvsp[(3) - (3)].Number)); }
    break;

  case 133:
#line 258 "lscp.y"
    { (yyval.String) = LSCPSERVER->DestroyMidiInputDevice((yyvsp[(3) - (3)].Number));   }
    break;

  case 134:
#line 259 "lscp.y"
    { (yyval.String) = LSCPSERVER->DestroyFxSend((yyvsp[(3) - (5)].Number),(yyvsp[(5) - (5)].Number)); }
    break;

  case 135:
#line 262 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String); }
    break;

  case 136:
#line 263 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String); }
    break;

  case 137:
#line 266 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputDevice((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));      }
    break;

  case 138:
#line 267 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputChannel((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number), (yyvsp[(3) - (7)].Number)); }
    break;

  case 139:
#line 268 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputType((yyvsp[(5) - (5)].String), (yyvsp[(3) - (5)].Number));        }
    break;

  case 140:
#line 269 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInput((yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].Number), (yyvsp[(9) - (9)].Number), (yyvsp[(3) - (9)].Number));      }
    break;

  case 141:
#line 270 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputDevice((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));        }
    break;

  case 142:
#line 271 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputPort((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));          }
    break;

  case 143:
#line 272 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputChannel((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));       }
    break;

  case 144:
#line 273 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputType((yyvsp[(5) - (5)].String), (yyvsp[(3) - (5)].Number));          }
    break;

  case 145:
#line 274 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetVolume((yyvsp[(5) - (5)].Dotnum), (yyvsp[(3) - (5)].Number));                 }
    break;

  case 146:
#line 275 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMute((yyvsp[(5) - (5)].Dotnum), (yyvsp[(3) - (5)].Number));            }
    break;

  case 147:
#line 276 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelSolo((yyvsp[(5) - (5)].Dotnum), (yyvsp[(3) - (5)].Number));            }
    break;

  case 148:
#line 277 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMap((yyvsp[(3) - (5)].Number), (yyvsp[(5) - (5)].Number));             }
    break;

  case 149:
#line 278 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMap((yyvsp[(3) - (5)].Number), -1);             }
    break;

  case 150:
#line 279 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMap((yyvsp[(3) - (5)].Number), -2);             }
    break;

  case 151:
#line 282 "lscp.y"
    { (yyval.Bool) = true;  }
    break;

  case 152:
#line 283 "lscp.y"
    { (yyval.Bool) = false; }
    break;

  case 153:
#line 286 "lscp.y"
    { (yyval.KeyValList)[(yyvsp[(1) - (3)].String)] = (yyvsp[(3) - (3)].String);          }
    break;

  case 154:
#line 287 "lscp.y"
    { (yyval.KeyValList) = (yyvsp[(1) - (5)].KeyValList); (yyval.KeyValList)[(yyvsp[(3) - (5)].String)] = (yyvsp[(5) - (5)].String); }
    break;

  case 155:
#line 290 "lscp.y"
    { (yyval.FillResponse) = fill_response_bytes;      }
    break;

  case 156:
#line 291 "lscp.y"
    { (yyval.FillResponse) = fill_response_percentage; }
    break;

  case 157:
#line 294 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDevices();           }
    break;

  case 158:
#line 295 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDevices();             }
    break;

  case 159:
#line 296 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListChannels();                    }
    break;

  case 160:
#line 297 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableEngines();            }
    break;

  case 161:
#line 298 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableMidiInputDrivers();   }
    break;

  case 162:
#line 299 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableAudioOutputDrivers(); }
    break;

  case 163:
#line 300 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListMidiInstrumentMappings((yyvsp[(3) - (3)].Number));    }
    break;

  case 164:
#line 301 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAllMidiInstrumentMappings();   }
    break;

  case 165:
#line 302 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListMidiInstrumentMaps();          }
    break;

  case 166:
#line 303 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListFxSends((yyvsp[(3) - (3)].Number));                   }
    break;

  case 167:
#line 306 "lscp.y"
    { (yyval.String) = LSCPSERVER->LoadInstrument((yyvsp[(1) - (5)].String), (yyvsp[(3) - (5)].Number), (yyvsp[(5) - (5)].Number));       }
    break;

  case 168:
#line 307 "lscp.y"
    { (yyval.String) = LSCPSERVER->LoadInstrument((yyvsp[(3) - (7)].String), (yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number), true); }
    break;

  case 169:
#line 310 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetEngineType((yyvsp[(1) - (3)].String), (yyvsp[(3) - (3)].Number)); }
    break;

  case 170:
#line 313 "lscp.y"
    { (yyval.LoadMode) = MidiInstrumentMapper::ON_DEMAND;      }
    break;

  case 171:
#line 314 "lscp.y"
    { (yyval.LoadMode) = MidiInstrumentMapper::ON_DEMAND_HOLD; }
    break;

  case 172:
#line 315 "lscp.y"
    { (yyval.LoadMode) = MidiInstrumentMapper::PERSISTENT;     }
    break;

  case 178:
#line 331 "lscp.y"
    { (yyval.Number) = 16; }
    break;

  case 185:
#line 350 "lscp.y"
    { (yyval.Dotnum) = (yyvsp[(1) - (1)].Number); }
    break;

  case 195:
#line 378 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (3)].String) + "," + (yyvsp[(3) - (3)].String); }
    break;

  case 198:
#line 383 "lscp.y"
    { std::stringstream ss; ss << "\'" << (yyvsp[(1) - (1)].Number) << "\'"; (yyval.String) = ss.str(); }
    break;

  case 199:
#line 384 "lscp.y"
    { std::stringstream ss; ss << "\'" << (yyvsp[(1) - (1)].Dotnum) << "\'"; (yyval.String) = ss.str(); }
    break;

  case 200:
#line 392 "lscp.y"
    { (yyval.Dotnum) = (yyvsp[(1) - (1)].Number); }
    break;

  case 201:
#line 393 "lscp.y"
    { (yyval.Dotnum) = -1; }
    break;

  case 202:
#line 396 "lscp.y"
    { std::string s; s = (yyvsp[(1) - (1)].Char); (yyval.String) = s; }
    break;

  case 203:
#line 397 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + (yyvsp[(2) - (2)].Char);                  }
    break;

  case 204:
#line 400 "lscp.y"
    { (yyval.Dotnum) = atof(String((yyvsp[(1) - (3)].String) + "." + (yyvsp[(3) - (3)].String)).c_str());                         }
    break;

  case 205:
#line 401 "lscp.y"
    { String s = "+"; s += (yyvsp[(2) - (4)].String); s += "."; s += (yyvsp[(4) - (4)].String); (yyval.Dotnum) = atof(s.c_str()); }
    break;

  case 206:
#line 402 "lscp.y"
    { (yyval.Dotnum) = atof(String("-" + (yyvsp[(2) - (4)].String) + "." + (yyvsp[(4) - (4)].String)).c_str());                   }
    break;

  case 207:
#line 406 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (1)].Char);      }
    break;

  case 208:
#line 407 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + (yyvsp[(2) - (2)].Char); }
    break;

  case 209:
#line 410 "lscp.y"
    { (yyval.Char) = '0'; }
    break;

  case 210:
#line 411 "lscp.y"
    { (yyval.Char) = '1'; }
    break;

  case 211:
#line 412 "lscp.y"
    { (yyval.Char) = '2'; }
    break;

  case 212:
#line 413 "lscp.y"
    { (yyval.Char) = '3'; }
    break;

  case 213:
#line 414 "lscp.y"
    { (yyval.Char) = '4'; }
    break;

  case 214:
#line 415 "lscp.y"
    { (yyval.Char) = '5'; }
    break;

  case 215:
#line 416 "lscp.y"
    { (yyval.Char) = '6'; }
    break;

  case 216:
#line 417 "lscp.y"
    { (yyval.Char) = '7'; }
    break;

  case 217:
#line 418 "lscp.y"
    { (yyval.Char) = '8'; }
    break;

  case 218:
#line 419 "lscp.y"
    { (yyval.Char) = '9'; }
    break;

  case 219:
#line 422 "lscp.y"
    { (yyval.Number) = atoi(String(1, (yyvsp[(1) - (1)].Char)).c_str());      }
    break;

  case 220:
#line 423 "lscp.y"
    { (yyval.Number) = atoi(String(String("1") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 221:
#line 424 "lscp.y"
    { (yyval.Number) = atoi(String(String("2") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 222:
#line 425 "lscp.y"
    { (yyval.Number) = atoi(String(String("3") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 223:
#line 426 "lscp.y"
    { (yyval.Number) = atoi(String(String("4") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 224:
#line 427 "lscp.y"
    { (yyval.Number) = atoi(String(String("5") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 225:
#line 428 "lscp.y"
    { (yyval.Number) = atoi(String(String("6") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 226:
#line 429 "lscp.y"
    { (yyval.Number) = atoi(String(String("7") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 227:
#line 430 "lscp.y"
    { (yyval.Number) = atoi(String(String("8") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 228:
#line 431 "lscp.y"
    { (yyval.Number) = atoi(String(String("9") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 229:
#line 433 "lscp.y"
    { (yyval.Char) = 'A'; }
    break;

  case 230:
#line 433 "lscp.y"
    { (yyval.Char) = 'B'; }
    break;

  case 231:
#line 433 "lscp.y"
    { (yyval.Char) = 'C'; }
    break;

  case 232:
#line 433 "lscp.y"
    { (yyval.Char) = 'D'; }
    break;

  case 233:
#line 433 "lscp.y"
    { (yyval.Char) = 'E'; }
    break;

  case 234:
#line 433 "lscp.y"
    { (yyval.Char) = 'F'; }
    break;

  case 235:
#line 433 "lscp.y"
    { (yyval.Char) = 'G'; }
    break;

  case 236:
#line 433 "lscp.y"
    { (yyval.Char) = 'H'; }
    break;

  case 237:
#line 433 "lscp.y"
    { (yyval.Char) = 'I'; }
    break;

  case 238:
#line 433 "lscp.y"
    { (yyval.Char) = 'J'; }
    break;

  case 239:
#line 433 "lscp.y"
    { (yyval.Char) = 'K'; }
    break;

  case 240:
#line 433 "lscp.y"
    { (yyval.Char) = 'L'; }
    break;

  case 241:
#line 433 "lscp.y"
    { (yyval.Char) = 'M'; }
    break;

  case 242:
#line 433 "lscp.y"
    { (yyval.Char) = 'N'; }
    break;

  case 243:
#line 433 "lscp.y"
    { (yyval.Char) = 'O'; }
    break;

  case 244:
#line 433 "lscp.y"
    { (yyval.Char) = 'P'; }
    break;

  case 245:
#line 433 "lscp.y"
    { (yyval.Char) = 'Q'; }
    break;

  case 246:
#line 433 "lscp.y"
    { (yyval.Char) = 'R'; }
    break;

  case 247:
#line 433 "lscp.y"
    { (yyval.Char) = 'S'; }
    break;

  case 248:
#line 433 "lscp.y"
    { (yyval.Char) = 'T'; }
    break;

  case 249:
#line 433 "lscp.y"
    { (yyval.Char) = 'U'; }
    break;

  case 250:
#line 433 "lscp.y"
    { (yyval.Char) = 'V'; }
    break;

  case 251:
#line 433 "lscp.y"
    { (yyval.Char) = 'W'; }
    break;

  case 252:
#line 433 "lscp.y"
    { (yyval.Char) = 'X'; }
    break;

  case 253:
#line 433 "lscp.y"
    { (yyval.Char) = 'Y'; }
    break;

  case 254:
#line 433 "lscp.y"
    { (yyval.Char) = 'Z'; }
    break;

  case 255:
#line 434 "lscp.y"
    { (yyval.Char) = 'a'; }
    break;

  case 256:
#line 434 "lscp.y"
    { (yyval.Char) = 'b'; }
    break;

  case 257:
#line 434 "lscp.y"
    { (yyval.Char) = 'c'; }
    break;

  case 258:
#line 434 "lscp.y"
    { (yyval.Char) = 'd'; }
    break;

  case 259:
#line 434 "lscp.y"
    { (yyval.Char) = 'e'; }
    break;

  case 260:
#line 434 "lscp.y"
    { (yyval.Char) = 'f'; }
    break;

  case 261:
#line 434 "lscp.y"
    { (yyval.Char) = 'g'; }
    break;

  case 262:
#line 434 "lscp.y"
    { (yyval.Char) = 'h'; }
    break;

  case 263:
#line 434 "lscp.y"
    { (yyval.Char) = 'i'; }
    break;

  case 264:
#line 434 "lscp.y"
    { (yyval.Char) = 'j'; }
    break;

  case 265:
#line 434 "lscp.y"
    { (yyval.Char) = 'k'; }
    break;

  case 266:
#line 434 "lscp.y"
    { (yyval.Char) = 'l'; }
    break;

  case 267:
#line 434 "lscp.y"
    { (yyval.Char) = 'm'; }
    break;

  case 268:
#line 434 "lscp.y"
    { (yyval.Char) = 'n'; }
    break;

  case 269:
#line 434 "lscp.y"
    { (yyval.Char) = 'o'; }
    break;

  case 270:
#line 434 "lscp.y"
    { (yyval.Char) = 'p'; }
    break;

  case 271:
#line 434 "lscp.y"
    { (yyval.Char) = 'q'; }
    break;

  case 272:
#line 434 "lscp.y"
    { (yyval.Char) = 'r'; }
    break;

  case 273:
#line 434 "lscp.y"
    { (yyval.Char) = 's'; }
    break;

  case 274:
#line 434 "lscp.y"
    { (yyval.Char) = 't'; }
    break;

  case 275:
#line 434 "lscp.y"
    { (yyval.Char) = 'u'; }
    break;

  case 276:
#line 434 "lscp.y"
    { (yyval.Char) = 'v'; }
    break;

  case 277:
#line 434 "lscp.y"
    { (yyval.Char) = 'w'; }
    break;

  case 278:
#line 434 "lscp.y"
    { (yyval.Char) = 'x'; }
    break;

  case 279:
#line 434 "lscp.y"
    { (yyval.Char) = 'y'; }
    break;

  case 280:
#line 434 "lscp.y"
    { (yyval.Char) = 'z'; }
    break;

  case 281:
#line 435 "lscp.y"
    { (yyval.Char) = '0'; }
    break;

  case 282:
#line 435 "lscp.y"
    { (yyval.Char) = '1'; }
    break;

  case 283:
#line 435 "lscp.y"
    { (yyval.Char) = '2'; }
    break;

  case 284:
#line 435 "lscp.y"
    { (yyval.Char) = '3'; }
    break;

  case 285:
#line 435 "lscp.y"
    { (yyval.Char) = '4'; }
    break;

  case 286:
#line 435 "lscp.y"
    { (yyval.Char) = '5'; }
    break;

  case 287:
#line 435 "lscp.y"
    { (yyval.Char) = '6'; }
    break;

  case 288:
#line 435 "lscp.y"
    { (yyval.Char) = '7'; }
    break;

  case 289:
#line 435 "lscp.y"
    { (yyval.Char) = '8'; }
    break;

  case 290:
#line 435 "lscp.y"
    { (yyval.Char) = '9'; }
    break;

  case 291:
#line 436 "lscp.y"
    { (yyval.Char) = '!'; }
    break;

  case 292:
#line 436 "lscp.y"
    { (yyval.Char) = '#'; }
    break;

  case 293:
#line 436 "lscp.y"
    { (yyval.Char) = '$'; }
    break;

  case 294:
#line 436 "lscp.y"
    { (yyval.Char) = '%'; }
    break;

  case 295:
#line 436 "lscp.y"
    { (yyval.Char) = '&'; }
    break;

  case 296:
#line 436 "lscp.y"
    { (yyval.Char) = '('; }
    break;

  case 297:
#line 436 "lscp.y"
    { (yyval.Char) = ')'; }
    break;

  case 298:
#line 436 "lscp.y"
    { (yyval.Char) = '*'; }
    break;

  case 299:
#line 436 "lscp.y"
    { (yyval.Char) = '+'; }
    break;

  case 300:
#line 436 "lscp.y"
    { (yyval.Char) = '-'; }
    break;

  case 301:
#line 436 "lscp.y"
    { (yyval.Char) = '.'; }
    break;

  case 302:
#line 436 "lscp.y"
    { (yyval.Char) = ','; }
    break;

  case 303:
#line 436 "lscp.y"
    { (yyval.Char) = '/'; }
    break;

  case 304:
#line 437 "lscp.y"
    { (yyval.Char) = ':'; }
    break;

  case 305:
#line 437 "lscp.y"
    { (yyval.Char) = ';'; }
    break;

  case 306:
#line 437 "lscp.y"
    { (yyval.Char) = '<'; }
    break;

  case 307:
#line 437 "lscp.y"
    { (yyval.Char) = '='; }
    break;

  case 308:
#line 437 "lscp.y"
    { (yyval.Char) = '>'; }
    break;

  case 309:
#line 437 "lscp.y"
    { (yyval.Char) = '?'; }
    break;

  case 310:
#line 437 "lscp.y"
    { (yyval.Char) = '@'; }
    break;

  case 311:
#line 438 "lscp.y"
    { (yyval.Char) = '['; }
    break;

  case 312:
#line 438 "lscp.y"
    { (yyval.Char) = '\\'; }
    break;

  case 313:
#line 438 "lscp.y"
    { (yyval.Char) = ']'; }
    break;

  case 314:
#line 438 "lscp.y"
    { (yyval.Char) = '^'; }
    break;

  case 315:
#line 438 "lscp.y"
    { (yyval.Char) = '_'; }
    break;

  case 316:
#line 439 "lscp.y"
    { (yyval.Char) = '{'; }
    break;

  case 317:
#line 439 "lscp.y"
    { (yyval.Char) = '|'; }
    break;

  case 318:
#line 439 "lscp.y"
    { (yyval.Char) = '}'; }
    break;

  case 319:
#line 439 "lscp.y"
    { (yyval.Char) = '~'; }
    break;

  case 320:
#line 440 "lscp.y"
    { (yyval.Char) = '\200'; }
    break;

  case 321:
#line 440 "lscp.y"
    { (yyval.Char) = '\201'; }
    break;

  case 322:
#line 440 "lscp.y"
    { (yyval.Char) = '\202'; }
    break;

  case 323:
#line 441 "lscp.y"
    { (yyval.Char) = '\203'; }
    break;

  case 324:
#line 441 "lscp.y"
    { (yyval.Char) = '\204'; }
    break;

  case 325:
#line 441 "lscp.y"
    { (yyval.Char) = '\205'; }
    break;

  case 326:
#line 442 "lscp.y"
    { (yyval.Char) = '\206'; }
    break;

  case 327:
#line 442 "lscp.y"
    { (yyval.Char) = '\207'; }
    break;

  case 328:
#line 442 "lscp.y"
    { (yyval.Char) = '\210'; }
    break;

  case 329:
#line 443 "lscp.y"
    { (yyval.Char) = '\211'; }
    break;

  case 330:
#line 443 "lscp.y"
    { (yyval.Char) = '\212'; }
    break;

  case 331:
#line 443 "lscp.y"
    { (yyval.Char) = '\213'; }
    break;

  case 332:
#line 444 "lscp.y"
    { (yyval.Char) = '\214'; }
    break;

  case 333:
#line 444 "lscp.y"
    { (yyval.Char) = '\215'; }
    break;

  case 334:
#line 444 "lscp.y"
    { (yyval.Char) = '\216'; }
    break;

  case 335:
#line 445 "lscp.y"
    { (yyval.Char) = '\217'; }
    break;

  case 336:
#line 445 "lscp.y"
    { (yyval.Char) = '\220'; }
    break;

  case 337:
#line 445 "lscp.y"
    { (yyval.Char) = '\221'; }
    break;

  case 338:
#line 446 "lscp.y"
    { (yyval.Char) = '\222'; }
    break;

  case 339:
#line 446 "lscp.y"
    { (yyval.Char) = '\223'; }
    break;

  case 340:
#line 446 "lscp.y"
    { (yyval.Char) = '\224'; }
    break;

  case 341:
#line 447 "lscp.y"
    { (yyval.Char) = '\225'; }
    break;

  case 342:
#line 447 "lscp.y"
    { (yyval.Char) = '\226'; }
    break;

  case 343:
#line 447 "lscp.y"
    { (yyval.Char) = '\227'; }
    break;

  case 344:
#line 448 "lscp.y"
    { (yyval.Char) = '\230'; }
    break;

  case 345:
#line 448 "lscp.y"
    { (yyval.Char) = '\231'; }
    break;

  case 346:
#line 448 "lscp.y"
    { (yyval.Char) = '\232'; }
    break;

  case 347:
#line 449 "lscp.y"
    { (yyval.Char) = '\233'; }
    break;

  case 348:
#line 449 "lscp.y"
    { (yyval.Char) = '\234'; }
    break;

  case 349:
#line 449 "lscp.y"
    { (yyval.Char) = '\235'; }
    break;

  case 350:
#line 450 "lscp.y"
    { (yyval.Char) = '\236'; }
    break;

  case 351:
#line 450 "lscp.y"
    { (yyval.Char) = '\237'; }
    break;

  case 352:
#line 450 "lscp.y"
    { (yyval.Char) = '\240'; }
    break;

  case 353:
#line 451 "lscp.y"
    { (yyval.Char) = '\241'; }
    break;

  case 354:
#line 451 "lscp.y"
    { (yyval.Char) = '\242'; }
    break;

  case 355:
#line 451 "lscp.y"
    { (yyval.Char) = '\243'; }
    break;

  case 356:
#line 452 "lscp.y"
    { (yyval.Char) = '\244'; }
    break;

  case 357:
#line 452 "lscp.y"
    { (yyval.Char) = '\245'; }
    break;

  case 358:
#line 452 "lscp.y"
    { (yyval.Char) = '\246'; }
    break;

  case 359:
#line 453 "lscp.y"
    { (yyval.Char) = '\247'; }
    break;

  case 360:
#line 453 "lscp.y"
    { (yyval.Char) = '\250'; }
    break;

  case 361:
#line 453 "lscp.y"
    { (yyval.Char) = '\251'; }
    break;

  case 362:
#line 454 "lscp.y"
    { (yyval.Char) = '\252'; }
    break;

  case 363:
#line 454 "lscp.y"
    { (yyval.Char) = '\253'; }
    break;

  case 364:
#line 454 "lscp.y"
    { (yyval.Char) = '\254'; }
    break;

  case 365:
#line 455 "lscp.y"
    { (yyval.Char) = '\255'; }
    break;

  case 366:
#line 455 "lscp.y"
    { (yyval.Char) = '\256'; }
    break;

  case 367:
#line 455 "lscp.y"
    { (yyval.Char) = '\257'; }
    break;

  case 368:
#line 456 "lscp.y"
    { (yyval.Char) = '\260'; }
    break;

  case 369:
#line 456 "lscp.y"
    { (yyval.Char) = '\261'; }
    break;

  case 370:
#line 456 "lscp.y"
    { (yyval.Char) = '\262'; }
    break;

  case 371:
#line 457 "lscp.y"
    { (yyval.Char) = '\263'; }
    break;

  case 372:
#line 457 "lscp.y"
    { (yyval.Char) = '\264'; }
    break;

  case 373:
#line 457 "lscp.y"
    { (yyval.Char) = '\265'; }
    break;

  case 374:
#line 458 "lscp.y"
    { (yyval.Char) = '\266'; }
    break;

  case 375:
#line 458 "lscp.y"
    { (yyval.Char) = '\267'; }
    break;

  case 376:
#line 458 "lscp.y"
    { (yyval.Char) = '\270'; }
    break;

  case 377:
#line 459 "lscp.y"
    { (yyval.Char) = '\271'; }
    break;

  case 378:
#line 459 "lscp.y"
    { (yyval.Char) = '\272'; }
    break;

  case 379:
#line 459 "lscp.y"
    { (yyval.Char) = '\273'; }
    break;

  case 380:
#line 460 "lscp.y"
    { (yyval.Char) = '\274'; }
    break;

  case 381:
#line 460 "lscp.y"
    { (yyval.Char) = '\275'; }
    break;

  case 382:
#line 460 "lscp.y"
    { (yyval.Char) = '\276'; }
    break;

  case 383:
#line 461 "lscp.y"
    { (yyval.Char) = '\277'; }
    break;

  case 384:
#line 461 "lscp.y"
    { (yyval.Char) = '\300'; }
    break;

  case 385:
#line 461 "lscp.y"
    { (yyval.Char) = '\301'; }
    break;

  case 386:
#line 462 "lscp.y"
    { (yyval.Char) = '\302'; }
    break;

  case 387:
#line 462 "lscp.y"
    { (yyval.Char) = '\303'; }
    break;

  case 388:
#line 462 "lscp.y"
    { (yyval.Char) = '\304'; }
    break;

  case 389:
#line 463 "lscp.y"
    { (yyval.Char) = '\305'; }
    break;

  case 390:
#line 463 "lscp.y"
    { (yyval.Char) = '\306'; }
    break;

  case 391:
#line 463 "lscp.y"
    { (yyval.Char) = '\307'; }
    break;

  case 392:
#line 464 "lscp.y"
    { (yyval.Char) = '\310'; }
    break;

  case 393:
#line 464 "lscp.y"
    { (yyval.Char) = '\311'; }
    break;

  case 394:
#line 464 "lscp.y"
    { (yyval.Char) = '\312'; }
    break;

  case 395:
#line 465 "lscp.y"
    { (yyval.Char) = '\313'; }
    break;

  case 396:
#line 465 "lscp.y"
    { (yyval.Char) = '\314'; }
    break;

  case 397:
#line 465 "lscp.y"
    { (yyval.Char) = '\315'; }
    break;

  case 398:
#line 466 "lscp.y"
    { (yyval.Char) = '\316'; }
    break;

  case 399:
#line 466 "lscp.y"
    { (yyval.Char) = '\317'; }
    break;

  case 400:
#line 466 "lscp.y"
    { (yyval.Char) = '\320'; }
    break;

  case 401:
#line 467 "lscp.y"
    { (yyval.Char) = '\321'; }
    break;

  case 402:
#line 467 "lscp.y"
    { (yyval.Char) = '\322'; }
    break;

  case 403:
#line 467 "lscp.y"
    { (yyval.Char) = '\323'; }
    break;

  case 404:
#line 468 "lscp.y"
    { (yyval.Char) = '\324'; }
    break;

  case 405:
#line 468 "lscp.y"
    { (yyval.Char) = '\325'; }
    break;

  case 406:
#line 468 "lscp.y"
    { (yyval.Char) = '\326'; }
    break;

  case 407:
#line 469 "lscp.y"
    { (yyval.Char) = '\327'; }
    break;

  case 408:
#line 469 "lscp.y"
    { (yyval.Char) = '\330'; }
    break;

  case 409:
#line 469 "lscp.y"
    { (yyval.Char) = '\331'; }
    break;

  case 410:
#line 470 "lscp.y"
    { (yyval.Char) = '\332'; }
    break;

  case 411:
#line 470 "lscp.y"
    { (yyval.Char) = '\333'; }
    break;

  case 412:
#line 470 "lscp.y"
    { (yyval.Char) = '\334'; }
    break;

  case 413:
#line 471 "lscp.y"
    { (yyval.Char) = '\335'; }
    break;

  case 414:
#line 471 "lscp.y"
    { (yyval.Char) = '\336'; }
    break;

  case 415:
#line 471 "lscp.y"
    { (yyval.Char) = '\337'; }
    break;

  case 416:
#line 472 "lscp.y"
    { (yyval.Char) = '\340'; }
    break;

  case 417:
#line 472 "lscp.y"
    { (yyval.Char) = '\341'; }
    break;

  case 418:
#line 472 "lscp.y"
    { (yyval.Char) = '\342'; }
    break;

  case 419:
#line 473 "lscp.y"
    { (yyval.Char) = '\343'; }
    break;

  case 420:
#line 473 "lscp.y"
    { (yyval.Char) = '\344'; }
    break;

  case 421:
#line 473 "lscp.y"
    { (yyval.Char) = '\345'; }
    break;

  case 422:
#line 474 "lscp.y"
    { (yyval.Char) = '\346'; }
    break;

  case 423:
#line 474 "lscp.y"
    { (yyval.Char) = '\347'; }
    break;

  case 424:
#line 474 "lscp.y"
    { (yyval.Char) = '\350'; }
    break;

  case 425:
#line 475 "lscp.y"
    { (yyval.Char) = '\351'; }
    break;

  case 426:
#line 475 "lscp.y"
    { (yyval.Char) = '\352'; }
    break;

  case 427:
#line 475 "lscp.y"
    { (yyval.Char) = '\353'; }
    break;

  case 428:
#line 476 "lscp.y"
    { (yyval.Char) = '\354'; }
    break;

  case 429:
#line 476 "lscp.y"
    { (yyval.Char) = '\355'; }
    break;

  case 430:
#line 476 "lscp.y"
    { (yyval.Char) = '\356'; }
    break;

  case 431:
#line 477 "lscp.y"
    { (yyval.Char) = '\357'; }
    break;

  case 432:
#line 477 "lscp.y"
    { (yyval.Char) = '\360'; }
    break;

  case 433:
#line 477 "lscp.y"
    { (yyval.Char) = '\361'; }
    break;

  case 434:
#line 478 "lscp.y"
    { (yyval.Char) = '\362'; }
    break;

  case 435:
#line 478 "lscp.y"
    { (yyval.Char) = '\363'; }
    break;

  case 436:
#line 478 "lscp.y"
    { (yyval.Char) = '\364'; }
    break;

  case 437:
#line 479 "lscp.y"
    { (yyval.Char) = '\365'; }
    break;

  case 438:
#line 479 "lscp.y"
    { (yyval.Char) = '\366'; }
    break;

  case 439:
#line 479 "lscp.y"
    { (yyval.Char) = '\367'; }
    break;

  case 440:
#line 480 "lscp.y"
    { (yyval.Char) = '\370'; }
    break;

  case 441:
#line 480 "lscp.y"
    { (yyval.Char) = '\371'; }
    break;

  case 442:
#line 480 "lscp.y"
    { (yyval.Char) = '\372'; }
    break;

  case 443:
#line 481 "lscp.y"
    { (yyval.Char) = '\373'; }
    break;

  case 444:
#line 481 "lscp.y"
    { (yyval.Char) = '\374'; }
    break;

  case 445:
#line 481 "lscp.y"
    { (yyval.Char) = '\375'; }
    break;

  case 446:
#line 482 "lscp.y"
    { (yyval.Char) = '\376'; }
    break;

  case 447:
#line 482 "lscp.y"
    { (yyval.Char) = '\377'; }
    break;

  case 448:
#line 485 "lscp.y"
    { (yyval.String) = " ";      }
    break;

  case 450:
#line 487 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + " "; }
    break;

  case 451:
#line 488 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + (yyvsp[(2) - (2)].String);  }
    break;

  case 452:
#line 491 "lscp.y"
    { (yyval.String) = (yyvsp[(2) - (3)].String); }
    break;

  case 453:
#line 492 "lscp.y"
    { (yyval.String) = (yyvsp[(2) - (3)].String); }
    break;


/* Line 1267 of yacc.c.  */
#line 5437 "y.tab.c"
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


#line 759 "lscp.y"


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

