#pragma once

#include "IOutputHandler.h"
#include "IInputHandler.h"
#include "GameSettings.h"

#include <string>
#include <memory>
#include <thread>

class GameApplication
{
private:
	std::string playerName{};
	std::shared_ptr<IOutputHandler> pOutput{};
	std::shared_ptr<IInputHandler> pInput{};

	std::unique_ptr<std::thread> pServerThread{};

	int startingChips{};

	int playerCount{};

	int port{};
	std::string ipAddress{};

public:
	GameApplication() = default;
	GameApplication(GameSettings gameSettings) : playerName(gameSettings.nickname), ipAddress(gameSettings.ipAddress), startingChips(gameSettings.startingChips), playerCount(gameSettings.playerCount), port(gameSettings.port) {}
	
	void startSingleplayer();
	void startMultiplayer();

};