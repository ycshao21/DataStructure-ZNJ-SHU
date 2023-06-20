#include<iostream>
#include<conio.h>
#include<vector>
#include"solutions/W4_Solutions.h"
#include"../../Tools/Settings.hpp"

namespace Menu
{
    void BinaryTreeTest() {
        char key;
        bool validInput;
        while (true) {
            system("cls");
            std::cout << "冬-实验四 二叉树拓展及标记二叉树\n" << std::endl;
            std::cout << "[1] 左右子树交换" << std::endl;
            std::cout << "[2] 标记二叉树" << std::endl;
            std::cout << "[3] 返回上一级菜单" << std::endl;

            while ((key = _getch()) < '1' && key > '3');

            switch (key) {
            case '1':
            {
                system("cls");
                std::cout << "左右子树交换\n" << std::endl;

                W4::Question1();

                system("pause");
                break;
            }
            case '2':
            {
                system("cls");
                std::cout << "标记二叉树\n" << std::endl;

                ShowCursor();
                std::cout << "请输入测试组数：";
                int numOfCases;
                while (true) {
                    std::cin >> numOfCases;
                    validInput = !std::cin.fail() && numOfCases > 0;
                    ClearBuffer();
                    if (validInput) { break; }
                    std::cout << "输入有误！请重新输入测试组数：";
                }

                int a, b;
                std::cout << "请输入测试数据：" << std::endl;
                for (int i = 0; i < numOfCases; i++) {
                    while (true) {
                        std::cout << "(" << i + 1 << ") ";
                        std::cin >> a >> b;
                        validInput = !std::cin.fail() && a > 0 && b > 0;
                        ClearBuffer();
                        if (validInput) { break; }
                        std::cout << "输入有误，请重新输入！" << std::endl;
                    }
                    W4::Question2(a, b);
                }
                HideCursor();

                std::cout << std::endl;
                system("pause");
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