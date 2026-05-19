#pragma once

/**
 * @file ConsoleMenuController.h
 * @brief File containing declaration of ConsoleMenuController class
 */


#include "IMenuController.h"
#include "ConsoleMenuView.h"



/**
 * @brief Controller for the console-based menu.
 *
 * @details Implements the IMenuController interface to handle user input
 * via the standard console. Uses ConsoleMenuView to display prompts.
 */ 
class ConsoleMenuController : public IMenuController
{
private:
	ConsoleMenuView &view;			 ///< Reference to the view responsible for console output.

	/**
	 * @brief Executes the step-by-step configuration for a single-player game.
	 *
	 * @details Walks the user through inputting their nickname, bot count, and starting chips.
	 * Supports a rollback mechanism where inputting "0" goes back to the previous step.
	 *
	 * @return A GameSettings struct configured for a single-player match.
	 */
	GameSettings configureStartSingleplayer();
	
	/**
	 * @brief Executes the step-by-step configuration for hosting a multiplayer game.
	 *
	 * @details Walks the user through inputting their nickname, hosting port, player count,
	 * and starting chips. Defaults the IP address to localhost.
	 * Supports a rollback mechanism where inputting "0" goes back to the previous step.
	 *
	 * @return A GameSettings struct configured for hosting a multiplayer match.
	 */
	GameSettings configureStartMultiplayer();

	/**
	 * @brief Executes the step-by-step configuration for joining an existing multiplayer game.
	 *
	 * @details Walks the user through inputting their nickname, the server's IP address,
	 * and the connection port.
	 * Supports a rollback mechanism where inputting "0" goes back to the previous step.
	 *
	 * @return A GameSettings struct configured for joining a multiplayer match.
	 */
	GameSettings configureJoinMultiplayer();

public:
	/**
	 * @brief Constructs the ConsoleMenuController.
	 * @param givenViewRef Reference to the ConsoleMenuView to be used.
	 */
	ConsoleMenuController(ConsoleMenuView& givenViewRef) : view(givenViewRef) {}

	/** 
	 * @copydoc IMenuController::askForMenuChoice() 
	 *
	 * @note Loops until a valid choice within the defined enum bounds is provided.
	 * Displays an error message via the view if an invalid input is detected.
	 */
	virtual MenuChoice askForMenuChoice() override;

	/** @copydoc IMenuController::askForNickname() 
	 *
	 * @note Validates the input to ensure it contains only alphabetical characters.
	 * If the user inputs "0", it acts as a signal to go back to the previous menu step.
	 * Returns "0" if user want to go back.
	 */
	virtual std::string askForNickname() override;

	/** @copydoc IMenuController::askForIP() 
	 * 
	 * @note Prompts the user to enter an IP address for connecting to a server.
	 * 
	 */
	virtual std::string askForIP() override;

	/** @copydoc IMenuController::askForPortToConnect() */
	virtual int askForPortToConnect() override;

	/** @copydoc IMenuController::askForPortToCreate() */
	virtual int askForPortToCreate() override;

	/** @copydoc IMenuController::askForBotsCount() 
	 * @note Validates that the input is between 0 and maxBots (3). 
	 * Inputting 0 serves as a signal to step back in the menu.
	 */
	virtual int askForBotsCount() override;

	/** @copydoc IMenuController::askForPlayerCount() */
	virtual int askForPlayerCount() override;

	/** @copydoc IMenuController::askForStartingChips() */
	virtual int askForStartingChips() override;

	/** @copydoc IMenuController::runAndGetSettings() 
	 *
	 * @note Prompts the user for their initial menu choice and directs them 
	 * to the corresponding setup workflow (Singleplayer, Host Multiplayer, Join Multiplayer).
	 * Handles the exit condition by returning a specific settings state (port = -1). 
	 * 
	 */
	virtual GameSettings runAndGetSettings() override;
};