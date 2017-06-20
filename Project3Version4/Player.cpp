// Player.cpp

#include "provided.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define BIGNUMBER 100000

class HumanPlayerImpl
{
public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class BadPlayerImpl
{
public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class SmartPlayerImpl
{
public:
    int chooseMove(const Scaffold& s, int N, int color);
private:
    int winGame(Scaffold & s, int lastMove, int color, int N);
    bool inbound(Scaffold & s, int row, int col);
    int decideMove(Scaffold & grid, int N, int color, int depth, int & score);
};

int HumanPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    Scaffold grid = s;
    int column;
    do {
        cout << "What column do you want to drop? (1 is the leftmost column) " << endl;
        cin >> column;
    } while (!grid.makeMove(column, color));
    return column;
}

int BadPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    Scaffold grid = s;
    int column = 1;
    for (; column <= s.cols(); ++column) {
        if (grid.makeMove(column, color)) return column;
    }
    return column;
}

int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    Scaffold grid = s;
    int score = INT_MIN;
    return decideMove(grid, N, color, 0, score);
}

int SmartPlayerImpl::decideMove(Scaffold & grid, int N, int color, int depth, int & score) {
    int res = 1;
    if (depth % 2 == 0) {
        
        int bestScore = INT_MIN;
        for (int col = 1; col <= grid.cols(); ++col) {
            if (grid.makeMove(col, color)) {
                int curScore = bestScore;
                int gameStatus = winGame(grid, col, color, N);
                if (gameStatus == 1) {
                    curScore = BIGNUMBER - depth;
                } else if (gameStatus == 0) {
                    curScore = 0;
                } else {
                    decideMove(grid, N, 1 - color, depth+1, curScore);
                }
                if (curScore > bestScore) {
                    bestScore = curScore;
                    res = col;
                }
                grid.undoMove();
            }
        }
        score = bestScore;
        
    } else {
        
        int bestScore = INT_MAX;
        for (int col = 1; col <= grid.cols(); ++col) {
            if (grid.makeMove(col, color)) {
                int curScore = bestScore;
                
                int gameStatus = winGame(grid, col, color, N);
                if (gameStatus == 1) {
                    curScore = -(BIGNUMBER - depth);
                } else if (gameStatus == 0) {
                    curScore = 0;
                } else {
                    decideMove(grid, N, 1 - color, depth+1, curScore);
                }
                
                if (curScore < bestScore) {
                    bestScore = curScore;
                    res = col;
                }
                grid.undoMove();
            }
        }
        score = bestScore;
        
    }
    
    return res;
}

// if color wins, return 1
// if tie, return 0
// if don't know, return -1
int SmartPlayerImpl::winGame(Scaffold & grid, int lastmove, int color, int N) {
    vector<pair<int, int>> direction = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, 1}, {1, -1}, {-1, -1}, {1, 1}};
    
    int i = grid.levels(), j = lastmove;
    for (; i >= 1; --i){
        if (grid.checkerAt(j, i) != VACANT) break;
    }
    
    for (int k = 0; k < direction.size(); k += 2) {
        int deltarow = direction[k].first, deltacol = direction[k].second;
        int row = i + deltarow, col = j + deltacol;
        
        int cnt = 1;
        while (inbound(grid, row, col)) {
            if (grid.checkerAt(col, row) == color) {
                cnt++;
                col += deltacol;
                row += deltarow;
            } else break;
        }
        if (cnt >= N) {
            return 1;
        }
    }
    
    if (grid.numberEmpty() == 0) {
        return 0;
    }
    
    return -1;
}

// return if both row and col is valid
bool SmartPlayerImpl::inbound(Scaffold & grid, int row, int col) {
    if (row < 1 || col < 1 || row > grid.levels() || col > grid.cols()) return false;
    return true;
}
//******************** Player derived class functions *************************

// These functions simply delegate to the Impl classes' functions.
// You probably don't want to change any of this code.

HumanPlayer::HumanPlayer(string nm)
: Player(nm)
{
    m_impl = new HumanPlayerImpl;
}

HumanPlayer::~HumanPlayer()
{
    delete m_impl;
}

int HumanPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

BadPlayer::BadPlayer(string nm)
: Player(nm)
{
    m_impl = new BadPlayerImpl;
}

BadPlayer::~BadPlayer()
{
    delete m_impl;
}

int BadPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

SmartPlayer::SmartPlayer(string nm)
: Player(nm)
{
    m_impl = new SmartPlayerImpl;
}

SmartPlayer::~SmartPlayer()
{
    delete m_impl;
}

int SmartPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}
