/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON_VERSION "2.7.12-4996"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "syntax.y"

	#include<stdio.h>
	#include<string.h>
	#include<stdlib.h>
	#include<ctype.h>
	#include"tree.h"

	#define YYSTYPE struct TreeNode
	
	#define STACKMAX 100

	struct TreeNode *root = NULL;
	
	//节点栈
	struct TreeNode *NodeStack[STACKMAX];
	static int stackTop = -1;
	
	//栈操作
	void push(TreeNode *node) {
		if (stackTop == STACKMAX-1) {
			printf("stack overflow!\n");
			return;
		}
		stackTop++;
		NodeStack[stackTop] = node;
	}

	TreeNode *pop() {
		if (stackTop == -1) {
			printf("Nothing to pop out in stack!\n");
			return;
		}
		TreeNode *p = NodeStack[stackTop];
		stackTop--;
		return p;
	}

	void Traverse(TreeNode *subtree, int depth) {
		if(subtree != NULL) {
		//	if(subtree->state != "empty") {
				int i = 0;
				for(; i < depth; i++)
					printf(" ");//缩进
				printf("%s ", subtree->state);
				if(subtree->state == "INT")
					printf("%d ", subtree->value.intValue);
				else if(subtree->state == "FLOAT")
					printf("%f ", subtree->value.floatValue);
				else if(subtree->state == "ID")
					printf("%s ", subtree->value.idValue);

		//	}
			printf("(%d)\n",subtree->line);
			depth++;
			Traverse(subtree->firstChild, depth);
			depth--;
			Traverse(subtree->rightBrother, depth);
			//printf("-----doProgram-----\n");
			//doProgram(root);
		}
	}



/* Line 371 of yacc.c  */
#line 133 "syntax.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "syntax.tab.h".  */
#ifndef YY_YY_SYNTAX_TAB_H_INCLUDED
# define YY_YY_SYNTAX_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     FLOAT = 259,
     ID = 260,
     SEMI = 261,
     COMMA = 262,
     ASSIGNOP = 263,
     RELOP = 264,
     PLUS = 265,
     MINUS = 266,
     STAR = 267,
     DIV = 268,
     AND = 269,
     OR = 270,
     NOT = 271,
     DOT = 272,
     TYPE = 273,
     LP = 274,
     RP = 275,
     LB = 276,
     RB = 277,
     LC = 278,
     RC = 279,
     STRUCT = 280,
     RETURN = 281,
     IF = 282,
     ELSE = 283,
     WHILE = 284,
     FOR = 285,
     BREAK = 286,
     CONTINUE = 287,
     LOWER_THAN_ELSE = 288
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

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

#endif /* !YY_YY_SYNTAX_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 232 "syntax.tab.c"

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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif


