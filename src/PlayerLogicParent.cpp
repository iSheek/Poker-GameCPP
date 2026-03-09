#include "PlayerLogicParent.h"
#include <cstdint>

void PlayerLogicParent::addChips(unsigned int chipsToAdd)
{
	if (UINT32_MAX - this->playersChips < chipsToAdd)
	{
		this->playersChips = UINT32_MAX;
	}
	else this->playersChips += chipsToAdd;
}

void PlayerLogicParent::removeChips(unsigned int chipsToRemove)
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

void PlayerLogicParent::resetPlayer(unsigned int startingChips)
{
	resetCards();
	resetChips();
	this->playersChips = startingChips;
	this->hasFolded = false;
	this->currentBet = 0;
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
}