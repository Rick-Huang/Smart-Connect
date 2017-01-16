// Player.cpp

#include "provided.h"
#include "support.h"
#include <string>
#include <iostream>
using namespace std;

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
};

int HumanPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    if(s.numberEmpty() == 0) // if the board is full, return -1 because there are no valid moves that can be played
    return -1;
    int input = 0; // create variable called input that stores the value of the input
    cout << "Please enter move > "; // prompts user to enter move
    cin >> input;
    while(input < 1 || input > s.cols()) { // if move is not valid, prompt player to enter a valid move
        cout << "Please enter a valid move > ";
        cin >> input;
    }
    while(s.checkerAt(input, s.levels()) != VACANT) { // if the column the player entered is full, prompt player to enter a column that is not full
        cout << "That column is full, please choose another > ";
        cin >> input;
    }
    return input; // return the valid input from the user
}

int BadPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    if(s.numberEmpty() == 0) // if the board is full, return -1 because there are no valid moves that can be played
    return -1;
    for(int i = 1; i <= s.cols(); i++) { // starting from the first column, just put a piece in that column until it is full
        if(s.checkerAt(i, s.levels()) == VACANT)
        return i;
    }
}

int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
  if(s.numberEmpty() == 0) // if the board is full, return -1 because there are no valid moves that can be played
  return -1;
    Scaffold b = s; // create scaffold object and copy in the value of s, the columns of b can be manipulated to allow for the determineBestComputerMove function to determine the best move
    int finalRating = -2; // create a variable called finalRating that is passed by reference in to the function, initially set at -2 which is considered to be the null value
    if(s.numberEmpty() == (s.cols() * s.levels()))
        return (s.cols()/2);
    int bestMove = determineBestComputerMove(b, color, finalRating, N, 0); // call determineBestComputerMove function in support.cpp to determine the best move
    return bestMove; // return that best move
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
