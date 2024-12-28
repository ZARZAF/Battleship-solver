#pragma once
#include <unordered_map>
#include "Position.hpp"

class Cell
{
	Position position;
	bool hit;
	std::unordered_map<double, int> distances;

public:
	Cell(Position position, bool hit);

	void add_distance(double distance);

	bool get_hit() const;
	Position get_position() const;
	const std::unordered_map<double, int>& get_distances() const;
};