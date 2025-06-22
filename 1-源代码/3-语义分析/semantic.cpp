// semantic.cpp
#include "semantic.h"
#include "type.h"     // 稍后实现
#include <iostream>
#include "ast.h"


SemanticAnalyzer::SemanticAnalyzer() {
    // 1) 创建全局作用域
    currentScope_ = std::make_shared<Scope>(nullptr);
    rootScope_ = currentScope_;
    // 2) 预先注册标准库函数原型（extern）。以 printf 为例：
    {
        // 返回类型 int
        TypePtr ret = std::make_shared<BasicType>(TS_INT);
        // 第一个参数 const char*
        TypePtr p0 = std::make_shared<PointerType>(
                         std::make_shared<BasicType>(TS_CHAR));
        // 可变参数标记：最后一个 bool 为 true
        std::vector<TypePtr> params = { p0 };
        TypePtr printfTy = std::make_shared<FunctionType>(ret, params, true);
        // 插入符号表：名字、类型、存储类别 extern、位置可随意填 (0,0)
        currentScope_->insert({ "printf", printfTy, SC_EXTERN, SourceLoc{0,0} });
    }

}

void SemanticAnalyzer::analyze(ASTNode* root) {
    visit(root);
}

// 构造类型：给出 specifier 列表和 declarator 节点
// semantic.cpp

static TypePtr buildType(ASTNode* spec_list, ASTNode* declarator) {
    // —— 1. 处理 spec_list ——
    // 缺省用 int
    TypeSpecifier ts = TS_INT;
    if (spec_list) {
        for (auto* spec : spec_list->kids) {
            if (spec && spec->tag == ASTTag::SPECIFIER) {
                ts = static_cast<TypeSpecifier>(spec->ival);
                break;
            }
        }
    }
    TypePtr ty = std::make_shared<BasicType>(ts);

    // —— 2. 递归处理 declarator，各种修饰 ——
    std::function<TypePtr(ASTNode*, TypePtr)> applyDeclarator =
        [&](ASTNode* decl, TypePtr base) -> TypePtr {
            if (!decl) return base;
            switch (decl->tag) {
                case ASTTag::POINTER: {
                    ASTNode* child = !decl->kids.empty() ? decl->kids[0] : nullptr;
                    return std::make_shared<PointerType>(applyDeclarator(child, base));
                }
                case ASTTag::ARRAY_DECL: {
                    // kids: [ direct_decl, (tq_list?), (size_expr?) ]
                    ASTNode* sizeNode = nullptr;
                    if (decl->kids.size() >= 3 && decl->kids[2] && decl->kids[2]->tag == ASTTag::CONST)
                        sizeNode = decl->kids[2];
                    int size = sizeNode ? static_cast<int>(sizeNode->ival) : -1;
                    // 先把 direct_decl（kids[0]）处理上去
                    TypePtr elem = applyDeclarator(decl->kids.empty() ? nullptr : decl->kids[0], base);
                    return std::make_shared<ArrayType>(elem, size);
                }
                case ASTTag::FUNC_DECL: {
                    // kids: [ direct_decl, (param_list?) ]
                    std::vector<TypePtr> params;
                    if (decl->kids.size() == 2 && decl->kids[1]) {
                        for (auto* p : decl->kids[1]->kids) {
                            if (!p) continue;
                            ASTNode* pspec = p->kids.empty() ? nullptr : p->kids[0];
                            ASTNode* pdtor = (p->kids.size()>1 ? p->kids[1] : nullptr);
                            params.push_back(buildType(pspec, pdtor));
                        }
                    }
                    return std::make_shared<FunctionType>(base, params, false);
                }
                case ASTTag::DECLARATOR: {
                    // kids 可能是 0、1、2 三种
                    size_t k = decl->kids.size();
                    if (k == 0) {
                        return base;
                    }
                    // 先处理最末级修饰
                    ASTNode* last = decl->kids.back();
                    TypePtr t = applyDeclarator(last, base);
                    // 若有两个修饰（pointer + direct_decl），再处理 pointer
                    if (k == 2 && decl->kids[0]) {
                        t = applyDeclarator(decl->kids[0], t);
                    }
                    return t;
                }
                default:
                    return base;
            }
        };

    // —— 最终从 declarator（可能为空）开始递归 ——
    return applyDeclarator(declarator, ty);
}


