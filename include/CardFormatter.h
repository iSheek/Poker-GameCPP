#pragma once

#include "Cards.h"
#include "HandScore.h"
#include <string>

struct CardStrings
{
    std::string cardRankStr = "";
    std::string cardSuitStr = "";
    std::string wholeCardString()
    {
        return this->cardRankStr + " " + this->cardSuitStr;
    }
};


class CardFormatter
{
private:

public:
    static CardStrings getCardName(const Card& card);

    static std::string getHandName(PokerHand hand);
};
