#pragma once

#include "Deck.h"
#include "Cards.h"
#include "PlayerLogicParent.h"
#include <memory>
#include <vector>

// game dealer
class GameManager
{
private:
	std::vector<std::shared_ptr<PlayerLogicParent>> pPlayers;
	std::vector<Card> communityCards;
	Deck deck;

	unsigned int currentBet;
	unsigned long mainPot;

public:
	GameManager()
	{

	}
};