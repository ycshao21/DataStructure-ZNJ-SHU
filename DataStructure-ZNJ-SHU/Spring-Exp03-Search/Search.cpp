#include<iostream>
#include<string>
#include<vector>
#include<unordered_set>
#include<conio.h>
#include"solutions/S3_Solutions.h"
#include"../../tools/Random.hpp"
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
            std::cout << "[3] 二叉搜索树\n";
            std::cout << "[4] 返回上一级菜单" << std::endl;

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
                HideCursor();
                std::vector<int> vec1, vec2;

                std::cout << "[1] 用例测试" << "\n";
                std::cout << "[2] 效率对比" << "\n" << std::endl;
                while ((key = _getch()) < '1' && key > '2');

                if (key == '1') {
                    ShowCursor();
                    int temp;
                    std::cout << "请输入第一个数组的元素:" << std::endl;
                    while (true) {
                        for (int i = 0; i < m; i++) {
                            std::cin >> temp;
                            validInput = !std::cin.fail() && (i == 0 || vec1[i - 1] <= temp);
                            if (!validInput) { break; }
                            vec1.push_back(temp);
                        }
                        ClearBuffer();
                        if (validInput) { break; }
                        std::cout << "输入有误！请重新输入第一个数组的元素:" << std::endl;
                    }
                    std::cout << "请输入第二个数组的元素: " << std::endl;
                    while (true) {
                        for (int i = 0; i < n; i++) {
                            std::cin >> temp;
                            validInput = !std::cin.fail() && (i == 0 || vec2[i - 1] <= temp);
                            if (!validInput) { break; }
                            vec2.push_back(temp);
                        }
                        ClearBuffer();
                        if (validInput) { break; }
                        std::cout << "输入有误！请重新输入第二个数组的元素:" << std::endl;
                    }
                    HideCursor();
                } else {
                    std::cout << "正在生成第一个数组……\n";
                    vec1 = Rand_Uniform<int>().generateVec(m, -1000000, 10000000);
                    std::ranges::sort(vec1);
                    std::cout << "正在生成第二个数组……" << std::endl;
                    vec2 = Rand_Normal<int>().generateVec(n, 0, 500000);
                    std::ranges::sort(vec2);
                }

                std::cout << "\n线性查找算法" << std::endl;
                clock_t start = clock();
                S3::FindMedian_Linear(vec1, vec2);
                clock_t end = clock();
                if (key == '2') {
                    std::cout << "用时" << end - start << "ms" << std::endl;
                }

                std::cout << "\n二分查找算法" << std::endl;
                start = clock();
                S3::FindMedian_Binary(vec1, vec2);
                end = clock();
                if (key == '2') {
                    std::cout << "用时" << end - start << "ms" << std::endl;
                }

                std::cout << std::endl;
                system("pause");
                break;
            }
            case '3':
            {
                std::cout << "\n二叉搜索树\n";
                std::cout << "[1] 用例测试\n";
                std::cout << "[2] 效率对比\n" << std::endl;

                while ((key = _getch()) < '1' && key > '2');

                system("cls");
                if (key == '1') {
                    S3::BST_Test();
                } else {
                    S3::BST_EfficiencyTest();
                    system("pause");
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