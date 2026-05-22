/**
 * @file Deck.h
 * @brief File containing declaration of Deck class
 */
#pragma once

#include <vector>

#include "Cards.h"
#include "DeckType.h"

/**
 * @brief Class representing a deck of cards
 */
class Deck
{
private:
	std::vector<Card> deck{}; ///< Internal vector storing the cards
	DeckType deckType{}; ///< The type of deck being used

	/**
	 * @brief Adds cards to the deck up to a specified rank limit
	 * @param rankLimit The limit of ranks to add
	 */
	void addCards(int rankLimit);
public:
	/**
	 * @brief Constructor with specified deck type
	 * @param deckType The type of deck to create
	 */
	Deck(DeckType deckType);
	
	/**
	 * @brief Default constructor
	 */
	Deck();
	
	/**
	 * @brief Resets the deck to its initial state
	 */
	void resetDeck();
	
	/**
	 * @brief Shuffles the cards in the deck
	 */
	void shuffleDeck();
	
	/**
	 * @brief Draws a card from the deck
	 * @return The drawn card
	 */
	Card drawCard();
	
	/**
	 * @brief Gets the current deck of cards
	 * @return Vector of cards in the deck
	 */
	std::vector<Card> getDeck() const;
	
	/**
	 * @brief Gets the number of cards left in the deck
	 * @return Number of remaining cards
	 */
	int getCardsLeft() const;
};