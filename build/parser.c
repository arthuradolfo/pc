/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */

#line 67 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
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
   by #include "parser.h".  */
#ifndef YY_YY_HOME_ARTHUR_REA_DE_TRABALHO_PC_BUILD_PARSER_H_INCLUDED
# define YY_YY_HOME_ARTHUR_REA_DE_TRABALHO_PC_BUILD_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 5 "parser.y" /* yacc.c:355  */

#include "parser.h" //arquivo automaticamente gerado pelo bison
#include "main.h"
#include "cc_misc.h" //arquivo com funcoes de auto incremento
#include "cc_ast_node.h"

#line 104 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:355  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TK_PR_INT = 258,
    TK_PR_FLOAT = 259,
    TK_PR_BOOL = 260,
    TK_PR_CHAR = 261,
    TK_PR_STRING = 262,
    TK_PR_IF = 263,
    TK_PR_THEN = 264,
    TK_PR_ELSE = 265,
    TK_PR_WHILE = 266,
    TK_PR_DO = 267,
    TK_PR_INPUT = 268,
    TK_PR_OUTPUT = 269,
    TK_PR_RETURN = 270,
    TK_PR_CONST = 271,
    TK_PR_STATIC = 272,
    TK_PR_FOREACH = 273,
    TK_PR_FOR = 274,
    TK_PR_SWITCH = 275,
    TK_PR_CASE = 276,
    TK_PR_BREAK = 277,
    TK_PR_CONTINUE = 278,
    TK_PR_CLASS = 279,
    TK_PR_PRIVATE = 280,
    TK_PR_PUBLIC = 281,
    TK_PR_PROTECTED = 282,
    TK_OC_LE = 283,
    TK_OC_GE = 284,
    TK_OC_EQ = 285,
    TK_OC_NE = 286,
    TK_OC_AND = 287,
    TK_OC_OR = 288,
    TK_OC_SL = 289,
    TK_OC_SR = 290,
    TK_LIT_INT = 291,
    TK_LIT_FLOAT = 292,
    TK_LIT_FALSE = 293,
    TK_LIT_TRUE = 294,
    TK_LIT_CHAR = 295,
    TK_LIT_STRING = 296,
    TK_IDENTIFICADOR = 297,
    TOKEN_ERRO = 298
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 13 "parser.y" /* yacc.c:355  */

	comp_tree_t *tree;
	void *valor_lexico;   /* Pointer to run-time expression operator */

