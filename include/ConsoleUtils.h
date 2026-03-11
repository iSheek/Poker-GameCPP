#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "CardFormatter.h"




class ConsoleUtils
{
public:
    static void printAt(int x, int y, const std::string& text)
    {
        // ansi command moving cursor
        std::cout << "\033[" << y << ";" << x << "H" << text;
    }

    static std::vector<std::string> generateCardGraphic(const Card& card);
};