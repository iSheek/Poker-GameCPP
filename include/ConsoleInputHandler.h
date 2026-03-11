#pragma once

#include "IInputHandler.h"
#include "PlayerAction.h"
#include "PlayerState.h"
#include <vector>
#include <string>


class ConsoleInputHandler : public IInputHandler
{
private:
	unsigned int askForValueToRaise(unsigned int currentHighestBet, unsigned int playersCurrentChips);
	std::vector<std::vector<std::string>> playersCardsGraphics;

public:
	PlayerAction requestAction(const TableState& tableState, const PlayerState& playerState) override;
	void onPlayersCardDealt(const Card& card) override;
};