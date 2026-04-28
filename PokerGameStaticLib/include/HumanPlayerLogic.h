#pragma once

#include "PlayerLogicParent.h"
#include "IInputHandler.h"
#include <memory>

class HumanPlayerLogic : public PlayerLogicParent
{
private:
	std::shared_ptr<IInputHandler> pInputHandler{};
	
public:
	HumanPlayerLogic(int startingChips);
	HumanPlayerLogic(int startingChips, std::shared_ptr<IInputHandler> inputHandlerPointer);

	PlayerAction makeDecision(const TableState& state) override;

};