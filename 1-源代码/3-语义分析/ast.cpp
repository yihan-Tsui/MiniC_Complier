#include "ast.h"
#include <cstdlib>      // strtoll
#include <cstring>

/* ──────────────────────────
 * 内部小工具
 * ──────────────────────────*/
namespace {
    inline ASTNode* make(ASTTag tag) {
        return new ASTNode(tag);
    }

    // 若左节点已经是某 tag 的列表，则直接 push；否则新建列表结点
    ASTNode* append_to_list(ASTTag tag, ASTNode* list_or_node, ASTNode* item) {
        if (list_or_node && list_or_node->tag == tag) {
            list_or_node->kids.push_back(item);
            return list_or_node;
        }
        auto* n = make(tag);
        n->kids.reserve(4);
        n->kids.push_back(list_or_node);
        n->kids.push_back(item);
        return n;
    }
}

/* ──────────────────────────
 * 基本原子节点
 * ──────────────────────────*/
ASTNode* new_id_node(const char* name, SourceLoc loc)
{
    auto* n = make(ASTTag::ID);
    n->loc = loc;
    n->text = name;
    return n;
}

ASTNode* new_const_node(const char* literal, SourceLoc loc)
{
    auto* n = make(ASTTag::CONST);
    n->loc = loc;
    n->text = literal;
    char* endp = nullptr;
    n->ival = std::strtoll(literal, &endp, 0);
    return n;
}

ASTNode* new_string_node(const char* literal, SourceLoc loc)
{
    auto* n = make(ASTTag::STRING);
    n->loc = loc;
    n->text = literal;
    return n;
}

/* ──────────────────────────
 * 后缀、调用、成员访问
 * ──────────────────────────*/
ASTNode* new_array_ref_node(ASTNode* array, ASTNode* index, SourceLoc loc)
{
    auto* n = make(ASTTag::ARRAY_REF);
    n->kids = {array, index};
    n->loc = loc;
    return n;
}

ASTNode* new_func_call_node(ASTNode* callee, ASTNode* arg_list, SourceLoc loc)
{
    auto* n = make(ASTTag::FUNC_CALL);
    n->kids = {callee};
    n->loc = loc;
    if (arg_list) n->kids.push_back(arg_list);
    return n;
}

ASTNode* new_struct_ref_node(ASTNode* base, const char* field, bool is_ptr_op, SourceLoc loc)
{
    auto* n = make(ASTTag::STRUCT_REF);
    n->kids = {base};
    n->loc = loc;
    n->text = field;
    n->flag = is_ptr_op;
    return n;
}

/* ──────────────────────────
 * 自增 / 复合字面量
 * ──────────────────────────*/
ASTNode* new_post_inc_node(ASTNode* expr, SourceLoc loc) {
    auto* n = make(ASTTag::POST_INC);
    n->kids = {expr};
    n->loc = loc;
    return n;
}
ASTNode* new_post_dec_node(ASTNode* expr, SourceLoc loc) {
    auto* n = make(ASTTag::POST_DEC);
    n->kids = {expr};
    n->loc = loc;
    return n;
}
ASTNode* new_pre_inc_node (ASTNode* expr, SourceLoc loc) {
    auto* n = make(ASTTag::PRE_INC );
    n->kids = {expr};
    n->loc = loc;
    return n;
}
ASTNode* new_pre_dec_node (ASTNode* expr, SourceLoc loc) {
    auto* n = make(ASTTag::PRE_DEC );
    n->kids = {expr};
    n->loc = loc;
    return n;
}

ASTNode* new_compound_literal_node(ASTNode* type_name, ASTNode* init_list, SourceLoc loc)
{
    auto* n = make(ASTTag::COMPOUND_LITERAL);
    n->kids = {type_name, init_list};
    n->loc = loc;
    return n;
}

/* ──────────────────────────
 * 参数 / 实参与逗号表达式
 * ──────────────────────────*/
ASTNode* new_arg_list(ASTNode* first_arg, SourceLoc loc)
{
    auto* n = make(ASTTag::ARG_LIST);
    n->kids.push_back(first_arg);
    n->loc = loc;
    return n;
}

