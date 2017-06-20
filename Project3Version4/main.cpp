// main.cpp

#include "provided.h"
#include <string>
#include <iostream>
using namespace std;

int main()
{
    SmartPlayer smart1("smart1");
    HumanPlayer human1("human1");
    Game g1(4, 4, 3, &human1, &smart1);
    g1.play();
    

}
