#include "interpreter.h"
#include <cctype>
#include <sstream>


int IRInterpreter::asInt(const std::string& s) {
    if (s.empty()) return 0;
    if (isdigit(s[0]) || (s[0] == '-' && s.size() > 1 && isdigit(s[1]))) {
        return std::stoi(s);
    }
    return 0;
}



std::string IRInterpreter::asStr(const std::string& s) {
    if (s.size() >= 2 && s.front() == '"' && s.back() == '"') {
        return s.substr(1, s.size() - 2);
    } else if (memory_.count(s) && std::holds_alternative<std::string>(memory_[s])) {
        return std::get<std::string>(memory_[s]);
    }
    return s;
}

void IRInterpreter::runStepByStep(const std::vector<Quad>& quads) {
    // 建立 label -> index 映射 (用于控制流跳转)
    std::unordered_map<std::string, int> labelToIndex;
    for (int i = 0; i < quads.size(); ++i) {
        if (quads[i].op == "label") {
            labelToIndex[quads[i].result] = i;
        }
    }

    std::string cmd;

    while (pc_ < quads.size()) {
        const auto& q = quads[pc_];

        if (breakpoints_.count(q.loc.line)) {
            std::cout << "🟥 Breakpoint hit at line " << q.loc.line << "\n";
            dumpVariables(q.loc.line);

            // ⚠️关键修复：命中断点时立刻执行当前指令！
            execute(q, quads, labelToIndex);

            pc_++;

            // 如果下一条指令属于同一行，也立刻执行，避免二次命中断点
            while (pc_ < quads.size() && quads[pc_].loc.line == q.loc.line) {
                execute(quads[pc_], quads, labelToIndex);
                pc_++;
            }
            continue;
        }

        // 显示当前指令
        std::cout << "[PC " << pc_ << "] " << q.op << " " << q.arg1 << " " << q.arg2 << " -> " << q.result;
        std::cout << " @ line " << q.loc.line << "\n";
        std::cout << "(step> ";
        std::getline(std::cin, cmd);

        if (cmd == "next" || cmd == "n") {
            execute(q, quads, labelToIndex); pc_++;
        }
        else if (cmd.starts_with("break ")) {
            int line = std::stoi(cmd.substr(6));
            breakpoints_.insert(line);
            std::cout << "✅ Breakpoint set at line " << line << "\n";
        }
        else if (cmd == "continue" || cmd == "c") {
            // 先执行当前指令
            execute(q, quads, labelToIndex); pc_++;

            while (pc_ < quads.size()) {
                const auto& current = quads[pc_];

                if (breakpoints_.count(current.loc.line)) {
                    std::cout << "🟥 Breakpoint hit at line " << current.loc.line << "\n";
                    dumpVariables(current.loc.line);

                    // ⚠️关键修复：命中断点立刻执行当前指令！
                    execute(current, quads, labelToIndex); pc_++;

                    // 若下一条同一行，也执行
                    while (pc_ < quads.size() && quads[pc_].loc.line == current.loc.line) {
                        execute(quads[pc_], quads, labelToIndex);
                        pc_++;
                    }

                    break;
                }

                execute(current,quads, labelToIndex);

                // 处理控制流
                if (current.op == "goto") {
                    pc_ = labelToIndex[current.result];
                } else if (current.op == "ifFalse") {
                    int cond = memory_.count(current.arg1) ? std::get<int>(memory_[current.arg1]) : asInt(current.arg1);
                    pc_ = cond ? pc_ + 1 : labelToIndex[current.result];
                } else if (current.op == "ifTrue") {
                    int cond = memory_.count(current.arg1) ? std::get<int>(memory_[current.arg1]) : asInt(current.arg1);
                    pc_ = cond ? labelToIndex[current.result] : pc_ + 1;
                } else {
                    pc_++;
                }
            }
        }
        else if (cmd == "print") {
            dumpVariables(q.loc.line);
        }
        else if (cmd == "exit" || cmd == "q") {
            std::cout << "👋 Exiting...\n";
            break;
        }
        else {
            std::cout << "❓ Unknown command: " << cmd << "\n";
        }
    }
}








