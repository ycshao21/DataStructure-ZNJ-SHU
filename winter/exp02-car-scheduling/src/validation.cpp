#include <algorithm>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
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
        std::cout << "TestObj constructed.\n";
    }
    TestObj(const TestObj& other) : a(other.a), arr(new int[5])
    {
        std::copy(other.arr, other.arr + 5, arr);
        std::cout << "TestObj copied.\n";
    }
    TestObj(TestObj&& other) noexcept : a(other.a), arr(other.arr)
    {
        other.arr = nullptr;
        std::cout << "TestObj moved.\n";
    }
    TestObj& operator=(const TestObj& other)
    {
        if (this != &other) {
            a = other.a;
            delete[] arr;
            arr = new int[5];
            std::copy(other.arr, other.arr + 5, arr);
            std::cout << "TestObj copy assigned.\n";
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
            std::cout << "TestObj move assigned.\n";
        }
        return *this;
    }
    ~TestObj()
    {
        delete[] arr;
        std::cout << "TestObj of " << a << " destroyed.\n";
    }
};

void stack_validation()
{
    std::cout << "Construct an empty stack...\n";
    myds::Stack<TestObj> st;
    std::cout << std::format("Capacity={}, size={}\n", st.getCapacity(), st.getSize());
    std::cout << std::format("Is empty? {}\n", st.isEmpty());

    std::cout << "Push 1 TestObj into the stack (copy)...\n";
    TestObj obj(-5);
    st.push(obj);

    std::cout << "Copy construct the stack...\n";
    myds::Stack<TestObj> st2(st);
    std::cout << std::format("Capacity={}, size={}\n", st2.getCapacity(), st2.getSize());

    std::cout << "Push 10 TestObj into the stack (move)...\n";
    for (int i = 0; i < 10; ++i) {
        st.push(TestObj(i));
        std::cout << std::format("Capacity={}, size={}. Is full? {}\n", st.getCapacity(),
                                 st.getSize(), st.isFull());
    }

    std::cout << std::format("The top element is {}.\n", st.getTop().a);

    std::cout << "Pop 5 TestObj from the stack...\n";
    for (int i = 0; i < 5; ++i) {
        st.pop();
        std::cout << std::format("Capacity={}, size={}\n", st.getCapacity(),
                                 st.getSize());
    }

    std::cout << "Destroy the stack...\n";
}

void task01_validation(int numOfCars)
{
    // inputOrder = 1, 2, 3, ..., numOfCars
    std::vector<int> inputOrder(numOfCars);
    std::iota(inputOrder.begin(), inputOrder.end(), 1);

    std::size_t numOfSuccessfulCases = 0;
    std::size_t successCntInTest = 0;
    std::size_t numOfFullPerms = 0;

    std::cout << "Step 1: Checking if the algorithm misses any successful cases.\n";
    {
        std::cout << "Calculating all possible stack output sequences...";
        std::vector<std::vector<int>> allPossibleOutputOrders;
        algorithm::generateAllStackOutput(inputOrder, allPossibleOutputOrders);
        numOfSuccessfulCases = allPossibleOutputOrders.size();

        std::cout << "done.\n";

        std::cout << "Testing...\n";
        for (const auto& outputOrder : allPossibleOutputOrders) {
            bool success = task01(outputOrder, numOfCars, nullptr);
            if (!success) {
                std::cout << "Failed while testing the output sequence: ";
                for (int car : outputOrder) {
                    std::cout << car << ' ';
                }
                std::cout << "\nPlease fix the algorithm!\n";
                return;
            }
        }
        std::cout << "Passed (1/2).\n";
    }

    std::cout << "Step 2: Checking if the algorithm mistakely accepts some "
                 "failed cases.\n";
    {
        std::cout << "Testing on full permutations...\n";

        std::filesystem::path resultPath = "output/task01_validation_result.txt";
        std::filesystem::create_directories(resultPath.parent_path());
        std::ofstream f(resultPath);

        auto& perm = inputOrder;
        do {
            bool success = task01(perm, numOfCars, nullptr);
            if (success) {
                ++successCntInTest;
                f << std::format("[{}] ", successCntInTest);
                for (int car : perm) {
                    f << std::format("{} ", car);
                }
                f << '\n' << std::flush;
            }
            ++numOfFullPerms;
        } while (std::ranges::next_permutation(perm).found);

        f.close();

        std::cout << std::format(
            "All cases accepted by the algorithm have been saved to {}.\n",
            resultPath.string());

        if (successCntInTest != numOfSuccessfulCases) {
            std::cout << "Failed. Please fix the algorithm!\n";
            return;
        }
        std::cout << "Passed (2/2).\n";
    }

    std::cout << std::format("Congratulations! All {}/{} successful cases are "
                             "accepted by your algorithm! Good job!\n",
                             successCntInTest, numOfFullPerms);
}

void task02_validation(int numOfCars)
{
    // outOrder = 1, 2, 3, ..., numOfCars
    std::vector<int> outputOrder(numOfCars);
    std::iota(outputOrder.begin(), outputOrder.end(), 1);

    std::size_t numOfSuccessfulCases = 0;
    std::size_t successCntInTest = 0;
    std::size_t numOfFullPerms = 0;

    std::cout << "Step 1: Checking if the algorithm misses any successful outputs.\n";
    {
        std::vector<std::vector<int>> allPossibleInputOrders;
        std::vector<int> revOutOrder(outputOrder);
        std::ranges::reverse(revOutOrder);
        algorithm::generateAllStackOutput(revOutOrder, allPossibleInputOrders);
        for (auto& inOrder : allPossibleInputOrders) {
            std::ranges::reverse(inOrder);
        }
        numOfSuccessfulCases = allPossibleInputOrders.size();
        std::cout << "done.\n";

        std::cout << "Testing...\n";
        for (const auto& inputOrder : allPossibleInputOrders) {
            bool success = task02(inputOrder, numOfCars, nullptr);
            if (!success) {
                std::cout << "Failed while testing the input sequence: ";
                for (int car : inputOrder) {
                    std::cout << car << ' ';
                }
                std::cout << "\nPlease fix the algorithm!\n";
                return;
            }
        }
        std::cout << "Passed (1/2).\n";
    }

    std::cout << "Step 2: Checking if the algorithm mistakely accepts some "
                 "failed outputs.\n";
    {
        std::cout << "Testing on full permutations...\n";

        std::filesystem::path resultPath = "output/task02_validation_result.txt";
        std::filesystem::create_directories(resultPath.parent_path());
        std::ofstream f(resultPath);

        auto& perm = outputOrder;
        do {
            bool success = task02(perm, numOfCars, nullptr);
            if (success) {
                ++successCntInTest;
                f << std::format("[{}] ", successCntInTest);
                for (int car : perm) {
                    f << std::format("{} ", car);
                }
                f << '\n' << std::flush;
            }
            ++numOfFullPerms;
        } while (std::ranges::next_permutation(perm).found);

        f.close();

        std::cout << std::format(
            "All cases accepted by the algorithm have been saved to {}.\n",
            resultPath.string());

        if (successCntInTest != numOfSuccessfulCases) {
            std::cout << "Failed. Please fix the algorithm!\n";
            return;
        }
        std::cout << "Passed (2/2).\n";
    }

    std::cout << std::format("Congratulations! All {}/{} successful cases are "
                             "accepted by your algorithm! Good job!\n",
                             successCntInTest, numOfFullPerms);
}