#include<iostream>
#include<conio.h>
#include"Tools/Settings.hpp"

namespace Menu
{
    void InterviewArrangement();
    void Train();
    void LiteratureAssistant();
    void BinaryTreeTest();
    void AdjMatWDirGraphTest();
    void AdjListWUndirGraphTest();
    void Search();
    ////void Sort();
}

int main() {
    char key;
    bool flag = true;
    HideCursor();

    while (flag) {
        system("cls");
        std::cout << "SJ结构实验\n" << std::endl;

        std::cout << "[1] 冬-实验一 面试安排\n";
        std::cout << "[2] 冬-实验二 车厢调度\n";
        std::cout << "[3] 冬-实验三 文学研究助手\n";
        std::cout << "[4] 冬-实验四 二叉树拓展及标记二叉树\n";
        std::cout << "[5] 春-实验一 有向网的邻接矩阵验证及拓展\n";
        std::cout << "[6] 春-实验二 无向网的邻接表验证和拓展\n";
        std::cout << "[7] 春-实验三 查找算法验证及设计\n";
        std::cout << "[8] 春-实验四 排序算法验证及设计\n";
        std::cout << "[9] 退出" << std::endl;

        while ((key = _getch()) < '1' || key > '9');

        switch (key) {
        case '1': { Menu::InterviewArrangement();    break; }
        case '2': { Menu::Train();                   break; }
        case '3': { Menu::LiteratureAssistant();     break; }
        case '4': { Menu::BinaryTreeTest();          break; }
        case '5': { Menu::AdjMatWDirGraphTest();     break; }
        case '6': { Menu::AdjListWUndirGraphTest();  break; }
        case '7': { Menu::Search();                  break; }
        case '8': { break; }  // Unfinished
        case '9': { flag = false; break; }
        }
    }
}