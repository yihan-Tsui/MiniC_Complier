#ifndef MINI_C_AST_H
#define MINI_C_AST_H

#include <string>
#include <vector>
#include <cstdint>

/*──────────────────────────────
 * 0.  语义分析辅助
 *─────────────────────────────*/

// 在 type.h 中定义具体的 Type 类
struct Type;

// 用于记录 AST 节点在源文件中的行、列位置
struct SourceLoc {
    int line = 0;
    int col  = 0;
};

/*──────────────────────────────
 * 1.  词法‑语法层枚举
 *─────────────────────────────*/
//——单目运算符——
enum UnaryOp : int {
    op_address, op_deref, op_unary_plus, op_neg,
    op_bitnot, op_not
};

//——赋值运算符（含复合）——
enum AssignOp : int {
    op_assign, op_mul_assign, op_div_assign, op_mod_assign,
    op_add_assign, op_sub_assign, op_shl_assign, op_shr_assign,
    op_and_assign, op_xor_assign, op_or_assign
};

//——额外二元运算符——
enum BinaryOp : int {
    // ASCII 运算符直接用字面字符
    SHL = 256, SHR,
    LE, GE, EQ, NE
};

//——存储类别说明符——
enum StorageClass : int {
    SC_TYPEDEF, SC_EXTERN, SC_STATIC, SC_AUTO, SC_REGISTER
};

//——基本类型说明符——
enum TypeSpecifier : int {
    TS_VOID, TS_CHAR, TS_SHORT, TS_INT, TS_LONG,
    TS_FLOAT, TS_DOUBLE, TS_SIGNED, TS_UNSIGNED,
    TS_BOOL, TS_COMPLEX, TS_IMAGINARY,
    TS_TYPE_NAME            // typedef‑alias
};

//——struct / union——
enum StructUnionKind : int { SU_STRUCT, SU_UNION };

//——限定符 / 函数特性——
enum TypeQualifier : int { TQ_CONST, TQ_RESTRICT, TQ_VOLATILE };
enum FuncSpecifier : int { FS_INLINE };

/*──────────────────────────────
 * 2.  AST 结点与标签
 *─────────────────────────────*/
enum class ASTTag : std::uint16_t {
    /*── 基本 / 运算类 ──*/
    ID, CONST, STRING,
    UNARY, BINARY, LOGIC_AND, LOGIC_OR,
    COND, ASSIGN,
    ARRAY_REF, STRUCT_REF, FUNC_CALL,
    SIZEOF_EXPR, CAST_EXPR, COMPOUND_LITERAL,
    EXPR_LIST, ARG_LIST,
    PRE_INC,  PRE_DEC,      // ← 新增
    POST_INC, POST_DEC,     // ← 新增
    /*── 声明 & 类型 ──*/
    SPECIFIER, SPEC_LIST, DECLARATION, INIT_DECL, INIT_DECL_LIST,
    DECL_SPEC_LIST, DECLARATOR, POINTER_DECL,
    ARRAY_DECL, FUNC_DECL, OLD_FUNC_DECL,
    PARAM_DECL, PARAM_LIST, PARAM_LIST_ELIPS,
    ID_LIST, TYPE_NAME_NODE,
    ABS_DECL, ABS_ARRAY, ABS_ARRAY_CHILD,
    ABS_FUNC, ABS_FUNC_CHILD,
    POINTER, POINTER_CHAIN,
    TQ_LIST,

    /*── struct / enum ──*/
    SU_SPEC, STRUCT_DECL, STRUCT_DECL_LIST,
    STRUCT_DECLARATOR, STRUCT_DECLARATOR_LIST,
    BITFIELD,
    ENUM_SPEC, ENUM_LIST, ENUM_CONST,

    SPECQ_LIST,

    /*── 初始化 / 设计化初始化 ──*/
    INIT_EXPR, INIT_LIST_NODE, INIT_ITEM_LIST,
    DESIGNATOR_LIST, DESIGNATED_INIT,
    ARRAY_DESIGNATOR, FIELD_DESIGNATOR,

    /*── 语句 ──*/
    LABELED_ID_STMT, CASE_STMT, DEFAULT_STMT,
    COMPOUND_STMT, BLOCK_ITEM_LIST, BLOCK_DECL, BLOCK_STMT,
    EXPR_STMT,
    IF_STMT, SWITCH_STMT,
    WHILE_STMT, DO_WHILE_STMT,
    FOR_STMT, FOR_DECL_STMT,
    GOTO_STMT, CONTINUE_STMT, BREAK_STMT, RETURN_STMT,

