// Scaffold.cpp

#include "provided.h"
#include <vector>
#include <stack>
#include <iostream>
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
    int n_cols;
    int n_levels;
    vector<vector<int>> grid;
    stack<int> moves;
};

ScaffoldImpl::ScaffoldImpl(int nColumns, int nLevels)
{
  if(nColumns > 0 && nLevels > 0) { // initialize scaffold as long as valid values are passed in
  n_cols = nColumns;
  n_levels = nLevels;
  }
  else { // if invalid scaffold rows or column numbers entered, print out an error
      cerr << "Invalid row or column number entered" << endl;
      exit(1);
  }
  grid.resize(nLevels);  // resize the vectors so that it has the correct number of rows and columns
  for (int i = 0; i < nLevels; i++)
  grid[i].resize(nColumns);

  for(int i = 0; i < nLevels; i++)  { // go to every position in the scaffold and set the value to VACANT
    for(int j = 0; j < nColumns; j++)
    grid[i][j] = VACANT;
  }
}

int ScaffoldImpl::cols() const
{
    return n_cols;  // return number of columns in scaffold
}

int ScaffoldImpl::levels() const
{
    return n_levels;  // return number of levels in the scaffold
}

int ScaffoldImpl::numberEmpty() const
{
  int numEmpty = 0; // create variable to store the number of empty spaces
    for(int i = 0; i < n_levels; i++) { // go to every position in the scaffold and count the number of empty spaces
      for(int j = 0; j < n_cols; j++) {
        if(grid[i][j] == -1)
        numEmpty++;
      }
    }
    return numEmpty; // return the number of empty spaces
}

int ScaffoldImpl::checkerAt(int column, int level) const
{
    int checkLevel = levels() - level; // change level input so that it is numbered as the vector is numbered
    if(grid[checkLevel][column - 1] == RED) // return RED if the space there has a red checker
    return RED;
    else if(grid[checkLevel][column - 1] == BLACK) // return BLACK if the space there has a black checker
    return BLACK;
    else
    return VACANT; // return vacant if it is an empty space

}

void ScaffoldImpl::display() const
{
  for(int i = 0; i < n_levels; i++) { // start by printing out a | and then going to every space and printing out the appropriate value, followed by another |
    cout << '|';
    for(int j = 0; j < n_cols; j++) {
      if(grid[i][j] == RED) // print R if there is a red checker there
      cout << 'R';
      else if(grid[i][j] == BLACK) // print B if there is a black checker there
      cout << 'B';
      else if(grid[i][j] == VACANT) // print a space if it is vacant
      cout << ' ';
      cout << '|';
    }
    cout << endl; // print new line after every row
  }

  for(int k = 0; k < n_cols + n_cols + 1; k++) { // print out the characters that are part of the base of the scaffold
    if(k == 0)
    cout << '+';
    else if(k % 2 != 0)
    cout << '-';
    else
    cout << '+';
  }
  cout << endl;
}

bool ScaffoldImpl::makeMove(int column, int color)
{
  if(column <= 0 || column > n_cols) // return false if invalid column is entered
  return false;
  for(int i = n_levels - 1; i >= 0; i--) { // start at the bottom of the scaffold and go up until the first vacant spot is found, and put the checker there
    if(grid[i][column - 1] == -1) {
      grid[i][column - 1] = color;
      moves.push(column); // store the column number of the most recently added checker to be used for the undoMove function
      return true;
    }
  }
  return false;
}

int ScaffoldImpl::undoMove()
{
  if(moves.empty() == true) // if no moves have been made previously, return 0
  return 0;
  int lastMove = moves.top(); // using the stack, see the most recently added item and pop it off, that is the column of the most recently added checker
  moves.pop();
  for(int i = 0; i < n_levels; i++) // start from the top and go down until you find the first non-vacant space and make that space vacant
  {
    if(grid[i][lastMove - 1] != -1) {
      grid[i][lastMove - 1] = -1;
      return lastMove;
    }
  }
  return 0;
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
