#pragma once

/**
* @file GameEvents.h 
* @brief File containing declaration of every event of the game
*/


#include "Cards.h"
#include "PlayerAction.h"
#include "TableState.h"
#include "PublicPlayerInfo.h"
#include "PlayerState.h"
#include "ShowdownResult.h"
#include <vector>
#include <string>
#include <variant>
#include <future>

/**
* @brief Struct with data for @ref IOutputHandler::renderTable
*/
struct TableStateEvent
{
	TableState tableState{};
	std::vector<PublicPlayerInfo> publicPlayersInfo{};
};

/**
* @brief Struct with data for @ref IOutputHandler::onPlayerAction
*/
struct PlayerActionEvent
{
	std::string playerName{};
	PlayerAction action{};
};

/**
* @brief Struct with data for @ref IOutputHandler::onShowdown
*/
struct ShowdownEvent
{
	ShowdownResult result{};
};

/**
* @brief Struct with data for @ref IOutputHandler::onCommunityCardDealt
*/
struct CommunityCardDealtEvent
{
	Card card{};
};

/**
* @brief Struct with data for @ref IInputHandler::onPlayersCardDealt
*/
struct PlayerCardDealtEvent
{
	Card card{};
};

/**
* @brief Struct with data for @ref IInputHandler::requestAction
* @details The promise must be fulfilled with the player's decision. 
* If it is destroyed without a value, the waiting game thread gets a broken promise (std::future_error thrown by future.get()).
*/
struct ActionRequestEvent
{
	TableState tableState{};
	PlayerState playerState{};
	std::promise<PlayerAction> actionPromise{};			///< promise of the player's decision
};

/**
* @brief Alias for variant of every struct from GameEvents
*/
using GameEvent = std::variant<
	TableStateEvent,
	PlayerActionEvent,
	ShowdownEvent,
	CommunityCardDealtEvent,
	PlayerCardDealtEvent,
	ActionRequestEvent
>;