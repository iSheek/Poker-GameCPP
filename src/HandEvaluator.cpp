#include "Cards.h"
#include "HandScore.h"
#include <vector>
#include <algorithm>
#include <optional>
#include <array>
#include <stdexcept>

#include "HandEvaluator.h"

	// Every function here should have sorted cards in parameter

	std::optional<std::vector<Card>> HandEvaluator::checkForHighestStraightFlush(const std::vector<Card>& cardsToCheck)
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

	std::optional<std::vector<Card>> HandEvaluator::checkForFourOfAKind(const std::vector<Card>& cardsToCheck)
	{
		if (cardsToCheck.size() < 4) return std::nullopt;

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

	std::optional<std::vector<Card>> HandEvaluator::checkForFullHouse(const std::vector<Card>& cardsToCheck)
	{
		if (cardsToCheck.size() < 5) return std::nullopt;

		std::array<int, 14> rankCounts = { 0 };
		for (const auto& card : cardsToCheck)
		{
			rankCounts[(int)card.rank]++;
		}

		CardRank bestThreeRank = CardRank::NONE;
		CardRank bestTwoRank = CardRank::NONE;

		// Additional if (because ace is 1 in enum)
		if (rankCounts[(int)CardRank::ACE] >= 3)
		{
			bestThreeRank = CardRank::ACE;
		}
		else
		{
			for (int i = 13; i > 1; --i)
			{
				if (rankCounts[i] >= 3)
				{
					bestThreeRank = (CardRank)i;
					break;
				}
			}
		}

		if (bestThreeRank == CardRank::NONE) return std::nullopt;

		if (bestThreeRank != CardRank::ACE && rankCounts[(int)CardRank::ACE] >= 2)
		{
			bestTwoRank = CardRank::ACE;
		}
		else
		{
			for (int i = 13; i > 1; --i)
			{
				if (rankCounts[i] >= 2 && (CardRank)i != bestThreeRank)
				{
					bestTwoRank = (CardRank)i;
					break;
				}
			}
		}

		if (bestTwoRank == CardRank::NONE) return std::nullopt;

		std::vector<Card> usedCards;
		usedCards.reserve(5);

		std::vector<Card> usedForPair;
		usedForPair.reserve(2);

		int threesAdded = 0;
		int twosAdded = 0;
		for (const auto& card : cardsToCheck)
		{
			if (card.rank == bestThreeRank && threesAdded < 3)
			{
				usedCards.push_back(card);
				++threesAdded;
			}
			else if (card.rank == bestTwoRank && twosAdded < 2)
			{
				usedForPair.push_back(card);
				++twosAdded;
			}
		}

		for (const auto& card : usedForPair) usedCards.push_back(card);


		return usedCards;
	}

	std::optional<std::vector<Card>> HandEvaluator::checkForHighestFlush(const std::vector<Card>& cardsToCheck)
	{
		if (cardsToCheck.size() < 5) return std::nullopt;

		std::vector<Card> usedCards;
		usedCards.reserve(5);

		if (cardsToCheck.back().rank == CardRank::ACE)
		{
			usedCards.push_back(cardsToCheck.back());

			usedCards.insert(usedCards.end(), cardsToCheck.begin(), cardsToCheck.begin() + 4);
		}
		else
		{
			usedCards.insert(usedCards.end(), cardsToCheck.begin(), cardsToCheck.begin() + 5);
		}

		return usedCards;

	}

	std::optional<std::vector<Card>> HandEvaluator::checkForHighestStraight(const std::vector<Card>& cardsToCheck)
	{
		if (cardsToCheck.size() < 5) return std::nullopt;

		std::array<std::optional<Card>, 14> rankMap;

		for (const auto& card : cardsToCheck)
		{
			// we put first card of each rank into array
			if (!rankMap[(int)card.rank].has_value())
			{
				rankMap[(int)card.rank] = card;
			}
		}

		if (rankMap[(int)CardRank::ACE].has_value() && rankMap[(int)CardRank::KING].has_value() &&
			rankMap[(int)CardRank::QUEEN].has_value() && rankMap[(int)CardRank::JACK].has_value() && rankMap[(int)CardRank::TEN].has_value())
		{
			return std::vector<Card> {
				rankMap[(int)CardRank::ACE].value(), rankMap[(int)CardRank::KING].value(), rankMap[(int)CardRank::QUEEN].value(),
					rankMap[(int)CardRank::JACK].value(), rankMap[(int)CardRank::TEN].value()
			};
		}

		unsigned int counter = 0;

		for (int i = 13; i >= 1; --i)
		{
			if (rankMap[i].has_value())
			{
				++counter;
			}
			else counter = 0;
			if (counter == 5)
			{
				return std::vector<Card> {
					rankMap[i + 4].value(),
						rankMap[i + 3].value(),
						rankMap[i + 2].value(),
						rankMap[i + 1].value(),
						rankMap[i].value()
				};
			}
		}

		return std::nullopt;
	}

	std::optional<std::vector<Card>> HandEvaluator::checkForHighestThreeOfAKind(const std::vector<Card>& cardsToCheck)
	{
		if (cardsToCheck.size() < 3) return std::nullopt;

		std::array<int, 14> rankCounts = { 0 };
		for (const auto& card : cardsToCheck)
		{
			rankCounts[(int)card.rank]++;
		}

		CardRank foundThreeRank = CardRank::NONE;

		bool foundHand = false;
		if (rankCounts[(int)CardRank::ACE] >= 3)
		{
			foundThreeRank = CardRank::ACE;
			foundHand = true;
		}
		else {
			for (int i = 13; i > 1; --i)
			{
				if (rankCounts[i] >= 3)
				{
					foundThreeRank = static_cast<CardRank>(i);
					foundHand = true;
					break;
				}
			}
		}

		if (!foundHand) return std::nullopt;

		std::vector<Card> usedCards;
		usedCards.reserve(5);


		short foundKicker = 0;
		std::vector<Card> highestKickers;
		highestKickers.reserve(2);

		// Additional 'if' to use Ace as kicker
		if (rankCounts[1] > 0 && foundThreeRank != CardRank::ACE)
		{
			for (const auto& card : cardsToCheck)
			{
				if ((int)card.rank == 1)
				{
					highestKickers.push_back(card);
					++foundKicker;
					if (foundKicker > 1) break;
				}
			}
		}

		short threeCardsCounter = 0;

		// We put three of a kind cards into our vector to return
		for (const auto& card : cardsToCheck)
		{
			if (card.rank == foundThreeRank)
			{
				if (threeCardsCounter < 3) {
					usedCards.push_back(card);
					++threeCardsCounter;
				}

			}
			else if (foundKicker < 2)
			{
				highestKickers.push_back(card);
				++foundKicker;
			}
		}

		usedCards.insert(usedCards.end(), highestKickers.begin(), highestKickers.end());
		return usedCards;


	}

	std::optional<std::vector<Card>> HandEvaluator::checkForHighestTwoPair(const std::vector<Card>& cardsToCheck)
	{
		if (cardsToCheck.size() < 4) return std::nullopt;

		std::array<int, 14> rankCounts = { 0 };
		for (const auto& card : cardsToCheck)
		{
			rankCounts[(int)card.rank]++;
		}

		CardRank firstPairRank = CardRank::NONE;
		CardRank secondPairRank = CardRank::NONE;

		bool foundHand = false;

		if (rankCounts[(int)CardRank::ACE] >= 2)
		{
			firstPairRank = CardRank::ACE;
		}
		for (int i = 13; i > 1; --i)
		{
			if (rankCounts[i] >= 2)
			{
				if (firstPairRank == CardRank::NONE) {
					firstPairRank = static_cast<CardRank>(i);
				}
				else if (i != (int)firstPairRank)
				{
					secondPairRank = static_cast<CardRank>(i);
					foundHand = true;
					break;
				}

			}
		}


		if (!foundHand) return std::nullopt;

		std::vector<Card> usedCards;
		usedCards.reserve(5);


		bool foundKicker = false;
		Card highestKicker;

		// Additional 'if' to use Ace as kicker
		if (rankCounts[1] > 0 && firstPairRank != CardRank::ACE)
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


		short twoCardsCounter = 0;
		// We put two pair cards into our vector to return
		for (const auto& card : cardsToCheck)
		{
			if (card.rank == firstPairRank && twoCardsCounter < 2)
			{
				usedCards.push_back(card);
				++twoCardsCounter;
			}
		}

		twoCardsCounter = 0;

		for (const auto& card : cardsToCheck)
		{
			if (card.rank == secondPairRank && twoCardsCounter < 2)
			{
				usedCards.push_back(card);
				++twoCardsCounter;
			}
			else if (!foundKicker && card.rank != firstPairRank)
			{
				highestKicker = card;
				foundKicker = true;
			}
		}

		usedCards.push_back(highestKicker);
		return usedCards;
	}

	std::optional<std::vector<Card>> HandEvaluator::checkForHighestOnePair(const std::vector<Card>& cardsToCheck)
	{
		if (cardsToCheck.size() < 2) return std::nullopt;

		std::array<int, 14> rankCounts = { 0 };
		for (const auto& card : cardsToCheck)
		{
			rankCounts[(int)card.rank]++;
		}

		CardRank pairRank = CardRank::NONE;

		bool foundHand = false;

		if (rankCounts[(int)CardRank::ACE] >= 2)
		{
			pairRank = CardRank::ACE;
			foundHand = true;
		}
		else {
			for (int i = 13; i > 1; --i)
			{
				if (rankCounts[i] >= 2)
				{
					if (pairRank == CardRank::NONE) {
						pairRank = static_cast<CardRank>(i);
						foundHand = true;
						break;
					}

				}
			}
		}


		if (!foundHand) return std::nullopt;

		std::vector<Card> usedCards;
		usedCards.reserve(5);


		int foundKickersCounter = 3;
		std::vector<Card> highestKickers;

		// Additional 'if' to use Ace as kickers
		if (rankCounts[1] > 0 && pairRank != CardRank::ACE)
		{
			for (const auto& card : cardsToCheck)
			{
				if ((int)card.rank == 1)
				{
					highestKickers.push_back(card);
					--foundKickersCounter;
				}
			}
		}


		short twoCardsCounter = 0;
		// We put one pair cards into our vector to return
		for (const auto& card : cardsToCheck)
		{
			if (card.rank == pairRank && twoCardsCounter < 2)
			{
				usedCards.push_back(card);
				++twoCardsCounter;
			}
			else if (foundKickersCounter > 0 && card.rank != pairRank && card.rank != CardRank::ACE)
			{
				highestKickers.push_back(card);
				--foundKickersCounter;
			}
		}


		usedCards.insert(usedCards.end(), highestKickers.begin(), highestKickers.end());
		return usedCards;
	}

	std::optional<std::vector<Card>> HandEvaluator::checkForHighCard(const std::vector<Card>& cardsToCheck)
	{
		if (cardsToCheck.size() < 1) return std::nullopt;

		std::vector<Card> usedCards;
		usedCards.reserve(5);

		short usedAce = 0;
		short fiveCards = 5;

		if (cardsToCheck.back().rank == CardRank::ACE)
		{
			usedCards.push_back(cardsToCheck.back());
			usedAce = 1;
			--fiveCards;
		}


		for (size_t i = 0; i < cardsToCheck.size() - usedAce; i++)
		{
			if (fiveCards > 0)
			{
				usedCards.push_back(cardsToCheck[i]);
				--fiveCards;
			}

		}

		return usedCards;

	}

	HandScore HandEvaluator::Evaluate(std::vector<Card> allCardsInHand)
	{
		std::sort(allCardsInHand.begin(), allCardsInHand.end(), [](const Card& a, const Card& b) {return a.rank > b.rank; });


		std::array<std::vector<Card>, 5> suitBuckets;

		for (const Card& card : allCardsInHand)
		{
			suitBuckets[static_cast<int>(card.suit)].push_back(card);
		}

		for (const auto& bucket : suitBuckets)
		{
			if (bucket.size() < 5) continue;

			if (auto sfCards = checkForHighestStraightFlush(bucket))
			{
				if (sfCards.value().front().rank == CardRank::KING)
				{
					return HandScore{ PokerHand::ROYAL_FLUSH, sfCards.value() };
				}
				return HandScore{ PokerHand::STRAIGHT_FLUSH, sfCards.value() };
			}

		}

		if (auto usedCards = checkForFourOfAKind(allCardsInHand))
		{
			return HandScore{ PokerHand::FOUR_OF_A_KIND, usedCards.value() };
		}

		if (auto usedCards = checkForFullHouse(allCardsInHand))
		{
			return HandScore{ PokerHand::FULL_HOUSE, usedCards.value() };
		}

		for (const auto& bucket : suitBuckets)
		{
			if (bucket.size() < 5) continue;

			if (auto usedCards = checkForHighestFlush(bucket))
			{
				return HandScore{ PokerHand::FLUSH, usedCards.value() };
			}

		}

		if (auto usedCards = checkForHighestStraight(allCardsInHand))
		{
			return HandScore{ PokerHand::STRAIGHT, usedCards.value() };
		}

		if (auto usedCards = checkForHighestThreeOfAKind(allCardsInHand))
		{
			return HandScore{ PokerHand::THREE_OF_A_KIND, usedCards.value() };
		}

		if (auto usedCards = checkForHighestTwoPair(allCardsInHand))
		{
			return HandScore{ PokerHand::TWO_PAIR, usedCards.value() };
		}

		if (auto usedCards = checkForHighestOnePair(allCardsInHand))
		{
			return HandScore{ PokerHand::ONE_PAIR, usedCards.value() };
		}

		if (auto usedCards = checkForHighCard(allCardsInHand))
		{
			return HandScore{ PokerHand::HIGH_CARD, usedCards.value() };
		}


		throw std::invalid_argument("THERE WERE NOT ENOUGH CARDS TO EVALUATE HAND");


	}
