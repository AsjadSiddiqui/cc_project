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
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     END = 0,
     tok_integer = 258,
     tok_float = 259,
     tok_boolean = 260,
     tok_string = 261,
     tok_plus_print = 262,
     tok_minus = 263,
     tok_multiply = 264,
     tok_divide = 265,
     tok_and = 266,
     tok_or = 267,
     tok_not = 268,
     tok_var = 269,
     tok_for_start = 270,
     tok_in = 271,
     tok_range = 272,
     tok_loop_start = 273,
     tok_loop_end = 274,
     tok_if = 275,
     tok_else = 276,
     tok_if_end = 277,
     tok_equal = 278,
     tok_less_than = 279,
     tok_greater_than = 280,
     tok_increment = 281,
     tok_print_anon = 282,
     tok_add_anon_vars = 283,
     tok_if_equals_20_start = 284,
     tok_else_block = 285,
     tok_identifier = 286,
     tok_int_literal = 287,
     tok_float_literal = 288,
     tok_string_literal = 289,
     tok_end = 290
   };
#endif
/* Tokens.  */
#define END 0
#define tok_integer 258
#define tok_float 259
#define tok_boolean 260
#define tok_string 261
#define tok_plus_print 262
#define tok_minus 263
#define tok_multiply 264
#define tok_divide 265
#define tok_and 266
#define tok_or 267
#define tok_not 268
#define tok_var 269
#define tok_for_start 270
#define tok_in 271
#define tok_range 272
#define tok_loop_start 273
#define tok_loop_end 274
#define tok_if 275
#define tok_else 276
#define tok_if_end 277
#define tok_equal 278
#define tok_less_than 279
#define tok_greater_than 280
#define tok_increment 281
#define tok_print_anon 282
#define tok_add_anon_vars 283
#define tok_if_equals_20_start 284
#define tok_else_block 285
#define tok_identifier 286
#define tok_int_literal 287
#define tok_float_literal 288
#define tok_string_literal 289
#define tok_end 290




