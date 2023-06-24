#include<iostream>
#include<string>
#include<vector>
#include<conio.h>
#include"solutions/S3_Solutions.h"
#include"solutions/S3_EfficiencyTest.h"
#include"../Tools/Settings.hpp"

namespace Menu
{
    void Search()
    {
        char key;
        bool validInput;
        while (true) {
            system("cls");
            std::cout << "春-实验三 查找算法验证及设计\n" << std::endl;

            std::cout << "[1] 查找三个数组的最小共同元素\n";
            std::cout << "[2] 求两个有序数组的中位数\n";
            std::cout << "[3] 二叉排序树\n";
            std::cout << "[4] 第二题效率对比\n";
            std::cout << "[5] 返回上一级菜单" << std::endl;

            while ((key = _getch()) < '1' && key > '5');

            switch (key) {
            case '1':
            {
                system("cls");
                std::cout << "查找三个数组的最小共同元素\n" << std::endl;

                ShowCursor();
                std::cout << "请输入三个数组的大小: ";
                int aSize, bSize, cSize;
                while (true) {
                    std::cin >> aSize >> bSize >> cSize;
                    validInput = aSize > 0 && bSize > 0 && cSize > 0;
                    ClearBuffer();
                    if (validInput) { break; }
                    std::cout << "输入有误！请重新输入三个数组的大小: ";
                }

                std::vector<int> a(aSize), b(bSize), c(cSize);
                std::cout << "请输入第一个数组的元素：" << std::endl;
                while (true) {
                    for (auto& e : a) {
                        std::cin >> e;
                        validInput = !std::cin.fail();
                        if (!validInput) { break; }
                    }
                    ClearBuffer();
                    if (validInput) { break; }
                    std::cout << "输入有误！请重新输入第一个数组的元素：" << std::endl;
                }

                std::cout << "请输入第二个数组的元素：" << std::endl;
                while (true) {
                    for (auto& e : b) {
                        std::cin >> e;
                        validInput = !std::cin.fail();
                        if (!validInput) { break; }
                    }
                    ClearBuffer();
                    if (validInput) { break; }
                    std::cout << "输入有误！请重新输入第二个数组的元素：" << std::endl;
                }

                std::cout << "请输入第三个数组的元素：" << std::endl;
                while (true) {
                    for (auto& e : c) {
                        std::cin >> e;
                        validInput = !std::cin.fail();
                        if (!validInput) { break; }
                    }
                    ClearBuffer();
                    if (validInput) { break; }
                    std::cout << "输入有误！请重新输入第三个数组的元素：" << std::endl;
                }
                HideCursor();
                std::cout << std::endl;

                S3::FindMinCommonElement(a, b, c);

                std::cout << std::endl;
                system("pause");
                break;
            }
            case '2':
            {
                system("cls");
                std::cout << "求两个有序数组的中位数\n" << std::endl;

                ShowCursor();
                std::cout << "请分别输入两个数组的长度（2个数）：";
                int m = -1, n = -1;
                while (true) {
                    std::cin >> m >> n;
                    validInput = !std::cin.fail() && m > 0 && n > 0;
                    ClearBuffer();
                    if (validInput) { break; }
                    std::cout << "输入有误！请重新输入两个数组的长度（2个数）: ";
                }

                std::vector<int> vec1(m), vec2(n);
                std::cout << "请输入第一个数组的元素:" << std::endl;
                while (true) {
                    for (int i = 0; i < m; i++) {
                        std::cin >> vec1[i];
                        validInput = !std::cin.fail() && (i == 0 || vec1[i - 1] <= vec1[i]);
                        if (!validInput) { break; }
                    }
                    ClearBuffer();
                    if (validInput) { break; }
                    std::cout << "输入有误！请重新输入第一个数组的元素:" << std::endl;
                }
                std::cout << "请输入第二个数组的元素: " << std::endl;
                while (true) {
                    for (int i = 0; i < n; i++) {
                        std::cin >> vec2[i];
                        validInput = !std::cin.fail() && (i == 0 || vec2[i - 1] <= vec2[i]);
                        if (!validInput) { break; }
                    }
                    ClearBuffer();
                    if (validInput) { break; }
                    std::cout << "输入有误！请重新输入第二个数组的元素:" << std::endl;
                }
                HideCursor();

                std::cout << "\n线性查找：" << std::endl;
                S3::FindMedian_Linear(vec1, vec2);
                std::cout << "\n二分查找：" << std::endl;
                S3::FindMedian_Binary(vec1, vec2);

                std::cout << std::endl;
                system("pause");
                break;
            }
            case '3':
            {
                system("cls");
                ShowCursor();
                HideCursor();

                system("pause");
                break;
            }
            case '4':
            {
                system("cls");
                std::cout << "第二题效率对比\n" << std::endl;

                ShowCursor();
                std::cout << "请分别输入两个数组的长度（2个数）：";
                size_t m = 0, n = 0;
                while (true) {
                    std::cin >> m >> n;
                    validInput = !std::cin.fail() && m > 0 && n > 0;
                    ClearBuffer();
                    if (validInput) { break; }
                    std::cout << "输入有误！请重新输入两个数组的长度（2个数）: ";
                }
                HideCursor();

                S3::Q2_EfficiencyTest<int>(m, n);

                system("pause");
                break;
            }
            case '5':
            {
                return;
            }
            }
        }
    }
}