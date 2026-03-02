#pragma once

enum class CardSuit
{
	NONE = -1,

	DIAMONDS = 1,
	CLUBS,
	HEARTS,
	SPADES
};

enum class CardRank
{
	NONE = -1,

	ACE = 1,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,

	JACK,
	QUEEN,
	KING,

	JOKER
};

struct Card
{
	CardSuit suit = CardSuit::NONE;
	CardRank rank = CardRank::NONE;

	bool operator>(const Card& other)
	{
		return rank > other.rank;
	}
};