/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   259

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  34
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  64
/* YYNRULES -- Number of states.  */
#define YYNSTATES  125

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   288

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
      25,    26,    27,    28,    29,    30,    31,    32,    33
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    13,    16,    20,    22,
      26,    28,    30,    36,    39,    40,    42,    44,    46,    51,
      56,    60,    64,    66,    69,    74,    77,    78,    81,    83,
      87,    93,   101,   107,   110,   113,   123,   126,   127,   131,
     133,   137,   139,   143,   145,   146,   150,   154,   158,   162,
     166,   170,   174,   178,   182,   185,   188,   193,   197,   202,
     206,   208,   210,   212,   216
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      35,     0,    -1,    36,    -1,    -1,    37,    36,    -1,    39,
      38,     6,    -1,    39,     6,    -1,    39,    44,    47,    -1,
      43,    -1,    43,     7,    38,    -1,    18,    -1,    40,    -1,
      25,    41,    23,    50,    24,    -1,    25,    42,    -1,    -1,
       5,    -1,     5,    -1,     5,    -1,    43,    21,     3,    22,
      -1,     5,    19,    45,    20,    -1,     5,    19,    20,    -1,
      46,     7,    45,    -1,    46,    -1,    39,    43,    -1,    23,
      50,    48,    24,    -1,    49,    48,    -1,    -1,    55,     6,
      -1,    47,    -1,    26,    55,     6,    -1,    27,    19,    55,
      20,    49,    -1,    27,    19,    55,    20,    49,    28,    49,
      -1,    29,    19,    55,    20,    49,    -1,    31,     6,    -1,
      32,     6,    -1,    30,    19,    54,     6,    55,     6,    54,
      20,    49,    -1,    51,    50,    -1,    -1,    39,    52,     6,
      -1,    53,    -1,    53,     7,    52,    -1,    43,    -1,    43,
       8,    55,    -1,    55,    -1,    -1,    55,     8,    55,    -1,
      55,    14,    55,    -1,    55,    15,    55,    -1,    55,     9,
      55,    -1,    55,    10,    55,    -1,    55,    11,    55,    -1,
      55,    12,    55,    -1,    55,    13,    55,    -1,    19,    55,
      20,    -1,    11,    55,    -1,    16,    55,    -1,     5,    19,
      56,    20,    -1,     5,    19,    20,    -1,    55,    21,    55,
      22,    -1,    55,    17,     5,    -1,     5,    -1,     3,    -1,
       4,    -1,    55,     7,    56,    -1,    55,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    95,    95,   109,   116,   130,   147,   162,   178,   188,
     207,   221,   234,   262,   279,   286,   302,   318,   334,   362,
     388,   414,   431,   443,   457,   480,   492,   502,   517,   528,
     547,   572,   607,   635,   654,   673,   716,   729,   740,   759,
     770,   790,   801,   821,   831,   840,   857,   875,   894,   912,
     931,   950,   969,   989,  1008,  1023,  1039,  1064,  1087,  1109,
    1130,  1145,  1160,  1177,  1194
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "FLOAT", "ID", "SEMI", "COMMA",
  "ASSIGNOP", "RELOP", "PLUS", "MINUS", "STAR", "DIV", "AND", "OR", "NOT",
  "DOT", "TYPE", "LP", "RP", "LB", "RB", "LC", "RC", "STRUCT", "RETURN",
  "IF", "ELSE", "WHILE", "FOR", "BREAK", "CONTINUE", "LOWER_THAN_ELSE",
  "$accept", "Program", "ExtDefList", "ExtDef", "ExtDecList", "Specifier",
  "StructSpecifier", "OptTag", "Tag", "VarDec", "FunDec", "VarList",
  "ParamDec", "CompSt", "StmtList", "Stmt", "DefList", "Def", "DecList",
  "Dec", "OptExp", "Exp", "Args", YY_NULL
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
     285,   286,   287,   288
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    34,    35,    36,    36,    37,    37,    37,    38,    38,
      39,    39,    40,    40,    41,    41,    42,    43,    43,    44,
      44,    45,    45,    46,    47,    48,    48,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    50,    50,    51,    52,
      52,    53,    53,    54,    54,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    56,    56
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     3,     2,     3,     1,     3,
       1,     1,     5,     2,     0,     1,     1,     1,     4,     4,
       3,     3,     1,     2,     4,     2,     0,     2,     1,     3,
       5,     7,     5,     2,     2,     9,     2,     0,     3,     1,
       3,     1,     3,     1,     0,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     4,     3,     4,     3,
       1,     1,     1,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,    10,    14,     0,     2,     3,     0,    11,    16,     0,
      13,     1,     4,    17,     6,     0,     8,     0,    37,     0,
       5,     0,     0,    37,     7,     0,     0,    37,    20,     0,
       0,    22,    17,     9,     0,    26,    41,     0,    39,    12,
      36,    23,    19,     0,    18,    61,    62,    60,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    28,     0,    26,
       0,     0,    38,     0,    21,     0,    54,    55,     0,     0,
       0,     0,    44,    33,    34,    24,    25,    27,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    42,    40,
      57,    64,     0,    53,    29,     0,     0,     0,    43,    45,
      48,    49,    50,    51,    52,    46,    47,    59,     0,     0,
      56,     0,     0,     0,    58,    63,    30,    32,     0,     0,
      44,    31,     0,     0,    35
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,    15,    25,     7,     9,    10,    16,
      17,    30,    31,    57,    58,    59,    26,    27,    37,    38,
      97,    60,    92
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -49
static const yytype_int16 yypact[] =
{
       3,   -49,    10,    29,   -49,     3,    21,   -49,    18,    32,
     -49,   -49,   -49,    24,   -49,    38,    -2,    33,     3,    20,
     -49,    55,    61,     3,   -49,    55,    57,     3,   -49,    55,
      51,    75,   -49,   -49,    73,    47,    -1,    80,    90,   -49,
     -49,    77,   -49,     3,   -49,   -49,   -49,    92,    43,    43,
      43,    43,   104,   106,   108,   103,   120,   -49,    88,    47,
      79,    43,   -49,    55,   -49,    64,    -3,    -5,   151,    93,
      43,    43,    43,   -49,   -49,   -49,   -49,   -49,    43,    43,
      43,    43,    43,    43,    43,    43,   133,    43,   193,   -49,
     -49,   122,   121,   -49,   -49,   165,   179,   134,   193,   214,
     214,    -3,    -3,    -5,    -5,   238,   226,   -49,   136,    43,
     -49,    47,    47,    43,   -49,   -49,   114,   -49,   107,    47,
      43,   -49,   132,    47,   -49
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -49,   -49,   149,   -49,   135,     6,   -49,   -49,   -49,   -21,
     -49,   112,   -49,   150,   110,   100,    30,   -49,   118,   -49,
      50,   -48,    74
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -16
static const yytype_int8 yytable[] =
{
      66,    67,    68,    69,    36,    21,     6,    61,    41,    82,
      83,     6,    86,    88,    86,     8,    87,    91,    87,    22,
      22,     1,    95,    96,    98,    29,    13,    14,     2,    11,
      99,   100,   101,   102,   103,   104,   105,   106,     1,   108,
      28,   -15,    36,    19,    20,     2,    45,    46,    47,    29,
      45,    46,    47,    35,    48,    18,    23,    40,    48,    49,
      32,    91,    50,    49,    34,   118,    50,    45,    46,    47,
      23,    42,    98,    51,    52,    48,    53,    54,    55,    56,
      49,    39,    43,    50,    90,    77,    62,    78,    79,    80,
      81,    82,    83,    84,    85,    44,    86,    63,    22,    94,
      87,    78,    79,    80,    81,    82,    83,    84,    85,    73,
      86,    65,    75,   120,    87,    78,    79,    80,    81,    82,
      83,    84,    85,    70,    86,    71,    74,    72,    87,   109,
      78,    79,    80,    81,    82,    83,    84,    85,   107,    86,
     113,   110,   119,    87,    78,    79,    80,    81,    82,    83,
      84,    85,   123,    86,    12,    64,    33,    87,   114,    78,
      79,    80,    81,    82,    83,    84,    85,    24,    86,    76,
     122,    93,    87,    78,    79,    80,    81,    82,    83,    84,
      85,    89,    86,   115,     0,   111,    87,    78,    79,    80,
      81,    82,    83,    84,    85,     0,    86,     0,     0,   112,
      87,    78,    79,    80,    81,    82,    83,    84,    85,     0,
      86,   116,   117,     0,    87,     0,     0,     0,     0,   121,
       0,     0,     0,   124,    80,    81,    82,    83,    84,    85,
       0,    86,     0,     0,     0,    87,    80,    81,    82,    83,
      84,     0,     0,    86,     0,     0,     0,    87,    80,    81,
      82,    83,     0,     0,     0,    86,     0,     0,     0,    87
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-49)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
      48,    49,    50,    51,    25,     7,     0,     8,    29,    12,
      13,     5,    17,    61,    17,     5,    21,    65,    21,    21,
      21,    18,    70,    71,    72,    19,     5,     6,    25,     0,
      78,    79,    80,    81,    82,    83,    84,    85,    18,    87,
      20,    23,    63,    19,     6,    25,     3,     4,     5,    43,
       3,     4,     5,    23,    11,    23,    23,    27,    11,    16,
       5,   109,    19,    16,     3,   113,    19,     3,     4,     5,
      23,    20,   120,    26,    27,    11,    29,    30,    31,    32,
      16,    24,     7,    19,    20,     6,     6,     8,     9,    10,
      11,    12,    13,    14,    15,    22,    17,     7,    21,     6,
      21,     8,     9,    10,    11,    12,    13,    14,    15,     6,
      17,    19,    24,     6,    21,     8,     9,    10,    11,    12,
      13,    14,    15,    19,    17,    19,     6,    19,    21,     7,
       8,     9,    10,    11,    12,    13,    14,    15,     5,    17,
       6,    20,    28,    21,     8,     9,    10,    11,    12,    13,
      14,    15,    20,    17,     5,    43,    21,    21,    22,     8,
       9,    10,    11,    12,    13,    14,    15,    17,    17,    59,
     120,    20,    21,     8,     9,    10,    11,    12,    13,    14,
      15,    63,    17,   109,    -1,    20,    21,     8,     9,    10,
      11,    12,    13,    14,    15,    -1,    17,    -1,    -1,    20,
      21,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      17,   111,   112,    -1,    21,    -1,    -1,    -1,    -1,   119,
      -1,    -1,    -1,   123,    10,    11,    12,    13,    14,    15,
      -1,    17,    -1,    -1,    -1,    21,    10,    11,    12,    13,
      14,    -1,    -1,    17,    -1,    -1,    -1,    21,    10,    11,
      12,    13,    -1,    -1,    -1,    17,    -1,    -1,    -1,    21
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    18,    25,    35,    36,    37,    39,    40,     5,    41,
      42,     0,    36,     5,     6,    38,    43,    44,    23,    19,
       6,     7,    21,    23,    47,    39,    50,    51,    20,    39,
      45,    46,     5,    38,     3,    50,    43,    52,    53,    24,
      50,    43,    20,     7,    22,     3,     4,     5,    11,    16,
      19,    26,    27,    29,    30,    31,    32,    47,    48,    49,
      55,     8,     6,     7,    45,    19,    55,    55,    55,    55,
      19,    19,    19,     6,     6,    24,    48,     6,     8,     9,
      10,    11,    12,    13,    14,    15,    17,    21,    55,    52,
      20,    55,    56,    20,     6,    55,    55,    54,    55,    55,
      55,    55,    55,    55,    55,    55,    55,     5,    55,     7,
      20,    20,    20,     6,    22,    56,    49,    49,    55,    28,
       6,    49,    54,    20,    49
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
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
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  YYUSE (yytype);
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
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
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

  YYUSE (yytype);
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
/* Line 1787 of yacc.c  */
#line 95 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *p1 = pop();
		p->state = "Program";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = p1->rightBrother = NULL;
		root = p;
		Traverse(root, 0);
		printf("-----semantic analysis-----\n");
		doProgram(root);
	}
    break;

  case 3:
