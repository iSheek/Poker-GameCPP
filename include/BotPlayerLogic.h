#pragma once

#include "PlayerLogicParent.h"
#include <string>

class BotPlayerLogic : public PlayerLogicParent
{
private:
	int aggressiveLevel;

	std::string getRandomNameFromFile();

public:
	BotPlayerLogic(unsigned int startingChips);
	BotPlayerLogic(unsigned int startingChips, int aggressiveLevel);

	PlayerAction makeDecision(const TableState& state) override;


};
