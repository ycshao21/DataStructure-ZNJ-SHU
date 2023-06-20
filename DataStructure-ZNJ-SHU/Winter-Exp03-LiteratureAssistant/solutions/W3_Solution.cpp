#include<iostream>
#include<fstream>
#include<sstream>
#include<conio.h>
#include<string>
#include<vector>
#include<set>
#include<direct.h>
#include<io.h>

namespace W3
{
    struct location
    {
        int row = 1;
        int col = 1;
    };

    // @brief Build next array for KMP (Multiple matching).
    void BuildNext(const std::string& pattern, std::vector<int>& next) {
        next.clear();
        next.push_back(-1);
        int t = -1;
        for (int j = 0; j < pattern.size();) {
            while (t >= 0 && pattern[j] != pattern[t]) {
                t = next[t];
            }
            ++t, ++j;
            if (pattern[j] == pattern[t]) {
                next.push_back(next[t]);
            } else {
                next.push_back(t);
            }
        }
    }

    void GetPatterns(std::ifstream& fpPat, std::vector<std::string>& patterns, std::vector<std::vector<int>>& next) {
        std::set<std::string> checkDuplicate;
        std::string word;
        while (fpPat >> word) {
            // Ignore the word if it is already read.
            if (checkDuplicate.find(word) != checkDuplicate.end()) {
                continue;
            }
            // Check if the word is valid.
            bool valid = true;
            for (auto& c : word) {
                if (c >= 'A' && c <= 'Z') {  // Convert uppercase to lowercase.
                    c = c - 'A' + 'a';
                } else if (!(c >= 'a' && c <= 'z') && c != '-') {  // Ignore non-alphabetic characters.
                    valid = false;
                    break;
                }
            }
            if (!valid) { continue; }
            checkDuplicate.emplace(word);
            patterns.push_back(word);
            // Build next array for KMP.
            std::vector<int> theNext;
            BuildNext(word, theNext);
            next.push_back(theNext);
        }
    }

    void Question(const std::string& patternPath, const std::string& textPath, const std::string& savePath) {
        // Read patterns to be counted.
        std::cout << "正在从" << patternPath << "读取待统计的单词……" << std::endl;
        std::ifstream fpPattern(patternPath);
        if (!fpPattern.good()) {
            std::cout << "文件不存在，程序终止！" << std::endl;
            return;
        }
        std::vector<std::string> patterns;
        std::vector<std::vector<int>> next;
        GetPatterns(fpPattern, patterns, next);
        fpPattern.close();
        if (patterns.empty()) {
            std::cout << "待统计的单词数不能为0，程序终止！" << std::endl;
            return;
        }
        std::cout << "读取完毕！\n" << std::endl;

        // Count the patterns in the text.
        std::cout << "正在对" << textPath << "的内容进行统计……" << std::endl;
        std::ifstream fpText(textPath);
        if (!fpText.good()) {
            std::cout << "文件不存在，程序终止！" << std::endl;
            return;
        }
        char ch;
        location pos{ 1, 1 };  // Position of current character.
        std::vector<int> p(next.size(), 0);  // Pattern pointers.
        std::vector<std::vector<location>> count(next.size());
        while ((ch = fpText.get()) != EOF) {
            // If it reaches the end of a line, move pos to the next row and reset the pattern pointers.
            if (ch == '\n' || ch == '\r') {
                ++pos.row, pos.col = 1;
                for (auto& i : p) { i = 0; }
                continue;
            }
            // Convert uppercase to lowercase.
            if (ch >= 'A' && ch <= 'Z') {
                ch = ch - 'A' + 'a';
            }
            // KMP for each pattern.
            for (int i = 0; i < patterns.size(); ++i) {
                while (p[i] >= 0 && ch != patterns[i][p[i]]) {
                    p[i] = next[i][p[i]];
                }
                ++p[i];
                // Pattern matched.
                if (p[i] == patterns[i].size()) {
                    count[i].emplace_back(pos.row, pos.col - p[i] + 1);
                    p[i] = next[i][p[i]];
                }
            }
            ++pos.col;
        }
        fpText.close();
        std::cout << "统计完毕！\n" << std::endl;

        // Output the result.
        std::ostringstream ans;
        for (int i = 0; i < patterns.size(); ++i) {
            ans << i + 1 << ". " << patterns[i] << "，出现次数：" << count[i].size() << std::endl;
            if (!count[i].empty()) {
                for (const auto& n : count[i]) {
                    ans << "    第" << n.row << "行，第" << n.col << "列" << std::endl;
                }
            }
            ans << std::endl;
        }
        std::cout << ans.str();

        std::cout << "结果输出完毕！" << std::endl;
        std::cout << "是否要将统计结果保存到" << savePath << "result.txt? [Y/N]" << std::endl;
        char key;
        while ((key = _getch()) != 'y' && key != 'Y' && key != 'n' && key != 'N');
        if (key == 'y' || key == 'Y') {
            if (_access(savePath.c_str(), 0) == -1) {
                _mkdir(savePath.c_str());
            }
            std::ofstream fout(savePath + "result.txt");
            fout << ans.str();
            fout.close();
            std::cout << "已保存！" << std::endl;
        }
    }
}