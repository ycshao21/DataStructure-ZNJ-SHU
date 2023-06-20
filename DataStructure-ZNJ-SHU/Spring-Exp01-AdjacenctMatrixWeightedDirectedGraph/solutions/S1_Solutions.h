#pragma once
#include<iostream>
#include<sstream>
#include"../data_structure/AdjMatWDirGraph.h"

namespace S1
{
    template<class VertTy, class WeightTy, WeightTy infinity>
    void InsertVertex(AdjMatWDirGraph<VertTy, WeightTy, infinity>& g, const VertTy& vert) {
        try {
            g.insertVertex(vert);
            std::cout << "插入成功！" << std::endl;
        } catch (VertexAlreadyExists) {
            std::cout << "该顶点已存在，无法插入" << std::endl;
        }
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void EraseVertex(AdjMatWDirGraph<VertTy, WeightTy, infinity>& g, const VertTy& vert) {
        try {
            g.eraseVertex(vert);
            std::cout << "删除成功！" << std::endl;
        } catch (VertexNotFound) {
            std::cout << "该顶点不存在" << std::endl;
        }
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void InsertEdge(AdjMatWDirGraph<VertTy, WeightTy, infinity>& g, const VertTy& from, const VertTy& to, const WeightTy& weight) {
        try {
            g.insertEdge(from, to, weight);
            std::cout << "插入成功！" << std::endl;
        } catch (IllegalParameterValue) {
            std::cout << "起点与终点相同，无法插入" << std::endl;
        } catch (VertexNotFound) {
            std::cout << "顶点不存在，无法插入" << std::endl;
        } catch (EdgeAlreadyExists) {
            std::cout << "该边已存在，无法插入" << std::endl;
        }
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void EraseEdge(AdjMatWDirGraph<VertTy, WeightTy, infinity>& g, const VertTy& from, const VertTy& to) {
        try {
            g.eraseEdge(from, to);
            std::cout << "删除成功！" << std::endl;
        } catch (VertexNotFound) {
            std::cout << "顶点不存在，无法删除" << std::endl;
        } catch (EdgeNotFound) {
            std::cout << "该边不存在" << std::endl;
        }
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void Degree(const AdjMatWDirGraph<VertTy, WeightTy, infinity>& g, const VertTy& vert) {
        std::ostringstream ss;
        try {
            ss << "\n总度数：" << g.degree(vert) << "\n"
                << "入度：" << g.inDegree(vert) << " 出度：" << g.outDegree(vert) << std::endl;
            std::cout << ss.str();
        } catch (VertexNotFound) {
            std::cout << "该顶点不存在" << std::endl;
        }
    }
    template<class VertTy, class WeightTy, WeightTy infinity>
    void ShortestPath(const AdjMatWDirGraph<VertTy, WeightTy, infinity>& g, const VertTy& vert) {
        std::cout << "------------\n";
        std::cout << "| Dijkstra |\n";
        std::cout << "------------" << std::endl;
        try {
            ShortestPath::Dijkstra(g, vert);
        } catch (VertexNotFound) {
            std::cout << "该顶点不存在" << std::endl;
        } catch (NegativeEdge) {
            std::cout << "含负权边，无法使用Dijkstra算法" << std::endl;
        }
        std::cout << std::endl;

        std::cout << "----------------\n";
        std::cout << "| Bellman-Ford |\n";
        std::cout << "----------------" << std::endl;
        try {
            ShortestPath::BellmanFord(g, vert);
        } catch (VertexNotFound) {
            std::cout << "该顶点不存在" << std::endl;
        } catch (NegativeCycle) {
            std::cout << "含负权回路" << std::endl;
        }
        std::cout << std::endl;

        std::cout << "------------------\n";
        std::cout << "| Floyd-Warshall |\n";
        std::cout << "------------------" << std::endl;
        try {
            ShortestPath::FloydWarshall(g);
        } catch (NegativeCycle) {
            std::cout << "含负权回路" << std::endl;
        }
    }
}
