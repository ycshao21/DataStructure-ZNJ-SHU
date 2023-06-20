#pragma once
#include<iostream>
#include<stack>
#include<queue>
#include<vector>
#include<unordered_set>
#include<limits>
#include"../../Tools/MyExceptions.h"

template<class VertTy, class WeightTy, WeightTy infinity>
class AdjMatWDirGraph;

namespace ShortestPath
{
    using indext = size_t;
    using sizet = size_t;

    template<class DistTy, DistTy infinity>
    struct PathNode
    {
        DistTy dist{ infinity };  // Distance from the source vertex.
        indext prev{ std::numeric_limits<indext>::max() };  // Index of the previous vertex.
    };

    template<class DistTy, DistTy infinity>
    struct VertNode  // For Dijkstra.
    {
        indext toIndex{ std::numeric_limits<indext>::max() };  // Index of the end vertex.
        DistTy dist{ infinity };  // Distance to the vertex.

        bool operator>(const VertNode<DistTy, infinity>& rhs) const {
            return dist > rhs.dist;
        }
    };

    template<class VertTy, class WeightTy, WeightTy infinity>
    void printPath(const std::vector<VertTy>& vertices, const std::vector<PathNode<WeightTy, infinity>>& paths,
        indext sourceIndex, indext endIndex, std::ostream& out) {
        std::stack<indext> st;
        if (paths[endIndex].dist == infinity) {
            out << "无路径" << std::endl;
            return;
        }
        indext curIndex = endIndex;
        while (curIndex != sourceIndex) {
            st.push(curIndex);
            curIndex = paths[curIndex].prev;
        }
        // Print the path.
        out << "最短路径：" << vertices[sourceIndex];
        while (!st.empty()) {
            out << "->" << vertices[st.top()];
            st.pop();
        }
        out << "\n长度：" << paths[endIndex].dist << std::endl;
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void Dijkstra(const AdjMatWDirGraph<VertTy, WeightTy, infinity>& g,
        const VertTy& source, const VertTy& end, std::ostream* out = &std::cout) {
        // Check if the graph has negative weights.
        for (const auto& row : g._adjMat) {
            for (const auto& w : row) {
                if (w < 0) {
                    throw NegativeEdge();
                }
            }
        }

        using PathNode = PathNode<WeightTy, infinity>;
        using VertNode = VertNode<WeightTy, infinity>;

        sizet vertNum = g.numOfVertices();
        indext sourceIndex = g.indexOfVertex(source);
        indext endIndex = g.indexOfVertex(end);
        std::vector<PathNode> paths(vertNum);
        paths[sourceIndex].dist = 0;
        std::vector<uint8_t> visited(vertNum, 0);

        // Create and initialize the minimum heap.
        std::priority_queue<VertNode, std::vector<VertNode>, std::greater<VertNode>> minHeap;
        minHeap.push(VertNode{ sourceIndex, 0 });
        while (!minHeap.empty()) {
            // Visit the nearest vertex.
            auto minVert = minHeap.top();
            minHeap.pop();
            indext minVertIndex = minVert.toIndex;
            if (visited[minVertIndex] == 1) { continue; }
            visited[minVertIndex] = 1;
            // Update the distance of its adjacent vertices if it is shorter.
            for (indext j = 0; j < vertNum; j++) {
                if (j == minVertIndex || g._adjMat[minVertIndex][j] == infinity) { continue; }
                WeightTy tempDist = minVert.dist + g._adjMat[minVertIndex][j];
                if (tempDist < paths[j].dist) {
                    paths[j] = { tempDist, minVertIndex };
                    minHeap.push(VertNode{ j, tempDist });
                }
            }
        }
        // Print the shortest path.
        if (out != nullptr) {
            printPath(g._vertices, paths, sourceIndex, endIndex, *out);
        }
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void BellmanFord(const AdjMatWDirGraph<VertTy, WeightTy, infinity>& g,
        const VertTy& source, const VertTy& end, std::ostream* out = &std::cout)
    {
        using PathNode = PathNode<WeightTy, infinity>;
        sizet vertNum = g.numOfVertices();
        indext sourceIndex = g.indexOfVertex(source);
        indext endIndex = g.indexOfVertex(end);
        // Initialize paths.
        std::vector<PathNode> paths(vertNum);
        paths[sourceIndex].dist = 0;
        // Loop for |V| - 1 times.
        bool relaxed = false;
        for (indext i = 0; i < vertNum - 1; i++) {
            relaxed = false;
            // Traverse all edges.
            for (indext fromIndex = 0; fromIndex < vertNum; fromIndex++) {
                if (paths[fromIndex].dist == infinity) { continue; }
                //if (fromIndex == sourceIndex || paths[fromIndex].dist == infinity) { continue; }
                for (indext toIndex = 0; toIndex < vertNum; toIndex++) {
                    if (g._adjMat[fromIndex][toIndex] == infinity) { continue; }
                    WeightTy tempDist = paths[fromIndex].dist + g._adjMat[fromIndex][toIndex];
                    if (tempDist < paths[toIndex].dist) {
                        paths[toIndex] = PathNode{ tempDist, fromIndex };
                        relaxed = true;
                    }
                }
            }
            if (!relaxed) { break; }
        }
        if (relaxed) {
            // If edges can still be relaxed, there is a negative cycle.
            for (indext fromIndex = 0; fromIndex < vertNum; fromIndex++) {
                if (paths[fromIndex].dist == infinity) { continue; }
                for (indext toIndex = 0; toIndex < vertNum; toIndex++) {
                    if (g._adjMat[fromIndex][toIndex] == infinity) { continue; }
                    WeightTy tempDist = paths[fromIndex].dist + g._adjMat[fromIndex][toIndex];
                    if (tempDist < paths[toIndex].dist) {
                        throw NegativeCycle();
                    }
                }
            }
        }
        // Print the shortest path.
        if (out != nullptr) {
            printPath(g._vertices, paths, sourceIndex, endIndex, *out);
        }
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void FloydWarshall(const AdjMatWDirGraph<VertTy, WeightTy, infinity>& g,
        const VertTy& source, const VertTy& end, std::ostream* out = &std::cout)
    {
        using PathNode = PathNode<WeightTy, infinity>;
        sizet vertNum = g.numOfVertices();
        indext sourceIndex = g.indexOfVertex(source);
        indext endIndex = g.indexOfVertex(end);
        // Initialize paths.
        std::vector<std::vector<PathNode>> paths(vertNum, std::vector<PathNode>(vertNum));
        for (indext i = 0; i < vertNum; i++) {
            for (indext j = 0; j < vertNum; j++) {
                paths[i][j].dist = (i == j) ? 0 : g._adjMat[i][j];
                if (i != j && g._adjMat[i][j] != infinity) {
                    paths[i][j].prev = i;
                }
            }
        }
        // Find the shortest paths for each pair of vertices.
        for (indext k = 0; k < vertNum; k++) {
            for (indext i = 0; i < vertNum; i++) {
                for (indext j = 0; j < vertNum; j++) {
                    if (paths[i][k].dist == infinity || paths[k][j].dist == infinity) { continue; }
                    WeightTy tempDist = paths[i][k].dist + paths[k][j].dist;
                    // If the distance from a vertex to itself is negative, there is a negative cycle.
                    if (i == j) {
                        if (tempDist < 0) {
                            throw NegativeCycle();
                        }
                        continue;
                    }
                    // If the distance from i to j through k is shorter, update the path.
                    if (tempDist < paths[i][j].dist) {
                        paths[i][j] = PathNode{ tempDist, paths[k][j].prev };
                    }
                }
            }
        }
        // Print the shortest path.
        if (out != nullptr) {
            printPath(g._vertices, paths[sourceIndex], sourceIndex, endIndex, *out);
        }
    }
}