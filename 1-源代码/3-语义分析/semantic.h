#ifndef MINI_C_SEMANTIC_H
#define MINI_C_SEMANTIC_H

#include <vector>
#include <string>
#include <memory>
#include "ast.h"
#include "symbol.h"

struct Diagnostic {
    SourceLoc loc;
    std::string message;
};

class SemanticAnalyzer {
public:
    SemanticAnalyzer();
    void analyze(ASTNode* root);
    void visitForDeclStmt(ASTNode* n);
    const std::vector<Diagnostic>& diagnostics() const { return diags_; }
    std::shared_ptr<Scope> getGlobalScope() const { return rootScope_; }
private:
    std::shared_ptr<Scope> rootScope_;
    std::shared_ptr<Scope> currentScope_;
    std::vector<Diagnostic> diags_;
    void visit(ASTNode* n);
    void visitFunctionDef(ASTNode* n);
    void visitCompoundStmt(ASTNode* n);
    void visitDeclaration(ASTNode* n);
    void visitInitDecl(ASTNode* n);
    void visitIdentifier(ASTNode* n);
    ASTNode* lastSpecList_{nullptr};
    void error(SourceLoc loc, const std::string& msg) {
        diags_.push_back({loc, msg});
    }
};

#endif // MINI_C_SEMANTIC_H
