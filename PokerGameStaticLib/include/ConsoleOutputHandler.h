/**
 * @file ConsoleOutputHandler.h
 * @brief File containing declaration of ConsoleOutputHandler class
 */
#pragma once

#include "IOutputHandler.h"
#include "HandScore.h"
#include <string>
#include <string_view>
#include <fstream>

/**
 * @brief Class handling game output to the console
 */
class ConsoleOutputHandler : public IOutputHandler
{
private:

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
	ConsoleOutputHandler();
	
	/**
	 * @brief Destructor for ConsoleOutputHandler
	 */
	~ConsoleOutputHandler();
	
	/** @copydoc IOutputHandler::renderTable() */
	void renderTable(const TableState& tableState, const std::vector<PublicPlayerInfo>& publicPlayersInfo) override;

	/** @copydoc IOutputHandler::onCommunityCardDealt() */
	void onCommunityCardDealt(const Card& card) override;
	
	/** @copydoc IOutputHandler::onPlayerAction() */
	void onPlayerAction(const std::string& playerName, const PlayerAction& action) override;
	
	/** @copydoc IOutputHandler::onShowdown() */
	void onShowdown(const std::vector<std::string>& winnerNames, const HandScore& winningHand, const int& pot) override;
};