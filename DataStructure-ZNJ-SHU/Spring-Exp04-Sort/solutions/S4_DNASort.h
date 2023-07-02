#pragma once
#include<vector>
#include<string>

namespace S4
{
    using indext = size_t;
    using sizet = size_t;

    std::vector<std::string> DNASort(const std::vector<std::string>& dnaVec, std::ostream* out = &std::cout);
}
