#include "BaseGameApplication.h"
#include "TexasHoldemManager.h"
#include "HumanPlayerLogic.h"
#include "BotPlayerLogic.h"


void BaseGameApplication::startSingleplayer()
{
	TexasHoldemManager manager{ this->pOutput };

	auto mainPlayer = std::make_shared<HumanPlayerLogic>(this->startingChips, this->pInput);

	manager.addPlayer(mainPlayer);

	for (int i = 0; i < (playerCount-1); ++i)
	{
		auto bot = std::make_shared<BotPlayerLogic>(this->startingChips);
		manager.addPlayer(bot);
	}
}

void BaseGameApplication::startMultiplayer()
{

}
