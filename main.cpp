
// main.cpp

#include "provided.h"
#include <string>
#include <iostream>
#include "support.h"
#include <cassert>
using namespace std;

int main()
{
	HumanPlayer hp("Rick");
	SmartPlayer sp("Computer");
	Game g1(4, 4, 3, &sp, &hp);
	g1.play();
	cout << endl << "This time I'll go first." << endl;
	Game g2(3, 3, 3, &sp, &hp);
	g2.play();

	/*

	Scaffold a(5, 5);
	assert(a.numberEmpty() == 25); // check if numberEmpty works properly
	assert(a.makeMove(1, RED) == true);
	assert(a.numberEmpty() == 24);
	assert(a.makeMove(1, RED) == true);
	assert(a.makeMove(1, RED) == true);
	assert(a.makeMove(1, RED) == true);
	assert(a.makeMove(1, RED) == true);
	assert(a.makeMove(1, RED) != true); // check can't make move if column is full
	a.display(); // check if the display is correct
	assert(a.cols() == 5);
	assert(a.levels() == 5);
	assert(a.checkerAt(1, 5) == true); // check if checkerAt function works
	assert(a.checkerAt(1, 4) == true);
	assert(a.checkerAt(1, 3) == true);
	assert(a.checkerAt(1, 2) == true);
	assert(a.checkerAt(1, 1) == true);
	assert(a.undoMove() == 1); // check if undoMove works properly
	assert(a.undoMove() == 1);
	assert(a.undoMove() == 1);
	assert(a.undoMove() == 1);
	assert(a.undoMove() == 1);
	assert(a.numberEmpty() == 25);
	BadPlayer b("test");
	assert(b.chooseMove(a, 5, BLACK ) == 1);
	assert(b.chooseMove(a, 5, BLACK ) == 1);
	assert(b.chooseMove(a, 5, BLACK ) == 1);
	assert(b.chooseMove(a, 5, BLACK ) == 1);
	assert(b.chooseMove(a, 5, BLACK ) == 1);
	assert(b.chooseMove(a, 5, BLACK ) == 2);// check badPlayer chooses move of the leftmost non-filled column

	int nWin = -2;
	HumanPlayer hp("Test1");
	SmartPlayer sp("Test2");
	Game g3(5, 5, 5, &hp, &sp);
	assert(g3.completed(nWin) == false);
	assert(nWin == -2);

	*/

}
