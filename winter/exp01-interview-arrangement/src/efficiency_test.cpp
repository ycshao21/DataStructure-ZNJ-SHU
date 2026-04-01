#include <array>
#include <filesystem>
#include <fstream>
#include <print>

#include "utils/timer.hpp"

#include "solution.hpp"

void efficiencyTest()
{
    std::filesystem::path resultPath = "output/result.csv";
    std::filesystem::create_directories(resultPath.parent_path());

    std::ofstream file(resultPath);
    std::println(file, "N,K,M,Elapsed Time(s)");

    constexpr std::array<std::size_t, 5> nList = {100, 1000, 10000, 100000, 1000000};
    constexpr std::array<std::size_t, 4> kList = {2, 20, 200, 2000};
    constexpr std::array<std::size_t, 4> mList = {3, 30, 300, 3000};

    for (std::size_t n : nList) {
        for (std::size_t i = 0; i < kList.size(); ++i) {
            std::size_t k = kList[i], m = mList[i];
            std::println("N={}, K={}, M={}", n, k, m);

            {
                utils::Timer timer;
                runTask01(n, k, m, nullptr);
                double elapsed = timer.elapsed();
                std::println("Elapsed time: {}s", elapsed);

                std::println(file, "{},{},{},{}", n, k, m, elapsed);
                file.flush();  // Flush after each write to ensure data is saved even if the program crashes.
            }

            std::println("{}", std::string(40, '-'));
        }
    }
    file.close();

    std::println("The results have been saved to \"{}\".", resultPath.string());
}
