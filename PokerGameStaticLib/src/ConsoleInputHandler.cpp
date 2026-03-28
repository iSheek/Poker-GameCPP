#include "ConsoleInputHandler.h"
#include "CardFormatter.h"
#include "ConsoleUtils.h"
#include <iostream>
#include "ConsoleCONSTANS.h"

unsigned int ConsoleInputHandler::askForValueToRaise(unsigned int currentHighestBet, unsigned int playersCurrentChips, int xPlacement, int yPlacement)
{
	unsigned int valueToRaise = 0;

	bool validRaise = false;

	while (!validRaise) {
		ConsoleUtils::printAt(xPlacement, yPlacement++, "HOW MUCH (0 to go back): ");
		while (!(std::cin >> valueToRaise))
		{
			ConsoleUtils::printAt(xPlacement, yPlacement++, "BAD VALUE!");
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		if (valueToRaise == 0) return 0;
		if (valueToRaise % 10 != 0) ConsoleUtils::printAt(xPlacement, yPlacement++, "The smallest chip is 10!");
		else if (valueToRaise <= currentHighestBet)
		{
			ConsoleUtils::printAt(xPlacement, yPlacement++, "The value isn't more than current bet!");
		}
		else if (valueToRaise > playersCurrentChips)
		{
			ConsoleUtils::printAt(xPlacement, yPlacement++, "You don't have that much chips!");
		}
		else validRaise = true;
	}
	return valueToRaise;
}

PlayerAction ConsoleInputHandler::requestAction(const TableState& tableState, const PlayerState& playerState)
{
	

	int xForPlayerCards = (MAX_LINE_LENGTH - ((CARD_WIDTH * 4 / 3) * MAX_PLAYERS_CARDS)) / 4;
	int yForPlayerCards = STARTING_Y_FOR_PLAYER_CARDS;

	int StartingXForPlayerCards = xForPlayerCards;

	//int lastXForPlayersCards;

	for (const auto& card : playerState.playersCards)
	{
		auto cardGraphic = ConsoleUtils::generateCardGraphic(card);
		for (const auto& graphicLine : cardGraphic)
		{
			ConsoleUtils::printAt(xForPlayerCards, yForPlayerCards++, graphicLine);

		}
		xForPlayerCards += (CARD_WIDTH * 4 / 3);
		yForPlayerCards = STARTING_Y_FOR_PLAYER_CARDS;
	}

	
	int yForAction = STARTING_Y_FOR_COMMUNITY_CARDS + CARD_LENGTH + 4;

	PlayerAction playerAction = { ActionType::NONE, 0 };

	int userInput = 1;

	bool askForInputs = true;

	while (askForInputs)
	{
		// reset variable after every loop
		int yForAction = STARTING_Y_FOR_COMMUNITY_CARDS + CARD_LENGTH + 4;

		ConsoleUtils::printAt(xForPlayerCards, yForAction++, "YOUR CHIPS: " + std::to_string(playerState.currentChips));


		std::string callOrCheckText = "1. ";

		if (tableState.amountToCall == 0) callOrCheckText += "CHECK";
		else if (tableState.amountToCall >= playerState.currentChips) callOrCheckText += "CALL (ALL-IN)";
		else callOrCheckText += "CALL";

		ConsoleUtils::printAt(xForPlayerCards, yForAction++, "===MAKE YOUR DECISION===");
		ConsoleUtils::printAt(xForPlayerCards, yForAction++, callOrCheckText);
		ConsoleUtils::printAt(xForPlayerCards, yForAction++, "2. FOLD");
		ConsoleUtils::printAt(xForPlayerCards, yForAction++, "3. RAISE");

		ConsoleUtils::printAt(xForPlayerCards, yForAction++, "YOUR CHOICE: ");
		while (!(std::cin >> userInput))
		{
			ConsoleUtils::printAt(xForPlayerCards, yForAction++, "BAD VALUE!");
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}


		if (tableState.amountToCall == 0)
		{
			switch (userInput)
			{
			case 1:
				playerAction.actionType = ActionType::CHECK;
				askForInputs = false;
				break;
			case 2:
				playerAction.actionType = ActionType::FOLD;
				askForInputs = false;
				break;
			case 3:
				playerAction.actionType = ActionType::RAISE;
				playerAction.amount = askForValueToRaise(tableState.currentHighestBet, playerState.currentChips, xForPlayerCards, yForAction++);
				if (playerAction.amount != 0) askForInputs = false;
				else
				{
					ConsoleUtils::printAt(xForPlayerCards, yForAction++, "--RAISE CANCELED--");
				}
				break;
			default:
				ConsoleUtils::printAt(xForPlayerCards, yForAction++, "WRONG CHOICE!");
				break;
			}
		}
		else
		{
			switch (userInput)
			{
			case 1:
				playerAction.actionType = ActionType::CALL;
				askForInputs = false;
				break;
			case 2:
				playerAction.actionType = ActionType::FOLD;
				askForInputs = false;
				break;
			case 3:
				playerAction.actionType = ActionType::RAISE;
				playerAction.amount = askForValueToRaise(tableState.currentHighestBet, playerState.currentChips, xForPlayerCards, yForAction++);
				if (playerAction.amount != 0) askForInputs = false;
				else ConsoleUtils::printAt(xForPlayerCards, yForAction++, "--RAISE CANCELED--");
				break;
			default:
				ConsoleUtils::printAt(xForPlayerCards, yForAction++, "WRONG CHOICE!");
				break;
			}
		}
	}
	return playerAction;
}

void ConsoleInputHandler::onPlayersCardDealt(const Card& card)
{
	this->playersCardsGraphics.push_back(ConsoleUtils::generateCardGraphic(card));
}