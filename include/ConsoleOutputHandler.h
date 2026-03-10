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

	// TODO add definition for these and think whether to add addLog() also into interface
	
	void addLog(const std::string& message); 

public:
	ConsoleOutputHandler();
	~ConsoleOutputHandler();
	void renderTable(const TableState& tableState) override;
};