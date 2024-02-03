#pragma once

namespace MyDS
{
    template<class WeightTy>
    struct AdjListEdge
    {
        int toIndex;  // Index of the vertex the edge is pointing to.
        WeightTy weight{ 1 };  // Weight of the edge.
    };
}
