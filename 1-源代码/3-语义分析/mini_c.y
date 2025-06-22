%defines
%output "mini_c.tab.cpp"
%{
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

%}

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%locations

%union {
    int       ival;   /* 运算符枚举、数值常量等整数值 */
    char     *sval;   /* 标识符、字符串、常量的原始文本 */
    ASTNode  *node;   /* AST 子树 */
}

/*—— 所有会产生 ASTNode* 的 nonterminal ——*/
%type <node>
    primary_expression
    postfix_expression
    argument_expression_list
    unary_expression
    cast_expression
    multiplicative_expression
    additive_expression
    shift_expression
    relational_expression
    equality_expression
    and_expression
    exclusive_or_expression
    inclusive_or_expression
    logical_and_expression
    logical_or_expression
    conditional_expression
    assignment_expression
    expression
    constant_expression

    declaration
    declaration_specifiers
    init_declarator_list
    init_declarator


    struct_or_union_specifier

    struct_declaration_list
    struct_declaration
    specifier_qualifier_list
    struct_declarator_list
    struct_declarator

    enum_specifier
    enumerator_list
    enumerator



    declarator
    direct_declarator
    pointer

    type_qualifier_list
    parameter_type_list
    parameter_list
    parameter_declaration
    identifier_list

    type_name
    abstract_declarator
    direct_abstract_declarator

    initializer
    initializer_list
    designation
    designator_list
    designator

    statement
    labeled_statement
    compound_statement
    block_item_list
    block_item

    expression_statement
    selection_statement
    iteration_statement
    jump_statement

    translation_unit
    external_declaration
    function_definition
    declaration_list
;

/*—— 运算符枚举，用 ival 存 ——*/
%type <ival> assignment_operator unary_operator

%type <ival> storage_class_specifier type_qualifier function_specifier
%type <node> type_specifier

%type <ival> struct_or_union



/*—— token 的语义值类型 ——*/
%token  <sval> IDENTIFIER
%token  <sval> CONSTANT
%token  <sval> STRING_LITERAL
%token  <sval> TYPE_NAME
%token         SIZEOF

%token         PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP
%token         LE_OP GE_OP EQ_OP NE_OP AND_OP OR_OP
%token         MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN SUB_ASSIGN
%token         LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN

%token         TYPEDEF EXTERN STATIC AUTO REGISTER INLINE RESTRICT
%token         CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token         BOOL COMPLEX IMAGINARY
%token         STRUCT UNION ENUM ELLIPSIS
%token         CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%start translation_unit
%%


primary_expression
    : IDENTIFIER              { $$ = new_id_node($1, LOC(@1)); }
    | CONSTANT                { $$ = new_const_node($1, LOC(@1)); }
    | STRING_LITERAL          { $$ = new_string_node($1, LOC(@1)); }
    | '(' expression ')'      { $$ = $2; $$->loc = LOC(@3); }
    ;

postfix_expression
    : primary_expression                                           { $$ = $1; }
    | postfix_expression '[' expression ']'                        { $$ = new_array_ref_node($1, $3, LOC(@2)); }
    | postfix_expression '(' ')'                                   { $$ = new_func_call_node($1, NULL, LOC(@2)); }
    | postfix_expression '(' argument_expression_list ')'          { $$ = new_func_call_node($1, $3, LOC(@2)); }
    | postfix_expression '.' IDENTIFIER                            { $$ = new_struct_ref_node($1, $3, false, LOC(@2)); }
    | postfix_expression PTR_OP IDENTIFIER                         { $$ = new_struct_ref_node($1, $3, true, LOC(@2)); }
    | postfix_expression INC_OP                                    { $$ = new_post_inc_node($1, LOC(@2)); }
    | postfix_expression DEC_OP                                    { $$ = new_post_dec_node($1, LOC(@2)); }
    | '(' type_name ')' '{' initializer_list '}'                   { $$ = new_compound_literal_node($2, $5, LOC(@1)); }
    | '(' type_name ')' '{' initializer_list ',' '}'               { $$ = new_compound_literal_node($2, $5, LOC(@1)); }
    ;


