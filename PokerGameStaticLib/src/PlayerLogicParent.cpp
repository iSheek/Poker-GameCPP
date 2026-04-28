#include "PlayerLogicParent.h"
#include <cstdint>

void PlayerLogicParent::addChips(int chipsToAdd)
{
	if (INT32_MAX - this->playersChips < chipsToAdd)
	{
		this->playersChips = INT32_MAX;
	}
	else this->playersChips += chipsToAdd;
}

void PlayerLogicParent::removeChips(int chipsToRemove)
{
	if (chipsToRemove > this->playersChips)
	{
		this->playersChips = 0;
	}
	else this->playersChips -= chipsToRemove;
}

void PlayerLogicParent::resetCards()
{
	this->playersCards[0] = { CardSuit::NONE, CardRank::NONE };
	this->playersCards[1] = { CardSuit::NONE, CardRank::NONE };
}

void PlayerLogicParent::resetChips()
{
	this->playersChips = 0;
}

void PlayerLogicParent::resetPlayer(int startingChips)
{
	resetCards();
	resetChips();
	this->playersChips = startingChips;
	this->hasFolded = false;
	this->currentBet = 0;
	this->totalBet = 0;
}

void PlayerLogicParent::setCards(const Card& firstCard, const Card& secondCard)
{
	this->playersCards[0] = firstCard;
	this->playersCards[1] = secondCard;
}

void PlayerLogicParent::resetForNewRound()
{
	resetFold();
	resetCards();
	setCurrentBet(0);
	setTotalBet(0);
}