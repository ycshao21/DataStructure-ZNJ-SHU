#include <string>
#include <iostream>
#include "S4_QuickSort.h"
#include "S4_DNASort.h"

namespace Spring04
{
    void MergeForDNA(std::string& dna, int low, int mid, int high, int& count)
    {
        int i = low, j = mid + 1;
        int k = 0;
        std::string tmp(high - low + 1, ' ');
        while (i <= mid && j <= high)
        {
            if (dna[i] <= dna[j])
            {
                tmp[k++] = dna[i++];
            }
            else
            {
                tmp[k++] = dna[j++];
                count += mid - i + 1;
            }
        }
        while (i <= mid)
        {
            tmp[k++] = dna[i++];
        }

        while (j <= high)
        {
            tmp[k++] = dna[j++];
        }
        std::move(tmp.begin(), tmp.end(), dna.begin() + low);
    }

    void MergeSortForDNA(std::string& dna, int low, int high, int& count)
    {
        if (low >= high)
            return;

        int mid = low + ((high - low) >> 1);
        MergeSortForDNA(dna, low, mid, count);
        MergeSortForDNA(dna, mid + 1, high, count);
        MergeForDNA(dna, low, mid, high, count);
    }

    std::vector<std::string> DNASort(const std::vector<std::string>& dnaVec, std::ostream* out)
    {
        using Pair = std::pair<int, int>;  // {index of DNA sequence, number of reverse pairs}
        auto DNA_comp = [&](const Pair& lhs, const Pair& rhs)
        {
            if (lhs.second == rhs.second)
                return dnaVec[lhs.first] > dnaVec[rhs.first];

            return lhs.second < rhs.second;
        };

        int n = (int)dnaVec.size(), m = (int)dnaVec[0].size();
        std::vector<Pair> lookup(n);
        for (int i = 0; i < n; i++)
        {
            int count = 0;
            std::string copy(dnaVec[i]);
            MergeSortForDNA(copy, 0, m - 1, count);
            lookup[i] = { i, count };
        }
        QuickSort(lookup, 0, n - 1, DNA_comp);

        std::vector<std::string> sorted;
        for (const auto& e : lookup)
            sorted.push_back(dnaVec[e.first]);

        if (out)
        {
            for (const auto& dna : sorted)
                (*out) << dna << std::endl;
        }

        return sorted;
    }
}