#pragma once

#include "Cards.h"
#include <array>
#include <nlohmann/json.hpp>

struct PlayerState
{
	std::array<Card, 2> playersCards{};
	int currentChips{};
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PlayerState, playersCards, currentChips)