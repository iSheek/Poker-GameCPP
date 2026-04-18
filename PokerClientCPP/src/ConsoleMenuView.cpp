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
}

void ConsoleMenuView::showIPInput()
{
	std::cout << ansiToClear;
}

void ConsoleMenuView::showPortInput()
{
	std::cout << ansiToClear;
}

void ConsoleMenuView::showBotCountInput()
{
	std::cout << ansiToClear;
}
