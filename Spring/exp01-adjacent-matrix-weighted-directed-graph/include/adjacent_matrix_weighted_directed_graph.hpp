#pragma once
#include "square_matrix.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <ranges>
#include <vector>

namespace myds {

template <class VertTy = int, class WeightTy = int,
          WeightTy infinity = std::numeric_limits<WeightTy>::max()>
class AdjMatWDirGraph {
  using Graph = AdjMatWDirGraph<VertTy, WeightTy, infinity>;

public:
  AdjMatWDirGraph(int vertNum = 0)
      : m_vertices(vertNum), m_adjMat(vertNum), m_numEdges(0) {}
  AdjMatWDirGraph(const std::vector<VertTy> &vertices);
  AdjMatWDirGraph(const Graph &) = default;
  Graph &operator=(const Graph &) = default;
  virtual ~AdjMatWDirGraph() = default;

  int getNumOfVertices() const { return (int)m_vertices.size(); }
  int getNumOfEdges() const { return m_numEdges; }

  int getOutDegree(const VertTy &from) const;
  int getInDegree(const VertTy &to) const;
  int getDegree(const VertTy &v) const {
    return getOutDegree(v) + getInDegree(v);
  }

  const VertTy *getFirstAdjVertex(const VertTy &from) const;
  VertTy *getFirstAdjVertex(const VertTy &from);

  const VertTy *getNextAdjVertex(const VertTy &from, const VertTy &after) const;
  VertTy *getNextAdjVertex(const VertTy &from, const VertTy &after);

  WeightTy getWeight(const VertTy &from, const VertTy &to) const;
  WeightTy getInfinity() const { return infinity; }

  void clear();
  void setVertex(const VertTy &oldVert, const VertTy &newVert);
  void insertVertex(const VertTy &vert);
  void eraseVertex(const VertTy &vert);
  void setWeight(const VertTy &from, const VertTy &to,
                 const WeightTy &newWeight);
  void insertEdge(const VertTy &from, const VertTy &to, const WeightTy &weight);
  void eraseEdge(const VertTy &from, const VertTy &to);

  void PrintAdjacentMatrix(std::ostream &out = std::cout) const;
  void PrintEdges(std::ostream &out = std::cout) const;

  /* Shortest Path Algorithm */

  template <class VertTy, class WeightTy, WeightTy infinity>
  friend void
  algorithm::dijkstra(const AdjMatWDirGraph<VertTy, WeightTy, infinity> &g,
                      const VertTy &source, const VertTy &end,
                      std::ostream *out);

  template <class VertTy, class WeightTy, WeightTy infinity>
  friend void
  algorithm::bellman_ford(const AdjMatWDirGraph<VertTy, WeightTy, infinity> &g,
                          const VertTy &source, const VertTy &end,
                          std::ostream *out);

