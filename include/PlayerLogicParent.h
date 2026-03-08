#pragma once

#include "PlayerAction.h"
#include "Cards.h"
#include "TableState.h"
#include <array>


class PlayerLogicParent
{
private:
	std::array<Card, 2> playersCards;
	unsigned int playersChips;
	bool hasFolded;
	unsigned int currentBet;

protected:
	PlayerLogicParent(unsigned int startingChips)
	{
		resetPlayer(startingChips);
	}

public:

	virtual PlayerAction makeDecision(const TableState& state) = 0;

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

	void addToCurrentBet(unsigned int amountToAdd)
	{
		this->currentBet += amountToAdd;
	}

	void resetPlayer(unsigned int startingChips);

};