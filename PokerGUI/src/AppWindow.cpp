/**
 * @file AppWindow.cpp
 * @brief File containing definition of AppWindow class' functions
 */

#include "AppWindow.h"
#include "GUIConstants.h"

#include <cstdio>
#include <stdexcept>

/**
* @brief Custom function for error callback from GLFW
*/
static void glfwErrorCallback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}


void AppWindow::initGLFW()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwSetErrorCallback(glfwErrorCallback);
    if (glfwInit() == GLFW_FALSE)
    {
        throw std::runtime_error("GLFW NOT INITIALIZED");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    using namespace GUIConstants::WindowSettings;
    // glfw window creation
    // --------------------
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, WINDOW_NAME, NULL, NULL);
    if (window == NULL)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    glfwGetMonitorContentScale(glfwGetPrimaryMonitor(), &mainScale, NULL);
}

void AppWindow::initGLAD()
{
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLAD");
    }
}
