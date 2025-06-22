// ir.cpp
#include "ir.h"
#include "ast.h"
#include <cassert>
#include <iostream>

#include "symbol.h"





void dumpAST(ASTNode* n, int indent = 0) {
    if (!n) return;
    std::string pad(indent, ' ');
    // std::cout << pad << "Tag = " << static_cast<int>(n->tag) << ", text = " << n->text << ", loc = (" << n->loc.line << "," << n->loc.col << ")\n";
    for (auto* c : n->kids) dumpAST(c, indent + 2);
}


// 生成入口
std::vector<Quad> IRGenerator::generate(ASTNode* root) {
    if (!currentScope_) {
        std::cerr << "FATAL ERROR in IRGenerator::generate: currentScope_ is null at entry!" << std::endl;
        return {}; // 返回空列表
    }
    dumpAST(root);
    quads_.clear();
    breakLabels_.clear();
    continueLabels_.clear();
    lastLoc_ = {0,0};
    genStmt(root);
    for (const auto& q : quads_) {
        // std::cout << "[IR] " << q.op << " " << q.arg1 << " " << q.arg2 << " -> " << q.result << "\n";
    }
    return quads_;
}

void IRGenerator::recordLoc(SourceLoc loc) {
    lastLoc_ = loc;
}

// 表达式生成，返回“这个表达式结果”的变量名（临时或直接变量）
std::string IRGenerator::genExpr(ASTNode* n) {
    if (!n) return "";

    // 每次真正用到 n->loc 的时候先记录：
    recordLoc(n->loc);

    switch (n->tag) {
        case ASTTag::CONST: {
            std::string t = newTemp();
            TypePtr ty = std::make_shared<BasicType>(TS_INT);
            emit("=", n->text, "", t, lastLoc_, /*var=*/"", ty);
            tempTypes_[t] = ty;
            return t;
        }
        case ASTTag::ID: {
            auto *sym = symbolTable_->lookup(n->text);
            if (sym) tempTypes_[n->text] = sym->type;
            return n->text;
        }

        case ASTTag::UNARY: {
            std::string src = genExpr(n->kids[0]);
            std::string t   = newTemp();
            std::string op;
            switch (static_cast<UnaryOp>(n->ival)) {
                case op_address:    op = "addr";   break;
                case op_deref:      op = "deref";  break;
                case op_unary_plus: op = "+";      break;
                case op_neg:        op = "-";      break;
                case op_bitnot:     op = "~";      break;
                case op_not:        op = "!";      break;
            }
            TypePtr ty = tempTypes_[src];
            emit(op, src, "", t, lastLoc_, "", ty);
            tempTypes_[t] = ty;
            return t;
        }

        case ASTTag::BINARY: {
            std::string lhs = genExpr(n->kids[0]);
            std::string rhs = genExpr(n->kids[1]);
            std::string t   = newTemp();
            int opv = n->ival;
            std::string op;

            if (opv < 256) {
                op = std::string(1, static_cast<char>(opv));
            } else {
                switch (static_cast<BinaryOp>(opv)) {
                    case SHL: op = "<<"; break;
                    case SHR: op = ">>"; break;
                    case LE:  op = "<="; break;
                    case GE:  op = ">="; break;
                    case EQ:  op = "=="; break;
                    case NE:  op = "!="; break;
                    default:  op = "?";  break;
                }
            }

            TypePtr ty = tempTypes_[lhs];
            emit(op, lhs, rhs, t, lastLoc_, "", ty);
            tempTypes_[t] = ty;
            return t;
        }

        case ASTTag::LOGIC_AND: {
            std::string L_false = newLabel();
            std::string L_end   = newLabel();
            std::string t       = newTemp();
            TypePtr ty = std::make_shared<BasicType>(TS_INT);

            emit("=", "1", "", t, lastLoc_, "", ty);

            std::string a = genExpr(n->kids[0]);
            emit("ifFalse", a, "", L_false, lastLoc_);

            std::string b = genExpr(n->kids[1]);
            emit("ifFalse", b, "", L_false, lastLoc_);

            emit("goto", "", "", L_end, lastLoc_);
            emit("label", "", "", L_false, lastLoc_);

            emit("=", "0", "", t, lastLoc_, "", ty);
            emit("label", "", "", L_end, lastLoc_);

            tempTypes_[t] = ty;
            return t;
        }

        case ASTTag::LOGIC_OR: {
            std::string L_true  = newLabel();
            std::string L_end   = newLabel();
            std::string t       = newTemp();
            TypePtr ty = std::make_shared<BasicType>(TS_INT);

            emit("=", "0", "", t, lastLoc_, "", ty);

            std::string a = genExpr(n->kids[0]);
            emit("ifTrue", a, "", L_true, lastLoc_);

            std::string b = genExpr(n->kids[1]);
            emit("ifTrue", b, "", L_true, lastLoc_);

            emit("goto", "", "", L_end, lastLoc_);
            emit("label", "", "", L_true, lastLoc_);

            emit("=", "1", "", t, lastLoc_, "", ty);
            emit("label", "", "", L_end, lastLoc_);

            tempTypes_[t] = ty;
            return t;
        }

        case ASTTag::COND: {
            std::string L_false = newLabel();
            std::string L_end   = newLabel();
            std::string t       = newTemp();

            std::string c = genExpr(n->kids[0]);
            emit("ifFalse", c, "", L_false, lastLoc_);

            std::string r1 = genExpr(n->kids[1]);
            emit("=", r1, "", t, lastLoc_, "", tempTypes_[r1]);

            emit("goto", "", "", L_end, lastLoc_);
            emit("label", "", "", L_false, lastLoc_);

            std::string r2 = genExpr(n->kids[2]);
            emit("=", r2, "", t, lastLoc_, "", tempTypes_[r2]);

            emit("label", "", "", L_end, lastLoc_);

            tempTypes_[t] = tempTypes_[r1];  // 或某种 merge 类型推导
            return t;
        }

        case ASTTag::ASSIGN: {
            std::string rhs = genExpr(n->kids[1]);
            std::string lhs = genExpr(n->kids[0]);
            auto *sym = symbolTable_->lookup(lhs);
            TypePtr vtype = sym ? sym->type : tempTypes_[rhs];
            emit("=", rhs, "", lhs, lastLoc_, lhs, vtype);
            return lhs;
        }

        case ASTTag::ARRAY_REF: {
            std::string base = genExpr(n->kids[0]);
            std::string idx  = genExpr(n->kids[1]);
            std::string t    = newTemp();
            emit("[]", base, idx, t, lastLoc_, "", tempTypes_[base]);
            tempTypes_[t] = tempTypes_[base];
            return t;
        }

        case ASTTag::STRUCT_REF: {
            std::string base = genExpr(n->kids[0]);
            std::string fld  = n->text;
            std::string t    = newTemp();
            emit(n->flag ? "->" : ".", base, fld, t, lastLoc_, "", tempTypes_[base]);
            tempTypes_[t] = tempTypes_[base];
            return t;
        }

        case ASTTag::FUNC_CALL: {
            if (n->kids.size() == 2) {
                for (auto* a : n->kids[1]->kids) {
                    std::string tmp = genExpr(a);
                    emit("param", tmp, "", "", lastLoc_, "", tempTypes_[tmp]);
                }
            }
            std::string ret = newTemp();
            int argc = (n->kids.size() == 2 ? n->kids[1]->kids.size() : 0);
            emit("call", n->kids[0]->text, std::to_string(argc), ret, lastLoc_, "", nullptr);
            return ret;
        }

        case ASTTag::STRING: {
            std::string t = newTemp();
            TypePtr ty = std::make_shared<PointerType>(std::make_shared<BasicType>(TS_CHAR));
            emit("=", n->text, "", t, lastLoc_, "", ty);
            tempTypes_[t] = ty;
            return t;
        }

        case ASTTag::EXPR_LIST: {
            genExpr(n->kids[0]);
            return genExpr(n->kids[1]);
        }

        case ASTTag::INIT_EXPR: {
            if (!n->kids.empty()) {
                return genExpr(n->kids[0]);  // unwrap INIT_EXPR 包装，递归实际表达式
            }
            return "";
        }


        default:
            for (auto* c : n->kids) genExpr(c);
            return "";
    }
}


