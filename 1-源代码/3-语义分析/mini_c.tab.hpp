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

#ifndef YY_YY_MINI_C_TAB_HPP_INCLUDED
# define YY_YY_MINI_C_TAB_HPP_INCLUDED
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
    LOWER_THAN_ELSE = 258,         /* LOWER_THAN_ELSE  */
    IDENTIFIER = 259,              /* IDENTIFIER  */
    CONSTANT = 260,                /* CONSTANT  */
    STRING_LITERAL = 261,          /* STRING_LITERAL  */
    TYPE_NAME = 262,               /* TYPE_NAME  */
    SIZEOF = 263,                  /* SIZEOF  */
    PTR_OP = 264,                  /* PTR_OP  */
    INC_OP = 265,                  /* INC_OP  */
    DEC_OP = 266,                  /* DEC_OP  */
    LEFT_OP = 267,                 /* LEFT_OP  */
    RIGHT_OP = 268,                /* RIGHT_OP  */
    LE_OP = 269,                   /* LE_OP  */
    GE_OP = 270,                   /* GE_OP  */
    EQ_OP = 271,                   /* EQ_OP  */
    NE_OP = 272,                   /* NE_OP  */
    AND_OP = 273,                  /* AND_OP  */
    OR_OP = 274,                   /* OR_OP  */
    MUL_ASSIGN = 275,              /* MUL_ASSIGN  */
    DIV_ASSIGN = 276,              /* DIV_ASSIGN  */
    MOD_ASSIGN = 277,              /* MOD_ASSIGN  */
    ADD_ASSIGN = 278,              /* ADD_ASSIGN  */
    SUB_ASSIGN = 279,              /* SUB_ASSIGN  */
    LEFT_ASSIGN = 280,             /* LEFT_ASSIGN  */
    RIGHT_ASSIGN = 281,            /* RIGHT_ASSIGN  */
    AND_ASSIGN = 282,              /* AND_ASSIGN  */
    XOR_ASSIGN = 283,              /* XOR_ASSIGN  */
    OR_ASSIGN = 284,               /* OR_ASSIGN  */
    TYPEDEF = 285,                 /* TYPEDEF  */
    EXTERN = 286,                  /* EXTERN  */
    STATIC = 287,                  /* STATIC  */
    AUTO = 288,                    /* AUTO  */
    REGISTER = 289,                /* REGISTER  */
    INLINE = 290,                  /* INLINE  */
    RESTRICT = 291,                /* RESTRICT  */
    CHAR = 292,                    /* CHAR  */
    SHORT = 293,                   /* SHORT  */
    INT = 294,                     /* INT  */
    LONG = 295,                    /* LONG  */
    SIGNED = 296,                  /* SIGNED  */
    UNSIGNED = 297,                /* UNSIGNED  */
    FLOAT = 298,                   /* FLOAT  */
    DOUBLE = 299,                  /* DOUBLE  */
    CONST = 300,                   /* CONST  */
    VOLATILE = 301,                /* VOLATILE  */
    VOID = 302,                    /* VOID  */
    BOOL = 303,                    /* BOOL  */
    COMPLEX = 304,                 /* COMPLEX  */
    IMAGINARY = 305,               /* IMAGINARY  */
    STRUCT = 306,                  /* STRUCT  */
    UNION = 307,                   /* UNION  */
    ENUM = 308,                    /* ENUM  */
    ELLIPSIS = 309,                /* ELLIPSIS  */
    CASE = 310,                    /* CASE  */
    DEFAULT = 311,                 /* DEFAULT  */
    IF = 312,                      /* IF  */
    ELSE = 313,                    /* ELSE  */
    SWITCH = 314,                  /* SWITCH  */
    WHILE = 315,                   /* WHILE  */
    DO = 316,                      /* DO  */
    FOR = 317,                     /* FOR  */
    GOTO = 318,                    /* GOTO  */
    CONTINUE = 319,                /* CONTINUE  */
    BREAK = 320,                   /* BREAK  */
    RETURN = 321                   /* RETURN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 26 "mini_c.y"

    int       ival;   /* 运算符枚举、数值常量等整数值 */
    char     *sval;   /* 标识符、字符串、常量的原始文本 */
    ASTNode  *node;   /* AST 子树 */

#line 136 "mini_c.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;

int yyparse (void);


#endif /* !YY_YY_MINI_C_TAB_HPP_INCLUDED  */
