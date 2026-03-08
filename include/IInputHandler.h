#pragma once

#include "PlayerAction.h"
#include "TableState.h"
#include "Cards.h"
#include <array>

class IInputHandler
{
public:
	virtual PlayerAction requestAction(const TableState& tableState, std::array<Card,2> playerCards) = 0;
	virtual ~IInputHandler() = default;
};