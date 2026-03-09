#include "ConsoleInputHandler.h"
#include "CardFormatter.h"
#include <iostream>

unsigned int ConsoleInputHandler::askForValueToRaise(unsigned int currentHighestBet, unsigned int playersCurrentChips)
{
	unsigned int valueToRaise = 0;

	bool validRaise = false;

	while (!validRaise) {
		std::cout << "Put how much raise to (enter 0 to go back): ";
		while (!(std::cin >> valueToRaise))
		{
			std::cout << "BAD VALUE!";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		if (valueToRaise == 0) return 0;
		else if (valueToRaise <= currentHighestBet)
		{
			std::cout << "The value isn't more than current bet!" << std::endl;
		}
		else if (valueToRaise > playersCurrentChips)
		{
			std::cout << "You don't have that much chips!" << std::endl;
		}
		else validRaise = true;
	}
	return valueToRaise;
}

PlayerAction ConsoleInputHandler::requestAction(const TableState& tableState, const PlayerState& playerState)
{
	PlayerAction playerAction = { ActionType::NONE, 0 };

	int userInput = 1;

	bool askForInputs = true;

	while (askForInputs)
	{

		std::cout << "\n------------------------------------\n";
		std::cout << "YOUR CHIPS: " << playerState.currentChips << " $\n";
		std::cout << "YOUR CARDS: [" << CardFormatter::getCardName(playerState.playersCards[0]).wholeCardString() << "] ["
			<< CardFormatter::getCardName(playerState.playersCards[1]).wholeCardString() << "]\n";
		std::cout << "------------------------------------\n"; 

		std::string callOrCheckText = "1. ";

		if (tableState.amountToCall == 0) callOrCheckText += "CHECK";
		else if (tableState.amountToCall >= playerState.currentChips) callOrCheckText += "CALL (ALL-IN)";
		else callOrCheckText += "CALL";

		std::cout << "===MAKE YOUR DECISION===" << std::endl;
		std::cout << callOrCheckText << std::endl;
		std::cout << "2. FOLD" << std::endl;
		std::cout << "3. RAISE" << std::endl;

		std::cout << "YOUR CHOICE: ";
		while (!(std::cin >> userInput))
		{
			std::cout << "BAD VALUE!";
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
				playerAction.amount = askForValueToRaise(tableState.currentHighestBet, playerState.currentChips);
				if (playerAction.amount != 0) askForInputs = false;
				else std::cout << "--RAISE CANCELED--" << std::endl;
				break;
			default:
				std::cout << "WRONG CHOICE!" << std::endl;
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
				playerAction.amount = askForValueToRaise(tableState.currentHighestBet, playerState.currentChips);
				if (playerAction.amount != 0) askForInputs = false;
				else std::cout << "--RAISE CANCELED--" << std::endl;
				break;
			default:
				std::cout << "WRONG CHOICE!" << std::endl;
				break;
			}
		}
	}
	return playerAction;
}