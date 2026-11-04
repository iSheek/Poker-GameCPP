/**
 * @file BettingRules.cpp
 * @brief File containing definition of BettingRules namespace's functions
 */


#include "BettingRules.h"
#include "PlayerAction.h"
#include "TableState.h"
#include "PlayerState.h"
#include <vector>
#include <algorithm>

namespace BettingRules
{

	AvailableOptions getPossibleOptions(const TableState& tableState, const PlayerState& playerState)
	{
		if (playerState.currentChips <= 0)
		{
			return AvailableOptions{ .actions {ActionType::NONE}, .minRaiseTo {0}, .maxRaiseTo {0} };
		}

		AvailableOptions possibleOptions{};

		possibleOptions.actions.push_back(ActionType::FOLD);
		possibleOptions.minRaiseTo = tableState.lastFullRaiseAmount + tableState.currentHighestBet;
		possibleOptions.maxRaiseTo = playerState.currentChips + playerState.currentBet;


		if (playerState.currentBet < tableState.currentHighestBet)
		{
			possibleOptions.actions.push_back(ActionType::CALL);
		}
		else
		{
			possibleOptions.actions.push_back(ActionType::CHECK);
		}

		if (possibleOptions.maxRaiseTo > tableState.currentHighestBet)
		{
			possibleOptions.actions.push_back(ActionType::RAISE);

			if (possibleOptions.maxRaiseTo < possibleOptions.minRaiseTo)
			{
				possibleOptions.minRaiseTo = possibleOptions.maxRaiseTo;
			}
		}

		return possibleOptions;
	}

	bool isActionValid(const AvailableOptions& playersAvailableOptions, const PlayerAction& playerAction)
	{

		if (playerAction.actionType == ActionType::NONE) return false;

		auto it = std::find(playersAvailableOptions.actions.begin(), playersAvailableOptions.actions.end(), playerAction.actionType);

		if (it == playersAvailableOptions.actions.end())
		{
			return false;
		}

		if (playerAction.actionType == ActionType::RAISE && !(playerAction.amount <= playersAvailableOptions.maxRaiseTo && playerAction.amount >= playersAvailableOptions.minRaiseTo))
		{
			return false;
		}

		return true;

	}

}
