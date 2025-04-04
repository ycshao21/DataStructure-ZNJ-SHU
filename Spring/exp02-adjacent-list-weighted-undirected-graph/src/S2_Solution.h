#pragma once
#include "AdjListWUndirGraph.h"
#include <format>

namespace Spring02 {
template <class VertTy, class WeightTy, WeightTy infinity>
void InsertVertex(myds::AdjListWUndirGraph<VertTy, WeightTy, infinity> &g,
                  const VertTy &vert) {
  try {
    g.InsertVertex(vert);
    std::cout << "����ɹ���" << std::endl;
  } catch (VertexAlreadyExists) {
    std::cout << "�ö����Ѵ��ڣ��޷�����"
              << std::endl;
  }
}

template <class VertTy, class WeightTy, WeightTy infinity>
void EraseVertex(myds::AdjListWUndirGraph<VertTy, WeightTy, infinity> &g,
                 const VertTy &vert) {
  try {
    g.EraseVertex(vert);
    std::cout << "ɾ���ɹ���" << std::endl;
  } catch (VertexNotFound) {
    std::cout << "�ö��㲻����" << std::endl;
  }
}

template <class VertTy, class WeightTy, WeightTy infinity>
void InsertEdge(myds::AdjListWUndirGraph<VertTy, WeightTy, infinity> &g,
                const VertTy &from, const VertTy &to, const WeightTy &weight) {
  try {
    g.InsertEdge(from, to, weight);
    std::cout << "����ɹ���" << std::endl;
  } catch (IllegalParameterValue) {
    std::cout << "������յ���ͬ���޷�����"
              << std::endl;
  } catch (VertexNotFound) {
    std::cout << "���㲻���ڣ��޷�����" << std::endl;
  } catch (EdgeAlreadyExists) {
    std::cout << "�ñ��Ѵ��ڣ��޷�����" << std::endl;
  }
}

template <class VertTy, class WeightTy, WeightTy infinity>
void EraseEdge(myds::AdjListWUndirGraph<VertTy, WeightTy, infinity> &g,
               const VertTy &from, const VertTy &to) {
  try {
    g.EraseEdge(from, to);
    std::cout << "ɾ���ɹ���" << std::endl;
  } catch (VertexNotFound) {
    std::cout << "���㲻���ڣ��޷�ɾ��" << std::endl;
  } catch (EdgeNotFound) {
    std::cout << "�ñ߲�����" << std::endl;
  }
}

template <class VertTy, class WeightTy, WeightTy infinity>
void Degree(const myds::AdjListWUndirGraph<VertTy, WeightTy, infinity> &g,
            const VertTy &vert) {
  try {
    std::string result = std::format("������{}", g.GetDegree(vert));
    std::cout << result << std::endl;
  } catch (VertexNotFound) {
    std::cout << "�ö��㲻����" << std::endl;
  }
}

template <class VertTy, class WeightTy, WeightTy infinity>
void ConnectedComponent(
    const myds::AdjListWUndirGraph<VertTy, WeightTy, infinity> &g) {
  try {
    if (g.IsConnected())
      std::cout << "��ͼ����ͨͼ\n";
    else
      std::cout << "��ͼ������ͨͼ\n";
    std::cout << "��ͨ��������" << g.GetNumOfConnectedComponent() << std::endl;
  } catch (NoVertex) {
    std::cout << "�޶���" << std::endl;
  }
}

template <class VertTy, class WeightTy, WeightTy infinity>
void MinimumSpanningTree(
    const myds::AdjListWUndirGraph<VertTy, WeightTy, infinity> &g) {
  try {
    if (g.HasUniqueMST())
      std::cout << "��ͼ��Ψһ��С������" << std::endl;
    else
      std::cout << "��ͼ�ж����С������" << std::endl;
  } catch (NoVertex) {
    std::cout << "�޶���" << std::endl;
    return;
  } catch (GraphDisconnected) {
    std::cout << "����ͨͼ���޷�������С�����"
                 "�"
              << std::endl;
    return;
  }

  std::cout << "-----------\n";
  std::cout << "| Kruskal |\n";
  std::cout << "-----------" << std::endl;
  Algorithm::Kruskal(g);
  std::cout << std::endl;

  std::cout << "--------\n";
  std::cout << "| Prim |\n";
  std::cout << "--------" << std::endl;
  Algorithm::Prim(g);
  std::cout << std::endl;

  std::cout << "------------------\n";
  std::cout << "| Reverse-Delete |\n";
  std::cout << "------------------" << std::endl;
  Algorithm::ReverseDelete(g);
}
} // namespace Spring02
