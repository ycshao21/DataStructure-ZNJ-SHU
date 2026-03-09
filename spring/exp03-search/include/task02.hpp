#pragma once

#include <vector>

// Note: These algorithms assume that we have two equal-length sorted arrays of size `n`.
// And we define that the median is the n-th element in the merged sorted array of size `2n`.

template <class T>
T findMedian_linear(const std::vector<T>& vec1, const std::vector<T>& vec2)
{
    std::size_t n = vec1.size();
    std::size_t i = 0, j = 0;
    T med = static_cast<T>(0);
    for (std::size_t cnt = 0; cnt < n; ++cnt) {
        if (vec1[i] < vec2[j]) {
            med = vec1[i++];
        } else {
            med = vec2[j++];
        }
    }
    return med;
}

template <class T>
T findMedian_binary(const std::vector<T>& vec1, const std::vector<T>& vec2)
{
    std::size_t n = vec1.size();
    std::size_t left = 0, right = n;

    while (left <= right) {
        std::size_t i = left + ((right - left) >> 1);
        std::size_t j = n - i;

        if (i < n && vec2[j - 1] > vec1[i]) {
            left = i + 1;  // i is too small, increase it
        } else if (i > 0 && vec1[i - 1] > vec2[j]) {
            right = i - 1; // i is too big, decrease it
        } else {  // i is perfect
            if (i == 0) {
                return vec2[j - 1];
            }
            if (j == 0) {
                return vec1[i - 1];
            }
            return std::max(vec1[i - 1], vec2[j - 1]);
        }
    }
    return static_cast<T>(0);  // This line should never be reached.
}

// The following two functions are the generalized versions of the above two functions,
// which can handle the case when the two sorted arrays have different sizes,
// and the median is defined as the average of the two middle elements in the merged sorted array when the total size is even.

template <class T>
double findMedian_linear_general(const std::vector<T>& vec1, const std::vector<T>& vec2)
{
    std::size_t m = vec1.size();
    std::size_t n = vec2.size();
    if (m > n) {
        return findMedian_linear_general(vec2, vec1);
    }

    // Note that m <= n is guaranteed here.
    std::size_t totalSize = m + n;
    std::size_t i = 0, j = 0;
    T current = 0, prev = 0;

    // For example, if `totalSize` is 5, we get `current` at the index of 2, and the median is `current` itself.
    // Otherwise, if `totalSize` is 6, we get `prev` at the index of 2 and `current` at the index of 3, and the median is the average of `prev` and `current`.
    for (std::size_t cnt = 0; cnt <= totalSize / 2; ++cnt) {
        prev = current;
        if (i == m) {
            current = vec2[j++];
        } else if (j == n) {
            current = vec1[i++];
        } else if (vec1[i] < vec2[j]) {
            current = vec1[i++];
        } else {
            current = vec2[j++];
        }
    }

    return (totalSize % 2 == 1)
        ? static_cast<double>(current)
        : (static_cast<double>(prev) + static_cast<double>(current)) / 2.0;
}

template <class T>
double findMedian_binary_general(const std::vector<T>& vec1, const std::vector<T>& vec2)
{
    std::size_t m = vec1.size();
    std::size_t n = vec2.size();
    if (m > n) {
        return findMedian_binary_general(vec2, vec1);
    }

    // Note that m <= n is guaranteed here.
    std::size_t left = 0, right = m;
    std::size_t leftSize = (m + n + 1) >> 1;

    // Binary search on the smaller array `vec1`.
    while (left <= right) {
        std::size_t i = left + ((right - left) >> 1);
        std::size_t j = leftSize - i;

        if (i < m && vec2[j - 1] > vec1[i]) {
            left = i + 1;  // i is too small, increase it
        } else if (i > 0 && vec1[i - 1] > vec2[j]) {
            right = i - 1; // i is too big, decrease it
        } else {  // i is perfect
            T leftMax = (i == 0) ? vec2[j - 1] :
                        ((j == 0) ? vec1[i - 1] : std::max(vec1[i - 1], vec2[j - 1]));
            if ((m + n) % 2 == 1) {
                return static_cast<double>(leftMax);
            }
            T rightMin = (i == m) ? vec2[j] : 
                        ((j == n) ? vec1[i] : std::min(vec1[i], vec2[j]));
            return (static_cast<double>(leftMax) + static_cast<double>(rightMin)) / 2.0;
        }
    }
    return 0.0;  // This line should never be reached.
}