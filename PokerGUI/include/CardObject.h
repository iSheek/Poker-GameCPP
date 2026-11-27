#pragma once

/**
* @file CardObject.h 
* @brief File containing declaration of CardObject class
*/

#include "SceneObject.h"
#include "SpriteRenderer.h"
#include "cards/Cards.h"

/**
* @brief Class representing a single card in the scene
*/
class CardObject : public SceneObject
{
private:
	Card card{};						///< which card is this object representing
	bool isHighlighted{ false };		///< flag whether this object will be highlighted
	bool isHidden{ false };				///< flag whether this card should be face down
	const Texture& frameTexture;		///< texture of the frame (for highlight)

	/**
	* @brief Helper method that gets SpriteDrawData for the frame
	* @return SpriteDrawData of the frame
	*/
	SpriteDrawData getFrameDrawData() const;

public:
	/**
	* @brief Main constructor of the class
	* @details It calls constructor of the main class @see SceneObject::SceneObject
	* @param spriteData data of the sprite
	* @param card which card will this object represent
	* @param frameTexture texture of the frame
	*/
	CardObject(const SpriteDrawData& spriteData, const Card& card, const Texture& frameTexture);

	/**
	* @copydoc SceneObject::appendSprites
	*/
	void appendSprites(std::vector<SpriteDrawData>& allSpritesData) const override;

	/**
	* @brief Setter of isHidden flag
	* @param isHidden Is the card face down
	*/
	void setIsHidden(bool isHidden)
	{
		this->isHidden = isHidden;
	}

	/**
	* @brief Setter of isHighlighted flag
	* @param isHighlighted Is the card highlighted
	*/
	void setIsHighlighted(bool isHighlighted)
	{
		this->isHighlighted = isHighlighted;
	}

	/**
	* @brief Explicit default destructor
	* @details Explicitly wrote with override to make sure that base class destructor is virtual
	*/
	~CardObject() override = default;



	//TODO DELETE
	void setCard(const Card& card)
	{
		this->card = card;
	}
};