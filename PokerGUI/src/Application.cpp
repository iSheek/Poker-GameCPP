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
    resourceManager.loadTexture(TextureNames::CARDS_ATLAS, FileNames::CARDS_ATLAS_FILE);
    resourceManager.loadTexture(TextureNames::CHIP_TEXTURE, FileNames::CHIP_TEXTURE_FILE);
    lastTime = glfwGetTime();
}

void Application::startRenderLoop()
{
    // Our state
    bool show_demo_window = true;
    ImVec4 clear_color = ImVec4(0.207f, 0.395f, 0.3f, 1.00f);        // poker table color

    const Texture& pokerAtlas = resourceManager.getTextureRef(TextureNames::CARDS_ATLAS);
    const Texture& chipTex = resourceManager.getTextureRef(TextureNames::CHIP_TEXTURE);

    glm::vec2 testPosition = glm::vec2(320.0f, 180.0f);
    glm::vec2 testSize = glm::vec2(64.0f, 64.0f);
    float testRotation = 0.0f;
    glm::vec4 testUVRect = glm::vec4(0.0f, 192.0f / 256.0f, 64.0f / 896.0f, 64.0f / 256.0f);
    glm::vec4 testMultiplier = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    bool flagTest = false;


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
        //if (show_demo_window)
        //    ImGui::ShowDemoWindow(&show_demo_window);

        ImGui::Begin("TESTSCREEN");
        ImGui::SliderFloat("Rotation", &testRotation, 0.0f, 300.0f);
        ImGui::SliderFloat2("Position", &testPosition.x, 0.0f, 1080.0f);
        ImGui::SliderFloat2("Size", &testSize.x, 0.0f, 620.0f);
        ImGui::SliderFloat4("UVRect", &testUVRect.x, 0.0f, 1000.0f);
        ImGui::SliderFloat4("Multiplier", &testMultiplier.x, 0.0f, 1.0f);
        ImGui::Checkbox("white exception", &flagTest);
        ImGui::End();

        int display_w, display_h;
        glfwGetFramebufferSize(appWindow.getWindowPtr(), &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        SpriteDrawData testData
        {
            .texture = chipTex,
            .position = testPosition + glm::vec2(60.0f, 0.0f),
            .size = glm::vec2(16.0f, 14.0f),
            .rotation = testRotation,
            .UVrect = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
            .multiplier = testMultiplier,
            .useWhiteException = flagTest
        };

        SpriteDrawData testData2
        {
            .texture = pokerAtlas,
            .position = testPosition,
            .size = testSize,
            .rotation = testRotation,
            .UVrect = testUVRect,
            .multiplier = testMultiplier,
            .useWhiteException = flagTest
        };

        SpriteDrawData testData2shadow
        {
            .texture = pokerAtlas,
            .position = testPosition - glm::vec2(2.0f, -2.0f),
            .size = testSize,
            .rotation = testRotation,
            .UVrect = testUVRect,
            .multiplier = glm::vec4(0.0f, 0.0f, 0.0f, 0.4f),
            .useWhiteException = flagTest
        };

        spriteRenderer.draw(testData);
        spriteRenderer.draw(testData2shadow);
        spriteRenderer.draw(testData2);


        // shadow test 

        imGuiLayer.renderImGui();

        glfwSwapBuffers(appWindow.getWindowPtr());
    }
}