ASTNode* append_arg_list(ASTNode* list, ASTNode* arg, SourceLoc loc)
{
    ASTNode* n = append_to_list(ASTTag::ARG_LIST, list, arg);
    n->loc = loc;
    return n;
}

ASTNode* new_expr_list(ASTNode* left, ASTNode* right, SourceLoc loc)
{
    ASTNode* n = append_to_list(ASTTag::ARG_LIST, left, right);
    n->loc = loc;
    return n;
}

/* ──────────────────────────
 * 一元 / 二元 / 条件 / 逻辑 / 赋值
 * ──────────────────────────*/
ASTNode* new_unary_op_node(int op, ASTNode* operand, SourceLoc loc)
{
    auto* n = make(ASTTag::UNARY);
    n->loc = loc;
    n->ival = op;
    n->kids = {operand};
    return n;
}

ASTNode* new_sizeof_node(ASTNode* target, bool is_type_name, SourceLoc loc)
{
    auto* n = make(ASTTag::SIZEOF_EXPR);
    n->flag = is_type_name;
    n->loc = loc;
    n->kids = {target};
    return n;
}

ASTNode* new_cast_node(ASTNode* type_name, ASTNode* expr, SourceLoc loc)
{
    auto* n = make(ASTTag::CAST_EXPR);
    n->kids = {type_name, expr};
    n->loc = loc;
    return n;
}

ASTNode* new_binop_node(int op, ASTNode* lhs, ASTNode* rhs, SourceLoc loc)
{
    auto* n = make(ASTTag::BINARY);
    n->loc = loc;
    n->ival = op;
    n->kids = {lhs, rhs};
    return n;
}

ASTNode* new_logical_and_node(ASTNode* lhs, ASTNode* rhs, SourceLoc loc)
{
    auto* n = make(ASTTag::LOGIC_AND);
    n->kids = {lhs, rhs};
    n->loc = loc;
    return n;
}

ASTNode* new_logical_or_node(ASTNode* lhs, ASTNode* rhs, SourceLoc loc)
{
    auto* n = make(ASTTag::LOGIC_OR);
    n->kids = {lhs, rhs};
    n->loc = loc;
    return n;
}

ASTNode* new_conditional_node(ASTNode* cond, ASTNode* then_expr, ASTNode* else_expr, SourceLoc loc)
{
    auto* n = make(ASTTag::COND);
    n->kids = {cond, then_expr, else_expr};
    n->loc = loc;
    return n;
}

ASTNode* new_assign_node(ASTNode* lhs, int op, ASTNode* rhs, SourceLoc loc)
{
    auto* n = make(ASTTag::ASSIGN);
    n->loc = loc;
    n->ival = op;
    n->kids = {lhs, rhs};
    return n;
}

/* ──────────────────────────
 * 4.  声明 & 类型系统
 * ──────────────────────────*/
static ASTNode* new_leaf(ASTTag list_tag, int enum_val, SourceLoc loc)
{
    auto* leaf = make(ASTTag::SPECIFIER);
    leaf->ival = enum_val;
    leaf->loc = loc;
    return append_to_list(list_tag, nullptr, leaf);
}

/*—— 声明与说明符 ——*/
ASTNode* new_spec_list(int spec, SourceLoc loc) {
    return new_leaf(ASTTag::SPEC_LIST, spec, loc);
}
ASTNode* append_spec_list(ASTNode* list, int spec, SourceLoc loc) {
    return append_to_list(ASTTag::SPEC_LIST, list, new_leaf(ASTTag::SPEC_LIST, spec, loc)->kids[0]);
}

ASTNode* new_declaration(ASTNode* spec_list, ASTNode* init_list, SourceLoc loc)
{
    auto* n = make(ASTTag::DECLARATION);
    n->kids = {spec_list};
    n->loc = loc;
    if (init_list) n->kids.push_back(init_list);
    return n;
}

