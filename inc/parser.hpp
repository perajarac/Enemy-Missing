/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_INC_PARSER_HPP_INCLUDED
# define YY_YY_INC_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOKEN_HALT = 258,              /* TOKEN_HALT  */
    TOKEN_INT = 259,               /* TOKEN_INT  */
    TOKEN_IRET = 260,              /* TOKEN_IRET  */
    TOKEN_CALL = 261,              /* TOKEN_CALL  */
    TOKEN_RET = 262,               /* TOKEN_RET  */
    TOKEN_JMP = 263,               /* TOKEN_JMP  */
    TOKEN_BEQ = 264,               /* TOKEN_BEQ  */
    TOKEN_BNE = 265,               /* TOKEN_BNE  */
    TOKEN_BGT = 266,               /* TOKEN_BGT  */
    TOKEN_PUSH = 267,              /* TOKEN_PUSH  */
    TOKEN_POP = 268,               /* TOKEN_POP  */
    TOKEN_XCHG = 269,              /* TOKEN_XCHG  */
    TOKEN_ADD = 270,               /* TOKEN_ADD  */
    TOKEN_SUB = 271,               /* TOKEN_SUB  */
    TOKEN_MUL = 272,               /* TOKEN_MUL  */
    TOKEN_DIV = 273,               /* TOKEN_DIV  */
    TOKEN_NOT = 274,               /* TOKEN_NOT  */
    TOKEN_AND = 275,               /* TOKEN_AND  */
    TOKEN_OR = 276,                /* TOKEN_OR  */
    TOKEN_XOR = 277,               /* TOKEN_XOR  */
    TOKEN_SHL = 278,               /* TOKEN_SHL  */
    TOKEN_SHR = 279,               /* TOKEN_SHR  */
    TOKEN_LD = 280,                /* TOKEN_LD  */
    TOKEN_ST = 281,                /* TOKEN_ST  */
    TOKEN_CSRRD = 282,             /* TOKEN_CSRRD  */
    TOKEN_CSRWR = 283,             /* TOKEN_CSRWR  */
    TOKEN_GLOBAL = 284,            /* TOKEN_GLOBAL  */
    TOKEN_EXTERN = 285,            /* TOKEN_EXTERN  */
    TOKEN_SECTION = 286,           /* TOKEN_SECTION  */
    TOKEN_WORD = 287,              /* TOKEN_WORD  */
    TOKEN_SKIP = 288,              /* TOKEN_SKIP  */
    TOKEN_ASCII = 289,             /* TOKEN_ASCII  */
    TOKEN_END = 290,               /* TOKEN_END  */
    TOKEN_IDENT = 291,             /* TOKEN_IDENT  */
    TOKEN_LPAR = 292,              /* TOKEN_LPAR  */
    TOKEN_RPAR = 293,              /* TOKEN_RPAR  */
    TOKEN_LBRACKET = 294,          /* TOKEN_LBRACKET  */
    TOKEN_RBRACKET = 295,          /* TOKEN_RBRACKET  */
    TOKEN_PLUS = 296,              /* TOKEN_PLUS  */
    TOKEN_MINUS = 297,             /* TOKEN_MINUS  */
    TOKEN_PERCENT = 298,           /* TOKEN_PERCENT  */
    TOKEN_DOLLAR = 299,            /* TOKEN_DOLLAR  */
    TOKEN_SEMI = 300,              /* TOKEN_SEMI  */
    TOKEN_COLON = 301,             /* TOKEN_COLON  */
    TOKEN_COMMA = 302,             /* TOKEN_COMMA  */
    TOKEN_REG = 303,               /* TOKEN_REG  */
    TOKEN_STATUS = 304,            /* TOKEN_STATUS  */
    TOKEN_HANDLER = 305,           /* TOKEN_HANDLER  */
    TOKEN_CAUSE = 306,             /* TOKEN_CAUSE  */
    TOKEN_NUM = 307,               /* TOKEN_NUM  */
    TOKEN_STRING = 308             /* TOKEN_STRING  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 24 "misc/parser.y"

		int num;
		int op_code;
		char* ident;
	

#line 124 "inc/parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_INC_PARSER_HPP_INCLUDED  */
