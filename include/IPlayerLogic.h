#pragma once

#include "PlayerAction.h"

class IPlayerLogic
{
public:
	virtual PlayerAction makeDecision(unsigned int amountToCall) = 0;
	virtual ~IPlayerLogic() = default;
};
