/**
 * @file HandScore.cpp
 * @brief File containing definition of HandScore methods
 */
#include "HandScore.h"
#include "Cards.h"
#include <algorithm>
#include <cassert>

int HandScore::getCardStrength(CardRank rank) const
{
	if (rank == CardRank::ACE) return 14;
	return (int)rank;
}

bool HandScore::operator>(const HandScore& other) const
{
	if (hand != other.hand)
	{
		return hand > other.hand;
	}

	assert(usedCardsInHand.size() == other.usedCardsInHand.size());

	for (size_t i = 0; i < std::min(usedCardsInHand.size(), other.usedCardsInHand.size()); i++)
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

bool HandScore::operator==(const HandScore& other) const
{
	if (hand != other.hand) return false;

	assert(usedCardsInHand.size() == other.usedCardsInHand.size());

	for (size_t i = 0; i < std::min(usedCardsInHand.size(), other.usedCardsInHand.size()); i++)
	{
		int myCardStrength = getCardStrength(usedCardsInHand[i].rank);
		int otherCardStrength = getCardStrength(other.usedCardsInHand[i].rank);

		if (myCardStrength != otherCardStrength)
		{
			return false;
		}
	}

	return true;
}