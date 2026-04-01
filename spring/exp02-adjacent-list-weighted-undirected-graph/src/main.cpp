#include <array>
#include <filesystem>
#include <print>
#include <iostream>

#include "utils/console.hpp"

#include "adjacent_list_weighted_undirected_graph.hpp"
#include "solution.hpp"

static VT getVertex()
{
    std::print("Please input the vertex (integer): ");
    VT v;
    while (true) {
        std::cin >> v;
        bool validInput = !std::cin.fail();
        utils::clearBuffer();
        if (validInput) {
            break;
        }
        std::print("Invalid input. Please re-input the vertex (integer): ");
    }
    return v;
}

void exp02_adjListWUndirGraph()
{
    utils::Menu menu("Exp02 - Adjacent List Weighted Undirected Graph");

    Graph g;
    menu.setHeader([&]() {
        std::println();
        std::println("Edges:");
        g.printEdges();
        std::println();

        std::println("Adjacent List:");
        g.printAdjacentList();
    });

    menu.addItem("Insert Vertex", [&]() {
        VT v = getVertex();
        opt01_insertVertex(g, v);
    });
    menu.addItem("Erase Vertex", [&]() {
        VT v = getVertex();
        opt02_eraseVertex(g, v);
    });
    menu.addItem("Insert Edge", [&]() {
        std::print("Please input the edge (<start vertex> <end vertex> <weight>): ");
        VT from, to;
        WT weight;
        while (true) {
            std::cin >> from >> to >> weight;
            bool validInput = !std::cin.fail();
            utils::clearBuffer();
            if (validInput) {
                break;
            }
            std::print("Invalid input. Please re-input the edge (<start vertex> "
                       "<end vertex> <weight>): ");
        }
        opt03_insertEdge(g, from, to, weight);
    });
    menu.addItem("Erase Edge", [&]() {
        std::print("Please input the edge (<start vertex> <end vertex>): ");
        VT from, to;
        while (true) {
            std::cin >> from >> to;
            bool validInput = !std::cin.fail();
            utils::clearBuffer();
            if (validInput) {
                break;
            }
            std::print("Invalid input. Please re-input the edge (<start vertex> "
                       "<end vertex>): ");
        }
        opt04_eraseEdge(g, from, to);
    });
    menu.addItem("Degree", [&]() {
        VT v = getVertex();
        opt05_degree(g, v);
    });
    menu.addItem("Connected Component", [&]() {
        opt06_connectedComponent(g);
    });
    menu.addItem("Minimum Spanning Tree", [&]() {
        opt07_minimumSpanningTree(g);
    });
    menu.addItem("Clear", [&]() {
        g.clear();
    });
    menu.run();
}

int main()
{
    std::filesystem::current_path(EXPERIMENT_WORKING_DIR);
    exp02_adjListWUndirGraph();
}