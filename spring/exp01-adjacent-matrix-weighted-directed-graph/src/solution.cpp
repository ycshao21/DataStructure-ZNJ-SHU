#include <format>
#include <print>

#include "graph_exceptions.hpp"
#include "shortest_path.hpp"
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

void opt03_insertEdge(Graph& g, const VT& from, const VT& to, const WT& weight)
{
    try {
        g.insertEdge(from, to, weight);
    } catch (VertexNotFoundException) {
        std::println("[ERROR] Vertex \"{}\" or \"{}\" is not in the graph!", from, to);
    } catch (SelfLoopNotAllowedException) {
        std::println("[ERROR] Self loop is not allowed!");
    } catch (InvalidWeightException) {
        std::println("[ERROR] Invalid weight!");
    } catch (DuplicateEdgeException) {
        std::println("[WARNING] Edge <\"{}\", \"{}\"> is already in the graph. Skip.", from, to);
    }
}

void opt04_eraseEdge(Graph& g, const VT& from, const VT& to)
{
    try {
        g.eraseEdge(from, to);
    } catch (VertexNotFoundException) {
        std::println("[ERROR] Vertex \"{}\" or \"{}\" is not in the graph!", from, to);
    } catch (EdgeNotFoundException) {
        std::println("[WARNING] Edge <\"{}\", \"{}\"> is not in the graph. Skip.", from, to);
    }
}

void opt05_degree(const Graph& g, const VT& v)
{
    try {
        std::println("Degree: {}", g.countDegree(v));
        std::println("Out-degree: {}", g.countOutDegree(v));
        std::println("In-degree: {}", g.countInDegree(v));
    } catch (VertexNotFoundException) {
        std::println("[ERROR] Vertex \"{}\" is not in the graph!", v);
    }
}

void opt06_shortestPath(const Graph& g, const VT& src, const VT& end)
{
    std::println("------------");
    std::println("| Dijkstra |");
    std::println("------------");
    try {
        algorithm::dijkstra(g, src, end);
    } catch (VertexNotFoundException) {
        std::println("[ERROR] Vertex \"{}\" or \"{}\" is not in the graph!", src, end);
    } catch (NegativeEdgeException) {
        std::println("[ERROR] Negative edge is not allowed in Dijkstra algorithm!");
    }
    std::println();

    std::println("----------------");
    std::println("| Bellman-Ford |");
    std::println("----------------");
    try {
        algorithm::bellmanFord(g, src, end);
    } catch (VertexNotFoundException) {
        std::println("[ERROR] Vertex \"{}\" or \"{}\" is not in the graph!", src, end);
    } catch (NegativeCycleException) {
        std::println("[ERROR] Negative cycle is detected!");
    }
    std::println();

    std::println("------------------");
    std::println("| Floyd-Warshall |");
    std::println("------------------");
    try {
        algorithm::floydWarshall(g, src, end);
    } catch (VertexNotFoundException) {
        std::println("[ERROR] Vertex \"{}\" or \"{}\" is not in the graph!", src, end);
    } catch (NegativeCycleException) {
        std::println("[ERROR] Negative cycle is detected!");
    }
}
