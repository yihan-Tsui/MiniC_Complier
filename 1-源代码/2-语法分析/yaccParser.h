#pragma once

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<map>
#include<vector>

#include "yaccGrammar.h"
using namespace std;

struct YaccParser {
    // 构造函数
    YaccParser() = default;

	YaccParser(std::string filename) {
		Parsering(filename);
	}


    vector<string> terminal;
	string start;

    using producer = pair < string, vector<string> >;
    vector<producer> producer_list;

    string program;

    // Parsering 处理
    void Parsering(std::string filename) {
		std::ifstream ifile;
		ifile.open(filename, std::ios::in);
		readFromStream(ifile);
		ifile.close();
		mapping_terminal_nonterminal();
		producers_after_mapping();  
	}

    void readFromStream(std::istream & ifile) {
    // 读取.y文件
    // 文件分为三个部分：
    // 1. 声明部分（%token等）
    // 2. 产生式部分（%%之间的内容）
    // 3. 程序部分（最后一个%%之后）
    
	string line;
    int section = 0;
    while (getline(ifile, line)) {
        if(line == "") continue;  
        if (line == "%%") {
            section++;
            if (section == 1) {
                // 读取产生式部分
                producerParsing(ifile); //producerParsing 会读取第二个 %%
                section++;
                }
            continue;
        }
        
        
        switch (section) {
            case 0:
                // 读取声明部分
                section_declartion(line);
                break;
            case 2:
                // 读取代码部分
                program += line + "\n";
                break;
            default:
                throw "";
        }   
    }
    }
    // 读取声明部分

    void section_declartion(std::string ln) {
		std::string left = "", right = "";
		int len = ln.length();
		int i = 0;
		bool flag = 1;
		//在未读到%%之前，读取声明部分
        if (ln[i] == '%'&& ln[i + 1] != '%'){
			++i;//跳过%
			while (i < len && ln[i] == ' ') ++i;// || ln[i] == '\t')
			//读取声明部分
            while (i < len && !(ln[i] == ' ')) {
				left += ln[i];
				++i;
			}

			while (i < len && ln[i] == ' ')	i++;
            // 读取token内融
			if (left == "token") {
				for (; i < len; i++){
					if (ln[i] != ' ') {
						right += ln[i];
						if (i == len - 1)

							terminal.push_back(right);
					}
					else {
						terminal.push_back(right);
						right = "";
					}
				}
			}else if (left=="start"){
				start = "";
				while (i < len) start.push_back(ln[i++]);
			}else {
				throw "";
			}

		}
	}

    void producerParsing(std::istream & ifile) {

		//读取产生式
		std::string left;
		do { ifile >> left; } while (left == ""); //跳过空格
		
		//直到读到第二个%%之前
        while (left != "%%") {
			std::string str;
			ifile >> str;
			if (str != ":" && str != "|") throw "";
			readProducerRight(ifile, left);
			do { ifile >> left; } while (left == "");
		}
	}
    
    void readProducerRight(std::istream & ifile, std::string left) {
		std::string str;
		do {
			ifile >> str;
			vector<std::string> curRight;
			while (str != "|" && str != ";") {
				curRight.push_back(str);
				ifile >> str;
			}
			producer_list.push_back({ left, curRight });
		} while (str != ";");
	}

    //辅助函数
    static bool vector_contain(vector<string> str, string stt) {
		for (int i = 0; i < str.size(); i++) {
			if (str[i] == stt) return true;
		}
		return false;
	}

