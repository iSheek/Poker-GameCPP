#pragma once

/**
 * @file IMenuController.h
 * @brief File containing declaration of IMenuController interface
 */

#include "MenuChoice.h"
#include "GameSettings.h"
#include <string>


/**
 * @brief Interface for controlling the game's pre-match menu.
 *
 * @details This interface defines the contract for any menu controller
 * implementation (e.g., console-based, GUI-based). It abstracts the process
 * of gathering user input required to configure and start a game session.
 */
class IMenuController
{
public:
	/**
	 * @brief Virtual destructor to ensure proper cleanup of derived classes.
	 */
	virtual ~IMenuController() = default;
	
	/**
	 * @brief Handles input from user to select an option from the main menu.
	 * @return The selected MenuChoice struct.
	 */
	virtual MenuChoice askForMenuChoice() = 0;

	/**
	 * @brief Handles input from user for their desired nickname.
	 * @return The player's chosen nickname as a string.
	 */
	virtual std::string askForNickname() = 0;

	/**
	 * @brief Handles input from user to enter an IP address for a multiplayer connection.
	 * @return The target IP address as a string.
	 */
	virtual std::string askForIP() = 0;

	/**
	 * @brief Handles input from user to specify the port number to connect to an existing server.
	 * @return The port number for the client connection.
	 */
	virtual int askForPortToConnect() = 0;

	/**
	 * @brief Handles input from user to define a port number for hosting a new multiplayer server.
	 * @return The port number to open for hosting.
	 */
	virtual int askForPortToCreate() = 0;

	/**
	 * @brief Handles input from user for how many AI bots they want to include in the game.
	 * @return The requested number of bots.
	 */
	virtual int askForBotsCount() = 0;

	/**
	 * @brief Handles input from user for the total number of players in a hosted multiplayer match.
	 * @return The total player count.
	 */
	virtual int askForPlayerCount() = 0;

	/**
	 * @brief Handles input from user to specify the starting amount of chips for each player.
	 * @return The starting chip amount.
	 */
	virtual int askForStartingChips() = 0;

	/**
	 * @brief Executes the main menu loop and gathers all necessary game configurations.
	 *
	 * @details Orchestrates the sequence of prompts based on whether the user
	 * wants to play single-player, host a game, or join a game.
	 *
	 * @return A fully populated GameSettings struct based on the user's choices.
	 */
	virtual GameSettings runAndGetSettings() = 0;
};