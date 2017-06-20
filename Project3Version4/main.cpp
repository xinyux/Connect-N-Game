// main.cpp

#include "provided.h"
#include <string>
#include <iostream>
using namespace std;

int main()
{
    // Start a game with a board, size of 4 by 4
    // 3 checkers in a line gives a winner
    SmartPlayer smart1("smart1");
    HumanPlayer human1("human1");
    Game g1(4, 4, 3, &human1, &smart1);
    g1.play();
}
