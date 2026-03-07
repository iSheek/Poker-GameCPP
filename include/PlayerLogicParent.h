#pragma once

#include "IPlayerLogic.h"
#include "PlayerAction.h"
#include "Cards.h"
#include <array>
#include <cstdint>


class PlayerLogicParent : public IPlayerLogic
{
private:
	std::array<Card, 2> playersCards;
	unsigned int playersChips;
	bool hasFolded;
	unsigned int currentBet;


public:
	PlayerLogicParent(unsigned int startingChips)
	{	
		resetPlayer(startingChips);
	}

	virtual PlayerAction makeDecision() override = 0;

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

	void fold()
	{
		this->hasFolded = true;
	}

	bool getHasFolded() const
	{
		return this->hasFolded;
	}

	void resetFold()
	{
		this->hasFolded = false;
	}

	void setCurrentBet(unsigned int bet)
	{
		this->currentBet = bet;
	}

	unsigned int getCurrentBet() const
	{
		return this->currentBet;
	}

	void resetPlayer(unsigned int startingChips)
	{
		resetCards();
		resetChips();
		this->playersChips = startingChips;
		this->hasFolded = false;
		this->currentBet = 0;
	}

};