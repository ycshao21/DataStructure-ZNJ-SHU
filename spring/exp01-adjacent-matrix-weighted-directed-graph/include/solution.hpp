#pragma once
#include "adjacent_matrix_weighted_directed_graph.hpp"

using VT = int;
using WT = int;
using Graph = myds::AdjMatWDirGraph<VT, WT>;

void opt01_insertVertex(Graph& g, const VT& v);
void opt02_eraseVertex(Graph& g, const VT& v);
void opt03_insertEdge(Graph& g, const VT& from, const VT& to, const WT& weight);
void opt04_eraseEdge(Graph& g, const VT& from, const VT& to);
void opt05_degree(const Graph& g, const VT& v);
void opt06_shortestPath(const Graph& g, const VT& src, const VT& end);
