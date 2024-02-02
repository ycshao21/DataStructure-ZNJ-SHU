#pragma once
#include<vector>
#include"../../Tools/MyExceptions.h"

class DisjointSet
{
    using indext = long long;
    using sizet = size_t;
public:
    DisjointSet(sizet theSize) : _data(theSize, -1) {}

    ~DisjointSet() = default;

    indext root(indext idx) const {
        if (idx >= (indext)_data.size()) {
            throw IllegalIndex();
        }
        indext rt = idx;
        while (_data[rt] > -1) {
            rt = _data[rt];
        }
        return rt;
    }

    void unite(indext fromIndex, indext toIndex) {
        if (fromIndex != toIndex) {
            // Add vert2 to the set containing vert1
            _data[fromIndex] += _data[toIndex];
            _data[toIndex] = fromIndex;
        }
    }
private:
    std::vector<indext> _data;
};
