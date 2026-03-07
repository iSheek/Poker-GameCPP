#pragma once

#include "IPlayerLogic.h"
#include "PlayerAction.h"
#include "Cards.h"
#include <array>


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

	virtual PlayerAction makeDecision(unsigned int amountToCall) override = 0;

	void setCards(const Card& firstCard, const Card& secondCard);

	void setChips(unsigned int playersChips)
	{
		this->playersChips = playersChips;
	}

	void addChips(unsigned int chipsToAdd);
	
	void removeChips(unsigned int chipsToRemove);

	unsigned int getChips() const
	{
		return this->playersChips;
	}

	std::array<Card, 2> getPlayerCards() const
	{
		return this->playersCards;
	}

	void resetCards();

	void resetChips();

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

	void resetPlayer(unsigned int startingChips);

};