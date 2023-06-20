#pragma once
#include<vector>

template<class _Ty, _Ty defaultValue = _Ty()>
struct SquareMatrix
{
    using sizet = size_t;
    using indext = size_t;
public:
    SquareMatrix(sizet theSize = 0) : mat(theSize, std::vector<_Ty>(theSize, defaultValue)) {}
    SquareMatrix(const SquareMatrix<_Ty, defaultValue>&) = default;
    SquareMatrix<_Ty, defaultValue>& operator=(const SquareMatrix<_Ty, defaultValue>&) = default;
    virtual ~SquareMatrix() = default;

    sizet size() const { return mat.size(); }
    sizet empty()const { return mat.empty(); }

    std::vector<_Ty>& operator[](indext idx) { return mat[idx]; }
    const std::vector<_Ty>& operator[](indext idx) const { return mat[idx]; }
    auto begin() const { return mat.begin(); }
    auto end() const { return mat.end(); }

    void resize(sizet newSize) {
        if (mat.size() == newSize) { return; }
        if (mat.size() > newSize) {
            mat.resize(newSize);
            for (auto& row : mat) {
                row.resize(newSize);
            }
        } else {
            for (auto& row : mat) {
                row.resize(newSize, defaultValue);
            }
            mat.resize(newSize, std::vector<_Ty>(newSize, defaultValue));
        }
    }

    void addOneDimension() {
        for (auto& row : mat) {
            row.push_back(defaultValue);
        }
        mat.push_back(std::vector<_Ty>(mat.size() + 1, defaultValue));
    }

    void removeOneDimension() {
        mat.pop_back();
        for (auto& row : mat) {
            row.pop_back();
        }
    }
private:
    std::vector<std::vector<_Ty>> mat;
};
