#include <format>
#include <iostream>

#include "binary_tree.hpp"

void task01()
{
    /*
     * Construct a binary tree t1:
     *          1
     *         / \
     *        2   3
     *        \  / \
     *        4 5   6
     *       / \    \
     *      7  8     9
     *              /
     *             10
     */
    myds::BinaryTree<int> emptyTree;
    myds::BinaryTree<int> t7(7, emptyTree, emptyTree);
    myds::BinaryTree<int> t8(8, emptyTree, emptyTree);
    myds::BinaryTree<int> t5(5, emptyTree, emptyTree);
    myds::BinaryTree<int> t10(10, emptyTree, emptyTree);
    myds::BinaryTree<int> t9(9, t10, emptyTree);
    myds::BinaryTree<int> t6(6, emptyTree, t9);
    myds::BinaryTree<int> t4(4, t7, t8);
    myds::BinaryTree<int> t2(2, emptyTree, t4);
    myds::BinaryTree<int> t3(3, t5, t6);
    myds::BinaryTree<int> t1(1, t2, t3);

    std::cout << "Initial tree:\n";
    std::cout << t1;
    std::cout << std::format("Size: {}\n", t1.getSize());
    std::cout << std::format("Height: {}\n", t1.getHeight());

    t1.revolute();

    std::cout << "After revolute():\n";
    std::cout << t1;
}

void task02(int a, int b)
{
    int leftBranch = 0, rightBranch = 0;
    while (a > 1 && b > 1) {
        if (a > b) {
            leftBranch += a / b;
            a %= b;
        } else {
            rightBranch += b / a;
            b %= a;
        }
    }

    if (a == 0 || b == 0) {
        std::cout << "Node does not exist!\n";
        return;
    }
    if (a == 1) {
        rightBranch += b - 1;
    } else {
        leftBranch += a - 1;
    }
    std::cout << std::format("{} {}\n", leftBranch, rightBranch);
}