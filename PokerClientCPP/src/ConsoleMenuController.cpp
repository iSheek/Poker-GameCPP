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
constexpr std::string_view wrongChipInput{ "WRONG AMOUNT OF CHIPS, SMALLEST CHIP IS 10 AND STARTING CHIPS CAN'T BE SMALLER THAN 1000!" };
constexpr int maxBots{ 4 };
constexpr std::string_view wrongBotCountMessage{ "WRONG BOT COUNT, YOU CAN PUT MAX 4 BOTS" };
constexpr std::string_view localhostAddress{ "127.0.0.1" };
constexpr int smallestChip{ 10 };


MenuChoice ConsoleMenuController::askForMenuChoice()
{
	int choice{-1};
	
	bool showError{ false };

	while (choice < 1 || choice > static_cast<int>(MenuChoice::numberofchoices))
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

	return static_cast<MenuChoice>(choice-1);
	
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

		if (givenNickname == "0")
		{
			break;
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
		if (givenCount == 0) break;
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
		this->view.showPlayerCountInput();
		if (showError) this->view.showError(wrongBotCountMessage);

		std::cin >> givenCount;
		if (!std::cin)
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.clear();
			showError = true;
			continue;
		}
		if (givenCount == 0) break;
		else if (0 > givenCount || maxBots < givenCount)
		{
			showError = true;
			continue;
		}
		else break;
	}

	return givenCount;

}

int ConsoleMenuController::askForStartingChips()
{
	bool showError{ false };
	int givenChips{};
	while (true)
	{
		this->view.showStartingChipsInput();
		if (showError) this->view.showError(wrongChipInput);

		std::cin >> givenChips;

		if (!std::cin)
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.clear();
			showError = true;
			continue;
		}
		if (givenChips == 0) break;
		if (givenChips < 1000 || givenChips % smallestChip != 0)
		{
			showError = true;
			continue;
		}

		else break;

	}

	return givenChips;
}


GameSettings ConsoleMenuController::runAndGetSettings()
{
	MenuChoice chosenOption{ askForMenuChoice() };

	GameSettings gameSettings{};

	switch (chosenOption)
	{
	case MenuChoice::START_SINGLEPLAYER:
		gameSettings = configureStartSingleplayer();
		break;
	case MenuChoice::START_MULTIPLAYER:
		gameSettings = configureStartMultiplayer();
		break;
	case MenuChoice::JOIN_MULTIPLAYER:
		gameSettings = configureJoinMultiplayer();
		break;
	case MenuChoice::numberofchoices:
	case MenuChoice::EXIT:
		gameSettings = GameSettings{};
		break;
	default:
		break;
	}

	return gameSettings;

}


GameSettings ConsoleMenuController::configureStartSingleplayer()
{
	GameSettings settingsToReturn{};

	settingsToReturn.isMultiplayer = false;

	int step{ 1 };
	while (step > 0 && step < 4)
	{
		switch (step)
		{
		case 1:
			settingsToReturn.nickname = askForNickname();
			if (settingsToReturn.nickname == "0") --step;
			else ++step;
			break;
		case 2:
			settingsToReturn.playerCount = askForBotsCount();
			if (settingsToReturn.playerCount == 0) --step;
			else ++step;
			break;
		case 3:
			settingsToReturn.startingChips = askForStartingChips();
			if (settingsToReturn.startingChips == 0) --step;
			else ++step;
			break;
		default:
			break;
		}
	}
	if (step >= 0) return GameSettings{};

	return settingsToReturn;

}

GameSettings ConsoleMenuController::configureStartMultiplayer()
{
	GameSettings settingsToReturn{};

	settingsToReturn.isMultiplayer = true;
	settingsToReturn.isHost = true;
	settingsToReturn.ipAddress = localhostAddress;

	int step{ 1 };
	while (step > 0 && step < 5)
	{
		switch (step)
		{
		case 1:
			settingsToReturn.nickname = askForNickname();
			if (settingsToReturn.nickname == "0") --step;
			else ++step;
			break;
		case 2:
			settingsToReturn.port = askForPortToCreate();
			if (settingsToReturn.port == 0) --step;
			else ++step;
			break;
		case 3:
			settingsToReturn.playerCount = askForPlayerCount();
			if (settingsToReturn.playerCount == 0) --step;
			else ++step;
			break;
		case 4:
			settingsToReturn.startingChips = askForStartingChips();
			if (settingsToReturn.startingChips == 0) --step;
			else ++step;
			break;
		default:
			break;
		}
	}
	if (step >= 0) return GameSettings{};

	return settingsToReturn;
}

GameSettings ConsoleMenuController::configureJoinMultiplayer()
{
	GameSettings settingsToReturn{};

	settingsToReturn.isMultiplayer = true;

	int step{ 1 };
	while (step > 0 && step < 4)
	{
		switch (step)
		{
		case 1:
			settingsToReturn.nickname = askForNickname();
			if (settingsToReturn.nickname == "0") --step;
			else ++step;
			break;
		case 2:
			settingsToReturn.ipAddress = askForIP();
			if (settingsToReturn.ipAddress == "0") --step;
			else ++step;
			break;
		case 3:
			settingsToReturn.port = askForPortToConnect();
			if (settingsToReturn.port == 0) --step;
			else ++step;
			break;
		default:
			break;
		}
	}
	if (step >= 0) return GameSettings{};

	return settingsToReturn;
}