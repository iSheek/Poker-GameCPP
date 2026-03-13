
#include "BotPlayerLogic.h"
#include <random>
#include "HandEvaluator.h"
#include <algorithm>
#include <chrono>
#include <thread>

BotPlayerLogic::BotPlayerLogic(unsigned int startingChips) : PlayerLogicParent(startingChips) 
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(1, 10);
	this->aggressiveLevel = dist(gen);

}

BotPlayerLogic::BotPlayerLogic(unsigned int startingChips, int aggressiveLevel) : PlayerLogicParent(startingChips)
{
	if (aggressiveLevel > 0 && aggressiveLevel < 11)
	{
		this->aggressiveLevel = aggressiveLevel;
	}

	else
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(1, 10);
		this->aggressiveLevel = dist(gen);
	}
	
}



PlayerAction BotPlayerLogic::makeDecision(const TableState& state)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));

    int aggressiveMoveFactor = this->aggressiveLevel;
    auto botCards = this->getPlayerCards();
    auto allCards = state.communityCards;

    if (state.communityCards.empty())
    {
        // PRE-FLOP LOGIC
        auto card1 = botCards[0].rank;
        auto card2 = botCards[1].rank;

        if (card1 == card2)
        {
            if (card1 == CardRank::ACE) aggressiveMoveFactor += 10;
            else if ((int)card1 > 10)   aggressiveMoveFactor += 6;
            else                        aggressiveMoveFactor += 3;
        }
        else
        {
            int strength1 = (card1 == CardRank::ACE) ? 14 : (int)card1;
            int strength2 = (card2 == CardRank::ACE) ? 14 : (int)card2;

            if (strength1 >= 10 && strength2 >= 10) aggressiveMoveFactor += 3;
        }
    }
    else
    {
        // POST-FLOP
        allCards.insert(allCards.end(), botCards.begin(), botCards.end());
        auto botCurrentHand = HandEvaluator::Evaluate(allCards);

        if ((int)botCurrentHand.hand > 4)
        {
            aggressiveMoveFactor += (int)botCurrentHand.hand % 5;
        }
        else
        {
            aggressiveMoveFactor -= (5 - (int)botCurrentHand.hand % 5);
        }
    }


    float riskRatio = (float)state.amountToCall / this->getChips();

    if (riskRatio < 0.1f) aggressiveMoveFactor += 5;
    else if (riskRatio < 0.5f) aggressiveMoveFactor += 1;
    else if (riskRatio < 0.9f) aggressiveMoveFactor -= 2;
    else aggressiveMoveFactor -= 5;


    int raiseChance = std::clamp(aggressiveMoveFactor, 1, 20) * 3;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100);
    int rng = dist(gen);


    unsigned int targetRaise = 0;

    if (state.currentHighestBet == 0)
    {
        if (aggressiveMoveFactor > 15) targetRaise = state.currentPot;
        else targetRaise = state.currentPot / 2;
    }
    else
    {
        if (aggressiveMoveFactor > 15) targetRaise = state.currentHighestBet * 3;
        else targetRaise = state.currentHighestBet * 2;
    }

    std::uniform_int_distribution<> distRandomBoost(0, 3);
    targetRaise += distRandomBoost(gen) * 10;
    targetRaise = (targetRaise / 10) * 10;

    unsigned int minRaise = state.currentHighestBet + 20;
    if (targetRaise < minRaise) targetRaise = minRaise;

    PlayerAction toReturn;

    if (rng <= raiseChance)
    {
        toReturn.actionType = ActionType::RAISE;
        toReturn.amount = std::min(targetRaise, this->getChips()); // protection to not do all-in if bot doesnt have more chips
    }
    else
    {
        if (state.amountToCall == 0)
        {
            toReturn.actionType = ActionType::CHECK;
            toReturn.amount = 0;
        }
        else
        {
            int callChance = std::clamp(aggressiveMoveFactor * 4, 20, 90);
            int rngCall = dist(gen);

            if (rngCall <= callChance)
            {
                toReturn.actionType = ActionType::CALL;
                toReturn.amount = std::min(state.amountToCall, this->getChips());
            }
            else
            {
                toReturn.actionType = ActionType::FOLD;
                toReturn.amount = 0;
            }
        }
    }

    return toReturn;
}