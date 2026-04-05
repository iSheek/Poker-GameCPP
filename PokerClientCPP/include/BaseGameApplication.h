#pragma once

#include "IOutputHandler.h"
#include "IInputHandler.h"

#include <string>
#include <memory>
#include <thread>

class BaseGameApplication
{
protected:
	std::string playerName{};
	std::shared_ptr<IOutputHandler> pOutput{};
	std::shared_ptr<IInputHandler> pInput{};

	std::unique_ptr<std::thread> pServerThread{};

	int startingChips{};

	int playerCount{};

public:
	
	void startSingleplayer();
	void startMultiplayer();

	virtual void run() = 0;

};