#pragma once

#include <chrono>

namespace utils {

class Timer {
public:
  Timer() { reset(); }
  ~Timer() = default;

  void reset() { m_start = std::chrono::high_resolution_clock::now(); }
  double elapsed() const {
    return std::chrono::duration_cast<std::chrono::duration<double>>(
               std::chrono::high_resolution_clock::now() - m_start)
        .count();
  }

private:
  std::chrono::high_resolution_clock::time_point m_start;
};

} // namespace utils