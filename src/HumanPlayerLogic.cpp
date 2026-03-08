#include "HumanPlayerLogic.h"

HumanPlayerLogic::HumanPlayerLogic(unsigned int startingChips) : PlayerLogicParent(startingChips) {}
HumanPlayerLogic::HumanPlayerLogic(unsigned int startingChips, std::shared_ptr<IInputHandler> inputHandlerPointer) : PlayerLogicParent(startingChips),
pInputHandler(inputHandlerPointer) {
}

PlayerAction HumanPlayerLogic::makeDecision(const TableState& state)
{
	if (pInputHandler) {
		return pInputHandler->requestAction(state, this->getPlayerCards());
	}
	return PlayerAction{ ActionType::FOLD, 0 };
}