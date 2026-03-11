#pragma once

#include "PlayerLogicParent.h"

class BotPlayerLogic : public PlayerLogicParent
{
private:


public:
	BotPlayerLogic(unsigned int startingChips);

	PlayerAction makeDecision(const TableState& state) override;


};
