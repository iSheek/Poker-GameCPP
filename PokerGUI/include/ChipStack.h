#pragma once

/**
* @file ChipStack.h
* @brief File containing declaration of ChipStack class
*/

#include "SceneObject.h"

/**
* @brief Class representing stack of chips that represents an amount
* @details spriteData.position represents back leftmost column of the chips
*/
class ChipStack : public SceneObject
{
private:
	int amount{};	///< amount of chips (value)

public:
	/**
	* @brief Main constructor of the class
	* @details It calls constructor of the main class @see SceneObject::SceneObject
	* @param spriteData data of the sprite, .position represents a position of the first chip from the bottom of the back leftmost column
	* @param amount amount of chips
	*/
	ChipStack(const SpriteDrawData& spriteData, int amount) : SceneObject(spriteData), amount(amount) {}

	/**
	* @copydoc SceneObject::appendSprites
	*/
	void appendSprites(std::vector<SpriteDrawData>& allSpritesData) const override;


	/**
	* @brief Setter of the amount
	* @param newAmount new amount
	*/
	void setAmount(int newAmount)
	{
		amount = newAmount;
	}

	/**
	* @brief Getter of the amount
	* @return amount of the chips
	*/
	int getAmount() const
	{
		return amount;
	}

};