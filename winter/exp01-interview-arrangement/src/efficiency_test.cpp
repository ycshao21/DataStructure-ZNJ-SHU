#include <array>
#include <filesystem>
#include <fstream>

#include "utils/timer.hpp"

#include "solution.hpp"

void efficiencyTest()
{
    std::filesystem::path resultPath = "output/result.csv";
    if (!std::filesystem::exists(resultPath.parent_path())) {
        std::filesystem::create_directories(resultPath.parent_path());
    }
    std::ofstream resultFile(resultPath);
    resultFile << "N,K,M,Elapsed Time(s)\n" << std::flush;

    const std::array<std::size_t, 5> nList = {100, 1000, 10000, 100000, 1000000};
    const std::array<std::size_t, 4> kList = {2, 20, 200, 2000};
    const std::array<std::size_t, 4> mList = {3, 30, 300, 3000};

    for (std::size_t n : nList) {
        for (std::size_t i = 0; i < kList.size(); ++i) {
            std::size_t k = kList[i], m = mList[i];
            std::cout << std::format("N = {}, K = {}, M = {}\n", n, k, m);

            {
                utils::Timer timer;
                runTask01(n, k, m, nullptr);
                double elapsed = timer.elapsed();
                std::cout << std::format("Elapsed time: {} s\n", elapsed);
                resultFile << std::format("{},{},{},{}\n", n, k, m, elapsed)
                           << std::flush;
            }

            std::cout << std::format("{}\n", std::string(40, '-'));
        }
    }

    std::cout << std::format("The result has been saved to \"{}\".\n",
                             resultPath.string());
}
