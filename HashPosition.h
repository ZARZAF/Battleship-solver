#pragma once
#include "Position.hpp"
#include <unordered_map>

struct HashPosition {
    std::size_t operator()(const Position& p) const {
        return std::hash<int>()(p.x) ^ (std::hash<int>()(p.y) << 1);
    }
};