/* Line 1787 of yacc.c  */
#line 109 "syntax.y"
    {//empty
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		p->state = "empty";
		p->firstChild = p->rightBrother = NULL;
		p->productionRule = 2;
		push(p);						
	}
    break;

  case 4:
/* Line 1787 of yacc.c  */
#line 116 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *p2 = pop();
		TreeNode *p1 = pop();
		p->state = "ExtDefList";
		p->line = p1->line;
		p->firstChild = p1;
		p1->rightBrother = p2;
		p->rightBrother = NULL;
		p->productionRule = 1;
		push(p);	
	}
    break;

  case 5:
/* Line 1787 of yacc.c  */
#line 130 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *p3 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *p2 = pop();
		TreeNode *p1 = pop();
		p->state = "ExtDef";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = NULL;
		p1->rightBrother = p2;
		p2->rightBrother = p3;
		p3->state = (yyvsp[(3) - (3)]).state;
		p3->line = (yyvsp[(3) - (3)]).line;
		p3->rightBrother = NULL;
		p->productionRule = 1;
		push(p);	
	}
    break;

  case 6:
/* Line 1787 of yacc.c  */
#line 147 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *p2 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *p1 = pop();
		p->state = "ExtDef";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = NULL;
		p1->rightBrother = p2;
		p2->state = (yyvsp[(2) - (2)]).state;
		p2->line = (yyvsp[(2) - (2)]).line;
		p2->rightBrother = NULL;
		p->productionRule = 2;
		push(p);		
	}
    break;

  case 7:
/* Line 1787 of yacc.c  */
#line 162 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *p3 = pop();
		TreeNode *p2 = pop();
		TreeNode *p1 = pop();
		p->state = "ExtDef";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = NULL;
		p1->rightBrother = p2;
		p2->rightBrother = p3;
		p->productionRule = 3;
		push(p);		
	}
    break;

  case 8:
/* Line 1787 of yacc.c  */
#line 178 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *p1 = pop();
		p->state = "ExtDecList";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = NULL;
		p->productionRule = 1;
		push(p);			
	}
    break;

  case 9:
/* Line 1787 of yacc.c  */
#line 188 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *p3 = pop();
		TreeNode *p2 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *p1 = pop();
		p->state = "ExtDecList";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = NULL;
		p1->rightBrother = p2;
		p2->state = (yyvsp[(2) - (3)]).state;
		p2->line = (yyvsp[(2) - (3)]).line;
		p2->firstChild = NULL;
		p2->rightBrother = p3;
		p->productionRule = 2;
		push(p);		
	}
    break;

  case 10:
/* Line 1787 of yacc.c  */
#line 207 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *p1 = (TreeNode *)malloc(sizeof(TreeNode));
		p1->state = (yyvsp[(1) - (1)]).state;
		p1->line = (yyvsp[(1) - (1)]).line;
		p1->value = (yyvsp[(1) - (1)]).value;
		p1->firstChild = p1->rightBrother = NULL;
		p->state = "Specifier";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = NULL;
		p->productionRule = 1;
		push(p);	
	}
    break;

  case 11:
/* Line 1787 of yacc.c  */
#line 221 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *p1 = pop();
		p->state = "Specifier";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = NULL;
//		p1->rightBrother = NULL;
		p->productionRule = 2;
		push(p);	
	}
    break;

  case 12:
/* Line 1787 of yacc.c  */
#line 234 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *p5 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *p4 = pop();
		TreeNode *p3 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *p2 = pop();
		TreeNode *p1 = (TreeNode *)malloc(sizeof(TreeNode));
		p1->state = (yyvsp[(1) - (5)]).state;
		p1->line = (yyvsp[(1) - (5)]).line;
		p1->firstChild = NULL;
		p1->rightBrother = p2;
		p->state = "StructSpecifier";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = NULL;
		p2->rightBrother = p3;
		p3->state = (yyvsp[(3) - (5)]).state;
		p3->line = (yyvsp[(3) - (5)]).line;
		p3->firstChild = NULL;
		p3->rightBrother = p4;
		p4->rightBrother = p5;
		p5->state = (yyvsp[(5) - (5)]).state;
		p5->line = (yyvsp[(5) - (5)]).line;
		p5->firstChild = NULL;
		p5->rightBrother = NULL;
		p->productionRule = 1;
		push(p);					
	}
    break;

  case 13:
