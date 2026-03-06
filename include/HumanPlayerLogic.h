#pragma once

#include "IPlayerLogic.h"
#include "PlayerAction.h"
#include "Cards.h"
#include <array>
#include <cstdint>

class HumanPlayerLogic : public IPlayerLogic
{
private:
	std::array<Card, 2> playersCards;
	unsigned int playersChips;

public:
	HumanPlayerLogic(unsigned int startingChips)
	{	
		resetCards();
		resetChips();
		this->playersChips = startingChips;
	}

	PlayerAction makeDecision() override
	{
		
	}

	void setCards(const Card& firstCard, const Card& secondCard)
	{
		this->playersCards[0] = firstCard;
		this->playersCards[1] = secondCard;
	}

	void setChips(unsigned int playersChips)
	{
		this->playersChips = playersChips;
	}

	void addChips(unsigned int chipsToAdd)
	{
		if (UINT32_MAX - this->playersChips < chipsToAdd)
		{
			this->playersChips = UINT32_MAX;
		}
		else this->playersChips += chipsToAdd;
	}
	
	void removeChips(unsigned int chipsToRemove)
	{
		if (chipsToRemove > this->playersChips)
		{
			this->playersChips = 0;
		}
		else this->playersChips -= chipsToRemove;
	}

	unsigned int getChips() const
	{
		return this->playersChips;
	}

	std::array<Card, 2> getPlayerCards() const
	{
		return this->playersCards;
	}

	void resetCards()
	{
		this->playersCards[0] = { CardSuit::NONE, CardRank::NONE };
		this->playersCards[1] = { CardSuit::NONE, CardRank::NONE };
	}

	void resetChips()
	{
		this->playersChips = 0;
	}

};