    // 映射终结符和非终结符
    void mapping_terminal_nonterminal(){
		
        // 映射终结符
        vector<string> Terminal;
        vector<int> Terminal_idxs;
        int terminal_idx = 300;
        for (int i = 0; i < terminal.size(); ++i) {
			Terminal.push_back(terminal[i]);
			Terminal_idxs.push_back(terminal_idx++);
		}

        // 映射非终结符
        vector<string> NonTerminal;
        vector<int> NonTerminal_idxs;
        int nonterminal_idx = 999;

        NonTerminal.push_back("__PROGRAM__");
        NonTerminal_idxs.push_back(nonterminal_idx++);
        NonTerminal.push_back(start);
        NonTerminal_idxs.push_back(nonterminal_idx++);

        //处理产生式里的终结符和非终结符
        for (auto iter = producer_list.begin(); iter != producer_list.end(); iter++) {

			//对每个产生式右部的符号进行处理
            for (auto k : iter->second) {
				//''引号内的符号必为终结符
                if (k[0] == '\'') {
					//如果已经在终结符列表中，则跳过
                    if (vector_contain(Terminal, k)) continue;
					//否则，将该终结符加入终结符列表，并分配一个索引
                    else {
						Terminal.push_back(k);
						Terminal_idxs.push_back(k[1]);
					}
				}
				//非''的符号且不在终结符列表中，则必为非终结符
				else {
					if (vector_contain(NonTerminal, k) || vector_contain(Terminal, k)) continue;
					//
                    else {
						NonTerminal.push_back(k);
						NonTerminal_idxs.push_back(nonterminal_idx++);
					}}}
			// 再处理左部
			const std::string &lhs = iter->first;             // 整个左部符号名
			if (!vector_contain(NonTerminal, lhs)             // 如果既不在非终结符列表
			&& !vector_contain(Terminal, lhs) ) {           // 又不在终结符列表
				NonTerminal.push_back(lhs);                  // 就把它当作新的非终结符
				NonTerminal_idxs.push_back(nonterminal_idx++);
			}


			}
				
		

        // 将终结符和非终结符加入符号表
        for (int i = 0; i < Terminal_idxs.size(); ++i) {
			appendNewSymbol(Terminal_idxs[i], Terminal[i], true);
		}
		for (int i = 0; i < NonTerminal_idxs.size(); ++i) {
			appendNewSymbol(NonTerminal_idxs[i], NonTerminal[i], false);
		}


    }

    //映射后的产生式，产生式中终结符或非终结符以数字形式表示
    void producers_after_mapping(){

        producers.push_back({ idnameToIdx("__PROGRAM__"), {idnameToIdx(start)} });
		for (auto & producer : producer_list) {
			int left = idnameToIdx(producer.first);
			vector<int> v;
			for (auto & str : producer.second) {
				v.push_back(idnameToIdx(str));
			}
			producers.push_back({ left, v });
		}
    }

    //``将生成的语法分析表写入文件
    void writeTabs(std::string filename)
    {
		FILE * tabFile = fopen(filename.c_str(), "w");
		writeTab(tabFile, fprintf);
		fclose(tabFile);
	}
};

struct  initWrite{

	static string init_write() {
		string content = "";
		//生成符号名称的初始化代码
		for (auto p_ : map_idx_idname) {
			int idx = p_.first;
			string name = p_.second;
			content += "strcpy(idx_token[" + to_string(idx) + "], \"" + name + "\");";
		}
		//生成产生式初始化代码
		for (int t = 0; t < producers.size(); ++t) {
			//获取产生式
			auto & p_ = producers[t];
			//获取产生式左部符号编号
			int idx = p_.first;
			//获取产生式右部符号编号
			auto & vec = p_.second;
			//获取产生式右部符号个数
			int l = vec.size();
			//生成产生式初始化代码
			vector<int> v(2);
			//产生式右部符号个数
			v[0] = l;
			//产生式左部符号编号
			v[1] = idx;
			//生成产生式右部符号编号
			for (int i = 0; i < l; ++i) {
				v.push_back(vec[i]);
			}
			//生成产生式初始化代码
			for (int i = 0; i < l + 2; ++i) {
				content += "producers[" + to_string(t) + "][" + to_string(i) + "]=" + to_string(v[i]) + ";";
			}
		}
		return content;
	}

};

map<int, set<int> > firsts;

