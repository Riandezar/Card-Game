#include "card.h"
#include <vector>

class Deck {
    public:
        Deck();
        void fillDeck();
        Card drawCard();
        void shuffle();
        int cardsRemaining() const {return deck.size();}
        bool isEmpty() const {return deck.empty();}
    private:
       std::vector<Card> deck;
};