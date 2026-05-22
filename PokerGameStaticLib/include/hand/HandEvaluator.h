/**
 * @file HandEvaluator.h
 * @brief File containing declaration of HandEvaluator class
 */
#pragma once

#include "Cards.h"
#include "HandScore.h"
#include <vector>
#include <optional>

/**
 * @brief Class responsible for evaluating poker hands
 */
class HandEvaluator
{
private:

	// Every function here should have sorted cards in parameter

	/**
	 * @brief Checks for the highest possible Straight Flush
	 * @param cardsToCheck Sorted vector of cards
	 * @return Optional vector of 5 cards forming the hand
	 */
	static std::optional<std::vector<Card>> checkForHighestStraightFlush(const std::vector<Card>& cardsToCheck);
	
	/**
	 * @brief Checks for Four of a Kind
	 * @param cardsToCheck Sorted vector of cards
	 * @return Optional vector of 5 cards forming the hand
	 */
	static std::optional<std::vector<Card>> checkForFourOfAKind(const std::vector<Card>& cardsToCheck);

	/**
	 * @brief Checks for a Full House
	 * @param cardsToCheck Sorted vector of cards
	 * @return Optional vector of 5 cards forming the hand
	 */
	static std::optional<std::vector<Card>> checkForFullHouse(const std::vector<Card>& cardsToCheck);

	/**
	 * @brief Checks for the highest possible Flush
	 * @param cardsToCheck Sorted vector of cards
	 * @return Optional vector of 5 cards forming the hand
	 */
	static std::optional<std::vector<Card>> checkForHighestFlush(const std::vector<Card>& cardsToCheck);

	/**
	 * @brief Checks for the highest possible Straight
	 * @param cardsToCheck Sorted vector of cards
	 * @return Optional vector of 5 cards forming the hand
	 */
	static std::optional<std::vector<Card>> checkForHighestStraight(const std::vector<Card>& cardsToCheck);

	/**
	 * @brief Checks for Three of a Kind
	 * @param cardsToCheck Sorted vector of cards
	 * @return Optional vector of 5 cards forming the hand
	 */
	static std::optional<std::vector<Card>> checkForHighestThreeOfAKind(const std::vector<Card>& cardsToCheck);

	/**
	 * @brief Checks for the highest Two Pair
	 * @param cardsToCheck Sorted vector of cards
	 * @return Optional vector of 5 cards forming the hand
	 */
	static std::optional<std::vector<Card>> checkForHighestTwoPair(const std::vector<Card>& cardsToCheck);

	/**
	 * @brief Checks for the highest One Pair
	 * @param cardsToCheck Sorted vector of cards
	 * @return Optional vector of 5 cards forming the hand
	 */
	static std::optional<std::vector<Card>> checkForHighestOnePair(const std::vector<Card>& cardsToCheck);

	/**
	 * @brief Checks for the highest card
	 * @param cardsToCheck Sorted vector of cards
	 * @return Optional vector of 5 cards forming the hand
	 */
	static std::optional<std::vector<Card>> checkForHighCard(const std::vector<Card>& cardsToCheck);


public:
	/**
	 * @brief Evaluates a collection of cards to determine the best possible poker hand
	 * @param allCardsInHand Vector of cards to evaluate
	 * @return The evaluated score of the hand
	 */
	static HandScore Evaluate(std::vector<Card> allCardsInHand);

};