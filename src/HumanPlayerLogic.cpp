#include "HumanPlayerLogic.h"

HumanPlayerLogic::HumanPlayerLogic(unsigned int startingChips) : PlayerLogicParent(startingChips) {}
HumanPlayerLogic::HumanPlayerLogic(unsigned int startingChips, std::shared_ptr<IInputHandler> inputHandlerPointer) : PlayerLogicParent(startingChips),
pInputHandler(inputHandlerPointer) {
}

PlayerAction HumanPlayerLogic::makeDecision(const TableState& state)
{
	if (this->pInputHandler) {
		PlayerState playerState;
		playerState.currentChips = this->getChips();
		playerState.playersCards = this->getPlayerCards();
		return this->pInputHandler->requestAction(state, playerState);
	}
	return PlayerAction{ ActionType::FOLD, 0 };
}