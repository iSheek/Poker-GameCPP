#include "ConsoleMenuController.h"
#include "ConsoleMenuView.h"
#include "MenuChoice.h"
#include <iostream>
#include <limits>


std::string_view wrongInputMessage{ "WRONG INPUT!" };

void ConsoleMenuController::askForMenuChoice()
{
	int choice{-1};
	
	bool showError{ false };

	while (choice < 0 || choice > static_cast<int>(MenuChoice::numberofchoices))
	{
		this->view.showMenuChoices();
		if (showError) this->view.showError(wrongInputMessage);
		std::cin >> choice;
		if (!std::cin)
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.clear();
			showError = true;
		}
	}

	MenuChoice chosenChoice{ static_cast<MenuChoice>(choice) };

	switch (chosenChoice)
	{
	case MenuChoice::START_SINGLEPLAYER:
		askForNickname();
		break;
	case MenuChoice::START_MULTIPLAYER:
		break;
	case MenuChoice::JOIN_MULTIPLAYER:
		break;
	case MenuChoice::EXIT:
		break;
	case MenuChoice::numberofchoices:
		[[fallthrough]]
	default:
		break;
	}

	
}

void ConsoleMenuController::askForNickname()
{
}

void ConsoleMenuController::askForIP()
{
}

void ConsoleMenuController::askForPort()
{
}

void ConsoleMenuController::askForBotsCount()
{
}
