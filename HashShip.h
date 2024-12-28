#pragma once
#include "Ship.h"
#include "HashPosition.h"
#include <unordered_map>

struct HashShip
{
    std::size_t operator()(const Ship& ship) const {
        return HashPosition()(ship.get_position());
    }
};
