#include "S1_Solution.h"
#include "AdjMatWDirGraph.h"
#include "Console.h"

#include <iostream>
#include <conio.h>

namespace Spring01
{
    void AdjMatWDirGraphTest()
    {
        MyDS::AdjMatWDirGraph<int, int> g;
        while (true)
        {
            Console::Clear();
            std::cout << "春-实验一 有向网的邻接矩阵验证及拓展\n" << std::endl;

            std::cout << "边：\n";
            g.PrintEdges();
            std::cout << "\n邻接矩阵：\n";
            g.PrintAdjacentMatrix();

            std::cout << "\n[1] 插入顶点  [2] 删除顶点  [3] 插入边  [4] 删除边\n";
            std::cout << "[5] 度数      [6] 最短路径  [7] 清空    [8] 退出\n" << std::endl;

            char choice;
            while ((choice = _getch()) < '1' && choice > '8');

            switch (choice)
            {
                case '1':
                {
                    std::cout << "插入顶点\n";
                    std::cout << "请输入顶点（整数）：";
                    int v;
                    while (true)
                    {
                        std::cin >> v;
                        bool validInput = !std::cin.fail();
                        Console::ClearBuffer();
                        if (validInput)
                            break;
                        std::cout << "输入有误，请重新输入顶点（整数）：";
                    }

                    InsertVertex(g, v);

                    Console::WaitForKey();
                    break;
                }
                case '2':
                {
                    std::cout << "删除顶点\n";
                    std::cout << "请输入顶点：";
                    int v;
                    while (true)
                    {
                        std::cin >> v;
                        bool validInput = !std::cin.fail();
                        Console::ClearBuffer();
                        if (validInput)
                            break;
                        std::cout << "输入有误，请重新输入顶点：";
                    }

                    EraseVertex(g, v);

                    Console::WaitForKey();
                    break;
                }
                case '3':
                {
                    std::cout << "插入边\n";
                    std::cout << "请依次输入边的起点、终点和权值（整数）：";
                    int from, to, weight;
                    while (true)
                    {
                        std::cin >> from >> to >> weight;
                        bool validInput = !std::cin.fail();
                        Console::ClearBuffer();
                        if (validInput)
                            break;
                        std::cout << "输入有误，请重新输入边的起点、终点和权值（整数）：";
                    }

                    InsertEdge(g, from, to, weight);

                    Console::WaitForKey();
                    break;
                }
                case '4':
                {
                    std::cout << "删除边\n";
                    std::cout << "请依次输入边的起点和终点：";
                    int from, to;
                    while (true)
                    {
                        std::cin >> from >> to;
                        bool validInput = !std::cin.fail();
                        Console::ClearBuffer();
                        if (validInput)
                            break;
                        std::cout << "输入有误，请重新输入边的起点和终点：";
                    }

                    EraseEdge(g, from, to);

                    Console::WaitForKey();
                    break;
                }
                case '5':
                {
                    std::cout << "度数\n";
                    std::cout << "请输入顶点：";
                    int v;
                    while (true)
                    {
                        std::cin >> v;
                        bool validInput = !std::cin.fail();
                        Console::ClearBuffer();
                        if (validInput)
                            break;
                        std::cout << "输入有误，请重新输入顶点：";
                    }

                    Degree(g, v);

                    Console::WaitForKey();
                    break;
                }
                case '6':
                {
                    std::cout << "最短路径\n";
                    std::cout << "请输入源点和终点：";
                    int source, end;
                    while (true)
                    {
                        std::cin >> source >> end;
                        bool validInput = !std::cin.fail();
                        Console::ClearBuffer();
                        if (validInput)
                            break;
                        std::cout << "输入有误，请重新输入源点和终点：";
                    }

                    ShortestPath(g, source, end);

                    Console::WaitForKey();
                    break;
                }
                case '7':
                {
                    g.Clear();
                    break;
                }
                case '8':
                {
                    return;
                }
            }
        }
    }
}

int main()
{
    Spring01::AdjMatWDirGraphTest();
}