// ``计算first集
void initFirsts() {

	// 初始化终结符first集，其first值为自己
    for (auto & p_ : producers) {
		for (int s : p_.second) {
			if (isTerminator(s)) firsts[s].insert(s);
		}
	}

    // 计算非终结符first集
	bool flag = true; // 标志位，判断是否需要下一轮迭代
	while (flag) {
		flag = false;
		for (auto & p_ : producers) {
			int s = p_.first; // 产生式左部，非终结符
			if (isTerminator(s)) continue;
			bool hasEpsilon = true; //标记是否所有符号都能推导出空串
			// 遍历产生式右部的每个符号，获取当前符号的First集
			for (int item : p_.second) {
				auto & thisSet = firsts[item];
				for (int c : thisSet) {
					if (c == 0) continue;
					//把未加入的符号加入first集
					if (firsts[s].count(c) == 0) {
						flag = true;
						firsts[s].insert(c);
					}
				}
				//若不含0，则不需要继续看下一个符号
				if (thisSet.count(0) == 0) {
					hasEpsilon = false;
					break;
				}
			}
			if (hasEpsilon && firsts[s].count(0) == 0) {
				flag = true;
				firsts[s].insert(0);
			}
		}
	}
}


struct LRDFA {
    //创建起始状态0
	int startState = 0;
    //用于存储所有状态
	std::vector< LRState > statesVec;     

	LRDFA() {
		using namespace std;
		auto & dfa = *this;

        //创建起始产生式，编号为0号产生式
		LRItem item0;
		item0.grammarInt = 0;
		item0.predictiveSymbol = '$';
		
        //创建起始状态，编号为0，并把起始产生式加入
        LRState state0;
        state0.numberInt = 0;
		state0.LRItemsSet.insert(item0);

        //计算first集
		initFirsts();

        //扩展起始状态
		state0.extend();

        //将起始状态加入DFA
		dfa.startState = 0;
		dfa.statesVec.push_back(state0);

        //使用队列进行BFS状态间扩展
		queue<int> que;
		que.push(0);
		while (!que.empty()) {
            //从队列中取出一个状态
			int idx = que.front();
			que.pop();
            //获取当前弹出的状态
			auto & start = dfa.statesVec[idx];
			map<int, LRState> newStates;
            //遍历当前状态的每一个 LR 项
			for (const LRItem & item : start.LRItemsSet) {
				auto & producer = producers[item.grammarInt];
                //1、如果.已到最后，跳过
				if (item.positionInt >= producer.second.size()) continue;
				//2、如果.未到最后，则获得.后下一个符号
                int c = producer.second[item.positionInt];
				//创建新的LR项，该LR项将.后移一位
                LRItem newItem = item;
				++newItem.positionInt;
				//将新的LR项加入新的状态
				newStates[c].LRItemsSet.insert(newItem);
			}
            //对每个新状态扩展
			for (auto & p_ : newStates) {
				p_.second.extend();
			}
			for (auto & p_ : newStates) {
				auto & start = dfa.statesVec[idx];                  // push changes the '&'. Must reget.
				bool flag = true;
                // 检查是否与现有状态相同
				for (auto & other : dfa.statesVec) {
                    // 如果状态大小不同，则跳过
					if (p_.second.LRItemsSet.size() != other.LRItemsSet.size()) continue;
					bool same = true;
					for (auto & item : p_.second.LRItemsSet) {
                        // 如果other中不包含item，则跳过
						if (other.LRItemsSet.count(item) == 0) {
							same = false;
							break;
						}
					}
                    //``如果找到相同状态，就不加入新状态，而是加一条边指过去
					if (same) {
						start.edgesMap[p_.first] = other.numberInt;
						flag = false;
						break;
					}
				}
                //如果未找到相同状态，则加入新状态
				if (flag) {
					int c = p_.first;
					int idx = dfa.statesVec.size();
					
					start.edgesMap[c] = idx;
					p_.second.numberInt = idx;
					dfa.statesVec.push_back(p_.second);
					que.push(idx);
				}
			}

		}

	}
	
