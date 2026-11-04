/**
 * @file BettingRules.h
 * @brief File containing declaration of BettingRules namespace's functions and struct
 */

#pragma once


#include "PlayerAction.h"
#include "TableState.h"
#include "PlayerState.h"
#include <vector>
#include <algorithm>


/**
 * @brief Namespace containing things for validation, especially in betting phase
 */
namespace BettingRules
{
	/**
	 * @brief Struct representing possible options for the player at the moment
	 */
	struct AvailableOptions
	{
		std::vector <ActionType> actions{};	///< Vector containing all possible actions for the player
		int minRaiseTo{};					///< Minimum amount of player's chips that player need to raise (current + already bet)
		int maxRaiseTo{};					///< Maximum amount of all player's chips that player need to raise (current + already bet)
	};

	/**
	 * @brief Checks what player is legally able to do in this moment
	 * @details If player doesn't have any chips then it returns ActionType::NONE,
	 * if you can only do all-in then minRaiseTo = maxRaiseTo
	 * @param tableState current table's state
	 * @param playerState current player's state
	 * @return AvailableOptions struct containing all legal actions and max/min amount of chips for raising
	 */
	AvailableOptions getPossibleOptions(const TableState& tableState, const PlayerState& playerState);


	/**
	 * @brief Validates if player's action is legal
	 * @param playersAvailableOptions player's possible options
	 * @param playerAction player's intended action
	 * @return true if action is legal, false otherwise
	 */
	bool isActionValid(const AvailableOptions& playersAvailableOptions, const PlayerAction& playerAction);

}
