#pragma once

#include <algorithm>
#include <format>
#include <iostream>
#include <limits>
#include <list>
#include <queue>
#include <ranges>
#include <stack>
#include <vector>

#include "graph_exceptions.hpp"
#include "minimum_spanning_tree.hpp"

namespace myds
{

template <class V = int, class W = int, W inf = std::numeric_limits<W>::max()>
class AdjListWUndirGraph
{
    using IndexType = std::int64_t;

    struct AdjListEdge
    {
        IndexType toIndex = -1;  // Index of the vertex the edge is pointing to.
        W weight = 0;            // Weight of the edge.
    };

    class FindEdgeFn  // For finding edge according to the toIndex.
    {
    public:
        FindEdgeFn(IndexType toIndex) : m_toIndex(toIndex)
        {
        }
        bool operator()(const AdjListEdge& e) const
        {
            return e.toIndex == m_toIndex;
        }

    private:
        IndexType m_toIndex;
    };

    using AdjList = std::list<AdjListEdge>;
    using VisitFn = void (*)(const V&);

public:
    AdjListWUndirGraph(std::size_t numVertices = 0)
        : m_vertices(numVertices), m_adjLists(numVertices)
    {
    }
    AdjListWUndirGraph(const std::vector<V>& vertices);

    AdjListWUndirGraph(const AdjListWUndirGraph<V, W, inf>&) = default;
    AdjListWUndirGraph<V, W, inf>& operator=(const AdjListWUndirGraph<V, W, inf>&) =
        default;

    virtual ~AdjListWUndirGraph() = default;

    std::size_t getNumOfVertices() const
    {
        return m_vertices.size();
    }
    std::size_t getNumOfEdges() const
    {
        return m_numEdges;
    }

    std::size_t countDegree(const V& v) const;

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

    W getWeight(const V& v1, const V& v2) const;

    constexpr W getInf() const
    {
        return inf;
    }

    void clear();

    void setVertex(const V& oldV, const V& newV);
    void insertVertex(const V& v);
    void eraseVertex(const V& v);

    void setWeight(const V& v1, const V& v2, const W& newWeight);
    void insertEdge(const V& v1, const V& v2, const W& weight);
    void eraseEdge(const V& v1, const V& v2);

    bool isConnected() const;
    std::size_t getNumOfConnectedComponent() const;
    bool hasUniqueMST() const
    {
        return algorithm::hasUniqueMST(*this);
    }

    template <class V1, class W1, W1 inf1>
    friend W1 algorithm::kruskal(const AdjListWUndirGraph<V1, W1, inf1>& g,
                                 std::ostream* out);
    template <class V1, class W1, W1 inf1>
    friend W1 algorithm::prim(const AdjListWUndirGraph<V1, W1, inf1>& g,
                              std::ostream* out);
    template <class V1, class W1, W1 inf1>
    friend W1 algorithm::reverseDelete(const AdjListWUndirGraph<V1, W1, inf1>& g,
                                       std::ostream* out);

    // @brief Depth-first search from one vertex.
    void dfs(const V& src, VisitFn visit = printVertex) const;
    // @brief Depth-first search for the whole graph.
    void dfs(VisitFn visit = printVertex) const;
    // @brief Breadth-first search from one vertex.
    void bfs(const V& src, VisitFn visit = printVertex) const;
    // @brief Breadth-first search for the whole graph.
    void bfs(VisitFn visit = printVertex) const;

    void printAdjacentList(std::ostream& out = std::cout) const;
    void printEdges(std::ostream& out = std::cout) const;

private:
    void checkIndex(IndexType index) const
    {
        if (index < 0 || index >= (IndexType) m_vertices.size()) {
            throw VertexNotFoundException();
        }
    }

    void _dfs(IndexType srcIndex, std::vector<uint8_t>& visited,
              VisitFn visit = printVertex) const;
    void _bfs(IndexType srcIndex, std::vector<uint8_t>& visited,
              VisitFn visit = printVertex) const;

    static void printVertex(const V& v)
    {
        std::cout << v << " ";
    }

    template <class V1, class W1, W1 inf1>
    friend bool algorithm::findTreePath(const AdjListWUndirGraph<V1, W1, inf1>& tree,
                                        IndexType prevIndex, IndexType fromIndex,
                                        IndexType endIndex,
                                        std::stack<algorithm::MSTEdge<W1>>& path);

    template <class V1, class W1, W1 inf1>
    friend bool algorithm::hasUniqueMST(const AdjListWUndirGraph<V1, W1, inf1>& g);

