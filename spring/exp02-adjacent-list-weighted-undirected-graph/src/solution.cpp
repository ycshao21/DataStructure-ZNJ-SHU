#include <format>

#include "graph_exceptions.hpp"
#include "solution.hpp"

void opt01_insertVertex(Graph& g, const VT& v)
{
    try {
        g.insertVertex(v);
    } catch (DuplicateVertexException) {
        std::cout << std::format(
            "[WARNING] Vertex \"{}\" is already in the graph. Skip.\n", v);
    }
}

void opt02_eraseVertex(Graph& g, const VT& v)
{
    try {
        g.eraseVertex(v);
    } catch (VertexNotFoundException) {
        std::cout << std::format("[WARNING] Vertex \"{}\" is not in the graph. Skip.\n",
                                 v);
    }
}

void opt03_insertEdge(Graph& g, const VT& v1, const VT& v2, const WT& weight)
{
    try {
        g.insertEdge(v1, v2, weight);
    } catch (VertexNotFoundException) {
        std::cout << std::format("[ERROR] Vertex \"{}\" or \"{}\" is not in the graph!\n",
                                 v1, v2);
    } catch (SelfLoopNotAllowedException) {
        std::cout << "[ERROR] Self loop is not allowed!\n";
    } catch (InvalidWeightException) {
        std::cout << "[ERROR] Invalid weight!\n";
    } catch (DuplicateEdgeException) {
        std::cout << std::format(
            "[WARNING] Edge (\"{}\", \"{}\") is already in the graph. Skip.\n", v1, v2);
    }
}

void opt04_eraseEdge(Graph& g, const VT& v1, const VT& v2)
{
    try {
        g.eraseEdge(v1, v2);
    } catch (VertexNotFoundException) {
        std::cout << std::format("[ERROR] Vertex \"{}\" or \"{}\" is not in the graph!\n",
                                 v1, v2);
    } catch (EdgeNotFoundException) {
        std::cout << std::format(
            "[WARNING] Edge (\"{}\", \"{}\") is not in the graph. Skip.\n", v1, v2);
    }
}

void opt05_degree(const Graph& g, const VT& v)
{
    try {
        std::cout << std::format("Degree: {}\n", g.countDegree(v));
    } catch (VertexNotFoundException) {
        std::cout << std::format("[ERROR] Vertex \"{}\" is not in the graph!\n", v);
    }
}

void opt06_connectedComponent(const Graph& g)
{
    try {
        if (g.isConnected()) {
            std::cout << "The graph is connected.\n";
        } else {
            std::cout << "The graph is not connected.\n";
        }
        std::cout << std::format("Number of connected components: {}\n",
                                 g.getNumOfConnectedComponent());
    } catch (NoVertexException) {
        std::cout << "[ERROR] No vertex in the graph!\n";
    }
}

void opt07_minimumSpanningTree(const Graph& g)
{
    try {
        if (g.hasUniqueMST()) {
            std::cout << "The graph has a unique minimum spanning tree.\n";
        } else {
            std::cout << "The graph has multiple minimum spanning trees.\n";
        }
    } catch (NoVertexException) {
        std::cout << "[ERROR] No vertex in the graph!\n";
        return;
    } catch (GraphDisconnectedException) {
        std::cout << "[ERROR] The graph is not connected, cannot generate a minimum "
                     "spanning tree!\n";
        return;
    }

    std::cout << "-----------\n";
    std::cout << "| Kruskal |\n";
    std::cout << "-----------\n";
    algorithm::kruskal(g);
    std::cout << std::endl;

    std::cout << "--------\n";
    std::cout << "| Prim |\n";
    std::cout << "--------\n";
    algorithm::prim(g);
    std::cout << std::endl;

    std::cout << "------------------\n";
    std::cout << "| Reverse-Delete |\n";
    std::cout << "------------------\n";
    algorithm::reverseDelete(g);
}