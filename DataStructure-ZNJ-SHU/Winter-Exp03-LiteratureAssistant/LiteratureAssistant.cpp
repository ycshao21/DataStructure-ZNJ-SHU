#include<iostream>
#include<string>
#include"solutions/W3_Solution.h"
#include"../../Tools/Settings.hpp"

namespace Menu
{
    void LiteratureAssistant() {
        system("cls");
        std::cout << "冬-实验三 文学研究助手\n" << std::endl;

        std::string patternPath = "Winter-Exp03-LiteratureAssistant/data/patterns.txt";
        std::string textPath = "Winter-Exp03-LiteratureAssistant/data/text.txt";
        std::string savePath = "Winter-Exp03-LiteratureAssistant/output/";

        W3::Question(patternPath, textPath, savePath);

        std::cout << std::endl;
        system("pause");
    }
}