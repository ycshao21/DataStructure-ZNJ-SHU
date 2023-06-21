#pragma once
#include"../data_structure/AdjListWUndirGraph.h"

namespace S2
{
    template<class VertTy, class WeightTy, WeightTy infinity>
    void InsertVertex(AdjListWUndirGraph<VertTy, WeightTy, infinity>& g, const VertTy& vert)
    {
        try {
            g.insertVertex(vert);
            std::cout << "插入成功！" << std::endl;
        } catch (VertexAlreadyExists) {
            std::cout << "该顶点已存在，无法插入" << std::endl;
        }
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void EraseVertex(AdjListWUndirGraph<VertTy, WeightTy, infinity>& g, const VertTy& vert) {
        try {
            g.eraseVertex(vert);
            std::cout << "删除成功！" << std::endl;
        } catch (VertexNotFound) {
            std::cout << "该顶点不存在" << std::endl;
        }
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void InsertEdge(AdjListWUndirGraph<VertTy, WeightTy, infinity>& g, const VertTy& from, const VertTy& to, const WeightTy& weight) {
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
    void EraseEdge(AdjListWUndirGraph<VertTy, WeightTy, infinity>& g, const VertTy& from, const VertTy& to) {
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
    void Degree(const AdjListWUndirGraph<VertTy, WeightTy, infinity>& g, const VertTy& vert) {
        std::ostringstream ss;
        try {
            ss << "\n度数：" << g.degree(vert) << "\n";
            std::cout << ss.str();
        } catch (VertexNotFound) {
            std::cout << "该顶点不存在" << std::endl;
        }
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void ConnectedComponent(const AdjListWUndirGraph<VertTy, WeightTy, infinity>& g) {
        if (g.connected()) {
            std::cout << "该图是连通图\n";
        } else {
            std::cout << "该图不是连通图\n";
        }
        std::cout << "连通分量数：" << g.numOfConnectedComponent() << std::endl;
    }

    template<class VertTy, class WeightTy, WeightTy infinity>
    void MinimumSpanningTree(const AdjListWUndirGraph<VertTy, WeightTy, infinity>& g) {
        if (g.hasUniqueMST()) {
            std::cout << "该图有唯一最小生成树" << std::endl;
        } else {
            std::cout << "该图有多个最小生成树" << std::endl;
        }
        std::cout << "-----------\n";
        std::cout << "| Kruskal |\n";
        std::cout << "-----------" << std::endl;

        std::cout << "--------\n";
        std::cout << "| Prim |\n";
        std::cout << "--------" << std::endl;

        std::cout << "------------------\n";
        std::cout << "| Reverse-Delete |\n";
        std::cout << "------------------" << std::endl;
    }
}
