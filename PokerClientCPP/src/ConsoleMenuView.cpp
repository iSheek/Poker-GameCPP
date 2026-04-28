#include "ConsoleMenuView.h"
#include "MenuChoice.h"
#include <iostream>
#include <string>
#include <string_view>
#include <array>

constexpr std::string_view mainMenuText{ "=====POKER GAME=====" };
constexpr std::string_view startSingleplayerText{ "Play singleplayer" };
constexpr std::string_view startMultiplayerText{ "Play multiplayer" };
constexpr std::string_view joinMultiplayerText{ "Join multiplayer game" };
constexpr std::string_view exitText{ "Exit" };
constexpr std::string_view endOfText{ "(input 0 to go back)" };

constexpr auto allChoiceTextsArray = std::array{startSingleplayerText, startMultiplayerText, joinMultiplayerText, exitText };

// ANSI sequence to clear screen
constexpr std::string_view ansiToClear{ "\033[2J\033[1;1H" };

constexpr int maxBotsCount{3};


void ConsoleMenuView::showMenuChoices()
{
	
	std::cout << ansiToClear;

	static_assert(allChoiceTextsArray.size() == static_cast<int>(MenuChoice::numberofchoices));

	std::cout << mainMenuText << "\n";

	for (size_t i = 1; i <= allChoiceTextsArray.size(); ++i)
	{
		std::cout << i << ". " << allChoiceTextsArray[i - 1] << "\n";
	}

	std::cout << "YOUR CHOICE: ";

}

void ConsoleMenuView::showNicknameInput()
{
	std::cout << ansiToClear;

	std::cout << "Enter your nickname: (only letters) " << endOfText << "\n";

}

void ConsoleMenuView::showIPInput()
{
	std::cout << ansiToClear;

	std::cout << "Enter IPv4 address to connect to: " << endOfText << "\n";
}

void ConsoleMenuView::showPortConnectInput()
{
	std::cout << ansiToClear;

	std::cout << "Enter port to connect to: " << endOfText << "\n";
}

void ConsoleMenuView::showPortCreateInput()
{
	std::cout << ansiToClear;

	std::cout << "Enter port to your connection: " << endOfText << "\n";
}

void ConsoleMenuView::showBotCountInput()
{
	std::cout << ansiToClear;

	std::cout << "Enter the amount of bots to add: " << "(MAX: " << maxBotsCount << ") " << endOfText << "\n";
}

void ConsoleMenuView::showPlayerCountInput()
{
	std::cout << ansiToClear;

	std::cout << "Enter the amount of players that will play (including you): " << "(MAX: " << maxBotsCount+1 << ") " << endOfText << "\n";
}

void ConsoleMenuView::showStartingChipsInput()
{
	std::cout << ansiToClear;

	std::cout << "Enter the amount of chips that every player will start with: " << endOfText << "\n";
}

void ConsoleMenuView::showError(std::string_view error)
{
	std::cout << "ERROR: " << error << "\n";
}
