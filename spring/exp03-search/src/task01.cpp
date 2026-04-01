#include <print>
#include <vector>
#include <iostream>

#include "task01.hpp"

void findMinCommonElement(const std::vector<int>& a, const std::vector<int>& b,
                          const std::vector<int>& c, std::ostream* out)
{
    std::size_t i = 0, j = 0, k = 0;
    while (i < a.size() && j < b.size() && k < c.size()) {
        if (a[i] < b[j]) {
            ++i;
        } else if (b[j] < c[k]) {
            ++j;
        } else if (c[k] < a[i]) {
            ++k;
        } else {
            if (out != nullptr) {
                std::println(*out, "{} {} {} {}", a[i], i + 1, j + 1, k + 1);
            }
            return;
        }
    }

    if (out != nullptr) {
        std::println(*out, "NOT FOUND");
    }
}