/* Line 1787 of yacc.c  */
#line 262 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *p2 = pop();
		TreeNode *p1 = (TreeNode *)malloc(sizeof(TreeNode));
		p1->state = (yyvsp[(1) - (2)]).state;
		p1->line = (yyvsp[(1) - (2)]).line;
		p1->firstChild = NULL;
		p1->rightBrother = p2;
		p->state = "StructSpecifier";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = NULL;
		p->productionRule = 2;
		push(p);					
	}
    break;

  case 14:
/* Line 1787 of yacc.c  */
#line 279 "syntax.y"
    {//empty
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		p->state = "empty";
		p->firstChild = p->rightBrother = NULL;
		p->productionRule = 2;
		push(p);			
	}
    break;

  case 15:
/* Line 1787 of yacc.c  */
#line 286 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *p1 = (TreeNode *)malloc(sizeof(TreeNode));
		p1->state = (yyvsp[(1) - (1)]).state;
		p1->line = (yyvsp[(1) - (1)]).line;
		p1->value = (yyvsp[(1) - (1)]).value;
		p1->firstChild = p1->rightBrother = NULL;
		p->state = "OptTag";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = NULL;
		p->productionRule = 1;
		push(p);					
	}
    break;

  case 16:
/* Line 1787 of yacc.c  */
#line 302 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *p1 = (TreeNode *)malloc(sizeof(TreeNode));
		p1->state = (yyvsp[(1) - (1)]).state;
		p1->line = (yyvsp[(1) - (1)]).line;
		p1->value = (yyvsp[(1) - (1)]).value;
		p1->firstChild = p1->rightBrother = NULL;
		p->state = "Tag";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = NULL;
		p->productionRule = 1;
		push(p);	
	}
    break;

  case 17:
/* Line 1787 of yacc.c  */
#line 318 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *p1 = (TreeNode *)malloc(sizeof(TreeNode));
		p1->state = (yyvsp[(1) - (1)]).state;
		p1->line = (yyvsp[(1) - (1)]).line;
		//printf("%s\n", $1.value.idValue);
		p1->value = (yyvsp[(1) - (1)]).value;
		printf("%s\n", p1->value.idValue);
		p1->firstChild = p1->rightBrother = NULL;
		p->state = "VarDec";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = NULL;
		p->productionRule = 1;
		push(p);	
	}
    break;

  case 18:
/* Line 1787 of yacc.c  */
#line 334 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *p4 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *p3 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *p2 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *p1 = pop();
		p->state = "VarDec";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = NULL;
		p1->rightBrother = p2;
		p2->state = (yyvsp[(2) - (4)]).state;
		p2->line = (yyvsp[(2) - (4)]).line;
		p2->firstChild = NULL;
		p2->rightBrother = p3;
		p3->state = (yyvsp[(3) - (4)]).state;
		p3->line = (yyvsp[(3) - (4)]).line;
		p3->value = (yyvsp[(3) - (4)]).value;
		p3->firstChild = NULL;
		p3->rightBrother = p4;
		p4->state = (yyvsp[(4) - (4)]).state;
		p4->line = (yyvsp[(4) - (4)]).line;
		p4->firstChild = p4->rightBrother = NULL;
		p->productionRule = 2;
		push(p);	
	}
    break;

  case 19:
/* Line 1787 of yacc.c  */
#line 362 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *p4 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *p3 = pop();
		TreeNode *p2 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *p1 = (TreeNode *)malloc(sizeof(TreeNode));
		p1->state = (yyvsp[(1) - (4)]).state;
		p1->line = (yyvsp[(1) - (4)]).line;
		p1->value = (yyvsp[(1) - (4)]).value;
		p1->firstChild = NULL;
		p1->rightBrother = p2;
		p->state = "FunDec";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = NULL;
		p2->state = (yyvsp[(2) - (4)]).state;
		p2->line = (yyvsp[(2) - (4)]).line;
		p2->firstChild = NULL;
		p2->rightBrother = p3;
		p3->rightBrother = p4;
		p4->state = (yyvsp[(4) - (4)]).state;
		p4->line = (yyvsp[(4) - (4)]).line;
		p4->firstChild = p4->rightBrother = NULL;		
		p->productionRule = 1;
		push(p);			 
	}
    break;

  case 20:
/* Line 1787 of yacc.c  */
#line 388 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *p3 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *p2 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *p1 = (TreeNode *)malloc(sizeof(TreeNode));
		p1->state = (yyvsp[(1) - (3)]).state;
		p1->line = (yyvsp[(1) - (3)]).line;
		p1->value = (yyvsp[(1) - (3)]).value;
		p1->firstChild = NULL;
		p1->rightBrother = p2;
		p->state = "FunDec";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = NULL;
		p2->state = (yyvsp[(2) - (3)]).state;
		p2->line = (yyvsp[(2) - (3)]).line;
		p2->firstChild = NULL;
		p2->rightBrother = p3;
		p3->state = (yyvsp[(3) - (3)]).state;
		p3->line = (yyvsp[(3) - (3)]).line;
		p3->firstChild = p3->rightBrother = NULL;
		p->productionRule = 2;
		push(p);					
	}
    break;

  case 21:
/* Line 1787 of yacc.c  */
#line 414 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *p3 = pop();
		TreeNode *p2 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *p1 = pop();
		p->state = "VarList";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = NULL;
		p1->rightBrother = p2;
		p2->state = (yyvsp[(2) - (3)]).state;
		p2->line = (yyvsp[(2) - (3)]).line;
		p2->firstChild = NULL;
		p2->rightBrother = p3;
		p->productionRule = 1;
		push(p);	
	}
    break;

  case 22:
/* Line 1787 of yacc.c  */
#line 431 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *p1 = pop();
		p->state = "VarList";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = NULL;
		p->productionRule = 2;
		push(p);
	}
    break;

  case 23:
/* Line 1787 of yacc.c  */
#line 443 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *p2 = pop();
		TreeNode *p1 = pop();
		p->state = "ParamDec";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = NULL;
		p1->rightBrother = p2;
		//p2->rightBrother = NULL;?不需要吗
		p->productionRule = 1;
		push(p);	
	}
    break;

  case 24:
