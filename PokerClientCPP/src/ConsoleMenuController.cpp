#include "ConsoleMenuController.h"
#include "ConsoleMenuView.h"
#include "MenuChoice.h"
#include <algorithm>
#include <string>
#include <iostream>
#include <limits>


std::string_view wrongInputMessage{ "WRONG INPUT!" };
std::string_view wrongNicknameMessage{ "WRONG NICKNAME, YOU CAN ONLY USE LETTERS!" };

MenuChoice ConsoleMenuController::askForMenuChoice()
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

	return static_cast<MenuChoice>(choice);
	
}

std::string ConsoleMenuController::askForNickname()
{

	bool showError{ false };
	std::string givenNickname{};


	while (true)
	{
		this->view.showNicknameInput();

		if (showError) this->view.showError(wrongNicknameMessage);

		std::cin >> givenNickname;
		if (!std::cin)
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.clear();
			showError = true;
			continue;
		}

		if (!givenNickname.empty() && std::all_of(givenNickname.begin(), givenNickname.end(), [](char c) {return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')); }))
		{
			break;
		}

	}

}

std::string ConsoleMenuController::askForIP()
{



}

int ConsoleMenuController::askForPort()
{
}

int ConsoleMenuController::askForBotsCount()
{
}

void ConsoleMenuController::run()
{
}
