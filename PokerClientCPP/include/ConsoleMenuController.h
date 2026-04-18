#pragma once

#include "IMenuController.h"
#include "ConsoleMenuView.h"


class ConsoleMenuController : public IMenuController
{
private:
	ConsoleMenuView view{};
public:
	virtual void askForMenuChoice() override;
	virtual void askForNickname() override;
	virtual void askForIP() override;
	virtual void askForPort() override;
	virtual void askForBotsCount() override;
};