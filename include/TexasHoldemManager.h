#pragma once

#include "GameManager.h"
#include <stdexcept>

class TexasHoldemManager : public GameManager
{
private:
	unsigned int smallBlind;
	unsigned int bigBlind;

	TableState currentTableState;

	void bettingRound()
	{
		int playersToAct = 0;
		for (auto& p : pPlayers)
		{
			if (!p->getHasFolded() && p->getChips() > 0) playersToAct++;
		}


		while (playersToAct > 0)
		{
			for (auto& pPlayer : pPlayers)
			{
				// every player made decision
				if (playersToAct <= 0) break;

				// every player who folded or played all-in are skipped
				if (pPlayer->getHasFolded() || pPlayer->getChips() == 0) continue;


				if (this->currentTableState.currentHighestBet <= pPlayer->getCurrentBet()) this->currentTableState.amountToCall = 0;
				else currentTableState.amountToCall = this->currentTableState.currentHighestBet - pPlayer->getCurrentBet();

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
					int activePlayers = 0;
					for (auto& p : pPlayers)
					{
						if (!p->getHasFolded() && p->getChips() > 0) activePlayers++;
					}
					playersToAct = activePlayers - 1; // -1 because person who raised did their move
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
	
	void blindsPhase()
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

	void preFlopPhase()
	{
		this->deck.shuffleDeck();
		for (auto& pPlayer : pPlayers)
		{
			pPlayer->setCards(deck.drawCard(), deck.drawCard());
		}

		bettingRound();

	}

	void flopPhase()
	{

	}

	void turnPhase()
	{

	}

	void riverPhase()
	{

	}

	void showdownPhase()
	{

	}

	void cleanupPhase()
	{

	}

public: 
	TexasHoldemManager(std::shared_ptr<IOutputHandler> pOutputHandler) : GameManager(pOutputHandler), smallBlind(10), bigBlind(20) 
	{
		deck = Deck(DeckType::STANDARD);
		currentTableState.amountToCall = 0;
		currentTableState.currentHighestBet = 0;
		currentTableState.currentPot = 0;

	}

	void playRound() override
	{
		if (pPlayers.size() < 2) throw std::range_error("ERROR NOT ENOUGH PLAYERS");

	}

	void setSmallBlind(unsigned int newSmallBlindBet)
	{
		this->smallBlind = newSmallBlindBet;
	}

	void setBigBlind(unsigned int newBigBlindBet)
	{
		this->bigBlind = newBigBlindBet;
	}
};