#include "deck.h"
#include "player.h"
#include <vector>
#include <atomic>

class GameManager {
    public:
        void initializeGame();
        void play();
        void getPlayerInput();
        void calculateWinningPlayer();
        void timer();
    private:
        std::vector<Player> players;
        Deck deck;
        std::atomic<bool> doneDrawing;
};