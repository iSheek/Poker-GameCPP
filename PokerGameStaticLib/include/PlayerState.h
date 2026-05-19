/**
 * @file PlayerState.h
 * @brief File containing declaration of PlayerState struct
 */
#pragma once

#include "Cards.h"
#include <array>
#include <nlohmann/json.hpp>

/**
 * @brief Struct representing the private state of a player
 */
struct PlayerState
{
	std::array<Card, 2> playersCards{}; ///< The two hole cards given to the player
	int currentChips{}; ///< The current amount of chips the player holds
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PlayerState, playersCards, currentChips)