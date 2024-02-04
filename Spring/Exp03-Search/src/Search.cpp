#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include "S3_Solution.h"
#include "Console.h"
#include "Random.hpp"

namespace Spring03
{
    void Search()
    {
        while (true)
        {
            Console::Clear();
            std::cout << "春-实验三 查找算法验证及设计\n\n";

            std::cout << "[1] 查找三个数组的最小共同元素\n";
            std::cout << "[2] 求两个有序数组的中位数\n";
            std::cout << "[3] 二叉搜索树\n";
            std::cout << "[4] 退出" << std::endl;

            char key;
            while ((key = _getch()) < '1' && key > '5');

            switch (key)
            {
                case '1':
                {
                    Console::Clear();
                    std::cout << "查找三个数组的最小共同元素\n" << std::endl;

                    std::cout << "请输入三个数组的大小: ";
                    int aSize, bSize, cSize;
                    while (true)
                    {
                        std::cin >> aSize >> bSize >> cSize;
                        bool validInput = aSize > 0 && bSize > 0 && cSize > 0;
                        Console::ClearBuffer();
                        if (validInput)
                            break;
                        std::cout << "输入有误！请重新输入三个数组的大小: ";
                    }

                    std::vector<int> a(aSize), b(bSize), c(cSize);
                    std::cout << "请输入第一个数组的元素：" << std::endl;
                    while (true)
                    {
                        bool validInput = true;
                        for (int i = 0; i < aSize; i++)
                        {
                            std::cin >> a[i];
                            validInput = !std::cin.fail() && (i == 0 || a[i - 1] <= a[i]);
                            if (!validInput)
                                break;
                        }
                        Console::ClearBuffer();
                        if (validInput)
                            break;
                        std::cout << "输入有误！请重新输入第一个数组的元素：" << std::endl;
                    }

                    std::cout << "请输入第二个数组的元素：" << std::endl;
                    while (true)
                    {
                        bool validInput = true;
                        for (int i = 0; i < bSize; i++)
                        {
                            std::cin >> b[i];
                            validInput = !std::cin.fail() && (i == 0 || b[i - 1] <= b[i]);
                            if (!validInput)
                                break;
                        }
                        Console::ClearBuffer();
                        if (validInput)
                            break;
                        std::cout << "输入有误！请重新输入第二个数组的元素：" << std::endl;
                    }

                    std::cout << "请输入第三个数组的元素：" << std::endl;
                    while (true)
                    {
                        bool validInput = true;
                        for (int i = 0; i < cSize; i++)
                        {
                            std::cin >> c[i];
                            validInput = !std::cin.fail() && (i == 0 || c[i - 1] <= c[i]);
                            if (!validInput)
                                break;
                        }
                        Console::ClearBuffer();
                        if (validInput)
                            break;
                        std::cout << "输入有误！请重新输入第三个数组的元素：" << std::endl;
                    }
                    std::cout << std::endl;

                    Spring03::FindMinCommonElement(a, b, c);

                    std::cout << std::endl;
                    Console::WaitForKey();
                    break;
                }
                case '2':
                {
                    Console::Clear();
                    std::cout << "求两个有序数组的中位数\n" << std::endl;

                    std::cout << "请分别输入两个数组的长度（2个数）：";
                    int m = -1, n = -1;
                    while (true)
                    {
                        std::cin >> m >> n;
                        bool validInput = !std::cin.fail() && m > 0 && n > 0;
                        Console::ClearBuffer();
                        if (validInput)
                            break;
                        std::cout << "输入有误！请重新输入两个数组的长度（2个数）: ";
                    }
                    std::vector<int> vec1(m), vec2(n);

                    std::cout << "[1] 用例测试" << "\n";
                    std::cout << "[2] 效率对比" << "\n" << std::endl;
                    while ((key = _getch()) < '1' && key > '2');

                    if (key == '1')
                    {
                        std::cout << "请输入第一个数组的元素:" << std::endl;
                        while (true)
                        {
                            bool validInput = true;
                            for (int i = 0; i < m; i++)
                            {
                                std::cin >> vec1[i];
                                validInput = !std::cin.fail() && (i == 0 || vec1[i - 1] <= vec1[i]);
                                if (!validInput)
                                    break;
                            }
                            Console::ClearBuffer();
                            if (validInput)
                                break;
                            std::cout << "输入有误！请重新输入第一个数组的元素:" << std::endl;
                        }
                        std::cout << "请输入第二个数组的元素: " << std::endl;
                        while (true)
                        {
                            bool validInput = true;
                            for (int i = 0; i < n; i++)
                            {
                                std::cin >> vec2[i];
                                validInput = !std::cin.fail() && (i == 0 || vec2[i - 1] <= vec2[i]);
                                if (!validInput)
                                    break;
                            }
                            Console::ClearBuffer();
                            if (validInput)
                                break;
                            std::cout << "输入有误！请重新输入第二个数组的元素:" << std::endl;
                        }
                    }
                    else
                    {
                        std::cout << "正在生成第一个数组……\n";
                        vec1 = Rand_Uniform<int>().generateVec(m, -1000000, 10000000);
                        std::ranges::sort(vec1);
                        std::cout << "正在生成第二个数组……" << std::endl;
                        vec2 = Rand_Normal<int>().generateVec(n, 0, 500000);
                        std::ranges::sort(vec2);
                    }

                    {
                        std::cout << "\n线性查找算法" << std::endl;
                        clock_t start = clock();
                        Spring03::FindMedian_Linear(vec1, vec2);
                        clock_t end = clock();
                        if (key == '2')
                            std::cout << "用时" << end - start << "ms" << std::endl;
                    }

                    {
                        std::cout << "\n二分查找算法" << std::endl;
                        clock_t start = clock();
                        Spring03::FindMedian_Binary(vec1, vec2);
                        clock_t end = clock();
                        if (key == '2')
                            std::cout << "用时" << end - start << "ms" << std::endl;
                    }

                    std::cout << std::endl;
                    Console::WaitForKey();
                    break;
                }
                case '3':
                {
                    std::cout << "\n二叉搜索树\n";
                    std::cout << "[1] 用例测试\n";
                    std::cout << "[2] 效率对比\n" << std::endl;

                    while ((key = _getch()) < '1' && key > '2');

                    Console::Clear();
                    if (key == '1')
                    {
                        Spring03::BST_Test();
                    }
                    else
                    {
                        Spring03::BST_EfficiencyTest();
                        Console::WaitForKey();
                    }
                    break;
                }
                case '4':
                {
                    return;
                }
            }
        }
    }
}

int main()
{
    Spring03::Search();
}