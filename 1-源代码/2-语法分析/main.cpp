#define _CRT_SECURE_NO_WARNINGS

#include "yaccParser.h"
#include "yaccGrammar.h"
#include "LR1Table.h"
#include "yaccSource.h"

using namespace std;

int main() {
    
    YaccParser parser("./c99.y");
    
    //printProducers(printf);

    //写入 token 定义表,用于 Lex 词法分析器引用符号编号
    parser.writeTabs("./y.tab.h");
    
    //构造 LALR 自动机
    LRDFA lalrdfa;
    lalrdfa.lrDFA_to_lalrDFA();
    //构造 LALR 分析表
    LR1Table lr1table(lalrdfa);

    //输出文件重定向到 y.tab.c
    freopen("./y.tab.c", "w", stdout);

    printf("%s\n", yacc_program.c_str());
    printf("void init_producers() { %s }\n", initWrite::init_write().c_str());
    //打印GoTo表
    printf("int GoTo(int state, int c) { %s }\n", lr1table.print_lr1("state", "c").c_str());
    return 0;
}
