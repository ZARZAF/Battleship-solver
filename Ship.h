#pragma once
#include "Position.hpp"

class Ship
{
	Position position;
	bool destroyed;

public:
	Ship(Position position);

	void destroy();
	
	bool is_destroyed() const;
	Position get_position() const;
	double get_distance(Position destination) const;
	bool operator==(const Ship& other) const;
};