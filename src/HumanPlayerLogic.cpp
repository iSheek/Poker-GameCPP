#include "HumanPlayerLogic.h"

HumanPlayerLogic::HumanPlayerLogic(unsigned int startingChips) : PlayerLogicParent(startingChips) {}
HumanPlayerLogic::HumanPlayerLogic(unsigned int startingChips, std::shared_ptr<IInputHandler> inputHandlerPointer) : PlayerLogicParent(startingChips),
pInputHandler(inputHandlerPointer) {
}

PlayerAction HumanPlayerLogic::makeDecision()
{
	if (pInputHandler) {
		return pInputHandler->requestAction();
	}
	return PlayerAction{ ActionType::FOLD, 0 };
}