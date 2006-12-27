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
#define YYLAST   4355

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  227
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  137
/* YYNRULES -- Number of rules.  */
#define YYNRULES  522
/* YYNRULES -- Number of states.  */
#define YYNSTATES  1630

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
     421,   423,   429,   433,   441,   449,   459,   467,   477,   481,
     489,   501,   505,   511,   515,   521,   525,   531,   539,   543,
     547,   551,   555,   559,   565,   569,   573,   579,   587,   593,
     603,   609,   615,   621,   627,   633,   639,   645,   651,   657,
     663,   667,   673,   675,   677,   679,   681,   683,   685,   687,
     689,   693,   697,   699,   703,   709,   717,   721,   723,   725,
     727,   729,   731,   733,   735,   737,   739,   741,   743,   745,
     747,   749,   751,   753,   755,   757,   759,   761,   763,   765,
     767,   769,   771,   775,   777,   779,   781,   783,   785,   787,
     789,   792,   796,   801,   806,   808,   811,   813,   815,   817,
     819,   821,   823,   825,   827,   829,   831,   833,   836,   839,
     842,   845,   848,   851,   854,   857,   860,   862,   864,   866,
     868,   870,   872,   874,   876,   878,   880,   882,   884,   886,
     888,   890,   892,   894,   896,   898,   900,   902,   904,   906,
     908,   910,   912,   914,   916,   918,   920,   922,   924,   926,
     928,   930,   932,   934,   936,   938,   940,   942,   944,   946,
     948,   950,   952,   954,   956,   958,   960,   962,   964,   966,
     968,   970,   972,   974,   976,   978,   980,   982,   984,   986,
     988,   990,   992,   994,   996,   998,  1000,  1002,  1004,  1006,
    1008,  1010,  1012,  1014,  1016,  1018,  1020,  1022,  1024,  1026,
    1028,  1030,  1032,  1034,  1036,  1038,  1040,  1042,  1044,  1046,
    1048,  1050,  1052,  1054,  1056,  1058,  1060,  1062,  1064,  1066,
    1068,  1070,  1072,  1074,  1076,  1078,  1080,  1082,  1084,  1086,
    1088,  1090,  1092,  1094,  1096,  1098,  1100,  1102,  1104,  1106,
    1108,  1110,  1112,  1114,  1116,  1118,  1120,  1122,  1124,  1126,
    1128,  1130,  1132,  1134,  1136,  1138,  1140,  1142,  1144,  1146,
    1148,  1150,  1152,  1154,  1156,  1158,  1160,  1162,  1164,  1166,
    1168,  1170,  1172,  1174,  1176,  1178,  1180,  1182,  1184,  1186,
    1188,  1190,  1192,  1194,  1196,  1198,  1200,  1202,  1204,  1206,
    1208,  1210,  1212,  1214,  1216,  1218,  1220,  1222,  1224,  1226,
    1228,  1230,  1232,  1234,  1236,  1238,  1240,  1242,  1244,  1246,
    1248,  1250,  1252,  1254,  1256,  1258,  1260,  1262,  1264,  1266,
    1268,  1270,  1272,  1274,  1276,  1278,  1280,  1282,  1284,  1286,
    1288,  1290,  1292,  1294,  1296,  1298,  1300,  1302,  1305,  1308,
    1312,  1316,  1318,  1320,  1322,  1326,  1330,  1334,  1340,  1346,
    1353,  1361,  1366,  1371,  1375,  1380,  1388,  1398,  1405,  1409,
    1419,  1431,  1438,  1446,  1464,  1495,  1504,  1509,  1535,  1560,
    1584,  1607,  1633,  1658,  1680,  1701,  1715,  1728,  1740,  1753,
    1765,  1783,  1805,  1816,  1823,  1833,  1848,  1859,  1889,  1910,
    1930,  1960,  1980,  2011,  2032,  2050,  2079,  2107,  2133,  2152,
    2170,  2198,  2214,  2231,  2251,  2272,  2290,  2306,  2325,  2341,
    2352,  2360,  2369,  2376,  2383,  2388,  2393,  2399,  2410,  2416,
    2430,  2435,  2440
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
     282,   280,    -1,   359,   282,   241,    -1,   289,   282,   242,
      -1,   359,    -1,   363,    -1,   303,    -1,   344,    -1,   344,
     282,   268,    -1,   308,    -1,   309,    -1,   310,    -1,   311,
      -1,   316,    -1,   320,    -1,   319,    -1,   318,    -1,   317,
      -1,   312,    -1,   313,    -1,   314,    -1,   315,    -1,   360,
      -1,   321,    -1,   308,    -1,   309,    -1,   310,    -1,   311,
      -1,   316,    -1,   320,    -1,   319,    -1,   318,    -1,   317,
      -1,   312,    -1,   313,    -1,   314,    -1,   315,    -1,   360,
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
     282,   307,   282,   266,    -1,   353,   282,   307,    -1,   321,
      -1,   322,    -1,   343,   282,   258,    -1,   343,   282,   294,
      -1,   342,   282,   307,   282,   258,   282,   259,   282,   260,
      -1,   345,    -1,   344,   282,   307,   282,   258,    -1,   352,
     282,   263,    -1,   351,   282,   307,   282,   263,   282,   265,
      -1,   328,   282,   278,   282,   274,     4,   271,    -1,   333,
     282,   278,   282,   278,   282,   274,     4,   271,    -1,   337,
     282,   278,   282,   274,     4,   271,    -1,   338,   282,   278,
     282,   278,   282,   274,     4,   271,    -1,   303,   282,   245,
      -1,   344,   282,   361,   282,   258,   282,   268,    -1,   351,
     282,   334,   282,   263,   282,   265,   282,   253,   282,   253,
      -1,   362,   282,   273,    -1,   330,   282,   274,   282,   246,
      -1,   330,   282,   274,    -1,   340,   282,   274,   282,   246,
      -1,   340,   282,   274,    -1,   351,   282,   263,   282,   261,
      -1,   351,   282,   263,   282,   261,   282,   270,    -1,   303,
     282,   263,    -1,   343,   282,   258,    -1,   343,   282,   294,
      -1,   330,   282,   278,    -1,   340,   282,   278,    -1,   351,
     282,   263,   282,   265,    -1,   323,   282,   249,    -1,   324,
     282,   250,    -1,   330,   282,   263,   282,   252,    -1,   334,
     282,   263,   282,   253,   282,   253,    -1,   335,   282,   263,
     282,   254,    -1,   350,   282,   263,   282,   252,   282,   255,
     282,   256,    -1,   340,   282,   263,   282,   252,    -1,   347,
     282,   263,   282,   255,    -1,   348,   282,   263,   282,   256,
      -1,   349,   282,   263,   282,   257,    -1,   354,   282,   263,
     282,   262,    -1,   355,   282,   263,   282,   273,    -1,   356,
     282,   263,   282,   273,    -1,   344,   282,   263,   282,   258,
      -1,   344,   282,   263,   282,   295,    -1,   344,   282,   263,
     282,   296,    -1,   274,     4,   271,    -1,   246,   282,   274,
       4,   271,    -1,   357,    -1,   358,    -1,   329,    -1,   339,
      -1,   306,    -1,   304,    -1,   336,    -1,   305,    -1,   343,
     282,   258,    -1,   343,   282,   294,    -1,   345,    -1,   352,
     282,   263,    -1,   267,   282,   264,   282,   263,    -1,   297,
     282,   267,   282,   264,   282,   263,    -1,   266,   282,   263,
      -1,   325,    -1,   326,    -1,   327,    -1,   278,    -1,   278,
      -1,   274,    -1,   278,    -1,   278,    -1,   294,    -1,   274,
      -1,   278,    -1,   278,    -1,   278,    -1,   278,    -1,   275,
      -1,   278,    -1,   278,    -1,   278,    -1,   278,    -1,   274,
      -1,   281,    -1,   281,    -1,   281,    -1,   281,    -1,   272,
      -1,   271,     5,   272,    -1,   274,    -1,   281,    -1,   278,
      -1,   275,    -1,   278,    -1,   274,    -1,   279,    -1,   274,
     279,    -1,   276,     6,   276,    -1,     7,   276,     6,   276,
      -1,     8,   276,     6,   276,    -1,   277,    -1,   276,   277,
      -1,     9,    -1,    10,    -1,    11,    -1,    12,    -1,    13,
      -1,    14,    -1,    15,    -1,    16,    -1,    17,    -1,    18,
      -1,   277,    -1,    10,   276,    -1,    11,   276,    -1,    12,
     276,    -1,    13,   276,    -1,    14,   276,    -1,    15,   276,
      -1,    16,   276,    -1,    17,   276,    -1,    18,   276,    -1,
      19,    -1,    20,    -1,    21,    -1,    22,    -1,    23,    -1,
      24,    -1,    25,    -1,    26,    -1,    27,    -1,    28,    -1,
      29,    -1,    30,    -1,    31,    -1,    32,    -1,    33,    -1,
      34,    -1,    35,    -1,    36,    -1,    37,    -1,    38,    -1,
      39,    -1,    40,    -1,    41,    -1,    42,    -1,    43,    -1,
      44,    -1,    45,    -1,    46,    -1,    47,    -1,    48,    -1,
      49,    -1,    50,    -1,    51,    -1,    52,    -1,    53,    -1,
      54,    -1,    55,    -1,    56,    -1,    57,    -1,    58,    -1,
      59,    -1,    60,    -1,    61,    -1,    62,    -1,    63,    -1,
      64,    -1,    65,    -1,    66,    -1,    67,    -1,    68,    -1,
      69,    -1,    70,    -1,     9,    -1,    10,    -1,    11,    -1,
      12,    -1,    13,    -1,    14,    -1,    15,    -1,    16,    -1,
      17,    -1,    18,    -1,    71,    -1,     3,    -1,    72,    -1,
      73,    -1,    74,    -1,    75,    -1,    76,    -1,    77,    -1,
       7,    -1,     8,    -1,     6,    -1,     5,    -1,    78,    -1,
      79,    -1,    80,    -1,    81,    -1,     4,    -1,    82,    -1,
      83,    -1,    84,    -1,    85,    -1,    86,    -1,    87,    -1,
      88,    -1,    89,    -1,    90,    -1,    91,    -1,    92,    -1,
      93,    -1,    94,    -1,    95,    -1,    96,    -1,    97,    -1,
      98,    -1,    99,    -1,   100,    -1,   101,    -1,   102,    -1,
     103,    -1,   104,    -1,   105,    -1,   106,    -1,   107,    -1,
     108,    -1,   109,    -1,   110,    -1,   111,    -1,   112,    -1,
     113,    -1,   114,    -1,   115,    -1,   116,    -1,   117,    -1,
     118,    -1,   119,    -1,   120,    -1,   121,    -1,   122,    -1,
     123,    -1,   124,    -1,   125,    -1,   126,    -1,   127,    -1,
     128,    -1,   129,    -1,   130,    -1,   131,    -1,   132,    -1,
     133,    -1,   134,    -1,   135,    -1,   136,    -1,   137,    -1,
     138,    -1,   139,    -1,   140,    -1,   141,    -1,   142,    -1,
     143,    -1,   144,    -1,   145,    -1,   146,    -1,   147,    -1,
     148,    -1,   149,    -1,   150,    -1,   151,    -1,   152,    -1,
     153,    -1,   154,    -1,   155,    -1,   156,    -1,   157,    -1,
     158,    -1,   159,    -1,   160,    -1,   161,    -1,   162,    -1,
     163,    -1,   164,    -1,   165,    -1,   166,    -1,   167,    -1,
     168,    -1,   169,    -1,   170,    -1,   171,    -1,   172,    -1,
     173,    -1,   174,    -1,   175,    -1,   176,    -1,   177,    -1,
     178,    -1,   179,    -1,   180,    -1,   181,    -1,   182,    -1,
     183,    -1,   184,    -1,   185,    -1,   186,    -1,   187,    -1,
     188,    -1,   189,    -1,   190,    -1,   191,    -1,   192,    -1,
     193,    -1,   194,    -1,   195,    -1,   196,    -1,   197,    -1,
     198,    -1,   199,    -1,   200,    -1,   201,    -1,   202,    -1,
     203,    -1,   204,    -1,   205,    -1,   206,    -1,   207,    -1,
     208,    -1,   209,    -1,   210,    -1,   211,    -1,   212,    -1,
     213,    -1,   214,    -1,   215,    -1,   216,    -1,   217,    -1,
     218,    -1,   219,    -1,   220,    -1,   221,    -1,   282,    -1,
     274,    -1,   280,   282,    -1,   280,   274,    -1,   222,   280,
     222,    -1,   223,   280,   223,    -1,   224,    -1,   225,    -1,
     226,    -1,    19,    22,    22,    -1,    25,    23,    38,    -1,
      31,    19,    34,    -1,    39,    32,    31,    19,    34,    -1,
      21,    30,    23,    19,    36,    -1,    21,    36,    23,    19,
      38,    23,    -1,    22,    23,    37,    38,    36,    33,    43,
      -1,    30,    27,    37,    38,    -1,    30,    33,    19,    22,
      -1,    19,    30,    30,    -1,    32,    33,    32,    23,    -1,
      22,    23,    24,    19,    39,    30,    38,    -1,    32,    33,
      32,    89,    31,    33,    22,    19,    30,    -1,    36,    23,
      31,    33,    40,    23,    -1,    37,    23,    38,    -1,    37,
      39,    20,    37,    21,    36,    27,    20,    23,    -1,    39,
      32,    37,    39,    20,    37,    21,    36,    27,    20,    23,
      -1,    37,    23,    30,    23,    21,    38,    -1,    21,    26,
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
      -1,    21,    26,    19,    32,    32,    23,    30,    89,    21,
      33,    39,    32,    38,    -1,    21,    26,    19,    32,    32,
      23,    30,    89,    27,    32,    24,    33,    -1,    20,    39,
      24,    24,    23,    36,    89,    24,    27,    30,    30,    -1,
      37,    38,    36,    23,    19,    31,    89,    21,    33,    39,
      32,    38,    -1,    40,    33,    27,    21,    23,    89,    21,
      33,    39,    32,    38,    -1,    38,    33,    38,    19,    30,
      89,    40,    33,    27,    21,    23,    89,    21,    33,    39,
      32,    38,    -1,    38,    33,    38,    19,    30,    89,    40,
      33,    27,    21,    23,    89,    21,    33,    39,    32,    38,
      89,    31,    19,    42,    -1,    27,    32,    37,    38,    36,
      39,    31,    23,    32,    38,    -1,    23,    32,    25,    27,
      32,    23,    -1,    33,    32,    89,    22,    23,    31,    19,
      32,    22,    -1,    33,    32,    89,    22,    23,    31,    19,
      32,    22,    89,    26,    33,    30,    22,    -1,    34,    23,
      36,    37,    27,    37,    38,    23,    32,    38,    -1,    19,
      39,    22,    27,    33,    89,    33,    39,    38,    34,    39,
      38,    89,    22,    23,    40,    27,    21,    23,    89,    34,
      19,    36,    19,    31,    23,    38,    23,    36,    -1,    19,
      39,    22,    27,    33,    89,    33,    39,    38,    34,    39,
      38,    89,    22,    23,    40,    27,    21,    23,    37,    -1,
      19,    39,    22,    27,    33,    89,    33,    39,    38,    34,
      39,    38,    89,    22,    23,    40,    27,    21,    23,    -1,
      19,    39,    22,    27,    33,    89,    33,    39,    38,    34,
      39,    38,    89,    22,    36,    27,    40,    23,    36,    89,
      34,    19,    36,    19,    31,    23,    38,    23,    36,    -1,
      19,    39,    22,    27,    33,    89,    33,    39,    38,    34,
      39,    38,    89,    22,    36,    27,    40,    23,    36,    -1,
      19,    39,    22,    27,    33,    89,    33,    39,    38,    34,
      39,    38,    89,    21,    26,    19,    32,    32,    23,    30,
      89,    34,    19,    36,    19,    31,    23,    38,    23,    36,
      -1,    19,    39,    22,    27,    33,    89,    33,    39,    38,
      34,    39,    38,    89,    21,    26,    19,    32,    32,    23,
      30,    -1,    19,    39,    22,    27,    33,    89,    33,    39,
      38,    34,    39,    38,    89,    38,    43,    34,    23,    -1,
      19,    40,    19,    27,    30,    19,    20,    30,    23,    89,
      31,    27,    22,    27,    89,    27,    32,    34,    39,    38,
      89,    22,    36,    27,    40,    23,    36,    37,    -1,    31,
      27,    22,    27,    89,    27,    32,    34,    39,    38,    89,
      22,    23,    40,    27,    21,    23,    89,    34,    19,    36,
      19,    31,    23,    38,    23,    36,    -1,    31,    27,    22,
      27,    89,    27,    32,    34,    39,    38,    89,    34,    33,
      36,    38,    89,    34,    19,    36,    19,    31,    23,    38,
      23,    36,    -1,    31,    27,    22,    27,    89,    27,    32,
      34,    39,    38,    89,    22,    23,    40,    27,    21,    23,
      37,    -1,    31,    27,    22,    27,    89,    27,    32,    34,
      39,    38,    89,    22,    23,    40,    27,    21,    23,    -1,
      31,    27,    22,    27,    89,    27,    32,    34,    39,    38,
      89,    22,    36,    27,    40,    23,    36,    89,    34,    19,
      36,    19,    31,    23,    38,    23,    36,    -1,    31,    27,
      22,    27,    89,    27,    32,    37,    38,    36,    39,    31,
      23,    32,    38,    -1,    31,    27,    22,    27,    89,    27,
      32,    37,    38,    36,    39,    31,    23,    32,    38,    37,
      -1,    31,    27,    22,    27,    89,    27,    32,    37,    38,
      36,    39,    31,    23,    32,    38,    89,    31,    19,    34,
      -1,    31,    27,    22,    27,    89,    27,    32,    37,    38,
      36,    39,    31,    23,    32,    38,    89,    31,    19,    34,
      37,    -1,    31,    27,    22,    27,    89,    27,    32,    34,
      39,    38,    89,    22,    36,    27,    40,    23,    36,    -1,
      31,    27,    22,    27,    89,    27,    32,    34,    39,    38,
      89,    34,    33,    36,    38,    -1,    31,    27,    22,    27,
      89,    27,    32,    34,    39,    38,    89,    21,    26,    19,
      32,    32,    23,    30,    -1,    31,    27,    22,    27,    89,
      27,    32,    34,    39,    38,    89,    38,    43,    34,    23,
      -1,    31,    27,    22,    27,    89,    27,    32,    34,    39,
      38,    -1,    24,    42,    89,    37,    23,    32,    22,    -1,
      24,    42,    89,    37,    23,    32,    22,    37,    -1,    37,
      23,    36,    40,    23,    36,    -1,    40,    33,    30,    39,
      31,    23,    -1,    31,    39,    38,    23,    -1,    37,    33,
      30,    33,    -1,    20,    43,    38,    23,    37,    -1,    34,
      23,    36,    21,    23,    32,    38,    19,    25,    23,    -1,
      36,    23,    37,    23,    38,    -1,    31,    27,    37,    21,
      23,    30,    30,    19,    32,    23,    33,    39,    37,    -1,
      32,    19,    31,    23,    -1,    23,    21,    26,    33,    -1,
      35,    39,    27,    38,    -1
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
     214,   215,   216,   217,   220,   221,   222,   223,   224,   225,
     226,   227,   230,   231,   232,   233,   234,   235,   238,   241,
     242,   245,   246,   247,   250,   251,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     270,   271,   274,   275,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   290,   291,   294,   297,   298,   299,
     302,   305,   308,   311,   314,   315,   318,   321,   324,   327,
     330,   333,   334,   337,   340,   343,   346,   349,   352,   355,
     358,   361,   362,   365,   366,   367,   368,   376,   377,   380,
     381,   384,   385,   386,   390,   391,   394,   395,   396,   397,
     398,   399,   400,   401,   402,   403,   406,   407,   408,   409,
     410,   411,   412,   413,   414,   415,   417,   417,   417,   417,
     417,   417,   417,   417,   417,   417,   417,   417,   417,   417,
     417,   417,   417,   417,   417,   417,   417,   417,   417,   417,
     417,   417,   418,   418,   418,   418,   418,   418,   418,   418,
     418,   418,   418,   418,   418,   418,   418,   418,   418,   418,
     418,   418,   418,   418,   418,   418,   418,   418,   419,   419,
     419,   419,   419,   419,   419,   419,   419,   419,   420,   420,
     420,   420,   420,   420,   420,   420,   420,   420,   420,   420,
     420,   421,   421,   421,   421,   421,   421,   421,   422,   422,
     422,   422,   422,   423,   423,   423,   423,   424,   424,   424,
     425,   425,   425,   426,   426,   426,   427,   427,   427,   428,
     428,   428,   429,   429,   429,   430,   430,   430,   431,   431,
     431,   432,   432,   432,   433,   433,   433,   434,   434,   434,
     435,   435,   435,   436,   436,   436,   437,   437,   437,   438,
     438,   438,   439,   439,   439,   440,   440,   440,   441,   441,
     441,   442,   442,   442,   443,   443,   443,   444,   444,   444,
     445,   445,   445,   446,   446,   446,   447,   447,   447,   448,
     448,   448,   449,   449,   449,   450,   450,   450,   451,   451,
     451,   452,   452,   452,   453,   453,   453,   454,   454,   454,
     455,   455,   455,   456,   456,   456,   457,   457,   457,   458,
     458,   458,   459,   459,   459,   460,   460,   460,   461,   461,
     461,   462,   462,   462,   463,   463,   463,   464,   464,   464,
     465,   465,   465,   466,   466,   469,   470,   471,   472,   475,
     476,   482,   485,   488,   491,   494,   497,   500,   503,   506,
     509,   512,   515,   518,   521,   524,   527,   530,   533,   536,
     539,   542,   545,   548,   551,   554,   557,   560,   563,   566,
     569,   572,   575,   578,   581,   584,   587,   590,   593,   596,
     599,   602,   605,   608,   611,   614,   617,   620,   623,   626,
     629,   632,   635,   638,   641,   644,   647,   650,   653,   656,
     659,   662,   665,   668,   671,   674,   677,   680,   683,   686,
     689,   692,   695,   698,   701,   704,   707,   710,   713,   716,
     719,   722,   725
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
  "set_chan_instruction", "key_val_list", "buffer_size_type",
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
  "MIDI_INPUT_CHANNEL", "MIDI_INPUT_TYPE", "MIDI_INPUT", "FX_SEND",
  "FX_SENDS", "SERVER", "VOLUME", "MUTE", "SOLO", "BYTES", "PERCENTAGE",
  "RESET", "MISCELLANEOUS", "NAME", "ECHO", "QUIT", 0
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
     238,   238,   238,   238,   239,   239,   239,   239,   239,   239,
     239,   239,   240,   240,   240,   240,   240,   240,   241,   242,
     242,   243,   243,   243,   244,   244,   245,   245,   245,   245,
     245,   245,   245,   245,   245,   245,   245,   245,   245,   245,
     246,   246,   247,   247,   248,   248,   248,   248,   248,   248,
     248,   248,   248,   248,   249,   249,   250,   251,   251,   251,
     252,   253,   254,   255,   256,   256,   257,   258,   259,   260,
     261,   262,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   271,   272,   272,   272,   272,   273,   273,   274,
     274,   275,   275,   275,   276,   276,   277,   277,   277,   277,
     277,   277,   277,   277,   277,   277,   278,   278,   278,   278,
     278,   278,   278,   278,   278,   278,   279,   279,   279,   279,
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
     279,   279,   279,   279,   279,   280,   280,   280,   280,   281,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   324,   325,   326,   327,   328,   329,   330,
     331,   332,   333,   334,   335,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,   353,   354,   355,   356,   357,   358,   359,   360,
     361,   362,   363
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
       1,     5,     3,     7,     7,     9,     7,     9,     3,     7,
      11,     3,     5,     3,     5,     3,     5,     7,     3,     3,
       3,     3,     3,     5,     3,     3,     5,     7,     5,     9,
       5,     5,     5,     5,     5,     5,     5,     5,     5,     5,
       3,     5,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     1,     3,     5,     7,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       2,     3,     4,     4,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     1,     1,     1,
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
       1,     1,     1,     1,     1,     1,     1,     2,     2,     3,
       3,     1,     1,     1,     3,     3,     3,     5,     5,     6,
       7,     4,     4,     3,     4,     7,     9,     6,     3,     9,
      11,     6,     7,    17,    30,     8,     4,    25,    24,    23,
      22,    25,    24,    21,    20,    13,    12,    11,    12,    11,
      17,    21,    10,     6,     9,    14,    10,    29,    20,    19,
      29,    19,    30,    20,    17,    28,    27,    25,    18,    17,
      27,    15,    16,    19,    20,    17,    15,    18,    15,    10,
       7,     8,     6,     6,     4,     4,     5,    10,     5,    13,
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
       0,     0,     0,     0,     0,     0,     1,   442,   443,     2,
       0,     9,   294,   289,   288,   286,   287,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   278,
     280,   281,   282,   283,   284,   285,   290,   291,   292,   293,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     441,    12,   206,    11,   189,    10,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   444,     0,     0,     0,   445,     0,     0,   446,     0,
       0,     0,     0,   458,     0,     0,     0,     3,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   207,   194,
     208,   209,   210,   211,   212,   213,   214,   215,   279,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   190,
       0,     0,    13,    30,    31,     0,     0,     0,     0,     0,
       0,     0,    16,     0,    71,    76,    88,    95,    96,     0,
      80,     0,     0,     0,     0,     0,    72,     0,    81,     0,
       0,     0,     0,     0,   100,     0,     0,     0,     0,     0,
       0,    14,     0,    15,     0,     0,    27,     0,     0,     0,
       0,    17,     0,     0,     0,    18,     0,     0,     0,     0,
       0,     0,     0,    19,   147,   149,   146,   144,   148,   145,
       0,   152,     0,     0,    20,     0,     0,    21,     0,     0,
       0,     0,     0,    22,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    23,
      33,    34,    35,    36,    42,    43,    44,    45,    37,    41,
      40,    39,    38,    47,    46,    24,    48,    49,    50,    51,
      57,    58,    59,    60,    52,    56,    55,    54,    53,    62,
      61,   436,    25,   435,    26,     0,     0,     0,     0,   451,
     452,   522,     0,     0,     0,     0,     0,     0,   195,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   438,   437,     0,   448,     0,     0,     0,   518,     0,
       0,   447,     0,     0,     0,     0,     0,    32,   178,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   197,   198,   199,   200,   201,   202,   203,   204,
     205,     0,    97,   167,    98,     0,     0,     0,     0,   102,
     173,    94,     0,     0,     0,     0,   119,   120,     0,     0,
       0,   113,   115,     0,   121,   122,     0,     0,     0,     0,
       0,   150,   151,   153,     0,     0,   124,     0,   177,     0,
     125,     0,   176,    68,    69,    70,     0,     0,     0,     0,
       0,     0,     0,   108,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   111,   188,   187,     0,     0,     0,
       0,     0,     0,     0,     0,   118,   449,     0,   457,   461,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   521,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     450,     0,     0,     0,     0,   439,   440,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    89,     0,     0,     0,
     142,   143,    91,    92,    93,    82,     0,    77,     0,     0,
       0,    83,     0,     0,   453,   101,    73,     0,     0,     0,
       0,   168,     0,     0,     0,     0,     0,   112,     0,   114,
     116,   170,   123,   175,     0,     0,     0,     0,     0,     0,
       0,   174,     0,   156,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   483,     0,     0,   512,
       0,   466,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   514,   515,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   520,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   459,     0,   462,     0,
       0,     0,   462,   510,     0,     0,     0,     0,    90,    78,
       0,    86,     0,    74,     0,    84,   103,     0,     0,   169,
      67,     0,     0,   510,     0,     0,   286,   287,   140,   181,
     183,   186,     0,   194,   185,   184,   117,   180,     0,     0,
       0,     0,     0,     0,   154,     0,     0,     0,     0,     0,
       0,   126,   160,     0,   161,   128,   162,   130,     0,     0,
     137,   138,   139,   131,   163,   132,   164,   165,   133,   166,
       0,     0,     0,   134,   171,   172,   135,   136,   104,     0,
     106,     0,   109,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   465,   511,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   513,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   460,     0,     0,
       0,     0,     0,     0,   516,     0,    79,    87,    85,    75,
      99,     0,     0,     0,     0,     0,   141,     0,     0,   182,
     191,     0,     0,     0,     0,     0,   155,     0,     0,     0,
       0,   127,     0,     0,     0,   105,   107,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   192,   193,     0,     0,     0,   482,     0,     0,     0,
       0,     0,     0,   454,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   456,     0,     0,     0,     0,     0,
     129,     0,   110,     0,   477,     0,     0,     0,     0,     0,
       0,     0,   479,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   509,     0,     0,     0,     0,
     476,     0,     0,     0,   478,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     455,     0,     0,   475,     0,     0,   519,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   517,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     506,   501,     0,   501,    63,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   502,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     463,     0,   499,   505,     0,     0,   480,     0,     0,    64,
      65,   179,   157,   158,   159,     0,   499,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   506,   508,     0,     0,
       0,     0,     0,   480,     0,     0,     0,     0,     0,     0,
     498,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   503,     0,   489,   491,     0,     0,     0,     0,
     503,     0,     0,     0,    66,   489,     0,     0,     0,     0,
       0,     0,   494,     0,     0,     0,     0,     0,     0,     0,
     493,   488,     0,     0,     0,     0,     0,   504,     0,     0,
       0,     0,     0,     0,     0,   507,     0,     0,     0,     0,
     474,     0,     0,     0,     0,     0,     0,     0,   481,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   473,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   493,     0,     0,     0,   470,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     469,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   468,     0,   472,     0,     0,     0,
       0,     0,   497,   484,     0,     0,     0,   467,   471,     0,
       0,     0,     0,     0,     0,   486,     0,     0,     0,     0,
       0,     0,   500,     0,     0,   496,     0,     0,     0,   495,
       0,     0,     0,   490,     0,     0,   487,   492,   464,   485
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    13,    14,    15,    16,   342,   439,   455,   381,   383,
     417,   352,   423,   391,   474,   386,   395,   414,   663,   837,
     809,   403,   646,   650,  1419,  1021,  1023,  1025,  1033,  1035,
    1038,   612,   830,   988,   840,  1043,   619,   850,   842,   651,
     647,   577,  1420,  1006,   998,   999,   684,  1000,  1001,  1002,
     272,   620,   274,   472,  1005,   920,    49,    50,    17,    18,
      19,    20,    21,    22,    23,    24,    25,  1037,  1031,  1032,
     649,    26,    27,    28,    29,    30,   343,   354,   355,   356,
     588,   440,   441,   442,   443,   444,   445,   446,   447,   448,
     449,   450,   451,   452,   357,   358,   415,   359,  1422,  1423,
    1424,   425,   360,   361,   362,   363,   364,   365,   666,   366,
     427,   367,   368,   369,   370,   371,   372,   344,   374,   375,
     376,   670,   671,   672,   377,   378,   379,   673,   674,   675,
     810,   811,    31,   454,   681,   431,    32
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -1046
static const yytype_int16 yypact[] =
{
      50, -1046, -1046,    51,    66,    54,    76,   200,   129,   111,
     152,    45,   182,   177,   -95,  1932, -1046,    23,    23,    23,
      23,    23,    23,    23,    23,    23,    23,    23,    23,    23,
      23,    23, -1046,   272,   255,   276,   218,   273,   291,   311,
     299,   307,   204,   142,   315,   208, -1046, -1046, -1046, -1046,
     114, -1046, -1046, -1046, -1046, -1046, -1046, -1046,   578,   578,
     578,   578,   578,   578,   578,   578,   578, -1046, -1046, -1046,
   -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046,
   -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046,
   -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046,
   -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046,
   -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046,
   -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046,
   -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046,
   -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046,
   -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046,
   -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046,
   -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046,
   -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046,
   -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046,
   -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046,
   -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046,
   -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046,
   -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046,
   -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046,
   -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046,
   -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046,
   -1046,  2597, -1046, -1046, -1046, -1046,   181,   116,   305,   305,
     306,   207,   207,   199,    47,   181,   198,   105,   105,  2154,
     319, -1046,   322,   323,   313, -1046,   321,   331, -1046,   332,
     310,   348,   350, -1046,   308,   355,   336, -1046, -1046, -1046,
   -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046,   578, -1046,
     578,   578,   578,   578,   578,   578,   578,   578, -1046, -1046,
   -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046,
     354,   349, -1046, -1046,    23,   159,   358,   353,   344,   360,
     365,   356, -1046,    23, -1046, -1046, -1046, -1046, -1046,    23,
   -1046,    23,    23,    23,    23,    23, -1046,    23, -1046,    23,
      23,    23,    23,    23, -1046,    23,    23,    23,    23,    23,
     364, -1046,    23, -1046,    23,   366, -1046,    23,   357,   352,
     371, -1046,    23,    23,    23, -1046,    23,    23,    23,   258,
     373,   363,   379, -1046, -1046, -1046, -1046, -1046, -1046, -1046,
      23, -1046,    23,   375, -1046,    23,    23, -1046,    23,    23,
     369,   396,   391, -1046,    23,    23,    23,    23,    23,    23,
      23,    23,   380,   381,   408,   395,   397,   359,   403, -1046,
   -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046,
   -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046,
   -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046,
   -1046,  2597,  2154, -1046, -1046,    23,   401,   400,   404, -1046,
   -1046, -1046,   399,   405,   420,   423,   411,   426, -1046,   428,
     429,    80,   430,   431,   434,   436,   367,   432,   419,   421,
      63,   435,   435,   435,   435,   435,   435,   435,   435,   435,
     435,   537,   435,   435,   435,   435,   613,   435,   442,   613,
     613,   451,   537,   452,   386,   454,  2597,  2597,   613,   613,
     613,   613,   455,   459,   390,   458,   537,   613,   444,     2,
    2597,   613,   537,   473,   470,   477,    57,   613,   613,   613,
     613,   466,   481,  2816,   479,   478,   484,    71,   468,   469,
     482,  2597, -1046,   613, -1046,   487,   480,   488, -1046,   474,
     483, -1046,   486,   485,   491,  2154,  2154, -1046, -1046,   493,
     494,   492,   498,   489,   500,   490,   495,   497,    23,    23,
      23,    23,    23,    23,    23,    23,    23,    23,    23,    23,
      23,    23,   578,   578,   578,   578,   578,   578,   578,   578,
     578,   501, -1046, -1046, -1046,    23,    23,    23,    23, -1046,
   -1046, -1046,   505,    23,    23,   510, -1046, -1046,   511,   503,
     514,  2154,  2154,    23, -1046, -1046,    23,   515,   512,   506,
     530, -1046, -1046, -1046,   520,   526, -1046,    23, -1046,    23,
   -1046,    23,  2597, -1046, -1046, -1046,   535,   539,   570,   559,
      52,   566,   571, -1046,    23,    23,    23,    23,    23,    23,
      23,    23,    23,    23,    23,    23,    23,    23,    23,    23,
     586,    23,   567,    23, -1046,  2597, -1046,   580,   587,   582,
     583,   591,   592,   600,   599, -1046, -1046,   594, -1046, -1046,
     608,   617,   607,   551,  1488,  1710,   609,   611,   612,   614,
     620,   556,   624,   618,   641,   613,   112,   613,   613,  2597,
     613,  2597,  2597,   613,   613,   613,   613,  2597,   613,   637,
     613,  2597,   613,   613,   581,   613,   613,   584,   636,   648,
     585,  2597,  2597,   613,   613,   639,   643,   653,   588,   642,
     647,   613,    80,   613,   649, -1046,   595,   658,   659,   645,
     655,   656,   613,   613,   613,   613,   613,   613,   613,   613,
     613,   613,   613,   613,  2597,   613,  2597,   613,   657,   613,
     665,   613,   660,   668,   662,   603,   672,   677,   667,   675,
   -1046,   679,   664,   678,   676, -1046, -1046,   616,   683,   684,
     685,   681,   688,   687,   628,   686, -1046,   682,   697,    23,
   -1046, -1046, -1046, -1046, -1046, -1046,  2154,  2597,    23,    23,
      23, -1046,  2154,    23, -1046, -1046,  2597,    23,    23,   699,
      23, -1046,    23,   700,   635,   701,   704,    23,  3035,    23,
      23, -1046, -1046, -1046,   646,   709,   702,   711,   703,   650,
      23, -1046,    23, -1046,   651,   714,   716,   717,   713,   712,
     707,    23,    23,    23,    23,    23,    23,    23,    23,    23,
      23,    23,    23,  3254,    23,  3473,    23,   733,    23,   730,
      23,   669,   723,   737,   735,   734,   736,   680,   689,   743,
     741,   740,   739,   742,   752,   744, -1046,   751,   745, -1046,
     746, -1046,   738,   748,   613,  2597,   613,   613,   613,  2597,
     613,   613,   613,   747,   613,   613,   749,   754,   758,   753,
    2597,  2376,    80,   755,   759,   768,   760,   762,   764,   613,
     613,   765,   767,   769,   708, -1046, -1046,   775,   613,   613,
    2597,   613,   101,   613,   537,  2597,   613,   476,  2816,  2816,
    2376,  2597,  2376,  2597, -1046,    80,   777,   613,   778,   725,
     761,   784,   770,   729,   779,   799, -1046,   801, -1046,   785,
     787,   793,   790,   791,   115,   796,   807,   803, -1046,  2154,
      23, -1046,    23,  2154,    23, -1046, -1046,   797,    23, -1046,
   -1046,   802,   804, -1046,   806,  3692,   578,   578,   831, -1046,
    2597, -1046,   175,    25, -1046, -1046, -1046, -1046,   805,   790,
     791,   232,   815,   808, -1046,    23,   819,   233,   756,   833,
     839, -1046, -1046,    23, -1046, -1046,  2597, -1046,   841,   809,
   -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046,  2597,
      23,   578,   578, -1046, -1046, -1046, -1046, -1046,   831,  3911,
     831,  4130, -1046,   780,    23,   827,   843,   781,   243,   849,
     850,   840,   842,   851,   834,   838,   854, -1046, -1046,   844,
     846,   852,   845,   855,  2597,  2597,  2597,  2597,   613,   847,
    2597,   848,   853,   856,  2376,   303,   415,  2376,   578,   861,
     863,   865,   857,   858,   613,   866,   867,   872,   876, -1046,
     613,   864,   877,   613,  2376,  2376,   878,   613,   874,   860,
     221,   871,   875,   883,   884,   891,   880, -1046,   885,   886,
     792,   888,   895,   869, -1046,   890,    23,  2597,  2597,    23,
   -1046,   901,    23,   903,   906,   904,   831,   578,   578, -1046,
     578,   907,   908,   909,   910,   925, -1046,   913,   911,   912,
     259, -1046,   931,   929,    23,   831,   831,   914,    23,   920,
     926,   922,   927,   924,   930,   940,   932,   949,   942,   933,
     937,   209,   892,   941,   956,   944,   946,    80,   947,   950,
     899,   578,   578,   951,   902,   953, -1046,   965,   957,   915,
     961,   962,   966, -1046,   537,   968,   613,   970,   977,   971,
     987,   923,   974,   982,   984,   994,   980,   988,   983,   981,
     990,   996,   107,   993,   938,  1007,   997,    23,   998,   995,
    1009,   999,  1012,  1004, -1046,  1000,   160,  1002,  1003,  1010,
   -1046,  1008, -1046,  1005, -1046,  1013,  1011,  1024,  1017,  1014,
    1016,   963, -1046,  1027,   967,  1029,  1030,  1035,    84,  1025,
    1036,  1039,  1037,  1038,   613,  1040,   976,  1044,   979,  1046,
    1048,   985,  1049,  1042,  1041,   989,  1043,  1045,  1015,  1047,
   -1046,  1053,  1054,  1050, -1046,  1058,  1051,   283,  1055,  1061,
    1067,  1056,  1073,  1065,  1070,  1072,  1080,  1074,    23,  1075,
    1086,  1069,  1088,  1071,  1081,   285,  1076,  1078,  1077,   100,
   -1046,  1082,  1090, -1046,  1079,  1089, -1046,  1085,  1084,  1097,
     147,  1091,  1093,  1057,  1099,  1087,  1092,  1094,  1095, -1046,
    1098,   476,  1100,  1105,  1102,  1108,  1106,  1107,  1109,  1114,
    1113,  1110,  1060,  1118,  1117,  1111,  1062,  1129,  1126,  1119,
    1116,  1083,  1137,  1120,  1131,  1096,  1136,  1135,  1142,  1141,
    1101,    17,  1134, -1046,    23,  1130,  1128,  1148,  1133,  1149,
      20,  1152,  1143,  1153,  1101,   106,  1156,  1145,  1155,  1170,
    1154,  1171,  1104,  1163,  1146,  1165,  1172,  1158,  1173,  1166,
    1176,  1187,  1175,  1178, -1046,  1182,  1177,    31,  1189,  1191,
    1190,  1195,  1188,  1192,  1193,  1198,  1196,  1180,  1194,  1200,
    1202,  1201,  1204,    74,  1203,  1215,  1207,  1221,  1213,  1205,
   -1046,  1209,  1208,  1157,  1228,  1229,  1162,  1220,  1230,    23,
   -1046, -1046, -1046, -1046, -1046,  1233, -1046,  1234,  1208,  1237,
    1225,  1238,  1169,  1241,  1227,  1231, -1046, -1046,  1243,  1179,
    1232,  1235,  1247, -1046,  1236,  1239,  1246,  1240,  1242,  1245,
   -1046,  1244,  1250,  1253,  1248,  1183,  1252,    80,  1251,  1254,
    1255,  1258,  1267,  1257,  1260,  1270,  1271,  1272,   235,  1259,
    1273,  1262, -1046,  1269,  1263,  1186,  1268,  1265,  1282,  1285,
    1274,  1286,  1249,  1275, -1046, -1046,  1263,  1274,  1276,  1219,
    1290,  1278, -1046,  1283,  1226,  1281,  1284,  1287,  1288,  1261,
    1264, -1046,  1289,  1279,  1266,  1292,  1291, -1046,  1293,  1294,
    1297,  1264,  1295,  1298,  1302, -1046,   236,  1299,  1296,  1304,
   -1046,   237,  1303,  1321,  1305,  1322,  1327,  1324, -1046,  1317,
    1312,  1332,  1333,  1326,  1325,  1328,  1329,  1330, -1046,  1331,
    1334,  1335,  1323,  1280,  1336,  1337,  1338,  1346,  1339,  1342,
    1340, -1046,  1341,  1343,  1344, -1046,  1345,  1349,  1347,  1351,
    1352,  1348,  1356,  1358,  1353,  1363,  1368,  1366,  1359,  1357,
   -1046,  1360,  1361,  1374,  1364,  1362,  1365,  1369,  1367,  1375,
    1370,  1377,  1371,  1372, -1046,  1376, -1046,  1381,  1373,  1379,
    1392,  1393, -1046,  1310,  1380,  1394,  1396, -1046, -1046,  1397,
    1383,  1382,  1387,  1388,  1399, -1046,  1389,  1390,  1391,  1405,
    1407,  1395, -1046,  1398,  1410, -1046,  1411,  1400,  1401, -1046,
    1408,  1403,  1404, -1046,  1406,  1378, -1046, -1046, -1046, -1046
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046,
   -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046, -1046,  -709,
   -1046, -1046, -1046, -1046, -1046,  -673, -1045, -1046,   338,   241,
   -1046,  -484,  -697,  -878, -1046,   121,  -481,  -888,  -853,  -690,
    -735,   496,   -13, -1046,  -889,   361,  -626,   256,  -919,   -39,
     145,   -14,   362,  -251,  -473,   -15,  1402, -1046, -1046, -1046,
   -1046, -1046, -1046, -1046, -1046, -1046, -1046,  -444, -1046, -1046,
   -1046, -1046, -1046, -1046, -1046, -1046,  -112,  1164,  1167,  1174,
    -346,  1161,  1168,  1181,  1184,  1185,  1197,  1199,  1423,  1644,
    1866,  -257,  -240,  -239,    39, -1046, -1046,  1871, -1046, -1046,
   -1046, -1046,  2093,  -238, -1046, -1046,  1159,  -287, -1046,  2094,
   -1046,  1160,  4069,  -236, -1046,    53,  -104,  -245,  4070, -1046,
     916, -1046, -1046, -1046,   -85,  4071, -1046, -1046, -1046, -1046,
   -1046, -1046, -1046,  4067, -1046, -1046, -1046
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -207
static const yytype_int16 yytable[] =
{
     275,   273,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   852,   578,   318,
     320,   321,   322,   323,   324,   325,   326,   327,  1044,   814,
    -206,   466,   373,   839,   645,   623,   624,   990,   626,   832,
     419,   429,  1015,   392,   396,   393,   397,   633,   467,   468,
     636,     1,   641,     2,  1384,  1151,   643,  1384,   654,   986,
     653,  1048,  1158,  1050,  1417,  1418,   648,   614,    43,     3,
     347,     4,     5,    33,   413,     6,   659,    36,   627,   758,
       7,     8,   695,   433,    44,     9,    10,    11,   660,    12,
     587,   759,   642,   690,   661,  1440,    34,   662,   655,    37,
     436,  1441,    35,   438,  1054,  1442,  1385,  1281,   691,  1392,
     308,   602,   603,   604,   605,   606,   607,   608,   609,   610,
    1282,  1333,  1257,  1028,   432,   433,   434,  1396,  1323,  1248,
      47,    48,   807,  1029,  1334,   345,   435,   346,  1335,   347,
     348,  1249,   436,   437,  1397,   438,   808,   349,    40,  1069,
      41,  1232,  1070,   350,   351,   592,   593,   594,   595,   596,
     597,   598,   599,   600,   601,   353,   615,   616,   617,   618,
    1343,   621,   302,   418,   424,    42,   387,    46,   475,   410,
     303,  1088,  1262,  1344,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,  1263,  1136,   394,   398,   492,   493,
    1130,   430,   340,   319,   319,   319,   319,   319,   319,   319,
     319,   319,   341,   984,    45,  1155,  1156,   420,   399,   340,
     400,   421,   389,   401,   575,   576,   388,    38,  1209,   422,
     402,   389,  1210,    39,   806,   300,   812,   813,   390,   305,
    1211,   301,  1161,   589,   823,   306,   825,   270,  1162,  -206,
    -206,  -206,   828,   575,   576,   294,  1495,  1534,  1539,   665,
     590,   591,  1496,  1535,  1540,   683,  1090,  1096,  1027,  1091,
    1064,   271,   853,  1040,   473,    -4,    -4,  1111,   292,   648,
    1112,   861,   862,   863,   864,   865,   866,   867,   868,   869,
     870,   871,   872,  1191,   291,   878,  1064,   532,   493,   293,
     880,   668,   575,   576,  1309,  1310,  1328,  1329,   664,  1137,
     667,   295,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,  1046,  1047,   704,   705,   453,   469,   296,   491,
     297,   382,   384,   298,   299,   304,   380,   385,   500,    47,
     340,   476,   477,   482,   501,   485,   502,   503,   504,   505,
     506,   478,   507,   480,   508,   509,   510,   511,   512,   479,
     513,   514,   515,   516,   517,  1126,  1288,   519,  1129,   520,
     481,   483,   522,   484,   486,   487,   490,   526,   527,   528,
     489,   529,   530,   531,   494,   495,   496,   497,   498,   499,
    1132,   518,   559,   521,   524,   536,   523,   537,   525,   533,
     539,   540,  1044,   541,   542,   534,   535,   538,   543,   546,
     547,   548,   549,   550,   551,   552,   553,   544,   545,   554,
     555,  1138,   557,   978,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   556,   558,   560,   564,   565,   567,
     566,   569,  1217,   568,   570,   571,   572,   573,  1014,  1007,
     580,   574,   579,   581,   584,   585,   583,   562,  1030,   586,
     563,   582,   587,   488,   622,   488,   488,   488,   488,   488,
     488,   488,   488,   625,   628,   629,   630,   637,   638,   639,
     640,   644,   578,  1041,  1042,   308,   602,   603,   604,   605,
     606,   607,   608,   609,   610,   656,   657,   613,   680,   658,
     682,   687,   688,   689,   692,   613,   613,   693,   613,   694,
     696,   698,   699,   697,   713,   634,   635,   702,   703,   700,
     706,   707,   613,   701,   708,   709,   710,   711,   613,   714,
     712,   729,   734,   676,   677,   678,   679,   737,   738,   686,
     739,   740,   745,   747,   746,   471,   308,   602,   603,   604,
     605,   606,   607,   608,   609,   610,   611,   748,   749,   750,
     473,   473,   754,   318,   320,   321,   322,   323,   324,   325,
     326,   327,   755,   715,   716,   717,   718,   719,   720,   721,
     722,   723,   724,   725,   726,   727,   728,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   756,   757,   760,
     730,   731,   732,   733,   761,   778,   780,   782,   735,   736,
     785,   783,   786,  1146,   784,   787,   741,   742,   743,   788,
     789,   744,   308,   602,   603,   604,   605,   606,   607,   608,
     609,   610,   751,   339,   752,   791,   753,   790,   792,   793,
     794,   798,   797,   801,   799,   802,   800,   803,   804,   762,
     763,   764,   765,   766,   767,   768,   769,   770,   771,   772,
     773,   774,   775,   776,   777,   805,   779,   824,   781,   834,
     829,   835,   844,   833,   836,   845,   846,   847,   848,   849,
     856,   857,   854,   858,   855,   859,   860,   879,   877,   562,
     562,   882,   884,   881,   883,   885,   886,   887,   888,   889,
     890,   891,   894,   892,   648,   893,   815,   895,   896,   818,
     819,   820,   821,   897,   613,   898,   613,   900,   827,   901,
     903,   831,   831,   899,   917,   902,   913,   916,   561,   841,
     843,   919,   924,   918,   925,   923,   935,   851,   926,   928,
     931,   932,   927,   933,   934,   936,   937,   319,   319,   319,
     319,   319,   319,   319,   319,   319,   954,   956,   958,   959,
     960,   874,   961,   876,   962,   613,   966,   963,   967,   964,
     968,   969,   971,   973,   972,   970,   976,   974,   965,   987,
     993,   991,   631,   632,   977,   994,   975,   992,  1008,  1009,
    1010,  1057,  1011,  1012,   904,  1013,   652,  1019,  1016,  1017,
    1059,   905,  1018,   906,   907,   908,  1020,   909,   910,   685,
    1053,  1055,   911,   912,  1056,   914,  1058,   915,  1060,  1061,
    1062,  1063,  1064,  1066,  1073,   922,  1065,  1067,  1068,  1071,
    1072,   471,   471,   339,  1079,   929,  1087,   930,  1092,  1081,
    1083,  1093,  1102,  1082,  1089,  1097,   938,   939,   940,   941,
     942,   943,   944,   945,   946,   947,   948,   949,  1095,   951,
    1098,   953,  1099,   955,  1101,   957,  1108,  1109,  1113,  1106,
    1110,  1114,  1118,  1115,  1117,  1116,  1119,  1120,  1125,  1123,
    1145,  1171,  1124,  1121,  1122,  1131,  1133,  1160,  1152,  1144,
    1174,  1134,   980,   981,   982,  1135,   831,   985,   843,  1141,
     989,   989,  1142,  1143,  1147,  1149,  1148,  1004,  1150,  1153,
    1163,  1157,  1159,  1164,  1421,  1165,   851,  1166,  1167,  1168,
    1170,  1169,  1175,   339,  1022,  1024,  1172,  1022,   613,  1034,
    1036,  1173,  1022,  1045,   686,   686,  1004,  1176,  1004,  1178,
    1179,  1183,  1180,   843,  1187,  1185,  1184,  1188,  1186,  1189,
    1192,  1190,  1193,  1195,  1197,  1199,  1198,  1085,  1086,  1200,
     561,   561,  1201,  1203,  1074,  1075,  1202,  1076,  1077,  1078,
    1205,  1204,  1207,  1080,  1206,   652,  1208,   816,   817,  1214,
    1213,  1212,  1215,   822,  1421,  1216,  1218,   826,  1220,  1219,
    1221,  1222,  1223,   339,   339,  1224,  1225,   838,   838,  1227,
    1094,  1228,  1085,  1086,  1226,  1229,  1231,  1234,  1100,  1233,
    1235,  1236,  1237,  1238,   339,  1239,  1240,  1241,  1242,  1243,
    1245,  1244,  1246,  1247,  1250,  1103,  1252,  1251,  1253,  1255,
     873,  1257,   875,  1256,  1259,  1260,  1264,  1258,  1261,  1107,
    1266,  1265,  1267,  1268,  1270,  1269,  1271,   339,  1272,  1140,
    1276,  1278,  1275,  1273,  1274,  1279,  1277,  1280,  1283,  1284,
    1285,  1287,  1286,  1289,   989,  1290,  1003,  1291,  1292,  1293,
    1004,  1294,  1296,  1004,  1295,  1297,  1304,  1305,  1299,  1307,
    1298,  1300,  1311,  1308,  1301,  1303,  1024,  1306,  1312,  1034,
    1004,  1004,  1003,  1024,  1313,  1003,  1314,  1003,  1181,  1182,
    1315,  1316,  1317,  1319,  1302,  1318,  1320,  1322,  1323,  1324,
    1325,  1326,  1337,  1327,  1331,  1332,  1330,  1177,  1340,  1338,
    1336,  1339,  1341,  1342,  1345,  1346,  1348,  1349,  1356,  1357,
    1350,  1358,  1351,  1359,  1352,  1361,  1353,  1362,  1355,  1194,
    1363,   319,   319,  1196,  1366,  1360,  1347,   488,  1364,  1365,
    1367,  1369,  1370,  1371,  1368,  1373,  1375,  1372,  1377,  1379,
    1376,   979,  1380,  1381,  1382,   983,  1386,  1384,  1388,  1389,
    1391,  1393,  1374,  1390,  1395,  1398,   995,  1405,   339,   339,
    1036,  1399,  1024,  1394,   339,  1378,   319,   319,   339,  1400,
    1383,  1396,  1402,  1403,  1401,  1404,  1026,  1406,  1408,  1407,
     339,  1039,  1254,  1410,   685,   685,  1409,  1049,  1411,  1051,
    1412,  1413,  1414,  1415,  1426,  1416,  1425,  1427,  1428,  1429,
    1431,  1432,  1433,  1434,  1430,  1437,  1435,  1439,  1438,  1003,
     488,   488,  1003,   319,  1444,   339,  1447,   339,  1436,  1445,
     851,  1443,  1446,  1449,  1448,  1450,  1451,  1452,  1453,  1003,
    1003,  1454,  1455,  1456,  1458,  1459,  1460,  1461,  1463,  1462,
    1464,  1465,  1473,  1466,  1467,  1469,  1471,  1470,  1468,  1474,
    1472,  1509,  1482,  1321,  1485,  1502,  1475,  1486,  1478,  1481,
    1476,  1488,   319,   319,  1477,   488,  1479,  1480,  1483,  1487,
    1489,  1490,  1491,  1492,  1493,  1494,  1499,  1498,  1497,  1500,
    1501,  1505,  1503,  1504,  1506,  1508,  1511,  1045,  1512,  1513,
    1514,  1507,  1510,  1515,  1517,  1516,  1518,  1529,  1524,  1519,
    1537,  1520,  1527,  1523,  1530,  1533,   488,   488,  1526,  1531,
     838,  1127,  1128,   838,  1532,  1528,   652,  1541,  1536,  1387,
    1542,   339,  1538,  1543,  1544,   339,  1545,  1546,  1547,  1548,
    1521,  1549,  1550,  1522,  1558,  1525,  1551,   339,  1552,  1559,
    1553,  1554,   339,  1555,  1556,  1564,  1557,  1569,  1562,  1560,
    1574,  1567,  1561,  1572,  1575,  1576,  1563,  1565,  1566,  1577,
    1568,  1578,  1570,  1573,  1571,  1579,  1580,  1581,   339,  1582,
    1584,  1583,  1585,  1587,  1586,  1588,  1600,  1593,  1589,  1604,
    1629,   339,  1594,  1592,  1457,  1590,  1601,  1591,  1595,  1596,
    1597,   339,  1599,   339,  1598,  1602,  1603,  1606,  1605,  1607,
    1608,  1609,  1610,  1611,  1612,  1613,  1615,  1614,  1617,  1616,
    1618,  1620,  1619,  1621,  1622,  1230,  1623,  1624,  1625,  1626,
    1627,  1154,  1354,  1628,  1484,   426,   428,   404,  1139,   456,
     405,  1052,   307,     0,     0,     0,   457,   406,     0,     0,
       0,     0,   669,     0,     0,     0,  1003,     0,     0,   458,
       0,     0,   459,   460,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   461,     0,   462,     0,   339,
     339,   328,    52,    53,    54,    55,    56,   329,   330,   331,
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
     795,   463,   270,   328,    52,    53,    54,    55,    56,   329,
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
     268,   269,   464,   796,   270,    51,    52,    53,    54,    55,
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
     266,   267,   268,   269,   465,   416,   270,   328,    52,    53,
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
     264,   265,   266,   267,   268,   269,   407,   408,   270,   328,
      52,    53,    54,   996,   997,    57,    58,    59,    60,    61,
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
     262,   263,   264,   265,   266,   267,   268,   269,   575,   576,
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
     262,   263,   264,   265,   266,   267,   268,   269,   328,   921,
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
     263,   264,   265,   266,   267,   268,   269,   328,   950,    53,
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
     264,   265,   266,   267,   268,   269,   328,   952,    53,    54,
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
     265,   266,   267,   268,   269,   328,  1084,    53,    54,    55,
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
     266,   267,   268,   269,   328,  1104,    53,    54,    55,    56,
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
     267,   268,   269,   328,  1105,    53,    54,    55,    56,   329,
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
     268,   269,   409,   411,   412,   470
};

static const yytype_int16 yycheck[] =
{
      15,    15,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,   752,   491,    58,
      59,    60,    61,    62,    63,    64,    65,    66,   947,   719,
       5,   288,   277,   742,    32,   519,   520,   915,   522,   736,
     285,   286,   930,   281,   282,   281,   282,   528,   288,   288,
     531,     1,   536,     3,    37,  1100,   537,    37,   542,   912,
     541,   950,  1107,   952,    33,    34,   539,   511,    23,    19,
      23,    21,    22,    22,    27,    25,    19,    23,   522,    27,
      30,    31,   563,    20,    39,    35,    36,    37,    31,    39,
      27,    39,   536,    22,    37,    21,    30,    40,   542,    23,
      37,    27,    36,    40,   957,    31,    89,    23,    37,    89,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      36,    21,    22,    22,    19,    20,    21,    21,    22,    22,
     225,   226,    20,    32,    34,    19,    31,    21,    38,    23,
      24,    34,    37,    38,    38,    40,    34,    31,    19,    34,
      39,  1196,    37,    37,    38,   501,   502,   503,   504,   505,
     506,   507,   508,   509,   510,   277,   512,   513,   514,   515,
      23,   517,    30,   285,   286,    23,   280,     0,   290,   283,
      38,     6,    22,    36,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    34,  1084,   281,   282,    39,    40,
    1078,   286,    21,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    31,   910,    32,  1104,  1105,    19,    19,    21,
      21,    23,    24,    24,   222,   223,    19,    27,    19,    31,
      31,    24,    23,    33,   715,    31,   717,   718,    31,    31,
      31,    37,    21,   500,   728,    37,   730,   224,    27,   224,
     225,   226,   733,   222,   223,    37,    21,    21,    21,   546,
     500,   500,    27,    27,    27,   552,    34,    34,   941,    37,
      37,    15,   753,   946,   289,   225,   226,    34,    23,   752,
      37,   762,   763,   764,   765,   766,   767,   768,   769,   770,
     771,   772,   773,    34,    22,   779,    37,    39,    40,    23,
     781,   546,   222,   223,    21,    22,    21,    22,   546,     6,
     546,    38,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,   948,   949,   575,   576,   287,   288,    37,   344,
      19,   278,   279,    34,    27,    20,    31,    31,   353,   225,
      21,    19,    19,    33,   359,    37,   361,   362,   363,   364,
     365,    38,   367,    22,   369,   370,   371,   372,   373,    38,
     375,   376,   377,   378,   379,  1074,  1254,   382,  1077,   384,
      38,    23,   387,    23,    19,    39,    27,   392,   393,   394,
      26,   396,   397,   398,    26,    32,    42,    27,    23,    33,
    1080,    27,    33,    27,    42,   410,    39,   412,    27,    26,
     415,   416,  1321,   418,   419,    42,    27,    32,    39,   424,
     425,   426,   427,   428,   429,   430,   431,    21,    27,    39,
      39,     6,    27,   904,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    26,    38,    33,    36,    38,    40,
      36,    21,  1177,    38,    21,    34,    20,    19,   929,   922,
      19,    22,    22,    19,    22,    36,    89,   472,   942,    38,
     475,    25,    27,   318,    22,   320,   321,   322,   323,   324,
     325,   326,   327,    22,    22,    89,    22,    22,    19,    89,
      22,    37,   955,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    22,    26,   511,    32,    22,
      19,    22,    24,    19,    36,   519,   520,    38,   522,    27,
      23,    23,    38,    33,    19,   529,   530,    32,    27,    36,
      27,    27,   536,    37,    32,    27,    37,    27,   542,    32,
      40,    30,    27,   547,   548,   549,   550,    27,    27,   553,
      37,    27,    27,    37,    32,   289,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    27,    38,    33,
     575,   576,    27,   602,   603,   604,   605,   606,   607,   608,
     609,   610,    33,   588,   589,   590,   591,   592,   593,   594,
     595,   596,   597,   598,   599,   600,   601,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    27,    39,    33,
     615,   616,   617,   618,    33,    19,    39,    27,   623,   624,
      27,    24,    21,  1094,    32,    23,   631,   632,   633,    19,
      21,   636,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,   647,   271,   649,    27,   651,    43,    21,    32,
      89,    30,    33,    23,    32,    89,    32,    23,    30,   664,
     665,   666,   667,   668,   669,   670,   671,   672,   673,   674,
     675,   676,   677,   678,   679,    24,   681,    30,   683,    33,
      89,    23,    33,    89,    89,    32,    23,    89,    36,    32,
      22,    22,    33,    38,    89,    30,    30,    22,    31,   704,
     705,    23,    89,    33,    32,    23,    19,    30,    23,    20,
      36,    23,    19,    27,  1177,    89,   720,    23,    23,   723,
     724,   725,   726,    32,   728,    27,   730,    89,   732,    33,
      23,   735,   736,    36,    89,    43,    27,    27,   472,   743,
     744,    27,    23,    32,    32,    89,    23,   751,    27,    89,
      89,    27,    39,    27,    27,    33,    39,   602,   603,   604,
     605,   606,   607,   608,   609,   610,    23,    27,    89,    36,
      23,   775,    27,   777,    30,   779,    23,    31,    27,    89,
      30,    32,    20,    22,    30,    33,    38,    32,    89,    32,
      22,    32,   526,   527,    36,    32,    40,    33,    33,    30,
      22,    30,    32,    31,   809,    31,   540,    89,    33,    32,
      30,   816,    33,   818,   819,   820,    31,   822,   823,   553,
      33,    33,   827,   828,    89,   830,    32,   832,    89,    40,
      21,    20,    37,    30,    21,   840,    39,    37,    37,    33,
      23,   575,   576,   471,    37,   850,     5,   852,    23,    37,
      34,    33,    33,    39,    39,    89,   861,   862,   863,   864,
     865,   866,   867,   868,   869,   870,   871,   872,    39,   874,
      27,   876,    23,   878,    23,   880,    39,    24,    19,    89,
      89,    21,    38,    33,    23,    33,    38,    23,    23,    27,
      22,    89,    37,    39,    38,    38,    38,    27,    24,    32,
      21,    38,   906,   907,   908,    39,   910,   911,   912,    38,
     914,   915,    39,    38,    38,    33,    39,   921,    32,    32,
      39,    33,    38,    38,  1387,    32,   930,    33,    27,    39,
      34,    36,    32,   561,   938,   939,    38,   941,   942,   943,
     944,    36,   946,   947,   948,   949,   950,    36,   952,    36,
      34,    34,    38,   957,    19,    36,    38,    34,    38,    38,
      19,    39,    23,    39,    34,    33,    30,   996,   997,    32,
     704,   705,    38,    23,   979,   980,    36,   982,   983,   984,
      21,    39,    39,   988,    32,   719,    39,   721,   722,    23,
      39,    89,    38,   727,  1457,    39,    39,   731,    89,    39,
      39,    89,    39,   631,   632,    30,    39,   741,   742,    38,
    1015,    39,  1041,  1042,    89,    39,    38,    30,  1023,    39,
      39,    24,    89,    39,   652,    33,    32,    23,    38,    31,
      39,    38,    32,    27,    31,  1040,    19,    89,    31,    31,
     774,    22,   776,    38,    22,    31,    34,    38,    38,  1054,
      30,    38,    34,    38,    33,    32,    22,   685,    31,  1088,
      23,    22,    89,    39,    38,    25,    89,    22,    33,    23,
      21,    23,    25,    23,  1078,    89,   921,    23,    89,    23,
    1084,    23,    23,  1087,    89,    33,    23,    23,    89,    21,
      39,    38,    27,    32,    39,    38,  1100,    37,    27,  1103,
    1104,  1105,   947,  1107,    27,   950,    40,   952,  1137,  1138,
      27,    36,    32,    23,    89,    33,    32,    32,    22,    40,
      22,    40,    22,    32,    36,    38,    40,  1132,    33,    40,
      38,    32,    38,    26,    33,    32,    27,    40,    23,    27,
      38,    23,    38,    27,    39,    26,    38,    23,    38,  1154,
      27,   996,   997,  1158,    26,    38,    89,  1002,    38,    89,
      33,    89,    23,    27,    43,    39,    19,    38,    27,    23,
      40,   905,    27,    21,    23,   909,    32,    37,    40,    21,
      21,    19,    89,    40,    21,    19,   920,    31,   816,   817,
    1194,    36,  1196,    40,   822,    89,  1041,  1042,   826,    34,
      89,    21,    21,    89,    40,    32,   940,    32,    40,    27,
     838,   945,  1217,    37,   948,   949,    33,   951,    32,   953,
      23,    36,    34,    31,    23,    38,    27,    27,    23,    31,
      27,    23,    26,    43,    32,    23,    32,    23,    27,  1084,
    1085,  1086,  1087,  1088,    19,   873,    23,   875,    38,    32,
    1254,    38,    21,    34,    39,    37,    89,    19,    19,  1104,
    1105,    89,    32,    23,    21,    21,    19,    32,    89,    21,
      19,    34,    23,    32,    21,    33,    19,    32,    89,    23,
      34,    22,    89,  1288,    23,    89,    36,    23,    34,    31,
      38,    23,  1137,  1138,    39,  1140,    36,    34,    36,    34,
      23,    34,    32,    23,    23,    23,    34,    24,    39,    30,
      37,    19,    34,    38,    19,    19,    30,  1321,    89,    19,
      32,    37,    37,    30,    33,    89,    32,    23,    39,    32,
      24,    33,    31,    34,    27,    23,  1181,  1182,    36,    34,
    1074,  1075,  1076,  1077,    36,    42,  1080,    34,    39,  1354,
      19,   979,    38,    38,    22,   983,    19,    23,    31,    37,
      89,    19,    19,    89,    19,    89,    30,   995,    33,    36,
      32,    32,  1000,    33,    33,    19,    32,    24,    31,    89,
      19,    31,    36,    24,    22,    27,    38,    38,    36,    23,
      39,    23,    38,    36,    39,    32,    23,    19,  1026,    23,
      33,    32,    32,    19,    33,    31,    23,    22,    36,    89,
      22,  1039,    32,    36,  1419,    40,    27,    38,    31,    38,
      38,  1049,    31,  1051,    38,    23,    23,    23,    38,    23,
      23,    38,    40,    36,    36,    26,    36,    38,    23,    38,
      23,    33,    37,    23,    23,  1194,    36,    36,    30,    36,
      36,  1103,  1321,    37,  1457,   286,   286,   283,  1087,   288,
     283,   955,    50,    -1,    -1,    -1,   288,   283,    -1,    -1,
      -1,    -1,   546,    -1,    -1,    -1,  1321,    -1,    -1,   288,
      -1,    -1,   288,   288,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   288,    -1,   288,    -1,  1127,
    1128,     3,     4,     5,     6,     7,     8,     9,    10,    11,
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
     222,   288,   224,     3,     4,     5,     6,     7,     8,     9,
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
     220,   221,   288,   223,   224,     3,     4,     5,     6,     7,
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
     218,   219,   220,   221,   288,   284,   224,     3,     4,     5,
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
     220,   221,   283,   283,   283,   288
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     1,     3,    19,    21,    22,    25,    30,    31,    35,
      36,    37,    39,   228,   229,   230,   231,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   298,   299,   300,   301,
     302,   359,   363,    22,    30,    36,    23,    23,    27,    33,
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
      37,    38,   238,   303,   304,   305,   306,   321,   322,   324,
     329,   330,   331,   332,   333,   334,   336,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   351,   352,   353,
      31,   235,   342,   236,   342,    31,   242,   343,    19,    24,
      31,   240,   330,   340,   351,   243,   330,   340,   351,    19,
      21,    24,    31,   248,   304,   305,   306,   329,   336,   339,
     343,   345,   352,    27,   244,   323,   324,   237,   303,   344,
      19,    23,    31,   239,   303,   328,   333,   337,   338,   344,
     351,   362,    19,    20,    21,    31,    37,    38,    40,   233,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   360,   234,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   321,
     360,   274,   280,   282,   241,   303,    19,    19,    38,    38,
      22,    38,    33,    23,    23,    37,    19,    39,   277,    26,
      27,   282,    39,    40,    26,    32,    42,    27,    23,    33,
     282,   282,   282,   282,   282,   282,   282,   282,   282,   282,
     282,   282,   282,   282,   282,   282,   282,   282,    27,   282,
     282,    27,   282,    39,    42,    27,   282,   282,   282,   282,
     282,   282,    39,    26,    42,    27,   282,   282,    32,   282,
     282,   282,   282,    39,    21,    27,   282,   282,   282,   282,
     282,   282,   282,   282,    39,    39,    26,    27,    38,    33,
      33,   274,   282,   282,    36,    38,    36,    40,    38,    21,
      21,    34,    20,    19,    22,   222,   223,   268,   281,    22,
      19,    19,    25,    89,    22,    36,    38,    27,   307,   318,
     319,   320,   307,   307,   307,   307,   307,   307,   307,   307,
     307,   307,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,   258,   278,   294,   307,   307,   307,   307,   263,
     278,   307,    22,   258,   258,    22,   258,   294,    22,    89,
      22,   274,   274,   263,   278,   278,   263,    22,    19,    89,
      22,   258,   294,   263,    37,    32,   249,   267,   281,   297,
     250,   266,   274,   263,   258,   294,    22,    26,    22,    19,
      31,    37,    40,   245,   330,   334,   335,   340,   344,   347,
     348,   349,   350,   354,   355,   356,   278,   278,   278,   278,
      32,   361,    19,   334,   273,   274,   278,    22,    24,    19,
      22,    37,    36,    38,    27,   263,    23,    33,    23,    38,
      36,    37,    32,    27,   280,   280,    27,    27,    32,    27,
      37,    27,    40,    19,    32,   282,   282,   282,   282,   282,
     282,   282,   282,   282,   282,   282,   282,   282,   282,    30,
     282,   282,   282,   282,    27,   282,   282,    27,    27,    37,
      27,   282,   282,   282,   282,    27,    32,    37,    27,    38,
      33,   282,   282,   282,    27,    33,    27,    39,    27,    39,
      33,    33,   282,   282,   282,   282,   282,   282,   282,   282,
     282,   282,   282,   282,   282,   282,   282,   282,    19,   282,
      39,   282,    27,    24,    32,    27,    21,    23,    19,    21,
      43,    27,    21,    32,    89,   222,   223,    33,    30,    32,
      32,    23,    89,    23,    30,    24,   263,    20,    34,   247,
     357,   358,   263,   263,   266,   278,   274,   274,   278,   278,
     278,   278,   274,   258,    30,   258,   274,   278,   263,    89,
     259,   278,   259,    89,    33,    23,    89,   246,   274,   246,
     261,   278,   265,   278,    33,    32,    23,    89,    36,    32,
     264,   278,   267,   263,    33,    89,    22,    22,    38,    30,
      30,   263,   263,   263,   263,   263,   263,   263,   263,   263,
     263,   263,   263,   274,   278,   274,   278,    31,   258,    22,
     263,    33,    23,    32,    89,    23,    19,    30,    23,    20,
      36,    23,    27,    89,    19,    23,    23,    32,    27,    36,
      89,    33,    43,    23,   282,   282,   282,   282,   282,   282,
     282,   282,   282,    27,   282,   282,    27,    89,    32,    27,
     282,     4,   282,    89,    23,    32,    27,    39,    89,   282,
     282,    89,    27,    27,    27,    23,    33,    39,   282,   282,
     282,   282,   282,   282,   282,   282,   282,   282,   282,   282,
       4,   282,     4,   282,    23,   282,    27,   282,    89,    36,
      23,    27,    30,    31,    89,    89,    23,    27,    30,    32,
      33,    20,    30,    22,    32,    40,    38,    36,   263,   274,
     278,   278,   278,   274,   259,   278,   265,    32,   260,   278,
     260,    32,    33,    22,    32,   274,     7,     8,   271,   272,
     274,   275,   276,   277,   278,   281,   270,   281,    33,    30,
      22,    32,    31,    31,   263,   264,    33,    32,    33,    89,
      31,   252,   278,   253,   278,   254,   274,   252,    22,    32,
     258,   295,   296,   255,   278,   256,   278,   294,   257,   274,
     252,     7,     8,   262,   275,   278,   273,   273,   271,   274,
     271,   274,   268,    33,   265,    33,    89,    30,    32,    30,
      89,    40,    21,    20,    37,    39,    30,    37,    37,    34,
      37,    33,    23,    21,   282,   282,   282,   282,   282,    37,
     282,    37,    39,    34,     4,   276,   276,     5,     6,    39,
      34,    37,    23,    33,   282,    39,    34,    89,    27,    23,
     282,    23,    33,   282,     4,     4,    89,   282,    39,    24,
      89,    34,    37,    19,    21,    33,    33,    23,    38,    38,
      23,    39,    38,    27,    37,    23,   246,   274,   274,   246,
     260,    38,   266,    38,    38,    39,   271,     6,     6,   272,
     276,    38,    39,    38,    32,    22,   263,    38,    39,    33,
      32,   253,    24,    32,   255,   271,   271,    33,   253,    38,
      27,    21,    27,    39,    38,    32,    33,    27,    39,    36,
      34,    89,    38,    36,    21,    32,    36,   282,    36,    34,
      38,   276,   276,    34,    38,    36,    38,    19,    34,    38,
      39,    34,    19,    23,   282,    39,   282,    34,    30,    33,
      32,    38,    36,    23,    39,    21,    32,    39,    39,    19,
      23,    31,    89,    39,    23,    38,    39,   267,    39,    39,
      89,    39,    89,    39,    30,    39,    89,    38,    39,    39,
     256,    38,   253,    39,    30,    39,    24,    89,    39,    33,
      32,    23,    38,    31,    38,    39,    32,    27,    22,    34,
      31,    89,    19,    31,   282,    31,    38,    22,    38,    22,
      31,    38,    22,    34,    34,    38,    30,    34,    38,    32,
      33,    22,    31,    39,    38,    89,    23,    89,    22,    25,
      22,    23,    36,    33,    23,    21,    25,    23,   264,    23,
      89,    23,    89,    23,    23,    89,    23,    33,    39,    89,
      38,    39,    89,    38,    23,    23,    37,    21,    32,    21,
      22,    27,    27,    27,    40,    27,    36,    32,    33,    23,
      32,   282,    32,    22,    40,    22,    40,    32,    21,    22,
      40,    36,    38,    21,    34,    38,    38,    22,    40,    32,
      33,    38,    26,    23,    36,    33,    32,    89,    27,    40,
      38,    38,    39,    38,   262,    38,    23,    27,    23,    27,
      38,    26,    23,    27,    38,    89,    26,    33,    43,    89,
      23,    27,    38,    39,    89,    19,    40,    27,    89,    23,
      27,    21,    23,    89,    37,    89,    32,   282,    40,    21,
      40,    21,    89,    19,    40,    21,    21,    38,    19,    36,
      34,    40,    21,    89,    32,    31,    32,    27,    40,    33,
      37,    32,    23,    36,    34,    31,    38,    33,    34,   251,
     269,   281,   325,   326,   327,    27,    23,    27,    23,    31,
      32,    27,    23,    26,    43,    32,    38,    23,    27,    23,
      21,    27,    31,    38,    19,    32,    21,    23,    39,    34,
      37,    89,    19,    19,    89,    32,    23,   282,    21,    21,
      19,    32,    21,    89,    19,    34,    32,    21,    89,    33,
      32,    19,    34,    23,    23,    36,    38,    39,    34,    36,
      34,    31,    89,    36,   269,    23,    23,    34,    23,    23,
      34,    32,    23,    23,    23,    21,    27,    39,    24,    34,
      30,    37,    89,    34,    38,    19,    19,    37,    19,    22,
      37,    30,    89,    19,    32,    30,    89,    33,    32,    32,
      33,    89,    89,    34,    39,    89,    36,    31,    42,    23,
      27,    34,    36,    23,    21,    27,    39,    24,    38,    21,
      27,    34,    19,    38,    22,    19,    23,    31,    37,    19,
      19,    30,    33,    32,    32,    33,    33,    32,    19,    36,
      89,    36,    31,    38,    19,    38,    36,    31,    39,    24,
      38,    39,    24,    36,    19,    22,    27,    23,    23,    32,
      23,    19,    23,    32,    33,    32,    33,    19,    31,    36,
      40,    38,    36,    22,    32,    31,    38,    38,    38,    31,
      23,    27,    23,    23,    89,    38,    23,    23,    23,    38,
      40,    36,    36,    26,    38,    36,    38,    23,    23,    37,
      33,    23,    23,    36,    36,    30,    36,    36,    37,    22
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
#line 220 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputDeviceParameter((yyvsp[(3) - (7)].Number), (yyvsp[(5) - (7)].String), (yyvsp[(7) - (7)].String));      }
    break;

  case 105:
#line 221 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputChannelParameter((yyvsp[(3) - (9)].Number), (yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].String), (yyvsp[(9) - (9)].String)); }
    break;

  case 106:
#line 222 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMidiInputDeviceParameter((yyvsp[(3) - (7)].Number), (yyvsp[(5) - (7)].String), (yyvsp[(7) - (7)].String));        }
    break;

  case 107:
#line 223 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMidiInputPortParameter((yyvsp[(3) - (9)].Number), (yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].String), (yyvsp[(9) - (9)].String));      }
    break;

  case 108:
#line 224 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                         }
    break;

  case 109:
#line 225 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMidiInstrumentMapName((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].String));               }
    break;

  case 110:
#line 226 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetFxSendAudioOutputChannel((yyvsp[(5) - (11)].Number),(yyvsp[(7) - (11)].Number),(yyvsp[(9) - (11)].Number),(yyvsp[(11) - (11)].Number)); }
    break;

  case 111:
#line 227 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetEcho((yyparse_param_t*) yyparse_param, (yyvsp[(3) - (3)].Dotnum));  }
    break;

  case 112:
#line 230 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateAudioOutputDevice((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].KeyValList)); }
    break;

  case 113:
#line 231 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateAudioOutputDevice((yyvsp[(3) - (3)].String));    }
    break;

  case 114:
#line 232 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateMidiInputDevice((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].KeyValList));   }
    break;

  case 115:
#line 233 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateMidiInputDevice((yyvsp[(3) - (3)].String));      }
    break;

  case 116:
#line 234 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateFxSend((yyvsp[(3) - (5)].Number),(yyvsp[(5) - (5)].Number));            }
    break;

  case 117:
#line 235 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateFxSend((yyvsp[(3) - (7)].Number),(yyvsp[(5) - (7)].Number),(yyvsp[(7) - (7)].String)); }
    break;

  case 118:
#line 238 "lscp.y"
    { (yyval.String) = LSCPSERVER->ResetChannel((yyvsp[(3) - (3)].Number)); }
    break;

  case 119:
#line 241 "lscp.y"
    { (yyval.String) = LSCPSERVER->ClearMidiInstrumentMappings((yyvsp[(3) - (3)].Number));  }
    break;

  case 120:
#line 242 "lscp.y"
    { (yyval.String) = LSCPSERVER->ClearAllMidiInstrumentMappings(); }
    break;

  case 121:
#line 245 "lscp.y"
    { (yyval.String) = LSCPSERVER->DestroyAudioOutputDevice((yyvsp[(3) - (3)].Number)); }
    break;

  case 122:
#line 246 "lscp.y"
    { (yyval.String) = LSCPSERVER->DestroyMidiInputDevice((yyvsp[(3) - (3)].Number));   }
    break;

  case 123:
#line 247 "lscp.y"
    { (yyval.String) = LSCPSERVER->DestroyFxSend((yyvsp[(3) - (5)].Number),(yyvsp[(5) - (5)].Number)); }
    break;

  case 124:
#line 250 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String); }
    break;

  case 125:
#line 251 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String); }
    break;

  case 126:
#line 254 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputDevice((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));      }
    break;

  case 127:
#line 255 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputChannel((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number), (yyvsp[(3) - (7)].Number)); }
    break;

  case 128:
#line 256 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputType((yyvsp[(5) - (5)].String), (yyvsp[(3) - (5)].Number));        }
    break;

  case 129:
#line 257 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInput((yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].Number), (yyvsp[(9) - (9)].Number), (yyvsp[(3) - (9)].Number));      }
    break;

  case 130:
#line 258 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputDevice((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));        }
    break;

  case 131:
#line 259 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputPort((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));          }
    break;

  case 132:
#line 260 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputChannel((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));       }
    break;

  case 133:
#line 261 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputType((yyvsp[(5) - (5)].String), (yyvsp[(3) - (5)].Number));          }
    break;

  case 134:
#line 262 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetVolume((yyvsp[(5) - (5)].Dotnum), (yyvsp[(3) - (5)].Number));                 }
    break;

  case 135:
#line 263 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMute((yyvsp[(5) - (5)].Dotnum), (yyvsp[(3) - (5)].Number));            }
    break;

  case 136:
#line 264 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelSolo((yyvsp[(5) - (5)].Dotnum), (yyvsp[(3) - (5)].Number));            }
    break;

  case 137:
#line 265 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMap((yyvsp[(3) - (5)].Number), (yyvsp[(5) - (5)].Number));             }
    break;

  case 138:
#line 266 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMap((yyvsp[(3) - (5)].Number), -1);             }
    break;

  case 139:
#line 267 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMap((yyvsp[(3) - (5)].Number), -2);             }
    break;

  case 140:
#line 270 "lscp.y"
    { (yyval.KeyValList)[(yyvsp[(1) - (3)].String)] = (yyvsp[(3) - (3)].String);          }
    break;

  case 141:
#line 271 "lscp.y"
    { (yyval.KeyValList) = (yyvsp[(1) - (5)].KeyValList); (yyval.KeyValList)[(yyvsp[(3) - (5)].String)] = (yyvsp[(5) - (5)].String); }
    break;

  case 142:
#line 274 "lscp.y"
    { (yyval.FillResponse) = fill_response_bytes;      }
    break;

  case 143:
#line 275 "lscp.y"
    { (yyval.FillResponse) = fill_response_percentage; }
    break;

  case 144:
#line 278 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDevices();           }
    break;

  case 145:
#line 279 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDevices();             }
    break;

  case 146:
#line 280 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListChannels();                    }
    break;

  case 147:
#line 281 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableEngines();            }
    break;

  case 148:
#line 282 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableMidiInputDrivers();   }
    break;

  case 149:
#line 283 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableAudioOutputDrivers(); }
    break;

  case 150:
#line 284 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListMidiInstrumentMappings((yyvsp[(3) - (3)].Number));    }
    break;

  case 151:
#line 285 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAllMidiInstrumentMappings();   }
    break;

  case 152:
#line 286 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListMidiInstrumentMaps();          }
    break;

  case 153:
#line 287 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListFxSends((yyvsp[(3) - (3)].Number));                   }
    break;

  case 154:
#line 290 "lscp.y"
    { (yyval.String) = LSCPSERVER->LoadInstrument((yyvsp[(1) - (5)].String), (yyvsp[(3) - (5)].Number), (yyvsp[(5) - (5)].Number));       }
    break;

  case 155:
#line 291 "lscp.y"
    { (yyval.String) = LSCPSERVER->LoadInstrument((yyvsp[(3) - (7)].String), (yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number), true); }
    break;

  case 156:
#line 294 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetEngineType((yyvsp[(1) - (3)].String), (yyvsp[(3) - (3)].Number)); }
    break;

  case 157:
#line 297 "lscp.y"
    { (yyval.LoadMode) = MidiInstrumentMapper::ON_DEMAND;      }
    break;

  case 158:
#line 298 "lscp.y"
    { (yyval.LoadMode) = MidiInstrumentMapper::ON_DEMAND_HOLD; }
    break;

  case 159:
#line 299 "lscp.y"
    { (yyval.LoadMode) = MidiInstrumentMapper::PERSISTENT;     }
    break;

  case 165:
#line 315 "lscp.y"
    { (yyval.Number) = 16; }
    break;

  case 172:
#line 334 "lscp.y"
    { (yyval.Dotnum) = (yyvsp[(1) - (1)].Number); }
    break;

  case 182:
#line 362 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (3)].String) + "," + (yyvsp[(3) - (3)].String); }
    break;

  case 185:
#line 367 "lscp.y"
    { std::stringstream ss; ss << "\'" << (yyvsp[(1) - (1)].Number) << "\'"; (yyval.String) = ss.str(); }
    break;

  case 186:
#line 368 "lscp.y"
    { std::stringstream ss; ss << "\'" << (yyvsp[(1) - (1)].Dotnum) << "\'"; (yyval.String) = ss.str(); }
    break;

  case 187:
#line 376 "lscp.y"
    { (yyval.Dotnum) = (yyvsp[(1) - (1)].Number); }
    break;

  case 188:
#line 377 "lscp.y"
    { (yyval.Dotnum) = -1; }
    break;

  case 189:
#line 380 "lscp.y"
    { std::string s; s = (yyvsp[(1) - (1)].Char); (yyval.String) = s; }
    break;

  case 190:
#line 381 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + (yyvsp[(2) - (2)].Char);                  }
    break;

  case 191:
#line 384 "lscp.y"
    { (yyval.Dotnum) = atof(String((yyvsp[(1) - (3)].String) + "." + (yyvsp[(3) - (3)].String)).c_str());                         }
    break;

  case 192:
#line 385 "lscp.y"
    { String s = "+"; s += (yyvsp[(2) - (4)].String); s += "."; s += (yyvsp[(4) - (4)].String); (yyval.Dotnum) = atof(s.c_str()); }
    break;

  case 193:
#line 386 "lscp.y"
    { (yyval.Dotnum) = atof(String("-" + (yyvsp[(2) - (4)].String) + "." + (yyvsp[(4) - (4)].String)).c_str());                   }
    break;

  case 194:
#line 390 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (1)].Char);      }
    break;

  case 195:
#line 391 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + (yyvsp[(2) - (2)].Char); }
    break;

  case 196:
#line 394 "lscp.y"
    { (yyval.Char) = '0'; }
    break;

  case 197:
#line 395 "lscp.y"
    { (yyval.Char) = '1'; }
    break;

  case 198:
#line 396 "lscp.y"
    { (yyval.Char) = '2'; }
    break;

  case 199:
#line 397 "lscp.y"
    { (yyval.Char) = '3'; }
    break;

  case 200:
#line 398 "lscp.y"
    { (yyval.Char) = '4'; }
    break;

  case 201:
#line 399 "lscp.y"
    { (yyval.Char) = '5'; }
    break;

  case 202:
#line 400 "lscp.y"
    { (yyval.Char) = '6'; }
    break;

  case 203:
#line 401 "lscp.y"
    { (yyval.Char) = '7'; }
    break;

  case 204:
#line 402 "lscp.y"
    { (yyval.Char) = '8'; }
    break;

  case 205:
#line 403 "lscp.y"
    { (yyval.Char) = '9'; }
    break;

  case 206:
#line 406 "lscp.y"
    { (yyval.Number) = atoi(String(1, (yyvsp[(1) - (1)].Char)).c_str());      }
    break;

  case 207:
#line 407 "lscp.y"
    { (yyval.Number) = atoi(String(String("1") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 208:
#line 408 "lscp.y"
    { (yyval.Number) = atoi(String(String("2") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 209:
#line 409 "lscp.y"
    { (yyval.Number) = atoi(String(String("3") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 210:
#line 410 "lscp.y"
    { (yyval.Number) = atoi(String(String("4") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 211:
#line 411 "lscp.y"
    { (yyval.Number) = atoi(String(String("5") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 212:
#line 412 "lscp.y"
    { (yyval.Number) = atoi(String(String("6") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 213:
#line 413 "lscp.y"
    { (yyval.Number) = atoi(String(String("7") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 214:
#line 414 "lscp.y"
    { (yyval.Number) = atoi(String(String("8") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 215:
#line 415 "lscp.y"
    { (yyval.Number) = atoi(String(String("9") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 216:
#line 417 "lscp.y"
    { (yyval.Char) = 'A'; }
    break;

  case 217:
#line 417 "lscp.y"
    { (yyval.Char) = 'B'; }
    break;

  case 218:
#line 417 "lscp.y"
    { (yyval.Char) = 'C'; }
    break;

  case 219:
#line 417 "lscp.y"
    { (yyval.Char) = 'D'; }
    break;

  case 220:
#line 417 "lscp.y"
    { (yyval.Char) = 'E'; }
    break;

  case 221:
#line 417 "lscp.y"
    { (yyval.Char) = 'F'; }
    break;

  case 222:
#line 417 "lscp.y"
    { (yyval.Char) = 'G'; }
    break;

  case 223:
#line 417 "lscp.y"
    { (yyval.Char) = 'H'; }
    break;

  case 224:
#line 417 "lscp.y"
    { (yyval.Char) = 'I'; }
    break;

  case 225:
#line 417 "lscp.y"
    { (yyval.Char) = 'J'; }
    break;

  case 226:
#line 417 "lscp.y"
    { (yyval.Char) = 'K'; }
    break;

  case 227:
#line 417 "lscp.y"
    { (yyval.Char) = 'L'; }
    break;

  case 228:
#line 417 "lscp.y"
    { (yyval.Char) = 'M'; }
    break;

  case 229:
#line 417 "lscp.y"
    { (yyval.Char) = 'N'; }
    break;

  case 230:
#line 417 "lscp.y"
    { (yyval.Char) = 'O'; }
    break;

  case 231:
#line 417 "lscp.y"
    { (yyval.Char) = 'P'; }
    break;

  case 232:
#line 417 "lscp.y"
    { (yyval.Char) = 'Q'; }
    break;

  case 233:
#line 417 "lscp.y"
    { (yyval.Char) = 'R'; }
    break;

  case 234:
#line 417 "lscp.y"
    { (yyval.Char) = 'S'; }
    break;

  case 235:
#line 417 "lscp.y"
    { (yyval.Char) = 'T'; }
    break;

  case 236:
#line 417 "lscp.y"
    { (yyval.Char) = 'U'; }
    break;

  case 237:
#line 417 "lscp.y"
    { (yyval.Char) = 'V'; }
    break;

  case 238:
#line 417 "lscp.y"
    { (yyval.Char) = 'W'; }
    break;

  case 239:
#line 417 "lscp.y"
    { (yyval.Char) = 'X'; }
    break;

  case 240:
#line 417 "lscp.y"
    { (yyval.Char) = 'Y'; }
    break;

  case 241:
#line 417 "lscp.y"
    { (yyval.Char) = 'Z'; }
    break;

  case 242:
#line 418 "lscp.y"
    { (yyval.Char) = 'a'; }
    break;

  case 243:
#line 418 "lscp.y"
    { (yyval.Char) = 'b'; }
    break;

  case 244:
#line 418 "lscp.y"
    { (yyval.Char) = 'c'; }
    break;

  case 245:
#line 418 "lscp.y"
    { (yyval.Char) = 'd'; }
    break;

  case 246:
#line 418 "lscp.y"
    { (yyval.Char) = 'e'; }
    break;

  case 247:
#line 418 "lscp.y"
    { (yyval.Char) = 'f'; }
    break;

  case 248:
#line 418 "lscp.y"
    { (yyval.Char) = 'g'; }
    break;

  case 249:
#line 418 "lscp.y"
    { (yyval.Char) = 'h'; }
    break;

  case 250:
#line 418 "lscp.y"
    { (yyval.Char) = 'i'; }
    break;

  case 251:
#line 418 "lscp.y"
    { (yyval.Char) = 'j'; }
    break;

  case 252:
#line 418 "lscp.y"
    { (yyval.Char) = 'k'; }
    break;

  case 253:
#line 418 "lscp.y"
    { (yyval.Char) = 'l'; }
    break;

  case 254:
#line 418 "lscp.y"
    { (yyval.Char) = 'm'; }
    break;

  case 255:
#line 418 "lscp.y"
    { (yyval.Char) = 'n'; }
    break;

  case 256:
#line 418 "lscp.y"
    { (yyval.Char) = 'o'; }
    break;

  case 257:
#line 418 "lscp.y"
    { (yyval.Char) = 'p'; }
    break;

  case 258:
#line 418 "lscp.y"
    { (yyval.Char) = 'q'; }
    break;

  case 259:
#line 418 "lscp.y"
    { (yyval.Char) = 'r'; }
    break;

  case 260:
#line 418 "lscp.y"
    { (yyval.Char) = 's'; }
    break;

  case 261:
#line 418 "lscp.y"
    { (yyval.Char) = 't'; }
    break;

  case 262:
#line 418 "lscp.y"
    { (yyval.Char) = 'u'; }
    break;

  case 263:
#line 418 "lscp.y"
    { (yyval.Char) = 'v'; }
    break;

  case 264:
#line 418 "lscp.y"
    { (yyval.Char) = 'w'; }
    break;

  case 265:
#line 418 "lscp.y"
    { (yyval.Char) = 'x'; }
    break;

  case 266:
#line 418 "lscp.y"
    { (yyval.Char) = 'y'; }
    break;

  case 267:
#line 418 "lscp.y"
    { (yyval.Char) = 'z'; }
    break;

  case 268:
#line 419 "lscp.y"
    { (yyval.Char) = '0'; }
    break;

  case 269:
#line 419 "lscp.y"
    { (yyval.Char) = '1'; }
    break;

  case 270:
#line 419 "lscp.y"
    { (yyval.Char) = '2'; }
    break;

  case 271:
#line 419 "lscp.y"
    { (yyval.Char) = '3'; }
    break;

  case 272:
#line 419 "lscp.y"
    { (yyval.Char) = '4'; }
    break;

  case 273:
#line 419 "lscp.y"
    { (yyval.Char) = '5'; }
    break;

  case 274:
#line 419 "lscp.y"
    { (yyval.Char) = '6'; }
    break;

  case 275:
#line 419 "lscp.y"
    { (yyval.Char) = '7'; }
    break;

  case 276:
#line 419 "lscp.y"
    { (yyval.Char) = '8'; }
    break;

  case 277:
#line 419 "lscp.y"
    { (yyval.Char) = '9'; }
    break;

  case 278:
#line 420 "lscp.y"
    { (yyval.Char) = '!'; }
    break;

  case 279:
#line 420 "lscp.y"
    { (yyval.Char) = '#'; }
    break;

  case 280:
#line 420 "lscp.y"
    { (yyval.Char) = '$'; }
    break;

  case 281:
#line 420 "lscp.y"
    { (yyval.Char) = '%'; }
    break;

  case 282:
#line 420 "lscp.y"
    { (yyval.Char) = '&'; }
    break;

  case 283:
#line 420 "lscp.y"
    { (yyval.Char) = '('; }
    break;

  case 284:
#line 420 "lscp.y"
    { (yyval.Char) = ')'; }
    break;

  case 285:
#line 420 "lscp.y"
    { (yyval.Char) = '*'; }
    break;

  case 286:
#line 420 "lscp.y"
    { (yyval.Char) = '+'; }
    break;

  case 287:
#line 420 "lscp.y"
    { (yyval.Char) = '-'; }
    break;

  case 288:
#line 420 "lscp.y"
    { (yyval.Char) = '.'; }
    break;

  case 289:
#line 420 "lscp.y"
    { (yyval.Char) = ','; }
    break;

  case 290:
#line 420 "lscp.y"
    { (yyval.Char) = '/'; }
    break;

  case 291:
#line 421 "lscp.y"
    { (yyval.Char) = ':'; }
    break;

  case 292:
#line 421 "lscp.y"
    { (yyval.Char) = ';'; }
    break;

  case 293:
#line 421 "lscp.y"
    { (yyval.Char) = '<'; }
    break;

  case 294:
#line 421 "lscp.y"
    { (yyval.Char) = '='; }
    break;

  case 295:
#line 421 "lscp.y"
    { (yyval.Char) = '>'; }
    break;

  case 296:
#line 421 "lscp.y"
    { (yyval.Char) = '?'; }
    break;

  case 297:
#line 421 "lscp.y"
    { (yyval.Char) = '@'; }
    break;

  case 298:
#line 422 "lscp.y"
    { (yyval.Char) = '['; }
    break;

  case 299:
#line 422 "lscp.y"
    { (yyval.Char) = '\\'; }
    break;

  case 300:
#line 422 "lscp.y"
    { (yyval.Char) = ']'; }
    break;

  case 301:
#line 422 "lscp.y"
    { (yyval.Char) = '^'; }
    break;

  case 302:
#line 422 "lscp.y"
    { (yyval.Char) = '_'; }
    break;

  case 303:
#line 423 "lscp.y"
    { (yyval.Char) = '{'; }
    break;

  case 304:
#line 423 "lscp.y"
    { (yyval.Char) = '|'; }
    break;

  case 305:
#line 423 "lscp.y"
    { (yyval.Char) = '}'; }
    break;

  case 306:
#line 423 "lscp.y"
    { (yyval.Char) = '~'; }
    break;

  case 307:
#line 424 "lscp.y"
    { (yyval.Char) = '\200'; }
    break;

  case 308:
#line 424 "lscp.y"
    { (yyval.Char) = '\201'; }
    break;

  case 309:
#line 424 "lscp.y"
    { (yyval.Char) = '\202'; }
    break;

  case 310:
#line 425 "lscp.y"
    { (yyval.Char) = '\203'; }
    break;

  case 311:
#line 425 "lscp.y"
    { (yyval.Char) = '\204'; }
    break;

  case 312:
#line 425 "lscp.y"
    { (yyval.Char) = '\205'; }
    break;

  case 313:
#line 426 "lscp.y"
    { (yyval.Char) = '\206'; }
    break;

  case 314:
#line 426 "lscp.y"
    { (yyval.Char) = '\207'; }
    break;

  case 315:
#line 426 "lscp.y"
    { (yyval.Char) = '\210'; }
    break;

  case 316:
#line 427 "lscp.y"
    { (yyval.Char) = '\211'; }
    break;

  case 317:
#line 427 "lscp.y"
    { (yyval.Char) = '\212'; }
    break;

  case 318:
#line 427 "lscp.y"
    { (yyval.Char) = '\213'; }
    break;

  case 319:
#line 428 "lscp.y"
    { (yyval.Char) = '\214'; }
    break;

  case 320:
#line 428 "lscp.y"
    { (yyval.Char) = '\215'; }
    break;

  case 321:
#line 428 "lscp.y"
    { (yyval.Char) = '\216'; }
    break;

  case 322:
#line 429 "lscp.y"
    { (yyval.Char) = '\217'; }
    break;

  case 323:
#line 429 "lscp.y"
    { (yyval.Char) = '\220'; }
    break;

  case 324:
#line 429 "lscp.y"
    { (yyval.Char) = '\221'; }
    break;

  case 325:
#line 430 "lscp.y"
    { (yyval.Char) = '\222'; }
    break;

  case 326:
#line 430 "lscp.y"
    { (yyval.Char) = '\223'; }
    break;

  case 327:
#line 430 "lscp.y"
    { (yyval.Char) = '\224'; }
    break;

  case 328:
#line 431 "lscp.y"
    { (yyval.Char) = '\225'; }
    break;

  case 329:
#line 431 "lscp.y"
    { (yyval.Char) = '\226'; }
    break;

  case 330:
#line 431 "lscp.y"
    { (yyval.Char) = '\227'; }
    break;

  case 331:
#line 432 "lscp.y"
    { (yyval.Char) = '\230'; }
    break;

  case 332:
#line 432 "lscp.y"
    { (yyval.Char) = '\231'; }
    break;

  case 333:
#line 432 "lscp.y"
    { (yyval.Char) = '\232'; }
    break;

  case 334:
#line 433 "lscp.y"
    { (yyval.Char) = '\233'; }
    break;

  case 335:
#line 433 "lscp.y"
    { (yyval.Char) = '\234'; }
    break;

  case 336:
#line 433 "lscp.y"
    { (yyval.Char) = '\235'; }
    break;

  case 337:
#line 434 "lscp.y"
    { (yyval.Char) = '\236'; }
    break;

  case 338:
#line 434 "lscp.y"
    { (yyval.Char) = '\237'; }
    break;

  case 339:
#line 434 "lscp.y"
    { (yyval.Char) = '\240'; }
    break;

  case 340:
#line 435 "lscp.y"
    { (yyval.Char) = '\241'; }
    break;

  case 341:
#line 435 "lscp.y"
    { (yyval.Char) = '\242'; }
    break;

  case 342:
#line 435 "lscp.y"
    { (yyval.Char) = '\243'; }
    break;

  case 343:
#line 436 "lscp.y"
    { (yyval.Char) = '\244'; }
    break;

  case 344:
#line 436 "lscp.y"
    { (yyval.Char) = '\245'; }
    break;

  case 345:
#line 436 "lscp.y"
    { (yyval.Char) = '\246'; }
    break;

  case 346:
#line 437 "lscp.y"
    { (yyval.Char) = '\247'; }
    break;

  case 347:
#line 437 "lscp.y"
    { (yyval.Char) = '\250'; }
    break;

  case 348:
#line 437 "lscp.y"
    { (yyval.Char) = '\251'; }
    break;

  case 349:
#line 438 "lscp.y"
    { (yyval.Char) = '\252'; }
    break;

  case 350:
#line 438 "lscp.y"
    { (yyval.Char) = '\253'; }
    break;

  case 351:
#line 438 "lscp.y"
    { (yyval.Char) = '\254'; }
    break;

  case 352:
#line 439 "lscp.y"
    { (yyval.Char) = '\255'; }
    break;

  case 353:
#line 439 "lscp.y"
    { (yyval.Char) = '\256'; }
    break;

  case 354:
#line 439 "lscp.y"
    { (yyval.Char) = '\257'; }
    break;

  case 355:
#line 440 "lscp.y"
    { (yyval.Char) = '\260'; }
    break;

  case 356:
#line 440 "lscp.y"
    { (yyval.Char) = '\261'; }
    break;

  case 357:
#line 440 "lscp.y"
    { (yyval.Char) = '\262'; }
    break;

  case 358:
#line 441 "lscp.y"
    { (yyval.Char) = '\263'; }
    break;

  case 359:
#line 441 "lscp.y"
    { (yyval.Char) = '\264'; }
    break;

  case 360:
#line 441 "lscp.y"
    { (yyval.Char) = '\265'; }
    break;

  case 361:
#line 442 "lscp.y"
    { (yyval.Char) = '\266'; }
    break;

  case 362:
#line 442 "lscp.y"
    { (yyval.Char) = '\267'; }
    break;

  case 363:
#line 442 "lscp.y"
    { (yyval.Char) = '\270'; }
    break;

  case 364:
#line 443 "lscp.y"
    { (yyval.Char) = '\271'; }
    break;

  case 365:
#line 443 "lscp.y"
    { (yyval.Char) = '\272'; }
    break;

  case 366:
#line 443 "lscp.y"
    { (yyval.Char) = '\273'; }
    break;

  case 367:
#line 444 "lscp.y"
    { (yyval.Char) = '\274'; }
    break;

  case 368:
#line 444 "lscp.y"
    { (yyval.Char) = '\275'; }
    break;

  case 369:
#line 444 "lscp.y"
    { (yyval.Char) = '\276'; }
    break;

  case 370:
#line 445 "lscp.y"
    { (yyval.Char) = '\277'; }
    break;

  case 371:
#line 445 "lscp.y"
    { (yyval.Char) = '\300'; }
    break;

  case 372:
#line 445 "lscp.y"
    { (yyval.Char) = '\301'; }
    break;

  case 373:
#line 446 "lscp.y"
    { (yyval.Char) = '\302'; }
    break;

  case 374:
#line 446 "lscp.y"
    { (yyval.Char) = '\303'; }
    break;

  case 375:
#line 446 "lscp.y"
    { (yyval.Char) = '\304'; }
    break;

  case 376:
#line 447 "lscp.y"
    { (yyval.Char) = '\305'; }
    break;

  case 377:
#line 447 "lscp.y"
    { (yyval.Char) = '\306'; }
    break;

  case 378:
#line 447 "lscp.y"
    { (yyval.Char) = '\307'; }
    break;

  case 379:
#line 448 "lscp.y"
    { (yyval.Char) = '\310'; }
    break;

  case 380:
#line 448 "lscp.y"
    { (yyval.Char) = '\311'; }
    break;

  case 381:
#line 448 "lscp.y"
    { (yyval.Char) = '\312'; }
    break;

  case 382:
#line 449 "lscp.y"
    { (yyval.Char) = '\313'; }
    break;

  case 383:
#line 449 "lscp.y"
    { (yyval.Char) = '\314'; }
    break;

  case 384:
#line 449 "lscp.y"
    { (yyval.Char) = '\315'; }
    break;

  case 385:
#line 450 "lscp.y"
    { (yyval.Char) = '\316'; }
    break;

  case 386:
#line 450 "lscp.y"
    { (yyval.Char) = '\317'; }
    break;

  case 387:
#line 450 "lscp.y"
    { (yyval.Char) = '\320'; }
    break;

  case 388:
#line 451 "lscp.y"
    { (yyval.Char) = '\321'; }
    break;

  case 389:
#line 451 "lscp.y"
    { (yyval.Char) = '\322'; }
    break;

  case 390:
#line 451 "lscp.y"
    { (yyval.Char) = '\323'; }
    break;

  case 391:
#line 452 "lscp.y"
    { (yyval.Char) = '\324'; }
    break;

  case 392:
#line 452 "lscp.y"
    { (yyval.Char) = '\325'; }
    break;

  case 393:
#line 452 "lscp.y"
    { (yyval.Char) = '\326'; }
    break;

  case 394:
#line 453 "lscp.y"
    { (yyval.Char) = '\327'; }
    break;

  case 395:
#line 453 "lscp.y"
    { (yyval.Char) = '\330'; }
    break;

  case 396:
#line 453 "lscp.y"
    { (yyval.Char) = '\331'; }
    break;

  case 397:
#line 454 "lscp.y"
    { (yyval.Char) = '\332'; }
    break;

  case 398:
#line 454 "lscp.y"
    { (yyval.Char) = '\333'; }
    break;

  case 399:
#line 454 "lscp.y"
    { (yyval.Char) = '\334'; }
    break;

  case 400:
#line 455 "lscp.y"
    { (yyval.Char) = '\335'; }
    break;

  case 401:
#line 455 "lscp.y"
    { (yyval.Char) = '\336'; }
    break;

  case 402:
#line 455 "lscp.y"
    { (yyval.Char) = '\337'; }
    break;

  case 403:
#line 456 "lscp.y"
    { (yyval.Char) = '\340'; }
    break;

  case 404:
#line 456 "lscp.y"
    { (yyval.Char) = '\341'; }
    break;

  case 405:
#line 456 "lscp.y"
    { (yyval.Char) = '\342'; }
    break;

  case 406:
#line 457 "lscp.y"
    { (yyval.Char) = '\343'; }
    break;

  case 407:
#line 457 "lscp.y"
    { (yyval.Char) = '\344'; }
    break;

  case 408:
#line 457 "lscp.y"
    { (yyval.Char) = '\345'; }
    break;

  case 409:
#line 458 "lscp.y"
    { (yyval.Char) = '\346'; }
    break;

  case 410:
#line 458 "lscp.y"
    { (yyval.Char) = '\347'; }
    break;

  case 411:
#line 458 "lscp.y"
    { (yyval.Char) = '\350'; }
    break;

  case 412:
#line 459 "lscp.y"
    { (yyval.Char) = '\351'; }
    break;

  case 413:
#line 459 "lscp.y"
    { (yyval.Char) = '\352'; }
    break;

  case 414:
#line 459 "lscp.y"
    { (yyval.Char) = '\353'; }
    break;

  case 415:
#line 460 "lscp.y"
    { (yyval.Char) = '\354'; }
    break;

  case 416:
#line 460 "lscp.y"
    { (yyval.Char) = '\355'; }
    break;

  case 417:
#line 460 "lscp.y"
    { (yyval.Char) = '\356'; }
    break;

  case 418:
#line 461 "lscp.y"
    { (yyval.Char) = '\357'; }
    break;

  case 419:
#line 461 "lscp.y"
    { (yyval.Char) = '\360'; }
    break;

  case 420:
#line 461 "lscp.y"
    { (yyval.Char) = '\361'; }
    break;

  case 421:
#line 462 "lscp.y"
    { (yyval.Char) = '\362'; }
    break;

  case 422:
#line 462 "lscp.y"
    { (yyval.Char) = '\363'; }
    break;

  case 423:
#line 462 "lscp.y"
    { (yyval.Char) = '\364'; }
    break;

  case 424:
#line 463 "lscp.y"
    { (yyval.Char) = '\365'; }
    break;

  case 425:
#line 463 "lscp.y"
    { (yyval.Char) = '\366'; }
    break;

  case 426:
#line 463 "lscp.y"
    { (yyval.Char) = '\367'; }
    break;

  case 427:
#line 464 "lscp.y"
    { (yyval.Char) = '\370'; }
    break;

  case 428:
#line 464 "lscp.y"
    { (yyval.Char) = '\371'; }
    break;

  case 429:
#line 464 "lscp.y"
    { (yyval.Char) = '\372'; }
    break;

  case 430:
#line 465 "lscp.y"
    { (yyval.Char) = '\373'; }
    break;

  case 431:
#line 465 "lscp.y"
    { (yyval.Char) = '\374'; }
    break;

  case 432:
#line 465 "lscp.y"
    { (yyval.Char) = '\375'; }
    break;

  case 433:
#line 466 "lscp.y"
    { (yyval.Char) = '\376'; }
    break;

  case 434:
#line 466 "lscp.y"
    { (yyval.Char) = '\377'; }
    break;

  case 435:
#line 469 "lscp.y"
    { (yyval.String) = " ";      }
    break;

  case 437:
#line 471 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + " "; }
    break;

  case 438:
#line 472 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + (yyvsp[(2) - (2)].String);  }
    break;

  case 439:
#line 475 "lscp.y"
    { (yyval.String) = (yyvsp[(2) - (3)].String); }
    break;

  case 440:
#line 476 "lscp.y"
    { (yyval.String) = (yyvsp[(2) - (3)].String); }
    break;


/* Line 1267 of yacc.c.  */
#line 5280 "y.tab.c"
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


#line 728 "lscp.y"


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