void SemanticAnalyzer::visit(ASTNode* n) {
    if (!n) return;
    switch (n->tag) {
        case ASTTag::FUNCTION_DEF:    visitFunctionDef(n);    break;
        case ASTTag::COMPOUND_STMT:   visitCompoundStmt(n);   break;
        case ASTTag::DECLARATION:     visitDeclaration(n);    break;
        case ASTTag::INIT_DECL:       visitInitDecl(n);       break;
        case ASTTag::ID:              visitIdentifier(n);     break;

        case ASTTag::FOR_DECL_STMT:   visitForDeclStmt(n);    break; // <-- Add this case if missing


        default:
            // 递归遍历所有子节点
            for (auto* c : n->kids) visit(c);
    }
}

void SemanticAnalyzer::visitForDeclStmt(ASTNode* n) {
    // n->kids = { decl, cond_expr_stmt, iter_expr?, body }

    // --- 1. 进入 for 循环的新作用域 ---
    currentScope_ = currentScope_->push();
    bool scopePushed = true; // Assume push succeeds for now

    if (!currentScope_) {
        error(n->loc, "Semantic Error: Failed to push scope for FOR loop.");
        scopePushed = false;
        // Maybe try to visit children anyway to find other errors? Depends on desired robustness.
    }

    // --- 2. 访问初始化声明 (在新的作用域内) ---
    // decl is n->kids[0], which should be a DECLARATION node
    if (n->kids.size() > 0 && n->kids[0]) {
        visit(n->kids[0]); // This will eventually call visitDeclaration -> visitInitDecl for 'i'
    }

    // --- 3. 访问条件表达式 (在新的作用域内) ---
    // cond_expr_stmt is n->kids[1]
    if (n->kids.size() > 1 && n->kids[1]) {
        visit(n->kids[1]);
        // TODO: Add type checking, expect boolean result for condition
    }

    // --- 4. 访问迭代表达式 (在新的作用域内) ---
    // iter_expr is n->kids[2] (optional)
    if (n->kids.size() > 2 && n->kids[2]) {
        visit(n->kids[2]);
    }

    // --- 5. 访问循环体 (在新的作用域内) ---
    // body is n->kids[3]
    if (n->kids.size() > 3 && n->kids[3]) {
        visit(n->kids[3]);
    }

    // --- 6. 离开 for 循环作用域 ---
    if (scopePushed && currentScope_) { // Ensure scope was pushed and is still valid
        currentScope_ = currentScope_->pop();
    }
}

// 在 semantic.cpp 中替换掉旧的 visitFunctionDef

