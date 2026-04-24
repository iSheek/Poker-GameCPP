#pragma once

#include <string>


struct GameSettings
{
	bool isMultiplayer{false};
	std::string nickname{};
	std::string ipAddress{};
	int port{};
	int startingChips{};
	int playerCount{};
};