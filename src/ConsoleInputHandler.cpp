#include "ConsoleInputHandler.h"
#include <iostream>

unsigned int ConsoleInputHandler::askForValueToRaise()
{
	unsigned int valueToRaise = 0;
	std::cout << "Put how much raise to: ";
	while (!(std::cin >> valueToRaise))
	{
		std::cout << "BAD VALUE!";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	return valueToRaise;
}

PlayerAction ConsoleInputHandler::requestAction(const TableState& tableState, std::array<Card, 2> playerCards)
{
	PlayerAction playerAction = { ActionType::NONE, 0 };

	int userInput = 1;

	bool askForInputs = true;

	while (askForInputs)
	{

		std::string callOrCheckText = "1. ";

		if (tableState.amountToCall == 0) callOrCheckText += "CHECK";
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
				playerAction.amount = askForValueToRaise();
				askForInputs = false;
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
				playerAction.amount = askForValueToRaise();
				askForInputs = false;
				break;
			default:
				std::cout << "WRONG CHOICE!" << std::endl;
				break;
			}
		}
	}
	return playerAction;
}