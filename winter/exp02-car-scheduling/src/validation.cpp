#include <filesystem>
#include <format>
#include <fstream>
#include <print>
#include <numeric>
#include <vector>

#include "permutation.hpp"
#include "solution.hpp"
#include "stack.hpp"

struct TestObj
{
    int a = 0;
    int* arr = nullptr;

    TestObj(int aa) : a(aa), arr(new int[5])
    {
        std::println("TestObj constructed.");
    }
    TestObj(const TestObj& other) : a(other.a), arr(new int[5])
    {
        std::copy(other.arr, other.arr + 5, arr);
        std::println("TestObj copied.");
    }
    TestObj(TestObj&& other) noexcept : a(other.a), arr(other.arr)
    {
        other.arr = nullptr;
        std::println("TestObj moved.");
    }
    TestObj& operator=(const TestObj& other)
    {
        if (this != &other) {
            a = other.a;
            delete[] arr;
            arr = new int[5];
            std::copy(other.arr, other.arr + 5, arr);
            std::println("TestObj copy assigned.");
        }
        return *this;
    }
    TestObj& operator=(TestObj&& other) noexcept
    {
        if (this != &other) {
            a = other.a;
            delete[] arr;
            arr = other.arr;
            other.arr = nullptr;
            std::println("TestObj move assigned.");
        }
        return *this;
    }
    ~TestObj()
    {
        delete[] arr;
        std::println("TestObj of {} destroyed.", a);
    }
};

void runStackValidation()
{
    std::println("Construting an empty stack...");
    myds::Stack<TestObj> st;
    std::println("Capacity={}, size={}", st.getCapacity(), st.getSize());
    std::println("Is empty? {}", st.isEmpty());

    std::println("Push 1 TestObj into the stack (copy)...");
    TestObj obj(-5);
    st.push(obj);

    std::println("Copy construct the stack...");
    myds::Stack<TestObj> st2(st);
    std::println("Capacity={}, size={}", st2.getCapacity(), st2.getSize());

    std::println("Push 10 TestObj into the stack (move)...");
    for (int i = 0; i < 10; ++i) {
        st.push(TestObj(i));
        std::println("Capacity={}, size={}. Is full? {}", st.getCapacity(),
                     st.getSize(), st.isFull());
    }

    std::println("The top element is {}.", st.getTop().a);

    std::println("Pop 5 TestObj from the stack...");
    for (int i = 0; i < 5; ++i) {
        st.pop();
        std::println("Capacity={}, size={}", st.getCapacity(), st.getSize());
    }

    std::println("Destroy the stack...");
}

void runTask01_validation(int numOfCars)
{
    // inputOrder = 1, 2, 3, ..., numOfCars
    std::vector<int> inputOrder(numOfCars);
    std::iota(inputOrder.begin(), inputOrder.end(), 1);

    std::size_t numOfSuccessfulCases = 0;
    std::size_t successCntInTest = 0;
    std::size_t numOfFullPerms = 0;

    std::println();
    std::println("Step 1: Checking if the algorithm misses any successful cases.");
    {
        std::println("Calculating all possible stack output sequences...");
        std::vector<std::vector<int>> allPossibleOutputOrders;
        myalgorithm::generateAllStackOutput(inputOrder, allPossibleOutputOrders);
        numOfSuccessfulCases = allPossibleOutputOrders.size();
        std::println("Done.");

        std::println("Testing...");
        for (const auto& outputOrder : allPossibleOutputOrders) {
            bool success = runTask01(outputOrder, numOfCars, nullptr);
            if (!success) {
                std::print("Failed while testing the output sequence: ");
                for (int car : outputOrder) {
                    std::print("{} ", car);
                }
                std::println();
                std::println("Please fix the algorithm!");
                return;
            }
        }
        std::println("Passed (1/2).");
    }

    std::println();
    std::println("Step 2: Checking if the algorithm mistakely accepts some failed cases.");
    {
        std::println("Testing on full permutations...");

        std::filesystem::path resultPath = "output/task01_validation_result.txt";
        std::filesystem::create_directories(resultPath.parent_path());
        std::ofstream file(resultPath);

        auto& perm = inputOrder;
        do {
            bool success = runTask01(perm, numOfCars, nullptr);
            if (success) {
                ++successCntInTest;
                std::print(file, "[{}] ", successCntInTest);
                for (int car : perm) {
                    std::print(file, "{} ", car);
                }
                std::println(file);
                file.flush();
            }
            ++numOfFullPerms;
        } while (std::ranges::next_permutation(perm).found);

        file.close();

        std::println(
            "All cases accepted by the algorithm have been saved to {}.",
            resultPath.string());

        if (successCntInTest != numOfSuccessfulCases) {
            std::println("Failed. Please fix the algorithm!");
            return;
        }
        std::println("Passed (2/2).");
    }

    std::println();
    std::println("Congratulations! All {}/{} successful cases are accepted by your algorithm! Good job!",
                 successCntInTest, numOfFullPerms);
}

void runTask02_validation(int numOfCars)
{
    // outOrder = 1, 2, 3, ..., numOfCars
    std::vector<int> outputOrder(numOfCars);
    std::iota(outputOrder.begin(), outputOrder.end(), 1);

    std::size_t numOfSuccessfulCases = 0;
    std::size_t successCntInTest = 0;
    std::size_t numOfFullPerms = 0;

    std::println();
    std::println("Step 1: Checking if the algorithm misses any successful outputs.");
    {
        std::vector<std::vector<int>> allPossibleInputOrders;
        std::vector<int> revOutOrder(outputOrder);
        std::ranges::reverse(revOutOrder);
        myalgorithm::generateAllStackOutput(revOutOrder, allPossibleInputOrders);
        for (auto& inOrder : allPossibleInputOrders) {
            std::ranges::reverse(inOrder);
        }
        numOfSuccessfulCases = allPossibleInputOrders.size();
        std::println("Done.");

        std::println("Testing...");
        for (const auto& inputOrder : allPossibleInputOrders) {
            bool success = runTask02(inputOrder, numOfCars, nullptr);
            if (!success) {
                std::print("Failed while testing the input sequence: ");
                for (int car : inputOrder) {
                    std::print("{} ", car);
                }
                std::println();
                std::println("Please fix the algorithm!");
                return;
            }
        }
        std::println("Passed (1/2).");
    }

    std::println();
    std::println("Step 2: Checking if the algorithm mistakely accepts some "
                 "failed outputs.");
    {
        std::println("Testing on full permutations...");

        std::filesystem::path resultPath = "output/task02_validation_result.txt";
        std::filesystem::create_directories(resultPath.parent_path());
        std::ofstream f(resultPath);

        auto& perm = outputOrder;
        do {
            bool success = runTask02(perm, numOfCars, nullptr);
            if (success) {
                ++successCntInTest;
                std::print(f, "[{}] ", successCntInTest);
                for (int car : perm) {
                    std::print(f, "{} ", car);
                }
                std::println(f);
                f.flush();
            }
            ++numOfFullPerms;
        } while (std::ranges::next_permutation(perm).found);

        f.close();

        std::println(
            "All cases accepted by the algorithm have been saved to {}.",
            resultPath.string());

        if (successCntInTest != numOfSuccessfulCases) {
            std::println("Failed. Please fix the algorithm!");
            return;
        }
        std::println("Passed (2/2).");
    }

    std::println();
    std::println("Congratulations! All {}/{} successful cases are "
                 "accepted by your algorithm! Good job!",
                 successCntInTest, numOfFullPerms);
}