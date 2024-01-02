#include "card.h"

class Player {
    public:
        void setDrew(bool didDraw) {drew = didDraw;}
        void setPlayerCard(Card card) {playerCard = card;}
        bool getDrew() {return drew;}
        Card getPlayerCard() {return playerCard;}
        Player();
    private:
        bool drew;
        Card playerCard;
};