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

	std::vector<std::string> generateCardGraphic(const Card& card);

	std::vector<std::vector<std::string>> communityCardsGraphics;

	std::vector<std::vector<std::string>> playersCardsGraphics;
	

public:
	ConsoleOutputHandler();
	~ConsoleOutputHandler();
	void renderTable(const TableState& tableState) override;

	void onCommunityCardDealt(const Card& card) override;
	void onPlayerAction(const std::string& playerName, PlayerAction action) override;
	void onShowdown(const std::vector<std::shared_ptr<PlayerLogicParent>>& winners, const HandScore& winningHand, unsigned int pot) override;
};