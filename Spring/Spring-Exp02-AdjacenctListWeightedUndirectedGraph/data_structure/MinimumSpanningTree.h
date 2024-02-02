#pragma once
#include<iostream>
#include<sstream>
#include<unordered_set>
#include<vector>
#include<queue>
#include<stack>
#include<limits>
#include"AdjListEdge.h"
#include"DisjointSet.h"
#include"../../Tools/MyExceptions.h"

template<class VertTy, class WeightTy, WeightTy infinity>
class AdjListWUndirGraph;

namespace MST
{
    using indext = size_t;
    using sizet = size_t;

    template<class WeightTy>
    struct MST_Edge
    {
        indext fromIndex{};
        indext toIndex{};
        WeightTy weight{};

        bool operator>(const MST_Edge<WeightTy>& edge) const {
            return weight > edge.weight;
        }
        bool operator<(const MST_Edge<WeightTy>& edge) const {
            return weight < edge.weight;
        }
    };

    template<class VertTy, class WeightTy, WeightTy infinity>
    void CheckGraph(const AdjListWUndirGraph<VertTy, WeightTy, infinity>& g) {
        // The graph must have at least one vertex.
        if (g.numOfVertices() == 0) {
            throw NoVertex();
        }
        // If the graph is not connected, there is no MST.
        if (!g.connected()) {
            throw GraphDisconnected();
        }
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    WeightTy Kruskal(const AdjListWUndirGraph<VertTy, WeightTy, infinity>& g, std::ostream* out = &std::cout) {
        sizet vertNum = g.numOfVertices();
        if (vertNum == 1) {
            if (out) {
                (*out) << "No edge.\n"
                    << "Total weight: 0" << std::endl;
            }
            return 0;
        }

        CheckGraph(g);

        // Create a disjoint set.
        DisjointSet vertSet(vertNum);
        // Create a minimum heap and add all edges to it.
        using MST_Edge = MST_Edge<WeightTy>;
        std::priority_queue<MST_Edge, std::vector<MST_Edge>, std::greater<MST_Edge>> minHeap;
        for (indext fromIndex = 0; fromIndex < vertNum - 1; fromIndex++) {
            for (const auto& e : g._adjList[fromIndex]) {
                if (fromIndex < e.toIndex) {
                    minHeap.push(MST_Edge{ fromIndex, e.toIndex, e.weight });
                }
            }
        }

        std::ostringstream ss;
        WeightTy totalWeight = 0;
        // MST has vertNum - 1 edges in total.
        for (indext cnt = 0; cnt < vertNum - 1;) {
            MST_Edge curEdge = minHeap.top();
            minHeap.pop();
            auto fromRoot = vertSet.root(curEdge.fromIndex);
            auto toRoot = vertSet.root(curEdge.toIndex);
            // If vertices of the edge does not belong to the same set, add it to the MST.
            if (fromRoot != toRoot) {
                vertSet.unite(fromRoot, toRoot);
                ss << "(" << ++cnt << ") "
                    << "(" << g._vertices[curEdge.fromIndex] << ", " << g._vertices[curEdge.toIndex] << "): "
                    << curEdge.weight << std::endl;
                totalWeight += curEdge.weight;
            }
        }
        ss << "\nTotal weight: " << totalWeight << std::endl;
        if (out) {
            (*out) << ss.str();
        }
        return totalWeight;
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    WeightTy Prim(const AdjListWUndirGraph<VertTy, WeightTy, infinity>& g, std::ostream* out = &std::cout) {
        sizet vertNum = g.numOfVertices();
        if (vertNum == 1) {
            if (out) {
                (*out) << "No edge.\n" <<
                    "Total weight: 0" << std::endl;
            }
            return 0;
        }

        CheckGraph(g);

        // Initialize the minimum heap.
        using MST_Edge = MST_Edge<WeightTy>;
        std::priority_queue<MST_Edge, std::vector<MST_Edge>, std::greater<MST_Edge>> minHeap;
        for (const auto& e : g._adjList[0]) {
            minHeap.push(MST_Edge{ 0, e.toIndex, e.weight });
        }
        std::vector<uint8_t> visited(vertNum, 0);
        visited[0] = 1;

        //  Find suitable edges.
        WeightTy totalWeight = 0;
        indext cnt = 0;
        std::ostringstream ss;
        while (!minHeap.empty()) {
            MST_Edge curEdge = minHeap.top();
            minHeap.pop();
            // Select the edges with unvisited vertices with the minimum weight.
            if (visited[curEdge.toIndex] == 1) { continue; }
            visited[curEdge.toIndex] = 1;
            ss << "(" << ++cnt << ") "
                << "(" << g._vertices[curEdge.fromIndex] << ", " << g._vertices[curEdge.toIndex] << "): "
                << curEdge.weight << std::endl;
            totalWeight += curEdge.weight;
            // Update edges with unvisited vertices.
            for (const auto& e : g._adjList[curEdge.toIndex]) {
                if (!visited[e.toIndex]) {
                    minHeap.push(MST_Edge{ curEdge.toIndex, e.toIndex, e.weight });
                }
            }
        }
        ss << "\nTotal weight: " << totalWeight << std::endl;
        if (out != nullptr) {
            (*out) << ss.str();
        }
        return totalWeight;
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    WeightTy ReverseDelete(const AdjListWUndirGraph<VertTy, WeightTy, infinity>& g, std::ostream* out = &std::cout) {
        sizet vertNum = g.numOfVertices();
        if (vertNum == 1) {
            if (out) {
                (*out) << "No edge.\n" <<
                    "Total weight: 0" << std::endl;
            }
            return 0;
        }

        CheckGraph(g);

        // Initialize the maximum heap.
        using MST_Edge = MST_Edge<WeightTy>;
        std::priority_queue<MST_Edge> maxHeap;
        for (indext fromIndex = 0; fromIndex < vertNum - 1; fromIndex++) {
            for (const auto& e : g._adjList[fromIndex]) {
                if (fromIndex < e.toIndex) {
                    maxHeap.push(MST_Edge{ fromIndex, e.toIndex, e.weight });
                }
            }
        }
        // Copy the gragh.
        using Graph = AdjListWUndirGraph<VertTy, WeightTy, infinity>;
        Graph mst{ g };
        while (mst.numOfEdges() > vertNum - 1) {
            MST_Edge curEdge = maxHeap.top();
            maxHeap.pop();
            // Remove the edge:
            auto fromIter = std::ranges::find_if(mst._adjList[curEdge.fromIndex], Graph::FindEdge(curEdge.toIndex));
            mst._adjList[curEdge.fromIndex].erase(fromIter);
            auto toIter = std::ranges::find_if(mst._adjList[curEdge.toIndex], Graph::FindEdge(curEdge.fromIndex));
            mst._adjList[curEdge.toIndex].erase(toIter);
            mst._edgeNum--;
            // Add the edge back if it breaks the connectivity.
            if (!mst.connected()) {
                mst._adjList[curEdge.fromIndex].push_front(AdjListEdge{ curEdge.toIndex, curEdge.weight });
                mst._adjList[curEdge.toIndex].push_front(AdjListEdge{ curEdge.fromIndex, curEdge.weight });
                mst._edgeNum++;
            }
        }
        // Traverse the MST.
        std::ostringstream ss;
        WeightTy totalWeight = 0;
        indext cnt = 0;
        for (indext fromIndex = 0; fromIndex < vertNum; fromIndex++) {
            for (const auto& e : mst._adjList[fromIndex]) {
                if (fromIndex < e.toIndex) {
                    ss << "(" << ++cnt << ") "
                        << "(" << mst._vertices[fromIndex] << ", " << mst._vertices[e.toIndex] << "): "
                        << e.weight << std::endl;
                    totalWeight += e.weight;
                }
            }
        }
        ss << "\nTotal weight: " << totalWeight << std::endl;
        if (out != nullptr) {
            (*out) << ss.str();
        }
        return totalWeight;
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    bool treeFindPath(const AdjListWUndirGraph<VertTy, WeightTy, infinity>& tree,
        indext prevIndex, indext fromIndex, indext endIndex, std::stack<MST_Edge<WeightTy>>& path)
    {
        if (fromIndex == endIndex) { return true; }
        for (const auto& e : tree._adjList[fromIndex]) {
            if (e.toIndex == prevIndex) { continue; }
            path.push(MST_Edge<WeightTy>{ fromIndex, e.toIndex, e.weight });
            if (treeFindPath(tree, fromIndex, e.toIndex, endIndex, path)) {
                return true;
            }
            path.pop();
        }
        return false;
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    bool isUnique(const AdjListWUndirGraph<VertTy, WeightTy, infinity>& g) {
        sizet vertNum = g.numOfVertices();
        if (vertNum == 1) { return true; }
        CheckGraph(g);
        // Initialize another graph for MST:
        AdjListWUndirGraph<VertTy, WeightTy, infinity> mst;
        mst._vertices = g._vertices;
        mst._adjList.resize(vertNum);
        // Use Kruskal algorithm to find an MST and store the discarded edges:
        DisjointSet vertSet(vertNum);
        using MST_Edge = MST_Edge<WeightTy>;
        std::priority_queue<MST_Edge, std::vector<MST_Edge>, std::greater<MST_Edge>> minHeap;
        for (indext fromIndex = 0; fromIndex < vertNum - 1; fromIndex++) {
            for (const auto& e : g._adjList[fromIndex]) {
                if (fromIndex < e.toIndex) {
                    minHeap.push(MST_Edge{ fromIndex, e.toIndex, e.weight });
                }
            }
        }
        std::vector<MST_Edge> discardedEdges;

        for (indext cnt = 0; cnt < vertNum - 1;) {
            MST_Edge curEdge = minHeap.top();
            minHeap.pop();
            auto fromRoot = vertSet.root(curEdge.fromIndex);
            auto toRoot = vertSet.root(curEdge.toIndex);
            if (fromRoot != toRoot) {
                vertSet.unite(fromRoot, toRoot);
                cnt++;
                // Add the edge to the MST:
                mst._adjList[curEdge.fromIndex].push_front(AdjListEdge{ curEdge.toIndex, curEdge.weight });
                mst._adjList[curEdge.toIndex].push_front(AdjListEdge{ curEdge.fromIndex, curEdge.weight });
                mst._edgeNum++;
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
        std::stack<MST_Edge> path;
        for (const auto& e : discardedEdges) {
            treeFindPath(mst, std::numeric_limits<indext>::max(), e.fromIndex, e.toIndex, path);
            while (!path.empty()) {
                if (e.weight <= path.top().weight) {
                    return false;
                }
                path.pop();
            }
        }
        return true;
    }
}