/*—— init‑declarator 列表 ——*/
ASTNode* new_init_decl(ASTNode* declarator, ASTNode* initializer, SourceLoc loc)
{
    auto* n = make(ASTTag::INIT_DECL);
    n->kids = {declarator};
    n->loc = loc;
    if (initializer) n->kids.push_back(initializer);
    return n;
}
ASTNode* new_init_list(ASTNode* init_decl, SourceLoc loc) {
    ASTNode* n = append_to_list(ASTTag::INIT_DECL_LIST,nullptr,init_decl);
    n->loc = loc;
    return n;
}
ASTNode* append_init_list(ASTNode* list, ASTNode* init_decl, SourceLoc loc) {
    ASTNode* n = append_to_list(ASTTag::INIT_DECL_LIST,list,init_decl);
    n->loc = loc;
    return n;
}

/*—— struct / union / enum ——*/
ASTNode* new_struct_su_node(StructUnionKind su, const char* id, ASTNode* decl_list, SourceLoc loc)
{
    auto* n = make(ASTTag::SU_SPEC);
    n->ival = su;
    n->loc = loc;
    if (id) n->text = id;
    if (decl_list) n->kids.push_back(decl_list);
    return n;
}

ASTNode* new_sdecl_list(ASTNode* sdecl, SourceLoc loc) {
    ASTNode* n = append_to_list(ASTTag::STRUCT_DECL_LIST,nullptr,sdecl);
    n->loc = loc;
    return n;
}
ASTNode* append_sdecl_list(ASTNode* list, ASTNode* sdecl, SourceLoc loc) {
    ASTNode* n = append_to_list(ASTTag::STRUCT_DECL_LIST, list, sdecl);
    n->loc = loc;
    return n;
}

ASTNode* new_struct_decl(ASTNode* specq_list, ASTNode* sdecl_list, SourceLoc loc)
{
    auto* n = make(ASTTag::STRUCT_DECL);
    n->kids = {specq_list, sdecl_list};
    n->loc = loc;
    return n;
}

ASTNode* new_specq_list(int sq, SourceLoc loc) {
    return new_leaf(ASTTag::SPECQ_LIST, sq, loc);
}
ASTNode* append_specq_list(ASTNode* list, int sq, SourceLoc loc) {
    return append_to_list(ASTTag::SPECQ_LIST, list, new_leaf(ASTTag::SPECQ_LIST, sq, loc)->kids[0]);
}

ASTNode* new_sdeclarator_list(ASTNode* sdec, SourceLoc loc) {
    ASTNode* n = append_to_list(ASTTag::STRUCT_DECLARATOR_LIST,nullptr,sdec);
    n->loc = loc;
    return n;
}
ASTNode* append_sdeclarator_list(ASTNode* list, ASTNode* sdec, SourceLoc loc) {
    ASTNode* n = append_to_list(ASTTag::STRUCT_DECLARATOR_LIST, list, sdec);
    n->loc = loc;
    return n;
}

ASTNode* new_bitfield_node(ASTNode* declarator, ASTNode* width, SourceLoc loc)
{
    auto* n = make(ASTTag::BITFIELD);
    if (declarator) n->kids.push_back(declarator);
    n->kids.push_back(width);
    n->loc = loc;
    return n;
}

ASTNode* new_enum_node(const char* id, ASTNode* enumerator_list, SourceLoc loc)
{
    auto* n = make(ASTTag::ENUM_SPEC);
    n->loc = loc;
    if (id) n->text = id;
    if (enumerator_list) n->kids.push_back(enumerator_list);
    return n;
}

ASTNode* new_enum_const(const char* id, ASTNode* val, SourceLoc loc)
{
    auto* n = make(ASTTag::ENUM_CONST);
    n->text = id;
    n->loc = loc;
    if (val) n->kids.push_back(val);
    return n;
}
ASTNode* new_enum_list(ASTNode* e, SourceLoc loc) {
    ASTNode* n = append_to_list(ASTTag::ENUM_LIST,nullptr,e);
    n->loc = loc;
    return n;
}
ASTNode* append_enum_list(ASTNode* list, ASTNode* e, SourceLoc loc) {
    ASTNode* n = append_to_list(ASTTag::ENUM_LIST, list,e);
    n->loc = loc;
    return n;
}

/*—— 类型限定符列表 ——*/
ASTNode* new_tq_list(int tq, SourceLoc loc) {
    return new_leaf(ASTTag::TQ_LIST,tq, loc);
}
ASTNode* append_tq_list(ASTNode* list, int tq, SourceLoc loc) {
    return append_to_list(ASTTag::TQ_LIST,list,new_leaf(ASTTag::TQ_LIST,tq, loc)->kids[0]);
}

