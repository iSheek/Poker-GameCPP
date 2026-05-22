/**
 * @file GameManager.h
 * @brief File containing declaration of GameManager class
 */
#pragma once

#include "Deck.h"
#include "Cards.h"
#include "PlayerLogicParent.h"
#include "IOutputHandler.h"
#include <memory>
#include <vector>

/**
 * @brief Class representing the game dealer and manager
 */
class GameManager
{
protected:
	std::vector<std::shared_ptr<PlayerLogicParent>> pPlayers{}; ///< The players at the table
	Deck deck{}; ///< The deck of cards used for the game

	TableState currentTableState{}; ///< The current state of the table

	std::vector<std::shared_ptr<IOutputHandler>> outputHandlers{}; ///< output handlers to use for rendering

	/**
	 * @brief Protected constructor for GameManager
	 * @param pOutputHandler The output handler to use
	 */
	GameManager(std::shared_ptr<IOutputHandler> pOutputHandler)
	{
		outputHandlers.push_back(pOutputHandler);
		currentTableState.currentHighestBet = 0;
		currentTableState.currentPot = 0;
	}

	GameManager(std::vector<std::shared_ptr<IOutputHandler>> outputHandlers) : outputHandlers(outputHandlers) {}

public:

	/**
	 * @brief Virtual destructor
	 */
	virtual ~GameManager() = default;

	/**
	 * @brief Adds a player to the game
	 * @param pPlayer Shared pointer to the player logic
	 */
	void addPlayer(std::shared_ptr<PlayerLogicParent> pPlayer)
	{
		this->pPlayers.push_back(pPlayer);
	}

	/**
	 * @brief Sets a new vector of output handlers
	 * @param newHandler vector of shared pointers to the new output handler
	 */
	void setPOutputHandler(const std::vector<std::shared_ptr<IOutputHandler>>& newHandler)
	{
		this->outputHandlers = newHandler;
	}

	/**
	 * @brief Adds an output handler to the game
	 * @param pOutputHandler Shared pointer to the output handler to add
	 */
	void addOutputHandler(std::shared_ptr<IOutputHandler> pOutputHandler)
	{
		this->outputHandlers.push_back(pOutputHandler);
	}

	/**
	 * @brief Plays a single round of the game
	 */
	virtual void playRound() = 0;

	/**
	 * @brief Gets the current number of players
	 * @return The number of players
	 */
	int getCurrentPlayerCount()
	{
		return static_cast<int>(this->pPlayers.size());
	}
};