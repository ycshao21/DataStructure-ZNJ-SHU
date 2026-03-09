#pragma once
#include <cstdint>
#include <format>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

#include "graph_exceptions.hpp"

namespace myds
{
template <class V, class W, W inf>
class AdjMatWDirGraph;
}

namespace algorithm
{
using IndexType = std::int64_t;

template <class V>
void printPath(const std::vector<V>& vertices, const std::vector<IndexType>& path,
               IndexType srcIndex, IndexType endIndex, std::ostream& out)
{
    std::stack<IndexType> st;
    IndexType curIndex = endIndex;
    while (curIndex != srcIndex) {
        st.push(curIndex);
        curIndex = path[curIndex];
    }

    out << vertices[srcIndex];
    while (!st.empty()) {
        out << std::format("->{}", vertices[st.top()]);
        st.pop();
    }
}

template <class V, class W, W inf>
void dijkstra(const myds::AdjMatWDirGraph<V, W, inf>& g, const V& src, const V& end,
              std::ostream* out = &std::cout)
{
    // Check if the graph has negative weights.
    for (const auto& row : g.m_adjMat) {
        for (const W& w : row) {
            if (w != inf && w < 0) {
                throw NegativeEdgeException();
            }
        }
    }

    std::size_t numVertices = g.getNumOfVertices();

    IndexType srcIndex = g.getIndexOfVertex(src);
    g.checkIndex(srcIndex);

    IndexType endIndex = g.getIndexOfVertex(end);
    g.checkIndex(endIndex);

    std::vector<uint8_t> visited(numVertices, 0);
    std::vector<W> dists(numVertices, inf);
    dists[srcIndex] = 0;
    std::vector<IndexType> path(numVertices, -1);

    struct VertexNode
    {
        W dist = inf;            // Distance to the vertex.
        IndexType toIndex = -1;  // Index of the end vertex.

        bool operator>(const VertexNode& rhs) const
        {
            return dist > rhs.dist;
        }
    };
    std::priority_queue<VertexNode, std::vector<VertexNode>, std::greater<>> minHeap;
    minHeap.emplace(0, srcIndex);

    while (!minHeap.empty()) {
        auto [minDist, u] = minHeap.top();
        minHeap.pop();

        // Skip visited vertices.
        if (visited[u] == 1) {
            continue;
        }

        visited[u] = 1;

        // Update the distance of its adjacent vertices if it is shorter.
        for (IndexType v = 0; v < (IndexType) numVertices; ++v) {
            if (visited[v] == 0 &&
                g.m_adjMat[u][v] != inf) {  // Skip itself and unreachable vertices.
                W newDist = minDist + g.m_adjMat[u][v];
                if (newDist < dists[v]) {
                    // Update
                    dists[v] = newDist;
                    path[v] = u;
                    minHeap.emplace(newDist, v);
                }
            }
        }
    }

    // Print the shortest path.
    if (out) {
        if (dists[endIndex] == inf) {
            (*out) << "No path.\n";
            return;
        }
        (*out) << "Shortest path: ";
        printPath(g.m_vertices, path, srcIndex, endIndex, *out);
        (*out) << std::format("\nDistance: {}\n", dists[endIndex]);
    }
}

template <class V, class W, W inf>
void bellmanFord(const myds::AdjMatWDirGraph<V, W, inf>& g, const V& src, const V& end,
                 std::ostream* out = &std::cout)
{
    std::size_t numVertices = g.getNumOfVertices();

    IndexType srcIndex = g.getIndexOfVertex(src);
    g.checkIndex(srcIndex);

    IndexType endIndex = g.getIndexOfVertex(end);
    g.checkIndex(endIndex);

    std::vector<W> dists(numVertices, inf);
    dists[srcIndex] = 0;
    std::vector<IndexType> path(numVertices, -1);

    // Loop for |V| - 1 times.
    bool relaxed = false;
    for (std::size_t t = 0; t < numVertices - 1; ++t) {
        relaxed = false;
        // Traverse all edges.
        for (IndexType u = 0; u < (IndexType) numVertices; ++u) {
            if (dists[u] == inf) {
                continue;
            }
            for (IndexType v = 0; v < (IndexType) numVertices; ++v) {
                if (g.m_adjMat[u][v] == inf) {  // Skip unreachable vertices.
                    continue;
                }

                W newDist = dists[u] + g.m_adjMat[u][v];
                if (newDist < dists[v]) {
                    dists[v] = newDist;
                    path[v] = u;
                    relaxed = true;
                }
            }
        }
        if (!relaxed) {
            break;
        }
    }

    if (relaxed) {
        // If edges can still be relaxed, there is a negative cycle.
        for (IndexType u = 0; u < (IndexType) numVertices; ++u) {
            // Skip unreachable vertices.
            if (dists[u] == inf) {
                continue;
            }

            for (IndexType v = 0; v < (IndexType) numVertices; ++v) {
                if (g.m_adjMat[u][v] == inf) {
                    continue;
                }

                W newDist = dists[u] + g.m_adjMat[u][v];
                if (newDist < dists[v]) {
                    throw NegativeCycleException();
                }
            }
        }
    }

    // Print the shortest path.
    if (out) {
        if (dists[endIndex] == inf) {
            (*out) << "No path.\n";
            return;
        }
        (*out) << "Shortest path: ";
        printPath(g.m_vertices, path, srcIndex, endIndex, *out);
        (*out) << std::format("\nDistance: {}\n", dists[endIndex]);
    }
}

template <class V, class W, W inf>
void floydWarshall(const myds::AdjMatWDirGraph<V, W, inf>& g, const V& src, const V& end,
                   std::ostream* out = &std::cout)
{
    std::size_t numVertices = g.getNumOfVertices();

    IndexType srcIndex = g.getIndexOfVertex(src);
    g.checkIndex(srcIndex);

    IndexType endIndex = g.getIndexOfVertex(end);
    g.checkIndex(endIndex);

    std::vector<std::vector<W>> dists(numVertices, std::vector<W>(numVertices));
    for (IndexType u = 0; u < (IndexType) numVertices; ++u) {
        for (IndexType v = 0; v < (IndexType) numVertices; ++v) {
            dists[u][v] = (u == v) ? 0 : g.m_adjMat[u][v];
        }
    }

    std::vector<std::vector<IndexType>> paths(numVertices,
                                              std::vector<IndexType>(numVertices, -1));
    for (IndexType u = 0; u < (IndexType) numVertices; ++u) {
        for (IndexType v = 0; v < (IndexType) numVertices; ++v) {
            if (u != v && g.m_adjMat[u][v] != inf) {
                paths[u][v] = u;
            }
        }
    }

    // Find the shortest paths for each pair of vertices.
    for (IndexType k = 0; k < (IndexType) numVertices; ++k) {
        for (IndexType i = 0; i < (IndexType) numVertices; ++i) {
            for (IndexType j = 0; j < (IndexType) numVertices; ++j) {
                if (dists[i][k] == inf || dists[k][j] == inf) {
                    continue;
                }
                W newDist = dists[i][k] + dists[k][j];

                if (i == j) {
                    // If the distance from a vertex to itself is negative, there is a
                    // negative cycle.
                    if (newDist < 0) {
                        throw NegativeCycleException();
                    }
                } else {
                    // If the distance from i to j through k is shorter, update the path.
                    if (newDist < dists[i][j]) {
                        dists[i][j] = newDist;
                        paths[i][j] = paths[k][j];
                    }
                }
            }
        }
    }

    // Print the shortest path.
    if (out) {
        if (dists[srcIndex][endIndex] == inf) {
            (*out) << "No path.\n";
            return;
        }
        (*out) << "Shortest path: ";
        printPath(g.m_vertices, paths[srcIndex], srcIndex, endIndex, *out);
        (*out) << std::format("\nDistance: {}\n", dists[srcIndex][endIndex]);
    }
}
}  // namespace algorithm