IRInterpreter::Value IRInterpreter::evalBinary(const std::string& op, const Value& a, const Value& b) {
    if (std::holds_alternative<int>(a) && std::holds_alternative<int>(b)) {
        int x = std::get<int>(a), y = std::get<int>(b);
        if (op == "+") return x + y;
        if (op == "-") return x - y;
        if (op == "*") return x * y;
        if (op == "/") return y != 0 ? x / y : 0;
        if (op == "<") return x < y;
        if (op == ">") return x > y;
        if (op == "==") return x == y;
        if (op == "!=") return x != y;
        if (op == "&&") return x && y;
        if (op == "||") return x || y;
    }
    return 0;
}

std::string IRInterpreter::findLastSource(const std::vector<Quad>& quads, const std::string& target) {
    for (auto it = quads.rbegin(); it != quads.rend(); ++it) {
        if (it->result == target && !it->arg1.empty()) {
            return it->arg1;
        }
    }
    return "";
}

void IRInterpreter::execute(const Quad& q,
                            const std::vector<Quad>& quads,
                            const std::unordered_map<std::string, int>& labelToIndex) {
    // 类型记录
    if (!q.result.empty() && q.type) {
        types_[q.result] = q.type;
    }


    if (q.op == "=") {
        if (q.arg1.empty()) {
            memory_.emplace(q.result, 0);
        } else if (q.arg1[0] == '"') {
            memory_[q.result] = asStr(q.arg1);
        } else if (isdigit(q.arg1[0]) || (q.arg1[0] == '-' && isdigit(q.arg1[1]))) {
            memory_[q.result] = std::stoi(q.arg1);
        } else {
            memory_[q.result] = memory_.count(q.arg1) ? memory_[q.arg1] : 0;
        }
    }

    else if (q.op == "+" || q.op == "-" || q.op == "*" || q.op == "/" ||
             q.op == "<" || q.op == ">" || q.op == "==" || q.op == "!=" ||
             q.op == "&&" || q.op == "||") {

        Value valA = memory_.count(q.arg1) ? memory_[q.arg1] : asInt(q.arg1);
        Value valB = memory_.count(q.arg2) ? memory_[q.arg2] : asInt(q.arg2);
        memory_[q.result] = evalBinary(q.op, valA, valB);
             }

    else if (q.op == "!") {
        int val = asInt(q.arg1);
        memory_[q.result] = !val;
    }

    else if (q.op == "label" || q.op == "goto" || q.op == "ifTrue" || q.op == "ifFalse") {
        // 控制流不处理，外部 runStepByStep() 会处理 PC 跳转
    }

    // else if (q.op == "param" || q.op == "call" || q.op == "return") {
    //     std::cout << "[WARN] Function-related op '" << q.op << "' not yet supported.\n";
    // }


    else if (q.op == "param") {
        Value val = memory_.count(q.arg1) ? memory_[q.arg1] : asInt(q.arg1);
        paramStack_.push_back(val);
    }

    else if (q.op == "call") {
        CallFrame frame;
        frame.return_pc = pc_ + 1;
        frame.locals = memory_;  // 保存当前变量环境

        callStack_.push(frame);
        memory_.clear();

        int num_args = std::stoi(q.arg2);
        auto it = labelToIndex.find(q.arg1);
        if (it == labelToIndex.end()) {
            std::cerr << "[ERROR] Undefined function: " << q.arg1 << "\n";
            return;
        }

        pc_ = it->second + 1; // 跳转到函数标签下一条指令

        // 传递参数到函数内部
        for (int i = num_args - 1; i >= 0; --i) {
            memory_["arg" + std::to_string(i)] = paramStack_.back();
            paramStack_.pop_back();
        }
    }

    else if (q.op == "return") {
        Value ret_val = memory_.count(q.arg1) ? memory_[q.arg1] : asInt(q.arg1);

        if (callStack_.empty()) {
            std::cerr << "[ERROR] Return outside function!\n";
            return;
        }

        CallFrame frame = callStack_.top();
        callStack_.pop();

        memory_ = frame.locals;  // 恢复调用函数前的内存环境

        // 将返回值存入指定变量中（如果call指令有返回值）
        if (!quads[frame.return_pc - 1].result.empty()) {
            memory_[quads[frame.return_pc - 1].result] = ret_val;
        }

        pc_ = frame.return_pc;  // 返回调用位置继续执行
    }





    else {
        std::cerr << "[ERROR] Unknown op: " << q.op << "\n";
    }
}