// 语句生成
void IRGenerator::genStmt(ASTNode* n) {
    if (!n) return;
    recordLoc(n->loc);
    // 保存进入此函数时的作用域，以便在退出时恢复
    auto originalScope = currentScope_;
    bool scopePushed = false; // 标记此调用是否改变了作用域
    switch (n->tag) {
        case ASTTag::INIT_DECL: {
            ASTNode* dtor = n->kids[0];
            std::string varName = extractNameFromDeclarator(dtor); // 使用辅助函数
            SourceLoc varLoc = dtor ? dtor->loc : n->loc; // 获取位置信息

            if (varName.empty()) {
                std::cerr << "IR Gen Error: Could not extract variable name in INIT_DECL at line " << n->loc.line << std::endl;
                break;
            }

            if (n->kids.size() == 2 && n->kids[1]) { // Has initializer
                std::string rhs = genExpr(n->kids[1]);
                Symbol* sym = nullptr;
                std::cerr << "[DEBUG IRGen] Looking up '" << varName << "' in scope: " << currentScope_.get() << std::endl;
                if (currentScope_) { // 查找当前作用域
                    sym = currentScope_->lookup(varName);

                }
                TypePtr vtype = sym ? sym->type : nullptr;

                if (sym) {
                    // 找到了符号，现在检查它的类型指针
                    vtype = sym->type; // 从找到的符号获取类型指针
                    std::cerr << "[DEBUG IRGen]   Symbol '" << varName << "' FOUND in scope " << currentScope_.get() << ".";
                    if (vtype) {
                        // 类型指针有效！
                        std::cerr << " Type pointer is VALID: " << vtype.get() << " (" << vtype->toString() << ")" << std::endl;
                    } else {
                        // 类型指针是 NULL！这就是问题所在
                        std::cerr << " Type pointer is NULL!" << std::endl;
                    }
                } else {
                    // 符号本身就没找到
                    std::cerr << "[DEBUG IRGen]   Symbol '" << varName << "' NOT FOUND in scope " << currentScope_.get() << "." << std::endl;
                }

                if (!vtype) {
                    // 替换 error 调用
                    std::cerr << "IR Gen Warning: Could not find symbol type for '" << varName << "' during INIT_DECL at line " << varLoc.line << ". Type info might be missing." << std::endl;
                    // 尝试从 rhs 推断（如果 rhs 是临时变量且类型已知）
                    if(tempTypes_.count(rhs)) vtype = tempTypes_[rhs];
                    // 否则 vtype 保持 nullptr
                }
                // 使用变量声明的位置
                emit("=", rhs, "", varName, varLoc, varName, vtype);
            }
            // No IR needed for declaration without initializer in this phase
            break;
        }

        case ASTTag::EXPR_STMT:
            if (!n->kids.empty()) genExpr(n->kids[0]);
            break;

        case ASTTag::COMPOUND_STMT: {
            // *** 进入块作用域 ***
            if (!originalScope) { // 检查原始作用域是否有效
                std::cerr << "IR Gen Error: Attempting to push scope from a null originalScope at line " << n->loc.line << std::endl;
                // 在这里应该中断处理，例如 break 或 return
                break;
            }
            currentScope_ = originalScope->push();

            if (!currentScope_) { // 检查 push 操作的结果
                std::cerr << "IR Gen Error: Pushing scope resulted in nullptr at line " << n->loc.line << std::endl;
                // push 失败通常是因为原始 Scope 对象不是由 shared_ptr 管理的，
                // 但我们的 Scope 继承自 enable_shared_from_this，理论上不应失败除非 originalScope 本身有问题。
                // 或者 originalScope->push() 内部实现有错误。
                // 中断处理
                scopePushed = false; // 标记作用域并未成功改变
                break;
            }
            scopePushed = true;
            // 处理块内各项
            for (auto* item : n->kids) { // 假设 kids[0] 是 BLOCK_ITEM_LIST
                genStmt(item);
            }
            // 离开作用域的操作将在函数末尾统一处理
            break;
        }
        case ASTTag::BLOCK_ITEM_LIST:
            for (auto* c : n->kids) genStmt(c);
            break;

        case ASTTag::BLOCK_STMT:
            genStmt(n->kids[0]);
            break;

        case ASTTag::IF_STMT: {
            std::string L_false = newLabel();
            std::string L_end   = newLabel();

            std::string cond = genExpr(n->kids[0]);
            emit("ifFalse", cond, "", L_false, lastLoc_);

            genStmt(n->kids[1]);
            if (n->kids.size() == 3) {
                emit("goto", "", "", L_end, lastLoc_);
                emit("label", "", "", L_false, lastLoc_);
                genStmt(n->kids[2]);
                emit("label", "", "", L_end, lastLoc_);
            } else {
                emit("label", "", "", L_false, lastLoc_);
            }
            break;
        }

        case ASTTag::WHILE_STMT: {
            std::string L_top   = newLabel();
            std::string L_false = newLabel();
            emit("label", "", "", L_top, lastLoc_);

            std::string cond = genExpr(n->kids[0]);
            emit("ifFalse", cond, "", L_false, lastLoc_);

            breakLabels_.push_back(L_false);
            continueLabels_.push_back(L_top);

            genStmt(n->kids[1]);
            emit("goto", "", "", L_top, lastLoc_);
            emit("label", "", "", L_false, lastLoc_);

            breakLabels_.pop_back();
            continueLabels_.pop_back();
            break;
        }

        case ASTTag::DO_WHILE_STMT: {
            std::string L_top   = newLabel();
            std::string L_false = newLabel();
            emit("label", "", "", L_top, lastLoc_);

            breakLabels_.push_back(L_false);
            continueLabels_.push_back(L_top);

            genStmt(n->kids[0]);
            std::string cond = genExpr(n->kids[1]);
            emit("ifTrue", cond, "", L_top, lastLoc_);

            emit("label", "", "", L_false, lastLoc_);

            breakLabels_.pop_back();
            continueLabels_.pop_back();
            break;
        }

        case ASTTag::FOR_STMT: {
            genStmt(n->kids[0]);  // init

            std::string L_top   = newLabel();
            std::string L_false = newLabel();
            emit("label", "", "", L_top, lastLoc_);

            if (!n->kids[1]->kids.empty()) {
                std::string cond = genExpr(n->kids[1]->kids[0]);
                emit("ifFalse", cond, "", L_false, lastLoc_);
            }

            breakLabels_.push_back(L_false);
            continueLabels_.push_back(L_top);

            genStmt(n->kids[3]);         // body
            if (n->kids[2]) genExpr(n->kids[2]);  // iter

            emit("goto", "", "", L_top, lastLoc_);
            emit("label", "", "", L_false, lastLoc_);

            breakLabels_.pop_back();
            continueLabels_.pop_back();
            break;
        }

        case ASTTag::BREAK_STMT:
            assert(!breakLabels_.empty());
            emit("goto", "", "", breakLabels_.back(), lastLoc_);
            break;

        case ASTTag::CONTINUE_STMT:
            assert(!continueLabels_.empty());
            emit("goto", "", "", continueLabels_.back(), lastLoc_);
            break;

        case ASTTag::GOTO_STMT:
            emit("goto", "", "", n->text, lastLoc_);
            break;

        case ASTTag::LABELED_ID_STMT:
            emit("label", "", "", n->text, lastLoc_);
            genStmt(n->kids[0]);
            break;

        case ASTTag::SWITCH_STMT:
            genExpr(n->kids[0]);
            for (auto* c : n->kids[1]->kids)
                genStmt(c);
            break;

        case ASTTag::CASE_STMT:
            genExpr(n->kids[0]);
            genStmt(n->kids[1]);
            break;

        case ASTTag::DEFAULT_STMT:
            genStmt(n->kids[0]);
            break;

        case ASTTag::RETURN_STMT: {
            std::string v = n->kids.empty() ? "" : genExpr(n->kids[0]);
            // 单参 emit("return", ...) 会默认带上 lastLoc_
            emit("return", v);
            break;
        }



        case ASTTag::FOR_DECL_STMT: {
            // *** 进入 for 循环作用域 ***
            if (!originalScope) { // 检查原始作用域是否有效
                std::cerr << "IR Gen Error: Attempting to push scope from a null originalScope at line " << n->loc.line << std::endl;
                // 在这里应该中断处理，例如 break 或 return
                break;
            }
            currentScope_ = originalScope->push();
            scopePushed = true;
            if (!currentScope_) { // 检查 push 操作的结果
                std::cerr << "IR Gen Error: Pushing scope resulted in nullptr at line " << n->loc.line << std::endl;
                // push 失败通常是因为原始 Scope 对象不是由 shared_ptr 管理的，
                // 但我们的 Scope 继承自 enable_shared_from_this，理论上不应失败除非 originalScope 本身有问题。
                // 或者 originalScope->push() 内部实现有错误。
                // 中断处理
                scopePushed = false; // 标记作用域并未成功改变
                break;
            }
            // 处理初始化声明 (现在在新的 currentScope_ 下)
            genStmt(n->kids[0]);

            std::string L_top   = newLabel();
            std::string L_cont  = newLabel(); // Continue 跳转目标
            std::string L_false = newLabel(); // Break 跳转目标

            emit("label", "", "", L_top, lastLoc_); // 条件检查点

            // 处理条件 (在循环作用域内)
            if (n->kids[1] && n->kids[1]->tag == ASTTag::EXPR_STMT && !n->kids[1]->kids.empty()) {
                std::string cond = genExpr(n->kids[1]->kids[0]);
                emit("ifFalse", cond, "", L_false, lastLoc_);
            } // 如果没有条件，则无限循环 (除非内部 break)

            breakLabels_.push_back(L_false);
            continueLabels_.push_back(L_cont);

            // 处理循环体 (在循环作用域内)
            if (n->kids.size() > 3 && n->kids[3]) genStmt(n->kids[3]);

            emit("label", "", "", L_cont, lastLoc_); // continue 跳转到这里
            // 处理迭代 (在循环作用域内)
            if (n->kids.size() > 2 && n->kids[2]) {
                genExpr(n->kids[2]);
            }

            emit("goto", "", "", L_top, lastLoc_); // 跳回条件检查
            emit("label", "", "", L_false, lastLoc_); // break 跳到这里

            breakLabels_.pop_back();
            continueLabels_.pop_back();

            // 离开作用域的操作将在函数末尾统一处理
            break;
        }

        case ASTTag::FUNCTION_DEF: {
            ASTNode* spec_list = n->kids[0]; // 基本不再需要，类型来自符号表
            ASTNode* dtor      = n->kids[1];
            ASTNode* body      = nullptr;
            if (n->kids.size() > 3 && n->kids[3] && n->kids[3]->tag == ASTTag::COMPOUND_STMT) body = n->kids[3];
            else if (n->kids.size() > 2 && n->kids[2] && n->kids[2]->tag == ASTTag::COMPOUND_STMT) body = n->kids[2];

            // --- 1. Extract Function Name ---
            std::string funcName = extractNameFromDeclarator(dtor); // 使用辅助函数
            SourceLoc nameLoc = dtor ? dtor->loc : n->loc;

            if (funcName.empty()) {
                 std::cerr << "IR Gen Error: Could not extract function name from FUNCTION_DEF at line " << n->loc.line << std::endl;
                 funcName = "unknown_function";
            }

            // --- 2. Get Function Type from Symbol Table ---
            TypePtr funcType = nullptr;
            Symbol* funcSymbol = nullptr;
            if (funcName != "unknown_function" && symbolTable_) { // 使用全局 symbolTable_ 查找
                funcSymbol = symbolTable_->lookup(funcName);
            }
            if (funcSymbol && funcSymbol->type && dynamic_cast<FunctionType*>(funcSymbol->type.get())) {
                funcType = funcSymbol->type;
            } else if (funcName != "unknown_function") {
                 // 替换 error 调用
                 std::cerr << "IR Gen Error: Could not find symbol or valid type for function '" << funcName << "' in symbol table at line " << nameLoc.line << std::endl;
            }

            // --- 3. Emit Label ---
            emit("label", "", "", funcName, n->loc, /*var=*/"", funcType);

            // --- 4. Enter Function Scope ---
            if (!originalScope) { // 检查原始作用域是否有效
                std::cerr << "IR Gen Error: Attempting to push scope from a null originalScope at line " << n->loc.line << std::endl;
                // 在这里应该中断处理，例如 break 或 return
                break;
            }
            currentScope_ = originalScope->push();
            if (!currentScope_) { // 检查 push 操作的结果
                std::cerr << "IR Gen Error: Pushing scope resulted in nullptr at line " << n->loc.line << std::endl;
                // push 失败通常是因为原始 Scope 对象不是由 shared_ptr 管理的，
                // 但我们的 Scope 继承自 enable_shared_from_this，理论上不应失败除非 originalScope 本身有问题。
                // 或者 originalScope->push() 内部实现有错误。
                // 中断处理
                scopePushed = false; // 标记作用域并未成功改变
                break;
            }
            scopePushed = true;

            // --- 5. Process Parameters (不需要 buildType) ---
            // IR 生成阶段假设参数已由 SemanticAnalyzer 添加到符号表。
            // 这里不需要重新插入或构建类型，只需确保后续代码在正确的 scope 中执行。
            // 如果需要为参数生成特定 IR（如 'arg_alloc'），可以在此处理。
            // （省略了之前添加参数到 currentScope 的代码，因为这是 SemanticAnalyzer 的职责）

            // --- 6. Generate Function Body ---
            if (body) {
                 genStmt(body);
            } else {
                 std::cerr << "IR Gen Warning: Function '" << funcName << "' has no body at line " << n->loc.line << std::endl;
            }

            break; // FUNCTION_DEF handled
        }

        default:
            for (auto* c : n->kids)
                genStmt(c);
            break;
    }
    if (scopePushed) {
        if (currentScope_) { // 添加检查，防止对空指针调用 pop
            currentScope_ = currentScope_->pop(); // 正确：恢复到父作用域
            if (!currentScope_) {
                // 这个情况通常不应该发生，除非我们弹出了最外层的全局作用域
                std::cerr << "IR Gen Error: Popped scope resulted in nullptr! (Likely popped global scope or scope management issue)" << std::endl;
                // 在这里可能需要抛出异常或采取其他错误处理措施
            }
        } else {
            // 如果 scopePushed 为 true 但 currentScope_ 已经是 nullptr，说明状态已损坏
            std::cerr << "IR Gen Error: Scope stack corrupted before pop attempt." << std::endl;
        }
    }

}

