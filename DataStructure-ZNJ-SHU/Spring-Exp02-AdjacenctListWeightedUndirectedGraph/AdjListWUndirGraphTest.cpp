#include<iostream>
#include<conio.h>
#include"data_structure/AdjListWUndirGraph.h"
#include"solutions/S2_Solutions.h"
#include"../Tools/Settings.hpp"

namespace Menu
{
    void AdjListWUndirGraphTest() {
        static AdjListWUndirGraph<int, int> g;
        char key;
        bool validInput;
        while (true) {
            system("cls");
            HideCursor();
            std::cout << "春-实验二 无向网的邻接表验证和拓展\n" << std::endl;

            std::cout << "边：\n";
            g.printEdges();
            std::cout << "\n邻接表：\n";
            g.printAdjList();

            std::cout << "\n[1] 插入顶点  [2] 删除顶点  [3] 插入边  [4] 删除边\n";
            std::cout << "[5] 度数  [6] 连通分量数  [7] 最小生成树  [8] 清空  [9] 返回上一级菜单\n" << std::endl;

            while ((key = _getch()) < '1' && key > '9');

            switch (key) {
            case '1':
            {
                ShowCursor();
                std::cout << "插入顶点\n";
                std::cout << "请输入顶点（整数）：";
                int v;
                while (true) {
                    std::cin >> v;
                    validInput = !std::cin.fail();
                    ClearBuffer();
                    if (validInput) { break; }
                    std::cout << "输入有误，请重新输入顶点（整数）：";
                }
                HideCursor();

                S2::InsertVertex(g, v);

                system("pause");
                break;
            }
            case '2':
            {
                ShowCursor();
                std::cout << "删除顶点\n";
                std::cout << "请输入顶点：";
                int v;
                while (true) {
                    std::cin >> v;
                    validInput = !std::cin.fail();
                    ClearBuffer();
                    if (validInput) { break; }
                    std::cout << "输入有误，请重新输入顶点：";
                }
                HideCursor();

                S2::EraseVertex(g, v);

                system("pause");
                break;
            }
            case '3':
            {
                ShowCursor();
                std::cout << "插入边\n";
                std::cout << "请依次输入边的起点、终点和权值（整数）：";
                int from, to, weight;
                while (true) {
                    std::cin >> from >> to >> weight;
                    validInput = !std::cin.fail();
                    ClearBuffer();
                    if (validInput) { break; }
                    std::cout << "输入有误，请重新输入边的起点、终点和权值（整数）：";
                }
                HideCursor();

                S2::InsertEdge(g, from, to, weight);

                system("pause");
                break;
            }
            case '4':
            {
                ShowCursor();
                std::cout << "删除边\n";
                std::cout << "请依次输入边的起点和终点：";
                int from, to;
                while (true) {
                    std::cin >> from >> to;
                    validInput = !std::cin.fail();
                    ClearBuffer();
                    if (validInput) { break; }
                    std::cout << "输入有误，请重新输入边的起点和终点：";
                }
                HideCursor();

                S2::EraseEdge(g, from, to);

                system("pause");
                break;
            }
            case '5':
            {
                ShowCursor();
                std::cout << "度数\n";
                std::cout << "请输入顶点：";
                int v;
                while (true) {
                    std::cin >> v;
                    validInput = !std::cin.fail();
                    ClearBuffer();
                    if (validInput) { break; }
                    std::cout << "输入有误，请重新输入顶点：";
                }
                HideCursor();

                S2::Degree(g, v);

                system("pause");
                break;
            }
            case '6':
            {
                std::cout << "连通分量数\n";
                S2::ConnectedComponent(g);
                system("pause");
                break;
            }

            case '7':
            {
                ShowCursor();
                std::cout << "最小生成树\n";
                int source, end;
                while (true) {
                    std::cin >> source >> end;
                    validInput = !std::cin.fail();
                    ClearBuffer();
                    if (validInput) { break; }
                    std::cout << "输入有误，请重新输入源点和终点：";
                }
                HideCursor();

                S2::MinimumSpanningTree(g);

                system("pause");
                break;
            }
            case '8':
            {
                g.clear();
                break;
            }
            case '9':
            {
                return;
            }
            }
        }
    }
}