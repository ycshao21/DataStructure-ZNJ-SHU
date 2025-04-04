#pragma once
#include <format>
#include <iostream>

#include "adjacent_matrix_weighted_directed_graph.hpp"
#include "exceptions.hpp"

template <class VertTy, class WeightTy, WeightTy infinity>
void InsertVertex(myds::AdjMatWDirGraph<VertTy, WeightTy, infinity> &g,
                  const VertTy &v) {
  try {
    g.insertVertex(v);
    std::cout << "����ɹ���\n";
  } catch (VertexAlreadyExists) {
    std::cout << "�ö����Ѵ��ڣ��޷�����\n";
  }
}

template <class VertTy, class WeightTy, WeightTy infinity>
void EraseVertex(myds::AdjMatWDirGraph<VertTy, WeightTy, infinity> &g,
                 const VertTy &v) {
  try {
    g.eraseVertex(v);
    std::cout << "ɾ���ɹ���\n";
  } catch (VertexNotFound) {
    std::cout << "�ö��㲻����\n";
  }
}

template <class VertTy, class WeightTy, WeightTy infinity>
void InsertEdge(myds::AdjMatWDirGraph<VertTy, WeightTy, infinity> &g,
                const VertTy &from, const VertTy &to, const WeightTy &weight) {
  try {
    g.insertEdge(from, to, weight);
    std::cout << "����ɹ���\n";
  } catch (IllegalParameterValue) {
    std::cout << "������յ���ͬ���޷�����\n";
  } catch (VertexNotFound) {
    std::cout << "���㲻���ڣ��޷�����\n";
  } catch (EdgeAlreadyExists) {
    std::cout << "�ñ��Ѵ��ڣ��޷�����\n";
  }
}

template <class VertTy, class WeightTy, WeightTy infinity>
void EraseEdge(myds::AdjMatWDirGraph<VertTy, WeightTy, infinity> &g,
               const VertTy &from, const VertTy &to) {
  try {
    g.eraseEdge(from, to);
    std::cout << "ɾ���ɹ���\n";
  } catch (VertexNotFound) {
    std::cout << "���㲻���ڣ��޷�ɾ��\n";
  } catch (EdgeNotFound) {
    std::cout << "�ñ߲�����\n";
  }
}

template <class VertTy, class WeightTy, WeightTy infinity>
void Degree(const myds::AdjMatWDirGraph<VertTy, WeightTy, infinity> &g,
            const VertTy &v) {
  try {
    std::string result =
        std::format("�ܶ�����{0}\n��ȣ�{1} ���ȣ�{2}\n", g.getDegree(v),
                    g.getInDegree(v), g.getOutDegree(v));
    std::cout << result;
  } catch (VertexNotFound) {
    std::cout << "�ö��㲻����\n";
  }
}

template <class VertTy, class WeightTy, WeightTy infinity>
void ShortestPath(const myds::AdjMatWDirGraph<VertTy, WeightTy, infinity> &g,
                  const VertTy &source, const VertTy &end) {
  std::cout << "------------\n";
  std::cout << "| Dijkstra |\n";
  std::cout << "------------\n";
  try {
    algorithm::dijkstra(g, source, end);
  } catch (VertexNotFound) {
    std::cout << "���㲻����\n";
  } catch (NegativeEdge) {
    std::cout << "����Ȩ�ߣ��޷�ʹ��Dijkstra�㷨\n";
  }
  std::cout << std::endl;

  std::cout << "----------------\n";
  std::cout << "| Bellman-Ford |\n";
  std::cout << "----------------\n";
  try {
    algorithm::bellman_ford(g, source, end);
  } catch (VertexNotFound) {
    std::cout << "���㲻����\n";
  } catch (NegativeCycle) {
    std::cout
        << "����Ȩ��·���޷��������·��"
           "\n";
  }
  std::cout << std::endl;

  std::cout << "------------------\n";
  std::cout << "| Floyd-Warshall |\n";
  std::cout << "------------------\n";
  try {
    algorithm::floyd_warshall(g, source, end);
  } catch (VertexNotFound) {
    std::cout << "���㲻����\n";
  } catch (NegativeCycle) {
    std::cout
        << "����Ȩ��·���޷��������·��"
           "\n";
  }
}
