#include <print>

#include "dna_sort.hpp"
#include "quick_sort.hpp"

void mergeForDNA(std::string& dna, std::size_t low, std::size_t mid, std::size_t high,
                 std::size_t& count)
{
    std::size_t i = low, j = mid + 1;
    std::size_t k = 0;

    std::string tmp(high - low + 1, ' ');

    while (i <= mid && j <= high) {
        if (dna[i] <= dna[j]) {
            tmp[k++] = dna[i++];
        } else {
            tmp[k++] = dna[j++];
            count += mid - i + 1;
        }
    }

    while (i <= mid) {
        tmp[k++] = dna[i++];
    }

    while (j <= high) {
        tmp[k++] = dna[j++];
    }

    std::move(tmp.begin(), tmp.end(), dna.begin() + low);
}

void mergeSortForDNA(std::string& dna, std::size_t low, std::size_t high,
                     std::size_t& count)
{
    if (low >= high) {
        return;
    }

    std::size_t mid = low + ((high - low) >> 1);
    mergeSortForDNA(dna, low, mid, count);
    mergeSortForDNA(dna, mid + 1, high, count);
    mergeForDNA(dna, low, mid, high, count);
}

std::vector<std::string> dnaSort(const std::vector<std::string>& dnaVec,
                                 std::ostream* out)
{
    using Pair = std::pair<std::size_t, std::size_t>;  // {index of DNA sequence, number
                                                       // of reverse pairs}
    auto dnaComp = [&](const Pair& lhs, const Pair& rhs) {
        if (lhs.second == rhs.second) {
            return dnaVec[lhs.first] > dnaVec[rhs.first];
        }
        return lhs.second < rhs.second;
    };

    std::size_t n = dnaVec.size();
    std::size_t m = dnaVec[0].size();

    std::vector<Pair> lookup(n);

    for (std::size_t i = 0; i < n; ++i) {
        std::size_t count = 0;
        std::string copy(dnaVec[i]);
        mergeSortForDNA(copy, 0, m - 1, count);
        lookup[i] = {i, count};
    }

    myalgorithm::quickSort(lookup, myalgorithm::PivotStrategy::MedianOfThree, dnaComp);

    std::vector<std::string> sorted;
    sorted.reserve(lookup.size());
    for (const auto& e : lookup) {
        sorted.push_back(dnaVec[e.first]);
    }

    if (out != nullptr) {
        for (const auto& dna : sorted) {
            std::println(*out, "{}", dna);
        }
    }

    return sorted;
}