card: main.o card.o deck.o player.o game_manager.o 
	g++ main.o card.o deck.o player.o game_manager.o 

main.o: main.cpp
	g++ -c main.cpp

card.o: card.cpp
	g++ -c card.cpp

deck.o: deck.cpp
	g++ -c deck.cpp

game_manager.o: game_manager.cpp
	g++ -c game_manager.cpp

player.o: player.cpp
	g++ -c player.cpp
