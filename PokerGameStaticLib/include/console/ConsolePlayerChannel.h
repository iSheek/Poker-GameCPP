/**
 * @file ConsolePlayerChannel.h
 * @brief File containing declaration of ConsolePlayerChannel class
 */
#pragma once

#include "IPlayerChannel.h"
#include "PlayerAction.h"
#include "PlayerState.h"
#include "TableState.h"
#include "HandScore.h"
#include <string>
#include <string_view>
#include <fstream>

#include <vector>

/**
 * @brief Class handling game input and output via the system console
 * @details Implements the IPlayerChannel interface to provide a text-based UI,
 * using ANSI escape sequences for positioning and graphics.
 */
class ConsolePlayerChannel : public IPlayerChannel
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


	std::vector<std::string> uiLogs{}; ///< Vector holding the log messages to display

	std::ofstream logFile{}; ///< Output file stream for logging

	/**
	 * @brief Adds a message to the UI logs
	 * @param message The message to log
	 */
	void addLog(std::string_view message);

	/**
	 * @brief Clears or prepares the console for a fresh render
	 */
	void startOverwritingConsole();

	/**
	 * @brief Gets the current width of the console window
	 * @return Console width in characters
	 */
	int getConsoleWidth();

	/**
	 * @brief Verifies if the console window is large enough for the UI
	 */
	void checkIfConsoleSizeIsEnough();

	/**
	 * @brief Gets a string representation of the current best hand
	 * @param communityCards Cards on the table
	 * @param playersCards Cards held by the player
	 * @return String description of the hand
	 */
	std::string getCurrentHandString(const std::vector<Card>& communityCards, const std::array<Card, 2>& playersCards) const;


	std::vector<std::vector<std::string>> communityCardsGraphics{}; ///< Pre-rendered graphics for community cards

	/**
	 * @brief Converts a PlayerAction to its string representation
	 * @param action The action to convert
	 * @return String describing the action
	 */
	std::string actionToString(PlayerAction action);


public:
	/**
	 * @brief Constructor for ConsoleOutputHandler
	 */
	ConsolePlayerChannel();

	/**
	 * @brief Destructor for ConsoleOutputHandler
	 */
	~ConsolePlayerChannel();

	/** @copydoc IInputHandler::requestAction */
	PlayerAction requestAction(const TableState& tableState, const PlayerState& playerState) override;

	/** @copydoc IInputHandler::onPlayersCardDealt */
	void onPlayersCardDealt(const Card& card) override;

	/** @copydoc IOutputHandler::renderTable */
	void renderTable(const TableState& tableState, const std::vector<PublicPlayerInfo>& publicPlayersInfo) override;

	/** @copydoc IOutputHandler::onCommunityCardDealt */
	void onCommunityCardDealt(const Card& card) override;

	/** @copydoc IOutputHandler::onPlayerAction */
	void onPlayerAction(const std::string& playerName, const PlayerAction& action) override;

	/** @copydoc IOutputHandler::onShowdown */
	void onShowdown(const ShowdownResult& showdownResult) override;
};