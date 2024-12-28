#include <iostream>
#include "BoardSolver.h"
#include "Sector.h"

BoardSolver::BoardSolver(int W, int H, int N, int R) : Board(W,H,N,R){}

void BoardSolver::solve()
{
	int sector_width = std::min(SECTION_LIMIT_WIDTH, (int)(R / sqrt(2)) * 2);
	sector_width -= (sector_width + 1) % 2;
	int width_remainder = W % sector_width, height_remainder = H % sector_width;
	for (int i = 0; i < H / sector_width; i++)
	{
		for (int j = 0; j < W / sector_width; j++)
		{
			Position down_right((j + 1) * sector_width - 1, (i + 1) * sector_width - 1),
				up_left(j * sector_width, i * sector_width),
				center((down_right.x + up_left.x) / 2, (down_right.y + up_left.y) / 2);
			Sector sector(center, down_right, up_left);
			if (sector.solve())
			{
				game_won = true;
				return;
			}
		}
	}

	if (width_remainder != 0)
	{
		for (int i = 0; i < H / sector_width; i++)
		{
			Position down_right(W - 1, (i + 1) * sector_width - 1),
				up_left(W - width_remainder, i * sector_width),
				center(std::min(down_right.x, up_left.x + sector_width / 2), (down_right.y + up_left.y) / 2);
			Sector sector(center, down_right, up_left);
			if (sector.solve())
			{
				game_won = true;
				return;
			}
		}
	}

	if (height_remainder != 0)
	{
		for (int i = 0; i < W / sector_width; i++)
		{
			Position down_right((i + 1) * sector_width - 1, H - 1),
				up_left(i * sector_width, H - height_remainder),
				center((down_right.x + up_left.x) / 2, std::min(down_right.y, up_left.y + sector_width / 2));
			Sector sector(center, down_right, up_left);
			if (sector.solve())
			{
				game_won = true;
				return;
			}
		}
	}

	if (width_remainder != 0 && height_remainder != 0)
	{
		Position down_right(W - 1, H - 1),
			up_left(W - width_remainder, H - height_remainder),
			center(std::min(down_right.x, up_left.x + sector_width / 2), std::min(down_right.y, up_left.y + sector_width / 2));
		Sector sector(center, down_right, up_left);
		if (sector.solve())
		{
			game_won = true;
			return;
		}
	}
}
