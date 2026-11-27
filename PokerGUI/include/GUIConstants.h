#pragma once

/**
 * @file GUIConstants.h
 * @brief File containing constant values for GUI
 */

#include <glm/glm.hpp>
#include <imgui.h>
#include <array>

namespace GUIConstants
{
	using Cstr = const char*;

	inline constexpr ImVec4 TABLE_COLOR{ ImVec4(0.207f, 0.395f, 0.3f, 1.00f) };

	/**
	* @brief shader names for ResourceManager
	*/
	namespace ShaderProgramNames {
		inline constexpr Cstr SPRITE_PROGRAM { "sprite" };
	}

	/**
	* @brief texture names for ResourceManager
	*/
	namespace TextureNames {
		inline constexpr Cstr CARDS_ATLAS{ "pokeratlas" };
		inline constexpr Cstr CHIP_TEXTURE{ "chip" };
		inline constexpr Cstr CARD_FRAME{ "cardframe" };
	}

	/**
	* @brief uniform names in shaders
	*/
	namespace UniformNames {
		inline constexpr Cstr MODEL_MATRIX_NAME{ "model" };
		inline constexpr Cstr PROJECTION_MATRIX_NAME{ "projection" };
		inline constexpr Cstr TEXTURE_NAME_IN_SHADER{ "texture1" };
		inline constexpr Cstr MULTIPLIER_NAME_IN_SHADER{ "multiplier" };
		inline constexpr Cstr UVRECT_NAME_IN_SHADER{ "uvrect" };
		inline constexpr Cstr B_WHITE_EXCEPTION_IN_SHADER{ "whiteException" };
	}

	/**
	* @brief target resolution of graphics
	*/
	namespace VirtualResolution
	{
		// 640x360
		inline constexpr float left{ 0.0f };
		inline constexpr float right{ 640.f };
		inline constexpr float bottom{ 0.0f };
		inline constexpr float up{ 360.0f };

		inline constexpr int WIDTH{ static_cast<int>(right) };
		inline constexpr int HEIGHT{ static_cast<int>(up) };
	};

	/**
	* @brief names of folders
	*/
	namespace FolderNames
	{
		inline constexpr Cstr RESOURCES_FOLDER_NAME{ "res" };
		inline constexpr Cstr TEXTURES_FOLDER_NAME{ "textures" };
		inline constexpr Cstr SHADERS_FOLDER_NAME{ "shaders" };
	}

	/**
	* @brief names of files
	*/
	namespace FileNames {
		inline constexpr Cstr SPRITE_VERTEX_SHADER{ "vsprite.shader" };
		inline constexpr Cstr SPRITE_FRAGMENT_SHADER{ "fsprite.shader" };

		inline constexpr Cstr CARDS_ATLAS_FILE{ "cardsatlas.png" };
		inline constexpr Cstr CHIP_TEXTURE_FILE{ "chipsprite.png" };
		inline constexpr Cstr CARD_FRAME_TEXTURE_FILE{ "cardframe.png" };
	}

	/**
	* @brief settings for GLFW
	*/
	namespace WindowSettings
	{
		inline constexpr unsigned int SCR_WIDTH = 1280;
		inline constexpr unsigned int SCR_HEIGHT = 720;
		inline constexpr Cstr WINDOW_NAME = "PokerGame";
	}

	namespace SpriteConstants
	{
		inline constexpr float SHADOW_X_OFFSET{ 2.0f };
		inline constexpr float SHADOW_Y_OFFSET{ -2.0f };
		inline constexpr glm::vec4 SHADOW_MULTIPLIER{0.0f, 0.0f, 0.0f, 0.4f};

		inline constexpr glm::vec4 FRAME_MULTIPLIER{ 0.824f, 0.684f, 0.215f, 0.8f}; // gold

		inline constexpr float CARD_CELL_WIDTH{ 64.0f };
		inline constexpr float CARD_CELL_HEIGHT{ 64.0f };

		inline constexpr int HEARTS_SUIT_ROW_IN_ATLAS{ 0 };
		inline constexpr int DIAMONDS_SUIT_ROW_IN_ATLAS{ 1 };
		inline constexpr int CLUBS_SUIT_ROW_IN_ATLAS{ 2 };
		inline constexpr int SPADES_SUIT_ROW_IN_ATLAS{ 3 };
		inline constexpr int CARD_BACK_ROW_IN_ATLAS{ 1 };
		inline constexpr int CARD_BACK_COLUMN_IN_ATLAS{ 13 };


		inline constexpr int CHIP_WIDTH_FROM_TEXTURE{ 16 };
		inline constexpr int CHIP_HEIGHT_FROM_TEXTURE{ 14 };

		inline constexpr float CARDS_ATLAS_WIDTH{ 896.0f };
		inline constexpr float CARDS_ATLAS_HEIGHT{ 256.0f };


		inline constexpr int CARD_VISIBLE_WIDTH{42};
		inline constexpr int CARD_VISIBLE_HEIGHT{60};

	}

	namespace Chips{
		struct Denomination
		{
			int value{};
			glm::vec4 color{};
		};
		inline constexpr glm::vec4 WHITE{ glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) };
		inline constexpr glm::vec4 PURPLE{ glm::vec4(0.62f, 0.35f, 0.85f, 1.0f) };
		inline constexpr glm::vec4 RED{ glm::vec4(0.90f, 0.20f, 0.22f, 1.0f) };
		inline constexpr glm::vec4 GREEN{ glm::vec4(0.25f, 0.75f, 0.35f, 1.0f) };
		inline constexpr glm::vec4 BLUE{ glm::vec4(0.22f, 0.45f, 0.90f, 1.0f) };
		inline constexpr glm::vec4 BLACK{ glm::vec4(0.22f, 0.22f, 0.25f, 1.0f) };

		inline constexpr std::array<Denomination, 6> DENOMINATIONS{
			Denomination{100, BLACK},	
			Denomination{50, BLUE},
			Denomination{20, GREEN},
			Denomination{10, RED},
			Denomination{5, PURPLE},
			Denomination{1, WHITE}
		};

		namespace {
			constexpr bool isSortedDescending(const std::array<Denomination, DENOMINATIONS.size()> denominations)
			{
				for (size_t i{ 1 }; i < denominations.size(); ++i)
				{
					if (denominations[i - 1].value > denominations[i].value) continue;
					return false;
				}
				return true;
			}
			static_assert(isSortedDescending(DENOMINATIONS));
		}

		inline constexpr int STACK_STEP{ 2 };
		inline constexpr int MAX_CHIPS_IN_COLUMN{ 10 };
		inline constexpr int COLUMN_GAP{ 2 };
		inline constexpr int FRONT_ROW_PIXEL_OFFSET{ 6 };

		inline constexpr int FRONT_COLUMN_MAX_COUNT{ 2 };
		inline constexpr int BACK_COLUMN_MAX_COUNT{ 3 };

		inline constexpr int MAX_CHIPS_PER_PLAYER{ (FRONT_COLUMN_MAX_COUNT + BACK_COLUMN_MAX_COUNT) * MAX_CHIPS_IN_COLUMN };
	}
}