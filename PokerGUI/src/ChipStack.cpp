/**
* @file ChipStack.cpp
* @brief File containing definition of ChipStack class' methods
*/

#include "ChipStack.h"

#include "GUIConstants.h"

#include <glm/glm.hpp>
#include <vector>
#include <cassert>

using namespace GUIConstants;
using namespace GUIConstants::Chips;

namespace
{
	/**
	* @brief Helper function that breaks down the amount of chips into individual ones
	* @details Breaks down up to @see GUIConstants::Chips::MAX_CHIPS_PER_PLAYER and uses GUIConstants::Chips::DENOMINATIONS to get the colors, it works using greedy matching
	* @param fullAmount the amount of chips to break down to
	* @return vector of the colors of the chips
	*/
	std::vector<glm::vec4> breakDownChips(int fullAmount)
	{
		std::vector<glm::vec4> returnVector{};
		returnVector.reserve(MAX_CHIPS_PER_PLAYER);
		size_t denominationsIndex{ 0 };
		while (fullAmount > 0 && denominationsIndex < DENOMINATIONS.size() && returnVector.size() < MAX_CHIPS_PER_PLAYER)
		{
			if (fullAmount >= DENOMINATIONS[denominationsIndex].value)
			{
				fullAmount -= DENOMINATIONS[denominationsIndex].value;
				returnVector.push_back(DENOMINATIONS[denominationsIndex].color);
			}
			else
			{
				++denominationsIndex;
			}
		}
		return returnVector;
	}

	/**
	* @brief Helper function that gets the position of the chip in the stack
	* @param stackStartPosition starting position of the stack (back leftmost column)
	* @param i index of the chip from the list
	* @return vector (x,y) of the position of the chip
	*/
	glm::vec2 getPositionInStack(const glm::vec2& stackStartPosition, int i)
	{
		int column{ i / MAX_CHIPS_IN_COLUMN };
		int count{ i % MAX_CHIPS_IN_COLUMN };

		float x{};
		float y{};
		if (column < BACK_COLUMN_MAX_COUNT)
		{
			x = stackStartPosition.x + column * (SpriteConstants::CHIP_WIDTH_FROM_TEXTURE + COLUMN_GAP);
			y = stackStartPosition.y + count * STACK_STEP;
		}
		else if (column < (BACK_COLUMN_MAX_COUNT + FRONT_COLUMN_MAX_COUNT))
		{
			x = stackStartPosition.x + (column - BACK_COLUMN_MAX_COUNT + 0.5f) * (SpriteConstants::CHIP_WIDTH_FROM_TEXTURE + COLUMN_GAP);
			y = stackStartPosition.y - FRONT_ROW_PIXEL_OFFSET + count * STACK_STEP ;
		}
		else
		{
			assert(false);
			return stackStartPosition;
		}

		return glm::vec2(x, y);
	}
}

void ChipStack::appendSprites(std::vector<SpriteDrawData>& allSpritesData) const
{
	

	std::vector<glm::vec4> visibleChipsColors{ breakDownChips(amount) };

	assert(visibleChipsColors.size() <= MAX_CHIPS_PER_PLAYER);
	
	
	SpriteDrawData shadowSpriteData{ createShadowSpriteData() };

	for (int i{ 0 }; i < static_cast<int>(visibleChipsColors.size()); ++i)
	{
		SpriteDrawData copyShadowSpriteData{ shadowSpriteData };
		copyShadowSpriteData.position = getPositionInStack(copyShadowSpriteData.position, i);
		allSpritesData.push_back(copyShadowSpriteData);
	}


	
	for (int i{ 0 }; i < static_cast<int>(visibleChipsColors.size()); ++i)
	{
		SpriteDrawData copySpriteData{ spriteData };
		copySpriteData.position = getPositionInStack(spriteData.position, i);
		copySpriteData.multiplier = visibleChipsColors[i];
		copySpriteData.useWhiteException = true;
		allSpritesData.push_back(copySpriteData);
	}

}
