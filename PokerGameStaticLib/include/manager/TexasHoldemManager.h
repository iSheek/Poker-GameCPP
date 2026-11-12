/**
 * @file TexasHoldemManager.h
 * @brief File containing declaration of TexasHoldemManager class
 */
#pragma once

#include "GameManager.h"
#include "HandEvaluator.h"
#include "PublicPlayerInfo.h"
#include <vector>
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

	/**
	 * @brief Gets public info for every player
	 * @return vector containing all public info for every player (where index = pPlayers index)
	 */
	std::vector<PublicPlayerInfo> getEveryPlayersPublicInfo() const;

	/**
	 * @brief Executes a betting round starting from a specific player
	 * @details Actions are validated using functions from BettingRules namespace, illegal action is changed to FOLD and lastFullRaiseAmount is set to Big Blind at the start;
	 * the round is skipped when there's nobody else to bet with, and it ends when there's only one player
	 * @param startingIndex The index of the player who starts the betting
	 */
	void bettingRound(int startingIndex);

	/**
	* @brief Helper function that deals community cards and starts betting round 
	* @details this function operates only in flop, turn and river
	* @param amountOfCardsToDeal how many cards will be dealt
	*/
	void executeStreet(int amountOfCardsToDeal);

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
	 * @brief Handles the showdown phase
	 * @details using PotCalculator it divides pots into main one and side ones, every pot is evaluated separately, cards are shown only if there is any evaluation, 
	 * only one onShowdown with results; if there is a rest from dividing a pot between winners, then the closest from left of the dealer winner is getting the rest
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

	/**
	 * @brief Sets the small blind value
	 * @param newSmallBlindBet The new small blind amount
	 */
	void setSmallBlind(int newSmallBlindBet)
	{
		this->smallBlind = newSmallBlindBet;
	}

	/**
	 * @brief Sets the big blind value
	 * @param newBigBlindBet The new big blind amount
	 */
	void setBigBlind(int newBigBlindBet)
	{
		this->bigBlind = newBigBlindBet;
	}


};