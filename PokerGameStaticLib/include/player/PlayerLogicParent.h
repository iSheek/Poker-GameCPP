/**
 * @file PlayerLogicParent.h
 * @brief File containing declaration of PlayerLogicParent class
 */
#pragma once

#include "PlayerAction.h"
#include "Cards.h"
#include "TableState.h"
#include <array>
#include <string>

/**
 * @brief Abstract base class representing logic for any player in the game
 */
class PlayerLogicParent
{
private:
	std::array<Card, 2> playersCards{}; ///< The two hole cards of the player
	int playersChips{}; ///< The amount of chips the player owns
	bool hasFolded{}; ///< Flag indicating if the player folded
	int currentBet{}; ///< Current bet placed in the active betting phase
	int totalBet{}; ///< Total bet placed in the current round

	std::string playerName{}; ///< The player's display name
protected:
	/**
	 * @brief Constructor initializing player with starting chips
	 * @param startingChips Amount of chips to start with
	 */
	PlayerLogicParent(int startingChips)
	{
		resetPlayer(startingChips);
	}

public:

	/**
	 * @brief Virtual destructor
	 */
	virtual ~PlayerLogicParent() = default;

	/**
	 * @brief Prompts the player logic to make a decision based on table state
	 * @param state Current state of the table
	 * @return The action chosen by the player
	 */
	virtual PlayerAction makeDecision(const TableState& state) = 0;

	/**
	 * @brief Gives two cards to the player
	 * @param firstCard The first card
	 * @param secondCard The second card
	 */
	void setCards(const Card& firstCard, const Card& secondCard);

	/**
	 * @brief Sets the player's chip count
	 * @param playersChips The new amount of chips
	 */
	void setChips(int playersChips)
	{
		this->playersChips = playersChips;
	}

	/**
	 * @brief Adds chips to the player's stack
	 * @param chipsToAdd Amount to add
	 */
	void addChips(int chipsToAdd);
	
	/**
	 * @brief Removes chips from the player's stack
	 * @param chipsToRemove Amount to remove
	 */
	void removeChips(int chipsToRemove);

	/**
	 * @brief Gets the player's current chip count
	 * @return Amount of chips
	 */
	int getChips() const
	{
		return this->playersChips;
	}

	/**
	 * @brief Gets the player's hole cards
	 * @return Array of two cards
	 */
	std::array<Card, 2> getPlayerCards() const
	{
		return this->playersCards;
	}

	/**
	 * @brief Resets the player's cards
	 */
	void resetCards();

	/**
	 * @brief Sets the player's chip count to 0
	 */
	void resetChips();

	/**
	 * @brief Marks the player as folded
	 */
	void fold()
	{
		this->hasFolded = true;
	}

	/**
	 * @brief Checks if the player has folded
	 * @return True if folded, false otherwise
	 */
	bool getHasFolded() const
	{
		return this->hasFolded;
	}

	/**
	 * @brief Resets the fold status
	 */
	void resetFold()
	{
		this->hasFolded = false;
	}

	/**
	 * @brief Sets the current bet amount
	 * @param bet New bet amount
	 */
	void setCurrentBet(int bet)
	{
		this->currentBet = bet;
	}

	/**
	 * @brief Gets the current bet amount
	 * @return Current bet
	 */
	int getCurrentBet() const
	{
		return this->currentBet;
	}

	/**
	 * @brief Adds to the current bet
	 * @param amountToAdd Amount to add
	 */
	void addToCurrentBet(int amountToAdd)
	{
		this->currentBet += amountToAdd;
	}

	/**
	 * @brief Fully resets the player for a new game
	 * @param startingChips Amount of starting chips
	 */
	void resetPlayer(int startingChips);

	/**
	 * @brief Resets the player's temporary state for a new round
	 */
	void resetForNewRound();

	/**
	 * @brief Gets the player's name
	 * @return The player's name
	 */
	std::string getPlayerName() const
	{
		return this->playerName;
	}

	/**
	 * @brief Sets the player's name
	 * @param newName The new name
	 */
	void setPlayerName(std::string_view newName)
	{
		if (!newName.empty()) this->playerName = newName;
	}

	/**
	 * @brief Gets the total bet for the round
	 * @return Total bet amount
	 */
	int getTotalBet() const
	{
		return this->totalBet;
	}

	/**
	 * @brief Sets the total bet for the round
	 * @param newTotalBet New total bet amount
	 */
	void setTotalBet(int newTotalBet)
	{
		this->totalBet = newTotalBet;
	}

	/**
	 * @brief Adds to the total bet amount
	 * @param amountToAdd Amount to add
	 */
	void addToTotalBet(int amountToAdd)
	{
		this->totalBet += amountToAdd;
	}
};