#include <iostream>
#include <string>
#include <vector>
#include "HandScore.h"
#include "Cards.h"
#include "HandEvaluator.h"
#include "CardFormatter.h"
#include "../tests/include/TesterCLI.h"

TesterCLI::TesterCLI(const std::vector<Card>& deck)
{
    this->deckCopy = deck;
}

void TesterCLI::runTest()
{
    std::cout << "CLI TEST FOR POKER ---- TO RUN EVALUATE INPUT R" << std::endl;

    getCardFromList();

    char decision = '0';


    std::cin >> decision;

    if (decision == 'R')
    {
        printYourCardsAndHand();
    }
    else if (decision == 'E') exit(0);
}

void TesterCLI::setDeckAndReset(const std::vector<Card>& newDeck)
{
    this->deckCopy = newDeck;
    this->currentlyUsing.clear();
}


void TesterCLI::printCardsListFromDeck()
{
    int i = 1;
    std::cout << "CARDS LIST FROM DECK:" << std::endl;
    for (const auto& card : this->deckCopy)
    {
        std::cout << i++ << ". " << CardFormatter::getCardName(card).wholeCardString() << std::endl;;
    }
}

void TesterCLI::getCardFromList()
{
    int userInput;
    int n = 1;


    while (n <= 7) {
        printCardsListFromDeck();
        std::cout << std::endl;
        std::cout << "Card ID: ";
        std::cin >> userInput;

        --userInput;

        std::cout << std::endl;
        if (userInput >= 0 && userInput < deckCopy.size() && deckCopy[userInput].rank != CardRank::NONE && deckCopy[userInput].suit != CardSuit::NONE)
        {
            Card card = this->deckCopy[userInput];
            this->deckCopy[userInput].suit = CardSuit::NONE;
            this->deckCopy[userInput].rank = CardRank::NONE;
            currentlyUsing.push_back(card);
            ++n;
        }
        
    }

}

void TesterCLI::printYourCardsAndHand()
{
    std::cout << "Your cards: " << std::endl;

    for (auto& card : currentlyUsing)
    {
        CardStrings cardStr = CardFormatter::getCardName(card);
        std::cout << CardFormatter::getCardName(card).wholeCardString() << std::endl;
    }

    HandScore handScore = HandEvaluator::Evaluate(this->currentlyUsing);
    std::cout << "Your highest hand: " << CardFormatter::getHandName(handScore.hand) << std::endl;
    std::cout << "Used cards:" << std::endl;

    for (const auto& card : handScore.usedCardsInHand)
    {
        std::cout << CardFormatter::getCardName(card).wholeCardString() << std::endl;
    }

}