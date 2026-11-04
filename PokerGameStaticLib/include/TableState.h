/**
 * @file TableState.h
 * @brief File containing declaration of TableState struct
 */
#pragma once

#include "Cards.h"
#include <vector>
#include <nlohmann/json.hpp>

/**
 * @brief Struct representing the current state of the poker table
 */
struct TableState
{
	int amountToCall{}; ///< The amount required to call the current highest bet
	int currentHighestBet{}; ///< The highest bet placed in the current betting round
	long currentPot{}; ///< The total chips currently in the pot
	std::vector<Card> communityCards{}; ///< The community cards dealt on the table
	int lastFullRaiseAmount{}; ///< How much does raise increased (at the start of each phase it is equal to big blind)

	/**
	 * @brief Resets the table state for a new round
	 */
	void resetForNewRound()
	{
		this->amountToCall = 0;
		this->currentHighestBet = 0;
		this->currentPot = 0;
		this->communityCards.clear();
	}
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TableState, amountToCall, currentHighestBet, currentPot, communityCards, lastFullRaiseAmount)