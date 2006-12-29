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
#define YYLAST   4418

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  227
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  137
/* YYNRULES -- Number of rules.  */
#define YYNRULES  524
/* YYNRULES -- Number of states.  */
#define YYNSTATES  1634

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
     483,   491,   503,   507,   511,   517,   521,   527,   531,   537,
     545,   549,   553,   557,   561,   565,   571,   575,   579,   585,
     593,   599,   609,   615,   621,   627,   633,   639,   645,   651,
     657,   663,   669,   673,   679,   681,   683,   685,   687,   689,
     691,   693,   695,   699,   703,   705,   709,   715,   723,   727,
     729,   731,   733,   735,   737,   739,   741,   743,   745,   747,
     749,   751,   753,   755,   757,   759,   761,   763,   765,   767,
     769,   771,   773,   775,   777,   781,   783,   785,   787,   789,
     791,   793,   795,   798,   802,   807,   812,   814,   817,   819,
     821,   823,   825,   827,   829,   831,   833,   835,   837,   839,
     842,   845,   848,   851,   854,   857,   860,   863,   866,   868,
     870,   872,   874,   876,   878,   880,   882,   884,   886,   888,
     890,   892,   894,   896,   898,   900,   902,   904,   906,   908,
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
    1311,  1314,  1318,  1322,  1324,  1326,  1328,  1332,  1336,  1340,
    1346,  1352,  1359,  1367,  1372,  1377,  1381,  1386,  1394,  1404,
    1411,  1415,  1425,  1437,  1444,  1452,  1470,  1501,  1510,  1515,
    1541,  1566,  1590,  1613,  1639,  1664,  1686,  1707,  1721,  1734,
    1746,  1759,  1771,  1789,  1811,  1822,  1829,  1839,  1854,  1865,
    1895,  1916,  1936,  1966,  1986,  2017,  2038,  2056,  2085,  2113,
    2139,  2158,  2176,  2204,  2220,  2237,  2257,  2278,  2296,  2312,
    2331,  2347,  2358,  2366,  2375,  2382,  2389,  2394,  2399,  2405,
    2416,  2422,  2436,  2441,  2446
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
      -1,   354,    -1,   328,   282,   278,   282,   274,     4,   271,
      -1,   333,   282,   278,   282,   278,   282,   274,     4,   271,
      -1,   337,   282,   278,   282,   274,     4,   271,    -1,   338,
     282,   278,   282,   278,   282,   274,     4,   271,    -1,   303,
     282,   245,    -1,   344,   282,   361,   282,   258,   282,   268,
      -1,   351,   282,   334,   282,   263,   282,   265,   282,   253,
     282,   253,    -1,   362,   282,   273,    -1,   354,   282,   262,
      -1,   330,   282,   274,   282,   246,    -1,   330,   282,   274,
      -1,   340,   282,   274,   282,   246,    -1,   340,   282,   274,
      -1,   351,   282,   263,   282,   261,    -1,   351,   282,   263,
     282,   261,   282,   270,    -1,   303,   282,   263,    -1,   343,
     282,   258,    -1,   343,   282,   294,    -1,   330,   282,   278,
      -1,   340,   282,   278,    -1,   351,   282,   263,   282,   265,
      -1,   323,   282,   249,    -1,   324,   282,   250,    -1,   330,
     282,   263,   282,   252,    -1,   334,   282,   263,   282,   253,
     282,   253,    -1,   335,   282,   263,   282,   254,    -1,   350,
     282,   263,   282,   252,   282,   255,   282,   256,    -1,   340,
     282,   263,   282,   252,    -1,   347,   282,   263,   282,   255,
      -1,   348,   282,   263,   282,   256,    -1,   349,   282,   263,
     282,   257,    -1,   354,   282,   263,   282,   262,    -1,   355,
     282,   263,   282,   273,    -1,   356,   282,   263,   282,   273,
      -1,   344,   282,   263,   282,   258,    -1,   344,   282,   263,
     282,   295,    -1,   344,   282,   263,   282,   296,    -1,   274,
       4,   271,    -1,   246,   282,   274,     4,   271,    -1,   357,
      -1,   358,    -1,   329,    -1,   339,    -1,   306,    -1,   304,
      -1,   336,    -1,   305,    -1,   343,   282,   258,    -1,   343,
     282,   294,    -1,   345,    -1,   352,   282,   263,    -1,   267,
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
      27,    89,    27,    32,    34,    39,    38,    -1,    24,    42,
      89,    37,    23,    32,    22,    -1,    24,    42,    89,    37,
      23,    32,    22,    37,    -1,    37,    23,    36,    40,    23,
      36,    -1,    40,    33,    30,    39,    31,    23,    -1,    31,
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
     226,   227,   228,   229,   232,   233,   234,   235,   236,   237,
     240,   243,   244,   247,   248,   249,   252,   253,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   272,   273,   276,   277,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   292,   293,   296,   299,
     300,   301,   304,   307,   310,   313,   316,   317,   320,   323,
     326,   329,   332,   335,   336,   339,   342,   345,   348,   351,
     354,   357,   360,   363,   364,   367,   368,   369,   370,   378,
     379,   382,   383,   386,   387,   388,   392,   393,   396,   397,
     398,   399,   400,   401,   402,   403,   404,   405,   408,   409,
     410,   411,   412,   413,   414,   415,   416,   417,   419,   419,
     419,   419,   419,   419,   419,   419,   419,   419,   419,   419,
     419,   419,   419,   419,   419,   419,   419,   419,   419,   419,
     419,   419,   419,   419,   420,   420,   420,   420,   420,   420,
     420,   420,   420,   420,   420,   420,   420,   420,   420,   420,
     420,   420,   420,   420,   420,   420,   420,   420,   420,   420,
     421,   421,   421,   421,   421,   421,   421,   421,   421,   421,
     422,   422,   422,   422,   422,   422,   422,   422,   422,   422,
     422,   422,   422,   423,   423,   423,   423,   423,   423,   423,
     424,   424,   424,   424,   424,   425,   425,   425,   425,   426,
     426,   426,   427,   427,   427,   428,   428,   428,   429,   429,
     429,   430,   430,   430,   431,   431,   431,   432,   432,   432,
     433,   433,   433,   434,   434,   434,   435,   435,   435,   436,
     436,   436,   437,   437,   437,   438,   438,   438,   439,   439,
     439,   440,   440,   440,   441,   441,   441,   442,   442,   442,
     443,   443,   443,   444,   444,   444,   445,   445,   445,   446,
     446,   446,   447,   447,   447,   448,   448,   448,   449,   449,
     449,   450,   450,   450,   451,   451,   451,   452,   452,   452,
     453,   453,   453,   454,   454,   454,   455,   455,   455,   456,
     456,   456,   457,   457,   457,   458,   458,   458,   459,   459,
     459,   460,   460,   460,   461,   461,   461,   462,   462,   462,
     463,   463,   463,   464,   464,   464,   465,   465,   465,   466,
     466,   466,   467,   467,   467,   468,   468,   471,   472,   473,
     474,   477,   478,   484,   487,   490,   493,   496,   499,   502,
     505,   508,   511,   514,   517,   520,   523,   526,   529,   532,
     535,   538,   541,   544,   547,   550,   553,   556,   559,   562,
     565,   568,   571,   574,   577,   580,   583,   586,   589,   592,
     595,   598,   601,   604,   607,   610,   613,   616,   619,   622,
     625,   628,   631,   634,   637,   640,   643,   646,   649,   652,
     655,   658,   661,   664,   667,   670,   673,   676,   679,   682,
     685,   688,   691,   694,   697,   700,   703,   706,   709,   712,
     715,   718,   721,   724,   727
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
     238,   238,   238,   238,   238,   239,   239,   239,   239,   239,
     239,   239,   239,   239,   240,   240,   240,   240,   240,   240,
     241,   242,   242,   243,   243,   243,   244,   244,   245,   245,
     245,   245,   245,   245,   245,   245,   245,   245,   245,   245,
     245,   245,   246,   246,   247,   247,   248,   248,   248,   248,
     248,   248,   248,   248,   248,   248,   249,   249,   250,   251,
     251,   251,   252,   253,   254,   255,   256,   256,   257,   258,
     259,   260,   261,   262,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   271,   272,   272,   272,   272,   273,
     273,   274,   274,   275,   275,   275,   276,   276,   277,   277,
     277,   277,   277,   277,   277,   277,   277,   277,   278,   278,
     278,   278,   278,   278,   278,   278,   278,   278,   279,   279,
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
     279,   279,   279,   279,   279,   279,   279,   280,   280,   280,
     280,   281,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,   354,   355,   356,   357,   358,
     359,   360,   361,   362,   363
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
       7,    11,     3,     3,     5,     3,     5,     3,     5,     7,
       3,     3,     3,     3,     3,     5,     3,     3,     5,     7,
       5,     9,     5,     5,     5,     5,     5,     5,     5,     5,
       5,     5,     3,     5,     1,     1,     1,     1,     1,     1,
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
      24,    23,    22,    25,    24,    21,    20,    13,    12,    11,
      12,    11,    17,    21,    10,     6,     9,    14,    10,    29,
      20,    19,    29,    19,    30,    20,    17,    28,    27,    25,
      18,    17,    27,    15,    16,    19,    20,    17,    15,    18,
      15,    10,     7,     8,     6,     6,     4,     4,     5,    10,
       5,    13,     4,     4,     4
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
       0,     0,     0,     0,     0,     0,     1,   444,   445,     2,
       0,     9,   296,   291,   290,   288,   289,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   280,
     282,   283,   284,   285,   286,   287,   292,   293,   294,   295,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
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
     443,    12,   208,    11,   191,    10,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   446,     0,     0,     0,   447,     0,     0,   448,     0,
       0,     0,     0,   460,     0,     0,     0,     3,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   209,   196,
     210,   211,   212,   213,   214,   215,   216,   217,   281,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   192,
       0,     0,    13,    30,    31,     0,     0,     0,     0,     0,
       0,     0,     0,    16,     0,    71,    76,    88,    95,    96,
       0,    80,     0,     0,     0,     0,     0,    72,     0,    81,
       0,     0,     0,     0,     0,   100,     0,     0,     0,     0,
       0,   104,     0,    14,     0,    15,     0,     0,    27,     0,
       0,     0,     0,    17,     0,     0,     0,    18,     0,     0,
       0,     0,     0,     0,     0,    19,   149,   151,   148,   146,
     150,   147,     0,   154,     0,     0,    20,     0,     0,    21,
       0,     0,     0,     0,     0,    22,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    23,    33,    34,    35,    36,    42,    43,    44,
      45,    37,    41,    40,    39,    38,    47,    46,    24,    48,
      49,    50,    51,    57,    58,    59,    60,    52,    56,    55,
      54,    53,    62,    61,   438,    25,   437,    26,     0,     0,
       0,     0,   453,   454,   524,     0,     0,     0,     0,     0,
       0,   197,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   440,   439,     0,   450,
       0,     0,     0,   520,     0,     0,   449,     0,     0,     0,
       0,     0,    32,   180,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   199,   200,
     201,   202,   203,   204,   205,   206,   207,     0,    97,   169,
      98,     0,     0,     0,     0,   102,   175,    94,     0,     0,
       0,     0,   121,   122,     0,     0,     0,   115,   117,     0,
     123,   124,     0,     0,     0,     0,     0,   152,   153,   155,
       0,     0,   126,     0,   179,     0,   127,     0,   178,    68,
      69,    70,     0,     0,     0,     0,     0,     0,   109,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   113,   173,     0,   196,   174,   112,   190,   189,     0,
       0,     0,     0,     0,     0,     0,     0,   120,   451,     0,
     459,   463,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   523,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   452,     0,     0,     0,     0,
     441,   442,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    89,     0,     0,     0,   144,   145,    91,    92,
      93,    82,     0,    77,     0,     0,     0,    83,     0,     0,
     455,   101,    73,     0,     0,     0,     0,   170,     0,     0,
       0,     0,     0,   114,     0,   116,   118,   172,   125,   177,
       0,     0,     0,     0,     0,     0,     0,   176,     0,   158,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   193,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   485,     0,     0,   514,     0,   515,
     468,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   516,   517,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   522,     0,     0,     0,   194,   195,     0,     0,
       0,     0,     0,     0,     0,     0,   461,     0,   464,     0,
       0,     0,   464,   512,     0,     0,     0,     0,    90,    78,
       0,    86,     0,    74,     0,    84,   103,     0,     0,   171,
      67,     0,     0,   512,     0,     0,   288,   289,   142,   183,
     185,   188,   187,   186,   119,   182,     0,     0,     0,     0,
       0,     0,   156,     0,     0,     0,     0,     0,   128,   162,
       0,   163,   130,   164,   132,     0,     0,   139,   140,   141,
     133,   165,   134,   166,   167,   135,   168,     0,   136,   137,
     138,   105,     0,   107,     0,   110,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     467,   513,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   462,     0,     0,     0,
       0,     0,     0,   518,     0,    79,    87,    85,    75,    99,
       0,     0,     0,     0,     0,   143,   184,     0,     0,     0,
       0,     0,   157,     0,     0,     0,     0,   129,     0,     0,
       0,   106,   108,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     484,     0,     0,     0,     0,     0,     0,   456,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   458,     0,
       0,     0,     0,     0,   131,     0,   111,     0,   479,     0,
       0,     0,     0,     0,     0,     0,   481,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   511,
       0,     0,     0,     0,   478,     0,     0,     0,   480,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   457,     0,     0,   477,     0,     0,
     521,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   519,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   508,   503,     0,   503,    63,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   504,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   465,     0,   501,   507,     0,     0,
     482,     0,     0,    64,    65,   181,   159,   160,   161,     0,
     501,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     508,   510,     0,     0,     0,     0,     0,   482,     0,     0,
       0,     0,     0,     0,   500,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   505,     0,   491,   493,
       0,     0,     0,     0,   505,     0,     0,     0,    66,   491,
       0,     0,     0,     0,     0,     0,   496,     0,     0,     0,
       0,     0,     0,     0,   495,   490,     0,     0,     0,     0,
       0,   506,     0,     0,     0,     0,     0,     0,     0,   509,
       0,     0,     0,     0,   476,     0,     0,     0,     0,     0,
       0,     0,   483,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   475,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   495,     0,     0,     0,   472,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   471,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   470,     0,
     474,     0,     0,     0,     0,     0,   499,   486,     0,     0,
       0,   469,   473,     0,     0,     0,     0,     0,     0,   488,
       0,     0,     0,     0,     0,     0,   502,     0,     0,   498,
       0,     0,     0,   497,     0,     0,     0,   492,     0,     0,
     489,   494,   466,   487
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    13,    14,    15,    16,   342,   442,   458,   383,   385,
     419,   353,   425,   393,   477,   388,   397,   416,   668,   853,
     825,   405,   652,   656,  1423,  1038,  1040,  1042,  1050,  1052,
    1055,   618,   846,  1008,   856,   691,   625,   866,   858,   657,
     653,   582,  1424,  1024,  1018,  1019,   696,  1020,  1021,   693,
     272,   626,   274,   475,  1023,   939,    49,    50,    17,    18,
      19,    20,    21,    22,    23,    24,    25,  1054,  1048,  1049,
     655,    26,    27,    28,    29,    30,   343,   355,   356,   357,
     594,   443,   444,   445,   446,   447,   448,   449,   450,   451,
     452,   453,   454,   455,   358,   359,   417,   360,  1426,  1427,
    1428,   427,   361,   362,   363,   364,   365,   366,   671,   367,
     429,   368,   369,   370,   371,   372,   373,   344,   375,   376,
     377,   675,   676,   677,   378,   379,   380,   381,   679,   680,
     826,   827,    31,   457,   686,   434,    32
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -1041
static const yytype_int16 yypact[] =
{
      42, -1041, -1041,   126,    57,    66,    97,   110,   188,   118,
     186,   106,   184,   223,    26,  1999, -1041,    16,    16,    16,
      16,    16,    16,    16,    16,    16,    16,    16,    16,    16,
      16,    16, -1041,   232,   246,   277,   222,   284,   267,   309,
     304,   314,   152,    88,   322,   204, -1041, -1041, -1041, -1041,
     119, -1041, -1041, -1041, -1041, -1041, -1041, -1041,   279,   279,
     279,   279,   279,   279,   279,   279,   279, -1041, -1041, -1041,
   -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041,
   -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041,
   -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041,
   -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041,
   -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041,
   -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041,
   -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041,
   -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041,
   -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041,
   -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041,
   -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041,
   -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041,
   -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041,
   -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041,
   -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041,
   -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041,
   -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041,
   -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041,
   -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041,
   -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041,
   -1041,  2664, -1041, -1041, -1041, -1041,   200,   104,   312,   312,
     315,   189,   189,   132,   165,   200,   115,    93,    93,  2221,
     331, -1041,   335,   341,   328, -1041,   330,   350, -1041,   337,
     340,   353,   354, -1041,   345,   367,   348, -1041, -1041, -1041,
   -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041,   279, -1041,
     279,   279,   279,   279,   279,   279,   279,   279, -1041, -1041,
   -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041,
     362,   363, -1041, -1041,    16,   225,   365,   360,   351,   368,
     371,   374,   375, -1041,    16, -1041, -1041, -1041, -1041, -1041,
      16, -1041,    16,    16,    16,    16,    16, -1041,    16, -1041,
      16,    16,    16,    16,    16, -1041,    16,    16,    16,    16,
      16, -1041,   369, -1041,    16, -1041,    16,   373, -1041,    16,
     359,   378,   377, -1041,    16,    16,    16, -1041,    16,    16,
      16,   266,   383,   394,   410, -1041, -1041, -1041, -1041, -1041,
   -1041, -1041,    16, -1041,    16,   406, -1041,    16,    16, -1041,
      16,    16,   401,   380,   414, -1041,    16,    16,    16,    16,
      16,    16,    16,    16,    16,   403,   404,   384,   417,   407,
     428,   429, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041,
   -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041,
   -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041,
   -1041, -1041, -1041, -1041,  2664,  2221, -1041, -1041,    16,   430,
     426,   444, -1041, -1041, -1041,   425,   443,   461,   462,   451,
     467, -1041,   470,   468,    98,   469,   473,   474,   471,   408,
     476,   459,   465,   472,   127,   477,   477,   477,   477,   477,
     477,   477,   477,   477,   477,   536,   477,   477,   477,   477,
     619,   477,   478,   619,   619,   483,   536,   484,   418,   486,
    2664,  2664,   619,   619,   619,   619,   489,   480,   424,   492,
     536,   619,   481,    24,  2664,   619,   536,   493,   495,   500,
     121,   619,   619,   619,   619,   491,   505,   440,  2883,   503,
     504,   508,    53,   494,   496,   502,  2664, -1041,   619, -1041,
     510,   498,   512, -1041,   518,   506, -1041,   499,   509,   530,
    2221,  2221, -1041, -1041,   531,   532,   528,   534,   525,   537,
     523,   548,   538,   546,    16,    16,    16,    16,    16,    16,
      16,    16,    16,    16,    16,    16,    16,    16,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   563, -1041, -1041,
   -1041,    16,    16,    16,    16, -1041, -1041, -1041,   567,    16,
      16,   568, -1041, -1041,   569,   573,   584,  2221,  2221,    16,
   -1041, -1041,    16,   585,   581,   580,   591, -1041, -1041, -1041,
     582,   586, -1041,    16, -1041,    16, -1041,    16,  2664, -1041,
   -1041, -1041,   594,   592,   599,   600,   167,   610, -1041,    16,
      16,    16,    16,    16,    16,    16,    16,    16,    16,    16,
      16,    16,    16,    16,    16,   625,    16,   606,    16,   279,
     279, -1041, -1041,   187,    31, -1041, -1041,  2664, -1041,   620,
     622,   616,   624,   631,   647,   653,   654, -1041, -1041,   633,
   -1041, -1041,   650,   659,   642,   593,  1555,  1777,   648,   655,
     651,   652,   663,   598,   665,   660,   658,   668,   619,    75,
     619,   619,  2664,   619,  2664,  2664,   619,   619,   619,   619,
    2664,   619,   664,   619,  2664,   619,   619,   604,   619,   619,
     607,   662,   674,   609,  2664,  2664,   619,   619,   666,   671,
     677,   615,   669,   675,   619,    98,   619,   673, -1041,   621,
     686,   687,   676,   681,   619,   619,   619,   619,   619,   619,
     619,   619,   619,   619,   619,   619,  2664,   619,  2664,   619,
     682,   619,   690,   619,   301,   416,   279,   683,   692,   685,
     629,   697,   702,   698,   707, -1041,   712,   700,   710,   711,
   -1041, -1041,   656,   718,   716,   717,   709,   719,   708,   670,
     724,   715, -1041,   706,   728,    16, -1041, -1041, -1041, -1041,
   -1041, -1041,  2221,  2664,    16,    16,    16, -1041,  2221,    16,
   -1041, -1041,  2664,    16,    16,   725,    16, -1041,    16,   730,
     672,   726,   733,    16,  3102,    16,    16, -1041, -1041, -1041,
     678,   739,   731,   737,   727,   679,    16, -1041,    16, -1041,
     680,   738,   743,   744,   749,   741,    16,    16,    16,    16,
      16,    16,    16,    16,    16,    16,    16,    16,  3321,    16,
    3540,    16,   753,    16,   751,    16,   279,   279,   279,   691,
     745,   756,   755,   754,   757,   701,   703,   763,   760,   759,
     761,   758,   774,   766, -1041,   776,   767, -1041,   762, -1041,
   -1041,   765,   764,   619,  2664,   619,   619,   619,  2664,   619,
     619,   619,   769,   619,   619,   772,   773,   783,   775,  2664,
    2443,    98,   778,   779,   786,   780,   782,   784,   619,   619,
     781,   790,   785,   736, -1041, -1041,   619,   619,  2664,   619,
      89,   619,   536,  2664,   619,   440,  2883,  2883,  2443,  2664,
    2443,  2664, -1041,    98,   793,   619,   279,   279,   794,   746,
     800,   802,   806,   748,   792,   795, -1041,   818, -1041,   803,
     804,   809,   805,   807,   196,   812,   823,   826, -1041,  2221,
      16, -1041,    16,  2221,    16, -1041, -1041,   811,    16, -1041,
   -1041,   813,   810, -1041,   825,  3759,   279,   279,   847, -1041,
    2664, -1041, -1041, -1041, -1041, -1041,   821,   805,   807,   229,
     850,   844, -1041,    16,   840,   236,   798,   854, -1041, -1041,
      16, -1041, -1041,  2664, -1041,   859,   851, -1041, -1041, -1041,
   -1041, -1041, -1041, -1041, -1041, -1041,  2664,    16, -1041, -1041,
   -1041,   847,  3978,   847,  4197, -1041,   799,    16,   852,   865,
     801,   242,   864,   871,   860,   861,   872,   858,   863,   874,
   -1041, -1041,   866,   868,   875,   862,   880,  2664,  2664,  2664,
    2664,   619,   869,  2664,   870,   883,   879,  2443,  2443,   884,
     885,   889,   877,   876,   619,   891,   892,   890,   878,   619,
     908,   901,   619,  2443,  2443,   905,   619,   902,   914,    67,
     910,   906,   923,   924,   931,   920, -1041,   926,   929,   815,
     922,   928,   944, -1041,   934,    16,  2664,  2664,    16, -1041,
     932,    16,   933,   936,   935,   847, -1041,   937,   940,   938,
     941,   948, -1041,   946,   943,   947,   265, -1041,   953,   952,
      16,   847,   847,   951,    16,   949,   961,   959,   950,   958,
     962,   974,   960,   979,   969,   963,   964,   191,   918,   970,
     987,   973,   975,    98,   976,   977,   930,   978,   939,   981,
   -1041,   982,   984,   942,   983,   985,   988, -1041,   536,   991,
     619,   993,   996,   994,   989,   945,   997,  1002,   998,  1014,
    1000,  1008,  1003,  1001,  1011,  1019,   193,  1016,   965,  1029,
    1020,    16,  1022,  1018,  1038,  1023,  1040,  1032, -1041,  1026,
     195,  1031,  1028,  1037, -1041,  1034, -1041,  1041, -1041,  1043,
    1036,  1048,  1045,  1033,  1042,   992, -1041,  1055,   999,  1060,
    1061,  1063,    61,  1054,  1066,  1069,  1067,  1068,   619,  1070,
    1005,  1073,  1012,  1074,  1080,  1015,  1083,  1075,  1071,  1024,
    1076,  1072,  1027,  1077, -1041,  1086,  1089,  1081, -1041,  1096,
    1087,   302,  1093,  1094,  1095,  1084,  1098,  1091,  1097,  1090,
    1105,  1099,    16,  1100,  1108,  1101,  1111,  1102,  1103,   305,
    1104,  1107,  1109,   128, -1041,  1110,  1112, -1041,  1106,  1118,
   -1041,  1119,  1113,  1114,    96,  1120,  1122,  1047,  1128,  1116,
    1121,  1123,  1124, -1041,  1126,   440,  1127,  1115,  1130,  1135,
    1133,  1129,  1136,  1143,  1141,  1131,  1050,  1144,  1138,  1132,
    1085,  1149,  1146,  1139,  1137,  1125,  1159,  1142,  1152,  1134,
    1160,  1158,  1166,  1165,  1140,    28,  1157, -1041,    16,  1153,
    1151,  1171,  1154,  1172,    33,  1176,  1161,  1179,  1140,    70,
    1178,  1167,  1168,  1184,  1169,  1186,  1145,  1180,  1182,  1183,
    1190,  1170,  1188,  1174,  1192,  1199,  1189,  1193, -1041,  1195,
    1197,    49,  1201,  1207,  1204,  1210,  1205,  1206,  1212,  1217,
    1215,  1200,  1213,  1208,  1219,  1220,  1225,   205,  1211,  1232,
    1221,  1233,  1234,  1216, -1041,  1222,  1224,  1173,  1239,  1240,
    1175,  1231,  1242,    16, -1041, -1041, -1041, -1041, -1041,  1245,
   -1041,  1246,  1224,  1249,  1237,  1250,  1181,  1253,  1241,  1244,
   -1041, -1041,  1257,  1185,  1247,  1251,  1263, -1041,  1252,  1261,
    1264,  1254,  1255,  1256, -1041,  1258,  1260,  1265,  1266,  1202,
    1262,    98,  1271,  1277,  1267,  1279,  1280,  1270,  1273,  1283,
    1284,  1285,   138,  1274,  1286,  1275, -1041,  1259,  1278,  1223,
    1282,  1276,  1269,  1298,  1281,  1300,  1299,  1287, -1041, -1041,
    1278,  1281,  1290,  1236,  1303,  1291, -1041,  1296,  1238,  1295,
    1297,  1301,  1302,  1243,  1248, -1041,  1304,  1292,  1268,  1294,
    1305, -1041,  1306,  1311,  1312,  1248,  1307,  1308,  1317, -1041,
     197,  1310,  1318,  1309, -1041,   216,  1316,  1326,  1313,  1324,
    1333,  1332, -1041,  1325,  1321,  1340,  1341,  1331,  1329,  1334,
    1335,  1330, -1041,  1336,  1338,  1345,  1337,  1288,  1339,  1343,
    1327,  1349,  1342,  1346,  1347, -1041,  1344,  1348,  1351, -1041,
    1352,  1355,  1350,  1357,  1359,  1358,  1361,  1364,  1362,  1367,
    1374,  1372,  1365,  1363, -1041,  1366,  1368,  1380,  1369,  1370,
    1371,  1375,  1373,  1382,  1378,  1376,  1377,  1379, -1041,  1381,
   -1041,  1383,  1389,  1391,  1393,  1397, -1041,  1353,  1385,  1398,
    1401, -1041, -1041,  1402,  1388,  1392,  1400,  1403,  1408, -1041,
    1390,  1404,  1399,  1406,  1415,  1407, -1041,  1410,  1418, -1041,
    1422,  1411,  1412, -1041,  1416,  1413,  1414, -1041,  1417,  1429,
   -1041, -1041, -1041, -1041
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041,
   -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041, -1041,  -720,
   -1041, -1041, -1041, -1041, -1041,  -774, -1040, -1041,    25,   173,
   -1041,  -466,  -690,  -872, -1041,  -936,  -307,  -918,  -860,  -715,
    -737,   432,   -59, -1041,  -902,   355,  -636,   464,  -530,   -11,
     -40,   -14,   217,  -248,  -457,   -15,  1405, -1041, -1041, -1041,
   -1041, -1041, -1041, -1041, -1041, -1041, -1041,  -430, -1041, -1041,
   -1041, -1041, -1041, -1041, -1041, -1041,   -99,  1177,  1187,  1191,
    -337,  1164,  1194,  1196,  1198,  1203,  1209,  1214,  1218,  1226,
    1227,  -246,  -244,  -242,    47, -1041, -1041,  1228, -1041, -1041,
   -1041, -1041,  1230,  -249, -1041, -1041,  1235,  -308, -1041,  1272,
   -1041,  1492,  1716,  -241, -1041,    58,   -30,  -247,  1938, -1041,
     907, -1041, -1041, -1041,   -37,  1939, -1041,  -252, -1041, -1041,
   -1041, -1041, -1041,  1229, -1041, -1041, -1041
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -209
static const yytype_int16 yytable[] =
{
     275,   273,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   830,   319,   319,
     319,   319,   319,   319,   319,   319,   319,   692,   868,  1058,
     374,  1033,   394,   398,   433,   855,  -208,   583,   421,   431,
     395,   399,   469,     1,   470,     2,   471,   318,   320,   321,
     322,   323,   324,   325,   326,   327,   651,   629,   630,   848,
     632,     3,  1010,     4,     5,  1388,  1061,     6,  1063,  1157,
    1388,  1006,     7,     8,   647,   702,  1164,     9,    10,    11,
     660,    12,  1421,  1422,  1285,   620,   654,    34,  1167,    36,
     703,  1400,  1327,    35,  1168,   823,   633,  1286,   308,   608,
     609,   610,   611,   612,   613,   614,   615,   616,  1401,   824,
     648,  1045,   435,   436,   437,  1067,   661,  1389,   302,  1347,
      37,  1046,  1396,   345,   438,   346,   303,   347,   348,    43,
     439,   440,  1348,   441,   422,   349,   340,    38,   423,   391,
     665,   350,   351,    39,   352,    44,   424,   436,    33,  1337,
    1261,   401,   666,   402,   593,   352,   403,    41,   667,  1499,
    1236,   352,  1338,   404,   439,  1500,  1339,   441,   598,   599,
     600,   601,   602,   603,   604,   605,   606,   607,   354,   621,
     622,   623,   624,   300,   627,  1044,   420,   426,   347,   301,
    1057,   478,   415,   796,   771,  1145,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   772,    40,   390,    42,
    1213,  1161,  1162,   391,  1214,  1252,    45,  1266,  1538,  1139,
     392,   340,  1215,    46,  1539,   639,  1444,  1253,   642,  1267,
    1082,   341,  1445,  1083,   649,   305,  1446,  1543,   659,  1004,
     270,   306,   670,  1544,   396,   400,   580,   581,   688,   432,
     389,    47,    48,   412,   291,  -208,  -208,  -208,   595,   294,
     596,   707,   597,  1100,   495,   496,  1101,    -4,    -4,   292,
    1106,   580,   581,  1077,   476,   839,  1120,   841,   491,  1121,
     491,   491,   491,   491,   491,   491,   491,   491,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   678,  1195,
     293,   669,  1077,   673,   296,   536,   496,   896,   654,   672,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     580,   581,   295,  1313,  1314,   893,  1332,  1333,   297,   494,
    1059,  1060,   716,   717,   456,   472,   384,   386,   298,   504,
    1292,   299,   304,   382,    47,   505,   387,   506,   507,   508,
     509,   510,   340,   511,   479,   512,   513,   514,   515,   516,
     480,   517,   518,   519,   520,   521,   481,  1135,   482,   523,
    1138,   524,   483,   485,   526,   484,   486,   487,  1141,   530,
     531,   532,   488,   533,   534,   535,   489,   490,   492,  1358,
     493,   497,   498,   499,   501,   500,   522,   540,   527,   541,
     525,   548,   543,   544,   529,   545,   546,   502,   503,   537,
     561,   550,   551,   552,   553,   554,   555,   556,   557,   558,
     528,   822,   897,   828,   829,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   692,   538,   539,   542,   844,
     547,   549,   559,   560,   562,   563,  1221,   689,   690,   308,
     608,   609,   610,   611,   612,   613,   614,   615,   616,   869,
     567,   564,   565,   568,   570,   572,   569,   876,   877,   878,
     879,   880,   881,   882,   883,   884,   885,   886,   887,   271,
     571,   573,   574,   575,  1025,   576,   895,   577,   339,   578,
     579,   584,   585,   586,  1047,   590,   587,   588,   589,   644,
     628,   619,   592,   591,   593,   631,   634,   635,   636,   619,
     619,   643,   619,   645,   646,   662,   583,   694,   650,   640,
     641,   663,   664,   685,   687,   699,   619,   701,   700,   706,
     704,   709,   619,   708,   705,   710,   713,   681,   682,   683,
     684,   714,   712,   695,   698,   308,   608,   609,   610,   611,
     612,   613,   614,   615,   616,   617,   711,   715,   718,   719,
     720,   721,   722,   724,   723,   476,   476,   725,   319,   319,
     319,   319,   319,   319,   319,   319,   319,   726,   727,   728,
     729,   730,   731,   732,   733,   734,   735,   736,   737,   738,
     739,   740,   741,   742,   747,   750,   751,   318,   320,   321,
     322,   323,   324,   325,   326,   327,   743,   744,   745,   746,
     752,   753,   758,   759,   748,   749,   998,   760,   761,   763,
     762,   767,   754,   755,   756,   768,   769,   757,   308,   608,
     609,   610,   611,   612,   613,   614,   615,   616,   764,   770,
     765,  1032,   766,   773,   790,   792,   798,   797,   799,   319,
     319,   800,   801,   491,   774,   775,   776,   777,   778,   779,
     780,   781,   782,   783,   784,   785,   786,   787,   788,   789,
     802,   791,   803,   793,   808,   804,   805,   806,   794,   795,
     807,   812,   809,   814,   815,   813,   816,   817,   818,   820,
     819,   339,   821,   845,   840,   850,   849,   851,   852,   860,
     862,   567,   567,   861,   863,   864,   870,   865,   872,   873,
     871,   875,   894,   892,   874,   900,   899,   901,   902,   831,
     903,   904,   834,   835,   836,   837,   654,   619,   905,   619,
     906,   843,   907,   909,   847,   847,   908,   912,   910,   913,
     914,   915,   857,   859,   917,   911,   916,   919,   920,   921,
     867,   922,   932,   474,   491,   491,   319,   935,   937,   918,
     938,   936,   943,   944,   945,   951,   946,   942,   947,   950,
     952,   953,   954,   889,   955,   891,   972,   619,   974,   980,
     978,   979,   981,   339,   982,   898,   986,   987,   983,   988,
     984,   990,   985,   989,   991,   692,   992,  1152,   993,   994,
     997,  1007,   995,   996,  1011,  1013,  1012,  1014,  1028,  1027,
     923,  1026,  1029,  1030,  1034,  1031,  1075,   924,  1036,   925,
     926,   927,  1035,   928,   929,  1037,  1066,  1068,   930,   931,
    1070,   933,  1074,   934,  1071,  1069,  1072,  1073,  1076,  1079,
    1077,   941,  1080,  1078,  1081,  1084,  1085,  1086,  1092,  1095,
    1094,   948,  1098,   949,   339,   339,   319,   319,   491,  1096,
    1099,   956,   957,   958,   959,   960,   961,   962,   963,   964,
     965,   966,   967,  1102,   969,   339,   971,  1103,   973,  1105,
     975,  1108,  1110,  1122,  1111,   976,   977,  1107,  1115,  1118,
    1119,  1117,  1123,  1124,  1125,  1126,  1127,  1129,  1151,  1133,
     694,  1128,  1132,  1134,  1177,  1130,  1131,  1140,  1142,  1150,
    1156,  1000,  1001,  1002,   339,   847,  1005,   859,  1144,  1009,
    1009,  1143,  1147,  1155,  1148,   694,  1022,  1149,   694,  1153,
     694,  1154,  1158,  1159,  1425,   867,   491,   491,  1163,   566,
    1165,  1166,  1039,  1041,  1170,  1039,   619,  1051,  1053,  1169,
    1039,   695,   698,   698,  1022,  1171,  1022,  1172,  1173,  1174,
    1178,   859,  1175,  1176,  1179,  1180,  1181,  1191,  1182,  1184,
    1185,  1187,  1196,  1186,  1189,  1197,   319,   319,  1188,  1190,
    1192,  1193,  1204,  1201,  1087,  1088,  1194,  1089,  1090,  1091,
    1199,  1202,  1203,  1093,   637,   638,  1205,  1207,  1206,  1208,
    1209,  1210,  1211,  1212,  1425,   794,   795,  1216,   658,  1217,
    1218,  1219,  1228,  1240,  1220,  1222,  1223,  1225,  1104,  1224,
    1227,  1231,   697,  1229,  1232,  1109,  1238,  1233,  1226,  1235,
    1244,  1230,  1237,  1239,  1241,  1243,  1242,  1245,  1246,  1247,
    1249,  1248,  1112,  1250,   474,   474,  1251,  1254,  1256,   339,
     339,  1257,  1116,  1259,  1255,   339,  1260,   694,   694,   339,
    1261,  1262,  1263,  1264,  1265,  1268,  1269,  1270,  1271,  1274,
    1275,   339,  1277,   694,   694,  1273,  1276,  1009,  1280,  1272,
    1278,  1279,  1282,  1022,  1022,  1284,  1283,  1287,  1281,  1288,
    1289,  1291,  1290,  1293,  1294,  1041,  1295,  1297,  1051,  1022,
    1022,  1296,  1041,  1298,  1299,   339,  1300,   339,  1301,  1308,
    1302,  1305,  1309,  1303,  1304,  1307,  1306,  1311,  1310,  1312,
    1315,  1316,  1317,  1322,  1318,  1319,  1183,  1320,  1323,  1321,
    1327,  1324,  1326,  1329,  1341,  1331,  1351,  1160,  1360,  1369,
    1346,  1328,  1330,  1335,  1334,  1198,  1342,  1336,  1340,  1200,
    1343,  1345,  1344,  1349,  1350,  1352,  1353,  1361,  1362,  1354,
    1363,  1355,  1365,  1356,  1357,  1359,  1366,  1364,  1367,  1368,
    1370,  1371,  1374,  1375,  1373,  1372,  1377,  1376,  1379,  1381,
     566,   566,  1380,  1383,  1053,  1384,  1041,  1385,  1386,  1390,
    1388,  1392,  1393,  1395,  1394,  1397,   658,  1402,   832,   833,
    1399,  1398,  1404,  1403,   838,  1400,  1258,  1406,   842,  1405,
    1412,  1414,  1408,  1409,  1378,  1410,   339,  1411,   854,   854,
     339,  1413,  1416,  1382,  1415,  1417,  1419,  1418,  1429,  1387,
    1430,  1431,   339,  1432,  1407,  1420,  1433,   339,  1434,  1435,
    1436,  1437,  1441,  1438,   867,  1439,  1440,  1442,  1443,  1447,
     888,  1448,   890,  1449,  1450,  1452,  1453,  1451,  1456,  1457,
     339,  1454,  1455,  1459,  1458,  1460,  1462,  1463,  1464,  1465,
    1467,  1466,  1468,   339,  1472,  1469,  1470,  1325,  1471,   339,
    1473,   339,  1475,  1474,  1477,   694,  1476,  1478,  1509,  1504,
    1479,  1486,  1482,  1480,  1489,  1481,  1483,  1485,  1487,  1484,
    1490,  1491,  1492,  1493,  1494,  1495,  1496,  1497,  1498,  1503,
    1502,   695,  1506,  1501,  1508,  1505,  1507,  1510,  1511,  1512,
    1515,  1513,  1517,  1518,  1514,  1516,  1519,  1520,  1521,  1522,
    1530,  1528,  1525,  1523,  1533,  1524,  1531,  1526,  1527,  1534,
    1537,  1535,  1541,  1391,  1536,  1546,  1548,  1542,  1532,  1540,
    1545,  1547,  1549,   339,   339,  1550,  1551,  1529,  1552,  1553,
    1554,  1555,  1556,  1559,  1562,  1567,  1557,  1558,  1568,  1560,
    1561,  1234,  1573,  1563,  1566,  1565,  1578,  1564,  1571,  1576,
    1569,  1579,  1570,  1572,  1581,  1580,  1577,  1582,   999,  1574,
    1584,  1575,  1003,  1585,  1583,  1586,  1588,  1587,  1589,  1591,
    1592,  1590,  1488,  1015,  1597,  1065,  1593,  1599,  1461,  1596,
    1598,  1594,  1604,  1595,  1603,  1600,  1606,  1601,  1605,  1602,
    1607,  1610,  1043,  1609,  1611,  1612,  1613,  1056,  1618,  1621,
     697,   697,  1614,  1062,  1617,  1064,  1615,  1620,  1622,  1616,
    1619,  1625,  1608,  1624,  1623,  1626,  1629,  1627,  1628,  1630,
    1631,  1633,   459,  1146,  1632,   307,     0,   674,     0,     0,
     406,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     407,     0,     0,     0,   408,     0,     0,     0,     0,     0,
       0,     0,   460,     0,   461,     0,   462,     0,     0,     0,
       0,   463,     0,     0,     0,     0,     0,   464,     0,     0,
       0,     0,   465,     0,     0,     0,   466,     0,     0,     0,
       0,     0,   418,   409,   467,   468,     0,   473,     0,     0,
       0,   428,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   854,  1136,  1137,   854,   410,     0,   658,   328,    52,
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
     263,   264,   265,   266,   267,   268,   269,   810,   430,   270,
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
     261,   262,   263,   264,   265,   266,   267,   268,   269,   411,
     811,   270,    51,    52,    53,    54,    55,    56,    57,    58,
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
     269,   413,   414,   270,   328,    52,    53,    54,    55,    56,
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
     267,   268,   269,     0,     0,   270,   328,    52,    53,    54,
    1016,  1017,    57,    58,    59,    60,    61,    62,    63,    64,
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
     265,   266,   267,   268,   269,   580,   581,   328,    52,    53,
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
     264,   265,   266,   267,   268,   269,   328,    52,    53,    54,
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
     265,   266,   267,   268,   269,   328,   940,    53,    54,    55,
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
     266,   267,   268,   269,   328,   968,    53,    54,    55,    56,
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
     267,   268,   269,   328,   970,    53,    54,    55,    56,   329,
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
     268,   269,   328,  1097,    53,    54,    55,    56,   329,   330,
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
     269,   328,  1113,    53,    54,    55,    56,   329,   330,   331,
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
     328,  1114,    53,    54,    55,    56,   329,   330,   331,   332,
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
     261,   262,   263,   264,   265,   266,   267,   268,   269
};

static const yytype_int16 yycheck[] =
{
      15,    15,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,   732,    58,    59,
      60,    61,    62,    63,    64,    65,    66,   557,   765,   965,
     277,   949,   281,   282,   286,   755,     5,   494,   285,   286,
     281,   282,   288,     1,   288,     3,   288,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    32,   523,   524,   749,
     526,    19,   934,    21,    22,    37,   968,    25,   970,  1109,
      37,   931,    30,    31,   540,    22,  1116,    35,    36,    37,
     546,    39,    33,    34,    23,   515,   543,    30,    21,    23,
      37,    21,    22,    36,    27,    20,   526,    36,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    38,    34,
     540,    22,    19,    20,    21,   975,   546,    89,    30,    23,
      23,    32,    89,    19,    31,    21,    38,    23,    24,    23,
      37,    38,    36,    40,    19,    31,    21,    27,    23,    24,
      19,    37,    38,    33,    40,    39,    31,    20,    22,    21,
      22,    19,    31,    21,    27,    40,    24,    39,    37,    21,
    1200,    40,    34,    31,    37,    27,    38,    40,   505,   506,
     507,   508,   509,   510,   511,   512,   513,   514,   277,   516,
     517,   518,   519,    31,   521,   959,   285,   286,    23,    37,
     964,   290,    27,     6,    27,  1097,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    39,    19,    19,    23,
      19,  1113,  1114,    24,    23,    22,    32,    22,    21,  1091,
      31,    21,    31,     0,    27,   532,    21,    34,   535,    34,
      34,    31,    27,    37,   541,    31,    31,    21,   545,   929,
     224,    37,   550,    27,   281,   282,   222,   223,   556,   286,
     280,   225,   226,   283,    22,   224,   225,   226,   504,    37,
     504,   568,   504,    34,    39,    40,    37,   225,   226,    23,
      34,   222,   223,    37,   289,   741,    34,   743,   318,    37,
     320,   321,   322,   323,   324,   325,   326,   327,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,   550,    34,
      23,   550,    37,   550,    37,    39,    40,     6,   765,   550,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
     222,   223,    38,    21,    22,   791,    21,    22,    19,   344,
     966,   967,   580,   581,   287,   288,   278,   279,    34,   354,
    1258,    27,    20,    31,   225,   360,    31,   362,   363,   364,
     365,   366,    21,   368,    19,   370,   371,   372,   373,   374,
      19,   376,   377,   378,   379,   380,    38,  1087,    38,   384,
    1090,   386,    22,    33,   389,    38,    23,    23,  1093,   394,
     395,   396,    37,   398,   399,   400,    19,    39,    26,  1325,
      27,    26,    32,    42,    23,    27,    27,   412,    39,   414,
      27,    21,   417,   418,    27,   420,   421,    33,    33,    26,
      26,   426,   427,   428,   429,   430,   431,   432,   433,   434,
      42,   728,     6,   730,   731,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,   965,    42,    27,    32,   746,
      39,    27,    39,    39,    27,    38,  1183,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,   766,
     475,    33,    33,   478,    38,    40,    36,   774,   775,   776,
     777,   778,   779,   780,   781,   782,   783,   784,   785,    15,
      36,    38,    21,    21,   941,    34,   793,    20,   271,    19,
      22,    22,    19,    19,   960,    36,    25,    89,    22,    19,
      22,   515,    30,    38,    27,    22,    22,    89,    22,   523,
     524,    22,   526,    89,    22,    22,   973,   557,    37,   533,
     534,    26,    22,    32,    19,    22,   540,    19,    24,    27,
      36,    33,   546,    23,    38,    23,    37,   551,   552,   553,
     554,    32,    36,   557,   558,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    38,    27,    27,    27,
      32,    27,    37,    40,    27,   580,   581,    19,   608,   609,
     610,   611,   612,   613,   614,   615,   616,    39,    32,   594,
     595,   596,   597,   598,   599,   600,   601,   602,   603,   604,
     605,   606,   607,    30,    27,    27,    27,   608,   609,   610,
     611,   612,   613,   614,   615,   616,   621,   622,   623,   624,
      37,    27,    27,    32,   629,   630,   923,    37,    27,    33,
      38,    27,   637,   638,   639,    33,    27,   642,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,   653,    39,
     655,   948,   657,    33,    19,    39,    24,    27,    32,   689,
     690,    27,    21,   693,   669,   670,   671,   672,   673,   674,
     675,   676,   677,   678,   679,   680,   681,   682,   683,   684,
      23,   686,    19,   688,    32,    21,    43,    27,   689,   690,
      21,    33,    89,    32,    32,    30,    23,    89,    23,    31,
      30,   474,    24,    89,    30,    33,    89,    23,    89,    33,
      23,   716,   717,    32,    89,    36,    33,    32,    22,    22,
      89,    30,    22,    31,    38,    23,    33,    32,    89,   733,
      23,    19,   736,   737,   738,   739,  1183,   741,    30,   743,
      23,   745,    20,    23,   748,   749,    36,    19,    27,    23,
      23,    32,   756,   757,    36,    89,    27,    23,    33,    43,
     764,    23,    27,   289,   794,   795,   796,    27,    32,    89,
      27,    89,    23,    32,    27,    27,    39,    89,    89,    89,
      27,    27,    23,   787,    33,   789,    23,   791,    27,    23,
      89,    36,    27,   566,    30,   796,    23,    27,    31,    30,
      89,    33,    89,    32,    20,  1325,    30,  1104,    22,    32,
      36,    32,    40,    38,    32,    22,    33,    32,    22,    30,
     825,    33,    32,    31,    33,    31,    21,   832,    33,   834,
     835,   836,    32,   838,   839,    89,    33,    33,   843,   844,
      30,   846,    40,   848,    32,    89,    30,    89,    20,    30,
      37,   856,    37,    39,    37,    33,    23,    21,    37,    39,
      37,   866,     5,   868,   637,   638,   896,   897,   898,    34,
      39,   876,   877,   878,   879,   880,   881,   882,   883,   884,
     885,   886,   887,    23,   889,   658,   891,    33,   893,    39,
     895,    27,    23,    19,    33,   896,   897,    89,    89,    24,
      89,    39,    21,    33,    33,    23,    38,    23,    22,    37,
     940,    38,    27,    23,    89,    39,    38,    38,    38,    32,
      32,   925,   926,   927,   697,   929,   930,   931,    39,   933,
     934,    38,    38,    33,    39,   965,   940,    38,   968,    38,
     970,    39,    24,    32,  1391,   949,   976,   977,    33,   475,
      38,    27,   956,   957,    38,   959,   960,   961,   962,    39,
     964,   965,   966,   967,   968,    32,   970,    33,    27,    39,
      38,   975,    36,    34,    36,    21,    32,    19,    36,    36,
      34,    34,    19,    38,    36,    23,  1016,  1017,    38,    38,
      34,    38,    32,    34,   999,  1000,    39,  1002,  1003,  1004,
      39,    30,    33,  1008,   530,   531,    38,    23,    36,    39,
      21,    32,    39,    39,  1461,  1016,  1017,    89,   544,    39,
      23,    38,    30,    24,    39,    39,    39,    39,  1033,    89,
      39,    38,   558,    39,    39,  1040,    30,    39,    89,    38,
      32,    89,    39,    39,    89,    33,    39,    23,    38,    31,
      39,    38,  1057,    32,   580,   581,    27,    31,    19,   832,
     833,    31,  1067,    31,    89,   838,    38,  1097,  1098,   842,
      22,    38,    22,    31,    38,    34,    38,    30,    34,    33,
      22,   854,    39,  1113,  1114,    32,    31,  1091,    23,    38,
      38,    89,    22,  1097,  1098,    22,    25,    33,    89,    23,
      21,    23,    25,    23,    89,  1109,    23,    23,  1112,  1113,
    1114,    89,  1116,    23,    89,   888,    23,   890,    33,    23,
      39,    39,    23,    89,    38,    38,    89,    21,    37,    32,
      27,    27,    27,    33,    40,    27,  1141,    36,    23,    32,
      22,    32,    32,    22,    22,    32,    89,  1112,    23,    89,
      26,    40,    40,    36,    40,  1160,    40,    38,    38,  1164,
      32,    38,    33,    33,    32,    27,    40,    27,    23,    38,
      27,    38,    26,    39,    38,    38,    23,    38,    27,    38,
      26,    33,    23,    27,    89,    43,    39,    38,    19,    27,
     716,   717,    40,    23,  1198,    27,  1200,    21,    23,    32,
      37,    40,    21,    21,    40,    19,   732,    19,   734,   735,
      21,    40,    34,    36,   740,    21,  1221,    21,   744,    40,
      40,    37,    32,    31,    89,    32,   999,    27,   754,   755,
    1003,    33,    23,    89,    32,    36,    31,    34,    27,    89,
      23,    27,  1015,    23,    89,    38,    31,  1020,    32,    27,
      23,    26,    23,    43,  1258,    32,    38,    27,    23,    38,
     786,    19,   788,    32,    21,    39,    34,    23,    19,    19,
    1043,    37,    89,    32,    89,    23,    21,    21,    19,    32,
      89,    21,    19,  1056,    89,    34,    32,  1292,    21,  1062,
      33,  1064,    19,    32,    23,  1325,    34,    23,    19,    30,
      36,    89,    34,    38,    23,    39,    36,    31,    36,    34,
      23,    34,    23,    23,    34,    32,    23,    23,    23,    34,
      24,  1325,    89,    39,    38,    37,    34,    19,    37,    19,
      30,    22,    19,    32,    37,    89,    30,    89,    33,    32,
      36,    39,    89,    32,    23,    33,    31,    89,    34,    27,
      23,    34,    24,  1358,    36,    19,    22,    38,    42,    39,
      34,    38,    19,  1136,  1137,    23,    31,    89,    37,    19,
      19,    30,    33,    33,    19,    38,    32,    32,    19,    33,
      32,  1198,    24,    36,    31,    36,    19,    89,    31,    24,
      38,    22,    36,    39,    23,    27,    36,    23,   924,    38,
      23,    39,   928,    19,    32,    23,    33,    32,    32,    19,
      31,    33,  1461,   939,    22,   973,    36,    31,  1423,    36,
      32,    40,    23,    38,    31,    38,    23,    38,    27,    38,
      23,    23,   958,    38,    23,    23,    38,   963,    38,    23,
     966,   967,    40,   969,    26,   971,    36,    38,    23,    36,
      36,    23,    89,    33,    37,    23,    30,    36,    36,    36,
      36,    22,   288,  1098,    37,    50,    -1,   550,    -1,    -1,
     283,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     283,    -1,    -1,    -1,   283,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   288,    -1,   288,    -1,   288,    -1,    -1,    -1,
      -1,   288,    -1,    -1,    -1,    -1,    -1,   288,    -1,    -1,
      -1,    -1,   288,    -1,    -1,    -1,   288,    -1,    -1,    -1,
      -1,    -1,   284,   283,   288,   288,    -1,   288,    -1,    -1,
      -1,   286,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1087,  1088,  1089,  1090,   283,    -1,  1093,     3,     4,
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
     215,   216,   217,   218,   219,   220,   221,   222,   286,   224,
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
     213,   214,   215,   216,   217,   218,   219,   220,   221,   283,
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
     221,   283,   283,   224,     3,     4,     5,     6,     7,     8,
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
     219,   220,   221,    -1,    -1,   224,     3,     4,     5,     6,
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
     213,   214,   215,   216,   217,   218,   219,   220,   221
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
      37,    38,    40,   238,   303,   304,   305,   306,   321,   322,
     324,   329,   330,   331,   332,   333,   334,   336,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   351,   352,
     353,   354,    31,   235,   342,   236,   342,    31,   242,   343,
      19,    24,    31,   240,   330,   340,   351,   243,   330,   340,
     351,    19,    21,    24,    31,   248,   304,   305,   306,   329,
     336,   339,   343,   345,   352,    27,   244,   323,   324,   237,
     303,   344,    19,    23,    31,   239,   303,   328,   333,   337,
     338,   344,   351,   354,   362,    19,    20,    21,    31,    37,
      38,    40,   233,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   360,   234,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   360,   274,   280,   282,   241,   303,    19,
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
     334,   335,   340,   344,   347,   348,   349,   350,   354,   355,
     356,   278,   278,   278,   278,    32,   361,    19,   334,     7,
       8,   262,   275,   276,   277,   278,   273,   274,   278,    22,
      24,    19,    22,    37,    36,    38,    27,   263,    23,    33,
      23,    38,    36,    37,    32,    27,   280,   280,    27,    27,
      32,    27,    37,    27,    40,    19,    39,    32,   282,   282,
     282,   282,   282,   282,   282,   282,   282,   282,   282,   282,
     282,   282,    30,   282,   282,   282,   282,    27,   282,   282,
      27,    27,    37,    27,   282,   282,   282,   282,    27,    32,
      37,    27,    38,    33,   282,   282,   282,    27,    33,    27,
      39,    27,    39,    33,   282,   282,   282,   282,   282,   282,
     282,   282,   282,   282,   282,   282,   282,   282,   282,   282,
      19,   282,    39,   282,   276,   276,     6,    27,    24,    32,
      27,    21,    23,    19,    21,    43,    27,    21,    32,    89,
     222,   223,    33,    30,    32,    32,    23,    89,    23,    30,
      31,    24,   263,    20,    34,   247,   357,   358,   263,   263,
     266,   278,   274,   274,   278,   278,   278,   278,   274,   258,
      30,   258,   274,   278,   263,    89,   259,   278,   259,    89,
      33,    23,    89,   246,   274,   246,   261,   278,   265,   278,
      33,    32,    23,    89,    36,    32,   264,   278,   267,   263,
      33,    89,    22,    22,    38,    30,   263,   263,   263,   263,
     263,   263,   263,   263,   263,   263,   263,   263,   274,   278,
     274,   278,    31,   258,    22,   263,     6,     6,   276,    33,
      23,    32,    89,    23,    19,    30,    23,    20,    36,    23,
      27,    89,    19,    23,    23,    32,    27,    36,    89,    23,
      33,    43,    23,   282,   282,   282,   282,   282,   282,   282,
     282,   282,    27,   282,   282,    27,    89,    32,    27,   282,
       4,   282,    89,    23,    32,    27,    39,    89,   282,   282,
      89,    27,    27,    27,    23,    33,   282,   282,   282,   282,
     282,   282,   282,   282,   282,   282,   282,   282,     4,   282,
       4,   282,    23,   282,    27,   282,   276,   276,    89,    36,
      23,    27,    30,    31,    89,    89,    23,    27,    30,    32,
      33,    20,    30,    22,    32,    40,    38,    36,   263,   274,
     278,   278,   278,   274,   259,   278,   265,    32,   260,   278,
     260,    32,    33,    22,    32,   274,     7,     8,   271,   272,
     274,   275,   278,   281,   270,   281,    33,    30,    22,    32,
      31,    31,   263,   264,    33,    32,    33,    89,   252,   278,
     253,   278,   254,   274,   252,    22,    32,   258,   295,   296,
     255,   278,   256,   278,   294,   257,   274,   252,   262,   273,
     273,   271,   274,   271,   274,   268,    33,   265,    33,    89,
      30,    32,    30,    89,    40,    21,    20,    37,    39,    30,
      37,    37,    34,    37,    33,    23,    21,   282,   282,   282,
     282,   282,    37,   282,    37,    39,    34,     4,     5,    39,
      34,    37,    23,    33,   282,    39,    34,    89,    27,   282,
      23,    33,   282,     4,     4,    89,   282,    39,    24,    89,
      34,    37,    19,    21,    33,    33,    23,    38,    38,    23,
      39,    38,    27,    37,    23,   246,   274,   274,   246,   260,
      38,   266,    38,    38,    39,   271,   272,    38,    39,    38,
      32,    22,   263,    38,    39,    33,    32,   253,    24,    32,
     255,   271,   271,    33,   253,    38,    27,    21,    27,    39,
      38,    32,    33,    27,    39,    36,    34,    89,    38,    36,
      21,    32,    36,   282,    36,    34,    38,    34,    38,    36,
      38,    19,    34,    38,    39,    34,    19,    23,   282,    39,
     282,    34,    30,    33,    32,    38,    36,    23,    39,    21,
      32,    39,    39,    19,    23,    31,    89,    39,    23,    38,
      39,   267,    39,    39,    89,    39,    89,    39,    30,    39,
      89,    38,    39,    39,   256,    38,   253,    39,    30,    39,
      24,    89,    39,    33,    32,    23,    38,    31,    38,    39,
      32,    27,    22,    34,    31,    89,    19,    31,   282,    31,
      38,    22,    38,    22,    31,    38,    22,    34,    34,    38,
      30,    34,    38,    32,    33,    22,    31,    39,    38,    89,
      23,    89,    22,    25,    22,    23,    36,    33,    23,    21,
      25,    23,   264,    23,    89,    23,    89,    23,    23,    89,
      23,    33,    39,    89,    38,    39,    89,    38,    23,    23,
      37,    21,    32,    21,    22,    27,    27,    27,    40,    27,
      36,    32,    33,    23,    32,   282,    32,    22,    40,    22,
      40,    32,    21,    22,    40,    36,    38,    21,    34,    38,
      38,    22,    40,    32,    33,    38,    26,    23,    36,    33,
      32,    89,    27,    40,    38,    38,    39,    38,   262,    38,
      23,    27,    23,    27,    38,    26,    23,    27,    38,    89,
      26,    33,    43,    89,    23,    27,    38,    39,    89,    19,
      40,    27,    89,    23,    27,    21,    23,    89,    37,    89,
      32,   282,    40,    21,    40,    21,    89,    19,    40,    21,
      21,    38,    19,    36,    34,    40,    21,    89,    32,    31,
      32,    27,    40,    33,    37,    32,    23,    36,    34,    31,
      38,    33,    34,   251,   269,   281,   325,   326,   327,    27,
      23,    27,    23,    31,    32,    27,    23,    26,    43,    32,
      38,    23,    27,    23,    21,    27,    31,    38,    19,    32,
      21,    23,    39,    34,    37,    89,    19,    19,    89,    32,
      23,   282,    21,    21,    19,    32,    21,    89,    19,    34,
      32,    21,    89,    33,    32,    19,    34,    23,    23,    36,
      38,    39,    34,    36,    34,    31,    89,    36,   269,    23,
      23,    34,    23,    23,    34,    32,    23,    23,    23,    21,
      27,    39,    24,    34,    30,    37,    89,    34,    38,    19,
      19,    37,    19,    22,    37,    30,    89,    19,    32,    30,
      89,    33,    32,    32,    33,    89,    89,    34,    39,    89,
      36,    31,    42,    23,    27,    34,    36,    23,    21,    27,
      39,    24,    38,    21,    27,    34,    19,    38,    22,    19,
      23,    31,    37,    19,    19,    30,    33,    32,    32,    33,
      33,    32,    19,    36,    89,    36,    31,    38,    19,    38,
      36,    31,    39,    24,    38,    39,    24,    36,    19,    22,
      27,    23,    23,    32,    23,    19,    23,    32,    33,    32,
      33,    19,    31,    36,    40,    38,    36,    22,    32,    31,
      38,    38,    38,    31,    23,    27,    23,    23,    89,    38,
      23,    23,    23,    38,    40,    36,    36,    26,    38,    36,
      38,    23,    23,    37,    33,    23,    23,    36,    36,    30,
      36,    36,    37,    22
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
    { (yyval.String) = LSCPSERVER->SetEcho((yyparse_param_t*) yyparse_param, (yyvsp[(3) - (3)].Dotnum));  }
    break;

  case 113:
#line 229 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetGlobalVolume((yyvsp[(3) - (3)].Dotnum));                            }
    break;

  case 114:
#line 232 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateAudioOutputDevice((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].KeyValList)); }
    break;

  case 115:
#line 233 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateAudioOutputDevice((yyvsp[(3) - (3)].String));    }
    break;

  case 116:
#line 234 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateMidiInputDevice((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].KeyValList));   }
    break;

  case 117:
#line 235 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateMidiInputDevice((yyvsp[(3) - (3)].String));      }
    break;

  case 118:
#line 236 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateFxSend((yyvsp[(3) - (5)].Number),(yyvsp[(5) - (5)].Number));            }
    break;

  case 119:
#line 237 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateFxSend((yyvsp[(3) - (7)].Number),(yyvsp[(5) - (7)].Number),(yyvsp[(7) - (7)].String)); }
    break;

  case 120:
#line 240 "lscp.y"
    { (yyval.String) = LSCPSERVER->ResetChannel((yyvsp[(3) - (3)].Number)); }
    break;

  case 121:
#line 243 "lscp.y"
    { (yyval.String) = LSCPSERVER->ClearMidiInstrumentMappings((yyvsp[(3) - (3)].Number));  }
    break;

  case 122:
#line 244 "lscp.y"
    { (yyval.String) = LSCPSERVER->ClearAllMidiInstrumentMappings(); }
    break;

  case 123:
#line 247 "lscp.y"
    { (yyval.String) = LSCPSERVER->DestroyAudioOutputDevice((yyvsp[(3) - (3)].Number)); }
    break;

  case 124:
#line 248 "lscp.y"
    { (yyval.String) = LSCPSERVER->DestroyMidiInputDevice((yyvsp[(3) - (3)].Number));   }
    break;

  case 125:
#line 249 "lscp.y"
    { (yyval.String) = LSCPSERVER->DestroyFxSend((yyvsp[(3) - (5)].Number),(yyvsp[(5) - (5)].Number)); }
    break;

  case 126:
#line 252 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String); }
    break;

  case 127:
#line 253 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String); }
    break;

  case 128:
#line 256 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputDevice((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));      }
    break;

  case 129:
#line 257 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputChannel((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number), (yyvsp[(3) - (7)].Number)); }
    break;

  case 130:
#line 258 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputType((yyvsp[(5) - (5)].String), (yyvsp[(3) - (5)].Number));        }
    break;

  case 131:
#line 259 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInput((yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].Number), (yyvsp[(9) - (9)].Number), (yyvsp[(3) - (9)].Number));      }
    break;

  case 132:
#line 260 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputDevice((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));        }
    break;

  case 133:
#line 261 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputPort((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));          }
    break;

  case 134:
#line 262 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputChannel((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));       }
    break;

  case 135:
#line 263 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputType((yyvsp[(5) - (5)].String), (yyvsp[(3) - (5)].Number));          }
    break;

  case 136:
#line 264 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetVolume((yyvsp[(5) - (5)].Dotnum), (yyvsp[(3) - (5)].Number));                 }
    break;

  case 137:
#line 265 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMute((yyvsp[(5) - (5)].Dotnum), (yyvsp[(3) - (5)].Number));            }
    break;

  case 138:
#line 266 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelSolo((yyvsp[(5) - (5)].Dotnum), (yyvsp[(3) - (5)].Number));            }
    break;

  case 139:
#line 267 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMap((yyvsp[(3) - (5)].Number), (yyvsp[(5) - (5)].Number));             }
    break;

  case 140:
#line 268 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMap((yyvsp[(3) - (5)].Number), -1);             }
    break;

  case 141:
#line 269 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMap((yyvsp[(3) - (5)].Number), -2);             }
    break;

  case 142:
#line 272 "lscp.y"
    { (yyval.KeyValList)[(yyvsp[(1) - (3)].String)] = (yyvsp[(3) - (3)].String);          }
    break;

  case 143:
#line 273 "lscp.y"
    { (yyval.KeyValList) = (yyvsp[(1) - (5)].KeyValList); (yyval.KeyValList)[(yyvsp[(3) - (5)].String)] = (yyvsp[(5) - (5)].String); }
    break;

  case 144:
#line 276 "lscp.y"
    { (yyval.FillResponse) = fill_response_bytes;      }
    break;

  case 145:
#line 277 "lscp.y"
    { (yyval.FillResponse) = fill_response_percentage; }
    break;

  case 146:
#line 280 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDevices();           }
    break;

  case 147:
#line 281 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDevices();             }
    break;

  case 148:
#line 282 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListChannels();                    }
    break;

  case 149:
#line 283 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableEngines();            }
    break;

  case 150:
#line 284 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableMidiInputDrivers();   }
    break;

  case 151:
#line 285 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableAudioOutputDrivers(); }
    break;

  case 152:
#line 286 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListMidiInstrumentMappings((yyvsp[(3) - (3)].Number));    }
    break;

  case 153:
#line 287 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAllMidiInstrumentMappings();   }
    break;

  case 154:
#line 288 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListMidiInstrumentMaps();          }
    break;

  case 155:
#line 289 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListFxSends((yyvsp[(3) - (3)].Number));                   }
    break;

  case 156:
#line 292 "lscp.y"
    { (yyval.String) = LSCPSERVER->LoadInstrument((yyvsp[(1) - (5)].String), (yyvsp[(3) - (5)].Number), (yyvsp[(5) - (5)].Number));       }
    break;

  case 157:
#line 293 "lscp.y"
    { (yyval.String) = LSCPSERVER->LoadInstrument((yyvsp[(3) - (7)].String), (yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number), true); }
    break;

  case 158:
#line 296 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetEngineType((yyvsp[(1) - (3)].String), (yyvsp[(3) - (3)].Number)); }
    break;

  case 159:
#line 299 "lscp.y"
    { (yyval.LoadMode) = MidiInstrumentMapper::ON_DEMAND;      }
    break;

  case 160:
#line 300 "lscp.y"
    { (yyval.LoadMode) = MidiInstrumentMapper::ON_DEMAND_HOLD; }
    break;

  case 161:
#line 301 "lscp.y"
    { (yyval.LoadMode) = MidiInstrumentMapper::PERSISTENT;     }
    break;

  case 167:
#line 317 "lscp.y"
    { (yyval.Number) = 16; }
    break;

  case 174:
#line 336 "lscp.y"
    { (yyval.Dotnum) = (yyvsp[(1) - (1)].Number); }
    break;

  case 184:
#line 364 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (3)].String) + "," + (yyvsp[(3) - (3)].String); }
    break;

  case 187:
#line 369 "lscp.y"
    { std::stringstream ss; ss << "\'" << (yyvsp[(1) - (1)].Number) << "\'"; (yyval.String) = ss.str(); }
    break;

  case 188:
#line 370 "lscp.y"
    { std::stringstream ss; ss << "\'" << (yyvsp[(1) - (1)].Dotnum) << "\'"; (yyval.String) = ss.str(); }
    break;

  case 189:
#line 378 "lscp.y"
    { (yyval.Dotnum) = (yyvsp[(1) - (1)].Number); }
    break;

  case 190:
#line 379 "lscp.y"
    { (yyval.Dotnum) = -1; }
    break;

  case 191:
#line 382 "lscp.y"
    { std::string s; s = (yyvsp[(1) - (1)].Char); (yyval.String) = s; }
    break;

  case 192:
#line 383 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + (yyvsp[(2) - (2)].Char);                  }
    break;

  case 193:
#line 386 "lscp.y"
    { (yyval.Dotnum) = atof(String((yyvsp[(1) - (3)].String) + "." + (yyvsp[(3) - (3)].String)).c_str());                         }
    break;

  case 194:
#line 387 "lscp.y"
    { String s = "+"; s += (yyvsp[(2) - (4)].String); s += "."; s += (yyvsp[(4) - (4)].String); (yyval.Dotnum) = atof(s.c_str()); }
    break;

  case 195:
#line 388 "lscp.y"
    { (yyval.Dotnum) = atof(String("-" + (yyvsp[(2) - (4)].String) + "." + (yyvsp[(4) - (4)].String)).c_str());                   }
    break;

  case 196:
#line 392 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (1)].Char);      }
    break;

  case 197:
#line 393 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + (yyvsp[(2) - (2)].Char); }
    break;

  case 198:
#line 396 "lscp.y"
    { (yyval.Char) = '0'; }
    break;

  case 199:
#line 397 "lscp.y"
    { (yyval.Char) = '1'; }
    break;

  case 200:
#line 398 "lscp.y"
    { (yyval.Char) = '2'; }
    break;

  case 201:
#line 399 "lscp.y"
    { (yyval.Char) = '3'; }
    break;

  case 202:
#line 400 "lscp.y"
    { (yyval.Char) = '4'; }
    break;

  case 203:
#line 401 "lscp.y"
    { (yyval.Char) = '5'; }
    break;

  case 204:
#line 402 "lscp.y"
    { (yyval.Char) = '6'; }
    break;

  case 205:
#line 403 "lscp.y"
    { (yyval.Char) = '7'; }
    break;

  case 206:
#line 404 "lscp.y"
    { (yyval.Char) = '8'; }
    break;

  case 207:
#line 405 "lscp.y"
    { (yyval.Char) = '9'; }
    break;

  case 208:
#line 408 "lscp.y"
    { (yyval.Number) = atoi(String(1, (yyvsp[(1) - (1)].Char)).c_str());      }
    break;

  case 209:
#line 409 "lscp.y"
    { (yyval.Number) = atoi(String(String("1") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 210:
#line 410 "lscp.y"
    { (yyval.Number) = atoi(String(String("2") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 211:
#line 411 "lscp.y"
    { (yyval.Number) = atoi(String(String("3") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 212:
#line 412 "lscp.y"
    { (yyval.Number) = atoi(String(String("4") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 213:
#line 413 "lscp.y"
    { (yyval.Number) = atoi(String(String("5") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 214:
#line 414 "lscp.y"
    { (yyval.Number) = atoi(String(String("6") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 215:
#line 415 "lscp.y"
    { (yyval.Number) = atoi(String(String("7") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 216:
#line 416 "lscp.y"
    { (yyval.Number) = atoi(String(String("8") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 217:
#line 417 "lscp.y"
    { (yyval.Number) = atoi(String(String("9") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 218:
#line 419 "lscp.y"
    { (yyval.Char) = 'A'; }
    break;

  case 219:
#line 419 "lscp.y"
    { (yyval.Char) = 'B'; }
    break;

  case 220:
#line 419 "lscp.y"
    { (yyval.Char) = 'C'; }
    break;

  case 221:
#line 419 "lscp.y"
    { (yyval.Char) = 'D'; }
    break;

  case 222:
#line 419 "lscp.y"
    { (yyval.Char) = 'E'; }
    break;

  case 223:
#line 419 "lscp.y"
    { (yyval.Char) = 'F'; }
    break;

  case 224:
#line 419 "lscp.y"
    { (yyval.Char) = 'G'; }
    break;

  case 225:
#line 419 "lscp.y"
    { (yyval.Char) = 'H'; }
    break;

  case 226:
#line 419 "lscp.y"
    { (yyval.Char) = 'I'; }
    break;

  case 227:
#line 419 "lscp.y"
    { (yyval.Char) = 'J'; }
    break;

  case 228:
#line 419 "lscp.y"
    { (yyval.Char) = 'K'; }
    break;

  case 229:
#line 419 "lscp.y"
    { (yyval.Char) = 'L'; }
    break;

  case 230:
#line 419 "lscp.y"
    { (yyval.Char) = 'M'; }
    break;

  case 231:
#line 419 "lscp.y"
    { (yyval.Char) = 'N'; }
    break;

  case 232:
#line 419 "lscp.y"
    { (yyval.Char) = 'O'; }
    break;

  case 233:
#line 419 "lscp.y"
    { (yyval.Char) = 'P'; }
    break;

  case 234:
#line 419 "lscp.y"
    { (yyval.Char) = 'Q'; }
    break;

  case 235:
#line 419 "lscp.y"
    { (yyval.Char) = 'R'; }
    break;

  case 236:
#line 419 "lscp.y"
    { (yyval.Char) = 'S'; }
    break;

  case 237:
#line 419 "lscp.y"
    { (yyval.Char) = 'T'; }
    break;

  case 238:
#line 419 "lscp.y"
    { (yyval.Char) = 'U'; }
    break;

  case 239:
#line 419 "lscp.y"
    { (yyval.Char) = 'V'; }
    break;

  case 240:
#line 419 "lscp.y"
    { (yyval.Char) = 'W'; }
    break;

  case 241:
#line 419 "lscp.y"
    { (yyval.Char) = 'X'; }
    break;

  case 242:
#line 419 "lscp.y"
    { (yyval.Char) = 'Y'; }
    break;

  case 243:
#line 419 "lscp.y"
    { (yyval.Char) = 'Z'; }
    break;

  case 244:
#line 420 "lscp.y"
    { (yyval.Char) = 'a'; }
    break;

  case 245:
#line 420 "lscp.y"
    { (yyval.Char) = 'b'; }
    break;

  case 246:
#line 420 "lscp.y"
    { (yyval.Char) = 'c'; }
    break;

  case 247:
#line 420 "lscp.y"
    { (yyval.Char) = 'd'; }
    break;

  case 248:
#line 420 "lscp.y"
    { (yyval.Char) = 'e'; }
    break;

  case 249:
#line 420 "lscp.y"
    { (yyval.Char) = 'f'; }
    break;

  case 250:
#line 420 "lscp.y"
    { (yyval.Char) = 'g'; }
    break;

  case 251:
#line 420 "lscp.y"
    { (yyval.Char) = 'h'; }
    break;

  case 252:
#line 420 "lscp.y"
    { (yyval.Char) = 'i'; }
    break;

  case 253:
#line 420 "lscp.y"
    { (yyval.Char) = 'j'; }
    break;

  case 254:
#line 420 "lscp.y"
    { (yyval.Char) = 'k'; }
    break;

  case 255:
#line 420 "lscp.y"
    { (yyval.Char) = 'l'; }
    break;

  case 256:
#line 420 "lscp.y"
    { (yyval.Char) = 'm'; }
    break;

  case 257:
#line 420 "lscp.y"
    { (yyval.Char) = 'n'; }
    break;

  case 258:
#line 420 "lscp.y"
    { (yyval.Char) = 'o'; }
    break;

  case 259:
#line 420 "lscp.y"
    { (yyval.Char) = 'p'; }
    break;

  case 260:
#line 420 "lscp.y"
    { (yyval.Char) = 'q'; }
    break;

  case 261:
#line 420 "lscp.y"
    { (yyval.Char) = 'r'; }
    break;

  case 262:
#line 420 "lscp.y"
    { (yyval.Char) = 's'; }
    break;

  case 263:
#line 420 "lscp.y"
    { (yyval.Char) = 't'; }
    break;

  case 264:
#line 420 "lscp.y"
    { (yyval.Char) = 'u'; }
    break;

  case 265:
#line 420 "lscp.y"
    { (yyval.Char) = 'v'; }
    break;

  case 266:
#line 420 "lscp.y"
    { (yyval.Char) = 'w'; }
    break;

  case 267:
#line 420 "lscp.y"
    { (yyval.Char) = 'x'; }
    break;

  case 268:
#line 420 "lscp.y"
    { (yyval.Char) = 'y'; }
    break;

  case 269:
#line 420 "lscp.y"
    { (yyval.Char) = 'z'; }
    break;

  case 270:
#line 421 "lscp.y"
    { (yyval.Char) = '0'; }
    break;

  case 271:
#line 421 "lscp.y"
    { (yyval.Char) = '1'; }
    break;

  case 272:
#line 421 "lscp.y"
    { (yyval.Char) = '2'; }
    break;

  case 273:
#line 421 "lscp.y"
    { (yyval.Char) = '3'; }
    break;

  case 274:
#line 421 "lscp.y"
    { (yyval.Char) = '4'; }
    break;

  case 275:
#line 421 "lscp.y"
    { (yyval.Char) = '5'; }
    break;

  case 276:
#line 421 "lscp.y"
    { (yyval.Char) = '6'; }
    break;

  case 277:
#line 421 "lscp.y"
    { (yyval.Char) = '7'; }
    break;

  case 278:
#line 421 "lscp.y"
    { (yyval.Char) = '8'; }
    break;

  case 279:
#line 421 "lscp.y"
    { (yyval.Char) = '9'; }
    break;

  case 280:
#line 422 "lscp.y"
    { (yyval.Char) = '!'; }
    break;

  case 281:
#line 422 "lscp.y"
    { (yyval.Char) = '#'; }
    break;

  case 282:
#line 422 "lscp.y"
    { (yyval.Char) = '$'; }
    break;

  case 283:
#line 422 "lscp.y"
    { (yyval.Char) = '%'; }
    break;

  case 284:
#line 422 "lscp.y"
    { (yyval.Char) = '&'; }
    break;

  case 285:
#line 422 "lscp.y"
    { (yyval.Char) = '('; }
    break;

  case 286:
#line 422 "lscp.y"
    { (yyval.Char) = ')'; }
    break;

  case 287:
#line 422 "lscp.y"
    { (yyval.Char) = '*'; }
    break;

  case 288:
#line 422 "lscp.y"
    { (yyval.Char) = '+'; }
    break;

  case 289:
#line 422 "lscp.y"
    { (yyval.Char) = '-'; }
    break;

  case 290:
#line 422 "lscp.y"
    { (yyval.Char) = '.'; }
    break;

  case 291:
#line 422 "lscp.y"
    { (yyval.Char) = ','; }
    break;

  case 292:
#line 422 "lscp.y"
    { (yyval.Char) = '/'; }
    break;

  case 293:
#line 423 "lscp.y"
    { (yyval.Char) = ':'; }
    break;

  case 294:
#line 423 "lscp.y"
    { (yyval.Char) = ';'; }
    break;

  case 295:
#line 423 "lscp.y"
    { (yyval.Char) = '<'; }
    break;

  case 296:
#line 423 "lscp.y"
    { (yyval.Char) = '='; }
    break;

  case 297:
#line 423 "lscp.y"
    { (yyval.Char) = '>'; }
    break;

  case 298:
#line 423 "lscp.y"
    { (yyval.Char) = '?'; }
    break;

  case 299:
#line 423 "lscp.y"
    { (yyval.Char) = '@'; }
    break;

  case 300:
#line 424 "lscp.y"
    { (yyval.Char) = '['; }
    break;

  case 301:
#line 424 "lscp.y"
    { (yyval.Char) = '\\'; }
    break;

  case 302:
#line 424 "lscp.y"
    { (yyval.Char) = ']'; }
    break;

  case 303:
#line 424 "lscp.y"
    { (yyval.Char) = '^'; }
    break;

  case 304:
#line 424 "lscp.y"
    { (yyval.Char) = '_'; }
    break;

  case 305:
#line 425 "lscp.y"
    { (yyval.Char) = '{'; }
    break;

  case 306:
#line 425 "lscp.y"
    { (yyval.Char) = '|'; }
    break;

  case 307:
#line 425 "lscp.y"
    { (yyval.Char) = '}'; }
    break;

  case 308:
#line 425 "lscp.y"
    { (yyval.Char) = '~'; }
    break;

  case 309:
#line 426 "lscp.y"
    { (yyval.Char) = '\200'; }
    break;

  case 310:
#line 426 "lscp.y"
    { (yyval.Char) = '\201'; }
    break;

  case 311:
#line 426 "lscp.y"
    { (yyval.Char) = '\202'; }
    break;

  case 312:
#line 427 "lscp.y"
    { (yyval.Char) = '\203'; }
    break;

  case 313:
#line 427 "lscp.y"
    { (yyval.Char) = '\204'; }
    break;

  case 314:
#line 427 "lscp.y"
    { (yyval.Char) = '\205'; }
    break;

  case 315:
#line 428 "lscp.y"
    { (yyval.Char) = '\206'; }
    break;

  case 316:
#line 428 "lscp.y"
    { (yyval.Char) = '\207'; }
    break;

  case 317:
#line 428 "lscp.y"
    { (yyval.Char) = '\210'; }
    break;

  case 318:
#line 429 "lscp.y"
    { (yyval.Char) = '\211'; }
    break;

  case 319:
#line 429 "lscp.y"
    { (yyval.Char) = '\212'; }
    break;

  case 320:
#line 429 "lscp.y"
    { (yyval.Char) = '\213'; }
    break;

  case 321:
#line 430 "lscp.y"
    { (yyval.Char) = '\214'; }
    break;

  case 322:
#line 430 "lscp.y"
    { (yyval.Char) = '\215'; }
    break;

  case 323:
#line 430 "lscp.y"
    { (yyval.Char) = '\216'; }
    break;

  case 324:
#line 431 "lscp.y"
    { (yyval.Char) = '\217'; }
    break;

  case 325:
#line 431 "lscp.y"
    { (yyval.Char) = '\220'; }
    break;

  case 326:
#line 431 "lscp.y"
    { (yyval.Char) = '\221'; }
    break;

  case 327:
#line 432 "lscp.y"
    { (yyval.Char) = '\222'; }
    break;

  case 328:
#line 432 "lscp.y"
    { (yyval.Char) = '\223'; }
    break;

  case 329:
#line 432 "lscp.y"
    { (yyval.Char) = '\224'; }
    break;

  case 330:
#line 433 "lscp.y"
    { (yyval.Char) = '\225'; }
    break;

  case 331:
#line 433 "lscp.y"
    { (yyval.Char) = '\226'; }
    break;

  case 332:
#line 433 "lscp.y"
    { (yyval.Char) = '\227'; }
    break;

  case 333:
#line 434 "lscp.y"
    { (yyval.Char) = '\230'; }
    break;

  case 334:
#line 434 "lscp.y"
    { (yyval.Char) = '\231'; }
    break;

  case 335:
#line 434 "lscp.y"
    { (yyval.Char) = '\232'; }
    break;

  case 336:
#line 435 "lscp.y"
    { (yyval.Char) = '\233'; }
    break;

  case 337:
#line 435 "lscp.y"
    { (yyval.Char) = '\234'; }
    break;

  case 338:
#line 435 "lscp.y"
    { (yyval.Char) = '\235'; }
    break;

  case 339:
#line 436 "lscp.y"
    { (yyval.Char) = '\236'; }
    break;

  case 340:
#line 436 "lscp.y"
    { (yyval.Char) = '\237'; }
    break;

  case 341:
#line 436 "lscp.y"
    { (yyval.Char) = '\240'; }
    break;

  case 342:
#line 437 "lscp.y"
    { (yyval.Char) = '\241'; }
    break;

  case 343:
#line 437 "lscp.y"
    { (yyval.Char) = '\242'; }
    break;

  case 344:
#line 437 "lscp.y"
    { (yyval.Char) = '\243'; }
    break;

  case 345:
#line 438 "lscp.y"
    { (yyval.Char) = '\244'; }
    break;

  case 346:
#line 438 "lscp.y"
    { (yyval.Char) = '\245'; }
    break;

  case 347:
#line 438 "lscp.y"
    { (yyval.Char) = '\246'; }
    break;

  case 348:
#line 439 "lscp.y"
    { (yyval.Char) = '\247'; }
    break;

  case 349:
#line 439 "lscp.y"
    { (yyval.Char) = '\250'; }
    break;

  case 350:
#line 439 "lscp.y"
    { (yyval.Char) = '\251'; }
    break;

  case 351:
#line 440 "lscp.y"
    { (yyval.Char) = '\252'; }
    break;

  case 352:
#line 440 "lscp.y"
    { (yyval.Char) = '\253'; }
    break;

  case 353:
#line 440 "lscp.y"
    { (yyval.Char) = '\254'; }
    break;

  case 354:
#line 441 "lscp.y"
    { (yyval.Char) = '\255'; }
    break;

  case 355:
#line 441 "lscp.y"
    { (yyval.Char) = '\256'; }
    break;

  case 356:
#line 441 "lscp.y"
    { (yyval.Char) = '\257'; }
    break;

  case 357:
#line 442 "lscp.y"
    { (yyval.Char) = '\260'; }
    break;

  case 358:
#line 442 "lscp.y"
    { (yyval.Char) = '\261'; }
    break;

  case 359:
#line 442 "lscp.y"
    { (yyval.Char) = '\262'; }
    break;

  case 360:
#line 443 "lscp.y"
    { (yyval.Char) = '\263'; }
    break;

  case 361:
#line 443 "lscp.y"
    { (yyval.Char) = '\264'; }
    break;

  case 362:
#line 443 "lscp.y"
    { (yyval.Char) = '\265'; }
    break;

  case 363:
#line 444 "lscp.y"
    { (yyval.Char) = '\266'; }
    break;

  case 364:
#line 444 "lscp.y"
    { (yyval.Char) = '\267'; }
    break;

  case 365:
#line 444 "lscp.y"
    { (yyval.Char) = '\270'; }
    break;

  case 366:
#line 445 "lscp.y"
    { (yyval.Char) = '\271'; }
    break;

  case 367:
#line 445 "lscp.y"
    { (yyval.Char) = '\272'; }
    break;

  case 368:
#line 445 "lscp.y"
    { (yyval.Char) = '\273'; }
    break;

  case 369:
#line 446 "lscp.y"
    { (yyval.Char) = '\274'; }
    break;

  case 370:
#line 446 "lscp.y"
    { (yyval.Char) = '\275'; }
    break;

  case 371:
#line 446 "lscp.y"
    { (yyval.Char) = '\276'; }
    break;

  case 372:
#line 447 "lscp.y"
    { (yyval.Char) = '\277'; }
    break;

  case 373:
#line 447 "lscp.y"
    { (yyval.Char) = '\300'; }
    break;

  case 374:
#line 447 "lscp.y"
    { (yyval.Char) = '\301'; }
    break;

  case 375:
#line 448 "lscp.y"
    { (yyval.Char) = '\302'; }
    break;

  case 376:
#line 448 "lscp.y"
    { (yyval.Char) = '\303'; }
    break;

  case 377:
#line 448 "lscp.y"
    { (yyval.Char) = '\304'; }
    break;

  case 378:
#line 449 "lscp.y"
    { (yyval.Char) = '\305'; }
    break;

  case 379:
#line 449 "lscp.y"
    { (yyval.Char) = '\306'; }
    break;

  case 380:
#line 449 "lscp.y"
    { (yyval.Char) = '\307'; }
    break;

  case 381:
#line 450 "lscp.y"
    { (yyval.Char) = '\310'; }
    break;

  case 382:
#line 450 "lscp.y"
    { (yyval.Char) = '\311'; }
    break;

  case 383:
#line 450 "lscp.y"
    { (yyval.Char) = '\312'; }
    break;

  case 384:
#line 451 "lscp.y"
    { (yyval.Char) = '\313'; }
    break;

  case 385:
#line 451 "lscp.y"
    { (yyval.Char) = '\314'; }
    break;

  case 386:
#line 451 "lscp.y"
    { (yyval.Char) = '\315'; }
    break;

  case 387:
#line 452 "lscp.y"
    { (yyval.Char) = '\316'; }
    break;

  case 388:
#line 452 "lscp.y"
    { (yyval.Char) = '\317'; }
    break;

  case 389:
#line 452 "lscp.y"
    { (yyval.Char) = '\320'; }
    break;

  case 390:
#line 453 "lscp.y"
    { (yyval.Char) = '\321'; }
    break;

  case 391:
#line 453 "lscp.y"
    { (yyval.Char) = '\322'; }
    break;

  case 392:
#line 453 "lscp.y"
    { (yyval.Char) = '\323'; }
    break;

  case 393:
#line 454 "lscp.y"
    { (yyval.Char) = '\324'; }
    break;

  case 394:
#line 454 "lscp.y"
    { (yyval.Char) = '\325'; }
    break;

  case 395:
#line 454 "lscp.y"
    { (yyval.Char) = '\326'; }
    break;

  case 396:
#line 455 "lscp.y"
    { (yyval.Char) = '\327'; }
    break;

  case 397:
#line 455 "lscp.y"
    { (yyval.Char) = '\330'; }
    break;

  case 398:
#line 455 "lscp.y"
    { (yyval.Char) = '\331'; }
    break;

  case 399:
#line 456 "lscp.y"
    { (yyval.Char) = '\332'; }
    break;

  case 400:
#line 456 "lscp.y"
    { (yyval.Char) = '\333'; }
    break;

  case 401:
#line 456 "lscp.y"
    { (yyval.Char) = '\334'; }
    break;

  case 402:
#line 457 "lscp.y"
    { (yyval.Char) = '\335'; }
    break;

  case 403:
#line 457 "lscp.y"
    { (yyval.Char) = '\336'; }
    break;

  case 404:
#line 457 "lscp.y"
    { (yyval.Char) = '\337'; }
    break;

  case 405:
#line 458 "lscp.y"
    { (yyval.Char) = '\340'; }
    break;

  case 406:
#line 458 "lscp.y"
    { (yyval.Char) = '\341'; }
    break;

  case 407:
#line 458 "lscp.y"
    { (yyval.Char) = '\342'; }
    break;

  case 408:
#line 459 "lscp.y"
    { (yyval.Char) = '\343'; }
    break;

  case 409:
#line 459 "lscp.y"
    { (yyval.Char) = '\344'; }
    break;

  case 410:
#line 459 "lscp.y"
    { (yyval.Char) = '\345'; }
    break;

  case 411:
#line 460 "lscp.y"
    { (yyval.Char) = '\346'; }
    break;

  case 412:
#line 460 "lscp.y"
    { (yyval.Char) = '\347'; }
    break;

  case 413:
#line 460 "lscp.y"
    { (yyval.Char) = '\350'; }
    break;

  case 414:
#line 461 "lscp.y"
    { (yyval.Char) = '\351'; }
    break;

  case 415:
#line 461 "lscp.y"
    { (yyval.Char) = '\352'; }
    break;

  case 416:
#line 461 "lscp.y"
    { (yyval.Char) = '\353'; }
    break;

  case 417:
#line 462 "lscp.y"
    { (yyval.Char) = '\354'; }
    break;

  case 418:
#line 462 "lscp.y"
    { (yyval.Char) = '\355'; }
    break;

  case 419:
#line 462 "lscp.y"
    { (yyval.Char) = '\356'; }
    break;

  case 420:
#line 463 "lscp.y"
    { (yyval.Char) = '\357'; }
    break;

  case 421:
#line 463 "lscp.y"
    { (yyval.Char) = '\360'; }
    break;

  case 422:
#line 463 "lscp.y"
    { (yyval.Char) = '\361'; }
    break;

  case 423:
#line 464 "lscp.y"
    { (yyval.Char) = '\362'; }
    break;

  case 424:
#line 464 "lscp.y"
    { (yyval.Char) = '\363'; }
    break;

  case 425:
#line 464 "lscp.y"
    { (yyval.Char) = '\364'; }
    break;

  case 426:
#line 465 "lscp.y"
    { (yyval.Char) = '\365'; }
    break;

  case 427:
#line 465 "lscp.y"
    { (yyval.Char) = '\366'; }
    break;

  case 428:
#line 465 "lscp.y"
    { (yyval.Char) = '\367'; }
    break;

  case 429:
#line 466 "lscp.y"
    { (yyval.Char) = '\370'; }
    break;

  case 430:
#line 466 "lscp.y"
    { (yyval.Char) = '\371'; }
    break;

  case 431:
#line 466 "lscp.y"
    { (yyval.Char) = '\372'; }
    break;

  case 432:
#line 467 "lscp.y"
    { (yyval.Char) = '\373'; }
    break;

  case 433:
#line 467 "lscp.y"
    { (yyval.Char) = '\374'; }
    break;

  case 434:
#line 467 "lscp.y"
    { (yyval.Char) = '\375'; }
    break;

  case 435:
#line 468 "lscp.y"
    { (yyval.Char) = '\376'; }
    break;

  case 436:
#line 468 "lscp.y"
    { (yyval.Char) = '\377'; }
    break;

  case 437:
#line 471 "lscp.y"
    { (yyval.String) = " ";      }
    break;

  case 439:
#line 473 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + " "; }
    break;

  case 440:
#line 474 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + (yyvsp[(2) - (2)].String);  }
    break;

  case 441:
#line 477 "lscp.y"
    { (yyval.String) = (yyvsp[(2) - (3)].String); }
    break;

  case 442:
#line 478 "lscp.y"
    { (yyval.String) = (yyvsp[(2) - (3)].String); }
    break;


/* Line 1267 of yacc.c.  */
#line 5312 "y.tab.c"
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


#line 730 "lscp.y"


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

