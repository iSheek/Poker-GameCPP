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
	std::vector<Card> usedCardsInHand;

	int getCardStrength(CardRank rank) const
	{
		if (rank == CardRank::ACE) return 14;
		return (int)rank;
	}

	bool operator>(const HandScore& other) const
	{
		if (hand != other.hand)
		{
			return hand > other.hand;
		}

		for (size_t i = 0; i < usedCardsInHand.size(); i++)
		{
			int myCardStrength = getCardStrength(usedCardsInHand[i].rank);
			int otherCardStrength = getCardStrength(other.usedCardsInHand[i].rank);

			if (myCardStrength != otherCardStrength)
			{
				return myCardStrength > otherCardStrength;
			}
		}

		return false;
	}
};