#pragma once
#include <iostream>
#include <vector>

namespace Spring03
{
    void BST_Test();

    void BST_EfficiencyTest();

    template<class Ty, class Pred = std::less<void>>
    void FindMinCommonElement(const std::vector<Ty>& a, const std::vector<Ty>& b, const std::vector<Ty>& c,
        const Pred& less = {}, std::ostream* out = &std::cout)
    {
        int i = 0, j = 0, k = 0;
        while (i < a.size() && j < b.size() && k < c.size())
        {
            if (less(a[i], b[j]))
            {
                i++;
            }
            else if (less(b[j], c[k]))
            {
                j++;
            }
            else if (less(c[k], a[i]))
            {
                k++;
            }
            else
            {
                if (out)
                    (*out) << a[i] << " " << (i + 1) << " " << (j + 1) << " " << (k + 1) << std::endl;
                return;
            }
        }

        if (out)
            (*out) << "NOT FOUND" << std::endl;
    }

    template<class Ty>
        requires std::is_arithmetic_v<Ty>
    double FindMedian_Linear(const std::vector<Ty> vec1, const std::vector<Ty>& vec2, std::ostream* out = &std::cout)
    {
        int m = (int)vec1.size(), n = (int)vec2.size();
        if (m > n)
            return FindMedian_Linear(vec2, vec1, out);

        // The following code is based on the assumption that m <= n.
        int i = 0, j = 0;
        auto moveForward = [&](int step) -> Ty {
            for (int cnt = 0; cnt < step; cnt++)
            {
                if (i == m)
                    j++;
                else
                    vec1[i] < vec2[j] ? i++ : j++;
            }
            return (i == m) ? vec2[j] : std::min(vec1[i], vec2[j]);
        };

        // Find the (m+n+1)/2 th number:
        Ty first = moveForward((m + n + 1) / 2 - 1);
        // If total size is an odd number, return {first}.
        if ((m + n) & 1)
        {
            if (out)
                (*out) << "中位数为" << first << std::endl;
            return first;
        }

        // Otherwise, find the next number and return the average.
        Ty second = moveForward(1);
        double med = first + (second - first) / 2.0;
        if (out)
            (*out) << "中位数为" << med << std::endl;
        return med;
    }

    template<class Ty>
        requires std::is_arithmetic_v<Ty>
    double FindMedian_Binary(const std::vector<Ty>& vec1, const std::vector<Ty>& vec2, std::ostream* out = &std::cout)
    {
        int m = (int)vec1.size(), n = (int)vec2.size();
        if (m > n)
            return FindMedian_Binary(vec2, vec1, out);

        // The following code is based on the assumption that m <= n.
        int left = 0, right = m;
        Ty leftMax = -1, rightMin = -1;
        int leftSize = (m + n + 1) >> 1;
        // Binary search in vec1
        while (true)
        {
            int i = left + ((right - left) >> 1),
                j = leftSize - i;

            if (i == 0)
            {  // Boundary reaches the left border.
                leftMax = vec2[j - 1];
                rightMin = (j == n) ? vec1[0] : std::min(vec1[0], vec2[j]);
                if (leftMax > rightMin)  // It may happen if m == 1.
                    left = i + 1;
                else
                    break;
            }
            else if (i == m)  // Boundary reaches the right border.
            {
                leftMax = (j == 0) ? vec1[i - 1] : std::max(vec1[i - 1], vec2[j - 1]);
                rightMin = vec2[j];
                break;  // It is impossible that leftMax > rightMin.
            }
            else  // Normal case
            {
                leftMax = std::max(vec1[i - 1], vec2[j - 1]);
                rightMin = std::min(vec1[i], vec2[j]);

                if (vec1[i - 1] > vec2[j])
                    right = i;
                else if (vec1[i] < vec2[j - 1])
                    left = i + 1;
                else  // Median found
                    break;
            }
        }

        // If total size is an odd number, return leftMax.
        if ((m + n) & 1)
        {
            if (out)
                (*out) << "中位数为" << leftMax << std::endl;
            return leftMax;
        }

        // Otherwise, return the average of leftMax and rightMin.
        double med = leftMax + (rightMin - leftMax) / 2.0;
        if (out)
            (*out) << "中位数为" << med << std::endl;
        return med;
    }
}
