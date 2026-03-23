#pragma once

#include <nlohmann/json.hpp>

enum class NetworkCommand
{
	UNKNOWN = -1,
	RENDER_TABLE = 0,
	REQUEST_ACTION,
	ON_PLAYER_ACTION,
	ON_COMMUNITY_CARD_DEALT,
	ON_SHOWDOWN
};


NLOHMANN_JSON_SERIALIZE_ENUM(NetworkCommand, {
	{NetworkCommand::UNKNOWN, "unknown"},
	{NetworkCommand::RENDER_TABLE, "renderTable"},
	{NetworkCommand::REQUEST_ACTION, "requestAction"},
	{NetworkCommand::ON_PLAYER_ACTION, "onPlayerAction"},
	{NetworkCommand::ON_COMMUNITY_CARD_DEALT, "onCommunityCardDealt"},
	{NetworkCommand::ON_SHOWDOWN, "onShowdown"}
	})