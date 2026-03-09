#pragma once

#include <algorithm>
#include <format>
#include <iostream>
#include <limits>
#include <ranges>
#include <vector>

#include "graph_exceptions.hpp"
#include "shortest_path.hpp"
#include "square_matrix.hpp"

namespace myds
{

template <class V = int, class W = int, W inf = std::numeric_limits<W>::max()>
class AdjMatWDirGraph
{
    using IndexType = std::int64_t;

public:
    AdjMatWDirGraph(std::size_t numVertices = 0)
        : m_vertices(numVertices), m_adjMat(numVertices)
    {
    }
    AdjMatWDirGraph(const std::vector<V>& vertices);

    AdjMatWDirGraph(const AdjMatWDirGraph<V, W, inf>&) = default;
    AdjMatWDirGraph<V, W, inf>& operator=(const AdjMatWDirGraph<V, W, inf>&) = default;

    virtual ~AdjMatWDirGraph() = default;

    std::size_t getNumOfVertices() const
    {
        return m_vertices.size();
    }
    std::size_t getNumOfEdges() const
    {
        return m_numEdges;
    }

    std::size_t countOutDegree(const V& from) const
    {
        IndexType fromIndex = getIndexOfVertex(from);
        checkIndex(fromIndex);
        return countOutDegreeByIndex(fromIndex);
    }
    std::size_t countInDegree(const V& to) const
    {
        IndexType toIndex = getIndexOfVertex(to);
        checkIndex(toIndex);
        return countInDegreeByIndex(toIndex);
    }
    std::size_t countDegree(const V& v) const
    {
        IndexType vIndex = getIndexOfVertex(v);
        return countOutDegreeByIndex(vIndex) + countInDegreeByIndex(vIndex);
    }

    IndexType getIndexOfVertex(const V& v) const;
    IndexType getIndexOfFirstAdjVertex(const V& from) const;
    IndexType getIndexOfNextAdjVertex(const V& from, const V& after) const;

    V& getVertex(IndexType vIndex)
    {
        checkIndex(vIndex);
        return m_vertices[vIndex];
    }
    const V& getVertex(IndexType vIndex) const
    {
        checkIndex(vIndex);
        return m_vertices[vIndex];
    }

    W getWeight(const V& from, const V& to) const;

    constexpr W getInf() const
    {
        return inf;
    }

    void clear();

    void setVertex(const V& oldV, const V& newV);
    void insertVertex(const V& v);
    void eraseVertex(const V& v);

    void setWeight(const V& from, const V& to, const W& newWeight);
    void insertEdge(const V& from, const V& to, const W& weight);
    void eraseEdge(const V& from, const V& to);

    void printAdjacentMatrix(std::ostream& out = std::cout) const;
    void printEdges(std::ostream& out = std::cout) const;

    /* Shortest Path Algorithm */

    template <class V1, class W1, W1 inf1>
    friend void algorithm::dijkstra(const AdjMatWDirGraph<V1, W1, inf1>& g, const V1& src,
                                    const V1& end, std::ostream* out);

    template <class V1, class W1, W1 inf1>
    friend void algorithm::bellmanFord(const AdjMatWDirGraph<V1, W1, inf1>& g,
                                       const V1& src, const V1& end, std::ostream* out);

    template <class V1, class W1, W1 inf1>
    friend void algorithm::floydWarshall(const AdjMatWDirGraph<V1, W1, inf1>& g,
                                         const V1& src, const V1& end, std::ostream* out);

private:
    void checkIndex(IndexType index) const
    {
        if (index < 0 || index >= (IndexType) m_vertices.size()) {
            throw VertexNotFoundException();
        }
    }
    std::size_t countOutDegreeByIndex(IndexType fromIndex) const;
    std::size_t countInDegreeByIndex(IndexType toIndex) const;

