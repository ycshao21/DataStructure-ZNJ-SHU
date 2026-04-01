#include <algorithm>
#include <print>
#include <unordered_set>
#include <vector>
#include <array>

#include "utils/console.hpp"
#include "utils/random.hpp"
#include "utils/timer.hpp"

#include "binary_search_tree.hpp"
#include "task03.hpp"

static int getKeyFromUser() {
    std::print("Please input an integer: ");
    int key;
    while (true) {
        std::cin >> key;
        bool validInput = !std::cin.fail();
        utils::clearBuffer();
        if (validInput) {
            break;
        }
        std::print("Invalid input! Please re-input an integer: ");
    }
    return key;
}

void bst_functionalTest()
{
    utils::Menu menu("BST Functional Test", true, "Return to Main Menu");

    myds::BinarySearchTree<int, int> tree;
    menu.setHeader([&]() {
        std::println();
        tree.printKeyTree();
    });

    menu.addItem("Insert Element", [&]() {
        int key = getKeyFromUser();
        tree.insert(key, key);
    });

    menu.addItem("Erase Element (Ver1: Replace with Successor)", [&]() {
        int key = getKeyFromUser();
        tree.erase_ver1(key);
    });

    menu.addItem("Erase Element (Ver2: Replace with Predecessor)", [&]() {
        int key = getKeyFromUser();
        tree.erase_ver2(key);
    });

    menu.addItem("Erase Element (Ver3: Move Left Subtree to Successor)", [&]() {
        int key = getKeyFromUser();
        tree.erase_ver3(key);
    });

    menu.addItem("Erase Element (Ver4: Move Right Subtree to Predecessor)", [&]() {
        int key = getKeyFromUser();
        tree.erase_ver4(key);
    });

    menu.addItem("Clear", [&]() {
        tree.clear();
    });

    menu.run();
}

void bst_efficiencyTest()
{
    std::println("BST Efficiency Test");
    std::print("Please input the number of elements: ");
    int num;
    bool validInput;
    while (true) {
        std::cin >> num;
        validInput = !std::cin.fail() && num > 0;
        utils::clearBuffer();
        if (validInput) {
            break;
        }
        std::print("Invalid input! Please re-input the number of elements: ");
    }

    std::println("Generating random elements...");
    std::unordered_set<int> uniqueKeys;
    std::vector<std::pair<int, int>> elements;
    while (elements.size() < static_cast<size_t>(num)) {
        int val = utils::RandUniform<int>()(-2 * num, 2 * num);
        auto [_, inserted] = uniqueKeys.insert(val);
        if (inserted) {
            elements.emplace_back(val, val);
        }
    }

    myds::BinarySearchTree<int, int> baseTree(elements);

    auto runTest = [&](int version, const std::string& description) {
        std::print("Testing {}: ", description);
        myds::BinarySearchTree<int, int> testTree(baseTree);
        utils::Timer timer;
        for (const auto& e : elements) {
            if (version == 1) {
                testTree.erase_ver1(e.first);
            } else if (version == 2) {
                testTree.erase_ver2(e.first);
            } else if (version == 3) {
                testTree.erase_ver3(e.first);
            } else if (version == 4) {
                testTree.erase_ver4(e.first);
            }
        }
        std::println("Time taken: {}s", timer.elapsed());
    };
    runTest(1, "Replace with Successor");
    runTest(2, "Replace with Predecessor");
    runTest(3, "Move Left Subtree to Successor");
    runTest(4, "Move Right Subtree to Predecessor");
}