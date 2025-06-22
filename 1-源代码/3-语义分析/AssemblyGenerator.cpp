// AssemblyGenerator.cpp
#include "AssemblyGenerator.h"
#include <sstream>
#include <iostream>
#include <cctype>
#include <cassert>

AssemblyGenerator::AssemblyGenerator(const std::vector<Quad> &quads)
        : quads_(quads), stackSize_(0) {
    allocateStack();
}

void AssemblyGenerator::allocateStack() {
    int offset = 0;

    // 1) 给所有源变量（localOffset_）分配空间
    for (auto &q : quads_) {
        if (!q.var.empty() && localOffset_.count(q.var) == 0) {
            offset += 8;
            localOffset_[q.var] = offset;
        }
    }

    // 2) 给所有临时变量（t1, t2, ...）分配空间
    for (auto &q : quads_) {
        if (!q.result.empty() && q.result[0] == 't'
            && tempOffset_.count(q.result) == 0) {
            offset += 8;
            tempOffset_[q.result] = offset;
        }
    }

    // 16 字节对齐
    stackSize_ = ((offset + 15) / 16) * 16;
}

std::string AssemblyGenerator::generate() {
    std::ostringstream out;

    // 1) 段和全局符号声明
    out << ".text\n";
    out << ".globl _main\n";

    // 2) 如果首条 IR 是一条 "label main"，先输出 _main:，然后 prologue
    size_t idx = 0;
    if (!quads_.empty() && quads_[0].op == "label" && quads_[0].result == "main") {
        out << "_main:\n";
        emitPrologue(out);
        idx = 1;
    } else {
        // 否则也输出 prologue
        emitPrologue(out);
    }

    // 3) 其余指令
    for (size_t i = idx; i < quads_.size(); ++i) {
        emitInstruction(quads_[i], out);
    }

    // 4) epilogue
    emitEpilogue(out);
    return out.str();
}

void AssemblyGenerator::emitPrologue(std::ostream &os) const {
    os << "\tstp x29, x30, [sp, #-16]!   // push FP, LR\n";
    os << "\tmov x29, sp\n";
    if (stackSize_ > 0) {
        os << "\tsub sp, sp, #" << stackSize_ << "\n";
    }
}

void AssemblyGenerator::emitEpilogue(std::ostream &os) const {
    if (stackSize_ > 0) {
        os << "\tadd sp, sp, #" << stackSize_ << "\n";
    }
    os << "\tldp x29, x30, [sp], #16   // pop FP, LR\n";
    os << "\tret\n";
}

void AssemblyGenerator::loadOperand(const std::string &name, std::ostream &os) const {
    if (!name.empty() && std::isdigit(name[0])) {
        // 立即数
        os << "\tmov w9, #" << name << "\n";
    }
    else if (localOffset_.count(name)) {
        // 局部变量
        os << "\tldr w9, [x29, #-" << localOffset_.at(name) << "]\n";
    }
    else if (tempOffset_.count(name)) {
        // 临时变量
        os << "\tldr w9, [x29, #-" << tempOffset_.at(name) << "]\n";
    }
    else {
        // 全局变量
        os << "\tadrp x10, " << name << "\n";
        os << "\tadd  x10, x10, :lo12:" << name << "\n";
        os << "\tldr w9, [x10]\n";
    }
}

void AssemblyGenerator::storeResult(const std::string &name, std::ostream &os) const {
    if (localOffset_.count(name)) {
        // 局部变量
        os << "\tstr w9, [x29, #-" << localOffset_.at(name) << "]\n";
    }
    else if (tempOffset_.count(name)) {
        // 临时变量
        os << "\tstr w9, [x29, #-" << tempOffset_.at(name) << "]\n";
    }
    else {
        // 全局变量
        os << "\tadrp x10, " << name << "\n";
        os << "\tadd  x10, x10, :lo12:" << name << "\n";
        os << "\tstr w9, [x10]\n";
    }
}

void AssemblyGenerator::emitInstruction(const Quad &q, std::ostream &os) const {
    using std::string;

    // 标签
    if (q.op == "label") {
        // 非 main 的其他标签直接原样输出
        if (q.result != "main") {
            os << q.result << ":\n";
        }
        return;
    }

    // 无条件跳转
    if (q.op == "goto") {
        os << "\tb " << q.result << "\n";
        return;
    }

    // ifFalse x -> cmp x, #0; beq L
    if (q.op == "ifFalse") {
        loadOperand(q.arg1, os);
        os << "\tcmp w9, #0\n";
        os << "\tbeq " << q.result << "\n";
        return;
    }

    // 赋值 =
    if (q.op == "=") {
        loadOperand(q.arg1, os);
        storeResult(q.result, os);
        return;
    }

    // 二元算术/逻辑运算
    static const std::unordered_map<string, string> binOpMap = {
            { "+",  "add"  }, { "-",  "sub"  }, { "*",   "mul"  },
            { "/",  "sdiv" }, { "<<", "lsl"  }, { ">>",  "lsr"  },
            { "&",  "and"  }, { "|",  "orr"  }, { "^",   "eor"  }
    };
    if (binOpMap.count(q.op)) {
        loadOperand(q.arg1, os);
        os << "\tmov w10, w9\n";
        loadOperand(q.arg2, os);
        os << "\tmov w11, w9\n";
        os << "\t" << binOpMap.at(q.op) << " w9, w10, w11\n";
        storeResult(q.result, os);
        return;
    }

    // 比较运算，使用 cset 生成布尔 0/1
    static const std::unordered_map<string, string> cmpCondMap = {
            {"==", "eq"}, {"!=", "ne"},
            {"<",  "lt"}, {">",  "gt"},
            {"<=", "le"}, {">=", "ge"}
    };
    if (cmpCondMap.count(q.op)) {
        loadOperand(q.arg1, os);
        os << "\tmov w10, w9\n";
        loadOperand(q.arg2, os);
        os << "\tmov w11, w9\n";
        os << "\tcmp w10, w11\n";
        os << "\tcset w9, " << cmpCondMap.at(q.op) << "\n";
        storeResult(q.result, os);
        return;
    }

    // call / param / return
    if (q.op == "param") {
        return;
    }
    if (q.op == "call") {
        os << "\tbl " << q.arg1 << "\n";
        os << "\tmov w9, w0\n";
        storeResult(q.result, os);
        return;
    }
    if (q.op == "return") {
        if (!q.arg1.empty()) {
            loadOperand(q.arg1, os);
            os << "\tmov w0, w9\n";
        }
        return;
    }

    std::cerr << "Unhandled IR op: " << q.op << "\n";
}
