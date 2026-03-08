#pragma once

#include "Cards.h"
#include <vector>

struct TableState
{
	unsigned int amountToCall = 0;
	unsigned int currentHighestBet = 0;
	unsigned long currentPot = 0;
	std::vector<Card> communityCards;
};