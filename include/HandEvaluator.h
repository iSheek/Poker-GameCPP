#pragma once

#include "Cards.h"
#include "HandScore.h"
#include <vector>
#include <algorithm>

class HandEvaluator
{
private:

	static bool checkForHighestStraightFlush(const std::vector<Card>& cardsToCheck)
	{
		if (cardsToCheck.size() < 5) return false;

		int startingIndex = 1;
		int endIndex = 5;

		while (endIndex <= cardsToCheck.size())
		{
			bool straightFlushIsPossible = true;
			for (size_t i = startingIndex; i < endIndex; i++)
			{
				if ((int)cardsToCheck[i].rank != (int)cardsToCheck[i - 1].rank - 1)
				{
					straightFlushIsPossible = false;
					break;
				}
			}
			if (straightFlushIsPossible) return true;
			++startingIndex;
			++endIndex;
		}

		// Check for royal flush (because ace in enum is 1)
		if (cardsToCheck.front().rank == CardRank::KING && cardsToCheck[3].rank == CardRank::TEN && cardsToCheck.back().rank == CardRank::ACE) return true;

		return false;
	}
	


public:
	static PokerHand Evaluate(std::vector<Card> allCardsInHand)
	{
		std::sort(allCardsInHand.begin(), allCardsInHand.end(), [](const Card& a, const Card& b) {return a.rank > b.rank; });


		std::vector<Card> suitBuckets[5];

		for (const Card& card : allCardsInHand)
		{
			suitBuckets[static_cast<int>(card.suit)].push_back(card);
		}

		for (size_t i = 1; i < suitBuckets->size(); i++)
		{
			if (checkForHighestStraightFlush(suitBuckets[i]))
			{
				if (suitBuckets[i].front().rank == CardRank::KING && suitBuckets[i][3].rank == CardRank::TEN && suitBuckets[i].back().rank == CardRank::ACE) return PokerHand::ROYAL_FLUSH;
				return PokerHand::STRAIGHT_FLUSH;
			}


		}


	}




};