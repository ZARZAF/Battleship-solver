#pragma once

struct Position
{
	int x, y;

	Position(int x, int y) : x(x), y(y) {}

	bool operator==(const Position& other) const
	{
		return (x == other.x) && (y == other.y);
	}
};

inline bool in_area(const Position& up_left, const Position& down_right, int x, int y)
{
	return x >= up_left.x && x <= down_right.x && y >= up_left.y && y <= down_right.y;
}