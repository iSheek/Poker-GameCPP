#pragma once

#include "Cards.h"
#include "HandScore.h"
#include <vector>
#include <algorithm>
#include <optional>
#include <array>

class HandEvaluator
{
private:

	static std::optional<std::vector<Card>> checkForHighestStraightFlush(const std::vector<Card>& cardsToCheck)
	{
		if (cardsToCheck.size() < 5) return std::nullopt;

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
			if (straightFlushIsPossible)
			{
				return std::vector<Card>(cardsToCheck.begin() + startingIndex - 1, cardsToCheck.begin() + endIndex);
			}
			++startingIndex;
			++endIndex;
		}

		// Check for royal flush (because ace in enum is 1)
		if (cardsToCheck.front().rank == CardRank::KING && cardsToCheck[3].rank == CardRank::TEN && cardsToCheck.back().rank == CardRank::ACE)
		{
			return std::vector<Card>{cardsToCheck[0], cardsToCheck[1], cardsToCheck[2], cardsToCheck[3], cardsToCheck.back()};
		}

		return std::nullopt;
	}
	
	static std::optional<std::vector<Card>> checkForFourOfAKind(const std::vector<Card>& cardsToCheck)
	{
		std::array<int, 14> rankCounts = { 0 };
		for (const auto& card : cardsToCheck)
		{
			rankCounts[(int)card.rank]++;
		}

		CardRank foundFourRank = CardRank::NONE;

		bool foundHand = false;

		for (int i = 1; i < rankCounts.size(); i++)
		{
			if (rankCounts[i] == 4)
			{
				foundFourRank = static_cast<CardRank>(i);
				foundHand = true;
				break;
			}
		}

		if (!foundHand) return std::nullopt;

		std::vector<Card> usedCards;
		usedCards.reserve(5);

		
		bool foundKicker = false;
		Card highestKicker;

		// Additional 'if' to use Ace as kicker
		if (rankCounts[1] > 0 && foundFourRank != CardRank::ACE)
		{
			for (const auto& card : cardsToCheck)
			{
				if ((int)card.rank == 1)
				{
					highestKicker = card;
					foundKicker = true;
					break;
				}
			}
		}


		// We put four of a kind cards into our vector to return
		for (const auto& card : cardsToCheck)
		{
			if (card.rank == foundFourRank)
			{
				usedCards.push_back(card);
			}
			else if (!foundKicker)
			{
				highestKicker = card;
				foundKicker = true;
			}
		}



		usedCards.push_back(highestKicker);
		return usedCards;

	}


public:
	static HandScore Evaluate(std::vector<Card> allCardsInHand)
	{
		std::sort(allCardsInHand.begin(), allCardsInHand.end(), [](const Card& a, const Card& b) {return a.rank > b.rank; });


		std::array<std::vector<Card>, 5> suitBuckets;

		for (const Card& card : allCardsInHand)
		{
			suitBuckets[static_cast<int>(card.suit)].push_back(card);
		}

		for (size_t i = 1; i < suitBuckets.size(); i++)
		{
			if (suitBuckets.size() < 5) continue;

			if (auto sfCards = checkForHighestStraightFlush(suitBuckets[i]))
			{
				if (suitBuckets[i].front().rank == CardRank::KING)
				{
					return HandScore{ PokerHand::ROYAL_FLUSH, sfCards.value()};
				}
				return HandScore{ PokerHand::STRAIGHT_FLUSH, sfCards.value() };
			}

		}

		checkForFourOfAKind(allCardsInHand);


	}




};