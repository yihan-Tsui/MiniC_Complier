#pragma once

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<map>
#include<vector>

struct YylParser{

    std::string program1;
    std::map<std::string, std::string> define_rules;
    std::vector<std::pair<std::string, std::string> > regex_rules;
    std::string program2;

    std::pair<std::string, std::string> lnToPair(std::string ln)
    {
        std::string left = "", right = "";
        int len = ln.length();
        int i = 0;
        while (i<len && (ln[i] == ' ' || ln[i] == '\t'))
            ++i;
        while (i<len && !(ln[i] == ' ' || ln[i] == '\t'))
        {
            left += ln[i];
            ++i;
        }
        while (i<len && (ln[i] == ' ' || ln[i] == '\t'))
            ++i;
        while (i < len) right += ln[i++];
        return{ left, right };
    }

    void readFromStream(std::istream & ifile)
    {
        using namespace std;

        string ln;                // ln <==> line
        int step = 0;
        bool inDef = false;
        while (getline(ifile, ln))
        {
            ln.erase(0, ln.find_first_not_of(" \t\r\n"));
            ln.erase(ln.find_last_not_of(" \t\r\n") + 1);

            // 跳过空行
            if (ln.empty())
                continue;


            if (inDef)
            {
                if (ln == "%}")
                    inDef = false;
                else
                {
                    program1 += ln + "\n";
                }
                continue;
            }
            if (ln == "%{")
            {
                inDef = true;
                continue;
            }
            if (ln == "%%")
            {
                ++step;
                continue;
            }
            if (ln == "")
                continue;
            switch (step)
            {
                case 0:
                {
                    auto p_ = lnToPair(ln);
                    std::cout << "[DEFINE] " << p_.first << " = " << p_.second << std::endl;

                    define_rules[p_.first] = p_.second;
                    break;
                }
                case 1:
                {
                    auto p_ = lnToPair(ln);
                    std::cout << "[REGEX] " << p_.first << " => " << p_.second << std::endl;

                    regex_rules.push_back(p_);
                    break;
                }
                case 2:
                    program2 += ln + "\n"; // 添加换行符
                    break;
                default:
                    throw "";
            }
        }

    }

    void initAll(std::string filename)
    {
        std::ifstream ifile;
        ifile.open(filename, std::ios::in);
        readFromStream(ifile);
        ifile.close();
    }

    YylParser() = default;

    YylParser(std::string filename)
    {
        initAll(filename);
    }


    void show() const
    {
        using namespace std;

        cout << "=== C 代码声明部分 (program1) ===" << endl;
        if (!program1.empty()) {
            cout << program1 << endl;
        } else {
            cout << "(无内容)" << endl;
        }

        cout << "=== 宏定义部分 (define_rules) ===" << endl;
        if (!define_rules.empty()) {
            for (const auto &p : define_rules) {
                cout << p.first << " = " << p.second << endl;
            }
        } else {
            cout << "(无内容)" << endl;
        }

        cout << "=== 正则表达式规则部分 (regex_rules) ===" << endl;
        if (!regex_rules.empty())
        {
            for (const auto &p : regex_rules)
            {
                cout << p.first << " => " << p.second << endl;
            }
        } else
        {
            cout << "(无内容)" << endl;
        }

        cout << "=== 用户代码部分 (program2) ===" << endl;
        if (!program2.empty()) {
            cout << program2 << endl;
        } else {
            cout << "(无内容)" << endl;
        }
    }

};

