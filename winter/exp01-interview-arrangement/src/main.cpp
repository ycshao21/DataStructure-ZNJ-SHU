#include <array>
#include <filesystem>
#include <format>
#include <iostream>

#include "utils/console.hpp"

#include "efficiency_test.hpp"
#include "solution.hpp"

static void getInputValues(int& n, int& k, int& m)
{
    std::cout << "Please input the values of N, K, M: ";
    while (true) {
        std::cin >> n >> k >> m;
        bool isValid = !std::cin.fail() && n > 0 && k > 0 && m > 0;
        utils::clearBuffer();
        if (isValid) {
            break;
        }
        std::cout << "Invalid input! Please re-input the values of N, K, M: ";
    }
}

static void exp01_interviewArrangement()
{
    const std::array<std::string, 4> menu = {"Task 1", "Task 2", "Efficiency Test",
                                             "Exit"};

    while (true) {
        std::cout << "Exp01 - Interview Arrangement\n";

        for (std::size_t i = 0; i < menu.size(); ++i) {
            std::cout << std::format("[{}] {}\n", i + 1, menu[i]);
        }

        std::size_t choice = utils::getChoice(menu.size());
        if (choice == menu.size()) {
            return;
        }

        std::cout << std::format("\n[{}]\n", menu[choice - 1]);

        if (choice == 1) {
            int n, k, m;
            getInputValues(n, k, m);
            task01(n, k, m, &std::cout);
        } else if (choice == 2) {
            int n, k, m;
            getInputValues(n, k, m);
            task02(n, k, m, &std::cout);
        } else if (choice == 3) {
            efficiencyTest();
        }

        std::cout << '\n' << std::flush;
    }
}

int main()
{
    std::filesystem::current_path(EXPERIMENT_WORKING_DIR);
    exp01_interviewArrangement();
}