#pragma once
#include "AdjListWUndirGraph.h"
#include <format>

namespace Spring02
{
    template<class VertTy, class WeightTy, WeightTy infinity>
    void InsertVertex(MyDS::AdjListWUndirGraph<VertTy, WeightTy, infinity>& g, const VertTy& vert)
    {
        try
        {
            g.InsertVertex(vert);
            std::cout << "插入成功！" << std::endl;
        }
        catch (VertexAlreadyExists)
        {
            std::cout << "该顶点已存在，无法插入" << std::endl;
        }
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void EraseVertex(MyDS::AdjListWUndirGraph<VertTy, WeightTy, infinity>& g, const VertTy& vert)
    {
        try
        {
            g.EraseVertex(vert);
            std::cout << "删除成功！" << std::endl;
        }
        catch (VertexNotFound)
        {
            std::cout << "该顶点不存在" << std::endl;
        }
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void InsertEdge(MyDS::AdjListWUndirGraph<VertTy, WeightTy, infinity>& g, const VertTy& from, const VertTy& to, const WeightTy& weight)
    {
        try
        {
            g.InsertEdge(from, to, weight);
            std::cout << "插入成功！" << std::endl;
        }
        catch (IllegalParameterValue)
        {
            std::cout << "起点与终点相同，无法插入" << std::endl;
        }
        catch (VertexNotFound)
        {
            std::cout << "顶点不存在，无法插入" << std::endl;
        }
        catch (EdgeAlreadyExists)
        {
            std::cout << "该边已存在，无法插入" << std::endl;
        }
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void EraseEdge(MyDS::AdjListWUndirGraph<VertTy, WeightTy, infinity>& g, const VertTy& from, const VertTy& to)
    {
        try
        {
            g.EraseEdge(from, to);
            std::cout << "删除成功！" << std::endl;
        }
        catch (VertexNotFound)
        {
            std::cout << "顶点不存在，无法删除" << std::endl;
        }
        catch (EdgeNotFound)
        {
            std::cout << "该边不存在" << std::endl;
        }
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void Degree(const MyDS::AdjListWUndirGraph<VertTy, WeightTy, infinity>& g, const VertTy& vert)
    {
        try
        {
            std::string result = std::format("度数：{}", g.GetDegree(vert));
            std::cout << result << std::endl;
        }
        catch (VertexNotFound)
        {
            std::cout << "该顶点不存在" << std::endl;
        }
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void ConnectedComponent(const MyDS::AdjListWUndirGraph<VertTy, WeightTy, infinity>& g)
    {
        try
        {
            if (g.IsConnected())
                std::cout << "该图是连通图\n";
            else
                std::cout << "该图不是连通图\n";
            std::cout << "连通分量数：" << g.GetNumOfConnectedComponent() << std::endl;
        }
        catch (NoVertex)
        {
            std::cout << "无顶点" << std::endl;
        }
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void MinimumSpanningTree(const MyDS::AdjListWUndirGraph<VertTy, WeightTy, infinity>& g)
    {
        try
        {
            if (g.HasUniqueMST())
                std::cout << "该图有唯一最小生成树" << std::endl;
            else
                std::cout << "该图有多个最小生成树" << std::endl;
        }
        catch (NoVertex)
        {
            std::cout << "无顶点" << std::endl;
            return;
        }
        catch (GraphDisconnected)
        {
            std::cout << "非连通图，无法计算最小生成树" << std::endl;
            return;
        }

        std::cout << "-----------\n";
        std::cout << "| Kruskal |\n";
        std::cout << "-----------" << std::endl;
        Algorithm::Kruskal(g);
        std::cout << std::endl;

        std::cout << "--------\n";
        std::cout << "| Prim |\n";
        std::cout << "--------" << std::endl;
        Algorithm::Prim(g);
        std::cout << std::endl;

        std::cout << "------------------\n";
        std::cout << "| Reverse-Delete |\n";
        std::cout << "------------------" << std::endl;
        Algorithm::ReverseDelete(g);
    }
}
