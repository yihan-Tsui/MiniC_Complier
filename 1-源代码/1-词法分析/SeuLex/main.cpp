#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstring>

#include <filesystem>

#include "yylParser.h"  // 解析规则文件的头文件
#include "RegFilter.h"  // 正则表达式过滤器头文件
#include "RegToDFA.h"   // 正则表达式到 DFA 的转换头文件
#include "SwitchDuilder.h"  // 生成 switch-case 语句的工具头文件
#include "lexSource.h"  // 词法分析器源代码生成头文件


#include <string>
#include <sstream>
using namespace std;

RegToDFA ctrl;  // 创建一个 RegToDFA 对象，用于管理正则表达式到 DFA 的转换




int main()
{
    YylParser yyl("../../rules/littlec.l");

    yyl.show();

    // 获取规则文件中的宏定义，并对每个宏定义的值进行特殊字符过滤
    std::map<std::string, std::string> ruleMap = yyl.define_rules;



    for (auto & p_ : ruleMap)
    {
        p_.second = RegFilter::spcharFilter(p_.second);  // 过滤转义字符（如 \n, \t 等）
    }


    // 初始化 DFA 控制器，设置允许的字符集（ASCII 9 到 126）
    ctrl.init();

    // 获取规则文件中的正则表达式规则，并进行处理
    auto regs = yyl.regex_rules;
    for (auto & p_ : regs)
    {
        if (*p_.first.begin() == '\"' && *p_.first.rbegin() == '\"')
        {
            // 如果正则表达式是字符串字面量，调用 quoteFilter 处理
            p_.first = RegFilter::quoteFilter(p_.first);
        }
        else
        {
            // 否则，调用 totalFilter 进行全面过滤（包括宏替换、字符范围扩展等）
            p_.first = RegFilter::totalFilter(p_.first, ruleMap);
        }
    }

    // 将处理后的正则表达式逐个添加到 DFA 构造器中
    for (auto & p_ : regs)
    {
        ctrl.appendRegex(p_.first, p_.second);  // 添加正则表达式及其对应的语义动作
    }

    //system("pause");  // 暂停程序，等待用户按键继续

    // 生成最小化 DFA
    ctrl.generate();  // 包括 NFA 转换为 DFA 和 DFA 最小化

    // 打印最小化后的 DFA（可选）
    ctrl.show();



    //system("pause");  // 暂停程序，等待用户按键继续

    // 获取最小化 DFA 的状态数
    int cnt = ctrl.nodes;

    // 生成 DFA 执行函数（DFAExec）
    std::map<std::string, std::set<int > > case_list;
    for (int i = 0; i < cnt; ++i) {
        int f = minDFA[i].flag;  // 获取当前状态的标志值
        if (f != 0) {  // 如果状态有标志值，将其添加到 case_list
            string s = ctrl.flag_map[f];  // 根据标志值获取对应的语义动作
            case_list[s].insert(i);
        }
    }
    // 使用 SwitchBuilder 生成 switch-case 语句
    string DFAExecuter =
            SwitchBuilder::stdBuild("DFAState", case_list, "\n error(\"unexpected word\");\n") + "\n return WHITESPACE; \n";  // 默认返回空白字符

    string Func_DFAExec =
            "int DFAExec(void){\n " + DFAExecuter + "\n} ";

    // 生成 DFA 尝试函数（DFATry）
    case_list.clear();
    for (int i = 0; i < cnt; ++i) {
        int f = minDFA[i].flag;  // 获取当前状态的标志值
        if (f != 0) {  // 如果状态有标志值，将其添加到 case_list
            case_list["{return 1;}"].insert(i);
        }
    }
    string Func_DFATry = "int DFATry(void){ " + SwitchBuilder::stdBuild("DFAState", case_list, "return 0;") + "} ";

    // 生成 DFA 推进函数（DFAPush）
    case_list.clear();
    for (int i = 0; i < cnt; ++i) {
        auto & table = minDFA[i].ptrs;  // 获取当前状态的转移表
        std::map<std::string, std::set<int > > local_list;
        for (auto p_ : table) {
            int next = p_.second->id;  // 获取下一个状态的 ID
            string order = "{ DFAState = " + to_string(next) + "; }";  // 生成状态转移语句
            local_list[order].insert(p_.first);  // 根据输入字符分组
        }
        string content = "{ " + SwitchBuilder::stdBuild("c", local_list, "{return 1;}") + " }";
        case_list[content].insert(i);
    }
    string DFA_pusher = SwitchBuilder::stdBuild("DFAState", case_list, "return 0;") +" return 0; ";
    string Func_DFAPush = "int DFAPush(char c){ " + DFA_pusher + "} ";

    // 打印生成的 DFA 执行函数和推进函数
    //printf("%s\n%s\n", Func_DFAExec.c_str(), Func_DFAPush.c_str());

    //system("pause");  // 暂停程序，等待用户按键继续

    // 将用户代码部分与自动生成的 DFA 函数组合
    lexSource::program1 = yyl.program1;  // 用户代码部分 1
    lexSource::program2 = yyl.program2;  // 用户代码部分 2
    lexSource::auto_program = Func_DFAExec + "\n" + Func_DFATry + "\n" + Func_DFAPush + "\n";

    // 生成完整的词法分析器源代码文件（lex.yy.c）
    yieldLexYyC("../../Lex/lex.yy.c");



}