    /*── 顶层 ──*/
    TRANSL_UNIT, DECL_STMT, FUNCTION_DEF, DECL_LIST
};

struct ASTNode {
    ASTTag                    tag;
    std::string               text;     // 标识符
    std::int64_t              ival{};   // 数值或枚举值
    bool                      flag{};
    SourceLoc                 loc{};    // 源代码行列信息
    Type*                     type{};   // 语义分析后填充的类型指针
    std::vector<ASTNode*>     kids;     // 子节点（按动作顺序）
    explicit ASTNode(ASTTag t, SourceLoc loc_ = SourceLoc{})
        : tag(t), loc(loc_) {}
};

/* 方便在别处直接引用整棵语法树 */
extern ASTNode *ast_root;

/*──────────────────────────────
 * 3.  表达式构造函数
 *─────────────────────────────*/
ASTNode* new_id_node   (const char* name,   SourceLoc loc);
ASTNode* new_const_node(const char* literal, SourceLoc loc);
ASTNode* new_string_node(const char* literal, SourceLoc loc);

ASTNode* new_array_ref_node(ASTNode* array, ASTNode* index, SourceLoc loc);
ASTNode* new_func_call_node(ASTNode* callee, ASTNode* arg_list, SourceLoc loc);
ASTNode* new_struct_ref_node(ASTNode* base, const char* field, bool is_ptr_op, SourceLoc loc);

ASTNode* new_post_inc_node(ASTNode* expr, SourceLoc loc);
ASTNode* new_post_dec_node(ASTNode* expr, SourceLoc loc);
ASTNode* new_pre_inc_node(ASTNode* expr, SourceLoc loc);
ASTNode* new_pre_dec_node(ASTNode* expr, SourceLoc loc);
ASTNode* new_compound_literal_node(ASTNode* type_name, ASTNode* init_list, SourceLoc loc);

ASTNode* new_arg_list(ASTNode* first_arg, SourceLoc loc);
ASTNode* append_arg_list(ASTNode* list, ASTNode* arg, SourceLoc loc);

ASTNode* new_unary_op_node(int op, ASTNode* operand, SourceLoc loc);
ASTNode* new_sizeof_node(ASTNode* target, bool is_type_name, SourceLoc loc);
ASTNode* new_cast_node(ASTNode* type_name, ASTNode* expr, SourceLoc loc);
ASTNode* new_binop_node  (int op, ASTNode* lhs, ASTNode* rhs, SourceLoc loc);    // op 可为字符或 BinaryOp
ASTNode* new_logical_and_node(ASTNode* lhs, ASTNode* rhs, SourceLoc loc);
ASTNode* new_logical_or_node(ASTNode* lhs, ASTNode* rhs, SourceLoc loc);
ASTNode* new_conditional_node(ASTNode* cond, ASTNode* then_expr, ASTNode* else_expr, SourceLoc loc);
ASTNode* new_assign_node (ASTNode* lhs, int op, ASTNode* rhs, SourceLoc loc);

ASTNode* new_expr_list(ASTNode* left, ASTNode* right, SourceLoc loc);

/*──────────────────────────────
 * 4.  声明 & 类型系统
 *─────────────────────────────*/
ASTNode* new_declaration(ASTNode* spec_list, ASTNode* init_list, SourceLoc loc);
ASTNode* new_spec_list(int spec, SourceLoc loc);                   // 建立首节点
ASTNode* append_spec_list(ASTNode* list, int spec, SourceLoc loc); // 追加

ASTNode* new_init_list(ASTNode* init_decl, SourceLoc loc);
ASTNode* append_init_list(ASTNode* list, ASTNode* init_decl, SourceLoc loc);
ASTNode* new_init_decl(ASTNode* declarator, ASTNode* initializer, SourceLoc loc);

ASTNode* new_struct_su_node(StructUnionKind su, const char* id, ASTNode* decl_list, SourceLoc loc);
ASTNode* new_sdecl_list(ASTNode* sdecl, SourceLoc loc);
ASTNode* append_sdecl_list(ASTNode* list, ASTNode* sdecl, SourceLoc loc);
ASTNode* new_struct_decl(ASTNode* specq_list, ASTNode* sdecl_list, SourceLoc loc);

ASTNode* new_specq_list(int spec_or_qual, SourceLoc loc);
ASTNode* append_specq_list(ASTNode* list, int spec_or_qual, SourceLoc loc);

