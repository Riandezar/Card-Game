#include "deck.h"
#include <random>
#include <algorithm>

/*
Default constructor that creates a new deck
The deck is filled with all 52 cards of a standard deck of playing cards
The cards are in order of rank and suit
*/
Deck::Deck() {
    fillDeck();
}

/*
Clears the deck and fills it with all 52 cards of a standard deck of playing cards
The cards are in order of rank and suit
Parameters: none
Returns: none
*/
void Deck::fillDeck() {
    Card::Rank allRanks[] = {
        Card::Rank::ace,
        Card::Rank::two,
        Card::Rank::three,
        Card::Rank::four,
        Card::Rank::five,
        Card::Rank::six,
        Card::Rank::seven,
        Card::Rank::eight,
        Card::Rank::nine,
        Card::Rank::ten,
        Card::Rank::jack,
        Card::Rank::queen,
        Card::Rank::king,
    };
    Card::Suit allSuits[] = {
        Card::Suit::clubs,
        Card::Suit::diamonds,
        Card::Suit::hearts,
        Card::Suit::spades
    };

    deck.clear();
    deck.reserve(sizeof(allRanks) * sizeof(allSuits));

    for(Card::Rank rank : allRanks)
        for(Card::Suit suit : allSuits) {
            deck.push_back(Card(rank, suit));
        }
}

/*
Draws a card from the deck by popping the back of the vector
Parameters: None
Returns: Card
*/
Card Deck::drawCard() {
    Card drawnCard = deck.back();
    deck.pop_back();
    return drawnCard;
}

/*
Shuffles the deck randomly
Parameters: None
Returns: None
*/
void Deck::shuffle() {
    auto rd = std::random_device {};
    auto rng = std::default_random_engine{ rd() };
    std::shuffle(std::begin(deck), std::end(deck), rng);
}