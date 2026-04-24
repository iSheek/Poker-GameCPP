#include "ConsoleMenuController.h"
#include "ConsoleMenuView.h"
#include "MenuChoice.h"
#include "GameSettings.h"
#include <algorithm>
#include <string>
#include <iostream>
#include <limits>


constexpr std::string_view wrongInputMessage{ "WRONG INPUT!" };
constexpr std::string_view wrongNicknameMessage{ "WRONG NICKNAME, YOU CAN ONLY USE LETTERS!" };

constexpr int maxBots{ 4 };

constexpr std::string_view wrongBotCountMessage{ "WRONG BOT COUNT, YOU CAN PUT MAX 4 BOTS" };


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

	return givenNickname;
}

std::string ConsoleMenuController::askForIP()
{
	
	std::string givenIP{};
	
	bool showError{ false };

	while (true)
	{
		this->view.showIPInput();
		if (showError) this->view.showError(wrongInputMessage);

		std::cin >> givenIP;

		if (!std::cin)
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.clear();
			showError = true;
			continue;
		}
		else break;
	}

	return givenIP;
}

int ConsoleMenuController::askForPortToConnect()
{

	bool showError{ false };
	int givenPort{};
	while (true)
	{
		this->view.showPortConnectInput();
		if (showError) this->view.showError(wrongInputMessage);

		std::cin >> givenPort;

		if (!std::cin)
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.clear();
			showError = true;
			continue;
		}
		else break;

	}

	return givenPort;

}

int ConsoleMenuController::askForPortToCreate()
{
	bool showError{ false };
	int givenPort{};
	while (true)
	{
		this->view.showPortCreateInput();
		if (showError) this->view.showError(wrongInputMessage);

		std::cin >> givenPort;

		if (!std::cin)
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.clear();
			showError = true;
			continue;
		}
		else break;

	}

	return givenPort;
}

int ConsoleMenuController::askForBotsCount()
{

	bool showError{ false };

	int givenCount{};

	while (true)
	{
		this->view.showBotCountInput();
		if (showError) this->view.showError(wrongBotCountMessage);

		std::cin >> givenCount;
		if (!std::cin)
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.clear();
			showError = true;
			continue;
		}
		else if (0 > givenCount || maxBots < givenCount)
		{
			showError = true;
			continue;
		}
		else break;
	}

	return givenCount;


}

int ConsoleMenuController::askForPlayerCount()
{

	bool showError{ false };

	int givenCount{};

	while (true)
	{
		this->view.showBotCountInput();
		if (showError) this->view.showError(wrongBotCountMessage);

		std::cin >> givenCount;
		if (!std::cin)
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.clear();
			showError = true;
			continue;
		}
		else if (0 > givenCount || maxBots < givenCount)
		{
			showError = true;
			continue;
		}
		else break;
	}

	return givenCount;

}


GameSettings ConsoleMenuController::runAndGetSettings()
{
	MenuChoice chosenOption{ askForMenuChoice() };

	GameSettings gameSettings{};

	switch (chosenOption)
	{
	case MenuChoice::START_SINGLEPLAYER:
		gameSettings.isMultiplayer = false;
		gameSettings.nickname = askForNickname();
		gameSettings.playerCount = askForBotsCount();
		break;
	case MenuChoice::START_MULTIPLAYER:
		gameSettings.isMultiplayer = true;
		gameSettings.nickname = askForNickname();
		gameSettings.port = askForPortToCreate();
		gameSettings.playerCount = askForPlayerCount();
		break;
	case MenuChoice::JOIN_MULTIPLAYER:
		gameSettings.isMultiplayer = true;
		gameSettings.nickname = askForNickname();
		gameSettings.ipAddress = askForIP();
		gameSettings.port = askForPortToConnect();
		break;
	case MenuChoice::numberofchoices:
	case MenuChoice::EXIT:
		throw std::exception("Program Ended"); // we throw exception so main will catch it and end the program and clean it properly
		break;
	default:
		break;
	}

	return gameSettings;

}
