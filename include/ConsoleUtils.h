#pragma once

#include "CardFormatter.h"
#include <iostream>
#include <string>
#include <string_view>
#include <vector>





class ConsoleUtils
{
public:
    static void printAt(int x, int y, std::string_view text)
    {
        // ansi command moving cursor
        std::cout << "\033[" << y << ";" << x << "H" << text;
    }

    static std::vector<std::string> generateCardGraphic(const Card& card);
};