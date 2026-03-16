#include <iostream>
#include "Deck.h"
#include "../tests/include/TesterCLI.h"
#include <memory>
#include "TexasHoldemManager.h"
#include "ConsoleInputHandler.h"
#include "ConsoleOutputHandler.h"
#include "HumanPlayerLogic.h"
#include "BotPlayerLogic.h"
#include <thread>
#include <chrono>
#include <boost/asio.hpp>
#include <nlohmann/json.hpp>

using asiotcp = boost::asio::ip::tcp;
using json = nlohmann::json;

constexpr int PORT = 1234;

int main() {
    //try {
    //    auto outputHandler = std::make_shared<ConsoleOutputHandler>();
    //    auto inputHandler = std::make_shared<ConsoleInputHandler>();
    //    TexasHoldemManager manager(outputHandler);

    //    unsigned int startingChips = 10000;

    //    auto player1 = std::make_shared<HumanPlayerLogic>(startingChips, inputHandler);
    //    player1->setPlayerName("YOU");

    //    auto bot1 = std::make_shared<BotPlayerLogic>(startingChips);
    //    auto bot2 = std::make_shared<BotPlayerLogic>(startingChips);

    //    manager.addPlayer(player1);
    //    manager.addPlayer(bot1);
    //    manager.addPlayer(bot2);

    //    while (true) {
    //        manager.playRound();

    //        if (player1->getChips() == 0 || bot1->getChips() == 0) {
    //            std::this_thread::sleep_for(std::chrono::milliseconds(500));
    //            std::cout << "\n\nYOU LOST!!!!\n";
    //            break;
    //        }

    //        std::cout << "\nPRESS ENTER TO CONTINUE\n";
    //        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //        std::cin.get();
    //    }
    //}
    //catch (const std::exception& e) {
    //    std::cerr << "\nFATAL ERROR: " << e.what() << "\n";
    //}

    try
    {
        boost::asio::io_context io_context;

        asiotcp::acceptor acceptor(io_context, asiotcp::endpoint(asiotcp::v4(), PORT));

        std::cout << "SERVER WAITING FOR PLAYERS... \n";

        // std::vector<asiotcp::socket> allSockets;


        asiotcp::socket socket(io_context);

        acceptor.accept(socket);

        std::cout << "USER HAS CONNECTED\n";


        std::string message;

        Card testCard = { CardSuit::HEARTS, CardRank::ACE };

        json j = testCard;

        std::string toSend = j.dump() + '\n';

        
        boost::system::error_code error;
        boost::asio::write(socket, boost::asio::buffer(toSend), error);

 
    }
    catch (std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
    }


    return 0;
}