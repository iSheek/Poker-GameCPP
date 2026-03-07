#pragma once

#include "PlayerAction.h"

class IInputHandler
{
public:
	virtual PlayerAction requestAction(unsigned int amountToCall) = 0;
	virtual ~IInputHandler() = default;
};