/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "misc/parser.y"

	#include <string.h>
	#include <stdio.h>
	#include "../inc/assembler.hpp"

	extern int yylex();
	extern int yyparse();
	extern FILE* yyin;

	extern int line_number;
	int parse = 1;

	void yyerror(const char* s);

	class Assembler;

	

#line 90 "src/parser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TOKEN_HALT = 3,                 /* TOKEN_HALT  */
  YYSYMBOL_TOKEN_INT = 4,                  /* TOKEN_INT  */
  YYSYMBOL_TOKEN_IRET = 5,                 /* TOKEN_IRET  */
  YYSYMBOL_TOKEN_CALL = 6,                 /* TOKEN_CALL  */
  YYSYMBOL_TOKEN_RET = 7,                  /* TOKEN_RET  */
  YYSYMBOL_TOKEN_JMP = 8,                  /* TOKEN_JMP  */
  YYSYMBOL_TOKEN_BEQ = 9,                  /* TOKEN_BEQ  */
  YYSYMBOL_TOKEN_BNE = 10,                 /* TOKEN_BNE  */
  YYSYMBOL_TOKEN_BGT = 11,                 /* TOKEN_BGT  */
  YYSYMBOL_TOKEN_PUSH = 12,                /* TOKEN_PUSH  */
  YYSYMBOL_TOKEN_POP = 13,                 /* TOKEN_POP  */
  YYSYMBOL_TOKEN_XCHG = 14,                /* TOKEN_XCHG  */
  YYSYMBOL_TOKEN_ADD = 15,                 /* TOKEN_ADD  */
  YYSYMBOL_TOKEN_SUB = 16,                 /* TOKEN_SUB  */
  YYSYMBOL_TOKEN_MUL = 17,                 /* TOKEN_MUL  */
  YYSYMBOL_TOKEN_DIV = 18,                 /* TOKEN_DIV  */
  YYSYMBOL_TOKEN_NOT = 19,                 /* TOKEN_NOT  */
  YYSYMBOL_TOKEN_AND = 20,                 /* TOKEN_AND  */
  YYSYMBOL_TOKEN_OR = 21,                  /* TOKEN_OR  */
  YYSYMBOL_TOKEN_XOR = 22,                 /* TOKEN_XOR  */
  YYSYMBOL_TOKEN_SHL = 23,                 /* TOKEN_SHL  */
  YYSYMBOL_TOKEN_SHR = 24,                 /* TOKEN_SHR  */
  YYSYMBOL_TOKEN_LD = 25,                  /* TOKEN_LD  */
  YYSYMBOL_TOKEN_ST = 26,                  /* TOKEN_ST  */
  YYSYMBOL_TOKEN_CSRRD = 27,               /* TOKEN_CSRRD  */
  YYSYMBOL_TOKEN_CSRWR = 28,               /* TOKEN_CSRWR  */
  YYSYMBOL_TOKEN_GLOBAL = 29,              /* TOKEN_GLOBAL  */
  YYSYMBOL_TOKEN_EXTERN = 30,              /* TOKEN_EXTERN  */
  YYSYMBOL_TOKEN_SECTION = 31,             /* TOKEN_SECTION  */
  YYSYMBOL_TOKEN_WORD = 32,                /* TOKEN_WORD  */
  YYSYMBOL_TOKEN_SKIP = 33,                /* TOKEN_SKIP  */
  YYSYMBOL_TOKEN_ASCII = 34,               /* TOKEN_ASCII  */
  YYSYMBOL_TOKEN_END = 35,                 /* TOKEN_END  */
  YYSYMBOL_TOKEN_IDENT = 36,               /* TOKEN_IDENT  */
  YYSYMBOL_TOKEN_LPAR = 37,                /* TOKEN_LPAR  */
  YYSYMBOL_TOKEN_RPAR = 38,                /* TOKEN_RPAR  */
  YYSYMBOL_TOKEN_LBRACKET = 39,            /* TOKEN_LBRACKET  */
  YYSYMBOL_TOKEN_RBRACKET = 40,            /* TOKEN_RBRACKET  */
  YYSYMBOL_TOKEN_PLUS = 41,                /* TOKEN_PLUS  */
  YYSYMBOL_TOKEN_MINUS = 42,               /* TOKEN_MINUS  */
  YYSYMBOL_TOKEN_PERCENT = 43,             /* TOKEN_PERCENT  */
  YYSYMBOL_TOKEN_DOLLAR = 44,              /* TOKEN_DOLLAR  */
  YYSYMBOL_TOKEN_SEMI = 45,                /* TOKEN_SEMI  */
  YYSYMBOL_TOKEN_COLON = 46,               /* TOKEN_COLON  */
  YYSYMBOL_TOKEN_COMMA = 47,               /* TOKEN_COMMA  */
  YYSYMBOL_TOKEN_REG = 48,                 /* TOKEN_REG  */
  YYSYMBOL_TOKEN_STATUS = 49,              /* TOKEN_STATUS  */
  YYSYMBOL_TOKEN_HANDLER = 50,             /* TOKEN_HANDLER  */
  YYSYMBOL_TOKEN_CAUSE = 51,               /* TOKEN_CAUSE  */
  YYSYMBOL_TOKEN_NUM = 52,                 /* TOKEN_NUM  */
  YYSYMBOL_TOKEN_STRING = 53,              /* TOKEN_STRING  */
  YYSYMBOL_YYACCEPT = 54,                  /* $accept  */
  YYSYMBOL_prog = 55,                      /* prog  */
  YYSYMBOL_statements = 56,                /* statements  */
  YYSYMBOL_statement = 57,                 /* statement  */
  YYSYMBOL_directive = 58,                 /* directive  */
  YYSYMBOL_global_list = 59,               /* global_list  */
  YYSYMBOL_extern_list = 60,               /* extern_list  */
  YYSYMBOL_word_list = 61,                 /* word_list  */
  YYSYMBOL_word = 62,                      /* word  */
  YYSYMBOL_instr = 63,                     /* instr  */
  YYSYMBOL_spec_operand = 64,              /* spec_operand  */
  YYSYMBOL_sys_reg = 65                    /* sys_reg  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   159

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  12
/* YYNRULES -- Number of rules.  */
#define YYNRULES  70
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  169

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   308


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      45,    46,    47,    48,    49,    50,    51,    52,    53
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    99,    99,   104,   105,   109,   110,   114,   115,   116,
     121,   122,   125,   130,   133,   140,   144,   151,   156,   163,
     164,   168,   172,   179,   183,   186,   191,   196,   201,   205,
     209,   214,   219,   223,   228,   232,   236,   241,   247,   251,
     255,   259,   263,   267,   272,   278,   283,   288,   292,   296,
     300,   305,   310,   316,   321,   322,   326,   331,   335,   340,
     345,   350,   355,   359,   363,   367,   374,   379,   385,   386,
     387
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TOKEN_HALT",
  "TOKEN_INT", "TOKEN_IRET", "TOKEN_CALL", "TOKEN_RET", "TOKEN_JMP",
  "TOKEN_BEQ", "TOKEN_BNE", "TOKEN_BGT", "TOKEN_PUSH", "TOKEN_POP",
  "TOKEN_XCHG", "TOKEN_ADD", "TOKEN_SUB", "TOKEN_MUL", "TOKEN_DIV",
  "TOKEN_NOT", "TOKEN_AND", "TOKEN_OR", "TOKEN_XOR", "TOKEN_SHL",
  "TOKEN_SHR", "TOKEN_LD", "TOKEN_ST", "TOKEN_CSRRD", "TOKEN_CSRWR",
  "TOKEN_GLOBAL", "TOKEN_EXTERN", "TOKEN_SECTION", "TOKEN_WORD",
  "TOKEN_SKIP", "TOKEN_ASCII", "TOKEN_END", "TOKEN_IDENT", "TOKEN_LPAR",
  "TOKEN_RPAR", "TOKEN_LBRACKET", "TOKEN_RBRACKET", "TOKEN_PLUS",
  "TOKEN_MINUS", "TOKEN_PERCENT", "TOKEN_DOLLAR", "TOKEN_SEMI",
  "TOKEN_COLON", "TOKEN_COMMA", "TOKEN_REG", "TOKEN_STATUS",
  "TOKEN_HANDLER", "TOKEN_CAUSE", "TOKEN_NUM", "TOKEN_STRING", "$accept",
  "prog", "statements", "statement", "directive", "global_list",
  "extern_list", "word_list", "word", "instr", "spec_operand", "sys_reg", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-9)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      -9,    54,    -3,    -9,    -9,    -9,    -9,     0,    -9,     3,
      14,    20,    25,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    -2,    40,    21,    41,
      55,    56,    57,     4,    22,    42,    -9,    44,    -9,    -9,
      -9,    -9,    -9,    -9,    -9,    -9,    47,    49,    50,    -9,
      -9,    51,    52,    53,    58,    59,    -9,    60,    61,    62,
      63,    64,    65,    66,     5,    68,    69,    70,    -9,    -9,
      -9,    71,    72,    -9,    73,    -9,    74,    -9,    -9,    -9,
      75,    -9,    -9,    -9,    -9,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    18,
      91,    92,    93,    94,    -1,    95,    21,    67,   104,     4,
      97,    98,    99,    -9,    -9,    -9,    -9,    -9,    -9,    -9,
      -9,    -9,    -9,    -9,   100,     8,   101,   102,    -9,    -9,
      -9,   103,     9,    -9,    -9,    -9,    -9,    -9,    -9,    11,
      12,    13,   105,   108,   112,    -9,    -9,    26,    -9,    -9,
      -9,    -9,    -9,    -9,    -9,    -9,    -9,   107,   109,    -9,
      17,   110,   111,   115,   117,    -9,    -9,    -9,    -9
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     2,     1,    23,    24,    53,     0,    57,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    13,     0,     4,     5,
       6,    66,    67,    54,    58,    62,     0,     0,     0,    55,
      56,     0,     0,     0,     0,     0,    29,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    68,    69,
      70,     0,     0,    15,     7,    17,     8,     9,    21,    22,
      10,    19,    11,    12,    14,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    35,    25,    26,    27,    28,    30,    31,
      32,    33,    34,    44,     0,     0,     0,     0,    41,    39,
      50,     0,     0,    47,    36,    37,    16,    18,    20,     0,
       0,     0,     0,     0,     0,    43,    38,     0,    46,    45,
      59,    63,    60,    64,    61,    65,    42,     0,     0,    48,
       0,     0,     0,     0,     0,    52,    40,    51,    49
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
      -9,    -9,    -9,    -9,    -9,    -9,    -9,    -9,    -8,    -9,
      -9,    -4
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,    38,    39,    74,    76,    80,    81,    40,
      43,    71
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    62,   130,    41,    63,   131,    44,
      78,   100,    64,   132,   143,   148,    65,   150,   152,   154,
      66,   133,    42,   163,     3,    45,    79,   101,   124,   125,
     144,   149,    46,   151,   153,   155,   159,   160,    47,   164,
      68,    69,    70,    48,    82,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    67,    72,
      84,    73,    75,    77,    85,    83,    86,    87,    88,    89,
      90,   138,   135,   136,     0,    91,    92,    93,    94,    95,
      96,    97,    98,     0,    99,   102,   103,   104,   105,   106,
     107,   108,   109,     0,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   126,   127,
     137,   128,   129,   134,   139,   140,   141,   142,   157,   145,
     146,   147,   158,   156,   161,   167,   162,   168,   165,   166
};

