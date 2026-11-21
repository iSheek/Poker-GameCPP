/**
 * @file Texture.cpp
 * @brief File containing definition of Texture class' functions
 */

#include "Texture.h"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <string>
#include <stdexcept>
#include <cassert>

Texture::Texture(const std::string& texturePath)
{
	// flip image since opengl texture start from bottom-left and stbi starts from top-left
	stbi_set_flip_vertically_on_load(true);
	int nrChannels{};
	unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, STBI_rgb_alpha);	// we use RGBA so we have multiple of 4, using only RGB is error-prone
	if (!data)
	{
		throw std::runtime_error("ERROR WITH TEXTURE: " + texturePath + " " + stbi_failure_reason());
	}

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);

}

Texture::~Texture()
{
	glDeleteTextures(1, &id);
}

void Texture::bind(unsigned int textureUnit) const
{
	assert(textureUnit < 16);
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, id);
}
