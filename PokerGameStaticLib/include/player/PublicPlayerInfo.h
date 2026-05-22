/**
 * @file PublicPlayerInfo.h
 * @brief File containing declaration of PublicPlayerInfo struct
 */
#pragma once

#include <string>
#include <nlohmann/json.hpp>

/**
 * @brief Struct representing publicly visible information about a player
 */
struct PublicPlayerInfo
{
	std::string name{}; ///< The player's chosen nickname
	int chips{}; ///< The player's current total chips
	int currentBet{}; ///< The amount the player has bet in the current phase
	int totalBet{}; ///< The total amount the player has bet during the round
	bool hasFolded{ true }; ///< Whether the player has folded their hand
};


NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PublicPlayerInfo, name, chips, currentBet, totalBet, hasFolded)