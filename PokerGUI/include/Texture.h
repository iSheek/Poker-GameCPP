#pragma once
/**
 * @file Texture.h
 * @brief File containing declaration of Texture class
 */

#include <string>

/**
* @brief Class representing texture
*/
class Texture
{
private:
	unsigned int id{};		///< id of the texture
	int width{};			///< width of the texture
	int height{};			///< height of the texture

public:
	/**
	* @brief Main constructor of the texture
	* @details It loads the texture and generate texture with parameters for pixel-art graphics
	* @param texturePath path to the texture file
	* @throws std::runtime_error if there is a problem with texture file
	*/
	Texture(const std::string& texturePath);

	/**
	* @brief Custom destructor of the texture
	* @details It calls OpenGL function to destroy the texture
	*/
	~Texture();

	/**
	* @name Copying and moving
	* Class is the sole owner of the resources and copying would cause double remove
	*/
	///@{
	Texture(const Texture& other) = delete;
	Texture(Texture&& other) = delete;
	Texture& operator=(const Texture& other) = delete;
	Texture& operator=(Texture&& other) = delete;
	///@}

	/**
	* @brief Function that activate texture unit and binds the texture
	* @param textureUnit number of the texture unit (0-15)
	*/
	void bind(unsigned int textureUnit = 0) const;

	/**
	* @brief Getter of the width
	* @return texture's width
	*/
	int getWidth() const
	{
		return width;
	}

	/**
	* @brief Getter of the height
	* @return texture's height
	*/
	int getHeight() const
	{
		return height;
	}

};