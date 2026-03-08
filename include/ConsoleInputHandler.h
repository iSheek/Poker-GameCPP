#pragma once

#include "IInputHandler.h"
#include "PlayerAction.h"
#include "PlayerState.h"


class ConsoleInputHandler : public IInputHandler
{
	unsigned int askForValueToRaise(unsigned int currentHighestBet, unsigned int playersCurrentChips);

public:
	PlayerAction requestAction(const TableState& tableState, const PlayerState& playerState) override;

};