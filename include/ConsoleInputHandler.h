#pragma once

#include "IInputHandler.h"
#include "PlayerAction.h"


class ConsoleInputHandler : public IInputHandler
{
	unsigned int askForValueToRaise();

public:
	PlayerAction requestAction(const TableState& tableState, std::array<Card, 2> playerCards) override;

};