void IRInterpreter::runUntil(const std::vector<Quad>& quads, int breakLine) {
    // 建立 label -> index 映射
    std::unordered_map<std::string, int> labelToIndex;
    for (int i = 0; i < quads.size(); ++i) {
        if (quads[i].op == "label") {
            labelToIndex[quads[i].result] = i;
        }
    }

    int pc = 0;
    while (pc < quads.size()) {
        const auto& q = quads[pc];
        std::cout << "[PC " << pc << "] line = " << q.loc.line << ", breakLine = " << breakLine << "\n";
        if (q.loc.line >= breakLine) break;

        std::cout << "[EXEC] " << q.op << " " << q.arg1 << " " << q.arg2 << " -> " << q.result << "\n";

        if (!q.result.empty() && q.type) {
            types_[q.result] = q.type;
        }

        if (q.op == "=") {
            if (q.arg1.empty()) {
                memory_.emplace(q.result, 0);
            } else if (q.arg1[0] == '"') {
                memory_[q.result] = asStr(q.arg1);
            } else if (isdigit(q.arg1[0]) || (q.arg1[0] == '-' && isdigit(q.arg1[1]))) {
                memory_[q.result] = std::stoi(q.arg1);
            } else {
                memory_[q.result] = memory_.count(q.arg1) ? memory_[q.arg1] : 0;
            }
        }
        else if (q.op == "+" || q.op == "-" || q.op == "*" || q.op == "/" ||
                 q.op == "<" || q.op == ">" || q.op == "==" || q.op == "!=" ||
                 q.op == "&&" || q.op == "||") {
            Value valA = memory_.count(q.arg1) ? memory_[q.arg1] : asInt(q.arg1);
            Value valB = memory_.count(q.arg2) ? memory_[q.arg2] : asInt(q.arg2);
            memory_[q.result] = evalBinary(q.op, valA, valB);
        }
        else if (q.op == "!") {
            int val = asInt(q.arg1);
            memory_[q.result] = !val;
        }
        else if (q.op == "ifFalse") {
            int cond = memory_.count(q.arg1) ? std::get<int>(memory_[q.arg1]) : asInt(q.arg1);
            if (!cond) {
                pc = labelToIndex[q.result];
                continue;
            }
        }
        else if (q.op == "ifTrue") {
            int cond = memory_.count(q.arg1) ? std::get<int>(memory_[q.arg1]) : asInt(q.arg1);
            if (cond) {
                pc = labelToIndex[q.result];
                continue;
            }
        }

        else if (q.op == "goto") {
            std::cout << "[DEBUG] Handling goto to " << q.result << "\n";
            auto it = labelToIndex.find(q.result);
            if (it != labelToIndex.end()) {
                pc = it->second;
                continue;
            } else {
                std::cerr << "[ERROR] Unknown label: " << q.result << "\n";
            }
        }


        else if (q.op == "label") {
            // do nothing
        }
        else if (q.op == "param" || q.op == "call" || q.op == "return") {
            // 留给下一阶段实现函数调用
        }

        pc++;  // 正常执行下一条
    }

    dumpVariables(breakLine);
}


void IRInterpreter::dumpVariables(int breakLine) {
    std::cout << "\n---- Variables before line " << breakLine << " ----\n";
    for (const auto& [name, val] : memory_) {
        // 忽略以 "t" 开头的临时变量（比如 t1, t2）
        if (!name.empty() && name[0] == 't' && isdigit(name[1])) continue;

        std::cout << name << " = ";
        if (std::holds_alternative<int>(val)) {
            std::cout << std::get<int>(val);
        } else if (std::holds_alternative<std::string>(val)) {
            std::cout << "\"" << std::get<std::string>(val) << "\"";
        }

        if (types_.count(name)) {
            std::cout << "  (type = " << types_[name]->toString() << ")";
        }

        std::cout << "\n";
    }
}

