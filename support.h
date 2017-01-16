#ifndef SUPPORT_INCLUDED
#define SUPPORT_INCLUDED

#include <string>
#include <vector>
#include "provided.h"

int determineBestComputerMove(Scaffold& s, int color, int& rating, int nWin, int depth);
int determineBestHumanMove(Scaffold& s, int color, int& rating, int nWin, int depth);
bool completedSupport(const Scaffold& board, int& winner, int nToWin);

#endif
