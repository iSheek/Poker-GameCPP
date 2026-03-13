#include <iostream>
#include "Deck.h"
#include "../tests/include/TesterCLI.h"
#include <memory>
#include "TexasHoldemManager.h"
#include "ConsoleInputHandler.h"
#include "ConsoleOutputHandler.h"
#include "HumanPlayerLogic.h"
#include "BotPlayerLogic.h"


int main() {
    try {
        auto outputHandler = std::make_shared<ConsoleOutputHandler>();
        auto inputHandler = std::make_shared<ConsoleInputHandler>();
        TexasHoldemManager manager(outputHandler);

        unsigned int startingChips = 10000;

        auto player1 = std::make_shared<HumanPlayerLogic>(startingChips, inputHandler);
        player1->setPlayerName("YOU");

        auto bot1 = std::make_shared<BotPlayerLogic>(startingChips);
        auto bot2 = std::make_shared<BotPlayerLogic>(startingChips);

        manager.addPlayer(player1);
        manager.addPlayer(bot1);
        manager.addPlayer(bot2);

        while (true) {
            manager.playRound();

            if (player1->getChips() == 0 || bot1->getChips() == 0) {
                std::cout << "\n\nYOU LOST!!!!\n";
                break;
            }

            std::cout << "\nPRESS ENTER TO CONTINUE\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
    }
    catch (const std::exception& e) {
        std::cerr << "\nFATAL ERROR: " << e.what() << "\n";
    }
    return 0;
}