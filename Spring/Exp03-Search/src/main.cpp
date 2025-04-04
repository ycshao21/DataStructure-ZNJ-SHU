#include "Console.h"
#include "S3_Solution.h"
#include "random.hpp"
#include <algorithm>
#include <conio.h>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

void Search() {
  while (true) {
    Console::Clear();
    std::cout << "��-ʵ���� �����㷨��֤�����\n\n";

    std::cout << "[1] ���������������С��ͬԪ��\n";
    std::cout << "[2] �����������������λ��\n";
    std::cout << "[3] ����������\n";
    std::cout << "[4] �˳�\n";

    char key;
    while ((key = _getch()) < '1' && key > '5')
      ;

    switch (key) {
    case '1': {
      Console::Clear();
      std::cout << "���������������С��ͬԪ��\n" << std::endl;

      std::cout << "��������������Ĵ�С: ";
      int aSize, bSize, cSize;
      while (true) {
        std::cin >> aSize >> bSize >> cSize;
        bool validInput = aSize > 0 && bSize > 0 && cSize > 0;
        Console::ClearBuffer();
        if (validInput)
          break;
        std::cout << "��������������������������Ĵ�С: ";
      }

      std::vector<int> a(aSize), b(bSize), c(cSize);
      std::cout << "�������һ�������Ԫ�أ�\n" << std::endl;
      while (true) {
        bool validInput = true;
        for (int i = 0; i < aSize; i++) {
          std::cin >> a[i];
          validInput = !std::cin.fail() && (i == 0 || a[i - 1] <= a[i]);
          if (!validInput) {
            break;
          }
        }
        Console::ClearBuffer();
        if (validInput) {
          break;
        }
        std::cout << "�������������������һ�������Ԫ�أ�\n";
      }

      std::cout << "������ڶ��������Ԫ�أ�\n";
      while (true) {
        bool validInput = true;
        for (int i = 0; i < bSize; i++) {
          std::cin >> b[i];
          validInput = !std::cin.fail() && (i == 0 || b[i - 1] <= b[i]);
          if (!validInput)
            break;
        }
        Console::ClearBuffer();
        if (validInput)
          break;
        std::cout << "������������������ڶ��������Ԫ�أ�\n";
      }

      std::cout << "����������������Ԫ�أ�\n";
      while (true) {
        bool validInput = true;
        for (int i = 0; i < cSize; i++) {
          std::cin >> c[i];
          validInput = !std::cin.fail() && (i == 0 || c[i - 1] <= c[i]);
          if (!validInput)
            break;
        }
        Console::ClearBuffer();
        if (validInput)
          break;
        std::cout << "����������������������������Ԫ�أ�\n";
      }
      std::cout << std::endl;

      findMinCommonElement(a, b, c);

      std::cout << std::endl;
      Console::WaitForKey();
      break;
    }
    case '2': {
      Console::Clear();
      std::cout << "�����������������λ��\n" << std::endl;

      std::cout << "��ֱ�������������ĳ��ȣ�2��������";
      int m = -1, n = -1;
      while (true) {
        std::cin >> m >> n;
        bool validInput = !std::cin.fail() && m > 0 && n > 0;
        Console::ClearBuffer();
        if (validInput)
          break;
        std::cout << "��������������������������ĳ��ȣ�2������: ";
      }
      std::vector<int> vec1(m), vec2(n);

      std::cout << "[1] ��������\n";
      std::cout << "[2] Ч�ʶԱ�\n" << std::endl;
      while ((key = _getch()) < '1' && key > '2')
        ;

      if (key == '1') {
        std::cout << "�������һ�������Ԫ��:" << std::endl;
        while (true) {
          bool validInput = true;
          for (int i = 0; i < m; i++) {
            std::cin >> vec1[i];
            validInput = !std::cin.fail() && (i == 0 || vec1[i - 1] <= vec1[i]);
            if (!validInput)
              break;
          }
          Console::ClearBuffer();
          if (validInput)
            break;
          std::cout << "�������������������һ�������Ԫ��:" << std::endl;
        }
        std::cout << "������ڶ��������Ԫ��: " << std::endl;
        while (true) {
          bool validInput = true;
          for (int i = 0; i < n; i++) {
            std::cin >> vec2[i];
            validInput = !std::cin.fail() && (i == 0 || vec2[i - 1] <= vec2[i]);
            if (!validInput)
              break;
          }
          Console::ClearBuffer();
          if (validInput)
            break;
          std::cout << "������������������ڶ��������Ԫ��:" << std::endl;
        }
      } else {
        std::cout << "�������ɵ�һ�����顭��\n";
        vec1 = Rand_Uniform<int>().generateVec(m, -1000000, 10000000);
        std::ranges::sort(vec1);
        std::cout << "�������ɵڶ������顭��" << std::endl;
        vec2 = Rand_Normal<int>().generateVec(n, 0, 500000);
        std::ranges::sort(vec2);
      }

      {
        std::cout << "\n���Բ����㷨" << std::endl;
        clock_t start = clock();
        Spring03::FindMedian_Linear(vec1, vec2);
        clock_t end = clock();
        if (key == '2')
          std::cout << "��ʱ" << end - start << "ms" << std::endl;
      }

      {
        std::cout << "\n���ֲ����㷨" << std::endl;
        clock_t start = clock();
        Spring03::FindMedian_Binary(vec1, vec2);
        clock_t end = clock();
        if (key == '2')
          std::cout << "��ʱ" << end - start << "ms" << std::endl;
      }

      std::cout << std::endl;
      Console::WaitForKey();
      break;
    }
    case '3': {
      std::cout << "\n����������\n";
      std::cout << "[1] ��������\n";
      std::cout << "[2] Ч�ʶԱ�\n" << std::endl;

      while ((key = _getch()) < '1' && key > '2')
        ;

      Console::Clear();
      if (key == '1') {
        Spring03::BST_Test();
      } else {
        Spring03::BST_EfficiencyTest();
        Console::WaitForKey();
      }
      break;
    }
    case '4': {
      return;
    }
    }
  }
}

int main() { Search(); }