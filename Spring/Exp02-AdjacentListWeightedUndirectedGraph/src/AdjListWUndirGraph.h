#pragma once
#include <vector>
#include <list>
#include <queue>
#include <algorithm>
#include <ranges>
#include <iomanip>
#include <limits>
#include "AdjListEdge.h"
#include "MinimumSpanningTree.h"
#include "MyExceptions.h"

namespace MyDS
{
    template<class VertTy = int, class WeightTy = int, WeightTy infinity = std::numeric_limits<WeightTy>::max()>
    class AdjListWUndirGraph
    {
        using Graph = AdjListWUndirGraph<VertTy, WeightTy, infinity>;
        using Edge = AdjListEdge<WeightTy>;
        using EdgeList = std::list<Edge>;
    public:
        AdjListWUndirGraph(int vertNum = 0)
            : m_Vertices(vertNum), m_AdjList(vertNum), m_EdgeNum(0)
        {
        }
        AdjListWUndirGraph(const std::vector<VertTy>& vertices);
        AdjListWUndirGraph(const Graph&) = default;
        AdjListWUndirGraph(Graph&&) = default;
        Graph& operator=(const Graph&) = default;
        ~AdjListWUndirGraph() = default;

        int GetNumOfVertices() const { return m_Vertices.size(); }
        int GetNumOfEdges() const { return m_EdgeNum; }
        bool IsConnected() const;
        int GetNumOfConnectedComponent() const;
        bool HasUniqueMST() const { return Algorithm::IsUnique(*this); }

        int GetDegree(const VertTy& vert) const;

        const VertTy* GetFirstAdjVertex(const VertTy& from) const;
        VertTy* GetFirstAdjVertex(const VertTy& from);
        const VertTy* GetNextAdjVertex(const VertTy& from, const VertTy& after)const;
        VertTy* GetNextAdjVertex(const VertTy& from, const VertTy& after);

        WeightTy GetWeight(const VertTy& from, const VertTy& to) const;
        WeightTy GetInfinity() const { return infinity; }
    public:
        void Clear();
        void SetVertex(const VertTy& oldVert, const VertTy& newVert) { m_Vertices[GetIndexOfVertex(oldVert)] = newVert; }
        void InsertVertex(const VertTy& vert);
        void EraseVertex(const VertTy& vert);
        void SetWeight(const VertTy& from, const VertTy& to, const WeightTy& newWeight);
        void InsertEdge(const VertTy& from, const VertTy& to, const WeightTy& weight);
        void EraseEdge(const VertTy& from, const VertTy& to);
    public:
        template<class VertTy, class WeightTy, WeightTy infinity>
        friend WeightTy Algorithm::Kruskal(const AdjListWUndirGraph<VertTy, WeightTy, infinity>& g, std::ostream* out);
        template<class VertTy, class WeightTy, WeightTy infinity>
        friend WeightTy Algorithm::Prim(const AdjListWUndirGraph<VertTy, WeightTy, infinity>& g, std::ostream* out);
        template<class VertTy, class WeightTy, WeightTy infinity>
        friend WeightTy Algorithm::ReverseDelete(const AdjListWUndirGraph<VertTy, WeightTy, infinity>& g, std::ostream* out);
    public:
        // @brief Depth-first search from one vertex.
        void DFS(const VertTy& from, void (*visit)(const VertTy&) = OutputVertex) const;
        // @brief Depth-first search for the whole graph.
        void DFS(void (*visit)(const VertTy&) = OutputVertex) const;
        // @brief Breadth-first search from one vertex.
        void BFS(const VertTy& from, void (*visit)(const VertTy&) = OutputVertex) const;
        // @brief Breadth-first search for the whole graph.
        void BFS(void (*visit)(const VertTy&) = OutputVertex) const;
    public:
        void PrintAdjacentList(std::ostream& out = std::cout) const;
        void PrintEdges(std::ostream& out = std::cout) const;
    private:
        int GetIndexOfVertex(const VertTy& vert) const;

        void _DFS(int sourceIndex, std::vector<uint8_t>& visited, void (*visit)(const VertTy&) = OutputVertex) const;
        void _BFS(int sourceIndex, std::vector<uint8_t>& visited, void (*visit)(const VertTy&) = OutputVertex) const;

        static void OutputVertex(const VertTy& vert) { std::cout << vert << " "; }

        template<class VertTy, class WeightTy, WeightTy infinity>
        friend bool Algorithm::TreeFindPath(const AdjListWUndirGraph<VertTy, WeightTy, infinity>& tree,
            int prevIndex, int fromIndex, int endIndex, std::stack<MST_Edge<WeightTy>>& path);

