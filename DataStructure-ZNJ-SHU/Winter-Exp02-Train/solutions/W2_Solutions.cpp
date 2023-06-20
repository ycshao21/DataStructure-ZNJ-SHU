#include<sstream>
#include<vector>
#include"../data_structure/ArrayStack.h"

namespace W2
{
    bool Question1(const std::vector<int>& outputOrder, int numOfCars, std::ostream* out) {
        std::ostringstream process;
        ArrayStack<int> holdingTrack(numOfCars - 1);
        bool success = true;
        int checkingCar = 1;
        for (int i = 0; i < numOfCars; ++i) {
            if (!holdingTrack.empty() && holdingTrack.top() == outputOrder[i]) {
                process << "| -> " << outputOrder[i] << "号车厢从辅助轨道驶入主轨道右侧\n";
                holdingTrack.pop();
            } else {
                while (checkingCar < outputOrder[i]) {
                    process << "-> | " << checkingCar << "号车厢从主轨道左侧驶入辅助轨道\n";
                    holdingTrack.push(checkingCar);
                    ++checkingCar;
                }
                if (checkingCar == outputOrder[i]) {
                    process << "->-> " << outputOrder[i] << "号车厢从主轨道左侧驶入主轨道右侧\n";
                    ++checkingCar;
                } else {
                    success = false;
                    break;
                }
            }
        }
        if (success) {
            process << "调度完成！";
        } else {
            process.str("调度失败！");
        }

        if (out) {
            (*out) << process.str() << std::endl;
        }
        return success;
    }

    bool Question2(const std::vector<int>& inputOrder, int numOfCars, std::ostream* out) {
        std::ostringstream process;
        ArrayStack<int> holdingTrack(numOfCars);
        bool success = true;
        int nextCarToOutput = 1;
        for (int i = 0; i < numOfCars; ++i) {
            if (inputOrder[i] == nextCarToOutput) {
                process << "->-> " << inputOrder[i] << "号车厢从主轨道左侧驶入主轨道右侧\n";
                ++nextCarToOutput;
                while (!holdingTrack.empty() && holdingTrack.top() == nextCarToOutput) {
                    process << "| -> " << holdingTrack.top() << "号车厢从辅助轨道驶入主轨道右侧\n";
                    holdingTrack.pop();
                    ++nextCarToOutput;
                }
            } else {
                if (!holdingTrack.empty() && holdingTrack.top() < inputOrder[i]) {
                    success = false;
                    break;
                }
                holdingTrack.push(inputOrder[i]);
                process << "-> | " << inputOrder[i] << "号车厢从主轨道左侧驶入辅助轨道\n";
            }
        }
        if (success) {
            process << "调度完成！";
        } else {
            process.str("调度失败！");
        }

        if (out) {
            (*out) << process.str() << std::endl;
        }
        return success;
    }
}