#pragma once

#include "PlayerLogicParent.h"
#include "IInputHandler.h"
#include <memory>

class HumanPlayerLogic : public PlayerLogicParent
{
private:
	std::shared_ptr<IInputHandler> pInputHandler;
	
public:
	HumanPlayerLogic(unsigned int startingChips) : PlayerLogicParent(startingChips) {}
	HumanPlayerLogic(unsigned int startingChips, std::shared_ptr<IInputHandler> inputHandlerPointer) : PlayerLogicParent(startingChips), 
		pInputHandler(inputHandlerPointer){}

	PlayerAction makeDecision() override
	{
		if (pInputHandler) {
			return pInputHandler->requestAction();
		}
		return PlayerAction{ ActionType::FOLD, 0 };
	}

};