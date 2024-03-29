#pragma once
#include <vector>

namespace Spring04
{
    template<class Ty, class Pred>
    int Partition(std::vector<Ty>& vec, int low, int high, const Pred& comp)
    {
        int i = low - 1, j = high + 1;
        Ty pivot = vec[low];  // Choose the first element as the pivot.

        while (true)
        {
            // Find the element on the left that is no less than pivot.
            do { i++; } while (comp(vec[i], pivot));
            // Find the element on the right that is no greater than pivot.
            do { j--; } while (comp(pivot, vec[j]));

            if (i >= j)
                break;

            // Swap the two elements.
            std::swap(vec[i], vec[j]);
        }
        return j;
    }

    // @brief Sort a vector using quick sort (choosing the first element as the pivot).
    template<class Ty, class Pred = std::less<void>>
    void QuickSort(std::vector<Ty>& vec, int low, int high, const Pred& comp = {})
    {
        if (low >= high)
            return;
        int p = Partition(vec, low, high, comp);
        QuickSort(vec, low, p, comp);
        QuickSort(vec, p + 1, high, comp);
    }

    template<class Ty, class Pred>
    int MedianOfThreePartition(std::vector<Ty>& vec, int low, int high, const Pred& comp = {})
    {
        int mid = low + (high - low) >> 1;

        // vec[mid] < vec[low] < vec[high]
        if (comp(vec[high], vec[mid]))
            std::swap(vec[mid], vec[high]);
        
        if (comp(vec[high], vec[low]))
            std::swap(vec[low], vec[high]);
        
        if (comp(vec[low], vec[mid]))
            std::swap(vec[mid], vec[low]);
        
        return Partition(vec, low, high, comp);
    }

    // @brief Sort a vector using quick sort (choosing the median of the first, middle, and last elements as the pivot).
    template<class Ty, class Pred = std::less<void>>
    void QuickSort_MedianOfThree(std::vector<Ty>& vec, int low, int high, const Pred& comp = {})
    {
        if (low >= high)
            return;

        int p = MedianOfThreePartition(vec, low, high, comp);
        QuickSort_MedianOfThree(vec, low, p - 1, comp);
        QuickSort_MedianOfThree(vec, p + 1, high, comp);
    }
}
