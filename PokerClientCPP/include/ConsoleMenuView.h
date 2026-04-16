#pragma once

#include "IMenuView.h"

class ConsoleMenuView : public IMenuView
{
public:
	virtual void showMenuChoices() override;
	virtual void showNicknameInput() override;
	virtual void showIPInput() override;
	virtual void showPortInput() override;
};