static const yytype_int8 yycheck[] =
{
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    36,    36,    36,    39,    39,    36,
      36,    36,    44,    44,    36,    36,    48,    36,    36,    36,
      52,    52,    52,    36,     0,    52,    52,    52,    40,    41,
      52,    52,    48,    52,    52,    52,    40,    41,    48,    52,
      49,    50,    51,    48,    52,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      46,    36,    36,    36,    47,    53,    47,    47,    47,    47,
      47,   109,   106,    36,    -1,    47,    47,    47,    47,    47,
      47,    47,    47,    -1,    48,    47,    47,    47,    47,    47,
      47,    47,    47,    -1,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    47,    47,
      36,    48,    48,    48,    47,    47,    47,    47,    40,    48,
      48,    48,    40,    48,    47,    40,    47,    40,    48,    48
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    55,    56,     0,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    57,    58,
      63,    36,    52,    64,    36,    52,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    36,    39,    44,    48,    52,    48,    49,    50,
      51,    65,    48,    36,    59,    36,    60,    36,    36,    52,
      61,    62,    52,    53,    46,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    48,
      36,    52,    47,    47,    47,    47,    47,    47,    47,    47,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    40,    41,    47,    47,    48,    48,
      36,    39,    44,    52,    48,    65,    36,    36,    62,    47,
      47,    47,    47,    36,    52,    48,    48,    48,    36,    52,
      36,    52,    36,    52,    36,    52,    48,    40,    40,    40,
      41,    47,    47,    36,    52,    48,    48,    40,    40
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    54,    55,    56,    56,    57,    57,    58,    58,    58,
      58,    58,    58,    58,    58,    59,    59,    60,    60,    61,
      61,    62,    62,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    64,    64,    65,    65,
      65
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     1,     2,     2,     2,
       2,     2,     2,     1,     2,     1,     3,     1,     3,     1,
       3,     1,     1,     1,     1,     4,     4,     4,     4,     2,
       4,     4,     4,     4,     4,     4,     4,     4,     5,     4,
       8,     4,     6,     5,     4,     5,     5,     4,     6,     8,
       4,     8,     8,     1,     2,     2,     2,     1,     2,     6,
       6,     6,     2,     6,     6,     6,     1,     1,     1,     1,
       1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 9: /* directive: TOKEN_SECTION TOKEN_IDENT  */
#line 117 "misc/parser.y"
                {
			std::string ident = (yyvsp[0].ident);
			Assembler::make_section(ident);
		}
#line 1249 "src/parser.cpp"
    break;

  case 11: /* directive: TOKEN_SKIP TOKEN_NUM  */
#line 122 "misc/parser.y"
                                       {
			Assembler::handle_skip((yyvsp[0].num));
		}
#line 1257 "src/parser.cpp"
    break;

  case 12: /* directive: TOKEN_ASCII TOKEN_STRING  */
#line 125 "misc/parser.y"
                                           {
			std::string ascii = (yyvsp[0].ident);
			ascii = ascii.substr(1,ascii.size()-2);
			Assembler::handle_ascii(ascii);
		}
#line 1267 "src/parser.cpp"
    break;

  case 13: /* directive: TOKEN_END  */
#line 130 "misc/parser.y"
                            {
			parse = 0;
		}
#line 1275 "src/parser.cpp"
    break;

  case 14: /* directive: TOKEN_IDENT TOKEN_COLON  */
#line 133 "misc/parser.y"
                                           {
			std::string ident = (yyvsp[-1].ident);
			Assembler::handle_label(ident);
		}
#line 1284 "src/parser.cpp"
    break;

  case 15: /* global_list: TOKEN_IDENT  */
#line 140 "misc/parser.y"
                              {
			std::string ident = (yyvsp[0].ident);
			Assembler::handle_bind_type(bind_type::GLO, ident);
		}
#line 1293 "src/parser.cpp"
    break;

  case 16: /* global_list: global_list TOKEN_COMMA TOKEN_IDENT  */
#line 144 "misc/parser.y"
                                                      {
			std::string ident = (yyvsp[0].ident);
			Assembler::handle_bind_type(bind_type::GLO, ident);
		}
#line 1302 "src/parser.cpp"
    break;

  case 17: /* extern_list: TOKEN_IDENT  */
#line 151 "misc/parser.y"
                              {
			std::string ident = (yyvsp[0].ident);	
			Assembler::handle_bind_type(bind_type::EXT, ident);
			
		}
#line 1312 "src/parser.cpp"
    break;

  case 18: /* extern_list: extern_list TOKEN_COMMA TOKEN_IDENT  */
#line 156 "misc/parser.y"
                                                      {
			std::string ident = (yyvsp[0].ident);
			Assembler::handle_bind_type(bind_type::EXT, ident);
		}
#line 1321 "src/parser.cpp"
    break;

  case 21: /* word: TOKEN_IDENT  */
#line 168 "misc/parser.y"
                              {
			std::string temp = (yyvsp[0].ident);
			Assembler::handle_word(temp);
		}
#line 1330 "src/parser.cpp"
    break;

  case 22: /* word: TOKEN_NUM  */
#line 172 "misc/parser.y"
                            {
			Assembler::handle_word((yyvsp[0].num));
		}
#line 1338 "src/parser.cpp"
    break;

  case 23: /* instr: TOKEN_HALT  */
#line 180 "misc/parser.y"
                        {
				Assembler::handle_instruction((Assembler::instruction)(yyvsp[0].op_code), {});
			}
#line 1346 "src/parser.cpp"
    break;

  case 24: /* instr: TOKEN_INT  */
#line 183 "misc/parser.y"
                           {
				Assembler::handle_instruction((Assembler::instruction)(yyvsp[0].op_code), {});
			}
#line 1354 "src/parser.cpp"
    break;

  case 25: /* instr: TOKEN_ADD TOKEN_REG TOKEN_COMMA TOKEN_REG  */
#line 187 "misc/parser.y"
                        { 
				Assembler::handle_instruction((Assembler::instruction)(yyvsp[-3].op_code), {(yyvsp[-2].num), (yyvsp[0].num)});
			}
#line 1362 "src/parser.cpp"
    break;

  case 26: /* instr: TOKEN_SUB TOKEN_REG TOKEN_COMMA TOKEN_REG  */
#line 192 "misc/parser.y"
                        { 
				Assembler::handle_instruction((Assembler::instruction)(yyvsp[-3].op_code), {(yyvsp[-2].num), (yyvsp[0].num)});
			}
#line 1370 "src/parser.cpp"
    break;

  case 27: /* instr: TOKEN_MUL TOKEN_REG TOKEN_COMMA TOKEN_REG  */
#line 197 "misc/parser.y"
                        { 
				Assembler::handle_instruction((Assembler::instruction)(yyvsp[-3].op_code), {(yyvsp[-2].num), (yyvsp[0].num)});
			}
#line 1378 "src/parser.cpp"
    break;

  case 28: /* instr: TOKEN_DIV TOKEN_REG TOKEN_COMMA TOKEN_REG  */
#line 202 "misc/parser.y"
                        { 
				Assembler::handle_instruction((Assembler::instruction)(yyvsp[-3].op_code), {(yyvsp[-2].num), (yyvsp[0].num)});
			}
#line 1386 "src/parser.cpp"
    break;

  case 29: /* instr: TOKEN_NOT TOKEN_REG  */
#line 206 "misc/parser.y"
                        { 
				Assembler::handle_instruction((Assembler::instruction)(yyvsp[-1].op_code), {0, (yyvsp[0].num)});
			}
#line 1394 "src/parser.cpp"
    break;

  case 30: /* instr: TOKEN_AND TOKEN_REG TOKEN_COMMA TOKEN_REG  */
#line 210 "misc/parser.y"
                        { 
				Assembler::handle_instruction((Assembler::instruction)(yyvsp[-3].op_code), {(yyvsp[-2].num), (yyvsp[0].num)});
			}
#line 1402 "src/parser.cpp"
    break;

  case 31: /* instr: TOKEN_OR TOKEN_REG TOKEN_COMMA TOKEN_REG  */
#line 215 "misc/parser.y"
                        { 
				Assembler::handle_instruction((Assembler::instruction)(yyvsp[-3].op_code), {(yyvsp[-2].num), (yyvsp[0].num)});
			}
#line 1410 "src/parser.cpp"
    break;

  case 32: /* instr: TOKEN_XOR TOKEN_REG TOKEN_COMMA TOKEN_REG  */
#line 220 "misc/parser.y"
                        { 
				Assembler::handle_instruction((Assembler::instruction)(yyvsp[-3].op_code), {(yyvsp[-2].num), (yyvsp[0].num)});
			}
#line 1418 "src/parser.cpp"
    break;

  case 33: /* instr: TOKEN_SHL TOKEN_REG TOKEN_COMMA TOKEN_REG  */
#line 224 "misc/parser.y"
                        { 
				Assembler::handle_instruction((Assembler::instruction)(yyvsp[-3].op_code), {(yyvsp[-2].num), (yyvsp[0].num)});
			}
#line 1426 "src/parser.cpp"
    break;

  case 34: /* instr: TOKEN_SHR TOKEN_REG TOKEN_COMMA TOKEN_REG  */
#line 229 "misc/parser.y"
                        { 
				Assembler::handle_instruction((Assembler::instruction)(yyvsp[-3].op_code), {(yyvsp[-2].num), (yyvsp[0].num)});
			}
#line 1434 "src/parser.cpp"
    break;

  case 35: /* instr: TOKEN_XCHG TOKEN_REG TOKEN_COMMA TOKEN_REG  */
#line 233 "misc/parser.y"
                        { 
				Assembler::handle_instruction((Assembler::instruction)(yyvsp[-3].op_code), {(yyvsp[-2].num), (yyvsp[0].num)});
			}
#line 1442 "src/parser.cpp"
    break;

  case 36: /* instr: TOKEN_CSRRD sys_reg TOKEN_COMMA TOKEN_REG  */
#line 237 "misc/parser.y"
                        { 
				std::string ident = (yyvsp[-2].ident);
				Assembler::handle_sys_regr(ident, (yyvsp[0].num)); 
			}
#line 1451 "src/parser.cpp"
    break;

  case 37: /* instr: TOKEN_CSRWR TOKEN_REG TOKEN_COMMA sys_reg  */
#line 242 "misc/parser.y"
                        { 
				std::string ident = (yyvsp[0].ident);
				Assembler::handle_sys_regw(ident, (yyvsp[-2].num)); 
			}
#line 1460 "src/parser.cpp"
    break;

  case 38: /* instr: TOKEN_LD TOKEN_DOLLAR TOKEN_NUM TOKEN_COMMA TOKEN_REG  */
#line 248 "misc/parser.y"
                        { 
				Assembler::mem_imm_literal((yyvsp[-2].num), (yyvsp[0].num));
			}
#line 1468 "src/parser.cpp"
    break;

  case 39: /* instr: TOKEN_LD TOKEN_NUM TOKEN_COMMA TOKEN_REG  */
#line 252 "misc/parser.y"
                        {
				Assembler::mem_dir_literal((yyvsp[-2].num), (yyvsp[0].num));
			}
#line 1476 "src/parser.cpp"
    break;

  case 40: /* instr: TOKEN_LD TOKEN_LBRACKET TOKEN_REG TOKEN_PLUS TOKEN_NUM TOKEN_RBRACKET TOKEN_COMMA TOKEN_REG  */
#line 256 "misc/parser.y"
                        {
				Assembler::mem_dir_offset_literal((yyvsp[-5].num),(yyvsp[-3].num),(yyvsp[0].num));
			}
#line 1484 "src/parser.cpp"
    break;

  case 41: /* instr: TOKEN_LD TOKEN_REG TOKEN_COMMA TOKEN_REG  */
#line 260 "misc/parser.y"
                        {
				Assembler::mem_dir_register((yyvsp[-2].num), (yyvsp[0].num));
			}
#line 1492 "src/parser.cpp"
    break;

  case 42: /* instr: TOKEN_LD TOKEN_LBRACKET TOKEN_REG TOKEN_RBRACKET TOKEN_COMMA TOKEN_REG  */
#line 264 "misc/parser.y"
                        {
				Assembler::mem_ind_register((yyvsp[-3].num),(yyvsp[0].num));
			}
#line 1500 "src/parser.cpp"
    break;

  case 43: /* instr: TOKEN_LD TOKEN_DOLLAR TOKEN_IDENT TOKEN_COMMA TOKEN_REG  */
#line 268 "misc/parser.y"
                        { 
				std::string ident = (yyvsp[-2].ident);
				Assembler::mem_imm_symbol(ident, (yyvsp[0].num));
			}
#line 1509 "src/parser.cpp"
    break;

  case 44: /* instr: TOKEN_LD TOKEN_IDENT TOKEN_COMMA TOKEN_REG  */
#line 273 "misc/parser.y"
                        {
				std::string ident = (yyvsp[-2].ident);
				Assembler::mem_dir_symbol(ident,(yyvsp[0].num));
			}
#line 1518 "src/parser.cpp"
    break;

  case 45: /* instr: TOKEN_ST TOKEN_REG TOKEN_COMMA TOKEN_DOLLAR TOKEN_NUM  */
#line 279 "misc/parser.y"
                        {
				std::cout << "Error! Unvalid instruction: store can not be executed with immediate operand\n";
				Assembler::ass_end = true;
			}
#line 1527 "src/parser.cpp"
    break;

  case 46: /* instr: TOKEN_ST TOKEN_REG TOKEN_COMMA TOKEN_DOLLAR TOKEN_IDENT  */
#line 284 "misc/parser.y"
                        {
				std::cout << "Error! Unvalid instruction: store can not be executed with immediate operand\n";
				Assembler::ass_end = true;
			}
#line 1536 "src/parser.cpp"
    break;

  case 47: /* instr: TOKEN_ST TOKEN_REG TOKEN_COMMA TOKEN_NUM  */
#line 289 "misc/parser.y"
                        {	
				Assembler::st_mem_dir_literal((yyvsp[-2].num),(yyvsp[0].num));
			}
#line 1544 "src/parser.cpp"
    break;

  case 48: /* instr: TOKEN_ST TOKEN_REG TOKEN_COMMA TOKEN_LBRACKET TOKEN_REG TOKEN_RBRACKET  */
#line 293 "misc/parser.y"
                        {	
				Assembler::st_mem_dir_reg((yyvsp[-1].num),(yyvsp[-4].num));
			}
#line 1552 "src/parser.cpp"
    break;

  case 49: /* instr: TOKEN_ST TOKEN_REG TOKEN_COMMA TOKEN_LBRACKET TOKEN_REG TOKEN_PLUS TOKEN_NUM TOKEN_RBRACKET  */
#line 297 "misc/parser.y"
                        {	
				Assembler::st_mem_dir_offset_literal((yyvsp[-3].num),(yyvsp[-1].num),(yyvsp[-6].num));
			}
#line 1560 "src/parser.cpp"
    break;

  case 50: /* instr: TOKEN_ST TOKEN_REG TOKEN_COMMA TOKEN_IDENT  */
#line 301 "misc/parser.y"
                        {	
				std::string ident = (yyvsp[0].ident);
				Assembler::st_mem_dir_symbol(ident,(yyvsp[-2].num));
			}
#line 1569 "src/parser.cpp"
    break;

  case 51: /* instr: TOKEN_ST TOKEN_REG TOKEN_COMMA TOKEN_LBRACKET TOKEN_REG TOKEN_PLUS TOKEN_IDENT TOKEN_RBRACKET  */
#line 306 "misc/parser.y"
                        {
				std::cout << "Error! Value of symbol is not recognized in assembler phase\n";
				Assembler::ass_end = true;
			}
#line 1578 "src/parser.cpp"
    break;

  case 52: /* instr: TOKEN_LD TOKEN_LBRACKET TOKEN_REG TOKEN_PLUS TOKEN_IDENT TOKEN_RBRACKET TOKEN_COMMA TOKEN_REG  */
#line 311 "misc/parser.y"
                        {
				std::cout << "Error! Value of symbol is not recognized in assembler phase\n";
				Assembler::ass_end = true;
			}
#line 1587 "src/parser.cpp"
    break;

  case 53: /* instr: TOKEN_IRET  */
#line 317 "misc/parser.y"
                        { 
				Assembler::mk_iret();
			}
#line 1595 "src/parser.cpp"
    break;

  case 55: /* instr: TOKEN_PUSH TOKEN_REG  */
#line 323 "misc/parser.y"
                        {
				Assembler::push((yyvsp[0].num));
			}
#line 1603 "src/parser.cpp"
    break;

  case 56: /* instr: TOKEN_POP TOKEN_REG  */
#line 327 "misc/parser.y"
                        { 
				Assembler::pop((yyvsp[0].num),false);
			}
#line 1611 "src/parser.cpp"
    break;

  case 57: /* instr: TOKEN_RET  */
#line 332 "misc/parser.y"
                        { 
				Assembler::pop(15, false); 
			}
#line 1619 "src/parser.cpp"
    break;

  case 58: /* instr: TOKEN_JMP TOKEN_IDENT  */
#line 336 "misc/parser.y"
                        {
				std::string ident = (yyvsp[0].ident);
				Assembler::jump_sym(Assembler::instruction::JMP_CODE, 0, 0, ident);
			}
#line 1628 "src/parser.cpp"
    break;

  case 59: /* instr: TOKEN_BEQ TOKEN_REG TOKEN_COMMA TOKEN_REG TOKEN_COMMA TOKEN_IDENT  */
#line 341 "misc/parser.y"
                        {
				std::string ident = (yyvsp[0].ident);
				Assembler::jump_sym(Assembler::instruction::BEQ_CODE, (yyvsp[-4].num), (yyvsp[-2].num), ident);
			}
#line 1637 "src/parser.cpp"
    break;

  case 60: /* instr: TOKEN_BNE TOKEN_REG TOKEN_COMMA TOKEN_REG TOKEN_COMMA TOKEN_IDENT  */
#line 346 "misc/parser.y"
                        {
				std::string ident = (yyvsp[0].ident);
				Assembler::jump_sym(Assembler::instruction::BNE_CODE, (yyvsp[-4].num), (yyvsp[-2].num), ident);
			}
#line 1646 "src/parser.cpp"
    break;

  case 61: /* instr: TOKEN_BGT TOKEN_REG TOKEN_COMMA TOKEN_REG TOKEN_COMMA TOKEN_IDENT  */
#line 351 "misc/parser.y"
                        {
				std::string ident = (yyvsp[0].ident);
				Assembler::jump_sym(Assembler::instruction::BGT_CODE, (yyvsp[-4].num), (yyvsp[-2].num), ident);
			}
#line 1655 "src/parser.cpp"
    break;

  case 62: /* instr: TOKEN_JMP TOKEN_NUM  */
#line 356 "misc/parser.y"
                        {
				Assembler::jump_lit(Assembler::instruction::JMP_CODE, 0, 0,(yyvsp[0].num));
			}
#line 1663 "src/parser.cpp"
    break;

  case 63: /* instr: TOKEN_BEQ TOKEN_REG TOKEN_COMMA TOKEN_REG TOKEN_COMMA TOKEN_NUM  */
#line 360 "misc/parser.y"
                        {
				Assembler::jump_lit(Assembler::instruction::BEQ_CODE, (yyvsp[-4].num), (yyvsp[-2].num), (yyvsp[0].num));
			}
#line 1671 "src/parser.cpp"
    break;

  case 64: /* instr: TOKEN_BNE TOKEN_REG TOKEN_COMMA TOKEN_REG TOKEN_COMMA TOKEN_NUM  */
#line 364 "misc/parser.y"
                        {
				Assembler::jump_lit(Assembler::instruction::BNE_CODE, (yyvsp[-4].num), (yyvsp[-2].num), (yyvsp[0].num));
			}
#line 1679 "src/parser.cpp"
    break;

  case 65: /* instr: TOKEN_BGT TOKEN_REG TOKEN_COMMA TOKEN_REG TOKEN_COMMA TOKEN_NUM  */
#line 368 "misc/parser.y"
                        {
				Assembler::jump_lit(Assembler::instruction::BGT_CODE, (yyvsp[-4].num), (yyvsp[-2].num), (yyvsp[0].num));
			}
#line 1687 "src/parser.cpp"
    break;

  case 66: /* spec_operand: TOKEN_IDENT  */
#line 375 "misc/parser.y"
                {
			std::string ident = (yyvsp[0].ident);
			Assembler::mk_call(ident);
		}
#line 1696 "src/parser.cpp"
    break;

  case 67: /* spec_operand: TOKEN_NUM  */
#line 380 "misc/parser.y"
                {
			Assembler::mk_call((yyvsp[0].num));
		}
#line 1704 "src/parser.cpp"
    break;

  case 68: /* sys_reg: TOKEN_STATUS  */
#line 385 "misc/parser.y"
                     { (yyval.ident) = (yyvsp[0].ident); }
#line 1710 "src/parser.cpp"
    break;

  case 69: /* sys_reg: TOKEN_HANDLER  */
#line 386 "misc/parser.y"
                     { (yyval.ident) = (yyvsp[0].ident); }
#line 1716 "src/parser.cpp"
    break;

  case 70: /* sys_reg: TOKEN_CAUSE  */
#line 387 "misc/parser.y"
                     { (yyval.ident) = (yyvsp[0].ident); }
#line 1722 "src/parser.cpp"
    break;


#line 1726 "src/parser.cpp"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 391 "misc/parser.y"



	void yyerror(const char* s) {
		fprintf(stderr, "Parse error at line %d:\n", line_number);
		exit(1);
	}
