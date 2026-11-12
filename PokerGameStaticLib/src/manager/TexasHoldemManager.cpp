/**
 * @file TexasHoldemManager.cpp
 * @brief File containing definition of TexasHoldemManager methods
 */

#include "TexasHoldemManager.h"
#include "BettingRules.h"
#include "PotCalculator.h"
#include "ShowdownResult.h"
#include <algorithm>
#include <optional>

// when making ux outside console add commented methods from IOutputHandler

TexasHoldemManager::TexasHoldemManager(std::shared_ptr<IOutputHandler> pOutputHandler) : GameManager(pOutputHandler), smallBlind(10), bigBlind(20)
{
	deck = Deck(DeckType::STANDARD);
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

std::vector<PublicPlayerInfo> TexasHoldemManager::getEveryPlayersPublicInfo() const
{
	std::vector<PublicPlayerInfo> publicInfo;
	publicInfo.reserve(pPlayers.size());

	for (const auto& p : pPlayers)
	{
		publicInfo.push_back({
			p->getPlayerName(),
			p->getChips(),
			p->getCurrentBet(),
			p->getTotalBet(),
			p->getHasFolded()
			});

	}

	return publicInfo;
}


void TexasHoldemManager::bettingRound(int startingIndex)
{
	this->currentTableState.lastFullRaiseAmount = bigBlind;

	int playersToAct{};
	int playerIndex{};
	for (int i{}; i < pPlayers.size(); ++i)
	{
		if (!pPlayers[i]->getHasFolded() && pPlayers[i]->getChips() > 0)
		{
			playersToAct++;
			playerIndex = i;
		}
	}

	// if there's only one nonfolded player with chips and he doesn't have to even his bet, then we are skipping betting round
	if (playersToAct == 1 && pPlayers[playerIndex]->getCurrentBet() >= this->currentTableState.currentHighestBet)
	{
		return;
	}

	while (playersToAct > 0)
	{
		for (int i = 0; i < pPlayers.size(); i++)
		{
			// every player made decision
			if (playersToAct <= 0) break;

			int currentPlayerIndex = (startingIndex + i) % pPlayers.size();

			auto& pPlayer = pPlayers[currentPlayerIndex];

			// every player who folded or played all-in are skipped
			if (pPlayer->getHasFolded() || pPlayer->getChips() == 0) continue;


			if (this->currentTableState.currentHighestBet <= pPlayer->getCurrentBet()) this->currentTableState.amountToCall = 0;
			else currentTableState.amountToCall = this->currentTableState.currentHighestBet - pPlayer->getCurrentBet();

			if (this->outputHandlers.size() != 0)
			{
				std::vector<PublicPlayerInfo> publicInfo{ getEveryPlayersPublicInfo() };		

				for (const auto& pOutputHandler : outputHandlers)
				{
					if (!pOutputHandler) continue;
					pOutputHandler->renderTable(this->currentTableState, publicInfo);
				}
			}

			// we ask player for decision
			PlayerAction playerDecision = pPlayer->makeDecision(currentTableState);

			

			// validation of player's decision
			BettingRules::AvailableOptions validPlayerOptions{ BettingRules::getPossibleOptions(this->currentTableState, pPlayer->getPlayerState()) };

			// if player tried doing something illegal, then we are changing his action into fold
			if (!BettingRules::isActionValid(validPlayerOptions, playerDecision))
			{
				playerDecision.actionType = ActionType::FOLD;
				playerDecision.amount = 0;
			}



			// player has made a decision
			--playersToAct;

			switch (playerDecision.actionType)
			{
			case ActionType::CALL:
			{
				int actualCallAmount = std::min(this->currentTableState.amountToCall, pPlayer->getChips());
				pPlayer->removeChips(actualCallAmount);
				pPlayer->addToCurrentBet(actualCallAmount);
				pPlayer->addToTotalBet(actualCallAmount);
				this->currentTableState.currentPot += actualCallAmount;


				// changing amount for broadcasting it to the other players
				playerDecision.amount = actualCallAmount;
				break;
			}
			case ActionType::CHECK:
				// during check we just skip
				break;
			case ActionType::RAISE:
			{
				// we count how much player need to add to the new bet from his current bet
				int amountToAdd = playerDecision.amount - pPlayer->getCurrentBet();


				pPlayer->addToCurrentBet(amountToAdd);
				pPlayer->addToTotalBet(amountToAdd);
				pPlayer->removeChips(amountToAdd);

				int raiseDifference{ playerDecision.amount - this->currentTableState.currentHighestBet };

				if (raiseDifference > this->currentTableState.lastFullRaiseAmount)
				{
					this->currentTableState.lastFullRaiseAmount = raiseDifference;
				}

				this->currentTableState.currentPot += amountToAdd;

				if (this->currentTableState.currentHighestBet < playerDecision.amount)
				{
					this->currentTableState.currentHighestBet = playerDecision.amount;
				}
				
							

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
				pPlayer->fold();
				break;
			}

			for (const auto& pOutputHandler : outputHandlers)
			{
				if (!pOutputHandler) continue;
				pOutputHandler->onPlayerAction(pPlayer->getPlayerName(), playerDecision);
			}

			// if there's only max one player, then we don't ask another players
			if (std::count_if(pPlayers.begin(), pPlayers.end(), [](const std::shared_ptr<PlayerLogicParent>& a) { return !a->getHasFolded(); }) <= 1)
			{
				return;
			}
		}
	}

}

void TexasHoldemManager::blindsPhase()
{
	if (pPlayers.size() < 2) throw std::range_error("ERROR NOT ENOUGH PLAYERS");

	this->currentTableState.currentHighestBet = smallBlind;


	int p1Chips = pPlayers[0]->getChips();
	if (p1Chips <= currentTableState.currentHighestBet)
	{
		// ALL IN
		pPlayers[0]->setCurrentBet(p1Chips);
		pPlayers[0]->addToTotalBet(p1Chips);
		pPlayers[0]->removeChips(p1Chips);
		this->currentTableState.currentPot += p1Chips;
	}
	else
	{
		pPlayers[0]->setCurrentBet(smallBlind);
		pPlayers[0]->addToTotalBet(smallBlind);
		pPlayers[0]->removeChips(smallBlind);
		this->currentTableState.currentPot += smallBlind;
	}

	this->currentTableState.currentHighestBet = bigBlind;
	


	int p2Chips = pPlayers[1]->getChips();
	if (p2Chips <= bigBlind)
	{
		// ALL IN
		pPlayers[1]->setCurrentBet(p2Chips);
		pPlayers[1]->addToTotalBet(p2Chips);
		pPlayers[1]->removeChips(p2Chips);
		this->currentTableState.currentPot += p2Chips;
	}
	else
	{
		pPlayers[1]->setCurrentBet(bigBlind);
		pPlayers[1]->addToTotalBet(bigBlind);
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

	int startIndex = (pPlayers.size() == 2) ? SMALL_BLIND_PLAYER_INDEX : UNDER_THE_GUN_PLAYER_INDEX;
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

	int startIndex = (pPlayers.size() == 2) ? BIG_BLIND_PLAYER_INDEX : SMALL_BLIND_PLAYER_INDEX;
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

	int startIndex = (pPlayers.size() == 2) ? BIG_BLIND_PLAYER_INDEX : SMALL_BLIND_PLAYER_INDEX;
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

	int startIndex = (pPlayers.size() == 2) ? BIG_BLIND_PLAYER_INDEX : SMALL_BLIND_PLAYER_INDEX;
	bettingRound(startIndex);
}

void TexasHoldemManager::showdownPhase()
{
	std::vector<PublicPlayerInfo> publicInfo{ getEveryPlayersPublicInfo() };

	if (this->outputHandlers.size() != 0)
	{
		
		for (const auto& pOutputHandler : outputHandlers)
		{
			if (!pOutputHandler) continue;
			pOutputHandler->renderTable(this->currentTableState, publicInfo);
		}
	}

	using Pot = PotCalculator::Pot;

	std::vector<Pot> allPots{ PotCalculator::getAllPots(publicInfo) };

	std::vector<std::optional<HandScore>> allHands{};

	for (const auto& pPlayer : pPlayers)
	{
		if (pPlayer->getHasFolded())
		{
			// folded players are not evaluated
			allHands.push_back(std::nullopt);
		}
		else
		{
			std::vector<Card> cardsToUse = this->currentTableState.communityCards;
			std::array<Card, 2> playersCards = pPlayer->getPlayerCards();
			cardsToUse.insert(cardsToUse.end(), playersCards.begin(), playersCards.end());
			HandScore playerHandScore = HandEvaluator::Evaluate(cardsToUse);
			allHands.push_back(playerHandScore);
		}
	}

	std::vector<PotWinners> allPotWinners{};

	for (const auto& pot : allPots)
	{
		PotWinners potWinners{};
		potWinners.potAmount = pot.totalChips;
		std::optional<HandScore> biggestHandScore{};

		for (const auto& index : pot.authorizedPlayersIndices)
		{
			if (!biggestHandScore.has_value() || (allHands[index].has_value() && allHands[index] > biggestHandScore))
			{
				biggestHandScore = allHands[index];
			}
		}

		std::vector<int> winnersIndices{};

		for (const auto& index : pot.authorizedPlayersIndices)
		{
			if (biggestHandScore == allHands[index])
			{
				potWinners.winnersNames.push_back(pPlayers[index]->getPlayerName());
				winnersIndices.push_back(index);
			}
		}

		assert(potWinners.winnersNames.size() > 0);
		int splitAmount = pot.totalChips / static_cast<int>(winnersIndices.size());
		int restFromSplit = pot.totalChips - static_cast<int>((splitAmount * winnersIndices.size()));
		assert((splitAmount * static_cast<int>(winnersIndices.size()) + restFromSplit) == pot.totalChips);
		for (auto i : winnersIndices )
		{
			pPlayers[i]->addChips(splitAmount);
		}


		// winner the closest to the left of the dealer is getting the rest of the chips
		if (restFromSplit > 0)
		{
			assert(winnersIndices.size() > 0);

			int playerToGetRestIndex{};

			// when there's heads up (when up to 2 players are competing) then start is from BB player, otherwise from SB
			int start = pPlayers.size() > 2 ? SMALL_BLIND_PLAYER_INDEX : BIG_BLIND_PLAYER_INDEX;

			
			int distance{static_cast<int>(pPlayers.size() - 1)};

			for (auto i : winnersIndices)
			{
				// we are counting distance clockwise from start
				// adding amount of players to protect from minus sign
				if (((i - start + static_cast<int>(pPlayers.size())) % pPlayers.size()) <= distance)
				{
					distance = ((i - start + static_cast<int>(pPlayers.size())) % pPlayers.size());
					playerToGetRestIndex = i;
				}
			}

			pPlayers[playerToGetRestIndex]->addChips(restFromSplit);
		}


		if (pot.authorizedPlayersIndices.size() > 1)
		{
			// pot with only one winner is not evaluated
			potWinners.handsWereEvaluated = true;
		}

		allPotWinners.push_back(potWinners);

	}

#ifndef NDEBUG
	long sum{};
	for (const auto& pot : allPotWinners)
	{
		sum += pot.potAmount;
	}
	assert(sum == currentTableState.currentPot);
#endif

	// this vector will be for output through network
	std::vector<PlayerHand> playerHands{};
	
	// if there is only one nonfolded player then we are not showing cards
	if (std::find_if(allPotWinners.begin(), allPotWinners.end(), [](const PotWinners& a) {return a.handsWereEvaluated; }) != allPotWinners.end())
	{
		for (int i{}; i < allHands.size(); ++i)
		{
			std::optional<HandScore> hand{ allHands[i] };
			PlayerHand playerHand{};

			if (hand.has_value())
			{
				playerHand.hand = hand.value();
				playerHand.name = pPlayers[i]->getPlayerName();
				playerHands.push_back(playerHand);
			}


		}
	}

	ShowdownResult showdownResult{ allPotWinners, playerHands };

	for (const auto& pOutputHandler : outputHandlers)
	{
		if (!pOutputHandler) continue;
		pOutputHandler->onShowdown(showdownResult);
	}



}

void TexasHoldemManager::cleanupPhase()
{
	this->currentTableState.resetForNewRound();

	for (auto& pPlayer : pPlayers)
	{
		pPlayer->resetForNewRound();
	}

	// we first rotate and then remove because the other way it would move blinds two times

	if (pPlayers.size() > 1)
	{
		std::rotate(pPlayers.begin(), pPlayers.begin() + 1, pPlayers.end());
	}

	// remove players who don't have any chips
	pPlayers.erase(
		std::remove_if(pPlayers.begin(), pPlayers.end(), [](const std::shared_ptr<PlayerLogicParent>& p)
			{return p->getChips() == 0; }), pPlayers.end());



	this->deck.resetDeck();
	this->deck.shuffleDeck();
}