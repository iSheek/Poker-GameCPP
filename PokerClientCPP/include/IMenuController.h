#pragma once

#include "MenuChoice.h"
#include "GameSettings.h"
#include <string>

class IMenuController
{
public:
	virtual MenuChoice askForMenuChoice() = 0;
	virtual std::string askForNickname() = 0;
	virtual std::string askForIP() = 0;
	virtual int askForPortToConnect() = 0;
	virtual int askForPortToCreate() = 0;
	virtual int askForBotsCount() = 0;
	virtual int askForPlayerCount() = 0;
	virtual GameSettings runAndGetSettings() = 0;
};