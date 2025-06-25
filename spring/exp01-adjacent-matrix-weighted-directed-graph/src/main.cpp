#include <array>
#include <filesystem>
#include <format>
#include <iostream>

#include "utils/console.hpp"

#include "adjacent_matrix_weighted_directed_graph.hpp"
#include "solution.hpp"

static VT getVertex()
{
    std::cout << "Please input the vertex (integer): ";
    VT v;
    while (true) {
        std::cin >> v;
        bool validInput = !std::cin.fail();
        utils::clearBuffer();
        if (validInput) {
            break;
        }
        std::cout << "Invalid input. Please re-input the vertex (integer): ";
    }
    return v;
}

void exp01_adjMatWDirGraph()
{
    const std::array<std::string, 8> menu = {
        "Insert Vertex", "Erase Vertex",  "Insert Edge", "Erase Edge",
        "Degree",        "Shortest Path", "Clear",       "Exit"};

    Graph g;

    while (true) {
        std::cout << "Exp01 - Adjacent Matrix Weighted Directed Graph\n\n";

        std::cout << "Edges:\n";
        g.printEdges();
        std::cout << "\nAdjacent Matrix:\n";
        g.printAdjacentMatrix();
        std::cout << '\n';

        for (std::size_t i = 0; i < menu.size(); ++i) {
            std::cout << std::format("[{}] {} ", i + 1, menu[i]);
            if (i == menu.size() / 2 - 1) {
                std::cout << '\n';
            }
        }
        std::cout << '\n';

        std::size_t choice = utils::getChoice(menu.size());
        if (choice == menu.size()) {
            return;
        }

        std::cout << std::string(60, '#') << '\n' << std::flush;

        if (choice == 7) {
            g.clear();
            continue;
        }

        std::cout << std::format("[{}]\n", menu[choice - 1]);

        switch (choice) {
        case 1: {
            VT v = getVertex();
            opt01_insertVertex(g, v);
            break;
        }
        case 2: {
            VT v = getVertex();
            opt02_eraseVertex(g, v);
            break;
        }
        case 3: {
            std::cout << "Please input the edge (<start vertex> <end vertex> <weight>): ";
            VT from, to;
            WT weight;
            while (true) {
                std::cin >> from >> to >> weight;
                bool validInput = !std::cin.fail();
                utils::clearBuffer();
                if (validInput) {
                    break;
                }
                std::cout << "Invalid input. Please re-input the edge (<start vertex> "
                             "<end vertex> <weight>): ";
            }
            opt03_insertEdge(g, from, to, weight);
            break;
        }
        case 4: {
            std::cout << "Please input the edge (<start vertex> <end vertex>): ";
            VT from, to;
            while (true) {
                std::cin >> from >> to;
                bool validInput = !std::cin.fail();
                utils::clearBuffer();
                if (validInput) {
                    break;
                }
                std::cout << "Invalid input. Please re-input the edge (<start vertex> "
                             "<end vertex>): ";
            }
            opt04_eraseEdge(g, from, to);
            break;
        }
        case 5: {
            VT v = getVertex();
            opt05_degree(g, v);
            break;
        }
        case 6: {
            std::cout << "Please input the source and end vertex (<source vertex> <end "
                         "vertex>): ";
            VT src, end;
            while (true) {
                std::cin >> src >> end;
                bool validInput = !std::cin.fail();
                utils::clearBuffer();
                if (validInput) {
                    break;
                }
                std::cout << "Invalid input. Please re-input the source and end vertex "
                             "(<source vertex> <end vertex>): ";
            }

            opt06_shortestPath(g, src, end);
            break;
        }
        }

        std::cout << std::string(60, '#') << '\n' << std::flush;
    }
}

int main()
{
    std::filesystem::current_path(EXPERIMENT_WORKING_DIR);
    exp01_adjMatWDirGraph();
}