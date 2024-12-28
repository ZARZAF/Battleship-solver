#pragma once
#include "Board.h"
#include "Ship.h"
#include "HashShip.h"
#include <unordered_set>

class BoardResponder : Board
{
	std::unordered_set<Ship, HashShip> ships;

	void generate_battlefield();
	void respond(Position strike_position);

public:
	BoardResponder(int W, int H, int N, int R);

	void respond();
};