#line 165 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_HOME_ARTHUR_REA_DE_TRABALHO_PC_BUILD_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 182 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
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
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

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
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  18
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   300

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  60
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  40
/* YYNRULES -- Number of rules.  */
#define YYNRULES  118
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  233

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   298

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    59,     2,     2,    54,     2,     2,     2,
      47,    48,    58,    55,    51,    56,     2,    57,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    52,    44,
       2,    53,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    45,     2,    46,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    49,     2,    50,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   103,   103,   114,   115,   116,   117,   128,   129,   130,
     131,   133,   134,   139,   145,   151,   153,   154,   155,   157,
     158,   160,   161,   163,   164,   173,   174,   176,   177,   178,
     180,   181,   182,   183,   184,   185,   191,   192,   194,   195,
     196,   201,   202,   203,   208,   209,   210,   215,   216,   217,
     223,   228,   234,   241,   243,   245,   250,   256,   261,   267,
     268,   269,   271,   284,   304,   305,   306,   320,   334,   336,
     337,   339,   340,   342,   343,   344,   349,   350,   351,   352,
     353,   355,   356,   357,   359,   360,   361,   362,   363,   368,
     369,   370,   379,   388,   389,   390,   391,   396,   400,   401,
     402,   403,   404,   405,   407,   408,   409,   410,   411,   412,
     413,   414,   415,   416,   418,   419,   420,   423,   424
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TK_PR_INT", "TK_PR_FLOAT", "TK_PR_BOOL",
  "TK_PR_CHAR", "TK_PR_STRING", "TK_PR_IF", "TK_PR_THEN", "TK_PR_ELSE",
  "TK_PR_WHILE", "TK_PR_DO", "TK_PR_INPUT", "TK_PR_OUTPUT", "TK_PR_RETURN",
  "TK_PR_CONST", "TK_PR_STATIC", "TK_PR_FOREACH", "TK_PR_FOR",
  "TK_PR_SWITCH", "TK_PR_CASE", "TK_PR_BREAK", "TK_PR_CONTINUE",
  "TK_PR_CLASS", "TK_PR_PRIVATE", "TK_PR_PUBLIC", "TK_PR_PROTECTED",
  "TK_OC_LE", "TK_OC_GE", "TK_OC_EQ", "TK_OC_NE", "TK_OC_AND", "TK_OC_OR",
  "TK_OC_SL", "TK_OC_SR", "TK_LIT_INT", "TK_LIT_FLOAT", "TK_LIT_FALSE",
  "TK_LIT_TRUE", "TK_LIT_CHAR", "TK_LIT_STRING", "TK_IDENTIFICADOR",
  "TOKEN_ERRO", "';'", "'['", "']'", "'('", "')'", "'{'", "'}'", "','",
  "':'", "'='", "'$'", "'+'", "'-'", "'/'", "'*'", "'!'", "$accept",
  "prime_programa", "programa", "def_global_var", "any_type",
  "def_function", "body", "parameters", "parameter_chain", "parameter",
  "command_sequence", "case_command", "command_in_block", "simple_command",
  "io_command", "def_local_var", "attribution_command", "input_command",
  "output_command", "function_call", "shift_command", "flux_command",
  "condition_command", "iteration_command", "selection_command",
  "for_command_sequence", "foreach_expression_sequence", "action_command",
  "def_type", "type_fields", "type_field", "encapsulation",
  "primitive_type", "expression", "sub_expression_chain", "sub_expression",
  "literal", "operator", "unary_operator", "expression_sequence", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,    59,    91,    93,    40,    41,   123,
     125,    44,    58,    61,    36,    43,    45,    47,    42,    33
};
# endif