/* Line 1787 of yacc.c  */
#line 457 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *op1 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *stmtlist = pop();
		TreeNode *deflist = pop();
		TreeNode *op2 = (TreeNode *)malloc(sizeof(TreeNode));
		op1->state = (yyvsp[(1) - (4)]).state;
		op1->line = (yyvsp[(1) - (4)]).line;
		op1->rightBrother = deflist;
		deflist->rightBrother = stmtlist;
		stmtlist->rightBrother = op2;
		op2->state = (yyvsp[(4) - (4)]).state;
		op2->line = (yyvsp[(4) - (4)]).line;
		op2->rightBrother = p->rightBrother = NULL;
		p->firstChild = op1;
		p->state = "CompSt";
		p->line = op1->line;
		
		p->productionRule = 1;
		push(p);	
	}
    break;

  case 25:
/* Line 1787 of yacc.c  */
#line 480 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *stmtlist = pop();
		TreeNode *stmt = pop();
		p->state = "StmtList";
		p->line = stmt->line;
		p->firstChild = stmt;
		p->rightBrother = stmtlist->rightBrother = NULL;
		stmt->rightBrother = stmtlist;
		p->productionRule = 1;
		push(p);	
	}
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 492 "syntax.y"
    {
		//empty
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		p->state = "empty";
		p->firstChild = p->rightBrother = NULL;
		p->productionRule = 2;
		push(p);	
	}
    break;

  case 27:
/* Line 1787 of yacc.c  */
#line 502 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *exp = pop();
		TreeNode *semi = (TreeNode *)malloc(sizeof(TreeNode));
		p->state = "Stmt";
		p->line = exp->line;
		p->firstChild = exp;
		p->rightBrother = semi->rightBrother = NULL;
		exp->rightBrother = semi;
		semi->state = (yyvsp[(2) - (2)]).state;
		semi->line = (yyvsp[(2) - (2)]).line;

		p->productionRule = 1;
		push(p);	
	}
    break;

  case 28:
/* Line 1787 of yacc.c  */
#line 517 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *compst = pop();
		p->state = "Stmt";
		p->line = compst->line;
		p->firstChild = compst;
		p->rightBrother = compst->rightBrother = NULL;

		p->productionRule = 2;
		push(p);				
	}
    break;

  case 29:
/* Line 1787 of yacc.c  */
#line 528 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *re = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *semi = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *exp = pop();
		re->line = (yyvsp[(1) - (3)]).line;
		re->state = (yyvsp[(1) - (3)]).state;
		re->rightBrother = exp;
		exp->rightBrother = semi;
		semi->line = (yyvsp[(3) - (3)]).line;
		semi->state = (yyvsp[(3) - (3)]).state;
		semi->rightBrother = p->rightBrother = NULL;
		p->firstChild = re;
		p->line = re->line;
		p->state = "Stmt";

		p->productionRule = 3;
		push(p);				
	}
    break;

  case 30:
/* Line 1787 of yacc.c  */
#line 547 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *IF = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *op1 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *op2 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *stmt = pop();
		TreeNode *exp = pop();
		IF->state = (yyvsp[(1) - (5)]).state;
		IF->line = (yyvsp[(1) - (5)]).line;
		IF->rightBrother = op1;
		op1->state = (yyvsp[(2) - (5)]).state;
		op1->line = (yyvsp[(2) - (5)]).line;
		op1->rightBrother = exp;
		exp->rightBrother = op2;
		op2->line = (yyvsp[(4) - (5)]).line;
		op2->state = (yyvsp[(4) - (5)]).state;
		op2->rightBrother = stmt;
		stmt->rightBrother = p->rightBrother = NULL;
		p->line = IF->line;
		p->state = "Stmt";
		p->firstChild = IF;

		p->productionRule = 4;
		push(p);				
	}
    break;

  case 31:
/* Line 1787 of yacc.c  */
#line 572 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *IF = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *op1 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *op2 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *ELSE = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *stmt2 = pop();
		TreeNode *stmt = pop();
		TreeNode *exp = pop();
		IF->state = (yyvsp[(1) - (7)]).state;
		IF->line = (yyvsp[(1) - (7)]).line;
		IF->firstChild = NULL;
		IF->rightBrother = op1;
		op1->state = (yyvsp[(2) - (7)]).state;
		op1->line = (yyvsp[(2) - (7)]).line;
		op1->firstChild = NULL;
		op1->rightBrother = exp;
		exp->rightBrother = op2;
		op2->state = (yyvsp[(4) - (7)]).state;
		op2->line = (yyvsp[(4) - (7)]).line;
		op2->firstChild = NULL;
		op2->rightBrother = stmt;
		stmt->rightBrother = ELSE;
		ELSE->state = (yyvsp[(6) - (7)]).state;
		ELSE->line = (yyvsp[(6) - (7)]).line;
		ELSE->firstChild = NULL;
		ELSE->rightBrother = stmt2;
		stmt2->rightBrother = p->rightBrother = NULL;
		p->state = "Stmt";
		p->line = IF->line;
		p->firstChild = IF;

		p->productionRule = 5;
		push(p);				
	}
    break;

  case 32:
/* Line 1787 of yacc.c  */
#line 607 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *WHILE = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *op1 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *op2 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *stmt = pop();
		TreeNode *exp = pop();
		WHILE->state = (yyvsp[(1) - (5)]).state;
		WHILE->line = (yyvsp[(1) - (5)]).line;
		WHILE->firstChild = NULL;
		WHILE->rightBrother = op1;
		op1->state = (yyvsp[(2) - (5)]).state;
		op1->line = (yyvsp[(2) - (5)]).line;
		op1->firstChild = NULL;
		op1->rightBrother = exp;
		exp->rightBrother = op2;
		op2->state = (yyvsp[(4) - (5)]).state;
		op2->line = (yyvsp[(4) - (5)]).line;
		op2->firstChild = NULL;
		op2->rightBrother = stmt;
		stmt->rightBrother = p->rightBrother = NULL;
		p->state = "Stmt";
		p->line = WHILE->line;
		p->firstChild = WHILE;

		p->productionRule = 6;
		push(p);				
	}
    break;

  case 33:
/* Line 1787 of yacc.c  */
#line 635 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *p1 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *p2 = (TreeNode *)malloc(sizeof(TreeNode));	
		p1->state = (yyvsp[(1) - (2)]).state;
		p1->line = (yyvsp[(1) - (2)]).line;
		p1->firstChild = NULL;
		p1->rightBrother = p2;
		p2->state = (yyvsp[(2) - (2)]).state;
		p2->line = (yyvsp[(2) - (2)]).line;
		p2->firstChild = NULL;
		p2->rightBrother = NULL;
		p->state = "Stmt";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = NULL;
		p->productionRule = 7;
		push(p);
	}
    break;

  case 34:
