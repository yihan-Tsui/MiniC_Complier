// PrettyPrinter.h
#ifndef PRETTY_PRINTER_H
#define PRETTY_PRINTER_H

#include "ast.h"
#include <ostream>
#include <functional>

class PrettyPrinter {
public:
    explicit PrettyPrinter(std::ostream& os, int indentWidth = 4)
            : out(os), indentWidth(indentWidth) {}

    void print(ASTNode* root);

private:
    std::ostream& out;
    int indentLevel = 0;
    int indentWidth;

    void indent();
    void newline();
    void withIndent(const std::function<void()>& f);

    void printNode(ASTNode* n);

    // 语句 & 翻译单元
    void printTranslationUnit(ASTNode* n);
    void printFunctionDef(ASTNode* n);
    void printDeclStmt(ASTNode* n);
    void printDeclaration(ASTNode* n);
    void printIfStmt(ASTNode* n);
    void printForStmt(ASTNode* n);
    void printWhileStmt(ASTNode* n);
    void printReturnStmt(ASTNode* n);
    void printCompoundStmt(ASTNode* n);
    void printInitDeclList(ASTNode* n);

    // 表达式
    void printExpr(ASTNode* n);
    void printBinary(ASTNode* n, const char* op);
    void printUnary(ASTNode* n, const char* op, bool prefix=true);
    void printFuncCall(ASTNode* n);
    void printArrayRef(ASTNode* n);
    void printStructRef(ASTNode* n);


    // 声明 & 类型
    void printDeclSpec(ASTNode* n);
    void printDeclarator(ASTNode* n);
    void printParamList(ASTNode* n);

    // 辅助
    bool isStmt(ASTTag tag);
};

#endif // PRETTY_PRINTER_H
