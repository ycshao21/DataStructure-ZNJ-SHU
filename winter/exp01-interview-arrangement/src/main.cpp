#include <filesystem>
#include <print>

#include "utils/console.hpp"

#include "solution.hpp"
#include "efficiency_test.hpp"

static void inputNKM(int& n, int& k, int& m)
{
    std::print("Please input the values of N, K, M: ");
    while (true) {
        std::cin >> n >> k >> m;
        bool isValid = !std::cin.fail() && n > 0 && k > 0 && m > 0;
        utils::clearBuffer();
        if (isValid) {
            break;
        }
        std::print("Invalid input! Please re-input the values of N, K, M: ");
    }
}

static void exp01_interviewArrangement()
{
    utils::Menu menu("Exp01 - Interview Arrangement");

    menu.addItem("Task 1", []() {
        int n, k, m;
        inputNKM(n, k, m);
        runTask01(n, k, m, &std::cout);
    });
    menu.addItem("Task 2", []() {
        int n, k, m;
        inputNKM(n, k, m);
        runTask02(n, k, m, &std::cout);
    });
    menu.addItem("Efficiency Test", efficiencyTest);

    menu.run();
}

int main()
{
    std::filesystem::current_path(EXPERIMENT_WORKING_DIR);
    exp01_interviewArrangement();
}