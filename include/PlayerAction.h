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
	ActionType actionType;
	unsigned int amount = 0;
};


NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PlayerAction, actionType, amount)