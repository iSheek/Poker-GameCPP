#pragma once

#include "Deck.h"
#include "Cards.h"
#include "PlayerLogicParent.h"
#include "IOutputHandler.h"
#include <memory>
#include <vector>

// game dealer
class GameManager
{
protected:
	std::vector<std::shared_ptr<PlayerLogicParent>> pPlayers;
	std::vector<Card> communityCards;
	Deck deck;

	unsigned int currentHighestBet;
	unsigned long mainPot;

	std::shared_ptr<IOutputHandler> pOutputHandler;

	GameManager(std::shared_ptr<IOutputHandler> pOutputHandler) : pOutputHandler(pOutputHandler), currentHighestBet(0), mainPot(0) {}
public:

	virtual ~GameManager() = default;

	void addPlayer(std::shared_ptr<PlayerLogicParent> pPlayer)
	{
		this->pPlayers.push_back(pPlayer);
	}

	virtual void playRound() = 0;
};