ASTNode* new_sdeclarator_list(ASTNode* sdecltor, SourceLoc loc);
ASTNode* append_sdeclarator_list(ASTNode* list, ASTNode* sdecltor, SourceLoc loc);

ASTNode* new_bitfield_node(ASTNode* declarator /*nullable*/,
                           ASTNode* width_expr, SourceLoc loc);

ASTNode* new_enum_node(const char* id /*nullable*/, ASTNode* enumerator_list, SourceLoc loc);
ASTNode* new_enum_list(ASTNode* enumerator, SourceLoc loc);
ASTNode* append_enum_list(ASTNode* list, ASTNode* enumerator, SourceLoc loc);
ASTNode* new_enum_const(const char* id, ASTNode* value_expr /*nullable*/, SourceLoc loc);

ASTNode* new_tq_list(int tq, SourceLoc loc);
ASTNode* append_tq_list(ASTNode* list, int tq, SourceLoc loc);

ASTNode* new_declarator_node(ASTNode* pointer /*nullable*/, ASTNode* direct_decl, SourceLoc loc);
ASTNode* new_decl_ident(const char* id, SourceLoc loc);
ASTNode* new_array_decl(ASTNode* decl, ASTNode* tq_list /*nullable*/,
                        ASTNode* size_expr /*nullable*/,
                        bool is_static /*nullable*/,
                        bool is_star /*nullable*/, SourceLoc loc);
ASTNode* new_func_decl(ASTNode* decl, ASTNode* param_type_list /*nullable*/, SourceLoc loc);
ASTNode* new_oldstyle_func_decl(ASTNode* decl, ASTNode* id_list, SourceLoc loc);

ASTNode* new_pointer(ASTNode* tq_list /*nullable*/, SourceLoc loc);
ASTNode* prepend_pointer(ASTNode* tq_list /*nullable*/, ASTNode* existing, SourceLoc loc);

ASTNode* new_param_list(ASTNode* param_decl, SourceLoc loc);
ASTNode* append_param_list(ASTNode* list, ASTNode* param_decl, SourceLoc loc);
ASTNode* new_param_list_ellipsis(ASTNode* list, SourceLoc loc);
ASTNode* new_param_decl(ASTNode* decl_spec, ASTNode* declarator /*nullable*/, SourceLoc loc);

ASTNode* new_id_list(const char* id, SourceLoc loc);
ASTNode* append_id_list(ASTNode* list, const char* id, SourceLoc loc);

ASTNode* new_type_name(ASTNode* specq_list, ASTNode* abs_decl /*nullable*/, SourceLoc loc);

ASTNode* new_abs_decl(ASTNode* pointer /*nullable*/, ASTNode* direct_abs_decl /*nullable*/, SourceLoc loc);
ASTNode* new_abs_array(ASTNode* size_expr /*nullable*/, bool is_star /*nullable*/, SourceLoc loc);
ASTNode* new_abs_array_child(ASTNode* parent, ASTNode* size_expr /*nullable*/, bool is_star /*nullable*/, SourceLoc loc);
ASTNode* new_abs_func(ASTNode* param_type_list /*nullable*/, SourceLoc loc);
ASTNode* new_abs_func_child(ASTNode* parent, ASTNode* param_type_list /*nullable*/, SourceLoc loc);

/*──────────────────────────────
 * 5.  初始化 & 设计化初始化
 *─────────────────────────────*/
ASTNode* new_init_expr(ASTNode* expr, SourceLoc loc);
ASTNode* new_init_list_node(ASTNode* init_item_list, SourceLoc loc);
ASTNode* new_init_item_list(ASTNode* initializer, SourceLoc loc);
ASTNode* append_init_item(ASTNode* list, ASTNode* initializer, SourceLoc loc);

ASTNode* new_designated_init(ASTNode* designator_list, ASTNode* initializer, SourceLoc loc);
ASTNode* new_designator_list(ASTNode* designator, SourceLoc loc);
ASTNode* append_designator_list(ASTNode* list, ASTNode* designator, SourceLoc loc);
ASTNode* new_array_designator(ASTNode* const_expr, SourceLoc loc);
ASTNode* new_field_designator(const char* field, SourceLoc loc);

/*──────────────────────────────
 * 6.  语句
 *─────────────────────────────*/
ASTNode* new_labeled_stmt_id(const char* id, ASTNode* stmt, SourceLoc loc);
ASTNode* new_case_stmt(ASTNode* const_expr, ASTNode* stmt, SourceLoc loc);
ASTNode* new_default_stmt(ASTNode* stmt, SourceLoc loc);

