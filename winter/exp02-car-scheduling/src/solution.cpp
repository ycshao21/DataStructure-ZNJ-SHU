#include <print>
#include <ostream>
#include <vector>

#include "stack.hpp"

bool runTask01(const std::vector<int>& outputOrder, int numOfCars, std::ostream* out)
{
    myds::Stack<int> holdingTrack(numOfCars - 1);
    int checkingCar = 1;

    for (int outputCar : outputOrder) {
        if (!holdingTrack.isEmpty() && holdingTrack.getTop() == outputCar) {
            if (out != nullptr) {
                std::println(*out, "| -> Car {} drives from holding track to the right.", outputCar);
            }
            holdingTrack.pop();
        } else {
            while (checkingCar < outputCar) {
                if (out != nullptr) {
                    std::println(*out, "-> | Car {} drives from the left to holding track.", checkingCar);
                }
                holdingTrack.push(checkingCar);
                ++checkingCar;
            }
            if (checkingCar == outputCar) {
                if (out != nullptr) {
                    std::println(*out, "->-> Car {} drives from the left to the right.", outputCar);
                }
                ++checkingCar;
            } else {
                if (out != nullptr) {
                    std::println(*out, "...");
                    std::println(*out, "ERROR: Failed to schedule cars!");
                }
                return false;
            }
        }
    }

    if (out != nullptr) {
        std::println(*out, "Succeeded.");
    }
    return true;
}

bool runTask02(const std::vector<int>& inputOrder, int numOfCars, std::ostream* out)
{
    myds::Stack<int> holdingTrack(numOfCars - 1);
    int nextCarToOutput = 1;

    for (int inputCar : inputOrder) {
        if (inputCar == nextCarToOutput) {
            if (out != nullptr) {
                std::println(*out, "->-> Car {} drives from the left to the right.", inputCar);
            }
            ++nextCarToOutput;
            while (!holdingTrack.isEmpty() && holdingTrack.getTop() == nextCarToOutput) {
                if (out != nullptr) {
                    std::println(*out, "| -> Car {} drives from holding track to the right.", holdingTrack.getTop());
                }
                holdingTrack.pop();
                ++nextCarToOutput;
            }
        } else {
            if (!holdingTrack.isEmpty() && holdingTrack.getTop() < inputCar) {
                if (out != nullptr) {
                    std::println(*out, "...");
                    std::println(*out, "ERROR: Failed to schedule cars!");
                }
                return false;
            }
            holdingTrack.push(inputCar);
            if (out != nullptr) {
                std::println(*out, "-> | Car {} drives from the left to holding track.", inputCar);
            }
        }
    }

    if (out != nullptr) {
        std::println(*out, "Succeeded.");
    }
    return true;
}