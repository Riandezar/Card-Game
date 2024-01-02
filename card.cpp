#include "card.h"
#include <string>

/*
Constructor that creates a card with a given rank and suit (Rank and Suit are defined enums of card)
Parameters: Rank, Suit
Returns: None
*/
Card::Card(Rank rank, Suit suit){
    this->rank = rank;
    this->suit = suit;
}

/*
Default constructor that creates an empty Card
Used to represent players with no cards
*/
Card::Card(){
    
}

/*
Gives the string of a given suit
Parameters: Suit
Returns: string
*/
std::string Card::suitToString(Suit suit) const {
    switch (suit) {
        case Suit::clubs:
            return "clubs";
        case Suit::diamonds:
            return "diamonds";
        case Suit::hearts:
            return "hearts";
        case Suit::spades:
            return "spades";
    }
    return "error";
}

/*
Gives the string of a given rank
Parameters: Rank
Returns: string
*/
std::string Card::rankToString(Rank rank) const {
    switch (rank) {
        case Rank::ace:
            return "ace";
        case Rank::jack:
            return "jack";
        case Rank::queen:
            return "queen";
        case Rank::king:
            return "king";
    }
    return std::to_string(int(rank));
}

/*
Overloads the < (less than) operator to compare which of 2 cards wins according to the game rules
Parameters: Card, Card (Card1 < Card2)
Returns bool
*/
bool operator<(const Card &card1, const Card &card2) {
    if(card1.getRank() < card2.getRank())
        return true;
    else if(card1.getRank() > card2.getRank())
        return false;
    else if(card1.getSuit() < card2.getSuit())
        return true;
    else
        return false;
}

/*
Overloads the > (Greater than) operator to compare which of 2 cards wins according to the game rules
Parameters: Card, Card (card1 > card2)
Returns bool
*/
bool operator>(const Card& card1, const Card &card2) {
    return !operator<(card1, card2);
}

/*
Overloads the << (ostream) operator to print the rank and suit of a given card
Parameters: ostream, card (std::cout << card)
Returns ostream
*/
std::ostream& operator<<(std::ostream& out, const Card& card) {
    out << card.rankToString(card.getRank()) << " of " << card.suitToString(card.getSuit());
    return out;
}