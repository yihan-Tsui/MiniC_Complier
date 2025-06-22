#ifndef MINI_C_IR_H
#define MINI_C_IR_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "symbol.h"
#include "ast.h"
#include "type.h"

struct Quad {
    std::string op;      // 操作码，如 "+", "=", "ifFalse", "param", "call", "label", "goto" 等
    std::string arg1;    // 第一个操作数
    std::string arg2;    // 第二个操作数（如有）
    std::string result;  // 结果或目标临时变量、标签名
    SourceLoc  loc;      // 位置
    std::string var;     // 如果这是对某个源变量的操作，就记录它的名字
    TypePtr     type;    // 这条指令结果或变量的类型
};

class IRGenerator {
public:
// 在 ir.cpp 中替换 IRGenerator 构造函数

IRGenerator(std::shared_ptr<Scope> globalScope)
    // 在初始化列表中先打印 globalScope 的状态
    : tempCount_(0), labelCount_(0), lastLoc_({0,0}),
      symbolTable_(
          // 使用 lambda 在移动前打印 globalScope 状态
          [&]() -> std::shared_ptr<Scope> {
              std::cerr << "[DEBUG] IRGenerator Constructor: Initializing symbolTable_..." << std::endl;
              std::cerr << "[DEBUG]   Input globalScope valid? " << (globalScope ? "Yes" : "No") << std::endl;
              if(globalScope) std::cerr << "[DEBUG]   Input globalScope points to: " << globalScope.get() << std::endl;
              return std::move(globalScope); // 执行移动
          }() // 立即调用 lambda
      ),
      currentScope_(
          // 使用 lambda 在复制前打印 symbolTable_ 状态
          [&]() -> std::shared_ptr<Scope> {
              std::cerr << "[DEBUG] IRGenerator Constructor: Initializing currentScope_..." << std::endl;
              std::cerr << "[DEBUG]   symbolTable_ (after move) valid? " << (symbolTable_ ? "Yes" : "No") << std::endl;
              if(symbolTable_) std::cerr << "[DEBUG]   symbolTable_ points to: " << symbolTable_.get() << std::endl;
              return symbolTable_; // 执行复制
          }() // 立即调用 lambda
      ),
      tmpIdx_(0), labelIdx_(0)
{
    // 构造函数体内的检查
    std::cerr << "[DEBUG] IRGenerator Constructor Body Entry." << std::endl;

    // 检查 symbolTable_
    if (!symbolTable_) {
         std::cerr << "FATAL ERROR in IRGenerator Constructor Body: symbolTable_ is null!" << std::endl;
         throw std::runtime_error("IRGenerator requires a valid global scope (symbolTable_ check failed).");
    } else {
         std::cerr << "[DEBUG] IRGenerator Constructor Body: symbolTable_ check passed (points to: " << symbolTable_.get() << ")." << std::endl;
    }

    // 检查 currentScope_ (这是之前出错的地方)
    if (!currentScope_) {
         std::cerr << "FATAL ERROR in IRGenerator Constructor Body: currentScope_ is null!" << std::endl;
         std::cerr << "[DEBUG]   Value of symbolTable_.get() at this point: " << symbolTable_.get() << std::endl; // 再次打印 symbolTable_ 指针
         throw std::runtime_error("IRGenerator scope initialization failed (currentScope_ check failed).");
    } else {
         std::cerr << "[DEBUG] IRGenerator Constructor Body: currentScope_ check passed (points to: " << currentScope_.get() << ")." << std::endl;
    }
     std::cerr << "[DEBUG] IRGenerator Constructor Body Exit." << std::endl;
}
    std::shared_ptr<Scope> symbolTable_;
    std::shared_ptr<Scope> currentScope_;
    // 生成入口
    std::vector<Quad> generate(ASTNode* root);
    void recordLoc(SourceLoc loc);

    int tempCount_ = 0;
    int labelCount_ = 0;
    std::vector<Quad> quads_;
    std::vector<std::string> breakLabels_;
    std::vector<std::string> continueLabels_;

    SourceLoc lastLoc_;                    // 记录上一次要用的位置信息
    std::unordered_map<std::string,TypePtr> tempTypes_; // 临时变量类型映射
    int tmpIdx_ = 0, labelIdx_ = 0;

    // 产生新的临时变量名 t1, t2, …
    std::string newTemp() {
        return "t" + std::to_string(++tempCount_);
    }
    // 产生新的标签名 L1, L2, …
    std::string newLabel() {
        return "L" + std::to_string(++labelCount_);
    }
    //——— 新版 emit，将类型一起记录 —————————————————————————
    void emit(const std::string &op,
                           const std::string &arg1,
                           const std::string &arg2,
                           const std::string &res,
                           SourceLoc loc,
                           const std::string &var,
                           TypePtr type) {
        quads_.push_back({op, arg1, arg2, res, loc, var, type});
    }

    //——— 兼容旧调用的重载，默认 var = ""，type = nullptr —————————————
    void emit(const std::string &op,
                           const std::string &arg1,
                           const std::string &arg2,
                           const std::string &res) {
        emit(op, arg1, arg2, res, lastLoc_, /*var=*/"", /*type=*/nullptr);
    }
    void emit(const std::string &op,
                           const std::string &arg1,
                           const std::string &arg2,
                           const std::string &res,
                           SourceLoc loc) {
        emit(op, arg1, arg2, res, loc, /*var=*/"", /*type=*/nullptr);
    }
    void emit(const std::string &op,
                           const std::string &arg1) {
        emit(op, arg1, /*arg2=*/"", /*res=*/"", lastLoc_, /*var=*/"", /*type=*/nullptr);
    }

    // 递归生成表达式，返回这个表达式的结果临时变量或直接变量名
    std::string genExpr(ASTNode* n);
    // 递归生成语句
    void genStmt(ASTNode* n);
};

#endif // MINI_C_IR_H
