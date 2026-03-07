#include "HumanPlayerLogic.h"

HumanPlayerLogic::HumanPlayerLogic(unsigned int startingChips) : PlayerLogicParent(startingChips) {}
HumanPlayerLogic::HumanPlayerLogic(unsigned int startingChips, std::shared_ptr<IInputHandler> inputHandlerPointer) : PlayerLogicParent(startingChips),
pInputHandler(inputHandlerPointer) {
}

PlayerAction HumanPlayerLogic::makeDecision(unsigned int amountToCall)
{
	if (pInputHandler) {
		return pInputHandler->requestAction(amountToCall);
	}
	return PlayerAction{ ActionType::FOLD, 0 };
}