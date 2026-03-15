#pragma once

#include "Cards.h"
#include <vector>

struct TableState
{
	unsigned int amountToCall = 0;
	unsigned int currentHighestBet = 0;
	unsigned long currentPot = 0;
	std::vector<Card> communityCards;
	unsigned int highestBetInHistory = 0;

	void resetForNewRound()
	{
		this->amountToCall = 0;
		this->currentHighestBet = 0;
		this->currentPot = 0;
		this->communityCards.clear();
	}
};