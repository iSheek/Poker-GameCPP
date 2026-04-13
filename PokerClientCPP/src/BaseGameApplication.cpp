#include "BaseGameApplication.h"
#include "TexasHoldemManager.h"
#include "HumanPlayerLogic.h"
#include "BotPlayerLogic.h"
#include <chrono>
#include <iostream>
#include <thread>


void BaseGameApplication::startSingleplayer()
{
	TexasHoldemManager manager{ this->pOutput };

	auto mainPlayer = std::make_shared<HumanPlayerLogic>(this->startingChips, this->pInput);
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

void BaseGameApplication::startMultiplayer()
{

}
