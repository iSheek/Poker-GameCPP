/**
 * @file ImGuiLayer.cpp
 * @brief File containing definition of ImGuiLayer class' functions
 */

#include "ImGuiLayer.h"

constexpr const char* GLSL_VERSION = "#version 330 core";

ImGuiLayer::ImGuiLayer(const AppWindow& appWindow)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); //(void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

    // Setup Dear ImGui style
    ImGuiStyle& style = ImGui::GetStyle();
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();
    //style.FontSizeBase = 16.0f;           // Default to 13.0f when unspecified, which allows crisp legacy font for non-4K screens.
    style.FrameRounding = 3.0f;
    style.GrabRounding = 3.0f;


    // Setup scaling
    style.ScaleAllSizes(appWindow.getMainScale());        // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
    style.FontScaleDpi = appWindow.getMainScale();        // Set initial font scale. (in docking branch: using io.ConfigDpiScaleFonts=true automatically overrides this for every window depending on the current monitor)

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(appWindow.getWindowPtr(), true);
    ImGui_ImplOpenGL3_Init(GLSL_VERSION);
}
