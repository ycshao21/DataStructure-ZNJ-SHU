#pragma once
#include <vector>

namespace myds
{

template <class T, T defaultValue = T()>
struct SquareMatrix
{
public:
    SquareMatrix(std::size_t dim = 0) : m_data(dim, std::vector<T>(dim, defaultValue))
    {
    }
    SquareMatrix(const SquareMatrix<T, defaultValue>&) = default;
    SquareMatrix<T, defaultValue>& operator=(const SquareMatrix<T, defaultValue>&) =
        default;
    virtual ~SquareMatrix() = default;

    std::size_t getDim() const
    {
        return m_data.size();
    }

    bool isEmpty() const
    {
        return m_data.empty();
    }

    std::vector<T>& operator[](int idx)
    {
        return m_data[idx];
    }
    const std::vector<T>& operator[](int idx) const
    {
        return m_data[idx];
    }

    // Iterators
    auto begin() const
    {
        return m_data.begin();
    }
    auto end() const
    {
        return m_data.end();
    }

    void setDim(std::size_t newDim)
    {
        if (m_data.size() == newDim) {
            return;
        }

        if (m_data.size() > newDim) {
            // Discard the extra rows and columns
            m_data.resize(newDim);
            for (auto& row : m_data) {
                row.resize(newDim);
            }
        } else {
            // Add extra rows and columns
            for (auto& row : m_data) {
                row.resize(newDim, defaultValue);
            }
            m_data.resize(newDim, std::vector<T>(newDim, defaultValue));
        }
    }

    void addOneDim()
    {
        for (auto& row : m_data) {
            row.push_back(defaultValue);
        }
        m_data.push_back(std::vector<T>(m_data.size() + 1, defaultValue));
    }

    void removeOneDim()
    {
        m_data.pop_back();
        for (auto& row : m_data) {
            row.pop_back();
        }
    }

private:
    std::vector<std::vector<T>> m_data;
};

}  // namespace myds
