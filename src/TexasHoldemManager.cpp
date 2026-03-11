
#include "TexasHoldemManager.h"

// when making ux outside console add commented methods from IOutputHandler

TexasHoldemManager::TexasHoldemManager(std::shared_ptr<IOutputHandler> pOutputHandler) : GameManager(pOutputHandler), smallBlind(10), bigBlind(20)
{
	deck = Deck(DeckType::STANDARD);
	currentTableState.amountToCall = 0;
	currentTableState.currentHighestBet = 0;
	currentTableState.currentPot = 0;

}

void TexasHoldemManager::playRound()
{
	if (pPlayers.size() < 2) throw std::range_error("ERROR NOT ENOUGH PLAYERS");

	blindsPhase();
	preFlopPhase();
	flopPhase();
	turnPhase();
	riverPhase();
	showdownPhase();
	cleanupPhase();
}

void TexasHoldemManager::bettingRound(unsigned int startingIndex)
{
	int playersToAct = 0;
	for (auto& p : pPlayers)
	{
		if (!p->getHasFolded() && p->getChips() > 0) playersToAct++;
	}


	while (playersToAct > 0)
	{
		for (unsigned int i = 0; i < pPlayers.size(); i++)
		{
			// every player made decision
			if (playersToAct <= 0) break;

			unsigned int currentPlayerIndex = (startingIndex + i) % pPlayers.size();

			auto& pPlayer = pPlayers[currentPlayerIndex];

			// every player who folded or played all-in are skipped
			if (pPlayer->getHasFolded() || pPlayer->getChips() == 0) continue;


			if (this->currentTableState.currentHighestBet <= pPlayer->getCurrentBet()) this->currentTableState.amountToCall = 0;
			else currentTableState.amountToCall = this->currentTableState.currentHighestBet - pPlayer->getCurrentBet();

			if (this->pOutputHandler)
			{
				std::vector<PublicPlayerInfo> publicInfo;
				publicInfo.reserve(pPlayers.size());
				
				for (const auto& p : pPlayers)
				{
					publicInfo.push_back({
						p->getPlayerName(),
						p->getChips(),
						p->getCurrentBet(),
						p->getHasFolded()
						});

				}

				this->pOutputHandler->renderTable(this->currentTableState, publicInfo);
			}

			// we ask player for decision
			PlayerAction playerDecision = pPlayer->makeDecision(currentTableState);

			// player has made a decision
			--playersToAct;

			switch (playerDecision.actionType)
			{
			case ActionType::CALL:
			{
				unsigned int actualCallAmount = std::min(this->currentTableState.amountToCall, pPlayer->getChips());
				pPlayer->removeChips(actualCallAmount);
				pPlayer->addToCurrentBet(actualCallAmount);
				this->currentTableState.currentPot += actualCallAmount;
				break;
			}
			case ActionType::CHECK:
				// during check we just skip
				break;
			case ActionType::RAISE:
			{
				// we count how much player need to add to the new bet from his current bet
				unsigned int amountToAdd = playerDecision.amount - pPlayer->getCurrentBet();

				pPlayer->addToCurrentBet(amountToAdd);
				pPlayer->removeChips(amountToAdd);

				this->currentTableState.currentPot += amountToAdd;
				this->currentTableState.currentHighestBet = playerDecision.amount;

				// someone raised - playersToAct counter resets, everyone besides the person who raise has to make their move
				playersToAct = 0;
				for (auto& p : pPlayers)
				{
					if (!p->getHasFolded() && p->getChips() > 0 && p != pPlayer)
					{
						++playersToAct;
					}
				}
				break;
			}
			case ActionType::FOLD:
				pPlayer->fold();
				break;
			default:
				break;
			}
		}
	}

}

void TexasHoldemManager::blindsPhase()
{
	if (pPlayers.size() < 2) throw std::range_error("ERROR NOT ENOUGH PLAYERS");

	this->currentTableState.currentHighestBet = smallBlind;

	unsigned int p1Chips = pPlayers[0]->getChips();
	if (p1Chips <= currentTableState.currentHighestBet)
	{
		// ALL IN
		pPlayers[0]->setCurrentBet(p1Chips);
		pPlayers[0]->removeChips(p1Chips);
		this->currentTableState.currentPot += p1Chips;
	}
	else
	{
		pPlayers[0]->setCurrentBet(smallBlind);
		pPlayers[0]->removeChips(smallBlind);
		this->currentTableState.currentPot += smallBlind;
	}

	this->currentTableState.currentHighestBet = bigBlind;

	unsigned int p2Chips = pPlayers[1]->getChips();
	if (p2Chips <= bigBlind)
	{
		// ALL IN
		pPlayers[1]->setCurrentBet(p2Chips);
		pPlayers[1]->removeChips(p2Chips);
		this->currentTableState.currentPot += p2Chips;
	}
	else
	{
		pPlayers[1]->setCurrentBet(bigBlind);
		pPlayers[1]->removeChips(bigBlind);
		this->currentTableState.currentPot += bigBlind;
	}
}

void TexasHoldemManager::preFlopPhase()
{
	this->deck.shuffleDeck();
	for (auto& pPlayer : pPlayers)
	{
		if (deck.getCardsLeft() >= 2) pPlayer->setCards(deck.drawCard(), deck.drawCard());
		else throw std::out_of_range("ERROR THERE'S NOT ENOUGH CARDS IN DECK TO PLAY");
	}

	unsigned int startIndex = (pPlayers.size() == 2) ? SMALL_BLIND_PLAYER_INDEX : UNDER_THE_GUN_PLAYER_INDEX;
	bettingRound(startIndex);

}

