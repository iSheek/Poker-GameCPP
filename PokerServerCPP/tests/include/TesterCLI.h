/**
 * @file TesterCLI.h
 * @brief File containing declaration of TesterCLI class
 */
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "HandScore.h"
#include "Cards.h"
#include "HandEvaluator.h"

/**
 * @brief CLI utility for testing hand evaluation logic
 * @details Allows manual card selection from a deck to verify HandEvaluator output.
 */
class TesterCLI
{
    std::vector<Card> deckCopy; ///< Local copy of the deck used for testing
    std::vector<Card> currentlyUsing; ///< Cards selected for the current test case

public:
    /**
     * @brief Constructor
     * @param deck The deck to use for card selection
     */
    TesterCLI(const std::vector<Card>& deck);

    /**
     * @brief Runs the interactive test loop
     */
    void runTest();

    /**
     * @brief Resets the test state with a new deck
     * @param newDeck The new deck to use
     */
    void setDeckAndReset(const std::vector<Card>& newDeck);

    /**
     * @brief Prints all cards currently in the test deck
     */
    void printCardsListFromDeck();

    /**
     * @brief Prompts user to select cards from the list
     */
    void getCardFromList();

    /**
     * @brief Evaluates and prints the selected cards and the resulting hand
     */
    void printYourCardsAndHand();
};