void SemanticAnalyzer::visitFunctionDef(ASTNode* n) {
    // kids: { spec_list, declarator, [decl_list], compound_stmt }
    ASTNode* spec_list = n->kids[0];
    ASTNode* dtor      = n->kids[1]; // 顶层 declarator 节点
    ASTNode* body      = (n->kids.size() > 3 && n->kids.back()->tag == ASTTag::COMPOUND_STMT)
                           ? n->kids.back() // 通常是最后一个，但做个检查
                           : nullptr;
     if (!body && n->kids.size() > 2 && n->kids[2]->tag == ASTTag::COMPOUND_STMT) {
         body = n->kids[2]; // 兼容没有 decl_list 的情况
     }


    // --- 1. 构建函数类型 ---
    // buildType 函数会递归处理 dtor 来构建包含参数和返回类型的完整 FunctionType
    TypePtr funcType = buildType(spec_list, dtor);

    // --- 2. 提取函数名 (使用与 IRGenerator 中相同的、基于 AST 的修正逻辑) ---
    std::string funcName = "unknown_function"; // 默认备用名
    if (dtor && dtor->tag == ASTTag::DECLARATOR && !dtor->kids.empty()) {
         // 假设 FUNC_DECL 是顶层 DECLARATOR 的最后一个子节点
         ASTNode* funcDeclNode = dtor->kids.back();
         if (funcDeclNode && funcDeclNode->tag == ASTTag::FUNC_DECL && !funcDeclNode->kids.empty()) {
              // 假设包含名字的 DECLARATOR 是 FUNC_DECL 的第一个子节点
              ASTNode* nameDeclaratorNode = funcDeclNode->kids[0];
              // 检查这个节点是否是 DECLARATOR 并且 text 字段非空
              if (nameDeclaratorNode && nameDeclaratorNode->tag == ASTTag::DECLARATOR && !nameDeclaratorNode->text.empty()) {
                   funcName = nameDeclaratorNode->text; // 获取函数名
              }
         }
    }

    if (funcName == "unknown_function") {
        error(dtor ? dtor->loc : n->loc, "Semantic Error: Could not extract function name from definition.");
        // 如果无法提取函数名，后续处理可能意义不大，可以考虑提前返回
        // return;
    }

    // --- 3. 将函数符号插入到 *当前* 作用域 ---
    // 此时 currentScope_ 应该是全局作用域
    SourceLoc nameLoc = dtor ? dtor->loc : n->loc; // 尽量使用 declarator 的位置
    if (funcName != "unknown_function") {
        // 使用 SC_EXTERN 可能更符合全局函数的语义，但 SC_AUTO 也能工作
        if (!currentScope_->insert({funcName, funcType, SC_EXTERN /* 或 SC_AUTO */, nameLoc})) {
            error(nameLoc, "Semantic Error: Function '" + funcName + "' redefined.");
            // 如果重定义，后续处理也意义不大
            // return;
        } else {
            // 成功插入符号后，可选地将类型指针附加回 AST 节点（如果需要的话）
            // 例如：n->type = funcType.get(); // 附加到 FUNCTION_DEF 节点
            // 或者 dtor->type = funcType.get(); // 附加到 declarator 节点
            // 注意：这样做只是为了方便后续阶段访问，不管理内存
            if(dtor) dtor->type = funcType.get(); // 尝试附加到 dtor
        }
    }

    // --- 4. 创建并切换到函数内部的新作用域，处理参数 ---
    currentScope_ = currentScope_->push(); // 进入函数作用域

    // 从 FUNC_DECL 节点提取参数列表并添加到新作用域
    if (funcName != "unknown_function" && funcType && // 确保函数名和类型有效
        dtor && dtor->tag == ASTTag::DECLARATOR && !dtor->kids.empty()) {
        ASTNode* funcDeclNode = dtor->kids.back(); // FUNC_DECL
        // 检查是否有参数列表节点 (FUNC_DECL 的第二个子节点)
        if (funcDeclNode && funcDeclNode->tag == ASTTag::FUNC_DECL && funcDeclNode->kids.size() == 2) {
             ASTNode* paramListNode = funcDeclNode->kids[1]; // PARAM_LIST node
             if (paramListNode && paramListNode->tag == ASTTag::PARAM_LIST) {
                 int paramIndex = 0;
                 // 从 FunctionType 获取预期的参数类型，用于交叉验证或处理 K&R 情况
                 auto expectedParamTypes = std::dynamic_pointer_cast<FunctionType>(funcType)->params();

                 for (auto* paramDeclNode : paramListNode->kids) { // 每个孩子是 PARAM_DECL
                     if (paramDeclNode && paramDeclNode->tag == ASTTag::PARAM_DECL && paramDeclNode->kids.size() >= 1) {
                         ASTNode* paramSpec = paramDeclNode->kids[0];
                         ASTNode* paramDtor = (paramDeclNode->kids.size() > 1) ? paramDeclNode->kids[1] : nullptr;

                         // 使用 buildType 构建参数的实际类型
                         TypePtr paramType = buildType(paramSpec, paramDtor);

                         // 提取参数名（如果存在）
                         std::string paramName = "";
                         SourceLoc paramLoc = paramDeclNode->loc;
                         if (paramDtor) {
                            // 提取参数名，需要类似查找函数名的逻辑，但针对参数声明符
                            ASTNode* current = paramDtor;
                            while (current && current->tag != ASTTag::ID && !current->text.empty() && current->tag != ASTTag::DECLARATOR) { // 适配参数名可能在 DECLARATOR text 或其子 ID 中
                                if (!current->kids.empty()) current = current->kids[0]; else break;
                            }
                            if (current && current->tag == ASTTag::ID) {
                                paramName = current->text; paramLoc = current->loc;
                            } else if (current && current->tag == ASTTag::DECLARATOR && !current->text.empty()){
                                paramName = current->text; paramLoc = current->loc;
                            }
                         }

                         // 将参数插入到函数的当前作用域
                         if (!paramName.empty()) {
                             if (!currentScope_->insert({paramName, paramType, SC_AUTO, paramLoc})) {
                                 error(paramLoc, "Semantic Error: Redeclaration of parameter '" + paramName + "'.");
                             } else {
                                // 可选：将类型附加到参数的 AST 节点
                                // if (paramDtor) paramDtor->type = paramType.get();
                             }
                         } else {
                             // TODO: 处理没有名字的参数 (如 void func(int);)
                         }
                         paramIndex++;
                     }
                 }
                 // TODO: 处理可变参数 ... (PARAM_LIST_ELIPS)
             }
        }
    }


    // --- 5. 访问函数体 ---
    if (body) {
        visit(body); // 在函数作用域内处理函数体
    }

    // --- 6. 离开函数作用域 ---
    currentScope_ = currentScope_->pop();
}

