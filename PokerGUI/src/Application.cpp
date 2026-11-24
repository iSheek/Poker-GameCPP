/**
 * @file Application.cpp
 * @brief File containing definition of Application class' methods
 */

#include "Application.h"
#include "GUIConstants.h"

using namespace GUIConstants;

void Application::processInput()
{   // TODO COMMA CLOSES WINDOW ONLY FOR TESTING
    if (glfwGetKey(appWindow.getWindowPtr(), GLFW_KEY_COMMA) == GLFW_PRESS)
        glfwSetWindowShouldClose(appWindow.getWindowPtr(), true);
}

Application::Application() 
    : spriteRenderer(resourceManager.loadShaderProgram(ShaderProgramNames::SPRITE_PROGRAM, FileNames::SPRITE_VERTEX_SHADER, FileNames::SPRITE_FRAGMENT_SHADER))
{
    lastTime = glfwGetTime();
}

void Application::startRenderLoop()
{
    // Our state
    bool show_demo_window = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    // render loop
    // -----------
    while (!glfwWindowShouldClose(appWindow.getWindowPtr()))
    {
        double nowTime{ glfwGetTime() };
        deltaTime = nowTime - lastTime;
        lastTime = nowTime;

        glfwPollEvents();

        imGuiLayer.startImGuiNewFrames();

        // input
        // -----
        processInput();

        // TODO DELETE THIS AFTER CREATING OWN INTERFACE
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);




        int display_w, display_h;
        glfwGetFramebufferSize(appWindow.getWindowPtr(), &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        imGuiLayer.renderImGui();

        glfwSwapBuffers(appWindow.getWindowPtr());
    }
}
