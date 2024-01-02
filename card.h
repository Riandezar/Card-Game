#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>

class Card {

    friend bool operator< (const Card&, const Card&);
    friend bool operator> (const Card&, const Card&);
    friend std::ostream& operator<<(std::ostream&out, const Card&);

    public:
        enum class Suit: unsigned char{
            clubs,
            diamonds,
            hearts,
            spades
        };
        enum class Rank: unsigned char{
            ace = 1,
            two = 2,
            three = 3,
            four = 4,
            five = 5,
            six = 6,
            seven = 7,
            eight = 8,
            nine = 9,
            ten = 10,
            jack = 11,
            queen = 12,
            king = 13
        };
        Card(Rank rank, Suit suit);
        Card();
        Rank getRank() const {return rank;}
        Suit getSuit() const {return suit;}
        std::string suitToString(Suit suit) const;
        std::string rankToString(Rank rank) const;

    private:
        Rank rank;
        Suit suit;
};
#endif