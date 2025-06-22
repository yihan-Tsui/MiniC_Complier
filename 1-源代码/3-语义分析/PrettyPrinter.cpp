// PrettyPrinter.cpp
#include "PrettyPrinter.h"

void PrettyPrinter::print(ASTNode* root) {
    printNode(root);
    out.flush();
}

void PrettyPrinter::indent(){
    out << std::string(indentLevel * indentWidth, ' ');
}

void PrettyPrinter::newline(){
    out << "\n";
}

void PrettyPrinter::withIndent(const std::function<void()>& f){
    indentLevel++;
    f();
    indentLevel--;
}

bool PrettyPrinter::isStmt(ASTTag t){
    using T = ASTTag;
    return t==T::IF_STMT || t==T::FOR_STMT || t==T::FOR_DECL_STMT
           || t==T::WHILE_STMT|| t==T::RETURN_STMT
           || t==T::EXPR_STMT || t==T::COMPOUND_STMT
           || t==T::DECL_STMT;
}

void PrettyPrinter::printNode(ASTNode* n){
    if (!n) return;
    switch (n->tag) {
        case ASTTag::TRANSL_UNIT:        printTranslationUnit(n); break;
        case ASTTag::FUNCTION_DEF:       printFunctionDef(n);    break;
        case ASTTag::DECL_STMT:          printDeclStmt(n);       break;
        case ASTTag::DECLARATION:
            indent();
            printDeclaration(n);
            out << ";";
            newline();
            break;
        case ASTTag::IF_STMT:            printIfStmt(n);         break;
        case ASTTag::FOR_STMT:
        case ASTTag::FOR_DECL_STMT:      printForStmt(n);        break;
        case ASTTag::WHILE_STMT:         printWhileStmt(n);      break;
        case ASTTag::RETURN_STMT:        printReturnStmt(n);     break;
        case ASTTag::COMPOUND_STMT:      printCompoundStmt(n);   break;
        case ASTTag::EXPR_STMT:
                indent();
                // EXPR_STMT.kids[0] 可能是 nullptr（空语句）或者表达式
                if (!n->kids.empty() && n->kids[0]) {
                printExpr(n->kids[0]);
            }
            out << ";";
                newline();
                    break;

                        default:
                    if (isStmt(n->tag)) {
                    // 其它语句回退到 “表达式语句” 的处理
                            indent();
                    printExpr(n);
                    out << ";";
                    newline();
                } else {
                    printExpr(n);
                }

    }
}

// ── 顶层翻译单元 ──
void PrettyPrinter::printTranslationUnit(ASTNode* n){
    for (auto child : n->kids){
        printNode(child);
        newline();
    }
}

// ── 函数定义 ──
// kids: [spec_list, declarator, (opt decl_list), compound_stmt]
void PrettyPrinter::printFunctionDef(ASTNode* n){
    indent();
    printDeclSpec(n->kids[0]);
    out<<" ";
    printDeclarator(n->kids[1]);          // 包含函数名和参数
    out<<" ";
    printCompoundStmt(n->kids.back());
    newline();
}

// ── 声明语句、声明 ──
void PrettyPrinter::printDeclStmt(ASTNode* n){
    indent();
    printDeclaration(n->kids[0]);
    out<<";";
    newline();
}

void PrettyPrinter::printDeclaration(ASTNode* n) {
    // kids: [spec_list, init_decl_list]
    printDeclSpec(n->kids[0]);
     // 如果有初始化列表，就输出空格并专门打印它
        if (n->kids.size() > 1 && n->kids[1]) {
            out << " ";
            printInitDeclList(n->kids[1]);
        }
}

// ── If ──
void PrettyPrinter::printIfStmt(ASTNode* n){
    indent(); out<<"if ("; printExpr(n->kids[0]); out<<") ";
    if (n->kids[1]->tag==ASTTag::COMPOUND_STMT){
        printCompoundStmt(n->kids[1]);
    } else {
        newline();
        withIndent([&](){ printNode(n->kids[1]); });
    }
    if (n->kids.size()==3){
        indent(); out<<"else ";
        if (n->kids[2]->tag==ASTTag::COMPOUND_STMT)
            printCompoundStmt(n->kids[2]);
        else {
            newline();
            withIndent([&](){ printNode(n->kids[2]); });
        }
    }
}

