#include "W4_Solution.h"
#include "Console.h"
#include <iostream>
#include <conio.h>
#include <vector>

namespace Winter04
{
    void BinaryTreeTest()
    {
        bool validInput;
        while (true)
        {
            Console::Clear();
            std::cout << "冬-实验四 二叉树拓展及标记二叉树\n\n";

            std::cout << "[1] 左右子树交换\n";
            std::cout << "[2] 标记二叉树\n";
            std::cout << "[3] 退出" << std::endl;

            char choice;
            while ((choice = _getch()) < '1' && choice > '3');

            switch (choice)
            {
                case '1':
                {
                    Console::Clear();
                    std::cout << "左右子树交换\n\n";

                    Task01();

                    Console::WaitForKey();
                    break;
                }
                case '2':
                {
                    Console::Clear();
                    std::cout << "标记二叉树\n\n";

                    std::cout << "请输入测试组数：";
                    int numOfCases;
                    while (true)
                    {
                        std::cin >> numOfCases;
                        validInput = !std::cin.fail() && numOfCases > 0;
                        Console::ClearBuffer();
                        if (validInput)
                            break;
                        std::cout << "输入有误！请重新输入测试组数：";
                    }

                    std::cout << "请输入测试数据：" << std::endl;
                    for (int i = 0; i < numOfCases; i++)
                    {
                        int a, b;
                        while (true)
                        {
                            std::cout << "(" << i + 1 << ") ";
                            std::cin >> a >> b;
                            validInput = !std::cin.fail() && a > 0 && b > 0;
                            Console::ClearBuffer();
                            if (validInput)
                                break;
                            std::cout << "输入有误，请重新输入！" << std::endl;
                        }
                        Task02(a, b);
                    }
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
    Winter04::BinaryTreeTest();
}