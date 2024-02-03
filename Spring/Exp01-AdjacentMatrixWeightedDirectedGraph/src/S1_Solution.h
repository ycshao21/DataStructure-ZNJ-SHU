#pragma once
#include <iostream>
#include <format>
#include "AdjMatWDirGraph.h"

namespace Spring01
{
    template<class VertTy, class WeightTy, WeightTy infinity>
    void InsertVertex(MyDS::AdjMatWDirGraph<VertTy, WeightTy, infinity>& g, const VertTy& vert)
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
    void EraseVertex(MyDS::AdjMatWDirGraph<VertTy, WeightTy, infinity>& g, const VertTy& vert)
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
    void InsertEdge(MyDS::AdjMatWDirGraph<VertTy, WeightTy, infinity>& g, const VertTy& from, const VertTy& to, const WeightTy& weight)
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
    void EraseEdge(MyDS::AdjMatWDirGraph<VertTy, WeightTy, infinity>& g, const VertTy& from, const VertTy& to)
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
    void Degree(const MyDS::AdjMatWDirGraph<VertTy, WeightTy, infinity>& g, const VertTy& vert)
    {
        try
        {
            std::string result = std::format("总度数：{0}\n入度：{1} 出度：{2}",
                    g.GetDegree(vert), g.GetInDegree(vert), g.GetOutDegree(vert));
            std::cout << result << std::endl;
        }
        catch (VertexNotFound)
        {
            std::cout << "该顶点不存在" << std::endl;
        }
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void ShortestPath(const MyDS::AdjMatWDirGraph<VertTy, WeightTy, infinity>& g, const VertTy& source, const VertTy& end) {
        std::cout << "------------\n";
        std::cout << "| Dijkstra |\n";
        std::cout << "------------" << std::endl;
        try
        {
            Algorithm::Dijkstra(g, source, end);
        }
        catch (VertexNotFound)
        {
            std::cout << "顶点不存在\n";
        }
        catch (NegativeEdge)
        {
            std::cout << "含负权边，无法使用Dijkstra算法\n";
        }
        std::cout << std::endl;

        std::cout << "----------------\n";
        std::cout << "| Bellman-Ford |\n";
        std::cout << "----------------" << std::endl;
        try
        {
            Algorithm::BellmanFord(g, source, end);
        }
        catch (VertexNotFound)
        {
            std::cout << "顶点不存在\n";
        }
        catch (NegativeCycle)
        {
            std::cout << "含负权回路，无法计算最短路径\n";
        }
        std::cout << std::endl;

        std::cout << "------------------\n";
        std::cout << "| Floyd-Warshall |\n";
        std::cout << "------------------" << std::endl;
        try
        {
            Algorithm::FloydWarshall(g, source, end);
        }
        catch (VertexNotFound)
        {
            std::cout << "顶点不存在" << std::endl;
        }
        catch (NegativeCycle)
        {
            std::cout << "含负权回路，无法计算最短路径" << std::endl;
        }
    }
}
