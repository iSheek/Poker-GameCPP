/**
 * @file SpriteRenderer.cpp
 * @brief File containing definition of SpriteRenderer class' methods
 */

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GUIConstants.h"
#include "SpriteRenderer.h"

namespace
{
	constexpr unsigned int TEXTURE_SPRITE_SLOT{ 0 }; // slot for texture unit in OpenGL
}


SpriteRenderer::SpriteRenderer(const ShaderProgram& shaderProgram)
	: shaderProgram(shaderProgram)
{
	// create square (since every sprite will be a square)
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,				// left down vertex
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,				// left up vertex
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,				// right up vertex
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f				// right down vertex
	};

	unsigned int indices[] = {
		3, 1, 0,
		2, 1, 3
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	// index 0 of attrib pointer is location (XYZ), index 1 of attrib pointer is texture coords (UV)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glBindVertexArray(0);

	using namespace GUIConstants;
	using namespace GUIConstants::UniformNames;

	shaderProgram.use();
	shaderProgram.setInt(TEXTURE_NAME_IN_SHADER, TEXTURE_SPRITE_SLOT);

	glm::mat4 projection = glm::ortho(VirtualResolution::left, VirtualResolution::right, VirtualResolution::bottom, VirtualResolution::up);
	shaderProgram.setMat4(PROJECTION_MATRIX_NAME, projection);

	glEnable(GL_BLEND); // turn on blending since we will be using alpha channel
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

SpriteRenderer::~SpriteRenderer()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
}

void SpriteRenderer::draw(const SpriteDrawData& spriteData) const
{
	shaderProgram.use();

	spriteData.texture.bind(TEXTURE_SPRITE_SLOT);

	glm::mat4 transform = glm::mat4(1.0f); // identity matrix first
	transform = glm::translate(transform, glm::vec3(spriteData.position, 0.0f));
	transform = glm::rotate(transform, spriteData.rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::scale(transform, glm::vec3(spriteData.size, 1.0f));

	using namespace GUIConstants::UniformNames;

	shaderProgram.setMat4(MODEL_MATRIX_NAME, transform);

	shaderProgram.setVec4(MULTIPLIER_NAME_IN_SHADER, spriteData.multiplier);
	shaderProgram.setVec4(UVRECT_NAME_IN_SHADER, spriteData.UVrect);

	shaderProgram.setBool(B_WHITE_EXCEPTION_IN_SHADER, spriteData.useWhiteException);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);
}
