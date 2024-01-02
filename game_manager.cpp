#include "game_manager.h"
#include <string>
#include <sstream>
#include <chrono>
#include <thread>
#include <algorithm>

/*
Initializes the game by prompting the user to enter the number of players
This function error checks input and creates a player vector size of number players inputted
Parameters: None
Returns: None
*/
void GameManager::initializeGame() {
    int numPlayers = 0;
    std::string inputLine;

    do  {
        std:: cout << "Enter number of players (2-5): ";
        std::getline(std::cin, inputLine);
        std::stringstream ss(inputLine);
        ss >> numPlayers;
        if (numPlayers < 2 || numPlayers > 5 || !ss.eof()){
            std::cout << "Invlaid input try again" << "\n";
            numPlayers = 0;
        }
        std::cin.clear();
    } while(numPlayers < 2 || numPlayers > 5);

    players.clear();
    players.reserve(numPlayers);
    for(int i = 0; i < numPlayers; i++) {
        players.push_back(Player());
    }
    deck.shuffle();
}

/*
Creates the game loop of the game
Calls the helper functions for the game to be played (timer, getPlayerInput, calculateWinningPlayer)
Parameters: None
Returns: None
*/
void GameManager::play() {
    bool stillPlaying = true;

    do {
        doneDrawing = false;
        std::thread t1(&GameManager::timer, this);

        if(deck.cardsRemaining() < players.capacity()) {
            std::cout << "Not enough cards to deal to all players, shuffling deck.\n";
            deck.fillDeck();
            deck.shuffle();
        }

        while(!doneDrawing){
            getPlayerInput();
        }

        t1.join();

        calculateWinningPlayer();

    } while(stillPlaying);
}

/*
Calculates the winning player
Looks through the players vector for the winning card according to game rules
Parameters: None
Returns: None
*/
void GameManager::calculateWinningPlayer() {
    int winningPlayer = 0;
    bool someoneDrew = false;
    for(int i = 1; i < players.capacity(); i++) {
        if(!players[winningPlayer].getDrew() && players[i].getDrew()){
            winningPlayer = i;
            someoneDrew = true;
        }
        else if(players[winningPlayer].getDrew() && players[i].getDrew()){
            someoneDrew = true;
            if(players[winningPlayer].getPlayerCard() < players[i].getPlayerCard()) {
                winningPlayer = i;
            }
        }
    }
    if(someoneDrew) {
        std::cout << "Player " << winningPlayer+1 << " wins with " 
        << players[winningPlayer].getPlayerCard() << "\n";
    }
    else {
        std::cout << "No player drew a card, it's a draw!\n";
    }
    std::cout << "Next round will start in 5 seconds.\n";
    std::this_thread::sleep_for(std::chrono::seconds(5));
    for(int i = 0; i < players.capacity(); i++) {
        players[i].setDrew(false);
        players[i].setPlayerCard(Card());
    }
}

/*
Creates a timer that ticks down for how long the round is
The timer starts at 15 seconds and displays time remaining every 5 seconds
When the timer is done sets the atomic doneDrawing variable to true
Parameters: None
Returns: None
*/
void GameManager::timer(){
    for (int i = 15; i >= 0; i -= 5) {
        if(doneDrawing)
            break;
	    std::cout << "\nTime remaining: " << i << " seconds\n";
        if(i != 0)
	        std::this_thread::sleep_for(std::chrono::seconds(5));
	}
    doneDrawing = true;
}

/*
Accepts input for players to draw cards
Players draw a card by inputting their player number
If all players have drawn, sets the atomic doneDrawing to true
Error checks for bad input and does not allow players to draw multiple cards
Parameters: None
Returns: None
*/
void GameManager::getPlayerInput() {
    std::string inputLine;
    int inputNumber = 0;
    if(std::all_of(players.begin(), players.end(), [](Player& p){return p.getDrew();})){
        doneDrawing = true;
    }
    if(!doneDrawing){
        std::cout << "Cards left in deck: " << deck.cardsRemaining() << "\n";
        std::cout << "Enter your player number to draw a card: ";
        std::getline(std::cin, inputLine);
        std::stringstream ss(inputLine);
        ss >> inputNumber;
        std::cin.clear();
        if (inputNumber < 1 || inputNumber > players.capacity() || !ss.eof()){
            std::cout << "Invalid input try again" << "\n";
        }
        else if(players.at(inputNumber-1).getDrew()){
            std::cout << "Player " << inputNumber << " has already drew.\n";
        }
        else {
            players.at(inputNumber-1).setPlayerCard(deck.drawCard());
            players.at(inputNumber-1).setDrew(true);
            std::cout << "Player " << inputNumber << " drew: " 
            << players[inputNumber-1].getPlayerCard() << "\n";
        }
    }
}