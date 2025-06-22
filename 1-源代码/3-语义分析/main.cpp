// main.cpp
#include "ast.h"
#include "mini_c.tab.hpp" // Bison生成的头文件
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>           // 需要包含 vector
#include <fstream>          // 需要包含 fstream 用于文件输出
#include <filesystem>       // 需要包含 filesystem (C++17) 用于路径操作

#include "interpreter.h"    // 可能其他模式需要
#include "ir.h"             // IR 定义
#include "semantic.h"       // 语义分析器
#include "AssemblyGenerator.h" // *** 包含汇编生成器头文件 ***
#include "ObjectFileGenerator.h"
#include "InstructionEncoder.h"   // 你的指令编码器
#include "PrettyPrinter.h"

// 错误处理函数
void error(const char* msg)
{
    // 注意：Bison/Flex 可能在内部调用这个，确保它符合需要
    // 或者在Flex/Bison中使用 YYERROR 宏
    std::fprintf(stderr, "Lexer/Parser error: %s\n", msg);
}


extern FILE* yyin; // Flex 使用的输入文件指针
extern ASTNode *ast_root; // Bison 解析后生成的 AST 根节点 (在 .y 文件中定义)

/*──────────────────────────────
 * 简易 AST pretty‑printer
 *─────────────────────────────*/
// (tag_name, node_loc, print_ast 函数保持不变)
static const char* tag_name(ASTTag t)
{
#define CASE(x) case ASTTag::x: return #x;
    switch (t) {
        CASE(ID) CASE(CONST) CASE(STRING)
        CASE(UNARY) CASE(BINARY) CASE(LOGIC_AND) CASE(LOGIC_OR)
        CASE(COND) CASE(ASSIGN)
        CASE(ARRAY_REF) CASE(STRUCT_REF) CASE(FUNC_CALL)
        CASE(PRE_INC) CASE(PRE_DEC) CASE(POST_INC) CASE(POST_DEC)
        CASE(SIZEOF_EXPR) CASE(CAST_EXPR) CASE(COMPOUND_LITERAL)
        CASE(EXPR_LIST) CASE(ARG_LIST)

        CASE(SPECIFIER) CASE(SPEC_LIST) CASE(DECLARATION) CASE(INIT_DECL)
        CASE(INIT_DECL_LIST) CASE(DECLARATOR) CASE(ARRAY_DECL) CASE(FUNC_DECL)
        CASE(OLD_FUNC_DECL) CASE(POINTER) CASE(PARAM_DECL) CASE(PARAM_LIST)
        CASE(ENUM_SPEC) CASE(SU_SPEC) CASE(STRUCT_DECL) CASE(ENUM_CONST)
        CASE(TYPE_NAME_NODE) CASE(ABS_DECL) CASE(ABS_ARRAY) CASE(ABS_FUNC)

        CASE(INIT_EXPR) CASE(INIT_LIST_NODE) CASE(INIT_ITEM_LIST)
        CASE(DESIGNATED_INIT) CASE(ARRAY_DESIGNATOR) CASE(FIELD_DESIGNATOR)

        CASE(LABELED_ID_STMT) CASE(CASE_STMT) CASE(DEFAULT_STMT)
        CASE(COMPOUND_STMT) CASE(EXPR_STMT) CASE(IF_STMT) CASE(SWITCH_STMT)
        CASE(WHILE_STMT) CASE(DO_WHILE_STMT) CASE(FOR_STMT) CASE(FOR_DECL_STMT)
        CASE(GOTO_STMT) CASE(CONTINUE_STMT) CASE(BREAK_STMT) CASE(RETURN_STMT)
        CASE(BLOCK_ITEM_LIST) CASE(BLOCK_DECL) CASE(BLOCK_STMT) // 添加了 BLOCK_DECL

        CASE(TRANSL_UNIT) CASE(DECL_STMT) CASE(FUNCTION_DEF)
        // 添加其他可能存在的 Tag
        default: return "UNKNOWN";
    }
#undef CASE
}

static SourceLoc node_loc(const ASTNode* n) {
    if (!n) return {0, 0};
    if (n->loc.line || n->loc.col) return n->loc;
    if (!n->kids.empty() && n->kids[0]) return node_loc(n->kids[0]); // 添加空指针检查
    return n->loc;
}

static void print_ast(const ASTNode* n, int indent = 0)
{
    if (!n) return;
    auto l = node_loc(n);
    std::cout << std::string(indent,' ')
              << "[" << l.line << ":" << l.col << "] "
              << tag_name(n->tag) ;

    if (!n->text.empty()) std::cout << " \"" << n->text << "\"";
    if (n->ival) std::cout << " (" << n->ival << ")";
    if (n->flag) std::cout << " [flag]";
    // 打印类型信息（如果存在）
    if (n->type) std::cout << " {type: " << n->type->toString() << "}";


    std::cout << '\n';
    for (auto* child : n->kids) print_ast(child, indent + 2);
}

/*──────────────────────────────
 * main
 *─────────────────────────────*/
