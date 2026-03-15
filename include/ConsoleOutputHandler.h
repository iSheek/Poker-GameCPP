#pragma once

#include "IOutputHandler.h"
#include "HandScore.h"
#include <string>
#include <fstream>

class ConsoleOutputHandler : public IOutputHandler
{
private:

	std::vector<std::string> uiLogs;

	std::ofstream logFile;

	
	void addLog(const std::string& message); 

	void startOverwritingConsole();

	int getConsoleWidth();

	void checkIfConsoleSizeIsEnough();

	std::string getCurrentHandString(const std::vector<Card>& communityCards, const std::array<Card, 2>& playersCards) const;


	std::vector<std::vector<std::string>> communityCardsGraphics;

	std::string actionToString(PlayerAction action);
	

public:
	ConsoleOutputHandler();
	~ConsoleOutputHandler();
	void renderTable(const TableState& tableState, const std::vector<PublicPlayerInfo>& publicPlayersInfo) override;

	void onCommunityCardDealt(const Card& card) override;
	void onPlayerAction(const std::string& playerName, const PlayerAction& action) override;
	void onShowdown(const std::vector<std::string>& winnerNames, const HandScore& winningHand, const unsigned int& pot) override;
};