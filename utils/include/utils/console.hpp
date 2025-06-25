#pragma once
#include <iostream>
#include <limits>

namespace utils
{

inline void clearBuffer(char end = '\n')
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), end);
}

inline std::size_t getChoice(
    std::size_t numChoices, const std::string& prompt = "Input your choice: ",
    const std::string& err = "Invalid choice, please try again: ")
{
    if (!prompt.empty()) {
        std::cout << prompt;
    }

    std::size_t choice;
    while (true) {
        std::cin >> choice;
        if (!std::cin.fail() && choice >= 1 && choice <= numChoices) {
            return choice;
        }

        clearBuffer();
        if (!err.empty()) {
            std::cout << err;
        }
    }
}

}  // namespace utils