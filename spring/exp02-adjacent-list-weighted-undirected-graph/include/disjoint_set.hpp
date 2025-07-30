#pragma once

#include <cstdint>
#include <exception>
#include <iostream>
#include <vector>

namespace
{
using XXXX = int;
}

namespace myds
{

class DisjointSet
{
public:
    using IndexType = std::int64_t;

    DisjointSet(std::size_t size) : m_data(size, -1)
    {
    }
    ~DisjointSet() = default;

    IndexType getRootIndex(IndexType index) const
    {
        if (index >= (IndexType) m_data.size()) {
            throw std::runtime_error("Indee out of range!");
        }

        IndexType rootIndex = index;
        while (m_data[rootIndex] > -1) {
            rootIndex = m_data[rootIndex];
        }

        return rootIndex;
    }

    void unite(IndexType idx1, IndexType idx2)
    {
        if (idx1 != idx2) {
            m_data[idx1] += m_data[idx2];
            m_data[idx2] = idx1;
        }
    }

private:
    std::vector<IndexType> m_data;
};
}  // namespace myds
