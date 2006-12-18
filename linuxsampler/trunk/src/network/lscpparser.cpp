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
#define YYLAST   4318

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  227
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  132
/* YYNRULES -- Number of rules.  */
#define YYNRULES  510
/* YYNRULES -- Number of states.  */
#define YYNSTATES  1556

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
     421,   423,   429,   437,   447,   455,   465,   469,   477,   481,
     487,   491,   497,   501,   505,   509,   513,   517,   521,   525,
     529,   535,   543,   549,   559,   565,   571,   577,   583,   589,
     595,   601,   607,   613,   619,   623,   629,   631,   633,   635,
     637,   639,   641,   643,   645,   649,   653,   655,   661,   669,
     673,   675,   677,   679,   681,   683,   685,   687,   689,   691,
     693,   695,   697,   699,   701,   703,   705,   707,   709,   711,
     713,   715,   717,   721,   723,   725,   727,   729,   731,   733,
     735,   738,   742,   747,   752,   754,   757,   759,   761,   763,
     765,   767,   769,   771,   773,   775,   777,   779,   782,   785,
     788,   791,   794,   797,   800,   803,   806,   808,   810,   812,
     814,   816,   818,   820,   822,   824,   826,   828,   830,   832,
     834,   836,   838,   840,   842,   844,   846,   848,   850,   852,
     854,   856,   858,   860,   862,   864,   866,   868,   870,   872,
     874,   876,   878,   880,   882,   884,   886,   888,   890,   892,
     894,   896,   898,   900,   902,   904,   906,   908,   910,   912,
     914,   916,   918,   920,   922,   924,   926,   928,   930,   932,
     934,   936,   938,   940,   942,   944,   946,   948,   950,   952,
     954,   956,   958,   960,   962,   964,   966,   968,   970,   972,
     974,   976,   978,   980,   982,   984,   986,   988,   990,   992,
     994,   996,   998,  1000,  1002,  1004,  1006,  1008,  1010,  1012,
    1014,  1016,  1018,  1020,  1022,  1024,  1026,  1028,  1030,  1032,
    1034,  1036,  1038,  1040,  1042,  1044,  1046,  1048,  1050,  1052,
    1054,  1056,  1058,  1060,  1062,  1064,  1066,  1068,  1070,  1072,
    1074,  1076,  1078,  1080,  1082,  1084,  1086,  1088,  1090,  1092,
    1094,  1096,  1098,  1100,  1102,  1104,  1106,  1108,  1110,  1112,
    1114,  1116,  1118,  1120,  1122,  1124,  1126,  1128,  1130,  1132,
    1134,  1136,  1138,  1140,  1142,  1144,  1146,  1148,  1150,  1152,
    1154,  1156,  1158,  1160,  1162,  1164,  1166,  1168,  1170,  1172,
    1174,  1176,  1178,  1180,  1182,  1184,  1186,  1188,  1190,  1192,
    1194,  1196,  1198,  1200,  1202,  1204,  1206,  1208,  1210,  1212,
    1214,  1216,  1218,  1220,  1222,  1224,  1226,  1228,  1230,  1232,
    1234,  1236,  1238,  1240,  1242,  1244,  1246,  1248,  1251,  1254,
    1258,  1262,  1264,  1266,  1268,  1272,  1276,  1280,  1286,  1292,
    1299,  1307,  1312,  1317,  1321,  1326,  1334,  1344,  1351,  1355,
    1365,  1377,  1384,  1392,  1410,  1441,  1450,  1455,  1481,  1506,
    1530,  1553,  1579,  1604,  1626,  1647,  1661,  1674,  1686,  1699,
    1711,  1729,  1751,  1762,  1769,  1779,  1794,  1805,  1835,  1856,
    1876,  1906,  1926,  1957,  1978,  1996,  2025,  2053,  2079,  2098,
    2116,  2144,  2160,  2177,  2197,  2218,  2236,  2252,  2271,  2287,
    2298,  2305,  2312,  2317,  2322,  2328,  2339,  2345,  2359,  2364,
    2369
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     228,     0,    -1,   229,   280,    -1,   229,   281,   280,    -1,
      -1,   230,    -1,   231,    -1,     1,    -1,     3,    -1,   230,
       3,    -1,   230,   279,    -1,   230,   275,    -1,   230,   271,
      -1,   282,   279,   232,    -1,   284,   279,   235,    -1,   285,
     279,   236,    -1,   283,   279,   238,    -1,   287,   279,   240,
      -1,   288,   279,   243,    -1,   289,   279,   248,    -1,   290,
     279,   244,    -1,   295,   279,   237,    -1,   296,   279,   239,
      -1,   297,   279,   233,    -1,   298,   279,   234,    -1,   299,
     279,   277,    -1,   354,   279,   241,    -1,   286,   279,   242,
      -1,   354,    -1,   358,    -1,   300,    -1,   341,    -1,   341,
     279,   266,    -1,   305,    -1,   306,    -1,   307,    -1,   308,
      -1,   313,    -1,   317,    -1,   316,    -1,   315,    -1,   314,
      -1,   309,    -1,   310,    -1,   311,    -1,   312,    -1,   355,
      -1,   318,    -1,   305,    -1,   306,    -1,   307,    -1,   308,
      -1,   313,    -1,   317,    -1,   316,    -1,   315,    -1,   314,
      -1,   309,    -1,   310,    -1,   311,    -1,   312,    -1,   355,
      -1,   318,    -1,   339,   279,   258,   279,   259,   279,   260,
     279,   264,   279,   265,   279,   263,   279,   261,    -1,   339,
     279,   258,   279,   259,   279,   260,   279,   264,   279,   265,
     279,   263,   279,   261,   279,   251,    -1,   339,   279,   258,
     279,   259,   279,   260,   279,   264,   279,   265,   279,   263,
     279,   261,   279,   267,    -1,   339,   279,   258,   279,   259,
     279,   260,   279,   264,   279,   265,   279,   263,   279,   261,
     279,   251,   279,   267,    -1,   339,   279,   258,   279,   259,
     279,   260,    -1,   300,   279,   262,    -1,   341,   279,   258,
      -1,   341,   279,   291,    -1,   301,    -1,   333,    -1,   343,
     279,   304,   279,   271,    -1,   338,   279,   304,   279,   271,
     279,   271,    -1,   338,   279,   304,   279,   271,   279,   271,
     279,   246,    -1,   302,    -1,   329,   279,   304,   279,   271,
      -1,   328,   279,   304,   279,   271,   279,   271,    -1,   328,
     279,   304,   279,   271,   279,   271,   279,   246,    -1,   326,
      -1,   336,    -1,   327,   279,   304,   279,   275,    -1,   337,
     279,   304,   279,   275,    -1,   344,   279,   304,   279,   275,
     279,   275,    -1,   335,   279,   304,   279,   275,   279,   275,
     279,   271,    -1,   331,   279,   304,   279,   275,   279,   275,
      -1,   330,   279,   304,   279,   275,   279,   275,   279,   271,
      -1,   303,    -1,   300,   279,   304,   279,   262,    -1,   300,
     279,   315,   279,   247,   279,   262,    -1,   300,   279,   316,
     279,   262,    -1,   300,   279,   317,   279,   262,    -1,   321,
     279,   304,   279,   264,    -1,   348,   279,   304,    -1,   318,
      -1,   319,    -1,   340,   279,   258,    -1,   340,   279,   291,
      -1,   339,   279,   304,   279,   258,   279,   259,   279,   260,
      -1,   342,    -1,   341,   279,   304,   279,   258,    -1,   325,
     279,   275,   279,   271,     4,   268,    -1,   330,   279,   275,
     279,   275,   279,   271,     4,   268,    -1,   334,   279,   275,
     279,   271,     4,   268,    -1,   335,   279,   275,   279,   275,
     279,   271,     4,   268,    -1,   300,   279,   245,    -1,   341,
     279,   356,   279,   258,   279,   266,    -1,   357,   279,   270,
      -1,   327,   279,   271,   279,   246,    -1,   327,   279,   271,
      -1,   337,   279,   271,   279,   246,    -1,   337,   279,   271,
      -1,   300,   279,   262,    -1,   340,   279,   258,    -1,   340,
     279,   291,    -1,   327,   279,   275,    -1,   337,   279,   275,
      -1,   320,   279,   249,    -1,   321,   279,   250,    -1,   327,
     279,   262,   279,   252,    -1,   331,   279,   262,   279,   253,
     279,   253,    -1,   332,   279,   262,   279,   254,    -1,   347,
     279,   262,   279,   252,   279,   255,   279,   256,    -1,   337,
     279,   262,   279,   252,    -1,   344,   279,   262,   279,   255,
      -1,   345,   279,   262,   279,   256,    -1,   346,   279,   262,
     279,   257,    -1,   349,   279,   262,   279,   261,    -1,   350,
     279,   262,   279,   270,    -1,   351,   279,   262,   279,   270,
      -1,   341,   279,   262,   279,   258,    -1,   341,   279,   262,
     279,   292,    -1,   341,   279,   262,   279,   293,    -1,   271,
       4,   268,    -1,   246,   279,   271,     4,   268,    -1,   352,
      -1,   353,    -1,   326,    -1,   336,    -1,   303,    -1,   301,
      -1,   333,    -1,   302,    -1,   340,   279,   258,    -1,   340,
     279,   291,    -1,   342,    -1,   265,   279,   263,   279,   262,
      -1,   294,   279,   265,   279,   263,   279,   262,    -1,   264,
     279,   262,    -1,   322,    -1,   323,    -1,   324,    -1,   275,
      -1,   275,    -1,   271,    -1,   275,    -1,   275,    -1,   291,
      -1,   271,    -1,   275,    -1,   275,    -1,   275,    -1,   272,
      -1,   275,    -1,   275,    -1,   275,    -1,   271,    -1,   278,
      -1,   278,    -1,   278,    -1,   269,    -1,   268,     5,   269,
      -1,   271,    -1,   278,    -1,   275,    -1,   272,    -1,   275,
      -1,   271,    -1,   276,    -1,   271,   276,    -1,   273,     6,
     273,    -1,     7,   273,     6,   273,    -1,     8,   273,     6,
     273,    -1,   274,    -1,   273,   274,    -1,     9,    -1,    10,
      -1,    11,    -1,    12,    -1,    13,    -1,    14,    -1,    15,
      -1,    16,    -1,    17,    -1,    18,    -1,   274,    -1,    10,
     273,    -1,    11,   273,    -1,    12,   273,    -1,    13,   273,
      -1,    14,   273,    -1,    15,   273,    -1,    16,   273,    -1,
      17,   273,    -1,    18,   273,    -1,    19,    -1,    20,    -1,
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
     220,    -1,   221,    -1,   279,    -1,   271,    -1,   277,   279,
      -1,   277,   271,    -1,   222,   277,   222,    -1,   223,   277,
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
      27,    89,    27,    32,    34,    39,    38,    -1,    37,    23,
      36,    40,    23,    36,    -1,    40,    33,    30,    39,    31,
      23,    -1,    31,    39,    38,    23,    -1,    37,    33,    30,
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
     214,   215,   218,   219,   220,   221,   222,   223,   224,   227,
     228,   229,   230,   233,   236,   237,   240,   241,   244,   245,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   264,   265,   268,   269,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   283,   284,   287,
     290,   291,   292,   295,   298,   301,   304,   307,   308,   311,
     314,   317,   320,   323,   324,   327,   330,   333,   336,   339,
     342,   345,   346,   349,   350,   351,   352,   360,   361,   364,
     365,   368,   369,   370,   374,   375,   378,   379,   380,   381,
     382,   383,   384,   385,   386,   387,   390,   391,   392,   393,
     394,   395,   396,   397,   398,   399,   401,   401,   401,   401,
     401,   401,   401,   401,   401,   401,   401,   401,   401,   401,
     401,   401,   401,   401,   401,   401,   401,   401,   401,   401,
     401,   401,   402,   402,   402,   402,   402,   402,   402,   402,
     402,   402,   402,   402,   402,   402,   402,   402,   402,   402,
     402,   402,   402,   402,   402,   402,   402,   402,   403,   403,
     403,   403,   403,   403,   403,   403,   403,   403,   404,   404,
     404,   404,   404,   404,   404,   404,   404,   404,   404,   404,
     404,   405,   405,   405,   405,   405,   405,   405,   406,   406,
     406,   406,   406,   407,   407,   407,   407,   408,   408,   408,
     409,   409,   409,   410,   410,   410,   411,   411,   411,   412,
     412,   412,   413,   413,   413,   414,   414,   414,   415,   415,
     415,   416,   416,   416,   417,   417,   417,   418,   418,   418,
     419,   419,   419,   420,   420,   420,   421,   421,   421,   422,
     422,   422,   423,   423,   423,   424,   424,   424,   425,   425,
     425,   426,   426,   426,   427,   427,   427,   428,   428,   428,
     429,   429,   429,   430,   430,   430,   431,   431,   431,   432,
     432,   432,   433,   433,   433,   434,   434,   434,   435,   435,
     435,   436,   436,   436,   437,   437,   437,   438,   438,   438,
     439,   439,   439,   440,   440,   440,   441,   441,   441,   442,
     442,   442,   443,   443,   443,   444,   444,   444,   445,   445,
     445,   446,   446,   446,   447,   447,   447,   448,   448,   448,
     449,   449,   449,   450,   450,   453,   454,   455,   456,   459,
     460,   466,   469,   472,   475,   478,   481,   484,   487,   490,
     493,   496,   499,   502,   505,   508,   511,   514,   517,   520,
     523,   526,   529,   532,   535,   538,   541,   544,   547,   550,
     553,   556,   559,   562,   565,   568,   571,   574,   577,   580,
     583,   586,   589,   592,   595,   598,   601,   604,   607,   610,
     613,   616,   619,   622,   625,   628,   631,   634,   637,   640,
     643,   646,   649,   652,   655,   658,   661,   664,   667,   670,
     673,   676,   679,   682,   685,   688,   691,   694,   697,   700,
     703
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
  "midi_bank", "midi_prog", "volume_value", "sampler_channel",
  "instrument_index", "engine_name", "filename", "map_name", "entry_name",
  "param_val_list", "param_val", "boolean", "string", "dotnum", "digits",
  "digit", "number", "char", "text", "stringval", "SP", "LF", "CR", "ADD",
  "GET", "MAP", "UNMAP", "CLEAR", "CREATE", "DESTROY", "LIST", "LOAD",
  "ALL", "NONE", "DEFAULT", "NON_MODAL", "REMOVE", "SET", "SUBSCRIBE",
  "UNSUBSCRIBE", "SELECT", "CHANNEL", "AVAILABLE_ENGINES",
  "AVAILABLE_AUDIO_OUTPUT_DRIVERS", "CHANNELS", "INFO",
  "AUDIO_OUTPUT_DEVICE_COUNT", "AUDIO_OUTPUT_DEVICE_INFO",
  "MIDI_INPUT_DEVICE_COUNT", "MIDI_INPUT_DEVICE_INFO",
  "MIDI_INSTRUMENT_MAP_COUNT", "MIDI_INSTRUMENT_MAP_INFO",
  "MIDI_INSTRUMENT_COUNT", "MIDI_INSTRUMENT_INFO", "CHANNEL_COUNT",
  "CHANNEL_INFO", "BUFFER_FILL", "STREAM_COUNT", "VOICE_COUNT",
  "TOTAL_VOICE_COUNT", "TOTAL_VOICE_COUNT_MAX", "INSTRUMENT", "ENGINE",
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
  "SERVER", "VOLUME", "MUTE", "SOLO", "BYTES", "PERCENTAGE", "RESET",
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
     232,   232,   232,   233,   233,   233,   233,   233,   233,   233,
     233,   233,   233,   233,   233,   233,   233,   233,   234,   234,
     234,   234,   234,   234,   234,   234,   234,   234,   234,   234,
     234,   234,   234,   235,   235,   235,   235,   236,   237,   237,
     237,   238,   238,   238,   238,   238,   238,   238,   238,   238,
     238,   238,   238,   238,   238,   238,   238,   238,   238,   238,
     238,   238,   238,   238,   238,   238,   238,   238,   238,   238,
     238,   238,   239,   239,   239,   239,   239,   239,   239,   240,
     240,   240,   240,   241,   242,   242,   243,   243,   244,   244,
     245,   245,   245,   245,   245,   245,   245,   245,   245,   245,
     245,   245,   245,   245,   246,   246,   247,   247,   248,   248,
     248,   248,   248,   248,   248,   248,   248,   249,   249,   250,
     251,   251,   251,   252,   253,   254,   255,   256,   256,   257,
     258,   259,   260,   261,   261,   262,   263,   264,   265,   266,
     267,   268,   268,   269,   269,   269,   269,   270,   270,   271,
     271,   272,   272,   272,   273,   273,   274,   274,   274,   274,
     274,   274,   274,   274,   274,   274,   275,   275,   275,   275,
     275,   275,   275,   275,   275,   275,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   277,   277,   277,   277,   278,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   352,   353,   354,   355,   356,   357,
     358
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
       1,     5,     7,     9,     7,     9,     3,     7,     3,     5,
       3,     5,     3,     3,     3,     3,     3,     3,     3,     3,
       5,     7,     5,     9,     5,     5,     5,     5,     5,     5,
       5,     5,     5,     5,     3,     5,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     1,     5,     7,     3,
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
       6,     6,     4,     4,     5,    10,     5,    13,     4,     4,
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
       0,     0,     0,     0,     0,     0,     1,   432,   433,     2,
       0,     9,   284,   279,   278,   276,   277,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   268,
     270,   271,   272,   273,   274,   275,   280,   281,   282,   283,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
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
     431,    12,   196,    11,   179,    10,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   434,     0,     0,     0,   435,     0,     0,   436,     0,
       0,     0,     0,   448,     0,     0,     0,     3,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   197,   184,
     198,   199,   200,   201,   202,   203,   204,   205,   269,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   180,
       0,     0,    13,    30,    31,     0,     0,     0,     0,     0,
       0,    16,     0,    71,    76,    88,    95,    96,     0,    80,
       0,     0,     0,     0,     0,    72,     0,    81,     0,     0,
       0,     0,     0,   100,     0,     0,     0,     0,    14,     0,
      15,     0,     0,    27,     0,     0,     0,    17,     0,     0,
      18,     0,     0,     0,     0,     0,    19,   141,   143,   140,
     138,   142,   139,     0,   146,     0,    20,     0,     0,    21,
       0,     0,     0,     0,     0,    22,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      23,    33,    34,    35,    36,    42,    43,    44,    45,    37,
      41,    40,    39,    38,    47,    46,    24,    48,    49,    50,
      51,    57,    58,    59,    60,    52,    56,    55,    54,    53,
      62,    61,   426,    25,   425,    26,     0,     0,     0,     0,
     441,   442,   510,     0,     0,     0,     0,     0,     0,   185,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   428,   427,     0,   438,     0,     0,     0,
     506,     0,     0,   437,     0,     0,     0,     0,     0,    32,
     169,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   187,   188,   189,   190,   191,   192,   193,
     194,   195,     0,    97,   160,    98,     0,     0,     0,    94,
       0,     0,     0,     0,   114,   115,     0,     0,   110,   112,
     116,   117,     0,     0,     0,   144,   145,     0,     0,   118,
       0,   168,     0,   119,     0,   167,    68,   165,    69,    70,
       0,     0,     0,     0,     0,     0,     0,   106,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   108,   178,   177,     0,
       0,     0,     0,     0,     0,     0,     0,   113,   439,     0,
     447,   451,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   509,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   440,     0,     0,     0,     0,   429,
     430,     0,     0,     0,     0,     0,     0,     0,     0,    89,
       0,     0,     0,   136,   137,    91,    92,    93,    82,     0,
      77,     0,     0,     0,    83,     0,     0,   443,   101,    73,
       0,     0,     0,   161,     0,     0,     0,     0,   109,     0,
     111,     0,     0,     0,     0,     0,     0,   166,     0,   149,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     473,     0,   500,     0,   456,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   502,   503,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   508,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   449,     0,   452,     0,     0,     0,   452,
       0,     0,     0,     0,    90,    78,     0,    86,     0,    74,
       0,    84,     0,     0,   162,    67,     0,     0,     0,     0,
     276,   277,   134,   171,   173,   176,     0,   184,   175,   174,
       0,     0,     0,     0,     0,   147,     0,     0,     0,     0,
       0,     0,   120,   153,     0,   154,   122,   155,   124,     0,
       0,   131,   132,   133,   125,   156,   126,   157,   158,   127,
     159,     0,     0,     0,   128,   163,   164,   129,   130,   102,
       0,   104,     0,   107,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   455,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   501,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   450,     0,     0,     0,     0,     0,     0,
     504,     0,    79,    87,    85,    75,    99,     0,     0,     0,
       0,     0,   135,     0,     0,   172,   181,     0,     0,     0,
       0,     0,   148,     0,     0,     0,     0,   121,     0,     0,
       0,   103,   105,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   182,   183,     0,     0,     0,
     472,     0,     0,     0,     0,     0,     0,   444,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   446,     0,     0,     0,
       0,     0,   123,     0,   467,     0,     0,     0,     0,     0,
       0,     0,   469,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   499,     0,     0,     0,   466,
       0,     0,     0,   468,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   445,
       0,   465,     0,     0,   507,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   505,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   496,   491,     0,
     491,    63,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     492,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   453,     0,   489,   495,
       0,     0,   470,     0,     0,    64,    65,   170,   150,   151,
     152,     0,   489,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   496,   498,     0,     0,     0,     0,     0,   470,
       0,     0,     0,     0,     0,     0,   488,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   493,     0,
     479,   481,     0,     0,     0,     0,   493,     0,     0,     0,
      66,   479,     0,     0,     0,     0,     0,     0,   484,     0,
       0,     0,     0,     0,     0,     0,   483,   478,     0,     0,
       0,     0,     0,   494,     0,     0,     0,     0,     0,     0,
       0,   497,     0,     0,     0,     0,   464,     0,     0,     0,
       0,     0,     0,     0,   471,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   463,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   483,     0,     0,
       0,   460,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   459,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     458,     0,   462,     0,     0,     0,     0,     0,   487,   474,
       0,     0,     0,   457,   461,     0,     0,     0,     0,     0,
       0,   476,     0,     0,     0,     0,     0,     0,   490,     0,
       0,   486,     0,     0,     0,   485,     0,     0,     0,   480,
       0,     0,   477,   482,   454,   475
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    13,    14,    15,    16,   342,   430,   446,   378,   380,
     409,   351,   415,   387,   465,   383,   390,   406,   637,   798,
     772,   396,   619,   623,  1345,   962,   964,   966,   974,   976,
     979,   593,   792,   933,   984,   626,   806,   624,   620,   559,
    1346,   942,   943,   656,   944,   945,   946,   272,   627,   274,
     463,   949,   871,    49,    50,    17,    18,    19,    20,    21,
      22,    23,    24,    25,   978,   972,   973,   622,    26,    27,
      28,    29,    30,   343,   353,   354,   355,   569,   431,   432,
     433,   434,   435,   436,   437,   438,   439,   440,   441,   442,
     443,   356,   357,   407,   358,  1348,  1349,  1350,   417,   359,
     360,   361,   362,   363,   364,   640,   365,   419,   366,   367,
     368,   369,   370,   371,   344,   373,   374,   375,   644,   645,
     646,   376,   647,   648,   649,   773,   774,    31,   445,   655,
     422,    32
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -868
static const yytype_int16 yypact[] =
{
      68,  -868,  -868,    37,    99,    71,    86,   128,   114,   117,
     167,    83,   108,   177,    -6,  1895,  -868,   -25,   -25,   -25,
     -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,
     -25,   -25,  -868,   300,   221,   301,   288,   290,   293,   312,
     299,   307,   122,    70,   316,   154,  -868,  -868,  -868,  -868,
     113,  -868,  -868,  -868,  -868,  -868,  -868,  -868,   443,   443,
     443,   443,   443,   443,   443,   443,   443,  -868,  -868,  -868,
    -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,
    -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,
    -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,
    -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,
    -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,
    -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,
    -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,
    -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,
    -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,
    -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,
    -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,
    -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,
    -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,
    -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,
    -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,
    -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,
    -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,
    -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,
    -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,
    -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,
    -868,  2560,  -868,  -868,  -868,  -868,   162,   126,   308,   308,
     309,   111,   111,   157,   131,   162,   129,   106,   106,  2117,
     320,  -868,   323,   325,   314,  -868,   324,   341,  -868,   327,
     334,   345,   347,  -868,   335,   356,   339,  -868,  -868,  -868,
    -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,   443,  -868,
     443,   443,   443,   443,   443,   443,   443,   443,  -868,  -868,
    -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,
     353,   354,  -868,  -868,   -25,   227,   357,   348,   358,   361,
     364,  -868,   -25,  -868,  -868,  -868,  -868,  -868,   -25,  -868,
     -25,   -25,   -25,   -25,   -25,  -868,   -25,  -868,   -25,   -25,
     -25,   -25,   -25,  -868,   -25,   -25,   -25,   359,  -868,   -25,
    -868,   -25,   360,  -868,   -25,   350,   363,  -868,   -25,   -25,
    -868,   -25,   -25,   233,   365,   367,  -868,  -868,  -868,  -868,
    -868,  -868,  -868,   -25,  -868,   366,  -868,   -25,   -25,  -868,
     -25,   -25,   369,   378,   373,  -868,   -25,   -25,   -25,   -25,
     -25,   -25,   -25,   370,   396,   410,   412,   399,   408,   409,
    -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,
    -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,
    -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,
    -868,  -868,  2560,  2117,  -868,  -868,   -25,   404,   405,   411,
    -868,  -868,  -868,   406,   434,   423,   424,   415,   454,  -868,
     456,   451,    53,   455,   457,   459,   458,   460,   444,   441,
     101,   461,   461,   461,   461,   461,   461,   461,   461,   461,
     461,   402,   461,   461,   461,   461,   462,   453,   453,   463,
     402,   464,   467,  2560,  2560,   453,   453,   468,   472,   470,
     402,   466,    11,  2560,   453,   402,   473,   471,   476,    44,
     453,   453,   453,   453,   449,  2779,   477,   480,   481,    40,
     469,   474,   482,  2560,  -868,   453,  -868,   484,   475,   487,
    -868,   485,   478,  -868,   483,   490,   486,  2117,  2117,  -868,
    -868,   488,   497,   494,   500,   501,   489,   511,   499,   -25,
     -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,
     -25,   -25,   -25,   443,   443,   443,   443,   443,   443,   443,
     443,   443,   502,  -868,  -868,  -868,   -25,   -25,   -25,  -868,
     506,   -25,   -25,   507,  -868,  -868,   508,   509,  2117,  2117,
    -868,  -868,   510,   521,   512,  -868,  -868,   503,   505,  -868,
     -25,  -868,   -25,  -868,   -25,  2560,  -868,  -868,  -868,  -868,
     513,   535,   542,   540,   112,   547,   551,  -868,   -25,   -25,
     -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,
     -25,   -25,   -25,   -25,   566,   -25,  -868,  2560,  -868,   561,
     565,   558,   564,   571,   572,   577,   576,  -868,  -868,   555,
    -868,  -868,   573,   578,   569,   514,  1451,  1673,   575,   574,
     570,   579,   517,   587,   582,   589,   453,    46,   453,   453,
    2560,   453,  2560,  2560,   453,   453,   453,   453,  2560,   453,
     584,   453,  2560,   453,   526,   453,   453,   527,   585,   528,
    2560,  2560,   586,   588,   532,   603,   590,   453,    53,   453,
     608,  -868,   553,   621,   622,   607,   616,   617,   453,   453,
     453,   453,   453,   453,   453,   453,   453,   453,   453,   453,
    2560,   453,  2560,   453,   618,   453,   615,   627,   619,   563,
     630,   635,   625,   633,  -868,   638,   623,   640,   637,  -868,
    -868,   580,   646,   643,   644,   641,   634,   583,   642,  -868,
     628,   650,   -25,  -868,  -868,  -868,  -868,  -868,  -868,  2117,
    2560,   -25,   -25,   -25,  -868,  2117,   -25,  -868,  -868,  2560,
     -25,   647,   -25,  -868,   -25,   649,   595,   651,   -25,  2998,
     -25,   597,   656,   661,   654,   601,   -25,  -868,   -25,  -868,
     605,   668,   670,   671,   676,   667,   662,   -25,   -25,   -25,
     -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,  3217,
     -25,  3436,   -25,   679,   -25,   620,   669,   681,   680,   678,
     675,   624,   626,   687,   684,   682,   685,   683,   694,   688,
    -868,   689,  -868,   686,  -868,   690,   696,   453,  2560,   453,
     453,   453,  2560,   453,   453,   691,   453,   453,   692,   697,
     693,  2560,  2339,   700,   704,   703,   705,   706,   453,   453,
     707,   709,   710,   631,  -868,  -868,   708,   453,   453,  2560,
     453,   102,   453,   402,  2560,   453,   416,  2779,  2779,  2339,
    2560,  2339,  2560,  -868,    53,   711,   653,   715,   714,   717,
     659,   698,   701,  -868,   699,  -868,   712,   713,   720,   716,
     206,   718,   731,   734,  -868,  2117,   -25,  -868,   -25,  2117,
     -25,  -868,   719,   -25,  -868,  -868,   721,   722,   725,  3655,
     443,   443,   755,  -868,  2560,  -868,   156,    29,  -868,  -868,
     723,   716,   222,   740,   732,  -868,   -25,   730,   224,   695,
     745,   750,  -868,  -868,   -25,  -868,  -868,  2560,  -868,   751,
     743,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,
    2560,   -25,   443,   443,  -868,  -868,  -868,  -868,  -868,   755,
    3874,   755,  4093,  -868,   739,   756,   727,   226,   762,   761,
     752,   753,   760,   749,   754,   765,  -868,   757,   759,   763,
     758,   766,  2560,  2560,  2560,  2560,   453,   776,  2560,   780,
     782,   783,  2339,   289,   303,  2339,   443,   785,   786,   788,
     767,   772,   453,   789,   790,   768,   792,  -868,   453,   774,
     796,   453,  2339,  2339,   793,   773,   173,   791,   794,   802,
     803,   808,   798,  -868,   804,   787,   775,   800,   805,   818,
    -868,   810,   -25,  2560,  2560,   -25,  -868,   807,   -25,   812,
     820,   806,   755,   443,   443,  -868,   443,   821,   823,   827,
     828,   837,  -868,   833,   830,   832,   228,  -868,   850,   849,
     -25,   755,   755,   841,   856,   847,   857,   852,   855,   865,
     853,   872,   862,   858,   859,   161,   811,   860,   873,   866,
     864,    53,   867,   869,   816,   443,   443,   870,   834,   877,
    -868,   882,   878,   835,   881,   883,   886,  -868,   402,   887,
     901,   894,   871,   845,   896,   903,   905,   915,   902,   908,
     907,   909,   914,   920,   153,   919,   863,   932,   922,   -25,
     923,   917,   934,   921,   935,   927,  -868,   924,   164,   926,
     925,   931,  -868,   929,  -868,   936,   938,   950,   942,   937,
     939,   885,  -868,   952,   889,   957,   955,   959,    47,   949,
     965,   968,   966,   967,   453,   969,   904,   971,   906,   973,
     976,   911,   978,   972,   970,   918,   974,   928,   977,  -868,
     983,   987,   979,  -868,   997,   988,   248,   992,   994,   995,
     985,   996,   990,   998,   999,  1008,  1001,   -25,  1004,  1016,
    1000,  1017,  1002,  1009,   256,  1003,  1011,  1006,    57,  -868,
    1023,  -868,  1010,  1019,  -868,  1015,  1014,  1028,    65,  1022,
    1024,   960,  1030,  1018,  1021,  1025,  1026,  -868,  1029,   416,
    1031,  1039,  1037,  1043,  1041,  1032,  1045,  1049,  1046,  1036,
     989,  1053,  1047,  1038,  1059,  1058,  1048,  1050,  1005,  1068,
    1051,  1061,  1007,  1067,  1065,  1072,  1075,  1012,     7,  1063,
    -868,   -25,  1066,  1062,  1083,  1070,  1085,    21,  1088,  1071,
    1087,  1012,    64,  1093,  1077,  1081,  1076,  1098,  1033,  1089,
    1092,  1094,  1097,  1080,  1095,  1090,  1099,  1102,  1096,  1101,
    -868,  1105,  1091,    27,  1103,  1110,  1111,  1114,  1108,  1109,
    1113,  1119,  1117,  1107,  1112,  1115,  1122,  1121,  1123,   214,
    1116,  1132,  1120,  1134,  1133,  1118,  -868,  1124,  1125,  1074,
    1140,  1141,  1078,  1129,  1142,   -25,  -868,  -868,  -868,  -868,
    -868,  1143,  -868,  1145,  1125,  1152,  1144,  1151,  1084,  1156,
    1146,  1147,  -868,  -868,  1160,  1100,  1149,  1153,  1158,  -868,
    1150,  1163,  1164,  1154,  1155,  1157,  -868,  1161,  1162,  1165,
    1166,  1126,  1167,    53,  1168,  1169,  1170,  1171,  1177,  1172,
    1173,  1178,  1184,  1185,   174,  1174,  1159,  1175,  -868,  1181,
    1179,  1128,  1180,  1183,  1193,  1200,  1186,  1203,  1202,  1188,
    -868,  -868,  1179,  1186,  1196,  1138,  1209,  1197,  -868,  1201,
    1148,  1199,  1198,  1204,  1205,  1182,  1187,  -868,  1206,  1194,
    1190,  1207,  1208,  -868,  1192,  1218,  1215,  1187,  1210,  1211,
    1222,  -868,   215,  1212,  1224,  1214,  -868,   230,  1216,  1227,
    1217,  1231,  1230,  1233,  -868,  1223,  1220,  1239,  1240,  1232,
    1228,  1235,  1236,  1237,  -868,  1241,  1243,  1244,  1245,  1191,
    1246,  1229,  1226,  1253,  1247,  1248,  1242,  -868,  1238,  1259,
    1249,  -868,  1250,  1262,  1252,  1271,  1269,  1265,  1270,  1272,
    1266,  1274,  1275,  1276,  1268,  1273,  -868,  1278,  1279,  1283,
    1277,  1267,  1280,  1281,  1285,  1289,  1284,  1282,  1286,  1287,
    -868,  1288,  -868,  1291,  1292,  1290,  1300,  1304,  -868,  1251,
    1293,  1306,  1309,  -868,  -868,  1311,  1297,  1296,  1301,  1302,
    1313,  -868,  1303,  1307,  1308,  1319,  1321,  1310,  -868,  1312,
    1325,  -868,  1326,  1314,  1315,  -868,  1322,  1317,  1318,  -868,
    1320,  1333,  -868,  -868,  -868,  -868
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,
    -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  -680,
    -868,  -868,  -868,  -868,  -868,  -643,   321,  -868,   317,   232,
    -868,  -453,  -667,  -827,   115,  -507,  -861,  -660,  -701,   479,
     -22,  -825,   337,  -607,   407,  -867,   -13,   -39,   -14,   389,
    -261,  -454,   -15,  1316,  -868,  -868,  -868,  -868,  -868,  -868,
    -868,  -868,  -868,  -868,  -428,  -868,  -868,  -868,  -868,  -868,
    -868,  -868,  -868,  -154,  1082,  1104,  1106,  -289,  1079,  1086,
    1127,  1130,  1135,  1136,  1139,  1386,  1607,  1829,  -253,  -252,
    -251,    23,  -868,  -868,  1834,  -868,  -868,  -868,  -868,  1131,
    -249,  -868,  -868,  2053,   839,  -868,  2057,  -868,  4029,  4033,
    -240,  -868,    48,   -12,  -221,  4034,  -868,   842,  -868,  -868,
    -868,  -868,  -868,  -868,  -868,  -868,  -868,  -868,  4030,  -868,
    -868,  -868
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -197
static const yytype_int16 yytable[] =
{
     275,   273,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   808,   956,   319,
     319,   319,   319,   319,   319,   319,   319,   319,   560,   985,
     777,   800,   388,   391,  -196,   457,   458,   459,   667,   794,
     935,   389,   392,   618,  1310,   318,   320,   321,   322,   323,
     324,   325,   326,   327,   601,   602,   372,   604,  1310,    33,
    1343,  1344,   662,   633,   411,   421,   770,   615,   621,     1,
    1210,     2,   628,   595,   989,   634,   991,   663,  1261,  1187,
     771,   635,   605,  1211,   636,  1322,  1251,     3,  1270,     4,
       5,  1262,   616,     6,    36,  1263,  1311,   629,     7,     8,
     302,  1271,  1323,     9,    10,    11,    43,    12,   303,    37,
    1318,   308,   583,   584,   585,   586,   587,   588,   589,   590,
     591,   424,    44,   352,   969,   423,   424,   425,   568,    34,
     385,   410,   416,    40,   970,    35,   466,   426,   427,   724,
      45,   429,   386,   427,   428,   345,   429,   346,   412,   347,
     340,   725,   413,   300,   347,    38,    41,   348,   405,   301,
     414,    39,  1026,   349,   350,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,  1178,   393,    46,   394,   769,
    1141,   775,   776,   340,  1142,   305,  1192,  1179,   395,  1066,
      42,   306,  1143,   341,  1095,  1421,   930,  1072,  1193,   270,
    1096,  1422,   573,   574,   575,   576,   577,   578,   579,   580,
     581,   582,   809,   596,   597,   598,   599,  1091,  1092,    47,
      48,   817,   818,   819,   820,   821,   822,   823,   824,   825,
     826,   827,   828,   557,   558,  1366,  1460,   570,   571,   572,
    1007,  1367,  1461,  1008,   292,  1368,   786,   968,   788,   557,
     558,  1465,   981,  -196,  -196,  -196,  1028,  1466,  1034,  1029,
    1047,  1003,  1125,  1048,   621,  1003,   483,   484,   384,  1237,
    1238,   403,   517,   484,   464,   557,   558,  1256,  1257,   479,
     638,   479,   479,   479,   479,   479,   479,   479,   479,   641,
     987,   988,   834,    -4,    -4,  1073,   676,   677,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   642,  1074,
     444,   460,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   291,  1217,   293,   294,   379,   381,   295,   482,
     296,   297,  1062,   298,   299,  1065,   304,   490,    47,   377,
     382,   340,   467,   491,   468,   492,   493,   494,   495,   496,
     924,   497,   469,   498,   499,   500,   501,   502,  1068,   503,
     504,   505,   470,   471,   507,   472,   508,   473,   474,   510,
     475,   955,   476,   513,   514,   477,   515,   516,   478,   480,
     486,   481,   985,   485,   488,   487,   506,   509,   520,   511,
     512,   518,   522,   523,   519,   524,   525,   489,   521,   527,
     528,   529,   530,   531,   532,   533,   534,   535,   526,   536,
    1149,   308,   583,   584,   585,   586,   587,   588,   589,   590,
     591,   592,   271,   982,   983,   308,   583,   584,   585,   586,
     587,   588,   589,   590,   591,   537,   538,   540,   971,   539,
     546,   541,   542,   547,   551,   552,   549,   548,   544,   553,
     560,   545,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   308,   583,   584,   585,   586,   587,   588,   589,
     590,   591,   550,   556,   554,   555,   562,   561,   563,   567,
     566,   654,   565,   564,   600,   603,   606,   594,   568,   607,
     612,   613,   614,   594,   594,   630,   594,   631,   632,   659,
     661,   610,   611,   617,   660,   664,   594,   668,   669,   666,
     670,   594,   665,   675,   672,   678,   650,   651,   652,   653,
     673,   658,   674,   671,   679,  1082,   680,   681,   682,   683,
     684,   685,   700,   704,   707,   708,   709,   712,   716,   714,
     720,   715,   464,   464,   319,   319,   319,   319,   319,   319,
     319,   319,   319,   713,   686,   687,   688,   689,   690,   691,
     692,   693,   694,   695,   696,   697,   698,   699,   721,   722,
     318,   320,   321,   322,   323,   324,   325,   326,   327,   723,
     726,   701,   702,   703,   727,   744,   705,   706,   746,   747,
     748,   749,   750,   710,   711,   751,   752,   753,   754,   756,
     755,   757,   763,   758,   762,   717,   765,   718,   761,   719,
     766,   764,   767,   768,   787,   791,   795,   797,   796,   801,
     802,   803,   805,   728,   729,   730,   731,   732,   733,   734,
     735,   736,   737,   738,   739,   740,   741,   742,   743,   804,
     745,   810,   811,   812,   813,   814,   815,   816,   835,   833,
     836,   837,   838,   839,   840,   841,   842,   621,   843,   844,
     339,   544,   544,   845,   846,   848,   849,   850,   851,   847,
     852,   855,   853,   856,   865,   854,   868,   778,   870,   874,
     781,   782,   783,   784,   869,   594,   873,   594,   875,   790,
     877,   793,   793,   876,   880,   881,   462,   882,   883,   884,
     885,   886,   903,   807,   907,   906,   910,   908,   909,   905,
     913,   914,   915,   911,   918,   912,   917,   916,   919,  1002,
     960,   920,  1001,   932,   936,   938,   921,   830,   922,   832,
     937,   594,   923,   950,   951,   952,   953,   954,  1000,   961,
     957,   958,   995,   959,   994,   996,   997,   998,   999,  1003,
    1005,  1009,  1004,  1006,  1010,  1011,  1017,   857,  1019,  1021,
    1025,  1020,  1027,  1030,   858,  1031,   859,   860,   861,  1033,
     862,   863,  1036,  1037,  1039,   864,  1040,   866,  1044,   867,
    1045,  1049,  1050,  1053,  1035,  1051,  1052,  1054,  1056,  1061,
    1059,   878,  1055,   879,  1081,  1060,  1057,  1058,  1088,  1080,
    1094,  1085,   887,   888,   889,   890,   891,   892,   893,   894,
     895,   896,   897,   898,  1067,   900,  1046,   902,  1069,   904,
    1070,  1104,  1071,  1077,  1086,  1078,  1079,  1083,  1089,  1084,
    1097,  1093,  1098,   947,  1099,  1101,  1100,  1102,  1106,  1108,
    1103,  1107,  1109,  1110,  1114,   926,   927,   928,  1112,   793,
     931,   339,   934,   934,  1113,  1117,  1121,   947,   948,  1347,
     947,  1118,   947,  1119,  1105,   807,  1120,  1122,  1123,  1126,
     543,  1124,  1127,   963,   965,  1129,   963,   594,   975,   977,
    1131,   963,   986,   658,   658,   948,  1130,   948,  1135,  1132,
    1133,  1134,  1136,  1137,  1138,  1166,  1146,  1139,  1140,  1145,
    1144,   319,   319,  1148,  1147,  1152,  1150,   479,  1151,  1153,
    1012,  1013,  1156,  1014,  1015,  1016,  1155,  1157,  1018,  1159,
     608,   609,  1160,  1154,  1158,  1161,  1163,  1023,  1024,  1347,
     625,  1164,   339,  1165,  1167,  1168,  1169,  1170,  1171,  1173,
    1172,  1032,   657,   319,   319,  1174,  1176,  1177,  1175,  1038,
    1180,  1182,  1181,  1183,  1185,  1186,  1187,  1189,  1190,  1188,
    1194,  1196,  1191,  1195,   462,   462,  1041,  1197,  1198,  1023,
    1024,  1199,  1200,  1201,  1204,  1205,  1202,  1203,  1206,  1207,
    1208,  1209,  1212,   947,   479,   479,   947,   319,  1213,  1214,
    1216,  1215,  1218,  1219,  1220,  1221,  1222,   339,   339,  1223,
    1224,  1225,   934,   947,   947,  1226,  1232,  1228,   948,  1227,
    1233,   948,  1229,  1076,   339,  1231,  1234,  1230,  1235,  1239,
    1236,  1240,  1241,  1243,   965,  1242,  1244,   975,   948,   948,
    1245,  1247,  1246,  1248,   319,   319,  1250,   479,  1251,  1253,
    1252,  1255,  1254,  1258,  1260,  1264,   339,  1259,  1267,  1274,
    1265,  1266,  1268,  1111,  1269,  1272,  1273,  1275,  1276,  1277,
    1115,  1116,  1283,  1278,  1284,  1279,  1285,  1280,  1286,  1282,
    1287,  1288,  1289,  1290,  1291,  1128,   479,   479,  1292,  1293,
    1294,  1295,  1296,   543,   543,  1297,  1298,  1301,  1303,  1299,
    1305,  1302,  1306,  1307,  1300,  1312,  1304,   625,  1308,   779,
     780,  1309,  1314,  1310,  1315,   785,  1317,  1319,  1321,   789,
    1316,  1320,  1324,  1325,   977,  1326,  1327,   799,   799,  1328,
    1334,  1330,  1329,  1331,  1333,  1338,  1332,  1336,  1335,  1342,
    1351,  1337,  1339,  1352,  1184,  1340,  1341,  1354,  1353,  1355,
    1357,  1356,  1358,  1359,  1361,  1363,  1365,   829,  1364,   831,
    1360,  1370,  1371,  1362,  1369,  1372,  1373,  1374,  1375,  1378,
    1379,  1381,  1376,  1377,  1384,  1382,  1385,  1380,   339,   339,
     807,  1386,  1388,  1389,   339,  1390,  1387,  1397,   339,  1392,
    1391,  1393,  1395,  1424,  1398,  1396,  1399,  1400,   339,  1394,
    1401,  1411,  1412,  1402,  1414,  1404,  1403,  1407,  1405,  1406,
    1415,  1418,  1249,  1409,  1413,  1417,  1416,  1419,  1420,  1425,
     947,  1426,  1431,  1423,  1429,  1408,  1427,  1428,   339,  1432,
     339,  1430,  1434,  1433,  1435,  1436,  1437,  1438,  1439,  1440,
    1444,  1441,  1443,  1450,  1454,   986,  1445,  1442,  1446,  1453,
    1449,  1455,  1456,  1452,  1457,  1459,  1468,  1458,  1463,  1471,
    1467,  1462,  1464,  1470,  1473,  1469,  1472,  1474,  1475,  1476,
    1488,  1478,  1477,  1484,  1489,   925,  1313,  1479,  1480,   929,
    1481,  1447,  1490,  1493,  1482,  1483,  1448,  1494,   939,  1451,
    1486,  1485,  1487,  1495,  1492,  1491,  1498,  1496,  1499,  1497,
    1500,  1501,  1502,  1503,  1507,  1504,   967,  1506,  1505,  1508,
    1509,   980,  1513,  1515,   657,   657,  1510,   990,  1514,   992,
    1511,  1519,  1512,  1521,   339,  1526,  1520,  1527,   339,  1517,
    1516,  1518,  1525,  1528,  1522,  1523,  1524,  1529,   339,  1532,
    1383,  1531,  1533,   339,  1534,  1535,  1536,  1537,  1538,  1539,
    1530,  1540,  1543,  1541,  1544,  1546,  1542,  1545,  1547,  1548,
    1549,  1550,  1551,  1552,  1553,  1555,   339,  1554,  1090,  1087,
    1162,  1410,  1075,     0,  1281,   397,   307,   447,   639,   339,
       0,   643,     0,     0,   448,     0,     0,     0,     0,   339,
       0,   339,     0,   993,     0,     0,     0,   398,     0,   399,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   400,   449,     0,     0,   450,   799,
    1063,  1064,   799,   451,   452,   625,     0,   453,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   339,   339,   328,    52,    53,    54,    55,    56,
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
     267,   268,   269,   759,   454,   270,   328,    52,    53,    54,
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
     265,   266,   267,   268,   269,   455,   760,   270,    51,    52,
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
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   456,   408,   270,
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
     261,   262,   263,   264,   265,   266,   267,   268,   269,   418,
     401,   270,   328,    52,    53,    54,   940,   941,    57,    58,
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
     269,   557,   558,   328,    52,    53,    54,    55,    56,   329,
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
     268,   269,   328,    52,    53,    54,    55,    56,    57,    58,
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
     269,   328,   872,    53,    54,    55,    56,   329,   330,   331,
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
     328,   899,    53,    54,    55,    56,   329,   330,   331,   332,
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
     901,    53,    54,    55,    56,   329,   330,   331,   332,   333,
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
     262,   263,   264,   265,   266,   267,   268,   269,   328,  1022,
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
     263,   264,   265,   266,   267,   268,   269,   328,  1042,    53,
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
     264,   265,   266,   267,   268,   269,   328,  1043,    53,    54,
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
     265,   266,   267,   268,   269,   420,   402,   404,   461
};

static const yytype_int16 yycheck[] =
{
      15,    15,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,   718,   879,    58,
      59,    60,    61,    62,    63,    64,    65,    66,   482,   896,
     690,   711,   281,   282,     5,   288,   288,   288,   545,   706,
     867,   281,   282,    32,    37,    58,    59,    60,    61,    62,
      63,    64,    65,    66,   507,   508,   277,   510,    37,    22,
      33,    34,    22,    19,   285,   286,    20,   520,   522,     1,
      23,     3,   525,   501,   899,    31,   901,    37,    21,    22,
      34,    37,   510,    36,    40,    21,    22,    19,    23,    21,
      22,    34,   520,    25,    23,    38,    89,   525,    30,    31,
      30,    36,    38,    35,    36,    37,    23,    39,    38,    23,
      89,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    20,    39,   277,    22,    19,    20,    21,    27,    30,
      19,   285,   286,    19,    32,    36,   290,    31,    37,    27,
      32,    40,    31,    37,    38,    19,    40,    21,    19,    23,
      21,    39,    23,    31,    23,    27,    39,    31,    27,    37,
      31,    33,     6,    37,    38,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    22,    19,     0,    21,   686,
      19,   688,   689,    21,    23,    31,    22,    34,    31,  1016,
      23,    37,    31,    31,    21,    21,   863,  1022,    34,   224,
      27,    27,   491,   492,   493,   494,   495,   496,   497,   498,
     499,   500,   719,   502,   503,   504,   505,  1042,  1043,   225,
     226,   728,   729,   730,   731,   732,   733,   734,   735,   736,
     737,   738,   739,   222,   223,    21,    21,   490,   490,   490,
      34,    27,    27,    37,    23,    31,   699,   890,   701,   222,
     223,    21,   895,   224,   225,   226,    34,    27,    34,    37,
      34,    37,    34,    37,   718,    37,    39,    40,   280,    21,
      22,   283,    39,    40,   289,   222,   223,    21,    22,   318,
     529,   320,   321,   322,   323,   324,   325,   326,   327,   529,
     897,   898,   745,   225,   226,     6,   557,   558,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,   529,     6,
     287,   288,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    22,  1184,    23,    37,   278,   279,    38,   344,
      37,    19,  1012,    34,    27,  1015,    20,   352,   225,    31,
      31,    21,    19,   358,    19,   360,   361,   362,   363,   364,
     857,   366,    38,   368,   369,   370,   371,   372,  1018,   374,
     375,   376,    38,    22,   379,    38,   381,    33,    23,   384,
      23,   878,    37,   388,   389,    19,   391,   392,    39,    26,
      32,    27,  1249,    26,    23,    27,    27,    27,   403,    39,
      27,    26,   407,   408,    27,   410,   411,    33,    32,    21,
      27,   416,   417,   418,   419,   420,   421,   422,    39,    39,
    1111,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    15,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    39,    26,    38,   891,    27,
      36,    33,    33,    38,    21,    21,    40,    36,   463,    34,
     904,   466,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    38,    22,    20,    19,    19,    22,    19,    38,
      36,    32,    22,    25,    22,    22,    22,   501,    27,    22,
      22,    19,    22,   507,   508,    22,   510,    26,    22,    22,
      19,   515,   516,    37,    24,    36,   520,    23,    33,    27,
      23,   525,    38,    27,    36,    27,   530,   531,   532,   533,
      37,   535,    32,    38,    27,  1032,    32,    27,    27,    40,
      19,    32,    30,    27,    27,    27,    27,    27,    33,    27,
      27,    38,   557,   558,   583,   584,   585,   586,   587,   588,
     589,   590,   591,    32,   569,   570,   571,   572,   573,   574,
     575,   576,   577,   578,   579,   580,   581,   582,    33,    27,
     583,   584,   585,   586,   587,   588,   589,   590,   591,    39,
      33,   596,   597,   598,    33,    19,   601,   602,    27,    24,
      32,    27,    21,   608,   609,    23,    19,    21,    43,    21,
      27,    32,    32,    89,    30,   620,    89,   622,    33,   624,
      23,    32,    30,    24,    30,    89,    89,    89,    33,    33,
      32,    89,    32,   638,   639,   640,   641,   642,   643,   644,
     645,   646,   647,   648,   649,   650,   651,   652,   653,    36,
     655,    33,    89,    22,    22,    38,    30,    30,    33,    31,
      23,    32,    89,    23,    19,    30,    23,  1111,    20,    36,
     271,   676,   677,    23,    27,    19,    23,    23,    27,    89,
      36,    43,    89,    23,    27,    33,    27,   691,    27,    23,
     694,   695,   696,   697,    89,   699,    89,   701,    27,   703,
      89,   705,   706,    39,    89,    27,   289,    27,    27,    23,
      33,    39,    23,   717,    23,    36,    31,    27,    30,    89,
      23,    27,    30,    89,    20,    89,    33,    32,    30,    20,
      89,    32,    21,    32,    32,    32,    40,   741,    38,   743,
      33,   745,    36,    33,    30,    32,    31,    31,    40,    31,
      33,    32,    89,    33,    33,    30,    32,    30,    89,    37,
      30,    33,    39,    37,    23,    21,    37,   772,    37,    34,
       5,    39,    39,    23,   779,    33,   781,   782,   783,    39,
     785,   786,    27,    23,    23,   790,    33,   792,    39,   794,
      24,    19,    21,    23,    89,    33,    33,    38,    23,    23,
      27,   806,    38,   808,    22,    37,    39,    38,    24,    32,
      27,    33,   817,   818,   819,   820,   821,   822,   823,   824,
     825,   826,   827,   828,    38,   830,    89,   832,    38,   834,
      38,    34,    39,    38,    32,    39,    38,    38,    32,    39,
      39,    38,    38,   872,    32,    27,    33,    39,    38,    21,
      36,    36,    32,    36,    38,   859,   860,   861,    36,   863,
     864,   462,   866,   867,    34,    34,    19,   896,   872,  1313,
     899,    38,   901,    36,    89,   879,    38,    34,    38,    19,
     463,    39,    23,   887,   888,    34,   890,   891,   892,   893,
      33,   895,   896,   897,   898,   899,    30,   901,    23,    32,
      38,    36,    39,    21,    32,    24,    23,    39,    39,    39,
      89,   940,   941,    39,    38,    89,    39,   946,    39,    39,
     925,   926,    30,   928,   929,   930,    39,    39,   933,    38,
     513,   514,    39,    89,    89,    39,    39,   940,   941,  1383,
     523,    30,   543,    39,    89,    39,    33,    32,    23,    31,
      38,   956,   535,   982,   983,    38,    32,    27,    39,   964,
      31,    19,    89,    31,    31,    38,    22,    22,    31,    38,
      34,    30,    38,    38,   557,   558,   981,    38,    32,   982,
     983,    33,    22,    31,    89,    23,    39,    38,    89,    22,
      25,    22,    33,  1022,  1023,  1024,  1025,  1026,    23,    21,
      23,    25,    23,    89,    23,    89,    23,   608,   609,    23,
      89,    23,  1016,  1042,  1043,    33,    23,    89,  1022,    39,
      23,  1025,    38,  1026,   625,    38,    37,    89,    21,    27,
      32,    27,    27,    27,  1038,    40,    36,  1041,  1042,  1043,
      32,    23,    33,    32,  1073,  1074,    32,  1076,    22,    22,
      40,    32,    40,    40,    38,    22,   657,    36,    33,    89,
      40,    32,    38,  1068,    26,    33,    32,    27,    40,    38,
    1073,  1074,    23,    38,    27,    39,    23,    38,    27,    38,
      38,    26,    23,    27,    38,  1090,  1115,  1116,    89,    26,
      33,    43,    23,   676,   677,    27,    38,    19,    27,    39,
      23,    40,    27,    21,    89,    32,    89,   690,    23,   692,
     693,    89,    40,    37,    21,   698,    21,    19,    21,   702,
      40,    40,    19,    36,  1128,    34,    40,   710,   711,    21,
      40,    32,    89,    31,    27,    23,    32,    37,    33,    38,
      27,    32,    36,    23,  1149,    34,    31,    23,    27,    31,
      27,    32,    23,    26,    32,    23,    23,   740,    27,   742,
      43,    19,    32,    38,    38,    21,    23,    39,    34,    19,
      19,    32,    37,    89,    21,    23,    21,    89,   779,   780,
    1184,    19,    21,    89,   785,    19,    32,    19,   789,    32,
      34,    21,    33,    24,    34,    32,    23,    23,   799,    89,
      36,    23,    23,    38,    23,    34,    39,    31,    36,    34,
      23,    23,  1217,    36,    34,    32,    34,    23,    23,    34,
    1249,    30,    19,    39,    34,    89,    37,    89,   829,    19,
     831,    38,    19,    37,    22,    37,    30,    89,    19,    32,
      32,    30,    33,    39,    42,  1249,    32,    89,    33,    31,
      34,    23,    27,    36,    34,    23,    19,    36,    24,    19,
      34,    39,    38,    22,    31,    38,    23,    37,    19,    19,
      31,    33,    30,    19,    38,   858,  1281,    32,    32,   862,
      33,    89,    19,    31,    33,    32,    89,    39,   871,    89,
      89,    36,    36,    24,    36,    38,    24,    38,    36,    39,
      19,    22,    27,    23,    19,    23,   889,    23,    32,    23,
      32,   894,    19,    36,   897,   898,    33,   900,    31,   902,
      32,    22,    33,    31,   925,    23,    32,    27,   929,    38,
      40,    36,    31,    23,    38,    38,    38,    23,   939,    23,
    1345,    38,    23,   944,    23,    38,    40,    36,    36,    26,
      89,    38,    23,    36,    23,    33,    38,    37,    23,    23,
      36,    36,    30,    36,    36,    22,   967,    37,  1041,  1038,
    1128,  1383,  1025,    -1,  1249,   283,    50,   288,   529,   980,
      -1,   529,    -1,    -1,   288,    -1,    -1,    -1,    -1,   990,
      -1,   992,    -1,   904,    -1,    -1,    -1,   283,    -1,   283,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   283,   288,    -1,    -1,   288,  1012,
    1013,  1014,  1015,   288,   288,  1018,    -1,   288,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1063,  1064,     3,     4,     5,     6,     7,     8,
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
     219,   220,   221,   222,   288,   224,     3,     4,     5,     6,
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
     217,   218,   219,   220,   221,   288,   223,   224,     3,     4,
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
     215,   216,   217,   218,   219,   220,   221,   288,   284,   224,
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
     213,   214,   215,   216,   217,   218,   219,   220,   221,   286,
     283,   224,     3,     4,     5,     6,     7,     8,     9,    10,
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
     217,   218,   219,   220,   221,   286,   283,   283,   288
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     1,     3,    19,    21,    22,    25,    30,    31,    35,
      36,    37,    39,   228,   229,   230,   231,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   295,   296,   297,   298,
     299,   354,   358,    22,    30,    36,    23,    23,    27,    33,
      19,    39,    23,    23,    39,    32,     0,   225,   226,   280,
     281,     3,     4,     5,     6,     7,     8,     9,    10,    11,
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
     224,   271,   274,   275,   276,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,    22,    23,    23,    37,    38,    37,    19,    34,    27,
      31,    37,    30,    38,    20,    31,    37,   280,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,   273,   274,
     273,   273,   273,   273,   273,   273,   273,   273,     3,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,   276,
      21,    31,   232,   300,   341,    19,    21,    23,    31,    37,
      38,   238,   300,   301,   302,   303,   318,   319,   321,   326,
     327,   328,   329,   330,   331,   333,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   348,    31,   235,   339,
     236,   339,    31,   242,   340,    19,    31,   240,   327,   337,
     243,   327,   337,    19,    21,    31,   248,   301,   302,   303,
     326,   333,   336,   340,   342,    27,   244,   320,   321,   237,
     300,   341,    19,    23,    31,   239,   300,   325,   330,   334,
     335,   341,   357,    19,    20,    21,    31,    37,    38,    40,
     233,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   355,   234,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   355,   271,   277,   279,   241,   300,    19,    19,    38,
      38,    22,    38,    33,    23,    23,    37,    19,    39,   274,
      26,    27,   279,    39,    40,    26,    32,    27,    23,    33,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,    27,   279,   279,    27,
     279,    39,    27,   279,   279,   279,   279,    39,    26,    27,
     279,    32,   279,   279,   279,   279,    39,    21,    27,   279,
     279,   279,   279,   279,   279,   279,    39,    39,    26,    27,
      38,    33,    33,   271,   279,   279,    36,    38,    36,    40,
      38,    21,    21,    34,    20,    19,    22,   222,   223,   266,
     278,    22,    19,    19,    25,    22,    36,    38,    27,   304,
     315,   316,   317,   304,   304,   304,   304,   304,   304,   304,
     304,   304,   304,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,   258,   275,   291,   304,   304,   304,   304,
      22,   258,   258,    22,   258,   291,    22,    22,   271,   271,
     275,   275,    22,    19,    22,   258,   291,    37,    32,   249,
     265,   278,   294,   250,   264,   271,   262,   275,   258,   291,
      22,    26,    22,    19,    31,    37,    40,   245,   327,   331,
     332,   337,   341,   344,   345,   346,   347,   349,   350,   351,
     275,   275,   275,   275,    32,   356,   270,   271,   275,    22,
      24,    19,    22,    37,    36,    38,    27,   262,    23,    33,
      23,    38,    36,    37,    32,    27,   277,   277,    27,    27,
      32,    27,    27,    40,    19,    32,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
      30,   279,   279,   279,    27,   279,   279,    27,    27,    27,
     279,   279,    27,    32,    27,    38,    33,   279,   279,   279,
      27,    33,    27,    39,    27,    39,    33,    33,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,    19,   279,    27,    24,    32,    27,
      21,    23,    19,    21,    43,    27,    21,    32,    89,   222,
     223,    33,    30,    32,    32,    89,    23,    30,    24,   262,
      20,    34,   247,   352,   353,   262,   262,   264,   275,   271,
     271,   275,   275,   275,   275,   271,   258,    30,   258,   271,
     275,    89,   259,   275,   259,    89,    33,    89,   246,   271,
     246,    33,    32,    89,    36,    32,   263,   275,   265,   262,
      33,    89,    22,    22,    38,    30,    30,   262,   262,   262,
     262,   262,   262,   262,   262,   262,   262,   262,   262,   271,
     275,   271,   275,    31,   258,    33,    23,    32,    89,    23,
      19,    30,    23,    20,    36,    23,    27,    89,    19,    23,
      23,    27,    36,    89,    33,    43,    23,   279,   279,   279,
     279,   279,   279,   279,   279,    27,   279,   279,    27,    89,
      27,   279,     4,    89,    23,    27,    39,    89,   279,   279,
      89,    27,    27,    27,    23,    33,    39,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,     4,
     279,     4,   279,    23,   279,    89,    36,    23,    27,    30,
      31,    89,    89,    23,    27,    30,    32,    33,    20,    30,
      32,    40,    38,    36,   262,   271,   275,   275,   275,   271,
     259,   275,    32,   260,   275,   260,    32,    33,    32,   271,
       7,     8,   268,   269,   271,   272,   273,   274,   275,   278,
      33,    30,    32,    31,    31,   262,   263,    33,    32,    33,
      89,    31,   252,   275,   253,   275,   254,   271,   252,    22,
      32,   258,   292,   293,   255,   275,   256,   275,   291,   257,
     271,   252,     7,     8,   261,   272,   275,   270,   270,   268,
     271,   268,   271,   266,    33,    89,    30,    32,    30,    89,
      40,    21,    20,    37,    39,    30,    37,    34,    37,    33,
      23,    21,   279,   279,   279,   279,   279,    37,   279,    37,
      39,    34,     4,   273,   273,     5,     6,    39,    34,    37,
      23,    33,   279,    39,    34,    89,    27,    23,   279,    23,
      33,   279,     4,     4,    39,    24,    89,    34,    37,    19,
      21,    33,    33,    23,    38,    38,    23,    39,    38,    27,
      37,    23,   246,   271,   271,   246,   260,    38,   264,    38,
      38,    39,   268,     6,     6,   269,   273,    38,    39,    38,
      32,    22,   262,    38,    39,    33,    32,   253,    24,    32,
     255,   268,   268,    38,    27,    21,    27,    39,    38,    32,
      33,    27,    39,    36,    34,    89,    38,    36,    21,    32,
      36,   279,    36,    34,    38,   273,   273,    34,    38,    36,
      38,    19,    34,    38,    39,    34,    19,    23,   279,    34,
      30,    33,    32,    38,    36,    23,    39,    21,    32,    39,
      39,    19,    23,    31,    89,    39,    23,    38,    39,   265,
      39,    39,    89,    39,    89,    39,    30,    39,    89,    38,
      39,    39,   256,    39,    30,    39,    24,    89,    39,    33,
      32,    23,    38,    31,    38,    39,    32,    27,    22,    34,
      31,    89,    19,    31,   279,    31,    38,    22,    38,    22,
      31,    38,    22,    34,    34,    38,    30,    38,    32,    33,
      22,    31,    39,    38,    89,    23,    89,    22,    25,    22,
      23,    36,    33,    23,    21,    25,    23,   263,    23,    89,
      23,    89,    23,    23,    89,    23,    33,    39,    89,    38,
      89,    38,    23,    23,    37,    21,    32,    21,    22,    27,
      27,    27,    40,    27,    36,    32,    33,    23,    32,   279,
      32,    22,    40,    22,    40,    32,    21,    22,    40,    36,
      38,    21,    34,    38,    22,    40,    32,    33,    38,    26,
      23,    36,    33,    32,    89,    27,    40,    38,    38,    39,
      38,   261,    38,    23,    27,    23,    27,    38,    26,    23,
      27,    38,    89,    26,    33,    43,    23,    27,    38,    39,
      89,    19,    40,    27,    89,    23,    27,    21,    23,    89,
      37,    89,    32,   279,    40,    21,    40,    21,    89,    19,
      40,    21,    21,    38,    19,    36,    34,    40,    21,    89,
      32,    31,    32,    27,    40,    33,    37,    32,    23,    36,
      34,    31,    38,    33,    34,   251,   267,   278,   322,   323,
     324,    27,    23,    27,    23,    31,    32,    27,    23,    26,
      43,    32,    38,    23,    27,    23,    21,    27,    31,    38,
      19,    32,    21,    23,    39,    34,    37,    89,    19,    19,
      89,    32,    23,   279,    21,    21,    19,    32,    21,    89,
      19,    34,    32,    21,    89,    33,    32,    19,    34,    23,
      23,    36,    38,    39,    34,    36,    34,    31,    89,    36,
     267,    23,    23,    34,    23,    23,    34,    32,    23,    23,
      23,    21,    27,    39,    24,    34,    30,    37,    89,    34,
      38,    19,    19,    37,    19,    22,    37,    30,    89,    19,
      32,    30,    89,    33,    32,    32,    33,    89,    89,    34,
      39,    89,    36,    31,    42,    23,    27,    34,    36,    23,
      21,    27,    39,    24,    38,    21,    27,    34,    19,    38,
      22,    19,    23,    31,    37,    19,    19,    30,    33,    32,
      32,    33,    33,    32,    19,    36,    89,    36,    31,    38,
      19,    38,    36,    31,    39,    24,    38,    39,    24,    36,
      19,    22,    27,    23,    23,    32,    23,    19,    23,    32,
      33,    32,    33,    19,    31,    36,    40,    38,    36,    22,
      32,    31,    38,    38,    38,    31,    23,    27,    23,    23,
      89,    38,    23,    23,    23,    38,    40,    36,    36,    26,
      38,    36,    38,    23,    23,    37,    33,    23,    23,    36,
      36,    30,    36,    36,    37,    22
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
#line 218 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputDeviceParameter((yyvsp[(3) - (7)].Number), (yyvsp[(5) - (7)].String), (yyvsp[(7) - (7)].String));      }
    break;

  case 103:
#line 219 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputChannelParameter((yyvsp[(3) - (9)].Number), (yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].String), (yyvsp[(9) - (9)].String)); }
    break;

  case 104:
#line 220 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMidiInputDeviceParameter((yyvsp[(3) - (7)].Number), (yyvsp[(5) - (7)].String), (yyvsp[(7) - (7)].String));        }
    break;

  case 105:
#line 221 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMidiInputPortParameter((yyvsp[(3) - (9)].Number), (yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].String), (yyvsp[(9) - (9)].String));      }
    break;

  case 106:
#line 222 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String);                                                         }
    break;

  case 107:
#line 223 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMidiInstrumentMapName((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].String));               }
    break;

  case 108:
#line 224 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetEcho((yyparse_param_t*) yyparse_param, (yyvsp[(3) - (3)].Dotnum));  }
    break;

  case 109:
#line 227 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateAudioOutputDevice((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].KeyValList)); }
    break;

  case 110:
#line 228 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateAudioOutputDevice((yyvsp[(3) - (3)].String));    }
    break;

  case 111:
#line 229 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateMidiInputDevice((yyvsp[(3) - (5)].String),(yyvsp[(5) - (5)].KeyValList));   }
    break;

  case 112:
#line 230 "lscp.y"
    { (yyval.String) = LSCPSERVER->CreateMidiInputDevice((yyvsp[(3) - (3)].String));      }
    break;

  case 113:
#line 233 "lscp.y"
    { (yyval.String) = LSCPSERVER->ResetChannel((yyvsp[(3) - (3)].Number)); }
    break;

  case 114:
#line 236 "lscp.y"
    { (yyval.String) = LSCPSERVER->ClearMidiInstrumentMappings((yyvsp[(3) - (3)].Number));  }
    break;

  case 115:
#line 237 "lscp.y"
    { (yyval.String) = LSCPSERVER->ClearAllMidiInstrumentMappings(); }
    break;

  case 116:
#line 240 "lscp.y"
    { (yyval.String) = LSCPSERVER->DestroyAudioOutputDevice((yyvsp[(3) - (3)].Number)); }
    break;

  case 117:
#line 241 "lscp.y"
    { (yyval.String) = LSCPSERVER->DestroyMidiInputDevice((yyvsp[(3) - (3)].Number));   }
    break;

  case 118:
#line 244 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String); }
    break;

  case 119:
#line 245 "lscp.y"
    { (yyval.String) = (yyvsp[(3) - (3)].String); }
    break;

  case 120:
#line 248 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputDevice((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));      }
    break;

  case 121:
#line 249 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputChannel((yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number), (yyvsp[(3) - (7)].Number)); }
    break;

  case 122:
#line 250 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetAudioOutputType((yyvsp[(5) - (5)].String), (yyvsp[(3) - (5)].Number));        }
    break;

  case 123:
#line 251 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInput((yyvsp[(5) - (9)].Number), (yyvsp[(7) - (9)].Number), (yyvsp[(9) - (9)].Number), (yyvsp[(3) - (9)].Number));      }
    break;

  case 124:
#line 252 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputDevice((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));        }
    break;

  case 125:
#line 253 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputPort((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));          }
    break;

  case 126:
#line 254 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputChannel((yyvsp[(5) - (5)].Number), (yyvsp[(3) - (5)].Number));       }
    break;

  case 127:
#line 255 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetMIDIInputType((yyvsp[(5) - (5)].String), (yyvsp[(3) - (5)].Number));          }
    break;

  case 128:
#line 256 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetVolume((yyvsp[(5) - (5)].Dotnum), (yyvsp[(3) - (5)].Number));                 }
    break;

  case 129:
#line 257 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMute((yyvsp[(5) - (5)].Dotnum), (yyvsp[(3) - (5)].Number));            }
    break;

  case 130:
#line 258 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelSolo((yyvsp[(5) - (5)].Dotnum), (yyvsp[(3) - (5)].Number));            }
    break;

  case 131:
#line 259 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMap((yyvsp[(3) - (5)].Number), (yyvsp[(5) - (5)].Number));             }
    break;

  case 132:
#line 260 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMap((yyvsp[(3) - (5)].Number), -1);             }
    break;

  case 133:
#line 261 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetChannelMap((yyvsp[(3) - (5)].Number), -2);             }
    break;

  case 134:
#line 264 "lscp.y"
    { (yyval.KeyValList)[(yyvsp[(1) - (3)].String)] = (yyvsp[(3) - (3)].String);          }
    break;

  case 135:
#line 265 "lscp.y"
    { (yyval.KeyValList) = (yyvsp[(1) - (5)].KeyValList); (yyval.KeyValList)[(yyvsp[(3) - (5)].String)] = (yyvsp[(5) - (5)].String); }
    break;

  case 136:
#line 268 "lscp.y"
    { (yyval.FillResponse) = fill_response_bytes;      }
    break;

  case 137:
#line 269 "lscp.y"
    { (yyval.FillResponse) = fill_response_percentage; }
    break;

  case 138:
#line 272 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetAudioOutputDevices();           }
    break;

  case 139:
#line 273 "lscp.y"
    { (yyval.String) = LSCPSERVER->GetMidiInputDevices();             }
    break;

  case 140:
#line 274 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListChannels();                    }
    break;

  case 141:
#line 275 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableEngines();            }
    break;

  case 142:
#line 276 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableMidiInputDrivers();   }
    break;

  case 143:
#line 277 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAvailableAudioOutputDrivers(); }
    break;

  case 144:
#line 278 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListMidiInstrumentMappings((yyvsp[(3) - (3)].Number));    }
    break;

  case 145:
#line 279 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListAllMidiInstrumentMappings();   }
    break;

  case 146:
#line 280 "lscp.y"
    { (yyval.String) = LSCPSERVER->ListMidiInstrumentMaps();          }
    break;

  case 147:
#line 283 "lscp.y"
    { (yyval.String) = LSCPSERVER->LoadInstrument((yyvsp[(1) - (5)].String), (yyvsp[(3) - (5)].Number), (yyvsp[(5) - (5)].Number));       }
    break;

  case 148:
#line 284 "lscp.y"
    { (yyval.String) = LSCPSERVER->LoadInstrument((yyvsp[(3) - (7)].String), (yyvsp[(5) - (7)].Number), (yyvsp[(7) - (7)].Number), true); }
    break;

  case 149:
#line 287 "lscp.y"
    { (yyval.String) = LSCPSERVER->SetEngineType((yyvsp[(1) - (3)].String), (yyvsp[(3) - (3)].Number)); }
    break;

  case 150:
#line 290 "lscp.y"
    { (yyval.LoadMode) = MidiInstrumentMapper::ON_DEMAND;      }
    break;

  case 151:
#line 291 "lscp.y"
    { (yyval.LoadMode) = MidiInstrumentMapper::ON_DEMAND_HOLD; }
    break;

  case 152:
#line 292 "lscp.y"
    { (yyval.LoadMode) = MidiInstrumentMapper::PERSISTENT;     }
    break;

  case 158:
#line 308 "lscp.y"
    { (yyval.Number) = 16; }
    break;

  case 164:
#line 324 "lscp.y"
    { (yyval.Dotnum) = (yyvsp[(1) - (1)].Number); }
    break;

  case 172:
#line 346 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (3)].String) + "," + (yyvsp[(3) - (3)].String); }
    break;

  case 175:
#line 351 "lscp.y"
    { std::stringstream ss; ss << "\'" << (yyvsp[(1) - (1)].Number) << "\'"; (yyval.String) = ss.str(); }
    break;

  case 176:
#line 352 "lscp.y"
    { std::stringstream ss; ss << "\'" << (yyvsp[(1) - (1)].Dotnum) << "\'"; (yyval.String) = ss.str(); }
    break;

  case 177:
#line 360 "lscp.y"
    { (yyval.Dotnum) = (yyvsp[(1) - (1)].Number); }
    break;

  case 178:
#line 361 "lscp.y"
    { (yyval.Dotnum) = -1; }
    break;

  case 179:
#line 364 "lscp.y"
    { std::string s; s = (yyvsp[(1) - (1)].Char); (yyval.String) = s; }
    break;

  case 180:
#line 365 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + (yyvsp[(2) - (2)].Char);                  }
    break;

  case 181:
#line 368 "lscp.y"
    { (yyval.Dotnum) = atof(String((yyvsp[(1) - (3)].String) + "." + (yyvsp[(3) - (3)].String)).c_str());                         }
    break;

  case 182:
#line 369 "lscp.y"
    { String s = "+"; s += (yyvsp[(2) - (4)].String); s += "."; s += (yyvsp[(4) - (4)].String); (yyval.Dotnum) = atof(s.c_str()); }
    break;

  case 183:
#line 370 "lscp.y"
    { (yyval.Dotnum) = atof(String("-" + (yyvsp[(2) - (4)].String) + "." + (yyvsp[(4) - (4)].String)).c_str());                   }
    break;

  case 184:
#line 374 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (1)].Char);      }
    break;

  case 185:
#line 375 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + (yyvsp[(2) - (2)].Char); }
    break;

  case 186:
#line 378 "lscp.y"
    { (yyval.Char) = '0'; }
    break;

  case 187:
#line 379 "lscp.y"
    { (yyval.Char) = '1'; }
    break;

  case 188:
#line 380 "lscp.y"
    { (yyval.Char) = '2'; }
    break;

  case 189:
#line 381 "lscp.y"
    { (yyval.Char) = '3'; }
    break;

  case 190:
#line 382 "lscp.y"
    { (yyval.Char) = '4'; }
    break;

  case 191:
#line 383 "lscp.y"
    { (yyval.Char) = '5'; }
    break;

  case 192:
#line 384 "lscp.y"
    { (yyval.Char) = '6'; }
    break;

  case 193:
#line 385 "lscp.y"
    { (yyval.Char) = '7'; }
    break;

  case 194:
#line 386 "lscp.y"
    { (yyval.Char) = '8'; }
    break;

  case 195:
#line 387 "lscp.y"
    { (yyval.Char) = '9'; }
    break;

  case 196:
#line 390 "lscp.y"
    { (yyval.Number) = atoi(String(1, (yyvsp[(1) - (1)].Char)).c_str());      }
    break;

  case 197:
#line 391 "lscp.y"
    { (yyval.Number) = atoi(String(String("1") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 198:
#line 392 "lscp.y"
    { (yyval.Number) = atoi(String(String("2") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 199:
#line 393 "lscp.y"
    { (yyval.Number) = atoi(String(String("3") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 200:
#line 394 "lscp.y"
    { (yyval.Number) = atoi(String(String("4") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 201:
#line 395 "lscp.y"
    { (yyval.Number) = atoi(String(String("5") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 202:
#line 396 "lscp.y"
    { (yyval.Number) = atoi(String(String("6") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 203:
#line 397 "lscp.y"
    { (yyval.Number) = atoi(String(String("7") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 204:
#line 398 "lscp.y"
    { (yyval.Number) = atoi(String(String("8") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 205:
#line 399 "lscp.y"
    { (yyval.Number) = atoi(String(String("9") + (yyvsp[(2) - (2)].String)).c_str()); }
    break;

  case 206:
#line 401 "lscp.y"
    { (yyval.Char) = 'A'; }
    break;

  case 207:
#line 401 "lscp.y"
    { (yyval.Char) = 'B'; }
    break;

  case 208:
#line 401 "lscp.y"
    { (yyval.Char) = 'C'; }
    break;

  case 209:
#line 401 "lscp.y"
    { (yyval.Char) = 'D'; }
    break;

  case 210:
#line 401 "lscp.y"
    { (yyval.Char) = 'E'; }
    break;

  case 211:
#line 401 "lscp.y"
    { (yyval.Char) = 'F'; }
    break;

  case 212:
#line 401 "lscp.y"
    { (yyval.Char) = 'G'; }
    break;

  case 213:
#line 401 "lscp.y"
    { (yyval.Char) = 'H'; }
    break;

  case 214:
#line 401 "lscp.y"
    { (yyval.Char) = 'I'; }
    break;

  case 215:
#line 401 "lscp.y"
    { (yyval.Char) = 'J'; }
    break;

  case 216:
#line 401 "lscp.y"
    { (yyval.Char) = 'K'; }
    break;

  case 217:
#line 401 "lscp.y"
    { (yyval.Char) = 'L'; }
    break;

  case 218:
#line 401 "lscp.y"
    { (yyval.Char) = 'M'; }
    break;

  case 219:
#line 401 "lscp.y"
    { (yyval.Char) = 'N'; }
    break;

  case 220:
#line 401 "lscp.y"
    { (yyval.Char) = 'O'; }
    break;

  case 221:
#line 401 "lscp.y"
    { (yyval.Char) = 'P'; }
    break;

  case 222:
#line 401 "lscp.y"
    { (yyval.Char) = 'Q'; }
    break;

  case 223:
#line 401 "lscp.y"
    { (yyval.Char) = 'R'; }
    break;

  case 224:
#line 401 "lscp.y"
    { (yyval.Char) = 'S'; }
    break;

  case 225:
#line 401 "lscp.y"
    { (yyval.Char) = 'T'; }
    break;

  case 226:
#line 401 "lscp.y"
    { (yyval.Char) = 'U'; }
    break;

  case 227:
#line 401 "lscp.y"
    { (yyval.Char) = 'V'; }
    break;

  case 228:
#line 401 "lscp.y"
    { (yyval.Char) = 'W'; }
    break;

  case 229:
#line 401 "lscp.y"
    { (yyval.Char) = 'X'; }
    break;

  case 230:
#line 401 "lscp.y"
    { (yyval.Char) = 'Y'; }
    break;

  case 231:
#line 401 "lscp.y"
    { (yyval.Char) = 'Z'; }
    break;

  case 232:
#line 402 "lscp.y"
    { (yyval.Char) = 'a'; }
    break;

  case 233:
#line 402 "lscp.y"
    { (yyval.Char) = 'b'; }
    break;

  case 234:
#line 402 "lscp.y"
    { (yyval.Char) = 'c'; }
    break;

  case 235:
#line 402 "lscp.y"
    { (yyval.Char) = 'd'; }
    break;

  case 236:
#line 402 "lscp.y"
    { (yyval.Char) = 'e'; }
    break;

  case 237:
#line 402 "lscp.y"
    { (yyval.Char) = 'f'; }
    break;

  case 238:
#line 402 "lscp.y"
    { (yyval.Char) = 'g'; }
    break;

  case 239:
#line 402 "lscp.y"
    { (yyval.Char) = 'h'; }
    break;

  case 240:
#line 402 "lscp.y"
    { (yyval.Char) = 'i'; }
    break;

  case 241:
#line 402 "lscp.y"
    { (yyval.Char) = 'j'; }
    break;

  case 242:
#line 402 "lscp.y"
    { (yyval.Char) = 'k'; }
    break;

  case 243:
#line 402 "lscp.y"
    { (yyval.Char) = 'l'; }
    break;

  case 244:
#line 402 "lscp.y"
    { (yyval.Char) = 'm'; }
    break;

  case 245:
#line 402 "lscp.y"
    { (yyval.Char) = 'n'; }
    break;

  case 246:
#line 402 "lscp.y"
    { (yyval.Char) = 'o'; }
    break;

  case 247:
#line 402 "lscp.y"
    { (yyval.Char) = 'p'; }
    break;

  case 248:
#line 402 "lscp.y"
    { (yyval.Char) = 'q'; }
    break;

  case 249:
#line 402 "lscp.y"
    { (yyval.Char) = 'r'; }
    break;

  case 250:
#line 402 "lscp.y"
    { (yyval.Char) = 's'; }
    break;

  case 251:
#line 402 "lscp.y"
    { (yyval.Char) = 't'; }
    break;

  case 252:
#line 402 "lscp.y"
    { (yyval.Char) = 'u'; }
    break;

  case 253:
#line 402 "lscp.y"
    { (yyval.Char) = 'v'; }
    break;

  case 254:
#line 402 "lscp.y"
    { (yyval.Char) = 'w'; }
    break;

  case 255:
#line 402 "lscp.y"
    { (yyval.Char) = 'x'; }
    break;

  case 256:
#line 402 "lscp.y"
    { (yyval.Char) = 'y'; }
    break;

  case 257:
#line 402 "lscp.y"
    { (yyval.Char) = 'z'; }
    break;

  case 258:
#line 403 "lscp.y"
    { (yyval.Char) = '0'; }
    break;

  case 259:
#line 403 "lscp.y"
    { (yyval.Char) = '1'; }
    break;

  case 260:
#line 403 "lscp.y"
    { (yyval.Char) = '2'; }
    break;

  case 261:
#line 403 "lscp.y"
    { (yyval.Char) = '3'; }
    break;

  case 262:
#line 403 "lscp.y"
    { (yyval.Char) = '4'; }
    break;

  case 263:
#line 403 "lscp.y"
    { (yyval.Char) = '5'; }
    break;

  case 264:
#line 403 "lscp.y"
    { (yyval.Char) = '6'; }
    break;

  case 265:
#line 403 "lscp.y"
    { (yyval.Char) = '7'; }
    break;

  case 266:
#line 403 "lscp.y"
    { (yyval.Char) = '8'; }
    break;

  case 267:
#line 403 "lscp.y"
    { (yyval.Char) = '9'; }
    break;

  case 268:
#line 404 "lscp.y"
    { (yyval.Char) = '!'; }
    break;

  case 269:
#line 404 "lscp.y"
    { (yyval.Char) = '#'; }
    break;

  case 270:
#line 404 "lscp.y"
    { (yyval.Char) = '$'; }
    break;

  case 271:
#line 404 "lscp.y"
    { (yyval.Char) = '%'; }
    break;

  case 272:
#line 404 "lscp.y"
    { (yyval.Char) = '&'; }
    break;

  case 273:
#line 404 "lscp.y"
    { (yyval.Char) = '('; }
    break;

  case 274:
#line 404 "lscp.y"
    { (yyval.Char) = ')'; }
    break;

  case 275:
#line 404 "lscp.y"
    { (yyval.Char) = '*'; }
    break;

  case 276:
#line 404 "lscp.y"
    { (yyval.Char) = '+'; }
    break;

  case 277:
#line 404 "lscp.y"
    { (yyval.Char) = '-'; }
    break;

  case 278:
#line 404 "lscp.y"
    { (yyval.Char) = '.'; }
    break;

  case 279:
#line 404 "lscp.y"
    { (yyval.Char) = ','; }
    break;

  case 280:
#line 404 "lscp.y"
    { (yyval.Char) = '/'; }
    break;

  case 281:
#line 405 "lscp.y"
    { (yyval.Char) = ':'; }
    break;

  case 282:
#line 405 "lscp.y"
    { (yyval.Char) = ';'; }
    break;

  case 283:
#line 405 "lscp.y"
    { (yyval.Char) = '<'; }
    break;

  case 284:
#line 405 "lscp.y"
    { (yyval.Char) = '='; }
    break;

  case 285:
#line 405 "lscp.y"
    { (yyval.Char) = '>'; }
    break;

  case 286:
#line 405 "lscp.y"
    { (yyval.Char) = '?'; }
    break;

  case 287:
#line 405 "lscp.y"
    { (yyval.Char) = '@'; }
    break;

  case 288:
#line 406 "lscp.y"
    { (yyval.Char) = '['; }
    break;

  case 289:
#line 406 "lscp.y"
    { (yyval.Char) = '\\'; }
    break;

  case 290:
#line 406 "lscp.y"
    { (yyval.Char) = ']'; }
    break;

  case 291:
#line 406 "lscp.y"
    { (yyval.Char) = '^'; }
    break;

  case 292:
#line 406 "lscp.y"
    { (yyval.Char) = '_'; }
    break;

  case 293:
#line 407 "lscp.y"
    { (yyval.Char) = '{'; }
    break;

  case 294:
#line 407 "lscp.y"
    { (yyval.Char) = '|'; }
    break;

  case 295:
#line 407 "lscp.y"
    { (yyval.Char) = '}'; }
    break;

  case 296:
#line 407 "lscp.y"
    { (yyval.Char) = '~'; }
    break;

  case 297:
#line 408 "lscp.y"
    { (yyval.Char) = '\200'; }
    break;

  case 298:
#line 408 "lscp.y"
    { (yyval.Char) = '\201'; }
    break;

  case 299:
#line 408 "lscp.y"
    { (yyval.Char) = '\202'; }
    break;

  case 300:
#line 409 "lscp.y"
    { (yyval.Char) = '\203'; }
    break;

  case 301:
#line 409 "lscp.y"
    { (yyval.Char) = '\204'; }
    break;

  case 302:
#line 409 "lscp.y"
    { (yyval.Char) = '\205'; }
    break;

  case 303:
#line 410 "lscp.y"
    { (yyval.Char) = '\206'; }
    break;

  case 304:
#line 410 "lscp.y"
    { (yyval.Char) = '\207'; }
    break;

  case 305:
#line 410 "lscp.y"
    { (yyval.Char) = '\210'; }
    break;

  case 306:
#line 411 "lscp.y"
    { (yyval.Char) = '\211'; }
    break;

  case 307:
#line 411 "lscp.y"
    { (yyval.Char) = '\212'; }
    break;

  case 308:
#line 411 "lscp.y"
    { (yyval.Char) = '\213'; }
    break;

  case 309:
#line 412 "lscp.y"
    { (yyval.Char) = '\214'; }
    break;

  case 310:
#line 412 "lscp.y"
    { (yyval.Char) = '\215'; }
    break;

  case 311:
#line 412 "lscp.y"
    { (yyval.Char) = '\216'; }
    break;

  case 312:
#line 413 "lscp.y"
    { (yyval.Char) = '\217'; }
    break;

  case 313:
#line 413 "lscp.y"
    { (yyval.Char) = '\220'; }
    break;

  case 314:
#line 413 "lscp.y"
    { (yyval.Char) = '\221'; }
    break;

  case 315:
#line 414 "lscp.y"
    { (yyval.Char) = '\222'; }
    break;

  case 316:
#line 414 "lscp.y"
    { (yyval.Char) = '\223'; }
    break;

  case 317:
#line 414 "lscp.y"
    { (yyval.Char) = '\224'; }
    break;

  case 318:
#line 415 "lscp.y"
    { (yyval.Char) = '\225'; }
    break;

  case 319:
#line 415 "lscp.y"
    { (yyval.Char) = '\226'; }
    break;

  case 320:
#line 415 "lscp.y"
    { (yyval.Char) = '\227'; }
    break;

  case 321:
#line 416 "lscp.y"
    { (yyval.Char) = '\230'; }
    break;

  case 322:
#line 416 "lscp.y"
    { (yyval.Char) = '\231'; }
    break;

  case 323:
#line 416 "lscp.y"
    { (yyval.Char) = '\232'; }
    break;

  case 324:
#line 417 "lscp.y"
    { (yyval.Char) = '\233'; }
    break;

  case 325:
#line 417 "lscp.y"
    { (yyval.Char) = '\234'; }
    break;

  case 326:
#line 417 "lscp.y"
    { (yyval.Char) = '\235'; }
    break;

  case 327:
#line 418 "lscp.y"
    { (yyval.Char) = '\236'; }
    break;

  case 328:
#line 418 "lscp.y"
    { (yyval.Char) = '\237'; }
    break;

  case 329:
#line 418 "lscp.y"
    { (yyval.Char) = '\240'; }
    break;

  case 330:
#line 419 "lscp.y"
    { (yyval.Char) = '\241'; }
    break;

  case 331:
#line 419 "lscp.y"
    { (yyval.Char) = '\242'; }
    break;

  case 332:
#line 419 "lscp.y"
    { (yyval.Char) = '\243'; }
    break;

  case 333:
#line 420 "lscp.y"
    { (yyval.Char) = '\244'; }
    break;

  case 334:
#line 420 "lscp.y"
    { (yyval.Char) = '\245'; }
    break;

  case 335:
#line 420 "lscp.y"
    { (yyval.Char) = '\246'; }
    break;

  case 336:
#line 421 "lscp.y"
    { (yyval.Char) = '\247'; }
    break;

  case 337:
#line 421 "lscp.y"
    { (yyval.Char) = '\250'; }
    break;

  case 338:
#line 421 "lscp.y"
    { (yyval.Char) = '\251'; }
    break;

  case 339:
#line 422 "lscp.y"
    { (yyval.Char) = '\252'; }
    break;

  case 340:
#line 422 "lscp.y"
    { (yyval.Char) = '\253'; }
    break;

  case 341:
#line 422 "lscp.y"
    { (yyval.Char) = '\254'; }
    break;

  case 342:
#line 423 "lscp.y"
    { (yyval.Char) = '\255'; }
    break;

  case 343:
#line 423 "lscp.y"
    { (yyval.Char) = '\256'; }
    break;

  case 344:
#line 423 "lscp.y"
    { (yyval.Char) = '\257'; }
    break;

  case 345:
#line 424 "lscp.y"
    { (yyval.Char) = '\260'; }
    break;

  case 346:
#line 424 "lscp.y"
    { (yyval.Char) = '\261'; }
    break;

  case 347:
#line 424 "lscp.y"
    { (yyval.Char) = '\262'; }
    break;

  case 348:
#line 425 "lscp.y"
    { (yyval.Char) = '\263'; }
    break;

  case 349:
#line 425 "lscp.y"
    { (yyval.Char) = '\264'; }
    break;

  case 350:
#line 425 "lscp.y"
    { (yyval.Char) = '\265'; }
    break;

  case 351:
#line 426 "lscp.y"
    { (yyval.Char) = '\266'; }
    break;

  case 352:
#line 426 "lscp.y"
    { (yyval.Char) = '\267'; }
    break;

  case 353:
#line 426 "lscp.y"
    { (yyval.Char) = '\270'; }
    break;

  case 354:
#line 427 "lscp.y"
    { (yyval.Char) = '\271'; }
    break;

  case 355:
#line 427 "lscp.y"
    { (yyval.Char) = '\272'; }
    break;

  case 356:
#line 427 "lscp.y"
    { (yyval.Char) = '\273'; }
    break;

  case 357:
#line 428 "lscp.y"
    { (yyval.Char) = '\274'; }
    break;

  case 358:
#line 428 "lscp.y"
    { (yyval.Char) = '\275'; }
    break;

  case 359:
#line 428 "lscp.y"
    { (yyval.Char) = '\276'; }
    break;

  case 360:
#line 429 "lscp.y"
    { (yyval.Char) = '\277'; }
    break;

  case 361:
#line 429 "lscp.y"
    { (yyval.Char) = '\300'; }
    break;

  case 362:
#line 429 "lscp.y"
    { (yyval.Char) = '\301'; }
    break;

  case 363:
#line 430 "lscp.y"
    { (yyval.Char) = '\302'; }
    break;

  case 364:
#line 430 "lscp.y"
    { (yyval.Char) = '\303'; }
    break;

  case 365:
#line 430 "lscp.y"
    { (yyval.Char) = '\304'; }
    break;

  case 366:
#line 431 "lscp.y"
    { (yyval.Char) = '\305'; }
    break;

  case 367:
#line 431 "lscp.y"
    { (yyval.Char) = '\306'; }
    break;

  case 368:
#line 431 "lscp.y"
    { (yyval.Char) = '\307'; }
    break;

  case 369:
#line 432 "lscp.y"
    { (yyval.Char) = '\310'; }
    break;

  case 370:
#line 432 "lscp.y"
    { (yyval.Char) = '\311'; }
    break;

  case 371:
#line 432 "lscp.y"
    { (yyval.Char) = '\312'; }
    break;

  case 372:
#line 433 "lscp.y"
    { (yyval.Char) = '\313'; }
    break;

  case 373:
#line 433 "lscp.y"
    { (yyval.Char) = '\314'; }
    break;

  case 374:
#line 433 "lscp.y"
    { (yyval.Char) = '\315'; }
    break;

  case 375:
#line 434 "lscp.y"
    { (yyval.Char) = '\316'; }
    break;

  case 376:
#line 434 "lscp.y"
    { (yyval.Char) = '\317'; }
    break;

  case 377:
#line 434 "lscp.y"
    { (yyval.Char) = '\320'; }
    break;

  case 378:
#line 435 "lscp.y"
    { (yyval.Char) = '\321'; }
    break;

  case 379:
#line 435 "lscp.y"
    { (yyval.Char) = '\322'; }
    break;

  case 380:
#line 435 "lscp.y"
    { (yyval.Char) = '\323'; }
    break;

  case 381:
#line 436 "lscp.y"
    { (yyval.Char) = '\324'; }
    break;

  case 382:
#line 436 "lscp.y"
    { (yyval.Char) = '\325'; }
    break;

  case 383:
#line 436 "lscp.y"
    { (yyval.Char) = '\326'; }
    break;

  case 384:
#line 437 "lscp.y"
    { (yyval.Char) = '\327'; }
    break;

  case 385:
#line 437 "lscp.y"
    { (yyval.Char) = '\330'; }
    break;

  case 386:
#line 437 "lscp.y"
    { (yyval.Char) = '\331'; }
    break;

  case 387:
#line 438 "lscp.y"
    { (yyval.Char) = '\332'; }
    break;

  case 388:
#line 438 "lscp.y"
    { (yyval.Char) = '\333'; }
    break;

  case 389:
#line 438 "lscp.y"
    { (yyval.Char) = '\334'; }
    break;

  case 390:
#line 439 "lscp.y"
    { (yyval.Char) = '\335'; }
    break;

  case 391:
#line 439 "lscp.y"
    { (yyval.Char) = '\336'; }
    break;

  case 392:
#line 439 "lscp.y"
    { (yyval.Char) = '\337'; }
    break;

  case 393:
#line 440 "lscp.y"
    { (yyval.Char) = '\340'; }
    break;

  case 394:
#line 440 "lscp.y"
    { (yyval.Char) = '\341'; }
    break;

  case 395:
#line 440 "lscp.y"
    { (yyval.Char) = '\342'; }
    break;

  case 396:
#line 441 "lscp.y"
    { (yyval.Char) = '\343'; }
    break;

  case 397:
#line 441 "lscp.y"
    { (yyval.Char) = '\344'; }
    break;

  case 398:
#line 441 "lscp.y"
    { (yyval.Char) = '\345'; }
    break;

  case 399:
#line 442 "lscp.y"
    { (yyval.Char) = '\346'; }
    break;

  case 400:
#line 442 "lscp.y"
    { (yyval.Char) = '\347'; }
    break;

  case 401:
#line 442 "lscp.y"
    { (yyval.Char) = '\350'; }
    break;

  case 402:
#line 443 "lscp.y"
    { (yyval.Char) = '\351'; }
    break;

  case 403:
#line 443 "lscp.y"
    { (yyval.Char) = '\352'; }
    break;

  case 404:
#line 443 "lscp.y"
    { (yyval.Char) = '\353'; }
    break;

  case 405:
#line 444 "lscp.y"
    { (yyval.Char) = '\354'; }
    break;

  case 406:
#line 444 "lscp.y"
    { (yyval.Char) = '\355'; }
    break;

  case 407:
#line 444 "lscp.y"
    { (yyval.Char) = '\356'; }
    break;

  case 408:
#line 445 "lscp.y"
    { (yyval.Char) = '\357'; }
    break;

  case 409:
#line 445 "lscp.y"
    { (yyval.Char) = '\360'; }
    break;

  case 410:
#line 445 "lscp.y"
    { (yyval.Char) = '\361'; }
    break;

  case 411:
#line 446 "lscp.y"
    { (yyval.Char) = '\362'; }
    break;

  case 412:
#line 446 "lscp.y"
    { (yyval.Char) = '\363'; }
    break;

  case 413:
#line 446 "lscp.y"
    { (yyval.Char) = '\364'; }
    break;

  case 414:
#line 447 "lscp.y"
    { (yyval.Char) = '\365'; }
    break;

  case 415:
#line 447 "lscp.y"
    { (yyval.Char) = '\366'; }
    break;

  case 416:
#line 447 "lscp.y"
    { (yyval.Char) = '\367'; }
    break;

  case 417:
#line 448 "lscp.y"
    { (yyval.Char) = '\370'; }
    break;

  case 418:
#line 448 "lscp.y"
    { (yyval.Char) = '\371'; }
    break;

  case 419:
#line 448 "lscp.y"
    { (yyval.Char) = '\372'; }
    break;

  case 420:
#line 449 "lscp.y"
    { (yyval.Char) = '\373'; }
    break;

  case 421:
#line 449 "lscp.y"
    { (yyval.Char) = '\374'; }
    break;

  case 422:
#line 449 "lscp.y"
    { (yyval.Char) = '\375'; }
    break;

  case 423:
#line 450 "lscp.y"
    { (yyval.Char) = '\376'; }
    break;

  case 424:
#line 450 "lscp.y"
    { (yyval.Char) = '\377'; }
    break;

  case 425:
#line 453 "lscp.y"
    { (yyval.String) = " ";      }
    break;

  case 427:
#line 455 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + " "; }
    break;

  case 428:
#line 456 "lscp.y"
    { (yyval.String) = (yyvsp[(1) - (2)].String) + (yyvsp[(2) - (2)].String);  }
    break;

  case 429:
#line 459 "lscp.y"
    { (yyval.String) = (yyvsp[(2) - (3)].String); }
    break;

  case 430:
#line 460 "lscp.y"
    { (yyval.String) = (yyvsp[(2) - (3)].String); }
    break;


/* Line 1267 of yacc.c.  */
#line 5210 "y.tab.c"
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


#line 706 "lscp.y"


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

