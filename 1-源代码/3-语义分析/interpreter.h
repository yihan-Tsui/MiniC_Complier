#pragma once

#include "ir.h"
#include <unordered_map>
#include <variant>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>



class IRInterpreter {
public:
    void runUntil(const std::vector<Quad>& quads, int breakLine);
    void runStepByStep(const std::vector<Quad>& quads);
    void execute(const Quad& q,
                            const std::vector<Quad>& quads,
                            const std::unordered_map<std::string, int>& labelToIndex);
    std::string findLastSource(const std::vector<Quad>& quads, const std::string& target);
    using Value = std::variant<int, std::string>;
    struct CallFrame {
        int return_pc;
        std::unordered_map<std::string, Value> locals;
    };
    Value getOrZero(const std::string& name);
    std::unordered_map<std::string, Value> memory_;
    std::unordered_map<std::string, TypePtr> types_;
    int pc_ = 0;
    std::unordered_set<int> breakpoints_;
    int lastBreakpointPC = -1;  // 在类中记录
    int asInt(const std::string& s);
    std::string asStr(const std::string& s);
    Value evalBinary(const std::string& op, const Value& a, const Value& b);
    void dumpVariables(int breakLine);
    std::stack<CallFrame> callStack_;
    std::vector<Value> paramStack_;
    std::unordered_map<std::string, int> labelToIndex_;
    std::vector<Quad> quads_;
};

