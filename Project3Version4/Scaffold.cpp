// Scaffold.cpp

#include <iostream>
#include <vector>
#include <stack>
#include "provided.h"
using namespace std;

class ScaffoldImpl
{
  public:
    ScaffoldImpl(int nColumns, int nLevels); 
    int cols() const;
    int levels() const;
    int numberEmpty() const;
    int checkerAt(int column, int level) const; 
    void display() const; 
    bool makeMove(int column, int color); 
    int undoMove();
  private:
    int m_col, m_row, m_empty;
    vector<vector<int>> m_grid;
    vector<int> m_vacant;
    stack<int> m_move;
};

ScaffoldImpl::ScaffoldImpl(int nColumns, int nLevels)
{
    if (nColumns <= 0 || nLevels<=0) {
        cerr << "Columns and Levels Must be Positive!";
        exit(1);
    }
    
    m_col = nColumns;
    m_row = nLevels;
    m_empty = nColumns * nLevels;
    m_vacant = vector<int> (nColumns, nLevels - 1);
    m_grid.resize(nLevels);
    for (int i = 0; i < nLevels; ++i) {
      m_grid[i] = vector<int> (nColumns, VACANT);
    }
}

int ScaffoldImpl::cols() const
{
    return m_col;
}

int ScaffoldImpl::levels() const
{
    return m_row;
}

int ScaffoldImpl::numberEmpty() const
{
    return m_empty;
}

int ScaffoldImpl::checkerAt(int column, int level) const
{
    return m_grid[m_row-level][column-1];  
}

void ScaffoldImpl::display() const
{
    for (int i = 0; i < m_row; ++i) {
      string row = "|";
      for (int j = 0; j < m_col; ++j) {
        if (m_grid[i][j] == VACANT) {
          row.push_back(' ');
        } else if (m_grid[i][j] == RED) {
          row.push_back('R');
        } else {
          row.push_back('B');
        }
        row.push_back('|');
      }
      cout << row << endl;
  }
  
    string endrow;
    for (int k = 0; k < m_col; k++) endrow += "+-" ;
    endrow.push_back('+');
    cout << endrow << endl;
}

bool ScaffoldImpl::makeMove(int column, int color)
{
    if (column < 1 || column > m_col || m_vacant[column-1] < 0) return false;

    m_grid[m_vacant[column-1]][column-1] = color;
    --m_vacant[column-1];
    --m_empty;
    m_move.push(column-1);
    
    return true;
}

int ScaffoldImpl::undoMove()
{
    if (m_move.empty()) return 0;
    
    int lastmove = m_move.top();
    m_move.pop();
    
    m_grid[m_vacant[lastmove]+1][lastmove] = VACANT;
    ++m_vacant[lastmove];
    ++m_empty;

    return lastmove+1;
}

//******************** Scaffold functions *******************************

// These functions simply delegate to ScaffoldImpl's functions.
// You probably don't want to change any of this code.

Scaffold::Scaffold(int nColumns, int nLevels)
{
    m_impl = new ScaffoldImpl(nColumns, nLevels);
}
 
Scaffold::~Scaffold()
{
    delete m_impl;
}
 
Scaffold::Scaffold(const Scaffold& other)
{
    m_impl = new ScaffoldImpl(*other.m_impl);
}
 
Scaffold& Scaffold::operator=(const Scaffold& rhs)
{
    if (this != &rhs)
    {
        Scaffold temp(rhs);
        swap(m_impl, temp.m_impl);
    }
    return *this;
}
 
int Scaffold::cols() const
{
    return m_impl->cols();
}

int Scaffold::levels() const
{
    return m_impl->levels();
}

int Scaffold::numberEmpty() const
{
    return m_impl->numberEmpty();
}

int Scaffold::checkerAt(int column, int level) const
{
    return m_impl->checkerAt(column, level);
}
 
void Scaffold::display() const
{
    m_impl->display();
}
 
bool Scaffold::makeMove(int column, int color)
{
    return m_impl->makeMove(column, color);
}
 
int Scaffold::undoMove()
{
    return m_impl->undoMove();
}
