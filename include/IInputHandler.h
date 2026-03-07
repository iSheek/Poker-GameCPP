#pragma once

#include "PlayerAction.h"

class IInputHandler
{
public:
	virtual PlayerAction requestAction() = 0;
	virtual ~IInputHandler() = default;
};