#include <algorithm>
#include <format>
#include <unordered_set>
#include <vector>
#include <array>

#include "utils/console.hpp"
#include "utils/random.hpp"
#include "utils/timer.hpp"

#include "binary_search_tree.hpp"
#include "task03.hpp"

static int getKeyFromUser() {
    std::cout << "Please input an integer: ";
    int key;
    while (true) {
        std::cin >> key;
        bool validInput = !std::cin.fail();
        utils::clearBuffer();
        if (validInput) {
            break;
        }
        std::cout << "Invalid input! Please re-input an integer: ";
    }
    return key;
}

void bst_functionalTest()
{
    myds::BinarySearchTree<int, int> tree;
    const std::array<std::string, 7> menu = {
        "Insert Element",
        "Erase Element (Ver1: Replace with Successor)",
        "Erase Element (Ver2: Replace with Predecessor)",
        "Erase Element (Ver3: Move Left Subtree to Successor)",
        "Erase Element (Ver4: Move Right Subtree to Predecessor)",
        "Clear",
        "Return to Main Menu"
    };

    while (true) {
        std::cout << "\nBST Functional Test\n" << std::endl;
        tree.printKeyTree();

        for (std::size_t i = 0; i < menu.size(); ++i) {
            std::cout << std::format("[{}] {}\n", i + 1, menu[i]);
        }

        int choice = utils::getChoice(7);
        if (choice == menu.size()) {
            return;
        }
        if (choice == 6) {
            tree.clear();
            continue;
        }

        std::cout << std::format("\n[{}]\n", menu[choice - 1]);

        int key = getKeyFromUser();
        if (choice == 1) {
            tree.insert(key, key);
        } else if (choice == 2) {
            tree.erase_ver1(key);
        } else if (choice == 3) {
            tree.erase_ver2(key);
        } else if (choice == 4) {
            tree.erase_ver3(key);
        } else if (choice == 5) {
            tree.erase_ver4(key);
        }
    }
}

void bst_efficiencyTest()
{
    std::cout << "\nBST Efficiency Test\n";
    std::cout << "Please enter the number of elements: ";
    int num;
    bool validInput;
    while (true) {
        std::cin >> num;
        validInput = !std::cin.fail() && num > 0;
        utils::clearBuffer();
        if (validInput)
            break;
        std::cout << "Please enter a valid number of elements: ";
    }

    std::cout << "Generating random elements...\n" << std::endl;
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
        std::cout << std::format("Testing {}: ", description);
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
        std::cout << std::format("Time taken: {}s\n", timer.elapsed());
    };
    runTest(1, "Replace with Successor");
    runTest(2, "Replace with Predecessor");
    runTest(3, "Move Left Subtree to Successor");
    runTest(4, "Move Right Subtree to Predecessor");
}