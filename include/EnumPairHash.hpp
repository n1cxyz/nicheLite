#pragma once

#include <utility>
#include <functional>
#include "State.hpp"
#include "Direction.hpp"

struct EnumPairHash {
    std::size_t operator()(const std::pair<State, Direction>& p) const {
        return std::hash<int>()(static_cast<int>(p.first)) ^ (std::hash<int>()(static_cast<int>(p.second)) << 1);
    }
};