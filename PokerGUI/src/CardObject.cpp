/**
* @file CardObject.cpp
* @brief File containing definition of CardObject class' methods
*/


#include "CardObject.h"
#include "GUIConstants.h"

#include <cassert>

using namespace GUIConstants::SpriteConstants;

namespace {
	/**
	* @brief Helper function that gets UVRect from the atlas of the desired card
	* @param card which card's UVRect we want
	* @param isHidden should the UVRect be of the hidden card
	* @return glm::vec4 of mapped UVRect for the desired card
	*/
	glm::vec4 getAtlasMappedUVRect(const Card& card, bool isHidden = false)
	{
		static_assert(static_cast<int>(CardRank::ACE) == 1 && static_cast<int>(CardRank::KING) == 13);
		int column{static_cast<int>(card.rank) - 1};

		int row{};
		if (!isHidden)
		{
			switch (card.suit)
			{
			case CardSuit::DIAMONDS:
				row = DIAMONDS_SUIT_ROW_IN_ATLAS;
				break;
			case CardSuit::CLUBS:
				row = CLUBS_SUIT_ROW_IN_ATLAS;
				break;
			case CardSuit::HEARTS:
				row = HEARTS_SUIT_ROW_IN_ATLAS;
				break;
			case CardSuit::SPADES:
				row = SPADES_SUIT_ROW_IN_ATLAS;
				break;
			default:
				assert(false);
				break;
			}
		}
		else
		{
			column = CARD_BACK_COLUMN_IN_ATLAS;
			row = CARD_BACK_ROW_IN_ATLAS;
		}
		

		return glm::vec4(column * CARD_CELL_WIDTH / CARDS_ATLAS_WIDTH,
			(CARDS_ATLAS_HEIGHT - (row + 1) * CARD_CELL_HEIGHT) / CARDS_ATLAS_HEIGHT,
			CARD_CELL_WIDTH / CARDS_ATLAS_WIDTH,
			CARD_CELL_HEIGHT / CARDS_ATLAS_HEIGHT);
	}

}

SpriteDrawData CardObject::getFrameDrawData() const
{
	return SpriteDrawData{
		.texture = frameTexture,
		.position = spriteData.position,
		.size = spriteData.size,
		.rotation = spriteData.rotation,
		.UVrect = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		.multiplier = FRAME_MULTIPLIER,
		.useWhiteException = false
	};

}

void CardObject::appendSprites(std::vector<SpriteDrawData>& allSpritesData) const
{
	SpriteDrawData shadowSpriteData{ createShadowSpriteData() };
	allSpritesData.push_back(shadowSpriteData);

	if (isHighlighted)
	{
		SpriteDrawData frameData{ getFrameDrawData() };
		allSpritesData.push_back(frameData);
	}

	SpriteDrawData cardData{ spriteData };
	cardData.UVrect = getAtlasMappedUVRect(card, isHidden);
	allSpritesData.push_back(cardData);

}
