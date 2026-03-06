#include <iostream>
#include <string>
#include <vector>
#include "HandScore.h"
#include "Cards.h"
#include "HandEvaluator.h"
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

std::string TesterCLI::getHandName(PokerHand hand)
{
    switch (hand)
    {
    case PokerHand::ROYAL_FLUSH:     return "Royal Flush";
    case PokerHand::STRAIGHT_FLUSH:  return "Straight Flush";
    case PokerHand::FOUR_OF_A_KIND:  return "Four of a Kind";
    case PokerHand::FULL_HOUSE:      return "Full House";
    case PokerHand::FLUSH:           return "Flush";
    case PokerHand::STRAIGHT:        return "Straight";
    case PokerHand::THREE_OF_A_KIND: return "Three of a Kind";
    case PokerHand::TWO_PAIR:        return "Two Pair";
    case PokerHand::ONE_PAIR:        return "One Pair";
    case PokerHand::HIGH_CARD:       return "High Card";
    default:                         return "UNKNOWN HAND";
    }
}

std::string TesterCLI::getCardName(const Card& card)
{
    std::string rankStr;
    switch (card.rank)
    {
    case CardRank::NONE:  rankStr = "NONE"; break;
    case CardRank::ACE:   rankStr = "A"; break;
    case CardRank::KING:  rankStr = "K"; break;
    case CardRank::QUEEN: rankStr = "Q"; break;
    case CardRank::JACK:  rankStr = "J"; break;
    case CardRank::TEN:   rankStr = "10"; break;
    default:              rankStr = std::to_string((int)card.rank); break;
    }

    std::string suitStr;
    switch (card.suit)
    {
    case CardSuit::NONE:     suitStr = "NONE"; break;
    case CardSuit::HEARTS:   suitStr = " Hearts"; break;
    case CardSuit::DIAMONDS: suitStr = " Diamonds"; break;
    case CardSuit::CLUBS:    suitStr = " Clubs"; break;
    case CardSuit::SPADES:   suitStr = " Spades"; break;
    default:                 suitStr = " ???"; break;
    }

    return rankStr + suitStr;
}

void TesterCLI::printCardsListFromDeck()
{
    int i = 1;
    std::cout << "CARDS LIST FROM DECK:" << std::endl;
    for (const auto& card : this->deckCopy)
    {
        std::cout << i++ << ". " << getCardName(card) << std::endl;;
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
        std::cout << getCardName(card) << std::endl;
    }

    HandScore handScore = HandEvaluator::Evaluate(this->currentlyUsing);
    std::cout << "Your highest hand: " << getHandName(handScore.hand) << std::endl;
    std::cout << "Used cards:" << std::endl;

    for (const auto& card : handScore.usedCardsInHand)
    {
        std::cout << getCardName(card) << std::endl;
    }

}