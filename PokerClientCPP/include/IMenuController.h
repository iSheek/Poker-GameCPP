#pragma once

class IMenuController
{
public:
	virtual void askForMenuChoice() = 0;
	virtual void askForNickname() = 0;
	virtual void askForIP() = 0;
	virtual void askForPort() = 0;
	virtual void askForBotsCount() = 0;
};