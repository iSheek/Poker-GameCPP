#pragma once
/**
 * @file Cards.h
 * @brief File containing enum classes for cards and Card struct
 */

#include <nlohmann/json.hpp>

/**
 * @brief Enum class representing card's suit
 * @details It uses -1 as NONE value representing nothing
 */
enum class CardSuit
{
	NONE = -1,

	DIAMONDS = 1,
	CLUBS,
	HEARTS,
	SPADES
};

/**
 * @brief Enum class representing card's rank
 * @details It uses -1 as NONE value representing nothing and ace is represented as 1, 
 * also it contains joker (if there will be any plan to add games including him)
 */
enum class CardRank
{
	NONE = -1,

	ACE = 1,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,

	JACK,
	QUEEN,
	KING,

	JOKER
};

/**
 * @brief Structure representing a single card
 */
struct Card
{
	CardSuit suit{ CardSuit::NONE };	///< enum representing card's suit
	CardRank rank{CardRank::NONE};		///< enum representing card's rank

};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Card, suit, rank)