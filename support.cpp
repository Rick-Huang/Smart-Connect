#include "support.h"
#include "provided.h"
#include <iostream>
#include <vector>

using namespace std;

int determineBestComputerMove(Scaffold& s, int color, int& rating, int nWin, int depth)
{
    int otherRating = -2; // initialize otherRating variable that stores the rating of the best human move, intialize to -2, which is considered null value
    int winner = -2; // initialize winner variable that stores the color of the winner, initialize to -2, which is considered null value
    int opposing = -2; // initialize opposing variable that stores the color of the opponent, initialize to -2, which is considered null value
    vector<int> ratings; // create a vector that stores the ratings of each column
    if(color == BLACK) // set opposing to be the correct color, the color of the opposing player
    opposing = RED;
    else
    opposing = BLACK;

    for(int i = 1; i <= s.cols(); i++) { // visit every column in the scaffold and play a move
        if(s.makeMove(i, color) == true) {
            if(completedSupport(s, winner, nWin) == true && winner == color) { // if a win results, store that value into the vector
                ratings.push_back(5000000 - depth);
            }
            else if(completedSupport(s, winner, nWin) == true && winner == TIE_GAME) { // if a tie results, store that value into the vector
                ratings.push_back(0 + depth);
            }
            else { // if no win or tie found, call determineBestHumanMove to determine the best next move of a human player and store that into the vector of ratings
                determineBestHumanMove(s, opposing, otherRating, nWin, depth + 1);
                ratings.push_back(otherRating); // store the rating of the human move into the vector
            }
            s.undoMove(); // undo the move that was made
        }
        else
        ratings.push_back(-999999999); // if a column is full, push a very negative value that should never be chosen to serve as a placeholder in the vector
        continue;
    }


    int bestMove = 1; // declare a variable that stores the column of the best move, initially set at 1
    int bestScore = ratings[0]; // declare a variable that stores the rating of the best move, initially set as the rating of the first column
    for(int j = 1; j < s.cols(); j++) // go through for loop, if a column has a higher rating than the initially set values, set those as the new bestMove and bestScore
    {
        if(ratings[j] > bestScore) {
            bestMove = j+1;
            bestScore = ratings[j];
        }
    }
    rating = bestScore; // set rating to be that of the bestScore
    return bestMove; // return the column of the best move
}

int determineBestHumanMove(Scaffold& s, int color, int& rating, int nWin, int depth)
{
    int otherRating = -2; // initialize otherRating variable that stores the rating of the best human move, intialize to -2, which is considered null value
    int winner = -2; // initialize winner variable that stores the color of the winner, initialize to -2, which is considered null value
    int opposing = -2; // initialize opposing variable that stores the color of the opponent, initialize to -2, which is considered null value
    vector<int> ratings; // create a vector that stores the ratings of each column
    if(color == BLACK) // set opposing to be the correct color, the color of the opposing player
    opposing = RED;
    else
    opposing = BLACK;

    for(int i = 1; i <= s.cols(); i++) { // visit every column in the scaffold and play a move
        if(s.makeMove(i, color) == true) {
            if(completedSupport(s, winner, nWin) == true && winner == color) { // if a win results, store that value into the vector
                ratings.push_back(-5000000 + depth);
            }
            else if(completedSupport(s, winner, nWin) == true && winner == TIE_GAME) { // if a tie results, store that value into the vector
                ratings.push_back(0 - depth);
            }
            else { // if no win or tie found, call determineBestComputerMove to determine the best next move of a human player and store that into the vector of ratings
                determineBestComputerMove(s, opposing, otherRating, nWin, depth + 1);
                ratings.push_back(otherRating); // store the rating of the human move into the vector
            }
            s.undoMove(); // undo the move that was made
        }
        else // if the column is full, push a very positive number that should never be chosen to serve as a placeholder in the vector
        ratings.push_back(999999999);
        continue;
    }

    int bestMove = 1; // declare a variable that stores the column of the best move, initially set at 1
    int bestScore = ratings[0]; // declare a variable that stores the rating of the best move, initially set as the rating of the first column
    for(int j = 1; j < s.cols(); j++) // go through for loop, if a column has a lower rating than the initially set values, set those as the new bestMove and bestScore
    {
        if(ratings[j] < bestScore) {
            bestMove = j+1;
            bestScore = ratings[j];
        }
    }
    rating = bestScore; // return the lowest score
    return bestMove; // return the column of the lowest score
}

