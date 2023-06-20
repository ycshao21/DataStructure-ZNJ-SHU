#include<iostream>
#include<conio.h>
#include"solutions/W1_Solutions.h"
#include"../../Tools/Settings.hpp"

namespace Menu
{
    void InterviewArrangement() {
        char key;
        bool validInput;
        while (true) {
            system("cls");
            std::cout << "冬-实验一 面试安排\n" << std::endl;

            std::cout << "[1] 第一题\n";
            std::cout << "[2] 第二题\n";
            std::cout << "[3] 返回上一级菜单" << std::endl;

            while ((key = _getch()) < '1' && key > '3');

            switch (key) {
            case '1':
            {
                system("cls");
                std::cout << "第一题\n" << std::endl;

                ShowCursor();
                std::cout << "请输入N，K，M的值：";
                int N, K, M;
                while (true) {
                    std::cin >> N >> K >> M;
                    validInput = !std::cin.fail() && N >= 0 && K > 0 && M > 0;
                    ClearBuffer();
                    if (validInput) { break; }
                    std::cout << "输入有误！请重新输入N，K，M的值：";
                }
                HideCursor();

                W1::Question1(N, K, M);

                std::cout << std::endl;
                system("pause");
                break;
            }
            case '2':
            {
                system("cls");
                std::cout << "第二题\n" << std::endl;

                ShowCursor();
                std::cout << "请输入N，K，M的值：";
                int N, K, M;
                while (true) {
                    std::cin >> N >> K >> M;
                    validInput = !std::cin.fail() && N >= 0 && K > 0 && M > 0;
                    ClearBuffer();
                    if (validInput) { break; }
                    std::cout << "输入有误！请重新输入N，K，M的值：";
                }
                HideCursor();

                W1::Question2(N, K, M);

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