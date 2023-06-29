#pragma once
#include<vector>
#include<ranges>
#include"S3_Solutions.h"
#include"../../tools/Random.hpp"
#include"../../Tools/Settings.hpp"

namespace S3
{
    template<class Ty>
        requires std::is_arithmetic_v<Ty>
    void Q2_EfficiencyTest(sizet m, sizet n) {
        std::cout << "正在生成第一个数组……\n";
        std::vector<Ty> vec1 = Rand_Uniform<Ty>().generateVec(m, -1000000, 10000000);
        std::ranges::sort(vec1);

        std::cout << "正在生成第二个数组……" << std::endl;
        std::vector<Ty> vec2 = Rand_Normal<Ty>().generateVec(n, 5000, Ty(n));
        std::ranges::sort(vec2);

        double med;
        std::cout << "\n线性查找算法" << std::endl;
        clock_t start = clock();
        FindMedian_Linear(vec1, vec2);
        clock_t end = clock();
        std::cout << "用时" << end - start << "ms" << std::endl;

        std::cout << "\n二分查找算法" << std::endl;
        start = clock();
        FindMedian_Binary(vec1, vec2);
        end = clock();
        std::cout << "用时" << end - start << "ms" << std::endl;
    }
}
