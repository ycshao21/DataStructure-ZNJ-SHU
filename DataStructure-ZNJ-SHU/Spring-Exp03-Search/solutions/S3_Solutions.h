#pragma once
#include<iostream>
#include<vector>
//#include<unordered_set>

namespace S3
{
    using indext = size_t;
    using sizet = size_t;

    template<class Ty, class Pred = std::less<void>>
    void FindMinCommonElement(const std::vector<Ty>& a, const std::vector<Ty>& b, const std::vector<Ty>& c,
        const Pred& less = {}, std::ostream* out = &std::cout)
    {
        indext i = 0, j = 0, k = 0;
        while (i < a.size() && j < b.size() && k < c.size()) {
            if (less(a[i], b[j])) {
                i++;
            } else if (less(b[j], c[k])) {
                j++;
            } else if (less(c[k], a[i])) {
                k++;
            } else {
                if (out) {
                    (*out) << a[i] << " " << (i + 1) << " " << (j + 1) << " " << (k + 1) << std::endl;
                }
                return;
            }
        }
        if (out) {
            (*out) << "NOT FOUND" << std::endl;
        }
    }

    template<class Ty>
        requires std::is_arithmetic_v<Ty>
    double FindMedian_Linear(const std::vector<Ty> vec1, const std::vector<Ty>& vec2, std::ostream* out = &std::cout) {
        sizet m = vec1.size(), n = vec2.size();
        if (m > n) {
            return FindMedian_Linear(vec2, vec1, out);
        }
        // The following code is based on the assumption that m <= n.
        indext i = 0, j = 0;
        auto moveForward = [&](sizet step) -> Ty {
            for (indext cnt = 0; cnt < step; cnt++) {
                if (i == m) {
                    j++;
                } else {
                    vec1[i] < vec2[j] ? i++ : j++;
                }
            }
            return (i == m) ? vec2[j] : std::min(vec1[i], vec2[j]);
        };
        // Find the (m+n+1)/2 th number:
        Ty first = moveForward((m + n + 1) / 2 - 1);
        // If total size is an odd number, return first.
        if ((m + n) & 1) {
            if (out) {
                (*out) << "中位数为" << first << std::endl;
            }
            return first;
        }
        // Otherwise, find the next number and return the average.
        Ty second = moveForward(1);
        double med = first + (second - first) / 2.0;
        if (out) {
            (*out) << "中位数为" << med << std::endl;
        }
        return med;
    }

    template<class Ty>
        requires std::is_arithmetic_v<Ty>
    double FindMedian_Binary(const std::vector<Ty>& vec1, const std::vector<Ty>& vec2, std::ostream* out = &std::cout) {
        sizet m = vec1.size(), n = vec2.size();
        if (m > n) {
            return FindMedian_Binary(vec2, vec1, out);
        }
        // The following code is based on the assumption that m <= n.
        indext left = 0, right = m;
        Ty leftMax = -1, rightMin = -1;
        sizet leftSize = (m + n + 1) >> 1;
        // Binary search in vec1
        while (true) {
            indext i = left + ((right - left) >> 1),
                j = leftSize - i;
            if (i == 0) {  // Boundary reaches the left border.
                leftMax = vec2[j - 1];
                rightMin = (j == n) ? vec1[0] : std::min(vec1[0], vec2[j]);
                if (leftMax > rightMin) {  // It may happen if m == 1.
                    left = i + 1;
                } else {
                    break;
                }
            } else if (i == m) {  // Boundary reaches the right border.
                leftMax = (j == 0) ? vec1[i - 1] : std::max(vec1[i - 1], vec2[j - 1]);
                rightMin = vec2[j];
                break;  // It is impossible that leftMax > rightMin.
            } else {  // Normal case
                leftMax = std::max(vec1[i - 1], vec2[j - 1]);
                rightMin = std::min(vec1[i], vec2[j]);
                if (vec1[i - 1] > vec2[j]) {
                    right = i;
                } else if (vec1[i] < vec2[j - 1]) {
                    left = i + 1;
                } else {  // Median found
                    break;
                }
            }
        }
        // If total size is an odd number, return leftMax.
        if ((m + n) & 1) {
            if (out) {
                (*out) << "中位数为" << leftMax << std::endl;
            }
            return leftMax;
        }
        // Otherwise, return the average of leftMax and rightMin.
        double med = leftMax + (rightMin - leftMax) / 2.0;
        if (out) {
            (*out) << "中位数为" << med << std::endl;
        }
        return med;
    }

