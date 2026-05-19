/**
 * @file TexasHoldemManager.h
 * @brief File containing declaration of TexasHoldemManager class
 */
#pragma once

#include "GameManager.h"
#include "HandEvaluator.h"
#include <stdexcept>
#include <algorithm>

constexpr int SMALL_BLIND_PLAYER_INDEX = 0;
constexpr int BIG_BLIND_PLAYER_INDEX = 1;

constexpr int UNDER_THE_GUN_PLAYER_INDEX = 2;

/**
 * @brief Class managing the flow of a Texas Hold'em game
 */
class TexasHoldemManager : public GameManager
{
private:
	int smallBlind{}; ///< The value of the small blind
	int bigBlind{}; ///< The value of the big blind

	TableState currentTableState{}; ///< The current state of the table

	/**
	 * @brief Executes a betting round starting from a specific player
	 * @param startingIndex The index of the player who starts the betting
	 */
	void bettingRound(int startingIndex);

	/**
	 * @brief Handles the small and big blinds at the start of a round
	 */
	void blindsPhase();

	/**
	 * @brief Handles the pre-flop phase (dealing cards to players)
	 */
	void preFlopPhase();

	/**
	 * @brief Handles the flop phase (dealing first 3 community cards)
	 */
	void flopPhase();

	/**
	 * @brief Handles the turn phase (dealing the 4th community card)
	 */
	void turnPhase();

	/**
	 * @brief Handles the river phase (dealing the 5th community card)
	 */
	void riverPhase();

	/**
	 * @brief Handles the showdown phase (evaluating hands and awarding the pot)
	 */
	void showdownPhase();

	/**
	 * @brief Performs cleanup after a round (resetting states, removing bankrupt players)
	 */
	void cleanupPhase();

public: 
	/**
	 * @brief Constructor
	 * @param pOutputHandler The output handler to use
	 */
	TexasHoldemManager(std::shared_ptr<IOutputHandler> pOutputHandler);

	/**
	 * @brief Plays a single round of Texas Hold'em
	 */
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