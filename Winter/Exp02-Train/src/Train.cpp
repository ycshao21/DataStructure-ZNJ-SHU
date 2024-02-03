#include "W2_Solution.h"
#include "Console.h"

#include <iostream>
#include <conio.h>
#include <vector>
#include <set>

namespace Winter02
{
    void Train()
    {
        while (true)
        {
            Console::Clear();
            std::cout << "冬-实验二 车厢调度\n\n";

            std::cout << "[1] 第一题\n";
            std::cout << "[2] 第二题\n";
            std::cout << "[3] 第一题的算法验证\n";
            std::cout << "[4] 第二题的算法验证\n";
            std::cout << "[5] 退出" << std::endl;

            char key;
            while ((key = _getch()) < '1' && key > '5');

            switch (key)
            {
                case '1':
                {
                    Console::Clear();
                    std::cout << "第一题\n" << std::endl;

                    std::cout << "请输入车厢数量：";
                    int numOfCars;
                    bool validInput;
                    while (true)
                    {
                        std::cin >> numOfCars;
                        validInput = !std::cin.fail() && numOfCars >= 1;
                        Console::ClearBuffer();
                        if (validInput)
                            break;
                        std::cout << "输入有误！请重新输入车厢数量：";
                    }

                    std::cout << "\n请输入主轨道右侧的车厢顺序：" << std::endl;
                    std::vector<int> outputOrder(numOfCars);
                    while (true)
                    {
                        std::set<int> checkOrder;
                        for (int i = 0; i < numOfCars; ++i)
                        {
                            std::cin >> outputOrder[i];
                            validInput = !std::cin.fail()
                                && outputOrder[i] >= 1 && outputOrder[i] <= numOfCars
                                && checkOrder.find(outputOrder[i]) == checkOrder.end();
                            if (!validInput)
                                break;
                            checkOrder.emplace(outputOrder[i]);
                        }
                        Console::ClearBuffer();
                        if (validInput)
                            break;
                        std::cout << "输入有误！请重新输入主轨道右侧的车厢顺序：" << std::endl;
                    }
                    std::cout << "\n";

                    Task01(outputOrder, numOfCars);

                    std::cout << std::endl;
                    Console::WaitForKey();
                    break;
                }
                case '2':
                {
                    Console::Clear();
                    std::cout << "第二题\n" << std::endl;

                    std::cout << "请输入车厢数量：";
                    int numOfCars;
                    bool validInput;
                    while (true)
                    {
                        std::cin >> numOfCars;
                        validInput = !std::cin.fail() && numOfCars >= 1;
                        Console::ClearBuffer();
                        if (validInput)
                            break;
                        std::cout << "输入有误！请重新输入车厢数量：";
                    }

                    std::cout << "\n请输入主轨道左侧的车厢顺序：" << std::endl;
                    std::vector<int> inputOrder(numOfCars);
                    while (true)
                    {
                        std::set<int> checkOrder;
                        for (int i = 0; i < numOfCars; ++i)
                        {
                            std::cin >> inputOrder[i];
                            validInput = !std::cin.fail()
                                && inputOrder[i] >= 1 && inputOrder[i] <= numOfCars
                                && checkOrder.find(inputOrder[i]) == checkOrder.end();
                            if (!validInput)
                                break;
                            checkOrder.emplace(inputOrder[i]);
                        }
                        Console::ClearBuffer();
                        if (validInput)
                            break;
                        std::cout << "输入有误！请重新输入主轨道左侧的车厢顺序：" << std::endl;
                    }
                    std::cout << "\n";

                    Task02(inputOrder, numOfCars);

                    std::cout << std::endl;
                    Console::WaitForKey();
                    break;
                }
                case '3':
                {
                    Console::Clear();
                    std::cout << "第一题的算法验证\n" << std::endl;

                    std::cout << "请输入车厢数量：";
                    int numOfCars;
                    bool validInput;
                    while (true)
                    {
                        std::cin >> numOfCars;
                        validInput = !std::cin.fail() && numOfCars >= 1;
                        Console::ClearBuffer();
                        if (validInput)
                            break;
                        std::cout << "输入有误！请重新输入车厢数量：";
                    }
                    std::cout << "\n";

                    Task01_Validation(numOfCars);

                    std::cout << std::endl;
                    Console::WaitForKey();
                    break;
                }
                case '4':
                {
                    Console::Clear();
                    std::cout << "第二题的算法验证\n" << std::endl;

                    std::cout << "请输入车厢数量：";
                    int numOfCars;
                    bool validInput;
                    while (true)
                    {
                        std::cin >> numOfCars;
                        validInput = !std::cin.fail() && numOfCars >= 1;
                        Console::ClearBuffer();
                        if (validInput)
                            break;
                        std::cout << "输入有误！请重新输入车厢数量：";
                    }
                    std::cout << "\n";

                    Task02_Validation(numOfCars);

                    std::cout << std::endl;
                    Console::WaitForKey();
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

int main()
{
    Winter02::Train();
}