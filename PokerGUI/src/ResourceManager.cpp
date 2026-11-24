/**
 * @file ResourceManager.cpp
 * @brief File containing definition of ResourceManager class' methods
 */


#include "ResourceManager.h"
#include "GUIConstants.h"

#include <whereami.h>

#include <cassert>
#include <filesystem>
#include <string>
#include <unordered_map>
#include <stdexcept>

using namespace GUIConstants::FolderNames;

ResourceManager::ResourceManager()
{
	int length = wai_getExecutablePath(NULL, 0, NULL);
	if (length < 0)
	{
		throw std::runtime_error("ERROR WITH FINDING PATH TO .EXE - NOPATH");
	}
	std::string path(length, '\0');
	int dirLength{};

	if (wai_getExecutablePath(path.data(), length, &dirLength) == -1)
	{
		throw std::runtime_error("ERROR WITH FINDING PATH TO .EXE");
	}

	path = path.substr(0, dirLength);
	std::filesystem::path realPath{ path };
	realPath /= RESOURCES_FOLDER_NAME;

	if (!std::filesystem::is_directory(realPath))
	{
		throw std::runtime_error("ERROR RES FOLDER NOT FOUND: " + realPath.string());
	}

	resourcesPath = realPath;

}

const Texture& ResourceManager::loadTexture(const std::string& name, const std::string& fileName)
{
	std::filesystem::path texturePath{ resourcesPath / TEXTURES_FOLDER_NAME / fileName };
	auto emplaced = textures.try_emplace(name, texturePath.string());
	assert(emplaced.second);					
	return emplaced.first->second;		// from iterator we gets both key and value (first is key, second is value)
}

const ShaderProgram& ResourceManager::loadShaderProgram(const std::string& name, const std::string& vertexShaderFileName, const std::string& fragmentShaderFileName)
{
	std::filesystem::path vertexPath{ resourcesPath / SHADERS_FOLDER_NAME / vertexShaderFileName };
	std::filesystem::path fragmentPath{ resourcesPath / SHADERS_FOLDER_NAME / fragmentShaderFileName };
	auto emplaced = shaderPrograms.try_emplace(name, vertexPath.string(), fragmentPath.string());
	assert(emplaced.second);
	return emplaced.first->second;	// from iterator we gets both key and value (first is key, second is value)
}

const ShaderProgram& ResourceManager::getShaderProgramRef(const std::string& name) const
{
	auto it = shaderPrograms.find(name);
	if (it == shaderPrograms.end())
	{
		assert(false);
		throw std::logic_error("ERROR NAME NOT FOUND IN SHADERPROGRAM MAP: " + name);
	}
	return it->second;
}

const Texture& ResourceManager::getTextureRef(const std::string& name) const
{
	auto it = textures.find(name);
	if (it == textures.end())
	{
		assert(false);
		throw std::logic_error("ERROR NAME NOT FOUND IN TEXTURE MAP: " + name);
	}
	return it->second;
}
