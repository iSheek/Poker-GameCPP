#pragma once

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