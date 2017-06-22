main: main.o Player.o Scaffold.o Game.o
	g++ -Wall -std=c++11 main.o Player.o Scaffold.o Game.o -o main

main.o: main.cpp provided.h
	g++ -Wall -std=c++11 -c main.cpp

Player.o: Player.cpp provided.h
	g++ -Wall -std=c++11 -c Player.cpp

Scaffold.o: Scaffold.cpp provided.h
	g++ -Wall -std=c++11 -c Scaffold.cpp

Game.o: Game.cpp provided.h
	g++ -Wall  -std=c++11 -c Game.cpp

clean:
	-rm *.o