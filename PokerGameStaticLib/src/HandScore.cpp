#include "HandScore.h"
#include "Cards.h"

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

	if (usedCardsInHand.size() > other.usedCardsInHand.size()) return true;

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

bool HandScore::operator==(const HandScore& other) const
{
	if (usedCardsInHand.size() != other.usedCardsInHand.size()) return false; 

	if (hand != other.hand) return false;

	for (size_t i = 0; i < usedCardsInHand.size(); i++)
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