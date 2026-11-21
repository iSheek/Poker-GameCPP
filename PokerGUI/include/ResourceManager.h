#pragma once

/**
 * @file ResourceManager.h
 * @brief File containing declaration of ResourceManager class
 */

#include "Texture.h"
#include "ShaderProgram.h"

#include <filesystem>
#include <string>
#include <unordered_map>

/**
* @brief Class that manages all resources
* @pre There has to be existing OpenGL context
*/
class ResourceManager
{
private:
	std::filesystem::path resourcesPath{};									///< path to the res folder
																			
	std::unordered_map<std::string, ShaderProgram> shaderPrograms{};		///< map of all existing shaderPrograms
	std::unordered_map<std::string, Texture> textures{};					///< map of all existing textures

public:
	/**
	* @brief Main constructor of the class
	* @details It uses .exe directory to find res folder
	* @throws std::runtime_error when there's problem with finding .exe directory and when there isn't res folder
	*/
	ResourceManager();


	/**
	* @name Copying and moving
	* Class is the sole owner of the resources and copying would cause double remove
	*/
	///@{
	ResourceManager(const ResourceManager& other) = delete;
	ResourceManager(ResourceManager&& other) = delete;
	ResourceManager& operator=(const ResourceManager& other) = delete;
	ResourceManager& operator=(ResourceManager&& other) = delete;
	///@}

	/**
	* @brief Loads texture from the file and names it
	* @param name given name of the texture
	* @param fileName name of the file in textures directory
	* @throws std::runtime_error from Texture constructor if something goes wrong @see Texture::Texture
	*/
	void loadTexture(const std::string& name, const std::string& fileName);

	/**
	* @brief Loads the shader program from the files and names it
	* @param name given name of the shader program
	* @param vertexShaderFileName name of the file of vertex shader's source code in the shaders directory
	* @param fragmentShaderFileName name of the file of fragment shader's source code in the shaders directory
	* @throws std::runtime_error from ShaderProgram constructor if something goes wrong @see ShaderProgram::ShaderProgram
	*/
	void loadShaderProgram(const std::string& name, const std::string& vertexShaderFileName, const std::string& fragmentShaderFileName);

	/**
	* @brief Getter of the reference of shader program
	* @param name name of existing shader program
	* @throws std::logic_error if there's no given name in map
	* @return const reference to shader program
	*/
	const ShaderProgram& getShaderProgramRef(const std::string& name) const;

	/**
	* @brief Getter of the reference of texture
	* @param name name of existing texture
	* @throws std::logic_error if there's no given name in map
	* @return const reference to texture
	*/
	const Texture& getTextureRef(const std::string& name) const;


};