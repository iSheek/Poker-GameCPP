/**
 * @file ConsolePlayerChannel.cpp
 * @brief File containing definition of ConsolePlayerChannel's methods
 */

#include "ConsolePlayerChannel.h"
#include "CardFormatter.h"
#include "ConsoleUtils.h"
#include "ConsoleCONSTANS.h"
#include "HandEvaluator.h"
#include "HandScore.h"
#include <iostream>
#include <limits>
#include <Windows.h>
#include <thread>
#include <filesystem>
#include <string>
#include <string_view>


constexpr auto LOGFILE_NAME = "playersmoveinfo.log";

int ConsolePlayerChannel::askForValueToRaise(int currentHighestBet, int playersCurrentChips, int xPlacement, int yPlacement)
{
	int valueToRaise = 0;

	bool validRaise = false;

	while (!validRaise) {
		ConsoleUtils::printAt(xPlacement, yPlacement++, "HOW MUCH (0 to go back): ");
		while (!(std::cin >> valueToRaise))
		{
			ConsoleUtils::printAt(xPlacement, yPlacement++, "BAD VALUE!");
			std::cin.clear();
			std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
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

PlayerAction ConsolePlayerChannel::requestAction(const TableState& tableState, const PlayerState& playerState)
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
			std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
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

void ConsolePlayerChannel::onPlayersCardDealt(const Card& card)
{
	this->playersCardsGraphics.push_back(ConsoleUtils::generateCardGraphic(card));
}

ConsolePlayerChannel::ConsolePlayerChannel()
{
    // unlock ANSI sequences in windows
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    std::filesystem::path logDir = std::filesystem::current_path() / "logs";

    std::filesystem::create_directories(logDir);

    std::filesystem::path logPath = logDir / LOGFILE_NAME;

    this->logFile.open(logPath);
    if (!logFile.is_open())
    {
        throw std::runtime_error("ERROR FILE WASN'T OPENED");
    }
    // sequence turning off line wrapping
    std::cout << "\033[?7l";

}

ConsolePlayerChannel::~ConsolePlayerChannel()
{
    this->logFile.close();

    // allow line wrapping again
    std::cout << "\033[?7h";
}

int ConsolePlayerChannel::getConsoleWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }
    return MAX_LINE_LENGTH; // return basic value if any errors
}

void ConsolePlayerChannel::startOverwritingConsole()
{
    std::cout << "\033[H";
}

void ConsolePlayerChannel::addLog(std::string_view message)
{
    if (!logFile.is_open()) return;

    logFile << message << '\n';
    logFile.flush();

    this->uiLogs.push_back(static_cast<std::string>(message));
    if (uiLogs.size() > MAX_LOGS_IN_CONSOLE)
    {
        uiLogs.erase(uiLogs.begin());
    }

}

void ConsolePlayerChannel::renderTable(const TableState& tableState, const std::vector<PublicPlayerInfo>& publicPlayersInfo)
{
    // startOverwritingConsole();

    system("cls");

    int startingXForPlayerInfo = MAX_LINE_LENGTH / static_cast<int>((publicPlayersInfo.size()));

    // int maxTextForName = MAX_LINE_LENGTH / publicPlayersInfo.size() - 4;
    int maxTextForName = startingXForPlayerInfo - 2;

    int xForPlayerInfo = startingXForPlayerInfo;


    for (const auto& playerInfo : publicPlayersInfo)
    {
        std::string name = playerInfo.name;
        if (name.length() > maxTextForName && maxTextForName > 0)
        {
            name = name.substr(0, maxTextForName);
        }

        ConsoleUtils::printAt(xForPlayerInfo, Y_FOR_PLAYERS_INFO, name);

        std::string currentChips = "CHIPS: " + std::to_string(playerInfo.chips);
        ConsoleUtils::printAt(xForPlayerInfo, Y_FOR_PLAYERS_INFO + 1, currentChips);

        std::string currentBet = "CURRENT BET: " + std::to_string(playerInfo.currentBet);
        ConsoleUtils::printAt(xForPlayerInfo, Y_FOR_PLAYERS_INFO + 2, currentBet);

        std::string totalBet = "TOTAL BET: " + std::to_string(playerInfo.totalBet);
        ConsoleUtils::printAt(xForPlayerInfo, Y_FOR_PLAYERS_INFO + 3, totalBet);

        if (playerInfo.hasFolded)
        {
            ConsoleUtils::printAt(xForPlayerInfo, Y_FOR_PLAYERS_INFO + 4, "FOLDED");
        }

        xForPlayerInfo += startingXForPlayerInfo;

    }



    int xForCommunityCards = (MAX_LINE_LENGTH - ((CARD_WIDTH * 4 / 3) * MAX_COMMUNITY_CARDS)) / 2;
    int yForCommunityCards = STARTING_Y_FOR_COMMUNITY_CARDS;

    for (const auto& card : tableState.communityCards)
    {
        auto cardGraphic = ConsoleUtils::generateCardGraphic(card);
        for (const auto& graphicLine : cardGraphic)
        {
            ConsoleUtils::printAt(xForCommunityCards, yForCommunityCards++, graphicLine);

        }
        xForCommunityCards += (CARD_WIDTH * 4 / 3);
        yForCommunityCards = STARTING_Y_FOR_COMMUNITY_CARDS;
    }






    int xForInfo = STARTING_X_FOR_LOGS, yForInfo = STARTING_Y_FOR_LOGS;

    ConsoleUtils::printAt(xForInfo, yForInfo++, "====================================");
    ConsoleUtils::printAt(xForInfo, yForInfo++, "MAIN POT: " + std::to_string(tableState.currentPot));
    ConsoleUtils::printAt(xForInfo, yForInfo++, "HIGHEST BET: " + std::to_string(tableState.highestBetInHistory));

    ConsoleUtils::printAt(xForInfo, yForInfo++, "====================================");

    ConsoleUtils::printAt(xForInfo, yForInfo++, "==== LOGS ====");
    for (const auto& log : uiLogs)
    {
        ConsoleUtils::printAt(xForInfo, yForInfo++, log);
    }

}

std::string ConsolePlayerChannel::actionToString(PlayerAction action)
{
    std::string toReturn = ": ";

    switch (action.actionType)
    {
    case ActionType::FOLD:
        toReturn += "FOLD";
        break;
    case ActionType::CALL:
        toReturn += "CALL";
        break;
    case ActionType::CHECK:
        toReturn += "CHECK";
        break;
    case ActionType::RAISE:
        toReturn += ("RAISE TO " + std::to_string(action.amount));
        break;
    default:
        toReturn += "???";
        break;
    }

    return toReturn;

}


void ConsolePlayerChannel::onPlayerAction(const std::string& playerName, const PlayerAction& action)
{

    this->addLog(playerName + actionToString(action));
}


void ConsolePlayerChannel::onShowdown(const std::vector<std::string>& winnerNames, const HandScore& winningHand, const int& pot)
{
    std::string winnerLog = "SHOWDOWN WON BY: ";
    for (auto& w : winnerNames) winnerLog += w + " ";
    winnerLog += "WITH: " + CardFormatter::getHandName(winningHand.hand) + " (" + std::to_string(pot) + ")";

    this->addLog(winnerLog);
}


void ConsolePlayerChannel::checkIfConsoleSizeIsEnough()
{
    while (true)
    {
        int currentWidth = getConsoleWidth();

        if (currentWidth >= MAX_LINE_LENGTH) {
            break;
        }

        std::cout << "\033[2J\033[H"; // clears console and starts to overwrite
        std::cout << "YOU HAVE TOO THIN CONSOLE FOR PROPER GRAPHIC" << std::endl;
        std::cout << "PLEASE WIDEN IT TO PLAY" << std::endl;

        // sleep so we won't use too much cpu unnecessarily
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void ConsolePlayerChannel::onCommunityCardDealt(const Card& card)
{
    this->communityCardsGraphics.push_back(ConsoleUtils::generateCardGraphic(card));
}

std::string ConsolePlayerChannel::getCurrentHandString(const std::vector<Card>& communityCards, const std::array<Card, 2>& playersCards) const
{
    std::vector<Card> cardsToEvaluate = communityCards;
    cardsToEvaluate.insert(cardsToEvaluate.end(), playersCards.begin(), playersCards.end());
    HandScore currentHandScore = HandEvaluator::Evaluate(cardsToEvaluate);

    return CardFormatter::getHandName(currentHandScore.hand);
}
