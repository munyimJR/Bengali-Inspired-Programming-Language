
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>

void yyerror(const char *s);
int yylex(void);

extern int line_num;
extern FILE *yyin;
extern int keyword_count;
extern int identifier_count;
extern char *keywords[];
extern char *identifiers[];

// ডেটা টাইপ
typedef enum { TYPE_INT, TYPE_FLOAT, TYPE_STRING } VarType;

// সিম্বল টেবিল
typedef struct {
    char name[100];
    VarType type;
    union {
        int ival;
        double fval;
        char *sval;
    } value;
} Symbol;

Symbol symbol_table[1000];
int symbol_count = 0;

// AST নোড টাইপ
typedef enum {
    NODE_PROGRAM, NODE_STMT_LIST, NODE_DECLARATION, NODE_ASSIGNMENT,
    NODE_INCREMENT, NODE_DECREMENT, NODE_OUTPUT, NODE_INPUT,
    NODE_IF, NODE_WHILE, NODE_FOR, NODE_EXPRESSION, NODE_STRING_EXPR,
    NODE_CONDITION, NODE_INT_LITERAL, NODE_FLOAT_LITERAL, 
    NODE_STRING_LITERAL, NODE_IDENTIFIER, NODE_NEWLINE
} NodeType;

typedef struct ASTNode {
    NodeType type;
    union {
        int ival;
        double fval;
        char *sval;
    } value;
    VarType var_type;
    char op;
    struct ASTNode *left;
    struct ASTNode *right;
    struct ASTNode *next;
    struct ASTNode *condition;
    struct ASTNode *body;
    struct ASTNode *else_body;
    struct ASTNode *init;
    struct ASTNode *update;
} ASTNode;

ASTNode* create_node(NodeType type);
void execute_node(ASTNode *node);
void free_tree(ASTNode *node);
Symbol* lookup_symbol(const char *name);
Symbol* declare_symbol(const char *name, VarType type);
double eval_expression(ASTNode *node);
char* eval_string_expression(ASTNode *node);
int eval_condition(ASTNode *node);

// বাংলা সংখ্যা ASCII তে রূপান্তর
void convert_bangla_to_ascii(char *str) {
    unsigned char *p = (unsigned char *)str;
    char result[1000];
    int j = 0;
    while (*p) {
        if (p[0] == 0xE0 && p[1] == 0xA7 && p[2] >= 0xA6 && p[2] <= 0xAF) {
            result[j++] = '0' + (p[2] - 0xA6);
            p += 3;
        } else {
            result[j++] = *p++;
        }
    }
    result[j] = '\0';
    strcpy(str, result);
}

// পূর্ণসংখ্যা বাংলা সংখ্যায় প্রিন্ট
void print_bangla_number(int num) {
    char str[50];
    sprintf(str, "%d", num);
    
    const char* bangla_digits[] = {
        "০", "১", "২", "৩", "৪", 
        "৫", "৬", "৭", "৮", "৯"
    };
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            printf("%s", bangla_digits[str[i] - '0']);
        } else if (str[i] == '-') {
            printf("-");
        } else {
            printf("%c", str[i]);
        }
    }
}

// দশমিক সংখ্যা বাংলা সংখ্যায় প্রিন্ট
void print_bangla_float(double num) {
    char str[50];
    sprintf(str, "%g", num);
    
    const char* bangla_digits[] = {
        "০", "১", "২", "৩", "৪", 
        "৫", "৬", "৭", "৮", "৯"
    };
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            printf("%s", bangla_digits[str[i] - '0']);
        } else if (str[i] == '. ') {
            printf(".");
        } else if (str[i] == '-') {
            printf("-");
        } else if (str[i] == 'e' || str[i] == 'E') {
            printf("e");
        } else if (str[i] == '+') {
            printf("+");
        } else {
            printf("%c", str[i]);
        }
    }
}



/* Line 189 of yacc.c  */
#line 212 "parser.tab.c"

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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     SHURU = 258,
     SHESH = 259,
     PURNO = 260,
     VOGNO = 261,
     SHOBDO = 262,
     JODI = 263,
     NAHOLE = 264,
     JOTOKKHON = 265,
     JNY = 266,
     DEKHAO = 267,
     NAO = 268,
     NEWLINE_KW = 269,
     PLUS = 270,
     MINUS = 271,
     MULT = 272,
     DIV = 273,
     PLUS_ASSIGN = 274,
     MINUS_ASSIGN = 275,
     MULT_ASSIGN = 276,
     DIV_ASSIGN = 277,
     INCREMENT = 278,
     DECREMENT = 279,
     LT = 280,
     GT = 281,
     LE = 282,
     GE = 283,
     EQ = 284,
     NE = 285,
     AND = 286,
     OR = 287,
     ASSIGN = 288,
     LBRACE = 289,
     RBRACE = 290,
     LPAREN = 291,
     RPAREN = 292,
     SEMICOLON = 293,
     COMMA = 294,
     OUTPUT_OP = 295,
     INPUT_OP = 296,
     INT_LITERAL = 297,
     FLOAT_LITERAL = 298,
     STRING_LITERAL = 299,
     IDENTIFIER = 300,
     UMINUS = 301
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 139 "parser.y"

    int ival;
    double fval;
    char *sval;
    struct ASTNode *node;