/* Line 1787 of yacc.c  */
#line 654 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *p1 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *p2 = (TreeNode *)malloc(sizeof(TreeNode));	
		p1->state = (yyvsp[(1) - (2)]).state;
		p1->line = (yyvsp[(1) - (2)]).line;
		p1->firstChild = NULL;
		p1->rightBrother = p2;
		p2->state = (yyvsp[(2) - (2)]).state;
		p2->line = (yyvsp[(2) - (2)]).line;
		p2->firstChild = NULL;
		p2->rightBrother = NULL;
		p->state = "Stmt";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = NULL;
		p->productionRule = 8;
		push(p);
	}
    break;

  case 35:
/* Line 1787 of yacc.c  */
#line 673 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *p1 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *p2 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *p9 = pop();
		TreeNode *p4 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *p7 = pop();
		TreeNode *p6 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *p5 = pop();
		TreeNode *p8 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *p3 = pop();
		p1->state = (yyvsp[(1) - (9)]).state;
		p1->line = (yyvsp[(1) - (9)]).line;
		p1->firstChild = NULL;
		p1->rightBrother = p2;
		p2->state = (yyvsp[(2) - (9)]).state;
		p2->line = (yyvsp[(2) - (9)]).line;
		p2->firstChild = NULL;
		p2->rightBrother = p3;
		p3->rightBrother = p4;
		p4->state = (yyvsp[(4) - (9)]).state;
		p4->line = (yyvsp[(4) - (9)]).line;
		p4->firstChild = NULL;
		p4->rightBrother = p5;
		p5->rightBrother = p6;
		p6->state = (yyvsp[(6) - (9)]).state;
		p6->line = (yyvsp[(6) - (9)]).line;
		p6->firstChild = NULL;
		p6->rightBrother = p7;
		p7->rightBrother = p8;
		p8->state = (yyvsp[(8) - (9)]).state;
		p8->line = (yyvsp[(8) - (9)]).line;
		p8->firstChild = NULL;
		p8->rightBrother = p9;
		p->state = "Stmt";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = NULL;
		p->productionRule = 9;
		push(p);
	}
    break;

  case 36:
/* Line 1787 of yacc.c  */
#line 716 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *deflist = pop();
		TreeNode *def = pop();
		p->state = "DefList";
		p->line = def->line;
		p->firstChild = def;
		p->rightBrother = deflist->rightBrother = NULL;
		def->rightBrother = deflist;

		p->productionRule = 1;
		push(p);	
	}
    break;

  case 37:
/* Line 1787 of yacc.c  */
#line 729 "syntax.y"
    {
		//empty
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		p->state = "empty";
		p->firstChild = p->rightBrother = NULL;

		p->productionRule = 2;
		push(p);				
	}
    break;

  case 38:
/* Line 1787 of yacc.c  */
#line 740 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *semi = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *declist = pop();
		TreeNode *specifier = pop();
		p->state = "Def";
		p->line = specifier->line;
		p->firstChild = specifier;
		p->rightBrother = semi->rightBrother = NULL;
		specifier->rightBrother = declist;
		declist->rightBrother = semi;
		semi->line = (yyvsp[(3) - (3)]).line;
		semi->state = (yyvsp[(3) - (3)]).state;
		semi->firstChild = NULL;
		p->productionRule = 1;
		push(p);	
	}
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 759 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *dec = pop();
		p->state = "DecList";
		p->line = dec->line;
		p->firstChild = dec;
		p->rightBrother = dec->rightBrother = NULL;

		p->productionRule = 1;
		push(p);	
	}
    break;

  case 40:
/* Line 1787 of yacc.c  */
#line 770 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *comma = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *declist = pop();
		TreeNode *dec = pop();
		p->state = "DecList";
		p->line = dec->line;
		p->firstChild = dec;
		p->rightBrother = declist->rightBrother = NULL;
		dec->rightBrother = comma;
		comma->line = (yyvsp[(2) - (3)]).line;
		comma->state = (yyvsp[(2) - (3)]).state;
		comma->firstChild = NULL;
		comma->rightBrother = declist;
		
		p->productionRule = 2;
		push(p);	
	}
    break;

  case 41:
/* Line 1787 of yacc.c  */
#line 790 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *vardec = pop();
		p->state =  "Dec";
		p->line = vardec->line;
		p->firstChild = vardec;
		vardec->rightBrother = p->rightBrother = NULL;

		p->productionRule = 1;
		push(p);	
	}
    break;

  case 42:
/* Line 1787 of yacc.c  */
#line 801 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		//TreeNode *vardec = pop();
		TreeNode *op = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *exp = pop();
		TreeNode *vardec = pop();
		vardec->rightBrother = op;
		op->state = (yyvsp[(2) - (3)]).state;
		op->line = (yyvsp[(2) - (3)]).line;
		op->rightBrother = exp;
		exp->rightBrother = p->rightBrother = NULL;
		p->state = "Dec";
		p->line = vardec->line;
		p->firstChild = vardec;

		p->productionRule = 2;
		push(p);				
	}
    break;

  case 43:
/* Line 1787 of yacc.c  */
#line 821 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *exp = pop();
		p->state = "OptExp";
		p->line = exp->line;
		p->firstChild = exp;
		p->rightBrother = NULL;
		p->productionRule = 1;
		push(p);
	}
    break;

  case 44:
/* Line 1787 of yacc.c  */
#line 831 "syntax.y"
    {//empty
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		p->state = "empty";
		p->firstChild = p->rightBrother = NULL;
		p->productionRule = 2;
		push(p);
	}
    break;

  case 45:
/* Line 1787 of yacc.c  */
#line 840 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *exp2 = pop();
		TreeNode *exp1 = pop();
		TreeNode *op = (TreeNode *)malloc(sizeof(TreeNode));
		op->state = (yyvsp[(2) - (3)]).state;
		op->line = (yyvsp[(2) - (3)]).line;
		op->firstChild = NULL;
		p->line = exp1->line;
		p->firstChild = exp1;
		p->state = "Exp";
		exp1->rightBrother = op;
		op->rightBrother = exp2;
		p->rightBrother = exp2->rightBrother = NULL;
		p->productionRule = 1;
		push(p);	
	}
    break;

  case 46:
