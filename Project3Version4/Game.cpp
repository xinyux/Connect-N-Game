// Game.cpp

#include <iostream>
#include <vector>
#include "provided.h"
using namespace std;

class GameImpl
{
public:
    GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black);
    bool completed(int& winner) const;
    bool takeTurn();
    void play();
    int checkerAt(int c, int r) const;
    ~GameImpl() {
//        delete m_grid;
    }
private:
    Player * m_red, * m_black;
    int cur_player = RED, m_N;
    unique_ptr<Scaffold> m_grid;
    bool m_haswinner = false;
    
    void haswinner(int lastmove, int color);
    bool inbound(int row, int col);
};

GameImpl::GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black) : m_grid(new Scaffold(nColumns, nLevels))
{
    m_red = red;
    m_black = black;
    m_N = N;
}

bool GameImpl::completed(int& winner) const
{
    if (m_haswinner) {
        winner = 1 - cur_player;
        return true;
    }
    
    if (m_grid->numberEmpty() == 0) {
        winner = TIE_GAME;
        return true;
    }
    
    return false;
}

bool GameImpl::takeTurn()
{
    int winner;
    if (completed(winner)) {
        if (winner == RED) {
            cout << "Player " << m_red->name() << " wins!\n";
            cout << "Checker RED wins" << endl;
        } else if (winner == BLACK) {
            cout << "Player " << m_black->name() << " wins!\n";
            cout << "Checker BLACK wins" << endl;
        } else {
            cout << "Tie game!\n";
        }
        return false;
    }
    
    if (cur_player == RED) {
        cout << "RED's turn\n";
        int move = m_red->chooseMove((*m_grid), m_N, RED);
        m_grid->makeMove(move, RED);
        haswinner(move, RED);
        cur_player = BLACK;
    } else {
        cout << "BLACK's turn\n";
        int move = m_black->chooseMove((*m_grid), m_N, BLACK);
        m_grid->makeMove(move, BLACK);
        haswinner(move, BLACK);
        cur_player = RED;
    }
    
    return true;
}

void GameImpl::play()
{
    m_grid->display();
    while (takeTurn()) {
        cin.ignore();
        m_grid->display();
    }
}

int GameImpl::checkerAt(int c, int r) const
{
    return m_grid->checkerAt(c, r);
}

// give last move, check if some one wins, if win, set m_haswinner flag to true
void GameImpl::haswinner(int lastmove, int color) {
    vector<pair<int, int>> direction = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, 1}, {1, -1}, {-1, -1}, {1, 1}};
    
    int i = m_grid->levels(), j = lastmove;
    for (; i >= 1; --i){
        if (m_grid->checkerAt(j, i) != VACANT) break;
    }
    
    for (int k = 0; k < direction.size(); k += 2) {
        int deltarow1 = direction[k].first, deltacol1 = direction[k].second;
        int row = i + deltarow1, col = j + deltacol1;
        
        int cnt = 1;
        while (inbound(row, col)) {
            if (m_grid->checkerAt(col, row) == color) {
                cnt++;
                col += deltacol1;
                row += deltarow1;
            } else break;
        }
        
        int deltarow2 = direction[k+1].first, deltacol2 = direction[k+1].second;
        row = i + deltarow2, col = j + deltacol2;
        while (inbound(row, col)) {
            if (m_grid->checkerAt(col, row) == color) {
                cnt++;
                col += deltacol2;
                row += deltarow2;
            } else break;
        }
        
        if (cnt >= m_N) {
            m_haswinner = true;
            return;
        }
    }
    
}

bool GameImpl::inbound(int row, int col) {
    if (row < 1 || col < 1 || row > m_grid->levels() || col > m_grid->cols()) return false;
    return true;
}

//******************** Game functions *******************************

// These functions simply delegate to GameImpl's functions.
// You probably don't want to change any of this code.

Game::Game(int nColumns, int nLevels, int N, Player* red, Player* black)
{
    m_impl = new GameImpl(nColumns, nLevels, N, red, black);
}

Game::~Game()
{
    delete m_impl;
}

bool Game::completed(int& winner) const
{
    return m_impl->completed(winner);
}

bool Game::takeTurn()
{
    return m_impl->takeTurn();
}

void Game::play()
{
    m_impl->play();
}

int Game::checkerAt(int c, int r) const
{
    return m_impl->checkerAt(c, r);
}