/* Line 214 of yacc.c  */
#line 303 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 315 "parser.tab.c"

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

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   210

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  81
/* YYNRULES -- Number of states.  */
#define YYNSTATES  161

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   301

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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     7,     8,    11,    14,    17,    20,    23,
      26,    28,    30,    32,    34,    37,    40,    43,    45,    49,
      53,    59,    61,    65,    69,    75,    77,    81,    85,    91,
      95,    99,   103,   107,   111,   115,   118,   121,   124,   127,
     131,   133,   135,   137,   140,   143,   147,   155,   167,   177,
     185,   197,   198,   200,   205,   206,   208,   210,   214,   218,
     222,   226,   230,   234,   238,   242,   246,   248,   250,   254,
     258,   260,   264,   268,   270,   272,   274,   278,   281,   283,
     287,   289
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      48,     0,    -1,     3,    49,     4,    -1,    -1,    49,    50,
      -1,    51,    38,    -1,    55,    38,    -1,    56,    38,    -1,
      57,    38,    -1,    60,    38,    -1,    62,    -1,    63,    -1,
      64,    -1,    38,    -1,     5,    52,    -1,     6,    53,    -1,
       7,    54,    -1,    45,    -1,    45,    39,    52,    -1,    45,
      33,    69,    -1,    45,    33,    69,    39,    52,    -1,    45,
      -1,    45,    39,    53,    -1,    45,    33,    69,    -1,    45,
      33,    69,    39,    53,    -1,    45,    -1,    45,    39,    54,
      -1,    45,    33,    72,    -1,    45,    33,    72,    39,    54,
      -1,    45,    33,    69,    -1,    45,    33,    72,    -1,    45,
      19,    69,    -1,    45,    20,    69,    -1,    45,    21,    69,
      -1,    45,    22,    69,    -1,    45,    23,    -1,    45,    24,
      -1,    12,    58,    -1,    40,    59,    -1,    58,    40,    59,
      -1,    69,    -1,    72,    -1,    14,    -1,    13,    61,    -1,
      41,    45,    -1,    61,    41,    45,    -1,     8,    36,    67,
      37,    34,    49,    35,    -1,     8,    36,    67,    37,    34,
      49,    35,     9,    34,    49,    35,    -1,     8,    36,    67,
      37,    34,    49,    35,     9,    62,    -1,    10,    36,    67,
      37,    34,    49,    35,    -1,    11,    36,    65,    38,    67,
      38,    66,    37,    34,    49,    35,    -1,    -1,    55,    -1,
       5,    45,    33,    69,    -1,    -1,    55,    -1,    56,    -1,
      68,    25,    68,    -1,    68,    26,    68,    -1,    68,    27,
      68,    -1,    68,    28,    68,    -1,    68,    29,    68,    -1,
      68,    30,    68,    -1,    67,    31,    67,    -1,    67,    32,
      67,    -1,    36,    67,    37,    -1,    69,    -1,    70,    -1,
      69,    15,    70,    -1,    69,    16,    70,    -1,    71,    -1,
      70,    17,    71,    -1,    70,    18,    71,    -1,    42,    -1,
      43,    -1,    45,    -1,    36,    69,    37,    -1,    16,    71,
      -1,    73,    -1,    72,    15,    73,    -1,    44,    -1,    45,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   180,   180,   189,   190,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   215,   216,   217,   221,   225,   230,
     235,   244,   248,   253,   258,   267,   271,   276,   281,   290,
     296,   302,   308,   314,   320,   329,   333,   340,   344,   348,
     359,   360,   361,   365,   369,   373,   384,   390,   396,   405,
     413,   423,   424,   425,   434,   435,   436,   440,   446,   452,
     458,   464,   470,   476,   482,   488,   492,   496,   497,   503,
     512,   513,   519,   528,   532,   536,   541,   542,   550,   551,
     560,   564
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SHURU", "SHESH", "PURNO", "VOGNO",
  "SHOBDO", "JODI", "NAHOLE", "JOTOKKHON", "JNY", "DEKHAO", "NAO",
  "NEWLINE_KW", "PLUS", "MINUS", "MULT", "DIV", "PLUS_ASSIGN",
  "MINUS_ASSIGN", "MULT_ASSIGN", "DIV_ASSIGN", "INCREMENT", "DECREMENT",
  "LT", "GT", "LE", "GE", "EQ", "NE", "AND", "OR", "ASSIGN", "LBRACE",
  "RBRACE", "LPAREN", "RPAREN", "SEMICOLON", "COMMA", "OUTPUT_OP",
  "INPUT_OP", "INT_LITERAL", "FLOAT_LITERAL", "STRING_LITERAL",
  "IDENTIFIER", "UMINUS", "$accept", "program", "statement_list",
  "statement", "declaration", "decl_list_int", "decl_list_float",
  "decl_list_string", "assignment", "increment_decrement",
  "output_statement", "output_list", "output_item", "input_statement",
  "input_list", "if_statement", "while_statement", "for_statement",
  "for_init", "for_update", "condition", "arithmetic_expr", "expression",
  "term", "factor", "string_expression", "string_term", 0
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    47,    48,    49,    49,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    51,    51,    51,    52,    52,    52,
      52,    53,    53,    53,    53,    54,    54,    54,    54,    55,
      55,    55,    55,    55,    55,    56,    56,    57,    58,    58,
      59,    59,    59,    60,    61,    61,    62,    62,    62,    63,
      64,    65,    65,    65,    66,    66,    66,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    68,    69,    69,    69,
      70,    70,    70,    71,    71,    71,    71,    71,    72,    72,
      73,    73
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     0,     2,     2,     2,     2,     2,     2,
       1,     1,     1,     1,     2,     2,     2,     1,     3,     3,
       5,     1,     3,     3,     5,     1,     3,     3,     5,     3,
       3,     3,     3,     3,     3,     2,     2,     2,     2,     3,
       1,     1,     1,     2,     2,     3,     7,    11,     9,     7,
      11,     0,     1,     4,     0,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     1,     1,     3,     3,
       1,     3,     3,     1,     1,     1,     3,     2,     1,     3,
       1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     3,     0,     0,     1,     2,     0,     0,     0,     0,
       0,     0,     0,     0,    13,     0,     4,     0,     0,     0,
       0,     0,    10,    11,    12,    17,    14,    21,    15,    25,
      16,     0,     0,    51,     0,    37,     0,    43,     0,     0,
       0,     0,    35,    36,     0,     5,     6,     7,     8,     9,
       0,     0,     0,     0,     0,     0,     0,     0,    73,    74,
      75,     0,     0,    66,    67,    70,     0,     0,     0,    52,
       0,    42,     0,    80,    75,    38,    40,    41,    78,     0,
      44,     0,    31,    32,    33,    34,    29,    30,    19,    18,
      23,    22,    81,    27,    26,    77,     0,    66,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    39,    45,     0,     0,
       0,    65,    76,    63,    64,     3,    57,    58,    59,    60,
      61,    62,    68,    69,    71,    72,     3,     0,     0,    79,
      20,    24,    28,     0,     0,    53,    54,    46,    49,    55,
      56,     0,     0,     0,     3,    48,     3,     0,     0,    47,
      50
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    16,    17,    26,    28,    30,    18,    19,
      20,    35,    75,    21,    37,    22,    23,    24,    70,   151,
      61,    62,    63,    64,    65,    77,    78
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -109
static const yytype_int16 yypact[] =
{
      13,  -109,    19,    45,  -109,  -109,   -13,    21,    33,    84,
      85,    86,    71,    82,  -109,   155,  -109,    89,    92,   114,
     116,   119,  -109,  -109,  -109,   -12,  -109,    -3,  -109,    -2,
    -109,   108,   108,     0,    -1,   122,   118,   124,   113,   113,
     113,   113,  -109,  -109,    18,  -109,  -109,  -109,  -109,  -109,
     113,   -13,   113,    21,    -6,    33,   113,   108,  -109,  -109,
    -109,    40,   164,    94,    97,  -109,    42,   121,   163,  -109,
     129,  -109,   113,  -109,  -109,  -109,    94,   153,  -109,    -1,
    -109,   127,    94,    94,    94,    94,    94,   153,    65,  -109,
      69,  -109,  -109,    60,  -109,  -109,    75,   144,   108,   108,
     152,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   161,   136,   108,   144,    -6,  -109,  -109,   -13,    21,
      33,  -109,  -109,  -109,   156,  -109,  -109,  -109,  -109,  -109,
    -109,  -109,    97,    97,  -109,  -109,  -109,   113,    -9,  -109,
    -109,  -109,  -109,    81,    90,    94,   158,   195,  -109,  -109,
    -109,   168,    25,   172,  -109,  -109,  -109,   126,   135,  -109,
    -109
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -109,  -109,  -108,  -109,  -109,   -48,   -43,   -51,   -33,    61,
    -109,  -109,   130,  -109,  -109,    56,  -109,  -109,  -109,  -109,
     -31,    96,   -32,    10,   -45,   -30,    95
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      69,    66,    76,    89,    94,    67,    82,    83,    84,    85,
      91,    95,    86,    71,    87,    56,     1,   143,    88,     4,
      90,    50,    98,    99,    93,    97,    96,    51,   144,   146,
      52,    54,    25,     9,    56,    72,    53,    55,    73,    92,
     114,    58,    59,    73,    74,    68,   157,    76,   158,     5,
       6,     7,     8,     9,    72,    10,    11,    12,    13,   154,
      58,    59,    73,    74,   134,   135,    27,   123,   124,   142,
     140,    98,    99,    98,    99,   115,   141,   100,    29,   111,
     107,   108,   138,    14,   107,   108,     6,     7,     8,     9,
      15,    10,    11,    12,    13,     6,     7,     8,     9,   120,
      10,    11,    12,    13,   118,   145,    98,    99,   119,   107,
     108,    34,   121,   149,   109,   110,   147,   132,   133,    14,
      31,    32,    33,    36,    56,   148,    15,    45,    14,    56,
      46,     6,     7,     8,     9,    15,    10,    11,    12,    13,
       6,     7,     8,     9,    57,    10,    11,    12,    13,    72,
      58,    59,    47,    60,    48,    58,    59,    49,    60,   107,
     108,   159,    79,    80,    14,    81,   112,   113,   115,   137,
     160,    15,   117,    14,    38,    39,    40,    41,    42,    43,
      15,   122,    38,    39,    40,    41,   125,    98,    44,   101,
     102,   103,   104,   105,   106,   136,    44,   126,   127,   128,
     129,   130,   131,    15,   152,   153,   156,   150,   155,   116,
     139
};

