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
#line 3 "mini_c.y"

#include <stdio.h>
#include "ast.h"            /* 定义了 ASTNode 结构和 new_* 系列函数 */
ASTNode *ast_root = NULL;  /* 最终的 AST 根 */
int yylex(void);
void yyerror(const char *s);

#define LOC(YYL) SourceLoc{ (YYL).first_line, (YYL).first_column }

static ASTNode* make_type_spec_node(int ts)
{
    ASTNode* n = new ASTNode(ASTTag::SPECIFIER);
    n->ival = ts;
    return n;
}


#line 89 "mini_c.tab.cpp"

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

#include "mini_c.tab.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_LOWER_THAN_ELSE = 3,            /* LOWER_THAN_ELSE  */
  YYSYMBOL_IDENTIFIER = 4,                 /* IDENTIFIER  */
  YYSYMBOL_CONSTANT = 5,                   /* CONSTANT  */
  YYSYMBOL_STRING_LITERAL = 6,             /* STRING_LITERAL  */
  YYSYMBOL_TYPE_NAME = 7,                  /* TYPE_NAME  */
  YYSYMBOL_SIZEOF = 8,                     /* SIZEOF  */
  YYSYMBOL_PTR_OP = 9,                     /* PTR_OP  */
  YYSYMBOL_INC_OP = 10,                    /* INC_OP  */
  YYSYMBOL_DEC_OP = 11,                    /* DEC_OP  */
  YYSYMBOL_LEFT_OP = 12,                   /* LEFT_OP  */
  YYSYMBOL_RIGHT_OP = 13,                  /* RIGHT_OP  */
  YYSYMBOL_LE_OP = 14,                     /* LE_OP  */
  YYSYMBOL_GE_OP = 15,                     /* GE_OP  */
  YYSYMBOL_EQ_OP = 16,                     /* EQ_OP  */
  YYSYMBOL_NE_OP = 17,                     /* NE_OP  */
  YYSYMBOL_AND_OP = 18,                    /* AND_OP  */
  YYSYMBOL_OR_OP = 19,                     /* OR_OP  */
  YYSYMBOL_MUL_ASSIGN = 20,                /* MUL_ASSIGN  */
  YYSYMBOL_DIV_ASSIGN = 21,                /* DIV_ASSIGN  */
  YYSYMBOL_MOD_ASSIGN = 22,                /* MOD_ASSIGN  */
  YYSYMBOL_ADD_ASSIGN = 23,                /* ADD_ASSIGN  */
  YYSYMBOL_SUB_ASSIGN = 24,                /* SUB_ASSIGN  */
  YYSYMBOL_LEFT_ASSIGN = 25,               /* LEFT_ASSIGN  */
  YYSYMBOL_RIGHT_ASSIGN = 26,              /* RIGHT_ASSIGN  */
  YYSYMBOL_AND_ASSIGN = 27,                /* AND_ASSIGN  */
  YYSYMBOL_XOR_ASSIGN = 28,                /* XOR_ASSIGN  */
  YYSYMBOL_OR_ASSIGN = 29,                 /* OR_ASSIGN  */
  YYSYMBOL_TYPEDEF = 30,                   /* TYPEDEF  */
  YYSYMBOL_EXTERN = 31,                    /* EXTERN  */
  YYSYMBOL_STATIC = 32,                    /* STATIC  */
  YYSYMBOL_AUTO = 33,                      /* AUTO  */
  YYSYMBOL_REGISTER = 34,                  /* REGISTER  */
  YYSYMBOL_INLINE = 35,                    /* INLINE  */
  YYSYMBOL_RESTRICT = 36,                  /* RESTRICT  */
  YYSYMBOL_CHAR = 37,                      /* CHAR  */
  YYSYMBOL_SHORT = 38,                     /* SHORT  */
  YYSYMBOL_INT = 39,                       /* INT  */
  YYSYMBOL_LONG = 40,                      /* LONG  */
  YYSYMBOL_SIGNED = 41,                    /* SIGNED  */
  YYSYMBOL_UNSIGNED = 42,                  /* UNSIGNED  */
  YYSYMBOL_FLOAT = 43,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 44,                    /* DOUBLE  */
  YYSYMBOL_CONST = 45,                     /* CONST  */
  YYSYMBOL_VOLATILE = 46,                  /* VOLATILE  */
  YYSYMBOL_VOID = 47,                      /* VOID  */
  YYSYMBOL_BOOL = 48,                      /* BOOL  */
  YYSYMBOL_COMPLEX = 49,                   /* COMPLEX  */
  YYSYMBOL_IMAGINARY = 50,                 /* IMAGINARY  */
  YYSYMBOL_STRUCT = 51,                    /* STRUCT  */
  YYSYMBOL_UNION = 52,                     /* UNION  */
  YYSYMBOL_ENUM = 53,                      /* ENUM  */
  YYSYMBOL_ELLIPSIS = 54,                  /* ELLIPSIS  */
  YYSYMBOL_CASE = 55,                      /* CASE  */
  YYSYMBOL_DEFAULT = 56,                   /* DEFAULT  */
  YYSYMBOL_IF = 57,                        /* IF  */
  YYSYMBOL_ELSE = 58,                      /* ELSE  */
  YYSYMBOL_SWITCH = 59,                    /* SWITCH  */
  YYSYMBOL_WHILE = 60,                     /* WHILE  */
  YYSYMBOL_DO = 61,                        /* DO  */
  YYSYMBOL_FOR = 62,                       /* FOR  */
  YYSYMBOL_GOTO = 63,                      /* GOTO  */
  YYSYMBOL_CONTINUE = 64,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 65,                     /* BREAK  */
  YYSYMBOL_RETURN = 66,                    /* RETURN  */
  YYSYMBOL_67_ = 67,                       /* '('  */
  YYSYMBOL_68_ = 68,                       /* ')'  */
  YYSYMBOL_69_ = 69,                       /* '['  */
  YYSYMBOL_70_ = 70,                       /* ']'  */
  YYSYMBOL_71_ = 71,                       /* '.'  */
  YYSYMBOL_72_ = 72,                       /* '{'  */
  YYSYMBOL_73_ = 73,                       /* '}'  */
  YYSYMBOL_74_ = 74,                       /* ','  */
  YYSYMBOL_75_ = 75,                       /* '&'  */
  YYSYMBOL_76_ = 76,                       /* '*'  */
  YYSYMBOL_77_ = 77,                       /* '+'  */
  YYSYMBOL_78_ = 78,                       /* '-'  */
  YYSYMBOL_79_ = 79,                       /* '~'  */
  YYSYMBOL_80_ = 80,                       /* '!'  */
  YYSYMBOL_81_ = 81,                       /* '/'  */
  YYSYMBOL_82_ = 82,                       /* '%'  */
  YYSYMBOL_83_ = 83,                       /* '<'  */
  YYSYMBOL_84_ = 84,                       /* '>'  */
  YYSYMBOL_85_ = 85,                       /* '^'  */
  YYSYMBOL_86_ = 86,                       /* '|'  */
  YYSYMBOL_87_ = 87,                       /* '?'  */
  YYSYMBOL_88_ = 88,                       /* ':'  */
  YYSYMBOL_89_ = 89,                       /* '='  */
  YYSYMBOL_90_ = 90,                       /* ';'  */
  YYSYMBOL_YYACCEPT = 91,                  /* $accept  */
  YYSYMBOL_primary_expression = 92,        /* primary_expression  */
  YYSYMBOL_postfix_expression = 93,        /* postfix_expression  */
  YYSYMBOL_argument_expression_list = 94,  /* argument_expression_list  */
  YYSYMBOL_unary_expression = 95,          /* unary_expression  */
  YYSYMBOL_unary_operator = 96,            /* unary_operator  */
  YYSYMBOL_cast_expression = 97,           /* cast_expression  */
  YYSYMBOL_multiplicative_expression = 98, /* multiplicative_expression  */
  YYSYMBOL_additive_expression = 99,       /* additive_expression  */
  YYSYMBOL_shift_expression = 100,         /* shift_expression  */
  YYSYMBOL_relational_expression = 101,    /* relational_expression  */
  YYSYMBOL_equality_expression = 102,      /* equality_expression  */
  YYSYMBOL_and_expression = 103,           /* and_expression  */
  YYSYMBOL_exclusive_or_expression = 104,  /* exclusive_or_expression  */
  YYSYMBOL_inclusive_or_expression = 105,  /* inclusive_or_expression  */
  YYSYMBOL_logical_and_expression = 106,   /* logical_and_expression  */
  YYSYMBOL_logical_or_expression = 107,    /* logical_or_expression  */
  YYSYMBOL_conditional_expression = 108,   /* conditional_expression  */
  YYSYMBOL_assignment_expression = 109,    /* assignment_expression  */
  YYSYMBOL_assignment_operator = 110,      /* assignment_operator  */
  YYSYMBOL_expression = 111,               /* expression  */
  YYSYMBOL_constant_expression = 112,      /* constant_expression  */
  YYSYMBOL_declaration = 113,              /* declaration  */
  YYSYMBOL_declaration_specifiers = 114,   /* declaration_specifiers  */
  YYSYMBOL_init_declarator_list = 115,     /* init_declarator_list  */
  YYSYMBOL_init_declarator = 116,          /* init_declarator  */
  YYSYMBOL_storage_class_specifier = 117,  /* storage_class_specifier  */
  YYSYMBOL_type_specifier = 118,           /* type_specifier  */
  YYSYMBOL_struct_or_union_specifier = 119, /* struct_or_union_specifier  */
  YYSYMBOL_struct_or_union = 120,          /* struct_or_union  */
  YYSYMBOL_struct_declaration_list = 121,  /* struct_declaration_list  */
  YYSYMBOL_struct_declaration = 122,       /* struct_declaration  */
  YYSYMBOL_specifier_qualifier_list = 123, /* specifier_qualifier_list  */
  YYSYMBOL_struct_declarator_list = 124,   /* struct_declarator_list  */
  YYSYMBOL_struct_declarator = 125,        /* struct_declarator  */
  YYSYMBOL_enum_specifier = 126,           /* enum_specifier  */
  YYSYMBOL_enumerator_list = 127,          /* enumerator_list  */
  YYSYMBOL_enumerator = 128,               /* enumerator  */
  YYSYMBOL_type_qualifier = 129,           /* type_qualifier  */
  YYSYMBOL_function_specifier = 130,       /* function_specifier  */
  YYSYMBOL_declarator = 131,               /* declarator  */
  YYSYMBOL_direct_declarator = 132,        /* direct_declarator  */
  YYSYMBOL_pointer = 133,                  /* pointer  */
  YYSYMBOL_type_qualifier_list = 134,      /* type_qualifier_list  */
  YYSYMBOL_parameter_type_list = 135,      /* parameter_type_list  */
  YYSYMBOL_parameter_list = 136,           /* parameter_list  */
  YYSYMBOL_parameter_declaration = 137,    /* parameter_declaration  */
  YYSYMBOL_identifier_list = 138,          /* identifier_list  */
  YYSYMBOL_type_name = 139,                /* type_name  */
  YYSYMBOL_abstract_declarator = 140,      /* abstract_declarator  */
  YYSYMBOL_direct_abstract_declarator = 141, /* direct_abstract_declarator  */
  YYSYMBOL_initializer = 142,              /* initializer  */
  YYSYMBOL_initializer_list = 143,         /* initializer_list  */
  YYSYMBOL_designation = 144,              /* designation  */
  YYSYMBOL_designator_list = 145,          /* designator_list  */
  YYSYMBOL_designator = 146,               /* designator  */
  YYSYMBOL_statement = 147,                /* statement  */
  YYSYMBOL_labeled_statement = 148,        /* labeled_statement  */
  YYSYMBOL_compound_statement = 149,       /* compound_statement  */
  YYSYMBOL_block_item_list = 150,          /* block_item_list  */
  YYSYMBOL_block_item = 151,               /* block_item  */
  YYSYMBOL_expression_statement = 152,     /* expression_statement  */
  YYSYMBOL_selection_statement = 153,      /* selection_statement  */
  YYSYMBOL_iteration_statement = 154,      /* iteration_statement  */
  YYSYMBOL_jump_statement = 155,           /* jump_statement  */
  YYSYMBOL_translation_unit = 156,         /* translation_unit  */
  YYSYMBOL_external_declaration = 157,     /* external_declaration  */
  YYSYMBOL_function_definition = 158,      /* function_definition  */
  YYSYMBOL_declaration_list = 159          /* declaration_list  */
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
typedef yytype_int16 yy_state_t;

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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  55
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1631

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  91
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  69
/* YYNRULES -- Number of rules.  */
#define YYNRULES  238
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  400

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   321


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
       2,     2,     2,    80,     2,     2,     2,    82,    75,     2,
      67,    68,    76,    77,    74,    78,    71,    81,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    88,    90,
      83,    89,    84,    87,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    69,     2,    70,    85,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    72,    86,    73,    79,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   144,   144,   145,   146,   147,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   165,   166,   170,   171,
     172,   173,   174,   175,   179,   180,   181,   182,   183,   184,
     189,   190,   194,   195,   196,   197,   202,   203,   204,   209,
     210,   211,   216,   217,   218,   219,   220,   225,   226,   227,
     233,   235,   241,   243,   249,   251,   257,   259,   265,   267,
     273,   275,   281,   283,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   303,   305,   311,   317,   319,
     325,   327,   329,   331,   333,   335,   337,   339,   345,   347,
     353,   355,   361,   362,   363,   364,   365,   369,   370,   371,
     372,   373,   374,   375,   376,   377,   378,   379,   380,   381,
     383,   385,   390,   392,   394,   401,   402,   406,   408,   414,
     419,   421,   423,   425,   431,   433,   439,   441,   443,   449,
     451,   453,   455,   457,   463,   465,   471,   473,   479,   481,
     483,   488,   493,   495,   501,   503,   505,   507,   509,   511,
     513,   515,   517,   519,   521,   523,   525,   531,   533,   535,
     537,   543,   545,   550,   552,   558,   560,   566,   568,   570,
     576,   578,   583,   585,   591,   593,   595,   601,   603,   605,
     607,   609,   611,   613,   615,   617,   619,   621,   627,   629,
     631,   637,   639,   641,   643,   649,   655,   657,   662,   664,
     670,   671,   672,   673,   674,   675,   680,   682,   684,   689,
     691,   697,   699,   705,   707,   713,   715,   720,   722,   724,
     729,   731,   733,   735,   737,   739,   745,   747,   749,   751,
     753,   759,   761,   766,   768,   774,   776,   782,   784
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
  "\"end of file\"", "error", "\"invalid token\"", "LOWER_THAN_ELSE",
  "IDENTIFIER", "CONSTANT", "STRING_LITERAL", "TYPE_NAME", "SIZEOF",
  "PTR_OP", "INC_OP", "DEC_OP", "LEFT_OP", "RIGHT_OP", "LE_OP", "GE_OP",
  "EQ_OP", "NE_OP", "AND_OP", "OR_OP", "MUL_ASSIGN", "DIV_ASSIGN",
  "MOD_ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN", "LEFT_ASSIGN", "RIGHT_ASSIGN",
  "AND_ASSIGN", "XOR_ASSIGN", "OR_ASSIGN", "TYPEDEF", "EXTERN", "STATIC",
  "AUTO", "REGISTER", "INLINE", "RESTRICT", "CHAR", "SHORT", "INT", "LONG",
  "SIGNED", "UNSIGNED", "FLOAT", "DOUBLE", "CONST", "VOLATILE", "VOID",
  "BOOL", "COMPLEX", "IMAGINARY", "STRUCT", "UNION", "ENUM", "ELLIPSIS",
  "CASE", "DEFAULT", "IF", "ELSE", "SWITCH", "WHILE", "DO", "FOR", "GOTO",
  "CONTINUE", "BREAK", "RETURN", "'('", "')'", "'['", "']'", "'.'", "'{'",
  "'}'", "','", "'&'", "'*'", "'+'", "'-'", "'~'", "'!'", "'/'", "'%'",
  "'<'", "'>'", "'^'", "'|'", "'?'", "':'", "'='", "';'", "$accept",
  "primary_expression", "postfix_expression", "argument_expression_list",
  "unary_expression", "unary_operator", "cast_expression",
  "multiplicative_expression", "additive_expression", "shift_expression",
  "relational_expression", "equality_expression", "and_expression",
  "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_or_expression",
  "conditional_expression", "assignment_expression", "assignment_operator",
  "expression", "constant_expression", "declaration",
  "declaration_specifiers", "init_declarator_list", "init_declarator",
  "storage_class_specifier", "type_specifier", "struct_or_union_specifier",
  "struct_or_union", "struct_declaration_list", "struct_declaration",
  "specifier_qualifier_list", "struct_declarator_list",
  "struct_declarator", "enum_specifier", "enumerator_list", "enumerator",
  "type_qualifier", "function_specifier", "declarator",
  "direct_declarator", "pointer", "type_qualifier_list",
  "parameter_type_list", "parameter_list", "parameter_declaration",
  "identifier_list", "type_name", "abstract_declarator",
  "direct_abstract_declarator", "initializer", "initializer_list",
  "designation", "designator_list", "designator", "statement",
  "labeled_statement", "compound_statement", "block_item_list",
  "block_item", "expression_statement", "selection_statement",
  "iteration_statement", "jump_statement", "translation_unit",
  "external_declaration", "function_definition", "declaration_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-309)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1578,  -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,
    -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,
    -309,  -309,  -309,  -309,  -309,    46,  -309,    26,  1578,  1578,
    -309,    47,  -309,  1578,  1578,  1483,  -309,  -309,   -17,    62,
    -309,    58,   110,  -309,   -29,  -309,   313,    66,    22,  -309,
    -309,    13,   331,  -309,  -309,  -309,  -309,    62,     1,   178,
    -309,    83,  -309,  -309,   110,    58,  -309,   393,   913,  -309,
      26,  -309,  1332,  1382,   725,    66,   331,   331,  1267,  -309,
      53,   331,   193,  1076,  -309,    15,  -309,  -309,  -309,  -309,
      14,    96,  -309,  -309,  1092,  1169,  1169,  1076,   101,   109,
     130,   162,   597,   166,   216,   152,   158,   565,   702,  -309,
    -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,    73,   697,
    1076,  -309,   112,   -41,   258,    54,   265,   180,   179,   182,
     271,    35,  -309,  -309,   -18,  -309,  -309,  -309,  -309,   470,
    -309,  -309,  -309,  -309,  -309,  -309,   822,  -309,  -309,  -309,
    -309,  -309,  -309,    48,   215,   224,  -309,    33,   103,  -309,
     238,   242,   779,  1285,  -309,  -309,  -309,  1076,   -10,  -309,
     225,  -309,  -309,    19,  -309,  -309,  -309,  -309,  -309,   597,
     702,  -309,   702,  -309,  -309,   229,   597,  1076,  1076,  1076,
     243,   547,   228,  -309,  -309,  -309,    -9,    84,   106,   251,
     317,  -309,  -309,   928,  1076,   318,  -309,  -309,  -309,  -309,
    -309,  -309,  -309,  -309,  -309,  -309,  -309,  1076,  -309,  1076,
    1076,  1076,  1076,  1076,  1076,  1076,  1076,  1076,  1076,  1076,
    1076,  1076,  1076,  1076,  1076,  1076,  1076,  1076,  1076,  -309,
    -309,  -309,  1076,   319,  -309,   218,   913,    88,  -309,  1153,
     942,  -309,    63,  -309,   129,  -309,  1530,  -309,   320,   899,
    -309,  -309,  1076,  -309,   255,   256,  -309,  -309,    53,  -309,
    1076,  -309,  -309,   261,   262,   597,  -309,    86,   100,   117,
     266,   625,   625,  -309,  -309,  -309,  1220,   176,  -309,   957,
    -309,  -309,   150,  -309,   170,  -309,  -309,  -309,  -309,  -309,
     112,   112,   -41,   -41,   258,   258,   258,   258,    54,    54,
     265,   180,   179,   182,   271,   -28,  -309,   264,  -309,  -309,
     159,  -309,  -309,  -309,  -309,   267,   269,  -309,   270,   272,
     129,  1429,  1034,  -309,  -309,  -309,   316,   322,  -309,  -309,
    -309,  -309,   260,   260,  -309,   597,   597,   597,  1076,  1048,
    1062,   822,  -309,  -309,  1076,  -309,  1076,  -309,  -309,  -309,
     913,  -309,  -309,  -309,  -309,  -309,   321,  -309,   323,   324,
    -309,  -309,   281,  -309,  -309,   151,   597,   153,   597,   173,
     222,  -309,  -309,  -309,  -309,  -309,  -309,   597,   297,  -309,
     597,  -309,   597,  -309,   802,  -309,  -309,  -309,  -309,  -309
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   111,    92,    93,    94,    95,    96,   141,   139,    98,
      99,   100,   101,   104,   105,   102,   103,   138,   140,    97,
     106,   107,   108,   115,   116,     0,   234,     0,    80,    82,
     109,     0,   110,    84,    86,     0,   231,   233,   133,     0,
     144,     0,   157,    78,     0,    88,    90,   143,     0,    81,
      83,   114,     0,    85,    87,     1,   232,     0,   136,     0,
     134,     0,   161,   159,   158,     0,    79,     0,     0,   237,
       0,   236,     0,     0,     0,   142,     0,   121,     0,   117,
       0,   123,     0,     0,   129,     0,   145,   162,   160,    89,
      90,     2,     3,     4,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   209,
      24,    25,    26,    27,    28,    29,   215,     6,    18,    30,
       0,    32,    36,    39,    42,    47,    50,    52,    54,    56,
      58,    60,    62,    75,     0,   213,   214,   200,   201,     0,
     211,   202,   203,   204,   205,     2,     0,   188,    91,   238,
     235,   170,   156,   169,     0,   163,   165,     0,     0,   153,
      25,     0,     0,     0,   120,   113,   118,     0,     0,   124,
     126,   122,   130,     0,    30,    77,   137,   131,   135,     0,
       0,    22,     0,    19,    20,     0,     0,     0,     0,     0,
       0,     0,     0,   227,   228,   229,     0,     0,   172,     0,
       0,    12,    13,     0,     0,     0,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    64,     0,    21,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   216,
     210,   212,     0,     0,   191,     0,     0,     0,   196,     0,
       0,   167,   174,   168,   175,   154,     0,   155,     0,     0,
     152,   148,     0,   147,    25,     0,   112,   127,     0,   119,
       0,   132,   206,     0,     0,     0,   208,     0,     0,     0,
       0,     0,     0,   226,   230,     5,     0,   174,   173,     0,
      11,     8,     0,    16,     0,    10,    63,    33,    34,    35,
      37,    38,    40,    41,    45,    46,    43,    44,    48,    49,
      51,    53,    55,    57,    59,     0,    76,     0,   199,   189,
       0,   192,   195,   197,   184,     0,     0,   178,    25,     0,
     176,     0,     0,   164,   166,   171,     0,     0,   151,   146,
     125,   128,    23,     0,   207,     0,     0,     0,     0,     0,
       0,     0,    31,     9,     0,     7,     0,   198,   190,   193,
       0,   185,   177,   182,   179,   186,     0,   180,    25,     0,
     149,   150,   217,   219,   220,     0,     0,     0,     0,     0,
       0,    17,    61,   194,   187,   183,   181,     0,     0,   224,
       0,   222,     0,    14,     0,   218,   221,   225,   223,    15
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -309,  -309,  -309,  -309,   -20,  -309,  -111,    78,    91,    51,
      75,   156,   157,   171,   172,   174,  -309,   -80,   -67,  -309,
     -76,   -89,   -25,     0,  -309,   341,  -309,   -37,  -309,  -309,
     332,   -58,   -59,  -309,   141,  -309,   354,   -74,   233,  -309,
     -22,   -35,   -26,   -64,   -69,  -309,   160,  -309,    81,  -128,
    -228,   -66,    61,  -308,  -309,   167,   -88,  -309,   -19,  -309,
     278,  -185,  -309,  -309,  -309,  -309,   383,  -309,  -309
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,   117,   118,   292,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   217,
     134,   176,    26,    70,    44,    45,    28,    29,    30,    31,
      78,    79,    80,   168,   169,    32,    59,    60,    33,    34,
      61,    47,    48,    64,   325,   155,   156,   157,   199,   326,
     254,   244,   245,   246,   247,   248,   136,   137,   138,   139,
     140,   141,   142,   143,   144,    35,    36,    37,    72
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      27,   147,   148,   175,   154,    46,   282,   161,   185,   218,
     162,   178,   360,    75,   190,    77,    63,   175,   164,    58,
     166,    69,   171,    58,   330,   253,    40,    71,    49,    50,
      40,   196,   197,    53,    54,    27,   222,   223,    88,    77,
      77,    77,   135,    90,    77,    65,   238,   149,    90,   198,
      38,    51,    40,   150,   236,    57,   238,    40,   170,   330,
     356,    66,    40,   174,   268,   238,    58,    40,   226,   227,
     288,    77,   239,   153,   181,   183,   184,   174,   267,   147,
     269,   284,   200,   201,   202,    76,   360,   175,   177,    41,
      83,   272,   271,    41,   259,   265,   349,   350,   276,   178,
     174,   257,    42,    68,   197,   166,   197,   258,   297,   298,
     299,   277,   278,   279,   135,   249,    43,   250,    39,    52,
      41,   198,   237,   198,    42,    41,    77,   252,   294,    42,
     249,   251,   250,    73,    42,    74,   293,   228,   229,     8,
     203,   167,   204,    77,   205,    77,     8,   174,    17,    18,
     296,    86,   285,   317,   345,    17,    18,   242,   238,   243,
     238,   315,   175,   145,    92,    93,   281,    94,   346,    95,
      96,   316,   287,   286,   238,   250,   187,   322,   352,   147,
     321,   341,    42,   329,   179,   347,    42,   344,   219,   186,
     175,   238,   336,   220,   221,   337,   331,   188,   332,   174,
     174,   174,   174,   174,   174,   174,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   174,   174,    75,   353,   388,
     192,   390,   174,   252,   354,   238,   108,   238,   242,   189,
     243,   146,   358,   191,   110,   111,   112,   113,   114,   115,
     355,   392,   193,   286,   238,   250,   170,   238,   194,   153,
     174,    84,    85,   147,   359,   232,   153,   372,   373,   374,
     287,   273,   366,   274,   233,   369,   172,   173,   234,   174,
     224,   225,   375,   377,   379,    62,   382,   304,   305,   306,
     307,   230,   231,   255,   147,    81,   153,   381,   389,   235,
     391,   319,   320,   147,   383,   393,   394,    87,   256,   395,
     300,   301,   397,   280,   398,   308,   309,    62,   260,    81,
      81,    81,   261,   270,    81,   302,   303,   275,   283,   289,
       1,   290,   295,   318,   335,   338,   339,   147,   359,   342,
     343,   153,   351,   348,   357,   361,   174,   362,     1,   387,
     363,    81,   364,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    67,   370,   396,   310,   384,
     311,    62,   371,   385,   386,    87,    81,    91,    92,    93,
       1,    94,    68,    95,    96,   312,    89,   313,   163,   340,
     314,    82,   380,    81,   323,    81,   334,   241,    56,     0,
       0,     0,     0,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,     0,    97,    98,
      99,     0,   100,   101,   102,   103,   104,   105,   106,   107,
     108,     0,     0,     0,     0,    67,   109,     0,   110,   111,
     112,   113,   114,   115,    91,    92,    93,     1,    94,     0,
      95,    96,     0,   116,     0,     0,     0,     0,     0,     0,
       0,     0,    87,     0,     0,     0,     0,     0,     0,     0,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,     0,    97,    98,    99,     0,   100,
     101,   102,   103,   104,   105,   106,   107,   108,     0,     0,
       0,     0,    67,   240,     0,   110,   111,   112,   113,   114,
     115,   145,    92,    93,     1,    94,     0,    95,    96,     0,
     116,     0,     0,     0,     0,     0,     0,     0,     0,   145,
      92,    93,     0,    94,     0,    95,    96,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    91,    92,    93,     0,    94,     0,    95,    96,     0,
       0,     0,     0,     0,   108,     0,     0,     0,     0,     0,
       0,     0,   110,   111,   112,   113,   114,   115,     0,   145,
      92,    93,   108,    94,     0,    95,    96,   116,     0,     0,
     110,   111,   112,   113,   114,   115,     0,     0,     0,     0,
       0,     0,    97,    98,    99,   195,   100,   101,   102,   103,
     104,   105,   106,   107,   108,     0,     0,     0,     0,    67,
       0,     0,   110,   111,   112,   113,   114,   115,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   116,     0,     0,
       0,     0,   108,     0,     0,     0,     0,     0,     0,     0,
     110,   111,   112,   113,   114,   115,   145,    92,    93,     1,
      94,     0,    95,    96,     0,   116,     0,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,     0,     0,   145,
      92,    93,     0,    94,     0,    95,    96,     0,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,     0,   158,     0,     0,
       0,     8,     0,     0,     0,     0,     0,     0,     0,   108,
      17,    18,     0,     0,     0,     0,     0,   110,   111,   112,
     113,   114,   115,   145,    92,    93,   216,    94,     0,    95,
      96,     0,   108,     0,     0,   159,     0,     0,     0,     0,
     110,   160,   112,   113,   114,   115,   145,    92,    93,     0,
      94,   262,    95,    96,     0,     8,     0,     0,     0,     0,
       0,     0,     0,     0,    17,    18,   145,    92,    93,     0,
      94,     0,    95,    96,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   108,     0,     0,   263,
       0,     0,     0,     0,   110,   264,   112,   113,   114,   115,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   108,
       0,   242,     0,   243,   146,   399,     0,   110,   111,   112,
     113,   114,   115,     0,     0,     0,     0,     0,     0,   108,
       0,   242,     0,   243,   146,     0,     0,   110,   111,   112,
     113,   114,   115,   145,    92,    93,     0,    94,     0,    95,
      96,     0,     0,     0,     0,     0,     0,   145,    92,    93,
       0,    94,     0,    95,    96,     0,     0,     0,     0,     0,
       0,     0,   145,    92,    93,     8,    94,     0,    95,    96,
       0,     0,     0,     0,    17,    18,   145,    92,    93,     0,
      94,     0,    95,    96,     0,     0,     0,     0,     0,     0,
       0,   145,    92,    93,     0,    94,   108,    95,    96,     0,
       0,     0,     0,     0,   110,   111,   112,   113,   114,   115,
     108,     0,     0,     0,     0,   146,     0,     0,   110,   111,
     112,   113,   114,   115,     0,   108,   291,     0,     0,     0,
       0,     0,     0,   110,   111,   112,   113,   114,   115,   108,
       0,     0,   327,     0,     0,     0,     0,   110,   328,   112,
     113,   114,   115,     0,   108,     0,     0,     0,     0,   351,
       0,     0,   110,   111,   112,   113,   114,   115,   145,    92,
      93,     0,    94,     0,    95,    96,     0,     0,     0,     0,
       0,     0,   145,    92,    93,     0,    94,     0,    95,    96,
       0,     0,     0,     0,     0,     0,   145,    92,    93,     0,
      94,     0,    95,    96,     0,     0,     0,     0,     0,     0,
     145,    92,    93,     0,    94,     0,    95,    96,     0,     0,
       0,     0,     0,     0,     0,     0,   145,    92,    93,     0,
      94,   108,    95,    96,   367,     0,     0,     0,     0,   110,
     368,   112,   113,   114,   115,   108,   376,     0,     0,     0,
       0,     0,     0,   110,   111,   112,   113,   114,   115,   108,
     378,     0,     0,     0,     0,     0,     0,   110,   111,   112,
     113,   114,   115,   108,     0,     0,     0,     0,     0,     0,
       0,   110,   111,   112,   113,   114,   115,    40,     0,   180,
       1,     0,     0,     0,     0,     0,     0,   110,   111,   112,
     113,   114,   115,   145,    92,    93,     0,    94,     0,    95,
      96,     0,     0,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     249,   324,   250,     0,     0,     0,     0,     1,     0,    42,
       0,     0,     0,     0,     0,     0,   182,     0,     0,     0,
       0,     0,     0,     0,   110,   111,   112,   113,   114,   115,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,     1,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   286,   324,   250,
       0,     0,     1,     0,     0,     0,    42,     0,     0,     0,
       0,     0,     0,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,     1,
     165,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   266,     0,
       0,     0,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,   151,     0,     0,     1,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    67,     0,     0,     0,     0,     0,
       0,     0,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,     1,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     152,     0,     0,     0,     0,     0,     0,     0,     0,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    55,     0,     0,     0,     0,     0,     0,
       1,     0,     0,     0,     0,     0,     0,   365,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,     1,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,   333,     1,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25
};