	void lrDFA_to_lalrDFA(){

		LRDFA lalrdfa;

		auto & dfa = *this;
		//核心项，记录产生式部分及对应的一个或多个状态编号
		vector<pair<set<pair<int, int>>, set<int>>> core;

		//遍历所有lrdfa状态
		for (auto &state : dfa.statesVec){
			set<pair<int, int>> stateCore;
			for (auto &lritem : state.LRItemsSet){
				//把state中的每个item的产生式和点位置记录下来加入core
				stateCore.insert(make_pair(lritem.grammarInt, lritem.positionInt));
			}
			//判断该状态的core是否已存在于core中
			bool exist = false;
			for (auto &c : core){
				//当前状态的core已存在于core中，则将当前状态的标号加入该core项中
				if (c.first == stateCore)
				{
					exist = true;
					c.second.insert(state.numberInt);}
			}
			if (!exist)
			{
				//当前状态的core不存在于core中，则将该状态作为一个新的core
				//首先加入自己
				set<int> newStateNum;
				newStateNum.insert(state.numberInt);
				core.push_back(make_pair(stateCore, newStateNum));
			}
		}


		//建立lalrdfa
		//旧、新状态标号映射表
		map<int, int> indexMap;
		int count = 0;

		for (auto &c : core){
			LRState newState;
			//更新同心集状态的状态号
			newState.numberInt = count;
			count++;

			//更新同心集状态的动作，将当前core的同心集里的第一个状态的动作作为新状态的动作
        	//将这个边映射表赋给新状态
			newState.edgesMap = dfa.statesVec[*c.second.begin()].edgesMap;
			
			//将旧状态标号与新状态标号建立映射
			//遍历core.second中的每个状态索引，这些状态具有相同的核心项
			for (auto &state : c.second){
				//利用每一个state里的item更新同心集状态里lritem
				for (auto &lritem : dfa.statesVec[state].LRItemsSet)
					newState.LRItemsSet.insert(lritem);
				//将同心集里的状态标号映射为新的状态标号
				indexMap.emplace(state, newState.numberInt);
			}
			//将新状态加入lalrdfa
			lalrdfa.statesVec.push_back(newState);
		}

	}
	/*
    //LR1->LALR，状态合并
    void generateLALR() {
		
        int n = statesVec.size();
		//stateBelongs数组，表示每个状态所属的主状态
        int stateBelongs[65536];
        for (int i = 0; i < n; ++i) stateBelongs[i] = -1;

        // 打印开始信息
        printf("[INFO] Starting LALR state merging... Total states: %d\n", n);
        //遍历所有状态
        for (int i = 0; i < n; ++i) {
            //如果已经处理过，则跳过
            if (stateBelongs[i] != -1) continue;
            //将当前状态标记为主状态
            stateBelongs[i] = i;

            // 打印当前主状态
            printf("[DEBUG] Merging into state %d\n", i);
            //比较其他状态
            for (int j = i + 1; j < n; ++j) {
                //如果已经处理过，则跳过
                if (stateBelongs[j] != -1) continue;
                bool isSame = true;

                // 检查核心项是否一致（忽略 lookahead）
                for (auto & item1 : statesVec[i].LRItemsSet) {
                    bool found = false;
                    for (auto & item2 : statesVec[j].LRItemsSet) {
                        //如果两个状态的LR项相同，则跳过
                        if (item1.grammarInt == item2.grammarInt && item1.positionInt == item2.positionInt) {
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        isSame = false;
                        break;
                    }
                }

                for (auto & item1 : statesVec[j].LRItemsSet) {
                    bool found = false;
                    for (auto & item2 : statesVec[i].LRItemsSet) {
                        //如果两个状态的LR项相同，则跳过
                        if (item1.grammarInt == item2.grammarInt && item1.positionInt == item2.positionInt) {
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        isSame = false;
                        break;
                    }
                }

                if (isSame) {
                    stateBelongs[j] = i;
                }
            }
        }

        // 打印合并完成信息
        int cnt = 0;
        for (int i = 0; i < n; ++i) {
            if (stateBelongs[i] == i) cnt++;
        }
        printf("[INFO] LALR merge complete. Reduced from %d to %d states.\n", n, cnt);
    }
*/
	


};
