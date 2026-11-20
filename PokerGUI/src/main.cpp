/**
 * @file main.cpp
 * @brief main file
 */

#include "Application.h"

#include <exception>
#include <iostream>

int main()
{
    try {
        Application app{};

        app.startRenderLoop();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << "\n";
        return -1;
    }
    return 0;
}