argument_expression_list
    : assignment_expression                                        { $$ = new_arg_list($1, LOC(@1)); }
    | argument_expression_list ',' assignment_expression           { $$ = append_arg_list($1, $3, LOC(@2)); }
    ;

unary_expression
    : postfix_expression                                           { $$ = $1; }
    | INC_OP unary_expression                                      { $$ = new_pre_inc_node($2, LOC(@1)); }
    | DEC_OP unary_expression                                      { $$ = new_pre_dec_node($2, LOC(@1)); }
    | unary_operator cast_expression                               { $$ = new_unary_op_node($1, $2, LOC(@1)); }
    | SIZEOF unary_expression                                      { $$ = new_sizeof_node($2, false, LOC(@1)); }
    | SIZEOF '(' type_name ')'                                     { $$ = new_sizeof_node($3, true, LOC(@1)); }
    ;

unary_operator
    : '&'   { $$ = op_address; }
    | '*'   { $$ = op_deref; }
    | '+'   { $$ = op_unary_plus; }
    | '-'   { $$ = op_neg; }
    | '~'   { $$ = op_bitnot; }
    | '!'   { $$ = op_not; }
    ;


cast_expression
    : unary_expression                                             { $$ = $1; }
    | '(' type_name ')' cast_expression                            { $$ = new_cast_node($2, $4, LOC(@1)); }
    ;

multiplicative_expression
    : cast_expression                                              { $$ = $1; }
    | multiplicative_expression '*' cast_expression                { $$ = new_binop_node('*', $1, $3, LOC(@2)); }
    | multiplicative_expression '/' cast_expression                { $$ = new_binop_node('/', $1, $3, LOC(@2)); }
    | multiplicative_expression '%' cast_expression                { $$ = new_binop_node('%', $1, $3, LOC(@2)); }
    ;


additive_expression
    : multiplicative_expression                                    { $$ = $1; }
    | additive_expression '+' multiplicative_expression            { $$ = new_binop_node('+', $1, $3, LOC(@2)); }
    | additive_expression '-' multiplicative_expression            { $$ = new_binop_node('-', $1, $3, LOC(@2)); }
    ;


shift_expression
    : additive_expression                                          { $$ = $1; }
    | shift_expression LEFT_OP additive_expression                 { $$ = new_binop_node(SHL, $1, $3, LOC(@2)); }
    | shift_expression RIGHT_OP additive_expression                { $$ = new_binop_node(SHR, $1, $3, LOC(@2)); }
    ;


relational_expression
    : shift_expression                                             { $$ = $1; }
    | relational_expression '<' shift_expression                   { $$ = new_binop_node('<', $1, $3, LOC(@2)); }
    | relational_expression '>' shift_expression                   { $$ = new_binop_node('>', $1, $3, LOC(@2)); }
    | relational_expression LE_OP shift_expression                 { $$ = new_binop_node(LE, $1, $3, LOC(@2)); }
    | relational_expression GE_OP shift_expression                 { $$ = new_binop_node(GE, $1, $3, LOC(@2)); }
    ;


equality_expression
    : relational_expression                                        { $$ = $1; }
    | equality_expression EQ_OP relational_expression              { $$ = new_binop_node(EQ, $1, $3, LOC(@2)); }
    | equality_expression NE_OP relational_expression              { $$ = new_binop_node(NE, $1, $3, LOC(@2)); }
    ;



and_expression
    : equality_expression
        { $$ = $1; }
    | and_expression '&' equality_expression
        { $$ = new_binop_node('&', $1, $3, LOC(@2)); }
    ;


exclusive_or_expression
    : and_expression
        { $$ = $1; }
    | exclusive_or_expression '^' and_expression
        { $$ = new_binop_node('^', $1, $3, LOC(@2)); }
    ;


