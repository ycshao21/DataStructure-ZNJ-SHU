#include "W1_Solution.h"

#include "Console.h"
#include <iostream>
#include <conio.h>

namespace Winter01
{
    void InterviewArrangement()
    {
        while (true)
        {
            Console::Clear();
            std::cout << "冬-实验一 面试安排\n\n";

            std::cout << "[1] 第一题\n";
            std::cout << "[2] 第二题\n";
            std::cout << "[3] 退出" << std::endl;

            char choice;
            while ((choice = _getch()) < '1' && choice > '3');

            if (choice == '3')
                return;

            Console::Clear();
            if (choice == '1')
                std::cout << "第一题：\n";
            else
                std::cout << "第二题：\n";

            std::cout << "请输入N，K，M的值：";
            int N, K, M;
            while (true)
            {
                std::cin >> N >> K >> M;
                bool isValid = !std::cin.fail() && N > 0 && K > 0 && M > 0;
                Console::ClearBuffer();
                if (isValid)
                    break;
                std::cout << "输入有误！请重新输入N，K，M的值：";
            }

            if (choice == '1')
                Task01(N, K, M);
            else
                Task02(N, K, M);

            std::cout << std::endl;
            Console::WaitForKey();
        }
    }
}

int main()
{
    Winter01::InterviewArrangement();
}