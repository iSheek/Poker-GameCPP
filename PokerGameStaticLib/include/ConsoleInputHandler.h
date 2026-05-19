#pragma once

/**
 * @file ConsoleInputHandler.h
 * @brief File containing declaration of ConsoleInputHandler class
 */

#include "IInputHandler.h"
#include "PlayerAction.h"
#include "PlayerState.h"
#include "TableState.h"
#include <vector>
#include <string>

 /**
  * @brief Class that handles input to the console from user
  */
class ConsoleInputHandler : public IInputHandler
{
private:
	/**
	 * @brief Method that asks user for value to raise
	 * @details It validates the input and allows user to go back when they enter 0
	 * @param[in] currentHighestBet highest bet currently
	 * @param[in] playersCurrentChips player's chips
	 * @param[in] xPlacement x coordinate for console to print
	 * @param[in] yPlacement y coordinate for console to print
	 * @return value from user to raise to
	 */
	int askForValueToRaise(int currentHighestBet, int playersCurrentChips, int xPlacement, int yPlacement);

	std::vector<std::vector<std::string>> playersCardsGraphics{}; ///< vector containing graphics for cards made from symbols for console

public:
	/** @copydoc IInputHandler::requestAction() */
	PlayerAction requestAction(const TableState& tableState, const PlayerState& playerState) override;
	
	/** @copydoc IInputHandler::onPlayersCardDealt() */
	void onPlayersCardDealt(const Card& card) override;
};