#pragma once

#include "PlayerLogicParent.h"
#include "IInputHandler.h"
#include <memory>

class HumanPlayerLogic : public PlayerLogicParent
{
private:
	std::shared_ptr<IInputHandler> pInputHandler;
	
public:
	HumanPlayerLogic(unsigned int startingChips);
	HumanPlayerLogic(unsigned int startingChips, std::shared_ptr<IInputHandler> inputHandlerPointer);

	PlayerAction makeDecision(unsigned int amountToCall) override;

};