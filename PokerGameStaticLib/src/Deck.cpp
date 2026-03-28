#include <vector>
#include <random>

#include "Deck.h"
#include "Cards.h"
#include "DeckType.h"

constexpr int MAX_RANKS = 14;


// [1, MAX_RANKS)

void Deck::addCards(int rankLimit)
{
	bool addingJokers = false;

	if (rankLimit <= 0) return;
	if (rankLimit > MAX_RANKS) {
		rankLimit = MAX_RANKS;
		addingJokers = true;
	}

	for (size_t suitNumber = 1; suitNumber < 5; suitNumber++)
	{
		for (size_t rankNumber = 1; rankNumber < rankLimit; rankNumber++)
		{
			Card card;
			card.suit = (CardSuit)suitNumber;
			card.rank = (CardRank)rankNumber;
			this->deck.push_back(card);
		}
	}
	if (addingJokers)
	{
		Card joker;
		joker.suit = CardSuit::NONE;
		joker.rank = CardRank::JOKER;
		this->deck.push_back(joker);
		this->deck.push_back(joker);
	}

}


Deck::Deck(DeckType deckType)
{
	this->deckType = deckType;
	resetDeck();
}

Deck::Deck()
{
	this->deckType = DeckType::STANDARD;
	resetDeck();
}

void Deck::resetDeck()
{
	int i = 0;
	switch (deckType)
	{
	case DeckType::STANDARD:
		i = 14;
		break;
	case DeckType::WITH_JOKERS:
		i = 15;
		break;
	default:
		break;
	}

	if (i > 0)
	{
		this->deck.clear();
		addCards(i);
	}

}

void Deck::shuffleDeck()
{
	std::mt19937 gen;
	std::random_device rd;
	gen.seed(rd());
	std::shuffle(deck.begin(), deck.end(), gen);
}

Card Deck::drawCard()
{
	if (this->deck.empty())
	{
		return Card{ CardSuit::NONE, CardRank::NONE };
	}

	Card drawedCard = this->deck.back();
	this->deck.pop_back();

	return drawedCard;
}

std::vector<Card> Deck::getDeck() const
{
	return this->deck;
}

unsigned int Deck::getCardsLeft() const
{
	return static_cast<unsigned int>(this->deck.size());
}