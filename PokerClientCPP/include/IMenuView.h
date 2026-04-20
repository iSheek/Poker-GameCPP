#pragma once

#include <string_view>

class IMenuView
{

public:
	virtual void showMenuChoices() = 0;
	virtual void showNicknameInput() = 0;
	virtual void showIPInput() = 0;
	virtual void showPortInput() = 0;
	virtual void showBotCountInput() = 0;
	virtual void showStartingChipsInput() = 0;
	virtual void showError(std::string_view error) = 0;
};