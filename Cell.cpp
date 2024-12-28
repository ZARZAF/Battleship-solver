#include "Cell.h"
#include <stdexcept>

Cell::Cell(Position position, bool hit) : position(position), hit(hit) {}

void Cell::add_distance(double distance)
{
	if (distance <= 0)
		throw std::invalid_argument("received negative value");

	if (distances.find(distance) == distances.end())
		distances[distance] = 1;
	else
		distances[distance]++;
}

bool Cell::get_hit() const
{
	return hit;
}

Position Cell::get_position() const
{
	return position;
}

const std::unordered_map<double, int>& Cell::get_distances() const
{
	return distances;
}
