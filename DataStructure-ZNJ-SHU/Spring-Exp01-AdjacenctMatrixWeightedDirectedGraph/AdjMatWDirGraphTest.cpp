#include<iostream>
#include<conio.h>
#include"data_structure/AdjMatWDirGraph.h"
#include"solutions/S1_Solutions.h"
#include"../../Tools/Settings.hpp"

namespace Menu
{
    void AdjMatWDirGraphTest() {
        static AdjMatWDirGraph<int, int> g;
        char key;
        bool validInput;
        while (true) {
            system("cls");
            HideCursor();
            std::cout << "春-实验一 有向网的邻接矩阵验证及拓展\n" << std::endl;

            std::cout << "顶点：\n";
            g.printVertices();
            std::cout << "\n边：\n";
            g.printEdges();
            std::cout << "\n邻接矩阵：\n";
            g.printAdjMatrix();

            std::cout << "\n[1] 插入顶点  [2] 删除顶点  [3] 插入边  [4] 删除边\n";
            std::cout << "[5] 度数      [6] 最短路径  [7] 清空    [8] 返回上一级菜单\n" << std::endl;

            while ((key = _getch()) < '1' && key > '8');

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

                S1::InsertVertex(g, v);

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

                S1::EraseVertex(g, v);

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

                S1::InsertEdge(g, from, to, weight);

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

                S1::EraseEdge(g, from, to);

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

                S1::Degree(g, v);

                system("pause");
                break;
            }
            case '6':
            {
                ShowCursor();
                std::cout << "最短路径\n";
                std::cout << "请输入源点和终点：";
                int source, end;
                while (true) {
                    std::cin >> source >> end;
                    validInput = !std::cin.fail();
                    ClearBuffer();
                    if (validInput) { break; }
                    std::cout << "输入有误，请重新输入源点和终点：";
                }
                HideCursor();

                S1::ShortestPath(g, source, end);

                system("pause");
                break;
            }
            case '7':
            {
                g.clear();
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