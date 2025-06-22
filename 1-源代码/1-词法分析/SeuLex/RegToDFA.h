#pragma once

#include <string>

#include "NFA.h"
#include "DFA.h"

#include <fstream>

struct RegToDFA{

	int nodes;

	std::map<int, std::string> flag_map;

	int flagCnt = 10;

	NFANode * startNode;
	char reg[65536];
	
	void init() {
		for (int i = 9; i < 127; ++i) {
			if (true/*i != '#'*/) {

				allowed_chars.push_back(i);
			}
		}
		memset(FA_flag, 0, sizeof FA_flag);
	}

	void appendRegex(std::string regStr, std::string info) {
		strcpy(reg, regStr.c_str());
		if (flag_map.empty()) {
			parseFirstReg(reg, startNode, flagCnt);
		}else {
			parseReg(reg, startNode, flagCnt);
		}
		flag_map[flagCnt] = info;
		++flagCnt;
	}

	void generate() {
		int states = NFAtoDFA(startNode);
		DFAMinimizer.init(states);
		DFAMinimizer.deal();
		nodes = DFAMinimizer.generate();
	}




    void show(const std::string& outputFilePath = "dfa_output.txt") {
        // 打开文件流，准备写入
        std::ofstream outFile(outputFilePath);
        if (!outFile.is_open()) {
            std::cerr << "Failed to open file: " << outputFilePath << std::endl;
            return;
        }


        for (int i = 0; i < nodes; ++i) {
            // 打印状态编号
            outFile << "State " << i << ": ";

            // 打印标志值
            outFile << "[Flag = " << minDFA[i].flag << "] ";
            if (minDFA[i].flag != 0) {
                outFile << "(Accepting State - Semantic Action: " << flag_map[minDFA[i].flag] << ") ";
            } else {
                outFile << "(Non-Accepting State) ";
            }

            // 打印转移关系
            outFile << "Transitions: ";
            for (auto &p_ : minDFA[i].ptrs) {
                char inputChar = p_.first;
                int nextState = p_.second->id;

                // 如果输入字符是不可打印字符，用 ASCII 码表示
                if (inputChar < 32 || inputChar > 126) {
                    outFile << "<ASCII " << static_cast<int>(inputChar) << ", State " << nextState << "> ";
                } else {
                    outFile << "<'" << inputChar << "', State " << nextState << "> ";
                }
            }

            outFile << std::endl;
        }

        outFile << "End of Minimized DFA" << std::endl;

        // 关闭文件流
        outFile.close();


        std::cout << "Minimized DFA has been saved to file: " << outputFilePath << std::endl;
    }

};
