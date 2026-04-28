#pragma once

#include "IMenuController.h"
#include "ConsoleMenuView.h"


class ConsoleMenuController : public IMenuController
{
private:
	ConsoleMenuView &view;

	GameSettings configureStartSingleplayer();
	GameSettings configureStartMultiplayer();
	GameSettings configureJoinMultiplayer();
public:
	ConsoleMenuController(ConsoleMenuView& givenViewRef) : view(givenViewRef) {}
	virtual MenuChoice askForMenuChoice() override;
	virtual std::string askForNickname() override;
	virtual std::string askForIP() override;
	virtual int askForPortToConnect() override;
	virtual int askForPortToCreate() override;
	virtual int askForBotsCount() override;
	virtual int askForPlayerCount() override;
	virtual int askForStartingChips() override;
	virtual GameSettings runAndGetSettings() override;
};