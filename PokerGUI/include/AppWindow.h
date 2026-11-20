#pragma once

/**
 * @file AppWindow.h
 * @brief File containing declaration of AppWindow class
 */

#include <glad/glad.h>
#include <GLFW/glfw3.h>


/**
* @brief Class managing app's window
* 
* @details It uses GLFW for creating window and initializes GLAD context
*/
class AppWindow
{
private:
	GLFWwindow* window{};       ///< raw pointer to GLFW window
    float mainScale{};          ///< content scale of the monitor

    /**
    * @brief Method for initializing GLFW
    */
    void initGLFW();            
    
    /**
    * @brief Method for initializing GLAD
    */
    void initGLAD();            
public:
    /**
    * @brief Main constructor that initializes everything
    * @details It first initializes GLFW context and creates window, after that it initializes GLAD
    * @throws std::runtime_error if there's fail in initializing GLFW, initializing GLAD or creating a window
    */
	AppWindow()
	{
        initGLFW();
        initGLAD();
	}

    /**
    * @brief Custom destructor of the class
    * @details It destroys first the window and after that other GLFW resources
    */
    ~AppWindow()
    {
        glfwDestroyWindow(window);
        // glfw: terminate, clearing all previously allocated GLFW resources.
        // ------------------------------------------------------------------
        glfwTerminate();
    }

    /**
    * @name Copying and moving
    * Class is the sole owner of the resources and copying would cause double remove
    */
    ///@{
    AppWindow(const AppWindow& other) = delete;
    AppWindow(AppWindow&& other) = delete;
    AppWindow& operator=(const AppWindow& other) = delete;
    AppWindow& operator=(AppWindow&& other) = delete;
    ///@}

    /**
    * @brief Getter of GLFWwindow pointer
    * @return Raw pointer of GLFWwindow
    */
    GLFWwindow* getWindowPtr() const
    {
        return window;
    }

    /**
    * @brief Getter of monitor's content scale
    * @return Monitor's content scale as float
    */
    float getMainScale() const
    {
        return mainScale;
    }

};