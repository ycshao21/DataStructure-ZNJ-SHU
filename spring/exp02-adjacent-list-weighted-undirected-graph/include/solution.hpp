#pragma once
#include "adjacent_list_weighted_undirected_graph.hpp"

using VT = int;
using WT = int;
using Graph = myds::AdjListWUndirGraph<VT, WT>;

void opt01_insertVertex(Graph& g, const VT& v);
void opt02_eraseVertex(Graph& g, const VT& v);
void opt03_insertEdge(Graph& g, const VT& v1, const VT& v2, const WT& weight);
void opt04_eraseEdge(Graph& g, const VT& v1, const VT& v2);
void opt05_degree(const Graph& g, const VT& v);
void opt06_connectedComponent(const Graph& g);
void opt07_minimumSpanningTree(const Graph& g);
