#include <array>
#include <filesystem>
#include <format>
#include <iostream>
#include <print>

#include "utils/console.hpp"

#include "solution.hpp"

void exp04_binaryTree()
{
    utils::Menu menu("Exp04 - Binary Tree");

    menu.addItem("Task 1", []() {
        runTask01();
    });

    menu.addItem("Task 2", []() {
        std::print("Please input the number of cases: ");
        int numOfCases;
        while (true) {
            std::cin >> numOfCases;
            bool validInput = !std::cin.fail() && numOfCases > 0;
            utils::clearBuffer();
            if (validInput) {
                break;
            }
            std::print("Invalid input! Please re-input the number of cases: ");
        }

        std::println("Please input the cases:");
        for (int i = 0; i < numOfCases; ++i) {
            int a, b;
            while (true) {
                std::print("({}) ", i + 1);
                std::cin >> a >> b;
                bool validInput = !std::cin.fail() && a > 0 && b > 0;
                utils::clearBuffer();
                if (validInput) {
                    break;
                }
                std::print("Invalid input! Please re-input the cases: ");
            }
            runTask02(a, b);
        }
    });

    menu.run();
}

int main()
{
    std::filesystem::current_path(EXPERIMENT_WORKING_DIR);
    exp04_binaryTree();
}