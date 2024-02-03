#include <iostream>
#include "BinaryTree.h"

namespace Winter04
{
    void Task01()
    {
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
        MyDS::BinaryTree<int> emptyTree;
        MyDS::BinaryTree<int> t7;    t7.MakeTree(7, emptyTree, emptyTree);
        MyDS::BinaryTree<int> t8;    t8.MakeTree(8, emptyTree, emptyTree);
        MyDS::BinaryTree<int> t5;    t5.MakeTree(5, emptyTree, emptyTree);
        MyDS::BinaryTree<int> t10;   t10.MakeTree(10, emptyTree, emptyTree);
        MyDS::BinaryTree<int> t9;    t9.MakeTree(9, t10, emptyTree);
        MyDS::BinaryTree<int> t6;    t6.MakeTree(6, emptyTree, t9);
        MyDS::BinaryTree<int> t4;    t4.MakeTree(4, t7, t8);
        MyDS::BinaryTree<int> t2;    t2.MakeTree(2, emptyTree, t4);
        MyDS::BinaryTree<int> t3;    t3.MakeTree(3, t5, t6);
        MyDS::BinaryTree<int> t1;    t1.MakeTree(1, t2, t3);

        std::cout << "初始树：\n";
        std::cout << t1;

        t1.Revolute();

        std::cout << "调用revolute()函数后：\n";
        std::cout << t1;
    }

    void Task02(int a, int b)
    {
        int lBranch = 0, rBranch = 0;
        while (a > 1 && b > 1)
        {
            if (a > b)
            {
                lBranch += a / b;
                a %= b;
            }
            else
            {
                rBranch += b / a;
                b %= a;
            }
        }

        if (a == 0 || b == 0)
        {
            std::cout << "不存在该结点" << std::endl;
            return;
        }
        if (a == 1)
            rBranch += b - 1;
        else
            lBranch += a - 1;

        std::cout << lBranch << " " << rBranch << std::endl;
    }
}