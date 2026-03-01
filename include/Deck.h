#pragma once

#include <vector>

#include "Cards.h"
#include "DeckType.h"

class Deck
{
private:
	std::vector<Card> deck;
	DeckType deckType;

	void addCards(int& rankLimit);
public:
	Deck(DeckType deckType);
	void resetDeck();
	void shuffleDeck();
	Card drawCard();
};