void SemanticAnalyzer::visitCompoundStmt(ASTNode* n) {
    // 进入新的块
    currentScope_ = currentScope_->push();
    for (auto* item : n->kids) visit(item);
    currentScope_ = currentScope_->pop();
}

void SemanticAnalyzer::visitDeclaration(ASTNode* n) {
    // 记下 spec_list，以便后面 visitInitDecl 拿到
    lastSpecList_ = n->kids[0];
    // n->kids = {spec_list, [init_decl_list]}
    if (n->kids.size() >= 2) {
        visit(n->kids[1]);  // visit INIT_DECL_LIST
    }
}

void SemanticAnalyzer::visitInitDecl(ASTNode* n) {
    // n->kids = { declarator, [initializer] }
    ASTNode* dtor = n->kids[0];
    SourceLoc nameLoc = dtor ? dtor->loc : n->loc; // 获取名字定义的大概位置

    // 用上一次 visitDeclaration 缓存的 spec_list
    TypePtr varType = buildType(lastSpecList_, dtor);
    std::string name = extractNameFromDeclarator(dtor);
    if (!varType) {
        std::cerr << "[DEBUG Semantic] ERROR: buildType returned nullptr for variable '" << name << "' at line " << nameLoc.line << "!" << std::endl;
        // 你可以在这里决定如何处理：
        // 1. 报告一个内部错误
        error(nameLoc, "Internal Compiler Error: Failed to build type for variable '" + name + "'.");
        // 2. 尝试赋一个默认类型（比如 int），但这可能隐藏问题
        // varType = std::make_shared<BasicType>(TS_INT);
        // 3. 或者直接返回，阻止插入无类型的符号
        if (n->kids.size() == 2) { visit(n->kids[1]); } // 也许仍然访问初始化器
        return;
    }


    // 清空，避免下次乱用
    lastSpecList_ = nullptr;

    // --- 使用与 IR 生成器相同的健壮方法提取名字 ---
 // <--- 修改点

    // --- 添加检查，确保名字提取成功 ---
    if (name.empty()) {
        error(nameLoc, "Semantic Error: Could not extract variable name from declarator.");
        // 如果名字为空，后续插入无意义，可以提前返回或跳过插入
        if (n->kids.size() == 2) { visit(n->kids[1]); } // 仍然处理初始化表达式，以发现其中的错误
        return;
    }

    std::cerr << "[DEBUG Semantic] Inserted '" << name << "' into scope: " << currentScope_.get() << std::endl;
    // --- 使用提取到的名字插入符号表 ---
    if (!currentScope_->insert({name, varType, SC_AUTO, nameLoc})) { // 使用 nameLoc

        error(nameLoc, "Semantic Error: Variable '" + name + "' redefined.");
    }

    // --- 处理初始化器（如果有） ---
    if (n->kids.size() == 2) {
        visit(n->kids[1]); // 访问 initializer
        // TODO: 在这里可以添加类型检查，确保 initializer 的类型与 varType 兼容/可转换
    }
}



void SemanticAnalyzer::visitIdentifier(ASTNode* n) {
    // 使用时查表
    auto* sym = currentScope_->lookup(n->text);
    if (!sym) {
        error(n->loc, "未定义的标识符“" + n->text + "”");
    }
}


