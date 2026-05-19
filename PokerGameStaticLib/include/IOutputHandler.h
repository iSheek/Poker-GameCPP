/**
 * @file IOutputHandler.h
 * @brief File containing declaration of IOutputHandler interface
 */
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

/**
 * @brief Interface for handling game output and rendering
 */
class IOutputHandler
{
public:
	// methods for animations when making UX outside console
	/*
	virtual void onChipsMovedToPot(int amount) = 0;
	virtual void onCardBurn() = 0;
	*/

	/**
	 * @brief Callback for when a community card is dealt
	 * @param card The dealt card
	 */
	virtual void onCommunityCardDealt(const Card& card) = 0;

	/**
	 * @brief Callback for when a player performs an action
	 * @param playerName Name of the player
	 * @param action The action performed
	 */
	virtual void onPlayerAction(const std::string& playerName, const PlayerAction& action) = 0;

	/**
	 * @brief Callback for the showdown phase
	 * @param winnerNames List of winners' names
	 * @param winningHand The winning hand's score
	 * @param pot The total pot amount awarded
	 */
	virtual void onShowdown(const std::vector<std::string>& winnerNames, const HandScore& winningHand, const int& pot) = 0;

	/**
	 * @brief Renders the current state of the table and players
	 * @param tableState Current state of the table
	 * @param publicPlayersInfo Publicly visible information about all players
	 */
	virtual void renderTable(const TableState& tableState, const std::vector<PublicPlayerInfo>& publicPlayersInfo) = 0;

	/**
	 * @brief Virtual destructor
	 */
	virtual ~IOutputHandler() = default;
};