// ── For ──
// kids: [init, cond, iter?, body]
void PrettyPrinter::printForStmt(ASTNode* n){
    indent(); out<<"for (";
    if (n->kids[0]) {
        if (n->kids[0]->tag == ASTTag::DECLARATION) {
            printDeclaration(n->kids[0]);
        } else {
            ASTNode* initNode = n->kids[0];
            if (initNode->tag == ASTTag::EXPR_STMT
                && !initNode->kids.empty()
                && initNode->kids[0])
                initNode = initNode->kids[0];
            printExpr(initNode);
        }
    }

    out<<"; ";
    // cond: 通常是 EXPR_STMT 包装
    if (n->kids[1]) {
        ASTNode* condNode = n->kids[1];
        if (condNode->tag == ASTTag::EXPR_STMT
            && !condNode->kids.empty()
            && condNode->kids[0])
            condNode = condNode->kids[0];
        printExpr(condNode);
    }

    out<<"; ";
//    ASTNode* iter = (n->kids.size()>2 ? n->kids[2] : nullptr);
//    if (iter) printExpr(iter);

    // iter: 有时也是 EXPR_STMT，有时直接是表达式
    if (n->kids.size() > 2 && n->kids[2]) {
        ASTNode* iterNode = n->kids[2];
        if (iterNode->tag == ASTTag::EXPR_STMT
            && !iterNode->kids.empty()
            && iterNode->kids[0])
            iterNode = iterNode->kids[0];
        printExpr(iterNode);
    }


    out<<") ";
    if (n->kids.back()->tag==ASTTag::COMPOUND_STMT)
        printCompoundStmt(n->kids.back());
    else {
        newline();
        withIndent([&](){ printNode(n->kids.back()); });
    }
}

// ── While ──
void PrettyPrinter::printWhileStmt(ASTNode* n){
    indent(); out<<"while ("; printExpr(n->kids[0]); out<<") ";
    if (n->kids[1]->tag==ASTTag::COMPOUND_STMT)
        printCompoundStmt(n->kids[1]);
    else {
        newline();
        withIndent([&](){ printNode(n->kids[1]); });
    }
}

// ── Return ──
void PrettyPrinter::printReturnStmt(ASTNode* n){
    indent(); out<<"return";
    if (!n->kids.empty()){
        out<<" ";
        printExpr(n->kids[0]);
    }
    out<<";"; newline();
}

// ── Compound ──
void PrettyPrinter::printCompoundStmt(ASTNode* n) {
    indent();
    out << "{";
    newline();

    withIndent([&]() {
        // 先检查是否真的是一个 BLOCK_ITEM_LIST
        if (!n->kids.empty()
            && n->kids[0]
            && n->kids[0]->tag == ASTTag::BLOCK_ITEM_LIST) {
            ASTNode* blockList = n->kids[0];
            for (ASTNode* item : blockList->kids) {
                if (!item) continue;
                switch (item->tag) {
                    case ASTTag::BLOCK_DECL:
                        // 声明包装：拆开并打印
                        indent();
                        printDeclaration(item->kids[0]);
                        out << ";";
                        newline();
                        break;
                    case ASTTag::BLOCK_STMT:
                        // 语句包装：取出里面的真正 stmt
                        if (!item->kids.empty() && item->kids[0]) {
                            printNode(item->kids[0]);
                        }
                        break;
                    default:
                        // 其它直接递归
                        printNode(item);
                }
            }
        } else {
            // 回退：如果 kids[0] 不是 BLOCK_ITEM_LIST，就打印所有子节点
            for (ASTNode* child : n->kids) {
                if (child) printNode(child);
            }
        }
    });

    indent();
    out << "}";
    newline();
}



// ── 声明符 & 类型相关 ──
// spec_list: kids 是一连串枚举值
void PrettyPrinter::printDeclSpec(ASTNode* n){
    if (!n) return;
    bool first = true;
    for (ASTNode* leaf : n->kids) {
        // 跳过 nullptr 或者不是 SPECIFIER 的节点
        if (!leaf || leaf->tag != ASTTag::SPECIFIER)
            continue;

        if (!first) out << " ";
        first = false;

        int spec = leaf->ival;
        switch (spec) {
            case TS_INT:    out << "int";    break;
            case TS_CHAR:   out << "char";   break;
            case TS_VOID:   out << "void";   break;
                // … 其他类型 …
            default:        out << "/*spec" << spec << "*/";
        }
    }
}


