#pragma once

#include "IMenuController.h"
#include "ConsoleMenuView.h"


class ConsoleMenuController : public IMenuController
{
private:
	ConsoleMenuView &view;
public:
	ConsoleMenuController(ConsoleMenuView& givenViewRef) : view(givenViewRef) {}
	virtual MenuChoice askForMenuChoice() override;
	virtual std::string askForNickname() override;
	virtual std::string askForIP() override;
	virtual int askForPort() override;
	virtual int askForBotsCount() override;
	virtual void run() override;
};