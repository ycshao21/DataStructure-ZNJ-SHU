#include <print>

#include "graph_exceptions.hpp"
#include "solution.hpp"

void opt01_insertVertex(Graph& g, const VT& v)
{
    try {
        g.insertVertex(v);
    } catch (DuplicateVertexException) {
        std::println("[WARNING] Vertex \"{}\" is already in the graph. Skip.", v);
    }
}

void opt02_eraseVertex(Graph& g, const VT& v)
{
    try {
        g.eraseVertex(v);
    } catch (VertexNotFoundException) {
        std::println("[WARNING] Vertex \"{}\" is not in the graph. Skip.", v);
    }
}

void opt03_insertEdge(Graph& g, const VT& v1, const VT& v2, const WT& weight)
{
    try {
        g.insertEdge(v1, v2, weight);
    } catch (VertexNotFoundException) {
        std::println("[ERROR] Vertex \"{}\" or \"{}\" is not in the graph!", v1, v2);
    } catch (SelfLoopNotAllowedException) {
        std::println("[ERROR] Self loop is not allowed!");
    } catch (InvalidWeightException) {
        std::println("[ERROR] Invalid weight!");
    } catch (DuplicateEdgeException) {
        std::println("[WARNING] Edge (\"{}\", \"{}\") is already in the graph. Skip.", v1, v2);
    }
}

void opt04_eraseEdge(Graph& g, const VT& v1, const VT& v2)
{
    try {
        g.eraseEdge(v1, v2);
    } catch (VertexNotFoundException) {
        std::println("[ERROR] Vertex \"{}\" or \"{}\" is not in the graph!", v1, v2);
    } catch (EdgeNotFoundException) {
        std::println("[WARNING] Edge (\"{}\", \"{}\") is not in the graph. Skip.", v1, v2);
    }
}

void opt05_degree(const Graph& g, const VT& v)
{
    try {
        std::println("Degree: {}", g.countDegree(v));
    } catch (VertexNotFoundException) {
        std::println("[ERROR] Vertex \"{}\" is not in the graph!", v);
    }
}

void opt06_connectedComponent(const Graph& g)
{
    try {
        if (g.isConnected()) {
            std::println("The graph is connected.");
        } else {
            std::println("The graph is not connected.");
        }
        std::println("Number of connected components: {}", g.getNumOfConnectedComponent());
    } catch (NoVertexException) {
        std::println("[ERROR] No vertex in the graph!");
    }
}

void opt07_minimumSpanningTree(const Graph& g)
{
    try {
        if (g.hasUniqueMST()) {
            std::println("The graph has a unique minimum spanning tree.");
        } else {
            std::println("The graph has multiple minimum spanning trees.");
        }
    } catch (NoVertexException) {
        std::println("[ERROR] No vertex in the graph!");
        return;
    } catch (GraphDisconnectedException) {
        std::println("[ERROR] The graph is not connected, cannot generate a minimum "
                     "spanning tree!");
        return;
    }

    std::println("-----------");
    std::println("| Kruskal |");
    std::println("-----------");
    algorithm::kruskal(g);
    std::println();

    std::println("--------");
    std::println("| Prim |");
    std::println("--------");
    algorithm::prim(g);
    std::println();

    std::println("------------------");
    std::println("| Reverse-Delete |");
    std::println("------------------");
    algorithm::reverseDelete(g);
}