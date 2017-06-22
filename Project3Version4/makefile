OBJS = main.o Player.o Scaffold.o Game.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -std=c++11 -c $(DEBUG)
LFLAGS = -Wall -std=c++11 $(DEBUG)

# -Wall 
# Directs g++ to give warnings about code that’s probably in error

# -g
# Generates debugging information that is used by gdb-based debuggers

main: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o main

main.o: main.cpp provided.h
	$(CC) $(CFLAGS) main.cpp

Player.o: Player.cpp provided.h
	$(CC) $(CFLAGS) Player.cpp

Scaffold.o: Scaffold.cpp provided.h
	$(CC) $(CFLAGS) Scaffold.cpp

Game.o: Game.cpp provided.h 
	$(CC) $(CFLAGS) Game.cpp 

clean:
	-rm *.o 
