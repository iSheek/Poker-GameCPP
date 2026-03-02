#pragma once

#include <vector>

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


struct HandScore
{
	PokerHand hand;
	std::vector<int> valuesInHand;
	std::vector<Card> usedCardsInHand;

	bool operator>(const HandScore& other)
	{
		if (hand != other.hand)
		{
			return hand > other.hand;
		}

		return valuesInHand > other.valuesInHand;
	}
};