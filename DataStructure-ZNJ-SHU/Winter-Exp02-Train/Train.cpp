#include<iostream>
#include<conio.h>
#include<vector>
#include<set>
#include"solutions/W2_Solutions.h"
#include"solutions/W2_Validation.h"
#include"../../Tools/Settings.hpp"

namespace Menu
{
    void Train() {
        char key;
        bool validInput;
        while (true) {
            system("cls");
            std::cout << "冬-实验二 车厢调度\n" << std::endl;
            std::cout << "[1] 第一题\n";
            std::cout << "[2] 第二题\n";
            std::cout << "[3] 第一题的算法验证\n";
            std::cout << "[4] 第二题的算法验证\n";
            std::cout << "[5] 返回上一级菜单" << std::endl;

            while ((key = _getch()) < '1' && key > '5');

            switch (key) {
            case '1':
            {
                system("cls");
                std::cout << "第一题\n" << std::endl;

                ShowCursor();
                std::cout << "请输入车厢数量：";
                int numOfCars;
                while (true) {
                    std::cin >> numOfCars;
                    validInput = !std::cin.fail() && numOfCars >= 1;
                    ClearBuffer();
                    if (validInput) { break; }
                    std::cout << "输入有误！请重新输入车厢数量：";
                }

                std::cout << "\n请输入主轨道右侧的车厢顺序：" << std::endl;
                std::vector<int> outputOrder(numOfCars);
                while (true) {
                    std::set<int> checkOrder;
                    for (int i = 0; i < numOfCars; ++i) {
                        std::cin >> outputOrder[i];
                        validInput = !std::cin.fail()
                            && outputOrder[i] >= 1 && outputOrder[i] <= numOfCars
                            && checkOrder.find(outputOrder[i]) == checkOrder.end();
                        if (!validInput) { break; }
                        checkOrder.emplace(outputOrder[i]);
                    }
                    ClearBuffer();
                    if (validInput) { break; }
                    std::cout << "输入有误！请重新输入主轨道右侧的车厢顺序：" << std::endl;
                }
                HideCursor();
                std::cout << "\n";

                W2::Question1(outputOrder, numOfCars);

                std::cout << std::endl;
                system("pause");
                break;
            }
            case '2':
            {
                system("cls");
                std::cout << "第二题\n" << std::endl;

                ShowCursor();
                std::cout << "请输入车厢数量：";
                int numOfCars;
                while (true) {
                    std::cin >> numOfCars;
                    validInput = !std::cin.fail() && numOfCars >= 1;
                    ClearBuffer();
                    if (validInput) { break; }
                    std::cout << "输入有误！请重新输入车厢数量：";
                }

                std::cout << "\n请输入主轨道左侧的车厢顺序：" << std::endl;
                std::vector<int> inputOrder(numOfCars);
                while (true) {
                    std::set<int> checkOrder;
                    for (int i = 0; i < numOfCars; ++i) {
                        std::cin >> inputOrder[i];
                        validInput = !std::cin.fail()
                            && inputOrder[i] >= 1 && inputOrder[i] <= numOfCars
                            && checkOrder.find(inputOrder[i]) == checkOrder.end();
                        if (!validInput) { break; }
                        checkOrder.emplace(inputOrder[i]);
                    }
                    ClearBuffer();
                    if (validInput) { break; }
                    std::cout << "输入有误！请重新输入主轨道左侧的车厢顺序：" << std::endl;
                }
                HideCursor();
                std::cout << "\n";

                W2::Question2(inputOrder, numOfCars);

                std::cout << std::endl;
                system("pause");
                break;
            }
            case '3':
            {
                system("cls");
                std::cout << "第一题的算法验证\n" << std::endl;

                ShowCursor();
                std::cout << "请输入车厢数量：";
                int numOfCars;
                while (true) {
                    std::cin >> numOfCars;
                    validInput = !std::cin.fail() && numOfCars >= 1;
                    ClearBuffer();
                    if (validInput) { break; }
                    std::cout << "输入有误！请重新输入车厢数量：";
                }
                HideCursor();
                std::cout << "\n";

                W2::Q1_Validation(numOfCars);

                std::cout << std::endl;
                system("pause");
                break;
            }
            case '4':
            {
                system("cls");
                std::cout << "第二题的算法验证\n" << std::endl;

                ShowCursor();
                std::cout << "请输入车厢数量：";
                int numOfCars;
                while (true) {
                    std::cin >> numOfCars;
                    validInput = !std::cin.fail() && numOfCars >= 1;
                    ClearBuffer();
                    if (validInput) { break; }
                    std::cout << "输入有误！请重新输入车厢数量：";
                }
                HideCursor();
                std::cout << "\n";

                W2::Q2_Validation(numOfCars);

                std::cout << std::endl;
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