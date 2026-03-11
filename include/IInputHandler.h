#pragma once

#include "PlayerAction.h"
#include "TableState.h"
#include "PlayerState.h"
#include "Cards.h"
#include <array>

class IInputHandler
{
public:
	virtual PlayerAction requestAction(const TableState& tableState, const PlayerState& playerState) = 0;
	virtual void onPlayersCardDealt(const Card& card) = 0;
	virtual ~IInputHandler() = default;
};