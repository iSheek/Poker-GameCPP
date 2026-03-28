#pragma once

#include <string>
#include <nlohmann/json.hpp>

struct PublicPlayerInfo
{
	std::string name;
	unsigned int chips = 0;
	unsigned int currentBet = 0;
	unsigned int totalBet = 0;
	bool hasFolded = true;
};


NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PublicPlayerInfo, name, chips, currentBet, totalBet, hasFolded)