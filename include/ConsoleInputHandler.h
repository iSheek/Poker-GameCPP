#pragma once

#include "IInputHandler.h"
#include "PlayerAction.h"


class ConsoleInputHandler : public IInputHandler
{
	unsigned int askForValueToRaise();

public:
	PlayerAction requestAction(unsigned int amountToCall) override;

};