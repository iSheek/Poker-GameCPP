/**
 * @file PlayerAction.h
 * @brief File containing declaration of PlayerAction struct and ActionType enum
 */
#pragma once

#include <nlohmann/json.hpp>

/**
 * @brief Enum class representing types of actions a player can take
 */
enum class ActionType
{
	NONE = -1,

	FOLD = 1,
	CHECK,
	CALL,
	RAISE
};

/**
 * @brief Struct representing an action taken by a player
 */
struct PlayerAction
{
	ActionType actionType{ ActionType::NONE }; ///< The type of action the player is taking
	int amount{}; ///< The amount of chips associated with the action (e.g. for RAISE), for RAISE amount tells to how much we are betting and for CALL amount tells how much are we giving
};


NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PlayerAction, actionType, amount)