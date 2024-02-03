#pragma once
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <unordered_set>
#include <limits>
#include "MyExceptions.h"

namespace MyDS
{
    template<class VertTy, class WeightTy, WeightTy infinity>
    class AdjMatWDirGraph;
}

namespace Algorithm
{
    template<class DistTy, DistTy infinity>
    struct PathNode
    {
        DistTy dist{ infinity };  // Distance from the source vertex.
        int prev{ std::numeric_limits<int>::max() };  // Index of the previous vertex.
    };

    template<class DistTy, DistTy infinity>
    struct VertNode  // For Dijkstra.
    {
        int toIndex{ std::numeric_limits<int>::max() };  // Index of the end vertex.
        DistTy dist{ infinity };  // Distance to the vertex.

        bool operator>(const VertNode<DistTy, infinity>& rhs) const
        {
            return dist > rhs.dist;
        }
    };

    template<class VertTy, class WeightTy, WeightTy infinity>
    void PrintPath(const std::vector<VertTy>& vertices, const std::vector<PathNode<WeightTy, infinity>>& paths,
        int sourceIndex, int endIndex, std::ostream& out)
    {
        if (paths[endIndex].dist == infinity)
        {
            out << "No Path." << std::endl;
            return;
        }

        std::stack<int> st;
        int curIndex = endIndex;
        while (curIndex != sourceIndex)
        {
            st.push(curIndex);
            curIndex = paths[curIndex].prev;
        }

        // Print the path.
        out << "The shortest path: " << vertices[sourceIndex];
        while (!st.empty())
        {
            out << "->" << vertices[st.top()];
            st.pop();
        }
        out << "\nLength: " << paths[endIndex].dist << std::endl;
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void Dijkstra(const MyDS::AdjMatWDirGraph<VertTy, WeightTy, infinity>& g,
        const VertTy& source, const VertTy& end, std::ostream* out = &std::cout)
    {
        // Check if the graph has negative weights.
        for (const auto& row : g.m_AdjMat)
        {
            for (const auto& w : row)
            {
                if (w < 0)
                    throw NegativeEdge();
            }
        }

        using PathNode = PathNode<WeightTy, infinity>;
        using VertNode = VertNode<WeightTy, infinity>;

        int vertNum = g.GetNumOfVertices();
        int sourceIndex = g.GetIndexOfVertex(source);
        int endIndex = g.GetIndexOfVertex(end);
        std::vector<PathNode> paths(vertNum);
        paths[sourceIndex].dist = 0;
        std::vector<uint8_t> visited(vertNum, 0);

        // Create and initialize the minimum heap.
        std::priority_queue<VertNode, std::vector<VertNode>, std::greater<VertNode>> minHeap;
        minHeap.push(VertNode{ sourceIndex, 0 });
        while (!minHeap.empty())
        {
            // Visit the nearest vertex.
            auto minVert = minHeap.top();
            minHeap.pop();
            int minVertIndex = minVert.toIndex;
            if (visited[minVertIndex] == 1)  // Skip visited vertices.
                continue;

            visited[minVertIndex] = 1;
            // Update the distance of its adjacent vertices if it is shorter.
            for (int j = 0; j < vertNum; j++)
            {
                if (j == minVertIndex || g.m_AdjMat[minVertIndex][j] == infinity)  // Skip itself and unreachable vertices.
                    continue;

                WeightTy tempDist = minVert.dist + g.m_AdjMat[minVertIndex][j];
                if (tempDist < paths[j].dist)
                {
                    // Update
                    paths[j] = { tempDist, minVertIndex };
                    minHeap.push(VertNode{ j, tempDist });
                }
            }
        }

        // Print the shortest path.
        if (out)
            PrintPath(g.m_Vertices, paths, sourceIndex, endIndex, *out);
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void BellmanFord(const MyDS::AdjMatWDirGraph<VertTy, WeightTy, infinity>& g,
        const VertTy& source, const VertTy& end, std::ostream* out = &std::cout)
    {
        int vertNum = g.GetNumOfVertices();
        int sourceIndex = g.GetIndexOfVertex(source);
        int endIndex = g.GetIndexOfVertex(end);

        // Initialize paths.
        using PathNode = PathNode<WeightTy, infinity>;
        std::vector<PathNode> paths(vertNum);
        paths[sourceIndex].dist = 0;

        // Loop for |V| - 1 times.
        bool relaxed = false;
        for (int i = 0; i < vertNum - 1; i++)
        {
            relaxed = false;
            // Traverse all edges.
            for (int fromIndex = 0; fromIndex < vertNum; fromIndex++)
            {
                if (paths[fromIndex].dist == infinity)
                    continue;
                ////if (fromIndex == sourceIndex || paths[fromIndex].dist == infinity)
                ////    continue;
                for (int toIndex = 0; toIndex < vertNum; toIndex++)
                {
                    if (g.m_AdjMat[fromIndex][toIndex] == infinity)  // Skip unreachable vertices.
                        continue;

                    WeightTy tempDist = paths[fromIndex].dist + g.m_AdjMat[fromIndex][toIndex];
                    if (tempDist < paths[toIndex].dist)
                    {
                        paths[toIndex] = PathNode{ tempDist, fromIndex };
                        relaxed = true;
                    }
                }
            }
            if (!relaxed)
                break;
        }

        if (relaxed)
        {
            // If edges can still be relaxed, there is a negative cycle.
            for (int fromIndex = 0; fromIndex < vertNum; fromIndex++)
            {
                if (paths[fromIndex].dist == infinity)  // Skip unreachable vertices.
                    continue;

                for (int toIndex = 0; toIndex < vertNum; toIndex++)
                {
                    if (g.m_AdjMat[fromIndex][toIndex] == infinity)
                        continue;

                    WeightTy tempDist = paths[fromIndex].dist + g.m_AdjMat[fromIndex][toIndex];
                    if (tempDist < paths[toIndex].dist)
                        throw NegativeCycle();
                }
            }
        }

        // Print the shortest path.
        if (out)
            PrintPath(g.m_Vertices, paths, sourceIndex, endIndex, *out);
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void FloydWarshall(const MyDS::AdjMatWDirGraph<VertTy, WeightTy, infinity>& g,
        const VertTy& source, const VertTy& end, std::ostream* out = &std::cout)
    {
        int vertNum = g.GetNumOfVertices();
        int sourceIndex = g.GetIndexOfVertex(source);
        int endIndex = g.GetIndexOfVertex(end);

        // Initialize paths.
        using PathNode = PathNode<WeightTy, infinity>;
        std::vector<std::vector<PathNode>> paths(vertNum, std::vector<PathNode>(vertNum));
        for (int i = 0; i < vertNum; i++)
        {
            for (int j = 0; j < vertNum; j++)
            {
                paths[i][j].dist = (i == j) ? 0 : g.m_AdjMat[i][j];
                if (i != j && g.m_AdjMat[i][j] != infinity)
                    paths[i][j].prev = i;
            }
        }

        // Find the shortest paths for each pair of vertices.
        for (int k = 0; k < vertNum; k++)
        {
            for (int i = 0; i < vertNum; i++)
            {
                for (int j = 0; j < vertNum; j++)
                {
                    if (paths[i][k].dist == infinity || paths[k][j].dist == infinity)
                        continue;
                    WeightTy tempDist = paths[i][k].dist + paths[k][j].dist;

                    // If the distance from a vertex to itself is negative, there is a negative cycle.
                    if (i == j)
                    {
                        if (tempDist < 0)
                            throw NegativeCycle();
                        continue;
                    }
                    // If the distance from i to j through k is shorter, update the path.
                    if (tempDist < paths[i][j].dist)
                        paths[i][j] = PathNode{ tempDist, paths[k][j].prev };
                }
            }
        }

        // Print the shortest path.
        if (out)
            PrintPath(g.m_Vertices, paths[sourceIndex], sourceIndex, endIndex, *out);
    }
}