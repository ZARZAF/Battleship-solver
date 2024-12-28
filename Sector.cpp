#include "Sector.h"
#include <iostream>
#include <vector>
#include "HashPosition.h"
#include <unordered_set>

Cell Sector::strike(Position strike)
{
	printf("%d %d\n", strike.x, strike.y);

	char command[10];

	scanf("%s", command);
	if (std::string(command) == "Hit!") 
	{
		return Cell(strike, true);
	}
	else if (std::string(command) == "Miss!")
	{
		Cell miss(strike, false);
		int K;
		scanf("%d", &K);

		for (int i = 0; i < K; ++i) 
		{
			double distnace;
			scanf("%lf", &distnace);
			miss.add_distance(distnace);
		}

		return miss;
	}
	else if (std::string(command) == "Win!")
	{
			game_won = true;
			return Cell(strike, true);
	}
	else 
	{
		throw std::invalid_argument("received incorrect response");
	}
}

bool Sector::find_edge_point(Cell& corner)
{
	if (game_won)
		return true;

	Position rowling_to_center_pos = corner.get_position();
	if (corner.get_position().x == center.get_position().x)
	{
		while (corner.get_hit() && corner.get_position().y != center.get_position().y)
		{
			rowling_to_center_pos.y > center.get_position().y ? rowling_to_center_pos.y-- : rowling_to_center_pos.y++;
			corner = strike(rowling_to_center_pos);
			if (game_won)
				break;
		}
		return !(corner.get_position() == center.get_position());
	}
	else
	{
		while (corner.get_hit() && corner.get_position().x != center.get_position().x)
		{
			rowling_to_center_pos.x > center.get_position().x ? rowling_to_center_pos.x-- : rowling_to_center_pos.x++;
			corner = strike(rowling_to_center_pos);
			if (game_won)
				break;
		}
		return !(corner.get_position() == center.get_position());
	}
}

void Sector::partition(Position down_right, Position up_left)
{
	if (down_right == up_left || down_right.x < up_left.x || down_right.y < up_left.y || game_won)
		return;

	Sector sector(down_right, down_right, up_left);
	sector.solve();
}

void Sector::trilateration(Cell& vertex1, Cell& vertex2, Cell& vertex3, Position down_right, Position up_left)
{
	if (game_won)
		return;

	std::unordered_set<Position, HashPosition> radius_cells;
	std::unordered_set<Position, HashPosition> stricken_cells;
	const double epsilon = 0.5;

	for (auto it = vertex1.get_distances().begin(); it != vertex1.get_distances().end(); it++)
	{
		for (int x = it->first; x > 0; x--)
		{
			double y_squared = it->first * it->first - x * x;
			if (y_squared > 0)
			{
				int y = static_cast<int>(std::round(std::sqrt(y_squared)));

				if (std::abs(y * y - y_squared) < epsilon)
				{
					int cell_x = vertex1.get_position().x - x, cell_y = vertex1.get_position().y - y;
					if (in_area(up_left, down_right, cell_x, cell_y) && stricken_cells.find(Position(cell_x, cell_y)) == stricken_cells.end())
						radius_cells.insert(Position(cell_x, cell_y));
					cell_x = vertex1.get_position().x + x;
					cell_y = vertex1.get_position().y - y;
					if (x != 0 && in_area(up_left, down_right, cell_x, cell_y) && stricken_cells.find(Position(cell_x, cell_y)) == stricken_cells.end())
						radius_cells.insert(Position(cell_x, cell_y));
					cell_x = vertex1.get_position().x - x;
					cell_y = vertex1.get_position().y + y;
					if (y != 0 && in_area(up_left, down_right, cell_x, cell_y) && stricken_cells.find(Position(cell_x, cell_y)) == stricken_cells.end())
						radius_cells.insert(Position(cell_x, cell_y));
					cell_x = vertex1.get_position().x + x;
					cell_y = vertex1.get_position().y + y;
					if (x != 0 && y != 0 && in_area(up_left, down_right, cell_x, cell_y) && stricken_cells.find(Position(cell_x, cell_y)) == stricken_cells.end())
						radius_cells.insert(Position(cell_x, cell_y));
					
				}
			}
		}

		int strikes_count = it->second;

		for (auto v1_it = radius_cells.begin(); v1_it != radius_cells.end() && strikes_count > 0; v1_it++)
		{
			for (auto v2_it = vertex2.get_distances().begin(); v2_it != vertex2.get_distances().end() && strikes_count > 0; v2_it++)
			{
				int v2_x_offset = abs(vertex2.get_position().x - v1_it->x), v2_y_offset = abs(vertex2.get_position().y - v1_it->y);
 				if (std::abs(v2_it->first * v2_it->first - (v2_x_offset * v2_x_offset + v2_y_offset * v2_y_offset)) < epsilon)
				{
					for (auto v3_it = vertex3.get_distances().begin(); v3_it != vertex3.get_distances().end() && strikes_count > 0; v3_it++)
					{
						int v3_x_offset = abs(vertex3.get_position().x - v1_it->x), v3_y_offset = abs(vertex3.get_position().y - v1_it->y);
						if (std::abs(v3_it->first * v3_it->first - (v3_x_offset * v3_x_offset + v3_y_offset * v3_y_offset)) < epsilon)
						{
							strike(*v1_it);
							if (game_won)
								return;
							stricken_cells.insert(*v1_it);
							strikes_count--;
						}
					}
				}
			}
		}

		radius_cells.clear();
	}
}

