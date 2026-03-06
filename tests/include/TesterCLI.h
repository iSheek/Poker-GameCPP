#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "HandScore.h"
#include "Cards.h"
#include "HandEvaluator.h"

class TesterCLI
{
    std::vector<Card> deckCopy;
    std::vector<Card> currentlyUsing;

public:
    TesterCLI(const std::vector<Card>& deck);

    void runTest();

    void setDeckAndReset(const std::vector<Card>& newDeck);

    std::string getHandName(PokerHand hand);

    std::string getCardName(const Card& card);

    void printCardsListFromDeck();

    void getCardFromList();

    void printYourCardsAndHand();
};