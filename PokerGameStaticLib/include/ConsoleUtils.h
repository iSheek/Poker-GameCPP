/**
 * @file ConsoleUtils.h
 * @brief File containing declaration of ConsoleUtils class
 */
#pragma once

#include "CardFormatter.h"
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

/**
 * @brief Class containing utility functions for console manipulation
 */
class ConsoleUtils
{
public:
    /**
     * @brief Prints text at specific console coordinates
     * @param x The x coordinate
     * @param y The y coordinate
     * @param text The text to print
     */
    static void printAt(int x, int y, std::string_view text)
    {
        // ansi command moving cursor
        std::cout << "\033[" << y << ";" << x << "H" << text;
    }

    /**
     * @brief Generates graphic representation of a card
     * @param card The card to generate graphic for
     * @return Vector of strings representing the card
     */
    static std::vector<std::string> generateCardGraphic(const Card& card);
};