#pragma once
#include<vector>

namespace MyDS
{
    template<class T, T defaultValue = T()>
    struct SquareMatrix
    {
    public:
        SquareMatrix(int dim = 0)
            : m_Data(dim, std::vector<T>(dim, defaultValue))
        {
        }
        SquareMatrix(const SquareMatrix<T, defaultValue>&) = default;
        SquareMatrix<T, defaultValue>& operator=(const SquareMatrix<T, defaultValue>&) = default;
        virtual ~SquareMatrix() = default;

        int GetDim() const { return (int)m_Data.size(); }
        int IsEmpty()const { return m_Data.empty(); }

        std::vector<T>& operator[](int idx) { return m_Data[idx]; }
        const std::vector<T>& operator[](int idx) const { return m_Data[idx]; }

        // Iterators
        auto begin() const { return m_Data.begin(); }
        auto end() const { return m_Data.end(); }

        void SetDim(int newDim)
        {
            if (m_Data.size() == newDim)
                return;

            if (m_Data.size() > newDim)
            {
                // Discard the extra rows and columns
                m_Data.resize(newDim);
                for (auto& row : m_Data)
                    row.resize(newDim);
            }
            else
            {
                // Add extra rows and columns
                for (auto& row : m_Data)
                    row.resize(newDim, defaultValue);
                m_Data.resize(newDim, std::vector<T>(newDim, defaultValue));
            }
        }

        void AddOneDim()
        {
            for (auto& row : m_Data)
                row.push_back(defaultValue);
            m_Data.push_back(std::vector<T>(m_Data.size() + 1, defaultValue));
        }

        void RemoveOneDim()
        {
            m_Data.pop_back();
            for (auto& row : m_Data)
                row.pop_back();
        }
    private:
        std::vector<std::vector<T>> m_Data;
    };
}