inclusive_or_expression
    : exclusive_or_expression
        { $$ = $1; }
    | inclusive_or_expression '|' exclusive_or_expression
        { $$ = new_binop_node('|', $1, $3, LOC(@2)); }
    ;


logical_and_expression
    : inclusive_or_expression
        { $$ = $1; }
    | logical_and_expression AND_OP inclusive_or_expression
        { $$ = new_logical_and_node($1, $3, LOC(@2)); }
    ;


logical_or_expression
    : logical_and_expression
        { $$ = $1; }
    | logical_or_expression OR_OP logical_and_expression
        { $$ = new_logical_or_node($1, $3, LOC(@2)); }
    ;


conditional_expression
    : logical_or_expression
        { $$ = $1; }
    | logical_or_expression '?' expression ':' conditional_expression
        { $$ = new_conditional_node($1, $3, $5, LOC(@2)); }
    ;


assignment_expression
    : conditional_expression
        { $$ = $1; }
    | unary_expression assignment_operator assignment_expression
        { $$ = new_assign_node($1, $2, $3, LOC(@2)); }
    ;


assignment_operator
    : '='           { $$ = op_assign; }
    | MUL_ASSIGN    { $$ = op_mul_assign; }
    | DIV_ASSIGN    { $$ = op_div_assign; }
    | MOD_ASSIGN    { $$ = op_mod_assign; }
    | ADD_ASSIGN    { $$ = op_add_assign; }
    | SUB_ASSIGN    { $$ = op_sub_assign; }
    | LEFT_ASSIGN   { $$ = op_shl_assign; }
    | RIGHT_ASSIGN  { $$ = op_shr_assign; }
    | AND_ASSIGN    { $$ = op_and_assign; }
    | XOR_ASSIGN    { $$ = op_xor_assign; }
    | OR_ASSIGN     { $$ = op_or_assign; }
    ;

expression
    : assignment_expression
        { $$ = $1; }
    | expression ',' assignment_expression
        { $$ = new_expr_list($1, $3, LOC(@2)); }
    ;


constant_expression
    : conditional_expression
        { $$ = $1; }
    ;

/* 声明相关 */
declaration
    : declaration_specifiers ';'
        { $$ = new_decl_stmt($1, LOC(@2)); }
    | declaration_specifiers init_declarator_list ';'
        { $$ = new_declaration($1, $2, LOC(@3)); }
    ;


declaration_specifiers
    : storage_class_specifier
        { $$ = new_spec_list($1, LOC(@1)); }
    | storage_class_specifier declaration_specifiers
        { $$ = append_spec_list($2, $1, LOC(@1)); }
    | type_specifier
        { $$ = new_spec_list($1, LOC(@1)); }
    | type_specifier declaration_specifiers
        { $$ = append_spec_list($2, $1, LOC(@1)); }
    | type_qualifier
        { $$ = new_spec_list($1, LOC(@1)); }
    | type_qualifier declaration_specifiers
        { $$ = append_spec_list($2, $1, LOC(@1)); }
    | function_specifier
        { $$ = new_spec_list($1, LOC(@1)); }
    | function_specifier declaration_specifiers
        { $$ = append_spec_list($2, $1, LOC(@1)); }
    ;


init_declarator_list
    : init_declarator
        { $$ = new_init_list($1, LOC(@1)); }
    | init_declarator_list ',' init_declarator
        { $$ = append_init_list($1, $3, LOC(@2)); }
    ;


init_declarator
    : declarator
        { $$ = new_init_decl($1, NULL, LOC(@1)); }
    | declarator '=' initializer
        { $$ = new_init_decl($1, $3, LOC(@2)); }
    ;


storage_class_specifier
    : TYPEDEF   { $$ = SC_TYPEDEF; }
    | EXTERN    { $$ = SC_EXTERN; }
    | STATIC    { $$ = SC_STATIC; }
    | AUTO      { $$ = SC_AUTO; }
    | REGISTER  { $$ = SC_REGISTER; }
    ;

