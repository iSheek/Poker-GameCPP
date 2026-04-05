#pragma once

#include "GameManager.h"
#include "HandEvaluator.h"
#include <stdexcept>
#include <algorithm>

constexpr int SMALL_BLIND_PLAYER_INDEX = 0;
constexpr int BIG_BLIND_PLAYER_INDEX = 1;

constexpr int UNDER_THE_GUN_PLAYER_INDEX = 2;

class TexasHoldemManager : public GameManager
{
private:
	int smallBlind{};
	int bigBlind{};

	TableState currentTableState{};

	void bettingRound(int startingIndex);
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

	void setSmallBlind(int newSmallBlindBet)
	{
		this->smallBlind = newSmallBlindBet;
	}

	void setBigBlind(int newBigBlindBet)
	{
		this->bigBlind = newBigBlindBet;
	}
};