/**
 * @file IInputHandler.h
 * @brief File containing declaration of IInputHandler interface
 */
#pragma once

#include "PlayerAction.h"
#include "TableState.h"
#include "PlayerState.h"
#include "Cards.h"
#include <array>

// TODO: CHANGE INPUT AND OUTPUT HANDLERS INTO PROPER MVC

/**
 * @brief Interface for handling user input during the game
 */
class IInputHandler
{
public:
	/**
	 * @brief Requests an action from the player
	 * @param tableState The current state of the table
	 * @param playerState The current state of the player
	 * @return The action taken by the player
	 */
	virtual PlayerAction requestAction(const TableState& tableState, const PlayerState& playerState) = 0;
	
	/**
	 * @brief Callback for when a card is dealt to the player
	 * @param card The dealt card
	 */
	virtual void onPlayersCardDealt(const Card& card) = 0;
	
	/**
	 * @brief Virtual destructor
	 */
	virtual ~IInputHandler() = default;
};