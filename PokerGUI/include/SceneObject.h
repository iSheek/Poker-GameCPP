#pragma once

/**
* @file SceneObject.h
* @brief File containing declaration of SceneObject abstract class
*/


#include <vector>

#include "GUIConstants.h"
#include "SpriteRenderer.h"

/**
* @brief Abstract class that represents an object in the scene
*/
class SceneObject {
protected:
	SpriteDrawData spriteData;	///< all needed data for a sprite to be drawn

	/**
	* @brief Constructor of the base class
	* @details Protected to futher block from creating an object from this class
	* @param spriteData data of the sprite
	*/
	SceneObject(const SpriteDrawData& spriteData) : spriteData(spriteData) {}
	
	/**
	* @brief Helper method that creates shadow of the sprite
	* @return SpriteDrawData object containing all data needed for shadow of the sprite
	*/
	SpriteDrawData createShadowSpriteData() const;

public:
	/**
	* @brief Method that appends all sprites for a single scene object
	* @details For example, cards need sprites for shadow, card itself (and optionally a frame for UI), chips have chip itself and a shadow
	*/
	virtual void appendSprites(std::vector<SpriteDrawData>& allSpritesData) const = 0;

	/**
	* @brief Virtual default destructor of the parent class
	*/
	virtual ~SceneObject() = default;

};