#include "Utils.hpp"
//#include "Constants.hpp"

bool Utils::touchesWall(SDL_Rect& box, std::vector<Tile*>& tiles) {
    for (Tile* tile : tiles) {
        if (tile && tile->getType() == 1 && checkCollision(box, tile->getBox())) {
            return true;
        }
    }

    return false;
}

bool Utils::checkCollision(const SDL_Rect& a, const SDL_Rect& b) {
    // sides of rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    // calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    // calculate the sides of  rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    // if any of the sides from A are outside of B
    if (bottomA <= topB) {
        return false;
    }
    if (topA >= bottomB) {
        return false;
    }
    if (rightA <= leftB) {
        return false;
    }
    if (leftA >= rightB) {
        return false;
    }

    return true;
}