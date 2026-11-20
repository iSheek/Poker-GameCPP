#pragma once

/**
 * @file ImGuiLayer.h
 * @brief File containing declaration of ImGuiLayer class
 */

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "AppWindow.h"


 /**
 * @brief Class managing ImGui layer of the GUI
 *
 * @details This class is using RAII for creating context of ImGui and attaching it to GLFW and OpenGL
 */
class ImGuiLayer
{
public:
    /**
    * @brief Main constructor of the class
    * @param appWindow existing AppWindow object
    * @pre OpenGL context has to be current (glfwMakeContextCurrent) and GLAD has to be loaded - whole window has to be initialized and created
    */
    ImGuiLayer(const AppWindow& appWindow);                        
    
    /**
    * @name Copying and moving
    * Class is the sole owner of the resources and copying would cause double remove
    */
    ///@{
    ImGuiLayer(const ImGuiLayer& other) = delete;                  
    ImGuiLayer(ImGuiLayer&& other) = delete;                       
    ImGuiLayer& operator=(const ImGuiLayer& other) = delete;       
    ImGuiLayer& operator=(ImGuiLayer&& other) = delete;            
    ///@}

    /**
    * @brief Custom destructor of the class
    * @details It destroys ImGui backends and context in order: opengl backend -> glfw backend -> imgui context
    */
    ~ImGuiLayer()
    {
        // Cleanup
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    /**
    * @brief Method for preparing ImGui for frame
    * @details It has to be put before any OpenGL draw call
    */
    void startImGuiNewFrames()
    {
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    /**
    * @brief Method used for rendering ImGui layer
    * @details It has to be put at the end of the render loop (before swapping buffers)
    */
    void renderImGui()
    {
        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

};