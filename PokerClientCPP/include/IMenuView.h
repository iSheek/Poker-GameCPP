#pragma once

class IMenuView
{

public:
	virtual void showMenuChoices() = 0;
	virtual void showNicknameInput() = 0;
	virtual void showIPInput() = 0;
	virtual void showPortInput() = 0;
	virtual void showBotCountInput() = 0;
};