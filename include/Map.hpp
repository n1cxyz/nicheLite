#pragma once

#include <vector>
#include "Tile.hpp"

class Map {
private:
    std::vector<Tile*> tiles;
    std::vector<SDL_Rect> clips;
public:
    Map();
    ~Map() {};

    void loadFromFile(const std::string& levelFile);
    void renderLevel(SDL_Renderer* renderer, SDL_Rect& camera);
    
    const std::vector<Tile*>& getTiles() const { return tiles; }
};