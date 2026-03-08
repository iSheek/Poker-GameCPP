#pragma once

#include "GameManager.h"
#include <stdexcept>

class TexasHoldemManager : public GameManager
{
private:
	unsigned int smallBlind;
	unsigned int bigBlind;

	void bettingRound()
	{

	}
	
	void blindsPhase()
	{
		if (pPlayers.size() < 2) throw std::range_error("ERROR NOT ENOUGH PLAYERS");

		this->currentHighestBet = smallBlind;

		unsigned int p1Chips = pPlayers[0]->getChips();
		if (p1Chips <= currentHighestBet)
		{
			// ALL IN
			pPlayers[0]->setCurrentBet(p1Chips);
			pPlayers[0]->removeChips(p1Chips);
			this->mainPot += p1Chips;
		}
		else
		{
			pPlayers[0]->setCurrentBet(smallBlind);
			pPlayers[0]->removeChips(smallBlind);
			this->mainPot += smallBlind;
		}

		this->currentHighestBet = bigBlind;

		unsigned int p2Chips = pPlayers[1]->getChips();
		if (p2Chips <= bigBlind)
		{
			// ALL IN
			pPlayers[1]->setCurrentBet(p2Chips);
			pPlayers[1]->removeChips(p2Chips);
			this->mainPot += p2Chips;
		}
		else
		{
			pPlayers[1]->setCurrentBet(bigBlind);
			pPlayers[1]->removeChips(bigBlind);
			this->mainPot += bigBlind;
		}
	}

	void preFlopPhase()
	{

	}

	void flopPhase()
	{

	}

	void turnPhase()
	{

	}

	void riverPhase()
	{

	}

	void showdownPhase()
	{

	}

	void cleanupPhase()
	{

	}

public: 
	TexasHoldemManager(std::shared_ptr<IOutputHandler> pOutputHandler) : GameManager(pOutputHandler), smallBlind(10), bigBlind(20) {}

	void playRound() override
	{
		if (pPlayers.size() < 2) throw std::range_error("ERROR NOT ENOUGH PLAYERS");

	}

	void setSmallBlind(unsigned int newSmallBlindBet)
	{
		this->smallBlind = newSmallBlindBet;
	}

	void setBigBlind(unsigned int newBigBlindBet)
	{
		this->bigBlind = newBigBlindBet;
	}
};