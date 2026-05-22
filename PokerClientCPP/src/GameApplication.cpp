/**
 * @file GameApplication.cpp
 * @brief File containing definition for GameApplication's methods
 */


#include "GameApplication.h"
#include "TexasHoldemManager.h"
#include "HumanPlayerLogic.h"
#include "BotPlayerLogic.h"
#include "IOutputHandler.h"
#include "IInputHandler.h"
#include "ConsolePlayerChannel.h"
#include "ClientNetworkManager.h"
#include "ServerManager.h"
#include "boost/asio.hpp"
#include <chrono>
#include <iostream>
#include <thread>
#include <memory>


void GameApplication::startSingleplayer()
{
	TexasHoldemManager manager{ this->pHandler };

	auto mainPlayer = std::make_shared<HumanPlayerLogic>(this->startingChips, this->pHandler);
	mainPlayer->setPlayerName(this->playerName);
	manager.addPlayer(mainPlayer);

	for (int i = 0; i < (playerCount-1); ++i)
	{
		auto bot = std::make_shared<BotPlayerLogic>(this->startingChips);
		manager.addPlayer(bot);
	}

	while (true)
	{
		manager.playRound();

		if (mainPlayer->getChips() == 0)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			
			// change this line so menu view will be responsible for this
			std::cout << "\n\nYOU LOST!!! \n\n";
			break;
		}
		else if (manager.getCurrentPlayerCount() <= 1)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));

			std::cout << "\n\nYOU WON!!! \n\n";
		}

		std::cout << "\nPRESS ENTER TO CONTINUE\n";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin.get();

	}


}

void GameApplication::startMultiplayer()
{

	if (this->isHost)
	{
		pServerThread = std::make_unique<std::thread>([this]() 
			{
				try
				{
					ServerManager server(this->playerCount, this->ipAddress, this->port);
					server.acceptPlayers();
					server.startGame(this->startingChips);
				}
				catch (std::exception& e) {
					std::cout << "ERROR: " << e.what() << "\n";
				}
			});
	}


	boost::asio::io_context ioContext;
	std::shared_ptr pHandler = std::make_shared<ConsolePlayerChannel>();

	ClientNetworkManager networkManager{ ioContext, pHandler };

	std::this_thread::sleep_for(std::chrono::milliseconds(500)); // wait to let the server turn on

	networkManager.tryToConnectToServer(this->ipAddress, this->port, this->playerName);

	networkManager.runLoop();

	if(this->isHost) pServerThread->join();
}