#define YYPACT_NINF -169

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-169)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      35,  -169,  -169,  -169,  -169,  -169,    89,   -32,  -169,    47,
    -169,    35,     8,    35,    35,  -169,     9,   -29,  -169,  -169,
     -36,  -169,  -169,   -30,    18,  -169,   241,    63,  -169,   241,
      63,  -169,  -169,  -169,    14,     2,   156,  -169,  -169,  -169,
    -169,  -169,  -169,    10,   241,  -169,  -169,  -169,  -169,    15,
    -169,   194,  -169,   241,    89,    20,    24,    13,    32,    34,
      36,    18,    48,   241,   217,    43,    59,  -169,  -169,  -169,
    -169,  -169,  -169,  -169,  -169,  -169,  -169,   241,  -169,    62,
    -169,    57,    63,  -169,    65,    57,  -169,  -169,    67,    61,
    -169,    64,    66,  -169,  -169,  -169,  -169,   198,  -169,    13,
    -169,  -169,   241,  -169,   241,  -169,    72,    74,    57,   241,
     241,   241,   146,    95,    77,    78,    80,    84,  -169,  -169,
     131,   198,    60,    76,    69,  -169,  -169,  -169,  -169,  -169,
    -169,  -169,  -169,  -169,  -169,  -169,  -169,  -169,    90,  -169,
      92,  -169,   241,   241,   125,  -169,  -169,  -169,    98,   102,
     151,   103,   104,   105,    16,   241,  -169,   133,   134,  -169,
     241,   241,   137,   130,  -169,   198,   198,   153,  -169,   138,
     139,   135,  -169,   161,   149,   150,  -169,   166,   143,   145,
     147,   159,  -169,  -169,   152,  -169,   155,  -169,  -169,  -169,
     241,   219,   218,   241,   241,  -169,   201,   241,   241,    16,
     241,    57,   178,   241,  -169,    57,    57,   184,  -169,   241,
    -169,   185,   183,  -169,   186,  -169,   241,  -169,   225,  -169,
    -169,  -169,    57,   241,    16,  -169,    57,  -169,  -169,   188,
    -169,    57,  -169
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,    84,    85,    86,    87,    88,     0,     0,    11,     0,
       2,     3,     0,     3,     3,    12,     0,     0,     1,     5,
       0,     6,     4,     0,     0,     7,     0,    16,     9,     0,
      16,    82,    83,    81,     0,    77,     0,    98,    99,   102,
     101,   100,   103,    95,     0,   116,   114,   115,    97,     0,
      89,    90,    94,     0,     0,     0,     0,    17,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,     0,    92,     0,
      21,     0,     0,    18,     0,     0,    76,    78,    79,     0,
      56,   117,     0,    93,     8,    91,    22,    23,    13,    19,
      10,    14,     0,    96,     0,    55,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    75,    74,
       0,    23,     0,     0,     0,    27,    28,    33,    30,    36,
      37,    31,    32,    34,    59,    60,    61,    29,     0,    20,
       0,   118,     0,     0,     0,    53,    54,    73,     0,     0,
       0,     0,     0,     0,     0,     0,    26,     0,     0,    38,
       0,     0,     0,     0,    15,    23,    23,    39,    80,     0,
       0,     0,    44,    45,     0,     0,    41,    42,     0,    69,
       0,     0,    57,    58,     0,    50,     0,    35,    25,    24,
       0,     0,     0,     0,     0,    47,    48,     0,     0,     0,
       0,     0,     0,     0,    40,     0,     0,     0,    46,     0,
      43,     0,    71,    70,     0,    68,     0,    52,    62,    66,
      67,    49,     0,     0,     0,    51,     0,    64,    72,     0,
      63,     0,    65
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -169,  -169,    73,  -169,    -1,  -169,   -83,   207,   140,   160,
    -117,  -169,  -169,  -153,  -169,  -169,  -169,  -169,  -169,   -91,
    -169,  -169,  -169,  -169,  -169,  -168,    21,  -169,  -169,   180,
    -169,  -169,   -24,   -26,   168,   190,  -169,  -169,  -169,   -97
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     9,    10,    11,    12,    13,    98,    56,    83,    57,
     122,   123,   124,   125,   126,   127,   128,   129,   130,    48,
     132,   133,   134,   135,   136,   180,   211,   137,    14,    34,
      35,    36,    15,    91,    50,    51,    52,    77,    53,    92
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      49,   179,   101,    58,   163,    16,   131,   141,    25,    26,
      17,    27,    62,   146,    28,    29,    24,    30,    65,     1,
       2,     3,     4,     5,   106,   144,    55,   107,   108,    55,
     131,   213,   112,   113,   114,   115,   116,    89,     1,     2,
       3,     4,     5,    31,    32,    33,   179,    18,   188,   189,
      20,    23,     6,    79,    61,    63,   229,    64,   120,     7,
      60,    66,    80,   131,    82,   121,     1,     2,     3,     4,
       5,   179,    81,   138,   131,   131,   140,     8,    84,    54,
      86,    55,    85,   145,    19,   147,    21,    22,   149,   152,
      88,    93,     1,     2,     3,     4,     5,   138,     1,     2,
       3,     4,     5,    94,    96,     8,    97,   103,   131,   100,
     164,   150,   102,   166,   105,   104,   169,   170,   215,   142,
     156,   143,   218,   219,   153,   154,   175,   155,   165,   181,
     138,     8,   167,   131,   184,   185,   171,   151,   168,   227,
     172,   138,   138,   230,   173,   176,   177,   178,   232,     1,
       2,     3,     4,     5,     1,     2,     3,     4,     5,     1,
       2,     3,     4,     5,   204,   157,   158,   207,   208,   182,
     183,   210,   212,   159,   214,   138,   160,   217,    64,   186,
     187,   190,   193,   221,   161,   162,   191,   192,   148,   194,
     225,   195,   196,   174,   197,   198,   199,   212,   202,   200,
     138,     1,     2,     3,     4,     5,   106,   201,   203,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,    67,    68,    69,    70,    71,    72,   205,   209,
     206,   216,   220,   222,   223,   226,   231,    59,   224,   139,
     120,    87,    99,    78,   228,    95,     0,   121,     0,    73,
      74,    75,    76,    37,    38,    39,    40,    41,    42,    43,
       0,     0,     0,     0,    44,    90,     0,     0,     0,     0,
       0,     0,    45,    46,     0,     0,    47,    37,    38,    39,
      40,    41,    42,    43,     0,     0,     0,     0,    44,     0,
       0,     0,     0,     0,     0,     0,    45,    46,     0,     0,
      47
};

