#pragma once
#include <map>
#include "yaccParser.h"
#include "yaccGrammar.h"
using namespace std;

struct LR1TableUnit {
    int type;//0：规约，1：移进
    int data;//产生式或者状态编号
};

// lR1表的行，关于map,int为输入的符号编号，LR1TableUnit为输入该符号后的action
using LR1TableRow = std::map<int, LR1TableUnit>;

struct LR1Table {
    vector<LR1TableRow> table;

    LR1Table() = default;
    LR1Table(const LRDFA &dfa){
        //遍历所有状态，每个状态创建表的一行
        for (const LRState & src : dfa.statesVec) {
			LR1TableRow row;
            //遍历所有边
            for (auto & p_ : src.edgesMap) {
				int input = p_.first;
				LR1TableUnit e = { 1, p_.second };
				row.insert({ input, e });
			}

            //遍历所有LR项，确定是移进或者规约
			for (auto & item : src.LRItemsSet) {
				if (item.positionInt != producers[item.grammarInt].second.size()) continue;
				//规约规约冲突
                //编号优先级人为解决 reduce/reduce 冲突
                //优先级为：产生式编号
                //1、编号小的优先
                //2、编号相同，则先出现的优先
                int gid = item.grammarInt;
				auto it = row.find(item.predictiveSymbol); //如果找到规约规约冲突
				//如果没找到 或 已经有一条 reduce 操作，但是它的产生式编号比我大 ， 则替换
                if (it == row.end() || (it->second.type == 0 && gid < it->second.data)) {
					row[item.predictiveSymbol] = { 0, gid } ;
				}
			}
			table.push_back(std::move(row));
		}
    }

    // LALR 分析表“翻译”成可编译的 C/C++ 代码
    //运行时不再通过查 map
    //通过两个嵌套的 switch 语句直接返回动作值
    string print_lr1(string state_name, string token_name) {
		
        using std::to_string;

		//外层switch，结合case跳转到对应的状态
        std::string outer_switch = "switch (" + state_name + ")	{";
		//外层default
        std::string outer_default = "default: return 65536; }";
		//累计外层switch内包含的内容
        std::string inner = "";
		for (int i = 0; i < table.size(); ++i) {
			//内层switch，对应某一个状态下，读入不同值后
            std::string inner_switch = "case " + to_string(i) + " : switch (" + token_name + ")	{";
			std::string inner_after = "default: return 65536; }";
			//用 tmp 来累加本状态下每个符号对应的 case
            std::string tmp = "";
			//遍历该状态下（该行内）所有lr1表项内容
            for (auto p_ : table[i]) {
				int to;
                //归约：编码成负数 -1 - 产生式号
				if (p_.second.type == 0) {
					to = -1 - p_.second.data;
				}
                //移进或 GOTO：直接用目标状态号
                else {
					to = p_.second.data;
				}
                //拼出这一条 case 语句
                //p_.first 是符号编号，to 是动作编码
				tmp += "case " + to_string(p_.first) + " :{return " + to_string(to) + ";}";
			}
			inner += inner_switch + tmp + inner_after;
		}
		return outer_switch + inner + outer_default;
	}

    LR1TableUnit &operator()(int row, int col) {
        return table[row][col];
    }
};




