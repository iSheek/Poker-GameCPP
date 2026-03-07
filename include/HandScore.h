#pragma once

#include <vector>
#include <Cards.h>

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
	std::vector<Card> usedCardsInHand;

	int getCardStrength(CardRank rank) const;
	bool operator>(const HandScore& other) const;

};