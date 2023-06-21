#pragma once

template<class WeightTy>
struct AdjListEdge
{
    size_t toIndex;  // Index of the vertex the edge is pointing to.
    WeightTy weight{ 1 };  // Weight of the edge.
};
