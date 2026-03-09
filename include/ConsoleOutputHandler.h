#pragma once

#include "IOutputHandler.h"
#include "HandScore.h"
#include <string>

class ConsoleOutputHandler : public IOutputHandler
{
private:
	std::string getCardName(const Card& card) const;
	std::string getHandName(PokerHand hand) const;

public:
	void renderTable(const TableState& tableState) override;
};