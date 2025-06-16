#pragma once

#include "SDL.h"
#include "Tile.hpp"
#include <vector>

namespace Utils {
    bool touchesWall(SDL_Rect& box, std::vector<Tile*>& tiles);
    bool checkCollision(const SDL_Rect& a, const SDL_Rect& b);
}