/* Line 1787 of yacc.c  */
#line 857 "syntax.y"
    {	
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *exp2 = pop();
		TreeNode *exp1 = pop();
		TreeNode *op = (TreeNode *)malloc(sizeof(TreeNode));
		op->state = (yyvsp[(2) - (3)]).state;
		op->line = (yyvsp[(2) - (3)]).line;
		op->firstChild = NULL;
		p->line = exp1->line;
		p->firstChild = exp1;
		p->state = "Exp";
		exp1->rightBrother = op;
		op->rightBrother = exp2;
		p->rightBrother = exp2->rightBrother = NULL;

		p->productionRule = 2;
		push(p);		
	}
    break;

  case 47:
/* Line 1787 of yacc.c  */
#line 875 "syntax.y"
    {
		
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *exp2 = pop();
		TreeNode *exp1 = pop();
		TreeNode *op = (TreeNode *)malloc(sizeof(TreeNode));
		op->state = (yyvsp[(2) - (3)]).state;
		op->line = (yyvsp[(2) - (3)]).line;
		op->firstChild = NULL;
		p->line = exp1->line;
		p->firstChild = exp1;
		p->state = "Exp";
		exp1->rightBrother = op;
		op->rightBrother = exp2;
		p->rightBrother = exp2->rightBrother = NULL;

		p->productionRule = 3;
		push(p);	
	}
    break;

  case 48:
/* Line 1787 of yacc.c  */
#line 894 "syntax.y"
    {	
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *exp2 = pop();
		TreeNode *exp1 = pop();
		TreeNode *op = (TreeNode *)malloc(sizeof(TreeNode));
		op->state = (yyvsp[(2) - (3)]).state;
		op->line = (yyvsp[(2) - (3)]).line;
		op->firstChild = NULL;
		p->line = exp1->line;
		p->firstChild = exp1;
		p->state = "Exp";
		exp1->rightBrother = op;
		op->rightBrother = exp2;
		p->rightBrother = exp2->rightBrother = NULL;
		
		p->productionRule = 4;
		push(p);	
	}
    break;

  case 49:
/* Line 1787 of yacc.c  */
#line 912 "syntax.y"
    {
		
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *exp2 = pop();
		TreeNode *exp1 = pop();
		TreeNode *op = (TreeNode *)malloc(sizeof(TreeNode));
		op->state = (yyvsp[(2) - (3)]).state;
		op->line = (yyvsp[(2) - (3)]).line;
		op->firstChild = NULL;
		p->line = exp1->line;
		p->state = "Exp";
		p->firstChild = exp1;
		exp1->rightBrother = op;
		op->rightBrother = exp2;
		p->rightBrother = exp2->rightBrother = NULL;
		p->productionRule = 5;

		push(p);	
	}
    break;

  case 50:
/* Line 1787 of yacc.c  */
#line 931 "syntax.y"
    {
			
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *exp2 = pop();
		TreeNode *exp1 = pop();
		TreeNode *op = (TreeNode *)malloc(sizeof(TreeNode));
		op->state = (yyvsp[(2) - (3)]).state;
		op->line = (yyvsp[(2) - (3)]).line;
		op->firstChild = NULL;
		p->line = exp1->line;
		p->firstChild = exp1;
		p->state = "Exp";
		exp1->rightBrother = op;
		op->rightBrother = exp2;
		p->rightBrother = exp2->rightBrother = NULL;

		p->productionRule = 6;
		push(p);	
	}
    break;

  case 51:
/* Line 1787 of yacc.c  */
#line 950 "syntax.y"
    {
			
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *exp2 = pop();
		TreeNode *exp1 = pop();
		TreeNode *op = (TreeNode *)malloc(sizeof(TreeNode));
		op->state = (yyvsp[(2) - (3)]).state;
		op->line = (yyvsp[(2) - (3)]).line;
		op->firstChild = NULL;
		p->line = exp1->line;
		p->firstChild = exp1;
		p->state = "Exp";
		exp1->rightBrother = op;
		op->rightBrother = exp2;
		p->rightBrother = exp2->rightBrother = NULL;

		p->productionRule = 7;
		push(p);	
	}
    break;

  case 52:
/* Line 1787 of yacc.c  */
#line 969 "syntax.y"
    {
			
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *exp2 = pop();
		TreeNode *exp1 = pop();
		TreeNode *op = (TreeNode *)malloc(sizeof(TreeNode));
		op->state = (yyvsp[(2) - (3)]).state;
		op->line = (yyvsp[(2) - (3)]).line;
		op->firstChild = NULL;
		p->line = exp1->line;
		p->firstChild = exp1;
		p->state = "Exp";
		exp1->rightBrother = op;
		op->rightBrother = exp2;
		p->rightBrother = exp2->rightBrother = NULL;

		
		p->productionRule = 8;
		push(p);	
	}
    break;

  case 53:
/* Line 1787 of yacc.c  */
#line 989 "syntax.y"
    {
		
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *exp2 = pop();
		TreeNode *exp1 = pop();
		TreeNode *op = (TreeNode *)malloc(sizeof(TreeNode));
		op->state = (yyvsp[(2) - (3)]).state;
		op->line = (yyvsp[(2) - (3)]).line;
		op->firstChild = NULL;
		p->line = exp1->line;
		p->firstChild = exp1;
		p->state = "Exp";
		exp1->rightBrother = op;
		op->rightBrother = exp2;
		p->rightBrother = exp2->rightBrother = NULL;

		p->productionRule = 9;
		push(p);	
	}
    break;

  case 54:
/* Line 1787 of yacc.c  */
#line 1008 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *op = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *exp = pop();
		op->state = (yyvsp[(2) - (2)]).state;
		op->line = (yyvsp[(2) - (2)]).line;
		op->firstChild = NULL;
		p->line = exp->line;
		p->firstChild = op;
		p->state = "Exp";
		op->rightBrother = exp;
		exp->rightBrother = p->rightBrother = NULL;
		p->productionRule = 10;
		push(p);	
	}
    break;

  case 55:
/* Line 1787 of yacc.c  */
#line 1023 "syntax.y"
    {
			
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *op = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *exp = pop();
		op->state = (yyvsp[(2) - (2)]).state;
		op->line = (yyvsp[(2) - (2)]).line;
		op->firstChild = NULL;
		p->line = exp->line;
		p->firstChild = op;
		p->state = "Exp";
		op->rightBrother = exp;
		exp->rightBrother = p->rightBrother = NULL;
		p->productionRule = 11;
		push(p);	
	}
    break;

  case 56:
