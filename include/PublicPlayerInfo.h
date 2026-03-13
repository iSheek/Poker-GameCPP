#pragma once

#include <string>

struct PublicPlayerInfo
{
	std::string name;
	unsigned int chips = 0;
	unsigned int currentBet = 0;
	unsigned int totalBet = 0;
	bool hasFolded = true;
};