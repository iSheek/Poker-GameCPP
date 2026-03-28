#pragma once

#include "GameManager.h"
#include "HandEvaluator.h"
#include <stdexcept>
#include <algorithm>

constexpr unsigned int SMALL_BLIND_PLAYER_INDEX = 0;
constexpr unsigned int BIG_BLIND_PLAYER_INDEX = 1;

constexpr unsigned int UNDER_THE_GUN_PLAYER_INDEX = 2;

class TexasHoldemManager : public GameManager
{
private:
	unsigned int smallBlind;
	unsigned int bigBlind;

	TableState currentTableState;

	void bettingRound(unsigned int startingIndex);
	void blindsPhase();
	void preFlopPhase();
	void flopPhase();
	void turnPhase();
	void riverPhase();
	void showdownPhase();
	void cleanupPhase();

public: 
	TexasHoldemManager(std::shared_ptr<IOutputHandler> pOutputHandler);

	void playRound() override;

	void setSmallBlind(unsigned int newSmallBlindBet)
	{
		this->smallBlind = newSmallBlindBet;
	}

	void setBigBlind(unsigned int newBigBlindBet)
	{
		this->bigBlind = newBigBlindBet;
	}
};