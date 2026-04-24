#pragma once

#include "IMenuView.h"
#include <string_view>

class ConsoleMenuView : public IMenuView
{
public:
	virtual void showMenuChoices() override;
	virtual void showNicknameInput() override;
	virtual void showIPInput() override;
	virtual void showPortConnectInput() override;
	virtual void showPortCreateInput() override;
	virtual void showBotCountInput() override;
	virtual void showPlayerCountInput() override;
	virtual void showStartingChipsInput() override;
	virtual void showError(std::string_view error) override;
};