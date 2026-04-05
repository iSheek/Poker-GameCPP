#pragma once

#include <nlohmann/json.hpp>

enum class ActionType
{
	NONE = -1,

	FOLD = 1,
	CHECK,
	CALL,
	RAISE
};

struct PlayerAction
{
	ActionType actionType{ ActionType::NONE };
	int amount{};
};


NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PlayerAction, actionType, amount)