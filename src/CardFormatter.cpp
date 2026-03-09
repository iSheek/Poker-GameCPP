#include <CardFormatter.h>
#include <string>

CardStrings CardFormatter::getCardName(const Card& card)
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
    case CardSuit::HEARTS:   suitStr = "Hearts"; break;
    case CardSuit::DIAMONDS: suitStr = "Diamonds"; break;
    case CardSuit::CLUBS:    suitStr = "Clubs"; break;
    case CardSuit::SPADES:   suitStr = "Spades"; break;
    default:                 suitStr = "???"; break;
    }

    return { rankStr, suitStr };
}


std::string CardFormatter::getHandName(PokerHand hand)
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