/*—— declarator / pointer / array / func ——*/
ASTNode* new_declarator_node(ASTNode* pointer, ASTNode* direct_decl, SourceLoc loc)
{
    auto* n = make(ASTTag::DECLARATOR);
    if (pointer) n->kids.push_back(pointer);
    n->kids.push_back(direct_decl);
    n->loc = loc;
    return n;
}

ASTNode* new_decl_ident(const char* id, SourceLoc loc)
{
    auto* n = make(ASTTag::DECLARATOR);
    n->text = id;
    n->loc = loc;
    return n;
}

ASTNode* new_array_decl(ASTNode* decl, ASTNode* tq_list,
                        ASTNode* size_expr, bool is_static, bool is_star, SourceLoc loc)
{
    auto* n = make(ASTTag::ARRAY_DECL);
    n->kids = {decl};
    n->loc = loc;
    if (tq_list)     n->kids.push_back(tq_list);
    if (size_expr)   n->kids.push_back(size_expr);
    n->flag = is_static || is_star;   // 粗略放一起，用位标记也行
    return n;
}

ASTNode* new_func_decl(ASTNode* decl, ASTNode* param_type_list, SourceLoc loc)
{
    auto* n = make(ASTTag::FUNC_DECL);
    n->kids = {decl};
    n->loc = loc;
    if (param_type_list) n->kids.push_back(param_type_list);
    return n;
}
ASTNode* new_oldstyle_func_decl(ASTNode* decl, ASTNode* id_list, SourceLoc loc)
{
    auto* n = make(ASTTag::OLD_FUNC_DECL);
    n->kids = {decl, id_list};
    n->loc = loc;
    return n;
}

ASTNode* new_pointer(ASTNode* tq_list, SourceLoc loc)
{
    auto* n = make(ASTTag::POINTER);
    n->loc = loc;
    if (tq_list) n->kids.push_back(tq_list);
    return n;
}

ASTNode* prepend_pointer(ASTNode* tq_list, ASTNode* existing, SourceLoc loc)
{
    auto* n = make(ASTTag::POINTER);
    n->loc = loc;
    if (tq_list) n->kids.push_back(tq_list);
    n->kids.push_back(existing);
    return n;
}

/*—— 参数列表 & 声明 ——*/
ASTNode* new_param_decl(ASTNode* decl_spec, ASTNode* declarator, SourceLoc loc)
{
    auto* n = make(ASTTag::PARAM_DECL);
    n->kids = {decl_spec};
    n->loc = loc;
    if (declarator) n->kids.push_back(declarator);
    return n;
}
ASTNode* new_param_list(ASTNode* p, SourceLoc loc) {
    ASTNode* n = append_to_list(ASTTag::PARAM_LIST,nullptr,p);
    n->loc = loc;
    return n;
}
ASTNode* append_param_list(ASTNode* list, ASTNode* p ,SourceLoc loc) {
    ASTNode* n = append_to_list(ASTTag::PARAM_LIST,list,p);
    n->loc = loc;
    return n;
}
ASTNode* new_param_list_ellipsis(ASTNode* list, SourceLoc loc)
{
    auto* ellip = make(ASTTag::PARAM_LIST_ELIPS);
    ellip->loc = loc;
    return append_to_list(ASTTag::PARAM_LIST, list, ellip);
}

/*—— 标识符列表 ——*/
ASTNode* new_id_list(const char* id, SourceLoc loc) {
    return append_to_list(ASTTag::ID_LIST,nullptr,new_id_node(id, loc));
}
ASTNode* append_id_list(ASTNode* list, const char* id, SourceLoc loc) {
    return append_to_list(ASTTag::ID_LIST,list,new_id_node(id, loc));
}

/*—— type‑name / 抽象声明符 ——*/
ASTNode* new_type_name(ASTNode* specq_list, ASTNode* abs_decl, SourceLoc loc)
{
    auto* n = make(ASTTag::TYPE_NAME_NODE);
    n->kids = {specq_list};
    n->loc = loc;
    if (abs_decl) n->kids.push_back(abs_decl);
    return n;
}

