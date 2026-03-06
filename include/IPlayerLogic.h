#pragma once

#include "PlayerAction.h"

class IPlayerLogic
{
public:
	virtual PlayerAction makeDecision() = 0;
	virtual ~IPlayerLogic() = default;
};