    std::vector<V> m_vertices;
    std::vector<AdjList> m_adjLists;
    std::size_t m_numEdges = 0;
};

////////////////////////////////////////////////////////////////////////////////////////////////
// Implementation of member functions
////////////////////////////////////////////////////////////////////////////////////////////////

template <class V, class W, W inf>
AdjListWUndirGraph<V, W, inf>::AdjListWUndirGraph(const std::vector<V>& vertices)
{
    std::unordered_set<V> unique_vertices;
    for (const V& v : vertices) {
        unique_vertices.insert(v);
    }
    m_vertices.assign(unique_vertices.begin(), unique_vertices.end());

    m_adjLists.resize(m_vertices.size());
    m_numEdges = 0;
}

template <class V, class W, W inf>
std::size_t AdjListWUndirGraph<V, W, inf>::countDegree(const V& v) const
{
    IndexType vIndex = getIndexOfVertex(v);
    checkIndex(vIndex);

    return m_adjLists[vIndex].size();
}

template <class V, class W, W inf>
auto AdjListWUndirGraph<V, W, inf>::getIndexOfVertex(const V& v) const -> IndexType
{
    for (IndexType i = 0; i < (IndexType) m_vertices.size(); ++i) {
        if (m_vertices[i] == v) {
            return i;
        }
    }
    return -1;
}

template <class V, class W, W inf>
auto AdjListWUndirGraph<V, W, inf>::getIndexOfFirstAdjVertex(const V& from) const
    -> IndexType
{
    IndexType fromIndex = getIndexOfVertex(from);
    checkIndex(fromIndex);

    if (m_adjLists[fromIndex].empty()) {
        return -1;
    }
    return m_adjLists[fromIndex].front().toIndex;
}

template <class V, class W, W inf>
auto AdjListWUndirGraph<V, W, inf>::getIndexOfNextAdjVertex(
    const V& from, const V& after) const -> IndexType
{
    IndexType fromIndex = getIndexOfVertex(from);
    checkIndex(fromIndex);

    IndexType afterIndex = getIndexOfVertex(after);
    checkIndex(afterIndex);

    // Check if "to" is adjacent to "from".

    auto it = std::ranges::find_if(m_adjLists[fromIndex], FindEdgeFn(afterIndex));
    if (it == m_adjLists[fromIndex].end()) {
        return -1;
    }

    // Move to the next adjacent vertex.
    ++it;
    if (it == m_adjLists[fromIndex].end()) {
        return -1;
    }

    return it->toIndex;
}

template <class V, class W, W inf>
W AdjListWUndirGraph<V, W, inf>::getWeight(const V& v1, const V& v2) const
{
    IndexType v1Index = getIndexOfVertex(v1);
    checkIndex(v1Index);

    IndexType v2Index = getIndexOfVertex(v2);
    checkIndex(v2Index);

    if (v1Index == v2Index) {
        throw EdgeNotFoundException();
    }

    auto it = std::ranges::find_if(m_adjLists[v1Index], FindEdgeFn(v2Index));
    if (it == m_adjLists[v1Index].end()) {
        throw EdgeNotFoundException();
    }

    return it->weight;
}

template <class V, class W, W inf>
bool AdjListWUndirGraph<V, W, inf>::isConnected() const
{
    if (m_vertices.empty()) {
        throw NoVertexException();
    }

    if (m_vertices.size() == 1) {
        return true;
    }

    if (m_numEdges < m_vertices.size() - 1) {
        return false;
    }

    // If the graph can be wholly traversed from one vertex, it is connected.
    std::vector<uint8_t> visited(m_vertices.size(), 0);
    _bfs(0, visited, nullptr);
    return std::ranges::find(visited, 0) == visited.end();
}

template <class V, class W, W inf>
std::size_t AdjListWUndirGraph<V, W, inf>::getNumOfConnectedComponent() const
{
    if (m_vertices.empty()) {
        throw NoVertexException();
    }

    // The number of connected components is equal to the number of times of
    // traversal.
    std::size_t cnt = 0;
    std::vector<uint8_t> visited(m_vertices.size(), 0);
    for (IndexType idx = 0; idx < (IndexType) m_vertices.size(); ++idx) {
        if (visited[idx] == 0) {
            ++cnt;
            _bfs(idx, visited, nullptr);
        }
    }
    return cnt;
}

template <class V, class W, W inf>
void AdjListWUndirGraph<V, W, inf>::setVertex(const V& oldV, const V& newV)
{
    IndexType vIndex = getIndexOfVertex(oldV);
    checkIndex(vIndex);

    m_vertices[vIndex] = newV;
}

template <class V, class W, W inf>
void AdjListWUndirGraph<V, W, inf>::insertVertex(const V& v)
{
    if (std::ranges::find(m_vertices, v) != m_vertices.end()) {
        throw DuplicateVertexException();
    }

    m_vertices.push_back(v);
    m_adjLists.push_back({});
}

template <class V, class W, W inf>
void AdjListWUndirGraph<V, W, inf>::eraseVertex(const V& v)
{
    IndexType vIndex = getIndexOfVertex(v);
    checkIndex(vIndex);

    m_numEdges -= m_adjLists[vIndex].size();

    for (IndexType fromIndex = 0; fromIndex < (IndexType) m_adjLists.size();
         ++fromIndex) {
        if (fromIndex != vIndex) {
            std::erase_if(m_adjLists[fromIndex], FindEdgeFn(vIndex));
        }
    }

    auto lastIndex = (IndexType) (m_vertices.size() - 1);
    if (vIndex != lastIndex) {
        // Replace the vertex to be deleted with the last vertex
        m_vertices[vIndex] = std::move(m_vertices[lastIndex]);
        m_adjLists[vIndex] = std::move(m_adjLists[lastIndex]);
        for (IndexType fromIndex = 0; fromIndex < lastIndex; ++fromIndex) {
            if (fromIndex != vIndex) {
                auto it =
                    std::ranges::find_if(m_adjLists[fromIndex], FindEdgeFn(lastIndex));
                if (it != m_adjLists[fromIndex].end()) {
                    it->toIndex = vIndex;
                }
            }
        }
    }
    m_adjLists.pop_back();
    m_vertices.pop_back();
}

template <class V, class W, W inf>
void AdjListWUndirGraph<V, W, inf>::setWeight(const V& v1, const V& v2,
                                              const W& newWeight)
{
    IndexType v1Index = getIndexOfVertex(v1);
    checkIndex(v1Index);

    IndexType v2Index = getIndexOfVertex(v2);
    checkIndex(v2Index);

    if (newWeight == inf) {
        throw InvalidWeightException();
    }

    if (v1Index == v2Index) {
        throw EdgeNotFoundException();
    }

    auto it1 = std::ranges::find_if(m_adjLists[v1Index], FindEdgeFn(v2Index));
    if (it1 == m_adjLists[v1Index].end()) {
        throw EdgeNotFoundException();
    }
    it1->weight = newWeight;

    auto it2 = std::ranges::find_if(m_adjLists[v2Index], FindEdgeFn(v1Index));
    it2->weight = newWeight;
}

template <class V, class W, W inf>
void AdjListWUndirGraph<V, W, inf>::insertEdge(const V& v1, const V& v2, const W& weight)
{
    IndexType v1Index = getIndexOfVertex(v1);
    checkIndex(v1Index);

    IndexType v2Index = getIndexOfVertex(v2);
    checkIndex(v2Index);

    if (v1Index == v2Index) {
        throw SelfLoopNotAllowedException();
    }

    if (weight == inf) {
        throw InvalidWeightException();
    }

    auto it = std::ranges::find_if(m_adjLists[v1Index], FindEdgeFn(v2Index));
    if (it != m_adjLists[v1Index].end()) {
        throw DuplicateEdgeException();
    }
    // Insert the edge at the front of the list.
    m_adjLists[v1Index].push_front({v2Index, weight});
    m_adjLists[v2Index].push_front({v1Index, weight});

    ++m_numEdges;
}

template <class V, class W, W inf>
void AdjListWUndirGraph<V, W, inf>::eraseEdge(const V& v1, const V& v2)
{
    IndexType v1Index = getIndexOfVertex(v1);
    checkIndex(v1Index);

    IndexType v2Index = getIndexOfVertex(v2);
    checkIndex(v2Index);

    if (v1Index == v2Index) {
        throw EdgeNotFoundException();
    }

    auto erased = (bool) std::erase_if(m_adjLists[v1Index], FindEdgeFn(v2Index));
    if (!erased) {
        throw EdgeNotFoundException();
    }
    std::erase_if(m_adjLists[v2Index], FindEdgeFn(v1Index));

    --m_numEdges;
}

template <class V, class W, W inf>
void AdjListWUndirGraph<V, W, inf>::_dfs(IndexType srcIndex,
                                         std::vector<uint8_t>& visited,
                                         VisitFn visit) const
{
    // Visit the current vertex:
    visited[srcIndex] = 1;
    if (visit) {
        (*visit)(m_vertices[srcIndex]);
    }

    // Visit its unvisited adjacent vertices:
    for (const auto& edge : m_adjLists[srcIndex]) {
        if (visited[edge.toIndex] == 0) {
            _dfs(edge.toIndex, visited, visit);
        }
    }
}

template <class V, class W, W inf>
void AdjListWUndirGraph<V, W, inf>::_bfs(IndexType srcIndex,
                                         std::vector<uint8_t>& visited,
                                         VisitFn visit) const
{
    // Visit the current vertex:
    visited[srcIndex] = 1;
    if (visit) {
        (*visit)(m_vertices[srcIndex]);
    }

    std::queue<IndexType> q;
    q.push(srcIndex);

    while (!q.empty()) {
        IndexType curIndex = q.front();
        q.pop();

        // Visit its adjacent vertices:
        for (const auto& edge : m_adjLists[curIndex]) {
            IndexType adjIndex = edge.toIndex;

            if (visited[adjIndex] == 1) {
                continue;
            }

            visited[adjIndex] = 1;
            if (visit != nullptr) {
                (*visit)(m_vertices[adjIndex]);
            }
            q.push(adjIndex);
        }
    }
}

template <class V, class W, W inf>
void AdjListWUndirGraph<V, W, inf>::dfs(const V& src, void (*visit)(const V&)) const
{
    IndexType srcIndex = getIndexOfVertex(src);
    checkIndex(srcIndex);

    std::vector<uint8_t> visited(m_vertices.size(), 0);
    _dfs(srcIndex, visited, visit);
}

template <class V, class W, W inf>
void AdjListWUndirGraph<V, W, inf>::dfs(void (*visit)(const V&)) const
{
    std::vector<uint8_t> visited(m_vertices.size(), 0);
    for (IndexType fromIndex = 0; fromIndex < (IndexType) m_vertices.size();
         ++fromIndex) {
        if (visited[fromIndex] == 0) {
            _dfs(fromIndex, visited, visit);
        }
    }
}

template <class V, class W, W inf>
void AdjListWUndirGraph<V, W, inf>::bfs(const V& src, void (*visit)(const V&)) const
{
    IndexType srcIndex = getIndexOfVertex(src);
    checkIndex(srcIndex);

    std::vector<uint8_t> visited(m_vertices.size(), 0);
    _bfs(srcIndex, visited, visit);
}

template <class V, class W, W inf>
void AdjListWUndirGraph<V, W, inf>::bfs(void (*visit)(const V&)) const
{
    std::vector<uint8_t> visited(m_vertices.size(), 0);
    for (IndexType fromIndex = 0; fromIndex < (IndexType) m_vertices.size();
         ++fromIndex) {
        if (visited[fromIndex] == 0) {
            _bfs(fromIndex, visited, visit);
        }
    }
}

template <class V, class W, W inf>
void AdjListWUndirGraph<V, W, inf>::clear()
{
    m_vertices.clear();
    m_adjLists.clear();
    m_numEdges = 0;
}

template <class V, class W, W inf>
void AdjListWUndirGraph<V, W, inf>::printAdjacentList(std::ostream& out) const
{
    if (m_vertices.empty()) {
        out << "None\n";
        return;
    }

    std::size_t max_width = 0;
    for (const auto& v : m_vertices) {
        max_width = std::max(max_width, std::format("{}", v).size());
    }
    for (IndexType fromIndex = 0; fromIndex < (IndexType) m_vertices.size();
         ++fromIndex) {
        out << std::format("{:>{}} | ", m_vertices[fromIndex], max_width);
        for (const auto& e : m_adjLists[fromIndex]) {
            out << std::format("{}({}) -> ", m_vertices[e.toIndex], e.weight);
        }
        out << "end\n";
    }
}

template <class V, class W, W inf>
void AdjListWUndirGraph<V, W, inf>::printEdges(std::ostream& out) const
{
    std::size_t edgeCnt = 0;
    for (IndexType fromIndex = 0; fromIndex < (IndexType) m_adjLists.size();
         ++fromIndex) {
        for (const auto& e : m_adjLists[fromIndex]) {
            if (fromIndex < e.toIndex) {
                ++edgeCnt;
                out << std::format("({0}) ({1}, {2}): {3}\n", edgeCnt,
                                   m_vertices[fromIndex], m_vertices[e.toIndex],
                                   e.weight);
            }
        }
    }

    if (edgeCnt == 0) {
        out << "None\n";
    }
}

}  // namespace myds
