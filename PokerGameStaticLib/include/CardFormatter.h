#pragma once

/**
 * @file CardFormatter.h
 * @brief File containing declaration of CardFormatter class
 */


#include "Cards.h"
#include "HandScore.h"
#include <string>

/**
 * @brief A structure used for holding a string of card's rank and suit
 */
struct CardStrings
{
    std::string cardRankStr{ "" };  ///< string representation of card's rank
    std::string cardSuitStr {""};   ///< string representation of card's suit
    
    /**
     * @brief Function for getting both card's rank and suit into one string
     *
     * @return one string with both rank and suit together (with space between)
     */
    std::string wholeCardString()   
    {
        return this->cardRankStr + " " + this->cardSuitStr;
    }
};


/**
 * @brief A class that gives access to functions for text representation of card and hand
 * 
 */
class CardFormatter
{
private:

public:
    /**
     * @brief Function used for getting string representation of whole card
     * @param[in] card 
     * @return CardStrings structure
     */
    static CardStrings getCardName(const Card& card);


    /**
     * @brief Function used for getting text representation of hand's name
     * @param[in] hand
     * @return string containing hand's name
     */
    static std::string getHandName(PokerHand hand);
};
