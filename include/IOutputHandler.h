#pragma once

#include "Cards.h"
#include <vector>
#include "TableState.h"

class IOutputHandler
{
public:
	virtual void renderTable(const TableState& state) = 0;
	virtual ~IOutputHandler() = default;
};