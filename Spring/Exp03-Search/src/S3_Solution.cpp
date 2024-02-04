#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <conio.h>
#include "BinarySearchTree.h"
#include "Console.h"
#include "Random.hpp"

namespace Spring03
{
    void BST_Test()
    {
        MyDS::BinarySearchTree<int, int> tree;
        while (true)
        {
            Console::Clear();
            std::cout << "用例测试\n" << std::endl;
            tree.PrintKeyTree();

            std::cout << "[1] 插入元素\n";
            std::cout << "[2] 删除元素（用左子树最大元素替换待删除元素）\n";
            std::cout << "[3] 删除元素（用右子树最小元素替换待删除元素）\n";
            std::cout << "[4] 删除元素（将左子树移动到右子树最小元素的左子树）\n";
            std::cout << "[5] 删除元素（将右子树移动到左子树最大元素的右子树）\n";
            std::cout << "[6] 清空\n";
            std::cout << "[7] 返回上一级菜单\n" << std::endl;

            char choice;
            while ((choice = _getch()) < '1' && choice > '7');

            auto getKeyFn = [&]()->int {
                int key;
                while (true)
                {
                    std::cin >> key;
                    bool validInput = !std::cin.fail();
                    Console::ClearBuffer();
                    if (validInput)
                        break;
                    std::cout << "输入有误，请重新输入：";
                }
                return key;
            };

            switch (choice)
            {
                case '1':
                {
                    std::cout << "插入元素\n";
                    std::cout << "请输入待插入元素的键（整数）：";
                    int key = getKeyFn();
                    tree.Insert(key, key);
                    break;
                }
                case '2':
                {
                    std::cout << "删除元素（用左子树最大元素替换待删除元素）\n";
                    std::cout << "请输入待删除元素的键：";
                    int key = getKeyFn();
                    tree.Erase_Ver1(key);
                    break;
                }
                case '3':
                {
                    std::cout << "删除元素（用右子树最小元素替换待删除元素）\n";
                    std::cout << "请输入待删除元素的键：";
                    int key = getKeyFn();
                    tree.Erase_Ver2(key);
                    break;
                }
                case '4':
                {
                    std::cout << "删除元素（将左子树移动到右子树最小元素的左子树）\n";
                    std::cout << "请输入待删除元素的键：";
                    int key = getKeyFn();
                    tree.Erase_Ver3(key);
                    break;
                }
                case '5':
                {
                    std::cout << "删除元素（将右子树移动到左子树最大元素的右子树）\n";
                    std::cout << "请输入待删除元素的键：";
                    int key = getKeyFn();
                    tree.Erase_Ver4(key);
                    break;
                }
                case '6':
                {
                    tree.Clear();
                    break;
                }
                case '7':
                {
                    return;
                }
            }
        }
    }

    void BST_EfficiencyTest()
    {
        std::cout << "效率对比\n" << std::endl;
        std::cout << "请输入元素个数：";
        int numOfElements;
        bool validInput;
        while (true)
        {
            std::cin >> numOfElements;
            validInput = !std::cin.fail() && numOfElements;
            Console::ClearBuffer();
            if (validInput)
                break;
            std::cout << "输入有误！请重新输入元素个数: ";
        }

        std::cout << "正在构造二叉搜索树……\n" << std::endl;
        std::unordered_set<int> set;
        std::vector<std::pair<int, int>> elements;
        for (size_t i = 0; i < numOfElements;)
        {
            int temp = Rand_Uniform<int>()(-2 * numOfElements, 2 * numOfElements);
            if (set.find(temp) == set.end())
            {
                set.insert(temp);
                elements.push_back(std::pair<int, int>{ temp, temp });
                i++;
            }
        }

        MyDS::BinarySearchTree<int, int> tree(elements);
        std::vector<void(MyDS::BinarySearchTree<int, int>::*)(const int&)> methods = {
            &MyDS::BinarySearchTree<int, int>::Erase_Ver1, &MyDS::BinarySearchTree<int, int>::Erase_Ver2,
            &MyDS::BinarySearchTree<int, int>::Erase_Ver3, &MyDS::BinarySearchTree<int, int>::Erase_Ver4
        };

        auto eraseTestFn = [&](int idx) {
            MyDS::BinarySearchTree<int, int> copy(tree);
            clock_t start = clock();
            for (const auto& element : elements)
                (copy.*methods[idx - 1])(element.first);  // Call erase function.

            clock_t end = clock();
            std::cout << "用时" << end - start << "ms" << std::endl;
        };

        std::cout << "方法一：用左子树最大元素替换待删除元素" << std::endl;
        eraseTestFn(1);
        std::cout << "方法二：用右子树最小元素替换待删除元素" << std::endl;
        eraseTestFn(2);
        std::cout << "方法三：将左子树移动到右子树最小元素的左子树" << std::endl;
        eraseTestFn(3);
        std::cout << "方法四：将右子树移动到左子树最大元素的右子树" << std::endl;
        eraseTestFn(4);
    }
}