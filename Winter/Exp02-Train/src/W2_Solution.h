#pragma once
#include<iostream>
#include<vector>

namespace Winter02
{
    bool Task01(const std::vector<int>& outputOrder, int numOfCars, std::ostream* out = &std::cout);
    bool Task02(const std::vector<int>& inputOrder, int numOfCars, std::ostream* out = &std::cout);

    void Task01_Validation(int numOfCars);
    void Task02_Validation(int numOfCars);
}
