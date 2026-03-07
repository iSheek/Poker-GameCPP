#pragma once

#include "Cards.h"
#include <vector>

struct TableState
{
	unsigned int amountToCall;
	unsigned int currentHighestBet;
	unsigned long currentPot;
	std::vector<Card> communityCards;
};