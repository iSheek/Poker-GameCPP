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

constexpr auto allChoiceTextsArray = std::array{startSingleplayerText, startMultiplayerText, joinMultiplayerText, exitText };

// ANSI sequence to clear screen
constexpr std::string_view ansiToClear{ "\x1B[2J\x1B[H" };

constexpr int maxBotsCount{4};


void ConsoleMenuView::showMenuChoices()
{
	
	std::cout << ansiToClear;

	static_assert(allChoiceTextsArray.size() == static_cast<int>(MenuChoice::numberofchoices));

	std::cout << mainMenuText << "\n";

	for (size_t i = 1; i < allChoiceTextsArray.size(); ++i)
	{
		std::cout << i << ". " << allChoiceTextsArray[i - 1] << "\n";
	}

	std::cout << "YOUR CHOICE: ";

}

void ConsoleMenuView::showNicknameInput()
{
	std::cout << ansiToClear;

	std::cout << "Enter your nickname: (only letters)\n";

}

void ConsoleMenuView::showIPInput()
{
	std::cout << ansiToClear;

	std::cout << "Enter IP address to connect to:\n";
}

void ConsoleMenuView::showPortConnectInput()
{
	std::cout << ansiToClear;

	std::cout << "Enter port to connect to:\n";
}

void ConsoleMenuView::showPortCreateInput()
{
	std::cout << ansiToClear;

	std::cout << "Enter port to your connection:\n";
}

void ConsoleMenuView::showBotCountInput()
{
	std::cout << ansiToClear;

	std::cout << "Enter the amount of bots to add: " << "(MAX: " << maxBotsCount << ")\n";
}

void ConsoleMenuView::showPlayerCountInput()
{
	std::cout << ansiToClear;

	std::cout << "Enter the amount of players that will play (including you): " << "(MAX: " << maxBotsCount << ")\n";
}

void ConsoleMenuView::showStartingChipsInput()
{
	std::cout << ansiToClear;

	std::cout << "Enter the amount of chips that every player will start with: \n";
}

void ConsoleMenuView::showError(std::string_view error)
{
	std::cout << "ERROR: " << error << "\n";
}
