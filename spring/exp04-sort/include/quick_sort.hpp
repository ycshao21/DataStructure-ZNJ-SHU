#pragma once
#include <vector>

namespace myalgorithm
{

enum class PivotStrategy
{
    FirstElement = 0,
    MedianOfThree
};

template <class T, class Pred>
std::size_t partition_firstElement(std::vector<T>& vec, std::size_t low, std::size_t high,
                                   const Pred& compare)
{
    std::size_t i = low - 1;
    std::size_t j = high + 1;

    const T& pivot = vec[low];  // Choose the first element as the pivot.

    while (true) {
        // Find the element on the left that is no less than pivot.
        do {
            ++i;
        } while (compare(vec[i], pivot));

        // Find the element on the right that is no greater than pivot.
        do {
            --j;
        } while (compare(pivot, vec[j]));

        if (i >= j) {
            break;
        }

        // Swap the two elements.
        std::swap(vec[i], vec[j]);
    }

    return j;
}

template <class T, class Pred>
std::size_t partition_medianOfThree(std::vector<T>& vec, std::size_t low,
                                    std::size_t high, const Pred& compare)
{
    std::size_t mid = low + ((high - low) >> 1);

    if (compare(vec[high], vec[mid])) {
        std::swap(vec[mid], vec[high]);
    }

    if (compare(vec[high], vec[low])) {
        std::swap(vec[low], vec[high]);
    }

    if (compare(vec[low], vec[mid])) {
        std::swap(vec[mid], vec[low]);
    }

    return partition_firstElement(vec, low, high, compare);
}

// @brief Sort a vector using quick sort (choosing the first element as the pivot).
template <class T, class Pred, class PartitionFn>
void quickSort(std::vector<T>& vec, std::size_t low, std::size_t high,
               PartitionFn partition, const Pred& compare)
{
    if (low >= high) {
        return;
    }

    std::size_t p = partition(vec, low, high, compare);
    quickSort(vec, low, p, partition, compare);
    quickSort(vec, p + 1, high, partition, compare);
}

template <class T, class Pred = std::less<void>>
void quickSort(std::vector<T>& vec, PivotStrategy strategy = PivotStrategy::MedianOfThree,
               const Pred& compare = Pred{})
{
    switch (strategy) {
    case PivotStrategy::FirstElement: {
        quickSort(vec, 0, vec.size() - 1, partition_firstElement<T, Pred>, compare);
        break;
    }
    case myalgorithm::PivotStrategy::MedianOfThree: {
        quickSort(vec, 0, vec.size() - 1, partition_medianOfThree<T, Pred>, compare);
        break;
    }
    default:
        throw std::invalid_argument("Invalid pivot strategy.");
    }
}

}  // namespace myalgorithm
