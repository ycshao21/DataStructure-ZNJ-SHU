#include<iostream>
#include"../data_structure/BinaryTree.h"

namespace W4
{
    void Question1(std::ostream* out) {
        /*
        * Construct a binary tree t1:
        *          1
        *         / \
        *        2   3
        *         \ / \
        *         4 5  6
        *        / \    \
        *       7   8    9
        *               /
        *              10
        */
        BinaryTree<int> emptyTree;
        BinaryTree<int> t7;    t7.makeTree(7, emptyTree, emptyTree);
        BinaryTree<int> t8;    t8.makeTree(8, emptyTree, emptyTree);
        BinaryTree<int> t5;    t5.makeTree(5, emptyTree, emptyTree);
        BinaryTree<int> t10;   t10.makeTree(10, emptyTree, emptyTree);
        BinaryTree<int> t9;    t9.makeTree(9, t10, emptyTree);
        BinaryTree<int> t6;    t6.makeTree(6, emptyTree, t9);
        BinaryTree<int> t4;    t4.makeTree(4, t7, t8);
        BinaryTree<int> t2;    t2.makeTree(2, emptyTree, t4);
        BinaryTree<int> t3;    t3.makeTree(3, t5, t6);
        BinaryTree<int> t1;    t1.makeTree(1, t2, t3);
        if (out) {
            (*out) << "初始树：\n"
                << t1;
        }

        t1.revolute();

        if (out) {
            (*out) << "调用revolute()函数后：\n"
                << t1;
        }
    }

    void Question2(int a, int b, std::ostream* out) {
        int lBranch = 0, rBranch = 0;
        while (a > 1 && b > 1) {
            if (a > b) {
                lBranch += a / b;
                a %= b;
            } else {
                rBranch += b / a;
                b %= a;
            }
        }
        if (a == 0 || b == 0) {
            if (out) {
                (*out) << "不存在该结点" << std::endl;
            }
            return;
        }
        if (a == 1) {
            rBranch += b - 1;
        } else {
            lBranch += a - 1;
        }

        if (out) {
            (*out) << lBranch << " " << rBranch << std::endl;
        }
    }
}