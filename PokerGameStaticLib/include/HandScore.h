/**
 * @file HandScore.h
 * @brief File containing declaration of HandScore struct and PokerHand enum
 */
#pragma once

#include <vector>
#include <Cards.h>

/**
 * @brief Enum class representing types of poker hands
 */
enum class PokerHand
{
	HIGH_CARD = 1,
	ONE_PAIR,
	TWO_PAIR,
	THREE_OF_A_KIND,
	STRAIGHT,
	FLUSH,
	FULL_HOUSE,
	FOUR_OF_A_KIND,
	STRAIGHT_FLUSH,
	ROYAL_FLUSH
};

/**
 * @brief Struct representing the score and cards of an evaluated hand
 */
struct HandScore
{
	PokerHand hand{ PokerHand::HIGH_CARD };
	std::vector<Card> usedCardsInHand{};

	/**
	 * @brief Gets the numerical strength of a given card rank
	 * @param rank The rank to evaluate
	 * @return Numerical strength of the rank
	 */
	int getCardStrength(CardRank rank) const;
	
	/**
	 * @brief Compares this HandScore with another to see if this one is greater
	 * @param other The other HandScore to compare against
	 * @return true if this HandScore is better, false otherwise
	 */
	bool operator>(const HandScore& other) const;
	
	/**
	 * @brief Compares this HandScore with another for equality
	 * @param other The other HandScore to compare against
	 * @return true if both HandScores are equal, false otherwise
	 */
	bool operator==(const HandScore& other) const;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(HandScore, hand, usedCardsInHand)