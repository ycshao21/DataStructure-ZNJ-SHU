#include <filesystem>
#include <iostream>

#include "solution.hpp"

void exp03_literatureAssistant()
{
    std::cout << "Exp03 - Literature Assistant\n";

    std::filesystem::path patternPath = "data/patterns.txt";
    std::filesystem::path textPath = "data/text.txt";
    std::filesystem::path outputDir = "output/";

    runTask(patternPath, textPath, outputDir);
}

int main()
{
    std::filesystem::current_path(EXPERIMENT_WORKING_DIR);
    exp03_literatureAssistant();
}