type_specifier
    : VOID       { $$ = make_type_spec_node(TS_VOID); }
    | CHAR       { $$ = make_type_spec_node(TS_CHAR); }
    | SHORT      { $$ = make_type_spec_node(TS_SHORT); }
    | INT        { $$ = make_type_spec_node(TS_INT); }
    | LONG       { $$ = make_type_spec_node(TS_LONG); }
    | FLOAT      { $$ = make_type_spec_node(TS_FLOAT); }
    | DOUBLE     { $$ = make_type_spec_node(TS_DOUBLE); }
    | SIGNED     { $$ = make_type_spec_node(TS_SIGNED); }
    | UNSIGNED   { $$ = make_type_spec_node(TS_UNSIGNED); }
    | BOOL       { $$ = make_type_spec_node(TS_BOOL); }
    | COMPLEX    { $$ = make_type_spec_node(TS_COMPLEX); }
    | IMAGINARY  { $$ = make_type_spec_node(TS_IMAGINARY); }
    | struct_or_union_specifier
        { $$ = $1; }
    | enum_specifier
        { $$ = $1; }
    | TYPE_NAME
        { $$ = make_type_spec_node(TS_TYPE_NAME); }
    ;

struct_or_union_specifier
    : struct_or_union IDENTIFIER '{' struct_declaration_list '}'
        { $$ = new_struct_su_node(static_cast<StructUnionKind>($1), $2, $4, LOC(@2)); }
    | struct_or_union '{' struct_declaration_list '}'
        { $$ = new_struct_su_node(static_cast<StructUnionKind>($1), nullptr, $3, LOC(@2)); }
    | struct_or_union IDENTIFIER
        { $$ = new_struct_su_node(static_cast<StructUnionKind>($1), $2, nullptr, LOC(@2)); }
    ;



struct_or_union
    : STRUCT  { $$ = SU_STRUCT; }
    | UNION   { $$ = SU_UNION; }
    ;

struct_declaration_list
    : struct_declaration
        { $$ = new_sdecl_list($1, LOC(@1)); }
    | struct_declaration_list struct_declaration
        { $$ = append_sdecl_list($1, $2, LOC(@2)); }
    ;


struct_declaration
    : specifier_qualifier_list struct_declarator_list ';'
        { $$ = new_struct_decl($1, $2, LOC(@3)); }
    ;

specifier_qualifier_list
    : type_specifier specifier_qualifier_list
        { $$ = append_specq_list($2, $1, LOC(@1)); }
    | type_specifier
        { $$ = new_specq_list($1, LOC(@1)); }
    | type_qualifier specifier_qualifier_list
        { $$ = append_specq_list($2, $1, LOC(@1)); }
    | type_qualifier
        { $$ = new_specq_list($1, LOC(@1)); }
    ;


struct_declarator_list
    : struct_declarator
        { $$ = new_sdeclarator_list($1, LOC(@1)); }
    | struct_declarator_list ',' struct_declarator
        { $$ = append_sdeclarator_list($1, $3, LOC(@2)); }
    ;

    
struct_declarator
    : declarator
        { $$ = $1; }
    | ':' constant_expression
        { $$ = new_bitfield_node(NULL, $2, LOC(@1)); }
    | declarator ':' constant_expression
        { $$ = new_bitfield_node($1, $3, LOC(@2)); }
    ;


enum_specifier
    : ENUM '{' enumerator_list '}'
        { $$ = new_enum_node(NULL, $3, LOC(@1)); }
    | ENUM IDENTIFIER '{' enumerator_list '}'
        { $$ = new_enum_node($2, $4, LOC(@1)); }
    | ENUM '{' enumerator_list ',' '}'
        { $$ = new_enum_node(NULL, $3, LOC(@1)); }
    | ENUM IDENTIFIER '{' enumerator_list ',' '}'
        { $$ = new_enum_node($2, $4, LOC(@1)); }
    | ENUM IDENTIFIER
        { $$ = new_enum_node($2, NULL, LOC(@1)); }
    ;