void TexasHoldemManager::flopPhase()
{
	int foldedPlayers = 0;
	for (auto const& p : pPlayers)
	{
		if (p->getHasFolded()) ++foldedPlayers;
	}

	if (pPlayers.size() - foldedPlayers < 2) return;


	deck.drawCard(); // dealer throws away one card

	// dealer puts 3 community cards
	this->currentTableState.communityCards.push_back(deck.drawCard());
	this->currentTableState.communityCards.push_back(deck.drawCard());
	this->currentTableState.communityCards.push_back(deck.drawCard());

	currentTableState.currentHighestBet = 0;
	for (auto& pPlayer : pPlayers)
	{
		if (!pPlayer->getHasFolded()) pPlayer->setCurrentBet(0);
	}

	unsigned int startIndex = (pPlayers.size() == 2) ? BIG_BLIND_PLAYER_INDEX : SMALL_BLIND_PLAYER_INDEX;
	bettingRound(startIndex);

}

void TexasHoldemManager::turnPhase()
{
	int foldedPlayers = 0;
	for (auto const& p : pPlayers)
	{
		if (p->getHasFolded()) ++foldedPlayers;
	}

	if (pPlayers.size() - foldedPlayers < 2) return;

	deck.drawCard(); // dealer throws away one card

	this->currentTableState.communityCards.push_back(deck.drawCard());

	currentTableState.currentHighestBet = 0;
	for (auto& pPlayer : pPlayers)
	{
		if (!pPlayer->getHasFolded()) pPlayer->setCurrentBet(0);
	}

	unsigned int startIndex = (pPlayers.size() == 2) ? BIG_BLIND_PLAYER_INDEX : SMALL_BLIND_PLAYER_INDEX;
	bettingRound(startIndex);

}

void TexasHoldemManager::riverPhase()
{
	int foldedPlayers = 0;
	for (auto const& p : pPlayers)
	{
		if (p->getHasFolded()) ++foldedPlayers;
	}

	if (pPlayers.size() - foldedPlayers < 2) return;

	deck.drawCard(); // dealer throws away one card

	this->currentTableState.communityCards.push_back(deck.drawCard());

	currentTableState.currentHighestBet = 0;
	for (auto& pPlayer : pPlayers)
	{
		if (!pPlayer->getHasFolded()) pPlayer->setCurrentBet(0);
	}

	unsigned int startIndex = (pPlayers.size() == 2) ? BIG_BLIND_PLAYER_INDEX : SMALL_BLIND_PLAYER_INDEX;
	bettingRound(startIndex);
}

void TexasHoldemManager::showdownPhase()
{
	if (this->pOutputHandler)
	{
		std::vector<PublicPlayerInfo> publicInfo;
		publicInfo.reserve(pPlayers.size());

		for (const auto& p : pPlayers)
		{
			publicInfo.push_back({
				p->getPlayerName(),
				p->getChips(),
				p->getCurrentBet(),
				p->getHasFolded()
				});

		}

		this->pOutputHandler->renderTable(this->currentTableState, publicInfo);
	}


	std::optional<HandScore> biggestHandScore = std::nullopt;
	std::vector<std::shared_ptr<PlayerLogicParent>> winners;


	// Evaluate and find winner/winners
	for (auto& pPlayer : pPlayers)
	{
		if (pPlayer->getHasFolded()) continue;
		std::vector<Card> cardsToUse = this->currentTableState.communityCards;
		std::array<Card, 2> playersCards = pPlayer->getPlayerCards();
		cardsToUse.insert(cardsToUse.end(), playersCards.begin(), playersCards.end());

		HandScore playerHandScore = HandEvaluator::Evaluate(cardsToUse);

		if (!biggestHandScore.has_value() || playerHandScore > biggestHandScore.value())
		{
			biggestHandScore = playerHandScore;
			winners.clear();
			winners.push_back(pPlayer);
		}
		else if (biggestHandScore.value() == playerHandScore)
		{
			winners.push_back(pPlayer);
		}
	}

	if (!winners.empty())
	{
		unsigned int splitAmount = this->currentTableState.currentPot / winners.size();

		unsigned int restFromSplit = this->currentTableState.currentPot - (splitAmount * winners.size());

		for (auto& winner : winners)
		{
			winner->addChips(splitAmount);
		}

		if (restFromSplit > 0)
		{
			for (auto& winner : winners)
			{
				winner->addChips(restFromSplit);
				break;
			}
		}
	}

}

void TexasHoldemManager::cleanupPhase()
{
	this->currentTableState.resetForNewRound();

	for (auto& pPlayer : pPlayers)
	{
		pPlayer->resetForNewRound();
	}

	// remove players who doesnt have any chips
	pPlayers.erase(
		std::remove_if(pPlayers.begin(), pPlayers.end(), [](const std::shared_ptr<PlayerLogicParent>& p)
			{return p->getChips() == 0; }), pPlayers.end());

	if (pPlayers.size() > 1)
	{
		std::rotate(pPlayers.begin(), pPlayers.begin() + 1, pPlayers.end());
	}
}