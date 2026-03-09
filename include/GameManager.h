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
	Deck deck;

	TableState currentTableState;

	std::shared_ptr<IOutputHandler> pOutputHandler;

	GameManager(std::shared_ptr<IOutputHandler> pOutputHandler) : pOutputHandler(pOutputHandler) 
	{
		currentTableState.currentHighestBet = 0;
		currentTableState.currentPot = 0;
	}
public:

	virtual ~GameManager() = default;

	void addPlayer(std::shared_ptr<PlayerLogicParent> pPlayer)
	{
		this->pPlayers.push_back(pPlayer);
	}

	virtual void playRound() = 0;
};