ASTNode* new_abs_decl(ASTNode* pointer, ASTNode* direct_abs_decl, SourceLoc loc)
{
    auto* n = make(ASTTag::ABS_DECL);
    n->loc = loc;
    if (pointer) n->kids.push_back(pointer);
    if (direct_abs_decl) n->kids.push_back(direct_abs_decl);
    return n;
}

ASTNode* new_abs_array(ASTNode* size, bool is_star, SourceLoc loc)
{
    auto* n = make(ASTTag::ABS_ARRAY);
    n->loc = loc;
    if (size) n->kids.push_back(size);
    n->flag = is_star;
    return n;
}
ASTNode* new_abs_array_child(ASTNode* parent, ASTNode* size, bool is_star, SourceLoc loc)
{
    ASTNode* n = append_to_list(ASTTag::ABS_ARRAY_CHILD, parent, new_abs_array(size,is_star, loc));
    n->loc = loc;
    return n;
}
ASTNode* new_abs_func(ASTNode* param_list, SourceLoc loc)
{
    auto* n = make(ASTTag::ABS_FUNC);
    n->loc = loc;
    if (param_list) n->kids.push_back(param_list);
    return n;
}
ASTNode* new_abs_func_child(ASTNode* parent, ASTNode* param_list, SourceLoc loc)
{
    ASTNode* n = append_to_list(ASTTag::ABS_FUNC_CHILD, parent, new_abs_func(param_list, loc));
    n->loc = loc;
    return n;
}

/* ──────────────────────────
 * 5.  初始化 & 设计化初始化
 * ──────────────────────────*/
ASTNode* new_init_expr(ASTNode* expr, SourceLoc loc) {
    auto* n = make(ASTTag::INIT_EXPR);
    n->kids = {expr};
    n->loc = loc;
    return n;
}
ASTNode* new_init_item_list(ASTNode* init, SourceLoc loc) {
    ASTNode* n = append_to_list(ASTTag::INIT_ITEM_LIST,nullptr,init);
    n->loc = loc;
    return n;
}
ASTNode* append_init_item(ASTNode* list, ASTNode* init, SourceLoc loc) {
    ASTNode* n = append_to_list(ASTTag::INIT_ITEM_LIST,list,init);
    n->loc = loc;
    return n;
}

ASTNode* new_init_list_node(ASTNode* item_list, SourceLoc loc)
{
    auto* n = make(ASTTag::INIT_LIST_NODE);
    n->kids = {item_list};
    n->loc = loc;
    return n;
}

/*── 指定化初始化器 ──*/
ASTNode* new_designator_list(ASTNode* d, SourceLoc loc) {
    ASTNode* n = append_to_list(ASTTag::DESIGNATOR_LIST,nullptr,d);
    n->loc = loc;
    return n;
}
ASTNode* append_designator_list(ASTNode* list, ASTNode* d, SourceLoc loc) {
    ASTNode* n = append_to_list(ASTTag::DESIGNATOR_LIST,list,d);
    n->loc = loc;
    return n;
}

ASTNode* new_array_designator(ASTNode* const_expr, SourceLoc loc)
{
    auto* n = make(ASTTag::ARRAY_DESIGNATOR);
    n->kids = {const_expr};
    n->loc = loc;
    return n;
}

ASTNode* new_field_designator(const char* field, SourceLoc loc)
{
    auto* n = make(ASTTag::FIELD_DESIGNATOR);
    n->text = field;
    n->loc = loc;
    return n;
}

ASTNode* new_designated_init(ASTNode* designator_list, ASTNode* initializer, SourceLoc loc)
{
    auto* n = make(ASTTag::DESIGNATED_INIT);
    n->kids = {designator_list, initializer};
    n->loc = loc;
    return n;
}

/* ──────────────────────────
 * 6.  语句
 * ──────────────────────────*/
ASTNode* new_labeled_stmt_id(const char* id, ASTNode* stmt, SourceLoc loc) {
    auto* n = make(ASTTag::LABELED_ID_STMT);
    n->text=id;
    n->loc = loc;
    n->kids={stmt};
    return n;
}
ASTNode* new_case_stmt(ASTNode* expr, ASTNode* stmt, SourceLoc loc) {
    auto* n = make(ASTTag::CASE_STMT);
    n->kids={expr,stmt};
    n->loc = loc;
    return n;
}
ASTNode* new_default_stmt(ASTNode* stmt, SourceLoc loc) {
    auto* n = make(ASTTag::DEFAULT_STMT);
    n->kids={stmt};
    n->loc = loc;
    return n;
}

