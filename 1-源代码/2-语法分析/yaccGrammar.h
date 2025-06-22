#pragma once

#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>

//符号名索引    
std::map<std::string, int> map_idname_idx;
//索引符号名
std::map<int, std::string> map_idx_idname;

//终结符索引集
std::set<int> terminators;

//将符号名转换为索引
int idnameToIdx(std::string name) {
	
	assert(map_idname_idx.find(name)!= map_idname_idx.end());
	return map_idname_idx[name];
}
//将索引转换为符号名
std::string idxToIdname(int idx) {
	assert(map_idx_idname.find(idx)!= map_idx_idname.end());
	return map_idx_idname[idx];
}

//添加新符号，输入符号索引、名称和是否为终结符
void appendNewSymbol(int idx, std::string name, bool isTerminator) {

	map_idname_idx.insert({ name, idx });
	map_idx_idname.insert({ idx, name });
	//如果是终结符，则同时加入到终结符集合中
    if (isTerminator) {
		terminators.insert(idx);
	}
}

//判断是否为终结符
bool isTerminator(int idx) {
    //如果终结符索引集包含该索引，则返回true
	return terminators.count(idx);
}
bool isTerminator(std::string str) {
	int idx = idnameToIdx(str);
	return isTerminator(idx);
}

//产生式，左部和右部用索引表示
typedef std::pair< int, std::vector<int> > Producer;
std::vector<Producer> producers;

//打印所有产生式
void printProducers(int(*print_)(const char *, ...)) {
    for (auto & producer: producers){
        std::string left = idxToIdname(producer.first);
        print_("%s : => ", left.c_str());
        for (int item : producer.second) {
            print_(" %s ", idxToIdname(item).c_str());
        }
        print_("\n");
    }
}

//将所有合格的终结符（符号名首字母是英文字母的终结符？）定义写入到文件
void writeTab(FILE * file, int(*print_)(FILE *, const char *, ...))
{
    //先写入空白符宏定义
    //#define WHITESPACE 0  
    // /*sp */ 
	print_(file, "#define WHITESPACE 0  \n /*sp */ \n\n");
	for (auto & p_ : map_idname_idx)
    {
		if (!isTerminator(p_.second))
            continue;
		if ((p_.first[0] <'a' || p_.first[0]>'z') &&
			(p_.first[0] <'A' || p_.first[0]>'Z'))
            continue;
        //符号名首字母是英文字母的终结符 写入文件，如#define NUM 6

		print_(file, "#define %s %s\n", p_.first.c_str(), std::to_string(p_.second).c_str());
	}
}

extern std::map<int, std::set<int> > firsts;

struct LRItem {
	int positionInt = 0;     //点的位置  
	int grammarInt = -1;     //产生式标号
	int predictiveSymbol;   //预测符
	//``operator<重载
	bool operator < (const LRItem & t) const {
		if (grammarInt == t.grammarInt) {
			if (positionInt == t.positionInt) return predictiveSymbol < t.predictiveSymbol;
			return positionInt < t.positionInt;
		}
		return grammarInt < t.grammarInt;
	}
};

struct LRState {
	int numberInt = -1;      //状态号                   
	std::map<int, int> edgesMap;         //<读入的符号的编号, 状态号>，即状态转移
	std::set<LRItem> LRItemsSet;         //该状态包含的所有LR项

	//状态内部扩展（50）：当前LR状态的扩展，只要点后是非终结符，则讲该非终结符相关的产生式加入到该LR状态中
    void extend() {

		using namespace std;
        //将当前状态的所有LR项加入队列
		auto & s = *this;

		queue<LRItem> que;
		for (auto & item : s.LRItemsSet) {
			que.push(item);
		}
        //处理队列中的每个弹出的LR项
		while (!que.empty()) {
			auto item = que.front();
			que.pop();
            //获取产生式
			auto & producer = producers[item.grammarInt];
			int itemLen = producer.second.size();
			//1、如果点在末尾，则跳过
            if (item.positionInt >= itemLen) continue; 
			//2、如果点后是终结符，则跳过
            if (isTerminator(producer.second[item.positionInt])) continue;
			//3、如果点后是非终结符
            //需要将该非终结符的所有产生式加入到状态集中
            //并由此产生式计算即将push进的产生式的展望符号
            int newLeft = producer.second[item.positionInt];
			

            //Ⅰ由此产生式计算即将push进的产生式的展望符号
            set<int> nexts;
			bool flag = true;
            //遍历点后所有符号
			for (int j = item.positionInt + 1; j < itemLen; ++j) {
				bool noEpsilon = true;
                //获取该符号的first集
				auto & fi = firsts[producer.second[j]];
				//如果点后有一个符号，其first集没有epsilon，跳出循环
                for (int c : fi) {
					if (c == 0) noEpsilon = false; 
					else {
						nexts.insert(c);
					}
				}
				if (noEpsilon) {
					flag = false;
					break;
				}
			}
            //如果点后所有符号的first集都有epsilon
			if (flag) {
				nexts.insert(item.predictiveSymbol);
			}
            //Ⅱ将该非终结符的所有产生式加入到状态集中
			for (int i = 0; i < producers.size(); ++i) {
				//如果产生式左符号不是该非终结符，则跳过
                if (producers[i].first != newLeft) continue;
                //遍历展望符号
				for (auto c : nexts) {
					LRItem newItem;
					newItem.grammarInt = i;
					newItem.positionInt = 0;
					newItem.predictiveSymbol = c;
					if (s.LRItemsSet.count(newItem) == 0) {
						s.LRItemsSet.insert(newItem);
						que.push(newItem);
					}
				}
			}

		}
	}

};