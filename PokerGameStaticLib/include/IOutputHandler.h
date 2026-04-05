#pragma once

#include "Cards.h"
#include "HandScore.h"
#include "PlayerAction.h"
#include "PlayerLogicParent.h"
#include "TableState.h"
#include "PublicPlayerInfo.h"
#include <vector>
#include <memory>
#include <string>
#include <string_view>

class IOutputHandler
{
public:
	// methods for animations when making UX outside console
	/*
	virtual void onChipsMovedToPot(int amount) = 0;
	virtual void onCardBurn() = 0;
	*/
	virtual void onCommunityCardDealt(const Card& card) = 0;
	virtual void onPlayerAction(const std::string& playerName, const PlayerAction& action) = 0;
	virtual void onShowdown(const std::vector<std::string>& winnerNames, const HandScore& winningHand, const int& pot) = 0;
	virtual void renderTable(const TableState& tableState, const std::vector<PublicPlayerInfo>& publicPlayersInfo) = 0;
	virtual ~IOutputHandler() = default;
};