// declarator: 可能包含指针、标识符、参数列表
void PrettyPrinter::printDeclarator(ASTNode* n){
    // 简化处理：直接从 text 中读函数名或变量名
    if (!n->text.empty()){
        out<<n->text;
    } else if (!n->kids.empty()){
        // 对于 FUNC_DECL: kids[0] 是 DECLARATOR（带函数名），kids[1] 是 PARAM_LIST
        if (n->tag==ASTTag::FUNC_DECL){
            printDeclarator(n->kids[0]);
            out<<"(";
            if (n->kids.size()>1) printParamList(n->kids[1]);
            out<<")";
            return;
        } else {
            printDeclarator(n->kids[0]);
        }
    }
}

// 参数列表
void PrettyPrinter::printParamList(ASTNode* n){
    bool first=true;
    for (auto pd : n->kids){
        if (!first) out<<", ";
        first=false;
        // pd: PARAM_DECL 节点，kids[0] 是 spec_list，kids[1] 可选 declarator
        printDeclSpec(pd->kids[0]);
        if (pd->kids.size()>1){
            out<<" ";
            printDeclarator(pd->kids[1]);
        }
    }
}

// ── 表达式打印 ──
void PrettyPrinter::printExpr(ASTNode* n){
    using T = ASTTag;
    switch (n->tag){
        case T::ID:
            out<<n->text; break;
        case T::CONST:
            out<<n->text; break;
        case T::BINARY:
            printExpr(n->kids[0]);
            out<<" "<< static_cast<char>(n->ival) <<" ";
            printExpr(n->kids[1]);
            break;
        case T::UNARY:{
            int op = n->ival;
            const char* s = op=='-'? "-" : op=='+'? "+" : "";
            printUnary(n, s, true);
            break;
        }
        case T::ASSIGN:
            printExpr(n->kids[0]);
            out<<" = ";
            printExpr(n->kids[1]);
            break;
        case T::FUNC_CALL:
            printFuncCall(n);
            break;
        case T::ARRAY_REF:
            printArrayRef(n);
            break;
        case T::STRUCT_REF:
            printStructRef(n);
            break;

        case T::INIT_EXPR:
            // 把初始化表达式里的真实表达式解包再打印
            if (!n->kids.empty() && n->kids[0])
                printExpr(n->kids[0]);
                    break;
        default:
            out<<"/*unhandled:"<<(int)n->tag<<"*/";
    }
}

void PrettyPrinter::printUnary(ASTNode* n, const char* op, bool prefix){
    if (prefix) out<<op;
    printExpr(n->kids[0]);
    if (!prefix) out<<op;
}

void PrettyPrinter::printFuncCall(ASTNode* n){
    printExpr(n->kids[0]);
    out<<"(";
    if (n->kids.size()>1) printExpr(n->kids[1]);
    out<<")";
}

void PrettyPrinter::printArrayRef(ASTNode* n){
    printExpr(n->kids[0]);
    out<<"[";
    printExpr(n->kids[1]);
    out<<"]";
}

void PrettyPrinter::printStructRef(ASTNode* n){
    printExpr(n->kids[0]);
    out<<(n->flag? "->" : ".");
    out<<n->text;
}


void PrettyPrinter::printInitDeclList(ASTNode* n) {
    if (!n) return;
    bool first = true;
    for (ASTNode* initDecl : n->kids) {
        if (!initDecl) continue;
        if (!first) out << ", ";
        first = false;
        // declarator
        ASTNode* dtor = initDecl->kids[0];
        printDeclarator(dtor);
//        // initializer?
//        if (initDecl->kids.size() > 1 && initDecl->kids[1]) {
//            out << " = ";
//            printExpr(initDecl->kids[1]);
//        }

                // initializer?
                        if (initDecl->kids.size() > 1 && initDecl->kids[1]) {
                        out << " = ";
                        ASTNode* initNode = initDecl->kids[1];
                        // 如果是 INIT_EXPR，解包再打印
                                if (initNode->tag == ASTTag::INIT_EXPR
                                                                      && !initNode->kids.empty()
                                                                                          && initNode->kids[0])
                                initNode = initNode->kids[0];
                        printExpr(initNode);
                    }

    }
}