#include "Ship.h"
#include <cmath>

Ship::Ship(Position position) : position(position), destroyed(false) {}

void Ship::destroy()
{
	destroyed = true;
}

bool Ship::is_destroyed() const
{
	return destroyed;
}

Position Ship::get_position() const
{
	return position;
}

double Ship::get_distance(Position destination) const
{
	return std::sqrt((destination.x - position.x) * (destination.x - position.x) +
		(destination.y - position.y) * (destination.y - position.y));
}

bool Ship::operator==(const Ship& other) const
{
	return (position.x == other.position.x) && (position.y == other.position.y);

}
