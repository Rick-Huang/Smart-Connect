// Game.cpp

#include "provided.h"
#include "support.h"
#include <iostream>

using namespace std;

class GameImpl
{
  public:
    GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black);
    bool completed(int& winner) const;
    bool takeTurn();
    void play();
    int checkerAt(int c, int r) const;
private:
    Scaffold board;
    int nToWin;
    Player* redPlayer;
    Player* blackPlayer;
    int turn;
};

GameImpl::GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black)
: board(nColumns, nLevels)
{
    nToWin = N; // initialize private member variables to the correct starting values to play the game properly
    redPlayer = red;
    blackPlayer = black;
    turn = RED;
}

bool GameImpl::completed(int& winner) const
{
    return completedSupport(board, winner, nToWin); // call completeSupport function in support.cpp
}

bool GameImpl::takeTurn()
{
    if(completed(turn) == true) // if the game is over, return false because no more moves need to be made
    return false;
    int move = 0; // declare move variable that stores the position of the move
    if(turn == RED) // have redPlayer make move it is red's turn, else allow black player to make its move
    move = redPlayer->chooseMove(board, nToWin, turn);
    else
    move = blackPlayer->chooseMove(board, nToWin, turn);
    board.makeMove(move, turn);
    if(turn == RED) // change turn so that the next iteration of takeTurn is the other player
    turn = BLACK;
    else
    turn = RED;
    return true;
}

void GameImpl::play()
{
    int thisWinner = -2; // declare function that stores the winner, set value to -2, which will be considered the default null value
    cout << "Connect N Game" << endl; // print useul lines for the game
    if(redPlayer->isInteractive() == true)
    cout << "Interactive Red Player: " << redPlayer->name() << endl;
    else
    cout << "Non-interactive Red Player: " << redPlayer->name() << endl;
    if(blackPlayer->isInteractive() == true)
    cout << "Interactive Black Player: " << blackPlayer->name() << endl;
    else
    cout << "Non-interactive Black Player: " << blackPlayer->name() << endl;
    board.display(); // display the game board
    while(completed(thisWinner) == false) // continue to play the game as long as the game is not over
    {
        takeTurn(); // call takeTurn function for the game to take turns
        board.display(); // display the board after each turn
        if(redPlayer->isInteractive() == false || blackPlayer->isInteractive() == false) { // prompt for user input when playing with a non-interactive player
            cout << "Press enter to continue." << endl;
			cin.ignore(10000, '\n');
        }
    }
    if(thisWinner == RED) // print out the correct lines for who won
    cout << redPlayer -> name() << " wins!" << endl;
    else if(thisWinner == BLACK)
    cout << blackPlayer -> name() << " wins!" << endl;
    else
    cout << "TIE GAME, THERE IS NO WINNER" << endl;
}

int GameImpl::checkerAt(int c, int r) const // call checkerAt function within Scaffold.cpp
{
    return board.checkerAt(c, r);
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