enumerator_list
    : enumerator
        { $$ = new_enum_list($1, LOC(@1)); }
    | enumerator_list ',' enumerator
        { $$ = append_enum_list($1, $3, LOC(@2)); }
    ;


enumerator
    : IDENTIFIER
        { $$ = new_enum_const($1, NULL, LOC(@1)); }
    | IDENTIFIER '=' constant_expression
        { $$ = new_enum_const($1, $3, LOC(@1)); }
    ;


type_qualifier
    : CONST
        { $$ = TQ_CONST; }
    | RESTRICT
        { $$ = TQ_RESTRICT; }
    | VOLATILE
        { $$ = TQ_VOLATILE; }
    ;

function_specifier
    : INLINE
        { $$ = FS_INLINE; }
    ;

declarator
    : pointer direct_declarator
        { $$ = new_declarator_node($1, $2, LOC(@1)); }
    | direct_declarator
        { $$ = new_declarator_node(NULL, $1, LOC(@1)); }
    ;


direct_declarator
    : IDENTIFIER
        { $$ = new_decl_ident($1, LOC(@1)); }
    | '(' declarator ')'
        { $$ = $2; $$->loc = LOC(@3); }
    | direct_declarator '[' type_qualifier_list assignment_expression ']'
        { $$ = new_array_decl($1, $3, $4, NULL, NULL, LOC(@2)); }
    | direct_declarator '[' type_qualifier_list ']'
        { $$ = new_array_decl($1, $3, NULL, NULL, NULL, LOC(@2)); }
    | direct_declarator '[' assignment_expression ']'
        { $$ = new_array_decl($1, NULL, $3, NULL, NULL, LOC(@2)); }
    | direct_declarator '[' STATIC type_qualifier_list assignment_expression ']'
        { $$ = new_array_decl($1, $4, $5, true, NULL, LOC(@2)); }
    | direct_declarator '[' type_qualifier_list STATIC assignment_expression ']'
        { $$ = new_array_decl($1, $3, $5, true, NULL, LOC(@2)); }
    | direct_declarator '[' type_qualifier_list '*' ']'
        { $$ = new_array_decl($1, $3, NULL, NULL, true, LOC(@2)); }
    | direct_declarator '[' '*' ']'
        { $$ = new_array_decl($1, NULL, NULL, NULL, true, LOC(@2)); }
    | direct_declarator '[' ']'
        { $$ = new_array_decl($1, NULL, NULL, NULL, false, LOC(@2)); }
    | direct_declarator '(' parameter_type_list ')'
        { $$ = new_func_decl($1, $3, LOC(@2)); }
    | direct_declarator '(' identifier_list ')'
        { $$ = new_oldstyle_func_decl($1, $3, LOC(@2)); }
    | direct_declarator '(' ')'
        { $$ = new_func_decl($1, NULL, LOC(@2)); }
    ;


pointer
    : '*'
        { $$ = new_pointer(NULL, LOC(@1)); }
    | '*' type_qualifier_list
        { $$ = new_pointer($2, LOC(@1)); }
    | '*' pointer
        { $$ = prepend_pointer(NULL, $2, LOC(@1)); }
    | '*' type_qualifier_list pointer
        { $$ = prepend_pointer($2, $3, LOC(@1)); }
    ;


type_qualifier_list
    : type_qualifier
        { $$ = new_tq_list($1, LOC(@1)); }
    | type_qualifier_list type_qualifier
        { $$ = append_tq_list($1, $2, LOC(@2)); }
    ;

parameter_type_list
    : parameter_list
        { $$ = $1; }
    | parameter_list ',' ELLIPSIS
        { $$ = new_param_list_ellipsis($1, LOC(@2)); }
    ;


parameter_list
    : parameter_declaration
        { $$ = new_param_list($1, LOC(@1)); }
    | parameter_list ',' parameter_declaration
        { $$ = append_param_list($1, $3, LOC(@2)); }
    ;


