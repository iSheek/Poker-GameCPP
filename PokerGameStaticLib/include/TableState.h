#pragma once

#include "Cards.h"
#include <vector>

struct TableState
{
	int amountToCall{};
	int currentHighestBet{};
	long currentPot{};
	std::vector<Card> communityCards{};
	int highestBetInHistory{};

	void resetForNewRound()
	{
		this->amountToCall = 0;
		this->currentHighestBet = 0;
		this->currentPot = 0;
		this->communityCards.clear();
	}
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TableState, amountToCall, currentHighestBet, currentPot, communityCards, highestBetInHistory)