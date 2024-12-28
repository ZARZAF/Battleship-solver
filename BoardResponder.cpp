#include "BoardResponder.h"

void BoardResponder::generate_battlefield()
{
	while (ships.size() < N)
	{
		Ship rand_ship(Position(rand() % W, rand() % H));
		if (ships.find(rand_ship) == ships.end())
			ships.insert(rand_ship);
	}
}

BoardResponder::BoardResponder(int W, int H, int N, int R) : Board(W, H, N, R)
{
	generate_battlefield();
}

void BoardResponder::respond(Position strike_position)
{
	if (ships.find(Ship(strike_position)) != ships.end())
	{
		if (ships.size() == 1)
		{
			printf("Win!");
			game_won = true;
		}
		else
		{
			printf("Hit!");
			ships.erase(Ship(strike_position));
		}
			

		return;
	}

	std::vector<const Ship*> targets_in_range;

	for (auto it = ships.begin(); it != ships.end(); it++)
	{
		if (it->get_distance(strike_position) <= R)
			targets_in_range.push_back(&(*it));
	}

	printf("Miss! %d", (int)targets_in_range.size());
	for (auto it = targets_in_range.begin(); it != targets_in_range.end(); it++)
	{
		printf(" %lf", (**it).get_distance(strike_position));
	}
	printf("\n");
}

void BoardResponder::respond()
{
	int x, y;
	while (!game_won)
	{
		scanf("%d %d", &x, &y);
		respond(Position(x, y));
	}
	
}