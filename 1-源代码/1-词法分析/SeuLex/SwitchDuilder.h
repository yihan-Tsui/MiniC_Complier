#pragma once

#include <string>
#include <vector>
#include <set>
#include <map>

struct SwitchBuilder {
    static std::string stdBuild(std::string var_name, std::map<std::string, std::set<int>> case_list, std::string defaultCase = "error(\"\");") {
        using std::string;
        using std::to_string;

        // 定义缩进级别
        const string indent1 = "    "; // 一级缩进
        const string indent2 = "        "; // 二级缩进

        // 开始部分
        string begin = "switch(" + var_name + ") {\n";

        // 结束部分
        string end = indent1 + "default: {\n" +
                     indent2 + defaultCase + "\n" +
                     indent1 + "}\n"
                               "}";

        // 中间部分
        string middle = "";

        for (const auto& p_ : case_list) {
            // 添加 case 标签
            string pbegin = "";
            for (int caseIdx : p_.second) {
                pbegin += indent1 + "case " + to_string(caseIdx) + ":\n";
            }
            pbegin += indent1 + "{\n"; // 打开 case 块

            // 添加 case 内容
            string pend = indent2 + p_.first + "\n" +
                          indent1 + "    break;\n" +
                          indent1 + "}\n"; // 关闭 case 块

            middle += pbegin + pend;
        }

        // 拼接完整的 switch 语句
        return begin + middle + end;
    }
};

