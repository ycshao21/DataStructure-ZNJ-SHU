#include <format>
#include <print>

#include "binary_tree.hpp"

void runTask01()
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

    std::println("Initial tree:");
    t1.print();
    std::println("Size: {}", t1.getSize());
    std::println("Height: {}", t1.getHeight());

    t1.revolute();

    std::println("After revolute():");
    t1.print();
}

void runTask02(int a, int b)
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
        std::println("Node does not exist!");
        return;
    }
    if (a == 1) {
        rightBranch += b - 1;
    } else {
        leftBranch += a - 1;
    }
    std::println("{} {}", leftBranch, rightBranch);
}