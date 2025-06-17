#pragma once

#include <tuple>

enum class State { Idle, Run, Attack };

enum class Direction { Left, Right, Up, Down };

enum class Type { Player, Enemy };

struct TupleHash {
    template <typename T>
    inline void hashCombine(std::size_t& seed, const T& val) const {
        seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    template <typename... T>
    std::size_t operator()(const std::tuple<T...>& t) const {
        std::size_t seed = 0;
        std::apply([&](const auto&... args) {
            (..., hashCombine(seed, args));
        }, t);
        return seed;
    }
};