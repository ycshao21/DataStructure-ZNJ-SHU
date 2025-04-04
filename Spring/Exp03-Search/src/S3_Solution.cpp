#include "BinarySearchTree.h"
#include "Console.h"
#include "Random.hpp"
#include <algorithm>
#include <conio.h>
#include <iostream>
#include <unordered_set>


namespace Spring03 {
void BST_Test() {
  myds::BinarySearchTree<int, int> tree;
  while (true) {
    Console::Clear();
    std::cout << "��������\n" << std::endl;
    tree.PrintKeyTree();

    std::cout << "[1] ����Ԫ��\n";
    std::cout << "[2] ɾ��Ԫ�أ������������Ԫ���滻��ɾ��Ԫ�أ�\n";
    std::cout << "[3] ɾ��Ԫ�أ�����������СԪ���滻��ɾ��Ԫ�أ�\n";
    std::cout << "[4] ɾ��Ԫ�أ����������ƶ�����������СԪ�ص���������\n";
    std::cout << "[5] ɾ��Ԫ�أ����������ƶ������������Ԫ�ص���������\n";
    std::cout << "[6] ���\n";
    std::cout << "[7] ������һ���˵�\n" << std::endl;

    char choice;
    while ((choice = _getch()) < '1' && choice > '7')
      ;

    auto getKeyFn = [&]() -> int {
      int key;
      while (true) {
        std::cin >> key;
        bool validInput = !std::cin.fail();
        Console::ClearBuffer();
        if (validInput)
          break;
        std::cout << "�����������������룺";
      }
      return key;
    };

    switch (choice) {
    case '1': {
      std::cout << "����Ԫ��\n";
      std::cout << "�����������Ԫ�صļ�����������";
      int key = getKeyFn();
      tree.Insert(key, key);
      break;
    }
    case '2': {
      std::cout << "ɾ��Ԫ�أ������������Ԫ���滻��ɾ��Ԫ�أ�\n";
      std::cout << "�������ɾ��Ԫ�صļ���";
      int key = getKeyFn();
      tree.Erase_Ver1(key);
      break;
    }
    case '3': {
      std::cout << "ɾ��Ԫ�أ�����������СԪ���滻��ɾ��Ԫ�أ�\n";
      std::cout << "�������ɾ��Ԫ�صļ���";
      int key = getKeyFn();
      tree.Erase_Ver2(key);
      break;
    }
    case '4': {
      std::cout << "ɾ��Ԫ�أ����������ƶ�����������СԪ�ص���������\n";
      std::cout << "�������ɾ��Ԫ�صļ���";
      int key = getKeyFn();
      tree.Erase_Ver3(key);
      break;
    }
    case '5': {
      std::cout << "ɾ��Ԫ�أ����������ƶ������������Ԫ�ص���������\n";
      std::cout << "�������ɾ��Ԫ�صļ���";
      int key = getKeyFn();
      tree.Erase_Ver4(key);
      break;
    }
    case '6': {
      tree.Clear();
      break;
    }
    case '7': {
      return;
    }
    }
  }
}

void BST_EfficiencyTest() {
  std::cout << "Ч�ʶԱ�\n" << std::endl;
  std::cout << "������Ԫ�ظ�����";
  int numOfElements;
  bool validInput;
  while (true) {
    std::cin >> numOfElements;
    validInput = !std::cin.fail() && numOfElements;
    Console::ClearBuffer();
    if (validInput)
      break;
    std::cout << "������������������Ԫ�ظ���: ";
  }

  std::cout << "���ڹ����������������\n" << std::endl;
  std::unordered_set<int> set;
  std::vector<std::pair<int, int>> elements;
  for (size_t i = 0; i < numOfElements;) {
    int temp = Rand_Uniform<int>()(-2 * numOfElements, 2 * numOfElements);
    if (set.find(temp) == set.end()) {
      set.insert(temp);
      elements.push_back(std::pair<int, int>{temp, temp});
      i++;
    }
  }

  myds::BinarySearchTree<int, int> tree(elements);
  std::vector<void (myds::BinarySearchTree<int, int>::*)(const int &)> methods =
      {&myds::BinarySearchTree<int, int>::Erase_Ver1,
       &myds::BinarySearchTree<int, int>::Erase_Ver2,
       &myds::BinarySearchTree<int, int>::Erase_Ver3,
       &myds::BinarySearchTree<int, int>::Erase_Ver4};

  auto eraseTestFn = [&](int idx) {
    myds::BinarySearchTree<int, int> copy(tree);
    clock_t start = clock();
    for (const auto &element : elements)
      (copy.*methods[idx - 1])(element.first); // Call erase function.

    clock_t end = clock();
    std::cout << "��ʱ" << end - start << "ms" << std::endl;
  };

  std::cout << "����һ�������������Ԫ���滻��ɾ��Ԫ��" << std::endl;
  eraseTestFn(1);
  std::cout << "������������������СԪ���滻��ɾ��Ԫ��" << std::endl;
  eraseTestFn(2);
  std::cout << "�����������������ƶ�����������СԪ�ص�������" << std::endl;
  eraseTestFn(3);
  std::cout << "�����ģ����������ƶ������������Ԫ�ص�������" << std::endl;
  eraseTestFn(4);
}
} // namespace Spring03