ASTNode* new_compound_stmt(ASTNode* block_item_list, SourceLoc loc)
{
    auto* n = make(ASTTag::COMPOUND_STMT);
    n->loc = loc;
    if (block_item_list) n->kids.push_back(block_item_list);
    return n;
}
ASTNode* new_block_item_list(ASTNode* item, SourceLoc loc) {
    ASTNode* n = append_to_list(ASTTag::BLOCK_ITEM_LIST,nullptr,item);
    n->loc = loc;
    return n;
}
ASTNode* append_block_item_list(ASTNode* list, ASTNode* item, SourceLoc loc) {
    ASTNode* n = append_to_list(ASTTag::BLOCK_ITEM_LIST,list,item);
    n->loc = loc;
    return n;
}
ASTNode* new_block_decl(ASTNode* decl, SourceLoc loc) {
    auto* n = make(ASTTag::BLOCK_DECL);
    n->kids={decl};
    n->loc = loc;
    return n;
}
ASTNode* new_block_stmt(ASTNode* stmt, SourceLoc loc) {
    auto* n = make(ASTTag::BLOCK_STMT);
    n->kids={stmt};
    n->loc = loc;
    return n;
}

ASTNode* new_expr_stmt(ASTNode* expr, SourceLoc loc) {
    if(!expr) return make(ASTTag::EXPR_STMT);
    auto* n=make(ASTTag::EXPR_STMT);
    n->kids={expr};
    n->loc = loc;
    return n;
}

ASTNode* new_if_stmt(ASTNode* cond, ASTNode* then_s, ASTNode* else_s, SourceLoc loc)
{
    auto* n = make(ASTTag::IF_STMT);
    n->loc = loc;
    n->kids = {cond, then_s};
    if (else_s) n->kids.push_back(else_s);
    return n;
}

ASTNode* new_switch_stmt(ASTNode* expr, ASTNode* body, SourceLoc loc) {
    auto* n = make(ASTTag::SWITCH_STMT);
    n->kids={expr,body};
    n->loc = loc;
    return n;
}
ASTNode* new_while_stmt(ASTNode* cond, ASTNode* body, SourceLoc loc) {
    auto* n = make(ASTTag::WHILE_STMT);
    n->kids={cond,body};
    n->loc = loc;
    return n;
}
ASTNode* new_do_while_stmt(ASTNode* body, ASTNode* cond, SourceLoc loc) {
    auto* n = make(ASTTag::DO_WHILE_STMT);
    n->kids={body,cond};
    n->loc = loc;
    return n;
}

ASTNode* new_for_stmt(ASTNode* init, ASTNode* cond, ASTNode* iter, ASTNode* body, SourceLoc loc)
{
    auto* n = make(ASTTag::FOR_STMT);
    n->kids = {init, cond};
    n->loc = loc;
    if (iter) n->kids.push_back(iter);
    n->kids.push_back(body);
    return n;
}

ASTNode* new_for_decl_stmt(ASTNode* decl, ASTNode* cond, ASTNode* iter, ASTNode* body, SourceLoc loc)
{
    auto* n = make(ASTTag::FOR_DECL_STMT);
    n->kids = {decl, cond};
    n->loc = loc;
    if (iter) n->kids.push_back(iter);
    n->kids.push_back(body);
    return n;
}

ASTNode* new_goto_stmt(const char* id, SourceLoc loc) {
    auto* n = make(ASTTag::GOTO_STMT);
    n->text=id;
    n->loc = loc;
    return n;
}
ASTNode* new_continue_stmt(SourceLoc loc) {
    auto* n = make(ASTTag::CONTINUE_STMT);
    n->loc = loc;
    return n;
}
ASTNode* new_break_stmt(SourceLoc loc) {
    auto* n = make(ASTTag::BREAK_STMT);
    n->loc = loc;
    return n;
}
ASTNode* new_return_stmt(ASTNode* expr, SourceLoc loc) {
    auto* n = make(ASTTag::RETURN_STMT);
    n->loc = loc;
    if(expr)n->kids={expr};
    return n;
}