  template <class VertTy, class WeightTy, WeightTy infinity>
  friend void algorithm::floyd_warshall(
      const AdjMatWDirGraph<VertTy, WeightTy, infinity> &g,
      const VertTy &source, const VertTy &end, std::ostream *out);

private:
  int getIndexOfVertex(const VertTy &vert) const {
    int i = 0;
    for (; i < m_vertices.size(); i++) {
      if (m_vertices[i] == vert) {
        break;
      }
    }
    if (i == m_vertices.size())
      throw VertexNotFound();

    return i;
  }

private:
  std::vector<VertTy> m_vertices;            // Vertices in the graph.
  SquareMatrix<WeightTy, infinity> m_adjMat; // Adjacent matrix of the graph.
  int m_numEdges = 0;                        // Number of edges in the graph.
};

////////////////////////////////////////////////////////////////////////////////////////////////
// Implementation of member functions
////////////////////////////////////////////////////////////////////////////////////////////////

template <class VertTy, class WeightTy, WeightTy infinity>
AdjMatWDirGraph<VertTy, WeightTy, infinity>::AdjMatWDirGraph(
    const std::vector<VertTy> &vertices) {
  // Check if there are duplicate vertices.
  for (const auto &v : vertices) {
    if (std::ranges::find(m_vertices, v) == m_vertices.end())
      m_vertices.push_back(v);
  }
  m_adjMat.setDim(m_vertices.size());
  m_numEdges = 0;
}

template <class VertTy, class WeightTy, WeightTy infinity>
const VertTy *AdjMatWDirGraph<VertTy, WeightTy, infinity>::getFirstAdjVertex(
    const VertTy &from) const {
  int fromIndex = getIndexOfVertex(from);
  for (int toIndex = 0; toIndex < m_vertices.size(); toIndex++) {
    if (m_adjMat[fromIndex][toIndex] != infinity)
      return &m_vertices[toIndex];
  }
  return nullptr;
}

template <class VertTy, class WeightTy, WeightTy infinity>
VertTy *AdjMatWDirGraph<VertTy, WeightTy, infinity>::getFirstAdjVertex(
    const VertTy &from) {
  auto const_this = const_cast<const Graph *>(this);
  return const_cast<VertTy *>(const_this->getFirstAdjVertex(from));
}

template <class VertTy, class WeightTy, WeightTy infinity>
const VertTy *AdjMatWDirGraph<VertTy, WeightTy, infinity>::getNextAdjVertex(
    const VertTy &from, const VertTy &after) const {
  int fromIndex = getIndexOfVertex(from);
  int afterIndex = getIndexOfVertex(after);
  for (int toIndex = afterIndex + 1; toIndex < m_vertices.size(); toIndex++) {
    if (m_adjMat[fromIndex][toIndex] != infinity) {
      return &m_vertices[toIndex];
    }
  }
  return nullptr;
}

template <class VertTy, class WeightTy, WeightTy infinity>
VertTy *AdjMatWDirGraph<VertTy, WeightTy, infinity>::getNextAdjVertex(
    const VertTy &from, const VertTy &after) {
  auto const_this = const_cast<const Graph *>(this);
  return const_cast<VertTy *>(const_this->getNextAdjVertex(from, after));
}

template <class VertTy, class WeightTy, WeightTy infinity>
int AdjMatWDirGraph<VertTy, WeightTy, infinity>::getOutDegree(
    const VertTy &from) const {
  int fromIndex = getIndexOfVertex(from);
  int outD = 0;
  for (const auto &weight : m_adjMat[fromIndex]) {
    if (weight != infinity)
      outD++;
  }
  return outD;
}

template <class VertTy, class WeightTy, WeightTy infinity>
int AdjMatWDirGraph<VertTy, WeightTy, infinity>::getInDegree(
    const VertTy &to) const {
  int toIndex = getIndexOfVertex(to);
  int inDegree = 0;
  for (int fromIndex = 0; fromIndex < m_vertices.size(); fromIndex++) {
    if (m_adjMat[fromIndex][toIndex] != infinity)
      inDegree++;
  }
  return inDegree;
}

template <class VertTy, class WeightTy, WeightTy infinity>
WeightTy
AdjMatWDirGraph<VertTy, WeightTy, infinity>::getWeight(const VertTy &from,
                                                       const VertTy &to) const {
  int fromIndex = getIndexOfVertex(from);
  int toIndex = getIndexOfVertex(to);
  return m_adjMat[fromIndex][toIndex];
}

template <class VertTy, class WeightTy, WeightTy infinity>
void AdjMatWDirGraph<VertTy, WeightTy, infinity>::insertVertex(
    const VertTy &v) {
  if (std::ranges::find(m_vertices, v) != m_vertices.end())
    throw VertexAlreadyExists();

  m_vertices.push_back(v);
  m_adjMat.addOneDim();
}

template <class VertTy, class WeightTy, WeightTy infinity>
void AdjMatWDirGraph<VertTy, WeightTy, infinity>::eraseVertex(const VertTy &v) {
  int vIndex = getIndexOfVertex(v);
  for (int i = 0; i < m_vertices.size(); i++) {
    if (m_adjMat[vIndex][i] != infinity)
      m_numEdges--;

    if (m_adjMat[i][vIndex] != infinity)
      m_numEdges--;
  }
  int lastIndex = (int)m_vertices.size() - 1;
  if (vIndex != lastIndex) {
    // Replace the vertex to be deleted with the last vertex
    m_vertices[vIndex] = std::move(m_vertices[lastIndex]);
    m_adjMat[vIndex] = std::move(m_adjMat[lastIndex]);
    for (int i = 0; i < lastIndex; i++) {
      m_adjMat[i][vIndex] = std::move(m_adjMat[i][lastIndex]);
    }
    m_adjMat[vIndex][vIndex] = infinity;
  }
  m_adjMat.removeOneDim();
  m_vertices.pop_back();
}

template <class VertTy, class WeightTy, WeightTy infinity>
void AdjMatWDirGraph<VertTy, WeightTy, infinity>::setWeight(
    const VertTy &from, const VertTy &to, const WeightTy &newWeight) {
  if (newWeight == infinity) {
    throw InfiniteWeight("Weight cannot be infinity!");
  }

  int fromIndex = getIndexOfVertex(from);
  int toIndex = getIndexOfVertex(to);
  if (m_adjMat[fromIndex][toIndex] == infinity)
    throw EdgeNotFound();

  m_adjMat[fromIndex][toIndex] = newWeight;
}

template <class VertTy, class WeightTy, WeightTy infinity>
void AdjMatWDirGraph<VertTy, WeightTy, infinity>::insertEdge(
    const VertTy &from, const VertTy &to, const WeightTy &weight) {
  if (weight == infinity)
    throw InfiniteWeight("Weight cannot be infinity!");

  int fromIndex = getIndexOfVertex(from);
  int toIndex = getIndexOfVertex(to);

  if (fromIndex == toIndex)
    throw IllegalParameterValue("Loop is not allowed!");

  if (m_adjMat[fromIndex][toIndex] != infinity)
    throw EdgeAlreadyExists();

  m_adjMat[fromIndex][toIndex] = weight;
  m_numEdges++;
}

template <class VertTy, class WeightTy, WeightTy infinity>
void AdjMatWDirGraph<VertTy, WeightTy, infinity>::eraseEdge(
    const VertTy &from, const VertTy &to) {
  int fromIndex = getIndexOfVertex(from);
  int toIndex = getIndexOfVertex(to);

  if (m_adjMat[fromIndex][toIndex] == infinity)
    throw EdgeNotFound();

  m_adjMat[fromIndex][toIndex] = infinity;
  m_numEdges--;
}

template <class VertTy, class WeightTy, WeightTy infinity>
void AdjMatWDirGraph<VertTy, WeightTy, infinity>::clear() {
  m_vertices.clear();
  m_adjMat.setDim(0);
  m_numEdges = 0;
}

template <class VertTy, class WeightTy, WeightTy infinity>
void AdjMatWDirGraph<VertTy, WeightTy, infinity>::printAdjacentMatrix(
    std::ostream &out) const {
  if (m_vertices.empty())
    return;

  int width = 5;
  out << std::setw(width + 1) << "";
  for (const auto &v : m_vertices)
    out << std::setw(width) << v << " ";
  out << "\n";

  out << std::setw(width + 1) << "";
  for (const auto &v : m_vertices)
    out << "______";
  out << std::endl;

  for (int i = 0; i < m_adjMat.getDim(); i++) {
    out << std::setw(width - 1) << m_vertices[i] << " |";
    for (const auto &w : m_adjMat[i]) {
      if (w == infinity)
        out << std::setw(width) << "inf" << " ";
      else
        out << std::setw(width) << w << " ";
    }
    out << std::endl;
  }
}

template <class VertTy, class WeightTy, WeightTy infinity>
void AdjMatWDirGraph<VertTy, WeightTy, infinity>::printEdges(
    std::ostream &out) const {
  int edgeCnt = 0;
  for (int fromIndex = 0; fromIndex < m_adjMat.getDim(); fromIndex++) {
    for (int toIndex = 0; toIndex < m_adjMat.getDim(); toIndex++) {
      if (m_adjMat[fromIndex][toIndex] != infinity) {
        edgeCnt++;
        out << "(" << edgeCnt << ") "
            << "<" << m_vertices[fromIndex] << ", " << m_vertices[toIndex]
            << ">: " << m_adjMat[fromIndex][toIndex] << "\n";
      }
    }
  }
}
} // namespace myds
