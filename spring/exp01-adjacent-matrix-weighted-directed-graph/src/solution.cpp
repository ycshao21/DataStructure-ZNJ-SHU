#include <format>
#include <iostream>

#include "graph_exceptions.hpp"
#include "shortest_path.hpp"
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

void opt03_insertEdge(Graph& g, const VT& from, const VT& to, const WT& weight)
{
    try {
        g.insertEdge(from, to, weight);
    } catch (VertexNotFoundException) {
        std::cout << std::format("[ERROR] Vertex \"{}\" or \"{}\" is not in the graph!\n",
                                 from, to);
    } catch (SelfLoopNotAllowedException) {
        std::cout << "[ERROR] Self loop is not allowed!\n";
    } catch (InvalidWeightException) {
        std::cout << "[ERROR] Invalid weight!\n";
    } catch (DuplicateEdgeException) {
        std::cout << std::format(
            "[WARNING] Edge <\"{}\", \"{}\"> is already in the graph. Skip.\n", from, to);
    }
}

void opt04_eraseEdge(Graph& g, const VT& from, const VT& to)
{
    try {
        g.eraseEdge(from, to);
    } catch (VertexNotFoundException) {
        std::cout << std::format("[ERROR] Vertex \"{}\" or \"{}\" is not in the graph!\n",
                                 from, to);
    } catch (EdgeNotFoundException) {
        std::cout << std::format(
            "[WARNING] Edge <\"{}\", \"{}\"> is not in the graph. Skip.\n", from, to);
    }
}

void opt05_degree(const Graph& g, const VT& v)
{
    try {
        std::cout << std::format("Degree: {}\n", g.countDegree(v));
        std::cout << std::format("Out-degree: {}\n", g.countOutDegree(v));
        std::cout << std::format("In-degree: {}\n", g.countInDegree(v));
    } catch (VertexNotFoundException) {
        std::cout << std::format("[ERROR] Vertex \"{}\" is not in the graph!\n", v);
    }
}

void opt06_shortestPath(const Graph& g, const VT& src, const VT& end)
{
    std::cout << "------------\n";
    std::cout << "| Dijkstra |\n";
    std::cout << "------------\n";
    try {
        algorithm::dijkstra(g, src, end);
    } catch (VertexNotFoundException) {
        std::cout << std::format("[ERROR] Vertex \"{}\" or \"{}\" is not in the graph!\n",
                                 src, end);
    } catch (NegativeEdgeException) {
        std::cout << "[ERROR] Negative edge is not allowed in Dijkstra algorithm!\n";
    }
    std::cout << '\n';

    std::cout << "----------------\n";
    std::cout << "| Bellman-Ford |\n";
    std::cout << "----------------\n";
    try {
        algorithm::bellmanFord(g, src, end);
    } catch (VertexNotFoundException) {
        std::cout << std::format("[ERROR] Vertex \"{}\" or \"{}\" is not in the graph!\n",
                                 src, end);
    } catch (NegativeCycleException) {
        std::cout << "[ERROR] Negative cycle is detected!\n";
    }
    std::cout << '\n';

    std::cout << "------------------\n";
    std::cout << "| Floyd-Warshall |\n";
    std::cout << "------------------\n";
    try {
        algorithm::floydWarshall(g, src, end);
    } catch (VertexNotFoundException) {
        std::cout << std::format("[ERROR] Vertex \"{}\" or \"{}\" is not in the graph!\n",
                                 src, end);
    } catch (NegativeCycleException) {
        std::cout << "[ERROR] Negative cycle is detected!\n";
    }
}