int main(int argc, char* argv[])
{
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <operation> <file>\n";
        std::cerr << "Operations: static_compile, view_ast, view_ir, gen_asm\n";
        return 1;
    }

    std::string operation = argv[1];
    std::string inputFilename = argv[2];

    yyin = std::fopen(inputFilename.c_str(), "r");
    if (!yyin) {
        std::perror(inputFilename.c_str());
        return 2;
    }

    if (yyparse() == 0 && ast_root != nullptr) {
        // 1. 语义分析
        SemanticAnalyzer sema;
        sema.analyze(ast_root); // 调用 analyze (返回 void)

        // *** 修正错误检查 ***
        // 通过检查 diagnostics() 的结果来判断是否有错误
        bool hasSemanticErrors = !sema.diagnostics().empty();

        if (hasSemanticErrors) {
             std::cerr << "[!] Semantic Errors Detected:\n";
             for (const auto &d : sema.diagnostics()) { // 直接使用 diagnostics() 获取错误
                 std::cerr << "  [" << d.loc.line << ":" << d.loc.col << "] Error: "
                           << d.message << "\n";
             }
             std::cerr << "Compilation aborted due to semantic errors.\n";
             fclose(yyin);
             return 3; // 返回错误码
        }
        // else { // 如果没有错误，可以继续执行
        //     std::cout << "Semantic analysis successful.\n";
        // }

        // 2. 根据操作执行不同逻辑 (后续代码保持不变)
        if (operation == "sc") {
            std::cout << "Static compilation checks passed (Semantic Analysis).\n";
        } else if (operation == "ast") {
            std::cout << "---- Abstract Syntax Tree (AST) ----\n";
            print_ast(ast_root);
        } else if (operation == "ir") {
            // ... (view_ir 代码保持不变) ...
            auto globalScope = sema.getGlobalScope();
            if (!globalScope) { // *** 添加检查 ***
                std::cerr << "FATAL ERROR in main: SemanticAnalyzer::getGlobalScope() returned a null pointer!" << std::endl;
                fclose(yyin);
                return 6; // 或者其他错误码
            }
            IRGenerator irgen(globalScope);
            auto quads = irgen.generate(ast_root);
            std::cout << "\n---- Three-address code (IR) ----\n";
            for (const auto &q : quads) {
                printf("%-8s %-8s %-8s -> %-8s",
                       q.op.c_str(),
                       q.arg1.c_str(),
                       q.arg2.c_str(),
                       q.result.c_str());
                printf("  @ (%d,%d)", q.loc.line, q.loc.col);
                if (!q.var.empty()) printf("  var=%s", q.var.c_str());
                if (q.type) printf("  type=%s", q.type->toString().c_str());
                printf("\n");
            }
        }

        else if (operation == "debug") {
            auto globalScope = sema.getGlobalScope();
            IRGenerator irgen(globalScope);
            auto quads = irgen.generate(ast_root);
            IRInterpreter interp;
            interp.runStepByStep(quads);
        }

        else if (operation == "asm") {
            // 确保拿到全局符号表
            auto globalScope = sema.getGlobalScope();
            if (!globalScope) {
                std::cerr << "FATAL ERROR in main: SemanticAnalyzer::getGlobalScope() returned a null pointer!" << std::endl;
                fclose(yyin);
                return 6;
            }

            // 生成 IR
            IRGenerator irgen(globalScope);
            auto quads = irgen.generate(ast_root);

            // 生成 ARM64 汇编
            AssemblyGenerator asmGen(quads);
            std::string asmCode = asmGen.generate();

            // 将汇编代码写入文件
            std::ofstream outFile("1.s"); // 你可以自定义文件名
            if (!outFile) {
                std::cerr << "Error: Failed to open output file for writing!" << std::endl;
                fclose(yyin);
                return 7;
            }
            outFile << asmCode;
            outFile.close();

            std::cout << "Assembly code successfully written to '1.s'.\n";
        }

        else if (operation == "obj") {
            const char* assemblyFile = "1.s";
            const char* objectFile = "1.o";

            // 调用系统命令：使用 `as` 汇编器来将 `1.s` 编译成 `1.o`
            std::string command = "as " + std::string(assemblyFile) + " -o " + std::string(objectFile);

            // 输出命令并执行
            std::cout << "Running command: " << command << std::endl;

            // 执行命令
            int result = system(command.c_str());

            // 检查命令是否执行成功
            if (result == 0) {
                std::cout << "Compilation successful, " << objectFile << " created." << std::endl;
            } else {
                std::cerr << "Error during compilation." << std::endl;
            }
        }

        else if (operation == "exec") {
            const char* objectFile = "1.o";
            const char* executableFile = "1";

            // 调用系统命令：使用 `g++` 链接器将 `1.o` 链接成可执行文件 `1`
            std::string command = "g++ " + std::string(objectFile) + " -o " + std::string(executableFile);

            // 输出命令并执行
            std::cout << "Running command: " << command << std::endl;

            // 执行命令
            int result = system(command.c_str());

            // 检查命令是否执行成功
            if (result == 0) {
                std::cout << "Executable created successfully: " << executableFile << std::endl;
            } else {
                std::cerr << "Error during linking." << std::endl;
            }
        }

        else if (operation == "pp") {
            PrettyPrinter pp(std::cout, /*缩进宽度*/ 4);
            pp.print(ast_root);
        }


        else {
             std::cerr << "Error: Unknown operation '" << operation << "'\n";
             std::cerr << "Available operations: static_compile, view_ast, view_ir, gen_asm\n";
             fclose(yyin);
             return 1;
        }

        fclose(yyin);
        return 0;
    } else {
        std::cerr << "Error: Parsing failed";
        if (ast_root == nullptr && yyin != nullptr) {
            std::cerr << " (AST generation failed)";
        }
         std::cerr << ".\n";
        if (yyin) fclose(yyin);
        return 1;
    }
}