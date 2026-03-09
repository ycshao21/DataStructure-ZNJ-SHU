#include <algorithm>
#include <array>
#include <filesystem>
#include <format>
#include <iostream>
#include <vector>

#include "utils/console.hpp"
#include "utils/random.hpp"
#include "utils/timer.hpp"

#include "task01.hpp"
#include "task02.hpp"
#include "task03.hpp"

static std::vector<int> getSortedArray(std::size_t size)
{
    std::cout << std::format("Please input {} integers in ascending order: ", size);

    std::vector<int> arr(size);
    while (true) {
        bool validInput = true;
        for (std::size_t i = 0; i < size; ++i) {
            std::cin >> arr[i];
            validInput = !std::cin.fail() && (i == 0 || arr[i - 1] <= arr[i]);
            if (!validInput) {
                break;
            }
        }

        utils::clearBuffer();
        if (validInput) {
            break;
        }
        std::cout << std::format(
            "Invalid input! Please re-input {} integers in ascending order: ", size);
    }
    return arr;
}

void runTask01() {
    std::cout << "Please input the sizes of three vectors: ";
    std::size_t size1, size2, size3;
    while (true) {
        std::cin >> size1 >> size2 >> size3;
        bool validInput = size1 > 0 && size2 > 0 && size3 > 0;
        utils::clearBuffer();
        if (validInput) {
            break;
        }
        std::cout << "Invalid input! Please re-input the sizes of three vectors: ";
    }

    std::cout << "\n=== Array a ===\n";
    std::vector<int> a = getSortedArray(size1);

    std::cout << "\n=== Array b ===\n";
    std::vector<int> b = getSortedArray(size2);

    std::cout << "\n=== Array c ===\n";
    std::vector<int> c = getSortedArray(size3);

    std::cout << '\n';
    findMinCommonElement(a, b, c);
}

void runTask02() {
    // Input mode selection.
    const std::array<std::string, 2> inputModeMenu = {"Manual Input", "Random Generation"};
    for (std::size_t i = 0; i < inputModeMenu.size(); ++i) {
        std::cout << std::format("[{}] {}\n", i + 1, inputModeMenu[i]);
    }
    int inputModeChoice = utils::getChoice(2);
    std::cout << '\n';

    const std::array<std::string, 2> versionMenu = {"Simple Version", "General Version"};
    for (std::size_t i = 0; i < versionMenu.size(); ++i) {
        std::cout << std::format("[{}] {}\n", i + 1, versionMenu[i]);
    }
    int versionChoice = utils::getChoice(2);
    std::cout << '\n';

    // Input sizes of vectors.
    int m = -1, n = -1;
    if (versionChoice == 1) {
        std::cout << "Please input the size of two vectors (n): ";
        while (true) {
            std::cin >> n;
            if (!std::cin.fail() && n > 0) {
                break;
            }
            std::cout << "Invalid input! Please re-input the size of two vectors (n): ";
        }
        m = n;
    } else {
        std::cout << "Please input the sizes of two vectors (m and n): ";
        while (true) {
            std::cin >> m >> n;
            bool validInput = !std::cin.fail() && m > 0 && n > 0;
            utils::clearBuffer();
            if (validInput) {
                break;
            }
            std::cout << "Invalid input! Please re-input the sizes of two vectors (m and n): ";
        }
    }

    std::vector<int> vec1, vec2;
    if (inputModeChoice == 1) {
        std::cout << "\n=== Vector 1 ===\n";
        vec1 = getSortedArray(m);

        std::cout << "\n=== Vector 2 ===\n";
        vec2 = getSortedArray(n);
    } else {
        std::cout << "\nGenerating two sorted vectors...\n";
        vec1 = utils::RandUniform<int>().generateVec(m, -1000000, 10000000);
        vec2 = utils::RandNormal<int>().generateVec(n, 0, 500000);
        std::ranges::sort(vec1);
        std::ranges::sort(vec2);
        std::cout << "Done.\n";
    }

    bool showTime = inputModeChoice == 2;

    auto benchmark = [&](const std::string& name, auto simpleFn, auto generalFn) {
        std::cout << std::format("\n--- {} Algorithm ---\n", name);
        utils::Timer timer;
        if (versionChoice == 1) {
            int res = simpleFn(vec1, vec2);
            double t = timer.elapsed();
            std::cout << std::format("Median: {}\n", res);
            if (showTime) {
                std::cout << std::format("Time: {}s\n", t);
            }
        } else {
            double res = generalFn(vec1, vec2);
            double t = timer.elapsed();
            std::cout << std::format("Median: {}\n", res);
            if (showTime) {
                std::cout << std::format("Time: {}s\n", t);
            }
        }
    };

    benchmark("Linear", findMedian_linear<int>, findMedian_linear_general<int>);
    benchmark("Binary", findMedian_binary<int>, findMedian_binary_general<int>);
}

void runTask03() {
    const std::array<std::string, 2> submenu = {"Functional Test",
                                                "Efficiency Test"};
    for (std::size_t i = 0; i < submenu.size(); ++i) {
        std::cout << std::format("[{}] {}\n", i + 1, submenu[i]);
    }
    int subchoice = utils::getChoice(2);
    if (subchoice == 1) {
        bst_functionalTest();
    } else {
        bst_efficiencyTest();
    }
}

void exp03_search()
{
    const std::array<std::string, 4> menu = {
        "Task 1 - Find Minimum Common Element in Three Sorted Arrays",
        "Task 2 - Find Median of Two Sorted Arrays",
        "Task 3 - Binary Search Tree",
        "Exit"
    };

    while (true) {
        std::cout << "Exp03 - Search\n";

        for (std::size_t i = 0; i < menu.size(); ++i) {
            std::cout << std::format("[{}] {}\n", i + 1, menu[i]);
        }

        std::size_t choice = utils::getChoice(menu.size());
        if (choice == menu.size()) {
            return;
        }

        std::cout << std::format("\n[{}]\n", menu[choice - 1]);

        if (choice == 1) {
            runTask01();
        } else if (choice == 2) {
            runTask02();
        } else {  // choice == 3
            runTask03();
        }
        std::cout << '\n' << std::flush;
    }
}

int main()
{
    std::filesystem::current_path(EXPERIMENT_WORKING_DIR);
    exp03_search();
}