#include <algorithm>
#include <array>
#include <cstddef>
#include <filesystem>
#include <print>
#include <vector>

#include "utils/console.hpp"
#include "utils/random.hpp"
#include "utils/timer.hpp"

#include "task01.hpp"
#include "task02.hpp"
#include "task03.hpp"

static std::vector<int> getSortedArray(std::size_t size)
{
    std::print("Please input {} integers in ascending order: ", size);
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
        std::print("Invalid input! Please re-input {} integers in ascending order: ", size);
    }
    return arr;
}

void runTask01() {
    std::print("Please input the sizes of three vectors: ");
    std::size_t size1, size2, size3;
    while (true) {
        std::cin >> size1 >> size2 >> size3;
        bool validInput = size1 > 0 && size2 > 0 && size3 > 0;
        utils::clearBuffer();
        if (validInput) {
            break;
        }
        std::print("Invalid input! Please re-input the sizes of three vectors: ");
    }

    std::println();

    std::println("=== Array a ===");
    std::vector<int> a = getSortedArray(size1);
    std::println();

    std::println("=== Array b ===");
    std::vector<int> b = getSortedArray(size2);
    std::println();

    std::println("=== Array c ===");
    std::vector<int> c = getSortedArray(size3);
    std::println();

    findMinCommonElement(a, b, c);
}

void runTask02() {
    utils::Menu inputModeMenu("", false);
    inputModeMenu.addItem("Manual Input");
    inputModeMenu.addItem("Random Generation");
    std::size_t inputModeChoice = inputModeMenu.ask();

    utils::Menu versionMenu("", false);
    versionMenu.addItem("Simple Version");
    versionMenu.addItem("General Version");
    std::size_t versionChoice = versionMenu.ask();

    // Input sizes of vectors.
    int m = -1, n = -1;
    if (versionChoice == 1) {
        std::print("Please input the size of two vectors (n): ");
        while (true) {
            std::cin >> n;
            if (!std::cin.fail() && n > 0) {
                break;
            }
            std::print("Invalid input! Please re-input the size of two vectors (n): ");
        }
        m = n;
    } else {
        std::print("Please input the sizes of two vectors (m and n): ");
        while (true) {
            std::cin >> m >> n;
            bool validInput = !std::cin.fail() && m > 0 && n > 0;
            utils::clearBuffer();
            if (validInput) {
                break;
            }
            std::print("Invalid input! Please re-input the sizes of two vectors (m and n): ");
        }
    }
    std::println();

    std::vector<int> vec1, vec2;
    if (inputModeChoice == 1) {
        std::println("=== Vector 1 ===");
        vec1 = getSortedArray(m);
        std::println();

        std::println("=== Vector 2 ===");
        vec2 = getSortedArray(n);
    } else {
        std::println("Generating two sorted vectors...");
        vec1 = utils::RandUniform<int>().generateVec(m, -1000000, 10000000);
        vec2 = utils::RandNormal<int>().generateVec(n, 0, 500000);
        std::ranges::sort(vec1);
        std::ranges::sort(vec2);
        std::println("Done.");
    }

    bool showTime = inputModeChoice == 2;

    auto benchmark = [&](const std::string& name, auto simpleFn, auto generalFn) {
        std::println();
        std::println("--- {} Algorithm ---", name);
        utils::Timer timer;
        if (versionChoice == 1) {
            int res = simpleFn(vec1, vec2);
            double t = timer.elapsed();
            std::println("Median: {}", res);
            if (showTime) {
                std::println("Time: {}s", t);
            }
        } else {
            double res = generalFn(vec1, vec2);
            double t = timer.elapsed();
            std::println("Median: {}", res);
            if (showTime) {
                std::println("Time: {}s", t);
            }
        }
    };

    benchmark("Linear", findMedian_linear<int>, findMedian_linear_general<int>);
    benchmark("Binary", findMedian_binary<int>, findMedian_binary_general<int>);
}

void runTask03() {
    utils::Menu menu("", false);
    menu.addItem("Functional Test");
    menu.addItem("Efficiency Test");

    std::size_t choice = menu.ask();
    if (choice == 1) {
        bst_functionalTest();
    } else {
        bst_efficiencyTest();
    }
}

void exp03_search()
{
    utils::Menu menu("Exp03 - Search");
    menu.addItem("Task 1 - Find Minimum Common Element in Three Sorted Arrays", runTask01);
    menu.addItem("Task 2 - Find Median of Two Sorted Arrays", runTask02);
    menu.addItem("Task 3 - Binary Search Tree", runTask03);
    menu.run();
}

int main()
{
    std::filesystem::current_path(EXPERIMENT_WORKING_DIR);
    exp03_search();
}