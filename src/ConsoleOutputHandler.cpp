
#include "ConsoleOutputHandler.h"
#include "HandScore.h"
#include "CardFormatter.h"
#include <string>
#include <iostream>
#include <Windows.h>
#include <thread>
#include "HandEvaluator.h"

constexpr auto LOGFILE_NAME = "playersmoveinfo.log";
constexpr int MAX_LOGS_IN_CONSOLE = 10;
constexpr int MAX_LINE_LENGTH = 80;

constexpr int CARD_WIDTH = 9;
constexpr int CARD_LENGTH = 7;

constexpr char CARD_OUTLINE_CHARACTER = '&';

ConsoleOutputHandler::ConsoleOutputHandler()
{
    // unlock ANSI sequences in windows
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    this->logFile.open(LOGFILE_NAME);
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

void ConsoleOutputHandler::renderTable(const TableState& tableState)
{

    std::cout << "\n====================================\n";
    std::cout << "POT: " << tableState.currentPot << " $\n";
    std::cout << "HIGHEST BET: " << tableState.currentHighestBet << " $\n";
    std::cout << "COMMUNITY CARDS: ";

    if (tableState.communityCards.empty()) {
        std::cout << "(NO CARDS)";
    }
    else {
        for (const auto& card : tableState.communityCards) {
            std::cout << "[" << CardFormatter::getCardName(card).wholeCardString() << "] ";
        }
    }
    std::cout << "\n====================================\n";
}


std::vector<std::string> ConsoleOutputHandler::generateCardGraphic(const Card& card)
{
    CardStrings cardStrings = CardFormatter::getCardName(card);
    std::string cardRank = cardStrings.cardRankStr;
    char cardSuitFirstLetter = cardStrings.cardSuitStr[0];

    std::vector<std::string> toReturn;
    toReturn.reserve(CARD_LENGTH);
    std::string lineOfCard(CARD_WIDTH, ' ');

    std::string topAndBottom(CARD_WIDTH, CARD_OUTLINE_CHARACTER);

    toReturn.push_back(topAndBottom);

    lineOfCard[0] = CARD_OUTLINE_CHARACTER;
    lineOfCard[lineOfCard.size() - 1] = CARD_OUTLINE_CHARACTER; 

    for (size_t i = 0; i < CARD_LENGTH - 2; i++)
    {
        std::string toPush = lineOfCard;
        if (i == 0)
        {
            toPush.replace(1, cardRank.size(), cardRank);
        }
        else if (i == ((CARD_LENGTH / 2) - 1))
        {
            toPush[(toPush.size() - 1) / 2] = cardSuitFirstLetter;
        }
        toReturn.push_back(toPush);
    }

    toReturn.push_back(topAndBottom);

    return toReturn;
}

// TODO implement methods

void ConsoleOutputHandler::onPlayerAction(const std::string& playerName, PlayerAction action)
{
    
}


void ConsoleOutputHandler::onShowdown(const std::vector<std::shared_ptr<PlayerLogicParent>>& winners, const HandScore& winningHand, unsigned int pot)
{

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
    this->communityCardsGraphics.push_back(generateCardGraphic(card));
}

std::string ConsoleOutputHandler::getCurrentHandString(const std::vector<Card>& communityCards, const std::array<Card, 2>& playersCards) const
{
    std::vector<Card> cardsToEvaluate = communityCards;
    cardsToEvaluate.insert(cardsToEvaluate.end(), playersCards.begin(), playersCards.end());
    HandScore currentHandScore = HandEvaluator::Evaluate(cardsToEvaluate);

    return CardFormatter::getHandName(currentHandScore.hand);
}