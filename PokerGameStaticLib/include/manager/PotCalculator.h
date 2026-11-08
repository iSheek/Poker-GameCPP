/**
 * @file PotCalculator.h
 * @brief File containing declaration of PotCalculator namespace's functions and struct
 */

#pragma once

#include <vector>
#include "PublicPlayerInfo.h"

/**
 * @brief Namespace containing functions and struct for calculating all pots
 */
namespace PotCalculator
{
	/**
	 * @brief Struct representing a pot
	 */
	struct Pot
	{
		long totalChips{};									///< total amount of chips in pot
		std::vector <int> authorizedPlayersIndices{};		///< vector containing all players' indices that are authorized for pot
	};

	/**
	 * @brief Gets every pots
	 * @details if player with the most contribution folded, then surplus of his contribution will be given to the biggest pot with any authorized player;
	 * authorized players in each pot is = to index from publicPlayersInfo;
	 * if every player folded then caller is ought to handle this situation
	 * @param publicPlayersInfo vector of public informations of every player
	 * @throws runtime_error when argument's vector's size is 0
	 * @return vector containing all pots (where index 0 is main pot)
	 */
	std::vector<Pot> getAllPots(const std::vector<PublicPlayerInfo>& publicPlayersInfo);

}