#pragma once
#include "SquareMatrix.h"
#include "ShortestPath.h"
#include "MyExceptions.h"

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <ranges>
#include <limits>
#include <vector>

namespace MyDS
{
    template<class VertTy = int, class WeightTy = int, WeightTy infinity = std::numeric_limits<WeightTy>::max()>
    class AdjMatWDirGraph
    {
        using Graph = AdjMatWDirGraph<VertTy, WeightTy, infinity>;
    public:
        AdjMatWDirGraph(int vertNum = 0)
            : m_Vertices(vertNum), m_AdjMat(vertNum), m_EdgeNum(0)
        {
        }
        AdjMatWDirGraph(const std::vector<VertTy>& vertices);
        AdjMatWDirGraph(const Graph&) = default;
        Graph& operator=(const Graph&) = default;
        virtual ~AdjMatWDirGraph() = default;

        int GetNumOfVertices() const { return (int)m_Vertices.size(); }
        int GetNumOfEdges() const { return m_EdgeNum; }

        int GetOutDegree(const VertTy& from) const;
        int GetInDegree(const VertTy& to) const;
        int GetDegree(const VertTy& vert) const { return GetOutDegree(vert) + GetInDegree(vert); }

        const VertTy* GetFirstAdjVertex(const VertTy& from) const;
        VertTy* GetFirstAdjVertex(const VertTy& from);
        const VertTy* GetNextAdjVertex(const VertTy& from, const VertTy& after)const;
        VertTy* GetNextAdjVertex(const VertTy& from, const VertTy& after);

        WeightTy GetWeight(const VertTy& from, const VertTy& to) const;
        WeightTy GetInfinity() const { return infinity; }

        void Clear();
        void SetVertex(const VertTy& oldVert, const VertTy& newVert) { m_Vertices[GetIndexOfVertex(oldVert)] = newVert; }
        void InsertVertex(const VertTy& vert);
        void EraseVertex(const VertTy& vert);
        void SetWeight(const VertTy& from, const VertTy& to, const WeightTy& newWeight);
        void InsertEdge(const VertTy& from, const VertTy& to, const WeightTy& weight);
        void EraseEdge(const VertTy& from, const VertTy& to);

        void PrintAdjacentMatrix(std::ostream& out = std::cout) const;
        void PrintEdges(std::ostream& out = std::cout) const;

        /* Shortest Path Algorithm */

        template<class VertTy, class WeightTy, WeightTy infinity>
        friend void Algorithm::Dijkstra(const AdjMatWDirGraph<VertTy, WeightTy, infinity>& g,
            const VertTy& source, const VertTy& end, std::ostream* out);

        template<class VertTy, class WeightTy, WeightTy infinity>
        friend void Algorithm::BellmanFord(const AdjMatWDirGraph<VertTy, WeightTy, infinity>& g,
            const VertTy& source, const VertTy& end, std::ostream* out);

        template<class VertTy, class WeightTy, WeightTy infinity>
        friend void Algorithm::FloydWarshall(const AdjMatWDirGraph<VertTy, WeightTy, infinity>& g,
            const VertTy& source, const VertTy& end, std::ostream* out);
    private:
        int GetIndexOfVertex(const VertTy& vert) const
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
    private:
        std::vector<VertTy> m_Vertices;  // Vertices in the graph.
        SquareMatrix<WeightTy, infinity> m_AdjMat;  // Adjacent matrix of the graph.
        int m_EdgeNum;  // Number of edges in the graph.
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Implementation of member functions
    ////////////////////////////////////////////////////////////////////////////////////////////////

