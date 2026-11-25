/**
 * @file Framebuffer.cpp
 * @brief File containing definition of Framebuffer class' methods
 */

#include <glad/glad.h>

#include <algorithm>
#include <stdexcept>

#include "Framebuffer.h"
#include "GUIConstants.h"

using namespace GUIConstants;



Framebuffer::Framebuffer()
{
	glGenFramebuffers(1, &FBO);

	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, VirtualResolution::WIDTH, VirtualResolution::HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// attach texture to framebuffer
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId, 0);


	if (!(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE))
	{
		glDeleteTextures(1, &textureId);
		glDeleteFramebuffers(1, &FBO);
		throw std::runtime_error("ERROR SOMETHING WENT WRONG WITH FRAMEBUFFER");
	}

	// unbind after creating
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

Framebuffer::~Framebuffer()
{
	glDeleteTextures(1, &textureId);
	glDeleteFramebuffers(1, &FBO);
}

void Framebuffer::drawToFramebuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glViewport(0, 0, VirtualResolution::WIDTH, VirtualResolution::HEIGHT);
	ImVec4 clear_color = TABLE_COLOR;        // poker table color
	glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Framebuffer::showInWindow(int windowWidth, int windowHeight)
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, FBO);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	int scale{ std::min(windowWidth / VirtualResolution::WIDTH, windowHeight / VirtualResolution::HEIGHT) };
	scale = scale <= 0 ? 1 : scale;

	int dstRectWidth{ VirtualResolution::WIDTH * scale };
	int dstRectHeight{ VirtualResolution::HEIGHT * scale };

	int dstX0{ (windowWidth - dstRectWidth) / 2 };
	int dstY0{ (windowHeight - dstRectHeight) / 2 };

	glBlitFramebuffer(0, 0, VirtualResolution::WIDTH, VirtualResolution::HEIGHT, dstX0, dstY0, dstX0 + dstRectWidth, dstY0 + dstRectHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);

	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glViewport(0, 0, windowWidth, windowHeight);
}
