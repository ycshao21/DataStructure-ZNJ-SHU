#pragma once

#include <format>
#include <iostream>
#include <vector>


void BST_Test();

void BST_EfficiencyTest();

void findMinCommonElement(const std::vector<int> &a, const std::vector<int> &b,
                          const std::vector<int> &c,
                          std::ostream *out = &std::cout) {
  std::size_t i = 0, j = 0, k = 0;
  while (i < a.size() && j < b.size() && k < c.size()) {
    if (a[i] < b[j]) {
      i++;
    } else if (b[j] < c[k]) {
      j++;
    } else if (c[k] < a[i]) {
      k++;
    } else {
      if (out) {
        (*out) << std::format("{} {} {} {}\n", a[i], i + 1, j + 1, k + 1);
      }
      return;
    }
  }

  if (out) {
    (*out) << "NOT FOUND\n";
  }
}

template <class T>
  requires std::is_arithmetic_v<T>
double findMedian_Linear(const std::vector<T> vec1, const std::vector<T> &vec2,
                         std::ostream *out = &std::cout) {
  std::size_t m = vec1.size(), n = vec2.size();
  if (m > n) {
    return findMedian_Linear(vec2, vec1, out);
  }

  // The following code is based on the assumption that m <= n.
  std::size_t i = 0, j = 0;
  auto moveForward = [&](std::size_t step) -> T {
    for (std::size_t cnt = 0; cnt < step; cnt++) {
      if (i == m)
        j++;
      else
        vec1[i] < vec2[j] ? i++ : j++;
    }
    return (i == m) ? vec2[j] : std::min(vec1[i], vec2[j]);
  };

  // Find the (m+n+1)/2 th number:
  T first = moveForward((m + n + 1) / 2 - 1);
  // If total size is an odd number, return {first}.
  if ((m + n) & 1) {
    if (out) {
      (*out) << std::format("��λ��Ϊ{}\n", first);
    }
    return first;
  }

  // Otherwise, find the next number and return the average.
  T second = moveForward(1);
  double med = first + (second - first) / 2.0;
  if (out) {
    (*out) << std::format("��λ��Ϊ{}\n", med);
  }
  return med;
}

template <class T>
  requires std::is_arithmetic_v<T>
double FindMedian_Binary(const std::vector<T> &vec1, const std::vector<T> &vec2,
                         std::ostream *out = &std::cout) {
  std::size_t m = vec1.size(), n = vec2.size();
  if (m > n)
    return FindMedian_Binary(vec2, vec1, out);

  // The following code is based on the assumption that m <= n.
  std::size_t left = 0, right = m;
  T leftMax = -1, rightMin = -1;
  std::size_t leftSize = (m + n + 1) >> 1;
  // Binary search in vec1
  while (true) {
    std::size_t i = left + ((right - left) >> 1), j = leftSize - i;

    if (i == 0) { // Boundary reaches the left border.
      leftMax = vec2[j - 1];
      rightMin = (j == n) ? vec1[0] : std::min(vec1[0], vec2[j]);
      if (leftMax > rightMin) // It may happen if m == 1.
        left = i + 1;
      else
        break;
    } else if (i == m) // Boundary reaches the right border.
    {
      leftMax = (j == 0) ? vec1[i - 1] : std::max(vec1[i - 1], vec2[j - 1]);
      rightMin = vec2[j];
      break; // It is impossible that leftMax > rightMin.
    } else   // Normal case
    {
      leftMax = std::max(vec1[i - 1], vec2[j - 1]);
      rightMin = std::min(vec1[i], vec2[j]);

      if (vec1[i - 1] > vec2[j])
        right = i;
      else if (vec1[i] < vec2[j - 1])
        left = i + 1;
      else // Median found
        break;
    }
  }

  // If total size is an odd number, return leftMax.
  if ((m + n) & 1) {
    if (out) {
      (*out) << std::format("��λ��Ϊ{}\n", leftMax);
    }
    return leftMax;
  }

  // Otherwise, return the average of leftMax and rightMin.
  double med = leftMax + (rightMin - leftMax) / 2.0;
  if (out) {
    (*out) << std::format("��λ��Ϊ{}\n", med);
  }
  return med;
}