#pragma once

#include "PlayerLogicParent.h"
#include <random>
#include <string>

class BotPlayerLogic : public PlayerLogicParent
{
private:
	int aggressiveLevel{};

	std::random_device rd{};
	std::mt19937 gen{};

	std::string getRandomNameFromFile();

public:
	BotPlayerLogic(int startingChips);
	BotPlayerLogic(int startingChips, int aggressiveLevel);

	PlayerAction makeDecision(const TableState& state) override;


};
