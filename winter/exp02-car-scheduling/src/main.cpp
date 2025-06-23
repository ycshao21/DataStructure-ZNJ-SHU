#include <array>
#include <filesystem>
#include <format>
#include <iostream>
#include <unordered_set>
#include <vector>

#include "utils/console.hpp"

#include "solution.hpp"
#include "stack.hpp"
#include "validation.hpp"

static int getNumOfCars()
{
    std::cout << "Please input the number of cars: ";

    int numOfCars;
    while (true) {
        std::cin >> numOfCars;
        bool validInput = !std::cin.fail() && numOfCars >= 1;
        utils::clearBuffer();
        if (validInput) {
            break;
        }
        std::cout << "Invalid input! Please re-input the number of cars: ";
    }

    return numOfCars;
}

static void getOrderOfCars(std::vector<int>& order, int numOfCars,
                           const std::string& orderType)
{
    std::cout << std::format("Please input the {} order of cars: ", orderType);

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
        std::cout << std::format("Invalid input! Please re-input the {} order of cars: ",
                                 orderType);
    }
}

static void exp02_carScheduling()
{
    const std::array<std::string, 6> menu = {
        "Task 1", "Task 2", "Stack Validation", "Task 1 Validation", "Task 2 Validation",
        "Exit"};

    while (true) {
        std::cout << "Exp02 - Car Scheduling\n";

        for (std::size_t i = 0; i < menu.size(); ++i) {
            std::cout << std::format("[{}] {}\n", i + 1, menu[i]);
        }

        std::size_t choice = utils::getChoice(menu.size());
        if (choice == menu.size()) {
            return;
        }

        std::cout << std::format("\n[{}]\n", menu[choice - 1]);

        if (choice == 1) {
            int numOfCars = getNumOfCars();
            std::vector<int> outOrder(numOfCars);
            getOrderOfCars(outOrder, numOfCars, "output");
            task01(outOrder, numOfCars, &std::cout);
        } else if (choice == 2) {
            int numOfCars = getNumOfCars();
            std::vector<int> inputOrder(numOfCars);
            getOrderOfCars(inputOrder, numOfCars, "input");
            task02(inputOrder, numOfCars, &std::cout);
        } else if (choice == 3) {
            stack_validation();
        } else if (choice == 4) {
            int numOfCars = getNumOfCars();
            task01_validation(numOfCars);
        } else if (choice == 5) {
            int numOfCars = getNumOfCars();
            task02_validation(numOfCars);
        }

        std::cout << '\n' << std::flush;
    }
}

int main()
{
    std::filesystem::current_path(EXPERIMENT_WORKING_DIR);
    exp02_carScheduling();
}