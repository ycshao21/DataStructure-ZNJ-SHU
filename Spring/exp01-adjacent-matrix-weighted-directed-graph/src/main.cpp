#include <array>
#include <format>
#include <iostream>


#include "AdjMatWDirGraph.hpp"
#include "solution.hpp"

void AdjMatWDirGraphTest() {
  const std::array<std::string, 8> menu = {
      "Insert Vertex", "Erase Vertex",  "Insert Edge", "Erase Edge",
      "Degree",        "Shortest Path", "Clear",       "Exit"};

  myds::AdjMatWDirGraph<int, int> g;

  while (true) {
    std::cout << "Exp01 - Adjacent Matrix Weighted Directed Graph\n";
    for (std::size_t i = 0; i < menu.size(); ++i) {
      std::cout << std::format("[{}] {} ", i + 1, menu[i]);
      if (i == menu.size() / 2) {
        std::cout << '\n';
      }
    }

    std::cout << "Edges:\n";
    g.PrintEdges();
    std::cout << "\nAdjacent Matrix:\n";
    g.PrintAdjacentMatrix();

    std::cout << "\n[1] Insert Vertex  [2] Erase Vertex  [3] Insert Edge  [4] Erase Edge\n";
    std::cout << "[5] Degree       [6] Shortest Path  [7] Clear  [8] Exit\n" << std::endl;

    switch (choice) {
    case '1': {
      std::cout << "���붥��\n";
      std::cout << "�����붥�㣨��������";
      int v;
      while (true) {
        std::cin >> v;
        bool validInput = !std::cin.fail();
        Console::ClearBuffer();
        if (validInput)
          break;
        std::cout << "�����������������붥�㣨��������";
      }

      InsertVertex(g, v);

      Console::WaitForKey();
      break;
    }
    case '2': {
      std::cout << "ɾ������\n";
      std::cout << "�����붥�㣺";
      int v;
      while (true) {
        std::cin >> v;
        bool validInput = !std::cin.fail();
        Console::ClearBuffer();
        if (validInput)
          break;
        std::cout << "�����������������붥�㣺";
      }

      EraseVertex(g, v);

      Console::WaitForKey();
      break;
    }
    case '3': {
      std::cout << "�����\n";
      std::cout << "����������ߵ���㡢�յ��Ȩֵ����������";
      int from, to, weight;
      while (true) {
        std::cin >> from >> to >> weight;
        bool validInput = !std::cin.fail();
        Console::ClearBuffer();
        if (validInput)
          break;
        std::cout << "������������������ߵ���㡢�յ��Ȩֵ����������";
      }

      InsertEdge(g, from, to, weight);

      Console::WaitForKey();
      break;
    }
    case '4': {
      std::cout << "ɾ����\n";
      std::cout << "����������ߵ������յ㣺";
      int from, to;
      while (true) {
        std::cin >> from >> to;
        bool validInput = !std::cin.fail();
        Console::ClearBuffer();
        if (validInput)
          break;
        std::cout << "������������������ߵ������յ㣺";
      }

      EraseEdge(g, from, to);

      Console::WaitForKey();
      break;
    }
    case '5': {
      std::cout << "����\n";
      std::cout << "�����붥�㣺";
      int v;
      while (true) {
        std::cin >> v;
        bool validInput = !std::cin.fail();
        Console::ClearBuffer();
        if (validInput)
          break;
        std::cout << "�����������������붥�㣺";
      }

      Degree(g, v);

      Console::WaitForKey();
      break;
    }
    case '6': {
      std::cout << "���·��\n";
      std::cout << "������Դ����յ㣺";
      int source, end;
      while (true) {
        std::cin >> source >> end;
        bool validInput = !std::cin.fail();
        Console::ClearBuffer();
        if (validInput)
          break;
        std::cout << "������������������Դ����յ㣺";
      }

      ShortestPath(g, source, end);

      Console::WaitForKey();
      break;
    }
    case '7': {
      g.Clear();
      break;
    }
    case '8': {
      return;
    }
    }
  }
}

int main() { AdjMatWDirGraphTest(); }