static const yytype_int16 yycheck[] =
{
       0,    68,    68,    83,    73,    27,   191,    74,    97,   120,
      74,    85,   320,    48,   102,    52,    42,    97,    77,     4,
      78,    46,    81,     4,   252,   153,     4,    46,    28,    29,
       4,   107,   108,    33,    34,    35,    77,    78,    64,    76,
      77,    78,    67,    65,    81,    74,    74,    72,    70,   108,
       4,     4,     4,    72,    19,    72,    74,     4,    80,   287,
      88,    90,     4,    83,    74,    74,     4,     4,    14,    15,
     198,   108,    90,    73,    94,    95,    96,    97,   167,   146,
      90,    90,     9,    10,    11,    72,   394,   167,    73,    67,
      89,   179,    73,    67,   158,   162,   281,   282,   186,   173,
     120,    68,    76,    89,   180,   163,   182,    74,   219,   220,
     221,   187,   188,   189,   139,    67,    90,    69,    72,    72,
      67,   180,    87,   182,    76,    67,   163,   153,   204,    76,
      67,   153,    69,    67,    76,    69,   203,    83,    84,    36,
      67,    88,    69,   180,    71,   182,    36,   167,    45,    46,
     217,    68,    68,   242,    68,    45,    46,    69,    74,    71,
      74,   237,   242,     4,     5,     6,   191,     8,    68,    10,
      11,   238,   198,    67,    74,    69,    67,    89,   289,   246,
     246,   270,    76,   250,    88,    68,    76,   275,    76,    88,
     270,    74,   259,    81,    82,   262,    67,    67,    69,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   252,    68,    68,
       4,    68,   242,   249,    74,    74,    67,    74,    69,    67,
      71,    72,    73,    67,    75,    76,    77,    78,    79,    80,
      70,    68,    90,    67,    74,    69,   268,    74,    90,   249,
     270,    73,    74,   320,   320,    75,   256,   345,   346,   347,
     286,   180,   331,   182,    85,   332,    73,    74,    86,   289,
      12,    13,   348,   349,   350,    42,   356,   226,   227,   228,
     229,    16,    17,    68,   351,    52,   286,   354,   376,    18,
     378,    73,    74,   360,   360,    73,    74,    64,    74,   387,
     222,   223,   390,    60,   392,   230,   231,    74,    70,    76,
      77,    78,    70,    88,    81,   224,   225,    88,    90,    68,
       7,     4,     4,     4,     4,    70,    70,   394,   394,    68,
      68,   331,    72,    67,    70,    68,   356,    68,     7,    58,
      70,   108,    70,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    72,    70,    90,   232,    68,
     233,   158,    70,    70,    70,   162,   163,     4,     5,     6,
       7,     8,    89,    10,    11,   234,    65,   235,    76,   268,
     236,    57,   351,   180,   247,   182,   256,   139,    35,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    -1,    55,    56,
      57,    -1,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    -1,    -1,    -1,    -1,    72,    73,    -1,    75,    76,
      77,    78,    79,    80,     4,     5,     6,     7,     8,    -1,
      10,    11,    -1,    90,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   259,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    -1,    55,    56,    57,    -1,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    -1,    -1,
      -1,    -1,    72,    73,    -1,    75,    76,    77,    78,    79,
      80,     4,     5,     6,     7,     8,    -1,    10,    11,    -1,
      90,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     4,
       5,     6,    -1,     8,    -1,    10,    11,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,     4,     5,     6,    -1,     8,    -1,    10,    11,    -1,
      -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    76,    77,    78,    79,    80,    -1,     4,
       5,     6,    67,     8,    -1,    10,    11,    90,    -1,    -1,
      75,    76,    77,    78,    79,    80,    -1,    -1,    -1,    -1,
      -1,    -1,    55,    56,    57,    90,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    -1,    -1,    -1,    -1,    72,
      -1,    -1,    75,    76,    77,    78,    79,    80,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    90,    -1,    -1,
      -1,    -1,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      75,    76,    77,    78,    79,    80,     4,     5,     6,     7,
       8,    -1,    10,    11,    -1,    90,    -1,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    -1,    -1,     4,
       5,     6,    -1,     8,    -1,    10,    11,    -1,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    -1,    32,    -1,    -1,
      -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      45,    46,    -1,    -1,    -1,    -1,    -1,    75,    76,    77,
      78,    79,    80,     4,     5,     6,    89,     8,    -1,    10,
      11,    -1,    67,    -1,    -1,    70,    -1,    -1,    -1,    -1,
      75,    76,    77,    78,    79,    80,     4,     5,     6,    -1,
       8,    32,    10,    11,    -1,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    45,    46,     4,     5,     6,    -1,
       8,    -1,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,    70,
      -1,    -1,    -1,    -1,    75,    76,    77,    78,    79,    80,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      -1,    69,    -1,    71,    72,    73,    -1,    75,    76,    77,
      78,    79,    80,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      -1,    69,    -1,    71,    72,    -1,    -1,    75,    76,    77,
      78,    79,    80,     4,     5,     6,    -1,     8,    -1,    10,
      11,    -1,    -1,    -1,    -1,    -1,    -1,     4,     5,     6,
      -1,     8,    -1,    10,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     4,     5,     6,    36,     8,    -1,    10,    11,
      -1,    -1,    -1,    -1,    45,    46,     4,     5,     6,    -1,
       8,    -1,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     4,     5,     6,    -1,     8,    67,    10,    11,    -1,
      -1,    -1,    -1,    -1,    75,    76,    77,    78,    79,    80,
      67,    -1,    -1,    -1,    -1,    72,    -1,    -1,    75,    76,
      77,    78,    79,    80,    -1,    67,    68,    -1,    -1,    -1,
      -1,    -1,    -1,    75,    76,    77,    78,    79,    80,    67,
      -1,    -1,    70,    -1,    -1,    -1,    -1,    75,    76,    77,
      78,    79,    80,    -1,    67,    -1,    -1,    -1,    -1,    72,
      -1,    -1,    75,    76,    77,    78,    79,    80,     4,     5,
       6,    -1,     8,    -1,    10,    11,    -1,    -1,    -1,    -1,
      -1,    -1,     4,     5,     6,    -1,     8,    -1,    10,    11,
      -1,    -1,    -1,    -1,    -1,    -1,     4,     5,     6,    -1,
       8,    -1,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,
       4,     5,     6,    -1,     8,    -1,    10,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     4,     5,     6,    -1,
       8,    67,    10,    11,    70,    -1,    -1,    -1,    -1,    75,
      76,    77,    78,    79,    80,    67,    68,    -1,    -1,    -1,
      -1,    -1,    -1,    75,    76,    77,    78,    79,    80,    67,
      68,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,    77,
      78,    79,    80,    67,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    75,    76,    77,    78,    79,    80,     4,    -1,    67,
       7,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,    77,
      78,    79,    80,     4,     5,     6,    -1,     8,    -1,    10,
      11,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      67,    68,    69,    -1,    -1,    -1,    -1,     7,    -1,    76,
      -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    75,    76,    77,    78,    79,    80,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,     7,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,
      -1,    -1,     7,    -1,    -1,    -1,    76,    -1,    -1,    -1,
      -1,    -1,    -1,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,     7,
      73,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,     4,    -1,    -1,     7,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    72,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,     7,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,     0,    -1,    -1,    -1,    -1,    -1,    -1,
       7,    -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,     7,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,     7,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,   113,   114,   117,   118,
     119,   120,   126,   129,   130,   156,   157,   158,     4,    72,
       4,    67,    76,    90,   115,   116,   131,   132,   133,   114,
     114,     4,    72,   114,   114,     0,   157,    72,     4,   127,
     128,   131,   129,   133,   134,    74,    90,    72,    89,   113,
     114,   149,   159,    67,    69,   132,    72,   118,   121,   122,
     123,   129,   127,    89,    73,    74,    68,   129,   133,   116,
     131,     4,     5,     6,     8,    10,    11,    55,    56,    57,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    73,
      75,    76,    77,    78,    79,    80,    90,    92,    93,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   111,   113,   147,   148,   149,   150,
     151,   152,   153,   154,   155,     4,    72,   109,   142,   113,
     149,     4,    68,   114,   135,   136,   137,   138,    32,    70,
      76,   109,   134,   121,   123,    73,   122,    88,   124,   125,
     131,   123,    73,    74,    95,   108,   112,    73,   128,    88,
      67,    95,    67,    95,    95,   112,    88,    67,    67,    67,
     147,    67,     4,    90,    90,    90,   111,   111,   123,   139,
       9,    10,    11,    67,    69,    71,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    89,   110,    97,    76,
      81,    82,    77,    78,    12,    13,    14,    15,    83,    84,
      16,    17,    75,    85,    86,    18,    19,    87,    74,    90,
      73,   151,    69,    71,   142,   143,   144,   145,   146,    67,
      69,   131,   133,   140,   141,    68,    74,    68,    74,   134,
      70,    70,    32,    70,    76,   109,    73,   112,    74,    90,
      88,    73,   147,   139,   139,    88,   147,   111,   111,   111,
      60,   113,   152,    90,    90,    68,    67,   133,   140,    68,
       4,    68,    94,   109,   111,     4,   109,    97,    97,    97,
      98,    98,    99,    99,   100,   100,   100,   100,   101,   101,
     102,   103,   104,   105,   106,   111,   109,   112,     4,    73,
      74,   142,    89,   146,    68,   135,   140,    70,    76,   109,
     141,    67,    69,    54,   137,     4,   109,   109,    70,    70,
     125,   112,    68,    68,   147,    68,    68,    68,    67,   152,
     152,    72,    97,    68,    74,    70,    88,    70,    73,   142,
     144,    68,    68,    70,    70,    68,   135,    70,    76,   109,
      70,    70,   147,   147,   147,   111,    68,   111,    68,   111,
     143,   109,   108,   142,    68,    70,    70,    58,    68,   147,
      68,   147,    68,    73,    74,   147,    90,   147,   147,    73
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    91,    92,    92,    92,    92,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    94,    94,    95,    95,
      95,    95,    95,    95,    96,    96,    96,    96,    96,    96,
      97,    97,    98,    98,    98,    98,    99,    99,    99,   100,
     100,   100,   101,   101,   101,   101,   101,   102,   102,   102,
     103,   103,   104,   104,   105,   105,   106,   106,   107,   107,
     108,   108,   109,   109,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   111,   111,   112,   113,   113,
     114,   114,   114,   114,   114,   114,   114,   114,   115,   115,
     116,   116,   117,   117,   117,   117,   117,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   119,   119,   119,   120,   120,   121,   121,   122,
     123,   123,   123,   123,   124,   124,   125,   125,   125,   126,
     126,   126,   126,   126,   127,   127,   128,   128,   129,   129,
     129,   130,   131,   131,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   133,   133,   133,
     133,   134,   134,   135,   135,   136,   136,   137,   137,   137,
     138,   138,   139,   139,   140,   140,   140,   141,   141,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   142,   142,
     142,   143,   143,   143,   143,   144,   145,   145,   146,   146,
     147,   147,   147,   147,   147,   147,   148,   148,   148,   149,
     149,   150,   150,   151,   151,   152,   152,   153,   153,   153,
     154,   154,   154,   154,   154,   154,   155,   155,   155,   155,
     155,   156,   156,   157,   157,   158,   158,   159,   159
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     3,     1,     4,     3,     4,
       3,     3,     2,     2,     6,     7,     1,     3,     1,     2,
       2,     2,     2,     4,     1,     1,     1,     1,     1,     1,
       1,     4,     1,     3,     3,     3,     1,     3,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     5,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     2,     3,
       1,     2,     1,     2,     1,     2,     1,     2,     1,     3,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     5,     4,     2,     1,     1,     1,     2,     3,
       2,     1,     2,     1,     1,     3,     1,     2,     3,     4,
       5,     5,     6,     2,     1,     3,     1,     3,     1,     1,
       1,     1,     2,     1,     1,     3,     5,     4,     4,     6,
       6,     5,     4,     3,     4,     4,     3,     1,     2,     2,
       3,     1,     2,     1,     3,     1,     3,     2,     2,     1,
       1,     3,     1,     2,     1,     1,     2,     3,     2,     3,
       3,     4,     3,     4,     2,     3,     3,     4,     1,     3,
       4,     1,     2,     3,     4,     2,     1,     2,     3,     2,
       1,     1,     1,     1,     1,     1,     3,     4,     3,     2,
       3,     1,     2,     1,     1,     1,     2,     5,     7,     5,
       5,     7,     6,     7,     6,     7,     3,     2,     2,     2,
       3,     1,     2,     1,     1,     4,     3,     1,     2
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

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
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

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yyerror_range[1] = yylloc;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* primary_expression: IDENTIFIER  */
#line 144 "mini_c.y"
                              { (yyval.node) = new_id_node((yyvsp[0].sval), LOC((yylsp[0]))); }
#line 1902 "mini_c.tab.cpp"
    break;

  case 3: /* primary_expression: CONSTANT  */
#line 145 "mini_c.y"
                              { (yyval.node) = new_const_node((yyvsp[0].sval), LOC((yylsp[0]))); }
#line 1908 "mini_c.tab.cpp"
    break;

  case 4: /* primary_expression: STRING_LITERAL  */
#line 146 "mini_c.y"
                              { (yyval.node) = new_string_node((yyvsp[0].sval), LOC((yylsp[0]))); }
#line 1914 "mini_c.tab.cpp"
    break;

  case 5: /* primary_expression: '(' expression ')'  */
#line 147 "mini_c.y"
                              { (yyval.node) = (yyvsp[-1].node); (yyval.node)->loc = LOC((yylsp[0])); }
#line 1920 "mini_c.tab.cpp"
    break;

  case 6: /* postfix_expression: primary_expression  */
#line 151 "mini_c.y"
                                                                   { (yyval.node) = (yyvsp[0].node); }
#line 1926 "mini_c.tab.cpp"
    break;

  case 7: /* postfix_expression: postfix_expression '[' expression ']'  */
#line 152 "mini_c.y"
                                                                   { (yyval.node) = new_array_ref_node((yyvsp[-3].node), (yyvsp[-1].node), LOC((yylsp[-2]))); }
#line 1932 "mini_c.tab.cpp"
    break;

  case 8: /* postfix_expression: postfix_expression '(' ')'  */
#line 153 "mini_c.y"
                                                                   { (yyval.node) = new_func_call_node((yyvsp[-2].node), NULL, LOC((yylsp[-1]))); }
#line 1938 "mini_c.tab.cpp"
    break;

  case 9: /* postfix_expression: postfix_expression '(' argument_expression_list ')'  */
#line 154 "mini_c.y"
                                                                   { (yyval.node) = new_func_call_node((yyvsp[-3].node), (yyvsp[-1].node), LOC((yylsp[-2]))); }
#line 1944 "mini_c.tab.cpp"
    break;

  case 10: /* postfix_expression: postfix_expression '.' IDENTIFIER  */
#line 155 "mini_c.y"
                                                                   { (yyval.node) = new_struct_ref_node((yyvsp[-2].node), (yyvsp[0].sval), false, LOC((yylsp[-1]))); }
#line 1950 "mini_c.tab.cpp"
    break;

  case 11: /* postfix_expression: postfix_expression PTR_OP IDENTIFIER  */
#line 156 "mini_c.y"
                                                                   { (yyval.node) = new_struct_ref_node((yyvsp[-2].node), (yyvsp[0].sval), true, LOC((yylsp[-1]))); }
#line 1956 "mini_c.tab.cpp"
    break;

  case 12: /* postfix_expression: postfix_expression INC_OP  */
#line 157 "mini_c.y"
                                                                   { (yyval.node) = new_post_inc_node((yyvsp[-1].node), LOC((yylsp[0]))); }
#line 1962 "mini_c.tab.cpp"
    break;

  case 13: /* postfix_expression: postfix_expression DEC_OP  */
#line 158 "mini_c.y"
                                                                   { (yyval.node) = new_post_dec_node((yyvsp[-1].node), LOC((yylsp[0]))); }
#line 1968 "mini_c.tab.cpp"
    break;

  case 14: /* postfix_expression: '(' type_name ')' '{' initializer_list '}'  */
#line 159 "mini_c.y"
                                                                   { (yyval.node) = new_compound_literal_node((yyvsp[-4].node), (yyvsp[-1].node), LOC((yylsp[-5]))); }
#line 1974 "mini_c.tab.cpp"
    break;

  case 15: /* postfix_expression: '(' type_name ')' '{' initializer_list ',' '}'  */
#line 160 "mini_c.y"
                                                                   { (yyval.node) = new_compound_literal_node((yyvsp[-5].node), (yyvsp[-2].node), LOC((yylsp[-6]))); }
#line 1980 "mini_c.tab.cpp"
    break;

  case 16: /* argument_expression_list: assignment_expression  */
#line 165 "mini_c.y"
                                                                   { (yyval.node) = new_arg_list((yyvsp[0].node), LOC((yylsp[0]))); }
#line 1986 "mini_c.tab.cpp"
    break;

  case 17: /* argument_expression_list: argument_expression_list ',' assignment_expression  */
#line 166 "mini_c.y"
                                                                   { (yyval.node) = append_arg_list((yyvsp[-2].node), (yyvsp[0].node), LOC((yylsp[-1]))); }
#line 1992 "mini_c.tab.cpp"
    break;

  case 18: /* unary_expression: postfix_expression  */
#line 170 "mini_c.y"
                                                                   { (yyval.node) = (yyvsp[0].node); }
#line 1998 "mini_c.tab.cpp"
    break;

  case 19: /* unary_expression: INC_OP unary_expression  */
#line 171 "mini_c.y"
                                                                   { (yyval.node) = new_pre_inc_node((yyvsp[0].node), LOC((yylsp[-1]))); }
#line 2004 "mini_c.tab.cpp"
    break;

  case 20: /* unary_expression: DEC_OP unary_expression  */
#line 172 "mini_c.y"
                                                                   { (yyval.node) = new_pre_dec_node((yyvsp[0].node), LOC((yylsp[-1]))); }
#line 2010 "mini_c.tab.cpp"
    break;

  case 21: /* unary_expression: unary_operator cast_expression  */
#line 173 "mini_c.y"
                                                                   { (yyval.node) = new_unary_op_node((yyvsp[-1].ival), (yyvsp[0].node), LOC((yylsp[-1]))); }
#line 2016 "mini_c.tab.cpp"
    break;

  case 22: /* unary_expression: SIZEOF unary_expression  */
#line 174 "mini_c.y"
                                                                   { (yyval.node) = new_sizeof_node((yyvsp[0].node), false, LOC((yylsp[-1]))); }
#line 2022 "mini_c.tab.cpp"
    break;

  case 23: /* unary_expression: SIZEOF '(' type_name ')'  */
#line 175 "mini_c.y"
                                                                   { (yyval.node) = new_sizeof_node((yyvsp[-1].node), true, LOC((yylsp[-3]))); }
#line 2028 "mini_c.tab.cpp"
    break;

  case 24: /* unary_operator: '&'  */
#line 179 "mini_c.y"
            { (yyval.ival) = op_address; }
#line 2034 "mini_c.tab.cpp"
    break;

  case 25: /* unary_operator: '*'  */
#line 180 "mini_c.y"
            { (yyval.ival) = op_deref; }
#line 2040 "mini_c.tab.cpp"
    break;

  case 26: /* unary_operator: '+'  */
#line 181 "mini_c.y"
            { (yyval.ival) = op_unary_plus; }
#line 2046 "mini_c.tab.cpp"
    break;

  case 27: /* unary_operator: '-'  */
#line 182 "mini_c.y"
            { (yyval.ival) = op_neg; }
#line 2052 "mini_c.tab.cpp"
    break;

  case 28: /* unary_operator: '~'  */
#line 183 "mini_c.y"
            { (yyval.ival) = op_bitnot; }
#line 2058 "mini_c.tab.cpp"
    break;

  case 29: /* unary_operator: '!'  */
#line 184 "mini_c.y"
            { (yyval.ival) = op_not; }
#line 2064 "mini_c.tab.cpp"
    break;

  case 30: /* cast_expression: unary_expression  */
#line 189 "mini_c.y"
                                                                   { (yyval.node) = (yyvsp[0].node); }
#line 2070 "mini_c.tab.cpp"
    break;

  case 31: /* cast_expression: '(' type_name ')' cast_expression  */
#line 190 "mini_c.y"
                                                                   { (yyval.node) = new_cast_node((yyvsp[-2].node), (yyvsp[0].node), LOC((yylsp[-3]))); }
#line 2076 "mini_c.tab.cpp"
    break;

  case 32: /* multiplicative_expression: cast_expression  */
#line 194 "mini_c.y"
                                                                   { (yyval.node) = (yyvsp[0].node); }
#line 2082 "mini_c.tab.cpp"
    break;

  case 33: /* multiplicative_expression: multiplicative_expression '*' cast_expression  */
#line 195 "mini_c.y"
                                                                   { (yyval.node) = new_binop_node('*', (yyvsp[-2].node), (yyvsp[0].node), LOC((yylsp[-1]))); }
#line 2088 "mini_c.tab.cpp"
    break;

  case 34: /* multiplicative_expression: multiplicative_expression '/' cast_expression  */
#line 196 "mini_c.y"
                                                                   { (yyval.node) = new_binop_node('/', (yyvsp[-2].node), (yyvsp[0].node), LOC((yylsp[-1]))); }
#line 2094 "mini_c.tab.cpp"
    break;

  case 35: /* multiplicative_expression: multiplicative_expression '%' cast_expression  */
#line 197 "mini_c.y"
                                                                   { (yyval.node) = new_binop_node('%', (yyvsp[-2].node), (yyvsp[0].node), LOC((yylsp[-1]))); }
#line 2100 "mini_c.tab.cpp"
    break;

  case 36: /* additive_expression: multiplicative_expression  */
#line 202 "mini_c.y"
                                                                   { (yyval.node) = (yyvsp[0].node); }
#line 2106 "mini_c.tab.cpp"
    break;

  case 37: /* additive_expression: additive_expression '+' multiplicative_expression  */
#line 203 "mini_c.y"
                                                                   { (yyval.node) = new_binop_node('+', (yyvsp[-2].node), (yyvsp[0].node), LOC((yylsp[-1]))); }
#line 2112 "mini_c.tab.cpp"
    break;

  case 38: /* additive_expression: additive_expression '-' multiplicative_expression  */
#line 204 "mini_c.y"
                                                                   { (yyval.node) = new_binop_node('-', (yyvsp[-2].node), (yyvsp[0].node), LOC((yylsp[-1]))); }
#line 2118 "mini_c.tab.cpp"
    break;

  case 39: /* shift_expression: additive_expression  */
#line 209 "mini_c.y"
                                                                   { (yyval.node) = (yyvsp[0].node); }
#line 2124 "mini_c.tab.cpp"
    break;

  case 40: /* shift_expression: shift_expression LEFT_OP additive_expression  */
#line 210 "mini_c.y"
                                                                   { (yyval.node) = new_binop_node(SHL, (yyvsp[-2].node), (yyvsp[0].node), LOC((yylsp[-1]))); }
#line 2130 "mini_c.tab.cpp"
    break;

  case 41: /* shift_expression: shift_expression RIGHT_OP additive_expression  */
#line 211 "mini_c.y"
                                                                   { (yyval.node) = new_binop_node(SHR, (yyvsp[-2].node), (yyvsp[0].node), LOC((yylsp[-1]))); }
#line 2136 "mini_c.tab.cpp"
    break;

  case 42: /* relational_expression: shift_expression  */
#line 216 "mini_c.y"
                                                                   { (yyval.node) = (yyvsp[0].node); }
#line 2142 "mini_c.tab.cpp"
    break;

  case 43: /* relational_expression: relational_expression '<' shift_expression  */
#line 217 "mini_c.y"
                                                                   { (yyval.node) = new_binop_node('<', (yyvsp[-2].node), (yyvsp[0].node), LOC((yylsp[-1]))); }
#line 2148 "mini_c.tab.cpp"
    break;

  case 44: /* relational_expression: relational_expression '>' shift_expression  */
#line 218 "mini_c.y"
                                                                   { (yyval.node) = new_binop_node('>', (yyvsp[-2].node), (yyvsp[0].node), LOC((yylsp[-1]))); }
#line 2154 "mini_c.tab.cpp"
    break;

  case 45: /* relational_expression: relational_expression LE_OP shift_expression  */
#line 219 "mini_c.y"
                                                                   { (yyval.node) = new_binop_node(LE, (yyvsp[-2].node), (yyvsp[0].node), LOC((yylsp[-1]))); }
#line 2160 "mini_c.tab.cpp"
    break;

  case 46: /* relational_expression: relational_expression GE_OP shift_expression  */
#line 220 "mini_c.y"
                                                                   { (yyval.node) = new_binop_node(GE, (yyvsp[-2].node), (yyvsp[0].node), LOC((yylsp[-1]))); }
#line 2166 "mini_c.tab.cpp"
    break;

  case 47: /* equality_expression: relational_expression  */
#line 225 "mini_c.y"
                                                                   { (yyval.node) = (yyvsp[0].node); }
#line 2172 "mini_c.tab.cpp"
    break;

  case 48: /* equality_expression: equality_expression EQ_OP relational_expression  */
#line 226 "mini_c.y"
                                                                   { (yyval.node) = new_binop_node(EQ, (yyvsp[-2].node), (yyvsp[0].node), LOC((yylsp[-1]))); }
#line 2178 "mini_c.tab.cpp"
    break;

  case 49: /* equality_expression: equality_expression NE_OP relational_expression  */
#line 227 "mini_c.y"
                                                                   { (yyval.node) = new_binop_node(NE, (yyvsp[-2].node), (yyvsp[0].node), LOC((yylsp[-1]))); }
#line 2184 "mini_c.tab.cpp"
    break;

  case 50: /* and_expression: equality_expression  */
#line 234 "mini_c.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 2190 "mini_c.tab.cpp"
    break;

  case 51: /* and_expression: and_expression '&' equality_expression  */
#line 236 "mini_c.y"
        { (yyval.node) = new_binop_node('&', (yyvsp[-2].node), (yyvsp[0].node), LOC((yylsp[-1]))); }
#line 2196 "mini_c.tab.cpp"
    break;

  case 52: /* exclusive_or_expression: and_expression  */
#line 242 "mini_c.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 2202 "mini_c.tab.cpp"
    break;

  case 53: /* exclusive_or_expression: exclusive_or_expression '^' and_expression  */
#line 244 "mini_c.y"
        { (yyval.node) = new_binop_node('^', (yyvsp[-2].node), (yyvsp[0].node), LOC((yylsp[-1]))); }
#line 2208 "mini_c.tab.cpp"
    break;

  case 54: /* inclusive_or_expression: exclusive_or_expression  */
#line 250 "mini_c.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 2214 "mini_c.tab.cpp"
    break;

  case 55: /* inclusive_or_expression: inclusive_or_expression '|' exclusive_or_expression  */
#line 252 "mini_c.y"
        { (yyval.node) = new_binop_node('|', (yyvsp[-2].node), (yyvsp[0].node), LOC((yylsp[-1]))); }
#line 2220 "mini_c.tab.cpp"
    break;

  case 56: /* logical_and_expression: inclusive_or_expression  */
#line 258 "mini_c.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 2226 "mini_c.tab.cpp"
    break;

  case 57: /* logical_and_expression: logical_and_expression AND_OP inclusive_or_expression  */
#line 260 "mini_c.y"
        { (yyval.node) = new_logical_and_node((yyvsp[-2].node), (yyvsp[0].node), LOC((yylsp[-1]))); }
#line 2232 "mini_c.tab.cpp"
    break;

  case 58: /* logical_or_expression: logical_and_expression  */
#line 266 "mini_c.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 2238 "mini_c.tab.cpp"
    break;

  case 59: /* logical_or_expression: logical_or_expression OR_OP logical_and_expression  */
#line 268 "mini_c.y"
        { (yyval.node) = new_logical_or_node((yyvsp[-2].node), (yyvsp[0].node), LOC((yylsp[-1]))); }
#line 2244 "mini_c.tab.cpp"
    break;

  case 60: /* conditional_expression: logical_or_expression  */
#line 274 "mini_c.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 2250 "mini_c.tab.cpp"
    break;

  case 61: /* conditional_expression: logical_or_expression '?' expression ':' conditional_expression  */
#line 276 "mini_c.y"
        { (yyval.node) = new_conditional_node((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), LOC((yylsp[-3]))); }
#line 2256 "mini_c.tab.cpp"
    break;

  case 62: /* assignment_expression: conditional_expression  */
#line 282 "mini_c.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 2262 "mini_c.tab.cpp"
    break;

  case 63: /* assignment_expression: unary_expression assignment_operator assignment_expression  */
#line 284 "mini_c.y"
        { (yyval.node) = new_assign_node((yyvsp[-2].node), (yyvsp[-1].ival), (yyvsp[0].node), LOC((yylsp[-1]))); }
#line 2268 "mini_c.tab.cpp"
    break;

  case 64: /* assignment_operator: '='  */
#line 289 "mini_c.y"
                    { (yyval.ival) = op_assign; }
#line 2274 "mini_c.tab.cpp"
    break;

  case 65: /* assignment_operator: MUL_ASSIGN  */
#line 290 "mini_c.y"
                    { (yyval.ival) = op_mul_assign; }
#line 2280 "mini_c.tab.cpp"
    break;

  case 66: /* assignment_operator: DIV_ASSIGN  */
#line 291 "mini_c.y"
                    { (yyval.ival) = op_div_assign; }
#line 2286 "mini_c.tab.cpp"
    break;

  case 67: /* assignment_operator: MOD_ASSIGN  */
#line 292 "mini_c.y"
                    { (yyval.ival) = op_mod_assign; }
#line 2292 "mini_c.tab.cpp"
    break;

  case 68: /* assignment_operator: ADD_ASSIGN  */
#line 293 "mini_c.y"
                    { (yyval.ival) = op_add_assign; }
#line 2298 "mini_c.tab.cpp"
    break;

  case 69: /* assignment_operator: SUB_ASSIGN  */
#line 294 "mini_c.y"
                    { (yyval.ival) = op_sub_assign; }
#line 2304 "mini_c.tab.cpp"
    break;

  case 70: /* assignment_operator: LEFT_ASSIGN  */
#line 295 "mini_c.y"
                    { (yyval.ival) = op_shl_assign; }
#line 2310 "mini_c.tab.cpp"
    break;

  case 71: /* assignment_operator: RIGHT_ASSIGN  */
#line 296 "mini_c.y"
                    { (yyval.ival) = op_shr_assign; }
#line 2316 "mini_c.tab.cpp"
    break;

  case 72: /* assignment_operator: AND_ASSIGN  */
#line 297 "mini_c.y"
                    { (yyval.ival) = op_and_assign; }
#line 2322 "mini_c.tab.cpp"
    break;

  case 73: /* assignment_operator: XOR_ASSIGN  */
#line 298 "mini_c.y"
                    { (yyval.ival) = op_xor_assign; }
#line 2328 "mini_c.tab.cpp"
    break;

  case 74: /* assignment_operator: OR_ASSIGN  */
#line 299 "mini_c.y"
                    { (yyval.ival) = op_or_assign; }
#line 2334 "mini_c.tab.cpp"
    break;

  case 75: /* expression: assignment_expression  */
#line 304 "mini_c.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 2340 "mini_c.tab.cpp"
    break;

  case 76: /* expression: expression ',' assignment_expression  */
#line 306 "mini_c.y"
        { (yyval.node) = new_expr_list((yyvsp[-2].node), (yyvsp[0].node), LOC((yylsp[-1]))); }
#line 2346 "mini_c.tab.cpp"
    break;

  case 77: /* constant_expression: conditional_expression  */
#line 312 "mini_c.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 2352 "mini_c.tab.cpp"
    break;

  case 78: /* declaration: declaration_specifiers ';'  */
#line 318 "mini_c.y"
        { (yyval.node) = new_decl_stmt((yyvsp[-1].node), LOC((yylsp[0]))); }
#line 2358 "mini_c.tab.cpp"
    break;

  case 79: /* declaration: declaration_specifiers init_declarator_list ';'  */
#line 320 "mini_c.y"
        { (yyval.node) = new_declaration((yyvsp[-2].node), (yyvsp[-1].node), LOC((yylsp[0]))); }
#line 2364 "mini_c.tab.cpp"
    break;

  case 80: /* declaration_specifiers: storage_class_specifier  */
#line 326 "mini_c.y"
        { (yyval.node) = new_spec_list((yyvsp[0].ival), LOC((yylsp[0]))); }
#line 2370 "mini_c.tab.cpp"
    break;

  case 81: /* declaration_specifiers: storage_class_specifier declaration_specifiers  */
#line 328 "mini_c.y"
        { (yyval.node) = append_spec_list((yyvsp[0].node), (yyvsp[-1].ival), LOC((yylsp[-1]))); }
#line 2376 "mini_c.tab.cpp"
    break;

  case 82: /* declaration_specifiers: type_specifier  */
#line 330 "mini_c.y"
        { (yyval.node) = new_spec_list((yyvsp[0].node), LOC((yylsp[0]))); }
#line 2382 "mini_c.tab.cpp"
    break;

  case 83: /* declaration_specifiers: type_specifier declaration_specifiers  */
#line 332 "mini_c.y"
        { (yyval.node) = append_spec_list((yyvsp[0].node), (yyvsp[-1].node), LOC((yylsp[-1]))); }
#line 2388 "mini_c.tab.cpp"
    break;

  case 84: /* declaration_specifiers: type_qualifier  */
#line 334 "mini_c.y"
        { (yyval.node) = new_spec_list((yyvsp[0].ival), LOC((yylsp[0]))); }
#line 2394 "mini_c.tab.cpp"
    break;

  case 85: /* declaration_specifiers: type_qualifier declaration_specifiers  */
#line 336 "mini_c.y"
        { (yyval.node) = append_spec_list((yyvsp[0].node), (yyvsp[-1].ival), LOC((yylsp[-1]))); }
#line 2400 "mini_c.tab.cpp"
    break;

  case 86: /* declaration_specifiers: function_specifier  */
#line 338 "mini_c.y"
        { (yyval.node) = new_spec_list((yyvsp[0].ival), LOC((yylsp[0]))); }
#line 2406 "mini_c.tab.cpp"
    break;

  case 87: /* declaration_specifiers: function_specifier declaration_specifiers  */
#line 340 "mini_c.y"
        { (yyval.node) = append_spec_list((yyvsp[0].node), (yyvsp[-1].ival), LOC((yylsp[-1]))); }
#line 2412 "mini_c.tab.cpp"
    break;

  case 88: /* init_declarator_list: init_declarator  */
#line 346 "mini_c.y"
        { (yyval.node) = new_init_list((yyvsp[0].node), LOC((yylsp[0]))); }
#line 2418 "mini_c.tab.cpp"
    break;

  case 89: /* init_declarator_list: init_declarator_list ',' init_declarator  */
#line 348 "mini_c.y"
        { (yyval.node) = append_init_list((yyvsp[-2].node), (yyvsp[0].node), LOC((yylsp[-1]))); }
#line 2424 "mini_c.tab.cpp"
    break;

  case 90: /* init_declarator: declarator  */
#line 354 "mini_c.y"
        { (yyval.node) = new_init_decl((yyvsp[0].node), NULL, LOC((yylsp[0]))); }
#line 2430 "mini_c.tab.cpp"
    break;

  case 91: /* init_declarator: declarator '=' initializer  */
#line 356 "mini_c.y"
        { (yyval.node) = new_init_decl((yyvsp[-2].node), (yyvsp[0].node), LOC((yylsp[-1]))); }
#line 2436 "mini_c.tab.cpp"
    break;

  case 92: /* storage_class_specifier: TYPEDEF  */
#line 361 "mini_c.y"
                { (yyval.ival) = SC_TYPEDEF; }
#line 2442 "mini_c.tab.cpp"
    break;

  case 93: /* storage_class_specifier: EXTERN  */
#line 362 "mini_c.y"
                { (yyval.ival) = SC_EXTERN; }
#line 2448 "mini_c.tab.cpp"
    break;

  case 94: /* storage_class_specifier: STATIC  */
#line 363 "mini_c.y"
                { (yyval.ival) = SC_STATIC; }
#line 2454 "mini_c.tab.cpp"
    break;

  case 95: /* storage_class_specifier: AUTO  */
#line 364 "mini_c.y"
                { (yyval.ival) = SC_AUTO; }
#line 2460 "mini_c.tab.cpp"
    break;

  case 96: /* storage_class_specifier: REGISTER  */
#line 365 "mini_c.y"
                { (yyval.ival) = SC_REGISTER; }
#line 2466 "mini_c.tab.cpp"
    break;

  case 97: /* type_specifier: VOID  */
#line 369 "mini_c.y"
                 { (yyval.node) = make_type_spec_node(TS_VOID); }
#line 2472 "mini_c.tab.cpp"
    break;

  case 98: /* type_specifier: CHAR  */
#line 370 "mini_c.y"
                 { (yyval.node) = make_type_spec_node(TS_CHAR); }
#line 2478 "mini_c.tab.cpp"
    break;

  case 99: /* type_specifier: SHORT  */
#line 371 "mini_c.y"
                 { (yyval.node) = make_type_spec_node(TS_SHORT); }
#line 2484 "mini_c.tab.cpp"
    break;

  case 100: /* type_specifier: INT  */
#line 372 "mini_c.y"
                 { (yyval.node) = make_type_spec_node(TS_INT); }
#line 2490 "mini_c.tab.cpp"
    break;

  case 101: /* type_specifier: LONG  */
#line 373 "mini_c.y"
                 { (yyval.node) = make_type_spec_node(TS_LONG); }
#line 2496 "mini_c.tab.cpp"
    break;

  case 102: /* type_specifier: FLOAT  */
#line 374 "mini_c.y"
                 { (yyval.node) = make_type_spec_node(TS_FLOAT); }
#line 2502 "mini_c.tab.cpp"
    break;

  case 103: /* type_specifier: DOUBLE  */
#line 375 "mini_c.y"
                 { (yyval.node) = make_type_spec_node(TS_DOUBLE); }
#line 2508 "mini_c.tab.cpp"
    break;

  case 104: /* type_specifier: SIGNED  */
#line 376 "mini_c.y"
                 { (yyval.node) = make_type_spec_node(TS_SIGNED); }
#line 2514 "mini_c.tab.cpp"
    break;

  case 105: /* type_specifier: UNSIGNED  */
#line 377 "mini_c.y"
                 { (yyval.node) = make_type_spec_node(TS_UNSIGNED); }
#line 2520 "mini_c.tab.cpp"
    break;

  case 106: /* type_specifier: BOOL  */
#line 378 "mini_c.y"
                 { (yyval.node) = make_type_spec_node(TS_BOOL); }
#line 2526 "mini_c.tab.cpp"
    break;

  case 107: /* type_specifier: COMPLEX  */
#line 379 "mini_c.y"
                 { (yyval.node) = make_type_spec_node(TS_COMPLEX); }
#line 2532 "mini_c.tab.cpp"
    break;

  case 108: /* type_specifier: IMAGINARY  */
#line 380 "mini_c.y"
                 { (yyval.node) = make_type_spec_node(TS_IMAGINARY); }
#line 2538 "mini_c.tab.cpp"
    break;

  case 109: /* type_specifier: struct_or_union_specifier  */
#line 382 "mini_c.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 2544 "mini_c.tab.cpp"
    break;

  case 110: /* type_specifier: enum_specifier  */
#line 384 "mini_c.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 2550 "mini_c.tab.cpp"
    break;

  case 111: /* type_specifier: TYPE_NAME  */
#line 386 "mini_c.y"
        { (yyval.node) = make_type_spec_node(TS_TYPE_NAME); }
#line 2556 "mini_c.tab.cpp"
    break;

  case 112: /* struct_or_union_specifier: struct_or_union IDENTIFIER '{' struct_declaration_list '}'  */
#line 391 "mini_c.y"
        { (yyval.node) = new_struct_su_node(static_cast<StructUnionKind>((yyvsp[-4].ival)), (yyvsp[-3].sval), (yyvsp[-1].node), LOC((yylsp[-3]))); }
#line 2562 "mini_c.tab.cpp"
    break;

  case 113: /* struct_or_union_specifier: struct_or_union '{' struct_declaration_list '}'  */
#line 393 "mini_c.y"
        { (yyval.node) = new_struct_su_node(static_cast<StructUnionKind>((yyvsp[-3].ival)), nullptr, (yyvsp[-1].node), LOC((yylsp[-2]))); }
#line 2568 "mini_c.tab.cpp"
    break;

  case 114: /* struct_or_union_specifier: struct_or_union IDENTIFIER  */
#line 395 "mini_c.y"
        { (yyval.node) = new_struct_su_node(static_cast<StructUnionKind>((yyvsp[-1].ival)), (yyvsp[0].sval), nullptr, LOC((yylsp[0]))); }
#line 2574 "mini_c.tab.cpp"
    break;

  case 115: /* struct_or_union: STRUCT  */
#line 401 "mini_c.y"
              { (yyval.ival) = SU_STRUCT; }
#line 2580 "mini_c.tab.cpp"
    break;

  case 116: /* struct_or_union: UNION  */
#line 402 "mini_c.y"
              { (yyval.ival) = SU_UNION; }
#line 2586 "mini_c.tab.cpp"
    break;

  case 117: /* struct_declaration_list: struct_declaration  */
#line 407 "mini_c.y"
        { (yyval.node) = new_sdecl_list((yyvsp[0].node), LOC((yylsp[0]))); }
#line 2592 "mini_c.tab.cpp"
    break;

  case 118: /* struct_declaration_list: struct_declaration_list struct_declaration  */
#line 409 "mini_c.y"
        { (yyval.node) = append_sdecl_list((yyvsp[-1].node), (yyvsp[0].node), LOC((yylsp[0]))); }
#line 2598 "mini_c.tab.cpp"
    break;

  case 119: /* struct_declaration: specifier_qualifier_list struct_declarator_list ';'  */
#line 415 "mini_c.y"
        { (yyval.node) = new_struct_decl((yyvsp[-2].node), (yyvsp[-1].node), LOC((yylsp[0]))); }
#line 2604 "mini_c.tab.cpp"
    break;

  case 120: /* specifier_qualifier_list: type_specifier specifier_qualifier_list  */
#line 420 "mini_c.y"
        { (yyval.node) = append_specq_list((yyvsp[0].node), (yyvsp[-1].node), LOC((yylsp[-1]))); }
#line 2610 "mini_c.tab.cpp"
    break;

  case 121: /* specifier_qualifier_list: type_specifier  */
#line 422 "mini_c.y"
        { (yyval.node) = new_specq_list((yyvsp[0].node), LOC((yylsp[0]))); }
#line 2616 "mini_c.tab.cpp"
    break;

  case 122: /* specifier_qualifier_list: type_qualifier specifier_qualifier_list  */
#line 424 "mini_c.y"
        { (yyval.node) = append_specq_list((yyvsp[0].node), (yyvsp[-1].ival), LOC((yylsp[-1]))); }
#line 2622 "mini_c.tab.cpp"
    break;

  case 123: /* specifier_qualifier_list: type_qualifier  */
#line 426 "mini_c.y"
        { (yyval.node) = new_specq_list((yyvsp[0].ival), LOC((yylsp[0]))); }
#line 2628 "mini_c.tab.cpp"
    break;

  case 124: /* struct_declarator_list: struct_declarator  */
#line 432 "mini_c.y"
        { (yyval.node) = new_sdeclarator_list((yyvsp[0].node), LOC((yylsp[0]))); }
#line 2634 "mini_c.tab.cpp"
    break;

  case 125: /* struct_declarator_list: struct_declarator_list ',' struct_declarator  */
#line 434 "mini_c.y"
        { (yyval.node) = append_sdeclarator_list((yyvsp[-2].node), (yyvsp[0].node), LOC((yylsp[-1]))); }
#line 2640 "mini_c.tab.cpp"
    break;

  case 126: /* struct_declarator: declarator  */
#line 440 "mini_c.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 2646 "mini_c.tab.cpp"
    break;

  case 127: /* struct_declarator: ':' constant_expression  */
#line 442 "mini_c.y"
        { (yyval.node) = new_bitfield_node(NULL, (yyvsp[0].node), LOC((yylsp[-1]))); }
#line 2652 "mini_c.tab.cpp"
    break;

  case 128: /* struct_declarator: declarator ':' constant_expression  */
#line 444 "mini_c.y"
        { (yyval.node) = new_bitfield_node((yyvsp[-2].node), (yyvsp[0].node), LOC((yylsp[-1]))); }
#line 2658 "mini_c.tab.cpp"
    break;

  case 129: /* enum_specifier: ENUM '{' enumerator_list '}'  */
#line 450 "mini_c.y"
        { (yyval.node) = new_enum_node(NULL, (yyvsp[-1].node), LOC((yylsp[-3]))); }
#line 2664 "mini_c.tab.cpp"
    break;

  case 130: /* enum_specifier: ENUM IDENTIFIER '{' enumerator_list '}'  */
#line 452 "mini_c.y"
        { (yyval.node) = new_enum_node((yyvsp[-3].sval), (yyvsp[-1].node), LOC((yylsp[-4]))); }
#line 2670 "mini_c.tab.cpp"
    break;

  case 131: /* enum_specifier: ENUM '{' enumerator_list ',' '}'  */
#line 454 "mini_c.y"
        { (yyval.node) = new_enum_node(NULL, (yyvsp[-2].node), LOC((yylsp[-4]))); }
#line 2676 "mini_c.tab.cpp"
    break;

  case 132: /* enum_specifier: ENUM IDENTIFIER '{' enumerator_list ',' '}'  */
#line 456 "mini_c.y"
        { (yyval.node) = new_enum_node((yyvsp[-4].sval), (yyvsp[-2].node), LOC((yylsp[-5]))); }
#line 2682 "mini_c.tab.cpp"
    break;

  case 133: /* enum_specifier: ENUM IDENTIFIER  */
#line 458 "mini_c.y"
        { (yyval.node) = new_enum_node((yyvsp[0].sval), NULL, LOC((yylsp[-1]))); }
#line 2688 "mini_c.tab.cpp"
    break;

  case 134: /* enumerator_list: enumerator  */
#line 464 "mini_c.y"
        { (yyval.node) = new_enum_list((yyvsp[0].node), LOC((yylsp[0]))); }
#line 2694 "mini_c.tab.cpp"
    break;

  case 135: /* enumerator_list: enumerator_list ',' enumerator  */
#line 466 "mini_c.y"
        { (yyval.node) = append_enum_list((yyvsp[-2].node), (yyvsp[0].node), LOC((yylsp[-1]))); }
#line 2700 "mini_c.tab.cpp"
    break;

  case 136: /* enumerator: IDENTIFIER  */
#line 472 "mini_c.y"
        { (yyval.node) = new_enum_const((yyvsp[0].sval), NULL, LOC((yylsp[0]))); }
#line 2706 "mini_c.tab.cpp"
    break;

  case 137: /* enumerator: IDENTIFIER '=' constant_expression  */
#line 474 "mini_c.y"
        { (yyval.node) = new_enum_const((yyvsp[-2].sval), (yyvsp[0].node), LOC((yylsp[-2]))); }
#line 2712 "mini_c.tab.cpp"
    break;

  case 138: /* type_qualifier: CONST  */
#line 480 "mini_c.y"
        { (yyval.ival) = TQ_CONST; }
#line 2718 "mini_c.tab.cpp"
    break;

  case 139: /* type_qualifier: RESTRICT  */
#line 482 "mini_c.y"
        { (yyval.ival) = TQ_RESTRICT; }
#line 2724 "mini_c.tab.cpp"
    break;

  case 140: /* type_qualifier: VOLATILE  */
#line 484 "mini_c.y"
        { (yyval.ival) = TQ_VOLATILE; }
#line 2730 "mini_c.tab.cpp"
    break;

  case 141: /* function_specifier: INLINE  */
#line 489 "mini_c.y"
        { (yyval.ival) = FS_INLINE; }
#line 2736 "mini_c.tab.cpp"
    break;

  case 142: /* declarator: pointer direct_declarator  */
#line 494 "mini_c.y"
        { (yyval.node) = new_declarator_node((yyvsp[-1].node), (yyvsp[0].node), LOC((yylsp[-1]))); }
#line 2742 "mini_c.tab.cpp"
    break;

  case 143: /* declarator: direct_declarator  */
#line 496 "mini_c.y"
        { (yyval.node) = new_declarator_node(NULL, (yyvsp[0].node), LOC((yylsp[0]))); }
#line 2748 "mini_c.tab.cpp"
    break;

  case 144: /* direct_declarator: IDENTIFIER  */
#line 502 "mini_c.y"
        { (yyval.node) = new_decl_ident((yyvsp[0].sval), LOC((yylsp[0]))); }
#line 2754 "mini_c.tab.cpp"
    break;

  case 145: /* direct_declarator: '(' declarator ')'  */
#line 504 "mini_c.y"
        { (yyval.node) = (yyvsp[-1].node); (yyval.node)->loc = LOC((yylsp[0])); }
#line 2760 "mini_c.tab.cpp"
    break;

  case 146: /* direct_declarator: direct_declarator '[' type_qualifier_list assignment_expression ']'  */
#line 506 "mini_c.y"
        { (yyval.node) = new_array_decl((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[-1].node), NULL, NULL, LOC((yylsp[-3]))); }
#line 2766 "mini_c.tab.cpp"
    break;

  case 147: /* direct_declarator: direct_declarator '[' type_qualifier_list ']'  */
#line 508 "mini_c.y"
        { (yyval.node) = new_array_decl((yyvsp[-3].node), (yyvsp[-1].node), NULL, NULL, NULL, LOC((yylsp[-2]))); }
#line 2772 "mini_c.tab.cpp"
    break;

  case 148: /* direct_declarator: direct_declarator '[' assignment_expression ']'  */
#line 510 "mini_c.y"
        { (yyval.node) = new_array_decl((yyvsp[-3].node), NULL, (yyvsp[-1].node), NULL, NULL, LOC((yylsp[-2]))); }
#line 2778 "mini_c.tab.cpp"
    break;

  case 149: /* direct_declarator: direct_declarator '[' STATIC type_qualifier_list assignment_expression ']'  */
#line 512 "mini_c.y"
        { (yyval.node) = new_array_decl((yyvsp[-5].node), (yyvsp[-2].node), (yyvsp[-1].node), true, NULL, LOC((yylsp[-4]))); }
#line 2784 "mini_c.tab.cpp"
    break;

  case 150: /* direct_declarator: direct_declarator '[' type_qualifier_list STATIC assignment_expression ']'  */
#line 514 "mini_c.y"
        { (yyval.node) = new_array_decl((yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[-1].node), true, NULL, LOC((yylsp[-4]))); }
#line 2790 "mini_c.tab.cpp"
    break;

  case 151: /* direct_declarator: direct_declarator '[' type_qualifier_list '*' ']'  */
#line 516 "mini_c.y"
        { (yyval.node) = new_array_decl((yyvsp[-4].node), (yyvsp[-2].node), NULL, NULL, true, LOC((yylsp[-3]))); }
#line 2796 "mini_c.tab.cpp"
    break;

  case 152: /* direct_declarator: direct_declarator '[' '*' ']'  */
#line 518 "mini_c.y"
        { (yyval.node) = new_array_decl((yyvsp[-3].node), NULL, NULL, NULL, true, LOC((yylsp[-2]))); }
#line 2802 "mini_c.tab.cpp"
    break;

  case 153: /* direct_declarator: direct_declarator '[' ']'  */
#line 520 "mini_c.y"
        { (yyval.node) = new_array_decl((yyvsp[-2].node), NULL, NULL, NULL, false, LOC((yylsp[-1]))); }
#line 2808 "mini_c.tab.cpp"
    break;

  case 154: /* direct_declarator: direct_declarator '(' parameter_type_list ')'  */
#line 522 "mini_c.y"
        { (yyval.node) = new_func_decl((yyvsp[-3].node), (yyvsp[-1].node), LOC((yylsp[-2]))); }
#line 2814 "mini_c.tab.cpp"
    break;

  case 155: /* direct_declarator: direct_declarator '(' identifier_list ')'  */
#line 524 "mini_c.y"
        { (yyval.node) = new_oldstyle_func_decl((yyvsp[-3].node), (yyvsp[-1].node), LOC((yylsp[-2]))); }
#line 2820 "mini_c.tab.cpp"
    break;

  case 156: /* direct_declarator: direct_declarator '(' ')'  */
#line 526 "mini_c.y"
        { (yyval.node) = new_func_decl((yyvsp[-2].node), NULL, LOC((yylsp[-1]))); }
#line 2826 "mini_c.tab.cpp"
    break;

  case 157: /* pointer: '*'  */
#line 532 "mini_c.y"
        { (yyval.node) = new_pointer(NULL, LOC((yylsp[0]))); }
#line 2832 "mini_c.tab.cpp"
    break;

  case 158: /* pointer: '*' type_qualifier_list  */
#line 534 "mini_c.y"
        { (yyval.node) = new_pointer((yyvsp[0].node), LOC((yylsp[-1]))); }
#line 2838 "mini_c.tab.cpp"
    break;

  case 159: /* pointer: '*' pointer  */
#line 536 "mini_c.y"
        { (yyval.node) = prepend_pointer(NULL, (yyvsp[0].node), LOC((yylsp[-1]))); }
#line 2844 "mini_c.tab.cpp"
    break;

  case 160: /* pointer: '*' type_qualifier_list pointer  */
#line 538 "mini_c.y"
        { (yyval.node) = prepend_pointer((yyvsp[-1].node), (yyvsp[0].node), LOC((yylsp[-2]))); }
#line 2850 "mini_c.tab.cpp"
    break;

  case 161: /* type_qualifier_list: type_qualifier  */
#line 544 "mini_c.y"
        { (yyval.node) = new_tq_list((yyvsp[0].ival), LOC((yylsp[0]))); }
#line 2856 "mini_c.tab.cpp"
    break;

  case 162: /* type_qualifier_list: type_qualifier_list type_qualifier  */
#line 546 "mini_c.y"
        { (yyval.node) = append_tq_list((yyvsp[-1].node), (yyvsp[0].ival), LOC((yylsp[0]))); }
#line 2862 "mini_c.tab.cpp"
    break;

  case 163: /* parameter_type_list: parameter_list  */
#line 551 "mini_c.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 2868 "mini_c.tab.cpp"
    break;

  case 164: /* parameter_type_list: parameter_list ',' ELLIPSIS  */
#line 553 "mini_c.y"
        { (yyval.node) = new_param_list_ellipsis((yyvsp[-2].node), LOC((yylsp[-1]))); }
#line 2874 "mini_c.tab.cpp"
    break;

  case 165: /* parameter_list: parameter_declaration  */
#line 559 "mini_c.y"
        { (yyval.node) = new_param_list((yyvsp[0].node), LOC((yylsp[0]))); }
#line 2880 "mini_c.tab.cpp"
    break;

  case 166: /* parameter_list: parameter_list ',' parameter_declaration  */
#line 561 "mini_c.y"
        { (yyval.node) = append_param_list((yyvsp[-2].node), (yyvsp[0].node), LOC((yylsp[-1]))); }
#line 2886 "mini_c.tab.cpp"
    break;

  case 167: /* parameter_declaration: declaration_specifiers declarator  */
#line 567 "mini_c.y"
        { (yyval.node) = new_param_decl((yyvsp[-1].node), (yyvsp[0].node), LOC((yylsp[0]))); }
#line 2892 "mini_c.tab.cpp"
    break;

  case 168: /* parameter_declaration: declaration_specifiers abstract_declarator  */
#line 569 "mini_c.y"
        { (yyval.node) = new_param_decl((yyvsp[-1].node), (yyvsp[0].node), LOC((yylsp[0]))); }
#line 2898 "mini_c.tab.cpp"
    break;

  case 169: /* parameter_declaration: declaration_specifiers  */
#line 571 "mini_c.y"
        { (yyval.node) = new_param_decl((yyvsp[0].node), NULL, LOC((yylsp[0]))); }
#line 2904 "mini_c.tab.cpp"
    break;

  case 170: /* identifier_list: IDENTIFIER  */
#line 577 "mini_c.y"
        { (yyval.node) = new_id_list((yyvsp[0].sval), LOC((yylsp[0]))); }
#line 2910 "mini_c.tab.cpp"
    break;

  case 171: /* identifier_list: identifier_list ',' IDENTIFIER  */
#line 579 "mini_c.y"
        { (yyval.node) = append_id_list((yyvsp[-2].node), (yyvsp[0].sval), LOC((yylsp[0]))); }
#line 2916 "mini_c.tab.cpp"
    break;

  case 172: /* type_name: specifier_qualifier_list  */
#line 584 "mini_c.y"
        { (yyval.node) = new_type_name((yyvsp[0].node), NULL, LOC((yylsp[0]))); }
#line 2922 "mini_c.tab.cpp"
    break;

  case 173: /* type_name: specifier_qualifier_list abstract_declarator  */
#line 586 "mini_c.y"
        { (yyval.node) = new_type_name((yyvsp[-1].node), (yyvsp[0].node), LOC((yylsp[-1]))); }
#line 2928 "mini_c.tab.cpp"
    break;

  case 174: /* abstract_declarator: pointer  */
#line 592 "mini_c.y"
        { (yyval.node) = new_abs_decl((yyvsp[0].node), NULL, LOC((yylsp[0]))); }
#line 2934 "mini_c.tab.cpp"
    break;

  case 175: /* abstract_declarator: direct_abstract_declarator  */
#line 594 "mini_c.y"
        { (yyval.node) = new_abs_decl(NULL, (yyvsp[0].node), LOC((yylsp[0]))); }
#line 2940 "mini_c.tab.cpp"
    break;

  case 176: /* abstract_declarator: pointer direct_abstract_declarator  */
#line 596 "mini_c.y"
        { (yyval.node) = new_abs_decl((yyvsp[-1].node), (yyvsp[0].node), LOC((yylsp[-1]))); }
#line 2946 "mini_c.tab.cpp"
    break;

  case 177: /* direct_abstract_declarator: '(' abstract_declarator ')'  */
#line 602 "mini_c.y"
        { (yyval.node) = (yyvsp[-1].node); (yyval.node)->loc = LOC((yylsp[0])); }
#line 2952 "mini_c.tab.cpp"
    break;

  case 178: /* direct_abstract_declarator: '[' ']'  */
#line 604 "mini_c.y"
        { (yyval.node) = new_abs_array(NULL, NULL, LOC((yylsp[-1]))); }
#line 2958 "mini_c.tab.cpp"
    break;

  case 179: /* direct_abstract_declarator: '[' assignment_expression ']'  */
#line 606 "mini_c.y"
        { (yyval.node) = new_abs_array((yyvsp[-1].node), NULL, LOC((yylsp[-2]))); }
#line 2964 "mini_c.tab.cpp"
    break;

  case 180: /* direct_abstract_declarator: direct_abstract_declarator '[' ']'  */
#line 608 "mini_c.y"
        { (yyval.node) = new_abs_array_child((yyvsp[-2].node), NULL, NULL, LOC((yylsp[-1]))); }
#line 2970 "mini_c.tab.cpp"
    break;

  case 181: /* direct_abstract_declarator: direct_abstract_declarator '[' assignment_expression ']'  */
#line 610 "mini_c.y"
        { (yyval.node) = new_abs_array_child((yyvsp[-3].node), (yyvsp[-1].node), NULL, LOC((yylsp[-2]))); }
#line 2976 "mini_c.tab.cpp"
    break;

  case 182: /* direct_abstract_declarator: '[' '*' ']'  */
#line 612 "mini_c.y"
        { (yyval.node) = new_abs_array(NULL, true, LOC((yylsp[-2]))); }
#line 2982 "mini_c.tab.cpp"
    break;

  case 183: /* direct_abstract_declarator: direct_abstract_declarator '[' '*' ']'  */
#line 614 "mini_c.y"
        { (yyval.node) = new_abs_array_child((yyvsp[-3].node), NULL, true, LOC((yylsp[-2]))); }
#line 2988 "mini_c.tab.cpp"
    break;

  case 184: /* direct_abstract_declarator: '(' ')'  */
#line 616 "mini_c.y"
        { (yyval.node) = new_abs_func(NULL, LOC((yylsp[-1]))); }
#line 2994 "mini_c.tab.cpp"
    break;

  case 185: /* direct_abstract_declarator: '(' parameter_type_list ')'  */
#line 618 "mini_c.y"
        { (yyval.node) = new_abs_func((yyvsp[-1].node), LOC((yylsp[-2]))); }
#line 3000 "mini_c.tab.cpp"
    break;

  case 186: /* direct_abstract_declarator: direct_abstract_declarator '(' ')'  */
#line 620 "mini_c.y"
        { (yyval.node) = new_abs_func_child((yyvsp[-2].node), NULL, LOC((yylsp[-1]))); }
#line 3006 "mini_c.tab.cpp"
    break;

  case 187: /* direct_abstract_declarator: direct_abstract_declarator '(' parameter_type_list ')'  */
#line 622 "mini_c.y"
        { (yyval.node) = new_abs_func_child((yyvsp[-3].node), (yyvsp[-1].node), LOC((yylsp[-2]))); }
#line 3012 "mini_c.tab.cpp"
    break;

  case 188: /* initializer: assignment_expression  */
#line 628 "mini_c.y"
        { (yyval.node) = new_init_expr((yyvsp[0].node), LOC((yylsp[0]))); }
#line 3018 "mini_c.tab.cpp"
    break;

  case 189: /* initializer: '{' initializer_list '}'  */
#line 630 "mini_c.y"
        { (yyval.node) = new_init_list_node((yyvsp[-1].node), LOC((yylsp[-2]))); }
#line 3024 "mini_c.tab.cpp"
    break;

  case 190: /* initializer: '{' initializer_list ',' '}'  */
#line 632 "mini_c.y"
        { (yyval.node) = new_init_list_node((yyvsp[-2].node), LOC((yylsp[-3]))); }
#line 3030 "mini_c.tab.cpp"
    break;

  case 191: /* initializer_list: initializer  */
#line 638 "mini_c.y"
        { (yyval.node) = new_init_item_list((yyvsp[0].node), LOC((yylsp[0]))); }
#line 3036 "mini_c.tab.cpp"
    break;

  case 192: /* initializer_list: designation initializer  */
#line 640 "mini_c.y"
        { (yyval.node) = new_designated_init((yyvsp[-1].node), (yyvsp[0].node), LOC((yylsp[-1]))); }
#line 3042 "mini_c.tab.cpp"
    break;

  case 193: /* initializer_list: initializer_list ',' initializer  */
#line 642 "mini_c.y"
        { (yyval.node) = append_init_item((yyvsp[-2].node), (yyvsp[0].node), LOC((yylsp[-1]))); }
#line 3048 "mini_c.tab.cpp"
    break;

  case 194: /* initializer_list: initializer_list ',' designation initializer  */
#line 644 "mini_c.y"
        { (yyval.node) = append_designated_init((yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node), LOC((yylsp[-2]))); }
#line 3054 "mini_c.tab.cpp"
    break;

  case 195: /* designation: designator_list '='  */
#line 650 "mini_c.y"
        { (yyval.node) = (yyvsp[-1].node); }
#line 3060 "mini_c.tab.cpp"
    break;

  case 196: /* designator_list: designator  */
#line 656 "mini_c.y"
        { (yyval.node) = new_designator_list((yyvsp[0].node), LOC((yylsp[0]))); }
#line 3066 "mini_c.tab.cpp"
    break;

  case 197: /* designator_list: designator_list designator  */
#line 658 "mini_c.y"
        { (yyval.node) = append_designator_list((yyvsp[-1].node), (yyvsp[0].node), LOC((yylsp[0]))); }
#line 3072 "mini_c.tab.cpp"
    break;

  case 198: /* designator: '[' constant_expression ']'  */
#line 663 "mini_c.y"
        { (yyval.node) = new_array_designator((yyvsp[-1].node), LOC((yylsp[-2]))); }
#line 3078 "mini_c.tab.cpp"
    break;

  case 199: /* designator: '.' IDENTIFIER  */
#line 665 "mini_c.y"
        { (yyval.node) = new_field_designator((yyvsp[0].sval), LOC((yylsp[-1]))); }
#line 3084 "mini_c.tab.cpp"
    break;

  case 200: /* statement: labeled_statement  */
#line 670 "mini_c.y"
                              { (yyval.node) = (yyvsp[0].node); }
#line 3090 "mini_c.tab.cpp"
    break;

  case 201: /* statement: compound_statement  */
#line 671 "mini_c.y"
                              { (yyval.node) = (yyvsp[0].node); }
#line 3096 "mini_c.tab.cpp"
    break;

  case 202: /* statement: expression_statement  */
#line 672 "mini_c.y"
                              { (yyval.node) = (yyvsp[0].node); }
#line 3102 "mini_c.tab.cpp"
    break;

  case 203: /* statement: selection_statement  */
#line 673 "mini_c.y"
                              { (yyval.node) = (yyvsp[0].node); }
#line 3108 "mini_c.tab.cpp"
    break;

  case 204: /* statement: iteration_statement  */
#line 674 "mini_c.y"
                              { (yyval.node) = (yyvsp[0].node); }
#line 3114 "mini_c.tab.cpp"
    break;

  case 205: /* statement: jump_statement  */
#line 675 "mini_c.y"
                              { (yyval.node) = (yyvsp[0].node); }
#line 3120 "mini_c.tab.cpp"
    break;

  case 206: /* labeled_statement: IDENTIFIER ':' statement  */
#line 681 "mini_c.y"
        { (yyval.node) = new_labeled_stmt_id((yyvsp[-2].sval), (yyvsp[0].node), LOC((yylsp[-2]))); }
#line 3126 "mini_c.tab.cpp"
    break;

  case 207: /* labeled_statement: CASE constant_expression ':' statement  */
#line 683 "mini_c.y"
        { (yyval.node) = new_case_stmt((yyvsp[-2].node), (yyvsp[0].node), LOC((yylsp[-3]))); }
#line 3132 "mini_c.tab.cpp"
    break;

  case 208: /* labeled_statement: DEFAULT ':' statement  */
#line 685 "mini_c.y"
        { (yyval.node) = new_default_stmt((yyvsp[0].node), LOC((yylsp[-2]))); }
#line 3138 "mini_c.tab.cpp"
    break;

  case 209: /* compound_statement: '{' '}'  */
#line 690 "mini_c.y"
        { (yyval.node) = new_compound_stmt(NULL, LOC((yylsp[-1]))); }
#line 3144 "mini_c.tab.cpp"
    break;

  case 210: /* compound_statement: '{' block_item_list '}'  */
#line 692 "mini_c.y"
        { (yyval.node) = new_compound_stmt((yyvsp[-1].node), LOC((yylsp[-2]))); }
#line 3150 "mini_c.tab.cpp"
    break;

  case 211: /* block_item_list: block_item  */
#line 698 "mini_c.y"
        { (yyval.node) = new_block_item_list((yyvsp[0].node), LOC((yylsp[0]))); }
#line 3156 "mini_c.tab.cpp"
    break;

  case 212: /* block_item_list: block_item_list block_item  */
#line 700 "mini_c.y"
        { (yyval.node) = append_block_item_list((yyvsp[-1].node), (yyvsp[0].node), LOC((yylsp[0]))); }
#line 3162 "mini_c.tab.cpp"
    break;

  case 213: /* block_item: declaration  */
#line 706 "mini_c.y"
        { (yyval.node) = new_block_decl((yyvsp[0].node), LOC((yylsp[0]))); }
#line 3168 "mini_c.tab.cpp"
    break;

  case 214: /* block_item: statement  */
#line 708 "mini_c.y"
        { (yyval.node) = new_block_stmt((yyvsp[0].node), LOC((yylsp[0]))); }
#line 3174 "mini_c.tab.cpp"
    break;

  case 215: /* expression_statement: ';'  */
#line 714 "mini_c.y"
        { (yyval.node) = NULL; }
#line 3180 "mini_c.tab.cpp"
    break;

  case 216: /* expression_statement: expression ';'  */
#line 716 "mini_c.y"
        { (yyval.node) = new_expr_stmt((yyvsp[-1].node), LOC((yylsp[0]))); }
#line 3186 "mini_c.tab.cpp"
    break;

  case 217: /* selection_statement: IF '(' expression ')' statement  */
#line 721 "mini_c.y"
        { (yyval.node) = new_if_stmt((yyvsp[-2].node), (yyvsp[0].node), NULL, LOC((yylsp[-4]))); }
#line 3192 "mini_c.tab.cpp"
    break;

  case 218: /* selection_statement: IF '(' expression ')' statement ELSE statement  */
#line 723 "mini_c.y"
        { (yyval.node) = new_if_stmt((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), LOC((yylsp[-6]))); }
#line 3198 "mini_c.tab.cpp"
    break;

  case 219: /* selection_statement: SWITCH '(' expression ')' statement  */
#line 725 "mini_c.y"
        { (yyval.node) = new_switch_stmt((yyvsp[-2].node), (yyvsp[0].node), LOC((yylsp[-4]))); }
#line 3204 "mini_c.tab.cpp"
    break;

  case 220: /* iteration_statement: WHILE '(' expression ')' statement  */
#line 730 "mini_c.y"
        { (yyval.node) = new_while_stmt((yyvsp[-2].node), (yyvsp[0].node), LOC((yylsp[-4]))); }
#line 3210 "mini_c.tab.cpp"
    break;

  case 221: /* iteration_statement: DO statement WHILE '(' expression ')' ';'  */
#line 732 "mini_c.y"
        { (yyval.node) = new_do_while_stmt((yyvsp[-5].node), (yyvsp[-2].node), LOC((yylsp[-6]))); }
#line 3216 "mini_c.tab.cpp"
    break;

  case 222: /* iteration_statement: FOR '(' expression_statement expression_statement ')' statement  */
#line 734 "mini_c.y"
        { (yyval.node) = new_for_stmt((yyvsp[-3].node), (yyvsp[-2].node), NULL, (yyvsp[0].node), LOC((yylsp[-5]))); }
#line 3222 "mini_c.tab.cpp"
    break;

  case 223: /* iteration_statement: FOR '(' expression_statement expression_statement expression ')' statement  */
#line 736 "mini_c.y"
        { (yyval.node) = new_for_stmt((yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node), LOC((yylsp[-6]))); }
#line 3228 "mini_c.tab.cpp"
    break;

  case 224: /* iteration_statement: FOR '(' declaration expression_statement ')' statement  */
#line 738 "mini_c.y"
        { (yyval.node) = new_for_decl_stmt((yyvsp[-3].node), (yyvsp[-2].node), NULL, (yyvsp[0].node), LOC((yylsp[-5]))); }
#line 3234 "mini_c.tab.cpp"
    break;

  case 225: /* iteration_statement: FOR '(' declaration expression_statement expression ')' statement  */
#line 740 "mini_c.y"
        { (yyval.node) = new_for_decl_stmt((yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node), LOC((yylsp[-6]))); }
#line 3240 "mini_c.tab.cpp"
    break;

  case 226: /* jump_statement: GOTO IDENTIFIER ';'  */
#line 746 "mini_c.y"
        { (yyval.node) = new_goto_stmt((yyvsp[-1].sval), LOC((yylsp[-2]))); }
#line 3246 "mini_c.tab.cpp"
    break;

  case 227: /* jump_statement: CONTINUE ';'  */
#line 748 "mini_c.y"
        { (yyval.node) = new_continue_stmt(LOC((yylsp[-1]))); }
#line 3252 "mini_c.tab.cpp"
    break;

  case 228: /* jump_statement: BREAK ';'  */
#line 750 "mini_c.y"
        { (yyval.node) = new_break_stmt(LOC((yylsp[-1]))); }
#line 3258 "mini_c.tab.cpp"
    break;

  case 229: /* jump_statement: RETURN ';'  */
#line 752 "mini_c.y"
        { (yyval.node) = new_return_stmt(NULL, LOC((yylsp[-1]))); }
#line 3264 "mini_c.tab.cpp"
    break;

  case 230: /* jump_statement: RETURN expression ';'  */
#line 754 "mini_c.y"
        { (yyval.node) = new_return_stmt((yyvsp[-1].node), LOC((yylsp[-2]))); }
#line 3270 "mini_c.tab.cpp"
    break;

  case 231: /* translation_unit: external_declaration  */
#line 760 "mini_c.y"
        { ast_root = (yyval.node) = (yyvsp[0].node); }
#line 3276 "mini_c.tab.cpp"
    break;

  case 232: /* translation_unit: translation_unit external_declaration  */
#line 762 "mini_c.y"
        { ast_root = (yyval.node) = new_translation_unit((yyvsp[-1].node), (yyvsp[0].node), LOC((yylsp[0]))); }
#line 3282 "mini_c.tab.cpp"
    break;

  case 233: /* external_declaration: function_definition  */
#line 767 "mini_c.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 3288 "mini_c.tab.cpp"
    break;

  case 234: /* external_declaration: declaration  */
#line 769 "mini_c.y"
        { (yyval.node) = new_decl_stmt((yyvsp[0].node), LOC((yylsp[0]))); }
#line 3294 "mini_c.tab.cpp"
    break;

  case 235: /* function_definition: declaration_specifiers declarator declaration_list compound_statement  */
#line 775 "mini_c.y"
        { (yyval.node) = new_function_def((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node), LOC((yylsp[-2]))); }
#line 3300 "mini_c.tab.cpp"
    break;

  case 236: /* function_definition: declaration_specifiers declarator compound_statement  */
#line 777 "mini_c.y"
        { (yyval.node) = new_function_def((yyvsp[-2].node), (yyvsp[-1].node), NULL, (yyvsp[0].node), LOC((yylsp[-1]))); }
#line 3306 "mini_c.tab.cpp"
    break;

  case 237: /* declaration_list: declaration  */
#line 783 "mini_c.y"
        { (yyval.node) = new_declaration_list((yyvsp[0].node), LOC((yylsp[0]))); }
#line 3312 "mini_c.tab.cpp"
    break;

  case 238: /* declaration_list: declaration_list declaration  */
#line 785 "mini_c.y"
        { (yyval.node) = append_declaration_list((yyvsp[-1].node), (yyvsp[0].node), LOC((yylsp[0]))); }
#line 3318 "mini_c.tab.cpp"
    break;


#line 3322 "mini_c.tab.cpp"

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
  *++yylsp = yyloc;

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

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc);
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 789 "mini_c.y"

#include <stdio.h>

extern char yytext[];
extern int column;

void yyerror(char const *s)
{
    fflush(stdout);
    printf("\n%*s\n%*s\n", column, "^", column, s);
}
