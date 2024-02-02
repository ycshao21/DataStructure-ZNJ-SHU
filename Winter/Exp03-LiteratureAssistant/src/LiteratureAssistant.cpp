#include "W3_Solution.h"
#include "Console.h"

#include <iostream>
#include <string>

namespace Winter03
{
    void LiteratureAssistant()
    {
        std::cout << "冬-实验三 文学研究助手\n\n";

        std::string patternPath = "data/patterns.txt";
        std::string textPath = "data/text.txt";
        std::string outputDir = "output/";

        Winter03::Task(patternPath, textPath, outputDir);

        std::cout << std::endl;
        Console::WaitForKey();
    }
}

int main()
{
    Winter03::LiteratureAssistant();
}