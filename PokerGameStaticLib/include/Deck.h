#pragma once

#include <vector>

#include "Cards.h"
#include "DeckType.h"

class Deck
{
private:
	std::vector<Card> deck{};
	DeckType deckType{};

	void addCards(int rankLimit);
public:
	Deck(DeckType deckType);
	Deck();
	void resetDeck();
	void shuffleDeck();
	Card drawCard();
	std::vector<Card> getDeck() const;
	int getCardsLeft() const;
};