bool completedSupport(const Scaffold& board, int& winner, int nToWin)
{
    int counterType = -2; // initialize a variable to store the color of the
    int counter = 0;
    if(board.cols() >= nToWin) { // if there are enough columns for there to be a horizonal win
        for(int i = 1; i <= board.levels(); i++) { // check horizontal
            counterType = -2;
            counter = 0;
            for(int j = 1; j <= board.cols(); j++) {
                if(board.checkerAt(j, i) == VACANT) { // if a vacant spot is found, reset the counter back to 0
                    counter = 0;
                    counterType = -2;
                    continue;
                }
                else if(board.checkerAt(j, i) != VACANT) { // if the spot is not vacant
                    if(counterType == -2) { // if the counterType is set at null, set counterType to be the color of that node and set counter to be 1
                        counterType = board.checkerAt(j, i);
                        counter = 1;
                        continue;
                    }
                    else if(board.checkerAt(j, i) == counterType) { // if the checker is the same as the counterType, increment counter by 1
                        counter++;
                    }
                    else { // if the checker is the opposite color as counterType, set counter to 1 and set counterType to be that color
                        counter = 1;
                        counterType = board.checkerAt(j, i);
                        continue;
                    }
                }
                if(counter == nToWin) { // if the counter is the same number as the number of connections needed to win, return the color and return true
                    winner = counterType;
                    return true;
                }
            }
        }
    }

    counterType = -2; // reset values of counter and counterType
    counter = 0;
    if(board.levels() >= nToWin) // if there are enough levels for there to be a vertical win
    for(int j = 1; j <= board.cols(); j++) { // check vertical wins
        counterType = -2;
        counter = 0;
        for(int i = 1; i<= board.levels(); i++) {
            if(board.checkerAt(j, 1) == VACANT) // if the vertical is vacant, move on to the next column
            break;
            if(board.checkerAt(j, i) == VACANT) { //if a vacant spot is found, reset the values of counter and counterType
                counter = 0;
                counterType = -2;
                continue;
            }
            else if(board.checkerAt(j, i) != VACANT) { // if a spot isn't vacant
                if(counterType == -2) { // if the counterType is previously set as null, set it to the color of the checker at that space and set counter to 1
                    counterType = board.checkerAt(j, i);
                    counter = 1;
                    continue;
                }
                else if(board.checkerAt(j, i) == counterType) { // if the checker at a space is the same color as counterType, increment the counter
                    counter++;
                }
                else { // if the checker at a space is not the same color as counterType, set counterType to be that color and reset counter to 1
                    counter = 1;
                    counterType = board.checkerAt(j, i);
                    continue;
                }
            }
            if(counter == nToWin) { // if counter reaches the number of connections to win, return the winner and return true
                winner = counterType;
                return true;
            }
        }
    }

    counterType = -2; // reset values of counterType and counter
    counter = 0;
    if(board.levels() >= nToWin) { // this program checks the diagonals for wins from the bottom left corner and then continuing to the right
        for(int x = board.cols(); x >= 1; x--) {
            counterType = -2;
            counter = 0;
            int i = 1;
            int j = x;
            while(i <= board.levels() && j <= board.cols()) { // the way that counterType and counter is incremented and changed is the same way as in the check for horizontal and vertical wins
                if(board.checkerAt(j, i) == VACANT) {
                    counter = 0;
                    counterType = -2;
                }
                else if(board.checkerAt(j, i) != VACANT) {
                    if(counterType == -2) {
                        counterType = board.checkerAt(j, i);
                        counter = 1;
                    }
                    else if(board.checkerAt(j, i) == counterType) {
                        counter++;
                    }
                    else {
                        counter = 1;
                        counterType = board.checkerAt(j, i);
                    }
                }
                if(counter == nToWin) {
                    winner = counterType;
                    return true;
                }
                i++;
                j++;
            }
        }

        counterType = -2;
        counter = 0;
        for(int x = board.levels(); x >= 1; x--) { // check for diagonal wins starting from the bottom left corner and continuing upwards
            counterType = -2;
            counter = 0;
            int i = x;
            int j = 1;
            while(i <= board.levels() && j <= board.cols()) { // the way that counterType and counter is incremented and changed is the same way as in the check for horizontal and vertical wins
                if(board.checkerAt(j, i) == VACANT) {
                    counter = 0;
                    counterType = -2;
                }
                else if(board.checkerAt(j, i) != VACANT) {
                    if(counterType == -2) {
                        counterType = board.checkerAt(j, i);
                        counter = 1;
                    }
                    else if(board.checkerAt(j, i) == counterType) {
                        counter++;
                    }
                    else {
                        counter = 1;
                        counterType = board.checkerAt(j, i);
                    }
                }
                if(counter == nToWin) {
                    winner = counterType;
                    return true;
                }
                i++;
                j++;
            }
        }

        counterType = -2;
        counter = 0;
        for(int x = 1; x <= board.cols(); x++) { // check for diagonal wins starting at the top left corner and continuing downwards
            counterType = -2;
            counter = 0;
            int i = 1;
            int j = x;
            while(i <= board.levels() && j >= 1) {
                if(board.checkerAt(j, i) == VACANT) { // the way that counterType and counter is incremented and changed is the same way as in the check for horizontal and vertical wins
                    counter = 0;
                    counterType = -2;
                }
                else if(board.checkerAt(j, i) != VACANT) {
                    if(counterType == -2) {
                        counterType = board.checkerAt(j, i);
                        counter = 1;
                    }
                    else if(board.checkerAt(j, i) == counterType) {
                        counter++;
                    }
                    else {
                        counter = 1;
                        counterType = board.checkerAt(j, i);
                    }
                }
                if(counter == nToWin) {
                    winner = counterType;
                    return true;
                }
                i++;
                j--;
            }
        }

        counterType = -2;
        counter = 0;
        for(int x = board.levels(); x >= 1; x--) { // check for diagonal wins starting from the top right corner and continuing downwards
            counterType = -2;
            counter = 0;
            int i = x;
            int j = board.cols();
            while(i <= board.levels() && j >= 1) { // the way that counterType and counter is incremented and changed is the same way as in the check for horizontal and vertical wins
                if(board.checkerAt(j, i) == VACANT) {
                    counter = 0;
                    counterType = -2;
                }
                else if(board.checkerAt(j, i) != VACANT) {
                    if(counterType == -2) {
                        counterType = board.checkerAt(j, i);
                        counter = 1;
                    }
                    else if(board.checkerAt(j, i) == counterType) {
                        counter++;
                    }
                    else {
                        counter = 1;
                        counterType = board.checkerAt(j, i);
                    }
                }
                if(counter == nToWin) {
                    winner = counterType;
                    return true;
                }
                i++;
                j--;
            }
        }
    }

    if(board.numberEmpty() == 0) { // return true and winner is a tie if there are no more free positions on the board
        winner = TIE_GAME;
        return true;
    }

    return false;
}