        template<class VertTy, class WeightTy, WeightTy infinity>
        friend bool Algorithm::IsUnique(const AdjListWUndirGraph<VertTy, WeightTy, infinity>& g);
    private:
        class FindEdgeFn  // For finding edge according to the toIndex.
        {
        public:
            FindEdgeFn(int toIndex)
                : m_ToIndex(toIndex)
            {
            }
            bool operator()(const Edge& edge) const { return edge.toIndex == m_ToIndex; }
        private:
            int m_ToIndex;
        };
    private:
        std::vector<VertTy> m_Vertices;
        std::vector<EdgeList> m_AdjList;
        int m_EdgeNum;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Implementation of member functions
    ////////////////////////////////////////////////////////////////////////////////////////////////

    template<class VertTy, class WeightTy, WeightTy infinity>
    AdjListWUndirGraph<VertTy, WeightTy, infinity>::AdjListWUndirGraph(const std::vector<VertTy>& vertices)
    {
        // Check if there are duplicate vertices.
        for (const auto& vert : vertices)
        {
            if (std::ranges::find(m_Vertices, vert) == m_Vertices.end())
                m_Vertices.push_back(vert);
        }
        m_AdjList.resize(m_Vertices.size());
        m_EdgeNum = 0;
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    bool AdjListWUndirGraph<VertTy, WeightTy, infinity>::IsConnected() const
    {
        if (m_Vertices.empty())
            throw NoVertex();

        if (m_Vertices.size() == 1)
            return true;

        if (m_EdgeNum < m_Vertices.size() - 1)
            return false;

        // If the graph can be wholly traversed from one vertex, it is connected.
        std::vector<uint8_t> visited(m_Vertices.size(), 0);
        _BFS(0, visited, nullptr);
        return std::ranges::find(visited, 0) == visited.end();
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    int AdjListWUndirGraph<VertTy, WeightTy, infinity>::GetNumOfConnectedComponent() const
    {
        if (m_Vertices.empty())
            throw NoVertex();

        // The number of connected components is equal to the number of times of traversal.
        int cnt = 0;
        std::vector<uint8_t> visited(m_Vertices.size(), 0);
        for (int vertIndex = 0; vertIndex < m_Vertices.size(); vertIndex++)
        {
            if (visited[vertIndex] == 0)
            {
                cnt++;
                _BFS(vertIndex, visited, nullptr);
            }
        }
        return cnt;
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    int AdjListWUndirGraph<VertTy, WeightTy, infinity>::GetDegree(const VertTy& vert) const
    {
        int vertIndex = GetIndexOfVertex(vert);
        return (int)m_AdjList[vertIndex].size();
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    const VertTy* AdjListWUndirGraph<VertTy, WeightTy, infinity>::GetFirstAdjVertex(const VertTy& from) const {
        int fromIndex = GetIndexOfVertex(from);
        if (m_AdjList[fromIndex].empty())
            return nullptr;

        int toIndex = m_AdjList[fromIndex].front().to;
        return &m_Vertices[toIndex];
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    VertTy* AdjListWUndirGraph<VertTy, WeightTy, infinity>::GetFirstAdjVertex(const VertTy& from)
    {
        auto const_this = const_cast<const Graph*>(this);
        return const_cast<VertTy*>(const_this->firstAdjVertex(from));
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    const VertTy* AdjListWUndirGraph<VertTy, WeightTy, infinity>::GetNextAdjVertex(const VertTy& from, const VertTy& after) const {
        int fromIndex = GetIndexOfVertex(from);
        int afterIndex = GetIndexOfVertex(after);

        // Check if "to" is adjacent to "from".
        auto edgeIter = std::ranges::find_if(m_AdjList[fromIndex], FindEdge(afterIndex));
        if (edgeIter == m_AdjList[fromIndex].end())
            return nullptr;

        // Move to the next adjacent vertex.
        edgeIter++;
        if (edgeIter == m_AdjList[fromIndex].end())
            return nullptr;

        int nextIndex = edgeIter->toIndex;
        return &m_Vertices[nextIndex];
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    VertTy* AdjListWUndirGraph<VertTy, WeightTy, infinity>::GetNextAdjVertex(const VertTy& from, const VertTy& after)
    {
        auto const_this = const_cast<const Graph*>(this);
        return const_cast<VertTy*>(const_this->nextAdjVertex(from, after));
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    WeightTy AdjListWUndirGraph<VertTy, WeightTy, infinity>::GetWeight(const VertTy& from, const VertTy& to) const
    {
        int fromIndex = GetIndexOfVertex(from),
            toIndex = GetIndexOfVertex(to);
        auto edgeIter = std::ranges::find_if(m_AdjList[fromIndex], FindEdge(toIndex));
        if (edgeIter != m_AdjList[fromIndex].end())
            return edgeIter->weight;
        return infinity;
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    int AdjListWUndirGraph<VertTy, WeightTy, infinity>::GetIndexOfVertex(const VertTy& vert) const
    {
        int i = 0;
        for (; i < m_Vertices.size(); i++)
        {
            if (m_Vertices[i] == vert)
                break;
        }

        if (i == m_Vertices.size())
            throw VertexNotFound();

        return i;
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void AdjListWUndirGraph<VertTy, WeightTy, infinity>::InsertVertex(const VertTy& vert)
    {
        if (std::ranges::find(m_Vertices, vert) != m_Vertices.end())
            throw VertexAlreadyExists();

        m_Vertices.push_back(vert);
        m_AdjList.push_back(std::list<Edge>{});
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void AdjListWUndirGraph<VertTy, WeightTy, infinity>::EraseVertex(const VertTy& vert)
    {
        int vertIndex = GetIndexOfVertex(vert);
        m_EdgeNum -= (int)m_AdjList[vertIndex].size();
        for (int fromIndex = 0; fromIndex < m_AdjList.size(); fromIndex++)
        {
            if (fromIndex == vertIndex)
                continue;
            auto edgeIter = std::ranges::find_if(m_AdjList[fromIndex], FindEdgeFn(vertIndex));
            if (edgeIter != m_AdjList[fromIndex].end())
                m_AdjList[fromIndex].erase(edgeIter);
        }
        int lastIndex = (int)m_Vertices.size() - 1;
        if (vertIndex != lastIndex)
        {
            // Replace the vertex to be deleted with the last vertex
            m_Vertices[vertIndex] = std::move(m_Vertices[lastIndex]);
            m_AdjList[vertIndex] = std::move(m_AdjList[lastIndex]);
            for (int fromIndex = 0; fromIndex < lastIndex; fromIndex++)
            {
                if (fromIndex == vertIndex)
                    continue;
                auto edgeIter = std::ranges::find_if(m_AdjList[fromIndex], FindEdgeFn(lastIndex));
                if (edgeIter != m_AdjList[fromIndex].end())
                    edgeIter->toIndex = vertIndex;
            }
        }
        m_Vertices.pop_back();
        m_AdjList.pop_back();
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void AdjListWUndirGraph<VertTy, WeightTy, infinity>::SetWeight(const VertTy& from, const VertTy& to, const WeightTy& newWeight)
    {
        if (newWeight == infinity)
            throw IllegalParameterValue("Weight cannot be infinity.");

        int fromIndex = GetIndexOfVertex(from);
        int toIndex = GetIndexOfVertex(to);
        if (fromIndex == toIndex)
            throw EdgeNotFound();

        // Modify the weight of the edge from "from" to "to".
        auto fromIter = std::ranges::find_if(m_AdjList[fromIndex], FindEdge(toIndex));
        if (fromIter == m_AdjList[fromIndex].end())
            throw EdgeNotFound();
        fromIter->weight = newWeight;

        // Modify the weight of the edge from "to" to "from".
        auto toIter = std::ranges::find_if(m_AdjList[toIndex], FindEdge(fromIndex));
        toIter->weight = newWeight;
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void AdjListWUndirGraph<VertTy, WeightTy, infinity>::InsertEdge(const VertTy& from, const VertTy& to, const WeightTy& weight)
    {
        if (weight == infinity)
            throw InfiniteWeight();

        int fromIndex = GetIndexOfVertex(from);
        int toIndex = GetIndexOfVertex(to);

        if (fromIndex == toIndex)
            throw IllegalParameterValue("Loop is not allowed.");

        // Check if the edge already exists.
        if (std::ranges::find_if(m_AdjList[fromIndex], FindEdgeFn(toIndex)) != m_AdjList[fromIndex].end())
            throw EdgeAlreadyExists();

        // Insert the edge at the front of the list.
        m_AdjList[fromIndex].push_front(Edge{ toIndex, weight });
        m_AdjList[toIndex].push_front(Edge{ fromIndex, weight });
        m_EdgeNum++;
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void AdjListWUndirGraph<VertTy, WeightTy, infinity>::EraseEdge(const VertTy& from, const VertTy& to)
    {
        int fromIndex = GetIndexOfVertex(from),
            toIndex = GetIndexOfVertex(to);

        if (fromIndex == toIndex)
            throw EdgeNotFound();

        // Erase (from, to).
        auto fromIter = std::ranges::find_if(m_AdjList[fromIndex], FindEdgeFn(toIndex));
        if (fromIter == m_AdjList[fromIndex].end())
            throw EdgeNotFound();

        m_AdjList[fromIndex].erase(fromIter);
        // Erase (to, from).
        auto toIter = std::ranges::find_if(m_AdjList[toIndex], FindEdgeFn(fromIndex));
        m_AdjList[toIndex].erase(toIter);
        m_EdgeNum--;
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void AdjListWUndirGraph<VertTy, WeightTy, infinity>::_DFS(int sourceIndex,
        std::vector<uint8_t>& visited, void (*visit)(const VertTy&)) const
    {
        // Visit the current vertex:
        visited[sourceIndex] = 1;
        if (visit)
            (*visit)(m_Vertices[sourceIndex]);

        // Visit its unvisited adjacent vertices:
        for (const auto& edge : m_AdjList[sourceIndex])
        {
            if (visited[edge.toIndex] == 0)
                _DFS(edge.toIndex, visited, visit);
        }
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void AdjListWUndirGraph<VertTy, WeightTy, infinity>::_BFS(int sourceIndex,
        std::vector<uint8_t>& visited, void (*visit)(const VertTy&)) const
    {
        std::queue<int> vertQueue;
        // Visit the current vertex:
        visited[sourceIndex] = 1;
        if (visit)
            (*visit)(m_Vertices[sourceIndex]);

        vertQueue.push(sourceIndex);
        while (!vertQueue.empty())
        {
            int curIndex = vertQueue.front();
            vertQueue.pop();
            // Visit its adjacent vertices:
            for (const auto& edge : m_AdjList[curIndex])
            {
                int adjIndex = edge.toIndex;
                if (visited[adjIndex] == 0)
                {
                    visited[adjIndex] = 1;
                    if (visit != nullptr)
                        (*visit)(m_Vertices[adjIndex]);

                    vertQueue.push(adjIndex);
                }
            }
        }
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void AdjListWUndirGraph<VertTy, WeightTy, infinity>::DFS(const VertTy& source, void (*visit)(const VertTy&)) const {
        int fromIndex = GetIndexOfVertex(source);
        std::vector<uint8_t> visited(m_Vertices.size(), 0);
        _DFS(fromIndex, visited, visit);
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void AdjListWUndirGraph<VertTy, WeightTy, infinity>::DFS(void (*visit)(const VertTy&)) const
    {
        std::vector<uint8_t> visited(m_Vertices.size(), 0);
        for (int fromIndex = 0; fromIndex < m_Vertices.size(); fromIndex++)
        {
            if (visited[fromIndex] == 0)
                _DFS(fromIndex, visited, visit);
        }
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void AdjListWUndirGraph<VertTy, WeightTy, infinity>::BFS(const VertTy& source, void (*visit)(const VertTy&)) const {
        int fromIndex = GetIndexOfVertex(source);
        std::vector<uint8_t> visited(m_Vertices.size(), 0);
        _BFS(fromIndex, visited, visit);
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void AdjListWUndirGraph<VertTy, WeightTy, infinity>::BFS(void (*visit)(const VertTy&)) const {
        std::vector<uint8_t> visited(m_Vertices.size(), 0);
        for (int fromIndex = 0; fromIndex < m_Vertices.size(); fromIndex++)
        {
            if (visited[fromIndex] == 0)
                _BFS(fromIndex, visited, visit);
        }
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void AdjListWUndirGraph<VertTy, WeightTy, infinity>::Clear()
    {
        m_Vertices.clear();
        m_AdjList.clear();
        m_EdgeNum = 0;
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void AdjListWUndirGraph<VertTy, WeightTy, infinity>::PrintAdjacentList(std::ostream& out) const
    {
        for (int fromIndex = 0; fromIndex < m_Vertices.size(); fromIndex++)
        {
            out << std::setw(4) << m_Vertices[fromIndex] << " | ";
            for (const auto& e : m_AdjList[fromIndex])
                out << m_Vertices[e.toIndex] << "(" << e.weight << ") -> ";
            out << "end" << std::endl;
        }
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void AdjListWUndirGraph<VertTy, WeightTy, infinity>::PrintEdges(std::ostream& out) const
    {
        int edgeCnt = 0;
        for (int fromIndex = 0; fromIndex < m_AdjList.size(); fromIndex++)
        {
            for (const auto& e : m_AdjList[fromIndex])
            {
                int toIndex = e.toIndex;
                if (fromIndex < toIndex)
                {
                    edgeCnt++;
                    out << "(" << edgeCnt << ") "
                        << "(" << m_Vertices[fromIndex] << ", " << m_Vertices[toIndex] << "): "
                        << e.weight << "\n";
                }
            }
        }
    }
}
