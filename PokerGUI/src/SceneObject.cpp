/**
* @file SceneObject.cpp
* @brief File containing definition of SceneObject abstract class' methods
*/

#include <glm/glm.hpp>
#include "GUIConstants.h"
#include "SceneObject.h"

using namespace GUIConstants;

SpriteDrawData SceneObject::createShadowSpriteData() const
{
	SpriteDrawData shadowData = spriteData;
	shadowData.multiplier = SpriteConstants::SHADOW_MULTIPLIER;
	shadowData.position = shadowData.position + glm::vec2(SpriteConstants::SHADOW_X_OFFSET, SpriteConstants::SHADOW_Y_OFFSET);
	shadowData.useWhiteException = false;
	return shadowData;
}
