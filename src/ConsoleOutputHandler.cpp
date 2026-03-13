
#include "ConsoleOutputHandler.h"
#include "HandScore.h"
#include "CardFormatter.h"
#include <string>
#include <iostream>
#include <Windows.h>
#include <thread>
#include "HandEvaluator.h"
#include "ConsoleUtils.h"
#include "ConsoleCONSTANS.h"
#include <filesystem>

constexpr auto LOGFILE_NAME = "playersmoveinfo.log";


ConsoleOutputHandler::ConsoleOutputHandler()
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

ConsoleOutputHandler::~ConsoleOutputHandler()
{
    this->logFile.close();

    // allow line wrapping again
    std::cout << "\033[?7h";
}

int ConsoleOutputHandler::getConsoleWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }
    return MAX_LINE_LENGTH; // return basic value if any errors
}

void ConsoleOutputHandler::startOverwritingConsole()
{
    std::cout << "\033[H";
}

void ConsoleOutputHandler::addLog(const std::string& message)
{
    if (!logFile.is_open()) return;

    logFile << message << '\n';
    logFile.flush();

    this->uiLogs.push_back(message);
    if (uiLogs.size() > MAX_LOGS_IN_CONSOLE)
    {
        uiLogs.erase(uiLogs.begin());
    }

}

void ConsoleOutputHandler::renderTable(const TableState& tableState, const std::vector<PublicPlayerInfo>& publicPlayersInfo)
{   
    // startOverwritingConsole();

    system("cls");

    int startingXForPlayerInfo = MAX_LINE_LENGTH / (publicPlayersInfo.size());

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
        ConsoleUtils::printAt(xForPlayerInfo, Y_FOR_PLAYERS_INFO+1, currentChips);

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
    ConsoleUtils::printAt(xForInfo, yForInfo++, "HIGHEST BET: " + std::to_string(tableState.currentHighestBet));

    ConsoleUtils::printAt(xForInfo, yForInfo++, "===================================="); 

    ConsoleUtils::printAt(xForInfo, yForInfo++, "==== LOGS ====");
    for (const auto& log : uiLogs)
    {
        ConsoleUtils::printAt(xForInfo, yForInfo++, log);
    }

}

std::string ConsoleOutputHandler::actionToString(PlayerAction action)
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
        toReturn += ("RAISE " + std::to_string(action.amount) + " MORE");
        break;
    default:
        toReturn += "???";
        break;
    }

    return toReturn;

}


void ConsoleOutputHandler::onPlayerAction(const std::string& playerName, PlayerAction action)
{

    this->addLog(playerName + actionToString(action));
}


void ConsoleOutputHandler::onShowdown(const std::vector<std::shared_ptr<PlayerLogicParent>>& winners, const HandScore& winningHand, unsigned int pot)
{
    std::string winnerLog = "SHOWDOWN WON BY: ";
    for (auto& w : winners) winnerLog += w->getPlayerName() + " ";
    winnerLog += "WITH: " + CardFormatter::getHandName(winningHand.hand) + " (" + std::to_string(pot) + ")";

    this->addLog(winnerLog);
}


void ConsoleOutputHandler::checkIfConsoleSizeIsEnough()
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

void ConsoleOutputHandler::onCommunityCardDealt(const Card& card)
{
    this->communityCardsGraphics.push_back(ConsoleUtils::generateCardGraphic(card));
}

std::string ConsoleOutputHandler::getCurrentHandString(const std::vector<Card>& communityCards, const std::array<Card, 2>& playersCards) const
{
    std::vector<Card> cardsToEvaluate = communityCards;
    cardsToEvaluate.insert(cardsToEvaluate.end(), playersCards.begin(), playersCards.end());
    HandScore currentHandScore = HandEvaluator::Evaluate(cardsToEvaluate);

    return CardFormatter::getHandName(currentHandScore.hand);
}
