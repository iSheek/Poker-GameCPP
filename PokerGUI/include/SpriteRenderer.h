#pragma once
/**
 * @file SpriteRenderer.h
 * @brief File containing declaration of SpriteRenderer class
 */

#include <glm/glm.hpp>

#include "Texture.h"
#include "ShaderProgram.h"

/**
* @brief Helper struct containing information needed for proper render of a sprite
*/
struct SpriteDrawData
{
	const Texture& texture;								///< existing texture																
	glm::vec2 position{};								///< central point of sprite
	glm::vec2 size{};									///< full height and width of a sprite
	float rotation{};									///< rotation in radians of a sprite
	glm::vec4 UVrect{ 0.0f, 0.0f, 1.0f, 1.0f };			///< UV rectangle used for taking a part of texture atlas XYZW - XY fragment of atlas - ZW size of the fragment, default value is a whole texture
	glm::vec4 multiplier{ 1.0f, 1.0f, 1.0f, 1.0f };		///< multiplier used for shadows, UI, etc. it only multiplies existing color in shader, be default itself doesnt change anything
	bool useWhiteException{ false };					///< should we not use multiplier on pure white in fragment shader
};

/**
* @brief Class that takes care of rendering a sprite
*/
class SpriteRenderer
{
private:
	unsigned int VAO{};						///< id of vertex array object
	unsigned int VBO{};						///< id of vertex buffer object
	unsigned int EBO{};						///< id of element buffer object

	const ShaderProgram& shaderProgram;		///< existing shaderProgram

public:
	/**
	* @brief Main constructor of the class
	* @details It creates unit square (where 0,0 is central point), creates VAO, VBO, EBO and binds them together,
	* also it creates projection matrix and enables blending in OpenGL and sets up sampler settings
	* @param shaderProgram existing ShaderProgram
	* @pre shaderProgram has to live longer than renderer and there has to be existing OpenGL context
	*/
	SpriteRenderer(const ShaderProgram& shaderProgram);

	/**
	* @name Copying and moving
	* Class is the sole owner of the resources and copying would cause double remove
	*/
	///@{
	SpriteRenderer(const SpriteRenderer& other) = delete;
	SpriteRenderer(SpriteRenderer&& other) = delete;
	SpriteRenderer& operator=(const SpriteRenderer& other) = delete;
	SpriteRenderer& operator=(SpriteRenderer&& other) = delete;
	///@}

	/**
	* @brief Custom destructor of the class
	* @details It destroys buffers and VAO
	*/
	~SpriteRenderer();

	/**
	* @brief Method that draws a sprite
	* @details It uses existing ShaderProgram, creates model matrix using data from SpriteDrawData and draws a rectangle
	* @param spriteData data for rendering a sprite in a desired way
	*/
	void draw(const SpriteDrawData& spriteData) const;


};