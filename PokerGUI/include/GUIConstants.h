#pragma once

/**
 * @file GUIConstants.h
 * @brief File containing constant values for GUI
 */

namespace GUIConstants
{
	using Cstr = const char*;

	/**
	* @brief names for ResourceManager
	*/
	namespace ShaderProgramNames {
		inline constexpr Cstr SPRITE_PROGRAM { "sprite" };
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
}