/* ──────────────────────────
 * 7.  翻译单元 / 顶层
 * ──────────────────────────*/
ASTNode* new_translation_unit(ASTNode* prev, ASTNode* ext_decl, SourceLoc loc)
{
    if (!prev) {
        auto* n=make(ASTTag::TRANSL_UNIT);
        n->kids={ext_decl};
        n->loc = loc;
        return n;
    }
    prev->kids.push_back(ext_decl);
    return prev;
}

ASTNode* new_decl_stmt(ASTNode* declaration, SourceLoc loc)
{
    auto* n = make(ASTTag::DECL_STMT);
    n->loc=loc;
    n->kids={declaration};
    return n;
}

ASTNode* new_function_def(ASTNode* decl_spec, ASTNode* declarator,
                          ASTNode* decl_list, ASTNode* comp_stmt, SourceLoc loc)
{
    auto* n = make(ASTTag::FUNCTION_DEF);
    n->loc=loc;
    n->kids = {decl_spec, declarator};
    if (decl_list) n->kids.push_back(decl_list);
    n->kids.push_back(comp_stmt);
    return n;
}

ASTNode* new_declaration_list(ASTNode* decl, SourceLoc loc) {
    ASTNode* n = append_to_list(ASTTag::DECL_LIST,nullptr,decl);
    n->loc=loc;
    return n;
}
ASTNode* append_declaration_list(ASTNode* list, ASTNode* decl, SourceLoc loc) {
    ASTNode* n = append_to_list(ASTTag::DECL_LIST,list,decl);
    n->loc=loc;
    return n;
}

/*─────────  overload: enum ↔ node  ─────────*/

ASTNode* new_spec_list(ASTNode* spec_node, SourceLoc loc)
{
    ASTNode* n = append_to_list(ASTTag::SPEC_LIST, nullptr, spec_node);
    n->loc=loc;
    return n;
}
ASTNode* append_spec_list(ASTNode* list, ASTNode* spec_node, SourceLoc loc)
{
    ASTNode* n = append_to_list(ASTTag::SPEC_LIST, list, spec_node);
    n->loc=loc;
    return n;
}

/* 设计化初始化: 追加 (designator = initializer) */
ASTNode* append_designated_init(ASTNode* list,
                                ASTNode* designator_list,
                                ASTNode* initializer, SourceLoc loc)
{
    auto* di = new_designated_init(designator_list, initializer, loc);
    return append_init_item(list, di, loc);
}

/* 若你用到了 specq_list，同理加 overload： */
ASTNode* new_specq_list(ASTNode* node, SourceLoc loc)
{
    auto* n = append_to_list(ASTTag::SPECQ_LIST, nullptr, node);
    n->loc=loc;
    return n;
}
ASTNode* append_specq_list(ASTNode* list, ASTNode* node, SourceLoc loc)
{
    ASTNode* n = append_to_list(ASTTag::SPECQ_LIST, list, node);
    n->loc=loc;
    return n;

}


/* ── spec_list overload (node) ───────────────────────────*/
// ASTNode* new_spec_list(ASTNode* spec_node) {
//     return append_to_list(ASTTag::SPEC_LIST, nullptr, spec_node);
// }
// ASTNode* append_spec_list(ASTNode* list, ASTNode* spec_node) {
//     return append_to_list(ASTTag::SPEC_LIST, list, spec_node);
// }
//
// /* ── specq_list overload (node) ─────────────────────────*/
// ASTNode* new_specq_list(ASTNode* node) {
//     return append_to_list(ASTTag::SPECQ_LIST, nullptr, node);
// }
// ASTNode* append_specq_list(ASTNode* list, ASTNode* node) {
//     return append_to_list(ASTTag::SPECQ_LIST, list, node);
// }
//
// /* ── 追加指定化初始化器 ───────────────────────────────*/
// ASTNode* append_designated_init(ASTNode* list,
//                                 ASTNode* designator_list,
//                                 ASTNode* initializer)
// {
//     return append_init_item(list,
//             new_designated_init(designator_list, initializer));
// }