static const yytype_int16 yycheck[] =
{
      26,   154,    85,    29,   121,     6,    97,   104,    44,    45,
      42,    47,    36,   110,    44,    45,    45,    47,    44,     3,
       4,     5,     6,     7,     8,   108,    27,    11,    12,    30,
     121,   199,    16,    17,    18,    19,    20,    63,     3,     4,
       5,     6,     7,    25,    26,    27,   199,     0,   165,   166,
      42,    42,    17,    54,    52,    45,   224,    47,    42,    24,
      46,    46,    42,   154,    51,    49,     3,     4,     5,     6,
       7,   224,    48,    97,   165,   166,   102,    42,    46,    16,
      44,    82,    48,   109,    11,   111,    13,    14,   112,   113,
      42,    48,     3,     4,     5,     6,     7,   121,     3,     4,
       5,     6,     7,    44,    42,    42,    49,    46,   199,    44,
      50,    16,    45,    44,    48,    51,   142,   143,   201,    47,
      36,    47,   205,   206,    47,    47,   150,    47,    52,   155,
     154,    42,    42,   224,   160,   161,    11,    42,    46,   222,
      42,   165,   166,   226,    42,    42,    42,    42,   231,     3,
       4,     5,     6,     7,     3,     4,     5,     6,     7,     3,
       4,     5,     6,     7,   190,    34,    35,   193,   194,    36,
      36,   197,   198,    42,   200,   199,    45,   203,    47,    42,
      50,    28,    47,   209,    53,    54,    48,    48,    42,    28,
     216,    42,    42,    42,    28,    52,    51,   223,    46,    52,
     224,     3,     4,     5,     6,     7,     8,    48,    53,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    28,    29,    30,    31,    32,    33,     9,    28,
      12,    53,    48,    48,    51,    10,    48,    30,    52,    99,
      42,    61,    82,    53,   223,    77,    -1,    49,    -1,    55,
      56,    57,    58,    36,    37,    38,    39,    40,    41,    42,
      -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    55,    56,    -1,    -1,    59,    36,    37,    38,
      39,    40,    41,    42,    -1,    -1,    -1,    -1,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    55,    56,    -1,    -1,
      59
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,    17,    24,    42,    61,
      62,    63,    64,    65,    88,    92,    64,    42,     0,    62,
      42,    62,    62,    42,    45,    44,    45,    47,    44,    45,
      47,    25,    26,    27,    89,    90,    91,    36,    37,    38,
      39,    40,    41,    42,    47,    55,    56,    59,    79,    93,
      94,    95,    96,    98,    16,    64,    67,    69,    93,    67,
      46,    52,    92,    45,    47,    93,    46,    28,    29,    30,
      31,    32,    33,    55,    56,    57,    58,    97,    95,    64,
      42,    48,    51,    68,    46,    48,    44,    89,    42,    93,
      48,    93,    99,    48,    44,    94,    42,    49,    66,    69,
      44,    66,    45,    46,    51,    48,     8,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      42,    49,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    87,    92,    68,
      93,    99,    47,    47,    66,    93,    99,    93,    42,    92,
      16,    42,    92,    47,    47,    47,    36,    34,    35,    42,
      45,    53,    54,    70,    50,    52,    44,    42,    46,    93,
      93,    11,    42,    42,    42,    92,    42,    42,    42,    73,
      85,    93,    36,    36,    93,    93,    42,    50,    70,    70,
      28,    48,    48,    47,    28,    42,    42,    28,    52,    51,
      52,    48,    46,    53,    93,     9,    12,    93,    93,    28,
      93,    86,    93,    85,    93,    66,    53,    93,    66,    66,
      48,    93,    48,    51,    52,    93,    10,    66,    86,    85,
      66,    48,    66
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    60,    61,    62,    62,    62,    62,    63,    63,    63,
      63,    64,    64,    65,    65,    66,    67,    67,    67,    68,
      68,    69,    69,    70,    70,    70,    71,    72,    72,    72,
      73,    73,    73,    73,    73,    73,    74,    74,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      76,    76,    76,    77,    78,    79,    79,    80,    80,    81,
      81,    81,    82,    82,    83,    83,    83,    83,    84,    85,
      85,    86,    86,    87,    87,    87,    88,    89,    89,    90,
      90,    91,    91,    91,    92,    92,    92,    92,    92,    93,
      94,    94,    95,    95,    95,    95,    95,    95,    96,    96,
      96,    96,    96,    96,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    98,    98,    98,    99,    99
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     2,     2,     3,     6,     4,
       7,     1,     1,     6,     7,     3,     0,     1,     2,     2,
       3,     2,     3,     0,     3,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     1,     2,     2,
       4,     3,     3,     5,     3,     3,     5,     4,     4,     6,
       3,     6,     5,     2,     2,     4,     3,     3,     3,     1,
       1,     1,     6,     8,     7,     9,     6,     6,     5,     1,
       3,     1,     3,     2,     1,     1,     6,     1,     3,     3,
       6,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     2,     3,     1,     1,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

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
      yychar = yylex ();
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
     '$$ = $1'.

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
#line 104 "parser.y" /* yacc.c:1646  */
    {
	(yyval.tree) = tree_new();
	set_ast_root((yyval.tree));
	if ((yyvsp[0].tree))
		tree_insert_node((yyval.tree), (yyvsp[0].tree));

	gv_declare(AST_PROGRAMA, (yyval.tree), NULL);
	putToGraphviz((yyval.tree));
}
#line 1451 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 3:
#line 114 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; }
#line 1457 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 4:
#line 115 "parser.y" /* yacc.c:1646  */
    { if ((yyvsp[0].tree)) (yyval.tree) = (yyvsp[0].tree); else (yyval.tree) = NULL; }
#line 1463 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 5:
#line 116 "parser.y" /* yacc.c:1646  */
    { if ((yyvsp[0].tree)) (yyval.tree) = (yyvsp[0].tree); else (yyval.tree) = NULL; }
#line 1469 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 6:
#line 118 "parser.y" /* yacc.c:1646  */
    {
	if ((yyvsp[0].tree)) {
		tree_insert_node((yyvsp[-1].tree),(yyvsp[0].tree));
	}
	(yyval.tree) = (yyvsp[-1].tree);
}
#line 1480 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 13:
#line 140 "parser.y" /* yacc.c:1646  */
    {
	(yyval.tree) = tree_make_node(new_ast_node_value(AST_FUNCAO, (yyvsp[-4].valor_lexico)));
	if ((yyvsp[0].tree))
		tree_insert_node((yyval.tree),(yyvsp[0].tree));
}
#line 1490 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 14:
#line 146 "parser.y" /* yacc.c:1646  */
    {
	(yyval.tree) = tree_make_node(new_ast_node_value(AST_FUNCAO, (yyvsp[-4].valor_lexico)));
	if ((yyvsp[0].tree))
		tree_insert_node((yyval.tree),(yyvsp[0].tree));
}
#line 1500 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 15:
#line 151 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[-1].tree); }
#line 1506 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 23:
#line 163 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; }
#line 1512 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 24:
#line 165 "parser.y" /* yacc.c:1646  */
    {
	if ((yyvsp[-2].tree)) {
		(yyval.tree) = (yyvsp[-2].tree);
		if ((yyvsp[0].tree)) tree_insert_node((yyval.tree),(yyvsp[0].tree));
	} else {
		(yyval.tree) = (yyvsp[0].tree);
	}
}
#line 1525 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 25:
#line 173 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 1531 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 27:
#line 176 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 1537 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 28:
#line 177 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 1543 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 29:
#line 178 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 1549 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 30:
#line 180 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 1555 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 31:
#line 181 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 1561 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 32:
#line 182 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 1567 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 33:
#line 183 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 1573 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 34:
#line 184 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 1579 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 35:
#line 186 "parser.y" /* yacc.c:1646  */
    {
	(yyval.tree) = tree_make_node(new_ast_node_value(AST_BLOCO, NULL));
	if ((yyvsp[-1].tree)) tree_insert_node((yyval.tree),(yyvsp[-1].tree));
}
#line 1588 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 36:
#line 191 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 1594 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 37:
#line 192 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 1600 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 38:
#line 194 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; }
#line 1606 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 39:
#line 195 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; }
#line 1612 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 40:
#line 197 "parser.y" /* yacc.c:1646  */
    {
	comp_tree_t* node_identificador = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, (yyvsp[-2].valor_lexico)));
	(yyval.tree) = tree_make_binary_node(new_ast_node_value(AST_ATRIBUICAO, NULL), node_identificador, (yyvsp[0].tree));
}
#line 1621 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 41:
#line 201 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; }
#line 1627 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 42:
#line 202 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; }
#line 1633 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 43:
#line 204 "parser.y" /* yacc.c:1646  */
    {
	comp_tree_t* node_identificador = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, (yyvsp[-2].valor_lexico)));
	(yyval.tree) = tree_make_binary_node(new_ast_node_value(AST_ATRIBUICAO, NULL), node_identificador, (yyvsp[0].tree));
}
#line 1642 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 44:
#line 208 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; }
#line 1648 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 45:
#line 209 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; }
#line 1654 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 46:
#line 211 "parser.y" /* yacc.c:1646  */
    {
	comp_tree_t* node_identificador = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, (yyvsp[-2].valor_lexico)));
	(yyval.tree) = tree_make_binary_node(new_ast_node_value(AST_ATRIBUICAO, NULL), node_identificador, (yyvsp[0].tree));
}
#line 1663 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 47:
#line 215 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; }
#line 1669 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 48:
#line 216 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; }
#line 1675 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 49:
#line 218 "parser.y" /* yacc.c:1646  */
    {
	comp_tree_t* node_identificador = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, (yyvsp[-2].valor_lexico)));
	(yyval.tree) = tree_make_binary_node(new_ast_node_value(AST_ATRIBUICAO, NULL), node_identificador, (yyvsp[0].tree));
}
#line 1684 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 50:
#line 224 "parser.y" /* yacc.c:1646  */
    {
	comp_tree_t* node_identificador = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, (yyvsp[-2].valor_lexico)));
	(yyval.tree) = tree_make_binary_node(new_ast_node_value(AST_ATRIBUICAO, NULL), node_identificador, (yyvsp[0].tree));
}
#line 1693 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 51:
#line 229 "parser.y" /* yacc.c:1646  */
    {
	comp_tree_t* node_identificador = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, (yyvsp[-5].valor_lexico)));
	comp_tree_t* node_vetor_indexado = tree_make_binary_node(new_ast_node_value(AST_VETOR_INDEXADO, NULL), node_identificador, (yyvsp[-3].tree));
	(yyval.tree) = tree_make_binary_node(new_ast_node_value(AST_ATRIBUICAO, NULL), node_vetor_indexado, (yyvsp[0].tree));
}
#line 1703 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 52:
#line 235 "parser.y" /* yacc.c:1646  */
    {
	comp_tree_t* node_identificador = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, (yyvsp[-4].valor_lexico)));
	comp_tree_t* node_campo = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, (yyvsp[-2].valor_lexico)));
	(yyval.tree) = tree_make_ternary_node(new_ast_node_value(AST_ATRIBUICAO, NULL), node_identificador, (yyvsp[0].tree), node_campo);
}
#line 1713 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 53:
#line 241 "parser.y" /* yacc.c:1646  */
    {	(yyval.tree) = tree_make_unary_node(new_ast_node_value(AST_INPUT, NULL), (yyvsp[0].tree)); }