parameter_declaration
    : declaration_specifiers declarator
        { $$ = new_param_decl($1, $2, LOC(@2)); }
    | declaration_specifiers abstract_declarator
        { $$ = new_param_decl($1, $2, LOC(@2)); }
    | declaration_specifiers
        { $$ = new_param_decl($1, NULL, LOC(@1)); }
    ;


identifier_list
    : IDENTIFIER
        { $$ = new_id_list($1, LOC(@1)); }
    | identifier_list ',' IDENTIFIER
        { $$ = append_id_list($1, $3, LOC(@3)); }
    ;

type_name
    : specifier_qualifier_list
        { $$ = new_type_name($1, NULL, LOC(@1)); }
    | specifier_qualifier_list abstract_declarator
        { $$ = new_type_name($1, $2, LOC(@1)); }
    ;


abstract_declarator
    : pointer
        { $$ = new_abs_decl($1, NULL, LOC(@1)); }
    | direct_abstract_declarator
        { $$ = new_abs_decl(NULL, $1, LOC(@1)); }
    | pointer direct_abstract_declarator
        { $$ = new_abs_decl($1, $2, LOC(@1)); }
    ;


direct_abstract_declarator
    : '(' abstract_declarator ')'
        { $$ = $2; $$->loc = LOC(@3); }
    | '[' ']'
        { $$ = new_abs_array(NULL, NULL, LOC(@1)); }
    | '[' assignment_expression ']'
        { $$ = new_abs_array($2, NULL, LOC(@1)); }
    | direct_abstract_declarator '[' ']'
        { $$ = new_abs_array_child($1, NULL, NULL, LOC(@2)); }
    | direct_abstract_declarator '[' assignment_expression ']'
        { $$ = new_abs_array_child($1, $3, NULL, LOC(@2)); }
    | '[' '*' ']'
        { $$ = new_abs_array(NULL, true, LOC(@1)); }
    | direct_abstract_declarator '[' '*' ']'
        { $$ = new_abs_array_child($1, NULL, true, LOC(@2)); }
    | '(' ')'
        { $$ = new_abs_func(NULL, LOC(@1)); }
    | '(' parameter_type_list ')'
        { $$ = new_abs_func($2, LOC(@1)); }
    | direct_abstract_declarator '(' ')'
        { $$ = new_abs_func_child($1, NULL, LOC(@2)); }
    | direct_abstract_declarator '(' parameter_type_list ')'
        { $$ = new_abs_func_child($1, $3, LOC(@2)); }
    ;


initializer
    : assignment_expression
        { $$ = new_init_expr($1, LOC(@1)); }
    | '{' initializer_list '}'
        { $$ = new_init_list_node($2, LOC(@1)); }
    | '{' initializer_list ',' '}'
        { $$ = new_init_list_node($2, LOC(@1)); }
    ;


initializer_list
    : initializer
        { $$ = new_init_item_list($1, LOC(@1)); }
    | designation initializer
        { $$ = new_designated_init($1, $2, LOC(@1)); }
    | initializer_list ',' initializer
        { $$ = append_init_item($1, $3, LOC(@2)); }
    | initializer_list ',' designation initializer
        { $$ = append_designated_init($1, $3, $4, LOC(@2)); }
    ;


designation
    : designator_list '='
        { $$ = $1; }
    ;


designator_list
    : designator
        { $$ = new_designator_list($1, LOC(@1)); }
    | designator_list designator
        { $$ = append_designator_list($1, $2, LOC(@2)); }
    ;

designator
    : '[' constant_expression ']'
        { $$ = new_array_designator($2, LOC(@1)); }
    | '.' IDENTIFIER
        { $$ = new_field_designator($2, LOC(@1)); }
    ;


statement
    : labeled_statement       { $$ = $1; }
    | compound_statement      { $$ = $1; }
    | expression_statement    { $$ = $1; }
    | selection_statement     { $$ = $1; }
    | iteration_statement     { $$ = $1; }
    | jump_statement          { $$ = $1; }
    ;