    std::vector<V> m_vertices;      // Vertices in the graph.
    SquareMatrix<W, inf> m_adjMat;  // Adjacent matrix of the graph.
    std::size_t m_numEdges = 0;     // Number of edges in the graph.
};

////////////////////////////////////////
// Implementation of member functions
////////////////////////////////////////

template <class V, class W, W inf>
AdjMatWDirGraph<V, W, inf>::AdjMatWDirGraph(const std::vector<V>& vertices)
{
    // Check if there are duplicate vertices.
    for (const V& v : vertices) {
        if (std::ranges::find(m_vertices, v) == m_vertices.end()) {
            m_vertices.push_back(v);
        }
    }
    m_adjMat.setDim(m_vertices.size());
    m_numEdges = 0;
}

template <class V, class W, W inf>
auto AdjMatWDirGraph<V, W, inf>::countOutDegreeByIndex(IndexType fromIndex) const
    -> std::size_t
{
    std::size_t outDegree = 0;
    for (const W& weight : m_adjMat[fromIndex]) {
        if (weight != inf) {
            ++outDegree;
        }
    }
    return outDegree;
}

template <class V, class W, W inf>
auto AdjMatWDirGraph<V, W, inf>::countInDegreeByIndex(IndexType toIndex) const
    -> std::size_t
{
    std::size_t inDegree = 0;
    for (const auto& row : m_adjMat) {
        if (row[toIndex] != inf) {
            ++inDegree;
        }
    }
    return inDegree;
}

template <class V, class W, W inf>
auto AdjMatWDirGraph<V, W, inf>::getIndexOfVertex(const V& v) const -> IndexType
{
    for (IndexType i = 0; i < (IndexType) m_vertices.size(); ++i) {
        if (m_vertices[i] == v) {
            return i;
        }
    }
    return -1;
}

template <class V, class W, W inf>
auto AdjMatWDirGraph<V, W, inf>::getIndexOfFirstAdjVertex(const V& from) const
    -> IndexType
{
    IndexType fromIndex = getIndexOfVertex(from);
    checkIndex(fromIndex);

    for (IndexType toIndex = 0; toIndex < (IndexType) m_vertices.size(); ++toIndex) {
        if (m_adjMat[fromIndex][toIndex] != inf) {
            return toIndex;
        }
    }
    return -1;
}

template <class V, class W, W inf>
auto AdjMatWDirGraph<V, W, inf>::getIndexOfNextAdjVertex(
    const V& from, const V& after) const -> IndexType
{
    IndexType fromIndex = getIndexOfVertex(from);
    checkIndex(fromIndex);

    IndexType afterIndex = getIndexOfVertex(after);
    checkIndex(afterIndex);

    for (IndexType toIndex = afterIndex + 1; toIndex < (IndexType) m_vertices.size();
         ++toIndex) {
        if (m_adjMat[fromIndex][toIndex] != inf) {
            return &m_vertices[toIndex];
        }
    }
    return -1;
}

template <class V, class W, W inf>
auto AdjMatWDirGraph<V, W, inf>::getWeight(const V& from, const V& to) const -> W
{
    IndexType fromIndex = getIndexOfVertex(from);
    checkIndex(fromIndex);

    IndexType toIndex = getIndexOfVertex(to);
    checkIndex(toIndex);

    if (fromIndex == toIndex) {
        throw EdgeNotFoundException();
    }

    const W& weight = m_adjMat[fromIndex][toIndex];
    if (weight == inf) {
        throw EdgeNotFoundException();
    }
    return weight;
}

template <class V, class W, W inf>
void AdjMatWDirGraph<V, W, inf>::clear()
{
    m_vertices.clear();
    m_adjMat.setDim(0);
    m_numEdges = 0;
}

template <class V, class W, W inf>
void AdjMatWDirGraph<V, W, inf>::setVertex(const V& oldV, const V& newV)
{
    IndexType vIndex = getIndexOfVertex(oldV);
    checkIndex(vIndex);

    m_vertices[vIndex] = newV;
}

template <class V, class W, W inf>
void AdjMatWDirGraph<V, W, inf>::insertVertex(const V& v)
{
    if (std::ranges::find(m_vertices, v) != m_vertices.end()) {
        throw DuplicateVertexException();
    }

    m_vertices.push_back(v);
    m_adjMat.addOneDim();
}

template <class V, class W, W inf>
void AdjMatWDirGraph<V, W, inf>::eraseVertex(const V& v)
{
    IndexType vIndex = getIndexOfVertex(v);
    checkIndex(vIndex);

    for (std::size_t i = 0; i < m_vertices.size(); ++i) {
        if (m_adjMat[vIndex][i] != inf) {
            --m_numEdges;
        }

        if (m_adjMat[i][vIndex] != inf) {
            --m_numEdges;
        }
    }

    IndexType lastIndex = m_vertices.size() - 1;
    if (vIndex != lastIndex) {
        // Replace the vertex to be deleted with the last vertex
        m_vertices[vIndex] = std::move(m_vertices[lastIndex]);
        m_adjMat[vIndex] = std::move(m_adjMat[lastIndex]);
        for (IndexType i = 0; i < lastIndex; ++i) {
            m_adjMat[i][vIndex] = std::move(m_adjMat[i][lastIndex]);
        }
        m_adjMat[vIndex][vIndex] = inf;
    }
    m_adjMat.removeOneDim();
    m_vertices.pop_back();
}

template <class V, class W, W inf>
void AdjMatWDirGraph<V, W, inf>::setWeight(const V& from, const V& to, const W& newWeight)
{
    IndexType fromIndex = getIndexOfVertex(from);
    checkIndex(fromIndex);

    IndexType toIndex = getIndexOfVertex(to);
    checkIndex(toIndex);

    if (fromIndex == toIndex) {
        throw SelfLoopNotAllowedException();
    }

    if (newWeight == inf) {
        throw InvalidWeightException();
    }

    if (m_adjMat[fromIndex][toIndex] == inf) {
        throw EdgeNotFoundException();
    }

    m_adjMat[fromIndex][toIndex] = newWeight;
}

template <class V, class W, W inf>
void AdjMatWDirGraph<V, W, inf>::insertEdge(const V& from, const V& to, const W& weight)
{
    IndexType fromIndex = getIndexOfVertex(from);
    checkIndex(fromIndex);

    IndexType toIndex = getIndexOfVertex(to);
    checkIndex(toIndex);

    if (fromIndex == toIndex) {
        throw SelfLoopNotAllowedException();
    }

    if (weight == inf) {
        throw InvalidWeightException();
    }

    if (m_adjMat[fromIndex][toIndex] != inf) {
        throw DuplicateEdgeException();
    }

    m_adjMat[fromIndex][toIndex] = weight;
    ++m_numEdges;
}

template <class V, class W, W inf>
void AdjMatWDirGraph<V, W, inf>::eraseEdge(const V& from, const V& to)
{
    IndexType fromIndex = getIndexOfVertex(from);
    checkIndex(fromIndex);

    IndexType toIndex = getIndexOfVertex(to);
    checkIndex(toIndex);

    if (fromIndex == toIndex) {
        throw EdgeNotFoundException();
    }

    if (m_adjMat[fromIndex][toIndex] == inf) {
        throw EdgeNotFoundException();
    }

    m_adjMat[fromIndex][toIndex] = inf;
    --m_numEdges;
}

template <class V, class W, W inf>
void AdjMatWDirGraph<V, W, inf>::printAdjacentMatrix(std::ostream& out) const
{
    if (m_vertices.empty()) {
        out << "None\n";
        return;
    }

    std::size_t max_width = 5;
    for (const auto& v : m_vertices) {
        max_width = std::max(max_width, std::format("{}", v).size());
    }
    for (const auto& row : m_adjMat) {
        for (const W& w : row) {
            if (w == inf) {
                max_width = std::max(max_width, std::size_t(3));
            } else {
                max_width = std::max(max_width, std::format("{}", w).size());
            }
        }
    }

    // Column title
    out << std::format("{:>{}}", "", max_width + 2);
    for (const auto& v : m_vertices) {
        out << std::format("{:>{}} ", v, max_width);
    }
    out << '\n';

    out << std::format("{:>{}}", "", max_width + 2);
    std::string separator(max_width + 1, '-');
    for (const auto& v : m_vertices) {
        out << separator;
    }
    out << '\n';

    for (std::size_t i = 0; i < m_vertices.size(); ++i) {
        // Row title
        out << std::format("{:>{}} |", m_vertices[i], max_width);
        // Row content
        for (const W& w : m_adjMat[i]) {
            if (w == inf) {
                out << std::format("{:>{}} ", "inf", max_width);
            } else {
                out << std::format("{:>{}} ", w, max_width);
            }
        }
        out << '\n';
    }
}

template <class V, class W, W inf>
void AdjMatWDirGraph<V, W, inf>::printEdges(std::ostream& out) const
{
    std::size_t edgeCnt = 0;
    for (IndexType fromIndex = 0; fromIndex < (IndexType) m_adjMat.getDim();
         ++fromIndex) {
        for (IndexType toIndex = 0; toIndex < (IndexType) m_adjMat.getDim(); ++toIndex) {
            if (m_adjMat[fromIndex][toIndex] != inf) {
                ++edgeCnt;
                out << std::format("({0}) <{1}, {2}>: {3}\n", edgeCnt,
                                   m_vertices[fromIndex], m_vertices[toIndex],
                                   m_adjMat[fromIndex][toIndex]);
            }
        }
    }

    if (edgeCnt == 0) {
        out << "None\n";
    }
}
}  // namespace myds
