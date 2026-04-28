#pragma once

#include <string>


struct GameSettings
{
	bool isMultiplayer{false};
	bool isHost{ false };
	std::string nickname{};
	std::string ipAddress{};
	int port{};
	int startingChips{};
	int playerCount{};

	friend bool operator==(const GameSettings& a, const GameSettings& b) {
		if (a.isMultiplayer == b.isMultiplayer
			&& a.isHost == b.isHost
			&& a.nickname == b.nickname
			&& a.ipAddress == b.ipAddress
			&& a.port == b.port
			&& a.startingChips == b.startingChips
			&& a.playerCount == b.playerCount)
		{
			return true;
		}
		return false;
	}
};