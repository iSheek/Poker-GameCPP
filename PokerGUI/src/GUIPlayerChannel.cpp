/**
* @file GUIPlayerChannel.cpp
* @brief File containing definition of GUIPlayerChannel class' methods
*/


#include "GUIPlayerChannel.h"
#include "GameEvents.h"
#include <future>
#include <chrono>
#include <stdexcept>

void GUIPlayerChannel::onCommunityCardDealt(const Card& card)
{
	CommunityCardDealtEvent event{
		.card = card
	};
	eventQueue.push(std::move(event));
}

void GUIPlayerChannel::onPlayerAction(const std::string& playerName, const PlayerAction& action)
{
	PlayerActionEvent event{
		.playerName = playerName,
		.action = action
	};
	eventQueue.push(std::move(event));
}

void GUIPlayerChannel::onShowdown(const ShowdownResult& showdownResult)
{
	ShowdownEvent event{
		.result = showdownResult
	};
	eventQueue.push(std::move(event));
}

void GUIPlayerChannel::renderTable(const TableState& tableState, const std::vector<PublicPlayerInfo>& publicPlayersInfo)
{
	TableStateEvent event{
		.tableState = tableState,
		.publicPlayersInfo = publicPlayersInfo
	};
	eventQueue.push(std::move(event));
}

PlayerAction GUIPlayerChannel::requestAction(const TableState& tableState, const PlayerState& playerState)
{
	std::promise<PlayerAction> promiseAction{};

	std::future<PlayerAction> futureAction{ promiseAction.get_future() };
	ActionRequestEvent event
	{
		.tableState = tableState,
		.playerState = playerState,
		.actionPromise = std::move(promiseAction)
	};

	eventQueue.push(std::move(event));

	while (futureAction.wait_for(std::chrono::milliseconds(100)) != std::future_status::ready)
	{
		if (stopToken.stop_requested())
		{
			throw GameTerminationException("ERROR GAME TERMINATED");
		}
	}

	PlayerAction returnAction{};
	try {
		returnAction = futureAction.get();
	}
	catch (const std::future_error&)
	{
		throw GameTerminationException("ERROR GAME TERMINATED");
	}
	return returnAction;
}

void GUIPlayerChannel::onPlayersCardDealt(const Card& card)
{
	PlayerCardDealtEvent event{
		.card = card
	};
	eventQueue.push(std::move(event));
}
