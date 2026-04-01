#pragma once
#include <format>
#include <iostream>
#include <limits>
#include <print>
#include <queue>
#include <sstream>
#include <stack>
#include <unordered_set>
#include <vector>

#include "disjoint_set.hpp"
#include "graph_exceptions.hpp"

// Avoid circular includes
namespace myds
{
template <class V, class W, W inf>
class AdjListWUndirGraph;
}  // namespace myds

namespace algorithm
{
using IndexType = std::int64_t;

template <class W>
struct MSTEdge
{
    IndexType fromIndex{};
    IndexType toIndex{};
    W weight{};

    bool operator>(const MSTEdge<W>& e) const
    {
        return weight > e.weight;
    }
    bool operator<(const MSTEdge<W>& e) const
    {
        return weight < e.weight;
    }
};

template <class V, class W, W inf>
void validateGraphForMST(const myds::AdjListWUndirGraph<V, W, inf>& g)
{
    // The graph must have at least one vertex.
    if (g.getNumOfVertices() == 0) {
        throw NoVertexException();
    }

    // If the graph is not connected, there is no MST.
    if (!g.isConnected()) {
        throw GraphDisconnectedException();
    }
}

template <class V, class W, W inf>
W kruskal(const myds::AdjListWUndirGraph<V, W, inf>& g, std::ostream* out = &std::cout)
{
    std::size_t numVertices = g.getNumOfVertices();
    if (numVertices == 1) {
        if (out) {
            std::println(*out, "No edge.");
            std::println(*out, "Total weight: 0");
        }
        return 0;
    }

    validateGraphForMST(g);

    // Create a disjoint set.
    myds::DisjointSet vertSet(numVertices);
    // Create a minimum heap and add all edges to it.
    using MSTEdge = MSTEdge<W>;
    std::priority_queue<MSTEdge, std::vector<MSTEdge>, std::greater<MSTEdge>> minHeap;
    for (IndexType fromIndex = 0; fromIndex < (IndexType) (numVertices - 1);
         ++fromIndex) {
        for (const auto& e : g.m_adjLists[fromIndex]) {
            if (fromIndex < e.toIndex) {
                minHeap.push({fromIndex, e.toIndex, e.weight});
            }
        }
    }

    W totalWeight = 0;
    // MST has vertNum - 1 edges in total.
    for (std::size_t cnt = 0; cnt < numVertices - 1;) {
        MSTEdge curEdge = minHeap.top();
        minHeap.pop();
        auto fromRoot = vertSet.getRootIndex(curEdge.fromIndex);
        auto toRoot = vertSet.getRootIndex(curEdge.toIndex);

        // If vertices of the edge does not belong to the same set, add it to the
        // MST.
        if (fromRoot != toRoot) {
            vertSet.unite(fromRoot, toRoot);
            ++cnt;
            if (out) {
                std::println(*out, "({}) ({}, {}): {}", cnt,
                             g.m_vertices[curEdge.fromIndex],
                             g.m_vertices[curEdge.toIndex], curEdge.weight);
            }
            totalWeight += curEdge.weight;
        }
    }
    if (out) {
        std::println(*out, "Total weight: {}", totalWeight);
    }
    return totalWeight;
}

template <class V, class W, W inf>
W prim(const myds::AdjListWUndirGraph<V, W, inf>& g, std::ostream* out = &std::cout)
{
    std::size_t numVertices = g.getNumOfVertices();
    if (numVertices == 1) {
        if (out) {
            std::println(*out, "No edge.");
            std::println(*out, "Total weight: 0");
        }
        return 0;
    }

    validateGraphForMST(g);

    // Initialize the minimum heap.
    using MSTEdge = MSTEdge<W>;
    std::priority_queue<MSTEdge, std::vector<MSTEdge>, std::greater<MSTEdge>> minHeap;
    for (const auto& e : g.m_adjLists[0]) {
        minHeap.push({0, e.toIndex, e.weight});
    }

    std::vector<uint8_t> visited(numVertices, 0);
    visited[0] = 1;

    // Find suitable edges.
    W totalWeight = 0;
    std::size_t cnt = 0;
    while (!minHeap.empty()) {
        MSTEdge curEdge = minHeap.top();
        minHeap.pop();

        // Select the edges with unvisited vertices with the minimum weight.
        if (visited[curEdge.toIndex] == 1) {
            continue;
        }
        visited[curEdge.toIndex] = 1;

        ++cnt;
        if (out) {
            std::println(*out, "({}) ({}, {}): {}", cnt, g.m_vertices[curEdge.fromIndex],
                         g.m_vertices[curEdge.toIndex], curEdge.weight);
        }
        totalWeight += curEdge.weight;

        // Update edges with unvisited vertices.
        for (const auto& e : g.m_adjLists[curEdge.toIndex]) {
            if (!visited[e.toIndex]) {
                minHeap.push(MSTEdge{curEdge.toIndex, e.toIndex, e.weight});
            }
        }
    }
    if (out) {
        std::println(*out, "Total weight: {}", totalWeight);
    }
    return totalWeight;
}

template <class V, class W, W inf>
W reverseDelete(const myds::AdjListWUndirGraph<V, W, inf>& g,
                std::ostream* out = &std::cout)
{
    std::size_t numVertices = g.getNumOfVertices();
    if (numVertices == 1) {
        if (out) {
            std::println(*out, "No edge.");
            std::println(*out, "Total weight: 0");
        }
        return 0;
    }

    validateGraphForMST(g);

    // Initialize the maximum heap.
    using MSTEdge = MSTEdge<W>;
    std::priority_queue<MSTEdge> maxHeap;
    for (IndexType fromIndex = 0; fromIndex < (IndexType) (numVertices - 1);
         ++fromIndex) {
        for (const auto& e : g.m_adjLists[fromIndex]) {
            if (fromIndex < e.toIndex) {
                maxHeap.push(MSTEdge{fromIndex, e.toIndex, e.weight});
            }
        }
    }

    // Copy the gragh.
    using Graph = myds::AdjListWUndirGraph<V, W, inf>;
    Graph mst(g);

    while (mst.getNumOfEdges() >= numVertices) {
        MSTEdge curEdge = maxHeap.top();
        maxHeap.pop();

        // Remove the edge
        std::erase_if(mst.m_adjLists[curEdge.fromIndex],
                      typename Graph::FindEdgeFn(curEdge.toIndex));
        std::erase_if(mst.m_adjLists[curEdge.toIndex],
                      typename Graph::FindEdgeFn(curEdge.fromIndex));

        // Add the edge back if it breaks the connectivity.
        if (!mst.isConnected()) {
            mst.m_adjLists[curEdge.fromIndex].push_front(
                {curEdge.toIndex, curEdge.weight});
            mst.m_adjLists[curEdge.toIndex].push_front(
                {curEdge.fromIndex, curEdge.weight});
            continue;
        }

        --mst.m_numEdges;
    }

    // Traverse the MST.
    W totalWeight = 0;
    std::size_t cnt = 0;
    for (IndexType fromIndex = 0; fromIndex < (IndexType) numVertices; ++fromIndex) {
        for (const auto& e : mst.m_adjLists[fromIndex]) {
            if (fromIndex < e.toIndex) {
                if (out) {
                    std::println(*out, "({}) ({}, {}): {}", ++cnt, mst.m_vertices[fromIndex],
                                 mst.m_vertices[e.toIndex], e.weight);
                }
                totalWeight += e.weight;
            }
        }
    }
    if (out) {
        std::println(*out, "Total weight: {}", totalWeight);
    }

    return totalWeight;
}

template <class V, class W, W inf>
bool findTreePath(const myds::AdjListWUndirGraph<V, W, inf>& tree, IndexType prevIndex,
                  IndexType fromIndex, IndexType endIndex, std::stack<MSTEdge<W>>& path)
{
    if (fromIndex == endIndex) {
        return true;
    }

    for (const auto& e : tree.m_adjLists[fromIndex]) {
        if (e.toIndex == prevIndex) {
            continue;
        }

        path.push(MSTEdge<W>{fromIndex, e.toIndex, e.weight});
        if (findTreePath(tree, fromIndex, e.toIndex, endIndex, path)) {
            return true;
        }
        path.pop();
    }
    return false;
}

template <class V, class W, W inf>
bool hasUniqueMST(const myds::AdjListWUndirGraph<V, W, inf>& g)
{
    std::size_t numVertices = g.getNumOfVertices();
    if (numVertices == 1) {
        return true;
    }
    validateGraphForMST(g);

    // Initialize another graph for MST:
    using Graph = myds::AdjListWUndirGraph<V, W, inf>;
    Graph mst;
    mst.m_vertices = g.m_vertices;
    mst.m_adjLists.resize(numVertices);

    // Use Kruskal algorithm to find an MST and store the discarded edges:
    myds::DisjointSet vertexSet(numVertices);
    using MSTEdge = MSTEdge<W>;

    std::priority_queue<MSTEdge, std::vector<MSTEdge>, std::greater<MSTEdge>> minHeap;
    for (IndexType fromIndex = 0; fromIndex < (IndexType) (numVertices - 1);
         ++fromIndex) {
        for (const auto& e : g.m_adjLists[fromIndex]) {
            if (fromIndex < e.toIndex) {
                minHeap.push(MSTEdge{fromIndex, e.toIndex, e.weight});
            }
        }
    }
    std::vector<MSTEdge> discardedEdges;

    for (std::size_t cnt = 0; cnt < numVertices - 1;) {
        MSTEdge curEdge = minHeap.top();
        minHeap.pop();

        IndexType fromRoot = vertexSet.getRootIndex(curEdge.fromIndex);
        IndexType toRoot = vertexSet.getRootIndex(curEdge.toIndex);

        if (fromRoot != toRoot) {
            vertexSet.unite(fromRoot, toRoot);
            ++cnt;

            // Add the edge to the MST:
            mst.m_adjLists[curEdge.fromIndex].push_front(
                {curEdge.toIndex, curEdge.weight});
            mst.m_adjLists[curEdge.toIndex].push_front(
                {curEdge.fromIndex, curEdge.weight});
            ++mst.m_numEdges;
        } else {
            discardedEdges.push_back(curEdge);
        }
    }
    while (!minHeap.empty()) {
        discardedEdges.push_back(minHeap.top());
        minHeap.pop();
    }

    // Check if the weight of any discarded edge is greater than
    // other edges in the circle formed with the edge:
    std::stack<MSTEdge> path;
    for (const auto& e : discardedEdges) {
        findTreePath(mst, std::numeric_limits<int>::max(), e.fromIndex, e.toIndex, path);
        while (!path.empty()) {
            if (e.weight <= path.top().weight) {
                return false;
            }
            path.pop();
        }
    }
    return true;
}
}  // namespace algorithm
