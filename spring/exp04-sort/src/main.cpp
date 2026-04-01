#include <algorithm>
#include <filesystem>
#include <print>
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
    utils::Menu menu("", false);
    menu.addItem("Manual Input");
    menu.addItem("Random Generation");
    std::size_t mode = menu.ask();

    std::print("Please input the size of the array: ");
    int size;
    while (true) {
        std::cin >> size;
        bool validInput = !std::cin.fail() && size > 0;
        utils::clearBuffer();
        if (validInput) {
            break;
        }
        std::print("Invalid input! Please re-input the size of the array: ");
    }
    
    std::vector<int> arr;
    if (mode == 1) {
        arr.resize(size);

        std::print("Please input the elements of the array: ");
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
            std::print("Invalid input! Please re-input the elements of the array: ");
        }
    } else {
        std::println("Generating the array...");
        arr = utils::RandUniform<int>().generateVec(size, -20000, 20000);
    }

    std::println();

    std::vector<int> expected(arr);
    std::ranges::sort(expected);

    auto runTest = [&](const std::string& label, std::vector<int> testArr, auto sortFunc, bool check) {
        std::println("--- {} ---", label);
        
        utils::Timer timer;
        sortFunc(testArr);
        auto elapsed = timer.elapsed();

        if (mode == 1) {
            std::print("Result:");
            for (int e : testArr) {
                std::print(" {}", e);
            }
            std::println();
        }

        std::println("Elapsed time: {}s", elapsed);
        if (check) {
            if (testArr != expected) {
                std::println("!!! [ERROR] Wrong Sorting Result !!!");
            } else {
                std::println("[OK] Verification Passed.");
            }
        }
        std::println();
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
    std::print("Please input the number of DNA strings and their lengths: ");
    while (true) {
        std::cin >> n >> m;
        bool validInput = !std::cin.fail() && n > 0 && m > 0;
        utils::clearBuffer();
        if (validInput) {
            break;
        }
        std::print("Invalid input! Please re-input the number of DNA strings and their lengths: ");
    }

    std::println("Please input the DNA strings (only characters A, C, G, T are allowed):");
    std::vector<std::string> dnaVec(n);
    for (int i = 0; i < n; i++) {
        while (true) {
            std::print("({}) ", i + 1);
            std::cin >> dnaVec[i];
            if ((int)dnaVec[i].size() == m) {
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
            std::println("Invalid input! Please re-input the DNA string: ");
        }
    }
    dnaSort(dnaVec);
}

void exp04_sort()
{
    utils::Menu menu("Exp04 - Sort");
    menu.addItem("Task 1 - Quick Sort", runTask01);
    menu.addItem("Task 2 - DNA Sort", runTask02);
    menu.run();
}

int main()
{
    std::filesystem::current_path(EXPERIMENT_WORKING_DIR);
    exp04_sort();
}