    //void test_rand_runtime()
    //{
    //    const int N = 100000;
    //    std::unordered_set<int> a;
    //    int i = 0;
    //    while (a.size() < N) {
    //        a.insert((rand() + i) % INT_MAX);
    //        i = (i + 1) % N;
    //    }
    //    std::vector<int> b;		//直接遍历a进行删除，因为unordered_set每次遍历不一致，会导致删除的顺序不一致
    //    for (auto& e : a) b.push_back(e);
    //    std::cout << a.size() << std::endl;
    //    clock_t t = clock();
    //    BSTree<int, int> tree;
    //    BSTree<int, int> tree1;
    //    for (auto& e : b) tree.Insert(e, e);
    //    for (auto& e : b) tree1.Insert(e, e);
    //    //BSTree<int, int> tree1(tree);
    //    t = clock() - t;
    //    std::cout << "Rand insert time: " << (double)t / CLOCKS_PER_SEC << std::endl;
    //    clock_t t1 = clock();
    //    for (auto& e : b) {
    //        tree.Erase_lr(e);
    //    }
    //    t1 = clock() - t1;
    //    //std::cout << "Erase time1: " << (double)t1 / CLOCKS_PER_SEC << std::endl;
    //    clock_t t2 = clock();
    //    for (auto& e : b) {
    //        tree1.Erase_ll(e);
    //    }
    //    t2 = clock() - t2;
    //    std::cout << "Rand erase time1: " << (double)t1 / CLOCKS_PER_SEC << " ,Rand erase time2: " << (double)t2 / CLOCKS_PER_SEC << std::endl;
    //}

    //void test_sort_runtime()
    //{
    //    const int N = 100000;
    //    std::vector<int> b;
    //    for (int i = 0; i < N; i++) b.push_back(i);
    //    clock_t t = clock();
    //    BSTree<int, int> tree;
    //    BSTree<int, int> tree1;
    //    for (auto& e : b) tree.Insert(e, e);
    //    for (auto& e : b) tree1.Insert(e, e);
    //    //BSTree<int, int> tree1(tree);
    //    t = clock() - t;
    //    std::cout << "Sort insert time: " << (double)t / CLOCKS_PER_SEC << std::endl;
    //    clock_t t1 = clock();
    //    for (auto& e : b) {
    //        tree.Erase_lr(e);
    //    }
    //    t1 = clock() - t1;
    //    //std::cout << "Erase time1: " << (double)t1 / CLOCKS_PER_SEC << std::endl;
    //    clock_t t2 = clock();
    //    for (auto& e : b) {
    //        tree1.Erase_ll(e);
    //    }
    //    t2 = clock() - t2;
    //    std::cout << "Sort erase time1: " << (double)t1 / CLOCKS_PER_SEC << " ,Sort erase time2: " << (double)t2 / CLOCKS_PER_SEC << std::endl;
    //}

    //void Question03() {
    //    BSTree<int, int> tree;
    //    int a[] = { 5,3,4,1,7,8,2,6,0,9 };
    //    for (auto e : a) {
    //        tree.InsertR(e, e);
    //    }
    //    BSTree<int, int> tree1(tree);
    //    tree.printTree();
    //    tree1.printTree();
    //    for (auto e : a) {
    //        tree.Erase_ll(e);
    //        tree1.Erase_lr(e);
    //        tree.printTree();
    //        tree1.printTree();
    //    }

    //    test_rand_runtime();
    //    test_sort_runtime();
    //}
}
