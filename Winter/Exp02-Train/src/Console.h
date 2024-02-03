#pragma once
#include <iostream>

namespace Console
{
    inline void Clear()
    {
        system("cls");
    }

    inline void ClearBuffer(char end = '\n')
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), end);
    }

    inline void WaitForKey()
    {
        system("pause");
    }
}
