#pragma once

/**
 * @file IMenuView.h
 * @brief File containing declaration of IMenuView interface
 */

#include <string_view>

/**
 * @brief Interface for view layer of the game's main menu.
 *
 * @details This interface defines the contract for displaying menu prompts, 
 * options, and error messages to the user. It isolates the visual output 
 * logic (e.g., console printing, GUI rendering) from the controller logic.
 * 
 */

class IMenuView
{

public:
	/**
	 * @brief Virtual destructor to ensure proper cleanup of derived classes.
	 */
	virtual ~IMenuView() = default;
	
	/**
	 * @brief Displays the main menu options.
	 * @details Shows the available game modes (e.g., Singleplayer, Multiplayer, Join) and the exit option.
	 */
	virtual void showMenuChoices() = 0;

	/**
	 * @brief Handles visual part of asking the user for their nickname.
	 */
	virtual void showNicknameInput() = 0;

	/**
	 * @brief Handles visual part of asking the user for an IPv4 address to connect to.
	 */
	virtual void showIPInput() = 0;

	/**
	 * @brief Handles visual part of asking the user for a target port to connect as a client.
	 */
	virtual void showPortConnectInput() = 0;

	/**
	 * @brief Handles visual part of asking the user for a port to open for hosting a server.
	 */
	virtual void showPortCreateInput() = 0;

	/**
	 * @brief Handles visual part of asking the user for the desired number of AI bots.
	 */
	virtual void showBotCountInput() = 0;

	/**
	 * @brief Handles visual part of asking the user for the total number of players in the game.
	 */
	virtual void showPlayerCountInput() = 0;

	/**
	 * @brief Handles visual part of asking the user for the starting amount of chips.
	 */
	virtual void showStartingChipsInput() = 0;

	/**
	 * @brief Displays a specific error message to the user.
	 *
	 * @param error A string_view containing the detailed error message to be shown.
	 */
	virtual void showError(std::string_view error) = 0;
};