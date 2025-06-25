#include <array>
#include <filesystem>
#include <format>
#include <iostream>

#include "utils/console.hpp"

#include "solution.hpp"

void exp04_binaryTree()
{
    const std::array<std::string, 3> menu = {"Task 1", "Task 2", "Exit"};

    while (true) {
        std::cout << "Exp04 - Binary Tree\n";
        for (std::size_t i = 0; i < menu.size(); ++i) {
            std::cout << std::format("[{}] {}\n", i + 1, menu[i]);
        }

        std::size_t choice = utils::getChoice(menu.size());
        if (choice == menu.size()) {
            return;
        }

        std::cout << std::format("\n[{}]\n", menu[choice - 1]);

        if (choice == 1) {
            task01();
        } else {
            std::cout << "Please input the number of cases: ";
            int numOfCases;
            while (true) {
                std::cin >> numOfCases;
                bool validInput = !std::cin.fail() && numOfCases > 0;
                utils::clearBuffer();
                if (validInput) {
                    break;
                }
                std::cout << "Invalid input! Please re-input the number of cases: ";
            }

            std::cout << "Please input the cases:\n";
            for (int i = 0; i < numOfCases; ++i) {
                int a, b;
                while (true) {
                    std::cout << std::format("({}) ", i + 1);
                    std::cin >> a >> b;
                    bool validInput = !std::cin.fail() && a > 0 && b > 0;
                    utils::clearBuffer();
                    if (validInput) {
                        break;
                    }
                    std::cout << "Invalid input! Please re-input the cases: ";
                }
                task02(a, b);
            }
        }

        std::cout << '\n' << std::flush;
    }
}

int main()
{
    std::filesystem::current_path(EXPERIMENT_WORKING_DIR);
    exp04_binaryTree();
}