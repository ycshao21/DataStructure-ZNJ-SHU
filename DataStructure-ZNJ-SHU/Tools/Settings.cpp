#include <iostream>
#include <Windows.h>

void ShowCursor()
{
    HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    _CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(outputHandle, &cursorInfo);
    cursorInfo.bVisible = true;
    SetConsoleCursorInfo(outputHandle, &cursorInfo);
}

void HideCursor()
{
    HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    _CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(outputHandle, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(outputHandle, &cursorInfo);
}

/**
 * @brief Clear the input buffer.
 * @param end The end character of the input buffer.
*/
void ClearBuffer(char end)
{
    std::cin.clear();
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), end);
}