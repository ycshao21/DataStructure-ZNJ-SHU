#include <iostream>
#include <conio.h>
#include <vector>
#include <algorithm>
#include <ranges>
#include "S4_QuickSort.h"
#include "S4_DNASort.h"
#include "Console.h"
#include "Random.hpp"

namespace Spring04
{
    void Sort()
    {
        while (true)
        {
            Console::Clear();
            std::cout << "春-实验四 排序算法验证及设计\n" << std::endl;

            std::cout << "[1] 快速排序改进\n";
            std::cout << "[2] DNA排序\n";
            std::cout << "[3] 返回上一级菜单" << std::endl;

            char key;
            while ((key = _getch()) < '1' && key > '3');

            switch (key)
            {
            case '1':
            {
                Console::Clear();
                std::cout << "快速排序改进\n" << std::endl;

                std::cout << "请输入数组的大小：";
                int size;
                while (true)
                {
                    std::cin >> size;
                    bool validInput = !std::cin.fail() && size > 0;
                    Console::ClearBuffer();
                    if (validInput)
                        break;
                    std::cout << "输入有误！请重新输入数组的大小：";
                }
                std::vector<int> vec(size);

                std::cout << "[1] 用例测试\n";
                std::cout << "[2] 效率对比\n" << std::endl;
                while ((key = _getch()) < '1' && key > '2');

                if (key == '1')
                {
                    std::cout << "请输入数组元素：" << std::endl;
                    while (true)
                    {
                        bool validInput;
                        for (int i = 0; i < size; i++)
                        {
                            std::cin >> vec[i];
                            validInput = !std::cin.fail();
                            if (!validInput)
                                break;
                        }
                        Console::ClearBuffer();
                        if (validInput)
                            break;
                        std::cout << "输入有误！请重新输入数组元素：" << std::endl;
                    }
                }
                else
                {
                    std::cout << "正在生成数组元素……" << std::endl;
                    vec = Rand_Uniform<int>().generateVec(size, -20000, 20000);
                }

                std::vector<int> vec1(vec);
                {
                    std::cout << "\nstd::sort" << std::endl;

                    clock_t start = clock();
                    std::ranges::sort(vec1);
                    clock_t end = clock();

                    if (key == '1')
                    {
                        for (int e : vec1)
                            std::cout << e << " ";
                        std::cout << std::endl;
                    }
                    else
                    {
                        std::cout << "用时: " << end - start << "ms" << std::endl;
                    }
                }

                {
                    std::cout << "\nQuickSort\n";
                    std::vector<int> vec2(vec);

                    clock_t start = clock();
                    Spring04::QuickSort(vec2, 0, (int)vec2.size() - 1);
                    clock_t end = clock();
                    if (key == '1')
                    {
                        for (int e : vec2)
                            std::cout << e << " ";

                        std::cout << std::endl;
                    }
                    else
                    {
                        std::cout << "用时: " << end - start << "ms" << std::endl;
                    }

                    if (vec1 == vec2)
                        std::cout << "排序正确" << std::endl;
                    else
                        std::cout << "排序错误" << std::endl;
                }

                {
                    std::cout << "\nQuickSort_MedianOfThree\n";
                    std::vector<int> vec3(vec);

                    clock_t start = clock();
                    Spring04::QuickSort(vec3, 0, (int)vec3.size() - 1);
                    clock_t end = clock();

                    if (key == '1')
                    {
                        for (int e : vec3)
                            std::cout << e << " ";

                        std::cout << std::endl;
                    }
                    else
                    {
                        std::cout << "用时: " << end - start << "ms" << std::endl;
                    }

                    if (vec1 == vec3)
                        std::cout << "排序正确" << std::endl;
                    else
                        std::cout << "排序错误" << std::endl;
                }

                Console::WaitForKey();
                break;
            }
            case '2':
            {
                Console::Clear();
                std::cout << "DNA排序\n" << std::endl;

                std::cout << "请输入DNA字符串的数目n与长度m：";
                int n, m;
                while (true)
                {
                    std::cin >> n >> m;
                    bool validInput = !std::cin.fail() && n > 0 && m > 0;
                    Console::ClearBuffer();
                    if (validInput)
                        break;
                    std::cout << "输入有误！请重新输入DNA字符串的数目n与长度m：";
                }

                std::cout << "请输入DNA字符串" << std::endl;
                std::vector<std::string> dnaVec(n);
                for (int i = 0; i < n; i++)
                {
                    while (true)
                    {
                        std::cout << "(" << i + 1 << ") ";
                        std::cin >> dnaVec[i];
                        if (dnaVec[i].size() == m)
                        {
                            bool validInput = true;
                            for (char c : dnaVec[i])
                            {
                                if (c != 'A' && c != 'C' && c != 'G' && c != 'T')
                                {
                                    validInput = false;
                                    break;
                                }
                            }
                            if (validInput)
                                break;
                        }
                        Console::ClearBuffer();
                        std::cout << "输入有误，请重新输入！" << std::endl;
                    }
                }
                std::cout << std::endl;

                Spring04::DNASort(dnaVec);

                std::cout << std::endl;
                Console::WaitForKey();
                break;
            }
            case '3':
            {
                return;
            }
            }
        }
    }
}

int main()
{
    Spring04::Sort();
}