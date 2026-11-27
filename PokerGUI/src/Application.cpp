/**
 * @file Application.cpp
 * @brief File containing definition of Application class' methods
 */

#include "Application.h"
#include "GUIConstants.h"

#include "SceneObject.h"
#include "ChipStack.h"
#include "CardObject.h"

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
    resourceManager.loadTexture(TextureNames::CARD_FRAME, FileNames::CARD_FRAME_TEXTURE_FILE);
    lastTime = glfwGetTime();
}

void Application::startRenderLoop()
{
    // Our state
    bool show_demo_window = true;
    ImVec4 clear_color = TABLE_COLOR;        // poker table color

    const Texture& pokerAtlas = resourceManager.getTextureRef(TextureNames::CARDS_ATLAS);
    const Texture& chipTex = resourceManager.getTextureRef(TextureNames::CHIP_TEXTURE);

    glm::vec2 testPosition = glm::vec2(320.0f, 180.0f);
    glm::vec2 testSize = glm::vec2(64.0f, 64.0f);
    float testRotation = 0.0f;


    const Texture& frame = resourceManager.getTextureRef(TextureNames::CARD_FRAME);
    std::vector<SpriteDrawData> drawDatas{};


    SpriteDrawData testChip
    {
        .texture = chipTex,
        .position = glm::vec2(150.0f, 120.0f),
        .size = glm::vec2(16.0f, 14.0f),
        .rotation = testRotation,
        .UVrect = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)
    };

    SpriteDrawData testCard
    {
        .texture = pokerAtlas,
        .position = testPosition,
        .size = testSize,
        .rotation = testRotation
    };

    int rank{1};
    int color{ 1 };
    bool isHidden{ false };
    bool isHighlighted{ false };
    int amount{ 1000 };

    ChipStack testChipStack{ testChip, 5000 };
    CardObject testCardObject{ testCard, Card{ CardSuit::HEARTS, CardRank::ACE }, frame };

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
        ImGui::SliderInt("Rank", &rank, 1, 13);
        ImGui::SliderInt("Color", &color, 1, 4);
        ImGui::Checkbox("isHighlighted", &isHighlighted);
        ImGui::Checkbox("isHidden", &isHidden);
        ImGui::SliderInt("Amount", &amount, 0, 6000);
        ImGui::End();

        int display_w, display_h;
        glfwGetFramebufferSize(appWindow.getWindowPtr(), &display_w, &display_h);
        customFramebuffer.drawToFramebuffer();
        //glViewport(0, 0, display_w, display_h);
        //glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        //glClear(GL_COLOR_BUFFER_BIT);

        testCardObject.setCard(Card{ static_cast<CardSuit>(color), static_cast<CardRank>(rank) });
        testCardObject.setIsHidden(isHidden);
        testCardObject.setIsHighlighted(isHighlighted);

        testChipStack.setAmount(amount);

        drawDatas.clear();
        testChipStack.appendSprites(drawDatas);
        testCardObject.appendSprites(drawDatas);

        for (const auto& d : drawDatas)
        {
            spriteRenderer.draw(d);
        }

        customFramebuffer.showInWindow(display_w, display_h);

        imGuiLayer.renderImGui();

        glfwSwapBuffers(appWindow.getWindowPtr());
    }
}
