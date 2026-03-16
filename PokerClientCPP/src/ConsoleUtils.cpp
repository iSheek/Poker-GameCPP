
#include "ConsoleUtils.h"
#include "ConsoleCONSTANS.h"

std::vector<std::string> ConsoleUtils::generateCardGraphic(const Card& card)
{
    CardStrings cardStrings = CardFormatter::getCardName(card);
    std::string cardRank = cardStrings.cardRankStr;
    char cardSuitFirstLetter = cardStrings.cardSuitStr[0];

    std::vector<std::string> toReturn;
    toReturn.reserve(CARD_LENGTH);
    std::string lineOfCard(CARD_WIDTH, ' ');

    std::string topAndBottom(CARD_WIDTH, CARD_OUTLINE_CHARACTER);

    toReturn.push_back(topAndBottom);

    lineOfCard[0] = CARD_OUTLINE_CHARACTER;
    lineOfCard[lineOfCard.size() - 1] = CARD_OUTLINE_CHARACTER;

    for (size_t i = 0; i < CARD_LENGTH - 2; i++)
    {
        std::string toPush = lineOfCard;
        if (i == 0)
        {
            toPush.replace(1, cardRank.size(), cardRank);
        }
        else if (i == ((CARD_LENGTH / 2) - 1))
        {
            toPush[(toPush.size() - 1) / 2] = cardSuitFirstLetter;
        }
        toReturn.push_back(toPush);
    }

    toReturn.push_back(topAndBottom);

    return toReturn;
}