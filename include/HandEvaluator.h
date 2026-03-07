#pragma once

#include "Cards.h"
#include "HandScore.h"
#include <vector>
#include <optional>


class HandEvaluator
{
private:

	// Every function here should have sorted cards in parameter

	static std::optional<std::vector<Card>> checkForHighestStraightFlush(const std::vector<Card>& cardsToCheck);
	
	static std::optional<std::vector<Card>> checkForFourOfAKind(const std::vector<Card>& cardsToCheck);

	static std::optional<std::vector<Card>> checkForFullHouse(const std::vector<Card>& cardsToCheck);

	static std::optional<std::vector<Card>> checkForHighestFlush(const std::vector<Card>& cardsToCheck);

	static std::optional<std::vector<Card>> checkForHighestStraight(const std::vector<Card>& cardsToCheck);

	static std::optional<std::vector<Card>> checkForHighestThreeOfAKind(const std::vector<Card>& cardsToCheck);

	static std::optional<std::vector<Card>> checkForHighestTwoPair(const std::vector<Card>& cardsToCheck);

	static std::optional<std::vector<Card>> checkForHighestOnePair(const std::vector<Card>& cardsToCheck);

	static std::optional<std::vector<Card>> checkForHighCard(const std::vector<Card>& cardsToCheck);


public:
	static HandScore Evaluate(std::vector<Card> allCardsInHand);

};