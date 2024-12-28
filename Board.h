#pragma once

class Board
{
protected:
	static const int SECTION_LIMIT_WIDTH = 9999;
	const int W, H, N, R;
	bool game_won;

	Board(int W, int H, int N, int R);
};