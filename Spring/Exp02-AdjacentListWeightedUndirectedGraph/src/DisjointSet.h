#pragma once
#include <vector>

namespace MyDS
{
    class DisjointSet
    {
    public:
        DisjointSet(int size)
            : m_Data(size, -1)
        {
        }
        ~DisjointSet() = default;

        int GetRootIndex(int index) const
        {
            if (index >= (int)m_Data.size())
                throw "Index out of range!";

            int rt = index;
            while (m_Data[rt] > -1)
                rt = m_Data[rt];

            return rt;
        }

        void Unite(int fromIndex, int toIndex)
        {
            if (fromIndex != toIndex)
            {
                // Add vert2 to the set containing vert1
                m_Data[fromIndex] += m_Data[toIndex];
                m_Data[toIndex] = fromIndex;
            }
        }
    private:
        std::vector<int> m_Data;
    };
}