/* Line 1787 of yacc.c  */
#line 1039 "syntax.y"
    {

		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
		p->state = "Exp";
		TreeNode *id = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *op1 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *op2 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *args = pop();
		id->state = (yyvsp[(1) - (4)]).state;
		id->line = (yyvsp[(1) - (4)]).line;
		id->value = (yyvsp[(1) - (4)]).value;
		id->firstChild = op1->firstChild = op2->firstChild = NULL;
		id->rightBrother = op1;
		op1->state = (yyvsp[(2) - (4)]).state;
		op1->line = (yyvsp[(2) - (4)]).line;
		op1->rightBrother = args;
		args->rightBrother = op2;
		op2->state = (yyvsp[(4) - (4)]).state;
		op2->line = (yyvsp[(4) - (4)]).line;
		p->rightBrother = op2->rightBrother = NULL;
		p->firstChild = id;
		p->line = id->line;
		p->productionRule = 12;
		push(p);		
	}
    break;

  case 57:
/* Line 1787 of yacc.c  */
#line 1064 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		p->state = "Exp";
		TreeNode *id = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *op1 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *op2 = (TreeNode *)malloc(sizeof(TreeNode));
		id->state = (yyvsp[(1) - (3)]).state;
		id->line = (yyvsp[(1) - (3)]).line;
		id->value = (yyvsp[(1) - (3)]).value;
		id->firstChild = op1->firstChild = op2->firstChild = NULL;
		id->rightBrother = op1;
		op1->state = (yyvsp[(2) - (3)]).state;
		op1->line = (yyvsp[(2) - (3)]).line;
		op1->rightBrother = op2;
		op2->state = (yyvsp[(2) - (3)]).state;
		op2->line = (yyvsp[(2) - (3)]).line;
		op2->rightBrother = p->rightBrother = NULL;
		p->firstChild = id;
		p->line = id->line;

		p->productionRule = 13;
		push(p);	
	}
    break;

  case 58:
/* Line 1787 of yacc.c  */
#line 1087 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		p->state = "Exp";
		TreeNode *exp2 = pop();
		TreeNode *exp1 = pop();
		TreeNode *op1 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *op2 = (TreeNode *)malloc(sizeof(TreeNode));
		exp1->rightBrother = op1;
		op1->state = (yyvsp[(2) - (4)]).state;
		op1->line = (yyvsp[(2) - (4)]).line;
		op1->rightBrother = exp2;
		exp2->rightBrother = op2;
		op2->state = (yyvsp[(4) - (4)]).state;
		op2->line = (yyvsp[(4) - (4)]).line;
		op2->rightBrother = p->rightBrother = NULL;
		op2->firstChild = op1->firstChild = NULL;
		p->line = exp1->line;
		p->firstChild = exp1;

		p->productionRule = 14;
		push(p);	
	}
    break;

  case 59:
/* Line 1787 of yacc.c  */
#line 1109 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		p->state = "Exp";
		TreeNode *exp = pop();
		TreeNode *op = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *id = (TreeNode *)malloc(sizeof(TreeNode));
		exp->rightBrother = op;
		op->state = (yyvsp[(2) - (3)]).state;
		op->line = (yyvsp[(2) - (3)]).line;
		op->rightBrother = id;
		id->state = (yyvsp[(3) - (3)]).state;
		id->line = (yyvsp[(3) - (3)]).line;
		id->value = (yyvsp[(3) - (3)]).value;
		id->rightBrother = p->rightBrother = NULL;
		id->firstChild = op->firstChild = NULL;
		p->line = exp->line;
		p->firstChild = exp;
		
		p->productionRule = 15;
		push(p);	
	}
    break;

  case 60:
/* Line 1787 of yacc.c  */
#line 1130 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *temp = (TreeNode *)malloc(sizeof(TreeNode));
		temp->value = (yyvsp[(1) - (1)]).value;
		temp->state = (yyvsp[(1) - (1)]).state;
		temp->line = (yyvsp[(1) - (1)]).line;
		temp->firstChild = NULL;
		p->state = "Exp";
		p->line = temp->line;
		p->firstChild = temp;
		p->rightBrother = temp->rightBrother = NULL;
		//temp->line = 0;
		p->productionRule = 16;
		push(p);	
	}
    break;

  case 61:
/* Line 1787 of yacc.c  */
#line 1145 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *temp = (TreeNode *)malloc(sizeof(TreeNode));
		temp->value = (yyvsp[(1) - (1)]).value;
		temp->state = (yyvsp[(1) - (1)]).state;
		temp->line = (yyvsp[(1) - (1)]).line;
		temp->firstChild = NULL;
		p->state = "Exp";
		p->line = temp->line;
		p->firstChild = temp;
		p->rightBrother = temp->rightBrother = NULL;
		//temp->line = 0;
		p->productionRule = 17;
		push(p);
	}
    break;

  case 62:
/* Line 1787 of yacc.c  */
#line 1160 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *temp = (TreeNode *)malloc(sizeof(TreeNode));
		temp->value = (yyvsp[(1) - (1)]).value;
		temp->state = (yyvsp[(1) - (1)]).state;
		temp->line = (yyvsp[(1) - (1)]).line;
		temp->firstChild = NULL;
		p->state = "Exp";
		p->line = temp->line;
		p->firstChild = temp;
		p->rightBrother = temp->rightBrother = NULL;
		//temp->line = 0;
		p->productionRule = 18;
		push(p);	
	}
    break;

  case 63:
/* Line 1787 of yacc.c  */
#line 1177 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
		p->state = "Args";
		TreeNode *args = pop();
		TreeNode *comma = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *exp = pop();
		exp->rightBrother = comma;
		comma->state = (yyvsp[(2) - (3)]).state;
		comma->line = (yyvsp[(2) - (3)]).line;
		comma->rightBrother = args;
		comma->firstChild = NULL;
		args->rightBrother = p->rightBrother = NULL;
		p->line = exp->line;
		p->firstChild = exp;
		p->productionRule = 1;
		push(p);
	}
    break;

  case 64:
/* Line 1787 of yacc.c  */
#line 1194 "syntax.y"
    {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
		p->state = "Args";
		TreeNode *exp = pop();
		exp->rightBrother = p->rightBrother = NULL;
		p->line = exp->line;
		p->firstChild = exp;
		p->productionRule = 2;
		push(p);	
	}
    break;


/* Line 1787 of yacc.c  */
#line 2937 "syntax.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
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
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
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
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
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


/* Line 2050 of yacc.c  */
#line 1205 "syntax.y"


#include "lex.yy.c"

yyerror(char* msg) {
	printf("Error type 2 at line %d:syntax error near '%s'\n",yylineno,yytext);
}
