static const yytype_uint8 yycheck[] =
{
      33,    32,    34,    51,    55,     5,    38,    39,    40,    41,
      53,    56,    44,    14,    44,    16,     3,   125,    50,     0,
      52,    33,    31,    32,    54,    57,    57,    39,   136,    38,
      33,    33,    45,     8,    16,    36,    39,    39,    44,    45,
      72,    42,    43,    44,    45,    45,   154,    79,   156,     4,
       5,     6,     7,     8,    36,    10,    11,    12,    13,    34,
      42,    43,    44,    45,   109,   110,    45,    98,    99,   120,
     118,    31,    32,    31,    32,    15,   119,    37,    45,    37,
      15,    16,   113,    38,    15,    16,     5,     6,     7,     8,
      45,    10,    11,    12,    13,     5,     6,     7,     8,    39,
      10,    11,    12,    13,    39,   137,    31,    32,    39,    15,
      16,    40,    37,   146,    17,    18,    35,   107,   108,    38,
      36,    36,    36,    41,    16,    35,    45,    38,    38,    16,
      38,     5,     6,     7,     8,    45,    10,    11,    12,    13,
       5,     6,     7,     8,    36,    10,    11,    12,    13,    36,
      42,    43,    38,    45,    38,    42,    43,    38,    45,    15,
      16,    35,    40,    45,    38,    41,    45,    38,    15,    33,
      35,    45,    45,    38,    19,    20,    21,    22,    23,    24,
      45,    37,    19,    20,    21,    22,    34,    31,    33,    25,
      26,    27,    28,    29,    30,    34,    33,   101,   102,   103,
     104,   105,   106,    45,     9,    37,    34,   146,   152,    79,
     115
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    48,    49,     0,     4,     5,     6,     7,     8,
      10,    11,    12,    13,    38,    45,    50,    51,    55,    56,
      57,    60,    62,    63,    64,    45,    52,    45,    53,    45,
      54,    36,    36,    36,    40,    58,    41,    61,    19,    20,
      21,    22,    23,    24,    33,    38,    38,    38,    38,    38,
      33,    39,    33,    39,    33,    39,    16,    36,    42,    43,
      45,    67,    68,    69,    70,    71,    67,     5,    45,    55,
      65,    14,    36,    44,    45,    59,    69,    72,    73,    40,
      45,    41,    69,    69,    69,    69,    69,    72,    69,    52,
      69,    53,    45,    72,    54,    71,    67,    69,    31,    32,
      37,    25,    26,    27,    28,    29,    30,    15,    16,    17,
      18,    37,    45,    38,    69,    15,    59,    45,    39,    39,
      39,    37,    37,    67,    67,    34,    68,    68,    68,    68,
      68,    68,    70,    70,    71,    71,    34,    33,    67,    73,
      52,    53,    54,    49,    49,    69,    38,    35,    35,    55,
      56,    66,     9,    37,    34,    62,    34,    49,    49,    35,
      35
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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

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
  if (yyn == YYPACT_NINF)
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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

/* Line 1455 of yacc.c  */
#line 180 "parser.y"
    {
        (yyval.node) = (yyvsp[(2) - (3)].node);
        execute_node((yyval.node));
        printf("\n[প্রোগ্রাম সফলভাবে সম্পন্ন হয়েছে]\n");
        free_tree((yyval.node));
    ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 189 "parser.y"
    { (yyval.node) = NULL; ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 190 "parser.y"
    {
        if ((yyvsp[(1) - (2)].node) == NULL) {
            (yyval.node) = (yyvsp[(2) - (2)].node);
        } else {
            ASTNode *temp = (yyvsp[(1) - (2)].node);
            while (temp->next != NULL) temp = temp->next;
            temp->next = (yyvsp[(2) - (2)].node);
            (yyval.node) = (yyvsp[(1) - (2)].node);
        }
    ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 203 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].node); ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 204 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].node); ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 205 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].node); ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 206 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].node); ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 207 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].node); ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 208 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 209 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 210 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 211 "parser.y"
    { (yyval.node) = NULL; ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 215 "parser.y"
    { (yyval.node) = (yyvsp[(2) - (2)].node); (yyval.node)->var_type = TYPE_INT; ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 216 "parser.y"
    { (yyval.node) = (yyvsp[(2) - (2)].node); (yyval.node)->var_type = TYPE_FLOAT; ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 217 "parser.y"
    { (yyval.node) = (yyvsp[(2) - (2)].node); (yyval.node)->var_type = TYPE_STRING; ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 221 "parser.y"
    {
        (yyval.node) = create_node(NODE_DECLARATION);
        (yyval.node)->value.sval = (yyvsp[(1) - (1)].sval);
    ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 225 "parser.y"
    {
        (yyval.node) = create_node(NODE_DECLARATION);
        (yyval.node)->value.sval = (yyvsp[(1) - (3)].sval);
        (yyval.node)->next = (yyvsp[(3) - (3)].node);
    ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 230 "parser.y"
    {
        (yyval.node) = create_node(NODE_DECLARATION);
        (yyval.node)->value.sval = (yyvsp[(1) - (3)].sval);
        (yyval.node)->right = (yyvsp[(3) - (3)].node);
    ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 235 "parser.y"
    {
        (yyval.node) = create_node(NODE_DECLARATION);
        (yyval.node)->value.sval = (yyvsp[(1) - (5)].sval);
        (yyval.node)->right = (yyvsp[(3) - (5)].node);
        (yyval.node)->next = (yyvsp[(5) - (5)].node);
    ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 244 "parser.y"
    {
        (yyval.node) = create_node(NODE_DECLARATION);
        (yyval.node)->value.sval = (yyvsp[(1) - (1)].sval);
    ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 248 "parser.y"
    {
        (yyval.node) = create_node(NODE_DECLARATION);
        (yyval.node)->value.sval = (yyvsp[(1) - (3)].sval);
        (yyval.node)->next = (yyvsp[(3) - (3)].node);
    ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 253 "parser.y"
    {
        (yyval.node) = create_node(NODE_DECLARATION);
        (yyval.node)->value.sval = (yyvsp[(1) - (3)].sval);
        (yyval.node)->right = (yyvsp[(3) - (3)].node);
    ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 258 "parser.y"
    {
        (yyval.node) = create_node(NODE_DECLARATION);
        (yyval.node)->value.sval = (yyvsp[(1) - (5)].sval);
        (yyval.node)->right = (yyvsp[(3) - (5)].node);
        (yyval.node)->next = (yyvsp[(5) - (5)].node);
    ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 267 "parser.y"
    {
        (yyval.node) = create_node(NODE_DECLARATION);
        (yyval.node)->value.sval = (yyvsp[(1) - (1)].sval);
    ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 271 "parser.y"
    {
        (yyval.node) = create_node(NODE_DECLARATION);
        (yyval.node)->value.sval = (yyvsp[(1) - (3)].sval);
        (yyval.node)->next = (yyvsp[(3) - (3)].node);
    ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 276 "parser.y"
    {
        (yyval.node) = create_node(NODE_DECLARATION);
        (yyval.node)->value.sval = (yyvsp[(1) - (3)].sval);
        (yyval.node)->right = (yyvsp[(3) - (3)].node);
    ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 281 "parser.y"
    {
        (yyval.node) = create_node(NODE_DECLARATION);
        (yyval.node)->value.sval = (yyvsp[(1) - (5)].sval);
        (yyval.node)->right = (yyvsp[(3) - (5)].node);
        (yyval.node)->next = (yyvsp[(5) - (5)].node);
    ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 290 "parser.y"
    {
        (yyval.node) = create_node(NODE_ASSIGNMENT);
        (yyval.node)->value.sval = (yyvsp[(1) - (3)].sval);
        (yyval.node)->op = '=';
        (yyval.node)->right = (yyvsp[(3) - (3)].node);
    ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 296 "parser.y"
    {
        (yyval.node) = create_node(NODE_ASSIGNMENT);
        (yyval.node)->value.sval = (yyvsp[(1) - (3)].sval);
        (yyval.node)->op = '=';
        (yyval.node)->right = (yyvsp[(3) - (3)].node);
    ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 302 "parser.y"
    {
        (yyval.node) = create_node(NODE_ASSIGNMENT);
        (yyval.node)->value.sval = (yyvsp[(1) - (3)].sval);
        (yyval.node)->op = '+';
        (yyval.node)->right = (yyvsp[(3) - (3)].node);
    ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 308 "parser.y"
    {
        (yyval.node) = create_node(NODE_ASSIGNMENT);
        (yyval.node)->value.sval = (yyvsp[(1) - (3)].sval);
        (yyval.node)->op = '-';
        (yyval.node)->right = (yyvsp[(3) - (3)].node);
    ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 314 "parser.y"
    {
        (yyval.node) = create_node(NODE_ASSIGNMENT);
        (yyval.node)->value.sval = (yyvsp[(1) - (3)].sval);
        (yyval.node)->op = '*';
        (yyval.node)->right = (yyvsp[(3) - (3)].node);
    ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 320 "parser.y"
    {
        (yyval.node) = create_node(NODE_ASSIGNMENT);
        (yyval.node)->value.sval = (yyvsp[(1) - (3)].sval);
        (yyval.node)->op = '/';
        (yyval.node)->right = (yyvsp[(3) - (3)].node);
    ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 329 "parser.y"
    {
        (yyval.node) = create_node(NODE_INCREMENT);
        (yyval.node)->value.sval = (yyvsp[(1) - (2)].sval);
    ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 333 "parser.y"
    {
        (yyval.node) = create_node(NODE_DECREMENT);
        (yyval.node)->value.sval = (yyvsp[(1) - (2)].sval);
    ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 340 "parser.y"
    { (yyval.node) = (yyvsp[(2) - (2)].node); ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 344 "parser.y"
    {
        (yyval.node) = create_node(NODE_OUTPUT);
        (yyval.node)->left = (yyvsp[(2) - (2)].node);
    ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 348 "parser.y"
    {
        ASTNode *temp = (yyvsp[(1) - (3)].node);
        while (temp->next != NULL) temp = temp->next;
        ASTNode *new_output = create_node(NODE_OUTPUT);
        new_output->left = (yyvsp[(3) - (3)].node);
        temp->next = new_output;
        (yyval.node) = (yyvsp[(1) - (3)].node);
    ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 359 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 360 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 361 "parser.y"
    { (yyval.node) = create_node(NODE_NEWLINE); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 365 "parser.y"
    { (yyval.node) = (yyvsp[(2) - (2)].node); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 369 "parser.y"
    {
        (yyval.node) = create_node(NODE_INPUT);
        (yyval.node)->value.sval = (yyvsp[(2) - (2)].sval);
    ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 373 "parser.y"
    {
        ASTNode *temp = (yyvsp[(1) - (3)].node);
        while (temp->next != NULL) temp = temp->next;
        ASTNode *new_input = create_node(NODE_INPUT);
        new_input->value.sval = (yyvsp[(3) - (3)].sval);
        temp->next = new_input;
        (yyval.node) = (yyvsp[(1) - (3)].node);
    ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 384 "parser.y"
    {
        (yyval.node) = create_node(NODE_IF);
        (yyval.node)->condition = (yyvsp[(3) - (7)].node);
        (yyval.node)->body = (yyvsp[(6) - (7)].node);
        (yyval.node)->else_body = NULL;
    ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 390 "parser.y"
    {
        (yyval.node) = create_node(NODE_IF);
        (yyval.node)->condition = (yyvsp[(3) - (11)].node);
        (yyval.node)->body = (yyvsp[(6) - (11)].node);
        (yyval.node)->else_body = (yyvsp[(10) - (11)].node);
    ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 396 "parser.y"
    {
        (yyval.node) = create_node(NODE_IF);
        (yyval.node)->condition = (yyvsp[(3) - (9)].node);
        (yyval.node)->body = (yyvsp[(6) - (9)].node);
        (yyval.node)->else_body = (yyvsp[(9) - (9)].node);
    ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 405 "parser.y"
    {
        (yyval.node) = create_node(NODE_WHILE);
        (yyval.node)->condition = (yyvsp[(3) - (7)].node);
        (yyval.node)->body = (yyvsp[(6) - (7)].node);
    ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 413 "parser.y"
    {
        (yyval.node) = create_node(NODE_FOR);
        (yyval.node)->init = (yyvsp[(3) - (11)].node);
        (yyval.node)->condition = (yyvsp[(5) - (11)].node);
        (yyval.node)->update = (yyvsp[(7) - (11)].node);
        (yyval.node)->body = (yyvsp[(10) - (11)].node);
    ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 423 "parser.y"
    { (yyval.node) = NULL; ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 424 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 425 "parser.y"
    {
        (yyval.node) = create_node(NODE_DECLARATION);
        (yyval.node)->value.sval = (yyvsp[(2) - (4)].sval);
        (yyval.node)->var_type = TYPE_INT;
        (yyval.node)->right = (yyvsp[(4) - (4)].node);
    ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 434 "parser.y"
    { (yyval.node) = NULL; ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 435 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 436 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 440 "parser.y"
    {
        (yyval.node) = create_node(NODE_CONDITION);
        (yyval.node)->op = '<';
        (yyval.node)->left = (yyvsp[(1) - (3)].node);
        (yyval.node)->right = (yyvsp[(3) - (3)].node);
    ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 446 "parser.y"
    {
        (yyval.node) = create_node(NODE_CONDITION);
        (yyval.node)->op = '>';
        (yyval.node)->left = (yyvsp[(1) - (3)].node);
        (yyval.node)->right = (yyvsp[(3) - (3)].node);
    ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 452 "parser.y"
    {
        (yyval.node) = create_node(NODE_CONDITION);
        (yyval.node)->op = 'l';
        (yyval.node)->left = (yyvsp[(1) - (3)].node);
        (yyval.node)->right = (yyvsp[(3) - (3)].node);
    ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 458 "parser.y"
    {
        (yyval.node) = create_node(NODE_CONDITION);
        (yyval.node)->op = 'g';
        (yyval.node)->left = (yyvsp[(1) - (3)].node);
        (yyval.node)->right = (yyvsp[(3) - (3)].node);
    ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 464 "parser.y"
    {
        (yyval.node) = create_node(NODE_CONDITION);
        (yyval.node)->op = 'e';
        (yyval.node)->left = (yyvsp[(1) - (3)].node);
        (yyval.node)->right = (yyvsp[(3) - (3)].node);
    ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 470 "parser.y"
    {
        (yyval.node) = create_node(NODE_CONDITION);
        (yyval.node)->op = 'n';
        (yyval.node)->left = (yyvsp[(1) - (3)].node);
        (yyval.node)->right = (yyvsp[(3) - (3)].node);
    ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 476 "parser.y"
    {
        (yyval.node) = create_node(NODE_CONDITION);
        (yyval.node)->op = '&';
        (yyval.node)->left = (yyvsp[(1) - (3)].node);
        (yyval.node)->right = (yyvsp[(3) - (3)].node);
    ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 482 "parser.y"
    {
        (yyval.node) = create_node(NODE_CONDITION);
        (yyval.node)->op = '|';
        (yyval.node)->left = (yyvsp[(1) - (3)].node);
        (yyval.node)->right = (yyvsp[(3) - (3)].node);
    ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 488 "parser.y"
    { (yyval.node) = (yyvsp[(2) - (3)].node); ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 492 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 496 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 497 "parser.y"
    {
        (yyval.node) = create_node(NODE_EXPRESSION);
        (yyval.node)->op = '+';
        (yyval.node)->left = (yyvsp[(1) - (3)].node);
        (yyval.node)->right = (yyvsp[(3) - (3)].node);
    ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 503 "parser.y"
    {
        (yyval.node) = create_node(NODE_EXPRESSION);
        (yyval.node)->op = '-';
        (yyval.node)->left = (yyvsp[(1) - (3)].node);
        (yyval.node)->right = (yyvsp[(3) - (3)].node);
    ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 512 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 513 "parser.y"
    {
        (yyval.node) = create_node(NODE_EXPRESSION);
        (yyval.node)->op = '*';
        (yyval.node)->left = (yyvsp[(1) - (3)].node);
        (yyval.node)->right = (yyvsp[(3) - (3)].node);
    ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 519 "parser.y"
    {
        (yyval.node) = create_node(NODE_EXPRESSION);
        (yyval.node)->op = '/';
        (yyval.node)->left = (yyvsp[(1) - (3)].node);
        (yyval.node)->right = (yyvsp[(3) - (3)].node);
    ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 528 "parser.y"
    {
        (yyval.node) = create_node(NODE_INT_LITERAL);
        (yyval.node)->value.ival = (yyvsp[(1) - (1)].ival);
    ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 532 "parser.y"
    {
        (yyval.node) = create_node(NODE_FLOAT_LITERAL);
        (yyval.node)->value.fval = (yyvsp[(1) - (1)].fval);
    ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 536 "parser.y"
    {
        (yyval.node) = create_node(NODE_IDENTIFIER);
        (yyval.node)->value.sval = strdup((yyvsp[(1) - (1)].sval));
        free((yyvsp[(1) - (1)].sval));
    ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 541 "parser.y"
    { (yyval.node) = (yyvsp[(2) - (3)].node); ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 542 "parser.y"
    {
        (yyval.node) = create_node(NODE_EXPRESSION);
        (yyval.node)->op = 'u';
        (yyval.node)->right = (yyvsp[(2) - (2)].node);
    ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 550 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 551 "parser.y"
    {
        (yyval.node) = create_node(NODE_STRING_EXPR);
        (yyval.node)->op = '+';
        (yyval.node)->left = (yyvsp[(1) - (3)].node);
        (yyval.node)->right = (yyvsp[(3) - (3)].node);
    ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 560 "parser.y"
    {
        (yyval.node) = create_node(NODE_STRING_LITERAL);
        (yyval.node)->value.sval = (yyvsp[(1) - (1)].sval);
    ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 564 "parser.y"
    {
        (yyval.node) = create_node(NODE_IDENTIFIER);
        (yyval.node)->value.sval = strdup((yyvsp[(1) - (1)].sval));
        free((yyvsp[(1) - (1)].sval));
    ;}
    break;



/* Line 1455 of yacc.c  */
#line 2462 "parser.tab.c"
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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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



/* Line 1675 of yacc.c  */
#line 571 "parser.y"


// AST নোড তৈরি
ASTNode* create_node(NodeType type) {
    ASTNode *node = (ASTNode*)calloc(1, sizeof(ASTNode));
    node->type = type;
    return node;
}

// নোড এক্সিকিউট
void execute_node(ASTNode *node) {
    if (node == NULL) return;
    
    switch (node->type) {
        case NODE_DECLARATION: {
            Symbol *sym = declare_symbol(node->value.sval, node->var_type);
            if (node->right) {
                if (node->var_type == TYPE_STRING) {
                    sym->value.sval = eval_string_expression(node->right);
                } else {
                    double val = eval_expression(node->right);
                    if (node->var_type == TYPE_INT) {
                        sym->value.ival = (int)val;
                    } else {
                        sym->value.fval = val;
                    }
                }
            }
            break;
        }
        case NODE_ASSIGNMENT: {
            Symbol *sym = lookup_symbol(node->value.sval);
            if (sym) {
                if (sym->type == TYPE_STRING && node->right->type == NODE_STRING_LITERAL) {
                    if (sym->value.sval) free(sym->value.sval);
                    sym->value.sval = eval_string_expression(node->right);
                } else if (sym->type == TYPE_STRING) {
                    if (sym->value.sval) free(sym->value.sval);
                    sym->value.sval = eval_string_expression(node->right);
                } else {
                    double val = eval_expression(node->right);
                    if (node->op == '=') {
                        if (sym->type == TYPE_INT) sym->value.ival = (int)val;
                        else sym->value.fval = val;
                    } else if (node->op == '+') {
                        if (sym->type == TYPE_INT) sym->value.ival += (int)val;
                        else sym->value.fval += val;
                    } else if (node->op == '-') {
                        if (sym->type == TYPE_INT) sym->value.ival -= (int)val;
                        else sym->value.fval -= val;
                    } else if (node->op == '*') {
                        if (sym->type == TYPE_INT) sym->value.ival *= (int)val;
                        else sym->value.fval *= val;
                    } else if (node->op == '/') {
                        if (sym->type == TYPE_INT) sym->value.ival /= (int)val;
                        else sym->value.fval /= val;
                    }
                }
            }
            break;
        }
        case NODE_INCREMENT: {
            Symbol *sym = lookup_symbol(node->value.sval);
            if (sym) {
                if (sym->type == TYPE_INT) sym->value.ival++;
                else sym->value.fval++;
            }
            break;
        }
        case NODE_DECREMENT: {
            Symbol *sym = lookup_symbol(node->value.sval);
            if (sym) {
                if (sym->type == TYPE_INT) sym->value.ival--;
                else sym->value.fval--;
            }
            break;
        }
        case NODE_OUTPUT: {
            if (node->left) {
                if (node->left->type == NODE_NEWLINE) {
                    printf("\n");
                } else if (node->left->type == NODE_STRING_LITERAL || 
                           node->left->type == NODE_STRING_EXPR ||
                           (node->left->type == NODE_IDENTIFIER && 
                            lookup_symbol(node->left->value.sval) &&
                            lookup_symbol(node->left->value.sval)->type == TYPE_STRING)) {
                    char *str = eval_string_expression(node->left);
                    printf("%s", str);
                    free(str);
                } else {
                    double val = eval_expression(node->left);
                    if (fmod(val, 1.0) == 0) {
                        print_bangla_number((int)val);
                    } else {
                        print_bangla_float(val);
                    }
                }
            }
            break;
        }
        case NODE_INPUT: {
            Symbol *sym = lookup_symbol(node->value.sval);
            if (sym) {
                if (sym->type == TYPE_INT) {
                    char buffer[100];
                    if(scanf("%99s", buffer) == 1) {
                        convert_bangla_to_ascii(buffer);
                        sym->value.ival = atoi(buffer);
                    }
                } else if (sym->type == TYPE_FLOAT) {
                    char buffer[100];
                    if(scanf("%99s", buffer) == 1) {
                        convert_bangla_to_ascii(buffer);
                        sym->value.fval = atof(buffer);
                    }
                } else if (sym->type == TYPE_STRING) {
                    char buffer[1000];
                    if(fgets(buffer, sizeof(buffer), stdin)) {
                        size_t len = strlen(buffer);
                        if (len > 0 && buffer[len-1] == '\n') {
                            buffer[len-1] = '\0';
                        }
                        if (sym->value.sval) free(sym->value.sval);
                        sym->value.sval = strdup(buffer);
                    }
                }
            }
            break;
        }
        case NODE_IF: {
            if (eval_condition(node->condition)) {
                execute_node(node->body);
            } else if (node->else_body) {
                execute_node(node->else_body);
            }
            break;
        }
        case NODE_WHILE: {
            while (eval_condition(node->condition)) {
                execute_node(node->body);
            }
            break;
        }
        case NODE_FOR: {
            if (node->init) execute_node(node->init);
            while (eval_condition(node->condition)) {
                execute_node(node->body);
                if (node->update) execute_node(node->update);
            }
            break;
        }
    }
    
    if (node->next) execute_node(node->next);
}

double eval_expression(ASTNode *node) {
    if (node == NULL) return 0;
    
    switch (node->type) {
        case NODE_INT_LITERAL:
            return (double)node->value.ival;
        case NODE_FLOAT_LITERAL:
            return node->value.fval;
        case NODE_IDENTIFIER: {
            Symbol *sym = lookup_symbol(node->value.sval);
            if (sym->type == TYPE_INT) return (double)sym->value.ival;
            if (sym->type == TYPE_FLOAT) return sym->value.fval;
            return 0;
        }
        case NODE_EXPRESSION: {
            double left = node->left ? eval_expression(node->left) : 0;
            double right = eval_expression(node->right);
            switch (node->op) {
                case '+': return left + right;
                case '-': return left - right;
                case '*': return left * right;
                case '/': return right != 0 ? left / right : 0;
                case 'u': return -right;
            }
        }
    }
    return 0;
}

char* eval_string_expression(ASTNode *node) {
    if (node == NULL) return strdup("");
    
    switch (node->type) {
        case NODE_STRING_LITERAL:
            return strdup(node->value.sval);
        case NODE_IDENTIFIER: {
            Symbol *sym = lookup_symbol(node->value.sval);
            if (sym && sym->type == TYPE_STRING) {
                return strdup(sym->value.sval);
            }
            return strdup("");
        }
        case NODE_STRING_EXPR: {
            char *left = eval_string_expression(node->left);
            char *right = eval_string_expression(node->right);
            char *result = malloc(strlen(left) + strlen(right) + 1);
            strcpy(result, left);
            strcat(result, right);
            free(left);
            free(right);
            return result;
        }
    }
    return strdup("");
}

int eval_condition(ASTNode *node) {
    if (node == NULL) return 1;
    
    double left = eval_expression(node->left);
    double right = eval_expression(node->right);
    
    switch (node->op) {
        case '<': return left < right;
        case '>': return left > right;
        case 'l': return left <= right;
        case 'g': return left >= right;
        case 'e': return left == right;
        case 'n': return left != right;
        case '&': return eval_condition(node->left) && eval_condition(node->right);
        case '|': return eval_condition(node->left) || eval_condition(node->right);
    }
    return 0;
}

void free_tree(ASTNode *node) {
    if (node == NULL) return;
    free_tree(node->left);
    free_tree(node->right);
    free_tree(node->next);
    free_tree(node->condition);
    free_tree(node->body);
    free_tree(node->else_body);
    free_tree(node->init);
    free_tree(node->update);
    if (node->value.sval && (node->type == NODE_STRING_LITERAL || 
        node->type == NODE_IDENTIFIER || node->type == NODE_DECLARATION ||
        node->type == NODE_ASSIGNMENT || node->type == NODE_INPUT ||
        node->type == NODE_INCREMENT || node->type == NODE_DECREMENT)) {
        free(node->value.sval);
    }
    free(node);
}

void yyerror(const char *s) {
    fprintf(stderr, "Error at line %d: %s\n", line_num, s);
}

// সিম্বল লুকআপ
Symbol* lookup_symbol(const char *name) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i].name, name) == 0) {
            return &symbol_table[i];
        }
    }
    fprintf(stderr, "Error: Undeclared variable '%s'\n", name);
    exit(1);
}

// সিম্বল ঘোষণা
Symbol* declare_symbol(const char *name, VarType type) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i].name, name) == 0) {
            fprintf(stderr, "Error: Variable '%s' already declared\n", name);
            exit(1);
        }
    }
    
    if (symbol_count >= 1000) {
        fprintf(stderr, "Error: Symbol table full\n");
        exit(1);
    }
    
    Symbol *sym = &symbol_table[symbol_count++];
    strcpy(sym->name, name);
    sym->type = type;
    
    if (type == TYPE_INT) sym->value.ival = 0;
    else if (type == TYPE_FLOAT) sym->value.fval = 0.0;
    else if (type == TYPE_STRING) sym->value.sval = strdup("");
    
    return sym;
}

int main(int argc, char **argv) {
    setlocale(LC_ALL, "en_US.UTF-8");
    
    keyword_count = 0;
    identifier_count = 0;
    
    printf("=== বাংলা প্রোগ্রামিং ভাষা কম্পাইলার ===\n\n");
    
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            fprintf(stderr, "Error: Cannot open file '%s'\n", argv[1]);
            return 1;
        }
    } else {
        yyin = fopen("code.txt", "r");
        if (!yyin) {
            fprintf(stderr, "Error: Cannot open 'code.txt'\n");
            return 1;
        }
    }
    
    yyparse();
    fclose(yyin);
    
    fprintf(stderr, "\n[STATS]KEYWORDS:%d,IDENTIFIERS:%d[/STATS]\n", keyword_count, identifier_count);
    
    for (int i = 0; i < keyword_count; i++) {
        free(keywords[i]);
    }
    for (int i = 0; i < identifier_count; i++) {
        free(identifiers[i]);
    }
    
    return 0;
}
