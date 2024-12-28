#pragma once
#include "Board.h"

class BoardSolver : Board 
{
public:
	BoardSolver(int W, int H, int N, int R);
	void solve();
};