    template<class VertTy, class WeightTy, WeightTy infinity>
    AdjMatWDirGraph<VertTy, WeightTy, infinity>::AdjMatWDirGraph(const std::vector<VertTy>& vertices)
    {
        // Check if there are duplicate vertices.
        for (const auto& v : vertices)
        {
            if (std::ranges::find(m_Vertices, v) == m_Vertices.end())
                m_Vertices.push_back(v);
        }
        m_AdjMat.SetDim(m_Vertices.size());
        m_EdgeNum = 0;
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    const VertTy* AdjMatWDirGraph<VertTy, WeightTy, infinity>::GetFirstAdjVertex(const VertTy& from) const
    {
        int fromIndex = GetIndexOfVertex(from);
        for (int toIndex = 0; toIndex < m_Vertices.size(); toIndex++)
        {
            if (m_AdjMat[fromIndex][toIndex] != infinity)
                return &m_Vertices[toIndex];
        }
        return nullptr;
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    VertTy* AdjMatWDirGraph<VertTy, WeightTy, infinity>::GetFirstAdjVertex(const VertTy& from)
    {
        auto const_this = const_cast<const Graph*>(this);
        return const_cast<VertTy*>(const_this->GetFirstAdjVertex(from));
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    const VertTy* AdjMatWDirGraph<VertTy, WeightTy, infinity>::GetNextAdjVertex(const VertTy& from, const VertTy& after) const {
        int fromIndex = GetIndexOfVertex(from);
        int afterIndex = GetIndexOfVertex(after);
        for (int toIndex = afterIndex + 1; toIndex < m_Vertices.size(); toIndex++)
        {
            if (m_AdjMat[fromIndex][toIndex] != infinity)
                return &m_Vertices[toIndex];
        }
        return nullptr;
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    VertTy* AdjMatWDirGraph<VertTy, WeightTy, infinity>::GetNextAdjVertex(const VertTy& from, const VertTy& after)
    {
        auto const_this = const_cast<const Graph*>(this);
        return const_cast<VertTy*>(const_this->GetNextAdjVertex(from, after));
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    int AdjMatWDirGraph<VertTy, WeightTy, infinity>::GetOutDegree(const VertTy& from) const
    {
        int fromIndex = GetIndexOfVertex(from);
        int outD = 0;
        for (const auto& w : m_AdjMat[fromIndex])
        {
            if (w != infinity)
                outD++;
        }
        return outD;
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    int AdjMatWDirGraph<VertTy, WeightTy, infinity>::GetInDegree(const VertTy& to) const
    {
        int toIndex = GetIndexOfVertex(to);
        int inD = 0;
        for (int fromIndex = 0; fromIndex < m_Vertices.size(); fromIndex++)
        {
            if (m_AdjMat[fromIndex][toIndex] != infinity)
                inD++;
        }
        return inD;
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    WeightTy AdjMatWDirGraph<VertTy, WeightTy, infinity>::GetWeight(const VertTy& from, const VertTy& to) const
    {
        int fromIndex = GetIndexOfVertex(from);
        int toIndex = GetIndexOfVertex(to);
        return m_AdjMat[fromIndex][toIndex];
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void AdjMatWDirGraph<VertTy, WeightTy, infinity>::InsertVertex(const VertTy& vert)
    {
        if (std::ranges::find(m_Vertices, vert) != m_Vertices.end())
            throw VertexAlreadyExists();

        m_Vertices.push_back(vert);
        m_AdjMat.AddOneDim();
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void AdjMatWDirGraph<VertTy, WeightTy, infinity>::EraseVertex(const VertTy& vert)
    {
        int vertIndex = GetIndexOfVertex(vert);
        for (int i = 0; i < m_Vertices.size(); i++)
        {
            if (m_AdjMat[vertIndex][i] != infinity)
                m_EdgeNum--;

            if (m_AdjMat[i][vertIndex] != infinity)
                m_EdgeNum--;
        }
        int lastIndex = (int)m_Vertices.size() - 1;
        if (vertIndex != lastIndex)
        {
            // Replace the vertex to be deleted with the last vertex
            m_Vertices[vertIndex] = std::move(m_Vertices[lastIndex]);
            m_AdjMat[vertIndex] = std::move(m_AdjMat[lastIndex]);
            for (int i = 0; i < lastIndex; i++)
                m_AdjMat[i][vertIndex] = std::move(m_AdjMat[i][lastIndex]);
            m_AdjMat[vertIndex][vertIndex] = infinity;
        }
        m_AdjMat.RemoveOneDim();
        m_Vertices.pop_back();
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void AdjMatWDirGraph<VertTy, WeightTy, infinity>::SetWeight(const VertTy& from, const VertTy& to, const WeightTy& newWeight)
    {
        if (newWeight == infinity)
            throw InfiniteWeight("Weight cannot be infinity!");

        int fromIndex = GetIndexOfVertex(from);
        int toIndex = GetIndexOfVertex(to);
        if (m_AdjMat[fromIndex][toIndex] == infinity)
            throw EdgeNotFound();

        m_AdjMat[fromIndex][toIndex] = newWeight;
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void AdjMatWDirGraph<VertTy, WeightTy, infinity>::InsertEdge(const VertTy& from, const VertTy& to, const WeightTy& weight)
    {
        if (weight == infinity)
            throw InfiniteWeight("Weight cannot be infinity!");

        int fromIndex = GetIndexOfVertex(from);
        int toIndex = GetIndexOfVertex(to);

        if (fromIndex == toIndex)
            throw IllegalParameterValue("Loop is not allowed!");

        if (m_AdjMat[fromIndex][toIndex] != infinity)
            throw EdgeAlreadyExists();

        m_AdjMat[fromIndex][toIndex] = weight;
        m_EdgeNum++;
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void AdjMatWDirGraph<VertTy, WeightTy, infinity>::EraseEdge(const VertTy& from, const VertTy& to)
    {
        int fromIndex = GetIndexOfVertex(from);
        int toIndex = GetIndexOfVertex(to);

        if (m_AdjMat[fromIndex][toIndex] == infinity)
            throw EdgeNotFound();

        m_AdjMat[fromIndex][toIndex] = infinity;
        m_EdgeNum--;
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void AdjMatWDirGraph<VertTy, WeightTy, infinity>::Clear()
    {
        m_Vertices.clear();
        m_AdjMat.SetDim(0);
        m_EdgeNum = 0;
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void AdjMatWDirGraph<VertTy, WeightTy, infinity>::PrintAdjacentMatrix(std::ostream& out) const
    {
        if (m_Vertices.empty())
            return;

        int width = 5;
        out << std::setw(width + 1) << "";
        for (const auto& v : m_Vertices)
            out << std::setw(width) << v << " ";
        out << "\n";

        out << std::setw(width + 1) << "";
        for (const auto& v : m_Vertices)
            out << "______";
        out << std::endl;

        for (int i = 0; i < m_AdjMat.GetDim(); i++)
        {
            out << std::setw(width - 1) << m_Vertices[i] << " |";
            for (const auto& w : m_AdjMat[i])
            {
                if (w == infinity)
                    out << std::setw(width) << "inf" << " ";
                else
                    out << std::setw(width) << w << " ";
            }
            out << std::endl;
        }
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void AdjMatWDirGraph<VertTy, WeightTy, infinity>::PrintEdges(std::ostream& out) const
    {
        int edgeCnt = 0;
        for (int fromIndex = 0; fromIndex < m_AdjMat.GetDim(); fromIndex++)
        {
            for (int toIndex = 0; toIndex < m_AdjMat.GetDim(); toIndex++)
            {
                if (m_AdjMat[fromIndex][toIndex] != infinity)
                {
                    edgeCnt++;
                    out << "(" << edgeCnt << ") "
                        << "<" << m_Vertices[fromIndex] << ", " << m_Vertices[toIndex] << ">: "
                        << m_AdjMat[fromIndex][toIndex] << "\n";
                }
            }
        }
    }
}

