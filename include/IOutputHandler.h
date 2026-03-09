#pragma once

#include "Cards.h"
#include <vector>
#include "TableState.h"

class IOutputHandler
{
public:
	// methods for animations when making UX outside console
	/*
	virtual void onCommunityCardDealt(const Card& card) = 0;
	virtual void onPlayerAction(unsigned int playerIndex, PlayerAction action) = 0;
	virtual void onChipsMovedToPot(unsigned int amount) = 0;
	virtual void onCardBurn() = 0;
	*/
	virtual void renderTable(const TableState& state) = 0;
	virtual ~IOutputHandler() = default;
};