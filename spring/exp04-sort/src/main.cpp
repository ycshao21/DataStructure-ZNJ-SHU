#include <algorithm>
#include <filesystem>
#include <format>
#include <iostream>
#include <ranges>
#include <vector>
#include <array>

#include "utils/console.hpp"
#include "utils/random.hpp"
#include "utils/timer.hpp"

#include "dna_sort.hpp"
#include "quick_sort.hpp"

void runTask01()
{
    static const std::array<std::string, 2> menu{"Manual Input", "Random Generation"};
    for (std::size_t i = 0; i < menu.size(); ++i) {
        std::cout << std::format("[{}] {}\n", i + 1, menu[i]);
    }
    std::size_t mode = utils::getChoice(menu.size());

    std::cout << "Please input the size of the array: ";
    int size;
    while (true) {
        std::cin >> size;
        bool validInput = !std::cin.fail() && size > 0;
        utils::clearBuffer();
        if (validInput) {
            break;
        }
        std::cout << "Invalid input! Please re-input the size of the array: ";
    }
    
    std::vector<int> arr;
    if (mode == 1) {
        arr.resize(size);

        std::cout << "Please input the elements of the array: ";
        while (true) {
            bool validInput = true;
            for (int i = 0; i < size; ++i) {
                std::cin >> arr[i];
                validInput = !std::cin.fail();
                if (!validInput) {
                    break;
                }
            }
            utils::clearBuffer();
            if (validInput) {
                break;
            }
            std::cout << "Invalid input! Please re-input the elements of the array: ";
        }
    } else {
        std::cout << "Generating the array...\n";
        arr = utils::RandUniform<int>().generateVec(size, -20000, 20000);
    }

    std::vector<int> expected(arr);
    std::ranges::sort(expected);

    auto runTest = [&](const std::string& label, std::vector<int> testArr, auto sortFunc, bool check) {
        std::cout << std::format("\n--- {} ---\n", label);
        
        utils::Timer timer;
        sortFunc(testArr);
        auto elapsed = timer.elapsed();

        if (mode == 1) {
            std::cout << "Result:";
            for (int e : testArr) std::cout << std::format(" {}", e);
            std::cout << "\n";
        }

        std::cout << std::format("Elapsed time: {} ms\n", elapsed);
        if (check) {
            if (testArr != expected) {
                std::cout << "!!! [ERROR] Wrong Sorting Result !!!\n";
            } else {
                std::cout << "[OK] Verification Passed.\n";
            }
        }
    };

    runTest("std::sort", arr, [](std::vector<int>& v) { std::ranges::sort(v); }, false);
    runTest("Quick Sort | First Element", arr, [](std::vector<int>& v) {
        myalgorithm::quickSort(v, myalgorithm::PivotStrategy::FirstElement);
    }, true);
    runTest("Quick Sort | Median Of Three", arr, [](std::vector<int>& v) {
        myalgorithm::quickSort(v, myalgorithm::PivotStrategy::MedianOfThree);
    }, true);
}

void runTask02()
{
    int n, m;
    std::cout << "Please input the number of DNA strings and their lengths: ";
    while (true) {
        std::cin >> n >> m;
        bool validInput = !std::cin.fail() && n > 0 && m > 0;
        utils::clearBuffer();
        if (validInput) {
            break;
        }
        std::cout << "Invalid input! Please re-input the number of DNA strings and their lengths: ";
    }

    std::cout << "Please input the DNA strings (only characters A, C, G, T are allowed):\n";
    std::vector<std::string> dnaVec(n);
    for (int i = 0; i < n; i++) {
        while (true) {
            std::cout << std::format("({}) ", i + 1);
            std::cin >> dnaVec[i];
            if (dnaVec[i].size() == m) {
                bool validInput = true;
                for (char c : dnaVec[i]) {
                    if (c != 'A' && c != 'C' && c != 'G' && c != 'T') {
                        validInput = false;
                        break;
                    }
                }
                if (validInput) {
                    break;
                }
            }
            utils::clearBuffer();
            std::cout << "Invalid input! Please re-input the DNA string: ";
        }
    }
    dnaSort(dnaVec);
}

void exp04_sort()
{
    const std::array<std::string, 3> menu = {
        "Task 1 - Quick Sort",
        "Task 2 - DNA Sort",
        "Exit"
    };

    while (true) {
        std::cout << "Exp04 - Sort\n";

        for (std::size_t i = 0; i < menu.size(); ++i) {
            std::cout << std::format("[{}] {}\n", i + 1, menu[i]);
        }

        std::size_t choice = utils::getChoice(menu.size());
        if (choice == menu.size()) {
            return;
        }

        std::cout << '\n';
        std::cout << std::format("[{}]\n", menu[choice - 1]);

        if (choice == 1) {
            runTask01();
        } else if (choice == 2) {
            runTask02();
        }

        std::cout << '\n';
    }
}

int main()
{
    std::filesystem::current_path(EXPERIMENT_WORKING_DIR);
    exp04_sort();
}