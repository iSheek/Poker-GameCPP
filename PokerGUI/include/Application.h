#pragma once

/**
 * @file Application.h
 * @brief File containing declaration of Application class
 */

#include "AppWindow.h"
#include "ImGuiLayer.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "Framebuffer.h"

 /**
 * @brief Class managing whole application
 *
 */
class Application
{
private:
    // first AppWindow and second ImGuiLayer so when they're destroyed, ImGuiLayer will be destroyed before object managing the window
    AppWindow appWindow{};                  ///< object managing the window
    ImGuiLayer imGuiLayer{ appWindow };     ///< object managing ImGuiLayer
    Framebuffer customFramebuffer{};        ///< object managing custom framebuffer that puts image from virtual resolution into window's resolution
    ResourceManager resourceManager{};      ///< object managing resources - created after ImGuiLayer since OpenGL resources has to be destroyed before context is destroyed
    SpriteRenderer spriteRenderer;          ///< object responsible for drawing sprites, it has to be created after resourceManager since he needs exisiting ShaderProgram


    double deltaTime{};                     ///< time between frames so every movement will be tied to the time instead of frames
    double lastTime{};                      ///< time of the last frame


    /**
    * @brief Helper function that processes inputs
    */
    void processInput();


public:
    /**
    * @brief Main constructor of the class
    */
    Application();

    /**
    * @name Copying and moving
    * There should be only one instance of the class and fields are not copyable
    */
    ///@{
    Application(const Application& other) = delete;
    Application(Application&& other) = delete;
    Application& operator=(const Application& other) = delete;
    Application& operator=(Application&& other) = delete;
    ///@}

    // there's no custom destructor since class' fields are cleaned using RAII

    /**
    * @brief Method that starts the render loop
    */
    void startRenderLoop();
};