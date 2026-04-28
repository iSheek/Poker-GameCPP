#pragma once

#include "PlayerAction.h"
#include "Cards.h"
#include "TableState.h"
#include <array>
#include <string>


class PlayerLogicParent
{
private:
	std::array<Card, 2> playersCards{};
	int playersChips{};
	bool hasFolded{};
	int currentBet{};
	int totalBet{};

	std::string playerName{};
protected:
	PlayerLogicParent(int startingChips)
	{
		resetPlayer(startingChips);
	}

public:

	virtual ~PlayerLogicParent() = default;

	virtual PlayerAction makeDecision(const TableState& state) = 0;

	void setCards(const Card& firstCard, const Card& secondCard);

	void setChips(int playersChips)
	{
		this->playersChips = playersChips;
	}

	void addChips(int chipsToAdd);
	
	void removeChips(int chipsToRemove);

	int getChips() const
	{
		return this->playersChips;
	}

	std::array<Card, 2> getPlayerCards() const
	{
		return this->playersCards;
	}

	void resetCards();

	void resetChips();

	void fold()
	{
		this->hasFolded = true;
	}

	bool getHasFolded() const
	{
		return this->hasFolded;
	}

	void resetFold()
	{
		this->hasFolded = false;
	}

	void setCurrentBet(int bet)
	{
		this->currentBet = bet;
	}

	int getCurrentBet() const
	{
		return this->currentBet;
	}

	void addToCurrentBet(int amountToAdd)
	{
		this->currentBet += amountToAdd;
	}

	void resetPlayer(int startingChips);

	void resetForNewRound();

	std::string getPlayerName() const
	{
		return this->playerName;
	}

	void setPlayerName(std::string_view newName)
	{
		if (!newName.empty()) this->playerName = newName;
	}

	int getTotalBet() const
	{
		return this->totalBet;
	}

	void setTotalBet(int newTotalBet)
	{
		this->totalBet = newTotalBet;
	}

	void addToTotalBet(int amountToAdd)
	{
		this->totalBet += amountToAdd;
	}
};