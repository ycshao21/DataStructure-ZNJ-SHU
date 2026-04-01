#include <array>
#include <filesystem>
#include <print>
#include <unordered_set>
#include <vector>

#include "utils/console.hpp"

#include "solution.hpp"
#include "stack.hpp"
#include "validation.hpp"

static int inputNumOfCars()
{
    std::print("Please input the number of cars: ");
    int numOfCars;
    while (true) {
        std::cin >> numOfCars;
        bool validInput = !std::cin.fail() && numOfCars >= 1;
        utils::clearBuffer();
        if (validInput) {
            break;
        }
        std::print("Invalid input! Please re-input the number of cars: ");
    }
    return numOfCars;
}

static int inputNumOfCarsLimited()
{
    constexpr int maxNumOfCars = 11;
    std::print("Please input the number of cars (no more than {}): ", maxNumOfCars);
    int numOfCars;
    while (true) {
        std::cin >> numOfCars;
        bool validInput = !std::cin.fail() && numOfCars >= 1 && numOfCars <= maxNumOfCars;
        utils::clearBuffer();
        if (validInput) {
            break;
        }
        std::print("Invalid input! Please re-input the number of cars (no more than {}): ", maxNumOfCars);
    }
    return numOfCars;
}

static void inputOrderOfCars(std::vector<int>& order, int numOfCars,
                           const std::string& orderType)
{
    std::print("Please input the {} order of cars: ", orderType);

    bool validInput = false;
    while (true) {
        std::unordered_set<int> check;
        for (int& car : order) {
            std::cin >> car;
            validInput = !std::cin.fail() && car >= 1 && car <= numOfCars &&
                         check.find(car) == check.end();
            if (!validInput) {
                break;
            }
            check.emplace(car);
        }

        utils::clearBuffer();
        if (validInput) {
            break;
        }
        std::print("Invalid input! Please re-input the {} order of cars: ", orderType);
    }
}

static void exp02_carScheduling()
{
    utils::Menu menu("Exp02 - Car Scheduling");

    menu.addItem("Task 1", []() {
        int numOfCars = inputNumOfCars();
        std::vector<int> outOrder(numOfCars);
        inputOrderOfCars(outOrder, numOfCars, "output");
        runTask01(outOrder, numOfCars, &std::cout);
    });

    menu.addItem("Task 2", []() {
        int numOfCars = inputNumOfCars();
        std::vector<int> inputOrder(numOfCars);
        inputOrderOfCars(inputOrder, numOfCars, "input");
        runTask02(inputOrder, numOfCars, &std::cout);
    });

    menu.addItem("Stack Validation", []() {
        runStackValidation();
    });

    menu.addItem("Task 1 Validation", []() {
        int numOfCars = inputNumOfCarsLimited();
        runTask01_validation(numOfCars);
    });

    menu.addItem("Task 2 Validation", []() {
        int numOfCars = inputNumOfCarsLimited();
        runTask02_validation(numOfCars);
    });

    menu.run();
}

int main()
{
    std::filesystem::current_path(EXPERIMENT_WORKING_DIR);
    exp02_carScheduling();
}