ASTNode* new_compound_stmt(ASTNode* block_item_list /*nullable*/, SourceLoc loc);
ASTNode* new_block_item_list(ASTNode* item, SourceLoc loc);
ASTNode* append_block_item_list(ASTNode* list, ASTNode* item, SourceLoc loc);
ASTNode* new_block_decl(ASTNode* decl, SourceLoc loc);
ASTNode* new_block_stmt(ASTNode* stmt, SourceLoc loc);

ASTNode* new_expr_stmt(ASTNode* expr /*nullable*/, SourceLoc loc);

ASTNode* new_if_stmt(ASTNode* cond, ASTNode* then_stmt, ASTNode* else_stmt /*nullable*/, SourceLoc loc);
ASTNode* new_switch_stmt(ASTNode* expr, ASTNode* stmt, SourceLoc loc);

ASTNode* new_while_stmt(ASTNode* cond, ASTNode* body, SourceLoc loc);
ASTNode* new_do_while_stmt(ASTNode* body, ASTNode* cond, SourceLoc loc);
ASTNode* new_for_stmt(ASTNode* init, ASTNode* cond, ASTNode* iter /*nullable*/, ASTNode* body, SourceLoc loc);
ASTNode* new_for_decl_stmt(ASTNode* decl, ASTNode* cond_expr_stmt,
                           ASTNode* iter_expr /*nullable*/, ASTNode* body, SourceLoc loc);

ASTNode* new_goto_stmt(const char* id, SourceLoc loc);
ASTNode* new_continue_stmt(SourceLoc loc);
ASTNode* new_break_stmt(SourceLoc loc);
ASTNode* new_return_stmt  (ASTNode* expr /*nullable*/, SourceLoc loc);

/*──────────────────────────────
 * 7.  翻译单元 / 顶层
 *─────────────────────────────*/
ASTNode* new_translation_unit(ASTNode* prev, ASTNode* ext_decl, SourceLoc loc);
ASTNode* new_decl_stmt    (ASTNode* declaration, SourceLoc loc);
ASTNode* new_function_def (ASTNode* decl_spec, ASTNode* declarator,
                           ASTNode* decl_list /*nullable*/, ASTNode* compound_stmt,
                           SourceLoc loc);

ASTNode* new_declaration_list(ASTNode* decl, SourceLoc loc);
ASTNode* append_declaration_list(ASTNode* list, ASTNode* decl, SourceLoc loc);

// ★ 放在初始化区域旁边
ASTNode* append_designated_init(ASTNode* list,
                                ASTNode* designator_list,
                                ASTNode* initializer, SourceLoc loc);

// ★ 新增两种 overload，让既能接 enum 也能接节点
ASTNode* new_spec_list(ASTNode* spec_node, SourceLoc loc);
ASTNode* append_spec_list(ASTNode* list, ASTNode* spec_node, SourceLoc loc);


/* 让列表函数既接受 enum 也接受 ASTNode* -------------------*/
// ASTNode* (ASTNode* spec_node);
ASTNode* append_spec_list(ASTNode* list, ASTNode* spec_node, SourceLoc loc);

ASTNode* new_specq_list(ASTNode* node, SourceLoc loc);
ASTNode* append_specq_list(ASTNode* list, ASTNode* node, SourceLoc loc);

static std::string extractNameFromDeclarator(ASTNode* dtor) {
    std::string name = "";
    if (!dtor) return name;

    ASTNode* current = dtor;
    // 循环查找，直到找到带 text 的 DECLARATOR 或 ID
    while (current) {
        if (current->tag == ASTTag::DECLARATOR && !current->text.empty()) {
            name = current->text;
            break;
        }
        if (current->tag == ASTTag::ID) {
            name = current->text;
            break;
        }
        // 如果当前节点是 DECLARATOR 或 FUNC_DECL 且有子节点，则深入第一个子节点
        // （这部分逻辑需要根据 AST 结构仔细调整）
        if ((current->tag == ASTTag::DECLARATOR || current->tag == ASTTag::FUNC_DECL) && !current->kids.empty()) {
            // 特殊处理函数名情况：FUNC_DECL -> DECLARATOR "name"
            if (current->tag == ASTTag::FUNC_DECL && current->kids[0] && current->kids[0]->tag == ASTTag::DECLARATOR && !current->kids[0]->text.empty()) {
                name = current->kids[0]->text;
                break;
            }
            current = current->kids[0]; // 默认深入第一个孩子
        } else {
            break; // 无法继续深入
        }
    }
    return name;
}


#endif /* MINI_C_AST_H */
