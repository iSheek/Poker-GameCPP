#pragma once

#include "MenuChoice.h"
#include <string>

class IMenuController
{
public:
	virtual MenuChoice askForMenuChoice() = 0;
	virtual std::string askForNickname() = 0;
	virtual std::string askForIP() = 0;
	virtual int askForPort() = 0;
	virtual int askForBotsCount() = 0;
	virtual void run() = 0;
};