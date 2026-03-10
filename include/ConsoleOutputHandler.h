#pragma once

#include "IOutputHandler.h"
#include "HandScore.h"
#include <string>
#include <fstream>

class ConsoleOutputHandler : public IOutputHandler
{
private:
	std::string getCardName(const Card& card) const;
	std::string getHandName(PokerHand hand) const;

	std::vector<std::string> uiLogs;

	std::ofstream logFile;

	
	void addLog(const std::string& message); 

public:
	ConsoleOutputHandler();
	~ConsoleOutputHandler();
	void renderTable(const TableState& tableState) override;

	void onPlayerAction(const std::string& playerName, PlayerAction action) override;
	void onShowdown(const std::vector<std::shared_ptr<PlayerLogicParent>>& winners, const HandScore& winningHand, unsigned int pot) override;
};