#include <format>
#include <iostream>
#include <vector>

#include "stack.hpp"

bool runTask01(const std::vector<int>& outputOrder, int numOfCars, std::ostream* out)
{
    myds::Stack<int> holdingTrack(numOfCars - 1);
    int checkingCar = 1;

    for (int outputCar : outputOrder) {
        if (!holdingTrack.isEmpty() && holdingTrack.getTop() == outputCar) {
            if (out != nullptr) {
                (*out) << std::format(
                    "| -> Car {} drives from holding track to the right.\n", outputCar);
            }
            holdingTrack.pop();
        } else {
            while (checkingCar < outputCar) {
                if (out != nullptr) {
                    (*out) << std::format(
                        "-> | Car {} drives from the left to holding track.\n",
                        checkingCar);
                }
                holdingTrack.push(checkingCar);
                ++checkingCar;
            }
            if (checkingCar == outputCar) {
                if (out != nullptr) {
                    (*out) << std::format(
                        "->-> Car {} drives from the left to the right.\n", outputCar);
                }
                ++checkingCar;
            } else {
                if (out != nullptr) {
                    (*out) << "...\nERROR: Failed to schedule cars!\n";
                }
                return false;
            }
        }
    }

    if (out != nullptr) {
        (*out) << "Succeeded.\n";
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
                (*out) << std::format("->-> Car {} drives from the left to the right.\n",
                                      inputCar);
            }
            ++nextCarToOutput;
            while (!holdingTrack.isEmpty() && holdingTrack.getTop() == nextCarToOutput) {
                if (out != nullptr) {
                    (*out) << std::format(
                        "| -> Car {} drives from holding track to the right.\n",
                        holdingTrack.getTop());
                }
                holdingTrack.pop();
                ++nextCarToOutput;
            }
        } else {
            if (!holdingTrack.isEmpty() && holdingTrack.getTop() < inputCar) {
                if (out != nullptr) {
                    (*out) << "...\nERROR: Failed to schedule cars!\n";
                }
                return false;
            }
            holdingTrack.push(inputCar);
            if (out != nullptr) {
                (*out) << std::format(
                    "-> | Car {} drives from the left to holding track.\n", inputCar);
            }
        }
    }

    if (out != nullptr) {
        (*out) << "Succeeded.\n";
    }
    return true;
}