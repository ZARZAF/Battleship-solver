#pragma once
#include "Cell.h"

class Sector
{
	bool game_won;
	int W, H;
	Position down_right, up_left;
	Cell center, up, down, left, right;


	Cell strike(Position strike); 
	bool find_edge_point(Cell& corner); 
	void partition(Position down_right, Position up_left);
	void trilateration(Cell& vertex1, Cell& vertex2, Cell& vertex3, Position down_right, Position up_left); 
	void linear_bilateration(Cell& vertex1, Cell& vertex2);
	double max_distance_to_corner(Position vertex, Position down_right, Position up_left) const;

public: 

	Sector(Position center_pos, Position down_right, Position up_left);

	bool solve();
};