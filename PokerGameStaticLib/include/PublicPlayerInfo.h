#pragma once

#include <string>
#include <nlohmann/json.hpp>

struct PublicPlayerInfo
{
	std::string name{};
	int chips{};
	int currentBet{};
	int totalBet{};
	bool hasFolded{ true };
};


NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PublicPlayerInfo, name, chips, currentBet, totalBet, hasFolded)