labeled_statement
    : IDENTIFIER ':' statement
        { $$ = new_labeled_stmt_id($1, $3, LOC(@1)); }
    | CASE constant_expression ':' statement
        { $$ = new_case_stmt($2, $4, LOC(@1)); }
    | DEFAULT ':' statement
        { $$ = new_default_stmt($3, LOC(@1)); }
    ;

compound_statement
    : '{' '}'
        { $$ = new_compound_stmt(NULL, LOC(@1)); }
    | '{' block_item_list '}'
        { $$ = new_compound_stmt($2, LOC(@1)); }
    ;


block_item_list
    : block_item
        { $$ = new_block_item_list($1, LOC(@1)); }
    | block_item_list block_item
        { $$ = append_block_item_list($1, $2, LOC(@2)); }
    ;


block_item
    : declaration
        { $$ = new_block_decl($1, LOC(@1)); }
    | statement
        { $$ = new_block_stmt($1, LOC(@1)); }
    ;


expression_statement
    : ';'
        { $$ = NULL; }
    | expression ';'
        { $$ = new_expr_stmt($1, LOC(@2)); }
    ;

selection_statement
    : IF '(' expression ')' statement    %prec LOWER_THAN_ELSE
        { $$ = new_if_stmt($3, $5, NULL, LOC(@1)); }
    | IF '(' expression ')' statement ELSE statement
        { $$ = new_if_stmt($3, $5, $7, LOC(@1)); }
    | SWITCH '(' expression ')' statement
        { $$ = new_switch_stmt($3, $5, LOC(@1)); }
    ;

iteration_statement
    : WHILE '(' expression ')' statement
        { $$ = new_while_stmt($3, $5, LOC(@1)); }
    | DO statement WHILE '(' expression ')' ';'
        { $$ = new_do_while_stmt($2, $5, LOC(@1)); }
    | FOR '(' expression_statement expression_statement ')' statement
        { $$ = new_for_stmt($3, $4, NULL, $6, LOC(@1)); }
    | FOR '(' expression_statement expression_statement expression ')' statement
        { $$ = new_for_stmt($3, $4, $5, $7, LOC(@1)); }
    | FOR '(' declaration expression_statement ')' statement
        { $$ = new_for_decl_stmt($3, $4, NULL, $6, LOC(@1)); }
    | FOR '(' declaration expression_statement expression ')' statement
        { $$ = new_for_decl_stmt($3, $4, $5, $7, LOC(@1)); }
    ;


jump_statement
    : GOTO IDENTIFIER ';'
        { $$ = new_goto_stmt($2, LOC(@1)); }
    | CONTINUE ';'
        { $$ = new_continue_stmt(LOC(@1)); }
    | BREAK ';'
        { $$ = new_break_stmt(LOC(@1)); }
    | RETURN ';'
        { $$ = new_return_stmt(NULL, LOC(@1)); }
    | RETURN expression ';'
        { $$ = new_return_stmt($2, LOC(@1)); }
    ;


translation_unit
    : external_declaration
        { ast_root = $$ = $1; }
    | translation_unit external_declaration
        { ast_root = $$ = new_translation_unit($1, $2, LOC(@2)); }
    ;

external_declaration
    : function_definition
        { $$ = $1; }
    | declaration
        { $$ = new_decl_stmt($1, LOC(@1)); }
    ;


function_definition
    : declaration_specifiers declarator declaration_list compound_statement
        { $$ = new_function_def($1, $2, $3, $4, LOC(@2)); }
    | declaration_specifiers declarator compound_statement
        { $$ = new_function_def($1, $2, NULL, $3, LOC(@2)); }
    ;


declaration_list
    : declaration
        { $$ = new_declaration_list($1, LOC(@1)); }
    | declaration_list declaration
        { $$ = append_declaration_list($1, $2, LOC(@2)); }
    ;


%%
#include <stdio.h>

extern char yytext[];
extern int column;

void yyerror(char const *s)
{
    fflush(stdout);
    printf("\n%*s\n%*s\n", column, "^", column, s);
}