void Sector::linear_bilateration(Cell& vertex1, Cell& vertex2)
{
	if (vertex1.get_position() == vertex2.get_position() || game_won)
		return;

	std::vector<int> integer_distances;
	const double epsilon = 1e-3;

	auto it = vertex1.get_distances().begin();
	for (it; it != vertex1.get_distances().end(); it++)
	{
		if (std::abs(std::fmod(it->first, 1.0)) < epsilon)
			integer_distances.push_back((*it).first);
	}

	if (vertex1.get_position().y == vertex2.get_position().y)
	{
		int vertex_distance = abs(vertex1.get_position().x - vertex2.get_position().x);

		for (size_t i = 0; i < integer_distances.size(); i++)
		{
			if (vertex_distance > integer_distances[i] && vertex2.get_distances().find(vertex_distance - integer_distances[i]) != vertex2.get_distances().end())
			{
				if (vertex1.get_position().x < vertex2.get_position().x)
					strike(Position(vertex1.get_position().x + integer_distances[i], vertex1.get_position().y));
				else
					strike(Position(vertex1.get_position().x - integer_distances[i], vertex1.get_position().y));
				if (game_won)
					return;
			}
		}
	}
	else if (vertex1.get_position().x == vertex2.get_position().x)
	{
		int vertex_distance = abs(vertex1.get_position().y - vertex2.get_position().y);

		for (size_t i = 0; i < integer_distances.size(); i++)
		{
			if (vertex_distance > integer_distances[i] && vertex2.get_distances().find(vertex_distance - integer_distances[i]) != vertex2.get_distances().end())
			{
				if (vertex1.get_position().y < vertex2.get_position().y)
					strike(Position(vertex1.get_position().x, vertex1.get_position().y + integer_distances[i]));
				else
					strike(Position(vertex1.get_position().x, vertex1.get_position().y - integer_distances[i]));
				if (game_won)
					return;
			}
		}
	}
}

double Sector::max_distance_to_corner(Position vertex, Position down_right, Position up_left) const
{
	double dist_to_top_left = std::sqrt(std::pow(vertex.x - up_left.x, 2) + std::pow(vertex.y - up_left.y, 2));
	double dist_to_top_right = std::sqrt(std::pow(vertex.x - down_right.x, 2) + std::pow(vertex.y - up_left.y, 2));
	double dist_to_bottom_left = std::sqrt(std::pow(vertex.x - up_left.x, 2) + std::pow(vertex.y - down_right.y, 2));
	double dist_to_bottom_right = std::sqrt(std::pow(vertex.x - down_right.x, 2) + std::pow(vertex.y - down_right.y, 2));

	return std::max({ dist_to_top_left, dist_to_top_right, dist_to_bottom_left, dist_to_bottom_right });
}

Sector::Sector(Position center_pos, Position down_right, Position up_left) : down_right(down_right), up_left(up_left), game_won(false),
center(strike(center_pos)), up(center), down(center), left(center), right(center) {}

bool Sector::solve()
{
	if (center.get_distances().empty())
		return game_won;

	if (center.get_hit())
	{
		partition(Position(down_right.x, center.get_position().y - 1), Position(center.get_position().x, up_left.y)); // Quadrant I
		partition(Position(center.get_position().x - 1, center.get_position().y - 1), up_left);						  // Quadrant II + up lane
		partition(Position(center.get_position().x - 1, down_right.y), Position(up_left.x, center.get_position().y)); // Quadrant III + left lane
		partition(down_right, Position(center.get_position().x, center.get_position().y));							  // Quadrant IV + down lane + right lane
	}
	else
	{
		bool partition_quadrant_I = false, partition_quadrant_II = false, partition_quadrant_III = false, partition_quadrant_IV = false;

		if (up_left.y != center.get_position().y)
		{
			up = strike(Position(center.get_position().x, up_left.y));
			if (!find_edge_point(up))
				partition_quadrant_I = partition_quadrant_II = true;
			else
				linear_bilateration(up, center);
		}

		if (up_left.x != center.get_position().x)
		{
			left = strike(Position(up_left.x, center.get_position().y));
			if (!find_edge_point(left))
				partition_quadrant_II = partition_quadrant_III = true;
			else
				linear_bilateration(left, center);
		}
		
		if (down_right.y != center.get_position().y)
		{
			down = strike(Position(center.get_position().x, down_right.y));
			if (!find_edge_point(down))
				partition_quadrant_III = partition_quadrant_IV = true;
			else
				linear_bilateration(center, down);
		}

		if (down_right.x != center.get_position().x)
		{
			right = strike(Position(down_right.x, center.get_position().y));
			if (!find_edge_point(right))
				partition_quadrant_IV = partition_quadrant_I = true;
			else
				linear_bilateration(center, right);
		}

		if (partition_quadrant_I)
			partition(Position(down_right.x, center.get_position().y - 1), Position(center.get_position().x + 1, up_left.y)); // coords
		else
			trilateration(center, up, right, Position(down_right.x, center.get_position().y - 1), Position(center.get_position().x + 1, up_left.y));
		if (partition_quadrant_II)
			partition(Position(center.get_position().x - 1, center.get_position().y - 1), up_left); // coords
		else
			trilateration(center, up, left, Position(center.get_position().x - 1, center.get_position().y - 1), up_left);
		if (partition_quadrant_III)
			partition(Position(center.get_position().x - 1, down_right.y), Position(up_left.x, center.get_position().y + 1)); // coords
		else
			trilateration(center, down, left, Position(center.get_position().x - 1, down_right.y), Position(up_left.x, center.get_position().y + 1));
		if (partition_quadrant_IV)
			partition(down_right, Position(center.get_position().x + 1, center.get_position().y + 1)); // coords
		else
			trilateration(center, down, right, down_right, Position(center.get_position().x + 1, center.get_position().y + 1));
	}

	return game_won;
}