#line 1719 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 54:
#line 243 "parser.y" /* yacc.c:1646  */
    {	(yyval.tree) = tree_make_unary_node(new_ast_node_value(AST_OUTPUT,NULL), (yyvsp[0].tree)); }
#line 1725 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 55:
#line 246 "parser.y" /* yacc.c:1646  */
    {
	comp_tree_t* node_identificador = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, (yyvsp[-3].valor_lexico)));
	(yyval.tree) = tree_make_binary_node(new_ast_node_value(AST_CHAMADA_DE_FUNCAO, NULL), node_identificador, (yyvsp[-1].tree));
}
#line 1734 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 56:
#line 251 "parser.y" /* yacc.c:1646  */
    {
	comp_tree_t* node_identificador = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, (yyvsp[-2].valor_lexico)));
	(yyval.tree) = tree_make_unary_node(new_ast_node_value(AST_CHAMADA_DE_FUNCAO, NULL), node_identificador);
}
#line 1743 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 57:
#line 257 "parser.y" /* yacc.c:1646  */
    {
	comp_tree_t* node_identificador = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, (yyvsp[-2].valor_lexico)));
	(yyval.tree) = tree_make_unary_node(new_ast_node_value(AST_SHIFT_LEFT, NULL), node_identificador);
}
#line 1752 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 58:
#line 262 "parser.y" /* yacc.c:1646  */
    {
	comp_tree_t* node_identificador = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, (yyvsp[-2].valor_lexico)));
	(yyval.tree) = tree_make_unary_node(new_ast_node_value(AST_SHIFT_RIGHT, NULL), node_identificador);
}
#line 1761 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 62:
#line 272 "parser.y" /* yacc.c:1646  */
    {
	(yyval.tree) = tree_make_node(new_ast_node_value(AST_IF_ELSE, NULL));

	//pendura expression
	if ((yyvsp[-3].tree)) tree_insert_node((yyval.tree), (yyvsp[-3].tree));

	//pendura body do then
	if ((yyvsp[0].tree))
		tree_insert_node((yyval.tree), (yyvsp[0].tree));
	else
		tree_insert_node((yyval.tree), tree_make_node(new_ast_node_value(AST_BLOCO, NULL)));
}
#line 1778 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 63:
#line 285 "parser.y" /* yacc.c:1646  */
    {
	(yyval.tree) = tree_make_node(new_ast_node_value(AST_IF_ELSE, NULL));

	//pendura expression
	if ((yyvsp[-5].tree)) tree_insert_node((yyval.tree), (yyvsp[-5].tree));

	//pendura body do then
	if ((yyvsp[-2].tree))
		tree_insert_node((yyval.tree), (yyvsp[-2].tree));
	else
		tree_insert_node((yyval.tree), tree_make_node(new_ast_node_value(AST_BLOCO, NULL)));

	//pendura body do else
	if ((yyvsp[0].tree))
		tree_insert_node((yyval.tree), (yyvsp[0].tree));
	else
		tree_insert_node((yyval.tree), tree_make_node(new_ast_node_value(AST_BLOCO, NULL)));
}
#line 1801 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 64:
#line 304 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; }
#line 1807 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 65:
#line 305 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; }
#line 1813 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 66:
#line 307 "parser.y" /* yacc.c:1646  */
    {
	(yyval.tree) = tree_make_node(new_ast_node_value(AST_WHILE_DO, NULL));

	//pendura expression
	if ((yyvsp[-3].tree)) tree_insert_node((yyval.tree), (yyvsp[-3].tree));

	//pendura body
	if ((yyvsp[0].tree))
		tree_insert_node((yyval.tree), (yyvsp[0].tree));
	else
		tree_insert_node((yyval.tree), tree_make_node(new_ast_node_value(AST_BLOCO, NULL)));

}
#line 1831 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 67:
#line 321 "parser.y" /* yacc.c:1646  */
    {
	(yyval.tree) = tree_make_node(new_ast_node_value(AST_DO_WHILE, NULL));

	//pendura body
	if ((yyvsp[-4].tree))
		tree_insert_node((yyval.tree), (yyvsp[-4].tree));
	else
		tree_insert_node((yyval.tree), tree_make_node(new_ast_node_value(AST_BLOCO, NULL)));

	//pendura expression
	if ((yyvsp[-1].tree)) tree_insert_node((yyval.tree), (yyvsp[-1].tree));
}
#line 1848 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 68:
#line 334 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; }
#line 1854 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 73:
#line 342 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = tree_make_unary_node(new_ast_node_value(AST_RETURN, NULL), (yyvsp[0].tree)); }
#line 1860 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 74:
#line 343 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; }
#line 1866 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 75:
#line 344 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; }
#line 1872 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 89:
#line 368 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 1878 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 90:
#line 369 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 1884 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 91:
#line 371 "parser.y" /* yacc.c:1646  */
    {
	//operador sobe
	(yyval.tree) = (yyvsp[-1].tree);
	//pendura operandos
	tree_insert_node((yyval.tree), (yyvsp[-2].tree));
	tree_insert_node((yyval.tree), (yyvsp[0].tree));
}
#line 1896 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 92:
#line 380 "parser.y" /* yacc.c:1646  */
    {
	if ((yyvsp[-1].tree)) {
		(yyval.tree) = (yyvsp[-1].tree);
		tree_insert_node((yyval.tree), (yyvsp[0].tree));
	} else {
		(yyval.tree) = (yyvsp[0].tree);
	}
}
#line 1909 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 93:
#line 388 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[-1].tree); }
#line 1915 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 94:
#line 389 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 1921 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 95:
#line 390 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, (yyvsp[0].valor_lexico))); }
#line 1927 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 96:
#line 392 "parser.y" /* yacc.c:1646  */
    {
	comp_tree_t* node_identificador = tree_make_node(new_ast_node_value(AST_IDENTIFICADOR, (yyvsp[-3].valor_lexico)));
	(yyval.tree) = tree_make_binary_node(new_ast_node_value(AST_VETOR_INDEXADO,NULL), node_identificador, (yyvsp[-1].tree));
}
#line 1936 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 97:
#line 396 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 1942 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 98:
#line 400 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = tree_make_node(new_ast_node_value(AST_LITERAL, (yyvsp[0].valor_lexico))); }
#line 1948 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 99:
#line 401 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = tree_make_node(new_ast_node_value(AST_LITERAL, (yyvsp[0].valor_lexico))); }
#line 1954 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 100:
#line 402 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = tree_make_node(new_ast_node_value(AST_LITERAL, (yyvsp[0].valor_lexico))); }
#line 1960 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 101:
#line 403 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = tree_make_node(new_ast_node_value(AST_LITERAL, (yyvsp[0].valor_lexico))); }
#line 1966 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 102:
#line 404 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = tree_make_node(new_ast_node_value(AST_LITERAL, (yyvsp[0].valor_lexico))); }
#line 1972 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 103:
#line 405 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = tree_make_node(new_ast_node_value(AST_LITERAL, (yyvsp[0].valor_lexico))); }
#line 1978 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 104:
#line 407 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = tree_make_node(new_ast_node_value(AST_LOGICO_COMP_LE, NULL)); }
#line 1984 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 105:
#line 408 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = tree_make_node(new_ast_node_value(AST_LOGICO_COMP_GE, NULL)); }
#line 1990 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 106:
#line 409 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = tree_make_node(new_ast_node_value(AST_LOGICO_COMP_IGUAL, NULL)); }
#line 1996 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 107:
#line 410 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = tree_make_node(new_ast_node_value(AST_LOGICO_COMP_DIF, NULL)); }
#line 2002 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 108:
#line 411 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = tree_make_node(new_ast_node_value(AST_LOGICO_E, NULL)); }
#line 2008 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 109:
#line 412 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = tree_make_node(new_ast_node_value(AST_LOGICO_OU, NULL)); }
#line 2014 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 110:
#line 413 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = tree_make_node(new_ast_node_value(AST_ARIM_SOMA, NULL)); }
#line 2020 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 111:
#line 414 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = tree_make_node(new_ast_node_value(AST_ARIM_SUBTRACAO, NULL)); }
#line 2026 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 112:
#line 415 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = tree_make_node(new_ast_node_value(AST_ARIM_DIVISAO, NULL)); }
#line 2032 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 113:
#line 416 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = tree_make_node(new_ast_node_value(AST_ARIM_MULTIPLICACAO, NULL)); }
#line 2038 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 114:
#line 418 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = tree_make_node(new_ast_node_value(AST_ARIM_INVERSAO, NULL)); }
#line 2044 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 115:
#line 419 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = tree_make_node(new_ast_node_value(AST_LOGICO_COMP_NEGACAO, NULL)); }
#line 2050 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 116:
#line 420 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; }
#line 2056 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 117:
#line 423 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 2062 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;

  case 118:
#line 425 "parser.y" /* yacc.c:1646  */
    {
	//sobe expressao
	(yyval.tree) = (yyvsp[-2].tree);
	//pendura proxima
	tree_insert_node((yyval.tree), (yyvsp[0].tree));
}
#line 2073 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
    break;


#line 2077 "/home/arthur/Área de Trabalho/pc/build/parser.c" /* yacc.c:1646  */
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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 432 "parser.y" /* yacc.c:1906  */

