/**
 * @file ShowdownResult.h
 * @brief File containing structs regarding Showdown and its results
 */


#pragma once

#include "HandScore.h"
#include <nlohmann/json.hpp>
#include <vector>
#include <string>

 /**
  * @brief Struct representing the pot value, its winners and whether there was any evaluation of hands
  */
struct PotWinners
{
	long potAmount{};							///< sum of the chips for the pot
	std::vector<std::string> winnersNames{};	///< names of the winners of the pot, there's more than one if there was a tie
	bool handsWereEvaluated{};					///< true if hands were evaluated, false if there's only one authorized player for this pot
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PotWinners, potAmount, winnersNames, handsWereEvaluated)

/**
 * @brief Struct representing the player's score and its name
 */
struct PlayerHand
{
	std::string name{};		///< name of the player
	HandScore hand{};		///< HandScore of the player
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PlayerHand, name, hand)


/**
 * @brief Struct containing every information needed to send through the network
 */
struct ShowdownResult
{
	std::vector<PotWinners> potWinners{};		///< all pots and its winners (0 is the main pot and another ones are with bigger value to get into)
	std::vector<PlayerHand> playersHands{};		///< HandScores and names of the players that were able to be in a showdown, empty if there was no showdown
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ShowdownResult, potWinners, playersHands)