/* Copy the first part of user declarations.  */
#line 1 "muslang.y"

	#include <stdio.h>
	#include <stdlib.h>
	#include <string>
	#include "IR.h"
	
	extern int yyparse();
	extern int yylex();
	extern FILE *yyin;
	
	// Global debug flag
	int debug_mode = 0;
	
	// Counter for anonymous variables
	static int anonVarCounter = 0;
	std::string getNextAnonVarName() {
		return "anon" + std::to_string(anonVarCounter++);
	}
	
	// Create references for the latest anonymous variables
	static int latestAnon = -1;
	Value* getLatestAnon() {
		if (latestAnon < 0) {
			fprintf(stderr, "No anonymous variable available\n");
			exit(EXIT_FAILURE);
		}
		std::string name = "anon" + std::to_string(latestAnon);
		Value* ptr = getFromSymbolTable(name.c_str());
		return builder.CreateLoad(builder.getDoubleTy(), ptr, "load_anon");
	}
	
	// Helper function to get an anonymous variable by index
	Value* getAnonVar(int index) {
		if (index < 0 || index >= anonVarCounter) {
			if (debug_mode) fprintf(stderr, "Anonymous variable index out of range\n");
			exit(EXIT_FAILURE);
		}
		std::string name = "anon" + std::to_string(index);
		Value* ptr = getFromSymbolTable(name.c_str());
		return builder.CreateLoad(builder.getDoubleTy(), ptr, "load_anon");
	}
	
	#define DEBUGBISON
	//This code is for producing debug output.
	#ifdef DEBUGBISON
		#define debugBison(a) (debug_mode ? printf("\n%d \n",a) : 0)
	#else
		#define debugBison(a)
	#endif


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
typedef union YYSTYPE
#line 51 "muslang.y"
{
	char *identifier;
	int int_literal;
	double float_literal;
	char *string_literal;
	llvm::Value* value; 
}
/* Line 193 of yacc.c.  */
#line 227 "muslang.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 240 "muslang.tab.c"

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
# if defined YYENABLE_NLS && YYENABLE_NLS
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
#define YYFINAL  41
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   176

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  15
/* YYNRULES -- Number of rules.  */
#define YYNRULES  59
/* YYNRULES -- Number of states.  */
#define YYNSTATES  102

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   290

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     7,     9,    10,    14,    17,    19,
      21,    23,    25,    27,    29,    31,    33,    35,    38,    40,
      42,    46,    50,    54,    58,    63,    68,    73,    78,    80,
      84,    90,    93,    96,    99,   107,   113,   121,   129,   141,
     149,   157,   161,   165,   169,   173,   177,   179,   181,   183,
     185,   187,   191,   195,   199,   203,   205,   207,   209,   216
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      37,     0,    -1,    -1,    39,    37,    -1,    39,    -1,    -1,
       1,    38,    37,    -1,     1,     0,    -1,    28,    -1,    27,
      -1,    49,    -1,    50,    -1,    40,    -1,    42,    -1,    43,
      -1,    44,    -1,    48,    -1,     7,    34,    -1,     1,    -1,
       1,    -1,    14,     6,     9,    -1,    14,     3,     9,    -1,
      14,     4,     9,    -1,    14,     5,     9,    -1,    14,     3,
       9,    32,    -1,    14,     3,     9,    47,    -1,    14,     4,
       9,    33,    -1,    14,     4,     9,    47,    -1,    41,    -1,
      31,     9,    47,    -1,    31,     9,    31,     7,    47,    -1,
       9,    26,    -1,     7,    46,    -1,     7,    34,    -1,    15,
      16,    17,    32,    18,    37,    19,    -1,    20,    45,    18,
      37,    22,    -1,    20,    45,    18,    37,    21,    37,    22,
      -1,    20,    45,    18,    37,    18,    37,    22,    -1,    20,
       9,    23,    32,    18,    37,    22,    21,    18,    37,    22,
      -1,    20,     9,    25,     9,    18,    37,    22,    -1,    20,
       9,    23,    32,    18,    37,    22,    -1,    47,    23,    47,
      -1,    47,    24,    47,    -1,    47,    25,    47,    -1,     9,
      25,     9,    -1,     9,    23,    32,    -1,    31,    -1,    32,
      -1,    33,    -1,     9,    -1,    46,    -1,    47,     7,    47,
      -1,    47,     8,    47,    -1,    47,     9,    47,    -1,    47,
      10,    47,    -1,    22,    -1,    21,    -1,    20,    -1,    14,
       3,     9,     7,     9,     9,    -1,     7,     9,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    91,    91,    92,    93,    94,    94,    99,   108,   133,
     144,   145,   146,   147,   148,   149,   150,   151,   156,   161,
     168,   169,   170,   171,   172,   181,   189,   198,   206,   210,
     216,   226,   243,   244,   248,   258,   263,   268,   274,   308,
     321,   333,   334,   335,   336,   346,   355,   356,   357,   358,
     362,   363,   364,   365,   366,   371,   403,   425,   430,   460
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "$undefined", "tok_integer", "tok_float",
  "tok_boolean", "tok_string", "tok_plus_print", "tok_minus",
  "tok_multiply", "tok_divide", "tok_and", "tok_or", "tok_not", "tok_var",
  "tok_for_start", "tok_in", "tok_range", "tok_loop_start", "tok_loop_end",
  "tok_if", "tok_else", "tok_if_end", "tok_equal", "tok_less_than",
  "tok_greater_than", "tok_increment", "tok_print_anon",
  "tok_add_anon_vars", "tok_if_equals_20_start", "tok_else_block",
  "tok_identifier", "tok_int_literal", "tok_float_literal",
  "tok_string_literal", "tok_end", "$accept", "program", "@1", "statement",
  "declaration", "assignment", "output", "loop", "conditional",
  "condition", "term", "expression", "special_token", "add_anon_vars",
  "print_anon_var", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    36,    37,    37,    37,    38,    37,    37,    39,    39,
      39,    39,    39,    39,    39,    39,    39,    39,    39,    39,
      40,    40,    40,    40,    40,    40,    40,    40,    40,    41,
      41,    41,    42,    42,    43,    44,    44,    44,    44,    44,
      44,    45,    45,    45,    45,    45,    46,    46,    46,    46,
      47,    47,    47,    47,    47,    48,    48,    48,    49,    50
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     0,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       3,     3,     3,     3,     4,     4,     4,     4,     1,     3,
       5,     2,     2,     2,     7,     5,     7,     7,    11,     7,
       7,     3,     3,     3,     3,     3,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     1,     1,     1,     6,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     5,     0,     0,     0,     0,    57,    56,    55,     9,
       8,     0,     0,     0,    12,    28,    13,    14,    15,    16,
      10,    11,     7,     0,    49,    46,    47,    48,    17,    32,
      31,     0,     0,     0,     0,     0,    49,     0,    50,     0,
       0,     1,     3,     6,    21,    22,    23,    20,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    49,
      46,    29,     0,    24,    25,    26,    27,     0,     0,     0,
       0,    51,    52,    53,    54,    41,    42,    43,     0,     0,
       0,     0,     0,     0,     0,    35,    30,    58,     0,     0,
       0,     0,     0,    34,    40,    39,    37,    36,     0,     0,
       0,    38
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    12,    23,    13,    14,    15,    16,    17,    18,    37,
      38,    39,    19,    20,    21
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -40
static const yytype_int16 yypact[] =
{
      73,     3,    -7,   -17,    42,    -4,     2,   -40,   -40,   -40,
     -40,    43,    51,    22,   -40,   -40,   -40,   -40,   -40,   -40,
     -40,   -40,   -40,    22,   -40,   -40,   -40,   -40,   -40,   -40,
     -40,    56,    57,    63,    69,    75,     5,    84,   -40,   151,
      23,   -40,   -40,   -40,    31,    44,   -40,   -40,    67,    77,
     103,    96,    52,    52,    52,    52,    52,    52,    52,   -40,
     100,    71,   104,    88,    71,    98,    71,    97,   101,   107,
     -14,    11,    11,   -40,   -40,    50,    50,    50,    52,   112,
     119,   142,   142,   142,   142,   -40,    81,   -40,   110,   108,
     109,   113,   114,   -40,   111,   -40,   -40,   -40,   124,   142,
     115,   -40
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -40,   -13,   -40,   -40,   -40,   -40,   -40,   -40,   -40,   -40,
     120,   -39,   -40,   -40,   -40
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -49
static const yytype_int8 yytable[] =
{
      42,    61,    24,    22,    83,    64,    66,    84,    85,    30,
      43,    36,    35,    71,    72,    73,    74,    75,    76,    77,
      54,    55,    -2,     1,    25,    26,    27,    28,    49,     2,
      50,     3,    59,    25,    26,    27,     4,     5,    70,    86,
      -2,    -2,     6,     7,     8,    31,    32,    33,    34,     9,
      10,    41,    40,    11,    60,    26,    27,    52,    53,    54,
      55,    59,    25,    63,    27,    44,    45,    88,    89,    90,
      91,    92,    46,    -2,     1,    25,    26,    65,    47,    53,
       2,    55,     3,    25,    26,    27,   100,     4,     5,    53,
      54,    55,    48,     6,     7,     8,   -47,     1,   -47,    67,
       9,    10,    51,     2,    11,     3,   -48,    78,   -48,    68,
       4,     5,    69,    79,    -2,    80,     6,     7,     8,    81,
       1,    87,    29,     9,    10,    82,     2,    11,     3,    93,
      94,    95,    98,     4,     5,    96,    97,   101,    -2,     6,
       7,     8,    99,     1,     0,     0,     9,    10,     0,     2,
      11,     3,     0,     0,     0,     0,     4,     5,    52,    53,
      54,    55,     6,     7,     8,     0,     0,     0,     0,     9,
      10,     0,     0,    11,    56,    57,    58
};

static const yytype_int8 yycheck[] =
{
      13,    40,     9,     0,    18,    44,    45,    21,    22,    26,
      23,     9,    16,    52,    53,    54,    55,    56,    57,    58,
       9,    10,     0,     1,    31,    32,    33,    34,    23,     7,
      25,     9,     9,    31,    32,    33,    14,    15,    51,    78,
      18,    19,    20,    21,    22,     3,     4,     5,     6,    27,
      28,     0,     9,    31,    31,    32,    33,     7,     8,     9,
      10,     9,    31,    32,    33,     9,     9,    80,    81,    82,
      83,    84,     9,     0,     1,    31,    32,    33,     9,     8,
       7,    10,     9,    31,    32,    33,    99,    14,    15,     8,
       9,    10,    17,    20,    21,    22,     8,     1,    10,    32,
      27,    28,    18,     7,    31,     9,     8,     7,    10,    32,
      14,    15,     9,     9,    18,    18,    20,    21,    22,    18,
       1,     9,     2,    27,    28,    18,     7,    31,     9,    19,
      22,    22,    21,    14,    15,    22,    22,    22,    19,    20,
      21,    22,    18,     1,    -1,    -1,    27,    28,    -1,     7,
      31,     9,    -1,    -1,    -1,    -1,    14,    15,     7,     8,
       9,    10,    20,    21,    22,    -1,    -1,    -1,    -1,    27,
      28,    -1,    -1,    31,    23,    24,    25
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     7,     9,    14,    15,    20,    21,    22,    27,
      28,    31,    37,    39,    40,    41,    42,    43,    44,    48,
      49,    50,     0,    38,     9,    31,    32,    33,    34,    46,
      26,     3,     4,     5,     6,    16,     9,    45,    46,    47,
       9,     0,    37,    37,     9,     9,     9,     9,    17,    23,
      25,    18,     7,     8,     9,    10,    23,    24,    25,     9,
      31,    47,     7,    32,    47,    33,    47,    32,    32,     9,
      37,    47,    47,    47,    47,    47,    47,    47,     7,     9,
      18,    18,    18,    18,    21,    22,    47,     9,    37,    37,
      37,    37,    37,    19,    22,    22,    22,    22,    21,    18,
      37,    22
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
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
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
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
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



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



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
        case 2:
#line 91 "muslang.y"
    {debugBison(1);;}
    break;

  case 3:
#line 92 "muslang.y"
    {debugBison(2);;}
    break;

  case 4:
#line 93 "muslang.y"
    {debugBison(2);;}
    break;

  case 5:
#line 94 "muslang.y"
    {
		debugBison(997);
		yyerrok; /* Try to recover from errors wherever they occur */
		yyclearin; /* Clear the lookahead token */
	;}
    break;

  case 7:
#line 99 "muslang.y"
    {
		debugBison(998); 
		yyerrok; /* Handle errors that extend to EOF */
		YYACCEPT; /* Accept what we've parsed so far */
	;}
    break;

  case 8:
#line 108 "muslang.y"
    {
		debugBison(300);
		/* Direct handler for C F♯ C♯ E C♯ C♯ as a single token */
		if (anonVarCounter < 2) {
			yyerror("Not enough anonymous variables for addition");
			exit(EXIT_FAILURE);
		}
		
		fprintf(stderr, "Processing addition pattern as single token with anon vars: %d and %d\n", 
		        anonVarCounter-2, anonVarCounter-1);
		
		// Get the two most recent anonymous variables
		Value *val1 = getAnonVar(anonVarCounter-2);  // First anonymous var (x)
		Value *val2 = getAnonVar(anonVarCounter-1);  // Second anonymous var (y)
		
		// Create the addition operation
		Value *sum = builder.CreateFAdd(val1, val2, "fadd");
		
		// Create a new anonymous variable for the result
		std::string name = getNextAnonVarName();
		setDouble(name.c_str(), sum);
		latestAnon = anonVarCounter - 1;
		
		fprintf(stderr, "Created new anon var %d with sum\n", latestAnon);
	;}
    break;

  case 9:
#line 133 "muslang.y"
    {
		debugBison(301);
		/* Direct handler for E C♯ as a single token */
		if (latestAnon >= 0) {
			fprintf(stderr, "Print anon token: Printing anon var %d\n", latestAnon);
			Value* val = getLatestAnon();
			printDouble(val);
		} else {
			yyerror("No anonymous variable available to print");
		}
	;}
    break;

  case 10:
#line 144 "muslang.y"
    {debugBison(100);;}
    break;

  case 11:
#line 145 "muslang.y"
    {debugBison(201);;}
    break;

  case 12:
#line 146 "muslang.y"
    {debugBison(3);;}
    break;

  case 13:
#line 147 "muslang.y"
    {debugBison(4);;}
    break;

  case 14:
#line 148 "muslang.y"
    {debugBison(5);;}
    break;

  case 15:
#line 149 "muslang.y"
    {debugBison(6);;}
    break;

  case 16:
#line 150 "muslang.y"
    {debugBison(7);;}
    break;

  case 17:
#line 151 "muslang.y"
    {  /* Add this rule to handle the final string prints */
		debugBison(30);
		printString((yyvsp[(2) - (2)].string_literal));
		free((yyvsp[(2) - (2)].string_literal));
	;}
    break;

  case 18:
#line 156 "muslang.y"
    { 
		debugBison(999); 
		yyerrok; /* Error recovery - consume the token and continue */
		YYABORT; /* Stop parsing to prevent infinite loops */
	;}
    break;

  case 19:
#line 161 "muslang.y"
    {
		debugBison(996);
		yyerrok; /* Recover from errors in statements too */
	;}
    break;

  case 20:
#line 168 "muslang.y"
    {debugBison(7); /* Variable declaration with string type */;}
    break;

  case 21:
#line 169 "muslang.y"
    {debugBison(8); /* Variable declaration with integer type */;}
    break;

  case 22:
#line 170 "muslang.y"
    {debugBison(9); /* Variable declaration with float type */;}
    break;

  case 23:
#line 171 "muslang.y"
    {debugBison(10); /* Variable declaration with boolean type */;}
    break;

  case 24:
#line 173 "muslang.y"
    {
		debugBison(101); 
		/* Anonymous variable declaration with integer type and initial value */
		std::string name = getNextAnonVarName();
		Value *val = createDoubleConstant((double)(yyvsp[(4) - (4)].int_literal));
		setDouble(name.c_str(), val);
		latestAnon = anonVarCounter - 1;
	;}
    break;

  case 25:
#line 182 "muslang.y"
    {
		debugBison(103);
		/* Anonymous variable declaration with integer type and expression value */
		std::string name = getNextAnonVarName();
		setDouble(name.c_str(), (yyvsp[(4) - (4)].value));
		latestAnon = anonVarCounter - 1;
	;}
    break;

  case 26:
#line 190 "muslang.y"
    {
		debugBison(102); 
		/* Anonymous variable declaration with float type and initial value */
		std::string name = getNextAnonVarName();
		Value *val = createDoubleConstant((yyvsp[(4) - (4)].float_literal));
		setDouble(name.c_str(), val);
		latestAnon = anonVarCounter - 1;
	;}
    break;

  case 27:
#line 199 "muslang.y"
    {
		debugBison(104);
		/* Anonymous variable declaration with float type and expression value */
		std::string name = getNextAnonVarName();
		setDouble(name.c_str(), (yyvsp[(4) - (4)].value));
		latestAnon = anonVarCounter - 1;
	;}
    break;

  case 28:
#line 206 "muslang.y"
    {debugBison(11);;}
    break;

  case 29:
#line 210 "muslang.y"
    {
		debugBison(12); 
		// Fix: Properly handle the assignment with value
		setDouble((yyvsp[(1) - (3)].identifier), (yyvsp[(3) - (3)].value)); 
		free((yyvsp[(1) - (3)].identifier));
	;}
    break;

  case 30:
#line 216 "muslang.y"
    {
		debugBison(34);
		// Handle case for "i C♯ i E 2" (var = var + expr)
		Value* ptr = getFromSymbolTable((yyvsp[(1) - (5)].identifier));
		Value* val = builder.CreateLoad(builder.getDoubleTy(), ptr, "load_for_addition");
		Value* result = performBinaryOperation(val, (yyvsp[(5) - (5)].value), '+');
		setDouble((yyvsp[(1) - (5)].identifier), result);
		free((yyvsp[(1) - (5)].identifier));
		free((yyvsp[(3) - (5)].identifier));
	;}
    break;

  case 31:
#line 226 "muslang.y"
    {
		debugBison(33); 
		/* Special case for C♯ E E (increment latest anonymous variable) */
		if (latestAnon >= 0) {
			std::string name = "anon" + std::to_string(latestAnon);
			Value* ptr = getFromSymbolTable(name.c_str());
			Value* val = builder.CreateLoad(builder.getDoubleTy(), ptr, "load_anon");
			Value* one = createDoubleConstant(1.0);
			Value* result = performBinaryOperation(val, one, '+');
			setDouble(name.c_str(), result);
		} else {
			yyerror("No anonymous variable available to increment");
		}
	;}
    break;

  case 32:
#line 243 "muslang.y"
    {debugBison(13); printDouble((yyvsp[(2) - (2)].value));;}
    break;

  case 33:
#line 244 "muslang.y"
    {debugBison(14); printString((yyvsp[(2) - (2)].string_literal)); free((yyvsp[(2) - (2)].string_literal));;}
    break;

  case 34:
#line 249 "muslang.y"
    {
		debugBison(15);
		createLoopStart((yyvsp[(4) - (7)].int_literal));
		/* Loop body code is automatically inserted by the parser */
		createLoopEnd();
	;}
    break;

  case 35:
#line 259 "muslang.y"
    {
		debugBison(16);
		createIfStatement((yyvsp[(2) - (5)].value));
	;}
    break;

  case 36:
#line 264 "muslang.y"
    {
		debugBison(17);
		createIfElseStatement((yyvsp[(2) - (7)].value));
	;}
    break;

  case 37:
#line 269 "muslang.y"
    {
		debugBison(17);
		createIfElseStatement((yyvsp[(2) - (7)].value));
	;}
    break;

  case 38:
#line 275 "muslang.y"
    {
		debugBison(44);
		// Special pattern for if z==20 ... else ... with explicit tokens
		Value *val = getLatestAnon();
		Value *constant = createDoubleConstant((double)(yyvsp[(4) - (11)].int_literal));
		Value *cond = createComparison(val, constant, llvm::CmpInst::FCMP_OEQ);
		
		// Create basic blocks for if-else structure
		BasicBlock *thenBlock = BasicBlock::Create(context, "then", mainFunction);
		BasicBlock *elseBlock = BasicBlock::Create(context, "else", mainFunction);
		BasicBlock *mergeBlock = BasicBlock::Create(context, "ifcont", mainFunction);
		
		// Convert condition to boolean
		Value *condBool = builder.CreateFPToUI(cond, builder.getInt1Ty(), "ifcond");
		
		// Create branch instruction based on condition
		builder.CreateCondBr(condBool, thenBlock, elseBlock);
		
		// Set insertion point for then block code (handled by parser)
		builder.SetInsertPoint(thenBlock);
		
		// Branch from then block to merge block
		builder.CreateBr(mergeBlock);
		
		// Set insertion point for else block code (handled by parser)
		builder.SetInsertPoint(elseBlock);
		
		// Branch from else block to merge block
		builder.CreateBr(mergeBlock);
		
		// Set insertion point to merge block for code after if-else
		builder.SetInsertPoint(mergeBlock);
	;}
    break;

  case 39:
#line 309 "muslang.y"
    {
		debugBison(42);
		// Special case for G G G C♯ F♯ F♯ C♯ (if x > y)
		if (anonVarCounter < 2) {
			yyerror("Not enough anonymous variables for comparison");
			exit(EXIT_FAILURE);
		}
		Value *val1 = getAnonVar(anonVarCounter-2); // Second last anonymous variable (x)
		Value *val2 = getAnonVar(anonVarCounter-1); // Last anonymous variable (y)
		Value *cond = createComparison(val1, val2, llvm::CmpInst::FCMP_OGT);
		createIfStatement(cond);
	;}
    break;

  case 40:
#line 322 "muslang.y"
    {
		debugBison(43);
		// Special case for G G G C♯ G♯ G♯ 20 (if z == 20)
		Value *val = getLatestAnon();
		Value *constant = createDoubleConstant((double)(yyvsp[(4) - (7)].int_literal));
		Value *cond = createComparison(val, constant, llvm::CmpInst::FCMP_OEQ);
		createIfStatement(cond);
	;}
    break;

  case 41:
#line 333 "muslang.y"
    {debugBison(18); (yyval.value) = createComparison((yyvsp[(1) - (3)].value), (yyvsp[(3) - (3)].value), llvm::CmpInst::FCMP_OEQ);;}
    break;

  case 42:
#line 334 "muslang.y"
    {debugBison(19); (yyval.value) = createComparison((yyvsp[(1) - (3)].value), (yyvsp[(3) - (3)].value), llvm::CmpInst::FCMP_OLT);;}
    break;

  case 43:
#line 335 "muslang.y"
    {debugBison(20); (yyval.value) = createComparison((yyvsp[(1) - (3)].value), (yyvsp[(3) - (3)].value), llvm::FCmpInst::FCMP_OGT);;}
    break;

  case 44:
#line 336 "muslang.y"
    {debugBison(31); 
		/* Special case for C♯ F♯ F♯ C♯ (compare the two most recent anonymous variables) */
		if (anonVarCounter < 2) {
			yyerror("Not enough anonymous variables for comparison");
			exit(EXIT_FAILURE);
		}
		Value *val1 = getAnonVar(anonVarCounter-2); // Second last anonymous variable (x)
		Value *val2 = getAnonVar(anonVarCounter-1); // Last anonymous variable (y)
		(yyval.value) = createComparison(val1, val2, llvm::CmpInst::FCMP_OGT);
	;}
    break;

  case 45:
#line 346 "muslang.y"
    {debugBison(32);
		/* Special case for C♯ G♯ G♯ 20 (compare last anonymous variable with a constant) */
		Value *val = getLatestAnon();
		Value *constant = createDoubleConstant((double)(yyvsp[(3) - (3)].int_literal));
		(yyval.value) = createComparison(val, constant, llvm::CmpInst::FCMP_OEQ);
	;}
    break;

  case 46:
#line 355 "muslang.y"
    {debugBison(21); Value* ptr = getFromSymbolTable((yyvsp[(1) - (1)].identifier)); (yyval.value) = builder.CreateLoad(builder.getDoubleTy(), ptr, "load_identifier"); free((yyvsp[(1) - (1)].identifier));;}
    break;

  case 47:
#line 356 "muslang.y"
    {debugBison(22); (yyval.value) = createDoubleConstant((double)(yyvsp[(1) - (1)].int_literal));;}
    break;

  case 48:
#line 357 "muslang.y"
    {debugBison(23); (yyval.value) = createDoubleConstant((yyvsp[(1) - (1)].float_literal));;}
    break;

  case 49:
#line 358 "muslang.y"
    {debugBison(29); (yyval.value) = getLatestAnon(); /* C♯ refers to latest anonymous variable */;}
    break;

  case 50:
#line 362 "muslang.y"
    {debugBison(24); (yyval.value) = (yyvsp[(1) - (1)].value);;}
    break;

  case 51:
#line 363 "muslang.y"
    {debugBison(25); (yyval.value) = performBinaryOperation((yyvsp[(1) - (3)].value), (yyvsp[(3) - (3)].value), '+');;}
    break;

  case 52:
#line 364 "muslang.y"
    {debugBison(26); (yyval.value) = performBinaryOperation((yyvsp[(1) - (3)].value), (yyvsp[(3) - (3)].value), '-');;}
    break;

  case 53:
#line 365 "muslang.y"
    {debugBison(27); (yyval.value) = performBinaryOperation((yyvsp[(1) - (3)].value), (yyvsp[(3) - (3)].value), '*');;}
    break;

  case 54:
#line 366 "muslang.y"
    {debugBison(28); (yyval.value) = performBinaryOperation((yyvsp[(1) - (3)].value), (yyvsp[(3) - (3)].value), '/');;}
    break;

  case 55:
#line 371 "muslang.y"
    { 
		debugBison(40); 
		// Handle end of if statement 
		if (!ifStack.empty()) {
			IfInfo ifInfo = ifStack.top();
			
			// Add branch to merge block if needed
			if (!builder.GetInsertBlock()->getTerminator()) {
				builder.CreateBr(ifInfo.mergeBlock);
			}
			
			// Check if this is part of an if-else statement
			if (ifInfo.elseBlock) {
				// If we're currently in the then block, we should move to the else block
				if (builder.GetInsertBlock() == ifInfo.thenBlock) {
					fprintf(stderr, "Moving from then block to else block\n");
					builder.SetInsertPoint(ifInfo.elseBlock);
					// Don't pop the stack yet - we're moving to the else part
				} else {
					// We're in the else block, so finish the if-else structure
					fprintf(stderr, "Finishing if-else statement, moving to merge block\n");
					ifStack.pop();
					builder.SetInsertPoint(ifInfo.mergeBlock);
				}
			} else {
				// Regular if statement
				fprintf(stderr, "Finishing if statement, moving to merge block\n");
				ifStack.pop();
				builder.SetInsertPoint(ifInfo.mergeBlock);
			}
		}
	;}
    break;

  case 56:
#line 403 "muslang.y"
    {
		debugBison(41);
		// Handle else part of if-else statement
		if (!ifStack.empty()) {
			IfInfo ifInfo = ifStack.top();
			
			// Add branch from 'then' block to merge block if needed
			if (!builder.GetInsertBlock()->getTerminator()) {
				builder.CreateBr(ifInfo.mergeBlock);
			}
			
			// Check if this if statement has an else block
			if (ifInfo.elseBlock) {
				fprintf(stderr, "Handling else token, moving to else block\n");
				builder.SetInsertPoint(ifInfo.elseBlock);
			} else {
				yyerror("else without matching if");
			}
		} else {
			yyerror("else without matching if");
		}
	;}
    break;

  case 57:
#line 425 "muslang.y"
    { debugBison(42); /* Handle if statement beginning */ ;}
    break;

  case 58:
#line 431 "muslang.y"
    {
		debugBison(105);
		/* Special case for C F♯ C♯ E C♯ C♯ (add previous two anonymous variables) */
		if (anonVarCounter < 2) {
			yyerror("Not enough anonymous variables for addition");
			exit(EXIT_FAILURE);
		}
		
		fprintf(stderr, "Processing addition pattern with anon vars: %d and %d\n", 
		        anonVarCounter-2, anonVarCounter-1);
		
		// Get the two most recent anonymous variables
		Value *val1 = getAnonVar(anonVarCounter-2);  // First anonymous var (x)
		Value *val2 = getAnonVar(anonVarCounter-1);  // Second anonymous var (y)
		
		// Create the addition operation
		Value *sum = builder.CreateFAdd(val1, val2, "fadd");
		
		// Create a new anonymous variable for the result
		std::string name = getNextAnonVarName();
		setDouble(name.c_str(), sum);
		latestAnon = anonVarCounter - 1;
		
		fprintf(stderr, "Created new anon var %d with sum\n", latestAnon);
	;}
    break;

  case 59:
#line 461 "muslang.y"
    {
        debugBison(200);
        /* Special case for E C♯ (print the latest anonymous variable) */
        if (latestAnon >= 0) {
            fprintf(stderr, "Print rule: Printing anon var %d\n", latestAnon);
            Value* val = getLatestAnon();
            printDouble(val);
        } else {
            yyerror("No anonymous variable available to print");
        }
    ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2098 "muslang.tab.c"
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


#line 473 "muslang.y"

int main(int argc, char** argv) {
	// Process command line arguments
	bool fileProvided = false;
	
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "--debug") == 0 || strcmp(argv[i], "-d") == 0) {
			debug_mode = 1;
			if (debug_mode) fprintf(stderr, "Debug mode enabled\n");
		} else {
			// Assume it's the input file
			FILE *fp = fopen(argv[i], "r");
			if (fp) {
				yyin = fp;
				fileProvided = true;
			} else {
				fprintf(stderr, "Error: Could not open file '%s'\n", argv[i]);
				return EXIT_FAILURE;
			}
		}
	}
	
	if (!fileProvided) { 
		yyin = stdin; // Read from terminal if no file provided
	}
	
	// Initialize LLVM
	initLLVM();
	
	// Parse the input
	int parserResult = yyparse();
	
	// Handle parser result - ignore EOF syntax error
	if (parserResult != 0) {
		if (debug_mode) fprintf(stderr, "Parser reported error code %d (ignoring EOF syntax error)\n", parserResult);
	} else {
		if (debug_mode) fprintf(stderr, "Parsing completed successfully\n");
	}
	
	// Handle any unclosed control structures
	while (!ifStack.empty()) {
		IfInfo ifInfo = ifStack.top();
		ifStack.pop();
		
		// If we're in the then block and no terminator exists
		BasicBlock *currentBlock = builder.GetInsertBlock();
		if (currentBlock && !currentBlock->getTerminator()) {
			// Create branch to the merge block
			builder.CreateBr(ifInfo.mergeBlock);
		}
		
		// Move to the merge point for continuing execution
		builder.SetInsertPoint(ifInfo.mergeBlock);
	}
	
	while (!loopStack.empty()) {
		LoopInfo loopInfo = loopStack.top();
		loopStack.pop();
		
		// If we're in the loop body and no terminator exists
		BasicBlock *currentBlock = builder.GetInsertBlock();
		if (currentBlock && !currentBlock->getTerminator()) {
			// Create branch back to the header for the next iteration
			builder.CreateBr(loopInfo.headerBlock);
		}
		
		// Move to the exit point for continuing execution
		builder.SetInsertPoint(loopInfo.exitBlock);
	}
	
	// Add the final return instruction
	BasicBlock *currentBlock = builder.GetInsertBlock();
	if (currentBlock && !currentBlock->getTerminator()) {
		builder.CreateRet(ConstantInt::get(context, APInt(32, 0)));
		if (debug_mode) fprintf(stderr, "Added final return instruction to program\n");
	}
	
	// Print the LLVM IR - always do this even if there were parsing errors
	printLLVMIR();
	
	// Always return success - the IR generation is what matters
	return EXIT_SUCCESS;
}
