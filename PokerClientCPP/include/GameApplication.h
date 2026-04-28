#pragma once

#include "IOutputHandler.h"
#include "IInputHandler.h"
#include "GameSettings.h"
#include "ConsoleOutputHandler.h"
#include "ConsoleInputHandler.h"

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

	bool isHost{ false };

public:
	GameApplication() = default;
	GameApplication(GameSettings gameSettings) : 
		playerName(gameSettings.nickname), 
		ipAddress(gameSettings.ipAddress), 
		startingChips(gameSettings.startingChips), 
		playerCount(gameSettings.playerCount), 
		port(gameSettings.port), 
		isHost(gameSettings.isHost),
		pOutput(std::make_shared<ConsoleOutputHandler>()), 
		pInput(std::make_shared<ConsoleInputHandler>()) 
	{}
	
	GameApplication(GameSettings gameSettings, std::shared_ptr<IOutputHandler> pOutput, std::shared_ptr<IInputHandler> pInput) : 
		playerName(gameSettings.nickname), 
		isHost(gameSettings.isHost), 
		ipAddress(gameSettings.ipAddress),
		startingChips(gameSettings.startingChips), 
		playerCount(gameSettings.playerCount), 
		port(gameSettings.port),
		pOutput(pOutput), 
		pInput(pInput) 
	{}

	void startSingleplayer();
	void startMultiplayer();

};