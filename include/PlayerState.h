#pragma once

#include "Cards.h"
#include <array>

struct PlayerState
{
	std::array<Card, 2> playersCards;
	unsigned int currentChips;
};