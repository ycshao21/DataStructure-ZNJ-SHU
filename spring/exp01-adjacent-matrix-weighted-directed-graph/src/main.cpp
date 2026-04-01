#include <array>
#include <filesystem>
#include <format>
#include <print>

#include "utils/console.hpp"

#include "adjacent_matrix_weighted_directed_graph.hpp"
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

void exp01_adjMatWDirGraph()
{
    utils::Menu menu("Exp01 - Adjacent Matrix Weighted Directed Graph");

    Graph g;
    menu.setHeader([&]() {
        std::println();
        std::println("Edges:");
        g.printEdges();
        std::println();

        std::println("Adjacent Matrix:");
        g.printAdjacentMatrix();
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
    menu.addItem("Shortest Path", [&]() {
        std::print("Please input the source and end vertex (<source vertex> <end vertex>): ");
        VT src, end;
        while (true) {
            std::cin >> src >> end;
            bool validInput = !std::cin.fail();
            utils::clearBuffer();
            if (validInput) {
                break;
            }
            std::print("Invalid input. Please re-input the source and end vertex "
                         "(<source vertex> <end vertex>): ");
        }
        opt06_shortestPath(g, src, end);
    });

    menu.addItem("Clear", [&]() {
        g.clear();
    });

    menu.run();

    // while (true) {
    //     std::println("Exp01 - Adjacent Matrix Weighted Directed Graph");
    //     std::println();

    //     // Print menu
    //     for (std::size_t i = 0; i < menu.size(); ++i) {
    //         std::print("[{}] {} ", i + 1, menu[i]);
    //         if (i == menu.size() / 2 - 1) {
    //             std::println();
    //         }
    //     }
    //     std::println();

    //     // Get choice
    //     std::size_t choice = utils::getChoice(menu.size());
    //     if (choice == menu.size()) {
    //         return;
    //     }

    //     std::println("{}", std::string(60, '#'));

    //     if (choice == 7) {
    //         g.clear();
    //         continue;
    //     }

    //     std::println("[{}]", menu[choice - 1]);

    //     switch (choice) {
    //     case 1: {
    //         VT v = getVertex();
    //         opt01_insertVertex(g, v);
    //         break;
    //     }
    //     case 2: {
    //         VT v = getVertex();
    //         opt02_eraseVertex(g, v);
    //         break;
    //     }
    //     case 3: {
    //         std::print("Please input the edge (<start vertex> <end vertex> <weight>): ");
    //         VT from, to;
    //         WT weight;
    //         while (true) {
    //             std::cin >> from >> to >> weight;
    //             bool validInput = !std::cin.fail();
    //             utils::clearBuffer();
    //             if (validInput) {
    //                 break;
    //             }
    //             std::print("Invalid input. Please re-input the edge (<start vertex> "
    //                          "<end vertex> <weight>): ");
    //         }
    //         opt03_insertEdge(g, from, to, weight);
    //         break;
    //     }
    //     case 4: {
    //         std::print("Please input the edge (<start vertex> <end vertex>): ");
    //         VT from, to;
    //         while (true) {
    //             std::cin >> from >> to;
    //             bool validInput = !std::cin.fail();
    //             utils::clearBuffer();
    //             if (validInput) {
    //                 break;
    //             }
    //             std::print("Invalid input. Please re-input the edge (<start vertex> "
    //                          "<end vertex>): ");
    //         }
    //         opt04_eraseEdge(g, from, to);
    //         break;
    //     }
    //     case 5: {
    //         VT v = getVertex();
    //         opt05_degree(g, v);
    //         break;
    //     }
    //     case 6: {
    //         std::print("Please input the source and end vertex (<source vertex> <end vertex>): ");
    //         VT src, end;
    //         while (true) {
    //             std::cin >> src >> end;
    //             bool validInput = !std::cin.fail();
    //             utils::clearBuffer();
    //             if (validInput) {
    //                 break;
    //             }
    //             std::print("Invalid input. Please re-input the source and end vertex "
    //                          "(<source vertex> <end vertex>): ");
    //         }

    //         opt06_shortestPath(g, src, end);
    //         break;
    //     }
    //     }

    //     std::println("{}", std::string(60, '#'));
    //     std::println();
    // }
}

int main()
{
    std::filesystem::current_path(EXPERIMENT_WORKING_DIR);
    exp01_adjMatWDirGraph();
}