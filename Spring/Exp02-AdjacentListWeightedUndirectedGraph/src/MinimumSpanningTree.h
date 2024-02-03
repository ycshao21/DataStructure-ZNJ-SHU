#pragma once
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <vector>
#include <queue>
#include <stack>
#include <limits>
#include "AdjListEdge.h"
#include "DisjointSet.h"
#include "MyExceptions.h"

namespace MyDS
{
    template<class VertTy, class WeightTy, WeightTy infinity>
    class AdjListWUndirGraph;
}

namespace Algorithm
{
    template<class WeightTy>
    struct MST_Edge
    {
        int fromIndex{};
        int toIndex{};
        WeightTy weight{};

        bool operator>(const MST_Edge<WeightTy>& edge) const
        {
            return weight > edge.weight;
        }
        bool operator<(const MST_Edge<WeightTy>& edge) const
        {
            return weight < edge.weight;
        }
    };

    template<class VertTy, class WeightTy, WeightTy infinity>
    void CheckGraph(const MyDS::AdjListWUndirGraph<VertTy, WeightTy, infinity>& g)
    {
        // The graph must have at least one vertex.
        if (g.GetNumOfVertices() == 0)
            throw NoVertex();

        // If the graph is not connected, there is no MST.
        if (!g.IsConnected())
            throw GraphDisconnected();
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    WeightTy Kruskal(const MyDS::AdjListWUndirGraph<VertTy, WeightTy, infinity>& g, std::ostream* out = &std::cout)
    {
        int vertNum = g.GetNumOfVertices();
        if (vertNum == 1)
        {
            if (out)
                (*out) << "No edge.\n"
                       << "Total weight: 0" << std::endl;
            return 0;
        }

        CheckGraph(g);

        // Create a disjoint set.
        MyDS::DisjointSet vertSet(vertNum);
        // Create a minimum heap and add all edges to it.
        using MST_Edge = MST_Edge<WeightTy>;
        std::priority_queue<MST_Edge, std::vector<MST_Edge>, std::greater<MST_Edge>> minHeap;
        for (int fromIndex = 0; fromIndex < vertNum - 1; fromIndex++)
        {
            for (const auto& e : g.m_AdjList[fromIndex])
            {
                if (fromIndex < e.toIndex)
                    minHeap.push(MST_Edge{ fromIndex, e.toIndex, e.weight });
            }
        }

        std::ostringstream ss;
        WeightTy totalWeight = 0;
        // MST has vertNum - 1 edges in total.
        for (int cnt = 0; cnt < vertNum - 1;)
        {
            MST_Edge curEdge = minHeap.top();
            minHeap.pop();
            auto fromRoot = vertSet.GetRootIndex(curEdge.fromIndex);
            auto toRoot = vertSet.GetRootIndex(curEdge.toIndex);

            // If vertices of the edge does not belong to the same set, add it to the MST.
            if (fromRoot != toRoot)
            {
                vertSet.Unite(fromRoot, toRoot);
                ss << "(" << ++cnt << ") "
                    << "(" << g.m_Vertices[curEdge.fromIndex] << ", " << g.m_Vertices[curEdge.toIndex] << "): "
                    << curEdge.weight << std::endl;
                totalWeight += curEdge.weight;
            }
        }
        ss << "\nTotal weight: " << totalWeight << std::endl;
        if (out)
            (*out) << ss.str();

        return totalWeight;
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    WeightTy Prim(const MyDS::AdjListWUndirGraph<VertTy, WeightTy, infinity>& g, std::ostream* out = &std::cout)
    {
        int vertNum = g.GetNumOfVertices();
        if (vertNum == 1)
        {
            if (out)
                (*out) << "No edge.\n" <<
                    "Total weight: 0" << std::endl;
            return 0;
        }

        CheckGraph(g);

        // Initialize the minimum heap.
        using MST_Edge = MST_Edge<WeightTy>;
        std::priority_queue<MST_Edge, std::vector<MST_Edge>, std::greater<MST_Edge>> minHeap;
        for (const auto& e : g.m_AdjList[0])
            minHeap.push(MST_Edge{ 0, e.toIndex, e.weight });

        std::vector<uint8_t> visited(vertNum, 0);
        visited[0] = 1;

        // Find suitable edges.
        WeightTy totalWeight = 0;
        int cnt = 0;
        std::ostringstream ss;
        while (!minHeap.empty())
        {
            MST_Edge curEdge = minHeap.top();
            minHeap.pop();

            // Select the edges with unvisited vertices with the minimum weight.
            if (visited[curEdge.toIndex] == 1)
                continue;

            visited[curEdge.toIndex] = 1;
            ss << "(" << ++cnt << ") "
                << "(" << g.m_Vertices[curEdge.fromIndex] << ", " << g.m_Vertices[curEdge.toIndex] << "): "
                << curEdge.weight << std::endl;
            totalWeight += curEdge.weight;

            // Update edges with unvisited vertices.
            for (const auto& e : g.m_AdjList[curEdge.toIndex])
            {
                if (!visited[e.toIndex])
                    minHeap.push(MST_Edge{ curEdge.toIndex, e.toIndex, e.weight });
            }
        }
        ss << "\nTotal weight: " << totalWeight << std::endl;
        if (out)
            (*out) << ss.str();

        return totalWeight;
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    WeightTy ReverseDelete(const MyDS::AdjListWUndirGraph<VertTy, WeightTy, infinity>& g, std::ostream* out = &std::cout)
    {
        int vertNum = g.GetNumOfVertices();
        if (vertNum == 1)
        {
            if (out)
                (*out) << "No edge.\n"
                    << "Total weight: 0" << std::endl;
            return 0;
        }

        CheckGraph(g);

        // Initialize the maximum heap.
        using MST_Edge = MST_Edge<WeightTy>;
        std::priority_queue<MST_Edge> maxHeap;
        for (int fromIndex = 0; fromIndex < vertNum - 1; fromIndex++)
        {
            for (const auto& e : g.m_AdjList[fromIndex])
            {
                if (fromIndex < e.toIndex)
                    maxHeap.push(MST_Edge{ fromIndex, e.toIndex, e.weight });
            }
        }
        // Copy the gragh.
        using Graph = MyDS::AdjListWUndirGraph<VertTy, WeightTy, infinity>;
        Graph mst(g);
        while (mst.GetNumOfEdges() > vertNum - 1)
        {
            MST_Edge curEdge = maxHeap.top();
            maxHeap.pop();

            // Remove the edge:
            auto fromIter = std::ranges::find_if(mst.m_AdjList[curEdge.fromIndex], Graph::FindEdgeFn(curEdge.toIndex));
            mst.m_AdjList[curEdge.fromIndex].erase(fromIter);
            auto toIter = std::ranges::find_if(mst.m_AdjList[curEdge.toIndex], Graph::FindEdgeFn(curEdge.fromIndex));
            mst.m_AdjList[curEdge.toIndex].erase(toIter);
            mst.m_EdgeNum--;

            // Add the edge back if it breaks the connectivity.
            if (!mst.IsConnected())
            {
                mst.m_AdjList[curEdge.fromIndex].push_front(MyDS::AdjListEdge{ curEdge.toIndex, curEdge.weight });
                mst.m_AdjList[curEdge.toIndex].push_front(MyDS::AdjListEdge{ curEdge.fromIndex, curEdge.weight });
                mst.m_EdgeNum++;
            }
        }

        // Traverse the MST.
        std::ostringstream ss;
        WeightTy totalWeight = 0;
        int cnt = 0;
        for (int fromIndex = 0; fromIndex < vertNum; fromIndex++)
        {
            for (const auto& e : mst.m_AdjList[fromIndex])
            {
                if (fromIndex < e.toIndex)
                {
                    ss << "(" << ++cnt << ") "
                        << "(" << mst.m_Vertices[fromIndex] << ", " << mst.m_Vertices[e.toIndex] << "): "
                        << e.weight << std::endl;
                    totalWeight += e.weight;
                }
            }
        }
        ss << "\nTotal weight: " << totalWeight << std::endl;
        if (out)
            (*out) << ss.str();

        return totalWeight;
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    bool TreeFindPath(const MyDS::AdjListWUndirGraph<VertTy, WeightTy, infinity>& tree,
        int prevIndex, int fromIndex, int endIndex, std::stack<MST_Edge<WeightTy>>& path)
    {
        if (fromIndex == endIndex)
            return true;

        for (const auto& e : tree.m_AdjList[fromIndex])
        {
            if (e.toIndex == prevIndex)
                continue;

            path.push(MST_Edge<WeightTy>{ fromIndex, e.toIndex, e.weight });
            if (TreeFindPath(tree, fromIndex, e.toIndex, endIndex, path))
                return true;

            path.pop();
        }
        return false;
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    bool IsUnique(const MyDS::AdjListWUndirGraph<VertTy, WeightTy, infinity>& g)
    {
        int vertNum = g.GetNumOfVertices();
        if (vertNum == 1)
            return true;
        CheckGraph(g);

        // Initialize another graph for MST:
        MyDS::AdjListWUndirGraph<VertTy, WeightTy, infinity> mst;
        mst.m_Vertices = g.m_Vertices;
        mst.m_AdjList.resize(vertNum);

        // Use Kruskal algorithm to find an MST and store the discarded edges:
        MyDS::DisjointSet vertSet(vertNum);
        using MST_Edge = MST_Edge<WeightTy>;

        std::priority_queue<MST_Edge, std::vector<MST_Edge>, std::greater<MST_Edge>> minHeap;
        for (int fromIndex = 0; fromIndex < vertNum - 1; fromIndex++)
        {
            for (const auto& e : g.m_AdjList[fromIndex])
            {
                if (fromIndex < e.toIndex)
                    minHeap.push(MST_Edge{ fromIndex, e.toIndex, e.weight });
            }
        }
        std::vector<MST_Edge> discardedEdges;

        for (int cnt = 0; cnt < vertNum - 1;)
        {
            MST_Edge curEdge = minHeap.top();
            minHeap.pop();
            auto fromRoot = vertSet.GetRootIndex(curEdge.fromIndex);
            auto toRoot = vertSet.GetRootIndex(curEdge.toIndex);
            if (fromRoot != toRoot)
            {
                vertSet.Unite(fromRoot, toRoot);
                cnt++;

                // Add the edge to the MST:
                mst.m_AdjList[curEdge.fromIndex].push_front(MyDS::AdjListEdge{ curEdge.toIndex, curEdge.weight });
                mst.m_AdjList[curEdge.toIndex].push_front(MyDS::AdjListEdge{ curEdge.fromIndex, curEdge.weight });
                mst.m_EdgeNum++;
            }
            else
            {
                discardedEdges.push_back(curEdge);
            }
        }
        while (!minHeap.empty())
        {
            discardedEdges.push_back(minHeap.top());
            minHeap.pop();
        }

        // Check if the weight of any discarded edge is greater than
        // other edges in the circle formed with the edge:
        std::stack<MST_Edge> path;
        for (const auto& e : discardedEdges)
        {
            TreeFindPath(mst, std::numeric_limits<int>::max(), e.fromIndex, e.toIndex, path);
            while (!path.empty())
            {
                if (e.weight <= path.top().weight)
                    return false;

                path.pop();
            }
        }
        return true;
    }
}
